# OpenRGP

Open-source reimplementation of AMD's closed-source **Radeon GPU Profiler (RGP)**,
for reading and analyzing `.rgp` capture files produced by the **Mesa radv**
Vulkan driver with SQTT (Shader Queue Trace & Timing) hardware tracing
(`MESA_VK_TRACE=rgp`).

RGP is closed-source; OpenRGP re-derives the file format from the open-source
Mesa writer (`ac_rgp.c` / `ac_sqtt.h`, MIT), the SQTT token layouts from AMD's public MIT-licensed
rocprof-trace-decoder sources (copy in `re/amd-src`) and, for the AMD_RDF container, from the public libamdrdf
specification (`re/amdrdf`). No RGP source code is copied.

## Status

**Reads RDNA2, RDNA3 and RDNA4 radv captures, and AMD's newer `AMD_RDF` containers.** The `.rgp` container and
derived SPM counters are parsed; the SQTT token stream is decoded natively into waves with per-instruction timing,
dispatches (inferred from wave activity), command-processor events and idle gaps; kernels are identified by
walking the shader ISA along the traced branches.

Validation against AMD's rocprof-trace-decoder 0.1.6 (identical time, duration and stall for every traced
instruction, identical exec/wait/stall per wave):

| generation | GPU | traced waves | instructions |
|---|---|---|---|
| RDNA4 (SQTT 4) | RX 9060 XT / Strix Halo | 56,847 (9 radv captures + one RDF sample) | 2.0M+ |
| RDNA3 (SQTT 3) | Radeon 780M | 1,275 | 10.3M |
| RDNA2 (SQTT 1-2) | RX 6800M | 55 | 4,016 |

The wave count of the 32k-token llama.cpp capture (246,898) equals RGP's own log.

Limits: radv traces carry no dispatch markers, so dispatch boundaries are inferred (a drained engine or a
>1000-cycle pause in wave launches) and can split or merge neighbouring dispatches. Kernel identification
works for compute kernels on RDNA2, RDNA3 and RDNA4; RDNA2 graphics shaders are still unidentified (see TODO.md). Without
`llvm-objdump` the kernel commands group waves by trace signature instead.

## Language

C++17 core library (no Qt) + Qt 6 Widgets GUI + CLI. Single toolchain.
(Original request was Rust; switched to C++/Qt6 since RGP is a Qt6 app.)

## Build

```sh
cmake -B build -G Ninja
cmake --build build
ctest --test-dir build
```

Requires a C++17 compiler and (for the GUI) Qt6 Widgets/Gui/Core.

## CLI

```sh
openrgp info   <file>                 # profile summary (GPU/CPU/API/traces, container format)
openrgp spm    <file>                 # derived SPM counters (cache/mem/LDS)
openrgp tokens <file>                 # SQTT token statistics
openrgp dump   <file> [-n N] [-se I]  # dump tokens
openrgp waves  <file> [dur-file]      # every wave; traced waves list their instruction categories and timing
openrgp dispatches <file> [--se N]    # dispatch table: start, cycles, waves, identified kernel
openrgp events <file> [--se N] [-n N] # command-processor events (dispatch, flush, bottom-of-pipe), shader data
openrgp kernels <file>... [--mcpu X]  # per-kernel wave time from the shader ISA; several files are merged
openrgp cycles  <file>... [--sig S]   # cycles per instruction mnemonic for one kernel
openrgp occupancy <file> [--bin N]    # resident waves over time (text chart)
openrgp gaps   <file> [--min N]       # periods in which no wave is resident
openrgp export <file> waves|insts|dispatches|occupancy|spm|json [--se N] [--bin N]
```
Cycle counts are shader-clock cycles. `kernels`, `cycles` and `dispatches` use `llvm-objdump` (the `--mcpu` default
follows the capture's GPU). Shader identity comes from walking the disassembly along the traced branches, because
radv traces carry no wave start PC.

## GUI

```sh
openrgp_gui [file]
openrgp_gui <file> --screenshot <dir>     # one PNG per tab (also a smoke test)
```
Tabs: **Summary**, **Dispatches** (kernel table), **Occupancy** (resident waves and idle gaps per shader engine),
**Timeline** (wave lifetimes per SIMD slot, coloured by dispatch; wheel zooms, drag pans), **Waves** (sortable),
**Events**, **SPM Counters**, **Tokens**. File > Export writes the CSV and JSON files described above.

## Library

Link `libopenrgp_core.a`; headers under `core/include/openrgp/`.

```cpp
#include <openrgp/rgp_file.h>
openrgp::Profile p;
std::string err;
openrgp::RgpFile::load("capture.rgp", p, &err);
auto s = openrgp::summarize(p);   // GPU name, topology, clocks, ...
// p.derived_spm -> named SPM counters
// openrgp::tokenize(...) -> SQTT token stream
```

## Format

See `docs/rgp-file-format.md` for the full `.rgp` (B00P / SQTT) specification.

## Layout

```
core/   openrgp_core library (containers, SPM, SQTT decoder, kernel identification, analysis/export)
cli/    openrgp_cli
gui/    openrgp_gui (Qt6)
test/   unit tests; test/data holds small RDNA4 and RDNA2 captures with AMD-verified expected counts
docs/   format spec
re/     reverse-engineering artifacts (decompiled RGP parser fns, Ghidra proj)
tools/  rtd: harness around AMD's rocprof-trace-decoder used as the validation oracle; python helpers
TODO.md / HANDOVER.md   active task list + handover notes
```

## Legal

OpenRGP implements the `.rgp` file format (facts) and re-derives parsing logic
from decompilation; no RGP source is reproduced. The Mesa writer is MIT-licensed.
