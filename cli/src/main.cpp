// OpenRGP CLI
//   openrgp info   <file.rgp>   profile summary (GPU/CPU/API/traces)
//   openrgp spm    <file.rgp>   derived SPM counters (cache/memory/LDS)
//   openrgp tokens <file.rgp>   SQTT token stream statistics
//   openrgp dump   <file.rgp> [-n N] [-se I]   dump first N tokens of SE I
//   openrgp waves  <file.rgp> [dur-file]       native decode: traced waves with instruction categories
//   openrgp dispatches <file.rgp> [--se N]     dispatch table (inferred from wave activity) with identified kernels
//   openrgp events <file.rgp> [--se N] [-n N]  command-processor events, shader data, other-SIMD instruction counts
//   openrgp kernels <file.rgp>...              identify the shader of every traced wave; per-kernel wave time
//   openrgp cycles  <file.rgp>... [--sig S]    cycles per instruction for one kernel (default: top identified)
#include "openrgp/rgp_file.h"
#include "openrgp/sqtt_trace.h"
#include "openrgp/sqtt_decode.h"
#include "openrgp/kernels.h"
#include "openrgp/analysis.h"
#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <map>
#include <cstdio>

using namespace openrgp;

static void usage(){
    std::cerr <<
      "OpenRGP - open-source Radeon GPU Profiler\n"
      "usage:\n"
      "  openrgp info   <file.rgp>            profile summary\n"
      "  openrgp spm    <file.rgp>            derived SPM counters\n"
      "  openrgp tokens <file.rgp>            SQTT token statistics\n"
      "  openrgp dump   <file.rgp> [-n N] [-se I]   dump tokens\n"
      "  openrgp waves  <file.rgp> [durations-file] every wave (traced waves list their instruction categories)\n"
      "  openrgp dispatches <file.rgp> [--se N] [--mcpu X]   dispatch table with identified kernels\n"
      "  openrgp events <file.rgp> [--se N] [-n N]           command-processor events, shader data\n"
      "  openrgp kernels <file.rgp>... [--mcpu X]            per-kernel wave statistics across captures\n"
      "  openrgp cycles  <file.rgp>... [--sig S]             per-instruction cycle breakdown of one kernel\n"
      "  openrgp occupancy <file.rgp> [--bin N] [--se N]     resident waves over time\n"
      "  openrgp gaps   <file.rgp> [--min N] [--se N]        periods with no resident wave\n"
      "  openrgp export <file.rgp> waves|insts|dispatches|occupancy|spm|json [--se N] [--bin N] [--mcpu X]\n";
}

static bool load(const std::string& path, Profile& p){
    std::string err;
    if(!RgpFile::load(path, p, &err)){ std::cerr << "error: " << err << "\n"; return false; }
    return true;
}

static uint32_t majorOf(SqttVersion v){ return (v>=SqttVersion::V3_2)?3:2; }

int cmd_info(const std::string& path){
    Profile p; if(!load(path,p)) return 1;
    auto s = summarize(p);
    std::cout << "file:        " << p.path << "\n";
    if(p.container == "AMD_RDF") std::cout << "format:      AMD_RDF (" << p.rdf_chunks.size() << " chunks)\n";
    else std::cout << "format:      B00P v" << p.header.version_major << "." << p.header.version_minor
              << (p.header.flags&1?" (semaphore-queue-timing)":"") << "\n";
    std::cout << "captured:    " << (s.capture_time.rfind("1900", 0) == 0 ? std::string("unknown") : s.capture_time) << "\n";
    std::cout << "GPU:         " << s.gpu_name << "\n";
    std::cout << "  topology:  " << s.shader_engines << " SE x " << s.cu_per_se
              << " CU x " << s.simd_per_cu << " SIMD, " << s.waves_per_simd << " wf/SIMD\n";
    std::cout << "  registers: " << s.vgprs_per_simd << " VGPR/SIMD, " << s.sgprs_per_simd << " SGPR/SIMD\n";
    std::cout << "  clocks:    SCLK " << s.sclk_hz/1000000 << " MHz, MCLK " << s.mclk_hz/1000000 << " MHz\n";
    if(p.asic){
        std::cout << "  device:    id=0x" << std::hex << p.asic->device_id << " rev=0x"
                  << p.asic->device_revision_id << std::dec
                  << "  vram=" << (p.asic->vram_size/1024/1024) << " MB\n";
        std::cout << "  caches:    L1=" << p.asic->l1_cache_size << " L2=" << p.asic->l2_cache_size
                  << " LDS=" << p.asic->lds_size << "\n";
    }
    std::cout << "CPU:         " << s.cpu_name << " (" << s.vendor << ")\n";
    if(p.cpu) std::cout << "  cores:     " << p.cpu->num_logical_cores << " logical / "
                        << p.cpu->num_physical_cores << " physical, " << p.cpu->clock_speed << " MHz, "
                        << p.cpu->system_ram_size << " MB RAM\n";
    std::cout << "API:         " << s.api << "\n";
    std::cout << "traces:      " << s.num_se_traces << " SE, " << s.total_sqtt_bytes << " bytes SQTT data\n";
    std::cout << "code objs:   " << s.num_code_objects << "  loader events: " << s.num_loader_events
              << "  PSO: " << s.num_pso << "  queue events: " << s.num_queue_events << "\n";
    std::cout << "derived SPM: " << (s.has_derived_spm?"yes":"no")
              << (s.has_derived_spm?" ("+std::to_string(s.spm_counter_count)+" counters)":"") << "\n";
    return 0;
}

int cmd_spm(const std::string& path){
    Profile p; if(!load(path,p)) return 1;
    if(!p.derived_spm){ std::cerr << "no derived SPM data\n"; return 1; }
    auto& s = *p.derived_spm;
    std::cout << "derived SPM: " << s.timestamps.size() << " samples, interval=" << s.sampling_interval << "\n";
    // group -> counters
    for(auto& g : s.groups){
        std::cout << "\n[" << g.name << "]\n";
        for(uint32_t cid : g.counter_ids){
            if(cid >= s.counters.size()) continue;
            auto& c = s.counters[cid];
            double sum=0, mn=1e30, mx=-1e30; size_t n=c.values.size();
            for(double v:c.values){ sum+=v; if(v<mn)mn=v; if(v>mx)mx=v; }
            double avg = n? sum/n : 0;
            std::cout << "  " << c.name << "\n      avg=" << avg
                      << "  min=" << mn << "  max=" << mx << "\n";
        }
    }
    return 0;
}

int cmd_tokens(const std::string& path){
    Profile p; if(!load(path,p)) return 1;
    std::map<uint32_t,int> total; long long markers=0; long long toks=0;
    for(size_t i=0;i<p.sqtt_data_ptr.size();i++){
        if(!p.sqtt_data_ptr[i]) continue;
        auto& d=p.sqtt_descs[i];
        auto tk = tokenize(p.sqtt_data_ptr[i], p.sqtt_data[i].size, i, majorOf(d.sqtt_version),0,(uint32_t)d.sqtt_version);
        for(auto&t:tk){ total[t.type]++; if(t.is_marker())markers++; }
        toks += tk.size();
        std::cout << "SE" << i << ": " << tk.size() << " tokens\n";
    }
    std::cout << "\ntotal: " << toks << " tokens, " << markers << " markers\nby type:";
    for(auto&kv:total) std::cout << "  t"<<kv.first<<"="<<kv.second;
    std::cout << "\n";
    return 0;
}

int cmd_dump(const std::string& path, int n, int se){
    Profile p; if(!load(path,p)) return 1;
    if(se<0 || se>=(int)p.sqtt_data_ptr.size() || !p.sqtt_data_ptr[se]){
        std::cerr << "bad SE index\n"; return 1;
    }
    auto& d=p.sqtt_descs[se];
    SqttParser sp; sp.init(p.sqtt_data_ptr[se], p.sqtt_data[se].size, 0, se, majorOf(d.sqtt_version),0,(uint32_t)d.sqtt_version);
    SqttToken t; int c=0;
    while(sp.advance(t) && (n<0 || c<n)){
        printf("type=%-3u hdr=%04x ts=%llu pos=%u se=%u f1c=%u f20=%u f24=%u f28=%u f2c=%u f34=%u f38=%u f3c=%u %s\n",
          t.type,t.header,(unsigned long long)t.timestamp,t.position,t.se,t.f1c,t.f20,t.f24,t.f28,t.f2c,t.f34,t.f38,t.f3c,t.is_marker()?"<MARKER>":"");
        c++;
    }
    return 0;
}

// waves: native decode of every SE. One line per traced wave in the same shape as tools/rtd dumps:
//   W cu simd slot begin end ninst exec wait stall start_pc : cat cat ...
static int cmd_waves(const std::string& path, const std::string& durfile){
    Profile p; if(!load(path,p)) return 1;
    FILE* df = durfile.empty() ? nullptr : fopen(durfile.c_str(), "w");
    for(size_t se=0; se<p.sqtt_data_ptr.size(); se++){
        SqttDecode d; std::string err;
        if(!decode_sqtt_gfx12(p.sqtt_data_ptr[se], p.sqtt_data[se].size, (int)se, d, &err)){ std::cerr << "SE" << se << ": " << err << "\n"; return 1; }
        for(auto& w : d.waves){
            if(!w.traced) continue;
            printf("W %d %d %d %lld %lld %zu %lld %lld %lld %llx %d :", w.cu, w.simd, w.slot, (long long)w.begin, (long long)w.end, w.insts.size(),
                   (long long)w.exec, (long long)w.wait, (long long)w.stall, (unsigned long long)w.start_pc, w.se);
            for(auto& i : w.insts) printf(" %d", (int)i.cat);
            printf("\n");
            if(df){ fprintf(df, "D :"); for(auto& i : w.insts) fprintf(df, " %lld,%lld,%lld", (long long)i.duration, (long long)i.stall, (long long)i.time); fprintf(df, "\n"); }
        }
    }
    if(df) fclose(df);
    return 0;
}

// kernels / cycles: identify the shader of every traced wave and aggregate. Several files may be given.
static int cmd_kernels(const std::vector<std::string>& files, bool cycles, const std::string& sigfilter, const std::string& mcpu){
    std::map<std::string, KernelStats> ks; uint64_t unid = 0; std::string err;
    if(!analyze_captures(files, mcpu, cycles, ks, &unid, &err)){ std::cerr << err << "\n"; return 1; }
    std::vector<KernelStats*> v; uint64_t total = 0;
    for(auto& [s, k] : ks){ v.push_back(&k); total += k.wave_cycles; }
    std::sort(v.begin(), v.end(), [](auto* a, auto* b){ return a->wave_cycles > b->wave_cycles; });
    if(!cycles){
        printf("%-30s %-9s %9s %6s %10s %12s %6s %6s %6s %s\n", "kernel", "sig", "wave-cyc%", "waves", "insts/wave", "avg wave cyc", "exec%", "wait%", "stall%", "captures");
        for(auto* k : v){
            double t = (double)(k->exec + k->wait + k->stall) + 1e-9;
            printf("%-30s %-9s %9.1f %6llu %10llu %12.0f %6.1f %6.1f %6.1f %zu\n", k->label.c_str(), k->sig.c_str(), 100.0 * k->wave_cycles / (double)std::max<uint64_t>(total, 1),
                   (unsigned long long)k->waves, (unsigned long long)k->insts, (double)k->wave_cycles / (double)std::max<uint64_t>(k->waves, 1),
                   100 * k->exec / t, 100 * k->wait / t, 100 * k->stall / t, k->captures.size());
        }
        if(unid) printf("(%llu traced waves could not be matched to a shader)\n", (unsigned long long)unid);
        return 0;
    }
    KernelStats* k = nullptr;
    for(auto* c : v) if(c->sig.rfind(sigfilter, 0) == 0 || (sigfilter.empty() && c->label != "unidentified")){ k = c; break; }
    if(!k){ std::cerr << "no kernel matches\n"; return 1; }
    uint64_t all = 0; for(auto& [m, a] : k->by_mnemonic) all += a[1];
    printf("kernel %s (%s): %llu waves, %llu instruction-cycles\n", k->sig.c_str(), k->label.c_str(), (unsigned long long)k->waves, (unsigned long long)all);
    printf("%-32s %9s %11s %5s %8s %9s\n", "mnemonic", "count", "cycles", "%", "stall%", "cyc/inst");
    std::vector<std::pair<std::string, std::array<uint64_t,3>>> m(k->by_mnemonic.begin(), k->by_mnemonic.end());
    std::sort(m.begin(), m.end(), [](auto& a, auto& b){ return a.second[1] > b.second[1]; });
    for(size_t i = 0; i < m.size() && i < 20; i++)
        printf("%-32s %9llu %11llu %5.1f %8.0f %9.1f\n", m[i].first.c_str(), (unsigned long long)m[i].second[0], (unsigned long long)m[i].second[1],
               100.0 * m[i].second[1] / (double)std::max<uint64_t>(all, 1), 100.0 * m[i].second[2] / (double)std::max<uint64_t>(m[i].second[1], 1),
               (double)m[i].second[1] / (double)m[i].second[0]);
    return 0;
}

static int cmd_dispatches(const std::string& file, int se, const std::string& mcpu){
    std::vector<DispatchRow> rows; std::string err;
    if(!analyze_dispatches(file, mcpu, se, rows, &err)){ std::cerr << err << "\n"; return 1; }
    printf("%4s %12s %9s %7s %7s  %-30s %s\n", "#", "start", "cycles", "waves", "traced", "kernel", "sig");
    for(auto& r : rows) printf("%4d %12lld %9lld %7llu %7llu  %-30s %s%s\n", r.index, (long long)r.begin, (long long)(r.end - r.begin), (unsigned long long)r.waves,
        (unsigned long long)r.traced, r.label.empty() ? "(no traced wave)" : r.label.c_str(), r.sig.c_str(), r.inferred ? "" : "  [marker]");
    return 0;
}

// events: counts per kind and the event list for one shader engine.
static int cmd_events(const std::string& path, int se, int limit){
    Profile p; if(!load(path,p)) return 1;
    if(se<0 || se>=(int)p.sqtt_data_ptr.size()){ std::cerr << "bad SE index\n"; return 1; }
    SqttDecode d; std::string err;
    if(!decode_sqtt_gfx12(p.sqtt_data_ptr[se], p.sqtt_data[se].size, se, d, &err)){ std::cerr << err << "\n"; return 1; }
    std::map<int,int> c; for(auto& e : d.events) c[(int)e.kind]++;
    printf("SE%d: %zu events, %zu shader-data tokens, %zu utilisation-counter samples, %zu other-SIMD memory instructions\n", se, d.events.size(), d.shader_data.size(), d.util_counters.size(), d.other_simd.size());
    for(auto& [k, v] : c) printf("  %-16s %d\n", event_kind_name((EventKind)k), v);
    int n = 0;
    for(auto& e : d.events){ if(limit >= 0 && n++ >= limit) break; printf("  t=%-10lld %-16s me=%u pipe=%u id=%u%s\n", (long long)e.time, event_kind_name(e.kind), e.me, e.pipe, e.id, e.inferred ? " (inferred)" : ""); }
    for(size_t i = 0; i < d.shader_data.size() && (limit < 0 || (int)i < limit); i++) printf("  shader-data t=%lld cu=%d simd=%d slot=%d value=0x%x%s\n", (long long)d.shader_data[i].time, d.shader_data[i].cu, d.shader_data[i].simd, d.shader_data[i].slot, d.shader_data[i].value, d.shader_data[i].priv ? " (trap)" : "");
    return 0;
}

static std::string arg_value(int argc, char** argv, const char* name, const std::string& def){
    for(int i=3;i<argc-1;i++) if(std::string(argv[i])==name) return argv[i+1];
    return def;
}

static int cmd_occupancy(const std::string& path, int64_t bin, bool csv, int se){
    CaptureDecode c; std::string err;
    if(!decode_capture(path, c, &err)){ std::cerr << err << "\n"; return 1; }
    if(se < 0 || se >= (int)c.se.size()){ std::cerr << "bad SE index\n"; return 1; }
    if(csv){ export_occupancy_csv(c.se[se], bin, std::cout); return 0; }
    auto bins = occupancy(c.se[se], bin);
    auto s = summarize(c.p); double cap = (double)s.cu_per_se * s.simd_per_cu * s.waves_per_simd;
    double avg = 0, tot = 0; int peak = 0;
    for(auto& b : bins){ avg += b.avg_waves; peak = std::max(peak, b.peak_waves); }
    if(!bins.empty()) avg /= bins.size();
    (void)tot;
    printf("SE%d: %zu bins of %lld cycles; average %.1f resident waves, peak %d (hardware limit %.0f, %.1f%% average occupancy)\n", c.se_index[se], bins.size(), (long long)bin, avg, peak, cap, cap ? 100 * avg / cap : 0.0);
    int maxw = std::max(peak, 1);
    for(auto& b : bins){ int n = (int)(40.0 * b.avg_waves / maxw); printf("%12lld %7.1f %s\n", (long long)b.begin, b.avg_waves, std::string(n, '#').c_str()); }
    return 0;
}

static int cmd_gaps(const std::string& path, int64_t min_len, int se){
    CaptureDecode c; std::string err;
    if(!decode_capture(path, c, &err)){ std::cerr << err << "\n"; return 1; }
    if(se < 0 || se >= (int)c.se.size()){ std::cerr << "bad SE index\n"; return 1; }
    auto g = idle_gaps(c.se[se], min_len);
    int64_t span = c.se[se].last_time - c.se[se].first_time, idle = 0; for(auto& x : g) idle += x.end - x.begin;
    printf("SE%d: %zu idle gaps of at least %lld cycles, %lld of %lld cycles idle (%.1f%%)\n", c.se_index[se], g.size(), (long long)min_len, (long long)idle, (long long)span, span ? 100.0 * idle / span : 0.0);
    for(auto& x : g) printf("  %12lld .. %-12lld %8lld cycles\n", (long long)x.begin, (long long)x.end, (long long)(x.end - x.begin));
    return 0;
}

// export <what> <file> [--se N] [--mcpu X] [--bin N]   what = waves | insts | dispatches | occupancy | spm | json
static int cmd_export(const std::string& what, const std::string& path, int argc, char** argv){
    int se = atoi(arg_value(argc, argv, "--se", "0").c_str());
    int64_t bin = atoll(arg_value(argc, argv, "--bin", "2000").c_str());
    if(what == "spm"){ Profile p; if(!load(path, p)) return 1; if(!p.derived_spm){ std::cerr << "no derived SPM data\n"; return 1; } export_spm_csv(p, std::cout); return 0; }
    CaptureDecode c; std::string err;
    if(!decode_capture(path, c, &err)){ std::cerr << err << "\n"; return 1; }
    std::string mcpu = arg_value(argc, argv, "--mcpu", guess_mcpu(c.p));
    if(what == "waves") export_waves_csv(c, std::cout);
    else if(what == "insts") export_insts_csv(c, std::cout);
    else if(what == "occupancy"){ if(se < 0 || se >= (int)c.se.size()){ std::cerr << "bad SE index\n"; return 1; } export_occupancy_csv(c.se[se], bin, std::cout); }
    else if(what == "dispatches" || what == "json"){
        std::vector<DispatchRow> rows; std::string e2;
        if(!analyze_dispatches(path, mcpu, se, rows, &e2)){ std::cerr << e2 << "\n"; return 1; }
        if(what == "dispatches") export_dispatches_csv(rows, std::cout); else export_json(c, rows, std::cout);
    } else { std::cerr << "unknown export '" << what << "' (waves, insts, dispatches, occupancy, spm, json)\n"; return 2; }
    return 0;
}

int main(int argc, char** argv){
    if(argc<3){ usage(); return 2; }
    std::string cmd=argv[1], path=argv[2];
    int n=200, se=0;
    for(int i=3;i<argc;i++){
        if(std::string(argv[i])=="-n" && i+1<argc) n=std::atoi(argv[++i]);
        else if(std::string(argv[i])=="-se" && i+1<argc) se=std::atoi(argv[++i]);
    }
    if(cmd=="info") return cmd_info(path);
    if(cmd=="spm") return cmd_spm(path);
    if(cmd=="tokens") return cmd_tokens(path);
    if(cmd=="dump") return cmd_dump(path,n,se);
    if(cmd=="waves") return cmd_waves(path, argc>3 ? argv[3] : "");
    if(cmd=="occupancy") return cmd_occupancy(path, atoll(arg_value(argc, argv, "--bin", "2000").c_str()), false, atoi(arg_value(argc, argv, "--se", "0").c_str()));
    if(cmd=="gaps") return cmd_gaps(path, atoll(arg_value(argc, argv, "--min", "1000").c_str()), atoi(arg_value(argc, argv, "--se", "0").c_str()));
    if(cmd=="export"){ if(argc < 4){ usage(); return 2; } return cmd_export(argv[3], path, argc, argv); }
    if(cmd=="dispatches" || cmd=="events"){
        std::string mcpu; int se = 0, lim = 40;
        for(int i=3;i<argc;i++){ std::string a = argv[i]; if(a=="--se" && i+1<argc) se = atoi(argv[++i]); else if(a=="--mcpu" && i+1<argc) mcpu = argv[++i]; else if(a=="-n" && i+1<argc) lim = atoi(argv[++i]); }
        if(mcpu.empty()){ Profile pp; mcpu = load(path, pp) ? guess_mcpu(pp) : "gfx1201"; }
        return cmd=="dispatches" ? cmd_dispatches(path, se, mcpu) : cmd_events(path, se, lim);
    }
    if(cmd=="kernels" || cmd=="cycles"){
        std::vector<std::string> files; std::string sig, mcpu;
        for(int i=2;i<argc;i++){ std::string a = argv[i]; if(a=="--sig" && i+1<argc) sig = argv[++i]; else if(a=="--mcpu" && i+1<argc) mcpu = argv[++i]; else files.push_back(a); }
        if(mcpu.empty()){ Profile pp; mcpu = (!files.empty() && load(files[0], pp)) ? guess_mcpu(pp) : "gfx1201"; }
        return cmd_kernels(files, cmd=="cycles", sig, mcpu);
    }
    usage(); return 2;
}
