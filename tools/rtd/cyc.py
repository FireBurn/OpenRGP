#!/usr/bin/env python3
"""cyc.py work_dir sig_prefix : attribute wave cycles to instruction mnemonics for one kernel (by ISA signature)."""
import sys,collections,hashlib
wd,want=sys.argv[1:3]
tot=collections.Counter(); cnt=collections.Counter(); stall=collections.Counter(); nw=0; ntot=0
for n in range(4,13):
    d=f'{wd}/isa{n}'; wf=f'{wd}/w{n}.txt'
    sys.argv=['m',d,wf]; ns={}; exec(open('/home/fireburn/AI/OpenRGP/tools/rtd/match.py').read().split("groups=collections")[0],ns)
    cos=ns['cos']; walk=ns['walk']; JUMP,NEXT=7,8; target=ns['target']
    txt=collections.defaultdict(list)
    for l in open(f'{d}/isa.txt'):
        c,off,sz,t=l.rstrip('\n').split('\t',3); txt[int(c)].append(t)
    sig={c:hashlib.md5(' '.join(ts).encode()).hexdigest()[:8] for c,ts in txt.items()}
    cand=[c for c in cos if sig[c].startswith(want)]
    if not cand: continue
    ds=open(f'{wd}/w{n}.txt.d').read().split('\n')
    for li,l in enumerate(open(wf)):
        h,t=l.split(' :'); tr=[int(x) for x in t.split()]
        c=max(cand,key=lambda c:walk(c,tr))
        if walk(c,tr)<len(tr)*0.95: continue
        dur=[tuple(int(y) for y in x.split(',')) for x in ds[li].split(':',1)[1].split()]
        ins=cos[c]; idx={o:i for i,(o,_,_,_) in enumerate(ins)}; i=0;k=0
        while k<len(tr) and i<len(ins):
            off,sz,cl,tx=ins[i]
            if cl=='skip': i+=1; continue
            if cl=='end': break
            tk=tr[k]
            if tk==NEXT and cl!='cb': k+=1; continue
            m=tx.split()[0]; m=m.replace('_e32','').replace('_e64','')
            tot[m]+=dur[k][0]; stall[m]+=dur[k][1]; cnt[m]+=1
            if cl in (JUMP,'cb'):
                tg=target(off,sz,tx); i=idx[tg] if (tk==JUMP and tg in idx) else i+1
            else: i+=1
            k+=1
        nw+=1; ntot+=sum(x[0] for x in dur)
print(f'{nw} waves, {ntot} instruction-cycles total')
print(f"{'mnemonic':32s} {'count':>7s} {'cycles':>9s} {'%':>5s} {'stall%of':>8s} {'cyc/inst':>8s}")
for m,v in tot.most_common(16): print(f'{m:32s} {cnt[m]:7d} {v:9d} {100*v/ntot:5.1f} {100*stall[m]/max(v,1):8.0f} {v/cnt[m]:8.1f}')
