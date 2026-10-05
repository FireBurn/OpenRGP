// AMD_RDF ("Radeon Data File") container reader.
// Format: github.com/GPUOpen-Drivers/libamdrdf docs/specification.md (32 byte header, data chunks, 64 byte index entries).
// RGP 2.x profiles use it with chunk names AsicInfo, ApiInfo, ClockCalibration, CodeObject, COLoadEvent,
// PsoCorrelation, SqttData and SpmSession/SpmCounterData. The payload structs match the radv .rgp ones.
#include "openrgp/rgp_file.h"

#include <cstddef>
#include <cstring>
#include <algorithm>
#ifdef OPENRGP_HAVE_ZSTD
#include <zstd.h>
#endif

namespace openrgp {
namespace {
uint32_t u32(const uint8_t* p) { uint32_t v; std::memcpy(&v, p, 4); return v; }
int64_t  i64(const uint8_t* p) { int64_t v; std::memcpy(&v, p, 8); return v; }
uint64_t u64(const uint8_t* p) { uint64_t v; std::memcpy(&v, p, 8); return v; }

struct IndexEntry {
    std::string id; uint8_t compression; uint32_t version;
    int64_t hdr_off, hdr_size, data_off, data_size, unc_size;
};
}  // namespace

bool RgpFile::parse_rdf(Profile& out, std::string* err) {
    auto fail = [&](const std::string& m) { if (err) *err = m; return false; };
    const size_t file_size = out.buffer.size();
    if (file_size < 32) return fail("file too small");
    const uint8_t* b = out.buffer.data();
    uint32_t version = u32(b + 8);
    int64_t idx_off = i64(b + 16), idx_size = i64(b + 24);
    if (version != 3) return fail("unsupported RDF version " + std::to_string(version));
    if (idx_off < 32 || idx_size < 0 || idx_size % 64 || (uint64_t)idx_off + (uint64_t)idx_size > file_size) return fail("bad RDF chunk index");

    std::vector<IndexEntry> entries;
    size_t extra = 0;
    for (int64_t i = 0; i < idx_size / 64; i++) {
        const uint8_t* e = b + idx_off + i * 64;
        IndexEntry x;
        size_t n = 0; while (n < 16 && e[n]) n++;
        x.id.assign((const char*)e, n);
        x.compression = e[16]; x.version = u32(e + 20);
        x.hdr_off = i64(e + 24); x.hdr_size = i64(e + 32); x.data_off = i64(e + 40); x.data_size = i64(e + 48); x.unc_size = i64(e + 56);
        if (x.hdr_off < 0 || x.hdr_size < 0 || x.data_off < 0 || x.data_size < 0 ||
            (uint64_t)x.hdr_off + (uint64_t)x.hdr_size > file_size || (uint64_t)x.data_off + (uint64_t)x.data_size > file_size)
            return fail("RDF chunk " + x.id + " lies outside the file");
        if (x.compression == 1) extra += (size_t)x.unc_size;
        else if (x.compression != 0) return fail("unknown RDF compression " + std::to_string(x.compression));
        entries.push_back(x);
    }

    // Decompressed chunks live after the file bytes in the same buffer, so every pointer stays valid.
    if (extra) {
#ifdef OPENRGP_HAVE_ZSTD
        out.buffer.resize(file_size + extra);
        b = out.buffer.data();
#else
        return fail("file has Zstd compressed chunks but OpenRGP was built without libzstd");
#endif
    }
    size_t tail = file_size;
    auto chunk = [&](const IndexEntry& x, const uint8_t*& data, size_t& size) -> bool {
        if (x.compression == 0) { data = b + x.data_off; size = (size_t)x.data_size; return true; }
#ifdef OPENRGP_HAVE_ZSTD
        size_t r = ZSTD_decompress(out.buffer.data() + tail, (size_t)x.unc_size, b + x.data_off, (size_t)x.data_size);
        if (ZSTD_isError(r)) return false;
        data = out.buffer.data() + tail; size = r; tail += (size_t)x.unc_size;
        return true;
#else
        return false;
#endif
    };
    auto offset_of = [&](const uint8_t* d) { return (size_t)(d - out.buffer.data()); };

    out.header.magic = kMagic; out.header.version_major = 1; out.header.version_minor = 6;
    out.container = "AMD_RDF";

    std::vector<uint64_t> spm_ts;
    std::vector<std::pair<uint32_t, DerivedSpmGroup>> spm_groups;
    std::vector<std::pair<uint32_t, DerivedSpmCounter>> spm_counters;
    for (auto& x : entries) {
        out.rdf_chunks.push_back(x.id);
        const uint8_t* d; size_t n;
        if (!chunk(x, d, n)) return fail("cannot read RDF chunk " + x.id);
        const uint8_t* h = b + x.hdr_off; size_t hs = (size_t)x.hdr_size;

        if (x.id == "AsicInfo") {
            // RDF layout = radv layout with gpu_timestamp_frequency/max clocks moved right after the trace clocks and the
            // two reserved blocks removed (608 bytes instead of 752).
            AsicInfo a; std::memset(&a, 0, sizeof a);
            auto* dst = (uint8_t*)&a; size_t pos = 0;
            auto take = [&](size_t to, size_t len) { if (pos + len <= n) std::memcpy(dst + to, d + pos, len); pos += len; };
            take(offsetof(AsicInfo, flags), 24);                                                             // flags, sclk, mclk
            take(offsetof(AsicInfo, gpu_timestamp_frequency), 24);                                           // ts freq, max sclk, max mclk
            take(offsetof(AsicInfo, device_id), offsetof(AsicInfo, gpu_timestamp_frequency) - offsetof(AsicInfo, device_id));
            take(offsetof(AsicInfo, memory_ops_per_clock), offsetof(AsicInfo, reserved1) - offsetof(AsicInfo, memory_ops_per_clock));
            take(offsetof(AsicInfo, active_pixel_packer_mask), offsetof(AsicInfo, reserved2) - offsetof(AsicInfo, active_pixel_packer_mask));
            take(offsetof(AsicInfo, gl1_cache_size), n > pos ? n - pos : 0);
            out.asic = a;
        } else if (x.id == "ApiInfo" && n >= 8) {
            ApiInfo a; std::memset(&a, 0, sizeof a);
            out.rdf_api_raw = (int)u32(d); out.rdf_api_version = (int)u32(d + 4);
            // RDF numbers APIs differently from the radv format; (3, 12) is DirectX 12 in RGP's own sample.
            a.api_type = (out.rdf_api_raw == 3 && out.rdf_api_version == 12) ? ApiType::DIRECTX_12 : ApiType::GENERIC;
            out.api = a;
        } else if (x.id == "ClockCalibration" && n >= 24) {
            for (size_t o = 0; o + 24 <= n; o += 24) { ClockCalibration c; c.cpu_timestamp = u64(d + o + 8); c.gpu_timestamp = u64(d + o + 16); out.clock_calibration.push_back(c); }
        } else if (x.id == "CodeObject") {
            CodeObjectRecord r; r.size = (uint32_t)n; r.elf_offset = offset_of(d);
            out.code_objects.push_back(r);
            out.code_object_db.record_count++;
        } else if (x.id == "COLoadEvent" && hs >= 4) {
            uint32_t cnt = u32(h);
            for (uint32_t i = 0; i < cnt && (size_t)(i + 1) * 40 <= n; i++) {
                const uint8_t* r = d + i * 40; LoaderEventRecord e;
                e.loader_event_type = u32(r) & 0xffff; e.reserved = u32(r + 4); e.base_address = u64(r + 8);
                e.code_object_hash[0] = u64(r + 16); e.code_object_hash[1] = u64(r + 24); e.time_stamp = u64(r + 32);
                out.loader_events.push_back(e);
            }
        } else if (x.id == "PsoCorrelation" && hs >= 4) {
            uint32_t cnt = u32(h);
            for (uint32_t i = 0; i < cnt && (size_t)(i + 1) * 96 <= n; i++) {
                const uint8_t* r = d + i * 96; PsoCorrelationRecord e; std::memset(&e, 0, sizeof e);
                e.api_pso_hash = u64(r + 8); e.pipeline_hash[0] = u64(r + 16); e.pipeline_hash[1] = u64(r + 24);
                std::memcpy(e.api_level_obj_name, r + 32, 64); e.api_level_obj_name[63] = 0;
                out.pso_correlation.push_back(e);
            }
        } else if (x.id == "SqttData" && hs >= 12) {
            SqttDesc sd; std::memset(&sd, 0, sizeof sd);
            sd.shader_engine_index = (int32_t)u32(h + 4); sd.sqtt_version = (SqttVersion)(int32_t)u32(h + 8);
            out.sqtt_descs.push_back(sd);
            SqttDataRef dr; dr.offset = (int32_t)offset_of(d); dr.size = (int32_t)n;
            out.sqtt_data.push_back(dr); out.sqtt_data_ptr.push_back(d);
        }
        else if (x.id == "SpmSession" && hs >= 20) {
            spm_ts.assign(n / 8, 0);
            for (size_t i = 0; i < spm_ts.size(); i++) spm_ts[i] = u64(d + i * 8);
        } else if (x.id == "DerivedSpmGroup" && hs >= 20) {
            // header: {0, index, counter count, name length, 0}; data: counter indices then the name
            uint32_t idx = u32(h + 4), cnt = u32(h + 8), nl = u32(h + 12);
            if ((size_t)cnt * 4 + nl > n) continue;
            DerivedSpmGroup g; for (uint32_t i = 0; i < cnt; i++) g.counter_ids.push_back(u32(d + i * 4));
            g.name.assign((const char*)d + cnt * 4, nl);
            spm_groups.push_back({idx, std::move(g)});
        } else if (x.id == "DerivedSpmCtr" && hs >= 24) {
            // header: {0, index, component count, usage, name length, description length};
            // data: one double per timestamp, component indices (u32), name, description
            uint32_t idx = u32(h + 4), ncomp = u32(h + 8), usage = u32(h + 12), nl = u32(h + 16), dl = u32(h + 20);
            size_t tail_len = (size_t)ncomp * 4 + nl + dl;
            if (tail_len > n) continue;
            size_t nv = (n - tail_len) / 8;
            DerivedSpmCounter c; c.usage_type = usage;
            c.values.resize(nv); std::memcpy(c.values.data(), d, nv * 8);
            const uint8_t* t = d + nv * 8;
            for (uint32_t i = 0; i < ncomp; i++) c.component_ids.push_back(u32(t + i * 4));
            c.name.assign((const char*)t + ncomp * 4, nl);
            c.description.assign((const char*)t + ncomp * 4 + nl, dl);
            spm_counters.push_back({idx, std::move(c)});
        }
    }
    if (!spm_counters.empty()) {
        std::sort(spm_counters.begin(), spm_counters.end(), [](auto& a, auto& b) { return a.first < b.first; });
        std::sort(spm_groups.begin(), spm_groups.end(), [](auto& a, auto& b) { return a.first < b.first; });
        DerivedSpmDb db{}; db.num_timestamps = (uint32_t)spm_ts.size(); db.timestamps = spm_ts;
        if (spm_ts.size() > 2) {   // the file stores no interval: report the median step between samples
            std::vector<uint64_t> dl; for (size_t i = 1; i < spm_ts.size(); i++) dl.push_back(spm_ts[i] - spm_ts[i - 1]);
            std::nth_element(dl.begin(), dl.begin() + dl.size() / 2, dl.end()); db.sampling_interval = (uint32_t)dl[dl.size() / 2];
        }
        for (auto& c : spm_counters) db.counters.push_back(std::move(c.second));
        for (auto& g : spm_groups) db.groups.push_back(std::move(g.second));
        out.derived_spm = std::move(db);
    }
    if (out.sqtt_descs.empty()) return fail("RDF file has no SqttData chunks");
    return true;
}

}  // namespace openrgp
