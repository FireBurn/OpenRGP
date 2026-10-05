import struct, sys

CHUNK_NAMES = {0:"ASIC_INFO",1:"SQTT_DESC",2:"SQTT_DATA",3:"API_INFO",4:"RESERVED",5:"QUEUE_EVENT_TIMINGS",6:"CLOCK_CALIBRATION",7:"CPU_INFO",8:"SPM_DB",9:"CODE_OBJECT_DATABASE",10:"CODE_OBJECT_LOADER_EVENTS",11:"PSO_CORRELATION",12:"INSTRUMENTATION_TABLE",128:"DERIVED_SPM_DB"}

fn = sys.argv[1]
data = open(fn,'rb').read()
print(f"file size: {len(data):#x} ({len(data)} bytes)")
magic, vmaj, vmin, flags, chunk_off, sec, min_, hr, dom, mon, yr, dow, doy, dst = struct.unpack_from("<IIIIiiiiiiiiii", data, 0)
print(f"magic={magic:#010x} ver={vmaj}.{vmin} flags={flags:#x} chunk_offset={chunk_off}")
print(f"time: {1900+yr}-{mon+1:02d}-{dom:02d} {hr:02d}:{min_:02d}:{sec:02d} dow={dow} doy={doy} dst={dst}")

off = chunk_off
i = 0
while off + 16 <= len(data):
    cid, minor, major, size, pad = struct.unpack_from("<IHHii", data, off)
    ctype, cindex = cid & 0xFF, (cid >> 8) & 0xFF
    name = CHUNK_NAMES.get(ctype, f"UNKNOWN({ctype})")
    print(f"[{i:2d}] off={off:#010x} type={ctype:3d} {name:24s} idx={cindex} ver={major}.{minor} size={size:#x} ({size})")
    if size <= 0 or off + size > len(data) + 64:
        print("   !! bad size, stopping")
        break
    off += size
    i += 1
