#!/bin/bash
# Builds rtd_summary against the 0.1.6 rocprof-trace-decoder (the 0.2 build in the ROCm SDK wheel hangs on these traces).
set -e; cd "$(dirname "$0")"
if [ ! -d v016 ]; then mkdir v016 && curl -sL https://github.com/ROCm/rocprof-trace-decoder/releases/download/0.1.6/rocprof-trace-decoder-manylinux-2.28-0.1.6-Linux.tar.gz | tar xz -C v016; fi
L=$(dirname "$(find "$PWD/v016" -name 'librocprof-trace-decoder.so' | head -1)")
g++ -O2 -std=c++17 -I../../core/include -I. rtd_summary.cpp ../../build/libopenrgp_core.a -L"$L" -lrocprof-trace-decoder -Wl,-rpath,"$L" -o rtd_summary
