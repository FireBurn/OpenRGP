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
- Kernel identification by ISA walk (RDNA2/3 rules: scratch is VMEM, wave64 doubling, per-stage labels and signatures for multi-stage graphics objects) (`kernels`, `cycles`, `dispatches`), with a trace-signature fallback when
  `llvm-objdump` is unavailable.
- Occupancy and idle-gap analysis; CSV/JSON export; GUI tabs for dispatches, occupancy, timeline, waves (virtual table, no
  row cap), events; decoding runs on a worker thread; screenshot mode.
- AMD_RDF derived SPM counters; RDNA2/3 utilisation-counter tokens.
- Tests: `ctest` runs RDNA4 and RDNA2 decodes against checked-in captures (and RDNA3 via OPENRGP_TEST_RDNA3).

## Open / known limits
- Dispatch boundaries without markers are inferred from a 1,000-cycle pause in wave launches. Tried and rejected: using
  residency (hardware wave limit or observed peak) to ignore pauses while the engine is full. VGPR-limited matmuls
  pause launches with the engine nearly full inside one dispatch, and back-to-back small dispatches pause equally
  full, so the signal cannot separate them. Captures with dispatch markers (the 780M ones) are exact.
- RDNA2/3 VALU instructions issued with an empty exec mask are traced as immediate-class tokens. The kernel matcher
  models this: after an instruction that narrows exec, every VALU up to the next branch or exec restore may be traced
  as either (ClsEither). Consistent with every capture here, but not verified against hardware documentation.
  Two more RDNA2/3 quirks are handled in best_match(): wave64 waves trace each vector instruction twice, and a
  vector-memory instruction can be traced twice.
- AMD_RDF: derived SPM counters are decoded (sampling interval = median sample step). The raw SpmCounterData chunks
  are not: they would need the counter-to-register mapping, and the derived counters carry the same data. The sample
  carries no capture date or wall-clock time anywhere (checked SystemInfo, TraceConfig, TraceProcessInfo), so `info`
  prints "unknown".
- Validation is limited to radv captures, one AMD RDF sample, and RDNA2 graphics on one GPU (4 captures of the same
  app). The RDNA3 test needs a 44 MB capture and only runs when OPENRGP_TEST_RDNA3 is set.
- The oracle (tools/rtd) needs AMD's closed decoder library; only used for validation, never by the product.

## Validation targets
`decode_q8kv_32k_5tok.rgp` (RGP's own log: 246,898 wavefronts, 186 events, 113 compute states): wave count matches
exactly; event and compute-state counts are not comparable because radv traces carry no marker tokens.

## Notes
- Legal: file formats are facts; logic is re-derived from MIT-licensed AMD decoder sources and public specs.
- RGP itself cannot run headless here (bundled Qt lacks the offscreen plugin).
