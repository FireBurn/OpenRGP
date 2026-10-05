#!/usr/bin/env python3
"""mkisa.py file.rgp out_dir : extract code objects, disassemble, write isa.txt (co offset size text) + cos.txt (co lines wmma dot4 name)"""
import sys,struct,subprocess,os,re
f,out=sys.argv[1:3]; os.makedirs(out,exist_ok=True)
b=open(f,'rb').read()
isa=open(f'{out}/isa.txt','w'); cos=open(f'{out}/cos.txt','w')
starts=[m.start() for m in re.finditer(b'\x7fELF',b)]
for i,s in enumerate(starts):
    shoff=struct.unpack_from('<Q',b,s+0x28)[0]; shentsize,shnum=struct.unpack_from('<HH',b,s+0x3a)
    end=s+shoff+shentsize*shnum
    p=f'{out}/co{i}.elf'; open(p,'wb').write(b[s:end])
    t=subprocess.run(['llvm-objdump','-d','--mcpu=gfx1201','--triple=amdgcn--amdpal',p],capture_output=True,text=True).stdout
    n=wm=dt=0; name='?'
    for l in t.split('\n'):
        m=re.match(r'<(\S+)>:',l.split(' ',1)[-1]) if l and not l.startswith('\t') else None
        if m and name=='?': name=m.group(1)
        m=re.match(r'\t(.*?)\s*// ([0-9A-F]+): ([0-9A-F ]+?)(?: <[^>]*\+0x([0-9a-f]+)>)?$',l)
        if not m: continue
        txt,addr,hexs,tg=m.groups(); sz=4*len(hexs.split())
        if tg: txt=txt+' @'+str(int(tg,16))
        isa.write(f'{i}\t{int(addr,16)}\t{sz}\t{txt.strip()}\n'); n+=1
        wm+= 'wmma' in txt; dt+= 'dot4' in txt
    cos.write(f'{i}\t{n}\t{wm}\t{dt}\t{name}\n')
    os.remove(p)
