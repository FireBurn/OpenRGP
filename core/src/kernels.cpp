#include "openrgp/kernels.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <functional>
#include <sstream>
#include <unordered_map>
#include <unistd.h>

namespace openrgp {
namespace {

int classify(const std::string& t) {
    size_t sp = t.find(' ');
    std::string m = t.substr(0, sp);
    auto starts = [&](const char* p) { return m.rfind(p, 0) == 0; };
    if (m == "s_endpgm") return ClsEnd;
    if (m == "exp" || m == "export" || m == "s_version") return ClsSkip;   // exports and the version pseudo-op are not traced
    if (m == "s_branch") return (int)InstCat::Jump;
    if (starts("s_cbranch")) return ClsCondBranch;
    // Not traced: s_delay_alu, s_wait_alu, s_barrier_wait
    if (starts("s_delay") || m == "s_wait_alu" || m == "s_barrier_wait") return ClsSkip;
    if (m == "s_barrier_signal" || m == "s_barrier_signal_isfirst") return (int)InstCat::Msg;
    if (starts("s_wait") || starts("s_nop") || starts("s_clause") || starts("s_barrier") || starts("s_sleep") || starts("s_setprio") ||
        starts("s_code_end") || starts("s_icache") || starts("s_inst_prefetch") || starts("s_trap") || starts("s_set_inst"))
        return (int)InstCat::Immed;
    if (starts("s_load") || starts("s_buffer_load") || starts("s_prefetch")) return (int)InstCat::Smem;
    if (starts("s_sendmsg") || starts("s_ttrace") || starts("s_message")) return (int)InstCat::Msg;
    if (starts("s_")) return (int)InstCat::Salu;
    if (starts("ds_")) return (int)InstCat::Lds;
    if (starts("flat_") || starts("scratch_")) return (int)InstCat::Flat;
    if (starts("global_") || starts("buffer_") || starts("image_") || starts("tbuffer_")) return (int)InstCat::Vmem;
    return (int)InstCat::Valu;
}

std::string fnv_hex(const std::string& s) {
    uint64_t h = 1469598103934665603ull;
    for (unsigned char c : s) { h ^= c; h *= 1099511628211ull; }
    char b[17]; snprintf(b, sizeof b, "%08llx", (unsigned long long)(h & 0xffffffffull));
    return b;
}

bool disassemble(const uint8_t* elf, size_t size, const std::string& mcpu, CodeObjectIsa& co, std::string* err) {
    char path[] = "/tmp/openrgp-co-XXXXXX";
    int fd = mkstemp(path);
    if (fd < 0) { if (err) *err = "mkstemp failed"; return false; }
    if (write(fd, elf, size) != (ssize_t)size) { close(fd); unlink(path); if (err) *err = "write failed"; return false; }
    close(fd);
    std::string cmd = std::string("llvm-objdump -d --mcpu=") + mcpu + " --triple=amdgcn--amdpal " + path + " 2>/dev/null";
    FILE* f = popen(cmd.c_str(), "r");
    if (!f) { unlink(path); if (err) *err = "cannot run llvm-objdump"; return false; }
    std::string all; char buf[4096]; size_t n;
    while ((n = fread(buf, 1, sizeof buf, f)) > 0) all.append(buf, n);
    pclose(f); unlink(path);
    std::istringstream in(all); std::string line;
    std::unordered_map<uint32_t, int> idx;
    std::vector<uint32_t> label_off; std::vector<std::string> label_name;
    std::vector<uint32_t> targets;   // byte offsets, resolved after the pass
    std::string h;
    while (std::getline(in, line)) {
        if (line.empty()) continue;
        if (line[0] != '\t') {
            size_t lt = line.find('<'), gt = line.find('>');
            if (lt != std::string::npos && gt != std::string::npos && gt > lt && line.size() > gt + 1 && line[gt + 1] == ':') {
                // "0000000000000140 <_amdgpu_ps_main>:" starts a function
                char* e; unsigned long long a0 = strtoull(line.c_str(), &e, 16);
                label_off.push_back((uint32_t)a0); label_name.push_back(line.substr(lt + 1, gt - lt - 1));
            }
            if (co.name.empty() && lt != std::string::npos && gt != std::string::npos && line.find(' ') != std::string::npos && gt > lt)
                co.name = line.substr(lt + 1, gt - lt - 1);
            continue;
        }
        size_t c = line.find("//");
        if (c == std::string::npos) continue;
        std::string text = line.substr(1, c - 1);
        while (!text.empty() && (text.back() == ' ' || text.back() == '\t')) text.pop_back();
        // "// 000000000020: BFA50026 <_amdgpu_cs_main+0xbc>"
        const char* q = line.c_str() + c + 2;
        while (*q == ' ') q++;
        char* e; unsigned long long addr = strtoull(q, &e, 16);
        if (*e != ':') continue;
        q = e + 1; int words = 0;
        while (*q) {
            while (*q == ' ') q++;
            if (*q == '<' || !*q) break;
            const char* s = q; while (isxdigit((unsigned char)*q)) q++;
            if (q == s) break;
            words++;
        }
        IsaInst in_; in_.off = (uint32_t)addr; in_.size = 4u * words; in_.text = text; in_.cls = classify(text);
        long tgt = -1;
        const char* lt = strchr(q, '<');
        if (lt) { const char* pl = strstr(lt, "+0x"); if (pl) tgt = (long)strtoul(pl + 3, nullptr, 16); }
        idx[in_.off] = (int)co.ins.size();
        targets.push_back(tgt >= 0 ? (uint32_t)tgt : 0xffffffffu);
        co.ins.push_back(in_);
        h += text; h += '\n';
        const std::string& tx = co.ins.back().text;
        if (tx.find("wmma") != std::string::npos) co.wmma++;
        if (tx.find("dot4") != std::string::npos) co.dot4++;
        if (tx.rfind("v_exp", 0) == 0) co.exp++;
        if (tx.rfind("ds_", 0) == 0) co.ds++;
        if (tx.find("fma_mix") != std::string::npos || tx.find("dot2") != std::string::npos) co.mixfma++;
        if (tx.find("permlane") != std::string::npos || tx.find("dpp") != std::string::npos || tx.find("swizzle") != std::string::npos) co.permute++;
    }
    for (size_t i = 0; i < co.ins.size(); i++) {
        if (targets[i] != 0xffffffffu) { auto it = idx.find(targets[i]); if (it != idx.end()) co.ins[i].target = it->second; }
    }
    for (size_t k = 0; k < label_off.size(); k++) {
        auto it = idx.find(label_off[k]);
        if (it != idx.end()) { co.starts.push_back(it->second); co.start_names.push_back(label_name[k]); }
    }
    if (co.starts.empty() && !co.ins.empty()) { co.starts.push_back(0); co.start_names.push_back(co.name); }
    co.sig = fnv_hex(h);
    return !co.ins.empty();
}

}  // namespace

bool load_isa(const Profile& p, const std::string& mcpu, std::vector<CodeObjectIsa>& out, std::string* err) {
    out.clear();
    for (auto& r : p.code_objects) {
        CodeObjectIsa co;
        if (!disassemble(p.buffer.data() + r.elf_offset, r.size, mcpu, co, err)) {
            if (err && err->empty()) *err = "disassembly failed";
            return false;
        }
        out.push_back(std::move(co));
    }
    return true;
}

size_t walk_trace(const CodeObjectIsa& isa, const std::vector<InstCat>& tr, std::vector<int>* path, size_t start) {
    size_t i = start, k = 0;
    const auto& ins = isa.ins;
    while (k < tr.size() && i < ins.size()) {
        const IsaInst& in = ins[i];
        if (in.cls == ClsSkip) { i++; continue; }
        if (in.cls == ClsEnd) return k;
        InstCat tk = tr[k];
        if (tk == InstCat::Next && in.cls != ClsCondBranch) { k++; continue; }   // stray not-taken token
        if (k == 0 && tk == InstCat::Immed && in.cls != (int)InstCat::Immed) { k++; continue; }   // prologue s_setprio some drivers inject
        if (in.cls == (int)InstCat::Jump || in.cls == ClsCondBranch) {
            if (tk == InstCat::Jump && in.target >= 0) { if (path) path->push_back((int)i); i = (size_t)in.target; k++; continue; }
            if (tk == InstCat::Next && in.cls == ClsCondBranch) { if (path) path->push_back((int)i); i++; k++; continue; }
            return k;
        }
        if (in.cls == (int)tk) { if (path) path->push_back((int)i); i++; k++; continue; }
        return k;
    }
    return k;
}

size_t walk_best(const CodeObjectIsa& isa, const std::vector<InstCat>& tr, size_t* start_idx) {
    size_t best = 0, bs = 0;
    for (int st : isa.starts) { size_t k = walk_trace(isa, tr, nullptr, (size_t)st); if (k > best) { best = k; bs = (size_t)st; } }
    if (start_idx) *start_idx = bs;
    return best;
}

std::string kernel_label(const CodeObjectIsa& c) {
    if (c.wmma && c.exp) return "flash-attn (WMMA)";
    if (c.wmma) return "matmul (WMMA)";
    if (c.dot4 && c.ds) return "mat-vec int8 (dot4+LDS)";
    if (c.dot4) return "mat-vec int8 (dot4)";
    if (c.mixfma > 20 && c.permute) return "mat-vec float / norm";
    return "other (" + std::to_string(c.ins.size()) + " instrs)";
}

bool analyze_captures(const std::vector<std::string>& files, const std::string& mcpu, bool with_mnemonics,
                      std::map<std::string, KernelStats>& out, uint64_t* unidentified, std::string* err) {
    if (unidentified) *unidentified = 0;
    int cap = 0;
    for (auto& f : files) {
        Profile p;
        std::string e;
        if (!RgpFile::load(f, p, &e)) { if (err) *err = f + ": " + e; return false; }
        std::vector<CodeObjectIsa> isa;
        bool have_isa = load_isa(p, mcpu, isa, &e);
        if (!have_isa) isa.clear();   // no disassembler: fall back to grouping waves by their trace signature
        // group traced waves by identical category trace
        struct Group { std::vector<InstCat> tr; std::vector<const SqttWave*> ws; };
        std::map<std::vector<uint8_t>, Group> groups;
        std::vector<SqttDecode> dec(p.sqtt_data_ptr.size());
        for (size_t se = 0; se < p.sqtt_data_ptr.size(); se++) {
            if (!p.sqtt_data_ptr[se]) continue;
            if (!decode_sqtt(p.sqtt_data_ptr[se], p.sqtt_data[se].size, (int)se, dec[se], &e)) { if (err) *err = f + ": " + e; return false; }
        }
        for (auto& d : dec) for (auto& w : d.waves) {
            if (!w.traced || w.insts.empty()) continue;
            std::vector<uint8_t> key; key.reserve(w.insts.size());
            for (auto& i : w.insts) key.push_back((uint8_t)i.cat);
            auto& g = groups[key];
            if (g.ws.empty()) for (auto c : key) g.tr.push_back((InstCat)c);
            g.ws.push_back(&w);
        }
        for (auto& [key, g] : groups) {
            size_t best = 0; int bi = -1;
            size_t bstart = 0;
            for (size_t c = 0; c < isa.size(); c++) { size_t st = 0; size_t k = walk_best(isa[c], g.tr, &st); if (k > best) { best = k; bi = (int)c; bstart = st; } }
            bool ok = bi >= 0 && best >= g.tr.size() * 8 / 10;
            std::string sig = ok ? isa[bi].sig : "unmatched-" + std::to_string(g.tr.size());
            if (!have_isa) {   // stable id from the category sequence itself
                uint32_t h = 2166136261u; for (uint8_t k : key) h = (h ^ k) * 16777619u;
                char b[16]; snprintf(b, sizeof b, "t%08x", h); sig = b;
            }
            KernelStats& ks = out[sig];
            if (ks.sig.empty()) {
                ks.sig = sig;
                if (!have_isa) ks.label = "(" + std::to_string(g.tr.size()) + "-instruction trace; no llvm-objdump)";
                else if (ok) ks.label = kernel_label(isa[bi]);
                else if (bi >= 0 && best > 0) ks.label = "unidentified (best " + std::to_string(100 * best / g.tr.size()) + "% of " + isa[bi].sig + ")";
                else ks.label = "unidentified";
            }
            if (!ok && have_isa && unidentified) *unidentified += g.ws.size();
            if (std::find(ks.captures.begin(), ks.captures.end(), cap) == ks.captures.end()) ks.captures.push_back(cap);
            int64_t b = INT64_MAX, e2 = 0;
            for (auto* w : g.ws) {
                ks.waves++; ks.wave_cycles += (uint64_t)(w->end - w->begin); ks.exec += w->exec; ks.wait += w->wait; ks.stall += w->stall;
                ks.insts = w->insts.size();
                b = std::min(b, w->begin); e2 = std::max(e2, w->end);
            }
            ks.spans.push_back(e2 - b);
            if (with_mnemonics && ok) {
                std::vector<int> path;
                walk_trace(isa[bi], g.tr, &path, bstart);
                for (auto* w : g.ws) {
                    for (size_t i = 0; i < path.size() && i < w->insts.size(); i++) {
                        std::string m = isa[bi].ins[path[i]].text.substr(0, isa[bi].ins[path[i]].text.find(' '));
                        for (const char* sfx : {"_e32", "_e64"}) { size_t q = m.rfind(sfx); if (q != std::string::npos && q + 4 == m.size()) m.erase(q); }
                        auto& a = ks.by_mnemonic[m];
                        a[0]++; a[1] += (uint64_t)w->insts[i].duration; a[2] += (uint64_t)w->insts[i].stall;
                    }
                }
            }
        }
        cap++;
    }
    return true;
}

bool analyze_dispatches(const std::string& file, const std::string& mcpu, int se, std::vector<DispatchRow>& out, std::string* err) {
    Profile p; std::string e;
    if (!RgpFile::load(file, p, &e)) { if (err) *err = e; return false; }
    if (se < 0 || se >= (int)p.sqtt_data_ptr.size() || !p.sqtt_data_ptr[se]) { if (err) *err = "no such shader engine"; return false; }
    SqttDecode d;
    if (!decode_sqtt_gfx12(p.sqtt_data_ptr[se], p.sqtt_data[se].size, se, d, &e)) { if (err) *err = e; return false; }
    std::vector<CodeObjectIsa> isa;
    bool have_isa = load_isa(p, mcpu, isa, &e);
    std::vector<int> ev_index;   // dispatch event index -> row
    for (size_t i = 0; i < d.events.size(); i++) {
        if (d.events[i].kind != EventKind::Dispatch || d.events[i].waves_started == 0) { ev_index.push_back(-1); continue; }
        DispatchRow r; r.index = (int)out.size(); r.begin = d.events[i].time; r.end = d.events[i].time; r.inferred = d.events[i].inferred;
        for (int k = 0; k < 3; k++) r.dim[k] = d.events[i].dim[k];
        ev_index.push_back(r.index); out.push_back(r);
    }
    std::vector<std::map<std::string, std::pair<int, std::string>>> votes(out.size());
    for (auto& w : d.waves) {
        if (w.dispatch < 0 || w.dispatch >= (int)ev_index.size() || ev_index[w.dispatch] < 0) continue;
        DispatchRow& r = out[ev_index[w.dispatch]];
        r.waves++; r.begin = std::min(r.begin, w.begin); r.end = std::max(r.end, w.end);
        if (!w.traced || w.insts.empty()) continue;
        r.traced++;
        std::string sig = "?", label = "unidentified";
        if (have_isa) {
            std::vector<InstCat> tr; for (auto& i : w.insts) tr.push_back(i.cat);
            size_t best = 0; int bi = -1;
            for (size_t c = 0; c < isa.size(); c++) { size_t k = walk_best(isa[c], tr); if (k > best) { best = k; bi = (int)c; } }
            if (bi >= 0 && best >= tr.size() * 8 / 10) { sig = isa[bi].sig; label = kernel_label(isa[bi]); }
        } else {
            sig = "trace-" + std::to_string(w.insts.size()); label = "(no llvm-objdump)";
        }
        auto& v = votes[ev_index[w.dispatch]][sig]; v.first++; v.second = label;
    }
    for (size_t i = 0; i < out.size(); i++) {
        int best = 0; for (auto& [sig, v] : votes[i]) if (v.first > best) { best = v.first; out[i].sig = sig; out[i].label = v.second; }
    }
    return true;
}

}  // namespace openrgp
