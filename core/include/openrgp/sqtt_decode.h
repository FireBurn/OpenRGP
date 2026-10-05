// OpenRGP native SQTT decoder for RDNA4 (GFX12, SQTT 3.x/"tt version 4") traces from Mesa radv.
//
// Turns one shader engine's raw SQTT buffer into waves: when each wave ran, on which CU/SIMD/slot,
// its start PC (so the shader is known), and for waves on the traced SIMD the instruction stream with
// per-instruction timing, stalls and the exec/wait/stall time split.
//
// The bit-level token format follows AMD's public rocprof-trace-decoder sources (MIT licensed):
// https://github.com/ROCm/rocm-systems/tree/develop/projects/rocprof-trace-decoder (re/amd-src keeps a copy).
// This is an independent implementation, not a translation of that code.
#pragma once
#include <cstdint>
#include <string>
#include <vector>

namespace openrgp {

enum class InstCat : uint8_t {
    None = 0, Smem, Salu, Vmem, Flat, Lds, Valu, Jump, Next, Immed, Trap, Msg, Bvh
};
const char* inst_cat_name(InstCat c);

struct WaveInst {
    int64_t time;      // first attempt to issue, shader clock
    InstCat cat;
    int64_t duration;  // includes stall
    int64_t stall;
};

// A start PC (absolute GPU address, 0 if unknown) valid from instruction index `first_inst` on.
struct PcMark { uint64_t first_inst; uint64_t addr; };

struct SqttWave {
    int      se = 0;
    int      cu = 0;      // (sa << 7) | wgp
    int      simd = 0;
    int      slot = 0;
    int64_t  begin = 0, end = 0;
    uint64_t start_pc = 0;   // from COMPUTE_PGM_LO/HI at launch
    uint8_t  me = 0, pipe = 0;
    int      dispatch = -1;     // index into SqttDecode::events of the dispatch this wave belongs to, -1 if unknown
    bool     traced = false;  // true: on the traced SIMD, insts/timeline are populated
    bool     complete = false;
    int64_t  exec = 0, wait = 0, stall = 0;
    std::vector<WaveInst> insts;
    std::vector<PcMark>   pcs;
};

enum class EventKind : uint8_t {
    Dispatch, CsPartialFlush, CacheFlush, BottomOfPipe, TtFlush, SaveContext, TtStallBegin, TtStallEnd, PacketLoss, Other
};
const char* event_kind_name(EventKind k);

// Something the command processor or trace hardware reported, in shader-clock time.
struct SqttEvent {
    int64_t   time = 0;
    EventKind kind = EventKind::Other;
    uint8_t   me = 0, pipe = 0;
    uint32_t  id = 0;            // raw event id, or the REG_INIT payload for dispatches
    bool      bop = false;       // bottom-of-pipe flavoured event
    bool      inferred = false;  // dispatch inferred from wave activity rather than seen as a marker
    uint64_t  entry_pc = 0;      // dispatches: COMPUTE_PGM when the capture recorded it (radv usually does not)
    uint32_t  dim[3] = {0, 0, 0};// dispatches: COMPUTE_NUM_THREAD_X/Y/Z when recorded
    uint32_t  waves_started = 0; // dispatches: waves launched before the next dispatch on the same pipe
    uint64_t  first_wave = 0;    // index range into SqttDecode::waves of the waves attributed to this dispatch
    uint64_t  last_wave = 0;
};

// s_ttracedata / shader data token (a value a shader wrote into the trace).
struct SqttShaderData { int64_t time; uint32_t value; int cu, simd, slot; bool priv, shortform; };

// A memory instruction issued by a wave on a SIMD that is not the traced one (category and issue cycles only).
// Utilisation counter sample (RDNA2/3 only). values follow the token order: RDNA3 spi_busy, vdata0, vdata1, sdata0, sdata1,
// lds0, lds1, exp0, exp1 (4 bits each); RDNA2 spi_busy-or-lds1, vdata0, vdata1, sdata0, sdata1, lds0 (8 bits each).
struct SqttUtilCounter {
    int64_t time = 0;
    int sa = 0, cid = 0, tm = 0;
    std::vector<uint16_t> values;
};

struct SqttOtherSimd { int64_t time; InstCat cat; int cycles; };

struct SqttDecode {
    int      version = 0;       // tt version from the header (4 = GFX12)
    int      target_cu = 0, target_simd = 0;
    int64_t  first_time = 0, last_time = 0;
    uint64_t tokens = 0, unknown_tokens = 0;
    bool     desync = false;     // decoding stopped early because the token stream lost sync
    std::vector<SqttWave> waves;   // every wave seen in this SE (traced ones carry instructions)
    std::vector<SqttEvent> events;
    std::vector<SqttShaderData> shader_data;
    std::vector<SqttUtilCounter> util_counters;
    std::vector<SqttOtherSimd> other_simd;
    int64_t  realtime_frequency = 0, counter_frequency = 0;
    uint64_t save_context_waves = 0;
};

// Fill SqttWave::dispatch for waves without a marker-based dispatch by splitting wave activity into busy periods
// (a dispatch ends when every wave has drained). Appends Dispatch events with inferred = true. Called by
// decode_sqtt_gfx12 automatically when fewer than half of the waves were attributed to marker dispatches.
void infer_dispatches(SqttDecode& d);

// Decode one SE buffer of any supported generation (SQTT version 1-2 RDNA2, 3 RDNA3, 4 RDNA4). Returns false with
// *err set when the stream is not recognised.
bool decode_sqtt(const uint8_t* data, size_t size, int se, SqttDecode& out, std::string* err);
// Historical name for decode_sqtt.
bool decode_sqtt_gfx12(const uint8_t* data, size_t size, int se, SqttDecode& out, std::string* err);

}  // namespace openrgp
