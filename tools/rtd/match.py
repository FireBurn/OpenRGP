#!/usr/bin/env python3
"""match.py isa_dir waves.txt : identify which code object each wave group ran by walking ISA along traced instruction categories."""
import sys,re,collections
d,wf=sys.argv[1:3]
SMEM,SALU,VMEM,FLAT,LDS,VALU,JUMP,NEXT,IMMED,MSG=1,2,3,4,5,6,7,8,9,11
H=dict(delay=0,walu=0,wait=1,nop=1,clause=1,bwait=0)
def cls(t):
    m=t.split()[0]
    if m=='s_branch': return JUMP
    if m.startswith('s_cbranch') : return 'cb'
    for pre,key in (('s_delay','delay'),('s_wait_alu','walu'),('s_wait','wait'),('s_nop','nop'),('s_clause','clause')):
        if m.startswith(pre): return IMMED if H[key] else 'skip'
    if m=='s_barrier_signal' or m=='s_barrier_signal_isfirst': return MSG
    if m=='s_barrier_wait': return {0:'skip',1:IMMED,2:MSG}[H.get('bwait',1)]
    if m.startswith(('s_barrier','s_sleep','s_setprio','s_code_end','s_icache','s_inst_prefetch','s_trap','s_set_inst')): return IMMED
    if m.startswith(('s_load','s_buffer_load','s_prefetch')): return SMEM
    if m.startswith(('s_sendmsg','s_ttrace','s_message')): return MSG
    if m=='s_endpgm': return 'end'
    if m.startswith('s_'): return SALU
    if m.startswith('ds_'): return LDS
    if m.startswith(('flat_','scratch_')): return FLAT
    if m.startswith(('global_','buffer_','image_','tbuffer_')): return VMEM
    return VALU
raw=[l.rstrip('\n').split('\t',3) for l in open(f'{d}/isa.txt')]
def load():
    global cos
    cos=collections.defaultdict(list)
    for c,off,sz,t in raw: cos[int(c)].append((int(off),int(sz),cls(t),t))
load()
names={}
for l in open(f'{d}/cos.txt'):
    p=l.split('\t'); names[int(p[0])]=(int(p[1]),int(p[2]),int(p[3]))
def target(off,sz,t):
    m=re.search(r'@(\d+)$',t)
    if m: return int(m.group(1))
def walk(co,trace):
    ins=cos[co]; idx={o:i for i,(o,_,_,_) in enumerate(ins)}
    i=0; k=0
    while k<len(trace) and i<len(ins):
        off,sz,c,t=ins[i]
        if c=='skip': i+=1; continue
        if c=='end': return k
        tk=trace[k]
        if tk==NEXT and c not in ('cb',): k+=1; continue
        if c in(JUMP,'cb'):
            tg=target(off,sz,t)
            if tk==JUMP and tg in idx: i=idx[tg]; k+=1; continue
            if tk==NEXT and c=='cb': i+=1; k+=1; continue
            return k
        if c==tk: i+=1; k+=1; continue
        return k
    return k
groups=collections.OrderedDict()
for l in open(wf):
    h,t=l.split(' :'); p=h.split(); n=int(p[6]); tr=[int(x) for x in t.split()]
    groups.setdefault((n,tuple(tr)),[]).append((int(p[4]),int(p[5])))
import itertools
def run(verbose):
    res=[]
    for (n,tr),ws in groups.items():
        sc=[(walk(c,list(tr)),c) for c in cos]; best=max(sc)
        res.append((n,len(ws),best,[c for k,c in sc if k>=n-1]))
    return res
if '--search' in sys.argv:
    out=[]
    for combo in itertools.product([0,1],repeat=5):
        H.update(dict(zip(['delay','walu','wait','nop','clause'],combo))); load()
        r=run(False); out.append((sum(len(x[3])>0 for x in r),sum(x[2][0]/x[0] for x in r),combo))
    for o in sorted(out,reverse=True)[:6]: print(o)
    sys.exit()
res=run(True)
for n,nw,best,full in sorted(res,key=lambda r:-r[0]*r[1]):
    print(f'insts={n:5d} waves={nw:4d} best co{best[1]} matched {best[0]}/{n}  full-matches={full[:6]}')
