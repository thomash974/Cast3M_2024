# Cas tests dgibi en texte compacté, partie 2/2

Cadres de commentaires et alignements supprimés (le code est inchangé). Un cas par section au minimum, complété pour couvrir les opérateurs.

## snap [Mecanique Non-lineaire]
```
* TEST SNAP
* EXEMPLE D UTILISATION DE LA PROCEDURE PASAPAS ( ET INCREME)
* PROBLEME DE GRANDS DEPLACEMENTS
* PROBLEME DU SNAP une seule barre est maillee et calculee
* \/ F
TITRE ' SNAP ' ;
* TEMPS ;
* ------------- geometrie ligne ST formee d' 1  SEG2 -------------------
* PAR SYMETRIE, ON N'ETUDIE QUE LA MOITIE
OPTI ECHO 0 ;
OPTI DIME 2 ELEM SEG2 MODE PLAN CONT ;DENS 1. ;
P1 = 0. 1. ; P2 = 10. 0. ;
ST = P1 D 1 P2 ;
* ------------ calcul mecanique . ------------------
 MO = MODE ST MECANIQUE BARR ;
* MATERIAU ET CARACTERISTIQUES
MA1 = MATE MO YOUN 2.1E11 NU 0.3 ;
CAR1 = CARA MO SECT 0.05 ;
MACA= MA1 ET CAR1;
* ----------- calcul de la rigidite --------------------------------------
RI1 = RIGI MACA MO ;
* ----------- definition des conditions aux limites ----------------------
CL1 = BLOQ UX P1 ;
CL2 = BLOQ UX P2 ;
CL3 = BLOQ UY P2 ;
CL4 = BLOQ UY p1;
CL = CL1 ET CL2 ET CL3 ;
* ----------- definition du chargement -----------------------------------
FP11 = FORCE ( 0 -12.5e5 ) p1;
LIX1 = PROG 0. 40. ;
LIY1 = PROG 0. 40. ;
EV1 = EVOL MANU T LIX1 F(T) LIY1 ;
* ----------- resolution par la procedure NONLIN -------------------------
* CALCUL EN GRANDS DEPLACEMENTS
TAB2 = TABLE ;
CHA1 = CHAR MECA FP11 EV1 ;
TAB2.'GRANDS_DEPLACEMENTS'=VRAI;
TAB2.'AUTOMATIQUE' = VRAI;
* ---------- pilotage suivant le deplacement du point P1
'DEBPROC' AUTOPILO DELT*'CHPOINT' DELA*'CHPOINT' ZMOD*'MMODEL'
          ZMAT*'MCHAML' TTT*TABLE ;
      NORM1 = (extraire delt p1 'UY' ) *-1 ;
* mess ' norm1 ' norm1;
FINPROC NORM1;
TAB2.'AUTOPAS' = 200;
TAB2.'AUTOCRIT' = 0.075;
TAB2.'AUTORESU' = 1;
TAB2.'BLOCAGES_MECANIQUES' = CL;
TAB2.'MODELE' = MO;
TAB2.'CARACTERISTIQUES' = MACA;
TAB2.'CHARGEMENT' = CHA1;
LIS11 = PROG 0. 2. ;
TAB2.'TEMPS_CALCULES' = LIS11;
tab2.'REAC_GRANDS'=200.;
PASAPAS TAB2 ;
* ----------- resultats --------------------------------------------------
* courbe de snap through : montee descente montee
PGX = PROG 0.;
PGY = PROG 0.;
NDIM = (DIME ( TAB2 . DEPLACEMENTS )) - 1 ;
REPETER TBOU2 NDIM ;
LEDEP = TAB2 . DEPLACEMENTS. (&TBOU2);
REA1 = REAC CL3 LEDEP ;
V = EXTR LEDEP UY P1 ;
PGX = PGX ET ( PROG V ) ;
VV = EXTR REA1 FY P2 ;
PGY = PGY ET ( PROG VV ) ;
FIN TBOU2 ;
pgx = pgx * -1.;
strou = mini pgy;
sref = -2.e+6;
smp= sref * 1.05;smb = sref * 0.95;
mess ' borne min ' smp 'valeur trouvée' strou 'borne max' smb;
si (( strou > smb ) ou ( strou < smp) ) ;
   erreur (5);
finsi;
* EV5 = EVOL TURQ MANU 'Deplacement' PGX 'Force de reaction' PGY ;
* DESS EV5 ;
fin;
```

## FissVoil [Mecanique Nonlineaire]
```
graph = faux ;
* CAS TEST DU 13/11/14 PROVENANCE : TEST
SAUT PAGE;
* TEST PROCEDURE OUVCOR POUR UN PANEL EN CISSAILEMENT
* 4. * 1. * 0.2
* Le maillage est en 3D a l'aide d'elements
* massif CUB8. L'acier est maille a l'aide d'elements
* barre.
* MAILLAGE
opti dime 3 ;
opti elem cub8 ;
dfi = 0.15 ;
P1 = 0. 0. 0 ;
P2 = 4. 0. 0 ;
DT = DROI P1 P2 dini dfi dfin dfi ;
SM = DT TRANS (0 1. 0) dini dfi dfin dfi ;
DT = SM COTE 3 ;
VT = VOLU SM TRANS (0 0 0.2) dini dfi dfin dfi ;
elim 1.e-4 VT ;
* definition des renforcements dans la pertie centrale
* barre verticale
PA1 = 2. 0.05 0.05 ;
PA2 = PA1 PLUS (0 (1. - 0.05) 0) ;
DV = DROI PA1 PA2 dini dfi dfin dfi ;
* barres horizontales
P1 = 0.05 0.5 0.055 ;
P2 = P1 PLUS ((4. - 0.05) 0 0) ;
DH = DROI P1 P2 dini dfi dfin dfi ;
STRUCT = vt et dv et dh ;
MODB = MODE VT MECANIQUE ELASTIQUE ISOTROPE
                 ENDOMMAGEMENT DAMAGE_TC ;
* aciers
MODA = MODE (DH ET DV) MECANIQUE ELASTIQUE ISOTROPE
                PLASTIQUE ISOTROPE BARR ;
MODTOT = MODB et MODA;
* propriétés mécaniques
 yg = 22.e9 ;
 nub = 0.19 ;
 rhom = 2410 ;
 Gvalm = 300. ;
 ftulm = 3.3e6 ;
 redcm = 1.7e6 ;
 fc01m = -25.e6 ;
 rt45m = 1.18 ;
 fcu1m = -42.5e6 ;
 extum = -0.015;
 strpm = -22.e6 ;
 extpm = -0.001 ;
 ext1m = -0.006 ;
 str1m = -35.e6 ;
 ext2m = -0.008 ;
 str2m = -22.e6 ;
ncrim = 1 ;
jaco1 = jaco modb ;
jaco2 = chan 'RIGIDITE' modb jaco1 ;
hlenm = jaco2**(1./3.) ;
matb = mate modb YOUN yg NU nub RHO rhom HLEN hlenm
                   GVAL Gvalm FTUL ftulm REDC redcm FC01 fc01m
                   RT45 rt45m FCU1 fcu1m STRU extum EXTP extpm
                   STRP strpm EXT1 ext1m STR1 str1m EXT2 ext2m
                   STR2 str2m NCRI ncrim ;
* aciers renforcement
EA = 189274e6 ;
NUA = 0.3 ;
fe=554.e6;
ETa=3245.e6;
epsel = fe/Ea;
epsfin = 2.7e-2 .;
leps = prog 0. epsel epsfin;
sigfin = fe + (eta*(epsfin - epsel));
lsig = prog 0. fe sigfin;
evsig = evol manu leps lsig;
lsig = lsig enle 1 ;
leps = (leps enle 1) - (lsig / ea) ;
evecr = evol vert manu eps leps sig lsig ;
si graph ;
  dess (evsig et evecr) titr 'Courbes de traction et d ecrouissage (vert)' ;
fins ;
MATA = MATE MODA YOUN EA NU NUA RHO 7850
                   ECRO evecr SECT 7.85e-5 ;
MATOT = MATB et MATA;
* CONDITIONS AUX LIMITES
p1 = vt poin proc (0 0 0);
p2 = vt poin proc (1 0 0);
p3 = vt poin proc (1 0 1);
sb = vt poin plan p1 p2 p3 1e-4;
p1 = vt poin proc (p1 plus (0 1 0));
p2 = vt poin proc (p2 plus (0 1 0));
p3 = vt poin proc (p3 plus (0 1 0));
sh = vt poin plan p1 p2 p3 1e-4;
pp1 = vt poin proc (0 0 0);
pp2 = vt poin proc (1 0 0);
pp3 = vt poin proc (0 4 0);
ss = vt poin plan pp1 pp2 pp3 1e-4;
cl1 = BLOQ sh ux;
cl2 = BLOQ sb ux uy;
cl3 = BLOQ sh uy ;
cl4 = BLOQ ss uz ;
cl5 = RELA ACCRO (DV ET DH) VT 1.e-4 ;
cltot = cl1 et cl2 et cl3 et cl4 et cl5;
* chargement en déplacement
FO1 = DEPI cl1 (1) ;
list1 = prog 0 1;
list2 = prog 0 1.5e-3 ;
evol1 = evol manu list1 list2 ;
char1= CHAR MECA FO1 evol1;
* RESOLUTION : PASAPAS
listt = prog 0 pas 0.05 1 ;
tab1 = TABLE;
tab1 . MODELE = modtot ;
tab1 . CARACTERISTIQUES = matot ;
tab1 . CHARGEMENT = char1 ;
tab1 . BLOCAGES_MECANIQUES = cltot ;
tab1 . TEMPS_CALCULES = listt ;
tab1 . MOVA = 'RIEN' ;
PASAPAS tab1 ;
* POST-TRAITEMENT AVEC OUVCOR
* initou
tab1.geo = vt;
tab1.poi = vt poin proc (0. 0. 0.);
tab1.hor = vrai;
tab1.pla = 'XY';
tab1.pas = 20;
tab1.lh = 2.;
tab1.lb = 0.;
tab1.lg = 0.;
tab1.ld = 4.;
tab1.crito = 1.e-9;
tab1.critp = 1.e-5;
initou tab1;
* zonfis
tab1.droi = faux;
hau = 2.;
bas = 0.;
nha = 4;
nba = 2;
pha = 1;
pba = 1;
gau = -0.05;
dro = 0.05;
alpha = 0.;
zonfis tab1 pha pba nha nba hau bas gau dro alpha;
* postou
dist = 0.03;
tab1.critt = 0.5;
* postou tab1 dist;
fin;
```

## grot1 [Mecanique Plastique]
```
opti dime 2 elem qua4 mode plan defo;
opti echo 0;
* grandes rotations sur un element 2D-DP
* calcul elastique lineaire
l = 1000.;
p1 = 0 l;
p3 = 0 0;
d1 = droit 1 p3 p1;
plaq = d1 tran 1 (l 0);
p2 = (enve plaq) poin proc (l l) ;
p4 = (enve plaq) poin proc (l 0);
* creation du modele
objaf = MODE plaq mecanique elastique plastique parfait;
* caracteristiques du materiau
mat = MATE objaf YOUNG 200000. NU 0.3 SIGY 10E6 ;
* calcul des rigidites elementaires
* et
* definition des blocages
* deplacement impose
cdl1 = bloq UX p1;
cdep1 = depi cdl1 (-1000.);
cdl11 = bloq UY p1;
cdep11 = depi cdl11 (-1000.);
cdl2 = bloq UX p2;
cdep2 = depi cdl2 (-2000.);
cdl21 = bloq UY p2;
cdep21 = depi cdl21 0;
cdl3 = bloq UX p3;
cdep3 = depi cdl3 0;
cdl31 = bloq UY p3;
cdep31 = depi cdl31 0;
cdl4 = bloq UX p4;
cdl41 = bloq UY p4;
cdep4 = depi cdl4 (-1000.);
cdep41 = depi cdl41 (1000.);
cdlt = cdl1 et cdl11 et cdl2 et cdl21 et cdl3 et cdl31
       et cdl4 et cdl41;
fo1 = cdep1 et cdep11 et cdep2 et cdep21 et cdep3 et cdep31
      et cdep4 et cdep41 ;
cdep41 = depi cdl41 1100.;
cdep21 = depi cdl21 100.;
fo2 = cdep1 et cdep11 et cdep21 et cdep3 et cdep31
      et cdep4 et cdep41 et cdep2;
* creation du chargement
li1 = prog 0 19 20;
li3 = prog 0 1 0;
li4 = prog 0 0 1;
li5 = prog 0 pas 19 19 pas 1 20;
evt2 = evol manu t li1 f li3;
evt3 = evol manu t li1 f li4;
cha1 = char 'DIMP' fo1 evt2;
cha2 = char 'DIMP' fo2 evt3;
* resolution avec pasapas
tab1 = table;
tab1.'GRANDS_DEPLACEMENTS' = vrai;
tab1.'BLOCAGES_MECANIQUES' = cdlt;
tab1.'MODELE' = objaf;
tab1.'CARACTERISTIQUES' = mat;
tab1.'CHARGEMENT' = cha1 et cha2;
tab1.'TEMPS_CALCULES' = li5;
pasapas tab1;
pp = react cdl21 (tab1.'DEPLACEMENTS'.(2));
ppa = 1.34310E+07;
ppy = maxi pp;
err1 = abs ((ppy - ppa)/ppa);
SI (ERR1 < 1.E-2);
    ERRE 0;
SINO;
    ERRE 5;
FINSI;
fin;
```

## j2_bcn [Mecanique Plastique]
```
* PERFORATED STRIP UNDER TRACTION
* TEST: J2 perfect plasticity model
* ------------- OPCIONES GENERALES --------------------------------
GRAPH = 'N' ;
OPTION DIME 2 TRAC x ELEM qua8 MODE plan defo;
* ------------- CREACION DE LA GEOMETRIA --------------------------
p1 = 5. 0.;
p2 = 10. 0.;
p3 = 10. 18.;
p4 = 0. 18.;
p5 = 0. 5.;
pce = 0. 0.;
aux = 0.7071067 * 5.;
p6 = aux aux;
den = 12;
l12 = d den p1 p2;
l23 = d den p2 p3;
l36 = d den p3 p6;
l61 = cerc den p6 pce p1;
l34 = d den p3 p4;
l45 = d den p4 p5;
l56 = cerc den p5 pce p6;
l63 = d den p6 p3;
mall1 = daller l12 l23 l36 l61;
mall2 = daller l34 l45 l56 l63;
malla = mall1 et mall2;
elim 1.E-3 malla;
* ------------- MODELO -------------------------------------------
 NUHOR = 0.2;
 ROHOR = 2.5e3;
 E_ELAS = 7.e7;
 E_PLAS = 0.e0;
 K_PLAS = (E_PLAS*E_ELAS)/(E_ELAS-E_PLAS);
 SININI = 2.43e5;
 SINFIN = 0.;
 VELOCI = 0.;
 mod1 = model malla mecanique elastique plastique j2;
 mat1 = mater mod1 youn E_ELAS nu NUHOR rho ROHOR
                     sig0 SININI sigi SINFIN kiso K_PLAS
                     velo VELOCI;
* mod1 = model malla mecanique elastique plastique parfait;
* mat1 = mater mod1 youn E_ELAS nu NUHOR
* sigy SININI ;
* -------------- MATRICES DE RIGIDEZ -----------------------------
 rig1 = rigi mod1 mat1;
* -------------- CONDICIONES DE CONTORNO -------------------------
 rigcont1 = bloq uy l12;
 rigcont2 = bloq ux l45;
 rigcont = rigcont1 et rigcont2;
 rig2 = rig1 et rigcont;
* -------------- MOVIMIENTO IMPUESTO -----------------------------
 rigsupe = bloq uy l34;
 valor = .1;
 movyy = depi rigsupe valor;
 evol1 = evol manu t (prog 0. 1.) level (prog 0. 1.);
 evfut = char dimp evol1 movyy;
* --------------- RESOLUCION -------------------------------------
 maxiter = 15;
 t0 = table;
 t0.MODELE = mod1;
 t0.CARACTERISTIQUES = mat1;
 t0.BLOCAGES_MECANIQUES = rigcont et rigsupe;
 t0.CHARGEMENT = evfut;
 t0.ACCELERATION = maxiter;
 t0.MAXITERATION = maxiter;
 t0.PRECISION = 1.E-10;
 t0.CONVERGENCE_FORCEE = faux;
 t0.K_TANGENT = vrai;
 t0.TEMPS_CALCULES = prog 0. pas 0.1 1.;
 t0.TEMPS_SAUVES = t0.TEMPS_CALCULES;
 t0.HYPOTHESE_DEFORMATIONS = 'LINEAIRE' ;
 pasapas t0;
* --------------- POSTPROCESO ------------------------------------
 imax = 10;
 fuer = prog 0.;
 i = 1;
 repeter blocdefi imax;
   aux = reac rigsupe t0.deplacements.i;
   aux = resu aux;
   pbas = extr aux MAIL ;
   pbas = POIN 1 pbas ;
   aux = extr aux fy pbas;
   fuer = fuer et (prog aux);
   i=i+1;
 fin blocdefi;
 law = evol manu t (prog 0. pas 0.02 0.2) f(t) fuer;
 SI (NEG GRAPH 'N') ;
   dessin law;
  @cartoon t0 malla 1.;
 FINSI ;
 err = (aux - 1.40382E+06)/1.40382E+06 ;
 list err;
 SI ((ABS err) < 0.5e-5) ;
   ERRE 0 ;
 SINON ;
   ERRE 5 ;
 FINSI ;
 FIN;
```

## plas14 [Mecanique Plastique]
```
* Test Plas14.dgibi: Jeux de données
graph='N';
saut page;
opti echo 1;
* EXEMPLE OF A CONCRETE SQUARE SECTION WITH 4 STEEL
* 20mm BARS
* CONCRETE DIMENSIONS: (0.25*0.25)m2 - ALL SECTION
* (0.20*0.20)m2 - CORE SECTION
* TRANSVERSAL REINFORCEMENT: 10mm Bars / 7.0cm
* NOVEMBER 1993
* Quadrangular Elements
* opti dime 2 elem qua4 echo 1 ;
   opti dime 2 echo 1 ;
* Triangular Elements
* opti dime 2 elem tri3;
* DEFINITION OF THE STEEL GEOMETRY
secste = 3.14159*((10.e-3)**2);
cars1 = ( 8.50e-2 8.50e-2);
cars2 = ( 8.50e-2 -8.50e-2);
cars3 = (-8.50e-2 -8.50e-2);
cars4 = (-8.50e-2 8.50e-2);
meshf = cars1 et cars2 et cars3 et cars4;
meshf = coul meshf bleu;
* Quadrangular Elements
   opti dime 2 elem qua4 echo 1 ;
* DEFINITION OF THE CONCRETE GEOMETRY
* - UNCONFINED
* verd - vertical number of divisions
* hord - horizontal number of divisions
verd = 4;
hord = 4;
divu = 1;
pc1 = -12.5d-2 12.5d-2;
pc2 = -12.5d-2 10.0d-2;
pc3 = 2.5d-2 0.0d-2;
carc1 = pc1 d (divu) pc2 tran (divu) pc3;
carc2 = carc1 plus ( 22.5d-2 0.0);
carc3 = carc2 plus ( 0.0 -22.5d-2);
carc4 = carc3 plus (-22.5d-2 0.0);
pc4 = -10.0d-2 12.5d-2;
pc5 = -10.0d-2 10.0d-2;
pc6 = 20.0d-2 0.0d-2;
carc5 = pc4 d (divu) pc5 tran (verd) pc6;
carc6 = carc5 plus ( 0.0 -22.5d-2);
pc7 = -12.5d-2 10.0d-2;
pc8 = -10.0d-2 10.0d-2;
pc9 = 0.0d-2 -20.0d-2;
carc7 = pc7 d (divu) pc8 tran (hord) pc9;
carc8 = carc7 plus ( 22.5d-2 0.0);
meshu = carc1 et carc2 et carc3 et carc4 et carc5 et carc6 et carc7 et carc8;
meshu = coul meshu jaune;
* opti donn 5;
* - CONFINED
pc10 = -10.0d-2 10.0d-2;
pc11 = 10.0d-2 10.0d-2;
pc12 = 0.0d-2 -20.0d-2;
meshc = pc10 d (verd) pc11 tran (hord) pc12;
meshc = coul meshc rouge;
elim (meshf et meshu et meshc) 0.001;
titre 'Section:blue=steel,yellow=unconfined concrete ,red=confined concrete';
si (ega graph 'Y');
trac (meshf et meshu et meshc);
finsi;
opti dime 3 elem seg2;
pp0 = 0.0 .0 .0;
pp1 = 1.0 .0 .0;
llb = pp0 d 1 pp1;
elim (llb et pp0 et pp1) 0.001;
* CARACTERIZATION OF THE STEEL AND CONCRETE MODELS
* Quadrangular Elements
   modf = MODE meshf mecanique elastique PLASTIQUE ACIER_UNI pojs;
   modbs = MODE meshf mecanique elastique PLASTIQUE ACIER_ANCRAGE pojs;
   modu = MODE meshu mecanique elastique PLASTIQUE BETON_UNI quas;
   modc = MODE meshc mecanique elastique PLASTIQUE BETON_UNI quas;
   modlab = MODE (meshc et meshu) mecanique elastique PLASTIQUE UNILATERAL quas;
   modshea = MODE (meshc et meshu) mecanique elastique plastique cisail_nl quas;
   modshea2 = MODE (meshc et meshu) mecanique elastique plastique cisail_nl quas;
* Triangular Elements
* modf = MODE meshf mecanique elastique fibre_nl
* ferraille tris;
* modu = MODE meshu mecanique elastique fibre_nl
* beton tris;
* modc = MODE meshc mecanique elastique fibre_nl
* beton tris;
* Steel
matf = MATE modf 'YOUN' 2.03e5 'NU' 0.30 'STSY' 440.0 'EPSU' .090 'STSU' 760.0 'EPSH' 0.030 'FALD' 4.375 'A6FA' 620.0 'CFAC' 0.5 'AFAC' 0.008 'ROFA' 20.0 'BFAC' 0.010 'A1FA' 18.5 'A2FA' 0.15 'RHO ' 7.8D-3 ;
carf = 'CARA' modf 'ALPY' 1. 'ALPZ' 2. 'SECT' secste;
* Bond slip for lap splices
G12 = 0.1*(30000./(2.*(1+0.25)*0.05));
xs1t = 0.0006;
xs2t = 0.0020;
xs3t = 0.0060;
xt1t = 5.;
xt3t = 0.15*xt1t;
xalfa = 0.4;
mess G12;
mess (xt1t/xs1t);
matbs = MATE modbs 'YOUN' 2.03e5 'NU' 0.30 'STSY' 440.0 'EPSU' .090 'STSU' 760.0 'EPSH' 0.030 'FALD' 4.375 'A6FA' 620.0 'CFAC' 0.5 'AFAC' 0.008 'ROFA' 20.0 'BFAC' 0.010 'A1FA' 18.5 'A2FA' 0.15 'RHO ' 7.8D-3 'G12 ' G12 'S1T' xs1t 'S2T' xs2t 'S3T' xs3t 'T1T' xt1t 'T3T' xt3t 'ALFA' xalfa 'SECB' (pi*((0.020/2.)**2)) 'LANC' (10.*0.020) 'SECT' secste;
carbs = 'CARA' modbs 'ALPY' 0. 'ALPZ' 0.;
* Unconfined concrete
matu = MATE modu 'YOUN' 0.30e5 'NU' .20 'STFC' 30.0 'EZER' .002 'STFT' 3.0 'ALF1' .22687 'OME1' .32912 'ZETA' 100.0 'ST85' .0 'TRAF' 3.0 'FACL' 1. 'FAMX' 10. 'STPT' .0 'FAM1' 1. 'FAM2' 10. 'RHO ' 2.3D-3;
caru = 'CARA' modu 'ALPY' .66 'ALPZ' .00;
* Confined concrete
* Initial concrete Young modulus =
* 2 * STIFC / ( BETA * EZERO )
matc = MATE modc 'YOUN' 0.2254e5 'NU' .25 'STFC' 30.0 'EZER' .002 'STFT' 3.0 'ALF1' .22687 'OME1' .32912 'ZETA' 0.0 'ST85' 6.0 'TRAF' 3.0 'FACL' 1. 'FAMX' 10. 'STPT' .0 'FAM1' 1. 'FAM2' 10. 'RHO ' 2.3D-3;
carc = 'CARA' modc 'ALPY' .66 'ALPZ' .00;
* Laborderie
matlab = MATE modlab 'YOUN' 0.297E+5 'NU' .20 'YS1 ' 2.5E-4 'YS2 ' 1.5E-3 'A1  ' 5000. 'A2  ' 10. 'B1  ' 1.5 'B2  ' 1.5 'BET1' 1.0 'BET2' -40. 'SIGF' 3.5 'RHO ' 7.8D-3;
carlab = 'CARA' modlab 'ALPY' .66 'ALPZ' .00;
* Linear shear behaviour
EbetJoi = 22540.;
xnub = 0.25;
tultshea = (0.9*500.*pi*((10./2000.)**2))/(0.20*0.07);
GY = EbetJoi/(2.*(1.+XNUB));
UXX1=PROG 0. (0.98*tultshea/GY) (tultshea/GY) (2.*(tultshea/GY)) (10.*(tultshea/GY)) ;
SHEAR1=PROG 0. (0.99*tultshea) tultshea tultshea tultshea;
EP = (extr SHEAR1 2)/(extr UXX1 2);
DMAXP = 1. - ((extr SHEAR1 3)/(EP*(extr UXX1 3)));
DMAXN = DMAXP;
DELAP = (extr UXX1 2);
DELAN = DELAP;
E2F = (1.-DMAXP)*EP;
XNU = 0.;
XMONOP = PROG;
XMONON = PROG;
YMONOP = PROG;
YMONON = PROG;
J0 = 2;
  REPETER LAB2 ((DIME SHEAR1) - 2);
    J0 = J0 + 1;
    YY = (EXTR SHEAR1 J0);
    XX = ((EXTR UXX1 J0) - ((extr SHEAR1 J0)/E2F));
    XMONOP = INSE XMONOP (J0 - 2) (MAXI (PROG XX 0.));
    YMONOP = INSE YMONOP (J0 - 2) YY;
  FIN LAB2;
XMONON = (XMONOP);
YMONON = (YMONOP);
monop = evol manu XMONOP YMONOP;
monon = evol manu XMONON YMONON;
matshea = mate modshea 'YOUN' ebetjoi 'NU  ' XNUB 'DELP' delap 'DMAP' dmaxp 'DELN' delan 'DMAN' dmaxn 'BETA' 0.2 'ALFA' 0. 'TETA' 1. 'MONP' monop 'MONN' monon 'RHO ' 0. 'ALPY' 0. 'ALPZ' 1.;
modq = modf et modu et modc et modshea;
macq = matf et matu et matc et carf et caru et carc et matshea;
modq2 = modbs et modu et modc et modshea;
macq2 = matbs et matu et matc et carbs et caru et carc et matshea;
modq3 = modf et modlab et modshea;
macq3 = matf et matlab et carf et carlab et matshea;
* USE OF "MOMCUR" PROCEDURE FOR THE ANALYSIS OF THE
* PLASTIC BEHAVIOUR SECCION
* CARACTERIZATION OF THE ACTION
* (CURVATURES ALONG OY AXIS AND CONSTANT AXIAL FORCE)
eppl = 440.0/2.03e5;
cy = prog 0 pas .0005 .005 pas .005 .138;
ncur = dime cy;
cz = prog ncur * .00;
fa = (prog ncur * -.25);
* RESOLUTION
my mz ea moc1 = mocu cy cz fa modq macq (1.d-6*eppl) verif;
* opti donn 5;
si (ega graph 'Y');
nste = dime (moc1 . contraintes);
repete bouc nste;
toto = redu (modc et modu) (moc1 . contraintes . (&bouc - 1));
titre 'pas' &bouc '---' 'SMXX' '---' 'deformation normale =' (moc1 . deformations .(&bouc - 1));
trac (exco toto SMXX) (modc et modu) (matc et matu) (meshu et meshc) ;
toto = redu (modc et modu) (moc1 . variables_internes . (&bouc - 1));
titre 'pas' &bouc 'EPSO';
trac (exco toto EPSO) (modc et modu) (matc et matu) (meshu et meshc) ;
 fin bouc;
finsi;
my2 mz2 ea2 moc2 = mocu cy cz fa modq2 macq2 (1.d-6*eppl) verif;
si (ega graph 'Y');
nste = dime (moc2 . contraintes);
repete bouc nste;
toto = redu (modc et modu) (moc2 . contraintes . (&bouc - 1));
titre 'pas' &bouc 'SMXX';
trac (exco toto SMXX) (modc et modu) (matc et matu) (meshu et meshc) ;
 fin bouc;
finsi;
my3 mz3 ea3 = mocu cy cz fa modq3 macq3 (1.d-6*eppl);
* OUTPUT DIAGRAMS
c1= evol rouge manu 'Curvature' cy 'Moment' (my*1.d3);
c2= evol vert manu 'Curvature' cy 'Moment' (my2*1.d3);
c3= evol bleu manu 'Curvature' cy 'Moment' (my3*1.d3);
* TRILINEAR CURVE FOR A TAKEDA MODEL
* FOR THE SAME SECTION
* abstak=prog 0. 2.03791E-03 1.85207E-02 1.38834E-01;
abstak=prog 0. 2.03791E-03 1.85207E-02 1.38E-01;
* ordtak=prog 0. 2.05353E+01 7.10923E+01 7.06633E+01;
ordtak=prog 0. 21.133 71.1 72.817;
albnl=evol vert manu 'Curvature' abstak 'Moment' ordtak;
* PLOT
si (ega graph 'Y');
  tt = table;
  tt.1 = 'MARQ CARR';
  tt.2 = '';
  titre 'courbe mocu (blanc: beton uni et bleu: unilateral) , takeda (vert)  et avec lap splices (rouge)';
  dess (albnl et c1 et c2 et c3) tt;
finsi;
* ERREUR
ordtak=ipol cy abstak ordtak;
errlis=ordtak - (my*1.d3);
errea=((ltl errlis errlis)**0.5) / (dime ordtak);
denom=((ltl ordtak ordtak)**0.5) / (dime ordtak);
errel=errea/denom;
mess 'erreur relative=' errel '(+-=3.5%)';
si (errel > 4.d-2); erre 5;
sinon; erre 0;
finsi;
* TEST 3D
* Modèle avec une rotule non lineaire
* et un element de poutre linéaire
pp0 = 0.0 .0 .0;
pp1 = 0.10 0. 0.;
pp2 = 1.0 .0 .0;
llhinge = pp0 d 1 pp1;
llelast = pp1 d 2 pp2;
modhing = 'MODE' llhinge mecanique elastique SECTION PLASTIQUE SECTION TIMO;
mathing = MATE modhing MODS modq MATS macq 'VECT' (0. 1. 0.);
modhing2 = 'MODE' llhinge mecanique elastique SECTION PLASTIQUE SECTION TIMO;
mathing2 = MATE modhing2 MODS modq2 MATS macq2 'VECT' (0. 1. 0.);
* modelas = 'MODE' llelast mecanique elastique SECTION PLASTIQUE
* SECTION TIMO;
* matelas = MATE modelas MODS modq MATS macq
* 'VECT' (0. 1. 0.);
XXINRZ = (0.25**4)/12.;
modelas = 'MODE' llelast mecanique elastique POUT;
matelas = MATE modelas YOUN ((1./3.)*0.297E+5) NU .20 INRZ XXINRZ INRY XXINRZ TORS XXINRZ SECT (0.25*0.25) 'VECT' (0. 1. 0.) 'RHO ' 2.3D-3;
MODTOT = MODELAS et MODHING;
MATTOT = MATELAS et MATHING;
MODTOT2 = MODELAS et MODHING2;
MATTOT2 = MATELAS et MATHING2;
* Check of the total mass
MASTOT = MASS MODTOT MATTOT;
valmas = maxi (resu (MASTOT * (manu chpo (llhinge et llelast) UX 9.81)));
valmasth = 1.41019E-03;
errel = (valmas - valmasth)/valmasth;
si (errel > 4.d-2); erre 5;
sinon; erre 0;
finsi;
bl0 = BLOQ DEPL ROTA pp0;
bl2 = BLOQ UZ pp2;
dep2 = DEPI bl2 1.;
FV = FORC ((-0.25) 0. 0.) pp2;
time = prog 0. 0.1 1.0;
tidep = prog 0. 0. 0.01;
tiforv = prog 0. 1. 1.;
timecalc = prog 0. 0.1 pas 0.05 1.;
evde = evol manu time tidep;
evfv =evol manu time tiforv;
chade = charg dimp dep2 evde;
chafv = charg fv evfv;
* Linear shear
   TAB = TABLE ;
   TAB.'BLOCAGES_MECANIQUES' = BL0 et BL2;
   TAB.'MODELE' = MODTOT;
   TAB.'CHARGEMENT' = CHADE et CHAFV;
   TAB.'TEMPS_CALCULES' = timecalc;
   TAB.'CARACTERISTIQUES' = MATTOT;
   TAB.'MOVA' = RIEN;
TMASAU=table;
tab . 'MES_SAUVEGARDES'=TMASAU;
TMASAU .'DEFTO'=VRAI;
TMASAU .'DEFIN'=VRAI;
   PASAPAS TAB ;
dtab1=index(tab.deplacements) ;
ndime=dime dtab1 ;
prdep = prog 0.;
prfor = prog 0.;
i=1 ;
REPETER BOU1 (ndime - 1);
i=i+1 ;
d=dtab1.i ;
dep0 = tab.deplacements.d ;
sig0 = tab.contraintes.d ;
var0 = tab.variables_internes.d ;
def0 = tab.deformations_inelastiques.d ;
prdep = prdep et (prog (extr dep0 pp2 UZ));
reabase = reac bl0 dep0;
prfor = prfor et (prog ((-1.)*(extr reabase pp0 FZ)));
FIN BOU1;
depfor = evol manu prdep prfor;
si (ega graph 'Y');
  titre 'courbe effort tranchant - déplacement';
  dess depfor;
finsi;
errl = abs ((maxi (extr depfor ordo) abs) - 7.72465E-02);
si (errl > 4.d-2); erre 5;
sinon; erre 0;
finsi;
fin;
```

## rupt31 [Mecanique Rupture]
```
* Cas test pour la procedure SIF
* 2D, plaque semi-infinie de taille l1 avec fissure interne de taille l2
* Soumise a une contrainte sig, dans la direction orthogonale a la fissure
* Test sur le calcul du KI
* Valeur theorique KI = sig * (pi*l2/(cos(pi*l2/(2*l1))))**0.5
* Options generales
OPTI 'DIME' 2 'MODE' 'PLAN' 'ELEM' 'TRI6' ;
* Parametres
l1 = 10. ;
l2 = 1. ;
sig = 42. ;
* Maillage
p1 = 0. 0. ;
p2 = (l1 - l2) 0. ;
p3 = (l1 + l2) 0. ;
p4 = (2. * l1) 0. ;
p5 = (2. * l1) (5. * l1) ;
p6 = 0. (5. * l1) ;
p7 = p5 SYME 'DROIT' p1 p4 ;
p8 = p6 SYME 'DROIT' p1 p4 ;
* --densites (loin et pres de la fissure)
den1 = l1 / 4. ;
den2 = l2 / 20. ;
l12 = DROI p1 p2 'DINI' den1 'DFIN' den2 ;
l23s = DROI p2 p3 'DINI' den2 'DFIN' den2 ;
l34 = DROI p3 p4 'DINI' den2 'DFIN' den1 ;
l45 = DROI p4 p5 'DINI' den1 'DFIN' den1 ;
l56 = DROI p5 p6 'DINI' den1 'DFIN' den1 ;
l61 = DROI p6 p1 'DINI' den1 'DFIN' den1 ;
con1 = l12 ET l23s ET l34 ET l45 ET l56 ET l61 ;
s1 = SURF con1 ;
l23i = DROI p2 p3 'DINI' den2 'DFIN' den2 ;
l47 = DROI p4 p7 'DINI' den1 'DFIN' den1 ;
l78 = DROI p7 p8 'DINI' den1 'DFIN' den1 ;
l81 = DROI p8 p1 'DINI' den1 'DFIN' den1 ;
con2 = l12 ET l23i ET l34 ET l47 ET l78 ET l81 ;
s2 = SURF con2 ;
stot = s1 ET s2 ;
* Modele et materiau
mo = MODE stot 'MECANIQUE' ;
ma = MATE mo 'YOUN' 200.E9 'NU' 0.3 ;
* Blocages
bl1 = BLOQ 'DEPL' p1 ;
bl2 = BLOQ 'UY' p4 ;
* Chargement
f1 = PRES 'MASS' mo l56 (-1. * sig) ;
f2 = PRES 'MASS' mo l78 (-1. * sig) ;
f = f1 ET f2 ;
* Resolution
r0 = RIGI mo ma ;
rig = r0 ET bl1 ET bl2 ;
u = RESO rig f ;
* Solution de reference
k1ref = sig * ((pi * l2 / (COS (pi * l2 / (2. * l1)))) ** 0.5) ;
* Solution par SIF
t1 = TABL ;
t1 . 'FRTFISS' = p2 ;
t1 . 'LEVRE_1' = l23s ;
t1 . 'MODMIXTE' = VRAI ;
t1 . 'LEVRE_2' = l23s ;
SIF ma u t1 ;
k1sif = t1 . 'K1' ;
errsif = 100. * (k1sif - k1ref) / k1ref ;
* Affichage
OPTI 'ECHO' 0 ;
SAUT 3 'LIGNE' ;
MESS 'BILAN, CALCUL DE KI' ;
MESS ;
MESS 'Solution de reference ' k1ref ;
MESS 'Calcul avec SIF       ' k1sif ;
MESS 'Ecart relatif (%)     ' errsif ;
* Test d'erreur
MESS ; MESS ;
SI ((ABS errsif) > 1.) ;
  ERRE 'ERREUR DANS LE CALCUL DU KI' ;
SINON ;
  MESS 'CAS TEST PASSE AVEC SUCCES !' ;
FINSI ;
FIN ;
```

## TirantLAB [Mecanique Transitoire]
```
* CAS TEST DU 13/11/14 PROVENANCE : TEST
SAUT PAGE;
* TEST ELEMENT COAXIAL COS2 POUR MODELE DE LIAISON
* ACIER-BETONEN REGIME LINEAIRE
* TIRANT 3 m SECTION CARRE 0.1 * 0.1
* Le tirant est maille en 3D a l'aide d'elements
* massif CUB8. L'acier est maille a l'aide d'elements
* barre. Le tirant est soumise sous un chargemet
* monotone.
OPTI ECHO 0;
* parametres
xp1 = 3.;
xp2 = xp1 + 0.1;
yp1 = 0.1;
yp2 = yp1/2.;
nelx = 100;
nely = 1;
nelz = 1;
opti dime 3 elem cub8;
* geometrie et maillage
b1 = 0. 0. 0.;
b2 = xp1 0. 0.;
lib1 = b1 droi nelx b2 ;
sb1 = lib1 tran nely (0. yp1 0.) ;
vol1 = sb1 volu tran nelz (0. 0. yp1) ;
a1 = 0. yp2 yp2; a2 = xp1 yp2 yp2;
PA1 = (-0.1 yp2 yp2) ;
PA2 = (xp2 yp2 yp2) ;
lia1 = droi nelx a1 a2 ;
lia2 = lia1 plus (0. 0. 0.);
D1 = DROI 1 PA1 A1 ;
D2 = DROI 1 A2 PA2 ;
ACI = D1 et D2 et LIA1 ;
acibet = racc lia1 lia2 1.e-4;
vtot = vol1 et acibet;
* loi d adherence
pulo1 = prog 0. 1.;
pulo2 = prog 0. 1.e11;
pulop = evol manu pulo1 pulo2;
* materiaux
* acier
yga = 210.e9;
nua = 0.3;
secc1 = 7.854e-5;
secc2 = 7.854e-5;
* beton
ygb = 30.e9;
nub = 0.2;
* model
* acier
moa= model aci mecanique elastique isotrope barre;
maa = mate moa young yga nu nua SECT secc1;
* beton
mob = model vol1 mecanique elastique isotrope;
mab =MATE mob youn ygb nu nub;
* beton acier
moab = model acibet mecanique elastique isotrope plastique
liaison_acbe cos2;
maab = mate moab 'PULO' pulop 'KN' 1e15 'KS' 1.e11 'SECT' secc2 ;
motot = moa et mob et moab;
matot = maa et mab et maab;
* conditions aux limites
cl1 = rela accro lia2 vol1;
cl2 = bloqu UZ sb1;
cl3 = bloqu depl PA1;
cl4 = bloqu ux PA2;
cl5 = bloqu uz pa2;
cl6 = bloqu uy pa2;
pp1 = 0. 0. 0.;
pp2 = 1. 0. 0.;
pp3 = 1. 0. yp1;
sy1 = vol1 poin plan pp1 pp2 pp3 1.e-4;
cl7 = bloq uy sy1;
cltot = cl1 et cl2 et cl3 et cl4 et cl5 et cl6 et cl7;
* chargement
evo1 = evol manu (prog 0. 1.) (prog 0. 2.e-3);
for1 = depi cl4 1.;
char1 = chargement (for1 ) evo1 dimp;
* table
tab1 = table;
tab1.modele = motot;
tab1.caracteristiques = matot;
tab1.blocages_mecaniques = cltot;
tab1.chargement= char1;
tab1.'PRECISION' = 1.e-5;
tab1.temps_calcules =
prog 0. pas 0.5 1.;
pasapas tab1;
* post traitement
* force
rr0 = reac cl4 tab1.deplacements.1;
rr1 = resu rr0;
fff = extr rr1 'FX' (poin ( extr rr0 mail ) initial );
errf = abs(fff - 33.75e3)/33.75e3;
si (> errf 1e-3);
erreur (5);
finsi;
fin;
```

## fluaendo [Mecanique Viscoendommagement]
```
complet = faux ;
* pour calcul complet mettre complet à : vrai;
OPTI ECHO 1 DIME 2 ELEM QUA8 MODE AXIS;
* MAILLAGE AXISYMETRIQUE EPROUVETTE CYLINDRIQUE
* MATERIAU VISCO-PLASTIQUE ENDOMMAGEABLE DEPENDANT DE LA
* TEMPERATURE POUR N M KK A R EVOL
   P1 = 0 0; P2 = 3E-3 0; P3 = 3E-3 30E-3; P4 = 0 30E-3;
   L1 = P1 P2 DROIT 1 ;
   L2 = P2 P3 DROIT 1 ;
   L3 = P3 P4 DROIT 1 ;
   L4 = P4 P1 DROIT 1 ;
* mesh
   EPROU = L1 L2 L3 L4 DALLER PLAN ;
* boundary conditions
   CL1 = BLOQ L1 UZ ;
   CL3 = BLOQ L4 UR ;
   CL = CL1 ET CL3 ;
* MODE defines the behavior of the material and the finite element
* formulation
   MO = MODE EPROU MECANIQUE ELASTIQUE VISCOPLASTIQUE VISCODOMMAGE;
* where is the load applied ?
   pres=pression mass mo -137. l3 ;
* Definition des coefficients variables avec la temperature
   PROGKSI1 = PROG 0. 2.E5 ;
   PROGK1 = PROG 15. 15. ;
   CTRAC1 = EVOL MANU KSI PROGKSI1 K PROGK1 ;
   PROGKSI2 = PROG 0. 2.E5 ;
   PROGK2 = PROG 75. 75. ;
   CTRAC2 = EVOL MANU KSI PROGKSI2 K PROGK2 ;
CTRAC = NUAGE 'T'*'FLOTTANT' 'EVOL'*'EVOLUTION'
                   1000. CTRAC1 1050. CTRAC2 ;
* lors de l'ecoulement :
* interpolation des coefficients avec la temperature
* car les listes de temperatures ne sont pas identiques pour N
* et les autre coef.
   EVN = EVOL MANU 'T' (PROG 1000 1025 1050 ) 'N   '
                                        (PROG 9 7 5);
   EVM = EVOL MANU 'T' (PROG 1000 1050) 'M   ' (PROG 8 4 );
   EVKK = EVOL MANU 'T' (PROG 1000 1050) 'KK  ' (PROG 2200 800 );
   EVR = EVOL MANU 'T' (PROG 1000 1050) 'R   ' (PROG 7 3 );
   EVA = EVOL MANU 'T' (PROG 1000 1050) 'A   ' (PROG 639 1261 );
* Definition du materiau variable
   MATVAR = MATE MO YOUN 150000. NU 0.3 rho 7800. alph 0. 'TALP' 0. 'TREF' 1000.
                 N EVN M EVM KK EVKK ALP1 0. BLP1 0.
                 R EVR A EVA EVOL CTRAC SMAX 0. ;
* Definition des cartes de temperature
   TEMP0 = MANU CHPO EPROU 1 'T' 1000. ;
   TEMP1 = MANU CHPO EPROU 1 'T' 1050. ;
* Definition du chargement
   LI1 = PROG 0. 3.E7 ; LI2 = PROG 1. 1. ;
   EV = EVOL MANU T LI1 LOAD LI2 ;
   CHA1 = CHAR 'MECA' PRES EV ;
   TEMPSs = TABLE; TEMPE = TABLE;
   TEMPSs.0 = 0. ;TEMPSs.1 = 6000.;
   TEMPE.0 = TEMP0; TEMPE.1 = TEMP1;
   CHA2 = CHAR 'T' TEMPSs TEMPE;
   CHA = CHA1 ET CHA2;
   TAB = TABLE ;
   TAB.'BLOCAGES_MECANIQUES' = CL;
   TAB.'CARACTERISTIQUES' = MATVAR;
   TAB.'MODELE' = MO;
   TAB.'CHARGEMENT' = CHA;
si complet;
   LIS = PROG 0. pas 1.E-1 1. 1.5 2 pas 1 10 15 20 pas 10 100
              150 200 pas 100 800. 850. pas 50 1100 pas 20 1400 ;
sinon;
LIS = PROG 0. pas 1.E-1 1. 1.5 2 ;
finsi;
   TAB.'TEMPS_CALCULES' = LIS;
   PASAPAS TAB ;
* CONTROLE DES RESULTATS AVEC DE LA SOLUTION DE REFERENCE
* OBTENUE PAR ALGORITHME ou par code
si complet;
 REF_D = 5.87E-2 ;
 REF_P = 1.36E-3 ;
sinon;
 REF_D = 3.98156E-05;
 REF_P = 1.51511E-05;
finsi;
* tind=index (tab.resucont); ntind=dime tind ;
* T=tind.ntind;
D = EXTR ( PECHE TAB VARIABLES_INTERNES) 'VHWD' 1 1 1;
P = EXTR ( PECHE TAB VARIABLES_INTERNES) 'EPSE' 1 1 1;
list D; list P;
errd = ABS ((REF_D - D) / REF_D) ;
errp = ABS ((REF_P - P) / REF_P) ;
err = MAXI (prog errd errp) ;
temps;
SI ( ERR <EG 0.05 );
   ERRE 0;
SINON;
   ERRE 5;
FINSI;
FIN;
```

## mistral_dpg [Mecanique Viscoplastique]
```
* Test mistral_dpg.dgibi: Jeux de donnees
  opti echo 1 ;
  opti dime 2 elem qua8 ;
  opti mode plan gene ;
* TEST DE VALIDATION
* MODELE MISTRAL
* ELASTICITE ET PLASTICITE INSTANTANE
* MAILLAGE:
* EPROUVETTE RECTANGULAIRE
* CHARGEMENT:
* DEPLACEMENT LATERAL IMPOSE MONOTONE CROISSANT
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
* Geometrie
  XX = 1. ; YY = 0.5 ;
   P00 = 0. 0. ;
   P10 = XX 0. ;
   P11 = XX YY ; P01 = 0. YY ;
   LX0 = droi 1 P00 P10 ;
   LY1 = droi 1 P10 P11 ;
   LX1 = droi 1 P11 P01 ;
   LY0 = droi 1 P01 P00 ;
* Maillage
   EPROU = dall LX0 LY1 LX1 LY0 ;
* trac EPROU ;
* Modele et materiau
   MODDPG = mode EPROU mecanique elastique orthotrope
                                 viscoplastique mistral
                                 DPGE P00 ;
  VEC1 = 1. 1. ; TETA = 45. ; ICBASE = 0 ;
  SENSIP1 = -2 ; SENSIP2 = 1 ;
  fichier = 'CHAINE' DIVERS '/mimatdpg_par' ;
  PDILT E1 E2 E3 NU12 NU23 NU13 MU12 MU23 MU13
  PNBRE PCOHI PECOU PEDIR PRVCE PECRX PDVDI PCROI PINCR
    = @mistpar fichier SENSIP1 SENSIP2 ;
   MATER = mate MODDPG
             'YG1 ' E1 'YG2 ' E2 'YG3 ' E3
             'NU12' NU12 'NU23' NU23 'NU13' NU13
             'G12 ' MU12
             'ALP1' 0. 'ALP2' 0. 'ALP3' 0. 'TALP' 0. 'TREF' 300.
 'DILT' PDILT 'NBRE' PNBRE 'COHI' PCOHI 'ACOU' PECOU 'EDIR' PEDIR
 'RVCE' PRVCE 'ECRX' PECRX 'DVDI' PDVDI 'CROI' PCROI 'INCR' PINCR
                    'SIP1' SENSIP1 'SIP2' SENSIP2 'IBAS' ICBASE
             'DIRECTION' VEC1 'INCLINE' TETA ;
* Conditions aux limites
   CLX0 = bloq ux LX0 ;
   CLX1 = bloq ux LX1 ;
   CLY0 = bloq uy LY0 ;
   CLY1 = bloq uy LY1 ;
   CL = CLX0 et CLX1 et CLY0 et CLY1 ;
* Chargement
   T1 = 100. ; DT1 = 10. ;
   EPSXY1 = 0.01 ;
   TT0 = 300. ; TT1 = TT0 ;
   PHIT0 = 0. ;
   TEMPS = prog 0. T1 ;
   TEMPSCAL = prog 0. pas DT1 T1 ;
   DEPX = depi CLX1 YY ;
   DEPY = depi CLY1 XX ;
   EVEPS = evol manu TEMPS (prog 0. EPSXY1) ;
   CHADE = char dimp (DEPX et DEPY) EVEPS ;
   TT = manu chpo EPROU 1 'T' 1. ;
   EVTT = evol manu TEMPS (prog TT0 TT1) ;
   CHTT = char 'T' TT EVTT ;
   PHI = manu chpo EPROU 1 'FI' 1. ;
   EVFI = evol manu TEMPS (prog 0. 0.) ;
   CHFI = char 'FI' PHI EVFI ;
   CHA = CHADE et CHTT et CHFI ;
* Valeurs initiales
   VINT0 = zero MODDPG 'VARINTER' ;
   FIT0 = manu chml MODDPG 'FIT ' PHIT0 type 'SCALAIRE' 'STRESSES' ;
   VINT0 = VINT0 + FIT0 ;
* Calcul
   TAB = TABLE ;
   TAB.'VARIABLES_INTERNES' = TABLE ;
   TAB.'BLOCAGES_MECANIQUES' = CL ;
   TAB.'CARACTERISTIQUES' = MATER ;
   TAB.'MODELE' = MODDPG ;
   TAB.'CHARGEMENT' = CHA ;
   TAB.'VARIABLES_INTERNES' . 0 = VINT0 ;
   TAB.'TEMPS_CALCULES' = TEMPSCAL ;
   TAB.'HYPOTHESE_DEFORMATIONS' = 'LINEAIRE' ;
   PASAPAS TAB ;
* Traitement des resultats
   SIG = TAB.'CONTRAINTES' ;
   DEP = tab.'DEPLACEMENTS' ;
   VI = tab.'VARIABLES_INTERNES' ;
   NT = dime TEMPSCAL-1 ;
   ERMAX = 0.001 ;
   SIGT = SIG.NT ;
   SIGT_PO = chang chpo MODDPG SIGT ;
   SIGXX = extr SIGT_PO SMXX P00 ;
   SIGYY = extr SIGT_PO SMYY P00 ;
   SIGZZ = extr SIGT_PO SMZZ P00 ;
   SIGXY = extr SIGT_PO SMXY P00 ;
   DEPT = DEP.NT ;
   EPSIT = epsi DEPT MODDPG 'LINE' ;
   EPSIT_PO = chang chpo MODDPG EPSIT ;
   EPSXX = extr EPSIT_PO EPXX P00 ;
   EPSYY = extr EPSIT_PO EPYY P00 ;
   EPSZZ = extr EPSIT_PO EPZZ P00 ;
   EPSXY = (extr EPSIT_PO GAXY P00)/2. ;
   VIT = VI.NT ;
   VIT_PO = chang chpo MODDPG VIT ;
   EPSP11 = extr VIT_PO EP01 P00 ;
   EPSP22 = extr VIT_PO EP02 P00 ;
   EPSP33 = extr VIT_PO EP03 P00 ;
   EPSP12 = extr VIT_PO EP04 P00 ;
   EPSP13 = extr VIT_PO EP05 P00 ;
   EPSP23 = extr VIT_PO EP06 P00 ;
   mess ;
   mess 'SIGXX SIGYY SIGZZ :    ' SIGXX SIGYY SIGZZ ;
   mess 'SIGXY :                ' SIGXY ;
   mess ;
   mess 'EPSXX EPSYY EPSZZ :    ' EPSXX EPSYY EPSZZ ;
   mess 'EPSXY :                ' EPSXY ;
   mess ;
   mess 'EPSP11 EPSP22 EPSP33 : ' EPSP11 EPSP22 EPSP33 ;
   mess 'EPSP12 EPSP13 EPSP23 : ' EPSP12 EPSP13 EPSP23 ;
   mess ;
* SIGT_XY = exco SIGT 'SMXY' ;
* trac SIGT_XY MODDPG ;
* GAMA_XY = exco EPSIT 'GAXY' ;
* trac GAMA_XY MODDPG ;
   MUXY = 4.E10 ;
   AA = 400.E6 ; BB = 1.E10 ;
   A0 = AA/(2.*MUXY) ;
   A1 = 1. + (BB/MUXY) ;
   EPSPXY1 = (EPSXY1-A0)/A1 ;
   SIGXY1 = AA + (2.*BB*EPSPXY1) ;
   EPSEXY1 = SIGXY1/(2.*MUXY) ;
   ERSIGXY = ABS( (SIGXY/SIGXY1) - 1. ) ;
   EREPSPXY = ABS( (EPSP12/EPSPXY1) - 1. ) ;
   si (ERSIGXY > ERMAX) ;
    mess ;
    mess 'ABS(erreur relative) sur la contrainte > ' ERMAX ;
    mess ERSIGXY ;
   finsi ;
   si (EREPSPXY > ERMAX) ;
    mess ;
    mess 'ABS(erreur relative) sur la deformation plastique > ' ERMAX ;
    mess EREPSPXY ;
    mess ;
   finsi ;
   P_ER = prog ERSIGXY EREPSPXY ;
   ERMA = maxi P_ER ;
   si (ERMA > ERMAX) ;
    ERRE 5 ;
   finsi ;
   fin ;
```

## t_visk2 [Mecanique Viscoplastique]
```
graph='N';
saut page ;
* test loi visk2
opti dime 3 elem cub8 ;
p_ori = 0. 0. 0.; e_x = 1. 0. 0. ; e_y = 0. 1. 0. ;
e_z = 0. 0. 1. ;
p1 = p_ori ;
l1 = p1 d 1 (p1 plus e_x) ;
s1 = l1 trans 1 e_y ;
v1 = s1 volu trans 1 e_z ;
s2 = face 2 v1 ;
misopoin = vrai ;
* ATTENTION le cas faux appelle un peu de travail de l operateur !
si faux ;
mo1 = mode v1 mecanique elastique viscoplastique visk2 ;
ma1 = mate mo1 young 2.e11 nu 0.3 rho 7.8e9 alpha 1.5e-5
  sigy 200.e6 h (0.1*2.e11) eta (2.*0.1*2.e11) hvis (0.1*2.e11) n 5. ;
finsi ;
si vrai ;
mo1 = mode v1 mecanique elastique viscoplastique visk2 ;
ma1 = mate mo1 young 150.e9 nu 0.3 rho 7.8e9 alpha 1.5e-5
        sigy 200.e6 h (0.1*2.e11) eta 0.2e11 hvis (2*0.2e11) n 1 ;
ma2 = mate mo1 young 20.e9 nu 0.3 rho 7.8e9 alpha 1.5e-5
        sigy 75.0e6 h (0.05*2.e11) eta 0.2e11 hvis (2*0.2e11) n 1 ;
finsi ;
si faux ;
mo1 = mode v1 mecanique elastique plastique cinematique ;
ma1 = mate mo1 young 150.e9 nu 0.3 rho 7.8e9 alpha 1.5e-5
         sigy 200.e6 h (0.1*2.e11) ;
ma2 = mate mo1 young 20.e9 nu 0.3 rho 7.8e9 alpha 1.5e-5
         sigy 75.0e6 h (0.05*2.e11) ;
finsi ;
chsig1 = zero mo1 contrain ;
chvar1 = zero mo1 varinter ;
t_ev = table ;
t_prog = table ;
si misopoin ;
t_prog . 1 = (prog 0. pas 1. 8.)*1. ;
t_prog . 2 = (prog 0. pas 1. 8.)*10. ;
sinon ;
t_prog . 1 = prog 0. 1. 2. 2.3 2.6 3. pas 1. 20. ;
t_prog . 2 = prog 0. 10. 20. 23. 26. 30. pas 1. 40. pas 10. 60. ;
finsi ;
* opti impr 'poub' ;
si misopoin ;
 n_tra = 1 ;
sinon ;
 n_tra = 2 ;
finsi ;
repeter b_tra n_tra ;
bl1 = (bloq s1 uz) et (bloq p1 depla) et (bloq l1 uy) ;
bl2 = bloq s2 uz ;
chdimp1 = depi bl2 1.e-3 ;
l_temps = t_prog . &b_tra ;
si misopoin ;
 l_ordo = prog 0. 1. 2. ((dime l_temps) - 3)*3. ;
 l_ordo = l_ordo / 1. ;
sinon ;
 l_ordo = prog 0. 1. 2. 2.3 2.6 ((dime l_temps) - 5)* 3. ;
finsi ;
ev_t = evol manu l_temps l_ordo ;
cha1 = char dimp ev_t chdimp1 ;
tpas = table ;
tpas . modele = mo1 ;
tpas . caracteristiques = ma1 ;
tpas . chargement = cha1 ;
tpas . blocages_mecaniques = bl1 et bl2 ;
tpas . temps_calcules = prog 0. pas 1. 5. ;
* tpas . temps_calcules = prog 0. 1. 2.;
TMASAU=table;
tpas . 'MES_SAUVEGARDES'=TMASAU;
TMASAU .'DEFTO'=VRAI;
TMASAU .'DEFIN'=VRAI;
pasapas tpas ;
tpas . caracteristiques = ma2 ;
tpas . temps_calcules = prog 6. pas 1. 8. ;
pasapas tpas ;
* post-traitement
o_res = prog ;
repeter b_evo (dime tpas . temps) ;
rea1 = reac bl2 tpas . deplacements . (&b_evo-1) ;
si (&b_evo ega 1) ;
 res1 = manu chpo 1 p1 fz 0. ;
sinon ;
 res1 = resu rea1 ;
finsi ;
pe1 = point 1 (extr res1 mail) ;
o_res = o_res et (prog (extr res1 fz pe1)) ;
fin b_evo ;
t_ev . &b_tra = evol manu 'temps(s)' l_temps 'F(1.e3*T)' (o_res/1.e7) ;
fin b_tra ;
tabsymb = table ;
tabsymb . titre = table ;
tabsymb . 1 = 'MARQ CROI' ;
tabsymb . titre . 1 = 'taux defo 0.001/s' ;
tabsymb . 2 = 'MARQ LOSA' ;
tabsymb . titre . 2 = 'taux defo 0.01/s' ;
si (neg graph 'N') ;
 si misopoin ;
 dess (t_ev . 1) lege tabsymb
 titre ' visk2  / resultante / traction et relaxation' ;
 sinon ;
 dess (t_ev . 1 et t_ev . 2) lege tabsymb
 titre ' visk2  / resultante / traction et relaxation' ;
 finsi ;
finsi ;
si misopoin ;
  si ( abs((extr o_res 6) - 2.41830E+08) > 1.e5) ;
    erre 5 ;
  sinon ;
    erre 0 ;
  finsi ;
fin ;
```

## g_theta_utilisateur_1 [Mecanique rupture]
```
* VERIFICATION DE LA PROCEDURE G_THETA
* POUR LE CALCUL DE G POUR UNE FISSURE DROITE
* DANS UN CARRE
* VERIFICATION DU CALCUL DE G VIA EN 2D AVEC
* ELEMENTS STANDARDS ET CHAMP_THETA UTILISATEUR
* EN MODE I PUR
* I - INIT DES DONNÉES CAS_TEST
OPTI 'DIME' 2 'ELEM' 'QUA4' ;
BTRA = FAUX ;
* DONNEES GEOMETRIQUES
A0 = 1. ;
L1 = A0 / 4. ;
DENS1 = L1 / 5. ;
DENS2 = A0 / L1 * DENS1 ;
DENS DENS1 ;
* PROPRIÉTÉS MATÉRIAU
MYOU = 2E11 ;
POI = 0.3 ;
KAPPA = 3-(4*POI) ;
MU = MYOU/(2*(1+POI)) ;
* II - MAILLAGE
* CREATION DES SURFACES
P0 = 0. 0. ;
D1 = DROI (P0 MOIN (L1 0.)) (P0 PLUS (L1 0.)) ;
S1 = D1 TRAN (0. L1) ;
CONT1 = CONT S1 ;
CONT1 = DIFF CONT1 D1 ;
CONT2 = CONT1 HOMO (A0 / L1) P0 ;
S2 = CONT1 REGL 'DFIN' DENS2 CONT2 ;
S1 = S1 ET S2 ;
S2 = S1 SYME 'DROI' P0 (1. 0.) ;
S0 = (S1 COUL 'BLEU') ET (S2 COUL 'ROUG') ;
* TRAC S0 ;FIN ;
* FUSION
PRE1 = 1.E-10 ;
PLIGS = S1 POIN 'DROI' P0 (1. 0.) ;
PLIGS = (COOR 1 PLIGS) POIN 'EGSUPE' (0. - PRE1) ;
PLIGI = S2 POIN 'DROI' P0 (1. 0.) ;
PLIGI = (COOR 1 PLIGI) POIN 'EGSUPE' (0. - PRE1) ;
ELIM PLIGS PLIGI PRE1 ;
* LEVRES ET FRONT
CON0 = CONT S0 ;
PLEVS = S1 POIN 'DROI' P0 (1. 0.) ;
PLEVS = (COOR 1 PLEVS) POIN 'EGINFE' PRE1 ;
LVSUP = CON0 ELEM 'APPUYE' PLEVS ;
PLEVI = S2 POIN 'DROI' P0 (1. 0.) ;
PLEVI = (COOR 1 PLEVI) POIN 'EGINFE' PRE1 ;
LVINF = CON0 ELEM 'APPUYE' PLEVI ;
FRON1 = INTE (CHAN 'POI1' LVSUP) (CHAN 'POI1' LVINF) ;
FRON1 = FRON1 POIN 1 ;
* III - MODELE ET MATERIAU
MOD1 = MODE S0 'MECANIQUE' 'ELASTIQUE' ;
MAT1 = MATE MOD1 'YOUN' MYOU 'NU' POI ;
* IV - CONDITIONS AUX LIMITES POUR LES 2 MODES
* IV.1 - EFFORTS DONNES
* PREPARATIFS
CEXT = DIFF CON0 (LVSUP ET LVINF) ;
SEXT = S0 ELEM 'APPUYE' 'LARGEMENT' CON0 ;
MOD2 = REDU MOD1 SEXT ;
X Y = COOR SEXT ;
X Y = (CHAN 'CHAM' X MOD2 'STRESSES') (CHAN 'CHAM' Y MOD2 'STRESSES') ;
TETA = CHAN (ATG Y (X + 1.E-30)) 'TYPE' 'SCALAIRE' ;
RAY1 = (((X)**2) + ((Y)**2))**0.5 ;
RAY1 = CHAN RAY1 'TYPE' 'SCALAIRE' ;
PREF = 1. / ((2*PI*RAY1)**0.5) ;
COS05 = COS (TETA/2) ;
SIN05 = SIN (TETA/2) ;
COS15 = COS (3*TETA/2) ;
SIN15 = SIN (3*TETA/2) ;
SIG0 = ZERO MOD2 'CONTRAIN' ;
* MODE I :
SXX = PREF*(COS05*(1.-(SIN05*SIN15))) ;
SXY = PREF*(COS05*SIN05*COS15) ;
SYY = PREF*(COS05*(1.+(SIN05*SIN15))) ;
SZZ = POI * (SXX + SYY) ;
SIG1 = SIG0 + (NOMC 'SMXX' SXX) + (NOMC 'SMXY' SXY) + (NOMC 'SMYY' SYY)
                + (NOMC 'SMZZ' SZZ) ;
TCHAR = REDU (BSIG MOD2 SIG1) CEXT ;
* IV.2 - DEPLACEMENT ANALYTIQUE
* PREPARATIFS
X Y = COOR S0 ;
LSUP = (COOR 1 PLEVS) POIN 'EGINFE' (0. - PRE1) ;
LINF = (COOR 1 PLEVI) POIN 'EGINFE' (0. - PRE1) ;
Y = Y + ((COOR 2 LSUP) + 1.E-30) + ((COOR 2 LINF) - 1.E-30) ;
TETA = ATG Y (X + 1.E-30) ;
RAY1 = (((X)**2) + ((Y)**2))**0.5 ;
PREF = (RAY1/(2*PI))**0.5 ;
COS05 = COS (TETA/2) ;
SIN05 = SIN (TETA/2) ;
XI0 = CHAN 'CHPO' MOD1 (ZERO MOD1 'DEPLACEM') ;
* MODE I :
XIX = PREF/(2.*MU)*(COS05*(KAPPA - 1. + (2.*(SIN05**2)))) ;
XIY = PREF/(2.*MU)*(SIN05*(KAPPA + 1. - (2.*(COS05**2)))) ;
USOL = XI0 + (NOMC 'UX' XIX) + (NOMC 'UY' XIY) ;
* V - APPEL A G_THETA
* G_THETA AVEC OPTION 'COUCHE'
SUPTAB = TABL ;
SUPTAB.'OBJECTIF' = MOT 'J' ;
SUPTAB.'FRONT_FISSURE' = FRON1 ;
SUPTAB.'MODELE' = MOD1 ;
SUPTAB.'LEVRE_SUPERIEURE' = LVSUP ;
SUPTAB.'LEVRE_INFERIEURE' = LVINF ;
SUPTAB.'CARACTERISTIQUES' = MAT1 ;
SUPTAB.'SOLUTION_RESO' = USOL ;
SUPTAB.'CHARGEMENTS_MECANIQUES' = TCHAR ;
SUPTAB2 = COPI SUPTAB ;
SUPTAB.'COUCHE' = 4 ;
G_THETA SUPTAB ;
GNUM1 = SUPTAB.'RESULTATS' ;
* G_THETA AVEC LE CHAMP THETA CALCULE AVEC LE NOMBRE DE COUCHES MAIS FOURNI
* DANS L'INDICE 'CHAMP_THETA'
SUPTAB2.'CHAMP_THETA' = SUPTAB.'CHAMP_THETA' ;
SUPTAB3 = COPI SUPTAB2 ;
G_THETA SUPTAB2 ;
GNUM2 = SUPTAB2.'RESULTATS' ;
* G_THETA AVEC CHAMP THETA COMPLETEMENT CREE PAR L'UTILISATEUR
* DANS L'INDICE 'CHAMP_THETA'
PSI PHI = PSIP S0 LVSUP 'DEUX' FRON1 ;
RHO = (((NOMC 'SCAL' PSI)**2.) + ((NOMC 'SCAL' PHI)**2.))**0.5 ;
R1 = L1 ;
R2 = 1.05*R1 ;
FUNC = BORN ((RHO - R2) / (R1 - R2)) 'COMPRIS' 0. 1. ;
THETA = MANU 'CHPO' S0 2 'UX' 1. 'UY' 0. ;
THETA = FUNC * THETA ;
SUPTAB3.'CHAMP_THETA' = THETA ;
G_THETA SUPTAB3 ;
GNUM3 = SUPTAB3.'RESULTATS' ;
* RESULTAT ANALYTIQUE
GANA = (1. - (POI**2.)) / MYOU ;
* CALCUL DES ERREURS
SAUT 'LIGNE' ;
OPTI 'ECHO' 0 ;
MESS 'RESULTAT AVEC ''COUCHE'' :' GNUM1/50 ;
MESS 'RESULTAT AVEC ''CHAMP_THETA'' DE VALEUR IDENTIQUE :' GNUM2 ;
MESS 'RESULTAT AVEC ''CHAMP_THETA'' DIFFERENT :' GNUM3/50 ;
MESS 'RESULTAT ANALYTIQUE :' GANA/50 ;
* ERREURS
GNUM = PROG GNUM1 GNUM2 GNUM3 ;
ERR1 = GNUM - GANA ;
ERR1 = (ABS ERR1) / GANA ;
CRI1 = 1.E-2 ;
SI ((MAXI ERR1) >EG CRI1) ;
    MESS 'ERREUR : L''ERREUR SUR G DEPASSE LE CRITERE' ;
    ERRE 5 ;
FINSI ;
FIN ;
```

## metallurgie_05 [Metallurgie]
```
* TEST METALLURGIE_05
* CALCUL D'UN DIAGRAMME T.R.C. SUR UNE MISE EN DONNEES
* METALLURGIQUE COMPLETE : ACIER 16MND5
* REF : A. Bonaventure, « Évaluation expérimentale et numérique des
* contraintes résiduelles dans des structures soudées en
* multipasse », PhD Theses, 2012
* Appel a la PROCEDURE TRC.PROCEDUR qui genere automatiquement le
* diagramme T.R.C.
'OPTI' 'TRAC' PSC 'EPTR' 10 ;
'OPTI' 'DIME' 2 'ELEM' 'TRI3';
* Temperatures initiales et finales
TINI = 900.;
TFIN = 20. ;
* Calcul automatique de la liste des vitesses de refroidissement
NBVI = 30. ;
VIT1 = 250. ;
VIT2 = 1. ;
VLOG1 ='LOG' VIT1 ;
VLOG2 ='LOG' VIT2 ;
PASLOG =(VLOG2 - VLOG1) / (NBVI - 1);
LRELOG ='PROG' VLOG1 'PAS' PASLOG VLOG2;
LISTREF='EXP' LRELOG;
* MAILLAGE
P1 = 0. 0. ;
P2 = 1. 0. ;
P3 = 0. 1. ;
MAILT ='MANU' 'TRI3' P1 P2 P3 ;
* MODELE
LISTPHA ='MOTS' 'AUST' 'MART' 'BAIN' 'FERR' 'MB  ' ;
LISTREAC ='MOTS' 'MB  ' 'MART' 'BAIN' 'FERR' 'AUST' 'AUST' 'AUST' ;
LISTPROD ='MOTS' 'AUST' 'AUST' 'AUST' 'AUST' 'MART' 'BAIN' 'FERR' ;
LISTTYPE ='MOTS' 'LEBL' 'LEBL' 'LEBL' 'LEBL' 'KOIS' 'LEBL' 'LEBL' ;
NOMCONS ='16MND5';
MODCP1 ='MODE' MAILT 'METALLURGIE' 'PHASES' LISTPHA
                                     'REACTIFS' LISTREAC
                                     'PRODUITS' LISTPROD
                                     'TYPE' LISTTYPE
                                     'CONS' NOMCONS ;
* Materiaux - caracteristiques
* 1ere transformation :
PEQ1 ='EVOL' 'MANU' 'T' ('PROG' 716. 802. )
                    'PEQ1' ('PROG' 0. 1. );
F1 ='EVOL' 'MANU' 'TPOI' ('PROG' -1.D-6 0. )
                    'F1' ('PROG' 0. 1. );
TAU1 ='EVOL' 'MANU' 'T' ('PROG' 716. 802. )
                    'TAU1' ('PROG' 12. 0.5 );
* 2eme transformation : parametres identiques a la premiere
PEQ2 ='CHAN' 'NOMORD' PEQ1 1 'PEQ2';
F2 ='CHAN' 'NOMORD' F1 1 'F2' ;
TAU2 ='CHAN' 'NOMORD' TAU1 1 'TAU2';
* 3eme transformation : parametres identiques a la premiere
PEQ3 ='CHAN' 'NOMORD' PEQ1 1 'PEQ3';
F3 ='CHAN' 'NOMORD' F1 1 'F3' ;
TAU3 ='CHAN' 'NOMORD' TAU1 1 'TAU3';
* 4eme transformation : parametres identiques a la premiere
PEQ4 ='CHAN' 'NOMORD' PEQ1 1 'PEQ4';
F4 ='CHAN' 'NOMORD' F1 1 'F4' ;
TAU4 ='CHAN' 'NOMORD' TAU1 1 'TAU4';
* 5eme transformation
MS5 = 380. ;
KM5 = 0.0247 ;
* 6eme transformation
PEQ6 ='EVOL' 'MANU' 'T' ('PROG' 375 380 405 600 )
                    'PEQ6' ('PROG' 0. 1. 1. 0. );
F6 ='EVOL' 'MANU' 'TPOI' ('PROG' -100. -80. -60. -50. -40. -30. -25. -20. -18. -15. -12. -10. -9. -5. -1. -0.05 0.D0 1.D-6)
                    'F6' ('PROG' 0.005 1.573 2.857 3.417 3.982 4.583 4.833 5.26 5.472 6.033 7.675 11.4 18.45 17.1 0.328 0.00238 0.00238 0.) ;
TAU6 ='EVOL' 'MANU' 'T' ('PROG' 375 380)
                    'TAU6' ('PROG' 1.D6 20 );
* 7eme transformation
PEQ7 ='EVOL' 'MANU' 'T' ('PROG' 625 630 730 735 )
                    'PEQ7' ('PROG' 0 1 1 0 );
F7 ='EVOL' 'MANU' 'TPOI' ('PROG' -8.5 -6.2 -4.7 0. 1.D-6)
                    'F7' ('PROG' 0.001 0.13 1.5 1.5 0. );
TAU7 ='EVOL' 'MANU' 'T' ('PROG' 625 630 )
                    'TAU7' ('PROG' 1.D6 5 );
MATCP1 ='MATE' MODCP1 'PEQ1' PEQ1 'TAU1' TAU1 'F1' F1
                       'PEQ2' PEQ2 'TAU2' TAU2 'F2' F2
                       'PEQ3' PEQ3 'TAU3' TAU3 'F3' F3
                       'PEQ4' PEQ4 'TAU4' TAU4 'F4' F4
                       'MS5' MS5 'KM5' KM5
                       'PEQ6' PEQ6 'TAU6' TAU6 'F6' F6
                       'PEQ7' PEQ7 'TAU7' TAU7 'F7' F7;
* Appel a la procedure TRC.procedur
TRC MODCP1 MATCP1 TINI TFIN LISTREF 'AUST' ;
FIN ;
```

## dp3xx [Nautilus]
```
* Cas test de performace EXECRXT // RESOU et RÃ©olutions
* Depressurisation d'une enceinte type Phébus
* Le maillage correspond à une enceinte cylindrique
* d'environ 10 m3 avec un mur en contact avec la
* paroi verticale (10 cm d'acier)
* Tout le volume est initialement a 1.86bar et 90oC
* et la température du mur est mise à 40oC
* au début du calcul. On calcule la depressurisation
* de cette enceinte sur 50 secondes en n'injectant pas de
* vapeur. La temperature d injection est de 90oC.
* Ce test (un peu long)
* verifie le demarrage de la condensation "
* verifie l'evolution moyenne de la temprature gaz
* verifie la pression max a 50"
* verifie la vitesse max a 50" (Convection naturelle)
* Auteurs : E. Studer, J.P. Magnaud Novembre 1999
* revisite Avril 2002
* Ce test peut utiliser la procedure enceinte
* 1/ il faut l'avoir (ce n'est pas donne a tout le monde)
* 2/ faire enceinte = mot 'ENCEINTE' ;
 COMPLET = FAUX ;
 GRAPH = FAUX ;
* COMPLET = VRAI ;
* GRAPH = VRAI ;
TCPT = FAUX;
TKPR = VRAI;
TRESOU = VRAI;
IMPARA = VRAI;
 'SI' COMPLET ;
 nbit=100;
 DT0 = 1. ;
 n1 = 1 ; n2 = 4 ; n3 = 4 ;
 n4 = 8 ; nn = 2 ;
 n1 = 2 ; n2 = 8 ; n3 = 8 ;
 n4 = 16 ; nn = 4 ;
 n1 = 3 ; n2 = 12 ; n3 = 12 ;
 n4 = 24 ; nn = 6 ;
 n1 = 4 ; n2 = 16 ; n3 = 16 ;
 n4 = 32 ; nn = 8 ;
 'SINON' ;
 nbit= 5 ;
 DT0 = 10. ;
 n1 = 1 ; n2 = 2 ; n3 = 4 ;
 n4 = 4 ; nn = 1 ;
 'FINSI' ;
* Definition du maillage de l'enceinte cylindrique
 'OPTI' 'DIME' 3 'ELEM' 'CU20' 'ECHO' 1 ;
 ri = 1.052 ; sp = 0.10 ; hc = 4.163 ;
 epsi = 1.000e-2 ; ;
 epsi = 1.000e-5 ; ;
 p0 = 0.000 0.000 0.000 ;
 px = -1000.000 0.000 0.000 ;
 py = 0.000 -1000.000 0.000 ;
 pz = 0.000 0.000 1000.000 ;
 cd = 0.000 0.000 -20.000 ;
 ph0 = 0.000 0.000 hc ;
 phx = ri 0.000 hc ;
 phy = 0.000 ri hc ;
 fg1 = 0.25 ;
 fg2 = fg1 * (2.0 ** 0.5) / 2. ;
 p1 = (ri*fg1) 0.000 0.000 ;
 p2 = (ri*fg2) (ri*fg2) 0.000 ;
 p3 = 0.000 (ri*fg1) 0.000 ;
 p4 = ri 0.000 0.000 ;
 p5 = 0.000 ri 0.000 ;
 p6 = (ri+sp) 0.000 0.000 ;
 p7 = 0.000 (ri+sp) 0.000 ;
* Hauteur de l'enceinte
  h1 = 4.163 ;
* Vecteur de translation
  v1 = 0. 0. h1 ;
 l1 = 'DROI' p0 p1 n1 ;
 l2 = 'DROI' p1 p2 n1 ;
 l3 = 'DROI' p2 p3 n1 ;
 l4 = 'DROI' p3 p0 n1 ;
 l5 = 'CERC' p4 p0 p5 (2*n1) ;
 l6 = 'CERC' p6 p0 p7 (2*n1) ;
 basf0= 'DALL' l1 l2 l3 l4 'PLAN' ;
 basf1=('REGL' (l2 'ET' l3) l5 n2) ;
 l44= cote 2 basf1;
 ax4= (inve l4) et l44 ;
 l11= cote 4 basf1;
 ax1= l11 et (inve l1) ;
 basf = basf0 'ET' ('REGL' (l2 'ET' l3) l5 n2) ;
 'ELIM' basf epsi ;
 basf = basf 'ET' ('SYME' basf 'DROI' p0 p3) ;
 ax11 = ('SYME' ax1 'DROI' p0 p3) 'ET' (inve ax1) ;
 'ELIM' basf epsi ;
 basf = basf 'ET' ('SYME' basf 'DROI' p0 p1) ;
 ax44 = (inve ax4) 'ET' ('SYME' ax4 'DROI' p0 p4) ;
 'ELIM' basf epsi ;
 basm = 'REGL' l5 l6 n3 ;
 basm = basm 'ET' ('SYME' basm 'DROI' p0 p3) ;
 'ELIM' basm epsi ;
 basm = basm 'ET' ('SYME' basm 'DROI' p0 p1) ;
 'ELIM' basm epsi ;
* Creation du volume
 dx = ri / 2. ;
 nz1 = ('ENTIER' ( h1 / dx ))*nn ;
 bas = basf 'VOLU' nz1 'TRAN' v1 ;
 mbas = basm 'VOLU' nz1 'TRAN' v1 ;
 mbas = mbas 'COUL' 'ROUG' ;
 plan1 = ax11 'TRAN' nz1 v1 ;
 plan4 = ax44 'TRAN' nz1 v1 ;
 'ELIM' (bas et plan1 et plan4) epsi ;
 mt = bas ;
 wall = mbas ;
 elim (mt et wall) epsi ;
* Localisation d'une brèche éventuelle au bas de l'enceinte
 pjg = 'POIN' basf 'PROC' (0.000 0.000 0.000) ;
 jg = ('ELEM' basf 'APPUIE' 'LARGEMENT' pjg) 'COUL' 'VERT' ;
* Fin de la définition du maillage
* Début de l'initialisation de la procédure ENCEINTE : table RXT
 rxt = 'TABLE' ;
 rxt.'VERSION'= 'V0' ;
 rxt.'TCPT' = TCPT ;
 rxt.'TKPR' = TKPR ;
 rxt.'TRESOU' = TRESOU ;
 rxt.'IMPARA' = IMPARA ;
list (nbno mt);
* opti donn 5;
* -- Nom du volume fluide
 rxt.'vtf' = mt ;
 rxt.'epsi' = epsi ;
* -- Definition des murs de l'enceinte : ici un seul mur
* -- en ACIER dont on traitera la thermique dans l'épaisseur
* -- et que l'on initialise a 40oC
* -- On definit d'abort la matériau ACIER avec sa conductivite
* -- thermique LAMBDA (W/m/K) et le produit ro*Cp (J/m3/K)
 rxt.'THERMP' = VRAI ;
 rxt.'vtp' = wall ;
 rxt.'LAMBDA' = 15. ;
 rxt.'ROCP' = 3.9E6 ;
 rxt.'Tp0' = 40. ;
 rxt.'ECHAN' = 10. ;
* -- Conditions initiales dans l'enceinte de test
 rxt.'TF0' = 90.0 ;
 rxt.'PT0' = 1.86076e5 ;
 rxt.'Yvap0' = 0.2728 ;
* -- On positionne une brèche
* rxt.'breche' = jg ;
* rxt.'diru1' = 0 0 1 ;
* -- On definit un point interne au maillage pour imposer la valeur de
* -- la pression
 rxt.'pi' = (0.0 0.0 0.5) ;
* -- On indique que le calcul comporte de la vapeur d'eau
 rxt.'VAPEUR' = VRAI ;
* -- On active le recalcul automatique du préconditionnement
* -- toutes les 5 itérations
 rxt.'FRPREC' = 5 ;
 rxt.'DETMAT' = VRAI ;
* -- Definition du scenario thermohydraulique
* rxt.'scenario' = table ;
* -- Conditions a la breche (Obligatoire pour l'instant)
* rxt.'scenario'.'t' = prog 0.0 1000.0 ;
* rxt.'scenario'.'qeau' = prog 0.000 0.000 ;
* rxt.'scenario'.'qair' = prog 0.000 0.000 ;
* rxt.'scenario'.'tinj' = prog 90.0 90.0 ;
* -- On impose le pas de temps (s)
 rxt.'DT0' = DT0 ;
* -- On impose la viscosite turbulente (m2/s)
 rxt.'MODTURB'='NUTURB' ;
 rxt.'NUT' = 1.e-2 ;
* -- On lance le calcul sur 20 itérations d'une seconde
 rxt.'GRAPH'=GRAPH ;
 TEMPS;
 EXECRXT 2 rxt ;
 TEMPS;
 EXECRXT (nbit - 2 ) rxt ;
 TEMPS;
list rxt.TIC.'Tfm' ;
list rxt.TIC.'PT' ;
list rxt.TIC.'Qc' ;
list rxt.TIC.'LMAXU';
 'SI' (NON COMPLET) ;
ltfm=Prog
* 90.000 82.759 65.078 60.601 56.047 51.777 ;
* 90.000 82.759 68.655 63.051 58.082 53.682 ;
 90.000 82.759 68.586 62.980 57.998 53.590 ;
lPT =Prog
* 1.86076E+05 1.83833E+05 1.73114E+05 1.55674E+05 1.49937E+05 1.47211E+05 ;
* 1.86076E+05 1.83833E+05 1.74918E+05 1.61022E+05 1.54803E+05 1.51174E+05 ;
 1.86076E+05 1.83833E+05 1.74882E+05 1.60905E+05 1.54659E+05 1.51012E+05 ;
Lqc =Prog
* 0.0000 7.74979E-02 4.99805E-02 3.61752E-02 3.16373E-02 2.90635E-02 ;
* 0.0000 5.58061E-02 4.29392E-02 3.41083E-02 3.01362E-02 2.76068E-02 ;
 0.0000 5.62319E-02 4.32212E-02 3.43710E-02 3.03769E-02 2.78135E-02 ;
Lmaxu=Prog
* 0.0000 0.0000 0.30666 0.45360 0.55440 0.30930 ;
* 0.0000 0.0000 0.30666 0.45360 0.49687 0.29288 ;
 0.0000 0.0000 0.30666 0.45360 0.49797 0.29336 ;
tic=rxt.'TIC' ;
ERtf=SOMM( abs (ltfm - tic.'Tfm') )/ 80. ;
ERPT=SOMM( abs (lPT - tic.'PT' ) ) /1.e5 ;
ERQc=SOMM( abs (lqc - tic.'Qc' ) ) ;
ERum=SOMM( abs (Lmaxu - tic.'LMAXU' ) )/2. ;
Mess 'ERtf=' ERtf 'ERPT=' ERPT 'ERQc=' ERQc 'ERum=' ERum ;
ierr = 0 ;
Si (ERtf '>' 1.e-4) ; ierr = ierr + 1 ; Finsi ;
Si (ERPT '>' 1.e-4) ; ierr = ierr + 1 ; Finsi ;
Si (ERQc '>' 1.e-4) ; ierr = ierr + 1 ; Finsi ;
Si (ERum '>' 1.e-3) ; ierr = ierr + 1 ; Finsi ;
 'FINSI' ;
Si GRAPH ;
$vtf=rxt.'GEO'.'$vtf' ;
mt =doma $vtf maillage ;
Mpl1=chan 'QUAF' plan1 ;
Mpl4=chan 'QUAF' plan4 ;
ELIM (mt et Mpl1 et Mpl4) epsi ;
$mpl1= mode Mpl1 'NAVIER_STOKES' MACRO ;
$mpl4= mode Mpl4 'NAVIER_STOKES' MACRO ;
plan1= doma $mpl1 maillage ;
plan4= doma $mpl4 maillage ;
plan=plan1 et plan4 ;
paroif = rxt.'GEO'.'paroif';
rho=rxt.'TIC'.'RHO';
rvp=rxt.'TIC'.'RVP';
tf=rxt.'TIC'.'TF';
un=rxt.'TIC'.'UN' ;
un1=redu un plan ;
ung= vect un1 1. ux uy uz jaune ;
trace ung plan ;
opti isov suli ;
trace rho plan 'TITRE'' Rho' ;
trace rvp plan 'TITRE'' Rvp' ;
trace tf plan 'TITRE'' Tf ' ;
trace rho paroif 'TITRE'' Rho' ;
trace rvp paroif 'TITRE'' Rvp' ;
trace Tf paroif 'TITRE'' Tf ' ;
Fcond = tic.'Fcondw';
trace Fcond paroif 'TITRE' ' Flux de condensation Kg / m**2 ' ;
 axe = p0 d nz1 (p0 plus v1) ;
 axe = chan axe 'QUAF' ;
 elim (axe et mt) epsi ;
evr= evol 'CHPO' rho axe ;
dess evr 'TITRE' ' Rho axe ';
evt = evol 'CHPO' Tf axe ;
dess evt 'TITRE' ' Température axe ';
evvp= evol 'CHPO' rvp axe ;
dess evvp 'TITRE' ' rvp axe ';
'FINSI' ;
'SI' (IERR '>' 0) ;
  'MESS' 'Il y a des problemes !!!' ;
  'ERRE' 5 ;
'SINO';
  'MESS' 'Tout s est bien passe!' ;
'FINS' ;
 'FIN' ;
```

## test_debi [Poreux]
```
* Test tedebi.dgibi: Jeux de données
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
GRAPH = 'N' ;
SAUT PAGE;
SI (NEG GRAPH 'N') ;
  OPTI ECHO 1 ;
  OPTI TRAC PSC ;
SINO ;
  OPTI ECHO 1 ;
FINSI ;
* TEST TEDEBI
* verification du fonctionnement correct de DEBI
TITRE 'VERIFICATION DU FONCTIONNEMENT DE DEBIT';
OPTION DIME 2 ELEM QUA8 MODE PLAN DEFO ;
* ------------------ DEFINITION DE LA GEOMETRIE --------
SI (NEG GRAPH 'N');
  TRAC (L1 ET O) 'QUAL' ;
FINSI;
XL=10. ;
XD = 0.2 ;
NX = 5 ;
NY = 2;
P1 = 0. 0.;
P2 = XL 0. ;
L1 = P1 D NX P2 ;
SU = TRAN NY L1 (0. 1.) ;
* DEFINITION DU MODELE
MO1 = MODE SU POREUX ;
* ------- APPEL A DEBIT -------------
DD = DEBIT MO1 XD L1 ;
* ------- CALCUL DE LA RESULTANTE -------------
RR = RESU DD ;
GEO = EXTR RR 'MAIL';
PR = POINT GEO 1 ;
VAD= EXTR RR 'FP' PR;
VREF = XL * XD;
* --------- CODE DE BON FONCTIONNEMENT -----------------
ERR = (ABS(VREF - VAD))/VREF ;
SI (ERR < 1.E-6);
  ERRE 0;
SINON;
  ERRE 5;
FINSI;
FIN;
```

## adve_02 [Thermique Advection]
```
* Cas-test de l'operateur ADVEction dans la formulation THERMIQUE
* Ce cas-test verifie que le produit de la rigidite d'advection avec un
* champ de temperature donne : v.gradT est egal a la solution attendue.
* Attention, il s'agit du champ solution integre sur l'element fini
* et non pas la solution analytique.
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
* Commentez cette ligne pour voir les traces :
'OPTI' 'TRAC' 'PSC' ;
O1 = 0 0 ;
X1 = 1 0 ;
Y1 = 0 1 ;
S1 =(O1 'DROI' 1 X1) 'TRAN' 1 Y1 ;
L1 = S1 'COTE' 1 'COUL' 'ROUG' ;
L3 = S1 'COTE' 3 ;
L4 = S1 'COTE' 4 'COUL' 'ROUG' ;
'TITR' ' Maillage : carre de cote 1...' ;
'TRAC' 'QUAL' S1 ;
mo1 = 'MODE' S1 thermique advection ;
ma1 = 'MATE' mo1 'K' 1. 'RHO' 1.5 'C' 1. 'VITX' 0.22 'VITY' 1.0 ;
cht1 = (s1 'COOR' 1) + (S1 'COOR' 2) 'NOMC' T ;
KA1 = 'ADVE' mo1 ma1 ;
chq1 = ka1 * cht1 ;
chqref = 'MANU' 'CHPO' s1 1 'Q' 0.305 'NATURE' 'DISCRET' ;
err1 = 'MAXI' 'ABS' (chq1 - chqref / chqref) ;
'OPTI' 'ECHO' 0 ;
'MESS' ;
'MESS'
' > Ecart relatif entre champs calcule et reference =' err1 ;
'MESS' ;
'OPTI' 'ECHO' 1 ;
'SI' (err1 > 1.e-5) ;
  'ERRE' 5 ;
'SINO' ;
  'OPTI' 'ECHO' 0 ;
  'MESS' ;
  'MESS' ' > Test reussi ! ' ;
  'MESS' ;
'OPTI' 'ECHO' 1 ;
'FINS' ;
'FIN' ;
```

## tran15 [Thermique Conduction]
```
* Calcul avec des elements 'JOI1' (support 'SEG2') et 'POI1'
* Test tran15.dgibi: jeux de données
* THERMIQUE TRANSITOIRE LINEAIRE EN 2D
* CONDUCTION
* CONVECTION
* - Verification de CAPA, COND et CONV
* Pour les elements JOI1 et POI1 en
* formulation THERMIQUE
* Description
* Les noeuds de la surface S1 echangent
* avec le point POI2 par le bias de JOI1.
* Coefficient de CONDUCTION 'KT' sur les
* elements 'JOI1'
* Coefficient de CONVECTION 'H' sur le
* point POI2 avec une temperature
* exterieure 'TC'
* Température initiale T_ini
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
'OPTI' 'TRAC' 'PSC' ;
* Parametrage du jeu de donnees
 Dt = 100. ;
 Duree = 30000. ;
 Val_KT = 5. ;
 Val_Mass = 4. ;
 Val_Cp = 4200. ;
 Val_H = 10. ;
 Temp_EXT = 15. ;
* MAILLAGE
 P1 = 0. 0. ;
 P2 = 1. 0. ;
 L1 ='DROI' 1 P1 P2 ;
 L2 = L1 'PLUS' (0. 0.2) ;
 S1 ='REGL' 1 L1 L2 ;
 POI1 ='CHAN' 'POI1' S1 ;
 POI2 = 2. 2. ;
* Creation du MAILLAGE de SEG2 reliant les noeuds de S1 aux noeuds de POI1
 NBPOI ='NBEL' POI1;
 MAILJOI1='VIDE' 'MAILLAGE';
'REPE' SURPOI1 NBPOI;
   MAILJOI1 = MAILJOI1 'ET' ('DROI' 1 ('POIN' POI1 &SURPOI1) POI2) ;
'FIN' SURPOI1 ;
 MAILJOI1 = MAILJOI1 'COUL' 'BLEU' ;
* MODELE & CARACTERISTIQUES
 MOD1 ='MODE' MAILJOI1 'THERMIQUE' 'CONDUCTION' 'JOI1' ;
 MOD2 ='MODE' POI1 'THERMIQUE' 'CONVECTION' ;
 MODTOT= MOD1 'ET' MOD2 ;
 MAT1 ='MATE' MOD1 'M' Val_Mass 'C' Val_Cp 'KT' Val_KT ;
 MAT2 ='MATE' MOD2 'H' Val_H 'TC' Temp_EXT ;
 MATTOT= MAT1 'ET' MAT2 ;
* CONDITIONS INITIALES
 T_ini ='MANU' 'CHPO' MAILJOI1 'T' 1.5 ;
* RESOLUTION AVEC PASAPAS
 LISTPS ='PROG' 0. 'PAS' Dt Duree ;
 TAB1 ='TABL' 'PASAPAS';
 TAB1.'MODELE' = MODTOT ;
 TAB1.'CARACTERISTIQUES'= MATTOT ;
 TAB1.'TEMPS_CALCULES' = LISTPS ;
 TAB1.'TEMPERATURES' ='TABL' ;
 TAB1.'TEMPERATURES' . 0= T_ini ;
 PASAPAS TAB1 ;
* POST TRAITEMENT
 EVO1 ='EVOL' 'TEMP' TAB1 TEMPERATURES 'T' (POI2 'ET' (POIN 1 POI1));
'DESS' EVO1 ;
'FIN';
```

## ther-perm [Thermique Convection]
```
* Test Ther-perm.dgibi: Jeux de données
* Calcul d'une plaque infinie (de largeur 2L) avec
* une source volumique et température imposéé sur
* les bords. Conductivité dépend linéairement de la
* température.
* Modélisation plane.
* Auteur : Michel Bulik
* Date : Décembre 1996
* Références :
* [1] Klaus-Jürgen Bathe & Mohammad R. Khoshgoftaar,
* Finite element formulation and solution of
* non-linear heat transfer, Nuclear Engineering
* and Design, v. 51 (1979), pp. 389-401
* [2] J. Joly, Cas tests non linéaires de validation
* pour DELFINE, Note technique EMT.SMTS.TTMF
* 84/29
* [3] V. Arpaci, Conduction Heat Transfer, Adison-
* Wesley, 1966, pp. 130-132
* Les résultats du calcul sont comparés avec la
* solution analytique (voir [3]).
* Options ...
    opti dime 2 elem seg2 echo 1 ;
* Paramètres ...
    L = 5.e-3 ;
    ep = L / 10 ;
    K0 = 2. ;
    beta = 0.025 ;
    T0 = 100. ;
    q = 10000000. ;
    graph = faux ;
* Points ...
    dens ep ;
    p1 = 0 0 ;
    p2 = 0 ep ;
    vechoriz = L 0 ;
* Lignes ...
    li1 = p1 d 1 p2 ;
* Surface ...
    opti elem qua4 ;
    su1 = li1 tran vechoriz dini (L/100.) dfin (L/10.);
    li2 = cote 3 su1 ;
    li3 = cote 2 su1 ;
    si(graph) ;
       titr 'Le maillage de la plaque' ;
       trac su1 ;
    finsi ;
* Modèles ...
    mocnd = mode su1 thermique ;
    dt1 = -100. ;
    T1 = T0 + dt1 ;
    K1 = K0 * (beta*dt1 + 1) ;
    dt2 = 1000. ;
    T2 = T0 + dt2 ;
    K2 = K0 * (beta*dt2 + 1) ;
    titr 'K(T)' ;
    evk = evol manu 'T' (prog T1 T2) 'K' (prog K1 K2) ;
    si(graph) ;
       dess evk ;
    finsi ;
    macnd = mate mocnd 'K' evk ;
* Température imposée ...
    blt = bloq T li2 ;
    ti1 = depi blt T0 ;
* Source volumique ...
    fl1 = sour mocnd su1 q ;
* Préparation de table pour THERMIC ...
    tabth = table THERMIQUE ;
    tabth . 'BLOCAGE' = blt ;
    tabth . 'IMPOSE' = ti1 ;
    tabth . 'FLUX' = fl1 ;
    tabth . 'INSTANT(0)' = manu chpo su1 1 T T0
                           nature diffus ;
    tabth . 'TABCOND' = table ;
    tabth . 'TABCOND' . mocnd = evk ;
    tabth . 'NIVEAU' = 1 ;
* Lancement du calcul ...
    thermic tabth NONLINEAIRE ;
* Post-traitement ...
    tresu = tabth . TEMPERATURE ;
    titr 'Profil de temperature absolue' ;
    evt = evol chpo tresu T li3 ;
    si(graph) ;
       dess evt ;
    finsi ;
    titr
'Profil de temperature relative (solution analytique)';
    chx = coor 1 li3 ;
    evx = evol chpo chx SCAL li3 ;
    lrx = extr evx ABSC ;
    lr1 = prog (dime lrx) * 1. ;
    ev1 = evol manu lrx lr1 ;
* toto1 = ev1 - ((evx / L)*(evx / L)) ;
* toto1 = ev1 - (extr ((evx / L)*(evx / L)) cour 1) ;
    ev1x = extr (evx / L) cour 1;
    toto1 = ev1 - (ev1x * ev1x) ;
    toto2 = (toto1 * (L*L*q*beta/K0)) + ev1 ;
    kkabsc = extr toto2 ABSC ;
    kkordo = extr toto2 ORDO ;
    toto3 = evol manu kkabsc (kkordo ** 0.5) ;
    toto4 = toto3 - ev1 ;
    toto5 = (toto4 * (2*K0/(beta*q*L*L))) coul VERT ;
    si(graph) ;
       dess toto5 ;
    finsi ;
    titr
'Profil de temperature relative (solution EF)' ;
    evtrel = ((evt - (T0 * ev1)) * (2*K0/(q*L*L)))
             coul ROUG ;
    si(graph) ;
       dess (evtrel et toto5) ;
    finsi ;
* Test ...
    ladiff = abs (extr (evtrel - toto5) ORDO) ;
    valtst = maxi ladiff ;
    si(valtst > 1.e-5) ;
       erre 5 ;
    finsi ;
* Bye ...
    fin ;
```

## ther1bis [Thermique Convection]
```
* Test ther1bis.dgibi: jeux de données
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
GRAPH = 'N' ;
SAUT PAGE;
SI (NEG GRAPH 'N') ;
  OPTI ECHO 1 ;
  OPTI TRAC PSC ;
SINO ;
  OPTI ECHO 0 ;
FINSI ;
SAUT PAGE;
* THER1BIS
* TEST D'UN PROBLEME DE DIFFUSION
* AVEC UNE TEMPERATURE IMPOSEE
* ET UNE SOURCE REPARTIE
* TEMPERATURE IMPOSEE + SOURCE
* Ce test permet de vérifier le bon
* fonctionnement des divers
* opérateurs thermiques de CAST3M
* Une plaque rectangulaire constituée
* d'éléments QUA4 est soumise à
* une température imposée à une de ses
* extrémités et une condition de source
* volumique imposée sur une partie
* Les résultats sont comparés à la
* solution analytique du problème
* ----- OPTIONS GENERALES DE CALCUL -------
OPTI DIME 2 ELEM QUA4 ;
TEMPS ;
* - CREATION DE LA GEOMETRIE:
* POINTS SUPPORTS DES ELEMENTS -
A1 = 0. 0. ;A2 = 3. 0. ;
B1 = 0. 4. ;B2 = 3. 4. ;
C1 = 0. 6. ;C2 = 3. 6. ;
* - CREATION DES LIGNES -
L1 = D 50 A1 A2;
L2 = D 50 B1 B2;
L3 = D 50 C1 C2;
* - CREATION DES SURFACES -
S1 = (REGL 100 L1 L2) COUL BLEU;
S2 = (REGL 50 L2 L3) COUL ROUG;
STOT = S1 ET S2;
SI(NEG GRAPH 'N');
    TRACE 'QUAL' STOT ;
FINSI;
* --- DONNEES DU PROBLEME DE THERMIQUE ----
* -------------- MODELISATION ------------
MOD1 = MODE STOT THERMIQUE ISOTROPE ;
* DONNEES DES CARACTERISTIQUES DU MATERIAU
KCOND = 100. ;
MAT1 = MATE MOD1 'K' KCOND ;
* - CREATION DES MATRICES DE CONDUCTIVITE -
CND1 = CONDUCTIVITE MOD1 MAT1 ;
* - TEMPERATURES IMPOSEES: BLOQUE + DEPI --
BB1 = BLOQUE L1 'T' ;
T0 = 10. ;
EE1 = DEPI BB1 T0. ;
* ----------- SOURCE DE CHALEUR -----------
VALQ = 1000. ;
S1 = SOURCE MOD1 VALQ S2 ;
* - ASSEMBLAGE DES TERMES DE CONDUCTIVITE -
CCC = CND1 ET BB1 ;
* -ASSEMBLAGE DES TERMES DE FLUX EQUIVALENTS
FFF = EE1 ET S1 ;
* ------------- RESOLUTION ----------------
CHTER = RESO CCC FFF ;
* --- POST-TRAITEMENT: TRACE DES CHAMPS ---
* RESULTATS
* - ET CALCUL DES VALEURS CARACTERISTIQUES
TITR 'TEMPERATURE' ;
SI(NEG GRAPH 'N');
     TRACER STOT CHTER ;
FINSI;
T = EXTR CHTER T C2 ;
TEMPS ;
* CODE DE FONCTIONNEMENT
* Calcul de la température en C2
TREF = T0 - ( (VALQ / (2. * KCOND)) *
              (
               ((COOR 2 C2)**2) -
               (2*(COOR 2 C2)*(COOR 2 C2))+
               ((COOR 2 B2)**2)
              )
             );
RESI1=100. * (ABS((T-TREF)/TREF));
* TEST SOURCE
MESS 'Temperature theorique :' TREF '°C';
MESS 'Temperature calculee  :' T '°C';
MESS '    Soit un ecart de : ' RESI1 '%';
SAUTER 1 LIGNES ;
RESITOT = PROG RESI1 ;
SI((MAXI RESITOT) <EG 1.);
  ERRE 0;
SINO;
  ERRE 5;
FINSI;
FIN;
```

## lapnvf [Thermique Diffusion]
```
* cas test lapnvf.dgibi
* Cas Test pour l'operateur LAPN version VF
* On cherche la solution stationnaire d'un problème de diffusion
* thermique sur un disque où on impose une température T1 sur le
* disque de rayon r1 et T2 à l'exterieur du disque de rayon r2.
* La solution analytique ne dépend que du rayon r, soit :
* T2 log (r/r1) - T1 log (r/r2)
* T(r) = -----------------------------
* log r2 - log r1
* On effectue quand meme un calcul 2D sur un maillage constitué de
* quadrangles et de triangles.
* Auteurs : J.CREUZIL et F.DABBENE (TTMF) 12/97
* - Options
'OPTI' 'DIME' 2 'ELEM' 'TRI3' ;
'OPTI' 'ECHO' 0 ;
 'OPTI' 'TRAC' 'PS' ;
 GRAPH = 'N' ;
* - Données du problème
R1 = 3.0 ; R2 = 9.0 ;
T1 = 200.0 ; T2 = 100.0 ;
* - Maillage
R0 = R1 - 0.5 ;
R3 = R2 + 0.5 ;
MR0 = -1.D0 * R0 ;
MR1 = -1.D0 * R1 ;
MR2 = -1.D0 * R2 ;
MR3 = -1.D0 * R3 ;
PC = 0.0 0.0 ;
P0 = R0 0.0 ;
P1 = R1 0.0 ;
P2 = R2 0.0 ;
P3 = R3 0.0 ;
P4 = 0.0 R0 ;
P5 = 0.0 R1 ;
P6 = 0.0 R2 ;
P7 = 0.0 R3 ;
P8 = MR0 0.0 ;
P9 = MR1 0.0 ;
P10 = MR2 0.0 ;
P11 = MR3 0.0 ;
N = 12 ;
N1 = 10 ;
P0P1 = P0 'DROI' 2 P1 ;
P1P2 = P1 'DROI' N P2 ;
P2P3 = P2 'DROI' 2 P3 ;
P4P5 = P4 'DROI' 2 P5 ;
P5P6 = P5 'DROI' N P6 ;
P6P7 = P6 'DROI' 2 P7 ;
P9P8 = P9 'DROI' 2 P8 ;
P10P9 = P10 'DROI' N P9 ;
P11P10 = P11 'DROI' 2 P10;
P5P4 = 'INVE' P4P5 ;
P6P5 = 'INVE' P5P6 ;
P7P6 = 'INVE' P6P7 ;
P4P0 = 'CERC' N1 P4 PC P0 ;
P5P1 = 'CERC' N1 P5 PC P1 ;
P1P5 = 'INVE' P5P1 ;
P2P6 = 'CERC' N1 P2 PC P6 ;
P6P2 = 'INVE' P2P6 ;
P3P7 = 'CERC' N1 P3 PC P7 ;
P8P4 = 'CERC' N1 P8 PC P4 ;
P5P9 = 'CERC' N1 P5 PC P9 ;
P9P5 = 'INVE' P5P9 ;
P6P10 = 'CERC' N1 P6 PC P10;
P10P6 = 'INVE' P6P10 ;
P7P11 = 'CERC' N1 P7 PC P11;
P4P7 = P4P5 'ET' P5P6 'ET' P6P7 ;
M00 = 'DALL' P0P1 P1P5 P5P4 P4P0 ;
M10 = 'DALL' P1P2 P2P6 P6P5 P5P1 ;
M20 = 'DALL' P2P3 P3P7 P7P6 P6P2 ;
'OPTI' 'ELEM' 'QUA4' ;
M30 = 'DALL' P9P8 P8P4 P4P5 P5P9 ;
M40 = 'DALL' P10P9 P9P5 P5P6 P6P10 ;
M50 = 'DALL' P11P10 P10P6 P6P7 P7P11 ;
M = M00 'ET' M10 'ET' M20 'ET' M30 'ET' M40 'ET' M50 ;
M1 = M00 'ET' M30 ;
M3 = M20 'ET' M50 ;
M2 = M10 'ET' M40 ;
COT1 = 'CONT' M ;
* - Tables domaines
$M = 'DOMA' M ;
$M1 = 'DOMA' M1 'INCL' $M;
$M2 = 'DOMA' M2 'INCL' $M;
$M3 = 'DOMA' M3 'INCL' $M;
$D1 = 'DOMA' P4P7 'INCL' $M;
* - Resolution du probleme
CHP1 = 'MANU' 'CHPO' $M1.'CENTRE' 1 'SCAL' T1 ;
CHP2 = 'MANU' 'CHPO' $M3.'CENTRE' 1 'SCAL' T2 ;
CHP3 = 'KCHT' $M 'SCAL' 'CENTRE' 0. CHP1 CHP2 ;
CHP4 = 'MANU' 'CHPO' $M2.'CENTRE' 1 'SCAL' 0. ;
RV = EQEX $M 'ITMA' 10
     'OPTI' 'VF' 'IMPL' 'CENTREE'
     'ZONE' $M 'OPER' 'DFDT' 1.D0 'CNM' 'DT' 'INCO' 'CN'
     'ZONE' $M 'OPER' 'LAPN' 'DIFF' 'INCO' 'CN'
     'CLIM' 'CN' 'TIMP' $M1.'CENTRE' T1
     'CLIM' 'CN' 'TIMP' $M3.'CENTRE' T2
;
RV . 'INCO' = TABLE 'INCO' ;
RV . 'INCO' . 'CN' = 'KCHT' $M 'SCAL' 'CENTRE' 0. ;
RV . 'INCO' . 'CNM' = 'KCHT' $M 'SCAL' 'CENTRE' 0. ;
RV . 'INCO' . 'DIFF' = 'KCHT' $M 'SCAL' 'CENTRE' 2. ;
RV . 'INCO' . 'DT' = 20. ;
EXEC RV ;
* - Solution analytique
XC YC = 'COOR' $M.'CENTRE' ;
SOL0 = 'LOG' ( R1 / R2 ) ;
SOL1 = 'LOG' ( R1 ** T2 / (R2 ** T1)) ;
RC = XC*XC + (YC*YC) ** 0.5 ;
SS1 = 'MANU' 'CHPO' $M.'CENTRE' 1 'SCAL' (SOL1 / SOL0) ;
SS2 = (T1 - T2) / SOL0 * (LOG RC) ;
SS4 = 'MANU' 'CHPO' $M1.'CENTRE' 1 'SCAL' T1 ;
SS5 = 'MANU' 'CHPO' $M3.'CENTRE' 1 'SCAL' T2 ;
SS3 = 'KCHT' $M 'SCAL' 'CENTRE' (SS2 + SS1) SS4 SS5 ;
* - Tracé des résultats
ERR1 = 'ABS' ((RV.INCO.'CN') - SS3) ;
'SI' ('NEG' GRAPH 'N') ;
     SSS3 = 'ELNO' $M SS3 ;
     'TITR' 'Solution (coupe)' ;
     EV1 = 'EVOL' 'CHPO' SSS3 P4P7 ;
     'DESS' EV1 ;
     MOD1 = 'MODE' M 'THERMIQUE' ;
     CHAM1 = 'KCHA' $M 'CHAM' (RV.INCO.'CN') ;
     'TRAC' MOD1 CHAM1 'TITR' 'Solution' ;
     MERR1 = ( 'KCHA' $M 'CHAM' ERR1) ;
     'TRAC' MOD1 MERR1 'TITR' 'Erreur relative' ;
'FINSI' ;
* - Gestion des erreurs
MAXE1 = 'MAXI' ERR1 ;
'MESS' 'Erreur Absolue : ' MAXE1 ;
'SI' (MAXE1 '>' 6.) ;
     'ERRE' 5 ;
'SINO' ;
     'ERRE' 0 ;
'FINS' ;
FIN;
```

## rayo_abs-axi-1 [Thermique Diffusion]
```
* Rayonnement thermique en milieu absorbant dans une cavité sphérique
* (pas de couplage avec d'autres modes de transfet d'énergie)
* Comparaison à un calcul analytique
* Ref: Siegel&Howell Ed.3 p609-615
* On evalue la puissance perdue par un gaz absorbant de température
* uniforme 2273K et de coefficient d'absorption 100./m contenu dans
* cavité de rayon 0.01m à la température uniforme de 1273K.
* Calcul 2D axisymétrique
* Remarque: le calcul des facteurs de forme n'utilise pas l'option
* convexe 'CONV'
 option echo 1 dime 2 elem qua4 mode axis ;
 graph = faux ;
* Maillage
R1 = 1.E-2 ;
O = 0. 0. ;
p1 = 0. ( -1. * R1 ) ;
p2 = R1 0. ;
p3 = 0. R1 ;
d = 1.E-3 ;
p1p2 = cerc p1 O p2 DINI d DFIN d;
p2p3 = cerc p2 O p3 DINI d DFIN d;
sphe_ext = p1p2 et p2p3 ;
si graph ;
trac sphe_ext ;
finsi ;
cavite = sphe_ext ;
tout = cavite;
* Propriétés physiques
e_wall = 0.5 ;
abso0 = -100. ;
T_wall = 1273. ;
T_gas = 2273. ;
* Modèle de rayonnement
mrt = mode sphe_ext thermique rayonnement 'CAVITE' ;
e = mate mrt 'EMIS' e_wall 'CABS' abso0 'TABS' T_gas;
* opti 'IMPI' 1 ;
* Facteurs de forme et matrice de rayonnement
 fft = ffor mrt e;
 chamr = raye mrt fft e ;
* gaz absorbant : calcul du terme R*Tg4
tg = manu chpo tout 1 'T' T_gas natu 'DIFFUS';
tg_cavi = redu tg cavite ;
tge_cavi = chan 'CHAM' tg_cavi mrt 'GRAVITE' ;
crg= rayn mrt chamr tge_cavi ;
fg = crg*tg_cavi ;
* paroi : calcul du terme R*Tw4
tp = manu chpo tout 1 'T' T_wall natu 'DIFFUS';
t_cavi = redu tp cavite ;
te_cavi = chan 'CHAM' t_cavi mrt 'GRAVITE' ;
cr = rayn mrt chamr te_cavi ;
fw = cr *t_cavi ;
* puissance perdue par les frontieres:
puis_n = fw - fg ;
t1 = manu chpo tout 1 'T' 1.0 natu 'DIFFUS' ;
lm1 = MOTS 'Q' ;
lm2 = MOTS 'T' ;
puis_t = xty puis_n t1 lm1 lm2 ;
* puissance théorique perdue par les frontieres:
abso0 = -1 * abso0 ;
b0 = 5.670E-8 ;
EMG1 = b0 * ( T_gas ** 4. ) ;
EMS1 = b0 * ( T_wall ** 4. ) ;
AIRE1 = 4. * 3.1416 * R1 * R1 ;
tau1 = 2. / ( ( 2. * abso0 * R1 ) ** 2. ) ;
tau0 = ( 2. * abso0 * R1 ) + 1. ;
tau0 = tau0 * ( 'EXP' ( -2. * abso0 * R1 ) ) ;
tau1 = ( 1. - tau0 ) * tau1 ;
abso1 = 1. - tau1 ;
denom0 = ( 1. / e_wall ) + ( 1. / abso1 ) - 1. ;
res0 = -1. * AIRE1 * ( EMG1 - EMS1 ) / denom0 ;
* Erreur methode 1
si ( ( 'ABS' res0 ) '>' 1.E-5 ) ;
  err1 = ( 'ABS' ( res0 - puis_t ) ) / ( 'ABS' res0 ) ;
  err1 = err1 * 100. ;
sinon ;
  err1 = 0. ;
finsi ;
'MESS' ' Puissance absorbée calculée methode 1  = ' puis_t ;
'MESS' ' Puissance absorbee théorique = ' res0 ;
'MESS' ' Erreur methode 1 en pourcentage = ' err1 ' % ' ;
* calcul du flux rayonné au moyen de l'évaluation de la
* température de rayonnement (option 2 de RAYE)
       trad = raye mrt fft e te_cavi 1e-7 ;
* mess 'trad ' (mini trad) (maxi trad);
* calcul du coefficient d'echange
       hrad = HRCAV mrt e te_cavi trad ;
* mess 'hrad ' (mini hrad) (maxi hrad);
       trad_n1= chan 'CHPO' mrt trad ;
       trad_n = nomc trad_n1 'T' 'NATU' 'DIFFUS';
* pour la condition de convection
       cr = cond mrt hrad;
       f = conv mrt hrad trad_n;
* flux rayonne
       fray = (cr * tp)- f;
       fray_tot = maxi (resu fray);
       mess ' flux par methode 2 ' fray_tot ;
* Erreur methode 2
si ( ( 'ABS' res0 ) '>' 1.E-5 ) ;
  err2 = ( 'ABS' ( res0 - fray_tot) ) / ( 'ABS' res0 ) ;
  err2 = err2 * 100. ;
sinon ;
  err2 = 0. ;
finsi ;
'MESS' ' Puissance absorbée calculée methode 2  = ' fray_tot ;
'MESS' ' Puissance absorbee théorique = ' res0 ;
'MESS' ' Erreur methode 2 en pourcentage = ' err2 ' % ' ;
si (( err1 '<' .2 ) et ( err2 '<' .2 ));
 'ERRE' 0 ;
sinon ;
 'ERRE' 5 ;
finsi ;
fin ;
```

## nlin_int_surface [Thermique Hydraulique]
```
'OPTION' echo 0 ;
'DEBPROC' CAS ;
'ARGUMENT' icas*'ENTIER' ;
'SI' ('EGA' icas 1) ;
   'OPTION' 'DIME' 2 ;
   p1 = 0. 0. ; p2 = 1. 0. ; p3 = 0. 1. ;
   tit = 'CHAINE' 'Triangle' ;
   mt = 'MANUEL' 'TRI3' p1 p2 p3 ;
   disc = 'QUAI' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'CONTOUR' _mt ;
'FINSI' ;
'SI' ('EGA' icas 2) ;
   'OPTION' 'DIME' 2 ;
   p1 = 0. 0. ; p2 = 1.5 0. ; p3 = 3. 3. ; p4 = 0. 2. ;
   tit = 'CHAINE' 'Carre deforme' ;
   mt = 'MANUEL' 'QUA4' p1 p2 p3 p4 ;
   disc = 'LINE' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'CONTOUR' _mt ;
'FINSI' ;
'SI' ('EGA' icas 3) ;
   'OPTION' 'DIME' 3 ;
   p1 = 0. 0. 0. ; p2 = 1. 0. 0. ; p3 = 0. 1. 0. ;
   p4 = 0.5 0.5 0.5 ;
   tit = 'CHAINE' 'Tétra' ;
   mt = 'MANUEL' 'TET4' p1 p2 p3 p4 ;
   disc = 'QUAF' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
'FINSI' ;
'SI' ('EGA' icas 4) ;
   'OPTION' 'DIME' 3 ;
   p1 = 0. 0. 0. ; p2 = 1.5 0. 0. ; p3 = 3. 3. 0.; p4 = 0. 2. 0. ;
   p5 = 0.5 0.5 0.5 ;
   tit = 'CHAINE' 'Pyramide deforme' ;
   mt = 'MANUEL' 'PYR5' p1 p2 p3 p4 p5 ;
   disc = 'QUAI' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   cmt = ('MANUEL' 'QUA4' p1 p2 p3 p4) 'ET'
         ('MANUEL' 'TRI3' p1 p2 p5) 'ET'
         ('MANUEL' 'TRI3' p2 p3 p5) 'ET'
         ('MANUEL' 'TRI3' p3 p4 p5) 'ET'
         ('MANUEL' 'TRI3' p4 p1 p5) ;
   _cmt = 'CHANGER' cmt 'QUAF' ;
   'ELIMINATION' (_mt 'ET' _cmt) 1.D-6 ;
* _cmt = 'CONTOUR' _mt ;
* _mt = 'CHANGER' mt 'QUAF' ;
* _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
'FINSI' ;
'SI' ('EGA' icas 5) ;
   'OPTION' 'DIME' 3 'ELEM' 'PRI6' ;
   p1 = 0. 0. 0. ; p2 = 1. 0. 0. ; p3 = 0. 1. 0. ;
   fac = 'MANUEL' 'TRI3' p1 p2 p3 ;
   p5 = 0.5 0.5 0.5 ;
   tit = 'CHAINE' 'Prisme deforme' ;
   mt = 'VOLUME' fac 1 'TRAN' p5 ;
   disc = 'QUAI' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
'FINSI' ;
'SI' ('EGA' icas 6) ;
   'OPTION' 'DIME' 3 'ELEM' 'CUB8' ;
   p1 = 0. 0. 0. ; p2 = 1.5 0. 0. ; p3 = 3. 3. 0.; p4 = 0. 2. 0. ;
   fac = 'MANUEL' 'QUA4' p1 p2 p3 p4 ;
   p5 = 0.5 0.5 0.5 ;
   tit = 'CHAINE' 'Cube deforme' ;
   mt = 'VOLUME' fac 1 'TRAN' p5 ;
   disc = 'LINE' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
'FINSI' ;
'SI' ('EGA' icas 7) ;
   'OPTION' 'DIME' 3 'ELEM' 'CUB8' ;
   p1 = 0. 0. 0. ; p2 = 1. 0. 0. ; p3 = 1. 1. 0.; p4 = 0. 1. 0. ;
   fac = 'MANUEL' 'QUA4' p1 p2 p3 p4 ;
   p5 = 0. 0. 1. ;
   tit = 'CHAINE' 'Cube regulier' ;
   mt = 'VOLUME' fac 1 'TRAN' p5 ;
   cmt = fac ;
   disc = 'LINE' ;
   tolerr = 1.D-12 ;
   _mt = 'CHANGER' mt 'QUAF' ;
   _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
* _cmt = _cmt 'ELEM' ('LECT' 4) ;
* _cmt = 'CHANGER' cmt 'QUAF' ;
* 'ELIMINATION' (_mt 'ET' _cmt) 1.D-6 ;
'FINSI' ;
'RESPRO' tit _mt _cmt disc tolerr ;
'FINPROC' ;
* NOM : NLIN_INT_SURFACE
* DESCRIPTION : Teste les intégrales de surface sur différents types
* d'éléments. Ici, on vérifie qu'on obtient les mêmes
* valeurs de surface avec :
* NLIN où on donne uniquement la surface et deux champs
* valant 1.
* NLIN où on donne le volume et la surface et deux champs
* valant 1.
* NLIN où on donne le volume et la surface et deux champs
* dont la divergence vaut 1.
* A faire : dimension 1 ? Ca serait rigolo.
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 26/07/2006, version initiale
* HISTORIQUE : v1, 26/07/2006, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
interact= FAUX ;
graph = FAUX ;
verbose = VRAI ;
'SI' ('NON' interact) ;
  'OPTION' 'TRAC' 'PS' ;
'SINON' ;
* 'OPTION' 'TRAC' 'X' ;
  'OPTION' 'TRAC' 'OPEN' ;
'FINSI' ;
moscal1 = mots 'SCAL';
tres = 'TABLE' ;
ncas = 7 ;
mgau = 'GAM2' ;
ok = VRAI ;
'REPETER' iicas ncas ;
icas = &iicas ;
* icas = 6 ;
tit _mt _cmt disc tolerr = CAS icas ;
'SI' graph ;
   'TRACER' mt ;
'FINSI' ;
idim = 'VALEUR' 'DIME' ;
* _mt = 'CHANGER' mt 'QUAF' ;
* 'SI' ('EGA' idim 2) ;
* _cmt = 'CONTOUR' _mt ;
* 'FINSI' ;
* 'SI' ('EGA' idim 3) ;
* _cmt = 'ENVELOPPE' _mt ;
* _cmt = 'DOMA' ('MODELISER' _mt 'NAVIER_STOKES' 'LINE') 'ENVELOPPE' ;
* 'FINSI' ;
ch1 = 'MANUEL' 'CHPO' _mt 1 'SCAL' 1.D0 ;
'SI' ('EGA' idim 2) ;
   xmt ymt = 'COORDONNEE' _mt ;
   cx = 0.1 ; cy = PI ;
   sc = '+' cx cy ;
   chdiv1 = '/' (coli xmt cx ymt cy) sc ;
   chrigo = '*' xmt ymt ;
'FINSI' ;
'SI' ('EGA' idim 3) ;
   xmt ymt zmt = 'COORDONNEE' _mt ;
   cx = 0.1 ; cy = PI ; cz = '**' 2. 0.5 ;
   sc = cx '+' cy '+' cz ;
   chdiv1 = '/' (coli xmt cx ymt cy zmt cz) sc ;
   chrigo = xmt '*' ymt '*' zmt ;
'FINSI' ;
* 'TRACER' chrigo _mt ;
* Méthode 1
numop = 1 ; numvar = 1 ; numdat = 0 ; numcof = 0 ;
numder = ('VALEUR' 'DIME') ;
A = ININLIN numop numvar numdat numcof numder ;
A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'SCAL' ;
A . 'VAR' . 1 . 'DISC' = disc ;
A . 1 . 1 . 0 = 'LECT' ;
matm1 = 'NLIN' disc _cmt A A mgau ;
* v1 = xtmx ch1 matm1 ;
v1 = xty ch1 (matm1*ch1) moscal1 moscal1;
* Méthode 2
numop = 1 ; numvar = 1 ; numdat = 0 ; numcof = 0 ;
numder = ('VALEUR' 'DIME') ;
A = ININLIN numop numvar numdat numcof numder ;
A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'SCAL' ;
A . 'VAR' . 1 . 'DISC' = disc ;
A . 1 . 1 . 0 = 'LECT' ;
matm2 = 'NLIN' disc _mt _cmt A A mgau ;
* v2 = xtmx ch1 matm2 ;
v2 = xty ch1 (matm2*ch1) moscal1 moscal1;
* Méthode 3
numop = 1 ; numvar = 1 ; numdat = 0 ; numcof = 0 ;
numder = ('VALEUR' 'DIME') ;
A = ININLIN numop numvar numdat numcof numder ;
A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'SCAL' ;
A . 'VAR' . 1 . 'DISC' = disc ;
'REPETER' ndim idim ;
   A . 1 . 1 . &ndim = 'LECT' ;
'FIN' ndim ;
matm3 = 'NLIN' disc _mt _cmt A A mgau ;
* v3 = xtmx chdiv1 matm3 ;
v3 = xty chdiv1 (matm3*chdiv1) moscal1 moscal1;
* v3 = 0.D0 ;
t1 = '<' ('ABS' ('-' v2 v1)) tolerr ;
t2 = '<' ('ABS' ('-' v3 v1)) tolerr ;
tes = 'ET' t1 t2 ;
ok = ok 'ET' tes ;
'SI' ('OU' verbose ('NON' tes)) ;
   'MESSAGE' ('CHAINE' tit ' ' disc ' tolerr=' tolerr) ;
   'MESSAGE' ('CHAINE' 'v1 = ' v1 '  v2 - v1 = ' ('-' v2 v1)
                      '  v3 - v1 = ' ('-' v3 v1) ) ;
   'SI' tes ; 'MESSAGE' ('CHAINE' 'tes = ok') ;
   'SINON' ; 'MESSAGE' ('CHAINE' 'tes = KO') ; 'FINSI' ;
'FINSI' ;
'FIN' iicas ;
'SI' ok ;
   'MESSAGE' ('CHAINE' 'Tout sest bien passe') ;
'SINON' ;
   'MESSAGE' ('CHAINE' 'Il y a eu des erreurs') ;
'FINSI' ;
* 'LISTE' matm1 ; 'LISTE' matm2 ;
'SI' interact ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
'SI' ('NON' ok) ;
   'ERREUR' 5 ;
'FINSI' ;
* End of dgibi file NLIN_INT_SURFACE
'FIN' ;
```

## dilthe [Thermique Mecanique]
```
* fichier dilthe.dgibi
'OPTION' 'ECHO' 0 ;
* NOM : DILTHE
* DESCRIPTION : Dilatation thermique d'un cube encastre sur deux faces
* opposees
* Ce cas-test sortait en erreur de non-convergence dans
* les iterations internes au refroidissement pour cause
* de critere de convergence trop serre dans ccoin0.eso
* (< precision machine).
* Correction faite en fiche anomalie 9553
* LANGAGE : GIBIANE-CAST3M
* AUTEURS : Harry POMMIER (CEA/DEN/DM2S/SEMT/LTA)
* + modifs Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
* mél : stephane.gounand@cea.fr
* VERSION : v1, 20/09/2017, version initiale
* HISTORIQUE : v1, 20/09/2017, création
* HISTORIQUE :
* HISTORIQUE :
interact = faux ;
graph = faux ;
* Dilatation thermique d'un cube encastre sur deux faces opposees
'OPTI' 'DIME' 3 ;
'OPTI' 'ELEM' 'CUB8' ;
* MAILLAGE
ne = 2 ;
P1 = 0. 0. 0. ;
P2 = 0. 0.01 0. ;
P3 = 0. 0.01 0.01 ;
P4 = 0. 0. 0.01 ;
L12 = 'DROI' ne P1 P2 ;
L23 = 'DROI' ne P2 P3 ;
L34 = 'DROI' ne P3 P4 ;
L41 = 'DROI' ne P4 P1 ;
S1 = 'DALL' L12 L23 L34 L41 ;
MAILT = 'VOLU' 'TRAN' ne S1 (0.01 0. 0.) ;
* TRAC MAILT ;
* MODELES
MODTHER = 'MODE' MAILT 'THERMIQUE' 'CONDUCTION' ;
MODMECA = 'MODE' MAILT 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE'
                       'PLASTIQUE' 'CHABOCHE1' ;
* MATERIAUX
* THER
LTK = 'PROG' 20. 100. 200. 300. 400. 500. 600. 700.
   800. 900. 1000. 1200. 1400. 10000. ;
LK = 'PROG' 14.7 15.8 17.2 18.6 20. 21.1 22.2 23.2
   24.1 24.8 25.5 26.9 28.3 28.3 ;
LTRHO = 'PROG' 20. 200. 400. 600. 800.
   1000. 1200. 1400. 1500. 10000. ;
LRHO = 'PROG' 8000. 7930. 7840. 7750. 7650.
   7550. 7450. 7350. 7300. 7300. ;
LTCP = 'PROG' 20. 100. 200. 300. 400. 600. 800.
   1000. 1200. 1500. 10000. ;
LCP = 'PROG' 450. 490. 525. 545. 560. 580. 625. 660. 670. 690. 690. ;
EVK = 'EVOL' 'MANU' 'T' LTK 'K' LK ;
EVRHO = 'EVOL' 'MANU' 'T' LTRHO 'RHO' LRHO ;
EVCP = 'EVOL' 'MANU' 'T' LTCP 'C' LCP ;
* MECA
LTSIGY = 'PROG' 20. 200. 300. 400. 500. 600. 700.
   800. 900. 1000. 1500. 10000. ;
LSIGY = 'PROG' 287.e6 198.e6 172.e6 157.e6 152.e6 145.e6 136.e6 127.e6
   115.e6 79.e6 5.e6 1.e6 ;
LTEMPER = 'PROG' 20. 200. 300. 400. 500. 600. 700. 800.
   900. 1000. 1500. 10000. ;
LRM = 'PROG' 900.e6 800.e6 725.e6 440.e6 400.e6 360.e6 260.e6
   225.e6 60.e6 25.e6 5.e6 4.e6 ;
EVRM = 'EVOL' 'MANU' 'T' LTEMPER 'RM' LRM ;
LB = 'PROG' 2. 2. 2. 5. 5. 5. 5. 5. 20. 20. 2. 2. ;
EVB = 'EVOL' 'MANU' 'T' LTEMPER 'B' LB ;
EVSIGY = 'EVOL' 'MANU' 'T' LTSIGY 'R0' LSIGY ;
MATHE = 'MATE' MODTHER 'K' EVK 'RHO' EVRHO 'C' EVCP ;
MAMEC = 'MATE' MODMECA 'YOUN' 200.e6 'NU' 0.3 'RHO' EVRHO 'ALPH' 20.e-6 'TALP' 0. 'TREF' 20.
                   'A' 0. 'C' 0. PSI 1. OMEG 0. 'R0' EVSIGY
                   'RM' EVRM 'B' EVB ;
* CLS
PTFIX1 = MAILT 'POIN' 'PLAN' (0. 0. 0.)
(1. 0. 0.) (0. 0. 1.) 1.e-5 ;
PTFIX2 = MAILT 'POIN' 'PLAN' (0. 0.01 0.)
(1. 0.01 0.) (0. 0.01 1.) 1.e-5 ;
PTFIXT = PTFIX1 'ET' PTFIX2 ;
BLOQM = 'BLOQ' PTFIXT 'UX' 'UY' 'UZ' ;
* CHARGEMENT THERMIQUE
SRC1 = 'SOUR' MODTHER 2.e9 MAILT ;
EVO1 = 'EVOL' 'MANU' 'TEMPS' (PROG 0. 5. 10. 10000.)
              'Q' ('PROG' 0. 1. 0. 0.) ;
CHA1 = 'CHAR' 'Q' SRC1 EVO1 ;
* PASAPAS
LTCAL = 'PROG' 0.5 'PAS' 0.5 10. 'PAS' 10. 100. 'PAS' 1000. 10000. ;
CHPTINI = 'MANU' 'CHPO' MAILT 1 'T' 20. 'NATU' 'DIFFUS' ;
MODTOT = MODMECA 'ET' MODTHER ;
MATTOT = MATHE 'ET' MAMEC ;
HTAB ='TABL' ;
HTAB . 'MODELE' = MODTOT ;
HTAB . 'CARACTERISTIQUES' = MATTOT ;
HTAB . 'BLOCAGES_MECANIQUES' = BLOQM ;
HTAB . 'CHARGEMENT' = CHA1 ;
HTAB . 'TEMPS_CALCULES' = LTCAL ;
HTAB . 'TEMPERATURES' = 'TABL' ;
HTAB . 'TEMPERATURES' . 0 = CHPTINI ;
HTAB . 'CELSIUS' = VRAI ;
HTAB . 'PRECISION' = 1e-6 ;
HTAB . 'PROCESSEURS' = 'MOT' 'MONOPROCESSEUR' ;
HTAB . 'PROCEDURE_CHARTHER' = VRAI ;
PASAPAS HTAB ;
* Tests
* (pas de test pertinent pour l'instant, on ctrole juste
* l'execution sans erreur)
lok = vrai ;
* Test final
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'SINON' ;
   'SAUT' 1 'LIGN' ;
   'MESSAGE' ('CHAINE' 'Tout sest bien passe !') ;
'FINSI' ;
'SI' interact ;
   'OPTION' 'ECHO' 1 ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
'FIN' ;
```

## simtrc [Thermique Metallurgie]
```
SAUT PAGE ;
complet = vrai ;
GRAPH = 'F' ;
* simtrc.dgibi
* Simulation du trc avec l'operateur comp
* Prise en compte de la concentration en carbone (cte)
* version initiale : Martinez le 30/07/98
* mettre complet = vrai pour generer le trc du 16MND5
* Parametres du calcul :
* Vitesse de refroidissement
lis_ref1 = prog -0.05 -0.1 -0.15 -0.2 -0.3 -0.5 -1. -2. -3. -4. -5.
                -6. -7. -8. -9. -10. -12. -15. -18. -20. -25. -30.
                -40. -50. -60. -80. -100. -400. ;
lis_ref1 = prog -0.05 -0.1 -0.3 -0.4 -0.5 -1. -2. -3. -4. -5. -7. -10.
                -15. -25. -35. -40. -60. -80. -150. ;
lis_ref2 = prog -0.07 -0.11 -0.18 -0.23 -0.4 -0.57 -1.3 -2.8 -3.1
                 -4.2 -5.5 -6.4 -7.3 -8.7 -9.9 -10.01 -12.3 -15.5
              -19. -23. -26. -34. -45. -57. -61. -88. -300. -390. ;
lis_ref = lis_ref1 ;
* Delta Temperature
d_tempe = 2. ;
* INITIALISATION DU DEPOUILLEMENT
dfer = 100. ;
dbai = 100. ;
dmar = 100. ;
ffer = 100. ;
fbai = 100. ;
fmar = 100. ;
tdf = 1. ; tff = 1. ;
tdb = 1. ; tfb = 1. ;
tdm = 1. ; tfm = 1. ;
lis_dfer = prog ;
lis_dbai = prog ;
lis_dmar = prog ;
lis_tdf = prog ;
lis_tdb = prog ;
lis_tdm = prog ;
lis_ffer = prog ;
lis_fbai = prog ;
lis_tff = prog ;
lis_tfb = prog ;
lis_refr = prog ;
lis_pfer = prog ;
lis_pbai = prog ;
lis_pmar = prog ;
* LECTURE DES DONNEES DU DIAGRAMME TRC
DTRC_1 = nuage 'TP'*flottant 'ZFF'*flottant 'ZFB'*flottant
      'TDF'*flottant 'TFF'*flottant 'TDB'*flottant 'TFB'*flottant
 -0.05 0.67 0.33 769. 644. 548. 395.
-0.1 0.45 0.55 752. 644.0 566.0 395.0
-0.3 0.16 0.84 714.0 639.0 588.0 395.0
-0.4 0.06 0.94 700.0 659.0 591.0 395.0
-0.5 0. 1. 700.0 690.0 593.0 395.0
-1.0 0. 0.96 700.0 690. 600.0 395.0
-2.0 0. 0.91 700.0 690.0 588.0 395.0 ;
DTRC_1 = DTRC_1 et (nuage 'TP'*flottant 'ZFF'*flottant 'ZFB'*flottant
   'TDF'*flottant 'TFF'*flottant 'TDB'*flottant 'TFB'*flottant
-3.0 0. 0.87 700.0 390.0 581.0 396.0
-4.0 0.0 0.69 700.0 690.0 573.0 396.0
-5.0 0.0 0.55 700.0 690.0 568.0 398.0
-7.0 0.0 0.46 700.0 690.0 559.0 400.0
-10.0 0.0 0.34 700.0 690.0 543.0 402.0
-15.0 0.0 0.22 700.0 690.0 525.0 405.0
-25.0 0.0 0.05 700.0 690.0 498.0 415.0) ;
DTRC_1 = DTRC_1 et (nuage 'TP'*flottant 'ZFF'*flottant 'ZFB'*flottant
   'TDF'*flottant 'TFF'*flottant 'TDB'*flottant 'TFB'*flottant
-35.0 0.0 0. 710.0 700.0 430.0 425.0
-40.0 0.0 0. 710.0 700.0 430.0 425.0
-60.0 0.0 0. 710.0 700.0 430.0 425.0
-80.0 0.0 0.0 710.0 700.0 430.0 425.0
-150.0 0.0 0.0 710.0 700.0 430.0 425.0 );
* Chauffage (modele de leblond)
DTCH_1 = nuage
 'COMP' 'TE' 730.0 750.0 770.0 790.0 810.0 830.0 840.0 860.0
 880.0 900.0
 'COMP' 'CK' 0.0 0.22 0.53 1.05 2.02 4.55 5.6 7.37 10.77 20.0
 'COMP' 'CL' 1.0 0.97 0.94 0.87 0.76 0.45 0.0 0.0 0.0 0.0 ;
* LECTURE DU MAILLAGE
opti dime 2 elem qua8 mode axis ;
elmat = table ;
piece = table ;
a00 = 0. 0. ;
a01 = 0.01 0. ;
a02 = 0.01 0.01 ;
a03 = 0. 0.01 ;
d1 = droi 1 a00 a01 ;
d2 = droi 1 a01 a02 ;
d3 = droi 1 a02 a03 ;
d4 = droi 1 a03 a00 ;
l_ext = (d1 et d2 et d3) ;
tot = dalle d1 d2 d3 d4 plan ;
* DEFINITION D'UN MODELE
p_mode1 = mode tot 'THERMIQUE' 'ISOTROPE' 'CONS' me1 ;
si faux ;
p_mode2 = mode tot 'TAILGRAI' 'ISOTROPE' 'CONS' me2 ;
p_mode3 = mode tot 'DIFFUSION' 'CONS' carb1 ;
finsi ;
momic_1 = mode tot melange cerem ;
mamic_1 = mate momic_1
* changement de type de certaines donnees
 'AC1' 730. 'AR1' 760. 'MS0' 422.
'BETA' -0.0307 'AC' 9146. 'AA' 37.5 'ZS' 0. 'TPLM' -0.5 'CARB' 0.0074
'ACAR' 540. 'DG0' 0.00001 'AGRA' 11200.
 'TIHT' 1000. 'TFHT' 200. 'DTHT' 2. 'NHTR' DTRC_1 'NLEB' DTCH_1
  'MS' 400. ;
phamic_1 = manu chml momic_1 'AUST' 1. 'FERR' 0. 'BAIN' 0. 'MART' 0.
 'RIGIDITE' ;
* BOUCLE SUR LES HISTOIRES THERMIQUES
n_bou1 = dime lis_ref ;
repeter bou_1 n_bou1 ;
* CHARGEMENT THERMIQUE
  t0tempe = 1000.0 ;
  t1tempe = 100.0 ;
  t_chtem = manu CHPO tot 1 'T' 1. ;
  t0chtem = t0tempe * t_chtem ;
  app_fer = 0 ;
  app_bai = 0 ;
  app_mar = 0 ;
* INITIALISATION
si faux ;
  chcarb = manu 'CHML' p_mode3 'ACC' 0.0074 'TYPE' 'ACTIVITE' ;
  chdg = manu 'CHML' p_mode2 'DG' 10.e-6 'TYPE' 'GRAIN' ;
finsi ;
  p_table = table ;
  p_table.'TEMPERATURES' = table ;
  p_table.'MATPHASES' = table ;
  p_table.'TRC' = table ;
  p_table.TEMPERATURES.0 = t0chtem ;
  p_table.MATPHASES.0 = mamic_1 et phamic_1 ;
 lma_1 = extr p_table.MATPHASES.0 comp ;
  lis_tps=prog ;
  lis_te =prog ;
  lis_pa =prog ;
  lis_pf =prog ;
  lis_pb =prog ;
  lis_pm =prog ;
* BOUCLE SUR LE TEMPS
  t_point = extr lis_ref &bou_1 ;
  t0temps = 0. ;
  t1temps = (t1tempe - t0tempe) / t_point ;
  atpnt = ABS t_point ;
  deltt = d_tempe / atpnt ;
  n_bou2 = enti((t1temps - t0temps) / deltt) + 1 ;
  t_ps = t0temps - deltt ;
mess '=============================================================' ;
mess '=============================================================' ;
mess ' Vitesse de refroidissement : ' t_point ;
  repeter bou_2 n_bou2 ;
   chdtps1 = manu chml momic_1 'DTPS' deltt ;
 chtemp0 = manu chml tot temp t_ps ;
 chtemp1 = manu chml tot temp (t_ps + deltt) ;
     t_ps = t_ps + deltt ;
     p_table.temperatures.&bou_2 = p_table.temperatures.(&bou_2-1) +
             (t_chtem * t_point * deltt) ;
     n1 = (dime p_table.temperatures) - 1 ;
     si (n1 > 0) ;
       cot1 = p_table.temperatures.&bou_2 ;
       cot0 = p_table.temperatures.(&bou_2-1) ;
       dt1 = cot1 - cot0 ;
       dtp1 = dt1 / deltt ;
       max_dt = maxi dt1 ;
       cht1 = chan 'CHAM' cot1 tot ;
       cht0 = chan 'CHAM' cot0 tot ;
       chp0 = p_table.'MATPHASES'.(&bou_2-1) ;
       chtp1 = chan cham dtp1 tot ;
       htab1 = p_table.'TRC' ;
   cho1 = comp momic_1 (cht0 et chtemp0 et chp0 et chdtps1)
      (cht1 et chtemp1) ;
  chp1 = exco cho1 lma_1 ;
       p_table.'MATPHASES'.&bou_2 = chp1 ;
     finsi ;
* verification des temperatures de debut et de fin de chgt de phase
    p_fe0 = maxi (exco 'FERR' chp0) ;
    p_ba0 = maxi (exco 'BAIN' chp0) ;
    p_au = maxi (exco 'AUST' chp1) ;
    p_fe = maxi (exco 'FERR' chp1) ;
    p_ba = maxi (exco 'BAIN' chp1) ;
    p_ma = maxi (exco 'MART' chp1) ;
    t_app = maxi (exco T cot1) ;
    tr_ma = maxi (exco chp1 MS) ;
    lis_tps= lis_tps et (prog t_ps) ;
    lis_te = lis_te et (prog t_app) ;
    lis_pa = lis_pa et (prog p_au) ;
    lis_pf = lis_pf et (prog p_fe) ;
    lis_pb = lis_pb et (prog p_ba) ;
    lis_pm = lis_pm et (prog p_ma) ;
* Temperatures d'apparition :ferrite, bainite et martensite
     si (p_fe > 0.001) ;
      si (app_fer EGA 0) ;
       app_fer = 1 ;
       t_app = maxi (exco T cot1) ;
       dfer = t_app ;
       tdf = t_ps ;
      finsi ;
     finsi ;
     si (p_ba > 0.001) ;
      si (app_bai EGA 0) ;
       app_bai = 1 ;
       t_app = maxi (exco T cot1) ;
       dbai = t_app ;
       tdb = t_ps ;
      finsi ;
     finsi ;
     si (p_ma > 0.001) ;
      si (app_mar EGA 0) ;
       app_mar = 1 ;
       t_app = maxi (exco T cot1) ;
       dmar = t_app ;
       tdm = t_ps ;
      finsi ;
     finsi ;
* Temperatures de fin de transformation de ferrite et bainite
     si (app_fer EGA 1) ;
        d_fe = p_fe - p_fe0 ;
        si (d_fe < 0.000001) ;
         app_fer = 2 ;
         t_app = maxi (exco T cot1) ;
         ffer = t_app ;
         tff = t_ps ;
        finsi ;
       finsi ;
       si (app_bai EGA 1) ;
        d_ba = p_ba - p_ba0 ;
        si (d_ba < 0.000001) ;
         app_bai = 2 ;
         t_app = maxi (exco T cot1) ;
         fbai = t_app ;
         tfb = t_ps ;
        finsi ;
      finsi ;
si ((non complet) et (&bou_2 > 150)) ;
 quitter bou_2 ;
finsi ;
  fin bou_2 ;
  lis_dfer = lis_dfer et (prog dfer) ;
  lis_dbai = lis_dbai et (prog dbai) ;
  lis_dmar = lis_dmar et (prog dmar) ;
  lis_tdf = lis_tdf et (prog tdf) ;
  lis_tdb = lis_tdb et (prog tdb) ;
  lis_tdm = lis_tdm et (prog tdm) ;
  lis_ffer = lis_ffer et (prog ffer) ;
  lis_fbai = lis_fbai et (prog fbai) ;
  lis_tff = lis_tff et (prog tff) ;
  lis_tfb = lis_tfb et (prog tfb) ;
* presentation des resultats
mess 'ferrite' dfer ffer ;
mess 'bainite' dbai fbai ;
 mess '==========================================================' ;
  n_f = (dime p_table.MATPHASES) - 1 ;
  ch4 = p_table.MATPHASES.n_f ;
* austenite
  p_au = maxi (exco 'AUST' ch4) ;
* ferrite
  p_fe = maxi (exco 'FERR' ch4) ;
* bainite
  p_ba = maxi (exco 'BAIN' ch4) ;
* martensite
  p_ma = maxi (exco 'MART' ch4) ;
* Verification des proportions
  p_tot = p_au + p_fe + p_ba + p_ma ;
mess ' INTG des fractions volumiques : ' p_tot ;
mess '===============================================================';
mess 'Tpoint     %austenite     %ferrite     %bainite     %martensite';
mess t_point p_au p_fe p_ba p_ma ;
si (non complet) ;
 quitter bou_1 ;
finsi ;
fin bou_1 ;
* TRACE DU TRC
ev_dfer = evol bleu manu TPS lis_tdf T lis_dfer ;
ev_dbai = evol vert manu TPS lis_tdb T lis_dbai ;
ev_dmar = evol manu TPS lis_tdm T lis_dmar ;
ev_ffer = evol bleu manu TPS lis_tff T lis_ffer ;
ev_fbai = evol vert manu TPS lis_tfb T lis_fbai ;
tabdess = table;
tabdess . 1 = 'MARQ TRIA NOLI' ;
tabdess . 2 = 'MARQ LOSA NOLI' ;
tabdess . 3 = 'MARQ CARR NOLI' ;
tabdess . 4 = 'MARQ TRIA NOLI' ;
tabdess . 5 = 'MARQ LOSA NOLI' ;
tabdess . 'TITRE' = table ;
tabdess . 'TITRE' . 1 = MOT 'ferrite' ;
tabdess . 'TITRE' . 2 = MOT 'bainite' ;
tabdess . 'TITRE' . 3 = MOT 'martensite' ;
tabdess . 'TITRE' . 4 = MOT 'ferrite' ;
tabdess . 'TITRE' . 5 = MOT 'bainite' ;
'SI' ('EGA' GRAPH 'O') ;
opti trac x ;
dess (ev_dfer et ev_dbai et ev_dmar et ev_ffer et ev_fbai) 'LOGX'
     LEGE TITX 'temps' TITY 'temperature' tabdess ;
'FINSI' ;
si (non complet) ;
p_au0 = .65196 ;
RESI=ABS((p_au-p_au0)/p_au0);
SI(RESI <EG 1E-2);
    ERRE 0;
SINO;
    ERRE 5;
FINSI;
sinon ;
p_au0 = 5.09126E-05 ; p_ma0 = 0.99995 ;
RES_au=ABS((p_au-p_au0)/p_au0);
RES_ma=ABS((p_ma-p_ma0)/p_ma0);
SI((RES_au <EG 1E-2) et (RES_ma <EG 1E-2));
    ERRE 0;
SINO;
    ERRE 5;
FINSI;
finsi ;
fin;
```

## test_vari_props [Thermique ProprietesVariables]
```
* FRA Exemple simple de definition d'une proriete thermique variable
* fonction de 1 parametre (EVOL) ou plusieurs parametres (NUAGE)
* Simulation axisymetrique d'une trempe sur un cylindre avec echange
* convectif avec l'air ambient. Il s'agit de la conductivite du tube
* est variable : evolution de T ou nuage de T et ETAT.
* ENG Easy example of a variable thermal property, function of 1
* parameter (EVOL) or of several parameters (NUAGE)
* Axisymetric modelisation of a tube quenching with convective heat
* exchange with ambient atmosphere. The tube heat conductivity is a
* function of the temperature T or a function of T and ETAT.
'OPTION' 'ECHO' 1 ;
OPTI DEBU 1;
* 1 * (FRA) Definitions generales - (ENG) General definitions
'OPTION' 'DIME' 2 'ELEM' QUA4 'MODE' AXIS ;
* (FRA) Definition du maillage - (ENG) Mesh definition
PD = 0. 0. ;
PC = 0.1 0. ;
PB = 0.1 0.02 ;
PA = 0. 0.02 ;
D1 = 'DROITE' 20 PD PC ;
Tube = 'TRANSLATION' 1 D1 (0. 0.02) ;
D2 = 'COTE' 2 Tube ;
D3 = 'COTE' 3 Tube ;
D4 = 'COTE' 4 Tube ;
pt_TC2 = Tube 'POINT' 'PROC' (0.095 0.) ;
pt_TC1 = Tube 'POINT' 'PROC' (0.05 0.) ;
* 'TRACER' Tube ;
* (FRA) Definition des modeles thermiques (conduction et convection)
* (ENG) Thermic models definition (conduction and convective exchange)
Mod_Tube = 'MODELISER' Tube 'THERMIQUE' 'ISOTROPE' ;
Mod_Teco = 'MODELISER' D2 'THERMIQUE' 'CONVECTION' ;
ModTot = Mod_Tube 'ET' Mod_Teco ;
* (FRA) Defintion du modele de convection
* (ENG) Convective model definition
Mat_Teco = 'MATERIAU' Mod_TECO 'H   ' 1515. ;
* (FRA) Chargement convectif - Temperature constante de l'air ambient
* (ENG) Convective loading - The temperature room is constant
T_air = 25. ;
EvTECO = 'EVOL' 'MANU' 'TEMPS' ('PROG' 0. 1.E+9)
                       'T' ('PROG' 1. 1.) ;
ChpTECO = 'MANU' 'CHPO' D2 1 'T' T_air ;
CharTECO = 'CHARGEMENT' 'TECO' ChpTECO EvTECO ;
* (FRA) Temperature initiale du tube uniforme
* (ENG) The initial temperature of the tube is uniform
T_ini = 800. ;
ChpT0 = 'MANU' 'CHPO' Tube 1 'T   ' T_ini ;
* (FRA) Instants calcules et sauves - (ENG) Calculated and saved times
l_tcalc = 'PROG' 0. 'PAS' 10. 400. ;
l_tsauv = 'PROG' 0. 10. 20. 30. 40. 50. 'PAS' 50. 400. ;
* 2 * (FRA) Calcul PASAPAS - Conductivite fonction de T
* * (ENG) PASAPAS call - Conductivity function of temperature
* (FRA) Defintion de la conductivite du tube (fonction de T)
* (ENG) Conductivity tube definition (temperature function)
EvK = 'EVOL' 'MANU' 'T   ' ('PROG' 0. 2000.) 'K   ' ('PROG' 10. 30.) ;
Mat_Tube = 'MATERIAU' Mod_Tube 'K   ' EvK 'C   ' 400. 'RHO ' 7800. ;
MatTot = Mat_Tube 'ET' Mat_Teco ;
* (FRA) Appel a PASAPAS-TRANSNON - (ENG) PASAPAS-TRANSNON call
ETAB1 = 'TABLE' ;
ETAB1.'MODELE' = ModTot ;
ETAB1.'CARACTERISTIQUES' = MatTot ;
ETAB1.'CHARGEMENT' = CharTECO ;
ETAB1.'TEMPERATURES' = 'TABLE' ;
ETAB1.'TEMPERATURES'. 0 = ChpT0 ;
ETAB1.'TEMPS_SAUVES' = l_tsauv ;
ETAB1.'TEMPS_CALCULES' = l_tcalc ;
PASAPAS ETAB1 ;
* (FRA) Depouillement des resultats - (ENG) Results extraction
TEMP1_1 = 'PROG' ; TEMP2_1 = 'PROG' ;
I = 0 ;
'REPETER' Boucle ('DIMENSION' ETAB1.'TEMPS') ;
  Tps = ETAB1.'TEMPS'.I ;
  T1 = 'EXTRAIRE' (ETAB1.'TEMPERATURES'.I) 'T  ' pt_TC1 ;
  T2 = 'EXTRAIRE' (ETAB1.'TEMPERATURES'.I) 'T  ' pt_TC2 ;
  TEMP1_1 = TEMP1_1 'ET' ('PROG' T1) ;
  TEMP2_1 = TEMP2_1 'ET' ('PROG' T2) ;
  I = I + 1 ;
'FIN' Boucle ;
* 3 * (FRA) Calcul PASAPAS - Conductivite fonction de T et de ETAT
* * (ENG) PASAPAS call - Conductivity function of temperature and ETAT parameter
* (FRA) Defintion de la conductivite du tube : K est une fonction de T et ETAT
* (ENG) Conductivity tube definition : K is function of T and ETAT
EvK = 'EVOL' 'MANU' 'T   ' ('PROG' 0. 2000.) 'K   ' ('PROG' 10. 30.) ;
NuagK = 'NUAGE' 'ETAT'*'FLOTTANT' 'K   '*'EVOLUTION' 0. EvK 10. EvK ;
* (FRA) Ici ETAT n'a aucune influence sur K (ENG) Here ETAT plays no role on K
Mat_Tube = 'MATERIAU' Mod_Tube 'K   ' NuagK 'C   ' 400. 'RHO ' 7800. ;
MatTot = Mat_Tube 'ET' Mat_Teco ;
* (FRA) Evolution du parametre externe 'ETAT'
* (ENG) Evolution of the external parameter 'ETAT'
EvEtat = 'EVOL' 'MANU' 'TEMPS' ('PROG' 0. 1.E+9)
                       'ETAT' ('PROG' 2. 2.) ;
Chp_E1 = 'MANU' 'CHPO' Tube 1 'ETAT' 1. ;
CharEtat = 'CHARGEMENT' 'ETAT' Chp_E1 EvEtat ;
* (FRA) Appel a PASAPAS-TRANSNON - (ENG) PASAPAS-TRANSNON call
ETAB2 = 'TABLE' ;
ETAB2.'MODELE' = ModTot ;
ETAB2.'CARACTERISTIQUES' = MatTot ;
ETAB2.'CHARGEMENT' = CharTECO 'ET' CharEtat ;
ETAB2.'TEMPERATURES' = 'TABLE' ;
ETAB2.'TEMPERATURES'. 0 = ChpT0 ;
ETAB2.'TEMPS_SAUVES' = l_tsauv ;
ETAB2.'TEMPS_CALCULES' = l_tcalc ;
PASAPAS ETAB2 ;
* (FRA) Depouillement des resultats - (ENG) Results extraction
TEMP1_2 = 'PROG' ; TEMP2_2 = 'PROG' ;
I = 0 ;
'REPETER' Boucle ('DIMENSION' ETAB2.'TEMPS') ;
  Tps = ETAB2.'TEMPS'.I ;
  T1 = 'EXTRAIRE' (ETAB2.'TEMPERATURES'.I) 'T  ' pt_TC1 ;
  T2 = 'EXTRAIRE' (ETAB2.'TEMPERATURES'.I) 'T  ' pt_TC2 ;
  TEMP1_2 = TEMP1_2 'ET' ('PROG' T1) ;
  TEMP2_2 = TEMP2_2 'ET' ('PROG' T2) ;
  I = I + 1 ;
'FIN' Boucle ;
* 4 * (FRA) Comparaison des resultats - Tests d'erreur
* * (ENG) Results comparison - Error tests
EcT_1 = 100. * ('MAXIMUM' ('ABS' (TEMP1_2 - TEMP1_1))) ;
EcT_2 = 100. * ('MAXIMUM' ('ABS' (TEMP2_2 - TEMP2_1))) ;
'MESS' ;
'MESS' 'Ecart Point 1 : ' EcT_1 ' %' ;
'MESS' 'Ecart Point 2 : ' EcT_2 ' %' ;
'MESS' ;
'SI' (('>' EcT_1 1.E-3) 'OU' ('>' EcT_2 1.E-3)) ;
  'ERREUR' 5 ;
'FINSI' ;
'FIN' ;
```

## rayo-2D-5 [Thermique Rayonnement]
```
* Calcul d'une plaque infinie (de largeur 2L) avec tempé-
* rature imposée au milieu et soumise au rayonnement.
* Il s'agit de trouver la température au bord en régime
* permanent.
* Néanmoins nous cherchons la solution en faisant un
* calcul transitoire avec PASAPAS pour tester celle-ci
* en configuration température imposée + rayonnement vers
* l'infini.
* Modélisation plane.
* Auteurs : Michel Bulik & Nadia Coulon
* Date : Avril 1997
* on introduit une emissivite a l infini differente de 1
* et une temperature a l'infini differente de 0K
* Options ...
    opti dime 2 elem seg2 echo 1 ;
* Paramètres ...
    L = 1. ;
    ep = L / 10 ;
    graph = faux ;
   Tempini = 1000. ;
   Tempext = 2. * Tempini ;
    cte_sb = 5.673e-8 ;
    Gamma = 1. ;
    si ( neg Gamma 0. ) ;
       lambda = (cte_sb * Tempini * Tempini * Tempini * L) / Gamma ;
       mess 'Lambda = ' lambda ;
       valemis = 0.8 ;
        e0 = 0.5 ;
    sinon ;
       lambda = 1. ;
       mess 'Lambda choisie arbitrairement = ' lambda ;
       valemis = 0. ;
       e0 = 1. ;
    finsi ;
* Points ...
    dens 0.1 ;
    p1 = 0 0 ;
    p2 = 0 ep ;
    vechoriz = L 0 ;
* Lignes ...
    li1 = p1 d 1 p2 ;
* Surface ...
    opti elem qua4 ;
    su1 = li1 tran vechoriz dini 0.1 dfin 0.01 ;
    li2 = cote 3 su1 ;
    p3 = li2 poin proc vechoriz ;
    li3 = cote 2 su1 ;
    si(graph) ;
       titr 'Le maillage de la plaque' ;
       trac su1 ;
    finsi ;
* Modèles ...
    mocnd = mode su1 thermique ;
    macnd = mate mocnd 'K' lambda 'RHO' 1. 'C' lambda ;
    moray = mode li2 thermique rayonnement INFINI ;
    maray = mate moray 'EMIS' valemis 'E_IN' e0;
* Température imposée ...
    blt = bloq 'T' li1 ;
    ti = depi blt Tempini ;
    lr1 = prog 0 100 ;
    lr2 = prog 1 1 ;
    ev1 = evol manu 't' lr1 'T' lr2 ;
    chti = char 'TIMP' ev1 ti ;
* Température extérieure ...
    chtext = manu chpo li2 1 'T' Tempext nature diffus ;
    chte = char 'TERA' ev1 chtext ;
* Préparation de la table pour PASAPAS ...
    tabnl = table ;
    tabnl . MODELE = mocnd et moray ;
    tabnl . CARACTERISTIQUES = macnd et maray ;
    tabnl . BLOCAGES_THERMIQUES = blt ;
    tabnl . CHARGEMENT = chti et chte ;
    tabnl . TEMPS_CALCULES = prog 0. pas 0.1 1.
                                     pas 0.2 2. ;
    tabnl . TEMPERATURES = table ;
    tabnl . TEMPERATURES . 0 = manu chpo su1 1 'T' Tempini ;
* tabnl . RAYONNEMENT = table ;
* tabnl . RAYONNEMENT . 1 = table ;
* tabnl . RAYONNEMENT . 1 . TYPE = 'INFINI' ;
* tabnl . RAYONNEMENT . 1 . MODELE = moray ;
    tabnl . 'PROCEDURE_THERMIQUE' = 'DUPONT' ;
    tabnl . 'CTE_STEFAN_BOLTZMANN' = cte_sb ;
    tabnl . 'RELAXATION_THETA' = 1. ;
* Appel à PASAPAS ...
    pasapas tabnl ;
* Petit post-traitement ...
    listt = prog ;
    listtp3 = prog ;
    listtp3r = prog ;
    nbpas = dime (tabnl . TEMPS) ;
    repeter surpas nbpas ;
       lindice = &surpas - 1 ;
       listt = listt et (prog (tabnl . TEMPS . lindice)) ;
       valtp3 = extr (tabnl . TEMPERATURES . lindice) T p3 ;
       listtp3 = listtp3 et (prog valtp3) ;
       valtp3r = (valtp3 - Tempext) / (Tempini - Tempext) ;
       listtp3r = listtp3r et (prog valtp3r) ;
* ... Vérification s'il n'y a pas d'oscillations spatiales ...
       si(faux) ;
          chtit = chai 'Profil de temperature au temps '
                  (tabnl . TEMPS . lindice) ;
          titr chtit ;
          profil = evol chpo (tabnl . TEMPERATURES . lindice)
                   'T' li3 ;
          dess profil ;
       finsi ;
    fin surpas ;
    titr 'Evolution de la temperature au bord de la plaque' ;
    evtp3 = evol manu 't' listt 'T' listtp3 ;
    titr 'Evolution de la temperature relative au bord de la plaque' ;
    evtp3r = evol manu 't' listt 'T' listtp3r ;
    si(graph) ;
       dess evtp3 ;
       dess evtp3r ;
    finsi ;
* Vérification si c'est OK ...
* On va résoudre analytiquement le problème en écrivant l'égalité
* des flux (T = température au bord de la plaque) :
* T_imp - T
* lambda ------------- = epsilon * sigma * (T^4 - T_ext^4)
* L
* avec epsilon(e,e0)
    ee = ((1./valemis) + (1./e0) - 1.); ee = 1./ee ;
    mess ' ee: ' ee ;
    A_0 = -1 * ((lambda * Tempini / L) +
                             (ee * cte_sb * (Tempext**4))) ;
    A_1 = lambda / L ;
    A_2 = 0.0 ;
    A_3 = 0.0 ;
    A_4 = ee * cte_sb ;
    r1 = racp A_0 A_1 A_2 A_3 A_4 ;
* mess 'Zéros du polynôme :' r1 ' ' r2 ' ' r3 ' ' r4 ;
    sol_anlt = r1 extr 2 ;
    sol_calc = extr listtp3 (dime listtp3) ;
    mess ' anal ' sol_anlt ; mess ' calc ' sol_calc ;
    erreur = 100 * (sol_calc - sol_anlt) / sol_anlt ;
    mess 'Erreur relative = ' erreur '%' ;
    si(abs(erreur) > 0.01) ;
       erre 5 ;
    sinon ;
       erre 0 ;
    finsi ;
* Bye ...
    fin ;
```

## rayo-axi-4 [Thermique Rayonnement]
```
* Ce jeu de données permet la vérification du
* calcul des facteurs de forme dans le cas
* axisymétrique. On calcule le flux dû au
* rayonnement entre 2 sphères concentriques, la
* température de chacune des sphères étant
* homogène. Le résultat est comparé à la solution
* analytique, voir
* Jean Crabol, Transfert de Chaleur, tome 2,
* Masson, 1990, pp.169-175
* Options
option dime 2 mode axis elem qua4 ;
graph = faux ;
* DEFINITION DE LA GEOMETRIE DU PROBLEME
* Dimensions de la sphere interieure
RIint = 97.2e-3;
MRIint = -97.2e-3;
RIext = 99.0e-3;
MRIext = -99.0e-3;
* Dimensions de la sphere exterieure
REint = 130.0e-3;
MREint = -130.0e-3;
REext = 134.5e-3;
MREext = -134.5e-3;
* Nombres de divisions
n1 = 10 ; n2 = 2 ; n3 = 4 ;
* Le centre
O = 0. 0. ;
* Points sur l'enceinte interieure
P1 = 0. RIint;
P2 = RIint 0.;
P3 = 0. MRIint;
P4 = 0. MRIext;
P5 = RIext 0.;
P6 = 0. RIext;
* Points sur l'enceinte exterieure
Q1 = 0. REint;
Q2 = REint 0.;
Q3 = 0. MREint;
Q4 = 0. MREext;
Q5 = REext 0.;
Q6 = 0. REext;
* Les lignes (droites et arcs)
ARCP1 = cerc n1 P1 O P2 ;
ARCP2 = cerc n1 P2 O P3 ;
ARCII = ARCP1 et ARCP2 ;
ARCP3 = cerc n1 P4 O P5 ;
ARCP4 = cerc n1 P5 O P6 ;
ARCIE = ARCP3 et ARCP4 ;
ARCQ1 = cerc n1 Q1 O Q2 ;
ARCQ2 = cerc n1 Q2 O Q3 ;
ARCEI = ARCQ1 et ARCQ2 ;
ARCQ3 = cerc n1 Q4 O Q5 ;
ARCQ4 = cerc n1 Q5 O Q6 ;
ARCEE = ARCQ3 et ARCQ4 ;
P6P1 = droi n2 P6 P1 ;
P3P4 = droi n2 P3 P4 ;
Q6Q1 = droi n2 Q6 Q1 ;
Q3Q4 = droi n2 Q3 Q4 ;
Q1P6 = droi n3 Q1 P6 ;
P4Q3 = droi n3 P4 Q3 ;
* Les surfaces
SPHERINT = P6P1 ARCII P3P4 ARCIE DALLE ;
SPHEREXT = Q6Q1 ARCEI Q3Q4 ARCEE DALLE ;
SPHERAIR = Q1P6 ARCIE P4Q3 ARCEI DALLE ;
iARCIE=inve ARCIE ;
iARCEI=inve ARCEI ;
cavite = iARCIE et iARCEI ;
TOUTacie = SPHERINT et SPHEREXT ;
TOUT = TOUTacie ;
si(graph) ;
   titr 'Le maillage du modele' ;
   trac TOUT ;
finsi ;
* Rayonnement
MRI = MODELI iARCIE thermique RAYONNEMENT 'CAVITE' CONS 'CAV1';
MRE = MODELI iARCEI thermique RAYONNEMENT 'CAVITE' CONS 'CAV1';
mrt = mri et mre ;
vei = 0.9 ;
vee = 0.3 ;
ei = mate mri 'EMIS' vei ;
ee = mate mre 'EMIS' vee ;
chemis = ei et ee ;
tref = 0. ;
* On testera sur le champ de température suivant
T_inter = 700.0 ;
T_exter = 1000.0 ;
T_inter = T_inter + 273.0 ;
T_exter = T_exter + 273.0 ;
chptint = manu chpo spherint 1 T T_inter nature discret ;
chptext = manu chpo spherext 1 T T_exter nature discret ;
chptmpt = chptint et chptext ;
* Les facteurs de forme
ff = ffor mrt chemis;
* Matrice de rayonnement
mr = raye mrt ff chemis ;
* Conductivité due au rayonnement
cte_sb = 5.67e-8 ;
cr = rayn mrt mr (chan CHAM chptmpt mrt GRAVITE) cte_sb ;
* Flux résultant
flux12 = cr * chptmpt ;
flux1 = redu flux12 iARCIE ;
flux2 = redu flux12 iARCEI ;
rsfl1 = maxi (resu flux1) ;
rsfl2 = maxi (resu flux2) ;
* Solution analytique
solflux = cte_sb * 4 * pi * RIext * RIext * ((T_exter**4)-(T_inter**4));
denom1 = 1.0 / vei ;
denom2 = (RIext * RIext * ((1.0/vee) - 1.0)) / (REint*REint) ;
denom = denom1 + denom2 ;
solflux = solflux / denom ;
diffrel = 100 * ((abs rsfl2) - solflux) / solflux ;
opti echo 0 ;
mess 'Flux arrivant sur la sphère intérieure' rsfl1 ;
mess 'Flux partant de la sphère extérieure  ' rsfl2 ;
mess 'Solution analytique pour le flux = ' solflux ;
mess 'Erreur obtenue est de ' diffrel '%';
opti echo 1 ;
* Test si c'est OK
si((abs diffrel) > 1.) ;
   erre 5 ;
finsi;
* Bye
fin ;
```

## arcgau [Thermique Statique]
```
complet = faux;
* pour calcul complet mettre complet à : vrai;
* Test de la procedure ARCGAU : Calcul du champ de température
* créé par le déplacement d'un arc de soudure, de la
* largeur de bain et comparaison avec la solution
* analytique
* (D'après Rosenthal : Mathematical Theory of Heat
* Distribution During Welding and Cutting)
opti dime 3 elem cub8 echo 1;
* Définition de la plaque
* Abscisse minimale
xini = -0.05;
* Abscisse maximale
xfin = 0.03;
* Nombre d'éléments
si complet;
nbex = 81;
sinon;
nbex = 31;
finsi;
* Densité
denx = (xfin - xini)/nbex;
* Ordonnée minimale
yini = -0.025;
* Ordonnée maximale
yfin = 0.025;
* Nombre d'éléments
si complet ;
nbey = 21;
sinon;
nbey = 11;
finsi;
* Densité
deny = (yfin - yini)/nbey;
* Cote minimale
zini = -0.002;
* Cote maximale
zfin = 0.;
* Nombre d'éléments
nbez = 2;
p1 = xini yini zfin;
p2 = xini yfin zfin;
p3 = xfin yfin zfin;
p4 = xfin yini zfin;
l1 = d nbey p1 p2;
l2 = d nbex p2 p3;
l3 = d nbey p3 p4;
l4 = d nbex p4 p1;
* Surface supérieure
su1 = dall l1 l2 l3 l4 'PLAN';
p11 = xini yini zini;
p12 = xini yfin zini;
p13 = xfin yfin zini;
p14 = xfin yini zini;
l11 = d nbey p11 p12;
l12 = d nbex p12 p13;
l13 = d nbey p13 p14;
l14 = d nbex p14 p11;
* Surface inférieure
su11 = dall l11 l12 l13 l14 'PLAN';
vep = 0. 0. (zini - zfin);
* Maillage
obj = su1 volu nbez 'TRAN' vep;
elim (su11 et obj) 1.e-7;
* Calcul
* Température de fusion
si complet;
TFUSION = 1400.;
sinon;
TFUSION = 1200;
finsi;
TAB1 = TABLE;
TAB1.'RENDEMENT' = 0.65;
TAB1.'DIFFUSVITE' = 35./(7200.*790.);
TAB1.'CONDUCTIVITE' = 35.;
TAB1.'VITESSE' = 1.667E-3;
TAB1.'T0' = 20.;
TAB1.'TFUSION' = TFUSION;
TAB1.'NTERMES' = 15;
TAB1.'MAILLAGE' = OBJ;
TAB1.'NSURFACES' = 2;
TAB2 = TABLE;
TAB2.1 = SU1;
TAB2.2 = SU11;
TAB1.'SURFACE' = TAB2;
TAB1.'EPAISSEUR' = (zini - zfin);
TAB1.'INSTANT' = 0.;
TAB1.'LOCAL' = VRAI;
si complet;
TAB1.'PRECISION' = 0.0001;
sinon;
TAB1.'PRECISION' = 0.0005;
finsi;
TAB1.'PUISSANCE' = 600.;
TAB1.'GAUSS' = FAUX;
cht = arcgau tab1;
* Solution analytique au point ou la largeur de bain a ete evaluee
EPS1 = 1.0E-4;
Q = TAB1.'PUISSANCE';
RHO = TAB1.'RENDEMENT';
A = TAB1.'DIFFUSVITE';
LBDA = TAB1.'CONDUCTIVITE';
V = TAB1.'VITESSE';
T0 = TAB1.'T0';
NTER = 15;
OBJ = TAB1.'MAILLAGE';
THK = TAB1.'EPAISSEUR';
X = TAB1.'XBAIN'. 1;
Y = TAB1.'LARGEUR'. 1;
Z = 0.;
KS = X;
R = ((KS**2) + (Y**2) + (Z**2))**0.5;
R = R + EPS1;
TT = ((-0.5)*V/A)*R;
TT = (EXP(TT))/R;
I = 0;
REPETER BOUC1 NTER;
   I = I + 1;
   TN = 2.*I*THK;
   RN = ((KS**2) + (Y**2) + ((TN - Z)**2))**0.5;
   RPN = ((KS**2) + (Y**2) + ((TN + Z)**2))**0.5;
   TN = ((-0.5)*V/A)*RN;
   TN = (EXP TN)/RN;
   TPN = ((-0.5)*V/A)*RPN;
   TPN = (EXP TPN)/RPN;
   TT = TT + TN + TPN;
FIN BOUC1;
TT = (EXP(((-0.5)*V/A)*KS))*TT;
TT = (Q*RHO/(2.*PI*LBDA))*TT;
T = T0 + TT;
mess 'Température de fusion : ' (TAB1.'TFUSION');
mess 'Solution analytique   : ' T;
RESI = abs ((TFUSION - T)/T);
mess 'Erreur                : ' RESI;
si complet ;
erma = 5.e-3;
sinon;
erma =4.5e-2;
finsi;
SI (RESI < erma);
    ERRE 0;
SINON;
    ERRE 5;
FINSI;
fin;
```

## couplage_thermique3 [Thermique Transitoire]
```
* ------------ Cas test couplage_thermique3.dgibi -------------------
* Tests des opérateurs de Castem-fluide
* - Options générales
OPTI DIME 2 ELEM QUA8 ECHO 0 ;
GRAPH = 'N' ;
EPS0 = 1.D-6 ;
* Couplage thermique entre deux domaines solides l'échange entre les
* deux domaines étant réalisés en assurant la continuité du flux et
* une relation entre les champs inconnues à la frontière : on compare
* à les solutions stationnaires calculée et analytique.
* La géométrie est un barreau constitué de deux parties de longueur
* respective L1 et L2 et de diffusivité thermique D1 et D2. On a la
* relation b1*Tg + b2*Tg = b3 à l'interface, bi étant connus et Tg
* (resp. Td) représentant la valeur à la frontière coté gauche (resp.
* coté droit). On note T1(x) (resp. T2(x)) la température dans le
* premier barreau (resp. dans le deuxième).
* Chargement : Flux nul sur les frontières haute et basse (1D) et
* température imposées aux deux extrémités (notée T1 et T2).
* Solution stationnaire : Soit Tg (resp. Td) la température au niveau
* de l'interface entre les deux barreaux vue du premier barreau (resp.
* du deuxième). A l'état stationnaire, l'égalité des gradients et la
* condition de saut à l'interface donne :
* Tg*det = (a1*T1 + a2*T2)*b2 - b3*a2
* Td*det = b3*a1 - (a1*T1 + a2*T2)*b1
* avec a1=D1/L1, a2=D2/L2 et det=a1b2 - a2b1
* On a alors
* T1(x) = T1 + (Tg-T1) x/L1 pour x in [0,L1]
* T2(x) = T2 + (Td-T2) (L1+L2-x)/L2 pour x in [L1,L1+L2]
* Application numérique : D1=2 ; L1=1 ; T1=0 ; D2=3 ; L2=5 ; T2=1 ;
* Relation de saut : 5*Tg - 3*Td = 2
* On obtient alors a1=2 et a2=3/5; Tg=1/3 et Td=-1/9 ;
* T1(x) = x/3
* T2(x) = (2*x-3)/9
* ATTENTION : La convergence de l'algorithme de Quarteroni n'est pas
* garantie pour d'autres choix de data !
* Auteur : F.Dabbene 05/06
* = Données physico-numériques
* DISCR=LINE/MACRO/QUAF
DISCR = 'LINE' ;
L1 = 1. ; D1 = 2. ; T1 = 0. ; a1 = D1/L1 ;
L2 = 5. ; D2 = 3. ; T2 = 1. ; a2 = D2/L2 ;
* b1 = 7. ; b2 = 11. ; b3 = 2. ;
* b1 =-5. ; b2 = 5. ; b3 = 10. ;
* b1 = 1. ; b2 = -1. ; b3 = -2. ;
b1 = 5. ; b2 = -3. ; b3 = 2. ;
T0 = T1 + T2 / 2. ;
* --------------------------------------- Début de la procédure KEXEC
'DEBP' kexec ;
* K E X E C
* Résolution implicite d'un problème de mécanique des fluides décrit
* par l'intermédiaire d'une table structurée par l'opérateur EQEX.
* E/ rv : Table décrivant le problème à résoudre
* /S rv : A l'indice INCO, table contenant la solution au temps final
* L'utilisateur peut par l'intermédiaire de procédures personnelles
* stocker les résultats aux temps intermédiaires, faire des tracés, ...
* K E X E C
'ARGUMENT' rv*'TABLE   ' ;
* TESTS et INITIALISATION
* On n'accepte que les formulations en modèle NAVIER_STOKES
'SI' ('EGA' (rv . 'NAVISTOK') 0) ;
   'MESS' 'Pas de modèle NAVIER_STOKES' ;
   'ERRE' 5 ;
'FINSI' ;
* On n'accepte qu'un schéma en temps d'Euler
* ischt=0 si le schéma en temps n'est ni BDF2, ni BDF4
ischt = 0 ;
dimope = 'DIME' (rv . 'LISTOPER') ;
'REPETER' bloc0 dimope ;
      nomper = 'EXTRAIRE' &bloc0 (rv . 'LISTOPER') ;
      notable = 'MOT' ('TEXTE' ('CHAINE' &bloc0 nomper)) ;
      'SI' ('EGA' nomper 'DFDT    ') ;
         ischt = ischt + rv . notable . 'KOPT' . 'ISCHT' ;
      'FINSI' ;
'FIN' bloc0 ;
'SI' ('NEG' ischt 0) ;
   'MESS' 'Pas de schéma en temps autre que Euler' ;
   'ERRE' 5 ;
'FINSI' ;
* Coefficient de relaxation mis à 1 si non initialisé
'SI' ('NON' ('EXISTE' rv 'OMEGA')) ;
   'MESS' '** WARNING ** OMEGA NON défini --> OMEGA=1' ;
   omeg = 1.D0 ;
'SINON' ;
   omeg = rv . 'OMEGA' ;
'FINSI' ;
* Création de la table pour historique
'SI' ('NON' ('EXISTE' rv 'HIST')) ;
   rv . 'HIST' = 'TABLE' ;
'FINSI' ;
* IMPKRES : Niveau d'impression pour KRES
* IMPTCRR : Fréquence d'impression pour TCRR (affichage résidu)
IMPKRES = 0 ;
IMPTCRR = RV . 'IMPR' ;
* RESOLUTION suivant EQEX
* 1
* Boucle en temps
ITMA = rv . 'ITMA' ;
'SI' ('<EG' ITMA 1) ; ITMA = 1 ; 'FINSI' ;
'REPETER' bloc1 ITMA ;
* 2
* Boucle de point fixe interne à un pas de temps
'REPETER' bloci (rv . 'NITER') ;
* st mat : Second membre et matrice des opérateurs DFDT
* sf mau : Second membre er matrice des opérateurs sauf DFDT
st mat = 'KOPS' 'MATRIK' ;
sf mau = 'KOPS' 'MATRIK' ;
* 3
* Boucle sur les opérateurs de EQEX
'REPETER' bloc2 dimope ;
      nomper = 'EXTRAIRE' &bloc2 (rv . 'LISTOPER') ;
      notable = 'MOT' ('TEXTE' ('CHAINE' &bloc2 nomper)) ;
      'SI' ('EGA' nomper 'DFDT    ') ;
         msi mai = ('TEXTE' nomper) (rv . notable) ;
         mat = mat 'ET' mai ;
         st = st 'ET' msi ;
      'SINO' ;
         msi mai = ('TEXTE' nomper) (rv . notable) ;
         mau = mau 'ET' mai ;
         sf = sf 'ET' msi ;
      'FINSI' ;
'FIN' bloc2 ;
* Fin Boucle sur les opérateurs de EQEX
* 3
s2 = sf 'ET' st ;
ma1 = mau 'ET' mat ;
'SI' ('EXISTE' rv 'CLIM') ;
   s1 = rv . 'CLIM' ;
'SINON' ;
   s1 = ' ' ;
'FINSI' ;
rv . 'S2' = s2 ;
rv . 'METHINV' . 'MATASS' = ma1 ;
rv . 'METHINV' . 'MAPREC' = ma1 ;
res = 'KRES' ma1 'TYPI' (rv . 'METHINV')
                  'CLIM' s1
                  'SMBR' s2
                  'IMPR' IMPKRES ;
* 'LIST' res ;
'SI' ('EXIS' (rv . 'INCO') 'LX') ;
   rv . 'INCO' . 'LXOK' = 1 ;
   rv . 'INCO' . 'LX' = 'EXCO' 'LX' res ;
'FINSI' ;
eps = 'TCRR' res omeg (rv . 'INCO') 'IMPR' IMPTCRR ;
'MENAGE' ;
'FIN' bloci ;
* Fin Boucle de point fixe interne à un pas de temps
* 2
irt = 0 ;
'SI' ('EGA' (rv . 'ITMA') 0) ;
   irt = 'TCNM' rv 'NOUP';
'SINON' ;
   irt = 'TCNM' rv ;
'FINSI' ;
'MENAGE' ;
'SI' ('EGA' irt 1) ;
   'MESSAGE' ' Temps final atteint : ' (rv . 'PASDETPS' . 'TPS') ;
   'QUITTER' bloc1 ;
'FINSI' ;
'FIN' bloc1 ;
* Fin Boucle en temps
* 1
* K E X E C
'FINPROC' ;
* --------------------------------------- Fin de la procédure KEXEC
* --------------------------------------- Début de la procédure KRELA
'DEBPROC' krela rvx*table ;
RV = RVX . 'EQEX' ;
fron = 'DOMA' RVX.'DOMZ' 'MAILLAGE' ;
chp1 mat1 = 'KOPS' 'MATRIK' ;
* Imposition du flux pour chaque sous-problème
chp1 mat1 = 'LAPN' rv . '1LAPN' ;
tf1 = 'NOMC' 'T1' rv . 'INCO' . 'T1' ;
val1 = 'KOPS' mat1 'MULT' tf1 ;
val1 = 'NOMC' 'SCAL' val1 ;
chp2 mat2 = 'LAPN' rv . '2LAPN' ;
tf2 = 'NOMC' 'T2' rv . 'INCO' . 'T2' ;
val2 = 'KOPS' mat2 'MULT' tf2 ;
val2 = 'NOMC' 'SCAL' val2 ;
v1 = val1 - val2 / 2. ;
v2 = val2 - val1 / 2. ;
rv . 'INCO' . 'FLU1' = 'KCHT' RVX.'DOMZ' 'SCAL' 'SOMMET' v1 ;
rv . 'INCO' . 'FLU2' = 'KCHT' RVX.'DOMZ' 'SCAL' 'SOMMET' v2 ;
rela1 = 'RELA' b1 'UX' fron + b2 'UY' fron ;
smr1 = 'DEPI' rela1 b3 ;
rela2 = 'KOPS' 'RIMA' rela1 ;
rela3 = 'KOPS' 'CHANINCO' rela2
               ('MOTS' 'LX' 'UX' 'UY')
               ('MOTS' 'LX' 'T1' 'T2')
               ('MOTS' 'FLX' 'FX' 'FY')
               ('MOTS' 'LX' 'T1' 'T2')
;
smr3 = 'EXCO' smr1 'FLX' 'LX' ;
'FINP' smr3 rela3 ;
* --------------------------------------- Fin de la procédure KRELA
* = MAILLAGE
XMIN = 0. ; X1 = XMIN + L1 ; X2 = X1 + L2 ;
YMIN = 0. ; DY = 1. ; Y1 = YMIN + DY ; Y2 = Y1 + DY ;
NX = 5 ; NY = 1 ;
* ------------------------------------------ Points du premier domaine
P1 = XMIN YMIN ;
P2 = X1 YMIN ;
P3 = X1 Y2 ;
P4 = XMIN Y2 ;
* ------------------------------------------ Points du deuxième domaine
PD1 = P2 ;
PD2 = X2 YMIN ;
PD3 = X2 Y2 ;
PD4 = P3 ;
* ------------------------------------------ Lignes du premier domaine
P1P2 = P1 'DROIT' NX P2 ;
P2P3 = P2 'DROIT' NY P3 ;
P3P4 = P3 'DROIT' NX P4 ;
P4P1 = P4 'DROIT' NY P1 ;
* ------------------------------------------ Lignes du deuxième domaine
PD1PD2 = PD1 'DROIT' NX PD2 ;
PD2PD3 = PD2 'DROIT' NY PD3 ;
PD3PD4 = PD3 'DROIT' NX PD4 ;
PD4PD1 = 'INVERSE' P2P3 ;
* ------------------------------------------ Maillages
* Afin d'éviter toute confusion de maillages, ces objets sont à écraser
* après la création des modèles (à remplacer par le maillage qui
* soustend le modèle)
DOM1 = 'DALLER' P1P2 P2P3 P3P4 P4P1 ;
DOM2 = 'DALLER' PD1PD2 PD2PD3 PD3PD4 PD4PD1 ;
DGAU = P4P1 ;
DDRO = PD2PD3 ;
DBA1 = P1P2 ;
DBA2 = PD1PD2 ;
* = Création des MODELES
DDOM1 = 'CHANGER' DOM1 'QUAF' ;
DDOM2 = 'CHANGER' DOM2 'QUAF' ;
DDOMT = DDOM1 'ET' DDOM2 ;
DDBA1 = 'CHANGER' DBA1 'QUAF' ;
DDBA2 = 'CHANGER' DBA2 'QUAF' ;
DDGAU = 'CHANGER' DGAU 'QUAF' ;
DDDRO = 'CHANGER' DDRO 'QUAF' ;
DFRON = 'CHANGER' P2P3 'QUAF' ;
$DOM1 = 'MODELISER' DDOM1 'NAVIER_STOKES' DISCR ;
$DOM2 = 'MODELISER' DDOM2 'NAVIER_STOKES' DISCR ;
$DOMT = 'MODELISER' DDOMT 'NAVIER_STOKES' DISCR ;
$DBA1 = 'MODELISER' DDBA1 'NAVIER_STOKES' DISCR ;
$DBA2 = 'MODELISER' DDBA2 'NAVIER_STOKES' DISCR ;
$DGAU = 'MODELISER' DDGAU 'NAVIER_STOKES' DISCR ;
$DDRO = 'MODELISER' DDDRO 'NAVIER_STOKES' DISCR ;
$FRON = 'MODELISER' DFRON 'NAVIER_STOKES' DISCR ;
DOM1 = 'DOMA' $DOM1 'MAILLAGE' ;
DOM2 = 'DOMA' $DOM2 'MAILLAGE' ;
DOMT = 'DOMA' $DOMT 'MAILLAGE' ;
DGAU = 'DOMA' $DGAU 'MAILLAGE' ;
DDRO = 'DOMA' $DDRO 'MAILLAGE' ;
FRON = 'DOMA' $FRON 'MAILLAGE' ;
DBA1 = 'DOMA' $DBA1 'MAILLAGE' ;
DBA2 = 'DOMA' $DBA2 'MAILLAGE' ;
* = Solution analytique
DET0 = a1*b2 - (a2*b1) ;
DET1 = a1*T1 + (a2*T2) * b2 - (a2*b3) ;
DET2 = a1*T1 + (a2*T2) * b1 * -1. + (a1*b3) ;
TG = DET1 / DET0 ;
TD = DET2 / DET0 ;
D1X = 'EXTR' ('EVOL' 'CHPO' DBA1 ('COOR' 1 DBA1)) 'ORDO' 1 ;
D2X = 'EXTR' ('EVOL' 'CHPO' DBA2 ('COOR' 1 DBA2)) 'ORDO' 1 ;
X1X = D1X / L1 ;
NBPT = 'NBEL' ('CHAN' 'POI1' DBA1) ;
X2X = D2X - ('PROG' NBPT*L1) / L2 ;
T1X = (TG-T1)*X1X + ('PROG' NBPT*T1) ;
T2X = (T2-TD)*X2X + ('PROG' NBPT*TD) ;
EV1 = 'EVOL' 'ROUG' 'MANU' D1X T1X ;
EV2 = 'EVOL' 'ROUG' 'MANU' D2X T2X ;
EV3 = EV1 ET EV2 ;
* MODELISATION DU PROBLEME
* L'état stationnaire est obtenu en résolvant le problème contraint par
* la relation sur les températures d'interface, la condition de flux
* continu étant imposée à chaque pas d'un processus itératif (sorte
* d'algorithme de Quarteroni sans découplage mais avec condition de
* Neumann/Neumann à l'interface entre les deux problèmes)
* = Description du problème (table EQEX)
* Description de chaque sous-problème
RV = 'EQEX' $DOMT 'ITMA' 1 'NITER' 200 'ALFA' 1.
            'OPTI' 'EF' 'IMPL'
            'ZONE' $DOM1 'OPER' 'LAPN' D1 'INCO' 'T1'
            'ZONE' $DOM2 'OPER' 'LAPN' D2 'INCO' 'T2' ;
* Traitement de l'interface
RV = 'EQEX' RV
            'OPTI' 'EF' 'IMPL' 'CENTREE'
            'ZONE' $FRON 'OPER' 'FIMP' 'FLU1' 'INCO' 'T1'
            'ZONE' $FRON 'OPER' 'FIMP' 'FLU2' 'INCO' 'T2'
            'ZONE' $FRON 'OPER' KRELA
            ;
* Conditions aux limites (extrémités du domaine)
RV = 'EQEX' RV
            'CLIM' 'T1' 'TIMP' DGAU T1
            'CLIM' 'T2' 'TIMP' DDRO T2 ;
* = Initialisation de la table INCO et résolution
RV . 'INCO' . 'T1' = 'KCHT' $DOM1 SCAL SOMMET T0 ;
RV . 'INCO' . 'T2' = 'KCHT' $DOM2 SCAL SOMMET T0 ;
RV . 'INCO' . 'FLU1' = 'KCHT' $FRON SCAL SOMMET 0. ;
RV . 'INCO' . 'FLU2' = 'KCHT' $FRON SCAL SOMMET 0. ;
chp1 mat1 = 'KOPS' 'MATRIK' ;
RV . 'INCO' . 'LX' = chp1 ;
* Méthode d'inversion du problème : méthode directe
rv . 'METHINV' . 'TYPINV' = 1 ;
* -------------------- Utilisé en itératif seulement
rv . 'METHINV' . 'IMPINV' = 0 ;
rv . 'METHINV' . 'NITMAX' = 100 ;
rv . 'METHINV' . 'PRECOND' = 3 ;
rv . 'METHINV' . 'RESID' = 1.e-6 ;
rv . 'METHINV' . 'FCPRECT' = 1 ;
rv . 'METHINV' . 'FCPRECI' = 1 ;
rv . 'METHINV' . 'PCMLAG' = 'APR2' ;
KEXEC RV ;
* = Post-traitement de la solution calculée
EVC1 = 'EVOL' 'CHPO' DBA1 RV.'INCO'.'T1' ;
EVC2 = 'EVOL' 'CHPO' DBA2 RV.'INCO'.'T2' ;
CT1 = 'EXTR' EVC1 'ORDO' 1 ;
CT2 = 'EXTR' EVC2 'ORDO' 1 ;
EVC3 = ('EVOL' 'VERT' 'MANU' D1X CT1)
  'ET' ('EVOL' 'VERT' 'MANU' D2X CT2) ;
* = Tracés
'SI' ('EGA' GRAPH 'O') ;
CHAM1 = 'CHAN' 'CHAM' RV.'INCO'.'T1' DOM1 ;
CHAM2 = 'CHAN' 'CHAM' RV.'INCO'.'T2' DOM2 ;
'TRAC' $DOMT (CHAM1 'ET' CHAM2) ;
TAB1 = 'TABLE' ;
TAB1 . 'TITRE' = 'TABLE' ;
TAB1 . 'TITRE' . 2 = 'Solution castem' ;
TAB1 . 'TITRE' . 1 = '---------------' ;
TAB1 . 'TITRE' . 4 = 'Solution exacte' ;
TAB1 . 'TITRE' . 3 = '---------------' ;
TAB1 . 1 = 'MARQ CROI NOLI' ;
TAB1 . 2 = 'MARQ CROI NOLI' ;
'DESS' (EVC3 'ET' EV3) 'TITR' 'Temperature en fonction de x'
                       'TITX' 'x' 'TITY' 'T' 'MIMA'
                       'LEGE' TAB1 ;
'FINSI' ;
* = Controle erreur
SOM1 = 'ABS' (('MAXI' ('INTG' EV3)) - ('MAXI' ('INTG' EVC3))) ;
TEST = SOM1 '<' EPS0 ;
'SI' TEST ;
     'ERRE' 0 ;
'SINO' ;
     'MESS' 'Analytic Integration -  Computed = Difference ' ;
     'MESS' ('MAXI' ('INTG' EV3))'-' ('MAXI' ('INTG' EVC3)) '=' SOM1 ;
     'ERRE' 5 ;
'FINSI' ;
'FIN' ;
```

## tran8 [Thermique Transitoire]
```
* CAS TEST DU 91/06/13 PROVENANCE : TEST
* Test tran8.dgibi: jeux de données
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
GRAPH = 'N' ;
SAUT PAGE;
SI (NEG GRAPH 'N') ;
  OPTI ECHO 1 ;
  OPTI TRAC PSC ;
SINO ;
  OPTI ECHO 0 ;
FINSI ;
SAUT PAGE;
* TRAN8
* THERMIQUE TRANSITOIRE LINEAIRE EN 2D
* Test NAFEMS numero T3
* description
* A C B
* <_0.02_>
* <______________0.1 m______________>
* ---> axe X
* conditions aux limites
* - temperature imposee au point A :
* TA = 0
* - temperature imposee au point B :
* TB = 100 * sin (PI * temps / 40)
OPTI DIME 2;
OPTI ELEM QUA4;
* ---------- geometrie : maillage ---------
PA1 = 0. 0.; PB1 = 0.1 0. ;
PA2 = 0. 0.01; PB2 = 0.1 0.01;
N = 10;
D1 = PA1 DROI N PB1;
D2 = PB1 DROI 1 PB2;
D3 = PB2 DROI N PA2;
D4 = PA2 DROI 1 PA1;
SUR1 = DALL D1 D2 D3 D4 PLAN;
PC = POIN SUR1 PROC (0.08 0.);
SI (NEG GRAPH 'N');
  TITR 'TRAN8 : MAILLAGE';
  TRAC 'QUAL' SUR1;
FINSI;
* --------- modeles - materiaux -----------
MODL1 = MODE SUR1 THERMIQUE ISOTROPE QUA4;
MATR1 = MATE MODL1 'RHO' 7200 'K' 35.0 'C' 440.5;
* temperatures imposees : fonction du temps
* - Cote PA : temperature constante
* de 0 degres celcius
* - Cote PB : temperature variable
* en fonction du temps
BLOCD4 = BLOQ D4 'T';
BLOCD2 = BLOQ D2 'T';
TEMPD4 = DEPI BLOCD4 1.;
TEMPD2 = DEPI BLOCD2 1.;
* Un pas toutes les secondes,
* temps maximum 40. s.
LTEMPS = PROG 0. PAS 1. 40.;
LD4 = PROG 41 * 0.;
LD2 = PROG SINU (1. / 80.) AMPL 100 LTEMPS;
EVOLD4 = EVOL MANU TEMPS LTEMPS THETA LD4;
EVOLD2 = EVOL MANU TEMPS LTEMPS THETA LD2;
CHAD4 = CHAR 'TIMP' TEMPD4 EVOLD4;
CHAD2 = CHAR 'TIMP' TEMPD2 EVOLD2;
* Creation d'un flux nul (type chargement)
FLU0 = MANU CHPO (D1 ET D3) 1 Q 0.;
EVOL3= EVOL MANU TEMP LTEMPS FLUX (PROG 41 * 1.);
FLU1 = CHAR 'Q' FLU0 EVOL3;
* --- objets pour la procedure PASAPAS ----
BLOCT = (BLOCD2 ET BLOCD4);
CHART = (FLU1 ET CHAD4 ET CHAD2);
TAB1 = TABL;
TAB1.'TEMPERATURES' = TABL;
TAB1.'TEMPERATURES' . 0 = MANU CHPO SUR1 1 T 0.;
TAB1.'BLOCAGES_THERMIQUES' = BLOCT;
TAB1.'CHARGEMENT' = CHART;
TAB1.'MODELE' = MODL1;
TAB1.'CARACTERISTIQUES' = MATR1;
TAB1.'TEMPS_SAUVES' = PROG 0. PAS 1. 32.;
TAB1.'TEMPS_CALCULES' = PROG 0. PAS 1. 32.;
TAB1.'PROCEDURE_THERMIQUE' = LINEAIRE;
PASAPAS TAB1;
* ------- extraction des resultats --------
* Temperature du point C a t = 32 s.
* Construction de l'evolution de T au cours
* du temps
LTEMPE = VIDE 'LISTREEL';
LTEMPS = VIDE 'LISTREEL';
NBPAS = DIME (TAB1. 'TEMPS') ;
REPE SURPAS NBPAS;
  INDICE = &SURPAS;
  LTEMPS = LTEMPS ET (PROG (TAB1.'TEMPS'. (INDICE - 1)));
  LTEMPE = LTEMPE ET (PROG (EXTR TAB1.'TEMPERATURES'. (INDICE - 1) T (SUR1 POIN PROC (0.08 0.))));
FIN SURPAS;
EVTEMPE = EVOL BLEU MANU LTEMPS LTEMPE;
THET1 = EXTR LTEMPE NBPAS;
THET2 = 36.6;
ERG =100 * (ABS ((THET2 - THET1) / THET2));
* Trace facultatif de la repartition
* de temperature a t = 32 s
SI (NEG GRAPH 'N');
  TITR 'TRAN8 : Temperature a t = 32 s';
  CHPO3 = PECHE TAB1 'TEMPERATURES' TAB1. 'TEMPS' . (NBPAS - 1);
  TRAC SUR1 CHPO3;
   TITR 'Evolution de la temperature en  fonction du temps : ';
  DESS EVTEMPE ;
FINSI;
* -------- Test Reactions dans solution -------
IREAC1 = 'EXIS' TAB1 'REACTIONS_THERMIQUES' ;
* -------- affichage des resultats --------
MESS ' RESULTATS ';
MESS ' --------- ';
SAUT 1 LIGN;
MESS 'Temperature theorique :' THET2' C';
MESS 'Temperature calculee  :' THET1' C';
MESS '    Soit un ecart de : ' ERG '%';
SAUT 1 LIGN;
* ------- code fonctionnement -------------
SI ((ERG <EG 5) 'ET' IREAC1);
   ERRE 0;
SINON;
   'SI' ('NON' IREAC1) ;
     SAUT 1 LIGN;
     'MESS' '*****  ERREUR : il manque les reactions thermiques ! ' ;
     SAUT 1 LIGN;
   'FINS' ;
   ERRE 5 ;
FINSI;
TEMPS;
FIN;
```
