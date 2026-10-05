// Decode a radv .rgp with AMD's rocprof-trace-decoder and summarise waves per shader.
#include <openrgp/rgp_file.h>
#include "rocprof_trace_decoder.h"
#include <algorithm>
#include <cinttypes>
#include <cstdio>
#include <csignal>
#include <unistd.h>
#include <map>
#include <array>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
using namespace openrgp;

struct Agg {
    uint64_t waves = 0, life = 0, exec = 0, wait = 0, stall = 0, insts = 0;
    uint64_t cat[16] = {};
    int64_t first = INT64_MAX, last = 0;
};
struct Ins { uint32_t size; std::string text; };
struct Ctx {
    std::vector<std::map<uint64_t, Ins>> isa; std::vector<uint64_t> co_base; std::vector<std::array<int,3>> co_info; std::map<uint64_t,int> base_to_co;
    const Profile* p; size_t se = 0;
    std::vector<uint64_t> bases;               // sorted loader bases
    std::map<uint64_t, Agg> agg;
    uint64_t waves = 0, infos = 0; int64_t tmin = INT64_MAX, tmax = 0;
};
static uint64_t shader_of(Ctx* c, uint64_t addr) {
    auto it = std::upper_bound(c->bases.begin(), c->bases.end(), addr);
    return it == c->bases.begin() ? 0 : *(it - 1);
}
static uint64_t se_cb(uint8_t** buf, uint64_t* sz, void* u) {
    Ctx* c = (Ctx*)u;
    if (c->se >= c->p->sqtt_data_ptr.size()) { *sz = 0; return 0; }
    *buf = (uint8_t*)c->p->sqtt_data_ptr[c->se]; *sz = c->p->sqtt_data[c->se].size; if (getenv("RTD_LIMIT")) *sz = std::min<uint64_t>(*sz, atoi(getenv("RTD_LIMIT"))); c->se++;
    return *sz;
}
static Ctx* g; static volatile uint64_t n_isa, n_tr; static uint64_t last_pc;
static void onint(int){ fprintf(stderr,"isa_cb=%lu tr_cb=%lu last_pc=%lx\n",(unsigned long)n_isa,(unsigned long)n_tr,(unsigned long)last_pc); _exit(1);}
static rocprofiler_thread_trace_decoder_status_t isa_cb(char* out, uint64_t* mem, uint64_t* size, rocprofiler_thread_trace_decoder_pc_t pc, void*) {
    n_isa++; last_pc = pc.address;
    uint64_t base = shader_of(g, pc.address);
    auto it = g->base_to_co.find(base);
    if (it == g->base_to_co.end()) return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_ERROR_INVALID_ARGUMENT;
    auto& m = g->isa[it->second]; auto j = m.find(pc.address - base);
    if (j == m.end()) return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_ERROR_INVALID_ARGUMENT;
    size_t n = j->second.text.size();
    if (*mem < n + 1) { *mem = n + 1; return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_ERROR_OUT_OF_RESOURCES; }
    memcpy(out, j->second.text.c_str(), n + 1); *mem = n; *size = j->second.size;
    return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_SUCCESS;
}
static rocprofiler_thread_trace_decoder_status_t tr_cb(rocprofiler_thread_trace_decoder_record_type_t t, void* ev, uint64_t n, void* u) {
    n_tr++; if (t==ROCPROFILER_THREAD_TRACE_DECODER_RECORD_GFXIP) fprintf(stderr,"gfxip=%lu\n",(unsigned long)(uintptr_t)ev);
    Ctx* c = (Ctx*)u;
    if (t == ROCPROFILER_THREAD_TRACE_DECODER_RECORD_INFO) c->infos += n;
    if (t == ROCPROFILER_THREAD_TRACE_DECODER_RECORD_OCCUPANCY) { static int d; auto* o=(rocprofiler_thread_trace_decoder_occupancy_t*)ev; for (uint64_t i=0;i<n && d<6;i++,d++) fprintf(stderr,"occ pc=%lx co=%lu t=%lu cu=%d simd=%d wave=%d start=%d\n",(unsigned long)o[i].pc.address,(unsigned long)o[i].pc.code_object_id,(unsigned long)o[i].time,o[i].cu,o[i].simd,o[i].wave_id,o[i].start); }
    if (t != ROCPROFILER_THREAD_TRACE_DECODER_RECORD_WAVE) return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_SUCCESS;
    auto* w = (rocprofiler_thread_trace_decoder_wave_t*)ev;
    for (uint64_t i = 0; i < n; i++, w++) {
        static int d2; if (d2++ < 2) { fprintf(stderr,"wave cu=%d simd=%d id=%d t=%ld..%ld insts=%lu\n",w->cu,w->simd,w->wave_id,(long)w->begin_time,(long)w->end_time,(unsigned long)w->instructions_size); for (uint64_t k=0;k<w->instructions_size && k<12;k++){auto&I=w->instructions_array[k]; fprintf(stderr,"   t=%ld cat=%d dur=%d stall=%d pc=%lx\n",(long)I.time,I.category,I.duration,I.stall,(unsigned long)I.pc.address);} }
        static int dbg; if (dbg++ < 0 && w->instructions_size) fprintf(stderr,"wave pc0=%lx co=%lu first_base=%lx last_base=%lx\n",(unsigned long)w->instructions_array[0].pc.address,(unsigned long)w->instructions_array[0].pc.code_object_id,(unsigned long)c->bases.front(),(unsigned long)c->bases.back());
        if (getenv("RTD_DUMP")) { static FILE* df = fopen(getenv("RTD_DUMP"), "w"); uint64_t ex=0,wa=0,st=0; for (uint64_t k=0;k<w->timeline_size;k++){auto&q=w->timeline_array[k]; if(q.type==ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_EXEC)ex+=q.duration; else if(q.type==ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_WAIT)wa+=q.duration; else if(q.type==ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_STALL)st+=q.duration;}
          fprintf(df,"W %d %d %d %ld %ld %lu %lu %lu %lu :",w->cu,w->simd,w->wave_id,(long)w->begin_time,(long)w->end_time,(unsigned long)w->instructions_size,(unsigned long)ex,(unsigned long)wa,(unsigned long)st); for (uint64_t k=0;k<w->instructions_size;k++) fprintf(df," %d",w->instructions_array[k].category); fprintf(df,"\n"); fflush(df);
          static FILE* dd = fopen((std::string(getenv("RTD_DUMP"))+".d").c_str(), "w"); fprintf(dd,"D :"); for (uint64_t k=0;k<w->instructions_size;k++) fprintf(dd," %d,%d,%ld",w->instructions_array[k].duration,(int)w->instructions_array[k].stall,(long)w->instructions_array[k].time); fprintf(dd,"\n"); fflush(dd);}
        uint64_t pc0 = w->instructions_size ? w->instructions_array[0].pc.address : 0;
        Agg& a = c->agg[shader_of(c, pc0)];
        a.waves++; a.life += w->end_time - w->begin_time;
        a.first = std::min<int64_t>(a.first, w->begin_time); a.last = std::max<int64_t>(a.last, w->end_time);
        c->tmin = std::min<int64_t>(c->tmin, w->begin_time); c->tmax = std::max<int64_t>(c->tmax, w->end_time);
        for (uint64_t k = 0; k < w->timeline_size; k++) {
            auto& s = w->timeline_array[k];
            if (s.type == ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_EXEC) a.exec += s.duration;
            else if (s.type == ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_WAIT) a.wait += s.duration;
            else if (s.type == ROCPROFILER_THREAD_TRACE_DECODER_WSTATE_STALL) a.stall += s.duration;
        }
        for (uint64_t k = 0; k < w->instructions_size; k++) { a.insts++; a.cat[w->instructions_array[k].category & 15]++; }
        c->waves++;
    }
    return ROCPROFILER_THREAD_TRACE_DECODER_STATUS_SUCCESS;
}
int main(int argc, char** argv) {
    if (argc < 2) return 1;
    Profile p; std::string err;
    if (!RgpFile::load(argv[1], p, &err)) { fprintf(stderr, "%s\n", err.c_str()); return 1; }
    signal(SIGINT, onint); signal(SIGALRM, onint); alarm(getenv("RTD_ALARM")?atoi(getenv("RTD_ALARM")):20);
    Ctx c; c.p = &p; for (auto& d : p.sqtt_descs) fprintf(stderr,"se%d sqtt_version=0x%x\n", d.shader_engine_index,(int)d.sqtt_version);
    for (auto& e : p.loader_events) if (e.loader_event_type == 0) c.bases.push_back(e.base_address);
    std::sort(c.bases.begin(), c.bases.end());
    g = &c;
    if (argc > 2) {
        std::string d = argv[2]; std::ifstream f(d + "/isa.txt"); std::string line; int nco = 0;
        for (auto& e : p.loader_events) if (e.loader_event_type == 0) { c.base_to_co[e.base_address] = nco++; }
        c.isa.resize(nco);
        while (std::getline(f, line)) {
            std::istringstream ss(line); int co; uint64_t off; uint32_t sz; ss >> co >> off >> sz; std::string t; std::getline(ss >> std::ws, t);
            if (co < nco) c.isa[co][off] = {sz, t};
        }
        // names / wmma counts
        std::ifstream cf(d + "/cos.txt"); while (std::getline(cf, line)) { std::istringstream ss(line); int co, n, wm, dt; ss >> co >> n >> wm >> dt; c.co_info.push_back({n, wm, dt}); }
    }
    fprintf(stderr,"loaded, bases=%zu se=%zu\n", c.bases.size(), p.sqtt_data_ptr.size());
    auto st = rocprof_trace_decoder_parse_data(se_cb, tr_cb, isa_cb, &c);
    printf("status=%s waves=%" PRIu64 " info=%" PRIu64 " span=%" PRId64 " cycles shaders=%zu\n",
           rocprof_trace_decoder_get_status_string(st), c.waves, c.infos, c.tmax - c.tmin, c.agg.size());
    std::vector<std::pair<uint64_t, Agg>> v(c.agg.begin(), c.agg.end());
    std::sort(v.begin(), v.end(), [](auto& a, auto& b) { return a.second.life > b.second.life; });
    printf("%-14s %7s %10s %9s %6s %6s %6s %8s  [salu valu vmem smem lds flat]\n", "shader_base", "waves", "wave-cyc", "span", "exec%", "wait%", "stal%", "insts");
    for (auto& [b, a] : v) {
        double tot = a.exec + a.wait + a.stall + 1e-9;
        int co = c.base_to_co.count(b) ? c.base_to_co[b] : -1; int ni = co >= 0 && co < (int)c.co_info.size() ? c.co_info[co][0] : 0, wm = co >= 0 && co < (int)c.co_info.size() ? c.co_info[co][1] : 0, dt = co >= 0 && co < (int)c.co_info.size() ? c.co_info[co][2] : 0;
        printf("co%-3d n=%-5d wmma=%-3d dot4=%-3d ", co, ni, wm, dt);
        printf("%-14" PRIx64 " %7" PRIu64 " %10" PRIu64 " %9" PRId64 " %6.1f %6.1f %6.1f %8" PRIu64 "  [%" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64 " %" PRIu64 "]\n",
               b, a.waves, a.life, a.last - a.first, 100 * a.exec / tot, 100 * a.wait / tot, 100 * a.stall / tot, a.insts,
               a.cat[2], a.cat[6], a.cat[3], a.cat[1], a.cat[5], a.cat[4]);
    }
}
