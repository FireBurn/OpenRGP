# OpenRGP — TODO

Open-source reader for radv SQTT captures (`MESA_VK_TRACE=rgp`) and AMD_RDF files. C++17 core (`openrgp_core`),
CLI (`openrgp_cli`) and a Qt 6 GUI (`openrgp_gui`). See README.md for usage and validation, HANDOVER.md for history.

## Done
- `.rgp` (B00P) container and AMD_RDF container (zstd chunks) into one `Profile`; derived SPM counters.
- Native SQTT decoder for RDNA2/3/4 (token tables layered base -> RDNA3 -> RDNA4; RDNA2/3 time re-sorting through
  a lookahead; per-version field layouts), waves, instructions, exec/wait/stall, other-SIMD instructions, shader data,
  command-processor events (dispatch, cs-partial-flush, cache flush, bottom-of-pipe, trace flush/stall, save-context).
  Validated against AMD rocprof-trace-decoder 0.1.6 on RDNA4, RDNA3 (780M) and RDNA2 (RX 6800M) captures.
- Dispatch table: marker-based when markers exist, otherwise inferred from wave activity.
- Kernel identification by ISA walk (`kernels`, `cycles`, `dispatches`), with a trace-signature fallback when
  `llvm-objdump` is unavailable.
- Occupancy and idle-gap analysis; CSV/JSON export; GUI tabs for dispatches, occupancy, timeline, waves; screenshot mode.
- Tests: `ctest` runs RDNA4 and RDNA2 decodes against checked-in captures (and RDNA3 via OPENRGP_TEST_RDNA3).

## Open
- Kernel identification on RDNA2/3: `classify()` in kernels.cpp encodes which instructions the gfx12 trace omits
  (s_delay_alu, s_wait_alu, s_barrier_wait, exports). RDNA2/3 emit a different set, so most shaders there come back
  "unidentified". Needs per-generation rules; AMD's decoder can print its instruction stream for comparison
  (tools/rtd).
- Dispatch inference is heuristic (1000-cycle launch gap). Real dispatch markers (REG_INIT/user-data) appear in
  captures from other drivers; the marker path exists but is untested beyond the radv captures, which carry few.
- SPM data inside AMD_RDF files (SpmSession/SpmCounterData chunks) is not decoded; `info` lists the chunks only.
- Counters tokens (UTILCTR) are skipped; shader-data tokens are collected but not shown in the GUI.
- GUI decodes on the UI thread (a 44 MB trace takes a few seconds); the Waves tab is capped at 50,000 rows.
- AMD_RDF capture date is not parsed (`info` prints "unknown").
- The oracle (tools/rtd) needs AMD's closed decoder library; only used for validation, never by the product.

## Validation targets
`decode_q8kv_32k_5tok.rgp` (RGP's own log: 246,898 wavefronts, 186 events, 113 compute states): wave count matches
exactly; event and compute-state counts are not comparable because radv traces carry no marker tokens.

## Notes
- Legal: file formats are facts; logic is re-derived from MIT-licensed AMD decoder sources and public specs.
- RGP itself cannot run headless here (bundled Qt lacks the offscreen plugin).
