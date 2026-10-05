#include "openrgp/rgp_file.h"
#include <cstring>
#include <fstream>
#include <sstream>
#include <ctime>

namespace openrgp {

namespace {
// little-endian readers
template <class T> T rd(const uint8_t* p) { T v; std::memcpy(&v, p, sizeof(T)); return v; }
uint16_t rd16(const uint8_t* p){ return rd<uint16_t>(p); }
uint32_t rd32(const uint8_t* p){ return rd<uint32_t>(p); }
int32_t  rd32s(const uint8_t* p){ return rd<int32_t>(p); }
uint64_t rd64(const uint8_t* p){ return rd<uint64_t>(p); }
int64_t  rd64s(const uint8_t* p){ return rd<int64_t>(p); }

bool in_range(size_t off, size_t n, size_t size){ return off + n <= size; }

void copy_str(char* dst, size_t cap, const uint8_t* src, size_t len){
    size_t n = len < cap-1 ? len : cap-1;
    std::memcpy(dst, src, n); dst[n] = 0;
    // stop at first NUL (fixed-width fields are NUL padded), then trim trailing
    // whitespace (Mesa copies /proc/cpuinfo values verbatim, incl. '\n')
    while(n>0 && dst[n-1]=='\0') n--;
    while(n>0 && (dst[n-1]=='\n'||dst[n-1]=='\r'||dst[n-1]==' '||dst[n-1]=='\t')) n--;
    dst[n] = 0;
}
} // namespace

bool RgpFile::load(const std::string& path, Profile& out, std::string* err){
    std::ifstream f(path, std::ios::binary);
    if(!f) { if(err) *err = "cannot open "+path; return false; }
    std::vector<uint8_t> buf((std::istreambuf_iterator<char>(f)), std::istreambuf_iterator<char>());
    out.path = path;
    return load(buf.data(), buf.size(), out, err);
}

bool RgpFile::load(const uint8_t* data, size_t size, Profile& out, std::string* err){
    out.buffer.assign(data, data+size);
    if(size >= 8 && std::memcmp(data, "AMD_RDF ", 8) == 0) return parse_rdf(out, err);
    return parse(out.buffer.data(), out.buffer.size(), out, err);
}

bool RgpFile::parse(const uint8_t* data, size_t size, Profile& out, std::string* err){
    auto fail = [&](const std::string& m){ if(err) *err = m; return false; };
    if(size < sizeof(FileHeader)) return fail("file too small");
    std::memcpy(&out.header, data, sizeof(FileHeader));
    if(out.header.magic != kMagic) return fail("bad magic (not B00P)");
    if(out.header.version_major != 1) return fail("unsupported major version");

    size_t off = (size_t)out.header.chunk_offset;
    while(off + sizeof(ChunkHeader) <= size){
        ChunkHeader ch; std::memcpy(&ch, data+off, sizeof(ch));
        auto ct = (ChunkType)ch.type();
        size_t cend = off + (size_t)ch.size_in_bytes;
        if(ch.size_in_bytes <= 0 || cend > size) return fail("bad chunk size");
        const uint8_t* b = data + off;

        switch(ct){
        case ChunkType::CPU_INFO: {
            if(ch.size_in_bytes < (int32_t)sizeof(CpuInfo)) break;
            CpuInfo c;
            copy_str(c.vendor_id, sizeof(c.vendor_id), b+16, 16);
            copy_str(c.processor_brand, sizeof(c.processor_brand), b+32, 48);
            std::memcpy(c.reserved, b+80, 8);
            c.cpu_timestamp_freq = rd64(b+88);
            c.clock_speed = rd32(b+96);
            c.num_logical_cores = rd32(b+100);
            c.num_physical_cores = rd32(b+104);
            c.system_ram_size = rd32(b+108);
            out.cpu = c;
            break;
        }
        case ChunkType::ASIC_INFO: {
            if(ch.size_in_bytes < (int32_t)sizeof(AsicInfo)) break;
            AsicInfo a;
            size_t p = 16;
            a.flags = rd64(b+p); p+=8;
            a.trace_shader_core_clock = rd64(b+p); p+=8;
            a.trace_memory_clock = rd64(b+p); p+=8;
            a.device_id = rd32s(b+p); p+=4;
            a.device_revision_id = rd32s(b+p); p+=4;
            a.vgprs_per_simd = rd32s(b+p); p+=4;
            a.sgprs_per_simd = rd32s(b+p); p+=4;
            a.shader_engines = rd32s(b+p); p+=4;
            a.compute_unit_per_shader_engine = rd32s(b+p); p+=4;
            a.simd_per_compute_unit = rd32s(b+p); p+=4;
            a.wavefronts_per_simd = rd32s(b+p); p+=4;
            a.minimum_vgpr_alloc = rd32s(b+p); p+=4;
            a.vgpr_alloc_granularity = rd32s(b+p); p+=4;
            a.minimum_sgpr_alloc = rd32s(b+p); p+=4;
            a.sgpr_alloc_granularity = rd32s(b+p); p+=4;
            a.hardware_contexts = rd32s(b+p); p+=4;
            a.gpu_type = (GpuType)rd32s(b+p); p+=4;
            a.gfxip_level = (GfxIpLevel)rd32s(b+p); p+=4;
            a.gpu_index = rd32s(b+p); p+=4;
            a.gds_size = rd32s(b+p); p+=4;
            a.gds_per_shader_engine = rd32s(b+p); p+=4;
            a.ce_ram_size = rd32s(b+p); p+=4;
            a.ce_ram_size_graphics = rd32s(b+p); p+=4;
            a.ce_ram_size_compute = rd32s(b+p); p+=4;
            a.max_number_of_dedicated_cus = rd32s(b+p); p+=4;
            a.vram_size = rd64s(b+p); p+=8;
            a.vram_bus_width = rd32s(b+p); p+=4;
            a.l2_cache_size = rd32s(b+p); p+=4;
            a.l1_cache_size = rd32s(b+p); p+=4;
            a.lds_size = rd32s(b+p); p+=4;
            copy_str(a.gpu_name, sizeof(a.gpu_name), b+p, 256); p+=256;
            std::memcpy(&a.alu_per_clock, b+p, 4); p+=4;
            std::memcpy(&a.texture_per_clock, b+p, 4); p+=4;
            std::memcpy(&a.prims_per_clock, b+p, 4); p+=4;
            std::memcpy(&a.pixels_per_clock, b+p, 4); p+=4;
            a.gpu_timestamp_frequency = rd64(b+p); p+=8;
            a.max_shader_core_clock = rd64(b+p); p+=8;
            a.max_memory_clock = rd64(b+p); p+=8;
            a.memory_ops_per_clock = rd32(b+p); p+=4;
            a.memory_chip_type = (MemoryType)rd32(b+p); p+=4;
            a.lds_granularity = rd32(b+p); p+=4;
            std::memcpy(a.cu_mask, b+p, sizeof(a.cu_mask)); p+=sizeof(a.cu_mask);
            std::memcpy(a.reserved1, b+p, sizeof(a.reserved1)); p+=sizeof(a.reserved1);
            std::memcpy(a.active_pixel_packer_mask, b+p, 16); p+=16;
            std::memcpy(a.reserved2, b+p, 16); p+=16;
            a.gl1_cache_size = rd32(b+p); p+=4;
            a.instruction_cache_size = rd32(b+p); p+=4;
            a.scalar_cache_size = rd32(b+p); p+=4;
            a.mall_cache_size = rd32(b+p); p+=4;
            out.asic = a;
            break;
        }
        case ChunkType::API_INFO: {
            if(ch.size_in_bytes < (int32_t)sizeof(ApiInfo)) break;
            ApiInfo a;
            size_t p = 16;
            a.api_type = (ApiType)rd32(b+p); p+=4;
            a.major_version = rd16(b+p); p+=2;
            a.minor_version = rd16(b+p); p+=2;
            a.profiling_mode = rd32(b+p); p+=4;
            a.reserved = rd32(b+p); p+=4;
            std::memcpy(a.profiling_mode_data, b+p, 512); p+=512;
            a.instruction_trace_mode = (InstructionTraceMode)rd32(b+p); p+=4;
            a.reserved2 = rd32(b+p); p+=4;
            std::memcpy(a.instruction_trace_data, b+p, 8); p+=8;
            out.api = a;
            break;
        }
        case ChunkType::CODE_OBJECT_DATABASE: {
            CodeObjectDbHeader h;
            h.offset = rd32(b+16); h.flags = rd32(b+20); h.size = rd32(b+24); h.record_count = rd32(b+28);
            out.code_object_db = h;
            // records: each is { u32 size } followed by the ELF blob (size bytes, aligned 4)
            size_t rp = off + 32;
            for(uint32_t i=0;i<h.record_count && rp+4 <= size;i++){
                uint32_t esz = rd32(data+rp);
                size_t elf_off = rp + 4;
                out.code_objects.push_back({esz, elf_off});
                rp = elf_off + ((esz + 3) & ~3u);
            }
            break;
        }
        case ChunkType::CODE_OBJECT_LOADER_EVENTS: {
            uint32_t off_f = rd32(b+16), flags = rd32(b+20), recsz = rd32(b+24), recnt = rd32(b+28);
            size_t rp = off + 32;
            for(uint32_t i=0;i<recnt && rp+40 <= size;i++){
                LoaderEventRecord r{};
                r.loader_event_type = rd32(data+rp);
                r.reserved = rd32(data+rp+4);
                r.base_address = rd64(data+rp+8);
                r.code_object_hash[0] = rd64(data+rp+16);
                r.code_object_hash[1] = rd64(data+rp+24);
                r.time_stamp = rd64(data+rp+32);
                out.loader_events.push_back(r);
                rp += 40;
            }
            break;
        }
        case ChunkType::PSO_CORRELATION: {
            uint32_t off_f = rd32(b+16), flags = rd32(b+20), recsz = rd32(b+24), recnt = rd32(b+28);
            size_t rp = off + 32;
            for(uint32_t i=0;i<recnt && rp+88 <= size;i++){
                PsoCorrelationRecord r;
                std::memset(&r,0,sizeof(r));
                r.api_pso_hash = rd64(data+rp);
                r.pipeline_hash[0] = rd64(data+rp+8);
                r.pipeline_hash[1] = rd64(data+rp+16);
                copy_str(r.api_level_obj_name, sizeof(r.api_level_obj_name), data+rp+24, 64);
                out.pso_correlation.push_back(r);
                rp += 88;
            }
            break;
        }
        case ChunkType::QUEUE_EVENT_TIMINGS: {
            uint32_t qi_cnt = rd32(b+16), qi_sz = rd32(b+20), qe_cnt = rd32(b+24), qe_sz = rd32(b+28);
            size_t rp = off + 32;
            for(uint32_t i=0;i<qi_cnt && rp+24 <= size;i++){
                QueueInfoRecord r;
                r.queue_id = rd64(data+rp);
                r.queue_context = rd64(data+rp+8);
                r.hardware_info = rd32(data+rp+16);
                r.reserved = rd32(data+rp+20);
                out.queue_info.push_back(r);
                rp += 24;
            }
            for(uint32_t i=0;i<qe_cnt && rp+56 <= size;i++){
                QueueEventRecord r;
                r.event_type = (QueueEventType)rd32(data+rp);
                r.sqtt_cb_id = rd32(data+rp+4);
                r.frame_index = rd64(data+rp+8);
                r.queue_info_index = rd32(data+rp+16);
                r.submit_sub_index = rd32(data+rp+20);
                r.api_id = rd64(data+rp+24);
                r.cpu_timestamp = rd64(data+rp+32);
                r.gpu_timestamps[0] = rd64(data+rp+40);
                r.gpu_timestamps[1] = rd64(data+rp+48);
                out.queue_events.push_back(r);
                rp += 56;
            }
            break;
        }
        case ChunkType::CLOCK_CALIBRATION: {
            // each record is a full 40-byte chunk-header struct
            size_t rp = off;
            while(rp + 40 <= cend){
                ClockCalibration c;
                c.cpu_timestamp = rd64(data+rp+16);
                c.gpu_timestamp = rd64(data+rp+24);
                out.clock_calibration.push_back(c);
                rp += 40;
            }
            break;
        }
        case ChunkType::SQTT_DESC: {
            SqttDesc d;
            d.shader_engine_index = rd32s(b+16);
            d.sqtt_version = (SqttVersion)rd32s(b+20);
            d.instrumentation_spec_version = rd16(b+24);
            d.instrumentation_api_version = rd16(b+26);
            d.compute_unit_index = rd32s(b+28);
            out.sqtt_descs.push_back(d);
            break;
        }
        case ChunkType::SQTT_DATA: {
            SqttDataRef d;
            d.offset = rd32s(b+16);
            d.size = rd32s(b+20);
            out.sqtt_data.push_back(d);
            if((size_t)d.offset + (size_t)d.size <= size){
                out.sqtt_data_ptr.push_back(data + d.offset);
            } else {
                out.sqtt_data_ptr.push_back(nullptr);
            }
            break;
        }
        case ChunkType::DERIVED_SPM_DB: {
            DerivedSpmDb s;
            s.num_timestamps = rd32(b+24);
            s.sampling_interval = rd32(b+40);
            uint32_t num_groups = rd32(b+28);
            uint32_t num_counters = rd32(b+32);
            uint32_t num_components = rd32(b+36);
            size_t rp = off + 44;
            // timestamps
            for(uint32_t i=0;i<s.num_timestamps && rp+8<=size;i++){ s.timestamps.push_back(rd64(data+rp)); rp+=8; }
            // groups
            for(uint32_t i=0;i<num_groups && rp+20<=size;i++){
                uint32_t sz = rd32(data+rp), offg = rd32(data+rp+4), nlen = rd32(data+rp+8),
                       dlen = rd32(data+rp+12), ncnt = rd32(data+rp+16);
                DerivedSpmGroup g;
                g.name.assign((char*)data+rp+offg, nlen);
                size_t cp = rp + offg + nlen + dlen;
                for(uint32_t j=0;j<ncnt;j++){ g.counter_ids.push_back(rd32(data+cp)); cp+=4; }
                s.groups.push_back(std::move(g));
                rp += sz;
            }
            // counters
            for(uint32_t i=0;i<num_counters && rp+28<=size;i++){
                uint32_t sz = rd32(data+rp), offc = rd32(data+rp+4), nlen = rd32(data+rp+8),
                       dlen = rd32(data+rp+12), ncomp = rd32(data+rp+16);
                // struct: size(4) offset(4) name_len(4) desc_len(4) num_components(4) usage(1) + pad(3) = 24
                uint32_t usage = data[rp+20];
                DerivedSpmCounter c;
                c.name.assign((char*)data+rp+offc, nlen);
                c.description.assign((char*)data+rp+offc+nlen, dlen);
                c.usage_type = usage;
                size_t cp = rp + offc + nlen + dlen;
                for(uint32_t j=0;j<ncomp;j++){ c.component_ids.push_back(rd32(data+cp)); cp+=4; }
                s.counters.push_back(std::move(c));
                rp += sz;
            }
            // components
            for(uint32_t i=0;i<num_components && rp+24<=size;i++){
                uint32_t sz = rd32(data+rp), offc = rd32(data+rp+4), nlen = rd32(data+rp+8),
                       dlen = rd32(data+rp+12), usage = rd32(data+rp+16);
                DerivedSpmComponent c;
                c.name.assign((char*)data+rp+offc, nlen);
                c.usage_type = usage;
                s.components.push_back(std::move(c));
                rp += sz;
            }
            // counter values (doubles), then component values
            for(auto& c : s.counters){
                c.values.resize(s.num_timestamps);
                for(uint32_t i=0;i<s.num_timestamps && rp+8<=size;i++){ std::memcpy(&c.values[i], data+rp, 8); rp+=8; }
            }
            for(auto& c : s.components){
                c.values.resize(s.num_timestamps);
                for(uint32_t i=0;i<s.num_timestamps && rp+8<=size;i++){ std::memcpy(&c.values[i], data+rp, 8); rp+=8; }
            }
            out.derived_spm = std::move(s);
            break;
        }
        default:
            break;
        }
        off = cend;
    }
    return true;
}

ProfileSummary summarize(const Profile& p){
    ProfileSummary s;
    if(p.cpu){ s.cpu_name = p.cpu->processor_brand; s.vendor = p.cpu->vendor_id; }
    if(p.asic){
        s.gpu_name = p.asic->gpu_name;
        s.shader_engines = p.asic->shader_engines;
        s.cu_per_se = p.asic->compute_unit_per_shader_engine;
        s.simd_per_cu = p.asic->simd_per_compute_unit;
        s.waves_per_simd = p.asic->wavefronts_per_simd;
        s.vgprs_per_simd = p.asic->vgprs_per_simd;
        s.sgprs_per_simd = p.asic->sgprs_per_simd;
        s.sclk_hz = p.asic->trace_shader_core_clock;
        s.mclk_hz = p.asic->trace_memory_clock;
    }
    if(p.api){
        switch(p.api->api_type){
        case ApiType::VULKAN: s.api="Vulkan"; break;
        case ApiType::DIRECTX_12: s.api="DX12"; break;
        case ApiType::OPENCL: s.api="OpenCL"; break;
        default: s.api="Generic"; break;
        }
    }
    s.num_se_traces = (int)p.sqtt_descs.size();
    for(auto& d : p.sqtt_data) s.total_sqtt_bytes += (size_t)d.size;
    s.num_code_objects = (int)p.code_objects.size();
    s.num_loader_events = (int)p.loader_events.size();
    s.num_pso = (int)p.pso_correlation.size();
    s.num_queue_events = (int)p.queue_events.size();
    s.has_derived_spm = p.derived_spm.has_value();
    if(p.derived_spm) s.spm_counter_count = (int)p.derived_spm->counters.size();
    // capture time
    std::tm tm{};
    tm.tm_sec=p.header.second; tm.tm_min=p.header.minute; tm.tm_hour=p.header.hour;
    tm.tm_mday=p.header.day_in_month; tm.tm_mon=p.header.month; tm.tm_year=p.header.year;
    char buf[32]; std::strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",&tm);
    s.capture_time = buf;
    return s;
}

} // namespace openrgp
