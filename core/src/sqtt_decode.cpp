#include "openrgp/sqtt_decode.h"

#include <array>
#include <cstdlib>
#include <deque>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <map>
#include <unordered_map>

namespace openrgp {

const char* event_kind_name(EventKind k) {
    static const char* n[] = {"dispatch", "cs-partial-flush", "cache-flush", "bottom-of-pipe", "tt-flush", "save-context", "tt-stall-begin", "tt-stall-end", "packet-loss", "other"};
    return n[(int)k];
}

const char* inst_cat_name(InstCat c) {
    static const char* n[] = {"none", "smem", "salu", "vmem", "flat", "lds", "valu", "jump", "next", "immed", "trap", "msg", "bvh"};
    return n[(int)c];
}

namespace {

enum Tok : uint8_t {
    T_UNKNOWN, T_EVENT, T_EVENT_SYNC, T_REG, T_REG_INIT, T_VALU_INST, T_IMM_ONE, T_IMMEDIATE, T_WAVE_READY,
    T_NEW_PC, T_WAVE_END, T_WAVE_START, T_WAVE_START_EXT, T_WAVE_ALLOC, T_SHADER_DATA, T_SHADER_DATA_SHORT,
    T_UTIL_COUNTER, T_TIME, T_NOP, T_MISC, T_TIMESTAMP, T_HEADER, T_INST, T_EXEC_POPCOUNT1, T_EXEC_POPCOUNT3, T_TIME_SHORT
};

struct Info { uint8_t type, length, tb, te; };

struct Enc { uint8_t type, pattern, plen, length, tb, te; };

// Prefix table: indexed by the low 8 bits of the stream at the token start (LSB first).
// Built in three layers, each overriding the previous one (RDNA2 base, RDNA3, RDNA4).
struct Table {
    std::array<Info, 256> t;
    void add(const Enc& e) {
        for (int i = e.pattern; i < 256; i += 1 << e.plen) t[i] = {e.type, e.length, e.tb, e.te};
    }
    // layer 0 = RDNA2 (tt 1-2), 1 = RDNA3 (tt 3), 2 = RDNA4 (tt 4)
    explicit Table(int layer) {
        t.fill({T_UNKNOWN, 4, 0, 0});
        static const Enc base[] = {
            {T_INST,        0b010,      3, 20, 4, 7},   {T_VALU_INST,   0b011,      3, 12, 3, 6},
            {T_IMM_ONE,     0b1101,     4, 12, 4, 7},   {T_IMMEDIATE,   0b00100,    5, 24, 5, 8},
            {T_WAVE_READY,  0b10100,    5, 24, 5, 8},   {T_NEW_PC,      0b0100001,  7, 64, 8, 11},
            {T_WAVE_START,  0b01100,    5, 32, 5, 7},   {T_WAVE_START_EXT, 0b11100, 5, 48, 5, 7},
            {T_WAVE_ALLOC,  0b00101,    5, 20, 5, 8},   {T_WAVE_END,    0b10101,    5, 20, 5, 8},
            {T_SHADER_DATA, 0b00110,    5, 52, 5, 8},   {T_SHADER_DATA_SHORT, 0b10110, 5, 28, 5, 8},
            {T_UTIL_COUNTER,0b0110001,  7, 64, 7, 9},   {T_TIME,        0b1000,     4,  8, 4, 8},
            {T_NOP,         0b0000,     4,  4, 0, 0},   {T_MISC,        0b1010001,  7, 24, 7, 16},
            {T_EVENT,       0b01100001, 8, 24, 8, 11},  {T_EVENT_SYNC,  0b11100001, 8, 32, 8, 11},
            {T_REG,         0b1001,     4, 64, 4, 7},   {T_REG_INIT,    0b1110001,  7, 64, 7, 10},
            {T_TIMESTAMP,   0b0000001,  7, 64, 16, 64}, {T_HEADER,      0b0010001,  7, 64, 0, 0},
        };
        for (auto& e : base) add(e);
        static const Enc rdna3[] = {
            {T_MISC,        0b1010001,  7, 24, 7, 16},  {T_UTIL_COUNTER,0b0110001,  7, 48, 7, 9},
            {T_TIMESTAMP,   0b0000001,  7, 48, 12, 48},
        };
        if (layer >= 1) for (auto& e : rdna3) add(e);
        static const Enc rdna4[] = {
            {T_INST,        0b010,      3, 20, 3, 6},   {T_SHADER_DATA, 0b0000110,  7, 56, 7, 10},
            {T_SHADER_DATA_SHORT, 0b1000110, 7, 32, 7, 10}, {T_EXEC_POPCOUNT1, 0b1100110, 7, 24, 7, 10},
            {T_EXEC_POPCOUNT3, 0b010110, 6, 48, 6, 9},  {T_NEW_PC,      0b0100001,  7, 72, 8, 11},
            {T_WAVE_START_EXT, 0b11100, 5, 40, 5, 7},   {T_WAVE_ALLOC,  0b00101,    5, 24, 5, 8},
            {T_TIMESTAMP,   0b0000001,  7, 64, 12, 64},
        };
        if (layer >= 2) for (auto& e : rdna4) add(e);
        // Seen in GFX12 captures from radv but absent from the reference tables: 8-bit tokens with prefixes 1110 and
        // 1111 whose bits 4-5 advance the clock (bits 6-7 carry something else). Found by matching instruction
        // times against AMD's rocprof-trace-decoder 0.1.6 output.
        static const Enc radv_time[] = {
            {T_TIME_SHORT,  0b1110,     4,  8, 4, 6},   {T_TIME_SHORT,  0b1111,     4,  8, 4, 6},
        };
        for (auto& e : radv_time) add(e);   // all generations: radv traces carry these short clock tokens
    }
};

// Instruction codes reported by the INST token (RDNA4 numbering) -> category and issue cycles.
struct Mapped { InstCat cat; int cycles; bool other_simd = false; };

Mapped map_inst(int e, int dprate, int derate) {
    using C = InstCat;
    switch (e) {
    case 0: return {C::Salu, 1};  // salu
    case 1: return {C::Smem, 1};  // smem_rd
    case 2: return {C::Smem, 1};  // smem_wr
    case 3: return {C::Jump, 1};  // branch_taken
    case 4: return {C::Next, 1};  // branch_not_taken
    case 5: return {C::Salu, 1};  // jump
    case 6: return {C::Trap, 1};  // trap
    case 7: return {C::Salu, 1};  // salu_no_exec
    case 8: return {C::Trap, 1};  // fatal_halt
    case 9: return {C::Msg, 1};  // message
    case 10: return {C::Valu, 1};  // valu_1
    case 11: return {C::Valu, 4};  // valut_4
    case 12: return {C::Valu, 1};  // valub_1
    case 13: return {C::Valu, 2};  // valub_2
    case 14: return {C::Valu, 4};  // valub_4
    case 15: return {C::Valu, 16};  // valub_16
    case 18: return {C::Valu, 1};  // vinterp
    case 19: return {C::Immed, 1};  // barrier_wait
    case 28: return {C::Flat, 2};  // flat_rd_2
    case 29: return {C::Flat, 3};  // flat_wr_3
    case 30: return {C::Flat, 4};  // flat_wr_4
    case 31: return {C::Flat, 5};  // flat_wr_5
    case 32: return {C::Flat, 6};  // flat_wr_6
    case 33: return {C::Vmem, 1};  // sgmem_rd_1
    case 34: return {C::Vmem, 2};  // sgmem_rd_2
    case 35: return {C::Vmem, 1};  // sgmem_wr_1
    case 36: return {C::Vmem, 2};  // sgmem_wr_2
    case 37: return {C::Vmem, 3};  // sgmem_wr_3
    case 38: return {C::Vmem, 4};  // sgmem_wr_4
    case 39: return {C::Vmem, 5};  // sgmem_wr_5
    case 40: return {C::Vmem, 6};  // sgmem_wr_6
    case 41: return {C::Lds, 1};  // lds_rd
    case 42: return {C::Lds, 1};  // lds_wr_1
    case 43: return {C::Lds, 2};  // lds_wr_2
    case 44: return {C::Lds, 3};  // lds_wr_3
    case 45: return {C::Lds, 4};  // lds_wr_4
    case 46: return {C::Lds, 5};  // lds_wr_5
    case 47: return {C::Vmem, 1};  // buf_rd_1
    case 48: return {C::Vmem, 2};  // buf_rd_2
    case 49: return {C::Vmem, 1};  // buf_wr_1
    case 50: return {C::Vmem, 2};  // buf_wr_2
    case 51: return {C::Vmem, 3};  // buf_wr_3
    case 52: return {C::Vmem, 4};  // buf_wr_4
    case 53: return {C::Vmem, 5};  // buf_wr_5
    case 54: return {C::Vmem, 6};  // buf_wr_6
    case 55: return {C::Vmem, 1};  // img_sample_1
    case 56: return {C::Vmem, 2};  // img_sample_2
    case 57: return {C::Vmem, 3};  // img_sample_3
    case 58: return {C::Vmem, 4};  // img_sample_4
    case 59: return {C::Vmem, 5};  // img_sample_5
    case 60: return {C::Vmem, 6};  // img_sample_6
    case 61: return {C::Vmem, 7};  // img_sample_7
    case 62: return {C::Vmem, 8};  // img_sample_8
    case 63: return {C::Vmem, 9};  // img_sample_9
    case 64: return {C::Vmem, 10};  // img_sample_10
    case 65: return {C::Vmem, 11};  // img_sample_11
    case 66: return {C::Vmem, 12};  // img_sample_12
    case 68: return {C::Vmem, 1};  // img_rd_1
    case 69: return {C::Vmem, 2};  // img_rd_2
    case 70: return {C::Vmem, 3};  // img_rd_3
    case 71: return {C::Vmem, 4};  // img_rd_4
    case 72: return {C::Vmem, 2};  // img_wr_2
    case 73: return {C::Vmem, 3};  // img_wr_3
    case 74: return {C::Vmem, 4};  // img_wr_4
    case 75: return {C::Vmem, 5};  // img_wr_5
    case 76: return {C::Vmem, 6};  // img_wr_6
    case 77: return {C::Vmem, 7};  // img_wr_7
    case 78: return {C::Vmem, 8};  // img_wr_8
    case 103: return {C::Bvh, 8};  // raytrace8
    case 104: return {C::Bvh, 9};  // raytrace9
    case 105: return {C::Bvh, 11};  // raytrace11
    case 106: return {C::Bvh, 12};  // raytrace12
    case 110: return {C::Lds, 1};  // lds_dir_load
    case 111: return {C::Lds, 1};  // lds_param_load
    case 114: return {C::Salu, 1};  // salu_wr_exec
    case 115: return {C::Valu, 1};  // valu1_wr_exec
    case 116: return {C::Valu, 2};  // valu_b2_wr_exec
    case 117: return {C::Salu, 1};  // rfe
    case 118: return {C::Bvh, 6};  // lds_bvh_6
    case 121: return {C::Bvh, 10};  // lds_bvh_10
    case 122: return {C::Msg, 1};  // barrier_signal
    case 135: return {C::Salu, 1};  // dyn_vgpr
    case 136: return {C::Salu, 1};  // try_lock
    case 137: return {C::Salu, 1};  // unlock
    case 138: return {C::Msg, 1};  // barrier_join
    case 140: return {C::Valu, 8};  // wmma8
    case 141: return {C::Valu, 16};  // wmma16
    case 142: return {C::Valu, 32};  // wmma32
    case 143: return {C::Valu, 64};  // wmma64
    case 150: return {C::Smem, 1};  // icpref
    case 151: return {C::Smem, 1};  // kcpref
    case 152: return {C::Salu, 3};  // salu_float3
    case 153: return {C::Valu, 1};  // valu_scl_trans
    case 155: return {C::Salu, 2};  // salu2
    case 156: return {C::Salu, 5};  // salu5
    case 146: return {C::Valu, dprate};            // valu_dpfp
    case 147: return {C::Valu, dprate * derate};   // valu_derate
    }
    if (e >= 80 && e <= 84) return {C::Lds, e - 79, true};          // LDS issued by another SIMD
    if (e >= 85 && e <= 89) return {C::Flat, e - 83, true};         // FLAT issued by another SIMD
    if (e == 119) return {C::Lds, 6, true};
    if (e == 120) return {C::Lds, 10, true};
    if (e >= 188 && e < 222) return {C::Vmem, e + 1 - 188, true};   // VMEM issued by another SIMD
    if (e >= 222) return {C::Vmem, e + 1 - 222};                                                           // block store
    return {C::None, 0};
}

#include "inst_tables.inc"

constexpr int kInstRfe = 117, kInstTrap = 6, kInstJump = 5;

enum State { S_EMPTY = 0, S_IDLE, S_EXEC, S_WAIT, S_STALL };

struct WaveBuild {
    SqttWave w;
    int cur_state = S_IDLE;
    int ver = 4;                 // SQTT version: <= 3 extends s_barrier waits (RDNA2/3)
    bool extend_barrier = false;
    int64_t last_state_cycle = 0;
    int trap = 0;  // 0 restored, 2 standby
    bool done = false;
    std::vector<std::pair<int64_t, int>> timeline;  // (duration, state), merged runs

    void update_state(int ns, int64_t time) {
        if (time > last_state_cycle) {
            if (timeline.empty() || timeline.back().second != cur_state) timeline.push_back({0, cur_state});
            timeline.back().first += time - last_state_cycle;
            last_state_cycle = time;
        }
        cur_state = ns;
    }
    void update_barrier(int64_t t) {
        if (!extend_barrier) return;
        extend_barrier = false;
        if (w.insts.empty()) return;
        WaveInst& back = w.insts.back();
        if (back.cat == InstCat::Immed) {
            update_state(S_WAIT, back.time + back.duration);
            update_state(S_EXEC, t + 1);
            back.duration = std::max<int64_t>(0, t - back.time);
            back.cat = InstCat::Msg;
        }
    }
    void immediate(int64_t t) {
        update_barrier(t);
        if (trap) return;
        int64_t time = t;
        if (!w.insts.empty()) time = std::min(time, w.insts.back().time + w.insts.back().duration);
        int64_t stall = t - time;
        w.insts.push_back({time, InstCat::Immed, stall + 1, stall});
        update_state(S_WAIT, time);
        update_state(S_EXEC, t + 1);
    }
    void valu(int64_t t, bool w64) {
        update_barrier(t);
        if (trap) return;
        int64_t time = t, dur = w64 ? 2 : 1, stall = 0;
        if (cur_state == S_STALL && last_state_cycle < time) { stall = time - last_state_cycle; dur += stall; time = last_state_cycle; }
        w.insts.push_back({time, InstCat::Valu, dur, stall});
        update_state(S_EXEC, t);
    }
    void inst(int64_t t, int code, Mapped m) {
        update_barrier(t);
        if (code == kInstRfe) {
            w.pcs.push_back({w.insts.size(), 0});
            trap = 0;
            if (!w.insts.empty() && w.insts.back().cat == InstCat::Trap)
                w.insts.back().duration = std::max<int64_t>(w.insts.back().duration, t + 1 - w.insts.back().time);
            return;
        } else if (code == kInstTrap) {
            w.insts.push_back({t, InstCat::Trap, 1, 0});
            trap = 2;
        }
        if (trap) return;
        w.end = t;
        if (m.cat == InstCat::Immed) { immediate(t); return; }   // the shipped 0.1.6 decoder does not extend barriers (only newer sources do)
        if (m.cat == InstCat::None) return;
        int64_t time = t, dur = m.cycles, stall = 0;
        if (cur_state == S_STALL && last_state_cycle < time) { stall = time - last_state_cycle; dur += stall; time = last_state_cycle; }
        w.insts.push_back({time, m.cat, dur, stall});
        if (code == kInstJump) w.pcs.push_back({w.insts.size(), 0});
        update_state(S_EXEC, t);
    }
    void wave_ready(int64_t t) { update_barrier(t - 1); update_state(S_STALL, t); }
    void new_pc(int64_t t, uint64_t pc) {
        update_barrier(t);
        if (w.pcs.empty() || trap) return;
        size_t idx = w.pcs.size();
        while (idx > 0 && w.pcs[idx - 1].addr == 0) idx--;
        if (idx == w.pcs.size()) w.pcs.push_back({w.insts.size(), 0});
        w.pcs[idx].addr = pc << 2;
    }
    void complete(int64_t t) {
        update_state(S_EMPTY, t);
        w.end = t;
        done = true;
        w.complete = true;
        if (w.insts.empty()) return;
        int64_t time = w.insts.back().time + w.insts.back().duration;
        if (time < t && trap == 0) w.insts.push_back({time, InstCat::Msg, t - time, 0});
    }
    void finish() {
        for (auto& [d, s] : timeline) {
            if (s == S_EXEC) w.exec += d; else if (s == S_WAIT) w.wait += d; else if (s == S_STALL) w.stall += d;
        }
    }
};

struct Bits {
    const uint8_t* d; size_t nbytes;
    // 64 bits of the stream starting at bit `pos`, LSB first, zero padded past the end.
    uint64_t peek(size_t pos) const {
        unsigned __int128 v = 0;
        size_t byte = pos / 8;
        for (int i = 0; i < 9; i++) if (byte + i < nbytes) v |= (unsigned __int128)d[byte + i] << (8 * i);
        return (uint64_t)(v >> (pos % 8));
    }
};

}  // namespace

bool decode_sqtt(const uint8_t* data, size_t size, int se, SqttDecode& out, std::string* err) {
    static const Table tbl_rdna2(0), tbl_rdna3(1), tbl_rdna4(2);
    Bits bits{data, size};
    size_t pos = 0, end = size * 8;
    // The stream starts with a HEADER token (prefix 0010001); its version field selects the token layout.
    const int ver = (int)((bits.peek(0) >> 7) & 0x3f);
    if ((bits.peek(0) & 0x7f) != 0x11 || ver < 1 || ver > 4) {
        if (err) *err = "unsupported SQTT stream (version " + std::to_string(ver) + "; supported: 1-2 RDNA2, 3 RDNA3, 4 RDNA4)";
        return false;
    }
    const Table& table = ver >= 4 ? tbl_rdna4 : ver == 3 ? tbl_rdna3 : tbl_rdna2;
    int64_t now = 0;
    bool is_ext = false, have_header = false, stop = false;
    int dprate = 1, derate = 1;
    int target_sa_wgp = 0, target_simd = 0;
    uint64_t wave_pgm[2][4] = {};
    uint32_t cs_dim[2][4][3] = {};
    int cur_dispatch[2][4]; for (auto& a : cur_dispatch) for (auto& v : a) v = -1;
    std::map<int, uint64_t> running;                // gpu location -> start pc
    std::map<int, std::pair<size_t, int64_t>> run_idx;  // gpu location -> (index in out.waves, begin)
    std::array<std::vector<WaveBuild>, 32> slots;   // per wave slot of the traced SIMD
    std::vector<WaveBuild> traced_done;
    auto flush_slot = [&](int s) {
        while (!slots[s].empty() && slots[s].back().done) { traced_done.push_back(std::move(slots[s].back())); slots[s].pop_back(); }
    };

    // Pass 1: bit stream -> timestamped tokens.
    struct Raw { int64_t time; uint64_t c; uint8_t type; size_t pos = 0; uint8_t len = 0; };
    std::vector<Raw> toks; toks.reserve(size / 3);
    while (pos + 8 <= end) {
        uint64_t cur = bits.peek(pos);
        if (ver >= 4 && is_ext && (cur & 1)) { pos += 8; continue; }
        const Info& info = table.t[cur & 0xff];
        if (info.type == T_NOP) { pos += 4; continue; }
        is_ext = info.type == T_WAVE_START_EXT;
        uint64_t len = info.length;
        if (pos + len > end + 64) break;
        if (info.type == T_TIMESTAMP) {
            if (ver >= 4) {            // rt:1 pl:1 tl:1 time:52
                bool rt = (cur >> 7) & 1; if (!rt) now += (int64_t)(cur >> 12);
            } else if (ver == 3) {     // pl:1 (bit 8) rt:1 (bit 9) time:36 (bit 12)
                bool rt = (cur >> 9) & 1; if (!rt) now += (int64_t)((cur >> 12) & ((1ull << 36) - 1));
            } else {                   // type:2 (bits 14-15) time:48 (bit 16)
                if (((cur >> 14) & 3) == 1) now += (int64_t)(cur >> 16);
            }
            pos += len; continue;
        }
        { uint64_t mask = (info.te > info.tb) ? ((1ull << (info.te - info.tb)) - 1) : 0;
          now += (int64_t)((cur >> info.tb) & mask) + (info.type == T_TIME ? 4 : 0); }
        uint64_t c = cur;
        if (len == 72) c = bits.peek(pos + 8);
        pos += len;
        out.tokens++;
        int64_t t = now;
        if (ver <= 3 && info.type == T_WAVE_READY) t -= 1;
        if (info.type == T_TIME || info.type == T_TIME_SHORT) continue;   // pure clock advances: consumed, not tokens
        toks.push_back({t, c, info.type, pos - len, (uint8_t)len});
    }
    // RDNA2/3 emit tokens slightly out of time order; the hardware reference re-sorts them through a small lookahead.
    if (ver <= 3) {
        std::deque<Raw> la; std::vector<Raw> sorted; sorted.reserve(toks.size());
        for (auto& r : toks) {
            if (!la.empty() && r.time < la.back().time) la.push_front(r); else la.push_back(r);
            while (!la.empty() && la.front().time < la.back().time) { sorted.push_back(la.front()); la.pop_front(); }
        }
        while (!la.empty()) { sorted.push_back(la.front()); la.pop_front(); }
        toks.swap(sorted);
    }

    // Pass 2: interpret tokens.
    for (const Raw& tk : toks) {
        if (stop) break;
        now = tk.time; uint64_t c = tk.c; const unsigned type = tk.type;
        if (out.first_time == 0) out.first_time = now;
        out.last_time = now;

        switch (type) {
        case T_HEADER: {
            out.version = (c >> 7) & 0x3f;
            if (have_header) break;   // headers repeat when the buffer is re-armed; the first one decides the layout
            if (out.version != ver) {
                if (!have_header) { if (err) *err = "SQTT header version " + std::to_string(out.version) + " disagrees with the stream"; return false; }
                out.desync = true; stop = true; break;   // a second header means the stream lost sync; keep what was decoded
            }
            int dsimd = (c >> 13) & 3, dwgp = (c >> 15) & 7, dsa = (c >> 19) & 1;
            target_sa_wgp = (dsa << 7) + dwgp; target_simd = dsimd;
            int dpr = (c >> 28) & (ver < 3 ? 0xf : 7);
            dprate = dpr ? (1 << (dpr - 1)) : 1;
            derate = 1 << ((c >> 33) & 7);
            out.target_cu = target_sa_wgp; out.target_simd = target_simd;
            have_header = true;
            break; }
        case T_REG: {
            unsigned pipe = (c >> 7) & 3, me = (c >> 9) & 3, cs = (c >> 15) & 1, addr = (c >> 16) & 0xffff;
            uint32_t data32 = (uint32_t)(c >> 32);
            if (cs && (me & 1) < 2 && pipe < 4) {
                if (addr >= 0x7 && addr <= 0x9) cs_dim[me & 1][pipe][addr - 7] = data32;
                if (addr == 0xC) wave_pgm[me & 1][pipe] = (wave_pgm[me & 1][pipe] & ~0xffffffffull) | data32;
                else if (addr == 0xD) wave_pgm[me & 1][pipe] = (wave_pgm[me & 1][pipe] & 0xffffffffull) | ((uint64_t)data32 << 32);
            }
            break; }
        case T_REG_INIT: {
            unsigned pipe = (c >> 14) & 3, me = (c >> 16) & 3, type = (c >> 18) & 3; uint32_t data32 = (uint32_t)(c >> 20);
            if (type == 2 && (data32 & 1)) {
                SqttEvent e; e.time = now; e.kind = EventKind::Dispatch; e.me = me; e.pipe = pipe; e.id = data32;
                e.entry_pc = (wave_pgm[me & 1][pipe & 3] << 8) & ((1ull << 48) - 1);
                for (int k = 0; k < 3; k++) e.dim[k] = cs_dim[me & 1][pipe & 3][k];
                e.first_wave = out.waves.size(); e.last_wave = out.waves.size();
                cur_dispatch[me & 1][pipe & 3] = (int)out.events.size();
                out.events.push_back(e);
            }
            break; }
        case T_EVENT: {
            unsigned bop = (c >> 11) & 1, pipe = (c >> 14) & 3, me = (c >> 16) & 3, id = (c >> 18) & 0x3f;
            EventKind k = EventKind::Other;
            switch (id) {
            case 0x7: k = EventKind::CsPartialFlush; break;
            case 0x4: case 0x6: case 0x14: case 0x16: k = EventKind::CacheFlush; break;
            case 0x28: k = EventKind::BottomOfPipe; break;
            case 0x36: k = EventKind::TtFlush; break;
            }
            SqttEvent e; e.time = now; e.kind = k; e.me = me; e.pipe = pipe; e.id = id; e.bop = bop;
            out.events.push_back(e);
            break; }
        case T_MISC: {
            unsigned f = (c >> 16) & 0xff;
            auto push = [&](EventKind k) { SqttEvent e; e.time = now; e.kind = k; out.events.push_back(e); };
            if (f & 0x08) push(EventKind::SaveContext);
            if (f & 0x10) push(EventKind::TtStallBegin);
            if (f & 0x20) push(EventKind::TtStallEnd);
            break; }
        case T_SHADER_DATA: case T_SHADER_DATA_SHORT: {
            bool sh = type == T_SHADER_DATA_SHORT;
            SqttShaderData d; d.time = now; d.shortform = sh;
            if (ver >= 4) {   // header:10 sa:1 simd:2 wgp:4 wave:5 data:32|8 sdt:2
                unsigned sa = (c >> 10) & 1, simd = (c >> 11) & 3, wgp = (c >> 13) & 0xf, wave = (c >> 17) & 0x1f, sdt = (c >> 54) & 3;
                d.value = sh ? (uint32_t)((c >> 22) & 0xff) : (uint32_t)(c >> 22);
                d.cu = (sa << 7) + wgp; d.simd = simd; d.slot = wave; d.priv = sdt != 0;
            } else {          // header:8 sa:1 simd:2 wgp:3 exec:1 wave:5 data:32|8
                unsigned sa = (c >> 8) & 1, simd = (c >> 9) & 3, wgp = (c >> 11) & 7, exec = (c >> 14) & 1, wave = (c >> 15) & 0x1f;
                if (exec && ver > 2) break;
                d.value = sh ? (uint32_t)((c >> 20) & 0xff) : (uint32_t)(c >> 20);
                d.cu = (sa << 7) + wgp; d.simd = simd; d.slot = wave; d.priv = false;
            }
            out.shader_data.push_back(d);
            break; }
        case T_WAVE_START: case T_WAVE_START_EXT: {
            unsigned sa = (c >> 7) & 1, simd = (c >> 8) & 3, count = (c >> 25) & 0x7f, wgp, wid, pipe, me;
            if (ver >= 4) { wgp = (c >> 10) & 0xf; wid = (c >> 15) & 0x1f; pipe = (c >> 20) & 3; me = (c >> 22) & 1; }
            else          { wgp = (c >> 10) & 7;   wid = (c >> 13) & 0x1f; pipe = (c >> 21) & 3; me = (c >> 23) & 1; }
            int cu = (sa << 7) + wgp, loc = (cu << 7) | (simd << 5) | wid;
            if (count >= 66 && count < 90) {   // context save/restore: not a launch
                break;
            }
            uint64_t pc = ((wave_pgm[me & 1][pipe & 3] << 8) & ((1ull << 48) - 1));
            running[loc] = pc;
            SqttWave w; w.se = se; w.cu = cu; w.simd = simd; w.slot = wid; w.begin = now; w.start_pc = pc; w.me = me; w.pipe = pipe;
            run_idx[loc] = {out.waves.size(), now};
            w.dispatch = cur_dispatch[me & 1][pipe & 3];
            if (w.dispatch >= 0) { out.events[w.dispatch].waves_started++; out.events[w.dispatch].last_wave = out.waves.size() + 1; }
            out.waves.push_back(w);
            if (cu == target_sa_wgp && (int)simd == target_simd && wid < 32) {
                flush_slot(wid);
                WaveBuild b; b.ver = ver; b.w = w; b.w.traced = true; b.last_state_cycle = now; b.w.pcs.push_back({0, pc});
                slots[wid].push_back(std::move(b));
            }
            break; }
        case T_WAVE_END: {
            unsigned sa = (c >> 8) & 1, simd = (c >> 9) & 3; unsigned wgp = (c >> (ver >= 4 ? 11 : 11)) & (ver >= 4 ? 0xf : 7), wid = (c >> 15) & 0x1f;
            int cu = (sa << 7) + wgp, loc = (cu << 7) | (simd << 5) | wid;
            if (cu == target_sa_wgp && (int)simd == target_simd && wid < 32 && !slots[wid].empty()) slots[wid].back().complete(now);
            auto it = run_idx.find(loc);
            if (it != run_idx.end()) { out.waves[it->second.first].end = now; out.waves[it->second.first].complete = true; run_idx.erase(it); running.erase(loc); }
            break; }
        case T_INST: {
            unsigned wid, code; bool w64;
            if (ver >= 4) { w64 = (c >> 6) & 1; wid = (c >> 7) & 0x1f; code = (c >> 12) & 0xff; }
            else          { w64 = (c >> 7) & 1; wid = (c >> 8) & 0x1f; code = (c >> 13) & 0x7f; }
            Mapped m = ver >= 4 ? map_inst((int)code, dprate, derate) : ver == 3 ? map_inst11((int)code, dprate, derate) : map_inst10((int)code, dprate, derate);
            if (w64) m.cycles *= 2;   // wave64 issues each instruction over two cycles
            if (m.other_simd) { out.other_simd.push_back({now, m.cat, m.cycles}); break; }
            if (wid < 32 && !slots[wid].empty()) slots[wid].back().inst(now, (int)code, m);
            break; }
        case T_VALU_INST: { unsigned wid = (c >> 7) & 0x1f; bool w64 = (c >> 6) & 1; if (!slots[wid].empty()) slots[wid].back().valu(now, w64); break; }
        case T_IMM_ONE: { unsigned wid = (c >> 7) & 0x1f; if (!slots[wid].empty()) slots[wid].back().immediate(now); break; }
        case T_IMMEDIATE: { unsigned mask = (c >> 8) & 0xffff; for (int i = 0; i < 16; i++) if ((mask >> i) & 1 && !slots[i].empty()) slots[i].back().immediate(now); break; }
        case T_WAVE_READY: { unsigned mask = (c >> 8) & 0xffff; for (int i = 0; i < 16; i++) if ((mask >> i) & 1 && !slots[i].empty()) slots[i].back().wave_ready(now); break; }
        case T_NEW_PC: {
            unsigned wave; uint64_t pc;
            if (ver >= 4) { wave = (c >> 3) & 0x1f; pc = (c >> 8) & ((1ull << 55) - 1); }
            else          { wave = (c >> 11) & 0x1f; pc = (c >> 16) & ((1ull << 46) - 1); }
            if (wave < 32 && !slots[wave].empty()) slots[wave].back().new_pc(now, pc);
            break; }
        case T_UNKNOWN: out.unknown_tokens++; break;
        default: break;
        }
    }
    if (!have_header) { if (err) *err = "no SQTT header token"; return false; }
    {
        size_t att = 0; for (auto& w : out.waves) att += w.dispatch >= 0;
        if (att * 2 < out.waves.size()) {
            for (auto& w : out.waves) w.dispatch = -1;   // drop sparse marker attribution, infer instead
            for (auto& e : out.events) if (e.kind == EventKind::Dispatch) { e.waves_started = 0; }
            infer_dispatches(out);
        }
    }
    for (auto& s : slots) for (auto& b : s) traced_done.push_back(std::move(b));
    // merge traced wave data into the all-waves list (match by slot + begin time)
    for (auto& b : traced_done) {
        b.finish();
        for (auto& w : out.waves) {
            if (w.cu == b.w.cu && w.simd == b.w.simd && w.slot == b.w.slot && w.begin == b.w.begin) {
                w.traced = true; w.insts = std::move(b.w.insts); w.pcs = std::move(b.w.pcs);
                w.exec = b.w.exec; w.wait = b.w.wait; w.stall = b.w.stall;
                if (b.done) w.end = b.w.end;
                break;
            }
        }
    }
    return true;
}

void infer_dispatches(SqttDecode& d) {
    std::vector<size_t> order;
    for (size_t i = 0; i < d.waves.size(); i++) if (d.waves[i].complete && d.waves[i].end >= d.waves[i].begin) order.push_back(i);
    std::sort(order.begin(), order.end(), [&](size_t a, size_t b) { return d.waves[a].begin < d.waves[b].begin; });
    // Consecutive dispatches overlap while the first drains, so a long pause in wave launches also starts a new one.
    constexpr int64_t kLaunchGap = 1000;
    int cur = -1; int64_t cur_end = 0, last_begin = 0;
    for (size_t i : order) {
        SqttWave& w = d.waves[i];
        if (cur < 0 || w.begin > cur_end || w.begin - last_begin > kLaunchGap) {
            SqttEvent e; e.time = w.begin; e.kind = EventKind::Dispatch; e.inferred = true; e.id = 0xffffffffu; e.me = w.me; e.pipe = w.pipe;
            e.first_wave = i; e.last_wave = i + 1;
            cur = (int)d.events.size(); d.events.push_back(e); cur_end = w.end;
        }
        w.dispatch = cur; cur_end = std::max(cur_end, w.end); last_begin = w.begin;
        d.events[cur].waves_started++;
        d.events[cur].first_wave = std::min<uint64_t>(d.events[cur].first_wave, i);
        d.events[cur].last_wave = std::max<uint64_t>(d.events[cur].last_wave, i + 1);
    }
}

bool decode_sqtt_gfx12(const uint8_t* data, size_t size, int se, SqttDecode& out, std::string* err) {
    return decode_sqtt(data, size, se, out, err);
}

}  // namespace openrgp
