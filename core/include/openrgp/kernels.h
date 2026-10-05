// Kernel identification and per-kernel statistics for radv .rgp captures.
//
// radv's SQTT streams carry no usable wave start PC, so a wave's shader is recovered by walking each code
// object's disassembly along the wave's traced instruction categories (taken/not-taken branches pick the
// path). Exactly one code object normally survives. Disassembly comes from llvm-objdump (gfx1201 capable).
#pragma once
#include "openrgp/rgp_file.h"
#include "openrgp/sqtt_decode.h"
#include <array>
#include <map>
#include <string>
#include <vector>

namespace openrgp {

struct IsaInst {
    uint32_t off = 0, size = 0;
    int      cls = 0;             // InstCat value, or one of the Cls* markers below
    int      target = -1;         // branch target as an instruction index, -1 if none
    std::string text;
};
enum : int { ClsSkip = -1, ClsCondBranch = -2, ClsEnd = -3, ClsEither = -4 /* traced as VALU or as IMMED */ };

struct CodeObjectIsa {
    std::vector<IsaInst> ins;
    std::vector<int> starts;      // instruction indices of function symbols (a wave may start at any of them)
    std::vector<std::string> start_names;
    std::string sig;              // stable hash of the disassembly (same shader in different captures = same sig)
    std::string name;             // first symbol
    int wmma = 0, dot4 = 0, exp = 0, ds = 0, mixfma = 0, permute = 0;
};

// Disassemble every code object in the profile. Needs llvm-objdump; `mcpu` e.g. "gfx1201".
bool load_isa(const Profile& p, const std::string& mcpu, std::vector<CodeObjectIsa>& out, std::string* err);

// Walk `isa` along the traced categories. Returns how many trace entries were consumed consistently.
size_t walk_trace(const CodeObjectIsa& isa, const std::vector<InstCat>& trace, std::vector<int>* path = nullptr, size_t start = 0);
// Best walk over every start symbol of the code object; returns consumed count, start index via *start_idx.
size_t walk_best(const CodeObjectIsa& isa, const std::vector<InstCat>& trace, size_t* start_idx = nullptr);

// Result of matching one wave trace against all code objects. `trace` is what was actually walked (the input, or the
// wave64-collapsed form when `collapsed`); `consumed` counts its entries that fit the ISA path.
struct Match {
    int co = -1; size_t start = 0, consumed = 0; bool collapsed = false; std::vector<InstCat> trace;
    bool ok() const { return co >= 0 && consumed * 10 >= trace.size() * 8; }
};
Match best_match(const std::vector<CodeObjectIsa>& isa, const std::vector<InstCat>& trace);

// `start` is the instruction index the walk began at; it picks the stage of multi-stage code objects.
std::string kernel_label(const CodeObjectIsa& c, size_t start = (size_t)-1);
std::string kernel_sig(const CodeObjectIsa& c, size_t start);

struct KernelStats {
    std::string sig, label;
    uint64_t waves = 0, wave_cycles = 0, exec = 0, wait = 0, stall = 0, insts = 0;
    std::vector<int64_t> spans;
    std::map<std::string, std::array<uint64_t, 3>> by_mnemonic;   // mnemonic -> {count, cycles, stall cycles}
    std::vector<int> captures;
};

// Decode every SE of every file, identify kernels and aggregate. `with_mnemonics` also attributes cycles to
// instructions (slower).
bool analyze_captures(const std::vector<std::string>& files, const std::string& mcpu, bool with_mnemonics,
                      std::map<std::string, KernelStats>& out, uint64_t* unidentified_waves, std::string* err);

struct DispatchRow {
    int      index = 0;
    int      event = -1;             // index of the dispatch event in SqttDecode::events (what SqttWave::dispatch refers to)
    int64_t  begin = 0, end = 0;     // shader clock
    uint64_t waves = 0, traced = 0;
    bool     inferred = true;
    std::string sig, label;          // kernel of the traced waves (majority), empty if none was traced/identified
    uint32_t dim[3] = {0, 0, 0};
};
// Dispatch table of one shader engine of one capture (all SEs run every dispatch, so SE 0 is representative;
// pass another index to use that SE's traced WGP instead).
bool analyze_dispatches(const std::string& file, const std::string& mcpu, int se, std::vector<DispatchRow>& out, std::string* err);

}  // namespace openrgp
