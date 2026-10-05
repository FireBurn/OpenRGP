# OpenRGP — HANDOVER

Last updated: 2026-10-05 (session 3: RDNA2/3 decoding, events, AMD_RDF, analysis/export, GUI tabs; see TODO.md)

## What is OpenRGP
Open-source reimplementation of AMD's closed-source **Radeon GPU Profiler (RGP)**,
targeting `.rgp` capture files produced by the **Mesa radv** Vulkan driver
(`MESA_VK_TRACE=rgp` + SQTT hardware tracing). The user (fireburn) profiles
llama.cpp (Qwen3.8-27B DFlash speculative decode) on a **Ryzen AI Max+ 395
(Strix Halo, GFX1201, 4 SE x 16 CU x 2 SIMD, 64 GB LPDDR5X)** using per-submit
captures with a local Mesa patch.

**Language: C++17 + Qt 6** (user approved C++/Qt6 since RGP is a Qt6 app;
original ask was Rust). Three deliverables:
- `openrgp_core` — plain C++ library (no Qt): container parser, SPM, SQTT tokenizer
- `openrgp_cli` — CLI: see README.md (info, spm, tokens, dump, waves, dispatches, events, kernels, cycles, occupancy, gaps, export)
- `openrgp_gui` — Qt6 Widgets GUI: Summary, Dispatches, Occupancy, Timeline, Waves, SPM, Tokens

## Quick start (the sections below are older session notes; README.md and TODO.md are current)
```
cd ~/AI/OpenRGP
cmake -B build -G Ninja && cmake --build build
./build/openrgp_cli info   <file.rgp>
./build/openrgp_cli spm    <file.rgp>
./build/openrgp_cli tokens <file.rgp>
./build/openrgp_cli dump   <file.rgp> -n 100 -se 0
QT_QPA_PLATFORM=offscreen ./build/openrgp_gui <file.rgp>   # headless test
ctest --test-dir build          # container walk test
```
Verified on all 14 user captures + correct derived-SPM counter names.

## What works (tested)
1. **Container parse** (B00P v1.6): header, CPU_INFO, ASIC_INFO, API_INFO,
   CODE_OBJECT_DATABASE, CODE_OBJECT_LOADER_EVENTS, PSO_CORRELATION,
   QUEUE_EVENT_TIMINGS, CLOCK_CALIBRATION, per-SE SQTT_DESC/SQTT_DATA,
   DERIVED_SPM_DB. See `docs/rgp-file-format.md` (full spec).
2. **Derived SPM counters**: decode group/counter/component names + double
   values. On GFX1201 captures: Cache (Instr/Scalar/L0/L2 hit), LDS bank
   conflict, Memory bytes (fetch/write/local-vidmem/PCIe), Memory %, Ray tracing.
3. **SQTT 3.x tokenizer**: reimplementation of RGP's `AdvanceParser2X`.
   Consumes each per-SE trace buffer exactly. Produces a token stream with
   type + decoded fields. (Token→event correlation is the next milestone.)

## Key locations
| Thing | Path |
|---|---|
| Project | `~/AI/OpenRGP/` |
| RGP install (v2.7.0.32, NOT stripped) | `~/AI/llama-deep/rgp/dl/x/RadeonDeveloperToolSuite-2026-05-28-1806/` |
| RGP binary | `.../RadeonGPUProfiler` (16.5 MB) |
| Sample profile (AMD_RDF format) | `.../samples/sample_profile.rgp` |
| User's B00P captures | `~/AI/llama-deep/rgp/decode_94k/*.rgp` (13), `~/AI/llama-deep/rgp/decode_q8kv_32k_5tok.rgp` |
| RGP settings/log (ground truth) | `~/.RadeonGPUProfiler/rgp_settings.xml`, `rgp_log_file.txt` |
| Mesa source (format spec) | `~/AI/llama-deep/fozdb/wt/licm2/src/amd/common/ac_rgp.c`, `ac_sqtt.h`, `src/amd/vulkan/tools/radv_sqtt.c`, `src/amd/vulkan/layers/radv_sqtt_layer.c` |
| Capture script | `~/AI/llama-deep/rgp/capture.sh` |
| Ghidra 12.1.4 | `~/ghidra_12.1.4_PUBLIC` (Java 25) |
| Ghidra project | `~/AI/OpenRGP/re/ghidra/rgp_proj` |
| Decompiled RGP parser fns | `~/AI/OpenRGP/re/decompiled/*.c` |
| frida 17.22 | `~/re-tools-venv/bin/frida` |
| Chunk walker (python) | `~/AI/OpenRGP/tools/walk_chunks.py` |

## How the SQTT 3.x token format works (decoded)
- Per-SE trace = compressed stream of 16-bit words. Parser `position` advances
  so header byte offset = `position/2`. Exact parse consumes `size` bytes.
- 16-bit header: low nibble = entry type (0..15).
  - even pos: `u16 at byte pos/2`
  - odd pos: `((u16 at byte pos/2+2)&0xf)<<12 | (u16 at byte pos/2)>>4`
- entry→token type map: `[0,1,2,3,4,2,6,7,7,7,10,11,12,13,14,2]`
- entry→advance(words): `[2,8,8,4,2,6,2,2,2,2,2,8,6,4,8,6]`
- 48-bit timestamps = plain LE 6-byte read (8 bytes >>4 when pos odd).
- Entry types: 0=wavefront (start if hdr>>13==1, scans for ts), 1=timestamped,
  2=u16+u32 payload, 3=u32 payload (wavefront header), 4/6=header-only,
  5=u32 payload, 7/8/9=header-only (marker if (hdr>>10)==0x35),
  10=instruction, 11=timestamp, 13/15=context registers.
- `0x35` = THREAD_TRACE_MARKER SQ event (0x33 START, 0x34 STOP, 0x36 FLUSH, 0x37 FINISH).
- RGP name tables extracted: event names (0..0x3e), stage names
  (PS,VS,GS,ES,HS,LS,CS,PS1,PS2,PS3,VS), sync (DRAW_DONE/FLUSH_DFSM/NULL/MARKER),
  issue (NULL/INST/STALL).
- Driver markers (from Mesa ac_sqtt.h): cb_start(16B,id=1), cb_end(12B,id=2),
  event(12B,id=0,api_type; Dispatch=6), event_with_dims(24B), barrier_start(8B,id=3),
  barrier_end(8B,id=4), user_event(4B,id=5), general_api(4B,id=6),
  pipeline_bind(12B,id=0xC). Written 2 dwords/packet.

## RGP binary RE notes
- `nm` shows all symbols (not stripped). Key fns (see re/decompiled/):
  `RgpSqttParserInitialize`@0xbe5d40, `AdvanceParser2X`@0xbe6380 (core loop),
  `RgpSqttParserAdvance`@0xbe7c80, `RgpInstSequencerUpdate`@0xb97910,
  `RgpEventProcessorAddEvent`@0xb6d250, `ParseValuInst3X`@0xbe5ec0,
  `RgpDataSetLoaderPopulateDataSet`@0xb4b0a0 (main load; calls Initialize per SE).
- Initialize args (from decompiled PopulateDataSet):
  (parser, data, dataset, bias=0, size, logical_se, sqtt_major, sqtt_minor,
   dataset+0x104, 0, dataset+0x124, dataset+0x130, double clock_ratio=xmm0).
- PIE VA→file offset for .rodata: `file_off = va - 0xdee000 + 0x9ef000`.
- RGP can't run headless here (bundled Qt 6.7 has no offscreen plugin; system
  Qt 6.12 plugins ABI-incompatible). For live ground truth: dlopen the exe and
  call parser fns directly, or frida under a headless compositor.

## Open questions / next
- How RGP's event processor correlates tokens into events/wavefronts
  (to match RGP log counts: 186 events, 246898 wavefronts, etc.).
- Exact per-field meaning of decoded token fields (f1c/f20/f24/f28/f2c/…).
- How driver user-data marker dwords are reassembled from THREAD_TRACE_MARKER.
- AMD_RDF container structure (secondary).

## How to resume
1. `cat TODO.md` — active list (next = token→event correlation).
2. Build: `cmake -B build -G Ninja && cmake --build build`.
3. Test: `./build/openrgp_cli info|spm|tokens <capture>`.
4. Ghidra: `~/ghidra_12.1.4_PUBLIC/support/analyzeHeadless rgp_proj 1 -process
   RadeonGPUProfiler -postScript <script>.java -scriptPath ~/AI/OpenRGP/re/ghidra`
   (project already imported; see re/ghidra/DecompileSqtt.java as a template).
5. frida: `~/re-tools-venv/bin/frida` (needs a running RGP; see headless notes).

## Session 2 addendum (2026-10-04): native decode finished
- `core/src/sqtt_decode.cpp`: GFX12 SQTT -> waves (start/end, per-instruction category/time/duration/stall, exec/wait/stall).
- `core/src/kernels.cpp`: shader identification by walking llvm-objdump disassembly along traced categories; `kernels`/`cycles` CLI.
- Validation: tools/rtd (AMD decoder 0.1.6 as oracle) -> 2573/2573 waves identical on the 9 decode_94k captures with waves.
- Reference source copy: re/amd-src (MIT, AMD). HEAD of it desyncs on radv streams; see TODO.md for the three differences.
- Known limits: radv streams carry no wave start PC / dispatch markers, so kernels are identified by ISA walk (a wave that
  matches no code object is reported "unidentified"); only one WGP per SE is traced; GFX12 only; GUI has no wave views yet.
