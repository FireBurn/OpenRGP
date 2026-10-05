// Regression test for the native SQTT decoder: decode_test <capture> <traced waves> <traced instructions> [<dispatches>]
// The expected numbers were cross-checked against AMD's rocprof-trace-decoder 0.1.6, which produced identical
// per-instruction timing for every traced wave of these captures.
#include "openrgp/analysis.h"
#include <cstdio>
#include <cstdlib>
using namespace openrgp;
int main(int argc, char** argv) {
    if (argc < 4) { fprintf(stderr, "usage: decode_test <capture> <waves> <insts> [dispatches]\n"); return 2; }
    CaptureDecode c; std::string err;
    if (!decode_capture(argv[1], c, &err)) { fprintf(stderr, "%s: %s\n", argv[1], err.c_str()); return 1; }
    size_t waves = 0, insts = 0, all = 0; int64_t exec = 0, wait = 0, stall = 0, dispatches = 0;
    for (size_t k = 0; k < c.se.size(); k++) {
        auto& d = c.se[k];
        if (d.desync) { fprintf(stderr, "SE%d lost sync\n", c.se_index[k]); return 1; }
        if (d.unknown_tokens) { fprintf(stderr, "SE%d: %llu unknown tokens\n", c.se_index[k], (unsigned long long)d.unknown_tokens); return 1; }
        for (auto& e : d.events) dispatches += e.kind == EventKind::Dispatch;
        for (auto& w : d.waves) { all++; if (w.traced) { waves++; insts += w.insts.size(); exec += w.exec; wait += w.wait; stall += w.stall; } }
    }
    printf("%s: %zu waves, traced %zu, instructions %zu, exec %lld wait %lld stall %lld, dispatches %lld\n", argv[1], all, waves, insts,
           (long long)exec, (long long)wait, (long long)stall, (long long)dispatches);
    if (waves != strtoull(argv[2], nullptr, 10) || insts != strtoull(argv[3], nullptr, 10)) { fprintf(stderr, "unexpected counts\n"); return 1; }
    if (argc > 4 && dispatches != atoll(argv[4])) { fprintf(stderr, "unexpected dispatch count\n"); return 1; }
    return 0;
}
