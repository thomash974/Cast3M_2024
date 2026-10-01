# Cas tests dgibi en texte compacté, partie 1/2

Cadres de commentaires et alignements supprimés (le code est inchangé). Un cas par section au minimum, complété pour couvrir les opérateurs.

## @solvmec_03 [(sans section)]
```
* Test du mini solveur mecanique (procedure @SOLVMEC)
* - eprouvette entaillee en traction
* - comportement visco-elastique
* - calcul en petits deplacements
* On compare les resultats a ceux de la procedure PASAPAS
* Options generales
OPTI 'DIME' 2 'ELEM' 'QUA4' 'MODE' 'PLAN' 'CONT' 'ECHO' 0 ;
* Geometrie : barre rectangulaire l x h avec une
* entaille circulaire de largeur le et profondeur pe
l = 1.0 ;
h = 0.1 ;
le = 0.1 * l ;
pe = 0.1 * h ;
* Maillage
ne = 51 ;
* barre rectangulaire
p0 = 0. 0. ;
p1 = l 0. ;
lb = DROI ne p0 p1 ;
mai = lb TRAN 3 (0. h) ;
ld = mai COTE 2 ;
lh = mai COTE 3 ;
lg = mai COTE 4 ;
* deplacement des noeuds pour l'entaille circulaire
p2 = ((l - le) / 2.) h ;
p3 = ((l + le) / 2.) h ;
re = (pe / 2.) + (le * le / (8. * pe)) ;
p4 = (l / 2.) (h - pe + re) ;
xh yh = COOR lh ;
pmil = xh POIN 'COMPRIS' (COOR 1 p2) (COOR 1 p3) ;
DEPL pmil 'PROJ' 'CYLI' (0. 1.) 'CERC' p4 p2 ;
cmai = CONT mai ;
* TRAC mai 'TITR' 'Maillage' ;
* Modele et caracteristiques materiau
mo = MODE mai 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' 'FLUAGE' 'NORTON' ;
ma = MATE mo 'YOUN' 1.E9 'NU' 0.3 'SMAX' 0. 'AF1' 3.E-13 'AF2' 1.2 'AF3' 1. ;
* Blocages
clg = BLOQ 'UX' lg ;
clb = BLOQ 'UY' lb ;
cld = BLOQ 'UX' ld ;
cl = clg ET clb ET cld ;
* Chargement : deplacement impose (essai de relaxation)
uimp = 5.E-3 ;
fuim = DEPI cld uimp ;
ev1 = EVOL 'MANU' 'Temps' (PROG 0. 100. 1000.) 'Coef' (PROG 0. 1. 1.) ;
cha = CHAR 'DIMP' fuim ev1 ;
* Resolutions avec PASAPAS et @SOLVMEC
tab1 = TABL ;
tab1 . 'MODELE' = mo ;
tab1 . 'CARACTERISTIQUES' = ma ;
tab1 . 'BLOCAGES_MECANIQUES' = cl ;
tab1 . 'CHARGEMENT' = cha ;
tab1 . 'TEMPS_CALCULES' = PROG 10. 'PAS' 10. 1000. ;
tab2 = COPI tab1 ;
TEMP 'ZERO' ;
PASAPAS tab1 ;
tpp = TEMP 'HORL' ;
TEMP 'ZERO' ;
@SOLVMEC tab2 ;
tms = TEMP 'HORL' ;
* Performances
MESS ;
MESS 'Duree d''execution (ms)' ;
MESS '----------------------' ;
MESS 'PASAPAS  :' ' ' tpp ;
MESS '@SOLVMEC :' ' ' tms ;
MESS ;
* Post traitement : courbes F (resultante des reactions a gauche) vs Temps
* EPSE max (def. plas. eq. max) vs Temps
n1 = DIME (tab2 . 'TEMPS') ;
ltp = PROG ;
lr1 = PROG ;
lr2 = PROG ;
le1 = PROG ;
le2 = PROG ;
lerr = PROG ;
lere = PROG ;
REPE b1 n1 ;
* temps
  ltp = ltp ET (tab1 . 'TEMPS' . (&b1 - 1)) ;
* effort de reaction
  r1 = tab1 . 'REACTIONS' . (&b1 - 1) ;
  r2 = tab2 . 'REACTIONS' . (&b1 - 1) ;
  SI (EGA &b1 1) ;
    rr1 = 0. ;
    rr2 = 0. ;
  SINON ;
    rr1 = -1. * (@TOTAL r1 lg 'FX') ;
    rr2 = -1. * (@TOTAL r2 lg 'FX') ;
    lerr = lerr ET (ABS ((rr1 - rr2) / rr1)) ;
  FINSI ;
  lr1 = lr1 ET rr1 ;
  lr2 = lr2 ET rr2 ;
* deformation plastique equivalente
  vi1 = tab1 . 'VARIABLES_INTERNES' . (&b1 - 1) ;
  vi2 = tab2 . 'VARIABLES_INTERNES' . (&b1 - 1) ;
  epqmax1 = MAXI (EXCO 'EPSE' vi1) ;
  epqmax2 = MAXI (EXCO 'EPSE' vi2) ;
  le1 = le1 ET epqmax1 ;
  le2 = le2 ET epqmax2 ;
  SI (epqmax1 > 1.E-10) ;
    lere = lere ET (ABS ((epqmax1 - epqmax2) / epqmax1)) ;
  FINSI ;
FIN b1 ;
* ecarts relatifs max
err = MAXI 'ABS' lerr ;
ere = MAXI 'ABS' lere ;
MESS ;
MESS 'Ecarts relatifs max' ;
MESS '-------------------' ;
MESS 'Defo. plast. eq. max :' ' ' ere ;
MESS 'Reaction             :' ' ' err ;
MESS ;
* trace des courbes
tleg = TABL ;
tleg . 'TITRE' = TABL ;
tleg . 'TITRE' . 1 = CHAI 'Pasapas' ;
tleg . 'TITRE' . 2 = CHAI 'Mini solveur' ;
tleg . 2 = MOT 'MARQ ROND NOLI' ;
eve1 = EVOL 'MANU' 'Temps' ltp 'EPSE max' le1 ;
eve2 = EVOL 'ROUG' 'MANU' 'Temps' ltp 'EPSE max' le2 ;
* DESS (eve1 ET eve2) 'TITR' 'EPSE max vs Temps' 'LEGE' tleg 'NO' ;
evr1 = EVOL 'MANU' 'Temps' ltp 'Reaction' lr1 ;
evr2 = EVOL 'ROUG' 'MANU' 'Temps' ltp 'Reaction' lr2 ;
* DESS (evr1 ET evr2) 'TITR' 'Force vs Temps' 'LEGE' tleg 'NE' ;
* Test et erreur si ecart trop important
SI ((ere > 1.E-5) OU (err > 1.E-4)) ;
  ERRE 'Ecart trop important entre les resultats de @SOLVMEC et de PASAPAS' ;
FINSI ;
FIN ;
```

## bgmo_bcn [(sans section)]
```
* TESTING FILE FOR THE OPERATOR BGMO EVALUATING
* THE FUNCIONS INVOLVED IN THE BRUNO GERARD MODEL
GRAPH='N';
nn1 = 100;
tkk = PROG;
cokk = PROG;
t=0.;
repeter kk1 nn1;
  con1 = BGMO 'COND' t 20. .8e-3;
  tkk = tkk INSE &kk1 t;
  cokk = cokk INSE &kk1 con1;
  t= t + (.5 / 50.);
fin kk1;
num1 = EXTR cokk 50 ;
flag1 = ABS(num1 - 1.6577);
evol1 = EVOL MANU 'temps' tkk 'COND' cokk;
SI (NEG GRAPH 'N');
dess evol1;
FINSI;
nn1 = 100;
tkk = PROG;
cokk = PROG;
t=0.;
repeter kk1 nn1;
  con1 = BGMO 'DCON' t 20. .8e-3;
  tkk = tkk INSE &kk1 t;
  cokk = cokk INSE &kk1 con1;
  t= t + (.5 / 50.);
fin kk1;
num1 = EXTR cokk 50 ;
flag2 = ABS(num1 + 2.4476);
evol1 = EVOL MANU 'temps' tkk 'COND' cokk;
SI (NEG GRAPH 'N');
dess evol1;
FINSI;
nn1 = 100;
tkk = PROG;
cokk = PROG;
t=0.;
repeter kk1 nn1;
  con1 = BGMO 'CAPA' t 20. 700.;
  tkk = tkk INSE &kk1 t;
  cokk = cokk INSE &kk1 con1;
  t= t + (.5 / 50.);
fin kk1;
num1 = EXTR cokk 50 ;
flag3 = ABS(num1 - 0.33457);
evol1 = EVOL MANU 'temps' tkk 'COND' cokk;
SI (NEG GRAPH 'N');
dess evol1;
FINSI;
nn1 = 100;
tkk = PROG;
cokk = PROG;
t=0.;
repeter kk1 nn1;
  con1 = BGMO 'DCAP' t 20. 700.;
  tkk = tkk INSE &kk1 t;
  cokk = cokk INSE &kk1 con1;
  t= t + (.5 / 50.);
fin kk1;
num1 = EXTR cokk 50 ;
flag4 = ABS(num1 + 0.65976);
evol1 = EVOL MANU 'temps' tkk 'COND' cokk;
SI (NEG GRAPH 'N');
dess evol1;
FINSI;
flag5 = (flag1+flag2+flag3+flag4);
SI (flag5 < 1.e-4);
ERRE 0;
SINON;
ERRE 5;
FINSI;
FIN;
```

## bobiproc [(sans section)]
```
DEBPROC INDUCTAN BOBINE*'MAILLAGE' TBIOT*'TABLE';
* CALCUL DE LA MUTUELLE INDUCTANCE ENTRE UN INDUCTEUR
* DECRIT ANALYTIQUEMENT PAR LA TABLE TBIOT ET UN
* INDUIT DE TYPE MAILLAGE.
* TBIOT.'SOUSTYPE' = INDUCTEUR
* TBIOT.1 = TABLE DECRIVANT L'INDUCTEUR 1
* TBIOT.N = TABLE DECRIVANT L'INDUCTEUR N
* POUR L'INDUCTEUR 1 PAR EXEMPLE :
* TBIOT.1.'SOUSTYPE' = INDUCTEUR1
* TBIOT.1.'GEOTYPE' = 'BARR' OU 'ARC' OU 'CIRC'
* CAS 'ARC' OU 'CIRC':
* TBIOT.1.'POINT1' = CENTRE DE LA SPIRE
* TBIOT.1.'POINT2' = PREMIER POINT DEFINISSANT LA SPIRE
* TBIOT.1.'POINT3' = DEUXIEME POINT DEFINISSANT LA SPIRE
* TBIOT.1.'FLOT1' = RAYON INTERIEUR DE LA BOBINE
* TBIOT.1.'FLOT2' = RAYON EXTERIEUR DE LA BOBINE
* TBIOT.1.'FLOT3' = HAUTEUR DE LA BOBINE
* CAS 'BARR':
* TBIOT.1.'POINT1' = EXTREMITE 1 DE LA BARRE
* TBIOT.1.'POINT2' = EXTREMITE 2 DE LA BARRE
* POINT1 ET POINT2 DEFINISSENT L'AXE X LOCAL
* TBIOT.1.'POINT3' = POINT DEFINISSANT L'AXE Y LOCAL
* TBIOT.1.'FLOT1' = DY DE LA BOBINE
* TBIOT.1.'FLOT2' = DZ DE LA BOBINE
* TBIOT.1.'SECTION' = 'RECTANGLE' OU 'TRAPEZE'
* DANS LE CAS 'TRAPEZE', ON A DE PLUS :
* TBIOT.1.'PENTEBASSE' = PENTE BASSE
* TBIOT.1.'PENTEHAUTE' = PENTEHAUTE
* SYNTAXE : MUTU = INDUCTAN BOBINE TBIOT;
* MAILLAGE DE POINTS CONSTITUE DES
* BARYCENTRES DES ELEMENTS DE 'BOBINE'
  NE = NBEL BOBINE;
  IEL = 1;
  GEO1 = BOBINE ELEM IEL;
  P0 = BARY GEO1;
  GEO2 = P0 ET P0;
  GEO2 = GEO2 ELEM POI1 1;
  NEM1=NE-1;
  REPETER BOUC NEM1;
    IEL = IEL + 1;
    GEO1 = BOBINE ELEM IEL;
    PC = BARY GEO1;
    GEO3 = PC ET PC;
    GEO3 = GEO3 ELEM POI1 1;
    GEO2 = GEO2 ET GEO3;
  FIN BOUC;
  ELIM 0.01 GEO2;
* CALCUL DU POTENTIEL VECTEUR DU A CHAQUE
* INDUCTEUR ET DU POTENTIEL VECTEUR TOTAL
  PI = 3.14159265;
  MU0 = 4.*PI*1.E-7;
* INITIALISATION DU POTENTIEL VECTEUR TOTAL
  ATOT = MANU 'CHPO' GEO2 3 AX 0. AY 0. AZ 0.;
* BOUCLE SUR LES INDUCTEURS
  IND = 0;
  NIND = DIME TBIOT;
  NIND = NIND-1;
  REPETER BOUC NIND;
    IND = IND+1;
    TYPI = TBIOT.IND.'GEOTYPE';
    Q1 = TBIOT.IND.'POINT1';
    Q2 = TBIOT.IND.'POINT2';
    Q3 = TBIOT.IND.'POINT3';
* CAS DES CERCLES ET DES ARCS
    SI ((EGA TYPI 'CIRC') OU (EGA TYPI 'ARC'));
      RI = TBIOT.IND.'FLOT1';
      RE = TBIOT.IND.'FLOT2';
      H = TBIOT.IND.'FLOT3';
      S = (RE-RI)*H;
      DNS = 1./S;
      SECT = TBIOT.IND.'SECTION';
* SECTION RECTANGULAIRE
      SI (EGA SECT 'RECTANGLE');
        SI (EGA TYPI 'CIRC');
          AIND = BIOT 'POTE' GEO2 'CERC' Q1 Q2 Q3
                 RI RE H DNS MU0;
        FINSI;
        SI (EGA TYPI 'ARC');
          AIND = BIOT 'POTE' GEO2 'ARC' Q1 Q2 Q3
                 RI RE H DNS MU0;
        FINSI;
      FINSI;
* SECTION TRAPEZOIDALE
      SI (EGA SECT 'TRAPEZE');
        PENT1 = TBIOT.IND.'PENTEBASSE';
        PENT2 = TBIOT.IND.'PENTEHAUTE';
        SI (EGA TYPI 'CIRC');
          AIND = BIOT 'POTE' GEO2 'CERC' Q1 Q2 Q3
                 RI RE H 'TRAP' PENT1 PENT2 DNS MU0;
        FINSI;
        SI (EGA TYPI 'ARC');
          AIND = BIOT 'POTE' GEO2 'ARC' Q1 Q2 Q3
                 RI RE H 'TRAP' PENT1 PENT2 DNS MU0;
        FINSI;
      FINSI;
* CAS DES BARRES
    SINON;
      DY = TBIOT.IND.'FLOT1';
      DZ = TBIOT.IND.'FLOT2';
      S = DY*DZ;
      DNS = 1./S;
      SECT = TBIOT.IND.'SECTION';
* SECTION RECTANGULAIRE;
      SI (EGA SECT 'RECTANGLE');
        AIND = BIOT 'POTE' GEO2 'BARR' Q1 Q2 Q3 DY DZ
               DNS MU0;
      FINSI;
* SECTION TRAPEZOIDALE
      SI (EGA SECT 'TRAPEZE');
        PENT1 = TBIOT.IND.'PENTEBASSE';
        PENT2 = TBIOT.IND.'PENTEHAUTE';
        AIND = BIOT 'POTE' GEO2 'BARR' Q1 Q2 Q3
               DY DZ 'TRAP' PENT1 PENT2 DNS MU0;
      FINSI;
    FINSI;
    ATOT = ATOT + AIND;
  FIN BOUC;
* CALCUL DES VOLUMES ELEMENTAIRES
  LVOL = PROG 0.;
  IE = 0;
  REPETER BOUC NE;
    IE = IE+1;
    GEO1 = BOBINE ELEM IE;
    MOD1 = MODE GEO1 MECANIQUE ELASTIQUE;
    MAT1 = MATE MOD1 'RHO' 1. 'YOUN' 1. 'NU' 1.;
    VMAS = MASSE MOD1 MAT1;
    CUNI = MANU 'CHPO' GEO1 1 UZ 1.;
    VOEL = VMAS*CUNI;
    VOLU = @TOTAL VOEL GEO1 FZ;
    LVOL = LVOL ET (PROG VOLU);
  FIN BOUC;
  NEP1=NE+1;
  LENT = LECT 2 PAS 1 NEP1;
  LVOL = EXTR LVOL (LENT);
  CVOL = MANU 'CHPO' GEO2 1 SCAL LVOL;
* CALCUL DE LA NORME DU
* POTENTIEL VECTEUR
  LCOM = MOTS AX AY AZ;
  ANOR = PSCA AIND AIND LCOM LCOM;
  ANOR = ANOR**0.5;
* PONDERATION PAR LE VOLUME
* ELEMENTAIRE : CALCUL DE LA MUTUELLE
  LCOM = MOTS SCAL;
  MUTUELLE=PSCA ANOR CVOL LCOM LCOM;
  MUTUELLE = @TOTAL MUTUELLE GEO2 SCAL;
  MUTUELLE = MUTUELLE/S;
FINPROC MUTUELLE;
OPTI DIME 3 ELEM CUB8 MODE TRIDIM COUL ROUG ;
DENS 0.1;
O0 = 0. 0. 0. ;
O1 = 0. 0. 1. ;
O2 = 1. 0. 0. ;
O3 = 0. 1. 0. ;
P1 = 0.9 0. -0.1;
P2 = 1.1 0. -0.1;
P3 = 1.1 0. 0.1;
P4 = 0.9 0. 0.1 ;
N1 = 3;
N2 = 3;
NC = 16;
L1 = P1 D N1 P2 ;
L2 = P2 D N2 P3 ;
L3 = P3 D N1 P4 ;
L4 = P4 D N2 P1 ;
S1 = L1 L2 L3 L4 DALL PLAN;
BOBINE = VOLU S1 ROTA NC 360 O0 O1;
ELIM 0.01 BOBINE;
OEIL = 1000. 1000. 1000.;
* TRAC OEIL BOBINE CACHE;
* L'INDUCTEUR EST UNE BOBINE CIRCULAIRE :
* ON MODELISE UN SEUL INDUCTEUR
TBIOT = TABLE 'INDUCTEUR';
TBIOT . 1 = TABLE 'INDUCTEUR1';
TBIOT . 1 . 'GEOTYPE' = 'CIRC';
TBIOT . 1 . 'POINT1' = O0;
TBIOT . 1 . 'POINT2' = O2;
TBIOT . 1 . 'POINT3' = O3;
TBIOT . 1 . 'FLOT1' = 0.9;
TBIOT . 1 . 'FLOT2' = 1.1;
TBIOT . 1 . 'FLOT3' = 0.2;
TBIOT . 1 . 'SECTION' = 'RECTANGLE';
SELF = INDUCTAN BOBINE TBIOT;
LIST SELF;
SOLREF = 3.15e-6;
ERREL = ABS(SOLREF-SELF)/SOLREF;
LIST ERREL;
SI (ERREL > 0.02);
   ERREUR 5;
FINSI;
FIN;
```

## boobj [(sans section)]
```
 SAUT PAGE ;
* Utilisation des opérateurs CHI1 et CHI2
* test avec échange
* Ce test est identique à bo2.dgibi mais les entrées sont des OBJETS
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
OPTION DIME 2 ;
* DEFINITION DU MAILLAGE
n1 = 1 ;
* n2 = 160 ;
* n2 = 80 ;
n2 = 1 ;
* POINT SERVANT A DEFINIR LE CONTOUR
a = 0.0 0.0 ;
b = 1. 0.0 ;
c = 1. 8. ;
d = 0. 8. ;
option elem qua4 ;
ab = a droit n1 b ;
bc = b droit n2 c ;
cd = c droit n1 d ;
da = d droit n2 a ;
* DEFINITION DU MAILLAGE
GP = AB BC CD DA DALL 'PLAN' ;
ELIM 0.001 GP ;
AB= CHANG POI1 AB ;
G1= CHANG POI1 GP ;
G0= DIFF G1 AB ;
TABDON=OBJET DONCHI1 ;
TABDON%GIDEN (LECT 1 22 5 103 50);
 COMP1=OBJET LINVCOMP ;
 COMP1%COM_IDEN 162 ;
 COMP1%COM_NOM X162 ;
 COMP1%COM_CHAR -1 ;
TABDON%GNVCOMP 1 COMP1 ;
   TABESP1= OBJET LIESPECE ;
    TABESP1%ESP_IDEN 163 ;
    TABESP1%ESP_LOGK 7. ;
    TABESP1%ESP_ITYP 2 ;
    TABESP1%ESP_COMP (LECT 162 50) ;
    TABESP1%ESP_STOE (PROG 1. 1.) ;
   TABESP2= OBJET LIESPECE;
    TABESP2%ESP_IDEN 164 ;
    TABESP2%ESP_LOGK 1.5 ;
    TABESP2%ESP_ITYP 2 ;
    TABESP2%ESP_COMP ( LECT 162 5) ;
    TABESP2%ESP_STOE ( PROG 1. 1.) ;
* TABDON.NVESP= TABLE ;
 TABDON%GNVESP 1 TABESP1 ;
 TABDON%GNVESP 2 TABESP2 ;
 TABDON%GECHANGE ( LECT 162) ;
 TB1=CHI1 TABDON COMP ('CHAINE' DIVERS '/COMPOM')
   LOGK ('CHAINE' DIVERS '/COMPOM') ;
* Table de données de CHI2
* TBPAR2= TABLE ;
* TBPAR2.'SOUSTYPE'='DONNEES_CHIMIQUES' ;
 TBPAR2= OBJET DONCHI2 ;
 TBPAR2%GLOGC (MANU CHPO G1 6 X001 -6. X022 -6. X005 -6.
               X050 -6. X162 -2. X103 -6.) ;
  TOTCA= MANU CHPO G1 1 X001 1.D-15 ;
  TOTLI1= MANU CHPO G1 1 X022 1.248D-9 ;
  TOTLI2= MANU CHPO AB 1 X022 (1.D-3 - 1.248D-9) ;
  TOTLI = TOTLI1 + TOTLI2 ;
  TOTNA1= MANU CHPO G1 1 X005 1.100131015D-1 ;
  TOTNA2= MANU CHPO AB 1 X005 (1.D-1 - 1.100131015D-1) ;
  TOTNA= TOTNA1 + TOTNA2 ;
  TOTCL1= MANU CHPO G1 1 X103 1.D-1 ;
  TOTCL2= MANU CHPO AB 1 X103 (1.02D-1 - 1.D-1) ;
   TOTCL= TOTCL1+ TOTCL2 ;
  TOTSF1= MANU CHPO G1 1 X162 1.D-2 ;
  TOTSF2= MANU CHPO AB 1 X162 (1.D-15 - 1.D-2);
  TOTSF= TOTSF1 + TOTSF2 ;
  TOTH1= MANU CHPO G1 1 X050 -1.3012D-5 ;
  TOTH2= MANU CHPO AB 1 X050 (1.0001D-3 + 1.3012D-5) ;
   TOTH = TOTH1 + TOTH2 ;
 TBPAR2%GTOT ( TOTCA + TOTLI + TOTNA + TOTCL + TOTSF +TOTH) ;
 TBPAR2%GFIONI ( MANU CHPO G1 1 SCAL 0.001) ;
 TBPARM= OBJET PARMCHI2 ;
 TBPARM%GITMAX 80;
 TBPARM%GEPS 1.D-8 ;
 TBPARM%GNFI 4 ;
 TBPARM%GITERSOL 15 ;
 TBPARM%GSORTIE ( MOTS 'FION' 'TYP5' 'SURF') ;
 TB3= CHI2 TB1 TBPARM TBPAR2 ;
* controle des résultats
 FIONTE1=MANU CHPO G1 1 SCAL 1.00030E-01 'NATURE' DISCRET ;
 FIONTE2=MANU CHPO AB 1 SCAL (1.02000E-01 - 1.00030E-01)
 'NATURE' DISCRET ;
 FIONTES= FIONTE1 + FIONTE2 ;
 VERR1= ( ABS ( FIONTES - TB3.FION )) MASQUE SUPERIEUR 5.D-6 SOMME ;
 SURFTE1= MANU CHPO G0 2 W006 9.98262E-03 W010 1.73813E-05
   'NATURE' DISCRET ;
 SURFTE2= MANU CHPO AB 2 W006 3.15844E-19 W010 9.98885E-16
 'NATURE' DISCRET ;
 SURFTES= SURFTE1+SURFTE2 ;
 SURFD=SURFTES / 50. ;
 VERR2= ( ABS ( SURFTES - TB3.SURF )) MASQUE SUPERIEUR SURFD SOMME ;
 TY5TE1= MANU CHPO G0 1 W011 3.12037E-20 'NATURE' DISCRET ;
 TY5TE2= MANU CHPO AB 1 W011 9.43503E-33 'NATURE' DISCRET ;
 TY5TES= TY5TE1+TY5TE2 ;
 TY5D= TY5TES/ 50. ;
 VERR3= ( ABS ( TY5TES - TB3.TYP5 )) MASQUE SUPERIEUR TY5D SOMME ;
 VERR= VERR1+VERR2+VERR3 ;
 SI (VERR EGA 0 ) ;
  ERRE 0 ;
 SINO ;
  ERRE 5 ;
 FINSI ;
FIN ;
```

## calcul_inductance_ppipede [(sans section)]
```
OPTI DIME 2 ELEM TRI3;
* example pour MPMA + JPMA
* calcul d'inductance d'un parallélépipède dans CAST3M
* et comparaison avec la formule analytique
* l'intérêt de MPMA + JPMA : on peut calculer l'énergie magnétique
* (et donc l'inductance) associée à une densité de courant J(x,y) quelconque
* IMPORTANT: J(x,y) est donné en 2D (avec une épaisseur selon Z)
* mais le potentiel magnétique est calculé en 3D
OPTI 'ECHO' 0;
* afficher ou pas
AFFICH = FAUX;
* longueur, largeur, épaisseur
LX = 100.E-3;
LY = 5.E-3;
EPAI = 12.E-3;
CT0 = POIN 0. 0.;
N1 = 6;
TAILLE1 = LY/N1;
* maillage
DENS TAILLE1;
* on prend la densité de courant pour que le courant soit égal à 1 A
JA = (1./LY)/EPAI;
X1 = (-1.)*LX/2;
Y1 = (-1.)*LY/2;
X2 = (-1.)*LX/2;
Y2 = LY/2;
X3 = LX/2;
Y3 = LY/2;
X4 = LX/2;
Y4 = (-1.)*LY/2;
P1 = POIN X1 Y1;
P2 = POIN X2 Y2;
P3 = POIN X3 Y3;
P4 = POIN X4 Y4;
LD1 = D P1 P2;
LD2 = D P2 P3;
LD3 = D P3 P4;
LD4 = D P4 P1;
CT = LD1 ET LD2 ET LD3 ET LD4;
SU1 = SURF CT;
ELIM SU1 1.E-7;
* il faut un modèle
MTB = 'MODE' SU1 'THERMIQUE' 'ISOTROPE';
* remarque: ici on fait le plus simple, on impose une densité de courant;
* il est également possible de résoudre un problème "thermique",
* afin de trouver une densité de courant inconnue,
* et ensuite on peut calculer le potentiel vecteur, l'énergie magnétique, etc.
* dans ce cas on le ferait de mainère suivante :
* SIGMA = 1;
* MAT1 = MATE MTB 'K' SIGMA;
* COND1 = COND MAT1 MTB;
* V0 = 0;
* V1 = 1;
* B0 = BLOQ 'T' LD3;
* CL0 = DEPI B0 V0;
* CL1 = FLUX MTB LD1 JA;
* V = RESO (COND1 ET B0) (CL0 ET CL1);
* J = GRAD V MTB;
* J = J * -1.;
* JX = EXCO 'T,X' J;
* JY = EXCO 'T,Y' J;
* JX = CHAN 'COMP' 'JX' JX;
* JY = CHAN 'COMP' 'JY' JY;
* J = JX ET JY;
* TRAC J MTB SU1 TITR 'J obtenu par RESO';
JXC = MANU 'CHPO' SU1 'JX' JA;
JYC = MANU 'CHPO' SU1 'JY' 0.;
JX = CHAN 'CHAM' JXC SU1;
JY = CHAN 'CHAM' JYC SU1;
* il faut une composante 'JX' et une autre 'JY'
JX = CHAN 'COMP' 'JX' JX;
JY = CHAN 'COMP' 'JY' JY;
J = JX ET JY;
SI AFFICH;
TRAC J MTB SU1 TITR 'DENSITE DE COURANT';
FINSI;
* on calcule la martice M (une seule fois)
M = MPMA MTB EPAI;
* et ensuite on calcule A
* si J change, on peut recalculer A avec la même matrice M
A = JPMA J MTB M;
SI AFFICH;
TRAC A MTB SU1 TITR 'POT MAG VECT MOYENNE SUR L''EPAISSEUR';
FINSI;
* on a le potentiel vecteur, on peut calculer l'énergie magnétique
AX = EXCO 'AX' A;
AY = EXCO 'AY' A;
CJX = CHAN 'CHPO' MTB JX;
CAX = CHAN 'CHPO' MTB AX;
CJX = CHAN 'COMP' 'SCAL' CJX;
CAX = CHAN 'COMP' 'SCAL' CAX;
WX = CAX * CJX ;
CJY = CHAN 'CHPO' MTB JY;
CAY = CHAN 'CHPO' MTB AY;
CJY = CHAN 'COMP' 'SCAL' CJY;
CAY = CHAN 'COMP' 'SCAL' CAY;
WY = CAY * CJY ;
CW = WX + WY;
W = CHAN 'CHAM' SU1 CW;
* intégrale de la densité d'énergie magnétique (x2)
L1 = INTG W MTB;
* on multiplie par l'épaisseur car l'intégration est faite en 3D
L = (L1*EPAI);
MOT1 = CHAI 'INDUCTANCE TROUVEE PAR LES ELEMENTS FINIS:' L;
* on applique la formule analytique
* Rosa, Grover - FORMULAS AND TABLES FOR THE CALCULATION OF
* MUTUAL AND SELF-INDUCTANCE
* Bulletin of Bureau of Standards vol 8 no 1, p.153
AJOUT1 = 0.5+(0.2235*((LY+EPAI)/LX));
LREF = ((2*LX)*100)*(LOG((2*LX)/(LY+EPAI))+AJOUT1)*(1.E-9);
MOT2 = CHAI 'INDUCTANCE TROUVEE PAR LA FORMULE ANALYTIQUE:' LREF;
MESS MOT1;
MESS MOT2;
* test de validite
 EC = (L - LREF) ABS;
SI (EC > 1d-10); MESS 'resultat incorrect' ' ' ec; erreur 5; finsi;
fin;
```

## colline [(sans section)]
```
* ECOULEMENT AUTOUR D'UNE COLLINE
* G. TURBELIN 14/12/99
opti dime 2 elem qua8;
COMPLET=FAUX;
GRAPH='N' ;
Si complet ;
iitma=20000 ;
sinon;
iitma=5 ;
finsi ;
* ------------------ PROCEDURE FILTREKE ---------------------------------
 DEBP FILTREKE ;
 ARGU RX*TABLE ;
* Filtre sur K et Epsilon
* - Echelle de vitesse (K**0.5) inférieure à une fraction (alfk)
* de Uref (vitesse caractéristique) (alfk=1 pour l'instant)
* Uref=max(UN,U0)
* - K > K0
* - Epsilon tel que l'echelle de longueur reste inférieure
* à (L0/a) où L0 = diamètre enceinte et a=f(Re)
* => Nut < Uref*L0/a
 rv=rx.'EQEX' ;
 rvp=rv.'PRESSION' ;
 iarg=rx.'IARG' ;
 NASTOK = rv.'NAVISTOK' ;
 si( non ( ega iarg 4)) ;
 mess 'Procedure FILTREKE : nombre d arguments incorrect ' iarg ;
 quitter FILTREKE ;
 finsi ;
 si ( ega ('TYPE' rx.'ARG1') 'MOT     ') ;
 U1=rv.'INCO'.(rx.'ARG1') ;
 sinon ;
 si ( ega ('TYPE' (rx.'ARG1')) 'FLOTTANT') ;
 U1=rx.'ARG1' ;
 sinon ;
 mess 'Procedure FILTREKE : type argument 1 invalide ' ;
 quitter FILTREKE ;
 finsi ;
 finsi ;
 si ( ega ('TYPE' rx.'ARG2') 'MOT     ') ;
 L0=rv.'INCO'.(rx.'ARG2') ;
 sinon ;
 si ( ega ('TYPE' (rx.'ARG2')) 'FLOTTANT') ;
 L0=rx.'ARG2' ;
 sinon ;
 mess 'Procedure FILTREKE : type argument 2 invalide ' ;
 quitter FILTREKE ;
 finsi ;
 finsi ;
 si ( ega ('TYPE' rx.'ARG3') 'MOT     ') ;
 NU=rv.'INCO'.(rx.'ARG3') ;
 sinon ;
 si ( ega ('TYPE' (rx.'ARG3')) 'FLOTTANT') ;
 NU=rx.'ARG3' ;
 sinon ;
 mess 'Procedure FILTREKE : type argument 3 invalide ' ;
 quitter FILTREKE ;
 finsi ;
 finsi ;
 si ( ega ('TYPE' rx.'ARG4') 'MOT     ') ;
 UN=rv.'INCO'.(rx.'ARG4') ;
 sinon ;
 si ( ega ('TYPE' (rx.'ARG4')) 'CHPOINT') ;
 UN=rx.'ARG4' ;
 sinon ;
 mess 'Procedure FILTREKE : type argument 4 invalide ' ;
 quitter FILTREKE ;
 finsi ;
 finsi ;
 nic=dime (rx.'LISTINCO') ;
 si( non ( ega nic 2)) ;
 mess 'Procedure FILTREKE : nombre d inconnues incorrect ' nic ;
 quitter FILTREKE ;
 finsi ;
 nomi1=extr 1 (rx.'LISTINCO');
 nomi2=extr 2 (rx.'LISTINCO');
 nom1= mot (text (chai nomi1)) ;
 nom2= mot (text (chai nomi2)) ;
 en=rv.'INCO'.nom2 ;
 kn=rv.'INCO'.nom1 ;
 Rec=100.;
 k0 = 1.e-10 ;
 cnu=0.09;
 lcu=extr un 'COMP' ;
 mdu=un lcu 'PSCA' un lcu;
 mdu=mdu ** 0.5 ;
 Re=kops (kops (kops mdu '*' L0) '/' nu) '+' (Rec / 10.) ;
 a= exp (kops Rec '/' Re ) ;
 mdu = kops mdu '|<' u1 ;
 mdu2= kops mdu '*' mdu ;
 kn=kops kn '|<' k0 ;
 kn=kops kn '>|' mdu2 ;
 E0= kops (kops kn '**' 1.5) '*' (a / L0) ;
 en=kops en '|<' E0 ;
 rv.'INCO'.nom2=en ;
 rv.'INCO'.nom1=kn ;
 as2 ama1 = 'KOPS' 'MATRIK' ;
* RESPRO as2 ama1 ;
 FINPROC ;
* ------------------------------- FIN PROCEDURE FILTREKE ----------------
* CONSTRUCTION DU MAILLAGE
* Définition des longueurs
* hauteur du domaine (mm)
Hdo = 170.;
* hauteur de la colline (mm)
H_ref = 28.;
* abscisses caractéristiques (mm)
Xmind = -326.; Xmaxd = 500.; X1d=0.;
X2d=9.; X3d= 14.; X4d= 20.;
X5d=30.; X6d=40.; X7d=54.;
* abscisses caractéristiques adim
Xmin = Xmind/H_ref ; Xmax = Xmaxd/H_ref; X1=X1d/H_ref;
X2=X2d/H_ref; X3= X3d/H_ref; X4=X4d/H_ref;
X5=X5d/H_ref; X6=X6d/H_ref; X7=X7d/H_ref;
Hd = Hdo/H_ref ;
* Nb de maille
* Nombre de maille entre x=9 et x=14(colline)
Nbcol = 1;
* Nb de maille entre x=-326 et x =-54 (bas1 & haut4)
Nbbas1 = 25;
* Nb de maille entre x=54 et x =500 (bas2 & haut1)
Nbbas2 = 40;
* Nb de maille entre y=0 et x =170 (sortie et entree)
Nbsort = 20 ;
* Densité
DIbasG = -1*(Xmin+X7)/Nbbas1 ;
DIbas1 = 2*DIbasG ; DFbas1 = 0.5*DIbasG;
DIbasD = (Xmax-X7)/Nbbas1 ;
DIbas2 = 0.8*DIbasD ; DFbas2 = 1.5*DIbasD;
Dsort = Hd '/' Nbsort ;
DIsort = 0.3* Dsort;
DFsort = 2.* Dsort;
* Construction de la colline a partir
* de polynomes du troisième ordre
* Cote GAUCHE
coG60 = 0. (56.39011190988/H_ref);
coG61 = 1. (+2.010520359035);
coG62 = 0. ((1.644919857549e-2)*H_ref) ;
coG63 = 0. (-2.674976141766e-5 *(H_ref**2));
lignG6 = COURBE (3*Nbcol) 'DINI'1. 'DFIN'1.
 coG60 coG61 coG62 coG63 'PARAMETRE' (-1*X7) (-1*X6) ;
coG50 = 0. (17.92461334664/H_ref);
coG51 = 1. -8.743920332081e-1 ;
coG52 = 0. ((-5.567361123058e-2)*H_ref) ;
coG53 = 0. ((-6.277731764683e-4)*(H_ref**2));
lignG5 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1.
 coG50 coG51 coG52 coG53 'PARAMETRE' (-1*X6) (-1*X5) ;
coG40 = 0. (40.46435022819/H_ref);
coG41 = 1. +1.379581654948;
coG42 = 0. ((1.945884504128e-2)*H_ref);
coG43 = 0. ((+2.070318932190e-4)*(H_ref**2));
lignG4 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1.
 coG40 coG41 coG42 coG43 'PARAMETRE' (-1*X5) (-1*X4) ;
coG30 = 0. (25.79601052357/H_ref);
coG31 = 1. -8.20669300745e-1;
coG32 = 0. ((-9.055370274339e-2)*H_ref) ;
coG33 = 0. ((-1.626510569859e-3)*(H_ref**2));
lignG3 = COURBE (1*Nbcol) 'DINI'1. 'DFIN'1.
 coG30 coG31 coG32 coG33 'PARAMETRE' (-1*X4) (-1*X3) ;
coG20 = 0. ((2.507355893131e+1)/H_ref);
coG21 = 1. -9.754803562315e-1;
coG22 = 0. ((-1.016116352781e-1)*H_ref) ;
coG23 = 0. ((-1.889794677828e-3)*(H_ref**2)) ;
lignG2 = COURBE (1*Nbcol) 'DINI'1. 'DFIN'1.
 coG20 coG21 coG22 coG23 'PARAMETRE' (-1*X3) (-1*X2) ;
coG10 = 0. (28/H_ref);
coG11 = 1. 0.;
coG12 = 0. ((6.775070969851e-3)*H_ref) ;
coG13 = 0. ((+2.124527775800e-3)*(H_ref**2)) ;
lignG1 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1.
 coG10 coG11 coG12 coG13 'PARAMETRE' (-1*X2) X1 ;
colG = lignG6 et lignG5 et lignG4 et lignG3
et lignG2 et lignG1 ;
elim colG 1e-5;
* trac colG;
* Cote Droit
coD10 = 0. (28/H_ref);
coD11 = 1. 0.;
coD12 = 0. ((6.775070969851e-3)*H_ref) ;
coD13 = 0. ((-2.124527775800e-3)*(H_ref**2));
lignD1 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1. coD10
 coD11 coD12 coD13 'PARAMETRE' X1 X2 ;
coD20 = 0. ((2.507355893131e+1)/H_ref);
coD21 = 1. 9.754803562315e-1;
coD22 = 0. ((-1.016116352781e-1)*H_ref) ;
coD23 = 0. ((1.889794677828e-3)*(H_ref**2)) ;
lignD2 = COURBE (1*Nbcol) 'DINI'1. 'DFIN'1. coD20 coD21
  coD22 coD23 'PARAMETRE' X2 X3 ;
coD30 = 0. ((25.79601052357)/H_ref);
coD31 = 1. 8.20669300745e-1;
coD32 = 0. ((-9.055370274339e-2)*H_ref) ;
coD33 = 0. ((1.626510569859e-3)*(H_ref**2)) ;
lignD3 = COURBE (1*Nbcol) 'DINI'1. 'DFIN'1. coD30 coD31
  coD32 coD33 'PARAMETRE' X3 X4 ;
coD40 = 0. (40.46435022819/H_ref);
coD41 = 1. -1.379581654948;
coD42 = 0. ((1.945884504128e-2)*H_ref);
coD43 = 0. ((-2.070318932190e-4)*(H_ref**2));
lignD4 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1. coD40
 coD41 coD42 coD43 'PARAMETRE' X4 X5 ;
coD50 = 0. (17.92461334664/H_ref);
coD51 = 1. 8.743920332081e-1;
coD52 = 0. ((-5.567361123058e-2)*H_ref) ;
coD53 = 0. ((6.277731764683e-4)*(H_ref**2));
lignD5 = COURBE (2*Nbcol) 'DINI'1. 'DFIN'1. coD50 coD51
 coD52 coD53 'PARAMETRE' X5 X6 ;
coD60 = 0. (56.39011190988/H_ref);
coD61 = 1. -2.010520359035;
coD62 = 0. ((1.644919857549e-2)*H_ref) ;
coD63 = 0. ((2.674976141766e-5)*(H_ref**2)) ;
lignD6 = COURBE (3*Nbcol) 'DINI'1. 'DFIN'1. coD60
 coD61 coD62 coD63 'PARAMETRE' X6 X7 ;
colD = lignD1 et lignD2 et lignD3 et lignD4
et lignD5 et lignD6 ;
elim colD 1e-6;
colline = colG et colD;
elim colline 1e-6;
* trac colline;opti donn 5 ;
* Construction des cotes du domaine
bas1 = (Xmin 0.) d (-1*Nbbas1) ((-1*X7) 0.) DINI DIbas1 DFIN DFbas1;
bas2 = (X7 0.) d (-1*Nbbas2) (Xmax 0.) DINI DIbas2 DFIN DFbas2;
bas = bas1 et colline et bas2;
elim bas 1e-6;
* Le maillage de la face supérieure doit correspondre avec le
* maillage de la face inférieure. Pour ne pas avoir de pb dans le
* post-traitement (définition de lignes a X=Cst) , il est utile d'avoir
* un maillage rectiligne.
* Haut Droite et Haut Gauche
hautD = (Xmax Hd) d (-1*Nbbas2) (X7 Hd) DINI DFbas2 DFIN DIbas2;
hautG = ((-1*X7) Hd) d (-1*Nbbas1) (Xmin Hd) DINI DFbas1 DFIN DIbas1;
* cote Droit
haut1D = (X7 Hd) d (3*Nbcol) (X6 Hd);
haut2D = (X6 Hd) d (2*Nbcol) (X5 Hd);
haut3D = (X5 Hd) d (2*Nbcol) (X4 Hd);
haut4D = (X4 Hd) d (1*Nbcol) (X3 Hd);
haut5D = (X3 Hd) d (1*Nbcol) (X2 Hd);
haut6D = (X2 Hd) d (2*Nbcol) (X1 Hd);
* Cote Gauche
haut6G = ((-1*X1) Hd) d (2*Nbcol) ((-1*X2) Hd);
haut5G = ((-1*X2) Hd) d (1*Nbcol) ((-1*X3) Hd);
haut4G = ((-1*X3) Hd) d (1*Nbcol) ((-1*X4) Hd);
haut3G = ((-1*X4) Hd) d (2*Nbcol) ((-1*X5) Hd);
haut2G = ((-1*X5) Hd) d (2*Nbcol) ((-1*X6) Hd);
haut1G = ((-1*X6) Hd) d (3*Nbcol) ((-1*X7) Hd);
haut = hautD et haut1D et haut2D et haut3D et haut4D et
haut5D et haut6D et haut6G et haut5G et haut4G et
haut3G et haut2G et haut1G et hautG;
elim haut 1e-6;
sortie1 =(Xmax 0.) d (-1*(Nbsort/2)) (Xmax (Hd/2))
DINI DIsort DFIN DFsort;
sortie2 =(Xmax (Hd/2)) d (-1*(Nbsort/2)) (Xmax Hd)
DINI DFsort DFIN DIsort;
sortie = (sortie1 et sortie2);
elim sortie 1e-5;
entree1 =(Xmin Hd) d (-1*(Nbsort/2)) (Xmin (Hd/2))
DINI DIsort DFIN DFsort;
entree2 =(Xmin (Hd/2)) d (-1*(Nbsort/2)) (Xmin 0.)
DINI DFsort DFIN DIsort;
entree = (entree1 et entree2);
elim entree 1e-5;
elim (bas et sortie et haut et entree ) 1e-5;
surf2 = dall bas sortie haut entree plan;
ORIENTER surf2;
* trac surf2; opti donn 5;
* Le maillage est sans dimension ...
* CALCUL DE L'ERREUR
'DEBPROC' ERR;
 'ARGUMENT' rvx*'TABLE';
  rv= rvx.'EQEX';
  DD = rv.PASDETPS.'NUPASDT' ;
  NN = DD/5;
  L0 = (DD '-' (5*NN)) 'EGA' 0;
  'SI' L0;
UN = RV.INCO.'UN' ;
UNM1 = RV.INCO.'UNM1' ;
unx= kcht (rv.'DOMAINE') scal sommet (exco 'UX' un) ;
unm1x = kcht (rv.'DOMAINE') scal sommet (exco 'UX' unm1) ;
uny= kcht (rv.'DOMAINE') scal sommet (exco 'UY' un) ;
unm1y = kcht (rv.'DOMAINE') scal sommet (exco 'UY' unm1) ;
ERRX = KOPS unx '-' unm1x ;
ERRY = KOPS uny '-' unm1y ;
ELIX = MAXI ERRX 'ABS' ;
ELIY = MAXI ERRY 'ABS' ;
ELIX = (LOG (ELIX + 1.0E-20))/(LOG 20.) ;
ELIY = (LOG (ELIY + 1.0E-20))/(LOG 20.) ;
MESSAGE 'ITER ' RV.PASDETPS.'NUPASDT' '   ERREUR LINF ' ELIX ELIY
'MAX NUT/NU = ' ((MAXI RV.INCO.'NUT')/NU) ;
RV.INCO.'UNM1'= KCHT (rv.'DOMAINE') vect sommet (RV.INCO.'UN') ;
IT = PROG RV.PASDETPS.'NUPASDT' ;
ERY = PROG ELIY ;
ERX = PROG ELIX ;
RV.INCO.'IT' = (RV.INCO.'IT') ET IT ;
RV.INCO.'ERY' = (RV.INCO.'ERY') ET ERY ;
RV.INCO.'ERX' = (RV.INCO.'ERX') ET ERX ;
'FINSI' ;
 'FINPROC' ;
* Définition des domaines
$surf = DOMA surf2 1.e-5 MACRO;
$bas = DOMA bas INCL $surf 1.e-5 MACRO;
$entree = DOMA entree INCL $surf 1.e-5 MACRO;
$haut = DOMA haut INCL $surf 1.e-5 MACRO;
$sortie = DOMA sortie INCL $surf 1.e-5 MACRO;
surf=$surf.maillage;
ORIENTER surf;
entree= $entree.maillage;
haut = $haut.maillage ;
bas = $bas.maillage ;
sortie= $sortie.maillage ;
* CONSTANTES (avec Dim)
* Hauteur du canal (m)
Hc = 170e-3;
* Hauteur de reference (m)
H_ref = 28.e-3 ;
* vitesse de reference (m/s) = Vx(85)
U_ref = 2.147;
* constante de Von Karman
C1 = 0.4;
* constante du modele k-e
CNU = 0.09;
* taux de turbulence
INT = 0.03 ;
* vitesse de frottement (aerodynamique) en m/s
Uf = 0.079;
Lref = (Hc/H_ref) ;
* Proprietes physiques
* nu de l'eau (m**2/s)
nu_eau = 1e-6;
nu = nu_eau;
* NUT_ent/Nu
alf1 = 40.;
* Reynolds de l'écoulement
Re = (U_ref*H_ref)/nu ;
iRe = 1/Re ;
* Coordonnees
* Ordonnées de tous les points du maillage (sans dim)
Y1 = coor 2 surf;
* Ordonnées de tous les points de l'entree (CHPO et LISTREEL)  (sans dim)
Y2 = coor 2 entree;
YC2 = EVOL CHPO Y2 scal (inve entree) ;
* Nombre de noeud en hauteur
NH = DIME (extr YC2 ordo);
* list NH ;
* DISTANCE A LA PAROI (1/2 hauteur de la premiere maille) (sans dim)
YP = (EXTR (extr YC2 ordo) 2)/2;
* list Yp;
* opti donn 5;
* Prise en compte de Yp dans les ordonnees (y=y+yp)
Yyp = MANU CHPO entree 1 scal YP;
Yyp = Y2 + Yyp;
* CALCUL DES PROFILS D'ENTREE (un peu complique ...)
* (U= a*lnYyp + b) et (K= c*Yyp + d)
* (a,b,c,d) sont obtenus a partir des profils experimentaux.
* Definition du domaine ou les profils seront imposes
M_imp =entree;
* Calcul du profil symetrique
Yc = MANU CHPO entree 1 scal ((85.e-3/H_ref)+YP);
Ysym = Yc -(abs(Yyp - Yc));
Yslog = log Ysym;
* Profil de vitesse (sans dim) : Calcul des coeff a et b
* De maniere grossiere
a = 0.873/( (log((85.e-3/H_ref)+YP)) - (log((1.e-3/ H_ref)+YP)) ) ;
* list a;
b= 2.147-( a*(log((85.e-3/H_ref)+YP)) );
* list b ;
b=MANU CHPO entree 1 scal b;
* opti donn 5;
Uent = (Yslog*a)+b ;
Uent = Uent /U_ref;
* List Uent ;
* opti donn 5;
* Transformation du chpo scalaire en
* chpo vecteur + imposition sur le domaine
U1 = Uent NOMC 'UX' ;
U1 = KCHT $surf vect sommet U1;
* Valeurs IMPOSEES
UX_IMP = EXCO (REDU U1 M_imp) 'UX' SCAL;
UY_IMP = EXCO (REDU U1 M_imp) 'UY' SCAL;
* Valeurs INITIALES (sans dim)
U_ini = MANU CHPO surf 1 scal 1.;
U_ini = U_ini NOMC 'UX' ;
U_ini = KCHT $surf vect sommet U_ini;
* opti donn 5;
* ENERGIE CINETIQUE
* Kadim = K/(U_ref**2)
* Profil ECT : coeff c et d
c = -1.85184878e-1*H_ref;
d = 1.912227164e-2;
d = MANU CHPO entree 1 scal d;
Kent = ((Ysym*c)+ d);
Kent = (Kent/(U_ref**2));
* Fonction de l'intensite de la turbulence
K2 = (INT)**2 ;
K2 = 'MANU' 'CHPO' surf 1 scal K2;
* INITIALE
K_ini = KCHT $surf scal sommet K2;
* IMPOSEE
K_IMP = KCHT $surf scal sommet K2 Kent ;
K_IMP = EXCO (REDU K_IMP M_imp) SCAL;
* DISSIPATION
* Fonction de K_ini et de NUT
* K_ini est sans dim
E2 = (CNU*(K_ini**2)*Re)/(alf1);
* En entree, fonction de Kent et d'une longueur caractéristique
* K_ent est sans dim
E3 = ((Kent**1.5)*H_ref)/(Lref);
* INITIALE
E_ini = KCHT $surf scal sommet E2;
* IMPOSEE
E_IMP= KCHT $surf scal sommet E2 E3 ;
E_IMP=EXCO (REDU E_IMP M_imp) SCAL ;
* list E_imp;
* opti donn 5;
* NUT INITIALE
* NUTadim = NUT/(Uref*Href)
* NUadim =1/Re
* Fonction de K et E
* N2=CNU*(K_ini**2)*(E_ini**-1);
* Fonction de nu
N3=KCHT $surf scal sommet (alf1/Re) ;
N_ini = noel $surf N3 ;
* U* INITIALES
UET_ini1 = kcht $bas scal centre (Uf/U_ref);
UET_ini2 = kcht $haut scal centre (Uf/U_ref);
* opti donn 5;
* Module de resolution
RV = EQEX $surf ITMA iitma ALFA 0.8
OPTI 'SUPG' 'RNG'
  ZONE $surf OPER ERR
  ZONE $surf OPER NSKE iRe 'NUT' INCO 'UN' 'KN' 'EN'
  ZONE $bas OPER FPU iRe 'UET1' YP INCO 'UN' 'KN' 'EN'
  ZONE $haut OPER FPU iRe 'UET2' YP INCO 'UN' 'KN' 'EN'
  ZONE $surf OPER FILTREKE 1. Lref iRe 'UN' INCO 'KN' 'EN';
RV = EQEX RV
     CLIM 'UN' UIMP M_imp UX_imp
     CLIM 'UN' VIMP M_imp UY_imp
     CLIM 'KN' TIMP M_imp K_imp
     CLIM 'EN' TIMP M_imp E_imp ;
RVP = eqpr $surf
     ZONE $surf OPER PRESSION
     ZONE $bas OPER VNIMP 0.
     ZONE $haut OPER VNIMP 0.;
RV.PRESSION = RVP;
RV.INCO = TABLE INCO;
RV.INCO.'UN' = U_ini;
RV.INCO.'KN' = K_ini;
RV.INCO.'EN' = E_ini;
RV.INCO.'NUT' = N_ini;
RV.INCO.'UET1' = UET_ini1;
RV.INCO.'UET2' = UET_ini2;
RV.INCO.'UNM1'= KCHT (rv.'DOMAINE') vect sommet (1.E-3 1.E-3) ;
RV.INCO.'IT' = PROG 1 ;
RV.INCO.'ERY' = PROG 0. ;
RV.INCO.'ERX' = PROG 0.;
 rv.inco.'TABFK' = TABLE 'FiltreK' ;
 rv.inco.'TABFE' = TABLE 'FiltreE' ;
 rv.inco.'TTF' = TABLE 'Temps' ;
 rv.inco.'iTabF' = PROG ;
lh= (POIN SURF PROC (-2. 3.)) et (POIN SURF PROC (2. 0.5))
  et (POIN SURF PROC (2. 3.))
  et (POIN SURF PROC (10. 3.)) et (POIN SURF PROC (17. 3.));
  his=khis 'UN' 1 lh
           'UN' 2 lh
           'KN' lh
           'EN' lh;
   rv.hist=his;
exec RV;
 Fin;
```

## conge_seg2_seg3 [(sans section)]
```
* Petit test de l'opérateur CONG avec des éléments SEG2 et SEG3
* Il convient de vérifier "à l'oeil" la qualité
* des congés de raccordement produits
OPTI 'DENS' 0.1 ;
OPTI 'TRAC' 'PSC';
* E N D I M E N S I O N 2
OPTI 'DIME' 2 ;
p1 = 0. 0. ;
p2 = 1. 0. ;
p3 = 1. 1. ;
p4 = 1. 0.5 ;
p5 = 2. 0.5 ;
* Éléments de maillage SEG2
OPTI 'ELEM' 'SEG2' ;
l1 = DROI p1 p2 ;
l2 = DROI p2 p3 ;
l3 = DROI p4 p5 ;
* congé simple
TRAC 'QUAL' (l1 ET l2) 'TITR' 'Lignes avant conge' ;
l1b lcong l2b = CONG l1 l2 0.3 ;
TRAC 'QUAL' (l1b ET lcong ET l2b) 'TITR' 'Lignes apres conge' ;
* congé double
TRAC 'QUAL' (l1 ET l3) 'TITR' 'Lignes avant conge' ;
l1b lcong l3b = CONG l1 l3 0.3 'DOUBLE' ;
TRAC 'QUAL' (l1b ET lcong ET l3b) 'TITR' 'Lignes apres conge' ;
* Éléments de maillage SEG3
OPTI 'ELEM' 'SEG3' ;
l1 = DROI p1 p2 ;
l2 = DROI p2 p3 ;
l3 = DROI p4 p5 ;
* congé simple
TRAC 'QUAL' (l1 ET l2) 'TITR' 'Lignes avant conge' ;
l1b lcong l2b = CONG l1 l2 0.3 ;
TRAC 'QUAL' (l1b ET lcong ET l2b) 'TITR' 'Lignes apres conge' ;
* congé double
TRAC 'QUAL' (l1 ET l3) 'TITR' 'Lignes avant conge' ;
l1b lcong l3b = CONG l1 l3 0.3 'DOUBLE' ;
TRAC 'QUAL' (l1b ET lcong ET l3b) 'TITR' 'Lignes apres conge' ;
* E N D I M E N S I O N 3
OPTI 'DIME' 3 ;
p1 = 0. 0. 0. ;
p2 = 0. 0. 1. ;
p3 = 0. 1. 1. ;
p4 = 0.5 0. 1. ;
p5 = 0.5 0. 2. ;
* Éléments de maillage SEG2
OPTI 'ELEM' 'SEG2' ;
l1 = DROI p1 p2 ;
l2 = DROI p2 p3 ;
l3 = DROI p4 p5 ;
* congé simple
TRAC 'QUAL' (l1 ET l2) 'TITR' 'Lignes avant conge' ;
l1b lcong l2b = CONG l1 l2 0.3 ;
TRAC 'QUAL' (l1b ET lcong ET l2b) 'TITR' 'Lignes apres conge' ;
* congé double
TRAC 'QUAL' (l1 ET l3) 'TITR' 'Lignes avant conge' ;
l1b lcong l3b = CONG l1 l3 0.3 'DOUBLE' ;
TRAC 'QUAL' (l1b ET lcong ET l3b) 'TITR' 'Lignes apres conge' ;
* Éléments de maillage SEG3
OPTI 'ELEM' 'SEG3' ;
l1 = DROI p1 p2 ;
l2 = DROI p2 p3 ;
l3 = DROI p4 p5 ;
* congé simple
TRAC 'QUAL' (l1 ET l2) 'TITR' 'Lignes avant conge' ;
l1b lcong l2b = CONG l1 l2 0.3 ;
TRAC 'QUAL' (l1b ET lcong ET l2b) 'TITR' 'Lignes apres conge' ;
* congé double
TRAC 'QUAL' (l1 ET l3) 'TITR' 'Lignes avant conge' ;
l1b lcong l3b = CONG l1 l3 0.3 'DOUBLE' ;
TRAC 'QUAL' (l1b ET lcong ET l3b) 'TITR' 'Lignes apres conge' ;
FIN ;
```

## cormasse [(sans section)]
```
* Tests de la procédure cormasse qui corrige un chpo afin que ses valeurs
* soient positives et inférieures à Maxrho, et que que son intégrale
* soit égale à une valeur cible.
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
Lref = 3. ;
p1 = 0. 0. ;
p2 = Lref 0. ;
p3 = Lref Lref ;
p4 = 0. Lref ;
vtf = 'MANU' 'QUA4' P1 P2 P3 P4 ;
Mvtf = 'CHAN' vtf 'QUAF' ;
'ELIM' Mvtf 1.D-5 ;
$vtf = 'MODE' Mvtf 'NAVIER_STOKES' 'QUAF' ;
vtf = 'DOMA' $vtf 'MAILLAGE' ;
x y = 'COOR' vtf ;
MaxRho = 10000. ;
* 1. Champ uniforme 2 : Mcfd=18
RHOi = 'KCHT' $vtf 'SCAL' 'SOMMET' 2. ;
* 1.1/ Correction nulle
mcible1 = 18. ;
dRHO1 RHOk1 MiCFD = CORMASSE $vtf RHOi Mcible1 MaxRho ;
* 1.2/ Correction uniforme +9 / V = +1
mcible2 = 27. ;
dRHO2 RHOk2 MiCFD = CORMASSE $vtf RHOi Mcible2 MaxRho ;
* 1.3/Correction uniforme -9 / V = -1
mcible3 = 9. ;
dRHO3 RHOk3 MiCFD = CORMASSE $vtf RHOi Mcible3 MaxRho ;
* 2. Champ non uniforme linéaire (y+1) : Mcfd=22.5
RHOi = 'KCHT' $vtf 'SCAL' 'SOMMET' (y '+' 1.) ;
* 2.4/Correction uniforme -9/V = -1 en restant positif
mcible4 = 13.500000001 ;
dRHO4 RHOk4 MiCFD = CORMASSE $vtf RHOi Mcible4 MaxRho ;
* 2.5/Idem légèrement négatif
mcible5 = 13.499999999 ;
dRHO5 RHOk5 MiCFD = CORMASSE $vtf RHOi Mcible5 MaxRho ;
* 2.6/Correction non uniforme (redistribution du négatif)
mcible6 = 9. ;
dRHO6 RHOk6 MiCFD = CORMASSE $vtf RHOi Mcible6 MaxRho ;
* 2.7/Correction non uniforme (redistribution du négatif)
mcible7 = 1. ;
dRHO7 RHOk7 MiCFD = CORMASSE $vtf RHOi Mcible7 MaxRho ;
* Tests de non-régression
'LIST' (rhok2 '-' 1.);
'LIST' (rhok2 '-' 3.);
'LIST' (rhok3 '-' 1.);
'LIST' (rhok4 '-' y);
'LIST' (rhok5 '-' y);
'LIST' (rhok6 '-' 2.4) ;
'LIST' (rhok7 '-' (2./3.));
erho1 = rhok1 '-' 2. ;
val1 = 'MAXI' erho1 'ABS' ;
erho2 = rhok2 '-' 3. ;
val2 = 'MAXI' erho2 'ABS' ;
erho3 = rhok3 '-' 1. ;
val3 = 'MAXI' erho3 'ABS' ;
erho4 = rhok4 '-' y ;
val4 = 'MAXI' erho4 'ABS' ;
erho5 = rhok5 '-' y ;
val5 = 'MAXI' erho5 'ABS' ;
erho6 = ('REDU' rhok6 (p3 'ET' p4)) '-' 2.4 ;
val6 = 'MAXI' erho6 'ABS' ;
erho7 = ('REDU' rhok7 (p3 'ET' p4)) '-' (2./3.) ;
val7 = 'MAXI' erho7 'ABS' ;
'MESS' val1 val2 val3 val4 val5 val6 val7 ;
graph = faux ;
'SI' graph ;
   'TRAC' vtf RHOk1 'TITR' 'Rho_i=2 , Rho_f=2' ;
   'TRAC' vtf RHOk2 'TITR' 'Rho_i=2 , Rho_f=3' ;
   'TRAC' vtf RHOk3 'TITR' 'Rho_i=2 , Rho_f=1' ;
   'TRAC' vtf RHOk4 'TITR' 'Rho_i=y+1 , Rho_f=y^+' ;
   'TRAC' vtf RHOk5 'TITR' 'Rho_i=y+1 , Rho_f=y^-' ;
   'TRAC' vtf RHOk6
   'TITR' 'Rho_i=y+1 , Rho_f=(0,0.9,2.4) en (bas,milieu,haut)' ;
   'TRAC' vtf RHOk7
   'TITR' 'Rho_i=y+1 , Rho_f=(0,0,2/3) en (bas,milieu,haut)' ;
'FINS' ;
vmax = 'MAXI' ('PROG' val1 val2 val3 val4 val5 val6 val7) ;
'SI' (vmax '>' 1.D-8) ;
   'ERRE' 5 ;
'FINS' ;
'FIN' ;
```

## dync02 [(sans section)]
```
* Calcul d'un rotor de type Jeffcott avec contact frottant
* avec la methode HBM (DYNC)
* ___ ^ Z
* _|_ kc,mu |__
* _______ jeu |_ \_
* | k,c | | | \ \
* |----------| m |----------| +--|--|-----> Y
* | |_______| R R+jeu
* ___ jeu
* _|_ kc,mu
* ^ Z
* +----> X
* Ref : [Xie et al., MSSP, 2015]
* Auteur : PBZ CEA-ENSTA, 2020-07-07
* OPTIONS GENERALES
  OPTI DIME 3 ELEM SEG2 ;
  OPTION 'TRAC' 'PSC' 'EPTR' 8 'POTR' 'HELVETICA_16';
* PARAMETRES
* nombre de modes a calculer
  NMODE = 2;
* nombre de harmoniques a calculer et NFFT
  NHBM = 7;
  NFFT = 256;
* mu de frottement
* mu = 0.05;
  mu = 0.2;
* DEFINITION DU MODELE
* rotor data
  m = 1. ;
  k = 100.;
  c = 5. ;
  jeu = 0.105;
  R = 20.*jeu ;
  ebal = 0.1;
* Fbal = ebal * m * (Omega**2) ; avec Omega = vitesse de rotation en rad/s
* contact parameters
  kchoc= 25. * k;
  mu_s = mu;
  mu_d = mu;
  si (mu_s < mu_d); erreur 21; finsi;
  Kt = 10.*kchoc;
  Ct = 0.5*(m*Kt)**0.5;
* deduced parameter
  w = (k/m)**0.5;
  wHz = w / (2.*pi);
  wchoc = (kchoc/m)**0.5;
  xi = 0.5 * c / ((kchoc*m)**0.5);
  mess 'w=' w '(' wHz ')Hz < wchoc=' wchoc;
  mess 'xi=' xi;
* critical timestep (Diff Centrees, no damping)
  wadhe = ((k+Kt)/m)**0.5;
  dtc = 2. / wadhe;
* !!! on adimensionne apres !!!
* BASE MODALE
* point physique
  p1 = 0. 0. 0.;
* base modale = 2 modes
  palfa1 = 0. 0. 0.;
  phi1 = MANU 'CHPO' p1 3 'UX' 0. 'UY' 1. 'UZ' 0. 'NATURE' 'DIFFUS';
  palfa2 = 0. 0. 0.;
  phi2 = MANU 'CHPO' p1 3 'UX' 0. 'UY' 0. 'UZ' 1. 'NATURE' 'DIFFUS';
  TBAS = TABL 'BASE_MODALE';
  TBAS . 'MODES' = TABL 'BASE_DE_MODES';
  TBAS . 'MODES' . 1 = TABL 'MODES';
  TBAS . 'MODES' . 1 . 'POINT_REPERE' = palfa1;
  TBAS . 'MODES' . 1 . 'FREQUENCE' = wHz/wchoc;
  TBAS . 'MODES' . 1 . 'MASSE_GENERALISEE' = 1.;
  TBAS . 'MODES' . 1 . 'DEFORMEE_MODALE' = phi1;
  TBAS . 'MODES' . 2 = TABL 'MODES';
  TBAS . 'MODES' . 2 . 'POINT_REPERE' = palfa2;
  TBAS . 'MODES' . 2 . 'FREQUENCE' = wHz/wchoc;
  TBAS . 'MODES' . 2 . 'MASSE_GENERALISEE' = 1.;
  TBAS . 'MODES' . 2 . 'DEFORMEE_MODALE' = phi2;
* AMORTISSEMENT
  TAMOR = TABL 'AMORTISSEMENT';
  Ctot = MANU 'RIGIDITE' 'TYPE' 'AMORTISSEMENT'
        (palfa1 et palfa2) (MOTS 'ALFA') (prog (c / (m*wchoc)));
  TAMOR . 'AMORTISSEMENT' = Ctot ;
* LIAISONS
* contact-frottant point_cercle_frottement
  TL1 = TABL 'LIAISON_ELEMENTAIRE';
  TL1 . 'TYPE_LIAISON' = mot 'POINT_CERCLE_FROTTEMENT';
  TL1 . 'SUPPORT' = p1;
  TL1 . 'NORMALE' = (1. 0. 0.) ;
  TL1 . 'EXCENTRATION' = (0. 0. 0.) ;
  TL1 . 'RAIDEUR' = 1.;
  TL1 . 'RAYON' = 1. ;
  TL1 . 'COEFFICIENT_GLISSEMENT' = mu_d;
  TL1 . 'COEFFICIENT_ADHERENCE' = mu_s;
  TL1 . 'RAIDEUR_TANGENTIELLE' = -1.*Kt;
* TL1 . 'AMORTISSEMENT_TANGENTIEL'= Ct;
  TL1 . 'AMORTISSEMENT_TANGENTIEL'= 1.E-4;
  TL1 . 'VITESSE_ENTRAINEMENT' = 0. ;
* TL1 . 'VITESSE_ENTRAINEMENT' = -1.*R*Omega;
* stockage
  TLB = TABL 'LIAISON_B';
  TLB . 1 = TL1;
  TLIA = TABL 'LIAISON';
  TLIA . 'LIAISON_B' = TLB;
* CHARGEMENT
  Fbal = ebal*m/(m*jeu) ;
  Fchpo_Y = MANU 'CHPO' 1 palfa1 'FALF' Fbal;
  Fchpo_Z = MANU 'CHPO' 1 palfa2 'FALF' Fbal;
* +++ BALOURD == 1 pour ajouter w**2 a Fbal
* CALCUL NON LINEAIRE
* chargement spatial : GFC1
      TAB_CHAR = TABLE 'CHARGEMENT';
      TAB_CHAR . 1 = Fchpo_Y;
      TAB_CHAR . -1 = Fchpo_Z;
* Pour ajouter w**2 dans la definition du chargement
      TAB_CHAR . 'BALOURD' = 1;
* Approximation pour la solution initiale à fréquence fixe
      VEC_INIT = TABLE 'INITIAL';
      VEC_INIT . 'FREQUENCE' = 0.5/wchoc ;
* VEC_INIT . 3 = 0.1;
* Paramètres numériques pour la continuation
      PAR_NUM = TABLE 'PARAMETRES_NUMERIQUES';
      PAR_NUM . 'TYPE' = MOT 'FORC';
      PAR_NUM . 'VAL_FIN' = 60./wchoc;
      PAR_NUM . 'DS0' = 0.01;
* PAR_NUM . 'DSMAX' = 0.1;
      PAR_NUM . 'DSMAX' = 0.025;
      PAR_NUM . 'DSMIN' = 1.E-4;
      PAR_NUM . 'ITERMOY' = 3.4;
      PAR_NUM . 'ITERMAX' = 20;
      PAR_NUM . 'ANGLE_MIN' = 0.;
      PAR_NUM . 'ANGLE_MAX' = 40.;
      PAR_NUM . 'ISENS' = 1.;
       PAR_NUM . 'NBPAS' = 2000;
* PAR_NUM . 'NBPAS' = 200;
      PAR_NUM . 'TOLERANCE' = 1.E-7;
* PAR_NUM . 'CALC_JAC' = VRAI;
      PAR_NUM . 'CALC_JAC' = FAUX;
* Appel a l'operateur
* opti impi 2;
 opti impi 1;
      TCON = DYNC TBAS TAB_CHAR TLIA TAMOR VEC_INIT PAR_NUM
                        NHBM NFFT;
 opti impi 0;
* POST-TRAITEMENT
* COURBE DE REPONSE
* frequence
  FREQ = TCON . 'REPONSE' . 'FREQUENCE';
* MAX de la NORME2 des COEFFICIENTS de FOURIER pour chaque freq
  AMPS = TCON . 'REPONSE' . 'NORME_DEPLACEMENT';
* evolution
  XY = EVOL MANU '\w' FREQ '|Q|' AMPS;
* stabilite
  STAB = TCON . 'REPONSE' . 'STABILITE';
  TABSTB = TABLE;
  TABSTB . 'LIGNE_VARIABLE' = TABL ENTI;
  TABSTB . 'LIGNE_VARIABLE' . 1 = STAB;
  TITR 'Jeffcott : courbe de reponse';
  DESS XY TABSTB ;
  DESS XY TABSTB XBOR 0.14 0.16 ;
* BIFURCATIONS
* recup
  NBIF = DIME TCON . 'BIFURCATION' . 'TYPE';
  prLP_Q = PROG; prLP_w = PROG;
  prBP_Q = PROG; prBP_w = PROG;
  prPD_Q = PROG; prPD_w = PROG;
  prNS_Q = PROG; prNS_w = PROG;
  REPE BBIF NBIF;
    typbif = EXTR TCON . 'BIFURCATION' . 'TYPE' &BBIF;
    Qbif = EXTR TCON . 'BIFURCATION' . 'NORME_DEPLACEMENT' &BBIF;
    wbif = EXTR TCON . 'BIFURCATION' . 'FREQUENCE' &BBIF;
    SI (EGA typbif 'LP'); prLP_Q = prLP_Q et Qbif; prLP_w = prLP_w et wbif; FINSI;
    SI (EGA typbif 'BP'); prBP_Q = prBP_Q et Qbif; prBP_w = prBP_w et wbif; FINSI;
    SI (EGA typbif 'PD'); prPD_Q = prPD_Q et Qbif; prPD_w = prPD_w et wbif; FINSI;
    SI (EGA typbif 'NS'); prNS_Q = prNS_Q et Qbif; prNS_w = prNS_w et wbif; FINSI;
  FIN BBIF;
* creation d'1 evolution + table de dessin
  ibif = 1;
  evBIF = VIDE 'EVOLUTIO';
* Limit Point
  si ((dime prLP_w) > 0); ibif = ibif + 1;
    evLP = EVOL MANU LEGE 'LP' '\w' prLP_w '|Q|' prLP_Q;
    evBIF = evBIF et evLP;
    TABSTB . ibif = MOT 'NOLI MARQ LOSA';
  finsi;
* Branch Point
  si ((dime prBP_w) > 0); ibif = ibif + 1;
    evBP = EVOL MANU LEGE 'BP' '\w' prBP_w '|Q|' prBP_Q;
    evBIF = evBIF et evBP;
    TABSTB . ibif = MOT 'NOLI MARQ CARR';
  finsi;
* Period Doubling Point
  si ((dime prPD_w) > 0); ibif = ibif + 1;
    evPD = EVOL MANU LEGE 'PD' '\w' prPD_w '|Q|' prPD_Q;
    evBIF = evBIF et evPD;
    TABSTB . ibif = MOT 'NOLI MARQ TRID';
  finsi;
* Neimark Sacker Point
  si ((dime prNS_w) > 0); ibif = ibif + 1;
    evNS = EVOL MANU LEGE 'NS' '\w' prNS_w '|Q|' prNS_Q;
    evBIF = evBIF et evNS;
    TABSTB . ibif = MOT 'NOLI MARQ TRIU';
  finsi;
  DESS (XY ET evBIF )TABSTB 'TITR' 'Jeffcott : courbe de reponse + bifurcations';
* STABILITE via les EXPOSANTS DE FLOQUET
* On assigne une couleur aux exposants de FLOQUET et on leur assigne une couleur
  TEXP_R = TCON . 'REPONSE' . 'EXPOSANT_REEL';
  TEXP_I = TCON . 'REPONSE' . 'EXPOSANT_IMAGINAIRE';
  exp_R = VIDE 'EVOLUTIO';
  exp_I = VIDE 'EVOLUTIO';
   coco = MOTS 'ROUG' 'BLEU' 'VERT' 'AZUR' 'ORAN' 'VIOL' 'TURQ' ;
  repe bexp;
    si (non (exis TEXP_R &bexp)); quit bexp ; finsi;
    coco_i = EXTR coco &bexp;
    exp_R = exp_R ET (evol coco_i 'MANU' '\w' FREQ '\m_{R}' TEXP_R . &bexp);
    exp_I = exp_I ET (evol coco_i 'MANU' '\w' FREQ '\m_{I}' TEXP_I . &bexp);
  fin bexp;
  TITRE 'Jeffcott : exposants de Floquet';
  DESS exp_R ;
  DESS exp_I ;
* REPONSE DE L'HARMONIQUE 1
* evolution de l'harmonique 1 des modes en y et en z
  j = 1;
  y1 = TCON . REPONSE . COEFFICIENTS . j . palfa1;
  z1 = TCON . REPONSE . COEFFICIENTS . j . palfa2;
  ev1 = (EVOL 'AZUR' 'MANU' 'LEGE' 'mode 1 (y)' '\w' FREQ 'Q^{j=1}' y1)
    et (EVOL 'ORAN' 'MANU' 'LEGE' 'mode 2 (Z)' '\w' FREQ 'Q^{j=1}' Z1);
  DESS ev1 'TITR' 'Jeffcott : Reponse de l harmonique 1 des 2 modes' LEGE SO;
* TEST DE BON FONCTIONNEMENT
* listreel des erreurs
  prERR = PROG;
* amplitude max et w correspondant a la 1ere resonance (harmonique 1)
  wref1 = 0.8860;
  Qref1 = 4.5324;
  imax1 wmax1 Qmax1 = MAXI XY;
  prERR = prERR et (wmax1 - wref1) et (Qmax1 - Qref1);
* nombre et/ou type et/ou localisation des bifurcations
  wrefNS = 0.28929;
  QrefNS = 1.5662 ;
  wNS = EXTR prNS_w 1;
  QNS = EXTR prNS_Q 1;
  prERR = prERR et (wNS - wrefNS) et (QNS - QrefNS);
* test
  ERRMAX = MAXI prERR 'ABS';
  SI (ERRMAX > 0.05);
    LIST prERR;opti donn 5 trac X;
    ERRE 5;
  FINSI;
* PERFORMANCES
  TEMP IMPR MAXI CPU;
* opti donn 5 trac X;
FIN ;
```

## eauacti [(sans section)]
```
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
 SAUT PAGE ;
* Test de bon fonctionnement des operateurs LOGK COAC FION et NEUT
* eau + temperature 80. + pression CO2
OPTION DIME 2 ;
A= 0. 0. ;
B= 5. 0. ;
OPTION ELEM QUA4 ;
 AB= A DROIT 1 B ;
 MT = CHANGE AB POI1 ;
  XX YY = COOR MT ;
* table de données pour CHI1
TABDON=TABLE ;
TABDON.BDD= 'STRASBG' ;
TABDON.IDEN= LECT 1 50 60 61 101 165 ;
 TABDON.CHXMX= LECT 2144 2148 2157 2166 2168 2192 2198 2200
    2224 2231 2249 2278 2281 2372 ;
 TABCLIM=TABLE ;
 TABCLIM.TYP6= LECT 2002 ;
 TABCLIM.TYP3= LECT 2400 ;
 TABCLIM.COMP3= LECT 101 ;
 TABDON.CLIM=TABCLIM ;
 TABDON.TEMPERATURE = 'OUI' ;
   TB1=CHI1 TABDON
  LOGK ('CHAINE' DIVERS '/COMPSM')
  ENTH ('CHAINE' DIVERS '/COMPSM')
  COMP ('CHAINE' DIVERS '/COMPSM') ;
* table de données pour CHI2
 TBPARM= TABLE ;
 TBPAR2= TABLE ;
 TBPAR2.'SOUSTYPE'= 'DONNEES_CHIMIQUES' ;
 TBPARM.ITMAX = 95;
 TBPARM.ITERSOLI = 10 ;
 TBPARM.NFI = 8;
 TBPARM.EPS= 1.D-4 ;
 TBPAR2.LOGC= MANU CHPO MT 6 X001 -3.6 X050 -6.0 X060 -5.0
              X061 -3. X101 -6.5 X165 -6.5 ;
  TOT001= MANU CHPO MT 1 X001 6.D-4 ;
  TOT050= MANU CHPO MT 1 X050 -1.15D-3 ;
  TOT060= MANU CHPO MT 1 X060 0.D0 ;
  TOT061= MANU CHPO MT 1 X061 2.8D-2 ;
  TOT101= MANU CHPO MT 1 X101 0.D0 ;
  TOT165= MANU CHPO MT 1 X165 5.5D-5 ;
 TBPAR2.TOT= TOT001+ TOT050 + TOT060 + TOT061 + TOT101 + TOT165 ;
* définition du champ de temperature
  TMPE= MANU CHPO MT 1 SCAL 80. ;
  TBPAR2.TEMPE= TMPE ;
* KCO2= MANU CHPO MT 1 W016 20.45 ;
   KCO2= MANU CHPO MT 1 W016 2.32 ;
  TBPAR2.CLIM= KCO2 ;
 TBPARM.SORTIE= MOTS 'PREC' 'FION' 'TYP5' 'SOLU' ;
 TBPARM.IMPRIM= LECT 1 ;
* option impi 1 ;
 TB3= CHI2 TB1 TBPARM TBPAR2 ;
  option impi 0 ;
* Opérateur LOGK
  ONI= TB3.FION ;
 LLK= LOGK TB1 FORCEIONI ONI TEMPERATURE TMPE ;
* LIST LLK ;
* Verification du résultat
* Les valeurs LKREF sont celles figurant dans la colonne LOGK
* dans le tableau sorti par CHIMI2 avec l'option  impi 1
 LKREF = MANU CHPO MT 32 W001 0. W002 0. W003 0. W004 0. W005 0.
 W006 0. W007 14.799 W008 1.41924 W009 3.5127 W010 12.063
 W011 -8.982 W012 12.103 W013 6.6868 W014 10.049 W015 16.374
 W016 18.266 W017 12.564 W018 12.793 W019 8.871 W020 3.2849
 W021 33.481 W022 38.633 W023 27.960 W024 32.431 W025 41.452
 W026 29.842 W027 2.4878 W028 12.715 W029 42.9798 W030 47.0985
 W031 26.582 W032 18.491 'NATURE' DISCRET ;
 VERLK=( ABS( LLK-LKREF)) MASQ SUPERIEUR 0.01 SOMME ;
 LIST VERLK ;
 SI ( VERLK EGA 0) ;
     ERRE 0 ;
 SINO ;
     ERRE 5 ;
 FINSI ;
* Opérateur NEUT
 CHA= NEUT TB1 ( TB3.SOLU ) ;
* LIST CHA ;
* Vérification du résultat
* Les valeurs de référence pour NCAT et NANI sont les valeurs
* de cations et anions dans le tableau imprimé par CHIMI2 avec
* l'option impi 1
 NCAT= EXTR CHA 'CATI' ((EXTR CHA MAIL) POINT 1) ;
 NANI= EXTR CHA 'ANIO' ((EXTR CHA MAIL) POINT 1) ;
 LIST NANI ;
 SI (ABS(NANI + 0.001136 ) > 0.000001) ;
     ERRE 5 ;
 FINSI ;
 LIST NCAT ;
 SI (ABS(NCAT - 0.001131 ) > 0.000001) ;
     ERRE 5 ;
 FINSI ;
* Opérateur FION
 FIO = FION TB1 ( TB3.SOLU ) ;
* LIST FIO ;
* vérification du résultat
 FFF= RESU( ABS(TB3.FION - FIO)) ;
 VFF= EXTR FFF 'SCAL' ((EXTR FFF MAIL) POINT 1) ;
 LIST VFF ;
 SI (VFF > 1.D-10) ;
      ERRE 5 ;
 FINSI ;
* Opérateur COAC
 ACT = COAC TB1 FORCEIONI ONI TEMPERAT TMPE ;
* LIST ACT ;
 VAC= EXTR ACT 'SCAL' ((EXTR ACT MAIL) POINT 1) ;
 LIST VAC ;
 SI (ABS(VAC + 0.02229 ) > 0.0001) ;
     ERRE 5 ;
 FINSI ;
fin ;
```

## echi_som [(sans section)]
```
* test de non-regression concernant l'operateur ECHI
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
EPSI = 1.E-8 ;
P0 = 0.0 0.0 ;
P1 = 1.0 0.0 ;
P2 = 1.0 1.0 ;
P3 = 0.0 1.0 ;
S1 = 'MANU' 'QUA4' P0 P1 P2 P3 ;
Mparoif = 'CHAN' S1 'QUAF' ;
$paroif = 'MODE' Mparoif 'NAVIER_STOKES' 'LINE' ;
paroif = 'DOMA' $paroif 'MAILLAGE' ;
Diag = 'DOMA' $paroif 'XXDIAGSI' ;
   rtf = 'EQEX'
   'OPTI' 'EFM1' 'CENTREE' 'IMPL'
   'ZONE' $paroif 'OPER' 'ECHI' 'KHEW' 'TBPW' 'INCO' 'TF'
   'OPTI' 'EFM1' 'CENTREE' 'IMPL'
   'ZONE' $paroif 'OPER' 'ECHI' 'KHW1' 'TBPW' 'INCO' 'TF'
   'OPTI' 'EF' 'CENTREE' 'IMPL'
   'ZONE' $paroif 'OPER' 'ECHI' 'KHEW' 'TBPW' 'INCO' 'TF'
   'OPTI' 'EF' 'CENTREE' 'IMPL'
   'ZONE' $paroif 'OPER' 'ECHI' 'KHW1' 'TBPW' 'INCO' 'TF' ;
rtf.'INCO' = 'TABLE' 'INCO' ;
rtf.'INCO'.'TF' = 'KCHT' $paroif 'SCAL' 'SOMMET' 10.0 ;
rtf.'INCO'.'TBPW' = 'KCHT' $paroif 'SCAL' 'SOMMET' 5.0 ;
XX1 = 'COORD' 1 paroif ;
rtf.'INCO'.'KHEW' = 'KCHT' $paroif 'SCAL' 'CENTRE' 1.5 ;
rtf.'INCO'.'KHW1' = 'KCHT' $paroif 'SCAL' 'SOMMET' (XX1 + 1.0 ) ;
B1 A1 = 'ECHI' rtf.'1ECHI' ;
B2 A2 = 'ECHI' rtf.'2ECHI' ;
B3 A3 = 'ECHI' rtf.'3ECHI' ;
B4 A4 = 'ECHI' rtf.'4ECHI' ;
TF1 = 'COPIER' rtf.'INCO'.'TBPW' ;
TF1 = 'NOMC' TF1 'TF' ;
BB2 = 'KMF' A2 TF1 ;
BB4 = 'KMF' A4 TF1 ;
BB1 = 'KMF' A1 TF1 ;
BB3 = 'KMF' A3 TF1 ;
ERROR = 0 ;
BBB2 = Diag * (rtf.'INCO'.'KHW1') * TF1 ;
'SI' (('MAXI' (BB2 - B2) 'ABS') '>' EPSI) ;
ERROR = ERROR + 1 ;
'MESS' ('MAXI' (BB2 - B2) 'ABS') ;
'MESS' 'Probleme echi (EFM1) coeff mult aux sommets !' ;
'FINSI' ;
'SI' (('MAXI' (BBB2 - BB2) 'ABS') '>' EPSI) ;
ERROR = ERROR + 1 ;
'MESS' ('MAXI' (BBB2 - BB2) 'ABS') ;
'MESS' 'Probleme echi (EFM1) coeff mult aux sommets !' ;
'FINSI' ;
'SI' (('MAXI' (BB4 - B4) 'ABS') '>' EPSI) ;
ERROR = ERROR + 1 ;
'MESS' ('MAXI' (BB4 - B4) 'ABS') ;
'MESS' 'Probleme echi (EF)   coeff mult aux sommets !' ;
'FINSI' ;
'SI' (('MAXI' (BB1 - B1) 'ABS') '>' EPSI) ;
ERROR = ERROR + 1 ;
'MESS' ('MAXI' (BB1 - B1) 'ABS') ;
'MESS' 'Probleme echi (EFM1) coeff mult aux centres !' ;
'FINSI' ;
'SI' (('MAXI' (BB3 - B3) 'ABS') '>' EPSI) ;
ERROR = ERROR + 1 ;
'MESS' ('MAXI' (BB3 - B3) 'ABS') ;
'MESS' 'Probleme echi (EF)   coeff mult aux centres !' ;
'FINSI' ;
'SI' (ERROR '>' 0) ;
'ERRE' 5 ;
'FINSI' ;
'FIN' ;
```

## effmarti [(sans section)]
```
OPTI DIME 3 MODE TRID ELEM QUA4;
* Test sur la procedure de EFFMARTI pour tester la
* projection des efforts globaux sur un element coque
* vers le modele à trois couches de MARTI.
* On teste un seul element avec les caracteristiques
* suivantes:
* Epaisseur 0.1 m
* Enrobage externe 0.025 m
* Enrobage interne 0.025 m
* cotg(th) 1.43
* Le cas test consiste à projeter le tenseur des efforts suivant:
* N11 = 1 N/m
* N22 = 2 N/m
* N12 = 3 N/m
* M11 = 4 Nm/m
* M22 = 5 Nm/m
* M12 = 6 Nm/m
* V1 = 7 N/m
* V2 = 8 N/m
* On laisse l'option pour effectuer le meme calcul sur un element
* plus complexe (CAS1 = 2)
* Develloppé par Alberto FRAU /DEN/DANS/DM2S/SEMT/EMSI
* et Nicolas ILE /DEN/DANS/DM2S/SEMT/EMSI
* selection du calcul
* si CAS1 egal à 1 -> alors on lance le cas test
* si CAS1 egal à 2 -> alors on lance le cas test
CAS1 = 1.;
SI (CAS1 EGA 1);
* Calcul de test pour la procedure EFFMARTI
* Proprietés geometriques
  H1 = 0.1;
  ER1 = 0.025;
  ER2 = 0.025;
  COT1 = 1.43;
* Definition de l'element
  P0 = 0. 0. 0.;
  P1 = 1. 0. 0.;
  P2 = 1. 1. 0.;
  P3 = 0. 1. 0.;
  L1 = D 1 P0 P1;
  L2 = D 1 P1 P2;
  L3 = D 1 P2 P3;
  L4 = D 1 P3 P0;
* definition de l'element
  SUR1 = DALL L1 L2 L3 L4;
* Contruction du modele et du materiau
  MOD1 = MODE SUR1 MECANIQUE ELASTIQUE ISOTROPE COQ4;
  MAT1 = MATE MOD1 YOUNG 30000.E6 NU 0.2 RHO 2500. EPAI H1;
* Definition du tensueur des efforts
  N11_A = 1;
  N22_A = 2;
  N12_A = 3;
  M11_A = 4;
  M22_A = 5;
  M12_A = 6;
  V1_A = 7;
  V2_A = 8;
  SIG1 = MANU CHML MOD1 'TYPE' 'CONTRAINTES'
                         'N11' N11_A 'N22' N22_A 'N12' N12_A
                         'M11' M11_A 'M22' M22_A 'M12' M12_A
                         'V1' V1_A 'V2' V2_A;
  SIG1 = RTENS SIG1 MOD1 MAT1 (1.0 0. 0.) (0. 1. 0.);
* Projection des efforts sur les trois couches de MARTI
  SIG2 = EFFMARTI SIG1 MOD1 MAT1 (1. 0. 0.) (0. 1. 0.)
   H1 ER1 ER2 COT1;
* extractions des efforts projetés
  N11E_A = EXTR SIG2 'N11E' 1 1 1;
  N22E_A = EXTR SIG2 'N22E' 1 1 1;
  N12E_A = EXTR SIG2 'N12E' 1 1 1;
  N11I_A = EXTR SIG2 'N11I' 1 1 1;
  N22I_A = EXTR SIG2 'N22I' 1 1 1;
  N12I_A = EXTR SIG2 'N12I' 1 1 1;
  VR_A = EXTR SIG2 'VR' 1 1 1;
* calcul des efforts projétés
  DD1 = H1 - ER1 - ER2;
  VR_B = ((V1_A*V1_A) + (V2_A*V2_A))**(0.5);
  N11E_B = (N11_A*0.5) + (M11_A/DD1) +
             ((V1_A*V1_A)/((2*VR_B)*(COT1)));
  N22E_B = (N22_A*0.5) + (M22_A/DD1) +
             ((V2_A*V2_A)/((2*VR_B)*(COT1)));
  N12E_B = (N12_A*0.5) + (M12_A/DD1) +
             ((V1_A*V2_A)/((2*VR_B)*(COT1)));
  N11I_B = (N11_A*0.5) - (M11_A/DD1) +
             ((V1_A*V1_A)/((2*VR_B)*(COT1)));
  N22I_B = (N22_A*0.5) - (M22_A/DD1) +
             ((V2_A*V2_A)/((2*VR_B)*(COT1)));
  N12I_B = (N12_A*0.5) - (M12_A/DD1) +
             ((V1_A*V2_A)/((2*VR_B)*(COT1)));
* test
  SI (ABS(N11E_B - N11E_A)>(1.E-10));
    ERRE 5;
  FINSI;
  SI (ABS(N22E_B - N22E_A)>(1.E-10));
    ERRE 5;
  FINSI;
  SI (ABS(N12E_B - N12E_A)>(1.E-10));
    ERRE 5;
  FINSI;
  SI (ABS(N11I_B - N11I_A)>(1.E-10));
    ERRE 5;
  FINSI;
  SI (ABS(N22I_B - N22I_A)>(1.E-10));
    ERRE 5;
  FINSI;
  SI (ABS(N12I_B - N12I_A)>(1.E-10));
    ERRE 5;
  FINSI;
SINON;
* Calcul des efforts projetés sur une plaque
* de dimensions 2x4 chargée par une force sur
* un cote et encastrée dans l'autre
* Proprietés geometriques
  H1 = 0.1;
  ER1 = 0.025;
  ER2 = 0.025;
  COT1 = 1.43;
* Definition de l'element
  P0 = 0. 0. 0.;
  P1 = 4. 0. 0.;
  P2 = 4. 2. 0.;
  P3 = 0. 2. 0.;
  L1 = D 20 P0 P1;
  L2 = D 10 P1 P2;
  L3 = D 20 P2 P3;
  L4 = D 10 P3 P0;
* definition de l'element
  SUR1 = DALL L1 L2 L3 L4;
* Construction du modele et du materiau
  MOD1 = MODE SUR1 MECANIQUE ELASTIQUE ISOTROPE COQ4;
  MAT1 = MATE MOD1 YOUNG 30000.E6 NU 0.2 RHO 2500. EPAI H1;
* Forces
  FOR1 = FORCE L2 'FZ' -1000.;
* Blocages
  BL1 = (BLOQUER 'UZ' L4) ET
        (BLOQUER 'UX' L4) ET
        (BLOQUER 'RY' L4) ET
        (BLOQUER 'UY' P0);
* Resolution
  RIG1 = RIGI MOD1 MAT1;
  RES1 = RESO (RIG1 ET BL1) (FOR1);
* Determination des efforts generalisés
  SIG1 = SIGM RES1 MOD1 MAT1;
  SIG1 = RTENS SIG1 MOD1 MAT1 (1.0 0. 0.) (0. 1. 0.);
  SIG2 = EFFMARTI SIG1 MOD1 MAT1 (1. 0. 0.) (0. 1. 0.)
   H1 ER1 ER2 COT1;
  TRAC (EXCO SIG1 'M11') MOD1 TITR 'Mxx';
  TRAC (EXCO SIG1 'M22') MOD1 TITR 'Myy';
  TRAC (EXCO SIG1 'M12') MOD1 TITR 'Mxy';
  TRAC (EXCO SIG1 'V1') MOD1 TITR 'Vx';
  TRAC (EXCO SIG1 'V2') MOD1 TITR 'Vy';
  TRAC (EXCO SIG2 'N11E') MOD1 TITR 'Nxx Externe';
  TRAC (EXCO SIG2 'N22E') MOD1 TITR 'Nyy Externe';
  TRAC (EXCO SIG2 'N12E') MOD1 TITR 'Nxy Externe';
  TRAC (EXCO SIG2 'N11I') MOD1 TITR 'Nxx Interne';
  TRAC (EXCO SIG2 'N22I') MOD1 TITR 'Nyy Interne';
  TRAC (EXCO SIG2 'N12I') MOD1 TITR 'Nxy Interne';
FINSI;
FIN;
```

## exemple_nommer [(sans section)]
```
* Fichier "exemple_nommer.dgibi"
nommer test 'c3m' ;
* test est un mot contenant 'c3m' ;
list test ;
* On doit avoir un nouveau MOT "TEST"
list *MOT ;
nommer TEST 'ZZZZ' ;
* C3M est un mot contenant "ZZZZ" (car TEST = MOT contenant 'c3m' -> converti en majuscules)
list C3M ;
* On doit avoir un nouveau MOT "C3M"
list *MOT ;
opti dime 2 elem QUA8 ;
p0 = 1. 0. ;
tabr = 'TABLE' ;
tabr. 1 = 'DROIT' 3 P0 (2. 0.) ;
list tabr ;
nommer 'Ma_Ligne' tabr. 1 ;
* La chaine est convertie en MAJUSCULES !
list MA_LIGNE ;
list *MAILLAGE ;
str_lig = 'CHAINE' 'Autre_nom' ;
nommer str_lig ma_ligne ;
list AUTRE_NOM ;
list *MAILLAGE ;
* Exemples d'effet de bord :
nommer test test ;
* test contenant c3M -> ce nommer revient a changer le contenu du mot C3M par le contenu de test !!!
* donc C3M contient "c3M" et non plus "ZZZZ" comme suite au premier nommer test !
list test ; list C3M ;
* -- Ci-apres FIN des exemples d'erreur (a ne pas commettre !)
'FIN' ;
* Quelques exemples d'erreur :
option erre ignore ;
* On ne donne pas l'objet a nommer :
nommer test ;
* On ne donne pas le nom de l'objet :
nommer MA_LIGNE ;
* On n'a pas le nom :
nommer P0 tabr ;
option erre normale ;
'FIN' ;
* -- Doit conduire aux affichages suivants :
 $ *
 $ * * Quelques exemples d'erreur :
 $ *
 $ * option erre ignore ;
 $ * * On ne donne pas l'objet a nommer :
 $ *
 $ * nommer test ;
 Objet a nommer non trouve / Object to be named not found
* ERREUR 21 ***** dans l'operateur NOMM
 Donnees incompatibles
 $ *
 $ * * On ne donne pas le nom de l'objet :
 $ * nommer MA_LIGNE ;
* ERREUR 37 ***** dans l'operateur NOMM
 On ne trouve pas d'objet de type 'MOT'
 $ *
 $ * * On n'a pas le nom :
 $ * nommer P0 tabr ;
* ERREUR 37 ***** dans l'operateur NOMM
 On ne trouve pas d'objet de type 'MOT'
 $ *
 $ * option erre normale ;
 $ * 'FIN' ;
```

## fatigue [(sans section)]
```
opti dime 3 elem cub8 echo 1 ;
* operateur FATIGUE
* exemples critere DANG VAN : JL FAYART
LGRAPH = FAUX ;
p_ori = 0. 0. 0. ;
e_x = 1. 0. 0. ; e_y = 0. 1. 0. ; e_z = 0. 0. 1. ;
p_A = p_ori plus p_ori ; p_B = p_A plus e_x ;
l1 = d 1 p_A p_B ;
s1 = l1 trans 1 e_y ;
p_C = p_B plus e_y ; p_D = p_C moins e_x ;
p_C = point s1 proc p_C ; p_D = point s1 proc p_D ;
V1 = s1 volu trans 1 e_z ;
p_E p_F p_G p_H = p_A p_B p_C p_D plus e_z ;
p_E = point v1 proc p_E ;
p_F = point v1 proc p_F ;
 p_G = point v1 proc p_G ;
p_H = point v1 proc p_H ;
mo1 = mode v1 mecanique elastique ;
ca1 = mate mo1 youn 2.e11 nu 0.3 ;
bl_A = bloq depla p_A ;
bl_B = bloq uy uz p_B ;
bl_C = bloq uz p_C ;
bl_D = bloq ux uz p_D ;
bl_t = bloq uz (p_E et p_F et p_G et p_H) ;
bl_cis1 = bloq depla(p_A et p_B et p_E et p_F) ;
bl_cis2 = bloq ux (p_C et p_D et p_G et p_H) ;
bl_cis3 = bloq uy uz (p_C et p_D et p_G et p_H) ;
* traction
ch_t = depi bl_t 6.5e-4 ;
abs1 = prog 0. 1. 2. 3.;
ev_t = evol manu abs1 (prog 0. -1. 0. 1.) ;
ctrasi = char meca ev_t ch_t ;
trasi = table 'PASAPAS' ;
trasi . modele = mo1 ;
trasi . caracteristiques = ca1 ;
trasi . blocages_mecaniques = bl_A et bl_B et bl_C et bl_D et bl_t ;
trasi . chargement = ctrasi ;
trasi . temps_calcules = abs1 ;
pasapas trasi ;
* explorer trasi ;
* kich : coefficients arbitraires
cafatp = manu chml trasi . modele 'ADVK' -0.33 'BDVK' 8.e7
  'APAP' -0.34 'BPAP' 8.1e7 'ASIN' -0.35 'BSIN' 8.2e7
  'ACRO' -0.36 'BCRO' 8.3e7 'A_DC' -0.37 'B_DC' 8.4e7
    type 'CARACTERISTIQUES' stresses ;
chasi1 = char trasi . temps trasi . contraintes ;
chfa1 = FATI mo1 chasi1 cafatp ;
* list chfa1 ;
 xtrasi = extr chfa1 dvkp 1 1 5 ;
 xtrasi0 = -8.75000E-03 ;
 er1 = abs((xtrasi - xtrasi0)/xtrasi0) ;
SI (LGRAPH) ;
  trac chfa1 mo1 ;
FINSI ;
chfa1 = FATI mo1 chasi1 cafatp 'DVKP' ;
rits16 = extr chfa1 dvkp 1 1 6 ;
ets16 = extr chfa1 'PTAU' 1 1 6 ;
SI (LGRAPH) ;
 dess ets16 ;
FINSI ;
chfa1 = FATI mo1 chasi1 cafatp 'PAPA' 'SEUI' 'TOUS' ;
rits16 = extr chfa1 papa 1 1 6 ;
ets16 = extr chfa1 'PTAU' 1 1 6 ;
SI (LGRAPH) ;
 dess ets16 ;
FINSI ;
* traction repetee
abs2 = prog 0. pas 1. 3. ;
ev_r = evol manu abs2 (prog 0. 0.5 1. 0.5) ;
ctrare = char meca ev_r ch_t ;
trare = table 'PASAPAS' ;
trare . modele = mo1 ;
trare . caracteristiques = ca1 ;
trare . blocages_mecaniques = bl_A et bl_B et bl_C et bl_D et bl_t ;
trare . chargement = ctrare ;
trare . temps_calcules = abs2 ;
pasapas trare ;
* explorer trare ;
chasi2 = char trare . temps trare . contraintes ;
chfa2 = FATI mo1 chasi2 cafatp 'DVKP' ;
 xtrare = extr chfa2 dvkp 1 1 5 ;
 xtrare0 = -0.41500 ;
 er2 = abs((xtrare - xtrare0)/xtrare0) ;
SI (LGRAPH) ;
  trac chfa2 mo1 ;
FINSI ;
ritr16 = extr chfa2 dvkp 1 1 6 ;
si (ritr16 > -0.2) ;
  etr16 = extr chfa2 ptau 1 1 6 ;
finsi ;
* cisaillement
ch_cis = depi bl_cis2 1.e-3;
ccisa = char meca ev_t ch_cis ;
tcisa = table 'PASAPAS' ;
tcisa . modele = mo1 ;
tcisa . caracteristiques = ca1 ;
tcisa . blocages_mecaniques = bl_cis1 et bl_cis2 et bl_cis3 ;
tcisa . chargement = ccisa ;
tcisa . temps_calcules = abs1 ;
pasapas tcisa ;
* explorer tcisa ;
chasi3 = char tcisa . temps tcisa . contraintes ;
chfa3 = FATI mo1 chasi3 cafatp 'DVKP' ;
rici16 = extr chfa3 dvkp 1 1 6 ;
eci16 = extr chfa3 'PTAU' 1 1 6 ;
 xtcisa = extr chfa3 dvkp 1 1 5 ;
 xtcisa0 = -3.84615E-02 ;
 er3 = abs((xtcisa - xtcisa0)/xtcisa0) ;
SI (LGRAPH) ;
  dess eci16 ;
FINSI ;
si ((er1 < 0.05 ) et (er2 < 0.05) et (er3 < 0.05)) ;
     erre 0 ;
sinon ;
    erre 5 ;
finsi ;
fin ;
```

## flslic4 [(sans section)]
```
* test de validation de l' élément de raccord fluide -
* structure LIC4.
* calcul du mode n=3 m=1 d'un système de coques
* concentriques. La coque exterieure est supposée
* encastrée, la coque interieure est libre.
* valeurs de comparaison: calcul en mode fourier n=3
* Les valeurs sont Fréquence = 47.491
* Masse généralisée = 2563.1
* On ne modélise qu'un quart de modèle compte tenu des
* symetries.
* Pour la coque externe, les conditions sont ux=uy=uz=0
* rx=ry=rz=0
* Pour la coque interne les conditions sont
* plan xz SYMETRIE
* plan yz ANTISYMETRIE
* uz=0
* Pour le fluide les conditions sont
* plan xz dP/dn=0
* plan yz P=0
* plan x=0 et x=h dP/dn
opti dime 3 ;
opti elem cub8 ;
opti echo 0 ;
* definition des donnees parametriques
ri =1.00; comm rayon de la coque interne ;
re =1.30; comm rayon de la coque externe ;
h =1.00; comm hauteur du modele ;
hc =0.04; comm epaisseur des coques ;
lc0=5.3; comm longueur caracteristique du fluide ;
y0 =2.1e11; comm module d YOUNG des coques ;
roc=7900; comm masse volumique de l acier ;
decouz= 5; comm nombre d elements suivant z ;
decout= 10; comm nombre d elements suivant teta ;
decouf= 5; comm nombre d elements sur le rayon ;
vect= 0. 0. 0.0; comm vect translation pour raccord fluide
structure ;
* definition des points
pci1= ri 0.00 0.00 ;
pci2= ri 0.00 h ;
pce1= re 0.00 0.00 ;
pce2= re 0.00 h ;
ce1=0.00 0.00 0.00 ;
ce2=0.00 0.00 h ;
* definition des coques
lci= pci1 d decouz pci2 ;
lce= pce1 d decouz pce2 ;
sci= lci rota decout 90 ce1 ce2 ;
sce= lce rota decout 90 ce1 ce2 ;
* definition du fluide
lcf1 = lci plus vect ;
lcf2 = lce moins vect ;
sflu1= lcf1 rota decout 90 ce1 ce2 ;
sflu2= lcf2 rota decout 90 ce1 ce2 ;
vflu = volu sflu1 decouf sflu2 ;
* definition des elements de raccords
opti elem lia4 ;
raci= liaison 0.001 sflu1 sci ;
race= liaison 0.001 sflu2 sce ;
* definition des modeles elements finis
moci = modele sci 'MECANIQUE' 'ELASTIQUE' coq4 ;
moce = modele sce 'MECANIQUE' 'ELASTIQUE' coq4 ;
mocri= modele raci 'MECANIQUE' 'LIQUIDE' lic4 ;
mocre= modele race 'MECANIQUE' 'LIQUIDE' lic4 ;
mocf = modele vflu 'LIQUIDE' lcu8 ;
* definition des materiaux
maci = mate moci youn y0 nu 0.3 rho roc epai hc ;
mace = mate moce youn y0 nu 0.3 rho roc epai hc ;
macf = mate mocf rho 1000 rorf 1000 cson 1435 cref 1435
                       lcar lc0 g 9.81 ;
macri= mate mocri rho 1000 rorf 1000 cson 1435 cref 1435
                      lcar lc0 g 9.81 ;
macre= mate mocre rho 1000 rorf 1000 cson 1435 cref 1435
                      lcar lc0 g 9.81 ;
cacri= carac mocri 'LIQUIDE' vflu ;
cacre= carac mocre 'LIQUIDE' vflu ;
macri= macri et cacri ;
macre= macre et cacre ;
macr = macri et macre ;
* calcul des rigidites
rigci= rigi moci maci ;
rigce= rigi moce mace ;
rigcf= rigi mocf macf ;
rigcr= rigi (mocri et mocre) macr;
rigt = rigci et rigce et rigcf et rigcr ;
* calcul des matrices de masse
masci= masse moci maci ;
masce= masse moce mace ;
mascf= masse mocf macf ;
mascr= masse (mocri et mocre) macr ;
mast = masci et masce et mascf et mascr ;
* definition des conditions aux limites
pcr1= pci1 tour 90 ce1 ce2 ;
pcr2= pci2 tour 90 ce1 ce2 ;
pcr3= pce2 tour 90 ce1 ce2 ;
pnx= sci point plan ce1 pci1 pci2 0.001 ;
vpny= vflu point plan pcr1 pcr2 pcr3 0.001 ;
pnz= sci point plan pcr1 ce1 pci1 0.001 ;
blo1= bloque depla rota sce ;
blo2= symt 'DEPL' ce1 pci1 pci2 sci 0.001 ;
blo3= anti 'DEPL' pcr1 pcr2 pcr3 sci 0.001 ;
blo4= symt 'ROTA' ce1 pci1 pci2 sci 0.001 ;
blo5= anti 'ROTA' pcr1 pcr2 pcr3 sci 0.001 ;
blo6= bloque uz sci ;
blop = bloque 'P' 'PI' vpny ;
blot= blo1 et blo2 et blo3 et blo4 et blo5 et blo6 et blop ;
* calcul de la rigidite totale
rigt= rigt et blot ;
* utilisation de vibre option proc
tmx1= vibr proch (prog 40.) rigt mast ;
* extraction des resultats
kfois=1 ;
freq = tmx1.modes.kfois.frequence ;
utot = tmx1.modes.kfois.deformee_modale ;
mn = tmx1.modes.kfois.masse_generalisee ;
* recalcul par modification de la normalisation
* maxi du deplacement ux =1
uxm = maxi (exco ux utot) ;
unox= utot/uxm ;
udx1= manu 'CHPOINT' (sci et sce et raci et race) 6
      ux 1.0 uy 0.0 uz 0.0 rx 0.0 ry 0.0 rz 0.0 nature diffus ;
udx2= manu 'CHPOINT' (raci et race et vflu) 2
      'P' 0.0 'PI' 0.0 nature diffus ;
udx = udx1 + udx2 ;
qx = ytmx unox udx mast ;
mnx = ytmx unox unox mast ;
mnx = mnx ;
* comparaison aux valeurs de références
iuer=0.05 ;
tvalth= table ;
tvalth.1=47.491 ;
tvalth.2=2563.1 ;
tvalca= table ;
tvalca.1= freq ;
tvalca.2= mnx ;
ierc=table ;
i=1 ;
iercmax= 0.0 ;
repeter bverif 2 ;
 ierc.i= ((tvalth.i)-(tvalca.i)) ;
 ierc.i= (ierc.i)/(tvalth.i) ;
 si ((ierc.i) < 0.0) ;
     xvali= ierc.i ;
     ierc.i=abs xvali ;
 finsi ;
 si (iercmax < (ierc.i)) ;
     iercmax= (ierc.i) ;
 finsi ;
i=i+1 ;
fin bverif ;
si (iercmax < iuer) ;
 mess 'bonne fin du calcul' ;
 sinon ;
 mess 'ecart maximal vaut ' iercmax 'il y a un probleme' ;
finsi ;
fin ;
```

## fluage_fibre_norton_2 [(sans section)]
```
* Comparaison du modele de fluage de Norton :
* - modele poutre a fibre VS modele massif
* - chargement uniaxial, traction puis compression
* - en force imposee
* Options generales
OPTI 'DIME' 3 'ELEM' 'CU20' 'ECHO' 0 ;
itrac = FAUX ;
* Parametres geometrie (poutre a section rectangulaire)
a = 0.05 ;
b = 0.02 ;
l = 1. ;
se = a * b ;
* Nombres d'elements
nea = 1 ;
neb = 1 ;
nel = 1 ;
* Parametres materiau
yo = 1.E8 ;
nu = 0.3 ;
af1 = 3.E-13 ;
af2 = 1.2 ;
af3 = 1.4 ;
* Parametres chargement
ftrac = 10000. ;
tl = 200. ;
* Maillage et modele volumique
p0 = 0. 0. 0. ;
p1 = 0. a 0. ;
l1 = DROI nea p0 p1 ;
s1 = l1 TRAN neb (0. 0. b) ;
p2 = s1 POIN 'PROC' (0. 0. b) ;
v1 = s1 VOLU 'TRAN' nel (l 0. 0.) ;
env1 = ENVE v1 ;
are1 = ARET v1 ;
p3 = v1 POIN 'PROC' (l 0. 0.) ;
s2 = v1 FACE 2 ;
mov = MODE v1 'MECANIQUE' 'ELASTIQUE' 'FLUAGE' 'NORTON' ;
mav = MATE mov 'YOUN' yo 'NU' nu 'SMAX' 0. 'AF1' af1
                          'AF2' af2 'AF3' af3 ;
* Maillage et modele de section
OPTI 'ELEM' 'CUB8' ;
lig1 = DROI nea ((-0.5 * a) (-0.5 * b) 0.) ((0.5 * a) (-0.5 * b) 0.) ;
s3 = lig1 TRAN neb (0. b 0.) ;
s3 = SURF (CONT s3) 'PLAN' ;
mos = MODE s3 'MECANIQUE' 'ELASTIQUE' 'PLASTIQUE' 'NORTON' 'QUAS' 'TRIS' ;
mas = MATE mos 'YOUN' yo 'NU' nu 'AF1' af1 'AF2' af2 'AF3' af3 'SMAX' (yo / 1000.) 'ALPY' 0.66 'ALPZ' 0.66 ;
* Maillage et modele de poutre TIMO
lf = DROI nel p0 p3 ;
mop = MODE lf 'MECANIQUE' 'ELASTIQUE' 'SECTION' 'PLASTIQUE' 'SECTION' 'TIMO' ;
map = MATE mop 'MODS' mos 'MATS' mas 'VECT' (0. 1. 0.) ;
* Conditions aux limites
tl0 = 1.E-5 ;
tl2 = 2. * tl ;
tl3 = 3. * tl ;
tl4 = 4. * tl ;
evcha = EVOL 'MANU' (PROG 0. tl0 tl (tl + tl0) tl2 (tl2 + tl0) tl3 (tl3 + tl0) tl4)
                    (PROG 0. 0.999 1. 0.001 0. -0.999 -1. -0.001 0.) ;
* pour le modele volumique
* encastrement
bl1 = (BLOQ 'UX' s1) ET (BLOQ 'UY' 'UZ' p0) ET (BLOQ 'UZ' p1) ;
* force imposee
ft = FSUR 'MASS' mov s2 ((ftrac / se) 0. 0.) ;
chaft = CHAR 'MECA' ft evcha ;
* pour le modele TIMO
* encastrement
bl1p = BLOQ 'DEPL' 'ROTA' p0 ;
* force imposee
ftp = FORC (ftrac 0. 0.) p3 ;
chaftp = CHAR 'MECA' ftp evcha ;
* Resolution
xpas = tl / 20. ;
ltc = PROG tl0 'PAS' xpas tl
           (tl + tl0) 'PAS' xpas tl2
           (tl2 + tl0) 'PAS' xpas tl3
           (tl3 + tl0) 'PAS' xpas tl4 ;
tv = TABL ;
tv . 'MODELE' = mov ;
tv . 'CARACTERISTIQUES' = mav ;
tv . 'BLOCAGES_MECANIQUES' = bl1 ;
tv . 'CHARGEMENT' = chaft ;
tv . 'TEMPS_CALCULES' = ltc ;
TEMP 'ZERO' ;
PASAPAS tv ;
itp1 = TEMP 'HORL' ;
tp = TABL ;
tp . 'MODELE' = mop ;
tp . 'CARACTERISTIQUES' = map ;
chmsg0 = ZERO mos 'CONTRAIN' ;
chmvi0 = ZERO mos 'VARINTER' ;
tp . 'VARIABLES_INTERNES' = TABL ;
tp . 'VARIABLES_INTERNES' . 0 = MANU 'CHML' mop 'VONS' chmsg0 'VAIS' chmvi0 'TYPE' 'VARIABLES INTERNES' 'STRESSES' ;
tp . 'BLOCAGES_MECANIQUES' = bl1p ;
tp . 'CHARGEMENT' = chaftp ;
tp . 'TEMPS_CALCULES' = ltc ;
TEMP 'ZERO' ;
PASAPAS tp ;
itp11 = TEMP 'HORL' ;
MESS 'Temps horloge : ' ;
MESS (CHAI '- modele massif :' ' ' itp1) ;
MESS (CHAI '- modele poutre :' ' ' itp11) ;
* Post traitement
n1 = DIME (tv . 'TEMPS') ;
ltps = PROG ;
* deplacements de l'extremite
luv = EXTR (EVOL 'TEMP' tv 'DEPLACEMENTS' 'UX' p3) 'ORDO' ;
lup = EXTR (EVOL 'TEMP' tp 'DEPLACEMENTS' 'UX' p3) 'ORDO' ;
* force de reaction a l'encastrement
lfv = PROG ;
REPE b1 n1 ;
  i1 = &b1 - 1 ;
  ltps = ltps ET (tv . 'TEMPS' . i1) ;
  fv = 0. ;
  SI (NEG i1 0) ;
    fv = MAXI (EXCO 'FX' (RESU (REDU (tv . 'REACTIONS' . i1) s1))) ;
  FINSI ;
  lfv = lfv ET fv ;
FIN b1 ;
lfp = EXTR (EVOL 'TEMP' tp 'REACTIONS' 'FX' p0) 'ORDO' ;
* defomration inelastique
lev = PROG ;
lep = PROG ;
vol1 = MESU v1 ;
REPE b1 n1 ;
  i1 = &b1 - 1 ;
  tps1 = tv . 'TEMPS' . i1 ;
  lev = lev ET ((INTG mov (tv . 'VARIABLES_INTERNES' . i1) 'EPSE') / vol1) ;
  uv = tv . 'DEPLACEMENTS' . i1 ;
  up = tp . 'DEPLACEMENTS' . i1 ;
  tabv = TABL ;
  tabv . 'DEPLACEMENTS' = TABL ;
  tabv . 'DEPLACEMENTS' . 1 = up ;
  tabv . 'VONS' = TABL ;
  tabv . 'VONS' . 1 = EXCO (tp . 'VARIABLES_INTERNES' . i1) 'VONS' ;
  tabv . 'VAIS' = TABL ;
  tabv . 'VAIS' . 1 = EXCO (tp . 'VARIABLES_INTERNES' . i1) 'VAIS' ;
  mail1 = POUT2MAS mop map 'GAUSS' tabv ;
  vips = tabv . 'VAIS_3D' . 1 ;
  mobid = MODE mail1 'MECANIQUE' ;
  cham1 = CHAN 'CHAM' mobid vips ;
  epsep = (INTG mobid cham1 'EPSE') * l / (NBEL lf) / se ;
  lep = lep ET epsep ;
FIN b1 ;
* Analyse/trace des resultats
tleg = TABL ;
tleg . 1 = MOT 'MARQ LOSA NOLI' ;
tleg . 2 = MOT 'MARQ ROND NOLI' ;
tleg . 'TITRE' = TABL ;
tleg . 'TITRE' . 1 = 'Modele 3D massif' ;
tleg . 'TITRE' . 2 = 'Modele poutre fibre' ;
MESS 'Ecart relatif max.' ;
evuv = EVOL 'VERT' 'MANU' 'Temps' ltps 'Deplacement' luv ;
evup = EVOL 'ROUG' 'MANU' 'Temps' ltps 'Deplacement' lup ;
difu = (MAXI (ABS (lup - luv))) / (MAXI (ABS luv)) ;
MESS '-- deplacement :' difu ;
SI itrac ;
  DESS (evuv ET evup) 'TITR' 'Deplacement vs. Temps' 'LEGE' tleg ;
FINSI ;
evfv = EVOL 'VERT' 'MANU' 'Temps' ltps 'Force' lfv ;
evfp = EVOL 'ROUG' 'MANU' 'Temps' ltps 'Force' lfp ;
diff = (MAXI (ABS (lfp - lfv))) / (MAXI (ABS lfv)) ;
MESS '-- effort      :' diff ;
SI itrac ;
  DESS (evfv ET evfp) 'TITR' 'Force vs. Temps' 'LEGE' tleg ;
FINSI ;
evev = EVOL 'VERT' 'MANU' 'TEMPS' ltps 'EPSE' lev ;
evep = EVOL 'ROUG' 'MANU' 'TEMPS' ltps 'ESPE' lep ;
dife = (MAXI (ABS (lep - lev))) / (MAXI (ABS lev)) ;
MESS '-- def. fluage :' dife ;
SI itrac ;
  DESS (evev ET evep) 'TITR' 'Deformation non lin. (EPSE) vs Temps' 'LEGE' tleg ;
FINSI ;
* Erreur si l'ecart relatif est trop eleve
lerr = PROG difu diff dife ;
errmax = MAXI lerr ;
MESS ;
SI (errmax > 6000.) ;
  MESS 'Echec du cas test !' ;
  ERRE 5 ;
SINON ;
  MESS 'Succes du cas test !' ;
FINSI ;
FIN ;
```

## forgeage [(sans section)]
```
* fichier forgeage.dgibi
* F O R G E A G E . D G I B I
* Objet :
* Exemple de simulation du forgeage d'un tube en compression simple.
* On applique un effort sur le bord superieur du tube, le deplacement
* de sa partie inferieure etant bloque axialement. Le tube est soumis
* a un champ de temperature variant quadratiquement de 0 a 1000 degres
* du haut vers le bas.
* Le tube a un comportement elastoplastique avec ecroissage lineaire
* isotrope. Ses carateristiques diminuent avec la temperature. Il se
* deforme donc essentiellement dans sa partie chaude, comme dans le cas
* d'une mise en forme par forgeage.
* On suppose que le tube est initialement a la temperature decrite.
* On calcule l'equilibre pas a pas, en appliquant la charge de facon
* croissante.
* Le calcul est realise en grands deplacements. On utilise des
* elements finis quadratiques a integration selective (BBAR) pour limiter
* les effets de verrouillage numerique dus a l'incompressibilite plastique.
* Enfin, on regularise le maillage au cours du calcul a l'aide de
* l'operateur DEDU ADAP appele dans PERSO1 afin de limiter l'ecrasement
* des mailles sur le bas du maillage.
* Description :
* Type de calcul : Mecanique, Plastique, Grands Deplacements
* Mode de calcul : 2D AXIS
* Type d'element : QUA8, TRI6
* Chargement : Temperature, Force
opti dime 2 elem qua8 mode axis ;
* ig1 : activation traces
* complet : calcul complet
ig1 = faux ;
complet = faux ;
* ------------------------- Geometrie, maillage ------------------------
* Parametres :
* ep1 : epaissseur du tube (m)
* lo1 : longueur du tube (m)
* Ri1 : rayon interieure du tube (m)
* hr1 : hauteur remaillage (m)
* de1 : densite maillage fin
* de2 : densite maillage grossier
ep1 = 1.0e-3 ;
lo1 = 3.e-3 ;
Ri1 = 5.e-3 ;
hr1 = 2.e-3 ;
de1 = 0.03e-3 ;
de2 = 0.25e-3 ;
de3 = de2 ;
de0 = 0.5 * de1 ;
* Points :
P1 = Ri1 0 ;
P2 = P1 plus (ep1 0) ;
P3 = P2 plus (0 hr1) ;
P4 = Ri1 hr1 ;
P5 = Ri1 lo1 ;
* Maillage du haut :
lm2 = P4 droi P3 dini de3 dfin de3 ;
s2 = lm2 tran (P5 moin P4) dini de3 dfin de3 ;
s2 = s2 coul gris ;
* Maillage du bas :
lb1 = P1 droi P2 dini de0 dfin de0 ;
ld1 = P2 droi P3 dini de0 dfin de2 ;
lm1 = lm2 ;
lg1 = P4 droi P1 dini de2 dfin de0 ;
sr1 = surf (lb1 et ld1 et lm1 et lg1) ;
sr1 = sr1 coul oran ;
* Maillage "total"
s0 = sr1 et s2 ;
* Optimisation Sr1 avec DEDU ADAP :
opti mode plan ;
chde1 = mesu dens sr1 ;
chde1 = born chde1 scal comp de1 de2 ;
clada1 = (bloq depl (lg1 et ld1)) et (bloq depl (lb1 et lm1)) et (rela mili sr1) ;
chada1 = dedu adap sr1 clada1 dens chde1 ;
clada1 = (bloq uy lb1) et (bloq depl (ld1 et lm1 et lg1)) et (rela mili sr1) ;
srX = (sr1 plus (0 0)) coul blan ;
form chada1 ;
opti mode axis ;
* Fin optimisation
si ig1 ;
  trac s0 titr ' Maillage tube' ;
  mbox1 = boite sr1 ;
  trac s0 boit mbox1 titr ' Zoom partie raffinee' ;
  trac (sr1 et srX) titr ' Maillage initial (blanc) / apres adaptation (orange)' ;
fins ;
* ------------------------ Modelisation mecanique ----------------------
* Caracteristiques materielles :
evym1 = evol roug manu 'T' (prog 0. 1000.) 'YOUN' (prog 210.e9 10.e9) ;
ecro0 = evol bleu manu 'EPSE' (prog 0. 1.) 'ECRO' (prog 300.e6 600.e6) ;
ecro1000 = evol vert manu 'EPSE' (prog 0. 1.) 'ECRO' (prog 10.e6 20.e6) ;
ecro1 = (nuag comp 'T' 0. comp 'ECRO' ecro0) et (nuag comp 'T' 1000. comp 'ECRO' ecro1000) ;
si ig1 ;
  dess evym1 titr 'Module de Young vs. temperature' ;
  tleg1 = table ;
  tleg1 . titre = table ;
  tleg1 . titre . 1 = 'T =    0 deg.' ;
  tleg1 . titre . 2 = 'T = 1000 deg.' ;
  dess ecro1 titr 'Courbes ecrouissage vs. temperature' lege tleg1 ;
fins ;
* Temperature initiale / imposee ;
chz1 = s0 coor 2 ;
cht1 = (((chz1 - lo1 / lo1) ** 2) * 1000.) nomc 'T' ;
mod1 = mode s0 mecanique elastique plastique isotrope bbar ;
chtref1 = chan cham mod1 cht1 ;
mat1 = mate mod1 youn evym1 nu 0.3 ecro ecro1 alph 1.e-5 tref chtref1 talp. 0. ;
* CL mecanique :
lh1 = s2 cote 3 ;
clmb1 = bloq uz lb1 ;
clmh1 = rela ense uz lh1 ;
* Force impose :
fimp1 = forc (0 -4000.) lh1 ;
ev1 = evol manu temp (prog 0. 1.) dimp (prog 0. 1.) ;
cgm1 = char meca fimp1 ev1 ;
* Chargement en temperature :
chz1 = s0 coor 2 ;
cht1 = (((chz1 - lo1 / lo1) ** 2) * 1000.) nomc 'T' ;
ev0 = evol manu temp (prog 0. 1.e12) dimp (prog 1. 1.) ;
cgt1 = char 'T' cht1 ev0 ;
si ig1 ;
  trac ((lh1 chan poi1) coul roug et s0) titr ' Noeuds deplacement impose' ;
  trac cht1 s0 titr 'Temperature imposee' ;
fins ;
* ------------------------------- PERSO1 -------------------------------
* Adaptation maillage avec PERSO1 :
debp perso1 tu1*table ;
wtab1 = tu1.wtable ;
* Sauvegarde configuration :
si (exis tu1 config_adaptation) ;
  iadap1 = dime tu1.config_adaptation ;
  tu1.config_adaptation.iadap1 = form ;
sino ;
  tu1.config_adaptation = table ;
  tu1.config_adaptation.0 = form ;
fins ;
* Retour config. initiale & sortie si fin de calcul :
tps1 = wtab1.temps0 ;
tpsmax1 = (tu1.temps_calcules) maxi ;
si (tps1 ega tpsmax1) ;
  mess ' ***** PERSO1 : retour config. initiale' ;
  form (tu1.config_adaptation.0) ;
  quit perso1 ;
fins ;
* Adaptation :
geoada1 = tu1.donnees_perso1.geom ;
rigada1 = tu1.donnees_perso1.clad ;
chdens1 = tu1.donnees_perso1.chdens ;
epsm1 = tu1.donnees_perso1.seuil ;
* Sauvegarde seuil adaptation :
si (exis wtab1 epsm_remail) ;
  seui1 = wtab1.epsm_remail ;
sino ;
  seui1 = epsm1 ;
fins ;
eps1 = tu1.estimation.deformations ;
epmax1 = maxi abs eps1 ;
* Test adaptation :
si (epmax1 > seui1) ;
  mess '  ***** PERSO1 : Adaptation maillage ' ;
  list seui1 ; list epsm1 ;
  wtab1.epsm_remail = seui1 + epsm1 ;
* Adaptation maillage avec DEDU ADAP :
  dep1 = tu1.estimation.deplacements ;
  conf1 = form dep1 ;
  opti mode plan ;
  chada1 = dedu adap geoada1 rigada1 dens chdens1 ;
  srx1 = (geoada1 plus (0 0)) coul blan ;
  form chada1 ;
  opti mode axis ;
  si ig1 ;
    trac nclk (srx1 et geoada1) titr 'Maillage initial (blanc) / adapte (orange)' ;
  fins ;
  form (-1.*dep1) ;
fins ;
finp ;
* ------------------------- Resolution PASAPAS -------------------------
ltca1 = prog 0. PAS 0.02 0.4 PAS 0.005 1. ;
si complet ;
  ltsa1 = prog 0. pas 0.02 1. ;
sino ;
  ltca1 = ltca1 extr (lect 1 pas 1 10) ;
  ltsa1 = ltca1 ;
fins ;
tpas1 = table ;
tpas1. modele = mod1 ;
tpas1. caracteristiques = mat1 ;
tpas1. chargement = cgm1 et cgt1 ;
tpas1. blocages_mecaniques = clmb1 et clmh1 ;
tpas1. grands_deplacements = vrai ;
tpas1. predicteur = mot hpp ;
tpas1. lagrangien = mot reactualise ;
tpas1. temps_calcules = ltca1 ;
tpas1. temps_sauves = ltsa1 ;
tpas1. procedure_perso1 = vrai ;
tpas1. donnees_perso1 = table ;
tpas1. donnees_perso1. geom = sr1 ;
tpas1. donnees_perso1. clad = clada1 ;
tpas1. donnees_perso1. chdens = chde1 ;
tpas1. donnees_perso1. seuil = 0.05 ;
pasapas tpas1 ;
* -------------------------- Post-traitement ---------------------------
if1 = (tpas1.temps) dime - 1 ;
depf1 = tpas1.deplacements.if1 ;
modf1 = mod1 ;
si ig1 ;
  conf0 = form ;
  form depf1 ;
  epsf1 = tpas1.estimation.deformations ;
  trac epsf1 modf1 titr 'Deformations en fin de calcul' ;
  sigf1 = tpas1.contraintes.if1 ;
  sigf1 = 1.e-6 * sigf1 ;
  trac sigf1 modf1 titr 'Contraintes en fin de calcul' ;
  form conf0 ;
fins ;
mbox1 = boite s0 ;
liso1 = prog -200. pas 25. 50. ;
def1 = vide deforme ;
repe b1 if1 ;
  depi1 = tpas1.deplacements.&b1 ;
  sigi1 = tpas1.contraintes.&b1 ;
  sigi1 = 1.e-6 * sigi1 ;
  form tpas1.config_adaptation.&b1 ;
  defi1 = defo s0 depi1 1. (exco sigi1 smzz smzz) mod1 ;
  form tpas1.config_adaptation.0 ;
  def1 = def1 et defi1 ;
  si (ega (vale trac) 'PSC') ;
    trac defi1 liso1 boit mbox1 ;
  fins ;
fin b1 ;
si ig1 ;
  trac anim def1 liso1 ;
fins ;
fin ;
* F I N F O R G E A G E . D G I B I
```

## gatt_dpg [(sans section)]
```
* Test gatt_dpg.dgibi: Jeux de données
'OPTI' 'DIME' 2 'MODE' 'PLAN' 'GENE' ;
'OPTI' 'ELEM' 'QUA8' ;
'OPTI' 'TRAC' 'PSC' ;
'TEMPS' 'ZERO' ;
L = 'MOT' LIST ; F = 'MOT' FIN ;
* TEST DE VALIDATION
* MODELE GATT_MONERIE
* AFA3GLAA INCOMPRESSIBLE AVEC COUPLAGE DYNAMIQUE
* MAILLAGE:
* EPROUVETTE CARRE
* CHARGEMENT:
* CONTRAINTE DE COMPRESSION IMPOSEE (ESSAI DE FLUAGE)
* TEMPERATURE CONSTANTE
* DENSITE DE FISSIONS CONSTANTE
* PRIMAIRE - MECANISMES 1 ET 2 - IRRADIATION
* DENSIFICATION - GONFLEMENT
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
GRAPH = FAUX ;
LISTCOUR = VRAI ;
NE = 1 ;
H = 1. ;
OO = 0. 0. ;
A1 = H 0. ;
A2 = H H ;
A3 = 0. H ;
LB = 'DROIT' NE OO A1 ;
LD = 'DROIT' NE A1 A2 ;
LH = 'DROIT' NE A2 A3 ;
LG = 'DROIT' NE A3 OO ;
SU1 = 'DALL' LB LD LH LG 'PLAN' ;
MODL1= MODE SU1 MECANIQUE ELASTIQUE
  VISCOPLASTIQUE GATT_MONERIE 'DPGE' OO ;
* Materiau GATT_MONERIE
TE1 = 1300. + 273. ;
PO = 4.9E-2 ;
DF1 = 1.E18 ;
TA = @GATTPAR ('CHAINE' DIVERS '/fichier_gatt') ;
TA.'BP' = 0. ;
TA.'POR0' = PO ;
TA.'CR' = 0.16E-2 ;
MATREE = MATE MODL1 'YOUN' (TA.'YOUN') ;
PP = 'MANU' 'CHML' MODL1 'T' TE1 'PORO' PO RIGIDITE ;
EE = 'VARI' 'NUAG' MODL1 MATREE PP ;
MATR11 = 'MATE' MODL1 'YOUN' EE 'NU' 0. 'RHO' 10950. 'ALPH' 0. 'TALP' 0. 'TREF' 1. ;
MATR12 = 'MATE' MODL1
 'R' (TA.'R') 'DG0' (TA.'DG0') 'DG' (TA.'DGCR')
 'K1' (TA.'K1') 'M1' (TA.'M1') 'Q1' (TA.'Q1') 'N1' (TA.'N1')
 'K2' (TA.'K2') 'M2' (TA.'M2') 'Q2' (TA.'Q2') 'N2' (TA.'N2')
 'OMEG' (TA.'OMEG') 'H' (TA.'H') 'Q' (TA.'Q') 'BETA' (TA.'BETA')
 'K' (TA.'K') 'A' (TA.'A') 'Q3' (TA.'Q3') 'N3' (TA.'N3')
 'CR' (TA.'CR') 'CR1' (TA.'CR1') 'CR2' (TA.'CR2') 'CR3' (TA.'CR3');
MATR13 = 'MATE' MODL1
 'KP' (TA.'KPAF') 'AP' (TA.'AP') 'BP' (TA.'BP') 'QP' (TA.'QP') ;
MATR14 = 'MATE' MODL1
 'ADEN' TA.'ADEN' 'KGON' TA.'KGON'.
 'POR0' (TA.'POR0') 'BUMI' (TA.'BUMI') 'EFIS' (TA.'EFIS') ;
* TYPE = 0. combustible UO2 sinon combustible AFA3GLAA
* COMP = 0. combustible incompressible sinon compressible
* DYN = 0. couplage dynamique sinon statique
MATR15 = 'MATE' MODL1 'TYPE' 1. 'COMP' 1. 'DYN' 1. ;
MATR16 = 'MATE' MODL1
         'DYN1' (TA.'DYN1') 'DYN2' (TA.'DYN2') 'DYN3' (TA.'DYN3') ;
MATR1 = MATR11 'ET' MATR12 'ET' MATR13 'ET' MATR14 'ET'
        MATR15 'ET' MATR16 ;
* Conditions aux limites
CLYB = 'BLOQ' 'UY' LB ;
CLXG = 'BLOQ' 'UX' LG ;
CLT = CLYB 'ET' CLXG ;
TMIL = 1.E6 ;
TFIN = 2.E6 ;
RHO0 = 1. - TA.'POR0' ;
AKBU = TA.'EFIS'*270./238./10950./RHO0*DF1 ;
* CE QUI SUIT EST VRAI CAR LE FLUX DE FISSIONS EST CONSTANT
TBU = (TA.'BUMI' / AKBU) - 1. ;
TTBU = ('ENTI' (TBU/10000.)) * 10000. ;
* Instants calcules
'SI' LISTCOUR ;
LIST1 = 'PROG' 0 'PAS' 0.1 1 'PAS' 1 10 'PAS' 10 100 'PAS' 100 1000
                  'PAS' 500 15000 ;
'SINON' ;
LIST1 = 'PROG' 0 'PAS' 0.1 1 'PAS' 1 10 'PAS' 10 100 'PAS' 100 1000
                  'PAS' 500 30000 ;
'FINSI' ;
* Chargement cte en temperature
CHTEMP = 'MANU' 'CHPO' SU1 1 'T' 1. ;
EVT = 'EVOL' 'MANU' ('PROG' 0. (2.*TFIN))
                         ('PROG' TE1 TE1) ;
CHARTEMP = 'CHAR' 'T' CHTEMP EVT ;
* Chargement cte en densite de fission
CHFISS = 'MANU' 'CHPO' SU1 1 'DFIS' 1. ;
EVF = 'EVOL' 'MANU' ('PROG' 0. (2.*TFIN))
                         ('PROG' DF1 DF1) ;
CHARFISS = 'CHAR' 'DFIS' CHFISS EVF ;
* Chargement en pression
valpres = 60E6 ;
compr = 'PRES' 'MASS' MODL1 valpres LH ;
EVP = 'EVOL' 'MANU' ('PROG' 0. 1. (2.*TFIN))
                         ('PROG' 0. 1. 1.) ;
CHARMECA = 'CHAR' 'MECA' compr EVP ;
CHARTOT = CHARMECA 'ET' CHARTEMP 'ET' CHARFISS ;
* Variables internes initiales 'PORO'=PO
VAR00 = 'ZERO' MODL1 'VARINTER' ;
VAR01 = 'MANU' 'CHML' MODL1 'PORO' PO
                            'TYPE' 'VARIABLES INTERNES' 'STRESSES' ;
VAR0 = VAR00 + VAR01 ;
TAB1 = TABLE ;
TAB1.'TEMPERATURES' = TABLE ;
TAB1.'VARIABLES_INTERNES'= TABLE ;
TAB1.'BLOCAGES_MECANIQUES' = CLT ;
TAB1.'MODELE' = MODL1 ;
TAB1.'CHARGEMENT' = CHARTOT ;
TAB1.'TEMPERATURES' . 0 = CHTEMP ;
TAB1.'VARIABLES_INTERNES' . 0 = VAR0 ;
TAB1.'CARACTERISTIQUES' = MATR1 ;
TAB1.'TEMPS_CALCULES' = LIST1 ;
TAB1.'TEMPS_SAUVES' = LIST1 ;
TMASAU = TABLE ;
tab1 . 'MES_SAUVEGARDES' = TMASAU ;
TMASAU .'DEFTO' = VRAI ;
TMASAU .'DEFIN' = VRAI ;
PASAPAS TAB1 ;
* CONTROLE DES RESULTATS
AP = TA.'AP' ;
BP = TA.'BP' ;
N1 = TA.'N1' ;
N2 = TA.'N2' ;
DG = TA.'DGCR' ;
* Facteurs multiplicatifs dus au dopage par le Chrome
WC1 = 'TANH' ( (TA.'CR' - TA.'CR2') / TA.'CR3' ) ;
WC1 = 1. + ( 0.5 * TA.'CR1' * (1. + WC1) ) ;
CV = 180. / PI ;
WC2 = 1. - ( 'COS' (CV * DG / TA.'DG0') ) ;
WC2 = 2. * (TA.'DG0'**TA.'M2') * WC2 ;
* Calcul de TO pour la fonction de couplage dynamique
TO = 'TANH' ( (TA.'DYN2' - TE1) / TA.'DYN3' ) ;
TO = TA.'DYN1' * (1. + TO) ;
TO = TO + 1. ;
BUMI = TA.'BUMI' ;
AKEVD = AKBU*TA.'KGON' ;
ADEN = TA.'ADEN' ;
KGON = TA.'KGON' ;
* Calcul de la cte AAAA intervenant ds le calcul de la def. de dens.
BUMAX0=60.D0*BUMI ;
CRIT=1.D-10 ;
'REPE' BLOC 100 ;
  BUMAX = BUMI* ('EXP' (1. - (ADEN/(KGON*BUMAX0)))) ;
  BUMAX = (0.2*BUMAX) + (0.8*BUMAX0) ;
  TEST='ABS' ((BUMAX-BUMAX0)/BUMAX0) ;
  'SI' ('<' TEST CRIT) ;
    'QUIT' BLOC ;
  'FINS' ;
  BUMAX0=BUMAX ;
'FIN' BLOC ;
AAAA = (-1.D0*RHO0*(ADEN-(KGON*BUMAX))) /
                ((1.D0+ADEN)*(LOG(BUMAX/BUMI))) ;
* Controle des resultats
SS = TAB1 . 'CONTRAINTES' ;
VV = TAB1 . 'VARIABLES_INTERNES' ;
IN = TAB1 . 'DEFORMATIONS_INELASTIQUES' ;
NCONT = ('DIME' (TAB1 . 'CONTRAINTES')) - 1 ;
ERMAX1 = 0. ;
ERMAX2 = 0. ;
Lzeit = 'PROG' ;
Lteta = 'PROG' ;
Lteta_c = 'PROG' ;
Lepsv = 'PROG' ;
Lepsv_c = 'PROG' ;
ind0 = 9 ;
zeit0 = 1. ;
epsv0 = 'MAXI' ('EXCO' IN.(ind0 + 1) 'EIYY') ;
'REPE' BLOC (NCONT - ind0) ;
  ind = ind0 + &BLOC ;
* SMYY = valpres ET LES AUTRES COMPOSANTES SONT NULLES
  SMYY = -1. * valpres ;
  SSM = SMYY / 3. ;
  SSEQ = 'ABS' SMYY ;
* Deviateur des contraintes
  SSPRIM2 = SMYY - SSM ;
* Contrainte YY calculee
  sy_c = 'MAXI' ('EXCO' SS.ind 'SMYY') ;
* VITESSE DE DEFORMATION VISCO-PLASTIQUE EVP D"ORIGINE THERMIQUE
* -- fluage primaire
  EVP02 = -1.5 * TA.'KPAF' *
   ('EXP' (-1.*TA.'QP'/(TA.'R'*TE1))) * (SSEQ**AP) ;
* -- fluage secondaire (2 mecanismes)
* on teste la porosite :
  PP = 'MAXI' ('EXCO' VV . &BLOC 'PORO') ;
  ECART1 = 'ABS' ((PP - PO) / PO) ;
  ERMAX1 = 'MAXI' ('PROG' ECART1 ERMAX1) ;
  A1 = (N1* (PP**(-1./N1) - 1.)**(-2.*N1/(N1+1.))) ;
  B1 = (1. + (2.*PP/3.))/ ((1. - PP) **(2.*N1/(N1+1.))) ;
  B1 = B1 + (A1/4.) ;
  A1 = 0. ;
  A2 = (N2* (PP**(-1./N2) - 1.)**(-2.*N2/(N2+1.))) ;
  B2 = (1. + (2.*PP/3.))/ ((1. - PP) **(2.*N2/(N2+1.))) ;
  B2 = B2 + (A2/4.) ;
  A2 = 0. ;
  EVP12 = 0.5 * (TA.'K1' * (DG**TA.'M1') * WC1 *
  ('EXP' (-1.*TA.'Q1'/(TA.'R'*TE1))) *
  (((A1*((1.5*SSM)**2)) + (B1*(SSEQ ** 2)))**((N1-1.)/2.)) *
  ((A1*1.5*SSM) + (3.*B1*SSPRIM2))) ;
  EVP22 = 0.5 * (TA.'K2' * WC2 * ('EXP' (-1.*TA.'Q2'/(TA.'R'*TE1))) *
  (((A2*((1.5*SSM)**2)) + (B2*(SSEQ ** 2)))**((N2-1.)/2.)) *
  ((A2*1.5*SSM) + (3.*B2*SSPRIM2))) ;
* FONCTION DE COUPLAGE STATIQUE
  TETA0 = 0.5 * TA.'BETA' *
      (1. +
      ('TANH' ((TE1 - (TA.'OMEG' * (SSEQ**(-1.*TA.'Q')))) / TA.'H'))) ;
* FONCTION DE COUPLAGE DYNAMIQUE
  zeit = TAB1.'TEMPS'.ind ;
  duree = zeit - zeit0 ;
  TETA = ( 1. + (zeit/TO) ) ** -1 ;
  TETA = TETA0 * (1. - TETA) ;
* Fonction de couplage dynamique calculee
  teta_c = 'MAXI' ('EXCO' VV.ind 'TETA') ;
* VITESSE DE DEFORMATION IRRADIATION
  EVIR2 = 1.5 * TA.'A' * DF1 * (SSEQ **(TA.'N3' - 1.)) *
       ('EXP' (-1.*TA.'Q3'/(TA.'R'*TE1))) * SSPRIM2 ;
* DEFORMATION VISCO-PLASTIQUE SELON YY
 KFI = 1.+(TA.'K'*DF1) ;
 EPSVa = EVIR2 + ( KFI * (EVP02+EVP12) ) ;
 EPSVb = KFI * (EVP22 - EVP12) ;
 INTGTETA = 'LOG' ( 1. + (duree/TO) ) ;
 INTGTETA = TO * INTGTETA ;
 INTGTETA = TETA0 * (duree - INTGTETA) ;
 epsv = (EPSVa * duree) + (EPSVb * INTGTETA) ;
 epsv = epsv0 + epsv ;
* Deformation viscoplastique calculee
 epsv_c = 'MAXI' ('EXCO' IN.ind 'EIYY') ;
* On teste la deformation viscoplastique :
     ECART2 = 'ABS' ((epsv_c - epsv) / epsv) ;
     ERMAX2 = 'MAXI' ('PROG' ECART2 ERMAX2) ;
  Lzeit = Lzeit 'ET' ('PROG' zeit) ;
  Lteta = Lteta 'ET' ('PROG' TETA) ;
  Lteta_c = Lteta_c 'ET' ('PROG' teta_c) ;
  Lepsv = Lepsv 'ET' ('PROG' epsv) ;
  Lepsv_c = Lepsv_c 'ET' ('PROG' epsv_c) ;
'FIN' BLOC ;
  'SI' (ERMAX1 '<EG' 1E-5) ;
     'ERRE' 0 ;
  'SINO' ;
     'MESS' 'POROSITE NON CONSTANTE' ;
     'MESS' 'ERREUR MAXIMALE POROSITE :'
             ERMAX1 '> 1E-5 ' ;
     'ERRE' 5 ;
  'FINS' ;
'SI' ( ERMAX2 '<EG' 0.05) ;
   'ERRE' 0 ;
'SINO' ;
   'MESS' 'ERREUR MAXIMALE DEFORMATION VISCOPLASTIQUE :'
           ERMAX2 '> 0.05 ' ;
   'ERRE' 5 ;
'FINS' ;
'SI' GRAPH ;
 'TITR' 'Deformations planes general. : Fonction de couplage dynamique';
 EVTETA = 'EVOL' 'MANU' 'Temps' Lzeit 'TETA' Lteta ;
 EVTETA_C = 'EVOL' 'MANU' 'Temps' Lzeit 'TETA' Lteta_c ;
 TAD = TABLE ;
 TAD . 1 = 'TIRC' ;
 TAD . 2 = 'TIRR' ;
 TAD . 'TITRE' = TABLE ;
 TAD . 'TITRE' . 1 = 'TETA THEORIQUE' ;
 TAD . 'TITRE' . 2 = 'TETA CALCULEE' ;
 'DESS' (EVTETA 'ET' EVTETA_C) TAD 'LEGE' ;
  'TITR' 'Deformations planes general. : Deformation viscoplastique' ;
  EVEPSV = 'EVOL' 'MANU' 'Temps' Lzeit 'EPSV' Lepsv ;
  EVEPSV_C = 'EVOL' 'MANU' 'Temps' Lzeit 'EPSV' Lepsv_c ;
  TAD = TABLE ;
  TAD . 1 = 'TIRC' ;
  TAD . 2 = 'TIRR' ;
  TAD . 'TITRE' = TABLE ;
  TAD . 'TITRE' . 1 = 'EPSV THEORIQUE' ;
  TAD . 'TITRE' . 2 = 'EPSV CALCULEE' ;
  'DESS' (EVEPSV 'ET' EVEPSV_C) TAD 'LEGE' ;
'FINS' ;
'FIN';
```

## hbm_jeffcott_contact [(sans section)]
```
* Systeme a deux ddl
* ROTOR JEFFCOTT AVEC CONTACT ROTOR-STATOR
* m x + c x + k x = Fbal*cos wt + Fchoc_x
* m y + c y + k y = Fbal*sin wt + Fchoc_y
* modele de contact :
* Fn = -{r-jeu}+ kchoc
* Ft = µ|Fn|sign(vrel)
* Continuation + HBM + AFT
* CHARMECA.PROCEDUR
* Calcul de la force non lineaire fnl(x,t) et de sa derivee dfnl(x,t)/dx
* dans le domaine temporel
* EN ENTREE :
* TAB1
* >> parametres génériques :
* . 'DEP_NL' : LISTCHPO DE DEPLACEMENTS TEMPORELLES
* ou (pas encore programmé)
* . i . 'CHPOINT' = CHPOINT unitaire des deplacements NL
* . i . 'LISTREEL' = evolution temporelle coefficient du chpoint
* >> parametres propres a ce cas test :
* . 'COEFF_FNL' : coefficient de non linearite
* . 'POINT_FNL' : point de non linearite
* . 'COMP_FNL' : composante de non linearite
* EN SORTIE :
* TAB1
* >> parametres génériques :
* . 'FNL_T' : LISTCHPO DES FORCES NON LINEAIRES TEMPORELLES
* ou TABLE d'indice : (pas encore programmé)
* . i . 'CHPOINT' = CHPOINT unitaire des forces non lineaires
* . i . 'LISTREEL' = evolution temporelle coefficient du chpoint
* . 'KNL_T' : DERIVEE DE FORCES NON LINEAIRES sous forme de TABLE :
* . i . j = 'LISTREEL' evolution temporelle de dFi/dxj
DEBPROC CHARMECA TAB1*'TABLE';
* parametres d'entree propres a ce cas test
* coefficient de la force nl
SI (EXIS TAB1 . 'COEFF_FNL');
  pmu = EXTR TAB1 . 'COEFF_FNL' 1;
  pkc = EXTR TAB1 . 'COEFF_FNL' 2;
  ph0 = EXTR TAB1 . 'COEFF_FNL' 3;
SINON;
  MESS 'CHARMECA: IL MANQUE Les COEFF_FNL'; ERRE 21;
FINSI;
SI (EXIS TAB1 . 'POINT_FNL');
  pNL = TAB1 . 'POINT_FNL';
SINON;
  MESS 'CHARMECA: IL MANQUE LA GEOMETRIE NL dans POINT_FNL'; ERRE 21;
FINSI;
SI (EXIS TAB1 . 'COMP_FNL');
  COMP_FNL = TAB1 . 'COMP_FNL';
  n_CNL = DIME COMP_FNL;
SINON;
  MESS 'CHARMECA: IL MANQUE LA COMPOSANTE NL dans COMP_FNL'; ERRE 21;
FINSI;
* parametres d'entree génériques
* DEPNL : list de champ par points, deplacements temporels du point nl
SI (EXIS TAB1 'DEP_NL');
  DEPNL = TAB1 . 'DEP_NL';
  IFCHPO = ega (type DEPNL) 'LISTCHPO';
  si (non IFCHPO);
    si (neg (type DEPNL) 'TABLE');
      mess 'CHARMECA: DEP_NL doit etre de type LISTCHPO ou TABLE';
      ERRE 21;
    sinon;
      si (neg (type DEPNL . 1) 'LISTREEL');
        mess 'CHARMECA: DEP_NL . i doit etre un LISTREEL';
        ERRE 21;
      finsi;
    finsi;
  finsi;
SINON;
  MESS 'CHARMECA: IL MANQUE LA LISTE DES DEPLACEMENTS dans DEP_NL';
  ERRE 21;
FINSI;
* calcul de fnl ET dfnl/dx ? dans le doute on calcule tout...
SI (NEG (TYPE IFFNL) 'LOGIQUE'); IFFNL = VRAI; FINSI;
SI (NEG (TYPE IFKNL) 'LOGIQUE'); IFKNL = VRAI; FINSI;
* Calcul de FNL
* nb: nombre de pas de temps
* NCNL : nombre de composantes pour la force nl
nb = DIME DEPNL;
FNLTEMP = VIDE 'LISTCHPO';
fxrp = prog ; fyrp =prog ;
dfxdxp = prog ; dfxdyp = prog ; dfydxp = prog ; dfydyp = prog ;
LST_R0 = PROG; LST_X0 = PROG; LST_Y0 = PROG;
NCNL = DIME COMP_FNL;
CNL1 = mot (EXTR COMP_FNL 1);
CNL2 = mot (EXTR COMP_FNL 2);
* BOUCLE POUR CONSTRUIRE le LISTREEL EXCENTRICITE(t)
  ib = 0;
  REPE bfor nb; ib = ib + 1;
    DEP_i0 = EXTR DEPNL ib;
    DEP_X0 = EXTR DEP_i0 pNL CNL1;
    DEP_Y0 = EXTR DEP_i0 pNL CNL2;
* mess 'x,y = ' DEP_X0 DEP_Y0;
    LST_X0 = LST_X0 ET DEP_X0;
    LST_Y0 = LST_Y0 ET DEP_Y0;
* EXCENTRICITE
    R0 = ((DEP_X0**2) + (DEP_Y0**2))**0.5;
    LST_R0 = LST_R0 ET R0;
  FIN bfor;
* ---------- BOUCLE POUR CALCULER LA FORCE NL -----------
  ib = 0;
  REPE Blst nb; ib = ib + 1;
    DEP_X0 = EXTR LST_X0 ib;
    DEP_Y0 = EXTR LST_Y0 ib;
    R0 = EXTR LST_R0 ib;
    SI (R0 <EG ph0);
      fxr = 0.;
      fyr = 0.;
      si IFKNL;
        dfxdx = 0. ;
        dfxdy = 0. ;
        dfydx = 0. ;
        dfydy = 0. ;
      finsi;
    SINON;
      fn = -1. * pkc * (R0 - ph0);
      ft = pmu * fn;
* car on suppose que v_tangentielle_relative >0
* (hyp : vitesse de roation >> deplacement du centre du disque)
      costet1 = DEP_X0 / R0;
      sintet1 = DEP_Y0 / R0;
      fxr = (fn * costet1) - (ft * sintet1);
      fyr = (fn * sintet1) + (ft * costet1);
      si IFKNL;
      cstet1 = costet1*sintet1;
      costet2 = costet1**2;
      sintet2 = sintet1**2;
      unmjeu1 = 1. - (ph0/R0);
      A1 = 1. - (ph0/R0 * sintet2);
      B1 = ph0/R0 * cstet1;
      C1 = B1;
      D1 = 1. - (ph0/R0 * costet2);
      dfxdx = pkc * ( A1 - (pmu * B1));
      dfxdy = pkc * ( C1 - (pmu * D1));
      dfydx = pkc * ( B1 + (pmu * A1));
      dfydy = pkc * ( D1 + (pmu * C1));
* On fournit en realite les termes de Knl = - dF/dX
      finsi;
    FINSI;
    fxrp = fxrp et fxr;
    fyrp = fyrp et fyr;
    FNLTEMP = FNLTEMP ET
             (MANU 'CHPO' pNL 2 CNL1 fxr CNL2 fyr 'NATURE' 'DISCRET');
    si IFKNL;
      dfxdxp = dfxdxp et dfxdx;
      dfxdyp = dfxdyp et dfxdy;
      dfydxp = dfydxp et dfydx;
      dfydyp = dfydyp et dfydy;
    finsi;
  FIN Blst;
* mess 'f^nl = ' fxr fyr;
* mess 'dfnl/du=' dfxdx dfxdy dfydx dfydy;
TAB1 . 'FNL_T' = FNLTEMP;
TAB1 . 'KNL_T' = table;
si IFKNL;
  TAB1 . 'KNL_T' . 1 = tabl;
  TAB1 . 'KNL_T' . 2 = tabl;
  TAB1 . 'KNL_T' . 1 . 1 = dfxdxp;
  TAB1 . 'KNL_T' . 1 . 2 = dfxdyp;
  TAB1 . 'KNL_T' . 2 . 1 = dfydxp;
  TAB1 . 'KNL_T' . 2 . 2 = dfydyp;
finsi;
fprog = (fxrp**2 + fyrp**2)**0.5;
fnlmax = MAXI fprog 'ABS';
si (EXIS TAB1 'FNLMAX'); fnlmax0 = TAB1 . 'FNLMAX';
sinon; fnlmax0 = 0.;
finsi;
* si chgt brusque (mise en contact ou perte de contact), on actualise K
si ( ((fnlmax > 1.E-50) et (fnlmax0 < 1.E-50))
  OU ((fnlmax < 1.E-50) et (fnlmax0 > 1.E-50)) );
* mess 'contact detecté !';
  WTAB . 'RECA_K' = VRAI;
finsi;
TAB1 . 'FNLMAX' = fnlmax;
TAB1 . 'EXCENTRICITE' = (MAXI (ABS LST_R0));
FINPROC;
* DEBUT DU CALCUL
* opti echo 0 ;
opti debug 1;
graph = faux ;
OPTI DIME 2 ELEM SEG2 MODE PLAN CONT ;
GRAPH = FAUX ; SAVE = FAUX; TNR = VRAI;
* GRAPH = VRAI ; SAVE = VRAI; TNR = FAUX;
* -------- Definition des options du calcul :
* complet = faux;
* CALCUL PAR DFT ? (Transformation de Fourier Discret
CALC_DFT = FAUX;
* si analyser la stabilite?
OP_STAB = FAUX;
* si adimensionnement du temps?
* Adim_t = VRAI;
* -------- Definition des parametres du calcul --------
* nombre d'harmoniques
 nhbm = 3 ;
* nhbm = 7 ;
* nhbm = 9 ;
* nhbm = 11 ;
* nhbm = 15 ;
* plage d'etude de frequence en Hz
t0 = 0.0;
t1 = 10.;
dt = 0.10;
* des iterations
itmoy = 6;
ds = 1.;
dsmax = 1.;
dsmin = 1.E-3 ;
* si AFT, OTFR: nb de points 2**OTFR pour TFR
* OTFR = 7;
OTFR = ENTI 'SUPERIEUR' (log (2 * (2 * nhbm + 1)) / (log 2));
mess 'OTFR = ' OTFR;
* -------- Definition des parametres du contact ---------------
* coefficient de frottement
pmu = 0.11 ;
si (pmu ega 0.00 1.E-4); mopmu = mot '000'; finsi;
si (pmu ega 0.05 1.E-4); mopmu = mot '005'; finsi;
si (pmu ega 0.11 1.E-4); mopmu = mot '011'; finsi;
si (pmu ega 0.15 1.E-4); mopmu = mot '015'; finsi;
si (pmu ega 0.20 1.E-4); mopmu = mot '020'; finsi;
si (pmu ega 0.25 1.E-4); mopmu = mot '025'; finsi;
* rigidite du contact
pkc = 2500. ;
* pkc = 0.;
* jeu initial
ph0 = 0.105 ;
* parametre de l'adimensionnement = 20% du jeu
u1max = 0.20*ph0;
* ---------Definition des parametres du rotor --------
* masse constant
pmass = 1. ;
* amortissement
pamor = 5. ;
* rigidite
prigi = 100. ;
* force du balourd
pbal = 0.1;
* frequences caracteristiques du pb (en Hz)
w0 = (prigi/pmass)**0.5 / (2.*pi);
w0c = ((prigi+pkc)/pmass)**0.5 / (2.*pi);
wc = ((pkc)/pmass)**0.5 / (2.*pi);
mess w0 w0c wc;
* prefix :
prefix = chai 'hbm_jeffcott_contact_' mopmu '_n' nhbm ;
TITRE prefix;
si GRAPH;
  ficps = chai prefix '.ps';
  opti TRAC PSC EPTR 6 POTR 'HELVETICA_16' 'FTRA' ficps;
finsi;
* ------------- geometrie --------
P1 = 0. 0. ; P2 = 1. 0. ;
* ----------- construction des matrices caracteristiques ----------
* OPTI DONN 5;
LIM1 = MOTS UX UY;
MASS1 = (MASS 'UX' pmass P2 ) ET (MASS 'UY' pmass P2 );
RI1 = MANU 'RIGI' P2 LIM1 (prog prigi 0. 0. prigi);
AMOR1 = MANU 'RIGI' P2 LIM1 (prog pamor 0. 0. pamor);
* ------- on définit une unique table pour tout (HBM et CONTINU) -------
TAB1 = TABLE ;
* --------- remplissage des matrices "temporelles" ---------
* TAB1 . 'MASSE_CONSTANTE' = MASS1 ;
* TAB1 . 'AMORTISSEMENT_CONSTANT' = AMOR1 ;
* ATTENTION AUX UNITES : ON VA TRAVAILLER EN Hz => mettre le 2pi ici
TAB1 . 'MASSE_CONSTANTE' = (2.*pi **2) * MASS1 ;
TAB1 . 'AMORTISSEMENT_CONSTANT' = (2.*pi) * AMOR1 ;
TAB1 . 'RIGIDITE_CONSTANTE' = RI1 ;
TAB1 . 'N_HARMONIQUE' = nhbm;
* ------- remplissage des resultats attendus sur ddls "temporels" -------
mycoul6 = MOTS 'VIOL' 'BLEU' 'BLEU' 'TURQ' 'TURQ' 'VERT' 'VERT'
                      'OLIV' 'OLIV' 'JAUN' 'JAUN' 'ORAN' 'ORAN'
                      'ROUG' 'ROUG' 'ROSE' 'ROSE' ;
mycoul6 = mycoul6 et (MOTS 24*'GRIS');
TAB1 . 'RESULTATS' = tabl;
TAB1 . 'RESULTATS' . 1 = tabl;
TAB1 . 'RESULTATS' . 1 . 'POINT_MESURE' = P2;
TAB1 . 'RESULTATS' . 1 . 'COMPOSANTE' = mot 'UX';
TAB1 . 'RESULTATS' . 1 . 'TITRE' = mot 'UX';
TAB1 . 'RESULTATS' . 1 . 'COULEUR' = mot 'BLEU';
TAB1 . 'RESULTATS' . 1 . 'COULEUR_HBM' = mycoul6;
TAB1 . 'RESULTATS' . 2 = tabl;
TAB1 . 'RESULTATS' . 2 . 'POINT_MESURE' = P2;
TAB1 . 'RESULTATS' . 2 . 'COMPOSANTE' = mot 'UY';
TAB1 . 'RESULTATS' . 2 . 'TITRE' = mot 'UY';
TAB1 . 'RESULTATS' . 2 . 'COULEUR' = mot 'ROSE';
TAB1 . 'RESULTATS' . 2 . 'COULEUR_HBM' = mycoul6;
* --------- passage en frequentiel ---------
  HBM TAB1;
MESS '>>>>>>>>>>>>>>>COMPOSANTES DEP TEMPORELLES D UN NOEUD';
LIST TAB1 . 'COMPOSANTES' . 'DEPLACEMENT';
MESS '>>>>>>>>>>>>>>>COMPOSANTES DEP FREQUENTIELLES D UN NOEUD';
LIST TAB1 . 'COMPOSANTES' . 'DEPLACEMENT_HBM';
* ----------- definition du chargement -----------------------------------
* ici, on definit directement le chargement en frequentiel
FP11 = MANU 'CHPO' p2 2 'F3' pbal 'G4' (pbal) 'NATURE' 'DISCRET';
LIX1 = PROG 0. pas 0.1 (t1+30.) ;
* ATTENTION AUX UNITES : ON VA TRAVAILLER EN Hz => mettre le 2pi ici
LIY1 = (2.*pi*LIX1)**2 ;
EV1 = EVOL MANU 't' LIX1 'F(t)' LIY1 ;
CHA1 = CHAR 'MECA' FP11 EV1 ;
si GRAPH;
  dess EV1 POSX CENT POSY CENT ;
finsi;
* ----------- resolution par la procedure CONTINU -----------------------
* OPTIONS DE CALCULS
TAB1 . 'CHARGEMENT' = CHA1;
* calcul des forces NL
TAB1 . 'PROCEDURE_CHARMECA'= VRAI ;
TAB1 . 'PROCEDURE_FREQUENCE_TEMPS' = mot 'AFT';
TAB1 . 'N_PT_TFR' = OTFR;
TAB1 . 'CALC_CHPO' = VRAI;
* TAB1 . 'CALC_CHPO' = faux; -> charmeca pas prevu !
* plage de frequence en Hz
LIS1T = prog t0 PAS dt t1;
TAB1 . 'TEMPS_CALCULES' = LIS1T;
TAB1 . 'MAXIPAS' = 500;
TAB1 . 'MAXIPAS' = 300;
TAB1 . 'PRECISION' = 1.E-5;
TAB1 . 'ACCELERATION' = 4;
* ------parametres du contact
TAB1 . 'COEFF_FNL' = PROG pmu pkc ph0;
TAB1 . 'POINT_FNL' = P2;
TAB1 . 'COMP_FNL' = mots 'UX' 'UY';
* ------parametres du continuation
TAB1 . 'NB_ITERATION' = itmoy;
TAB1 . 'MAXITERATION' = 30;
TAB1 . 'WTABLE' = tabl;
TAB1 . 'WTABLE' . 'DS' = ds;
TAB1 . 'WTABLE' . 'DSMAX' = dsmax;
TAB1 . 'WTABLE' . 'DSMIN' = dsmin;
TAB1 . 'MAXI_DEPLACEMENT' = u1max;
TAB1 . 'MAXSOUSPAS' = 3;
* resultats a sortir
* TAB1 . 'RESULTATS' = TRES1;
* stabilité
TAB1 . 'STABILITE' = vrai;
* opti debug 1 ;
TEMP ZERO;
* calcul avec continuation
CONTINU TAB1;
TEMP 'IMPR' 'MAXI' 'CPU';
* ---------------------- sauv avant reprise ----------------------------
* ficxdr = chai prefix '-avantREPRISE.xdr';
* mess ficxdr;
* opti sauv ficxdr;
* sauv ;
* ------------------------- reprise -----------------------------
* on impose l'absence de contact
TAB1 . 'COEFF_FNL' = PROG (0.*pmu) (0.*pkc) (1E6*ph0);
* on fait croire qu'on vient dans la direction opposee de maniere
* a etre capable de traiter le point de rebroussement
WTAB1 = TAB1 . 'WTABLE';
* OUBL TAB1 'WTABLE';
list WTAB1;
WTAB2 = TABL ;
WTAB2 . 'DTIME0' = -1. * WTAB1 . 'DTIME0';
WTAB2 . 'DDEP0' = -1. * WTAB1 . 'DDEP0';
TAB1 . 'WTABLE' = WTAB2;
CONTINU TAB1;
* ------------------------- post-traitement -----------------------------
* tracé de toutes les harmoniques individuellement
wprog = TAB1 . 'TEMPS_PROG';
* wprog = (extr evtot cour 1) extr ABSC;
evtot = TAB1 . 'RESULTATS_HBM' . 'RESULTATS_EVOL';
TDESS1 = TABL;
TDESS1 . 'TITRE' = TAB1 . 'RESULTATS_HBM' . 'TITRE';
si GRAPH;
  dess evtot
      TITX '\w(Hz)' POSX CENT
      TITY 'U_{k}' POSY CENT TDESS1 'LEGE';
  dess evtot YBOR -0.5 0.3 XBOR 0. 12
      TITX '\w(Hz)' POSX CENT
      TITY 'U_{k}' POSY CENT TDESS1 'LEGE';
finsi;
* traduction des resultats frequentiels en temporels
HBM_POST TAB1;
* tracé du max d'amplitude max_t(u(t))
evuyamp = TAB1 . 'RESULTATS' . 'RESULTATS_EVOL';
evuyamp1 = extr evuyamp COUR 1;
TDESS2 = TABL;
TDESS2 . 2 = mot 'TIRR';
TDESS2 . 'TITRE' = TAB1 . 'RESULTATS' . 'TITRE';
si GRAPH;
  dess evuyamp1
      TITX '\w(Hz)' POSX CENT
      TITY 'max|U(t)|' POSY CENT TDESS2 LEGE 'NO';
  dess evuyamp1
      TITX '\w(Hz)' POSX CENT
      TITY 'max|U(t)|' POSY CENT TDESS2 LEGE ;
finsi;
* tracé du max d'amplitude avec la stabilite !
istab = TAB1 . 'RESULTATS_STABILITE' . 'FLOQ' . 'STABILITE';
Tdess2 = TABL;
Tdess2 . 'LIGNE_VARIABLE' = TABL;
Tdess2 . 'LIGNE_VARIABLE' . 1 = istab;
si GRAPH;
  dess evuyamp1
      TITX '\w(Hz)' POSX CENT
      TITY 'max|U(t)|' POSY CENT Tdess2;
  Tdess2 . 1 = mot 'MARQ S PLUS';
  dess evuyamp1
      TITX '\w(Hz)' POSX CENT
      TITY 'max|U(t)|' POSY CENT Tdess2;
finsi;
* autres tracé de la stabilite : lambda_R en fonction de W
mycoul = mots 'VIOL' 'BLEU' 'AZUR' 'TURQ' 'VERT' 'OLIV'
              'JAUN' 'ORAN' 'ROUG' 'ROSE';
ncoul = dime mycoul;
wprog2 = enle wprog (dime wprog);
evlitot = VIDE 'EVOLUTIO' ;
evlrtot = VIDE 'EVOLUTIO' ;
nl = dime TAB1 . 'RESULTATS_STABILITE' . 'FLOQ' . 'EXPOSANT_REEL';
il = 0;
icoul = 0;
repe bl nl; il = il + 1; icoul = icoul + 1;
  si(icoul > ncoul); icoul = 1; finsi; coul1 = extr mycoul icoul;
  lr1 = TAB1 . 'RESULTATS_STABILITE' . 'FLOQ' . 'EXPOSANT_REEL' . il;
  evlrtot = evlrtot
  et (evol coul1 MANU '\w (Hz)' wprog2 '\l_{R}' lr1);
  li1 = TAB1 . 'RESULTATS_STABILITE' . 'FLOQ' . 'EXPOSANT_IMAG' . il;
  evlitot = evlitot
  et (evol coul1 MANU '\w (Hz)' wprog2 '\l_{I}' li1);
fin bl;
wprog3 = prog (mini wprog2) (maxi wprog2);
evzero = evol manu '\w (Hz)' wprog3 '\l_{R}' (0.*wprog3);
Tdess3 = tabl;
Tdess3 . 1 = mot 'TIRR';
si GRAPH;
  dess (evzero et evlrtot) 'TITY' '\l_{R} (s^{-1})' Tdess3;
  dess (evlitot) 'TITY' '\l_{I} (Hz)' ;
finsi;
* stabilite : trace dynamique pour faire une animation
si GRAPH;
  ficps = chai prefix '-ORBITE.ps';
  opti 'FTRA' ficps;
  TABORB = tabl;
  TABORB . 'PAS' = 3;
  TABORB . 'QUEUE' = MOT 'INFINIE';
  TABORB . 'EVOL_FIXE' = evzero ;
  ORBITE evlrtot TABORB;
finsi;
* ------------------------- sauvegarde -----------------------------
si SAVE ;
  ficxdr = chai prefix '.xdr';
  mess ficxdr;
  opti sauv ficxdr;
  sauv ;
finsi;
* --------------------- test de non regression ---------------------
si TNR ;
* reference : these de Lihan Xie fig3.10 page 84
* sauf qu'ici, on ne prend que 3 harmoniques
* recup valeurs de la courbes de reponse
  wamp = extr evuyamp 'ABSC' 1;
  wadim = wamp / wc;
  uyamp = extr evuyamp 'ORDO' 1;
  ramp = uyamp;
* R=UY puisque l'on a des orbites circulaires,
* sinon il faudrait calculer r(t)=uy(t)**2+uz(t)**2 , puis R=max(r(t))
  namp = DIME wamp;
* recherche de la mise en contact
  idebut = POSI 1 'DANS' (ENTI (MASQ ramp EGSUPE ph0));
  wdeb0 = extr wadim (idebut - 1);
  wdeb1 = extr wadim idebut;
  si ((wdeb0 > 0.16) ou (wdeb1 < 0.16));
    mess 'Mise en contact devrait se produire vers w/w0~0.16 !';
    mess 'PB car : ' wdeb0 ' < 0.16 < 'wdeb1 '  non verifie !';
    ERRE 5;
  finsi;
* verification que le calcul a bien attenit les w=10Hz
  wmax = maxi wamp;
  si (wmax < 10.);
    mess 'On devrait calculer jusqu a 10Hz au moins !';
    mess wmax;
    ERRE 5;
  finsi;
* verification de l'amplitude max atteinte
* rem : rmax = 4.4807 lors de la creation du cas test,
* mais on arrondit pour rref
  rmax = (maxi uyamp) / ph0;
  rref = 4.5 ;
  si ((ABS (rmax - rref)) > 0.05);
    mess 'Le max|U| devrait etre de ' rref ' !';
    mess rmax;
    ERRE 5;
  finsi;
* recherche des changements de stabilite
  istab1 = (istab enle 1) - (istab enle (DIME istab));
  istab1 = (posi 1 'DANS' istab1 'TOUS')
         et (posi -1 'DANS' istab1 'TOUS');
  si (neg (dime istab1) 4);
    mess 'Il devrait y avoir 4 points de changement de stabilite !';
    list istab1;
    ERRE 5;
  finsi;
finsi;
fin ;
```

## hotan [(sans section)]
```
* Option de calcul
OPTI 'DIME' 2 ELEM TRI3 MODE PLAN DEFO;
* OPTI TRAC OPEN;
OPTI 'SAUV' 'FORMAT' 'XDR' SAVING;
OPTI SORT 'RES' ;
* Parametres geometriques
L1 = 1. ;
R1 = 0.15 ;
* Maillage
* DENmail0 = R1 / 15. ;
* DENS2 = L1 / 15. ;
P0 = 0. 0. ;
P1 = R1 0. ;
P2 = L1 0. ;
P3 = L1 L1 ;
P4 = 0. L1 ;
P5 = 0. R1 ;
CER = CERC 15 P5 P0 P1 ;
L1 = DROI 20 P1 P2 ;
L2 = DROI 20 P2 P3 ;
L3 = DROI 20 P3 P4 ;
L4 = DROI 20 P4 P5 ;
C1 = CER ET L1 ET L2 ET L3 ET L4;
mail0 = SURF PLAN C1;
* Tracer le maillage
* TRAC mail0;
* Nombre de noeuds et d'éléments
nbno0 = nbno mail0 ; mess 'Nombre de noeuds :' nbno0 ;
nbel0 = nbel mail0 ; mess 'Nombre d éléments :' nbel0 ;
* Modèle élasto-plastique Von Mises à l'écrouissage isotrope
* Courbe de traction à déclarer. Limite d'élasticité 237 MPa
x = prog 0. 0.00112860 0.024 0.031 0.039 0.047 0.054
          0.062 0.070 0.077 0.086 0.095 0.104 0.112 ;
* 0.00112860
y = prog 0. 237. 266. 282. 296. 308. 318.
          327. 335. 342. 350. 355. 360. 364.;
* opti donn 5 ;
* Courbe d'ecrouissage : a priori, le 1er point donne Sy
epsy1 = extr x 2 ;
lep = (x enle 1) - epsy1 ;
lsig1 = y enle 1 ;
x = lep ; y = lsig1 ;
* Conversion de l'unité de contraintes (MPa)
y = y * 1.E6;
* Créer et tracer la courbe de traction
xy = evol roug manu x y ;
* dess xy titx 'Déformation' tity 'Contrainte [MPa]' ;
mod0 = MODELE mail0 'MECANIQUE' 'ELASTIQUE' 'PLASTIQUE' 'ISOTROPE';
mat0 = MATE mod0 'YOUN' 210E9 'NU' 0.30 'ECRO' xy;
* Modèle J2 pour contourner la déclaration d'une courbe de traction
* mod0 = MODELE mail0 'MECANIQUE' 'ELASTIQUE' 'PLASTIQUE' 'J2';
* mat0 = MATE mod0 'YOUN' 210E9 'NU' 0.30 'SIG0' 250E6 'KISO' 21E9 'SIGI' 400E6 'VELO' 0;
* mod0 = MODELE mail0 MECANIQUE 'ELASTIQUE' 'NON_LINEAIRE' 'EQUIPLAS'; ce truc est pour l'élasticité non linéaire
* Conditions aux limites
CLB = BLOQ L1 'UY';
CLG = BLOQ L4 'UX';
CL = CLB ET CLG;
* Chargement évolutive
* On se donne une sollicitation pendant 10s. Une charge/décharge qui monte linéairement
* jusqu'à 250MPa et puis descend à 0.
timestep = 0.5;
time1 = PROG 0.0 PAS timestep 5.0 ;
time2 = PROG 5.0 PAS timestep 10.0 ;
time = PROG 0.0 PAS timestep 10.0;
Pext1 = prog 'LINE' 'A' 45E6 'B' 0 time1;
Pext2 = prog 'LINE' 'A' -45E6 'B' 450E6 time2;
ev1 = evol manu 'Temps' time1 'Pression' Pext1;
ev2 = evol manu 'Temps' time2 'Pression' Pext2;
* dess ev1;
* dess ev2;
ev = CONCAT ev1 ev2;
* dess ev;
PRES1 = PRES 'MASS' mod0 -1.0 L2;
Charge1 = CHAR MECA PRES1 ev;
Vec = VECT PRES1 'FORC';
* TRAC Vec mail0;
RIG1 = RIGI mod0 mat0;
RIG1 = RIG1 ET CL;
* Initialisation de la table de calcul
 SAVING_TBL = TABLE ;
 SAVING_TBL . 'DEFIN' = VRAI;
 SAVING_TBL . 'DEFTO' = VRAI;
 SAVING_TBL . 'DEFLO' = FAUX;
 SAVING_TBL . 'ROTAF' = FAUX;
tab1 = TABLE ;
tab1.BLOCAGES_MECANIQUES = CL ;
tab1.MODELE = mod0 ;
tab1.RIGI=RIG1;
tab1.CARACTERISTIQUES = mat0 ;
tab1.CHARGEMENT = Charge1 ;
tab1.TEMPS_CALCULES = time ;
tab1.TEMPS_SAUVES = time;
tab1.TEMPS_SAUVEGARDES = time;
tab1.MES_SAUVEGARDES=SAVING_TBL;
* tab1.K_TANGENT = VRAI;
* tab1.K_TANGENT_SYME = VRAI;
* Calcul
PASAPAS tab1;
* Post-traitement (juste pour tester)
dd1 = tab1 . DEPLACEMENTS ;
td1 = dd1 . 0 ;
td2 = dd1 . 9 ;
td3 = dd1 . 20 ;
Def0 = DEFO mail0 td1 100. BLANC ;
Def1 = DEFO mail0 td2 100. ROUGE;
def2 = DEFO mail0 td3 100. BLEU ;
TITRE 'Déformée Blanc = ini , Rouge = milieu , Bleu = fin ' ;
* TRAC ( Def0 ET Def1 ET Def2 ) QUAL ;
* Export des résultats vers un fichier inp.
Pasmabou = 1 ;
REPETER mabou 20 ;
SIG_G = tab1 . CONTRAINTES . Pasmabou ;
EPS_G = tab1 . DEFORMATIONS . Pasmabou;
EPSP_G = tab1 . VARIABLES_INTERNES . Pasmabou;
* vmis1 = VMIS mod0 SIG_G ;
SIGXX = EXCO SIG_G SMXX;
SIGYY = EXCO SIG_G SMYY;
SIGXY = EXCO SIG_G SMXY;
EPSXX = EXCO EPS_G EPXX;
EPSXY = EXCO EPS_G EPYY;
GAMXY = EXCO EPS_G GAXY;
* EPSXY = GAMXY/2;
MAT_TAN = HOTA mod0 SIG_G EPSP_G mat0;
SORT 'AVS' mail0 SIGXX 'SUIT' 'TEMP' Pasmabou;
SORT 'AVS' mail0 SIGYY 'SUIT' 'TEMP' Pasmabou;
SORT 'AVS' mail0 SIGXY 'SUIT' 'TEMP' Pasmabou;
Pasmabou = Pasmabou + 1 ;
FIN mabou;
FIN;
```

## hy2 [(sans section)]
```
* --- 2 JUIN 1993 ---
* PERTES DE CHARGE et GMV (Groupe Moto Ventilateur)
* CANAL LONGUEUR 10. LARGEUR 1.
* test cas isotherme NS FROT ET GMV
* On considre l'coulement dans un canal plan vertical
* compris entre les plans x=0 et x=1. la hauteur est de 10.
* A proximite de la sortie du canal on a place un faisceau de tube.
* modelise par une perte de charge du type K U**BETA
* Dans la zone d'entree on a place un GMV
OPTION DIME 2 ELEM QUA4 ;
GRAPH=VRAI ;
GRAPH=FAUX ;
FIN;
p1=0 0.;
p2=1. 0.;
entree= p1 d 14 p2 ;
c1= 5. 0. ;
* ikas= 0 --> DROIT (option par defaut) ikas=1 --> COURBE
ikas=0 ;
mess 'ikas= 0 --> DROIT (option par defaut)  ikas=1 --> COURBE  ? ';
* obtenir ikas*entier ;
si (EGA ikas 1) ;
q1=p1 tour c1 -90. ;
q2=p2 tour c1 -90. ;
pp1=p1 c c1 q1 20 ;
pp2=p2 c c1 q2 20 ;
sortie=entree tour c1 -90 ;
sinon ;
q1=p1 plus (0 10) ;
q2=p2 plus (0 10) ;
pp1=p1 d q1 20 ;
pp2=p2 d q2 20 ;
sortie=entree plus (0 10) ;
finsi ;
pp1=inve pp1 ;
sortie=inve sortie;
elim 0.0001 (sortie et pp1 et pp2 );
cnt=entree et pp2 et sortie et pp1 ;
* bell=surf cnt ;
bell=daller entree pp2 sortie pp1 ;
angle=0. ;
* obtenir angle*flottant ;
bell=bell tour c1 angle ;
entree=entree tour c1 angle ;
sortie=sortie tour c1 angle ;
pp1=pp1 tour c1 angle ;
pp2=pp2 tour c1 angle ;
* pp1=inve pp1 ;
elim (pp1 et pp2 et entree et sortie et bell) 0.0001 ;
entref=entree elem seg2 (lect 2 pas 1 13) ;
* entree=inve entree ;
* sortie=inve sortie ;
 $bell=doma bell ;
 $bell.titre= 'CHAINE' 'TEST PERTES DE CHARGE ET GMV' ;
 $entree = doma entree 'INCL' $bell 1.e-4 ;
 $entref = doma entref 'INCL' $bell 1.e-4 ;
 $sortie = doma sortie 'INCL' $bell 1.e-4 ;
 $pp1 = doma pp1 'INCL' $bell 1.e-4 ;
 $pp2 = doma pp2 'INCL' $bell 1.e-4 ;
ech=bell elem qua4 (lect 211 pas 1 252) ;
 $ech = doma ech 'INCL' $bell 1.e-4 ;
gmvi=bell elem qua4 ( (lect 62 pas 1 65) et (lect 76 pas 1 79)) ;
cgmv=cont gmvi ;
legmv=cgmv elem seg2 (lect 1 pas 1 4) ;
lsgmv=cgmv elem seg2 (lect 7 pas 1 10) ;
$gmv=doma gmvi 'INCL' $bell 1.e-5 ;
egmv=gmvi elem 'APPUYE' 'LARGEMENT' legmv;
sgmv=gmvi elem 'APPUYE' 'LARGEMENT' lsgmv;
$egmv=doma egmv 'INCL' $gmv 1.e-5 ;
$sgmv=doma sgmv 'INCL' $gmv 1.e-5 ;
 CK= 100. 100. ;
 CB= 2. 2. ;
 tabgmv=table ;
 tabgmv.'DIR'= 0. 1. ;
 tabgmv.'PENTREE'=($egmv.centre);
 tabgmv.'PSORTIE'=($sgmv.centre);
 tabgmv.'LDEBIT'=legmv ;
 tabgmv.'IMPR'=5 ;
* tabgmv.'KIMP'=10. ;
 tabgmv.'GMV'= EVOL 'MANU'
 'DEBIT'
 (prog 0.3 0.6 0.8 1.)
 'PRESSION'
 (prog 180. 130. 80. 0.) ;
 Si GRAPH ;dessin tabgmv.'GMV' ;FINSI ;
 tabgmv.omega=0.2 ;
 list tabgmv ;
 nu=5.E-1 ;
 tpsc=1500 ;
 zero=1.e-20 ;
  rv=eqex $bell 'DUMP' ALFA 0.7 ITMA 400
  ZONE $BELL OPER NS NU INCO 'UN'
  ZONE $ech OPER 'FROT' CK CB INCO 'UN'
  ZONE $gmv OPER 'GMV' tabgmv INCO 'UN'
  CLIM 'UN' UIMP GMVi 0. ;
  rvp= eqpr $bell zone $bell oper PRESSION 0.
  zone $PP1 oper VNIMP 0.
  zone $PP1 oper VTIMP 0.
  zone $PP2 oper VNIMP 0.
  zone $PP2 oper VTIMP 0. ;
rv.'INCO'.'UN' = kcht $bell vect sommet (1.e-5 1. ) ;
rv.pression=rvp ;
rv.'FIDT'=20;
lh= (noeu 10) et (noeu 20) et (noeu 30) et (noeu 40) et
 (noeu 50) et (noeu 60) ;
lj= (manu poi1 ($bell.maillage poin proc( 0.5 0.5) ) ) ;
    his = khis 'UN' 1 lh 'UN' 2 (lh et lj) ;
   rv.'HIST'=his ;
opti veri 1;
    exec rv ;
  PN = rvp.'PN' ;
  un= (rv.'INCO'.'UN') ;
  ung1 = vect 0.1 un ux uy jaune ;
qe=dbit un $entree ;
qs=dbit un $sortie ;
dq=(abs qe )-(abs qs) ;
mess (' BILAN : dq=') dq ;
Si GRAPH ;
dessin his.'TABD' his.'1UN' ;
dessin his.'TABD' his.'2UN' ;
trace ung1 bell ;
trace pn bell ;
FINSI ;
FIN ;
```

## INTLIN [(sans section)]
```
* EXEMPLE INTLIN.dgibi
* Entrée : Sans objet
* Sortie : Sans objet
* Commentaire : Test de la procedure
* @INTLIN.PROCEDUR
* Developpeur : Benjamin Richard
* CEA, DEN, DANS, DM2S, SEMT, EMSI
* benjamin.richard@cea.fr
* Liste d abscisses
LI1 = PROG 0.0 20.0 33.0 50.0 66.0 83.0 89.0 100.0 110.0;
* Liste d ordonnees
LI2 = PROG 0.0 0.010255 0.014085 0.014935
0.014825 0.016445 0.018185 0.020615 0.020615;
* Choix du X0
X0 = 1.1771;
* Appel à @INTLIN
Y0 = @INTLIN LI1 LI2 X0;
* Test
SI (ABS (Y0 - 6.03558E-4) > 1.0E-8);
ERREUR 5;
FINSI;
FIN;
```

## mfil [(sans section)]
```
* fichier mfil.dgibi
* Filtering of a field using a rigidity matrix genrated by MFIL.
* Author:
* Guenhael Le Quilliec (LaMe - Polytech Tours)
* Version:
* 1.0 2021/01/04 Original version compatible with MFIL V1.0
* 1.1 2021/01/07 Version compatible with MFIL V1.1
* General options
OPTI 'DIME' 2 'MODE' 'PLAN' 'CONT' 'ELEM' QUA4 ;
graph0 = FAUX ;
* Filtering radius
r0 = 5.0 ;
* Mesh
p0 = 0.0 0.0 ;
p1 = 0.0 100.0 ;
p2 = 100.0 0.0 ;
lgn0 = DROI 100 p1 p0 ;
msh0 = TRAN lgn0 100 p2 ;
* Model
mod0 = MODE msh0 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' ;
* Material
mat0 = MATE mod0 'YOUN' 200.0e9 'NU' 0.3 'RHO' 1.0 ;
* Volume node field (as rho = 1)
vol0 = EXCO 'FX' ((MASS mod0 mat0) * (MANU 'CHPO' msh0 1 'UX' 1.0)) ;
* Rigidity matrix for filtering
filter0 = MFIL vol0 r0 ;
* Create a node field to be filtered
pnt0 = ((msh0 POIN 'DROI' (100.0 0.0) (60.0 100.0) 10.0)
              POIN 'DROI' (0.0 60.0) (100.0 60.0) 30.0)
     ET (msh0 POIN 'SPHE' (40.0 30.0) (40.0 50.0) 5.0)
     ET (msh0 POIN 'SPHE' (-50.0 150.0) (50.0 150.0) 15.0) ;
field0 = (MANU 'CHPO' msh0 1 'SCAL' 0.0 'NATURE' 'DIFFUS')
       + (MANU 'CHPO' pnt0 1 'SCAL' 1.0 'NATURE' 'DIFFUS') ;
* Filter the node field
field1 = field0 * filter0 ;
* Plot the field to screen before filtering
SI graph0 ;
    TRAC field0 (msh0 CHAN 'POI1') ;
    TRAC field0 msh0 ;
FINS ;
* Plot the field to screen after filtering
SI graph0 ;
    TRAC field1 (msh0 CHAN 'POI1') ;
    TRAC field1 msh0 ;
FINS ;
FIN ;
```

## MODTRI [(sans section)]
```
* EXEMPLE MODTRI.dgibi
* Entrée : Sans objet
* Sortie : Sans objet
* Commentaire : Test de la procedure
* @MODTRI.PROCEDUR
* Developpeur : Benjamin Richard
* CEA, DEN, DANS, DM2S, SEMT, EMSI
* benjamin.richard@cea.fr
GRAPH0 = FAUX;
* Parametres materiaux
* TAB1 . 1 = K1 -- pente elastique
* TAB1 . 2 = K2 -- pente endommagee
* TAB1 . 3 = K3 -- pente plastique
* TAB1 . 4 = X0 -- seuil 1
* TAB1 . 5 = X1 -- seuil 2
TAB1 = TABLE;
TAB1 . 1 = 2.822E6;
TAB1 . 2 = 1.4536E6;
TAB1 . 3 = 4.7975E4;
TAB1 . 4 = 0.0022;
TAB1 . 5 = 0.024;
* Initialisation des donnees
* DATA . 1 = DPLUS -- endommagement +
* DATA . 2 = DMOIN -- endommagement -
* DATA . 3 = DJ -- deplacement
* DATA . 4 = MAXDP -- deplacement max
* DATA . 5 = MAXDM -- deplacement min
DATA = TABLE;
DATA . 1 = 0.0;
DATA . 2 = 0.0;
DATA . 3 = 0.0;
DATA . 4 = 0.0;
DATA . 5 = 0.0;
* Creation de la liste de chargement
LIDJ1 = PROG 0 PAS 0.0001 0.05;
LIDJ2 = PROG 0.0499 PAS -0.0001 -0.05;
LIDJ3 = PROG -0.0499 PAS 0.0001 0;
LIDJ = LIDJ1 ET LIDJ2 ET LIDJ3;
FY = PROG;
DY = PROG;
* Boucle sur les pas de deplacement
REPE BOU1 ((DIME LIDJ) - 1);
I = &BOU1;
DJ = EXTR LIDJ I;
DATA . 3 = DJ;
* Appel a la loi constitutive
TAB3 = @MODTRI TAB1 DATA;
* Mise a jour des variables internes
DATA . 1 = TAB3 . 2;
DATA . 2 = TAB3 . 3;
DATA . 4 = TAB3 . 4;
DATA . 5 = TAB3 . 5;
FO1 = TAB3 . 1;
FY = FY ET (PROG FO1);
DY = DY ET (PROG DJ);
FIN BOU1;
* Construction de l evolution et visualisation
EV1 = EVOL MANU DY FY;
SI GRAPH0;
DESS EV1;
FINSI;
ABX = EXTR EV1 'ABSC';
ORD = EXTR EV1 'ORDO';
ORD50 = EXTR ORD 50;
SI (ABS (ORD50 - 10133.0) > 1.0E0);
ERREUR 5;
FINSI;
FIN;
```

## ns1 [(sans section)]
```
'OPTI' 'ECHO' 0 ;
* NOM : NS1
* DESCRIPTION : Ecoulement de Navier-Stokes dans une tete de Mickey
* avec force tangente sur le bord
* On utilise bloq depl dire pour imposer u.n = 0
* Le test vérifie u.n=0
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 06/06/2008, version initiale
* HISTORIQUE : v1, 06/06/2008, création
* HISTORIQUE :
* HISTORIQUE :
'SAUTER' 2 'LIGNE' ;
'MESSAGE' ' Execution de ns1.dgibi' ;
'SAUTER' 2 'LIGNE' ;
interact = FAUX ;
graph = FAUX ;
'OPTION' 'DIME' 2 'ELEM' 'QUA8' ;
'SI' ('NON' interact) ;
  'OPTION' 'TRAC' 'PS' ;
'SINON' ;
  'OPTION' 'TRAC' 'X' ;
'FINSI' ;
lok = VRAI ;
* Procédure de calcul de la normale à un contour
* _mt : maillage de surface
* discg : discrétisation géométrique
* mnor : noms de composantes pour la normale
* discm : discrétisation pour la normale
'DEBPROC' VNOR ;
'ARGUMENT' _mt*'MAILLAGE' ;
'ARGUMENT' discg*'MOT' ;
'ARGUMENT' mnor*'LISTMOTS' ;
'ARGUMENT' discm*'MOT' ;
idim = 'VALEUR' 'DIME' ;
numop = idim ; numder = idim ; numvar = 1 ; numdat = 0 ; numcof = 0 ;
A = ININLIN numop numvar numdat numcof numder ;
A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'DUMM' ;
A . 'VAR' . 1 . 'DISC' = 'CSTE' ;
A . 'VAR' . 1 . 'VALEUR' = 1.D0 ;
'REPETER' iiidim idim ;
   iidim = &iiidim ;
   A . iidim . 1 . 0 = 'LECT' ;
'FIN' iiidim ;
numvar = idim ;
numcof = idim ;
B = ININLIN numop numvar numdat numcof numder ;
'REPETER' iiidim idim ;
   iidim = &iiidim ;
   nominc = 'EXTRAIRE' mnor iidim ;
* 'LISTE' nominc ;
   B . 'VAR' . iidim . 'NOMDDL' = 'MOTS' nominc ;
   B . 'VAR' . iidim . 'DISC' = discm ;
   B . 'COF' . iidim . 'COMPOR' = 'CHAINE' 'VNOR' iidim ;
   B . 'COF' . iidim . 'LDAT' = 'LECT' ;
   B . iidim . iidim . 0 = 'LECT' iidim ;
'FIN' iiidim ;
chnori = 'NLIN' discg _mt A B 'GAU7' ;
* Matrice masse
numop = 1 ; numder = idim ; numvar = 1 ; numdat = 0 ; numcof = 0 ;
A = ININLIN numop numvar numdat numcof numder ;
A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'DUMM' ;
A . 'VAR' . 1 . 'DISC' = 'CSTE' ;
A . 'VAR' . 1 . 'VALEUR' = 1.D0 ;
A . 1 . 1 . 0 = 'LECT' ;
B = ININLIN numop numvar numdat numcof numder ;
B . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'SCAL' ;
B . 'VAR' . 1 . 'DISC' = discm ;
B . 1 . 1 . 0 = 'LECT' ;
chmass = 'NLIN' discg _mt A B 'GAU7' ;
chnor = '/' chnori chmass ;
'RESPRO' chnor ;
'FINPROC' ;
* Tracé des vitesses
'DEBPROC' TRACVIT ;
   'ARGUMENT' rvx*'TABLE' ;
   'SI' ('EXISTE' rvx 'EQEX') ;
      rv = rvx . 'EQEX' ;
      lrvx = VRAI ;
      domz = rvx . 'DOMZ' ;
   'SINON' ;
      rv = rvx ;
      lrvx = FAUX ;
      'ARGUMENT' domz*'MMODEL' ;
   'FINSI' ;
   nuit = rv . 'NUITER' ;
   chv = rv . 'INCO' . 'UN' ;
   maxv = 'MAXIMUM' chv 'ABS' ;
   'SI' ('<' maxv 1.D-8) ;
      maxv = 1.D0 ;
   'FINSI' ;
   echvit = maxv ;
   mt = 'DOMA' domz 'MAILLAGE' ;
   echmvi = '**' ('/' ('MESURE' mt) ('NBEL' mt))
                 ('/' 1.D0 ('VALEUR' 'DIME')) ;
   vref = '/' ('*' echmvi 2.D0) echvit ;
* Vecteur unité
   mpA = mt 'POIN' 'PROC' (0. 0.) ;
   cvecu = 'MANUEL' 'CHPO' mpA 2 'UX' echvit 'UY' 0.D0
        'NATURE' 'DISCRET' ;
   vecvit1 = 'VECTEUR' chv vref 'DEPL' 'JAUN' ;
   vecvit2 = 'VECTEUR' cvecu vref 'DEPL' 'ROUG' ;
   vecvit = vecvit1 'ET' vecvit2 ;
   tit = 'CHAINE' 'Vitesse ; nuiter=' nuit ' ; echvit=' echvit ;
   'TRACER' vecvit mt ('CONTOUR' mt) 'TITR' tit 'NCLK' ;
   'SI' lrvx ;
      'TRACER' vecvit mt ('CONTOUR' mt) 'TITR' tit 'NCLK' ;
      mat chpo = 'KOPS' 'MATRIK' ;
      'RESPRO' mat chpo ;
   'SINON' ;
      'TRACER' vecvit mt ('CONTOUR' mt) 'TITR' tit ;
   'FINSI' ;
'FINPROC' ;
* Imposition d'une force
'DEBPROC' KTOIM ;
   'ARGUMENT' rvx*'TABLE' ;
   rv = rvx . 'EQEX' ;
   mq = 'DOMA' (rvx . 'DOMZ') 'QUAF' ;
   for = rvx . 'ARG1' ;
   nominc = 'EXTRAIRE' (rvx . 'LISTINCO') 1 ;
   ni1 = 'CHAINE' '1' nominc ;
   ni2 = 'CHAINE' '2' nominc ;
* Matrice masse
   idim = 'VALEUR' 'DIME' ;
   numop = 2 ; numder = idim ; numvar = 2 ; numdat = 0 ; numcof = 0 ;
   A = ININLIN numop numvar numdat numcof numder ;
   A . 'VAR' . 1 . 'NOMDDL' = 'MOTS' 'FX' ;
   A . 'VAR' . 1 . 'DISC' = 'QUAF' ;
   A . 'VAR' . 1 . 'VALEUR' = for ;
   A . 'VAR' . 2 . 'NOMDDL' = 'MOTS' 'FY' ;
   A . 'VAR' . 2 . 'DISC' = 'QUAF' ;
   A . 'VAR' . 2 . 'VALEUR' = for ;
   A . 1 . 1 . 0 = 'LECT' ;
   A . 2 . 2 . 0 = 'LECT' ;
   B = ININLIN numop numvar numdat numcof numder ;
   B . 'VAR' . 1 . 'NOMDDL' = 'MOTS' ni1 ;
   B . 'VAR' . 1 . 'DISC' = 'QUAF' ;
   B . 'VAR' . 2 . 'NOMDDL' = 'MOTS' ni2 ;
   B . 'VAR' . 2 . 'DISC' = 'QUAF' ;
   B . 1 . 1 . 0 = 'LECT' ;
   B . 2 . 2 . 0 = 'LECT' ;
   forint = 'NLIN' 'QUAF' mq A B 'GAU7' ;
   chvid matvid = 'KOPS' 'MATRIK' ;
   'RESPRO' forint matvid ;
'FINPROC' ;
* Bloquage des vitesses suivant un champ de normale
'DEBPROC' KBLOQ ;
   'ARGUMENT' rvx*'TABLE' ;
   rv = rvx . 'EQEX' ;
   'SI' ('EXISTE' rvx 'MATRICE') ;
      mnormal = rvx . 'MATRICE' ;
   'SINON' ;
      vnormal = rv . 'VNORMAL' ;
      mail = 'DOMA' (rvx . 'DOMZ') 'MAILLAGE' ;
      mn = 'BLOQUE' 'DEPL' 'DIRE' vnormal mail ;
      mn = 'KOPS' 'RIMA' mn ;
      nominc = 'EXTRAIRE' (rvx . 'LISTINCO') 1 ;
      ni1 = 'CHAINE' '1' nominc ;
      ni2 = 'CHAINE' '2' nominc ;
      mnormal = 'KOPS' 'CHANINCO' mn
               ('MOTS' 'LX' 'UX' 'UY')
               ('MOTS' 'LX' ni1 ni2)
               ('MOTS' 'FLX' 'FX' 'FY')
               ('MOTS' 'LX' ni1 ni2) ;
      rvx . 'MATRICE' = mnormal ;
   'FINSI' ;
   chvid matvid = 'KOPS' 'MATRIK' ;
   'RESPRO' chvid mnormal ;
'FINPROC' ;
* Maillage
* Paramètres
Rgrand = 1. ; Dpetit = 1. ; ang = 45. ; dang = 10. ;
den = 0.1 ;
'DENS' den ;
* Points
p0 = 0. 0. ;
p1 = 0. ('*' Rgrand -1.) ;
p2 = POINTCYL Rgrand ('-' ang dang) ;
p3 = POINTCYL ('+' Rgrand Dpetit) ang ;
p4 = POINTCYL Rgrand ('+' ang dang) ;
p5 = POINTCYL Rgrand ('-' 180. ('+' ang dang)) ;
p6 = POINTCYL ('+' Rgrand Dpetit) ('-' 180. ang) ;
p7 = POINTCYL Rgrand ('-' 180. ('-' ang dang)) ;
* Contour
l1 = 'CER3' p7 p1 p2 ; l2 = 'CER3' p2 p3 p4 ;
l3 = 'CERCLE' p4 p0 p5 ; l4 = 'CER3' p5 p6 p7 ;
cmt = l1 'ET' l2 'ET' l3 'ET' l4 ;
_cmt = cmt ;
mt = 'SURFACE' cmt ; _mt = 'CHANGER' mt 'QUAF' ;
* Normale au contour
vnormal = VNOR cmt 'QUAF' ('MOTS' 'UX' 'UY') 'QUAF' ;
* Discrétisation
disv = 'QUAF' ;
disp = 'CENTREP1' ;
dec = 'CENTREE' ;
Re = 30. ;
dif = '/' 1. Re ;
omeg = 1. ;
nitmax = 5 ;
xfor = '**' 3. 0.5 ; yfor = PI ;
fnormal = 'MANUEL' 'CHPO' _cmt ('MOTS' 'FX' 'FY') ('PROG' xfor yfor) ;
'SI' graph ;
   vvno = 'VECT' vnormal 'DEPL' 'JAUN' ;
   vfno = 'VECT' fnormal 'FORC' 'ROUG' ;
   vtot = 'ET' vvno vfno ;
   tit = 'CHAINE' 'Maillage' ' '
                  'Jaune:normale' ' '
                  'Rouge:force imposee' ;
   'TRACER' vtot _mt 'TITR' tit ;
'FINSI' ;
$mt = 'MODELISER' _mt 'NAVIER_STOKES' disv ;
$cmt = 'MODELISER' cmt 'NAVIER_STOKES' disv ;
ppres = 'POIN' ('DOMA' $mt disp) 'PROC' (0.5 0.5) ;
mp1 = 'MANUEL' ppres 'POI1' ;
rv = 'EQEX' 'ITMA' 1 'NITER' nitmax 'OMEGA' omeg ;
'SI' graph ;
   rv = 'EQEX' rv
     'ZONE' $mt 'OPER' 'TRACVIT' ;
'FINSI' ;
rv = 'EQEX' rv
     'OPTI' 'EF' 'IMPL' dec disp
     'ZONE' $mt 'OPER' 'KONV' 1. 'UN' dif 'INCO' 'UN'
     'OPTI' 'EF' 'IMPL' dec disp 'FTAU'
     'ZONE' $mt 'OPER' 'LAPN' dif 'INCO' 'UN'
     'OPTI' 'EF' 'IMPL' dec disp
     'ZONE' $mt 'OPER' 'KBBT' -1. 'INCO' 'UN' 'PN'
     ;
* 'OPTI' 'EF' 'IMPL' 'CENTREE' disp
* 'ZONE' $mt 'OPER' 'DFDT' 1. 'UNM' 'DT' 'UN' dif 'INCO' 'UN' ;
rv = 'EQEX' rv
     'ZONE' $cmt 'OPER' 'KTOIM' fnormal 'INCO' 'UN' ;
rv = 'EQEX' rv
     'ZONE' $cmt 'OPER' 'KBLOQ' 'INCO' 'UN' ;
rv = 'EQEX' rv 'CLIM'
            'PN' 'TIMP' mp1 0. ;
rv . 'INCO' = 'TABLE' 'INCO' ;
rv . 'INCO' . 'UN' = 'KCHT' $mt 'VECT' 'SOMMET' (0. 0.) ;
rv . 'INCO' . 'PN' = 'KCHT' $mt 'SCAL' disp 0. ;
rv . 'VNORMAL' = vnormal ;
EXEC rv ;
'SI' graph ;
   TRACVIT rv $mt ;
   mt = 'DOMA' $mt 'MAILLAGE' ;
   fcou = FCOURANT mt (rv . 'INCO' . 'UN') ;
   'OPTI' 'ISOV' 'SULI' ;
   tit = 'CHAINE' 'Fonction de courant ; Re=' Re ;
   'TRACER' fcou _mt _cmt 'TITR' tit ;
   'OPTI' 'ISOV' 'SURF' ;
   MONTAGNE fcou _mt 'TITRE' tit 'SUPER' ;
'FINSI' ;
* Vérification que la vitesse est bien orthogonale à la normale
vit = rv . 'INCO' . 'UN' ;
mvit = 'MOTS' 'UX' 'UY' ;
ps = 'PSCAL' vit vnormal mvit mvit ;
mps = 'MAXIMUM' ps 'ABS' ;
valim = 1.D-12 ;
tst = ('<' mps valim) ;
'SI' ('NON' tst) ;
   cherr = 'CHAINE' '!!! Erreur, on aurait voulu '
                    'mps=' mps ' < ' 'valim=' valim ;
   'MESSAGE' cherr ;
'FINSI' ;
lok = lok 'ET' tst ;
* Fin du jeu de donnees
'SAUTER' 2 'LIGNE' ;
'SI' lok ;
   'MESSAGE' 'Tout sest bien passe' ;
'SINON' ;
   'MESSAGE' 'Il y a eu des erreurs' ;
'FINSI' ;
'SAUTER' 2 'LIGNE' ;
'SI' interact ;
   'OPTION' 'DONN' 5 'ECHO' 1 ;
'FINSI' ;
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'FINSI' ;
* End of dgibi file NS1
'FIN' ;
```

## ntableau [(sans section)]
```
* NOM : NTABLEAU
* DESCRIPTION : Le but de ce cas-test est de tester le trace
* d'un tableau de chiffres pour les diverses options et
* sorties.
* Malheureusement, on ne peut tester le bon fonctionnement
* qu'a l'oeil du specialiste car on ne sait pas faire de
* test automatise.
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : stephane.gounand@cea.fr
* VERSION : v1, 22/06/2016, version initiale
* HISTORIQUE : v1, 22/06/2016, création
* HISTORIQUE :
'OPTI' 'ECHO' 1 ;
'SAUT' 'PAGE' ;
interact = faux ;
* s'il n'y a pas de graphique, le cas-test ne sert a rien...
* graph = vrai ;
'OPTION' 'DIME' 2 'ELEM' 'SEG2' ;
'SI' interact ;
   lsort = 'MOTS' 'X' 'PS' 'PSC' 'OPEN' ;
* lsort = 'MOTS' 'X' 'PS' 'PSC' ;
'SINON' ;
   lsort = 'MOTS' 'PS' 'PSC' ;
* lsort = 'MOTS' 'PSC' ;
'FINSI' ;
* On ne teste pas beaucoup de cas pour l'instant
* Un tableau S, A, X, Y
cer = 'LIGN' 36 (0. 0.) (1. 0.) 360. 'ROTA' ;
xcer ycer = 'COORDONNEE' cer ;
evx = 'EVOL' 'CHPO' xcer cer ;
evy = 'EVOL' 'CHPO' ycer cer ;
ang = 'ATG' ycer xcer ;
eva = 'EVOL' 'CHPO' ang cer ;
evt1 = eva 'ET' evx 'ET' evy ;
'REPETER' isort ('DIME' lsort) ;
   mosort = 'EXTRAIRE' lsort &isort ;
   'OPTI' 'TRAC' mosort ;
   'NTABLEAU' evt1 'TITR' 'A mon beau cercle' 'STITR' 'Gounand FECIT'
                  'TCOL' 1 'Absc. curv.' 'TCOL' 2 'Angle'
                  'TCOL' 3 'X' 'TCOL' 4 'Y'
                  'TLIG' 11 'Quart' 'TLIG' 20 'Demi' 'TLIG' 29 '3Quart'
                  'TEXCOU' 2
                  'LOGO' ;
'FIN' isort ;
'SI' interact ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
* End of dgibi file NTABLEAU
'FIN' ;
```

## ordo_2 [(sans section)]
```
* TEST DE L OPERATEUR ORDO 'COUT'
* POUR LE CALCUL DE LA PERMUTATION OPTIMISANT UN COUT
* BP, 2016-06-24
* mot-cles : mathematiques, permutation, arrangement
* petite procedure utile pour le calcul a la main
debp coutperm lili*'LISTENTI' jperm*'LISTENTI';
  Scout = 0;
  repe bi (dime jperm);
    j = extr jperm &bi;
    k = ((&bi - 1) * n) + j;
    Scout = Scout + (ABS (extr lili k));
  fin bi;
finp Scout;
* donnees
* ml1 = lect
* 6 3 7 1 8
* 5 2 4 4 7
* 2 5 3 9 4
* 6 3 4 5 4
* 2 2 6 5 8 ;
ml1 = brui 'BLAN' 'POIS' 1000 (10**2);
list ml1;
* on verifie a la main sur toutes les permutations
n2 = dime ml1;
n = enti proche (n2**0.5);
nfacto = factorie n;
mess 'n!=' nfacto;
si (nfacto < 1000) ;
Tperm = table;
Tcout = lect;
* combinaison initiale
perm1 = lect 1 pas 1 n;
cout1 = coutperm ml1 perm1;
Tperm . 1 = (perm1 + 0);
Tcout = Tcout et cout1;
mess '----- Combinaison 1 de cout = ' cout1 '-----';
list perm1;
mess '--------------------------------------------------' ;
* boucle sur les combinaisons possibles
repe bcomb (nfacto - 1);
      icomb = &bcomb + 1;
* i=n-1
      i = n - 1;
* 10 if(a(i).lt.a(i+1)) go to 20
* i=i-1
* if(i.eq.0) go to 20
* go to 10
      repe b10;
        si ((extr perm1 i) < (extr perm1 (i+1))); quit b10; finsi;
        i = i - 1;
        si (i ega 0); quit b10; finsi;
      fin b10;
* 20 j=i+1
* k=n
      j = i + 1;
      k = n;
* 30 t=a(j)
* a(j)=a(k)
* a(k)=t
* j=j+1
* k=k-1
* if(j.lt.k) go to 30
* j=i
* if(j.ne.0) go to 40
* nextp=.false.
* return
      repe b30;
* swap
        t = extr perm1 j;
        REMPLACER perm1 j (extr perm1 k);
        REMPLACER perm1 k t;
        j = j + 1;
        k = k - 1;
        si (j < k); iter b30; finsi;
        j = i;
        si (j neg 0); quit b30; finsi;
        si (j ega 0); quit bcomb; finsi;
      fin b30;
* 40 j=j+1
* if(a(j).lt.a(i)) go to 40
* t=a(i)
* a(i)=a(j)
* a(j)=t
* nextp=.true.
* end
      repe b40;
        j = j + 1;
        si ((extr perm1 j) < (extr perm1 i)); iter b40; finsi;
* swap
        t = extr perm1 i;
        REMPLACER perm1 i (extr perm1 j);
        REMPLACER perm1 j t;
        quit b40;
      fin b40;
      cout1 = coutperm ml1 perm1;
      Tperm . icomb = (perm1 + 0);
      Tcout = Tcout et cout1;
      mess '----- Combinaison 'icomb' de cout = ' cout1 '-----';
      list perm1;
      mess '--------------------------------------------------' ;
fin bcomb;
jlist = lect 1 pas 1 nfacto;
Tcout2 jlist2 = ordo Tcout jlist;
jmin = extr jlist2 1;
cout2 = extr Tcout2 1;
mess '----- Combinaison ' jmin ' de cout mini = ' cout2 '-----';
list Tperm . jmin;
finsi;
* calcul via ORDO 'COUT' LISTENTI
* calcul de la permutation et du cout associe
* ------> methode Hongroise :
jperm = lect 1 pas 1 n;
temp zero;
c_ordo p_ordo = ORDO 'COUT' 'HONG' ml1 jperm;
temp 'SGAC' 'IMPR';
temp ;
mess '>>>>> Cout mini =' c_ordo '<<<<<';
list p_ordo;
* ------> methode ou lon calcule tout :
temp zero;
c_ordo2 p_ordo2 = ORDO 'COUT' ml1 jperm;
temp 'SGAC' 'IMPR';
temp ;
mess '>>>>> Cout mini =' c_ordo2 '<<<<<';
list p_ordo2;
* calcul via ORDO 'COUT' LISTREEL
* ------> methode Hongroise :
Xperm = lect 1 pas 1 n; list Xperm;
XML1 = FLOT ml1; list XML1;
temp zero;
* opti surv 2121211;
c_ordX p_ordX = ORDO 'COUT' 'HONG' Xml1 Xperm;
temp 'SGAC' 'IMPR';
temp ;
mess '>>>>> Cout mini =' c_ordX '<<<<<';
list c_ordX;
toto = p_ordX + 1;
list toto;
list p_ordX;
* ------> methode ou lon calcule tout :
temp zero;
c_ordX2 p_ordX2 = ORDO 'COUT' Xml1 Xperm;
temp 'SGAC' 'IMPR';
temp ;
mess '>>>>> Cout mini =' c_ordX2 '<<<<<';
list p_ordX2;
* test de non regression
si (nfacto < 1000) ;
  errcout = abs (cout2 - c_ordo);
  errperm = maxi (Tperm . jmin - p_ordo) 'ABS';
sinon;
  errcout = abs (c_ordo2 - c_ordo);
  errperm = maxi (p_ordo2 - p_ordo) 'ABS';
finsi;
SI ((errcout > 0) OU (errperm > 0)) ;
   ERRE 5 ;
SINO ;
   ERRE 0 ;
FINSI ;
FIN ;
```

## ouvfiss2D [(sans section)]
```
* TEST DE l'OPERATEUR OUVFISS EN 2D
* ON TIRE SUR UN BARREAU ENDOMMAGEABLE
* UN DEFAUT EST CREE POUR LOCALISER L'ENDOMMAGEMENT
* UNE SEULE FISSURE EST GENEREE, DONC L'OUVERTURE EST Delta(L) - Sigma/E0
* On UTILISE DU MAZARS A ECROUISSAGE LINEAIRE
OPTI DIME 2 ELEM QUA4 MODE PLAN CONT;
h=0.02;
L=0.2;
* caracteristiques
YG=3.E10;
Ft=3.E6;
Kt=Ft/YG;
GF=300.;
* AT<-10 pour écrouissage linéaire
AT=-20.;
* BT est la déformation à laquelle la contrainte s'annule
BT=2*GF/Ft/h;
DENSITE h;
P1=0. 0.;
P2=L 0.;
P3=0. H;
D1=D P1 P3;
S1=D1 TRANS P2;
D2=S1 COTE 3;
MOD1=MODE S1 MECANIQUE ELASTIQUE ISOTROPE ENDOMMAGEMENT MAZARS;
MAT1=MATE MOD1 YOUN YG NU 0.2 KTR0 (KT/0.9) ATRA
               AT BTRA BT ACOM 1.4 BCOM 1900. BETA 1.06 ;
CH1=MANU CHAM MOD1 'TYPE'
   'CARACTERISTIQUES' 'POSI' 'RIGIDITE' KTR0 1 1 1 (0.1*KT);
MAT1=MAT1 - CH1;
CL1=BLOQ D1 UX;
CL2=BLOQ P1 UY;
CL3=BLOQ D2 UX;
CLT=CL1 ET CL2 ET CL3;
F1=DEPI CL3 1.;
PROG1=PROG 0. 1.;
EVOL1=EVOL MANU PROG1 PROG1;
CHAR1=CHARGEMENT F1 EVOL1 'DIMP';
T0=Kt*L;
DELTAT=T0/10.;
TF=BT*h;
LT1=PROG (0.9*T0) PAS (T0/10.) TF;
TAB1=TABLE;
TAB1.MODELE=MOD1;
TAB1.CARACTERISTIQUES=MAT1;
TAB1.BLOCAGES_MECANIQUES=CLT;
TAB1.CHARGEMENT=CHAR1;
TAB1.TEMPS_CALCULES=LT1;
PASAPAS TAB1;
* courbe globale
ev1=@global tab1 evol1 cl3 fx;
* ouverture de fissure théorique
progd=extr ev1 absc;
progf=extr ev1 ordo;
* contrainte = F/h, deformation=F/(E*h),
* deplacement élastique = F*L/(E*h)
progouv=progd - (progf * L / YG / h);
evouv=evol manu progd 'deplacement' progouv 'ouverture';
* Dess evouv;
ouvfiss tab1;
* ouverture calculee
progouv2=prog;
n1=dime tab1.temps;
repeter bou1 n1;
  ouv1=extr tab1 . OUV . (&BOU1 - 1) EPXX 1 1 1;
  PROGOUV2=INSE PROGOUV2 &BOU1 OUV1;
FIN BOU1;
evouv2=evol manu progd 'deplacement' progouv2 'ouverture';
* Dess evouv2;
EVERR=ABS (EVOUV - EVOUV2);
SOM1=(INTG EVERR);
SOM2=(INTG EVOUV);
ERR_REL=SOM1/SOM2;
SI (ERR_REL > 1.E-2) ;
  ERREUR 5;
FINSI;
FIN;
```

## pointcylsph [(sans section)]
```
* Petit test simple sur les procedures POINTCYL et POINTSPH
* Precision pour les comparaisons de POINTs (critere de distance)
dprec = 'VALE' 'PREC' ; 'LISTER' dprec ;
* En 1D
'OPTION' 'DIME' 1 ;
pt1 = POINT 0. 'DENS' 1. ;
pt2 = POINT 0. 'DENS' 2. ;
SI ('>' (DIST pt1 pt2) dprec) ;
  ERRE 5 ;
FINSI ;
* En 2D
OPTI 'DIME' 2 ;
* POINTCYL syntaxe avec des FLOTTANTs
p1 = POINTCYL 0. 0. ;
p2 = POINTCYL 4. 80. ;
p3 = POINTCYL 1. 280. ;
p4 = POINTCYL 3. 180. ;
p5 = POINTCYL 2. 120. ;
mp1 = p1 ET p2 ET p3 ET p4 ET p5 ;
* POINTCYL syntaxe avec des LISTREELs
mp2 = POINTCYL (PROG 0. 4. 1. 3. 2.) (PROG 0. 80. 280. 180. 120.) ;
* test d'egalite des points engendres
REPE b1 (NBEL mp1) ;
  pt1 = mp1 POIN &b1 ;
  pt2 = mp2 POIN &b1 ;
  SI ('>' (DIST pt1 pt2) dprec) ;
    ERRE 5 ;
  FINSI ;
FIN b1 ;
* En 3D
OPTI 'DIME' 3 ;
* POINTCYL syntaxe avec des FLOTTANTs
p1 = POINTCYL 0. 0. 0. ;
p2 = POINTCYL 4. 80. 12. ;
p3 = POINTCYL 1. 280. -1. ;
p4 = POINTCYL 3. 180. 42. ;
p5 = POINTCYL 2. 120. -7. ;
mp1 = p1 ET p2 ET p3 ET p4 ET p5 ;
* POINTCYL syntaxe avec des LISTREELs
mp2 = POINTCYL (PROG 0. 4. 1. 3. 2.) (PROG 0. 80. 280. 180. 120.) (PROG 0. 12. -1. 42. -7.) ;
* test d'egalite des points engendres
REPE b1 (NBEL mp1) ;
  pt1 = mp1 POIN &b1 ;
  pt2 = mp2 POIN &b1 ;
  SI ('>' (DIST pt1 pt2) dprec) ;
    ERRE 5 ;
  FINSI ;
FIN b1 ;
* POINTSPH syntaxe avec des FLOTTANTs
p1 = POINTSPH 0. 0. 0. ;
p2 = POINTSPH 4. 80. 12. ;
p3 = POINTSPH 1. 280. -80. ;
p4 = POINTSPH 3. 180. 76. ;
p5 = POINTSPH 2. 120. -12. ;
mp1 = p1 ET p2 ET p3 ET p4 ET p5 ;
* POINSPHE syntaxe avec des LISTREELs
mp2 = POINTSPH (PROG 0. 4. 1. 3. 2.) (PROG 0. 80. 280. 180. 120.) (PROG 0. 12. -80. 76. -12.) ;
* test d'egalite des points engendres
REPE b1 (NBEL mp1) ;
  pt1 = mp1 POIN &b1 ;
  pt2 = mp2 POIN &b1 ;
  SI ('>' (DIST pt1 pt2) dprec) ;
    ERRE 5 ;
  FINSI ;
FIN b1 ;
FIN ;
```

## proi3 [(sans section)]
```
'OPTI' echo 0 ;
* NOM : PROI3
* DESCRIPTION : Cas-test de la gestion des soucis et du critere de
* rattrapage dans PROI.
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stephane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
* mel : stephane.gounand@cea.fr
* VERSION : v1, 15/02/2019, version initiale
* HISTORIQUE : v1, 15/02/2019, création
* HISTORIQUE :
* HISTORIQUE :
interact = faux ;
graph = faux ;
'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
p0 = 0. 1. ; p1 = 0. 0. ; p2 = 1. 1. ;
n1 = 2 ;
c1 = 'CERC' n1 p1 p0 p2 ;
d1 = 'COUT' c1 p0 ;
x1 y1 = 'COOR' d1 ;
x0 y0 = 'COOR' p0 ;
r1 = '**' ('+' ('**' ('-' x1 x0) 2) ('**' ('-' y1 y0) 2)) 0.5 ;
'SI' graph ; 'TRAC' r1 d1 ; 'FINS' ;
cr1 = 'CHAN' 'CHAM' r1 d1 ;
n2 = 3 ;
c2 = 'CERC' n2 p1 p0 p2 ;
d2 = 'COUT' c2 p0 'COUL' roug ;
'SI' graph ; 'TRAC' (d1 'ET' d2) ; 'FINS' ;
vcrit = 1.d-5 ;
lcrit = faux ;
'REPE' iicrit 20 ;
   icrit = &iicrit ;
   souci 0 ;
   r12 = 'PROI' d2 cr1 vcrit ;
   'SI' (souci) ;
      'MESS' 'Souci' ' ' icrit ' ! vcrit=' vcrit ;
      vcrit = '*' vcrit 2. ;
   'SINO' ;
      lcrit = vrai ;
      'QUIT' iicrit ;
   'FINS' ;
'FIN' iicrit ;
'SI' lcrit ;
   mr12 = 'MAXI' r12 'ABS' ;
   'MESS' 'Projection reussie vcrit=' vcrit ' icrit=' icrit
      ' maxi R=' mr12 ;
   'SI' graph ; 'TRAC' r12 d2 ; 'FINS' ;
'SINO' ;
   'MESS' 'Projection ratee vcrit=' vcrit ' icrit=' icrit ;
'FINS' ;
* Test
* Au 2019/0218, on a :
* Projection reussie vcrit= 8.19200E-02 icrit= 14 maxi R= 1.0731
vcritr = 8.5e-2 ; icritr = 15 ; mr12r = 1. '+' vcritr ;
lok = lcrit ;
'SI' lcrit ;
   'SI' ('>' vcrit vcritr) ;
      'MESS' ('CHAI' '!!!  vcrit=' vcrit ' > vcritr=' vcritr) ;
      lok = lok 'ET' faux ;
   'FINS' ;
   'SI' ('>' icrit icritr) ;
      'MESS' ('CHAI' '!!!  icrit=' icrit ' > icritr=' icritr) ;
      lok = lok 'ET' faux ;
   'FINS' ;
   'SI' ('>' mr12 mr12r) ;
      'MESS' ('CHAI' '!!!  mr12=' mr12 ' > mr12r=' mr12r) ;
      lok = lok 'ET' faux ;
   'FINS' ;
'FINS' ;
'SAUT' 1 'LIGNE' ;
'SI' lok ;
   'MESSAGE' 'Tout sest bien passe' ;
'SINON' ;
   'MESSAGE' '!!! Il y a eu des erreurs' ;
'FINSI' ;
'SAUT' 1 'LIGNE' ;
'SI' interact ;
   'OPTION' 'DONN' 5 'ECHO' 1 ;
'FINSI' ;
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'FINSI' ;
* End of dgibi file PROI3
'FIN' ;
```

## projgril_1 [(sans section)]
```
OPTI 'DIME' 2 'ECHO' 1 ;
* Test de la procedure PROJGRIL
* Projection dans 2 dimensions d'un nuage representant une grille
* de n dimensions
* utilise dans le cas de l'operateur IPOL option 'GRILL'
* - test avec fonction de 2, 3, 4 et meme 5 variables
MESS ; MESS ; MESS ;
* Tolerance pour les tests et indicateur de trace
tol1 = 1.E-14 ;
itrac = FAUX ;
* TEST sur une grille de dimension 2
MESS 'Grille de dimension 2' ;
MESS ;
l1 = PROG 1. 5. 12. ;
l2 = PROG 0. 2.5 ;
lf = PROG 4. 8. 15. 16. 23. 42. ;
nu1 = NUAG 'COMP' 'JIN' l1
           'COMP' 'SUN' l2
           'COMP' 'JACK' lf ;
mail1 chp1 = PROJGRIL nu1 ;
tp = TABL ;
tf = TABL ;
tp . 1 = 1. 0. ;
tf . 1 = 4. ;
tp . 2 = 5. 0. ;
tf . 2 = 8. ;
tp . 3 = 12. 0. ;
tf . 3 = 15. ;
tp . 4 = 1. 2.5 ;
tf . 4 = 16. ;
tp . 5 = 5. 2.5 ;
tf . 5 = 23. ;
tp . 6 = 12. 2.5 ;
tf . 6 = 42. ;
MESS ' Point  |   Valeur       |   Valeur       | Erreur' ;
MESS '        |   theorique    |   interpolee   |       ' ;
MESS '--------|----------------|----------------|-------' ;
REPE b1 (DIME tp) ;
  ft = tf . &b1 ;
  pt = mail1 POIN 'PROC' (tp . &b1) ;
  fc = EXTR chp1 'JACK' pt ;
  err1 = ABS ((fc - ft) / ft) ;
  MESS &b1 '|' ft '|' fc '|' err1 ;
  SI (err1 > tol1) ;
    MESS ; MESS ;
    MESS 'ECHEC DU CAS TEST !' ;
    ERREUR 4 ;
  FINSI ;
FIN b1 ;
SI itrac ;
  TRAC chp1 mail1 'TITR' 'Test sur une grille en dimension 2' ;
FINSI ;
MESS ; MESS ; MESS ;
* TEST sur une grille de dimension 3
MESS 'Grille de dimension 3' ;
MESS ;
l3 = PROG 0. 10. ;
lf = lf ET (PROG 8. 42. 4. 16. 15. 23.) ;
nu1 = NUAG 'COMP' 'EKO' l1
           'COMP' 'BEN' l2
           'COMP' 'BOON' l3
           'COMP' 'KATE' lf ;
mail1 chp1 = PROJGRIL nu1 (MOTS 'BEN') (PROG 1.25) ;
tp = TABL ;
tf = TABL ;
tp . 1 = 1. 0. ;
tf . 1 = 10. ;
tp . 2 = 5. 0. ;
tf . 2 = 15.5 ;
tp . 3 = 12. 0. ;
tf . 3 = 28.5 ;
tp . 4 = 1. 10. ;
tf . 4 = 12. ;
tp . 5 = 5. 10. ;
tf . 5 = 28.5 ;
tp . 6 = 12. 10. ;
tf . 6 = 13.5 ;
MESS ' Point  |   Valeur       |   Valeur       | Erreur' ;
MESS '        |   theorique    |   interpolee   |       ' ;
MESS '--------|----------------|----------------|-------' ;
REPE b1 (DIME tp) ;
  ft = tf . &b1 ;
  pt = mail1 POIN 'PROC' (tp . &b1) ;
  fc = EXTR chp1 'KATE' pt ;
  err1 = ABS ((fc - ft) / ft) ;
  MESS &b1 '|' ft '|' fc '|' err1 ;
  SI (err1 > tol1) ;
    MESS ; MESS ;
    MESS 'ECHEC DU CAS TEST !' ;
    ERREUR 4 ;
  FINSI ;
FIN b1 ;
SI itrac ;
  TRAC chp1 mail1 'TITR' 'Test sur une grille en dimension 3' ;
FINSI ;
MESS ; MESS ; MESS ;
* TEST sur une grille de dimension 4
MESS 'Grille de dimension 4' ;
MESS ;
l4 = PROG 1977. 2004. ;
lf = lf ET (PROG 42. 4. 23. 8. 15. 16.
                  4. 23. 16. 8. 15. 42.) ;
nu1 = NUAG 'COMP' 'WALT' l1
           'COMP' 'ROSE' l2
           'COMP' 'JACO' l3
           'COMP' 'SAYI' l4
           'COMP' 'HUGO' lf ;
mail1 chp1 = PROJGRIL nu1 (MOTS 'ROSE' 'WALT') (PROG 1.25 8.5) ;
tp = TABL ;
tf = TABL ;
tp . 1 = 0. 1977. ;
tf . 1 = 22. ;
tp . 2 = 10. 1977. ;
tf . 2 = 21. ;
tp . 3 = 0. 2004. ;
tf . 3 = 14.5 ;
tp . 4 = 10. 2004. ;
tf . 4 = 24. ;
MESS ' Point  |   Valeur       |   Valeur       | Erreur' ;
MESS '        |   theorique    |   interpolee   |       ' ;
MESS '--------|----------------|----------------|-------' ;
REPE b1 (DIME tp) ;
  ft = tf . &b1 ;
  pt = mail1 POIN 'PROC' (tp . &b1) ;
  fc = EXTR chp1 'HUGO' pt ;
  err1 = ABS ((fc - ft) / ft) ;
  MESS &b1 '|' ft '|' fc '|' err1 ;
  SI (err1 > tol1) ;
    MESS ; MESS ;
    MESS 'ECHEC DU CAS TEST !' ;
    ERREUR 4 ;
  FINSI ;
FIN b1 ;
SI itrac ;
  TRAC chp1 mail1 'TITR' 'Test sur une grille en dimension 4' ;
FINSI ;
MESS ; MESS ; MESS ;
* TEST sur une grille de dimension 5
MESS 'Grille de dimension 5' ;
MESS ;
l5 = PROG 1. 4. 6. ;
lf = lf ET (PROG 4. 23. 15. 4. 8. 15. 4. 8. 15. 42. 23. 16.
                  8. 42. 16. 42. 23. 16. 16. 23. 16. 15. 8. 15.
                 15. 4. 23. 4. 8. 15. 15. 42. 23. 16. 4. 8.
                 16. 8. 42. 42. 23. 16. 8. 4. 42. 23. 42. 4.) ;
nu1 = NUAG 'COMP' 'ALEX' l1
           'COMP' 'ANA' l2
           'COMP' 'SAWY' l3
           'COMP' 'CHAN' l4
           'COMP' 'DESM' l5
           'COMP' 'JOHN' lf ;
mail1 chp1 = PROJGRIL nu1 (MOTS 'ALEX' 'CHAN' 'SAWY' )
                          (PROG 5. 1984. 10. ) ;
xb = (1984. - 1977.) / (2004. - 1977.) ;
xbb = 1. - xb ;
tp = TABL ;
tf = TABL ;
tp . 1 = 0. 1. ;
tf . 1 = (42. * xbb) + (23. * xb) ;
tp . 2 = 2.5 1. ;
tf . 2 = 15. ;
tp . 3 = 0. 4. ;
tf . 3 = (8. * xbb) + (23. * xb) ;
tp . 4 = 2.5 4. ;
tf . 4 = (23. * xbb) + (8. * xb) ;
tp . 5 = 0. 6. ;
tf . 5 = (42. * xbb) + (4. * xb) ;
tp . 6 = 2.5 6. ;
tf . 6 = (4. * xbb) + (42. * xb) ;
MESS ' Point  |   Valeur       |   Valeur       | Erreur' ;
MESS '        |   theorique    |   interpolee   |       ' ;
MESS '--------|----------------|----------------|-------' ;
REPE b1 (DIME tp) ;
  ft = tf . &b1 ;
  pt = mail1 POIN 'PROC' (tp . &b1) ;
  fc = EXTR chp1 'JOHN' pt ;
  err1 = ABS ((fc - ft) / ft) ;
  MESS &b1 '|' ft '|' fc '|' err1 ;
  SI (err1 > tol1) ;
    MESS ; MESS ;
    MESS 'ECHEC DU CAS TEST !' ;
    ERREUR 4 ;
  FINSI ;
FIN b1 ;
SI itrac ;
  TRAC chp1 mail1 'TITR' 'Test sur une grille en dimension 5' ;
FINSI ;
MESS ; MESS ; MESS ;
MESS ; MESS ;
MESS 'SUCCES DU CAS TEST' ;
FIN ;
```

## Random_Set_Theory_01 [(sans section)]
```
* RSTHS.dgibi
* Random Set Theory analysis with a single trivial analytic function
* @PB(A,B,C,D) ==> (A*B) + (C*D)
GRAPH = VRAI ;
'OPTI' 'TRAC' 'PSC';
'OPTI' 'EPTR' 4 ;
'DEBP' @PB R*TABLE ;
* Analytical Function @PB
  !RV = ( (R.'A'.'VN' * R.'B'.'VN') + (R.'C'.'VN' * R.'D'.'VN') ) ;
'FINP' !RV ;
RS = OBJET @RSTH ;
R = 'TABL' ;
R.'A' ='TABL' ;
R.'A'.'MIN' ='PROG' 1.1 1.2 1.3 ;
R.'A'.'MAX' ='PROG' 1.4 1.5 1.6 ;
R.'A'.'CPB' ='PROG' 0.1 0.5 0.4 ;
R.'A'.'MINS' = RS%'SCV' R.'A'.'MIN' ;
R.'A'.'MAXS' = RS%'SCV' R.'A'.'MAX' ;
R.'A'.'CPBS' = RS%'SCS' R.'A'.'CPB' ;
EAN = ('EVOL' 'BOUT' 'MANU' 'MIN' R.'A'.'MINS' 'CPB' R.'A'.'CPBS' ) ;
EAX = ('EVOL' 'BRIQ' 'MANU' 'MAX' R.'A'.'MAXS' 'CPB' R.'A'.'CPBS' ) ;
R.'B' ='TABL' ;
R.'B'.'MIN' ='PROG' 3.1 3.2 ;
R.'B'.'MAX' ='PROG' 3.3 3.4 ;
R.'B'.'CPB' ='PROG' 0.2 0.8 ;
R.'B'.'MINS' = RS%'SCV' R.'B'.'MIN' ;
R.'B'.'MAXS' = RS%'SCV' R.'B'.'MAX' ;
R.'B'.'CPBS' = RS%'SCS' R.'B'.'CPB' ;
EBN = ('EVOL' 'BOUT' 'MANU' 'MIN' R.'B'.'MINS' 'CPB' R.'B'.'CPBS' ) ;
EBX = ('EVOL' 'BRIQ' 'MANU' 'MAX' R.'B'.'MAXS' 'CPB' R.'B'.'CPBS' ) ;
R.'C' ='TABL' ;
R.'C'.'MIN' ='PROG' 5.1 5.2 5.3 ;
R.'C'.'MAX' ='PROG' 5.4 5.5 5.6 ;
R.'C'.'CPB' ='PROG' 0.3 0.3 0.4 ;
R.'C'.'MINS' = RS%'SCV' R.'C'.'MIN' ;
R.'C'.'MAXS' = RS%'SCV' R.'C'.'MAX' ;
R.'C'.'CPBS' = RS%'SCS' R.'C'.'CPB' ;
ECN = ('EVOL' 'BOUT' 'MANU' 'MIN' R.'C'.'MINS' 'CPB' R.'C'.'CPBS' ) ;
ECX = ('EVOL' 'BRIQ' 'MANU' 'MAX' R.'C'.'MAXS' 'CPB' R.'C'.'CPBS' ) ;
R.'D' = 'TABL' ;
R.'D'.'MIN' ='PROG' 7.1 7.2 7.3 7.4;
R.'D'.'MAX' ='PROG' 7.5 7.6 7.7 7.8;
R.'D'.'CPB' ='PROG' 0.3 0.2 0.3 0.2;
R.'D'.'MINS' = RS%'SCV' R.'D'.'MIN' ;
R.'D'.'MAXS' = RS%'SCV' R.'D'.'MAX' ;
R.'D'.'CPBS' = RS%'SCS' R.'D'.'CPB' ;
EDN = ('EVOL' 'BOUT' 'MANU' 'MIN' R.'D'.'MINS' 'CPB' R.'D'.'CPBS' ) ;
EDX = ('EVOL' 'BRIQ' 'MANU' 'MAX' R.'D'.'MAXS' 'CPB' R.'D'.'CPBS' ) ;
RS%'RST' R ;
JX = R.'A'.'CX' ;
'REPE' J JX ;
  RS%'RSV' &J 0 ;
  RV = @PB R ;
  RS%'RSR' RV &J ;
'FIN' J ;
'SI' GRAPH ;
 'DESS' ( EAN 'ET' EAX )
  'TITX' 'Value A [1]'
  'POSX' 'CENT'
  'XBOR' 0.0 2.0
  'XGRA' 0.2
  'TITY' 'CPB [1]'
  'POSY' 'CENT'
  'YBOR' 0.0 1.0
  'YGRA' 0.1
  'TITR' 'Random Set Theory - Analytical computation'
  'GRIL' 'POIN' 'GRIS' ;
 'DESS' ( EBN 'ET' EBX )
  'TITX' 'Value B [1]'
  'POSX' 'CENT'
  'XBOR' 2.0 4.0
  'XGRA' 0.2
  'TITY' 'CPB [1]'
  'POSY' 'CENT'
  'YBOR' 0.0 1.0
  'YGRA' 0.1
  'TITR' 'Random Set Theory - Analytical computation'
  'GRIL' 'POIN' 'GRIS' ;
 'DESS' ( ECN 'ET' ECX )
  'TITX' 'Value C [1]'
  'POSX' 'CENT'
  'XBOR' 4.0 6.0
  'XGRA' 0.2
  'TITY' 'CPB [1]'
  'POSY' 'CENT'
  'YBOR' 0.0 1.0
  'YGRA' 0.1
  'TITR' 'Random Set Theory - Analytical computation'
  'GRIL' 'POIN' 'GRIS' ;
 'DESS' ( EDN 'ET' EDX )
  'TITX' 'Value D [1]'
  'POSX' 'CENT'
  'XBOR' 6.0 8.0
  'XGRA' 0.2
  'TITY' 'CPB [1]'
  'POSY' 'CENT'
  'YBOR' 0.0 1.0
  'YGRA' 0.1
  'TITR' 'Random Set Theory - Analytical computation'
  'GRIL' 'POIN' 'GRIS' ;
 'DESS' ( RS.'RT'.'EN' 'ET' RS.'RT'.'EX' )
  'TITX' 'Function PB [1]'
  'POSX' 'CENT'
  'XBOR' 30.0 60.0
  'XGRA' 5.0
  'TITY' 'CPB [1]'
  'POSY' 'CENT'
  'YBOR' 0.0 1.0
  'YGRA' 0.1
  'TITR' 'Random Set Theory - Analytical computation'
  'GRIL' 'POIN' 'GRIS' ;
'FINS' ;
'FIN' ;
```

## rotor_laval_poutre [(sans section)]
```
* Rotor de Laval
* Etude dans le repere inertiel (ou fixe) avec elements poutre de TIMO
* p2 kpal
* z=L +--/\/\/\--|
* p1a|
* =======+======= Mdisc, Ixyz
* p1b|
* z=0 +--/\/\/\--|
* p0
* Réf :
* [1] Vollan, Arne, and Louis Komzsik. "Computational techniques of rotor
* dynamics with the finite element method". CRC Press, 2012.]
* Mots-clés : Vibrations, calcul modal, machines tournantes,
* poutre, modes complexes, reponse frequentielle
* Auteur: Benoit Prabel, Mars 2020
* OPTIONS
* dimension, type d'elements geometriques, ...
  OPTI 'DIME' 3 'ELEM' 'SEG2';
* visualisation (sortie postscript)
  GRAPH = FAUX;
  OPTI 'TRAC' PSC 'EPTR' 12 'POTR' 'HELVETICA_16';
* DONNEES
* arbre (shaft)
  L = 1.0 ;
  Dshaft = 64.E-3;
* Disque (disc)
  zdisc = 0.5*L;
  Mdisc = 40.;
  Izdisc = 5. ;
* Materiau
  E1 = 2.1E11 ;
  nu1 = 0.3 ;
  rho1 = 7800. ;
  Visc1= 0.00001*E1;
* Palier
  kpal_x = 3.9E6;
  kpal_y = kpal_x;
  cpal_x = 1000.;
  cpal_y = cpal_x;
* Calculs preliminaires pour completer les donnees
* formule des caracteristiques des poutres a section circulaire creuse :
* Section = pi * ((Rext**2) - (Rint**2));
* Itorsion = pi * ((Rext**4) - (Rint**4)) / 2.;
* Iflexion = pi * ((Rext**4) - (Rint**4)) / 4.;
* on a un disque plein ==> Rint = 0
* on a les donnees (Mdisc et Idisc) integrees sur h et multipliee par rho1 :
* rho1 * h * pi * (R**2) = Mdisc
* rho1 * h * pi/2. * (R**4) = Izdisc
* (2)/(1) ==> 0.5*(R**2) = Izdisc/Mdisc ==> Rdisc = (2*Izdisc/Mdisc)**0.5
  Rdisc = (2*Izdisc/Mdisc)**0.5;
  hdisc = Mdisc / (rho1 * pi * (Rdisc**2));
  MESS 'Rdisc=' Rdisc ' hdisc=' hdisc;
* ==> caracteristiques geometriques de la poutre definissant le disque :
  Sdisc = pi * (Rdisc**2);
  Iz = pi/2. * (Rdisc**4);
  Ix = pi/4. * (Rdisc**4);
* caracteristique de l'arbre
  Rshaft = Dshaft /2.;
  Sshaft = pi * (Rshaft**2);
  Izshaft = pi/2. * (Rshaft**4);
  Ixshaft = pi/4. * (Rshaft**4);
* MAILLAGE
* PARAMETRES
  OPTI 'ELEM' SEG2;
  nL = 80;
  nVect = nL/16;
* POINTS
  p0 = 0. 0. 0.;
  p1a = 0. 0. (zdisc - hdisc);
  p1b = 0. 0. (zdisc + hdisc);
  p2 = 0. 0. L;
* points du palier
  ppal = p0 et p2;
* DROITES
  d1a = DROI (nL/2) p0 p1a;
  d2 = (DROI 1 p1a p1b) COUL 'BLEU';
  d1b = DROI (nL/2) p1b p2 ;
  d1 = d1a et d1b;
  dtot= d1 et d2;
* TRACE
si GRAPH;
  TRAC dtot 'TITRE' 'maillage';
finsi;
* ON VEUT QUELQUES POINTS POUR LE TRACE DE VECTEUR DANS POSTVIBR
  dVect = (DROI nVect p0 p1a) ET d2 ET (DROI nVect p1b p2);
  pVect = CHAN dVect 'POI1';
  ELIM dtot pVect (1.E-8*L);
* MODELE, MATERIAU, MATRICES
* 1 : arbre
mod1 = MODE d1 'MECANIQUE' TIMO;
mat1 = MATE mod1 'YOUNG' E1 'NU' Nu1 'RHO' Rho1
        'SECT' Sshaft 'INRY' Ixshaft 'INRZ' Ixshaft 'TORS' Izshaft
        'OMEG' 1. 'VISQ' Visc1;
* 2 : disque
mod2 = MODE d2 'MECANIQUE' TIMO;
mat2 = MATE mod2 'YOUNG' E1 'NU' Nu1 'RHO' Rho1
        'SECT' Sdisc 'INRY' Ix 'INRZ' Ix 'TORS' Iz
        'OMEG' 1. 'VISQ' Visc1;
mod12 = mod1 et mod2;
mat12 = mat1 et mat2;
* raideur, masse, couplage gyroscopique
K12 = RIGI mod12 mat12;
Mtot = MASS mod12 mat12;
Gtot = GYRO mod12 mat12;
* amortissement + amortissement corotatif
C12 KROT12 = AMOR mod12 mat12 'COROTATIF';
* 3 : paliers
* appuis = raideurs discretes
Kx3 = APPU 'UX' kpal_x ppal;
Ky3 = APPU 'UY' kpal_x ppal;
K3 = Kx3 et Ky3;
Cx3 = APPU 'UX' cpal_x ppal;
Cy3 = APPU 'UY' cpal_x ppal;
C3 = Cx3 et Cy3;
* autres conditions aux limites ?
bloZ = BLOQ 'UZ' 'RZ' ppal;
* assemblage
Ktot = K12 et K3 et bloZ;
Ctot = C12 et C3;
* MODES REELS
* PARAMETRES : on souhaite NbModR modes
  NbModR = 4;
* CALCUL
  TBasR1 = VIBR 'SIMUL' 1. NbModR Ktot Mtot;
* POST-TRAITEMENT
si GRAPH;
* tableau + deformees modale automatise via la procedure postvibr
* on peux customiser avec table d'options
  Toptions = TABL;
  Toptions .'MAILLAGE_VECTEUR' = pVect;
  POSTVIBR TBasR1 Toptions;
* quel est ce mode 3 ?
  phi3 = TBasR1 . 'MODES' . 3 . 'DEFORMEE_MODALE';
  TITRE 'Mode 3 : mode de torsion';
  TRAC (EXCO phi3 'RZ') dtot;
* c'est de la torsion !
* si on souhaite le supprimer, il faudrait bloquer plus de ddls RZ
sinon;
  POSTVIBR TBasR1 (MOTS 'TABL');
finsi;
* VIBR 'SIMUL' a detecte des modes doubles et il a donc ajoute un mode en plus
* retrouvons le vrai nombre avec une mini-boucle...
  NbModR = NbModR - 1 ;
  REPE bb; NbModR = NbModR + 1;
    SI (EXIS TBasR1 . 'MODES' (NbModR + 1));
      ITER bb;
    SINON;
      QUIT bb;
    FINSI;
  FIN bb;
  MESS 'nombre de modes reels fournis in fine par VIBR SIMUL='NbModR;
* CALCUL DU DIAGRAMME DE CAMPBELL
* (= EVOLUTION DES FREQUENCES COMPLEXES AVEC LA VITESSE DE ROTATION)
* OMEGA en RoundPerMinute
  PR_RPM = prog 0. 'PAS' 0.1E3 10.E3;
* on choisit l'unite pour OMEGA : RoundPerMinute, rad/s ou Hz(=tr/s)
* G est calcule pour 1 rad/s --> multiplier par FAC_G
  UNIT_OMEG = mot 'RPM' ; FAC_G = (2.*pi/60.); PROMEG = PR_RPM;
* UNIT_OMEG = mot 'rad/s'; FAC_G = 1.; PROMEG = (2.*pi/60.) * PR_RPM ;
* UNIT_OMEG = mot 'Hz' ; FAC_G = 2.*pi; PROMEG = PR_RPM / 60.;
  cha_x = chai '\W ('UNIT_OMEG')';
  NOMEG = DIME PROMEG;
* PROJECTION DES MATRICES ASSEMBLEES SUR LA BASE REELLE
  M1P = PJBA TBasR1 Mtot ;
* G est calcule pour 1 rad/s -> on mutliplie par FAC_G
  G1P = PJBA TBasR1 Gtot ;
  K1P = PJBA TBasR1 (K12 et K3) ;
  C1P = PJBA TBasR1 Ctot;
  KROT1P = PJBA TBasR1 KROT12;
* REM : il serait possible d'utiliser directement la procedure campbell,
* mais il semble plus pedagogique de reecrire ici la boucle et le calcul
* CREATION DE 2*NbModC LISTREELS DE TAILLE NOMEG
  NbModC = 2*NbModR;
  TfreqR = TABL;
  TfreqI = TABL;
  REPE BmodC NbModC;
    TfreqR . &BmodC = PROG NOMEG*0.;
    TfreqI . &BmodC = PROG NOMEG*0.;
  FIN BmodC;
* + 2 LISTREELS TEMPORAIRES DE TRAVAIL
  prWorkR = PROG NbModC*0.;
  prWorkI = PROG NbModC*0.;
* ON BOUCLE SUR LES FREQUENCES DE ROTATION Omega_j ---------------------
  REPE BOMEG NOMEG;
    Omega_j = EXTR PROMEG &BOMEG;
    MESS 'Calcul des modes complexes pour \W=' Omega_j ' ' UNIT_OMEG;
* on va resoudre : [ [K + W*C'] + iw [C + W*G] - w^2 [M] ] * \psi = 0
* G est calcule pour 1 rad/s -> on mutliplie par FAC_G
    K_j = K1P ET (Omega_j * KROT1P);
    C_j = C1P ET (Omega_j * FAC_G * G1P);
    M_j = M1P;
    TbasC_j = VIBC M_j K_j C_j ;
* extraction des frequences et tri par ordre croissant
    SI (&BOMEG EGA 1);
      ORDOVIBC TbasC_j;
* puis en minimisant la distance au resultat precedent
    SINON;
      ORDOVIBC TbasC_j TbasC_jm1;
    FINSI;
    prwR_j = TbasC_j . 'LISTE_FREQUENCES_REELLES' ;
    prwI_j = TbasC_j . 'LISTE_FREQUENCES_IMAGINAIRES' ;
* pour le prochain pas
    TbasC_jm1 = TbasC_j;
* on stocke dans les listreels finaux
    REPE BmodC NbModC;
      REMP (TfreqR . &BmodC) &BOMEG (EXTR prwR_j &BmodC);
      REMP (TfreqI . &BmodC) &BOMEG (EXTR prwI_j &BmodC);
    FIN BmodC;
  FIN BOMEG ;
* FIN DE LA BOUCLE SUR LES FREQUENCES DE ROTATION ----------------------
* POST-TRAITEMENT GRAPHIQUE
* on ne trace que les modes tq wR>0 -> i ={NbModC/2+1 ... NbModC}
  IFhalf = VRAI;
  si IFhalf; NC = NbModC/2; ideb = NC;
  sinon; NC = NbModC; ideb = 0;
  finsi;
  colors = @PALETTE NC;
  evfreqR = VIDE 'EVOLUTIO';
  evfreqI = VIDE 'EVOLUTIO';
  REPE BmodC NC;
    coco = EXTR colors &BmodC;
    i = ideb + &BmodC;
    evfreqR = evfreqR
    et (EVOL coco 'MANU' cha_x PROMEG 'w_{R} (Hz)' (TfreqR . i));
    evfreqI = evfreqI
    et (EVOL coco 'MANU' cha_x PROMEG 'w_{I} (/s)' (TfreqI . i));
  FIN BmodC;
si GRAPH;
  TITRE 'Campbell diagram';
  DESS evfreqR ;
  DESS evfreqI ;
finsi;
* POST-TRAITEMENT GRAPHIQUE
* On recombine les deformees Complexes issues de VIBC
  RECOVIBC TbasC_j TBasR1;
* Listing + trace des deformees Complexes issues de VIBC
  Topt = TABL;
  Topt . 'MAILLAGE_VECTEUR' = ppal;
  POSTVIBR TbasC_j Topt;
* opti donn 5 trac X;
* TEST DE NON REGRESSION
* ON TESTE JUSTE LE SUIVI
* preparation au calcul de la derivee
* abscisse
  dOMEG = ((ENLE PROMEG NOMEG) - (ENLE PROMEG 1));
  NdOMEG = NOMEG - 1;
* message
  opti echo 0;
  MESS (CHAI 'Mode'*4 'E[w]'*18 'E[dwR/dW]'*33 'max[dwR/dW]'*48 'E[dwI/dW]'*63 'max[dwI/dW]'*78);
* les courbes etant asse lineaire xtol = 10 est largement suffisant
  xtol = 10.;
* boucle sur les modes Complexes (i.e. sur les courbes)
  REPE BmodC NbModC;
* --- PARTIE REELLE ---
    wR = TfreqR . &BmodC;
    wRmoy = (SOMM wR) / NOMEG;
* calcul de la derivee
    dwRdW = ((ENLE wR NOMEG) - (ENLE wR 1)) / dOMEG;
* moyenne et valeur max
    dwRdWmoy = (SOMM dwRdW) / NdOMEG;
    dwRdWmax = MAXI 'ABS' dwRdW;
* --- PARTIE IMAGINAIRE ---
    wI = TfreqR . &BmodC;
    wImoy = (SOMM wI) / NOMEG;
* calcul de la derivee
    dwIdW = ((ENLE wI NOMEG) - (ENLE wI 1)) / dOMEG;
* moyenne et valeur max
    dwIdWmoy = (SOMM dwIdW) / NdOMEG;
    dwIdWmax = MAXI 'ABS' dwIdW;
* --- MESSAGE + TEST ---
* message
    MESS (CHAI &BmodC*4 wRmoy*18 dwRdWmoy*33 dwRdWmax*48 dwIdWmoy*63 dwIdWmax*78);
* test sur la derivee pour verifier la continuite
    dwdWref = MAXI 'ABS' (PROG dwRdWmoy dwIdWmoy 1.E-6);
    SI (dwRdWmax > (xtol*dwdWref)); ERRE 5; FINSI;
    SI (dwIdWmax > (xtol*dwdWref)); ERRE 5; FINSI;
  FIN BmodC;
  opti echo 1;
FIN ;
```

## satnsathoriz [(sans section)]
```
'OPTI' 'TRAC' PSC ;
GRAPH = FAUX ;
DEBPROC HHT_pro H1*FLOTTANT ;
T1 = H1 * BET ** N + 1. ** m * TSR + TR ;
FINPROC T1 ;
DEBPROC KKR_pro H0*FLOTTANT ;
* K0 = H0 * ALF EXP * KS ;
tt = HHT_PRO H0;
K0 = (tt '-' tr) '/' TSR ** ALF * KS ;
FINPROC K0 ;
DEBPROC TH_pro T1*FLOTTANT ;
H1 = T1 - TR / TSR ** M1 - 1. ** N1 / BET ;
FINPROC H1 ;
DEBPROC DHDT_pro H1*FLOTTANT T1*FLOTTANT ;
MESS 'Pour Frederic DEBUT';
MESS '(BET*H1)' (BET*H1);
MESS 'MOINSN' MOINSN;
MESS 'Valeur =' (BET*H1 ** MOINSN);
MESS ' ';
MESS 'Il y a la une puissance negative FLOTTANT d un ';
MESS 'FLOTTANT... au debut  ==> 3.36 ** -2.0304';
MESS 'Pour Frederic FIN';
FIN; COMM 'A retirer';
DHDT0 = BET*H1 ** MOINSN + 1. * H1 / (T1 - TR) * N1 * M1 ;
* MESS 'DHDT0' DHDT0;
DHDT0 = 1./BET *N1*M1*1./(TSR) *
        (((T1 - TR / TSR) ** M1 - 1.)
* (N1 - 1.)) *((T1 - TR / TSR) ** (M1 - 1.)) ;
* MESS 'DHDT0' DHDT0;
FINPROC DHDT0 ;
DEBPROC KINPHI int00*FLOTTANT ;
  phi0 = 0. ;
  mess 'int00' int00;
phit = (2* KS * PSI0) / (DT * int00) ;
  'MESS' 'phit' phit ;
* phi0 = 1.15;
  phi0 = phit;
  int0 = int00 - (phi0/2.); ;
  Int_p0 = prog int0 ;
  phi_p0 = prog phi0 ;
  repeter b1 (nb-1 );
    d0 = extr D2_prog &b1 ;
    phi0 = (2. * d0 / int0) + phi0 ;
    phi_p0 = phi_p0 et (prog phi0) ;
    int0 = int0 - phi0 ;
    Int_p0 = Int_p0 et (Prog int0) ;
  fin b1 ;
    d0 = extr D2_prog NB;
    phi0 = 2. * d0 / iNT0 + phi0 ;
    phi_p0 = phi_p0 et (prog phi0) ;
* list phi_p0 ;
* list int_p0 ;
     PNM1 = EXTR phi_p0 NB ;
     MESS 'PNM' PNM1 ;
     int = EXTR int_p0 NB ;
     MESS 'int' int ;
FINPROC phi_p0 Int_p0 ;
DEBPROC KPROG T00*FLOTTANT TN0*FLOTTANT NB0*ENTIER MO1*MOT ;
  DT = T00 - TN0 / NB0 ;
SI (EGA MO1 DEMI ) ;
MESS 'DEMI = ' MO1 ;
  T = T00 - (dt*0.5) ;
  h_pr0 = prog ;
  K_pr0 = prog ;
  D_pr0 = prog ;
  C_pr0 = prog ;
  T_pr0 = prog ;
    H = TH_pro T ;
    K = KKR_pro H ;
    DHDT = DHDT_pro H T ;
    D = K*DHDT ;
    C = 1./DHDT ;
  h_pr0 = prog H;
  K_pr0 = prog K;
  D_pr0 = prog D;
  C_pr0 = prog C;
  T_pr0 = prog T;
  T = T - DT ;
SINON ;
MESS 'TOTA = ' MO1 ;
    T = T00 ;
    H = TH_pro T ;
    K = KKR_pro H ;
    DHDT = DHDT_pro H T ;
    D = K*DHDT ;
    C = 1./DHDT ;
  h_pr0 = prog H;
  K_pr0 = prog K;
  D_pr0 = prog D;
  C_pr0 = prog C;
  T_pr0 = prog T;
  T = T - DT ;
FINSI;
  repe b0 nb0 ;
    H = TH_pro T ;
    K = KKR_pro H ;
    DHDT = DHDT_pro H T ;
    D = K*DHDT ;
    C = 1./DHDT ;
    h_pr0 = h_pr0 ET (prog H) ;
    K_pr0 = K_pr0 ET (prog K) ;
    D_pr0 = D_pr0 ET (prog D) ;
    C_pr0 = C_pr0 ET (prog C) ;
    T_pr0 = T_pr0 ET (prog T);
    T = T - DT ;
  FIN B0 ;
FINPROC h_pr0 K_pr0 D_pr0 C_pr0 T_pr0 ;
DEBPROC A x*FLOTTANT ;
si (x < 2.9 ) ;
X2 = (-1.)*X*X ;
A0 = X2 EXP * X * (1. - (ERF X) ** (-1.)) * RA2PI + (2.*X2) ;
sinon ;
X2 = X ** (-2.) * -0.5 ;
A0 = 108830.*X2+8162.*X2+706.*X2+74.*X2+10.*X2+2.*X2+1.;
* A0 = 8162.*X2+706.*X2+74.*X2+10.*X2+2.*X2+1.;
* A0 = 706.*X2+74.*X2+10.*X2+2.*X2+1.;
* A0 = 74.*X2+10.*X2+2.*X2+1.;
FINSI ;
FINPROC A0 ;
DEBPROC INTN phi*LISTREEL ;
PNM1 = EXTR phi NB ;
DD0 = EXTR D2_PROG NB ;
XX = PNM1 * 0.5D0 * (DD0 ** -0.5D0) ;
IC0 = PNM1*0.5D0 + (2.D0*DD0/PNM1*(A XX)) ;
FINPROC IC0 ;
'DEBPROC' CALPHILI ;
h_prog K_prog D_prog C_prog T_prog = KPROG T0 TN NB 'TOTA';
dinf = extr D_prog 1 ;
mess 'dinf' dinf;
dinf = extr D_prog 2 ;
mess 'dinf2' dinf;
T1 = extr T_prog 1 ;
mess 'T1' T1;
TN1 = extr T_prog (DIME T_prog) ;
T01 = extr T_prog 1 ;
db0 = 2. / ((T01 - TN1) ** 2.) ;
Y = T_prog - (prog (DIME T_prog)*TN1) * K_prog ;
KfH_evol = evol manu H_prog Y ;
* -------------------------- Dmoy par K
Db = (-1.) * ((INTG KfH_evol) extr 1) * db0 ;
* -------------------------- calcul de I 1/2 (j = 1)
* ????????????????????????????????????
Int = Db/pi**0.5*2.*nb ; 'MESS' 'Int' Int ;
* Int = 1.e-3/(ts - tn)*nb ;list Int ;
* Int = int * 2. ;
* opti donn 5 ;
* -------------------------- calcul de D (I + 1/2)
h2_prog K2_prog D2_prog C2_prog T2_prog = KPROG T0 TN nb DEMI ;
* -------------------------- calcul de PHI (I + 1/2)
phi_prog Int_prog = KINPHI Int ;
I2_evol = evol manu T_prog phi_prog ;
I2mi = I2_evol INTG * (-1.) / dt ; LIST I2mi ;
* I2_evol = evol manu phi_prog T_prog ;
* DESS I2_evol ;
* opti donn 5 ;
* -------------------------- calcul de ICHA (N - 1/2)
ICHA = INTN phi_prog ;
* -------------------------- DELTA (J=1)
DELTA = (EXTR Int_prog NB) - ICHA ;
* -------------------------- calcul de I 1/2 (j = 2)
int1 = int ;
Int = int1 - (DELTA * 0.5d0) ;
deltI = Int - Int1 ;
repeter b2 20 ;
* -------------------------- calcul de PHI (I + 1/2)
  phi_prog Int_prog = KINPHI Int ;
  'MESSAGE' 'valeur de xphi';
  'LISTE' ('EXTRAIRE' 1 phi_prog);
  I2_evol = evol manu T_prog phi_prog ;
  I2mi = I2_evol INTG * (-1.) / dt ;
* -------------------------- calcul de ICHA (N - 1/2)
  ICHA = INTN phi_prog ;
mess
'iter :' &b2 'icha' ICHA 'DELTA' DELTA 'Itot' (maxi I2mi) 'int' int;
* -------------------------- DELTA (J=1)
delta1 = DELTA ;
DELTA = (EXTR Int_prog NB) - ICHA ;
* -------------------------- calcul de I 1/2
int1 = int ;
* int = int1 - (DELTA * delta1 / (DELTA + delta1)) ;
* int = int1 - (DELTA * deltI / (DELTA + delta1)) ;
Int = int1 - (DELTA * 0.5d0 ) ;
deltI = Int - Int1 ;
si ( (DELTA abs) < (ICHA*1.e-4))
quitter b2 ;
finsi;
menage ;
fin b2 ;
'FINPROC' phi_prog h_prog T_prog ;
'MESS' 'Calcul de la solution de Philip en milieu saturé non saturé';
xf = 0.0;
'MESS' 'xf (frontiére saturé / non saturé) ' xf;
PSI0 = 1.D0;
'MESS' 'Quelle est la pression d injection dans le milieu saturé?' ;
mess 'PSI0' PSI0;
ALF = 0.08 * 100. ;
KS = 5.85E-2 / 3600. ;
TS = 0.3 ;
TR = 0.055 ;
TSR = TS - TR ;
N = 2.0304 ; N1 = 1./N ; MOINSN = (-1.)*N ;
M = -0.5075 ; M1 = 1./M ;
BET = -0.029227 * 100. ;
nb = 500 ;
H00 = -1.E-20 ;
* H00 = 0;
Hinf = -1.15D0 ;
RA2PI = PI ** (-0.5) * 2. ;
phi0 = 0. ;
HN = HINF ;
TN = HHT_pro HN ; LIST TN ;
HN = TH_pro TN ; LIST HN ;
KN = KKR_pro HN ; LIST KN ;
DHDTN = DHDT_pro HN TN ; LIST DHDTN ;
DN = KN*DHDTN ;
CN = 1./DHDTN ;
T0 = HHT_pro H00 ;
LIST (HN - (TH_pro (TN - 1.E-6)) / 1.E-6) ;
DT = T0 - TN / NB ;
LTEMPS = 'PROG' 1000. 'PAS' 1000. (1000. * 3.) ;
ntemps = 'DIME' LTEMPS ;
lastemps = 0. ;
TETSAT = TS ;
TETNSAT = HHT_pro HINF ;
OLDXDTET = (TETSAT - TETNSAT) * xf ;
* CALCUL DE PHI, H et TETA
  phi_prog h_prog t_prog = CALPHILI ;
   xfini = xf;
'REPETER' BTEMPS ntemps ;
   ttemps = 'EXTR' LTEMPS &BTEMPS ;
   DELTEMP = ttemps - lastemps ;
* profile de la charge dans la zone saturée
   LXSAT = 'PROG' 0. ;
   LHSAT = 'PROG' PSI0 ;
   LTETSAT = 'PROG' TETSAT ;
   LXNSAT = phi_prog * ((TTEMPS)** 0.5) ;
   ID = 'PROG' ('DIME' LXNSAT)*1. ;
   phif = EXTR phi_prog 1;
   mess 'phif' phif;
   xfr = xfini + (phif*(ttemps**0.5));
   mess 'xfr= 'xfr;
   LXNSAT = LXNSAT + (ID*xfini) ;
   LHNSAT = h_prog ;
   LTETNSAT = t_prog ;
   LX = LXSAT ET LXNSAT ;
   LTET = LTETSAT ET LTETNSAT ;
   LH = LHSAT ET LHNSAT ;
   'SI' (&BTEMPS 'EGA' 1) ;
* (LH = 'ORDO' LH CROISSANT);
      uun = 'PROG' ('DIME' LX) * 1.D0;
      courb = ('EVOL' 'MANU'(uun '-' LX) LH);
   'SINON' ;
* (LH = 'ORDO' LH CROISSANT) ;
      courb = courb 'ET' ('EVOL' 'MANU' (uun '-' LX) LH);
   'FINSI' ;
'FIN' BTEMPS ;
TAB1 = 'TABLE' ;
TAB1 . 'TITRE' = 'TABLE' ;
TAB1 . 'TITRE' . 1 = 'exacte 1000' ;
TAB1 . 'TITRE' . 2 = 'exacte 2000' ;
TAB1 . 'TITRE' . 3 = 'exacte 3000' ;
TAB1 . 1 = 'TIRR ';
TAB1 . 2 = 'TIRR ';
TAB1 . 3 = 'TIRR ';
'SI' (GRAPH);
dess (courb) LEGE TAB1;
'FINSI' ;
* CAS TEST : cacul.dgibi
* Test de fonctionnement de DARCYSAT en 2D sans effet de gravité.
* Infiltration d'eau dans une colonne horizontale de sable uniformément
* désaturé.
* - condition initiale : désaturation uniforme correspondant à une
* succion de 1,15 m ;
* - a l'instant initial, une extrémité de la colonne est noyée.
* La frontière est supposée rester a pression nulle ;
* Les options de modélisation declarées dans la table transmise à
* la procédure DARCYSAT sont les suivantes :
* - les effets gravitationnels ne sont pas pris en compte : pression =
* charge (indice GRAVITE absent ; valeur par défaut : FAUX);
* - Une liste de temps de sauvegarde est fournie en valeur de l'indice
* TEMPS_SAUVES ;
* - Le pas de temps est d'abord automatique (indice TEMPS_CALCULES absent)
* L'utilisateur fournit
* > le pas de temps initial (indice 'DT_INITIAL'),
* > le nombre d'itérations recherché par pas de temps (indice 'NITER')
* > le nombre de pas de temps (indice 'NPAS')
* - Le calcul est ensuite refais avec une liste de temps de calcul
* donnée à l'indice TEMPS_CALCULES ;
* - L'homogenéisation spatiale des propriétes physiques s'effectue
* par moyenne arithmétique des valeurs obtenues aux faces (indice
* HOMOGENEISATION de valeur DECENTRE)
* !!!!!!!!!!!!!!!!!!!!!!!!
* - La précision de convergence demandée est de 0,5 mm (indice RESIDU_MAX)
* cas test tiré du rapport DMT 97/25 :
* "Implémentation dans CASTEM 2000 d'un modèle de transfert hydrique
* en milieu poreux non saturé"
* CAS TEST : cacul.dgibi
'OPTION' 'ECHO' 1 ;
'SAUTER' 'PAGE';
'TITRE' 'infiltration horizontale dans le sable : cacul.dgibi' ;
'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
* 'OPTION' 'ISOV' 'LIGN' ;
* 'TRACER' 'PSC' ;
* Fonction qui calcule la perméabilité en fonction de la
* saturation réduite.
* Loi puissance :
* Perméabilité : K = Ks S^B
* Paramètres physiques à définir dans la table LOI :
* ALPHA : coef. B (s.d.)
* PERMSAT : coef. Ks, perméabilité à saturation (m/s)
* Entrée :
* LOI : table de données décrite ci-dessus
* SAT : saturation réduite
* TEST : mot facultatif 'NOTEST' qui permet de shunter les tests.
* Sortie :
* K1 : perméabilité totale en eau (m/s)
* Création maillage
* - Discrétisation :
ENX = 1 ;
ENY = 50 ;
'DENS' (1./eny) ;
* - Création des points et des droites
A0 = -0.5 1.0D0; B0 = 0.5 1.0D0;
'DENS' (1./eny) ;
A1 = -0.5 0.5D0; B1 = 0.5 0.5D0;
A2 = -0.5 0.25D0 ; B2 = 0.5 0.25D0 ;
A3 = -0.5 0.0D0; B3 = 0.5 0.0D0 ;
* - Création des droites
AB0 = 'DROIT' ENX A0 B0 ;
AB1 = 'DROIT' ENX A1 B1 ;
AB2 = 'DROIT' ENX A2 B2 ;
AB3 = 'DROIT' ENX A3 B3 ;
* - Creation des surfaces
MASSIF0 = AB3 'REGLER' AB2 'REGLER' AB1 'REGLER' AB0 ;
ENY = 'NBEL' MASSIF0 ;
ENTR = 'COULEUR' ('INVERSE' AB0) 'ROUGE' ;
SORT = 'COULEUR' (AB3) 'ROUGE' ;
'SI' GRAPH ;
  'TRACER' (MASSIF0 'ET' ENTR 'ET' SORT) ;
'FINSI' ;
* - Creation des maillages contenant tous les points
QFTOT = 'CHANGER' MASSIF0 'QUAF' ;
QFSORT = 'CHANGER' SORT 'QUAF' ;
QFENTR = 'CHANGER' ENTR 'QUAF' ;
'ELIMINATION' 0.00001 (QFTOT 'ET' QFSORT 'ET' QFENTR) ;
* - Modèles
MODHYB = 'MODELE' QFTOT 'DARCY' 'ISOTROPE' ;
MODENTR = 'MODELE' QFENTR 'DARCY' 'ISOTROPE' ;
MODSORT = 'MODELE' QFSORT 'DARCY' 'ISOTROPE' ;
CEENTR = 'DOMA' MODENTR 'CENTRE' ;
CESORT = 'DOMA' MODSORT 'CENTRE' ;
HYCEN = 'DOMA' MODHYB 'CENTRE' ;
HYFAC = 'DOMA' MODHYB 'FACE';
* - Création ligne de suivi pour le post-traitement et le test
* ligne des points centres (cas 1D)
'REPETER' BCL (ENY - 1) ;
    IP = &BCL ;
    JP = IP + 1 ;
    PI = 'POINT' HYCEN IP ;
    PJ = 'POINT' HYCEN JP ;
   'SI' (IP 'EGA' 1);
      LCENC = ('MANU' 'SEG2' PI PJ) ;
   'SINON' ;
      LCENC = LCENC 'ET' ('MANU' 'SEG2' PI PJ) ;
   'FINSI' ;
 FIN BCL ;
* - pression initiale (metre d'eau) dans le sable
HN = -1.15 ;
* - Conditions aux limites
* GBM modifie supprime bloque
* - frontière en limite du domaine de calcul (milieu désaturé)
ESORT = 'MANU' 'CHPO' CESORT 1 'TH' HN 'NATURE' 'DISCRET';
* - frontière mouillée
EENTR = 'MANU' 'CHPO' CEENTR 1 'TH' 1. 'NATURE' 'DISCRET';
* - chargement des CLs
LICALC = 'PROG' 0.D0 1.e20 ;
LIST1 = 'PROG' 2 * 1.D0 ;
VALI0 = 'CHAR' 'THIM' (ESORT et EENTR) ('EVOL' 'MANU' LICALC LIST1) ;
* - initialisation des inconnues
* (doit être compatible avec les conditions aux limites)
* - trace de charge d'eau
* TH0 = 'MANU' 'CHPO' ('DIFF' CEENTR HYFAC) 1 'TH' HN 'NATURE' 'DISCRET';
* TH0 = TH0 + SIMPE ;
* - charge d'eau
H0 = 'MANU' 'CHPO' HYCEN 1 'H' HN 'NATURE' 'DIFFUS';
H0 = 'MASQUE' ('COORDONNEE' 2 ('DOMA' modhyb centre))
             SUPERIEUR 0.98D0;
H0 = 1 '-' H0;
H0 = (HN * H0) + ((1.D0 - H0) * 1.D0);
H0 = 'NOMC' 'H' H0 NATURE DISCRET;
'TRACER' ('KCHA' MODHYB H0 'CHAM') modhyb;
* - flux
QFACE0 = 'MANU' 'CHPO' HYFAC 1 'FLUX' 0.D0 'NATURE' 'DISCRET' ;
* = Table DARCY_TRANSITOIRE =
* - initialisation table
SATUR = 'TABLE' ;
SATUR. 'TEMPS' = 'TABLE' ;
SATUR. 'CHARGE' = 'TABLE' ;
SATUR. 'FLUX' = 'TABLE' ;
SATUR . 'ITMAX' = 45;
* - données géommétriques
SATUR. 'SOUSTYPE' = 'DARCY_TRANSATUR' ;
SATUR. 'MODELE' = MODHYB ;
* - instant initial
SATUR. 'TEMPS' . 0 = 0. ;
SATUR. 'CHARGE' . 0 = 'COPIER' H0 ;
SATUR. 'FLUX' . 0 = 'COPIER' QFACE0 ;
* GBM
* - conditions aux limites et chargements
* SATUR. 'BLOCAGES_DARCY' = BSORT 'ET' BENTR ;
* SATUR. 'CHARGEMENT' = VALI0 ;
SATUR . 'TRACE_IMPOSE' = VALI0 ;
SATUR . 'LUMP' = FAUX;
SATUR . 'TYPDISCRETISATION' = 'VF' ;
* GBM MODIFIE
TABRES = table METHINV;
TABRES . 'TYPINV' = 1;
TABRES . 'PRECOND' = 5;
SATUR . 'METHINV' = TABRES;
SATUR . 'METHINV' . RESID = 1.D-20;
* - données physiques
* loi de perméabilité
LoiP = 'TABLE' 'PUISSANCE';
LoiP. 'ALPHA' = 8. ;
LoiP. 'PERMSAT' = 5.85E-2 / 3600. ;
SATUR.'LOI_PERMEABILITE' = 'TABLE' LoiP ;
* loi de succion
LoiS = 'TABLE' 'VAN_GENUCHTEN';
LoiS. 'PORO' = 0.3 ;
LoiS. 'TERESIDU' = 0.055 ;
LoiS. 'NEXP' = 2.0304 ;
LoiS. 'MEXP' = 0.5075 ;
LoiS. 'BHETA' = 0.029227 * 100. ;
SATUR.'LOI_SATURATION' = 'TABLE' LoiS ;
SATUR . 'COEF_EMMAGASINEMENT' = 0.D-6;
* SATUR . 'XI' = 1.D-5;
* - données numériques
SATUR. 'TEMPS_FINAL' = 2000.D0 ;
SATUR. 'HOMOGENEISATION' = 'CHAINE' 'DECENTRE' ;
 SATUR.'SOUS_RELAXATION' = 1.;
SATUR. 'NPAS' = 10000 ;
SATUR. 'RESIDU_MAX' = 1.D-4 ;
SATUR. 'NITER' = 10 ;
SATUR. 'DT_INITIAL' = 0.1D0 ;
SATUR. 'TEMPS_SAUVES' = ('PROG' 1 'PAS' 1 2.)*1000. ;
* SATUR. 'TEMPS_CALCULES' = ('PROG' 1 'PAS' 1 3.)*1000. ;
SATUR. 'MESSAGES' = 2 ;
* - Vérification du choix du dp minimum pour le calcul de la capacité.
* droite support des variables
dx = 'DROIT' (0. -1.15 ) 1000 (0. 0.) ;
zc = 'COOR' dx 2 ;
ev2 = 'EVOL' 'BLEU' 'CHPO' zc 'SCAL' dx ;
px = 'EXTR' ev2 'ORDO' ;
* calcul de la teneur en eau pour la pression zc
s0 t0 cap = HT_PRO (SATUR.'LOI_SATURATION') ZC ;
ev0 = 'EVOL' 'TURQ' 'CHPO' s0 'SCAL' dx ;
evt = 'EVOL' 'VERT' 'MANU' px (100. * ('EXTR' ev0 'ORDO')) ;
'SI' GRAPH ;
  'DESSIN' evt 'TITX' 'Pc(m)' 'TITY' 'S(%)'
               'TITRE' 'Loi capillaire S(Pc)' ;
'FINSI' ;
* calcul de la teneur en eau pour la pression zc - dp
dp = 1.e-4 ;
s1 t1 cap = HT_PRO (SATUR.'LOI_SATURATION')
              ('KOPS' zc '-' dp) ;
* représentation de la capacité
c1 = (t0 - t1) / dp;
ev1 = 'EVOL' 'ROUGE' 'CHPO' c1 'SCAL' dx ;
evc = 'EVOL' 'JAUNE' 'MANU' px ('EXTR' ev1 'ORDO') ;
'SI' GRAPH ;
  'DESSIN' evc 'TITX' 'Pc(m)' 'TITY' 'Capa(1/m)'
               'TITRE' 'Capacite capillaire' ;
'FINSI' ;
* | 1er CALCUL |
* - fonctionnement avec temps automatiques
DARCYSAT SATUR ;
* Post-traitement
  LT = 'LECT' 0 PAS 1 ((dime SATUR.TEMPS) - 1) ;
  liopt = 'MOTS' 'MIMA' 'AXES';
  TDES = TRACHIS SATUR 'CHARGE' LCENC LT 'PREF' ' ' 'UNIT' 's' ;
* le fichier lu est produit par resanalyphilhorsatnsat.dgibi
  LT = 'LECT' 1 'PAS' 1 (('DIME' SATUR.'TEMPS') - 1) ;
  liopt = 'MOTS' 'MIMA' 'AXES';
  TDES = TRACHIS SATUR 'CHARGE' LCENC LT 'PREF' ' ' 'UNIT' 's' ;
  TDES . 3 = 'TABLE' ;
  TDES . 3 . VALEUR = 'EXTRAIRE' courb 'COUR' 1;
  TDES . 3 . LEGEND2 = TAB1 . TITRE . 1;
  TDES . 3 . LEGEND1 = ' ' ;
  TDES . 4 = 'TABLE' ;
  TDES . 4 . VALEUR = 'EXTRAIRE' courb 'COUR' 2;
  TDES . 4 . LEGEND2 = TAB1 . TITRE . 2;
  TDES . 4 . LEGEND1 = ' ' ;
* TDES . 5 = 'TABLE' ;
* TDES . 5 . VALEUR = 'EXTRAIRE' courb 'COUR' 3;
* TDES . 5 . LEGEND2 = TAB1 . TITRE . 3;
* TDES . 5 . LEGEND1 = ' ' ;
'SI' GRAPH ;
  DESTRA TDES liopt 'TITX' 'z (m)' 'TITY' 'Pw (m)' ;
'FINSI' ;
toto = 'PRIM' TDES . 2 . VALEUR;
inta1 = 'EXTRAIRE' toto 'ORDO';
inta1 = 'EXTRAIRE' ('DIME' inta1) inta1;
'LISTE' inta1;
err1 = 'ABS' (inta1);
'LISTE' err1;
'SI' ((err1 '-' 2.95D-2) > 1.D-3) ;
   'ERREUR' 5;
'FINSI' ;
* opti donn 5;
* | 2nd CALCUL |
* - fonctionnement avec une liste de temps calculés
SATUR. 'TEMPS' = 'TABLE' ;
SATUR. 'TRACE_CHARGE' = 'TABLE' ;
SATUR. 'CHARGE' = 'TABLE' ;
SATUR. 'FLUX' = 'TABLE' ;
SATUR. 'TEMPS' . 0 = 0. ;
SATUR. 'TRACE_CHARGE' = TABLE ;
SATUR. 'CHARGE' . 0 = H0 ;
SATUR. 'FLUX' . 0 = QFACE0 ;
SATUR . 'TYPDISCRETISATION' = 'EFMH' ;
DARCYSAT SATUR ;
* Post-traitement
* -- Test de non régression
* Le test est effectué en vérifiant la solution
* - solution après 10 pas de temps
* -- Tracé (tous les temps)
  LT = 'LECT' 0 'PAS' 1 (('DIME' SATUR.'TEMPS') - 1) ;
  liopt = 'MOTS' 'MIMA' 'AXES';
  TDES = TRACHIS SATUR 'CHARGE' LCENC LT 'PREF' ' ' 'UNIT' 's' ;
    LT = 'LECT' 1 'PAS' 1 (('DIME' SATUR.'TEMPS') - 1) ;
  liopt = 'MOTS' 'MIMA' 'AXES';
  TDES = TRACHIS SATUR LCENC 'CHARGE' LT 'PREF' ' ' 'UNIT' 's' ;
  TDES . 3 = 'TABLE' ;
  TDES . 3 . VALEUR = 'EXTRAIRE' courb 'COUR' 1;
  TDES . 3 . LEGEND2 = TAB1 . TITRE . 1;
  TDES . 3 . LEGEND1 = ' ' ;
  TDES . 4 = 'TABLE' ;
  TDES . 4 . VALEUR = 'EXTRAIRE' courb 'COUR' 2;
  TDES . 4 . LEGEND2 = TAB1 . TITRE . 2;
  TDES . 4 . LEGEND1 = ' ' ;
'SI' GRAPH ;
   DESTRA TDES liopt 'TITX' 'z (m)' 'TITY' 'Pw (m)' ;
'FINSI' ;
toto = 'PRIM' TDES . 2 . VALEUR;
inta2 = 'EXTRAIRE' toto 'ORDO';
inta2 = 'EXTRAIRE' ('DIME' inta2) inta2;
'MESSAGE' inta1 inta2;
err2 = 'ABS' (inta2);
'LISTE' err2;
'SI' ((err2 '-' 1.22D-2) > 1.D-3) ;
   'ERREUR' 5;
'FINSI' ;
'MESSAGE' err1 err2;
'FIN';
```

## ssch [(sans section)]
```
 SAUT PAGE ;
* test elementaire de l'operateur ssch
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
opti dime 2 ;
pa = 0.0 0.0 ;
pb = 1.0 0.0 ;
pc = 1.0 1.0 ;
pd = 0.0 1.0 ;
su = manu qua4 pa pb pc pd ;
sup = chan su poi1 ;
tabdon = table ;
tabdon . iden = lect 1 101 ;
tabchi = chi1 tabdon COMP ('CHAINE' DIVERS '/COMPOM')
                     LOGK ('CHAINE' DIVERS '/COMPOM') ;
tbparm = table ;
tbparm . itmax = 40 ;
tbparm . eps = 1.d-4 ;
tbparm . sortie = mots 'SOLU' ;
tchi = table ;
tchi . soustype = donnees_chimiques ;
tchi . tot = manu chpo sup 2 x001 (prog 5.d-5 5.d-4 1.d-3 2.d-5 )
                              x101 (prog 5.d-5 1.d-3 5.d-4 1.d-5 ) ;
tchi . logc = manu chpo sup 2 x001 -4.
                              x101 -4. ;
tachi = chi2 tabchi tbparm tchi ;
dfi = manu chpo sup 2 x001 (prog 0.d0 1.d-5 2.e-5 0.d0)
                      x101 (prog 0.d0 1.d-5 3.e-5 0.d0) ;
cc = tachi . solu ;
dcc = manu chpo sup 3 w001 (prog 1.e-6 0.0 0.0 2.e-6)
                      w002 (prog 2.e-6 0.0 0.0 3.e-6)
                      w003 (prog 3.e-6 0.0 0.0 1.e-6) ;
res = ssch tabchi dfi cc dcc ;
tes = manu chpo sup 3 w001 (prog 1.d-6 6.4432d-6 9.4077d-6 3.d-6)
                      w002 (prog 1.d-6 6.4432d-6 1.94077d-5 3.d-6)
                      w003 (prog -1.d-6 3.5567d-6 1.05923d-5 -3.d-6);
ver = ( abs(res - tes) )masque superieur 1.d-5 somme ;
si (ver ega 0) ;
  erre 0 ;
sinon ;
  erre 5 ;
finsi ;
fin ;
```

## test-coller1 [(sans section)]
```
* CAS TEST DE VERIFICATION DE COLLER1
OPTI DIME 3 ELEM QUA4 ;
* ----------------------------- MAILLAGE ------------------------------
* Maillage poutre
P1 = 0. 0. 0. ;
PZ1 = 0. 0. 1. ;
POUT1 = DROI 1 P1 PZ1 ;
* Maillage Coque
VX = 2. ;
PCOQ1 = P1 MOIN (VX 1. 0.) ;
PCOQ2 = P1 PLUS (VX -1 0.) ;
LCOQ1 = DROI 2 PCOQ1 PCOQ2 ;
SCOQ1 = LCOQ1 TRAN 2 (0. 2. 0.) ;
P2 = P1 'PLUS' (VX 0. 0.) ;
P2 = SCOQ1 'POIN' 'PROC' P2 ;
V0 = P2 'MOINS' P1 ;
N0 = 'NORME' V0 ;
ELIM POUT1 SCOQ1 1.E-9 ;
REP1 = @REPERE P1 (PROG 3 * 0.2) VRAI TURQ ;
MTOT = POUT1 et SCOQ1 ;
* ---------------------- CONDITIONS AUX LIMITES -----------------------
* Conditions aux limites
BL1 = BLOQ UX UY UZ RX RY PZ1 ;
BL2 = BLOQ RZ PZ1 ;
BL3 = BLOQ UX UY P1 ;
COL1 = COLLER1 SCOQ1 POUT1 ;
BLOT = BL1 ET BL2 ET BL3 ET COL1 ;
* ---------------------------- CHARGEMENT -----------------------------
* Chargement
ANG_Z = 15. ;
ROT1 = DEPI BL2 (ANG_Z*pi/180.) ;
SCOQ2 = SCOQ1 'TOUR' ANG_Z P1 PZ1 ;
* ------------------------------ MODELES -------------------------------
* Modele
e = 10. ;
SECT5 = e*e ;
INRY5 = SECT5*SECT5/12. ;
INRZ5 = INRY5;
TORS5 = INRY5 + INRZ5;
Y_LOCAL = 0. 0. 0.;
MOP = MODE POUT1 MECANIQUE ELASTIQUE POUT ;
MAP = MATE MOP YOUN 200.E9 NU 0.3 ;
MAP = MAP ET (CARA MOP 'INRY' INRY5 'INRZ' INRZ5 'SECT' SECT5
                       'TORS' TORS5 'VECT' Y_LOCAL);
MOC = MODE SCOQ1 MECANIQUE ELASTIQUE COQ4 ;
MAC = MATE MOC YOUN 200.E9 NU 0.3 EPAI 1.;
MODTOT = MOC ET MOP ;
MATTOT = MAC ET MAP ;
RIGTOT = RIGI MODTOT MATTOT ;
BLOTOT = RIGTOT ET BLOT ;
* ---------------------------- RESOLUTION -----------------------------
NBF = 10 ;
L_TPS = PROG 0. PAS (ANG_Z/NBF) ANG_Z ;
N_PAS = DIME L_TPS ;
L_ANG = PROG 0. PAS (1./(N_PAS-1)) 1. ;
EVOLC = EVOL MANU L_TPS L_ANG ;
TAB1 = TABLE ;
TAB1 . 'MODELE' = MODTOT ;
TAB1 . 'CARACTERISTIQUES' = MATTOT ;
TAB1 . 'BLOCAGES_MECANIQUES' = BLOT ;
TAB1 . 'CHARGEMENT' = 'CHAR' 'DIMP' ROT1 EVOLC ;
TAB1 . 'GRANDS_DEPLACEMENTS' = VRAI ;
TAB1 . 'TEMPS_CALCULES' = L_TPS ;
TAB1 . 'HYPOTHESE_DEFORMATIONS' = 'LINEAIRE' ;
PASAPAS TAB1 ;
CONF0 = 'FORM' ;
FORM (TAB1.'DEPLACEMENTS'. NBF) ;
V1 = P2 'MOINS' P1 ;
FORM CONF0 ;
N1 = 'NORME' V1 ;
PSV01 = 'PSCA' V0 V1 ;
COS01 = PSV01 / (N0*N1) ;
ANG01 = ACOS COS01 ;
MESS 'ANGLE IMPOSE  ' ANG_Z ;
MESS 'ANGLE PASAPAS ' ANG01 ;
ERRANG = (ABS (ANG_Z-ANG01)) / ANG_Z ;
'SI' ('>' ERRANG 0.01) ;
  'ERRE' 5 ;
'FINSI' ;
FIN ;
```

## test2_fun_gultifr [(sans section)]
```
* Test sur la procedure G_ULTIFR (fonction pour determiner
* la position de l'etat de contraint courant par rapport à la surface
* de capacité
* Test pour l'option poutre courte
* b=0.3
* h=0.4
* c=0.025
* armature long 4f12
* cadre phi 8
* s = 0.95 m
* ly=1.0
* lz=1.5
* Develloppé par Alberto FRAU /DEN/DANS/DM2S/SEMT/EMSI
* et Nicolas ILE /DEN/DANS/DM2S/SEMT/EMSI
* donnée d'entrée
B_Y1 = 0.3;
B_Z1 = 0.4;
LTOT1Y = 1.0;
LTOT1Z = 1.5;
S_CAD1 = 0.95;
PHI_LON1 = 12.0;
ENR1 = 0.025;
A_CADRE1 = (2.0)*((PI)*((0.004)**(2.0)));
A_CADRE2 = (2.0)*((PI)*((0.004)**(2.0)));
* calcul des armatures longitudinales
ALL1 = (4.0)*((PI)*(((PHI_LON1*PHI_LON1)/(1.E6))/(4.0)));
* om_sy et om_sz
OM_SY1 = ((ALL1)*(500.E6))/(((B_Y1)*(B_Z1))*(25.E6));
OM_SZ1 = ((ALL1)*(500.E6))/(((B_Y1)*(B_Z1))*(25.E6));
* om_wy et om_wz
OM_WZ1 = ((A_CADRE1)*(500.E6))/(((B_Y1)*(S_CAD1))*(25.E6));
OM_WY1 = ((A_CADRE2)*(500.E6))/(((B_Z1)*(S_CAD1))*(25.E6));
* lamy ety lamz
LAMB_Y1 = ((LTOT1Z)/(B_Y1));
LAMB_Z1 = ((LTOT1Y)/(B_Z1));
* chiy et chiz
CHI_Z1 = ((B_Z1 - ((2.0)*(ENR1)))/(B_Z1));
CHI_Y1 = ((B_Y1 - ((2.0)*(ENR1)))/(B_Y1));
* test pour savoir si on est dans le cas du poteau court ou long
VAL_TT1 = LAMB_Y1 <EG (OM_SY1/OM_WY1);
VAL_TT2 = LAMB_Z1 <EG (OM_SZ1/OM_WZ1);
* calcul de Vymax et Vzmax
TAN_Y1 = (((LAMB_Y1**2.0) + 1.0)**(0.5)) - LAMB_Y1;
TAN_Z1 = (((LAMB_Z1**2.0) + 1.0)**(0.5)) - LAMB_Z1;
VY_MAX1 = OM_WY1*CHI_Y1 + ((0.5 - OM_WY1)*(TAN_Y1));
VZ_MAX1 = OM_WZ1*CHI_Z1 + ((0.5 - OM_WZ1)*(TAN_Z1));
VY_MAX1 = ((VY_MAX1)*(((B_Y1)*(B_Z1))*(25.e6)));
VZ_MAX1 = ((VZ_MAX1)*(((B_Y1)*(B_Z1))*(25.e6)));
* calcul des differentes valeur de N pour les trois zone dans le
* diagramme d'interaction
N_TRAC1 = ((OM_SY1)*(((B_Y1)*(B_Z1))*(25.e6)));
N_COMP1 = ((1.0 + OM_SY1)*(((B_Y1)*(B_Z1))*(-25.e6)));
N_LIMY1 = 0.5 + OM_SY1 - ((OM_WY1)*(LAMB_Y1 + 1.0 - CHI_Y1));
N_LIMY2 = 0.5 - OM_SY1 + ((OM_WY1)*(LAMB_Y1 - 1.0 + CHI_Y1));
N_LIMZ1 = 0.5 + OM_SZ1 - ((OM_WZ1)*(LAMB_Z1 + 1.0 - CHI_Z1));
N_LIMZ2 = 0.5 - OM_SZ1 + ((OM_WZ1)*(LAMB_Z1 - 1.0 + CHI_Z1));
N_LIMY1 = ((N_LIMY1)*(((B_Y1)*(B_Z1))*(-25.e6)));
N_LIMY2 = ((N_LIMY2)*(((B_Y1)*(B_Z1))*(-25.e6)));
N_LIMZ1 = ((N_LIMZ1)*(((B_Y1)*(B_Z1))*(-25.e6)));
N_LIMZ2 = ((N_LIMZ2)*(((B_Y1)*(B_Z1))*(-25.e6)));
* Test1 (Zone 2) Vz= Vzmax N=(N1z+N2z)/2.0
TB1 = TABLE;
TB1.'TYPE' = CHAINE 'PT_COURT';
TB1.'NN' = (N_LIMZ1 + N_LIMZ2)/(2.0);
TB1.'VY' = 0.0;
TB1.'VZ' = VZ_MAX1;
TB1.'MT' = 0.0;
TB1.'MY' = 0.0;
TB1.'MZ' = 0.0;
TB1.'BY' = B_Y1;
TB1.'BZ' = B_Z1;
TB1.'FCD' = 25.e6;
TB1.'FSD' = 500.e6;
TB1.'WSY' = OM_SY1;
TB1.'WSZ' = OM_SZ1;
TB1.'WWY' = OM_WY1;
TB1.'WWZ' = OM_WZ1;
TB1.'LY' = LAMB_Y1;
TB1.'LZ' = LAMB_Z1;
TB1.'XIY' = CHI_Y1;
TB1.'XIZ' = CHI_Z1;
VAL1Z = G_ULTIFR TB1;
* Test2 (Zone 2) Vz= Vzmax N=(N1z+N2z)/2.0
TB1.'NN' = (N_LIMZ1);
VAL2Z = G_ULTIFR TB1;
TB1.'NN' = (N_LIMZ2);
VAL3Z = G_ULTIFR TB1;
* Test3 N=Ntrac
TB1.'NN' = N_TRAC1;
TB1.'VY' = 0.0;
TB1.'VZ' = 0.0;
VAL4 = G_ULTIFR TB1;
* Test4 N=Ntrac
TB1.'NN' = N_COMP1;
TB1.'VY' = 0.0;
TB1.'VZ' = 0.0;
VAL5 = G_ULTIFR TB1;
SI ((ABS(VAL1Z)) > 1.E-8);
  ERRE 5;
FINSI;
SI ((ABS(VAL2Z)) > 1.E-8);
  ERRE 5;
FINSI;
SI ((ABS(VAL3Z)) > 1.E-8);
  ERRE 5;
FINSI;
SI ((ABS(VAL4)) > 1.E-8);
  ERRE 5;
FINSI;
SI ((ABS(VAL5)) > 1.E-8);
  ERRE 5;
FINSI;
FIN;
```

## testkfpt [(sans section)]
```
opti dime 2 elem QUA4;
nx = 1000;ny = 5;
p0=0 0;
p1 = 30. 0. ;
co1= p0 d dini 0.001 dfin 1. p1;
DISCR= QUAF;
* DISCR= MACRO;
COMPLET = FAUX ;
Si (NON COMPLET);
 DISCR= LINE;
p1 = 1. 0. ;
co1= p0 d 5 p1;
FINSI;
Mco1 = chan QUAF co1;
$co1 = mode Mco1 'NAVIER_STOKES' DISCR;
co1 = doma $co1 maillage ;
YP = 0.001;
 uet = ((coor 1 co1)*0.5+1.e-5);
 teta= (coor 1 co1);
 RO = 1. ;
 CP = 1. ;
 mu = 1.e-6 ;
 lb = 1.e-6;
 alpha = lb / ro*cp ;
 h = kfpt $co1 RO mu CP lb uet yp ;
 yplus = ro * yp * uet / mu;
 tetap = ro * cp * uet *(inve h);
 y1 = extr (evol chpo yplus co1) 'ORDO';
 t1 = extr (evol chpo tetap co1) 'ORDO';
 ev1 = evol 'MANU' 'Y+' y1 'TETA+' t1 ;
 pr = mu/alpha;
 Si COMPLET;
 dess ev1 TITR (chai 'Prandtl ' pr)'XBOR' 1. 1.e3 'LOGX';
 Finsi ;
 mu = 1.e-7;
  h = kfpt $co1 RO mu CP lb uet yp ;
 yplus = ro * yp * uet / mu;
 tetap = ro * cp * uet *(inve h);
 y1 = extr (evol chpo yplus co1) 'ORDO';
 t1 = extr (evol chpo tetap co1) 'ORDO';
 ev01 = evol 'MANU' 'Y+' y1 'TETA+' t1 ;
 pr = mu/alpha;
 mu = 1.e-5;
  h = kfpt $co1 RO mu CP lb uet yp ;
 yplus = ro * yp * uet / mu;
 tetap = ro * cp * uet *(inve h);
 y1 = extr (evol chpo yplus co1) 'ORDO';
 t1 = extr (evol chpo tetap co1) 'ORDO';
 ev10 = evol 'MANU' 'Y+' y1 'TETA+' t1 ;
 pr = mu/alpha;
 Si COMPLET;
 dess (ev1 et ev01 et ev10) 'XBOR' 1. 1.e3 'LOGX';
 Finsi ;
FIN ;
```

## test_coupe [(sans section)]
```
* Un petit cas test de l'operateur COUP
* Options generales
OPTI 'DIME' 3 'ELEM' 'CUB8' ;
itrac = FAUX ;
* Maillage
p1 = 0. 0. 0. ;
p2 = 1. 0. 0. ;
p3 = 1. 1. 0. ;
p4 = 0. 1. 0. ;
d1 = DROI 2 p1 p2 ;
d2 = DROI 2 p2 p3 ;
d3 = DROI 2 p3 p4 ;
d4 = DROI 2 p4 p1 ;
s = SURF (d1 ET d2 ET d3 ET d4) 'PLAN' ;
v = s VOLU TRAN 10 (0. 0. 10.) ;
* Plan de coupe et coupe du maillage
pc1 = 0. 0. 3.1 ;
pc2 = 1. 0. 3.1 ;
pc3 = 0. 1. 4.3 ;
pc = pc1 ET pc2 ET pc3 ;
s1 = COUP v pc1 pc2 pc3 ;
* Controle du maillage de la section
* verification avec VERM
VERM s1 ;
* les points sont ils bien dans le plan ?
ps1 = s1 POIN 'PLAN' pc1 pc2 pc3 1.E-10 ;
SI ((NBNO ps1) NEG (NBNO s1)) ;
  ERRE 'Les points du maillage de la coupe ne sont pas dans le plan !' ;
FINSI ;
* trace du maillage
SI itrac ;
  TRAC ((ARET v) ET (pc COUL 'ROUG') ET (s1 COUL 'VERT')) ;
FINSI ;
FIN ;
```

## test_lapn [(sans section)]
```
'OPTI' 'DIME' 3 'ELEM' 'QUA4' ;
* AX
AX11 = 1./3. ; AX12 = -1./3. ; AX13 = -1./6. ; AX14 = 1./6. ;
AX21 = -1./3. ; AX22 = 1./3. ; AX23 = 1./6. ; AX24 = -1./6. ;
AX31 = -1./6. ; AX32 = 1./6. ; AX33 = 1./3. ; AX34 = -1./3. ;
AX41 = 1./6. ; AX42 = -1./6. ; AX43 = -1./3. ; AX44 = 1./3. ;
* AY
AY11 = 1./3. ; AY12 = 1./6. ; AY13 = -1./6. ; AY14 = -1./3. ;
AY21 = 1./6. ; AY22 = 1./3. ; AY23 = -1./3. ; AY24 = -1./6. ;
AY31 = -1./6. ; AY32 = -1./3. ; AY33 = 1./3. ; AY34 = 1./6. ;
AY41 = -1./3. ; AY42 = -1./6. ; AY43 = 1./6. ; AY44 = 1./3. ;
AS11 = (0.5*AX11) + (2.0*AY11) ; AS12 = (0.5*AX12) + (2.0*AY12) ;
AS13 = (0.5*AX13) + (2.0*AY13) ; AS14 = (0.5*AX14) + (2.0*AY14) ;
AS21 = (0.5*AX21) + (2.0*AY21) ; AS22 = (0.5*AX22) + (2.0*AY22) ;
AS23 = (0.5*AX23) + (2.0*AY23) ; AS24 = (0.5*AX24) + (2.0*AY24) ;
AS31 = (0.5*AX31) + (2.0*AY31) ; AS32 = (0.5*AX32) + (2.0*AY32) ;
AS33 = (0.5*AX33) + (2.0*AY33) ; AS34 = (0.5*AX34) + (2.0*AY34) ;
AS41 = (0.5*AX41) + (2.0*AY41) ; AS42 = (0.5*AX42) + (2.0*AY42) ;
AS43 = (0.5*AX43) + (2.0*AY43) ; AS44 = (0.5*AX44) + (2.0*AY44) ;
LAS1 = 'PROG' AS11 AS12 AS13 AS14 ;
LAS2 = 'PROG' AS21 AS22 AS23 AS24 ;
LAS3 = 'PROG' AS31 AS32 AS33 AS34 ;
LAS4 = 'PROG' AS41 AS42 AS43 AS44 ;
P1 = 0.0 0.0 0.0 ;
P2 = 0.0 2.0 0.0 ;
P3 = 0.0 2.0 1.0 ;
P4 = 0.0 0.0 1.0 ;
MODT = 'MANU' 'QUA4' P1 P2 P3 P4 ;
$MODT = 'MODE' ('CHAN' MODT 'QUAF') 'NAVIER_STOKES' 'LINE' ;
TTT = 'EQEX' 'NITER' 1 'OMEGA' 1. 'ITMA' 0
      'OPTI' 'EF' 'IMPL'
      'ZONE' $MODT 'OPER' 'LAPN' 1.0 'INCO' 'TN' ;
TTT.'INCO' = 'TABLE' 'INCO' ;
TNS = 'KCHT' $MODT 'SCAL' 'SOMMET' 1.0 ;
TTT.'INCO'.'TN' = TNS ;
B1 MatA = 'LAPN' TTT.'1LAPN' ;
C1 = 'KOPS' MatA 'MULT' ('MANU' 'CHPO' P1 1 'TN' 1.0 'NATU' 'DISCRET');
C11 = 'EXTR' C1 'TN' P1 ;
C21 = 'EXTR' C1 'TN' P2 ;
C31 = 'EXTR' C1 'TN' P3 ;
C41 = 'EXTR' C1 'TN' P4 ;
C2 = 'KOPS' MatA 'MULT' ('MANU' 'CHPO' P2 1 'TN' 1.0 'NATU' 'DISCRET');
C12 = 'EXTR' C2 'TN' P1 ;
C22 = 'EXTR' C2 'TN' P2 ;
C32 = 'EXTR' C2 'TN' P3 ;
C42 = 'EXTR' C2 'TN' P4 ;
C3 = 'KOPS' MatA 'MULT' ('MANU' 'CHPO' P3 1 'TN' 1.0 'NATU' 'DISCRET');
C13 = 'EXTR' C3 'TN' P1 ;
C23 = 'EXTR' C3 'TN' P2 ;
C33 = 'EXTR' C3 'TN' P3 ;
C43 = 'EXTR' C3 'TN' P4 ;
C4 = 'KOPS' MatA 'MULT' ('MANU' 'CHPO' P4 1 'TN' 1.0 'NATU' 'DISCRET');
C14 = 'EXTR' C4 'TN' P1 ;
C24 = 'EXTR' C4 'TN' P2 ;
C34 = 'EXTR' C4 'TN' P3 ;
C44 = 'EXTR' C4 'TN' P4 ;
LBS1 = 'PROG' C11 C12 C13 C14 ;
LBS2 = 'PROG' C21 C22 C23 C24 ;
LBS3 = 'PROG' C31 C32 C33 C34 ;
LBS4 = 'PROG' C41 C42 C43 C44 ;
LERT = (LAS1 ET LAS2 ET LAS3 ET LAS4) - (LBS1 ET LBS2 ET LBS3 ET LBS4) ;
'MESS' 'Maximum erreur :' ('MAXI' LERT 'ABS') ;
'SI' (('MAXI' LERT 'ABS') > 1.E-14) ;
'MESS' 'Il y a des problèmes sur la matrice du laplacien' ;
'ERRE' 5 ;
'FINSI' ;
'FIN' ;
```

## topoptim_06 [(sans section)]
```
* fichier topoptim_06.dgibi
* Topology optimization of of a simple 2D structure subjected to a
* mechanical loading, with a symmetry restriction.
* Author:
* Guenhael Le Quilliec (LaMe - Polytech Tours)
* Version:
* V1.0 2017/04/18 Original version compatible with TOPOPTIM V2.1
graph0 = FAUX ;
* General options
OPTI 'DIME' 2 'MODE' 'PLAN' 'CONT' 'ELEM' QUA4 ;
* Mesh
nelx0 = 60 ;
nely0 = 20 ;
p0 = 0.0 0.0 ;
p1 = 0.0 20.0 ;
p2 = 60.0 0.0 ;
lgn0 = DROI nely0 p1 p0 ;
msh0 = TRAN lgn0 nelx0 p2 ;
p2 = msh0 POIN 'PROC' p2 ;
* Model and material
mod0 = MODE msh0 'MECANIQUE' 'ELASTIQUE' ;
mat0 = MATE mod0 'YOUN' 210.0e9 'NU' 0.3 ;
* Boundary conditions and loading
bc0 = (BLOQ 'UX' lgn0) ET (BLOQ 'UY' p2) ;
load0 = FORC (0.0 -1.0) p1 ;
* Finite element model table
mdl0 = TABL ;
mdl0.'MODELE' = mod0 ;
mdl0.'CARACTERISTIQUES' = mat0 ;
mdl0.'BLOCAGES_MECANIQUES' = bc0 ;
mdl0.'CHARGEMENT' = load0 ;
* Optimization table
tab0 = TABL ;
tab0.'RESOLUTION_LINEAIRE' = mdl0 ;
tab0.'FRACTION_VOLUME' = 0.5 ;
tab0.'RESTRICTIONS' = TABL ;
tab0.'RESTRICTIONS'.(1) = TABL ;
tab0.'RESTRICTIONS'.(1).'TYPE' = MOT 'SYME_DROI' ;
tab0.'RESTRICTIONS'.(1).'POIN1' = (p1 / 2.0) ;
tab0.'RESTRICTIONS'.(1).'POIN2' = (p1 / 2.0) PLUS p2 ;
tab0.'TRAC' = graph0 ;
* Optimization
TOPOPTIM tab0 ;
* Plot to screen
topo0 = tab0.'TOPOLOGIE'.(tab0.'CYCLE') ;
topomsh0 = tab0.'MAILLAGE'.(tab0.'CYCLE') ;
SI graph0 ;
    TRAC (REDU topo0 topomsh0) (REDU mod0 topomsh0)
         (PROG 0.0 'PAS' (1.0 / 56.0) 1.0) ;
FINS ;
FIN ;
```

## toposurf_02 [(sans section)]
```
* fichier toposurf_02.dgibi
* Extraction of the 3D smoothed surface from a simple 2D topology
* Author:
* Guenhael Le Quilliec (LaMe - Polytech Tours)
* Version:
* 3.0 2018/01/29 Updated to make it compatible with TOPOSURF V3.0
* 2.0 2018/01/26 Updated to make it compatible with TOPOSURF V2.0
* 1.0 2016/12/13 Original version compatible with TOPOSURF V1.0
* General options
OPTI 'DIME' 2 'MODE' 'PLAN' 'CONT' 'ELEM' QUA8 ;
graph0 = FAUX ;
* Mesh
p0 = 0.0 0.0 ;
p1 = 0.0 100.0 ;
p2 = 100.0 0.0 ;
lgn0 = DROI 50 p1 p0 ;
msh0 = TRAN lgn0 50 p2 ;
* Model
mod0 = MODE msh0 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' ;
* Topology (usualy obtained from procedure TOPOPTIM)
pnt0 = msh0 POIN 'SPHE' (50.0 50.0) (50.0 85.0) 10.0 ;
elm0 = msh0 ELEM 'APPU' pnt0 ;
topo0 = MANU 'CHML' mod0 'SCAL' 1.0 'TYPE' 'SCALAIRE' 'GRAVITE' ;
topo0 = ((topo0 * 0.0) REDU (DIFF msh0 elm0)) + (topo0 REDU elm0) ;
* Plot the topology to screen
SI graph0 ;
    TRAC topo0 mod0 ;
FINS ;
* Topology table
tab0 = TABL ;
tab0.'TOPOLOGIE' = topo0 ;
tab0.'MODELE' = mod0 ;
tab0.'TAUX_FILTRAGE' = 3 ;
* Generate a smoothed surface from the topology
srf0 = TOPOSURF tab0 ;
* Plot the smoothed surface to screen
SI graph0 ;
    TRAC srf0 'FACE' ;
FINS ;
* Save the smoothed surface in STL format
OPTI 'SORT' 'toposurf_02.stl' ;
SORT 'STL' srf0 ;
FIN ;
```

## traction316L [(sans section)]
```
* Essai de traction cyclique sur de l'acier 316L a 20 degC.
* Validation des donnees materiaux integrees dans la procedure BIBLIO.
* Reproduction de la courbe de traction presentee dans la reference,
* Fig. 2. (a).
* Description :
* Type de calcul : mecanique, plastique
* Mode de calcul : 3D
* Type d'element : CUB8
* Chargement : Deplacement impose
* Reference :
* O. Muransky, C.J. Hamelin, M.C. Smith, P.J. Bendeich, L. Edwards,
* "The effect of plasticity theory on predicted residual stress fields
* in numerical weld analyses",
* Computational Materials Science 54 (2012) 125–134.
opti dime 3 elem cub8 ;
* Pour affichages, mettre IG1 a VRAI :
ig1 = faux ;
* Pour calcul complet, mettre icomplet a vrai :
icomplet = faux ;
* opti trac psc eptr 5 ;
ig1 = ig1 ou (ega (vale trac) 'PSC') ;
* ------------------------------ Modele EF -----------------------------
* Temperature essai :
T0 = 20. ;
* Maillage cube unite :
L1 = (0 0 0) droi 1 (1 0 0) ;
S1 = L1 tran 1 (0 1 0) ;
V1 = S1 volu tran 1 (0 0 1) ;
si ig1 ;
  trac V1 titr 'Traction sur un cube unite' ;
fins ;
* Donnees 316L :
t316L = biblio '316L' refe 4 ;
* Modele et Caracteristiques :
mod1 = mode V1 mecanique elastique plastique chaboche2 ;
mat1 = mate mod1 'YOUN' t316L.'YOUN' 'NU' t316L.'NU' 'ALPH' t316L.'ALPH'
                    'R0' t316L.'R0' 'RM' t316L.'RM' 'B' t316L.'B'
                    'A1' t316L.'A1' 'C1' t316L.'C1' 'A2' t316L.'A2' 'C2' t316L.'C2'
                    'PSI' 1. 'OMEG' 0. 'TREF' T0 'TALP' T0 ;
* CL (blocages) :
Sx0 = (V1 coor 1) poin infe 1.e-3 ;
Sy0 = (V1 coor 2) poin infe 1.e-3 ;
S2 = V1 face 2 ;
CLUS1 = bloq S1 uz ;
CLUX0 = bloq Sx0 ux ;
CLUY0 = bloq Sy0 uy ;
CLUS2 = bloq S2 uz ;
cl0 = CLUS1 et CLUX0 et CLUY0 et CLUS2 ;
* Deplacement impose :
DCLS2 = depi CLUS2 1. ;
* Evolution temporelle :
epoint1 = 1.e-3 ;
emax1 = 0.015 ;
temax1 = emax1 / epoint1 ;
lamp1 = prog 0. 1. -1. 1. -1. 1. -1. 1. -1. 0. ;
ltps1 = prog 0. 1. 3. 5. 7. 9. 11. 13. 15. 16. ;
lamp1 = emax1 * lamp1 ;
ltps1 = temax1 * ltps1 ;
ev1 = evol manu temp ltps1 lamp1 ;
* Chargement mecanique :
cg1 = char dimp DCLS2 ev1 ;
* Chargement thermique :
cht1 = manu chpo V1 1 'T' T0 ;
cgt1 = char t cht1 ;
si ig1 ;
  dess ev1 titr 'Evolution temporelle du deplacement impose.' ;;
fins ;
* ------------------------- Resolution PASAPAS -------------------------
tpas1 = table ;
tpas1.modele = mod1 ;
tpas1.caracteristiques = mat1 ;
tpas1.chargement = cg1 et cgt1 ;
tpas1.blocages_mecaniques = cl0 ;
si icomplet ;
  tpas1.temps_calcules = ltps1 raff (0.05*temax1) ;
sino ;
  tpas1.temps_calcules = (ltps1 raff (0.05*temax1)) extr (lect 1 pas 1 10) ;
fins ;
list tpas1.temps_calcules ;
pasapas tpas1 ;
* ----------------------- Visualisation resultat -----------------------
* Courbe de traction a la temperature courante :
pz1 = S2 poin proc (0 0 1) ;
lu1 = prog 0. ;
lf1 = prog 0. ;
nb1 = (dime tpas1.temps) - 1 ;
repe b1 nb1 ;
  i1 = &b1 ;
  ui1 = (tpas1.deplacements.i1) extr 'UZ' pz1 ;
  fi1 = ((tpas1.reactions.i1) redu s2) resu ;
  fi1 = extr fi1 'FZ' ((extr fi1 mail) poin 1) ;
  lu1 = lu1 et ui1 ;
  lf1 = lf1 et fi1 ;
fin B1 ;
evfu1 = evol vert manu 'dL/L (%)' (100.*lu1) 'F/So (MPa)' (1.e-6*lf1) ;
si ig1 ;
  dess evfu1 gril point titr 'Courbe de traction cyclique 316L a 20. degC.' logo posy exce ;
fins ;
fin ;
```

## trac_anno [(sans section)]
```
OPTI 'DIME' 2 'ELEM' 'QUA4' ;
GRAPH = FAUX ;
* DESCRIPTION DES PARTIES D'UN MAILLAGE VIA UNE LEGENDE
LCLR = MOTS 'ROUG' 'BLEU' 'CYAN' 'INDI' 'JAUN' 'CARA' 'ROSE' 'ORAN' 'BOUT' 'VERT'
            'BRIQ' 'AZUR' 'VIOL' 'OR' 'CORA' 'BRUN' 'MARI' 'BLAN' 'NOIR' 'TURQ' ;
NCLR = DIME LCLR ;
MSH2 = (0. 0.) DROI 5 (5. 0.) TRAN 5 (0. 5.) ;
MSH1 = VIDE 'MAILLAGE'/'QUA4' ;
REPE K (NBEL MSH2) ;
    ELK = ELEM MSH2 &K ;
    CLR = EXTR LCLR ((@MOD (&K - 1) NCLR) + 1) ;
    MSH1 = MSH1 ET (COUL CLR ELK) ;
FIN K ;
ANN = VIDE 'ANNOTATI' ;
MSG = 'Je suis %' ;
REPE K NCLR ;
    CLR = EXTR LCLR &K ;
    ANN = ANN ET (ANNO 'CATE' CLR (REMP MSG '%' CLR)) ;
    SI ((&K EGA 3) OU (&K EGA 10) OU (&K EGA NCLR)) ;
        OPTI 'TRAC' 'PSC' 'FTRA' (CHAI 'cate_x' &K '.ps') ;
        TRAC MSH1 'FACE' ANN 'NCLK' ;
        SI GRAPH ;
            OPTI 'TRAC' 'X' ;
            TRAC MSH1 'FACE' ANN ;
            OPTI 'TRAC' 'OPEN' ;
            TRAC MSH1 'FACE' ANN ;
        FINS ;
    FINS ;
FIN K ;
LIST ANN ;
* AJOUT D'ETIQUETTES EN CERTAINS POINTS D'INTERET
DISTA = 0.3 ;
ANN_DEB = ANNO 'ETIQ' (0.5 0.5) DISTA 'SO' 'JE SUIS AU DEBUT' 'ROUG' ;
ANN_CP1 = ANNO 'ETIQ' (2.5 0.5) DISTA 'S' 'CHECKPOINT 1' ;
ANN_CP2 = ANNO 'ETIQ' (4.5 0.5) DISTA 'SE' 'CHECKPOINT 2' ;
ANN_CP3 = ANNO 'ETIQ' (0.5 2.5) DISTA 'O' 'CHECKPOINT 5' ;
ANN_CP4 = ANNO 'ETIQ' (2.5 2.5) DISTA 'C' 'CHECKPOINT 4' ;
ANN_CP5 = ANNO 'ETIQ' (4.5 2.5) DISTA 'E' 'CHECKPOINT 3' ;
ANN_CP6 = ANNO 'ETIQ' (0.5 4.5) DISTA 'NO' 'CHECKPOINT 6' ;
ANN_CP7 = ANNO 'ETIQ' (2.5 4.5) DISTA 'N' 'CHECKPOINT 7' ;
ANN_FIN = ANNO 'ETIQ' (4.5 4.5) DISTA 'NE' 'JE SUIS A LA FIN' 'VERT' ;
ANN2 = ANN_DEB ET ANN_CP1 ET ANN_CP2 ET ANN_CP3 ET ANN_CP4 ET
       ANN_CP5 ET ANN_CP6 ET ANN_CP7 ET ANN_FIN ;
BOIT1 = BOITE (MSH2 HOMO (BARY MSH2) 1.5) ;
* pour tester le menage
menage oblig;
OPTI 'TRAC' 'PSC' 'FTRA' 'etiq.ps' ;
TRAC MSH2 ANN2 'BOIT' BOIT1 ;
SI GRAPH ;
    OPTI 'TRAC' 'X' ;
    TRAC MSH2 ANN2 ;
    OPTI 'TRAC' 'OPEN' ;
    TRAC MSH2 ANN2 ;
FINS ;
LIST ANN2 ;
* REMPLACEMENT DES ISOVALEURS CONTINUES PAR UNE COLORMAP DISCRETE
CHPO1 = BRUI 'BLAN' 'UNIF' 0. 1. MSH1 ;
ANN3 = (ANNO 'CATE' 'BLEU' 'Froid') ET (ANNO 'CATE' 'ROUG' 'Chaud') ;
OPTI 'TRAC' 'PSC' 'FTRA' 'discr.ps' ;
TRAC MSH1 CHPO1 2 ANN3 ;
SI GRAPH ;
    OPTI 'TRAC' 'X' ;
    TRAC MSH1 CHPO1 2 ANN3 ;
    OPTI 'TRAC' 'OPEN' ;
    TRAC MSH1 CHPO1 2 ANN3 ;
FINS ;
FIN ;
```

## waam0 [(sans section)]
```
* fichier waam0.dgibi
* W A A M 0 . D G I B I
* Objet :
* Ce Dgibi a pour but de tester le fonctionnement des procedures :
* - SOUDAGE : definition d'une sequence de fabrication additive
* ou de soudage ;
* - WAAM : maillage d'une sequence de fabrication additive.
* Les affichages permettent de verifier les resultats.
* Trois sequences de fabrication "academiques" sont simulees :
* - le depot d'un mur rectiligne ;
* - la realisation d'un tube ;
* - la realisation d'une "forme libre".
opti dime 3 elem cub8 ;
* Pour activer les affichages, mettre IG1 a VRAI ;
ig1 = faux ;
* opti trac psc eptr 5 ;
* ---------------------- Sequences de fabrication ----------------------
* Parametres de fabrication :
debi1 = pi*0.6e-3*0.6e-3*10./60. ;
larg1 = 6.e-3 ;
* TAB1 : Table de fabrication du mur
tab1 = tabl ;
tab1.vitesse_de_soudage = 10.e-3 ;
tab1.vitesse_de_deplacement = 20.e-3 ;
tab1.puissance_de_soudage = 3.e3 ;
tab1.debit_de_fil = debi1 ;
* TAB2 : table de fabrication du tube
tab2 = tabl ;
tab2.vitesse_de_soudage = 10.e-3 ;
tab2.vitesse_de_deplacement = 20.e-3 ;
tab2.puissance_de_soudage = 3.e3 ;
tab2.debit_de_fil = debi1 ;
* TAB3 : table de fabrication de la forme libre
tab3 = tabl ;
tab3.vitesse_de_soudage = 10.e-3 ;
tab3.vitesse_de_deplacement = 20.e-3 ;
tab3.puissance_de_soudage = 3.e3 ;
tab3.debit_de_fil = debi1 ;
* Point de soudure initial :
soudage tab1 point 1. ;
soudage tab2 point 1. puis 6.e3 ;
soudage tab3 point 1. puis 6.e3 ;
* Repetition sequence de 2 passes en AR :
nb1 = 5 ;
repe b1 nb1 ;
* Vitesse + lente a la 1ere passe :
  si (&b1 ega 1) ;
    soudage tab1 passe droi (+100.e-3 0 0) vite 5.e-3 puis 4.e3 debi (0.5*debi1) ;
    lign1 = tab1.trajectoire ;
    p1 = (50.e-3 50.e-3 0) ;
    p2 = (0 50.e-3 0) ;
  sino ;
    soudage tab1 passe droi (+100.e-3 0 0) ;
  fins ;
  dh1 = debi1 / (tab1.vitesse_de_soudage) / larg1 ;
* 1er deplacement vertical :
  soudage tab1 depla droi (0 0 dh1) vite 16.e-3 ;
* Passe retour option MAIL (pour tester) :
  pc1 = tab1.trajectoire poin (nbno tab1.trajectoire) ;
  pl1 = lign1 poin 1 ;
  lign2 = lign1 plus (pc1 moin pl1) ;
  lign2 = lign2 syme point pc1 ;
  elim (pc1 et lign2) 1.e-6 ;
  soudage tab1 passe mail lign2 ;
* Passes du tube :
  si (&b1 ega 1) ;
    repe b2 4 ;
      soudage tab2 passe cerc p1 p2 10 vite 5.e-3 puis 5.e3 ;
      P1 p2 = p1 p2 tour (0 0 0) (0 0 1) 90. ;
    fin b2 ;
  sino ;
    repe b2 4 ;
      soudage tab2 passe cerc p1 p2 10 ;
      P1 p2 = p1 p2 tour (0 0 0) (0 0 1) 90. ;
    fin b2 ;
  fins ;
  dh2 = debi1 / (tab2.vitesse_de_soudage) / larg1 ;
* Dernier deplacement vertical si pas derniere sequence :
  si (&b1 neg nb1) ;
    soudage tab1 depla droi (0 0 dh1) ;
    soudage tab2 depla droi (0 0 dh2) ;
    soudage tab2 depla cerc p1 p2 1 ;
    P1 p2 = p1 p2 tour (0 0 0) (0 0 1) 90. ;
  fins ;
* Passes forme libre :
  soudage tab3 passe droi (0 -100.e-3 0) ;
  soudage tab3 passe cerc (20.e-3 -20.e-3 0.) (20.e-3 0. 0.) 10 ;
  soudage tab3 passe droi (+100.e-3 0 0) ;
  soudage tab3 passe cerc (20.e-3 +20.e-3 0.) (0. 20.e-3 0.) 10 ;
  soudage tab3 passe droi (0 +100.e-3 0) ;
  soudage tab3 passe droi (+120.e-3 -120.e-3 0) ;
  soudage tab3 depla droi (0 0 0) abso ;
  soudage tab3 depla droi (&b1*(0 0 dh1)) ;
fin b1 ;
soudage tab1 point 30. puis 0. ;
si ig1 ;
* Mur :
trac tab1.trajectoire titr 'trajectoire sequence mur' ;
dess tab1.evolution_deplacement titr 'deplacement sequence mur' ;
dess tab1.evolution_puissance titr 'puissance sequence mur' ;
dess tab1.evolution_debit titr 'debit sequence mur' ;
* Tube :
trac tab2.trajectoire titr 'trajectoire sequence tube' ;
dess tab2.evolution_deplacement titr 'deplacement sequence tube' ;
dess tab2.evolution_puissance titr 'puissance sequence tube' ;
dess tab2.evolution_debit titr 'debit sequence tube' ;
* Forme libre :
trac tab3.trajectoire titr 'trajectoire sequence UN' ;
dess tab3.evolution_deplacement titr 'deplacement sequence UN' ;
dess tab3.evolution_puissance titr 'puissance sequence UN' ;
dess tab3.evolution_debit titr 'debit sequence UN' ;
dess tab3.evolution_puissance titr 'puissance sequence UN' ;
fins ;
* ------------------------- Maillage avec WAAM -------------------------
* Mur :
tab21 = waam tab1 mail pas 5.e-3 larg larg1 dens 2.e-3 ;
elim tab21.maillage 1.e-5 ;
* Tube :
tab22 = waam tab2 mail pas 5.e-3 larg larg1 dens 2.e-3 ;
elim tab22.maillage 1.e-5 ;
* Forme libre :
tab32 = waam tab3 mail pas 5.e-3 larg larg1 dens 2.e-3 ;
elim tab32.maillage 1.e-5 ;
si ig1 ;
  trac cach tab21.maillage titr 'Maillage du mur' ;
  trac cach tab22.maillage titr 'Maillage du tube' ;
  trac cach tab32.maillage titr 'Maillage de la forme libre' ;
  waam tab21 visu cach (tab1.trajectoire) ;
  waam tab22 visu cach (tab2.trajectoire) ;
  waam tab32 visu cach (tab3.trajectoire) ;
fins ;
* ------------------ F I N W A A M 0 . D G I B I -----------------
fin ;
```

## phase_03 [Changement_De_Phase Changement_De_Phase]
```
graph= FAUX;
* Cas test : phase2d_02.dgibi
* Type : Verification & Validation analytique
* Barreau ayant un materiau constant et un changement de phase a 100°C
* Il est chauffe uniformement sur la surface S1
* Le test consiste a s'assurer que la chaleur injectee est bien egale
* a la chaleur specifique accumulee plus la chaleur de changement de
* phase
OPTI DIME 2 ELEM QUA4 TRAC 'PSC';
DT = 20. ;
P1 = (0. 0.) ;
P2 = P1 'PLUS' (0. 0.01) ;
L1 = 'DROI' 1 P1 P2 ;
L2 = L1 'PLUS' (0.1 0.) ;
L3 = L2 'PLUS' (0.1 0.) ;
P3 = POIN 1 L3 ;
NBEX = 10 ;
S1 = L1 'REGL' NBEX L2 ;
S2 = L2 'REGL' NBEX L3 ;
STOT = S1 'ET' S2 ;
rho1 = 1000. ;
C1 = 4180. ;
K1 = 100. ;
QL1 = rho1*2257000. ;
MOD1 = MODE STOT 'THERMIQUE';
MOD2 = MODE STOT 'CHANGEMENT_PHASE' 'PARFAIT' 'INCO' 'T' 'Q';
MAT1 = MATE MOD1 'RHO' rho1 'C' C1 'K' K1 ;
MAT2 = MATE MOD2 'DUAL' QL1 'PRIM' 100. ;
Tps_fin = 5000.D0 ;
Qsour = 1D6 ;
CHA1 = CHAR 'Q' ('SOUR' MOD1 Qsour S1) (EVOL 'MANU' 'TEMP' (PROG 0. Tps_fin) 'AMPL' (PROG 1. 1.));
TAB1 = 'TABL';
TAB1.'TEMPS_CALCULES' ='PROG' 0. 'PAS' 10. (Tps_fin / 2.D0) 'PAS' 150. Tps_fin ;
TAB1.'MODELE' = MOD1 ET MOD2 ;
TAB1.'CARACTERISTIQUES' = MAT1 ET MAT2 ;
TAB1.'CHARGEMENT' = CHA1 ;
TAB1.'PRECISION' = 1.D-8 ;
PASAPAS TAB1;
EVTP0 = EVOL 'ROUG' 'TEMP' TAB1 'TEMPERATURES' 'T' P1 ;
SI GRAPH ;
  DESS EVTP0 'XBOR' 0. Tps_fin 'YBOR' 0. 200. ;
FINS;
LIG_PROI = DROI 1000 P1 P3;
DIM1 = DIME TAB1.'TEMPS' ;
REPE SURI DIM1 ;
  ii = &SURI;
  PROPi = TAB1.'PROPORTIONS_PHASE'. (ii - 1) ;
  PROIi = PROI LIG_PROI PROPi;
  EVOLi = EVOL 'CHPO' PROIi 'PPHA' LIG_PROI;
FIN SURI;
SI GRAPH ;
 'TRAC' PROPi MOD2 ;
 'DESS' EVOLi;
'FINS';
* Bilan de chaleur
  T_0 ='CHAN' 'CHAM' ('EXCO' TAB1.'TEMPERATURES'. 0 'T' ) MOD2 'STRESSES' 'CARACTERISTIQUES' ;
  T_0 ='NOMC' T_0 'SCAL';
  T_1 ='CHAN' 'CHAM' ('EXCO' TAB1.'TEMPERATURES'.(DIM1 - 1) 'T' ) MOD2 'STRESSES' 'CARACTERISTIQUES' ;
  T_1 ='NOMC' T_1 'SCAL';
  ENE1='INTG' (rho1* C1 * (T_1 - T_0)) MOD2 ;
* Chaleur Latente consommee
  Prop0='CHAN' 'STRESSES' TAB1.'PROPORTIONS_PHASE'. 0 MOD2 'CARACTERISTIQUES' ;
  Prop0='NOMC' Prop0 'SCAL' ;
  Prop1='CHAN' 'STRESSES' TAB1.'PROPORTIONS_PHASE'.(DIM1 - 1) MOD2 'CARACTERISTIQUES' ;
  Prop1='NOMC' Prop1 'SCAL' ;
  ENE2 ='INTG' (QL1 * (Prop1 - Prop0)) MOD2 ;
  Pfin = ENE2/('INTG' (QL1 * (Prop1 ** 0)) MOD2) * 100. ;
* Integration temporelle
  ENE3 =('MAXI' ('RESU' ('TIRE' CHA1 0.D0))) * (Tps_fin - 0.D0) ;
 'OPTI' ECHO 0;
 'MESS' 'Energie calorifique reguliere :' ENE1 ;
 'MESS' 'Energie de chaleur latente    :' ENE2 '|' Pfin '%' ;
 'MESS' 'Energie totale                :'(ENE1+ENE2) ;
 'MESS' 'Energie injectee              :' ENE3 ;
  ERR_ABS ='ABS' (ENE3 - ENE1 - ENE2) ;
  ERR_REL = ERR_ABS / ENE3 * 100. ;
 'MESS' 'Erreur de bilan               :' ERR_ABS '|' ERR_REL '%' ;
 'OPTI' ECHO 1 ;
FIN;
```

## solubilite_01 [Changement_De_Phase Changement_De_Phase]
```
* Cas test : solubilite_01.dgibi
* Categorie : Verification
* Description :
* Teste le MODELE 'CHANGEMENT_PHASE' 'SOLUBILITE' developpe en 2021
* Plaque 2D constituee de 2 SOUS-ZONES 'TRI3' et 'QUA4'
* Le point P1 est soumis à un chargement oscillant sur les
* quantites duales 'QL' et 'QGA'.
* La quantite primale 'CL' a une limite de solubilite Sol1
* Les quantites primales 'CL' et 'CG' diffusent en plus dans
* le domaine avec un modele de DIFFUSION de FICK
* Validation : (Aucune actuellement)
* Tests a developper (Conservation des especes), solution analytique,
* etc.
'OPTI' 'TRAC' 'PSC';
'OPTI' 'DIME' 2 'ELEM' 'QUA4' 'MODE' 'PLAN' ;
* Solubilite
 Sol1 = 0.5 ;
 SrcQL = 2.E-5 ;
 SrcQG = 1.E-5 ;
* Geometrie
 P1 = 0. 0. ;
 P2 = 5.e-3 0. ;
 P3 = 5.e-3 10.e-3 ;
 P4 = 0. 10.e-3 ;
 n = 20 ;
 L23 = P2 'DROI' n P3 ;
 L41 = P4 'DROI' n P1 ;
 L14 ='INVE' L41 ;
 PA ='POIN' L41 'PROC' (0. 2.5e-3) ;
 n = 10 ;
 MQUA4 = ('INVE' L41) 'REGL' n L23 ;
 MTRI3 ='CHAN' 'TRI3' (L23 'REGL' n (L23 'PLUS' P2));
 su1 = MQUA4 'ET' MTRI3;
* Modeles et caracteristiques
 moddi1 ='MODE' su1 'DIFFUSION' 'FICK' 'INCO' 'CL' 'QL' 'CONS' 'CON1' ;
 moddi2 ='MODE' su1 'DIFFUSION' 'FICK' 'INCO' 'CG' 'QGA' 'CONS' 'CON2' ;
 modph1 ='MODE' su1 'CHANGEMENT_PHASE' 'SOLUBILITE' 'INCO' 'CL' 'CG' 'QL' 'QGA' 'CONS' 'SOL1' ;
 modtot = moddi1 'ET' moddi2 'ET' modph1 ;
 matdi1 ='MATE' moddi1 'K' 1.D-5 'CDIF' 5.D-2 ;
 matdi2 ='MATE' moddi2 'K' 2.D-5 'CDIF' 1.D-1 ;
 matph1 ='MATE' modph1 'SOLU' Sol1 ;
 mattot = matdi1 'ET' matdi2 'ET' matph1 ;
* CHARGEMENT
 srcdi1 ='MANU' 'CHPO' ('MANU' 'POI1' P1) 1 'QL' SrcQL ;
 srcdi2 ='MANU' 'CHPO' ('MANU' 'POI1' P1) 1 'QGA' SrcQG ;
 ltps1 ='PROG' 0. 'PAS' 0.1 10. ;
 lqL = 5.D-2 * ('SIN' (ltps1*360./4.)) ;
 lqG =-1.5D-2 * (3.D0 * ('SIN' (ltps1*360./3.))) * (1. + (ltps1 / 50.) ) ;
 Evdi1 ='EVOL' 'BLEU' 'MANU' 'TEMP' ltps1 'QL' lqL ;
 Evdi2 ='EVOL' 'ROUG' 'MANU' 'TEMP' ltps1 'QGA' lqG ;
 chardi1 ='CHAR' 'QL' srcdi1 Evdi1 ;
 chardi2 ='CHAR' 'QGA' srcdi2 Evdi2 ;
 chartot = chardi1 'ET' chardi2 ;
* PASAPAS
 listT ='PROG' 0. 'PAS' 0.2 10. ;
 xtab ='TABL' ;
 xtab.'MODELE' = modtot ;
 xtab.'CARACTERISTIQUES' = mattot ;
 xtab.'CHARGEMENT' = chartot ;
 xtab.'CONCENTRATIONS' ='TABL' ;
 xtab.'CONCENTRATIONS'. 0 ='MANU' 'CHPO' su1 2 'CL' 0.25 'CG' 0.D0 'NATURE' 'DIFFUS' ;
 xtab.'TEMPS_CALCULES' = listT ;
 xtab.'PRECISION' = 1.D-6 ;
 xtab.'CTOL' ='MANU' 'CHPO' su1 2 'CL' 1.D-6 'CG' 1.D-6 ;
 xtab.'PROCESSEURS' ='MONOPROCESSEUR' ;
 PASAPAS xtab ;
* POST-TRAITEMENT
* Chargement en P1
 TLEG ='TABL';
 TLEG.'TITRE' ='TABL';
 TLEG.'TITRE'. 1='CHAI' 'Liquide';
 TLEG.'TITRE'. 2='CHAI' 'Gaz' ;
 Tit1 ='CHAI' 'Chargement sur le point P1';
'DESS' (Evdi1 'ET' Evdi2) 'GRIL' 'TITR' Tit1 'LEGE' TLEG ;
* Evolution des concentrations en P1
 EVO_L ='EVOL' 'BLEU' 'TEMP' xtab 'CONCENTRATIONS' 'CL' P1 ;
 EVO_G ='EVOL' 'ROUG' 'TEMP' xtab 'CONCENTRATIONS' 'CG' P1 ;
 EVO_Som ='COUL' (EVO_L + EVO_G) 'VERT' ;
 Tit1 ='CHAI' 'Concentrations CL et CG';
'DESS' (EVO_L 'ET' EVO_G) 'GRIL' 'TITR' Tit1 'LEGE' TLEG ;
 Tit1 ='CHAI' 'Cumul des concentrations CL et CG';
'DESS' EVO_Som 'GRIL' 'TITR' Tit1 ;
* Evolution des reactions sur les blocages du modele de 'SOLUBILITE' en P1
 BLOSOL='PMAT' modph1 ;
 Ltps1 ='TABL' 'ESCLAVE' ;
 LREAL ='TABL' 'ESCLAVE' ;
 LREAG ='TABL' 'ESCLAVE' ;
'REPE' SURi ('DIME' xtab.'TEMPS') ;
   Tpsi = xtab.'TEMPS'. (&SURi - 1) ;
   Ci = xtab.'CONCENTRATIONS'. (&SURi - 1) ;
   REAi ='REDU' ('REAC' Ci BLOSOL) P1 ;
   Ltps1. &SURi = Tpsi ;
  'SI' ('EXIS' REAi 'QL');
     LREAL. &SURi ='MAXI' ('EXCO' REAi 'QL' );
  'SINO';
     LREAL. &SURi = 0.D0;
  'FINS';
  'SI' ('EXIS' REAi 'QGA');
     LREAG. &SURi ='MAXI' ('EXCO' REAi 'QGA' );
  'SINO';
     LREAG. &SURi = 0.D0;
  'FINS';
'FIN' SURi ;
 Ltps1 ='ETG' Ltps1 ;
 LREAL ='ETG' LREAL ;
 LREAG ='ETG' LREAG ;
 EVO_RL ='EVOL' 'BLEU' 'MANU' 'TEMP' Ltps1 'Reac_L' LREAL ;
 EVO_RG ='EVOL' 'ROUG' 'MANU' 'TEMP' Ltps1 'Reac_G' LREAG ;
 Tit1 ='CHAI' 'Reactions sur les blocages CL et CG';
'DESS' (EVO_RL 'ET' EVO_RG) 'GRIL' 'TITR' Tit1 'LEGE' TLEG ;
'REPE' SURi ('DIME' xtab.'TEMPS') ;
   Ci ='EXCO' xtab.'CONCENTRATIONS'. (&SURi - 1) 'CL';
   Tpsi = xtab.'TEMPS'. (&SURi - 1) ;
   Titi ='CHAI' 'Concentration ''CL'' au temps :' Tpsi ;
  'TRAC' Ci su1 'TITR' Titi ;
'FIN' SURi ;
'REPE' SURi ('DIME' xtab.'TEMPS') ;
   Ci ='EXCO' xtab.'CONCENTRATIONS'. (&SURi - 1) 'CG';
   Tpsi = xtab.'TEMPS'. (&SURi - 1) ;
   Titi ='CHAI' 'Concentration ''CG'' au temps :' Tpsi ;
  'TRAC' Ci su1 'TITR' Titi ;
'FIN' SURi ;
FIN ;
```

## flamcrebcom [Chimie Combustion]
```
* OPERATEUR FLAM
* Critere CREBCOM
* A. BECCANTINI DEN/DM2S/SFME/LTMF JUIN 2001
 'OPTION' 'DIME' 2 ;
 'OPTION' 'ELEM' QUA4 ;
 'OPTION' 'TRAC' 'X' ;
 'OPTION' 'ECHO' 0 ;
 GRAPH = FAUX ;
 LIG1 = (0.0 0.0) 'DROIT' 10 (0.0 1.0) ;
 DOM1 = 'TRANSLATION' LIG1 10 (1.0 0.0) ;
 DOM2 = 'TRANSLATION' LIG1 10 (-1.0 0.0) ;
 DOMTOT = DOM1 'ET' DOM2 ;
 $DOMTOT = 'MODE' DOMTOT 'EULER' ;
 $DOM1 = 'MODE' DOM1 'EULER' ;
 $DOM2 = 'MODE' DOM2 'EULER' ;
 TDOMTOT = 'DOMA' $DOMTOT 'VF' ;
 TDOM1 = 'DOMA' $DOM1 'VF' ;
 TDOM2 = 'DOMA' $DOM2 'VF' ;
 MDOMTOT = TDOMTOT . 'QUAF';
 MDOM1 = TDOM1 . 'QUAF';
 MDOM2 = TDOM2 . 'QUAF';
'ELIM' (MDOMTOT 'ET' MDOM1 'ET' MDOM2) 1D-5;
 EPSILON = 1.0D-2 ;
 CSIMAX = 9.0D-1 ;
* CSIMAX: maximum value of CSI
* CSIN = CSIMAX if x < 0
* 0.0 x => 0
 CSIN = ('MANUEL' 'CHPO' ('DOMA' $DOM2 'CENTRE') 1 'H2O2'
         (1.0001 '*' CSIMAX) 'NATURE' 'DISCRET')
        'ET'
        ('MANUEL' 'CHPO' ('DOMA' $DOM1 'CENTRE') 1 'H2O2' 0.0
         'NATURE' 'DISCRET') ;
 MOD1 = 'MODELISER' ('DOMA' $DOMTOT 'MAILLAGE') 'THERMIQUE' ;
 'SI' GRAPH ;
    CHM_CSI = 'KCHA' $DOMTOT 'CHAM' CSIN ;
    'TRAC' CHM_CSI MOD1 'TITR' ('CHAINE' 'csi');
 'FINSI' ;
 CHP1 = 'FLAM' 'CREBCOM' $DOMTOT EPSILON CSIMAX CSIN ;
* CHP1 = 1.0 in x = 0.05
* 0 ailleurs
 'SI' GRAPH ;
    CHM_C1 = 'KCHA' $DOMTOT 'CHAM' CHP1 ;
    'TRAC' CHM_C1 MOD1 'TITR' ('CHAINE' 'C1');
 'FINSI' ;
 GEO1 = ('COORDONNEE' 1 ('DOMA' $DOMTOT 'CENTRE')) 'POIN' 'COMPRIS'
   0.049 0.051 ;
 CHPTEST = 'MANUEL' 'CHPO' GEO1 1 'SCAL' 1.0 ;
 ERRO = 'MAXIMUM' (CHP1 '-' CHPTEST) 'ABS' ;
 'SI' (ERRO > 1.0D-6) ;
     'ERREUR' 5 ;
 'FINSI' ;
 'FIN' ;
```

## deto [Chimie Melange]
```
* Validation de l'opérateur DETO : Comparaison de la pression, de la
* température et de la vitesse de Chapman-Jouguet pour deux mélanges
* H2/O2/N2 entre des données expérimentales, un calcul de référence
* et l'opérateur DETO.
* On crée un CHAMPOINT contenant les conditions suivantes
* Pression et température du mélange 1.atm et 291.K
* Nombre de moles des différents constituants
* Point P1 H2=2. O2=1. N2=3. H2O=0.
* Point P2 H2=2. O2=1. N2=5. H2O=0.
* Valeurs de référence à 291K ET 1atm
* Vcj(m/s)
* PCJ(atm) TCJ(K) Calculée et mesurée
* Point P1 15.63 3003 2033. 2055.
* Point P2 14.39 2685 1850. 1822.
* Référence : Combustion, flames and explosion of gases,
* B.Lewis and G.von Elbe, page 545, Academic Press ed.
* Les différences observées entre le résultat du calcul DETO et le
* résultat du calcul de référence s'expliquent essentiellement par
* le fait que DETO utilise une cinétique chimique à une seule réation.
* - Initialisations
OPTI DIME 2 ELEM QUA4 ECHO 0 ;
P1 = 0. 0. ;
P2 = 2. 0. ;
P1P2 = P1 'DROI' 1 P2 ;
X Y = 'COOR' P1P2 ;
CHP3 = 'MANU' 'CHPO' P1P2 1 'H2' 2. ;
CHP1 = 'MANU' 'CHPO' P1P2 1 'O2' 1. ;
CHP4 = 'MANU' 'CHPO' P1P2 1 'H2O' 0. ;
CHP2 = 'EXCO' 'SCAL' (x + 3.) 'N2' ;
CHP5 = 'MANU' 'CHPO' P1P2 1 'P' 101325. ;
CHP6 = 'MANU' 'CHPO' P1P2 1 'T' 291. ;
* - Calcul
CHPTOT = CHP1 + CHP2 + CHP3 + CHP4 + CHP5 + CHP6 ;
CHPR1 CHPR2 CHPR3 = 'DETO' CHPTOT ;
* - Récupération des valeurs pour comparaison
P01 = ('EXTR' CHPR1 'PCJ' P1) / 101325.;
T1 = 'EXTR' CHPR1 'TCJ' P1 ;
V1 = 'EXTR' CHPR1 'VCJ' P1 ;
P02 = ('EXTR' CHPR1 'PCJ' P2) / 101325. ;
T2 = 'EXTR' CHPR1 'TCJ' P2 ;
V2 = 'EXTR' CHPR1 'VCJ' P2 ;
* - Affichage
P1ref = 15.63 ; T1ref = 3003. ; V1cref = 2033. ; V1mref = 2055. ;
P2ref = 14.39 ; T2ref = 2685. ; V2cref = 1850. ; V2mref = 1822. ;
F1 = '(F6.2)' ; F2 = '(F5.0)' ;
'MESS' '  ' ;
CH1 = 'CHAI' 'FORMAT' F1 'Ref. Pt1 P=' P1ref
             'FORMAT' F2 ' T=' T1ref ' V=' V1cref ' , ' V1mref ;
'MESS' CH1 ;
CH1 = 'CHAI' 'FORMAT' F1 'DETO Pt1 P=' P01
             'FORMAT' F2 ' T=' T1 ' V=' V1 ;
'MESS' CH1 ;
'MESS' '  ' ;
CH1 = 'CHAI' 'FORMAT' F1 'Ref. Pt2 P=' P2ref
             'FORMAT' F2 ' T=' T2ref ' V=' V2cref ' , ' V2mref ;
'MESS' CH1 ;
CH1 = 'CHAI' 'FORMAT' F1 'DETO Pt2 P=' P02
             'FORMAT' F2 ' T=' T2 ' V=' V2 ;
'MESS' CH1 ;
'MESS' '  ' ;
* - Test de bon fonctionnement : Erreur relative sur la Pcj
EPS1 = 0.05 ;
TEST1 = ((P01 - P1ref) / P1ref 'ABS') '<' EPS1 ;
TEST2 = ((P02 - P2ref) / P2ref 'ABS') '<' EPS1 ;
'SI' (TEST1 'ET' TEST2) ;
    'ERRE' 0 ;
'SINO' ;
    'ERRE' 5 ;
'FINS' ;
'FIN' ;
```

## adve_05 [Diffusion Advection]
```
* Cas-test de l'operateur ADVEction dans la formulation DIFFUSION
* Ce cas-test verifie que le produit de la rigidite d'advection avec un
* champ de concentration : v.gradC est egal a la solution attendue
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
mo1 = 'MODE' S1 diffusion advection ;
ma1 = 'MATE' mo1 'VITX' 0.22 'VITY' 1.0 ;
chC1 = (s1 'COOR' 1) + (S1 'COOR' 2) 'NOMC' 'CO' ;
KA1 = 'ADVE' mo1 ma1 ;
chq1 = ka1 * chC1 ;
chqref = 'MANU' 'CHPO' s1 1 'QCO' 0.305 'NATURE' 'DISCRET' ;
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

## diffusion_sous_contraintes_01 [Diffusion Fick]
```
* CAS TEST diffusion_sous_contraintes_01.dgibi
* NOTA : Ce cas-test ne valide aucun resultat analytique
* Il permet d'enrichir la base des cas-tests pour les utilisateurs
* Il incombe aux utilisateurs de valider et qualifier leur
* domaine de simulation.
* DESCRIPTION :
* Ce cas-test simule la diffusion d'une espece chimique dans un gradient
* de potentiel elastique (calcul mecanique couple a la diffusion)
* La piece est une eprouvette entaillee afin de generer un fort champ
* de contrainte en pointe d'entaille.
* - 2D PLAN
* - ELEMENTS FINIS TESTES : 'QUA4'
* - Regime transitoire pour la diffusion
* - Utilisation de la procedure CHARTHER pour appliquer le flux du au
* gradient de potentiel elastique
* - Utilisation de l'operateur SORET pour calculer le flux lui-meme
* - Convergence DIFFUSION-MECANIQUE activee car la diffusion est
* influencee par la mecanique.
'OPTI' 'DIME' 2 'ELEM' 'QUA4';
'OPTI' 'DEBU' 1;
'OPTI' 'TRAC' 'PSC';
'DEBP' CHARTHER PRECED TPS1;
* Dans la procedure CHARTHER (appel dans TRANSNON a chaque iterations)
* permet d'ajouter une flux de diffusion du a un gradient d'energie
* potetielle elastique dans le materiau
* - Le flux vaut JH=-CH.KD.grad(EPS(elas):SIG)
* - Le flux nodal integre QH est renvoye comme second membre dans
* l'indice 'ADDI_SECOND'
  SIG = PRECED.'ESTIMATION'.'CONTRAINTES';
  EPS ='ELAS' MOD1 SIG MAT1;
  ENECHM ='ENER' MOD1 EPS SIG ;
  ENE ='CHAN' 'CHPO' MOD1 ENECHM ;
* Pour les besoins de SORE, on met 'T' comme nom de composante
  ENE ='NOMC' 'T' ENE;
  CH ='EXCO' TH_COUR 'CH' 'CH';
  RIGDM ='SORE' MOD2 MATLOC COEF ENE ;
  TAA='TABL';
  TAA.'ADDI_SECOND'=RIGDM * CH;
'FINP' TAA ;
* MAILLAGE
 LX = 1. ;
 LY = 1. ;
 A0 = 0.2;
 NBEX = 50;
 NBEY = 50;
 NBA0 ='ENTI' 'SUPE' (NBEY*A0/LY) ;
 P1 = 0. 0. ;
 P2 = P1 'PLUS' (LX 0.);
 P3 = P2 'PLUS' (0. A0);
 P4 = P3 'PLUS' (0. (LY-A0));
 P5 = P1 'PLUS' (0. LY);
 P6 = P1 'PLUS' (0. A0);
 L1 ='DROI' P1 NBEX P2;
 L2 ='DROI' P6 NBEX P3;
 L3 ='DROI' P5 NBEX P4;
 S1 ='REGL' L1 NBA0 L2 'COUL' BLEU;
 S2 ='REGL' L2 (NBEY - NBA0) L3 'COUL' VERT;
 PIECE=S1 'ET' S2 ;
 LSUP= 'COTE' 2 S2 'COUL' 'JAUN' ;
 LDRO=('COTE' 2 S1) 'ET' LSUP 'COUL' 'CYAN' ;
 LGAU=('COTE' 4 S1) 'ET' ('COTE' 4 S2) 'COUL' 'TURQ' ;
* TRAC 'QUAL' (S1 ET S2 ET LSUP ET LGAU);
* MODELE & MATERIAU
 MOD1 ='MODE' PIECE 'MECANIQUE' 'ELASTIQUE' 'CONS' 'MEC1';
 MOD2 ='MODE' PIECE 'DIFFUSION' 'INCO' 'CH' 'QH' 'CONS' 'DIF1';
 MODTOT= MOD1 'ET' MOD2;
 MAT1 ='MATE' MOD1 'YOUN' 90.E9 'NU' 0.3 ;
 MAT2 ='MATE' MOD2 'KD' 5.D-3 'CDIF' 1. ;
 MATTOT= MAT1 'ET' MAT2 ;
* Pour une utilisation dans CHARTHER avec SORET
 DM = 2.D-13 ;
 MATLOC='MATE' MOD2 'KD' DM ;
 COEF ='MANU' 'CHML' MOD2 'SCAL' 1.D0 ;
* BLOCAGES
 BLO1 ='BLOQ' 'UX' LGAU ;
 BLO2 ='BLOQ' 'UY' LGAU ;
 BLO3 ='BLOQ' 'UX' LSUP ;
 BLOTOT= BLO1 'ET' BLO2 'ET' BLO3;
* CHARGEMENT
 DEPI1='DEPI' BLO1 (-1*LX/10);
 EVO1 ='EVOL' 'MANU' 'TEMP' ('PROG' 0. 0.5 1.) 'AMPL' ('PROG' 0. 1. 1.);
 CHADEP1='CHAR' 'DIMP' DEPI1 EVO1;
 CHATOT = CHADEP1;
* CONDITIONS INITIALES
 CHPCH0 ='MANU' 'CHPO' PIECE 1 'CH' 1. 'NATU' 'DIFFUS';
 LTPS1 ='PROG' 0. 'PAS' 0.05 1. ;
* PASAPAS
 TA1='TABL';
 TA1.MODELE = MODTOT ;
 TA1.CARACTERISTIQUES = MATTOT ;
 TA1.BLOCAGES_MECANIQUES= BLOTOT ;
 TA1.CHARGEMENT = CHATOT ;
 TA1.TEMPS_CALCULES = LTPS1 ;
 TA1.PROCEDURE_CHARTHER = VRAI ;
 TA1.CONVERGENCE_MEC_THE= VRAI ;
 TA1.CONCENTRATIONS ='TABL' ;
 TA1.CONCENTRATIONS. 0 = CHPCH0 ;
 PASAPAS TA1 ;
 DIM1 ='DIME' TA1.'TEMPS' - 1;
'TRAC' ('LOG' TA1.CONCENTRATIONS. DIM1) PIECE ;
 EVO1 ='EVOL' 'BLEU' 'TEMP' TA1 'CONCENTRATIONS' P3;
'DESS' EVO1;
'FIN';
```

## soret_1 [Diffusion Soret]
```
* CAS TEST soret_1.dgibi
* test effet Soret sur un disque plan avec trou central
* en modéle axisymetrique
* le potentiel agissant sur la concentration donne un gradient
* radial constant
* Concentration fixées sur les bords interne et externe
  GRAPH = 'N' ;
  'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
  'OPTION' 'MODE' 'AXIS' ;
  nbb = 100 ;l = 100. ;
  rint = 100. ;rext = rint + l ;
* ---- solution analytique calculée a partir d'une integrale-------
* -----donnée par MATLAB pour pour v = .5 ----------------------
* - pour ri = 100. re= 200. diffusivité du materiau 1.2
* --------- concentrations interne 20. externe 100. ---------------
l1 = 'PROG'0. 'PAS' 1. 11. 15. 20. 'PAS' 10. 100. ;
l2 = 'PROG'20. 80.15 119.15 144.21 160.09 169.94 175.83 179.11
 180.68 181.14 180.88 180.15 175.19 168.03 154.89 143.63 133.89
 125.39 117.27 111.27 105.35 100. ;
 evana = 'EVOL' 'MANU' 'ABSC' l1 'ORDO' l2 ;
* ------ on definit un maillage au pas de l1----------------------
  p1 = rint 0 ; p2 = rext 0. ; p3 = rint 1.;
  pp1 = 111. 0. ; pp2 = 115. 0 ; pp3 = 120. 0. ;
  nr = 1 ;
  su1 = ('DROI' 1 p3 p1 ) 'TRAN' (11 * nr) (pp1 'MOINS' p1 )
                   'TRAN' nr (pp2 'MOINS' pp1)
                   'TRAN' nr (pp3 'MOINS' pp2)
                   'TRAN' (8 * nr) (p2 'MOINS' pp3) ;
  'TITRE' ' traitement axi ' ;
  'SI' ('NEG' GRAPH 'N') ;
  'TRAC' su1 ;
  'FINSI' ;
  v = .5 ;
  lig1 = su1 'COTE' 2 ;
  cext = su1 'COTE' 3 ;
  cint = su1 'COTE' 1 ;
  kdif = 1.2 ;
  r = coor 1 su1 ;
* Cacul du potentiel T donnant T,R = v constante
  TT = CHAN 'COMP' 'T' ( r * v ) 'NATU' 'DIFFUS';
  kv = manu chpo su1 1 SCAL (1./kdif ) ;
  mod1 = su1 'MODE' 'THERMIQUE' 'ISOTROPE' ;
  mat1 = 'MATE' mod1 'K' kdif ;
* ------------- matrice de diffusion normale -------------------------
  rig1 = 'CONDUC' mod1 mat1 ;
* --------------matrice effet Soret -----------------------------------
  kvv = chan cham kv mod1 'RIGIDITE' ;
* rig2 = 'SORE' mod1 mat1 TT ;
  rig2 = sore mod1 mat1 kvv TT ;
  clime= 'BLOQUER' 'T' cext ;
  clims= 'BLOQUER' 'T' cint ;
  ff = ('DEPIMP' clime 100. ) 'ET' ( 'DEPIMP' clims 20.);
  sol1 = 'RESO' ( rig1 et rig2 et clime et clims) ff ;
  'TITR' 'Comparaison solution analytique / F.E. ' ;
  ev3 = 'EVOL' roug 'CHPO' sol1 'T' lig1 ;
  r1 = sol1 clime 'REAC' 'RESU' 'MAXI' ;
  r2 = sol1 clims 'REAC' 'RESU' 'MAXI' ;
   tabu = table ;
  tabu.1= 'MARQ CROI ' ;
  tabu.2= 'MARQ TRIA ' ;
   tabu.'TITRE' = table ;
  tabu.'TITRE'. 1 = MOT 'ANALYTIQUE' ;
  tabu.'TITRE'. 2 = MOT 'AXISYMETRIQUE' ;
  'SI' ('NEG' GRAPH 'N' ) ;
  'DESS' ( evana et ev3 ) lege tabu xbor 0. 100. ;
  finsi ;
* ----------------calcul de l'erreur ---------------------------------
 l3 = 'EXTR' ev3 'ORDO' ;
    si (( dime l2 ) neg (dime (ev3 extr absc ))) ;
 l3 = ipol (extr evana absc ) (ev3 extr absc ) ( ev3 extr ordo ) ;
    finsi ;
    delta = (l3 - l2) ;
 eeee = 'ABS' (delta / l2 ) ;
 'TITR' 'Erreur absolue ' ;
 ever1 = 'EVOL' 'MANU' 'ABSC' l1 'ORDO' delta ;
 'TITR' 'Erreur relative ' ;
 ever2 = 'EVOL' 'MANU' 'ABSC' l1 'ORDO' eeee ;
 ermax = 'MAXI' eeee ;
  'SI' ('NEG' GRAPH 'N' ) ;
  'DESS' ever1 'XBOR' 0. 100. ;
  'DESS' ever2 'XBOR' 0. 100. ;
  finsi ;
 'MESS' ' FLUX  en ENTREE  ' R2 ;
 'MESS' ' FLUX  en SORTIE  ' R1 ;
'SI' (ermax > 1.e-2 ) ;
   'ERRE' 5 ;
'FINS' ;
'FIN' ;
```

## lire_CSV_espaces [Entree-Sortie]
```
* TEST DE LECTURE DE FICHIERS CSV AVEC COMME SEPARATEUR ' '
* ON A MIS EXPRES DES ' ' SUPPLEMENTAIRES EN DEBUT ET FIN DE CERTAINES
* LIGNES AINSI QU'ENTRE CERTAINES VALEURS POUR VERIFIER QU'ILS SONT
* IGNORES
XPREC = VALE 'PREC';
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
* LECTURE EN COLONNES
TAB1 = LIRE 'CSV' ('CHAIN' DIVERS '/lire_csv_espaces.csv') 'SEPA' ' ';
L1 = PROG 0. 3. 6.;
L2 = PROG 1. 4. 7.;
L3 = PROG 2. 5. 8.;
SI (((MAXI 'ABS' (TAB1.(1) - L1)) >EG XPREC) OU
    ((MAXI 'ABS' (TAB1.(2) - L2)) >EG XPREC) OU
    ((MAXI 'ABS' (TAB1.(3) - L3)) >EG XPREC));
    ERRE 'PROBLEME DE LECTURE (LECTURE EN COLONNES)';
FINSI;
* LECTURE EN LIGNES
TAB2 = LIRE 'CSV' ('CHAIN' DIVERS '/lire_csv_espaces.csv') 'SEPA' ' ' 'LIGN';;
L1 = PROG 0. 1. 2.;
L2 = PROG 3. 4. 5.;
L3 = PROG 6. 7. 8.;
SI (((MAXI 'ABS' (TAB2.(1) - L1)) >EG XPREC) OU
    ((MAXI 'ABS' (TAB2.(2) - L2)) >EG XPREC) OU
    ((MAXI 'ABS' (TAB2.(3) - L3)) >EG XPREC));
    ERRE 'PROBLEME DE LECTURE (LECTURE EN LIGNES)';
FINSI;
FIN;
```

## exis_01 [Entree-Sortie Entree-Sortie]
```
* Test exis_01.dgibi: Jeux de données
* Presentation : Test de la 1ere syntaxe de EXIS :
* LOG1 ='EXIS' Nom(*'TYPE')
* LOG1 ='EXIS' Nom(*'FICHIER')
* Verification & Validation
* Les resultats attendus sont testes et une erreur
* est emise s'ils ne sont pas corrects
* Creation : 15/12/2021
* Createur : C. BERTHINIER
* MAILLAGE
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
 P1 = 0. 0. ;
 P2 = 1. 0. ;
 L1 ='DROI' 10 P1 P2 ;
* Test 1 de l'operateur EXIS
 LOG11 ='EXIS' P1 ; 'COMM' 'Doit etre VRAI';
 LOG12 ='EXIS' P1*'POINT' ; 'COMM' 'Doit etre VRAI';
 LOG13 ='EXIS' L1*'MAILLAGE' ; 'COMM' 'Doit etre VRAI';
 LOG14 ='EXIS' P1*'MAILLAGE' ; 'COMM' 'Doit etre FAUX';
 LOG15 ='EXIS' P1*'FICHIER' ; 'COMM' 'Doit etre FAUX';
 LOG1 = LOG11 'ET' LOG12 'ET' LOG13 'ET' ('NON' LOG14) 'ET' ('NON' LOG15) ;
* Creation d'un fichier bidon : Nom du fichier de calcul sans extension suivi de '.sauv'
 Nom_Fic ='VENV' 'CASTEM_PROJET';
'SI' ('EGA' Nom_fic ' ');
   Nom_fic = 'CHAI' '_bidon.dgibi';
'FINSI';
 Nom_SE ='EXTR' Nom_Fic ('LECT' 1 'PAS' 1 (('DIME' Nom_Fic) - 6)) ;
 Fic_Sauv ='CHAI' Nom_SE '.sauv' ;
'OPTI' 'SAUV' Fic_Sauv;
'SAUV' ;
* Test 2 de l'operateur EXIS
 LOG2 ='EXIS' Fic_Sauv*'FICHIER';
* Validation generale et FIN
 LOG_TOT = LOG1 'ET' LOG2 ;
'SI' ('NON' LOG_TOT);
  CHAI_ERR ='CHAI' 'Erreur dans le test de l''operateur EXIS (syntaxe 1)';
  'ERRE' CHAI_ERR ;
'FINS';
'FIN';
```

## sort_MAILLAGE [Entree-Sortie Entree-Sortie]
```
* Test sort_MAILLAGE.dgibi: Jeux de données
* TEST sort_MAILLAGE.dgibi
* Sortie d'un MAILLAGE avec SORT
* Relecture avec LIRE (Option non testee a-priori)
* Cas-Test de Verification & Validation
OPTI DIME 3;
OPTI ELEM CU20;
GRAPH = MOT 'N';
* geometrie : maillage
K = 2;
PB = 0. 2.75 0.;
PB1 = 0. 2.75 (((3.25 ** 2) - (2.75 ** 2)) ** 0.5);
PC = 3.25 0. 0.;
C1 = PC CERC (6 * K) (0. 0. 0.) PB1;
C2 = C1 PROJ CYLI (0. 0. 1) PLAN (0 0 0) (1 0 0) (0 1 0);
PA = 0. 1. 0.;
PA1 = 0. 1. (((2. ** 2) - (1. ** 2)) ** 0.5);
PD = 2. 0. 0.;
C3 = Pd CERC (6 * K) (0. 0. 0.) PA1;
C4 = C3 PROJ CYLI (0. 0. 1) PLAN (0 0 0) (1 0 0) (0 1 0);
D1 = PA DROI (2 * K) (0. 1.583 0.) DROI (2 * K) PB;
D3 = PC DROI (2 * K) (2.417 0. 0.) DROI (2 * K) PD;
ELIM (D1 ET C2 ET D3 ET C4) 0.0001;
SUR1 = DALL D1 C2 D3 C4 PLAN;
VOL1 = SUR1 VOLU (2 * K) TRAN (0. 0. -0.6);
* Surfaces et arc d'ellipse pour conditions aux limites
FACE1 = D1 TRAN (2 * K) (0. 0. -0.6);
FACE2 = C2 TRAN (2 * K) (0. 0. -0.6);
FACE3 = D3 TRAN (2 * K) (0. 0. -0.6);
C2CL = C2 PLUS (0. 0. -0.3);
ELIM (VOL1 ET FACE1 ET FACE2 ET FACE3 ET C2CL) 0.0001;
SI (NEG GRAPH 'N');
  TITR 'ELAS9 : MAILLAGE';
  TRAC (-1000 -1000 1000) FACE QUAL (COUL VOL1 BLAN);
FINSI;
* sortie : maillage
OPTI SORT 'Sort_MAILLAGE.mesh';
SORT VOL1;
OPTI SORT 'BIDON';
VOL2 = VOL1;
OUBL VOL1;
NBNO2 = NBNO VOL2;
NBEL2 = NBEL VOL2;
* Relecture : maillage
OPTI LECT 'Sort_MAILLAGE.mesh';
LIRE;
NBNO1 = NBNO VOL1;
NBEL1 = NBEL VOL1;
* Verification : Comparaison des MAILLAGES
ELIM VOL1 VOL2 1.E-5;
UNIQ (VOL1 ET VOL2);
INT1 = INTE VOL1 VOL2;
NBEI = NBEL INT1;
OPTI ECHO 0;
MESS 'NOEUDS  ' NBNO2 NBNO1;
MESS 'ELEMENTS' NBEL2 NBEL1;
MESS 'INTERSEC' NBEI ;
SI ((NEG NBNO2 NBNO1) OU (NEG NBEL2 NBEL1) OU (NEG NBEL1 NBEI));
  ERRE 5;
FINS;
OPTI ECHO 1;
* OPTI DONN 5;
FIN;
```

## tasse [Entree-Sortie Entree-Sortie]
```
* Test tasse.dgibi: Jeux de données
* Presentation : Ce cas-test de verification permet de
* lire un fichier au format 'STL'
* representant une tasse avec le logo
* Cast3M dessus.
* Creation : 03/12/2020
* Createur : F. DI PAOLA
* Le fichier tasse.stl est en binaire "little-endian" et
* n'est pas lisible sous IBM-RS6000
* Cette limitation du format STL n'est pas portable
* Le cas-test est commente
  FIN;
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
'OPTI' 'TRAC' 'PSC' ;
 tasse ='LIRE' 'STL' ('CHAINE' DIVERS '/tasse.stl') ;
'ELIM' tasse 1.E-10 ;
 atasse = ARET tasse ;
 COMPLET=FAUX;
 TASSE2='VIDE' 'MAILLAGE';
 TAB1 ='PART' tasse 'SEPA' atasse 'MAIL' ;
 DIM1 ='DIME' TAB1 - 2;
'REPE' SURi DIM1;
  'SI' ((&SURi '>EG' 66) 'ET' (&SURi '<EG' 72));
     TAB1. &SURi='COUL' TAB1. &SURi 'ROUG' ;
  'SINO';
     TAB1. &SURi='COUL' TAB1. &SURi 'GRIS' ;
  'FINS';
   TASSE2=TASSE2 'ET' TAB1. &SURi;
  'SI' COMPLET;
     TIT1='CHAI' 'PARTIE NUMERO:' &SURi ;
    'TRAC' 'FACE' TAB1. &SURi 'TITR' TIT1 'ARET' atasse;
  'FINS';
'FIN' SURi;
'TRAC' 'FACE' TASSE2 'ARET' atasse (1136.6 1975.3 797.37);
'TRAC' 'FACE' TASSE2 'ARET' atasse (516.51 -2216.1 837.11);
 FIN ;
```

## BINGHAMp [Fluides Convection]
```
* Fluide de BINGHAM : Ecoulement de POISEUILLE
* Comparaison à une solution analytique
* CANAL LONGUEUR 10. LARGEUR 4.
* Algorithme implicite (dans ce cas beaucoup plus rapide)
* Auteur : Isabelle Claudel Décembre 1997
GRAPH='N' ;
COMPLET= FAUX ;
ERR1=5.E-2 ;
option dime 2 elem qua4 ;
opti ISOV suli ;
* PROCEDURE CALCUL DE LA VISCOSITE
DEBP CALCUL ;
ARGU RX*TABLE ;
iarg=rx.'IARG' ;
si( non ( ega iarg 2)) ;
mess 'Procedure CALCUL : nombre d arguments incorrect ' iarg ;
quitter CALCUL ;
finsi ;
si ( ega ('TYPE' rx.'ARG1') 'MOT     ') ;
UN=rv.'INCO'.(rx.'ARG1') ;
sinon ;
mess 'Procedure CALCUL : type argument invalide ' ;
quitter CALCUL ;
finsi ;
si ( ega ('TYPE' rx.'ARG2') 'MOT     ') ;
NU=rv.'INCO'.(rx.'ARG2') ;
sinon ;
mess 'Procedure CALCUL : type argument invalide ' ;
quitter CALCUL ;
finsi ;
* mess ' Proc CALCUL ' ;
UN1= exco ux UN ;
UN2= exco uy UN ;
UNN1=NOMC UN1 'SCAL' ;
UNN2=NOMC UN2 'SCAL' ;
unn1= kcht $mt scal sommet UNN1;
unn2= kcht $mt scal sommet UNN2;
GU1 = kops UNN1 'GRAD' $mt ;
GU2 = kops UNN2 'GRAD' $mt ;
ddudx= exco ux GU1 ;
ddudy= exco uy GU1 ;
ddvdx= exco ux GU2 ;
ddvdy= exco uy GU2 ;
dudx= NOMC ddudx 'SCAL' ;
dudy= NOMC ddudy 'SCAL' ;
dvdx= NOMC ddvdx 'SCAL' ;
dvdy= NOMC ddvdy 'SCAL' ;
dudx= kcht $mt scal centre dudx ;
dudy= kcht $mt scal centre dudy ;
dvdx= kcht $mt scal centre dvdx ;
dvdy= kcht $mt scal centre dvdy ;
D11= dudx ;
D12= (kops (kops dudy '+' dvdx) '/' 2) ;
D21= (D12) ;
D22= (dvdy) ;
* Proten = Produit tensoriel D:D
ProTen = kops (kops D11 '*' D11) '+' (kops D12 '*' D12) ;
ProTen = kops ProTen '+' (kops D22 '*' D22) ;
ProTen = kops ProTen '+' (kops D21 '*' D21) ;
rv.'INCO'.'ProTen' = ProTen ;
* list ProTen ;
* Norme de D = racine carree (Proten / 2)
NormD = kops ProTen '/' 2. ;
NormD = kops NormD '**' 0.5 ;
* Comportement rhéologique de Bingham
Seuil = kcht $mt scal centre 10. ;
MUB = kcht $mt scal centre 10. ;
MU0 = kcht $mt scal centre 1000. ;
Dseuil = kops Seuil '/' (kops 2. '*' (kops MU0 '-' MUB) ) ;
TESTi = kcht $mt scal centre (NormD MASQUE 'EGINFE' Dseuil) ;
TESTs = kcht $mt scal centre (NormD MASQUE 'SUPERIEUR' Dseuil) ;
NormD = kops ( kops NormD '*' TESTs ) '+' ( kops Dseuil '*' TESTi) ;
MU = kops MUB '+' (kops Seuil '/' (kops 2. '*' NormD) ) ;
ro = kcht $mt scal centre 1. ;
NU = kops MU '/' ro ;
rv.'INCO'.(rx.'ARG2')=NU ;
rv.'INCO'.'GU1'=D12 ;
as2 ama1 = 'KOPS' 'MATRIK' ;
FINPROC as2 ama1 ;
* MAILLAGE
nbe=16 ; nbv=16 ;
nbee = nbe / 2 ;
p1=0. 0.;
p2=4. 0.;
entree= p1 d nbe p2 ;
c1= 5. 0. ;
isa = 2. 0. ;
entree2 = isa d nbee p2 ;
ikas=0 ;
* mess 'ikas= 0 --> DROIT (option par defaut)  ikas=1 --> COURBE  ? ';
* obtenir ikas*entier ;
si (EGA ikas 1) ;
q1=p1 tour c1 -90. ;
q2=p2 tour c1 -90. ;
pp1=p1 c c1 q1 nbv;
pp2=p2 c c1 q2 nbv;
sortie=entree tour c1 -90 ;
sinon ;
q1=p1 plus (0 10) ;
q2=p2 plus (0 10) ;
pp1=p1 d q1 nbv;
pp2=p2 d q2 nbv;
sortie=entree plus (0 10) ;
finsi ;
mientree = entree plus (0. 5.) ;
pp1=inve pp1 ;
sortie=inve sortie;
elim 0.0001 (sortie et pp1 et pp2 et entree );
cnt=entree et pp2 et sortie et pp1 ;
* mt=surf cnt ;
mt=daller entree pp2 sortie pp1 ;
angle=0. ;
mt=mt tour p1 angle ;
entree=entree tour p1 angle ;
sortie=sortie tour p1 angle ;
pp1=pp1 tour p1 angle ;
pp2=pp2 tour p1 angle ;
elim (pp1 et pp2 et entree et sortie et mt et entree2) 0.0001 ;
* ccc=2. 5. ;
* option donn 5 ;
mt = mt 'COUL' bleu ;
* trace mt ;
* RESOLUTION
mt0= mt ;
mt=chan mt quaf ;
$mt=mode mt 'NAVIER_STOKES' LINE ;
doma $mt 'IMPR' ;
entre1= chan entree quaf ;
sorti1= chan sortie quaf ;
elim (mt et entre1 et sorti1 et pp1 et pp2 ) 1.e-4 ;
$entree = mode entre1 'NAVIER_STOKES' LINE ;
$sortie = mode sorti1 'NAVIER_STOKES' LINE ;
* doma $entree 'IMPR' ;
* doma $sortie 'IMPR' ;
* dP/dy = - 20
 to = kcht $entree vect centre ( 0. 0.) ;
 tos = kcht $sortie vect centre ( 0. 200.) ;
* to = kcht $entree vect centre ( 0. 6.) ;
* tos = kcht $sortie vect centre ( 0. 0.) ;
EPS=1.E-6 ;
DT=1. ;
RV = EQEX $mt OPTI EF IMPL 'CENTREE'
 ZONE $mt 'OPER' CALCUL 'UN' 'NU'
 ZONE $mt 'OPER' DUDW EPS INCO 'UN'
 OPTI EF IMPL 'CENTREE'
ZONE $mt 'OPER' NS 1. 'UN' 'NU' INCO 'UN'
 ZONE $entree 'OPER' 'TOIMP' TO INCO 'UN'
 ZONE $sortie 'OPER' 'TOIMP' TOS INCO 'UN'
;
RV=EQEX RV CLIM
 UN UIMP (pp1 et pp2) 0.
 UN VIMP (pp1 et pp2) 0.
;
rv.'INCO'=table 'INCO' ;
rv.'INCO'.'UN' = kcht $mt VECT SOMMET (0. 0.) ;
rv.'INCO'.'NU' = kcht $mt SCAL CENTRE 10. ;
rv.'INCO'.'ProTen'= kcht $mt SCAL SOMMET 0. ;
DEBPROC POST ;
ARGU RV*TABLE GRAPH*MOT ;
* POST TRAITEMENT
evol2v10 = EVOL 'CHPO' (rv.'INCO'.'UN') UY (entree2) ;
* list evol2v ;
XX=extr evol2v10 'ABSC' ;
vth10 = prog
 -2.25
 -2.25
 -2.25
 -2.1875
 -2.
 -1.6875
 -1.25
 -0.6875
 0.
 ;
vc=extr evol2v10 'ORDO' ;
ER=SOMM( abs ((vth10 - vc)/2.5) ) ;
mess ' Ecart sur profil de V : ' ER ;
evol1v10 = EVOL 'MANU' Rayon xx Vitesse vth10 ;
evolt = evol1v10 et evol2v10 ;
TAB1=TABLE ;
TAB1.'TITRE'=TABLE ;
TAB1.1='MARQ ETOI REGU ' ;
TAB1.'TITRE' . 1=MOT 'V_theorique ' ;
TAB1.2='TIRR      REGU ' ;
TAB1.'TITRE' . 2=MOT 'V_calculee ' ;
un=rv.INCO.'UN' ;
ung1=vect un 0.5 ux uy jaune ;
si (EGA GRAPH 'O' );
DESS evolt 'TITX' 'X (m)' 'TITY' 'V (m/s)' 'LEGE' TAB1 ;
* list evolt ;
mt0 = doma $mt maillage ;
trace ung1 mt0 ;
nu = elno (rv.'INCO'.'NU') $mt ;
trace nu mt0 12 ;
FINSI ;
 si ( er > err1 ) ; erreur 5 ; finsi ;
FINPROC ;
rv.'OMEGA'=0.9;
rv.'NITER'=20 ;
EXEC RV ;
POST RV GRAPH ;
 FIN ;
```

## darcy3VF [Fluides Darcy]
```
* CAS TEST : darcy3.dgibi
 GRAPH = 'N' ;
'SAUT' 'PAGE' ;
NITER = 40 ;
* TEST DARCY3
* CALCUL DARCY ORTHOTROPE 3D
* TEST de TRANGEOL en VF
* On effectue trois calculs sur un cube, maillé par des cubes
* réguliers.
* Les conditions aux limites varient suivant le cas considéré :
* On impose le flux ou la charge sur les cotés du domaine.
* La solution analytique en charge est un polynome de degré un,
* la vitesse est constante et la conductivité hydraulique orthotrope.
* | 1 0 0 |
* K = | 0 3/4 0 |
* | 0 0 1/2 |
* H(x,y,z) = -45 x -80 y -60z + 200.
* V(x,y,z) = ( 45 ; 60 ; 30 )
* On s'attend à une précision de l'ordre de la précision machine.
* LE calcul est effectué comme limite d'un instationnaire pour
* tester TRANGEOL dans une boucle
'SAUT' 'PAGE' ;
* - Options générales de calcul.
'TITR' 'EFMH DARCY ORTHOTROPE 3D Lineaire : darcy3.dgibi' ;
'OPTI' 'DIME' 3 'ELEM' 'TET4' ;
 'OPTI' 'ECHO' 1 ;
* = MAILLAGE =
OEIL = 5.D0 6.D0 7.D0 ;
VECX = 1.D0 0.D0 0.D0 ;
VECY = 0.D0 1.D0 0.D0 ;
VECZ = 0.D0 0.D0 1.D0 ;
ENX = 6 ;
ENY = 6 ;
ENZ = 6 ;
DX = 1.D0 / ENX ;
DY = 1.D0 / ENY ;
DZ = 1.D0 / ENZ ;
* - Création des points
A0 = 0.D0 0.D0 0.D0 ;
B0 = 1.D0 0.D0 0.D0 ;
C0 = 1.D0 1.D0 0.D0 ;
D0 = 0.D0 1.D0 0.D0 ;
E0 = 0.D0 0.D0 1.D0 ;
F0 = 1.D0 0.D0 1.D0 ;
G0 = 1.D0 1.D0 1.D0 ;
H0 = 0.D0 1.D0 1.D0 ;
* - Création des droites
AB = 'DROI' ENX A0 B0 ;
AD = 'DROI' ENY A0 D0 ;
AE = 'DROI' ENZ A0 E0 ;
BC = 'DROI' ENY B0 C0 ;
BF = 'DROI' ENZ B0 F0 ;
CD = 'DROI' ENX C0 D0 ;
CG = 'DROI' ENZ C0 G0 ;
DH = 'DROI' ENZ D0 H0 ;
EF = 'DROI' ENX E0 F0 ;
EH = 'DROI' ENY E0 H0 ;
FG = 'DROI' ENY F0 G0 ;
GH = 'DROI' ENX G0 H0 ;
FE = 'INVE' EF ;
EA = 'INVE' AE ;
DC = 'INVE' CD ;
HD = 'INVE' DH ;
DA = 'INVE' AD ;
HE = 'INVE' EH ;
GF = 'INVE' FG ;
FB = 'INVE' BF ;
* - Creation des faces du cube
SDRO = 'DALL' AB BF FE EA 'PLAN' ;
SGAU = 'DALL' DC CG GH HD 'PLAN' ;
SBAS = 'DALL' AB BC CD DA 'PLAN' ;
SHAU = 'DALL' EF FG GH HE 'PLAN' ;
SDEV = 'DALL' BC CG GF FB 'PLAN' ;
SDER = 'DALL' AD DH HE EA 'PLAN' ;
* - Création maillage géométrique
ENXM = ENX + ENY + ENZ ;
ELI0 = 1.D0 / ENXM / 10.D0 ;
'SI' ('EGA' ('VALEUR' 'ELEM') 'CUB8') ;
   CUBE1 = 'PAVE' SDER SDEV SBAS SHAU SGAU SDRO ;
'SINON' ;
   CUBE1 = 'VOLU' (SDER 'ET' SDEV 'ET' SBAS 'ET' SHAU
                   'ET' SGAU 'ET' SDRO) ;
'FINSI' ;
QFTOT = CHANGE CUBE1 QUAF ;
QFGAU = CHANGE SGAU QUAF ;
QFDRO = CHANGE SDRO QUAF ;
QFHAU = CHANGE SHAU QUAF ;
QFBAS = CHANGE SBAS QUAF ;
QFDEV = CHANGE SDEV QUAF ;
QFDER = CHANGE SDER QUAF ;
 ELIM ELI0 (QFTOT ET QFGAU ET QFDRO ET QFHAU ET QFBAS ET QFDEV ET
              QFDER ) ;
* - Création maillage HYBRIDE et sous-objets (conditions aux limites)
MODHYB = MODE QFTOT 'DARCY' 'ANISOTROPE' ;
MODGAU = MODE QFGAU 'DARCY' 'ANISOTROPE' ;
MODDRO = MODE QFDRO 'DARCY' 'ANISOTROPE' ;
MODHAU = MODE QFHAU 'DARCY' 'ANISOTROPE' ;
MODBAS = MODE QFBAS 'DARCY' 'ANISOTROPE' ;
MODDEV = MODE QFDEV 'DARCY' 'ANISOTROPE' ;
MODDER = MODE QFDER 'DARCY' 'ANISOTROPE' ;
C11 = 'DOMA' MODHYB 'VOLUME' ;
CHYB1 = 'DOMA' MODHYB 'SURFACE' ;
CHYB2 = 'DOMA' MODHYB 'NORMALE' ;
CEGAU = 'DOMA' MODGAU 'CENTRE' ;
CEDRO = 'DOMA' MODDRO 'CENTRE' ;
CEHAU = 'DOMA' MODHAU 'CENTRE' ;
CEBAS = 'DOMA' MODBAS 'CENTRE' ;
CEDEV = 'DOMA' MODDEV 'CENTRE' ;
CEDER = 'DOMA' MODDER 'CENTRE' ;
* - Solution analytique
XX YY ZZ = 'COOR' (DOMA MODHYB 'FACE' ) ;
XXC YYC ZZC = 'COOR' (DOMA MODHYB 'CENTRE') ;
VKX = 1.D0 ;
VKY = 0.75D0 ;
VKZ = 0.5D0 ;
VVKX = MANU 'CHPO' (DOMA MODHYB 'CENTRE') 'K11' 1.D0 ;
VVKX = CHANGER ATTRIBUT VVKX 'NATU' DISCRET ;
VVKY = MANU 'CHPO' (DOMA MODHYB 'CENTRE') 'K22' 0.75D0 ;
VVKY = CHANGER ATTRIBUT VVKY 'NATU' DISCRET ;
VVKZ = MANU 'CHPO' (DOMA MODHYB 'CENTRE') 'K33' 0.5D0 ;
VVKZ = CHANGER ATTRIBUT VVKZ 'NATU' DISCRET ;
AA = -45.D0 ;
BB = -80.D0 ;
CC = -60.D0 ;
DD = 200.D0 ;
AAA = -1.D0 * VKX * AA ;
BBB = -1.D0 * VKY * BB ;
CCC = -1.D0 * VKZ * CC ;
PANAF = (AA * XX) + (BB * YY) + (CC * ZZ) + DD ;
PANAC = (AA * XXC) + (BB * YYC) + (CC * ZZC) + DD ;
VANAC = 'MANU' 'CHPO' (DOMA MODHYB 'CENTRE') 3 'VX' AAA
         'VY' BBB 'VZ' CCC ;
VANAF = 'MANU' 'CHPO' (DOMA MODHYB 'FACE') 3 'VX' AAA
          'VY' BBB 'VZ' CCC ;
* = RESOLUTION =
MATI3 = (NOMC 'K11' VVKX) et
         (NOMC 'K22' VVKY) et
         (NOMC 'K33' VVKZ) et
         (NOMC 'K21' (0.D0 * VVKX)) et
         (NOMC 'K31' (0.D0 * VVKX)) et
         (NOMC 'K32' (0.D0 * VVKX)) ;
* ;
* - Conditions aux limites
BBGAU = 'BLOQ' CEGAU 'TH' ;
BBDRO = 'BLOQ' CEDRO 'TH' ;
BBHAU = 'BLOQ' CEHAU 'TH' ;
BBBAS = 'BLOQ' CEBAS 'TH' ;
BBDEV = 'BLOQ' CEDEV 'TH' ;
BBDER = 'BLOQ' CEDER 'TH' ;
* - TH imposée
TTIMP = 'REDU' PANAF CEGAU ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEGAU = 'DEPI' BBGAU TTIM2 ;
TTIMP = 'REDU' PANAF CEDRO ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEDRO = 'DEPI' BBDRO TTIM2 ;
TTIMP = 'REDU' PANAF CEBAS ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEBAS = 'DEPI' BBBAS TTIM2 ;
TTIMP = 'REDU' PANAF CEHAU ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEHAU = 'DEPI' BBHAU TTIM2 ;
TTIMP = 'REDU' PANAF CEDEV ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEDEV = 'DEPI' BBDEV TTIM2 ;
TTIMP = 'REDU' PANAF CEDER ;
TTIM2 = 'EXCO' TTIMP 'SCAL' 'TH' ;
EEDER = 'DEPI' BBDER TTIM2 ;
* - Flux imposé
FLDRO = -60.D0 * (nomc 'FLUX' (doma moddro VOLUME));
FLGAU = 60.D0 * (nomc 'FLUX' (doma modgau VOLUME));
FLHAU = 30.D0 * (nomc 'FLUX' (doma modhau VOLUME));
FLBAS = -30.D0 * (nomc 'FLUX' (doma modbas VOLUME));
FLDEV = 45.D0 * (nomc 'FLUX' (doma moddev VOLUME));
FLDER = -45.D0 * (nomc 'FLUX' (doma modder VOLUME));
* - Assemblage et résolution en TH
h_lim = 'RESOUD' (BBGAU 'ET' BBDEV)
                 (EEGAU 'ET' EEDEV) ;
h_lim = 'EXCO' 'TH' h_lim;
CHCLIM = TABLE;
CHCLIM . 'NEUMANN' = ('NOMC' 'I35' ( FLHAU 'ET' FLBAS
                                 'ET' FLDRO 'ET' FLDER));
CHCLIM . 'DIRICHLET' = 'NOMC' 'I35' h_lim;
GEOL1 = TABLE;
GEOL1 . 'CONCENTRATION' = 'NOMC' 'I35' (0.D0 * PANAC) ;
GEOL1 . 'LUMP' = FAUX ;
GEOL1 . 'TYPDISCRETISATION' = 'VF' ;
GEOL1 . 'THETA_DIFFUSION' = 1.0D0 ;
GEOL1 . 'THETA_CONVECTION' = 1.0D0 ;
GEOL1 . 'DECENTREMENT' = FAUX ;
GEOL1 . 'DELTAT' = 10.D0 / NITER ;
GEOL1 . 'DIFFUSIVITE' = mati3 ;
GEOL1 . 'SOLVEUR' = 3 ;
GEOL1 . 'PRECONDITIONNEUR' = 3 ;
GEOL1 . 'POROSITE' = 'MANU' 'CHPO'
                (doma MODHYB CENTRE) 'CK' 1.D0 ;
GEOL1 . 'CLIMITES' = CHCLIM ;
GEOL1 . 'RECALCUL' = VRAI ;
GEOL1 GEOL2 = TRANGEOL Modhyb GEOL1;
* boucle transitoire
REPE blocc NITER ;
   mess 'boucle' &blocc;
   GEOL1 . 'RECALCUL' = FAUX ;
   GEOL1 GEOL2 = TRANGEOL Modhyb GEOL1 GEOL2;
FIN blocc;
PCEN3 = 'NOMC' 'H' GEOL1 . 'CONCENTRATION' ;
QFACE3 = 'NOMC' 'FLUX' GEOL1 . 'FLUXDIFF' ;
* - Calcul de V
VCENT3 = 'HVIT' MODHYB QFACE3 ;
QFACE3 = 'EXCO' QFACE3 'FLUX' 'SCAL' ;
VFACE3 = QFACE3 * CHYB2 / CHYB1 ;
* = Calcul ERREUR =
* ERReur relative en charge H au centre des éléments
* Erreur relative sur la vitesse au centre des éléments
ERRP3 = 'EXCO' PCEN3 'H' 'SCAL' ;
ERRP3 = ERRP3 - PANAC / PANAC ;
ERRP3 = 'ABS' ERRP3 ;
MOT1 = 'MOTS' 'VX' 'VY' 'VZ' ;
VDVD = 'PSCA' VANAC VANAC MOT1 MOT1 ;
VD3 = VANAC - VCENT3 ;
VC3 = 'PSCA' VD3 VD3 MOT1 MOT1 ;
SDC3 = 'ABS' ( VC3 / VDVD ) ;
SDC3 = SDC3 '**' 0.5 ;
* = Tracé resultats =
'SI' ('NEG' GRAPH 'N') ;
* - Transformation des quantités aux centres en MCHAML constant.
ERRP3 = 'KCHA' MODHYB 'CHAM' ERRP3 ;
SDS3 = 'KCHA' MODHYB 'CHAM' SDC3 ;
* L'erreur relative sur la charge au centre
* L'erreur relative sur la Vitesse au centre
'TITR' 'darcy3/3 : Erreur relative sur la charge' ;
'TRAC' MODHYB ERRP3 ;
'TITR' 'darcy3/3 : Erreur relative sur la vitesse' ;
'TRAC' MODHYB SDS3 ;
'FINSI' ;
* = Gestion ERREURS =
MAXP3 = 'MAXI' ERRP3 ;
MAXV3 = 'MAXI' SDC3 ;
'SAUT' 'PAGE' ;
'SAUT' 2 'LIGNE' ;
'MESS' '                             ERREURS RELATIVES            ' ;
'SAUT' 1 'LIGNE' ;
'MESS' ' cas test             H                 V' ;
'SAUT' 1 'LIGNE' ;
'MESS' ' numero3           ' maxp3 '      ' maxv3 ;
'SAUT' 2 'LIGNE' ;
EPS0 = 1.D-7 ;
LOG6 = MAXP3 > EPS0 ;
LOG9 = MAXV3 > EPS0 ;
LP0 = LOG6 ;
LV0 = LOG9 ;
L0 = LP0 'OU' LV0 ;
'SI' ( L0 ) ;
   'ERRE' 5 ;
'SINO' ;
   'ERRE' 0 ;
'FINSI' ;
'FIN' ;
```

## darcy5 [Fluides Darcy]
```
* CAS TEST : darcy5.dgibi
 GRAPH = FAUX ;
* GRAPH = VRAI ;
'SAUT' 'PAGE' ;
* TEST DARCY5
* Validation de la résolution des équations de DARCY formulées en
* (VITESSE - PRESSION) par comparaison avec
* la résolution des équations de DARCY formulées en (VITESSE - CHARGE)
* (Résolution par une méthode d'éléments finis mixtes hybrides)
* Le maillage est composés de triangles et de quadrangles et contient
* des lignes de maillages courbes
* la massif est supposé isotrope, indéformable et saturé
* Pour permettre la comparaison, la densité de l'eau reste constante
 OPTI ECHO 0 ;
'SAUT' 'PAGE' ;
* - Options générales de calcul
TITRE
'EFMY DARCY FORMULATION (VITESSE - PRESSION) 2D : darcy5.dgibi' ;
OPTI DIME 2 ELEM QUA4 ;
OPTI ISOV SURF ;
* - Données physiques
* - Densité de l'eau
RHO0 = 1000. ;
* - Pression athmosphérique
P0 = 1.013E5 ;
* - Composante du vecteur gravité
Gx0 = 0. ;
Gy0 = -9.81 ;
* - Perméabilité intrinsèque
LA0 = 1.e-9 ;
* - Construction du maillage
* - Discrétisation spatiale
ENX = 15 ;
ENY0 = 5 ;
ENY1 = 5 ;
ENY2 = 5 ;
* - Création des points
A0 = 0.d0 -2.d3 ; B0 = 5.d3 -2.d3 ;
A1 = 0.d0 -1.d3 ; B1 = 5.d3 -1.d3 ; C1 = 2.d3 -1.25d3 ;
A2 = 0.d0 0.0d3 ; B2 = 5.d3 0.0d3 ; C2 = 2.d3 0.25d3 ;
A3 = 0.d0 1.5d3 ; B3 = 5.d3 1.d3 ; C3 = 2.5d3 1.5d3 ;
* - Création des droites
AB0 = DROI ENX A0 B0 ;
AB1 = A1 cer3 C1 ENX B1 ;
AB2 = A2 cer3 C2 ENX B2 ;
AB3 = A3 cer3 C3 ENX B3 ;
* - Creation des SURFACES
NIVEAU0 = AB0 regle ENY0 AB1 ;
OPTI ELEM TRI3 ;
NIVEAU1 = AB1 regle ENY1 AB2 ;
OPTI ELEM QUA4 ;
NIVEAU2 = AB2 regle ENY2 AB3 ;
MASSIF0 = NIVEAU0 ET NIVEAU1 ET NIVEAU2 ;
HAUT = INVE AB3 ;
MASSIF0 = ORIENT MASSIF0 ;
QMASSIF = CHANGE MASSIF0 QUAF ;
QFHAUT = CHANGE HAUT QUAF ;
 ELIM 0.01 (QMASSIF ET QFHAUT ) ;
* - Domaines
* HYTOT = DOMA MASSIF0 0.01 ;
* CHYB1 = DOMA HYTOT 'SURFACE' ;
* CHYB2 = DOMA HYTOT 'NORMALE' ;
* MCHYB = DOMA HYTOT 'ORIENTAT' ;
* HYHAUT = DOMA HAUT INCL HYTOT 0.01 ;
* - Modélisation
* MODHYB = MODE HYTOT DARCY ISOTROPE HYQ4 HYT3 ;
 MODHYB = MODE QMASSIF DARCY ISOTROPE ;
 MODHAU = MODE QFHAUT DARCY ISOTROPE ;
 CHYB1 = DOMA MODHYB 'SURFACE' ;
 CHYB2 = DOMA MODHYB 'NORMALE' ;
 CEHAUT= DOMA MODHAU 'CENTRE' ;
 CETOT= DOMA MODHYB 'CENTRE' ;
* - perméabilité intrinsèque
LMME = MANU CHPO CETOT 1 'K' la0 'NATURE' 'DIFFU' ;
* - Résolution en en (VITESSE ; PRESSION)
LMMA = KCHA MODHYB 'CHAM' LMME ;
MATI_P = MATERIAU MODHYB 'K' LMMA ;
* Masse HYBride
CND1A_P = MHYBR MODHYB MATI_P ;
* Masse FORce
M_P = MHYBR MODHYB 'MASSE' ;
* MAtrice en Trace de pression TP
HND1A_P = MATP MODHYB CND1A_P ;
* - Conditions aux limites
BHAUT_P = BLOQUE CEHAUT 'TH' ;
* - TP imposee
PIMP = MANU CHPO CEHAUT 1 'TH' P0 'NATURE' 'DISCRET' ;
EHAUT_P = DEPI BHAUT_P PIMP ;
* - contribution des forces de volume au second membre
RHO = MANU CHPO CETOT 1 'SCAL' RHO0 'NATURE' 'DISCRET' ;
RCH = MANU CHPO CETOT 2 'FX' gx0 'FY' gy0 'NATURE' 'DISCRET' ;
RCH = RHO * RCH ;
GRAV2TP = SQTP MODHYB HND1A_P M_P RCH ;
* - Assemblage matrice et second membre
CCC1_P = HND1A_P ET BHAUT_P ;
* second membre du système matriciel en trace de charge
FFF1_P = GRAV2TP et EHAUT_P ;
* - Resolution en trace de pression
CHTER1_P = RESOUDRE CCC1_P FFF1_P ;
CHTER1_P = exco CHTER1_P 'TH' 'TH';
* - Calcul des pressions élémentaires
PCEN1 = HYBP MODHYB CND1A_P CHTER1_P M_P RCH ;
* - Calcul des débits
QFACE1_P = HDEBI MODHYB CND1A_P PCEN1 CHTER1_P M_P RCH;
VCENT1_P = HVIT MODHYB QFACE1_P ;
* VV = VECT VCENT1_P 0.5e9 'VX' 'VY' VERT ;
* titre 'VITESSES AUX CENTRES DES ELEMENTS : ECHL=1e9:2' ;
* TRAC VV CETOT ;
* - Résolution en (VITESSE ; CHARGE)
* - conductivité hydraulique
LMME = LMME * (ABS Gy0) * RHO0 ;
LMMA = KCHA MODHYB 'CHAM' LMME ;
MATI_H = MATERIAU MODHYB 'K' LMMA ;
* Masse HYBride
CND1A_H = MHYBR MODHYB MATI_H ;
* MAtrice en Trace de charge TH
HND1A_H = MATP MODHYB CND1A_H ;
* - Conditions aux limites
BHAUT_H = BLOQUE CEHAUT 'TH' ;
* - TH imposee
PIMP = NOMC 'TH' (CEHAUT COOR 2) ;
EHAUT_H = DEPI BHAUT_H PIMP ;
* - Assemblage matrice et second membre
CCC1_H = HND1A_H ET BHAUT_H ;
* second membre du système matriciel en trace de charge
FFF1_H = EHAUT_H ;
* - Resolution en trace de charge
CHTER1_H = RESOUDRE CCC1_H FFF1_H ;
CHTER1_H = exco CHTER1_H 'TH' 'TH';
* - Calcul de la charge
TCEN1 = HYBP MODHYB CND1A_H CHTER1_H ;
* - Calcul de la vitesse
QFACE1_H = HDEBI MODHYB CND1A_H TCEN1 CHTER1_H ;
VCENT1_H = HVIT MODHYB QFACE1_H ;
* VV = VECT VCENT1_H 0.5e9 'VX' 'VY' VERT ;
* titre 'CALCUL EN CHARGE : VITESSES AUX CENTRES DES ELTS : ECHL=1e9:2';
* TRAC VV CETOT ;
* - Comparaison des deux résolutions
* - comparaison des traces de charges
TP2 = (NOMC CHTER1_P SCAL) - P0 / (rho0 * gy0) ;
TP2 = ((DOMA MODHYB 'FACE') COOR 2) - TP2 ;
ER2 = (NOMC CHTER1_H SCAL)/TP2 - 1. ;
maxtp1 = ER2 ABS MAXI ;
* - comparaison des charges
PCEN2 = (NOMC PCEN1 SCAL) - P0 / (rho0 * gy0) ;
PCEN2 = CETOT COOR 2 - PCEN2 ;
ER2 = (NOMC TCEN1 SCAL)/PCEN2 - 1. ;
maxp1 = ER2 ABS MAXI ;
'SI' GRAPH ;
TITRE 'VARIATIONS RELATIVES DES CHARGES DH/H' ;
TRAC (KCHA MODHYB 'CHAM' er2) MODHYB (CONTOUR
 (DOMA MODHYB 'MAILLAGE')) ;
'FINSI' ;
* - comparaison des vitesse
QFACE1_P = NOMC SCAL QFACE1_P ;
VFACE1_P = QFACE1_P * CHYB2 / CHYB1 ;
QFACE1_H = NOMC SCAL QFACE1_H ;
VFACE1_H = QFACE1_H * CHYB2 / CHYB1 ;
maxvf1 = (kops QFACE1_P '-' QFACE1_H) / (maxi QFACE1_H) ABS MAXI ;
MOT1 = 'MOTS' 'VX' 'VY' ;
VDVD = 'PSCA' VCENT1_H VCENT1_H MOT1 MOT1 ;
VD1 = VCENT1_P - VCENT1_H ;
VC1 = 'PSCA' VD1 VD1 MOT1 MOT1 ;
SDC1 = 'ABS' ( VC1 / VDVD ) ;
SDC1 = SDC1 '**' 0.5D0 ;
maxvc1 = MAXI SDC1 ;
'SI' GRAPH ;
TITRE ' VARIATIONS RELATIVES DES VITESSES |DV|/|V|' ;
TRAC ('KCHA' MODHYB 'CHAM' SDC1) MODHYB (CONTOUR
 (DOMA MODHYB 'MAILLAGE')) ;
'FINSI' ;
'SAUT' 'PAGE' ;
'SAUT' 2 'LIGNE' ;
'MESS' '                       VARIATIONS RELATIVES                ' ;
'SAUT' 1 'LIGNE' ;
'MESS' '      TH                H                Vf              Vc' ;
'SAUT' 1 'LIGNE' ;
'MESS' ' ' maxtp1 ' ' maxp1 ' ' maxvf1 ' ' maxvc1 ;
'SAUT' 2 'LIGNE' ;
EPS0 = 1.E-7 ;
LOG1 = MAXTP1 > EPS0 ;
LOG2 = MAXP1 > EPS0 ;
LOG3 = MAXVF1 > EPS0 ;
LOG4 = MAXVC1 > EPS0 ;
L0 = LOG1 'OU' LOG2 'OU' LOG3 'OU' LOG4 ;
'SI' ( L0 ) ;
   'ERRE' 5 ;
'SINO' ;
   'ERRE' 0 ;
'FINS' ;
FIN ;
```

## pret_scal1 [Fluides Darcy]
```
* APPROCHE VF
* OPERATEUR PRET
* Operateur qui reconstruit les variables primitives aux faces
* A. BECCANTINI SFME/LTMF NOVEMBRE 01
 'OPTION' 'DIME' 2 'ELEM' QUA4 'ECHO' 0 'TRAC' 'X' ;
* GRAPH
* GRAPH = VRAI ;
 GRAPH = FAUX ;
* DOMAINE SPATIAL
* Deux carre
 A1 = 0.0D0 0.0D0;
 A2 = 1.0D0 0.0D0;
 A3 = 2.0D0 0.0D0;
 A4 = 2.0D0 1.0D0;
 A5 = 1.0D0 1.0D0;
 A6 = 0.0D0 1.0D0;
 L12 = A1 'DROIT' 1 A2;
 L23 = A2 'DROIT' 1 A3;
 L34 = A3 'DROIT' 1 A4;
 L45 = A4 'DROIT' 1 A5;
 L56 = A5 'DROIT' 1 A6;
 L61 = A6 'DROIT' 1 A1;
 L25 = A2 'DROIT' 1 A5;
 DOM10 = 'DALL' L12 L25 L56 L61
          'PLANE';
 DOM20 = 'DALL' L23 L34 L45 ('INVERSE' L25)
          'PLANE';
* Point face entre le deux carre, ou on fait les controlles
 P10 = 1.0 0.5;
 DOM1 = DOM10 ;
 DOM2 = DOM20 ;
'ELIMINATION' (DOM1 ET DOM2) 1D-6;
DOMTOT = DOM1 ET DOM2;
 $DOMTOT = 'MODELISER' DOMTOT 'EULER';
 $DOM1 = 'MODELISER' DOM1 'EULER';
 $DOM2 = 'MODELISER' DOM2 'EULER';
 TDOMTOT = 'DOMA' $DOMTOT 'VF';
 TDOM1 = 'DOMA' $DOM1 'VF';
 TDOM2 = 'DOMA' $DOM2 'VF';
 MDOM1 = TDOM1 . 'QUAF' ;
 MDOM2 = TDOM2 . 'QUAF' ;
 MDOMTOT = TDOMTOT . 'QUAF' ;
 'ELIMINATION' (MDOMTOT ET MDOM1) 0.0001 ;
 'ELIMINATION' (MDOMTOT ET MDOM2) 0.0001 ;
 P1 = ('DOMA' $DOMTOT 'FACE') 'POIN' 'PROC' P10 ;
 'SI' GRAPH;
   'TRACER' (('DOMA' $DOMTOT 'MAILLAGE') 'ET' ('DOMA' $DOMTOT 'FACEL')
   'ET' P1) 'TITRE' 'Domaine et FACEL';
 'FINSI' ;
 ETATG = 'PROG' 1.0 2.0 3.0 4.0 ;
 ETATD = ETATG '*' 10 ;
 SN =('MANUEL' 'CHPO' ('DOMA' $DOM1 'CENTRE') 4 'C1' 1.0 'C2' 2.0
     'C3' 3.0 'C4' 4.0 'NATU' 'DISCRET') 'ET'
     ('MANUEL' 'CHPO' ('DOMA' $DOM2 'CENTRE') 4 'C1' 10.0 'C2' 20.0
     'C3' 30.0 'C4' 40.0 'NATU' 'DISCRET') ;
 SF = 'PRET' 'CLAUDEIS' 'FACE' 1 $DOMTOT SN ;
* Control des etats sur la surface qui contient P1
 GEOP1 = ('DOMA' $DOMTOT 'FACEL') 'ELEM' 'APPUYE' 'LARGEMENT' P1;
 GEOP2 = ('DOMA' $DOMTOT 'FACE') 'ELEM' 'APPUYE' 'LARGEMENT' P1;
 SGEOP1 = 'REDU' SF GEOP1;
 C1g = 'EXTRAIRE' SGEOP1 'C1' 1 1 1;
 C1d = 'EXTRAIRE' SGEOP1 'C1' 1 1 3;
 C2g = 'EXTRAIRE' SGEOP1 'C2' 1 1 1;
 C2d = 'EXTRAIRE' SGEOP1 'C2' 1 1 3;
 C3g = 'EXTRAIRE' SGEOP1 'C3' 1 1 1;
 C3d = 'EXTRAIRE' SGEOP1 'C3' 1 1 3;
 C4g = 'EXTRAIRE' SGEOP1 'C4' 1 1 1;
 C4d = 'EXTRAIRE' SGEOP1 'C4' 1 1 3;
 CHPNOR = 'DOMA' $DOMTOT 'NORMALE' ;
* Orientation de la normal n de castem par raport a la
* notre; t est par consequence
 ORIENT = 'EXTRAIRE' CHPNOR P1 'UX' ;
* ORIENT = -1 -> Mon etat gauche est son etat droite
 'SI' (ORIENT > 0);
    ERRLIG = 'PROG' C1g C2g C3g C4g;
    ERRLID = 'PROG' C1d C2d C3d C4d;
 'SINON' ;
    ERRLID = 'PROG' C1g C2g C3g C4g;
    ERRLIG = 'PROG' C1d C2d C3d C4d;
 'FINSI' ;
 ERRO = 'MAXIMUM' ('PROG'
   ('MAXIMUM' (ETATG '-' ERRLIG) 'ABS')
   ('MAXIMUM' (ETATD '-' ERRLID) 'ABS')
 );
 'SI' (ERRO > 1.0D-14)
    'MESSAGE' 'Ordre en espace = 1';
    'MESSAGE' 'PRET = ???'
    'ERREUR' 5 ;
 'FINSI' ;
'FIN' ;
```

## vecoul3D [Fluides Darcy]
```
'OPTION' 'ECHO' 1 ;
'SAUTER' 'PAGE';
'TITRE' 'Vecteurs couleur' ;
OPTI DIME 3 ELEM CUB8 ;
* OPTI ISOV SURFACE ;
OPTI ISOV SULI ;
* OPTI TRAC PSC ;
GRAPH1 = FAUX ;
* CAS TEST : vecoul.dgibi
* --------------------- Création du maillage 3D ---------------------
EPSI1 = 0.0001 ;
* --------------------- Points du plan de base --------------
X1 = 10.0D0 ;
Y1 = 9.0D0 ;
Z1 = 13.5D0 ;
A1 = 2D0 0.0D0 0.0D0 ;
B1 = X1 0.0D0 0.0D0 ;
C1 = X1 Y1 0.0D0 ;
D1 = 0.0D0 Y1 0.0D0 ;
* --------------------- Lignes du plan de base --------------
* -- Densites --
NIV1 = 1.0 ;
NBX1 = ENTIER (NIV1 * 5) ;
NBY1 = ENTIER (NIV1 * 8) ;
NBZ1 = ENTIER (NIV1 * 6) ;
LG1 = DROIT NBX1 A1 B1 ;
LG2 = DROIT NBY1 B1 C1 ;
LG3 = DROIT NBX1 C1 D1 ;
LG4 = DROIT NBY1 D1 A1 ;
* ----------------------- Surface plan de base --------------
GP1 = DALLER LG1 LG2 LG3 LG4 ;
* ------------------------------- Volume --------------------
VD1 = 0.0D0 0.0D0 Z1 ;
GP2 = GP1 PLUS VD1 ;
MASSIF0 = COUL BLEU (GP1 VOLU NBZ1 GP2) ;
SI GRAPH1 ;
   TRAC CACH MASSIF0 ;
FINSI ;
* -- MAILLAGES QUAF --
QFTOT = CHANGE MASSIF0 QUAF ;
* -- MODELE --
MODHYB = MODE QFTOT 'DARCY' 'ANISOTROPE' ;
XXC YYC ZZC = 'COOR' (DOMA MODHYB 'CENTRE') ;
* -- Vecteur de base --
CH1 = (NOMC 'VX' (2.0*XXC)) ET (NOMC 'VY' YYC) ET (NOMC 'VZ' ZZC) ;
CH2 = 1.0D+11 * CH1 ;
VECT1 = VECT CH2 VX VY VZ ROUG ;
AFTOT = 'ARETE' QFTOT ;
SI GRAPH1 ;
   TRAC VECT1 QFTOT AFTOT ;
FINSI ;
AMPL2 = 0.61224E-12 ;
VCTOT1 = @VECOUL AMPL2 CH2 ;
SI GRAPH1 ;
   TRAC VCTOT1 QFTOT AFTOT ;
FINSI ;
VCTOT1 = @VECOUL AMPL2 CH2 0.34 ;
SI GRAPH1 ;
   TRAC VCTOT1 QFTOT AFTOT ;
FINSI ;
VCTOT1 = @VECOUL AMPL2 CH2 'ALTR' 0.34 ;
SI GRAPH1 ;
   TRAC VCTOT1 QFTOT AFTOT ;
FINSI ;
LMOT = 'MOTS' 'VX' 'VY' 'VZ' ;
VCTOT1 = @VECOUL AMPL2 ('*' CH2 0.) LMOT -1. ;
SI GRAPH1 ;
   TRAC VCTOT1 QFTOT AFTOT ;
FINSI ;
FIN ;
```

## lapn [Fluides Euler]
```
* CALCUL DU LAPLACIAN EN VF
* LAPL(T)=0
* On controlle que l'algorithme est lineaire exact
* A. BECCANTINI LTMF JUILLET 2001
 'OPTION' 'DIME' 2
           'ISOV' 'SULI' 'TRAC' 'X'
           'ELEM' 'QUA4' 'ECHO' 0 ;
 GRAPH = FAUX ;
* GRAPH = VRAI ;
* Domaine
 A1 = 0.0 0.0 ;
 A2 = 1.0 0.0 ;
 A3 = 1.0 1.0 ;
 A4 = 0.0 1.0 ;
 A1A2 = A1 'DROIT' 4 A2 ;
 A2A3 = A2 'DROIT' 5 A3 ;
 A3A4 = A3 'DROIT' 6 A4 ;
 A4A1 = A4 'DROIT' 5 A1 ;
 DOMCON = A1A2 'ET' A2A3 'ET' A3A4 'ET'
          A4A1 ;
 DOMTOT = 'SURF' DOMCON 'PLAN' ;
* L'objet modele Euler
 $DOMTOT = 'MODELISER' DOMTOT 'EULER';
 $DOMCON = 'MODELISER' DOMCON 'EULER';
 $A1A2 = 'MODELISER' A1A2 'EULER';
 $A2A3 = 'MODELISER' A2A3 'EULER';
 $A3A4 = 'MODELISER' A3A4 'EULER';
 $A4A1 = 'MODELISER' A4A1 'EULER';
 TDOMTOT = 'DOMA' $DOMTOT 'VF';
 TDOMCON = 'DOMA' $DOMCON 'VF';
 TA1A2 = 'DOMA' $A1A2 'VF';
 TA2A3 = 'DOMA' $A2A3 'VF';
 TA3A4 = 'DOMA' $A3A4 'VF';
 TA4A1 = 'DOMA' $A4A1 'VF';
 MDOMCON = TDOMCON . 'QUAF' ;
 MA1A2 = TA1A2 . 'QUAF' ;
 MA2A3 = TA2A3 . 'QUAF' ;
 MA3A4 = TA3A4 . 'QUAF' ;
 MA4A1 = TA4A1 . 'QUAF' ;
* old stuff $DOMTOT = 'DOMA' DOMTOT ;
 MDOMTOT = TDOMTOT . 'QUAF' ;
 'ELIMINATION' (MDOMTOT ET MDOMCON) 0.0001 ;
 'ELIMINATION' (MDOMTOT ET MA1A2) 0.0001 ;
 'ELIMINATION' (MDOMTOT ET MA2A3) 0.0001 ;
 'ELIMINATION' (MDOMTOT ET MA3A4) 0.0001 ;
 'ELIMINATION' (MDOMTOT ET MA4A1) 0.0001 ;
* Conditions initiales et aux
* limites
* A4 - A3
* A1 - A2
* TEST1
* Champ lineaire
* Conditions aux limites de type Dirichlet
 XXLIM YYLIM = 'COORDONNEE' DOMCON ;
 ACOEF = 1.0 ;
 BCOEF = 7.0 ;
 TLIM = (ACOEF '*' XXLIM) '+' (BCOEF '*' YYLIM) ;
 XXCEN YYCEN = 'COORDONNEE' ('DOMA' $DOMTOT 'CENTRE') ;
 TN = (ACOEF '*' XXCEN) '+' (BCOEF '*' YYCEN) ;
* Graphique des c.i.
 MOD1 = 'MODELISER' ('DOMA' $DOMTOT 'MAILLAGE') 'THERMIQUE' ;
 'SI' GRAPH ;
    CHM_TN = 'KCHA' $DOMTOT 'CHAM' TN ;
    'TRAC' CHM_TN MOD1 'TITR' ('CHAINE' 'TN at t= ' 0.0);
 'FINSI' ;
* Solutions
 GRADTN MCHAM = 'PENT' $DOMTOT 'FACE' 'DIAMANT'
          TN 'CLIM' TLIM ;
* Le reste ne serve pas, mais il faut l'initialiser
 MU = 0.0 ;
 CV = 1.0 ;
 KAPPA = 1.0 ;
 RN = 'MANUEL' 'CHPO' ('DOMA' $DOMTOT 'CENTRE') 1 'SCAL' 1.0 ;
 VN = 'MANUEL' 'CHPO' ('DOMA' $DOMTOT 'CENTRE') 2 'UX' 0.0 'UY' 0.0 ;
 GRADVN = 'MANUEL' 'CHPO' ('DOMA' $DOMTOT 'FACE') 4
      'P1DX' 0.0 'P1DY' 0.0
      'P2DX' 0.0 'P2DY' 0.0 ;
 LINC = 'MOTS' 'RN' 'UX' 'UY' 'TN' ;
* Le calcul
 IJACO IRESI1 DT = 'LAPN' 'VF' 'PROPCOST' 'RESI' 'EXPL'
    $DOMTOT MU KAPPA CV RN VN TN GRADVN GRADTN
      LINC ;
 'SI' (('MAXIMUM' IRESI1 'ABS') '>' 1.0D-5) ;
    'MESSAGE' 'Probleme 1' ;
    'ERREUR' 5 ;
 'FINSI' ;
* TEST 2
* Champ lineaire
* Condition limite de type Neumann
 QLIM = (-1.0 '*' KAPPA) '*'
  ('MANUEL' 'CHPO' ('DOMA' $DOMCON 'CENTRE') 2 'UX' ACOEF 'UY' BCOEF);
 GRADTN MCHAM = 'PENT' $DOMTOT 'FACE' 'DIAMANT'
          TN ;
 IJACO IRESI1 DT = 'LAPN' 'VF' 'PROPCOST' 'RESI' 'EXPL'
    $DOMTOT MU KAPPA CV RN VN TN GRADVN GRADTN
      LINC 'QIMP' QLIM ;
 'SI' (('MAXIMUM' IRESI1 'ABS') '>' 1.0D-5) ;
    'MESSAGE' 'Probleme 1' ;
    'ERREUR' 5 ;
 'FINSI' ;
 'FIN' ;
```

## cyltest6 [Fluides Non Stationnaire]
```
'OPTI' 'ECHO' 0 ;
* Ecoulement autour d'un cylindre circulaire
* Résolution des équations de Navier Stokes laminaires instationnaires
* Pompé sur cyltest.dgibi
* Ajouts Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* en date du 20/12/2007
* teste une méthode couplée et une méthode de projection
* algébrique incrémentale : vérification du bilan des forces
* locales et de la force s'exercant sur le cylindre
'SAUTER' 2 'LIGNE' ;
'MESSAGE' ' Execution de cyltest6.dgibi' ;
'SAUTER' 2 'LIGNE' ;
interact = FAUX ;
graph = FAUX ;
* Procedure tracvit
'DEBPROC' TRACVIT;
'ARGUMENT' RVX*'TABLE';
rv = rvx . 'EQEX' ;
umax = 2. ;
CHUN = 'VECTEUR' (rv.inco.un) (1. '/' (1. * umax)) UX UY JAUN;
'TRACER' CHUN mt cmt 'TITRE' 'Champ de vitesse'
         'NCLK' ;
as2 ama1 = 'KOPS' 'MATRIK';
'RESPRO' as2 ama1;
'FINP';
* Proc Bloc de pression nul
 'DEBPROC' BLOCPNUL ;
 'ARGUMENT' rvx*'TABLE' ;
 RV = RVX . 'EQEX';
 'SI' ('NON' ('EXISTE' rv 'MATPNULL')) ;
* Creation d'un bloc de pression nulle
   'MESSAGE' ('CHAINE' 'Calcul du bloc de pression') ;
   $mt = rvx . 'DOMZ' ;
   rt = 'EQEX' 'OPTI' 'EF' 'IMPL' 'CENTREE' 'CENTREP1'
               'ZONE' $mt
               'OPER' 'KMAB' 0. 'INCO' 'UN' 'PN' ;
   Rt.'INCO' = RV . 'INCO' ;
   smbb matb = kmab rt . '1KMAB' ;
   chpv = 'KCHT' $mt 'VECT' 'SOMMET' 'COMP' '1UN' '2UN' (0. 0.) ;
   matpres = 'KOPS' 'CMCT' matb chpv matb ;
   rv . 'MATPNULL' = matpres ;
 'SINON' ;
   matpres =rv . 'MATPNULL' ;
 'FINSI' ;
 smbvide matvide = 'KOPS' 'MATRIK' ;
'FINPROC' smbvide matpres ;
* Options globales
'OPTION' 'DIME' 2 'ELEM' 'QUA4' 'ECHO' 0 ;
'SI' interact ;
   'OPTION' 'TRAC' 'X' ;
'SINON' ;
   'OPTION' 'TRAC' 'PSC';
'FINSI' ;
'OPTION' isov suli;
disv = 'QUAF' ;
DISP = 'CENTREP1';
* iraff : raffinement du maillage
* mproj : méthode de projection ou couplée
* miter : méthode itérative ou directe
iraff = 1 ;
impkres = 0 ;
lok = VRAI ;
'REPETER' imet 6 ;
   'SAUTER' 1 'LIGN' ;
   iimet = &imet ;
   'SI' ('EGA' iimet 1) ;
      mproj = FAUX ;
      miter = FAUX ;
   'FINSI' ;
   'SI' ('EGA' iimet 2) ;
      mproj = FAUX ;
      miter = VRAI ;
   'FINSI' ;
   'SI' ('EGA' iimet 3) ;
      mproj = VRAI ; lprec = FAUX ;
      miter = FAUX ;
   'FINSI' ;
   'SI' ('EGA' iimet 4) ;
      mproj = VRAI ; lprec = FAUX ;
      miter = VRAI ;
   'FINSI' ;
   'SI' ('EGA' iimet 5) ;
      mproj = VRAI ; lprec = VRAI ;
      miter = FAUX ;
   'FINSI' ;
   'SI' ('EGA' iimet 6) ;
      mproj = VRAI ; lprec = VRAI ;
      miter = VRAI ;
   'FINSI' ;
   'SI' mproj ;
      'SI' lprec ;
         'MESSAGE' 'Methode projection preconditionnee' ;
      'SINON' ;
         'MESSAGE' 'Methode projection' ;
      'FINSI' ;
   'SINON' ;
      'MESSAGE' 'Methode directe' ;
   'FINSI' ;
   'SI' miter ;
      'MESSAGE' 'Solveur itératif' ;
   'SINON' ;
      'MESSAGE' 'Solveur direct' ;
   'FINSI' ;
   'SAUTER' 1 'LIGN' ;
* Construction du maillage:
* Construction des points:
nc = 8 ;
nx = 22 ; ny = 12 ;
nc = '*' nc iraff ;
nx = '*' nx iraff ;
ny = '*' ny iraff ;
p0 = 0. 0. ;
p1 = 0.5 0. ;
p2 = 0. 0.5 ;
p3 = -0.5 0. ;
p4 = 0. -0.5 ;
c1 = 'CERCLE' nc p1 p0 p2 ;
c2 = 'CERCLE' nc p2 p0 p3 ;
c3 = 'CERCLE' nc p3 p0 p4 ;
c4 = 'CERCLE' nc p4 p0 p1 ;
ligc = c1 'ET' c2 'ET' c3 'ET' c4 ;
ligc = 'INVERSE' ligc ;
pA = -6. -6. ;
pB = 15. -6. ;
pC = 15. 6. ;
pD = -6. 6. ;
bas = pA 'DROIT' nx pB ;
dro = pB 'DROIT' ny pC ;
hau = pC 'DROIT' nx pD ;
gau = pD 'DROIT' ny pA ;
lige = bas 'ET' dro 'ET' hau 'ET' gau ;
cntt = ligc 'ET' lige ;
mt = tria cntt ;
xmt ymt = 'COORDONNEE' mt ;
rmt = '**' ('+' ('**' xmt 2) ('**' ymt 2)) 0.5D0 ;
* rmt = '*' rmt 3. ;
rmt = '/' rmt 3. ;
rmt = '/' rmt iraff ;
mtr = 'RAFT' rmt mt ;
'SI' graph ;
   'TRACER' mtr 'TITR' ('CHAINE' 'nbl=' ('NBEL' mtr)) ;
'FINSI' ;
* 'OPTION' 'DONN' 5 ;
cercle = ligc ;
* Création du domaine total:
mt = mtr;
cmt = 'CONTOUR' mt;
* Changement des éléments du maillage en QUAF:
_mt = 'CHANGER' mt 'QUAF';
_cmt = 'CHANGER' cmt 'QUAF';
_cercle = 'CHANGER' cercle 'QUAF';
_entree = 'CHANGER' gau 'QUAF';
_sortie = 'CHANGER' dro 'QUAF';
_hau = 'CHANGER' hau 'QUAF';
_bas = 'CHANGER' bas 'QUAF';
'ELIM' 1.E-5 (_mt et _cercle et _entree 'ET' _sortie
              'ET' _cmt 'ET' _hau 'ET' _bas);
NN = 'NBEL' mt;
'MESSAGE' 'Nombre d éléments du maillage' NN;
* Formulation du domaine Navier Stokes:
$mt = 'MODE' _mt 'NAVIER_STOKES' disv ;
$cmt = 'MODE' _cmt 'NAVIER_STOKES' disv ;
$cercle = 'MODE' _cercle 'NAVIER_STOKES' disv ;
$entree = 'MODE' _entree 'NAVIER_STOKES' disv ;
$sortie = 'MODE' _sortie 'NAVIER_STOKES' disv ;
$hau = 'MODE' _hau 'NAVIER_STOKES' disv ;
$bas = 'MODE' _bas 'NAVIER_STOKES' disv ;
mt = 'DOMA' $mt 'MAILLAGE' ;
cmt = 'DOMA' $cmt 'MAILLAGE' ;
cercle = 'DOMA' $cercle 'MAILLAGE' ;
entree = 'DOMA' $entree 'MAILLAGE' ;
sortie = 'DOMA' $sortie 'MAILLAGE' ;
hau = 'DOMA' $hau 'MAILLAGE' ;
bas = 'DOMA' $bas 'MAILLAGE' ;
* Création des tables de résolution:
dt = .5D0 ;
* rey = 30. ;
rey = 100.;
nu = 1./rey;
arelax = 1.;
niter = 6 ;
nitime = 3 ;
RV = 'EQEX' 'OMEGA' 1.0 'NITER' niter 'ITMA' 1 'FIDT' 1 ;
RV = 'EQEX' RV
       'OPTI' 'EF' 'CENTREE' 'IMPL'
* 'ZONE' $mt 'OPER' 'NS' 'INV_RE' 'INCO' 'UN'
       'ZONE' $mt 'OPER' 'KONV' 1. 'UN' 'INV_RE' 'INCO' 'UN'
       'OPTI' 'EF' 'CENTREE' 'IMPL'
       'ZONE' $mt 'OPER' 'LAPN' 'INV_RE' 'INCO' 'UN'
       'OPTI' 'EF' 'CENTREE' 'IMPL'
       'ZONE' $mt 'OPER' 'DFDT' 1. 'UNM' 'DT' 'INCO' 'UN'
      'OPTI' 'EF' 'IMPL' 'CENTREE' DISP
      'ZONE' $mt
      'OPER' 'KBBT' 1. 'INCO' 'UN' 'PN' ;
'SI' graph ;
   rv = 'EQEX' rv
     'ZONE' $mt 'OPER' TRACVIT ;
'FINSI' ;
* Implantation des conditions aux limites:
RV = 'EQEX' RV
      'CLIM' 'UN' 'UIMP' cercle 0. 'UN' 'VIMP' cercle 0.
             'UN' 'UIMP' entree 1. 'UN' 'VIMP' entree 0.
             'UN' 'VIMP' hau 0.
             'UN' 'VIMP' bas 0. ;
* Choix de la méthode de résolution (couplée, projection)
* et des solveurs (direct, itératif)
'SI' ('NON' mproj) ;
* Solveur pour le système vitesse-pression
   rvm = rv . 'METHINV' ;
   rvm . 'SCALING' = 1 ;
   rvm . 'IMPINV' = impkres ;
   'SI' ('NON' miter) ;
      rvm . 'TYPINV' = 1 ;
   'SINON' ;
* On rajoute le bloc de pression nul
      rv = 'EQEX' rv 'ZONE' $mt 'OPER' BLOCPNUL ;
      rvm . 'TYPINV' = 4 ;
      rvm . 'LBCG' = 2 ;
      rvm . 'PRECOND' = 5 ;
      rvm . 'ILUTLFIL' = 3.D0 ;
   'FINSI' ;
'SINON' ;
   rv . 'GPROJ' = 'TABLE' ;
   rv . 'GPROJ' . 'NOMVIT' = 'UN' ;
   rv . 'GPROJ' . 'NOMPRES' = 'PN' ;
   'SI' ('NON' lprec) ;
      rv . 'GPROJ' . 'NOPREC' = VRAI ;
   'FINSI' ;
* Solveur pour les composantes de la vitesse
   rvm = rv . 'METHINV' ;
   rvm . 'SCALING' = 1 ;
   rvm . 'IMPINV' = impkres ;
   'SI' ('NON' miter) ;
      rvm . 'TYPINV' = 1 ;
   'SINON' ;
      rvm . 'TYPINV' = 4 ;
      rvm . 'LBCG' = 2 ;
      rvm . 'PRECOND' = 3 ;
   'FINSI' ;
* Solveur pour l'équation de pression
   rv . 'GPROJ'. 'METHINV' = 'TABLE' 'METHINV' ;
   rvgm = rv . 'GPROJ' . 'METHINV' ;
   rvgm . 'SCALING' = 1 ;
   rvgm . 'IMPINV' = impkres ;
   'SI' ('NON' miter) ;
      rvgm . 'TYPINV' = 1 ;
   'SINON' ;
      rvgm . 'TYPINV' = 4 ;
      rvgm . 'LBCG' = 2 ;
      rvgm . 'PRECOND' = 3 ;
* rvgm . 'PRECOND' = 5 ;
* rvgm . 'ILUTLFIL' = 1.D0 ;
   'FINSI' ;
'FINSI' ;
* Création de la table des inconnues et initialisation:
RV.INCO = 'TABLE' INCO;
RV.INCO.'UN' = 'KCHT' $mt 'VECT' 'SOMMET' (1.E-3 1.E-3);
RV.INCO.'UNM' = 'KCHT' $mt 'VECT' 'SOMMET' (1.E-3 1.E-3);
rv . 'INCO' . 'G' = (0. -9.8) ;
RV.INCO.'DT' = dt ;
RV.INCO.'INV_RE'= nu;
RV.INCO.'PN' = 'KCHT' $mt 'SCAL' DISP 0.;
* Table avec les résultats en vitesse
res = 'TABLE' ;
itres = 0 ;
res . itres = 'COPIER' (RV.INCO.'UN') ;
* Boucle en temps faite main
'TEMPS' 'ZERO' ;
'REPETER' iitime nitime ;
   rv . 'INCO' . 'UNM' = 'COPIER' (res . itres) ;
   EXEC RV;
   itres = '+' itres 1 ;
   res . itres = 'COPIER' (RV.INCO.'UN') ;
'FIN' iitime ;
TABTPS = TEMP 'NOEC';
tcpu = TABTPS.'TEMPS_CPU'.'INITIAL' ;
lastime = '-' ('DIME' res) 1 ;
vit = res . lastime ;
vitm1 = res . ('-' lastime 1) ;
umax = 2. ;
* Créer les matrices
bidon matkon = 'KONV' (rv . '1KONV') ;
bidon matlap = 'LAPN' (rv . '2LAPN') ;
chdfdt matdfdt = 'DFDT' (rv . '3DFDT') ;
rt = 'EQEX' 'ZONE' $mt
      'OPTI' 'EF' 'IMPL' 'CENTREE' DISP
      'OPER' 'KMBT' -1. 'INCO' 'PN' 'UN'
        ;
rt.'INCO' = rv . 'INCO' ;
bidon matgrp = 'KMBT' (rt . '1KMBT') ;
pre = rv . 'INCO' . 'PN' ;
nomavv = 'MOTS' 'UX' 'UY' ;
nomapv = 'MOTS' '1UN' '2UN' ;
nomavp = 'MOTS' 'SCAL' ;
nomapp = 'MOTS' 'PN' ;
vit = 'NOMC' nomavv nomapv vit ;
vitm1 = 'NOMC' nomavv nomapv vitm1 ;
pre = 'NOMC' nomavp nomapp pre ;
forlap = 'KOPS' matlap '*' vit ;
forkon = 'KOPS' matkon '*' vit ;
forgrp = 'KOPS' matgrp '*' pre ;
fordfdt = 'KOPS' matdfdt '*' ('-' vit vitm1) ;
forlap = ('NOMC' nomapv nomavv forlap) ;
forkon = ('NOMC' nomapv nomavv forkon) ;
forgrp = ('NOMC' nomapv nomavv forgrp) ;
fordfdt = ('NOMC' nomapv nomavv fordfdt) ;
fort = forlap '+' forkon '+' forgrp '+' fordfdt ;
fmax = 'MAXIMUM' fort 'ABS' ;
echf = '/' 0.5 fmax ;
vlap = 'VECTEUR' forlap echf UX UY VERT ;
vkon = 'VECTEUR' forkon echf UX UY ROUG ;
vgrp = 'VECTEUR' forgrp echf UX UY JAUN ;
vdfdt = 'VECTEUR' fordfdt echf UX UY TURQ ;
vf = 'VECTEUR' fort echf UX UY BLAN ;
vtot = vlap 'ET' vkon 'ET' vgrp 'ET' vdfdt 'ET' vf ;
'SI' graph ;
tit = 'CHAINE' 'vert=lap;roug=kon;jaun=grp;turq=dfdt;blan=reac;fmax='
                fmax ;
'TRACER' vtot _mt ('CONTOUR' _mt) 'TITRE' tit ;
'FINSI' ;
pmt = 'CHANGER' mt 'POI1' ;
pcmt = 'CHANGER' cmt 'POI1' ;
pint = 'DIFF' pmt pcmt ;
fortint = 'REDU' fort pint ;
fmaxint = 'MAXIMUM' fortint 'ABS' ;
'MESSAGE' ('CHAINE' 'fmax=' fmax) ;
'MESSAGE' ('CHAINE' 'fmaxint=' fmaxint) ;
errbf = '*' ('/' fmaxint fmax) 100. ;
'MESSAGE' ('CHAINE' 'erreur bilan forces =' errbf ' %') ;
forcer = 'REDU' fort cercle ;
rfor = 'RESULT' forcer ;
'MESSAGE' 'Resultante des forces sur le cylindre' ;
rfx = 'MAXIMUM' ('EXCO' 'UX' rfor) ;
rfy = 'MAXIMUM' ('EXCO' 'UY' rfor) ;
'MESSAGE' ('CHAINE' '  en x =' rfx) ;
'MESSAGE' ('CHAINE' '  en y =' rfy) ;
'MESSAGE' ('CHAINE' 'tcpu=' tcpu) ;
* Tests
* Erreur sur le bilan des forces au 16/04/2010
* 2.e-3 % pour la méthode directe
* 7 % pour la méthode projection algébrique
* 1 % pour la méthode double projection algébrique
* Valeur de la force de trainée (fx)
* -6.94e-1 pour la méthode directe
* -6.76e-1 pour la méthode projection algébrique
* -6.93e-1 pour la méthode double projection algébrique
'SI' mproj ;
* vrbf = 8. ;
   vrbf = 2. ;
'SINON' ;
   vrbf = 5.D-3 ;
'FINSI' ;
* vrft = -6.9e-1 ;
* tol = 0.3e-1 ;
vrft = -6.94e-1 ;
tol = 0.02e-1 ;
tst = '<' errbf vrbf ;
'SI' ('NON' tst) ;
   cherr = 'CHAINE' '!!! Erreur bilan force > ' vrbf ' %' ;
   'MESSAGE' cherr ;
'FINSI' ;
lok = lok 'ET' tst ;
tst = '<' ('ABS' ('-' rfx vrft)) tol ;
'SI' ('NON' tst) ;
   cherr = 'CHAINE' '!!! Erreur force trainee <> ' vrft ' a ' tol
    ' pres' ;
   'MESSAGE' cherr ;
'FINSI' ;
lok = lok 'ET' tst ;
'FIN' imet ;
'SAUTER' 2 'LIGNE' ;
'SI' lok ;
   'MESSAGE' 'Tout sest bien passe' ;
'SINON' ;
   'MESSAGE' 'Il y a eu des erreurs' ;
'FINSI' ;
'SAUTER' 2 'LIGNE' ;
'SI' interact ;
   'OPTION' 'DONN' 5 'ECHO' 1 ;
'FINSI' ;
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'FINSI' ;
* 'FIN' du jeu de données.
fin;
```

## cd_clim [Fluides Permanent]
```
* NOM : CD_CLIM
* DESCRIPTION : Calcul d'un problème de convection-diffusion illustrant
* l'importance de l'intégration par parties sur les
* conditions aux limites.
* 2D Convection-diffusion problem with a focus on the
* integration by parts' influence on the boundary
* conditions.
* + interactive GUI (interact = vrai)
* + slide generation for the lecture notes (transp = vrai)
* See:
* ENSTA Lecture Notes 2021
* Introduction to the finite element method applied to
* incompressible fluid mechanics (in english)
* Introduction a la methode des elements finis en
* mecanique des fluides incompressibles (en francais)
* Stephane GOUNAND and Sergey KUDRIAKOV
* http://www-cast3m.cea.fr/index.php?xml=supportcours
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 25/09/2007, version initiale
* HISTORIQUE : v1, 25/09/2007, création
'OPTION' 'DIME' 2 ;
interact = FAUX ;
transp = VRAI ;
'DEBPROC' CALCUL ;
'ARGUMENT' ikonv*'ENTIER' ;
'ARGUMENT' iPe*'ENTIER' ;
'ARGUMENT' isupg*'ENTIER' ;
'ARGUMENT' itrac*'ENTIER' ;
'ARGUMENT' lnclk/'LOGIQUE' ;
'SI' ('NON' ('EXISTE' lnclk)) ;
   lnclk = FAUX ;
'FINSI' ;
'OPTI' 'ELEM' 'QUA4' ;
nmail = 10 ;
kvit = 'LINE' ;
lPe = 'PROG' 1. 10. 20. 50. 100. ;
Pe = 'EXTRAIRE' lPe iPe ;
'SI' ('EGA' ikonv 1) ;
   mkonv = 'NOCONS' ;
'SINON' ;
   mkonv = 'CONS' ;
'FINSI' ;
'SI' ('EGA' isupg 1) ;
   msupg = 'CENTREE' ;
   niter = 1 ;
   omega = 1. ;
'FINSI' ;
'SI' ('EGA' isupg 2) ;
   msupg = 'SUPG' ;
   niter = 1 ;
   omega = 1. ;
'FINSI' ;
'SI' ('EGA' isupg 3) ;
   msupg = 'SUPGDC' ;
   niter = 10 ;
   omega = 0.7 ;
'FINSI' ;
* Maillage (Mesh)
p0 = 0. 0. ; p1 = 1. 0. ;
lt = 'DROIT' nmail p0 p1 ;
mt = 'TRANSLATION' lt nmail (0. 1.) ;
* mt = 'TRANSLATION' lt nmail (0. iang) ;
cmt = 'CONTOUR' mt ;
bas dro hau gau = 'COTE' mt ;
hau = 'INVERSE' hau ;
_bas = 'CHANGER' bas 'QUAF' ; _dro = 'CHANGER' dro 'QUAF' ;
_hau = 'CHANGER' hau 'QUAF' ; _gau = 'CHANGER' gau 'QUAF' ;
_mt = 'CHANGER' mt 'QUAF' ;
'ELIMINATION' (_mt 'ET' _bas 'ET' _gau 'ET' _dro 'ET' _hau) 1.D-6 ;
$mt = 'MODE' _mt 'NAVIER_STOKES' kvit ;
$gau = 'MODE' _gau 'NAVIER_STOKES' kvit ;
$dro = 'MODE' _dro 'NAVIER_STOKES' kvit ;
$hau = 'MODE' _hau 'NAVIER_STOKES' kvit ;
$bas = 'MODE' _bas 'NAVIER_STOKES' kvit ;
mt = 'DOMA' $mt 'MAILLAGE' ; gau = 'DOMA' $gau 'MAILLAGE' ;
dro = 'DOMA' $dro 'MAILLAGE' ; hau = 'DOMA' $hau 'MAILLAGE' ;
bas = 'DOMA' $bas 'MAILLAGE' ;
cmt = bas 'ET' dro 'ET' hau 'ET' gau ;
* Conditions aux limites (Boundary conditions)
mdiri = hau 'ET' gau 'ET' bas ;
* Champ de vitesses (velocity field)
ymt = 'COORDONNEE' 2 mt ;
mymt = '*' ('-' ymt 1.) -1. ;
vvit = 'NOMC' 'UX' (ymt '*' mymt '*' 4.D0) ;
un = 'KCHT' $mt 'VECT' 'SOMMET' vvit ;
* table EQEX (Problem description)
rv = 'EQEX' 'NITER' niter 'OMEGA' omega 'ITMA' 1
     'OPTI' 'EF' 'IMPL' msupg mkonv
     'ZONE' $mt 'OPER' 'KONV' Pe 'UN' 1. 'INCO' 'TN'
     'OPTI' 'EF' 'IMPL' 'CENTREE'
     'ZONE' $mt 'OPER' 'LAPN' 1. 'INCO' 'TN'
     'CLIM' 'TN' 'TIMP' mdiri 1. ;
rv . 'INCO' = 'TABLE' 'INCO' ;
rv . 'INCO' . 'UN' = un ;
rv . 'INCO' . 'TN' = 'KCHT' $mt 'SCAL' 'SOMMET' 0. ;
EXEC rv ;
tn = rv . 'INCO' . 'TN' ;
* Post-traitement (Post-treatment)
'SI' ('EGA' itrac 1) ;
   vun = 'VECT' un 'DEPL' 'JAUN' ;
   'SI' lnclk ;
      'TRACER' tn mt cmt vun 16 'NCLK' ;
   'SINON' ;
      'TRACER' tn mt cmt vun 16 ;
   'FINSI' ;
'FINSI' ;
'SI' ('EGA' itrac 2) ;
   'OPTI' 'DIME' 3 ;
   dep = 'NOMC' 'UZ' tn ;
   dep = '/' dep ('MAXIMUM' dep 'ABS') ;
   oeil = '*' (-2.1 -2.4 2.3) 2. ;
   'FORME' dep ;
   'SI' lnclk ;
      'TRACER' 'CACH' oeil tn mt 16 'NCLK' ;
   'SINON' ;
      'TRACER' 'CACH' oeil tn mt 16 ;
   'FINSI' ;
   'OPTI' 'DIME' 2 ;
'FINSI' ;
'FINPROC' ;
'SI' interact ;
* Table contenant les choix des menus (Menu entries)
tko = 'TABLE' ;
tko . 1 = 'NOCONS' ; tko . 2 = 'CONS' ;
ntko = 'DIME' tko ; itko = 1 ;
tPe = 'TABLE' ;
tPe . 1 = 'Pe=1.' ; tPe . 2 = 'Pe=10.' ; tPe . 3 = 'Pe=20.' ;
tPe . 4 = 'Pe=50' ; tPe . 5 = 'Pe=100' ;
ntPe = 'DIME' tPe ; itPe = 1 ;
tsu = 'TABLE' ;
tsu . 1 = 'CENTREE' ; tsu . 2 = 'SUPG' ; tsu . 3 = 'SUPGDC' ;
ntsu = 'DIME' tsu ; itsu = 1 ;
ttr = 'TABLE' ;
ttr . 1 = '2D' ; ttr . 2 = '3D' ;
nttr = 'DIME' ttr ; ittr = 1 ;
* Boucle d'affichage (Print loop)
'REPETER' bouc ;
   CALCUL itko itPe itsu ittr VRAI ;
   cha = 'CHAINE' 'Convection-diffusion sortie naturelle' ;
   ret = 'MENU' cha (tko . itko) (tPe . itPe) (tsu . itsu)
                    (ttr . ittr) ;
   'SI' ('EGA' ret 'Quitter') ;
      'QUITTER' bouc ;
   'FINSI';
   'SI' ('EGA' ret (tko . itko)) ; itko = '+' itko 1 ; 'FINSI' ;
   'SI' (itko > ntko) ; itko = 1 ; 'FINSI';
   'SI' ('EGA' ret (tPe . itPe)) ; itPe = '+' itPe 1 ; 'FINSI' ;
   'SI' (itPe > ntPe) ; itPe = 1 ; 'FINSI';
   'SI' ('EGA' ret (tsu . itsu)) ; itsu = '+' itsu 1 ; 'FINSI' ;
   'SI' (itsu > ntsu) ; itsu = 1 ; 'FINSI';
   'SI' ('EGA' ret (ttr . ittr)) ; ittr = '+' ittr 1 ; 'FINSI' ;
   'SI' (ittr > nttr) ; ittr = 1 ; 'FINSI';
'FIN' bouc ;
'FINS' ;
* Mes transparents
* Lecture notes slides
'SI' transp ;
'OPTI' 'TRAC' 'PS' 'ISOV' 'SULI' ;
   CALCUL 1 1 1 1 ;
   CALCUL 2 1 1 1 ;
'FINSI' ;
'SI' interact ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
* End of dgibi file CD_CLIM
'FIN' ;
```

## convdif1d [Fluides Permanent]
```
* NOM : CONVDIF1D
* DESCRIPTION : 1D convection-diffusion equation
* See:
* ENSTA Lecture Notes 2021
* Introduction to the finite element method applied to
* incompressible fluid mechanics (in english)
* Introduction a la methode des elements finis en
* mecanique des fluides incompressibles (en francais)
* Stephane GOUNAND and Sergey KUDRIAKOV
* http://www-cast3m.cea.fr/index.php?xml=supportcours
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 03/10/2008, version initiale
* HISTORIQUE : v1, 03/10/2008, création
'OPTION' 'DIME' 2 'ELEM' 'QUA8' ;
graph = FAUX ;
* Exact Solution : (1 - exp (2 Pe x)) / (1 - exp (2 Pe))
'DEBPROC' solex ;
'ARGUMENT' pe*'FLOTTANT' ;
pe2 = '*' pe 2 ;
lx = 'PROG' 0. 'PAS' 1.D-3 1. ;
l1 = 'PROG' ('DIME' lx) * 1. ;
num = '-' l1 ('EXP' ('*' lx pe2)) ;
den = '-' 1. ('EXP' pe2) ;
ly = '/' num den ;
evex = 'EVOL' 'MANU' lx ly ;
'RESPRO' evex ;
'FINPROC' ;
Peclet = 10. ;
* nmail : number of mesh elements
* dmail : refinement factor at the right boundary (>= 1)
* idecent = 1 : centered discretization for the convective term
* idecent = 2 : SUPG numerical diffusion
* cmd : multiplicative coefficient for the SUPG numerical diffusion
* term
nmail = 6 ;
dmail = 1. ;
idecent = 1 ;
cmd = 0.5 ;
* Densities
dmoy = '/' 1. ('FLOTTANT' nmail) ;
dini = '*' dmoy dmail ;
dfin = '/' dmoy dmail ;
* Upwinding
'SI' ('EGA' idecent 1) ;
   typdec = 'CENTREE' ;
   niter = 1 ;
'FINSI' ;
'SI' ('EGA' idecent 2) ;
   typdec = 'SUPG' ;
   niter = 1 ;
'FINSI' ;
* Mesh
p0 = 0. 0. ; p1 = 1. 0. ;
lt = 'DROIT' ('*' nmail -1) p0 p1 'DINI' dini 'DFIN' dfin ;
bas = lt ;
mt = 'TRANSLATION' lt 1 (0. 1.) ;
gau = 'COTE' 4 mt ;
dro = 'COTE' 2 mt ;
_bas = 'CHANGER' bas 'QUAF' ;
_gau = 'CHANGER' gau 'QUAF' ;
_dro = 'CHANGER' dro 'QUAF' ;
_mt = 'CHANGER' mt 'QUAF' ;
'ELIMINATION' (_mt 'ET' _bas 'ET' _gau 'ET' _dro) 1.D-6 ;
$mt = 'MODE' _mt 'NAVIER_STOKES' 'LINE' ;
$bas = 'MODE' _bas 'NAVIER_STOKES' 'LINE' ;
$gau = 'MODE' _gau 'NAVIER_STOKES' 'LINE' ;
$dro = 'MODE' _dro 'NAVIER_STOKES' 'LINE' ;
mt = 'DOMA' $mt 'MAILLAGE' ;
bas = 'DOMA' $bas 'MAILLAGE' ;
gau = 'DOMA' $gau 'MAILLAGE' ;
dro = 'DOMA' $dro 'MAILLAGE' ;
* Problem description
rv = 'EQEX' 'NITER' niter
     'OPTI' 'EF' 'IMPL' typdec 'CMD' cmd
     'ZONE' $mt 'OPER' 'KONV' 1. 'UN' 'ALF' 'INCO' 'TN'
     'OPTI' 'EF' 'IMPL' 'CENTREE'
     'ZONE' $mt 'OPER' 'LAPN' 'ALF' 'INCO' 'TN'
     'CLIM' gau 'TN' 'TIMP' 0.
     'CLIM' dro 'TN' 'TIMP' 1.
      ;
rv . 'INCO' = 'TABLE' 'INCO' ;
rv . 'INCO' . 'UN' = 'KCHT' $mt 'VECT' 'SOMMET' (1. 0.) ;
rv . 'INCO' . 'ALF' = 'KCHT' $mt 'SCAL' 'CENTRE' ('/' 0.5 Peclet) ;
rv . 'INCO' . 'TN' = 'KCHT' $mt 'SCAL' 'SOMMET' 0. ;
EXEC rv ;
* Post treatment
tn = rv . 'INCO' . 'TN' ;
evt = 'EVOL' 'CHPO' tn 'SCAL' bas ;
evx = SOLEX Peclet ;
evtot = evt 'ET' evx ;
tabt = 'TABLE' ; tabt . 'TITRE' = 'TABLE' ;
tabt . 1 = 'CHAINE' 'TIRC MARQ CROI' ;
tabt . 'TITRE' . 1 = 'CHAINE' 'Sol. App.' ;
tabt . 'TITRE' . 2 = 'CHAINE' 'Sol. Exa.' ;
'SI' graph ;
   'DESSIN' evtot 'TITX' 'X' 'TITY' 'T'
          'TITR' ('CHAINE' 'Peclet=' Peclet)
          'LEGE' tabt ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
* End of dgibi file CONVDIF1D
'FIN' ;
```

## tbsrc1 [Fluides Poreux]
```
* $$$ TBSRC1
* Test de non regression
* --- 2 JUIN 1998 ---
* Tube cylindrique Rayon R0=0.25 Longueur L0=16*R0
* test cas isotherme NS,FIMP KBBT en Implicite
* coefficient de FIMP CHPOINT SCAL SOMMET
* porosite u -> alfp*u
GRAPH = 'N' ;
DEBPROC TUBESRC ;
ARGU TYPELT*MOT NH*ENTIER NV*ENTIER GRAPH*MOT KPRESS*MOT
MACRO*MOT SRC*FLOTTANT ;
OPTION DIME 2 ELEM TYPELT ;
 option mode axis ;
r0=0.25 ; L0=16*R0 ;
ae=0. ;
P1=R0 0 ; p2=ae 0 ; p3 = ae (3.*L0/4.) ;
P4 = p3 plus (0 (L0/4));
r1=R0/2. ;
P7= P4 plus (R0 0) ;
* P8=R0 (3.*L0/4.) ;
entree= p1 d nh p2 ;
axe=p2 d nv p4 ;
sortie=p4 d nh p7 ;
paroi=p7 d nv p1 ;
mt= entree axe sortie paroi daller ;
* trace mt ;
ent = chan entree poi1 ;
ent=elem ent (lect 2 pas 1 (nbel ent)) ;
mtq=chan mt quaf ;
entree= chan entree quaf ;
sortie= chan sortie quaf ;
elim (mt et entree et sortie )1.e-5 ;
$mt= mode mtq 'NAVIER_STOKES' MACRO ; doma $mt 'IMPR' ;
NU=1.5E-2;
uE=1. ;
KPRESS='CENTREP1' ;
RU=eqex 'OMEGA' 0.9 'NITER' 5
 'OPTI' 'EF' 'IMPL' 'SUPG' KPRESS
  ZONE $mt OPER KBBT 'ALFP' INCO 'UN' 'PRES'
  ZONE $mt OPER NS 1. 'UN' NU INCO 'UN'
  'OPTI' INCOD KPRESS
  ZONE $mt OPER FIMP 'SRC' INCO 'PRES'
  CLIM
 UN UIMP entree 0. UN VIMP ent UE
 UN UIMP axe 0. UN UIMP paroi 0.
 UN VIMP paroi 0. ;
ru.inco=table 'INCO' ;
ru.'INCO'.'UN'=kcht $mt vect sommet (0. 1. ) ;
ru.'INCO'.'SRC'=kcht $mt scal sommet src ;
ru.'INCO'.'PRES' = kcht $mt scal KPRESS 0. ;
mt=doma $mt maillage;
alfp=0.5*(coor 1 mt) + 1. ;
ru.inco.'ALFP' = kcht $mt scal sommet alfp ;
 exec ru ;
 $entree=mode entree 'NAVIER_STOKES' MACRO ;
 $sortie=mode sortie 'NAVIER_STOKES' MACRO ;
 un=ru.'INCO'.'UN';
 qe=dbit un $entree ;
 qs=dbit un $sortie ;
 si ('EGA' graph 'O' );
 mt=doma $mt 'MAILLAGE' ;
 ung1=vect un 5.e-2 ux uy jaune ;
 trace ung1 mt ;
 pn=elno $mt (ru.'INCO'.'PRES') KPRESS ;
 trace pn mt ;
 srti=doma $sortie 'MAILLAGE' ;
 evolV = EVOL 'CHPO' (ru.'INCO'.'UN') UY (srti ) ;
 TAB1=TABLE;
 TAB1.'TITRE'=TABLE ;
 TAB1 . 1 ='MARQ      REGU ' ;
 TAB1.'TITRE' . 1 = mot 'Composante_UX ' ;
 DESS evolV 'TITX' 'R (m)' 'TITY' 'V (m/s)' LEGE TAB1 ;
 FINSI ;
 V=doma $mt 'VOLUME' ;
 VT=somt V ;
FINPROC RV qe qs vt ;
* QUADRATIQUE CENTREP1 SRCE=-0.1
 nv=15 ; nh= 3 ;
 MACRO= 'QUAF' ;
 kpress='CENTREP1';
 typelt=qua8 ;
 src= 0.1 ;
RV qe qs vt= TUBESRC typelt nh nv graph kpress macro src ;
 dq= (abs qe ) - qs + 6.8298E-03 ;
 mess ' qe ' qe ' qs ' qs ' dq ' dq ;
 mess 'VT= ' vt ' src= ' src ' VT*src= ' (vt*src) ;
 erq=abs (dq-(vt*src));
 err1=8.e-7 ;
 mess ' Erreur sur le debit : dq-vt*src ' (dq-(vt*src)) ;
* Attention sur les bilans effet du parametre de relaxation 0.9
* si ( erq > err1 ) ; erreur 5 ; finsi ;
 err2 =1.e-7 ;
 dq1=dq - 7.85390E-02 ;
 dq1=abs dq1 ;
 mess 'DQ1=' DQ1 ;
* ?*si ( dq1 > err2 ) ; erreur 5 ; finsi ;
FIN ;
```

## vahldavis [Fluides Thermique]
```
* modifie le 15/06/2014 passage EQPR -> EQEX
COMPLET = FAUX ;
SI ( COMPLET ) ;
      d1 = 0.02 ;
      d2 = 0.1;
      NITER = 5000 ;
      CFL = 1.0 ;
SINON ;
      d1 = 0.05 ;
      d2 = 0.5 ;
      NITER = 600 ;
      CFL = 1.0 ;
FINSI ;
GRAPH = FAUX ;
KPRESS='CENTRE';
DISCR ='MACRO';
BETA=1.;
* CAVITE CARREE - VAHL-DAVIS
* A. Chene/H. Paillere TTMF Aout 1997
* ESTIMATION DE LA CONVERGENCE
DEBPROC CALCUL;
ARGU RVX*'TABLE';
RV = RVX.'EQEX';
DD = RV.PASDETPS.'NUPASDT';
NN = DD/5;
LO = (DD-(5*NN)) EGA 0;
SI (LO);
UN = RV.INCO.'UN';
UNM1 = RV.INCO.'UNM1';
unx = kcht $MT scal sommet (exco 'UX' un);
unm1x = kcht $MT scal sommet (exco 'UX' unm1);
uny = kcht $MT scal sommet (exco 'UY' un);
unm1y = kcht $MT scal sommet (exco 'UY' unm1);
ERRX = KOPS unx '-' unm1x;
ERRY = KOPS uny '-' unm1y;
ELIX = MAXI ERRX 'ABS';
ELIY = MAXI ERRY 'ABS';
ELIX = (LOG (ELIX + 1.0E-10))/(LOG 10.);
ELIY = (LOG (ELIY + 1.0E-10))/(LOG 10.);
MESSAGE 'ITER' RV.PASDETPS.'NUPASDT' 'ERREUR LINF' ELIX ELIY;
RV.INCO.'UNM1' = KCHT $MT 'VECT' 'SOMMET' (RV.INCO.'UN');
IT = PROG RV.PASDETPS.'NUPASDT';
ER = PROG ELIY;
RV.INCO.'IT' = (RV.INCO.'IT') ET IT;
RV.INCO.'ER' = (RV.INCO.'ER') ET ER;
FINSI;
as2 ama1 = 'KOPS' 'MATRIK' ;
FINPROC as2 ama1 ;
* MAILLAGE
OPTI DIME 2;
OPTI ELEM QUA8;
p1 = 0. 0.;
p15 = 0.5 0.;
p2 = 1. 0.;
p25 = 1. 0.5;
p3 = 1. 1.;
p35 = 0.5 1.;
p4 = 0. 1.;
p45 = 0. 0.5;
bas = p1 d dini d1 dfin d2 p15 d dini d2 dfin d1 p2;
cdro = p2 d dini d1 dfin d2 p25 d dini d2 dfin d1 p3;
haut = p3 d dini d1 dfin d2 p35 d dini d2 dfin d1 p4;
cgau = p4 d dini d1 dfin d2 p45 d dini d2 dfin d1 p1;
cnt = bas et cdro et haut et cgau;
mt = bas cdro haut cgau daller;
* MODE
Mmt= chan mt quaf ;
$mt = MODE Mmt 'NAVIER_STOKES' DISCR ;
doma $mt 'IMPR' ;
mt = doma $mt 'MAILLAGE' ;
* PARAMETRES
Pr = 0.71;
Ra = 1.e6;
Gr = Ra/Pr;
NU = 1/(Gr**0.5);
ALF= NU/Pr;
gb = 0 -1;
uref = 1;
* CREATION DES TABLES
RV = EQEX $MT 'ITMA' NITER 'ALFA' CFL
 'ZONE' $MT 'OPER' CALCUL
 'OPTI' 'SUPG'
 'ZONE' $MT 'OPER' 'NS' NU GB 'TN' 0.5 'INCO' 'UN'
 'OPTI' 'SUPG' 'MMPG'
 'ZONE' $MT 'OPER' 'TSCAL' ALF 'UN' 0. 'INCO' 'TN'
 'OPTI' 'CENTREE'
  ZONE $MT 'OPER' 'DFDT' 1. 'UN' 'DELTAT' INCO 'UN'
  ZONE $MT 'OPER' 'DFDT' 1. 'TN' 'DELTAT' INCO 'TN'
;
RV = EQEX RV
 'CLIM' 'UN' 'UIMP' cnt 0.
        'UN' 'VIMP' cnt 0.
        'TN' 'TIMP' cgau 1.
        'TN' 'TIMP' cdro 0.;
RVP = EQEX 'OPTI' 'EF' KPRESS
 'ZONE' $MT OPER KBBT -1. beta INCO 'UN' 'PRES'
;
    rvp.'METHINV'.TYPINV=1 ;
    rvp.'METHINV'.IMPINV=0 ;
    rvp.'METHINV'.NITMAX=300;
    rvp.'METHINV'.PRECOND=3 ;
    rvp.'METHINV'.RESID =1.e-8 ;
    rvp.'METHINV' . 'FCPRECT'=100 ;
    rvp.'METHINV' . 'FCPRECI'=100 ;
  RV.'PROJ' =RVP ;
 RV.INCO = TABLE INCO;
 RV.INCO.'UN' = kcht $MT VECT SOMMET (0. 0.);
 RV.INCO.'PRES'= kcht $MT SCAL KPRESS 0.;
 corx = coor 1 mt;
 RV.INCO.'TN' = kcht $MT SCAL SOMMET (1.-corx);
 RV.INCO.'UNM1' = kcht $MT VECT SOMMET (1.E-5 1.E-5);
 RV.INCO.'IT' = PROG 1;
 RV.INCO.'ER' = PROG 0.;
EXEC RV;
* RESULTATS
Mcdro=chan cdro quaf ;
elim (mt et cdro) 1.e-3 ;
$cdro = mode Mcdro 'NAVIER_STOKES' DISCR;
DY = DOMA $cdro 'VOLUME';
DYT = SOMT DY;
elim (Mmt et Mcdro)1.e-3;
GRADT = KOPS RV.INCO.'TN' 'GRAD' $MT;
DTDX = KCHT $MT 'SCAL' 'CENTRE' (EXCO 'UX' GRADT);
DTDX = ELNO $MT DTDX;
DTDXp = KCHT $CDRO 'SCAL' 'SOMMET' DTDX;
DTDXp = KOPS DTDXp '*' (-1.);
EVOL1 = EVOL 'CHPO' DTDXp SCAL CDRO;
EVOL1 = EVOL1 COUL ROUG ;
DTDXpc = NOEL $CDRO DTDXp;
num = KOPS DTDXpc '*' DY;
num = SOMT NUM;
num = (-1)*NUM/DYT;
MESSAGE 'NUSSELT MOYEN' NUM;
MESSAGE 'NUSSELT MAX' (MAXI DTDXpc);
MESSAGE 'NUSSELT MIN' (MINI DTDXpc);
SI ( (MAXI DTDXp) < 12.00 ) ;
        ERREUR 5 ;
FINSI ;
SI ( ABS (NUM) < 7.55 ) ;
        ERREUR 5 ;
FINSI ;
SI ( (MINI RV.INCO.'ER') > -4.95 ) ;
        ERREUR 5 ;
FINSI ;
SI ( GRAPH ) ;
OPTI ISOV SULI;
trace mt 'TITR' 'MAILLAGE' ;
trac RV.INCO.'TN' mt (cont mt) 14 'TITR' 'TEMPERATURE' ;
unch = vect RV.INCO.'UN' 1. UX UY JAUNE;
trace unch mt (cont mt) 'TITR' 'CHAMP DE VITESSE' ;
EVOL4 = EVOL 'MANU' 'ITERATIONS' (RV.INCO.'IT') 'LOG|E|inf'
     (RV.INCO.'ER') ;
dess EVOL4 'XBOR' 0. 10000. 'YBOR' -10.0 0.0
        'TITR' 'CONVERGENCE VERS LE STATIONNAIRE' ;
TAB1 = TABLE ;
TAB1.1 = 'MARQ LOSA';
DESS EVOL1 'XBOR' 0. 1. 'GRIL' TAB1 'TITR' 'NUSSELT A LA PAROI' ;
un = RV.INCO.'UN';
un2=KOPS un '*' (Pr*(Gr**0.5));
sw = (-1.) * (KOPS un 'ROT' $mt) ;
rk = EQEX $mt 'OPTI' 'EF' 'IMPL'
ZONE $mt OPER LAPN 1. INCO 'PSI'
ZONE $mt OPER FIMP sw INCO 'PSI'
'CLIM' 'PSI' 'TIMP' (cgau et haut et bas et cdro) 0.;
rk.'INCO'=table 'INCO' ;
rk.'INCO'.'PSI'=kcht $mt scal sommet 0. ;
EXEC rk ;
psi=rk.'INCO'.'PSI';
psi2=kops psi '*' (Pr*(Gr**0.5)) ;
LISTE (MAXI PSI) ;
LISTE (MINI PSI) ;
trac psi mt CNT 14 'TITR' 'FONCTION DE COURANT' ;
FINSI ;
FIN ;
```

## aerosol3 [Fluides Transitoire]
```
GRAPH = FAUX ;
* AEROSOL3.DGIBI
* Exemple d'utilisation des FONCTIONS DE PAROI AEROSOL LAMINAIRES.
* Ce jeu de données teste les operateurs TSCA, ECHI, KUET et FPAL.
* On résoud une équation de transport de particules dans un
* ecoulement 2D plan de Poiseuille donne, avec dépot en paroi.
* resolution semi-implicite d'une equation de concentration avec
* depot d'aérosols en paroi
* P. CORNET SEMT/TTMF DECEMBRE 1997
* ------------------------- maillage ------------------------------------
TITRE 'MAILLAGE POUR DEPOT PAR DIFFUSION' ;
OPTIO DIME 2 ELEM QUA4 ;
L = 1. ;
H = 0.1 ;
nx = 30 ;
nz = 10 ;
E = H/nx ;
* POINTS :
PA1 = 0. 0. ;
PA2 = 0. (E-h) ;
PA3 = 0. (0.-H);
PB1 = L 0. ;
PB2 = L (e-h) ;
PB3 = L (0.-H);
PC1 = (L/2.) 0. ;
PC2 = (L/2.) (e-h) ;
PC3 = (L/2.) (0.-H);
* SEGMENTS DE BASE :
DA1 = PA1 DROIT nz PA3 ;
DB1 = PB1 DROIT nz PB3 ;
DC1 = PC1 DROIT nz PC3 ;
DAC3 = PA3 DROIT (nx/2) PC3 ;
DAC1 = PA1 DROIT (nx/2) PC1 ;
DAC2 = PA2 DROIT (nx/2) PC2 ;
DCB3 = PC3 DROIT (nx/2) PB3 ;
DCB1 = PC1 DROIT (nx/2) PB1 ;
DCB2 = PC2 DROIT (nx/2) PB2 ;
DSOL = DAC3 ET DCB3 ;
DAXE = DAC1 ET DCB1 ;
DFLU = DAC2 ET DCB2 ;
SOL2 = DSOL ELEM (LECT 2 PAS 1 NX) ;
DENT = DA1 ;
DSOR = DB1 ;
DMIL = DC1 ;
ENT2 = DENT ELEM (LECT 1 PAS 1 (NZ-1)) ;
* DOMAINES
DOM1 = DA1 DAC3 (INVE DC1) (INVE DAC1) DALLER PLAN ;
DOM2 = DC1 DCB3 (INVE DB1) (INVE DCB1) DALLER PLAN ;
DOMTOT = DOM1 ET DOM2 ;
BORTOT = CONTOUR DOMTOT ;
* ---------------------- MODELES et normales aux faces -----------
MDOMTOT = CHAN DOMTOT QUAF ;
Mdsor = CHAN dsor QUAF ;
Mdmil = CHAN dmil QUAF ;
Mdent = CHAN dent QUAF ;
Mdsol = CHAN dsol QUAF ;
Msol2 = CHAN sol2 QUAF ;
ELIM (MDOMTOT et Mdsor et Mdmil et Mdent et Mdsol et Msol2) 1.e-5 ;
$domtot =mode MDOMTOT 'NAVIER_STOKES' LINE ;
DOMA $domtot 'IMPR' ;
$dsor =mode Mdsor 'NAVIER_STOKES' LINE ;
$dmil =mode Mdmil 'NAVIER_STOKES' LINE ;
$dent =mode Mdent 'NAVIER_STOKES' LINE ;
$dsol =mode Mdsol 'NAVIER_STOKES' LINE ;
$sol2 =mode Msol2 'NAVIER_STOKES' LINE ;
NOR = DOMA $DOMTOT 'NORMALE' ;
* ------------------------ Donnees --------------------------------------
* ECOULEMENT : UM = vitesse debitante (m/s)
* NU = viscosite cinematique (m2/s)
* ROF = masse vomumique du gaz (kg/m3)
* PARTICULES : C0 = concentration initiale (part/m3)
* CP = concentration a la paroi (part/m3)
* ROG = gravite x masse volumique des particules (kg/m2s2)
* DP = diametre des particules (m)
* DIF = coefficient de diffusion brownienne (m2/s)
R0 = H ;
L0 = L ;
UM = 7.5E-3 ;
NU = 1.5E-5 ;
ROF = 1.2 ;
ROG = 0. (-9810.) ;
DP = 1.E-7 ;
DIF = 6.8E-10 ;
RAP = DP/2. ;
C0 = 1. ;
CP = 0. ;
* ----------------- INITIALISATION champ de vitesse ---------------------
cy=coor 2 domtot ;
cy=nomc 'UX' cy ;
cy=abs cy ;
VX= kcht $domtot scal sommet comp 'UX' (1.5*UM*( 1.-((cy/R0)**2.)) ) ;
VY= kcht $domtot scal sommet comp 'UY' 0. ;
VN= kcht $domtot vect sommet comp (mots 'UX' 'UY') (vx et vy) ;
* -------------------- calcul vitesse de depot des aerosols -------------
UET = KUET NU VN NOR $DOMTOT $SOL2 ;
AK = FPAL NU ROF UET NOR ROG RAP $SOL2 ;
* ------------------------- Equation de CONCENTRATION -------------------
CALCUL = EQEX $domtot 'ITMA' 100 'ALFA' 0.9 'TFINAL' 50.
  OPTI 'EFM1' 'EXPL' 'SUPGDC'
  ZONE $DOMTOT 'OPER' 'TSCA' DIF 'VN' 0. 'INCO' 'CN'
  ZONE $SOL2 'OPER' 'ECHI' AK CP 'INCO' 'CN'
  OPTI EFM1 'CENTREE'
  ZONE $DOMTOT 'OPER' 'DFDT' 1. 'CN' 'DELTAT' 'INCO' 'CN'
'CLIM' 'CN' TIMP DENT C0 ;
* --------------------------- Initialisations et historiques ------------
calcul.'INCO' = table 'INCO' ;
calcul.'INCO'.'VN'= vn ;
calcul.'INCO'.'CN' = kcht $domtot scal sommet c0 ;
lh = PB1 et PB2 et PB3 et PC1 et PC2 et PC3 ;
his = khis 'CN' lh ;
calcul.'HIST'=his ;
* --------------------------- EXECUTION ---------------------------------
EXEC CALCUL ;
* ------------------------- DESSINS -------------------------------------
SI GRAPH ;
  VNCH = VECTEUR VN 10. UX UY VERT ;
  TITRE 'depot laminaire : VITESSES ';
  TRACE VNCH DOMTOT (BORTOT) ;
  CN = calcul.'INCO'.'CN' ;
  opti isov ligne ;
  titre 'CONCENTRATION' ;
  trace cn domtot (bortot) ;
  dessin his.'TABD' his.'CN' ;
  CMIL = KCHT $DMIL scal sommet CN ;
  CSOR = KCHT $DSOR scal sommet CN ;
  CSOL = KCHT $DSOL scal sommet CN ;
  TITRE ' CONCENTRATION MILIEU ';
  evoc1 = evol chpo CMIL DMIL ; dess evoc1 ;
  TITRE ' CONCENTRATION SORTIE ';
  evoc2 = evol chpo CSOR DSOR ; dess evoc2 ;
  TITRE ' CONCENTRATION PAROI  ';
  evoc3 = evol chpo CSOL DSOL ; dess evoc3 ;
FINSI ;
* -------------------- test sur le flux deposé total --------------------
SUR = DOMA $SOL2 'VOLUME' ;
KV = SUR*AK ;
CN1 = KCHT $SOL2 scal sommet CALCUL.INCO.'CN' ;
CE2 = NOEL $SOL2 CN1 ;
CKS = CE2*KV ;
CKS = SOMT CKS ;
DEPREL = ( CKS - 1.26289E-06 ) / 1.26289E-06 ;
mess 'FLUX DEPOSE =' CKS ;
SI ( (ABS DEPREL) > 0.05 ) ;
     ERREUR 5 ;
FINSI ;
FIN ;
```

## ccar3d [Fluides Transitoire]
```
* --- 12 OCTOBRE 1998 ---
* TEST CAVITE CUBIQUE
* teste KCCT NS en 3D + le Bi CG
GRAPH = 'N' ;
err1=5.e-3;
option dime 2 elem tri6 ;
opti isov suli ;
p1= 0 0 ; p12=0.5 0. ; p2= 1 0 ;
ds1=0.051 ; ds2=0.12 ;
* ds1=0.01 ; ds2=0.1 ;
 ds1=2. ; ds2=2. ;
 ds1=0.25 ; ds2=0.2 ;
 ds1=0.3 ; ds2=0.3 ;
ab=p1 d dini ds1 dfin ds2 p12 d dini ds2 dfin ds1 p2 ;
ab12= p12 d dini ds1 dfin ds2 (0.5 0.5) d dini ds2
dfin ds1 (0.5 1.) ;
mt= ab trans dini ds1 dfin ds2 (0 0.5) trans dini ds2
dfin ds1 (0 0.5) ;
 bc=cote 2 mt ;
 cd=cote 3 mt ;
 da=cote 4 mt ;
ct=ab et bc et cd et da ;
elim ct 1.e-3 ;
 mt=ab bc cd da daller ;
mt=orie mt ;
opti dime 3 elem cu20;
mth=mt plus (0 0 1) ;
ab= ab12 plus (0 0 1) ;
oeil = 10 10 100 ;
nph=2 ;
cav=mt volu nph mth ;
* trace oeil cav;
macro= '   ' ;
f1=face 1 cav ;
f2=face 2 cav ;
f3=face 3 cav ;
cav= chan cav quaf ;
f1=chan f1 quaf ;
f2=chan f2 quaf ;
f3=chan f3 quaf ;
ab=chan ab quaf ;
psup=cd trans nph (0 0 1) ;
psup= chan psup quaf ;
elim (cav et f1 et f2 et f3 et psup et ab ) 1.e-5 ;
elim (f3 et psup) 1.e-5 ;
paroi=psup diff f3 ;
 $mt=mode cav 'NAVIER_STOKES' QUAF;
 $AB=mode AB 'NAVIER_STOKES' QUAF;
MU=1. ;
RO= 400. ;
kpress='CENTREP1' ;
prep1=doma $mt kpress;
bcp=elem prep1 POI1 (lect 1) ;
  rv= eqex 'OMEGA' 0.3 'NITER' 3
  'OPTI' 'EF' 'IMPL' KPRESS 'SUPG' 'DIV2'
  ZONE $mt OPER KBBT (1.) INCO 'UN' 'PRES'
  ZONE $mt OPER NS 1. 'UN' (MU/RO) INCO 'UN' ;
  rv=eqex rv
  CLIM
  UN VIMP (F3 ET F1) 0. UN WIMP (F1 et F2 et F3) 0.
  UN UIMP PSUP 1. UN UIMP (PAROI ET F1) 0. PRES TIMP bcp 0. ;
rv.inco= table inco ;
rv.inco.tn = kcht $mt scal sommet 5. ;
rv.inco.un = kcht $mt vect sommet (1.e-5 1.e-5 1.e-5) ;
rv.inco.pres = kcht $mt scal KPRESS 1.e-5 ;
 rv.'METHINV'.TYPINV=3 ;
 rv.'METHINV'.IMPINV=1 ;
 rv.'METHINV'.NITMAX=1000;
 rv.'METHINV'.PRECOND=3 ;
 rv.'METHINV'.RESID =1.e-10 ;
 exec rv ;
 srti=doma $AB 'MAILLAGE' ;
 evolV = EVOL 'CHPO' (rv.'INCO'.'UN') UX (srti ) ;
 evx=extr evolV 'ORDO' ;
 list evx ;
 evy=extr evolV 'ABSC' ;
 evolV= evol 'MANU' 'Vitesse' evx 'Hauteur' evy ;
 si ('EGA' graph 'O' );
 TAB1=TABLE;
 TAB1.'TITRE'=TABLE ;
 TAB1 . 1 ='MARQ      REGU ' ;
 TAB1.'TITRE' . 1 = mot 'Composante_UX ' ;
 DESS evolV 'TITX' 'R (m)' 'TITY' 'V (m/s)' LEGE TAB1 ;
 c1=vect (rv.inco.'UN') 0.3 ux uy uz jaune ;
 trace c1 mt ;
 pn=elno $mt (rv.inco.'PRES') kpress;
 trace pn mt ;
 finsi ;
 evx=abs evx ;
 lrr='PROG' 3.43000E-06 +3.74144E-02 +6.40402E-02 +6.91359E-02
 +6.26670E-02 +3.46496E-02 5.43639E-02 .17102 .65700 ;
 ER=SOMM( (((abs (evx - lrr))*0.125)**2.) / 1. ) ;
 ER=SOMM( abs (evx - lrr) ) ;
 mess ' Ecart sur CENTREP1 TRI7 QUADR ' er ;
 si ( er > err1 ) ; erreur 5 ; finsi ;
 FIN ;
```

## jetplankei [Fluides Transitoire]
```
* jetplankei.dgibi
* jet 2D Plan monophasique incompressible
* pour fiche de validation du K-epsilon
* Pierre Cornet , sept 97
* jpm , mars 06 : adaptation pour K-epsilon implicite (kei)
COMPLET = FAUX;
* --------------------------- Numérique ---------------------------------
Si COMPLET;
NBIT=400;
DT = 0.002 ;
DISCR = MACRO;
KPRESS= CENTREP1;
sinon;
NBIT=80;
DT = 0.01 ;
DISCR = LINE;
KPRESS= CENTRE;
finsi;
graph = faux;
* graph = vrai;
* opti trace 'PSC' ;
* ----------------------- fin Numérique ---------------------------------
* --------------------------- procédure ---------------------------------
* $$$$ OUTFLOW
'DEBPROC' OUTFLOW ;
ARGU RX*TABLE ;
* ZONE $Mt OPER 'OUTFLOW' $out Ro Un Muf INCO 'UN'
* UN
* MUF viscosité dynamique effective
* (tourbillonnaire+moléculaire)
rv=rx.'EQEX' ;
iarg=rx.'IARG' ;
* mess 'iarg='iarg;
$mt=rx.'DOMZ' ;
* Lecture du 1er Argument objet mmodel
Si(ega ('TYPE' rx.'ARG1') 'MMODEL  ');
$mfront=rx.'ARG1';
Dg=doma $mfront 'XXDIAGSI' ;
Sinon ;
erreur 2;
quitter outflow;
Finsi ;
* Lecture du 2ème Argument la densité
Si(ega ('TYPE' rx.'ARG2') 'MOT     ');
Ro = rv.inco.(rx.'ARG2');
Sinon ;
Ro = rx.'ARG2';
Finsi ;
* Lecture du 3ème Argument la vitesse
Si(ega ('TYPE' rx.'ARG3') 'MOT     ');
un = rv.inco.(rx.'ARG3');
Sinon ;
un = rx.'ARG3';
Finsi ;
* Lecture du 4ème Argument la viscosité
Si(ega ('TYPE' rx.'ARG4') 'MOT     ');
Muf = rv.inco.(rx.'ARG4');
Sinon ;
Muf = rx.'ARG4';
Finsi ;
* INITIALISATIONs
Si (Exist rx 'rxtm');
rxtm=rx.'rxtm';
lmx=rxtm.'lmx';
lm0=rxtm.'lm0';
lm=rxtm.'lm';
nc=rxtm.'nc';
MSV = chai rxtm.'msv' ;
MI1 = rxtm.'MI1' ;
KPRES=rxtm.'KPRES';
Sinon;
rxtm=table 'KIZX';
rx.'rxtm'=rxtm;
Si (NON (EGA (dime rx.'LISTINCO') 1));
  mess ' Erreur dans la procédure Outflow !';
  mess ' Il doit y avoir une inconnue !';
  quitter outflow ;
Finsi;
MI1=EXTR rx.'LISTINCO' 1 ;
lmx=(extr (rv.inco.MI1) 'COMP');
lm0=(extr un 'COMP');
nc=dime lm0;
Si(nc > 1);
* mess 'Outflow Cas vectoriel ' MI1;
MSV=chai 'VECT';
lm=mots (chai 1 MI1) (chai 2 MI1);
Si (EGA (vale dime) 3);
lm=lm et (mots (chai 3 MI1));
Finsi;
kpr=rx.'KOPT'.'KPOIN';
Si(EGA KPR 2);KPRES='CENTRE';Finsi;
Si(EGA KPR 4);KPRES='CENTREP1';Finsi;
Si(EGA KPR 5);KPRES='MSOMMET';Finsi;
Sinon;
* mess 'Outflow Cas scalaire  ' MI1;
MSV=chai 'SCAL';
lm=mots MI1;
Finsi;
rxtm.'lmx'=lmx;
rxtm.'lm0'=lm0;
rxtm.'lm'=lm;
rxtm.'nc'=nc;
rxtm.'msv'=chai MSV;
rxtm.'MI1'=MI1;
rxtm.'KPRES'=KPRES;
rxtm.'LISTINCO'=MOTS MI1 ;
rxtm.'DOMZ'=$mfront;
rxtm.'KOPT'=rx.'KOPT';
rxtm.'IARG'=1;
rxtm.'EQEX'=rx.'EQEX';
rxtm.'NOMZONE'=' ';
rxtm.'TDOMZ'=0;
rxtm.'NOMOPER'=mot 'MDIA_T';
Finsi;
* Fin Initialisations
 mfront=doma $mfront maillage ;
 nj=doma $mt 'NORMALEV';
* unj= vect nj 0.1 ux uy jaune ;
* trace unj mt;
 njf = redu nj mfront ;
* unj= vect njf 0.1 ux uy rouge ;
* trace unj mt TITR ' FRONTIERE';
 xn = rv.inco.MI1;
 ujf = redu un mfront ;
 us=psca ujf lm0 njf lm0;
 ius=masq us 'INFERIEUR' 0.;
 rv.inco.'us'=us;
 rv.inco.'ius'=ius;
 Si(Ega nc 1);
 us=2.*(redu xn mfront);
 Finsi;
 rxtm.'ARG1'=kcht $mfront scal sommet ((-1.)*Ro*us*ius);
 st1 mat1 = MDIA rxtm ;
* st1 mat1 = KOPS 'MATRIK' ;
 Dgi=Dg*ius;
 Si(nc > 1);
 puj=0.;
 Si(EXIST (rv.inco) 'PRESSION');
 pn=redu (elno $mt rv.inco.'PRESSION' KPRES) mfront;
 puj=Ro*pn*us;
 Finsi;
 gru = redu (Muf*(kops 'GRADS' (exco un 'UX') $mt)) mfront;
 grv = redu (Muf*(kops 'GRADS' (exco un 'UY') $mt)) mfront;
 mgunj = (nomc (Dgi*((psca gru lm0 njf lm0)-puj)) (extr lm 1))
       + (nomc (Dgi*((psca grv lm0 njf lm0)-puj)) (extr lm 2)) ;
 Si(Ega (vale dime) 3);
 mgunj = mgunj + (nomc (Dgi*((psca grv lm0 njf lm0)-puj)) (extr lm 3));
 Finsi;
 Sinon;
 grt = redu (Muf*(kops 'GRADS' xn $mt)) mfront ;
 mgunj = (nomc (Dgi*(psca grt lm0 njf lm0)) (extr lm 1)) ;
 Finsi;
 St1 = kcht $mfront MSV sommet comp lm ((-1.)*mgunj);
RESPRO St1 mat1 ;
FINPROC ;
* ----------------------- fin procédure ---------------------------------
* --------------------------- maillage ----------------------------------
TITRE 'JET' ;
OPTI DIME 2 ELEM QUA8 ;
DJ = 2.e-2 ; RJ = DJ/2. ; RM = 150.*RJ ;
DJ = 2.e-2 ; RJ = DJ/2. ; RM = 50.*RJ ;
* points :
P00=0. 0.; PJ0=RJ 0.; PR0=RM 0.; PJ5=RJ (50.*DJ);
P02=0. (20.*DJ); P03=0. (30.*DJ); P04=0. (40.*DJ); P05=0. (50.*DJ);
PR2=RM (20.*DJ); PR3=RM (30.*DJ); PR4=RM (40.*DJ); PR5=RM (50.*DJ);
* segments verticaux :
A02 = DROI -20 P00 P02 dini (0.5*DJ) dfin (1.25*DJ) ;
A23 = DROI -6 P02 P03 dini (0.9*DJ) dfin (1.25*DJ) ;
A34 = DROI 4 P03 P04 ;
A45 = DROI -3 P04 P05 dini (1.25*DJ) dfin (2.*DJ) ;
B02 = DROI -20 PR0 PR2 dini (0.5*DJ) dfin (1.25*DJ) ;
B23 = DROI -6 PR2 PR3 dini (0.9*DJ) dfin (1.25*DJ) ;
B34 = DROI 4 PR3 PR4 ;
B45 = DROI -3 PR4 PR5 dini (1.25*DJ) dfin (2.*DJ) ;
AXE = A02 ET A23 ET A34 ET A45 ;
BORD= B02 ET B23 ET B34 ET B45 ;
* segments horizontaux :
JET = DROI 2 P00 PJ0 ;
BAS2 = DROI PJ0 PR0 dini (RJ/2.) dfin (10.*RJ) ; BAS = JET ET BAS2 ;
HAU1 = DROI 2 P05 PJ5 ;
HAU2 = DROI PJ5 PR5 dini (RJ/2.) dfin (10.*RJ) ; HAUT=HAU1 ET HAU2 ;
* domaine total :
MT = DALL BAS BORD (inve HAUT) (inve AXE) 'PLAN' ;
CMT = cont MT ;
Mmt = chan QUAF MT ;
Mjet = chan QUAF jet ;
Mbord= chan QUAF bord;
Mbas2= chan QUAF bas2;
Maxe = chan QUAF axe ;
Mhaut= chan QUAF haut;
elim (Mmt et Mjet et Mbord et Mbas2 et Maxe et Mhaut) 1.e-5;
$MT = mode Mmt 'NAVIER_STOKES' DISCR;
$JET = mode Mjet 'NAVIER_STOKES' DISCR;
$BORD = mode Mbord 'NAVIER_STOKES' DISCR;
$BAS2 = mode Mbas2 'NAVIER_STOKES' DISCR;
$AXE = mode Maxe 'NAVIER_STOKES' DISCR;
$HAUT = mode Mhaut 'NAVIER_STOKES' DISCR;
Ml20d = Mhaut moins (P05 moins P02) coul verte;
Ml30d = Mhaut moins (P05 moins P03) coul verte;
Ml40d = Mhaut moins (P05 moins P04) coul verte;
elim (Mmt et Ml20d et Ml30d et Ml40d) 1.e-5;
MT = doma $MT maillage ;
axe = doma $axe maillage ;
jet = doma $jet maillage ;
bord= doma $bord maillage ;
bas2= doma $bas2 maillage ;
haut= doma $haut maillage ;
Si Graph;trace MT;Finsi;
* ------------------------ donnees physiques ----------------------------
NUF = 1.5E-5 ;
REJ = 2.e4 ;
UJ = REJ*NUF/DJ ; mess 'vitesse d injection (m/s) =' UJ ;
* KJ = 0.05*UJ*UJ ; mess 'KJ =' KJ ;
* EJ = 0.02*(UJ**3.)/DJ ; mess 'EJ =' EJ ;
KJ = 1.E-3 ;
EJ = 6.E-3 ;
NUTj = 0.09*KJ*KJ/EJ ; mess 'NUTJ =' nutj ;
KA = 1.E-7 ;
EA = 1.E-5 ;
L0 = 25.*DJ ;
* -------------------------- equations ----------------------------------
RV = EQEX $MT 'DUMP' 'ITMA' NBIT
    'OPTI' 'EF' 'SUPG' 'IMPL'
* 'ZONE' $MT OPER OUTFLOW $haut 1. 'UN' 'MUF' 'INCO' 'KN'
* 'ZONE' $MT OPER OUTFLOW $haut 1. 'UN' 'MUF' 'INCO' 'EN'
    'ZONE' $MT OPER OUTFLOW $haut 1. 'UN' 'MUF' 'INCO' 'UN'
    'ZONE' $MT 'OPER' 'KEPSILON' 1. 'UN' NUF 'DT' 'INCO' 'KN' 'EN'
    'ZONE' $MT 'OPER' 'NS' 1. 'UN' 'MUF' 'INCO' 'UN'
    'OPTI' 'EFM1' 'CENTREE'
    'ZONE' $MT 'OPER' DFDT 1. 'UN' 'DT' 'INCO' 'UN';
    RV = EQEX RV
    'CLIM' 'UN' UIMP JET 0. 'UN' VIMP JET UJ
           'UN' VIMP BAS2 0. 'UN' UIMP AXE 0.
                                    'UN' VIMP BORD 0.
           'KN' TIMP JET KJ 'EN' TIMP JET EJ
           'KN' TIMP BORD 0. 'EN' TIMP BORD EA ;
* RV.'ALGO_KEPSILON'= MOTS 'RNG';
RVP = EQEX 'OPTI' 'EF' KPRESS
 'ZONE' $MT 'OPER' 'KBBT' -1. 'INCO' 'UN' 'PRES' ;
RV.'PROJ'= RVP ;
* ------------------------ initialisations ------------------------------
RV.INCO = TABLE 'INCO' ;
RV.'INCO'.'UN' = KCHT $MT VECT SOMMET (1.E-7 1.E-7) ;
RV.'INCO'.'PRES' = 'KCHT' $MT 'SCAL' KPRESS 0.;
RV.'INCO'.'KN' = KCHT $MT SCAL SOMMET 1.E-7 ;
RV.'INCO'.'EN' = KCHT $MT SCAL SOMMET 1.E-5 ;
RV.'INCO'.'MUF' = KCHT $MT SCAL SOMMET 1.E-6 ;
RV.'INCO'.'DT' = DT ;
* ------------------------ historiques ----------------------------------
P11 = MT POIN 'PROC' ((25.*RJ) (10.*DJ));
P12 = MT POIN 'PROC' ((25.*RJ) (20.*DJ));
P14 = MT POIN 'PROC' ((25.*RJ) (40.*DJ));
P15 = MT POIN 'PROC' ((25.*RJ) (50.*DJ));
LH = P02 et P03 et P04 et P05 et P11 et P12 et P14 et P15 ;
HIS = KHIS 'UN' 1 LH 'UN' 2 LH 'KN' LH 'EN' LH ;
RV.'HIST' = HIS ;
* ------------------------ resolution -----------------------------------
 lh= (POIN MT PROC (0.05 0.01)) et (POIN MT PROC (0.05 0.05))
    et (POIN MT PROC (0.05 0.1)) et (POIN MT PROC (0.05 0.15))
    et (POIN MT PROC (0.05 0.2)) et (POIN MT PROC (0.05 0.7))
    et (POIN MT PROC (0.05 0.3)) et (POIN MT PROC (0.05 0.6))
    et (POIN MT PROC (0.05 0.4)) et (POIN MT PROC (0.05 0.5));
  his=khis 'UN' 1 lh
           'UN' 2 lh
           'KN' lh
           'EN' lh;
      his.'KFIH'=1;
  rv.'HIST'=his;
 EXEC rv;
UN = (RV.'INCO'.'UN');
uaxe = ((exco UN 'UY') redu axe)*(1./UJ);
evuaxe= evol chpo uaxe axe ;
* ------------------------ post-traitement ------------------------------
Si Graph;
 trace ((cont mt) et Ml20d et Ml30d et Ml40d);
 dessin his.'TABD' his.'KN' TITR ' historiques:  k';
 dessin his.'TABD' his.'EN' TITR ' historiques:  epsilon';
 dessin his.'TABD' his.'1UN' TITR ' historiques:  ux';
 dessin his.'TABD' his.'2UN' TITR ' historiques:  uy';
UNV = VECT UN 5.E-3 UX UY ;
TRAC UNV CMT TITRE 'VITESSES AIR' ;
dess evuaxe TITR 'Vitesse sur l axe';
z= (coor 2 axe) + 1.e-3;
vaxe= 5.8 * Dj * (inve z);
evax = evol chpo vaxe axe ;
dess (evax et evuaxe) ybor 0.1 1.2 TITR ' Vitesses sur l axe';
 u20d = (exco un 'UY') redu Ml20d;
 um20d = maxi u20d;
 u20d = evol chpo (u20d*(1./um20d)) ml20d ;
 u30d = (exco un 'UY') redu Ml30d;
 um30d = maxi u30d;
 u30d = evol chpo (u30d*(1./um30d)) ml30d ;
 u40d = (exco un 'UY') redu Ml40d;
 um40d = maxi u40d;
 u40d = evol chpo (u40d*(1./um40d)) ml40d ;
 z20d = maxi (coor 2 ml20d);
 z30d = maxi (coor 2 ml30d);
 z40d = maxi (coor 2 ml40d);
 r20d = (extr u20d 'ABSC')*(1./z20d);
 r30d = (extr u30d 'ABSC')*(1./z30d);
 r40d = (extr u40d 'ABSC')*(1./z40d);
 u20d = evol manu r20d (extr u20d 'ORDO');
 u30d = evol manu r30d (extr u30d 'ORDO');
 u40d = evol manu r40d (extr u40d 'ORDO');
 dess (u20d et u30d et u40d) XBOR 0. 0.4
 TITR ' Profil radiaux de vitesse';
nutsnu = rv.inco.'MUF' * (1./NUF) ;
trace nutsnu mt (cont mt) TITR 'Muf / Nu' ;
trace rv.inco.'KN' mt (cont mt) TITR ' Kn ';
trace rv.inco.'EN' mt (cont mt) TITR ' En ';
Finsi;
* -------------------- fin post-traitement ------------------------------
 Si (NON COMPLET);
 uaxref=prog
  1.0000 1.0250 0.97229 1.0009 0.96387
  0.99073 0.97449 1.0046 1.0016 1.0228
  1.0149 1.0024 0.96638 0.93515 0.89487
  0.85870 0.81994 0.78738 0.75198 0.72043
  0.69096 0.66619 0.64104 0.61681 0.59295
  0.57226 0.55194 0.52699 0.50559 0.48760
  0.47019 0.44757 0.42364 0.40301 ;
zaxe = extr evuaxe 'ABSC';
list (extr evuaxe 'ORDO');
evuaxer=evol manu zaxe uaxref ;
m=(INTG evuaxer 'ABSO') ;
delt2= (INTG (evuaxer - evuaxe) 'ABSO')/m;
mess ' deltaL2 : m=' m ' delt2=' delt2;
  Si (delt2 > 8.e-3);ERREUR 5;Finsi;
 FINSI;
FIN ;
```

## chimsour1d [Fluides Transport]
```
GRAPH = faux ;
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
* CAS TEST : chimsour1d.dgibi
* TRANSPORT GEOCHIMIE AVEC SOURCE ( CAS 1D)
* la partie post-traitement avec graphique contient des exemples
* d'utilisation des procedures TRACHIS TRACHIT DESTRA
* avec des recherches d'identificateurs par NOESPCHI et NOCOMCHI
* emplacement de COMPOM
emp1 = 'CHAINE' DIVERS '/COMPOM' ;
* emp1 = 'MOT' 'COMPOM' ;
* emp1 = 'MOT' '/export/home/castem2001/DGIBI/COMPOM' ;
'OPTION' 'ECHO' 0 ;
* Génération du maillage
'OPTION' 'DIME' 2 'ELEM' 'QUA4' 'TRACER' 'PSC' ;
* Axe
ORIG = 0.0 0.0 ;
R10 = 1. 0.0;
XAXE = 'DROIT' 1 ORIG R10;
'ELIMINATION' XAXE 0.01;
* Points
Z90 = 0.0 90.0;
Z5 = 0.0 5.0;
Z10 = 0.0 10.0;
Z40 = 0.0 40.0 ;
Z390 = 0.0 390.0;
ZNAD = 0.0 -100.0;
ZM40 = 0.0 -40.0 ;
ZBOT = 0.0 -10.0;
ZB2 = 0.0 -5.0;
ZT2 = 0.0 5.0;
ZTOP = 0.0 10.0;
ZZEN = 0.0 400.0;
XAXE2 = 'PLUS' XAXE ZNAD;
ZONE1 = 'TRANSLATION' XAXE2 6 ('MOIN' ZM40 ZNAD) ;
XAXM40 = 'INVERSE' ('COTE' 3 ZONE1) ;
YN = 'INVERSE' ('COTE' 4 ZONE1) ;
LIGM40 = 'ELEM' ZONE1 'APPUYE' 'LARGEMENT' XAXM40 ;
ZONE2 = 'TRANSLATION' XAXM40 6 ('MOIN' ZBOT ZM40) ;
XAXBOT = 'INVERSE' ('COTE' 3 ZONE2) ;
YK = 'INVERSE' ('COTE' 4 ZONE2) ;
LIGBOT = 'ELEM' ZONE2 'APPUYE' 'LARGEMENT' XAXBOT ;
ZONE3 = 'TRANSLATION' XAXBOT 8 ('MOIN' ZTOP ZBOT) ;
XAXTOP = 'INVERSE' (COTE 3 ZONE3) ;
LIGTOP = 'ELEM' ZONE3 'APPUYE' 'LARGEMENT' XAXTOP ;
YB = 'INVERSE' (COTE 4 ZONE3) ;
ZONE4 = 'TRANSLATION' XAXTOP 6 ('MOIN' Z40 ZTOP) ;
XAXP40 = 'INVERSE' (COTE 3 ZONE4) ;
YS = 'INVERSE' (COTE 4 ZONE4) ;
ZONE5 = 'TRANSLATION' XAXP40 36 ('MOIN' ZZEN Z40) ;
LIGP40 = 'ELEM' ZONE5 'APPUYE' 'LARGEMENT' XAXP40 ;
XAXE1 = 'INVERSE' (COTE 3 ZONE5) ;
YZ = 'INVERSE' (COTE 4 ZONE5) ;
LIGAX1 = 'ELEM' ZONE5 'APPUYE' 'LARGEMENT' XAXE1 ;
YAXE = YN 'ET' YK 'ET' YB 'ET' YS 'ET' YZ;
X80 = 80.0 0.0;
MT = ZONE1 'ET' ZONE2 'ET' ZONE3 'ET' ZONE4 'ET' ZONE5 ;
'ELIMINATION' (MT 'ET' YAXE) 0.01;
'TASSER' MT;
SDOM = 'ELEM' MT 'CONTENANT' ORIG ;
SDOM = 'COULEUR' SDOM 'ROUGE' ;
AXELEM = 'ELEM' MT 'APPUYE' 'LARGEMENT' YAXE ;
* Calcul CHI1
TABDON = 'TABLE' ;
TABDON.IDEN = 'LECT' 50 5 112 ;
TABDON.CLIM = 'TABLE' ;
TABDON.CLIM . TYP3 = 'LECT' 21442 ;
TABDON.CLIM . COMP3 = 'LECT' 112 ;
TABDON.CLIM . TYP6 = 'LECT' 21440 21441 12721 12722 ;
TB1 = 'CHI1' TABDON 'COMP' emp1 'LOGK' emp1 ;
* - Création des maillages hybrides
MFTOT = 'CHANER' MT 'QUAF' ;
MFSOUR = 'CHANER' SDOM 'QUAF' ;
MFBAS = 'CHANER' XAXE2 'QUAF' ;
MFAXE = 'CHANER' AXELEM 'QUAF' ;
MFP40 = 'CHANER' LIGP40 'QUAF' ;
MFTOP = 'CHANER' LIGTOP 'QUAF' ;
'ELIMINATION' 0.001
(MFTOT 'ET' MFSOUR 'ET' MFBAS 'ET' MFAXE 'ET' MFP40 'ET' MFTOP) ;
* - Modèle
MODHYB = 'MODELE' MFTOT 'DARCY' ANISOTROPE ;
MMSOUR = 'MODELE' MFSOUR 'DARCY' ANISOTROPE ;
MMBAS = 'MODELE' MFBAS 'DARCY' ANISOTROPE ;
MMAXE = 'MODELE' MFAXE 'DARCY' ANISOTROPE ;
MMP40 = 'MODELE' MFP40 'DARCY' ANISOTROPE ;
MMTOP = 'MODELE' MFTOP 'DARCY' ANISOTROPE ;
CHYB1 = 'DOMA' MODHYB 'SURFACE' ;
CHYB2 = 'DOMA' MODHYB 'NORMALE' ;
XVOLU = 'DOMA' MODHYB 'VOLUME' ;
CETOT = 'DOMA' MODHYB 'CENTRE' ;
MATOT = 'DOMA' MODHYB 'MAILLAGE ';
FATOT = 'DOMA' MODHYB 'FACE' ;
* - On génère la ligne SEGAXE pour le post-traitement
CEAXE = 'DOMA' MMAXE 'CENTRE' ;
NBCC = 'NBNO' CEAXE ;
PI1 = 'POINT' CEAXE 1 ;
PI0 = PI1 ;
I = 2 ;
'SI' (NBCC > 1) ;
  PI2 = 'POINT' CEAXE I ;
  SEGAXE = 'QUELCONQUE' 'SEG2' PI1 PI2 ;
  SI (NBCC > 2) ;
    NBCC2 = NBCC - 2 ;
    'REPETER' BLOC6 nbcc2 ;
      PI1 = PI2 ;
      I = I + 1 ;
      PI2 = 'POINT' CEAXE I ;
      LILI = 'QUELCONQUE' 'SEG2' PI1 PI2 ;
      SEGAXE = SEGAXE 'ET' LILI ;
    'FIN' BLOC6 ;
  'FINSI' ;
'FINSI' ;
* Données physiques
* - on entre la vitesse on en deduit le flux aux faces
V = 'MANU' CHPO FATOT 'NATURE' 'DISCRET' 2 'UX' 0. 'UY' 0.1;
VNCH = 'VECTEUR' V 1. 'UX' 'UY' 'ROUGE' ;
MOT1 = 'MOTS' 'UX' 'UY' ;
VAVN = 'PSCAL' V CHYB2 MOT1 MOT1 ;
VAVN = 'NOMC' 'SCAL' VAVN ;
QFACE = VAVN * CHYB1 ;
QFACE = 'NOMC' 'FLUX' QFACE ;
* - matériau pour le transport
DIR1 = 1. 0. ;
PORO = 0.5 ;
D11C = 1.D0 ;
D22C = 5.D0 ;
D11 = 'MANU' CHML MATOT SCAL D11C ;
D22 = 'MANU' CHML MATOT SCAL (D22C* poro) ;
D21 = 'MANU' CHML MATOT SCAL 1.D-15 ;
MAT1 = 'MATERIAU' MODHYB 'DIRECTION' DIR1 K11 D11 K21 D21 K22 D22 ;
* - pas de temps
* NBPAST nombre de pas de temps (200 pour un calcul significatif)
DELTAT= 1.25 ;
NBPAST= 10 ;
TETA = 1. ;
TFINAL = NBPAST * DELTAT ;
* Initialisation du système
* CTOTC concentrations au centre
* CTOT concentrations aux faces
CTOT = 'MANU' 'CHPO' FATOT 3 X050 2.D-9 X005 1.D-9 X112 0.D0 ;
TT1 = 'EXTR' CTOT 'COMP' ;
NOCOMP = 'EXTR' TT1 1 ;
CTOTC = 'MANU' 'CHPO' CETOT 1 NOCOMP 0. ;
NBCOMP = 'DIME' TT1 ;
MASHYB = 'MHYB' MODHYB MAT1 ;
'REPETER' BOUC1 NBCOMP ;
  NOCOMP = 'EXTR' TT1 &BOUC1 ;
  TPR = 'EXCO' CTOT NOCOMP 'TH' ;
  TPC = 'HYBP' MODHYB MASHYB TPR ;
  TPC = 'NOMC' NOCOMP TPC ;
  CTOTC = CTOTC + TPC ;
'FIN' BOUC1 ;
CLOGC = 'MANU' 'CHPO' CETOT 3 X050 -7. X005 -9. X112 -7. ;
FLOGC = 'MANU' 'CHPO' FATOT 3 X050 -7. X005 -9. X112 -7. ;
* Source
QELEM0 = 1.D-3;
QELEM = QELEM0 / DELTAT ;
SOURC0 = 'MANU' 'CHPO' CETOT 3 X050 0. X005 0. X112 0. ;
SOURC1 = 'MANU' 'CHPO' ('DOMA' MMSOUR 'CENTRE') 3
                X050 (-1.* QELEM) X005 QELEM X112 0. ;
SOURC1 = SOURC1 + SOURC0 ;
SOURC = 'CHARGEMENT' SOURC1
           ('EVOL' 'MANU' ('PROG' 0. 'PAS' DELTAT (200. * DELTAT))
                          (PROG 1. 1. 199. * 0.) ) ;
* On initialise les concentrations des aqueux aux faces
* par un premier calcul CHI2
TBPAR2 = 'TABLE' ;
TBPARM = 'TABLE' ;
TBPARM.'SOUSTYPE' = 'DONNEES_CHIMIQUES' ;
TBPARM.TOT = CTOT ;
TBPARM.LOGC = FLOGC ;
TBPAR2.ITMAX = 25 ;
TBPAR2.EPS = 1.D-4 ;
TBPAR2.NFI = 2 ;
TB4 = 'CHI2' TB1 TBPAR2 TBPARM ;
TAQU = TB4.AQUE ;
* conditions aux limites
LIMBAS = 'REDU' TAQU ('DOMA' MMBAS 'CENTRE') ;
BBBAS = 'BLOQ' ('DOMA' MMBAS 'CENTRE') 'TH' ;
* Table de données de TRANSPORT
TABTRAN = 'TABLE' ;
TABTRAN.SOUSTYPE = 'MOT' 'GEOCHIMIE' ;
TABTRAN.'MODELE' = MODHYB ;
TABTRAN.'DIFFUSION' = MAT1 ;
TABTRAN.'POROSITE' = 'MANU' 'CHPO' CETOT 1 'CK' PORO ;
TABTRAN.'CONVECTION' = QFACE ;
TABTRAN.'CHIMI1' = TB1 ;
TABTRAN.'TAQU' = 'TABLE' ;
TABTRAN.'TAQU'. 0 = TAQU ;
TABTRAN.ITMAX = 25;
TABTRAN.EPS = 1.D-4 ;
TABTRAN.NFI = 1 ;
TABTRAN.LOGC = 'TABLE' ;
TABTRAN.LOGC. 0 = CLOGC ;
TABTRAN.TOT = 'TABLE' ;
TABTRAN.TOT. 0 = CTOTC ;
TABTRAN.PRECISION = 5.E-3 ;
TABTRAN.SORTIE = 'MOTS' 'FION' 'SOLU' ;
TABTRAN.'BLOCAGE' = BBBAS ;
TABTRAN.'TRACE_IMPOSE' = 'CHARGEMENT' LIMBAS
                ('EVOL' 'MANU' ('PROG' 0. 450.) ('PROG' 1. 1.)) ;
TABTRAN.'SOURCE' = SOURC ;
TABTRAN.'PAS_DE_TEMPS' = DELTAT ;
TABTRAN.'TEMPS_FINAL' = TFINAL ;
TABTRAN.'THETA' = 1.D0 ;
* Calcul couplé transport/géochimie
CHITRNSP TABTRAN ;
* Controle des résultats
* Calcul théorique 1D (pour le NA+)
VITCENT = 'HVIT' MODHYB QFACE ;
UY = 'EXCO' VY VITCENT SCAL ;
XX YY = 'COOR' CETOT ;
YY = 'NOMC' YY SCAL ;
PETITT = TFINAL ;
DENO1 = (4. * PI * PETITT * D22C) ** 0.5 ;
DENO2 = (4. * PETITT * D22C) ** 0.5 ;
CXYT1 = QELEM0 / PORO / DENO1 ;
CXYT21 = ((YY -((UY / PORO) * PETITT)) / DENO2) ** 2 ;
CXYT2 = CXYT1 * ('EXP' (-1. * CXYT21)) ;
SC1 = CXYT2 * XVOLU ;
SCXYT = 'RESULT' SC1 ;
tttt = 'CHAINE' 'Concentration en NA+ le long de l axe au temps '
                   petitt ;
'TITRE' TTTT ;
EV100 = 'EVOL' CHPOI CXYT2 'SCAL' SEGAXE ;
* - Calcul de l'intégrale de la concentration de NA+ et comparaison
* à la valeur théorique (on compare l'intégrale et la valeur maximale)
ECXN = 'EXCO' W002 TABTRAN.'SOLU'. NBPAST 'SCAL' ;
SECX1 = ECXN * XVOLU ;
SECXN = 'RESULT' SECX1 ;
SS1 = 'EXTR' SCXYT 'SCAL' ('POINT' ('EXTR' SCXYT 'MAIL') 1) ;
SS2 = 'EXTR' SECXN 'SCAL' ('POINT' ('EXTR' SECXN 'MAIL') 1) ;
DIFS = ('ABS' (SS1 - SS2) ) / SS1;
'SI' (DIFS < 1.D-2) ;
   'ERREUR' 0 ;
'SINON' ;
   'ERREUR' 5 ;
'FINSI' ;
MAECXN = 'MAXIMUM' ECXN ;
MACXYT2 = 'MAXIMUM' CXYT2 ;
DIFFNA = 'ABS' (ECXN - CXYT2) ;
MADIFF = 'MAXIMUM' DIFFNA ;
ERRDIF = MADIFF / MACXYT2 ;
'SI' (ERRDIF > 1.D-1) ;
   'ERREUR' 5 ;
'FINSI' ;
* Post-traitement graphique
'SI' GRAPH ;
  EV51 = 'EVOL' 'VERT' CHPOI ECXN 'SCAL' SEGAXE ;
  'DESSIN' (ev51 'ET' ev100) ;
  MOTIA = 'CHAINE' 'Concentration le long de l axe'
                     ' pour différents temps ';
  LLTMP = 'LECT' 0 'PAS' 10 NBPAST ;
  LISMD = 'MOTS' 'W002' ;
  NE1 NE2 = NOESPCHI TB1 W002 ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' NE2 ;
  TBDES = TRACHIS TABTRAN 'SOLU' LLTMP LISMD ('MOTS' NO1) SEGAXE ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' MOTIA ;
  LISMD = 'MOTS' 'X050' ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NOMINT' X050 ;
  TBDES = TRACHIS TABTRAN 'AQUE' LLTMP LISMD ('MOTS' NO1) SEGAXE ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' MOTIA ;
  LISMD = 'MOTS' 'X005' ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NOMINT' X005 ;
  LISMD = 'MOTS' 'X112' ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NOMINT' X112 ;
  LISMD = 'MOTS' 'W001' ;
  NE1 NE2 = NOESPCHI TB1 W001 ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' NE2 ;
  TBDES = TRACHIS TABTRAN 'SOLU' LLTMP LISMD ('MOTS' NO1) SEGAXE ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' MOTIA ;
  LISMD = 'MOTS' 'W002' ;
  NE1 NE2 = NOESPCHI TB1 W002 ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' NE2 ;
  TBDES = TRACHIS TABTRAN 'SOLU' LLTMP LISMD ('MOTS' NO1) SEGAXE ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' MOTIA ;
  TBN = 'TABLE' ;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' 50 ;
  TBN.1 = NO1;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' 5 ;
  TBN.2 = NO1;
  NO1 NO2 NO3 = NOCOMCHI TB1 'NUMCOMP' 112 ;
  TBN.3 = NO1;
  MO1 NO1 = NOESPCHI TB1 50 ;
  MO2 NO2 = NOESPCHI TB1 5 ;
  MO3 NO3 = NOESPCHI TB1 112 ;
  LISMD = 'MOTS' MO1 MO2 MO3 ;
  CETOP = 'DOMA' MMTOP 'CENTRE' ;
  XXTOP YYTOP= 'COOR' CETOP ;
  YCTOP = 'EXTR' YYTOP 'SCAL' ('POINT' ('EXTR' YYTOP 'MAIL') 1) ;
  TITOP = CHAIN 'Evolution en fonction du temps a '
                  'FORMAT' '(F6.3)' YCTOP 'metres' ;
  TBDES = TRACHIT TABTRAN 'SOLU' LISMD TBN CETOP ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' TITOP ;
  LISMD = 'MOTS' 'X050' 'X005' 'X112' ;
  TBDES = TRACHIT TABTRAN 'AQUE' LISMD TBN CETOP ;
  DESTRA TBDES 'MIMA' 'LOGO' 'DATE' 'TITRE' TITOP ;
'FINSI' ;
'FIN' ;
```

## smithhutton_impl [Fluides Transport]
```
* Convection/Diffusion : CAS SMITH ET HUTTON
* REFERENCE : NUMERICAL HEAT TRANSFER, VOL.5, p.439, 1982
* Les faces latérales et supérieure d'une boite rectangulaire sont
* imperméables. Le fluide rentre et sort de la boite par la face
* inférieure. Il rentre par la moitié gauche de la face inférieure
* et sort par la moitié droite de cette même face.
* Le champ de vitesse est connu et donné par :
* v(x,y) = 2y(1-x2) i - 2x(1-y2) j
* la taille de la boite étant [-1,1]x[0,1]
* L'écoulement transporte un scalaire passif qui est injecté en entrée
* suivant le profil :
* c(x,0) = 1 + tanh(10(2x+1))
* avec x variant de -1 à 0 (entrée du domaine).
* Sur les frontières imperméables du domaine, la concentration est
* constante et égale à 1-tanh(10).
* On cherche la solution stationnaire du transport par diffusion et
* convection du champ scalaire passif. On compare la solution en sortie
* avec la solution de référence. Plusieurs solutions sont calculées
* suivant le Peclet (rapport entre la convection et la diffusion).
* Résolution (implicite) de l'équation stationnaire
'OPTI' 'DIME' 2 'ISOV' 'SULI' ;
* USER DATA - USER DATA - USER DATA - USER DATA - USER DATA - USER DATA
* Pe : Peclet (convection sur diffusion)
* Les cas traités dans la référence sont 10, 100, 500, 1000 et 1000000
Pe = 1000000 ;
* KSUPG : Option de décentrement (CENTREE/SUPG/SUPGDC)
* GRAPH : Booleen pour l'affichage des tracés à l'issue du calcul
* NX : Nombre de maille suivant x
* NY : Nombre de maille suivant y
* tolera : Tolérance pour la comparaison avec la solution de référence
KSUPG = 'CENTREE' ;
GRAPH = faux ;
'OPTI' 'ELEM' 'QUA4' ;
NY = 20 ;
NX = 2 * NY ;
tolera = 0.0002 ;
* USER DATA - USER DATA - USER DATA - USER DATA - USER DATA - USER DATA
* - MAILLAGE
* Points
A1 = -1.0 0.0 ;
A2 = 1.0 0.0 ;
A3 = 1.0 1.0 ;
A4 = -1.0 1.0 ;
A0 = 0.0 0.0 ;
* Lignes
LIN = A1 'DROI' NY A0 ;
LOUT = A0 'DROI' NY A2 ;
FBAS = LIN 'ET' LOUT ;
FDRO = A2 'DROI' NY A3 ;
FHAU = A3 'DROI' NX A4 ;
FGAU = A4 'DROI' NY A1 ;
LIMP = FDRO 'ET' FHAU 'ET' FGAU ;
* Maillage
DOMTOT = 'DALL' FBAS FDRO FHAU FGAU 'PLAN' ;
CNT1 = 'CONT' DOMTOT ;
* Modèles et sous-modèles
DOM2 = 'CHAN' 'QUAF' DOMTOT ;
LIN2 = 'CHAN' 'QUAF' LIN ;
LIMP2 = 'CHAN' 'QUAF' LIMP ;
$DOMTOT = 'MODE' DOM2 'NAVIER_STOKES' 'LINE' ;
$LIN = 'MODE' LIN2 'NAVIER_STOKES' 'LINE' ;
$LIMP = 'MODE' LIMP2 'NAVIER_STOKES' 'LINE' ;
* Récupération des maillages et fusion des supports
DOMTOT = 'DOMA' $DOMTOT 'MAILLAGE' ;
LIN = 'DOMA' $LIN 'MAILLAGE' ;
LIMP = 'DOMA' $LIMP 'MAILLAGE' ;
FDOMTOT = 'DOMA' $DOMTOT 'FACE' ;
CLIN = 'DOMA' $LIN 'CENTRE' ;
CLIMP = 'DOMA' $LIMP 'CENTRE' ;
'ELIM' FDOMTOT (CLIN 'ET' CLIMP) 1.D-3 ;
* Champ de vitesse
XX YY = 'COOR' DOMTOT ;
VXSH = (2.*YY)*(1.0-(XX*XX)) ;
VYSH = (-2.*XX)*(1.0-(YY*YY)) ;
VX0 = 'NOMC' 'UX' VXSH ;
VY0 = 'NOMC' 'UY' VYSH ;
VX = 'KCHT' $DOMTOT 'SCAL' 'SOMMET' 'COMP' 'UX' VX0 ;
VY = 'KCHT' $DOMTOT 'SCAL' 'SOMMET' 'COMP' 'UY' VY0 ;
CHVIT = 'KCHT' $DOMTOT 'VECT' 'SOMMET' 'COMP' 'UX' 'UY' (VX 'ET' VY) ;
* Diffusion (1/Pe)
DIF = 1.0 / ('FLOT' Pe) ;
* Profil de concentration à l'entrée
XBAS = 'COOR' 1 LIN ;
TOTO = 2.0*XBAS + 1.0 * 10. ;
SOLUTION = 'TANH' TOTO ;
SOLUTION = 1.0 + SOLUTION ;
CHP1 = 'KCHT' $LIN 'SCAL' 'SOMMET' 0. SOLUTION ;
CHP1 = 'NOMC' 'CN' CHP1 ;
* Conditions aux limites en concentration sur les frontières imperméables
C1 = (1.0 - (TANH 10.0)) ;
* Description du problème de transport
RV1 = 'EQEX' $DOMTOT 'ITMA' 1 'ALFA' 0.7
      'OPTI' 'EF' 'IMPL' KSUPG
* 'ZONE' $DOMTOT 'OPER' 'TSCAL' DIF 'VITESSE' 0. 'INCO' 'CN'
      'ZONE' $DOMTOT 'OPER' 'LAPN' DIF 'INCO' 'CN'
      'ZONE' $DOMTOT 'OPER' 'KONV' 1. 'VITESSE' DIF 'INCO' 'CN'
;
* Description des conditions aux limites
RV1 = 'EQEX' RV1
      'CLIM' 'CN' 'TIMP' LIN CHP1
      'CLIM' 'CN' 'TIMP' LIMP C1 ;
* Description des conditions initiales
RV1 . 'INCO' = TABLE 'INCO' ;
RV1 . 'INCO' . 'CN' = 'KCHT' $DOMTOT 'SCAL' 'SOMMET' 0. ;
* Autres data
RV1 . 'INCO' . 'VITESSE' = CHVIT ;
RV1 . 'INCO' . 'CN2' = 'KCHT' $DOMTOT 'SCAL' 'SOMMET' 0. ;
RV1 . 'INCO' . 'IT' = 'PROG' ;
RV1 . 'INCO' . 'TI' = 'PROG' ;
RV1 . 'INCO' . 'ER' = 'PROG' ;
* - CALCUL
EXEC RV1 ;
* - ANALYSE DES RESULTATS
EVOL1 = 'EVOL' 'CHPO' (RV1 . 'INCO' . 'CN') 'SCAL' FBAS ;
EVOL2 = 'EVOL' 'CHPO' XX 'SCAL' FBAS ;
LIX = 'EXTR' EVOL2 'ORDO' ;
LIU = 'EXTR' EVOL1 'ORDO' ;
EVOL3 = 'EVOL' 'MANU' 'X' LIX 'C(X,0)' LIU ;
* Solutions de référence
LIXT = PROG 0. 0.1 0.2 0.3 0.4 0.5 0.6 0.7 0.8 0.9 1.0 ;
SI ( Pe 'EGA' 10 ) ;
LIUT = PROG 1.989 1.402 1.146 0.946 0.775 0.621 0.480 0.349
            0.227 0.111 0.000 ;
FINSI ;
SI ( Pe 'EGA' 100 ) ;
LIUT = PROG 2.000 1.940 1.836 1.627 1.288 0.869 0.480 0.209
            0.070 0.017 0.000 ;
FINSI ;
SI ( Pe 'EGA' 500 ) ;
LIUT = PROG 2.000 2.000 1.998 1.965 1.702 0.947 0.242 0.023
            0.001 0.000 0.000 ;
FINSI ;
SI ( Pe 'EGA' 1000 ) ;
LIUT = PROG 2.000 2.000 2.000 1.985 1.841 0.951 0.154 0.001
            0.000 0.000 0.000 ;
FINSI ;
SI ( Pe 'EGA' 1000000 ) ;
LIUT = PROG 2.000 2.000 2.000 1.999 1.964 1.000 0.036 0.001
            0.000 0.000 0.000 ;
FINSI ;
EVOL4 = EVOL 'MANU' 'X' LIXT 'Uref(X,0)' LIUT ;
LIUC = IPOL LIXT LIX LIU ;
NP = DIME LIXT ;
ERR0 = 0. ;
REPETER BLOC1 NP ;
    UCAL = EXTRAIRE LIUC &BLOC1 ;
    UREF = EXTRAIRE LIUT &BLOC1 ;
    ERR0 = ERR0 + ((UCAL-UREF)*(UCAL-UREF)) ;
FIN BLOC1 ;
ERR0 = ERR0/NP ;
ERR0 = ERR0 '**' 0.5 ;
* - POST-TRAITEMENT
'SI' GRAPH ;
* Maillage
'TRAC' DOMTOT 'TITR' 'Maillage' ;
* Vitesse
UNCH = 'VECT' CHVIT 0.1 'UX' 'UY' 'ROUGE' ;
'TRAC' UNCH DOMTOT CNT1 'TITR' 'Vitesse transportante' ;
* Concentration
'TRAC' DOMTOT (RV1 . 'INCO' . 'CN') CNT1 'TITR' 'Concentration' ;
* Comparaison avec la solution analytique
TAB1 = TABLE ;
TAB1 . TITRE = TABLE ;
TAB1. TITRE . 1 = 'MOT' 'CAST3M' ;
TAB1. TITRE . 2 = 'MOT' 'REFERENCE' ;
TAB1. 2 = 'MARQ LOSA NOLI' ;
'TITR' 'Comparaison CAST3M/Référence' ;
'DESS' (EVOL3 ET EVOL4) 'LEGE' TAB1
       'MIMA' 'XBOR' -1.0 1.0 'YBOR' -1.0 3.0 ;
FINSI ;
* Arret si problème
SI ( ERR0 > tolera ) ;
    'MESS' 'Erreur de ' err0 ' > ' tolera ;
    ERREUR 5 ;
FINSI ;
'MESS' 'Erreur de ' err0 ' < ' tolera ;
FIN ;
```

## fsi2 [Fluides Vibration]
```
* CAS TEST DU 91/10/04 PROVENANCE : PETI
* Test fsi2.dgibi: jeux de données
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
* TEST FSI2
* CYLINDRICAL FLUID CAVITY WITHOUT
* FREE SURFACE
* Calculation of the acoustic frequencies,
* for m = 1, of cylindrical water volume
* of radius 1.43m and height 1.039m
* P8+----------+P5
* P7+----------+P6
* The boundary conditions are
* dp |
* ---- | = 0
* dz | h = 0.
* dp |
* ---- | = 0
* dr | r = R
TEMPS;
OPTI DIME 2;
OPTI MODE FOUR 1;
OPTI ELEM QUA4;
* geometry
* Dimensions en metres
* Points
P5 = 1.43 1.039 ;
P6 = 1.43 0.0 ;
P7= 0. 0. ;
P8 = 0. 1.039 ;
N1 = 10 ;
S4 = P6 D N1 P5 ; S5 =P7 D N1 P6 ;
S6 = P7 D N1 P8 ; S7 =P8 D N1 P5 ;
WATER = DALL S4 S5 S6 S7 QUELC ;
* OPTIO FOR TRACE
SI (NEG GRAPH 'N');
  TITR ' FSI2 : MAILLAGE';
  TRAC QUAL (WATER ET (0 0));
FINSI;
* MODE - materiau - rigidite - masse
MODLIQ = MODE WATER LIQUIDE LQU4 ;
MATLIQ = MATE MODLIQ
         RHO 1.E3 RORF 1.E3 CSON 1435.
         CREF 1435. LCAR 1 G 0.;
RIG1 = RIGI MODLIQ MATLIQ ;
MAS1 = MASS MODLIQ MATLIQ ;
* boundary conditions
* No explicit boundary condition
* the boundary conditions are natural .
* calculation of the frequencies
* and
* extraction of some results
* Use the operator VIBR. (option PROC)
FRE1 = TABLE;
FRE1.1 = 294.06;
FRE1.2 = 750.56;
LIST1 = PROG FRE1.1 FRE1.2 ;
RESUL = VIBR PROC LIST1 RIG1 MAS1 ;
* results
MESS ' RESULTATS ';
MESS ' --------- ';
SAUT 1 LIGN;
FRE2 = TABL;
MOD = TABL;
DEF = TABL;
ERG = TABL;
I = 0;
REPETER BLOC1 2;
  I = I + 1;
  FRE2.I = RESUL . MODES . I . FREQUENCE;
  ERG.I = 100 *
        (ABS ((FRE1.I - FRE2.I) / FRE1.I));
  MESS ' MODE ' I ;
  MESS ' ----------';
  MESS 'Frequence theorique :' FRE1.I 'Hz';
  MESS 'Frequence calculee  :' FRE2.I 'Hz';
  MESS '    Soit un ecart de : ' ERG.I '%';
  SAUT 1 LIGN;
FIN BLOC1;
* code validation
ERGMAX = MAXI (PROG ERG.1 ERG.2 );
SI (ERGMAX <EG 5.);
   ERRE 0;
SINON;
   ERRE 5;
FINSI;
SAUT 1 LIGN;
TEMPS;
SAUT 1 LIGN;
FIN;
```

## fsi7 [Fluides Vibration]
```
* Cas test FSI7
* Calcul d'une masse ajoutee en mode de Fourier
* (lame fluide)
* creation : D. Combescure Décembre 2006
* rem (bp) : - la structure n'est pas modelisee
* - on impose un deplacement de translation harmonique
* sur l'interface (raccord)
* +-------+ rac2| fluide |
* |fluide |rac2 | |
GRAPH = FAUX;
* GRAPH = VRAI; OPTI TRAC PSC ;
COMPLET = FAUX;
* COMPLET = VRAI;
opti dime 2 elem qua4 mode four 1;
* MAILLAGE
HH1 = 9.D-3;
R1 = 7.85D-3;
h1 = 0.3D-3;
HH2 = 20.D-3;
R2 = 10.D-3;
h2 = 0.6D-3;
SI COMPLET;
 nz12 = 10;
 nz1 = 10;
 nx1 = 5;
 nx2 = 5;
SINON;
 nz12 = 1;
 nz1 = 1;
 nx1 = 1;
 nx2 = 1;
FINSI;
p1 = 0. 0.;
p2 = (R1 - h1) 0.;
p3 = (R1 + h1) 0.;
surbas1 = droi nx1 p2 p3;
p4 = (R2 - h2) 0.;
p5 = (R2 + h2) 0.;
surbas2 = droi nx2 p4 p5;
p3s = p3 plus (0. 0.);
p4s = p4 plus (0. 0.);
sursol = droi 1 p3s p4s;
vz1= 0. HH1;
p2h = p2 plus (0.5*vz1);
p3h = p3 plus (0.5*vz1);
p4h = p4 plus (0.5*vz1);
p5h = p5 plus (0.5*vz1);
p2b = p2 plus (-0.5*vz1);
p3b = p3 plus (-0.5*vz1);
p4b = p4 plus (-0.5*vz1);
p5b = p5 plus (-0.5*vz1);
vz12= 0. (HH2 - HH1);
p4h2 = p4h plus (0.5*vz12);
p5h2 = p5h plus (0.5*vz12);
p4b2 = p4b plus (-0.5*vz12);
p5b2 = p5b plus (-0.5*vz12);
volint1 = ((tran surbas1 nz1 (0.5*vz1)) et
          (tran surbas1 nz1 ((-0.5)*vz1))) coul BLEU;
volint2 = ( ((tran surbas2 nz1 (0.5*vz1)) et
          (tran (surbas2 plus (0.5*vz1)) nz12 (0.5*vz12)))
       et ((tran surbas2 nz1 ((-0.5)*vz1)) et
          (tran (surbas2 plus ((-0.5)*vz1)) nz12 ((-0.5)*vz12)))
          ) coul AZUR;
volsol = ((tran sursol nz1 (0.5*vz1)) et
          (tran (sursol plus (0.5*vz1)) nz12 (0.5*vz12)) et
          (tran sursol nz1 ((-0.5)*vz1)) et
          (tran (sursol plus ((-0.5)*vz1)) nz12 ((-0.5)*vz12)))
            COUL ROUGE;
SI GRAPH;
 trac (volsol et volint1 et volint2);
FINSI;
surint = (d nz1 p2 p2h)
      et (d nz1 p2 p2b);
surint2 = (d nz1 p3 p3h)
      et (d nz1 p3 p3b);
surext = (d nz1 p4 p4h) et (d nz12 p4h p4h2)
      et (d nz1 p4 p4b)
      et (d nz12 p4b p4b2);
surext2 = (d nz1 p5 p5h) et (d nz12 p5h p5h2)
      et (d nz1 p5 p5b)
      et (d nz12 p5b p5b2);
surver1 = (surbas1 plus (0.5*vz1))
      et (surbas1 plus (-0.5*vz1));
surver2 = (surbas2 plus (0.5*(vz1 plus vz12)))
      et (surbas2 plus (-0.5*(vz1 plus vz12)));
elim 0.0001
   (surint et surint2 et surext et surext2
     et volint1 et volint2 et surver1 et surver2);
surextb = surext plus (0. 0.);
surint2b = surint2 plus (0. 0.);
elim 0.0001
   (surint2b et surextb et volsol);
SI GRAPH;
 trac (surint et surext et surint2 et surext2
    et volint1 et volint2 et volsol);
FINSI;
* MODELE DE FLUIDE
ro1 = 800.;
cf1 = 343.;
mod1 = MODE (volint1) liquide lqu4;
mat1 = MATE mod1 rho ro1 rorf ro1
                 cson cf1 cref cf1 lcar 1.D-3 g 0.;
mod2 = MODE (volint2) liquide lqu4;
mat2 = MATE mod2 rho ro1 rorf ro1
                 cson cf1 cref cf1 lcar 1.D-3 g 0.;
rig1 = rigi (mod1 et mod2) (mat1 et mat2);
mas1 = mass (mod1 et mod2) (mat1 et mat2);
blfl = bloq UR UT UZ
  (surint et surext2 );
blflI = bloq IUR IUT IUZ
  (surint et surext2 );
blfl2 = bloq UZ
  (surver1 et surver2);
blfl2I = bloq IUZ
  (surver1 et surver2);
opti elem rac2;
mrac2 = racc 0.0001 (surext) (surextb);
mrac1 = racc 0.0001 (surint2) (surint2b);
modrac1 = MODE mrac1 mecanique liquide rac2;
matrac1 = cara modrac1 liqu volint1;
modrac2 = MODE mrac2 mecanique liquide rac2;
matrac2 = cara modrac2 liqu volint2;
modliq = MODE (volint1 et volint2) liquide lqu4;
matliq = MATE (modliq et modrac1 et modrac2) rho ro1 rorf ro1
                 cson cf1 cref cf1 lcar 1. g 0.;
modtot = modrac1 et modrac2 et modliq;
mattot = matrac1 et matrac2 et matliq;
* MATRICES
bl1 = bloq UR UT UZ (surext2 et surint);
bl2ur = bloq UR (surextb et surint2b);
bl2ut = bloq UT (surextb et surint2b);
bl2uz = bloq UZ (surextb et surint2b);
bl1I = bloq IUR IUT IUZ (surext2 et surint);
bl2Iur = bloq IUR (surextb et surint2b);
bl2Iut = bloq IUT (surextb et surint2b);
bl2Iuz = bloq IUZ (surextb et surint2b);
dep1ur = depi bl2ur 1.;
dep1ut = depi bl2ut -1.;
Ktot = rigi modtot mattot;
Mtot = mass modtot mattot;
Mimpe = 'IMPE' Mtot 1. 'MASSE';
Kimpe = 'IMPE' Ktot 'RAIDEUR';
* CALCULS : REPONSE HARMONIQUE
SI COMPLET;
 prfreq = prog 10 pas 10. 1000.;
SINON;
 prfreq = prog 100 pas 100. 1000.;
FINSI;
prFR = prog;
prFT = prog;
repeter lab1 (dime prfreq);
 fr1 = extr prfreq &lab1;
 ImpTot = Kimpe et (((2.*pi*fr1)**2)*Mimpe)
       et bl1 et bl2ur et bl2ut et bl2uz et
   bl1I et bl2Iur et bl2Iut et bl2Iuz et blfl et blflI
   et blfl2 et blfl2I;
 deptot = reso ImpTot (dep1ur et dep1ut);
 reatot = reac deptot (bl2ur et bl2ut);
 prFR = prfr et (prog (maxi (exco (resu reatot) FR)));
 prFT = prft et (prog (maxi (exco (resu reatot) FT)));
fin lab1;
evfr = evol manu prfreq prfr;
evft = evol manu prfreq prft;
mm = 57.6d-3;
evfrma = evol rouge manu prfreq ((-1.)*((2.*pi*prfreq)**2)*mm);
TEST = ABS ((SOMM ((extr evfrma ordo) - (extr evfr ordo)))/
       (SOMM (extr evfrma ordo)));
SI GRAPH;
 trac (volint1 et volint2) (exco deptot 'P');
 trac (volint1 et volint2) (vecteur reatot 'FR' 'FZ');
 dess (evfr et evfrma);
FINSI;
* POST TRAITEMENT VIA FOUR2TRI
* rem : les elements raccords (RAC2) ne seront traites par FOUR2TRI
tab1 = table;
tab1.'MODELE' = modrac1 et modrac2 et modliq;
tab1.'ANGLES' = prog 0. pas 10. 270.;
tab1.'CHPO_SYME' = TABLE;
tab1.'CHPO_SYME'. 1 = exco deptot 'P' 'SCAL';
tab1.'EFFORTS' = TABLE;
tab1.'EFFORTS'. 1 = reatot;
FOUR2TRI tab1 1;
mesh3d1 = tab1 . 'MAILLAGE_3D';
SI GRAPH;
 trac mesh3D1 (tab1.'CHPO_SYME_3D'. 1 );
 trac mesh3D1 (vect (tab1.'EFFORTS_3D'. 1 ) FX FY FZ);
FINSI;
* TEST ET FIN DU CAS-TEST
SI (TEST >EG 1.d-2);
 ERRE 5;
FINSI;
TEMP IMPR MAXI CPU ;
FIN ;
```

## INTG_test_integration_reduite [Langage]
```
* Cas-test de calculs d'integrales avec les elements a integration
* reduite C20R et P15R
OPTI 'DIME' 3 'ELEM' 'CU20';
XZPREC = (VALE 'PREC') * 100.;
* CUBE C20R
P1 = 0. 0. 0.;
P2 = 1. 0. 0.;
D1 = DROI 1 P1 P2;
S1 = D1 TRAN 1 (0. 1. 0.);
V1 = S1 VOLU 'TRAN' 1 (0. 0. 1.);
* TRAC V1;FIN;
MO = MODE V1 'MECANIQUE' 'ELASTIQUE' 'C20R';
* VOLUME A PARTIR D’UN CHAMP CONSTANT
UN = MANU 'CHML' MO 'SCAL' 1.;
VOL = INTG MO UN;
ECART = ABS (VOL - 1.);
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP CONSTANT';
    ERRE 5;
FINSI;
* CHAMP LINEAIRE
Z = COOR 3 UN;
RES = INTG MO Z;
ECART = ABS (RES - 0.5);
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP LINEAIRE';
    ERRE 5;
FINSI;
* CHAMP QUADRATIQUE
RES = INTG MO (Z**2);
ECART = ABS (RES - (1./3.));
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP QUADRATIQUE';
    ERRE 5;
FINSI;
* PRISME P15R
P1 = 0. 0. 0.;
P2 = 1. 0. 0.;
P3 = 0. 1. 0.;
D1 = DROI 1 (DROI 1 (DROI 1 P1 P2) P3) P1;
S1 = SURF 'PLAN' D1;
V1 = S1 VOLU 'TRAN' 1 (0. 0. 1.);
* TRAC V1;FIN;
MO = MODE V1 'MECANIQUE' 'ELASTIQUE' 'P15R';
* VOLUME A PARTIR D’UN CHAMP CONSTANT
UN = MANU 'CHML' MO 'SCAL' 1.;
VOL = INTG MO UN;
ECART = ABS (VOL - 0.5);
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP CONSTANT';
    ERRE 5;
FINSI;
* CHAMP LINEAIRE
Z = COOR 3 UN;
RES = INTG MO Z;
ECART = ABS (RES - 0.25);
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP LINEAIRE';
    ERRE 5;
FINSI;
* CHAMP QUADRATIQUE
RES = INTG MO (Z**2);
ECART = ABS (RES - (1./6.));
MESS ECART XZPREC;
SI (ECART > XZPREC);
    MESS 'ERREUR DANS INTG POUR UN CHAMP QUADRATIQUE';
    ERRE 5;
FINSI;
FIN;
```

## evol_comp [Langage Base]
```
* PRESENTATION
* Ce cas-test permet de tester
* 1- le bon fonctionnement des differentes combinaisons de l'operateur
* 'EVOL' avec l'option 'COMP'
* 2- le bon fonctionnement de l'operateur 'LIST' de ces combisaisons
* 3- le bon fonctionnement de l'operateur 'DESS' de ces combisaisons
* 4- le bo fonctionnement de l'operateur 'RIMP'
 OPTI TRAC 'PSC';
LAB1 = PROG 1 2 3 4 5 ;
LRE1 = PROG 1. 0. -2.2 3. -1.E+5 ;
LIM1 = PROG 0. 5. -2.2 4. 0.E+5 ;
LAB2 = LAB1 ;
LMO2 = PROG 1. 5. (2.2*(2.**0.5)) +5. +1.E+5 ;
LPH2 = PROG 0. +90. -135. (ATG(4./3.)) +180. ;
EVR1 = 'EVOL' 'COMP' 'REIM' LAB1 LRE1 LIM1 ;
EVR2 = 'EVOL' 'COMP' 'MOPH' LAB2 LMO2 LPH2 ;
EVC2 = RIMP EVR1 ;
EVC3 = RIMP EVC2 ;
LIST EVC3 ;
LIST EVC2 ;
EV0 = 'ABS' (EVC3 - EVR1) ;
ra1 = 'MAXIMUM' ('EXTRAIRE' ev0 'ORDO' 1) ;
EV0 = RIMP EV0 ;
ra2 = 'MAXIMUM' ('EXTRAIRE' ev0 'ORDO' 1) ;
'SI' (('>' ra1 1.E-15) 'OU' ('>' ra2 5.E-11)) ;
  'ERREUR' 'TEST 1 RATE' ;
'FINSI' ;
EV0 = 'ABS' (EVC2 - EVR2) ;
ra1 = 'MAXIMUM' ('EXTRAIRE' ev0 'ORDO' 1) ;
'SI' ('>' ra1 1.E-15) ;
  'ERREUR' 'TEST 2 RATE' ;
'FINSI' ;
EV0 = RIMP EV0 ;
ra1 = 'MAXIMUM' ('EXTRAIRE' ev0 'ORDO' 1) ;
ra2 = 'MAXIMUM' ('EXTRAIRE' ev0 'ORDO' 2) ;
'SI' (('>' ra1 1.E-15) 'OU' ('>' ra2 1.E-15)) ;
  'ERREUR' 'TEST 3 RATE' ;
'FINSI' ;
FIN ;
```

## evol_manu [Langage Base]
```
* PRESENTATION
* Ce cas-test permet de tester
* 1- le bon fonctionnement des differentes combinaisons de l'operateur
* 'EVOL' avec l'option 'MANU'
* 2- le bon fonctionnement de l'operateur 'LIST' de ces combisaisons
* 3- le bon fonctionnement de l'operateur 'DESS' de ces combisaisons
* Creation : 09/03/2016
* Createur : C. BERTHINIER
* Modifications :
* IDENTIFI JJ/MM/AAAA : ...
 OPTI TRAC 'PSC';
* Fabrication des differentes listes : LISTMOTS, LISTREEL, LISTENTI
LMO1 = MOTS 'row ' ' =  ' 'Curv' 'absc' ;
LMO2 = MOTS 'row ' ' =  ' 'Curv' 'ordi' ;
LRE1 = PROG 1. 2. 3. 4. ;
LRE2 = PROG 1. 4. 9. 16. ;
LEN1 = LECT 5 6 7 8 ;
LEN2 = LECT 9 10 11 12 ;
* Fabrication des 9 combinaisons d'EVOLUTIO possibles
EV11 = 'EVOL' 'MANU' LMO1 LMO2;
EV12 = 'EVOL' 'MANU' LMO1 LRE1;
EV13 = 'EVOL' 'MANU' LMO1 LEN1;
EV21 = 'EVOL' 'MANU' LRE1 LMO2;
EV22 = 'EVOL' 'MANU' LRE1 LRE2;
EV23 = 'EVOL' 'MANU' LRE1 LEN1;
EV31 = 'EVOL' 'MANU' LEN1 LMO2;
EV32 = 'EVOL' 'MANU' LEN1 LRE2;
EV33 = 'EVOL' 'MANU' LEN1 LEN2;
EVTOT = EV11 ET EV12 ET EV13 ET
        EV21 ET EV22 ET EV23 ET
        EV31 ET EV32 ET EV33 ;
LIST EVTOT;
DESS EVTOT;
FIN;
```

## chan2 [Langage Fonctionnement]
```
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
GRAPH = 'N' ;
OPTI ECHO 1 ;
SAUT PAGE ;
SI (NEG GRAPH 'N');
  OPTI TRAC X ;
SINO ;
  OPTI TRAC PSC ;
FINSI ;
SAUT PAGE;
* NOM : CHAN2
* DESCRIPTION : Teste l'operateur CHANGER pour les cas suivants :
* - changer un MCHAML en MCHAML avec CHAN 'CHAM' ...
* - changer un CHPOINT en CHPOINT avec CHAN 'CHPO' ...
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Clément BERTHINIER (CEA/DEN/DM2S/SEMT/LM2S)
* mél : clement.berthinier@cea.fr
* VERSION : v1, 02/02/2015, version initiale
* HISTORIQUE : v1, 02/02/2015, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
* Création d'un maillage
OPTI DIME 3 ;
OPTI ELEM SEG2;
NEZ = 2 ;
P1= 0. 0. 0. ;
P2= 1. 0. 0. ;
L1= DROI NEZ P1 P2 ;
L2= L1 PLUS (0. 1. 0.);
OPTI ELEM QUA4 ;
S1= REGL L1 NEZ L2 ;
OPTI ELEM CUB8 ;
V1= VOLU S1 TRAN NEZ (0. 0. 1.);
SI(NEG GRAPH 'N');
  TRAC CACH V1 ;
FINSI ;
* Création d'un CHPOINT
X Y Z = COOR V1 ;
CHPO1 = X + (Y**2) + (Z**3) ;
list resu chpo1 ;
* Création d'un MMODEL de MECANIQUE
MODE1 = MODE V1 MECANIQUE ELASTIQUE ISOTROPE;
* Création de différents types de MCHAML : Supports différents
CHAM1 = CHAN 'CHAM' CHPO1 MODE1 ;
CHAM2 = CHAN 'NOEUD' CHAM1 MODE1 ;
CHAM3 = CHAN 'GRAVITE' CHAM1 MODE1 ;
CHAM4 = CHAN 'MASSE' CHAM1 MODE1 ;
CHAM5 = CHAN 'STRESSES' CHAM1 MODE1 ;
lister resu cham1 ;
lister resu cham2 ;
lister resu cham3 ;
lister resu cham4 ;
lister resu cham5 ;
* Passage d'un MCHAML a un MCHAML avec la syntaxe : CHAN 'CHAM' ...
* Ce cas peut se présenter en thermique avec des chargements sous
* forme de CHPOINT ou MCHAML indifféremment
* Par défaut le support est aux 'NOEUD'
CHAM12 = CHAN 'CHAM' CHAM1 MODE1 ;
CHAM22 = CHAN 'CHAM' CHAM2 MODE1 ;
CHAM32 = CHAN 'CHAM' CHAM3 MODE1 ;
CHAM42 = CHAN 'CHAM' CHAM4 MODE1 ;
CHAM52 = CHAN 'CHAM' CHAM5 MODE1 ;
lister resu cham12 ;
lister resu cham22 ;
lister resu cham32 ;
lister resu cham42 ;
lister resu cham52 ;
zz = 'ABS' (cham12 '-' cham1) ;
lister resu zz ; list (mini zz) ; list (maxi zz) ;
zz = 'ABS' (cham22 '-' cham1) ;
lister resu zz ; list (mini zz) ; list (maxi zz) ;
zz = 'ABS' (cham42 '-' cham1) ;
lister resu zz ; list (mini zz) ; list (maxi zz) ;
zz = 'ABS' (cham52 '-' cham1) ;
lister resu zz ; list (mini zz) ; list (maxi zz) ;
* Passage d'un MCHAML a un MCHAML avec la syntaxe : CHAN 'CHAM' ...
* Ce cas peut se présenter en thermique avec des chargements sous
* forme de CHPOINT ou MCHAML indifféremment
* Par défaut le support est aux 'NOEUD'
* Changement d'un MCHAML vers MCHAML en changeant Support
CHAM13 = CHAN 'CHAM' CHAM1 MODE1 'RIGIDITE' ;
CHAM23 = CHAN 'CHAM' CHAM2 MODE1 'RIGIDITE' ;
CHAM33 = CHAN 'CHAM' CHAM3 MODE1 'RIGIDITE' ;
CHAM43 = CHAN 'CHAM' CHAM4 MODE1 'RIGIDITE' ;
CHAM53 = CHAN 'CHAM' CHAM5 MODE1 'RIGIDITE' ;
lister resu cham13 ;
lister resu cham23 ;
lister resu cham33 ;
lister resu cham43 ;
lister resu cham53 ;
* Changement d'un MCHAML vers MCHAML en changeant Support ordre changé
CHAM14 = CHAN 'CHAM' 'RIGIDITE' CHAM1 MODE1 ;
CHAM24 = CHAN 'CHAM' 'RIGIDITE' CHAM2 MODE1 ;
CHAM34 = CHAN 'CHAM' 'RIGIDITE' CHAM3 MODE1 ;
CHAM44 = CHAN 'CHAM' 'RIGIDITE' CHAM4 MODE1 ;
CHAM54 = CHAN 'CHAM' 'RIGIDITE' CHAM5 MODE1 ;
lister resu cham14 ;
lister resu cham24 ;
lister resu cham34 ;
lister resu cham44 ;
lister resu cham54 ;
* Changement d'un MCHAML vers MCHAML en changeant Support et Type (vide)
CHAM15 = CHAN 'CHAM' CHAM1 MODE1 'RIGIDITE' 'SCAL_A1';
CHAM25 = CHAN 'CHAM' CHAM2 MODE1 'RIGIDITE' 'SCAL_B1';
CHAM35 = CHAN 'CHAM' CHAM3 MODE1 'RIGIDITE' 'SCAL_C1';
CHAM45 = CHAN 'CHAM' CHAM4 MODE1 'RIGIDITE' 'SCAL_D1';
CHAM55 = CHAN 'CHAM' CHAM5 MODE1 'RIGIDITE' 'SCAL_E1';
lister resu cham15 ;
lister resu cham25 ;
lister resu cham35 ;
lister resu cham45 ;
lister resu cham55 ;
* Changement d'un MCHAML vers MCHAML en changeant Support et Type (plein)
CHAM16 = CHAN 'CHAM' CHAM15 MODE1 'STRESSES' 'SCAL_A2';
CHAM26 = CHAN 'CHAM' CHAM25 MODE1 'STRESSES' 'SCAL_B2';
CHAM36 = CHAN 'CHAM' CHAM35 MODE1 'STRESSES' 'SCAL_C2';
CHAM46 = CHAN 'CHAM' CHAM45 MODE1 'STRESSES' 'SCAL_D2';
CHAM56 = CHAN 'CHAM' CHAM55 MODE1 'STRESSES' 'SCAL_E2';
lister resu cham16 ;
lister resu cham26 ;
lister resu cham36 ;
lister resu cham46 ;
lister resu cham56 ;
* Changement d'un CHPOINT vers MCHAML en spécifiant le Support
CHAM17 = CHAN 'CHAM' CHPO1 MODE1 'NOEUD' ;
CHAM27 = CHAN 'CHAM' CHPO1 MODE1 'GRAVITE' ;
CHAM37 = CHAN 'CHAM' CHPO1 MODE1 'STRESSES' ;
CHAM47 = CHAN 'CHAM' CHPO1 MODE1 'MASSE' ;
CHAM57 = CHAN 'CHAM' CHPO1 MODE1 'RIGIDITE' ;
lister resu cham17 ;
lister resu cham27 ;
lister resu cham37 ;
lister resu cham47 ;
lister resu cham57 ;
* Changement d'un CHPOINT vers MCHAML en spécifiant le Support et Type
CHAM18 = CHAN 'CHAM' CHPO1 MODE1 'NOEUD' 'SCALAIRE';
CHAM28 = CHAN 'CHAM' CHPO1 MODE1 'GRAVITE' 'SCALAIRE';
CHAM38 = CHAN 'CHAM' CHPO1 MODE1 'STRESSES' 'SCALAIRE';
CHAM48 = CHAN 'CHAM' CHPO1 MODE1 'MASSE' 'SCALAIRE';
CHAM58 = CHAN 'CHAM' CHPO1 MODE1 'RIGIDITE' 'SCALAIRE';
lister resu cham18 ;
lister resu cham28 ;
lister resu cham38 ;
lister resu cham48 ;
lister resu cham58 ;
* Changement d'un MCHAML vers CHPOINT en spécifiant un MAILLAGE
CHAM19 = CHAN 'CHAM' CHPO1 V1;
lister resu cham19 ;
* Passage d'un CHPOINT a un CHPOINT avec la syntaxe : CHAN 'CHPO' ...
* Ce cas peut se présenter en thermique avec des chargements sous
* forme de CHPOINT ou MCHAML indifféremment
* Le MMODEL est alors OPTIONNEL
* Changement d'un CHPOINT vers CHPOINT sans le modèle (inutile en fait)
CHPO2 = CHAN 'CHPO' CHPO1 ;
* Changement d'un CHPOINT vers CHPOINT en donnant le Modèle (inutilisé)
CHPO3 = CHAN 'CHPO' CHPO1 MODE1 ;
* Changement d'un CHPOINT vers MCHAML sans la méthode (MOYE, SOMM)
CHPO4 = CHAN 'CHPO' CHAM1 MODE1 ;
* Changement d'un CHPOINT vers MCHAML avec la méthode (MOYE, SOMM)
CHPO5 = CHAN 'CHPO' CHAM1 MODE1 'MOYE';
LIST RESU CHPO5;
* Changement d'un CHPOINT vers MCHAML sans la méthode (MOYE, SOMM)
CHPO6 = CHAN 'CHPO' CHAM1 MODE1 'SOMM';
LIST RESU CHPO6;
FIN;
```

## cinema1 [Langage Objets]
```
graph = 'N';
* Example of use of the cinema procedure
* A mesh is made of 4 arches: we want to pass under the 3 first arches,
* go around the 4th and go under the 4 arches.
* P.PEGON JRC-ISPRA 01/05/95
opti echo 1;
opti dime 3 elem qua4;
* generation of the mesh "mesht"
dens 1.;
dens 2.5;
p1=0 5 0; p2=0 10 0; p3=0 10 15; p4=0 -10 15;
p5=0 -10 0; p6=0 -5 0; p7=0 -5 10; p8=0 5 10;
cont1=p1 d p2 d p3 d p4 d p5 d p6 d p7 d p8 d p1;
mesh1=cont1 surf plan;
opti elem cub8;
p9=5 0 0;
mesh2=coul (mesh1 volu tran p9) bleu;
mesh3=coul (mesh2 plus (10 0 0)) vert;
mesh4=coul (mesh3 plus (10 0 0)) roug;
mesh5=coul (mesh4 plus (25 0 0)) turq;
mesht=mesh2 et mesh3 et mesh4 et mesh5;
* generation of the point of view trajectory (traj1)
* and of the associated direction of view (dire1)
ptra1=-15 2.5 2.5;
ptra2=30 2.5 2.5;
ptra3=45 17.5 2.5;
ptra4=60 2.5 2.5;
ptra5=0 2.5 2.5;
pcent=45 2.5 2.5;
traj1=ptra1 d ptra2;
cerc2=ptra2 pcent ptra3 c;
cerc2=cerc2 pcent ptra4 c;
traj3=ptra4 d pcent d ptra5;
trajt=traj1 et cerc2 et traj3;
traj0='CHAN' cerc2 'POI1';
grav1=bary mesh5;
j=0; repe lab1 (nbel traj0); j=j+1;
  oeilj=(traj0 elem j) point 1;
  direj=grav1 moin oeilj;
  si (j ega 1); dire1=direj;
  sinon; dire1=dire1 et direj; finsi;
fin lab1;
dirini=(dire1 elem 1 ) point 1;
dirfin=(dire1 elem (nbel dire1)) point 1;
repe lab1 (nbel traj1);
  dire1=dirini et dire1;
fin lab1;
repe lab1 (nbel traj3);
  dire1=dire1 et dirfin;
fin lab1;
traj1='CHAN' trajt 'POI1';
j=0; repe lab1 (nbel traj1); j=j+1;
  oeilj=(traj1 elem j) point 1;
  direj=(dire1 elem j) point 1;
  xd1 yd1 zd1=coor direj;
  vdirj=manu chpo oeilj 3 'UX' xd1 'UY' yd1 'UZ' zd1 nature discret;
  si (ega j 1); vdir1=vdirj;
  sinon; vdir1=vdir1 et vdirj; finsi;
fin lab1;
vvdir1=vecto vdir1 0.2 'UX' 'UY' 'UZ' jaun;
 si ( ega graph 'O');
trac (1000 10000 10000) cach (mesht et trajt) vvdir1;
trac (1000 1000 10000) cach (mesht et trajt) vvdir1;
  finsi;
* call cinema
axet1=0 0 1;
 si ( ega graph 'O');
defo1=cinema mesht traj1 dire1 axet1;
  finsi;
* plot
* WARNING: start the animation, stop it clicking in the same place,
* and resize the plot on the current frame in order to
* eliminate useless details by clipping
* (the dream is to exclude from the vision all what is cut)
oeil1=(traj1 elem 1) point 1;
opc11=(dire1 elem 1) point 1;
opc12=axet1;
opc11=opc11/(norm opc11);
opc12=opc12 moin ( (opc11 psca opc12) * opc11 );
opc12=opc12/(norm opc12);
opc13=opc11 pvec opc12;
pc11=oeil1 plus (2*opc11);
pc12=pc11 plus opc12;
pc13=pc11 plus opc13;
mena;
 si ( ega graph 'O');
trac oeil1 defo1 face dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 facb dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 fsdb dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 cach dire coup pc11 pc12 pc13 oscil;
finsi;
fin ;
```

## cinemb1 [Langage Objets]
```
graph = 'N';
* Example of use of the cinemb procedure
* A mesh is made of 1 arches: we want to pass under turning and rising
* the head.
* P.PEGON JRC-ISPRA 01/10/95
opti echo 1;
opti dime 3 elem qua4;
* generation of the mesh "mesht"
dens 2.5;
p1=0 5 0; p2=0 10 0; p3=0 10 15; p4=0 -10 15;
p5=0 -10 0; p6=0 -5 0; p7=0 -5 10; p8=0 5 10;
cont1=p1 d p2 d p3 d p4 d p5 d p6 d p7 d p8 d p1;
mesh1=cont1 surf plan;
opti elem cub8;
p9=6 0 0;
mesht=coul (mesh1 volu tran p9) bleu;
depl mesht 'PLUS' (-3 0 0);
* generation of the point of view trajectory (traj1)
* and of the associated direction of view (dire1)
* and direction of head axis (axet1)
ptra1=-15 0. 0.;
ptra2= 15 0. 0.;
traj1=chan (ptra1 d 30 ptra2) 'POI1';
j=0; repe lab1 (nbel traj1); j=j+1;
  oeilj=(traj1 elem j) point 1;
  xj =coor 1 oeilj;
  direj= ((-1)*xj) 0. 10.;
  direj=direj/(norm direj);
  axe1j=10. 0. xj; axe1j=axe1j/(norm axe1j);
  axe2j= 0. 1. 1.;
  alpha=xj/15.;
  axetj=(alpha*axe1j) plus ((1-(abs alpha))*axe2j);
  axetj=axetj/(norm axetj);
  xj yj zj=coor direj;
  vdirj=manu 'CHPO' oeilj 3 'UX' xj 'UY' yj 'UZ' zj nature discret;
  xj yj zj=coor axetj;
  vtetj=manu 'CHPO' oeilj 3 'UX' xj 'UY' yj 'UZ' zj nature discret;
  si (ega j 1); dire1=direj; axet1=axetj;
                vdir1=vdirj; vtet1=vtetj;
  sinon; dire1=dire1 et direj; axet1=axet1 et axetj;
                vdir1=vdir1 et vdirj; vtet1=vtet1 et vtetj;
  finsi;
fin lab1;
vvdir1=vecto vdir1 1 'UX' 'UY' 'UZ' jaun;
vvtet1=vecto vtet1 1 'UX' 'UY' 'UZ' vert;
SI ( ega graph 'O');
trac (100 10 100) cach (mesht et traj1) (vvdir1 et vvtet1);
* call cinemb
defo1=cinemb mesht traj1 dire1 axet1;
finsi;
* plot
* WARNING: start the animation, stop it clicking in the same place,
* and resize the plot on the current frame in order to
* eliminate useless details by clipping
* (the dream is to exclude from the vision all what is cut)
oeil1=(traj1 elem 1) point 1;
opc11=(dire1 elem 1) point 1;
opc12=(axet1 elem 1) point 1;;
opc11=opc11/(norm opc11);
opc12=opc12 moin ( (opc11 psca opc12) * opc11 );
opc12=opc12/(norm opc12);
opc13=opc11 pvec opc12;
pc11=oeil1 plus (2*opc11);
pc12=pc11 plus opc12;
pc13=pc11 plus opc13;
mena;
si ( ega graph 'O');
trac oeil1 defo1 face dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 facb dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 fsdb dire coup pc11 pc12 pc13 oscil;
trac oeil1 defo1 cach dire coup pc11 pc12 pc13 oscil;
finsi;
fin ;
```

## deda [Langage Objets]
```
'OPTI' 'ECHO' 0 ;
* Cas test pour l'operateur DEDAns
* On test le resultat de l'operateur DEDA sur des points sur des
* points situes a l'exterieur et a l'interieur d'un contour (2D) et
* d'une enveloppe (3D)
* Le maillage utilise est non convexe et non connexe (2 parties)
* On teste avec des points :
* - franchement loin du bord
* - tres pres du bord
* - colineaire/coplanaire a un element du bord
* - situes sur le bord (face, arete, sommet)
* - appartenant au bord (noeud du bord)
* Indicateur pour le trace
itrac = FAUX ;
* Distance pour placer des points "tres pres" du bord
* si l'on reduit cette distance, il convient d'adapter le critere de
* l'operateur DEDA en le choisissant plus eleve que la valeur par
* defaut
epsi = 1.E-5 ;
* EN DIMENSION 2
'OPTI' 'DIME' 2 'ELEM' 'SEG2' ;
'MESS' ;
'MESS' '*************************' ;
'MESS' '       DIMENSION 2' ;
'MESS' '*************************' ;
'MESS' ;
* Maillage du contour oriente convenablement : les trous internes
* tournent dans le sens oppose du cadre exterieur
p0 = 0. 0. ;
p1 = 8. 0. ;
p2 = 8. 8. ;
p3 = 4. 4. ;
p4 = 0. 8. ;
ne1 = 10 ;
cadre = p0 'DROI' ne1 p1 'DROI' ne1 p2 'DROI' ne1 p3 'DROI' ne1 p4
           'DROI' ne1 p0 ;
p5 = 2. 2. ;
p6 = 3. 2. ;
cerc1 = 'LIGN' 20 p5 p6 -360. 'ROTA' ;
'ELIM' 1.E-9 cerc1 ;
cont1 = cadre 'ET' cerc1 ;
* Table de points a l'exterieur et a l'interieur
tpe = 'TABL' 'ESCLAVE' ;
tpe . 1 = -1. -1. ;
tpe . 2 = 4. 6. ;
tpe . 3 = 2.5 2.7 ;
tpe . 4 = 1.5 1.5 ;
tpe . 5 = p3 'PLUS' (0. epsi) ;
tpe . 6 = (-1. * epsi) 4. ;
tpe . 7 = 15. 15. ;
tpe . 8 = 0. 10. ;
tpe . 9 = 10. 0. ;
mpe = ('ET' tpe) 'COUL' 'ROUG' ;
tpi = 'TABL' 'ESCLAVE' ;
tpi . 1 = 4. 3. ;
tpi . 2 = 6. 2. ;
tpi . 3 = 2. epsi ;
tpi . 4 = (8. - epsi) 4. ;
tpi . 5 = 5. 0. ;
tpi . 6 = 1. 7. ;
tpi . 7 = 4. 4. ;
tpi . 8 = 8. 0. ;
tpi . 9 = p0 ;
tpi . 10 = p2 ;
mpi = ('ET' tpi) 'COUL' 'VERT' ;
'SI' itrac ;
  'TRAC' (cont1 'ET' mpe 'ET' mpi)
    'TITR' 'Point ext. (rouge) et points int. (vert)' ;
'FINSI' ;
* Test si les points sont bien a l'exterieur du contour
'MESS' '***** Resultat de DEDA pour les points a l exterieur' ;
'REPE' b1 (('DIME' tpe) - 2) ;
  pe1 = tpe . &b1 ;
  log1 = 'DEDA' pe1 cont1 ;
  'LIST' log1 ;
  'SI' log1 ;
    'MESS' '***** ECHEC  du cas test !' ;
    'MESS' 'Le ' &b1 'ieme point exterieur est detecte a l interieur' ;
    'LIST' pe1 ;
    'ERREUR' 5 ;
  'FINSI' ;
'FIN' b1 ;
* Test si les points sont bien a l'interieur du contour
'MESS' ;
'MESS' '***** Resultat de DEDA pour les points a l interieur' ;
'REPE' b1 (('DIME' tpi) - 2) ;
  pi1 = tpi . &b1 ;
  log1 = 'DEDA' pi1 cont1 ;
  'LIST' log1 ;
  'SI' ('NON' log1) ;
     'MESS' '***** ECHEC  du cas test !' ;
    'MESS' 'Le ' &b1 'ieme point interieur est detecte a l exterieur' ;
    'LIST' pi1 ;
    'ERREUR' 5 ;
  'FINSI' ;
'FIN' b1 ;
'MESS' ;
'MESS' ;
* EN DIMENSION 3
'OPTI' 'DIME' 3 'ELEM' 'TRI3' ;
'MESS' ;
'MESS' '*************************' ;
'MESS' '       DIMENSION 3' ;
'MESS' '*************************' ;
'MESS' ;
* Maillage de l'enveloppe par revolution du contour precedent
p7 = 0. 10. 0. ;
p8 = 1. 10. 0. ;
ne2 = 10 ;
sur1 = 'SURF' cont1 'PLAN' ;
sur1 = 'ORIE' sur1 'POIN' (0. 0. -1.) ;
env1 = cont1 'ROTA' ne2 90. p7 p8 ;
cont2 = env1 'COTE' 3 ;
sur2 = 'SURF' cont2 'PLAN' ;
sur2 = 'ORIE' sur2 'POIN' (0. 1. 0.) ;
env1 = env1 'ET' sur1 'ET' sur2 ;
* Table de points a l'exterieur et a l'interieur
tpe = 'TABL' 'ESCLAVE' ;
tpe . 1 = 1. 1. 1. ;
tpe . 2 = -1. 10. -2. ;
tpe . 3 = (2. 2. 0.) 'TOUR' 40. p7 p8 ;
tpe . 4 = 4. 2. epsi ;
tpe . 5 = 3. (10. + epsi) -6. ;
tpe . 6 = (env1 'POIN' 'PROC' (p3 'TOUR' 65. p7 p8)) 'PLUS'
           (0. 0. epsi) ;
tpe . 7 = 2. 8. 0. ;
tpe . 8 = 0. 10. 0. ;
tpe . 9 = 2. 2. 0. ;
mpe = ('ET' tpe) 'COUL' 'ROUG' ;
tpi = 'TABL' 'ESCLAVE' ;
tpi . 1 = 4. 3. -1. ;
tpi . 2 = 7. 8. -5. ;
tpi . 3 = 2. (10. - epsi) -5. ;
tpi . 4 = (env1 'POIN' 'PROC' (p3 'TOUR' 80. p7 p8)) 'MOIN'
           (0. 0. epsi) ;
tpi . 5 = 3. 4. 0. ;
tpi . 6 = 8. 10. -8. ;
tpi . 7 = 0. 0. 0. ;
tpi . 8 = (env1 'POIN' 'PROC' (p6 'TOUR' 30. p7 p8)) 'PLUS'
           (0. 0. 0.) ;
tpi . 9 = env1 'POIN' 'PROC' (p3 'TOUR' 45. p7 p8) ;
tpi . 10 = p6 ;
mpi = ('ET' tpi) 'COUL' 'VERT' ;
'SI' itrac ;
  are1 = 'ARET' env1 ;
  'TRAC' (are1 'ET' mpe 'ET' mpi)
    'TITR' 'Point ext. (rouge) et points int. (vert)' ;
'FINSI' ;
* Test si les points sont bien a l'exterieur du contour
'MESS' '***** Resultat de DEDA pour les points a l exterieur' ;
'REPE' b1 (('DIME' tpe) - 2) ;
  pe1 = tpe . &b1 ;
  log1 = 'DEDA' pe1 env1 ;
  'LIST' log1 ;
  'SI' log1 ;
    'MESS' '***** ECHEC  du cas test !' ;
    'MESS' 'Le ' &b1 'ieme point exterieur est detecte a l interieur' ;
    'LIST' pe1 ;
    'ERREUR' 5 ;
  'FINSI' ;
'FIN' b1 ;
* Test si les points sont bien a l'interieur du contour
'MESS' ;
'MESS' '***** Resultat de DEDA pour les points a l interieur' ;
'REPE' b1 (('DIME' tpi) - 2) ;
  pi1 = tpi . &b1 ;
  log1 = 'DEDA' pi1 env1 ;
  'LIST' log1 ;
  'SI' ('NON' log1) ;
     'MESS' '***** ECHEC  du cas test !' ;
    'MESS' 'Le ' &b1 'ieme point interieur est detecte a l exterieur' ;
    'LIST' pi1 ;
    'ERREUR' 5 ;
  'FINSI' ;
'FIN' b1 ;
* Fin normale du cas test
'MESS' ;
'MESS' ;
'MESS' ;
'MESS' '***** SUCCES du cas test !' ;
'FIN' ;
```

## deduad1d [Langage Objets]
```
'OPTI' 'ECHO' 0 ;
* NOM : DEDUAD1D
* DESCRIPTION : cas-test élémentaire 1D pour 'DEDU' 'ADAP'
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 21/09/2005, version initiale
* HISTORIQUE : v1, 21/09/2005, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
'SAUTER' 2 'LIGNE' ;
'MESSAGE' ' Execution de deduad1d.dgibi' ;
'SAUTER' 2 'LIGNE' ;
interact= FAUX ;
graph = FAUX ;
debug = FAUX ;
* BEGINPROCEDUR cas1d
* NOM : CAS1D
* DESCRIPTION : Construit les cas pour deduadap 1D
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 15/12/2004, version initiale
* HISTORIQUE : v1, 15/12/2004, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
'DEBPROC' CAS1D ;
'ARGUMENT' mesh*'ENTIER' ;
'ARGUMENT' nbmail2*'ENTIER' ;
'ARGUMENT' disc/'MOT' ;
'SI' ('NON' ('EXISTE' disc)) ;
   disc = 'LINE' ;
'FINSI' ;
'SI' ('<' nbmail2 1) ;
   cherr = 'CHAINE' 'Nombre de mailles inférieur à 2...' ;
   'ERREUR' cherr ;
'FINSI' ;
nbmail = '*' nbmail2 2 ;
'SI' ('EGA' disc 'LINE') ;
   'OPTION' 'ELEM' 'SEG2' ;
'SINON' ;
   'OPTION' 'ELEM' 'SEG3' ;
'FINSI' ;
pA = 'POIN' 0. ;
pB = 'POIN' 1. ;
pC = 'POIN' 0.5 ;
'SI' ('OU' ('EGA' mesh 1) ('EGA' mesh 3)) ;
   mt = 'ET' ('DROIT' pA pC nbmail2) ('DROIT' pC pB nbmail2) ;
'FINSI' ;
'SI' ('EGA' mesh 2) ;
   mt = 'ET' ('DROIT' pA pC ('-' nbmail 1))
             ('DROIT' pC pB 1) ;
'FINSI' ;
* Blocages
rigblo = 'BLOQUE' 'UX' (pA 'ET' pB) ;
cblo = 'DEPIMPOSE' rigblo 0. ;
* Cas QUAF
'SI' ('EGA' disc 'QUAF') ;
   mt = 'CHANGER' mt 'QUAF' ;
   _mt = mt ;
'SINON' ;
   _mt = 'CHANGER' mt 'QUAF' ;
'FINSI' ;
* Métrique
'SI' ('ET' ('>EG' mesh 1) ('<EG' mesh 2)) ;
   met = 'CHAINE' 'rien' ;
'FINSI' ;
'SI' ('EGA' mesh 3) ;
   $mt = 'MODELISER' _mt 'NAVIER_STOKES' 'QUAF' ;
   mtc = 'DOMA' $mt 'CENTRE' ;
   xmt = 'COORDONNEE' mtc ;
   g11 = 'NOMC' 'G11' ('+' ('*' xmt 100.) 1.) ;
* cg11 = 'CHANGER' 'CHAM' g11 $mt 'NOEUD' ;
   met = g11 ;
'FINSI' ;
'RESPRO' mt _mt met rigblo cblo ;
* End of procedure file CAS1D
'FINPROC' ;
* ENDPROCEDUR cas1d
'OPTION' 'DIME' 1 ;
'SI' ('NON' interact) ;
  'OPTION' 'TRAC' 'PS' ;
'SINON' ;
  'OPTION' 'TRAC' 'X' ;
'FINSI' ;
* Pour les tests, on regarde les valeurs max. des indicateurs
* d'isotropie et d'equidistribution
lmaiso = 'PROG' ;
lmaequ = 'PROG' ;
* Ici les valeurs de référence
lok = VRAI ;
idx = 0 ;
lmaisor = 'PROG' 9 * 1.0 ;
lmaequr = 'PROG' 9 * 1.0 ;
* Maillage :
* mesh = 1 : maillage régulier
* mesh = 2 : maillage concentré à gauche
* mesh = 3 : maillage régulier + métrique concentrée à gauche
* nbmail2 : nombre de mailles divisé par 2
* 'QUAI' : quadratique incomplet (mécanique)
* 'QUAF' : quadratique fluide
tdisc = 'TABLE' ;
tdisc . 1 = 'LINE' ;
tdisc . 2 = 'QUAI' ;
tdisc . 3 = 'QUAF' ;
'REPETER' idisc 3 ;
   'REPETER' imesh 3 ;
      iidisc = &idisc ;
      iimesh = &imesh ;
      gdisc = tdisc . iidisc ;
      'SI' ('EGA' iidisc 1) ;
         nbmail2 = 16 ;
      'SINON' ;
         nbmail2 = 8 ;
      'FINSI' ;
* Maillage
      mail _mt met mblo cblo = CAS1D iimesh nbmail2 gdisc ;
      mes = 'CHAINE' 'mesh=' iimesh ' ; ' gdisc ;
      'MESSAGE' mes ;
      'SI' graph ;
         tit = 'CHAINE' 'Maillage initial ' mes ;
         'SI' interact ;
            'TRACER' mail 'TITR' tit 'NOEU' ;
         'SINON' ;
            'TRACER' mail 'TITR' tit 'NOEU' 'NCLK' ;
         'FINSI' ;
      'FINSI' ;
* adaptation
      'SI' ('EGA' ('TYPE' met) 'CHPOINT ') ;
         dep = 'DEDU' 'ADAP' _mt mblo cblo 'DISG' gdisc
                             'METR' met 'CSTE' debug ;
      'SINON' ;
         dep = 'DEDU' 'ADAP' _mt mblo cblo 'DISG' gdisc debug ;
      'FINSI' ;
* tracé
      orig = 'FORME' ;
      'FORME' dep ;
      'SI' ('EGA' ('TYPE' met) 'CHPOINT ') ;
         ciso = DEADUTIL 'QISO' _mt gdisc 'GAU7' met 'CSTE' ;
         cequ = DEADUTIL 'QEQU' _mt gdisc 'GAU7' met 'CSTE' ;
      'SINON' ;
         ciso = DEADUTIL 'QISO' _mt gdisc 'GAU7' ;
         cequ = DEADUTIL 'QEQU' _mt gdisc 'GAU7' ;
      'FINSI' ;
      maciso = 'MAXIMUM' ciso ; miciso = 'MINIMUM' ciso ;
      macequ = 'MAXIMUM' cequ ; micequ = 'MINIMUM' cequ ;
      'MESSAGE' ('CHAINE' 'CISO : max. = ' maciso '  min. = ' miciso) ;
      'MESSAGE' ('CHAINE' 'CEQU : max. = ' macequ '  min. = ' micequ) ;
* Tests
      lmaiso = 'ET' lmaiso ('PROG' maciso) ;
      lmaequ = 'ET' lmaequ ('PROG' macequ) ;
      idx = '+' idx 1 ;
      visor='EXTRAIRE' lmaisor idx ;
      tiso = ('<' maciso ('*' visor 1.01)) ;
      'SI' ('NON' tiso) ;
         cherr = 'CHAINE' '!!! Erreur, on aurait voulu max. ciso. < '
                          visor ;
         'MESSAGE' cherr ;
      'FINSI' ;
      lok = 'ET' lok tiso ;
      vequr='EXTRAIRE' lmaequr idx ;
      tequ = ('<' macequ ('*' vequr 1.01)) ;
      'SI' ('NON' tequ) ;
         cherr = 'CHAINE' '!!! Erreur, on aurait voulu max. cequ. < '
                          vequr ;
         'MESSAGE' cherr ;
      'FINSI' ;
      lok = 'ET' lok tequ ;
      'SI' graph ;
         tit = 'CHAINE' 'Maillage final ' mes ;
         'SI' interact ;
            'TRACER' mail 'TITR' tit 'NOEU' ;
         'SINON' ;
            'TRACER' mail 'TITR' tit 'NOEU' 'NCLK' ;
         'FINSI' ;
      'FINSI' ;
      'FORME' orig ;
   'FIN' imesh ;
'FIN' idisc ;
* Fin du jeu de données
'SAUTER' 2 'LIGNE' ;
'SI' lok ;
   'MESSAGE' 'Tout sest bien passe' ;
'SINON' ;
   'MESSAGE' 'Il y a eu des erreurs' ;
'FINSI' ;
'SAUTER' 2 'LIGNE' ;
'SI' interact ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'FINSI' ;
* End of dgibi file DEDUAD1D
'FIN' ;
```

## dessin [Langage Objets]
```
* dessin.dgibi
* PROCEDURE WATERFALL (experimentale)
* tracé Waterfall Cast3M (experimental) ____
DEBP WATERFALL ev1*'EVOLUTION' y1*'LISTREEL'
               moty1/'MOT' moopt1/'LISTMOTS' zcoef1/'FLOTTANT';
* initialisations
  ZLOGY = FAUX;
* recup des entrees + verif
  n1 = DIME ev1;
  si (neg n1 (dime y1)); ERRE 625; finsi;
  si (neg (type moty1) (MOT 'MOT')); moty1='\c'; finsi;
  si (ega (type moopt1) (MOT 'LISTMOTS'));
* veut-on changer l'echelle de y1
* (sans toucher a celle des evolutions) ?
    ZLOGY = EXIS moopt1 'LOGY';
  finsi;
  si (neg (type zcoef1) (MOT 'FLOTTANT')); zcoef1=1.; finsi;
* calcul du facteur alpha
* recherche de l'amplitude des evolutions
  lindic1 lx1 lf1 = MAXI 'ABS' ev1;
* maxf1 = MAXI 'ABS' lf1;
  maxf1 = (SOMM (ABS lf1)) / n1;
* recherche des espaces inter-y
  si ZLOGY;
    y1log = LOG y1;
    dy1 = ((maxi y1log) - (mini y1log)) / (n1 - 1);
  sinon;
    dy1 = ((maxi y1) - (mini y1)) / (n1 - 1);
  finsi;
* calcul de alpha
  alpha1 = zcoef1 * dy1 / maxf1;
* creation d'une nouvelle evolution prete a tracer
* recup des parametres de l'evolution de depart
  coco1 = EXTR ev1 'COUL';
  xlabel1 = EXTR ev1 'LEGX' 1;
* ylabel1 = EXTR ev1 'LEGY' 1;
* on ordonne selon y1 decroissant
  li1 = lect 1 pas 1 n1;
  y2 li2 = ORDO 'DECROISSANT' y1 li1;
* boucle sur les evol elementaires --> nouvelle evol
  ev2 = VIDE 'EVOLUTIO';
  REPE BEV1 n1;
* choix de l'evol a traiter en premier
    i2 = EXTR li2 &BEV1;
    y2j = EXTR y2 &BEV1;
* dernier parametre : la couleur
    coco2 = EXTR coco1 i2;
    molege1 = CHAI moty1 '=' FORMAT '(G10.2)' y2j;
* recup des listreels
    xprog2 = EXTR ev1 'ABSC' i2;
    fprog1 = EXTR ev1 'ORDO' i2;
* application de alpha aux evolutions
    si ZLOGY;
* de maniere a avoir LOG(f2) = LOG(y) + a*f1
      fprog2 = y2j * (exp (alpha1 * fprog1));
    sinon;
* de maniere a avoir f2 = y + a*f1
      fprog2 = y2j + (alpha1 * fprog1);
    finsi;
* stockage
    ev2 = ev2 et (EVOL coco2 'MANU' 'LEGE' molege1 xlabel1 xprog2 moty1 fprog2);
  FIN BEV1;
FINP ev2;
* cas-test de la directive DESSIN.
  OPTI 'TRAC' 'PSC' 'EPTR' 5 ;
  OPTI 'POTR' 'HELVETICA_16' ;
* remarque : il faudrait aussi tester avec
* OPTI TRAC 'X';
* OPTI TRAC 'OPEN' ;
* CB : TESTE DES CAS PARTICULIERS AYANT CONDUIT A DES ERREURS PAR LE PASSE
* 1
X1 =PROG -2. PAS 1. 750. ;
Y1 =EXP (-1. * X1);
EV1 = EVOL 'ROUG' MANU X1 Y1;
Tit1= CHAI 'Y=Exp(-X) sur une large gamme de X avec YBOR [0. ; 1.]';
DESS EV1 TITR Tit1 YBOR 0. 1.;
* 2
X11 =PROG -2. PAS 1. 750. ;
Y11 =EXP (-1. * X11);
EV11 = EVOL 'ROUG' MANU Y11 X11;
Tit1 = CHAI 'X=Exp(-Y) sur une large gamme de Y avec XBOR [0. ; 1.]';
DESS EV11 TITR Tit1 XBOR 0. 1.;
* 3
X2 = PROG -1 0. 1. 1.;
Y2 = PROG -1 0. 1. 1.;
EV2 = EVOL 'ROUG' MANU X2 Y2;
Tit1 = CHAI 'Y=X avec YBOR [0. ; 1.]';
DESS EV2 TITR Tit1 YBOR 0. 1.;
* 4
X21 = PROG -1 0. 1. 1.;
Y21 = PROG -1 0. 1. 1.;
EV21 = EVOL 'ROUG' MANU Y21 X21;
Tit1 = CHAI 'X=Y avec XBOR [0. ; 1.]';
DESS EV21 TITR Tit1 XBOR 0. 1.;
* 5
X3 = PROG 0. 1. ;
Y3 = PROG -0.1 1.2 ;
EV3 = EVOL 'ROUG' MANU X3 Y3;
Tit1 = CHAI 'YBOR [0. ; 1.]';
DESS EV3 TITR Tit1 YBOR 0. 1.;
* 6
X31 = PROG 0. 1. ;
Y31 = PROG -0.1 1.2 ;
EV31 = EVOL 'ROUG' MANU Y31 X31;
Tit1 = CHAI 'XBOR [0. ; 1.]';
DESS EV31 TITR Tit1 XBOR 0. 1.;
* 7
X4 = PROG 0. 1. ;
Y4 = PROG 1.2 -1.2 ;
EV4 = EVOL 'ROUG' MANU X4 Y4;
Tit1 = CHAI 'YBOR [0. ; 1.]';
DESS EV4 TITR Tit1 YBOR 0. 1.;
* 8
X41 = PROG 0. 1. ;
Y41 = PROG 1.2 -1.2 ;
EV41 = EVOL 'ROUG' MANU Y41 X41;
Tit1 = CHAI 'XBOR [0. ; 1.]';
DESS EV41 TITR Tit1 XBOR 0. 1.;
* 9
X5 = PROG 0. ;
Y5 = PROG 1.2 ;
EV5 = EVOL 'ROUG' MANU X5 Y5;
Tit1 = CHAI '1 seul point en [0. ; 1.2] et YBOR [0. ; 1.]';
DESS EV5 TITR Tit1 YBOR 0. 1.;
* 10
X51 = PROG 0. ;
Y51 = PROG 1.2 ;
EV51 = EVOL 'ROUG' MANU Y51 X51;
Tit1 = CHAI '1 seul point en [1.2 ; 0.] et XBOR [0. ; 1.]';
DESS EV51 TITR Tit1 XBOR 0. 1.;
* 11
X6 = PROG 0. ;
Y6 = PROG 0.5 ;
EV6 = EVOL 'ROUG' MANU X6 Y6;
Tit1 = CHAI '1 seul point en [0. ; 0.5] et YBOR [0. ; 1.]';
DESS EV6 TITR Tit1 YBOR 0. 1.;
* 12
X61 = PROG 0. ;
Y61 = PROG 0.5 ;
EV61 = EVOL 'ROUG' MANU Y61 X61;
Tit1 = CHAI '1 seul point en [0.5 ; 0.] et XBOR [0. ; 1.]';
DESS EV61 TITR Tit1 XBOR 0. 1.;
* 13
X7 = PROG ;
Y7 = PROG ;
EV7 = EVOL 'ROUG' MANU X7 Y7;
Tit1 = CHAI 'Evolution vide et YBOR [0. ; 1.]';
DESS EV7 TITR Tit1 YBOR 0. 1.;
* 14
X71 = PROG ;
Y71 = PROG ;
EV71 = EVOL 'ROUG' MANU Y71 X71;
Tit1 = CHAI 'Evolution vide et XBOR [0. ; 1.]';
DESS EV71 TITR Tit1 XBOR 0. 1.;
* 15
X8 = LECT 1 2 3 4 ;
Y8 = PROG -1. 1. 2. 3. ;
EV8 = EVOL 'ROUG' MANU X8 Y8 ;
Tit1 = CHAI 'Evolution avec LISTENTI en ABSCISSE et LISTREEL en ORDONNEES';
DESS EV8 TITR Tit1 ;
* 16
X9 = LECT 1 2 3 4 ;
Y9 = LECT -1 1 2 3 ;
EV9 = EVOL 'ROUG' MANU X9 Y9 ;
Tit1 = CHAI 'Evolution avec LISTENTI en ABSCISSE et LISTENTI en ORDONNEES';
DESS EV9 TITR Tit1 ;
* 17
X10 = PROG 1. 2. 3. 4.;
Y10 = LECT -1 1 2 3 ;
EV10 = EVOL 'ROUG' MANU X10 Y10 ;
Tit1 = CHAI 'Evolution avec LISTREEL en ABSCISSE et LISTENTI en ORDONNEES';
DESS EV10 TITR Tit1 ;
* ON TESTE D'ABORD LES ECHELLE ET GRADUATIONS
* (SP)
EV1 = EVOL 'BLEU' 'MANU' (PROG -1. -0.5 0.5 1. 2.)
                              (PROG 1.E-3 0. 0. 5.E-4 7E-2) ;
DESS EV1 'TITR' ' Sans option' ;
DESS EV1 'XBOR' -1.5 2.5
'TITR' ' Bornes sur X [-1.5 2.5] ' ;
DESS EV1 'YBOR' -0.5E-2 7.5E-2
'TITR' ' Bornes sur Y [-0.5E-2 7.5E-2] ' ;
DESS EV1 'XBOR' -1.5 2.5 'YBOR' -0.5E-2 7.5E-2
'TITR' ' Bornes sur X & Y ' ;
DESS EV1 'XBOR' -1.5 2.5 'YBOR' -0.5E-2 7.5E-2
         'XGRA' +0.5 'YGRA' +0.5E-2
'TITR' ' Bornes sur X-Y & les intervalles de graduations donnes ' ;
DESS EV1 'XBOR' -1.5 2.5 'YBOR' -0.5E-2 7.5E-2
         'XGRA' +0.5 'YGRA' +0.5E-2
         'AXES' 'GRIL' 'POIN'
'TITR' ' La grille & les axes en PLUS ' ;
* ON TESTE ENSUITE D'AUTRES OPTIONS AVEC UN SYSTEME 2DDL
* LEGENDE, TITRES, CENTREMENT, GRILLE ...
* (BP)
* w donné en rad/s
T1=2.;
w1=(2.*pi)/T1;
T2=5.;
w2=(2.*pi)/T2;
xp = prog 0. PAS 0.1 20.;
* castem utilise les degrés
yp = 100. * (sin ((180/pi)*w1*xp));
yp2 = 110. * (sin ((180/pi)*w2*xp));
ev1 = evol bleu manu xp yp;
ev2 = evol roug manu xp yp2;
tdess1 = tabl;
tdess1 . 1 = mot ' REMP MARQ PLUS REGU';
tdess1 . 'TITRE' = tabl;
ent1 = enti w1;
decim1 = (enti (10.*w1)) - (10*ent1);
ent2 = enti w2;
decim2 = (enti (10.*w2)) - (10*ent2);
tdess1 . 'TITRE' . 1 = chai '\W=' ent1 '.' decim1 'rad.s^{-1}';
tdess1 . 2 = mot 'MARQ ROND REGU';
tdess1 . 'TITRE' . 2 = chai '\W=' ent2 '.' decim2 'rad.s^{-1}';
DESS (ev1 et ev2)
'TITR' 'Déplacement x_{\W}(t) = sin(\Wt)'
'TITX' 't(s)' 'POSX' 'CENT'
'TITY' 'Dépl u_{A}^{1} (m)' 'POSY' 'CENT'
'LEGE' 'SO' tdess1;
DESS (ev1 et ev2)
'TITR' 'Déplacement x_{\W}(t) = sin(\Wt)'
'TITX' 't(s)' 'POSX' 'CENT'
'YBOR' -110. 110. 'YGRA' 22
'TITY' 'Dépl u_{A} (m^{1})' 'POSY' 'CENT'
'LEGE' tdess1;
DESS (ev1 et ev2)
'TITR' 'Déplacement x_{\W}(t) = sin(\Wt)'
'TITX' 't(s)'
 'XBOR' 0. T2
 'YBOR' -110. 110. 'YGRA' 22.
'TITY' 'Déplacement x (m)'
'LEGE' tdess1;
* systeme 2ddl : fonction de tranfert : amplitude et phase
ev1tot = VIDE 'EVOLUTION';
ev2tot = VIDE 'EVOLUTION';
* liscoul = mots VIOL BLEU TURQ BLEU ORAN AZUR ROUG ;
liscoul = mots VIOL BLEU TURQ OLIV ORAN AZUR ROUG ;
tdess2 = tabl;
tdess2 . 1 = mot 'MARQ PLUS REGU';
tdess2 . 2 = mot 'MARQ ROND REGU';
tdess2 . 3 = mot 'MARQ CROI REGU';
tdess2 . 4 = mot 'MARQ CARR REGU';
tdess2 . 5 = mot 'MARQ TRIU REGU';
tdess2 . 6 = mot 'MARQ ETOI REGU';
tdess2 . 7 = mot 'MARQ TRID REGU';
tdess2 . 'TITRE' = tabl;
xi1 = 0.02 ; xi2 = 0.05;
xi1p = prog 0.001 0.002 0.01 0.02 0.05 0.1 0.15 ;
xi2p = xi1p * (xi2 / xi1);
nxi = dime xi1p;
ixi = 0;
repe Bxi nxi; ixi = ixi + 1 ;
xi1 = extr xi1p ixi;
xi2 = extr xi2p ixi;
mess ixi ' xi_1=' xi1 ' xi_2=' xi2 ;
moxi1 = chai (enti (1000 * (xi1 - (enti xi1))));
si (ega (dime moxi1) 1); moxi1 = chai '00' moxi1; fins;
si (ega (dime moxi1) 2); moxi1 = chai '0' moxi1; fins;
moxi1 = chai (enti xi1) '.' moxi1;
tdess2 . 'TITRE' . ixi = chai '\x_{1}=' (moxi1);
m1=2.; k1 = m1*(w1**2); c1 = 2.*xi1*w1*k1;
m2=1.; k2 = m2*(w2**2); c2 = 2.*xi2*w2*k2;
mess w1 m1 k1 c1;
mess w2 m2 k2 c2;
wpadim = prog 0. PAS 0.002 2.;
wp = w1 * wpadim;
np = dime wp;
unp = prog np*1.;
A_R = ((k1 + k2)*unp) - ((wp**2)*m1);
A_I = wp*(c1 + c2);
B_R = -1.*k2*unp;
B_I = -1.*c2*wp;
D_R = (k2*unp) - ((wp**2)*m2);
D_I = wp*c2;
Den_R = (A_R*D_R) - (A_I*D_I) - (B_R**2) + (B_I**2) ;
Den_I = (A_R*D_I) + (A_I*D_R) - (2.*B_R*B_I);
Den2 = (Den_R**2) + (Den_I**2);
* pour simplifier on excite seulement en F1 et en phase
F1_R = 1.;
Num11_R = ((Den_R*D_R) - (Den_I*D_I)) * F1_R;
Num11_I = ((Den_R*D_I) - (Den_I*D_R)) * F1_R;
Num12_R = -1.*((Den_R*B_R) - (Den_I*B_I)) * F1_R;
Num12_I = -1.*((Den_R*B_I) - (Den_I*B_R)) * F1_R;
X1_R = Num11_R / Den2;
X1_I = Num11_I / Den2;
X2_R = Num12_R / Den2;
X2_I = Num12_I / Den2;
X1_AMP = ((X1_R**2)+(X1_I**2))**0.5;
X1_PHA = ATG X1_I X1_R;
X2_AMP = ((X2_R**2)+(X2_I**2))**0.5;
X2_PHA = ATG X2_I X2_R;
ev1_amp = evol BLEU manu wpadim X1_AMP;
ev2_amp = evol ROUG manu wpadim X2_AMP;
ev1_pha = evol BLEU manu wpadim X1_PHA;
ev2_pha = evol ROUG manu wpadim X2_PHA;
si (xi1 ega 0.02);
tdess1 . 'TITRE' . 1 = mot 'X_{1}';
tdess1 . 'TITRE' . 2 = mot 'X_{2}';
* 'Y LOG + titres X et Y centres + LEGE XY'
tit2ddl = chai 'Système à 2ddl : '
 '\w_{1}=0.5 \w_{2}=0.2 \x_{1}=2% \x_{2}=5%';
DESS (ev1_amp et ev2_amp)
'LOGY' 'YBOR' 1.E-3 1.E1
'GRIL' 'POIN' 'GRIS'
'TITR' tit2ddl
'TITX' '\W (Hz)' 'POSX' 'CENT'
'TITY' 'amplitude |x| (m)' 'POSY' 'CENT'
'LEGE' 'XY' 1.5 0.8 tdess1;
DESS (ev1_pha et ev2_pha)
'YBOR' -180. 180. 'YGRA' 90.
'GRIL' 'POIN' 'GRIS'
'TITR' tit2ddl
'TITX' '\W (Hz)' 'POSX' 'CENT'
'TITY' 'phase \j(x) (m)' 'POSY' 'CENT'
'LEGE' 'XY' 1.5 160 tdess1;
fins;
ev1tot = ev1tot et (ev1_amp coul (extr liscoul ixi));
ev2tot = ev2tot et (ev2_amp coul (extr liscoul ixi));
fin Bxi;
* ON CONTINUE AVEC D'AUTRES OPTIONS
* (BP)
tit2 = chai 'Evolution avec l`amortissement \x';
DESS ev1tot
'GRIL' 'POIN' 'GRIS' 'TITR' tit2
'LOGY'
'TITX' '\W (Hz)' 'POSX' 'CENT'
'TITY' '|X_{1}| (m)' 'POSY' 'CENT'
'LEGE' 'XY' 1.45 9. tdess2;
* rem : 'amplitude |X_{1}| (m)' est trop long (limite a 20 caracteres)!
* 'TITY' 'amplitude |X_{1}| (m)' 'POSY' 'CENT'
* test de loption LIGNE_VARIABLE
* on définit les style des (np-1) segments
* (=0 lign, =2 tirr, ... =5 pointilles)
nps3 = np / 3;
ltirr2 = lect nps3*0 nps3*5 (np - 1 - (2*nps3))*1;
ltirr3 = lect nps3*1 nps3*2 (np - 1 - (2*nps3))*0;
tdess2 . 'LIGNE_VARIABLE' = TABL;
tdess2 . 'LIGNE_VARIABLE' . 2 = ltirr2;
tdess2 . 'LIGNE_VARIABLE' . 3 = ltirr2;
tdess2 . 'LIGNE_VARIABLE' . 5 = ltirr3;
DESS ev1tot
'GRIL' 'POIN' 'GRIS' 'TITR' tit2
 LOGY
'TITX' '\W (Hz)' 'POSX' 'CENT'
'TITY' '|X_{1}| (m)' 'POSY' 'CENT'
'LEGE' 'XY' 1.45 9. tdess2;
* test pour faire des waterfall (+ option REMP BLAN)
* (bp,2019)
* dess ev1tot;
ev1log = WATERFALL ev1tot xi1p '\x' (mots 'LOGY');
repe Bxi nxi;
  tdess2 . &Bxi = CHAI tdess2 . &Bxi ' REMP BLAN';
fin Bxi;
dess ev1log 'LOGY' 'LEGE' tdess2;
* trace d'histogrammes
* bruit blanc Gaussien
NN = 10000 ;
LTIRAG1 = BRUI 'BLAN' 'GAUS' 0. 2. NN ;
LTIRAG2 = BRUI 'BLAN' 'GAUS' 0. 2. NN ;
* calcul du nombre de classes (entieres)
IMAX1 = ENTI 'SUPERIEUR' (MAXI LTIRAG1);
IMIN1 = ENTI 'INFERIEUR' (MINI LTIRAG1);
* boucle sur les classes
NC = IMAX1 - IMIN1;
LCOMPT1 = PROG NC*0. ;
LCOMPT2 = PROG NC*0. ;
IFIN1 = IMIN1;
REPE BC NC;
  IDEB1 = IFIN1;
  IFIN1 = IFIN1 + 1;
  NC1 = MASQ LTIRAG1 'COMPRIS' IDEB1 IFIN1 'SOMME';
  REMP LCOMPT1 &BC NC1;
  NC2 = MASQ LTIRAG2 'COMPRIS' IDEB1 IFIN1 'SOMME';
  REMP LCOMPT2 &BC NC2;
FIN BC;
list LCOMPT1;
* test de la procedure @HISTOGR
TOPT1 = TABL ;
TOPT1 . 'HPOS' = FLOT IMIN1 ;
TOPT1 . 'DESS' = 'GRIL AXES' ;
TOPT1 . 'COUL' = mot 'OCEA';
@HISTOGR LCOMPT1 TOPT1 FAUX ;
* recup des evolutions pour trace plus evolues
rainbow = mots 'MARI' 'MARI' 'MARI' 'BLEU' 'BLEU' 'AZUR' 'CYAN' 'TURQ'
'VERT' 'OR' 'ORAN' 'ROUG' 'BRIQ' 'BRIQ' 'BRUN' 'BRUN' 'BRUN' ;
TOPT1 = TABL ; TOPT1 . 'COUL' = rainbow;
evhist1 Thist = @HISTOGR LCOMPT1 TOPT1 VRAI ;
TOPT2 = TABL ; TOPT2 . 'COUL' = rainbow;
TOPT2 . 'NOMS' = TABL;
repe b NC; TOPT2 . 'NOMS' . &b = chai &b ''; fin b;
evhist2 Thist2 = @HISTOGR (-1.*LCOMPT2) TOPT2 VRAI ;
* DESS evhist1 Thist;
* DESS evhist2 Thist2;
* DESS (evhist1 et evhist2) Thist;
* avec Legende
repe b NC;
  Thist . &b = MOT 'REMP MARQ TRID';
* Thist . (NC + &b) = MOT 'REMP MARQ TRIU';
  Thist . (NC + &b) = MOT 'MARQ TRIU';
fin b;
DESS (evhist1 et evhist2) Thist YBOR -2500 2500 YGRA 500;
* Test des couleurs
coul3 = mots 'INDI' 'VIOL' 'MARI' 'BLEU' 'AZUR' 'CYAN'
             'TURQ' 'OCEA' 'BOUT' 'VERT' 'OLIV' 'LIME'
             'JAUN' 'OR' 'BRON'
             'ORAN' 'CORA' 'ROUG' 'BRIQ'
             'BRUN' 'CARA' 'BEIG' 'KAKI' 'POUR' 'ROSE' 'PEAU' 'LAVA'
             'BLAN' 'GRIS' 'NOIR' ;
n3 = dime coul3;
xx = prog 0. 1.;
yy = prog 1. 1.;
ev = vide EVOLUTIO;
T = tabl;
repe b n3;
  c = extr coul3 &b;
  ev = ev et (evol c 'MANU' xx (&b * yy));
  T . &b = chai 'LABEL' ' ' c ' REGU';
fin b;
dess ev T XBOR 0. 1.2 ;
FIN ;
```

## explochar [Langage Objets]
```
* Verifie le fonctionnement de la procedure EXPLORER avec la donnee
* d'un CHARGEMENT
opti dime 2 elem qua4 ;
* mettre GRAPH a O pour tester EXPLORER en interactif
GRAPH = 'N' ;
* GRAPH = 'O' ;
L1 = droi (0 0) (1 0) 10 ;
S1 = L1 tran 5 (0 0.4) ;
* trac S1 ;
mo1 = mode s1 mecanique ;
cht1 = (S1 coor 1) nomc T ;
chp1 = pres mass mo1 10. L1 ;
chep1 = manu chml mo1 epxx 1. epyy 2. epzz 3. gaxy 0. ;
lt1 = prog 0. pas 2. 10. ;
la1 = prog 0. pas 0.2 1. ;
ev1 = evol manu temp lt1 ampl la1 ;
cg1 = char t cht1 ev1 ;
cg2 = char meca chp1 ev1 ;
cg3 = char defi chep1 ev1 ;
tt1 = tabl ;
tt1 . 0 = 0. ;
tt1 . 1 = 1. ;
tt2 = tabl ;
tt2 . 0 = cht1 ;
tt2 . 1 = cht1 ;
cgt1 = char tabu tt1 tt2 ;
cg0 = cg1 et cg2 et cg3 et cgt1 ;
tab1 = table ;
tab1 . modele = mo1 ;
tab1 . chargement = cg0 ;
list cg0;
* ...test en X (interactif)
SI (NEG GRAPH 'N') ;
  explorer tab1 'CHAR' ;
* avec option
  topt = tabl;
  topt . 'TYPE' = mot 'T';
  EXPLORER tab1 'CHAR' topt;
  topt . 'TYPE' = mot 'MECA';
  topt . 'COMP' = mot 'FY';
  EXPLORER tab1 'CHAR' topt;
FINSI;
* ...test en PS
opti trac psc ;
* par defaut
  EXPLORER tab1 'CHAR' ;
* avec option
  topt = tabl;
  topt . 'TYPE' = mot 'T';
  EXPLORER tab1 'CHAR' topt;
  topt . 'TYPE' = mot 'MECA';
  topt . 'COMP' = mot 'FY';
  EXPLORER tab1 'CHAR' topt;
fin ;
```

## inclusions [Langage Objets]
```
* Maillage d'un echantillon cubique
* de particules spheriques en inclusion dans une matrice
* -------------------- Parametres de la realisation --------------------
* NBG1 : Nombre de particules.
* DEXC1 : Distance d'exclusion entre points germes des polyedres.
* Attention, si la distance est trop importante, le nombre
* de polyedres demandes ne pourra pas etre atteint.
* DENS1 : Densite (taille) moyenne des elements du maillage.
* Par defaut, vaut 1/5 de la taille moyenne des polyedres.
* IGER1 : Germe du generateur de nombres aleatoires.
* Mot-cle 'AUTO' => processus de congruence initialise a 1
* ITRAC1 : VRAI => affichage resultats.
NBG1 = 3 ** 3 ;
DEXC1 = 0.33 ;
DENS1 = 0.25 * (('FLOT' NBG1) ** (-1. / 3.)) ;
IGER1 = 1 ;
ITRAC1 = FAUX ;
'OPTI' 'ECHO' 1 ;
VECH1 = 'VALE' 'ECHO' ;
VTRA1 = 'VALE' 'TRAC' ;
* --------------------- Maillage d'un cube unite -----------------------
'OPTI' 'DIME' 3 'ELEM' 'TET4' ;
O1 = 0. 0. 0. ;
X1 = 1. 0. 0. ;
Y1 = 0. 1. 0. ;
Z1 = 0. 0. 1. ;
MCUB1 = ((O1 'DROI' 1 X1) 'TRAN' 1 Y1) 'VOLU' 'TRAN' 1 Z1 ;
ACUB1 = ('ARET' MCUB1) 'COUL' 'VERT' ;
* --------------- Tirage des points germes des polyedres ---------------
'SAUT' 1 'LIGN' ;
'MESS' '***** Tirage des points germes des polyedres' ;
MPTS1 = @POINTIR REPU NBG1 SPHE DEXC1 'GERM' IGER1 ;
NBG1 = NBNO MPTS1 ;
'SI' ITRAC1 ;
  'TITR' ('CHAI' NBG1 ' germes tires ') ;
  'TRAC' (ACUB1 'ET' MPTS1) ;
'FINS' ;
* ---------------- Partition de Voronoi du cube unite ------------------
'SAUT' 1 'LIGN' ;
'MESS' '***** Partition du cube unite en cellules de Voronoi ' ;
'TEMP' 'ZERO' ;
TPVORO1 = @P_BOIT2 (@P_VORO MPTS1) ;
'TEMP' ;
'SI' ITRAC1 ;
  'TITR' ' Partition du cube unite en cellules de Voronoi ' ;
  'TRAC' (TPVORO1 . 'MAV' 'ET' (MPTS1 'COUL' 'ROUG')) ;
'FINS' ;
* --------------------- Maillage des inclusions ------------------------
* On prend pour diametre des inclusions 0,97 fois la dist. d'exclusion
TAB1 = @INCLUSI TPVORO1 (0.95 * DEXC1) DEXC1 (DENS1) (ITRAC1) ;
* ----------------------- Affichages / Donnees -------------------------
'SI' ITRAC1 ;
  'TITR' ' Visualisation du maillage de la matrice ' ;
  'TRAC' 'FACE' TAB1 . 'MATR' ;
  'TITR' ' Visualisation du maillage des inclusions ' ;
  'TRAC' 'FACE' TAB1 . 'PART' ;
  'TITR' ' Visualisation du maillage "total"' ;
  'TRAC' 'FACE' TAB1 . 'MAIL' ;
* Structure de la table de resultat :
  PTS1 = MPTS1 'POIN' 1 ;
  'TITR' ' Le maillage de chaque inclusion est indice par son centre ' ;
  'TRAC' 'FACE' (TAB1 . PTS1 . 'PART' 'ET' ACUB1) ;
  'TITR'
  ' Ainsi que la portion de matrice relative a la cellule de Voronoi' ;
  'TRAC' 'FACE' (TAB1 . PTS1 . 'MATR' 'ET' ACUB1)
    'COUP' PTS1 (PTS1 'PLUS' Y1) (PTS1 'PLUS' Z1) ;
  MAILG1 = TAB1 . PTS1 . 'MAIL' ;
  PTS2 = TAB1 . PTS1 . 'MPT' 'POIN' 2 ;
  'TITR'
'Les centres des inclusions voisines sont au sous-indice "MPT"' ;
  'TRAC' 'FACE' (MAILG1 'ET' TAB1 . PTS1 . 'MPT' 'ET' ACUB1) ;
  'TITR'
'Ce qui donne acces aux maillages relatifs a ces inclusions voisines' ;
  'TRAC' 'FACE' (('ARET' MAILG1) 'ET' TAB1 . PTS2 . 'MAIL' 'ET' ACUB1) ;
  MAILG2 = TAB1 . PTS2 . 'MAIL' ;
  AG1G2 = 'ARET' (MAILG1 'ET' MAILG2) ;
  'TITR'
'La face a 2 inclusions voisines sont sous-indicees par leurs centres' ;
  'TRAC' 'FACE' (TAB1 . PTS1 . PTS2 . 'MATR' 'ET' ACUB1 'ET' AG1G2) ;
'FINS' ;
'FIN' ;
'OPTI' 'ECHO' 1 ;
```

## ktest_io1 [Langage Objets]
```
* But : Tester le fonctionnement de la sauvegarde
* Jeu de donnees qui cree tous les objets possibles et
* qui les sauve ensuite de 4 manières differentes :
* - en FORMate et en non-formate (binaire);
* - en enumerant tous les objets a sauver par leur
* noms et en utilisant l'operateur SAUV sans
* arguments (il cherche alors a sauver tous les
* objets qui se trovent dans la memoire).
   opti dime 2 echo 1 ;
* sg 2014/11 : nouveaux noms d'inconnues
   'OPTI' 'INCO' 'PP' 'PQ' ;
   'OPTI' 'INCO' ('MOTS' 'QQQQ') ('MOTS' 'QQQQ') ;
* No 0 : Points ...
   dens 1. ;
   p1 = 0 0 ;
   p2 = 2 0 ;
   p3 = .5 1.5 ;
* No 1 : Meleme ...
   opti elem seg2 ;
   li1 = p1 d 2 p2 ;
   li2 = p2 d 2 p3 ;
   li3 = p3 d 2 p1 ;
   co1 = li1 et li2 et li3 ;
   opti elem tri3 ;
   su1 = co1 surf plan ;
* No 4 : Affecte - n'existe plus
* No 5 : Chamelem - n'existe plus
* No 21 : Modele - n'existe plus
* No 38 : Mmodel ...
   mo0 = 'VIDE' 'MMODEL' ;
   mo1 = mode su1 mecanique elastique tri3 ;
* No 39 : Mchaml ...
   ma1 = mate mo1 youn 2.1e+11 nu 0.3 rho 7850. alph 1.e-5 ;
* No 3 : Rigidite ...
   ri1 = rigi mo1 ma1 ;
   cl1 = bloq depl li1 ;
   cltot = cl1 ;
   ritot = ri1 et cltot ;
   mas1 = mass mo1 ma1 ;
* No 2 : Chpoint ...
   fo1 = forc FX 1.e+4 p3 ;
   de1 = reso ritot fo1 ;
* No 8 : Solution ...
   sol1 = vibr PROCHE (prog 0.) ritot mas1 'SOLU';
* rem bp : objet SOLUTION = objet amene a disparaitre...
* No 10 : Table ...
   tab1 = vibr PROCHE (prog 0.) ritot mas1 ;
* No 9 : Structure ...
   st1 = stru ritot mas1 ;
* No 7 : Elemstru ...
   elst1 = elst st1 p2 ;
* No 6 : Bloqstru ...
   blst1 = clst st1 cltot ;
* No 11 : Maffec - n'existe plus ?????
* No 12 : Msostu - implicite
* No 13 : Imatri - implicite
* No 14 : Mjonct - implicite
* No 15 : Attache ...
   att1 = jonc elst1 UX (prog 1.) ;
* No 16 : Mmatri - implicite
* No 17 : Deforme ...
   def1 = defo li1 de1 1. ;
* No 18 : Listreel ...
   lr1 = prog 0. 1. ;
* No 19 : Listentier ...
   le1 = lect 1 ;
* No 22 : Evolution ...
   ev1 = evol manu 't' lr1 'f(t)' lr1 ;
* No 20 : Chargement ...
   cha1 = char fo1 ev1 ;
* No 23 : Superelement ...
   sup1 = supe RIGIDITE ri1 (p1 et p2) ;
* No 24 : Logique ...
   boo1 = VRAI ;
* No 25 : Flottant - implicite
   flot1 = pi ;
* No 26 : Entier - implicite
   ent1 = 732 ;
* No 27 : Mot - implicite
   mot1 = 'KAKA' ;
* No 28 : Texte ...
   text1 = text 'Essai de construction d un morceau de texte' ;
* No 29 : Listmots ...
   lm1 = MOTS UX UY ;
* No 30 : Vecteur ...
   ve1 = vect fo1 FX FY 1. ROUG ;
* No 31 : Vectdoub - n'existe plus ?????
* No 32 : Points - implicite
* No 33 : Configuration ...
   conf2 = form de1 ;
* No 34 : Listchpo ...
   lch1 = suit CHPOINT fo1 de1 ;
* No 35 : Basemoda ...
   bas1 = BASE st1 att1 sol1 ;
* No 36 : Procedur - implicite
* No 40 : Minte - implicite
* No 41 : Nuage ...
   nu1 = nuag COMP TEMPERATURE pi COMP TRAC ev1 ;
* No 43 : Matrik - comment le creer (EQEX->EQPR->KMAC) ?????
   kritot = 'KOPS' 'RIMA' ritot ;
   icpri = 'MOTS' 'UX' 'UY' 'LX' ;
   icdua = 'MOTS' 'FX' 'FY' 'FLX' ;
   kritot = 'CHANGER' 'INCO' kritot icpri icpri icdua icpri ;
   kfo1 = 'NOMC' icdua fo1 icpri ;
   kmas1 = 'KOPS' 'RIMA' mas1 ;
   kde1 = 'KRES' kritot kfo1 ;
* No 43 : Listobje
   lobj1 = enum ;
   lobj1 = lobj1 'ET' ev1 'ET' ev1 ;
   tab1 . 'lob1' = lobj1 ;
   lobj2 = enum ;
   lobj2 = lobj2 'ET' 1 'ET' 2 ;
   lobj3 = enum ;
   lobj3 = lobj3 'ET' tab1 'ET' tab1 ;
   tab1 . 'lob3' = lobj3 ;
   lobj4 = enum ;
   lobj4 = lobj4 'ET' lobj1 'ET' lobj1 ;
   tab1 . 'lob4' = lobj4 ;
* No 37 : Bloc ...
  repeter bloc1 1 ;
* On testera aussi le fonctionnement de IMPPIL ...
* opti impi 6 ;
* Sauvegarde de tous les objets nommes ...
    opti sauv 'testsauv_noms_B.sortgibi' ;
    sauv p1 p2 li1 mo0 mo1 ma1 ca1 ritot mas1 fo1 de1 sol1 tab1 st1
              elst1 blst1 att1 def1 lr1 le1 ev1 cha1 sup1 boo1 flot1
              ent1 mot1 text1 lm1 ve1 conf2 lch1 bas1 nu1
              kritot kmas1 kde1 lobj1 lobj2 lobj3 lobj4 bloc1 ;
    opti sauv FORM 'testsauv_noms_F.sortgibi' ;
    sauv FORM p1 p2 li1 mo0 mo1 ma1 ca1 ritot mas1 fo1 de1 sol1 tab1 st1
              elst1 blst1 att1 def1 lr1 le1 ev1 cha1 sup1 boo1 flot1
              ent1 mot1 text1 lm1 ve1 conf2 lch1 bas1 nu1
              kritot kmas1 kde1 lobj1 lobj2 lobj3 lobj4 bloc1 ;
* Sauvegarde de tous les objets dans la memoire ...
    opti sauv 'testsauv_glob_B.sortgibi' ;
    sauv ;
    opti sauv FORM 'testsauv_glob_F.sortgibi' ;
    sauv FORM ;
  fin bloc1 ;
fin ;
```

## nloc1 [Langage Objets]
```
graph='N';
saut page;
mess 'test CONN et NLOC';
* construction de connectivites sur des domaines differents
* mesh12=1/4 de disque, mesh1 et mesh2=1/2 disque et
* mesh=disque complet, avec ou sans symetrie de tel facon
* que la reduction sur mesh12 d'un calcul non local mene a l'aide
* de ces 4 conectivites soit toujours identique
opti dime 2 mode plan defo;
* 1) maillage: mesh est un maillage bi-symetrique
* mesh12 en est le 1/4 (compose de me1[tri3] et me2[qua4])
* mesh1 et mesh2 2 en sont des moities contenant mesh12
p1=0 0; p2=1 0; p22=.01 0; p3=0 1; p33=0 .01;
opti elem tri3;
c1=(c 3 p22 p1 p33);
nnc1=nbno c1;
j=1; pci=c1 poin j;
repeter lab1 (nnc1-1);
  j=j+1;
  pcf=c1 poin j;
  mecj=surf ((p1 d 1 pci) et (pci d 1 pcf) et (pcf d 1 p1)) 'PLANE';
  si (j ega 2); me1=mecj;
  sinon ; me1=me1 et mecj;
  finsi;
  pci=pcf;
fin lab1;
opti elem qua4;
me2=dall c1 (p33 d 3 p3) (c 3 p3 p1 p2) (p2 d 3 p22) 'PLAN';
mesh12=me1 et me2;
mesh2=mesh12 syme 'DROI' p1 p2;
mesh3=mesh12 syme 'DROI' p1 p3;
mesh4=mesh2 syme 'DROI' p1 p3;
mesh=mesh12 et mesh2 et mesh3 et mesh4;
elim mesh 1.d-5;
mmesh1=mesh12 et mesh2; mesh1=mmesh1;
mmesh2=mesh12 et mesh3; mesh2=mmesh2;
* 2) modele (tous les mesh ont mesh12 en commun)
mo=modeli mesh mecanique NON_LOCAL 'MOYE'
    'V_MOYENNE' (MOTS 'SCAL') consti constia;
mo12=modeli mesh12 mecanique NON_LOCAL 'MOYE'
    'V_MOYENNE' (MOTS 'SCAL') consti constia;
mo1=modeli mesh1 mecanique NON_LOCAL 'MOYE'
    'V_MOYENNE' (MOTS 'SCAL') consti constia;
mo2=modeli mesh2 mecanique NON_LOCAL 'MOYE'
    'V_MOYENNE' (MOTS 'SCAL') consti constia;
* 3) listmot des composantes a moyenner
* 4) calcul sur le disque complet
mess 'calcul sur le disque complet';
* 4.1) connectivite (normale)
co =conn mo 1. 'NORMAL' 'NO-MESH';
* 4.2) chamelem a moyenner
* (construit par projection d'un chpoint nul partout sauf au centre)
ssca=(manu 'CHPO' p1 1 'SCAL' 1.)
   + (manu 'CHPO' mesh 1 'SCAL' 0.);
csca=chan 'CHAM' ssca mo;
ssca=chan 'STRESSES' mo csca;
* 4.3) moyenne non-locale
moy=nloc ssca co ;
* 4.4) reduction sur le 1/4
mmoy=(redu moy me1) et (redu moy me2);
* 5) calcul sur le 1/4 de disque
mess 'calcul sur le 1/4 de disque';
* 5.1) connectivite avec symetries par rapport a 2 axes obtenues
* de facon "orthogonale" a partir d'une symetrie point et de
* 2 symetries droite
co12ecn=conn mo12 1. 'NORMAL' 'NO-MES12';
co12ecv=conn mo12 1. 'DROITE' p1 p2 'HO-MES12';
co12ech=conn mo12 1. 'DROITE' p1 p3 'VE-MES12';
co12ecp=conn mo12 1. 'POINT' p1 'PT-MES12';
co12vhp=co12ecn et co12ecv et co12ech et co12ecp;
* 5.2) chamelem a moyenner
* (construit par projection d'un chpoint nul partout sauf au centre)
ssca12=(manu 'CHPO' p1 1 'SCAL' 1.)
     + (manu 'CHPO' mesh12 1 'SCAL' 0.);
csca12=chan 'CHAM' ssca12 mo12;
ssca12=chan 'STRESSES' mo12 csca12;
* 5.3) moyenne non-locale
moy12=nloc ssca12 co12vhp ;
* 6) calcul sur le 1/2 disque vertical
mess 'calcul sur le 1/2 disque vertical';
* 6.1) connectivite avec une symetrie droite
co1ecn=conn mo1 1. 'NORMAL' 'NO-MESH1';
co1ecv=conn mo1 1. 'DROITE' p1 p3 'VE-MESH1';
co1v=co1ecn et co1ecv;
* 6.2) chamelem a moyenner
* (construit par projection d'un chpoint nul partout sauf au centre)
ssca1=(manu 'CHPO' p1 1 'SCAL' 1.)
     + (manu 'CHPO' mesh1 1 'SCAL' 0.);
csca1=chan 'CHAM' ssca1 mo1;
ssca1=chan 'STRESSES' mo1 csca1;
* 6.3) moyenne non-locale
moy1=nloc ssca1 co1v;
* 6.4) reduction sur le 1/4
mmoy1=(redu moy1 me1) et (redu moy1 me2);
* 7) calcul sur le 1/2 disque horizontal
mess 'calcul sur le 1/2 disque horizontal';
* 7.1) connectivite avec une symetrie droite
co2ecn=conn mo2 1. 'NORMAL' 'NO-MESH2';
co2ech=conn mo2 1. 'DROITE' p1 p2 'VE-MESH2';
co2h=co2ecn et co2ech;
* 7.2) chamelem a moyenner
* (construit par projection d'un chpoint nul partout sauf au centre)
ssca2=(manu 'CHPO' p1 1 'SCAL' 1.)
     + (manu 'CHPO' mesh2 1 'SCAL' 0.);
csca2=chan 'CHAM' ssca2 mo2;
ssca2=chan 'STRESSES' mo2 csca2;
* 7.3) moyenne non-locale
moy2=nloc ssca2 co2h ;
* 7.4) reduction sur le 1/4
mmoy2=(redu moy2 me1) et (redu moy2 me2);
* 8) erreur
m12m =(abs (moy12 - mmoy )) masque 'SUPERIEUR' 'SOMME' 1.d-10;
m12m1=(abs (moy12 - mmoy1)) masque 'SUPERIEUR' 'SOMME' 1.d-10;
m12m2=(abs (moy12 - mmoy2)) masque 'SUPERIEUR' 'SOMME' 1.d-10;
lerr=m12m + m12m1 + m12m2;
si (lerr > 0); erre 5;
sinon; erre 0; finsi;
fin;
```

## objet [Langage Objets]
```
* creation of object of class "complex number".
* define first the constructor
DEBMETH COMPLEX;
%REA=FAUX;
%IMA=FAUX;
%METHODE SET_IMA IMAG;
%METHODE SET_REA REAL;
%METHODE GET_IMA GIMAG;
%METHODE GET_REA GREAL;
FINMETH;
* define standard methods of the class
DEBMETH IMAG I*'FLOTTANT';
%IMA = I;
'SI' ('EGA' ('TYPE' %REA ) 'FLOTTANT');
   %METHODE MODULE MODUL;
'FINSI';
FINMETH;
DEBMETH REAL RR*'FLOTTANT';
%REA = RR;
'SI' ('EGA' ('TYPE' %IMA ) 'FLOTTANT');
   %METHODE MODULE MODUL;
'FINSI';
FINMETH;
DEBMETH GIMAG ;
II = %IMA;
'SI' ( 'NEG' ( 'TYPE' II) 'FLOTTANT');
   'MESSAGE' 'The imaginary value is not yet defined';
   'ERREUR' 19;
'FINSI';
FINMETH II;
DEBMETH GREAL;
RR = %REA;
'SI' ( 'NEG' ( 'TYPE' RR) 'FLOTTANT');
   'MESSAGE' 'The real value is not yet defined';
   'ERREUR' 19;
'FINSI';
FINMETH RR;
DEBMETH MODUL;
* It is not neccessary to check that real and imaginary exist
AA= %REA* %REA + ( %IMA*%IMA) ** 0.5;
FINMETH AA;
* creation of a COMPLEX OBJET and use
COM = OBJET COMPLEX;
list com;
COM%SET_REA 2.5;
UU=COM%GET_REA; MESS ' real value ' uu;
COM%SET_IMA 3.5;
list com;
ZZ = COM%MODULE ; list ZZ;
* set a new method MULTIplication
DEBMETH MULT RR;
'SI' (( 'EGA' ('TYPE' RR ) 'ENTIER  ') 'OU'
      ( 'EGA' ('TYPE' RR ) 'FLOTTANT'));
   %REA=%REA*RR; %IMA=%IMA*RR;
'SINON';
   'SI' ( 'EGA' ('TYPE' RR ) 'OBJET   ') ;
      RE = %REA*(RR%GET_REA) -( %IMA * (RR%GET_IMA));
      IM = %REA*(RR%GET_IMA) +(%IMA *(RR%GET_REA));
      %REA=RE; %IMA=IM;
   'SINON';
      MESS ' Multiplication impossible';
      ERREUR 19;
   'FINSI';
'FINSI';
FINMETH;
* add the new method to the object COM
COM%METHODE MULTI MULT;
list com;
COM%MULTI 3.5;
list com;
aa = OBJET complex;
aa%set_ima 2;
aa%set_rea 2;
com%multi aa;
list com;
yy = com%GET_REA; xx = COM%GET_IMA;
* aa va heriter de la methode MULTI via
* l'heritage entre objet
aa%HERITE COM;
list aa;
'SI' (( ABS( YY + 7.00)) > 1.e-5); ERREUR 5;FINSI;
'SI' (( ABS( XX - 42.0)) > 1.e-5) ; erreur 5; finsi;
FIN;
```

## posi [Langage Objets]
```
'OPTION' 'ECHO' 0 ;
* NOM : POSI
* DESCRIPTION : Non regression pour l'operateur POSI
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : stephane.gounand@cea.fr
* VERSION : v1, 07/03/2014, version initiale
* HISTORIQUE : v1, 07/03/2014, création
* HISTORIQUE :
* HISTORIQUE :
interact = faux ;
'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
NONORM = 'MOT' 'IDEN';
LISNORM = 'MOTS' 'IDEN' 'KDIA';
inorm = 'POSI' NONORM 'DANS' LISNORM;
* mess inorm;
ok = 'EGA' inorm 1 ;
* renvoie 0 au lieu de 1 !!!
'SI' ('NON' ok) ;
   'MESSAGE' ('CHAINE' 'Il y a eu des erreurs') ;
   'ERREUR' 5 ;
'SINON' ;
   'MESSAGE' ('CHAINE' 'Tout sest bien passe !') ;
'FINSI' ;
'SI' interact ;
   'OPTION' 'ECHO' 1 ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
* End of dgibi file POSI
'FIN' ;
```

## sens [Langage Objets]
```
* FICHIER DGIBI POUR TESTER L'OPERATEURR SENS
* option b)
* Arnaud de Gayffier
opti dime 2 elem seg2 ;
densite 1. ;
* on cree deux cercles concentriques orientés
* dans des sens différents.
pc0 = 0. 0. ;
p1 = 10. 0. ;
p2 = -10. 0.01 ;
c1 = c 10 p1 pc0 p2;
pc1 = 0. 0.02 ;
c2 = c 10 p2 pc1 p1;
p3 = 5. 0. ;
p4 = -5. 0.01 ;
c3 = c 10 p4 pc0 p3 ;
c4 = c 10 p3 pc1 p4 ;
* on maille l'interieur
su1 = surf (c1 et c2 et c3 et c4 ) 'PLAN';
* on extrait le contour
cont1 = cont su1 ;
* on extrait les composantes connexes du contours
tab1 = ccon cont1 ;
* on extrait les orientations du contours
tab2 = 'SENS' tab1 ;
* controle de validite
si ( (nbelem ( diff tab1.1 c1 )) NEG 31) ;
* tab1.1 est le cercle exterieur
  si ( (tab2.1) 'NEG' 1 ) ;
   erreur 5 ;
  finsi ;
  mess 'OK' ;
finsi ;
si ( (nbelem ( diff tab1.1 c3 )) NEG 30) ;
* tab1.1 est le cercle interieur
  si ( (tab2.1) 'NEG' -1 ) ;
   erreur 5 ;
  finsi ;
  mess 'OK' ;
finsi ;
si ( (nbelem ( diff tab1.2 c1 )) NEG 30) ;
* tab1.2 est le cercle exterieur
  si ( (tab2.2) 'NEG' 1 ) ;
   erreur 5 ;
  finsi ;
  mess 'OK' ;
finsi ;
si ( (nbelem ( diff tab1.2 c3 )) NEG 30) ;
* tab1.2 est le cercle interieur
  si ( (tab2.2) 'NEG' -1 ) ;
   erreur 5 ;
  finsi ;
  mess 'OK' ;
finsi ;
fin ;
```

## super1 [Langage Objets]
```
opti echo 0;
opti dime 2;
* definition of the mesh points and of the element
p1=1 0; p2=2 0; p3=3 0;
mes1=manu 'SUPE' p1 p2 p3;
* |2 1 0|
* definition of the K matrix K=|1 2 1|
* |0 1 2|
lis1=prog 2 1 0 1 2 1 0 1 2;
rig1=manu 'RIGIDITE' 'TYPE' 'RIGIDITE' mes1 (mots 'UY') lis1;
* use of the 'MASSE' option
masbl1=mass 'UY' 1 p3;
super1=super 'RIGIDITE' rig1 masbl1;
bb2 mas2=super 'MASSE' super1 masbl1 'LCHP';
u2=extr bb2 1;
* mess 'Solution with the "MASSE" option';
* mess (extr u2 'UY' p1) (extr u2 'UY' p2) (extr u2 'UY' p3);
* solution of the dirichlet problem
bl1=bloq p3 'UY';
f1=depi 1 bl1;
u1=reso (rig1 et bl1) f1;
u1=redu u1 (extr u2 'MAIL');
* error check
er1=u2-u1;
si ((xtx er1) > 1.D-15); erre 5;
sinon; ; erre 0; finsi;
FIN;
```

## test_@deslis [Langage Objets]
```
* NOM : test_@deslis
* DESCRIPTION : teste le bon fonctionnement de la procédure @DESLIS
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Pascal Maugis (CEA/DSM/LSCE)
* mél : pmaugis@cea.fr
* VERSION : v1, 05/07/2006, version initiale
* HISTORIQUE : v1, 05/06/2006, création
* HISTORIQUE :
* HISTORIQUE :
* Merci de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin d'en faciliter
* la maintenance !
* == PROGRAMME PRINCIPAL ==
'OPTION' 'TRACER' 'PS';
* liste de rééls
a = 'PROG' 1 2 16 3 'PAS' 1. 20.;
@DESLIS a ;
* liste d'entiers
@DESLIS ('ENTIER' a) ;
* diverses options de tracé
@DESLIS a 'LOGX' 'LOGY' 'GRIL' 'CARR' 'DATE' 'LOGO' 'AXES'
     'TITRE' 'Super titre' 'TITX' 'par ici' 'TITY' 'par la' 'NCLK' ;
* Conclusion : ménage et sauvegarde.
'FIN' ;
```

## trj_regu [Langage Objets]
```
'OPTION' 'ECHO' 1 ;
* NOM : TRJ_REGU
* DESCRIPTION : Test élémentaire Résidu et Jacobien pour méthode de
* régularisation de maillage en toute dimension d'espace
* (opérateur 'DEDU' option 'ADAP')
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 20/12/2005, version initiale
* HISTORIQUE : v1, 20/12/2005, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
interact= FAUX ;
* BEGINPROCEDUR errrel
* NOM : ERRREL
* DESCRIPTION : Calcul d'une erreur relative
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 23/04/2003, version initiale
* HISTORIQUE : v1, 23/04/2003, création
* HISTORIQUE :
* HISTORIQUE :
* Prière de PRENDRE LE TEMPS de compléter les commentaires
* en cas de modification de ce sous-programme afin de faciliter
* la maintenance !
'DEBPROC' ERRREL ;
'ARGUMENT' val*'FLOTTANT' ;
'ARGUMENT' valref*'FLOTTANT' ;
'SI' ('<' ('ABS' valref) 1.D-10) ;
   echref = 1.D0 ;
'SINON' ;
   echref = valref ;
'FINSI' ;
errabs = 'ABS' ('/' ('-' val valref) echref);
'RESPRO' errabs ;
* End of procedure file ERRREL
'FINPROC' ;
* ENDPROCEDUR errrel
eps = 1.D-8 ;
eps2 = '**' eps 0.5D0 ;
theta = 0.2D0 ; gamma = 2.D0 ;
'REPETER' desp 3 ;
   dimesp = &desp ;
   'MESSAGE' ('CHAINE' 'Dim. esp. = ' dimesp) ;
   'OPTION' 'DIME' dimesp ;
* Maillage
   'REPETER' dmail dimesp ;
      dimmail = &dmail ;
      'MESSAGE' ('CHAINE' 'Dim. mail. = ' dimmail) ;
      'SI' ('EGA' dimmail 1) ;
         'OPTION' 'ELEM' 'SEG2' ;
         c1 = '**' 2 0.5D0 ;
         c2 = PI ;
* lA = 'PROG' c1 c2 c1 ;
* lB = 'PROG' c2 c1 c2 ;
         SI ((VALE DIME) EGA 1);
           pA = 'POIN' c1 ;
           pB = 'POIN' c2 ;
         FINSI;
         SI ((VALE DIME) EGA 2);
           pA = 'POIN' c1 c2 ;
           pB = 'POIN' c2 c1 ;
         FINSI;
         SI ((VALE DIME) EGA 3);
           pA = 'POIN' c1 c2 c1 ;
           pB = 'POIN' c2 c1 c2 ;
         FINSI;
         mt = 'DROIT' 1 pA pB ;
      'FINSI' ;
      'SI' ('EGA' dimmail 2) ;
         'OPTION' 'ELEM' 'TRI3' ;
         c1 = '**' 2 0.5D0 ;
         c2 = PI ;
         c3 = PI '*' PI ;
* lA = 'PROG' c1 c1 c2 ;
* lB = 'PROG' c2 c3 c3 ;
* lC = 'PROG' c3 c3 c3 ;
         SI ((VALE DIME) EGA 1);
           pA = 'POIN' c1 ;
           pB = 'POIN' c2 ;
           pC = 'POIN' c3 ;
         FINSI;
         SI ((VALE DIME) EGA 2);
           pA = 'POIN' c1 c1 ;
           pB = 'POIN' c2 c3 ;
           pC = 'POIN' c3 c3 ;
         FINSI;
         SI ((VALE DIME) EGA 3);
           pA = 'POIN' c1 c1 c2 ;
           pB = 'POIN' c2 c3 c3 ;
           pC = 'POIN' c3 c3 c3 ;
         FINSI;
         mt = 'MANUEL' 'TRI3' pA pB pC ;
      'FINSI' ;
      'SI' ('EGA' dimmail 3) ;
         'OPTION' 'ELEM' 'TET4' ;
         c1 = '**' 2 0.5D0 ;
         c2 = PI ;
         c3 = PI '*' PI ;
         c4 = PI '*' PI '*' c1 ;
         c5 = '+' 1.D0 c3 ;
         pA = ('+' c1 c5) c1 ('*' c1 -1.D0) ;
         pB = ('+' c2 c5) c3 c2 ;
         pC = ('+' ('*' c3 -1.D0) c5) c2 c3 ;
         pD = ('+' c4 c5) ('*' c4 -1.D0) c4 ;
         mt = 'MANUEL' 'TET4' pA pB pC pD ;
      'FINSI' ;
      _mt = 'CHANGER' mt 'QUAF' ;
* Inconnus et discrétisation
      methgau = 'GAU7' ;
      gdisc = 'LINE' ;
      lcmpp = 'MOTS' 'UX' 'UY' 'UZ' ;
      lcmpd = 'MOTS' 'FX' 'FY' 'FZ' ;
      lext = 'LECT' 1 PAS 1 dimesp ;
      incop = 'EXTRAIRE' lcmpp lext ;
      incod = 'EXTRAIRE' lcmpd lext ;
      vdim = 'VALEUR' 'DIME' ;
* Test du résidu
      res = DEADRESI _mt gdisc methgau theta gamma incod ;
* 'LISTE' res ;
      Ephi = DEADFONC _mt gdisc methgau theta gamma ;
      unpert = 'FORME' ;
      'OPTION' 'ECHO' 0 ;
      'REPETER' idim vdim ;
         iidim = &idim ;
         po = pA ;
         incoip = 'EXTRAIRE' incop iidim ;
         incoid = 'EXTRAIRE' incod iidim ;
         dpsi = 'MANUEL' 'CHPO' po 1 incoip eps ;
         'FORME' dpsi ;
         Ephidpsi = DEADFONC _mt gdisc methgau theta gamma ;
         'FORME' unpert ;
         resiapp = '/' ('-' Ephidpsi Ephi) eps ;
         resical = 'EXTRAIRE' res incoid po ;
         erro = ERRREL resical resiapp ;
         'MESSAGE' ('CHAINE' '   Composante ' incoid) ;
         'MESSAGE' ('CHAINE' '   resiapp=' resiapp) ;
         'MESSAGE' ('CHAINE' '   resical=' resical) ;
         'MESSAGE' ('CHAINE' '   erro=' erro) ;
         'SI' ('>' erro eps2) ;
            'SI' interact ;
               cherr = 'CHAINE' '!!!! erro=' erro ;
               'ERREUR' cherr ;
            'SINON' ;
               'ERREUR' 5 ;
            'FINSI' ;
         'FINSI' ;
      'FIN' idim ;
* 'FIN' desp ;
* 'OPTION' 'ECHO' 1 ;
* Test du jacobien (par morceaux)
* jac = jacob tabmod 'TEST' ;
      jac = DEADKTAN _mt gdisc methgau theta gamma incop incod ;
* 'LISTE' jac ;
* resunp = RESID tabmod 'TEST' ;
      resunp = DEADRESI _mt gdisc methgau theta gamma incod ;
      unpert = 'FORME' ;
      'REPETER' idim vdim ;
         iidim = &idim ;
         ppert = pA ;
         incoip = 'EXTRAIRE' incop iidim ;
         incoid = 'EXTRAIRE' incod iidim ;
         dpsi = 'MANUEL' 'CHPO' ppert 1 incoip eps ;
         'FORME' dpsi ;
* resper = RESID tabmod 'TEST' ;
         resper = DEADRESI _mt gdisc methgau theta gamma incod ;
         'FORME' unpert ;
         dresapp = '/' ('-' resper resunp) eps ;
         dpert = 'MANUEL' 'CHPO' ppert 1 incoip 1.D0 ;
         drescal = '*' jac dpert ;
         erro = '/' ('**' ('XTX' ('-' drescal dresapp)) 0.5D0)
                     ('**' ('XTX' drescal) 0.5D0) ;
         'MESSAGE' ('CHAINE' '   Composante ' incoip) ;
         'MESSAGE' ('CHAINE' '   dresapp=') ; 'LISTE' dresapp ;
         'MESSAGE' ('CHAINE' '   drescal=') ; 'LISTE' drescal ;
         'MESSAGE' ('CHAINE' '   erro=' erro) ;
         'SI' ('>' erro eps2) ;
            'SI' interact ;
               cherr = 'CHAINE' '!!!! erro=' erro ;
               'ERREUR' cherr ;
            'SINON' ;
               'ERREUR' 5 ;
            'FINSI' ;
         'FINSI' ;
      'FIN' idim ;
   'FIN' dmail ;
'FIN' desp ;
'SAUTER' 2 'LIGNE' ;
'MESSAGE' ('CHAINE' 'Tout sest bien passe !') ;
'SAUTER' 2 'LIGNE' ;
'OPTION' 'ECHO' 1 ;
'SI' interact ;
   'OPTION' 'ECHO' 1 ;
   'OPTION' 'DONN' 5 ;
'FINSI' ;
* End of dgibi file TRJ_REGU
'FIN' ;
```

## voro2d [Langage Objets]
```
* fichier voro2d.dgibi
* voro3d.dgibi est un exemple d'utilisation dans un cas bidimensionel
* de la procedure MAILVORO de maillage d'agregats cubiques de polyedres
* de Voronoi. Cette procedure fait appel a l'operateur VORO
* La procedure @POINTIR permet de "tirer" aleatoirement un ensemble
* de points servant de germe de la partition de Voronoi.
* Maillage d'un agregat 2D de polyedres de Voronoi
* -------------------- Parametres de la realisation --------------------
* NBG1 : Nombre de polyedres.
* DEXC1 : Distance d'exclusion entre points germes des polyedres.
* Attention, si la distance est trop importante, le nombre
* de polyedres demandes ne pourra pas etre atteint.
* Par defaut, vaut 1/5 de la taille moyenne des polyedres.
* ITRAC1 : VRAI => affichage resultats.
NBG1 = 50;
DEXC1 = 0.05;
ITRAC = FAUX;
OPTI 'ECHO' 1 ;
OPTI 'DIME' 2 'ELEM' 'TRI3' ;
* Definition du contour de l'agregat
* CONTOUR SIMPLE (CARRE UNITAIRE)
SURF1 = (D 1 (0. 0.) (1. 0.)) TRAN 1 (0. 1.) ;
CON1 = CONT SURF1 ;
* CONTOUR CONCAVE (ETOILE A N BRANCHES)
N = 5 ;
R1 = 0.5 ;
R2 = 0.2 ;
P0 = 0.5 0.5 ;
P1 = P0 PLUS (0. R1) ;
P11 = P0 PLUS (0. R2) ;
P11 = P11 TOUR (0.5*360./N) P0 ;
PA = P1 ;
PB = P11 ;
MP1 = PA ET PB ;
REPE B1 (N-1);
  PC = PA TOUR (360./N) P0 ;
  PD = PB TOUR (360./N) P0 ;
  MP1 = MP1 ET PC ET PD ;
  PA = PC ;
  PB = PD ;
FIN B1 ;
CON2 = QUEL 'SEG2' MP1 ;
CON2 = D 1 CON2 P1 ;
* Tirage des points germes des polyedres
'SAUT' 1 'LIGN' ;
'MESS' '***** Tirage des points germes des polyedres' ;
MAIL1 = @POINTIR 'EXCL' NBG1 'SPHE' DEXC1 ;
* PARTITIONS DE VORONOI
TAB0 = VORO MAIL1 CON1 ;
A0 = TAB0 . 'VISU' ;
* MAILLAGE DE LA PARTITION DE VORONOI
TAB1 = MAILVORO TAB0 CON1 'COUL';
SI ITRAC;
  V1 = TAB1 . 'MAIL' ;
  TRAC 'FACE' V1 'TITR' 'Maillage de la partition de Voronoi' ;
FINS;
* PARTITIONS DE VORONOI
TAB0 = VORO MAIL1 CON2 ;
A0 = TAB0 . 'VISU' ;
* MAILLAGE DE LA PARTITION DE VORONOI
TAB1 = MAILVORO TAB0 CON2 'COUL' ;
SI ITRAC;
  V1 = TAB1 . 'MAIL' ;
  TRAC 'FACE' V1 'TITR' 'Maillage de la partition de Voronoi' ;
FINS;
FIN;
```

## c2d93 [Magnetodynamique Magnetodynamique]
```
* 2D AXISYMMETRIC MAGNETIC FIELD COMPUTATION
* Formulation : VECTOR POTENTIAL
* NON LINEAR MATERIAL
 OPTION DIME 2 ELEM TRI6 COUL VERT echo 1 ;
 GRAPH ='N' ;
* ------------------------Mesh --------------------------------------
 R1 =20. ; R2= 25. ; R3= 27. ; R4= 29. ; R5=39.;R6 = 130.;
 Z1= 2.5; Z2= 5. ; Z3= 20. ; Z4= 130.;Z31=30.;Z32=50.;
 DI1= 1.; DI2=5.;DI3=60. ;DI4= 10.;NET2= 6;
  DENS DI1 ;
 OZ3= 0. Z3; OZ2= 0. Z2;OZ1= 0. Z1;OZ4=0. Z4;
 OO= 0. 0.;R0Z0= DI1 0 ;
 R1Z0= R1 0. ;R2Z0= R2 0. ;R3Z0 = R3 0. ;R4Z0 = R4 0.;
 R0Z2= DI1 Z2 ; R4Z2 = R4 Z2 ;
  DENS DI2 ;
 R5Z0= R5 0. ;R5Z3= R5 Z3 ;R0Z3 =DI2 Z3 ;OZ3 = 0. Z3 ;
  DENS DI3 ;
 R6Z0=R6 0.; R6Z4=R6 Z4 ;
  DENS 10 ;
 R2Z3= R2 Z3 ; R1Z3= R1 Z3; R4Z1 = R4 Z1;
 R3Z1= R3 Z1 ;
 DENSITE DI4 ;
 R0Z4 = DI4 Z4 ; OZ4 = 0. Z4 ;
 NTRA= 1;
 FLAN1 =( D OO R0Z0 D R1Z0 ) TRAN DINI DI1 DFIN DI1 ( OZ1 MOINS OO )
             TRAN DINI DI1 DFIN DI1 ( OZ2 MOINS OZ1) COUL VERT ;
* ------------------------- COIL SURFACE -------------------------
 BOBI =( D R1Z0 R2Z0 ) TRAN DINI DI1 DFIN DI1 ( OZ1 MOINS OO )
                                                      COUL BLEU ;
 FLAN2 =(INVE( BOBI COTE 3)) TRAN DINI DI1 DFIN DI1
                            ( OZ2 MOINS OZ1) COUL VERT ;
 FLAN3 =( D R2Z0 R3Z0 ) TRAN DINI DI1 DFIN DI1 ( OZ1 MOINS OO )
             TRAN DINI DI1 DFIN DI1 ( OZ2 MOINS OZ1) COUL VERT ;
 FLAN4 =( D R3Z0 R4Z0 ) TRAN DINI DI1 DFIN DI1 ( OZ1 MOINS OO )
             TRAN DINI DI1 DFIN DI1 ( OZ2 MOINS OZ1) COUL VERT ;
* ---------------------IRON ------------------------------------------
 FER = (D OZ2 R0Z2 D R4Z2 D 6 R4Z0 D R5Z0 D R5Z3 D R0Z3 D OZ3 D OZ2 )
 SURF PLANE COUL ROUG ;
* ---------------------EXTERNAL AIR BOX ------------------------------
 FLAN5 = ( D R5Z0 R5Z3 D R6Z4 D R6Z0 D R5Z0 ) SURF PLANE ;
 FLAN6 =( D R0Z3 R5Z3 D R6Z4 D R0Z4 D R0Z3 ) SURF PLANE
                        COUL VERT ;
 TUB6 = (D OZ3 R0Z3 D R0Z4 D OZ4 D OZ3) SURF PLANE COUL vert ;
 AIREXT = (FLAN6 ET TUB6 ET FLAN5 ) coul blan ;
 AIRIN = ((FLAN1 ET FLAN2 ET FLAN3 ET FLAN4 ) coul vert) et BOBI ;
 TOUT = AIRIN ET AIREXT ET FER ; ELIM .2 TOUT ;
* --------------- BOUNDARIES -----------------------------------------
 ENPP = CONTOUR TOUT ;
 CEXTR=ENPP POINTS DROITE (130. 0.) (130. 100.) .1 ;
 CEXTH=ENPP POINTS DROITE ( 0. 130.) (10. 130.) .1 ;
 AXE=ENPP POINTS DROITE ( 0. 0. ) ( 0. 100. ) .1 ;
 AX1 = (AIRIN ET FER) POINT DROITE ( 0. 0. ) ( 0. 100. ) .1 ;
 AX2 = DIFF ( CHAN POI1 AXE) (CHAN POI1 AX1) ;
* FORMER DESCRIPTION IN MILLIMETRES
* --------------- SHIFT FOR METERS ------------------------------------
 deplacer tout homo .001 (0. 0.) ;
 SI (NEG GRAPH N ) ;
 TITRE ' MESH 2D ' ;
 TRAC tout ;
 FINSI ;
 MU0= 4. * PI * 1.E-7 ;
* ------------------CURENT DESCRIPTION ---------------------------------
 TABCOUR= TABLE ;
 DESCOUR TABCOUR 1 BOBI 'AMP' 800.E6 ;
 TABB = TABLE ;
* ----------------- AXISYMMETRIC PROBLEM ------------------------------
 TABB.'AXI'= VRAI ;
  NF = FER NBEL ;
   FER1 = FER ELEM ( LECT 1 PAS 1 30 ) ;
   FER2 = FER ELEM ( LECT 31 PAS 1 NF ) ;
* ------------------MATERIALS -----------------------------------------
 KEVOL = H_B MU0 ;
 TABMAT = TABLE ;
    OBFER1 = FER1 MODE THERMIQUE ISOTROPE ;
    OBFER2 = FER2 MODE THERMIQUE ISOTROPE ;
   STN = TABLE ; STN.EV1 = KEVOL ;
   TABMAT.OBFER1 = STN ;
   STN = TABLE ; STN.EV1 = KEVOL ;
   TABMAT.OBFER2 = STN ;
 TABB.'TABNUSEC' = TABMAT ;
 TABB.'MUAIR' =MU0 ;
* ------- LINEAR MATERIAL CAN BE TRAITED AS A SUPER ELEMENT OR NOT
   isuper= 1 ;
 'SI' ('EGA' isuper 1 ) ;
 TABB.'AIRSUP' = AIREXT ;
 TABB.'MAITRES' = ( FER CONTOUR) 'ELEM' 'COMP' R5Z0 OZ3 ;
 TABB.'ENCS' = CEXTR ET CEXTH ET AX2 ;
 TABB.'BLOQUE' = BLOQUER 'T' AX1 ;
 TABB.'AIR' = AIRIN ;
 'SINON' ;
 TABB.'AIR' = (AIRIN ET AIREXT) ;
 TABB.'BLOQUE' = BLOQUER 'T' (CEXTR ET CEXTH ET AXE ) ;
 'FINSI' ;
 TABB.'COUR'= TABCOUR ;
* ------POTENTIAL COMPUTATION OR FIRST STEP IF NON LINEAR PROBLEM ---
 POT_VECT TABB 'SOLIN' ;
 SOL1 = (TABB.'POTENTIEL' ) ENLEVER LX ;
 RAY = FLAN1 COTE 1 ;
 RAY2 = D 10 (0. .0001) ( .020 .0001) ;
* -------------SOME POST TRAITMENT B COMPUTATION ----------------
 BB = INDUCTIO AIRIN SOL1 VRAI ;
 PREF = AIRIN POINT PROCHE ( 0. 0. ) ;
 BY0 = EXTR BB 'BY' PREF ;
 BY10 = EXTR BB 'BY' ( AIRIN POINT PROCHE ( .010 0.)) ;
 TITRE ' COMPOSANTE BY AVANT ET APRES LISSAGE ' ;
 EVB1 = EVOL ROUG CHPO BB 'BY' RAY ;
* ---------- polynomial smothing if wanted --------------------
 CHLIS = PROI POLY TOUT RAY2 SOL1 1 AXIS ;
 BBY = (EXCO CHLIS 'BY' ) NOMC 'BY' ;
 BY01 = EXTR BBY 'BY' (RAY2 POINT INITIAL) ;
 BAT1 = 800.e6 * 5.e-3 * 5.e-3 * MU0 /10.e-3 ;
 option echo 0 ;
 MESS '**************************************************************';
 MESS '*  CIRCULAR COIL  internal radius 20 mm ' ;
 MESS '*        total    cross section  5*5 mm ' ;
 MESS '*         SYMMETRY BY HORIZONTAL PLANE  ' ;
 MESS '*  AMPERE  mufer >> muo  all AMPERE*TURNS in the GAP of 10 mm ';
 MESS '*                                                             ';
 MESS '*       J * EP * HAUT = B/ MU0 * e                            ';
 MESS '*   WAITED :   By = ' bat1 '  TESLAS                           ';
 MESS ' *************************************************************';
 MESS '  NUMERICAL DERIVATION    BY AU CENTRE ' BY0 ;
 MESS '  SMOTHED SOLUTION        BY AU CENTRE ' BY01 ;
 MESS ' *****************************************';
   RAP = ABS ((BY01 - bat1 ) / bat1 );
       SI ( RAP > .01 ) ; ERREUR 5 ; FINSI ;
 SI (NEG GRAPH N ) ;
 TITRE ' POTENTIAL   BEFORE AND AFTER   SMOTHING ' ;
 EVPO1 = EVOL ROUG CHPO SOL1 'T' RAY ;
 EVPO2 = EVOL VERT CHPO CHLIS 'A' RAY2 ;
 dess (evpo1 et evpo2) xbor 0. (R1 * 0.001 * .75);
 TITRE ' BY COMPONENT  BEFORE AND AFTER SMOTHING  ' ;
 EVB1 = EVOL ROUG CHPO BB 'BY' RAY ;
 EVB2 = EVOL VERT CHPO CHLIS 'BY' RAY2 ;
 dess (evb1 et evb2) xbor 0. (R1 * 0.001 * .75) ;
  FINSI ;
* ----------------- NON LINEAR COMPUTATION -------------------
* filling
 TABB.SOUSTYPE='THERMIQUE' ;
 TABB.CRITERE =1.E-4 ;
 TABB.NITER =1;
 TABB.'OME' = .1 ;
* ----------- test shortened to 2 iterations ----------------------
 TABB.ITERMAX=2;
 TABB.NIVEAU =1;
  MAG_NLIN TABB ;
 SOL2 = enlever (TABB.'POTENTIEL' ) LX ;
 BB = INDUCTIO AIRIN SOL2 VRAI ;
 BY02 = EXTR BB 'BY' PREF ;
 CHLIS = PROI POLY TOUT RAY2 SOL2 1 AXIS ;
 BBY = (EXCO CHLIS 'BY' ) NOMC 'BY' ;
 BY03 = EXTR BBY 'BY' (RAY2 POINT INITIAL) ;
 BAT = 2.4106 ;
 MESS ' *****************************************';
 MESS '  EXPECTED SOLUTIONS   AT CENTER   BY  ' BAT ;
 MESS '  NUMERICAL DERIVATION             BY  ' BY02 ;
 MESS '  SMOTHED SOLUTION                 BY  ' BY03 ;
 MESS ' *****************************************';
    itest = 1 ;
* --------------------GOOD WORKING MESSAGE -----------------------
    SI (EGA ITEST 1 ) ;
* ------- test shortened ---------------------------------------
   RAP = ABS ((BY03 - BAT ) / BAT);
       SI ( RAP > .01 ) ; ERREUR 5 ; FINSI ;
   SINON ;
* ------ COMPUTATION TILL CONVERGENCE OR UP TO 100 MORE ITERATION
 TABB.ITERMAX=100;
  MAG_NLIN TABB ;
 SOL2 = enlever (TABB.'POTENTIEL' ) LX ;
 BB = INDUCTIO AIRIN SOL2 VRAI ;
 BY02 = EXTR BB 'BY' PREF ;
 CHLIS = PROI POLY TOUT RAY2 SOL2 1 AXIS ;
 BBY = (EXCO CHLIS 'BY' ) NOMC 'BY' ;
 BY03 = EXTR BBY 'BY' (RAY2 POINT INITIAL) ;
 BAT = 2.3468 ;
 MESS ' *****************************************';
 MESS '  EXPECTED SOLUTION ON AXIS      BY   ' BAT ;
 MESS '  NUMERICAL DERIVATION  BY AU CENTRE ' BY02 ;
 MESS '  SMOTHED SOLUTION      BY AU CENTRE ' BY03 ;
 MESS ' *****************************************';
   RAP = ABS ((BY03 - BAT ) / BAT );
       SI ( RAP > .01 ) ; ERREUR 5 ; FINSI ;
  SI (NEG GRAPH N ) ;
 TITRE ' POTENTIAL   BEFORE AND AFTER   SMOTHING ' ;
 EVPO1 = EVOL ROUG CHPO SOL2 'T' RAY ;
 EVPO2 = EVOL VERT CHPO CHLIS 'A' RAY2 ;
 dess (evpo1 et evpo2) xbor 0. (R1 * 0.001 * .75);
 TITRE ' BY COMPONENT  BEFORE AND AFTER SMOTHING ' ;
 EVB1 = EVOL ROUG CHPO BB 'BY' RAY ;
 EVB2 = EVOL VERT CHPO CHLIS 'BY' RAY2 ;
 dess (evb1 et evb2) xbor 0. (R1 * 0.001 * .75);
 FINSI ;
   FINSI ;
 FIN ;
              ;
```

## symplaq [Magnetodynamique Magnetodynamique]
```
OPTI DIME 3 ELEM TRI3 ;
* OPTI IMPR 'symplaq.out';
P0 = 0. 0. 0. ;
P1 = 1. 0. 0. ;
P2 = 0. 0. 1.;
P3 = 0. 1. 0. ;
L1 = CERC 5 P1 P0 P3 ;
OEIL = 1000. 1000. 1000.;
L2 = L1 TOUR 90. P0 P2 ;
L3 = L2 TOUR 90. P0 P2 ;
L4 = L3 TOUR 90. P0 P2 ;
P4 = -1. 0. 0.;
L01 = L1 ET L2;
L02 = P4 DROIT 11 P1;
L0 = L01 ET L02;
ELIM 0.001 L0;
ELIM 0.001 L01;
ELIM 0.001 L02;
S1 = SURF L0 'PLANE';
ELIM 0.001 L0 S1;
ELIM 0.001 L01 S1;
ELIM 0.001 L02 S1;
S2 = S1 SYME 'DROIT' P4 P1;
S3 = S1 ET S2;
S3 = ORIEN S3 'POINT' P2;
S3 = VERSENS S3;
LB = L1 ET L2 ET L3 ET L4;
ELIM 0.001 LB S3;
* OPTI SAUV 'symplaq.bin';
* SAUV S3;
* OPTI DONN 5;
MOD1 = 'MODELE' S1 'MAGNETODYNAMIQUE'
 'POTENTIEL_VECTEUR' 'ISOTROPE' 'ROT3';
MAT1 = 'MATE' MOD1 'ETA' 1.E-4 'PERM' 1. 'EPAI' 1.;
M11 = 'MUTU' MOD1 MAT1 S1;
* CAS SYMETRIE : CHANGEMENT D'ORIENTATION
M21 = 'MUTU' MOD1 MAT1 S2;
M21 = -1.*M21;
M1 = M11 ET M21;
R1 = 'RESI' MOD1 MAT1 ;
* CONSTITUTION DU SYSTEME
* DONNEE DU CHAMP INUCTEUR : 100T/s
B1Z = MANU CHPO S1 1 SCAL 0.;
B2Z = MANU CHPO S1 1 SCAL 100.;
DTB=1.;
DBZDT = (B2Z-B1Z)/DTB;
X1 = (COOR 1 S1) ;
Y1 = (COOR 2 S1) ;
X2 = X1**2;
Y2 = Y1**2;
RAY = (X2+Y2)**0.5 ;
DAPHIDT = 0.5*RAY*DBZDT;
* ON PASSE EN CARTESIEN
ANGL1 = 'ATG' Y1 X1 ;
PIS4 = 'ATG' 1. 1. ;
PIS2 = 2.*PIS4;
ANGL2 = ANGL1 + PIS2 ;
COSA1 = 'COS' ANGL2 ;
SINA1 = 'SIN' ANGL2 ;
DAXDT = DAPHIDT*COSA1;
DAXDT = EXCO DAXDT SCAL AX;
DAXDT = CHAN DAXDT ATTRIBUT NATURE DISCRET;
DAYDT = DAPHIDT*SINA1;
DAYDT = EXCO DAYDT SCAL AY;
DAYDT = CHAN DAYDT ATTRIBUT NATURE DISCRET;
DAZDT = MANU CHPO S1 1 AZ 0.;
DAZDT = CHAN DAZDT ATTRIBUT NATURE DISCRET;
DADT = DAXDT ET DAYDT ET DAZDT ;
VADT = VECT DADT AX AY AZ 0.005 ROUGE;
DADTN=CNEQ MOD1 DADT;
* DONNEE DES OPERATEURS
TETA=0.5;
DT = 1.E-5;
TEMPS=0.;
OPE1 = M1 ET (R1*(TETA*DT)) ;
OPE2 = BLOQ 'FC' L01;
OPE3 = OPE1 ET OPE2;
SOU1 = M1 ET (R1*((TETA-1.)*DT)) ;
SOU2 = SOU1 ;
* SOU2 = SOU1 ET OPE2 ;
SOL1 = MANU CHPO S1 1 FC 0. ;
NDT = 5;
NSORT = NDT ;
REPE BOUC NDT;
IDT = &BOUC ;
TEMPS = TEMPS+DT;
SMB11 = SOU2*SOL1;
SMB12 = DT*DADTN;
SMB1 = SMB11 - SMB12;
SOL2 = RESO OPE3 SMB1;
SOL0 = OPE3*SOL2 ;
SOL1 = SOL2 ;
FIN BOUC;
CURR = DECO MOD1 MAT1 SOL1;
CURX = EXCO 'FC,X' CURR ;
CURX = CHAN 'CHPO' CURX MOD1;
CRX2 = CURX**2;
CURY = EXCO 'FC,Y' CURR ;
CURY = CHAN 'CHPO' CURY MOD1;
CRY2 = CURY**2;
CURZ = EXCO 'FC,Z' CURR ;
CURZ = CHAN 'CHPO' CURZ MOD1;
CRZ2 = CURZ**2;
CURP = CURX ET CURY ET CURZ ;
CURN = (CRX2+CRY2+CRZ2)**0.5;
JMAX = MAXI CURN;
LIST JMAX;
JREF = 17290.;
CURP = CURP/JMAX;
CURV = VECT CURP 'FC,X' 'FC,Y' 'FC,Z' 0.2 ROUGE;
ERRJ = ABS(JREF-JMAX)/JREF;
LIST ERRJ;
SI (ERRJ > 0.02);
   ERREUR 5;
FINSI;
* OPTI DONN 5;
FIN;
```

## chan_poi1_lenti [Maillage Autres]
```
* Test manu_lenti.dgibi : Jeux de données
* CAS TEST DU 2016/06/09
* Cas-test de Verification pour la syntaxe :
* MAIL2 = CHAN 'MOT1' MAIL1 LENTI1 ;
* Le LISTENTI LENTI1 contient la connectivité des noeuds de MAIL1 qu'il
* faut mettre en place.
* SI MOT1 n'est pas defini le type d'element pris celui de OPTI ELEM
* MAIL1 doit être de type POI1
* Ce cas-test permet de creer un element TET4 a partir d'un MAILLAGE de
* POI1 et d'une connectivite donnee dans un LISTREEL.
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
OPTI DIME 3 ELEM 'TET4';
GRAPH = 'N' ;
SI ('NEG' GRAPH 'N');
  OPTI TRAC 'OPEN';
SINO;
  OPTI TRAC 'PSC';
FINS;
LX = PROG 0. 0.5 1. 0.5;
LY = PROG 0. 1. 0. 0.5;
LZ = PROG 0. 0. 0. 1. ;
CONN1 = LECT 1 2 3 4 ;
M1 = POIN LX LY LZ ;
MAIL1 = CHAN 'TET4' M1 CONN1;
MAIL2 = CHAN M1 CONN1;
TRAC 'FACE' MAIL1;
TRAC 'CACH' MAIL2;
FIN;
```

## mato-2d3 [Maillage Autres]
```
'OPTION' 'ECHO' 0 ;
* NOM : MATO-2D3
* DESCRIPTION : Test du MAilleur TOpologique pour mailler un carré de
* avec une métrique anisotrope constante en espace
* dans le but d'obtenir 10x20 mailles, puis 20x10 mailles
* en autorisant le mailleur à modifier les noeuds du bord
* dans ce dernier cas.
* On teste la qualité des éléments obtenus.
* On améliore un peu la qualité du dernier maillage obtenu
* avec une boucle entre r-adaptation (DEDU ADAP) et
* remaillage.
* Issu de 2d_3.dgibi+tests
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
* mél : stephane.gounand@cea.fr
* VERSION : v1, 07/04/2020, version initiale
* HISTORIQUE : v1, 07/04/2020, création
* HISTORIQUE :
* HISTORIQUE :
interact = FAUX ;
graph = FAUX ;
'OPTION' 'DIME' 2 'ELEM' 'TRI3' ;
'SI' ('NON' interact) ;
  'OPTION' 'TRAC' 'PSC' ;
'SINON' ;
  'OPTION' 'TRAC' 'X' ;
'FINSI' ;
lqual = 'PROG' 0.5 'PAS' 0.025 1. ;
* Création du contour
d1 = 0.1 ; d2 = 0.05 ;
pA = 0. 0. ; pB = 1. 0. ; pC = 1. 1. ; pD = 0. 1. ;
lAB = 'DROI' pA pB 'DINI' d1 'DFIN' d1 ;
lBC = 'DROI' pB pC 'DINI' d2 'DFIN' d2 ;
lCD = 'DROI' pC pD 'DINI' d1 'DFIN' d1 ;
lDA = 'DROI' pD pA 'DINI' d2 'DFIN' d2 ;
cnt = lAB 'ET' lBC 'ET' lCD 'ET' lDA ;
'SI' graph ;
   tit = 'CHAI' 'Contour ' ;
      'TRACER' 'CACH' cnt 'TITR' tit 'NOEU' ;
'FINSI' ;
* Tests divers (consistance...)
lok = VRAI ;
* TEST 1 Création d'un maillage sans ajouter de noeuds
   mail1 = 'TRIA' 'TOPO' cnt 'NOAJ' ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere sans noeud supplémentaire' ;
      'TRAC' mail1 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 1 : on vérifie que le nombre de noeuds est conservé
nno1 = 'NBNO' cnt ;
nno2 = 'NBNO' mail1 ;
'SI' ('NEG' nno1 nno2) ;
   'MESS' '!!! TEST 1 : nombre de noeuds non conserve' ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 2 Création d'un maillage en ajoutant des noeuds interieurs
   mail2 = 'TRIA' 'TOPO' cnt ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere en ajoutant des noeuds interieurs' ;
      'TRAC' mail2 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 2 : on vérifie que les qualités mini, moyenne et maxi des éléments sont bonnes
qmail2 = 'INDI' 'TOPO' mail2 ;
miq = 'MINI' qmail2 ; moq = MATOUTIL 'MOYECHAM' qmail2 ;
maq = 'MAXI' qmail2 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 2 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail2 = 'MODE' mail2 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage avec noeuds interieurs' ;
      'TRAC' qmail2 momail2 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.66E+00 Qmoy= 0.87E+00 Qmax= 0.10E+01
miqref = 0.65 ; moqref = 0.86 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 2 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 2 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 2 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 3 Remaillage du précédent avec une métrique anisotrope constante
* en espace compatible avec le maillage du bord 10x20
   cmet = 'MANU' 'CHPO' mail2 3 'G11' ('**' d1 -2)
                                'G22' ('**' d2 -2)
                                'G21' 0. ;
* Facultatif : mettre tout ça dans la notice de ALGOMAIL
* ainsi que les valeurs par défaut
* tparam3 . 'debug' = 2 ;
   mail3 = 'REMA' mail2 ('CONT' mail2) cmet ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage avec metrique 10x20' ;
      'TRAC' mail3 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 3 : on vérifie que les qualités des éléments sont bonnes
   cmet = 'MANU' 'CHPO' mail3 3 'G11' ('**' d1 -2)
                                'G22' ('**' d2 -2)
                                'G21' 0. ;
qmail3 = 'INDI' 'TOPO' mail3 cmet ;
miq = 'MINI' qmail3 ; moq = MATOUTIL 'MOYECHAM' qmail3 ;
maq = 'MAXI' qmail3 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 3 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail3 = 'MODE' mail3 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage 10x20' ;
      'TRAC' qmail3 momail3 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.66E+00 Qmoy= 0.84E+00 Qmax= 0.10E+01
miqref = 0.65 ; moqref = 0.83 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 3 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 3 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 3 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 4 Remaillage du précédent avec une métrique anisotrope constante
* en espace différente visant à obtenir un maillage 20x10
* On demande au remailleur de modifier les noeuds du bord.
   cmet = 'MANU' 'CHPO' mail3 3 'G11' ('**' d2 -2)
                                'G22' ('**' d1 -2)
                                'G21' 0. ;
   mail4 = 'REMA' mail3 cmet ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage avec metrique anisotrope 20x10' ;
      'TRAC' mail4 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 4 : on vérifie que les qualités des éléments sont bonnes
   cmet = 'MANU' 'CHPO' mail4 3 'G11' ('**' d2 -2)
                                'G22' ('**' d1 -2)
                                'G21' 0. ;
qmail4 = 'INDI' 'TOPO' mail4 cmet ;
miq = 'MINI' qmail4 ; moq = MATOUTIL 'MOYECHAM' qmail4 ;
maq = 'MAXI' qmail4 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 4 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail4 = 'MODE' mail4 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage 20x10' ;
      'TRAC' qmail4 momail4 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.67E+00 Qmoy= 0.85E+00 Qmax= 0.10E+01
miqref = 0.66 ; moqref = 0.84 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 4 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 4 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 4 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 5 Une petite boucle avec de la r-adaptation (DEDU ADAP) pour voir si on peut
* améliorer la qualité du maillage mail3.
* La réponse est oui, on peut effectivement avoir une amélioration mais
* après quelque itérations la qualité oscille sans s'alméliorer entre
* r-adaptation et remaillage car les critères optimisés ne sont pas les
* mêmes aux deux étapes.
nopt = 2 ; iopt = 0 ;
* Paramètres de DEDUADAP
thdedu = 0.2 ; rdepa = 1. ; nitm = 1 ;
maili = mail4 ;
ldep = 'PROG' ; lqmin = 'PROG' ; lqmoy = 'PROG' ;
'REPE' bclopt nopt ;
   iopt = iopt '+' 1 ;
   tit = 'CHAI' 'i=' iopt ;
* Partie DEDUADAP
   maili1 = maili ;
   modi1 = 'MODE' maili1 'MECANIQUE' ;
   cmet = 'MANU' 'CHPO' maili1 3 'G11' ('**' d2 -2)
                                 'G22' ('**' d1 -2)
                                 'G21' 0. ;
   ccmet = 'CHAN' 'CHAM' cmet modi1 ;
   depa = 'DEDU' 'ADAP' maili1 'METR' ccmet modi1 'THET' thdedu 'NITM' nitm ;
   depa = '*' depa rdepa ;
   mcdep = 'MAXI' depa 'ABS' ; ldep = ldep 'ET' mcdep ;
   'MESS' tit ' dedu max. dep=' mcdep ;
   'FORM' depa ;
   qmaili1 = 'INDI' 'TOPO' maili1 cmet ;
   miq = 'MINI' qmaili1 ; moq = MATOUTIL 'MOYECHAM' qmaili1 ;
   maq = 'MAXI' qmaili1 ;
   'MESS' 'FORMAT' '(E9.2)' tit ' deduadap : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momaili1 = 'MODE' maili1 'THERMIQUE' ;
      vdep = 'VECT' depa -1. 'UX' 'UY' 'NOIR' ;
      titg = 'CHAI' tit ' deduadap' ;
      'TRAC' qmaili1 momaili1 vdep maili1 lqual 'TITR' titg ;
   'FINS' ;
* Partie MAILTOPO
   maili2 = 'REMA' maili1 cmet ;
* Qualités
   cmet = 'MANU' 'CHPO' maili2 3 'G11' ('**' d2 -2)
                                 'G22' ('**' d1 -2)
                                 'G21' 0. ;
   qmaili2 = 'INDI' 'TOPO' maili2 cmet ;
   miq = 'MINI' qmaili2 ; moq = MATOUTIL 'MOYECHAM' qmaili2 ;
   maq = 'MAXI' qmaili2 ;
   'MESS' 'FORMAT' '(E9.2)' tit ' mailtopo : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momaili2 = 'MODE' maili2 'THERMIQUE' ;
      titg = 'CHAI' tit ' mailtopo' ;
      'TRAC' qmaili2 momaili2 lqual 'TITR' titg ;
   'FINSI' ;
   maili = maili2 ;
'FIN' bclopt ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.68E+00 Qmoy= 0.89E+00 Qmax= 0.10E+01
miqref = 0.67 ; moqref = 0.88 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 5 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 5 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 5 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
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
* End of dgibi file MATO-2D3
'FIN' ;
```

## mato-2d4 [Maillage Autres]
```
'OPTION' 'ECHO' 0 ;
* NOM : MATO-2D4
* DESCRIPTION : Test du MAilleur TOpologique pour mailler un carré
* avec une métrique isotrope constante en espace
* dans le but d'obtenir 10x10 mailles.
* Au départ, le carré est 1x1. Concernant la frontière,
* on contraint le mailleur, soit à ne pas la modifier,
* soit à en modifier une partie, soit la totalité.
* On teste la qualité des éléments obtenus.
* Issu de 2d_9.dgibi+tests
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
* mél : stephane.gounand@cea.fr
* VERSION : v1, 07/04/2020, version initiale
* HISTORIQUE : v1, 07/04/2020, création
* HISTORIQUE :
* HISTORIQUE :
interact = FAUX ;
graph = FAUX ;
'OPTION' 'DIME' 2 'ELEM' 'TRI3' ;
'SI' ('NON' interact) ;
  'OPTION' 'TRAC' 'PSC' ;
'SINON' ;
  'OPTION' 'TRAC' 'X' ;
'FINSI' ;
lqual = 'PROG' 0. 'PAS' 0.05 1. ;
* Création du contour
nx = 1 ; nv = 10 ;
pA = 0. 0. ; pB = 1. 0. ; pC = 1. 1. ; pD = 0. 1. ;
lAB = 'DROI' nx pA pB ;
lBC = 'DROI' nx pB pC ;
lCD = 'DROI' nx pC pD ;
lDA = 'DROI' nx pD pA ;
cnt = lAB 'ET' lBC 'ET' lCD 'ET' lDA ;
'SI' graph ;
   tit = 'CHAI' 'Contour ' ;
      'TRACER' 'CACH' cnt 'TITR' tit 'NOEU' ;
'FINSI' ;
* Tests divers (consistance...)
lok = VRAI ;
* TEST 1 Création d'un maillage sans ajouter de noeuds
   mail1 = 'TRIA' 'TOPO' cnt 'NOAJ' ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere sans noeud supplémentaire' ;
      'TRAC' mail1 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 1 : on vérifie que le nombre de noeuds est conservé
nno1 = 'NBNO' cnt ;
nno2 = 'NBNO' mail1 ;
'SI' ('NEG' nno1 nno2) ;
   'MESS' '!!! TEST 1 : nombre de noeuds non conserve' ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 2 Remaillage de mail1 avec une taille voulue de 0.1 sans
* toucher le bord
   mail2 = 'REMA' mail1 ('CONT' mail1) ('/' 1. nv) ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere sans toucher le bord' ;
      'TRAC' mail2 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 2 : on vérifie que les qualités mini, moyenne et maxi des éléments sont bonnes
qmail2 = 'INDI' 'TOPO' mail2 ;
miq = 'MINI' qmail2 ; moq = MATOUTIL 'MOYECHAM' qmail2 ;
maq = 'MAXI' qmail2 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 2 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail2 = 'MODE' mail2 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage sans toucher le bord' ;
      'TRAC' qmail2 momail2 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.91E-01 Qmoy= 0.82E+00 Qmax= 0.10E+01
miqref = 0.08 ; moqref = 0.81 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 2 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 2 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 2 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 3 Remaillage de mail1 avec une taille voulue de 0.1 en touchant
* le bord sauf lAB
   mail3 = 'REMA' mail1 lAB ('/' 1. nv) ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere sans toucher lAB' ;
      'TRAC' mail3 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 3 : on vérifie que le bord n'a pas été touché
* ceci est fait dans mailtopo
* Test 3 : on vérifie que les qualités mini, moyenne et maxi des éléments sont bonnes
qmail3 = 'INDI' 'TOPO' mail3 ;
miq = 'MINI' qmail3 ; moq = MATOUTIL 'MOYECHAM' qmail3 ;
maq = 'MAXI' qmail3 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 3 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail3 = 'MODE' mail3 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage sans toucher lAB' ;
      'TRAC' qmail3 momail3 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.13E+00 Qmoy= 0.90E+00 Qmax= 0.10E+01
miqref = 0.12 ; moqref = 0.89 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 3 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 3 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 3 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 4 Remaillage de mail1 avec une taille voulue de 0.1 en touchant
* tout le bord
   mail4 = 'REMA' mail1 ('/' 1. nv) ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere en modifiant le bord' ;
      'TRAC' mail4 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 4 : on vérifie que le bord n'a pas été touché
* ceci est fait dans mailtopo
* Test 4 : on vérifie que les qualités mini, moyenne et maxi des éléments sont bonnes
qmail4 = 'INDI' 'TOPO' mail4 ;
miq = 'MINI' qmail4 ; moq = MATOUTIL 'MOYECHAM' qmail4 ;
maq = 'MAXI' qmail4 ;
'MESS' 'FORMAT' '(E9.2)' 'TEST 4 : Qmin=' miq ' Qmoy=' moq ' Qmax=' maq ;
   'SI' graph ;
      momail4 = 'MODE' mail4 'THERMIQUE' ;
      tit = 'CHAI' 'Qualite maillage avec bord modifie' ;
      'TRAC' qmail4 momail4 lqual 'TITR' tit ;
   'FINSI' ;
* Sur mon linux64 au 07/04/2020 : Qmin= 0.65E+00 Qmoy= 0.91E+00 Qmax= 0.10E+01
miqref = 0.64 ; moqref = 0.90 ; maqref = 0.99 ;
'SI' ('<EG' miq miqref) ;
   'MESS' '!!! TEST 4 : miq=' miq ' < miqref=' miqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' moq moqref) ;
   'MESS' '!!! TEST 4 : moq=' moq ' < moqref=' moqref ;
   lok = lok 'ET' faux ;
'FINS' ;
'SI' ('<EG' maq maqref) ;
   'MESS' '!!! TEST 4 : maq=' maq ' < maqref=' maqref ;
   lok = lok 'ET' faux ;
'FINS' ;
* TEST 5 Remaillage de mail4 avec une taille voulue de 0.1 en ne touchant
* plus le bord. On s'attend à ne pas changer le maillage mais
* c'est sans compter avec l'algorithme du noeud fictif qui nous
* a déjà fait des blagues
   mail5 = 'REMA' mail4 ('CONT' mail4) ('/' 1. nv) ;
   'SI' graph ;
      tit = 'CHAI' 'Maillage genere sans toucher le bord' ;
      'TRAC' mail5 'TITR' tit 'NOEU' ;
   'FINSI' ;
* Test 5 : on vérifie que mail5 et mail4 sont identiques ainsi que les
* qualités
dn45= 'NBEL' ('DIFF' mail4 mail5) ;
'SI' ('NEG' dn45 0) ;
   'MESS' '!!! TEST 5 : mail4 .NE. mail5' ;
   lok = lok 'ET' faux ;
'FINS' ;
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
* End of dgibi file MATO-2D4
'FIN' ;
```

## frenet_1 [Mathematiques Autres]
```
* VERIFICATION DE L'OPERATEUR FRENET
* LIGNE DROITE, CERCLE, ELLIPSE, CYCLOIDE, SPIRALE
* HELICE
* VERIFICATION EN DIMENSION 2
OPTI 'DIME' 2 'ELEM' 'SEG2' ;
* METTRE BTRAC = VRAI POUR TRACER LES RESULTATS
BTRAC = FAUX ;
* LISTMOTS POUR LES COMPOSANTES
TXY = MOTS 'TX' 'TY' ;
NXY = MOTS 'NX' 'NY' ;
* 1 - LIGNE DROITE
D1 = DROI 10 (0. 0.) (10. 0.) ;
CHPO1 = MANU 'CHPO' D1 2 'TX' 1. 'TY' 0. 'NATURE' 'DIFFUS' ;
CHPOREF = CHPO1 ;
* 2 - CERCLE COMPLET (FERME)
D2 = CERC 10 'ROTA' 360. (5. 0.) (0. 0.) ;
ELIM D2 1.E-10 ;
X Y = COOR D2 ;
CHPO1 = (NOMC 'TX' (0.-Y)) ET (NOMC 'TY' X) ;
NCHPO1 = (PSCA CHPO1 CHPO1 TXY TXY)**0.5 ;
CHPO1 = CHAN 'ATTRIBUT' (CHPO1 / NCHPO1) 'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
DEPL D2 'MOIN' (0. 8.) ;
DTOT = D1 ET D2 ;
* 3 - DEMI-CERCLE
D3 = CERC 10 'ROTA' 180. (5. 0.) (0. 0.) ;
X Y = COOR D3 ;
CHPO1 = (NOMC 'TX' (0.-Y)) ET (NOMC 'TY' X) ;
NCHPO1 = (PSCA CHPO1 CHPO1 TXY TXY)**0.5 ;
CHPO1 = CHAN 'ATTRIBUT' (CHPO1 / NCHPO1) 'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
DEPL D3 'MOIN' (0. 8.) ;
DEPL D3 'PLUS' (15. 0.) ;
DVER = DTOT ET (D3 ELEM (LECT 2 PAS 1 ((NBEL D3) - 1))) ;
DTOT = DTOT ET D3 ;
* 4 - ELLIPSE
T = PROG 0. PAS (2.*PI/40) (2.*PI) ;
B = 5. ;
A = 1.5 * B ;
X = A * (COS (180./PI*T)) ;
Y = B * (SIN (180./PI*T)) ;
LIG1 = QUEL (VALE 'ELEM') X Y ;
ELIM LIG1 1.E-10 ;
GEO1 = POIN (ENLE X (DIME X)) (ENLE Y (DIME Y)) ;
ELIM LIG1 GEO1 1.E-10 ;
TCHPO = MANU 'CHPO' GEO1 1 'T' (ENLE T (DIME T)) 'NATURE' 'DIFFUS' ;
CHPO1 = (NOMC 'TX' (-1. * A * (SIN (180./PI*TCHPO))))
       + (NOMC 'TY' (B * (COS (180./PI*TCHPO)))) ;
NCHPO1 = (PSCA CHPO1 CHPO1 TXY TXY)**0.5 ;
CHPO1 = CHAN 'ATTRIBUT' (CHPO1 / NCHPO1) 'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
DEPL LIG1 'MOIN' (15. 0.) ;
DVER = DVER ET LIG1 ;
DTOT = DTOT ET LIG1 ;
* 5 - CYCLOIDE
NDIS = 100 ;
T = PROG (2.*PI/NDIS) PAS (2.*PI/NDIS) ((2.*PI*(NDIS - 1))/NDIS) ;
X = T - (SIN (180./PI*T)) ;
Y = 1. - (COS (180./PI*T)) ;
CYC1 = QUEL (VALE 'ELEM') X Y ;
GEO1 = POIN X Y ;
ELIM CYC1 GEO1 1.E-10 ;
TCHPO = MANU 'CHPO' GEO1 1 'T' T 'NATURE' 'DIFFUS' ;
CHPO1 = (NOMC 'TX' (1. - (COS (180./PI*TCHPO))))
       + (NOMC 'TY' (SIN (180./PI*TCHPO))) ;
NCHPO1 = (PSCA CHPO1 CHPO1 TXY TXY)**0.5 ;
CHPO1 = CHAN 'ATTRIBUT' (-1. * CHPO1 / NCHPO1) 'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
DEPL CYC1 'PLUS' (0. 5.) ;
CYC1 = INVE CYC1 ;
DVER = DVER ET (CYC1 ELEM (LECT 2 PAS 1 ((NBEL CYC1) - 1))) ;
DTOT = DTOT ET CYC1 ;
* 6 - SPIRALE LOGARITHMIQUE
T = PROG 0. PAS (4.*PI/NDIS) (4.*PI) ;
B = 1.1 ;
X = (B**T)*(COS (180./PI*T)) ;
Y = (B**T)*(SIN (180./PI*T)) ;
SPI1 = QUEL (VALE 'ELEM') X Y ;
GEO1 = POIN X Y ;
ELIM SPI1 GEO1 1.E-10 ;
TCHPO = MANU 'CHPO' GEO1 1 'T' T 'NATURE' 'DIFFUS' ;
M1 = MOTS 'T' ;
COST = COS (180./PI*TCHPO) ;
SINT = SIN (180./PI*TCHPO) ;
BPT = B**TCHPO ;
CHPO1 = (NOMC 'TX' (BPT * ((COST*(LOG B)) - SINT) M1 M1 M1))
       + (NOMC 'TY' (BPT * ((SINT*(LOG B)) + COST) M1 M1 M1)) ;
NCHPO1 = (PSCA CHPO1 CHPO1 TXY TXY)**0.5 ;
CHPO1 = CHAN 'ATTRIBUT' (CHPO1 / NCHPO1) 'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
DEPL SPI1 'PLUS' (15. 5.) ;
DVER = DVER ET (SPI1 ELEM (LECT 2 PAS 1 ((NBEL SPI1) - 1))) ;
DTOT = DTOT ET SPI1 ;
* APPEL A FRENET
FREN1 = FREN DTOT ;
FREN1 = REDU FREN1 DVER ;
* VERIFICATION
* DETERMINATION DE LA NORMALE ANALYTIQUE
CHPO1 = PVEC CHPOREF TXY NXY ;
CHPOREF = REDU (CHPOREF ET CHPO1) DVER ;
* CALCUL DES ERREURS
DIF1 = FREN1 - CHPOREF ;
NORT = (PSCA DIF1 DIF1 TXY TXY)**0.5 ;
NORN = (PSCA DIF1 DIF1 NXY NXY)**0.5 ;
SI BTRAC ;
        T1 = VECT FREN1 TXY 'BLEU' ;
        N1 = VECT FREN1 NXY 'VERT' ;
        TRAC (T1 ET N1) DVER ;
        TRAC NORT DVER ;
        TRAC NORT DVER ;
        EVO1 = EVOL 'CHPO' NORT CYC1 ;
        DESS EVO1 ;
        EVO2 = EVOL 'CHPO' NORT SPI1 ;
        DESS EVO2 ;
FINSI ;
* VERIFICATION DES ERREURS
PRE1 = 1.E-2 ;
SI ((MAXI NORT) > PRE1) ;
        MESS 'ERREUR SUR LE VECTEUR TANGENT 2D' ;
        ERRE 5 ;
FINSI ;
SI ((MAXI NORN) > PRE1) ;
        MESS 'ERREUR SUR LE VECTEUR NORMAL 2D' ;
        ERRE 5 ;
FINSI ;
* VERIFICATION EN DIMENSION 3
OPTI 'DIME' 3 ;
* LISTMOTS POUR LES COMPOSANTES
TXYZ = MOTS 'TX' 'TY' 'TZ' ;
NXYZ = MOTS 'NX' 'NY' 'NZ' ;
BXYZ = MOTS 'BX' 'BY' 'BZ' ;
* ON COMPLETE LES REPERES ANALYTIQUES 2D
MCOMP = (MOTS 'TZ' 'NZ') ET BXYZ ;
CHPO1 = MANU 'CHPO' DTOT MCOMP (PROG 0. 0. 0. 0. 1.)'NATURE' 'DIFFUS' ;
CHPOREF = CHPOREF ET CHPO1 ;
CHPO1 = EXCO CHPOREF (TXYZ ET BXYZ) ;
CHPO2 = PVEC CHPO1 CHPO1 BXYZ TXYZ NXYZ ;
CHPO2 = CHAN 'ATTRIBUT' CHPO2 'NATURE' 'DIFFUS' ;
CHPOREF = EXCO (CHPO1 ET CHPO2) (TXYZ ET NXYZ) ;
* 7 - HELICE
A B = 5. 1. ;
NSEG = 120 * ((ENTI (EXTR (VALE 'ELEM') 4)) - 1) ;
T = PROG 0. PAS (6.*PI/NSEG) (6.*PI) ;
X = A * (COS (180.*T/PI)) ;
Y = A * (SIN (180.*T/PI)) ;
Z = B * T ;
HEL1 = QUEL (VALE 'ELEM') X Y Z ;
GEO1 = POIN X Y Z ;
ELIM HEL1 GEO1 1.E-10 ;
TCHPO = MANU 'CHPO' GEO1 1 'T' T 'NATURE' 'DIFFUS' ;
DENOM = ((A**2) + (B**2))**0.5 ;
CHPO1 = (NOMC 'TX' ((0. - A)/DENOM * (SIN (180.*TCHPO/PI)))) ET
        (NOMC 'TY' (A/DENOM * (COS (180.*TCHPO/PI)))) ET
                (MANU 'CHPO' HEL1 1 'TZ' (B/DENOM) 'NATURE' 'DIFFUS') ;
CHPO2 = (NOMC 'NX' (0. - (COS (180.*TCHPO/PI)))) ET
         (NOMC 'NY' (0. - (SIN (180.*TCHPO/PI)))) ET
                 (MANU 'CHPO' HEL1 1 'NZ' 0. 'NATURE' 'DIFFUS') ;
CHPOREF = CHPOREF ET CHPO1 ET CHPO2 ;
DEPL HEL1 'MOIN' (10. 0. 0.) ;
DEPL HEL1 'PLUS' (0. 10. 0.) ;
DVER = DVER ET (HEL1 ELEM (LECT 2 PAS 1 ((NBEL HEL1) - 1))) ; ;
DTOT = DTOT ET HEL1 ;
* APPEL A FRENET
FREN2 = FREN DTOT ;
FREN2 = REDU FREN2 DVER ;
* VERIFICATION
* DETERMINATION DE LA BINORMALE ANALYTIQUE
CHPO1 = PVEC CHPOREF CHPOREF TXYZ NXYZ BXYZ ;
CHPO1 = CHAN 'ATTRIBUT' CHPO1 'NATURE' 'DIFFUS' ;
CHPOREF = REDU (CHPOREF ET CHPO1) DVER ;
* CALCUL DES ERREURS
DIF2 = FREN2 - CHPOREF ;
NORT = (PSCA DIF2 DIF2 TXYZ TXYZ)**0.5 ;
NORN = (PSCA DIF2 DIF2 NXYZ NXYZ)**0.5 ;
NORB = (PSCA DIF2 DIF2 BXYZ BXYZ)**0.5 ;
SI BTRAC ;
        T1 = VECT FREN2 TXYZ 'BLEU' ;
        N1 = VECT FREN2 NXYZ 'VERT' ;
        B1 = VECT FREN2 BXYZ 'ROUG' ;
        TRAC (T1 ET N1 ET B1) DVER ;
        TRAC NORT DVER ;
        TRAC NORN DVER ;
        TRAC NORB DVER ;
        TRAC NORT DVER ;
        TRAC NORN DVER ;
        TRAC NORB DVER ;
        EVO1 = EVOL 'CHPO' NORT CYC1 ;
        DESS EVO1 ;
        EVO2 = EVOL 'CHPO' NORT SPI1 ;
        DESS EVO2 ;
        EVO3 = EVOL 'CHPO' NORT HEL1 ;
        DESS EVO3 ;
FINSI ;
* VERIFICATION DES ERREURS
SI ((MAXI (REDU NORT DVER)) > PRE1) ;
        MESS 'ERREUR SUR LE VECTEUR TANGENT 3D' ;
        ERRE 5 ;
FINSI ;
SI ((MAXI (REDU NORN DVER)) > PRE1) ;
        MESS 'ERREUR SUR LE VECTEUR NORMAL 3D' ;
        ERRE 5 ;
FINSI ;
SI ((MAXI (REDU NORB DVER)) > PRE1) ;
        MESS 'ERREUR SUR LA BINORMALE 3D' ;
        ERRE 5 ;
FINSI ;
FIN ;
```

## proi-parallele [Mathematiques Elementaires]
```
'OPTI' echo 0 ;
* NOM : PROI-PARALLELE
* DESCRIPTION : On teste le parallélisme avec les assistants pour faire
* un PROI en parallèle
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stephane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
* mel : stephane.gounand@cea.fr
* VERSION : v1, 31/07/2019, version initiale
* HISTORIQUE : v1, 31/07/2019, création
* HISTORIQUE :
* HISTORIQUE :
interact= FAUX ;
'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
p1 = 0. 0. ; p2 = 1.5 0.1 ;
p3 = 1.4 1.3 ; p4 = 0.1 1.3 ;
n1 = 3 ; n2 = 4 ; n3 = 5 ; n4 = 6 ;
cnt = 'DROI' n1 p1 p2 'DROI' n2 p3 'DROI' n3 p4 'DROI' n4 p1 ;
sur = 'SURF' cnt ;
x y = 'COOR' sur ;
r = '**' ('+' ('**' x 2) ('**' y 2)) 0.5 ;
chamr = 'CHAN' 'CHAM' r sur ;
lok = vrai ;
* PROI sur les points de sur
mail = 'CHAN' 'POI1' sur ;
* Sequentiel
chpors = 'PROI' chamr mail ;
errs = 'MAXI' ('-' chpors r) 'ABS' ;
* l'erreur vaut 5.d-9 sur ma machine au 31/07/2019
* l'erreur vaut 5.44493E-08 sur semt2 au 01/08/2019
crit1 = 1.D-7 ;
'MESS' 'errs=' errs ' crit1=' crit1 ;
tst1 = errs '<' crit1 ;
lok = lok 'ET' tst1 ;
* Parallele
nbpart = 'VALEUR' 'ASSI' ;
mapart = 'PART' 'ARLE' mail nbpart ;
tchpo = 'ASSI' 'TOUS' 'PROI' chamr mapart ;
* sg 23/03/2016 recommande par Clement
* chpo = 'ET' tchpo ;
chporp = 'ETG' tchpo ;
* la difference entre PROI parallele et sequentiel doit etre nulle
errps = 'MAXI' ('-' chporp chpors) 'ABS' ;
crit2 = ('VALE' 'PETI') '*' 10. ;
'MESS' 'errps=' errps ' crit2=' crit2 ;
tst2 = errps '<' crit2 ;
lok = lok 'ET' tst2 ;
'SAUT' 1 'LIGNE' ;
'SI' lok ;
   'MESSAGE' 'Tout sest bien passe' ;
'SINON' ;
   'MESSAGE' '!!! Il y a eu des erreurs' ;
'FINSI' ;
'SAUT' 1 'LIGNE' ;
'SI' interact ;
   'OPTION' 'DONN' 5 'ECHO' 1 ;
'FINSI' ;
'SI' ('NON' lok) ;
   'ERREUR' 5 ;
'FINSI' ;
* End of dgibi file PROI-PARALLELE
'FIN' ;
```

## condense1 [Mathematiques Fonctions]
```
* CAST TEST PORTANT SUR L'OPÉRATEUR SUPE
* Principe :
* On considère une matrice formée de l'assemblage
* d'une matrice de rigidité rig1
* de matrice de blocage nuls cl1 et cl2
* d'une matrie de masse massc1
* d'une  de blocage cl3
* et un chargement formé de
* de deplacement non nuls sur cl3: chpd0
* de forces reparties : chpfi
* On resoud indirectement par condensation sur les
* multiplicateurs de Lagrange de cl3 puis par
* une redescente sur tous les neouds
* On résoud directement
* On teste en particulier la normalisation des
* multiplicateur de Lagrange lorsque'ils sont maitres
* en choissant un module d'YOUNG une densité  élévés
* degay 20 02 97
* ========== taille du maillage ======================
m = 30 ;
n = m ;
E1 = 1.d15 ;
r0 = 7.d6 ;
graph = faux ;
* ========== maillage ================================
'OPTI' 'DIME' 2 'MODE' 'PLAN' 'DEFO';
'OPTI' 'ELEM' 'SEG2';
p1 = 0. 0. ;
p2 = 10. 0. ;
li1 = d p1 n p2 ;
opti elem qua4 ;
su1 = tran li1 m ( 0. 1. ) ;
ls1 = cote 3 su1 ;
P3 = 'POINT' su1 'PROC' ( 10. 1. ) ;
P4 = 'POINT' su1 'PROC' ( 0. 1. ) ;
lr0 = cote 4 su1 ;
lr10 = cote 2 su1 ;
* rotation du maillage de 45 pour avoir des conditions
* aux limites composées
'DEPL' su1 'TOUR' 45. ( 0. 5. ) ;
* ============== modle et matériau ===================
mod1 = 'MODE' su1 mecanique elastique ;
mod2 = 'MODE' ( li1 et ls1 ) mecanique elastique coq2 ;
mat1 = 'MATE' mod1 'YOUN' E1 'NU' 0.3 'RHO' r0 ;
mat2 = 'MATE' mod2 'YOUN' E1 'NU' 0.3 'RHO' r0 'EPAI' 0.05 ;
* =============== matrices classique ==================
mas1 = 'MASS' mod1 mat1 ;
mas2 = 'MASS' mod2 mat2 ;
massc1 = mas1 'ET' mas2 ;
rig1 = 'RIGI' ( mod1 'ET' mod2 ) ( mat1 'ET' mat2 ) ;
* ============ matrice lumpée "elementaire" ============
masd12 = lump mod2 mat2 ;
* ================= conditions aux limites =============
cl1 = bloq p1 'UX' ;
cl2 = 'SYMT' lr0 'DEPL' P1 P4 0.01 ;
cl3 = 'SYMT' lr10 'DEPL' P2 P3 0.01 ;
* cl3 = 'BLOQ' lr10 'UX' ;
rigt1 = rig1 et cl1 et cl2 et massc1 ;
rigt2 = rigt1 et cl3 ;
* ================= Condensation ========================
mailmult = 'EXTR' cl3 'MAIL' 'MULT' ;
sup1 = 'SUPE' 'RIGI' rigt2 mailmult ;
rigc1 = 'EXTR' sup1 'RIGI' ;
* ================= Chargement ===========================
* on impose un deplacement unité de lr10 selon l'axe de la plaque
chpd0 = 'DEPI' cl3 1. ;
* une alternative à DEPI est la commande suivante
* chp0 = 'MANU' 'CHPO' ( mailmult ) 1 'FLX' 1. ;
* on applique des forces sur le maillage
chpfi = 'CHPOINT' 'ALEATOIRE' ( mas1 et mas2 ) ;
chpfi = 'NOMC' chpfi ( 'MOTS' 'UX  ' 'UY  ' 'RZ  ' )
                    ( 'MOTS' 'FX  ' 'FY  ' 'MZ  ' )
         'NATU' 'DISCRET' ;
* ============ résolution indirecte ====================
chpfci = 'SUPE' sup1 'CHAR' (chpfi et chpd0) ;
depfl0 = 'RESO' rigc1 chpfci ;
* on redescend
dep0 = 'SUPER' 'DEPL' sup1 depfl0 (chpfi et chpd0);
chpf0 = 'REAC' cl3 dep0;
* ============== resolution directe =======================
dept1 = 'RESO' rigt2 ( chpd0 'ET' chpfi ) ;
dep1 = 'ENLE' dept1 'LX' ;
chpf1 = 'REAC' cl3 dept1 ;
* =============== Comparaison ============================
'OPTI' 'ECHO' 0 ;
* Erreur sur le deplacement
deperr = dep0 - dep1 ;
erx = 'EXCO' deperr 'UX' 'SCAL' / ( 'MAXI' 'ABS' ( 'EXCO' dep1 'UX'));
errx = ( 'MAXI' 'ABS' erx) ;
MESS 'Erreur sur X' ( errx * 100.) '%' ;
ery = 'EXCO' deperr 'UY' 'SCAL' / ( 'MAXI' 'ABS' ( 'EXCO' dep1 'UY'));
errY = ( 'MAXI' 'ABS' erY) ;
MESS 'Erreur sur Y' ( erry * 100.) '%' ;
erz = 'EXCO' deperr 'RZ' 'SCAL' ;
errz = ( 'MAXI' 'ABS' erz) ;
MESS 'Erreur sur RZ' (errz * 1.) 'difference absolue' ;
errtot = ( erx ** 2 ) + ( ery ** 2 ) ;
'OPTI' 'ECHO' 1 ;
'SI' graph ;
'TITR' 'Niveau d erreur' ;
'TRAC' errtot su1 ;
'FINSI' ;
* erreur sur les forces
ferr = chpf1 '-' chpf0 ;
errf = 'MAXI' 'ABS' ferr / ( 'MAXI' 'ABS' chpf0 ) ;
'MESS' 'Erreur sur les forces' ( errf '*' 100.) '%' ;
* Code de fonctionnement
'SI' ((errx > 1.D-9) 'OU' (erry > 1.D-9) 'OU' (errf > 1.D-9 ));
   'ERREUR' 5 ;
'SINON'
   'ERREUR' 0 ;
'FINSI' ;
'FIN' ;
```

## filc_test [Mathematiques Fonctions]
```
* Cas test de la procedure FILC
* Developpe par :
* Alberto FRAU (alberto.frau[at]cea.fr)
* Benjamin RICHARD (benjamin.richard[at]cea.fr)
* Institution :
* CEA/DEN/DANS/DM2S/SEMT/EMSI
* Commentaires
* On teste la procedure avec une signal composé de deux
* harmoniques et on verifie que le signal filtré l'harmonique
* de frequence plus elevee est bien filtree
* Parametres pour la definition du signal d'entree
T0 = 0.;
TMAX1 = 5.;
DT1 = 1/((2.)*(40.));
FO1 = 2.;
FO2 = 10.;
AMP1 = 2.;
GRAP1 = CHAINE 'N';
* Construction du signal par la somme des deux harmoniques (2Hz et 10Hz)
LL1 = PROG T0 PAS DT1 TMAX1;
VAL1 = ((((2)*(PI))*(FO1))/(PI))*(180.);
VAL2 = ((((2)*(PI))*(FO2))/(PI))*(180.);
LL2 = ((AMP1)*(SIN((VAL1)*(LL1)))) + ((SIN((VAL2)*(LL1))));
EV1 = EVOL MANU LL1 LL2;
EV1 = EV1 COUL BLEU;
* Filtrage à 5 Hz
EV2 = FILC EV1 5. 0.1;
EV2 = EV2 COUL ROUG;
SI ('NEG' GRAP1 'N');
  DESS (EV1 ET EV2);
FINSI;
* Test
SI (((MAXI (EXTR EV2 ORDO)) - (AMP1)) > 0.01);
  ERREUR 5;
FINSI;
FIN;
```

## ftran_test [Mathematiques Fonctions]
```
* Cas test de la procedure FTRAN
* Developpe par :
* Alberto FRAU (alberto.frau[at]cea.fr)
* Benjamin RICHARD (benjamin.richard[at]cea.fr)
* Institution :
* CEA/DEN/DANS/DM2S/SEMT/EMSI
* Commentaires
* On calcule la solution d'un oscillateur 1DDL et on deduit
* la fonction de transfert entre le deplacement au sommet et la
* force appliquée au meme point
* Options
OPTI DIME 3 MODE TRID ELEM SEG2;
* Sortie graphique
GRAP1 = CHAINE 'N';
* Caracteristique oscillatuer
FR_OSC1 = 20.;
OM_OSC1 = ((2)*(PI))*(FR_OSC1);
EP_OSC1 = 0.5;
M_OSC1 = 1000.;
K_OSC1 = ((OM_OSC1)**(2))*(M_OSC1);
* Caracteristique force
AMP_FOR1 = 100.;
FR_FOR1 = 2.;
OM_FOR1 = ((2)*(PI))*(FR_FOR1);
FMAX1 = 80.;
TMAX1 = (20.)/(FR_FOR1);
* Determination des coef pour la solution analytique
BETA1 = (OM_FOR1)/(OM_OSC1);
A1 = ((-1)*(((AMP_FOR1)/(K_OSC1))*((((2)*(EP_OSC1))*(BETA1))/(((1 - ((BETA1)**(2)))**(2)) + (((2)*(EP_OSC1))*(BETA1)**(2))))));
B1 = (((-1)*(OM_FOR1/OM_OSC1))*(((AMP_FOR1)/(K_OSC1))* (((1 - ((BETA1)**(2)))/ (((1 - ((BETA1)**(2)))**(2)) + (((2)*(EP_OSC1))*(BETA1)**(2)))))));
* Definition des plages temporelle et frequentielle
DT1 = (1)/((2)*(FMAX1));
LT1 = PROG 0. PAS DT1 TMAX1;
* Determination du deplacement et de la vitesse
OM_OSC2 = ((OM_OSC1)/(PI))*(180);
OM_FOR2 = ((OM_FOR1)/(PI))*(180);
LU1 = ((EXP(((-1)*(EP_OSC1))*(LT1)))*(((A1)*(COS((OM_OSC2)*(LT1)))) + (((B1)*(SIN((OM_OSC2)*(LT1))))))) + (((AMP_FOR1)/(K_OSC1))* ((((1 - ((BETA1)**(2)))*(SIN((OM_FOR2)*(LT1)))) - (((EP_OSC1)* ((BETA1)**(2)))*(COS((OM_FOR2)*(LT1)))))/((((1 - ((BETA1)**(2)))**(2)) + (((2)*(EP_OSC1))*(BETA1)**(2))))));
LV1 = (((EXP(((-1)*(EP_OSC1))*(LT1)))*(OM_OSC1))*(((A1)*((-1)* (SIN((OM_OSC2)*(LT1))))) + (((B1)*(COS((OM_OSC2)*(LT1))))))) + ((((AMP_FOR1)*(OM_FOR1))/(K_OSC1))*((((1 - ((BETA1)**(2)))* (COS((OM_FOR2)*(LT1)))) + (((EP_OSC1)*((BETA1)**(2)))* (SIN((OM_FOR2)*(LT1)))))/((((1 - ((BETA1)**(2)))**(2)) + (((2)*(EP_OSC1))*(BETA1)**(2))))));
* Evolution de la force
LF1 = (AMP_FOR1)*(SIN((OM_FOR2)*(LT1)));
EV_FOR1 = EVOL (ROUG) MANU 'Temps [s]' LT1 'Forc [N]' LF1;
EV_DEP1 = EVOL (BLEU) MANU 'Temps [s]' LT1 'Depl [m]' LU1;
EV_VIT1 = EVOL (VERT) MANU 'Temps [s]' LT1 'Depl [m]' LV1;
SI ('NEG' GRAP1 'N');
  DESS EV_FOR1 TITR 'Evolution de la force';
  DESS EV_DEP1 TITR 'Evolution du deplacement';
  DESS EV_VIT1 TITR 'Evolution de la vitesse';
FINSI;
F_TTR1 = FTRAN EV_DEP1 EV_FOR1 FMAX1 1;
SI ('NEG' GRAP1 'N');
  DESS F_TTR1 TITR 'Fonction de Transfert';
FINSI;
II1 VAL_X DENS1 = MAXI F_TTR1;
* Test sur la frequence de l'oscillateur
SI ((ABS(VAL_X - FR_OSC1)) > 0.00001);
 ERREUR 5;
FINSI;
FIN;
```

## gamma [Mathematiques Fonctions]
```
* Cas-test de VERIFICATION et VALIDATION pour les operateurs
* GAMM (Fonction Gamma d'Euler)
* BESS (Fonction Bessel)
'OPTI' 'TRAC' 'PSC';
'OPTI' 'EPTR' 5 ;
* Fonctions Gamma d'Euler
 LRG ='PROG' -4.995 'PAS' 0.01 4.995 ;
 LG1 ='GAMM' LRG ;
 EVG ='EVOL' 'BRIQ' 'MANU' LRG LG1 ;
 Tit1 ='CHAI' 'Fonction Gamma : \G(x)';
'DESS' EVG 'TITR' Tit1 'TITX' 'x' 'TITY' '\G(x)' 'AXES' 'XBOR' -5. 5. 'YBOR' -5. 5. ;
* VALIDATION : relation de recurrence : Gamma(x+1) = x * Gamma(x)
 LG2 = 'GAMM' (LRG + 1) ;
 Verif_G =(LG2 / (LRG * LG1)) - 1.D0 ;
* Erreur le cas echeant
 Max_Err_G ='MAXI' 'ABS' Verif_G ;
 XPREC_G =('VALE' 'PREC') * 100. ;
'SI' (Max_Err_G '>' XPREC_G );
   'MESS' 'Fonction GAMMA incorrecte : Erreur relative =' Max_Err_G ;
   'ERRE' 5 ;
'FINS';
* Fonctions de Bessel de type J
 LRJ ='PROG' -20. 'PAS' 0.01 20. ;
 LBJ0 ='BESS' 'J0' LRJ ;
 LBJ1 ='BESS' 'J1' LRJ ;
 LBJ2 ='BESS' 'JN' 2 LRJ ;
 EVJ0 ='EVOL' 'BRIQ' 'MANU' LRJ LBJ0 ;
 EVJ1 ='EVOL' 'BOUT' 'MANU' LRJ LBJ1 ;
 EVJ2 ='EVOL' 'BLEU' 'MANU' LRJ LBJ2 ;
 EVJ_Tot = EVJ0 'ET' EVJ1 'ET' EVJ2 ;
 TLEG1 ='TABL' ;
 TLEG1.'TITRE' ='TABL' ;
 TLEG1.'TITRE'. 1 ='CHAI' 'f(x) = Bessel J_{0}(x)' ;
 TLEG1.'TITRE'. 2 ='CHAI' 'f(x) = Bessel J_{1}(x)' ;
 TLEG1.'TITRE'. 3 ='CHAI' 'f(x) = Bessel J_{2}(x)' ;
 Tit1 ='CHAI' 'Fonction de Bessel de type J';
'DESS' EVJ_Tot 'LEGE' TLEG1 'NE' 'TITR' Tit1 'TITX' 'x' 'TITY' 'f(x)' 'AXES' 'YBOR' -1. 1.;
* VALIDATION : relation de recurrence sur les Jn : J0(x) + J2(x) = 2 * J1(x) / x
 Verif_J =(LRJ * (LBJ0 + LBJ2) / (2. * LBJ1)) - 1.D0 ;
* Erreur le cas echeant
 Max_Err_J ='MAXI' 'ABS' Verif_J ;
 XPREC_J =('VALE' 'PREC') * 2100. ;
'SI' (Max_Err_J '>' XPREC_J );
   'MESS' 'Fonctions BESSEL J_n(x) incorrectes : Erreur relative =' Max_Err_J XPREC_J ;
   'ERRE' 5 ;
'FINS';
* Fonctions de Bessel de type Y
 LRY ='PROG' 0.04 'PAS' 0.01 20. ;
 LBY0 ='BESS' 'Y0' LRY ;
 LBY1 ='BESS' 'Y1' LRY ;
 LBY2 ='BESS' 'YN' 2 LRY ;
 EVY0 ='EVOL' 'BRIQ' 'MANU' LRY LBY0 ;
 EVY1 ='EVOL' 'BOUT' 'MANU' LRY LBY1 ;
 EVY2 ='EVOL' 'BLEU' 'MANU' LRY LBY2 ;
 EVY_Tot = EVY0 'ET' EVY1 'ET' EVY2 ;
 TLEG1 ='TABL' ;
 TLEG1.'TITRE' ='TABL' ;
 TLEG1.'TITRE'. 1 ='CHAI' 'f(x) = Bessel Y_{0}(x)' ;
 TLEG1.'TITRE'. 2 ='CHAI' 'f(x) = Bessel Y_{1}(x)' ;
 TLEG1.'TITRE'. 3 ='CHAI' 'f(x) = Bessel Y_{2}(x)' ;
 Tit1 ='CHAI' 'Fonction de Bessel de type Y';
'DESS' EVY_Tot 'LEGE' TLEG1 'SE' 'TITR' Tit1 'TITX' 'x' 'TITY' 'f(x)' 'AXES' 'YBOR' -2. 1.;
* VALIDATION : relation de recurrence sur les Y_n : Y0(x) + Y2(x) = 2 * Y1(x) / x
 Verif_Y =(LRY * (LBY0 + LBY2) / (2. * LBY1)) - 1.D0 ;
* Erreur le cas echeant
 Max_Err_Y ='MAXI' 'ABS' Verif_Y ;
 XPREC_Y =('VALE' 'PREC') * 2000. ;
'SI' (Max_Err_Y '>' XPREC_Y );
   'MESS' 'Fonctions BESSEL Y_n(x) incorrectes : Erreur relative =' Max_Err_Y XPREC_Y ;
   'ERRE' 5 ;
'FINS';
FIN;
```

## identifi [Mathematiques Fonctions]
```
* soit le polynome du 3eme degre y=a*x*x*x + b*x*x + c*x + d
* on suppose connue la valeur d'une fonction G pour les
* abscisses x= 1, 2, 3, 4 et 5 .On recherche les coeffiecients a b c d
* de la fonction Y (polynome du troisieme degré) qui ajuste au mieux la
* fonction G sur les points connus.
* poly est une procédure calculant la fonction Y pour des valeurs de
* a b c d données en argument et pour les valeurs expérimentales de x
debp poly a*flottant b*flottant c*flottant d*flottant;
  x=1 ;
  f1=(a*x*x*x) + (x*x*b) + ( c * x ) + d ;
  x=2;
  f2=(a*x*x*x) + (x*x*b) + ( c * x ) + d ;
  x=3;
  f3=(a*x*x*x) + (x*x*b) + ( c * x ) + d ;
  x=4;
  f4=(a*x*x*x) + (x*x*b) + ( c * x ) + d ;
  x=5;
  f5=(a*x*x*x) + (x*x*b) + ( c * x ) + d ;
  ll=prog f1 f2 f3 f4 f5;
finpro ll;
* Nous choisissons la base connue de G corerspondant à un polynome du
* 3eme degré avec a=2 b=3 c=4 d=5 . Nous devons donc retrouver ces
* valeurs pour a b c d.
fG = poly 2. 3. 4. 5.;
* on cherche par l'opérateur MOCA les valeurs de a b c d
* on suppose un point de départ a=1 b=-1. c=10; d=8.
a=1.;
b=-1.;
c=10.;
d = 8.;
fdep = poly a b c d ;
* calcul de la fonction y pour ces paramètres et pour les abscisses
depa = prog a b c d ;
* calcul des "dérivées partielles" par rapport à : a , b , c , d par
* différence finie
debproc deriv a*flottant b*flottant c*flottant d*flottant fdep*listreel;
  deri_a= ((poly (a*1.01) b c d) - fdep)/( a*0.01);
  deri_b= ((poly a (b*1.01) c d) - fdep)/ (b*0.01);
  deri_c =((poly a b (c*1.01) d) - fdep)/(C*0.01);
  deri_d =((poly a b c (d*1.01)) - fdep)/(D*0.01);
finproc deri_a deri_b deri_c deri_d ;
deri_a deri_b deri_c deri_d = deriv a b c d fdep;
ss = moca depa fG fdep deri_a deri_b deri_c deri_d ;
list ss;
sol = prog 2. 3. 4. 5. ;
er = abs ( ss - sol);
ermax1= maxi er;
* remarque : l'opérateur MOCA cherche à minimiser l'écart en moyenne
* quadratique entre la base expérimentale et la fonction F(a,b,c,d),
* supposée linéaire en a b c d. Le polynome Y étant bien linéaire
* en a b c d, il trouve la "bonne" solution.
* envisageons maintenant que la fonction Y soit y= a + bx + cx**d
* on peut utiliser la procedure ajuste
* parametres lineaires a b c
* parametre non lineaire d
* on peut ecrire la fonction sous la forme:
* y = a * f1 + b* f2 + c* f3;
* avec f1= 1 f2 = X f3 = x**d
debp fct xtab*table p*listreel;
    tab1=table;
    tab2=table;
    x = xtab . 1;
    n=dime x;
* fonction f1
    tab1.1 = prog n*1.;
    tab1.2 = x;
    tab1.3 = x**( extr p 1);
    tab2.'F'= tab1;
finproc tab2;
debproc deri xtab*table p*listreel;
    tab1=table;
    tab2=table;
    tabg=table;
    tabf=table;
    tab=table;
    x = xtab . 1;
    n=dime x;
* df1/dp1
    tab1 . 1=prog n*0.;
* df2/dp1
    tab1. 2 = prog n*0.;
* df3/dp1
    tab1. 3= ( log x) * (x** ( extr p 1));
    tabf . 1 = tab1;
    tab. 'F' = tabf;
finproc tab;
* fabriquons un cas "experimental" en
* posant a =1 b=-6 c=4 d=3 e et en prenant pour base des abscisses x
sol2= prog 1. -6. 4. 3.;
x = prog 0.1 0.3 0.5 1 2.5 3.6 6. 7.8 9 11; nexp=10;
* on va calculer nos "resultats experimentaux" : fobj
ct= prog nexp*1.;
bx = -6. * X;
cxpd= 4*( X ** 3);
fobj= ct + bx + cxpd;
* preparation des données pour appel ajuste
k=1;
L=3;
xtab=table;
xtab. 1= x;
tab1=table;
tab1.'X' = xtab;
tab1. 'F' = fobj;
tab1. 'K'= k;
tab1.'L'= L;
tab1.'PMIN'=prog 0. -12 -20 -2 ;
tab1.'PMAX' = prog 10. 26. 12. 4. ;
temps;
p q = ajuste tab1 ;
temps;
mess ' sortie de la procedur ajuste valeur trouvée :';
mess ' a = ' ( extr p 1) ' valeur attendue   1.';
mess ' b = ' ( extr p 2) ' valeur attendue  -6.';
mess ' c = ' ( extr p 3) ' valeur attendue   4.';
mess ' d = ' ( extr q 1) ' valeur attendue   3.';
ltrou= p et q;
era= abs (ltrou - sol2);
ermax2= maxi era;
* on peut aussi tenter de resoudre le probleme à l'aide de MOCA
* Comme la fonction n'est pas linéaire en fonction du parametre d
* la solution fournie ne sera pas la bonne. on utilise le résultat
* trouvé pour nous donner une direction de descente le long de laquelle
* on cherche un minimun de la "distance" entre Fcalculée et Fobjectif
* une approche par itération est necessaire
para = prog 2. 2. 2. 2.;
* procedure pour calculer la fonction
debproc fcal para*listreel x*listreel;
  n = dime x;
  fa= prog n*( extr para 1) ;
  fb= ( extr para 2)*x ;
  fc= ( extr para 3) * ( x ** ( extr para 4));
  ff= fa + fb + fc;
finproc ff;
* procedur pour calculer les derivees partielles
debproc fderiv para*listreel x*listreel ;
  n=dime x;
  fdera= prog n*1.;
  fderb= x * 1;
  fderc= x**(extr para 4);
  fderd = (extr para 3)*( log x) * (x** ( extr para 4));
finproc fdera fderb fderc fderd;
* procedure pour calculer le critère de distance
debproc criter fcalc*listreel fobjec*listreel ;
  cri= 0.;
  repe aa ( dime fcalc);
    cri = cri + ( ((extr fcalc &aa) - (extr fobjec &aa) )**2);
  fin aa;
finproc cri;
* schema iteratif
temps;
repeter iter 500;
  fdep = fcal para x; crii = criter fdep fobj;
  mess ' debut iteration ' &iter ' critère ' crii;
* on teste la convergence ( coutnouv - coutanc ) / coutanc < 1.e-4
  si ( &iter. ega 1) ;
    crianc = crii;
  sinon;
    cri_conv= ( crianc - crii ) / crianc;
    mess ' critère de convergence ' cri_conv;
    crianc= crii;
    si ( cri_conv < 1.e-4) ;
      mess ' convergence à l itération ' &iter ' cout ' crii;
      quitter iter;
    finsi;
  finsi;
  fdera fderb fderc fderd = fderiv para x ;
* list fobj;list fdep; list fdera ; list fderb; list fderc; list fderd;
  nouvpara= moca para fobj fdep fdera fderb fderc fderd;
* list nouvpara;
* recherche le long de la direction donnée par nouvpara - para
  desc= (nouvpara - para ) * 0.333333333;
  imu=1;
  repe ide 30;
    nouvpara= para + (desc * imu);
    fnou= fcal nouvpara x;
    cria= criter fnou fobj;
    si ( cria > crii );
      si ( imu ega 1) ;
        si (&ide < 6) ;
          desc = desc / 10.;
          iterer ide;
        sinon;
          mess ' pas de longueur trouvée le long de la descente';
          quitter iter;
        finsi;
      finsi;
* recherche d'un min par approximation parabilique
      aa = cri2 + cria - (2.*crii) / 2.;
      bb= cria - cri2 / 2.;
      xx = bb / -2. / aa ;
      iies= xx - 1. ;
      para= nouvpara + ( iies * desc);
      quitter ide;
    sinon;
      si ((imu ega &ide ) et (imu ega 9)) ;
        para= nouvpara;quitter ide;
      finsi;
        imu=imu+1 ;
        cri2=crii;
        crii=cria;
    finsi;
  fin ide;
fin iter;
temps;
mess ' résutats par utilisation de moca itératif';
mess ' a = ' ( extr para 1) ' valeur attendue   1.';
mess ' b = ' ( extr para 2) ' valeur attendue  -6.';
mess ' c = ' ( extr para 3) ' valeur attendue   4.';
mess ' d = ' ( extr para 4) ' valeur attendue   3.';
erb= abs ( para - sol2);
ermax3= maxi erb;
* utilisation de l'opérateur levmar
* il faut définir la procédure feval qui evalue la fonction
* à minimiser et qui calcule les derivées partielles
debproc feval x*listreel para*listreel;
  dy=prog;
  n=dime x;
  m = dime para;
  a1= extr para 1 ;
  b1= extr para 2;
  c1= extr para 3;
  d1= extr para 4;
  aa1 = prog n*a1;
  y= aa1 + ( b1 * x ) + ( c1 * ( x ** d1)) ;
  fdera= prog n*1.;
  fderb= x * 1;
  fderc= x**(extr para 4);
  fderd = (extr para 3)*( log x) * (x** ( extr para 4));
  l_dy=prog;
  ia=0;
  repe baa n;
    l_dy= l_dy et (prog ( extr fdera &baa));
    l_dy= l_dy et (prog ( extr fderb &baa));
    l_dy= l_dy et (prog ( extr fderc &baa));
    l_dy= l_dy et (prog ( extr fderd &baa));
  fin baa;
finp y l_dy;
aa = prog 2. 2. 2. 2.;sis = prog nexp*1. ;
temps;
a0 chi2 = 'LEVM' ABSC x ORDO fobj 'PARA' aa SIGM sis PROC feval ;
temps;
mess ' résultats par utilisation de levm ' ;
mess ' a = ' ( extr a0 1) ' valeur attendue   1.';
mess ' b = ' ( extr a0 2) ' valeur attendue  -6.';
mess ' c = ' ( extr a0 3) ' valeur attendue   4.';
mess ' d = ' ( extr a0 4) ' valeur attendue   3.';
erc = abs ( a0 - sol2);
ermax4= maxi erc;
message ' erreur pour moca ' ermax1;
message ' erreur pour ajuste ' ermax2;
message ' erreur pour moca ' ermax3;
message ' erreur pour levm ' ermax4;
si ( (ermax1 + ermax2 + ermax3 + ermax4 ) > 1.e-4);
   erreur 5;
'SINON';
   'ERREUR' 0 ;
finsi;
fin;
```

## isosurf [Mathematiques Fonctions]
```
* CAS TEST : isosurf.dgibi
GRAPH = FAUX ;
'SAUT' 'PAGE' ;
* TEST @ISOSURF
* ISOSURFACES POUR MAILLAGE DE TETRAHEDRES
* Test de la procedure qui extrait les isosurfaces dont les valeurs
* sont listées dans une liste (LIS1) d'un champoint (HANA1) appuyé
* sur un maillage (MASSIF0) exclusivement constitué de tetrahèdres
* (TET4).
* Le résultat final est constitué du maillage surfacique (TRI3)
* regroupant l'ensemble des isosurface MAIF1 et du champoint CHPF1
* des isovaleurs LIS1 appuyées sur MAIF1.
* Si GRAPH est faux, seule l'isosurface de valeur 1500 est extraite
* et un test de non regression est realise sur la base de
* l'apartenance d'un point de coordonnees analytiques a la surface
* extraite.
* Si GRAPH est vrai, le meme test de non regression est realise,
* mais 6 isosurfaces dont les valeurs sont listees dans LIS1 sont
* tracees.
'OPTION' 'ECHO' 1 ;
'TITRE' 'Isosurface Tetra' ;
OPTI DIME 3 ELEM TET4 ;
OPTI ISOV SURFACE ;
* --------------------- Création du maillage 3D ---------------------
EPSI1 = 0.000001 ;
* Dimensions de base
LX1 = 10.D0 ;
LY1 = 10.D0 ;
LZ1 = 10.D0 ;
* Points
* Points tetra
P1 = 0.D0 0.D0 0.D0 ;
P2 = LX1 0.D0 0.D0 ;
P3 = LX1 LY1 0.D0 ;
P4 = (LX1 / 2.D0) (LY1 / 4.D0) LZ1 ;
* Lignes base
ND1 = 13 ;
LXY1 = DROIT ND1 P1 P2 ;
LXY2 = DROIT ND1 P2 P3 ;
LXY3 = DROIT ND1 P3 P1 ;
COT1 = LXY1 ET LXY2 ET LXY3 ;
LZZ1 = DROIT ND1 P1 P4 ;
LZZ2 = DROIT ND1 P2 P4 ;
LZZ3 = DROIT ND1 P3 P4 ;
COT2 = LXY1 ET LZZ2 ET (INVE LZZ1) ;
COT3 = LXY2 ET LZZ3 ET (INVE LZZ2) ;
COT4 = LXY3 ET LZZ1 ET (INVE LZZ3) ;
* Surfaces
SUB1 = SURF COT1 'PLANE' ;
SUZ1 = SURF COT2 'PLANE' ;
SUZ2 = SURF COT3 'PLANE' ;
SUZ3 = SURF COT4 'PLANE' ;
SUT1 = SUB1 ET SUZ1 ET SUZ2 ET SUZ3 ;
ELIM EPSI1 SUT1 ;
* -- VOLUMES --
MASSIF0 = COUL ROUG (VOLU SUT1) ;
SI GRAPH ;
   TRAC CACH MASSIF0 ;
FINSI ;
* -- MAILLAGES QUAF --
QFTOT = CHANGE MASSIF0 QUAF ;
* -- MODELE--
MODHYB = 'MODELE' QFTOT 'DARCY' 'ANISOTROPE' ;
HYSOM = 'DOMA' MODHYB 'SOMMET' ;
XXS YYS ZZS = 'COOR' HYSOM ;
* Valeurs charges imposees
GRA1 = 2000.D0 ;
* Champoint
PI2 = 2.0D0 * 3.1414D0 ;
HANA1 = (COS (PI2 * (XXS - (LX1 / 2.D0))))
* (COS (PI2 * (XXS - (LX1 / 2.D0))))
* (COS (PI2 * (YYS - (LY1 / 2.D0))))
* (COS (PI2 * (YYS - (LY1 / 2.D0))))
* (COS (PI2 * (ZZS - (LZ1 / 2.D0))))
* (COS (PI2 * (ZZS - (LZ1 / 2.D0))))
* GRA1 ;
* ------------------Tracer champoint-----------------------------
SI GRAPH ;
   TRAC CACH HANA1 MASSIF0 ;
FINSI ;
* Liste des isovaleurs a extraire
LIS1 = PROG 1500.0 ;
SI GRAPH ;
   LIS1 = PROG 1900.0 1700.0 1500.0 800.0 1040.0 1200.0 ;
FINSI ;
* Procedure @isosurf
MAIF1 CHPF1 = @ISOSURF MASSIF0 LIS1 HANA1 ;
SI GRAPH ;
   TRAC CHPF1 MAIF1 ;
FINSI ;
CONT1 = COT1 ET COT2 ET COT3 ET COT4 ;
VAL1 = MINI HANA1 ;
CHP2 = MANU 'CHPO' CONT1 1 'SCAL' VAL1 'NATURE' 'DISCRET' ;
MAT1 = MAIF1 ET CONT1 ;
CHT1 = CHPF1 ET CHP2 ;
SI GRAPH ;
   TRAC CACH FACE CHT1 MAT1 ;
FINSI ;
* Verification de l'algoritme
* Un point de coordonnees XT1, YT1, ZT1 identifie comme
* appartenant a la surface d'isovaleur 1500.0D0 definie
* dans LIS1 est il reelement contenu dans l'isosurface extraite ?
VAL0 = (COS (PI2 * ((LY1 / 4.D0) - (LY1 / 2.D0))))
* (COS (PI2 * ((LY1 / 4.D0) - (LY1 / 2.D0)))) ;
VAL1 = (1500.0D0 / (GRA1 * VAL0)) ** 0.5D0 ;
VAL2 = ((1.D0 - (VAL1 * VAL1)) ** 0.5D0) / VAL1 ;
VAL3 = ATG (VAL2) ;
ZT1 = (VAL3 / PI2 ) + (LZ1 / 2.D0) ;
XT1 = LX1 / 2.D0 ;
YT1 = LY1 / 4.D0 ;
PV1 = XT1 YT1 ZT1 ;
OPTI ERREUR IGNORE ;
GEO1 = MAIF1 ELEM 'CONTENANT' PV1 ;
OPTI ERREUR NORMAL ;
MOT1 = TYPE GEO1 ;
SI (EGA MOT1 'ANNULE') ;
   MESS 'Point de reference hors isosurface' ;
   'ERREUR' 5 ;
FINSI ;
FIN ;
```

## parallelisation_CHPOINT [Mathematiques Fonctions]
```
* Cas-Test de Verification : Operations Elementaires CHPOINTS
* Ce cas test permet de verifier le bon fonctionnement de la
* parallelisation des operations elementaires suivantes sur l'objet de
* type CHPOINT :
* CHPO2 = CHPO1 ** FLOT1
* CHPO2 = CHPO1 ** ENTI1
* CHPO2 = CHPO1 * FLOT1
* CHPO2 = CHPO1 / FLOT1
* CHPO2 = CHPO1 + FLOT1
* CHPO2 = CHPO1 - FLOT1
* CHPO2 = FLOT1 - CHPO1
* CHPO2 = COS CHPO1
* CHPO2 = SIN CHPO1
* CHPO2 = TAN CHPO1
* CHPO2 = ACOS CHPO1
* CHPO2 = ASIN CHPO1
* CHPO2 = ATG CHPO1
* CHPO2 = EXP CHPO1
* CHPO2 = LOG CHPO1
* CHPO2 = ABS CHPO1
* CHPO2 = COSH CHPO1
* CHPO2 = SINH CHPO1
* CHPO2 = TANH CHPO1
* CHPO2 = ERF CHPO1
* CHPO2 = ERFC CHPO1
* CHPO2 = ACOH CHPO1
* CHPO2 = ASIH CHPO1
* CHPO2 = ATAH CHPO1
* MAILLAGE
opti dime 3 elem cub8;
a1 =0. 0. 0.;
a2 =1. 0. 0.;
a3 =0. 2. 0.;
* nbre d elements
nbel=50;
d1=a1 d nbel a2;
s1=d1 tran nbel (0. 2. 0.);
msh = s1 volu nbel tran (0. 0. 3.);
* CALCULS SUR LES CHPOINTS
X0 Y0 Z0 = COOR msh;
* TOTO = TABL;
NBBOUC = 80 ;
BDESS = FAUX;
* Test de Cohabitation ASSISTANTS / PTHREADS (Correction ANOMALIE 9297)
* Utilisation de ASSI 'TOUS' car en OPTI PARA VRAI; les CHPOINTS sont
* systématiquement fusionnes
NBPART = 40;
MSHPART = PART 'ARLE' NBPART (CHAN 'POI1' msh);
X0p Y0p Z0p= ASSI 'TOUS' COOR MSHPART;
CHPADD = TABL 'ESCLAVE';
REPE SURPAR NBPART;
  CHPADD.&SURPAR = &SURPAR ;
FIN SURPAR;
REPE SURI 1000;
  BTEST = VRAI;
  X1P = ASSI 'TOUS' X0p '*' 0. ;
  X2P = ASSI 'TOUS' X1p '+' CHPADD ;
  REPE SURPAR NBPART;
    BTEST = BTEST 'ET' ('EGA' ('MINI' X2P. &SURPAR) CHPADD. &SURPAR) ;
  FIN SURPAR;
  SI (NON BTEST);
    MESS 'Erreur dans les ASSISTANTS combines au PTHREADS';
    REPE SURPAR NBPART;
      MESS &SURPAR ('MINI' X2P. &SURPAR);
    FIN SURPAR;
    ERRE 21 ;
  FINS;
  DETR X2P;
  DETR X1P;
FIN SURI;
* PUISSANCE
SI VRAI;
  PUI1 = 0 ;
  REPE SURI NBBOUC;
   X11 = X0 ** PUI1 ;
   Y11 = Y0 ** PUI1 ;
   Z11 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X11 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 1 ;
  REPE SURI NBBOUC;
   X12 = X0 ** PUI1 ;
   Y12 = Y0 ** PUI1 ;
   Z12 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X12 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 4 ;
  REPE SURI NBBOUC;
   X13 = X0 ** PUI1 ;
   Y13 = Y0 ** PUI1 ;
   Z13 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X13 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 3.00 ;
  REPE SURI NBBOUC;
   X14 = X0 ** PUI1 ;
   Y14 = Y0 ** PUI1 ;
   Z14 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X14 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 0.5 ;
  REPE SURI NBBOUC;
   X15 = X0 ** PUI1 ;
   Y15 = Y0 ** PUI1 ;
   Z15 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X15 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 1./5. ;
  REPE SURI NBBOUC;
   X16 = X0 ** PUI1 ;
   Y16 = Y0 ** PUI1 ;
   Z16 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X16 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  PUI1 = 2.4 ;
  REPE SURI NBBOUC;
   X17 = X0 ** PUI1 ;
   Y17 = Y0 ** PUI1 ;
   Z17 = Z0 ** PUI1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X17 D1;
    TIT1 = CHAI 'PUISSANCE' PUI1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
* ADDITION
SI VRAI;
  ADD1 = 2. ;
  REPE SURI NBBOUC;
   X3 = X0 + ADD1 ;
   Y3 = Y0 + ADD1 ;
   Z3 = Z0 + ADD1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X3 D1;
    TIT1 = CHAI 'ADDITION' ADD1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
* SOUSTRACTION
SI VRAI;
  SOU1 = 2. ;
  REPE SURI NBBOUC;
   X4 = X0 - SOU1 ;
   Y4 = Y0 - SOU1 ;
   Z4 = Z0 - SOU1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X4 D1;
    TIT1 = CHAI 'SOUSTRACTION' SOU1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  SOU1 = 2. ;
  REPE SURI NBBOUC;
   X5 = SOU1 - X0 ;
   Y5 = SOU1 - Y0 ;
   Z5 = SOU1 - Z0 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X5 D1;
    TIT1 = CHAI 'SOUSTRACTION' SOU1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
* DIVISION
SI VRAI;
  DIV1 = 10. ;
  REPE SURI NBBOUC;
   X6 = X0 / DIV1 ;
   Y6 = Y0 / DIV1 ;
   Z6 = Z0 / DIV1 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X6 D1;
    TIT1 = CHAI 'DIVISION' DIV1;
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
* FONCTIONS
SI VRAI;
  REPE SURI NBBOUC;
   X7 = COS (X0 * (180. / (MAXI X0))) ;
   Y7 = COS Y0 ;
   Z7 = COS Z0 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'COSINUS';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = SIN (X0 * (180. / (MAXI X0))) ;
   Y7 = SIN Y0 ;
   Z7 = SIN Z0 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'SINUS';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = TAN (X0 * (45. / (MAXI X0))) ;
   Y7 = TAN Y0 ;
   Z7 = TAN Z0 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'TANGENTE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ACOS (X0 / (MAXI X0)) ;
   Y7 = ACOS (Y0 / (MAXI Y0)) ;
   Z7 = ACOS (Z0 / (MAXI Z0)) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ARC COSINUS';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ASIN (X0 / (MAXI X0)) ;
   Y7 = ASIN (Y0 / (MAXI Y0)) ;
   Z7 = ASIN (Z0 / (MAXI Z0)) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ARC SINUS';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ATG (X0 / (MAXI X0)) ;
   Y7 = ATG (Y0 / (MAXI Y0)) ;
   Z7 = ATG (Z0 / (MAXI Z0)) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ARC TANGENTE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = EXP X0 ;
   Y7 = EXP Y0 ;
   Z7 = EXP Z0 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'EXPONENTIELLE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = LOG (X0 + 1.) ;
   Y7 = LOG (Y0 + 1.) ;
   Z7 = LOG (Z0 + 1.) ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'LOGARITHME';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ABS (-2. * X0) ;
   Y7 = ABS (-3. * Y0) ;
   Z7 = ABS (-4. * Z0) ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'VALEUR ABSOLUE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = COSH (X0 - 0.5) ;
   Y7 = COSH (Y0 - 0.5) ;
   Z7 = COSH (Z0 - 0.5) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'COSINUS HYPERBOLIQUE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = SINH (5. * (X0 - 0.5)) ;
   Y7 = SINH (Y0 - 0.5) ;
   Z7 = SINH (Z0 - 0.5) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'SINUS HYPERBOLIQUE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = TANH (2. * (X0 - 0.5)) ;
   Y7 = TANH (Y0 - 0.5) ;
   Z7 = TANH (Z0 - 0.5) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'TANGENTE HYPERBOLIQUE';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ERF (2. * (X0 - 0.5)) ;
   Y7 = ERF (Y0 - 0.5) ;
   Z7 = ERF (Z0 - 0.5) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ERF';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ERFC (2. * (X0 - 0.5)) ;
   Y7 = ERFC (Y0 - 0.5) ;
   Z7 = ERFC (Z0 - 0.5) ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ERFC';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ACOH (X0+1.) ;
   Y7 = ACOH (Y0+1.) ;
   Z7 = ACOH (Z0+1.) ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ACOH';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ASIH X0 ;
   Y7 = ASIH Y0 ;
   Z7 = ASIH Z0 ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ASIH';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
SI VRAI;
  REPE SURI NBBOUC;
   X7 = ATAH ((X0 - 0.5)*1.9) ;
   Y7 = ATAH ((Y0 * 0.9) / (MAXI Y0)) ;
   Z7 = ATAH ((Z0 * 0.9) / (MAXI Z0 )) ;
* TOTO.&SURI = X1 ;
  FIN SURI;
  SI (BDESS) ;
    EVO1 = EVOL 'CHPO' X7 D1;
    TIT1 = CHAI 'ATAH';
    DESS EVO1 'TITR' TIT1;
  FINSI;
FINS;
TEMP 'IMPR';
FIN;
```

## Pres_Mass [Mathematiques Fonctions]
```
* Test Pres_Mass.dgibi: Jeux de données
* Auteur : CB215821
* Creation : 24/08/2015
* Modifications :
* TEST PRES_MASS : Non-Regression
* Pression Nulle appliquee sur un cote d'un cube de cote 1
* Ce cas Test permet de s'assure qu'imposer une pression nulle
* sur une surface d'un MAILLAGE MASSIF fonctionne correctement.
* En effet, le traitement de la pression P=0.D0 est différent et
* presentait une anomalie.
OPTI DIME 3 ELEM CUB8 ;
P1 = 0. 0. 0. ;
P2 = 1. 0. 0. ;
L1 = DROI 10 P1 P2 ;
S1 = TRAN L1 10 (0. 1. 0.) ;
V1 = VOLU S1 10 'TRAN' (0. 0. 1.);
MOD1 = MODE V1 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE';
* Application de la pression nulle sur la surface S1 :
CHPO1 = PRES 'MASS' MOD1 0.D0 S1;
MAX1 = MAXI CHPO1;
LIST MAX1;
SI (MAX1 > 0.D0);
  ERRE 5;
FINS;
FIN;
```

## probdef [Mathematiques Fonctions]
```
* CAS TEST PROBDEF
* CALCUL IDEALISE D UNE PROBABILITE DE DEFAILLANCE
* Probabilite qu une resistance (R) soit inferieure a
* une sollicitation (S)
* R et S sont des variables aléatoires log-normales
* La probabilité de défaillance et l'indice de fiabilité
* calculés sont comparés au résultat analytique
opti echo 0;
* Moyenne, ecart-type et coeff. de variation de R
muR = 15.;
cvR = 0.1;
sigR = muR*cvR;
* Moyenne, ecart-type et coeff. de variation de S
muS = 5.;
cvS = 0.1;
sigS = muS*cvS;
* Corrélation
* ATTENTION : le cas RHO différent de 0 n est pas traite !
RHO = 0.;
* beta et proba theorique pour 2 lois log-normales
* cvR = sigR / muR;
* cvS = sigS / muS;
lR = log(cvR**2+1);
lS = log(cvS**2+1);
lRS = log(RHO*cvR*cvS+1);
BETA_th = (log(muR/muS)*(((cvS**2+1)/(cvR**2+1))**0.5))/
((lR+lS-(2.*lRS))**0.5);
Pf_th = 1-(PROB 0. 1. 0. 3. BETA_th);
* Calcul des 4 premiers moments statistiques de R et S
NpR = 10;
NpS = 10;
TabR = QUADRATU 'LOGN' muR sigR NpR;
TabS = QUADRATU 'LOGN' muS sigS NpS;
mr sr rr br = PARASTAT TabR;
ms ss rs bs = PARASTAT TabS;
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
MESS '%%% CALCUL DES PARAMETRES STATISTIQUES ';
MESS '%%% MOYENNE       ' mr ms;
MESS '%%% ECART_TYPE    ' sr ss;
MESS '%%% SYMETRIE      ' rr rs;
MESS '%%% APLATISSEMENT ' br bs;
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
* Calcul de la proba de défaillance et de l indice de fiabilité
Pf_RS = PROBABRS mr sr rr br ms ss rs bs ;
Beta_RS = INDIBETA -20. 20. Pf_RS;
* Calcul des erreurs
ErBeta = 100 * (ABS ((Beta_RS - Beta_th) / Beta_th));
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
MESS '                       RESULTATS';
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
MESS ' ';
MESS 'Probabilite de defaillance par PROBABRS      ' Pf_RS;
MESS 'Probabilite de defaillance theorique         ' Pf_th;
MESS ' ';
MESS 'Indice de fiabilite par PROBABRS       ' Beta_RS;
MESS 'Indice de fiabilite theorique          ' Beta_th;
MESS ' ';
MESS '%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%';
MESS ' ';
MESS '  ERREUR par rapport a Beta Theorique  ' ErBeta '%';
* code fonctionnement
* L'ecart maximum entre valeur theorique et calculee doit etre
* inferieure a 0.2 %.
SI (ErBeta <EG 0.2);
    ERRE 0;
SINON;
    ERRE 5;
FINSI;
* Temps de calcul et fin
SAUT 1 LIGN;
OPTI ECHO 1;
fin;
```

## prodt [Mathematiques Fonctions]
```
* Teste la procedure PRODT production d'energie turbulente
opti dime 3 elem cub8 ;
DISCR = 'MACRO' ;
a = 1.13 ;
b = 2.16 ;
n1= 2;
n2= 3;
n3= 5;
P0 = 0 0 0;
p1 = a 0 0;
p2 = a b 0;
p3 = 0 b 0;
cmt1= p0 d n1 p1 d n2 p2 d n1 p3 d n2 p0;
mt1 = surf 'PLAN' cmt1 ;
mt= mt1 volu n3 'TRAN' (0 0 3.51);
Mmt= chan mt QUAF ;
$mt= mode Mmt 'NAVIER_STOKES' DISCR;
mt=doma $mt maillage ;
x=coor 1 mt ;
y=coor 2 mt ;
z=coor 3 mt ;
u1= x + (2.*y) + (3.*z);
u2= (4.*x) + (5.*y) + (6.*z);
u3= (7.*x) + (8.*y) + (9.*z);
u=(nomc 'UX' u1) et (nomc 'UY' u2) et (nomc 'UZ' u3);
t=(8*x) + (16*y) + (32*z) ;
* Cas ou dt/dz >0 est de meme signe que gb
* Stratification instable => G=0.
gb=(1 1 1);
P=prodt u $mt gb t ;
mi= mini P ;
ma= maxi P ;
d=abs ( mi + ma - 1092.) ;
mess mi ma 'Solution : 546  d=' d ;
Si(d > 1.e-10);
erreur 5 ;
Finsi ;
* Cas ou dt/dz >0 est de signe contraire a gb (<0)
* Stratification stable => (P + G)(1 + C3*Rf)
* Rf=-G /(P+G)
gb=(1 1 1)*(-1.);
P=prodt u $mt gb t ;
mi= mini P ;
ma= maxi P ;
d=abs ( mi + ma - 1060.) ;
mess mi ma 'Solution : 530  d=' d ;
Si(d > 1.e-10);
erreur 5 ;
Finsi ;
FIN ;
```

## psatt [Mathematiques Fonctions]
```
* CAS TEST : psatt.dgibi
* Test de l'opérateur VARI PSATT(P)
* Les données sont un FLOTTANT, un LISTREEL ou un CHPO
'OPTI' 'DIME' 2 'ELEM' 'QUA4' ;
'OPTI' 'ECHO' 0 ;
* ------------------------------------------------------> FLOTTANT
X1 = 373.15D0 ;
X3 = VARI PSATT X1 ;
XSTO1 = X3 ;
X1 = 425.15D0 ;
X3 = VARI PSATT X1 ;
XSTO2 = X3 ;
X1 = 453.15D0 ;
X3 = VARI PSATT X1 ;
XSTO3 = X3 ;
* ------------------------------------------------------> LISTREEL
Y1 = 'PROG' 373.15D0 425.15D0 453.15D0 ;
Y3 = VARI PSATT Y1 ;
YSTO1 = EXTR Y3 1 ;
YSTO2 = EXTR Y3 2 ;
YSTO3 = EXTR Y3 3 ;
* ------------------------------------------------------> CHPO
P1 = 373.15D0 0. ;
P2 = 425.15D0 0. ;
P3 = 453.15D0 0. ;
P1P3 = P1 'DROI' 1 P2 'DROI' 1 P3 ;
Z1 = 'COOR' 1 P1P3 ;
Z3 = VARI PSATT Z1 ;
ZSTO1 = 'EXTR' Z3 'SCAL' P1 ;
ZSTO2 = 'EXTR' Z3 'SCAL' P2 ;
ZSTO3 = 'EXTR' Z3 'SCAL' P3 ;
* -------------------------------------------> Controle
CTRL1 = XSTO1 + YSTO1 + ZSTO1 / 3.d0 - XSTO1 / XSTO1 ;
CTRL2 = XSTO2 + YSTO2 + ZSTO2 / 3.d0 - XSTO2 / XSTO2 ;
CTRL3 = XSTO3 + YSTO3 + ZSTO3 / 3.d0 - XSTO3 / XSTO3 ;
CTRL4 = CTRL1 + CTRL2 + CTRL3 ;
XREF1 = 1.0133D5 ;
XREF2 = 5.021D5 ;
XREF3 = 10.027D5 ;
CTRL5 = XSTO1 + YSTO1 + ZSTO1 / 3.d0 - XREF1 / XREF1 ;
CTRL6 = XSTO2 + YSTO2 + ZSTO2 / 3.d0 - XREF2 / XREF2 ;
CTRL7 = XSTO3 + YSTO3 + ZSTO3 / 3.d0 - XREF3 / XREF3 ;
CTRL8 = CTRL5 + CTRL6 + CTRL7 ;
* -------------------------------------------> Affichage
'MESS' '     ' ;
'MESS' '     ' ;
'MESS' 'Pt 1  VARI PSATT ----->' XSTO1 YSTO1 ZSTO1 XREF1 ;
'MESS' 'Pt 2  VARI PSATT ----->' XSTO2 YSTO2 ZSTO2 XREF2 ;
'MESS' 'Pt 3  VARI PSATT ----->' XSTO3 YSTO3 ZSTO3 XREF3 ;
'MESS' '     ' ;
'MESS' 'Comparaison calculs rel.----->' CTRL4 ;
'MESS' 'Erreur rel. VDI         ----->' CTRL8 ;
'MESS' '     ' ;
'MESS' '     ' ;
'MESS' '     ' ;
'MESS' '     ' ;
'MESS' '     ' ;
* -------------------------------------------> Compte-rendu et sortie
EPS4 = 1.E-14 ;
EPS8 = 1.E-2 ;
CTRL4 = ABS CTRL4 ;
CTRL8 = ABS CTRL8 ;
LOG4 = CTRL4 > EPS4 ;
LOG8 = CTRL8 > EPS8 ;
L0 = LOG4 'OU' LOG8 ;
'SI' L0 ;
   'ERREUR' 5 ;
'SINON' ;
   'ERREUR' 0 ;
'FINSI' ;
'FIN' ;
```

## simpl2 [Mathematiques Fonctions]
```
graph='N';
saut page;
mess 'test de SIMPLE : resistance limite d"un treillis de 3 barres';
opti dime 2 elem seg2;
* test du simplex sur un treillis de 3 barres (avec utilisation
* de la procedure ANLIMTRE)
* on considere 3 barres pouvant suportees une contrainte limite
* egale a condlim. L'arrangement des trois barres est le suivant:
* p3 1 2
* ^
* p1 p4 p2 direction de sollicitation
* on cherche l'intensite de la charge limite suportee par ce
* treillis, pour les 2 directions de sollicitation indiquees
* dessus. Le resultat attendu est evidemment:
* cas 1: intensite=(1+2*sqrt(2))*conlim
* cas 2: intensite= 2*sqrt(2) *conlim
* lire les commentaires associes a ANLIMTRE
* PP 1/9/92
conlim=1.;
reacmax=5.;
* 1) preparation du maillage
p1=0 0; p2=2 0; p3=1 1; p4=1 0;
mesh=(p1 d 1 p3) et (p3 d 1 p2) et (p3 d 1 p4);
* WARNING: on tasse pour avoir les noeuds du maillage
* avec une numerotation ABSOLUE correcte
tass mesh;
* 2) point(s) bloque(s) (du maillage)
pbloq=p1 et p2 et p4;
si (ega (type pbloq) 'POINT   ');
  pbloq=pbloq et pbloq;
  pbloq=pbloq elem 1;
finsi;
* 3) point/composante sollicite (du maillage)
psoll=p3; vsoll1=0. 1.; vsoll2=1. 0.;
* 4) preparation de la table d'entree de ANLIMTRE
tt=table;
tt.'MESH'=mesh;
tt.'PBLOQ'=pbloq;
tt.'PSOLL'=psoll;
tt.'CONLIM'=conlim;
tt.'REACMAX'=reacmax;
* 5) premier cas - impression et erreur -
tt.'VSOLL'=vsoll1;
iok=ANLIMTRE tt;
si (iok ega 0);
  solut=tt.'CHARLIM';
  theorie=conlim * (1 + (2. ** .5));
  mess 'premiere direction de sollicitation';
  mess '--->theorie=' theorie ' calcul=' solut;
  si (abs (theorie - solut) > 1.d-6); erre 5;
  sinon; erre 0; finsi;
finsi;
* 6) deuxieme cas - impression et erreur -
tt.'VSOLL'=vsoll2;
iok=ANLIMTRE tt;
si (iok ega 0);
  solut=tt.'CHARLIM';
  theorie=conlim * (2. ** .5);
  mess 'deuxieme direction de sollicitation';
  mess '--->theorie=' theorie ' calcul=' solut;
  si (abs (theorie - solut) > 1.d-6); erre 5;
  sinon; erre 0; finsi;
finsi;
fin;
```

## t_@PASHIST [Mathematiques Fonctions]
```
* Test Procedure @PASHIST
* IDESS1 = VRAI : dessin actifs :
IDESS1 = FAUX ;
'OPTI' 'ECHO' 0 ;
* ---------------------- Construction Champ Test ----------------------
'OPTI' 'DIME' 2 'ELEM' 'QUA8' ;
* Maillage :
O1 = 0. 0. ;
OX1 = 1. 0. ;
OY1 = 0. 1. ;
NE1 = 1000 ;
L1 = O1 'DROI' NE1 OX1 ;
S1 = L1 'TRAN' 1 ((1. / ('FLOT' NE1)) * OY1) ;
* Trac S1 ; Opti Donn 5 ;
* Modele / Champ :
MOD0 = 'MODE' S1 'MECANIQUE' ;
CHPO1 = 'CHAN' 'ATTRIBUT' ((S1 'COOR' 1) 'NOMC' 'X')
  'NATURE' 'DISCRET' ;
CHPO2 = ('BRUI' 'BLAN' 'GAUS' 5. 1.3 S1) 'NOMC' 'GAUS' ;
CHPO3 = ('BRUI' 'BLAN' 'EXPO' -2. 1. S1) 'NOMC' 'EXPO' ;
CHPO0 = CHPO1 'ET' CHPO2 'ET' CHPO3 ;
CHAM0 = 'CHAN' 'CHAM' MOD0 CHPO0 'STRESSES' ;
* Trac MOD0 CHAM0 ;
* ------------------------ Tests fonctionnement -----------------------
* Synthaxe par defaut :
LHIST1 = @PASHIST MOD0 CHAM0 ;
DDSIG1 = 'HIST' 'VERT' MOD0 CHAM0 LHIST1 ;
'SI' IDESS1 ;
  'DESS' DDSIG1 'TITR' ' Verif. fonctionnement @PASHIST ' ;
'FINS' ;
* Donnee Noms de composantes par LISTMOTS :
LMOT1 = 'MOTS' 'EXPO' 'GAUS' ;
LHIST1 = @PASHIST MOD0 CHAM0 LMOT1 ;
DDSIG1 = 'HIST' 'VERT' MOD0 CHAM0 LHIST1 LMOT1 ;
'SI' IDESS1 ;
  'DESS' DDSIG1 'TITR'
    ' Verif. donnee Noms de composantes par LISTMOTS' ;
'FINS' ;
* Donnee Nom de composantes par un MOT :
MOT1 = 'MOT' 'X' ;
LHIST1 = @PASHIST MOD0 CHAM0 MOT1 ;
DDSIG1 = 'HIST' 'VERT' MOD0 CHAM0 LHIST1 MOT1 ;
'SI' IDESS1 ;
  'DESS' DDSIG1 'TITR'
    ' Verif. donnee Nom de composante par MOT (ici Coor 1 maillage)' ;
'FINS' ;
* Visualisation (donnee cachee) :
'SI' IDESS1 ;
  LHIST1 = @PASHIST MOD0 CHAM0 VRAI ;
'FINS' ;
'FIN' ;
```

## valitraj [Mathematiques Fonctions]
```
'SAUTER' PAGE ;
'OPTION' 'ECHO' 0 ;
GRAPH = faux ;
* Test de validation de l'opérateur TRAJ
* on considère un domaine carré dans lequel on se donne un champ
* de vitesse circulaire. En chaque point le module de la vitesse
* est égal à la distance au centre.
* Au temps 2*Pi chaque particule doit être revenue à sa position
* initiale après avoir décrit un cercle.
'OPTION' 'DIME' 2 'ELEM' 'QUA4' ;
* DEFINITION DU MAILLAGE
'TITRE' 'test trajectoires ' ;
P1 = 0. 0. ;
P2 = 2. 0. ;
P3 = 2. 2. ;
P4 = 0. 2. ;
LIG = P1 'DROITE' 10 P2 D 15 P3 D 20 P4 D 25 P1 ;
CARRE = 'SURFACE' 'PLAN' LIG ;
BORDS = 'CONTOUR' CARRE ;
CARRF = 'CHANGER' CARRE 'QUAF' ;
* CREATION DES ÉLEMENTS RELATIFS
MODCAR= 'MODELE' CARRF 'DARCY' 'ISOTROPE' ;
HYSUR = 'DOMA' MODCAR 'SURFACE' ;
HYNOR = 'DOMA' MODCAR 'NORMALE' ;
HYCEN = 'DOMA' MODCAR 'CENTRE' ;
HYFAC = 'DOMA' MODCAR 'FACE' ;
'SI' GRAPH ;
  'TITRE' 'Maillage';
  'TRACER' CARRE ;
'FINSI' ;
* Centre du cercle :
xcen = 1. ;
ycen = 1. ;
LOGERR = FAUX ;
* CALCUL DES TRAJECTOIRES AVEC LA FORMULATION MIXTE HYBRIDE
Mess ' ' ;
Mess 'Formulation Mixte-Hybride' ;
Mess '-------------------------' ;
* GENERATION DE LA VITESSE CIRCULAIRE V AUX CENTRES DES FACES
* ET DES FLUX CORRESPONDANT QN
XX YY = 'COOR' HYFAC ;
* le long d'un cercle, la vitesse est orthoradiale :
V1X = (YY * -1.) + YCEN ;
V1Y = XX - XCEN ;
V = ('NOMC' 'UX' V1X) 'ET' ('NOMC' 'UY' V1Y) ;
MOT1 = 'MOTS' 'UX' 'UY' ;
VAVN = 'PSCAL' V HYNOR MOT1 MOT1 ;
VAVN = 'NOMC' 'SCAL' VAVN ;
VF = HYNOR * VAVN ;
QN = VAVN * HYSUR ;
QN = 'NOMC' 'FLUX' QN ;
* LÂCHER DES PARTICULES
LACHER = 'TABLE' ;
LACHER.TEMPS_LACHER = 'PROG' 0. ;
LACHER.TEMPS_LIMITE = 2 * PI ;
LACHER.CFL = 0.05 ;
LACHER.DELTAT_SAUVE = 0. ;
LACHER.1 = ((XCEN + .4) YCEN) 'ET' ((XCEN + .6) YCEN) 'ET'
           ((XCEN + .8) YCEN) ;
MODTRJ CHMTRJ = 'TRAJ' 'CONVECTION_EXPLICITE' MODCAR QN LACHER ;
* CONTROLE DES RESULTATS
TABZONE = 'EXTR' MODTRJ 'ZONE' ;
'REPETER' BLOC1 ('NBNO' LACHER.1) ;
  I = &bloc1 ;
  PT1 = 'POINT' LACHER.1 I ;
  XP1 = ('COOR' PT1 1) - XCEN ;
  YP1 = ('COOR' PT1 2) - YCEN ;
  MAILTRJ = TABZONE . (2*I) ;
  NBPT1 = 'NBEL' mailtrj ;
* distance au centre du cercle :
  XX1 YY1 = 'COOR' mailtrj ;
  XX1 = XX1 - XCEN ;
  YY1 = YY1 - YCEN ;
  DISTC = ( (XX1*XX1) + (YY1*YY1) ) ** 0.5 ;
  DCMIN = 'MINIMUM' DISTC ;
  DCMAX = 'MAXIMUM' DISTC ;
  MESS 'Part.' (i @ARR 0) ', MAX et MIN de la distance au centre : '
        DCMAX DCMIN ;
  ERDCMAX = 'ABS' ( ((DCMAX + DCMIN) * 0.5) - XP1 ) ;
  MESS '            Erreur sur la moyenne de ces deux valeurs : '
       ERDCMAX ;
  'SI' (ERDCMAX > 1.D-2) ;
    LOGERR = VRAI ;
  'FINSI' ;
* Distance point de départ - point d'arrivée :
  PTF = 'POINT' MAILTRJ 'FINAL' ;
  XF1 = ('COOR' PTF 1) - XCEN ;
  YF1 = ('COOR' PTF 2) - YCEN ;
  DELX = XP1 - XF1;
  DELY = YP1 - YF1;
  DISTP = ((DELX * DELX) + (DELY * DELY)) ** 0.5 ;
  MESS '         Distance entre le point initial et le point final '
       DISTP ;
* erreur relative à la distance totale parcourue
  TT1 = 'EXTR' CHMTRJ 'TMPS' I NBPT1 2 ;
  LLON = TT1 * XP1 ;
  DISTPR = DISTP / LLON ;
  MESS '            soit, '
       'relativement a la distance totale parcourue :' DISTPR ;
  'SI' (DISTPR > 2.D-2) ;
    LOGERR = VRAI ;
  'FINSI' ;
'FIN' BLOC1 ;
* DIFFERENTS TRACÉS
'SI' GRAPH ;
  'TITRE' 'Vitesse de l ecoulement aux faces';
  VNCH1 = 'VECTEUR' VF 0.1 'UX' 'UY' 'ROUGE' ;
  'TRACER' VNCH1 (CARRE 'ET' LACHER.1) ;
  'TITRE' 'Trajectoires formulation mixte hybride (test circulaire)' ;
  CROB1 = 'EXTR' CHMTRJ 'MAIL' ;
  'TRACER' (CROB1 ET BORDS) ;
  'TRACER' CHMTRJ MODTRJ ;
  'TITRE' 'Trajectoires formulation mixte hybride (test circulaire)'
          ' 1 part.' ;
  TRAJ1 = 'REDU' CHMTRJ (TABZONE.2) ;
  'TRACER' TRAJ1 (TABZONE.1) ;
'FINSI' ;
* CALCUL DES TRAJECTOIRES AVEC LA FORMULATION ELEMENTS FINIS
Mess ' ' ;
Mess 'Formulation Elements Finis' ;
Mess '--------------------------' ;
* GENERATION D'UNE VITESSE CIRCULAIRE AUX NOEUDS DU MAILLAGE
XX YY = 'COOR' CARRE ;
* le long d'un cercle, la vitesse est orthoradiale :
V1X = (YY * -1.) + YCEN ;
V1Y = XX - XCEN ;
V1 = ('NOMC' 'VX' V1X) 'ET' ('NOMC' 'VY' V1Y) ;
* CALCUL DES TRAJECTOIRES AVEC LA FORMULATION ELEMENTS FINIS
* Cette formulation s'appuie sur la table domaine :
DOMCAR = 'DOMA' CARRE 'TABLE' ;
* On garde la même table de lâcher
MODTRJ CHMTRJ = 'TRAJ' DOMCAR V1 LACHER ;
* CONTROLE DES RESULTATS
TABZONE = 'EXTR' MODTRJ 'ZONE' ;
'REPETER' BLOC1 ('NBNO' LACHER.1) ;
  I = &bloc1 ;
  PT1 = 'POINT' LACHER.1 I ;
  XP1 = ('COOR' PT1 1) - XCEN ;
  YP1 = ('COOR' PT1 2) - YCEN ;
  MAILTRJ = TABZONE . (2*I) ;
  NBPT1 = 'NBEL' mailtrj ;
* distance au centre du cercle :
  XX1 YY1 = 'COOR' mailtrj ;
  XX1 = XX1 - XCEN ;
  YY1 = YY1 - YCEN ;
  DISTC = ( (XX1*XX1) + (YY1*YY1) ) ** 0.5 ;
  DCMIN = 'MINIMUM' DISTC ;
  DCMAX = 'MAXIMUM' DISTC ;
  MESS 'Part.' (i @ARR 0) ', MAX et MIN de la distance au centre : '
        DCMAX DCMIN ;
  ERDCMAX = 'ABS' ( ((DCMAX + DCMIN) * 0.5) - XP1 ) ;
  MESS '            Erreur sur la moyenne de ces deux valeurs : '
       ERDCMAX ;
  'SI' ( ERDCMAX > 1.D-4 ) ;
    LOGERR = VRAI ;
  'FINSI' ;
* Distance point de départ - point d'arrivée :
  PTF = 'POINT' MAILTRJ 'FINAL' ;
  XF1 = ('COOR' PTF 1) - XCEN ;
  YF1 = ('COOR' PTF 2) - YCEN ;
  DELX = XP1 - XF1;
  DELY = YP1 - YF1;
  DISTP = ((DELX * DELX) + (DELY * DELY)) ** 0.5 ;
  MESS '         Distance entre le point initial et le point final '
       DISTP ;
* erreur relative à la distance totale parcourue
  TT1 = 'EXTR' CHMTRJ 'TMPS' I NBPT1 2 ;
  LLON = TT1 * XP1 ;
  DISTPR = DISTP / LLON ;
  MESS '            soit, '
       'relativement a la distance totale parcourue :' DISTPR ;
  'SI' ( DISTPR > 2.D-3) ;
    LOGERR= VRAI ;
  'FINSI' ;
'FIN' BLOC1 ;
* DIFFERENTS TRACÉS
'SI' GRAPH ;
  'TITRE' 'Vitesses de l ecoulement aux noeuds du maillage' ;
  VNCH2 = 'VECTEUR' V1 0.1 'VX' 'VY' 'ROUGE' ;
  TRAC VNCH2 (CARRE 'ET' LACHER.1) ;
  'TITRE' 'Trajectoires formulation elements finis (test circulaire)' ;
  CROB2 = 'EXTR' CHMTRJ 'MAIL' ;
  'TRACER' (CROB2 'ET' BORDS) ;
'FINSI' ;
* Test de réussite et sortie :
'SI' LOGERR ;
  'ERREUR' 5 ;
'SINON' ;
  'ERREUR' 0 ;
'FINSI' ;
'FIN' ;
```

## tfr [Mathematiques Traitement du signal]
```
* Transformee de Fourier rapide (FFT via operateur TFR)
* et transformee inverse (FFT-1 via operateur TFRI)
* BP, 2018-10-04
* Test de plusieurs signaux
* nombre de points consideres (TFR demande une puissance de 2)
* p = 10;
  p = 18;
  n = 2**p;
* listes des temps (de dime n)
  t = prog 0. pas (4./n) npas (n-1);
* quelques listes utiles
  c180 = cos (180*t);
  s180 = sin (180*t);
* creneau
  cre_c = masq c180 'EGSUPE' 0.;
  cre_s = masq s180 'EGSUPE' 0.;
* bruite
  xh = (0.7*(sin (100*t))) + (sin (360*t));
  xb = brui 'BLAN' 'UNIF' 0. 0.5 (n );
  bru1 = xh + xb;
* rampe
  ram1 = 1.*t;
* pour le trace
  tt = tabl; tt . 2 = mot 'TIRR';
  tt . 3 = mot 'POIN ';
  tt . 4 = mot 'MARQ SS ROND';
* erreur
  err_p = prog ;
* boucle sur les signaux a traiter
REPE BB 6;
* quel cas traite t'on ?
  si (&BB ega 1) ; x = c180; finsi;
  si (&BB ega 2) ; x = s180; finsi;
  si (&BB ega 3) ; x = cre_c; finsi;
  si (&BB ega 4) ; x = ram1 ; finsi;
  si (&BB ega 5) ; x = bru1 ; finsi;
  si (&BB ega 6) ; x = cre_s; finsi;
* signal de depart
  ev_x = evol azur manu 't' t 'x' x;
* Transformee de Fourier
* Tx = TFR ev_x p 'MOPH';
  Tx = TFR ev_x p 'REIM';
* si (&BB ega 3); list Tx; sinon; list resum Tx; finsi;
* Transformee de Fourier inverse
  ev_y = (TFRI Tx) COUL 'BRON';
* si (&BB ega 3); list ev_y; sinon; list resum ev_y; finsi;
* si (&BB ega 3); dess (ev_x et ev_y) tt; finsi;
* test de bon fonctionnement
  t_y = EXTR (EXTR ev_y 'COUR' 1) 'ABSC' ;
  x = EXTR (EXTR ev_x 'COUR' 1) 'ORDO' ;
  y = EXTR (EXTR ev_y 'COUR' 1) 'ORDO' ;
  err_x = MAXI 'ABS' (x - y) ;
  err_p = err_p et err_x;
  MESS '>>> Cas' ' ' &BB ' : erreur =' err_x;
FIN BB ;
TEMP IMPR MAXI CPU;
xCPU1 = TEMP 'CPU' ;
mess '>>> temps CPU = ' xCPU1 ' ms ';
* Test des options
* Transformee de Fourier Module PHase
  Tx1 = TFR ev_x p 'MOPH' BLEU;
* Transformee de Fourier option FMAX
  Tx2 = TFR ev_x p 'FMAX' 256. VERT;
* Transformee de Fourier option FMIN (pas souvent utilise a priori)
  Tx3 = TFR ev_x p 'FMIN' 10.5 ORAN;
* Transformee de Fourier options FMIN FMAX simultanee
  Tx4 = TFR ev_x p 'FMIN' 10.5 'FMAX' 99.5 BRUN;
* Transformee de Fourier inverse sur Tx1 ...
  ev_y1 = (TFRI Tx1) COUL 'BLEU';
  y1 = IPOL t ev_y1;
  err_x1 = MAXI 'ABS' (x - y1) ;
  err_p = err_p et err_x1;
* ... et Tx2 seulement
  ev_y2 = (TFRI Tx2) COUL 'VERT';
  y2 = IPOL t ev_y2;
* pour ce cas, phenomene de Gibbs visible :
* on calcule une erreur moyenne plutot que max et on est + tolerant
* err_x2 = MAXI 'ABS' (x - y2) ;
  err_x2 = (SOMM (ABS (x - y2))) / (dime x);
* si (p < 16); dess (ev_x et ev_y et ev_y1 et ev_y2) tt; finsi;
* TEST DE NON REGRESSION
* pour info : lors de la creation du cas-test,
* | linux 64 | AIX |
* | castem18 | castem apres EVOL #9942 | avant | apres|
* | precision | ~1.E-10 | ~1.E-15 |~1.E-10|~1E-15|
* | performance | 540ms | 190ms | 1090ms| 930ms|
* perf linux 32 apres EVOL : 306ms
* PRECISION
XPREC = VALE 'PREC'; mess 'precision=' XPREC;
XTOL = XPREC * 100;
ZPREC1 = (maxi 'ABS' err_p) > XTOL;
ZPREC2 = err_x2 > 1.E-2;
SI ZPREC1; MESS 'PB DE PRECISION !'; FINSI;
SI ZPREC2; MESS 'PB DE PRECISION avec option FMAX !'; FINSI;
* PERFORMANCE
* ZPERF1 = xCPU1 > ??? difficile car tres dependant-machine ;
* SI ZPERF1; MESS 'PB DE PEROFRMANCE !'; FINSI;
* SI (ZPREC1 OU ZPERF1 ou ZPREC2);
SI (ZPREC1 OU ZPREC2);
  ERRE 5;
FINSI ;
FIN ;
```

## dy_devo2 [Mecanique Contact]
```
* VALIDATION DE LA LIAISON POINT-POINT-FROTTEMENT DE DYNE
* DY_DEVO2.DGIBI
* ref : Rapport DMT/92.056 de Vare, De Langre
* reimporte dans la base des cas-test par BP en 2015
OPTI DIME 3 ELEM SEG2 MODE TRID ;
* cible mobile ?
  FLMOBI = FAUX;
* FLMOBI = VRAI;
* sortie graphique ?
  GRAPH = FAUX;
  SI GRAPH ; OPTI TRAC PSC EPTR 6 POTR HELVETICA_16; FINSI;
* PROJECTILE
* masse
  M_PROJ = 1.;
* point
  P_PROJ = 0. 0. 0. ;
* MODES PROPRES (corps rigides a la main)
  UX_PROJ = MANU CHPO P_PROJ 3 UX 1. UY 0. UZ 0.;
  UY_PROJ = MANU CHPO P_PROJ 3 UX 0. UY 1. UZ 0.;
  BM_PROJ = (MANU 'MODE' 0. M_PROJ UX_PROJ)
         ET (MANU 'MODE' 0. M_PROJ UY_PROJ);
  T_PROJ = TRADUIRE BM_PROJ;
* CIBLE
* masse
  M_CIBL = 1.;
* point
  P_CIBL = 0. 0. 0. ;
* MODES PROPRES (corps rigides a la main)
  SI FLMOBI;
    ux_c = 1.;
  SINON;
    ux_c = 0.;
  FINSI;
  UX_CIBL = MANU CHPO P_CIBL 3 UX ux_c UY 0. UZ 0.;
  UY_CIBL = MANU CHPO P_CIBL 3 UX 0. UY 0. UZ 0.;
  BM_CIBL = (MANU 'MODE' 0. M_CIBL UX_CIBL)
         ET (MANU 'MODE' 0. M_CIBL UY_CIBL);
  T_CIBL = TRADUIRE BM_CIBL;
* CALCULS DYNE avec POINT_POINT_FROTTEMENT
* PARAMETRES DE CALCUL
NB_LIAI = 1 ;
NB_POINT = 1 ;
T = 1.E-2 ;
EXP_BLOC = 8 ;
NB_PAS = 2**EXP_BLOC ;
PAS2 = T / NB_PAS ;
MESS 'NOMBRE DE PAS DE TEMPS = ' NB_PAS ;
MESS 'PAS DE TEMPS = ' PAS2 ;
* BASE = ENSEMBLE DE BASES (couplees par la liaison)
TBASE = TABLE 'ENSEMBLE_DE_BASES';
TMOD1 = TABLE 'BASE_MODALE' ;
TMOD1 . 'MODES' = T_PROJ;
TBASE . 1 = TMOD1;
TMOD2 = TABLE 'BASE_MODALE' ;
TMOD2 . 'MODES' = T_CIBL;
TBASE . 2 = TMOD2;
* AMORTISSEMENT
TAMOR = TABLE 'AMORTISSEMENT';
L_AMOR = PROG 4 * 1.;
TAMOR . 'AMORTISSEMENT' = AMOR TBASE L_AMOR;
* LIAISON ENTRE LES 2 MASSES EN HAUT
* parametres de la liaison
  SI FLMOBI;
    jeuAB = 4.E-6;
    muglis= 2.0;
  SINON;
    jeuAB = 4.5E-6;
    muglis= 0.3;
  FINSI;
kchoc = 1.E7 ;
cchoc = 0. ;
muadhe= muglis;
ktang = 10. * kchoc;
mgen1 = TMOD1 . 'MODES' . 1 . 'MASSE_GENERALISEE';
ctang = 2.*((mgen1*(ktang+kchoc))**0.5);
* remplissage de la table
TLIA = TABLE 'LIAISON';
TLIA . 'LIAISON_B' = TABLE 'LIAISON_B';
TL1 = TABLE 'LIAISON_ELEMENTAIRE';
TLIA . 'LIAISON_B' . 1 = TL1;
TL1 . 'TYPE_LIAISON' = MOT 'POINT_POINT_FROTTEMENT';
TL1 . 'POINT_A' = P_PROJ ;
TL1 . 'POINT_B' = P_CIBL ;
TL1 . 'NORMALE' = 0. -1. 0. ;
TL1 . 'JEU    ' = jeuAB ;
TL1 . 'RAIDEUR' = kchoc ;
TL1 . 'AMORTISSEMENT' = cchoc ;
TL1 . 'COEFFICIENT_ADHERENCE' = muadhe ;
TL1 . 'COEFFICIENT_GLISSEMENT' = muglis ;
TL1 . 'RAIDEUR_TANGENTIELLE' = ktang ;
TL1 . 'AMORTISSEMENT_TANGENTIEL'= ctang ;
* TABLE DE SORTIE
TSORT = TABLE 'SORTIE';
* TSORT1 = TABLE 'VARIABLE' ; TSORT . 'VARIABLE' = TSORT1;
TSORT2 = TABLE 'LIAISON_B'; TSORT . 'LIAISON_B' = TSORT2;
TSORT2 . TL1 = VRAI ;
* sortie tous les ntsor pas de temps
ntsor = 1;
* CONDITION INITIALE = VITESSE VZ0
* Attention a ne pas utiliser PJBA pas prevu pour cela !
* on souhaite en réalité : \alpha0 = [\Phi]^-1 * V0
* (et pas \alpha0 = [\Phi]^T * V0) ...
* --> il vaut mieux ecrire directement :
VINIT1 = MANU 'CHPO' (TMOD1 . 'MODES' . 1 . 'POINT_REPERE')
  1 'ALFA' 1.E-3 'NATURE' 'DIFFUS';
VINIT2 = MANU 'CHPO' (TMOD1 . 'MODES' . 2 . 'POINT_REPERE')
  1 'ALFA' -1.E-3 'NATURE' 'DIFFUS';
VINIT = VINIT1 et VINIT2;
SI FLMOBI;
  VINIT3 = MANU 'CHPO' (TMOD2 . 'MODES' . 1 . 'POINT_REPERE')
  1 'ALFA' -3.E-3 'NATURE' 'DIFFUS';
  VINIT = VINIT et VINIT3;
FINSI;
mess 'VINIT = ' ; list VINIT;
TINIT = TABLE 'INITIAL';
TINIT . 'VITESSE' = VINIT;
* CALCUL DYNE
TDYNE = DYNE 'DE_VOGELAERE' TBASE TAMOR TINIT TLIA TSORT
                            NB_PAS PAS2 ntsor;
* POST TRAITEMENT DYNE
* recup des LISTREELS
tprog = TDYNE . 'TEMPS_DE_SORTIE';
ux1 = TDYNE . TL1 . 'UX_POINT_A';
uy1 = TDYNE . TL1 . 'UY_POINT_A';
fy1 = TDYNE . TL1 . 'FORCE_DE_CHOC_POINT_A';
fx1 = TDYNE . TL1 . 'FORCE_DE_CHOC_TANGENTIELLE';
* construction des EVOLUTIONS temporelles
evux1 = EVOL 'BLEU' 'MANU' 'LEGE' 'UX PPF'
             't (s)' tprog 'UX' ux1;
evuy1 = EVOL 'ORAN' 'MANU' 'LEGE' 'UY PPF'
             't (s)' tprog 'UY' uy1;
evfy1 = EVOL 'ORAN' 'MANU' 'LEGE' 'FY PPF'
             't (s)' tprog 'F_{choc}' fy1;
evfx1 = EVOL 'BLEU' 'MANU' 'LEGE' 'FX PPF'
             't (s)' tprog 'F_{tang}' fx1;
SI GRAPH ;
DESS (evux1 et evuy1)
  POSX CENT POSY CENT 'LEGE' NE
  'TITR' 'PPF : POINT_POINT_FROTTEMENT';
DESS (evfx1 et evfy1)
  POSX CENT POSY CENT 'LEGE' NE
  'TITR' 'PPF : POINT_POINT_FROTTEMENT';
FINSI;
* TRAJECTOIRE
evxy1 = EVOL 'BLEU' 'MANU' 'LEGE' 'UX PPF' 'UX' ux1 'UY' uy1;
xxx1 = prog 0. 7.E-6;
yyy1 = prog (-1.*jeuAB) (-1.*jeuAB);
evjeu = EVOL 'DEFA' 'MANU' 'LEGE' 'PAS DE LEGENDE' 'UX' xxx1 'UY' yyy1;
tdess1 = table;
tdess1 . 2 = MOT 'TIRC';
SI GRAPH ;
DESS (evxy1 et evjeu)
  POSX CENT POSY CENT 'LEGE' NE tdess1
  'TITR' 'PPF : POINT_POINT_FROTTEMENT';
FINSI;
* NOMBRE DE CHOCS
nbchoc = EXTR (COMT evfy1) 1;
si (neg nbchoc 1);
  mess 'nombre de choc incorrect (=' nbchoc')';
  ERRE 5;
finsi;
* TEMPS DE CHOC
* methode 1 :
* on suppose qu'il n'y a qu'1 choc continu
* connu a (+0/-2)*dt pres
ttous = MASQ (abs fy1) 'EGSUPE' 1.E-15 ;
itous = POSI 1. 'DANS' ttous 'TOUS';
ideb = (EXTR itous 1) - 1;
ifin = (EXTR itous (dime itous)) + 1 ;
Tchoc1 = (extr tprog ifin) - (extr tprog ideb);
* methode 2 :
Tchoc = (TOTE evfy1 1.E-15) extr 1;
* ANGLE DE REBOND
* position a la fin du choc
xfin = extr ux1 ifin;
yfin = extr uy1 ifin;
* position a la fin du calcul
xfin2 = extr ux1 NB_PAS;
yfin2 = extr uy1 NB_PAS;
* angle
beta = ATG (xfin2 - xfin) (yfin2 - yfin);
* MOYENNE DE LA FORCE DE CHOC
* normale
intfy1 = (INTG evfy1) ;
moyfy1 = intfy1 / Tchoc;
* tangentielle
intfx1 = (INTG evfx1) ;
moyfx1 = intfx1 / Tchoc;
* message
OPTI ECHO 0;
saut lign;
MESS 'Grandeur            Analytique     PPF          [DMT/92.056]';
SI FLMOBI;
 MESS 'Angle de rebond (°): -45       ' beta ' -44.63';
 MESS 'Temps de choc (ms) :  0.99     ' (Tchoc*1000.) '   1.01';
 MESS 'E(Fnormale) (N)    :  2.01     ' moyfy1 '   1.97';
 MESS 'E(Ftangent) (N)    : <0.604    ' moyfx1 '   0.232';
 err1 = (abs (beta + 45.)) / 45. ;
 err2 = (abs (Tchoc - 0.99E-3)) / 0.99E-3 ;
 err3 = (abs (moyfy1 + 2.01)) / 2.01 ;
SINON;
 MESS 'Angle de rebond (°): 21.80     ' beta '  21.79';
 MESS 'Temps de choc (ms) :  0.99     ' (Tchoc*1000.) '   1.02';
 MESS 'E(Fnormale) (N)    :  2.01     ' moyfy1 '   1.97';
 MESS 'E(Ftangent) (N)    :  0.604    ' moyfx1 '   0.591';
 err1 = (abs (beta - 21.80)) / 21.80 ;
 err2 = (abs (Tchoc - 0.99E-3)) / 0.99E-3 ;
 err3 = (abs (moyfy1 + 2.01)) / 2.01 ;
FINSI;
saut lign;
OPTI ECHO 1;
* TEST DE BON FONCTIONNEMENT
  MESS err1 err2 err3;
SI ( (err1 > 0.01) ou (err2 > 0.03) ou (err3 > 0.03) );
  ERRE 5;
FINSI;
FIN ;
```

## frocable [Mecanique Contact]
```
opti dime 2 mode plan cont elem qua4;
* === GEOMETRIES===
P1 = 0 0;
P2 = 5 0;
liab = P1 droi 5 P2;
su = liab trans 15 (0 3);
P3 = 0 1.5;
P4 = 5 1.5;
* P5 = 0 2.5;
* P6 = 5 2.5;
cab1 = p3 droi 11 P4;
* cab2 = p5 droi 10 p6;
* cabt = cab1 et cab2;
bordy = cote 4 su;
cab1= coul rouge cab1;
su = coul vert su;
toto= cab1 et su;
* trac toto;
* opti donn 5;
* === MODELES===
MODCAB1 = model cab1 mecanique elastique barre;
* list modcab1;
* list modcab2;
cabfr= impf cab1;
* MODFRO1 = model cabfr contact frottant frocable modcab1 su;
modfro1= model cab1 contact frottant frocable su;
* optio donn 5;
* list modfro1;
* juste pour voir azppel a rfco
* cdep crr = rfco modfro1 vrai ;
* list bb;
* opti donn 5;
* list ( frig modfro1);
MODBET = model su mecanique elastique;
* list modfro1;
* === MATERIAUX===
Ebet=34567e6;
nubet=0.2;
rhobet=2240;
matbet = mate MODBET YOUN Ebet NU nubet RHO rhobet;
Ecab=200000e6;
nucab=0.3;
rhocab=8000;
frotcab1=0.18;
phicab1 =0.002;
* on multiplie phicab1 par 10 pour avoir une influence
* plus importante
phicab1=phicab1*10;
matcab1 = mate MODCAB1 YOUN Ecab NU nucab RHO rhocab sect 0.15 ;
matfro1 = mate MODFRO1 FF frotcab1 PHIF phicab1;
mattot= matcab1 et matfro1 et matbet;
modtot= modfro1 et modcab1 et modbet;
* list matfro1;
* ===RIGIDITES===
ribet= RIGI MODBET matbet;
ricab= RIGI MODCAB1 matcab1;
* list riac1;
* list riac2;
* ===PRECONTRAINTES===
TAB = table;
TAB.'FF  '=frotcab1;
TAB.'PHIF'=phicab1;
TAB.'GANC'=0;
TAB.'RMU0'=0.43;
TAB.'FPRG'=1.7d9;
TAB.'RHL0'=2.5;
* ===CALCUL DES FORCES===
PRE1 = PREC MODCAB1 MATCAB1 TAB 3.e5;
PRE2 = PREC MODCAB1 MATCAB1 TAB 6.e5;
PRE3 = PREC MODCAB1 MATCAB1 TAB 9.e5;
PRE4 = PREC MODCAB1 MATCAB1 TAB 1.2e6;
PRE5 = PREC MODCAB1 MATCAB1 TAB 1.5e6;
PRE6 = PREC MODCAB1 MATCAB1 TAB 1.8e6;
PRE7 = PREC MODCAB1 MATCAB1 TAB 2.1e6;
PRE8 = PREC MODCAB1 MATCAB1 TAB 2.4e6;
PRE9 = PREC MODCAB1 MATCAB1 TAB 2.7e6;
PRE10 = PREC MODCAB1 MATCAB1 TAB 3.e6;
* list pre10;
el1=cab1 elem 1;
el2=cab1 elem 4;
FORC1 = FORC FX 3.e6 p4;
* list forc1;
FORC2 = FORC FX -3.e6 p3;
depenc= bloque depl ( bordy );
deppoi= bloque maxi UX P3;
* deppoi= bloque mini UX P4;
* riac1 = rela glissant modfro1 su 0.001 ;
* list riac1;
* opti donn 5;
* cl= riac1 et depenc et deppoi;
cl= depenc et deppoi;
* rig= rigi modtot mattot;
* rigtot=rig et cl;
* dep=reso rigtot forc1;
* VEC1 = VECT forc1 1.E-6 FX FY turq;
* trac (vec1) toto;
* def1=defo toto dep 0. blanc;
* def2=defo toto dep rouge;
* trac (def1 et def2);
* sig1=sigma modcab1 matcab1 dep;
* sxx1=extr sig1 comp;
* xx =exco 'EFFX' sig1;list xx;
* ===PAS A PAS===
* list1=prog 0 pas 0.5 1. pas 1. 3.;
* list2=prog 0 1 1 1 1;
* list3=prog 0 0 1 1.01 1.02;
list1=prog 0 pas 0.5 1 2 3 ;
list2=prog 0 1 1 1 1 ;
list3=prog 0 0 0.99 pas 0.005 1. ;
evt1=evol manu list1 list2;
evt2=evol manu list1 list3;
* dess (evt1 et evt2);
cha1=char meca forc1 evt1;
cha2=char meca forc2 evt2;
chat=cha1 et cha2;
tab1 = table;
tab1.'BLOCAGES_MECANIQUES'=cl;
tab1.'MODELE'=modtot;
tab1.'CHARGEMENT'=chat;
list mattot;
tab1.'CARACTERISTIQUES'=mattot;
tab1.'TEMPS_CALCULES'=list1;
tab1.'PRECISION'=1.e-7;
pasapas tab1;
* opti sauv 'donnees.sauv';
* sauv tab1;
debproc ecri ta*table mo*mmodel ge*maillage;
co= ta.contraintes ;
de= ta.deplacements ;
re = ta. reactions ;
cab= extr mo maillage;
na = (dime co ) - 1;
 repe bo na;
mess ' contraintes  au pas ' &bo;
list (( co . &bo redu mo) exco EFFX);
fin bo;
* repe ba na;
* mess ' deplacements au pas ' &ba;
* list ( de . &ba redu ge);
* fin ba;
repe bi na;
mess ' reactions au pas ' &bi;
list ( re . &bi redu ge) ;
fin bi;
finp ;
* ecri tab1 modcab1 cab1;
ffr1=(tab1.contraintes . 1) exco EFFX ;
list ffr1;
valref= ffr1 extr EFFX 1 6 2;
ffr4= (tab1.contraintes . 4) exco EFFX ;
minffr4= mini ffr4;
* teste de la valeur min trouvée au temps 1 par rapport a
* solution fournie par precontrainte( pre10)
xpre= mini pre10;
xsol= mini ffr1;
mess ' xsol ' xsol ' xpre ' xpre;
ersol= abs ( (xsol - xpre) / xpre);
mess ' erreur sur la precontrainte ' ersol ;
si ( ersol > 1.e-2) ;
erreur 5 ;
finsi;
* on compare la valeur trouvé au temps 1
* pour le point central (valref) et celle trouvée
* pour le temps 4
er=abs((minffr4 - valref)/valref);
mess ' erreur en % ' er;
si ( er > 0.01);
 erreur 5;
finsi;
* list pre10;
* list ffr1;
fin;
```

## 1ddl [Mecanique Dynamique]
```
* Etude d'un système 1 ddl
* Exemple d'utilisation de OSCI, SPO et SPON
* D. Combescure aout 2006
* GRAPH = VRAI;
GRAPH = FAUX;
* COMPLET = VRAI;
COMPLET = FAUX;
opti dime 2 elem seg2;
fr1 = 5.;
dt = 0.005;
prtime = prog 0. pas dt 100.;
* Durée de la rampe de montée et de descente du chargement
dtramp = 0.001;
* Durée de l'impulsion
dtchar = 0.05;
prtim1 = prog 0. 0.1 (0.1 + dtramp) (0.1 + dtramp + dtchar)
                     (0.1 + dtchar + (2.*dtramp)) 100.;
prload1 = ((2.*pi*fr1)**2)*(prog 0 0. 1. 1. 0. 0.);
evload1 = evol manu prtime (ipol prtime prtim1 prload1);
prtimec = prog 0. pas dt 1.;
SI (EGA GRAPH VRAI);
 dess evload1 xbord 0. 1. ;
FINSI;
* Réponse 1ddl elastique
ev1 = osci evload1 amor 0.05 freq fr1 temps prtimec depl 0.;
SI (EGA GRAPH VRAI);
 dess ev1 xbord 0. 1.;
 @excel1 ev1 'ev1.excel';
FINSI;
* Calcul spectre oscillateur
SI COMPLET;
 lfreq = (prog 0.01 pas 0.1 20.);
SINON;
 lfreq = prog 1. pas 1. 20.;
FINSI;
spev1 = spo evload1 amor (prog 0.05)
          freq lfreq
          acce coul rouge;
* Calcul spectre inélastique - oscilateur élastoplastique parfait
* Option DEMA => on trace la pseudoaccélération correspondant
* à la limite élastique (pour le dimensionnement)
* Ductilité 1
spnlev1 = spon DEMA SIGN evload1 SPEL spev1 ACCE
          AMOR (prog 0.05) CINE (prog 1. 0.00) ACCE;
* Ductilité 2
spnlev2 = spon DEMA SIGN evload1 SPEL spev1 ACCE
          AMOR (prog 0.05) CINE (prog 2. 0.00) ACCE;
* Ductilité 5
spnlev5 = spon DEMA SIGN evload1 SPEL spev1 ACCE
          AMOR (prog 0.05) CINE (prog 5. 0.00) ACCE;
SI (EGA GRAPH VRAI);
 dess (spnlev1 et spnlev2 et spnlev5 et spev1);
FINSI;
ERR = maxi ((extr spnlev1 ordo) - (extr spev1 ordo)) abs;
SI (ERR > 1.D-3);
 ERRE 4;
FINSI;
FIN;
```

## A1DDL [Mecanique Dynamique]
```
* EXEMPLE A1DDL.dgibi
* Entrée : Chargement sismique
* Sortie : Sans objet
* Commentaire : Test de la procedure
* @A1DDL.PROCEDUR
* Developpeur : Benjamin Richard
* CEA, DEN, DANS, DM2S, SEMT, EMSI
* benjamin.richard@cea.fr
* OPTIONS DE CALCUL
* repertoire des fichiers "divers"
DIVERS = VENV 'CASTEM_DIVERS';
RUN = 1;
* ACQUISITION RUN I
* RUN 1
SI (RUN EGA 1);
* OPTI ACQU './exp/21time.txt';
OPTI ACQU ('CHAINE' DIVERS '/21time.txt');
* ACQU TIME*LISTREEL 8192;
ACQU TIME*LISTREEL 550;
* OPTI ACQU './exp/21axtab.txt';
OPTI ACQU ('CHAINE' DIVERS '/21axtab.txt');
* ACQU AXTAB*LISTREEL 8192;
ACQU AXTAB*LISTREEL 550;
FINSI;
* RUN 2
SI (RUN EGA 2);
OPTI ACQU '.\exp\22time.txt';
ACQU TIME*LISTREEL 8192;
OPTI ACQU '.\exp\22axtab.txt';
ACQU AXTAB*LISTREEL 8192;
FINSI;
* RUN 3
SI (RUN EGA 3);
OPTI ACQU '.\exp\23time.txt';
ACQU TIME*LISTREEL 8192;
OPTI ACQU '.\exp\23axtab.txt';
ACQU AXTAB*LISTREEL 8192;
FINSI;
* RUN 4
SI (RUN EGA 4);
OPTI ACQU '.\exp\24time.txt';
ACQU TIME*LISTREEL 8192;
OPTI ACQU '.\exp\24axtab.txt';
ACQU AXTAB*LISTREEL 8192;
FINSI;
* REMPLISSAGE DE LA TABLE D ENTREE A @A1DDL
* Parametres dynamiques
* TABDYN . 1 = M; -- masse de la structure
* TABDYN . 2 = BETA; -- coefficient beta
* TABDYN . 3 = GAMMA; -- coefficient gamma
* TABDYN . 4 = FPLAS; -- effort de plastification
* TABDYN . 5 = KA; -- raideur de l'acier
* TABDYN . 6 = KB; -- raideur du beton
* TABDYN . 7 = ACTU -- type d actualisation
* --> 1 :
* --> 2 :
* --> 3 :
* TABDYN . 8 = TIME -- liste de temps
* TABDYN . 9 = AXTAB -- liste d acceleration en pied de maquette
* TABDYN . 10 = XI0 -- taux d amortissement initial
* TABDYN . 11 = XMIN -- taux d amrotissement minimal
* TABDYN . 12 = AMMAX -- taux d amortissement maximal
* TABDYN . 13 = NC -- indicateur sur le type d actualisation
* --> 0 :
* --> 1 :
* TABDYN . 14 = DPLUS -- endommagement positif
* TABDYN . 15 = DMOIN -- endommagement negatif
* TABDYN . 16 = MAXDP -- maximum deplacement positif
* TABDYN . 17 = MAXDM -- maximum deplacement negatif
* TABDYN . 18 = AOLD -- taux d amortissement au premier pas
TABDYN = TABLE;
TABDYN . 1 = 2980.0;
TABDYN . 2 = 0.25;
TABDYN . 3 = 0.50;
TABDYN . 4 = 35000.0;
TABDYN . 5 = 729.7855;
TABDYN . 6 = 2.8213E6;
TABDYN . 7 = 1;
TABDYN . 8 = TIME;
TABDYN . 9 = AXTAB;
TABDYN . 10 = 0.05;
TABDYN . 11 = 0.02;
TABDYN . 12 = 0.30;
TABDYN . 13 = 0.0;
TABDYN . 14 = 0.0;
TABDYN . 15 = 0.0;
TABDYN . 16 = 0.0;
TABDYN . 17 = 0.0;
TABDYN . 18 = 0.0;
* APPEL A @A1DDL
EVDR EVVR EVAR EVXI TAB3 = @A1DDL TABDYN;
* ECRITURES EN SORTIES
* @EXCEL1 EVDR (CHAI '.\evdr' RUN '.txt');
* @EXCEL1 EVVR (CHAI '.\evvr' RUN '.txt');
* @EXCEL1 EVAR (CHAI '.\evar' RUN '.txt');
* @EXCEL1 EVXI (CHAI '.\evxi' RUN '.txt');
LVDRA = extr (extr EVDR ordo) 500;
LVVRA = extr (extr EVVR ordo) 500;
LVARA = extr (extr EVAR ordo) 500;
LVXIA = extr (extr EVXI ordo) 500;
err1 = abs (1.56839E-05 - LVDRA);
err2 = abs (-7.66832E-03 - LVVRA);
err3 = abs (-2.50373E-02 - LVARA);
err4 = abs (2.10603E-02 - LVXIA);
si (> err1 1.0E-5);
erreur(5);
finsi;
si (> err2 1.0E-5);
erreur(5);
finsi;
si (> err3 1.0E-5);
erreur(5);
finsi;
si (> err4 1.0E-5);
erreur(5);
finsi;
FIN;
```

## drx_impact_anneau [Mecanique Dynamique]
```
* chute et rebond d'un anneau dans un cone rigide
* calcul drexus explicite avec impact ligne-ligne
* hypotheses : - materiau elastique lineaire
* - grandes deformations
* v
graph= faux;
opti dime 2 elem seg2 mode plan cont;
* maillage
pc = 0. 10. ; p1 = 0 0 ;
l1 = lign rota 60 pc p1 360. ;
elim l1 .1 ;
tg20 = (sin 20.) / (cos 20.) ;
e = 10 - (10.1/(sin 20.)) ;
p2 = 0 e ; p3 = ((20 - e) * tg20) 20 ;
p4 = (-1*(20 - e) * tg20) 20 ;
l2 = p3 d 1 p2 d 1 p4;
tout = l1 et l2 ;
* donnees drexus
mod1 = mode l1 mecanique coq2 ;
mat1 = mate mod1 youn 100 nu 0. rho .01 epai 1. dim3 1. ;
vit0 = manu chpo l1 3 ux 0 uy -4 rz 0.;
etab = table;
etab . modele = mod1 ;
etab . grandes_deformations = vrai ;
etab . caracteristiques = mat1;
etab . vitesse_initiale = vit0;
etab . frequence_sortie = 20 ;
etab . pas_temps = 2e-3 ;
etab . npasmax = 2000;
etab . impact = table;
etab . impact . maitre = l2 ;
etab . impact . esclave = l1 ;
drexus etab ;
* post-traitement
i = 1 ;
lt = prog 0.;
lz = prog 0. ;
repeter bou1 ( (dime etab . deplacements ) - 1) ;
  lt = lt et ( prog etab . temps . i ) ;
  dep1 = etab . deplacements . i;
  def1 = defo tout dep1 1;
  si (ega i 1);
    def = def1;
  sinon;
    def = def et def1;
  finsi;
  lz1=extr dep1 p1 UY;
  lz = lz et ( prog lz1 );
  i = i + 1 ;
fin bou1 ;
evdz = evol bleu manu 'Temps' lt 'Dy' lz ;
si graph ;
dess evdz;
trac def anime;
finsi;
* test de fonctionnement
err1 = 1. + (lz1 / 15.902) ;
mess 'Erreur sur la force ' (err1 * 100. ) '%' ;
lerr1 = err1 >eg 0.05 ;
si lerr1 ;
  mess 'Erreur dans le cas test impact_anneau' ;
  erreur 5 ;
finsi ;
fin;
```

## dyna14 [Mecanique Dynamique]
```
* Mots-clés : Vibrations, calcul modal, sous-structuration,
* Craigh-Brampton, dynamique
* TEST POUR LA SOUS-STRUCTURATION SANS UTILISATION DE BASE
* Etude d'un ASSEMBLAGE DE 2 PLAQUES
* Creation : D. COMBESCURE 30/09/2005
* Modif : B Prabel, 12/09/2014 : + sous-structuration libre-libre
* GRAPH = VRAI; OPTI TRAC PSC EPTR 5 POTR HELVETICA_16;
GRAPH = FAUX;
opti dime 2 elem qua4 mode plan defo;
* Maillage
nele = 1;
q0 = 0. 0. ; vz = 0. 1;
q1 = 5. 0. ; q2 = 10. 0. ;
q1b = q1 plus (0. 0.);
q3 = q0 plus vz;
q4 = q1 plus vz;
q5 = q2 plus vz;
q4b = q4 plus (0. 0.);
lig1 = d (5*nele) q0 q1 ;
sur1 = tran nele lig1 vz;
ligi0 = d nele q0 q3;
ligi1 = d nele q1 q4;
elim 0.0001 (lig1 et sur1 et ligi1 et ligi0);
lig2 = d (5*nele) q1b q2 ;
sur2 = coul (tran nele lig2 vz) rouge;
ligi1b = d nele q1b q4b;
ligi2 = d nele q2 q5;
elim 0.0001 (lig2 et sur2 et ligi2 et ligi1b);
surtot = sur1 et sur2;
si (GRAPH);
  trac (surtot) 'TITRE' 'Maillage 1 (noir) et 2 (rouge)';
finsi;
* Modèles et matrices
* Plaque 1
MO1 = MODE SUR1 'MECANIQUE' 'ELASTIQUE' 'QUA4' ;
MATE1 = MATE MO1 'YOUNG' 2.E5 'NU' 0.3 'RHO' 7.800D-3;
RIGPL1 = RIGI MATE1 MO1 ;
MASPL1 = MASS MATE1 MO1 ;
BLOQ1 = BLOQ 'DEPL' ligi0;
RIGPLA1= RIGPL1 et BLOQ1 ;
* bp SPLA1 = STRU RIGPLA1 MASPL1;
Meshi1 = ligi1;
BLOQ1L = (BLOQ 'UX' Meshi1) et (BLOQ 'UY' Meshi1);
* Plaque 2
MO2 = MODE SUR2 'MECANIQUE' 'ELASTIQUE' 'QUA4' ;
MATE2 = MATE MO2 'YOUNG' 2.E5 'NU' 0.3 'RHO' 7.80d-3;
RIGPL2 = RIGI MATE2 MO2 ;
MASPL2 = MASS MATE2 MO2 ;
BLOQ2 = BLOQ DEPL ligi2;
Meshi2 = ligi1b;
BLOQ2L =(BLOQ UX Meshi2) et (BLOQ UY Meshi2);
RIGPLA2 = RIGPL2 et BLOQ2 ;
* Liaison inter-plaque
LIUX = RELA 'UX' Meshi1 - 'UX' Meshi2 ;
LIUY= RELA 'UY' Meshi1 - 'UY' Meshi2;
ENCL = (LIUX et LIUY);
* Calcul du système complet sans sous-structuration
* calcul des modes
nmodo = 4;
SOLREF = VIBR 'PROCH' (PROG 0.) (lect nmodo)
          (RIGPLA2 et RIGPLA1 et ENCL) (MASPL2 et MASPL1) ;
* calcul de la reponse forcee harmonique
ptF = sur2 poin PROCH (q1b plus (0.4*(q2 moins q1b)));
F1 = FORC 'FY' 1. ptF;
OMEGA = 50.;
KDYN = (RIGPLA2 et RIGPLA1 et ENCL)
     et ( -1.*((2.*pi*OMEGA)**2) * (MASPL2 et MASPL1));
UDYN = RESO KDYN F1;
UY1ref = EXTR UDYN 'UY' q1;
si GRAPH;
  trac (vect F1 1. 'FORC' 'VERT') surtot;
finsi;
* Methode de sous-structuration de Craigh brampton
* Etape 1 : calcul des modes propres et statiques
* mode propre Plaque 1 (= modes propres "bloqués")
nmod1 = 1;
MODPLA1 = VIBR 'PROCH' (prog 0.) (lect nmod1)
               (RIGPLA1 et BLOQ1L) MASPL1 ;
i = 0;
repe Bmod1 nmod1; i = i + 1 ;
  def1 = MODPLA1 . 'MODES' . i . 'DEFORMEE_MODALE';
  frq1 = MODPLA1 . 'MODES' . i . 'FREQUENCE';
  mm1 = MODPLA1 . 'MODES' . i . 'MASSE_GENERALISEE';
  cha1 = chai 'Plaque 1 : Mode bloqué ' i ' - f= ' frq1 ' - m=' mm1;
  MESS cha1;
  si (GRAPH); trac (defo sur1 def1) 'TITRE' cha1; finsi;
fin Bmod1;
* mode propre Plaque 2 (= modes propres "bloqués")
nmod2 = 1;
MODPLA2 = VIBR 'PROCH' (prog 0.) (lect nmod2)
               (RIGPLA2 et BLOQ2L) MASPL2 ;
i = 0;
repe Bmod2 nmod2; i = i + 1 ;
  def2 = MODPLA2 . 'MODES' . i . 'DEFORMEE_MODALE';
  frq2 = MODPLA2 . 'MODES' . i . 'FREQUENCE';
  mm2 = MODPLA2 . 'MODES' . i . 'MASSE_GENERALISEE';
  cha2 = chai 'Plaque 2 : Mode bloqué ' i ' - f= ' frq2 ' - m=' mm2;
  MESS cha2;
  si (GRAPH); trac (defo sur2 def2) 'TITRE' cha2; finsi;
fin Bmod2;
* modes statiques Plaque 1 (on impose u=1 sur chaque ddl)
* creation de la table LIAISONS_STATIQUES
  tblsta1 = IDLI BLOQ1L Meshi1;
* creation des blocages de chaque ddl individuellement
  bliaiq1 = BLOQ tblsta1 ;
* creation du 2nd membre associé à chaque blocage
  DEPI tblsta1;
* resolution (statique) de chaque pb lineaire a deplacement imposé
  RESO (RIGPLA1 et bliaiq1) tblsta1;
* calcul de chaque force de reaction
  REAC bliaiq1 tblsta1;
nstat1 = ((dime tblsta1) - 1);
i = 0;
repe Bstat1 nstat1; i = i + 1;
  motinc = tblsta1 . i . 'DDL_LIAISON' ;
  notinc = noeu tblsta1 . i . 'POINT_LIAISON' ;
  ptrep1 = tblsta1 . i . 'POINT_REPERE' ;
  defsta1= tblsta1. i . 'DEFORMEE';
  cha1 = chai 'Mode statique ' i ' - ddl :'motinc ' #'notinc
  ' ->' (noeu ptrep1);
  mess cha1;
  si (GRAPH); trac (defo (surtot) defsta1) 'TITRE' cha1; finsi;
fin Bstat1;
* modes statiques Plaque 2 (on impose u=1 sur chaque ddl)
* creation de la table LIAISONS_STATIQUES
  tblsta2 = IDLI BLOQ2L Meshi2;
* creation des blocages de chaque ddl individuellement
  bliaiq2 = BLOQ tblsta2 ;
* creation du 2nd membre associé à chaque blocage
  DEPI tblsta2;
* resolution (statique) de chaque pb lineaire a deplacement imposé
  RESO (RIGPLA2 et bliaiq2) tblsta2;
* calcul de chaque force de reaction
  REAC bliaiq2 tblsta2;
nstat2 = ((dime tblsta2) - 1);
i = 0;
repe Bstat2 nstat2; i = i + 1;
  motinc = tblsta2 . i . 'DDL_LIAISON' ;
  notinc = noeu tblsta2 . i . 'POINT_LIAISON' ;
  ptrep2 = tblsta2 . i . 'POINT_REPERE' ;
  defsta2= tblsta2. i . 'DEFORMEE';
  cha2 = chai 'Mode statique ' i ' - ddl :'motinc ' #'notinc
  ' ->' (noeu ptrep2);
  mess cha2;
  si (GRAPH); trac (defo (surtot) defsta2) 'TITRE' cha2; finsi;
fin Bstat2;
* Etape 2 : calcul des matrices projetees
* calcul direct via les operateur RIGI et MASS
  rigtot1 = rigi tblsta1 modpla1;
  mastot1 = mass tblsta1 modpla1 MASPL1;
  rigtot2 = rigi tblsta2 modpla2;
  mastot2 = mass tblsta2 modpla2 MASPL2;
* on peut aussi passer par PJBA (plus couteux mais plus general)
  rigtot1p = PJBA RIGPL1 tblsta1 modpla1;
  mastot1p = PJBA MASPL1 tblsta1 modpla1;
  rigtot2p = PJBA RIGPL2 tblsta2 modpla2;
  mastot2p = PJBA MASPL2 tblsta2 modpla2;
* projection de la liaison 1-2 : seul les modes statiques sont non-nuls
  ENCLP = PJBA ENCL (tblsta1 et tblsta2);
* assemblage
  RIGMO = rigtot1 et rigtot2 et ENCLP;
  MASMO = mastot1 et mastot2;
* Etape 3 : calcul sur système complet sur base réduite
* calcul des modes
SOL_SS = VIBR 'PROCH' (PROG 0.1) (lect nmodo) RIGMO MASMO ;
* calcul de la reponse forcee harmonique
F1_SS = PJBA F1 modpla2 tblsta2;
KDYNSS = RIGMO et ( -1.*((2.*pi*OMEGA)**2) * MASMO);
UDYNSS = RESO KDYNSS F1_SS;
UDYNSS = RECO UDYNSS (modpla1 et modpla2) (tblsta1 et tblsta2);
UY1_ss = EXTR UDYNSS 'UY' q1;
* Methode de sous-structuration libre-libre
* mode propre Plaque 1 (= modes propres "libres")
nmod1 = 4;
MODPLL1 = VIBR 'PROCH' (prog 0.) (lect nmod1)
               (RIGPLA1) MASPL1 ;
* mode propre Plaque 2 (= modes propres "libres")
nmod2 = 4;
MODPLL2 = VIBR 'PROCH' (prog 0.) (lect nmod2)
               (RIGPLA2) MASPL2 ;
* reunion des 2 bases
MODPLL = MODPLL1 et MODPLL2;
i = 0;
repe Bmod (nmod1 + nmod2); i = i + 1 ;
  def = MODPLL . 'MODES' . i . 'DEFORMEE_MODALE';
  frq = MODPLL . 'MODES' . i . 'FREQUENCE';
  mm = MODPLL . 'MODES' . i . 'MASSE_GENERALISEE';
  cha = chai ' Mode libre ' i ' - f= ' frq ' - m=' mm;
  MESS cha;
  si (GRAPH); trac (defo surtot def) 'TITRE' cha; finsi;
fin Bmod;
* equation de liaison projetee sur la base libre
ENCLL = PJBA ENCL MODPLL;
RIGLL = PJBA (RIGPLA1 et RIGPLA2) MODPLL;
MASLL = PJBA (MASPL1 et MASPL2 ) MODPLL;
* calcul des modes du système complet
* SOL_LL = VIBR 'PROCH' (PROG 0.1) (lect nmodo)
SOL_LL = VIBR 'SIMUL' 0.1 nmodo
          (RIGLL et ENCLL) MASLL ;
* calcul de la reponse forcee harmonique
* F1_LL = PJBA F1 MODPLL;
F1_LL = PJBA F1 MODPLL2;
KDYNLL = RIGLL et ENCLL et ( -1.*((2.*pi*OMEGA)**2) * MASLL);
UDYNLL = RESO KDYNLL F1_LL;
UDYNLL = RECO UDYNLL MODPLL;
UY1_ll = EXTR UDYNLL 'UY' q1;
* Comparaison des resultats obtenus avec diverses methodes
* calcul des modes
 MESS ' Mode |  Reference  | Craigh-Brampton |  Libre-Libre';
i = 0;
REPE BMODO nmodo; i = i + 1 ;
 fr1ref = SOLREF . 'MODES' . i . 'FREQUENCE';
 fr1_ss = SOL_SS . 'MODES' . i . 'FREQUENCE';
 fr1_ll = SOL_LL . 'MODES' . i . 'FREQUENCE';
 MESS i fr1ref fr1_ss fr1_ll;
 si (GRAPH);
  def0 = SOLREF. 'MODES' . i . 'DEFORMEE_MODALE';
  trac (defo (surtot) def0)
    'TITRE' (chai 'mode 'i 'f=' fr1ref);
  def1 = reco (SOL_SS. 'MODES' . i . 'DEFORMEE_MODALE') tblsta1 modpla1;
  def2 = reco (SOL_SS. 'MODES' . i . 'DEFORMEE_MODALE') tblsta2 modpla2;
  def1 = exco def1 (mots UX UY) NATURE DIFFUS;
  def2 = exco def2 (mots UX UY) NATURE DIFFUS;
  trac (defo (surtot) (def1 et def2))
    'TITRE' (chai 'mode 'i 'f=' fr1_ss);
  defLL = reco (SOL_LL . 'MODES' . i . 'DEFORMEE_MODALE') MODPLL;
  trac (defo (surtot) defLL);
 finsi;
fin BMODO;
* calcul de la reponse forcee harmonique
si GRAPH;
  amp = 2000.;
  trac ((defo UDYN amp surtot 'DEFA')
     et (defo UDYNSS amp surtot 'BLEU')
     et (defo UDYNLL amp surtot 'ROSE'));
finsi;
mess UY1ref UY1_ss UY1_LL;
* Test de Non Regression
 fr1ref = SOLREF . 'MODES' . 1 . 'FREQUENCE';
 fr1_ss = SOL_SS . 'MODES' . 1 . 'FREQUENCE';
 fr1_ll = SOL_LL . 'MODES' . 1 . 'FREQUENCE';
 erel1 = abs ((fr1_ss - fr1ref)/fr1ref);
 erel2 = abs ((fr1_ll - fr1ref)/fr1ref);
 erel3 = abs ((UY1_ss - UY1ref) / UY1ref);
 erel4 = abs ((UY1_LL - UY1ref) / UY1ref);
 mess 'Erreur relative Craigh Brampton = ' erel1 erel3;
 mess 'Erreur relative libre-libre     = ' erel2 erel4;
* les resultats obtenus par la methode libre-libre sont assez mauvais
* dans ce cas de figure --> grande tolerance sur les valeurs testees
 SI ((erel1 < 0.01) et (erel2 < 0.20)
  et (erel3 < 0.01) et (erel4 < 0.50));
   ERRE 0;
 SINON;
   ERRE 5;
 FINSI;
FIN ;
```

## dyna15 [Mecanique Dynamique]
```
* Poteau soumis à une charge concentré
* Contribution statique des modes négligés
* D. Combescure aout 2006
* AFFICH = VRAI;
AFFICH = FAUX;
* COMPLET = VRAI;
COMPLET = FAUX;
opti dime 2 elem seg2;
H = 3.;
H1 = 2.;
p0 = 0. 0.;
p1 = 0. H1;
p2 = 0. H;
n1 = 50;
n2 = 25;
a = 0.25;
b = a;
e1 = 30000.D6;
ro1 = 2400.;
nu1 = 0.30;
sec1 = a*b;
in1 = (1./12.)*(b*(a**3));
lig1 = (d n1 p0 p1) et (d n2 p1 p2);
mod1 = MODE lig1 mecanique elastique TIMO;
mat1 = MATE mod1 YOUN E1 NU nu1 RHO ro1
       SECT sec1 INRZ in1;
KK1 = rigi mod1 mat1;
CC1 = 0.001*KK1;
MM1 = mass mod1 mat1;
bl0 = BLOQ DEPL ROTA p0;
fh1 = forc FX 1. p1;
* Calcul du premier mode
vib1 = vibr proche (prog 1.) (lect 1) (KK1 et bl0) MM1;
vib1b= vib1 . 'MODES';
nmod = (dime (vib1b) ) - 2;
SI AFFICH;
 repeter lab1 nmod;
  dep1 = vib1b. &lab1 . DEFORMEE_MODALE;
  fr1 = vib1b. &lab1 . FREQUENCE;
  titre fr1;
  trac (defo lig1 dep1);
 fin lab1;
FINSI;
* Calcul du pseudo mode
psm1 = psmo (KK1 et bl0) vib1b fh1;
depstaf = (defo lig1 (psm1 . 1 . DEPLACEMENT));
SI AFFICH;
 TITRE 'Pseudomode';
 TRAC depstaf;
FINSI;
* Définition du chargement
t1 = 1/400.;
SI COMPLET;
 tfin = 100.*t1;
SINON;
 tfin = 10.*t1;
FINSI;
dt = t1/2.;
lptemps = prog 0 t1 (2.*t1) (3.*t1) 100.;
lpchar = prog 0 0 1.D6 0. 0.;
ev1 = evol manu lptemps lpchar;
SI AFFICH;
 dess ev1 xbord 0. (10.*t1);
FINSI;
cha1 = char fh1 ev1;
* Méthode 1: intégration directe sur base physique
prtimeb = prog 0. pas dt tfin;
tab1 = table; opti sauv 'mon.fic';
tab1.'DEPL' = manu chpo lig1 2 ux 0 uy 0;
tab1.'VITE' = manu chpo lig1 2 ux 0 uy 0;
tab1.'CHAR' = cha1;
tab1.'RIGI' = (KK1 et bl0);
tab1.'AMOR' = CC1;
tab1.'MASS' = MM1;
tab1.'FREQ' = (1./dt);
tab1.'INST' = prtimeb;
tab1.'SAUV' = VRAI;
tab2 = dynamic tab1;
nn = dime tab2;
prp1 = prog;
repeter lab1 nn;
  depj = (tab2 . &lab1 . DEPL) ;
  si (ega &lab1 1);
    deft = defo lig1 depj 1;
  sinon;
    deft = deft et
     (defo lig1 depj 1);
  finsi;
  prp1 = prp1 et
   (prog (extr depj p1 UX));
fin lab1;
evp1_1 = (evol manu prtimeb prp1);
u1max = (maxi (extr evp1_1 ordo) abs);
nn = dime (extr evp1_1 absc);
yymax = 0;
xxmax = 0;
repeter lab1 nn;
 xx = extr (extr evp1_1 absc) &lab1;
 yy = extr (extr evp1_1 ordo) &lab1;
 si ((abs yy) > yymax);
  yymax = abs yy;
  xxmax = xx;
  nnmax = &lab1;
 finsi;
fin lab1;
depmax1 = tab2 . nnmax . DEPL;
bsi1 = bsigma (sigma depmax1 mod1 mat1) mod1 mat1;
bsi1b = bsi1 -
(* bsi1 (MANU CHPO p0 FX 1. ) (mots FX) (mots FX) (mots FX));
* Méthode 2: intégration directe sur base modale avec pseudomode
tbas1 = table 'BASE_MODALE';
tbas1.'MODES' = vib1b;
* On rajoute le pseudomode à la base modale
tbas1.'PSEUDO_MODES' =psm1;
TRIG = TABLE 'RAIDEUR_ET_MASSE';
TRIG.'RAIDEUR' = pjba tbas1 (KK1 et bl0) ;
TRIG.'MASSE' = pjba tbas1 MM1;
TAMOR = TABLE 'AMORTISSEMENT';
TAMOR . 'AMORTISSEMENT' = PJBA tbas1 CC1;
TCHAR = TABLE 'CHARGEMENT' ;
TCHAR.'BASE_A' = pjba tbas1 cha1;
TSORT = TABLE 'SORTIE' ;
TSORV = TABLE 'VARIABLE' ;
TSORT.'VARIABLE' = TSORV ;
TSORV.'VITESSE' = VRAI;
TSORV.'DEPLACEMENT' = VRAI ;
TSORV.'ACCELERATION' = VRAI ;
DTEX = DT;
NTT = ENTIER (tfin/(DT));
TRESU = DYNE DE_VOGELAERE TRIG TAMOR TCHAR
             NTT DTEX TSORT ;
evp1_2 = EVOL ROUGE RECO TRESU tbas1 cha1 'DEPL' P1 UX ;
evp1_2b = EVOL VERT RECO TRESU tbas1 'DEPL' P1 UX ;
u2max = (maxi (extr evp1_2 ordo) abs);
nn = dime (extr evp1_2 absc);
yymax = 0;
xxmax = 0;
repeter lab1 nn;
 xx = extr (extr evp1_2 absc) &lab1;
 yy = extr (extr evp1_2 ordo) &lab1;
 si ((abs yy) > yymax);
  yymax = abs yy;
  xxmax = xx;
  nnmax = &lab1;
 finsi;
fin lab1;
depmax2 = RECO TRESU tbas1 (nnmax*DTEX) cha1 'DEPL';
bsi2 = bsigma (sigma depmax2 mod1 mat1) mod1 mat1;
bsi2b = bsi2 -
(* bsi2 (MANU CHPO p0 FX 1. ) (mots FX) (mots FX) (mots FX));
SI AFFICH;
 DESS (evp1_1 et evp1_2)
  TITRE 'Calcul sur base physique/base modale';;
 DESS (evp1_2 et evp1_2b)
   TITRE 'Base modale - Résultats avec ou sans pseudomode';
 trac deft anime;
 trac lig1 (vecteur bsi1b fx fy);
 trac lig1 (vecteur bsi2b fx fy);
FINSI;
TEST = (MAXI ((EXTR evp1_2 ORDO) - (EXTR evp1_1 ORDO)) ABS)/
       (MAXI (EXTR evp1_2 ORDO) ABS);
SI (TEST > 0.10);
 ERRE 4;
FINSI;
FIN;
```

## dyna16 [Mecanique Dynamique]
```
* Portique soumis à un déplacement différentiel des appuis
* Calcul sur un mode dynamique et les modes statiques
* D. Combescure aout 2006
* OPTIONS
* GRAPH = VRAI;
GRAPH = FAUX;
* COMPLET = VRAI;
COMPLET = FAUX;
opti dime 2 elem seg2 mode plan cont;
* MAILLAGE
H = 3.;
L = 4.;
p1 = ((-0.5)*L) 0.;
vv = 0. H;
p1h = p1 plus vv;
p2 = (0.5*L) 0.;
p2h = p2 plus vv;
n1 = 10;
n2 = 20;
a = 0.25;
b = a;
e1 = 30000.D6;
ro1 = 2400.;
nu1 = 0.30;
sec1 = a*b;
in1 = (1./12.)*(b*(a**3));
lig1 = (d n1 p1 p1h) et (d n1 p2 p2h) et (d n2 p1h p2h);
* MODELES, MATERIAU ET MATRICES
mod1 = MODE lig1 mecanique elastique TIMO;
mat1 = MATE mod1 YOUN E1 NU nu1 RHO ro1
       SECT sec1 INRZ in1;
KK1 = rigi mod1 mat1;
CC1 = 0.001*KK1;
MM1 = mass mod1 mat1;
bl1 = BLOQ UY RZ p1;
bl2 = BLOQ UY RZ p2;
bl1u = BLOQ UX p1;
bl2u = BLOQ UX p2;
bltot = bl1 et bl2 et bl1u et bl2u;
fh1 = DEPI bl1u 1.;
fh2 = DEPI bl2u 1.;
* MODE PROPRE
vib1 = vibr proche (prog 1.) (lect 1) (KK1 et bltot) MM1;
vib1b= vib1 . 'MODES' ;
nmod = (dime (vib1b) ) - 2;
repeter lab1 nmod;
  dep1 = vib1b. &lab1 . DEFORMEE_MODALE;
  fr1 = vib1b. &lab1 . FREQUENCE;
  MESS &lab1 ' : ' fr1 'Hz';
* trac (defo lig1 dep1) ;
fin lab1;
* CALCUL TEMPOREL
* Définition du chargement
T1 = 0.02;
SI COMPLET;
 tfin = 50.*T1;
SINON;
 tfin = 2.*T1;
FINSI;
ltemps = prog 0. T1 (2.*T1) (3.*T1) (4.*T1) 10.;
lpacc1 = prog 0 1. -1. 0. 0. 0.;
lpacc2 = prog 0 0. 1. -1. 0. 0.;
dt = T1/20.;
ltime = prog 0 pas dt 10.;
evacc1 = evol manu ltime (ipol ltime ltemps lpacc1);
evdep1 evvit1 = insi evacc1;
evacc2 = evol manu ltime (ipol ltime ltemps lpacc2);
evdep2 evvit2 = insi evacc2;
prtimeb = prog 0 pas dt tfin;
prdep1 = extr evdep1 ordo;
prdep2 = extr evdep2 ordo;
* Méthode 1 => on impose le déplacement
* (calcul direct sur base physique avec DYNAMIC)
cha1 = (char fh1 evdep1) et (char fh2 evdep2);
tab1 = table;
tab1.'DEPL' = manu chpo lig1 2 ux 0 uy 0;
tab1.'VITE' = manu chpo lig1 2 ux 0 uy 0;
tab1.'CHAR' = cha1;
tab1.'RIGI' = (KK1 et bltot);
tab1.'AMOR' = CC1;
tab1.'MASS' = MM1;
tab1.'FREQ' = (0.25/dt);
tab1.'INST' = prtimeb;
tab1.'SAUV' = VRAI;
tab2 = dynamic tab1;
nn = dime tab2;
prp1h = prog;
repeter lab1 nn;
  si (ega &lab1 1);
    deft = defo lig1 (tab2 . &lab1 . DEPL) 100;
  sinon;
    deft = deft et
     (defo lig1 (tab2 . &lab1 . DEPL) 100);
  finsi;
  prp1h = prp1h et
   (prog (extr (tab2 . &lab1 . DEPL) p1h UX));
fin lab1;
Ev1UX1 = evol rouge manu prtimeb prp1h;
SI GRAPH;
 dess (evol manu prtimeb prp1h);
 trac deft anime;
FINSI;
* Méthode 2 => on impose -M*[K**-1*uimpose] au second membre
* (calcul direct sur base physique avec DYNAMIC)
* mode statique (à la main)
depsta1 = reso (KK1 et bltot) fh1;
depsta2 = reso (KK1 et bltot) fh2;
fh12 = (-1.)*MM1*depsta1;
fh22 = (-1.)*MM1*depsta2;
cha2 = (char fh12 evacc1) et (char fh22 evacc2);
tab1 = table;
tab1.'DEPL' = manu chpo lig1 2 ux 0 uy 0;
tab1.'VITE' = manu chpo lig1 2 ux 0 uy 0;
tab1.'CHAR' = cha2;
tab1.'RIGI' = (KK1 et bltot);
tab1.'AMOR' = CC1;
tab1.'MASS' = MM1;
tab1.'FREQ' = (0.25/dt);
tab1.'INST' = prtimeb;
tab1.'SAUV' = VRAI;
tab2 = dynamic tab1;
nn = dime tab2;
prp1h2 = prog;
prp1h2t = prog;
repeter lab2 nn;
  depj = (tab2 . &lab2 . DEPL);
  depjt = depj +
     ((extr prdep1 &lab2)*depsta1)
   + ((extr prdep2 &lab2)*depsta2);
  si (ega &lab2 1);
    def2 = defo lig1 depj 1000;
    deft2 = defo lig1 depjt 1000;
  sinon;
    deft2 = deft2 et
     (defo lig1 depjt 1000);
  finsi;
  prp1h2 = prp1h2 et
   (prog (extr depj p1h UX));
  prp1h2t = prp1h2t et
   (prog (extr depjt p1h UX));
fin lab2;
ta = table;
ta.2 = 'TIRR';
ta.3 = 'TIRL';
ta.4 = 'TIRL';
Ev2UX1 = evol rouge manu prtimeb prp1h2t;
* Méthode 3=> superposition de solution statique et dynamique
* (calcul direct sur base modale avec DYNE)
vib1 = vibr proche (prog 1.) (lect 1)
        (KK1 et bl1 et bl2 et bl1u et bl2u) MM1 'SOLU';
SPLA1=STRU (KK1 et bl1 et bl2 et bl1u et bl2u) MM1 ;
ELM1=CLST SPLA1 BL1u;
ELM2=CLST SPLA1 BL2u;
PR1=PROG 1. ;
LIUX=(RELA ELM1 LX PR1) et (RELA ELM2 LX PR1);
SOL1 = SOLS LIUX SPLA1;
BASE1 = BASE SPLA1 VIB1 LIUX SOL1;
MODYN1 = TRADUIRE (EXTR BASE1 MODE);
MOSTA1 = TRADUIRE (EXTR BASE1 STAT);
depsta1 = MOSTA1. 1 . DEFORMEE_MODALE;
fh12 = (-1.)*MM1*depsta1;
depsta2 = MOSTA1. 2 . DEFORMEE_MODALE;
fh22 = (-1.)*MM1*depsta2;
cha3 = (char fh12 evacc1) et (char fh22 evacc2);
vib1c= traduire vib1;
tbas1 = table 'BASE_MODALE';
tbas1.'MODES' = vib1c;
TRIG = TABLE 'RAIDEUR_ET_MASSE';
TRIG.'RAIDEUR' = pjba tbas1 (KK1 et bl1 et bl2 et bl1u et bl2u) ;
TRIG.'MASSE' = pjba tbas1 MM1;
TAMOR = TABLE 'AMORTISSEMENT';
TAMOR . 'AMORTISSEMENT' = PJBA tbas1 CC1;
TCHAR = TABLE 'CHARGEMENT' ;
TCHAR.'BASE_A' = pjba tbas1 cha3;
TSORT = TABLE 'SORTIE' ;
TSORV = TABLE 'VARIABLE' ;
TSORT.'VARIABLE' = TSORV ;
TSORV.'VITESSE' = VRAI;
TSORV.'DEPLACEMENT' = VRAI ;
TSORV.'ACCELERATION' = VRAI ;
DTEX = (pi/12.6)/100.;
NTT = ENTIER (tfin/DTEX);
* Appel à DYNE
TRESU = DYNE DE_VOGELAERE TRIG TAMOR TCHAR
             NTT DTEX TSORT ;
* POST-TRAITEMENT
Ev3UXD1 = EVOL VERT RECO TRESU tbas1 'DEPL' P1h UX ;
EV3UXS1 = EVOL MANU (EXTR Ev3UXD1 ABSC)
     (ipol (EXTR Ev3UXD1 ABSC) (extr evdep1 absc)
        ((extr evdep1 ordo)*(extr depsta1 p1h ux)));
EV3UXS2 = EVOL MANU (EXTR Ev3UXD1 ABSC)
     (ipol (EXTR Ev3UXD1 ABSC) (extr evdep2 absc)
        ((extr evdep2 ordo)*(extr depsta2 p1h ux)));
Ev3UX1 = EVOL MANU (EXTR Ev3UXD1 ABSC)
     ((EXTR Ev3UXD1 ORDO) + (EXTR Ev3UXS1 ORDO)
    + (EXTR Ev3UXS2 ORDO));
SI GRAPH;
 TRAC (DEFO LIG1 (MODYN1. 1 . DEFORMEE_MODALE));
 TRAC ((DEFO LIG1 depsta1) et
      (DEFO LIG1 depsta1 0. ROUG));
 TRAC ((DEFO LIG1 depsta2) et
      (DEFO LIG1 depsta2 0. ROUG));;
 TRAC ((DEFO LIG1 (depsta1 + depsta2)) et
      (DEFO LIG1 depsta2 0. ROUG));;
 trac lig1 (vecteur fh12 fx fy);
 trac lig1 (vecteur fh22 fx fy);
 trac lig1 (vecteur (fh12 et fh22) fx fy);
 dess (evacc1 et (evacc2 coul rouge)) xbord 0. 0.20;
 dess (evdep1 et (evdep2 coul rouge)) xbord 0. 0.20;
 DESS (Ev3UXD1 et Ev3UXS1 et Ev3UXS2) xbord 0 0.2;
 DESS (Ev1UX1 et Ev2UX1 et Ev3UX1) xbord 0. 1.;
FINSI;
TEST = MAXI (PROG
     ((MAXI (EXTR Ev2UX1 ORDO)) - (MAXI (EXTR Ev1UX1 ORDO)))
     ((MAXI (EXTR Ev3UX1 ORDO)) - (MAXI (EXTR Ev1UX1 ORDO)))) ABS;
SI (TEST > 1.D-5);
  ERR 4;
  LIST TEST;
FINSI;
FIN;
```

## sissi [Mecanique Dynamique]
```
* Test sissi.dgibi: jeux de données
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
* Mots-clés : Vibrations, calcul modal,
* poutre, seisme
* SISSI
* CAS TEST DU 91/06/19 PROVENANCE : PLAF
* CAS TEST DU 91/06/18 PROVENANCE : PLAF
* test de la procedure SISSIB
* 1 poutre encastree, 20 elements finis,
* IY different de IZ, un spectre
* d'oscillateurs en ACCE direction du
* seisme : X
TEMPS ;
OPTI DIME 3 ELEM 'SEG2' ;
C1 = 0. 0. 0. ;
C2 = 0. 0. 5. ;
C3 = 0. 0. 10. ;
L1 = DROITE 10 C1 C2 ;
L2 = DROITE 10 C2 C3 ;
LI = L1 ET L2 ;
SI (NEG GRAPH 'N');
  TRAC 'QUAL' LI;
FINSI;
MOD1 = MODE LI MECANIQUE ELASTIQUE POUT ;
CH_MAT = MATE MOD1 YOUNG 2.E11 NU 0.3 RHO 7800. ;
CH_CAR = CARA MOD1 SECT 0.25 INRY 0.006 INRZ 0.004 TORS 0.01 VECT ( 0. 1. 0. ) ;
CH_MAT=CH_MAT et CH_CAR;
RIG1 = RIGI CH_MAT MOD1 ;
ENC1 = BLOQ C1 DEPL ROTA ;
RIGFI= RIG1 ET ENC1 ;
MAS1 = MASS CH_MAT MOD1 ;
* Calcul des premiers modes
L_FREQ = PROG 3.58 4.38 24.09 25.15 ;
MODE_POU = VIBR PROCHE L_FREQ RIGFI MAS1 ;
* Calcul des contraintes modales
MODE_POU = SIGSOL MOD1 CH_MAT MODE_POU ;
* Calcul des reactions modales
MODE_POU = REAC ENC1 MODE_POU ;
ITAB2 = MODE_POU . 'MODES' ;
NB_MODE = ( DIME ITAB2 ) - 2 ;
* Definition du spectre acceleration
LIS_TEMP = PROG 0. PAS 1.E-2 0.50 ;
LIS_ACCE = PROG 0. 0.5 1. 0.5 0. -0.5 -1. -0.5 0. 0.5 1. 0.5 0. -0.5 -1. -0.5 0. 0.5 1. 0.5 0. -0.5 -1. -0.5 0. 0.5 1. 0.5 0. -0.5 -1. -0.5 0. 0.5 1. 0.5 0. -0.35 -0.7 -0.35 0. 0.25 0.5 0.25 0. -0.15 -0.3 -0.15 0. 0.1 0. ;
                  LIS_CHAR = EVOL MANU LIS_TEMP LIS_ACCE ;
SI (NEG GRAPH 'N');
  TITR 'Chargement en Acceleration';
  DESS LIS_CHAR;
FINSI;
LIS_FREQ = PROG 1. PAS 2. 400. ;
LIS_AMOR = PROG 2. 5. 10. 15. ;
LIS_AMOR = LIS_AMOR * 1.e-2 ;
SEISME_X = SPO LIS_CHAR 'AMOR' LIS_AMOR 'FREQ' LIS_FREQ 'ACCE' ;
BAS_AMOR = PROG 4. 6. 7. 9. ;
BAS_AMOR = BAS_AMOR * 1.e-2 ;
TAB1 = TABL ;
TAB1 . 'STRUCTURE' = MODE_POU ;
TAB1 . 'AMORTISSEMENT' = BAS_AMOR ;
TAB3 = 'TABLE' 'EXCITATION' ;
TAB1 . 'EXCITATION' = TAB3 ;
TAB3 . 1 = 'TABLE' ;
TAB3 . 1 . 'DIRECTION' = 'X' ;
TAB3 . 1 . 'SPECTRE' = SEISME_X ;
TAB3 . 1 . 'AMORTISSEMENT' = LIS_AMOR ;
TAB1 . 'RECOMBINAISON_MODES' = 'SRSS';
TAB1 . 'RECOMBINAISON_DIRECTIONS' = 'QUADRATIQUE' ;
TAB4 = 'TABLE' 'SORTIES' ;
TAB1 . 'SORTIES' = TAB4 ;
TAB4 . 'DOMAINE' = MOD1 ;
TAB4 . 'DEPLACEMENTS' = VRAI ;
TAB4 . 'CONTRAINTES' = VRAI ;
TAB4 . 'ACCELERATIONS' = VRAI ;
TAB2 = SISSIB TAB1 ;
MESS ' Chpoint de deplacement du point  C3 issu de SISSIB :' ;
MESS '  ' ;
CHP_DEP = TAB2 . 'X' . 'DEPLACEMENTS' ;
LIST ( REDU CHP_DEP C3 ) ;
MESS ' Chpoint d acceleration du point  C3 issu de SISSIB :' ;
MESS '  ' ;
CHP_ACC = TAB2 . 'X' . 'ACCELERATIONS' ;
LIST ( REDU CHP_ACC C3 ) ;
CHE_CONT = TAB2 . 'X' . 'CONTRAINTES' ;
MAX_CONT = MAXI CHE_CONT ;
MESS ' Valeur maximale des contraintes  issue de SISSIB =' MAX_CONT ;
MESS '  ' ;
* Verification de la procedure
* Verification du deplacement
* Verification de l'acceleration
* Verification de la contrainte maximale
* ----- calcul de S(N,X,B) -----
TSEIS = TABL ;
NB_AMOR = 'DIME' LIS_AMOR ;
I_MODE = 0 ;
REPETER BOUC1 NB_MODE ;
   I_MODE = I_MODE + 1 ;
   ITAB3 = ITAB2 . I_MODE ;
   F_N = ITAB3 . 'FREQUENCE' ;
   LOG_F_N = LOG F_N ;
   B_N = EXTRAIRE BAS_AMOR I_MODE ;
   P_SPEC = 'PROG' ;
   I_AMOR = 0 ;
   REPETER BOUC10 NB_AMOR ;
      I_AMOR = I_AMOR '+' 1 ;
      EVOLS1 = 'EXTR' SEISME_X 'COUR' I_AMOR ;
      LISABS1 = 'EXTR' EVOLS1 'ABSC' ;
      LISORD1 = 'EXTR' EVOLS1 'ORDO' ;
      LOG_ABS1 = 'LOG' LISABS1 ;
      LOG_ORD1 = 'LOG' LISORD1 ;
      S1 = IPOL LOG_F_N LOG_ABS1 LOG_ORD1 ;
      S_1 = 'EXP' S1 ;
      P_SPEC = P_SPEC ET ( 'PROG' S_1 ) ;
   FIN BOUC10 ;
   S_N = 'IPOL' B_N LIS_AMOR P_SPEC ;
  TSEIS . I_MODE = S_N ;
FIN BOUC1 ;
I_MODE = 0 ;
ZTRON = 'MANU' 'CHPO' LI 1 'UX' 1. ;
REPETER BOUC2 NB_MODE ;
   I_MODE = I_MODE + 1 ;
   S_I = TSEIS . I_MODE ;
   ITAB3 = ITAB2 . I_MODE ;
   F_I = ITAB3 .'FREQUENCE' ;
   D_I = ITAB3 .'DEFORMEE_MODALE' ;
   C_I = ITAB3 .'CONTRAINTE_MODALE' ;
   ITAB4=ITAB3 .'DEPLACEMENTS_GENERALISES';
   Q_I = ITAB4 . 1 ;
   M_I = ITAB3 . 'MASSE_GENERALISEE' ;
   W_I = 2.0 * PI * F_I ;
   QSM = Q_I / M_I ;
   COEF_1 = QSM / ( W_I * W_I ) ;
   DEPL_I = COEF_1 * S_I * D_I ;
   ACCE_I = QSM * S_I * D_I ;
   ZTRON = ZTRON - ( QSM * D_I ) ;
   CONT_I = COEF_1 * S_I * C_I ;
   'SI' ( I_MODE 'EGA' 1 ) ;
      DEPL_T = DEPL_I ** 2 ;
      ACCE_T = ACCE_I ** 2 ;
      CONT_T = CONT_I ** 2 ;
   'SINON' ;
      DEPL_T = DEPL_T + ( DEPL_I ** 2 ) ;
      ACCE_T = ACCE_T + ( ACCE_I ** 2 ) ;
      CONT_T = CONT_T + ( CONT_I ** 2 ) ;
   'FINSI' ;
FIN BOUC2 ;
LISORD1 = 'EXTR' SEISME_X 'ORDO' 1 ;
NVAL_1 = 'DIME' LISORD1 ;
GAMMA0 = 'EXTR' LISORD1 NVAL_1 ;
ACCE_T = ACCE_T + ( ( GAMMA0 * GAMMA0 ) * ( ZTRON ** 2 ) );
DEPL_T = DEPL_T ** 0.5 ;
ACCE_T = ACCE_T ** 0.5 ;
CONT_T = CONT_T ** 0.5 ;
D_SOM_X = 'EXTR' DEPL_T C3 'UX' ;
A_SOM_X = 'EXTR' ACCE_T C3 'UX' ;
C_MAX = 'MAXI' CONT_T ;
DEP = EXTR CHP_DEP C3 'UX' ;
ACC = EXTR CHP_ACC C3 'UX' ;
MESS '    deplacement du point C3 :' ;
LIST ( 'REDU' DEPL_T C3 ) ;
SAUTER 2 LIGNES ;
MESS '   acceleration du point C3 :' ;
LIST ( 'REDU' ACCE_T C3 ) ;
SAUTER 2 LIGNES ;
MESS '   contrainte maximale  =' C_MAX ;
SAUTER 2 LIGNES ;
TEMPS ;
* Code de bon fonctionnement
REF_DEP = D_SOM_X ;
REF_ACC = A_SOM_X ;
REF_CON = C_MAX ;
RES1 = 100 * (ABS ( ( DEP - REF_DEP ) / REF_DEP ));
RES2 = 100 * (ABS ( ( ACC - REF_ACC ) / REF_ACC ));
RES3 = 100 * (ABS ( ( MAX_CONT - REF_CON ) / REF_CON ));
SAUTER 2 LIGNES ;
MESS 'deplacement theorique :' D_SOM_X 'm';
MESS 'deplacement calculee  :' DEP 'm';
MESS '    Soit un ecart de : ' RES1 '%';
SAUTER 1 LIGNES ;
MESS 'acceleration theorique:' A_SOM_X 'm';
MESS 'acceleration calculee :' ACC 'm';
MESS '    Soit un ecart de : ' RES2 '%';
SAUTER 1 LIGNES ;
    SI ( RES1 <EG 1. ) ;
   ERRE 0 ;
SINON ;
   ERRE 5 ;
FINSI ;
SI ( RES2 <EG 1. ) ;
   ERRE 0 ;
SINON ;
   ERRE 5 ;
FINSI ;
SI ( RES3 <EG 1. ) ;
   ERRE 0 ;
SINON ;
   ERRE 5 ;
FINSI ;
FIN ;
```

## trac3d [Mecanique Dynamique]
```
* Mots-clés : Vibrations, calcul modal, coque, 2D Fourier,
* Reconstruction 3D
* TEST TRAC3D
* P3
* P1 P2
* Soit un cylindre dont on calcule la fréquence propre du
* deuxieme mode de flexion en mode fourier 1 puis 3. On
* construit alors les champs de déplacement tridimensionnels
* ainsi que le maillage 3D. on superpose les deux calculs pour
* obtenir un champs de deplacement 3D et une déformée.
OPTION ECHO 1;
GRAPH='N';
SAUT PAGE ;
OPTI NORM AUTO ;
OPTI DIME 2;
OPTI MODE FOUR NOHARM ;
OPTI ELEM SEG2;
* GEOMETRY
P1 = 0. 0. ;
P2 = 3.5 0.0 ;
P3 = 3.5 7.0 ;
LI1 = P1 DROIT 3 P2 ;
STEEL = LI1 ET (P2 DROIT 8 P3) ;
* MODELE - MATERIAU - RIGIDITE - MASSE
MODCOQ=MODE STEEL MECANIQUE COQ2 ;
MATCOQ=MATE MODCOQ RHO 8.0E3 YOUN 2.E11 NU 0.3 ;
CARCOQ=CARA MODCOQ EPAI 0.035 ;
MATCOQ=MATCOQ ET CARCOQ;
* BOUNDARY CONDITION
CL1 = BLOQ DEPL ROTA LI1 ;
* ============= MODE FOURIER 1 ================================
OPTI MODE FOUR 1 ;
RIG1 = RIGI MODCOQ MATCOQ ;
MAS1 = MASS MODCOQ MATCOQ ;
* CALCULATION OF THE FREQUENCIES
* AND
* EXTRACTION OF SOME RESULTS
RESUL = VIBR proche (prog 150.) (CL1 ET RIG1 ) MAS1 IMPR ;
FREQ1 = RESUL.MODES. 1 . FREQUENCE ;
DEP1 = RESUL. MODES. 1 . DEFORMEE_MODALE ;
DEP1 = NNOR DEP1 AVEC (MOTS UR) ;
DEP3D1 = CREER_3d STEEL DEP1 360. 20 1 ;
* ============= MODE FOURIER 3 ================================
OPTI MODE FOUR 3 ;
RIG1 = RIGI MODCOQ MATCOQ ;
MAS1 = MASS MODCOQ MATCOQ ;
* CALCULATION OF THE FREQUENCIES
* AND
* EXTRACTION OF SOME RESULTS
RESUL = VIBR PROC (PROG 100.) (CL1 ET RIG1 ) MAS1 IMPR ;
FREQ1 = RESUL.MODES. 1 . FREQUENCE ;
DEP1 = RESUL. MODES. 1 . DEFORMEE_MODALE ;
DEP1 = NNOR DEP1 AVEC (MOTS UR) ;
DEP3D3 = CREER_3d STEEL DEP1 360. 20 3 ;
ELIM DEP3D1.MAILLAGE DEP3D3.MAILLAGE 1.E-3 ;
DEP3DT = DEP3D1.DEPLACEMENT + DEP3D3.DEPLACEMENT ;
DEF3DT= DEFO DEP3DT DEP3D1.MAILLAGE 1 ;
TITR 'MAILLAGE 3D MODE FOURIER 1 ET 3 MODE AXIAL 2' ;
SI ( EGA GRAPH 'O') ;
TRAC (0. 12. 30.) CACH DEF3DT ;
FINSI;
POI1 = 0. 3.5 7. ;
POI2 = DEP3D1.MAILLAGE POIN PROC POI1 ;
DEPPOI2 = REDU DEP3DT POI2 ;
UXPOI2 = EXCO UX DEPPOI2 ;
POI22 = EXTR UXPOI2 MAIL ;
PP1 = POI22 POIN PROC (0 0 0) ;
UXPOI22 = EXTR UXPOI2 SCAL PP1 ;
ERR1=100*(ABS(0.14 - UXPOI22)/0.14);
SI (ERR1 < 5 );
ERRE 0;
SINON ;
ERRE 5;
FINSI;
FIN ;
```

## vibr9 [Mecanique Dynamique]
```
* Mots-clés : flambage, modes complexes,
* forces suiveuses, flottement
* TEST : VIBR9
* Calcul des modes propres complexes d'une
* structure soumise a une force suiveuse
* (la structure est composée de deux barres
* reliees par deux ressorts spiraux)
* Opti Echo 0;
Opti dime 2 elem seg2 impi 0;
* --- Affichage
Graph = 'N';
Affich = VRAI;
* Points reperes
P1= 0 0;
P2= 1 0;
L1 = D 1 P1 P2;
L2 = D 1 P2 P1;
* Description du système
* Demi-longueur d'une barre
a = 1;
* Masse d'une barre
m = 10;
* Raideur des ressorts spiraux
k = 20;
* Variation de la force suiveuse
Fmin = 0.;
Fmax = 100.;
PFs = 1.;
lFs= Prog Fmin PAS PFs Fmax;
* Frontiere des domaines
Fs1 = 5*k/(4*a);
Fs2 = 13*k/(4*a);
Si (Affich);
  Mess 'Fs 1 = ' Fs1;
  Mess 'Fs 2 = ' Fs2;
Finsi;
* Définition des grandeurs physiques
* --- Matrice Masse totale
Mt = m*a*a*(MANU RIGI type MASSE L1 (MOTS ALFA) DUAL (MOTS FALF) (PROG 5. 1. 1. 1.));
* --- Matrice Raideur
Ks = k*(MANU RIGI type RIGIDITE L1 (MOTS ALFA) DUAL (MOTS FALF) (PROG 2. -1. -1. 1.));
* --- Matrice Raideur pour force suiveuse unitaire
UK = 2*a*(MANU RIGI type RIGIDITE L1 (MOTS ALFA) DUAL (MOTS FALF) 'QUEL' (PROG -1. 1. 0. 0.));
* Initialisation de l'algorithme
* Frequences propres
Freqr = Table 'FREQ_REEL';
Freqi = Table 'FREQ_IMAG';
Repeter Freq1 4;
  Ifreq = &Freq1;
  Freqr.Ifreq = Prog;
  Freqi.Ifreq = Prog;
Fin Freq1;
dlFs = dime lFs;
* Itérations sur Fs
* --- Reperage de la force critique
FSauv = 'N';
Repeter bloc1 dlFs;
  i=&bloc1;
  Fs = extr lFs i;
* --- Matrice de Raideur totale
  Kt = Ks et (Fs*UK) ;
* Résolution
  BASC = VIBC Mt Kt ;
* Traitement et stockage
  Si (AFFICH);
  Mess 'Iteration' I;
  Mess 'Force suiveuse : ' Fs ;
  Mess ' ';
  Mess '---------------------------------------------------------------- --------------';
  Mess '  Mode     Frequence      Amort.      P. Reelle    P. Imaginaire Stabilité  ';
  Finsi;
  BMOD = BASC.'MODES';
  Repeter Freq2 4;
    Ifreq=&Freq2;
    MOD = BMOD.Ifreq;
    Si (EGA MOD.SOUSTYPE 'MODE_ANNULE');
      f1 = 0.;
      if1 =1.;
    Sinon;
      f1 = MOD.'FREQUENCE_REELLE';
      if1 =MOD.'FREQUENCE_IMAGINAIRE';
    Finsi;
    Freqr.Ifreq = Freqr.Ifreq et (Prog f1);
    Freqi.Ifreq = Freqi.Ifreq et (Prog if1);
    Si (Affich);
      Msg = 'STAB.';
      Si ((< if1 -1.D-10) et (>EG f1 0.));
        Msg = 'INST.';
        Si (EGA FSauv 'N');
          Fcrit = Fs - (PFs/2.);
          FSauv = 'O';
        Finsi;
      Finsi;
      Si (> f1 0.);
* Valeurs propres relatives a lambda = i omega = ix2PIxf
        Mess Ifreq f1 (if1/f1) (-2*PI*if1) (2*PI*f1) Msg;
      Sinon;
        Si (EGA f 0.);
          Mess Ifreq f1 '     -----     ' (-2*PI*if1) (2*PI*f1) Msg;
        Finsi;
      Finsi;
    Finsi;
  Fin Freq2;
  Mess ' ';
  Mess ' ';
* Fin du calcul
Fin bloc1;
Si ( EGA Graph 'O');
  TabM = Table;
  TabM.1 = 'NOLI';
  Titr 'Frequence (partie reelle)';
  Evol1 = Evol BLEU manu lFs (Freqr.1);
  Titr 'Frequence (partie imaginaire)';
  Evol2 = Evol BLEU manu lFs (Freqi.1);
  Titr 'Frequence dans le plan complexe';
  Evol3 = Evol BLEU manu (Freqr.1) (Freqi.1);
  Repeter Trac1 3;
    i=&Trac1+1;
    TabM.i ='NOLI';
    Titr 'Frequence (partie reelle)';
    Evol1 = Evol1 et (Evol BLEU manu lFs (Freqr.i));
    Titr 'Frequence (partie imaginaire)';
    Evol2 = Evol2 et (Evol BLEU manu lFs (Freqi.i));
    Titr 'Frequence dans le plan complexe';
    Evol3 = Evol3 et (Evol BLEU manu (Freqr.i) (Freqi.i));
  Fin Trac1;
  Dess Evol1 Titx 'Force (N)' Tity 'Re(F) (Hz)' TabM;
  Dess Evol2 Titx 'Force (N)' Tity 'Im(F) (Hz)' TabM;
  Dess Evol3 Titx 'Re(F) (Hz)' Tity 'Im(F) (Hz)' TabM;
Finsi;
Mess ' Theorie    Calcul       Erreur ';
Mess Fs1 Fcrit (Abs(Fcrit-Fs1)/Fs1);
* Opti donn 5;
Si ((Abs(Fcrit-Fs1)/Fs1) < 0.05);
  Erre 0;
Sinon;
  Erre 5;
Finsi;
FIN;
```

## Cast_test_RelaPout [Mecanique Elastique]
```
* Tranfert of load for beam elements - load known for a solid model
* D. COMBESCURE
* F4E - 6th January 2014
OPTI DIME 3 ELEM CUB8;
* Modele 1: Forces calculated with another software/here created manually
FLAGVISU = FAUX;
L1 = 0.1;
L2 = 0.25;
L3 = 3.;
fac1 = 1;
n1 = 2*fac1;
n2 = 3*fac1;
n3 = 10*fac1;
p0 = (-0.5*L1) (-0.5*L2) 0.;
p1 = (0.5*L1) (-0.5*L2) 0.;
vy = 0. L2 0.;
vz = 0. 0. L3;
p0c = 0. 0. 0.;
p1c = 0. L2 0.;
p0top = p0 plus (vz);
p1top = p1 plus (vz);
Lig0 = D n1 p0 p1;
Sur0 = Lig0 tran n2 vy;
Vol0 = Sur0 volu n3 tran vz;
elim 0.001 (vol0 et p0top et p1top et sur0);
Mod0 = mode vol0 mecanique elastique CUB8;
Emat0 = 200.D9;
Nmat0 = 0.3;
romat0 = 7800.;
mat0 = MATE mod0 youn Emat0 NU Nmat0 RHO romat0;
rig0 = rigi Mod0 mat0;
blvol0 = bloq sur0 depl;
mas0 = mass mod0 mat0;
lum0 = lump Mod0 Mat0;
* Loads
* Uniform acceleration
* for0 = mas0*accuni;
* Triangular acceleration
* for0 = mas0 * acc0;
* Lumped force
for0 = FORC FX 1. p0top;
SI FLAGVISU;
 TRAC VOL0 (VECTEUR for0 FX FY FZ) cach;
FINSI;
* Modele 2 - Mechanical model - Beam model
n1b = 3*fac1;
n2b = 4*fac1;
n3b = 15*fac1;
ep1 = 0.00001;
ep0 = (-1.)*ep1;
ep2 = ep1;
ep3 = ep1;
p0c = 0. 0. 0.;
vz = 0. 0. L3;
p1c = p0c plus vz;
opti elem seg2;
Vol1 = D n3b p0c p1c;
p0S = (-0.5*L1) (-0.5*L2) 0.;
p1S = (0.5*L1) (-0.5*L2) 0.;
opti elem qua4;
ns1 = 1;
ns2 = 1;
LigS1 = D ns1 p0S p1S;
SurS1 = LigS1 tran ns2 vy;
modS1 = mode SurS1 MECANIQUE ELASTIQUE QUAS;
Emat1 = 200.D9;
Nmat1 = 0.3;
romat1 = 7800.;
matS1 = MATE modS1 youn Emat1 NU Nmat1 RHO romat1
              ALPY 1. ALPZ 1.;
Mod1 = mode Vol1 mecanique elastique SECTION timo;
mat1 = mate mod1 MODS modS1 MATS mats1 VECT (1. 0. 0.);
rig1 = rigi Mod1 mat1;
mas1 = mass Mod1 Mat1;
bl0 = bloq depl vol1;
bl00 = bloq depl rota p0c;
rigmod = rig1 et bl00;
* Creation of the solid mesh and the constraints
* linking the beam and the solid meshes
tab11 = table;
tab11.'RELATION_3D' = VRAI;
vol1_3D = pout2mas mod1 mat1 tab11;
blpout = tab11.'RELATION_3D';
SI FLAGVISU;
 oeil = 2. 2. 4.;
 trac oeil vol1_3D cach;
FINSI;
Mod1b = mode VOL1_3D mecanique elastique ;
Emat1 = 200.D9;
Nmat1 = 0.3;
romat1 = 7800.;
mat1b = MATE mod1b youn Emat1 NU Nmat1 RHO romat1;
rig1b = rigi Mod1b mat1b;
* Displacement field to be transfered from vol1 to vol0
* Transfert through the Lagrangian multiplier
frdep0 = for0;
* Relation maitre-esclave
* Vol0 suit Vol1
rel1 = rela vol0 'ACCRO' vol1_3D;
rigtot1 = rig1 et bl00 et rel1 et blpout;
depj1 = reso rigtot1 frdep0;
* Calcul des forces nodales a partir des deplacements sur le modele 1
frdep1 = (rig1 et bl00) * depj1;
SI FLAGVISU;
 oeil = 2. 2. 4.;
 trac (defo vol1_3D depj1);
 TITRE 'Transfer through Lagrangian muliplier';
 trac vol1 (vecteur frdep1 FX FY FZ) cach;
FINSI;
* Test
res0 = maxi (resu frdep0);
res1 = maxi (resu frdep1);
ERR = (res0 - res1)/res0;
'SI' (ERR '>' 1.E-6) ; 'ERRE' 5; 'FINS' ;
'FIN' ;
```

## cham_vari [Mecanique Elastique]
```
* exemple d'utilisation de REDU gén&éralisé pour créer un grand champ
* associé à un modèle
opti dime 2 elem qua4;
su1 = ( 0 0 ) droi 10 (10 0 ) trans 5 ( 0 5);
l2 = cote 3 su1;
su2 = l2 trans 5 ( 0 5);
l3= cote 3 su2;
su3= l3 trans 5 (0 5);
* trac ( su1 et su2 et su3);
* exemple quand il y a peu de zones differentes
y1 = manu chml su1 youn 10. constituant 'TOTO' ;
y2 = manu chml su2 youn 20. constituant 'TOTO' ;
y3= manu chml su3 youn 30. constituant 'TOTO';
mo = model ( su1 et su2 et su3) mecanique elastique constituant 'TOTO' ;
you1= redu ( y1 et y2 et y3) mo;
ma1 = mate mo YOUN you1;
* exemple quand on veut une valeur constante par élément et que l'on peut
* définir un LISTREEL contenant ces valeurs
z1= prog (nbel su1)*10.;
z2= prog (nbel su2)*20.;
z3= prog (nbel su3)*30.;
ytot=z1 et z2 et z3;
you2= manu chml mo repa type RIGIDITE YOUN ytot;
ma2 = mate mo YOUN you2;
fin;
```

## comp1_fourier [Mecanique Elastique]
```
* CYLINDRE COMPOSITE BICOUCHE
* FIBRES ENROULEES -45/+45 AUTOUR DE L'AXE
* PRESSION INTERNE
* Un cylindre bloqué à sa base en déplacement suivant
* l'axe Z est soumis à une pression interne.
* 2D Fourier COQ2
* Ref : Rapport CEA , DEMT 85-482 , M. Hittinger, 1985
* Remise a plat : BP, 2017-01-23
* SI GRAPH = N PAS DE GRAPHIQUE AFFICHE
* SINON SI GRAPH DIFFERENT DE N TOUS
* LES GRAPHIQUES SONT AFFICHES
GRAPH = 'N' ;
* GRAPH = 'O';
SAUT PAGE;
SI (NEG GRAPH 'N') ;
  OPTI ECHO 1 ;
* OPTI TRAC X ;
  OPTI TRAC 'PSC' EPTR 5;
SINO ;
  OPTI ECHO 1 ;
FINSI ;
TITRE 'CYLINDRE COMPOSITE BICOUCHE SOUS PRESSION INTERNE';
OPTION DIME 2 MODE FOUR 0 ELEM SEG2;
DENS 0.1 ;
 NAX = 1;
 NAX = 4;
* GEOMETRIE
R = 1.05 ; H = 1. ;
PA = R 0.; PB = R H ;
O1 = 0. 0. ; O2 = 0. 1.;
CYL = PA DROIT NAX PB ;
SI (NEG GRAPH 'N') ;
  TRAC CYL 'QUAL' ;
FINSI ;
* DESCRIPTION DU MATERIAU ORTHOTROPE : COUCHE 1
MOD1 = MODE CYL MECANIQUE ELASTIQUE ORTHOTROPE COQ2 'CONS' 'couche 1';
MAT1 = MATE MOD1 'DIRE' O2 'INCL' 45
                 'YG1' 7.E6 'YG2' 1.3E6 NU12 0.28 G12 5.E5
                 'EPAI' 0.05 'EXCE' 0.025 ;
* verification graphique de l'orientation :
* 2D fourier coque => 3 vecteurs : V1, V2 et V3
v123 = VLOC MOD1 MAT1;
* mo123 = mots 'V1R' 'V1Z' 'V1T' 'V2R' 'V2Z' 'V2T' 'V3R' 'V3Z' 'V3T';
mo123 = mots 'V1R' 'V1Z' 'V2R' 'V2Z' 'V3R' 'V3Z' ;
ve123 = VECT v123 MOD1 0.07 mo123 (mots 'AZUR' 'OR' 'POUR');
SI (NEG GRAPH 'N');
  TITRE 'COMP1 couche 1 : V1(AZUR)  V2 (JAUNE)  V3(ROUG)';
  TRACE ve123 CYL 'CACH';
FINSI ;
* DESCRIPTION DU MATERIAU ORTHOTROPE : COUCHE 2
MOD2 = MODE CYL MECANIQUE ELASTIQUE ORTHOTROPE COQ2 'CONS' 'couche 2' ;
MAT2 = MATE MOD2 'DIRE' O2 'INCL' -45
                 'YG1' 7.E6 'YG2' 1.3E6 NU12 0.28 G12 5.E5
                 'EPAI' 0.05 'EXCE' -0.025 ;
* verification graphique de l'orientation :
v123 = VLOC MOD2 MAT2;
ve123 = VECT v123 MOD2 0.07 mo123 (mots 'AZUR' 'BRON' 'POUR');
SI (NEG GRAPH 'N');
  TITRE 'COMP1 couche 2 : V1(AZUR)  V2 (JAUNE)  V3(ROUG)';
  TRACE ve123 CYL 'CACH';
FINSI ;
* chargement
MOP = 'MODE' CYL 'CHARGEMENT' 'PRESSION' COQ2 ;
* on met -1 pour etre orienté vers les r>0
MAP = 'PRES' MOP 'PRES' -1. ;
* CREATION DE LA RIGIDITE
MODORT = MOD1 ET MOD2 'ET' MOP ;
MATORT = MAT1 ET MAT2 ;
RIG12 = RIGI MODORT MATORT ;
* CONDITIONS AUX LIMITES
CDL1 = BLOQ 'UZ' pB ;
CDL2 = BLOQ 'UT' pB ;
CDL = CDL1 ET CDL2 ;
* CALCUL
RIGITOT = RIG12 ET CDL ;
FP = 'BSIG' MOP MAP ;
DEP1 = RESO RIGITOT FP ;
DEFO0= DEFO CYL 0.0 DEP1 GRIS;
DEFO1= DEFO CYL DEP1 (EXCO DEP1 'UR');
SI (NEG GRAPH 'N') ;
 TRAC (DEFO1 et DEFO0) ;
FINSI;
* ref = calcul element LC8 tire de [DEMT 85-482]
uref = (0.63615E-5 + 0.64702E-5) /2.;
* VALEUR pour le TEST
ur1A = EXTR DEP1 'UR' PA ;
ur1B = EXTR DEP1 'UR' PB ;
MESS ' DEPLACEMENT RADIAL REFERENCE : ' uref;
MESS ' DEPLACEMENT RADIAL EN PA CALCULE :' ur1A ur1B;
RES1= ABS((ur1A - uref) / uref);
MESS 'ECART RELATIF : ' RES1 ;
MESS '************************************************';
SAUT 2 LIGN ;
TEMPS ;
* CODE BON FONCTIONNEMENT
SI (RES1 <EG 5.E-2);
   ERRE 0 ;
SINO;
   ERRE 5 ;
FINSI ;
FIN;
```

## joi22 [Mecanique Elastique]
```
* Test Joi22.dgibi: Jeux de données
OPTI ECHO 0 ;
SAUT PAGE ;
MESS'!==============================================!';
MESS'!                                              !';
MESS'!                    TEST JOI22                !';
MESS'!                                              !';
MESS'!       ESSAI DE TRACTION SUR UN JOINT 2D      !';
MESS'!                                              !';
MESS'!  Un joint 2D JOI2 a son bord inferieur       !';
MESS'!  encastre.                                   !';
MESS'!  Son bord superieur est libre. Un effort de  !';
MESS'!  traction est exercé sur son bord superieur. !';
MESS'!                                              !';
MESS'!                                              !';
MESS'!  Solution analytique :                       !';
MESS'!                                              !';
MESS'!     En ecrivant le principe des travaux      !';
MESS'!  virtuels,on montre que le deplacement delta !';
MESS'!  en chaque noeud est egal, dans le cas d un  !';
MESS'!  essai de traction uniaxial, a :             !';
MESS'!                       F                      !';
MESS'!        delta = ----------------              !';
MESS'!                   k * L * l                  !';
MESS'!  ou                                          !';
MESS'!    F = force totale exercee sur la structure !';
MESS'!    k = raideur                               !';
MESS'!    L = longueur de l element joint           !';
MESS'!    l = largeur de l element joint            !';
MESS'!                                              !';
MESS'!  Application numerique :                     !';
MESS'!                                              !';
MESS'!    F = 100000.0                              !';
MESS'!    k = 4.2E10                                !';
MESS'!    L = 2.0                                   !';
MESS'!    l = 1.0                                   !';
MESS'!                                              !';
MESS'!    Delta   =  100000 / (4.2E10 * 2.0 * 1.0)  !';
MESS'!            =  1.19047619E-6                  !';
MESS'!                                              !';
MESS'!==============================================!';
OPTION DIME 2 ;
OPTION ELEM SEG2 MODE PLAN CONT ;
SOLANA = 1.190476E-6 ;
SOLNUL = 0.0 ;
* ------- DEFINITION DE LA SURFACE TOP DU JOINT -------
A1 = 0.00 0.00 ;
B1 = 2.00 0.00 ;
* ---------- MAILLAGE ----------
H1 = A1 DROIT 1 B1 ;
L1 = H1 ;
* ------ DEFINITION DE LA SURFACE BOT DU JOINT --------
IA1 = 0.00 0.00 ;
IB1 = 2.00 0.00 ;
* ---------- MAILLAGE ----------
IH1 = IA1 DROIT 1 IB1 ;
IL1 = IH1 ;
* ---------- CREATION DU JOINT JOI2 ----------
OPTION ELEM RAC2 ;
VOL = RACCORD 0.00001 L1 IL1 ;
* --------- DEFINITION DES CONDITIONS LIMITES ---------
CL11 = BLOQ IA1 UX ;
CL12 = BLOQ IA1 UY ;
CL1 = CL11 ET CL12 ;
CL21 = BLOQ IB1 UX ;
CL22 = BLOQ IB1 UY ;
CL2 = CL21 ET CL22 ;
CL = CL1 ET CL2 ;
* ----- DEFINITION DU MODELE DU JOINT ---------
MOD1 =MODE VOL 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' JOI2;
MA1 = MATE MOD1 KS 4.2E08 KN 4.2E10 ;
* ------------- MATRICE DE HOOK ------------
HOO1 = HOOKE MOD1 MA1 ;
* LIST HOO1 ;
* ---------- MATRICE DE RIGIDITE ---------
* RI1 = RIGI MOD1 MA1 ;
RI1 = RIGI MOD1 HOO1 ;
RI2 = RI1 ET CL ;
* ---------- FORCE DE TRACTION ---------
FO1 = FORCE ( 0. 100000.0 ) L1 ;
* --------- RESOLUTION ----------
RE = RESO RI2 FO1 ;
MESS '                                              ' ;
MESS '                                              ' ;
MESS ' Solution Analytique :' ;
MESS '                                              ' ;
MESS '    UX =' SOLNUL ;
MESS '    UY =' SOLANA ;
MESS '                                              ' ;
MESS '                                              ' ;
MESS '                                              ' ;
MESS ' Solution Calculee :' ;
MESS '                                              ' ;
LIST RE ;
* ---------- CODE DE FONCTIONNEMENT ----------
DEPA1 = EXTR RE UY A1 ;
RESI = ABS( (DEPA1-SOLANA)/SOLANA ) ;
SI (RESI <EG 1E-4 ) ;
   ERRE 0 ;
SINO;
   ERRE 5 ;
FINSI ;
* ---------- CALCUL DES DEFORMATIONS ----------
EPS1 = EPSI MOD1 RE ;
LIST EPS1 ;
* ---------- CALCUL DES CONTRAINTES ----------
SIG1 = SIGMA MOD1 MA1 RE ;
LIST SIG1 ;
FIN ;
```

## ktest_lump_dkt [Mecanique Elastique]
```
* ktest pour tester l'opérateur LUMP
* elem DKT3
graph = faux;
ep1 = 1. ;
exc1 = 0.5 ;
a1 = 8 ** 0.5 ;
b1 = 18 ** 0.5 ;
ro1 = 5.d0 ;
'OPTI' 'ECHO' 0 ;
'OPTI' 'DIME' 3 'ELEM' 'SEG2' ;
P1 = -1. 1. 1. ;
P2 = 1. -1. 1. ;
P3 = 3. 3. 1. ;
* cote du triangle
* ==== TRI3
m_el1 = 'MANU' 'TRI3' P1 P2 P3 ;
mo_el1 = 'MODE' m_el1 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' 'DKT';
ma_el1 = 'MATE' mo_el1 'YOUN' 7.d0 'NU' 0.1 'RHO' ro1 'EPAI' ep1
          'EXCE' 0. ;
mas_el1 = 'LUMP' mo_el1 ma_el1 ;
* on teste les valeurs propres de la matrice
RESO mas_el1 ;
n1 = 'DIMN' mas_el1 ;
n2 = 'DIAG' mas_el1 ;
'MESS' 'Dimension du noyau' n1 ;
'MESS' 'Valeur propres négatives' n2 ;
err1 = ( n1 'NEG' 0 ) 'OU' ( n2 'NEG' 0 ) ;
ma_el1 = 'MATE' mo_el1 'YOUN' 7.d0 'NU' 0.1 'RHO' ro1 'EPAI' ep1
          'EXCE' exc1 ;
mas_el1 = 'LUMP' mo_el1 ma_el1 ;
* on teste les valeurs propres de la matrice
RESO mas_el1 ;
n1 = 'DIMN' mas_el1 ;
n2 = 'DIAG' mas_el1 ;
'MESS' 'Dimension du noyau' n1 ;
'MESS' 'Valeur propres négatives' n2 ;
err11 = ( n1 'NEG' 0 ) 'OU' ( n2 'NEG' 0 ) ;
* test sur le calcul de la taille de l'élément
* calculé avec mesu et avec la massse
* cela revient à considerer la conservation de l'energie
* cinétique en translation
s_el1 = 'MESU' m_el1 ;
un1 = 'MANU' 'CHPO' m_el1 3 'UX' 1. 'UY' 1. 'UZ' 1.;
s2_el1 = ( 'XTMX' mas_el1 un1 ) '/' ep1 / ro1 / 3. ;
dif2 = 'ABS' (( s_el1 - s2_el1 ) / s2_el1 ) ;
* mess s2_el1 ;
err2 = dif2 '>EG' 1.d-6 ;
'MESS' 'Erreur relative' ( dif2 * 100 ) '%' ;
'SI' ( err1 'OU' err2 'OU' err11 ) ;
  'MESS' 'problème de conservation de la masse' ;
  'ERREUR' 5 ;
'FINSI' ;
* Conservation de l'energie cinétique en rotation
* rotation de la coque autour de (p1 p2)
x1 = 'COOR' 1 m_el1 ;
x2 = 'COOR' 2 m_el1 ;
* mouvement suivant UZ
deu2 = ( 'MANU' 'CHPO' m_el1 6 'UX' 0. 'UY' 0. 'UZ' 0.
                 'RX' (2 ** -0.5 ) 'RY' (2 ** -0.5 * -.1 ) 'RZ' 0. )
       '+' ( 'NOMC' ( x1 + x2 / ( 2 ** 0.5) ) 'UZ' ) ;
deu2 = ( 'MANU' 'CHPO' m_el1 6 'UX' 0. 'UY' 0. 'UZ' 0.
                 'RX' 0. 'RY' 0. 'RZ' 0. )
       '+' ( 'NOMC' ( x1 + x2 / ( 2 ** 0.5) ) 'UZ' ) ;
mv_el1 = ( 'XTMX' mas_el1 deu2 ) ;
* energie cinétique de translation suivant z
* theorie a * b^3 / 12 * ep1 *rho
* a = 8^0.5 b = 8^0.5 pour l'energie de translation suivant UZ
mvtheo = ( a1 * ( b1 ** 3. ) / 12. * ep1 * ro1 ) ;
* energie cinétique de transaltion selon le plan de la coque
* on peut aussi considérer l'énergie de rotation des fibres
* c'est à dire le mouvement suivant UX et UY induit par la rotation
* on ne tient compte que de l'excentrement
mvtheo2 = mvtheo + ( ro1 * ep1 * ( exc1 ** 2. ) * a1 * b1 / 2.) ;
mvtheo3 = mvtheo2 + ( ro1 * ep1 * ( ep1 ** 2. / 12 )
* a1 * b1 / 2.) ;
'MESS' 'Qte de mvt :' mv_el1 ' Théorique' mvtheo
'Avec inertie' mvtheo2 ;
* ======= on augmente le nombre d'éléments
nelem = 100 ;
l1 = d p1 nelem p2 ;
l2 = d p2 nelem p3 ;
l3 = d p3 nelem p1 ;
su1 = 'SURF' 'PLAN' ( l1 et l2 et l3 ) ;
mo_el1 = 'MODE' su1 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' 'DKT';
ma_el1 = 'MATE' mo_el1 'YOUN' 7.d0 'NU' 0.1 'RHO' ro1 'EPAI' ep1
          'EXCE' exc1 ;
mas_el1 = 'LUMP' mo_el1 ma_el1 ;
* mas_el1 = 'MASS' mo_el1 ma_el1 ;
* rotation de la coque autour de (p1 p2)
x1 = 'COOR' 1 su1 ;
x2 = 'COOR' 2 su1 ;
* mouvement suivant UZ
deu2 = ( 'MANU' 'CHPO' su1 6 'UX' 0. 'UY' 0. 'UZ' 0.
                 'RX' (2 ** -0.5) 'RY' (2 ** -0.5 * -.1 ) 'RZ' 0. )
       '+' ( 'NOMC' ( x1 + x2 / ( 2 ** 0.5) ) 'UZ' ) ;
mv_el1 = ( 'XTMX' mas_el1 deu2 ) ;
'MESS' 'Qte de mvt :' mv_el1 ' Théorique' mvtheo
'Avec inertie' mvtheo2 ;
dif3 = mv_el1 - mvtheo2 / mvtheo2 ;
err3 = dif3 '>EG' 1.d-1 ;
'MESS' 'Erreur relative' ( dif3 * 100 ) '%' ;
'SI' ( err3 ) ;
  'MESS' 'problème de conservation de la masse en rotation' ;
  'ERREUR' 5 ;
'FINSI' ;
* test sur les fréquences propres
ro1 = 5. ;
'OPTI' 'DIME' 3 'ELEM' 'SEG2' ;
P1 = -1. 1. 1. ;
P2 = 1. -1. 1. ;
p3 = 1. 1. 1. ;
a1 = 2. ** 0.5 * 2 ;
b1 = 2. ** 0.5 ;
ep1 = 0.01 ;
you1 = 7. ;
nelem = 9 ;
l1 = d p1 nelem p2 ;
l2 = d p2 nelem p3 ;
l3 = d p3 nelem p1 ;
su1 = 'SURF' 'PLAN' ( l1 et l2 et l3 ) ;
mo_el1 = 'MODE' su1 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' 'DKT';
ma_el1 = 'MATE' mo_el1 'YOUN' you1 'NU' 0.3 'RHO' ro1 'EPAI' ep1 ;
rig1 = 'RIGI' mo_el1 ma_el1 ;
cl1 = 'BLOQ' ( l1 et l2 et l3 ) DEPL ROTA ;
* theorie Dr Robert Blevins
* Formulas for natural frequency and mode shape
* Van Nostrand Rheinhold Company
* p280
fith1 = 1. / 2. / pi / b1 / b1 * ( ( ep1 ** 2. * you1 / 12. / ro1
          / ( 1. - 0.09 ) ) ** 0.5 ) ;
mas_el1 = 'LUMP' mo_el1 ma_el1 ;
tab1a = 'VIBR' 'INTERVALLE' ( 10. * fith1 ) ( 100. * fith1 )
        ( rig1 et cl1 ) mas_el1
       'BASSE' 1 ;
fex1 = tab1a . 'MODES' . 1 . 'FREQUENCE' ;
def1a = defo su1 ( tab1a . modes . 1 . deformee_modale ) 0.5 bleu ;
* avec la masse consistante
mas_el1 = 'MASS' mo_el1 ma_el1 ;
tab1b = 'VIBR' 'INTERVALLE' (10. * fith1) ( 100. * fith1 )
        ( rig1 et cl1 ) mas_el1
       'BASSE' 1 ;
fex1b = tab1b . 'MODES' . 1 . 'FREQUENCE' ;
def1b = defo su1 ( tab1b . modes . 1 . deformee_modale ) 0.5 jaune ;
'MESS' 'Calcul de la 1 ere frequence propre' ;
'MESS' 'Lump : ' ( fex1 / fith1 ) 'Mass :' ( fex1b / fith1 )
 'theo ' 46,8 ;
dif5 = 'ABS' ( fex1 / fith1 - 46.8 / 46.8 ) ;
'MESS' 'Erreur relative ' ( dif5 * 100. ) '%' ;
err5 = dif5 '>EG' 0.05 ;
si graph ;
'TRAC' ( def1a et def1b ) ;
finsi;
'SI' ( err5 ) ;
  'MESS' 'problème du calcul de la frequence propre' ;
  'ERREUR' 5 ;
'FINSI' ;
'MESS' 'DKT test positif' ;
'FIN' ;
```

## phasage [Mecanique Elastique]
```
complet=vrai;
opti dime 3 elem cu20 mode trid;
am=-1; bm = -0.5; cm=-0.275;cp=0.275;bp=0.5;ap=1.;
* nca2=10;nca=nca2*2;nd1=2; nd2=4;
si complet ;
nca2=5;nca=nca2*2;nd1=1; nd2=2;
sinon;
nca2=4;nca=nca2*2;nd1=1; nd2=2;
finsi;
pa = am am 20;pb=bm am 20; pc= cm am 20; pd = cp am 20;
pe= bp am 20; pf = ap am 20;
liba = pa droi nd1 pb droi nd1 pc droi nd2 pd droi nd1 pe droi nd1 pf;
su = liba tran nd1 ( 0 bp 0) trans nd1 ( 0 0.225 0.) trans nd2 (0 0.55 0) tran nd1 ( 0 0.225 0) tran nd1 ( 0 BP 0);
* trac su;
vol1= su volu trans nca2 ( 0 0 -10);
 su2 = vol1 face 2;
 pceny = point su2 droite ( 0 0 10) ( 1 0 10) 0.51;
pcenxy = point pceny droite ( 0 0 10) ( 0 1 10) 0.51;
su21= elem su2 appu strict pcenxy coul rouge;
* trac ( su2 et su21);
vol2 = su21 volu trans nca2 (0 0 -10.);
su3 = vol2 face 2;
voltot = vol1 et vol2;
* trac voltot;
pc1d = cm cp 0.; pc1f = cm cp 20;
cab1 = pc1d droi nca pc1f chan seg2;
pc2d = cp cm 0.; pc2f = cp cm 20;
cab2 = pc2d droi nca pc2f chan seg2;
pc3d = cp cp 0.; pc3f = cp cp 20;
cab3 = pc3d droi nca pc3f chan seg2;
pc4d = cm cm 0.; pc4f = cm cm 20;
cab4 = pc4d droi nca pc4f chan seg2;
pc5d = 0 0 0.; pc5f = 0 0 20;
cab5 = pc5d droi nca pc5f chan seg2;
cable= cab1 et cab2 et cab3 et cab4 et cab5 coul bleu;
fer= cable plus (0 0 0 );
list ( nbno cable);
* elim voltot cable 0.01;
* trac ( vol2 et cable);
* description des modeles
mobet1 = model vol1 mecanique elastique;
mobet2 = model vol2 mecanique elastique;
mobeton = mobet1 et mobet2;
mocab1= model cab1 mecanique elastique barr;
mocab2= model cab2 mecanique elastique barr;
mocab3= model cab3 mecanique elastique barr;
mocab4= model cab4 mecanique elastique barr;
mocab5= model cab5 mecanique elastique barr;
mofer = model fer mecanique elastique barr;
* description des materiaux et sections
mabet1= mate mobet1 young 40000e6 nu 0.2 rho 2500.;
mabet2= mate mobet2 young 40000e6 nu 0.2 rho 2500.;
mabeton = mabet1 et mabet2;
macab1= mate mocab1 young 193000e6 nu 0.3 rho 7859 sect 0.0025;
macab2= mate mocab2 young 193000e6 nu 0.3 rho 7859 sect 0.0025;
macab3= mate mocab3 young 193000e6 nu 0.3 rho 7859 sect 0.0025;
macab4= mate mocab4 young 193000e6 nu 0.3 rho 7859 sect 0.0025;
macab5= mate mocab5 young 193000e6 nu 0.3 rho 7859 sect 0.0025;
mafer = mate mofer young 100000e6 nu 0.3 rho 7859 sect 0.00001;
* condition aux limites de deplacement
pp= point voltot droite (0 0 0 )( 0 0 20) 0.01;
blxy = bloqu 'UX' 'UY' pp;
px= point su3 proche (0.5 0 0 );
bly = bloqu 'UY' px;
blz = bloqu 'UZ' su3;
claccr = rela accro fer voltot 0.01;
cltot = blxy et bly et blz et claccr;
* chargement du au poids
gamma = -9.81;
mmas = masse mobeton mabeton;
vz = manu chpo voltot 1 'UZ' gamma;
fpoi= mmas * vz;
evpoi = evol manu 'TEMPS' (prog 0. 10000.) 'COEF' (PROG 1. 1.);
charpoid= chargement fpoi evpoi;
* description des caracteristioques generales pour les pertes quasi instantanee
coefprec=table;
coefprec . 'FF' = 0.16 ;
coefprec . 'PHIF' = 0.0015;
coefprec . 'GANC' = 0.012;
coefprec . 'RMU0' = 0.45 ;
coefprec . 'FPRG' = 1940.e6 ;
coefprec . 'RH10' = 2.3;
* creation de la table des etapes pour le cas 2 il n'y a q'une etape
cas3etap=table;
cas2=table;
cas3etap . 1 = cas2 ;
cas2 . 'TPS' = 300. ;
* premier groupe
group1_1 = table;
cas2 . 1 = group1_1 ;
group1_1 . 'GEOMETRIE1' = manu poi1 pc2d;
group1_1 . 'MODELE' = mocab2;
group1_1 . 'MATERIAU' = macab2;
group1_1 . 'FORCE' = 3.75e6;
group1_1 . 'COEF_PREC' = coefprec;
group1_1 . 'TYPE_CAB' = '1EXT';
group1_2= table;
cas2 . 2 = group1_2 ;
group1_2 . 'GEOMETRIE1' = manu poi1 pc1d;
group1_2 . 'MODELE' = mocab1;
group1_2 . 'MATERIAU' = macab1;
group1_2 . 'FORCE' = 3.75e6;
group1_2 . 'COEF_PREC' = coefprec;
group1_2 . 'TYPE_CAB' = '1EXT';
* deuxieme groupe
si complet;
cas3=table;
cas3etap . 2 = cas3;
cas3.'TPS'= 450.;
gr31=table;
cas3 . 1 = gr31;
gr31. 'GEOMETRIE1' = manu poi1 pc3d ;
gr31. 'MODELE' = mocab3;
gr31. 'MATERIAU' = macab3;
gr31. 'FORCE' = 3.75e6;
gr31. 'COEF_PREC' = coefprec;
gr31. 'TYPE_CAB' = '1EXT';
gr32=table;
cas3 . 2 = gr32;
gr32. 'GEOMETRIE1' = manu poi1 pc4d ;
gr32. 'MODELE' = mocab4;
gr32. 'MATERIAU' = macab4;
gr32. 'FORCE' = 3.75e6;
gr32. 'COEF_PREC' = coefprec;
gr32. 'TYPE_CAB' = '1EXT';
* troisieme groupe
cas4=table;
cas3etap . 3 = cas4;
cas4.'TPS'= 600.;
gr41=table;
cas4 . 1 = gr41;
gr41. 'GEOMETRIE1' = manu poi1 pc5d ;
gr41. 'GEOMETRIE2' = manu poi1 pc5f ;
gr41. 'MODELE' = mocab5;
gr41. 'MATERIAU' = macab5;
gr41. 'FORCE' = 3.75e6;
gr41. 'COEF_PREC' = coefprec;
gr41. 'TYPE_CAB' = '2EXT';
finsi;
* appel a la procedur tension
cas3etap = tension cas3etap;
* donnees relatives au levee
tlev = table;tlev1=table;tlev2=table;
tlev . 1 = tlev1;tlev . 2 = tlev2;
tlev1.'INSTANT' = 0.; tlev2.'INSTANT' = 150.;
tlev1.'MODELE' = mobet1;tlev2.'MODELE' = mobet2;
tlev1.'MATERIAU' = mabet1;tlev2.'MATERIAU' = mabet2;
tlev1.'COEF1'=70.;tlev2.'COEF1'=70.;
tlev1.'COEF2'= MANU CHML mobet1 'TAUX' 9.e-3 'STRESSES';
tlev2.'COEF2'= MANU CHML mobet2 'TAUX' 9.e-3 'STRESSES';
raysec1 = manu chml mobet1 'EPAI' 50. 'STRESSES';
raysec2 = manu chml mobet2 'EPAI' 100. 'STRESSES';
raysec = raysec1 et raysec2;
tlev1.'SECHAGE' = raysec1;tlev2.'SECHAGE' = raysec2;
* appel a phasage
tphas= table;
tphas.'FLUAGE' = 'BPEL99';
tphas.'RETRAIT' = 'BPEL99';
tphas.'PRECONTRAINTE'= cas3etap;
tphas.'LEVEES'= tlev;
tphas. 'TEMPS_FINAL' = 3000.;
tphas.'BLOCAGES' = cltot;
tphas.'DEPOU'= vrai;
tphas.'MOD_RESTE' = mofer;
tphas.'MAT_RESTE' = mafer;
* option debug ;
* option echo 2;
tphas = phasage TPHAS;
* opti sauv 'complet.res';
* sauv tphas;
* fin;
tsui = tphas.table_suite;
ttem= tsui.temps;
tdep= tsui.deplacements;
tcon= tsui.contraintes;
na = (dime ttem) - 1;
maxdepz= maxi( abs (exco tdep . na UZ));
maxcoz=maxi ( abs ( exco tcon . na SMZZ));
si complet;
message ' calcul complet = vrai';
verdep=1.1017; vericont=1.86069e+07;
sinon ;message ' calcul complet = faux';
verdep= 1.0949 ; vericont= 8.37572e+06;
finsi;
mess ' deplacemment en Z maxi ' maxdepz ' comparé à ' verdep;
mess ' contrainte en Z maxi ' maxcoz ' comparée à ' vericont;
erdep= abs((maxdepz - verdep) / verdep );
ercont = abs ((maxcoz - vericont) / vericont);
si ( erdep > 0.001) ;
   mess ' erreur deplacement ' erdep ' comparé à 0.001';
   erreur 5;
finsi;
si ( ercont > 0.001 );
   mess ' errreur contrainte ' ercont ' comparé à 0.001';
   erreur 5;
finsi;
fin;
```

## testjoi1orth [Mecanique Elastique]
```
opti elem seg2 dime 3 mode trid;
* SOLUTION ANALYTIQUE
      UXANA = 0.007;
      UYANA = -83.5455;
      UZANA = 0.00;
      RXANA = 0.00;
      RYANA = 0.00;
      RZANA = -4.175625;
* CREATION DES POUTRES
* PROPRIETES GEOMETRIQUES
l1=10.;
lt=30.;
torp = 5;
iyp = 3;
izp = 4;
secp = 0.2;
* PROPRIETES MATERIELLES
youp = 32;
nup = 0.2;
dir1 = 0 1 0;
dir2 = 1 0 0;
* POUTRE GAUCHE
pi1 = 0 0 0;
pi2 = l1 0 0;
li = pi1 d 1 pi2;
* POUTRE DROITE
ps1 = l1 0 0;
ps2 = lt 0 0;
ls = ps1 d 1 ps2;
lt = ls et li;
* trac lt;
mop = mode lt mecanique elastique poutre;
map = mate mop YOUN youp NU nup
           TORS torp INRY iyp INRZ izp SECT secp;
* JOINT
lj = pi2 d 1 ps1;
moj = mode lj mecanique elastique orthotrope joi1;
maj = mate moj direction dir1 dir2
         KN 30 KS1 40 KS2 30 QN 40 QS1 20 QS2 30;
mo1 = moj et mop;
ma1 = maj et map;
cl1 = bloq depl rota pi1;
ri1 = rigi mo1 ma1;
ri2 = ri1 et cl1;
fo1 = force (0. -1. 0.) ps2;
res = reso ri2 fo1;
ss1 = sigma mo1 ma1 res 'LINEAIRE';
ee1 = epsi mo1 ma1 res 'LINEAIRE';
gr1 = grad mo1 ma1 res;
gf1 = graf mo1 ma1 res;
sss = elas mo1 ee1 ma1;
fi1 = bsig mo1 ss1 ma1;
* ---------- CODE DE FONCTIONNEMENT ----------
* opti donn 5;
DEPA1 = EXTR res UY ps2 ;
RESI = ABS( (DEPA1-UYANA)/UYANA ) ;
list resi;
SI (RESI <EG 3E-3 ) ;
  ERRE 0 ;
SINO;
   ERRE 5 ;
FINSI ;
FIN;
```

## test_AMITEX [Mecanique Elastique]
```
* 23456789123456789123456789123456789123456789123456789123456789123456789
* CAS TESTS POUR L'UTILISATION DES PROCEDURES D'APPLICATION DES
* CONDITIONS AUX LIMITES ET DE CALCUL DE COMPORTEMENT MOYEN
* CAS CONSIDERES :
* CAS HOMOGENE ANISOTROPE
* CAS "MATRICE/INCLUSION SPHERIQUE" SUR MAILLAGE REGULIER
* L. GELEBART, DECEMBRE 2009
* PARAMETRES
NEL0 = 8;
NEL1 = 2;
VISU0 = 1;
* proprietes elastiques de l'inclusion et de la matrice
EI0 = 100.;
EM0 = 400.;
NUI0 = 0.3;
NUM0 = 0.1;
* Position et rayon de l'inclusion
DX0 = 0.3;
DY0 = 0.4;
DZ0 = 0.6;
R0 = 0.25;
E0 = 0.1;
* Chargement
CTAB = TABLE;
CTAB . 1 = 1.; CTAB . 2 = 2.; CTAB . 3 = 3.;
CTAB . 4 = 4.; CTAB . 5 = 5.; CTAB . 6 = 6.;
* Tolerance sur les tests
tol0 = 1e-9;
* GEOMETRIE ET MATERIAUX
* cas matrice/inclusion sur maillage regulier
OPTI DIME 3;
P1 = 0. 0. 0.;
P2 = 1. 0. 0.;
P3 = 1. 1. 0.;
P4 = 0. 1. 0.;
OPTI ELEM SEG2;
P1P2 = DROI P1 P2 NEL0;
P2P3 = DROI P2 P3 NEL0;
P3P4 = DROI P3 P4 NEL0;
P4P1 = DROI P4 P1 NEL0;
OPTI ELEM QUA4;
SURF0 = DALL P1P2 P2P3 P3P4 P4P1;
OPTI DIME 3 ELEM CUB8;;
VOL0 = SURF0 VOLU NEL0 TRANS (0. 0. 1.);
MODTOT0 = MODE VOL0 MECANIQUE ELASTIQUE;
UN0 = MANU CHML VOL0 SCAL 1.;
X0 = (COOR 1 VOL0) - DX0;
Y0 = (COOR 2 VOL0) - DY0;
Z0 = (COOR 3 VOL0) - DZ0;
DIST0 = ((X0 * X0 ) + (Y0 * Y0) + (Z0 * Z0)) ** 0.5;
DIST0 = CHAN CHAM DIST0 MODTOT0 RIGIDITE;
INCL0 = MASQUE DIST0 INFERIEUR R0;
MATR0 = MASQUE DIST0 SUPERIEUR R0;
YOUN0 = (EI0 * INCL0) + (EM0 * MATR0);
NU0 = (NUI0 * INCL0) + (NUM0 * MATR0);
MATTOT0 = MATE MODTOT0 YOUN YOUN0 NU NU0;
RIGMAT0 = RIGI MODTOT0 MATTOT0;
* cas homogene anisotrope
OPTI DIME 3;
P1 = 0. 0. 0.;
P2 = 1. 0. 0.;
P3 = 1. 1. 0.;
P4 = 0. 1. 0.;
OPTI ELEM SEG2;
P1P2 = DROI P1 P2 NEL1;
P2P3 = DROI P2 P3 NEL1;
P3P4 = DROI P3 P4 NEL1;
P4P1 = DROI P4 P1 NEL1;
OPTI ELEM QUA4;
SURF0 = DALL P1P2 P2P3 P3P4 P4P1;
OPTI DIME 3 ELEM CUB8;;
VOL1 = SURF0 VOLU NEL1 TRANS (0. 0. 1.);
DIR0 = POIN 1. 0. 0.;
DIR1 = POIN 0. 1. 0.;
MODTOT1 = MODE VOL1 MECANIQUE ELASTIQUE ANISOTROPE;
D110 = 123;
D210 = 45;
D220 = 678;
D310 = 91;
D320 = 23;
D330 = 456;
D410 = 10;
D420 = 11;
D430 = 12;
D440 = 222;
D510 = 2;
D520 = 4;
D530 = 6;
D540 = 8;
D550 = 777;
D610 = 10;
D620 = 14;
D630 = 16;
D640 = 18;
D650 = 13;
D660 = 321;
MATTOT1= MODTOT1 MATE DIRECTION DIR0 DIR1 PARALLELE D11 D110 D21 D210
D22 D220 D31 D310 D32 D320 D33 D330 D41 D410 D42 D420 D43 D430 D44
D440 D51 D510 D52 D520 D53 D530 D54 D540 D55 D550 D61 D610 D62
D620 D63 D630 D64 D640 D65 D650 D66 D660;
K0 = TABLE;
K0 . 1 = TABLE;
K0 . 1 . 1 = D110; K0 . 1 . 2 = D210; K0 . 1 . 3 = D310;
K0 . 1 . 4 = D410; K0 . 1 . 5 = D510; K0 . 1 . 6 = D610;
K0 . 2 = TABLE;
K0 . 2 . 1 = D210; K0 . 2 . 2 = D220; K0 . 2 . 3 = D320;
K0 . 2 . 4 = D420; K0 . 2 . 5 = D520; K0 . 2 . 6 = D620;
K0 . 3 = TABLE;
K0 . 3 . 1 = D310; K0 . 3 . 2 = D320; K0 . 3 . 3 = D330;
K0 . 3 . 4 = D430; K0 . 3 . 5 = D530; K0 . 3 . 6 = D630;
K0 . 4 = TABLE;
K0 . 4 . 1 = D410; K0 . 4 . 2 = D420; K0 . 4 . 3 = D430;
K0 . 4 . 4 = D440; K0 . 4 . 5 = D540; K0 . 4 . 6 = D640;
K0 . 5 = TABLE;
K0 . 5 . 1 = D510; K0 . 5 . 2 = D520; K0 . 5 . 3 = D530;
K0 . 5 . 4 = D540; K0 . 5 . 5 = D550; K0 . 5 . 6 = D650;
K0 . 6 = TABLE;
K0 . 6 . 1 = D610; K0 . 6 . 2 = D620; K0 . 6 . 3 = D630;
K0 . 6 . 4 = D640; K0 . 6 . 5 = D650; K0 . 6 . 6 = D660;
RIGMAT1 = RIGI MODTOT1 MATTOT1;
* VALIDATION DES CHARGEMENTS MOYENS IMPOSES
* SUR CAS TEST "MATRICE INCLUSION"
* Definition des chargements pour differents types de CL
RIGCL1 DEPI1 = @CLIM @CLPC VOL0 CTAB;
RIGCL2 DEPI2 = @CLIM @CLDHC VOL0 CTAB;
RIGCL3 DEPI3 = @CLIM @CLMI1C VOL0 CTAB;
RIGCL4 DEPI4 = @CLIM @CLMI2C VOL0 CTAB;
RIGCL5 DEPI5 = @CLIM @CLCH VOL0 CTAB;
RIGCL6 DEPI6 = @CLIM @CLPD VOL0 CTAB;
RIGCL7 DEPI7 = @CLIM @CLDH VOL0 CTAB;
* Resolution elastique
DEPT = TABLE;
DEPT . 1 = RESOU (RIGCL1 ET RIGMAT0) DEPI1;
DEPT . 2 = RESOU (RIGCL2 ET RIGMAT0) DEPI2;
DEPT . 3 = RESOU (RIGCL3 ET RIGMAT0) DEPI3;
DEPT . 4 = RESOU (RIGCL4 ET RIGMAT0) DEPI4;
DEPT . 5 = RESOU (RIGCL5 ET RIGMAT0) DEPI5;
DEPT . 6 = RESOU (RIGCL6 ET RIGMAT0) DEPI6;
DEPT . 7 = RESOU (RIGCL7 ET RIGMAT0) DEPI7;
* Validation
* pour les chargements en contrainte moyenne imposee
V0 = MESU VOL0;
i = 0;
REPETE BOU0 5;
i = i + 1;
SIG0 = SIGMA MODTOT0 MATTOT0 (DEPT . i) 'LINE';
SXX0 = (INTG SIG0 MODTOT0 SMXX) / V0;
SYY0 = (INTG SIG0 MODTOT0 SMYY) / V0;
SZZ0 = (INTG SIG0 MODTOT0 SMZZ) / V0;
SXY0 = (INTG SIG0 MODTOT0 SMXY) / V0;
SXZ0 = (INTG SIG0 MODTOT0 SMXZ) / V0;
SYZ0 = (INTG SIG0 MODTOT0 SMYZ) / V0;
* MESS SXX0;
* MESS SYY0;
* MESS SZZ0;
* MESS SXY0;
* MESS SXZ0;
* MESS SYZ0;
SI ((ABS (SXX0 - (CTAB . 1))) > tol0);ERRE 5;FINSI;
SI ((ABS (SYY0 - (CTAB . 2))) > tol0);ERRE 5;FINSI;
SI ((ABS (SZZ0 - (CTAB . 3))) > tol0);ERRE 5;FINSI;
SI ((ABS (SXY0 - (CTAB . 4))) > tol0);ERRE 5;FINSI;
SI ((ABS (SXZ0 - (CTAB . 5))) > tol0);ERRE 5;FINSI;
SI ((ABS (SYZ0 - (CTAB . 6))) > tol0);ERRE 5;FINSI;
FIN BOU0;
* Validation
* pour les chargements en deformation moyenne imposee
i = 5;
REPETE BOU0 2;
i = i + 1;
DEF0 = EPSI MODTOT0 MATTOT0 (DEPT . i) 'LINE' ;
EXX0 = (INTG DEF0 MODTOT0 EPXX) / V0;
EYY0 = (INTG DEF0 MODTOT0 EPYY) / V0;
EZZ0 = (INTG DEF0 MODTOT0 EPZZ) / V0;
EXY0 = (INTG DEF0 MODTOT0 GAXY) / (2 * V0);
EXZ0 = (INTG DEF0 MODTOT0 GAXZ) / (2 * V0);
EYZ0 = (INTG DEF0 MODTOT0 GAYZ) / (2 * V0);
* MESS EXX0;
* MESS EYY0;
* MESS EZZ0;
* MESS EXY0;
* MESS EXZ0;
* MESS EYZ0;
SI ((ABS (EXX0 - (CTAB . 1))) > tol0);ERRE 5;FINSI;
SI ((ABS (EYY0 - (CTAB . 2))) > tol0);ERRE 5;FINSI;
SI ((ABS (EZZ0 - (CTAB . 3))) > tol0);ERRE 5;FINSI;
SI ((ABS (EXY0 - (CTAB . 4))) > tol0);ERRE 5;FINSI;
SI ((ABS (EXZ0 - (CTAB . 5))) > tol0);ERRE 5;FINSI;
SI ((ABS (EYZ0 - (CTAB . 6))) > tol0);ERRE 5;FINSI;
FIN BOU0;
* VALIDATION DU CALCUL DE COMPOTEMENT MOYEN
* SUR CAS TEST HOMOGENE ANISOTROPE
VISU1 = TABLE;
VISU1 . 1 = 0;
VISU1 . 2 = 0;
VISU1 . 3 = 0;
CONV0 = 0;
AMPL0 = 1.;
TK = TABLE;
TK . 1 = TABLE;
TK . 2 = TABLE;
TK . 3 = TABLE;
TK . 4 = TABLE;
TK . 5 = TABLE;
TK . 6 = TABLE;
TK . 7 = TABLE;
K C D = @KEFF MODTOT1 MATTOT1 @CLPC AMPL0 CONV0 VISU1;
TK . 1 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLPD AMPL0 CONV0 VISU1;
TK . 2 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLDH AMPL0 CONV0 VISU1;
TK . 3 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLDHC AMPL0 CONV0 VISU1;
TK . 4 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLCH AMPL0 CONV0 VISU1;
TK . 5 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLMI1C AMPL0 CONV0 VISU1;
TK . 6 = K;
K C D = @KEFF MODTOT1 MATTOT1 @CLMI2C AMPL0 CONV0 VISU1;
TK . 7 = K;
ERR_K = 0;
i=0;
REPETE BOU0 7;
i = i + 1;
j = 0;
REPETE BOUJ0 6;
j = j + 1;
k = 0;
REPETE BOUK0 6;
k = k + 1;
ERR_K = ERR_K + (abs ((K0 . j . k) - (TK . i . j . k)));
FIN BOUK0;
FIN BOUJ0;
MESS 'ERR_K = ' ERR_K;
SI (ERR_K > tol0); ERRE 5; FINSI;
ERR_K = 0;
FIN BOU0;
* Raouter les comparaison pilotage C et D pour DH et P
FIN;
```

## visucoq [Mecanique Elastique]
```
* Exemple d'utilisation de coq2mas
* Visualisation 3D de résultats de calcul coque multicouche
* D. Combescure - Juillet 2007
* Laboratoire DYN - CEA Saclay
* FLAGVISU = VRAI;
* FLAGLONG = VRAI;
FLAGVISU = FAUX;
* FLAGLONG = FAUX;
opti dime 3 elem tri3;
R = 10.;
H = -1.;
ep1 = 1.0;
ep2 = 0.20;
p1 = R 0. 0.;
p2 = 0. R 0.;
p3 = ((-1.)*R) 0. 0.;
p4 = 0. ((-1.)*R) 0.;
p0 = 0. 0. H;
p0b = 0. 0. (-2.*H);
n1 = 20;
lig0 = (CER3 n1 p1 p2 p3)
    ET (CER3 n1 p3 p4 p1);
sur0 = SURF lig0 SPHE p0;
sur0b = SURF lig0 SPHE p0b;
mod1 = MODE sur0 mecanique elastique dkt cons 'Couche 1';
mat1 = MATE mod1 YOUN 30000.D6 NU 0.25 RHO 2400.
                  EPAI ep1 EXCE (1.*ep1);
mod2 = MODE sur0 mecanique elastique dkt cons 'Couche 2';
mat2 = MATE mod2 YOUN 30000.D6 NU 0.25 RHO 2400.
                  EPAI ep1 EXCE ((-1.)*ep1);
mod3 = MODE sur0 mecanique elastique dkt cons 'Couche 3';
mat3 = MATE mod3 YOUN 30000.D6 NU 0.25 RHO 2400.
                  EPAI ep1 ;
mod4 = MODE sur0b mecanique elastique dkt cons 'Couche 4';
mat4 = MATE mod4 YOUN 30000.D6 NU 0.25 RHO 2400.
                  EPAI ep2 ;
modtot = mod1 et mod2 et mod3 et mod4;
mattot = mat1 et mat2 et mat3 et mat4;
rigtot = rigi modtot mattot;
mastot = mass modtot mattot;
tabtot = table;
mesh3D = coq2mas modtot mattot tabtot;
SI FLAGVISU;
 trac (sur0 et sur0b) cach;
 trac mesh3D cach;
FINSI;
load = mastot * (manu chpo (sur0 et sur0b) 1 UZ -9.81);
bl0 = bloq depl lig0;
DEPJ = RESO (RIGTOT et BL0) load;
CONJ = SIGMA DEPJ MODTOT MATTOT;
TABTOT. 'DEPLACEMENTS' = TABLE;
TABTOT. 'DEPLACEMENTS' . 1 = DEPJ;
TABTOT. 'CONTRAINTES' = TABLE;
TABTOT. 'CONTRAINTES' . 1 = CONJ;
MESH3D = COQ2MAS MODTOT MATTOT TABTOT;
SI FLAGVISU;
 dep3D = (TABTOT.'DEPLACEMENTS_VOLUMIQUE'. 1 . TOTAL);
 trac (defo mesh3D dep3D) cach;
 mesh3Df = TABTOT.'MAILLAGE_FIBRE_MOYENNE' . TOTAL;
 con3Df = EXCO (TABTOT.'CONTRAINTES_FIBRE_MOYENNE'. 1 . TOTAL)
          SMXX;
 trac mesh3Df con3Df cach;
 mesh3D = TABTOT.'MAILLAGE_VOLUMIQUE' . TOTAL;
 con3D = EXCO (TABTOT.'CONTRAINTES_VOLUMIQUE'. 1 . TOTAL)
          SMXX;
 trac mesh3D con3D cach;
* Pour relecture avec PARAVIEW
 opti sort 'visucoq.inp';
 sort avs mesh3D (TABTOT.'CONTRAINTES_VOLUMIQUE'. 1 . TOTAL);
FINSI;
FIN;
```

## vsur3 [Mecanique Elastique]
```
* vsur3.dgibi : Test de VSUR en coq6 et coq8
opti echo 0 dime 3 elem qua8;
* Définition de la géométrie
p0 = 0. 0. 0.;
p1 = 9. 0. 6.;
p2 = 7. 6. 10.;
p3 = -2. 6. 4.;
p4 = 8. 3. 8.;
p5 = -1. 3. 2.;
l1 = D 3 p0 p1;
l2 = D 2 p1 p2;
l3 = D 5 p2 p3;
l4 = D 4 p3 p0;
cn1 = l1 et l2 et l3 et l4;
obj = SURF cn1 'PLANE';
* Définition des modèles
obj6 = obj elem 'TRI6';
obj8 = obj elem 'QUA8';
mo6 = modeli obj6 mecanique elastique isotrope coq6;
mo8 = modeli obj8 mecanique elastique isotrope coq8;
mod1 = mo6 et mo8;
* Comparaison des champs obtenus par VSUR
* Premier modèle : coq6 et coq8
che1 = VSUR mod1;
chn1 = VSUR mod1 'NORM';
chj1 = JACO mod1;
cnx1 = exco 'VX' che1 'SCAL';
cny1 = exco 'VY' che1 'SCAL';
cnz1 = exco 'VZ' che1 'SCAL';
cnn1 = (cnx1*cnx1) + (cny1*cny1) + (cnz1*cnz1);
cjn1 = chj1*chj1;
cze1 = cnn1 - cjn1;
* list cze1;
cnx1 = exco 'VX' chn1 'SCAL';
cny1 = exco 'VY' chn1 'SCAL';
cnz1 = exco 'VZ' chn1 'SCAL';
cnn1 = (cnx1*cnx1) + (cny1*cny1) + (cnz1*cnz1);
* list cnn1;
CPZ1 = CHAN CHPO MOD1 CZE1;
CPN1 = CHAN CHPO MOD1 CNN1;
RE11 = MAXI CPZ1 'ABS';
RE12 = (MAXI CPN1 'ABS') - 1.;
RE13 = (MAXI CPN1 'ABS') - (MINI CPN1 'ABS');
RES1 = RE11 + RE12 + RE13;
SI (res1 < 1.e-6) ;
  MESS 'OPERATEUR <VSUR> ERR  0';
  ERRE 0;
SINON;
  MESS 'OPERATEUR <VSUR> ERR  5';
  ERRE 5;
FINSI;
fin;
```

## weib [Mecanique Elastique]
```
opti echo 0;
* TRAVE CARICATA PER FLESSIONE A QUATTRO PUNTI ; DETERMINAZIONE
* DELLA PROBABILITA' DI ROTTURA SECONDO LA STATISTICA DI WEIBULL:
* CARATTERISTICHE GEOMETRICHE DELLA TRAVE
TITRE 'TRAVE CARICATA PER FLESSIONE A QUATTRO PUNTI';
OPTION DIME 2 ELEM QUA8;
L1= 4.5e1 ; comm 'lunghezza trave' ;
D1= 4.0e1 ; comm 'distanza tra gli appoggi' ;
D2= 2.0e1 ; comm 'distanza tra i carichi' ;
H = 3.0 ; comm 'altezza trave' ;
S = 4.0 ; comm 'spessore trave' ;
* CARICO PER UNITA' DI SPESSORE ED AGENTE SU META' TRAVE
PP1= -1.05E+2 ;
* CARATTERISTICHE DEL MATERIALE
YO1= 3.0e+5 ;
NU1= .23 ;
* VALORI DEL MODULO DI WEIBULL E DELLA SIGMA-ZERO
* DETERMINATI A PARTIRE DA UN SET DI PROVE SPERIMENTALI
* dati sperimentali
 lis1 = prog
 427.9555 852.2001 800.0194 445.7708 740.6716 827.7161 827.3882 590.6464
 750.3228 746.3323 446.1818 875.4909 630.5025 604.9180 648.6437 832.6529
 648.8641 785.7595 754.6536 697.0067 904.4279 807.3849 717.4614 690.0081
 600.4105 742.2141 893.2710 795.1147 697.7165 798.2668 ;
* determinazione dei parametri statistici
MESS '========================================';
MESS '==       WEIBULL STATISTICS           ==';
MESS '========================================';
 EW1 SU1 = weip lis1 40. 20. (3. * 4.) ;
MESS '========================================';
MESS ' Weibull modulus : ' EW1 ;
MESS ' Sigma zero      : ' SU1 ;
MESS '========================================';
* VALORI DELLA TENSIONE DI RIFER. E DEL FATTORE D'INTEGRAZIONE
SMR1= 0. ; comm 'nulla per materiali ceramici' ;
V0 = 2.0 * S ; comm '1 condizione di simmetria + spessore' ;
A0= 0. 0.;
A1= ((L1-D1)/2.) 0. ;
A2= (L1/2.) 0. ;
A3= ((L1-D2)/2.) 0. ;
p3= ((L1-D2)/2.) h ;
V1= 0. H ;
P2= (L1/2.) H ;
AT1= D 5 A0 A1 D 40 A2;
S1=AT1 TRAN 6 V1 ;
CT2= COTE 2 S1 ;
P3= S1 POINT PROC P3 ;
TASS S1;
* FORMULAZIONE
OPTION MODE PLAN CONT ;
OBJ= MODE S1 MECANIQUE ELASTIQUE QUA8;
* MATERIALE
MAT1=MATE OBJ YOUN YO1 NU NU1 ;
* RIGIDEZZA E VINCOLI
ENC1= BLOQUE UY A1 ;
ENC2= SYMT DEPL A2 P2 S1 0.0001;
RIG1= RIGI MAT1 OBJ;
RIGT =RIG1 ET ENC1 ET ENC2;
* CARICHI
FP3= FORC FY PP1 P3 ;
* RISOLUZIONE
DE1 =RESOU RIGT FP3 ;
* CAMPO DI TENSIONI
SE1 = SIGMA DE1 OBJ MAT1 ;
* STATEMENT DI RICHIAMO DELLA PROCEDURA 'WEIBULL'
PROT1 CHEL2 = WEIBULL SE1 OBJ V0 SMR1 SU1 EW1;
PROS = 1. - PROT1;
MESS '========================================';
MESS 'PROBAB. DI SOPRAVVIVENZA:' PROS ;
MESS 'PROBAB. DI ROTTURA      :' PROT1 ;
MESS '========================================';
MESS ' ';
pr2 = pros * 100. ;
ERR1 = ABS (100 * ( 60.20 - pr2 ) / 60.20 ) ;
MESS '========================================';
MESS '==       SURVIVAL PROBABILITY         ==';
MESS '========================================';
MESS ' SOLUTION ANALYTIQUE     60.20           %  ';
MESS ' SOLUTION CALCULEE     'pr2 '  %  ';
MESS ' ERREUR DE             'ERR1 '  %  ';
MESS '========================================';
SI (ERR1 < 5 );
  ERRE 0;
SINON;
  ERRE 5;
FINSI;
FIN;
```

## gdep5 [Mecanique Elastique Grands_deplacements]
```
* Description :
* Traction simple en deplacement impose.
* Eprouvette en forme de pave droit, 3 elements
* Calcul lineaire elastique en Grands deplacements,
* option Lagrangien Reactualise.
* Validation :
* La courbe contrainte-deformation issue du calcul doit etre egale a
* celle fourunie dans les caracteristiques du modele.
* Options generales
OPTI 'DIME' 3 'ELEM' 'CUB8' ;
* Mettre igraph a VRAI pour visualiser
igraph = faux ;
* Courbe de traction conventionnelle
ym1 = 210.e9 ;
nu1 = 0.3 ;
ht1 = 1.e9 ;
lec = PROG 0. 2.e-3 0.2 ;
lsc = prog 0. (ym1*2.e-3) ((0.2-2.e-3)*ht1+(ym1*2.e-3)) ;
cc = EVOL 'TURQ' 'MANU' lec lsc ;
* Courbe de traction rationnelle
ler = LOG (1. + lec) ;
lsr = lsc * (1 + lec) ;
cr = EVOL 'VERT' 'MANU' ler lsr ;
lsr = lsr enle 1 ;
lep = (ler enle 1) - (lsr / ym1) born mini 0. ;
ecr = evol roug manu eps lep sig lsr ;
si igraph ;
  tl = TABL ;
  tl . 'TITRE' = TABL ;
  tl . 'TITRE' . 1 = 'Courbe conventionnelle ' ;
  tl . 'TITRE' . 2 = 'Courbe rationnelle  ' ;
  tl . 1 = mot 'MARQ CARR TIRR' ;
  tl . 2 = mot 'MARQ TRIA TIRR' ;
  dess (cc et cr) lege tl titr
  ' Courbes traction conventionnelle et rationnelle' ;
  tl . 'TITRE' . 1 = 'Courbe de traction rationnelle' ;
  tl . 'TITRE' . 2 = 'Courbe d ecrouissage  ' ;
  dess (cr et ecr) lege tl titr
  ' Courbes de traction et d ecrouissage (roug)' ;
fins ;
* Maillage
p1 = 0. 0. 0. ;
p2 = 1. 0. 0. ;
l12 = DROI 1 p1 p2 ;
s1 = l12 TRAN 1 (0. 1. 0.) ;
v1 = s1 VOLU 'TRAN' 3 (0. 0. 3.) ;
s2 = v1 FACE 2 ;
si igraph ;
  trac qual V1 titr
    ' Traction simple : deplacement bloque-impose sur S1-S2 ' ;
fins ;
* Modele et materiau (plasticite isotrope avc courbe de traction)
yor = (EXTR lsr 1) / (EXTR ler 2) ;
mo1 = MODE v1 'MECANIQUE' 'ELASTIQUE' 'PLASTIQUE' 'ISOTROPE' ;
ma1 = MATE mo1 'YOUN' yor 'NU' 0.3 'ECRO' ecr ;
* Blocages et chargement (deplacement UZ de la face sup.)
bl1 = BLOQ 'UZ' s2 ;
bl2 = (BLOQ 'UZ' s1) ET (BLOQ 'UX' 'UY' p1) ET (BLOQ 'UY' p2) ;
bl = bl1 ET bl2 ;
ev1 = EVOL 'MANU' (PROG 0. 1.) (PROG 0. 1.) ;
* Avec un deplacement de 3., on a un dL/L de 100 % au temps 1
f1 = DEPI bl1 3. ;
cha = CHAR 'DIMP' f1 ev1 ;
* Resolution : lagrangien reactualise avec materiau courbe rationnelle
t1 = TABL 'PASAPAS' ;
t1 . 'MODELE' = mo1 ;
t1 . 'CARACTERISTIQUES' = ma1 ;
t1 . 'BLOCAGES_MECANIQUES' = bl ;
t1 . 'CHARGEMENT' = cha ;
t1 . 'MES_SAUVEGARDES' = TABL ;
t1 . 'MES_SAUVEGARDES' . 'DEFTO' = VRAI ;
t1 . 'GRANDS_DEPLACEMENTS' = VRAI ;
t1 . 'LAGRANGIEN' = MOT 'REACTUALISE' ;
t1 . 'TEMPS_CALCULES' = PROG 0. pas 2.e-3 0.2 ;
PASAPAS t1 ;
* Post traitement (courbe contrainte / deformation)
* On reconstruit la courbe Svmis Vs. Eeq et F(U) :
ntps1 = dime t1.temps - 1 ;
leeq1 = prog 0 ;
lsvm1 = prog 0 ;
luz1 = prog 0 ;
lfz1 = prog 0 ;
repe bp1 ntps1 ;
  sigi1 = t1.contraintes.&bp1 ;
  epsi1 = elas mo1 ma1 sigi1 ;
  eeqi1 = t1.variables_internes.&bp1 exco epse epzz ;
  eeqi1 = eeqi1 + epsi1 ;
  leeq1 = leeq1 et (prog (maxi abs eeqi1)) ;
  lsvm1 = lsvm1 et (prog (maxi abs (vmis mo1 sigi1))) ;
  fzi1 = (((t1.reactions.&bp1 redu s2) resu) exco fz fz) maxi abs ;
  lfz1 = lfz1 et (prog fzi1) ;
  uzi1 = (t1.deplacements.&bp1 redu s2 exco uz) maxi abs ;
  luz1 = luz1 et (prog uzi1) ;
fin bp1 ;
evr = EVOL 'ROSE' 'MANU' leeq1 lsvm1 ;
* On construit la courbe rationnelle a partir de la reponse F(U)
lepzz1 = luz1 / (mesu V1 / (mesu S1)) ;
lun1 = prog (dime lepzz1)*1. ;
lepzz1 = log (lun1 + lepzz1) ;
lfz1 = lfz1 * (lun1 + lepzz1) / (mesu S1) ;
evr2 = EVOL 'ORAN' 'MANU' lepzz1 lfz1 ;
si igraph ;
  tl = TABL ;
  tl . 'TITRE' = TABL ;
  tl . 'TITRE' . 1 = 'Courbe fournie ' ;
  tl . 'TITRE' . 2 = 'Szz(Ezz) PASAPAS ' ;
  tl . 'TITRE' . 3 = 'Szz(Ezz) de F(U) ' ;
  tl . 1 = mot 'TIRR MARQ TRIA' ;
  tl . 2 = mot 'TIRL' ;
  tl . 3 = mot 'TIRC' ;
  DESS (cr ET evr et evr2) 'LEGE' tl
    titr ' Comparaison courbes calculees-fournie ' ;
fins ;
* Validation :
* Erreur sur la contrainte :
lepc1 = extr evr absc ;
lsmc1 = extr evr ordo ;
lsmr1 = ipol cr lepc1 ;
err1 = maxi abs (lsmc1 - lsmr1) / (maxi abs lsmr1) ;
* Erreur sur l'integrale sous la courbe :
evrr1 = evol manu lepc1 lsmr1 ;
err2 = intg (evrr1 - evr) / (intg cr) abs ;
err0 = prog err1 err2 maxi ;
* Message / Sortie en erreur :
opti echo 0 ;
mess ' ' ;
mess '      RESULTATS ' ;
mess '      --------- ' ;
mess ' *** Erreur relative max. sur la contrainte : ' (100.* err1) ' %';
mess ' *** Erreur relative max. sur l energie     : ' (100.* err2) ' %';
  mess ' ' ;
opti echo 1 ;
si (err0 > 1.e-2) ;
  opti echo 0 ;
  mess ' ' ;
  mess '     > TEST ECHOUE :( ' ;
  mess ' ' ;
  opti echo 1 ;
  erre 5 ;
sino ;
  opti echo 0 ;
  mess ' ' ;
  mess '     > TEST REUSSI :) ' ;
  mess ' ' ;
  opti echo 1 ;
fins ;
FIN ;
```

## fuite_fissure [Mecanique Endommagement]
```
* Test fuite_fissure.dgibi: Jeux de données
* CALCUL DU DEBIT DE FUITE D'UN
* MELANGE D'AIR SEC
* A TRAVERS UNE FISSURE TRAVERSANTE
* POUR UNE DIFFERENCE DE PRESSION IMPOSEE
* écoulement monodimensionnel, diphasique
* homogène, en régime permanent
* AUTEUR : HELENE SIMON
* DATE : 26/10/2005
opti echo 1 dime 2 elem qua4 ;
* une seule ligne : la fissure est parallele au cote l12
l = 1./(2.**0.5) ;
p1=0. 0. ; p2= l l ;
l12 = d p1 p2 dini 0.01 dfin 0.01 ;
ouv = 'PROG' (nbno l12)*200e-6 ;
ep = manu 'CHPO' (chan 'POI1' l12) 1 'OUV' ouv natu 'DIFFUS';
tp = manu chpo l12 1 'T' 120. natu 'DIFFUS' ;
* modele
MO1 = 'MODELISER' l12 FISSURE MASS PARF POISEU_COLEBROOK;
* champ de prop materielles
MAT1 = 'MATERIAU' MO1 'RUGO' 40e-6 ;
* conditions aux limites
TAB_CL = table ;
TAB_CL.'PRESSION_TOTALE_AMONT' = 5e5 ;
TAB_CL.'PRESSION_VAPEUR_AMONT' = 0. ;
TAB_CL.'TEMPERATURE_AMONT' = 170. ;
TAB_CL.'PRESSION_TOTALE_AVAL' = 1e5 ;
TAB_CL.'TEMPERATURE_PAROI' = tp ;
TAB_CL.'OUVERTURE' = ep ;
res = fiss MO1 MAT1 TAB_CL ;
Qn = 'EXTRAIRE' res 'Q' P2 ;
Qref = 1.74459E-02 ;
'MESSAGE' 'debit calcule = ' Qn 'debit reference = ' Qref;
ere1=(Qn-Qref)/Qref ;
ere='ABS' ere1 ;
SI (ere <EG 1.d-5 ) ;
   ERRE 0;
SINON;
   ERRE 5;
FINSI;
'FIN' ;
```

## ricrag_3d [Mecanique Endommagement]
```
* Cas test de l'implantation numérique du modele
* RICRAG 3D LOCAL/NON LOCAL
* Développé par :
* Benjamin Richard
* Les cas de charges sont entrés :
* - 1 : Traction monotone
* - 2 : Compression monotone
* - 3 : Traction cyclique
* - 4 : Compression cyclique
* - 5 : Traction/compression cyclique
* Choix du cas de charge
ncas = 5;
graph=mot 'N';
* Test du fichier compatible avec le non local
* nloc0 = 0; Cas local
* nloc0 = 1; Cas non local
nloc0 = 0;
* -------------- Options de calcul ---------------------
OPTION DIME 3 ELEM CUB8;
* -------------- Definition de la geometrie ------------
P1 = 0. 0. 0.;
P2 = 1. 0. 0.;
P3 = 1. 1. 0.;
P4 = 0. 1. 0.;
P5 = 0. 0. 1. ;
L1 = P1 DROIT 1 P2 ;
L2 = P2 DROIT 1 P3 ;
L3 = P3 DROIT 1 P4 ;
L4 = P4 DROIT 1 P1 ;
LTOT = L1 ET L2 ET L3 ET L4 ;
SURF1 = SURF LTOT PLANE;
VOLTO =VOLU SURF1 1 TRANS P5;
SURF2= FACE VOLTO 2;
VOLTOT = VOLTO;
* ------- Définition des conditions aux limites --------
* ----------- et des déplacements imposés --------------
CL = BLOQ SURF1 UZ;
CLL = BLOQ P1 'DEPL';
CLL = CLL ET (BLOQ UY P2);
CL1 = BLOQ SURF2 Uz;
D1 = DEPI CL1 1;
* ----- Définition du modèle ---------------------------
SI (EGA nloc0 1);
MOD1 = MODE VOLTOT MECANIQUE ELASTIQUE ISOTROPE
         ENDOMMAGEMENT RICRAG
      'NON_LOCAL' 'MOYE' 'V_MOYENNE' (MOTS 'EPTI') ;
SINON;
MOD1 = MODE VOLTOT MECANIQUE ELASTIQUE ISOTROPE
         ENDOMMAGEMENT RICRAG;
FINSI ;
* ----- Paramètres matériaux ---------------------------
* Module d'Young
youngn = 36000E+6;
* Coefficient de Poisson
nun = 0.2;
* Résistance en traction
ftn = 3.6e6;
* Fragilité en traction
aldin = 1.0e-2;
* Fragilité en compression
alinn = 9.0e-5;
* Module d'écrouissage 1
gam1n = 7.0e9;
* Moduke d'écrouissage 2
a1n = 7.0e-7;
mat1 =MATE mod1 YOUN youngn NU nun
                  FT ftn ALIN alinn
                  GAM1 gam1n A1 a1n
                  ALDI aldin;
* ----- Définition des cas de charge -------------------
SI (EGA ncas 1) ;
LI1 = PROG 0. 1.;
LI2 = PROG 0. 4.0e-4;
LIS1 = PROG 0. PAS 0.02 1.;
FINSI;
SI (EGA ncas 2) ;
LI1 = PROG 0. 1.;
LI2 = PROG 0. -8.0e-3;
LIS1 = PROG 0. PAS 0.02 1.;
FINSI;
SI (EGA ncas 3) ;
LI1 = PROG 0. 1. 2. 3. 4. 5.;
LI2 = PROG 0. 1.5e-4 9.5e-6 2.0E-4 3.0E-5 2.5E-4;
LIS1 = PROG 0. PAS 0.02 5.;
FINSI;
SI (EGA ncas 4) ;
LI1 = PROG 0. 1. 2. 3. 4. 5.;
LI2 = PROG 0. -3.0e-3 -1.5e-4 -5.0E-3 -3.5E-4 -8.0E-3;
LIS1 = PROG 0. PAS 0.02 5.;
FINSI;
SI (EGA ncas 5) ;
LI1 = PROG 0. 1. 2. 3. 4. 5. 6.;
LI2 = PROG 0. 1.3e-4 -3.0e-3 -1.5E-4 -5.0E-3 -3.5E-4 -8.0E-3;
LIS1 = PROG 0. PAS 0.02 6;
FINSI;
EV = EVOL MANU LI1 LI2 ;
CHA1 = CHAR 'DIMP' D1 EV ;
* ----------- Calcul par l'operateur PASAPAS ------------
LC = 1.0e-10;
CO1 = CONNEC mod1 LC NORMAL;
TAB1 = TABLE ;
TAB1.'BLOCAGES_MECANIQUES' = CL ET CLL ET CL1;
TAB1.'MODELE' = MOD1;
TAB1.'MOVA' = 'D   ';
TAB1.'CHARGEMENT' = CHA1;
TAB1.'TEMPS_CALCULES' = LIS1;
TAB1.'MAXITERATION' = 10;
SI (EGA nloc0 1);
TAB1.CONN = CO1;
MAT1 = MAT1 ET (MATE MOD1 'LCAR' LC);
FINSI;
TAB1.'CARACTERISTIQUES' = MAT1;
PASAPAS TAB1 ;
* ----------- Courbe effort-deplacement -----------------
ev2=@global tab1 CL1 EV fz;
ee = extr ev2 ordo 1;
  aa = extr ee ( dime ee);
  list aa;
  err = abs (aa + 1.48500E+07 ) / 1.48500E+07 ;
  message ' erreur relative ' err;
  si (err > 1.e-3);
    erreur (5);
     finsi;
si ( ega graph 'O');
DESS EV2;
finsi;
* @excel1 ev2 'cas_5.dat';
list ev2;
fin;
```

## xfem_gd [Mecanique Endommagement]
```
opti DIME 2 ELEM QUA4 mode plan defo;
* xfemcapipica.dgibi
* Test de l'opérateur de passage des contraintes(déformations)
* PK2 aux contraintes de Cauchy pour la XFEM
* d'une plaque elastique en traction avec fissure droite
* création : as, le 14.01.2010
opti echo 0;
* Options :
* pour afficher les messages et les graphes + choix de la sortie en .ps:
lmess = faux ; lgraph = faux ;
si lgraph ; lps=vrai; sinon; lps= faux; finsi;
si lps; opti trac psc; opti ftra 'xfem_gd.ps'; finsi;
* Maillage :
dx1 = 0.06 ;
blim = 1. + 5 * dx1 ; nbr1 = enti (blim / dx1);
* densité sur la hauteur de la bande :
nbh1 = 3 ; hh1 = ((flot nbh1)*dx1);
p1 = 'POIN' 0. hh1 ; p2 = 'POIN' blim hh1 ;
pm3 = 'POIN' blim (0.) ; pm4 = 'POIN' 0. (0.) ;
p3 = 'POIN' blim (-1.*hh1) ; p4 = 'POIN' 0. (-1.*hh1) ;
lh = droi nbr1 p1 p2 ;
ldh = droi p2 pm3 DINI dx1 DFIN dx1;
lgh = droi p1 pm4 DINI dx1 DFIN dx1;
lm = droi nbr1 pm4 pm3;
ldb = droi pm3 p3 DINI dx1 DFIN dx1;
lgb = droi pm4 p4 DINI dx1 DFIN dx1;
lb = droi nbr1 p4 p3;
s1h = 'DALLER' lm ldh lh lgh ;
s1b = 'DALLER' lb ldb lm lgb ;
* fissure initiale :
a0 = 3.*dx1;
pfis0 = -0.01 0.; pfisi = a0 0.;
fis0 = coul (droi 1 pfis0 pfisi) roug;
* Modèle et materiau :
Ey1 = 2.e5 ; nu1=0.3; rho1 = 7.e-6 ;
* CHARGEMENT : déplacement imposé :
tf = 1.; NT = ENTI (3.*tf);
dt0 = tf / (flot NT) ; l_t = PROG 0. pas dt0 tf;
ufin = tf ; l_uimp = PROG 0. pas (ufin / (flot NT)) ufin;
evou = evol 'MANU' 'temps' l_t 'U_imp' l_uimp ;
coeff0 = 0.2;
* Calcul MASSIF
s1q = s1h ;
elim s1q 0.0001;
* Modèle et materiau :
Mod1q = s1q MODE mecanique elastique isotrope ;
mat1q = MATE Mod1q 'YOUN' Ey1 'NU' nu1 'RHO' rho1;
* Conditions aux limites, Déplacements imposés :
ptrach = poin s1q proc (p1 plus ((2.*dx1) (-2.*dx1) ));
cl1hx = 'BLOQUE' ptrach 'UX' ; cl1hy = 'BLOQUE' ptrach 'UY' ;
psyms = elem lm comp (poin s1q proc pfisi) pm3;
cl1sym = 'BLOQUE' psyms 'UY' ;
si lgraph ; trac (s1q et (coul psyms roug)); finsi;
cl0 = (cl1hx 'ET' cl1hy 'ET' cl1sym) ;
dep1 = DEPI cl1hy coeff0;
uimp0 = CHAR 'DIMP' dep1 evou ;
* Resolution iterative du probleme
TAB0 = TABL; TAB0.TEMPS0 = 0. ;
TAB0.'MODELE' = Mod1q ;
TAB0.'CARACTERISTIQUES' = mat1q ;
TAB0.'CHARGEMENT' = uimp0;
TAB0.'BLOCAGES_MECANIQUES' = cl0 ;
TAB0.'TEMPS_CALCULES' = L_t ; TAB0.'TEMPS_SAUVES' = L_t ;
TAB0.'CONVERGENCE_FORCEE' = faux;
TAB0.'DELTAITER' = 190;
TAB0.'MAXITERATION' = 199;
TAB0.'HYPOTHESE_DEFORMATIONS' = 'LINEAIRE';
PASAPAS tab0;
* opti donn 5;
* Calcul XFEM
s1 = s1h et s1b;
elim s1 0.0001;
si lgraph; trac (s1 et fis0); finsi;
* Modèle et materiau :
Mod1a = s1 MODE mecanique elastique isotrope xq4R;
Mod1 = Mod1a ;
mat1 = MATE Mod1 'YOUN' Ey1 'NU' nu1 'RHO' rho1;
* Table XFEM : fisssure initiale, critere d'initiation, modele zone cohesive
tab_xfem = tabl;
TAB_xfem.fissure = fis0 ;
* creation des level set
psi1 phi1 = PSIPHI s1 fis0 'DEUX' pfisi;
* Appel a TRIELE :
cheX1 = trie mod1 psi1 phi1 'SAUT';
* Conditions aux limites, Déplacements imposés :
ptrach = poin s1 proc (p1 plus ((2.*dx1) (-2.*dx1) ));
ptracb = poin s1 proc (p4 plus ((2.*dx1) (2.*dx1) ));
cl1hx = 'BLOQUE' ptrach 'UX' ; cl1bx = 'BLOQUE' ptracb 'UX' ;
cl1hy = 'BLOQUE' ptrach 'UY' ; cl1by = 'BLOQUE' ptracb 'UY' ;
cl1 = (cl1hx 'ET' cl1bx 'ET'cl1hy 'ET' cl1by) ;
* CHARGEMENT : déplacement imposé :
dep1 = (DEPI cl1hy coeff0) et (DEPI cl1by (-1.*coeff0)) ;
uimp0 = CHAR 'DIMP' dep1 evou ;
* Resolution iterative du probleme
TAB1 = TABL; TAB1.TEMPS0 = 0. ;
TAB1.'MODELE' = Mod1 ;
TAB1.'CARACTERISTIQUES' = mat1 ;
TAB1.'CHARGEMENT' = uimp0;
TAB1.'BLOCAGES_MECANIQUES' = cl1 ;
TAB1.'TEMPS_CALCULES' = L_t ; TAB1.'TEMPS_SAUVES' = L_t ;
TAB1.'CONVERGENCE_FORCEE' = faux;
TAB1.'DELTAITER' = 190;
TAB1.'MAXITERATION' = 199;
TAB1.'HYPOTHESE_DEFORMATIONS' = 'LINEAIRE';
* opti donn 5 ;
pasapas tab1;
* Post-traitement
naff = mini (lect ((dime tab1.deplacements) - 1)
                  ((dime tab0.deplacements) - 1));
si lgraph;
    trac ((defo s1q tab1.deplacements.naff 1.)
       et (defo (coul s1h roug) tab0.deplacements.naff 1.));
finsi;
conf0=form;
* TEST de PICA et CAPI
CAU1 = pica tab1.contraintes.naff tab1.deplacements.naff
            tab1.deplacements. 0 tab1.modele;
PIC1 = capi CAU1 tab1.deplacements.naff tab1.deplacements. 0
                                 tab1.modele;
CAU0 = pica tab0.contraintes.naff tab0.deplacements.naff
            tab0.modele;
PIC0 = capi CAU0 tab0.deplacements.naff tab0.modele;
si lmess ;
    mess '  ';
    mess 'Test de CAPI et PICA en grandes defs ';
    mess '  ';
    mess 'Configuration de départ = configuration initiale';
    mess '----------------------';
    mess '  ';
    mess 'Elements enrichis :';
finsi;
el1 = 3; pg1 = 61;
sig01 = extr tab1.contraintes.naff 'SMYY' 1 el1 pg1;
cau11 = extr CAU1 'SMYY' 1 el1 pg1;
pic11 = extr PIC1 'SMYY' 1 el1 pg1;
si lmess; mess 'XFEM:' 'ini' sig01 'pica1' cau11 'inicapi' pic11; fins;
pg0 = 3;
sig00 = extr tab0.contraintes.naff 'SMYY' 1 el1 pg0;
cau01 = extr CAU0 'SMYY' 1 el1 pg0;
pic01 = extr PIC0 'SMYY' 1 el1 pg0;
si lmess; mess 'QUA4:' 'ini' sig00 'pica1' cau01 'inicapi' pic01; fins;
err6001 = abs ((sig01-sig00)/sig00);
err6002 = abs ((cau11-cau01)/cau01);
err6003 = abs ((pic11-pic01)/pic01);
si lmess; mess '   '; fins;
el3 = 2;
sig013 = extr tab1.contraintes.naff 'SMYY' 1 el3 pg1;
cau13 = extr CAU1 'SMYY' 1 el3 pg1;
pic13 = extr PIC1 'SMYY' 1 el3 pg1;
si lmess; mess 'XFEM:' 'ini' sig013 'pica1' cau13 'inicapi' pic13;fins;
sig003 = extr tab0.contraintes.naff 'SMYY' 1 el3 pg0;
cau03 = extr CAU0 'SMYY' 1 el3 pg0;
pic03 = extr PIC0 'SMYY' 1 el3 pg0;
si lmess; mess 'QUA4:' 'ini' sig003 'pica1' cau03 'inicapi' pic03;fins;
err5001 = abs ((sig013-sig003)/sig003);
err5002 = abs ((cau13-cau03)/cau03);
err5003 = abs ((pic13-pic03)/pic03);
si lmess; mess '   '; fins;
si lmess; mess 'Element non enrichi:'; fins;
el2 = 11;
sig012 = extr tab1.contraintes.naff 'SMYY' 1 el2 pg1;
cau12 = extr CAU1 'SMYY' 1 el2 pg1;
pic12 = extr PIC1 'SMYY' 1 el2 pg1;
si lmess; mess 'XFEM:' 'ini' sig012 'pica1' cau12 'inicapi' pic12;fins;
sig002 = extr tab0.contraintes.naff 'SMYY' 1 el2 pg0;
cau02 = extr CAU0 'SMYY' 1 el2 pg0;
pic02 = extr PIC0 'SMYY' 1 el2 pg0;
si lmess; mess 'QUA4:' 'ini' sig002 'pica1' cau02 'inicapi' pic02;fins;
err26001 = abs ((sig012-sig002)/sig002);
err26002 = abs ((cau12-cau02)/cau02);
err26003 = abs ((pic12-pic02)/pic02);
errmax1 = maxi (prog err6001 err6002 err6003 err5001 err5002
           err5003 err26001 err26002 err26003 );
* Test de CAPI et PICA en grandes defs
* Configuration de départ = configuration initiale';
* XFEM :
uvr1 = XFEM 'RECO' tab1.deplacements. naff mod1 ;
FORM uvr1;
PIC111 = capi CAU1
  (tab1.deplacements. 0 - tab1.deplacements.naff)
tab1.deplacements. naff tab1.modele;
CAU111 = pica pic111 (tab1.deplacements. 0 - tab1.deplacements.naff)
            tab1.deplacements. naff tab1.modele;
* Standard :
form conf0;
form tab0.deplacements.naff;
PIC011 = capi CAU0 (tab0.deplacements. 0 - tab0.deplacements.naff)
                tab0.modele;
CAU011 = pica pic011 (tab0.deplacements. 0 - tab0.deplacements.naff)
            tab0.modele;
si lmess;
    mess '  ';
    mess 'Configuration de départ = configuration déformée';
    mess '----------------------';
    mess '  ';
    mess 'Elements enrichis :';
fins;
el1 = 3; pg1 = 61;
sig01 = extr CAU1 'SMYY' 1 el1 pg1;
cau11 = extr CAU111 'SMYY' 1 el1 pg1;
pic11 = extr PIC111 'SMYY' 1 el1 pg1;
si lmess; mess 'XFEM:' 'ini' sig01 'pica1' cau11 'inicapi' pic11;fins;
pg0 = 3;
sig00 = extr CAU0 'SMYY' 1 el1 pg0;
cau01 = extr CAU011 'SMYY' 1 el1 pg0;
pic01 = extr PIC011 'SMYY' 1 el1 pg0;
si lmess; mess 'QUA4:' 'ini' sig00 'pica1' cau01 'inicapi' pic01;fins;
err6001 = abs ((sig01-sig00)/sig00);
err6002 = abs ((cau11-cau01)/cau01);
err6003 = abs ((pic11-pic01)/pic01);
si lmess; mess '   ';fins;
el3 = 2;
sig013 = extr CAU1 'SMYY' 1 el3 pg1;
cau13 = extr CAU111 'SMYY' 1 el3 pg1;
pic13 = extr PIC111 'SMYY' 1 el3 pg1;
si lmess; mess 'XFEM:' 'ini' sig013 'pica1' cau13 'inicapi' pic13;fins;
sig003 = extr CAU0 'SMYY' 1 el3 pg0;
cau03 = extr CAU011 'SMYY' 1 el3 pg0;
pic03 = extr PIC011 'SMYY' 1 el3 pg0;
si lmess; mess 'QUA4:' 'ini' sig003 'pica1' cau03 'inicapi' pic03;fins;
err5001 = abs ((sig013-sig003)/sig003);
err5002 = abs ((cau13-cau03)/cau03);
err5003 = abs ((pic13-pic03)/pic03);
si lmess; mess '   '; fins;
si lmess; mess 'Element non enrichi:'; fins;
el2 = 11;
sig012 = extr CAU1 'SMYY' 1 el2 pg1;
cau12 = extr CAU111 'SMYY' 1 el2 pg1;
pic12 = extr PIC111 'SMYY' 1 el2 pg1;
si lmess; mess 'XFEM:' 'ini' sig012 'pica1' cau12 'inicapi' pic12;fins;
sig002 = extr CAU0 'SMYY' 1 el2 pg0;
cau02 = extr CAU011 'SMYY' 1 el2 pg0;
pic02 = extr PIC011 'SMYY' 1 el2 pg0;
si lmess; mess 'QUA4:' 'ini' sig002 'pica1' cau02 'inicapi' pic02;fins;
err26001 = abs ((sig012-sig002)/sig002);
err26002 = abs ((cau12-cau02)/cau02);
err26003 = abs ((pic12-pic02)/pic02);
errmax2 = maxi (prog err6001 err6002 err6003 err5001 err5002
           err5003 err26001 err26002 err26003 );
errmax = maxi (prog errmax1 errmax2);
si lmess;
    mess 'Erreur entre calcul standard et XFEM:' errmax;
fins;
* Erreur initiale entre calcul standard et XFEM: 0.10829
* Attention, on fait des erreurs assez importantes car le nombre de
* pts de Gauss n'est pas le même dans les deux cas :
* -> différences sur le calcul des contraintes initiales
* -> le pt de gauss xq4r est le plus proche possible du pt QUA4
* mais reste different, 'où une erreur importante pour les éléments
* en pointe de fissure.
* pr etre sur, comparer avec éléments xq4r à 4pts de Gauss ->erreur~e-15
SI (errmax >EG 20.);
   ERRE 5;
FINSI;
fin;
```

## rccmtest [Mecanique Fatigue]
```
* TEST DES ROUTINES INTERNES DE @RCCM
* CALCUL EN AXISYMETRIQUE ET EN 3D SUR UN SEGMENT D APPUI
* COMPARAISON DES RESULTATS
OPTION DIME 2 ELEM QUA8 ;
GRAPH = 'N' ;
OO = 0 0 ; OX = 1 0 ; OY = 0 1 ;
DENS 1. ;
P1 = 10 0 ; P2 = 15 0 ;HT = 50. ;
LIG = D DINI 3 DFIN 1. OO P1 D P2 ;
TOUT = D P1 P2 TRAN 5 ( 0 HT ) ;
CCONT = TOUT CONTOUR ;
LIINT = TOUT COTE 4 ;
OPTION MODE AXIS ;
MOD1 = MODE TOUT MECANIQUE ELASTIQUE ISOTROPE ;
MAT1 = MATE MOD1 YOUN 2.E5 NU .3 ;
FPRE = PRESSION MASS 5. MOD1 LIINT ;
RIG1 = RIGI MOD1 MAT1 ;
C1 = (TOUT COTE 1 ) ET ( TOUT COTE 3) ;
* ------- conditions limites -----------------------
CLM = BLOQUER DEPLA C1 ;
SOL1 = RESO ( RIG1 ET CLM) FPRE ;
DEF0 = DEFO CCONT SOL1 0. BLAN ;
DE1 = MAXI SOL1 AVEC ( MOTS UR) ;
AMP = 1./DE1 ;
DEF1 = DEFO CCONT SOL1 AMP ROUG ;
'SI' ( NEG GRAPH N) ;
TRAC ( DEF0 ET DEF1) ;
'FINSI' ;
SIG1 = SIGMA SOL1 MOD1 MAT1 ;
H = 25. ;
PP1 = P1 PLUS ( 0 H ) ; PP2 = P2 PLUS (0 H ) ;
NSEG = 12 ;
* NI TRACES NI ECRITURES DE FICHIERS EN INTERNE
GRAPL*LOGIQUE =FAUX ;
ECRI*LOGIQUE =FAUX ;NOMFICH = 'BLANC' ;
ETAT = 1 ; ICOU = 1 ;
TITRE ' RCCMCO2   ' ;
TABB1 = @RCCMCO2 ETAT ICOU PP1 PP2 NSEG SIG1 MOD1
                       .1 GRAPL ECRI NOMFICH (0 0 ) ;
* 3D
OPTION DIME 3 ELEM CU20 ;
OZ = 0 0 1 ;
VOL1 = TOUT VOLU ROTA 3 20 OO OY ;
ELIM .001 VOL1 ;
VOL1 = REGE VOL1 ;
DEPLACER VOL1 TOURNER -10 OO OY ;
MOD2 = MODE VOL1 MECANIQUE ELASTIQUE ;
MAT2 = MATE MOD2 YOUN 2.E5 NU .3 ;
VOENV = VOL1 ENVEL ;
SUI1 = VOENV POINT CYLI OO OY P1 .01 ;
SUINT = VOENV ELEM APPU STRIC SUI1 ;
FPRE = PRESSION MASS 5. MOD2 SUINT ;
RIG2 = RIGI MOD2 MAT2 ;
P11 = P1 TOURNER 20 OO OY ;P3 = P1 TOURNET 20 OO OY ;
OP = OO PLUS ( 0 HT 0) ;OP1 = P1 PLUS ( 0 HT 0) ;
OP3 = P3 PLUS ( 0 HT 0) ;
* ------------------ conditions limites ---------------------
CL1 = (BLOQUER DEPLA ( VOL1 POINT PLAN OO P1 P3 .001 ))
   ET (BLOQUER DEPLA ( VOL1 POINT PLAN OP OP1 OP3 .001)) ;
CL2 = (SYMT DEPLA OO OP P1 VOL1 .001 )
  ET (SYMT DEPLA OO OP P3 VOL1 .001 ) ;
SOL2 = RESO ( RIG2 ET CL1 ET CL2 ) FPRE ;
SIG2 = SIGMA SOL2 MOD2 MAT2 ;
VPER = 0 0 1 ;
'SI' ( NEG GRAPH N) ;
TRAC ( VOENV ET ( D 2 PP1 PP2 COUL ROUG) ) ;
'FINSI' ;
TABB2 = @RCCMCO2 ETAT ICOU PP1 PP2 NSEG SIG2 MOD2
                    .1 GRAPL ECRI NOMFICH VPER ;
* ------------ COMPARAISON DES RESULTATS SIGNIFICATIF -------
* ------------ ENTRE 2D ET 3D --------------------
* ATTENTION SMTT 2D CORRESPOND A SMYY EN 3D
OPTION ECHO 0 ;
III = INDEX TABB2;
REPETER BAB 3 ;
LRE1 = TABB1.&BAB ;
LRE2 = TABB2.&BAB ;
EPS1 = ABS(((EXTR LRE1 1 ) - (EXTR LRE2 1))/(EXTR LRE2 1)) ;
EPS2 = ABS(((EXTR LRE1 2 ) - (EXTR LRE2 3))/(EXTR LRE2 3)) ;
EPS3 = ABS(((EXTR LRE1 3 ) - (EXTR LRE2 2))/(EXTR LRE2 2)) ;
 MESS ' ERREURS  ' EPS1 EPS2 EPS3 ;
'SI' ((EPS1 > 0.01) OU (EPS2 > 0.01) OU (EPS3 > 0.01)) ;
 ERRE 5 ;
 'SINON' ;
 ERRE 0 ;
'FINSI' ;
'FIN' BAB ;
'FIN' ;
```

## flam3 [Mecanique Flambage]
```
* COMPARAISON DES CALCULS DE FLAMBAGE D'UN TUBE
* SOUS PRESSION INTERNE (TUBE DE SACLAY)
OPTI DIME 3 ELEM QUA4 ECHO 1;
MESS '  COMPARAISON DES CALCULS DE FLAMBAGE';
MESS 'D UN TUBE SOUS PRESSION INTERNE MODéLISé';
MESS '    AVEC COQ3 ET COQ4 (TUBE DE SACLAY)';
L = 10. ;
T = .01 ;
R = .5 ;
E = 2E11 ;
NV = 30 ;
NH = 8 ;
P1 = R 0 0 ;
P2 = R 0 L ;
L1 = P1 D NV P2 ;
AX1 = 0 0 0 ;
AX2 = 0 0 L;
SURF4 = ROTA L1 AX1 AX2 NH 90. ;
SURF3 = CHAN 'TRI3' SURF4;
SURF8 = CHAN 'QUADRATIQUE' SURF4 ;
* MODéLES, MATéRIAUX ET RIGIDITé
MODL3 = MODE SURF3 MECANIQUE COQ3;
MODL4 = MODE SURF4 MECANIQUE COQ4;
MODL8 = MODE SURF8 MECANIQUE COQ8;
MAT3 = MATE MODL3 YOUN E NU .30 RHO 8000 EPAI T ;
MAT4 = MATE MODL4 YOUN E NU .30 RHO 8000 EPAI T ;
MAT8 = MATE MODL8 YOUN E NU .30 RHO 8000 EPAI T ;
MOP1 = 'MODE' SURF3 'CHARGEMENT' 'PRESSION' COQ3 ;
MOP2 = 'MODE' SURF4 'CHARGEMENT' 'PRESSION' COQ4 ;
MOP3 = 'MODE' SURF8 'CHARGEMENT' 'PRESSION' COQ8 ;
MAP1 = 'PRES' MOP1 'PRES' -100. ;
MAP2 = 'PRES' MOP2 'PRES' -100. ;
MAP3 = 'PRES' MOP3 'PRES' -100. ;
MAP3B = 'CARA' MOP3 'EPAI' T ;
MODL3 = MODL3 ET MOP1 ; MAT3 = MAT3 ;
MODL4 = MODL4 ET MOP2 ; MAT4 = MAT4 ;
MODL8 = MODL8 ET MOP3 ; MAT8 = MAT8 ;
RIG3 = RIGI MODL3 MAT3 ;
RIG4 = RIGI MODL4 MAT4 ;
RIG8 = RIGI MODL8 MAT8 ;
I1 = PI*(R**3)*T ;
S1 = 2*PI*R*T ;
* CONDITION AUX LIMITES
LL41 = COTE 2 SURF4 ;
BL41 = SYMT DEPL ROTA (0 0 0) (1 0 0) (0 1 0) SURF4 .01 ;
BL42 = SYMT DEPL ROTA AX1 AX2 P1 SURF4 .01 ;
BL43 = SYMT DEPL ROTA AX1 AX2 (0 1 0) SURF4 .01;
F4 = 'BSIG' MOP2 MAP2 ;
LL31 = COTE 2 SURF4 ;
BL31 = SYMT DEPL ROTA (0 0 0) (1 0 0) (0 1 0) SURF3 .01 ;
BL32 = SYMT DEPL ROTA AX1 AX2 P1 SURF3 .01 ;
BL33 = SYMT DEPL ROTA AX1 AX2 (0 1 0) SURF3 .01;
F3 = 'BSIG' MOP1 MAP1 ;
BL81 = SYMT DEPL ROTA (0 0 0) (1 0 0) (0 1 0) SURF8 .01 ;
BL82 = SYMT DEPL ROTA AX1 AX2 P1 SURF8 .01 ;
BL83 = SYMT DEPL ROTA AX1 AX2 (0 1 0) SURF8 .01;
F8 = 'BSIG' MOP3 MAP3 MAP3B ;
* CALCULS éLASTIQUES
DEP3 = RESO (RIG3 ET BL31 ET BL32 ET BL33) F3 ;
SIG3 = SIGM MODL3 MAT3 DEP3 ;
KSIG3 = KSIG MODL3 MAT3 SIG3 FLAM ;
DEP4 = RESO (RIG4 ET BL41 ET BL42 ET BL43) F4 ;
SIG4 = SIGM MODL4 MAT4 DEP4 ;
KSIG4 = KSIG MODL4 MAT4 SIG4 FLAM ;
DEP8 = RESO (RIG8 ET BL81 ET BL82 ET BL83) F8 ;
SIG8 = SIGM MODL8 MAT8 DEP8 ;
KSIG8 = KSIG MODL8 MAT8 SIG8 FLAM ;
* CONDITIONS AUX LIMITES POUR LE CALCUL DE FLAMBAGE
BL33 = ANTI DEPL ROTA AX1 AX2 (0 1 0) SURF3 .01;
PP0 = POIN SURF3 PROCHE (0 R L) ;
BL34 = BLOQ UX PP0 ;
RIGT3 = RIG3 ET BL31 ET BL32 ET BL33 ET BL34 ;
BL43 = ANTI DEPL ROTA AX1 AX2 (0 1 0) SURF4 .01;
PP0 = POIN SURF4 PROCHE (0 R L) ;
BL44 = BLOQ UX PP0 ;
RIGT4 = RIG4 ET BL41 ET BL42 ET BL43 ET BL44 ;
BL83 = ANTI DEPL ROTA AX1 AX2 (0 1 0) SURF8 .01;
PP0 = POIN SURF8 PROCHE (0 R L) ;
BL84 = BLOQ UX PP0 ;
RIGT8 = RIG8 ET BL81 ET BL82 ET BL83 ET BL84 ;
* CALCUL DE FLAMBAGE
KP3 = KP MOP1 (MANU CHPO SURF3 1 P -100.) FLAM ;
TAB3 = VIBR PROCHE (PROG 79.) RIGT3
                     ((1*KP3) ET (-1*KSIG3) ) ;
KP4 = KP MOP2 (MANU CHPO SURF4 1 P -100.) FLAM ;
TAB4 = VIBR PROCHE (PROG 79.) RIGT4
                     ((1*KP4) ET (-1*KSIG4) ) ;
KP8 = KP MOP3 (MANU CHPO SURF8 1 P -100.) FLAM ;
TAB8 = VIBR PROCHE (PROG 79.) RIGT8
                     ((1*KP8) ET (-1*KSIG8) ) ;
DEP3 = TAB3.MODES. 1 .DEFORMEE_MODALE ;
DEP4 = TAB4.MODES. 1 .DEFORMEE_MODALE ;
DEP8 = TAB8.MODES. 1 .DEFORMEE_MODALE ;
DEF3 = DEFO DEP3 SURF3 1. ROUGE ;
DEF4 = DEFO DEP4 SURF4 1. VERT ;
DEF8 = DEFO DEP8 SURF8 1. BLEU ;
DEF0 = DEFO DEP3 SURF3 0. ;
* TRAC (DEF3 ET DEF4 ET DEF0) ;
F3 = TAB3.MODES. 1 .FREQUENCE ;
LL3 = (2*PI*F3)**2 ;
F4 = TAB4.MODES. 1 .FREQUENCE ;
LL4 = (2*PI*F4)**2 ;
F8 = TAB8.MODES. 1 .FREQUENCE ;
LL8 = (2*PI*F8)**2 ;
PCOQ3 = LL3*100 ;
PCOQ4 = LL4*100 ;
PCOQ8 = LL8*100 ;
PTH = PI**2*E*R*T/4/L/L ;
ERR3 = ABS (100.*(PTH - PCOQ3)/PCOQ3);
ERR4 = ABS (100.*(PTH - PCOQ4)/PCOQ4);
ERR8 = ABS (100.*(PTH - PCOQ8)/PCOQ8);
MESS 'CALCUL THéORIQUE        : ' PTH;
MESS 'CALCUL NUMéRIQUE (COQ3) : ' PCOQ3;
MESS 'ERREUR                  : ' ERR3 '%';
MESS 'CALCUL NUMéRIQUE (COQ4) : ' PCOQ4;
MESS 'ERREUR                  : ' ERR4 '%';
MESS 'CALCUL NUMéRIQUE (COQ8) : ' PCOQ8;
MESS 'ERREUR                  : ' ERR8 '%';
* ------------------ CODE DE BON FONCTIONNEMENT -------------------------
SI ((ERR3 < 5) ET (ERR4 < 5) ET (ERR8 < 8));
   ERRE 0;
SINON;
   ERRE 5;
FINSI;
FIN;
```

## kp2_test [Mecanique Flambage]
```
* test de la matrice de rigidité associée à un champ
* de pression linéaire.
* Il s'agit de calculer la variation de la composante
* verticale des forces de pression d'un reservoir
* semispherique, due à un mouvement verticale dans un champ
* de pression hydrostatique.
* reference : rapport DMT/95/
r1 = 1. ; comm 'rayon de la sphere' ;
d1 = 1. ; comm 'deplacement verticale' ;
rg = 1. ; comm 'module du gradient de la pression' ;
opti dime 3 elem qua4 ;
p1 = 0.001 0 0 ;
p2 = r1 0. r1 ;
c1 = 0 0 r1 ;
l1 = cerc p1 c1 p2 dini .05 dfin .15 ;
* on maille un secteur de 2 degrees
surf1 = rota l1 2. 1 (0 0 0) c1 ;
elim surf1 .0015;
surf1 = rege surf1 ;
modl1 = mode surf1 mecanique coq4 dkt ;
rig1 = kp modl1 rg (0 0 -1) ;
dep1 = manu chpo surf1 1 uz d1 ;
f1 = resu (rig1 * dep1) ;
fz1 = 180 * (maxi (exco fz f1));
mess 'analytique :'(-1*pi) 'numerique  :'fz1 ;
err1 = ((fz1 + pi)/fz1)*100 ;
mess ' erreur :'err1'%';
 si ((abs err1) > .03) ;
   erre 5 ;
 sinon ;
 erre 0 ;
finsi ;
fin ;
```

## tufi_relax [Mecanique Fluage]
```
OPTION ECHO 0;
opti dime 3 mode TRID elem seg2 ;
rap=10.;T1=10.;RMOY=T1 * rap;REXT1=RMOY + (T1 / 2.);
P1=0. 0. 0.;P2=0. 0. 0.;
TUFSS=MANU SEG2 P1 P2;
OBJTUFI= MODE TUFSS MECANIQUE ELASTIQUE FLUAGE NORTON TUFI;
CARTOT= mate OBJTUFI YOUN 2.E5 NU 0.3
AF1 3.e-15 AF2 5. AF3 1. SMAX 200. RAYO REXT1 EPAI T1
VX 1. VY 0. VZ 0. VXF 0. VYF 0. VZF 1. ANGL 120;
CDL=BLOQ depla rota p1;
RIG1= RIGI OBJTUFI CARTOT;RIG = RIG1 ET CDL;
DD = RESO RIG (MOME 100.E5 'MY' P2);
cdli=bloq 'RY' P2;CDL=CDL et cdli;
RIG = RIG1 ET CDL;
vdepli=extr DD 'RY' P2;
depli=depi cdli vdepli;
DD = RESO RIG depli;
M0=react DD cdli;vM0=extr M0 'MY' P2;
CMM=vdepli / vM0;
SS = SIGMA CARTOT OBJTUFI DD;
EVT = EVOL MANU 'T' (PROG 0. 1.E10) 'F(T)' (PROG 1. 1.);
dt=10.;LIS = PROG 0. pas dt 110. ;
FDT=CHAR 'DIMP' depli EVT;
TENTR=TABLE;
TENTR.CARACTERISTIQUES=CARTOT;
TENTR.MODELE=OBJTUFI;
TENTR.CHARGEMENT=FDT;
TENTR.'CONTRAINTES'=tabl;
TENTR.'DEPLACEMENTS'=tabl;
TENTR.'CONTRAINTES' . 0 =SS;
TENTR.'DEPLACEMENTS' . 0 = DD;
TENTR.BLOCAGES_MECANIQUES=CDL;
TENTR.TEMPS_CALCULES= LIS;
pasapas TENTR;
t10=TENTR.TEMPS . 10;
U10=TENTR.DEPLACEMENTS . 10;
VAR10=TENTR.VARIABLES_INTERNES . 10;
M10=react U10 cdli;vM10=extr M10 'MY' P2;phi_el=CMM * vM10;
phi_f=vdepli - phi_el;
vC10=extr VAR10 'JPOI' 1 1 1;
phi_fb=extr VAR10 'EPSE' 1 1 1;
U9=TENTR.DEPLACEMENTS . 9;
Mi=react U9 cdli;vMi=extr Mi 'MY' P2;phi_el=CMM * vMi;
phi_f9=vdepli - phi_el;
U10=TENTR.DEPLACEMENTS . 10;
Mi=react U10 cdli;vMi=extr Mi 'MY' P2;phi_el=CMM * vMi;
phi_f10=vdepli - phi_el;
U11=TENTR.DEPLACEMENTS . 11;
Mi=react U11 cdli;vMi=extr Mi 'MY' P2;phi_el=CMM * vMi;
phi_f11=vdepli - phi_el;
phi_fpt1=(phi_f10 - phi_f9) / dt;
phi_fpt2=(phi_f11 - phi_f10) / dt;
phi_fpt=(phi_fpt1 + phi_fpt2) / 2.;
* COMPARAISON A LA SOLUTION ANALYTIQUE
Mth10=7.747E6;phi_f10=1.850E-4;vCth10=4.576E-3;
ph_fpt10=1.020E-6;
errM=abs ((vM10 - Mth10) / Mth10);
errphif=abs ((phi_f - phi_f10) / phi_f10);
errphifb=abs ((phi_fb - phi_f10) / phi_f10);
errC=abs ((vC10 - vCth10) / vCth10);
errphfp=abs ((phi_fpt - ph_fpt10) / ph_fpt10);
err=errM * errphif * errphifb * errC * errphfp;
SI (ERR < (1.E-3 ** 5))ERRE 0;SINO;ERRE 5;FINSI;
fin;
```

## four2 [Mecanique Fourier]
```
* Test Four2.dgibi: Jeux de données
* Test four2.dgibi: Jeux de données
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
* TEST FOUR2
* CYLINDRE INFINI SOUS PRESSION EXTERNE(NU=0)
* Soit un cylindre infini soumis a une pression externe.
* Une analyse de flambage permet de determiner la charge critique
* associée aux 10 premiers modes de Fourier de la structure :
* (u = u°*cos(2*Teta) )
* (u = u°*cos(3*Teta) )
* (u = u°*cos(4*Teta) )
* (u = u°*cos(5*Teta) )
* Les éléments utilisés sont des éléments massifs.
* Comparaison a une solution analytique
TITRE 'CYLINDRE INFINI SOUS PRESSION EXTERNE';
OPTI DIME 2 ELEM qua8 MODE FOUR 0;
* ------------------ CONSTRUCTION DE LA GEOMETRIE ------------------------
PA1=999.5 0.;PB1=999.5 10.;PO1=0. 0.;PO2=0. 10.;
PA2=1000.5 0.;PB2=1000.5 10.;
L1 = PA1 DROI 5 PA2;
L2 = PA2 DROI 19 PB2;
L3 = PB2 DROI 5 PB1;
L4 = PB1 DROI 19 PA1;
CYL = DALLER L1 L2 L3 L4 PLAN;
SI (NEG GRAPH 'N');
  TRAC 'QUAL' CYL;
FINSI;
MOD1=MODE CYL MECANIQUE ELASTIQUE qua8;
* --- DECLARATION DE FOURIER NOHARM POUR LES OBJETS QUI SERONT UTILISES --
* ------------- POUR PLUSIEURS NUMEROS D'HARMONIQUE ----------------------
OPTI MODE FOUR NOHARM;
* -------------- CONDITIONS AUX LIMITES SYMETRIQUES ----------------------
SYMB=SYMT CYL DEPL PA1 PO1 0.05;
SYMH=SYMT CYL DEPL PB1 PO2 0.05;
CDL=SYMB ET SYMH;
* -------------- MATERIAU ET CARACTERISTIQUES ----------------------------
MAT =MATE MOD1 YOUN 20000. NU 0.;
* ------ DECLARATION DE FOURIER MODE 0 POUR LE CALCUL DES CONTRAINTES ----
OPTI MODE FOUR 0;
FP=PRES MASS MOD1 1. L2 ;
RIG=RIGI MOD1 MAT;
AAA = RIG ET CDL et (bloq PA1 UT);
U = RESO AAA FP ;
SIG = SIGMA U MOD1 MAT;
I = 1;
ERRMAX = 0.;
REPE BOUC1 9;
   I = I + 1;
* ----- DECLARATION DE FOURIER MODE I POUR L'ANALYSE DE FLAMBAGE ---------
   OPTI MODE FOUR I;
   MKSI = KSIGMA MOD1 MAT (SIG * -1.) FLAM;
   RIG = RIGI MOD1 MAT ;
* --------- RECHERCHE DE LA 1ERE FREQUENCE PROPRE ------------------------
   MODF=VIBR PROC (PROG 0.01) (RIG ET CDL) MKSI;
   W1 = MODF . MODES . 1 . FREQUENCE;
   LAMBDA1=(W1 * 2. * PI) ** 2 * (SIGN W1);
   LDUM = (20000./(1. - 0.))*((1./1000.)**3)/12.;
   LTH1 = LDUM*I*I;
   ERR1 = (LTH1 - LAMBDA1)/LTH1*100;
   SAUT 1 LIGN ;
   MESS 'Mode : ' I;
   SAUT 1 LIGN ;
   MESS '  K(SIG) SEUL  :   ON DOIT TROUVER LAMBDA=' LTH1;
   MESS '                   LE CALCUL DONNE LAMBDA=' LAMBDA1;
   MESS '     SOIT UN ECART DE                : ' ERR1 '%' ;
   SAUT 1 LIGN ;
   ERRMAX = MAXI ABS (PROG ERRMAX ERR1);
FIN BOUC1;
mess ' errmax vaut ' errmax '%';
SI (ERRMAX < 1.4D0 );
   ERRE 0;
SINON ;
   ERRE 5;
FINSI;
FIN;
```

## fronabs [Mecanique Interaction Fluide Structure]
```
* test des frontieres absorbantes
* on teste la reultante pour un champ de vitesses donne
option dime 3 elem cub8;
FRA = 0.4;
MFR = -1 * FRA;
RAC = (2. ** 0.5) / 2. ;
MRA = -1 * RAC ;
P0 = 0. 0. 0. ;
P1a = FRA 0. 0. ;
P1 = 1. 0. 0. ;
P2a = 0. 0. MFR;
P2 = 0. 0. -1. ;
P3 = FRA 0. MFR ;
P4 = RAC 0. MRA ;
* Plus NBRAY est grand et plus la solution numérique converge vers la
* solution analytique.
NBRAY = 6;
D1a = P0 DROI NBRAY P1a ;
D1b = P1a DROI NBRAY P1 ;
D2a = P0 DROI NBRAY P2a ;
D2b = P2a DROI NBRAY P2 ;
D2c = P1a DROI NBRAY P3 ;
D1c = P2a DROI NBRAY P3 ;
D3 = P3 DROI NBRAY P4 ;
C1 = CERC NBRAY P2 P0 P4 ;
C2 = CERC NBRAY P1 P0 P4 ;
SUR1 = REGL NBRAY D2a D2c ;
SUR2 = REGL NBRAY D2c C2 ;
SUR3 = REGL NBRAY D1c C1 ;
ELIM 1.D-6 SUR1 SUR2 ;
ELIM 1.D-6 SUR1 SUR3 ;
ELIM 1.D-6 SUR2 SUR3 ;
SUR1 = SUR1 ET SUR2 ET SUR3;
NBROT = NBRAY * 2 ;
SOL1 = SUR1 VOLU NBROT ROTA 90. ( 0.0 0.0 0.0 ) ( 0.0 0.0 1.0 ) ;
ELIM 1.e-6 SOL1 ;
SOL1 = REGE SOL1 ;
* TRAC QUAL SOL1 cach;
C1 = C1 ET C2 ;
BOR1 = C1 ROTA NBROT 90. ( 0.0 0.0 0.0 ) ( 0.0 0.0 1.0 ) ;
BOR1 = REGE BOR1 ;
ELIM 1.e-6 BOR1 SOL1 ;
MOD_S = MODE SOL1 MECANIQUE ;
E = 1. ;
POIS = 0. ;
RO = 1. ;
MAT_S1 = MATE MOD_S 'YOUN' E 'NU' POIS 'RHO' RO ;
AMOT1 = AMOR MOD_S BOR1 MAT_S1 ;
E = 2. ;
POIS = 0. ;
RO = 1. ;
MAT_S2 = MATE MOD_S 'YOUN' E 'NU' POIS 'RHO' RO ;
AMOT2 = AMOR MOD_S BOR1 MAT_S2 ;
X1 Y1 Z1 = COOR BOR1 ;
DEP1 = (X1 NOMC 'UX') ET (Y1 NOMC 'UY') ET (Z1 NOMC 'UZ') ;
RIG1 = RELA CORI DEPL SOL1 ;
RIG2 = BLOQ (P0 et P2) DEPL;
RIG3 = BLOQ P1 UY ;
F1 = DEPI RIG3 1. ;
DEP2 = RESO (RIG1 ET RIG2 et rig3 ) F1 ;
* vec1 = vect dep2 ux uy uz 1. jaun ;
* trac vec1 sol1 cach ;
FOR1 = RESU (AMOT1 * DEP1);
FOR2 = RESU (AMOT2 * DEP2);
for1 = (xtx for1) **.5 ;
for2 = (xtx for2) **.5 ;
* resultat analytiques
fan1 = 3**.5 * pi / 4 ;
fan2 = 2**.5 * pi / 4 ;
* comparaison et calcul d'erreur
err1 = (for1 - fan1) / fan1 * 100 ;
err2 = (for2 - fan2) / fan2 * 100 ;
errmax = maxi abs (prog err1 err2) ;
list errmax ;
MESS 'La résultante des forces visqueuses dues au déplacement radial est' FOR1;
MESS 'La résultante des forces visqueuses dues au déplacement tangentiel est' FOR2;
LIST (SOL1 ELEM 'TYPE');
* 1.2276 est l'erreur pour NBRAY = 6. On tolere un poil plus
SI(errmax <EG 1.228);
    ERRE 0;
SINO;
    ERRE 5;
FINSI;
FIN;
```

## iss2D_x [Mecanique Interaction_Sol_Structure]
```
GRAPH='Y';
SAUT PAGE ;
* REPONSE SISMIQUE DU SOL EN ABSENCE DE STRUTURE
* DESCRIPTION DU PROBLEME
* IL S'AGIT D'UN PROBLEME D'INTERACTION SOL-STRUCTURE.
* EN ABSENCE DE STRUCTURE, IL N'Y PAS D'INTERACTION. ON DOIT RETROUVER
* L'ACCELEROGRAMME IMPOSE A LA SURFACE DU SOL VIA LE PROCESSUS DE
* DECONVOLUTION (PROCEDURES DECONV OU DECONV3D) ET CONVOLUTION
* (PROCEDURE DYNAMIC OU PASAPAS).
* LE CYLINDRE DANS CE JEU DE DONNEES REPRESENTE LE SOL PROCHE TANDIS
* QUE LE SOL LOINTAIN QUI S'ETEND VERS L'INFINI EST REPRESENTE PAR UNE
* FRONTIERE ABSORBANTE COMPOSEE D'AMORTISSEURS VISQUEUX.
OPTION TRAC PSC ;
OPTION ECHO 0 ;
* PROCEDURE DE CALCUL DE LA DERIVEE PREMIERE
'DEBPROC' DERIV1 EV1 ;
     X = 'EXTR' EV1 'ABSC' ;
     Y = 'EXTR' EV1 'ORDO' ;
     NPOIN = 'DIME' X ;
     H = ( 'EXTR' X 2 ) - ( 'EXTR' X 1 ) ;
     X1 = ( 'PROG' 0.0 0.0 ) 'ET' Y ;
     X3 = Y 'ET' ( 'PROG' 0.0 0.0 ) ;
     DX = ( X3 - X1 ) / ( H * 2.0 ) ;
     Y1 = 'ENLE' ( 'ENLE' DX ( NPOIN + 2 ) ) 1 ;
     L1 = ( 'PROG' 0.0 ) 'ET' ( 'PROG' ( NPOIN - 2 ) * 1.0 )
                            'ET' ( 'PROG' 0.0 ) ;
     Y2 = Y1 * L1 ;
     EV2 = 'EVOL' 'MANU' X Y2 ;
'FINPROC' EV2 ;
* SOL SANS STRUCTURE
OPTI DIME 2 MODE FOUR 1 ELEM QUA8 COUL BLEU ;
R = 2. / (PI**0.5) ;
NE = 2 ;
NR = 3 ;
P0 = 0. 0. ;
P4 = (NR*R) 0. ;
SUR = COUL VERT (DROIT (NE*NR) P0 P4) ;
SOL = TRAN (NE*NR) SUR (0 (-1*NR*R)) ;
BOR = COTE 2 SOL ;
FON = COTE 3 SOL ;
AXE = COTE 4 SOL ;
ELIM SOL 0.001 ;
TITR 'MAILLAGE SOL (AXISYMETRIQUE)' ;
SI (NEG GRAPH 'N');
TRAC SOL QUAL NCLK;
FINSI;
* MODELE DE SOL
NU1 = 0.3 ;
G1 = 100.E7 ;
E1 = 2*(1 + NU1)*G1 ;
MOD_S = MODE SOL MECANIQUE ELASTIQUE ISOTROPE QUA8 ;
MAT_S = MATE MOD_S YOUN E1 NU NU1 RHO 2000 ;
MAS_S = MASS MOD_S MAT_S ;
RIG_S = RIGI MOD_S MAT_S ;
* AMORTISSEMENT DE TYPE RAYLEIGH
F1 = 5.0 ;
F2 = 25.0 ;
KSI_S = 0.05 ;
ALPHA = 4.0 * PI * F1 * F2 / (F1 + F2) ;
BETA = 1.0 / (PI * (F1 + F2)) ;
AMO_S = KSI_S * ((ALPHA * MAS_S) ET (BETA * RIG_S)) ;
* SIGNAL SISMIQUE (SELON SPECTRE PS92 SITE S1)
LFR = PROG 0.1 0.5 1.0 2.5 5. 33. 50. ;
LSP = PROG 0.1 0.5 1.0 2.5 2.5 1.0 1.0 ;
SP0 = EVOL MANU 'FREQ(HZ)' LFR 'ACCE(M/S*S)' LSP ;
TAB = TABLE ;
TAB.'MOTIT' = 'SPECTRE PS92 S1 ' ;
TAB.'SEISME'= TABLE ;
TAB.'SEISME'.'SPECTRE' = SP0 ;
TAB.'SEISME'.'AMORT' = 0.05 ;
TAB.'SEISME'.'TYPSP' = 'ACCE' ;
TAB.'SIGNAL' = TABLE ;
TAB.'SIGNAL'.'ENVE' = 'PLATLIN' ;
TAB.'SIGNAL'.'NP' = 8 ;
TAB.'SIGNAL'.'DUREE' = 2.56 ;
TAB.'SIGNAL'.'TDEBUT' = 0.75 ;
TAB.'SIGNAL'.'TFIN' = 1.5 ;
TAB.'NBITER' = 5 ;
TAB.'NBSIGN' = 1 ;
TAB.'NALEAT' = 3 ;
TAB.'FRCOUP' = 49.9 ;
TAB.'OPTSORT' = 'SPECTRE' ;
TABSIG = SIGNSYNT FABR TAB ;
* MOYENNE ZERO, PLAGE INITIALE ZERO
LT0 = EXTR TABSIG.1 ABSC ;
LA0 = EXTR TABSIG.1 ORDO ;
DT = (EXTR LT0 2) - (EXTR LT0 1) ;
NP0 = DIME LT0 ;
LT1 = PROG 0. PAS DT 2.3 ;
LA1 = IPOL LT1 LT0 LA0 ;
NP1 = DIME LT1 ;
LA1 = LA1 - (PROG NP1 * ((SOMM LA1) / NP1)) ;
LA1 = (PROG 20 * 0.) ET LA1 ;
LT1 = PROG 0. PAS DT NPAS (19 + NP1) ;
ACC1 = EVOL MANU 'TEMPS(S)' LT1 'ACCE(M/S*S)' LA1 ;
SI (NEG GRAPH 'N');
DESS ACC1 MIMA NCLK;
FINSI ;
* DECONVOLUTION ET FRONTIERE ABSORBANTE
TAB = TABLE ;
TAB.1 = TABLE ;
TAB.1 .'FRONTIERE' = BOR ;
TAB.1 .'MASSE_VOLUMIQUE' = 2000. ;
TAB.1 .'POISSON' = 0.3 ;
TAB.1 .'YOUNG' = E1 ;
TAB.1 .'AMORTISSEMENT' = 0.05 ;
TYP_F = 'LYSMER' ;
FC = 50.0 ;
DIR = 'HORI' ;
TABS = DECONV TAB FON MOD_S DIR ACC1 F1 F2 FC TYP_F ;
* TABLE POUR LA PROCEDURE 'DYNAMIC'
CH_DEPI = MANU CHPO 3 SOL UR 0.0 UT 0.0 UZ 0.0 ;
CH_VITI = MANU CHPO 3 SOL UR 0.0 UT 0.0 UZ 0.0 ;
TAB_DYN = TABLE ;
TAB_DYN.'DEPL' = CH_DEPI ;
TAB_DYN.'VITE' = CH_VITI ;
TAB_DYN.'RIGI' = RIG_S ;
TAB_DYN.'MASS' = MAS_S ;
TAB_DYN.'AMOR' = AMO_S ET TABS.'AMOR' ;
TAB_DYN.'CHAR' = TABS.'CHAR' ;
TAB_DYN.'FREQ' = TABS.'FCDYN' ;
DT = TABS.'PAS' ;
NB_PAS = ENTI (2.51 / DT) ;
TAB_DYN.'DEBU' = 0.0 ;
TAB_DYN.'INST' = PROG 0.0 PAS DT NPAS (NB_PAS - 1) ;
TDYNA = DYNAMIC TAB_DYN ;
* POST-TRAITEMENT
POI = TABLE ;
POI.1 = P0 ;
POI.2 = P4 ;
NP = DIME POI ;
L_TEM = PROG NB_PAS * 0.0 ;
L_D = TABLE ;
L_V = TABLE ;
I = 1 ;
REPE B1 NP ;
L_V.I = PROG NB_PAS * 0.0 ;
I = I + 1 ;
FIN B1 ;
I_TEM = 0 ;
REPETER B2 NB_PAS ;
  I_TEM = I_TEM + 1 ;
  TEM_I = TDYNA.I_TEM.'TEMP' ;
  REMP L_TEM I_TEM TEM_I ;
  CHV_I = TDYNA.I_TEM.'VITE' ;
  I = 1 ;
    REPE B2_1 NP ;
    REMP L_V.I I_TEM (EXTR CHV_I POI.I UR) ;
  I = I + 1 ;
  FIN B2_1 ;
FIN B2 ;
* REPONSE EN ACCELERATION
LT1 = EXTR ACC1 ABSC ;
EV_VIT = TABLE ;
EV_ACC = TABLE ;
I = 1 ;
REPE B3 NP ;
EV_VIT.I = EVOL MANU L_TEM L_V.I ;
EV_ACC.I = DERIV1 EV_VIT.I ;
LT2 = EXTR EV_ACC.I ABSC ;
LA2 = EXTR EV_ACC.I ORDO ;
LA2 = IPOL LT1 LT2 LA2 ;
EV_ACC.I = EVOL MANU 'TEMPS(S)' LT1 'ACCE(M/S*S)' LA2 ;
I = I + 1 ;
FIN B3 ;
* COMPARAISON AVEC L'ACCELEROGRAMME IMPOSE
SI (NEG GRAPH 'N');
DESS ((COUL ROUG EV_ACC.1) ET (COUL VERT EV_ACC.2) ET ACC1) NCLK
TITR 'ACCELEROGRAMMES IMPOSE (BLEU) ET CALCULES (ROUGE ET VERT)' MIMA ;
FINSI ;
ERR1 = MAXI ABS (EXTR (EV_ACC.1 - ACC1) ORDO) ;
ERR2 = MAXI ABS (EXTR (EV_ACC.2 - ACC1) ORDO) ;
SI ((MAXI (PROG ERR1 ERR2)) > 0.01);
ERRE 5;
FINSI;
FIN ;
```
