#pragma once
// Whole-capture analysis built on the native SQTT decoder: occupancy over time, idle gaps, and CSV/JSON export.
#include <iosfwd>
#include <string>
#include <vector>
#include "openrgp/kernels.h"
#include "openrgp/rgp_file.h"
#include "openrgp/sqtt_decode.h"

namespace openrgp {

// Best-effort LLVM -mcpu for the capture's GPU (from the ASIC name), "gfx1201" when unknown.
std::string guess_mcpu(const Profile& p);

// Decode every shader engine of a capture. Returns false (with *err) when no engine could be decoded.
struct CaptureDecode {
    Profile p;
    std::vector<SqttDecode> se;   // one per shader engine that carried data
    std::vector<int> se_index;
};
bool decode_capture(const std::string& file, CaptureDecode& out, std::string* err);

struct OccupancyBin {
    int64_t begin = 0, end = 0;
    double  avg_waves = 0;   // average resident waves in the bin (one shader engine)
    int     peak_waves = 0;
};
// Resident-wave count over time for one shader engine, in bins of `bin` shader-clock cycles.
std::vector<OccupancyBin> occupancy(const SqttDecode& d, int64_t bin);

struct Gap { int64_t begin = 0, end = 0; };
// Periods of at least `min_len` cycles in which no wave is resident (the engine is idle between dispatches).
std::vector<Gap> idle_gaps(const SqttDecode& d, int64_t min_len);

// CSV writers. Each writes a header line first.
void export_waves_csv(const CaptureDecode& c, std::ostream& os);
void export_insts_csv(const CaptureDecode& c, std::ostream& os);   // traced waves only, one row per instruction
void export_dispatches_csv(const std::vector<DispatchRow>& rows, std::ostream& os);
void export_occupancy_csv(const SqttDecode& d, int64_t bin, std::ostream& os);
void export_spm_csv(const Profile& p, std::ostream& os);           // derived SPM counters, one column per counter
// One JSON document: capture info, per-SE totals, dispatches, idle gaps.
void export_json(const CaptureDecode& c, const std::vector<DispatchRow>& rows, std::ostream& os);

}  // namespace openrgp
