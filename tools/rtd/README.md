# tools/rtd: validation oracle (AMD rocprof-trace-decoder 0.1.6)

OpenRGP now decodes SQTT natively (`openrgp_cli waves/kernels/cycles`). This directory keeps the harness used to
validate it against AMD's decoder. `rtd_summary` (build with `./build.sh`, needs the 0.1.6 library) dumps traced
waves as `RTD_DUMP=file`; the native `openrgp_cli waves <rgp> file.d` output has the same shape, so the two can be
diffed. The Python tools (mkisa.py, match.py, analyze.py, cyc.py) are the original prototype of the shader
identification that now lives in core/src/kernels.cpp.

Findings that make this work (RDNA4 / GFX1201, SQTT 3.3):
- Decoder 0.1.6 works. The 0.2 build shipped in the ROCm SDK wheel spins forever on these streams.
- The decoder reports instruction PC = 0 (the wave start address is not in the stream), hence the ISA walk.
- Traced categories: s_delay_alu and s_wait_alu are NOT traced; other s_wait_*, s_clause, s_nop are IMMED(9);
  s_barrier_signal is MESSAGE(11), s_barrier_wait is not traced; s_endpgm is MESSAGE(11); branches are JUMP(7)
  (taken) / NEXT(8, not taken); a stray NEXT can follow exec-writing instructions.
- Only one WGP per shader engine is traced, so wave counts are a sample.
- mkisa.py needs llvm-objdump with gfx1201 support. ISA tables are keyed by code-object order = loader-event order.
