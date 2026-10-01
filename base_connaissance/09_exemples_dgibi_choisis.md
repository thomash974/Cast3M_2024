# Exemples de cas tests commentés (compactés)

Sélection de cas tests représentatifs, pour l'usage typique : options, maillage, modèle, matériau, conditions aux limites, résolution, post-traitement, test de non-régression. Les cadres de commentaires et les alignements d'espaces ont été supprimés.

## channeldie3.dgibi [Mecanique Elastique]
```
* C H A N N E L D I E 3 . D G I B I
* Objet :
* Cas-test de validation des elements BBAR pour les elements tetra-
* edre, pyramide et hexaerdre lineaires.
* Calcul elastique de la compression d'un lopin de metal place dans
* une matrice l'empechant de se dilater lateralement (lopin coince dans
* un "canal", d'ou "channel die").
* Validation du calcul par comparaison a la solution analytique.
* Un 2nd chargement en deplacement impose sur la face superieure,
* non uniforme en espace (varaition quadratique), permet de valider
* l'integration dans les elements en verifiant que la pression est
* est bien sous-integree (champ constant dans l'element), ainsi que
* l'equilibre (F-Bsig).
* Verification du fonctionnement de l'operateur MASSE.
* Verification du fonctionnement de l'operateur KSIG.
* Description :
* Type de calcul : Mecanique Elastique
* Mode de calcul : 3D
* Type d'element : TET4, PYR5, CUB8
* Chargement : Deplacement impose
opti dime 3 mode TRID elem TET4 ;
* Pour affichages, mettre ig1 a VRAI :
ig1 = faux ;
* ------------------------------ MAILLAGE ------------------------------
* Points :
p1 = 0. 0. 0. ;
p2 = 100. 0. 0. ;
p3 = 100. 100. 0. ;
p4 = 0. 100. 0. ;
p5 = 0. 0. 100. ;
* Contour base :
ne1 = 5 ;
li1 = d ne1 p1 p2 ;
li2 = d ne1 p2 p3 ;
li3 = d ne1 p3 p4 ;
li4 = d ne1 p4 p1 ;
* Surface et Volume :
sur1 = dall li1 li2 li3 li4 'PLAN' ;
vol1 = volu tran sur1 p5 ne1 ;
sur2 = vol1 face 2 ;
sx0 = (enve vol1) poin plan p1 P4 p5 1.e-3 ;
sx0 = (enve vol1) elem appu stri sx0 ;
sy0 = (enve vol1) poin plan p1 P2 p5 1.e-3 ;
sy0 = (enve vol1) elem appu stri sy0 ;
sur3 = sx0 et sy0 ;
sur4 = (vol1 face 3) diff sur3 ;
sur3 = sur3 chan tri3 ;
sur0 = sur1 et sur2 et sur3 et sur4 ;
opti elem tet4 ;
vol1 = volu (sur1 et sur2 et sur3 et sur4) ;
list (vol1 elem type) ;
si ig1 ;
  trac cach vol1 titr 'Maillage lopin' ;
fins ;
* --------------------- MODELE / CARACTERISTIQUES ----------------------
* Valeurs modules d'elasticite :
ym1 = 1.5e11 ;
nu1 = 0.499 ;
* Modele et caracteristiques mecaniques :
mod1 = modele vol1 'MECANIQUE' 'ELASTIQUE' 'ISOTROPE' 'BBAR' ;
mat1 = mate mod1 'YOUNG' 1.5e11 'NU' nu1 'RHO' 7.6e3 ;
* Matrice de raideur :
rig1 = rigi mod1 mat1 ;
mas1 = mass mod1 mat1 ;
* ----------------------- CONDITIONS AUX LIMITES -----------------------
* Definition des points d'interet :
ptx0 = (vol1 coor 1) poin mini ;
pty0 = (vol1 coor 2) poin mini ;
ptz0 = sur1 ;
ptz1 = sur2 ;
clx0 = bloq ux ptx0 ;
cly0 = bloq uy pty0 ;
clz0 = bloq uz ptz0 ;
clz1 = bloq uz ptz1 ;
cl0 = clx0 et cly0 et clz0 et clz1 ;
* Affichages points CL :
si ig1 ;
  trac ((ptx0 coul roug) et (aret vol1)) titr 'Points Ux = 0' ;
  trac ((pty0 coul roug) et (aret vol1)) titr 'Points Uy = 0' ;
  trac ((ptz0 coul roug) et (ptz1 coul rouge) et (aret vol1)) titr 'Points Uz = 0 (surfaces bloquees par matrice)' ;
fins ;
* ----------------------------- CHARGEMENT -----------------------------
* Deplacement impose essai channel die :
Uy1 = -0.1 ;
pty1 = (vol1 coor 2) poin maxi ;
cly1 = bloq uy pty1 ;
dcl1 = depi cly1 Uy1 ;
* Deplacement impose non homogene :
ptx1 = (vol1 coor 1) poin maxi ;
clx1 = bloq ux ptx1 ;
chy1 = ptz1 coor 2 ;
Uz1 = (((-0.01 * (chy1 - 100.)) ** 2) / -100.) nomc uz ;
dcl2 = depi clz1 Uz1 ;
si ig1 ;
  trac ((pty1 coul vert) et (aret vol1)) titr 'Points deplacement Uy impose essai channel die' ;
  trac Uz1 ptz1 titr '2nd chargement : deplacement non homogene' ;
fins ;
* ---------------------------- DEPLACEMENTS ----------------------------
* Solution analytique au point P3:
UxAna1 = -1. * nu1 / (1. - nu1) * Uy1 ;
* Solution Castem au point P3: uycas.
deptot = reso (rig1 et cl0 et cly1) dcl1 ;
dep2 = reso (rig1 et cl0 et cly1 et clx1) dcl2 ;
* deplacement Ux au point P3 :
UxSim1 = extr deptot 'UX' p3 ;
* Deformee :
def0 = defo deptot (aret vol1) 0. blan ;
def1 = defo deptot (aret vol1) 100 roug ;
mot1 = chai format '(F7.4)' 'deformee (vue de dessus) : Ux =' UxSim1 ;
si ig1 ;
  trac (0 0 1.e6) (def0 et def1) titr mot1 ;
fins ;
opti oeil (1.e6 -1.e6 0.8e6) ;
* Calcul de l'erreur sur le déplacement.
err1 = abs (( UxAna1 - UxSim1 ) / ( UxAna1 )) ;
* ---------------------------- CONTRAINTES -----------------------------
* Solution analytique:
syyana1 = ym1 / (1. - (nu1 * nu1)) * uy1 / 100. ;
szzana1 = nu1 * syyana1 ;
prana1 = syyana1 + szzana1 / 3. ;
* Solution Castem : pression maximale = maxpres1.
sig1 = sigma mod1 deptot mat1 ;
* Validation KSIG avec BBAR :
ksg1 = ksigm mod1 sig1 ;
depto2 = reso (rig1 et ksg1 et cl0 et cly1) dcl1 ;
err6 = maxi abs (deptot - depto2) avec (mots ux uy uz) ;
* Affichage :
si ig1 ;
  trac sig1 mod1 titr 'Champ de contrainte' ;
fins ;
* Calcul de la pression :
syySim1 = exco 'SMYY' sig1 'P' ;
szzSim1 = exco 'SMZZ' sig1 'P' ;
prSim1 = (syySim1 + szzSim1) / 3. ;
syySim1 = mini syySim1 ;
szzSim1 = mini szzSim1 ;
prSim1 = mini prSim1 ;
* Calcul de l'erreur sur les contraintes :
err2 = ((syyana1 - syySim1) / syyana1) + ((szzana1 - szzSim1) / szzana1) + ((prana1 - prSim1) / prana1) ;
err2 = abs err2 ;
* Verification integration pression chargement non homogene :
sig2 = sigm mod1 mat1 dep2 ;
p2 I2 I3 = inva mod1 sig2 ;
* Dans prismes :
el1 = (vol1 elem tet4) elem 1 ;
model1 = redu mod1 el1 ;
pmax1 pmin1 = (maxi (redu p2 model1)) (mini (redu p2 model1)) ;
err3 = (maxi abs (pmax1 - pmin1)) / (maxi abs pmax1) ;
* Dans hexaedres :
el2 = (vol1 elem pyr5) elem 1 ;
model2 = redu mod1 el2 ;
pmax2 pmin2 = (maxi (redu p2 model2)) (mini (redu p2 model2)) ;
err4 = (maxi abs (pmax2 - pmin2)) / (maxi abs pmax2) ;
* Verification equilibre chargement non homogene :
bsg2 = bsig mod1 sig2 ;
rea2 = reac (cl0 et cly1 et clx1) dep2 ;
res2 = rea2 - bsg2 ;
err5 = (maxi abs res2) / (maxi abs rea2) ;
* Affichages solution chargement non homogene :
si ig1 ;
  trac (defo vol1 dep2 2.e3) cach titr ' Deformee chargement non homogene' ;
  trac sig2 mod1 titr ' Contraintes chargement non homogene' ;
* Affichage valeur champs aux points d'integration :
  list (redu sig2 model1) ;
  list (redu p2 model1) ;
  list (redu sig2 model2) ;
  list (redu p2 model2) ;
fins ;
* ----------------------------- VALIDATION -----------------------------
* Affichages :
opti echo 0 ; saut 1 lign ;
mess (chai format '(F6.2)' ' > Erreur relative deplacement au point P3 =' err1) ;
mess (chai format '(F6.2)' ' > Erreur relative contraintes et pression =' err2) ;
opti echo 1 ; saut 1 lign ;
* Test de validation:
err0 = maxi abs (prog err1 err2 err3 err4 err5) ;
prec0 = (vale prec) ** 0.5 * 10. ;
list err0 ;
list err1 ;
list err2 ;
list err3 ;
list err4 ;
list err5 ;
list err6 ;
list prec0 ;
si ( err0 >eg prec0 ) ;
  erreur 5 ;
finsi ;
fin;
```
## dependance.dgibi [Mecanique Plastique]
```
* TEST DE CONDENSATION
* poutre des section rectangulaire en appui simples
* face inferieure renforcee par une plaque en acier
* un renfort interne de type poutre
* un renfort interne de type barr
* les renforts sont disjoints du maillage massif
* comparaison des solutions obtenues par :
* rela accro / resou
* dependance / resou
* cmct / resou + mrem
* test de fonctionnement dans pasapas
opti echo 1;
graph='N' ;
opti dime 3 elem cub8 ;
* GEOMETRIE
long = 10.0;
* ---BETON
h = 1.;
h1= .9 ;
* h1 = 1. - (1./6.1);
pa=0.0 0. 0.0;
pb=long 0. 0.0;
pc=long 0. h ;
pd=0.0 0. h;pn = 0. 0. (h - h1) ;
* ---ARMATURE
prof = 1. ;
pm = long (prof/2) (h - h1) ;
pn = 0. (prof/2) (h - h1) ;
nb1 = 20;
nb2 = 4 ;
nb3=17 ;
c1=pa droi nb1 pb;
c2=pb droi nb2 pc;
c3=pc droi nb1 pd;
c4=pd droi nb2 pa;
sur1=(dall c1 c2 c3 c4) ;
sur1 = sur1 volu 2 tran (0 prof 0) ;
d1 = d nb3 pm pn coul roug ;
d2 = d1 plus ( 0 0 h1 ) ;
   finf = sur1 points plan pa pb (pa plus (0 1 0)) .01 ;
   finf = (( sur1 envel) elem appu stric finf ) ;
   fsup = finf plus (0 0 h) ;
   elim .1 sur1 fsup ;
* ----- on decolle la plaque pour pouvoir l ACCROCHER
 plaq = finf plus ( 0 0 0 ) coul bleu ;
'SI' ( 'NEG' graph 'N' ) ;
 trac (1000 1000 1000 ) ( sur1 et d1) ;
'FINSI' ;
* MODELE
* ------------------------- beton ---------------------------------
Eb = 0.4e11 ;
modb= 'MODE' sur1 mecanique elastique ;
matb= 'MATE' modb youn Eb nu 0.3;
ribe = rigi modb matb;
* ----------------------- barre ----------------------------
YOUCAB = 1495.D6/0.718D-2 ; ;
leps1 = 1.D-2 * (PROG 0. .718 .804 .890 1.00 1.278 2.957) ;
lsig1 = 1.D6 * (PROG 0. 1495. 1553. 1623. 1669. 1727. 1855.) ;
TRACAB = EVOL MANU 'EPS' leps1 'SIG' lsig1 ;
ym1 = (extr lsig1 2) / (extr leps1 2) ;
lsig1 = lsig1 enle 1 ;
lepsp1 = (leps1 enle 1) - (lsig1 / ym1) ;
trecro = evol vert manu 'EPS' lepsp1 'SIG' lsig1 ;
'SI' ( 'NEG' graph 'N' ) ;
  dess (TRACAB et trecro) titr ' Courbes de traction et d ecrouissage (vert)' ;
fins ;
mod1 = MODE d1 MECANIQUE ELASTIQUE ISOTROPE PLASTIQUE ISOTROPE BARR ;
mat1= MATE mod1 YOUN youcab NU 0.3 SECT 0.04 'ECRO' trecro ALPH 12.5E-6 ;
riba = rigi mod1 mat1 ;
* ------------------- - poutre -----------------------
mod2= 'MODE' d2 mecanique elastique pout ;
mat2=( 'MATE' mod2 youn Eb nu 0.0 INRY 10. INRZ 10. TORS 3.)
      et ( cara mod2 sect .02) ;
ripo = rigi mod2 mat2 ;
* --------------------- coque -------------------------
* ---- Courbe d'écrouissage de l'acier A42
EPS1 = PROG 0. 0.002 0.018 0.02 0.036 0.05 0.068 0.084 0.102 ;
SIG1 = PROG 0. 312. 325. 335. 400. 425. 450. 465. 475. ;
SIG1 = SIG1*1.E6 ;
EVSIG = EVOL MANU 'EPS' EPS1 'SIG' SIG1 ;
ym1 = (extr sig1 2) / (extr eps1 2) ;
sig1 = sig1 enle 1 ;
eps1 = (eps1 enle 1) - (sig1 / ym1) ;
EVECR = EVOL vert MANU 'EPS' EPS1 'SIG' SIG1 ;
'SI' ( 'NEG' graph 'N' ) ;
  dess (EVSIG et EVECR) titr ' Courbes de traction et d ecrouissage (vert)' ;
fins ;
* ---- Module de Young de la Peau d'étanchéité
YOUNT = 312.E6 / 0.002 ;
mod3 = mode plaq MECANIQUE ELASTIQUE ISOTROPE
     PLASTIQUE ISOTROPE coq4 ;
Mat3 = MATE mod3 YOUN YOUNT NU 0.3 EPAI 0.03 ecro EVecr ALPH 12.5E-6 ;
rico = rigi mod3 mat3 ;
* CONDITIONS AUX LIMITES
aa = sur1 points droite pa ( pa plus (0 1 0)) .01 ;
bb = sur1 points droite pb ( pb plus (0 1 0)) .01 ;
cl1 = bloq aa ux ;
cl2 = bloq aa uz ;
cl3 = bloq bb uz ;
cl4 = bloquer uy ( pa et pb) ;
clb = cl1 et cl2 et cl3 et cl4 ;
* on veut bloquer la rotation sur elle meme de la poutre
       dp2 = d2 elem ( lect 1 pas 1 ( nb3 - 1)) ;
       pf = d2 point final ;
 conf pf ( sur1 point proche pf ) ;
 clt = clb et ( bloquer RX pf ) ;
 racc = rela accro (plaq et d1 et dp2 ) sur1 ;
 radd = chan DEPE racc ;
* ------ concatenation des raideurs ------------
 rign = ribe et riba et ripo et rico ;
 riga = rign et racc et clt ;
 rigd = rign et radd et clt ;
* --- pression sur face superieure + force sur la plaque -----
MOP = 'MODE' fsup 'CHARGEMENT' 'PRESSION' ;
PRZ = 'PRES' MOP pres 1.e8 ;
f1 = bsig mop PRZ ;
   f2 = force 1.E8 FZ plaq ;
   ff = f1 + f2 ;
* -------------- solution par depend-------------------------
   dep2 = resou rigd ff ;
* -------------- solution par accro -------------------------
   dep1 = resou riga ff ;
* ------------- solution par cmct puis mrem ------------
* --- condensation des matrices liees aux noeuds esclaves ---
   rige = cmct (rign et clt ) radd ;
* --- condensation des la force liees aux noeuds esclaves -----
   racd radu = chan COND racc ;
   fad = f1 et ( radu * f2 ) ;
* ----- solution reduite ---------------------------------------
* dep30 = resou rige fad ;
* -- remeontee a la solution complete --------------------------
* on n'utilise plus tout cela, c'est intégré dans résou
* dep3 = mrem dep30 (rign et clt et radd ) ff ;
   dep3 = resou rige fad ;
   mde1 = mini dep1 avec ( mots UZ) ;
   mde2 = mini dep2 avec ( mots UZ) ;
   mde3 = mini dep3 avec ( mots UZ) ;
   surd = (sur1 envel ) et d1 et d2 ;
* ----------- reactions aux appuis et liaisons ---------------------
 rea1 = reac (clt et racc ) dep1 ;
 rea2 = reac (clt et radd ) dep2 ;
* ----------examen des differences entre les deux methodes ----------
aaa = rea1 - rea2 ;
reamo1 = (psca rea1 rea1 ( mots FX FY FZ) ( mots FX FY FZ)) ** .5 ;
reamo2 = (psca rea2 rea2 ( mots FX FY FZ) ( mots FX FY FZ)) ** .5 ;
depmod = (psca dep1 dep1 ( mots UX UY UZ) ( mots UX UY UZ)) ** .5 ;
    si ( neg GRAPH N) ;
 av = maxi ( abs rea1 ) avec (mots FZ) ;
 amv = 4./av ;
 vr1 = vecteur rea1 amv FX FY FZ roug ;
 vr2 = vecteur rea2 amv FX FY FZ vert ;
 amp = .3/ ( maxi depmod) ;
 amd = 4./(maxi reamo1) ;
 vd1 = vecteur rea1 amd FX FY FZ roug ;
 vd2 = vecteur rea2 amd FX FY FZ vert ;
 titre 'UZ mini accro ' mde1 ' dependence ' mde2 'cmct' mde3 ;
 dde0 = defo surd dep1 0. blan ;
 dde1 = defo surd dep1 amp vr1 roug ;
 dde2 = defo surd dep2 amp vr2 vert ;
 trac ( dde1 et dde2 ) ;
 dur1 = defo surd dep1 amp vd1 roug ;
 dur2 = defo surd dep2 amp vd2 vert ;
  trac ( dur1 et dur2 ) ;
vdif = vecteur aaa FX FY FZ amd vert ;
titre '  difference  sur reactions  accro depen ' ;
trac surd vdif ;
    finsi ;
rdif = reamo1 - reamo2 ;
a3= rdif point maxi ;
av1 = (abs (maxi rdif)) /( extr reamo1 SCAL (a3 point 1 )) ;
ruz = abs (((mde1 - mde2) * 100 ) / mde2 ) ;
mess ' differences relatives max sur la fleche maximum ' ruz '%' ;
mess ' differences relatives max sur les reactions     ' av1 '%' ;
 'SI' (( ruz > 1.e-7) OU ( av1 > 1.e-7));
 erre 5 ;
 'FINSI' ;
* suite uniquement pour tester que tout se passe correctement ds pasapas
evf = EVOL MANU 'Sec.' (prog 0. 1000.) 'Pa' (prog 1. 1. ) ;
chforce = char meca f2 evf ;
chpress = char pres prz evf ;
TABMC = TABLE ;
TABMC.MODELE = modb et mod1 et mod2 et mod3 et mop ;
TABMC.BLOCAGES_MECANIQUES = radd et clt ;
TABMC.CARACTERISTIQUES = matb et mat1 et mat2 et mat3 ;
TABMC.CHARGEMENT = chpress et chforce ;
evtt = prog 0. pas 1. 5.;
TABMC.TEMPS_CALCULES = evtt ;
TABMC.TEMPS_SAUVES = evtt ;
TABMC.'HYPOTHESE_DEFORMATIONS' = 'LINEAIRE' ;
PASAPAS TABMC ;
ttt = tabmc.'DEPLACEMENTS' ;
i1 = index ttt ;nt = dime i1 ;
dep = ttt . (i1.nt ) ;uref = -8.94153E-02 ;
uymi = mini dep avec (mots UZ) ;
* fleche attendue 5 iterations =-8.94153E-02 ;
ruz = abs (((uref - uymi) * 100 ) / (abs uymi )) ;
mess ' difference relative ' ruz '%' ;
 'SI' ( ruz > 5.e-1) ;
 erre 5 ;
 'FINSI' ;
 'FIN' ;
```
## adve_01.dgibi [Thermique Advection]
```
* Cas-test de l'operateur ADVEction dans la formulation THERMIQUE
* Comparaison a une solution analytique.
* On calcule la temperature d'un fluide qui s'ecoule dans un tuyau
* chauffe sur toute sa longueur.
* On verifie la temperature du fluide en sortie du tuyau.
* La puissance lineique est de : 500 W/m
* La temperature en entree est de : 20°C
* La vitesse d'ecoulement est de  : 25 cm/s
* La section du tuyau est de : 5.e-5 m2, diametre ~ 8 mm
* La longueur du tuyau est de : 5 m
* La temperature attendue en sortie est de : 70°C
* On utilise les elements lineaires et quadratiques (TUY2,TUY3)
'OPTI' 'DIME' 3 'ELEM' 'SEG2' ;
* Commentez cette ligne pour voir les traces :
'OPTI' 'TRAC' 'PSC' ;
O1 = 0 0 0 ;
X1 = 1 0 0 ;
P1 = 2.5 * X1 ;
P2 = 5.0 * X1 ;
Y1 = 0 1 0 ;
Z1 = 0 0 1 ;
L1 = O1 'DROI' 5 P1 'COUL' 'VERT' ;
L2 = P1 'DROI' 10 P2 ;
L2 = 'CHAN' 'QUAD' L2 'COUL' 'BLEU' ;
'TITR' ' Maillage du tuyau, longueur = 5 m (Vert=SEG2,Bleu=SEG3) ' ;
'TRAC' 'QUAL' (L1 'ET' L2) ;
mo1 = 'MODE' L1 thermique advection 'TUY2' ;
mo2 = 'MODE' L2 thermique advection 'TUY3' ;
mo1 = mo1 'ET' mo2 ;
L0 = L1 'ET' L2 ;
* Le flux advectee dans un tuyau est J = Rho.Cp.Sect.V :
ma1 = 'MATE' mo1 'RHO' 1.e3 'C' 4.e3 'VITE' 0.25 'SECT' 5.e-5 ;
sq1 = 'SOUR' mo1 ma1 L0 (5.e2 / 5.e-5) ;
list (MAXI (resu sq1));
'TITR' ' Terme source le long du tuyau ' ;
'DESS' ('EVOL' 'VERT' 'CHPO' sq1 L0 'Q') 'YBOR' 0. 300. ;
KA1 = 'ADVE' mo1 ma1 ;
cl1 = 'BLOQ' T O1 ;
dcl1 = 'DEPI' cl1 20. ;
cht2 = 'RESO' (ka1 'ET' cl1) (sq1 'ET' dcl1);
'TITR' ' Evolution de la temperature le long du tuyau ' ;
'DESS' ('EVOL' 'VERT' 'CHPO' cht2 L0 T) ;
* Test :
tref1 = 70. ;
tp1 = 'EXTR' cht2 T P2 ;
err1 = 'ABS' (TREF1 - tp1) / tp1 ;
'OPTI' 'ECHO' 0 ;
'MESS' ;
mot1 = 'CHAI' ' > Temperature calculee en  sortie = '
  'FORMAT' '(F3.0)' tp1 '°C pour 70°C attendu ' ;
'MESS' mot1 ;
'MESS' ' > Erreur relative = ' err1 ;
'MESS' ;
'OPTI' 'ECHO' 1 ;
'SI' (err1 > 1.e-5) ;
  'ERRE' 5 ;
'SINO' ;
  'OPTI' 'ECHO' 0 ;
  'MESS' ;
  'MESS' ' > Test reussi ' ;
  'MESS' ;
'FINS' ;
'FIN' ;
```
## burgerpsi.dgibi [Fluides Convection]
```
NX = 30 ; NY = 30 ;
NITER = 200 ;
CFL = 0.8 ;
GRAPH = 'N' ;
opti isov suli ;
* EQUATION DE CONVECTION NON-LINEAIRE Ut + div (F(U)) = 0
* RESOLUE SOUS FORME NON-CONSERVATIVE
* dU/dt + lambda . nabla U = 0 avec lambda = dF/dU
* AVEC L'OPTION PSI (POSITIVE STREAMWISE INVARIANT)
* PROCEDURE POUR TRACER COUPES
DEBPROC TRCE ;
ARGU M*'MAILLAGE' ;
nb = nbel M ;
R = (M poin 1) droi 1 (M poin 2) ;
i=2 ; itma = nb-2 ;
repeter bloc1 itma ;
R = R et ((M poin i) droi 1 (M poin (i+1))) ;
i=i+1 ;
fin bloc1 ;
FINPROC R ;
* PROCEDURE POUR CALCULER CHAMP DE VITESSE ET
* TESTER LA CONVERGENCE
DEBPROC CALCUL ;
ARGU RVX*'TABLE' ;
RV = RVX.'EQEX' ;
CN = RV.INCO.'CN' ;
DD = RV.PASDETPS.'NUPASDT' ;
NN = DD/5 ;
LO = (DD-(5*NN)) EGA 0 ;
SI ( LO ) ;
ERR = KOPS (RV.INCO.'CN') - (RV.INCO.'CNM1') ;
ELI = MAXI ERR 'ABS' ;
ELI = (LOG (ELI + 1.0E-20))/(LOG 10.) ;
MESSAGE 'ITER ' RV.PASDETPS.'NUPASDT' '   ERREUR LINF ' ELI ;
IT = PROG RV.PASDETPS.'NUPASDT' ;
ER = PROG ELI ;
RV.INCO.'IT' = (RV.INCO.'IT') ET IT ;
RV.INCO.'ER' = (RV.INCO.'ER') ET ER ;
FINSI ;
VY = KCHT $DOMTOT 'SCAL' 'SOMMET' 'COMP' 'UY' 1.0 ;
VX = NOMC 'UX' CN ;
VV = KCHT $DOMTOT 'VECT' 'SOMMET' 'COMP' (MOTS 'UX' 'UY')
        (VX ET VY) ;
RV.INCO.'VITESSE' = VV ;
RV.INCO.'CNM1' = KCHT $DOMTOT 'SCAL' 'SOMMET' (RV.INCO.'CN') ;
as2 ama1 = 'KOPS' 'MATRIK' ;
FINPROC as2 ama1 ;
opti dime 2 ;
opti elem tri3 ;
titre 'Equation de Burger' ;
* DIFFUSION
DIF = 1.0E-10 ;
* MAILLAGE
A1 = 0.0 0.0 ;
A2 = 1.0 0.0 ;
A3 = 1.0 1.0 ;
A4 = 0.0 1.0 ;
FBAS = A1 'DROI' NX A2 ;
FDRO = A2 'DROI' NY A3 ;
FHAU = A3 'DROI' NX A4 ;
FGAU = A4 'DROI' NY A1 ;
PA1 = FBAS POIN 'PROC' A1 ;
PA2 = FBAS POIN 'PROC' A2 ;
P12 = CHAN POI1 FBAS ;
MA1 = P12 ELEM 'CONTENANT' PA1 ;
MA2 = P12 ELEM 'CONTENANT' PA2 ;
DOMTOT = 'DALL' FBAS FDRO FHAU FGAU 'PLAN' ;
* CREATION MODELE NAVIER-STOKES
XDOMTOT = CHAN DOMTOT QUAF ;
XFBAS = CHAN FBAS QUAF ;
ELIM (XDOMTOT ET XFBAS) 1.E-3 ;
$DOMTOT = MODE XDOMTOT 'NAVIER_STOKES' LINE ;
$FBAS = MODE XFBAS 'NAVIER_STOKES' LINE ;
* INITIALISATION DU CHAMP DE VITESSE
VX = KCHT $DOMTOT 'SCAL' 'SOMMET' 'COMP' 'UX' 0.0 ;
VY = KCHT $DOMTOT 'SCAL' 'SOMMET' 'COMP' 'UY' 1.0 ;
CHVIT=KCHT $DOMTOT 'VECT' 'SOMMET' 'COMP' (MOTS 'UX' 'UY') (VX ET VY) ;
* PROFIL DE LA SOLUTION A L'ENTREE
XBAS = COOR 1 FBAS ;
XBAS = NOMC 'UX' XBAS ;
SOLUTION = 1.5 - (2.0*XBAS) ;
CHP1 = KCHT $FBAS 'SCAL' 'SOMMET' 'COMP' 'UX' SOLUTION ;
CHP1 = NOMC 'CN' CHP1 ;
* TABLE DE RESOLUTION
RV = EQEX $DOMTOT 'ITMA' NITER 'ALFA' CFL
        'ZONE' $DOMTOT
        'OPER' CALCUL
        'OPTI' 'PSI'
        'OPER' TSCAL DIF 'VITESSE' 0.0 'INCO' 'CN'
        'OPTI' 'CENTREE'
        'OPER' 'DFDT' 1. 'CN' 'DELTAT' 'INCO' 'CN'
        'CLIM' 'CN' 'TIMP' FBAS CHP1
        'CLIM' 'CN' 'TIMP' FGAU 1.5
        'CLIM' 'CN' 'TIMP' FDRO (-0.5)
        'CLIM' 'CN' 'TIMP' MA1 (-1.5)
        'CLIM' 'CN' 'TIMP' MA2 (0.5) ;
RV.INCO = TABLE 'INCO' ;
RV.INCO.'CN' = KCHT $DOMTOT 'SCAL' 'SOMMET' 0. ;
RV.INCO.'VITESSE'= CHVIT ;
RV.INCO.'CNM1' = KCHT $DOMTOT 'SCAL' 'SOMMET' 1. ;
RV.INCO.'IT' = PROG 1 ;
RV.INCO.'ER' = PROG 0. ;
EXEC RV ;
* ANALYSE DES RESULTATS
MESSAGE 'MAX = ' (MAXI RV.INCO.'CN') 'MAXTHEORIQUE = 1.5 ' ;
MESSAGE 'MIN = ' (MINI RV.INCO.'CN') 'MINTHEORIQUE = -0.5 ' ;
SI ( (MINI RV.INCO.'ER') > -4.0 ) ;
            ERREUR 5 ;
FINSI ;
SI ( (MAXI RV.INCO.'CN') > 1.50001D0 ) ;
            ERREUR 5 ;
FINSI ;
SI ( (MINI RV.INCO.'CN') < -0.50001D0 ) ;
            ERREUR 5 ;
FINSI ;
SI ( 'EGA' graph 'O') ;
TRAC DOMTOT ;
TRAC DOMTOT (RV.INCO.'CN') (CONT DOMTOT) 14 ;
P1 = DOMTOT POIN 'PROC' (0.0 0.7) ;
P2 = DOMTOT POIN 'PROC' (1.0 0.7) ;
P1P2 = DOMTOT POIN 'DROI' P1 P2 0.01 ;
LI12 = TRCE P1P2 ;
XX = COOR 1 LI12 ;
EVOL1 = EVOL 'CHPO' (RV.INCO.'CN') SCAL LI12 ;
EVOL2 = EVOL 'CHPO' XX SCAL LI12 ;
LIX = 'EXTR' EVOL2 ORDO ;
LIU = 'EXTR' EVOL1 ORDO ;
EVOL3 = EVOL 'MANU' 'X' LIX 'U(X)' LIU ;
EVOL3 = EVOL3 'COUL' VERT ;
EVOL4 = EVOL 'MANU' 'ITERATIONS' (RV.INCO.'IT') 'LOG|E|inf'
           (RV.INCO.'ER') ;
EVOL4 = EVOL4 'COUL' VERT ;
FINSI ;
opti elem qua4 ;
DOMTOT = 'DALL' FBAS FDRO FHAU FGAU 'PLAN' ;
* CREATION MODELE NAVIER-STOKES
XDOMTOT = CHAN DOMTOT QUAF ;
XFBAS = CHAN FBAS QUAF ;
ELIM (XDOMTOT ET XFBAS) 1.E-3 ;
$DOMTOT = MODE XDOMTOT 'NAVIER_STOKES' LINE ;
$FBAS = MODE XFBAS 'NAVIER_STOKES' LINE ;
* PROFIL DE LA SOLUTION A L'ENTREE
XBAS = COOR 1 FBAS ;
XBAS = NOMC 'UX' XBAS ;
SOLUTION = 1.5 - (2.0*XBAS) ;
CHP1 = KCHT $FBAS 'SCAL' 'SOMMET' 'COMP' 'UX' SOLUTION ;
CHP1 = NOMC 'CN' CHP1 ;
* TABLE DE RESOLUTION
CFL = 0.2 ;
RV = EQEX $DOMTOT 'ITMA' NITER 'ALFA' CFL
        'ZONE' $DOMTOT
        'OPER' CALCUL
        'OPTI' 'PSI'
        'OPER' TSCAL DIF 'VITESSE' 0.0 'INCO' 'CN'
        'OPTI' 'CENTREE'
        'OPER' 'DFDT' 1. 'CN' 'DELTAT' 'INCO' 'CN'
        'CLIM' 'CN' 'TIMP' FBAS CHP1
        'CLIM' 'CN' 'TIMP' FGAU 1.5
        'CLIM' 'CN' 'TIMP' FDRO (-0.5)
        'CLIM' 'CN' 'TIMP' MA1 (-1.5)
        'CLIM' 'CN' 'TIMP' MA2 (0.5) ;
RV.INCO = TABLE 'INCO' ;
RV.INCO.'CN' = KCHT $DOMTOT 'SCAL' 'SOMMET' 0. ;
RV.INCO.'VITESSE'= CHVIT ;
RV.INCO.'CNM1' = KCHT $DOMTOT 'SCAL' 'SOMMET' 1. ;
RV.INCO.'IT' = PROG 1 ;
RV.INCO.'ER' = PROG 0. ;
EXEC RV ;
* ANALYSE DES RESULTATS
MESSAGE 'MAX = ' (MAXI RV.INCO.'CN') 'MAXTHEORIQUE = 1.5 ' ;
MESSAGE 'MIN = ' (MINI RV.INCO.'CN') 'MINTHEORIQUE = -0.5 ' ;
SI ( (MINI RV.INCO.'ER') > -4.0 ) ;
            ERREUR 5 ;
FINSI ;
SI ( (MAXI RV.INCO.'CN') > 1.50001D0 ) ;
            ERREUR 5 ;
FINSI ;
SI ( (MINI RV.INCO.'CN') < -0.50001D0 ) ;
            ERREUR 5 ;
FINSI ;
* TRACE DES RESULTATS
SI ( 'EGA' graph 'O') ;
UEXACT = KCHT $DOMTOT 'SCAL' 'SOMMET' 0. ;
XX YY = 'COOR' (DOMA $DOMTOT SOMMET) ;
REPETER BLOC1 (NBNO DOMTOT) ;
P1 = (DOMA $DOMTOT SOMMET) POIN &BLOC1 ;
X1 = 'EXTR' XX 'SCAL' P1 ;
Y1 = 'EXTR' YY 'SCAL' P1 ;
D1 = Y1 - (0.5*X1/0.75) ;
D2 = Y1 - (2.0*(1.0-X1)) ;
D3 = Y1 - 1.0 - (2.0*(X1-1.0)) ;
BO1 = ( D1 > 0.) ;
BO2 = ( D2 > 0.) ;
BO3 = ( D3 > 0.) ;
SI ( BO1 ET BO3 ) ;
U1 = 1.5 ;
SINON ;
SI ( (NON BO1) ET (NON BO2) );
U1 = (1.5-(2.0*X1))/(1.-(2.0*Y1)) ;
SINON ;
U1 = -0.5 ;
FINSI ;
FINSI ;
C1 = MANU 'CHPO' P1 1 SCAL U1 ;
C2 = KCHT $DOMTOT 'SCAL' 'SOMMET' C1 ;
UEXACT = (UEXACT ET C2) ;
FIN BLOC1 ;
TRACE DOMTOT ;
TRAC DOMTOT (RV.INCO.'CN') (CONT DOMTOT) 14 ;
P1 = DOMTOT POIN 'PROC' (0.0 0.7) ;
P2 = DOMTOT POIN 'PROC' (1.0 0.7) ;
P1P2 = DOMTOT POIN 'DROI' P1 P2 0.01 ;
LI12 = TRCE P1P2 ;
XX = COOR 1 LI12 ;
EVOL1 = EVOL 'CHPO' (RV.INCO.'CN') SCAL LI12 ;
EVOL2 = EVOL 'CHPO' XX SCAL LI12 ;
LIX = 'EXTR' EVOL2 ORDO ;
LIU = 'EXTR' EVOL1 ORDO ;
EVOL33 = EVOL 'MANU' 'X' LIX 'U(X)' LIU ;
EVOL33 = EVOL33 'COUL' 'TURQ' ;
EVOL44 = EVOL 'CHPO' UEXACT SCAL LI12 ;
LIUEX = 'EXTR' EVOL44 ORDO ;
EVOL55 = EVOL 'MANU' 'X' LIX 'UEXACT(X)' LIUEX ;
EVOL55 = EVOL55 'COUL' 'ROUG' ;
TAB1 = TABLE ;
TAB1.1 = 'MARQ TRIA' ;
TAB1.2 = 'MARQ CARR' ;
TAB1.'TITRE' = TABLE ;
TAB1.'TITRE' . 1 = 'MOT' 'TRIANGLE' ;
TAB1.'TITRE' . 2 = 'MOT' 'QUADRANGLE' ;
TAB1.'TITRE' . 3 = 'MOT' 'EXACT' ;
DESS (EVOL3 ET EVOL33 ET EVOL55) 'XBOR' 0.0 1.0 'YBOR' -1. 2.
                'TITR' 'Coupe a y=0.7' LEGE TAB1 ;
EVOL6 = EVOL 'MANU' 'ITERATIONS' (RV.INCO.'IT') 'LOG|E|inf'
           (RV.INCO.'ER') ;
EVOL6 = EVOL6 COUL TURQ ;
DESS (EVOL4 ET EVOL6) 'XBOR' 0. 1000. 'YBOR' -10.0 0.0
 LEGE TAB1 ;
FINSI ;
FIN ;
```
## INTG_test_integration_reduite.dgibi [Langage]
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
## raft1.dgibi [Maillage Autres]
```
'OPTION' 'ECHO' 0 ;
* NOM : RAFT1
* DESCRIPTION : Exemple d'utilisation de RAFT :
* Maillage d'un carré avec un fort raffinement dans un
* des coins.
* On teste les tailles de mailles obtenues par rapport
* aux tailles de maille voulues.
* LANGAGE : GIBIANE-CAST3M
* AUTEUR : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
* mél : gounand@semt2.smts.cea.fr
* VERSION : v1, 11/12/2006, version initiale
* HISTORIQUE : v1, 11/12/2006, création
* HISTORIQUE : 23/01/2014 : simplification du jeu de données
* (procédure MESUELEM)
* HISTORIQUE :
interact = FAUX ;
graph = FAUX ;
* P R O C E D U R E S
* MESUELEM
* Calcul d'une mesure de maille aux noeuds
* Je sais le faire de trois manières (équivalentes pour les SEG2
* mais pas pour les TRI3)
* 1) Avec l'opérateur MESU (boucle sur les éléments en GIBIANE)
* + CHAN 'CHPO'
* 2) En intégrant (par éléments) un champ par élément valant 1
* + CHAN 'CHPO'
* 3) Matrice de masse diagonalisée
* Ici, c'est la méthode 3.
'DEBPROC' MESUELEM ;
'ARGUMENT' mm*'MAILLAGE' ;
'SI' faux ;
* Méthode 2
   mod = 'MODE' mm 'MECANIQUE' 'ELASTIQUE' ;
   c1 = 'MANU' 'CHML' mod 'SCAL' 1. 'GRAVITE' ;
   ctai = 'INTG' 'ELEM' mod c1 ;
   cctai = 'CHANGER' 'CHPO' mod ctai 'MOYE' ;
'FINSI' ;
* Méthode 3
cctai = 'DOMA' ('MODE' ('CHANGER' mm 'QUAF') 'NAVIER_STOKES' 'LINE')
               'XXDIAGSI' ;
'RESPRO' cctai ;
'FINPROC' ;
* CALTAIL
* Calcul du champ de taille de maille voulue T par un problème de
* thermique, on résout :
* Laplacien T = 0
* avec T_bord = taille des mailles du bord
'DEBPROC' CALTAIL ;
'ARGUMENT' mt*'MAILLAGE' ;
cmt = 'CONTOUR' mt ;
cdt = MESUELEM cmt ;
* En fait, on résout le problème au laplacien pour le log
* des tailles de maille.
lcdt = 'LOG' cdt ;
modt = 'MODELISER' mt 'THERMIQUE' 'ISOTROPE' ;
cart = 'MATERIAU' modt 'K' 1.D0 ;
matt = 'COND' modt cart ;
mcdt = 'EXTRAIRE' lcdt 'MAIL' ;
matb = 'BLOQUE' 'T' mcdt ;
fb = 'DEPIMPOSE' matb (NOMC lcdt 'T') ;
clden = 'EXCO' 'T' ('RESOUD' ('ET' matt matb) fb) ;
cden = 'EXP' clden ;
* 'TRACER' cden mt ;
'RESPRO' cden ;
'FINPROC' ;
* Fin des P R O C E D U R E S
'OPTION' 'DIME' 2 'ELEM' 'TRI3' ;
p1 = 0. 0. ; p2 = 1. 0. ; p3 = 1. 1. ; p4 = 0. 1. ;
dpeti = 1.D-4 ; dgran = 0.5 ;
d1 = 'DROIT' p1 p2 'DINI' dpeti 'DFIN' dgran ;
d2 = 'DROIT' p2 p3 'DINI' dgran 'DFIN' dgran ;
d3 = 'DROIT' p3 p4 'DINI' dgran 'DFIN' dgran ;
d4 = 'DROIT' p4 p1 'DINI' dgran 'DFIN' dpeti ;
cmt = d1 'ET' d2 'ET' d3 'ET' d4 ;
mt1 = 'TRIANGULATION' cmt ;
'SI' graph ;
   tit1 = 'CHAINE' 'Triangulation grossière du domaine' ;
   'TRACER' mt1 'TITR' tit1 ;
'FINSI' ;
cden = CALTAIL mt1 ;
'SI' graph ;
   'TRACER' cden mt1 'TITR' ('CHAINE' 'Taille de mailles voulues') ;
'FINSI' ;
mt2 = 'RAFT' cden mt1 ;
nlmt = 'NBEL' mt2 ;
npmt = 'NBNO' mt2 ;
tit2 = 'CHAINE' 'Maillage resultant : ' nlmt ' elements ; '
                                        npmt ' noeuds ' ;
'MESSAGE' tit2 ;
'SI' graph ;
   'TRACER' mt2 'TITR' tit2 ;
'FINSI' ;
mt = mt2 ;
cdenv = CALTAIL mt ;
cdeno = MESUELEM mt ;
* cdeno est en unité de surface.
* On transforme en unité de longueur en multipliant par 2
* (car mt est constitué de triangles) et en prenant la racine.
cdeno = cdeno '*' 2. ;
cdeno = '**' cdeno 0.5D0 ;
ecar = '/' cdeno cdenv ;
t2 = 'CHAINE' 'Taille de maille obtenue / voulue ' ;
'SI' graph ;
   'TRACER' ecar mt2 'TITR' t2 ;
'FINSI' ;
* Facteur d'écart autorisé
fecar = 1.5D0 ; ifecar = 0.3D0 ;
maecar = 'MAXIMUM' ecar ;
miecar = 'MINIMUM' ecar ;
ok = VRAI ;
'MESSAGE' t2 ;
'MESSAGE' ('CHAINE' '  Max : ' maecar) ;
tes1 = '<' maecar fecar ;
ok = ok 'ET' tes1 ;
'SI' ('NON' tes1) ;
     'MESSAGE' ('CHAINE' '!!!! On aurait voulu avoir < ' fecar) ;
'FINSI' ;
'MESSAGE' ('CHAINE' '  Min : ' miecar) ;
tes2 = '>' miecar ifecar ;
ok = ok 'ET' tes2 ;
'SI' ('NON' tes2) ;
     'MESSAGE' ('CHAINE' '!!!! On aurait voulu avoir > ' ifecar) ;
'FINSI' ;
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
* End of dgibi file RAFT1
'FIN' ;
```
## drx_flexion_elas.dgibi [Mecanique Dynamique]
```
* Cas test de la procédure EXPLICIT
* Calcul de la réponse dynamique d'une plaque axisymétrqiue
* à une force de type impact sur son centre
* La réponse est comparée à un calcul modale avec DYNE
* options de calcul:
* linéaire,
* petits déplacements,
* axisymétrie,
* éléments QUA4,TRI3 et COQ2,
* conditions aux limites de déplacements nuls en 1 point.
* maillage d'une plaque cylindrique
* en beton avec ferraillage
* Diametre 20 m Epaisseur 1m
* fer tous les metres
* axe de symétrie
* \ Force sur r=1m
* \ !!!!
* uz | beton |
* |_ ur | + fer |\
* O ---------------------------- \
* blocage suivant z
graph = faux;
opti echo 0;
* MAILLAGE
opti dime 2 mode axis ;
ep1 = 2. ;
ray1 = 20. ;
int1 = 2. ;
* parametre du nombre d'element sur la verticale
n1 = 6 ;
* paramètre du nombre d'élément sur l'horizontale
n2 = 1;
pi1 = 0. 0 ;
ps1 = 0. ep1 ;
opti elem seg2 ;
lv1 = d pi1 n1 ps1 ;
nfer = ( enti ray1 ) / ( enti int1 ) ;
tabmail = table maillage ;
tabmail . 1 = table ;
tabmail . 1 . 'LVERT' = lv1 ;
ln = lect 6 4 3 8 * 2 20 * 1 ;
opti elem qua4 ;
i = 1 ;
repeter bou1 nfer ;
  ni = extr ln i ;
  tabmail . i . 'SU' = (tabmail . i . 'LVERT') trans
                               ( ni * n2 ) ( int1 0. ) ;
  tabmail . i . 'LSUP' = cote 2 (tabmail . i . 'SU') ;
  tabmail . i . 'LINF' = cote 4 (tabmail . i . 'SU') ;
  i = i + 1;
  tabmail . i = table ;
  tabmail . i . 'LVERT' = inve (cote 3 (tabmail . (i - 1) . 'SU')) ;
si ( i ega 4 ) ;
  n1 = n1 / 2 ;
  d4 = int1 / ni / n2 ;
  pi4 = (2 * int1 + d4) 0. ;
  ps4 = (2 * int1 + d4) ep1 ;
  li4 = d pi4 n1 ps4 ;
  su4a = coutu (tabmail . (i - 1) . 'LVERT') li4 ;
  su4b = li4 trans ( ni * n2 - 1) ( (d4 * ( ni * n2 - 1)) 0.) ;
  tabmail . (i - 1) . 'SU' = su4a et su4b ;
  tabmail . (i - 1) . 'LSUP' = (cote 2 su4a) et (cote 2 su4b) ;
  tabmail . (i - 1) . 'LINF' = (cote 4 su4a) et (cote 4 su4b) ;
  tabmail . i . 'LVERT' = inve (cote 3 su4b ) ;
finsi ;
  si ( i ega 2 ) ;
   total1 = (tabmail . (i - 1 ) . 'SU') ;
   totsup1 = (tabmail . (i - 1 ) . LSUP ) ;
   totinf1 = (tabmail . (i - 1 ) . LINF ) ;
   totvert1 = (tabmail . i . LVERT ) ;
  sinon ;
   total2 = total1 et (tabmail . (i - 1) . 'SU') ;
* detr total1 ;
   total1 = total2 ;
   totsup2 = totsup1 et (tabmail . (i - 1) . 'LSUP') ;
* detr totsup1 ;
   totsup1 = totsup2 ;
   totinf2 = totinf1 et (tabmail . (i - 1) . 'LINF') ;
* detr totinf1 ;
   totinf1 = totinf2 ;
   totvert2 = totvert1 et (tabmail . i . LVERT ) ;
* detr totvert1 ;
   totvert1 = totvert2 ;
  finsi ;
fin bou1 ;
mailpres = ( elem ( tabmail . 1 . lsup ) 1 )
          et ( elem ( tabmail . 1 . lsup ) 2 )
          et ( elem ( tabmail . 1 . lsup ) 3 ) ;
totvert1 = coul totvert1 vert ;
totsup1 = coul totsup1 bleu ;
totinf1 = coul totinf1 bleu ;
total1 = coul total1 jaune ;
totfer = totvert1 et totsup1 et totinf1 ;
* trac totfer titr 'Ferraillage' ecla ;
* trac ( total1 et totfer ) titr 'Ferraillage et Beton' ecla ;
opti echo 0 ;
nelm = (nbelem total1) ;
nnom = (nbno total1) ;
nelc = ( nbelem totfer ) ;
nnoc = (nbno totfer) ;
nnddl = nnom * 2 + nnoc ;
sauter 1 ligne ;
mess 'Nbre d element massifs' nelm 'soit' nnom;
mess 'Nbre d element coque ' nelc 'soit' nnoc ;
mess 'Total' ( nelm + nelc ) 'Elements' nnddl 'ddl' ;
sauter 1 ligne ;
opti echo 1 ;
* determnation des distances minimales L
* pour le calcul du pas de temps
* MODELE ET MATERIAU
mobeto = mode total1 mecanique elastique ;
mabeto = mate mobeto YOUN 40.d9 NU 0.2 RHO 2.4d3;
mofer = mode totfer mecanique elastique coq2 ;
mafer = mate mofer RHO 7.8d3 YOUN 210.d9 NU 0.3 ;
carfer = cara mofer EPAI 12.d-3 ;
* CONDITONS AUX LIMITES
pext1 = total1 poin proc ( ray1 0. ) ;
cl1 = bloq UZ pext1 ;
* CHARGEMENT SPATIAL
fpres = (PRESS COQU ( redu mofer mailpres) 1. NORM) / -3.14158 ;
fpres = 'EXCO' fpres ( 'MOTS' 'FR' 'FZ' ) ;
vpres = vect fpres FR FZ rouge 2.;
titr 'Distribution spatiale du chargement (forces nodales equi.)' ;
* trac vpres total1 ;
* ANALYSE MODALE
rig1 = rigi ( mobeto et mofer ) (mabeto et mafer et carfer ) ;
mas1 = masse ( mobeto et mofer ) (mabeto et mafer et carfer ) ;
temps zero ;
tbas1 = vibr 'INTERVALLE' 0. 300. basse 70 ( rig1 et cl1 ) mas1;
lfreq = prog ;
i = 1 ;
repeter bou1 ( (dime tbas1 . modes ) - 2);
  tabi = tbas1 . modes . i ;
  lfreq = lfreq et ( prog tabi .frequence ) ;
* titr 'Frequence ' tabi .frequence ;
* trac ( defo total1 tabi . deformee_modale ) ;
  i = i + 1 ;
fin bou1 ;
* evolution temporelle force d'impact
evolp = evol manu
     ((prog 0. 10. 20. 30. 40. 50. 60. 70. 1000.)*1.d-3)
     ((prog 0. 55. 55. 110. 110. 55. 55. 0. 0.)*1.d6 / 3.) ;
* réponse élastique de la structrue avec dyne
tabchar = table chargement ;
cha1 = char MECA evolp fpres ;
chaba1 = PJBA cha1 tbas1 ;
tabchar . BASE_A = chaba1 ;
sol1 = 'PSMO' (rig1 et cl1 ) (tbas1 . 'MODES') fpres ;
tbas1 . 'PSEUDO_MODES' = sol1 ;
fr1 = extr lfreq (dime lfreq ) ;
w1 = 2 * pi * fr1 ;
dt = 2 ** .5 * 2 / w1 / 10 ;
npas = 'ENTI' ( 21.d-3 / dt) ; nins = 1 ;
'MESS' 'Nombre de pas  : ' npas ;
tbas1 = reac cl1 tbas1 ;
tabres = dyne de_vogelaere tbas1 tabchar npas dt nins ;
TABTPS = TEMP 'NOEC';
tdyn = TABTPS.'TEMPS_CPU'.'INITIAL' ;
evx = 'EVOL' 'RECO' tabres tbas1 cha1 'REAC' pext1 FZ ;
evy = 'EVOL' 'RECO' tabres tbas1 cha1 DEPL pi1 UZ ;
* calcul à l'aide de la procédure explicite
* pas de temps minimum
celbet = ( 37.d9 / 2.4d3 ) ** 0.5 ;
celfer = ( 210.d9 / 7.8d3 ) ** 0.5 ;
lmin = int1 / 6. / n1 ;
dtmin = lmin / ( maxi ( prog celfer celbet ) ) ;
tab_in = TABLE ;
tab_in .'CHARGEMENT' = cha1 ;
tab_in .'LIAISONS' = cl1 ;
tab_in .'MODELE' = mobeto et mofer;
tab_in .'CARACTERISTIQUES' = mafer et mabeto et carfer ;
tab_in .'PAS_TEMPS' = dtmin ;
tab_in .'NPASMAX' = enti ( 20.87d-3 / dtmin ) ;
tab_in .'TEMPS_SORTIE' = prog 0. PAS 2.5d-4 20.87d-3 ;
temps zero ;
 DREXUS tab_in ;
TABTPS = TEMP 'NOEC';
texpli = TABTPS.'TEMPS_CPU'.'INITIAL' ;
* FORCE DE REACTION DU CADRE
i = 1 ;
lt = prog 0.;
lz = prog 0. ;
lzpi1 = prog 0. ;
repeter bou1 ( (dime tab_in . deplacements ) - 1) ;
  lt = lt et ( prog tab_in . temps . i ) ;
  fex1 = tab_in . forces_exterieures . i;
  dep1 = tab_in . deplacements . i;
  fz = extr fex1 pext1 'FZ' ;
  lz = lz et ( prog fz ) ;
  lzpi1 = lzpi1 et ( prog ( extr dep1 pi1 UZ ) );
  i = i + 1 ;
fin bou1 ;
evfz = evol bleu manu 'Temps' lt 'Fz' lz ;
evx = coul evx turq ;
tabgraf = table ;
tabgraf . 1 = 'MARQ CROI  ' ;
tabgraf . 2 = 'MARQ PLUS ' ;
tabgraf.'TITRE' = table ;
tabgraf.'TITRE' . 1 = mot 'explicit' ;
tabgraf.'TITRE' . 2 = mot 'base_modale' ;
si graph;
dess ( evfz et evx ) tabgraf lege xbor 0. 0.024 ;
finsi;
* DEPLACEMENT VERTICAL AU DROIT DE LA FORCE
evuz = evol bleu manu 'TEMPS' lt 'UZ' lzpi1 ;
evy = coul evy turq ;
tabgraf . 2 = 'MARQ PLUS ' ;
tabgraf.'TITRE' . 2 = mot 'base_modale' ;
si graph;
dess ( evuz et evy ) tabgraf lege xbor 0. 0.024 ;
finsi;
* TEST DE BON FONCTIONNEMENT
lz2 = ipol lt ( extr evx 'ABSC' ) (extr evx 'ORDO' ) ;
err1 = (maxi abs ( lz2 - lz )) / ( maxi abs lz2 );
lerr1 = err1 >eg 0.15 ;
luz2 = ipol lt ( extr evy 'ABSC' ) (extr evy 'ORDO' ) ;
err2 = (maxi abs ( lzpi1 - luz2 )) / ( maxi abs luz2 ) ;
lerr2 = err2 >eg 0.05 ;
 mess 'Erreur sur la force ' (err1 * 100. ) '%' ;
 mess 'Erreur sur le deplacement ' (err2 * 100. ) '%' ;
si (tdyn <eg 0) ;
 mess 'Rapport Tps Calcul EXPLICIT/DYNE =' texpli '/' tdyn ;
sinon ;
 mess 'Rapport Tps Calcul EXPLICIT/DYNE =' (1. * texpli /tdyn) ;
finsi ;
si (ou lerr2 lerr1) ;
  mess 'Erreur dans le cas test beton_elas' ;
  erreur 5 ;
finsi ;
fin;
```
## frenet_1.dgibi [Mathematiques Autres]
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
## Contact2D.dgibi [Mecanique Contact]
```
* Ce cas-test permet de tester la gestion du contact par PASAPAS.
* Il simule la mise en contact, en deplacements imposes, d'un carre
* sur une surface rigide. Le probleme est traite en 2D, contraintes
* planes. On impose le deplacement de l'arete sup. du carre. Sa base
* entre en contact, le carre est mis en compression. On compare la
* solution EF a la solution analytique.
* 'OPTI' ECHO 0 ;
'OPTI' 'DIME' 2 'ELEM' QUA4 'MODE' 'PLAN' 'CONT' ;
* Si TRACes desires, mettre IG1 a VRAI :
IG1 = FAUX ;
* MAILLAGE
S1 = -10. 0.9999 ;
S2 = 10. 0.9999 ;
NLS1 = 5 ;
LS1 = S1 'DROI' NLS1 S2 ;
M1 = -5. 1. ;
M2 = 5. 1. ;
NLM1 = 7 ;
LM1 = M1 'DROI' NLM1 M2 ;
SM1 = LM1 'TRAN' NLM1 (0. 10.) ;
* Maillages de contact :
* MCONT1 = ('IMPO' 'MAIL' LM1 ('INVE' LS1)) 'COUL' 'JAUN' ;
* list MCONT1;
* Traces :
'SI' IG1 ;
  'TITR' 'Maillages' ;
* 'TRAC' 'FACE' (LS1 'ET' SM1 'ET' MCONT1) ;
'FINS' ;
* MODELES / CARACTERISTIQUES
MODM1 = 'MODE' SM1 'MECANIQUE' 'ELASTIQUE' ;
MATM1 = 'MATE' MODM1 'YOUN' 1.E3 'NU' 0.3 ;
* C.L. / CHARGEMENT
* Deplacements imposes :
LM3 = SM1 'COTE' 3 ;
LM4 = SM1 'COTE' 4 ;
CLLM3 = 'BLOQ' LM3 'UY' ;
CLLM4 = 'BLOQ' LM4 'UX' ;
CLS1 = 'BLOQ' LS1 'DEPL' ;
CL0 = CLLM3 'ET' CLLM4 'ET' CLS1 ;
UY0 = -0.0003 ;
DCLLM3 = 'DEPI' CLLM3 UY0 ;
'SI' IG1 ;
  'TITR' 'Deplacement impose au bord superieur du carre.' ;
  'TRAC' ('VECT' (DCLLM3 'NOMC' 'UY') 1. 'UX' 'UY' 'VERT')
  (LS1 'ET' SM1) ;
'FINS' ;
* Chargements :
LTPS1 = 'PROG' 0. 1. ;
EV1 = 'EVOL' 'MANU' 'TEMPS' LTPS1 ('PROG' 0. 1.) ;
CHARU1 = 'CHAR' 'DIMP' DCLLM3 EV1 ;
CHAR0 = CHARU1 ;
MODCONTA= model lm1 contact unilateral (inve ls1) 'SYME';
list modconta;
* RESOLUTION
* Construction de la table PASAPAS :
TAB1 = 'TABL' ;
TAB1 . 'TEMPS_CALCULES' = LTPS1 ;
TAB1 . 'MODELE' = MODM1 et modconta;
TAB1 . 'CARACTERISTIQUES' = MATM1 ;
TAB1 . 'BLOCAGES_MECANIQUES' = CL0 ;
TAB1 . 'CHARGEMENT' = CHAR0 ;
* TAB1 . 'CONTACT' = MCONT1 ;
* TAB1 . 'GRANDS_DEPLACEMENTS' = FAUX ;
* Resolution :
TAB2 = PASAPAS TAB1 ;
* DEPOUILLEMENT
DEP1 = (TAB2 . 'DEPLACEMENTS' . 1) 'ENLE' 'LX' ;
* Deformee :
DEFO0 = 'DEFO' (SM1 'ET' LS1) DEP1 0. 'VERT' ;
DEFO1 = 'DEFO' (SM1 'ET' LS1) DEP1 1. 'ROUG' ;
'SI' IG1 ;
  'TITR' 'Maillages non deforme (vert) et deforme (rouge).' ;
  'TRAC' (DEFO0 'ET' DEFO1) ;
'FINS' ;
* Definition des deplacements solutions et comparaison avec la
* solution EF :
EPXX1 = ((-1. * UY0) - 0.0001) * 0.1 * 0.3;
UXSM1 = (('COOR' 1 SM1) + 5.) * EPXX1 ;
SOLUX1 = UXSM1 'NOMC' 'UX' ;
EPYY1 = ((-1. * UY0) - 0.0001) * 0.1 ;
UYSM1 = ((('COOR' 2 SM1) - 1.) * EPYY1) + 0.0001;
SOLUY1 = (-1. * UYSM1) 'NOMC' 'UY' ;
SOLU1 = SOLUX1 'ET' SOLUY1 ;
ERR1 = 'MAXI' ('ABS' ((SOLU1 - DEP1) / ('MAXI' 'ABS' (SOLU1)))) ;
'SI' IG1 ;
  'TITR' 'Champ de deplacements.' ;
  'TRAC' ('CHAN' 'CHAM' DEP1 MODM1 'NOEUDS') MODM1 ;
'FINS' ;
* Comparaison des champs de contraintes :
EPS1 = 'EPSI' MODM1 SOLU1 ;
SIG1 = 'ELAS' MODM1 EPS1 MATM1 ;
SIG2 = TAB2 . 'CONTRAINTES' . 1 ;
ERR2 = 'MAXI' ('ABS' ((SIG1 - SIG2) / ('MAXI' 'ABS' (SIG1)))) ;
'SI' IG1 ;
  'TITR' 'Champ de contraintes.' ;
  'TRAC' SIG2 MODM1 ;
'FINS' ;
* Visualisations des reactions :
'SI' IG1 ;
  REAC1 = TAB2 . 'REACTIONS' . 1 ;
  VR1 = 'VECT' REAC1 0.8E-2 'FX' 'FY' 'ROUG' ;
  'TITR' 'Forces de reaction.' ;
  'TRAC' VR1 (LS1 'ET' SM1) ;
'FINS' ;
LERR0 = 'PROG' ERR1 ERR2 ;
ERR0 = 'MAXI' LERR0 ;
ERRMAX1 = 1.E-3 ;
'OPTI' 'ECHO' 0 ;
'SAUT' 1 'LIGN' ;
'MESS'
'------------------------ RESULTAT CAS-TEST ------------------------' ;
'SAUT' 1 'LIGN' ;
'MESS'
'Ecart relatif a la solution calculee sur les deplacements' ;
'MESS'
'et les contraintes :' ;
'MESS'
'-----------------------------------------------------------' ;
'MESS' ;
'MESS' '    MAX. ERREUR =' ERR0 ;
'SAUT' 1 'LIGN' ;
'SI' (ERR0 '<EG' ERRMAX1) ;
  'MESS' '==> Erreur relative inferieure a' ERRMAX1 ':' ;
  'MESS' '' ;
  'MESS' '                        __________________' ;
  'MESS' '                        |                |' ;
  'MESS' '                        |  TEST REUSSI ! |' ;
  'MESS' '                        |________________|' ;
  'SAUT' 1 'LIGN' ;
'SINO' ;
  'MESS' '==> Erreur relative superrieure a' ERRMAX1 ':' ;
  'MESS' '' ;
  'MESS' '                        __________________' ;
  'MESS' '                        |                |' ;
  'MESS' '                        |     ERREUR !   |' ;
  'MESS' '                        |________________|' ;
  'SAUT' 1 'LIGN' ;
  'ERRE' 5 ;
'FINS' ;
'MESS'
'-------------------------- FIN CAS-TEST ---------------------------' ;
'FIN' ;
'OPTI' 'ECHO' 1 ;
```
