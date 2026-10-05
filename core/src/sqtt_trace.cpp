#include "openrgp/sqtt_trace.h"
#include <cstring>

namespace openrgp {

// entry-type -> token-type (RGP .rodata CSWTCH_421)
const uint32_t kSqttTokenTypeMap[16] = {0,1,2,3,4,2,6,7,7,7,10,11,12,13,14,2};
// entry-type -> words to advance (RGP .rodata CSWTCH_425)
const uint32_t kSqttTokenAdvance[16] = {2,8,8,4,2,6,2,2,2,2,2,8,6,4,8,6};

namespace {
uint16_t rd16(const uint8_t* p){ uint16_t v; std::memcpy(&v,p,2); return v; }
uint32_t rd32(const uint8_t* p){ uint32_t v; std::memcpy(&v,p,4); return v; }

// 48-bit little-endian from 6 bytes
uint64_t rd48(const uint8_t* p){
    return (uint64_t)p[0] | (uint64_t)p[1]<<8 | (uint64_t)p[2]<<16 |
           (uint64_t)p[3]<<24 | (uint64_t)p[4]<<32 | (uint64_t)p[5]<<40;
}

// SQTT 3.x 16-bit header at word position `pos` (bit-packed when odd).
uint16_t hdr16(const uint8_t* base, uint32_t pos){
    uint32_t par = pos & 1;
    const uint8_t* p = base + (pos >> 1);
    uint16_t lo = rd16(p);
    if(!par) return lo;
    uint16_t hi = rd16(p + 2);
    return (uint16_t)(((hi & 0xf) << 12) | (lo >> 4));
}
// SQTT 3.x 32-bit value at word position `pos` + byteoff, bit-packed when odd.
uint32_t val32(const uint8_t* base, uint32_t pos, uint32_t byteoff){
    uint32_t par = pos & 1;
    const uint8_t* p = base + (pos >> 1) + byteoff;
    uint32_t lo = rd32(p) >> (4*par);
    if(!par) return lo;
    return ((rd32(p + 4) & 0xf) << 28) | lo;
}
// SQTT 3.x 48-bit timestamp at word position `pos` + byteoff.
uint64_t ts48(const uint8_t* base, uint32_t pos, uint32_t byteoff){
    uint32_t par = pos & 1;
    const uint8_t* p = base + (pos >> 1) + byteoff;
    uint64_t v = rd48(p);
    if(par) v = (v | ((uint64_t)(p[6] & 0xf) << 48)) >> 4;
    return v;
}
} // namespace

bool SqttParser::init(const uint8_t* d, uint32_t sz, uint32_t bias_, uint32_t se_,
                      uint32_t major_, uint32_t minor_, uint32_t ver_){
    data = d; size = sz; bias = bias_; se = se_;
    major = major_; minor = minor_; version = ver_;
    pos = 0; acc = 0; ts_delta = 0; ts_ready = 0; ctx_regs = 0;
    return d != nullptr && sz > 1 && (sz % 2 == 0);
}

bool SqttParser::advance(SqttToken& t){
    t = SqttToken{};
    const uint8_t* base = data + bias;
    uint32_t pos = this->pos;
    uint32_t size = this->size;
    uint32_t bias = this->bias;
    uint32_t major = this->major;
    uint32_t ts_ready = this->ts_ready;

    uint16_t hdr;
    if(major < 3){
        if(size < pos + 2 + bias) return false;
        hdr = rd16(base + pos);
    } else {
        uint32_t par = pos & 1;
        if(size < (pos >> 1) + 2 + bias + par*2) return false;
        hdr = hdr16(base, pos);
    }
    uint32_t etype = hdr & 0xf;
    uint32_t ttype = kSqttTokenTypeMap[etype];

    if(etype == 0){
        if((hdr >> 13) == 1){
            // wavefront start: scan forward for a word whose low nibble == 1
            uint64_t ts = 0; bool found = false;
            uint32_t scan = pos; uint32_t step = 2;
            for(int guard=0; guard<100000; guard++){
                scan += step;
                uint16_t u25;
                if(major < 3){
                    if(size < scan + 2 + bias) break;
                    u25 = rd16(base + scan);
                } else {
                    uint32_t par = scan & 1;
                    if(size < par*2 + (scan>>1) + 2 + bias) break;
                    u25 = hdr16(base, scan);
                }
                if((u25 & 0xf) == 1){
                    if(major < 3){
                        if(size < scan + 8 + bias) break;
                        ts = rd48(base + scan + 2);
                    } else {
                        uint32_t par = scan & 1;
                        if(size < (scan>>1) + 8 + bias + par) break;
                        ts = ts48(base, scan, 2);
                    }
                    found = true; break;
                }
                step = kSqttTokenAdvance[u25 & 0xf];
            }
            if(!found) return false;
            if(ts_ready == 0){ ts_delta = ts; ts_ready = 1; acc = 0; }
            else { acc = ts - ts_delta; }
            t.type = ttype;
            t.timestamp = acc;
            t.position = bias + pos;
            t.se = se;
            t.f20 = (hdr >> 12) & 1;
            t.f1c = hdr >> 13;
            t.header = hdr;
            this->ts_ready = ts_ready; this->ts_delta = ts_delta; this->acc = acc;
            this->pos = pos + kSqttTokenAdvance[etype];
            return true;
        } else {
            acc += (hdr >> 2) & 0x3fc;
            t.type = ttype;
            if(ts_ready != 0){
                t.timestamp = acc;
                t.position = bias + pos;
                t.se = se;
                t.f20 = (hdr >> 12) & 1;
                t.f1c = hdr >> 13;
            }
            t.header = hdr;
            this->acc = acc;
            this->pos = pos + kSqttTokenAdvance[etype];
            return true;
        }
    }

    if(etype == 1){
        t.type = 1;
        if(ts_ready != 0){
            t.timestamp = acc;
            t.position = bias + pos;
            if(major < 3){
                if(size < bias + pos + 8) return false;
                t.f20 = (uint32_t)rd48(base + pos + 2);
            } else {
                uint32_t par = pos & 1;
                if(size < (pos>>1) + 8 + bias + par) return false;
                t.f20 = (uint32_t)ts48(base, pos, 2);
            }
            t.se = se;
            t.f28 = 0;
        }
        t.header = hdr;
        this->pos = pos + kSqttTokenAdvance[etype];
        return true;
    }

    // types 2..0xf
    uint64_t lvar13 = acc + (((hdr >> 4) & 1) << 2);
    acc = lvar13;
    t.type = ttype;
    if(ts_ready == 0){
        t.header = hdr;
        this->acc = acc;
        this->pos = pos + kSqttTokenAdvance[etype];
        return true;
    }

    switch(etype){
    case 2: {
        uint16_t u25; uint32_t u18;
        if(major < 3){
            if(size < bias+pos+4) return false;
            u25 = rd16(base + pos + 2);
            if(size < bias+pos+8) return false;
            u18 = rd32(base + pos + 4);
        } else {
            u25 = hdr16(base, pos + 4);   // byteoff 2 in words
            if(size < (pos>>1) + 8 + bias + (pos&1)*2) return false;
            u18 = val32(base, pos, 4);
        }
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.f2c = u18;
        t.f28 = u25;
        t.f30 = 0;
        t.se = se;
        t.f1c = (hdr >> 7) & 0x3f;   // CONCAT24(hdr>>7, se) low
        t.f20 = (hdr >> 5) & 3;
        t.f24 = 0;
        t.f38 = (hdr >> 9) & 1;
        t.f34 = (hdr >> 15) & 1;
        break;
    }
    case 3: {
        uint32_t u18;
        if(major < 3){
            if(size < bias+pos+4) return false;
            u18 = rd32(base + pos);
        } else {
            u18 = val32(base, pos, 0);
        }
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        uint32_t hi = u18 >> 16;
        uint32_t a, b, c;
        if((u18 & 0x100000) == 0){
            a = 6; b = hi & 3; c = ((hi >> 2) & 3) + 1;
        } else {
            a = hi & 7; b = 0; c = (u18 >> 19) & 1;
        }
        t.f28 = (u18 >> 10) & 0xf;
        t.f3c = (u18 >> 22) & 0x7f;
        t.f2c = a;
        t.f40 = 0;
        t.f1c = (u18 >> 5) & 0x3f;
        t.f20 = ((u18 >> 6) & 0xf) | (((u18 >> 14) & 0xf) << 28);
        t.f30 = ((uint64_t)c << 32) | b;
        break;
    }
    case 4:
    case 6: {
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f1c = (hdr >> 5) & 0x3f;
        t.f20 = (hdr >> 6) & 0xf;
        t.f28 = (hdr >> 10) & 0xf;
        break;
    }
    case 5: {
        uint32_t u18;
        if(major < 3){
            if(size < bias+pos+8) return false;
            u18 = rd32(base + pos + 4);
        } else {
            u18 = val32(base, pos, 4);
        }
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f28 = (hdr >> 9) & 0x3f;
        t.f2c = u18;
        t.f20 = (hdr >> 5) & 3;
        t.f24 = 1;
        t.f30 = 1; t.f34 = 1;
        t.f38 = 0;
        t.f1c = (hdr >> 7) & 0x3f;
        break;
    }
    case 7: {
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        uint32_t h6 = hdr >> 6;
        uint32_t f28v, f2cv, f30v;
        if((hdr & 0x200) == 0){ f28v = h6 & 7; f2cv = 0; f30v = 0; }
        else { f28v = 6; f30v = h6 & 3; f2cv = ((h6 & 0xf) >> 2) + 1; }
        t.f2c = f2cv;
        t.f30 = f30v;
        t.f28 = f28v;
        t.f20 = 0;
        t.f1c = (hdr >> 5) & 0x3f;
        if((hdr >> 10) == 0x35){ t.f24 = 0; t.f34 = 1; }
        else { t.f24 = (hdr >> 10) & 0x3f; t.f34 = 0; }
        t.f38 = 0;
        break;
    }
    case 8: {
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f28 = 6;
        t.f24 = (hdr >> 10) & 0x3f;
        t.f1c = (hdr >> 5) & 0x3f;
        t.f20 = 2;
        t.f2c = (hdr >> 6) & 0x3fffffff;
        t.f30 = (((hdr >> 6) & 0xf) >> 2) + 1;
        if((hdr >> 10) == 0x35){ t.f24 = 0; t.f34 = 1; }
        else t.f34 = 0;
        t.f38 = 0;
        break;
    }
    case 9: {
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f20 = 1;
        t.f1c = (hdr >> 5) & 0x3f;
        t.f28 = (hdr >> 7) & 7;
        t.f24 = (hdr >> 10) & 0x3f;
        if((hdr >> 10) == 0x35){ t.f24 = 0; t.f34 = 1; }
        else t.f34 = 0;
        break;
    }
    case 10: {
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f1c = (hdr >> 9) & 0x3f;
        t.f20 = (hdr >> 5) & 0xf;
        t.f2c = (hdr >> 11) & 0x3f;
        t.f28 = (hdr >> 11) & 0x3f;  // generic instruction type (placeholder)
        t.f24 = instTypeSize(t.f28);
        break;
    }
    case 0xb: {
        uint64_t ts;
        if(major < 3){
            if(size < bias+pos+8) return false;
            ts = rd48(base + pos + 2);
        } else {
            uint32_t par = pos & 1;
            if(size < (pos>>1) + 8 + bias + par) return false;
            ts = ts48(base, pos, 2);
        }
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f1c = (hdr >> 9) & 0x3f;
        t.f20 = (hdr >> 5) & 0xf;
        t.f28 = (uint32_t)((ts * 4 & 0xffffffffffffULL) | (hdr >> 14));
        break;
    }
    case 0xd: {
        uint16_t u23;
        if(major < 3){
            if(size < bias+pos+4) return false;
            u23 = rd16(base + pos + 2);
        } else {
            u23 = hdr16(base, pos + 4);
        }
        uint32_t u18 = (u23 << 16) | (hdr & 0xffff);
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f1c = (u18 >> 5) & 0x3f;
        t.f20 = 0; t.f28 = 0; t.f2c = 0;
        // context register nibbles
        uint32_t v = u18 >> 8;
        for(uint32_t i=0;i<ctx_regs && i<16;i++){ t.f24 = v & 3; v >>= 2; }
        break;
    }
    case 0xf: {
        uint32_t u18;
        if(major < 3){
            if(size < bias+pos+6) return false;
            u18 = rd32(base + pos + 2);
        } else {
            u18 = val32(base, pos, 2);
        }
        t.timestamp = lvar13;
        t.position = bias + pos;
        t.se = se;
        t.f2c = u18;
        t.f24 = 1;
        t.f38 = 0;
        t.f28 = (hdr >> 9) & 0x3f;
        t.f1c = (hdr >> 5) & 0x3f;
        t.f30 = 0; t.f34 = 1;
        break;
    }
    default:
        break;
    }
    t.header = hdr;
    this->acc = acc;
    this->pos = pos + kSqttTokenAdvance[etype];
    return true;
}

std::vector<SqttToken> tokenize(const uint8_t* data, uint32_t size,
                                uint32_t se, uint32_t major, uint32_t minor, uint32_t version){
    std::vector<SqttToken> toks;
    SqttParser p;
    if(!p.init(data, size, 0, se, major, minor, version)) return toks;
    SqttToken t;
    int guard = 0;
    while(p.advance(t) && guard++ < 100000000){
        toks.push_back(t);
    }
    return toks;
}

} // namespace openrgp
