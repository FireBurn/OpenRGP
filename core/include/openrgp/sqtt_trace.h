// OpenRGP - SQTT 3.x thread-trace tokenizer.
//
// Faithful reimplementation of the token loop in AMD's closed RGP
// (function AdvanceParser2X in RadeonGPUProfiler, decompiled with Ghidra).
// The on-disk raw trace format is produced by hardware (SQTT 3.3 on GFX12)
// and written by Mesa radv; RGP's parser is the reference decoder. We
// re-implement the same state machine from the decompiled logic.
//
// SQTT 3.x stream: sequence of 16-bit words. `pos` advances in word units;
// a 16-bit header at an odd pos is bit-packed across two words.
#pragma once
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>

namespace openrgp {

// Token type mapping table (RGP .rodata CSWTCH_421): entry-type -> token-type
extern const uint32_t kSqttTokenTypeMap[16];
// Position-advance table (RGP .rodata CSWTCH_425): entry-type -> words to advance
extern const uint32_t kSqttTokenAdvance[16];

// Parsed SQTT token (field offsets mirror RGP's RgpSqttToken).
struct SqttToken {
    uint32_t type = 0;        // +0x00 token type (mapped)
    uint64_t timestamp = 0;   // +0x08
    uint32_t position = 0;    // +0x10 (pos + bias)
    uint32_t se = 0;          // +0x18 (low)  logical shader engine
    uint32_t f1c = 0;         // +0x1c
    uint32_t f20 = 0;         // +0x20
    uint32_t f24 = 0;         // +0x24
    uint32_t f28 = 0;         // +0x28
    uint32_t f2c = 0;         // +0x2c
    uint32_t f30 = 0;         // +0x30 (low)
    uint32_t f34 = 0;         // +0x34
    uint32_t f38 = 0;         // +0x38
    uint32_t f3c = 0;         // +0x3c
    uint32_t f40 = 0;         // +0x40
    // raw 16-bit header for this token
    uint16_t header = 0;
    // A hardware THREAD_TRACE_MARKER (0x35) event: entry types 7/8/9 (all map
    // to token type 7) with the marker flag set. Note: f34 at offset 0x34 has
    // type-specific meaning; only for type 7 does it indicate a marker.
    bool is_marker() const { return type == 7 && f34 != 0; }
};

// Parser state (offsets mirror RGP's RgpSqttParser).
struct SqttParser {
    const uint8_t* data = nullptr;  // +0x88
    uint32_t size = 0;              // +0x90
    uint32_t pos = 0;               // +0x94
    uint32_t bias = 0;              // +0x9c
    uint32_t se = 0;                // +0xa0
    uint32_t major = 0;             // +0xa4  (2 or 3)
    uint32_t minor = 0;             // +0xa8
    uint32_t version = 0;           // +0xac  (6..0x11)
    uint32_t ctx_regs = 0;          // +0xb0
    uint64_t acc = 0;               // +0x18 accumulated
    uint64_t ts_delta = 0;          // +0x20
    uint32_t ts_ready = 0;          // +0x28

    bool init(const uint8_t* d, uint32_t sz, uint32_t bias_, uint32_t se_,
              uint32_t major_, uint32_t minor_, uint32_t ver_);
    // Advance one token. Returns false when the stream is exhausted/invalid.
    bool advance(SqttToken& out);
    bool at_end() const { return pos >= size; }
};

// Decode the whole per-SE trace into a token list.
std::vector<SqttToken> tokenize(const uint8_t* data, uint32_t size,
                                uint32_t se, uint32_t major, uint32_t minor, uint32_t version);

// Instruction-type -> size in dwords (RgpSqttGetSizeFromInstructionType)
inline uint32_t instTypeSize(uint32_t t){ return (t > 19) ? 8 : 4; }

} // namespace openrgp
