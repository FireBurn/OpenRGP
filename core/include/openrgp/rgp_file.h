// OpenRGP - open-source reimplementation of AMD Radeon GPU Profiler (RGP)
// core container parser for .rgp files (B00P / SQTT format written by Mesa radv).
//
// The on-disk format is specified by the (MIT-licensed) writer in Mesa:
//   src/amd/common/ac_rgp.c  (structs + chunk layout)
//   src/amd/common/ac_sqtt.h (marker structs)
// We re-derive the layout here; no RGP (closed) code is used.
#pragma once
#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <optional>
#include <memory>

namespace openrgp {

// ---------------------------------------------------------------------------
// File header (56 bytes)
// ---------------------------------------------------------------------------
struct FileHeader {
    uint32_t magic;            // 0x50303042 "B00P"
    uint32_t version_major;    // 1
    uint32_t version_minor;    // 6
    uint32_t flags;            // bit0 is_semaphore_queue_timing_etw, bit1 no_queue_semaphore_timestamps
    int32_t  chunk_offset;     // = 56
    int32_t  second, minute, hour, day_in_month, month, year,
            day_in_week, day_in_year, is_daylight_savings;
};
static constexpr uint32_t kMagic = 0x50303042;

// ---------------------------------------------------------------------------
// Chunk types
// ---------------------------------------------------------------------------
enum class ChunkType : uint32_t {
    ASIC_INFO = 0,
    SQTT_DESC = 1,
    SQTT_DATA = 2,
    API_INFO = 3,
    RESERVED = 4,
    QUEUE_EVENT_TIMINGS = 5,
    CLOCK_CALIBRATION = 6,
    CPU_INFO = 7,
    SPM_DB = 8,
    CODE_OBJECT_DATABASE = 9,
    CODE_OBJECT_LOADER_EVENTS = 10,
    PSO_CORRELATION = 11,
    INSTRUMENTATION_TABLE = 12,
    DERIVED_SPM_DB = 128,
};

struct ChunkHeader {
    uint32_t id;               // type:8 | index:8 | reserved:16
    uint16_t minor_version;
    uint16_t major_version;
    int32_t  size_in_bytes;    // includes this header
    int32_t  padding;
    uint32_t type()   const { return id & 0xFF; }
    uint32_t index()  const { return (id >> 8) & 0xFF; }
};

// ---------------------------------------------------------------------------
// CPU info chunk (112 bytes)
// ---------------------------------------------------------------------------
struct CpuInfo {
    char vendor_id[16];
    char processor_brand[48];
    uint32_t reserved[2];
    uint64_t cpu_timestamp_freq;   // 1e9 (ns)
    uint32_t clock_speed;          // MHz
    uint32_t num_logical_cores;
    uint32_t num_physical_cores;
    uint32_t system_ram_size;      // MB
};

// ---------------------------------------------------------------------------
// ASIC info chunk (768 bytes)
// ---------------------------------------------------------------------------
enum class GpuType : int32_t { UNKNOWN=0, INTEGRATED=1, DISCRETE=2, VIRTUAL=3 };
enum class GfxIpLevel : int32_t {
    NONE=0, GFXIP_6=1, GFXIP_7=2, GFXIP_8=3, GFXIP_8_1=4, GFXIP_9=5,
    GFXIP_10_1=7, GFXIP_10_3=9, GFXIP_11_0=0xc, GFXIP_11_5=0xd,
    GFXIP_12=0x10, GFXIP_11_7=0x11
};
enum class MemoryType : uint32_t {
    UNKNOWN=0, DDR=1, DDR2=2, DDR3=3, DDR4=4, DDR5=5,
    GDDR3=0x10, GDDR4=0x11, GDDR5=0x12, GDDR6=0x13,
    HBM=0x20, HBM2=0x21, HBM3=0x22, LPDDR4=0x30, LPDDR5=0x31
};

struct AsicInfo {
    uint64_t flags;
    uint64_t trace_shader_core_clock;  // Hz
    uint64_t trace_memory_clock;       // Hz
    int32_t  device_id;
    int32_t  device_revision_id;
    int32_t  vgprs_per_simd;
    int32_t  sgprs_per_simd;
    int32_t  shader_engines;
    int32_t  compute_unit_per_shader_engine;
    int32_t  simd_per_compute_unit;
    int32_t  wavefronts_per_simd;
    int32_t  minimum_vgpr_alloc;
    int32_t  vgpr_alloc_granularity;
    int32_t  minimum_sgpr_alloc;
    int32_t  sgpr_alloc_granularity;
    int32_t  hardware_contexts;
    GpuType  gpu_type;
    GfxIpLevel gfxip_level;
    int32_t  gpu_index;
    int32_t  gds_size;
    int32_t  gds_per_shader_engine;
    int32_t  ce_ram_size;
    int32_t  ce_ram_size_graphics;
    int32_t  ce_ram_size_compute;
    int32_t  max_number_of_dedicated_cus;
    int64_t  vram_size;
    int32_t  vram_bus_width;
    int32_t  l2_cache_size;
    int32_t  l1_cache_size;
    int32_t  lds_size;
    char     gpu_name[256];
    float    alu_per_clock;
    float    texture_per_clock;
    float    prims_per_clock;
    float    pixels_per_clock;
    uint64_t gpu_timestamp_frequency;
    uint64_t max_shader_core_clock;
    uint64_t max_memory_clock;
    uint32_t memory_ops_per_clock;
    MemoryType memory_chip_type;
    uint32_t lds_granularity;
    uint16_t cu_mask[32][2];
    char     reserved1[128];
    uint32_t active_pixel_packer_mask[4];
    char     reserved2[16];
    uint32_t gl1_cache_size;
    uint32_t instruction_cache_size;
    uint32_t scalar_cache_size;
    uint32_t mall_cache_size;
    char     padding[4];
};

// ---------------------------------------------------------------------------
// API info chunk (560 bytes)
// ---------------------------------------------------------------------------
enum class ApiType : uint32_t { DIRECTX_12=0, VULKAN=1, GENERIC=2, OPENCL=3 };
enum class InstructionTraceMode : uint32_t { DISABLED=0, FULL_FRAME=1, API_PSO=2 };

struct ApiInfo {
    ApiType api_type;
    uint16_t major_version;
    uint16_t minor_version;
    uint32_t profiling_mode;
    uint32_t reserved;
    uint8_t  profiling_mode_data[512];
    InstructionTraceMode instruction_trace_mode;
    uint32_t reserved2;
    uint8_t  instruction_trace_data[8];
};

// ---------------------------------------------------------------------------
// SQTT desc (32 bytes) + data (24-byte header + payload)
// ---------------------------------------------------------------------------
enum class SqttVersion : int32_t {
    NONE=0, V2_2=0x5, V2_3=0x6, V2_4=0x7, V3_2=0xb, V3_3=0xc
};

struct SqttDesc {
    int32_t  shader_engine_index;
    SqttVersion sqtt_version;
    // v1 union
    int16_t  instrumentation_spec_version;
    int16_t  instrumentation_api_version;
    int32_t  compute_unit_index;
};

struct SqttDataRef {
    int32_t offset;   // absolute file offset of payload
    int32_t size;     // payload bytes
};

// ---------------------------------------------------------------------------
// Queue event timings
// ---------------------------------------------------------------------------
struct QueueInfoRecord {
    uint64_t queue_id;
    uint64_t queue_context;
    uint32_t hardware_info;   // queue_type:8 | engine_type:8 | reserved:16
    uint32_t reserved;
};
enum class QueueEventType : uint32_t {
    CMDBUF_SUBMIT=0, SIGNAL_SEMAPHORE=1, WAIT_SEMAPHORE=2, PRESENT=3
};
struct QueueEventRecord {
    QueueEventType event_type;
    uint32_t sqtt_cb_id;
    uint64_t frame_index;
    uint32_t queue_info_index;
    uint32_t submit_sub_index;
    uint64_t api_id;
    uint64_t cpu_timestamp;
    uint64_t gpu_timestamps[2];
};

struct ClockCalibration {
    uint64_t cpu_timestamp;
    uint64_t gpu_timestamp;
};

// ---------------------------------------------------------------------------
// Code object database
// ---------------------------------------------------------------------------
struct CodeObjectDbHeader {
    uint32_t offset;
    uint32_t flags;           // = elf gfxip level
    uint32_t size;
    uint32_t record_count;
};
struct CodeObjectRecord {
    uint32_t size;            // size of the ELF blob (aligned to 4)
    size_t   elf_offset;      // absolute file offset of the ELF blob
};

struct LoaderEventRecord {
    uint32_t loader_event_type;   // 0 load, 1 unload
    uint32_t reserved;
    uint64_t base_address;
    uint64_t code_object_hash[2];
    uint64_t time_stamp;
};

struct PsoCorrelationRecord {
    uint64_t api_pso_hash;
    uint64_t pipeline_hash[2];
    char api_level_obj_name[64];
};

// ---------------------------------------------------------------------------
// Derived SPM DB (GFX10+): counter groups/names + double values
// ---------------------------------------------------------------------------
struct DerivedSpmGroup {
    std::string name;
    std::vector<uint32_t> counter_ids;
};
struct DerivedSpmCounter {
    std::string name;
    std::string description;
    uint32_t usage_type;
    std::vector<uint32_t> component_ids;
    std::vector<double> values;
};
struct DerivedSpmComponent {
    std::string name;
    uint32_t usage_type;
    std::vector<double> values;
};
struct DerivedSpmDb {
    uint32_t num_timestamps;
    uint32_t sampling_interval;
    std::vector<uint64_t> timestamps;
    std::vector<DerivedSpmGroup> groups;
    std::vector<DerivedSpmCounter> counters;
    std::vector<DerivedSpmComponent> components;
};

// ---------------------------------------------------------------------------
// Top-level parsed profile
// ---------------------------------------------------------------------------
struct Profile {
    FileHeader header{};
    std::optional<CpuInfo>  cpu;
    std::optional<AsicInfo> asic;
    std::optional<ApiInfo>  api;

    std::vector<SqttDesc>    sqtt_descs;      // per SE
    std::vector<SqttDataRef> sqtt_data;       // per SE (matches sqtt_descs)
    std::vector<const uint8_t*> sqtt_data_ptr;  // pointers into file buffer

    CodeObjectDbHeader code_object_db{};
    std::vector<CodeObjectRecord> code_objects;
    std::vector<LoaderEventRecord> loader_events;
    std::vector<PsoCorrelationRecord> pso_correlation;

    std::vector<QueueInfoRecord>  queue_info;
    std::vector<QueueEventRecord> queue_events;
    std::vector<ClockCalibration> clock_calibration;

    std::optional<DerivedSpmDb> derived_spm;

    std::string container = "B00P";   // "B00P" (radv/RGP 1.x) or "AMD_RDF" (Radeon Data File)
    std::vector<std::string> rdf_chunks; // RDF: chunk identifiers in file order (for inspection)
    int rdf_api_raw = -1, rdf_api_version = -1;

    // raw file buffer (kept alive for pointers above)
    std::vector<uint8_t> buffer;
    std::string path;

    // convenience
    bool valid() const { return header.magic == kMagic; }
    const AsicInfo* gpu() const { return asic ? &*asic : nullptr; }
};

// ---------------------------------------------------------------------------
// Parser
// ---------------------------------------------------------------------------
class RgpFile {
public:
    static bool load(const std::string& path, Profile& out, std::string* err = nullptr);
    static bool load(const uint8_t* data, size_t size, Profile& out, std::string* err = nullptr);

private:
    static bool parse(const uint8_t* data, size_t size, Profile& out, std::string* err);
    static bool parse_rdf(Profile& out, std::string* err);   // AMD_RDF container (Radeon Data File, spec version 3)
};

// Human-readable summary of a profile (for CLI/GUI).
struct ProfileSummary {
    std::string gpu_name;
    std::string cpu_name;
    std::string vendor;
    std::string api;
    int shader_engines = 0, cu_per_se = 0, simd_per_cu = 0, waves_per_simd = 0;
    int vgprs_per_simd = 0, sgprs_per_simd = 0;
    uint64_t sclk_hz = 0, mclk_hz = 0;
    int num_se_traces = 0;
    size_t total_sqtt_bytes = 0;
    int num_code_objects = 0;
    int num_loader_events = 0;
    int num_pso = 0;
    int num_queue_events = 0;
    bool has_derived_spm = false;
    int spm_counter_count = 0;
    std::string capture_time;   // formatted
};
ProfileSummary summarize(const Profile& p);

} // namespace openrgp
