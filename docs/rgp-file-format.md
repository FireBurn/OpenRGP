# The `.rgp` file format (B00P / SQTT)

This document describes the on-disk format of `.rgp` capture files produced by
the **Mesa radv** Vulkan driver when SQTT (Shader Queue Trace & Timing)
hardware tracing is enabled (`MESA_VK_TRACE=rgp`).

The authoritative writer is the MIT-licensed Mesa code:
- `src/amd/common/ac_rgp.c` — file header, chunks, SPM dump
- `src/amd/common/ac_sqtt.h` — RGP marker structs
- `src/amd/vulkan/tools/radv_sqtt.c`, `src/amd/vulkan/layers/radv_sqtt_layer.c`

OpenRGP re-derives this layout independently; no closed RGP code is used.
(The closed RGP *reader* was studied with Ghidra/frida to decode the SQTT
3.x token stream — see `re/decompiled/`.)

> Note: the newer RGP (2.x) also writes a different container, magic
> `AMD_RDF ` ("Radeon Developer Format"), used by `samples/sample_profile.rgp`.
> That is a separate, larger format and is **not** what Mesa captures use.
> All user captures here are B00P.

## 1. File header (56 bytes)

```
offset  size  field
0x00    4     magic        = 0x50303042 ("B00P", little-endian)
0x04    4     version_major = 1
0x08    4     version_minor = 6
0x0c    4     flags        bit0 = is_semaphore_queue_timing_etw (set)
                           bit1 = no_queue_semaphore_timestamps
0x10    4     chunk_offset = 56 (0x38)
0x14    4     second
0x18    4     minute
0x1c    4     hour
0x20    4     day_in_month
0x24    4     month        (0-based, tm_mon)
0x28    4     year         (tm_year, i.e. years since 1900)
0x2c    4     day_in_week
0x30    4     day_in_year  (0-based)
0x34    4     is_daylight_savings
```

## 2. Chunks

The file is a sequence of chunks starting at `chunk_offset`. Each chunk begins
with a 16-byte header:

```
offset  size  field
0x00    4     id          bit[7:0]=type, bit[15:8]=index, rest reserved
0x04    2     minor_version
0x06    2     major_version
0x08    4     size_in_bytes  (includes this 16-byte header)
0x0c    4     padding
```

Chunk types:

| type | name                     | notes |
|------|--------------------------|-------|
| 0    | ASIC_INFO                | 768 B, GPU description |
| 1    | SQTT_DESC                | 32 B, per shader-engine |
| 2    | SQTT_DATA                | 24 B hdr + raw thread trace, per SE |
| 3    | API_INFO                 | 560 B |
| 4    | RESERVED                 | |
| 5    | QUEUE_EVENT_TIMINGS      | queue info + queue events |
| 6    | CLOCK_CALIBRATION        | CPU/GPU timestamp pairs |
| 7    | CPU_INFO                 | 112 B |
| 8    | SPM_DB                   | raw SPM counters (pre-GFX10) |
| 9    | CODE_OBJECT_DATABASE     | ELF shader blobs |
| 10   | CODE_OBJECT_LOADER_EVENTS| load/unload events |
| 11   | PSO_CORRELATION          | API PSO hash -> pipeline hash |
| 12   | INSTRUMENTATION_TABLE    | |
| 128  | DERIVED_SPM_DB           | named SPM counters + double values (GFX10+) |

Chunk order in Mesa captures:
`CPU_INFO, ASIC_INFO, API_INFO, [CODE_OBJECT_DATABASE], [CODE_OBJECT_LOADER_EVENTS],
[PSO_CORRELATION], [QUEUE_EVENT_TIMINGS], [CLOCK_CALIBRATION...],
(SQTT_DESC + SQTT_DATA)* per SE, (DERIVED_SPM_DB | SPM_DB)`.

### 2.1 CPU_INFO (112 B)
```
+0x10  char vendor_id[16]        e.g. "AuthenticAMD\n"
+0x20  char processor_brand[48]  e.g. "AMD Ryzen 9 8945HS ...\n"
+0x50  u32 reserved[2]
+0x58  u64 cpu_timestamp_freq    = 1e9 (ns ticks)
+0x60  u32 clock_speed           MHz
+0x64  u32 num_logical_cores
+0x68  u32 num_physical_cores
+0x6c  u32 system_ram_size       MB
```
(Strings are copied verbatim from `/proc/cpuinfo`, so they include a trailing
`\n` — trim when displaying.)

### 2.2 ASIC_INFO (768 B)
Key fields (offsets from chunk start):
```
+0x10  u64 flags
+0x18  u64 trace_shader_core_clock  Hz (SCLK at capture)
+0x20  u64 trace_memory_clock       Hz (MCLK at capture)
+0x28  i32 device_id                e.g. 0x7551 (30033) for GFX1201
+0x2c  i32 device_revision_id       e.g. 0xc0 (192)
+0x30  i32 vgprs_per_simd           1536
+0x34  i32 sgprs_per_simd           1728
+0x38  i32 shader_engines           4
+0x3c  i32 compute_unit_per_shader_engine  16
+0x40  i32 simd_per_compute_unit    2
+0x44  i32 wavefronts_per_simd      16
+0x48  i32 minimum_vgpr_alloc       12
+0x4c  i32 vgpr_alloc_granularity   24
+0x50  i32 minimum_sgpr_alloc       108
+0x54  i32 sgpr_alloc_granularity   108
+0x58  i32 hardware_contexts        8
+0x5c  i32 gpu_type                 1=integrated 2=discrete
+0x60  i32 gfxip_level              0x10 = GFXIP_12
...
+0x8c  i64 vram_size                bytes
+0x94  i32 vram_bus_width
+0x98  i32 l2_cache_size
+0x9c  i32 l1_cache_size
+0xa0  i32 lds_size
+0xa4  char gpu_name[256]           e.g. "GFX1201"
...
+0x1a4 u16 cu_mask[32][2]
+0x2a4 u32 gl1_cache_size
+0x2a8 u32 instruction_cache_size
+0x2ac u32 scalar_cache_size
+0x2b0 u32 mall_cache_size
```

### 2.3 API_INFO (560 B)
```
+0x10  u32 api_type        1=Vulkan
+0x14  u16 major_version
+0x16  u16 minor_version
+0x18  u32 profiling_mode  0=present
+0x1c  u32 reserved
+0x20  u8  profiling_mode_data[512]
+0x220 u32 instruction_trace_mode  1=full frame
+0x224 u32 reserved2
+0x228 u8  instruction_trace_data[8]  (shader_engine_filter.mask)
```

### 2.4 SQTT_DESC (32 B) — one per shader engine
```
+0x10  i32 shader_engine_index
+0x14  i32 sqtt_version     0x5=2.2(GFX8) 0x6=2.3(GFX9) 0x7=2.4(GFX10)
                            0xb=3.2(GFX11) 0xc=3.3(GFX12)
+0x18  i16 instrumentation_spec_version  (1)
+0x1a  i16 instrumentation_api_version   (5)
+0x1c  i32 compute_unit_index
```

### 2.5 SQTT_DATA (24 B header + payload) — one per shader engine
```
+0x10  i32 offset   ABSOLUTE file offset of the raw trace payload
+0x14  i32 size     payload bytes
```
The payload is the raw hardware thread trace (see §3).

### 2.6 CODE_OBJECT_DATABASE
```
+0x10  u32 offset
+0x14  u32 flags    = ELF gfxip level
+0x18  u32 size
+0x1c  u32 record_count
then record_count records, each:
   u32 elf_size            (aligned to 4)
   <elf_size bytes of ELF code object>
```

### 2.7 CODE_OBJECT_LOADER_EVENTS
```
+0x10  u32 offset
+0x14  u32 flags
+0x18  u32 record_size  (40)
+0x1c  u32 record_count
then record_count * 40 B records:
   u32 loader_event_type  0=load 1=unload
   u32 reserved
   u64 base_address
   u64 code_object_hash[2]
   u64 time_stamp
```

### 2.8 PSO_CORRELATION
```
+0x10  u32 offset
+0x14  u32 flags
+0x18  u32 record_size  (88)
+0x1c  u32 record_count
then record_count * 88 B records:
   u64 api_pso_hash
   u64 pipeline_hash[2]
   char api_level_obj_name[64]
```

### 2.9 QUEUE_EVENT_TIMINGS
```
+0x10  u32 queue_info_table_record_count
+0x14  u32 queue_info_table_size
+0x18  u32 queue_event_table_record_count
+0x1c  u32 queue_event_table_size
then queue_info records (24 B each):
   u64 queue_id
   u64 queue_context
   u32 hardware_info   queue_type:8 | engine_type:8
   u32 reserved
then queue_event records (56 B each):
   u32 event_type      0=cmdbuf_submit 1=signal_sem 2=wait_sem 3=present
   u32 sqtt_cb_id
   u64 frame_index
   u32 queue_info_index
   u32 submit_sub_index
   u64 api_id
   u64 cpu_timestamp
   u64 gpu_timestamps[2]
```

### 2.10 CLOCK_CALIBRATION — N × 40 B records
```
+0x10  u64 cpu_timestamp
+0x18  u64 gpu_timestamp
+0x20  u64 reserved
```

### 2.11 DERIVED_SPM_DB (GFX10+)
```
+0x10  u32 offset
+0x14  u32 flags
+0x18  u32 num_timestamps
+0x1c  u32 num_groups
+0x20  u32 num_counters
+0x24  u32 num_components
+0x28  u32 sampling_interval
then:
   num_timestamps * u64 timestamps
   num_groups group-records:
      u32 size_in_bytes
      u32 offset (=20)
      u32 group_name_length
      u32 group_description_length
      u32 num_counters
      <name bytes>
      num_counters * u32 counter_ids
   num_counters counter-records:
      u32 size_in_bytes
      u32 offset (=24)
      u32 counter_name_length
      u32 counter_description_length
      u32 num_components
      u8  usage_type
      <name bytes><desc bytes>
      num_components * u32 component_ids
   num_components component-records:
      u32 size_in_bytes
      u32 offset (=20)
      u32 component_name_length
      u32 component_description_length
      u32 usage_type
      <name bytes>
   num_counters * num_timestamps * f64  (counter values)
   num_components * num_timestamps * f64 (component values)
```
On a GFX1201 llama.cpp capture the groups are: Cache (Instruction/Scalar/L0/L2
cache hit), LDS (bank conflict), Memory (bytes) (fetch/write/local-vidmem/PCIe),
Memory (%) (unity busy / unit stalled / write-unit stalled), Ray tracing.

## 3. SQTT 3.x thread-trace token stream

The per-SE payload (SQTT_DATA) is a stream of hardware trace entries. On GFX12
(SQTT 3.3) the stream is **compressed**: a sequence of 16-bit words where a
16-bit "header" at an odd word position is bit-packed across two words.

RGP decodes this with a state machine (function `AdvanceParser2X` in
`RadeonGPUProfiler`, decompiled in `re/decompiled/AdvanceParser2X.c`). Key facts:

- Parser `position` advances so that the byte offset of the current header is
  `position / 2`. A correct parse consumes exactly `size` bytes (position ends
  at `2*size`).
- 16-bit header at word position `pos`:
  - even pos: `u16 at byte (pos/2)`
  - odd pos:  `((u16 at byte (pos/2+2)) & 0xf) << 12 | (u16 at byte (pos/2)) >> 4`
- Low nibble of the header = **entry type** (0..15).
- Entry type → token type map (RGP `.rodata`):
  `[0,1,2,3,4,2,6,7,7,7,10,11,12,13,14,2]`
- Entry type → position advance (words):
  `[2,8,8,4,2,6,2,2,2,2,2,8,6,4,8,6]`
- 48-bit real-time timestamps are read as a plain little-endian 6-byte value
  (8 bytes shifted right 4 when the position is odd).

Entry types (partially decoded):
- **0** — wavefront-related. If `(hdr>>13)==1` it is a *wavefront start*: the
  parser scans forward for a word whose low nibble is 1 and reads a 48-bit
  timestamp there (this establishes the running timestamp base). Otherwise the
  entry contributes `(hdr>>2)&0x3fc` to the accumulated offset.
- **1** — timestamped token; carries a 48-bit timestamp.
- **2** — carries a u16 + u32 payload (wavefront/context related).
- **3** — carries a u32 payload; complex decode (wavefront header / instruction).
- **4,6** — header-only tokens.
- **5** — carries a u32 payload.
- **7,8,9** — header-only; when `(hdr>>10)==0x35` the entry is a
  `THREAD_TRACE_MARKER` (a hardware marker event). `0x35` is the SQ event
  `THREAD_TRACE_MARKER` (see RGP's event-name table: 0x33=THREAD_TRACE_START,
  0x34=THREAD_TRACE_STOP, 0x35=THREAD_TRACE_MARKER, 0x36=FLUSH, 0x37=FINISH).
- **10** — generic instruction; size from `GetSizeFromInstructionType`
  (type 17..19 → 4 dwords, ≥20 → 8 dwords).
- **11 (0xb)** — carries a 48-bit timestamp.
- **13 (0xd)** — context-register nibbles.
- **15 (0xf)** — context register (uses `RgpGcnRegisterGetAddress(0x209, ver)`).

### RGP name tables (extracted from the binary)
- **Event (SQ event) names** (0..0x3e): … 0x33 THREAD_TRACE_START,
  0x34 THREAD_TRACE_STOP, 0x35 THREAD_TRACE_MARKER, 0x36 THREAD_TRACE_FLUSH,
  0x37 THREAD_TRACE_FINISH …
- **Stage names** (0..10): PS, VS, GS, ES, HS, LS, CS, PS1, PS2, PS3, VS
- **Sync event names**: 0=DRAW_DONE 1=FLUSH_DFSM 2=NULL else MARKER
- **Issue type names**: 0=NULL 1=INST 2=STALL else INST

### RGP marker structs (from Mesa `ac_sqtt.h`)
The *driver* writes these as SQTT user-data (2 dwords per packet). They are the
semantic events RGP shows (draws/dispatches, barriers, CB start/end, etc.):
- `rgp_sqtt_marker_cb_start` (16 B): identifier=1, cb_id, queue, device id, queue flags
- `rgp_sqtt_marker_cb_end` (12 B): identifier=2
- `rgp_sqtt_marker_event` (12 B): identifier=0, api_type (EventCmdDispatch=6, …),
  cb_id, cmd_id
- `rgp_sqtt_marker_event_with_dims` (24 B): + thread_x/y/z (per-dispatch)
- `rgp_sqtt_marker_barrier_start` (8 B): identifier=3, driver_reason
- `rgp_sqtt_marker_barrier_end` (8 B): identifier=4, flush bits, num_layout_transitions
- `rgp_sqtt_marker_user_event` (4 B): identifier=5, data_type (push/pop)
- `rgp_sqtt_marker_general_api` (4 B): identifier=6, api_type
- `rgp_sqtt_marker_pipeline_bind` (12 B): identifier=0xC, bind_point, pso hash

## 4. Ground-truth validation targets

RGP's own log for `decode_q8kv_32k_5tok.rgp` (35 MB, GFX1201) reports:
```
Events         : 186 @ 1048 B
Compute State  : 113 @ 368 B
Register State : 186 @ 9280 B
Wavefronts     : 246898 @ 24 B
Barriers       : 73 @ 88 B
Command Buffers: 4 @ 56 B
Context Ops    : 1904 @ 12 B
Persistent Ops : 21792 @ 12 B
Queue Timings  : 1 @ 80 B
Pipeline Info  : 1471212 B
```
OpenRGP currently matches: container layout, ASIC/CPU/API fields, queue-event
count (1), derived-SPM counters, and full SQTT token-stream consumption.
Matching the per-category event/wavefront counts is the next milestone (requires
decoding how RGP's event processor correlates tokens into events — see TODO.md).
