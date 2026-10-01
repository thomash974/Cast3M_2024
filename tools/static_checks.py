#!/usr/bin/env python3
"""Controles statiques Gibiane (sans Cast3M) utilises pendant tout le projet.

Usage : python3 tools/static_checks.py fichier1 [fichier2 ...]
        python3 tools/static_checks.py --orig procedur_origine/unpas.procedur procedur/unpas.procedur

Controles :
 1. blocs SI / FINSI et REPETER / FIN <etiquette> equilibres ;
 2. instructions (separees par ;) avec au moins deux signes '=' hors chaines
    (cause de l'erreur 1014 : "deux signes = dans la phrase") ;
 3. options >N / <N accolees a un nom de variable dans un CHAI (lues comme un
    seul mot) et litteral '/' isole dans un CHAI ;
 4. lignes de code de plus de 122 caracteres (limite observee dans UNPAS) ;
 5. avec --orig : lignes ajoutees (par rapport a l'original) qui sont des
    commentaires mais ne commencent pas en colonne 1.
"""
import re,sys,difflib

def read(p):
    return open(p,'rb').read().decode('latin-1').replace('\r','')

def code_lines(t):
    return [l for l in t.split('\n') if not l.lstrip().startswith('*')]

def check_blocks(t):
    code='\n'.join(code_lines(t))
    si=len(re.findall(r"(?<![\w'])'SI'|(?<![\w'])SI(?=\s*\()|(?<![\w'])SI(?=\s+[A-Za-z_])",code,re.I))
    fs=len(re.findall(r"'?FINS(?:I)?'?\s*;",code,re.I))
    rp=len(re.findall(r"(?<![\w'])'?REPE\w*'?\s+[A-Za-z_]\w*\s",code,re.I))
    fn=len(re.findall(r"(?<![\w'])'?FIN'?\s+[A-Za-z_]\w*\s*;",code,re.I))
    return si,fs,rp,fn

def check_equals(t):
    code='\n'.join(code_lines(t))
    code=re.sub(r"'[^']*'",lambda m:"'"+"x"*(len(m.group(0))-2)+"'",code)
    out=[];cur=0
    for m in re.finditer(r";",code):
        s=code[cur:m.end()];cur=m.end()
        if s.count('=')>=2: out.append(' '.join(s.split())[:110])
    return out

def check_chai(t):
    bad=[]
    for m in re.finditer(r"(?:^|\n)[ \t]*\w+ = CHAI ((?:[^;']|'(?:[^']|'')*')*);",t):
        a=m.group(1)
        if re.search(r"[A-Za-z0-9_][<>]\d",a) or re.search(r"'/'",a): bad.append(' '.join(a.split())[:110])
    return bad

def main(argv):
    orig=None
    if argv and argv[0]=='--orig':
        orig=argv[1]; argv=argv[2:]
    rc=0
    for p in argv:
        t=read(p)
        si,fs,rp,fn=check_blocks(t)
        print(f"== {p}")
        # les procedures d'origine utilisent des abreviations et des formes
        # (ITER, boucles sans etiquette) qui rendent le decompte absolu de
        # REPETER/FIN peu fiable : avec --orig on controle les deltas
        if orig:
            osi,ofs,orp,ofn=check_blocks(read(orig))
            print(f"   SI/FINSI : {si}/{fs} (delta {si-osi}/{fs-ofs}) {'OK' if (si==fs and si-osi==fs-ofs) else 'DESEQUILIBRE'} ; REPETER/FIN : delta {rp-orp}/{fn-ofn} {'OK' if rp-orp==fn-ofn else 'DESEQUILIBRE'}")
            if si!=fs or si-osi!=fs-ofs or rp-orp!=fn-ofn: rc=1
        else:
            print(f"   SI/FINSI : {si}/{fs} {'OK' if si==fs else 'DESEQUILIBRE'} ; REPETER/FIN : {rp}/{fn} {'OK' if rp==fn else 'a verifier (formes abregees possibles)'}")
            if si!=fs: rc=1
        eq=check_equals(t)
        if eq and not p.endswith('.procedur'):
            rc=1; print(f"   {len(eq)} instruction(s) avec deux signes = :"); [print('     ',x) for x in eq[:5]]
        ch=check_chai(t)
        if ch: rc=1; print(f"   {len(ch)} CHAI avec >N/<N colle a un nom ou '/' isole :"); [print('     ',x) for x in ch[:5]]
        long=[i+1 for i,l in enumerate(t.split('\n')) if len(l)>122 and not l.lstrip().startswith('*')]
        if long: print(f"   lignes de code > 122 car. : {long[:8]}")
        if orig:
            o=read(orig).split('\n'); n=t.split('\n')
            added=[l[2:] for l in difflib.ndiff(o,n) if l.startswith('+ ')]
            ind=[l for l in added if re.match(r"[ \t]+\*",l)]
            print(f"   lignes ajoutees : {len(added)} ; commentaires hors colonne 1 : {len(ind)}")
            if ind: rc=1; [print('     ',x[:90]) for x in ind[:5]]
    return rc
if __name__=='__main__':
    sys.exit(main(sys.argv[1:]))
