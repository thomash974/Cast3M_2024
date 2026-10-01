"""Generateur de valid_perf.dgibi (pilote de validation / benchmark PERF-RAID).

Execute chaque cas de la liste CASES (repertoire dgibi de PCW_24) dans une
procedure Gibiane VC<k>, en trois passes (PERF_RAID FAUX / niveau 1 / niveau 2),
compare les empreintes (extrema de DEPLACEMENTS, CONTRAINTES, TEMPERATURES) et
ecrit les logs. Usage :
    DGIBI_DIR=/chemin/PCW_24/dgibi OUT_DIR=livraison/validation python3 tools/gen_validation.py
"""
import re,os,sys,json
# Chemins : variables d'environnement DGIBI_DIR (repertoire dgibi de l'archive
# PCW_24) et OUT_DIR (sortie : valid_perf.dgibi). Valeurs par defaut relatives
# a ce fichier (tools/gen_validation.py).
HERE=os.path.dirname(os.path.abspath(__file__))
D=os.environ.get('DGIBI_DIR',os.path.join(HERE,'..','PCW_24','dgibi'))
OUT=os.environ.get('OUT_DIR',os.path.join(HERE,'..','livraison','validation'))
os.makedirs(OUT,exist_ok=True)

# (cas, classes visees)
CASES=[
 # --- endommagement (classe UNPAS : IENDOM) : massifs 2D/3D, axi, thermique, dynamique
 ('mazars','endommagement MAZARS, QUA4 CP'),
 ('mazars2','endommagement MAZARS, cycles'),
 ('compression','endommagement, compression'),
 ('endoaxi1','endommagement, axisymetrique'),
 ('endoaxi2','endommagement + thermique, axi'),
 ('endoaxi3','endommagement + thermique, axi'),
 ('endocp1','endommagement, contraintes planes'),
 ('fluaendo','fluage + endommagement + thermique'),
 ('relaxendo','relaxation + endommagement + thermique'),
 ('GTN_C20R','endommagement ductile (GTN)'),
 ('mvm_bcn','endommagement'),
 ('desmorat','endommagement + dynamique'),
 ('betdynlmt','endommagement + dynamique, beton'),
 ('ricbet_uni_1','beton arme, endommagement (structure)'),
 ('FissVoil','endommagement, voile (structure)'),
 ('GLRC_DM','coque + endommagement (HOOK conserve)'),
 # --- materiau dependant de parametres externes (T) : cache PAS_MATE et reutilisation MATVAR
 ('traction316L','T uniforme, E(T)'),
 ('test_vari_props','proprietes variables'),
 ('dilthe','dilatation thermique'),
 ('char_constant','chargement constant, thermique'),
 ('thgdep1','thermique + grands deplacements'),
 ('ther_meca_coque','thermomecanique coque'),
 ('dependance','dependance parametres, coque'),
 ('thme1','thermo-mecanique'),
 ('phase_03','metallurgie/phases'),
 # --- lois de comportement (massifs)
 ('plas5','plasticite'),
 ('plas_incomp','plasticite incompressible'),
 ('chaboche1','viscoplasticite Chaboche/Onera'),
 ('chaboche2','viscoplasticite'),
 ('norton_tra1','fluage Norton'),
 ('ddi','visco'),
 ('tufi','plasticite tuyau fibre'),
 ('fluage_maxwell_1','fluage Maxwell'),
 ('poudre3','poudre'),
 ('gurson','Gurson'),
 ('beton','beton'),
 ('ottovari_traction','plasticite'),
 # --- types d'elements : coques, poutres, fibres, joints, tuyaux
 ('plas8','coque plastique'),
 ('ohno2','coque visco Ohno'),
 ('guionnet_tra','coque visco'),
 ('g_c_etoile_coque_1','coque visco'),
 ('PoutreConsole_Plas_EcrouCineLine','poutre plastique'),
 ('fluage_fibre_norton_1','poutre fibres fluage'),
 ('test_cisailnl','poutre cisaillement non lineaire'),
 ('cou22','joint'),
 ('testjoi1ani','joint anisotrope'),
 ('joi_eli','joint elastique'),
 ('jointsoft1','joint adoucissant'),
 # --- grands deplacements / hyperelasticite
 ('gdep2','grands deplacements coque'),
 ('gdef2','grandes deformations'),
 ('Mooney_LRGTreloar_Traction','hyperelastique'),
 ('gdtract','grands deplacements + endommagement (reutilisation exclue)'),
 # --- dynamique et contact
 ('newmark1','dynamique Newmark poutre'),
 ('dyna_nl1','dynamique non lineaire'),
 ('Contact2D','contact 2D'),
 ('Coulomb3D','contact frottant 3D'),
 ('contact2D-adhe','contact adherent'),
]

def load(n):
    t=open(f'{D}/{n}.dgibi','rb').read().decode('latin-1').replace('\r','').replace('\x00','')
    return t

def strip_stmt(t,first_re):
    """commente les instructions (multi-lignes) dont le 1er mot verifie first_re"""
    L=t.split('\n'); out=[]; i=0
    while i<len(L):
        l=L[i]
        if re.match(first_re,l):
            j=i
            while j<len(L) and ';' not in L[j]: out.append('* [valid] '+L[j]); j+=1
            if j<len(L): out.append('* [valid] '+L[j])
            i=j+1
        else:
            out.append(l); i+=1
    return '\n'.join(out)

def patch(n,t):
    notes=[]
    t=re.sub(r"(?im)^\s*'?FIN'?\s*;.*$","* [valid] FIN final",t)
    t=re.sub(r"(?i)(\bECHO'?\s+)[-\d]+",r"\g<1>IECHO0",t)
    t=re.sub(r"(?i)(TRAC'?\s+)'?X'?(?=\s|;)",r"\1'PSC'",t)
    t=strip_stmt(t,r"(?i)^\s*@EXCEL1\b")
    t=strip_stmt(t,r"(?i)^\s*'?TEMPS?'?\s*;")
    # ERRE
    t,n0=re.subn(r"(?i)'?\bERRE'?\s*0\s*;","VTCT . 'N0' = (VTCT . 'N0') + 1 ;",t)
    t,n1=re.subn(r"(?i)'?\bERRE'?\s*\d+\s*;","VTCT . 'N5' = (VTCT . 'N5') + 1 ;",t)
    t,n2=re.subn(r"(?i)'?\bERRE'?\s+'(?:[^']|'')*'\s*;","VTCT . 'N5' = (VTCT . 'N5') + 1 ;",t)
    if re.search(r"(?i)'?\bERRE\b'?\s*(?!\s*=)[^;]*;",t) and re.search(r"(?im)^\s*'?ERRE'?\s",t): notes.append('ERRE non neutralise')
    # PASAPAS
    pat=re.compile(r"(?i)((?:[A-Za-z_]\w*[ \t]*=[ \t]*)?)'?PASAPAS'?(\s+)([A-Za-z_]\w*)(\s*);")
    t,np_=pat.subn(lambda m:f"{m.group(3)} . 'PERF_RAID' = VPSW ; {m.group(3)} . 'PERF_RAID_NIVEAU' = VNIV ; {m.group(1)}PASAPAS {m.group(3)} ; FPREC {m.group(3)} VTFPR ;",t)
    if np_==0: notes.append('PASAPAS non injecte')
    return t,notes,(n0,n1+n2,np_)




def jn(*parts):
    """assemble des objets CHAI en inserant l'objet ' ' entre eux (CHAI supprime les
    espaces terminaux d'une chaine ; un ' ' isole est conserve). Une partie dont
    le premier caractere est ^ n'est pas precedee d'un espace."""
    out=[]
    for p in parts:
        if p.startswith('^'):
            out.append(p[1:])
        else:
            if out: out.append("' '")
            out.append(p)
    return ' '.join(out)

def W(args,ind='    ',var='VMSG'):
    """message CHAI (les espaces sont produits par les options >N, pas par des
    espaces dans les chaines), affiche (MESS) et ecrit (SORT 'CHAI')"""
    return (f"{ind}{var} = CHAI {args} ;\n{ind}MESS {var} ;\n{ind}SORT 'CHAI' {var} ;\n")

drv=[]
A=drv.append
A("""* ======================================================================
* VALID_PERF.DGIBI
* ----------------------------------------------------------------------
* Validation et benchmark des optimisations PERF-RAID (UNPAS / PAS_MATE /
* PASAPAS / PAS_DEFA) sur des cas tests de la distribution (repertoire
* dgibi). Chaque cas est execute dans une procedure (variables locales),
* jusqu'a trois fois :
*   passe 1 : 'PERF_RAID' FAUX (comportement d'origine)
*   passe 2 : 'PERF_RAID' VRAI, niveau 1 (resultats identiques attendus)
*   passe 3 : 'PERF_RAID' VRAI, niveau 2 (reutilisation approchee de la
*             raideur : ecart faible attendu, inferieur a TOLV3)
* Les resultats stockes par PASAPAS (maxi, mini, maxi en valeur absolue de
* DEPLACEMENTS, CONTRAINTES, TEMPERATURES a chaque pas) sont compares a la
* passe 1. Les controles internes du cas (ERRE) sont neutralises et comptes.
* ----------------------------------------------------------------------
* SUIVI : console (lignes >>> Cas ... et <<< Cas ...), fichier
* valid_avancement.log (cas en cours, cas termines), valid_<cas>.log (un
* fichier par cas), valid_synthese.log (tableau final et temps cumules).
* valid_inutile.tmp est un fichier vide (ferme les fichiers de sortie).
* Les procedures modifiees (unpas, pas_mate, pasapas, pas_defa) doivent
* etre dans le repertoire d'execution.
* Reprise apres une erreur : regler IDEB0 sur le numero du cas.
* ======================================================================
* Verbosite : 0 = erreurs et avertissements ; 1 = + instructions ; -1 = erreurs
IECHO0 = 0 ;
OPTI 'ECHO' IECHO0 ;
OPTI 'TRAC' 'PSC' ;
* VRAI : tout l'affichage va dans valid_trace.log (console muette)
ITRACE0 = FAUX ;
* Premier et dernier cas executes (numeros de la liste ci-dessous)
IDEB0 = 1 ;
IFIN0 = %NCAS% ;
NTOT0 = %NCAS% ;
* Chronometrage (benchmark) et nombre de repetitions de chaque calcul
* (temps minimal retenu ; les cas courts durent quelques ms : utiliser 3
* ou plus pour lisser les mesures)
ITEMPS0 = VRAI ;
NREP0 = 1 ;
* Passe 3 (niveau 2, reutilisation approchee) : VRAI ou FAUX
IPASS3 = VRAI ;
* Tolerances relatives sur les extrema : niveau 1 (identique attendu) et
* niveau 2 (approche)
TOLV0 = 1.E-8 ;
TOLV3 = 5.E-3 ;
* Cas a sauter (ex. trop longs) : TSKIP . <numero> = VRAI ;
TSKIP = TABL ;
* Cas 15 (FissVoil) ecarte : son post-traitement (procedure INITOU) designe
* les noeuds par leur numero global (NOEUD i), ce qui suppose que le maillage
* du cas soit le premier cree dans la session. Il echoue donc des la passe 1
* (comportement d'origine) des qu'un autre maillage existe. A valider seul,
* dans une session neuve, si necessaire.
TSKIP . 15 = VRAI ;
*
DEBPROC CHRONO ;
    TH1 = TEMP 'HORL' ;
FINPROC TH1 ;
*
* Suivi : ecrit valid_avancement.log puis referme le fichier
DEBPROC AVANCE TV1*'TABLE' K1*'ENTIER' NT1*'ENTIER' NOM1*'MOT'
    P1*'ENTIER' ETA1*'MOT' ;
    OPTI 'SORT' 'valid_avancement.log' ;
    SORT 'CHAI' 'AVANCEMENT DE LA VALIDATION PERF-RAID' ;
    VM1 = CHAI 'Cas en cours :' ' ' K1 ' ' 'sur' ' ' NT1 ' ' ':' ' ' NOM1 ' ' '- passe' ' ' P1 ' ' '-' ' ' ETA1 ;
    SORT 'CHAI' VM1 ;
    SORT 'CHAI' 'Cas termines :' ;
    REPETER BAV1 NT1 ;
        I1 = &BAV1 ;
        SI ('EXIS' TV1 I1) ;
            T1 = TV1 . I1 ;
            VN1 = T1 . 'NOM' ;
            VO1 = T1 . 'OKM' ;
            VX1 = T1 . 'ERR2' ;
            VE1 = CHAI 'FORMAT' '(1PE9.2)' VX1 ;
            VM2 = CHAI I1*4 ' ' VO1 ' ' 'ecart' ' ' VE1 ' ' VN1 ;
            SORT 'CHAI' VM2 ;
        FINSI ;
    FIN BAV1 ;
    OPTI 'SORT' 'valid_inutile.tmp' ;
FINPROC ;
*
* Comparaison des empreintes de deux passes : ecart relatif maximal,
* nombre de tables de longueurs differentes, nombre de valeurs comparees
DEBPROC COMPAR TA*'TABLE' TB*'TABLE' ;
    VERRM = 0. ;
    VNLEN = 0 ;
    VNCMP = 0 ;
    LVN = 'MOTS' 'DEPLACEMENTS' 'CONTRAINTES' 'TEMPERATURES' ;
    REPETER ZVCMP ('DIME' LVN) ;
        VNOM = 'EXTR' LVN &ZVCMP ;
        VE1 = 'EXIS' TA VNOM ;
        VE2 = 'EXIS' TB VNOM ;
        SI (VE1 'ET' VE2) ;
            VL1 = TA . VNOM ;
            VL2 = TB . VNOM ;
            SI (('DIME' VL1) 'EGA' ('DIME' VL2)) ;
                VNCMP = VNCMP + ('DIME' VL1) ;
                VREF = 'MAXI' VL1 'ABS' ;
                SI (VREF '<' 1.E-300) ;
                    VREF = 1. ;
                FINSI ;
                VDIF = 'MAXI' (VL2 '-' VL1) 'ABS' ;
                VERR = VDIF '/' VREF ;
                SI (VERR '>' VERRM) ;
                    VERRM = VERR ;
                FINSI ;
            SINON ;
                VNLEN = VNLEN + 1 ;
            FINSI ;
        SINON ;
            SI (VE1 'OU' VE2) ;
                VNLEN = VNLEN + 1 ;
            FINSI ;
        FINSI ;
    FIN ZVCMP ;
FINPROC VERRM VNLEN VNCMP ;
*
* Empreinte : pour chaque pas stocke par PASAPAS, max(abs), max et min de
* chaque grandeur ; compteurs PERF-RAID et classes exercees
DEBPROC FPREC TA1*'TABLE' TR1*'TABLE' ;
    NS1 = 0 ;
    'SI' ('EXIS' TA1 'TEMPS') ;
        NS1 = ('DIME' (TA1 . 'TEMPS')) - 1 ;
    'FINSI' ;
    LNOM1 = 'MOTS' 'DEPLACEMENTS' 'CONTRAINTES' 'TEMPERATURES' ;
    'SI' (NS1 '>' 0) ;
        'REPETER' BNO1 ('DIME' LNOM1) ;
            NOM1 = 'EXTR' LNOM1 &BNO1 ;
            'SI' ('EXIS' TA1 NOM1) ;
                TD1 = TA1 . NOM1 ;
                'REPETER' BST1 NS1 ;
                    I1 = &BST1 ;
                    'SI' ('EXIS' TD1 I1) ;
                        V1 = TD1 . I1 ;
                        TY1 = 'TYPE' V1 ;
                        'SI' (('EGA' TY1 'CHPOINT') 'OU' ('EGA' TY1 'MCHAML')) ;
                            X1 = 'MAXI' V1 'ABS' ;
                            X2 = 'MAXI' V1 ;
                            X3 = 'MINI' V1 ;
                            LV1 = 'PROG' X1 X2 X3 ;
                            'SI' ('EXIS' TR1 NOM1) ;
                                TR1 . NOM1 = (TR1 . NOM1) 'ET' LV1 ;
                            'SINON' ;
                                TR1 . NOM1 = LV1 ;
                            'FINSI' ;
                        'FINSI' ;
                    'FINSI' ;
                'FIN' BST1 ;
            'FINSI' ;
        'FIN' BNO1 ;
    'FINSI' ;
    TR1 . 'NRE' = -1 ;
    TR1 . 'NMA' = -1 ;
    TR1 . 'NCA' = -1 ;
    TR1 . 'NHK' = -1 ;
    TR1 . 'CL' = 0 ;
    'SI' ('EXIS' TA1 'WTABLE') ;
        WT1 = TA1 . 'WTABLE' ;
        'SI' ('EXIS' WT1 'NB_RAIDEUR_REUT') ;
            TR1 . 'NRE' = WT1 . 'NB_RAIDEUR_REUT' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'NB_MAT_REUT') ;
            TR1 . 'NMA' = WT1 . 'NB_MAT_REUT' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'NB_RAIDEUR_CALC') ;
            TR1 . 'NCA' = WT1 . 'NB_RAIDEUR_CALC' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'NB_HOOK_EVITE') ;
            TR1 . 'NHK' = WT1 . 'NB_HOOK_EVITE' ;
        'FINSI' ;
        ICL1 = 0 ;
        'SI' ('EXIS' WT1 'MATVAR') ;
            'SI' (WT1 . 'MATVAR') ;
                ICL1 = ICL1 + 1 ;
            'FINSI' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'ENDOMMAGEMENT') ;
            'SI' (WT1 . 'ENDOMMAGEMENT') ;
                ICL1 = ICL1 + 10 ;
            'FINSI' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'VISCODOMMAGE') ;
            'SI' (WT1 . 'VISCODOMMAGE') ;
                ICL1 = ICL1 + 20 ;
            'FINSI' ;
        'FINSI' ;
        'SI' ('EXIS' WT1 'GRANDS_DEPLACEMENTS') ;
            'SI' (WT1 . 'GRANDS_DEPLACEMENTS') ;
                ICL1 = ICL1 + 100 ;
            'FINSI' ;
        'FINSI' ;
        TR1 . 'CL' = ICL1 ;
    'FINSI' ;
FINPROC ;
*
VRES = TABL ;
VNBK2 = 0 ;
VNBK3 = 0 ;
VSUM1 = 0 ;
VSUM2 = 0 ;
VSUM3 = 0 ;
MESS '==================================================' ;
VMSG = CHAI 'VALIDATION ET BENCHMARK PERF-RAID :' ' ' NTOT0 ' ' 'cas (du cas' ' ' IDEB0 ' ' 'au cas' ' ' IFIN0 ')' ;
MESS VMSG ;
MESS '==================================================' ;
AVANCE VRES IDEB0 NTOT0 'demarrage' 1 'initialisation' ;
""")
names=[]
for k,(n,desc) in enumerate(CASES,1):
    t=load(n)
    code='\n'.join(l for l in t.split('\n') if not l.lstrip().startswith('*'))
    if re.search(r"(?im)^\s*'?DEBP(ROC)?'?\b",code) or re.search(r"(?i)\b(LIRE|ACQU|REST|RESTITUER|SAUV|SAUVER)\b",code):
        print('SKIP',n,'(procedure ou fichier)'); continue
    body,notes,(n0,n5,npas)=patch(n,t)
    if npas==0:
        print('SKIP',n,notes); continue
    kk=len(names)+1; names.append((n,desc,notes,npas,n0,n5))
    log=f"valid_{n}.log"
    dd=desc.replace("'"," ")
    A(f"""*
* ---------------------------------------------------------------------
* Procedure du cas {kk} : {n} ({dd})
* Variables locales : le cas ne voit aucune variable des cas precedents
* ---------------------------------------------------------------------
DEBPROC VC{kk} VPSW*'LOGIQUE' VNIV*'ENTIER' VTFPR*'TABLE' VTCT*'TABLE' IECHO0*'ENTIER' ;
* ----- debut du cas {n}
""")
    A(body)
    A(f"""* ----- fin du cas {n}
FINPROC ;
*
* ---------------------------------------------------------------------
* Cas {kk} : {n} ({dd})
* ---------------------------------------------------------------------
SI ((IDEB0 '<EG' {kk}) 'ET' (IFIN0 '>EG' {kk}) 'ET' ('NON' ('EXIS' TSKIP {kk}))) ;
    MENAGE 'OBLI' ;
    MESS ' ' ;
    VMSG = CHAI '>>> Cas' ' ' '{kk}' ' ' 'sur' ' ' NTOT0 ' ' ':' ' ' '{n}' ' ' '({dd})' ;
    MESS VMSG ;
    NPASS = 2 ;
    SI IPASS3 ;
        NPASS = 3 ;
    FINSI ;
    VTH1 = 0 ;
    VTH2 = 0 ;
    VTH3 = 0 ;
    VNE51 = 0 ;
    VNE01 = 0 ;
    VNE52 = 0 ;
    VNE02 = 0 ;
    VNE53 = 0 ;
    VNE03 = 0 ;
    REPETER ZVRUN NPASS ;
* ordre des passes alterne d'un cas a l'autre (derive des temps en session)
        VIP = {'&ZVRUN' if kk%2 else 'NPASS + 1 - &ZVRUN'} ;
        VPSW = (VIP '>' 1) ;
        VNIV = 1 ;
        VMPS = 'inactif' ;
        SI (VIP 'EGA' 2) ;
            VMPS = 'actif niveau 1' ;
        FINSI ;
        SI (VIP 'EGA' 3) ;
            VNIV = 2 ;
            VMPS = 'actif niveau 2' ;
        FINSI ;
        AVANCE VRES {kk} NTOT0 '{n}' VIP 'en_cours' ;
        VMSG = CHAI '    passe' ' ' VIP ' ' 'sur' ' ' NPASS ' ' ': optimisations' ' ' VMPS ;
        MESS VMSG ;
        SI ITRACE0 ;
            OPTI 'IMPR' 'valid_trace.log' ;
        FINSI ;
        OPTI 'DIME' 3 'MODE' 'TRID' 'ELEM' 'CUB8' 'ECHO' IECHO0 ;
        VTHM = 0 ;
        REPETER ZVREP NREP0 ;
            VIR = &ZVREP ;
            VTFPR = TABL ;
            VTCT = TABL ;
            VTCT . 'N0' = 0 ;
            VTCT . 'N5' = 0 ;
            SI ITEMPS0 ;
                TEMP 'ZERO' ;
            FINSI ;
* Le cas s'execute dans une procedure (variables locales) : les variables
* d'un cas precedent ne peuvent pas masquer un mot-cle ou un operateur
            VC{kk} VPSW VNIV VTFPR VTCT IECHO0 ;
            VTHR = 0 ;
            SI ITEMPS0 ;
                VTHR = CHRONO ;
            FINSI ;
            SI (VIR 'EGA' 1) ;
                VTHM = VTHR ;
            SINON ;
                SI (VTHR '<' VTHM) ;
                    VTHM = VTHR ;
                FINSI ;
            FINSI ;
        FIN ZVREP ;
        VNER5 = VTCT . 'N5' ;
        VNER0 = VTCT . 'N0' ;
        SI (VIP 'EGA' 1) ;
            VTF1 = VTFPR ;
            VTH1 = VTHM ;
            VNE51 = VNER5 ;
            VNE01 = VNER0 ;
        FINSI ;
        SI (VIP 'EGA' 2) ;
            VTF2 = VTFPR ;
            VTH2 = VTHM ;
            VNE52 = VNER5 ;
            VNE02 = VNER0 ;
        FINSI ;
        SI (VIP 'EGA' 3) ;
            VTF3 = VTFPR ;
            VTH3 = VTHM ;
            VNE53 = VNER5 ;
            VNE03 = VNER0 ;
        FINSI ;
    FIN ZVRUN ;
*   comparaison des empreintes avec la passe 1
    VER2 VNL2 VNC2 = COMPAR VTF1 VTF2 ;
    VMOK2 = 'OK' ;
    SI ((VER2 '>' TOLV0) 'OU' (VNL2 '>' 0) 'OU' ('NON' (VNE52 'EGA' VNE51))) ;
        VMOK2 = 'ECART' ;
        VNBK2 = VNBK2 + 1 ;
    FINSI ;
    VER3 = 0. ;
    VNC3 = 0 ;
    VMOK3 = 'sans_objet' ;
    SI IPASS3 ;
        VER3 VNL3 VNC3 = COMPAR VTF1 VTF3 ;
        VMOK3 = 'OK' ;
        SI ((VER3 '>' TOLV3) 'OU' (VNL3 '>' 0) 'OU' ('NON' (VNE53 'EGA' VNE51))) ;
            VMOK3 = 'ECART' ;
            VNBK3 = VNBK3 + 1 ;
        FINSI ;
    FINSI ;
*   accelerations (temps de la passe 1 / temps de la passe)
    VSP2 = 0. ;
    VSP3 = 0. ;
    SI ((VTH1 '>' 0) 'ET' (VTH2 '>' 0)) ;
        VSP2 = (FLOT VTH1) '/' (FLOT VTH2) ;
    FINSI ;
    SI ((VTH1 '>' 0) 'ET' (VTH3 '>' 0)) ;
        VSP3 = (FLOT VTH1) '/' (FLOT VTH3) ;
    FINSI ;
    VSUM1 = VSUM1 + VTH1 ;
    VSUM2 = VSUM2 + VTH2 ;
    VSUM3 = VSUM3 + VTH3 ;
    VCLA = VTF2 . 'CL' ;
    VR2 = VTF2 . 'NRE' ;
    VC2 = VTF2 . 'NCA' ;
    VH2 = VTF2 . 'NHK' ;
    VM2 = VTF2 . 'NMA' ;
    VR3 = -1 ;
    VC3 = -1 ;
    VH3 = -1 ;
    VM3 = -1 ;
    SI IPASS3 ;
        VR3 = VTF3 . 'NRE' ;
        VC3 = VTF3 . 'NCA' ;
        VH3 = VTF3 . 'NHK' ;
        VM3 = VTF3 . 'NMA' ;
    FINSI ;
    VSE2 = CHAI 'FORMAT' '(1PE10.3)' VER2 ;
    VSE3 = CHAI 'FORMAT' '(1PE10.3)' VER3 ;
    VSS2 = CHAI 'FORMAT' '(F6.2)' VSP2 ;
    VSS3 = CHAI 'FORMAT' '(F6.2)' VSP3 ;
*   fichier de resultat du cas (SORT) et affichage console (MESS)
    OPTI 'SORT' '{log}' ;
"""+W(f"'=== Cas' ' ' '{kk}' ' ' ':' ' ' '{n}' ' ' '({dd})' ' ' '==='")
+W("'Valeurs comparees :' ' ' VNC2")
+W("'Temps horloge (ms) : origine' ' ' VTH1 ' ' '; niveau 1' ' ' VTH2 ' ' '; niveau 2' ' ' VTH3")
+W("'Acceleration par rapport a l origine : niveau 1' ' ' VSS2 ' ' '; niveau 2' ' ' VSS3")
+W("'Controles internes du cas : echecs origine' ' ' VNE51 ' ' '; niveau 1' ' ' VNE52 ' ' '; niveau 2' ' ' VNE53 ' ' '- reussites origine' ' ' VNE01 ' ' '; niveau 1' ' ' VNE02 ' ' '; niveau 2' ' ' VNE03")
+W("'Classes exercees (1 MATVAR, 10 ENDOM, 20 VISCODOM, 100 GD) :' ' ' VCLA")
+W("'Niveau 1 : raideur reutilisee' ' ' VR2 ' ' 'fois, recalculee' ' ' VC2 ' ' 'fois ; HOOK evite' ' ' VH2 ' ' 'fois ; caracteristiques reutilisees' ' ' VM2 ' ' 'fois'")
+W("'Niveau 2 : raideur reutilisee' ' ' VR3 ' ' 'fois, recalculee' ' ' VC3 ' ' 'fois ; HOOK evite' ' ' VH3 ' ' 'fois ; caracteristiques reutilisees' ' ' VM3 ' ' 'fois'")
+W("'Ecart relatif maximal : niveau 1' ' ' VSE2 ' ' '; niveau 2' ' ' VSE3")
+W("'RESULTAT : niveau 1' ' ' VMOK2 ' ' '; niveau 2' ' ' VMOK3")
+f"""    SI (('EGA' VNC2 0) ) ;
"""+W("'ATTENTION : aucune valeur comparee (resultats non stockes ?)'",ind='        ')
+f"""    FINSI ;
    OPTI 'SORT' 'valid_inutile.tmp' ;
    VRES . {kk} = TABL ;
    VRES . {kk} . 'NOM' = '{n}' ;
    VRES . {kk} . 'OKM' = VMOK2 ;
    VRES . {kk} . 'OK3' = VMOK3 ;
    VRES . {kk} . 'ERR2' = VER2 ;
    VRES . {kk} . 'ERR3' = VER3 ;
    VRES . {kk} . 'TH1' = VTH1 ;
    VRES . {kk} . 'TH2' = VTH2 ;
    VRES . {kk} . 'TH3' = VTH3 ;
    VRES . {kk} . 'SP2F' = VSP2 ;
    VRES . {kk} . 'SP3F' = VSP3 ;
    VRES . {kk} . 'NRE2' = VR2 ;
    VRES . {kk} . 'NCA2' = VC2 ;
    VRES . {kk} . 'NHK2' = VH2 ;
    VRES . {kk} . 'NMA2' = VM2 ;
    VRES . {kk} . 'NRE3' = VR3 ;
    VRES . {kk} . 'NCA3' = VC3 ;
    VRES . {kk} . 'NHK3' = VH3 ;
    VRES . {kk} . 'CL' = VCLA ;
    VRES . {kk} . 'NCMP' = VNC2 ;
    VMSG = CHAI '<<< Cas' ' ' '{kk}' ' ' 'sur' ' ' NTOT0 ' ' ':' ' ' '{n}' ' ' ':' ' ' 'niveau 1' ' ' VMOK2 ', niveau 2' ' ' VMOK3 ' ' '- ecart' ' ' VSE2 ', acceleration' ' ' VSS2 ' ' 'et' ' ' VSS3 ;
    MESS VMSG ;
    AVANCE VRES {kk} NTOT0 '{n}' NPASS 'termine' ;
    MENAGE 'OBLI' ;
FINSI ;
""")
NC=len(names)
drv[0]=drv[0].replace('%NCAS%',str(NC))
A("""*
* ---------------------------------------------------------------------
* Synthese
* ---------------------------------------------------------------------
OPTI 'SORT' 'valid_synthese.log' ;
"""+W("'=================================================='",ind='')
+W("'Synthese de la validation et du benchmark PERF-RAID'",ind='')
+W("'Classes : 1 MATVAR, 10 ENDOM, 20 VISCODOM, 100 GD'",ind='')
+W("'cas'*4 't.orig'*12 't.niv1'*20 't.niv2'*28 'acc1'*35 'acc2'*42 'ecart1'*54 'ecart2'*65 'r1'*70 'c1'*75 'h1'*80 'r2'*85 'c2'*90 'h2'*95 'm1'*100 ' ' 'res1' ' ' 'res2' ' ' 'nom'",ind='')
+"""REPETER ZVSY NTOT0 ;
    VI = &ZVSY ;
    SI ('EXIS' VRES VI) ;
        VR1 = VRES . VI ;
        VN1 = VR1 . 'NOM' ;
        VO1 = VR1 . 'OKM' ;
        VO3 = VR1 . 'OK3' ;
        VX2 = VR1 . 'ERR2' ;
        VX3 = VR1 . 'ERR3' ;
        VA1 = VR1 . 'TH1' ;
        VA2 = VR1 . 'TH2' ;
        VA3 = VR1 . 'TH3' ;
        VS2 = VR1 . 'SP2F' ;
        VS3 = VR1 . 'SP3F' ;
        VB1 = VR1 . 'NRE2' ;
        VB2 = VR1 . 'NCA2' ;
        VB3 = VR1 . 'NHK2' ;
        VB4 = VR1 . 'NRE3' ;
        VB5 = VR1 . 'NCA3' ;
        VB6 = VR1 . 'NHK3' ;
        VB7 = VR1 . 'NMA2' ;
"""+W("VI*4 VA1*12 VA2*20 VA3*28 'FORMAT' '(F6.2)' VS2*35 VS3*42 'FORMAT' '(1PE10.3)' VX2*54 VX3*65 VB1*70 VB2*75 VB3*80 VB4*85 VB5*90 VB6*95 VB7*100 ' ' VO1 ' ' VO3 ' ' VN1",ind='        ')
+"""    FINSI ;
FIN ZVSY ;
VSP2 = 0. ;
VSP3 = 0. ;
SI ((VSUM1 '>' 0) 'ET' (VSUM2 '>' 0)) ;
    VSP2 = (FLOT VSUM1) '/' (FLOT VSUM2) ;
FINSI ;
SI ((VSUM1 '>' 0) 'ET' (VSUM3 '>' 0)) ;
    VSP3 = (FLOT VSUM1) '/' (FLOT VSUM3) ;
FINSI ;
VSS2 = CHAI 'FORMAT' '(F6.2)' VSP2 ;
VSS3 = CHAI 'FORMAT' '(F6.2)' VSP3 ;
"""+W("'Temps cumules (ms) : origine' ' ' VSUM1 ' ' '; niveau 1' ' ' VSUM2 ' ' '; niveau 2' ' ' VSUM3",ind='')
+W("'Acceleration cumulee : niveau 1' ' ' VSS2 ' ' '; niveau 2' ' ' VSS3",ind='')
+W("'Nombre de cas en ecart : niveau 1 (tolerance identique)' ' ' VNBK2 ' ' '; niveau 2 (tolerance approchee)' ' ' VNBK3",ind='')
+W("'r1 c1 h1 m1 : raideur reutilisee, recalculee, HOOK evite, caracteristiques reutilisees (niveau 1) ; r2 c2 h2 : idem niveau 2'",ind='')
+W("'Les temps de cas de quelques ms sont peu significatifs : augmenter NREP0 pour lisser'",ind='')
+W("'Fin de la synthese'",ind='')
+"""OPTI 'SORT' 'valid_inutile.tmp' ;
AVANCE VRES NTOT0 NTOT0 'fin' 3 'VALIDATION_TERMINEE' ;
MESS '==================================================' ;
VMSG = CHAI 'VALIDATION TERMINEE :' ' ' NTOT0 ' ' 'cas, dont' ' ' VNBK2 ' ' 'en ecart au niveau 1 et' ' ' VNBK3 ' ' 'au niveau 2' ;
MESS VMSG ;
MESS '==================================================' ;
*
FIN ;
""")
open(f'{OUT}/valid_perf.dgibi','w',encoding='latin-1',newline='\n').write('\n'.join(drv))
json.dump([(n,d,nt) for n,d,nt,_,_,_ in names],open(os.path.join(OUT,'names.json'),'w'))
print(NC,'cas generes')
