# Compare native `openrgp_cli waves` output with oracle dumps (rtd_summary RTD_DUMP files) as multisets of waves.
# usage: python3 compare.py [capture.rgp oracle_dump.txt]...   (paths inside this file are the original session locations; edit)
import subprocess,collections,sys,os
def load(fn,dfn):
    C=collections.Counter()
    ls=[x for x in open(fn).read().split('\n') if x]; ds=[x for x in open(dfn).read().split('\n') if x]
    for l,d in zip(ls,ds):
        h,t=l.split(' :'); p=h.split()
        C[(tuple(int(x) for x in t.split()),tuple(tuple(int(y) for y in x.split(',')[:3]) for x in d.split(':',1)[1].split()),(int(p[6]),int(p[7]),int(p[8])))]+=1
    return C
cases=[(f'/home/fireburn/AI/llama-deep/rgp/decode_94k/decode_94k_300nodes_submit{n}.rgp',f'/tmp/claude-1000/ref{n}.txt') for n in range(4,13)]
S=subprocess.run('ls ~/AI/llama-deep/rgp/dl/x/Radeon*/samples/sample_profile.rgp',shell=True,capture_output=True,text=True).stdout.strip()
cases.append((S,'/tmp/claude-1000/rdf_ref.txt'))
extra=sys.argv[1:]
for a in range(0,len(extra),2): cases.append((extra[a],extra[a+1]))
T=W=0
for f,ref in cases:
    if not os.path.exists(ref): continue
    out=subprocess.run(['build/openrgp_cli','waves',f,'/tmp/claude-1000/n.txt.d'],capture_output=True,text=True)
    open('/tmp/claude-1000/n.txt','w').write(out.stdout)
    if out.returncode: print(os.path.basename(f),'FAILED:',out.stderr[:100]); continue
    N=load('/tmp/claude-1000/n.txt','/tmp/claude-1000/n.txt.d'); R=load(ref,ref+'.d')
    same=sum((N&R).values()); tot=sum(R.values()); T+=tot; W+=same
    print(f'{os.path.basename(f)[:34]:34s} waves {tot:6d} identical {same:6d} ({100*same/max(tot,1):.2f}%)')
print(f'TOTAL {W}/{T} = {100*W/max(T,1):.3f}%')
