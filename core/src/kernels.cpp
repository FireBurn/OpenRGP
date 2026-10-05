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

// `pre_gfx12`: RDNA2/3 route scratch accesses through the vector-memory path (traced as VMEM, not FLAT).
int classify(const std::string& t, bool pre_gfx12) {
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
    if (starts("flat_")) return (int)InstCat::Flat;
    if (starts("scratch_")) return (int)(pre_gfx12 ? InstCat::Vmem : InstCat::Flat);
    if (starts("global_") || starts("buffer_") || starts("image_") || starts("tbuffer_")) return (int)InstCat::Vmem;
    // RDNA2/3 sometimes trace a v_mov from a constant or SGPR as an immediate-class instruction instead of a VALU one.
    if (starts("v_mov_b32")) {
        size_t c = t.find(','), e = t.find_first_of(" ,", c == std::string::npos ? t.size() : c + 2);
        std::string src = c == std::string::npos ? "" : t.substr(c + 1, e == std::string::npos ? std::string::npos : e - c - 1);
        size_t b = src.find_first_not_of(' ');
        if (b != std::string::npos && src[b] != 'v') return ClsEither;
    }
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
        IsaInst in_; in_.off = (uint32_t)addr; in_.size = 4u * words; in_.text = text; in_.cls = classify(text, mcpu.rfind("gfx12", 0) != 0);
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
        // A vector-memory instruction can be traced twice (the issue is replayed); the extra token is not an instruction.
        if (k > 0 && tk == tr[k - 1] && (tk == InstCat::Vmem || tk == InstCat::Flat) && in.cls != (int)tk) { k++; continue; }
        if (in.cls == (int)tk || (in.cls == ClsEither && (tk == InstCat::Valu || tk == InstCat::Immed))) { if (path) path->push_back((int)i); i++; k++; continue; }
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

// Wave64 waves on RDNA2/3 trace every vector instruction twice. Halve each run of identical vector tokens; empty if a
// run has odd length (the trace is not consistently doubled).
static std::vector<InstCat> collapse_wave64(const std::vector<InstCat>& tr) {
    std::vector<InstCat> out;
    for (size_t i = 0; i < tr.size();) {
        InstCat c = tr[i]; size_t j = i; while (j < tr.size() && tr[j] == c) j++;
        size_t run = j - i;
        bool vec = c == InstCat::Valu || c == InstCat::Vmem || c == InstCat::Flat || c == InstCat::Lds;
        if (vec) { if (run % 2) return {}; run /= 2; }
        out.insert(out.end(), run, c);
        i = j;
    }
    return out;
}

Match best_match(const std::vector<CodeObjectIsa>& isa, const std::vector<InstCat>& tr) {
    Match m; m.trace = tr;
    auto run = [&](const std::vector<InstCat>& t, Match& r) {
        for (size_t c = 0; c < isa.size(); c++) { size_t st = 0; size_t k = walk_best(isa[c], t, &st); if (k > r.consumed) { r.consumed = k; r.co = (int)c; r.start = st; } }
    };
    run(tr, m);
    if (m.consumed * 10 < tr.size() * 8) {
        auto col = collapse_wave64(tr);
        if (!col.empty() && col.size() != tr.size()) {
            Match m2; m2.trace = col; run(col, m2);
            if (m2.consumed * 10 >= col.size() * 8 && m2.consumed * tr.size() > m.consumed * col.size()) { m2.collapsed = true; return m2; }
        }
    }
    return m;
}

std::string kernel_sig(const CodeObjectIsa& c, size_t start) {
    return c.starts.size() > 1 ? c.sig + "@" + std::to_string(start) : c.sig;
}

std::string kernel_label(const CodeObjectIsa& c, size_t start) {
    std::string stage = c.name;
    for (size_t i = 0; i < c.starts.size(); i++) if ((size_t)c.starts[i] == start) stage = c.start_names[i];
    if (stage.find("_main") != std::string::npos && stage.find("_cs_") == std::string::npos) {
        static const char* stages[][2] = {{"_gs_main", "geometry/NGG"}, {"_ps_main", "pixel"}, {"_vs_main", "vertex"}, {"_hs_main", "hull"}, {"_ls_main", "local"}, {"_es_main", "export"}};
        for (auto& st : stages) if (stage.find(st[0]) != std::string::npos) return std::string(st[1]) + " shader (" + std::to_string(c.ins.size()) + " instrs in object)";
    }
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
            Match mt = best_match(isa, g.tr);
            size_t best = mt.consumed; int bi = mt.co; size_t bstart = mt.start;
            bool ok = mt.ok();
            std::string sig = ok ? kernel_sig(isa[bi], bstart) : "unmatched-" + std::to_string(g.tr.size());
            if (!have_isa) {   // stable id from the category sequence itself
                uint32_t h = 2166136261u; for (uint8_t k : key) h = (h ^ k) * 16777619u;
                char b[16]; snprintf(b, sizeof b, "t%08x", h); sig = b;
            }
            KernelStats& ks = out[sig];
            if (ks.sig.empty()) {
                ks.sig = sig;
                if (!have_isa) ks.label = "(" + std::to_string(g.tr.size()) + "-instruction trace; no llvm-objdump)";
                else if (ok) ks.label = kernel_label(isa[bi], bstart);
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
                walk_trace(isa[bi], mt.trace, &path, bstart);
                for (auto* w : g.ws) {
                    for (size_t i = 0, pi = 0; i < path.size() && pi < w->insts.size(); i++, pi++) {
                        if (mt.collapsed && pi < w->insts.size()) {   // each ISA instruction owns two trace entries when vector
                            bool vec = mt.trace[i] == InstCat::Valu || mt.trace[i] == InstCat::Vmem || mt.trace[i] == InstCat::Flat || mt.trace[i] == InstCat::Lds;
                            if (vec && pi + 1 < w->insts.size()) { auto& a = ks.by_mnemonic[isa[bi].ins[path[i]].text.substr(0, isa[bi].ins[path[i]].text.find(' '))]; a[0]++; a[1] += (uint64_t)(w->insts[pi].duration + w->insts[pi + 1].duration); a[2] += (uint64_t)(w->insts[pi].stall + w->insts[pi + 1].stall); pi++; continue; }
                        }
                        std::string m = isa[bi].ins[path[i]].text.substr(0, isa[bi].ins[path[i]].text.find(' '));
                        for (const char* sfx : {"_e32", "_e64"}) { size_t q = m.rfind(sfx); if (q != std::string::npos && q + 4 == m.size()) m.erase(q); }
                        auto& a = ks.by_mnemonic[m];
                        a[0]++; a[1] += (uint64_t)w->insts[pi].duration; a[2] += (uint64_t)w->insts[pi].stall;
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
        DispatchRow r; r.index = (int)out.size(); r.event = (int)i; r.begin = d.events[i].time; r.end = d.events[i].time; r.inferred = d.events[i].inferred;
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
            Match mt = best_match(isa, tr);
            if (mt.ok()) { sig = kernel_sig(isa[mt.co], mt.start); label = kernel_label(isa[mt.co], mt.start); }
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
