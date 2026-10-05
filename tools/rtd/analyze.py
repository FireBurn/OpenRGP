#!/usr/bin/env python3
"""analyze.py work_dir [N...] : identify kernels in decoded captures and summarise wave time per kernel."""
import sys,os,re,collections,hashlib,importlib.util
wd=sys.argv[1]; subs=[int(x) for x in sys.argv[2:]] or list(range(13))
spec=importlib.util.spec_from_file_location('mt','/home/fireburn/AI/OpenRGP/tools/rtd/match.py')
src=open('/home/fireburn/AI/OpenRGP/tools/rtd/match.py').read().split("groups=collections")[0]
def label(f):
    w,e,d,ds,v_exp,sz=f['wmma'],f['exp'],f['dot4'],f['ds'],f['exp'],f['n']
    if w and e: return 'flash-attn (WMMA)'
    if w: return 'matmul (WMMA)'
    if d and ds: return 'mat-vec int8 (dot4+LDS)'
    if d: return 'mat-vec int8 (dot4)'
    if f['fma_mix']>20 and f['reduce']: return 'mat-vec float / norm'
    if f['gated']: return 'gated-delta-net'
    return 'other/elementwise (%d instrs)'%sz
agg=collections.defaultdict(lambda:dict(waves=0,cyc=0,ex=0,wa=0,st=0,subs=set(),spans=[],insts=0,f=None))
for n in subs:
    d=f'{wd}/isa{n}'; wf=f'{wd}/w{n}.txt'
    if not os.path.exists(wf): continue
    sys.argv=['m',d,wf]; ns={}; exec(src,ns)
    cos=ns['cos']; walk=ns['walk']
    feats={}; sig={}
    txt=collections.defaultdict(list)
    for l in open(f'{d}/isa.txt'):
        c,off,sz,t=l.rstrip('\n').split('\t',3); txt[int(c)].append(t)
    for c,ts in txt.items():
        j=' '.join(ts); sig[c]=hashlib.md5(j.encode()).hexdigest()[:8]
        feats[c]=dict(n=len(ts),wmma=sum('wmma' in t for t in ts),exp=sum(t.startswith('v_exp') for t in ts),dot4=sum('dot4' in t for t in ts),ds=sum(t.startswith('ds_') for t in ts),
                      fma_mix=sum('fma_mix' in t or 'dot2' in t for t in ts),reduce=sum('permlane' in t or 'dpp' in t or 'swizzle' in t for t in ts),gated=0)
    G=collections.OrderedDict()
    for l in open(wf):
        h,t=l.split(' :'); p=h.split(); tr=tuple(int(x) for x in t.split())
        G.setdefault(tr,[]).append(dict(b=int(p[4]),e=int(p[5]),ex=int(p[7]),wa=int(p[8]),st=int(p[9])))
    for tr,ws in G.items():
        best=max(((walk(c,list(tr)),c) for c in cos),key=lambda x:x[0])
        k,c=best
        if k<len(tr)*0.8: c=None
        key=(sig[c] if c is not None else 'unmatched-%d'%len(tr))
        a=agg[key]; a['waves']+=len(ws); a['cyc']+=sum(w['e']-w['b'] for w in ws)
        a['ex']+=sum(w['ex'] for w in ws); a['wa']+=sum(w['wa'] for w in ws); a['st']+=sum(w['st'] for w in ws)
        a['subs'].add(n); a['insts']=len(tr); a['spans'].append(max(w['e'] for w in ws)-min(w['b'] for w in ws))
        if c is not None: a['f']=feats[c]
tot=sum(a['cyc'] for a in agg.values())
print(f"{'kernel':34s} {'sig':9s} {'wave-cyc%':>9s} {'waves':>6s} {'insts/wave':>10s} {'avg wave cyc':>12s} {'exec%':>6s} {'wait%':>6s} {'stall%':>6s} subs")
for key,a in sorted(agg.items(),key=lambda x:-x[1]['cyc']):
    t=a['ex']+a['wa']+a['st']+1e-9
    lab=label(a['f']) if a['f'] else 'unidentified'
    print(f"{lab:34s} {key:9s} {100*a['cyc']/tot:9.1f} {a['waves']:6d} {a['insts']:10d} {a['cyc']/a['waves']:12.0f} {100*a['ex']/t:6.1f} {100*a['wa']/t:6.1f} {100*a['st']/t:6.1f} {sorted(a['subs'])}")
