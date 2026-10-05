#include "openrgp/analysis.h"

#include <algorithm>
#include <cstdio>
#include <ostream>

namespace openrgp {

std::string guess_mcpu(const Profile& p) {
    std::string n;
    for (char ch : summarize(p).gpu_name) n += (char)toupper((unsigned char)ch);
    struct { const char* key; const char* mcpu; } map[] = {
        {"NAVI48", "gfx1201"}, {"NAVI44", "gfx1200"}, {"NAVI31", "gfx1100"}, {"NAVI32", "gfx1101"}, {"NAVI33", "gfx1102"},
        {"PHOENIX", "gfx1103"}, {"HAWK", "gfx1103"}, {"STRIX", "gfx1150"}, {"NAVI21", "gfx1030"}, {"NAVI22", "gfx1031"},
        {"NAVI23", "gfx1032"}, {"NAVI24", "gfx1034"}, {"REMBRANDT", "gfx1035"}, {"RAPHAEL", "gfx1036"}, {"NAVI10", "gfx1010"},
        {"NAVI12", "gfx1011"}, {"NAVI14", "gfx1012"},
    };
    for (auto& m : map) if (n.find(m.key) != std::string::npos) return m.mcpu;
    return "gfx1201";
}

bool decode_capture(const std::string& file, CaptureDecode& out, std::string* err) {
    std::string e;
    if (!RgpFile::load(file, out.p, &e)) { if (err) *err = e; return false; }
    for (size_t i = 0; i < out.p.sqtt_data_ptr.size(); i++) {
        if (!out.p.sqtt_data_ptr[i] || out.p.sqtt_data[i].size == 0) continue;
        SqttDecode d; std::string de;
        if (!decode_sqtt(out.p.sqtt_data_ptr[i], out.p.sqtt_data[i].size, (int)i, d, &de)) { e = de; continue; }
        out.se.push_back(std::move(d)); out.se_index.push_back((int)i);
    }
    if (out.se.empty()) { if (err) *err = e.empty() ? "no thread-trace data in capture" : e; return false; }
    return true;
}

namespace {
// +1/-1 events of the resident-wave count, sorted by time.
std::vector<std::pair<int64_t, int>> edges(const SqttDecode& d) {
    std::vector<std::pair<int64_t, int>> ev;
    for (auto& w : d.waves) { if (!w.complete) continue; ev.push_back({w.begin, +1}); ev.push_back({w.end, -1}); }
    std::sort(ev.begin(), ev.end(), [](auto& a, auto& b) { return a.first != b.first ? a.first < b.first : a.second < b.second; });
    return ev;
}
}  // namespace

std::vector<OccupancyBin> occupancy(const SqttDecode& d, int64_t bin) {
    std::vector<OccupancyBin> out;
    auto ev = edges(d);
    if (ev.empty() || bin <= 0) return out;
    int64_t t0 = ev.front().first, t1 = ev.back().first;
    size_t nb = (size_t)((t1 - t0) / bin) + 1;
    out.resize(nb);
    for (size_t i = 0; i < nb; i++) { out[i].begin = t0 + (int64_t)i * bin; out[i].end = out[i].begin + bin; }
    int cur = 0; size_t e = 0;
    for (size_t i = 0; i < nb; i++) {
        int64_t b = out[i].begin, f = out[i].end, last = b; double area = 0; int peak = cur;
        while (e < ev.size() && ev[e].first < f) {
            area += (double)cur * (ev[e].first - last); last = ev[e].first;
            cur += ev[e].second; peak = std::max(peak, cur); e++;
        }
        area += (double)cur * (f - last);
        out[i].avg_waves = area / (double)bin; out[i].peak_waves = peak;
    }
    return out;
}

std::vector<Gap> idle_gaps(const SqttDecode& d, int64_t min_len) {
    std::vector<Gap> out;
    auto ev = edges(d);
    int cur = 0; int64_t idle_since = -1;
    for (auto& [t, dl] : ev) {
        if (cur == 0 && idle_since >= 0 && t - idle_since >= min_len) out.push_back({idle_since, t});
        cur += dl;
        if (cur == 0) idle_since = t; else idle_since = -1;
    }
    return out;
}

void export_waves_csv(const CaptureDecode& c, std::ostream& os) {
    os << "se,cu,simd,slot,begin,end,duration,dispatch,start_pc,traced,instructions,exec,wait,stall\n";
    for (size_t k = 0; k < c.se.size(); k++)
        for (auto& w : c.se[k].waves) {
            char pc[32]; snprintf(pc, sizeof pc, "0x%llx", (unsigned long long)w.start_pc);
            os << c.se_index[k] << ',' << w.cu << ',' << w.simd << ',' << w.slot << ',' << w.begin << ',' << w.end << ',' << (w.end - w.begin) << ','
               << w.dispatch << ',' << pc << ',' << (int)w.traced << ',' << w.insts.size() << ',' << w.exec << ',' << w.wait << ',' << w.stall << '\n';
        }
}

void export_insts_csv(const CaptureDecode& c, std::ostream& os) {
    os << "se,cu,simd,slot,wave_begin,index,time,category,duration,stall\n";
    for (size_t k = 0; k < c.se.size(); k++)
        for (auto& w : c.se[k].waves) {
            if (!w.traced) continue;
            for (size_t i = 0; i < w.insts.size(); i++)
                os << c.se_index[k] << ',' << w.cu << ',' << w.simd << ',' << w.slot << ',' << w.begin << ',' << i << ',' << w.insts[i].time << ','
                   << inst_cat_name(w.insts[i].cat) << ',' << w.insts[i].duration << ',' << w.insts[i].stall << '\n';
        }
}

static std::string csv_quote(const std::string& s) {
    std::string r = "\"";
    for (char ch : s) { if (ch == '"') r += '"'; r += ch; }
    return r + "\"";
}

void export_dispatches_csv(const std::vector<DispatchRow>& rows, std::ostream& os) {
    os << "index,event,start,cycles,waves,traced_waves,kernel,signature\n";
    for (auto& r : rows)
        os << r.index << ',' << r.event << ',' << r.begin << ',' << (r.end - r.begin) << ',' << r.waves << ',' << r.traced << ',' << csv_quote(r.label) << ',' << r.sig << '\n';
}

void export_occupancy_csv(const SqttDecode& d, int64_t bin, std::ostream& os) {
    os << "begin,end,avg_waves,peak_waves\n";
    for (auto& b : occupancy(d, bin)) os << b.begin << ',' << b.end << ',' << b.avg_waves << ',' << b.peak_waves << '\n';
}

void export_spm_csv(const Profile& p, std::ostream& os) {
    if (!p.derived_spm) return;
    auto& s = *p.derived_spm;
    os << "timestamp";
    for (auto& c : s.counters) os << ',' << csv_quote(c.name);
    os << '\n';
    for (size_t i = 0; i < s.timestamps.size(); i++) {
        os << s.timestamps[i];
        for (auto& c : s.counters) { os << ','; if (i < c.values.size()) os << c.values[i]; }
        os << '\n';
    }
}

static std::string json_str(const std::string& s) {
    std::string r = "\"";
    for (unsigned char ch : s) {
        if (ch == '"' || ch == '\\') { r += '\\'; r += (char)ch; }
        else if (ch < 0x20) { char b[8]; snprintf(b, sizeof b, "\\u%04x", ch); r += b; }
        else r += (char)ch;
    }
    return r + "\"";
}

void export_json(const CaptureDecode& c, const std::vector<DispatchRow>& rows, std::ostream& os) {
    os << "{\n  \"file\": " << json_str(c.p.path) << ",\n  \"container\": " << json_str(c.p.container) << ",\n  \"gpu\": " << json_str(summarize(c.p).gpu_name)
       << ",\n  \"shader_engines\": [";
    for (size_t k = 0; k < c.se.size(); k++) {
        auto& d = c.se[k]; size_t traced = 0; for (auto& w : d.waves) traced += w.traced;
        auto gaps = idle_gaps(d, 1000);
        os << (k ? "," : "") << "\n    {\"index\": " << c.se_index[k] << ", \"sqtt_version\": " << d.version << ", \"tokens\": " << d.tokens << ", \"waves\": " << d.waves.size()
           << ", \"traced_waves\": " << traced << ", \"events\": " << d.events.size() << ", \"first_time\": " << d.first_time << ", \"last_time\": " << d.last_time
           << ", \"idle_gaps\": [";
        for (size_t g = 0; g < gaps.size(); g++) os << (g ? ", " : "") << '[' << gaps[g].begin << ", " << gaps[g].end << ']';
        os << "]}";
    }
    os << "\n  ],\n  \"dispatches\": [";
    for (size_t i = 0; i < rows.size(); i++) {
        auto& r = rows[i];
        os << (i ? "," : "") << "\n    {\"index\": " << r.index << ", \"start\": " << r.begin << ", \"cycles\": " << (r.end - r.begin) << ", \"waves\": " << r.waves
           << ", \"traced_waves\": " << r.traced << ", \"kernel\": " << json_str(r.label) << ", \"signature\": " << json_str(r.sig) << "}";
    }
    os << "\n  ]\n}\n";
}

}  // namespace openrgp
