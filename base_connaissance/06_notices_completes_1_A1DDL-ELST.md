# Notices Gibiane complètes (français), partie 1/3 : @A1DDL à ELST

Texte des notices `INFO`, sans décorations, sans colonne « voir aussi » ni section anglaise. Chaque notice commence par `## NOM [section]`.

## @A1DDL [Post-traitement Analyse] (proc)
     Procedure @A1DDL

EV1 EV2 EV3 EV4 TAB2 = @A1DDL TAB1;

    Objet :

  La procedure @A1DDL permet de calculer la reponse dynamique d un
oscilateur non lineaire a 1 degre de liberte soumis a un chargement
sismique applique en effort impose (calcul dans la repere relatif
a la structure). L originalite de cette procedure est que le
coefficient d amortissement est actualise en fonction d une loi
phenomenologique.

TAB1 : TABLE table de donnees
        TAB1 . 1 = M; -- masse de la structure
        TAB1 . 2 = BETA; -- coefficient beta (schema de Newmark)
        TAB1 . 3 = GAMMA; -- coefficient gamma (schema de Newmark)
        TAB1 . 4 = FPLAS; -- effort de plastification
        TAB1 . 5 = KA; -- raideur de l acier
        TAB1 . 6 = KB; -- raideur du beton
        TAB1 . 7 = ACTU -- type d actualisation
        TAB1 . 8 = TIME -- liste de temps (type LISTREEL)
        TAB1 . 9 = AXTAB -- liste d acceleration (type LISTREEL)
        TAB1 . 10 = XI0 -- taux d amortissement initial
        TAB1 . 11 = XMIN -- taux d amrotissement minimal
        TAB1 . 12 = AMMAX -- taux d amortissement maximal
        TAB1 . 13 = NC -- indicateur sur le type d actualisation
        TAB1 . 14 = DPLUS -- endommagement positif initial
        TAB1 . 15 = DMOIN -- endommagement negatif initial
        TAB1 . 16 = MAXDP -- maximum du deplacement positif initial
        TAB1 . 17 = MAXDM -- minimum du deplacement negatif initial
        TAB1 . 18 = AOLD -- taux d amortissement au premier pas

EV1 : EVOLUTION Evolution du deplacements en fonction du temps
EV2 : EVOLUTION Evolution de la vitesse en fonction du temps
EV3 : EVOLUTION Evolution de l acceleration en fonction du temps
EV4 : EVOLUTION Evolution de l amortissement en fonction du temps

TAB2 : TABLE table de sortie des variables internes
        TAB2 . 1 = FO1 -- Force
        TAB2 . 2 = DPLUS -- Endommagement positif final
        TAB2 . 3 = DMOIN -- Endommagement negatif final
        TAB2 . 4 = MAXDP -- Maximum des deplacements positifs
        TAB2 . 5 = MAXDM -- Minimum des deplacement negatifs
        TAB2 . 6 = FF -- Effort de stabilisation
        TAB2 . 7 = XI -- Taux d amortissement final

## @AFEVOZT [Post-traitement Affichage] (proc)
    Procedure @AFEVOZT
   CHPO1 MAIL1 = @AFEVOZT TAB1 ('HORIZONTAL' | 'VERTICAL' ) (FLOT1);

La procedure @AFEVOZT permet creer un champ par point pour representer un jeu
d'evolutions sous forme d'iso-valeur. Ceci permet, par exemple, de representer
l'evolution d'un grandeur le long d'un axe et au cours du temps sur un unique
graphique.

Les evolutions doivent etre donnees dans une table contenant les entrees:
   -TAB1. i : evolutions a afficher (i est un entier);
   -TAB1.'TEMPS' : liste des temps (ou autre parametre) associes à chaque
   evolution.

Avec l'option 'HORIZONTAL', l'abscisse des evolutions est representee dans la
direction X, le temps dans la direction Y.
Avec l'option 'VERTICAL', l'abscisse des evolutions est representee dans la
direction Y, le temps dans la direction X.
Sans precision, l'option 'VERTICAL' est assumee.
Dans tous les cas, la couleur des iso-valeurs est basees sur l'ordonnees des
evolutions.

Le reel FLOT1 permet de preciser le rapport d'aspect entre l'abscisse des
evolutions et le temps.
Sans precision, le rapport d'aspect est de 1.0, ce qui signifie que sur
l'affichage, le temps est mis à l'echelle afin que le graphique soit un carre.
Avec un rapport d'aspect negatif, on peut changer le sens d'orientation de l'axe
des temps.
Sens d'augmentation du temps :
        |  HORIZONTAL  |  VERTICAL
FLOT1>0  |  vers le haut |  vers la droite
FLOT1<0  |  vers le bas  |  vers la gauche

La procedure renvoie un champ par point et son maillage support pour pouvoir
l'afficher avec l'operateur 'TRAC'.
Le maillage resultat contient le maillage support et les lignes marquant les
temps des evolutions.
Les lignes correspondants aux differents instants peuvent être obtenues par la
commande :
('ELEM' mail1 'SEG2').
Pour tracer le graphique en visualisant les differents instants et en cachant le
maillage support, on pourra utiliser la commande :
'TRAC' CHPO1 ('ELEM' MAIL1 'TRI3') ('ELEM' MAIL1 'SEG2');

Exemple :
'OPTI' 'DIME' 2;
*Creation de la table
TATEST = 'TABLE';
LITEMP = 'PROG' 0. 'PAS' 0.5 5 5.1 5.2 5.3 5.4 5.5 6 'PAS' 1 10;

TATEST . 'TEMPS' = LITEMP;
LIZ = 'PROG' 0. 'PAS' 0.05 1.0;
*Remplissage des evolutions
'REPE' ITP ('DIME' LITEMP);
   TPCOUR = 'EXTR' LITEMP &ITP;
   LIVAL = 'PROG';
   'REPE' itz ('DIME' liz);;
      ZCOUR = 'EXTR' LIZ &ITZ;
      VALCOUR = ('SIN' ( (360. * ZCOUR - 90) + ( 50 * ('COS' (20. *
      TPCOUR))))) * (1 + (TPCOUR / 10.));
      LIVAL = LIVAL 'ET' VALCOUR;
   'FIN'ITZ;
   TATEST . &ITP = 'EVOL' 'MANU' 'ABSC' LIZ 'ORDO' LIVAL;
'FIN' ITP;

LIST TATEST;
*Trace sous forme d'evolution
EVOTOT = 'VIDE' 'EVOLUTION';
'REPE' ITP ('DIME' LITEMP);
   EVOTOT = EVOTOT 'ET' TATEST . &ITP ;
'FIN' ITP;
DESS EVOTOT;
*Trace sous forme d'iso-valeur
MATEST CHTEST = @AFEVOZT TATEST 'HORIZONTAL' -0.5;
TRAC CHTEST MATEST ('CONTOUR' MATEST);
TRAC CHTEST MATEST ('ELEM' MATEST 'SEG2');

## @ALGSTA [Mecanique Resolution] (proc)
   Procedure @ALGSTA

   Objet :

Cette procedure est appelee en interne par la procedure @STATIO

## @ANA_LIM [Mecanique Resolution] (proc)
    Procedure @ANA_LIM

    @ANA_LIM TAB1;

   TAB1. BLOCAGES_MECANIQUES MAXITERATION
        BRIDE MECARUINE
        CADIM MODELE
        CALCUL_COQUE PAS
        CHARGEMENT PRECISION
        CONTRAINTES PROCEDURE_PERSO1
        CRITERE REPRISE
        DEPLA RESULTAT
        EVOLCL SIGLIM
        LISTCL
        LISTITER

    Objet :

Cette procedure permet de calculer le chargement limite d'une structure
sous la forme d'une suite monotone decroissante convergeant vers la
solution.
La modelisation est equivalente a un calcul plastique parfait.
Version 04/96
Elle s'utilise comme PASAPAS

Commentaires

TAB1 : Objet de type TABLE.

En entree, TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots dont voici la liste :

MODELE MMODEL objet modele (MECANIQUE ELASTIQUE)
        Indispensable

CHARGEMENT CHPOINT Forces nodales equivalentes
        Indispensable

BLOCAGES_MECANIQUES RIGIDITE blocages mecaniques
        Indispensable

CRITERE MOT choix du critere de plasticite
        VONMISES OU tresca (taper TRSCA)
        defaut: VONMISES

SIGLIM FLOTTANT limite d'ecoulement
        ou MCHAML pour un MCHAML il faut un type SCALAIRE
        appuye aux points de calcul des
        contraintes
        (voir operateur CHAN -> type "SCALAIRE"
        et "STRESSES")
        valeur par defaut: 1.

CALCUL_COQUE MCHAML active un calcul en coque
        stype CARACTERISTIQUES Caracteristiques de la coque (EPAI,
        ALFA) pour un veritable calcul
        plastique ALFA=2/3

PRECISION FLOTTANT valeur de la precision
        valeur par defaut: 1e-3

MAXITERATION ENTIER nombre maximum d'iterations
        valeur par defaut: 50

PAS ENTIER pas d'affichage des resultats
        valeur par defaut: 1

REPRISE LOGIQUE si REPRISE=VRAI il s'agit de la
        reprise d'un calcul
        (exemple a la fin)

PROCEDURE_PERSO1 LOGIQUE VRAI si procedure perso a la fin de
        chaque iteration

En sortie, TAB1 permet de retrouver les resultats:

 indice type objet

MECARUINE MCHAML VMises a convergence
        sstype CONTRAINTES

CONTRAINTES MCHAML contraintes a convergence

YOUNG MCHAML young a convergence

LISTITER LISTREEL liste des iterations

LISTCL LISTREEL liste des charges limites

EVOLCL EVOLUTION evolution des charges limites
        en fonction des iterations

CADIM FLOTTANT charge limite resultat de
        chargement limite/chargement elastique

DEPLA CHPO deplacements a convergence

le barometre permet de verifier que les Von Mises (ou les Tresca )
s'appuient bien sur la surface de charge.

liste des avertissements:

AVERT1:vous etes totalement elastique (passage au dessous de la limite
elastique)
AVERT2:la suite des charges limites est croissante -> invalidite de la
theorie
AVERT3:pas assez d'iterations

remarques:
-@ANA_LIM fonctionne soit en depplacements imposes soit en forces
imposes,mais pas avec les deux conditions pour un meme calcul.
Lorsqu'un calcul est fait en 'forces imposees', le parametre "charge
limite" represente la valeur a multiplier au chargement initial imposes
pour obtenir le chargement limite.
- Lorsqu'un calcul est fait en 'deplacements imposes', il convient de
depouiller le chargement a la fin de chaque iteration par l'intermediaire
d'une procedure PERSO1 qui traitera le resultat pour le transformer en
reactions aux endroits d'application des deplacements (REDU BSIG)
- Pour une reprise, a la fin du premier calcul, ajouter
table.REPRISE=vrai et relancer @ANA_LIM
- Le "ratio elastique" correspond au Vmises maxi apres un calcul
elastique incompressible divise par la limite d'ecoulement.
Pour plus de precisions voir David Plancq (42257492)

## @ARR [Mathematiques Fonctions] (proc)
   Procedure @ARR
   -------------- ENTI

Syntaxe : MOT2 = @ARR FLOT1 ENTI1 (MOT1)

      Objet :

  Procedure renvoyant, a partir d'un reel FLOT1 et d'un nombre de
  decimales ENTI1, l'arrondi du reel, avec ENTI1 chiffres apres la
  virgule, sous la forme du 'MOT' MOT2.

      Commentaire :

  FLOT1 : nombre dont on souhaite prendre l'arrondi

  ENTI1 : nombre de chiffres apres la virgule

  MOT1 : mot facultatif valant 'EXPOSANT' et forçant l'ecriture du
        nombre sous la forme 'aEb' (a etant la mantisse 'ET' b
        l'exposant).

      Remarques :

  1 - On passe automatiquement en notation EXPOSANT si l'affichage ne
      contiendrait autrement que des 0 ou si FLOT1 depasse 1.D10

  2 - l'operateur 'ENTIER' renvoie la troncature et non pas la partie
      entiere, ce qui n'est pas valide pour les nombres negatifs
      et est corrige ici.

  3 - Ne marche pas avec de grands nombres.

  4 - Resultat lie a la precision machine

## @B_TPO2D [—] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR Miguel A. Bretones UPC Barcelona

     Procedure @B_TPO2D

     @B_TPO2D SIG1 MODL1 ( FLOT1 ) ;

ESPA==============================================================

     Objeto :

La procedure @B_TPO2D calcula y dibuja, a partir de un campo de tensiones
las tensiones principales interpoladas en los nodos. La representacion
se efectua mediante un juego de vectores de magnitud proporcional al
valor de la tension correspondiente, con la orientacion adecuada.

     Comentario :

     SIG1 : Campo inicial de tensiones (tipo MCHAML)

     MODL1 : Modelo mecanico asociado (tipo MMODEL)

     FLOT1 : Factor de escala para la representacion vectorial del
        resultado (tipo FLOTTANT)

     Especificaciones :

      La procedure trabaja unicamente en dos dimensiones.

      El orden de entrada de los objetos iniciales debe respetarse.

      En ausencia del factor de escala, @B_TPO2D evalua uno de caracter
       heuristico. Dada la gran generalidad del problema a tratar, es
       te valor puede arrojar resultados visualmente malos. En este
       caso puede modificarse interactivamente dicho factor de escala
       hasta conseguir los resultados deseados.
      Una vez conocido, para cada problema en concreto, el valor de
       dicho factor, puede introducirse directamente como argumento
       de la procedure, lo que permitira no pasar por el proceso inte
       ractivo de prueba y error y asi poderla incluir dentro del cuer
       po de un programa principal.
      Finalmente, la entrada de un factor inicial de escala negativo
       provoca la estimacion del mismo pero sin la posibilidad de modi
       ficarlo de manera interactiva, no deteniendose por tanto la eje
       cucion.

      En terminales de color se indican como verdes las tensiones de
       compresion y como rojas las de traccion.

## @CARENE [Maillage Autres] (proc)
    Procedure @CARENE
    ----------------- @tole2 @tole3

    MAIL1 TAB2 TAB3 = @CARENE TAB1 LISTREE1 LISTREE2 FLOT1 ENT1 ;

    Objet :

La procedure @CARENE cree une carene (maillage tridimensionnel forme
d'elements de type QUA4) a partir de couples ( formes d'elements de
type SEG2). Ces couples (2 au minimum) doivent avoir le meme nombre de
points. Les points de meme rang des couples sont relies par une latte
(deformation elastique d'une poutre). La carene est generee par
surfaces reglees appuyees sur 2 lattes consecutives.

    Commentaires :

    TAB1 : Table donnant les couples.
        TAB1.1 = couple initial.
        TAB1.2 = couple final.
        TAB1.N = couple intermediaire facultatif (N=3,4..)

    LISTREE1 : Objet LISTREEL de 3 valeurs precisant les rotations
        imposees RX,RY,RZ au niveau du couple initial.
        -45. < RX,RY,RZ < 45.
        Si RX,RY,RZ > 45. la rotation est libre.

    LISTREE2 : Objet LISTREEL de 3 valeurs precisant les rotations
        imposees RX,RY,RZ au niveau du couple final.
        -45. < RX,RY,RZ < 45.
        Si RX,RY,RZ > 45. la rotation est libre.

    FLOT1 : reel donnant la longueur des elements le long d'une
        latte.

    ENT1 : Entier precisant la direction des lattes.
        = 1 , la latte est sur OX.
        = 2 , la latte est sur OY.
        = 3 , la latte est sur OZ.

    Exemple d'utilisation :

    titre 'essai de maillage par carene';
    ev = evol manu ' absci' ( prog 0.04 0.4 0.53 0.67 0.77 0.77)
        'ordo' ( prog -0.2 -0.13 -0.08 0. 0.23 0.41);
    evo1L = @lisse ev 50 0. 40 2;
    uu2 = extraire evo1l ordo;
    uu1 = extraire evo1l absc;
    evo2l = evol manu absci (prog 40*0.04) ordo uu2;
    ec1 = @couple evo1l evo2l 2;

* maillage de l'etrave
    u1 = prog -1.2 -1.34 -1.49 -1.6 -1.68 -1.74 -1.79 ;
    u2 = prog -0.16 -0.143 -0.11 -0.01 0.11 0.32 0.64;
    evf = evol manu absc u1 ordo u2;
    evo1Le = @lisse evf 50 50. 40 1;
    uu2 = extraire evo1le ordo;
    uu1 = extraire evo1le absc;
    evo2le = evol manu absci (prog 40*0.04) ordo uu2;
    ec2 = @couple evo2le evo1le 1;
    ta= table;
    ta. 1 = ec1; ta . 2 = ec2;
    pr1 = prog 0 2 0 ; pr2 = prog 25 50 50 ;
    dis = 0.5;
    aa bb cc = @carene ta pr1 pr2 dis 1;
    trac aa ( 0 10000 5000);

$$$$

## @CARTOON [Post-traitement Affichage] (proc)
     Procedure @CARTOON

(DEF1 = ) @CARTOON TAB1 GEO1 (BLO1) (OEIL1) (AMPL) ( 'NOSCIL' ) ;

    Objet :

  La procedure @CARTOON effectue une animation des deformees
  successives de GEO1 obtenues a partir des deplacements contenus
  dans TAB1.RESUDEPL.
  Dans le cas ou BLO1 est donne, les vecteurs correspondants aux
  reactions sont traces.
  En 3D cette animation est visualisee suivant le point d'observation
  OEIL1.
  On peut preciser l'amplitude maximale des deformees avec le
  coefficient AMPL.Par defaut il est determine automatiquement.
  Il est possible de desactiver l'option OSCIL qui est prise par defaut,
  en utilisant l'option NOSCIL.On obtient alors une simple animation.

  TAB1 : TABLE resultat de NONLIN
  GEO1 : MAILLAGE
  BLO1 : RIGIDITE blocage dont on veut tracer les reactions
  OEIL : POINT point d'observation en 3D
  DEF1 : DEFORMEE resultat si demande
  AMPL : FLOTTANT coefficent d'amplification des deformees
  NOSCIL : MOT desactive les oscillations

    remarque :

  Pour stopper l'animation, il suffit de cliquer dans la fenetre de
  dessin.

## @CDG [Maillage Generaux] (proc)
   CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
  A DISPOSITION DE LA COMMUNAUTE CASTEM2000
PAR DELERUYELLE F. (SOCOTEC-INDUSTRIE a L IPSN/DES)

    Procedure @CDG

    XG1 XG2 (XG3) = @CDG MODL1 (CAR1) ;

    Objet :

    Cette procedure calcule les coordonnees du centre de gravite de
    la geometrie contenue dans un modele.

    Commentaires :

    MODL1 : objet modele (type MMODEL).

    CAR1 : champ de caracteristiques geometriques (facultatif)
        (type MCHAML,sous-type CARACTERISTIQUES).
        Si on veut prendre en compte une distribution de masse
        volumique non uniforme, il faut entrer dans CAR1 le champ
        par element de MATERIAU (pour donner RHO) et le champ de
        CARACTERISTIQUES (pour donner EPAI, SECT, ...).

    XG1 : premiere coordonnee du centre de gravite (type FLOTTANT).

    XG2 : seconde coordonnee du centre de gravite (type FLOTTANT).

    XG3 : eventuellement, troisieme coordonnee du centre de gravite
        en 3 D (type FLOTTANT).

    Exemple :

    mo1 = mode s3d mecanique elastique isotrope coq3 coq4 ;
    ca1 = cara mo1 epai 0.5 ;
    xg1 xg2 xg3 = @cdg mo1 ca1 ;
    list xg1 ; list xg2 ; list xg3 ;

    Remarques :

    1) Cette procedure n'a ete testee que sur des modeles a formulation
       MECANIQUE.

    2) Pour les coques, le domaine d'integration est la surface de la
       coque et pour les poutres, le domaine d'integration est la ligne
       moyenne de la poutre. Si l'on veut integrer sur le volume de ces
       elements, il faut donner le champs de caracteristiques geometri-
       ques CAR1 (type MCHAML, sous-type CARACTERISTIQUES).

    3) Dans le cas des coques, meme en fournissant CAR1, on ne prend pas
       en compte l'excentrement.

    4) On peut traiter un modele mecanique contenant plusieurs types
       d'elements.

## @CFD10 [Post-traitement Analyse] (proc)
     Procedure @CFD10

F02 = @CFD10 FO1;

    Objet :

  La procedure @CFD10 permet de determiner la valeur du taux
d amortissement F02 a partir d un indicateur d endommagement
structural. Elle est appelee par la procedure @A1DDL.

F01 : FLOTTANT Indicateur d endommagement structural
F02 : FLOTTANT Taux d amortissement

## @CFS10 [Post-traitement Analyse] (proc)
     Procedure @CFS10

F02 = @CFS10 FO1;

    Objet :

  La procedure @CFS10 permet de determiner la valeur du taux
d amortissement F02 a partir d un indicateur d intensite de
chargement sismique. Elle est appelee par la procedure @A1DDL.

F01 : FLOTTANT Indicateur d intensite de chargement sismique
F02 : FLOTTANT Taux d amortissement

## @CHFLEC [Post-traitement Affichage] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR M. D. DUREISSEIX
        L.M.T. STRUCTURES & C.M.A.O.

   Procedure @CHFLEC

   PTF1 = @CHFLEC ECH1 CHPO1 (ARG1) (TAIL1) ;

   Objet :

Procedure pour construire un CHamp de FLEChes

on envoie
        ECH1 FLOTTANT echelle pour le trace des efforts
        CHPO1 CHPOINT champ par point a representer
       /ARG1 MOT si egal a 'G ' seul le cote gauche est trace
        'D ' seul le cote droit est trace
       /TAIL1 FLOTTANT taille des tetes de fleche
        si non precise : 1/5 de la valeur maxi
on recupere
        PTF1 MAILLAGE definissant les fleches

## @CIRCONS [—] (proc)
Procedure @CIRCONS

PT1 R1 = @CIRCONS ELT1 ;

Objet :

   La procedure @CIRCONS calcule le centre et le rayon du cercle
(sphere) circonscrit(e) a un element de type TRI3 (TET4) en 2D (3D).

Commentaire :

ELT1 = MAILLAGE, 1 element de type TRI3 ou TET4 ;

PT1 = POINT, centre du cercle (sphere) circonscrit(e) ;

R1 = FLOTTANT, rayon du cercle (sphere) circonscrit(e).

## @CLCH [Mecanique Limites] (proc)
Procedure @CLCH

    RIG1 F1 = @CLCH MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 06/2007

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
en contrainte homogene au contour avec un chargment en
contrainte moyenne imposee.

Commentaires :
MAIL0 : Maillage (MAILLAGE)
TAB1 : Contrainte moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Cette procedure fonctionne pour des porosites
   debouchantes uniquement si celles-ci sont "periodiques"

## @CLDH [Mecanique Limites] (proc)
Procedure @CLDH

    RIG1 F1 = @CLDH MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)
-------- G.TREGO (CEA Saclay DEN/DMN/SRMA)

Date : 10/2006

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
en deformation homogene au contour avec un chargment en
deformation moyenne imposee.

Commentaires :
MAIL0 : Maillage (MAILLAGE)
TAB1 : Deformation moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = EXX,
        TAB1.2 = EYY,
        TAB1.3 = EZZ,
        TAB1.4 = EXY,
        TAB1.5 = EXZ,
        TAB1.6 = EYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Cette procedure utilise l'enveloppe du maillage
   volumique. En consequence, le maillage considere n'est
   pas limite a une geometrie parallelepipedique.
   Attention a l'utilisation dans le cas de materiaux
   poreux...

## @CLDHC [Mecanique Limites] (proc)
Procedure @CLDHC

    RIG1 F1 = @CLDHC MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2006

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
en deformation homogene au contour avec un chargment en
contrainte moyenne imposee.

Commentaires :
MAIL0 : Maillage dont l'enveloppe est un
        parallelepipede rectangle (MAILLAGE)
TAB1 : Contrainte moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Pour une utilisation avec la procedure KEFF, preferer
   l'utilisation de @CLDH, plus efficace pour un resultat
   identique.
   Cette procedure fonctionne pour des porosites
   debouchantes uniquement si celles-ci sont "periodiques"

## @CLIM [Mecanique Limites] (proc)
Procedure @CLIM

    RIG1 F1 = @CLIM PROC0 MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2006

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions aux limites

Commentaires :
PROC0 : PROCEDURE, nom de la procedure choisie comme
        condition aux limites parmi:
    @CLPD, @CLPC, @CLCH, @CLDH, @CLDHC, @CLMI1C, @CLMI2C
MAIL0 : Maillage (MAILLAGE)
TAB1 : Contrainte ou deformation moyenne imposee en
        fonction de la procedure choisie (TABLE)
        selon l'ordre suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ;
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Se reporter aux notices des notices @CLPD, @CLPC, @CLCH,
   @CLDH, @CLDHC, @CLMI1C, @CLMI2C pour plus de precisions

## @CLMI1C [Mecanique Limites] (proc)
Procedure @CLMI1C

    RIG1 F1 = @CLMI1C MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 01/2009

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
en mixte normal de type 1 (le deplacement normal et les
contraintes tangentielles respectent des conditions
uniformes) au contour avec un chargment en contrainte
moyenne imposee.

Commentaires :
MAIL0 : Maillage dont l'enveloppe est un
        parallelepipede rectangle (MAILLAGE)
TAB1 : Contrainte moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Cette procedure fonctionne pour des porosites
   debouchantes uniquement si celles-ci sont "periodiques"

## @CLMI2C [Mecanique Limites] (proc)
Procedure @CLMI2C

    RIG1 F1 = @CLMI2C MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 01/2009

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
en mixte normal de type 2 (le deplacement tangntiel et la
contrainte normale respectent des conditions
uniformes) au contour avec un chargment en contrainte
moyenne imposee.

Commentaires :
MAIL0 : Maillage dont l'enveloppe est un
        parallelepipede rectangle (MAILLAGE)
TAB1 : Contrainte moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Cette procedure fonctionne pour des porosites
   debouchantes uniquement si celles-ci sont "periodiques"

## @CLPC [Mecanique Limites] (proc)
Procedure @CLPC

    RIG1 F1 = @CLPC MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2006

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
periodiques et un chargment en contrainte moyenne imposee.

Commentaires :
MAIL0 : Maillage periodique dont l'enveloppe est un
        parallelepipede rectangle (MAILLAGE)
TAB1 : Contrainte moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = SXX,
        TAB1.2 = SYY,
        TAB1.3 = SZZ,
        TAB1.4 = SXY,
        TAB1.5 = SXZ,
        TAB1.6 = SYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Pour une utilisation avec la procedure KEFF, preferer
   l'utilisation de @CLPD, plus efficace pour un resltat
   identique.
   Les maillages de faces en regards doivent etre
   superposables par translation.
   Cette procedure fonctionne pour des porosites
   debouchantes.

## @CLPD [Mecanique Limites] (proc)
Procedure @CLPD

    RIG1 F1 = @CLPD MAIL0 TAB1;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 10/2006

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite et les
forces nodales associees a un jeu de conditions au limites
periodiques et un chargment en deformation moyenne imposee.

Commentaires :
MAIL0 : Maillage periodique dont l'enveloppe est un
        parallelepipede rectangle (MAILLAGE)
TAB1 : Deformation moyenne imposee (TABLE) selon l'ordre
        suivant:
        TAB1.1 = EXX,
        TAB1.2 = EYY,
        TAB1.3 = EZZ,
        TAB1.4 = EXY,
        TAB1.5 = EXZ,
        TAB1.6 = EYZ,
RIG1 : Rigidite associe au chargement (RIGIDITE)
F1 : Forces nodales associees au chargement (CHPOINT)

Remarques :
   Les maillages de faces en regards doivent etre
   superposables par translation.
   Cette procedure fonctionne pour des porosites
   debouchantes.

## @CORIGI [Mecanique Limites] (proc)
Procedure @CORIGI

    RIG1 = @CORIGI MAIL0;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2006

Exemple associe : utilise par les procedures @CLIM

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Cette procedure permet de construire la rigidite associee
au blocage d'un mouvement de corps rigide.

Commentaires :
MAIL0 : Maillage quelconque (MAILLAGE)
RIG1 : Rigidite associee (RIGIDITE)

Remarques :
    Cette procedure est notamment utile pour des geometries
    complexes pour lesquelles le blocage du mouvement de
    corps rigide ne semble pas "evident".

## @COUPLAN [—] (proc)
Procedure @COUPLAN

TAB2 TAB3 = @COUPLAN TAB1 P1 P2 P3 ;

Objet :

   Procedure permettant de couper par un plan la partition de
Voronoi decrite par la table TAB1, resultat de la procedure @P_VORO.

Commentaire :

TAB1 = Objet TABLE, resultat de la procedure @P_VORO ;

P1/P2/P3 = Points du plan de coupe ;

TAB2/TAB3 = TABLEs resultats contenant les points sommets de la
        partition de Voronoi decrite par TAB1 coupee par le
        Plan defini par P1 P2 P3.

## @COUPLE [Maillage Lignes] (proc)
    Procedure @COUPLE
    ----------------- @tole2 @tole3

    MAIL1 = @COUPLE EVOL1 EVOL2 ENT1 ;

    Objet :

La procedure @COUPLE cree un couple i.e un maillage de segments a 2
noeuds de type seg2 a partir de deux EVOLUTIONS.

    Commentaires :

    EVOL1 : Evolution dans le plan YOZ.

    EVOL2 : Evolution dans le plan XOZ.

    ENT1 : Entier valant 1 si le couple est dans le plan XOZ ou
        valant 2 si le couple est dans le plan YOZ.

    Exemple d'utilisation :

     u1 = prog -1.79 -1.73 -1.67 -1.6 -1.49 -1.34 -1.2;
     u2 = prog 0.64 0.32 0.12 -0.01 -0.12 -0.15 -0.16;
     evf = evol manu absc u1 ordo u2;
     evo1Le = @lisse evf 50 0. 40 1;
     uu2 = extraire evo1le ordo;
     uu1 = extraire evo1le absc;
     evo2le = evol manu absci (prog 40*0.04) ordo uu2;
     ec2 = @couple evo2le evo1le 1;

$$$$

## @COUTOR1 [Mathematiques Autres] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

     Procedure @COUTOR1 voir aussi : @FRENET
     ------------------ @COUTOR2

     DS RAY TOR ALPHA BETA = @COUTOR1 ELEM1 CHT CHN CHB ;

 Objet :

Cette procedure calcule la courbure et la torsion d un segment de
ligne.

Commentaire :

        ELEM1 : Objet de type maillage constitue d un seul element de
        type SEG2 ou SEG3.

        CHT : Champ par points du vecteur unitaire de la tangente (type
        CHPOINT) reduit a l element ELEM1 et de composantes
        'TX', 'TY', ('TZ').

        CHN : Champ par points du vecteur unitaire de la normale (type
        CHPOINT) reduit a l element ELEM1 et de composantes
        'NX', 'NY', ('NZ').

        CHB : Champ par points du vecteur unitaire de la binormale (type
        CHPOINT) reduit a l element ELEM1 et de composantes
        'BX', 'BY', ('BZ').

        DS : Longueur de l element ELEM1 (type FLOTTANT).

        RAY : Rayon de courbure de l element ELEM1 (type FLOTTANT).

        TOR : Rayon de torsion de l element ELEM1 (type FLOTTANT).

        ALPHA : Angle de courbure
        (rotation du repere initial autour de la binormale)
        (type FLOTTANT).

        BETA : Angle de torsion
        (rotation du repere initial autour de la tangente)
        (type FLOTTANT).

Remarque 1 :

        La direction de la tangente est celle de la description de la ligne.
        le repere T, N, B, est dans le sens direct.

Remarque 2 :

        Cette procedure est utilisee par la procedure 'FRENET' pour calculer
        les reperes aux extremites de la ligne.

Remarque 3 :

        En dimension 2 : TOR = 0.
        BETA = 0.

## @COUTOR2 [Mathematiques Autres] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

     Procedure @COUTOR2
     ------------------ @FRENET

     CHRT = @COUTOR2 LIG1 CHT CHN CHB ;

Objet :

Cette procedure calcule la courbure et la torsion d une ligne sur
chacun de ses elements.

Commentaire :

        LIG1 : Objet de type maillage qui doit etre constitue d
        elements de type SEG2 ou SEG3.

        CHT : Champ par points du vecteur unitaire de la tangente
        (type CHPOINT) de composantes 'TX', 'TY', ('TZ').

        CHN : Champ par points du vecteur unitaire de la normale
        (type CHPOINT) de composantes 'NX', 'NY', ('NZ').

        CHB : Champ par points du vecteur unitaire de la binormale
        (type CHPOINT) de composantes 'BX', 'BY', ('BZ').

        CHRT : Champ par elements de composantes 'R' et 'T'
        (type MCHAML).

Remarque 1 :

        La direction de la tangente est celle de la description de la ligne.
        le repere T, N, B, est dans le sens direct.

Remarque 2 :

        En dimension 2 : la valeur de la composante T de CHRT est nulle sur
        tous les elements.

Remarque 3 :

        Le champ par elements CHRT est de sous-type 'GRAVITE'.

## @CRIPL [Mecanique Resolution] (proc)
   Procedure @CRIPL

   Objet :

Cette procedure est appelee en interne par la procedure @STATIO

## @DEDUIRE [Maillage Manipulation] (proc)
Procedure @DEDUIRE
------------------ DEDU

        OBJ1 = @DEDUIRE OBJ2 MAIT_ANC MAIT_NOU ;

Objet :

La procedure @DEDUIRE construit a partir du maillage OBJ2 et du
maillage de noeuds (de OBJ2) maitres MAIT_ANC un nouvel objet
ou l'ensemble de noeuds maitres est devenu MAIT_NOU.

## @DEFA2DL [Post-traitement Affichage] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR MM. J.Y. COGNARD & D. DUREISSEIX
        L.M.T. STRUCTURES & CMAO

   Procedure @DEFA2DL

   MAI1 = @DEFA2DL LIG0 PIN1 TAI1 TYP1 (DES1) (LOG1)

   Objet :

Procedure pour construire une ligne d'appuis en 2D (utilise @DEFA2DP)
    DEFinition d'Appuis en 2D pour une Ligne

on envoie
        LIG0 MAILLAGE ligne support des appuis
        PIN1 POINT pour definir l'interieur du domaine
        TAI1 FLOTTANT pour definir la taille
        TYP1 MOT pour definir le type d'appui sur la ligne
        'roul' : ligne d'appuis simples
        'enca' : ligne d'encastrements
        'mixt' : encastement du premier point plus
        ligne d'appuis simples
        DES1 /MOT pour une verification
        'trac' : pour le trace des appuis un par un
        LOG1 /LOGIQUE pour l'espacement des appuis
        VRAI l'espacement mini est 2.*TAI1
        FAUX un appui tous les points de LIG0
on recupere
        MAI1 MAILLAGE definissant la ligne d'appui

## @DEFA2DP [Post-traitement Affichage] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR MM. J.Y. COGNARD & D. DUREISSEIX
        L.M.T. STRUCTURES & CMAO

   Procedure @DEFA2DP

   MAI1 = @DEFA2DP TAI1 ORI1 VEC1 TYP1 ;

   Objet :

Procedure pour construire un appui en 2D (voir @DEFA2DL)
    DEFinition d'un Appui en 2D pour un Point

on envoie
        TAI1 FLOTTANT pour definir la taille
        ORI1 POINT pour definir l'origine
        VEC1 POINT vecteur interieur pour l'orientation
        TYP1 MOT pour definir le type d'appui
        'roul' pour un appui simple
        'enca' pour un encastrement (par defaut)
on recupere
        MAI1 MAILLAGE definissant l'appui

## @DEFPL [Mecanique Resolution] (proc)
   Procedure @DEFPL

   Objet :

Cette procedure est appelee en interne par la procedure @STATIO

## @DESLIS [Post-traitement Affichage] (proc)
Procedure @DESLIS

@DESliS | LISTREE1 |  ( 'LOGX'  ) ;
        | LISTENT1 |  ( 'LOGY'  ) ;
        ( 'GRIL' ) ;
        ( 'XBOR' XINF XSUP ) ;
        ( 'YBOR' YINF YSUP ) ;
        ( 'MIMA' ) ;
        ( 'DATE' ) ;
        ( 'LOGO' ) ;
        ( 'CHOI' (N1 (N2 (N3 ...))) ) ;
        ( 'TITR' 'bla bla...' ) ;
        ( 'TITX' 'blax' ) ;
        ( 'TITY' 'blay' ) ;
        ( 'AXES' ) ;
        ( 'NCLK' ) ;

 Objet
 Cette procedure permet de tracer a l'aide de l'operateur DESSIN
 l'evolutions des valeurs contenue dans la liste entree

 Commentaires

 LISTREE1 liste de valeurs reelles a tracer (type LISTREEL)

 LISTENT1 liste de valeurs entieres a tracer (type LISTENTI)

 Tous les mot-clefs sont des options generales de DESSIN
        (Cf. DESS) les mots possibles sont : 'LOGX' 'LOGY' 'GRIL'
        'CARR' 'XBOR' 'YBOR' 'DATE' 'LOGO'
        'TITR' 'TITX' 'TITY' 'AXES' 'NCLK'.

 On affiche toujours les valeurs min et max de la liste

## @ENCA [Post-traitement Affichage] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR M. D. DUREISSEIX
        L.M.T. STRUCTURES & C.M.A.O.

   Procedure @ENCA

   PTF1 = @ENCA TAIL1 MAIL1 VEC1 ;

   Objet :

Procedure pour construire un vrai ENCAstrement en 2D

on envoie
        TAIL1 FLOTTANT pour definir la taille
        MAIL1 MAILLAGE ligne sur laquelle il y a encastrement
        VEC1 POINT vecteur pour l'orientation des hachures
        (normale interieure)
on recupere
        PTF1 MAILLAGE definissant l'encastrement

## @EXCEL1 [—] (proc)
 CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
A DISPOSITION DE LA COMMUNAUTE CASTEM2000
  PAR Ch. LABORDERIE (LMT - ENS Cachan )

 Procedure @EXCEL1

 @EXCEL1 EVOL1 FICH1 ;

 Objet :

 Cette procedure met un objet EVOLUTION dans un fichier FICH1
 utilisable sous EXCEL. Le ; sert de separateur entre les deux
 colonnes de chiffres.

 Commentaires :

 EVOL1 : objet de type EVOLUTION

 FICH1 : nom du fichier resultat (type MOT)

## @FIS_1 [Maillage Autre] (proc)
   Procedure @FIS_1

   Objet :

Procedure appelee par @FIS_3DS

## @FIS_2 [Mecanique Rupture] (proc)
   Procedure @FIS_2

   Objet :

Procedure appelee par @FIS_3DS

## @FIS_3 [Mecanique Rupture] (proc)
   Procedure @FIS_3

   Objet :

Procedure appelee par @FIS_3DS

## @FIS_3DS [Maillage Autres] (proc)
    Procedure @FIS_3DS

VTOT LFF LEVREINF SAR SLAF SINF SAV_S SSUP_S SLAT_S BOUDIN EP3 =

    @FIS_3DS C A LO TO HO NT NC NS RC0 RC1 RC2 RC3
        ALPHA NDT NSDT XL XT XH ;

    Objet :

    La procedure @FIS_3DS permet de creer un bloc fissure 3D massif
en utilisant des elements Hexaedres a 20 noeuds et prismes a 15
noeuds. La fissure est supposee elliptique.

      Commentaire :

*
* c demi grand axe de l'ellipse
* a demi petit axe de l'ellipse
* rc0 rayon du tore
* rc1 coefficient multiplicateur du parametre rc0
* definissant l'epaisseur de la premiere couronne
* de deraffinement
* rc2 coefficient multiplicateur du parametre rc0
* definissant l'epaisseur de la deuxieme couronne
* de deraffinement
* rc3 coefficient multiplicateur du parametre rc0
* definissant l'epaisseur de la troisieme couronne
* de deraffinement (si ndt=2)
* nc nombre de couronnes
* ns nombre de secteurs sur 90 degres
* nt nombre de divisions sur un quart d'ellipse
* eps demi-angle d'ouverture de la fissure (degres)
* lo longueur du bloc
* to largeur du bloc
* ho hauteur du bloc
* ndt nombre de couronnes de deraffinement (1 ou 2)
* nsdt Nombre de secteurs sur 90 degres au niveau des
* couronnes de deraffinement des tranches (2 ou 4)
* beta impose le decoupage le long de la generatrice
* alpha impose l'angle des differentes tranches
* xl impose le nombre d'elements pour la prolongation
* du bloc initial suivant l'axe x (longueur)
* xt impose le nombre d'elements pour la prolongation
* du bloc initial suivant l'axe y (largeur)
* xh impose le nombre d'elements pour la prolongation
* du bloc initial suivant l'axe -z (hauteur)

En sortie differentes parties du maillage sont nommees Vtot est le
maillage complet.

## @FIX [Mathematiques Autres] (proc)
   Procedure @FIX
   -------------- ENTI

Syntaxe : MOT2 = @FIX FLOT1 ENTI1 (MOT1)

      Objet :

  Procedure renvoyant, a partir d'un reel FLOT1 et d'un nombre de
  decimales ENTI1, la troncature du reel, avec ENTI1 chiffres apres la
  virgule, sous la forme du 'MOT' MOT2.

      Commentaire :

  FLOT1 : nombre que l'on souhaite tronquer

  ENTI1 : nombre de chiffres apres la virgule

  MOT1 : mot facultatif valant 'EXPOSANT' et forçant l'ecriture du
        nombre sous la forme 'aEb' (a etant la mantisse 'ET' b
        l'exposant).

      Remarques :

  1 - On passe automatiquement en notation EXPOSANT si l'affichage ne
      contiendrait autrement que des 0 ou si FLOT1 depasse 1.D10,

  2 - Ne marche pas avec de grands nombres,

  3 - Resultat lie a la precision machine

## @FRENET [Mathematiques Autres] (proc)
     CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
    A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

 Procedure @FRENET
 ----------------- @COUTOR2

 CHT CHN CHB = @FRENET LIG1 ('TRACE') (OEIL1);

Objet :

 Cette procedure calcule le repere de Frenet le long d'une ligne

 Commentaire:

 LIG1 : objet de type MAILLAGE qui doit etre constitue d'elements
        de type SEG2 ou SEG3.

 TRACE : Mot-cle indiquant qu'il faut tracer le repere de
        Frenet.

 OEIL1: objet de type POINT indiquant le point de vue du trace
        pour une ligne en 3D.

 CHT : champ par points du vecteur unitaire de la tangente
        (type CHPOINT) de composantes 'TX', 'TY', 'TZ'.

 CHN : champ par points du vecteur unitaire de la normale
        (type CHPOINT) de composantes 'NX', 'NY', 'NZ'.

 CHB : champ par points du vecteur unitaire de la binormale
        (type CHPOINT) de composantes 'BX', 'BY', 'BZ'.

 Remarque 1:

 En dimension 2 les composantes BX et BY de CHB ont une valeur
 nulle en tout point .

 Remarque 2:

 La direction de la tangente est celle de la description de la
 ligne .Le repere (t,n,b) est dans le sens direct .

 Remarque 3:

 Il est necessaire que la courbe LIG1 comprenne au moins 5
 elements.

 Remarque 4:

 Si TRACE n'est pas specifie le trace du repere ne sera pas
 effectue.

## @GATTPAR [Mecanique Modele] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DES UTILISATEURS DES MODELES
        GATT_MONERIE ET UO2_DCN
        PAR C. STRUB ( CEA/DMT/SEMT/LM2S )

   Procedure @GATTPAR

      TAB1 = @GATTPAR NOMFIC ('TOUTATIS') ;

Objet :

    Cette procedure peut etre utilisee avant l'appel a l'operateur
    'MATE', dans le cas de l'utilisation des modeles GATT_MONERIE ou
    UO2_DCN (cf. operateur 'MODE'), pour lire des donnees sur un
    fichier.

En entree :

NOMFIC nom du fichier contenant differentes donnees necessaires
        a la construction des parametres materiau (objets CASTEM)
        pour le modele GATT_MONERIE ou UO2_DCN (type MOT).

TOUTATIS : mot-cle dans le cadre d'une utilisation avec TOUTATIS
        certaines donnees necessaires a la construction des
        parametres materiau, sont alors definies dans le code
        TOUTATIS.

En sortie :

TAB1 table dont les indices de type MOT sont des noms de
        composantes materiau a introduire dans le cadre du modele
        GATT_MONERIE ou UO2_DCN. Chaque objet indexe dans TAB1
        peut etre utilise dans l'operateur 'MATE'.

## @GLOBAL [Post-traitement Analyse] (proc)
     Procedure @GLOBAL

EVOL2=@GLOBAL TAB1 BLO1 EVOL1 MOT1;

    Objet :

  La procedure @GLOBAL construit un objet EVOL2 de type evolution
  contenant :
  En abscisse un listreel obtenu par interpolation de la
  liste des pas de temps successifs contenus dans TAB1 sur EVOL1.
  En ordonnee un listreel contenant les valeurs de la composante
  de nom MOT1 de la resultante des reactions successives de BLO1.

TAB1 : TABLE resultat de NONLIN
BLO1 : RIGIDITE blocage permettant de calculer les reactions
EVOL1 : EVOLUTION contient evolution d'un deplacement en fonction
        du temps.
MOT1 : MOT nom de la composante de la resultante
EVOL2 : EVOLUTION resultat contenant evolution de la composante
        desiree de la resultante des reactions en fonction
        du deplacement contenu dans EVOL1

    Exemple d'utilisation :

exemple de description des objets avant un calcul non lineaire

BLO1=BLOQ GEO1 UY;
CHP1=DEPI BLO1 1.;
LIST1=PROG 0. PAS 0.1 1.;
LIST2=PROG 0. PAS 0.01 0.05 PAS -0.01 0.0;
EVOL1=EVOL MANU TEMPS LIST1 FLECHE LIST2;
CHAR1=CHARGEMENT EVOL1 CHP1;
LT1=PROG 0. PAS 0.033 1.;
NONLIN TAB1 MOD1 MAT1 (RIG1 ET BLO1 ET BLO2 ET SYM1) CHAR1 LT1;

utilisation de la procedure

EVOL2=@GLOBAL TAB1 BLO1 EVOL1 FY;
DESSIN EVOL2;

## @HELICE [Maillage Autres] (proc)
     CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
    A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

Procedure @HELICE

GEO2 GEO3 = @HELICE GEO1 TYP1 P0 V0 PAS ALPHA NP ;

Objet :

Cette procedure cree le maillage engendre par une transformation
helicoïdale.

Commentaire:

GEO1 : Base de l'helice (POINT ou MAILLAGE de type ligne
        ou surface )

TYP1 : MOT definissant le type de la base, pouvant prendre
        l'une des trois valeurs 'POIN' 'LIGN' ou 'SURF'

P0 : POINT de l'axe de l'helice

V0 : Vecteur directeur de l'axe de l'helice (de type POINT)

PAS : Pas de l'helice (de type FLOTTANT)

ALPHA : Angle de rotation autour de l'axe de l'helice (de type
        FLOTTANT)

NP : Nombre d'elements crees entre la base et le sommet de
        l'helice (de type ENTIER)

GEO2 : Sommet de l'helice, homeomorphe a GEO1 (POINT ou MAILLAGE
        de type ligne ou surface )

GEO3 : MAILLAGE de la trajectoire de l'helice, de type ligne
        surface ou volume

Remarque :

Si GEO1 est un point GEO2 sera un point et GEO3 une ligne.

Si GEO1 est une ligne GEO2 sera une ligne et GEO3 une surface.

Si GEO1 est une surface GEO2 sera une surface et GEO3 un volume.

## @HISTOGR [Post-traitement Affichage] (proc)
    Procédure @HISTOGR

        (EVOL2 TABL2) = @HISTOGR LREE1 (TABL1) (LOGI1)

    Objet :

    Création/Tracé de données sous forme d'histogramme

    Commentaire :

    LREE1 = Objet LISTREEL contenant les données à tracer. A chaque
        valeur de cette liste sera associée une barre de
        l'histogramme.

    LOGI1 = Variable LOGIQUE indiquant si on veut récupérer le graphe
        sous forme d'objets EVOL2 et TABL2 (à transmettre à DESS)

    TABL1 = Objet TABLE controlant l'apparence du graphique :

        - Indice 'COUL' [MOT ou LISTMOTS]
        = Couleur(s) des barres (défaut='DEFA')

        - Indice 'NOMS' [TABLE]
        = Legendes affectees a chaque barre (défaut=numero).

        - Indice 'LARG' [LISTREEL]
        = Largeurs des barres (défaut=[0.8 ... 0.8])

        - Indice 'ESPA' [FLOTTANT]
        = Espace entre 2 barres (défaut=0.2)

        - Indice 'HPOS' [FLOTTANT]
        = Décalage horizontal du graphique (défaut=0.)

        - Indice 'INVE' [LOGIQUE]
        = Tracer les barres de droite à gauche ? (défaut=FAUX)

        - Indice 'DESS' [MOT]
        = Options passées à DESS (défaut=pas de tracé)
        La présence de ce mot-clé induit que @HISTOGR procède au
        tracé de l'histogramme (indépendemment de LOGI1)

    Exemple :

* Visualisation d'une distribution aléatoire gaussienne

    NN = 10000 ;

    LTIRAG1 = BRUI 'BLAN' 'GAUS' 0. 2. NN ;
    LTIRAG1 = LTIRAG1 - (MASQ LTIRAG1 'INFERIEUR' 0.) ;
    LTIRAG1 = ENTI LTIRAG1 ;

    IMIN1 = MINI LTIRAG1 ;
    NC = (MAXI LTIRAG1) - IMIN1 + 1 ;
    LCOMPT1 = PROG NC*0. ;

    REPE BLOC1 NN ;
        IPOS1 = (EXTR LTIRAG1 &BLOC1) + 1 - IMIN1 ;
        ICOMPT1 = EXTR LCOMPT1 IPOS1 ;
        REMP LCOMPT1 IPOS1 (ICOMPT1 + 1.) ;
    FIN BLOC1 ;

    TOPT1 = TABL ;
    TOPT1 . 'HPOS' = FLOT IMIN1 ;
    TOPT1 . 'DESS' = 'GRIL AXES' ;

    @HISTOGR LCOMPT1 TOPT1 FAUX ;

* autre exemple : cf. dessin.dgibi

## @INCLUSI [—] (proc)
Procedure @INCLUSI

TAB2 = @INCLUSI TAB1 DPAR1 DEXC1 (DENS1) (ITRA1) ;

Objet :

La procedure @INCLUSI maille un echantilon numerique cubique
d'un materiau constitue de particules spheriques de meme taille,
en inclusions dans une matrice.

Pour cela, elle s'appuie sur la partition de Voronoi des centres des
particules, obtenue a l'aide des procedures @P_VORO et @P_BOIT2.

Commentaire :

TAB1 = TABLE, resultat de la procedure @P_BOIT2 ;

DPAR1 = FLOTTANT, diametre des particules ;

DEXC1 = FLOTTANT, distance minimum entre centres des particules :
        DEXC1 doit etre strictement superieure a DPAR1 ;

DENS1 = FLOTTANT, densite (taille) "moyenne" des elements du
        maillage, prise egale au quart de la taille moyenne des
        cellules de Voronoi par defaut. Toutefois, @INCLUSI
        raffine automatiquement le maillage pour avoir au moins
        2 elements finis dans chaque ligament de matrice, dont
        l'epaisseur minimale est egale a (DEXC1-DPAR1) ;

ITRA1 = LOGIQUE, active des traces.

TAB2 = TABLE, sous-indicee comme suit :
. 'MAIL' = MAILLAGE des particules et de la matrice ;
. 'PART' = MAILLAGE des particules ;
. 'MATR' = MAILLAGE de la matrice ;
. 'MPT' = MAILLAGE de points, centres des particules ;

Si PT1 est un point de TAB2 . 'MPT' alors :
. PT1 . 'MAIL' = maillage de la particule de centre PT1 et de la
        portion de matrice comprise dans la cellule de
        Voronoi indicee par PT1 dans TAB1 ;
. PT1 . 'PART' = maillage de la particule de centre PT1 ;
. PT1 . 'MART' = maillage de la portion de matrice ;
. PT1 . 'MPT' = MAILLAGE de points, centres des particules voisines
        a PT1 ;
Si PT2 est un point de TAB2 . PT1 . 'MPT' alors :
. PT1 . PT2 . 'MATR' : maillage de la face commune aux sous-maillages
        des portions de matrice relatives aux particules de
        centres PT1 et PT2 dans la partition de Voronoi
        definie par TAB1.

Remarques :
   La procedure @INCLUSI ne reussit pas toujours a generer le mail-
-lage demande, notamment lorsque des particules sont tangentes a une
face ou a une arete du cube. Pour ameliorer sa robustesse, elle
s'autorise a deplacer ou a aplanir legerement les particules qui
posent probleme. L'utilisateur en est informe par un message. Il
peut donc etre utile de faire une copie des affichages, en les
redirigeant, par exemple, dans un fichier.

## @INITIA [Mecanique Resolution] (proc)
   Procedure @INITIA

   Objet :

Cette procedure est appelee en interne par la procedure @STATIO

## @INTLIN [Post-traitement Analyse] (proc)
     Procedure @INTLIN

Y0 = @INTLIN LI1 LI2 X0;

    Objet :

  La procedure @INTLIN permet de realiser l interpolation lineaire
d un objet X0 de type FLOTTANT sur la base de deux listes LI1 et LI2
de type LISTREEL et renvoie un objet Y0 de type FLOTTANT.

LI1 : LISTREEL Liste d abscisses
LI2 : LISTREEL Liste d ordonnees
X0 : FLOTTANT Objet a interpoler
Y0 : FLOTTANT Objet interpole

## @ISOSURF [Entree-Sortie Entree-Sortie] (proc)
 Procedure @ISOSURF

 Syntaxe : MAIL1 CHPF1 = @ISOSURF MASSIF0 LIS1 HANA1 ;

    Objet :

Procedure qui extrait les isosurfaces dont les valeurs sont
listees dans une liste de reels (LIS1) d'un champoint (HANA1)
appuye sur un maillage (MASSIF0).

Le resultat final est constitue du maillage surfacique
regroupant l'ensemble des isosurface MAIF1 et du champoint
CHPF1 des isovaleurs LIS1 appuyees sur MAIF1.

Postraitement TRAC CACH MAIF1 CHPF1 ;

    Commentaire :

Entree :
MASSIF0 : Maillage support du champoint

LIS1 : Liste (LISTREEL) d'isovaleurs a rechercher

HANA1 : Champoint appuye sur MASSIF0

Sortie :
MAIF1 : Maillage de l'ensemble des isosurfaces

CHPF1 : Champoint des isovaleurs LIS1 appuyees sur MAIF1

    Remarques :

1 - Attention la procedure utilise une elimination des points
    doubles des isosurfaces extraites

## @KEFF [Mecanique Resolution] (proc)
Procedure @KEFF

    K C D = @KEFF MODTOT MATTOT PROC AMPL0 CONV0 VISU0;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2008

Exemple associe : test_AMITEX.dgibi

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Determination du tenseur d'elasticite apparent a partir d
une microstructure,de ses parametres materiaux et d'un
choix de conditions aux limites. Cette
evaluation est realisee a partir de 6 calculs elementaires.

Commentaires :
    MODTOT : objet modele (MODEL)
    MATTOT : champ de caracteristiques elastiques associees
        au modele (CHMAL)
    PROC : PROCEDURE utilisee pour definir les conditions
        aux limites, au choix:
        @CLPC, @CLPD, @CLDH, @CLDHC, @CLCH, @CLMI1C,
        @CLMI2C
    AMPL0 : REEL definissant l'amplitude des chargements
    CONV0 : ENTIER, definissant la convention utilisee
        pour decrire le tenseur de rigidite apparent
        0 = convention de Voigt
        1 = convention "racine de 2"
    VISU0 : TABLE gerant les visualisations
        VISU0 ; 1 = 0 ou 1, pour les deformees
        VISU0 . 2 = 0 ou 1, pour les champs de contrainte
        VISU0 . 3 = 0 ou 1, pour les champs de deformation

    K : TABLE, tenseur apparent
    C : TABLE, contraintes moyennes pour les 6 chargements
    D : TABLE, deformations moyennes pour les 6 chargements

## @LACALC [Mecanique Resolution] (proc)
 Procedure @LACALC

 DEP1 = @LACALC TAB_LAM CLIM FF (RIG2) ;

 Objet:

 Cette procedure permet d'effectuer un calcul elastique
statique sur un maillage compose de plusieurs zones en
materiau composite multicouche.

 En entree:

 TAB_LAM Table caracteristique du multicouche (TABLE)
 CLIM Conditions aux limites pour la structure (RIGIDITE)
 FF Forces (CHPOINT)
 RIG2 Raideurs additionnelles pour les parties de la
        structure qui ne sont pas composees par des
        multicouches (Optionnel) (RIGIDITE)

 En sortie:

 DEP1 Champ de deplacement (CHPOINT)

## @LACRIT [Mecanique Resolution] (proc)
Procedure @LACRIT
----------------- @LASIEP

TAB_CRIT = @LACRIT TAB_LAM NZON TAB_SIEP FM MOT_CRIT ;

Objet:

Cette procedure permet d'effectuer un calcul couche par
couche et element par element du "failure rate" relatif
a un des criteres suivants:

        MAXSTRESS Maximum Stress
        MAXSTRAIN Maximum Strain
        TSAI-WU Tsai-Wu
        TSAI-HILL Tsai-Hill
        HOFFMANN Hoffmann

En entree:

TAB_LAM Table caracteristique (TABLE)
NZON Numero de l'i-eme zone
TAB_SIEP Table des contraintes et des deformations (TABLE)
FM Facteur Multiplicatif des contraintes ou
        des deformations (FLOTTANT)
MOT_CRIT Mot cle pour selectionner le critere de rupture
        (MOT)

En sortie:

TAB_CRIT Table des "failure rates" (TABLE)

## @LAFAIL [Mecanique Resolution] (proc)
Procedure @LAFAIL

@LAFAIL TAB_LAM TAB_FAIL ;

Objet:

Cette procedure permet de verifier la resistance limite
d'un multicouche par mise a zero des proprietes elastiques
des couches qui arrivent a rupture.

avec

TAB_LAM Table caracteristique du multicouche
TAB_FAIL Table caracteristique pour conduire un calcul
        de resistance pour un multicouche.
        La table contient en entree:

        Index Description

        'SOUSTYPE' MOT de valeur 'LAMINATE_FAIL'
        'TYP_FAIL' MOT pour identifier le type de verification
        que nous voulons effectuer.
        Celui-ci peut valoir:
        'FPF' : First Ply Failure (Defaut)
        'LPF' : Last Ply Failure
        'ITERMAX' ENTIER nombre maximum des iterations pour
        converger. (Defaut 10)
        'PREC' FLOTTANT indique la valeur de la
        precision de convergence. (Defaut 1.e-2)
        'CLIM' Objet RIGIDITE des conditions aux limites
        'CHARG' Objet CHPOINT du chargement
        'RIG2' Objet RIGIDITE pour une raideur
        additionnelle a cela du multicouche
        (Optionnel)

        et en sortie:

        'FMF' Facteur multiplicatif du chargement pour
        le First Ply Failure
        'NPF' Indice de la premiere couche cassee
        'NZF' Indice de la zone a laquelle appartient
        la premiere couche cassee
        'FML' Facteur multiplicatif du chargement pour
        le Last Ply Failure

## @LAGRAPH [Mecanique Resolution] (proc)
Procedure @LAGRAPH
--------------- @LACALC

TSIG = @LAGRAPH TAB_LAM DEPL1 NZON VET1 P0 ;

Objet :

Cette procedure permet de visualiser la variation des contraintes
suivant l'epaisseur par rapport a un point demande.

En entree:

TAB_LAM Table caracteristique du multicouche
DEPL1 Champ des deplacements
NZON Numero de la zone demandee
VET1 Direction d'orientation du champ des contraintes
P0 Point pur lequel on veut visualiser les contraintes

En sortie:

TSIG Table des contraintes

## @LAKAPPA [Mecanique Modele] (proc)
Procedure @LAKAPPA

@LAKAPPA TAB_LAM ;

Objet :

Cette procedure permet de modifier les modules de cisallement
G13 et G23 en function du calcul des facteurs correttives de
la stratification des couches.

En entree

TAB_LAM Table caracteristique du multicouche composite

## @LALIST [Mecanique Modele] (proc)
Procedure @LALIST

@LALIST TAB_COMP ;

Objet:

Cette procedure produit une liste des caracteristiques, zone
par zone, des multicouches contenus dans la table de definition

En entree:

TAB_COMP table caracteristique des multicouches composites

## @LAMASS [Mecanique Modele] (proc)
Procedure @LAMASS

MAS1 = @LAMASS TAB_LAM ;

Objet :

Cette procedure calcule les matrices de masse d'un
multicouche composite.

En entree

TAB_LAM Table caracteristique du multicouche composite

En sortie

MAS1 Resultat de type RIGIDITE de sous-type MASSE.

## @LAMAT [Mecanique Modele] (proc)
Procedure @LAMAT

 TAB_MAT = @LAMAT TAB_LAM NZONE ;

Objet:

Cette procedure permet d'avoir, selon le type d'homogeneisation
demande:
- la matrice de Hooke homogeneisee et les caracteristiques
  equivalentes (si TAB_ZONA.'TIPO'='OMOG')
- les objets de type MATERIAU relatif a chaque couche excentree
  (si TAB_ZONA.'TIPO'='MLAY')

 En entree

 TAB_LAM Table des caracteristiques du multicouche

 NZONE Numero de l'i-eme zone (Entier)

 En sortie

 TAB_MAT Table des objets MATERIAU ou MAHOOK et CARACTER pour
        la i-eme zone (index MAT et CAR).

## @LAREAD [Mecanique Modele] (proc)
Procedure @LAREAD

@LAREAD TAB_LAM (NUNIT) (NOM_FILE) ;

Objet :

Cette procedure permet de completer une table des caracteristiques
des multicouches a partir des donnes contenus en un fichier de
structure opportune.

En entree:

TAB_LAM Table caracteristique des multicouches composites
        avec les informations suivantes:
        TAB_LAM.TIPO : option de calcul (Mot)
        MLAY ou OMOG
        TAB_LAM.I : info sur la i-eme zone (Table)
        TAB_LAM.I.MAIL : MAILLAGE
        TAB_LAM.I.FELF : Type d'elements (ListMots)
        TAB_LAM.I.METRIF : Method de references (Mot)
        DIRE ou RADI
        TAB_LAM.I.DIRRIF : Direction de references (Point)
        TAB_LAM.I.DIRNOR : Direction normal (Point)
NUNIT*ENTIER Numero unite de laquelle lire les donnees (Defaut 2)
NOM_FILE*MOT Nom du fichier sur lequel on veut effectuer
        la lecture (Optionnel)

En sortie:

TAB_LAM Table caracteristique des multicouches composites

Note
Pour connaitre la structure du fichier des donnes et
de la table TAB_LAM voir les rapports a sujet des
materiaux composites multicouches dans Castem 2000.

## @LARIG [Mecanique Modele] (proc)
Procedure @LARIG

RIG1 = @LARIG TAB_MAT ;

Objet:

Cette procedure permet de calculer la matrice de raideur du
multicouche relatif a une zone soit dans le cas de couche
excentree soit dans le cas de multicouche homogeneisee.

En entree

TAB_MAT Table des objets de type MATERIAU ou MAHOOK et
        CARACTER (index MAT et CAR)

 En sortie

 RIG1 Objet de type RIGIDITE pour la zone consideree

## @LASIEP [Mecanique Resolution] (proc)
Procedure @LASIEP
----------------- @LACALC

TAB_SIEP = @LASIEP TAB_LAM NZON DEP1 (MOT1) ;

Objet:

 Cette procedure permet de calculer couche par couche les
 contraintes et les deformations pour une zone donnee et les
 reporte dans le systeme de reference associe a la direction
 de reference pour l'orthotropie (DIRRIF).

En entree:

TAB_LAM Table caracteristique du multicouche
NZON Numero de l'i-eme zone (Entier)
DEP1 Champ de deplacement
MOT1 Mot cle avec lequel on peut demander les champs
        de contraintes et de deformations ensemble ou
        separes.
        Elle est optionnelle et peut valoir :
        'ALL' : tous le deux (Defaut)
        'SIG' : contraintes seules
        'EPS' : deformations seules

 En sortie:

 TAB_SIEP Table avec les champs de contraintes et de deformations

## @LAVERG [Mecanique Resolution] (proc)
Procedure @LAVERG

@LAVERG TAB_CRIT NPLY OEIL1 ;

Objet :

Cette procedure permet d'effectuer une verification graphique
du "failure rate" relatif a un des criteres de rupture.

En entree:

TAB_CRIT Table des "failure rates" couche par couche
        (Voir la procedure LACRIT)
NPLY Numero de la couche qu'on veut verifier
OEIL1 Oeil (POINT)

## @LAVIS [Mecanique Modele] (proc)
Procedure @LAVIS

@LAVIS TAB_LAM NUM_ZONA ;

Objet :

Cette procedure permet de montrer la stratification des couches
pour une zone donnee.

En entree

TAB_LAM Table caracteristique du multicouche composite
NUM_ZONA Numero de la zone a montrer.

## @LIREENT [Entree-Sortie Entree-Sortie] (proc)
    Procedure @LIREENT

        ENT1 = @LIREENT ENT2 ENT3 ;

    Objet :

    Cette procedure permet, dans une utilisation interactive,
d'acquerir de la part de l'utilisateur un nombre entier compris
entre deux bornes.
    En cas d'erreur, un message apparait a l'ecran.

    Commentaire :

    ENT2 : borne inferieure (type ENTIER)

    ENT3 : borne superieure (type ENTIER)

    ENT1 : nombre entier obtenu (type ENTIER)

    Remarque :

    Les operandes doivent etre entres dans l'ordre indique
dans la syntaxe.

## @LIRERIS [Entree-Sortie Entree-Sortie] (proc)
    Procedure @LIRERIS

        LOG1 = @LIRERIS ;

    Objet :

    Cette procedure permet, dans une utilisation interactive,
d'acquerir de la part de l'utilisateur une reponse OUI ou NON.
    En cas d'erreur, un message apparait a l'ecran.

    Commentaire :

    LOG1 : objet booleen (type LOGIQUE)

## @LISPA16 [Mecanique Resolution] (proc)
 Procedure @LISPA16

    @LISPA16 TAB1 TAB2 ;

        TAB1.'FAT' .'CC' .'ROO2' .'FLU' .'CT'
        .'EPS' .'A316'
        .'MFIS' .'MTOT' .'OBJ' .'OBJT'
        .'MAT' .'MATT' . 'CAR' .'CART'
        .'BLO'

        TAB2.'DP' .'DC' .'PA' .'PB' .'CA'
        .'CB'
        .'DPTH' .'DCTH' .'TPSM'

 Objet :

 Cette procedure evalue la propagation en fatigue-fluage le long d'un
front de fissure modelise par des elements LISP, en fonction du niveau
de sollicitation, en appliquant le procedure de l'Annexe A16 du RCC-MR
(Rapport DMT 94/043).
 Pour l'acier 316, les caracteristiques du materiau a 525°C sont deja
rentrees dans la procedure.
 Cette procedure a ete developpee dans le cadre d'un travail presente
dans le rapport 94/612.

 Description des arguments d'entres et de sortie :

 1) Arguments d'entree :

   TAB1 (type TABLE) : table contenant les donnees du materiau ( a noter
   ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨ que les unites sont a respecter).

    * Pour un materiau autre que A316

     -> donnees en fatigue

      TAB1.FAT.'COEFFICIENT' : coefficient C de la loi de propagation
        n
        de Paris da/dN = C (DKeff).

      TAB1.FAT.'EXPOSANT' : exposant n de la loi de propagation
        n
        de Paris da/dN = C (DKeff) .

      C et n sont entres pour un DKeff exprime en MPaVm et da/dN en
      m/cycle.
      TAB1.CC.'EPS' : abscisses de la courbe de traction
        cyclique du materiau.

      TAB1.CC.'SIG' : ordonnees de la courbe de traction
        cyclique du materiau;

      TAB1.'ROO2' : limite d'elasticite du materiau a 0,2%.

    -> donnees en fluage

      TAB1.FLU.'COEFFICIENT' : coefficient A de la loi de propagation en
        fluage
        *q
        da/dt = A C .

      TAB1.FLU.'EXPOSANT' : exposant q de la loi de propagation en
        *q
        fluage da/dt = A C .

      TAB1.CT.'EPS' : abscisses de la courbe de traction
        monotone du materiau.

      TAB1.CT.'SIG' : ordonnees de la courbe de traction
        monotone du materiau.

      TAB1.EPS.'COEFFSEC' : coefficient C de la loi de fluage
        n
        secondaireEpsf = 100 C sig .

      TAB1.EPS.'EXPSEC' : exposant n de la loi de fluage secondaire
        n
        Epsf = 100 C sig .

        *
      A et q sont entres pour un C exprime en MPam/h et un da/dt en m/h.
      C est entre pour les contraintes exprimees en MPa.

    * Si le materiau est l'acier 316

      TAB1.'A316' : VRAI (objet de type LOGIQUE)

      Cette option contient les lois de comportement necessaires au
      calcul en fatigue-fluage pour l'acier 316 a 525°C. On a tenu
      compte du fluage primaire et du fluage secondaire.

   TAB2 (type TABLE) : table contenant les donnees du chargement
   ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨

      TAB2.'DP' : objet de type CHPOINT de forces appliquees
        a la structure pour la contribution primaire
        du chargement en fatigue.

      TAB2.'DC' : objet de type CHPOINT de forces appliquees a
        la structure pour le chargement complet de
        fatigue.

      TAB2.'PA' : objet de type CHPOINT de forces appliquees a
        la structure pour la contribution primaire du
        chargement A.

      TAB2.'PB' : objet de type CHPOINT de forces appliquees a
        la structure pour la contribution primaire du
        chargement B.

      TAB2.'CA' : objet de type CHPOINT de forces appliquees a
        la structure pour le chargement A complet.

      TAB2.'CB' : objet de type CHPOINT de forces appliquees a
        la structure pour le chargement B complet.

      TAB2.'DPTH' : objet de type CHPOINT de trmperatures
        appliquees a la structure pour la
        contribution primaire du chargement thermique.

      TAB2.'DCTH' : objet de type CHPOINT de temperatures
        appliquees a la structure pour le chargement
        thermique complet.

      TAB2.'TPSM' : objet de type FLOTTANT. Temps de maintien du
        chargement (B) en fluage.
        Il est entre en heure.

    Remarque : Selon l'Annexe A16 version2, le chargement de fatigue est
    defini par DP = PB - PA (DC = CB - CA). S'il existe un transitoire
    thermique T entre les etats permanents A et B alors
    DP = PB - PA + PT (DC = CB - CA + CT) (PT et CT sont les champs
    de forces associes respectivement aux champs DPTH et DCTH).

   AUTRES ARGUMENTS OBLIGATOIRES :
   ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨

      TAB1.'MFIS' : objet de type MAILLAGE constitue par les
        elements LISP.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## @LISSE [Mathematiques Fonctions] (proc)
    Procedure @LISSE
    ----------------- @tole2 @tole3

    EVOL2 = @LISSE EVOL1 FLOT1 FLOT2 ENT1 ENT2 ;

    Objet :

La procedure @LISSE effectue le lissage d'une evolution par deformation
elastique d'une poutre. La poutre passe par les points de l'evolution
EVOL1 donnee en entree.

    Commentaire :

    FLOT1 : reel donnant la rotation ( en degre) imposee a l'origine
        de la poutre.
        -45. < FLOT1 < 45. . SI FLOT1 > 45. il est ignore et la
        rotation est libre.

    FLOT2 : reel donnant la rotation ( en degre) imposee a
        l'extremite de la poutre.
        -45. < FLOT2 < 45. . SI FLOT2 > 45. il est ignore et la
        rotation est libre.

    ENT1 : entier donnant le nombre de points sur la courbe EVOL2.

    ENT2 : entier donnant la direction de la poutre : 1 si la
        poutre est suivant les abscisses et 2 si elle est situee
        sur les ordonnees.

    Exemple d'utilisation :

   ev = evol manu ' absci' ( prog 0.04 0.4 0.53 0.67 0.77 0.77)
        'ordo' ( prog -0.2 -0.13 -0.08 0. 0.23 0.41);
   evo1L = @lisse ev 50 0. 40 2;
$$$$

## @MATETHM [Multi-physique Multi-physique] (proc)
Procedure @MATETHM

MAT1 SEC1 = @MATETHM MOD1 CHPO1 ;

Objet :

   La procedure @MATETHM construit le champ de caracteristiques MAT1
associe au modele MOD1 dans le cas d'une formulation THERMOHYDRIQUE,
materiau SCHREFLER, ainsi que le second membre du systeme d'equations
couplees associe a ce modele. La procedure @MATETHM se substitue a
l'operateur MATE dans le cas d'une formulation THERMOHYDRIQUE.

   Elle fait appel a la procedure @SATURAT qui donne la saturation
en eau liquide du milieu poreux. Plus generalement, cette procedure
contient les caracteristiques materielles des differentes phases
constituant le milieu : solide poreux (beton), eau liquide et vapeur,
air sec. A priori, seule les caracteristiques de la phase solide sont
susceptibles d'etre modifiees.

Commentaire :

MOD1 = MMODEL, modele THERMOHYDRIQUE SCHREFLER ;

CHPO1 = CHPOINT d'inconnues primales (PG,PC,T) ;

MAT1 = MCHAML de caracteriques associes a MOD1 ;

SEC1 = CHPOINT a ajouter au second membre lors de la resolution
        (pre-cable dans PASAPAS) ;

Remarque :

   Le modele THERMOHYDRIQUE SCHREFLER permet de decrire le comporte-
-ment thermohydrique d'un milieu poreux deformable insature en eau
selon l'approche developpee par B.A. Schrefler et R.W.Lewis [1].

References :

[1] - R.W.Lewis et B.A. Schrefler - The Finite Element Method in the
Static and Dynamic Deformation and Consolidation of Porous Media,
Wiley (ed.), 1998 (2nd edition).

## @MESU [Maillage Generaux] (proc)
     CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
    A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

Procedure @MESU

VAL1 = @MESU GEO1 ;

Objet :

Cette procedure calcule la mesure d'un maillage :

    - longueur d'une ligne
    - aire d'une surface
    - volume d'un massif

Commentaire:

GEO1 : maillage que l'on veut mesurer

VAL1 : mesure du maillage (type FLOTTANT)

## @MISTPAR [Mecanique Modele] (proc)
CETTE PROCEDURE A ETE MISE GRACIEUSEMENT A DISPOSITION DES UTILISATEURS
DU MODELE MISTRAL :
- PAR C. STRUB (CEA/DMT/SEMI/LEMO) pour la version 1.1 (CAST3M 2001 a 2003)
- puis par R. LIMON (CEA/DMN/SEMI/LCMI) et F. BENTEJAC (CEA/DM2S/SEMT/LM2S)
  pour la version 2.0 (CAST3M 2004 a ...)

   Procedure @MISTPAR

   PDILT E1 E2 E3 NU12 NU23 NU13 MU12 MU23 MU13
   PNBRE PCOHI PECOU PEDIR PRVCE PECRX PDVDI PCROI PINCR
     = @mistpar NOMFIC SENSIP1 SENSIP2 ;

Objet :

    Cette procedure peut etre utilisee avant l'appel a l'operateur 'MATE',
    dans le cas de l'utilisation du modele MISTRAL (cf. operateur MODL), pour:
    lire les donnees sur un fichier.

En entree :

NOMFIC nom du fichier contenant les parametres materiau pour le
        modele MISTRAL (type MOT).

SENSIP1 numero d'ordre de la 1ere direction de la base d'orthotropie
        de MISTRAL dans la base d'orthotropie de CAST3M, affecte du
        signe - s'il y a changement de sens (type ENTIER).

SENSIP2 numero d'ordre de la 2eme direction de la base d'orthotropie
        de MISTRAL dans la base d'orthotropie de CAST3M, affecte du
        signe - s'il y a changement de sens (type ENTIER).

En sortie :

PDILT liste de reels contenant les parametres des fonctions
        traduisant l'evolution des coefficients de dilatation
        thermique en fonction de la temperature (type LISTREELS).

E1 E2 E3 NU12 NU23 NU13 MU12 MU23 MU13 :
        coefficients d'elasticite en fonction de la temperature absolue
        (en K) dans la base d'orthotropie de CAST3M (type EVOLUTION)

PNBRE liste de 4 entiers en format reel contenant (type LISTREELS):
        - les nombres de (tenseurs de) :
        - deformations plastiques instantanees a seuil
        (0 ou 1),
        - deformations viscoplastiques (0 a 3),
        - contraintes internes (0 a 3),
        - un nombre indiquant l'existence (>0) ou non (0) de
        variable(s) de durcissement d'irradiation
        differente(s) de la fluence de neutrons rapides.

PCOHI liste de reels contenant les parametres des fonctions
        traduisant l'evolution des coefficients d'anisotropie
        plastique (de Hill) en fonction de la temperature et de
        la fluence de neutrons rapides * (type LISTREELS).

PECOU liste de reels contenant les parametres relatifs a la loi
        d'ecoulement ** (type LISTREELS).

PEDIR liste de reels contenant les parametres relatifs aux
        contraintes seuil * (type LISTREELS).

PRVCE liste de reels contenant les parametres de la loi
        de restauration, vieillissement et couplage au niveau
        des deformations plastiques equivalentes * (type LISTREELS).

PECRX liste de reels contenant les parametres relatifs aux
        contraintes internes *** (type LISTREELS).

PDVDI liste de reels contenant les parametres relatifs a la variable
        de durcissement d'irradiation * (type LISTREELS).

        * : pour toutes les deformations plastiques
        ** : pour toutes les deformations viscoplastiques
        *** : pour toutes les contraintes internes

PCROI liste de reels contenant les parametres de la loi de croissance
        sous irradiation (type LISTREELS).

PINCR liste de reels contenant les increments maximaux autorises pour
        la determination automatique du pas de temps lors de l'integration
        des equations d'evolution des variables materiau par MISTRAL
        (type LISTREELS).

## @MOD [Mathematiques Fonctions] (proc)
Procedure @MOD

OBJ3 = @MOD OBJ1 OBJ2 ;

Objet :

Cet operateur calcule OBJ1 modulo OBJ2.

Commentaire :

types possibles pour OBJ1 et OBJ2 :
      ENTIER, FLOTTANT, LISTENTI, ou LISTREEL

OBJ3 : liste si l'un des deux arguments est une liste
        (LISTENTI ou LISTREEL)
       scalaire sinon (ENTIER ou FLOTTANT)

       reel si l'un des deux arguments contient des reels
        (FLOTTANT ou LISTREEL)
       entier sinon (ENTIER ou LISTENTI)

Remarque :

OBJ2 doit etre strictement positif.

## @MODTRI [Post-traitement Analyse] (proc)
     Procedure @MODTRI

TAB3 = @MODTRI TAB1 TAB2;

    Objet :

  La procedure @MODTRI permet de calculer la reponse statique
(force - deplacement) d un poteau en beton arme assimile a
une structure a 1 DDL. La procedure @MODTRI construit une table
resultat TAB3 a partir d une table de donnees TAB1 et d une
table caracterisant l etat initial des variables internes TAB2:

TAB1 : TABLE table de donnees
        TAB1 . 1 Pente 1 (elastique)
        TAB1 . 2 Pente 2 (endommagee)
        TAB1 . 3 Pente 3 (plastique)
        TAB1 . 4 Seuil d endommagement
        TAB1 . 5 Seuil de plastification

TAB2 : TABLE table de variables internes initiales
        TAB2 . 1 Endommagement lie aux deplacements positifs
        TAB2 . 2 Endommagement lie aux deplacements negatifs
        TAB2 . 3 Deplacement courant
        TAB2 . 4 Deplacement positif maximum sur l historique en temps
        TAB2 . 5 Deplacement negatif maximum sur l historique en temps

TAB3 : TABLE table de variables internes finales
        TAB3 . 1 Force
        TAB3 . 2 Endommagement lie aux deplacements positifs
        TAB3 . 3 Endommagement lie aux deplacements negatifs
        TAB3 . 4 Deplacement positif maximum sur l historique en temps
        TAB3 . 5 Deplacement negatif maximum sur l historique en temps
        TAB3 . 6 Endommagement courant

## @M_VORO [—] (proc)
Procedure @M_VORO

TAB2 = @M_VORO TAB1 DENS1 (FLOT1) (ITRA1) ;

Objet :

Procedure de maillage d'un agregat cubique de polyedres de Voronoi.

Commentaire :

TAB1 = TABLE, resultat de la procedure @P_BOIT ;

DENS1 = FLOTTANT, densite du maillage ;

FLOT1 = FLOTTANT, critere pour l'elimination de faces de petite
        taille (0,3xDENS1 par defaut) ;

ITRA1 = LOGIQUE, active des traces (pour DeBogage) ;

TAB2 = TABLE, dont l'indice 'MAIL' contient le maillage de
        l'agregat, l'indice 'ARET' celui des aretes de chaque
        polyedre (pour traces).
        De plus, chaque point de la partition de Voronoi sert
        d'indice pour le maillage du polyedre qui lui est associe
        (TAB2 . PT1 . 'MAIL', TAB2 . PT1 . 'ARET').

## @ORTHO [Mecanique Modele] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )
        PROCEDURE MISE A JOUR PAR OF LE 09/03/2009

    Procedure @ORTHO

  MAT1 MODL1 = @ORTHO GEO1 LIG1 CH1 CH2 ALPH1 LIST1
        (TYPEMOD (TYPEELT)) (PTGENE) ;

    Objet :

  Cette procedure permet la creation du champ par elements des caracteristiques
mecaniques d'un materiau orthotrope ayant une geometrie quelconque.
Les directions d'orthotropie sont obtenues a partir du repere local d'une ligne
directrice.

    Commentaire :

  GEO1 : Geometrie du maillage (type MAILLAGE)

  LIG1 : Ligne directrice de la geometrie GEO1 (type MAILLAGE)

  CH1 : Champ par points du vecteur unitaire de la premiere direction
        liee a LIG1 (type CHPOINT)

  CH2 : Champ par points du vecteur unitaire de la deuxieme direction
        liee a LIG1 (type CHPOINT)

  ALPH1 : Angle entre CH1 et la premiere direction d'orthotropie
        (type FLOTTANT)

  LIST1 : Liste des caracteristiques mecaniques (constantes) du materiau
        (type LISTREEL)

  TYPEMOD : Mot-cle correspondant a la modelisation souhaitee (type MOT) :

        'COMI' modele 2D/3D COques MInces
        (elements finis de type COQ2, COQ3 ou DKT)
        'COEP' modele 3D COques EPaisses/cisaillement transverse
        (elements finis de type DST, COQ4, COQ6 ou COQ8)
        'TRID' modele massif 3D
        'AXIS' modele massif 2D axisymetrique
        'FOUR' modele massif 2D serie de Fourier
        'PLANCONT' modele massif 2D en contraintes planes
        'PLANDEFO' modele massif 2D en deformations planes
        'PLANGENE' modele massif 2D en deformations planes generalisees

        (Par defaut, la modelisation correspond au mode de calcul massif
        courant donne par 'VALEUR' 'MODE'.)

  TYPEELT : Mot-cle permettant de preciser (lorsque TYPEMOD vaut 'COMI')
        l'element fini de type coque mince ('COQ3' ou 'DKT') a
        associer aux elements TRI3 du maillage GEO1 (type MOT)
        (Par defaut, l'element COQ3 sera utilise.)

  PTGENE : Point support (obligatoire) dans le cas d'une modelisation 2D
        massive ou coques minces en deformations planes generalisees

  MAT1 : Champ par elements contenant les caracteristiques du materiau
        orthotrope (type MCHAML, sous-type CARACTERISTIQUES)

  MODL1 : Objet modele definissant le materiau orthotrope (type MMODEL)

    Remarque 1 :

  LIST1 doit imperativement comporter les 13 valeurs suivantes :

   E1 module d'Young suivant la premiere direction d'orthotropie
   E2 module d'Young suivant la deuxieme direction d'orthotropie
   E3 module d'Young suivant la troisieme direction d'orthotropie
   NU12 coefficient de Poisson
   NU23 coefficient de Poisson
   NU13 coefficient de Poisson
   GR12 module de Coulomb
   GR23 module de Coulomb
   GR13 module de Coulomb
   ALP1 coefficient de dilatation thermique suivant la premiere
        direction d'orthotropie
   ALP2 coefficient de dilatation thermique suivant la deuxieme
        direction d'orthotropie
   ALP3 coefficient de dilatation thermique suivant la troisieme
        direction d'orthotropie
   RHO masse volumique

   (Mettre des 0. aux valeurs inutiles pour la modelisation consideree.)

    Remarque 2 :

  Dans le cas d'un probleme comprenant des modelisations de type coques
minces, coques epaisses et massives, il faut faire appel a la procedure
@ORTHO pour chaque modelisation consideree. Le maillage GEO1 peut etre
forme de plusieurs types d'elements de meme type (massifs ou coques).

    Remarque 3 :

  Les champs par points CH1 et CH2 peuvent etre obtenus en appliquant
la procedure @FRENET a la ligne de maillage LIG1.

    Remarque 4 :

  La procedure @ORTHO remplace l'appel aux deux operateurs MODL et MATE.
La liste des caracteristiques d'orthotropie est donnee dans la notice de
l'operateur MATE pour chaque type de materiau.

## @OTCOQUE [Mecanique Modele] (proc)
   Procedure @OTCOQUE

  LREEL1 DEP1 = @OTCOQUE FLOT1 ENTI1 FLOT2 FLOT3 FLOT4
        TAB1 TAB2
        FORC1 RIG1 P1;

   Objet :

   Cette procedure qui s'utilise en mode interactif, permet
d'optimiser les couches d'une structure de type coque ou plaque
selon la methode du FULL-STRESS-DESIGN.

   Commentaires :

   LREEL1 : liste contenant les couches des zones
        (type LISTREEL)

   DEP1 : champ de deplacements de la structure optimisee
        (type CHPOINT)

   FLOT1 : critere de convergence pour le sigma equivalent
        (type FLOTTANT)

   ENTI1 : nombre maximum d'iterations (type ENTIER)

   FLOT2 : couche initiale de la structure, valeur identique pour
        toutes les zones (type FLOTTANT)

   FLOT3 : valeur maximale du sigma equivalent, calculee en
        fonction de l'operateur VMIS (type FLOTTANT)

   FLOT4 : epaisseur minimale acceptable (type FLOTTANT)

   TAB1 : table contenant pour la i-eme zone l'objet relatif
        MMODL (type TABLE),TAB1.I (type MMODL), I (type ENTIER)

   TAB2 : table contenant pour la i-eme zone l'objet relatif
        avec les caracteristiques du materiau (type TABLE),
        TAB2.I (type MCHAML), I (type ENTIER)

   FORC1 : champ de forces (type CHPOINT)

   RIG1 : rigidite associee aux liaisons et a la partie de la
        structure qui n'a pas subi d'optimisation (type
        RIGIDITE),

   P1 : point de vue pour les traces.

   Note :

   - La methode ne donnera un resultat optimal d'un point de
vue mathematique que pour les structures isostatiques.
   - Il faut diviser la structure en zones a l'interieur desquelles
l'epaisseur est supposee uniforme.
   - La convergence peut etre controllee par un parametre qui
est appele interactivement a chaque iteration; il a pour fonction
la reduction ou l'amplification de la variation des epaisseurs
evaluee a chaque iteration sur la base du rapport entre
le sigma equivalent maximum de la zone et le sigma equivalent
optimal.

## @OTPOUT [Mecanique Modele] (proc)
    Procedure @OTPOUT

    TAB1 DEP1 = @OTPOUT FLOT1 ENTI1 FLOT2 FLOT3 FLOT4 FLOT4 FLOT5
        TAB2 TAB3
        FORC1 RIG1 TAB4;

    Objet :

    Cette procedure,qui s'utilise en mode interactif, permet
 d'optimiser les hauteurs et les bases de modeles de poutres
 a section rectangulaire selon la methode du FULL-STRESS-DESIGN.

    Commentaires :

    TAB1 : objet de type TABLE; TAB1.I (type LISTREEL) pour la i-eme
        zone fournit une liste contenant les valeurs de base,
        hauteur et surface de la section, resultat de l'optimisation
        I (type ENTIER),

    DEP1 : champ de deplacement de la structure optimisee
        (type CHPOINT),

    FLOT1 : critere de convergence pour le sigma equivalent
        (type FLOTTANT),

    ENTI1 : nombre maximum d'iterations (type ENTIER),

    FLOT2 : base initiale des poutres de la structure, valeur
        identique pour toutes les zones (type FLOTTANT),

    FLOT3 : hauteur initiale des poutres de la structure, valeur
        identique pour toutes les zones (type FLOTTANT),

    FLOT4 : valeur optimale du sigma equivalent, calcule
        a partir des efforts flexionnels et membranaires
        normaux (type FLOTTANT),

    FLOT5 : plus petite dimension acceptable pour la poutre
        (type FLOTTANT),

    TAB2 : table contenant pour la i-eme zone l'objet relatif
        MMODL (type TABLE),TAB2.I (type MMODL), I (type ENTIER),

    TAB3 : table contenant pour la i-eme zone l'objet relatif
        avec les caracteristiques du materiau (type TABLE),
        TAB3.I (type MCHAML), I (type ENTIER),

    FORC1 : champ de forces (type CHPOINT),

    RIG1 : rigidite associee aux liaisons et a une partie
        de la structure n'ayant pas subi d'optimisation
        (type RIGIDITE),

    TAB4 : table contenant pour la i-eme zone le vecteur relatif
        pour l'orientation des axes locaux (type TABLE),
        TAB4.I (type POINT), I (type ENTIER),

    Note :

    - La methode ne donnera un resultat optimal, d'un point de vue
 mathematique, que pour les structures isostatiques.
    - If faut diviser la structure en zones a l'interieur desquelles les
dimensions des poutres sont supposees uniformes.
    - La convergence peut etre controllee par un parametre qui
 est appele interactivement a chaque iteration; il a pour fonction
 la reduction ou l'amplification de la variation des epaisseurs
 evaluee a chaque iteration sur la base du rapport entre
 le sigma equivalent maximum de la zone et le sigma equivalent
 optimal.

## @PALETTE [Post-traitement] (proc)
Procedure @PALETTE

LMOT1 = @PALETTE NCOUL1;

Objet :
Cette procedure construit une palette de noms de couleurs Cast3M
pour leur application a des evolutions par exemple.

Entrees :
NCOUL1 : nombre de couleurs (type ENTIER) compris entre 1 et 20

Sorties :
LMOT1 : LISTMOTS compose de NCOUL couleurs differentes.

Exemple :
evol1 = COUL evol1 (@PALETTE (DIME evol1));
DESS evol1;

## @PASHIST [Post-traitement Analyse] (proc)
    Procedure @PASHIST voir aussi : HIST

    LRE1  = @PASHIST MOD1 CHAM1 | (MOT1)  | ;
        | (LMOT1) |

    Objet :

    La procedure @PASHIST determine une plage d'echantillonnage des
valeurs du champ CHAM1 (objet LISTREEL) a passer en argument de
l'operateur HIST.

    Commentaire :

    MOD1 : modele (de type MMODEL) ;

    CHAM1 : champ par elements (de type MCHAML) ;

    MOT1 : nom de la composante de CHAM1 a traiter (de type MOT) ;

    LMOT1 : nom de(s) la composante(s) de CHAM1 a traiter (de type
        LISTMOTS).

## @PLOTPRI [Post-traitement Affichage] (proc)
   Procedure @PLOTPRI

   @PLOTPRI SIG1 MODE1 ;

   Objet :

   Cette procedure qui s'utilise en mode interactif permet de
tracer un champ vectoriel de contraintes principales, ainsi
que le champ de contraintes equivalentes de Von Mises qui lui
correspond.

   Commentaire :

   SIG1 : champ de contraintes (type MCHAML)

   MODE1 : objet modele relatif au champ (type MMODEL)

   Note :

   Les fleches rouges correspondent a une contrainte principale
de traction tandis que les vertes correspondent a une contrainte
de compression.
Cette procedure ne peut s'utiliser qu'en 2D.

## @POINTIR [—] (proc)
  Procedure @POINTIR

PTS1 = @POINTIR | 'UNIF' N1  | (MAIL1) ...
        | 'EXCL' N1 | 'SPHE' RS1  | (N2) |
        'COUR' RC1 RC2 |

   ... ('PINI' PTS2) ('GERM' | 'AUTO' | ) ;
        | IGER1  |

  Objet :

    La procedure @POINTIR realise un maillage de points (POI1)
  repartis aleatoirement selon une distribution uniforme (option UNIF)
  ou selon un processus d'exclusion (option EXCL) dans le domaine
  defini par le maillage MAIL1 ou, par defaut, dans le domaine unite.
  En 2D, le domaine unite est un carre de cote 1 centre sur le point
  de coordonnees (0,5;0,5) ; en 3D, il s'agit d'un cube de cote 1
  centre sur le point de coordonnees (0,5;0,5;0,5).

  Commentaire :

  'UNIF' = Mot cle pour une distribution uniforme de points.

  'EXCL' = Mot cle pour une distribution generee selon un processus
        "d'exclusion" : chaque point de la distribution doit
        appartenir a un domaine donne.

  N1 = Objet de type ENTIER : nombre de points a generer.
        Dans le cas de l'option EXCL, en fonction des parametres
        du domaine d'exclusion, il est possible que le processus
        n'arrive pas a generer le nombre de points demande.

  'SPHE' = Mot cle indiquant que la zone d'exclusion autour des
        points est une sphere (cercle en 2D) centree sur ces
        points.

  R1S = Objet de type FLOTTANT : rayon de la SPHEre d'exclusion.

  'COUR' = Mot cle indiquant que la zone d'exclusion autour des
        points correspond a l'"exterieur" d'une couronne
        centree sur ces points.

  R1C = Objet de type FLOTTANT : rayon interne de la COURonne
  R2C = Objet de type FLOTTANT : rayon externe de la COURonne

  N2 = Objet de type ENTIER : nombre d'iterations du processus
        d'exclusion pour placer les N1 points demandes.
        Par defaut, N2 est egal a 25*N1.

  MAIL1 = Objet de type MAILLAGE (surface en 2D, volume en 3D) :
        definit le domaine dans lequel sont tires les points.

  'PINI' = Mot cle indiquant la donnee de points initiaux.

  PTS2 = Objet MAILLAGE de type POI1 : points initiaux, utiles
        uniquement dans le cas de l'option 'EXCL'.
        N.B. : Ces points ne sont pas inclus dans PTS1 en
        sortie de la procedure.

  'GERM' = Mot cle indiquant la donnee d'un nouveau germe.

  'AUTO' = Modification automatique du germe par congruence : le
        germe, stocke dans le fichier /tmp/germe, est modifie
        a chaque appel de @POINTIR avec l'option 'AUTO'.

  IGERM1 = Indice d'initialisation du generateur de nombres
        aleatoires.

  PTS1 = Objet de type MAILLAGE : maillage de POI1.

## @POLO [Magnetostatique Magnetostatique] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
       A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

   Procedure @POLO

   TABCHB TAB2 = @POLO TAGEO1 TABOB1 ( PL1 ) ;

Objet :

Calcul d'un champ magnetique poloidal genere par un ensemble
de bobines.

En entree :

TAGEO1 table contenant (type TABLE)
   i objet geometrique ou l'on veut calculer le
        champ magnetique (type MAILLAGE)

TABOB1 table a deux indices contenant les donnees
        relatives aux bobines (type TABLE)
        - 1er indice :
   i numero de la bobine (type ENTIER)
        - 2eme indice (pour chaque bobine) :
   COUL couleur de la bobine (voir palette dans COUL)
   RI rayon interne (type FLOTTANT)
   RE rayon externe (type FLOTTANT)
   H hauteur de la section (type FLOTTANT)
   C centre de la section (type POINT)
   V vecteur normal a la section (type POINT)
   SOL solenation : courant global dans la bobine =
        courant * nombre de spires (type FLOTTANT)
        + options facultatives (en 1er indice) :
   TRAC1 si existe : trace du maillage des bobines
   TRAC2 si existe : trace du contour des bobines dans
        les plans de coupe

PL1 table a deux indices contenant la definition
        des plans de coupe (facultative / type TABLE)
        - 1er indice :
   i numero du plan (type ENTIER)
        - 2eme indice (deux possibilites) :
        1/ pour definir chaque plan :
   PP point quelconque du plan (type POINT)
   VP vecteur normal (type POINT)
        2/ pour reprendre un contour deja calcule :
   MAIL contour des bobines dans un plan de coupe
        (type MAILLAGE)

En sortie :

TABCHB table contenant (type TABLE)
   i champ de Biot et Savart relatif au i-eme
        maillage GEO1 (type CHPOINT)

TAB2 table contenant (type TABLE)
BOBMAI.i maillage de chaque bobine i (type MAILLAGE)
LIG.j ensemble des coupes sur le plan j
        (type MAILLAGE)
CHBLIG.j champ magnetique relatif au maillage LIG.j
        (type CHPOINT)

Remarques :

Les grandeurs suivantes sont "en dur" dans la procedure :

NELE nombre elements generes lors des rotations
        effectuees pendant la creation du maillage des
        bobines
COEF1 coefficient etablissant la distance critique
        de selection des points lors de la recherche
        de contour

## @POMI [Mathematiques Fonctions] (proc)
      CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
     A DISPOSITION DE LA COMMUNAUTE CASTEM2000
PAR DELERUYELLE F. (SOCOTEC-INDUSTRIE a l'IPSN/DES)

    Procedure @POMI

    TCN PN = @POMI F1 N (PAS1) (IDEM) ;

    Objet :

    Cette procedure determine le polynome Pn(x) de degre n le plus
    'proche' d'une fonction f(x) donnee. Il s'agit en fait du polynome
    de degre n minimisant :
        2 /b 2
        D(f,Pn) = / [f(x) - Pn(x)] . dx
        /a

    On peut s'en servir pour faire du lissage, ou pour approcher une
    fonction 'experimentale' (donnee point par point) par une expres-
    sion analytique.

    Commentaires :

    F1 : fonction f(x) qu'on cherche a approcher par un polynome.
        (type EVOLUTION).

    N : degre du polynome Pn(x) recherche (type ENTIER).
        Il doit etre superieur ou egale a 1 .

    PAS1 : pas du decoupage sur l'axe des abscisses de l'evolution
        visualisant le polynome recherche Pn(x).
        Facultatif, la valeur par defaut est detaillee en remarque.
        (type FLOTTANT).

    IDEM : mot cle facultatif indiquant qu'on veut sur l'evolution
        visualisant le polynome recherche Pn(x) les meme abscisses
        que sur l'evolution visualisant la fonction f(x).
        (type MOT).

    TCN : table indexee par des entiers donnant les coeficients du
        polynome Pn(x) recherche (type TABLE).
        2 n
        Si: Pn(x) = a0 + a1.x + a2.x + ... + an.x
        Alors: a0 = TCN.0
        a1 = TCN.1

    PN : evolution visualisant le polynome Pn(x) recherche.
        (type EVOLUTION).

    Exemple :

    xx = prog 50. 100. 200. 300. 400. 500. ;
    yy = prog 2.37 2.06 1.74 161 1.42 1.2 ;
    f0 = evol blan manu 'XX' xx 'YY' yy;
    ta f1 = @POMI f0 5 ;
    list ta;
    dess (f0 et f1);

    Remarques :

    1) La procedure a besoin d'etre en dimension 2 ou 3 pour resoudre.
       Si ca n'est pas le cas, elle passe automatiquement en dimension
       2 et y reste en vue d'utilisations ulterieures.

    2) Le polynome Pn(x) obtenu ne passe que rarement aux memes points
       que la fonction f(x). Mais il est le plus proche de la fonction
       f(x) au sens de la 'distance' D(f,Pn) definie plus haut.
       Pn(x) n'est pas un polynome de degre n passant par des points
       donnes, car ce genre de polynome oscille generalement beaucoup.

    3) La fonction f(x) n'est connue que par son evolution F1 .
       Le calcul est base sur une formule analytique qui suppose que la
       fonction f(x) varie lineairement entre ces points connus.

    4) Le pas PAS1, s'il n'est pas fournis, est calcule comme suit :
       On considere A et B les extremites du domaine de definition de
       f(x), NBP le nombre de points de f(x), et :
        PAS1 = ((B-A)/(NBP-1)) / 4.
       Ce pas ne sert qu'a fournir l'evolution PN . Il n'influe pas
       sur le calcul des coefficients du polynome.

    5) Le polynome Pn(x) va necessairement avoir une limite infini au
       voisinage de l'infini. Il serait dangereux de s'en servir pour
       extrapoler une fonction connue point par point.

## @P_BOIT2 [—] (proc)
Procedure @P_BOIT2

TAB2 = @P_BOIT2 TAB1 (IVISU1) ;

Objet :

   Procedure determinant l'intersection d'un maillage de polyedres
de Voronoi construit par la procedure @P_VORO avec le cube de cote 1
et dont les 3 plans de base sont X=Y=Z=0. @P_BOIT2 utilise la pro-
-cedure @COUPLAN, contrairement a @P_BOIT.

Commentaire :

TAB1 = TABLE, resultat de la procedure @P_VORO ;

IVISU1 = LOGIQUE, active des traces (pour DeBogage) ;

TAB2 = TABLE, dont l'indice 'MAV' contient le maillage des
        aretes des polyedres.
        De plus, chaque point de la partition de Voronoi sert
        d'indice pour le maillage des aretes du polyedre associe
        (TAB2 . PT1 . 'MAV').

Remarque : Fait appel aux procedures @COUPLAN.

## @P_VORO [—] (proc)
Procedure @P_VORO

TAB1 = @P_VORO MPOI1 (FLOT1) (ILOG1) ;

Objet :

   Construit la partition de Voronoi d'un ensemble de points
(maillage de POI1). S'appuie sur une triangulation de cet ensemble
de points dans une boite de dimension finie, ce qui permet de
construire les polyedres associes aux points situes sur leur
enveloppe convexe.

Commentaire :

MPOI1 = MAILLAGE, nuage de points (POI1) ;

FLOT1 = FLOTTANT, rapport de la taille de la boite de triangu-
        -lation sur la dimension du nuage de points ;

ILOG1 = LOGIQUE, mettre a VRAI pour activer TRAC ;

TAB1 = TABLE, dont chaque indice est un point de MPOI1, dont
        le sous-indice 'MAV' contient le Maillage des Aretes du
        polyedre de Voronoi associe a ce point et le sous-indice
        'MPT' celui des Points de la Triangulation adjacents a
        chaque face de ce polyedre.
        De plus, l'indice 'MAV' de la table contient le Maillage
        des Aretes de tous les polyedres et l'indice 'MPT' le
        maillage MPOI1.

## @RAYO [Maillage Autres] (proc)
    Procedure @RAYO

    ST SINT L1EXT L2EXT L3EXT L4EXT LEVD LEVG = @RAYO PF P1 NBC;

    Objet :

Cette procedure cree un maillage rayonnant symetrique autour de la
pointe de fissure. La zone centrale entourant la pointe de fissure
est maillee en TRI6, les NBC-1 autres zones etant maillees en QUA8.
Afin de pouvoir distinguer les parties infirieures et supirieure de la
zone (en cas de fissure dans une interface par exemple), la couleur
rouge est affectie a la partie gauche du maillage et la couleur jaune a
la partie droite (la gauche et la droite etant definies par rapport a
un observateur place en pointe et regardant la fissure).

    Sorties :

    ST : MAILLAGE de la zone rayonnante

    SINT : MAILLAGE de la zone centrale (maillee en TRI6)

    L1EXT : MAILLAGEs des frontieres exterieures de ST (un par
    L2EXT quart de cercle depuis la levre gauche vers la levre
    L3EXT droite de la fissure.
    L4EXT

    LEVD : MAILLAGE de la levre droite de la fissure

    LEVD : MAILLAGE de la levre gauche de la fissure

    Commentaire :

    PF : pointe de la fissure (type POINT)

    P1 : point correspondant a l'extremite de la zone rayonnante
        sur la levre de la fissure (type POINT)

    NBC : nombre de couronnes demande (type ENTIER)

## @RCCM [Post-traitement Analyse] (proc)
Procedure @RCCM

@RCCM TABCOUP TABETAT TABGROU TABFATI ;

Objet :

Le RCC-M definit un ensemble de regles techniques de conception
et de construction des materiels mecaniques d'un ilot nucleaire.

Ces regles visent a assurer aux materiels auxquels elles
s'appliquent des securites vis a vis de differents types de
dommages :
- deformation excessive,
- instabilite,
- deformation progressive,
- fatigue,
- rupture brutale.

Le dossier d'analyse du comportement pour tout appareil construit
justifie que certains criteres (du volume B 3200 du rccm,
princpalement, dits de niveaux 0, A, C et D, correspondant a
differentes situations de fonctionnement, ainsi que les criteres
applicables a l'epreuve hydraulique) soient respectes pour des
chargements precises dans une specification d'equipement.
Ces criteres conduisent a l'analyse des contraintes sur des
segments d'appui (appeles coupes), normaux a la surface mediane
d'une paroi ou conduisant au chemin le plus court entre les 2 faces
de la paroi dans les zones de discontinuite.

Les contraintes analysees sont principalement les :

- contrainte totale : c'est la valeur atteinte en un point de
        la paroi par une contrainte, sous
        l'effet de l'ensemble des actions
        auxquelles est soumis l'appareil.

- contrainte de membrane : pour un tenseur de contraintes, de
        composantes sij, le tenseur de
        contrainte de membrane est le tenseur sm
        dont les composantes (sij)m sont egales
        a la valeur moyenne des contraintes sij
        le long du segment d'appui.

- contrainte de flexion
  linearisee : c'est la difference, en tout point du
        segment d'appui, du tenseur s linearise
        (sl) et du tenseur sm :
        (sij)f = (sij)l - (sij)m .

Ces contraintes sont ensuite differenciees, suivant les
redistributions par plasticite qu'elles peuvent entrainer, en
contraintes :
- primaire : fraction de la contrainte totale qui ne peut
        disparaitre du fait d'une faible deformation
        permanente. Ces contraintes sont essentiellement les
        contraintes de membrane et parfois les contraintes
        de flexion.
- secondaire : fraction de la contrainte totale qui peut
        disparaitre en consequence d'une faible deformation
        permanente, deduction faite des contraintes de
        pointe. Ces contraintes sont essentiellement les
        contraintes thermiques et les contraintes de flexion
        au voisinage d'une discontinuite majeure.
- de pointe : le tenseur des contraintes de pointe en un point est
        la difference entre le tenseur des contraintes
        totales et le tenseur correspondant a la
        distribution linearisee de meme moment et meme
        valeur moyenne.

Dans le cadre de l'analyse elastique, il est fait appel au critere
de plasticite de Tresca , la contrainte significative a prendre en
compte etant egale a la difference entre la plus grande et la plus
petite des trois contraintes principales prises algebriquement, les
contraintes de tension etant considerees comme positives et les
contraintes dec compression comme negatives. Elle est appelee
"contrainte equivalente de Tresca".

Les criteres de contrainte a respecter sont principalement les :

- critere de niveau 0 en situation de premiere categorie, dite de
  reference (situation dans laquelle se trouverait le materiel s'il
  etait soumis a des actions constantes dans le temps definies a
  partir des actions les plus severes auxquelles est soumis
  l'appareil lorsqu'il se trouve dans la situation de 2eme
  categorie), visant a premunir le materiel contre les dommages de
  deformation excessive, d'instabilites plastique, elastique et
  elastoplastique :
  . la contrainte equivalente primaire de membrane generale est
    limitee a Sm,
  . la contrainte equivalente primaire de membrane locale est
    limitee a 1,5 Sm,
  . la contrainte equivalente primaire de membrane + flexion est
    limitee a 1,5 Sm,
  (Sm : contrainte equivalente admissible donnee dans le RCCM-M
  pour les differents materiaux. Ici elle prise a la temperature de
  calcul).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## @RCCMCO2 [Post-traitement Analyse] (proc)
Procedure @RCCMCO2

Objet :

Cette procedure est appelee en interne par la procedure RCCM

## @RCCMTRV [Post-traitement Analyse] (proc)
Procedure @RCCMTRV

Objet :

Cette procedure est appelee en interne par la procedure RCCM

## @RELIEF [Post-traitement Affichage] (proc)
Directive @RELIEF Voir aussi MONTAGNE

     @RELIEF ;

Objet :

Cette procedure interactive sert a visualiser en relief une
composante d'un champ par point ou un champ par element et
de superposer les isovaleurs d'une deuxieme composante ou
d'une composante d'un deuxieme champ par point ou champ par
element.

Remarque :

On ne peut pas fournir de modele bases sur des QUAF

## @REMPCOU [Post-traitement Analyse] (proc)
    Procedure @REMPCOU

    Objet :

    Cette procedure prepare les tables decrivant les coupes
pour le post-traitement par la procedure RCCM. Voir notice de RCCM

## @REMPFAT [Post-traitement Analyse] (proc)
    Procedure @REMPFAT

    Objet :

    Cette procedure prepare les tables de fatigue
pour le post-traitement par la procedure RCCM. Voir notice de RCCM

## @REMPGRO [Post-traitement Analyse] (proc)
    Procedure @REMPGRO

    Objet :

    Cette procedure prepare les tables de groupe de charge
pour le post-traitement par la procedure RCCM. Voir notice de RCCM

## @REPERE [Maillage Autres] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CASTEM2000
      PAR M. CHAMPANEY Laurent (L.M.T. STRUCTURES et CMAO)

   Procedure @REPERE

   RP1 = @REPERE ORI1 TAIL0 NOM1 COUL1 ;

   Objet :

Procedure pour la construction d'un repere X;Y(;Z) a TRACer

En entree :

        ORI1 POINT origine du repere
        => (0. 0. (0.)) par defaut

        TAIL0 LISTREEL tailles en X,Y(,Z) du repere
        => (PROG 1. 1. (1.)) par defaut

        Remarque : - si un 2eme doublet/triplet de
        valeurs est fourni dans TAIL0,
        il specifiera les dimensions de
        la tete des fleches
        - si un 3eme doublet/triplet de
        valeurs est fourni dans TAIL0,
        il specifiera les dimensions des
        lettres nommant les 2/3 axes

        NOM1 LOGIQUE VRAI pour nommer les axes
        => VRAI par defaut

        COUL1 MOT couleur du repere
        => DEFA par defaut

En sortie :

        RP1 MAILLAGE du repere

## @RRSR [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RRSR
    ------------- @RSCS @RSCV

    RS%'RSR' FLO1 ENT1 DBG1 ;

    Objet :

    La methode @RRSR forme partie du objet @RSTH et est appelee avec
    l'abbreviation %'RSR'.

    Commentaire :

    La methode @RRSR affiche la resultat du calcul pour les paramètres
    du random set avec le nombre serielle ENT1

    FLO1 : valeur du resultat pour le nombre serielle ENT1 de la
        variation des paramètres du Random Set

    ENT1 : nombre serielle ENT1 de la variation des paramètres
        du Random Set

    DBG1 : Argument optionel de type ENTIER indiquant le niveau du
        deboggage (DBG1 manquant ouDBG1=0, pas de deboggage)

    Exemple :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @RRST [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RRST
    ------------- @RRSR @RSCS @RSCV

    LRE2 = RS%'RST' TAB1;

    Objet :

    La methode @RRST forme partie du objet @RSTH et est appelee avec
    l'abbreviation %'RST'.

    Commentaire :

    La methode @RRST initialise un objet @RSTH avec les donnees
    dans la TABLE TAB1.

    Exemples :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @RRSV [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RRSV
    ------------- @RRSR @RSCS @RSCV

    RS%'RSV' ENT1 DBG1 ;

    Objet :

    La methode @RRSV forme partie du objet @RSTH et est appelee avec
    l'abbreviation %'RSV'.

    Commentaire :

    La methode @RRSV extrait le valeur des paramètres du random set
    avec le nombre serielle ENT1 et introduit les valeurs dans la
    table %'RT' pour chaque paramètre avec un index .'RSV'

    ENT1 : nombre serielle ENT1 de la variation des paramètres
        du Random Set

    DBG1 : Argument optionel de type ENTIER indiquant le niveau du
        deboggage (DBG1 manquant ouDBG1=0, pas de deboggage)

    Exemple :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @RSCS [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RSCS
    ------------- @RRSR @RSCV

    LRE2 = RS%'SCS' LRE1 DBG1;

    Objet :

    La methode @RSCS forme partie du objet @RSTH et est appelee avec
    l'abbreviation %'SCS'.

    Commentaire :

    La methode @RSCS converte les donnees dans le liste LRE1 pour
    les valeurs des probabilites cumules de un Random Set en un
    format compatible avec une evolution.

    LRE2 : liste des valeurs pour les probabilites cumules en format
        compatible avec une evolution

    LRE1 : liste des valeurs pour les probabilites cumules

    DBG1 : Argument optionel de type ENTIER indiquant le niveau du
        deboggage (DBG1 manquant ouDBG1=0, pas de deboggage)

    Exemple :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @RSCV [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RSCV
    ------------- @RRSR @RSCS

    LRE2 = RS%'SCV' LRE1 DBG1;

    Objet :

    La methode @RSCV forme partie du objet @RSTH et est appelee avec
    l'abbreviation %'SCV'.

    Commentaire :

    La methode @RSCV converti les donnees dans le LISTREEL LRE1 pour
    les valeurs des elements focales d'un Random Set en un format
    compatible avec une evolution.

    LRE2 : liste des valeurs pour les elements focales en format
        compatible avec une evolution

    LRE1 : liste des valeurs pour les elements focales

    DBG1 : Argument optionel de type ENTIER indiquant le niveau du
        deboggage (DBG1 manquant ouDBG1=0, pas de deboggage)

    Exemple :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @RSTH [Mathematiques Autres] (proc)
* CETTE METHODE A ETE MISE GRACIEUSEMENT
* A DISPOSITION DE LA COMMUNAUTE CAST3M
* PAR TAMASKOVICS N.
* (Freiberg Institut für Geotechnik )

    Methode @RSTH
    ------------- @RRSR @RSCS @RSCV

    OBJ1 = OBJET @RSTH ;

    OBJ1%'RST' TAB1 ;
    OBJ1%'RSV' ENT1 DBG1 ;
    OBJ1%'RSR' FLO1 ENT1 DBG1 ;
    OBJ1%'SCV' LRE1 DBG1 ;
    OBJ1%'SCS' LRE1 DBG1 ;

    Objet :

    La methode @RSTH cree un objet OBJ1 pour calculer avec la theorie
    des Random Sets (constructeur d'objet).

    Commentaire :

    OBJ1 : Objet random set (type OBJET)

    L'objet OBJ1 a les methodes publiques suivantes:

    OBJ1%'RST' : Appelle la methode @RRST pour initialiser le "random set"
    OBJ1%'RSV' : Appelle la methode @RRSV pour extraire la valeur
        courante du "random set"
    OBJ1%'RSR' : Appelle la methode @RRSR pour afficher un resultat
        courant du "random set"
    OBJ1%'SCV' : Appelle la methode @RSCV pour extraire les valeurs
        du LISTREEL pour le "random set" (Intervalles des parametres)
    OBJ1%'SCS' : Appelle la methode @RSCS pour extraire les valeurs
        du LISTREEL pour le "random set" (Probabilite cumulee)

    L'objet a les variables publiques suivantes:

    %'RT' : TABLE TAB1 contennant les distributions des parametres
    %'NX' : Variable auxiliaire pour l'enumeration des valeurs courantes
    %'CX' : Variable auxiliaire pour l'enumeration des valeurs courantes
    %'RX' : Variable auxiliaire pour l'enumeration des valeurs courantes
    %'PX' : Variable auxiliaire pour l'enumeration des valeurs courantes
    %'IR' : Variable auxiliaire pour les indices de la TABLE TAB1
    %'IX' : Numero actuel de parametres dans le "Random Set"
    %'SN' : Numero sequentiel de l'element courants du resultat
    %'PN' : Probabilite de realisation de l'element courant
    %'MIN' : Valeurs minimales des elements courants du resultat
    %'CPN' : Probabilites des elements courants du resultat
    %'MAX' : Valeurs maximales des elements courants du resultat
    %'CPX' : Probabilites des elements courants du resultat

    %'MINS' : Valeurs minimales des elements du resultat
        ordonnes et modifies pour generer une evolution
    %'CPNS' : Probabilites cumules des elements du resultat
        ordonnes et modifies pour generer une evolution
        (valeur identique au %'CPXS')
    %'MAXS' : Valeurs maximales des elements du resultat
        ordonnes et modifies pour generer une evolution
    %'CPXS' : Probabilites cumules des elements du resultat
        ordonnes et modifies pour generer une evolution
        (valeur identique au %'CPNS')

    La table TAB1 doit avoir le format suivant:

    TAB1.'VAR' : TABLE contenant les donnees pour la variable VAR
    TAB1.'VAR'.'MIN' : LISTREEL avec les valeurs de la borne inferieure des elements focales
    TAB1.'VAR'.'MAX' : LISTREEL avec les valeurs de la borne superieure des elements focales
    TAB1.'VAR'.'CPB' : LISTREEL avec les valeurs de probabilite cumule des elements focales

    DBG1 : An optional argument with a value of type ENTIER indicating
        the debugging level (DBG1 missing or DBG1=0, no debugging)

    Exemple :

    Random_Set_Theory_01.dgibi
    Random_Set_Theory_03.dgibi
    Random_Set_Theory_03.dgibi

## @SATURAT [Fluides Modele] (proc)
Procedure @SATURAT

MAT1 = @SATURAT CHTK1 CHPC1 ;

Objet :

   La procedure @SATURAT determine, par defaut, la saturation en eau
liquide d'un milieu poreux modelise par un modele THERMOHYDRIQUE
SCHREFLER. Elle est fonction de la temperature du milieu en Kelvin
et de sa pression capillaire en Pascal.

   Cette procedure est appelee par la procedure @MATETHM.

Commentaire :

CHTK1 = CHPOINT de temperature (K) ;

CHPC1 = CHPOINT de pression capillaire (Pa) ;

## @SIGREF [Post-traitement Analyse] (proc)
 Procedure @SIGREF

    SS = @SIGREF PNOM MNOM EPAI FISS MODL1 ;

 Objet :

   Cette procedure est appelee par @LISPA16. Elle permet de calculer la
 contrainte de reference pour l'application de l'Annexe A16 du RCC-MR aux
 elements LISP.

 Commentaire :

SS : contrainte de reference (type MCHAML)

PNOM : effort de traction nominal Nzz (type MCHAML)

MNOM : effort de flexion nominal Mxx (type MCHAML)

EPAI : epaisseur de l'element LISP (type MCHAML)

FISS : profondeur de la fissure (type MCHAML)

MODL1 :objet modele (type MMODEL) associe au maillage constitue d'elements
       LISP

## @SOLVMEC [Mecanique Resolution] (proc)
Procedure @SOLVMEC

@SOLVMEC TAB1 ;

Objet :

   La procedure @SOLVMEC permet d'effectuer un calcul mecanique non lineaire
incremental selon un parametre d'evolution donne par l'utilisateur
(pseudo temps ou temps reel).

   Cette procedure est analogue a la procedure PASAPAS (indices en entree et
en sortie identiques) mais en constitue une version beaucoup plus simplifiee
et ceci a des fins de tests ou pedagogiques uniquement.

   Cette procedure n'est pas supportee et ne rentre pas dans le perimetre de
validation de Cast3M. La procedure de reference pour le calcul incremental
en mecanique et thermique est PASAPAS.

   De plus, les performances sont sensiblement moins elevees que celles de PASAPAS
et le domaine d'application est limite a la mecanique seule. Cependant, elle met
en oeuvre, comme dans PASAPAS, un schema de quasi Newton-Raphson pour la minimisation
du residu. Celui-ci est facilement lisible et modifiable pour l'utilisateur.

   Les indices de la table TAB1 a definir sont les suivants :

MODELE : Objet de type MMODEL, obligatoire.
        Ensemble des modeles avec une formulation mecanique
        --> objet cree par l'operateur MODE.

CARACTERISTIQUES : Objet de type MCHAML, obligatoire.
        Champ de caracteristiques materielles et geometriques
        (si necessaire) associees au modele
        --> objet cree par les operateurs MATE/CARA.

BLOCAGES_MECANIQUES : Objet de type RIGIDITE, obligatoire.
        Matrice des blocages mecaniques associee a une condition aux
        limites de type Dirichlet (deplacement impose)
        --> objet cree par les operateurs BLOQ/RELA.

CHARGEMENT : Objet de type CHARGEME, obligatoire.
        Definition du chargement en fonction du parametre d'evolution
        Les types de chargements acceptes sont :
        * ceux de type 'DIMP' (deplacements imposes)
        * ceux de type 'MECA' (efforts imposes)
        --> objet cree par l'operateur CHAR.

TEMPS_CALCULES : Objet de type LISTREEL, obligatoire.
        Liste des valeurs du parametre d'evolution (temps) pour
        lesquelles on effectue le calcul.
        --> objet cree par l'operateur PROG.

GRANDS_DEPLACEMENTS : Objet de type LOGIQUE, facultatif,
        egal a FAUX par defaut.
        Indique que l'on souhaite faire le calcul sous l'hypothese
        des "grands deplacements", c'est-a-dire :
        - re-calcul de la matrice de rigidite sur la configuration
        au debut de chaque pas de temps
        (et non la configuration initiale) ;
        - prise en compte de la matrice de raideur geometrique
        associee aux contraintes au debut du pas de temps
        (appel a l'operateur KSIG) ;
        - utilisation de la deformation quadratique (Green Lagrange)
        pour evaluer l'increment de deformation sur chaque pas de
        temps (et non la deformation lineaire) ;
        - transport des contraintes sur la configuration a la fin
        du pas de temps (operateur PICA).
        - verification de l'equilibre sur la configuration a la fin
        du pas de temps (et non la configuration initiale).

ACCELERATION_CONVERGENCE : Objet de type LOGIQUE, facultatif,
        egal a FAUX par defaut.
        Indique que l'on souhaite utiliser l'acceleration de convergence
        basee sur les precedents residus (operateur ACT3).
        L'acceleration est effectuee toutes les 4 iterations.

## @STAT [—] (proc)
   CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
  A DISPOSITION DE LA COMMUNAUTE CASTEM2000
PAR DELERUYELLE Fr. (SOCOTEC-INDUSTRIE a l'IPSN/DES)

   Procedure @STAT

   XM EX (YM EY A B R) = @STAT LX (LY) ;

   Objet :

   Cette procedure calcule les moyennes, ecarts types, et coefficients
   de regression lineaire de listes de reels.

   Commentaires :

   LX : liste de reels dont on veut la moyenne et l'ecart type.
        (type LISTREEL).

   LY : eventuellement, seconde liste de reels.
        (type LISTREEL).

   XM : moyenne de la liste LX (type FLOTTANT).

   EX : ecart type de la liste LX (type FLOTTANT).

   YM : si LY a ete donnee, moyenne de cette seconde liste.
        (type FLOTTANT).

   EY : si LY a ete donnee, ecart type de cette seconde liste.
        (type FLOTTANT).

   A : coefficient directeur de la droite de regression lineaire
        de LY sur LX (type FLOTTANT).

   B : ordonnee a l'origine de la droite de regression lineaire
        de LY sur LX (type FLOTTANT).

   R : coefficient de correlation de la regression lineaire
        de LY sur LX (type FLOTTANT).

   Exemple :

   lx = prog 0 1.85 4.65 7 10 11 12 15.8 ;
   ly = prog 2.25 2. 1.75 1.4 1. 0.8 1. 1.2 ;
   xm ex ym ey a b r = @STAT lx ly ;
   mess 'moy. y=' ym 'ecart type y=' ((ey / ym) * 100.) '%';
   ly2 = (lx * a) + (prog (dime lx) * b) ;
   titr 'a=' a 'b=' b 'r=' r ;
   ev0 = evol blanc manu 'x' lx 'y' ly ;
   ev1 = evol rouge manu 'x' lx 'y' ly2 ;
   dess (ev0 et ev1) ;

   Remarques :

   1) L'ecart type n'est pas donne en pourcentage. Il faut faire
      (ex/xm)*100. pour l'avoir en 'pour cent'.

   2) A et B sont tels que LX etant une liste d'abscisses et LY une
      liste d'ordonnees, la droite de regression lineaire aura pour
      equation : y = A.x + B

   3) Une regression lineaire de LY sur LX ne se justifie que si la
      valeur absolue du coefficient de correlation R est proche de 1.

## @STATIO [Mecanique Resolution] (proc)
L'algorithme stationnaire a ete cree et developpe par DANG VAN K.,
MAITOURNAM H. et NGUYEN Q. S. du Laboratoire de Mecanique des Solides
a l'Ecole Polytechnique.

Pour en connaitre le principe, voir l'article paru dans "Journal of
the Mechanics and Physics of Solids", ecrit par DANG VAN K. et
MAITOURNAM H., intitule : "Steady-state flow in classical elastoplas-
ticity : applications to repeated rolling and sliding contact" (1993,
41(11), pp. 1691-1710).

Cette procedure a ete programmee en langage Gibiane par DRAGON M., en
these au Laboratoire de Mecanique des Solides.

    Procedure @STATIO

    @STATIO TAB1 ;

    TAB1. BLOCAGES_MECANIQUES
        CARACTERISTIQUES
        CHARGEMENT
        CONTRAINTES
        CONTRAINTES_PLASTIQUES
        CONVERGENCE
        CRITERE_PLASTICITE
        DEFORMATIONS
        DEFORMATIONS_PLASTIQUES
        DEPLACEMENTS
        EP2D
        EP3D
        FORCES_PLASTIQUES
        MAXITERATION
        MODELE
        MODELE_TABLE
        PRECISION
        VARIABLES_INTERNES
        VA2D
        VA3D

    Objet :

Cette procedure permet de calculer les deformations plastiques d'une
structure soumise a un chargement mobile, dans l'etat stationnaire atteint
apres un grand nombre de cycles de chargement.

On se place dans le repere lie au chargement, et l'etat stationnaire est
determine directement. Exemples de telles structures : rail soumis au
passage repete d'une roue (2D), disque en rotation soumis au contact d'un
pion (3D) ...

   Commentaire :

Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres,
et en majuscules s'ils sont mis entre cotes).

TAB1 contient les parametres du calcul a definir en entree d'une part,
et les grandeurs mecaniques determinees au cours de la procedure d'autre
part.

     - Liste des parametres a definir en entree :

 BLOCAGES_MECANIQUES : (type RIGIDITE) blocages mecaniques

 CARACTERISTIQUES : (type MCHAML, sous-type CARACTERISTIQUES) champ de
        caracteristiques materielles, materiau elasto-plas-
        tique

 CHARGEMENT : (type CHPOINT) chargement defini sous la forme de
        de forces nodales

 MAXITERATION : (type ENTIER) nombre maximal d'iterations

 MODELE : (type MMODEL) objet modele s'appuyant sur le mail-
        lage entier de la structure, elasto-plastique

 MODELE_TABLE : (type TABLE) table indicee par des entiers de 1 a n,
        contenant les n colonnes du maillage 2D ou les n
        parts (type MMODEL) du maillage 3D axisymetrique
        (voir Remarques)

 PRECISION : (type FLOTTANT) precision utilisee dans le calcul du
        critere de plasticite, et dans le test de stationna-
        rite (par exemple 1.e-3)

     - Liste des parametres utilises au cours du calcul :

 Ces objets de type TABLE, contiennent sous les indices i designant les ite-
 rations, pour chacune de ces iterations (jusqu'a la convergence ou jusqu'a
 TAB1 . MAXITERATION) :

 CONTRAINTES : (type MCHAML, sous-type CONTRAINTES) contraintes
        obtenues par le calcul elastique

 CONTRAINTES_PLASTIQUES : (type MCHAML, sous-type CONTRAINTES) (L : epsp),
        ou L est la matrice de Hook et epsp le champ des
        deformations plastiques

 CONVERGENCE : (type LOGIQUE) mis a VRAI lorsque le calcul
        converge a la derniere iteration

 CRITERE : (type TABLE) table resultant du calcul du critere
        de plasticite contenant les 3 indices suivants :
        PL : logique VRAI si la solution est plastique
        NPL : nombre de points de Gauss ou la solution
        est plastique
        CR : (type MCHAML) vaut 1 en chaque point ou le
        critere est viole, et 0 sinon

 DEFORMATIONS : (type MCHAML, sous-type DEFORMATIONS) deformations
        obtenues par le calcul elastique

 DEFORMATIONS_PLASTIQUES : (type MCHAML, sous-type DEFORMATIONS) deformations
        plastiques calculees par l'algorithme stationnaire

 DEPLACEMENTS : (type CHPOINT, sous-type DEPLACEMENTS) deplace-
        ments obtenues par le calcul elastique

 EP2D : (type MCHAML, sous-type DEFORMATIONS) deformations
        plastiques initiales pour chaque iteration en 2D

 EP3D : (type MCHAML, sous-type DEFORMATIONS) deformations
        plastiques initiales pour chaque iteration en 3D

 FORCES_PLASTIQUES : (type CHPOINT, sous-type FORCE) forces calculees
        a partir des CONTRAINTES_PLASTIQUES

 VARIABLES_INTERNES : (type MCHAML, sous-type VARIABLES INTERNES) vari-
        ables internes
[… notice tronquée ; texte complet dans l'archive PCW_24]

## @STBL [Langage Objets] (proc)
Procedure @STBL
--------------- ENUM

OBJ1 = @STBL TAB1 ;

Objet :

La procedure @STBL effectue l'operation ET sur tous les objets
contenus dans la table TAB1 et sous les indices entiers allant de 1
a N.

## @SYSLIN [Mathematiques Autres] (proc)
Procedure @SYSLIN

    TABU0 = @SYSLIN TABM0 TABX0;

Auteurs: L. GELEBART (CEA Saclay DEN/DMN/SRMA)

Date : 09/2008

Exemple associe : utilise par les procedures @KEFF

Contact : lionel(dot)gelebart(at)cea(dot)fr

Objet :
Resolution du systeme lineaire M.U=X

Commentaires :
TABM0 : Table decrivant la matrice M
        TABM0 . i. j = M(i,j)
TABX0 : Table decrivant le vacteur X
        TABX0 . j = X(j)
TABU0 : Table resultat donnant le vecteur solution U
        TABU0 . j = U(j)
Remarques :
    Cette procedure utilise RESOU. Il peut parfois etre
    necessaire de modifier l'ordre des equations pour que
    RESOU puisse resoudre le systeme

## @TEST [Mecanique Resolution] (proc)
   Procedure @TEST

   Objet :

Cette procedure est appelee en interne par la procedure @STATIO

## @TOLE2 [Maillage Autres] (proc)
    Procedure @TOLE2
    ----------------- @lisse @tole3

    MAI2 = @TOLE2 MAI1 FLOT1 ENT1 ;

    Objet :

La procedure @TOLE2 cree un maillage massif de CUB8 a partir d'un
maillage MAI1 de carene ( maillage surfacique tridimensionnel QUA4).
La surface de la carene est au milieu de l'epaisseur.

    Commentaire :

    FLOT1 : reel donnant l'epaisseur de la carene.

    ENT1 : entier donnant le nombre d'elements dans l'epaisseur.

## @TOLE3 [Maillage Autres] (proc)
    Procedure @TOLE3
    ----------------- @lisse @tole2

    MAI1 MAI2 MAI3 MAI4 MAI5 = @TOLE3 MAI6 MAI7 FLOT1 ENT1;

    Objet :

La procedure @TOLE3 cree un maillage massif de CUB8 a partir de 2
couples de carenes ayant le meme nombre de points (maillage 3D de
SEG2). Ce couple massif a ses faces laterales planes et paralleles.

    Commentaire :

    MAI6 : maillage du premier couple externe (type SEG2).

    MAI7 : maillage du second couple externe(type SEG2).

    FLOT1 : epaisseur de la carene.

    ENT1 : entier donnant le nombre d'elements dans l'epaisseur.

    MAI1 : maillage du premier couple interne (SEG2).

    MAI2 : maillage du second couple interne (SEG2).

    MAI3 : maillage de la surface exterieure ( elle s'appuie sur
        les deux couples externes) (QUA4).

    MAI4 : maillage de la surface interne (elle s'appuie sur les
        deux couples internes) (QUA4).

    MAI5 : maillage volumique ( CUB8) du couple massif.

## @TORO [Magnetostatique Magnetostatique] (proc)
     CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
    A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

procedure @TORO

TABCHB TAB2 = @TORO TAGEO1 TABOB1 ;

Objet:

Calcul de l'induction magnetique creee par un ensemble
de bobines circulaires ou en 'D', reparties regulierement
autour de l'axe Oz, en l'absence de fer.

Commentaire :

En entree :

TAGEO1 table des domaines de calcul du champ

   TAGEO1.i geometrie ou le champ est calcule (type TABLE)
   TAGEO1.i.'mail' : maillage de la geometrie (type MAILLAGE)

TABOB1 table a deux indices contenant les donnees
------ relatives aux bobines (type TABLE)

      .GENE table contenant les donnees geometriques
        .1 nbob: nombre de bobines (type ENTIER)
        .2 b: largeur des bobines (type FLOTTANT)
        .3 h: hauteur des bobines (type FLOTTANT)
        .4 cbob: centre de la bobine (type POINT)
        .5 vn: vecteur normal au plan de la bobine (type POINT)
        .6 tsol: table des solenations des bobines
        .i solenation (courant * nombre de spires)
        de la bobine i (type FLOTTANT)
        .7 rt: rayon du tore (type FLOTTANT)
        .8 ri: nombre de bobines (type FLOTTANT)
      .TYPE 'c' pour une bobine circulaire
        'd' pour une bobine en 'D'
      .TRAC1 si oui : trace du maillage des bobines (type LOGIQUE)
      .CBIOT si oui : calcul de l'induction magnetique
      .D = troncon : table des troncons:
        troncon.j = troncj : table du troncon j:
        troncj.'l' longueur du troncon si rectiligne,
        .'r' rayon de courbure et
        .'alpha' angle de courbure si courbe

En sortie :

TABCHB table contenant
        TABCHB.i champ de Biot et Savart relatif au i-eme
        maillage GEO1 (type CHPOINT)

TAB2 table contenant
BOBMAI.i maillage de chaque bobine (type MAILLAGE)
CONT.j ensemble des coupes sur le plan j
        (type MAILLAGE)

Remarques:

Les grandeurs suivantes sont "en dur" dans la procedure :

NELE nombre d'elements generes lors des rotations
        et des translations effectuees pendant la
        creation du maillage des bobines.

COEF1 coefficient etablissant la distance critique
        de selection des points lors de la recherche
        de contour.

La procedure fournit l'induction dans le vide, calculee avec
mu0 = 4 pi 10-7.

## @TOTAL [Post-traitement Analyse] (proc)
     CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
    A DISPOSITION DE LA COMMUNAUTE CASTEM2000
        PAR P. LIBEYRE ( CEA/DSM/DRFC )

Procedure @TOTAL

TOT = @TOTAL CH1 GEO COMP1 ;

Objet :

Cette procedure calcule la resultante de la composante
d'un CHPOINT sur un maillage donne.

Commentaire:

CH1 : champ par points dont on veut sommer une composante
        (type CHPOINT)

GEO : MAILLAGE sur lequel on veut effectuer la sommation

COMP1 : nom de la composante a sommer (type MOT)

TOT : resultante de type FLOTTANT

## @VECOUL [Post-traitement Analyse] (proc)
 Procedure @VECOUL

 Syntaxe : VCTOT1 = @VECOUL CH1 AMPL1 (LMOT1) (MOT1) (VRED1) ;

    Objet :

Procedure qui construit un objet VCTOT1 (type VECTEUR)
de couleur variable en fonction de sa norme
a partir d'un champs de vecteur CH1 (type CHPOINT).

L'objet VCTOT1 est constitue de 10 sous-vecteurs de couleurs
VIOL AZUR BLEU TURQ OCEA VERT OLIV JAUN ORAN ROUG
qui correspondent a 10 intervalles de la plage de la norme
(echelle lineaire dans le sens croissant).

Les composantes des sous-vecteurs de couleurs sont renommees pour
permettre l'affichage de la valeur moyenne de la norme du vecteur
associee a sa couleur lors du trace graphique.

Il est possible d'extraire un pourcentage (VRED1 x 100) %
(si VRED1 dans [0,1]) ou un nombre donné VRED1 (si VRED1 > 1) de ces
vecteurs : aleatoirement si MOT1 = ALTR, regulierement sinon.

Postraitement TRAC VCTOT1 MAILLAGE ;

    Commentaire :

Entree :
CH1 : Champs de vecteur (type CHPOINT)

AMPL1 : Facteur d'amplification (FLOTTANT) OBLIGATOIRE

LMOT1 : Préciser les noms de composantes voulues (type LISTMOTS)

MOT1 : Extraction aleatoire si MOT1 = ALTR, reguliere sinon

VRED1 : Pourcentage ([0,1]) ou nombre (>1) de vecteurs extraits
        (type FLOTTANT)

Sortie :
VCTOT1 : Vecteur (VECTEUR) compose de 10 sous-type vecteur de
        differentes couleurs.

    Remarques :

1 - Le facteur d'amplification AMPL1 est une entree obligatoire.

2 - Si VRED1 < 0., on extrait 100 %.

## @VIS3D [Post-traitement Affichage] (proc)
     Procedure VIS3D

   @VIS3D GEO1 POINT1 POINT2 OEIL NROT (ROTOT);

    Objet :

  La procedure @VIS3D effectue une animation de l'enveloppe du maillage
  GEO1 par NROT rotations successives entre -ROTOT/2 et +ROTOT/2
  autour de l'axe defini par les points POINT1 et POINT2.
  Cette animation est visualisee suivant le point d'observation OEIL;

GEO1 : MAILLAGE (3D)
POINT1 : POINT
POINT2 : POINT
OEIL : POINT
NROT : ENTIER
ROTOT : FLOTTANT

    remarque :

  Les arguments doivent etre indiques dans l'ordre.
  Pour stopper l'animation, il suffit de cliquer dans la fenetre de
  dessin.

## @VISOR [Post-traitement Affichage] (proc)
   CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
  A DISPOSITION DE LA COMMUNAUTE CASTEM2000
PAR DELERUYELLE Fr. (SOCOTEC-INDUSTRIE a l'IPSN/DES)

  Procedure @VISOR

  VEC1 = @VISOR GEO1 (FLOT1) (COUL1) ;

  Objet :

Cette procedure permet de visualiser l'orientation des elements
orientables (SEG2,SEG3,TRI3,TRI6,QUA4,QUA8). Elle produit un
objet de type VECTEUR qu'on peut tracer.

  Commentaires :

  GEO1 : Maillage. (type MAILLAGE)

  FLOT1 : Coefficient d'amplification du vecteur resultat.
        Facultatif, il vaut 2/3 par defaut. (type FLOTTANT)

  COUL1 : Couleur du vecteur resultat.
        Facultatif, il est jaune par defaut. (type MOT)

  VEC1 : Objet resultat. (type VECTEUR)

  Exemple :

  opti dime 2 elem qua8 ;
  li = (0 0) d 5 (1 0) ;
  su = li tran 3 (0 -1) ;
  vo1 = @VISOR li ; trac vo1 li ;
  vo2 = @VISOR su roug ; trac vo2 su ;
  vo3 = @VISOR (su et li) ; trac vo3 su ;
  vo4 = @VISOR (cont su) ; trac vo4 su ;

  Remarques :

  1) En 2D, pour les elements plans, la fleche est vers le
     bas pour les elements retrogrades (aiguilles d'une montre)
     et vers le haut pour les elements directs (trigonometriques).

  2) En 3D, pour les elements plans, la fleche est dans le sens
     de la normale positive.

  3) Pour les elements lignes, la fleche est dans le sens de
     parcourt des elements.

## @ZACPLUS [Mecanique Resolution] (proc)
procedure @ZACPLUS

RES = @ZACPLUS TBZA;

Objet :

La procedure @ZACPLUS calcule directement l'etat limite d'une
structure soumise a un chargement cyclique. La methode de calcul
utilisee dans @ZACPLUS est basee sur les travaux des methodes
d'analyses simplifiees de MM. ZARKA ARNAUDEAU CASIER et sur les
modifications proposees par M. GATT

Commentaire :

TBZA : objet de type TABLE contenant les donnees suivantes

indice type objet pointe commentaires

TBZA.SIG1 MCHAML solutions elastiques correspondant
TBZA.SIG2 aux extrema du cycle de chargement.
        Ces contraintes elastiques seront
        precedemment calculees hors de la
        procedure.
        Nous supposons que la structure etudiee
        est soumise a un chargement cyclique
        dependant d'un seul parametre.
        La reponse elastique sera de la forme :

        SIG elas = (1 - F)*SIG1 + F*SIG2

        (F etant une fonction periodique a
        valeur dans l'intervalle [0,1]).

TBZA.CLIM RIGIDITE rigidites de blocage utilisees dans
        le calculde SIG1 et SIG2.

TBZA.I TABLE table contenant les caracteristiques
        du Ieme materiau de la structure.

TBZA.I.GEOM MAILLAGE Ieme partie geometrique delimitant l'un
        des materiaux constituant la structure.

TBZA.I.YOUN FLOTTANT module d'Young de la Ieme partie
        MCHAML geometrique.
        EVOLUTION

TBZA.I.NU FLOTTANT coefficient de Poisson
        MCHAML de la Ieme partie geometrique.
        EVOLUTION

TBZA.I.SIGY FLOTTANT limite d'elasticite
        MCHAML de la Ieme partie geometrique.
        EVOLUTION

TBZA.I.H FLOTTANT module d'ecrouissage
        MCHAML de la Ieme partie geometrique.
        EVOLUTION

RES : objet de type TABLE contenant les resultats suivants

DEPFINA MCHAML amplitudes des deformations plastiques
        (delta epsilon plastiques).

DSIFINA MCHAML amplitudes des contraintes(delta sigma).

EPMFINA MCHAML deformations plastiques moyennes
        (epsilon plastiques moyen).

SIMFINA MCHAML contraintes moyennes (sigma moyen).

MATETOT MCHAML champ contenant les caracteristiques
        des materiaux composant la structure
        globale.

MODETOT MMODEL modele associe au maillage
        de la structure globale.

Remarque 1:

Cette procedure peut etre utilisee dans les modes de calcul
suivants :
    - contraintes planes
    - deformations planes
    - axisymetrique
    - tridimensionnel

Remarque 2:

Pour utiliser cette procedur il faut que tous les MODELEs
utilises dans le calcul de la structure aient le meme nom de
constituant. Il faut donc le definir au moment de la creation
des modeles (operateur MODE).

## @ZACPRO1 [Mecanique Resolution] (proc)
procedure @ZACPRO1

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO2 [Mecanique Resolution] (proc)
procedure @ZACPRO2

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO3 [Mecanique Resolution] (proc)
procedure @ZACPRO3

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO4 [Mecanique Resolution] (proc)
procedure @ZACPRO4

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO5 [Mecanique Resolution] (proc)
procedure @ZACPRO5

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO6 [Mecanique Resolution] (proc)
procedure @ZACPRO6

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO7 [Mecanique Resolution] (proc)
procedure @ZACPRO7

  Cette procedure est appelee par la procedure @ZACPLUS

## @ZACPRO8 [Mecanique Resolution] (proc)
procedure @ZACPRO8

  Cette procedure est appelee par la procedure @ZACPLUS

## AAA1 [Mathematiques Elementaires]
   Operateur /
   ----------- ** *

   RESU1 = ( MODL1) OBJET1 / OBJET2 (MOT1) ;

   Objet :

   L'operateur / calcule la division de OBJET1 par OBJET2.

   MOT1 permet de preciser le nom de la composante sur laquelle
   porte l'operation pour les objets de type EVOLUTION (ABSC ou ORDO)
   ou NUAGE (voir aussi remarques).

   Operations possibles :

|  OBJET1  |  OBJET2  |  RESU1  |
|  ENTIER  |  ENTIER  |  ENTIER  |
|  ENTIER  |  FLOTTANT  |  FLOTTANT  |
|  ENTIER  |  LISTREEL  |  LISTREEL  |
|  ENTIER  |  EVOLUTIO  |  EVOLUTIO  |
|  ENTIER  |  CHPOINT  |  CHPOINT  |
|  ENTIER  |  MCHAML  |  MCHAML  |
|  ENTIER  |  NUAGE  |  NUAGE  |
|  FLOTTANT  |  ENTIER  |  FLOTTANT  |
|  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |
|  FLOTTANT  |  LISTREEL  |  LISTREEL  |
|  FLOTTANT  |  EVOLUTIO  |  EVOLUTIO  |
|  FLOTTANT  |  CHPOINT  |  CHPOINT  |
|  FLOTTANT  |  MCHAML  |  MCHAML  |
|  FLOTTANT  |  NUAGE  |  NUAGE  |
|  POINT  |  ENTIER  |  POINT  |
|  POINT  |  FLOTTANT  |  POINT  |
|  LISTREEL  |  ENTIER  |  LISTREEL  |
|  LISTREEL  |  FLOTTANT  |  LISTREEL  |
|  LISTREEL  |  LISTREEL  |  LISTREEL  |
|  LISTREEL  |  LISTENTI  |  LISTREEL  |
|  LISTENTI  |  ENTIER  |  LISTENTI  |
|  LISTENTI  |  FLOTTANT  |  LISTREEL  |
|  LISTENTI  |  LISTENTI  |  LISTENTI  |
|  LISTENTI  |  LISTREEL  |  LISTREEL  |
|  EVOLUTION  |  ENTIER  |  EVOLUTION  |
|  EVOLUTION  |  FLOTTANT  |  EVOLUTION  |
|  EVOLUTION  |  EVOLUTION  |  EVOLUTION  |
|  CHPOINT  |  ENTIER  |  CHPOINT  |
|  CHPOINT  |  FLOTTANT  |  CHPOINT  |
| CHPOINT (LISTMOT1)|  CHPOINT  (LISTMOT2)  |  CHPOINT  (LISTMOT3)  |
|  MCHAML  |  ENTIER  |  MCHAML  |
|  MCHAML  |  FLOTTANT  |  MCHAML  |
| (MODL1) MCHAML  |  MCHAML  |  MCHAML  |
| MCHAML (LISTMOT1) |  MCHAML (LISTMOT2)  |  MCHAML (LISTMOT3)  |
|  RIGIDITE  |  ENTIER  |  RIGIDITE  |
|  RIGIDITE  |  FLOTTANT  |  RIGIDITE  |
|  NUAGE  |  ENTIER  |  NUAGE  |
|  NUAGE  |  FLOTTANT  |  NUAGE  |
|  TABLE 'VECTEUR'  |  ENTIER  |  TABLE 'VECTEUR'  |
|  TABLE 'VECTEUR'  |  FLOTTANT  |  TABLE 'VECTEUR'  |

    Remarque 1 :

  Lorsque l'operateur / calcule la division de deux CHPOINT, on
utilise par defaut la regle de division suivante : tout point
ayant dans un des CHPOINT une composante unique de nom "SCAL",
voit toutes les valeurs des composantes de l'autre CHPOINT
divisees par la valeur du scalaire. Le CHPOINT RESU1 ne porte
que sur de tels points.

   Lorsque l'operateur / calcule la division de deux CHPOINT, on peut
aussi utiliser la regle de division suivante a condition de
fournir trois listes mot de longueur egale qui constituent
la cle de l'operation :
La ieme composante du chpoint resultat aura pour nom le ieme mot
de la troisieme liste de mots et sera egale au produit
de la composante du 1er champoint reperee par le ieme mot de la
1ere liste de mots par la composante du 2nd champoint reperee par
le ieme mot de la 2nde liste de mots.

Ex :
      chp3 chp1 chp2
   composante composante composante
    resultat argument1 argument2
      'FX' 'KX' 'UX'
      'FY' 'KYX' 'UX'

      lmot1 = 'MOTS' 'KX' 'KYX' ;
      lmot2 = 'MOTS' 'UX' 'UX' ;
      lmot3 = 'MOTS' 'FX' 'FY' ;
      chp3 = chp1 '/' chp2 lmot1 lmot2 lmot3 ;

Dans le cadre de cette option on peut specifier la nature du champ
resultat avec le mot cle 'NATURE'. Celui ci est alors suivi d'un des
trois mots suivant 'DIFFUS' 'DISCRET' 'INDETERMINE'.
On rappelle qu'un champ par point vaut zero la ou il n'est pas defini.

    Remarque 2 :

    L'operateur / calcule la division d'un objet de type TABLE
de sous-type 'VECTEUR' par un nombre (FLOTTANT ou ENTIER) VAL1.
Le resultat est de type TABLE et de sous-type 'VECTEUR'.

    Remarque 3 :

    Lorsque l'operateur / calcule la division de deux objets de type
EVOLUTION, les deux objets donnes, doivent avoir le Meme nombre de
courbes N1, et doivent etre de Meme type, c'est-a-dire soit reels,
soit complexes :

    a) Objets EVOLUTION reels:

    On effectue la division terme a terme des deux courbes de Meme indice
pour les deux objets; les abscisses de ces courbes doivent etre des
progressions identiques; elles deviennent les abscisses des courbes du
nouvel objet EVOLUTION cree par l'operateur.

    b) Objets EVOLUTION complexes :

    Les abscisses doivent etre identiques; elles deviennent les
abscisses du nouvel objet EVOLUTION cree par l'operateur.
Chacun des deux objets peut etre, soit "PREE PIMA", soit "MODU PHAS".

L'objet EVOL3 a le meme type que EVOL1. On peut lui attribuer une
couleur COUL1 :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## AAA2 [Mathematiques Elementaires]
   Operateur *
   ----------- ** /

   RESU1 = ( MODL1) OBJET1 * OBJET2 (MOT1) ;

   Objet :

   L'operateur * calcule le produit des objets OBJET1 et OBJET2.

   MOT1 permet de preciser le nom de la composante sur laquelle
   porte l'operation pour les objets de type EVOLUTION (ABSC ou ORDO)
   ou NUAGE (voir aussi remarques).

   Operations possibles :

|  OBJET1  |  OBJET2  |  RESU1  |
|  ENTIER  |  ENTIER  |  ENTIER  |
|  ENTIER  |  FLOTTANT  |  FLOTTANT  |
|  ENTIER  |  POINT  |  POINT  |
|  ENTIER  |  LISTREEL  |  LISTREEL  |
|  ENTIER  |  LISTENTI  |  LISTENTI  |
|  ENTIER  |  CHPOINT  |  CHPOINT  |
|  ENTIER  |  MCHAML  |  MCHAML  |
|  ENTIER  |  RIGIDITE  |  RIGIDITE  |
|  ENTIER  |  EVOLUTION  |  EVOLUTION  |
|  ENTIER  |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |
|  ENTIER  |  NUAGE  |  NUAGE  |
|  FLOTTANT  |  ENTIER  |  FLOTTANT  |
|  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |
|  FLOTTANT  |  POINT  |  POINT  |
|  FLOTTANT  |  LISTREEL  |  LISTREEL  |
|  FLOTTANT  |  LISTENTI  |  LISTENTI  |
|  FLOTTANT  |  CHPOINT  |  CHPOINT  |
|  FLOTTANT  |  MCHAML  |  MCHAML  |
|  FLOTTANT  |  RIGIDITE  |  RIGIDITE  |
|  FLOTTANT  |  EVOLUTION  |  EVOLUTION  |
|  FLOTTANT  |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |
|  FLOTTANT  |  NUAGE  |  NUAGE  |
|  POINT  |  ENTIER  |  POINT  |
|  POINT  |  FLOTTANT  |  POINT  |
|  LISTREEL  |  ENTIER  |  LISTREEL  |
|  LISTREEL  |  FLOTTANT  |  LISTREEL  |
|  LISTREEL  |  LISTREEL  |  LISTREEL  |
|  LISTREEL  |  LISTENTI  |  LISTREEL  |
|  LISTENTI  |  ENTIER  |  LISTENTI  |
|  LISTENTI  |  FLOTTANT  |  LISTREEL  |
|  LISTENTI  |  LISTENTI  |  LISTENTI  |
|  LISTENTI  |  LISTREEL  |  LISTREEL  |
|  EVOLUTION  |  ENTIER  |  EVOLUTION  |
|  EVOLUTION  |  FLOTTANT  |  EVOLUTION  |
|  EVOLUTION  |  MCHAML  |  MCHAML  |
|  EVOLUTION  |  CHPOINT  |  CHPOINT  |
|  EVOLUTION  |  EVOLUTION  |  EVOLUTION  |
|  CHPOINT  |  ENTIER  |  CHPOINT  |
|  CHPOINT  |  FLOTTANT  |  CHPOINT  |
| CHPOINT (LISTMOT1)|  CHPOINT  (LISTMOT2)  |  CHPOINT  (LISTMOT3)  |
|  CHPOINT  |  RIGIDITE  |  CHPOINT  |
|  CHPOINT  |  EVOLUTION  |  CHPOINT  |
|  MCHAML  |  ENTIER  |  MCHAML  |
|  MCHAML  |  FLOTTANT  |  MCHAML  |
|  MCHAML  |  EVOLUTION  |  MCHAML  |
| (MODL1) MCHAML  |  MCHAML  |  MCHAML  |
| MCHAML (LISTMOT1) |  MCHAML (LISTMOT2)  |  MCHAML (LISTMOT3)  |
|  RIGIDITE  |  CHPOINT  |  CHPOINT  |
|  RIGIDITE  |  ENTIER  |  RIGIDITE  |
|  RIGIDITE  |  FLOTTANT  |  RIGIDITE  |
|  NUAGE  |  ENTIER  |  NUAGE  |
|  NUAGE  |  FLOTTANT  |  NUAGE  |
|  TABLE 'VECTEUR'  |  ENTIER  |  TABLE 'VECTEUR'  |
|  TABLE 'VECTEUR'  |  FLOTTANT  |  TABLE 'VECTEUR'  |

    Remarque 1 :

  Lorsque l'operateur * calcule le produit de deux CHPOINT, on
utilise par defaut la regle de multiplication suivante : tout point
ayant dans un des CHPOINT une composante unique de nom "SCAL",
voit toutes les valeurs des composantes de l'autre CHPOINT
multipliees par la valeur du scalaire. Le CHPOINT RESU1 ne porte
que sur de tels points.

   Lorsque l'operateur * calcule le produit de deux CHPOINT, on peut
aussi utiliser la regle de multiplication suivante a condition de
fournir trois listes mot de longueur egale qui constituent
la cle de l'operation :
La ieme composante du chpoint resultat aura pour nom le ieme mot
de la troisieme liste de mots et sera egale au produit
de la composante du 1er champoint reperee par le ieme mot de la
1ere liste de mots par la composante du 2nd champoint reperee par
le ieme mot de la 2nde liste de mots.

Ex :
      chp3 chp1 chp2
   composante composante composante
    resultat argument1 argument2
      'FX' 'KX' 'UX'
      'FY' 'KYX' 'UX'

      lmot1 = 'MOTS' 'KX' 'KYX' ;
      lmot2 = 'MOTS' 'UX' 'UX' ;
      lmot3 = 'MOTS' 'FX' 'FY' ;
      chp3 = chp1 '*' chp2 lmot1 lmot2 lmot3 ;

Dans le cadre de cette option on peut specifier la nature du champ
resultat avec le mot cle 'NATURE'. Celui ci est alors suivi d'un des
trois mots suivant 'DIFFUS' 'DISCRET' 'INDETERMINE'.
On rappelle qu'un champ par point vaut zero la ou il n'est pas defini.

    Remarque 2 :

    L'operateur * calcule le produit d'un objet de type TABLE
de sous-type 'VECTEUR' par un nombre (FLOTTANT ou ENTIER) VAL1.
Le resultat est de type TABLE et de sous-type 'VECTEUR'.

    Remarque 3 :

    Lorsque l'operateur * calcule le produit de deux objets de type
EVOLUTION, les deux objets donnes, doivent avoir le Meme nombre de
courbes N1, et doivent etre de Meme type, c'est-a-dire soit reels,
soit complexes :

    a) Objets EVOLUTION reels:
[… notice tronquée ; texte complet dans l'archive PCW_24]

## AAA3 [Mathematiques Elementaires]
    Operateur **
    ------------ - /

    RESU1 = OBJET1 ** OBJET2 (MOT1) ;

    Objet :

    L'operateur ** eleve l'objet OBJET1 a la puissance OBJET2

    MOT1 permet de preciser le nom de la composante sur laquelle
    porte l'operation pour les objets de type EVOLUTION (ABSC ou ORDO)
    ou NUAGE (voir aussi remarques).

    Operations possibles :

|  OBJET1  |  OBJET2  |  RESU1  |
|  ENTIER  |  ENTIER  |  ENTIER  |
|  ENTIER  |  FLOTTANT  |  FLOTTANT  |
|  ENTIER  |  LISTREEL  |  LISTREEL  |
|  ENTIER  |  LISTENTI  |  LISTENTI  |
|  ENTIER  |  EVOLUTIO  |  EVOLUTIO  |
|  ENTIER  |  CHPOINT  |  CHPOINT  |
|  ENTIER  |  MCHAML  |  MCHAML  |
|  ENTIER  |  NUAGE  |  NUAGE  |
|  FLOTTANT  |  ENTIER  |  FLOTTANT  |
|  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |
|  FLOTTANT  |  LISTREEL  |  LISTREEL  |
|  FLOTTANT  |  LISTENTI  |  LISTREEL  |
|  FLOTTANT  |  EVOLUTIO  |  EVOLUTIO  |
|  FLOTTANT  |  CHPOINT  |  CHPOINT  |
|  FLOTTANT  |  MCHAML  |  MCHAML  |
|  FLOTTANT  |  NUAGE  |  NUAGE  |
|  LISTREEL  |  ENTIER  |  LISTREEL  |
|  LISTREEL  |  FLOTTANT  |  LISTREEL  |
|  LISTREEL  |  LISTREEL  |  LISTREEL  |
|  LISTREEL  |  LISTENTI  |  LISTREEL  |
|  LISTENTI  |  ENTIER  |  LISTENTI  |
|  LISTENTI  |  FLOTTANT  |  LISTREEL  |
|  LISTENTI  |  LISTREEL  |  LISTREEL  |
|  LISTENTI  |  LISTENTI  |  LISTENTI  |
|  EVOLUTION  |  ENTIER  |  EVOLUTION  |
|  EVOLUTION  |  FLOTTANT  |  EVOLUTION  |
|  CHPOINT  |  ENTIER  |  CHPOINT  |
|  CHPOINT  |  FLOTTANT  |  CHPOINT  |
|  MCHAML  |  ENTIER  |  MCHAML  |
|  MCHAML  |  FLOTTANT  |  MCHAML  |
|  RIGIDITE  |  ENTIER  |  RIGIDITE  |
|  RIGIDITE  |  FLOTTANT  |  RIGIDITE  |
|  NUAGE  |  ENTIER  |  NUAGE  |
|  NUAGE  |  FLOTTANT  |  NUAGE  |

    Remarque 1 :

    Lorsque l'operateur ** eleve a la puissance un objet EVOLUTION,
MOT1 permet de preciser si l'operation porte sur la liste des abscisses
(mot-cle 'ABSC') ou sur celle des ordonnees (mot-cle 'ORDO', par defaut).

    Remarque 2 :

    Lorsque l'operateur ** eleve a la puissance un objet NUAGE, MOT1
permet de preciser le nom de la composante sur laquelle porte l'operation.

    Remarque 3 :

    Pour les objets de type NUAGE, l'operation n'est possible que
    sur les composantes de type : ENTIER, FLOTTANT et EVOLUTION.

## AAA4 [Mathematiques Elementaires]
    Operateur -

    RESU1 = OBJET1 - OBJET2 | (LMOTS) ;
        | (MOT1)

    Objet :

    L'operateur - calcule la difference des objets OBJET1 et OBJET2.

    MOT1 permet de preciser le nom de la composante sur laquelle
    porte l'operation pour les objets de type EVOLUTION (ABSC ou ORDO)
    ou NUAGE (voir aussi remarques).

    Operations possibles :

   |  OBJET1  |  OBJET2  |  RESU1  |
   |-------------------------------------------------------------|
   |  ENTIER  |  ENTIER  |  ENTIER  |
   |  ENTIER  |  FLOTTANT  |  FLOTTANT  |
   |  ENTIER  |  LISTENTI  |  LISTENTI  |
   |  ENTIER  |  LISTREEL  |  LISTREEL  |
   |  ENTIER  |  EVOLUTIO  |  EVOLUTIO  |
   |  ENTIER  |  CHPOINT  |  CHPOINT  |
   |  ENTIER  |  MCHAML  |  MCHAML  |
   |  ENTIER  |  NUAGE  |  NUAGE  |
   |-------------------|--------------------|--------------------|
   |  FLOTTANT  |  ENTIER  |  FLOTTANT  |
   |  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |
   |  FLOTTANT  |  LISTENTI  |  LISTREEL  |
   |  FLOTTANT  |  LISTREEL  |  LISTREEL  |
   |  FLOTTANT  |  EVOLUTIO  |  EVOLUTIO  |
   |  FLOTTANT  |  CHPOINT  |  CHPOINT  |
   |  FLOTTANT  |  MCHAML  |  MCHAML  |
   |  FLOTTANT  |  NUAGE  |  NUAGE  |
   |-------------------|--------------------|--------------------|
   |  CHPOINT  |  CHPOINT  |  CHPOINT  |
   |  CHPOINT  |  ENTIER  |  CHPOINT  |
   |  CHPOINT  |  FLOTTANT  |  CHPOINT  |
   |-------------------|--------------------|--------------------|
   |  MCHAML  |  MCHAML  |  MCHAML  |
   |  MCHAML  |  ENTIER  |  MCHAML  |
   |  MCHAML  |  FLOTTANT  |  MCHAML  |
   |-------------------|--------------------|--------------------|
   |  EVOLUTION  |  EVOLUTION  |  EVOLUTION  |
   |-------------------|--------------------|--------------------|
   |  LISTENTI  |  ENTIER  |  LISTENTI  |
   |  LISTENTI  |  FLOTTANT  |  LISTREEL  |
   |  LISTENTI  |  LISTENTI  |  LISTENTI  |
   |  LISTENTI  |  LISTREEL  |  LISTREEL  |
   |-------------------|--------------------|--------------------|
   |  LISTREEL  |  ENTIER  |  LISTREEL  |
   |  LISTREEL  |  FLOTTANT  |  LISTREEL  |
   |  LISTREEL  |  LISTREEL  |  LISTREEL  |
   |  LISTREEL  |  LISTENTI  |  LISTREEL  |
   |-------------------|--------------------|--------------------|
   |  EVOLUTIO  |  ENTIER  |  EVOLUTIO  |
   |  EVOLUTIO  |  FLOTTANT  |  EVOLUTIO  |
   |-------------------|--------------------|--------------------|
   |  NUAGE  |  ENTIER  |  NUAGE  |
   |  NUAGE  |  FLOTTANT  |  NUAGE  |
   |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |

    Remarque 1 :

    Lorsque l'operateur - calcule la difference entre un CHPOINT et
un FLOTTANT, il soustrait à toutes les valeurs du CHPOINT la valeur du
FLOTTANT. La difference entre un FLOTTANT et un CHPOINT donne le
Meme resultat au signe pres.

    Remarque 2 :

    L'operateur - calcule la difference de deux objets de type TABLE
de sous-type 'VECTEUR'. Les tables doivent etre soustractibles, c'est
@ dire les elements d'indice commun doivent etre de type ENTIER ou
FLOTTANT.

    Remarque 3 :

    Lorsque l'operateur - calcule la difference entre deux objets de
type EVOLUTION, les deux objets, doivent etre de Meme type, c.à.d,
soit reels, soit complexes :

    a) Objets EVOLUTION reels :

    La somme est faite pour OBJET1=f(x) defini sur le domaine D1
        OBJET2=g(x) defini sur le domaine D2,
puis on calcule la difference sur le domaine commun (D1 et D2) .

    b) Objets EVOLUTION complexes :

    Les deux objets doivent avoir les memes abscisses. Chacun des deux
objets peut etre soit "PREE PIMA" soit "MODU PHAS" . L'objet RESU1
aura le meme type que OBJET1.

    Remarque 4 :

    Lorsque l'operateur - calcule la difference entre LIST(ENTI/REEL)
et ENTIER/FLOTTANT, la soustraction est effectuee sur tous les
termes du LIST(ENTI/REEL). L'ordre de OBJET1 et OBJET2 est important

    Remarque 5 :

    Lorsque l'operateur - calcule la difference de deux MCHAML,
pour les sous zones elementaires similaires, il effectue la difference
pour les noms de composantes identiques, sinon il realise l'adjonction
(La sous-zone est opposee avant l'adjonction si elle appartient a
OBJET2).

    Dans le cas ou les MCHAML pointent sur des objets non FLOTTANT, on
garde l'objet de pointeur non nul. Si les deux pointeurs sont non nuls,
une soustraction est faite dans le cas des 'POINT', des 'LISTREEL' et
des 'EVOLUTIO', en appliquant les regles de la soustraction relatives
a ces objets. Dans les autres cas, un message d'erreur est envoye.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## AAA5 [Mathematiques Elementaires]
    Operateur +

    |  1ere possibilite  |

    RESU1 = OBJET1 + OBJET2 | (LMOTS) ;
        | (MOT1)

    Objet :

    L'operateur + calcule la somme des objets OBJET1 et OBJET2.

    MOT1 permet de preciser le nom de la composante sur laquelle
    porte l'operation pour les objets de type EVOLUTION (ABSC ou ORDO)
    ou NUAGE (voir aussi remarques).

    Operations possibles :

   |  OBJET1  |  OBJET2  |  RESU1  |
   |-------------------------------------------------------------|
   |  ENTIER  |  ENTIER  |  ENTIER  |
   |  ENTIER  |  FLOTTANT  |  FLOTTANT  |
   |  ENTIER  |  LISTENTI  |  LISTENTI  |
   |  ENTIER  |  LISTREEL  |  LISTREEL  |
   |  ENTIER  |  EVOLUTIO  |  EVOLUTIO  |
   |  ENTIER  |  MCHAML  |  MCHAML  |
   |  ENTIER  |  NUAGE  |  NUAGE  |
   |-------------------|--------------------|--------------------|
   |  FLOTTANT  |  ENTIER  |  FLOTTANT  |
   |  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |
   |  FLOTTANT  |  LISTENTI  |  LISTREEL  |
   |  FLOTTANT  |  LISTREEL  |  LISTREEL  |
   |  FLOTTANT  |  EVOLUTIO  |  EVOLUTIO  |
   |  FLOTTANT  |  MCHAML  |  MCHAML  |
   |  FLOTTANT  |  NUAGE  |  NUAGE  |
   |-------------------|--------------------|--------------------|
   |  CHPOINT  |  CHPOINT  |  CHPOINT  |
   |  CHPOINT  |  FLOTTANT  |  CHPOINT  |
   |-------------------|--------------------|--------------------|
   |  MCHAML  |  MCHAML  |  MCHAML  |
   |  MCHAML  |  ENTIER  |  MCHAML  |
   |  MCHAML  |  FLOTTANT  |  MCHAML  |
   |-------------------|--------------------|--------------------|
   |  EVOLUTION  |  EVOLUTION  |  EVOLUTION  |
   |-------------------|--------------------|--------------------|
   |  LISTENTI  |  ENTIER  |  LISTENTI  |
   |  LISTENTI  |  FLOTTANT  |  LISTREEL  |
   |  LISTENTI  |  LISTENTI  |  LISTENTI  |
   |  LISTENTI  |  LISTREEL  |  LISTREEL  |
   |-------------------|--------------------|--------------------|
   |  LISTREEL  |  ENTIER  |  LISTREEL  |
   |  LISTREEL  |  FLOTTANT  |  LISTREEL  |
   |  LISTREEL  |  LISTREEL  |  LISTREEL  |
   |  LISTREEL  |  LISTENTI  |  LISTREEL  |
   |-------------------|--------------------|--------------------|
   |  EVOLUTIO  |  ENTIER  |  EVOLUTIO  |
   |  EVOLUTIO  |  FLOTTANT  |  EVOLUTIO  |
   |-------------------|--------------------|--------------------|
   |  NUAGE  |  ENRIER  |  NUAGE  |
   |  NUAGE  |  FLOTTANT  |  NUAGE  |
   |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |  TABLE 'VECTEUR'  |

    Remarque 1 :

    L'operateur + calcule la somme de deux objets de type TABLE
de sous-type 'VECTEUR'. Les tables doivent etre sommables, c'est a
dire les elements d'indice commun doivent etre de type ENTIER ou
FLOTTANT.

    Remarque 2 :

    Lorsque l'operateur + calcule la somme de deux objets EVOLUTION,
les deux objets, doivent etre de meme type, c'est-a-dire, soit reels,
soit complexes :

    a) Objets EVOLUTION reels :

    La somme est faite pour - OBJET1=f(x) defini sur le domaine D1
        - OBJET2=g(x) defini sur le domaine D2,
puis on calcule la somme sur le domaine commun (D1 et D2).

    b) Objets EVOLUTION complexes :

    Les deux objets doivent avoir les memes abscisses.
Chacun des deux objets peut etre soit "PREE PIMA" soit "MODU PHAS" .
L'objet RESULTAT aura le meme type que OBJET1.

    Remarque 3 :

    Lorsque l'operateur + calcule la somme d'un LIST(ENTI/REEL) avec un
ENTIER/FLOTTANT, l'ENTIER/FLOTTANT est additionne a tous les termes du
LIST(ENTI/REEL).

    Remarque 4 :

    Lorsque l'operateur + calcule la somme de deux MCHAML, pour les
sous zones elementaires similaires et pour les noms de composantes
identiques, il effectue la somme; sinon il realise l'adjonction.

    Dans le cas ou les MCHAML pointent sur des objets non FLOTTANT, on
garde l'objet de pointeur non nul. Si les deux pointeurs sont non nuls,
une addition est faite dans le cas des 'POINT', des 'LISTREEL' et des
'EVOLUTIO', en appliquant les regles de l'addition relatives a ces
objets. Dans les autres cas un message d'erreur est envoye.

    Dans le cas de l'addition faisant intervenir un FLOTTANT/ENTIER
et un MCHAML, il faut fournir un LISTMOTS (LMOTS)contenant la liste des
composantes sur lesquelles l'operation doit etre realisee, les autres
composantes seront alors inchangees. LMOTS est non necessaire si le
MCHAML contient une seule composante.

    Remarque 5 :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## AAA6 [Mathematiques Logique]
Operateur <
----------- <EG NEG

LOG1 = VAL1 < VAL2 ;

Objet :

L'operateur < compare deux nombres.

Commentaire :

VAL1, VAL2 : nombres de type ENTIER OU FLOTTANT

LOG1 : resultat de type LOGIQUE. a pour valeur VRAI si
        a pour valeur VRAI si VAL1 est plus petit que VAL2 et
        FAUX sinon.

## AAA7 [Mathematiques Logique]
Operateur <EG
------------- > NEG

LOG1 = VAL1 <EG VAL2 ;

Objet :

L'operateur <EG compare deux nombres.

Commentaire :

VAL1, VAL2 : nombres de type ENTIER ou FLOTTANT

LOG1 : resultat de type LOGIQUE
        a pour valeur VRAI si VAL1 est plus petit ou egal a
        VAL2 et FAUX sinon.

## AAA8 [Mathematiques Logique]
Operateur >
----------- <EG NEG

LOG1 = VAL1 > VAL2 ;

Objet :

L'operateur > compare deux nombres

Commentaire :

VAL1, VAL2 : nombres de type ENTIER ou FLOTTANT

LOG1 : resultat de type LOGIQUE
        a pour valeur VRAI si VAL1 est plus grand que VAL2 et
        FAUX sinon.

## AAA9 [Mathematiques Logique]
Operateur >EG
------------- < NEG

LOG1 = VAL1 >EG VAL2 ;

Objet :

L'operateur >EG compare deux nombres

Commentaire :

VAL1, VAL2 : nombres de type ENTIER ou FLOTTANT

LOG1 : resultat de type LOGIQUE
        a pour valeur VRAI si VAL1 est plus grand ou egal a
        VAL2 et FAUX sinon.

## ABS [Mathematiques Fonctions]
  RESU1 = 'ABS' OBJET1 (MOT1) ;

Operateur ABS

Objet :

L'operateur ABSOLU calcule la valeur absolue d'OBJET1.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  ENTIER  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTENTI  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ACCDCHI1 [Entree-Sortie Entree-Sortie] (proc)
Methode ACCDCHI1
--------------- OBJE DONCHI1

    OBJ1 = ACCDCHI1 MOT1 ;

    Objet

 La methode ACCDCHI1 permet d'acceder au contenu des objets de
 CLASSE DONCHI1.

    Commentaires

    voir DONCHI1

## ACCDCHI2 [Entree-Sortie Entree-Sortie] (proc)
Methode ACCDCHI2
--------------- DONCHI2

CHP1 = ACCDCHI2 MOT1 ;

   Objet

La methode ACCDCHI2 permet d'acceder au contenu des objets de
CLASSE DONCHI2.

   Commentaires

   voir DONCHI2

## ACCEVITE [Mathematiques Traitement] (proc)
Procedure ACCEVITE

EVOL1_V=FREQPERI EVOL2_A MOT1;

objet:

effectue la transformation d'un spectre de reponse d'acceleration
EVOL2_A (comportant N courbes) en frequence ou periode en un
spectre de reponse en vitesse (comportant N courbes) en frequence
ou en periode selon MOT1 valant 'FREQ'(uence) ou 'PERI'(ode).

## ACIER [Mecanique Modele] (proc)
    Procedure ACIER
    --------------- MATR

    MAT1 = ACIER 'A316L' MODL1 ;

    Objet :

    Cette procedure permet de creer un champ de materiau ayant les pro-
prietes, en unites SI, de l'acier 316L.

    Commentaire :

    MODL1 : objet modele (type MMODEL)

    MAT1 : description du materiau "acier 316L" (type MCHAML, sous-
        type CARACTERISTIQUES)

## ACOH [Mathematiques Fonctions]
  RESU1 = 'ACOH' OBJET1 (MOT1) ;

Operateur ACOH
-------------- ACOS ASIN ATG

Objet :

L'operateur ACOH calcule l'arc cosinus hyperbolique de l'objet
OBJET1.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ACOS [Mathematiques Fonctions]
  RESU1 = 'ACOS' OBJET1 (MOT1) ;

Operateur ACOS
-------------- ASIN ATG

Objet :

L'operateur ACOS (arc-cosinus) calcule l'arc-cosinus d'OBJET1.
Le resultat est en degres, dans l'intervalle [0 ; 180].

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ACQU [Entree-Sortie Entree-Sortie]
    Operateur ACQUERIR
    ------------------ LIRE

    |  1ere possibilite  |

    ACQUERIR OBJET1*TYP1 (N1) ( OBJET2*TYP2 ....) ;

        OBJETi=ENTIER,FLOTTANT,MOT
        LISTENTI,LISTREEL

    Objet :

    Insere dans un ensemble de donnees de CASTEM 2000, l'operateur
ACQUERIR permet d'acquerir des objets OBJET1 (OBJET2 . . .) sur
un fichier d'unite logique N2 definie par :

        OPTION ACQUERIR N2 ;

    Remarque 1 :

    Les types possibles des objets a acquerir sont : - ENTIER
        - FLOTTANT
        - MOT
        - LISTENTI
        - LISTREEL

    Il est possible d'omettre le type de l'objet a acquerir;
dans ce cas ,il ne faut pas mettre le * .

    Remarque 2 :

    Dans le cas d'objets de type LISTENTI ou LISTREEL il est necessaire
de fournir le nombre de valeurs a lire, N1 (type ENTIER).

    Remarque 3 :

    Le fichier doit etre compose d'enregistrements de 256 caracteres.
    Les objets de type MOT lus ont 72 caracteres au maximum.

     Exemple :

     Le fichier de lecture etant le suivant :

     1 ' est plus petit que ' 2
     2 fois 3 egale 6
     12 34 56 78 90

la sequence de lecture suivante :

        ACQUERIR I*ENTIER MM*MOT J*FLOTTANT;
        ACQUERIR K*ENTIER ;
        ACQUERIR LL*LISTENTI 5 ;

conduit a : I =1
        MM= est plus petit que
        J =2
        K =2
        LL= 12 34 56 78 90

    |  2eme possibilite  |

    MOT1 = 'ACQU' 'BRUT' ;

    Objet :

    L'operateur ACQUERIR permet de lire un enregistrement sur une unite
    logique definie prealablement par la directive :

        'OPTION' 'ACQUERIR' N2 ;
        ou 'OPTION' 'ACQUERIR' MOT2 ;

    avec :
    N2 : objet de type ENTIER, numero d'unite logique
    MOT2 : objet de type MOT, nom de fichier

    Le resultat de l'acquisition est un objet MOT1 de type MOT
    (512 caracteres maxi).

## ACT3 [Fluides Resolution]
    Operateur ACT3

     CHPO = ACT3 CHPO2 CHPO1 CHPO0 CHFO3 CHFO2 CHFO1 CHFO0;

    Objet :

    L'operateur ACT3 sert a accelerer la convergence de calculs
non lineaires en mecanique.

    Methode :

   A partir de 3 increments de forces correctrices et des 4
desequilibres correspondant, ACT3 evalue la correction de force
correctrice permettant de minimiser le desequilibre en resolvant
le probleme tangent sur sa restriction au sous-espace de dimension
3 defini par les champs en entree.

## ACTI [Mathematiques Autres]
    Operateur ACTIVE

     CH1  =  ACTIVE  | GEOM  CH2  CH3  CH4  ( FLOT1 )  (MOT1) ;
        |
        | SECA  CHPO1 CHPO2 CHPO3 CHPO4 ;

    Objet :

    L'operateur ACTIVE sert a accelerer la convergence de calculs
non lineaires .

    Commentaire :

    Deux types d'acceleration sont disponibles :

    a) GEOMETRIQUE :

        A partir de 3 champs successifs CH2, CH3, CH4
        on fabrique le champ CH1, en supposant
        que ces 3 champs sont en progression geometrique.
        S'il s'agit de CHPOINTs , on accelere toutes les
        composantes .
        S'il s'agit de MCHAMLs on n'accelere que la composante
        de nom MOT1 (ce nom est inutile, si le champ
        n'a qu'une composante ).
        On n'accelere que si le taux de convergence est inferieur a
        FLOT1, egal a 0.98, par defaut, (type FLOTTANT).

    b) SECANTE :

        A partir de 4 champs ( type CHPOINT ) qui sont, dans l'ordre :

        CHPO1 : increment de deplacement a la premiere iteration
        CHPO2 : increment de deplacement a l'iteration n-1
        CHPO3 : increment de deplacement a l'iteration n
        CHPO4 : increment de forces correctrices non lineaires a
        l'iteration n

    on calcule un vecteur CHAMP1 ( type CHPOINT ) qui est une estimation
    acceleree de CHPO3.

## ACTI3 [Mathematiques Autres] (proc)
    Procedure ACTI3

    Objet :

   Cette procedure pourrait etre utilisee par la procedure INCREME.
En fait celle ci utilise l'operateur ACT3 qui a exactement le meme
role.

   A partir de 4 champs de deplacements et des 4 champs d'increments
de forces correctrices associes, ACTI3 evalue le champs d'increments
de deplacement permettant de resoudre le probleme sur la restriction
de l'application tangente au sous-espace de dimension 3 defini par
les champs en entree.

## ACTUSAT1 [Mathematiques Autres]
   Procedure ACTUSAT1

   CHPO1 CHPO2 = ACTUSAT1 CHPO3 CHPO4 ;

   Objet :

   Cette procedure effectue le calcul de la permeabilite (chpo2)
et de la capapcite hydraulique (chpo1) a partir des charges
actuelle (chpo4) et precedente (chpo3) . Les point du
  support des champs sont des points faces.
  Cette procedure est a utiliser a partir de la procedure DARCYSAT
  Elle correspond a la methode 1

## ACTUSAT2 [Mathematiques Autres]
   Procedure ACTUSAT2

   CHPO1 CHPO2 = ACTUSAT2 CHPO3 CHPO4 ;

   Objet :

   Cette procedure effectue le calcul de la permeabilite (chpo2)
et de la capapcite hydraulique (chpo1) a partir des charges
actuelle (chpo4) et precedente (chpo3) . Les point du
  support des champs sont des points centres.
  Cette procedure est a utiliser a partir de la procedure DARCYSAT
  Elle correspond a la methode 2.

## ACTUSAT3 [Mathematiques Autres]
   Procedure ACTUSAT3

   CHPO1 CHPO2 = ACTUSAT3 CHPO3 CHPO4 ;

   Objet :

   Cette procedure effectue le calcul de la permeabilite (chpo2)
et de la capapcite hydraulique (chpo1) a partir des charges
actuelle (chpo4) et precedente (chpo3) . Les point du
  support des champs sont des points faces.
  Cette procedure est a utiliser a partir de la procedure DARCYSAT
  Elle correspond a la methode 3

## ADAPTE [—] (proc)
Procedure ADAPTE

Objet :

    La procedure ADAPTE permet d'adapter le maillage d'un modele
evoluant au cours du temps en fonction d'un autre maillage, a priori
moins fin. ADAPTE est notamment utilise dans le cas de la simulation
du soudage ou de la fabrication additive pour deraffiner le modele
au-dela d'une certaine distance du point d'apport de matiere.

    Le maillage du modele et celui fourni en argument doivent etre
hierarchiques : les noeuds de l'un doivent etre communs aux deux.

    Le modele a adapter est decrit par un CHARGEMENT de nom MODE.
L'adaptation est realisee en parcourant une trajectoire (celle du
procede). Celle-ci est egalement decrite par un CHARGEMENT.

Syntaxe :

CHAR2 LREE1 = ADAPTE 'MAIL' GEO1 CHAR1 'DIST' FLOT1 ...

        ... ('TRAJ' FLOT2) ('MINI' FLOT3) ;

Entrees :

GEO1 : objet MAILLAGE, dont les mailles sont subsitutuees a celles
        du maillage decrit dans le CHARGEMENT.

CHAR1 : objet CHARGEMENT, contenant :
        - un chargement de nom MODE, decrivant l'evolution temporelle
        du modele a adapter ;
        - un chargement de nom TRAJ, decrivant l'evolution temporelle
        d'un point le long d'une trajectoire.

FLOT1 : objet FLOTTANT, distance d'adaptation separant le point de la
        trajectoire a un instant donne et la partie adaptee.

FLOT2 : objet FLOTTANT, distance parcourue sur la trajectoire avant
        toute nouvelle adaptation. Permet de ne pas adapter le
        maillage systematiquement.

FLOT3 : objet FLOTTANT, distance minimale en-dessous de laquelle
        l'adaptation est systematiquement realisee. Sert a retirer
        les elements de la partie adaptee pour les remplacer par le
        maillage fin initial lorsque la trajectoire revient a proxi-
        -mite d'une partie adaptee (FLOT3 est pris egal FLOT1 s'il
        lui est superieur).

Sorties :

CHAR2 : objet CHARGEMENT, contenant :
        - un chargement, de nom MAIL, contenant le maillage adapte
        au cours du temps ;
        - un chargement, de nom BLOD, BLOM ou BLOT, contenant des
        relations (RIGIDITE) entre les inconnues nodales a l'inter-
        -face des parties non conformes du maillage adapte assurant
        la continuite de la solution.

LREE1 : objet LISTREEL, liste des instants ou le maillage est adapte.

Remarque : ADAPTE est disponible uniquement en dimension 3.

## ADET [Langage Objets]
Operateur ADET

  RESU1 =  ADET ('NOUV')  MO1 |  CHAR1  TI  |  ;
        ( CHAM1)  |  MOT1  XI  |
        |  CHAM2  |
        |  TABL1  |

Objet :

L'operateur ADET cree un champ par element s'appuyant sur
le modele MO1 si le mot NOUV est employe. Sinon il complete a
partir du champ par element CHAM1.

  Commentaire :

Le champ par element cree est sur les points de gauss des contraintes.

On peut utiliser autant de fois que necessaire les donnees
suivantes :

    - CHAR1 TI : a partir de l'objet chargement CHAR1 et pour
        le temps TI il fabrique tous les champs
        dont le type est autre que :
        MECA DIMP TIMP TERA TECO Q DEFI REAC
        CIMP UIMP FORC MODE MATE BLOD BLOM BLOT
    - MOT1 XI : a partir du mot MOT1 ( de 4 lettres au plus)
        et du flottant XI il cree un champ par element
        constant de nom composante MOT1
    - CHAM2 : addition du champ par element CHAM2
    - TABL1 : a partir d'une table les champs sous les indices
        'DEPLACEMENTS' 'CONTRAINTES' 'VARIABLES_INTERNES'
        'TEMPERATURES' 'PROPORTIONS_PHASE' sont inclus
        dans le chaump par element.

  RESU1 : objet de type MCHAML (champ par element)

## ADVE [Fluides Modele]
Operateur ADVE
-------------- MODE, MATE

ADV1 = ADVE MOD1 MAT1 ('SYMM') ;

Description :

L'operateur ADVE construit la matrice de rigidite du type :

  (ADV1)ij = Ni (V . grad(Nj)) dx ,

V etant un champ vectoriel a une ou deux ou trois composantes. Cette
matrice est non symetrique et correspond a la discretisation du
transport d'un scalaire par un champ de vitesse V.

 - THERMIQUE v.grad(T)
 - DIFFUSION v.grac(C) (Les inconnues primales et duales pour
        la DIFFUSION sont contenues dans MOD1)

Contenu :

MOD1 : MMODEL de type THERMIQUE ISOTROPE ADVECTION
MAT1 : MCHAML de type 'CARACTERISTIQUES' (voir MATE)
ADV1 : Matrice de 'RIGIDITE' non symetrique

Notes :

  1 - Si le mot cle 'SYMM' est present, le resultat sera la partie
      symetrique de la matrice originale, c-a-d :

     (ADV1)ij = [Ni (V . grad(Nj)) + Nj (V . grad(Ni))]/2 dx

      Dans ce cas, ADV1 est symetrique.

## AFCO [Post-traitement Affichage]
    Operateur AFCO

    GEO1 = AFCO GEO2 ;

    Objet :

    Cet operateur cree un objet GEO1 (type MAILLAGE) identique a l'objet
GEO2 (type MAILLAGE) mais chaque sous-objet a une couleur specifique.

    Remarque :

    Les couleurs sont attribuees comme suit :

        BLEU : SEG2,TRI3,CUB8,TET4,LIA3
        ROUGE : QUA4,PRI6,PYR5,RAC2,LIA4
        ROSE : SEG3,TRI6,CU20,TE10,LIA6
        VERT : QUA8,PR15,PY13,RAC3,LIA8
        TURQUOISE : TRI4,QUA5
        JAUNE : TRI7,QUA9
        BLANC : MULT

## AFFI [Maillage Manipulation]
    Operateur AFFINITE

    GEO2 = GEO1 AFFI FLOT1 POIN1 POIN2 ;

    Objet :

    L'operateur AFFINITE construit un objet par affinite geometrique
    d'un rapport donne suivant une direction precisee par deux points.

    Commentaire :

    GEO1 : geometrie initiale (type MAILLAGE)

    POIN1, POIN2 : points definissant la direction suivant laquelle
        on opere l'affinite (type POINT). Le point POIN1
        est conserve.

    FLOT1 : rapport de l'affinite (type FLOTTANT)

    GEO2 : geometrie resultant de l'affinite (type MAILLAGE)

    Remarques :

    1) Cet operateur n'est pas utilisable en DIMEnsion 1.

    2) GEO1 GEO2 ... GEOn AFFI FLOT1 POIN1 POIN2 ;

    L'operation est effectuee sur les n objets simultanement et a
n resultats :

       NC1 NC2 NC3 NC4 NS = C1 C2 C3 C4 S AFFI 0.2 (0 0) (10 0) ;

## AFFICHE [Post-traitement Affichage] (proc)
    Procedure AFFICHE
    ----------------- TRAC

    AFFICHE RIG1 CHPO1 GEO1 FLOT1 FLOT2 ;

    Objet :

    Cette procedure affiche sur l'ecran la deformee d'une structure
soumise a un chargement donne .

    Commentaire :

    RIG1 : matrice de rigidite de la structure (type RIGIDITE)

    CHPO1 : chargement de la structure (type CHPOINT)

    GEO1 : maillage de la structure (type MAILLAGE)

    FLOT1 : coefficient d'amplification de la deformee (type FLOTTANT)

    FLOT2 : coefficient d'amplification des vecteurs representatifs
        du chargement (type FLOTTANT)

    Remarque :

    Les operandes doivent etre entres dans l'ordre indique dans la
syntaxe.

## AFT [Mecanique Dynamique] (proc)
  Procedure AFT

  Objet :

 Cette procedure est utilisee par la procedure CONTINU.

        Frequence  |  Temps
        |
0. Entree : deplacement exprime  |  1. Recombine le deplacement
sous forme de serie de Fourier  |
        |  u(t)  =  U_0
U = (U_0 U_1 V_1 ... U_H V_H) =====> + \sum_{k=1..H} cos kwt U_k
        |  + \sum_{k=1..H} sin kwt V_k
        |
        |  ||
----------------------------------|--------------- || ---------------
        |  \/
        |
3. Sortie : forces non-lineaire  |  2. Calcul de la force non-
        <===== lineaire via CHARMECA
Fnl = (Fnl_0 ... Fnl_k Gnl_k)  |  .
        |  fnl(t) = fnl(u,u)
        |

## AFT1 [Mecanique Dynamique] (proc)
 Procedure AFT1

 Objet :

Cette procedure est utilisee par la procedure AFT.
Elle permet de calculer le deplacement temporel
a partir de son expresion dans le domaine frequentiel.

## AFT2 [Mecanique Dynamique] (proc)
 Procedure AFT2

 Objet :

Cette procedure est utilisee par la procedure AFT.
Elle permet de calculer la transformee de Fourier de la force
a partir de son expression dans le domaine temporel.

## AIDE [Langage Base]
    Operateur AIDE

      LISMO1 = AIDE MOT1 ;

FRAN====**************************************************
MOTS-CLES : INDEX MOT-CLE RECHERCHE
DICTIONNAIRE
FRAN====*************************************************
ANGL====*****************************************************
KEY-WORDS : INDEX KEY-WORDS SEARCH DICTIONNARY
ANGL====***************************************************

    Objet :

    L'operateur AIDE cherche dans la notice tous les operateurs
ayant la chaine MOT1 dans sa liste de mots-cles.
    Une impression de la liste a lieu si la liste n'est pas vide,
et un objet de type LISTMOTS est cree.
    MOT1 doit etre une chaine en majuscules.

## AJU1 [Fantome]
Operateur AJU1

Objet :

Cet operateur est utilise par la procedure AJUSTE

## AJU2 [Fantome]
Operateur AJU2

Objet :

Cet operateur est utilise par la procedure AJUSTE

## AJUSTE [Mathematiques Fonctions] (proc)
procedure AJUSTE

Q P = AJUSTE TAB1 ;

        TAB1.'X' (TAB1.'PMIN')
        TAB1.'F' (TAB1.'PMAX')
        TAB1.'K' (TAB1.'PRECISION')
        TAB1.'L' (TAB1.'MXTER')
       (TAB1.'POIDS') (TAB1.'MESSAGES')
        (TAB1.'IMPRESSION')

Objet :

  Soit une fonction F(x,y,z...,p1,..,pk) mise sous la forme :

   F(x,p) = q1 * f1(x,y,z,.,p1,..,pk)
        + q2 * f2(x,y,z,.,p1,..,pk)
        + ...
        + ql * fl(x,y,z,.,p1,..,pk)

        + g(x,y,z,.,p1,..,pk)

   qi (i=1,l) sont les parametres lineaires.
   pj (j=1,k) sont les parametres non lineaires.

   La procedure ajuste ces differents parametres afin que la
   fonction passe au mieux dans une serie de N couples

        ( (x,y,z,...) ; Fdi(x,y,z,..) )

   fournie par l' utilisateur.

   En fait, on cherche a minimiser la fonction :

       G = [ (poids(i) * ( F(x,p) - Fdi(x,y,z..) )**2 ]
        somme sur i=1,N

Donnees :

   TAB1.'X' : TABLE indicee par des entiers i=1,N qui contient
        le(s) LISTREEL(s) x,y,z,.....

   TAB1.'F' : valeurs a caler F(x,y,z...) (LISTREEL).

   TAB1.'K' : nombre de parametres non lineaires (ENTIER).

   TAB1.'L' : nombre de parametres lineaires (ENTIER).

   TAB1.'MESSAGES' : niveau de message (defaut=0 : rien)
        1 -> resultats, 2 -> iterations

   TAB1.'IMPRESSION' : frequence des impressions si MESSAGES=2
        (type ENTIER, defaut : toutes les 20 iterations).

   TAB1.'PMIN' : valeurs minimum de p
        (LISTREEL, obligatoire si K > 0).

   TAB1.'PMAX' : valeurs maximum de p
        (LISTREEL, obligatoire si K > 0).

   TAB1.'PRECISION' : (LISTREEL, utile si K>0) :
        critere de precision de convergence pour les K
        parametres non lineaires (defaut 1.e-7)

   TAB1.'MXTER' : nombre maximum d'iterations
        (ENTIER, utile si K>1, defaut=100).

   TAB1.'POIDS' : valeurs de poids a affecter a chacun des points de
        mesure fournis. (LISTREEL, defaut=1.)

   TAB1.'NOM_FCT': nom de la procedure qui calcule les fi(x,p) et g(x,p)
        (MOT, defaut='FCT').

   TAB1.'NOM_DERI': nom de la procedure qui calcule les derivees de
        fi(x,p) et g(x,p) par rapport aux p_j
        (MOT, defaut='DERI').

 Sortie :
   Q et P sont des LISTREELs contenant les parametres qi et pi.

 Utilisation :

   Deux procedures sont a creer par l'utilisateur.

  - Procedure FCT:

   Son but est de calculer la fonction a ajuster connaissant les
   valeurs des abscisses x,y,. et ceci pour un jeu de parametres
   p donne. En fait, on demande de calculer les fonctions
   f1,f2,...,fl et la fonction g.
   Pour chaque fonction fi, la procedure calcule autant de
   valeurs qu'il y a de valeurs dans x,y,z .. Le resultat doit
   etre mis sous la forme d'un objet TABLE.

   tbfonc = FCT xtab p;

   En argument FCT recevra la table TAB1.'X', ainsi que le
   LISTREEL p qui contient les valeurs courantes de P.

   La table doit se mettre sous la forme suivante:

        tbfonc.'F'.i = listreel des valeurs de fi

        tbfonc.'G' = listreel des valeurs de g

   Les parametres lineaires qi n'ont pas a etre ecrit.

  - Procedure DERI:

   Elle construit une table de listreels contenant les valeurs des
   fonctions f1,f2,...,fl et g derivees par rapport aux parametres
   non lineaires pj pour chaque valeur de x,y,z.. et de p.

   tbderi = DERI xtab p;

   En argument DERI recevra la table TAB1.'X', ainsi que le
   LISTREEL p.

   La table doit etre cree de la façon suivante:

        tbderi.'F'. j . i = listreel des valeurs de dfi/dpj

        tbderi.'G'. j = listreel des valeurs de dg/dpj

 Remarques :

  - Les abscisses etant dans un LISTRÉEL, il faut que les
    constantes soient exprimees, dans les procedures FCT et DERI,
    sous forme de LISTRÉEL.

    ex: f1(x)=x+1 donne f1(x)=x+(prog N*1);
        N etant la dimension de x.

  - Attention, les fonctions sinusoidales ont pour operandes des
    degres.

  - on peut creer des procedures de nom differents de ceux par
    defaut en completant les indices 'NOM_FCT' et 'NOM_DERI'. Bien
    faire preceder le nom de la procedure par l'operateur 'MOT'.

  - exemples dans : ajuste1.dgibi ajuste2.dgibi identifi.dgibi

## ALEA [Mathematiques Statistiques]
   Operateur ALEA

   OBJ1 = 'ALEA' 'BANDES_TOURNANTES' | MODE1  (MOT1)
        | MAIL1
        'EXPO' 'SIGMA' FLOT1 ('MOYENNE' FLOT2)
        |  'LAMBDA' FLOT3
        |  'LAMBDA1' FLOT4 (VEC4)
        ('LAMBDA2' FLOT5 (VEC5))
        ('LAMBDA3' FLOT6 (VEC6))

      Objet :

      Generation d'un champ scalaire aleatoire gaussien stationnaire
      (de moyenne, ecart-type 'ET' fonction de correlation
      constants) par la methode des bandes tournantes.
      Ce champ obeit a une loi de covariance exponentielle.
      La matrice de covariance a pour expression :

      Cij = s² * EXP ( - (d1²/l1² + d2²/l2² + d3²/l3²) ** .5 )

      ou s est l'ecart-type,
        (d1,d2,d3) sont les coordonnees du vecteur liant
        Pi et Pj deux points du maillage,
        (l1,l2,l3) les longueurs de correlation dans les 3 directions.

      Commentaires :

  'BANDES_TOURNANTES'
        : mot-cle indiquant que l'on utilise la methode des bandes
        tournantes (la seule methode disponible par cet
        operateur pour l'instant ; voir 'DCOV' et 'BRUI' pour la
        methode de decomposition matricielle).

     MODE1 : Modele sur lequel s'appuie le champ resultat
        (type MMODEL), pour obtenir un champ par element en
        sortie.

      MOT1 : mot-clef facultatif valant 'NOEUD','GRAVITE','RIGIDITE',
        'MASSE','STRESSES'
        indiquant quels points supports prendre en compte dans la
        generation du champ (defaut = 'NOEUD').
        Les options 'RIGIDITE','MASSE','STRESSES' reclament un
        modele de mecanique ; l'option 'GRAVITE' reclame un
        modele NAVIER-STOKES ou DARCY.

     MAIL1 : Maillage sur lequel s'appuie le champ resultat (type
        MAILLAGE), pour obtenir un champ par point en sortie.

    'EXPO' : mot-cle indiquant que la loi de covariance est
        exponentielle.

   'SIGMA' : mot-cle suivi de :

     FLOT1 : ecart-type du champ a engendrer (type FLOTTANT).

 'MOYENNE' : mot-cle optionnel suivi de :

     FLOT2 : valeur de la moyenne du champ aleatoire (type FLOTTANT)
        par defaut = 0.

  'LAMBDA' : mot-cle pour une correlation isotrope, suivi de :

     FLOT3 : longueur de correlation isotrope (type FLOTTANT).

 'LAMBDA1' : mots-cles pour une structure de correlation anisotrope.
('LAMBDA2') Il sont autant que la dimension de la structure de
('LAMBDA3') correlation, et sont suivis respectivement de :

     FLOT4 : longueurs de correlation (type FLOTTANT) dans les 3
    (FLOT5)
    (FLOT6) directions principales.

    (VEC4) : directions optionnelles des axes principaux
    (VEC5) de correlation 1, 2, et 3 respectivement (type POINT).
    (VEC6) Ils doivent etre non nuls et orthogonaux.
        Par defaut, ce sont les axes (1 0 0), (0 1 0) et (0 0 1).

      OBJ1 : champ resultat (type CHPOINT ou MCHAML selon que
        l'on donne un maillage ou un modele en entree),
        nature 'DIFFUS' (si c'est un champ-point), une
        composante 'SCAL'.

      Remarques :

        1. Le resultat obtenu est d'autant meilleure qualite que le
        maillage donne en entree est regulier et respecte
        la structure d'anisotropie eventuelle de la correlation.
        Aucune verification concernant cette regularite n'est
        effectuee.

## AMOR [Mecanique Modele]
    Operateur AMOR

    Objet :

    L'operateur AMOR calcule des matrices d'amortissement dans
differents cas :

    | Cas 1 : amortissement modal |

    AMOR1 = AMOR  | BASE1 |  LREEL1 ;
        | TAB1  |

    L'operateur AMOR construit une matrice diagonale d'amortissements
modaux. Elle affecte a chaque mode de base un amortissement reduit.

    Commentaire :

  AMOR1 : matrice d'amortissement (type RIGIDITE, sous-type
        AMORTISSEMENT)

  BASE1 : base modale (type BASEMODA)

  TAB1 : objet TABLE definissant les modes, les pseudo-modes, ...
        - de sous-type BASE_MODALE, ou
        - de sous-type ENSEMBLE_DE_BASES.

  LREEL1 : coefficients des amortissements modaux reduits (en %)
        (type LISTREEL)

    Dans le cas d'une structure unique, le n-ieme coefficient de la
liste de reels correspond au n-ieme mode de la base.
    Dans le cas de plusieurs structures, la liste de reels sera donnee
par structure et par mode.

    | Cas 2 : frontieres absorbantes |

     AMOR1 = AMOR MODL1 GEO1 MAT1 ;

    L'operateur AMOR calcule la matrice d'amortissement associee a
la frontiere d'un maillage, dans le cas d'elements solides ou fluides,
en 2D ou en 3D. La formulation correspond a la frontiere visqueuse de
Lysmer et Kuhlemeyer (1969).

    Commentaire :

  AMOR1 : matrice d'amortissement (type RIGIDITE)

  MODL1 : modele du sol ou du fluide (type MMODEL)

  GEO1 : maillage de la frontiere (type MAILLAGE)

  MAT1 : champ de caracteristiques materiau pour le sol ou le fluide
        (type MCHAML)

    | Cas 3 : amortissement materiel visqueux |

     AMOR1 = AMOR MODL1 MAT1 ;

    L'operateur AMOR calcule la matrice d'amortissement visqueux
    defini par le parametre de viscosite du materiau 'VISQ'.
    dans le cas d'elements solides massifs, barres,
    poutres (POUT, TIMO et TIMO modele SECTION) et coques.
    La matrice d'amortissement est calculee de façon similaire a la raideur.

    Commentaire :

  AMOR1 : matrice d'amortissement (type RIGIDITE)

  MODL1 : modele (type MMODEL)

  MAT1 : champ de caracteristiques materiau
        (type MCHAML)

## ANALYSER [Mathematiques Traitement] (proc)
Procedure ANALYSER
------------------ RECOMPOM

N1 EVOL1_DECO EVOL2_RESI=ANALYSER EVOL3_SIGN (TAB1);

Objet :

La procedure ANALYSER permet d'effectuer l'analyse en ondelettes
orthogonales d'un signal donne sur une grille uniforme de longueur
quelconque EVOL3_SIGN (dont on ne traite que la premiere courbe)
et suivant les options de TAB1. N1 indique le nombre de niveaux
d'analyse effectif, EVOL1_DECO (contenant N1 courbes) contient la
decomposition (des basses vers les hautes "frequences") et
EVOL2_RESI (contenant une courbes) le residu de EVOL3_SIGN.

Remarque:

La procedure ANALYSER utilise la procedure MULTIDEC.

Options :

Le contenu significatif de TAB1 est le suivant:

indice type objet commentaires
        pointe

 PUIS ENTIER PUIS permet d'imposer le nombre de points
        d'analyse (NPA=2**PUIS+1). Par defaut tout
        le signal est traite, eventuellement complete
        par des zero.

 LDEC ENTIER permet de specifier le nombre de niveaux de
        decomposition souhaite. Par defaut c'est le
        maximum.

 BORD MOT specifie les conditions de bord pour les
        calculs de correlation: 'SYME'(trique) ou
        'PADD'(ing) de zero. Le defaut est 'SYME'.

 TYPE MOT permet de specifier le type d'ondelette
        orthogonale: 'MALL'(at) ou 'DAUB'(echie).
        Le defaut est 'MALL'.

## ANIME [Post-traitement Affichage] (proc)
    Procedure ANIME

    DEFO1 = ANIME N1 GEO1 CHPO1 FLOT1 (CHPO2 FLOT2 (COUL1))...
        ... | CHPO3
        | CHEL MODE  ;

;

    Objet :

    La procedure ANIME construit un objet de type DEFORME propre a etre
visualise en animation a l'aide des options ANIME et OSCIL de l'
operateur TRAC.

    Commentaire :

    N1 : nombre de deformees (nombre d'images) a creer (type ENTIER)

    GEO1 : maillage a representer (type MAILLAGE)

    CHPO1 : champ de deplacement a representer (type CHPOINT)

    FLOT1 : coefficient d'amplification du champ de deplacement
        (type FLOTTANT)

    CHPO2 : champ de vecteurs forces eventuel a tracer (type CHPOINT)

    FLOT2 : coefficient d'amplification du champ de forces
        (type FLOTTANT)

    COUL1 : couleur du champ de forces (type MOT)

    CHPO3 : champ de scalaire dont on desire voir les isovaleurs.
        (type CHPOINT)

    CHEL : champ de scalaire dont on desire voir les isovaleurs.
        (type MCHAML)

    MODE : modele associe au precedent

## ANIMGKS [Post-traitement Affichage] (proc)
    Procedure ANIMGKS

    Objet :

    Cette procedure sert a faire de l'animation avec un systeme graphique
GKS. Contacter P. VERPEAUX pour son utilisation.

## ANLIMTRE [Fluides Resolution] (proc)
  Procedure ANLIMTRE

  IENT1 = ALIMTRE TAB1 ;

        TAB1.'MESH' .'PBLOQ' .'PSOLL' .'VSOLL'
        .'CONLIM' .'REACMAX'

  Objet :

  Cette procedure est une procedure d'analyse limite pour des
  reseaux de barres articulees par la methode du Simplex.

  Commentaire :

Soit un reseau de barres articulees formant le maillage MESH et
bloque en deplacement sur l'ensemble de points PBLOQ. On se propose
de trouver le maximum de la charge placee au point PSOLL dans la
direction VSOLL sachant que la contrainte EFFX dans chaque barre
est soumise a la contrainte |EFFX| <EG CONLIM

  IENT1 : indice resultat (type ENTIER), qui vaut 0 en cas
        de fonctionnement correct

  TAB1 : Objet de type TABLE.

        En entree, TAB1 doit contenir :

       indice type objet commentaires
        pointe

     MESH MAILLAGE le maillage

     PBLOQ MAILLAGE ensemble de points bloques en
        deplacement
     PSOLL POINT point charge

     VSOLL POINT direction de la charge

     CONLIM FLOTTANT valeur de la contrainte limite

     REACMAX FLOTTANT valeur de la reaction d'appui
        limite
        En sortie, TAB1 contient :

       indice type objet commentaires
        pointe

     CHARLIM FLOTTANT la charge limite

     MCHPV MCHAML les parametres internes

     CHPPB CHPOINT les bloquages

     CHPPS CHPOINT les sollicitations

## ANNO [Post-traitement Affichage]
 Operateur ANNO

 Objet :

 L'opérateur ANNO permet de créer un objet ANNOTATION. Ces objets
 peuvent etre regroupes a l'aide de l'operateur ET et transmis
 a TRAC pour enrichir l'affichage graphique.

 Plusieurs syntaxes sont disponibles pour creer differents types
 d'annotations :

 Syntaxes :

 1) Affichage d'une legende discrete (categories)

    ANNO1 = ANNO 'CATE' COUL1 TITR1 ;

 2) Affichage d'etiquettes localisees

    ANNO1 = ANNO 'ETIQ' POIN1 (COUL1) (POSI1) (DIST1) (LIEN1) MSG1 ;

Commentaires :

1) Une legende de type "categorie" est un rectangle de couleur COUL1
   couple a un texte TITR1 affiche sur le bandeau de droite, a la
   place des isovaleurs.

2) Une etiquette est un message MSG1 affiche en un point POIN1 du
   domaine. La couleur COUL1 peut etre specifiee, ainsi que la
   position de l'etiquette par rapport a POIN1 (mot-cle 'SO', 'S',
   'SE', 'O', 'C', 'E', 'NO', 'N', 'NE') et sa distance DIST1. Enfin,
   LIEN1 (type LOGIQUE) indique s'il faut dessiner une ligne entre
   POIN1 et l'etiquette (par defaut : VRAI)

## ANNOIMP [Maillage Autres] (proc)
Procedure ANNOIMP

GEO1 = ANNOIMP N1 FLOT1 FLOT2 HAUT1 FLOT3 FLOT4 ;

Objet :

Cette procedure genere un maillage d'anneau imparfait d'axe Oz.

Commentaire :

Le rayon de l'anneau varie suivant la loi suivante :

RAY1 = FLOT2 + FLOT3 * cos(FLOT1 * FLOT4)

Les coordonnees de la base sont donnees par :

      X1 = FLOT2 * cos(FLOT4)
      Y1 = FLOT2 * sin(FLOT4)
      Z1 = 0

HAUT1 : hauteur de l'anneau (type FLOTTANT)

FLOT1 : mode (type FLOTTANT)

FLOT2 : rayon (type FLOTTANT)

FLOT3 : defaut (type FLOTTANT)

FLOT4 : angle par rapport a Oz (type FLOTTANT)

N1 : nombre de segments sur la base de l'anneau (type ENTIER)

## ANNU [Langage Base]
Operateur ANNU

Cet operateur est a usage interne de Gibiane

## ANTI [Mecanique Limites]
    Operateur ANTI :
    -------------- RELA RESO

   RIG1 = ANTI ('DEPL') ('ROTA') POIN1 POIN2 (POIN3 si 3D) GEO1 (FLOT1)

    Objet :

   L'operateur ANTISYMETRIE permet d'imposer des conditions aux limites
de type antisymetrique sur les d.d.l. en DEPLACEMENT et/ou en ROTATION.

    Commentaire :

    Cet operateur cree l'objet RIG1 de type RIGIDITE associe aux
conditions aux limites. Il faudra l'adjoindre a la rigidite de la
structure calculee.

    POIN1,POIN2 : points qui definissent l'AXE d'ANTISYMETRIE
        en 2D (type POINT)

    POIN1,POIN2,POIN3 : points qui definissent le PLAN d'ANTISYMETRIE
        en 3D (type POINT)

    GEO1 : objet sur lequel on impose les conditions aux
        limites (type MAILLAGE)

    FLOT1 : valeur du critere de selection des points
        appartenant a l'axe/au plan d'antisymetrie
        (type FLOTTANT).
        Par defaut on utilise le 1/10 de la densite
        courante.
        FLOT1 est donc NECESSAIRE lorsqu'aucune densite
        n'a ete definie precedemment .

    'DEPL' : Mot-cle pour creer des conditions aux limites,
        de type ANTISYMETRIE sur les d.d.l. de depla-
        cement.

    'ROTA' : Mot-cle pour creer des conditions aux limites,
        de type ANTISYMETRIE sur les d.d.l. de rotation.

L'une au moins de ces deux dernieres specifications est OBLIGATOIRE.

    ATTENTION Le choix du critere conditionne l'ensemble des points
    _________ sur lesquels porteront les conditions d'antisymetrie.
        Il est donc conseille d'une part de le choisir avec
        soin et d'autre part de visualiser les blocages ainsi
        obtenus au moyen de l'operateur TRAC.

    REMARQUE Cet operateur n'est pas disponible en dimension 1.
    ________ L'utilisation de l'operateur BLOQUE est suffisante.

## APPU [Mecanique Limites]
    Operateur APPUI

   RIG1 = APPUI | ('DEPL') ('ROTA') | ('DIRECTION' VEC1) |  FLOT1 GEO1 ;
        |  'RADIAL'  POIN1  POIN2  |
        |  MOT1 ...  |

    Objet :

    L'operateur APPUI construit la rigidite RIG2, associee a des appuis
lineaires ( ressorts) appliques a des degres de liberte.
Cette rigidite sera ulterieurement a adjoindre a la rigidite de la
structure.

    Commentaire :

    'DEPL' : Mot-cle pour mettre un appui sur chacune des
        composantes de deplacement

    'ROTA' : Mot-cle pour mettre un appui sur chacune des
        composantes de rotation

    'RADIAL' : Mot-cle pour bloquer le deplacement radial
        par rapport | au point POIN1 en 2D (type POINT),
        | a l'axe POIN1 POIN2 en 3D (type POINT).

    'DIRECTION' : Mot-cle pour bloquer le deplacement
        (par defaut) ou la rotation (mot-cle 'ROTA')
        selon la direction definie par le vecteur VEC1

    VEC1 : vecteur (type POINT)

    MOT1 : un ou plusieurs noms (type MOT) representant les
        degres de liberte sur lesquels on veut mettre un
        appui (dans ce cas ne pas se servir des
        mots-cles precedents )

        Les noms des degres de liberte possibles sont :

        pour un calcul en MODE PLAN CONT : UX UY
        pour un calcul en MODE PLAN DEFO : UX UY
        pour un calcul en MODE AXIS : UR UZ RT
        pour un calcul en MODE FOUR : UR UZ UT RT
        pour un calcul en MODE TRID : UX UY UZ RX RY RZ

    FLOT1 : raideur elastique de l'appui (type FLOTTANT)

    GEO1 : objet oº seront imposes les appuis
        (type MAILLAGE ou POINT)

    RIG1 : matrice resultat (type RIGIDITE, sous-type RIGIDITE)

    Remarque :

    Cette rigidite doit etre passee en argument de l'indice
    RIGIDITE_CONSTANTE de la table d'entree de PASAPAS.

## ARCGAU [Thermique Resolution] (proc)
Procedure ARCGAU

   CHPO1 = ARCGAU TAB1 ;

        TAB1.'PUISSANCE' .'RENDEMENT'
        .'DIFFUSVITE' .'CONDUCTIVITE'
        .'VITESSE'
        .'T0' .'TFUSION'
        .'NTERMES'
        .'MAILLAGE'
        .'EPAISSEUR'
        .'LOCAL' .'INSTANT'
        .'PRECISION'
        .'NSURFACES' .'SURFACE'
        .'GAUSS' .'ECART-TYPE'

Objet :

Cette procedure calcule le champ de temperature resultant du
deplacement d'un arc de soudure sur une plaque infinie. L'arc est
soit ponctuel, soit gaussien et se deplace selon l'axe X.
La largeur de bain (largeur de l'isotherme a TFUSION) est calculee
pour toutes les surfaces donnees dans la table.
La solution analytique du probleme est tiree de Rosenthal :
Mathematical Theory of Heat Distribution During Welding and
Cutting.

Commentaire :

En entree :

    TAB1 : Objet de type TABLE, indice par des mots, servant a
        definir les options de calcul :

    Arguments :

        'PUISSANCE' : REEL : Puissance de l'arc (en W)

        'RENDEMENT' : REEL : Rendement de l'arc : Rapport de
        la puissance recue par la piece et de la puissance
        de l'arc

        'DIFFUSVITE' : REEL : Diffusivite thermique du materiau
        (en m2/s)

        'CONDUCTIVITE' : REEL : Conductivite thermique du
        materiau (en W/Km2)

        'VITESSE' : REEL : Vitesse de deplacement de l'arc (en m/s)

        'T0' : REEL : Temperature ambiante (en °C ou en K)

        'NTERMES' : ENTIER : Nombre de termes de la somme

        'MAILLAGE' : MAILLAGE : Maillage support du champ de
        temperature

        'EPAISSEUR' : REEL : Epaisseur de la piece (en m)

        'LOCAL' : BOOLEEN : VRAI si la piece est decrite dans
        le repere local a l'arc

        'INSTANT' : REEL : Si 'LOCAL' est FAUX, instant
        auquel il faut calculer le champ de temperature
        (l'abscisse de l'arc est alors V*t) (en s)

        'TFUSION' : REEL : Temperature de fusion (en °C ou en K)

        'PRECISION' : REEL : Precision du calcul de la largeur de
        bain (en m)

        'NSURFACES' : ENTIER : Nombre de surfaces sur lesquelles
        la largeur de bain doit etre calculee

        'SURFACE' : TABLE : indice par des entiers
        'SURFACE'.I : MAILLAGE : i-eme surface sur
        laquelle la largeur de bain doit etre
        calculee

        'GAUSS' : BOOLEEN : VRAI si la source est gaussienne

        'ECART-TYPE' : REEL : Ecart-type de la gaussienne (en m)

En sortie :

        CHPO1 : CHPOINT : Champ de temperature (en °C ou en K)

        Dans la table en entree :

        'LARGEUR' : TABLE :
        'LARGEUR'.I : REEL : Largeur de bain calculee
        sur la i-eme surface

        'XBAIN' : TABLE :
        'XBAIN'.I : REEL : Abscisse a laquelle la
        largeur de bain est maximale pour la
        i-eme surface

## ARET [Maillage Lignes]
Operateur ARETE
--------------- ENVE

ARET1 = ARETE VOLU1 ( TETA ) ;

Objet :

L'operateur ARETE construit un maillage constitue d'elements SEG2
representant les aretes vives d'un maillage tridimensionnel. Dans
cet operateur, une arete est consideree comme vive si la difference
d'angle entre les normales des facettes adjacentes est superieure
a une borne TETA valant 20 degres par defaut.

Commentaire :

ARET1 : objet de type MAILLAGE contenant uniquement des elements
        SEG2 representant les aretes vives.

VOLU1 : objet de type MAILLAGE tridimensionnel.

TETA : critere d'angle en degres (type FLOTTANT).

## ARGU [Langage Methodes]
Operateur ARGUMENT
------------------ QUIT RESP

ARGUMENT OBJET1?TYP1 OBJET2?TYP2 .....;

Objet :

L'operateur ARGUMENT permet de lire des arguments OBJETi, de type
TYPi, depuis l'interieur d'une procedure.

Pour des raisons de performances, il est preferable de recuperer
les arguments directement dans DEBPROC quand c'est possible.

Commentaire :

L'ensemble ?TYPi est facultatif. S'il est omis, ARGU essaie de
recuperer un objet de n'importe quel type. Les objets de type
inconnu doivent etre place a la fin de la liste des arguments
a lire.

Le caractere ? vaut :

- soit * si la lecture est imperative
- soit / sinon

Les types d'objet possibles sont:

    'MAILLAGE' 'AFFECTE ' 'DEFORME '
    'CHPOINT ' 'CHAMELEM' 'LISTREEL'
    'RIGIDITE' 'BLOQSTRU' 'LISTENTI'
    'ELEMSTRU' 'SOLUTION' 'CHARGEME'
    'STRUCTUR' 'TABLE ' 'MODELE '
    'MAFFEC ' 'MSOSTU ' 'EVOLUTIO'
    'IMATRI ' 'MJONCT ' 'SUPERELE'
    'ATTACHE ' 'MMATRI ' 'LOGIQUE '
    'FLOTTANT' 'ENTIER ' 'MOT '
    'TEXTE ' 'LISTMOTS' 'VECTEUR '
    'VECTDOUB' 'POINT ' 'CONFIGUR'
    'LISTCHPO' 'BASEMODA' 'PROCEDUR'
    'BLOC ' 'MMODEL ' 'MCHAML '
    'MINTE ' 'NUAGE ' 'MATRIK '
    'LISTOBJE'

Exemple :

Procedure faisant l'addition de n entiers avec n plus grand ou
egal a 2.

        DEBP ADDI ;
        ARGU I*ENTIER J*ENTIER ;
        K = I + J ;
        REPETER NFOI;
        ARGU L/ENTIER;
        SI ( EXISTE L) ;
        K = K + L ;
        SINON;
        QUITTER NFOI;
        FINSI;
        FIN NFOI;
        FINPROC K;
        X = ADDI 2 5 4;

## ASIH [Mathematiques Fonctions]
  RESU1 = 'ASIH' OBJET1 (MOT1) ;

Operateur ASIH
-------------- ACOS ASIN ATG

Objet :

L'operateur ASIH calcule l'arc sinus hyperbolique de l'objet
OBJET1.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ASIN [Mathematiques Fonctions]
  RESU1 = 'ASIN' OBJET1 (MOT1) ;

Operateur ASIN
-------------- ACOS ATG

Objet :

L'operateur ASIN (arc-sinus) calcule l'arc-sinus d'OBJET1.
Le resultat est en degres, dans l'intervalle [-90 ; 90].

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ASPARAM [Fluides Modele] (proc)
   Procedure ASPARAM

     ASPARAM OBJ1 ;

   OBJET :

La procedure ASPARAM complete la table RXT de la procedure ENCEINTE
en vue de modeliser l'aspersion.
Cette procedure est appelee par la procedure ENCEINTE

   Commentaire

    OBJ1 Table en entree de la procedure ENCEINTE

## ASSI [Langage Base]
    Operateur ASSI

   1 ere possibilite

       RES1 ... RESn = ASSI IASSIS INS1 ... INSP;

    Objet :

    L'operateur ASSIstant fait executer par l'assistant IASSIS
 (ENTIER) l'instruction elementaire :

     RES1 ... RESn = INS1 ... INSP;

    Si la version parallele de Castem est utilisee, l'instruction
 sera terminee aussitot qu'elle sera transferee a l'assistant.
 Si une autre instruction a besoin de ces resultats, elle devra attendre
 que ceux-ci soient disponobles.

    Exemple 1 :

    MAT1 = ASSI 1 MATER MODEL1 YOUNG 1E5 NU 0.3;

    L'assistant 1 va se charger d'executer :

    MAT1 = MATER MODEL1 YOUNG 1E5 NU 0.3;

    Si une autre instruction utilise par la suite MAT1, elle sera
 bloquee en attendant la disponibilite de MAT1 (que ce soit sur le
 maitre ou sur un assistant).

   2eme possibilite

    RES1 ... RESn = ASSI 'TOUS' INS1 ... INSP;

   Objet :

    Si la meme instruction est executee sur plusieurs assistants mais
 avec des donnees differentes, il suffit d'utiliser l'option 'tous'
 et de stocker les donnees a distribuer sous forme de tables de soustype
 ESCLAVE ou les donnees associees a l'assistant I se trouvent a l'indice I.
 Les resultats sont stockes dans des tables de sous types ESCLAVE.

    Exemple 2 :

     TMAT1 = 'ASSI' 'TOUS' MATER TMODL1 'YOUNG' 1E5 'NU' 0.3 ;

       TMODL1 : table de sous type ESCLAVE
       TMODL1 . i : modele associe a l'assistant i
       TMAT1 : table de sous type ESCLAVE
       TMAT1 . i : resultat associe a l'assistant i

    Exemple 3 :

       TMODL1 = 'TABLE' ESCLAVE ;
       TMODL1 . 1 = MODL1 ;
       TMODL1 . 3 = MODL2 ; TMODL1 . 4 = MODL4 ;

* Declaration de 2 assistants
       'OPTI' 'ASSI' 2 ;

       TMAT1 = ASSI 'TOUS' 'MATER' TMODL1 'YOUNG' 1E5 'NU' 0.3 ;
 la commande precedente est equivalente aux instructions suivantes :
       TMAT1 = 'TABLE' ESCLAVE ;
       TMAT1 . 1 = ASSI 1 'MATER' TMODL1 . 1 'YOUNG' 1E5 'NU' 0.3 ;
       TMAT1 . 3 = 'MATER' TMODL1 . 3 'YOUNG' 1E5 'NU' 0.3 ;
       TMAT1 . 4 = ASSI 1 'MATER' TMODL1 . 4 'YOUNG' 1E5 'NU' 0.3 ;

 Remarques :

    Lors de l'utilisation de l'option 'tous', toutes les tables ESCLAVES
 existantes dans l'instruction doivent avoir les memes indices.

    Il est tres fortement deconseiller de transferer des tables a un
 assistant i car ces objets peuvent etre modifies durant l'operation.

   Il est possible de faire travailler le maitre comme un assistant (le
 numero d'assistant qui lui est associe est 0 ).

   Il est possible de definir un IASSIS plus grand que le nombre
 d'assistants declares NBass (opti assi nbass ; ). L'operation sera
 transferee sur l'assistant I defini par I = modulo (IASSIS,nbass+1)
 (le maitre jouant aussi le role d'un assistant).

   Ces deux dernieres proprietes permettent de tester un programme
 GIBIANE parallele sur une machine sequentielle en definisaant 0
 assistant ('OPTI' 'ASSI' 0 ; ).

## ATAH [Mathematiques Fonctions]
  RESU1 = 'ATAH' OBJET1 (MOT1) ;

Operateur ATAH
-------------- ACOS ASIN ATG

Objet :

L'operateur ATAH calcule l'arc tangente hyperbolique de l'objet
OBJET1.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## ATG [Mathematiques Fonctions]
  RESU1 = 'ATG' OBJET1 (OBJET2) (MOT1) ;

Operateur ATG
------------- ACOS ASIN

Objet :

L'operateur ATG (arc-tangente) calcule l'arc-tangente
d'OBJET1, ou d' OBJET1 / OBJET2 si OBJET2 est donne.

Le resultat est en degres, dans l'intervalle [-90 ; 90]
pour l'arc-tangente a un argument et dans l'intervalle
[-180 ; 180] pour l'arc-tangente a deux arguments.

|  OBJET1  |  ( OBJET2 )  |  RESU1  |
|  ENTIER  |  (  ENTIER  )  |  FLOTTANT  |
|  FLOTTANT  |  ( FLOTTANT )  |  FLOTTANT  |
|  CHPOINT  |  ( CHPOINT  )  |  CHPOINT  |
|  LISTENTI  |  ( LISTENTI )  |  LISTREEL  |
|  LISTREEL  |  ( LISTREEL )  |  LISTREEL  |
|  EVOLUTIO  |  |  EVOLUTIO  |
|  MCHAML  |  (MCHAML)  |  MCHAML  |

Remarque 1 :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

Remarque 2 :

Lorsque l'objet OBJET2, est omis, l'operateur ATG calcule
l'arc tangente de l'objet OBJET1 (type ENTIER ou FLOTTANT).

Remarque 3 :

Lorsque l'operateur ATG calcule l'arc tangente d'un CHPOINT, il
remplace chaque valeur du CHPOINT par son arc tangente. L'objet
RESU1 est, dans ce cas, de type CHPOINT, de meme structure
qu'OBJET2.

Remarque 4 :

Lorsque l'operateur ATG calcule l'arc tangente d'OBJET1 de type
CHPOINT divise par l'OBJET2 de type CHPOINT, chaque valeur d'OBJET1
est divisee par la valeur correspondante d'OBJET2, si elle existe
(sinon un angle de +- 90 degres est donne), puis on en prend l'arc
tangente. Dans ce cas, l'objet RESU1 est de type CHPOINT, de Meme
structure qu'OBJET2.

## AUTOPILO [Fluides Resolution] (proc)
    Procedure AUTOPILO

 Cette procedure est appelee par la procedure de calcul nonlineaire
en cas de demande de limitation de charge automatique.
Le but de cette procedure est de fournir un coefficient pour normer
DELT afin que ce dernier soit compatible avec le critere de pilotage.
Ce coefficient est une norme de DELT au sens du critere. En principe il
est positif. Toutefois lui donner un signe permet de forcer l'algorithme
vers un direction donnee. Par defaut le critere est le max de
l'increment de deformation totale et de l'increment de deformation
"plastique" (total - elastique).
Pour plus d'information voir la procedure elle meme.

## AVCT [Mathematiques Autres]
 Directive AVCT

Objet : realise un increment en temps.

 n n-1 -1 n-1
T = T + DT * D * G

ou

 n -1 n-1 -1 n-1
T = (1+DT*D1/D) T + (D/DT+D1) * G (matrice masse diagonale

    ALIAS :
        n n-1 n-1
(D/DT + D1) T - (D/DT) T = G

T : inconnue au SOMMET --> l'increment est au SOMMET

T : inconnue au CENTRE --> l'increment est au FACE

Syntaxe :

AVCT (rv.kizt) (rv.kizc) (rv.pasdetps) (rv.kizg) (rv.kizd)
     ALFA 'IMPR' FIDT ;

rv.kizt

Table 'KIZT' cree par l'utilisateur et placee dans la table cree par
EQEX a l'entree KIZT (ici rv.kizt)
Cette table contient les CHAMPOINT-TRIO inconnues

< rv.kizc >

Table 'KIZC' cree par EQEX contient les conditions limites de type
valeur imposee.

< rv.padetps >

Table de type 'PASDETPS' Contient les informations relatives au
pas de temps. Elle est cree par les operateurs de discretisation
ayant une limite de stabilite en temps (NS , NSKE etc )
En l'absence de cette table DT est pris egal a 1.

< rv.kizg >

Table de type 'KIZG' cree par les operateurs de discretisation
contient les increments ranges dans l'ordre des inconnues de la
KIZT.

< rv.kizd >

Table de type 'KIZD' cree par KDIA contient les matrices masse
diagonales (sous forme de CHAMPOINT-TRIO)

< ALFA > Flottant : tolerance sur le pas de temps
DT reel = ALFA * DT calcule (par defaut ALFA=1.)

< IMPR > Mot : impression d'informations sur les pas de temps

< FIDT > Entier : frequence de l'impression

## BALOURD [Mecanique Dynamique] (proc)
     Procedure BALOURD Voir aussi GYRO, CAMPBELL

        BALOURD TAB1 PROMEG

Objet:

        BALOURD calcule la reponse d'une machine tournante
        a un balourd en utilisant eventuellement
        une base de modes propres

   INPUT

 TAB1 Table contenant:

    TAB1.'BASE_MODALE': Table contenant la base de modes reels utilisees
        (table generee par VIBR avec l'option TBAS)
        Si aucune base modale n'est donnee, le calcul est
        effectuedirectement dans l'espace physique.

    Les matrices de masse, de raideur, d'amortissement et de couplage
   gyroscopique peuvent etre donnees deja projetees sur la base de
   modes reels ou non:

    TAB1.'MASS_PROJ': Matrice de masse projetee sur les modes
        reels utilises
    TAB1.'MASSE': Matrice de masse

    TAB1.'RIGI_PROJ': Matrice de rigidite projetee sur les modes
        reels utilises
    TAB1.'RIGIDITE': Matrice de rigidite

    TAB1.'AMOR_PROJ': Matrice d'amortissement projetee sur les modes
        reels utilises
    TAB1.'AMORTISSEMENT': Matrice d'amortissement

    TAB1.'KROT_PROJ': Matrice de raideur antisymetrique due a
        l'amortissement corotatif projetee sur les modes reels utilises
    TAB1.'KROTATIF': Matrice de raideur antisymetrique due a
        l'amortissement corotatif

    TAB1.'GYRO_PROJ': Matrice de couplage gyrsocopique projetee sur
        les modes reels utilises
    TAB1.'GYROSCOPIQUE': Matrice de couplage gyrsocopique.
      La matrice de couplage gyroscopique doit etre donnee pour une vitesse
      de rotation de 1 rad/s

    La force de balourd peut etre definie de plusieurs façon

   1- La force de balourd reelle est donnee
      et la procedure calcule automatiquement la partie imaginaire
      necessaire au calcul en supposant l'axe de l'arbre tournant oriente
      suivant l'axe Ox et tournant avec une vitesse positive

    TAB1.'FBALOURD': Force de balourd pour une vitesse de rotation unite
      La force de balourd doit etre donnee pour une vitesse de rotation de
      1 rad/s

    TAB1.'VROTATION': CHPO defini sur les memes points que la force de balourd
      et donnant la direction du vecteur rotation
      (composante du CHPO: RX RY RZ).
      Par defaut, vecteur Ox. Ce vecteur permet de calculer la partie imaginaire
      du vecteur force de balourd.

   2- L'utilisateur donne directement la partie reelle et la partie imaginaire
      utilises pour la calcul (projetee ou non sur la base modale utilisee)

    TAB1.'FBAR_PROJ': Force de balourd reelle projetee sur les modes
        reels utilises
    TAB1.'FBAI_PROJ': Force de balourd imaginaire projetee sur les modes
        reels utilises

    TAB1.'FBALREEL': Force de balourd reelle pour une vitesse de
        rotation unite. La force de balourd doit etre donnee pour
        une vitesse de rotation de 1 rad/s.
    TAB1.'FBALIMAG': Force de balourd imaginaire pour une vitesse de
        rotation unite. La force de balourd doit etre donnee pour
        une vitesse de rotation de 1 rad/s

    TAB1.'REPONSE' : Table contenant les i points ou sont calcules les reponses
     (TAB1.'REPONSE').i.'POINT':

    TAB1.'SAUVDEFO': Vrai si on veut sauver les deformees pour chaque reponse i

    TAB1.'AFFICHAGE': VRAI si on veut afficher les frequences de rotation
        au cours du calcul

  PROMEG: LISTREEL contenant les vitesses de rotation (en rad/s) pour lesquelle
        on calcule la reponse au balourd

   OUTPUT

    TAB1.'REPONSE' : Table contenant i indices
     (TAB1.'REPONSE'). i . 'POINT': Points ou sont calcules les reponses
     Grandeurs donnees directement par l'inversion du systeme
    (pas de sens physique)
        (TAB1.'REPONSE'). i . 'UXREEL': Deplacement UX reel
        (TAB1.'REPONSE'). i . 'UYREEL': Deplacement UY reel
        (TAB1.'REPONSE'). i . 'UZREEL': Deplacement UZ reel
        (TAB1.'REPONSE'). i . 'RXREEL': Rotation RX reel
        (TAB1.'REPONSE'). i . 'RYREEL': Rotation RY reel
        (TAB1.'REPONSE'). i . 'RZREEL': Rotation RZ reel
        (TAB1.'REPONSE'). i . 'UXIMAG': Deplacement UX imaginaire
        (TAB1.'REPONSE'). i . 'UYIMAG': Deplacement UY imaginaire
        (TAB1.'REPONSE'). i . 'UZIMAG': Deplacement UZ imaginaire
        (TAB1.'REPONSE'). i . 'RXIMAG': Rotation RX imaginaire
        (TAB1.'REPONSE'). i . 'RYIMAG': Rotation RY imaginaire
        (TAB1.'REPONSE'). i . 'RZIMAG': Rotation RZ imaginaire
[… notice tronquée ; texte complet dans l'archive PCW_24]

## BARY [Maillage Generaux]
Operateur BARYCENTRE

POIN1 = BARY GEO1 ('ELEM');

Objet :

L'operateur BARYCENTRE cree le point (ou le maillage de points)
correspondant a la moyenne arithmetique de l'ensemble des noeuds
contenus dans une geometrie GEO1.

Commentaire :

GEO1 : geometrie (type MAILLAGE)

POIN1 : barycentre de la geometrie GEO1 (type POINT
        ou MAILLAGE de POI1)

'ELEM': option pour calculer le barycentre de chaque element
        (le resultat sera alors de type MAILLAGE de POI1)

Remarque :

Ce barycentre ne coincide pas en general avec le centre de
gravite de la geometrie.

## BASE [Mecanique Dynamique]
     Operateur BASE

     Cas 1 :
     BAS1 = BASE STRU1 (ATTA1) (SOL1) (SOL2) ;

     Cas 2 :
     TAB1 = BASE  TAB2  TAB3  | 'PLUS'  VEC1  ;
        | 'ROTA'  FLOT1  P1  P2  ;

     Objet :

     Cas 1 :
     Dans une analyse sur base modale, une structure est representee
par un ensemble de modes et de solutions statiques.
La specification des liaisons qui s'exercent eventuellement sur la
structure, ainsi que la specification de l'ensemble de modes et de
solutions statiques, definissent le probleme a resoudre.
L'operateur BASE permet de construire un objet (type BASEMODA)
qui rassemble ces diverses informations.

     Cas 2 :
     L'operateur BASE effectue une operation geometrique de translation
('PLUS') ou de rotation ('ROTA') sur un objet contenant les modes et
les pseudo-modes d'une structure.

    Commentaire :

    STRU1 : objet contenant la description de la structure, soit
        elementaire, soit forme de sous-structures identiques
        (type STRUCTUR).

    ATTA1 : objet contenant la specification des liaisons
        (type ATTACHE).

    SOL1 : objet contenant l'ensemble des modes
        (type SOLUTION, sous-type MODE).

    SOL2 : objet contenant l'ensemble des solutions statiques
        (type SOLUTION, sous-type SOLUTION STATIQUE)

    La specification des modes ,des liaisons, des solutions statiques
est facultative.

    TAB1 : objet contenant les caracteristiques modales de la
        structure apres translation ou rotation (type TABLE).
        structure de TAB1 : TAB1.'BASE' = TAB4
        .'POINT' = TAB5
        TAB4 a la Meme structure que TAB2.
        TAB5 donne la correspondance dans la nouvelle geome-
        trie des points contenus dans TAB3 (type TABLE),
        TAB5.(TAB3.I) = QI , QI est le point qui corres-
        pond au niveau de la geometrie modifiee au point
        PI = TAB3.I de la geometrie initiale.

    TAB2 : objet contenant les caracteristiques modales de la
        structure initiale (type TABLE),
        table de sous-type BASE_MODALE.

    TAB3 : objet de type TABLE indice par des ENTIERs variant de 1 a
        N et contenant des points de la geometrie,
        table de sous-type POINT.

    'PLUS' : objet de type MOT indiquant que l'operation geometrique
        effectuee est une translation de vecteur VEC1 (objet de
        type POINT).

    'ROTA' : objet de type MOT indiquant que l'operation geometrique
        effectuee est une rotation d'angle FLOT1 (en degre) autour
        de l'axe defini par le point P1 (en 2D) ou les points P1
        et P2 (en 3D).

    Combinaisons possibles :

    Si STRU1 est elementaire :

      BAS1 = BASE STRU1 ATTA1 SOL1 SOL2 ;
      BAS2 = BASE STRU1 ATTA1 SOL1 ;
      BAS3 = BASE STRU1 ATTA1 SOL2 ;
      BAS4 = BASE STRU1 ATTA1 ;
      BAS5 = BASE STRU1 SOL1 ;

    Si STRU est un ensemble de sous-structures identiques :

      BAS6 = BASE STRU1 ATTA1 SOL1 ;
      BAS7 = BASE STRU1 ATTA1 ;
      BAS8 = BASE STRU1 SOL1 ;

    Remarque :

    Dans le cas oº les solutions statiques sont deduites des liaisons
l'operateur BASE calcule automatiquement les solutions statiques,
par defaut.

    Lecture d'une base elementaire :

    Des operateurs comme PJBA , EVOL, RECO ,... demandent pour
operandes une base elementaire, c'est-a-dire une base modale qui
ne soit pas un ensemble de sous-bases.

    Il existe trois possibilites de lecture :

      BAS : lecture de la base elementaire BAS
      BAS STRU : lecture de la base elementaire prise dans BAS ,
        associee a la sous structure STRU
      BAS STRU N1 : recherche de la base elementaire BAS, associee a la
        Nieme sous-structure prise dans l'ensemble des
        sous-structures identiques STRU.

    Exemple 1 :

      B1 = BASE STRU1 MOD1 ; B1 est elementaire
      B = B1 ET B2 ET ....;
      FN1= PJBA B1  FORCE1 ;  |  Ces deux formulations
      FN1= PJBA B STRU1  FORCE1 ;  |  sont equivalentes

    Exemple 2 :

      STRU2= STRU1 RIGI2 MASS2 6 ; STRU2 contient 6 sous-
        structures identiques
      B2 = BASE STRU2 MOD2 ;
      FN2 = PJBA B2 STRU2 4 FORCE2 ; B2 STRU2 4 represente la
        base elementaire attachee a la
        4ieme sous-structure de STRU2

## BESS [Mathematiques Fonctions]
  RESU1 = 'BESS' | 'J0'  | OBJET1 (MOT1) ;
        | 'J1'  |
        | 'JN' | N1 |
        | 'Y0'  |
        | 'Y1'  |
        | 'YN' | N1 |

Operateur BESS

Objet :

L'operateur BESS applique l'une des fonctions de Bessel a l'objet OBJET1.

N1 : Objet de type 'ENTIER' correspondant a l'ordre de la fonction
     de Bessel pour les cas 'JN' ou 'YN'.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## BGMO [Multi-physique Multi-physique]
Operateur BGMO

OBJ2 = BGMO MOT1 OBJ1 (VAL1) (VAL2) ;

Description :

L'operateur BGMO evalue les fonctions apparaissant dans le modele
de decalcification de mortier de Bruno Gerard. Ces fonctions,
dependantes de la temperature sont la capacite, la conductivite et
leurs derivees en fonction de la temperature. Bien que ces fonctions
soient dimensionnelles, l'operateur peut aussi travailler pour des
problemes adimensionnels.

Cet operateur contient les fonctions de couplage decrivant
l'interaction entre le probleme chimique et le probleme mecanique.
Ces fonctions sont (1-CHD) ou CHD est le dommage chimique, et
la conductivite due au dommage mecanique.

Contenu :

MOT1 : 'COND' pour la conductivite
        'DCON' pour la derive de la conductivite
        'CAPA' pour la capacite
        'DCAP' pour la derive de la capacite
        'CHED' pour un moins le dommage chimique
        'CONM' pour la conductivite due au dommage mecanique
OBJ1 : REEL ou MCHAML decrivant la temperature
VAL1 : temperature de reference (REEL). Valeur par defaut : 1.
        si 'CONM' est utilise, l'argument de cette fonction est un
        endommagement normalise et cette valeur n'est pas utilisee
VAL2 : conductivite/capacite de reference (REEL). Valeur par
        defaut : 1.
        Si 'CHED' est utilise, le resultat est un endommagement
        normalise et VAL2 n'est pas utilisee.
OBJ2 : REEL ou MCHAML resultant de l'evaluation

Notes
Les unites sont les metres, annees et mmol/l
La temperature/concentration peut varier de 0 a 20 mmol/l
L'endommagement varie de 0 a 1

## BIBLIO [—] (proc)
CHAP{Specification generale}

    Procedure BIBLIO

    TAB1 = BIBLIO MOT1 ('REFE' ENT1) ;

    Objet :

        La procedure BIBLIO fournit des donnees issues de la litterature.
    Les donnees d'un meme sujet sont identifiees par un mot-cle (MOT1).
    La liste des mot-cles disponibles, donc des sujets couverts par BIBLIO,
    est precisee dans cette notice, de meme que la liste des references
    bibliographiques.

        Pour un meme sujet (mot-cle), il peut y avoir plusieurs references
    bibliographiques. L'option REFE permet alors de choisir parmi celles-ci
    en fournissant le numero de la reference. Ce numero est precise entre
    crochets dans la liste des references bibliographiques donnee dans cette
    notice. La liste des references bibliographiques est presentee par ordre
    alphabetique du nom du premier auteur. Enfin, pour un sujet donnee, la
    reference utilisee par defaut est precisee dans la description des donnees
    associees a chaque mot-cle.

    Commentaire :

    MOT1 : objet MOT, sujet pour lequel on souhaite obtenir des donnees.

    ENT1 : objet ENTIER, numero de la reference souhaitee.

    TAB1 : objet TABLE, donnees fournies par la procedure.

    Remarque : TAB1 contient systematique les informations complementaires
    ---------- suivantes (tracabilite) :
        - CREATEUR : le nom de la procedure qui les a fournies
        - REFERENCE : MOT1 et ENT1 concatenes

CHAP{Mot-cle "316L"}
PART{Caracteristiques thermomecaniques (Depradeux, 2004) [1] (defaut)}

    Donnees fournies dans TAB1 :

    TAB1 . 'RHO' : objet EVOLUTION, masse volumique (kg/m^3) en fonction
        de la temperature (degC) (tableau 3.6, p. 93).
        La valeur a 1500 degC est tiree de la remarque en bas
        de p. 95 concernant la chaleur latente massique.

    - Caracteristiques thermiques :

    TAB1 . 'K' : objet EVOLUTION, conductivite thermique (W/m/degC) en
        fonction de la temperature (degC) (tableau 3.6, p. 93).
        La valeur a 1500 degC est majoree pour tenir compte des
        effets hydrodynamiques dans le bain de metal fondu (voir
        remarque 1 ci-dessous).

    TAB1 . 'C' : objet EVOLUTION, capacite calorifique massique (J/kg/degC)
        en fonction de la temperature (degC) (tableau 3.6,p. 93).

    TAB1 . 'TFUS' : objet FLOTTANT, temperature de fusion (degC).

    TAB1 . 'QLAT' : objet FLOTTANT, chaleur latente massique de fusion (J/kg).
        Valeur tiree de la remarque en bas de p. 95 concernant
        la chaleur latente massique.

    - Caracteristiques mecaniques :

    TAB1 . 'NU' : objet FLOTTANT, coefficient de Poisson (P. 59).

    TAB1 . 'YOUN' : objet EVOLUTION, module de Young (Pa) en fonction de
        la temperature (degC).
        Colonne E(2), tableau A2.1, p. 210.

    TAB1 . 'ALPH' : objet EVOLUTION, coefficient de dilatation thermique
        en fonction de la temperature (degC).
        Colonne alpha(2), tableau A6.2, p. 211.

    TAB1 . 'SIGY' : objet EVOLUTION, limite d'elasticite conventionnelle (Pa)
        en fonction de la temperature (degC).
        Colonne Sigm(3), tableau A6.3, p. 212.

    TAB1 . 'TRAC' : objet EVOLUTION, courbes de traction conventionnelle (Pa)
        en fonction de la temperature (degC).
        Tableau A6.4, p. 212-213.
        NB : limite elastique a 0,2% de def. plastique.

    TAB1 . 'ECRO' : objet NUAGE, courbes d'ecrouissage (Sig. Vs Eps.Plas.)
        conventionnelle (Pa) en fonction de la temperature (degC).
        Ces courbes sont derivees des courbes de traction (TRAC) :
        on corrige la def. totale de la def. elas. (Sig/Youn) pour
        avoir la def. plas., puis on interpole la valeur de la
        contrainte pour une valeur nulle de la def. plastique.
        NB : la contrainte a Eps.Plas.=0 n'est pas necessairement
        egale a la limite d'elasticite (SIGY) fournie ci-dessus.

    Remarque 1 : la valeur majoree de la conductivite thermique est tiree
    ------------ de (Cambon, 2018) (voir table 1).

PART{Caracteristiques thermomecaniques (Cambon, 2018) [2]}

    Donnees fournies dans TAB1 :

    - Caracteristiques thermiques :

    TAB1 . 'K' : objet EVOLUTION, conductivite thermique (W/m/degC) en
        fonction de la temperature (degC) (Table 1).

    TAB1 . 'ENTH' : objet EVOLUTION, enthalpie volumique (J/m^3) en fonction
        de la temperature (degC) (table 1).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## BIF [Fluides Resolution] (proc)
    Operateur BIF
    ------------- FROT

    SYNTAXE (EQEX) : Cf operateur EQEX

    'OPER' BIF tabbif

    OBJET :

L'operateur BIF calcule les coefficients de couplage pour les equations
de quantite de mouvement et d'energie pour le gaz et le 'fluide
particules'. (formulation EF)
Les equations de qdm sont divisees par la masse volumique et ont pour
inconnues les vitesses.
Les equations d'energie sont divisees par (Rho*Cp) et ont pour inconnues
les temperatures.

    COMMENTAIRES :

  qdm: BIF calcule Kp et Kg. Les termes Ip et Ig sont
        assembles via FROT.

        Ig : gaz terme source de qdm du a la trainee
        Ip : particules, terme source de qdm du a la trainee
        [Ig] = [Ip] = m/s2 (force/unite de masse)
        Ig = Kg * (Upart - Ugaz)
        Ip = Kp * (Ugaz - Upart)
        Kg = Fd * alpha
        Kp = Fd * rhog / rhop
        Fd = (9/2) * nuf * (1 + 0.241 * Re^0.687) /Dp^2

  energie: BIF calcule Hp et Hg. Les termes Qp et Qg sont
        assembles via ECHI.

        Qg : gaz terme source d'energie (ech. par convection)
        Qp : part. terme source d energie (ech. par convection)
        [Qg] = [Qp] = K/s
        Qg = Hg * Volume * (Tpart - Tgaz)
        Qp = Hp * Volume * (Tgaz - Tpart)
        Hg = H * 6 * alpha / Dp / rhoCpg / Volume
        Hp = H * 6 / Dp / rhoCpp / Volume
        H = Nu * lambdag / Dp

tabbif TABLE
tabbif.'RHOF' masse volumique du fluide gaz (kg/m3) FLOTTANT
tabbif.'RHOP' masse volumique des particules (kg/m3) FLOTTANT
tabbif.'DPART' diametre des particules (m) FLOTTANT
tabbif.'NUF' viscosite cinematique du fluide (m2/s) FLOTTANT
tabbif.'ALPHA' indice de la table INCO pour la MOT
        fraction volumique des particules (CHPOINT SCAL SOMMET)
tabbif.'UFLUID' indice de la table INCO pour la MOT
        vitesse du gaz (CHPOINT VECT SOMMET)
tabbif.'UPART' indice de la table INCO pour la MOT
        vitesse des particules (CHPOINT VECT SOMMET)
tabbif.'KFLUID' indice de la table INCO pour le MOT
        coefficient Kg (gaz) (CHPOINT VECT CENTRE)
tabbif.'KPART' indice de la table INCO pour le MOT
        coefficient Kp (particules) (CHPOINT VECT CENTRE)

Et pour le cas THERMIQUE (optionnel):

tabbif.'LAMBDAF' conductivite thermique du gaz (Jm2/sK) FLOTTANT
tabbif.'ROCPF' masse vol. x capacite calor. du gaz (J/K) FLOTTANT
tabbif.'ROCPP' masse vol. x capacite calor. des part. (J/K) FLOTTANT
tabbif.'TGASN' indice de la table INCO pour la MOT
        temperature du gaz aux noeuds (CHPOINT SCAL SOMMET)
tabbif.'TGASE' indice de la table INCO pour la MOT
        temperature du gaz aux elements (CHPOINT SCAL CENTRE)
tabbif.'TPARTN' indice de la table INCO pour la MOT
        temperature des part. aux noeuds (CHPOINT SCAL SOMMET)
tabbif.'TPARTE' indice de la table INCO pour la MOT
        temperature des part aux elements (CHPOINT SCAL CENTRE)
tabbif.'HFLUID' indice de la table INCO pour le MOT
        coefficient d'echange Hg (gaz) (CHPOINT SCAL CENTRE)
tabbif.'HPART' indice de la table INCO pour le MOT
        coefficient d'echange Hp (part.) (CHPOINT SCAL CENTRE)

REMARQUE :

BIF controle l'existence de tabbif.'HPART':
    - si tabbif.'HPART' existe ====> calcule Kp, Kg, Hp, Hg
    - si tabbif.'HPART' n'existe pas ====> calcule Kp, Kg

## BILI_EFZ [Fluides Resolution] (proc)
    Procedure BILI_EFZ
    ------------------ MATE

    EVOL1=BILI_EFZ LREE1 LENT1 TABL1;

    Objet :

    Cette procedure permet de tester le modele de plasticite de
poutre 'BILIN_EFFZ', plasticite en effort tranchant.

    A partir d'un programme de chargement en courbure dont les
extremites des branches sont definies par LREE1 (objet de type
LISTREEL) et dont le nombre de point par branche est specifie par
LENT1 (objet de type LISTENTI), on produit la courbe EVOL1 (objet
de type evolution) de reponse du modele.

    La table TABL1 contient les parametres sigificatifs du modele:

    indice  |  type objet  |  commentaires
        |  point  |
    ---------|-----------------|-------------------------
     GELA  |  FLOTTANT  |  Module de cisaillement elastique
     GAYI  |  FLOTTANT  |  Module de cisaillement plastique
     YEFF  |  FLOTTANT  |  Effort tranchant  de plasticite
     SECZ  |  FLOTTANT  |  Section reduite

## BILI_MOY [Fluides Resolution] (proc)
    Procedure BILI_MOY
    ------------------ MATE

    EVOL1=BILI_MOY LREE1 LENT1 TABL1;

    Objet :

    Cette procedure permet de tester le modele de plasticite de
poutre 'BILINEAIRE', plasticite de flexion.

    A partir d'un programme de chargement en courbure dont les
extremites des branches sont definies par LREE1 (objet de type
LISTREEL) et dont le nombre de point par branche est specifie par
LENT1 (objet de type LISTENTI), on produit la courbe EVOL1 (objet
de type evolution) de reponse du modele.

    La table TABL1 contient les parametres sigificatifs du modele:

    indice  |  type objet  |  commentaires
        |  point  |
    ---------|-----------------|-------------------------
     EELA  |  FLOTTANT  |  Module elastique
     EAYI  |  FLOTTANT  |  Module plastique
     YMOM  |  FLOTTANT  |  Moment de plasticite
     INRY  |  FLOTTANT  |  Moment d'inertie

## BIOT [Magnetostatique Magnetostatique]
Operateur BIOT

Cas 1 :

CHPO1 = BIOT |('POTE')|
        |('INDU')|  GEO1

        |  'CERC'  CENTR1  POIN1 POIN2 RI RE H  |
        |  'ARC'  CENTR1  POIN1 POIN2 RI RE H  |
        |  'BARR'  POIN1  POIN2 POIN3 DY DZ  |
        |  'FIL'  POIN1  POIN2  |

        ('TRAP' P1 P2) DENS MU0 ;
Cas 2 :

CHPO3 = BIOT CHPO2 GEO1 ;

Objet :

Cas 1 :
L'operateur BIOT construit le champ d'induction ou le potentiel
vecteur de Biot et Savart cree sur l'objet GEO1 par une portion
d'inducteur filaire, surfacique ou massif de section droite
rectangulaire (defaut) ou trapezoidale. Il ne fonctionne qu'en 3D.

Cas 2 :
L'operateur BIOT construit le champ d'induction et le flux cree
sur l'objet GEO1 par une ( ou plusieurs ) spire(s) d'axe z par
une methode d'integrale elliptique. Le flux du champ d'induction
en un point de GEO1 est calcule a travers le cercle d'axe z
engendre par ce point. Il ne fonctionne qu'en 3D.

Commentaire :

'POTE' : on calcule le potentiel vecteur.
'INDU' : on calcule l'induction (defaut).
 GEO1 : objet geometrique support du champ a calculer (type
        MAILLAGE)

La geometrie de l'inducteur varie selon les mots cles choisis :

'CERC' : mot-cle suivi de :
CENTR1 : centre du cercle (type POINT)
POIN1  | deux points du plan de la spire (type POINT)
POIN2  | (les trois points doivent definir un plan)
RI : rayon interieur de l'inducteur (type FLOTTANT)
RE : rayon exterieur de l'inducteur (type FLOTTANT)
H : hauteur totale de l'inducteur dans le plan
        median (type FLOTTANT)
    Remarque : des valeurs adaptees de RI, RE et H permettent
        de modeliser une spire circulaire ou des nappes
        de courant surfaciques circulaires.
        RI = RE et H = 0 : spire circulaire
        RI = RE et H > 0 : nappe cylindrique
        H = 0 : couronne

'ARC' : mot-cle suivi de :
CENTR1 : centre du cercle (type POINT)
POIN1 : premiere extremite de l'arc (type POINT)
POIN2 : deuxieme extremite de l'arc (type POINT)
RI : rayon interieur de l'inducteur (type FLOTTANT)
RE : rayon exterieur de l'inducteur (type FLOTTANT)
H : hauteur totale de l'inducteur dans le plan
        median (type FLOTTANT)
    Remarque : des valeurs adaptees de RI, RE et H permettent
        de modeliser un arc circulaire ou des nappes
        de courant surfaciques circulaires.
        RI = RE et H = 0 : portion de spire circulaire
        RI = RE et H > 0 : portion de nappe cylindrique
        H = 0 : portion de couronne

'BARR' : mot-cle suivi de :
POIN1 : centre de gravite de la section initiale (type POINT)
POIN2 : centre de gravite de la section finale (type POINT)
 Le courant est oriente suivant l'axe local Ox (POIN1 POIN2)
POIN3 : point definissant avec POIN1 l'axe local oy de la barre
        (type POINT)
DY : largeur de la barre dans le plan POIN1 POIN2 POIN3 (plan xOy)
        (type FLOTTANT)
DZ : hauteur de la barre suivant le plan median orthogonal
        au prececent (plan xOz) (type FLOTTANT).
    Remarque : des valeurs adaptees de DY et DZ permettent
        de modeliser des nappes rectangulaires de courant.
        DZ = 0 : nappe rectangulaire dans le plan xOy
        DY = 0 : nappe rectangulaire dans le plan xOz

'FIL' : mot-cle suivi de :
POIN1 : premiere extremite du fil (type POINT)
POIN2 : deuxieme extremite du fil (type POINT)

'TRAP' : mot-cle permettant de definir une section trapezoidale :
        Dans le cas circulaire, on suppose que la section
        est dans le plan (r,z), les faces paralleles etant dans la
        direction z de l'axe de rotation.
        Dans le cas rectiligne, on suppose que la section
        est dans le plan (x,z), les faces paralleles etant dans la
        direction z.
        Les pentes sont alors definies dans le repere local de la
        section :
        P1 : pente inferieure (type FLOTTANT)
        P2 : pente superieure (type FLOTTANT)
    Remarque : des valeurs adaptees de P1 et P2 permettent
        de modeliser des inducteurs a section triangulaire
        ou des nappes de courant surfacique tronconiques.
        P1 = P2 et H = 0 : tronc de cone
        (cas circulaire)
        H = |P2 - P1|(RE-RI)/2  : section triangulaire

DENS : densite de courant (A/m2 dans le cas massif, ou A/m
        dans le cas surfacique ou A dans le cas filaire) dans la section
        droite de l'inducteur (type FLOTTANT), comptee positivement
        comme suit :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## BIOVOL [Magnetostatique Magnetostatique] (proc)
Procedure BIOVOL

     CHP1 = BIOVOL GEO1 GEO2 CHP2 FLOT1

Objet :

Calcul du champ magnetique par BIOT ET SAVART par
integration sur des elements de formes quelconques

Commentaire :

   GEO1 maillage de l'inducteur
   GEO2 maillage sur lequel on calcule le champ
   CHP2 chpoint des densites de courant sur GEO1
        (JX JY JZ) peut etre obtenu par appel a COUR3D

en sortie :

   CHP1 chpoint d'induction sur GEO2 ( BX BY BZ)

## BLOQ [Mecanique Limites]
    Operateur BLOQUE
    ---------------- REAC SYMT

CHAP{Blocage construit a partir de MOT ou de LISTMOTS}

PART{Syntaxe}
RIG1 = BLOQ |('MAXI')| |  MOT1 ...  | GEO1;
        |('MINI')| |  LISTMOT1  |
        |('DEPL')('ROTA') | ('DIRECTION' |VEC1 |)|
        |  |CHPO1| |
        |  'RADIAL' POIN1 (POIN2)  |
        |  'ORTHO'  POIN1 (POIN2)  |

PART{Objet}
    L'operateur BLOQUE construit la rigidite RIG1, associee a des
    conditions de valeurs imposees sur les inconnues d'un probleme
    discretise par la methode des mulitplicateur de Lagrange.

PART{Commentaires}
    Les conditions peuvent etre des conditions d'egalite ou des
    conditions unilaterales, auquel cas il faut specifier le
    mot-cle 'MINI' ou 'MAXI', selon que l'on desire limiter la
    valeur minimale ou la valeur maximale des inconnues concernees
    (cf. exemple 1).

    MOT1 ... : un (ou plusieurs) nom(s) representant les degres de
        liberte a bloquer. Les noms des degres de liberte associe
        a un modele specifique sont affiches lorsque celui-ci est
        liste (cf. remarque 3).

    LISTMOT1 : idem MOT1 mais sous la forme d'un LISTMOTS.

    'DEPL' : mot-cle pour bloquer tous les d.d.l. en deplacement
        (voir remarque pour le point support en MODE PLAN)

    'ROTA' : mot-cle pour bloquer tous les d.d.l. en rotation
        (voir remarque pour le point support en MODE PLAN)

    'DIRECTION': mot-cle pour bloquer le deplacement (par defaut)
        ou la rotation (mot-cle 'ROTA') selon la direction
        definie par le vecteur VEC1 (type POINT) ou par le
        champ de vecteur CHPO1 (type CHPOINT).

    'RADIAL' : mot-cle pour bloquer le deplacement radial
        par rapport | au point POIN1 en 2D .
        | a l'axe POIN1 POIN2 en 3D .

    'ORTHO' : mot-cle pour bloquer le deplacement ortho-radial
        par rapport | au point POIN1 en 2D
        | a l'axe POIN1 POIN2 en 3D

    GEO1 : objet ou seront imposees les conditions aux
        limites (type MAILLAGE ou POINT)

    RIG1 : matrice resultat (type RIGIDITE, sous-type RIGIDITE)

PART{Exemple}
 1. Si on souhaite imposer une condition UX <EG 0.3, on donnera :

        RIG1 = 'BLOQ' 'MAXI' 'UX' mesh1;
        FO1 = 'DEPI' RIG1 0.3 ;

PART{Remarques}

 1. Assemblage

    Pour la resolution, cette matrice de blocage doit etre a adjointe
    a la "rigidite" de la structure.

 2. Deplacement impose

    Lors la resolution du probleme, les valeurs non nulles a imposer
    doivent etre fournies comme second membre dans un objet de type
    CHPOINT construit a l'aide de l'operateur DEPIMP.

 3. Nom des degres de libertes pour un modele de :

     - MECANIQUE :
       si calcul en MODE PLAN CONT : UX UY
       si calcul en MODE PLAN DEFO : UX UY
       si calcul en MODE PLAN GENE : UX UY RZ(*) UZ RX RY
       si calcul en MODE AXIS : UR UZ RT
       si calcul en MODE FOUR : UR UZ UT RT
       si calcul en MODE TRID : UX UY UZ RX RY RZ
       si calcul en MODE UNID PLAN : UX UY UZ(+)
       si calcul en MODE UNID AXIS : UR UZ(+)
       si calcul en MODE UNID SPHE : UR

     - LIQUIDE : P PI

     - THERMIQUE : T

     - DARCY : TH

    (*) : pour les elements COQ2 seulement. Par ailleurs, UZ, RX, RY ne
        concernent que le point support des inconnues supplementaires.

    (+) : Les inconnues UY et UZ ne concernent que le point support des
        deformation(s) generalisee(s) des modes de calcul 1D.

 4. Deformations planes generalisees

    Les ddls de liberte du point support des inconnues supplementaires
    doivent etre bloques explicitement.
    Par exemple : RIG1 = 'BLOQUE' 'RX ' pt1 ;
    Les mot-cles 'DEPL' et 'ROTA' ne sont pas a utiliser.

CHAP{Blocage construit pour calculer une base de solutions statiques (sous-structuration)}

PART{Syntaxe}
       RIG1 = BLOQ TAB1 ;

PART{Objet}
    Construit les rigidites de blocage selon les informations
    contenues dans TAB1 et les concatene dans RIG1.

PART{Entree}
    TAB1 : objet TABLE, sous-type 'LIAISONS_STATIQUES', dont les
        indices sont des entiers et les sous-objets des objets TABLE,
        contenant les indices definissant le ddl a bloquer :
    TAB1 . 'POINT-LIAISON' : objet POINT (exemple P1)
    TAB1 . 'DDL_LIAISON' : objet MOT (exemple 'UX')

PART{Sortie}
    TAB1 . 'BLOCAGE' : objet RIGIDITE (exemple (BLOQ P1 UX))
    RIG2 : objet RIGIDITE, assemblage de toutes les
        rigidites elementaires creees.

PART{Remarque}
[… notice tronquée ; texte complet dans l'archive PCW_24]

## BMTD [Mathematiques Autres]
 Operateur BMTD
 -------------- DMTD

CHP2 = 'BMTD' MODL1 RIG1 CHP1 ;

 Objet:
Cet operateur est utilise dans le cadre d'une formulation
elements finis mixtes hybrides.
Soit D la matrice divergence, pour un element.
D est une matrice ligne dont tous les termes sont 1.
Soit M une matrice elementaire de diffusion.
Soit B la matrice de correspondance entre les numeros de face
 locaux et globaux.
Cet operateur va calculer pour chaque element le produit:
        -1 t
        B M D CHP1

Commentaires:

MODL1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

RIG1 : Objet rigidite de sous type DARCY contenant les
        matrices elementaires inverses pour les elements
        hybrides . Cet objet rigidite est le resultat de MHYB .

CHP1 : Objet de type CHPOINT, dont le support geometrique est le
        maillage CENTRE

CHP2 : Objet de type CHPOINT dont le support geometrique est le
        l'objet geometrie de RIG1,( MAILLAGE FACE ) .
        Les noms des composantes sont ceux de CHP1

## BOA [Maillage Lignes] (proc)
    Procedure BOA

    TAB1 = BOA (TAB2) ;

    Objet :

    La procedure BOA permet de mailler des lignes de tuyauterie de
façon interactive. Les donnees fournies sont proches de celles que
l'on rencontre couramment sur un plan.

    Commentaire :

    TAB2 : operande facultatif (type TABLE)
        TAB2 est issu d'une execution anterieure de BOA.
        TAB2 peut etre ainsi complete ou rectifie.

    TAB1 : objet resultat (type TABLE)

    Remarque :

    TAB1 se decompose comme suit :

        TAB1 'MAILLAGE' : maillage total

        TAB1 MOT1 : table decrivant la ligne de tuyauterie de
        nom MOT1

        TAB1 MOT1 'MAILLAGE' : maillage de la ligne MOT1
        TAB1 MOT1 'TRONCON' : table des maillages des tronçons d'une
        ligne
        TAB1 MOT1 'ELEMENT' : type d'element geometrique pour la
        ligne MOT1
        TAB1 MOT1 'PENTE' : pente par defaut de la ligne MOT1
        TAB1 MOT1 'ENTREE' : unite de longueur en entree
        TAB1 MOT1 'SORTIE' : unite de longueur en sortie
        TAB1 MOT1 'COULEUR' : couleur pour la ligne MOT1

    Utilisation :

    - Il suffit de repondre aux questions pour decrire les tuyauteries,
      qui sont definies sous forme de tronçons jointifs.

    - Il est possible de definir des tronçons de droite, des arcs, des
      coudes et doubles coudes, avec denivele eventuel.

    - Quand on parle de "nom" de ligne ou de tronçon, il s'agit en fait
      du nom de l'indice qui repere l'objet dans la table appropriee.
      C'est un objet de type MOT qu'il est conseille de fournir entre
      apostrophes.

    - En cas d'erreur de donnees, la procedure BOA peut s'arreter
      prematurement et produire un objet TAB1 non conforme. Dans ce cas,
      il suffit bien souvent d'executer a nouveau BOA sans rien modifier
      pour qu'une mise en ordre des resultats acquis soit effectuee.

## BOITE [Maillage Autres] (proc)
Procedure BOITE
--------------- COOR

MAIL2 = BOITE MAIL1 ;

Objet :

Construit le maillage d'une boite englobante du maillage donne en
entree.

Commentaire :

  MAIL1 : maillage d'entree (type MAILLAGE)

  MAIL2 : boite englobante (type MAILLAGE)

Remarque :

MAIL2 est constitue d'un element SEG2, QUA4 ou CUB8 suivant la
dimension courante 1, 2 ou 3.
Cette procedure est utile, conjointement à l'option 'BOIT' de
l'operateur TRAC.

## BORN [Mathematiques Autres]
    Operateur BORNER

    RES1  = BORNER  OBJ1 (OBJ2)  | 'MAXIMUM' OBJ4  |  ...  ;
        | 'MINIMUM' OBJ3  |
        | 'COMPRIS' OBJ3 OBJ4 |

    Objet :

    L'operateur BORNER permet de seuiller/borner les valeurs de l'objet
 OBJ1 (maximum/minimum ou inclusion dans un intervalle).
 Le resultat est mis dans l'objet RES1 de meme type que OBJ1.

    Chaque valeur de OBJ1 est comparee a la (aux) borne(s) fournie(s).
Cette valeur est conservee si elle est inferieure/superieure a la borne
(operation 'MAXIMUM'/'MINIMUM') ou egale a la borne sinon.
L'operation 'COMPRIS' correspond a une operation 'MINIMUM' suivie d'une
operation 'MAXIMUM'.

    Commentaire :

    OBJ1 objet de type LISTENTI, LISTREEL, EVOLUTION, CHPOINT, MCHAML
    RES1 objet de meme type que OBJ1

    OBJ3 borne(s) avec la(les)quelle(s) sont comparees les valeurs
    OBJ4 de OBJ1

    OBJ2 Si OBJ1 est un objet EVOLUTION OBJ2 est l'entier correspondant
        au numero de la courbe a borner.
        Si OBJ1 est un objet CHPOINT/MCHAML OBJ2 est le MOT correspondant
        au nom de la composante a borner. Si OBJ1 ne contient qu'une
        seule composante, le nom de la composante est facultatif.
        Cf. tableau ci-dessous :

    |  OBJ1 / RES1  |  OBJ2  |  OBJ3 / OBJ4  |
    |  LISTENTI  |  |  ENTIER  |
    |  LISTREEL  |  |  FLOTTANT  |
    |  EVOLUTION  |  ENTIER  |  FLOTTANT  |
    |  CHPOINT  |  MOT  |  FLOTTANT  |
    |  MCHAML  |  MOT  |  FLOTTANT  |

    Remarques :

    Dans le cas des objets de type EVOLUTION, il est possible de borner
 plusieurs courbes de OBJ1 et seules les courbes traitees sont mises
 dans l'objet resultat RES1.

    Par exemple :
      RES1 = BORNER Evol1 N1 'MAXIMUM' FLO1 N2 'COMPRIS' FLO2 FLO3 ;

    Dans le cas des objets de type MCHAML/CHPOINT, il est possible de
 borner plusieurs composantes de OBJ1 et seules les composantes traitees
 sont mises dans l'objet resultat RES1. Les composantes peuvent etre de
 type FLOTTANT, LISTENTI, LISTREEL, EVOLUTION quand OBJ1 est un MCHAML.

    Par exemple :
      RES1 = BORNER Chpo1 'COM1' 'MAXIMUM' FLO1 'COM2' 'MINIMUM' FLO2 ;

## BROCHE [Fluides Resolution] (proc)
   Procedure BROCHE

     BROCHE RXT TBT ;

   OBJET :

La procedure BROCHE est une procedure interne appelee par EXECRXT

   Commentaires

   RXT TABLE :
   TBT TABLE :

## BRUCHE [Fluides Resolution] (proc)
   Procedure BRUCHE

     BRUCHE RXT TBT ;

   OBJET :

La procedure BRUCHE est une procedure interne appelee par EXECRXT

   Commentaires

   RXT TABLE :
   TBT TABLE :

## BRUI [Mathematiques Statistiques]
    Operateur BRUI
    -------------- ALEA

    RESU1 = 'BRUI' 'BLAN' MOT1 FLOT1 FLOT2 | LREEL1 (COUL1)| (ENTI3) ;
    ou

    RESU1 = 'BRUI' 'BLAN' 'POIS' ENTI1 ENTI2 (ENTI3) ;

    Objet :

    1e SYNTAXE : selon les donnees, l'operateur BRUI construit un
        LISTREEL, un CHAMPOIN ou une EVOLUTIO dont les valeurs
        sont aleatoires.

    Commentaire :

    'BLAN' : mot-cle indiquant que les valeurs sont non correlees.

    MOT1 : type de repartition des valeurs, a choisir parmi les mots :
        'GAUS' gaussienne
        'UNIF' uniforme
        'EXPO' exponentielle

    FLOT1 : moyenne des valeurs generees (type FLOTTANT).
        Dans le cas EXPO, la moyenne ne sert a rien.

    FLOT2 : ecart-type (options 'GAUS' et 'EXPO') ou
        amplitude (option 'UNIF') (type FLOTTANT).

    ENTI2 : longueur du LISTREEL RESU1,
    ou
    LREEL1 : variable temps de l'EVOLUTION RESU1 (type LISTREEL),
    ou
    GEO1 : support geometrique du CHAMPOIN RESU1 (type MAILLAGE).

    COUL1 : Si LRREL1 est donne, couleur de la courbe representee par
        l'EVOLUTION (type MOT, 'BLAN' par defaut).

    ENTI3 : indice d'initialisation du generateur de nombre aleatoires
        (type ENTIER).

    RESU1 : resultat de type :
        - LISTREEL si ENTI1 est donne.
        - EVOLUTION si LRREL1 est donne.
        - CHPO1 si GEO1 est donne.

    2e SYNTAXE : l'operateur BRUI construit un LISTENTI dont les valeurs
        aleatoires suivent une distribution de Poisson.

    Commentaire :

    'BLAN' : mot-cle indiquant que les valeurs sont non correlees.

    'POIS' : mot-cle indiquant que les valeurs suivent une distribution
        de Poisson.

    ENTI1 : valeur moyenne de la distribution.

    ENTI2 : longueur du LISTENTI RESU1.

    ENTI3 : indice d'initialisation du generateur de nombre aleatoires
        (type ENTIER).

    RESU1 : resultat, LISTENTI de valeurs aleatoires suivant une
        distribution de Poisson.

    Remarques :

    1) L'indice ENTI3 permet de sauter ENTI3 termes du generateur
de nombres aleatoires. Cette option est a utiliser dans le cas
d'une reprise de calcul car le generateur est reinitialise
a chaque lancement de castem.

    2) Les appels consecutifs a l'operateurs BRUI au sein d'une meme
execution (a l'interieur d'une boucle par exemple) generent des series
de valeurs distinctes. Mieux vaut laisser le generateur se debrouiller
seul et ne pas preciser ENTI3 au moment de l'appel.

## BSIG [Fluides Resolution]
Operateur BSIGMA

  FORC1 = BSIGMA ('NOER') MODL1 SIG1 ( CAR1 ) (HOO1) ;

Objet :

L'operateur BSIGMA calcul le champ de forces nodales resultant de
l'integration d'un champ de contraintes.

  Commentaire :

 'NOER' : mot-cle indiquant de ne pas faire d'erreur en cas de
        changement de signe du jacobien. Dans ce cas, en
        sortie FORC1 contient un entier non nul.

  MODL1 : Objet modele ( type MMODEL ).

  SIG1 : champ de CONTRAINTES (type MCHAML, sous-type
        CONTRAINTES)

  CAR1 : champ de caracteristiques geometriques (type MCHAML,
        sous-type CARACTERISTIQUES) necessaire pour certains
        elements (poutres ,coques...).
        Il contient egalement les caracteristiques materielles
        pour l'element coque DST dans l'absence du champ de
        matrices de Hooke.
        Il contient les coefficients de phases d'un modele
        MELANGE PARALLELE quand le champ de contraintes
        contient les pseudo-contraintes associees a chacune
        des phases et non les contraintes globales.

  HOO1 : champ de matrices de Hooke necessaire pour l'element
        coque DST si CAR1 ne contient pas les caracteristiques
        materielles (type MCHAML, sous-type MATRICE DE HOOKE)

  FORC1 : champ de forces nodales (type CHPOINT)

## CABL [Mecanique Modele]
Operateur CABLE

RIG1 = CABLE GEO1 FLOT1 FLOT2;

Objet :

L'operateur CABLE permet de calculer la rigidite d'un cable

Commentaire :

GEO1 : support geometrique du cable (type MAILLAGE)
        ce support geometrique doit etre un element de type SEG2

FLOT1 : force correspondant a un allongement EPS1 exprime en %
        (type FLOTTANT)

FLOT2 : allongement (en %) du cable correspondant a la
        force FORC1 (type FLOTTANT)

RIG1 : rigidite du cable (type RIGIDITE)

## CALACTIV [Multi-physique Multi-physique] (proc)
  Procedure CALACTIV
  ------------------ COAC

CHP1 = CALACTIV TAB1 TAB2 LENT1 ;

      Objet
      Cette procedure calcule l'activite d'especes, dans une solution
      chimique, apres utilisation des operateurs CHI1 et CHI2.

      Commentaires
      TAB1 : table de soustype CHIMI1. Resultat de l'operateur CHI1.
      TAB2 : table de soustype CHIMI2. Resultat de l'operateur CHI2.
      LENT1: LISTENTI liste des identificateurs des especes pour
        lesquelles on veut faire le calcul.
      CHP1 : objet de type CHPOIN ayant une composante pour chaque
        espece de LENT1. Il contient l'activite de chaque espece
        en chaque point du maillage considere.

## CALCDISP [Multi-physique Multi-physique] (proc)
    Operateur CALCDISP

    dif_disp = CALCDISP QELEM DISPL DISPT ;

 ---------PROCEDURE DE CALCUL DE LA DISPERSIVITE------------------

 APPELE PAR TRANSGEN

|-----------------------------------------------------------------|
| Generalites : CALCDISP calcule le tenseur de dispersion  |
|  du probleme de transport convection-diffusion.  |
|-----------------------------------------------------------------|
|  |
|-----------------------------------------------------------------|
|  ENTREES  |
|-----------------------------------------------------------------|
|  |
| DISPL  : coefficient longitudinal de dispersivite  CHPO  |
|  |
| DISPT  : coefficient transverse de dispersivite CHPO  |
|  |
| QELEM  : vitesse au centre de chaque element CHPO - VX VY VZ  |
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
|  |
|  |
| dif_disp : C'est le tenseur de dispersion  |
|  composantes K11 K21 K22 K31 K32 K33  |
|  |
|  |
|******************************************************************

## CALCP [Multi-physique Multi-physique] (proc)
  Procedure CALCP

  Cph2 Cphe Cpo2 Cpn2 Cpco2 Cpco Cpair = CALCP T ;

  OBJET :

Procedure donnant la chaleur specifique a pression constante (Cp)
des gaz suivants : H2 , He , 02 , N2 , CO2 , CO , Air.

  Commentaires

    T : est la temperature en Celsius
        et peut etre un CHPOINT ou un FLOTTANT ou un LISTREEL.
    Cpi : est la chaleur specifique a pression constante en J/kg/K
        et est du meme type que la temperature d'entree
        pour chacun des gaz enumeres.

## CALCTRAC [Fluides Modele] (proc)
   Operateur CALCTRAC

   CALCTRAC MoDARCY Difftot' Cini nomespec nbespece LMLump
        (matrtr) TABRES Tbdartra CHCLIM;

 APPELE PAR TRANGEOL

|-----------------------------------------------------------------|
| Generalites : CALCTRAC calcule les traces de concentration  |
|  associees a la donnee de concentrations initiales |
|  Les Conditions limites de flux et de concentration|
|  sont pris en compte.  |
|-----------------------------------------------------------------|
|  |
|-----------------------------------------------------------------|
|  ENTREES  |
|-----------------------------------------------------------------|
| MoDARCY  : modele Darcy.  |
|  |
| Difftot  : Coefficient de diffusion totale, integre decentrement|
|  |
| Cini  : Concentration initiale, CHPOINT centre.  |
|  Composante 'H'.  |
|  |
| nomespec : liste des noms de composante des especes dans Cini  |
|  |
| nbespece : nombre de composante de Cini, soit nombre d'especes  |
|  |
| LMLump  : Logique. Si vrai on effectue une condensation de  |
|  masse de la matrice EFMH  |
|  |
| TABRES  : table contenant les options de resolution pour KRES  |
|  |
| TbDarTra : Table Darcy transitoire utilisee par MHYB, SMTP ...  |
|  |
| CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
|  Chpoint a n composantes contenant les conditions aux |
|  limites de Neumann et Dirichlet par espece.  |
|  |
|-----------------------------------------------------------------|
|  ENTREES-SORTIES  |
|-----------------------------------------------------------------|
|  |
| MatrTr  : matrice globale sur les traces, MATRIK. optionnel.  |
|  plus rapide si presente.  |
|  |
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
|  |
|  |
| Tcfin  : Trace de concentration aux faces (une composante par  |
|  espece chimique)  |
|  |
|*****************************************************************

## CALCULER [Mecanique Modele] (proc)
Procedure CALCULER

CALCULER ;

Objet :

Cette procedure permet une saisie assistee des donnees necessaires
pour effectuer un calcul de structures bidimensionnelles en elas-
ticite lineaire.

## CALLM [Multi-physique Multi-physique] (proc)
  Procedure CALLM
  --------------- CALMU

  Lmh2 Lmhe Lmo2 Lmn2 Lmco2 Lmco Lmvap Lmair = CALLM T ;

  OBJET :

Procedure donnant la conductivite thermique fonction de la temperature
pour les gaz suivants : H2, He, 02, N2, CO2, CO, H2Ovapeur, Air.

  Commentaires

    T : est la temperature en Kelvin
        et peut etre un CHPOINT ou un FLOTTANT ou un LISTREEL.
    Lmi : est la conductivite thermique en W/m/K
        et est du meme type que la temperature d'entree
        pour chacun des gaz enumeres.

## CALMU [Multi-physique Multi-physique] (proc)
  Procedure CALMU

  Muh2 Muhe Muo2 Mun2 Muco2 Muco Muvap Muair = CALMU T ;

  OBJET :

Procedure donnant la viscosite dynamique en fonction de la temperature
pour les gaz suivants : H2 , He , 02 , N2 , CO2 , CO , H2O , Air.

  Commentaires

    T : est la temperature en Kelvin
        et peut etre un CHPOINT ou un FLOTTANT ou un LISTREEL.
    Mui : est la viscosite dynamique en Kg/m/s
        et est du meme type que la temperature d'entree
        pour chacun des gaz enumeres.

## CALP [Mecanique Resolution]
 Operateur CALP
 -------------- EPSI CARA

 Cet operateur a plusieurs fonctions selon les donnees.

 | 1 Fonction |

 CHAM2 = CALP MODL1 CHAM1 (MOT1) ;

 Objet :

 L'operateur CALP (CALcul en Peau) calcule un champ de contraintes
 ou de deformations au sens des milieux continus,a partir d'un champ
 de contraintes ou de deformations generalisees calcule dans des
 elements de coque (COQ3, COQ2, DKT, COQ4 ou DST),
 ou de poutre (POUT ou TIMO).

 Dans le cas des coques, ce calcul est effectue aux points obtenus
 par projection des points supports soit dans le plan moyen de la
 coque, soit en peau superieure ou en peau inferieure. Lorsque les
 coques possedent plusieurs points d'integration dans l'epaisseur,
 l'operateur ne fait qu'extraire les valeurs aux points appropries.

 L'operateur n'effectue pas de rotation du tenseur de contraintes
 dont les composantes s'expriment donc dans les memes reperes dans
 lesquels etaient exprimees les contraintes generalisees (dans les
 reperes locaux). Si on veut obtenir les contraintes exprimees
 dans le meme repere sur un ensemble d'elements, il convient
 d'appliquer l'operateur RTEN sur le champ des contraintes avant
 d'utiliser CALP.

 Dans le cas des poutres, ce calcul est effectue en des points
 dont on donne les coordonnees dans le repere local.

 Les contraintes ainsi obtenues sont exprimees dans le repere
 local : l'axe X est parallele a l'axe de la poutre, le plan XY
 est defini par le vecteur contenu dans la composante VECT du
 champ des caracteristiques.

 Commentaire :

 CHAM1 : champ de contraintes ou de deformations generalisees
        (type MCHAML, sous-type CONTRAINTES ou DEFORMATIONS)

 CARA1 : champ de caracteristiques geometriques (type MCHAML)
        devant contenir obligatoirement l'epaisseur pour les
        coques et les donnees suivantes pour les poutres :
        'DY ' : coordonnee y du point ou l'on veut le resultat
        'DZ ' : coordonnee z du point ou l'on veut le resultat
        'SECT' : section droite
        'INRY' : moment d'inertie par rapport a l'axe local OY
        'INRZ' : moment d'inertie par rapport a l'axe local OZ

 MODL1 : objet modele (type MMODEL)

 MOT1 : mot-cle qui indique pour les coques ou l'on veut calculer
        le resultat:

        'SUPE' pour la peau superieure
        'MOYE' pour le plan moyen (par defaut)
        'INFE' pour la peau inferieure

 CHAM2 : champ de contraintes ou de deformations (type MCHAML,
        sous-type CONTRAINTES ou DEFORMATIONS)

 Remarques :

 1. Dans le cas des poutres la contrainte de cisaillement due au
moment de torsion n'est pas traitee .

 2. Dans le cas des coques avec cisaillement transverse, ce
cisaillement est la valeur moyenne sur l'epaisseur quel que soit
l'endroit ou l'on calcule les contraintes.

 | 2 eme Fonction  |

 CHAM2 = CALP MODL1 CHAM1 CARA1 ;

 Objet:

 Projection d un champ de temperature defini sur un massif sur
 nouveau modele de coque

 CHAM1 : champ par elements (type MCHAML) de TEMPERATURE defini
        sur un objet massif

 CARA1 : Caracteristiques associees au modele MODE (type MCHAML)

 MODL1 : modele MMODEL sur des elements de coques

 CHAM2 : objet resultant de la projection champ par
        elements de composantes TINF T et TSUP associees
        aux temperatures de la peau interne de la couche mediane et
        de la peau externe

 Remarque :

 Le Mchaml d origine doit obligatoirement etre defini sur un massif

## CAMPBELL [Mecanique Dynamique] (proc)
Procedure CAMPBELL

 Calcule le diagramme de Campbell d'une machine tournante.
 Le diagramme peut etre calcule dans le repere fixe
 (diagramme classique pour des modelisation de type poutre
 avec couplage gyroscopique)
 ou dans le repere tournant (evolution des frequences en tenant compte
 des raideurs centrifuges, de precontrainte et du couplage de Coriolis)

 CAMPBELL TAB1 PRFREQ

PRFREQ: LISTREEL contenant les vitesses de rotation pour lesquelles
        on calcule le diagramme de Campbell

TAB1 Table contenant:

1/ Si l'utilisateur a deja calcule la base modale:
   TAB1.'BASE_MODALE': Table contenant la base de modes reels utilisees
        (table generee par VIBR avec l'option TBAS)

2/ Si l'utilisateur desire calculer la base modale pour chaque vitesse de rotat
  (utile pour la prise en compte de la raideur de precontrainte et la raideur c
   TAB1.'NMODES' : Nombre de modes a calculer
   TAB1.'FREQ_PROCHE': Valeur de frequence autour de laquelle seront cherches
        les modes propres

   Les matrices de masse, de raideur, d'amortissement et de couplage
   gyroscopique peuvent etre donnees deja projetees sur la base de
   modes reels ou non:

   TAB1.'MASS_PROJ': Matrice de masse projetee sur les modes reels utilises
   TAB1.'MASSE': Matrice de masse

   TAB1.'RIGI_PROJ': Matrice de rigidite projetee sur les modes reels utilises
   TAB1.'RIGIDITE': Matrice de rigidite

   TAB1.'AMOR_PROJ': Matrice d'amortissement projetee sur les modes reels
        utilises
   TAB1.'AMORTISSEMENT': Matrice d'amortissement

Pour les diagrammes de Campbell classique (dans le repere fixe)

   TAB1.'KROT_PROJ': Matrice de raideur antisymetrique due a l'amortissement
        corotatif projetee sur les modes reels utilises
   TAB1.'KROTATIF': Matrice de raideur antisymetrique due a l'amortissement
        corotatif

   TAB1.'GYRO_PROJ': Matrice de couplage gyrsocopique projetee sur
        les modes reels utilises
   TAB1.'GYROSCOPIQUE': Matrice de couplage gyrsocopique pour une vitesse
        de rotation unite

Pour les diagrammes de Campbell dans le repere tournant

  TAB1.'CORI_PROJ': Matrice de couplage de Coriolis projetee sur les modes reel
  TAB1.'CORIOLIS': Matrice de couplage de Coriolis pour une vitesse de rotation

  TAB1.'KSIG_PROJ': Matrice de raideur de precontrainte projetee sur les modes
  TAB1.'KSIGMA': Matrice de raideur de precontrainte pour une vitesse de rotati

  TAB1.'KCEN_PROJ': Matrice de raideur centrifuge projetee sur les modes reels
  TAB1.'KCENT': Matrice de raideur centrifuge pour une vitesse de rotation unit

    Les matrices de couplage gyroscopique, de raideur de precontrainte et de ra
    doivent etre donnees pour une vitesse de rotation unite
     (1 Hz, 1 rad/s ou 1 tour/min selon le choix de l'utilisateur)

   TAB1.'AFFICHAGE': VRAI si on veut afficher les frequences de rotation
        au cours du calcul

  TAB1.'CLASSEMENT':VRAI si on veut classer les modes directs(pulsation reelle>
        et les modes retrogrades (pulsation reelle <0)

  TAB1.'AXE_DIRECT': Vecteur parallele a la vitesse de rotation necessaire pour
        definir les sens direct et retrograde

  OUTPUT

 TAB1. i Table contenant les resultats pour le mode complexe i
        (N modes reels donnant 2N modes complexes)
   (TAB1. i). 'FREQUENCE_REELLE' : Evolution donnant la frequence reelle
        en fonction de la frequence de rotation
   (TAB1. i). 'FREQUENCE_IMAGINAIRE': Evolution donnant la frequence imaginair
        en fonction de la frequence de rotation
   (TAB1. i). 'FREQUENCE_MODULE' : Evolution donnant le module de la frequence
        en fonction de la frequence de rotation
   (TAB1. i). 'AMORTISSEMENT' : Evolution donnant l'amortissement en fonction
        de la frequence de rotation

PRFREQ: LISTREEL contenant les frequences de rotation (Hz, rad/s ou autre unit
        pour lesquelles on calcule le diagramme de Campbell

Remarque:
        Pour chaque frequence de rotation, les frequences et amortissements
        sont classes par ordre croissant. La ligne i correspond donc
        a la frequence ieme par ordre croissant (pas de suivi de mode).
        Pour un meme point, l'amortissement et les frequences
        peuvent aussi correspondre a des modes differents.

## CAPA [Mecanique Modele]
Operateur CAPACITE

CAP1 = CAPACITE MMODE1 CAR1 ( TAB1 ) ;

        TAB1.'SOUSTYPE' .'CHALEUR LATENTE'
        .'TPHASE 1'.'TPHASE 2'
        .'CHAMP THERMIQUE 1'
        .'CHAMP THERMIQUE 2'

Objet :

L'operateur CAPACITE cree une matrice de capacite calorifique.

Commentaire :

MMODE1 : structure modelisee (type MMODEL)

CAR1 : objet contenant les caracteristiques physiques de la
        structure (type MCHAML, sous-type CARACTERISTIQUES)

TAB1 : table (type TABLE) contenant les renseignements pour le
        changement de phase, avec les indices suivants :

  'SOUSTYPE' : 'THERMIQUE' (type MOT)

  'CHALEUR LATENTE' : chaleur latente du changement de phase
        (type FLOTTANT)
  'TPHASE 1' : temperature 1 de changement de phase
        (type FLOTTANT)
  'TPHASE 2' : temperature 2 de changement de phase
        (type FLOTTANT)
  'CHAMP THERMIQUE 1': temperature au debut du pas
        (type CHPOINT)
  'CHAMP THERMIQUE 2': temperature a la fin du pas
        (type CHPOINT)

CAP1 : matrice de capacite calorifique (type RIGIDITE)

Remarque :

Dans le cas general la matrice de capacite est l'integrale sur le
domaine de tN . RHO . C . N . DV ou N est la matrice
des fonctions de forme.

Le changement de phase se fait entre les temperatures TPHASE 1
et TPHASE 2 entrainant une variation lineaire d'enthalpie massique de
CHALEUR LATENTE + C.(TPHASE 2 - TPHASE 1) ou C est la capacite
fournie dans le champ CAR1. Les temperatures TPHASE 1 et TPHASE 2
doivent etre differentes.

Lorsque TAB1 est specifie la matrice de capacite est obtenue comme
la derivee de l'enthalpie volumique entre les distributions
thermique CHAMP THERMIQUE 1 et CHAMP THERMIQUE 2.

## CAPI [Mecanique Resolution]
   Operateur CAPI

   CH2 =  CAPI |  -  | MODL1 CH1 DEP1 (DEP2);
        | 'JAUM' |
        | 'UTIL' |

   Objet :

1. Par defaut (pas de mot-cle), l'operateur CAPI transforme :
   - un champ de contraintes de Cauchy
     en un champ de contraintes de Piola-Kirchhoff de seconde espece
   - ou un champ de deformations d'Almansi-Euler
     en un champ de deformations de Green-Lagrange.

2. En presence du mot-cle 'JAUM' (Jaummann), l'operateur CAPI effectue
   un changement de repere sur le champ pour passer du repere
   general au repere corotationnel.

3. En presence du mot-cle 'UTIL' (utilisateur), CAPI ne fait rien.

  Commentaire :

  MODL1: objet de type MMODEL.

  CH1 : champ de contraintes/deformation avant transformation
        (type MCHAML, sous-type CONTRAINTES/DEFORMATIONS)

  DEP1 : champ de deplacements qui permet de passer de la configuration
        de reference a la configuration actuelle (type CHPOINT)

  DEP2 : pour la XFEM, champ de deplacements qui permet de passer
        de la configuration ou la fissure est fermee
        a la configuration de reference (type CHPOINT)

  CH2 : champ de contraintes apres transformation
        (type MCHAML, sous-type CONTRAINTES/DEFORMATIONS)

## CARA [Mecanique Modele]
  Operateur CARACTERISTIQUE
  ------------------------- MATE

  CAR1 = CARA MODL1 NOMCi VALi ... ;

  Objet :

  L'operateur CARA permet de construire le MCHAML CAR1 decrivant
  des caracteristiques qui ne peuvent pas etre deduites du maillage.
  Ces proprietes vont caracteriser l'objet MMODEL MODL1.

  Commentaire :

  MODL1 : objet modele (type MMODEL)

  NOMCi : nom de la ieme composantes (type MOT)

  VALi : valeur de la ieme composante (type FLOTTANT)

  CAR1 : objet contenant les caracteristiques geometrique (type
        MCHAML , sous-type CARACTERISTIQUES)

 | Noms des caracteristiques pour les elements massifs |

 ('DIM3') : epaisseur dans le cas des contraintes planes

 ('REND') : rendement du materiau

  --- Cas isotrope : 'ISOTROPE' : mot-cle
        FLOTT : type FLOTTANT, valeur de la grandeur
| Noms des caracteristiques pour les elements COQ2, COQ3, COQ4, DKT,
        DST

 'EPAI' : epaisseur de la coque
 ('CALF') : coefficient utilise dans le critere de plasticite
        (par defaut 2/3)
 ('EXCE') : excentrement du plan moyen de la coque par rapport au
        plan de reference, compte positif dans le sens de la
        normale (non disponible pour COQ3)
 ('DIM3') : epaisseur dans l'autre direction (cas des COQ2 en
        contraintes planes)

 | Noms des caracteristiques pour les elements COQ6, COQ8 |

 'EPAI' : epaisseur de la coque
 ('EXCE') : excentrement par rapport au plan moyen, compte positif
        dans le sens de la normale

 | Noms des caracteristiques pour un element POJS, SEGS, QUAS ou TRIS |

 La section est decrite dans le plan xOy. L'axe Ox du repere de
 description de la section est l'axe local Oy de l'element TIMO.

 'ALPY' : coefficient qui multiplie la contrainte de cisaillement
        sxy (Ox et Oy sont des axes locaux de l'element TIMO).

 'ALPZ' : coefficient qui multiplie la contrainte de cisaillement
        sxz (Ox et Oz sont des axes locaux de l'element TIMO).

 Ces coefficients dans le cas d'une section homogene peuvent etre
 definis d'apres la theorie de Timoshenko.

 | Noms des caracteristiques pour les elements de joint generalise |

 ('EPAI') : epaisseur du joint

 | Noms des caracteristiques pour un element BARR ou BAR3  |

 'SECT' : section droite

 | Noms des caracteristiques pour un element BAEX |

 'SECT' : section droite
 'EXCZ' : excentrement suivant l'axe local z
 'EXCY' : excentrement suivant l'axe local y
 'VX ' : composante x du vecteur orientant l'axe local Oy
 'VY ' : composante y du vecteur orientant l'axe local Oy
 'VZ ' : composante z du vecteur orientant l'axe local Oy

 | Noms des caracteristiques pour un element CERCE |

 'SECT' : section droite

 | Noms des caracteristiques pour un element POUTRE ou TIMO |

  Les caracteristiques de la poutre sont definies dans le repere local
  de l'element (Ox axe de la poutre oriente du premier point vers
  le second, Oy axe defini si necessaire par l'utilisateur,
  Oz completant le repere). Il faut que les axes Oy Oz soient des axes
  pricipaux de la section car on ne definit pas les moments d'inertie
  croisees (sauf poul l'element TIMO avec un modele SECTION)

  'SECT' : section droite
  'INRY' : moment d'inertie par rapport a l'axe local Oy
  'INRZ' : moment d'inertie par rapport a l'axe local Oz
  'TORS' : moment d'inertie de torsion
  ('SECY') : section reduite a l'effort tranchant selon l'axe local
  ('SECZ') : section reduite a l'effort tranchant selon l'axe local
  ('VECT') : mot-cle permettant de definir l'axe local Oy. Il doit
        etre suivi par un vecteur appartenant au plan xOy
        (objet de type POINT).
  ('DX  ') | : 3 distances permettant de calculer des contraintes a
  ('DY  ') |  partir des moments, pour le critere de plasticite
  ('DZ  ') |  (cf VMIS).
  ('OMEG') |  Vitesse de rotation de la poutre autour de son axe (en rad/s).
        Utilise pour calculer la matrice de couplage gyroscopique.

  Par defaut, les sections SECY et SECZ sont prises egales a SECT pour
  l'element TIMO et pour les elements POUTRE on neglige l'energie
  de deformation de cisaillement (cela revient a imposer des valeurs
  infinies pour les sections reduites)

 | Noms des caracteristiques pour un element TUYAU |

  Cet element sert a representer des portions de tuyau droit ou de
  coude, la differenciation se faisant par le rayon de courbure.
  Les caracteristiques du tuyau sont definies dans le repere local de
  l'element, de la Meme façon que pour l'element POUTRE.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CARB [Fantome]
Opérateur CARB

Objet :

Cet opérateur a été débranché.
Se reporter à l'opérateur CARA(CTERISTIQUES).

## CBLO [Fluides Limites]
    Operateur CBLO

    TAB2 = CBLO TAB1 FLOT1;

    Objet :

    L'operateur CBLO genere une table TAB2 (type TABLE) de blocs
compatibles a partir de la table TAB1 de bloc incompatibles, a la
tolerance FLOT1 (type FLOTTANT) pres.

    Remarques :

  - TAB1 est un table de 'SOUSTYPE' 'LISTE_DE_BLOCS'. Les autres indices
de TAB1 sont tous des entiers et pointent sur des objets de type MAILLAGE
formant un bloc (2D) ou sur des tables de 'SOUSTYPE' 'LISTE_DE_FACES'.

  - En 2D un bloc est une suite ordonnee de point (elements de type POI1)
qui permet de genere le contour du bloc.

 P2 +--------------+ P3
    |  |
    |  |
    |  BLOC1  |  Par exemple on a BLOC1=P1 et P2 et P3 et P4
    |  |  ou BLOC1=P1 et P4 et P3 et P2
    |  |
 P1 +--------------+ P4

  - Deux blocs contigus sont dits compatibles si tous les elements de
leurs contours en regard sont geometriquement identiques

 P2 +--------------+ P3
    |  |
    |  |
    |  BLOC1  |  Par exemple BLOC1(=P1 et P2 et P3 et P4 et P5)
    |  |  est compatible avec BLOC2(=Q1 et Q2 et Q3 et Q4
 P1 |  P5  | P4  et Q5) si P4 et Q4 d'une part
    +------+-------+-------------+ et P5 et Q5 d'autre part sont
        Q5 |  Q4  | Q3  des points differents occupant
        |  |  la meme position a TOL2 pres.
        |  BLOC2  |
        |  |
        |  |
        Q1 +---------------------+ Q2

  - En 3D un bloc est un ensemble de faces contenu dans la table
de 'SOUSTYPE' 'LISTE_DE_FACES'. Les autres indices de cette table sont
tous des entiers et pointent sur des objets de type MAILLAGE formant
une face. Chaque face est decrite par un contour ferme de SEG2 ne
comportant aucun trou.

## CCDONCHI [Multi-physique Multi-physique] (proc)
   Procedure CCDONCHI
   ------------------ CHI2 DONCHI2

OBJ4 = CCDONCHI TAB1 MOT1 OBJ1 (OBJ2) (OBJ3) ...(OBJn) ;

      Objet
      Cette procedure permet de grouper sur un maillage des objets
      de classe DONCHI2 calcules sur differents sous maillages.
      Les differents maillages sont consideres dans l'ordre dans
      lequel ils sont donnes.
      Commentaires
      TAB1 : table de sous type DOMAINE.
      MOT1 : mot precisant le support geometrique des CHPOINTS
        pour le domaine considere: SOMMET
        FACE
        CENTRE
      OBJ1 OBJ2 .. OBJn:
        Objets de type DONCHI2 definis sur des sous maillages
        de celui sur lequel est defini TAB1.
      OBJ4 : Objet de type DONCHI2 resultat.

## CCON [Maillage Manipulation]
Operateur CCON

TAB1 = CCON ( | 'STR1' | ) MAIL1 ;
        | 'STR2' |

| CET OPERATEUR EST OBSOLETE ET SERA SUPPRIME DANS LES PROCHAINES |
| VERSIONS  |
|  |
| SES FONCTIONNALITES ONT ETE INCLUSES DANS L'OPERATEUR PART QUI  |
| EST PLUS GENERAL  ====  |

Objet :

L'operateur CCON separe les composantes connexes d'un maillage et
les met dans un objet TABLE indice par des entiers 1, 2, 3...

En presence du mot-cle 'STR1' (cas des lignes), les points
appartenant a plus de deux elements separent les composantes
connexes.

En presence du mot cle 'STR2' (cas des surfaces), la connexion
entre voisins s'effectue par les aretes, et uniquement si celles-ci
n'appartiennent pas a plus de deux elements.

## CER3 [Maillage Lignes]
    Operateur CER3

   GEO1 = CER3 (N1) POIN1 POIN2 POIN3 ('DINI' DENS1) ('DFIN' DENS2) ;

    Objet :

    L'operateur CER3 permet de construire un arc de cercle passant par
trois points.

    Commentaire :

    POIN1 |
    POIN2 | : points permettant de definir l'arc de cercle(type POINT)
    POIN3 |

    N1 : nombre d'elements generes (type ENTIER)

    DENS1 | :densites associees aux points POIN1 et POIN3(type FLOTTANT
    DENS2 |

    GEO1 : arc de cercle (type MAILLAGE)

    Remarque :

    Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
    Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.
    Si N1 est negatif, N1 elements seront engendres et leurs tailles
seront calculees en tenant compte des densites des extremites.

    Si les densites associees aux points POIN1 et POIN3 ne sont pas
correctes, il est possible de les surcharger. Pour le premier point, il
faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour le
troisieme point, derriere le mot-cle 'DFIN'.

    Si une ligne LIG1 est donnee a la place du point POIN1 (ou POIN3),
cette ligne est prolongee jusqu'au point POIN3 (la ligne commence au
point POIN3).
    Si le point POIN3 n'est pas donne, la premiere extremite de la
ligne LIG1 est consideree, ce qui permet de fermer celle-ci.

## CERC [Maillage Lignes]
 Operateur CERCLE

 GEO1 = CERC (N1) ('DINI' DENS1) ('DFIN' DENS2) ...

        ... | ('CENTR')  POIN1 CENTR2 POIN3 ;
        |  'PASS'  POIN1 POIN2  POIN3 ;
        |  'ROTA'  FLOT1 POIN1 POIN2 (POIN3) ('ELIM');

 (C est aussi admis a la place de CERC)

 Objet :

 L'operateur CERC permet de construire un arc de cercle GEO1. Trois
 syntaxes sont disponibles : 'CENTR' (par defaut), 'PASS' et 'ROTA'.

 Commentaire communs :

 N1 : nombre d'elements generes (type ENTIER)

 DENS1 | : densites associees aux points POIN1 et POIN3
 DENS2 |  (type FLOTTANT)

 Syntaxe 'CENTR' :

 POIN1 | : points extremite de l'arc de cercle (type POINT)
 POIN3 |

 CENTR2 : centre du cercle (type POINT)

 GEO1 : arc de cercle (type MAILLAGE) de centre CENTR2,
        construit entre les points POIN1 et POIN3.
        Par convention, l'arc construit est l'arc le plus court.
        On ne peut pas construire de demi-cercle.

 Syntaxe 'PASS' :

 POIN1 | : points de l'arc de cercle (type POINT)
 POIN2 |
 POIN3 |

 GEO1 : arc de cercle (type MAILLAGE) passant par les points POIN1
        POIN2 et POIN3.

 Syntaxe 'ROTA' :

 FLOT1 : angle de rotation en degre (type FLOTTANT)

 POIN1 : points extremite initiale de l'arc de cercle (type POINT)

 POIN2 | : points definissant l'axe de rotation (type POINT)
(POIN3)|  (POIN3 est inutile en 2D)

 'ELIM' : identification du point final comme etant le point initial
        (possible seulement si FLOT1=360 degres)

 GEO1 : arc de cercle (type MAILLAGE) engendr\'e par la rotation
        de POIN1 autour de l'axe defini par POIN2 et POIN3.

 Remarque 1 :

 Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
 tailles seront calcules en fonction des densites des extremites.
 Si N1 est specifie et positif, N1 elements d'egale longueur
 seront engendres.
 Si N1 est negatif, N1 elements seront engendres et leurs tailles
 seront calculees en tenant compte des densites des extremites.

 Remarque 2 :

 Si les densites associees aux points des extremites ne sont pas
 correctes, il est possible de les surcharger. Pour le premier
 point, il faut donner la bonne valeur derriere le mot-cle 'DINI'
 et, pour le deuxieme point, derriere le mot-cle 'DFIN'.

 Remarque 3 :

 Si une ligne LIG1 est donnee a la place du point POIN1, GEO1 sera
 constitue de la ligne LIG1 prolongee par un arc de cercle jusqu'au
 point POIN3.
 De meme, si une ligne LIG3 est donnee a la place de POIN3, GEO1
 sera constitue de l'arc de cercle joignant POIN1 au premier point
 de LIG3 prolongee par LIG3.
 Si une ligne LIG1 est donne a la place des points POIN1 et POIN3,
 alors l'arc de cercle joindra les deux extremites de LIG1, ce qui
 permet de fermer celle-ci.

## CFL [Fluides Modele]
    Operateur CFL
    -------------- CSON

     CHAM4  =  'CFL'  MODL1  |  MATR1
        |
        |  ( CARA1 ) 'CSON' CHAM2
        |
        |  MATR2  'TAILLE'  CHAM3 ;

    Objet :

    L'operateur CFL permet de determiner le pas de temps de la
condition CFL (Courant Friedriech Levy) pour chaque element d'un
modele de comportement. Les deux options permettent de fournir
directement la taille ou la celerite du son dans un materiau.

      Commentaire :

      MODL1 : objet modele ( type MMODEL ).

      MATR1 : objet de type MCHAML de sous-type CARACTERISTIQUES,
        decrivant les parametres du modele de comportement
        (obtenu avec l'operateur MATE) ainsi que les cara-
        cteristiques geometriques d'eventuels elements coques
        ou poutres (obtenu avec l'operateur CARA).

      MATR2 : objet de type MCHAML de sous-type CARACTERISTIQUES,
        decrivant les parametres du modele de comportement
        (obtenu avec l'operateur MATE).

      CHAM2 : objet de type MCHAML definissant la celerite du son
        au centre de gravite de l'element nom de composante
        'CSON' . (obtenu avec l'operateur CSON)

      CHAM3 : objet de type MCHAML definissant la taille de
        propagation de l'information d'un noeud vers des
        elements non adjacents (composantes 'L' pour
        les elements massifs et 'L2H' pour les elements
        coques ou poutres).

      CHAM4 : objet resultat de type MCHAML defini au centre des
        de gravite des elements de composante 'TCFL' .

    Remarque :

  La condition CFL s'ecrit alors avec l'operateur 'MINI' qui va
calculer le minimum du champ par element CHAM4. Ce minimum constitue
un minorant du pas de stabilite pour les algorithmes explicites.

## CFND [Mathematiques Autres]
    Operateur CFND

      CHP2 = CFND CHP1 MOD1 ;

    Objet :

    L'operateur CFND modifie le champ par point CHP1 pour le
rendre compatible avec les relations de conformites incluses dans
le modele MOD1.
    Cet operateur est appele par la procedure CH_THETA.

## CH2CLIM [Multi-physique Multi-physique] (proc)
Methode CH2CLIM
--------------- DONCHI1 CHDCLIM

 CH2CLIM MOT1 LENT1

   Objet

La methode CH2CLIM charge un LISTENTI a l'indice MOT1
de l'element %CLIM d'un objet DONCHI1.
MOT1 est un mot pris dans la liste : TYP3 COMP3 TYP4 TYP5 TYP6

## CHAI [Langage Caracteres]
   Operateur CHAINE

   MOT1 = CHAINE  ('FORMAT' MOT2 ) OBJ1 |(*N)| ( OBJ2  .....)  ;

   Objet :

   L'operateur CHAINE permet de fabriquer un objet MOT1 de type MOT
   de 512 caracteres au plus.

   Commentaire :

   OBJi : objets de type MOT, ENTIER, FLOTTANT ou LOGIQUE

   MOT2 : format FORTRAN dans lequel on souhaite ecrire les flottants.
        On peut preciser le format pour chacun des flottants.
        MOT2 doit obligatoirement commencer et finir par des
        parentheses.
        Le format par defaut est '(1PE12.5)' (Cf. formats fortran)
        exemples
        '(A4)' : chaine de 4 caracteres
        '(I5)' : entier sur 5 chiffres
        '(F8.5)' : flottant sur 8 caracteres avec 5 decimales maxi
        sans exposant
        '(E12.5)' : flottant sur 12 caracteres avec 5 decimales maxi
        et exposant genre 'E5'
        '(D12.5)' : flottant sur 12 caracteres avec 5 decimales maxi
        et exposant genre 'D+05'

   Remarque :

   La chaine est fabriquee par concatenation des chaines de caracteres
   des objets OBJi de type MOT.

   Si OBJi est un objet de type ENTIER, FLOTTANT ou LOGIQUE, il est
   d'abord converti en chaine de caracteres.

   Pour les flottants, on prend en compte la derniere option FORMAT
   rencontree. Cette option doit etre utilisee avec precaution car une
   erreur de codage peut entrainer l'arret du programme.

   On peut par *N, <N, /N, >N demander que l'ecriture de l'objet OBJi
   place juste avant soit decale a droite (ou a gauche) sur la N-ieme
   colonne, en absolu ou en relatif :

   CHAI 'ABC' 'DEF'*10 ; ---> "ABC....DEF" (gauche/absolu)
   CHAI 'ABC' 'DEF'/10 ; ---> "ABC......DEF" (droite/absolu)
   CHAI 'ABC' 'DEF'<10 ; ---> "ABC.......DEF" (gauche/relatif)
   CHAI 'ABC' 'DEF'>10 ; ---> "ABC.........DEF" (droite/relatif)

   Exemples :

   1)
   PRESS = 25.86 ;
   ICAS = 2 ;
   AA=CHAINE ' CAS DE CHARGE NUMERO:' ICAS ' PRESSION :' PRESS;

CAS DE CHARGE NUMERO:2 PRESSION : 2.58600E+01

   2)
   AA=CHAINE ' CAS DE CHARGE NUMERO:' ICAS FORMAT '(F6.2)'
        ' PRESSION :' PRESS;

CAS DE CHARGE NUMERO:2 PRESSION : 25.86

   3)
   F1 = '(F6.2)' ;
   BB = CHAINE ' PRES1=' FORMAT F1 PRESS ' PRES2=' PRESS ' PRES3='
        FORMAT '(SP,1PE10.3)' PRESS ;

PRES1= 25.86 PRES2= 25.86 PRES3=+2.586E+01

   4)
   IJK=321; CC=CHAINE IJK*10 IJK*20;
        DD=CHAINE IJK/10 IJK/20;
   MESS CC ; MESS DD;

      321 321
        321 321

## CHAMINT [Fluides Resolution] (proc)
Operatueur CHAMINT

CH2 xstart = CHAMINT CH1 ;

utilise par TRANSGEN - pas pour utilisateur

CH1 chargement

CH2 chargement CH1 integre dans le temps

xstart valeur du temps a partir de laquelle
        le chargement est constant. Pour ne
        pas appele TIRE inutilement. Vaut
        le dernier temps si n'arrive jamais.

## CHAN [Langage Objets]
    Operateur CHANGER

    Cet operateur permet de changer un attribut ou le type d'un objet.
    Sa syntaxe generale est la suivante :

    OBJET1 = CHAN (MOT1) OBJET2 (OBJET3)(OBJET4) (OBJET..) (MOT2) (MOT3);

PART{Tableau de synthese des options}

|  |  |  |  |  |  |
|  OBJET1  |  MOT1  | OBJET2  | OBJET3  |  MOT2  | MOT3  |
|  |  |  |  |  |  |
|  MAILLAGE | (TYPE)  | MAILLAGE  (LISTENTI)  |
|  CHPOINT  |  'CHPO'  | CHPOINT  | (MMODEL)  |
|  CHPOINT  |  'CHPO'  | MCHAML  |  MMODEL  | ('MOYE')  |
|  | ('SOMM')  |
|  | ('SUPP')  |
|  CHPOINT  | 'ATTRIBUT' | CHPOINT  |  |'NATURE'  | 'INDETER'|
|  | 'DIFFUS' |
|  | 'DISCRET'|
|  CHPOINT  | 'COMP'  | CHPOINT  | MOT1  |  ...  |
|  | LISTMOT1 LISTMOT2 |  |
|  ...  | ( 'NATU' | 'INDETER'  |
|  | 'DIFFUS'  |
|  | 'DISCRET') |
|  CHPOINT  | 'TITR'  | CHPOINT  | MOT1  |
|  MCHAML  | 'NOEUD'  | MCHAML  | MMODEL  |
|  | 'GRAVITE'  |  |
|  | 'RIGIDITE' |  |
|  | 'MASSE'  |  |
|  | 'STRESSES' |  |
|  MCHAML  | 'CHAM'  | MCHAML  | MMODEL  | ('NOEUD')  | (TYP1)  |
|  | CHPOINT  | MMODEL  | ('GRAVITE') |  |
|  | ('RIGIDITE')|  |
|  | ('MASSE'  )|  |
|  | ('STRESSES')|  |
|  MCHAML  | 'CHAM'  | CHPOINT  | MAILLAGE  |
|  MCHAML  | 'COMP'  | MOT1  | CHE1  |
|  | LISTMOT1 LISTMOT2 |  |
|  MCHAML  |  'TYPE'  | MCHAML  |  |  TYP1  |
|  MCHAML  |  'CONS'  | MCHAML  |  |  MOT1  |
|  MMODEL  |  'CONS'  | MMODEL  |  |  MOT1  |
|  MATRIK  |  'INCO'  |  MATRIK  | LMOT1  LMOT2  LMOT3  LMOT4  |
|  |  MOT1  MOT2  MOT3  MOT4  |
|  RIGIDITE |  'INCO'  | RIGIDITE | LMOT1  LMOT2  LMOT3  LMOT4 | ... |
|  |  MOT1  MOT2  MOT3  MOT4 |  |
|  |  'COMPL'  |  |
|  ...  | ('SYME') |  |
|  | ('ANTI') | ('MULT')  |
|  | ('QUEL') |  |
|  RIGIDITE | 'TYPE'  |  RIGIDITE |  |  MOT1  |
|  RIGIDITE | 'DEPE'  |  RIGIDITE  |
| RIG1 RIG2 | 'COND'  | RIGIDITE  |
|  CHARGEME | 'TABL'  | CHARG1  MOT1  |  |
|  MOT  | 'MAJU'  | MOT  |  |
|  | 'MINU'  |  |
|  EVOLUTIO | 'TITR'  | EVOL1  |  -  | MOT1  |
|  | 'LEGE'  |  |  (k)  |  |
|  | 'NOMABS'  |  |  (k)  |  |
|  | 'NOMORD'  |  |  (k)  |  |

PART{Resultat de type MAILLAGE}

   -----------------> pour changer le type d'élément

     GEO2 = CHAN (TYPE) GEO1 (LENTI1) ;

   L'operateur CHAN construit un MAILLAGE GEO2 equivalent au MAILLAGE
   GEO1, mais forme d'elements du type demande TYPE (type MOT). Par
   defaut, on prend le type courant (cf OPTION).
   Si GEO1 est constitue d'elements quadratiques pour les fluides
   (complets) , TYPE peut prendre une des valeurs suivantes 'TRI3',
   'QUA4', 'TET4', 'PYR5', 'CUB8'.

   Si on donne pour TYPE le mot 'LIGNE', le maillage resultat est
   constitue uniquement de lignes.
   Si on donne pour TYPE le mot 'SURFACE', le maillage resultat est
   constitue uniquement d'elements triangulaires ou quadrangulaires,
   correspondant aux facettes des elements de GEO1.
   Si on donne pour TYPE le mot 'LINEAIRE' chaque element quadratique
   est remplace par un element lineaire.
   Si on donne pour TYPE le mot 'QUADRATIQUE' chaque element lineaire
   est remplace par un element quadratique.
   Si on donne pour TYPE le mot 'QUAF' chaque element 'QUADRATIQUE' est
   remplace par un element quadratique pour les fluides c'est a dire
   complet : TRI6 -> TRI7, QUA8 -> QUA9 CU20 -> CU27 etc.

   LENTI1 : Connectivite a etablir (type LISTENTI). GEO1 doit être de
        type POI1. GEO2 sera constitue d'autant d'elements que de
        N-uplets de connectivite dans LENTI1.

PART{Resultat de type CHPOINT}

   -----------------> a partir d'un MCHAML

    CHP2 = CHAN 'CHPO' MODL1 CHAM1 ( 'MOT1' );

   En presence du mot cle 'CHPO', l'operateur CHAN construit le CHPOINT
   CHPO2 a partir d'un nouveau champ par element CHAM1 (type MCHAML).

   Ce CHPOINT sera appuye sur les noeuds du maillage, sous-jacent au
   modele MODL1 (type MMODEL), en calculant :
   - la moyenne des valeurs aux noeuds des elements adjacents
     si MOT1 est egal a 'MOYE' (option par defaut),
   - ou la somme des contributions de chaque element aux noeuds
     si MOT1 vaut 'SOMM'.
   Ces valeurs aux noeuds sont determinees soit par extrapolation a
   partir des valeurs connues a l'interieur de l'element en cas de
   champ de sous-type SCALAIRE, en utilisant une methode de moindres
   carres et les fontions de forme de l'element, soit par moyenne
   directe de ces valeurs pour les champs de tout autre type.
   Le CHPOINT resultat est de nature diffuse.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CHANOLII [Multi-physique Multi-physique] (proc)
Methode CHANOLII
--------------- CHDCLIM

 CHANOLII MOT1 LENT1

   Objet

La methode CHANOLII charge l'objet LENT1 de type LISTENTI
dans l'element %MOT1 d'un objet CHDCLIM.

## CHANUOBJ [Multi-physique Multi-physique] (proc)
Methode CHANUOBJ
--------------- INDIOBJE

 CHANUOBJ ENTI1 OBJ1

   Objet

La methode CHANUOBJ charge l'objet OBJ1 de type OBJET
dans l'element %ENTI1 d'un objet INDIOBJE.

## CHANVCOM [Multi-physique Multi-physique] (proc)
Methode CHANVCOM
--------------- OBJE LINVCOMP

 CHANVCOM ENTI1 OBJ1

   Objet

La methode CHANVCOM charge l'objet OBJ1 de CLASSE LINVCOMP
a l'indice ENTI1 de l'element %NVCOMP d'un objet DONCHI1.

## CHANVESP [Multi-physique Multi-physique] (proc)
Methode CHANVESP
--------------- OBJE LIESPECE

 CHANVESP ENTI1 OBJ1

   Objet

La methode CHANVESP charge l'objet OBJ1 de CLASSE LIESPECE
a l'indice ENTI1 de l'element %NVESP d'un objet DONCHI1.

## CHANVSOS [Multi-physique Multi-physique] (proc)
Methode CHANVSOS
---------------- OBJE LIRSOSO

 CHANVSOS ENTI1 OBJ1

   Objet

La methode CHANVSOS charge l'objet OBJ1 de CLASSE LIRSOSO
a l'indice ENTI1 de l'element %NVSOSO d'un objet DONCHI1.

## CHAR [Multi-physique Multi-physique]
  Operateur CHARGEMENT
  -------------------- TIRE PROI FORM

        CHAR1 = CHAR (MOT) | CHE1  | (EVOL1) |  ... (|'LIBRE'|)
        | CHPO1 |  |'LIE ' |
        | TABLE1  TABLE2|
        | LREE1  LOBJ1 |

     ... ( | 'TRAN' VEC1 EVOL2  |  ) ;
        | 'ROTA' POIN1 (POIN2 si 3D) EVOL2 |
        | 'TRAJ' CHPO2  |

  Objet :

  L'operateur CHAR construit un objet CHAR1 de type CHARGEMENT,
de sous-type FORCE, contenant la description spatiale et temporelle du
chargement. On peut associer a l'objet CHARGEMENT un nom (donnee
facultative).

  On peut specifier un chargement non-lie au milieu etudie en definissant
un champ sur des points n'appartenant pas a ce milieu et en utilisant le
mot-cle 'LIBRE'. C'est par exemple le cas d'un outil d'usinage qui voit
defiler une piece. On specifie le deplacement eventuel d'un CHARGEMENT de
nature 'LIBRE' ou 'LIE ', en le definissant sur des points n'appartenant
pas au milieu etudie, et en utilisant l'une des options 'TRAN', 'ROTA'
ou 'TRAJ'.

  Dans le cadre de la procedure PASAPAS, le chargement est evalue :
s'il est de nature LIBRE, il s'applique tel quel, sinon, il s'applique
au milieu sur la configuration initiale, puis est transporte sur la
configuration actuelle.

  On peut egalement specifier un CHARGEMENT de nom TRAJ pour definir une
trajectoire. Dans ce cas, l'operateur prend comme argument le champ
d'abscisse curviligne le long de cette trajectoire (ligne maillee) et
l'evolution de cette abscisse au cours du temps. Le nom de chargement
TRAJ est ainsi reserve.

  Enfin, on peut specifier un CHARGEMENT de nom MAIL, MODE ou RIGI pour
ordonner en fonction du temps des maillages, modeles ou rigidites.
Dans ce cas, l'operateur utilise la syntaxe avec des tables.

  Commentaire :

     MOT : donnee facultative.
        type CHARACTER*4
        Dans le cas de l'utilisation de la procedure
        PASAPAS ce mot est indispensable.

        *** MECANIQUE ***
        - la pression PRES
        - les deplacements imposes DIMP
        - l'increment de deplacement impose DINC
        - les deformation libres imposes DEFI
        - Les autres chargements (meca) MECA
        - la temperature T
        - Flux (en consolidation) FLUX
        - les blocages mecaniques BLOM
        - Des parametres externes de nom MOT1

        *** THERMIQUE ***
        - les temperatures imposees TIMP
        - Les flux de chaleur Q
        - Les temperatures ext.(convection) TECO
        - Les temperatures ext.(rayonnement) TERA
        - les blocages thermiques BLOT

        *** DIFFUSION *** (Si 'INCO' 'CO' 'QCO')
        - la concentration CO
        - les concentrations imposees CIMP
        - Les flux de diffusion QCO
        - les blocages diffusions BLOD

        *** MODELE ***
        - le modele MODE
        - les caracteristiques MATE

     CHPO1 ou CHE1 : description spatiale du chargement
        type CHPOINT ou MCHAML

     EVOL1 : donnee facultative
        description temporelle du chargement (type EVOLUTION) :
        fonction contenant en abscisse les temps (dans l'ordre
        chronologique) et en ordonnee les valeurs F(TEMP) de la
        fonction F aux temps TEMP.
        Par defaut, le chargement est constant.

     TABLE1 : Table indicee par des entiers pointant vers les
        temps (type FLOTTANT). Cette liste d'entiers est
        obligatoirement egale a ( 0 1 2 3 ... N ).

     TABLE2 : Table indicee par ces memes entiers pointant vers
        des CHPOINTS ou des MCHAMLS

     LREE1 : LISTREEL donnant une liste d'instants.

     LOBJ1 : LISTOBJE donnant les objets associes a chaque instant
        de LREE1. LREE1 et LOBJ1 ont donc la meme dimension.
        Cette syntaxe est similaire a celle avec deux tables.

    'LIBRE','LIE ' : Mot-cle facultatif precisant la dependance du
        chargement au milieu etudie (par defaut 'LIE ').

    'TRAN' : mot-cle facultatif, indiquant que le chargement est
        anime d'un mouvement de translation relativement au
        corps modelise, suivi de :

     VEC1 : vecteur de translation (type POINT)
     EVOL2 : description temporelle de la translation (type
        EVOLUTION), fonction contenant en abscisse les temps
        (dans l'ordre chronologique ) et en ordonnee les
        valeurs de la vitesse

    'ROTA' : mot-cle facultatif, indiquant que le chargement est
        anime d'un mouvement de rotation relativement au
        corps modelise, suivi de :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CHARTHER [Thermique Limites] (proc)
   Procedure CHARTHER

        TAB1 = CHARTHER TAB2 FLOT1 ;

   Objet :

  La procedure CHARTHER est a surcharger par l'utilisateur quand
il souhaite definir ses propres conditions aux limites thermiques
"non conservatives" qui doivent etre mises a jour au cours des
iterations du schema de calcul d'un pas de temps de thermique.

[Nota : Le rayonnement est traite dans la procedure specifique de
        nom "PAS_RAYO". La procedure "CHARTHER" est reservee aux
        seules fins specifiques d'un utilisateur (eclaire). ]

   Commentaire :

      TAB2 : c'est la table entree dans PASAPAS

      FLOT1 : instant (FLOTTANT) pour lequel on veut calculer des termes
        de flux (second membre) et/ou des relations (matrice)

      TAB1 : est une table dont les indices sont

        - 'ADDI_SECOND' pointe un chpoint second membre

        - 'ADDI_MATRICE' pointe une matrice a mettre au
        premier membre

## CHAU [—]
    Operateur CHAUSSETTE

    ENT1=CHAU 'SERVEUR' ('ATTENTE' ENT4);
    ENT1=CHAU 'CLIENT' MOT1;
    ENT1=CHAU 'ECRITURE' LREE1 ('ECHO') ('ATTENTE' ENT4);
    ENT1=CHAU 'ECRITURE' MOT2 ('ECHO') ('ATTENTE' ENT4);
    ENT1 LREE2=CHAU 'LECTLIST' ENT2 ('ECHO') ('ATTENTE' ENT4);
    ENT1 MOT3=CHAU 'LECTUMOT' ENT3 ('ECHO') ('ATTENTE' ENT4);
    ENT1=CHAU 'FERMETURE' ('COMPLETE');

    Objet :

    L'operateur CHAUSSETTE permet d'ouvrir un port de communication
(service castem/numero 2000) soit comme serveur (mot cle 'SERVEUR')
sur l'ordinateur courant, soit de type client (mot cle 'CLIENT') sur
l'ordinateur-hote de nom MOT1 (type MOT).

    On peut ensuite ecrire sur le port (mot cle 'ECRITURE') la suite
de flottant LREE1 (type LISTREEL) ou un mot MOT2 (type MOT), ou bien
lire sur le port (mot cle 'LECTLIST') la suite de flottant LREE2
(type LISTREEL) de longueur ENT2 (type ENTIER) ou bien (mot cle
'LECTUMOT') le mot MOT3 (type MOT) de longueur ENT3 (type ENTIER).

    En fin d'utilisation, le port est ferme (mot cle 'FERMETURE').

    Remarque :

    1) Le processus de lecture etant bloquant (du moins pendant un laps
de temps donne - voir remarque 3), CHAUSSETTE permet d'implenter non
seulement une ligne de communication, mais aussi un semaphore.

    2) Lors de la transmission des donnees on peut travailler avec un
echo (mot cle 'ECHO'). En ecriture, on attend la lecture de l'echo
que l'on compare au paquet original. En lecture on retransmet en
ecriture le paquet que l'on vient de lire.

    3) Toute les operations de lecture, ainsi que l'attente du serveur
pour un client, sont affectees d'un temps d'attente maximum de 30
secondes avant sortie avec erreur. On peut modifier ce temps en
introduisant le mot cle 'ATTENTE' suivi du nouveau temps d'attente ENT4
(type ENTIER) exprime en seconde.

    4) ENT1 (type ENTIER) permet de verifier si l'operation demandee a
ete effectivement realisee. Le code suivant est utilise:

    ENT1=1 : pas de probleme,
    ENT1=-1 : l'operation n'a pas ete realisee au niveau du port,
    ENT1=-2 : les donnees ont ete inaccessibles sur le reseau dans
        le temps d'attente.
    ENT1=-3 : en mode 'ECRITURE' avec 'ECHO', on ne relit pas exactement
        ce que l'on a transmis

    5) Dans le cas d'une ouverture en mode 'SERVEUR', le port peut etre mis
en mode de 'FERMETURE' complete (mot cle 'COMPLETE') ou partielle. Si la
fermeture est partielle, le serveur fonctionne en mode incremental et peut
en particulier satisfaire, lors d'une re-ouverture en mode 'SERVEUR', la
connection avec un client en attente de communication. Dans le cas d'une
fermeture incomplete, le port ne peut etre ouvert en mode 'CLIENT'. Dans le
cas d'une fermeture complete, on ne peut effectuer une reouverture en mode
'SERVEUR' que lorsque tous les clients ont ete fermes.

## CHDCLIM [Multi-physique Multi-physique] (proc)
Methode CHDCLIM
--------------- OBJE CH2CLIM

 OBJ1 = OBJET CHDCLIM ;

   Objet

La methode CHDCLIM definit un objet de CLASSE CHDCLIM.
Les elements sont des mots definis par l'utilisateur.
Methode associee: GDCLIM.
        appel: OBJ1%GDCLIM MOT1 LENT1 ;

## CHI1 [Multi-physique Multi-physique]
Operateur CHI1

    TAB2 = CHI1 TAB1 'COMP' VAL1 < 'LOGK' VAL2 > <'ENTH' VAL3 > ;

     Objet
    Le but est de calculer la speciation d'une eau, en tout point
    d'un domaine a partir de la donnee des concentrations analytiques
    de chaque composant chimique du systeme. Le calcul se fait en
    deux temps a l'aide des operateurs CHI1 et CHI2.
    CHI1 rassemble toutes les donnees relatives a un systeme chimique,
    et CHI2 effectue la speciation.
     La terminologie est celle de Mineql.

       Toutes les concentrations sont donnees en moles par litre.

    Commentaires
    TAB1 est une TABLE indicee par les mots:
        'IDEN' <'CHXMX'> <'BDD'> <'CLIM'> <'NVCOMP'>
        <'NVESP'> <'ECHANGE'> <'TEMPERATURE'>

    TAB1.IDEN est un objet de type LISTENTI contenant les
        identifiants (dans la base de donnees),des composants chimi
        ques a utiliser.

    TAB1.CHXMX est un objet de type LISTENTI contenant les identifi
        ants des mineraux a retenir. A defaut on conserve tous les
        mineraux dont les composants sont dans TAB1.IDEN.

    TAB1.BDD contient un mot servant a preciser le format de la base
        de donnees. 'STRASBG' ou 'MINEQL' .
        'MINEQL' correspond a la base de donnees standard de Mineql.
        'STRASBG' correspond a la base de donnees issue de Kindis.
        Les formats sont decrits dans le rapport DMT/94/597.
        L'option par defaut est 'MINEQL'.

    TAB1.CLIM est une TABLE servant a definir les contraintes chimi
        ques. Cette TABLE est indicee par des mots tous facultatifs.
        <'TYP3'> <'COMP3'> <'TYP4'> <'TYP5'> <'TYP6'>

        TAB1.CLIM.TYP3 est un objet de type LISTENTI contenant les
        identifiants des especes dont on veut imposer l'activi
        te.

        TAB1.CLIM.COMP3 est un objet de type LISTENTI contenant
        pour chacune des especes de TAB1.CLIM.TYP3 l'identifi
        ant du composant immobile . Si TAB1.CLIM.TYP3 ne
        contient que des especes simples cette donnee est
        inutile.

        TAB1.CLIM.TYP4 est un objet de type LISTENTI contenant les
        identifiants des especes precipitees.

        TAB1.CLIM.TYP5 est un objet de type LISTENTI contenant les
        identifiants des especes en solution, pouvant etre
        precipites.

        TAB1.CLIM.TYP6 est un objet de type LISTENTI contenant les
        identifiants des especes non prises en compte.

    TAB1.NVCOMP est une TABLE permettant de rajouter des composants
        (ne figurant pas dans la base de donnees). Pour n composants
        , cette TABLE sera indicee par des nombres de 1 a n.
        Pour le i ieme composant a rajouter TAB1.NVCOMP.i sera une
        TABLE indicee par les mots: 'IDEN' 'NOM' 'CHARGE'
        TAB1.NVCOMP.i.IDEN est un entier identifiant du nouveau
        composant.
        TAB1.NVCOMP.i.NOM est un mot nom de ce composant
        TAB1.NVCOMP.i.CHARGE est un entier charge de l'espece
        simple associee.

    TAB1.NVESP est une TABLE permettant de rajouter ou de modifier
        des especes.Pour n especes, cette TABLE sera indicee par
        des nombres, de 1 a n.
        Pour la i ieme espece a rajouter TAB1.NVESP.i sera une
        TABLE indicee par les mots:
        'IDEN' 'LOGK' <'ITYP'> <'COMP'> <'STOECH'>

        TAB1.NVESP.i.IDEN est un entier identifiant de l'espece

        TAB1.NVESP.i.LOGK est un reel logk de l'espece

        TAB1.NVESP.i.ITYP entier type de l'espece
        2 complexe en solution
        3 activite fixee
        4 mineraux precipites
        5 mineraux dissous
        6 non pris en compte dans le calcul

        TAB1.NVESP.i.COMP objet LISTENTI contenant les identifiants
        des composants de l'espece. Le nombre de
        ces identifiants doit etre inferieur a 4
        pour une base de donnee de type MINEQL
        et inferieur a 8 pour une base de donnee
        de type STRASBG.

        TAB1.NVESP.i.STOECH objet LISTREEL coefficient
        stoechiometrique correspondant a chacun
        de ces composants.
        TAB1.NVESP.i.NOMESPECE mot. Nom de cette nouvelle espece
        chimique. ( au plus 32 caracteres.La
        valeur par defaut est contituee de 32
        blancs)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CHI2 [Multi-physique Multi-physique]
Operateur CHI2

    TAB4 = CHI2 TAB1 TAB2 <TAB3> ;

     Objet
    Le but est de calculer la speciation d'une eau, en tout point
    d'un domaine a partir de la donnee des concentrations analytiques
    de chaque composant chimique du systeme. Le calcul se fait en
    deux temps a l'aide des operateurs CHI1 et CHI2.
    CHI1 rassemble toutes les donnees relatives a un systeme chimique,
    et CHI2 effectue la speciation.
     La terminologie est celle de Mineql.

       Toutes les concentrations sont donnees en moles par litre.

    Commentaires
    TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

    TAB2 est un objet de type TABLE de sous-type 'DONNEES_CHIMIQUES'.
        Elle est indicee par les mots :
        'LOGC' 'TOT' <'FIONI'> <'NTY4'> <'TEMPE'> <'CLIM'>

    TAB2.LOGC est un objet de type CHPOIN qui possede une composante
        par composant chimique. Pour chaque composant chimique il
        contiendra le log de l'estimation de l'espece simple
        associee. Le nom de ces composantes est un mot de 4
        caracteres, forme par X suivi eventuellement de 0 ou 00 et
        du numero identifiant le composant chimique.

    TAB2.TOT est un objet de type CHPOIN qui possede une composante
        par composant chimique. Pour chaque composant chimique il
        contiendra la concentration totale (ou analytique) ( en
        solution + mineraux). Le nom de ces composantes est un mot
        de 4 caracteres, forme par X suivi eventuellement de 0 ou
        00 et du numero identifiant le composant chimique.

    TAB2.FIONI objet de type CHPOIN ayant une composante scalaire, et
        contenant une estimation de la force ionique en chaque
        point du maillage.

    TAB2.NTY4 objet de type CHPOIN ayant une composante pour chaque
        espece de precipite potentiel. En chaque point du maillage
        on indiquera si le mineral est precipite ( =1) ou non( =0).
        Les nom des composantes sont ceux figurant dans la liste
        TAB1.IDEN.NOMPRECI.

    TAB2.TEMPE objet de type CHPOIN contenant la temperature.

    TAB2.CLIM valeur de l'activite imposee des especes de type 3.
        Objet de type CHPOIN ayant une composante pour chaque
        espece dont l'activite est imposee.Les noms des composantes
        sont ceux figurant dans la liste TAB1.IDEN.NOMTYP3.

    TAB3 est un objet de type TABLE contenant les parametres de
        calcul. Elle est indicee par les mots :
        <'EPS'> <'ITMAX'> <'ITERSOLI'> <'PRECPE'> <'IAFFICHE'>
        <'NITERPE'> <'DELPE'> <'MDELPE'> <'NFI'> <'SORTIE'>
        <'IMPRIM'>

    TAB3.EPS est un REEL, la precision du calcul.
        Valeur par defaut 1.E-4.

    TAB3.ITMAX est un ENTIER nombre maximal d'iterations dans la
        resolution du systeme chimique. Valeur par defaut 20.

    TAB3.ITERSOLI est un ENTIER nombre maximal d'iterations, pour
        trouver les mineraux precipites. Valeur par defaut 10.

    TAB3.IAFFICHE est un ENTIER permettant le choix d'affichage des
        resultats pour les solutions solides.
        1 coefficients stoechiometriques des solutions solides
        2 fractions molaires des solutions solides
        Valeur par defaut 2.

    TAB3.CALCLOG est un ENTIER, indication sur le calcul en log
        de concentration ou pas dans la speciation
        0 calcul en concentration
        1 calcul en log de concentration
        Valeur par defaut 0

    TAB3.PRECPE est un REEL, precision sur le calcul redox.
        Valeur par defaut 1.E-10

    TAB3.NITERPE est un ENTIER nombre maximal d'iterations de
        dichotomie. Valeur par defaut 50.

    TAB3.DELPE est un REEL, l'intervalle initial des iterations de
        dichotomie. La valeur par defaut est 1.

    TAB3.MDELPE est un ENTIER nombre maximal de pas dans la recherche
        de l'intervalle de dichotomie. Valeur par defaut 20.
        ( evite de cycler lorsque l'on est tres loin de la solution)

    TAB3.NFI est un ENTIER nombre de cycles de chimie.
        Valeur par defaut 4. Un cycle correspond a la sequence:
        * calcul de la force ionique
        * modification des logk
        |---
        * boucle mineraux a  |* resolution ( iterative )
        precipiter  |
        |* verification des mineraux
        |  precipites
        |---
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CHITRNSP [Multi-physique Multi-physique] (proc)
  Procedure CHITRNSP
  ------------------ CHI2 DMTD

        CHITRNSP TAB1 ;

     Objet
     Cette procedure permet d'effectuer un calcul couple transport/
    chimie. Le transport utilise les elements finis mixte_hybrides.

     Commentaires
 TAB1 est une table de soustype 'GEOCHIMIE'.
 En entree, TAB1 sert a definir les options et les parametres du
 calcul.
 En sortie TAB1 contient les donnees d'entrees et les resultats de
 façon a permettre une reprise du calcul.
 Les indices de la table TAB1 sont des mots (a ecrire en
 toutes lettres, et en majuscules s'ils sont mis entre cotes)
 dont voici la description :

 Donnees physiques, geometriques et materielles :

 Indices: 'SOUSTYPE' 'MODELE' 'DIFFUSION' <'POROSITE'> 'DOMAINE'
      'CONVECTION' 'CHIMI1' <'ITERC'> <'PRECISION'> <'DECROISSANCE'>

 'SOUSTYPE' mot 'GEOCHIMIE'

 'MODELE' Objet modele (MMODEL cree par MODE,formulation DARCY)

 'DIFFUSION' Donnees physiques et materielles :
        conductivite hydraulique (MCHAML cree par MATE)

 'POROSITE' Contient la porosite au centre de l'element
        (CHPOIN de support DOMAINE.CENTRE)
        La valeur par defaut est 1.

 'DOMAINE' References geometriques (TABLE creee par DOMA)

 'CONVECTION' Flux de la vitesse convective (CHAMPOIN de support
        DOMAINE.FACE)

 'CHIMI1' Table issue de CHI1

 'ITERC' nombre max d'iterations de couplage (defaut 100)

 'PRECISION' precision critere de convergence pour le couplage
        valeur par defaut 1.E-3

 'DECROISSANCE' table TAB2 contenant les donnees relatives a la
       decroissance/filiation. Cette table est indicee par le mot
       'TETA' et des entiers de 1 a N. N etant le nombre de couples
        pere fils.
        TAB2.TETA est un reel le coefficient d'implicitation.
        TAB2.i est une table d'indices 'PERE' 'FILS' et 'LAMBDA'
        TAB2.i .'PERE' est un entier identifiant du pere.
        TAB2.i .'FILS' est un entier identifiant du fils.
        TAB2.i .'LAMBDA' est un reel la constante de decroissance.

    parametres de calcul de chimie

  indices: <'EPS'> <'ITMAX'> <'ITERSOLI'> <'PRECPE'> <'IAFFICHE'>
        <'NITERPE'> <'DELPE'> <'MDELPE'> <'NFI'> <'TEMPE'>
        <'CLIM'> <'SORTIE'> <'IMPRIM'>

 'EPS' un REEL, la precision du calcul.
        Valeur par defaut 1.E-4.

 'ITMAX' un ENTIER nombre maximal d'iterations dans la
        resolution du systeme chimique. Valeur par defaut 20.

 'ITERSOLI' un ENTIER nombre maximal d'iterations, pour
        trouver les mineraux precipites. Valeur par defaut 10.

 'IAFFICHE' un ENTIER permettant le choix d'affichage des
        resultats pour les solutions solides.
        1 coefficients stoechiometriques des solutions solides
        2 fractions molaires des solutions solides
        Valeur par defaut 2.

 'PRECPE' un REEL, precision sur le calcul redox.
        Valeur par defaut 1.E-10

 'NITERPE' un ENTIER nombre maximal d'iterations de
        dichotomie. Valeur par defaut 50.

 'DELPE' un REEL, l'intervalle initial des iterations de
        dichotomie. La valeur par defaut est 1.

 'MDELPE' un ENTIER nombre maximal de pas dans la recherche
        de l'intervalle de dichotomie. Valeur par defaut 20.
        ( evite de cycler lorsque l'on est tres loin de la solution)

 'NFI' un ENTIER nombre de cycles de chimie.
        Valeur par defaut 4. Un cycle correspond a la sequence:
        * calcul de la force ionique
        * modification des logk
        |---
        * boucle mineraux a  |* resolution ( iterative )
        precipiter  |
        |* verification des mineraux
        |  precipites
        |---

 'TEMPE' objet de type CHPOIN contenant la temperature.

 'CLIM' valeur de l'activite imposee des especes de type 3.
        Objet de type CHPOIN ayant une composante pour chaque
        espece dont l'activite est imposee.

 'SORTIE' un objet de type LISTMOTS. Ces mots doivent
        etre pris dans la liste:
        'PREC' 'FION' 'TYP6' 'TYP3' 'NTY4' 'TYP5' 'SURF' 'SOLU'
        'POLE' 'LOGK'
        Ils servent a preciser les elements que l'on veut voir
        figurer dans la TABLE TAB1.

 'IMPRIM' un objet de type LISTENTI . Dans le cas ou l'on demande
        un niveau de message superieur a 0 ( OPTION IMPI 1 ),
        ceci permet de limiter les impressions aux seuls noeuds
        du maillage dont le numero figure dans la liste.

 Conditions aux limites / chargements :

 Indices : <'BLOCAGE'> <'TRACE_IMPOSE'> <'FLUX_IMPOSE'> <'SOURCE'>

 'BLOCAGE' Contient les matrices de blocage (RIGIDITE)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CHOI [Entree-Sortie Entree-Sortie]
 Operateur CHOI

 LOG1 ... LOGn = CHOI CHAINE BOOL1 ... BOOLn ;

 Objet :

 L'operateur CHOI permet de choisir graphiquement des options
 dans un ensemble d'options presentees sous forme de cases a
 cocher.

CHAINE : Chaine de caracteres affichee a l'ecran

BOOL1 : Logique dont le nom est affiche a l'ecran precede de
... (X) si VRAI et ( ) si FAUX
BOOLn

LOG1 : Logique valant VRAI si l'option a ete retenue et FAUX
... sinon
LOGn

## CHPO [Langage Objets]
    Operateur CHPOINT

    CHPO1 = CHPOINT |'ALEATOIRE'  | RIG1 ;
        |'UNIFORME'  FLOT1 |

    Objet :

    L'operateur CHPOINT cree un objet CHPO1 (type CHPOINT), ayant pour
composantes les d.d.l. primaux de l'objet RIG1 (type RIGIDITE).

    Commentaire :

    Le CHPOINT CHPO1 peut avoir :

    - soit des valeurs 'ALEATOIRE'
    - soit une valeur 'UNIFORME' egale a FLOT1 (type FLOTTANT)

## CHPR0 [Fluides Resolution]
 Procedure CHPR0

 LREE1 = CHPR0 CHP1 MAIL1 ;

 Objet :

 cree une liste de reel a partir du champoint
Cette procedure est a utiliser a partir de la procedure DARCYSAT

## CHSP [Mathematiques Traitement]
    Operateur CHSP

    EVOL2 = CHSP EVOL1 'ENTR' MOT1 'SORT' MOT2 ('COUL' COUL1);

    Objet :

    Cet operateur permet de changer un (ou des) spectre(s) donne(s)
en un (ou des) spectre(s) d'un autre type.

    Commentaire :

    EVOL1 : Le (ou les) spectre(s) que l'on souhaite modifier
        (type EVOLUTION).

    'ENTR' : Mot-cle suivi de :

    MOT1 : type du (ou des) spectre(s) d'entree, choisi parmi :
        'DEPL', 'VITE' ou 'ACCE'.

    'SORT' : Mot-cle suivi de :

    MOT2 : Type du (ou des) spectre(s) de sortie, choisi parmi:
        'DEPL', 'VITE' ou 'ACCE'.

    'COUL' : Mot cle facultatif suivi de :

    COUL1 : couleur desiree des courbes (type MOT).

    EVOL2 : Spectre resultat (type EVOLUTION).

## CHTGAU [Thermique Resolution] (proc)
Procedure CHTGAU

CHPO1 = CHTGAU TAB1 ;

        TAB1.'PUISSANCE' .'RENDEMENT'
        .'DIFFUSVITE' .'CONDUCTIVITE'
        .'VITESSE'
        .'T0'
        .'NTERMES'
        .'MAILLAGE'
        .'EPAISSEUR'
        .'LOCAL' .'INSTANT'
        .'GAUSS' .'ECART-TYPE'

Objet :

Cette procedure calcule le champ de temperature resultant du
deplacement d'un arc de soudure sur une plaque infinie. L'arc est
soit ponctuel et se deplace selon l'axe X.
La solution analytique du probleme est tiree de Rosenthal :
Mathematical Theory of Heat Distribution During Welding and
Cutting.

Commentaire :

En entree :

    TAB1 : Objet de type TABLE, indice par des mots, servant a
        definir les options de calcul :

    Arguments :

        'PUISSANCE' : REEL : Puissance de l'arc (en W)

        'RENDEMENT' : REEL : Rendement de l'arc : Rapport de
        la puissance recue par la piece et de la puissance
        de l'arc

        'DIFFUSVITE' : REEL : Diffusivite thermique du materiau
        (en m2/s)

        'CONDUCTIVITE' : REEL : Conductivite thermique du
        materiau (en W/Km2)

        'VITESSE' : REEL : Vitesse de deplacement de l'arc (en m/s)

        'T0' : REEL : Temperature ambiante (en °C ou en K)

        'NTERMES' : ENTIER : Nombre de termes de la somme

        'MAILLAGE' : MAILLAGE : Maillage support du champ de
        temperature

        'EPAISSEUR' : REEL : Epaisseur de la piece (en m)

        'LOCAL' : BOOLEEN : VRAI si la piece est decrite dans
        le repere local a l'arc

        'INSTANT' : REEL : Si 'LOCAL' est FAUX, instant
        auquel il faut calculer le champ de temperature
        (l'abscisse de l'arc est alors V*t) (en s)

        'GAUSS' : BOOLEEN : VRAI si la source est gaussienne

        'ECART-TYPE' : REEL : Ecart-type de la gaussienne (in m)

En sortie :

        CHPO1 : CHPOINT : Champ de temperature (en °C ou en K)

## CHTITR [Mecanique Dynamique] (proc)
    Procedure CHTITR

La procedure CHTITR est appelee par la procedure DECONV.

## CH_THETA [Mecanique Rupture] (proc)
  Procedure CH_THETA

  CH_THETA SUPTAB OBJUTI BOOL ;

        SUPTAB.'MAILLAGE'
        .'FISSURE'
        .'FRONT_FISSURE'
        .'COUCHE'
        .'POINT_1'
        .'POINT_2'
        .'POINT_3'
        .'PCENTRE'
        .'CHPOINT_TRANSFORMATION'
        .'OPERATEUR'
        .'EPAISSEUR'

  Objet :

Cette procedure determine un chpoint de type THETA. c'est-a-dire
un champ/point dont la norme est constante a l'interieur d'une
couronne entourant le front d'une fissure, zero a l'exterieur
cette couronne. Le vecteur represente par ce chpoint indique
la direction de propagation eventuelle de la fissure. Pour un
front de fissure tridimensionnel, la procedure cree autant de
champs THETA qu'il y a de points sur le front de fissure. Les
champs THETA construits sont des champs locaux qui s'appuient
sur les noeuds du plan normal au front de fissure au point
considere (le maillage doit etre elabore de maniere a prevoir
l'existence de ces plans normaux). En 3D Cette procedure est
applicable uniquement pour les fissures planes.

  En entree

  SUPTAB = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres).

  OBJUTI = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres).
        Cette table est definie par les procedures G_THETA
        et G_CAS avant de faire appel a CH_THETA.

  BOOL = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres).
        Cette table est definie par les procedures G_THETA
        et G_CAS avant de faire appel a CH_THETA.

  1) ARGUMENTS OBLIGATOIRES DANS TOUS LES CAS
  SUPTAB.'MAILLAGE' = Objet de type MAILLAGE representant soit
        la structure totale etudiee (maillage
        utilise dans l'analyse par elements finis,
        soit, pour reduire le temps de calcul, le
        maillage entourant le plus grand des contours
        qu'on a defini pour calculer le champ THETA.
  SUPTAB.'FISSURE' = Objet de type MAILLAGE donnant les deux
        levres d'une fissure si elle est complete (la
        fissure presente des noeuds doubles), une
        seule levre si l'autre levre n'est pas maillee
        en raison, par example, de la symetrie du
        probleme.
  SUPTAB.'FRONT_FISSURE' = Objet de type POINT (representant la
        pointe de la fissure) si la fissure est
        une ligne, de type MAILLAGE (representant
        le front de la fissure) si la fissure est
        sur un plan en 3D.
  SUPTAB.'COUCHE' = Objet de type ENTIER representant le nombre
        de couches d'elements (autour du point de
        fissure) qui se deplacent pour simuler la
        propagation de la fissure.

  2) CAS D'UNE FISSURE CIRCULAIRE DANS UNE GEOMETRIE PLANE

  SUPTAB.'PCENTRE' = centre de la fissure circulaire

  3) CAS OU L EXTENSION DE FISSURE CORRESPOND A UNE
  SIMPLE TRANSLATION DANS UN TUYAUTERIE DROITE (3D)

  Dans ce cas on effectue dans la procedure une transformation de
  tuyau en plaque en passant au systeme de coordonnees cylindriques.
  Il est alors necessaire de fournir :

  SUPTAB.'POINT_1' = centre du systeme de coordonnees
  SUPTAB.'POINT_2' = POINT tel que l'axe defini par POINT_1
        vers POINT_2 soit l'axe Z poisitif
  SUPTAB.'POINT_3' = POINT tel que le plan defini par les 3 points
        POINT_1 POINT_2 POINT_3 donne l'angle theta nul

  4) CAS OU L EXTENSION DE FISSURE NE
  CORRESPOND PAS A UNE SIMPLE TRANSLATION

  A) Fissure dans un tuyauterie droite (3D, Rotation)

  SUPTAB.'POINT_1' = Objet de type POINT
  SUPTAB.'POINT_2' = Objet de type POINT qui, avec le point POINT_1,
        constitue l'axe perpendiculaire a la section
        fissuree.

  B) Fissure dans un coude (3D, rotation + transformation)

     Outre les deux points SUPTAB.'POINT_1' et SUPTAB.'POINT_2'
     definis en haut on donne encore :
  SUPTAB.'CHPOINT_TRANSFORMATION' = Objet de type CHPOINT utilise
        pour transformer une coude en
        un tuyauterie droite.

  SUPTAB.'OPERATEUR' = Objet de type MOT valant 'PLUS' ou 'MOIN'
        pour indiquer l'operateur PLUS ou MOIN a
        utiliser si l'on veut transformer la coude
        en un tuyauterie droite.

  5) CAS DES ELEMENTS DE COQUE

  SUPTAB.'EPAISSEUR' = Objet de type FLOTTANT donnant l'epaisseur
        de la coque a la pointe de la fissure

    En sortie :

  SUPTAB.'CHAMP_THETA' = Objet de type :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CH_THETX [Mecanique Rupture] (proc)
  Procedure CH_THETX

  THETA TABUTIL = CH_THETX SUPTAB ;

        SUPTAB . 'MAILLAGE'
        . 'PSI'
        . 'PHI'
        . 'FRONT_FISSURE'
        . 'COUCHE'

  Objet :

Appele par G_THETA qui calcule le taux de restitution d'energie,
cette procedure determine un chpoint d'avance virtuelle de type THETA
pour les elements XFEM. Plus precisement, il s'agit d'un champ/point
dont la norme est constante et egale a 1 a l'interieur d'une couronne
entourant le front de fissure, et 0 a l'exterieur de cette couronne.
Le vecteur represente par ce chpoint indique la direction de
propagation eventuelle de la fissure.

Non disponible en 3D pour l'instant.

  En entree

  SUPTAB = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres) :

  ARGUMENTS OBLIGATOIRES
  °°°°°°°°°°°°°°°°°°°°°°

  SUPTAB.'MAILLAGE' = Objet de type MAILLAGE representant soit
        la structure totale etudiee (maillage
        utilise dans l'analyse par elements finis,
        soit, pour reduire le temps de calcul, le
        maillage entourant le plus grand des contours
        qu'on a defini pour calculer le champ THETA.

  SUPTAB.'PSI' = Objet de type CHPOINT representant la 1ere level
        decrivant le repere local de la fissure
  SUPTAB.'PHI' = Objet de type CHPOINT representant la 2eme level
        decrivant le repere local de la fissure

  SUPTAB.'FRONT_FISSURE' = Objet representant le front de fissure
        -de type POINT en 2D
        -de type MAILLAGE (ligne) en 3D

  SUPTAB.'COUCHE' = Objet de type ENTIER representant le nombre
        de couches d'elements (autour du point de
        fissure) qui se deplacent pour simuler la
        propagtion de la fissure.

  SORTIE
  °°°°°°

  THETA = Objet de type :

       - TABLE indicee par des objets de type POINT contenant
        des elements de type CHPOINT dans les 3 dimensions.
        Chaque element contient le champ THETA au noeud du
        front, de coordonnees correspondant au point P: TETA.P.
        Elle est egalement indicee par le mot 'GLOBAL' pour
        donner le champ THETA global le long de tout le front
        de la fissure
       - CHPOINT contenant le champ THETA en 2 dimensions (ou en
        3 dimensions avec des elements coque mince) a la pointe
        de fissure.

  TABUTIL = Objet de type TABLE contenant le vecteur directeur
        unitaire donnant la direction du champs THETA

## CINEMA [Post-traitement Affichage] (proc)
Procedure CINEMA

DEFO1 = CINEMA GEO1 GEO2 GEO3 VEC1;

Objet :

Cette procedure produit une animation d'un objet GEO1 suivant
un succession de points de vue GEO2 et d'orientations de vision
GEO3 et une direction fixe de la tete VEC1.

Commentaire :

GEO1 : objet que l'on cherche a explorer (type MAILLAGE)

GEO2 : suite de POI1 definissant les positions successives du
        point de vue (type MAILLAGE)

GEO3 : suite de POI1 definissant les positions successives de
        la direction de vision (type MAILLAGE)

VEC1 : direction de l'axe de la tete de l'observateur (type POINT)

Remarque :

Il est conseille d'utiliser l'option DIRE de la directive TRAC pour
animer l'objet GEO1. Si FLO1 est la distance entre l'oeil et
le plan de vision, on peut proceder comme suit:

   DEFO1 = CINEMA GEO1 GEO2 GEO3 VEC1;
   OEIL1 = (GEO2 'ELEM' 1) 'POINT' 1;
   OPC11 = (GEO3 'ELEM' 1) 'POINT' 1;
   OPC12 = VEC1;
   OPC11 = OPC11/('NORM' OPC11);
   OPC12 = OPC12 'MOINS' ((OPC11 'PSCA' OPC1)*OPC11);
   OPC12 = OPC12/('NORM' OPC12);
   OPC13 = OPC11 'PVEC' OPC12;
   PC11 = OEIL1 'PLUS' (FLO1*OPC11);
   PC12 = PC11 'PLUS' OPC12;
   PC13 = PC11 'PLUS' OPC13;
   'TRAC' OEIL1 DEFO1 'FACE' 'DIRE' 'COUP' PC11 PC12 PC13 'OSCI';

## CINEMB [Post-traitement Affichage] (proc)
Procedure CINEMB

DEFO1 = CINEMB GEO1 GEO2 GEO3 GEO4;

Objet :

Cette procedure produit une animation d'un objet GEO1 suivant
un succession de points de vue GEO2, d'orientations de vision
GEO3 et d'orientations de la tete GEO4.

Commentaire :

GEO1 : objet que l'on cherche a explorer (type MAILLAGE)

GEO2 : suite de POI1 definissant les positions successives du
        point de vue (type MAILLAGE)

GEO3 : suite de POI1 definissant les positions successives de
        la direction de vision (type MAILLAGE)

GEO4 : suite de POI1 definissant les orientations successives de
        l'axe de la tete de l'observateur (type MAILLAGE)

Remarque :

Il est conseille d'utiliser l'option DIRE de la directive TRAC pour
animer l'objet GEO1. Si FLO1 est la distance entre l'oeil et
le plan de vision, on peut proceder comme suit:

   DEFO1 = CINEMA GEO1 GEO2 GEO3 GEO4;
   OEIL1 = (GEO2 'ELEM' 1) 'POINT' 1;
   OPC11 = (GEO3 'ELEM' 1) 'POINT' 1;
   OPC12 = (GEO4 'ELEM' 1) 'POINT' 1;;
   OPC11 = OPC11/('NORM' OPC11);
   OPC12 = OPC12 'MOINS' ((OPC11 'PSCA' OPC1)*OPC11);
   OPC12 = OPC12/('NORM' OPC12);
   OPC13 = OPC11 'PVEC' OPC12;
   PC11 = OEIL1 'PLUS' (FLO1*OPC11);
   PC12 = PC11 'PLUS' OPC12;
   PC13 = PC11 'PLUS' OPC13;
   'TRAC' OEIL1 DEFO1 'FACE' 'DIRE' 'COUP' PC11 PC12 PC13 'OSCI';

## CINIMOD [Mecanique Dynamique] (proc)
    Procedure CINIMOD

    CHPO2 = CINIMOD TAB1 MAS1 CHPO1 ;

    Objet :

    Cette procedure sert a calculer le CHPOINT des coordonees generalisees
(deplacements ou vitesses) qui correspondent a un CHPOINT des coordonees
(deplacements ou vitesses) nodales .

    Commentaire :

    TAB1 : Base modale (type TABLE de sous-type BASE_MODALE), issue
        de l'operateur VIBR ( option 'TBAS' ).

    CHPO1 : champ de deplacement (vitesse) nodal (type CHPOINT). Les
        points et les composantes de CHPO1 doivent etre inclus
        dans la base.

    CHPO2 : champ de deplacement (vitesse) generalisee (type CHPOINT) de
        composante ALFA.

    MAS1 : matrice masse (type RIGIDITE)

## CLINC [Nautilus] (proc)
    Procedure CLINC

    CHP1 = CLINC TAB1 TAB2 LOG1 MOT1 MOT2 MOT3 ;

    Objet :

    La procedure CLINC est une procedure appelee par EXECRXT et permet
d'imposer les conditions aux limites de Dirichlet des champs scalaires.

    Commentaire :

       TAB1 : Description du problème fluide (table RXT)

       TAB2 : Description de l'equation scalaire (table RTF)

       LOG1 : vrai si resolution parallele

       MOT1 : Nom de l'inconnue scalaire

       MOT2 : Nom de l'indice contenant la valeur a imposer

       MOT3 : Nom de l'indice de TAB1 . 'TIC' contenant le champ
        scalaire en debut de pas de temps

       CHP1 : Increment de la condition aux limites sur le pas de temps

    Remarque :

    Le champ interne TAB2 . 'CLIM' contient le CHPOINT des conditions
aux limites pour l'operateur KRES.

## CLMI [Fluides Resolution]
    Operateur CLMI

    SYNTAXE :
    Syntaxe EQEX:

    ... 'EQEX' ...
        'OPER' 'CLMI' ferm equa 'UE' 'DUE' 'I1NM' 'I2NM'
        'INCO' 'I1N'

    (... 'EQEX' ...
        'OPER' 'CLMI' ferm equa 'UE' 'DUE' 'I2NM' 'I1NM'
        'INCO' 'I2N')

    OBJET :

 Cet operateur discretise les equations integrales de quantite de
 mouvement(1), d'energie cinetique(2) et d'entrainement(3), utilisees
 pour le calcul des couches limites:

        d(D2) H+2 d(Ue) Cf
   (1) ----- + ---- ----- D2 = ----
        dX Ue dX 2

        d(D3) 3 d(Ue)
   (2) ----- + --- ----- D3 = 2Cd
        dX Ue dX

        d(D-D1) 1 d(Ue)
   (3) ------- + --- ----- (D-D1) = Ce
        dX Ue dX
 D2: Epaisseur de quantite de mouvement
 D3: Epaisseur d'energie cinetique
 D1: Epaisseur de deplacement
 D: Epaisseur de couche limite

 L'operateur CLMI ne discretise qu'une seule equation, donc dans le cas
 d'une methode a deux equations, il faudra appeler deux fois cet
 operateur dans le jeu de donnees.
 Cet operateur permet de traiter les cas de couches limites
 laminaires et turbulentes. Differentes methodes de
 resolution (choix de relations de fermeture) sont laissees
 a l'appreciation de l'utilisateur.

1/Couche limite laminaire:
  a/Approximation de la couche limite de Blasius:
    Cette methode peut-etre utilisee lorsque l'on souhaite
    calculer des couches limites sur parois planes avec des
    gradients de pression tres faibles.
  b/Approximation de Von Karman-Polhausen:
    Cette methode peut-etre utilisee pour des couches
    limites laminaires en presence d'un gradient de
    pression. Le gradient de pression doit varier lentement.
  c/Methode a deux equations:
    Cette methode est la plus generale, elle permet de
    calculer les couches limites laminaires, lorsque le
    gradient de pression varie rapidement. Cette methode est a
    preferer.
2/Couche limite turbulente:
  a/Methode de Head:
    Cette methode est basee sur les relations de fermeture
    de Head. Elle fournit de bons resultats.
  b/Methode de Michel:
    Cette methode repose sur des relations de fermeture
    deduites de l'etude des couches limites
    d'equilibre. De maniere generale, elle fournit des resultats
    meilleurs que dans la methode de Head. Cependant, cette
    methode a tendance a faire decoller la couche limite
    pour des valeurs de facteur de forme beaucoup plus
    faibles que les valeurs experimentales.

    Commentaires

  ferm FLOTTANT
        Type de relations de fermeture utilisees
        1 = Cas laminaire, approximation de Blasius
        2 = Cas laminaire, methode de Von Karman-Pohlausen
        3 = Cas laminaire, methode a 2 equations
        4 = Cas turbulent, methode de Michel
        5 = Cas turbulent, methode de Head

  equa FLOTTANT
        Type d'equation traitee par l'operateur CLMI
        1 = Equation de quantite de mouvement
        2 = Equation d'energie cinetique
        3 = Equation d'entrainement

  UE CHPOINT
        Champ de vitesse exterieur

  DUE CHPOINT
        gradient du champ de vitesse UE
        (La version actuelle de l'operateur ne calcule pas la derivee
        du champ UE, c'est pourquoi, il faut donner ce gradient en
        argument de CLMI. Cet argument devra disparaitre dans une
        future evolution).

  I1NM CHPOINT
        Inconnue de l'equation traitee au pas de temps precedent.
        Physiquement, cet argument est une longueur (unite: m).

  I2NM CHPOINT
        Inconnue de la deuxieme equation au pas de temps
        precedent(si methode a deux equations)
        Physiquement, cet argument est une longueur (unite: m).

  I1N CHPOINT
        Inconnue de l'equation
        Physiquement, cet argument est une longueur (unite: m).

    Options : (EQEX)

 L'algorithme a utiliser est un algorithme IMPLICITE
 La discretisation des equations integrales avec CLMI est du
 type EF avec un decentrement SUPG.

    Resultats :

 Outre les inconnues I1N, I1NM (I2N, I2NM si methode a deux equations),
 on peut recuperer, dans table des inconnues,le coefficient parietal
 local (CF), le facteur de forme de la couche limite (H). Ces deux
 termes sont calcules dans CLMI, ce sont des CHPOINT.

    Remarques :

 Dans les methodes utilisant une seule equation integrale,
 le CHPOINT I2NM n'est pas utilisee, cependant il faut
 laisser cet argument (argument actuellement obligatoire).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CLST [Mecanique Dynamique]
    Operateur CLST

    BLSTR1 = CLST STRU1 RIG1 ;

   Objet :

  L'operateur CLST cree un objet BLSTR1(type BLOQSTRU) que l'on utilise
pour ecrire des liaisons entre sous-structures.

    Commentaire :

      STRU1 : sous-structure (type STRUCTURE)

      RIG1 : rigidite correspondant a un blocage de la structure
        (type RIGIDITE)

## CMCT [Fluides Resolution]
    Operateur CMCT
    -------------- LUMP BLOQ

    | 1 Fonction |

      Syntaxe :

        RIG3 = 'CMCT' RIG1 CHPO1 ;

       Objet :

 L'operateur CMCT permet de realiser la condensation sur les inconnues L
d'un systeme de la forme
        t
        |  M  C  |  | U |  | F |
        |  | x  |  |  =  |  |
        |  C  0  |  | L |  | d |

ou C . U = d sont des relations sur les inconnues U.
et ou M est diagonale inversible.

       Commentaire :

        RIG1 : contient les matrices associees aux relations.

        CHPO1 : contient la matrice diagonale M inversee
        (voir operateur INVE)

        RIG2 : contient la matrice condensee [ C M-1 Ct ]

       Remarque :

La representation de l'inverse de M par un champ par point suppose
que les noms de composantes du champ sont les composantes primales
de la matrice (exemple UX UY UZ ).

    | 2 Fonction |

      Syntaxe :

        RIG3 = 'CMCT' RIG1 RIG2 ;

       Objet :

 L'operateur CMCT permet de realiser la condensation de la matrice
rig1 sur le les inconnues primales de rig2 quit definit les relations
de dependance .

        [K]U=F
        [C] une matrice de dependance telle que U=[C]V

        CMCT rend la matrice KP = Ct K C

    nota : pour la condensation des forces voir CHAN COND RIG2 ;

       Commentaire :

        RIG1 : matrices contenant des ddl esclaves

        RIG2 : contient les matrices definissant des relations
        sur des ddl de rig1

        RIG3 : contient la matrice condensee [ Ct K C ]

## CMOY [Mecanique Dynamique]
    Operateur CMOY

    EVOL1 = CMOY EVOL2 'ACQU' FLOT1 ('DECL' FLOT2) ('NCHO' ENTI1) ;

    Objet :

    L'operateur CMOY calcule un choc moyen a partir d'un ensemble
d'impacts. Chaque choc est detecte par le depassement d'un seuil;il est
enregistre sur un temps d'acquisition pre defini.

    Commentaire :

    EVOL2 : Enregistrements des chocs au cours du temps
        (type EVOLUTION).
        Il peut y avoir plusieurs courbes dans EVOL2.

    'ACQU' : Mot-cle suivi de :
    FLOT1 : Temps d'acquisition de chaque choc (type FLOTTANT).

    'DECL' : Mot-cle suivi de :
    FLOT2 : Seuil de declenchement de l'acquisition en % de la valeur
        maximale en valeur absolue des chocs (type FLOTTANT).

    'NCHO' : Mot-cle suivi de :
    ENTI1 : Nombre de chocs dont on va calculer la moyenne
        (type ENTIER)

    EVOL1 : resultat (type EVOLUTION) contenant autant de courbes
        qu'EVOL2.

## CNEQ [Multi-physique Multi-physique]
  Operateur CNEQ

     CHPO2 =  CNEQ  MODL1  | CHPO1 | ( CAR1 )  ;
        | CHAM1 |

   Objet :

   L'operateur CNEQ calcule le champ de valeurs nodales equivalent
a un champ volumique. Il permet par exemple de calculer les forces
nodales correspondant au poids ou a des forces centrifuges.

     Commentaire :

     MODL1 : Objet modele ( type MMODEL ).

     CHPO1 : champ volumique defini aux noeuds (type CHPOINT)

     CHAM1 : champ volumique defini dans les elements (type MCHAML)

     CAR1 : champ de caracteristiques geometriques (type MCHAML,
        sous-type CARACTERISTIQUES) necessaire pour certains
        elements (poutres ,coques,..).

     CHPO2 : champ de valeurs nodales (type CHPOINT)

     Remarque : Actuellement, cet operateur ne fonctionne que pour
     ___________ les modeles MECANIQUE, et pour les elements massifs,
        DKT et COQ4. Les champs volumiques doivent avoir des
        noms de composantes de forces.
        Il permet egalement de definir le terme source du au
        potentiel vecteur inducteur en formulation
        MAGNETODYNAMIQUE. Les champs volumiques doivent avoir des
        noms de composantes AX AY AZ.

## COAC [Multi-physique Multi-physique]
Operateur COAC

    CHPO3 = COAC TAB1 'FORCEION' CHPO1 < 'TEMPERAT' CHPO2 > ;

     Objet
    Calcul du coefficient d'activite d'une eau, en tout point
    d'un domaine pour un systeme chimique donne.

    Commentaires
    TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

    'FORCEION' mot cle ( doit preceder CHPO1)

    CHPO1 nom d'un objet de type CHPOIN ayant une composante scalaire,
        et contenant la valeur de la force ionique en chaque
        point du maillage.

    'TEMPERAT' mot cle ( doit preceder CHPO2)

    CHPO2 nom d'un objet de type CHPOIN contenant la temperature en
        chaque point du maillage. Cette temperature est exprimee
        en degres Celsius.

    CHPO3 objet de type CHPOIN ayant une composante scalaire, et
        contenant la valeur du coefficient d'activite en chaque
        point du maillage.

## CODENORM [Mecanique Resolution] (proc)
     Procedure CODENORM

     CODENORME TAB1 ;

     Objet :

     La procedure CODENORME effectue une etude reglementaire des tuyauterie.
     Les reglements disponibles sont:

     - RCC-M CLASSES 1 et 2, CRITERES C et D (B3600 et C3600, edition 1993)
     - RCC-MR CLASSE 1 , CRITERES C et D (RB3600, edition 1993)
     - ASME CLASSES 1 et 2, CRITERES C et D (NB3600 et NC3600, edition 1995)
     - ETCM CLASSE 2 , CRITERES C et D (FRAMATOME N° IT/M-96-0670)
     - EMSI CLASSE 1 , CRITERES C et D (CRITERE 3459)

REMARQUES:
  a) Les coefficients (B1&B2) de contrainte et la contrainte admissible
     Sm d'EMSI sont empruntes au RCC-M CLASSE 1.

  b )Les coefficients (B1&B2) de contrainte d'ETCM sont empruntes
     au RCC-M CLASSE 1 et la contrainte admissible Sh au RCC-M CLASSE 2.

  c) La contrainte admissible Sm d'ASME CLASSE 1 est emprunte au
     RCC-M CLASSE 1.

  d) Les coefficients (B1&B2) de contrainte et la contrainte admissible Sm
     d'ASME CLASSE 2 sont identiques a ceux de la CLASSE 1.

  e) Il est possible de definir manuellement les coefficients de contrainte
     ( B1,B2 ) pour l'ensemble des reglements, ainsi que (D1, D21, D22)
     pour RCC-MR. Voir 1.4.4 pour plus de precisions.

  f) Dans le cadre du reglement RCC-MR CLASSE 1, les moments dus aux
     deplacements ne sont pas pris en compte pour l'instant. Ainsi, le
     coefficient d'abattement g est fixe a 0 et les moments m1 (torsion)
     et m'R (flexion) sont pris nuls par defaut. Toutefois, il est possible
     pour l'utilisateur de donner g, m1 et m'R en entree dans l'optique
     d'une evolution de la procedure, g etant normalement donne par calcul.
     Lequel calcul, n'est pas integre a la procedure pour l'instant.

  g) Il est possible d'utiliser la procedure apres une reprise de fichier
     d'un calcul. Mais il y a des restrictions a cette fonctionnalite.
     En effet, la recuperation des champs de moments issus de plusieurs
     calculs , par recuperation de fichiers, conduit a une incompatibilite
     de pointeurs sur les modeles, les caracteristiques et les maillages.
     Ainsi, on ne peut pas recuperer les moments dus au poids dans un fichier,
     ceux dus aux efforts permanents dans un autre, et ceux du au seisme encore
     dans un autre, meme si la geometrie de la ligne, le maillage, le modele et
     les caracteristiques sont identiques dans les trois calculs qui ont
     genere ces fichiers.

     On peut soit:

     - traiter separement les cas de contraintes dues au poids, dues aux
       efforts permanents, dues aux efforts sismiques issus de fichiers
       differents.

     - enchainer le calcul des contraintes dues aux efforts permanents (calcul
       statique) et le calcul des contraintes dues aux efforts sismiques
       (calcul spectrale ou time history) avec des fichiers de jeu de donnees
       differents, mais avec une reprise de fichier. Pour chaque calcul, il
       faut sauver, dans un fichier, les modeles, les maillages, les
       caracteristiques, les contraintes, ainsi que tout ce qui est necessaire
       au calcul suivant afin d'avoir les meme pointeurs sur ces objets.
       Ce qui evite les incompatibilites.

     - recuperer toutes ces contraintes d'un fichier issu d'un calcul qui
       comportait tous ces champs. C'est a dire que l'on a enchaine le calcul
       des contraintes dues aux efforts permanents et le calcul des contraintes
       dues aux efforts sismiques dans le meme jeu de donnees.

     UTILISATION DE LA PROCEDURE
     Cette procedure peut etre utilisee de deux façons.

     Premier cas: on peut tester les differentes reglementations sur des
     valeurs ponctuelles de moments, pression et donnees geometriques (rayon
     exterieur, rayon de courbure pour les coudes, epaisseur). Ce sont
     des ENTIERS ou des FLOTTANTS. On se place dans le mode dit "MANUEL".
[… notice tronquée ; texte complet dans l'archive PCW_24]

## COLI [Mathematiques Autres]
Operateur COLI

CH1 = COLI | CH2 FLOT2  CH3 FLOT3  ( CH4 FLOT4 ...) | ;
        | LISTCHP1 LISTREE1  |
        | TABL1  LISTREE1  |

Objet :

L'operateur COLI effectue la combinaison lineaire
d'objets de meme type ponderes par une suite de reels.

Syntaxe 1 :

CH1 = COLI CH2 FLOT2 CH3 FLOT3 ( CH4 FLOT4 ...) ;

CH2, CH3, ... : objets de type CHPOINT ou MCHAML
FLOT2, FLOT3, ... : type FLOTTANT

CH1 : nouveau champ resultat de meme type que les CHi
CH1 = CH2 * FLOT2 + CH3 * FLOT3 + ...

Syntaxe 2 :

CH1 = COLI LISTCHP1 LISTREE1 ;

Les champs CH2, CH3 ... de type CHPOINT sont dans un LISTCHPO
Les reels FLOT2, FLOT3, ... sont dans un LISTREEL

Syntaxe 3 :

CH1 = COLI TABL1 LISTREE1 ;

Les objets de type CHPOINT, MCHAML ou LISTREEL sont indexes dans une
TABLE par des ENTIERS de 1 a N par PAS de 1
Les reels FLOT2, FLOT3, ... sont dans un LISTREEL

Exemple avec une table de CHPOINT ou de MCHAML:
  TABL1 . 1 = CH2;
  TABL1 . 2 = CH3;
  LIST1 = PROG FLOT2 FLOT3;
  CH1 = COLI TABL1 LIST1;
Le resultat CH1 est un nouveau champ de meme type que les CHi
tel que :CH1 = CH2 * FLOT2 + CH3 * FLOT3

Exemple avec une table de LISTREEL:
  TABL1 . 1 = COS (PROG 1. PAS 1. 360.);
  TABL1 . 2 = SIN (PROG 1. PAS 1. 360.);
  LIST1 = PROG FLOT2 FLOT3;
  CH1 = COLI TABL1 LIST1;
Le resultat CH1 est un LISTREEL tel que :
CH1 = (TABL1 . 1) * FLOT2 + (TABL1 . 2) * FLOT3

## COLL [Langage Base]
    Operateur COLLABORATEUR

L'opérateur COLL(aborateur) fournit des fonctionnalités de communication et
d'échanges d'objets entre différents collaborateurs de Cast3m (copies) pour
pouvoir réaliser des calculs à mémoire distribuée.
L'opérateur utilise actuellement la libraire openMPI pour transmettre les
messages. La fonctionnalité voulue est sélectionnée en précisant un mot clef
qui peut être :
        -DEBUT
        -FIN
        -RANG
        -NOMBRE
        -ENVOYER
        -RECEVOIR

 1) Initialisation des communications : DEBUT
        Syntaxe :
      COLL 'DEBUT';

        Arguments et résultats :
      N/A

        Description :
      La directive COLL 'DEBUT' initialise l'environnement de communication MPI.
      Elle initialise aussi les piles de communication gardant l'historique des
      communications entre les collaborateurs.

      Cette directive doit être appelée avant toute utilisation des autres
      fonctionnalités des collaborateurs. Un appel à une autre fonctionnalité
      avant un appel à COLL 'DEBUT' provoque une sortie en erreur de l'opérateur
      COLL.
      Elle appelle la fonction mpi_Init_Thread et la documentation d'OpenMPI
      recommande de l'appeler le plus tôt possible. De plus, MPI limite son
      appel à une fois par exécution de Cast3m.

 2) Fermeture des communications : FIN
        Syntaxe :
      COLL 'FIN';

        Arguments et résultats :
      N/A

        Description :
      Cette directive ferme l'environnement de communication MPI. Elle libère
      ensuite les piles de communication. Elle doit être appelée avant de
      quitter cast3m et une fois toutes les communications terminées.

      La directive COLL 'FIN' réalise un appel à la fonction mpi_Finalize et
      ne peut être appelée qu'une fois par exécution. Ceci est une limitation
      de MPI.

      Une fois COLL 'FIN' appelée, il n'est plus possible d'obtenir des
      informations sur l'environnement parallèle ou d'échanger des messages même
      après un autre appel à COLL 'DEBUT'.

      Si un collaborateur se termine sans appeler cette routine, l'environnement
      d'exécution MPI détecte une sortie non prévue. Il arrête tous les autres
      collaborateurs et renvoie une erreur.

 3) Récupération du rang du collaborateur : RANG
        Syntaxe :
      ENT1= COLL 'RANG';

        Arguments et résultats :
      ENT1 : entier, numéro du collaborateur

        Description :
      L'opérateur COLL 'RANG' permet de récupérer le numéro du collaborateur
      dans l'environnement parallèle.
      Ce numéro est compris entre 1 et (COLL 'NOMBRE').

 4) Récupération du nombre de collaborateurs : NOMBRE
        Syntaxe :
      ENT1= COLL 'NOMBRE';

        Arguments et résultats :
      ENT1 : entier, nombre de collaborateurs

        Description :
      L'opérateur COLL 'NOMBRE' permet de récupérer le nombre total de
      collaborateurs dans l'environnement parallèle.

 5) Envoi d'un message : ENVOYER
        Syntaxe :
      COLL 'ENVOYER' ENT1 OBJ1 .. OBJi .. OBJn;

        Arguments et résultats :
      ENT1 : Entier, numéro du collaborateur destinataire du message.
      OBJi : Objets à envoyer. Leur type doit faire partie des types supportés.

        Description :
      L'opérateur COLL 'ENVOYER' permet d'envoyer des objets à un collaborateur.
      Cet opérateur est bloquant. L'envoi du message ne commence que lorsque le
      destinataire est prêt à recevoir et l'exécution de l'opérateur ne se
      termine que lorsque le message est reçu.

      Les types d'objet actuellement supportés sont :
        -FLOTTANT : flottant
        -ENTIER : entier
        -LOGIQUE : logique
        -MOT : mot
        -CONFIGUR : configuration
        -POINT : noeud
        -MAILLAGE : maillage
        -CHPOINT : champ par point
        -MCHAML : champ par élément
        -RIGIDITE : rigidité
        -MMODEL : modèle

        Notes :
      L'opérateur COLL 'ENVOYER' utilise des fonctions bloquantes de MPI
      (mpi_send, mpi_recv, mpi_probe). La communication est synchrone et peut
      empêcher un script de se terminer si l'appel à COLL 'RECEVOIR'
      correspondant n'est pas réalisé par le destinataire.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## COLLER [Mecanique Limites] (proc)
   Procedure COLLER

    COQMASF = COLLER VOLUM8 SURF4 ('SOUPLE') ;

FONCTION :

    Definir des jonctions coque-massif ou poutre-massif en 3D.

OPERANDES :

    VOLUM8 : Zone volumique (type MAILLAGE).

    SURF4 : Zone modelisee en coques ou poutres, ou
        ensemble de points de l'enveloppe de VOLUM8 sur lesquels
        on veut connaitre les rotations (type MAILLAGE).

    'SOUPLE' : mot-cle (type MOT) demandant une certaine souplesse a la
        "colle" : on ne definit la jonction qu'en 1 point sur 2.

RESULTATS :

    COQMASF : Matrice (type RIGIDITE) definissant des rotations sur
        quelques points bien choisis de l'enveloppe des massifs.
        A adjoindre aux relations cinematiques (conditions aux
        limites et autres) du probleme.

REMARQUES :

    L'option 'SOUPLE' a ete introduite pour contre-balancer la
    raideur excessive d'un maillage trop grossier.
    l'effet de l'option "souple" est aussi facile a quantifier que
    celui des grosses mailles ...

    COLLER permet aussi de generer les valeurs de rotation sur un
    ensemble de noeuds appartenant a des elements massifs.

    Les valeurs de deplacements sont deja communes aux deux parties
    en raison des noeuds communs (cf. noeud X de l'illustration).

ILLUSTRATIONS :

        +--+--+--+--+ +--+--+--+
        |  |  |  |  |  |  |  |  |
  3D massif +--+--+--+--+ +--+--+--+
        |  |  |  |  |  |  |  |  |
        +--+--+--+--+ +--+--+--+
        |  |  |  |  |  |  |  |  |
        +--+--+--+--+ +--+--+--+
        |  |  |  |  |  |  |  |  |
        +--+--X--+--+ +--X--+--+
        I \
  3D coque I \
  ou poutre I \
        I \
        I \

## COLLER1 [Mecanique Limites] (proc)
   Procedure COLLER1 :

    POUTCOQ = COLLER1 SURF4 POUT2 (ANG) ;

FONCTION:

    Definir des jonctions poutre-coque en 3D, de facon a permettre
    aux coques de resister a des moments de torsion.

OPERANDES:

    SURF4 : Zone en plaques ou coques (type MAILLAGE).
    POUT2 : Zone en poutres, ou simplement l'ensemble des points de la
        surface sur lesquels on veut connaitre la rotation normale
        (type MAILLAGE).
    ANG : Angle mini (type FLOTTANT en degres) d'une poutre avec le
        plan des coques qu'elle touche. En deca de cette valeur
        d'angle, on n'effectue aucune operation particuliere de
        liaison (5 degres par defaut).

RESULTATS:

    POUTCOQ : Matrice (type RIGIDITE) definissant les rotations
        normales aux coques.
        A adjoindre aux relations cinematiques (conditions aux
        limites et autres) du probleme.

REMARQUES :

    COLLER permet aussi de generer les valeurs de rotation normale sur
    un ensemble de noeuds appartenant a des elements coques.

    Les valeurs de deplacements sont deja communes aux deux parties
    en raison des noeuds communs (cf. noeud X de l'illustration).

ILLUSTRATIONS :

  3D coque +--+--X--+--+ +--X--+--+
        I \
        I \
  3D poutre I \
        I \
        I \

## COLLER2 [Mecanique Limites] (proc)
   Procedure COLLER2

    RELA84 = COLLER2 MOD4 MAT4 MOD8 PGLUE (CON1 CON2);

FONCTION :

    Definir des jonctions coque-massif en 2D et 3D sans avoir de
    noeuds communs mais avec une geometrie compatible.

OPERANDES :

    MOD4 : Modele de coque (type MMODEL).

    MAT4 : Caracteristiques de la coque (epaisseur) (type MCHAML).

    MOD8 : Modele massif (type MMODEL).

    PGLUE : Points de la coque a coller au massif (type MAILLAGE ou
        POINT).

    CON1, CON2 : Noms des constituants des couches inferieures et
        superieures dans le cas d'une coque multicouche
        (type MOT).

RESULTATS :

    RELA84 : Matrice (type RIGIDITE) definissant des liaisons
        coque-massif.
        A adjoindre aux relations cinematiques (conditions aux
        limites et autres) du probleme.

REMARQUES :

  - D'abord, de nouveaux noeuds avec une cinematique de type massif
    sont generes en face des noeud PGLUE sur les faces superieure et
    inferieure de la coque, et lies a ces derniers.
  - Ensuite ces nouveaux noeuds sont relies au massif via RELA 'ACCRO'
    ce qui implique que leur positionnement geometrique
    (Xnew = Xpglue +/- EPAI*normale) doit correspondre a l'interieur
    ou la frontiere du volume du massif.

ILLUSTRATIONS :

        +---+---+---+ +--+--+--+
        |  |  |  |  |  |  |  |
  3D massif +---+---+---+ +--+--+--+
        |  |  |  |  |  |  |  |
        +---+---+---+ +--+--+--+
        |  |  |  |  |  |  |  |
        +---+---+---+ +--+--+--+
        |  |  |  |  |  |  |  | I
        +---+---+---+ +--+--+--+ I
        I I
  3D coque I I
  ou poutre I I
        I I
        I

## COMB [Mathematiques Autres]
    Operateur COMBTABLE

    CHPO1 = COMB ('SEMBLABLE') CHPO2 TAB1 ;

    Objet :

    L'operateur COMBTABLE effectue une combinaison lineaire d'objets
consignes dans une table indicee par des objets de type POINT.

    Commentaire :

  CHPO2 : champ (type CHPOINT) a une composante de nom quelconque,
        contenant les coefficients de ponderation. Ce champ s'appuie
        sur l'ensemble ou une partie des points indiçant la table.
        Ne definir CHPO2 que sur une partie equivaut a affecter des
        coefficients de ponderation nuls aux CHPOINT d'indice-point
        exclus de cette partie.

    TAB1 : table contenant les CHPOINT a combiner (type TABLE)

    CHPO1 : champ resultat (type CHPOINT)

    Remarque :

    L'option 'SEMBLABLE' indique que les CHPOINT a combiner s'appuient
sur une Meme geometrie.

    C'est une option qui accelere le calcul, mais qui demande a
l'utilisateur une bonne maitrise et une bonne connaissance de la
structure de ses CHPOINT.

## COMM [Langage Base]
    Directive COMMENTAIRE

    COMM TEXT1 ;

    Objet :

    La directive COMM permet d'introduire des commentaires
dans les donnees, TEXT1 etant un objet de type TEXTE.

    Nota : Le commentaire prend fin au ";" et ne doit pas comporter de
parentheses ni de signe "=";

    Remarque :

    Cette directive est tres avantageusement remplacee par la
mise en colonne 1 d'une asterisque *. Dans ce cas, la ligne est
sautee au moment de la lecture et aucun caractere n'est interdit.

    Exemple :

    COMM ' ceci est un commentaire ';
*  celui-ci coute moins cher |

## COMP [Fluides Modele]
Operateur COMP
-------------- CARA

CHE1 = COMP MOD1 CHE2 CHE3 ;

Objet :

L'operateur COMP etablit l'evolution des champs relatifs a un
modele physique, lois de comportement, d'etat ou bien cinetique,
entre un instant initiale et un instant final.
Il est necessaire de preciser l'objet MMODEL qui induit les lois,
l'etat initial des champs necessaires a la formulation contenue
dans le modele et l'etat final des variables de controle.

Applications possibles : lois de comportement en mecanique,
transitions de phase en metallurgie ...

Commentaire :

MOD1 : type MMODEL

CHE2 : type MCHAML, ensemble des grandeurs decrivant l'etat
        initial pour chaque modele elementaire, les champs etant
        identifies par des noms de composantes (en 4 lettres)
        et de constituants. Sont inclus notamment la date 'TEMP',
        la temperature 'T '.

CHE3 : type MCHAML, ensemble des grandeurs decrivant l'etat
        final pour chaque modele elementaire, les champs etant
        identifies de la meme maniere que ci-dessus.
        Sont inclus notamment la date 'TEMP', la temperature 'T '.

CHE1 : type MCHAML, ensemble des grandeurs decrivant l'etat final.

Remarques :

Mecanique : Les contraintes, variables internes, deformations
        inelastiques, deformations totales, ainsi eventuellement
        que les caracteristiques materiau et geometrique, les
        parametres externes du modele (s'il en existe) et autres
        grandeurs relatives a l'etat initial sont rangees dans CHE2.
        La deformation totale, les caracteristiques de materiau et
        geometriques, les parametres externes du modele (s'il en
        existe) relatifs a l'etat final sont ranges dans CHE3.
        CHE1 contient alors entre autre les nouvelles contraintes,
        variables internes et deformations inelastiques.

Metallurgie : La temperature, le temps et les caracteristiques
        materiau initiales, telles les proportions de phases ou
        les tailles de grain, sont rangees dans CHE2. La
        temperature finale est rangee dans CHE3. CHE1 contient
        les caracteristiques finales, notamment les proportions
        de phases.

## COMT [Mathematiques Traitement]
Operateur COMT

L'operateur COMT determine :
- le nombre de chocs de plusieurs enregistrements d'impacts au cours
  du temps (1ere syntaxe),
- ou le nombre + les maxima des forces et/ou les minima associes
  aux maxima et/ou les instants de debut
  et/ou de fin des chocs d'un enregistrement unique (2eme syntaxe).
Chaque choc est detecte par le depassement d'un seuil predefini.
Le minimum associe a un maximum est defini comme le minimum des forces comprises
entre ce maximum et le maximum precedent.
Si a l'instant initial le seuil est deja depasse, le minimum associe
au premier maximum est pris egal a la valeur du seuil.

|  1ere syntaxe : calcul du nombre de chocs  |

LENT1 = COMT EVOL1 (FLOT1) ;

Commentaire :

EVOL1 : Enregistrements des forces de chocs au cours du temps
        (type EVOLUTION). Il peut y avoir plusieurs courbes dans
        EVOL1.

FLOT1 : Seuil de declenchement de l'acquisition en % de la valeur
        maximale en valeur absolue des chocs (1.D-6% par defaut).
        (type FLOTTANT).

LENT1 : Objet contenant autant de valeurs qu'il y a de courbes
        dans EVOL1 (type LISTENTI).

|  2eme syntaxe : determination des temps de chocs  |

ENT1 (LREE1) (LREE2) (LENT2 et/ou LENT3)
= COMT EVOL1 (FLOT1) ('MINI') ('MAXI') ('DEBU' et/ou 'FIN');

Commentaire :

EVOL1 : Enregistrements des forces de chocs au cours du temps
        (type EVOLUTION). Il ne doit y avoir qu'une seule courbe
        dans EVOL1.

FLOT1 : Seuil de declenchement de l'acquisition en % de la valeur
        maximale en valeur absolue des chocs (1.D-6% par defaut).
        (type FLOTTANT).

ENT1 : Nombre de chocs (type ENTIER)

LREE1 : Liste des minima des forces associes aux maxima
        (type LISTREEL)

LREE2 : Liste des maxima des forces de chocs de chaque impact
        (type LISTREEL)

LENT2 : Objet contenant les indices de debut de choc, c'est-a-dire
        les entiers i tels que F_i < seuil et F_i+1 > seuil
        (type LISTENTI)

LENT3 : Objet contenant les indices de fin de choc, c'est-a-dire
        les entiers i tels que F_i > seuil et F_i+1 < seuil
        (type LISTENTI)

## CONC [Mathematiques Fonctions]
    Operateur CONCAT

    EVOL3 = CONCAT EVOL1 EVOL2 ;

    Objet :

    L'operateur CONCAT effectue la concatenation de deux objets.

    Commentaire :

    EVOL1, EVOL2 : objets a concatener (type EVOLUTION)
        Ils possedent le Meme nombre de courbes, N1; celles-ci
        sont mises bout a bout deux par deux.

    EVOL3 : resultat (type EVOLUTION) contenant N1 courbes

    Remarque :

    Pour la concatenation, on place en premier la courbe dont
la premiere abscisse est inferieure ou egale a la premiere abscisse de
l'autre courbe.

## COND [Thermique Modele]
    Operateur CONDUCTIVITE

    RIG1 = CONDUCTIVITE MMODE1 CAR1 ;

    Objet :

    L'operateur CONDUCTIVITE cree une matrice de conductivite, de
sous-type : conductivite, convection ou rayonnement selon le modele.

    Commentaire :

    MMODE1 : structure modelisee (type MMODEL).

    CAR1 : caracteristiques physiques de la structure
        (type MCHAML, sous-type CARACTERISTIQUES)

    RIG1 : matrice de conductivite (type RIGIDITE, sous-type
        CONDUCTIVITE, CONVECTION ou RAYONNEMENT).

    Remarque importante :

   La designation des peaux de la coque se fait par rapport a la
   normale exterieure de l'element : la peau superieure est placee
   dans le sens de la normale exterieure vis-a-vis du plan median.
   Dans le cas oº les elements ne sont pas orientes d'une façon
   coherente, il faut les reorienter en utilisant l'operateur ORIENT.

## CONDENS [Fluides Resolution] (proc)
   Procedure CONDENS

   QC Fcond Econd Hcond KKC ROVI FHP HT = CONDENS RXT
   $paroic TP TF MRVP KHcu;

   ENTREES : RXT TABLE
        $paroic MMODEL de la paroi condensante
        TP,TF,MRVP MOT:
        TP=indice du CHPO de temperature paroi dans RXT.'TIC'
        TF=indice du CHPO de temperature fluide
        MRVP=indice du CHPO de masse volumique de vapeur

        KHcu FLOTTANT: coefficient d'echange convectif utilisateur

   SORTIES : QC,Econd,Hcond FLOTTANT
        Fcond,KKC,ROVI,FHP,HT CHPO
        QC=debit de masse d'eau condensee
        Econd=energie condensee
        Hcond=enthalpie condensee
        Fcond=flux surfacique de masse condenssee
        KKC=coefficient d'echange de masse
        ROVI=masse volumique de vapeur a l'interface (saturation)
        FHP=flux d'energie total convection+condensation
        HT=coefficient d'echange thermique

   OBJET :

La procedure CONDENS calcule le flux condense par un modele de type
Chilton-Colburn et la correlation de convection naturelle :
     Sh = kL/Dv = 0.13 (Gr Sc)**1/3
     Jv = k ro (Yv - Yvsat) en kg/m²s

   Commentaires

Une option dont le mot-cle defini dans la table RXT ('MODCOND')
permet d'utiliser une version valable une fraction massique de
de vapeur quelconque (< 0.9999). cf. notice de EXECRXT.

## CONF [Maillage Manipulation]
    Directive CONFONDRE

    CONF POIN1 POIN2 ;

    Objet :

    La directive CONFONDRE reunit les points POIN1 et POIN2 au point
POIN2 (TYPE POINT).

## CONG [Maillage Lignes]
    Operateur CONGE

    GEO1 GEO3 GEO2 = LIG1 CONG (N1) FLOT1 LIG2 ('DOUBLE') ;

    Objet :

    L'operateur CONGE permet de construire un conge de raccordement
(circulaire) entre deux lignes LIG1 et LIG2.

    Commentaire :

    LIG1 | : lignes a raccorder (type MAILLAGE)
    LIG2 |

    FLOT1 : rayon du conge (type FLOTTANT)

    N1 : nombre d'elements generes (type ENTIER)

    GEO1 | : segments encadrant le conge (type MAILLAGE)
    GEO2 |  ces segments sont des parties des lignes LIG1 et LIG2

    GEO3 : conge (type MAILLAGE)

    Remarque:

    Les resultats sont dans l'ordre decrit ci-dessus (GEO1, GEO3, GEO2).

    Le conge est decoupe en N1 elements si N1 est specifie. Sinon le
 decoupage est etabli en fonction des densites associees aux points de
lignes LIG1 et LIG2.

        <-- <--
        -------------- /----------
        |  LIG1  /  GEO1
        |  /GEO3
        |  /
        |  |  ====>>  |
        V  | LIG2  |  |
        |  V  | GEO2
        |  |
        |  |

    Option DOUBLE :

    L'operateur cree un raccordement en "s" (appele "double coude")
entre 2 lignes non secantes. Ce raccordement est centre sur le dernier
point de la ligne LIG1 lorsque les lignes sont paralleles et sinon
au milieu de la droite qui realise la distance minimale entre les
deux lignes .

    --> -->
----------- -------..
    LIG1 GEO1 :.
        :. GEO3
        ====>> :.
        :.
        LIG2 :. GEO2
       ------------------ ----------
        --> -->

## CONN [Fluides Resolution]
    Operateur CONNECTIVITE

    CHAM1=CONN MODL1 |FLOT1 |'NORMAL'  (MOT1);
        |CHAM2 |'POINT'  POIN1  MOT1 ;
        |'DROITE'  POIN1 POIN2  MOT1 ;
        |'PLAN'  POIN1 POIN2 POIN3 MOT1 ;
        |'TRANS'  POIN1  MOT1 ;

    Objet :

    L'operateur CONNECTIVITE determine le champ par element CHAM1
(sous-type CONNECTIVITE NON LOCAL) des elements de MODL1, sans
modification ou bien symetrises par rapport a un point ou une droite
ou un plan ou encore translates, se trouvant a une distance inferieure
a FLOT1 de chaque element de MODL1. La distance peut variee dans le
maillage sous-tendant le modele et est alors specifiee par la composante
'NLAR' du MCHAML CHAM1 (sous-type CARACTERISTIQUE).

    Commentaire :

    'POINT' : mot-cle indiquant que l'on etablit les connectivites
        par rapport a un maillage symetrise par rapport a
        un point, suivi de:

     POIN1 : point de symetrie (type POINT)

    'DROITE' : mot-cle indiquant que l'on etablit les connectivites
        par rapport a un maillage symetrise par rapport a
        une droite, suivi de:

     POIN1 |  : deux points definissant une droite (type POINT)
     POIN2 |

    'PLAN' : mot-cle indiquant que l'on etablit les connectivites
        par rapport a un maillage symetrise par rapport a
        un plan, suivi de:

     POIN1 |  : trois points definissant un plan (type POINT)
     POIN2 |
     POIN3 |

    'TRANS' : mot-cle indiquant que l'on etablit les connectivites
        par rapport a un maillage translate suivant un vecteur,
        suivi de:

     POIN1 : vecteur de translation (type POINT)

     MOT1 : mot indiquant le nom du constituant (facultatif dans
        le cas 'NORMAL')

    Remarque :

    Cet operateur constitue un pre-traitement pour les calculs
en "non-local" (voir l'operateur NLOC).

    Attention :

    MODL1 ne doit comporter qu'un seul constituant, et etre associe
a un maillage comportant une seule region geometrique.

    MOT1 sert a distinguer parmis les connectivites associees a un meme
modele. Des connectivites differentes doivent avoir des noms de constituant
differents.

    Exemple :
        P4 X------------X P3
    Soit le maillage rectangulaire  |  |
    MESH genere a l'aide de quatres  |  MESH  |
    points P1,P2,P3,P4. Soit MMOD  |  |
    un modele associe a MESH. P1 X------------X P2

    On veut faire un calcul non local (voir l'operateur NLOC) sur MESH dans
    un cas ou l'on a physiquement deux axes de symetrie P1-P4 et P1-P2. En
    notant L la longueur caracteristique, la connectivite a generer est la
    suivante:

    CONN1='CONN' MMOD L 'NORMAL' 'INTERIEUR';
    CONN2='CONN' MMOD L 'DROITE' P1 P2 'BORD P1-P2';
    CONN3='CONN' MMOD L 'DROITE' P1 P4 'BORD P1-P4';
    CONN4='CONN' MMOD L 'POINT' P1 'COIN MANQUANT P1';
    CONN_TOT=CONN1 'ET' CONN2 'ET' CONN3 'ET' CONN4;

## CONT [Maillage Lignes]
Operateur CONTOUR
----------------- TRAC

GEO1 = CONTOUR ('NOID') (|'EXTE'|) GEO2 ;
        |'INTE'|
        |'TOUT'|

Objet :

L'operateur CONTOUR construit le contour d'un maillage.

Commentaire :

GEO2 : objet dont on veut le contour (type MAILLAGE)

GEO1 : contour de l'objet GEO2 (type MAILLAGE)

Remarques :

1) Quand le contour est inexistant, une erreur est declenchee sauf
   si le mot-cle 'NOID' est present (auquel cas un maillage vide
   est renvoye)

2) Les elements ponctuels, lineiques et volumiques de GEO2 n'ont
   pas de contour

3) Une arete d'un element surfacique de GEO2 appartient au contour
   GEO1 si :

   a) elle appartient a un seul element (option 'EXTE' par defaut)
      => frontiere(s) exterieure(s) de GEO2

   b) elle est partagee par au moins 3 elements (option 'INTE')
      => frontiere(s) interieure(s) entre les sous-maillages
        simples de GEO2 (i.e. generalement homeomorphes a des
        disques ou a des tores)

   c) elle n'est pas commune a exactement 2 elements (option 'TOUT')
      => union des frontieres externe(s) et interne(s) de GEO2

4) En 2D, seule la notion de frontiere exterieure a generalement
   du sens (pas de jonction entre 3 surfaces simples ou plus)

## CONTINU [Mecanique Resolution] (proc)
Procedure CONTINU
______________ CON_CALC AFT

  CONTINU TAB1;

Objet :

La procedure CONTINU propose de resoudre des problemes non-lineaires
poses sous la forme d'equations algebriques (1) qui dependent
d'un parametre (pseudo-temps noté t)
par une methode de continuation par pseudo-longueur d'arc.

  R(U,t) = Fext(t) + Fnl(U) - Fint(U,\sigma) = 0 (1.a)
  R(U,t) = Fext(t) + Fnl(U) + Z(t) U = 0 (1.b)

avec :

  R : vecteur Residu
  U : vecteur des inconnues
  Fext : vecteur des forces exterieures
  Fint : vecteur des forces internes (=\int B^T \sigma)
  Fnl : vecteur des forces non-lineaires
  Z : matrice de raideur dynamique (voir la procedure HBM)
  t : pseudo-temps

Le calcul est realise en 2 etapes :

1. Pas predicteur :

   A partir d'une precedente position (U_n, t_n), le probleme
   linearise est resolu (2) et une nouvelle position (U_p, t_p) est
   trouvee en imposant la longueur de l'increment (3) egale a ds.

      dR/dU * dU_p = - dR/dt * dt_p (2)
      ds^2 = dt_p^2/dt_ref^2 + dU_p^T*dU_p / dU_ref^2 (3)

   avec :
      dU_p = U_p - U_n
      dt_p = t_p - t_n
      ds = 1 initialement, mais de valeur adaptative
        selon la difficulte de convergence

2. Pas correcteurs :

   A partir de la position predite (U_p, t_p), des corrections
   successives (4) sont realisees dans le plan orthognal a la
   prediction jusqu'a rendre le residu inferieur a une tolerance
   donnee.

      [ dR/dU dR/dt ] * (dU^(i)) = (-R^(i-1)) (4)
      [ dU_p dt_p ] (dt^(i)) ( 0 )

Entree : (on indique entre parentheses les entrees valables
_______ uniquement avec les problemens de type a ou b)

TABHBM = TABLE

   . 'HBM' = VRAI pour indiquer que l'on
        souhaite resoudre un probleme
        du type (b)
        (FAUX par defaut)
   . 'MODELE' = modele mecanique utilise (a)
   . 'CARACTERISTIQUES' = materiau et caracteristiques (a)
   . | 'RIGIDITE_CONSTANTE' (a) | = raideur K (hors modele)
     | 'RIGIDITE_HBM'  (b) |
   . | 'AMORTISSEMENT_CONSTANT' (a)| = amortissement C
     | 'AMORTISSEMENT_HBM'  (b)|
   . | 'MASSE_CONSTANTE' (a) |  = masse M
     | 'MASSE_HBM'  (b) |
   . | 'BLOCAGES_MECANIQUES' (a) |= Kblocages (hors modele)
     | 'BLOCAGES_HBM'  (b) |
   . 'CHARGEMENT' = Fext(t)

   . 'MAXI_DEPLACEMENT' = dU_ref
   . 'TEMPS_CALCULES' = listreel de la discretisation
        souhaitee pour les pseudo-pas de
        temps t
        (les temps rellements converges
        seront differents et stockes a
        l'indice TEMPS_PROG)
   . 'FREQUENCE' (b) = evolution de la frequence
        fondamentale du probleme w(t)
        (w(t)=t par defaut)
        voir remarque 1 pour les unites

   . 'HYPOTHESE_DEFORMATIONS' = LINEAIRE (par defaut)
        QUADRATIQUE
        TRUESDELL
        JAUMANN
        UTILISATEUR
   . 'GRANDS_DEPLACEMENTS' = VRAI en grand deplacements (a)

   . 'PROCEDURE_CHARMECA' = VRAI si forces non-lineaires
        a: pression suiveuse
        b: terme Fnl(U)
        voir remarque 2
   . 'PROCEDURE_FREQUENCE_TEMPS' (b) = 'AFT' pour l'utilisation de
        la procedure AFT lors du calcul
        des efforts et Jacobienne non-
        lineaires
   . 'N_PT_TFR' (b) = 2**N_PT_TFR points seront
        utilises pour la discretisation
        temporelle lors de l'AFT

   . 'PAS_SAUVES' = entier N indiquant de sauver les
        resultats (U,t,\sigma) dans une
        table tous les N pas

   . 'STABILITE' = listmots de mots-cles parmi :
        + DIAG pour sauver le nombre de
        termes diagonaux negatifs
        comptes lors de la factorisation
        + FLOQ pour le calcul des
        exposants de Floquet (b)
   . |'RESULTATS'  (a) |  = table des resultats attendus
     |'RESULTATS_HBM' (b) |
        . i . 'POINT_MESURE'
        . 'COMPOSANTES'
        . 'COULEUR'
        . 'TITRE'

   . 'MAXITERATION' = nombre maxi d'iterations par pas
        (24 par defaut)
   . 'NB_ITERATION' = nombre d'iterations juge ideal
        (6 par defaut)
   . 'MAXIPAS' = nombre maxi de pas
        (1000 par defaut)
   . 'PRECISION' = tolerance relative sur le residu
        (1.E-6 par defaut)
   . 'COMPOSANTES'
        . | 'FORCE'  (a) |  = listmots des composantes a uti-
        . | 'FORCE_HBM' (b) |  -liser dans le produit scalaire
        definissant la norme du residu

Sortie :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CONTSEG3 [Maillage Autres] (proc)
    Procedure CONTSEG3

    RI1 MA1 MA2 = CONTSEG3 MA3 MA4 ;

    Objet :

    Cette procedure prepare le travail en vue de l'utilisation des
contacts unilateraux automatique entre deux lignes (composees
d'elements de type SEG3). A partir des deux lignes (MA3 et MA4)
decrites comme pour l'operateur IMPO c'est a dire orientees de telle
façon que l'autre ligne est sur leur flanc droit, on fournit un objet
de type rigidite et deux nouveaux objets maillage contenant des SEG2.

       MA3 ---------->--->
       MA4 <--------<--------

   En sortie:

    RI1 : objet de type rigidite qui contient des relations entre
        les noeuds milieux des SEG3 et les noeuds extremites et
        qu'il faut additionner aux autres conditions de
        blocages.

    MA1,MA2: objets maillages contenant des elements de type SEG2
        a utiliser pour definir les contacts unilateraux

   Remarque : Les contacts ne seront assures qu'entre les lignes MA1
        et MA2 qui ne contiennent que les noeuds extremites.
        Les penetrations des noeuds milieux ne seront pas
        detectees.

## CONV [Mecanique Limites]
 Operateur CONVECTION

 CHPO1 = CONV  MMODE1 CHAM1 | MOT1  FLOT1 | ;
        | CHPO2  |

 Objet :

 L'operateur CONVECTION permet d'imposer une condition de flux
 lineaire avec une temperature exterieure :
   Flux = S.H.Text

 Commentaire :

 MMODE1 : Modele de 'THERMIQUE' de 'CONVECTION' ou 'RAYONNEMENT'
        portant sur la surface qui echange (type MMODEL)

 CHAM1 : Materiaux representant le coefficient d'echange sur la
        surface (type MCHAML, sous-type CARACTERISTIQUES) ayant
        une composante 'H'

 MOT1 : Elements coques pour lesquels il faut preciser quelle
        face echange (COQ2,COQ2,COQ4,COQ6,COQ8)
        'TINF','TSUP'

        Elements classiques
        'T'

 FLOT1 : Valeur de la temperature exterieure (type FLOTTANT)

 CHPO2 : Valeurs de la temperature exterieure pour les noeuds du
        MAILLAGE de MMODE1 (type CHPOINT)

 CHPO1 : Flux nodaux equivalents (Second Membre) (type CHPOINT)

Remarque importante :

La designation des peaux de la coque se fait par rapport a la
normale exterieure de l'element : la peau superieure est placee dans
le sens de la normale exterieure vis-a-vis du plan median. Dans le
cas ou les elements ne sont pas orientes d'une facon coherente, il
faut les reorienter en utilisant l'operateur ORIE.

Dans le cas ou CHPO2 a plusieurs composantes, les noms de celles-ci
permettront de differencier les différents flux. Les composantes sont
a choisir parmi les valeurs de MOT1. Ceci permet lors d'appels a
PASAPAS de definir un chargement de type 'TECO' avec des temperatures
controlees pour la 'CONVECTION' ou le 'RAYONNEMENT'.

Remarque :

L'operateur 'CONV' est utilise pour calculer le second membre associe
a la resolution d'un probleme de RAYONNEMENT par linearisation du
coefficient d'echange. Dans ce cas, le modele passe en argument est
de formulation RAYONNEMENT.

## CONVT [Langage Caracteres] (proc)
Procedure CONVT
---------------

MOT2 = CONVT FLOT1 (ENTI1) (MOT1) ;

Objet :

Cet operateur convertit un temps donne en secondes, en une chaine
de caracteres contenant ce temps exprime dans l'unite pertinente
(us,ms,s,h,j,a)

Commentaire :

FLOT1 : le temps, en secondes, a exprimer

ENTI1 : le nombre de chiffres apres la virgule (voir @FIX)
        (facultatif - defaut 2)

MOT1 : l'unite dans laquelle convertir le temps (facultative)
        choix possibles : US,MS,S,H,J,D,A,Y

MOT2 : le mot affichable, de forme XXX.XXs (voir @FIX)

## CON_CALC [Mecanique Resolution] (proc)
 Procedure CON_CALC

 Objet :

Cette procedure est utilisee par la procedure CONTINU.
Elle permet de determiner les differents termes (Residu, Raideur
et leur derivee) necessaire a la resolution.

## COOR [Mathematiques Autres]
Operateur COORDONNEE

RESU1 = COOR  (N1) | POIN1 ;
        | GEO1  (CURV) ;
        | CHPO1 ;
        | CHEL1 ;
        | MOD1  ;

Objet :

   L'operateur COOR renvoie la N1-ieme coordonnee
d'un objet de type POINT, MAILLAGE, CHPOINT, MCHAML ou MMODEL.

   L'option CURV renvoie le champ de coordonnee curviligne
d'une ligne de maillage orientee.

Operations possibles :

        |  ENTREE  |  SORTIE (RESU1)  |
|  OBJET  |  POINT  (POIN1)  |  FLOTTANT  |
|  OBJET  |  MAILLAGE (GEO1)  |  CHPOINT  |
|  OBJET  |  CHPOINT  (CHPO1)  |  CHPOINT  |
|  OBJET  |  MCHAML  (CHEL1)  |  MCHAML  |
|  OBJET  |  MMODEL  (MOD1 )  |  MCHAML  |

Remarque 1 :

Pour un objet de type CHPOINT, l'operateur fournit les coordonnees
des noeuds supportant le champ.

Remarque 2 :

Pour un objet de type MCHAML, l'operateur fournit pour chaque
element les coordonnees des points de l'element ou est exprime le
champ.

Remarque 3 :

L'operateur COOR rend la densite du point considere pour
N1 = IDIM + 1.
Ceci est aussi vrai pour des objets MAILLAGE et CHPOINT.

Remarque 4 :

Si N1 n'est pas indique, l'operateur COOR rend les deux (ou trois)
coordonnees de l'objet.

Remarque 5 :

Pour l'option CURV, la donnee de N1 est sans objet, ni consequence.

Remarque 6 :

Dans le cas d'un MMODEL, COOR renvoie un MCHAML aux noeuds.

Exemples :

X Y Z = COOR P1 ;
  Y = COOR 2 P1 ;

## COPI [Langage Objets]
    Operateur COPIER

      OBJET2 = COPI OBJET1 ('GEOMETRIE') ;

        OBJET1=LISTCHPO,CHPOINT

    Objet :

    L'operateur COPIER cree un nouvel objet OBJET2 semblable a
l'objet donne OBJET1.

      Commentaire :

      OBJET1 : objet dont les type possibles sont : - LISTCHPO
        - CHPOINT
        - LISTREEL
        - MCHAML
        - TABLE

      OBJET2 : objet de Meme type qu'OBJET1

    Remarque :

    Dans le seul cas oº OBJET1 est de type CHPOINT, il est autorise
d'indiquer le mot 'GEOMETRIE'. La geometrie sous-jacente a OBJET1 est
alors dupliquee (c'est a dire creation d'un nouvel ensemble de noeuds
ayant les memes numeros que ceux de la geometrie initiale) pour
constituer le support d'OBJET2, ce qui n'est pas le cas sinon.

## COQ2MAS [Maillage Volumes] (proc)
Procedure COQ2MAS:

      MAIL3D = COQ2MAS MOD1 MAT1 TAB1;

Objet:
     COQ2MAS genere un maillage volumique MAIL3D
     a partir d'un modele de coque pour permettre
     la verification des dimensions et des orientations
     des modeles de coque.
     Chaque couche peut etre representee par une coque
     excentree (maillages contenus dans la table tab1)
     ou un volume excentre ayant l'epaisseur de l'element
     de coque (MAIL3D).
     Les champs de deplacements, de contraintes et
     de variables internes
     s'appuyant sur le maillage de coque initial peuvent
     aussi etre determines sur les nouveaux maillages
     pour visualisation.

Entree:
   MOD1 : Modele de coque multicouche DKT ou DST

   MAT1: Materiau contenant les donnees materiaux
        et les caracteristiques (epaisseur, excentrement)

   TAB1: Table contenant les champs a transferer et
        eventuellement les maillages calcules lors d'un appel
        precedent a la procedure COQ2MAS
        Dans ce dernier cas, les maillages ne sont pas regeneres
        mais ceux de la table sont utilises.

   TAB1. 'DEPLACEMENTS': Table contenant les champs de
        deplacements sur le modele de coque
        (un indice par champs de deplacements)

   TAB1. 'CONTRAINTES': Table contenant les champs de contraintes
        sur le modele de coque

   TAB1. 'VARIABLES_INTERNES': Table contenant les champs de variables
        internes sur le modele de coque

   Remarque: Les deplacements, contraintes et variables internes
        issus de la procedure PASAPAS peuvent etre utilises
        directement en faisant
        TAB1.'DEPLACEMENTS' = TABPASPAS . 'DEPLACEMENTS' ;
        TAB1.'CONTRAINTES' = TABPASPAS . 'CONTRAINTES' ;
        TAB1.'VARIABLES_INTERNES'= TABPASPAS.'VARIABLES_INTERNES';

   TAB1.'RELATION_3D': Si cet indice le table contient le booleen VRAI,
        les relations cinematiques liant le modele de
        coque et le maillage volumique sont crees.

Sortie:
    MAIL3D: Maillage 3D volumique ou surfacique

    TAB1: Table completee des indices:

    TAB1. 'MODELE': Modele de la couche i (a l'indice i)

    TAB1. 'MATERIAU': Materiau de la couche i (a l'indice i)

    TAB1. 'MAILLAGE_FIBRE_MOYENNE' : Maillage surfacique excentre
        au niveau de la fibre moyenne pour la couche i (a l'indice i)

    TAB1. 'MAILLAGE_FIBRE_INFERIEURE' : Maillage surfacique excentre
        au niveau de la fibre inferieure pour la couche i
        (a l'indice i)

    TAB1. 'MAILLAGE_FIBRE_SUPERIEURE' : Maillage surfacique excentre
        au niveau de la fibre superieure pour la couche i
        (a l'indice i)

    TAB1. 'MAILLAGE_VOLUMIQUE': Maillage volumique excentre ayant
        l'epaisseur reelle pour la couche i (a l'indice i)

    TAB1. 'DEPLACEMENTS_FIBRE_MOYENNE': Champs de deplacements
        de la fibre moyenne pour la couche i (a l'indice i)

    TAB1. 'DEPLACEMENTS_FIBRE_INFERIEURE': Champs de deplacements
        de la fibre inferieure pour la couche i (a l'indice i)

    TAB1. 'DEPLACEMENTS_FIBRE_SUPERIEURE': Champs de deplacements
        de la fibre superieure pour la couche i (a l'indice i)

    TAB1. 'DEPLACEMENTS_VOLUMIQUE': Champs de deplacements du maillage
        volumique pour la couche i (a l'indice i)

    TAB1. 'VARI_FIBRE_MOYENNE': Variable interne pour la couche i
        (indice i) uniquement pour la fibre moyenne

    TAB1. 'CONTRAINTES_FIBRE_MOYENNE': Contraintes de la
        fibre moyenne pour la couche i (a l'indice i)

    TAB1. 'CONTRAINTES_FIBRE_INFERIEURE': Champs de contraintes
        de la fibre inferieure pour la couche i (a l'indice i)

    TAB1. 'CONTRAINTES_FIBRE_SUPERIEURE': Champs de contraintes
        de la fibre superieure pour la couche i (a l'indice i)

    TAB1. 'CONTRAINTES_VOLUMIQUE': Champs de contraintes du maillage
        volumique pour la couche i (a l'indice i)

    TAB1.'RELATION_3D': Table contenant les relations cinematiques
        (RIGIDITE) entre le modele de coque et le maillage volumique

   Remarque 1: Les indices 'TOTAL' contiennent les maillages
        pour l'ensemble des couches

   Remarque 2: les contraintes et les variables internes sur
        les couches excentrees sont donnees aux noeuds (CHPO)

   Remarque 3: Les contraintes dans chaque couche sont donnees
        dans le repere local des elements de coque.

## CORI [Fluides Resolution]
Operateur CORIOLIS

Objet :

L'operateur CORIOLIS calcule des matrices de couplage ayant
pour origine des phenomenes lies aux forces de coriolis
(forces proportionnelles a des vitesses dans un repere non galileen)

RIG1 = CORIOLIS MODL1 MAT1 VEC1 ('HARM')

  Commentaire :

 RIG1 : matrice de couplage construite (TYPE rigidite, SOUS-TYPE
     amortissement)

 MODL1: Modele (objet MMODEL)

 MAT1 : Caracteristiques materiau (objet MCHAML)

 VEC1 : Vecteur rotation (objet POINT)

'HARM' : Mot cle facultatif pour specifier si la matrice calculee
        est une impedance dans le cas des modes de Fourier
        pour etre utilisee pour les calculs harmoniques
        (voir operateur IMPE)

Cet operateur est valable pour les elements
BARR, POUT, TUYAU, COQUE et MASSIF 3D et 2D Fourier

## CORMAN [Mechanics Resolution] (proc)
procedure CORMAN

Cette procedure est appelee par la procedure UNPAS, elle
calcule la solution d'un probleme elastique "grands_deplacements"
et "grandes_rotations" par la methode asymptotique numerique.

## CORMASSE [Fluides Resolution] (proc)
   Procedure CORMASSE

     CORMASSE RXT TBT ;

   OBJET :

La procedure CORMASSE est une procedure interne appelee par EXECRXT

   Commentaires

   RXT TABLE :
   TBT TABLE :

## COS [Mathematiques Fonctions]
  RESU1 = 'COS' OBJET1 (MOT1) ;

Operateur COS
------------- ACOS ASIN ATG

Objet :

L'operateur COS calcule le cosinus de l'objet OBJET1.
Les valeurs de OBJET1 doivent etre exprimees en degres.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## COSH [Mathematiques Fonctions]
  RESU1 = 'COSH' OBJET1 (MOT1) ;

Operateur COSH
-------------- ACOS ASIN ATG

Objet :

L'operateur COSH calcule le cosinus hyperbolique de l'objet OBJET1.

        |  OBJET1  |  RESU1  |
        |  ENTIER  |  FLOTTANT  |
        |  FLOTTANT  |  FLOTTANT  |
        |  LISTENTI  |  LISTREEL  |
        |  LISTREEL  |  LISTREEL  |
        |  EVOLUTIO  |  EVOLUTIO  |
        |  CHPOINT  |  CHPOINT  |
        |  MCHAML  |  MCHAML  |

Remarque :

Dans le cas d'un objet EVOLUTIO, MOT1 permet d'indiquer si l'operation
porte sur les abscisses (mot-cle 'ABSC') ou sur les ordonnees (mot-cle
'ORDO', par defaut).

## COSI [Mathematiques Traitement]
Operateur COSI voir aussi : INSI

EVOL1 = COSI EVOL2 (MOT1);

        MOT1='SIMP','LINE'

objet :

Operateur COSI effectue la correction EVOL1 de signaux en
acceleration EVOL2 de façon a assurer une vitesse finale, un
deplacement final et un deplacement moyen nuls quand les signaux
sont integres numeriquement en utilisant operateur INSI.

remarques :

- On suppose que la grille des abscisses est identique pour
  chaque signal.

- On suppose que le pas de temps est uniforme.

- La vitesse et le deplacement initiaux sont supposes nuls.

option:

Diverses methodes d'integration numerique peuvent etre choisies en
utilisant le mot-cle MOT1:

- MOT1='SIMP'(lifie) se refere a l'utilisation d'une methode des
  trapezes pour deduire chaque variable de la discretisation de sa
  derivee.

- MOT1='LINE'(aire) se refere a l'utilisation d'un approximation
  lineaire de acceleration et a son integration consistante.
  Le defaut pour MOT1 est 'SIMP'.

## COTE [Maillage Lignes]
    Operateur COTE

    GEO1 = COTE (I1) GEO2 ;

    Objet :

    L'operateur COTE permet de retrouver le cote I1 de l'objet
GEO2 (type MAILLAGE). Le resultat est un objet GEO1 (type MAILLAGE).

    Remarque 1 :

    Il faut que la construction de l'objet ait permis de definir les
cotes suivants :

    I=1 cote initial d'une surface construite par translation ou
        rotation d'une ligne
    I=2 cote lateral droit
    I=3 cote final
    I=4 cote lateral gauche

    Remarque 2 :

    Le sens de description des cotes est donne en orientant le contour
d'apres l'orientation de la ligne initiale.

        < 3
        |----------|
        |  |
        4  |  |  2
        |----------|
        1 >

    Remarque 3 :

    Si le numero du cote n'est pas indique, l'operateur COTE rend les
quatre (ou trois) cotes de l'objet, GEO1.

    Exemple :

        COTE1 COTE2 COTE3 COTE4 = COTE SURF1 ;

## COUL [Maillage Generaux]
Operateur COULEUR

OBJ2 = OBJ1 COUL ( | MOT1  | ) ;
        ( | LISMO1 | )
        ( | ENT1  | )

Objet :

L'operateur COUL duplique un objet OBJ1 en lui attribuant une
ou plusieurs couleurs choisies.

Commentaire :

OBJ1 : objet original (type MAILLAGE, EVOLUTIO, DEFORME ou
        VECTEUR).

MOT1 : nom de la couleur choisie (type MOT de 4 lettres) parmi
        les noms Cast3M listes dans la palette ci-dessous.

LISMO1 : noms des couleurs choisies (type LISTMOTS), uniquement pour
        les objets de type EVOLUTIO, DEFORME et VECTEUR.

ENT1 : ENTIER, numero de la couleur dans la palette ci-dessous.
        Si ENT1 est negatif, l'operateur attribue la couleur par defaut.

OBJ2 : objet resultat (meme type que OBJ1).

Remarques :

1) En l'absence de couleur choisie (MOT1 et LISMO1 et ENT1 absents),
   la couleur choisie est celle pre-definie par la directive OPTION 'COUL'.

2) La palette des couleurs disponible est la suivante :

   La couleur DEFA depend de l'unite de sortie graphique :
     BLANc ou NOIR selon la couleur de fond.

|No. | Nom Cast3M |  Nom X11  |  Rouge  |  Vert  |  Bleu  |
|1  |  DEFA  |  white/black  | 1./0.  | 1./0.  | 1./0.  |
|2  |  BLEU  |  blue  | 0.0000  | 0.0000  | 1.0000  |
|3  |  ROUG  |  red  | 1.0000  | 0.0000  | 0.0000  |
|4  |  ROSE  |  magenta  | 1.0000  | 0.0000  | 1.0000  |
|5  |  VERT  |  green  | 0.0000  | 1.0000  | 0.0000  |
|6  |  TURQuoise |  MediumTurquoise | 0.0000  | 0.8078  | 0.8196  |
|7  |  JAUNe  |  yellow  | 1.0000  | 1.0000  | 0.0000  |
|8  |  BLANc  |  white  | 1.0000  | 1.0000  | 1.0000  |
|9  |  NOIR  |  black  | 0.0000  | 0.0000  | 0.0000  |
|10  |  VIOLet  |  DarkViolet  | 0.5804  | 0.0000  | 0.8274  |
|11  |  ORANge  |  orange  | 1.0000  | 0.6471  | 0.0000  |
|12  |  AZUR  |  DodgerBlue  | 0.1176  | 0.5647  | 1.0000  |
|13  |  OCEAn  |  MediumSeaGreen  | 0.2353  | 0.7020  | 0.4431  |
|14  |  CYAN  |  LightSkyBlue  | 0.5294  | 0.8078  | 0.9804  |
|15  |  OLIVe  |  YellowGreen  | 0.6039  | 0.8039  | 0.1961  |
|16  |  GRIS  |  gray  | 0.7450  | 0.7450  | 0.7450  |
|17  |  POURpre  |  VioletRed  | 0.8157  | 0.1255  | 0.5647  |
|18  |  BRUN  |  SaddleBrown  | 0.5451  | 0.2706  | 0.0745  |
|19  |  BRIQue  |  Firebrick  | 0.6980  | 0.1333  | 0.1333  |
|20  |  CORAil  |  Coral  | 1.0000  | 0.5000  | 0.3137  |
|21  |  BEIGe  |  Wheat  | 0.9607  | 0.8706  | 0.7019  |
|22  |  OR  |  Gold  | 1.0000  | 0.8431  | 0.0000  |
|23  |  MARIne  |  Navy  | 0.0000  | 0.0000  | 0.5000  |
|24  |  BOUTeille |  DarkGreen  | 0.0000  | 0.3921  | 0.0000  |
|25  |  LIME  |  Chartreuse  | 0.5000  | 1.0000  | 0.0000  |
|26  |  LAVAnde  |  Lavender  | 0.9019  | 0.9019  | 0.9803  |
|27  |  BRONze  |  Goldenrod  | 0.8549  | 0.6470  | 0.1254  |
|28  |  KAKI  |  Khaki  | 0.9411  | 0.9019  | 0.5490  |
|29  |  PEAU  |  LightPink  | 1.0000  | 0.7137  | 0.7568  |
|30  |  CARAmel  |  Peru  | 0.8039  | 0.5215  | 0.2470  |
|31  |  INDIgo  |  Indigo  | 0.2941  | 0.0000  | 0.5882  |

## COUP [Maillage Surfaces]
    Operateur COUPER

    GEO2 = COUP GEO1 POIN1 POIN2 POIN3 ;

    Objet :

  L'operateur COUP genere la coupe 2D GEO2 (type MAILLAGE) d'un
maillage 3D GEO1 (type MAILLAGE) selon le plan defini par les 3
points POIN1, POIN2 et POIN3 (type POINT).

    Commentaire :

    GEO1 : maillage 3D

    GEO2 : maillage de coupe

## COUPLER [Maillage Manipulation] (proc)
   Procedure 'COUPLER'

 GEO2 (GEO3) = COUPLER (GEO1) PO1 CARCOQ (N) ('RAC');

OBJET :

Cette procedure genere le maillage GEO2 deduit de GEO1 par translation
de la demi epaisseur de GEO1. COUPLER genere aussi les elements de
raccord entre GEO1 et GEO2.

Commentaire:

PO1 : Oeil pour definir la direction dans laquelle le fluide se
        trouve (type POINT)
CARCOQ : Caracteristiques de GEO1 (type MCHAML)
GEO2 : Maillage translate de GEO1 (type MAILLAGE)

En option :

GEO1 : Maillage de la coque. Necessaire seulement quand le maillage
        support de CARCOQ est different de GEO1 (type MAILLAGE)
N : Entier positif pour demander l'inversion de la frontiere fluide
        par rapport a la coque GE01 (type ENTIER)
RAC : Mot cle indiquant que l'on veut les elements raccord entre GEO1
        et GEO2 (type MOT)
GEO3 : Maillage contenant les elements raccord entre GEO1 et GEO2
        (type MAILLAGE)

## COUR [Maillage Lignes]
    Operateur COURBE
    ---------------- CUBT

    LIG1 = COURBE (N1) ('DINI' DENS1) ('DFIN' DENS2) ...
        ... ('PINI' OBJET1) ('PFIN' OBJET2) ...
        ... POIN0 POIN1 (POIN2 (POIN3 ...) ) ...
        ... ('PARAMETRE' FLOT1 FLOT2) ('REGULIER') ;

    Objet :

    L'operateur COURBE cree une courbe polynomiale dont les
points P verifient l'equation suivante :

        2 3
    P = POIN0 + U. POIN1 + U .POIN2 + U .POIN3 + ...

U etant un parametre reel.

    Commentaire :

    N1 : nombre (type ENTIER)
   'DINI' : Mot-cle (type MOT) suivi de :
    DENS1 : valeur de la densite (type FLOTTANT).

   'DFIN' : Mot-cle (type MOT) suivi de :
    DENS2 : valeur de la densite (type FLOTTANT).

 Pour plus de precisions, se reporter aux operateurs DROITE, CERCLE ...

'PINI' : Mot-cle (type MOT) suivi de :
 OBJET1 : Point initial de la courbe (type POINT), effectivement
        pris comme tel si ses coordonnees s'obtiennent
        pour la valeur U1 du parametre U.
        Le point final de cet objet OBJET1 (type MAILLAGE)
        (forcement une ligne) sera le point initial de la courbe
        polynomiale (avec les memes reserves que ci-dessus) et
        l'objet resultat LIG1 contiendra l'OBJET1 suivi de la
        courbe polynomiale.

'PFIN' : Mot-cle (type MOT) suivi de :
 OBJET2 : Point final de la courbe (type POINT), effectivement
        pris comme tel si ses coordonnees s'obtiennent pour
        la valeur U2 du parametre U.
        Le point initial de cet objet OBJET2 (forcement une
        ligne)(type MAILLAGE) sera le point final de la courbe
        polynomiale (avec les memes reserves que ci-dessus) e
        l'objet resultat LIG1 contiendra la courbe polynomial
        suivie d'OBJET2.

    POIN0, : Points de la representation polynomiale de la
    POIN1, courbe (type POINT).
    POIN2, ... Ces points ne font pas partie de la courbe.
        POIN0 et POIN1 sont obligatoires.

   'PARAMETRE' : Mot-cle (type MOT) suivi de :
    FLOT1, FLOT2 : Bornes du parametre U du polynome de la courbe
        (type FLOTTANT), egales a (0,1) par defaut.

   'REGULIER' : Mot-cle (type MOT) indiquant que la courbe devra
        etre subdivisee en elements dont les longueurs
        seront etablies selon l'abscisse curviligne
        et non pas selon le parametre U.

    LIG1 : Objet resultat (type MAILLAGE).

## COUR3D [Magnetostatique Magnetostatique] (proc)
 Procedure COUR3D

 CHP1 = COUR3D GEO1 GEO2 GEO3 MOT1 FLOT1 (LOG1 )

objet :

    calcul des courants dans un inducteur maille en 3D

Commentaire :

 GEO1 maillage de l'inducteur ( massif 3d)
 GEO2 maillage de la zone de sortie des courants
 GEO3 maillage de la zone d'entree des courants
 MOT1 mot 'AMP' ou 'AT'
 FLOT1 flottant densite de courant si mot1 = AMP
        amperes totaux si mot1 = AT
 LOG1 logiqe valant vrai si on rectifie la densite de
        courant dans les rayons de courbure

 en sortie :

 CHP1 chpoint des densites de courant sur GEO1 ( JX JY JZ )

## COURSPEC [Post-traitement Affichage] (proc)
Procedure COURSPEC
------------------ RESPOWNS

EVOL1_SP=COURSPEC LREEL1_SP FLOT1_DT;

objet:

mise en forme EVOL1_SP pour le trace d'un spectre de puissance
stationnaire associe a une decomposition en ondelettes. LREEL1_SP
indique la valeur du spectre dans les bandes (obtenu avec VALSPE
ou RESPOWNS) et FLOT1_DT le pas de temps de la modulation residu.

## COUT [Maillage Lignes]
 Operateur COUTURE

|  1ere possibilite  |

 SURF1 = COUT LIG1 LIG2 ;

 Objet :

 L'operateur COUTURE construit une surface qui relie deux lignes
 a l'aide de triangles.

 Commentaire :

 LIG1  | : lignes entre lesquelles la surface est generee
 LIG2  |  (type MAILLAGE)

 SURF1 : surface creee (type MAILLAGE)

 Remarque :

 Les deux lignes sont supposees decrites dans le meme sens.

|  2eme possibilite  |

 MAIL2 = COUT MAIL1 POIN1 ;

 Objet :

 L'operateur COUTURE cree un etoilement du maillage MAIL1 a partir
 du point POIN1.

 Commentaire :

 POIN1 : point (type POINT) a relier au maillage MAIL1
 MAIL1 : maillage (type MAILLAGE) constitué d'elements POI1,
        SEG2, TRI3 ou QUA4

 MAIL2 : maillage resultat (type MAILLAGE) constitué d'elements
        SEG2, TRI3, TET4 ou PYR5

 Remarque :

 POIN1 peut appartenir a MAIL1 auquel cas les elements de MAIL1
 touchant POIN1 ne sont pas etoiles.

## CREER_3D [Maillage Volumes] (proc)
    Procedure CREER_3D

    TAB1 = CREER_3D GEO1 OBJ1 MODL1 FLOT1 N1 N2 ;

    Objet :

    Cette procedure permet de construire un maillage et un champs
soit de deplacements, soit de contraintes, soit de deformations
ou soit de pression 3D a partir d'un maillage 2D (forme d'elements
SEG2, TRI3 ou QUA4 uniquement) et d'un champ respectivement de
deplacements, de contraintes, de deformations ou de pression
axisymetrique ou de Fourier. Il ne peut pas etre fournit de
maillage de fluide et de structure en meme temps. Le champ OBJ1
doit contenir toutes les composantes compatibles avec le mode de
caclcul.

Note : le MCHAML de sortie est appuye aux noeuds du maillage.
       le CHPOINT de sortie est de nature 'DIFFUS'
       dans le cas des MCHAML, on doit donner le modele et celui-ci
est affecte par la procedure. On ne peut donc pas lancer plusieurs
fois la procedure a la suite dans le but de recombiner les modes
fourier. Pour les CHPO, ces operations sont possibles. Donc il faut
passer du MCHAML au CHPO avant de lancer 'CREER_3D' dans le cas
des contraintes et des deformations quand on prevoit de recombiner
apres.
    Apes l'execution a la procedure l'option 'DIME' vaut 3 .

    Commentaire :

   GEO1 : maillage 2D (type MAILLAGE)
        (optionnel - donne uniquement si OBJ1 est un CHPOINT)

   OBJ1 est soit :

        - champs de deplacements ou de contraintes ou de deformations
        ou de pression issu d'un calcul axisymetrique ou de
        FOURIER (type CHPOINT)

        soit

        - champs de contraintes ou de deformations issu d'un calcul
        axisymetrique ou de FOURIER (type MCHAML)

   MODL1 : modele associe au champs par elements (type MMODEL)
        (optionnel - donne uniquement si OBJ1 est un MCHAML)

   FLOT1 : angle de rotation en degres pour la construction du
        maillage 3D (type FLOTTANT)

   N1 : nombre de decoupages de cet angle (type ENTIER)

   N2 : numero de l'harmonique (type ENTIER) ( si calcul axi 0)

   TAB1 : objet de type TABLE

        .'MAILLAGE' : objet de type MAILLAGE .

        .'DEPLACEMENT' : objet de type CHPOINT. Actuellement ce champ
        n'a comme composantes que 'UX', 'UY', 'UZ'.

        .'CONTRAINTE' : objet de type CHPOINT ou MCHAML. Ce champs a
        comme composantes 'N11' 'N22' 'N12' 'M11'
        'M22' 'M12' pour les elements coques et 'SMRR' 'SMTT'
        'SMZZ' 'SMRZ' 'SMRT' 'SMZT' pour les elements massifs.

        .'DEFORMATION' : objet de type CHPOINT ou MCHAML. ce champs a
        comme composantes 'EPSS' 'EPTT' 'GAST' 'RTSS' 'RTTT'
        'RTST' pour les elements coques et 'EPRR' 'EPZZ'
        'EPTT' 'GARZ' 'GART' 'GAZT' pour les elements massifs.

        .'FLUIDE' : objet de type CHPOINT. Ce champs a comme
        composantes 'P', 'PI', 'UZ'.

        .'MODELE' : objet de type MMODEL associe au maillage 3D.

## CRIT [Mecanique Resolution]
    Operateur CRIT

    CHEL1 = CRIT MODL1 SIG1 VAR1 CAR1 ;

    Objet :

    Etant donne un champ de contraintes, un champ de variables
internes, un materiau et eventuellement d'autres caracteristiques,
l'operateur CRIT calcule le critere de plasticite correspondant.

     Commentaire :

    MODL1 : objet modele (type MMODEL)

    SIG1 : champ de contraintes
        (type MCHAML, sous-type CONTRAINTES)

    VAR1 : champ de variables internes
        (type MCHAML, sous-type VARIABLES INTERNES)

    CAR1 : description du materiau et de caracteristiques geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

    CHEL1 : critere de plasticite calcule
        (type MCHAML, sous-type SCALAIRE)

    Remarque :

    Il convient de respecter l'ordre des donnees en entree .

## CRITLOC [Mecanique Rupture] (proc)
    Procedure CRITLOC

    TAB1 = CRITLOC TAB2 ;
        TAB2.'TNONL' .'OBJMO' .'RICE'
        .'RICE' .'EPSILON' .'SIGMA'
        .'ALPHA' .'BETA' .'EPSC'
        .'LAMBDA' .'SIG0' .'SIGC
        .'WEIBULL' .'V0' . 'M'
        .'TEMPER'. 'SIGU' 'TEREF'
        .'XMULT' .'IC' .'N'

    Objet :

    La procedure CRITLOC permet d'appliquer l'un ou l'autre des deux
criteres locaux suivants pour l'analyse de la rupture :

    - critere de Weibull pour la rupture par clivage
    - critere de Rice pour la rupture ductile

    Description des arguments d'entree et de sortie

    1)Dans le cas de l'utilisation des nouveaux objets MMODEL et MCHAML

    TAB2 (type table) :

      TAB2.'TNONL' : table resultat du calcul nonlineaire de
        la procedure PASAPAS
      TAB2.'OBJMO' : objet modele correspondant a la zone
        geometrique ou l'on veut appliquer le critere
        dans le cas du critere de Rice, objet modele
        total dans le cas du critere de Weibull

      Si le critere de Rice pour la rupture ductile est demande :

      TAB2.'RICE' : VRAI
      TAB2.'EPSILON' : VRAI si decohesion controlee par la deformation
      TAB2.'SIGMA' : VRAI si decohesion controlee par la contrainte

      Si TAB2.'EPSILON' est VRAI il faut fournir les donnees des para-
      metres du critere :

      TAB2.'ALPHA' : parametres du modele
      TAB2.'BETA'
      TAB2.'EPSC' : deformation necessaire a l'apparition des cavites

      Si TAB2.'SIGMA' est VRAI il faut fournir les parametres du critere

      TAB2.'ALPHA' : parametres du modele
      TAB2.'BETA'
      TAB2.'LAMBDA' : depend du rapport de forme de l'inclusion et du
        sens de prelevement
      TAB2.'SIG0' : limite elastique du materiau
      TAB2.'SIGC' : contrainte necessaire a l'apparition des cavites

      Si le critere de Weibull pour la rupture par clivage est demande :

      TAB2.'WEIBULL' : VRAI

      TAB2.'V0' : constante liee a la taille de la microstructure d
        materiau
      TAB2.'M' : parametre de Weibull
      TAB2.'TEMPER' : vaut 1 si la contrainte caracteristique de clivage
        (appelee aussi constante du materiau mesurant sa
        resistance au clivage) depend de la temperature
        et 0 dans dans le cas contraire
      TAB2.'SIGU' : objet de type evolution representant la variation
        de sigu en fonction de la temperature si temper = 1
        ou valeur de sigu de type constante si temper = 0
      TAB2.'XMULT' : intervient pour le calcul du volume plastifie
        et vaut : 1 si la structure complete est modelisee
        2 s'il y a une symetrie
      TAB2.'IC' : vaut 1 ou 0 suivant que l'on veut prendre en
        compte ou non l'effet de la deformation plastique
        sur le clivage

      Pour les cas PLAN il faut fournir en plus :
      TAB2.'EPAI' : epaisseur de la structure

      Si TAB2.'TEMPER' vaut 1 il faut fournir egalement :
      TAB2.'TEREF' : temperature de reference a laquelle on veut calculer
        la contrainte de Weibull (SIGW depend de SIGU(TEREF))

      Si TAB2.'IC' vaut 1 il faut fournir egalement :
      TAB2.'N' : vaut 2 ou 4 en general

    TAB1 (type table) :

    Si le critere de Rice pour la rupture ductile est demande :

      la procedure fournit les valeurs moyennees par element de:

      TAB1.'TAUX' : taux de croissance R/R0 (type MCHAML)
      TAB1.'RAPPORT' : taux de triaxialite Sm/Seq (type MCHAML)
      TAB1.'SIGEQ' : contrainte de Von Mises (type MCHAML)
      TAB1.'EPSEQ' : deformation plast. cumulee (type MCHAML)
        et (si option SIGMA)
      TAB1.'CONTDECO': contrainte locale (type MCHAML)
      TAB1.'CPRINMAX': contr. principale maximale (type MCHAML)

    Si le critere de Weibull pour la rupture par clivage est demande :

      TAB1.'SIGW' : contrainte de Weibull (type FLOTTANT)
        quand SIGU = evolution, SIGW depend de SIGU(TEREF)
      TAB1.'PROB' : probabilite de rupture (type FLOTTANT)
        quand SIGU = constante, PROBA = 1 - EXP ( - (SIGW/SIGU)**m
        quand SIGU = evolution, PROBA = 1 - EXP ( - (SIGW/SIGU(TER
      TAB1.'VPLAS' : volume plastique (type FLOTTANT)
      TAB1.'SIGPMAX' : contrainte principale maximale (type FLOTTANT)
      TAB1.'ELEMENT' : element associe a SIGPMAX (type MAILLAGE)
      TAB1.'EPSEQ' : deformation plast associee a SIGPMAX
        (type FLOTTANT)

    Remarque :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## CSON [Fluides Modele]
    Operateur CSON

       CHAM3 = 'CSON' MODL1 MATR1 ;

    Objet :

    L'operateur CSON permet de caracteriser la celerite des ondes
sonores dans un milieu continu mecanique a l'aide de la definition
du modele de comportement, des caracteristiques correspondantes.
La celerite est une fonction de l'espace.
Par exemple pour un modele elastique isotrope, la celerite en un
point M vaut

        c(M) = (E(M)/RHO(M)) ** 0.5

      Commentaire :

      MODL1 : objet modele ( type MMODEL ).

      MATR1 : objet de type MCHAML de sous-type CARACTERISTIQUES,
        decrivant les parametres du modele de comportement
        (obtenu avec l'operateur MATE).

      CHAM3 : objet resultat de type MCHAML defini au centre des
        de gravite des elements de composante 'CSON'.

## CTOD [Mecanique Rupture] (proc)
Procedure CTOD

CTOD DEP1 TAB1 ;

        TAB1.'FRTFISS'
        .'LIFIS1'
        .'MAILLAGE' .'PFS1'

Objet :

Cette procedure calcule l'ouverture en pointe d'une fissure
chargee en mode I definie , en plasticite etendue , comme
2 fois le deplacement de la levre de la fissure au point
d'intersection avec la droite a 45 degres .
La procedure est applicable aux cas bidimensionnels et tridimen-
sionnels.
En 3D , l'ouverture de fissure est determinee en chaque noeud
sommet du front de fissure , a partir de l'ouverture dans le plan
normal au front de fissure au noeud considere.
(le maillage doit etre elabore de maniere a prevoir l'existence
de ces plans normaux au front de fissure).

Commentaire :

En entree :

DEP1 : Champ de deplacements

TAB1 : Objet de type TABLE ,indice par des mots, servant a
        definir les options et les parametres du calcul :

  Arguments pour un probleme bidimensionnel

   indice type objet commentaires
        pointe

  FRTFISS POINT pointe de la fissure

  LIFIS1 MAILLAGE ligne decrivant la levre de la fissure

  Arguments pour un probleme tridimensionnel

   indice type objet commentaires
        pointe

  FRTFISS MAILLAGE ligne decrivant le front de fissure

  PSF1 POINT un point de la surface de fissure
        n'appartenant pas au front

  En sortie :

  En sortie, TAB1 permet de retrouver les valeurs de
  l'ouverture de fissure.

  indice type objet commentaires
        pointe

  CTOD FLOTTANT/TABLE en 2D ,flottant: valeur du CTOD
        en 3D ,table contenant les valeurs
        du CTOD en chaque noeud du front.

  Exemple : pour lister la valeur du CTOD calcule au noeud P15 du
        front de fissure ,il faudra coder : LIST (TAB1.CTOD.P15 )

## CUBP [Maillage Lignes]
    Operateur CUBP
    -------------- COUR

    LIG1 = CUBP (N1) POIN1 POIN2 POIN3 POIN4 ('UNIF') ('DINI' DENS1);

    Objet :

    L'operateur CUBP construit l'arc de cubique passant par les points
POIN1, POIN2, POIN3 et POIN4.

    Commentaire :

    POINi : points par lesquels passe l'arc de cubique (type POINT)

    DENS1 : densite associee au point POIN1 (type FLOTTANT)

    DENS2 : densite associee au point POIN4 (type FLOTTANT)

    N1 : nombre d'elements generes (type ENTIER)

    LIG1 : arc de cubique (type MAILLAGE)

    Remarque 1 :

    Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
    Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.
    Si N1 est negatif, N1 elements seront engendres et leur tailles
seront calculees en tenant compte des densites des extremites.

    Remarque 2 :

    Si les densites associees aux points POIN1 et POIN4 ne sont pas
correctes, il est possible de les surcharger. Pour le premier point, il
faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour le
dernier point, derriere le mot-cle 'DFIN'.

    Remarque 3 :

    Si on donne le mot-cle 'UNIF', la repartition des points sur l'arc
de cubique sera faite en fonction de l'abscisse curviligne, sinon elle
sera liee au parametrage issu de la position des points intermediaires.

## CUBT [Maillage Lignes]
    Operateur CUBT
    -------------- COUR

    LIG1 = CUBT (N1) POIN1 VECT1 VECT2 POIN2 ...
        ... ('DINI' DENS1) ('DFIN' DENS2) ;

    Objet :

    L'operateur CUBT construit un arc de cubique passant par deux points
POIN1 et POIN2; il est de plus tangent respectivement en POIN1 au
vecteur VECT1 et en POIN2 au vecteur VECT2.

    Commentaire :

    POINi : points par lesquels passe l'arc de cubique (type POINT)

    DENSi : densites associees aux points POINi (type FLOTTANT)

    VECTi : vecteurs definissant les tangentes aux points POINi
        (type POINT)

    N1 : nombre d'elements generes (type ENTIER)

    LIG1 : arc de cubique resultat (type MAILLAGE)

    Remarque 1 :

    Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
    Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.
    Si N1 est negatif, N1 elements seront engendres et leur tailles
seront calculees en tenant compte des densites des extremites.

    Remarque 2 :

    Si les densites associees aux points POIN1 et POIN2 ne sont pas
correctes, il est possible de les surcharger. Pour le premier point, il
faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour le
dernier point, derriere le mot-cle 'DFIN'.

## CVOL [Mathematiques Fonctions]
Operateur CVOL

LREEL1 = CVOL LREEL2 LREEL3 (('NPNE' ENTI1) MOT1) ;

objet :

Operateur CVOL effectue la convolution du signal LREEL2 avec la
reponse LREEL3. Le resultat LREEL1 comporte le meme nombre de points
que LREEL2 et est implicitement associe a la meme grille d'abscisse
uniforme de pas 1.

options :

- Le signal de reponse est considere par defaut comme symetrique et
  LREEL3 ne contient que les points d'abscisse positif. Si LREEL3
  contient tous les points, ENTI1 contient le nombre de points
  d'abscisse strictement negatif. Il est introduit par le mot clef
  'NPNE'.

- La convolution peut etre effectuee par symetrisation du signal ou
  par "zero padding". MOT1 permet de specifier 'SYME' ou 'PADD'.
  Le defaut est 'SYME'.

## DALL [Maillage Surfaces]
    Operateur DALLER
    ---------------- ROTA SURF GENE

    Objet :

    L'operateur DALLER construit une surface, soit a partir de la
donnee d'un contour , soit a partir d'une representation polynomiale.

    | 1ere possibilite |
    SURF1 = DALL | COTE1 COTE2 COTE3 COTE4 | 'PLAN' ;
        |  | 'SPHE' CENTR1 ;
        |  | 'CYLI' POIN1  POIN2 ;
        |  | 'CONI' POIN1  POIN2 ;
        |  | 'TORI' CENTR1 POIN1 CENTR1
        |  | 'QUELCONQUE' ;

    Commentaire :

    Suivant le mot-cle l'objet genere s'appuie :

        * sur une surface plane ('PLAN')

        * sur une surface spherique ('SPHE')
        de centre CENTR1 (type POINT)

        * sur une surface cylindrique ('CYLI')
        d'axe POIN1 POIN2 (type POINT)

        * sur une surface conique ('CONI')
        de sommet POIN1 et d'axe POIN1 POIN2 (type POINT)

        * sur une surface torique ('TORI')
        de centre CENTR1 (type POINT),
        d'axe de symetrie POIN1 POIN2 (type POINT)
        et avec CENTR2 (type POINT) le centre du petit cercle

        * sur une surface issue des cotes ('QUELCONQUE')

    COTEi : cotes definissant un contour (type MAILLAGE)
        il faut que ce contour ait un sens

    CENTRi : centres (type POINT)

    POINi : points definissant les axes (type POINT)

    SURF1 : objet resultat (type MAILLAGE)

    Remarque :

    Les elements construits seront orientes d'apres le sens de
description du contour.

    Les cotes opposes n'ont pas forcement le meme nombre de points.
Par contre le nombre total de points doit etre pair.

        3ETOC
        C|\  | | | | |  /|2
        O|-|-|-|-|-|-|-|-|E
        T| | | | | | | | |T
        E|-|-|-|-|-|-|-|-|O
        4| | | | | | | | |C
        COTE1

    | 2eme possibilite |
    SURF1 = DALL | POLYNOME N1 N2 P00  P01 (P02 (P03 ...) )
        |  P10  P11 (P12 (P13 ...) )
        |  (P20 (P21 (P22 (P23 ...) )
        |  (  ...  )
        |  ('PARAMETRE' U1 U2 V1 V2) ('REGULIER');

    Le resultat est le MAILLAGE de la surface parametree d'equation:

        | P00 P01 P02 P03 .. |  |  1  |
        2  (N2-1)  | P10 P11 P12 P13 .. |  |  U  |
    P(U,V) = (1 V V  ...V  ) x | P20 P21 P22 P23 .. | x |  ..  |
        |  ...  |  |U**(N1-1)|

    Commentaire :

    N1, N2 : nombre de colonnes et de lignes de la matrice de
        points (type ENTIER)

    P00, P01, ... : points utilises pour la definition parametrique de
        la surface (type POINT).

    U1 et U2, : bornes de variation du parametre U, egales a (0,1)
        par defaut (type FLOTTANT).

    V1 et V2, : bornes de variation du parametre V, egales a (0,1)
        par defaut (type FLOTTANT).

    'REGULIER' : mot-cle indiquant que les points de la surface
        doivent etre regulierement repartis dans l'espace
        geometrique (eu egard aux densites existantes)
        plutot que dans l'espace parametrique.

## DANS [Mathematiques Autres]
 Operateur DANS

 LOG1 = DANS  |  LECT1  LECT2  |
        |  LISTREE1  RE1  |
        |  POINT1  MELE1  |
        |  | ('SEQU' )| LISTREE1 LISTREE2  |
        |  |  'QUEL'  |  |

 Objet :

a) L'operateur DANS fabrique un logique LOG1 qui est VRAI si le LISTENTI
    LECT1 est inclus dans le LISTENTI LECT2 et FAUX sinon.

    Pour que LECT1 soit inclus dans LECT2, p etant la dimension de LECT1 et
    q celle de LECT2, il faut qu'il existe n tel que les 1 ... p valeurs de
    LECT1 soient respectivement egales aux n*p+1 ... (n+1)*p valeurs de LECT2

b) L'operateur DANS fabrique un logique qui est VRAI si le reel RE1 est dans
    le listreel LISTREE1. La precision est calculee en fonction (*1.e-8)dut
    plus petit ecart entre deux valeurs consecutives du listreel.

c) L'operateur DANS fabrique un logique qui est VRAI si le point POINT1
     fait partie des noeuds du maillage MELE1.

d) - mot SEQU : L'operateur DANS fabrique un logique qui est vrai si
        la sequence du listree1 se retrouve dans le listreel2

e) - mot QUEL : L'operateur DANS fabrique un logique qui est vrai si tous
        les element du listreel1 existent dans le listreel2

## DARCYSAT [Fluides Resolution] (proc)
    Procedure DARCYSAT
    ------------------
    DARCYSAT TAB1 ;

    TAB1.'SOUSTYPE'.'MODELE'
        .'LOI_PERMEABILITE'.'LOI_SATURATION'.'HOMOGENEISATION'
        .'COEFEMMA'.'BLOCAGES_DARCY'.'CHARGEMENT'.'FORCE_GRAVITE'
        .'CONVERSION_CHARGE'.'TEMPS'.'TRACE_CHARGE'.'CHARGE'.('FLUX')
        .'TEMPS_CALCULES'.'TEMPS_SAUVES'.'TEMPS_FINAL'
        .'DT_INITIAL'.'NPAS'.'CFL'
        .'NITER'.'ITMAX'.'RESIDU_MAX'.'SOUS_RELAXATION'.'XI'
        .'DIVISION_DT'.'COFDIV'.'NMAXDT'.'MESSAGE'

   Objet :

   Cette procedure permet de simuler un transitoire d'ecoulement
   en zones saturee et non saturee d'un milieu poreux. L'ecoulement
   est decrit en zone saturee par l'equation de Darcy et en zone non
   saturee par l'equation de Richard's (ecrite ici avec h en metres)

   zone saturee (Pw - Pg > 0)

     Se dh/dt = -div(U) ; U = -Ks grad(h) ;
     h = (Pw-Pg)/rho*g + z (m) ou h = (Pw-Pg) + rho*g*z (Pa)
     avec, Se, coefficient d'emmagasinement (1/m),
        Ks, permeabilite a saturation (m/s),
        Pw, pression d'eau (Pa),
        Pg, pression de gaz (Pa),
        h, charge (m) et
        U, vitesse de Darcy (m/s).

   zone non saturee (Pw - Pg < 0)

     C(P) dh/dt = -div(U) ; U = -K(P) (grad h)

     avec, C(P) capacite capillaire (1/m)
        K(P), permeabilite (m/s)

   La resolution est effectuee en trace de charge par la methode EFMH.
   La teneur en eau se deduit de la pression par la procedure HT_PRO.
   La permeabilite se deduit de la saturation par la procedure KR_PRO.
   La capacite capillaire est deduite de la teneur en eau et de la
   pression.

   Le probleme etant non lineaire, des mecanismes automatiques ou non
   ont ete mis en place pour fiabiliser la convergence du systeme :
   relaxation de la capacite et de la conductivite hydraulique et
   homogeneisation des caracteristiques decentree sur les elements,
   changement automatique de pas de temps ou penalisation sur le
   terme transitoire.

   Commentaire :

   En entree, TAB1 sert a definir les options et les parametres du
   calcul. Les indices de la table TAB1 sont des mots (a coder tels
   quels) dont voici la description :

   |  |
   | Indice  Definition  |
   |  |
   |  |
   |-------------------------------------------------  |
   | Donnees physiques, geometriques et materielles :  |
   |-------------------------------------------------  |
   |  |
   |'SOUSTYPE'  'DARCY_TRANSATUR'  (type MOT)  |
   |  |
   |'MODELE'  Objet modele (MMODEL cree par MODE)  |
   |  |
   |'LOI_PERMEABILITE'  Objet table contenant les valeurs des  |
   |  parametres de la loi de permeabilite calculee par la|
   |  procedure KR_PRO.  |
   |  3 indices 'SOUSTYPE' possibles :  |
   |  |
   |  - soustypes au choix  |
   |  'PUISSANCE', 'MUALEM', 'BURDINE', 'MUALEM_BURDINE' |
   |  'BROOKS_COREY', 'EXPONENTIELLE', 'LOGARITHMIQUE'  |
   |  : la table doit contenir les  |
   |  indices designant les parametres utilises dans la  |
   |  procedure standard KR_PRO.  |
   |  |
   |  - soustype 'PERSONNELLE' : la table doit contenir  |
   |  les indices de la loi construite par l'utilisateur  |
   |  dans sa propre procedure KR_PRO, ou dans une autre  |
   |  dont le nom est stipule au sous-indice  |
   |  'NOM_PROCEDURE'.  |
   |  |
   |  - soustype 'MULTIZONE' : les indices doivent  |
   |  designer les differentes zones, les valeurs de ces  |
   |  indices etant alors des tables de soustype  |
   |  'PUISSANCE', 'MUALEM', 'BURDINE', 'MUALEM_BURDINE'  |
   |  'BROOKS_COREY', 'EXPONENTIELLE', 'LOGARITHMIQUE'  |
   |  documentees dans la notice de KR_PRO  |
   |  ou'PERSONNELLE' dont les indices  |
   |  designent les parametres des lois affectees a chaque|
   |  zone. Ces sous-tables doivent aussi contenir le  |
   |  modele de la zone a l'indice 'MODELE', ces sous-  |
   |  modeles constituant une partition du domaine general|
   |  |
   |  pour les autres sous-indices (defaut), voir KR_PRO  |
   |  |
   |'LOI_SATURATION' Objet table contenant les valeurs des  |
   |  parametres de la loi analytique de teneur en eau  |
   |  calculee par la procedure  HT_PRO.  |
   |  3 indices 'SOUSTYPE' possibles :  |
   |  |
   |  - soustypes aux choix 'VAN_GENUCHTEN',  |
   |  'EXPONENTIELLE', 'LOGARITHMIQUE'  |
   |  : la table doit contenir les  |
   |  indices designant les parametres utilises dans la  |
   |  procedure standard HT_PRO.  |
   |  |
   |  - soustype 'PERSONNELLE' : la table doit contenir  |
   |  les indices de la loi construite par l'utilisateur  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DARCYTRA [Fluides Resolution] (proc)
    Procedure DARCYTRA
    ------------------ DARCYSAT

    DARCYTRA TAB1 ;

        TAB1.'SOUSTYPE'.'MODELE'.'DOMAINE'.
        'CARACTERISTIQUES'.'EMMAGASINEMENT'.'CONVECTION'.
        'TEMPS'.'TRACE_CHARGE'.'CHARGE'.'FLUX'.
        'BLOCAGE'.'TRACE_IMPOSE'.'FLUX_IMPOSE'.'SOURCE'.
        'TEMPS_CALCULES'.'TEMPS_SAUVES'.
        'THETA'.'THETA_CONVECTION'

        ou TAB1.'SOUSTYPE'.'MODELE'.'DOMAINE'.'ORIENTATION'.
        'CARACTERISTIQUES'.'POROSITE'.'DECROISSANCE'.
        'COEF_RETARD'.'LANGMUIR'.'FREUNDLICH'.
        'LIMITE_SOLUBILITE'.'COEF_DISSOLUTION'.
        'CONVECTION'.'TEMPS'.'TRACE_CONC'.'CONCENTRATION'.
        'FLUX'.'PRECIPITE'.'DISSOLUTION'.
        'BLOCAGE'.'TRACE_IMPOSE'.'FLUX_IMPOSE'.
        'DISSOLUTION_IMPOSEE'.'SOURCE'.'TEMPS_CALCULES'.
        'TEMPS_SAUVES'.'THETA_DIFF'.'THETA_CONVECTION'.
        'THETA_DEC'.'THETA_DISS'.'PENALISATION'.
        'EPSI_LIM'.'ITMAX_LIM'.'EPSI_RET'.'EPSI_COR'.
        'ITMAX_RET'

    Objet :

    Cette procedure a deux fonctions.

 1) En presence de l'indice 'CHARGE', on resoud les equations
de DARCY en transitoire pour l'ecoulement par une methode d'elements
finis mixtes hybrides (EFMH).
    Les inconnues du probleme sont la charge ('H'),
la trace de charge ('TH') et le flux diffusif ('FLUX').

 2) En l'absence de l'indice 'CHARGE', resoud l'equation
de transport par diffusion-convection d'un champ scalaire actif
par un fluide dont la vitesse est connue. L'espece peut se trouver
sous trois formes : solute, adsorbat et precipite, dont les lois
d'echange doivent etre specifiees. A chaque loi correspondent un ou
plusieurs algorithmes auxquels des parametres numeriques doivent etre
fournis. On utilise la modelisation Darcy EFMH.
    Les inconnues du probleme sont la concentration ('H'),
la trace de concentration ('TH') et le flux diffusif ('FLUX').

    Commentaire :

    En entree, TAB1 sert a definir les options et les parametres du
calcul. Les indices de la table TAB1 sont des mots (a coder tel quel)
dont voici la description :

  |  |
  | Indice  Contenu  |
  |  |
  |  |
  |------------------------------------------------  |
  |Donnees physiques, geometriques et materielles :  |
  |------------------------------------------------  |
  |  |
  |  ------ Indices communs a l'ecoulement et au transport ------  |
  |  ------------------------------------------------------------  |
  |  |
  |'SOUSTYPE'  'DARCY' (type MOT)  |
  |  |
  |'MODELE'  Objet modele (MMODEL cree par MODE)  |
  |  |
  |'DOMAINE'  References geometriques (TABLE creee par DOMA)  |
  |  |
  |  ------ 1ere possibilite : Resolution de l'ecoulement ------  |
  |  -----------------------------------------------------------  |
  |  |
  |'CARACTERISTIQUES' Donnees physiques et materielles :  |
  |  conductivite hydraulique (CHAMELEM cree par MATE)  |
  |  |
  |'EMMAGASINEMENT' Valeur du coefficient d'emmagasinement  |
  |  (Type CHPO Centre, Comp 'CK', ou FLOTTANT)  |
  |  - Defaut 1.  |
  |  |
  |  ------ 2eme possibilite : Resolution du transport  ------  |
  |  ------------------------------------------------------------  |
  |  |
  |'CARACTERISTIQUES' Donnees physiques et materielles :  |
  |  diffusivite effective (CHAMELEM cree par MATE)  |
  |  |
  |'POROSITE'  Valeur de la porosite (Type CHPO Centre, Comp  |
  |  'CK', ou FLOTTANT) - Defaut 1.  |
  |  |
  |'DECROISSANCE' Valeur du terme de decroissance (Type FLOTTANT)  |
  |  Tel que dC/dt = - Lambda * C  - Defaut 0.  |
  |  |
  |'COEF_RETARD' Coefficient de retard lineaire dans le cas simple, |
  |  ou  Pente a l'origine de la fonction F(C) dans le  |
  |  cas d'isotherme non lineaire de Langmuir  |
  |  ou  Coefficient K de l'isotherme de Freundlich  |
  |  (Type CHPO Centre 'SCAL', ou FLOTTANT)  |
  |  |
  |'LANGMUIR'  Quantite maximale adsorbee sur le solide  |
  |  rapportee a l'unite de volume du fluide et exprimee|
  |  dans la meme unite que le solute.  |
  |  (Type CHPO Centre 'SCAL', ou FLOTTANT).  |
  |  F = (R-1) C / [1 + ((R-1) C / Fsat)]  |
  |  Si cet indice et le suivant sont absents,  |
  |  l'equilibre d'adsorption est lineaire. Cet indice a|
  |  priorite sur l'indice FREUNDLICH.  |
  |  |
  |'FREUNDLICH'  Exposant de la loi de Freundlich F = K (C ^ 1/n)  |
  |  (Type FLOTTANT).  |
  |  Dans ce cas (et si l'indice LANGMUIR n'existe pas),|
  |  l'indice 'RETARD' contient le coefficient  |
  |  K ramene a une unite de volume de fluide.  |
  |  - Non disponible pour l'instant -  |
  |  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DATE [Langage Base]
    Operateur DATE

    VAL1 = DATE ('LETTRE') | 'CONVERSION' | ;
        | 'EPOCH'  |
        | 'ANNEE'  |
        | 'MOIS'  |
        | 'JOUR'  |
        | 'HEURE'  |
        | 'MINUTE'  |
        | 'SECONDE'  |

CHAP{1ère fonction : Récupération de la date}

        Syntaxe :
    VAL1 = DATE ('LETTRE') ( | 'ANNEE'  | ) ;
        | 'MOIS'  |
        | 'JOUR'  |
        | 'HEURE'  |
        | 'MINUTE'  |
        | 'SECONDE' |

        Arguments et résultats :
    VAL1 : chaine de caractères ou flottant

        Description :
    L'opérateur DATE sert à récupérer la date et l'heure actuelle. Si aucune
    option n'est précisée, VAL1 est une chaine de caractère contenant la date
    complète. Si une option est précisée, seule la partie concernée de la date
    est renvoyée sous forme d'entier. On peut donc récupérer, par exemple,
    uniquement l'heure actuelle dans un entier en appelant
    VAL1 = 'DATE' 'HEURE;

    L'option 'LETTRE' permet d'obtenir le nom du mois au lieu de son numéro.
    (L'appel 'DATE' 'MOIS' 'LETTRE' renvoie alors une chaine de caractère.)

        Exemples :

    'LIST' ('DATE' 'LETTRE');
    Chaine de 32 caractères de contenu : 11 mai 2015 - 17H52min
    'LIST' ('DATE');
    Chaine de 32 caractères de contenu : 11/05/2015 - 17:52:38

CHAP{2ème fonction : Récupération du temps écoulé}

        Syntaxe :
    VAL1 = DATE 'EPOCH' ;

        Arguments et résultats :
    VAL1 : flottant

        Description :
    L'opérateur DATE renvoie le nombre de secondes depuis un temps non-défini
    mais fixe lors d'une exécution. Cette valeur permet, par différence, de
    mesurer un temps entre deux appels "'DATE' 'EPOCH'" ou d'initialiser des
    séries par un nombre différent à chaque exécution.

        Exemple :
    tdeb = 'DATE' 'EPOCH';
    ..... Opérations à chronométrer .....
    tfin = 'DATE' 'EPOCH';
    'MESS' ('CHAI' 'Temps ecoule : ' (tfin - tdeb));

CHAP{3ème fonction : Conversion d'un nombre de secondes}

        Syntaxe :
    VAL1 = DATE 'CONVERSION' VAL2;

        Arguments et résultats :
    VAL1 : chaine de caractere
    VAL2 : flottant

        Description :
    L'opérateur DATE convertit le nombre VAL2 de secondes en nombres de jours /
    heures / minutes / secondes. Le résultat est renvoyé sous forme de chaine de
    caractères dans VAL1.

        Exemples :
    'LIST' ('DATE' 'CONVERSION' 3600.0);
    Chaine de 32 caractères de contenu : 0J 01H 00min 0.000sec

    'LIST' ('DATE' 'CONVERSION' 123456.789);
    Chaine de 32 caractères de contenu : 1J 10H 17min 36.789sec

## DBIT [Fluides Resolution]
   Operateur DBIT

   Q = DBIT MODE1 U <'IMPR'>;

   Q1 Q2 = DBIT MODE1 U 'ALGE' <'IMPR'>;

   Objet :

 Calcule le flux d'un vecteur a travers une ligne en 2D ou une surface
en 3D
 Le resultat est un FLOTTANT, somme des flux (debit global).
 Si le mot cle 'ALGE' est precise, le flux dans le sens de la normale
 est distingue du flux dans le sens oppose (Q1 et Q2).

 La surface ou la ligne peut etre fermee ou non.
 Types d'elements : en 2D : SEG2 ou SEG3.
        en 3D : TRI3, QUA4, TRI7 ou QUA9
 En 2D axisymetrique la surface consideree est celle engendree par la
 rotation de 2pi radians de la ligne.
 La normale utilisee pour le calcul est celle definie implicitement
 par l'orientation des elements de l'objet maillage qui represente
 la frontiere (convention trigonometrique).
 Il est donc imperatif de veiller a la bonne oriention de ces
 elements lors de la creation du maillage.

   Commentaires :

  MODE1 : Objet modele (type MMODEL) 'NAVIER_STOKES'
  U : CHPOINT (VECT SOMMET) dont on calcule le debit.
  Q : FLOTTANT resultat.

   Remarque :

L'operateur imprime le debit global dans le sens de la normale ainsi
que le debit global dans le sens oppose si presence du mot cle 'IMPR'

## DCOV [Mathematiques Autres]
Operateur DCOV

   RIG1 = DCOV GEO1 | 'EXPO'  'SIGMA' FLOT1  ...
        | 'GAUS'

  ...  | 'LAMBDA'  FLOT2  ;
       | 'LAMBDA1' FLOT3 'LAMBDA2' FLOT4 ('LAMBDA3' FLOT5 si 3D)
        ('DIRECTION' VEC1 (VEC2 si 3D)) ;

   Objet :

   C etant une matrice de covariance, matrice symetrique definie
   positive, s'appuyant sur les points d'un maillage,
   l'operateur DCOV calcule la matrice M triangulaire
   inferieure, telle que M Mt = C. (M objet de type RIGIDITE)
   Cette matrice M servira par la suite a generer un champ
   aleatoire gaussien stationnaire F, tel que F = M G, ou G est
   un bruit blanc genere a l'aide de l'operateur BRUI. (F et G
   objets de type CHPO).
   F aura les caracteristiques suivantes :
        - moyenne nulle
        - matrice de covariance egale a C

   Commentaire :

   GEO1 geometrie sur les points de laquelle est definie la
        matrice de covariance C . (type MAILLAGE)

   FLOT1 ecart-type (type FLOTTANT). Cette valeur doit etre
        strictement positive.

   FLOT2 longueur de correlation dans le cas d'une covariance
        isotrope. (type FLOTTANT)
        Cette valeur doit etre strictement positive.

   FLOT3, FLOT4 et FLOT5 (si 3D) longueurs de correlation suivant
        les axes d'anisotropie, dans le cas d'une covariance
        anisotrope. (types FLOTTANT)
        Ces valeurs doivent etre strictement positives.

   VEC1 et VEC2 (si 3D) vecteur(s) permettant de definir le repere
        lie aux directions d'anisotropie, dans le cas d'une
        covariance anisotrope. (types POINT)

   Construction du repere orthonorme direct lie aux directions
   d'anisotropie :
    Dans le cas bidimensionnel, la definition d'un seul vecteur
   (VEC1) - correspondant a LAMBDA1 - est suffisante. Le deuxieme
   axe - correspondant a LAMBDA2 - est porte par le vecteur qui
   fait un angle de + 90 degres avec le vecteur VEC1.
    Dans le cas tridimensionnel, on construit un triedre a partir
   des deux vecteurs VEC1 et VEC2 fournis par l'utilisateur.
    Le premier axe correspond a VEC1, le second a VEC2.
    Le troisieme axe, correspondant a LAMBDA3, est porte par le
   vecteur obtenu par le produit vectoriel de VEC1 par VEC2.

   Dij etant la distance entre deux points Pi et Pj,
   D1ij, D2ij et D3ij (si 3D), etant les composantes de Dij
   suivant les axes d'anisotropie 1,2 et 3 (si 3D);

   selon la loi suivie, le terme Cij de la matrice sera :

    loi exponentielle (mot-cle 'EXPO') :

     en isotrope :
       Cij = FLOT1 * FLOT1 * EXP ( - Dij / FLOT2 )

     en anisotrope 2D :
       Cij = FLOT1 * FLOT1 * EXP ( -
        ( (D1ij / FLOT3) ** 2 + (D2ij / FLOT4) ** 2 ) ** 0.5 )

     en anisotrope 3D :
       Cij = FLOT1 * FLOT1 * EXP ( - ( (D1ij / FLOT3) ** 2 +
        (D2ij / FLOT4) ** 2 + (D3ij / FLOT5) ** 2 ) ** 0.5 )

    loi gaussienne (mot-cle 'GAUS') :

     en isotrope :
       Cij = FLOT1 * FLOT1 * EXP ( - Dij ** 2 / FLOT2 )

     en anisotrope 2D :
       Cij = FLOT1 * FLOT1 * EXP ( -
        ( (D1ij / FLOT3) ** 2 + (D2ij / FLOT4) ** 2 ) )

     en anisotrope 3D :
       Cij = FLOT1 * FLOT1 * EXP ( - ( (D1ij / FLOT3) ** 2 +
        (D2ij / FLOT4) ** 2 + (D3ij / FLOT5) ** 2 ) )

   RIG1 objet de type RIGIDITE defini sur un superelement
        correspondant aux points du maillage GEO1. La matrice est
        dimensionnee au carre du nombre de points du maillage
        GEO1. La partie triangulaire superieure ne contient que
        des 0.

   Remarque 1 :

   En dimension 1, seul le cas d'une covariance isotrope est
   autorise.

   Remarque 2 :

   Le maillage GEO1 peut etre une geometrie quelconque 2D ou 3D.
   Neanmoins, sa taille devra etre relativement limitee.

   Remarque 3 :

   Dans le cas d'une covariance anisotrope, les directions
   d'anisotropie sont orthogonales entre elles.
   En 3D notamment, les vecteurs VEC1 et VEC2 devront etre
   orthogonaux.

   Remarque 4 :

   La generation de cette matrice M est principalement destinee
   a la mise en oeuvre de simulations Monte-Carlo.

## DDFOUR [Magnetostatique Magnetostatique] (proc)
Procedure DDFOUR

CHP2 CHP3 = DDFOUR GEO1 GEO2 ENT1 CHP1 FLOT1 (P1) (LOG1 ENT2)

Objet :

 Analyse harmonique des multipoles en magnetostatique 2D
 potentiel vecteur.

Commentaire :

GEO1 maillage support de la solution en potentiel
GEO2 maillage ( arc sur lequel on fait l'analyse )
ENT1 nombre d'harmonique analysees
CHP1 solution en potentiel
FLOT1 rayon de normalisation
P1 origine du cercle d'analyse
LOG1 vrai si l'on veut un lissage polynomial
       ( voir PROI POLY)
ENT2 ordre de symetrie pour l'expansion polynomiale
       si LOG1 = vrai

en sortie :

CHP2 CHP3 chpoints utilises pour l'analyse d'homogeneite

## DEADFONC [Mathematiques Autres] (proc)
Procedure DEADFONC

Objet :

"DEdu ADap Fonctionnelle"

Calcule la valeur (par elements ou global) de la fonctionnelle
a minimiser.

Utilise par la procedure DEDUADAP.

## DEADJACO [Mathematiques Autres] (proc)
Procedure DEADJACO

Objet :

"DEdu ADap Jacobien"

Calcule un Jacobien signe ou renvoie un code d'erreur si le
signe change sur un element.

Utilise par la procedure DEDUADAP.

## DEADKTAN [Mathematiques Autres] (proc)
Procedure DEADKTAN

Objet :

"DEdu ADap K-Tangente"

Calcule la matrice tangente (exacte ou approchee) associee a la
fonctionnelle a minimiser.

Utilise par la procedure DEDUADAP.

## DEADRESI [Mathematiques Autres] (proc)
Procedure DEADRESI

Objet :

"DEdu ADap RESIdu"

Calcule le residu a annuler.

Utilise par la procedure DEDUADAP.

## DEADUTIL [Maillage Autres] (proc)
Procedure DEADUTIL

Objet :

"DEdu ADap UTILitaires"

Des utililitaires utilises par la procedure DEDUADAP.

## DEBI [Multi-physique Multi-physique]
    Operateur DEBIT

      CHPO2 = DEBIT  MODL1 | FLOT1 GEO1 |  ( MOT1) ;
        | CHPO1  |

    Objet :

    Cet operateur permet de calculer les valeurs nodales equivalentes
a une condition de debit (lineique en 2D ou surfacique en 3D)
imposee sur la frontiere d'un milieu poreux.

      Commentaire :

        MODL1 : objet massif, sur la frontiere duquel s'applique
        une condition de debit (type MMODEL).

        FLOT1 : valeur algebrique du debit impose (type FLOTTANT).

        GEO1 : objet (ligne en 2D ,surface en 3D), sur lequel
        s'applique la condition de debit (type MAILLAGE).

        CHPO1 : les valeurs algebriques des debits aux noeuds
        (type CHPOINT).

        MOT1 : nom donn au resultat (par defaut, pris dans le modele)

        CHPO2 : valeurs nodales equivalentes (type CHPOINT)

## DEBM [Langage Methodes]
    Operateur DEBMETH
    ----------------- RESP QUIT

    DEBMETH METH1 (OBJ1?TYP1 OBJ2?TYP2 .... ) ;

    Objet :
    Il s'agit de definir une methode qui pourra etre appliquee sur
un objet de type OBJET.

    L'operateur DEBMETH cree un objet de type PROCEDUR qui contient
une suite d'instructions elementaires, dont la premiere est DEBMETH
et la derniere est FINMETH.

    Commentaire :

  Cette operateur est strictement copie sur l'operateur DEBPROC. c'est
seulement a l'executuion de la procedure resultante que le comportement
differe. Une procedure definie ainsi ne peut servir que comme une
methode sur un objet de type OBJET.

## DEBP [Langage Methodes]
    Operateur DEBPROC
    ----------------- RESP QUIT

    DEBPROC PROC1 (OBJ1?TYP1 OBJ2?TYP2 .... ) ;

    Objet :

    L'operateur DEBPROC cree un objet de type PROCEDUR qui contient une
suite d'instructions elementaires, dont la premiere est DEBPROC et la
derniere est FINPROC.

    Commentaire :

    La procedure peut avoir une liste d'arguments types (OBJ1,OBJ2,...).
? peut prendre deux valeurs :

        * qui rend la donnee de l'argument obligatoire au
        moment de l'appel de la procedure,

        / qui la rend facultative.

Les types d'objet possibles sont:

   'MAILLAGE' 'AFFECTE ' 'DEFORME '
   'CHPOINT ' 'CHAMELEM' 'LISTREEL'
   'RIGIDITE' 'BLOQSTRU' 'LISTENTI'
   'ELEMSTRU' 'SOLUTION' 'CHARGEME'
   'STRUCTUR' 'TABLE ' 'MODELE '
   'MAFFEC ' 'MSOSTU ' 'EVOLUTIO'
   'IMATRI ' 'MJONCT ' 'SUPERELE'
   'ATTACHE ' 'MMATRI ' 'LOGIQUE '
   'FLOTTANT' 'ENTIER ' 'MOT '
   'TEXTE ' 'LISTMOTS' 'VECTEUR '
   'VECTDOUB' 'POINT ' 'CONFIGUR'
   'LISTCHPO' 'BASEMODA' 'PROCEDUR'
   'BLOC ' 'MMODEL ' 'MCHAML '
   'MINTE ' 'NUAGE ' 'MATRIK '
   'LISTOBJE'

    Il faut bien noter qu'en presence de plusieurs arguments
de Meme type seul l'ordre permet de les differencier.

    L'ensemble ?TYPi est facultatif. S'il est omis, DEBP essaie de
recuperer un objet de n'importe quel type. Les objets de type
inconnu doivent etre place a la fin de la liste des arguments
a lire.

    Remarques :

    Une procedure a acces a tous les objets existants avant son
 appel mais ne peut pas les modifier. Tout objet dont le nom
 commence par ! ne sera pas initialise par un objet de meme nom
 defini en dehors de la procedure.

    Les objets crees lors de l'execution d'une procedure ne sont pas
accessibles a l'exterieur de la procedure.

    Exemple de procedure de calcul de la fonction MODULO :

        DEBPROC MODULO I*ENTIER J*ENTIER ;
        MODERR='$$$$$';
        SI (J EGA 0) :
        MESSAGE ' ON NE PEUT FAIRE I MODULO ZERO ';
        RESPRO MODERR;
        QUITTER MODULO ; FINSI;
        K*ENTIER = I / J ;
        MOD = I - ( K * J ) ;
        FINPROC MOD;

    Exemple d'emploi de la procedure MODULO :

        K = 8 MODULO 3 ;
        SI ( K NEG 2 ) ;
        MESSAGE ' ERREUR DANS LA RECOPIE DE L EXEMPLE |' ;
        FINSI;

## DEBU [Presentation Presentation]
 Pour avoir des informations generales sur GIBI tapez INFO GIBI;

 Pour avoir des informations particulieres sur un operateur tapez
   INFO (nom de l'operateur) ;

 Pour avoir un exemple d'utilisation tapez INFO EXEMPLE;

 La liste des operateurs documentes est :

| Operateurs generaux :  |
| OPTI  FIN  TITR  COMM  OUBL  MANU  DENS  TASS  |
| Entrees-sorties :  |
| LIST  TRAC  SORT  LIRE  |
| Mise au point interactive de maillage :  |
| MODI  |
| Fabrication de logiques :  |
| <  >  <EG  >EG  EG  NEG  ET  OU  NON  |
| Fabrication de mots :  |
| MOT  |
| Fabrication de nombres :  |
| DENS  NBEL  NBNO  COOR  NORM  +  -  *  /  **  |
| EXP  LOG  ENTI  FLOT  PSCA  PMIX  SIN  COS  ATG  ABS  |
| Fabrication de points :  |
| DIGI  NOEU  POIN  CONF  BARY PVEC  *  /  |
| Fabrication de lignes :  |
| DROI  CERC  PARA  INTE  COTE  CONT  COMP  QUEL  CER3  CUBP  CUBT  |
| Fabrication de surfaces :  |
| SURF  DALL  TRAN  ROTA  INCL  ORIE  RACC  FACE  LIAI  REGL  COUT  |
| ENVE  GENE  REGE  |
| Fabrication de volumes :  |
| PAVE  VOLU  REGE  |
| Operations geometriques :  |
| ET  CHAN  INVE  PLUS  MOIN  HOMO  TOUR  AFFI  SYME  ELIM  DIFF  |
| DEPL  PROJ  ELEM  ORIE  VERS  INTE  |
| Calcul vectoriel :  |
| PLUS  MOIN  *  /  PSCA  PVEC  PMIX  |
| Test  boucle procedure et dialogue :  |
| SI  SINO  FINS  REPE  QUIT  FIN  DEBP  FINP  OBTE  MESS  TEXT  |
| Gestion des couleurs :  |
| COUL  |

## DECO [Magnetostatique Magnetostatique]
Operateur DECO

  DECO1 = DECO MODL1 FC1 (CAR1) ;

Objet :

L'operateur DECO calcule la densite de courant correspondant
a la fonction de courant (type CHPOINT) obtenue lors de la
resolution en formulation magnetodynamique. Pour des modeles
de coques, elle est fournie en A/m.

  Commentaire :

  MODL1 : Objet de type MMODEL (MAGNETODYNAMIQUE).

  FC1 : Fonction de courant (type CHPOINT).

  CAR1 : Champ de caracteristiques geometriques (type MCHAML).

  DECO1 : Densite de courant (type MCHAML).

## DECONV [Mecanique Dynamique] (proc)
    procedure DECONV

   TABRESU = DECONV COUCHE FOND_SOL MOD_SOL (SOL) DIR
        GAMMAO F1 F2 (FC) (TYP_F) (P_GAMMA)

Objet :

Cette procedure permet d'effectuer des calculs d'interaction sol-
structure (ISS) en 2D (deformation plane ou mode Fourier 0 (mouvement
vertical) et 1 (mouvement horizontal)) par la methode des elements
finis. Elle a deux fonctions:
  - formuler la matrice d'amortissement correspondant a la frontiere
    absorbante visqueuse sur la bordure du maillage de sol,
  - calculer le chargement sismique au cours du temps a appliquer sur
    la frontiere par la deconvolution du mouvement sismique
    (accelerogramme) donnee en surface libre du sol.
La resolution du probleme peut s'effectuer ensuite dans le domaine
temporel avec l'une des procedures d'integration suivantes :
  - procedure DYNAMIC en cas de comportement lineaire, possibilite
    d'inclure des liaisons unilaterales pour modeliser le decollement
    et le glissement du radier,
  - procedure PASAPAS en cas de comportement non lineaire du sol et de
    la structure (deformation plane seulement).

Commentaire :

En entree :

COUCHE : TABLE, a double indice contenant les proprietes du sol :

  COUCHE.I : SOUS-TABLE, relative a la ieme couche du sol et qui
        contient les indices suivants en toute lettre

  indice 'FRONTIERE' : MAILLAGE, frontiere verticale de la
        ieme couche
  indice 'MASSE_VOLUMIQUE' : FLOTTANT, masse volumique
  indice 'POISSON' : FLOTTANT, coefficient de Poisson
  indice 'YOUNG' : FLOTTANT, module d'Young
  indice 'AMORTISSEMENT : FLOTTANT, amortissement reduit

FOND_SOL : MAILLAGE, frontiere horizontale inferieure du sol
MOD_SOL : MMODEL, modele du sol
SOL : MAILLAGE, maillage du sol (QUA8 ou TRI6), facultatif
DIR : MOT, direction de l'acceleration du champ libre :
        'HORI' direction horizontale (onde SV)
        'VERT' direction verticale (onde P)
GAMMAO : EVOLUTION, acceleration du champ libre en surface. Le
        debut de cet accelerogramme doit comprendre
        un intervalle a acceleration nulle (100 points
        minimum). C'est le temps qui permet au front
        d'onde de traverser verticalement le sol
        represente par le maillage.
F1, F2 : FLOTTANT, frequences sur lesquelles l'amortissement
        reduit est ajuste suivant le modele de
        Rayleigh
FC : FLOTTANT, frequence de coupure pour la deconvolution
        par defaut FC = 50 Hz
TYP_F : MOT, type de frontiere : 'WHITE' (par defaut)
        'LYSMER'
P_GAMMA :'TABLE', Description des accélérogrammes d'entrée et de sortie
        pour la déconvolution (facultatif)
  indice 'ENTREE' :'TABLE', description de la nature de l'accéléro
        GAMMAO autre que sur la surface libre (fac
   sous-indice 'NATURE' : Nature du point de contrôle :
        'MOT' INSIDE : profondeur du sol
        'MOT' OUTCROP : outcrop du bedrock
   sous-indice 'CONTROLE' :'MAILLAGE', point de contrôle sur la frontière
        verticale si sous-indice 'NATURE' = INSIDE
  indice 'I' :'MAILLAGE', Ième (i = 1, 2, 3,...) points sur la
        frontière verticale pour lesquels on désire sortir
        l'accélérogramme en champ libre (résultats de
        déconvolution)

En sortie :

TABRESU : TABLE qui contient les resultats du calcul

  indice 'CHAR' : CHARGEMENT, excitation sismique au cours du temps
        sur la frontiere du sol
  indice 'AMOR' : RIGIDITE, frontiere absorbante de type TYP_F
  indice 'DEFO' : EVOLUTION, deformation maximale du sol en fonction
        de la profondeur
  indice 'ACCE' : TABLE, a indice ENTIER, contient les
        accelerations des points definis
        dans P_GAMMA
  indice 'PAS' : FLOTTANT
  indice 'FCDYN' : FLOTTANT, pas de temps et frequence de coupure
        a utiliser pour le calcul de
        l'interaction sol-structure a l'aide
        de la procedure DYNAMIC ou PASAPAS

Remarques :

La procedure n'accepte pas les frontieres obliques. Elle peut traiter
les mouvements horizontaux (onde SV) et verticaux (onde P).

La procedure est developpee pour effectuer la deconvolution sur la
moitie de la frontiere. Lorsque le maillage est symetrique ou
axisymetrique, il suffit d'appeler une fois la procedure DECONV.

Lorsque le maillage ( sol + structure ) n'est pas symetrique, il
doit etre divise en deux moities par l'axe OY. On appelle deux fois
la procedure DECONV pour effectuer la deconvolution des deux
moities du maillage.

## DECONV3D [Mecanique Dynamique] (proc)
    procedure DECONV3D

   TABRESU = DECONV3D COUCHE PC FOND_SOL MOD_SOL MAT_SOL DIR
        GAMMAO F1 F2 (FC) (P_GAMMA)

Objet :

Cette procedure permet d'effectuer des calculs sismiques d'interaction
sol-structure (ISS) en 3D par la methode des elements finis. Elle a
deux fonctions lorsque l'on n'évoque pas la methode de reduction de
domaine de Bielak [1]:
  - Formuler la matrice d'amortissement correspondant a la frontiere
    absorbante visqueuse sur la bordure du maillage de sol,
  - Calculer le chargement sismique au cours du temps a appliquer sur
    la frontiere par la deconvolution du mouvement sismique
    (accelerogramme) donnee en surface libre du sol

Lorsque la methode de Bielak[1] est évoquée (nouvelle option, si
COUCHE.'BLK' existe), le maillage du sol d'entrée (appelé zone interne)
peut être largement reduit. La procedure crée automatiquement une
couche d'elements enveloppe (appelée zone intermediare) et calcule le
chargement sismique à appliquer sur cette zone. Dans ce cas,
l'utilisateur doit créer lui-même une zone de sol externe a l'exterieure
de la zone intermediare et mettre sur sa bordure exterieure une
frontiere absorbante à l'aide de l'operateur AMOR. Dans cette option, il
est possible d'introduire des ondes SH inclinées comme chargement
sismique.

La resolution du probleme peut s'effectuer ensuite dans le domaine
temporel sur l'ensemble du maillage sol-structure avec l'une des
procedures d'integration suivantes :
  - procedure DYNAMIC en cas de comportement lineaire, possibilite
    d'inclure des liaisons unilaterales pour modeliser le decollement
    et le glissement du radier,
  - procedure PASAPAS en cas de comportement non lineaire du sol et de
    la structure.

Commentaire :

En entree :

COUCHE 'TABLE' : table a double indice
  COUCHE.'BLK' : si existe, deconvolution pour la methode de Bielak
  COUCHE.'BLK'.'EP_H' : epaisseur horizontale de la zone intermediare
        verticale
  COUCHE.'BLK'.'EP_V' : epaisseur veriticle de la zone intermediare
        horizontale
  COUCHE.I.'indice' : donnees pour la ieme couche du sol

    indice 'FRONTIERE' 'MAILLAGE' : frontiere verticale de la
        ieme couche
    indice 'MASSE_VOLUMIQUE' 'FLOTTANT' : masse volumique
    indice 'POISSON' 'FLOTTANT' : coefficient de Poisson
    indice 'YOUNG' 'FLOTTANT' : module d'Young
    indice 'AMORTISSEMENT 'FLOTTANT' : amortissement reduit

PC 'MAILLAGE' : point de reference situe au milieu du millage
        de sol ou sur l'axe de symetrie si calcul sur
        la moitie ou le quart du systeme
FOND_SOL 'MAILLAGE' : frontiere horizontale inferieure du sol
MOD_SOL 'MMODEL' : modele du sol
MAT_SOL 'MCHAML' : materiau du sol
DIR 'MOT' : direction de l'acceleration GAMMAO
        'UX' pour la direction X (onde SV)
        'UY' pour la direction Y (onde SH)
        'UZ' pour la direction Z (onde P)
GAMMAO 'EVOLUTIO' : acceleration du 'champ libre' en surface du sol
        comportant une plage initiale a zero
        acceleration sur au moins 100 pas de temps
F1, F2 'FLOTTANT' : frequences sur lesquelles l'amortissement
        : reduit est ajuste suivant le modele de
        RAYLEIGH
FC 'FLOTTANT' : frequence de coupure pour la deconvolution,
        par defaut FC = 50 Hz
P_GAMMA 'TABLE' : points sur la frontiere verticale pour
        lesquels on desire sortir les accelerogrammes

  indice 'ENTREE' :'TABLE' : description de la nature de
        l'accelerogramme GAMMAO autre que sur la surface
        libre (facultatif) ou description de l'onde
        incidente inclinée SH.
    sous-indice 'NATURE' : nature du point de controle :
        'MOT' INSIDE : dans le sol
        'MOT' OUTCROP : outcrop du bedrock
        'MOT' SH : Onde incidente SH inclinée dans
        le cas de la methode Bielak,
        DIR = UX : onde SH dans le plan YZ,
        DIR = UY : onde SH dans le plan XZ.
    sous-indice 'ANGLE' : Angle d'incidence de l'onde SH si
        'NATURE' = SH

    sous-indice 'CONTROLE' :'MAILLAGE':
        si 'NATURE' = 'INSIDE', point de controle
        sur la frontiere verticale,
        si 'NATURE' = 'SH', point de controle à la
        surface du sol pour lequel on impose
        l'accélérogramme du champ libre GAMMAO.

  indice 'I' :'MAILLAGE': ieme (i = 1, 2, 3,...) points sur la
        frontiere verticale pour lesquels on desire sortir
        l'accelerogramme en champ libre (resultats de
        deconvolution)

En sortie :
TABRESU 'TABLE' : table qui contient les resultats du calcul
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DEDA [Maillage Autres]
 Operateur DEDA

 LOG1 = DEDA P1 MAIL1 (FLO1) ;

 Objet :

L'operateur DEDA determine si un point est situe a l'interieur d'un
domaine defini par un maillage.

 Commentaire :

 P1 : objet POINT.

 MAIL1 : objet MAILLAGE, contour (enveloppe) ferme, oriente (voir
        remarque) et constitue d'elements SEG2 (TRI3) en 2D (3D).

 FLOT1 : objet FLOTTANT, facultatif, tolerance pour le test sur la
        nullite de l'angle solide total (voir remarque), sa valeur
        est prise egale a 1E-9 par defaut.

 LOG1 : objet LOGIQUE egal a VRAI si P1 est a l'interieur de MAIL1.

 Remarques :

 On calcule la somme de l'angle solide signe de tous les elements
 de MAIL1 vu depuis le point P1. Si cette somme est nulle
 (inferieure a FLOT1), P1 est considere a l'exterieur du maillage.

 Pour les points situe pres du bord, il convient d'utiliser une
 tolerance FTOL1 "suffisamment grande", d'autant plus que le nombre
 d'elements de MAIL1 est eleve.

 Le maillage MAIL1 doit etre convenablement oriente :
 - Deux elements adjacents doivent avoir la meme orientation, on
   pourra utiliser l'operateur VERS pour le verifier.
 - S'il est constitue de plusieurs parties, les bords internes (les
   "trous") doivent etre orientes dans le sens oppose du bord
   externe.

## DEDANS [Maillage Autres] (proc)
    Procedure DEDANS

    LOG1 = DEDANS PO1 MAIL1 (PREC) ;

    Objet :

 La procedure DEDANS permet de determiner si un point P01 (type POINT)
est situe a l'interieur d'un contour oriente ferme. Cette operation
n'a de sens qu'en dimension 2.

   PO1 : objet de type point.

   MAIL1 : objet de type maillage contenant un contour ferme oriente.

   PREC : precision ( type flottant), par defaut 0.

   LOG1 : objet de type logique qui vaut VRAi si le point est a
        l'interieur de la zone delimitee par le contour.

## DEDO [Maillage Lignes]
    Operateur DEDOUBLE

    GEO3 GEO4 = DEDO GE01 GEO2 ;

    Objet :

    L'operateur DEDOUBLE permet de dedoubler les noeuds de la ligne
GE02 dans l'objet maillage GE01. Le resultat est un nouvel objet
maillage GE03. GEO4 est la partie nouvelle correspondant a GEO2.

    Remarques :

    Cet operateur ne peut etre utilise qu'en dimension 2. GEO2 doit
etre une ligne continue (constituee d'elements SEG2 ou SEG3), et ne doit
pas contenir de bifurcations.

    Exemple :

    OPTI DIME 2 ELEM TRI3;
    P0 = 0. 0.;
    P1 = 5. 0.;
    P2 = 10. 0.;
    D1 = DROI 5 P0 P1;
    D2 = DROI 5 P1 P2;
    MAI1 = TRAN (D1 ET D2) 5 (0. 5.);
    MAI2 = TRAN (D1 ET D2) 5 (0. -5.);
    DED1 DED2 = DEDOUBLE (MAI1 ET MAI2) D1;

$$$$

## DEDU [Maillage Manipulation]
Operateur DEDU
-------------- DEPL

|  1re possibilite  |

   MAI1 = DEDU MAI2 MAI_ANC MAI_NOU ('REGU') ;

Objet :

L'operateur DEDU construit a partir du maillage MAI2 et du maillage
de noeuds maitres MAI_ANC (noeuds de MAI2) un nouveau maillage MAI1
ou l'ensemble des noeuds maitres MAI_ANC est devenu MAI_NOU.
En cas de probleme, il est possible d'utiliser la procedure @DEDUIRE
qui est beaucoup plus onereuse.

Si le mot cle 'REGU' est mentionne, le nouveau maillage MAI1 sera
regularise par deplacement des noeuds au centre de gravite des
noeuds adjacents.

Exemple pour regulariser un maillage existant :

  REGULARI = PASBEAU DEDU (PASBEAU CONT) (PASBEAU CONT) 'REGU' ;

Remarque :

Cette possibilite ne fonctionne actuellement que pour les TRI3 et QUA4.

|  2e possibilite  |

   NOBJ1 ... NOBJN = OBJ1 ... OBJN DEDU 'TRAN' GEO1 GEO2 ;

Objet :

L'operateur DEDU en presence du mot-cle 'TRAN' cree un objet dont le
support geometrique s'obtient a partir du support de l'objet initial
selon la meme transformation qui permet d'obtenir GEO2 a partir de
GEO1. Les points des supports de OBJ1 .. OBJN doivent appartenir a
GEO1, ainsi ceux de NOBJ1 .. NOBJN appartiennent a GEO2.

Il est necessaire de respecter la syntaxe.

Commentaire :

OBJ1 ... OBJN : types POINT, CHPOINT, MCHAML, MMODEL, MAILLAGE
        OBJ1 peut aussi etre une table. Dans ce cas tous les
        objets contenus dans la table, qui doivent etre d'un des
        types ci-dessus, subiront la transformation.Si une table
        est donnee, il ne doit pas y avoir d'autres objets.

GEO1 : type MAILLAGE

GEO2 : type MAILLAGE, topologiquement equivalent a GEO1

NOBJ1 ... NOBN : resultats respectivement de memes types
        que OBJ1 ... OBJN

|  3e possibilite  |

   NOBJ1 ... NOBJN = OBJ1 ... OBJN
        DEDU FLOT1 POIN1 (POIN2 si 3D) 'ROTA' GEO1 GEO2 ;

Objet :

L'operateur DEDU en presence du mot-cle 'ROTA' cree un objet dont le
support geometrique s'obtient a partir du support de l'objet initial
selon la rotation d'angle FLOT1, de centre POIN1 en 2D, d'axe POIN1
POIN2 en 3D, qui permet egalement d'obtenir GEO2 a partir de GEO1.
Les points des supports de OBJ1 .. OBJN doivent appartenir a GEO1,
ainsi ceux de NOBJ1 .. NOBJN appartiennent a GEO2.
Si les operandes possedent des composantes :
   'UX' 'UY 'UZ' ou 'FX' 'FY' 'FZ' ou
   'RX' 'RY' 'RZ' ou 'MX' 'MY' 'MZ' ou
   'SMXX' 'SMYY' 'SMZZ' 'SMXY' 'SMXZ' 'SMYZ' ou
   'EPXX' 'EPYY' 'EPZZ' 'GAXY' 'GAXZ' 'GAYZ',
celles-ci subissent egalement la rotation, les autres composantes
restant inchangees.

Il est necessaire de respecter la syntaxe.

Cette possibilite de l'operateur 'DEDU' n'est pas utilisable en
DIMEnsion 1 (sans interet).

Commentaire :

OBJ1 ... OBJN : types POINT, CHPOINT, MCHAML, MMODEL, MAILLAGE
        OBJ1 peut aussi etre une table. Dans ce cas tous les
        objets contenus dans la table, qui doivent etre d'un des
        types ci-dessus, subiront la transformation.Si une table
        est donnee, il ne doit pas y avoir d'autres objets.

GEO1 : type MAILLAGE, contient les points des supports des operandes

GEO2 : type MAILLAGE, image de GEO1 par la rotation specifiee

NOBJ1 ... NOBJN : resultats respectivement de memes types
        que OBJ1 ... OBJN

|  4e possibilite  |

   CHP1 = DEDU GEO1 CHP2;

Objet :

Connaissant un champ de deplacement (CHP2) de certains noeuds
d'un maillage GEO1, l'operateur deduit un champ de deplacements
regularise de tous les noeuds de GEO1.

|  5e possibilite  |

        (|'DENS' CHPO4) ;
   CHPO2 = 'DEDU' 'ADAP' MAIL (RIG1 (CHPO1)) (|'METR' |CHAM1 MOD1|)
        (  |CHPO3 MOT1|)
        ('THET' FLOT1)
        ('NITM' ENTI1)
        ('ACVG' LOGI1)
        ('DISG' MOT2)
        ('IDIR' ENTI2)
        ('TINV' TABL1) ;

Objet :

Genere un champ de deplacement permettant de regulariser un
maillage ou de l'adapter suivant une metrique.

Commentaire :

MAIL : maillage a regulariser ou adapter

RIG1 : Conditions sur les deplacements
CHPO1 (par defaut, on bloque les noeuds frontieres de MAIL)

CHAM1 : champ par element defini aux noeuds donnant l'inverse
        d'une metrique :
        tenseur symetrique de composantes G11, G21, G22,...
        (par defaut, le tenseur unite)

MOD1 : modele associe a CHAM1

CHPO3 : idem CHAM1 mais avec la donnee d'un chpoint et d'un nom
MOT1 d'espace de discretisation, cf. notice NLIN

CHPO4 : avec l'option DENSite, regularise le maillage suivant la
        carte de densite CHPO4 (voir MESU).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DEDUADAP [Fluides Resolution] (proc)
Procedure DEDUADAP

Objet :

Cette procedure implemente la resolution du probleme
d'optimisation non-lineaire qui sous-tend l'algorithme
utilise par l'operateur 'DEDU' option 'ADAP'.

Voir la notice de 'DEDU'.

## DEFO [Post-traitement Affichage]
    Operateur DEFORME
    ----------------- VECT

    DEF1 = DEFORME  GEO1 CHPO1 (FLOT1) (VEC1) (COUL1) | CHPO2

    Objet :

    L'operateur DEFORME construit un objet de type DEFORME a partir
d'une geometrie initiale et d'un champ de deplacements.
On peut appliquer aux deplacements un coefficient d'amplification.
Une couleur peut etre attribuee a l'objet DEFORME. Un champ scalaire
 peut etre associe a cet objet de type DEFORME.

    Commentaire :

    GEO1 : geometrie initiale (type MAILLAGE)

    CHPO1 : champ de deplacements (type CHPOINT)

    FLOT1 : coefficient d'amplification (type FLOTTANT)

    VEC1 : option pour representer un champ par des vecteurs (type
        VECTEUR)

    COUL1 : couleur attribuee a l'objet deforme (type MOT),
        la couleur par defaut est celle du maillage a deformer
        (voir les operateurs COUL et AFCO)

    CHPO2 : champ scalaire (type CHPOINT)

    CHEL : champ scalaire (type MCHAML)

    MODEL : modele associe (type MMODEL)

    Remarque 1 :

    Si le coefficient d'amplification FLOT1 n'est pas precise,
il est determine automatiquement.

    Remarque 2 :

    Cet objet peut etre visualise par l'operateur TRACE. Son trace peut
etre interprete comme le trace de la deformee de l'objet GEO1 par le
champ de deplacements CHPO1, avec une amplification FLOT1, dans la
couleur COUL.

    Remarque 3 :

    Il est possible d'associer un objet VEC1 de type VECTEUR a l'objet
DEFORME, ce qui permet d'obtenir sur le trace de la deformee la
representation par des vecteurs d'un champ (par exemple le chargement
ou les reactions aux blocages).

    Remarque 4 :

    Il est possible, dans le but de tracer plusieurs deformees sur le
meme graphique, d'appliquer l'operateur ET entre des objets de
type DEFORME.

     Remarque 5 :

     Le champ de scalaire est represente sous forme d'isovaleurs sur la
deformee.

## DEG3 [Mathematiques Fonctions]
    Operateur DEG3

      XR1 XI1 XR2 XI2 XR3 XI3 = DEG3 A0 A1 A2 A3 ;

    Objet :

    L'operateur DEG3 calcule les racines d'un polynome du 3-eme
degre.

      Commentaire :

      Le polynome est de la forme : A0 + A1*X + A2*X**2 + A3*X**3

      Les racines sont : XR1 + i*XI1
        XR2 + i*XI2
        XR3 + i*XI3

      A0, A1, A2, A3, XR1, XI1, XR2, XI2, XR3, XI3 sont de type
      FLOTTANT.

## DENS [Maillage Generaux]
Directive DENSITE

DENSITE FLOT1 ;

Objet :

La directive DENSITE sert a definir, par defaut, la taille locale
FLOT1 (type FLOTTANT) de la maille s'appuyant sur les points a
construire.

Alternativement, on peut utiliser la directive 'OPTI' 'DENS' FLOT1 ;

Commentaire :

A chaque point du maillage est associee la taille de la maille
venant le toucher. Cette taille peut evidemment varier d'un point a
l'autre. Elle est exprimee dans la meme unite que les coordonnees
des points.

Au cours d'une operation de creation de mailles entre deux points le
programme s'arrangera pour que la taille des mailles en ces deux
points soit la densite associee et pour qu'une progression
geometrique des tailles entre les deux points soit realisee.

ATTENTION :

Ne pas ecrire "DENS = 1 ;". Cela reviendrait a construire le nombre
entier DENS de valeur 1 ce qui n'est vraisemblablement pas le but
vise par l'utilisateur.

## DEPB [Mecanique Dynamique]
    Operateur DEPB

    ATTA1 = DEPB STRU1 CHPO1 ;

    Objet :

    L'operateur DEPB cree un objet de type ATTACHE qui est utilise pour
imposer des deplacements en certains points d'une sous-structure,
representee par sa base modale.

    Commentaire :

      STRU1 : sous-structure (type STRUCTURE)

      CHPO1 : champ par point cree par l'operateur DEPI (type CHPOINT)

      ATTA1 : objet resultat (type ATTACHE ,sous-type DEPI)

## DEPI [Mecanique Limites]
   Operateur DEPIMPOSE
   ------------------- SYMT ANTI

   CHPO1 =  DEPI  RIG1 | FLOT1  ;
        | CHPO2  ;
        | 'RELA' CHPO3 ;

   DEPI TAB1 ;

   Objet :

   L'operateur DEPI specifie la valeur de certains blocages ou
   relations.

   Commentaires :

   RIG1 : objet de type RIGIDITE, de sous-type BLOCAGE, definissant
        les conditions imposees a des degres de liberte.

   FLOT1 : valeur (type FLOTTANT) a imposer a tous les blocages
        uniformement.

   CHPO2 : champ (type CHPOINT) permettant d'imposer des valeurs
        aux inconnues bloquees lorsque les blocages ne portent que
        sur une inconnue.

        Les composantes doivent etre les memes que celles des
        blocages de RIG1. Par exemple :

        BLO1 = BLOQUE LI1 'UX' ;
        CCX = COOR 1 LI1 ;
        CCXX = NOMC 'UX' CCX ;
        FO1 = DEPI BLO1 CCXX ;

   CHPO3 : champ (type CHPOINT) permettant d'imposer des valeurs aux
        relations entre differents degres de liberte ('option 'RELA').
        Cette option n'est possible que si les relations impliquent
        les degres de liberte d'un meme noeud.

        Le champ CHPO3 ne doit contenir qu'une seule zone et
        n'avoir qu'une seule composante nommee 'SCAL'.

   CHPO1 : resultat (type CHPOINT), qu'il convient d'additionner
        au second membre (forces en mecanique) avant d'effectuer
        la resolution.

   TAB1 : type TABLE, sous-type 'LIAISONS_STATIQUES'. Les indices de
        TAB1 sont des entiers pointant sur des objets de type TABLE.
        Pour chacun l'indice 'FORCE' est cree : CHPOINT exprimant au
        'POINT_LIAISON', de type POINT, une force d'amplitude unite
        duale du 'DDL_LIASON', de type MOT, compatible avec le
        'BLOCAGE', de type RIGIDITE.

Remarque : Les degres de liberte de rotation sont exprimes en radians,
        il convient donc de donner les valeurs qui leurs sont
        imposees en cette unite.

## DEPL [Maillage Manipulation]
    Directive DEPLACER
    ------------------ MOIN SYME

    DEPL GEO1 |'PLUS' |  | VEC1  | ;
        |'MOINS'|  | CHPO1 | ;
        |'COOR' | 'CYLI'  POIN1  POIN2 (POIN3 SI 3D) ;
        |  | 'CART' ;
        |'TOUR' |  ANGL1  | POIN1 (POIN2 SI 3D) ;
        |  |  CHPO1  |
        |'HOMO'  RAPP1  POIN1 ;
        |'AFFI'  RAPP1  POIN1 POIN2 ;
        |'SYME' | 'POIN'  POIN1 ;
        |  | 'DROIT' POIN1 POIN2 ;
        |  | 'PLAN'  POIN1 POIN2 POIN3 ;
        |'PROJ' |('CYLI') VEC1  | |'PLAN' POIN1 POIN2 POIN3 ;
        |  | 'CONI'  SOMM1 | |'SPHE' CENT1 POIN1 ;
        |  |'CYLI' CENT1 CENT2 POIN1 ;
        |  |'CONI' POIN1 POIN2 POIN3 ;
        |  |'TORI' CENT1 POIN1 POIN2 POIN3 ;
        |  |'DROI' POIN1 POIN2 ;
        |  |'CERC' CENT1 POIN1 ;
        |'COOR' | 'CYLI'  POIN1  POIN2 ( POIN3 SI 3D) ;
        |  | 'CART' ;
        |'MILI' ;
        |'BARS' | POIN1 | (FLOT1) ;
        |'DEDU' | GEO2 GEO3 ;
        | CHP1 ;

    Objet :

    La directive DEPLACER a pour effet de deplacer l'ensemble des
points appartenant a l'objet GEO1 (type MAILLAGE ou POINT) sans
creer un nouvel objet.

    Commentaire :

    En presence des mots-cles suivants :

 'PLUS' : on applique a l'ensemble des points une translation
        du vecteur VEC1 (type POINT) ou du champ CHPO1 (type
        CHPOINT).

 'MOINS' : on applique a l'ensemble des points une translation
        du vecteur -VEC1 (type POINT) ou du champ -CHPO1 (type
        CHPOINT).

 'TOUR' : on applique a l'ensemble des points une rotation d'angle
        ANGL1 (type FLOTTANT) ou d'angle CHPO1 (type CHPOINT)
        autour du POIN1 (type POINT) en 2D
        ou de l'axe defini par POIN1 POIN2 (type POINT) en 3D.

 'HOMO' : on applique a l'ensemble des points une homothetie de centre
        POIN1 (type POINT) et de rapport RAPP1 (type FLOTTANT).

 'AFFI' : on applique a l'ensemble des points une affinite laissant
        invariant le point POIN1 (type POINT), de direction definie
        par (POIN2 - POIN1) et de rapport RAPP1 (type FLOTTANT).

 'SYME' : on applique a l'ensemble des points une symetrie suivant
        l'operation desiree :
        - 'POIN' = par rapport au point POIN1 (type POINT)
        - 'DROI' = par rapport a la droite POIN1 POIN2
        (type POINT)
        - 'PLAN' = par rapport au plan POIN1 POIN2 POIN3
        (type POINT)

 'PROJ' : on applique a l'ensemble des points une projection
        CYLIndrique suivant la direction definie par le vecteur
        VEC1 (type POINT) ou CONIque de centre SOMM1 (type POINT)
        sur la surface demandee :
        - PLAN defini par les points POIN1 POIN2 POIN3
        (type POINT)
        - SPHEre de centre CENT1 (type PPOINT) passant par
        le point POIN1 (type POINT)
        - CYLIndre d'axe passant par les points CENT1 et CENT2
        (type POINT)
        - CONE de sommet POIN1 (type POINT) dont l'axe passe par
        le point POIN2 et contenant le point POIN3 (type POINT)
        - TORE de centre CENT1 dont l'axe passe par le point
        POIN1, dont un centre de petit cercle est le point
        POIN2 et contenant le point POIN3.

     En 2D, la projection se fait sur une ligne :
       - DROIte definie par les points POIN1 et POIN2 (type POINT)
       - CERCle de centre CENT1 passant par le point POIN1 (type POINT).

 'COOR' : on effectue un changement de systeme de coordonnees entre
        les coordonnees cartesiennes et cylindriques.

        'CYLI' : on desire des coordonnees cylindriques.
        Les angles vont de -180 a +180 degres.
        En 2D, POIN1 est le centre du systeme de
        coordonnees et la ligne definie par POIN1
        vers POIN2 donne l'angle theta nul.
        En 3D, POIN1 est le centre du systeme de
        coordonnees, l'axe defini par POIN1 vers POIN2
        est l'axe Z positif et le plan defini par les
        trois points POIN1 POIN2 et POIN3 donne
        l'angle theta nul.

        'CART' : on desire des coordonnees cartesiennes.
        Les angles fournis doivent etre exprimes en
        degres variant entre -180 et +180.
        En 2D, l'origine du repere ne change pas et
        l'axe X correspond a theta egal zero.
        En 3D, l'origine et l'axe Z ne changent pas
        et l'axe X correspond a theta egal zero.

 'MILI' : Les points milieux des elements quadratiques sont
        projetes sur le plan mediateur des deux extremites.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DEPOU [Post-traitement Analyse] (proc)
Procedure DEPOU
--------------- PHASAGE

  TAB1 = DEPOU ........;

Objet :

  Cette procedure permet de fabriquer des evolutions de tensions
  le long des cables pour les differents instants du calcul.
  Elle est appellee automatiquement par la procedure PHASAGE.

## DESCOUR [Magnetostatique Magnetostatique] (proc)
Procedure DESCOUR

DESCOUR TAB1 ENT1 GEO1 MOT1 FLOT1

Objet :

Description des zones de courants en magnetostatique a
potentiel vecteur.

Commentaire :

TAB1 TABLE qui contiendra le descriptif des zones de courant
ENT1 numero d'ordre de la zone decrite
GEO1 maillage de la zone d'ordre ENT1
MOT1 mot valant 'AMP' OU 'AT' ou 'FIL'
FLOT1 flottant densite de courant J (AMP) ou nombre
       d'amperes totaux ( AT ) ou amperes par points (FIL )
       dans ce dernier cas Geo1 est de type maillage POI1

       On passe autant de fois dans DESCOUR qu'il y a de
       zones distinctes de courant

## DESS [Post-traitement Affichage]
    Directive DESSIN
    ---------------- MOT CHAI

   DESS (EVOL1 ET EVOL2 ET ... EVOLN) ( 'LOGX' ) ;
        ( 'LOGY' ) ;
        ( 'GRIL' (TYPELIGN) ('GRIS') ) ;
        ( 'CARR' ) ;
        ( 'XBOR' XINF XSUP ) ;
        ( 'YBOR' YINF YSUP ) ;
        ( 'XGRA' DELTAX ) ;
        ( 'YGRA' DELTAY ) ;
        ( 'MIMA' ) ;
        ( 'DATE' ) ;
        ( 'LOGO' ) ;
        ( 'SEPA' ) ;
        ( 'CHOI' (N1 (N2 (N3 ...))) ) ;
        ( 'TITR' 'titre global' ) ;
        ( 'TITX' 'xlabel' ) ;
        ( 'TITY' 'ylabel' ) ;
        ( 'POSX' MOPOSX ) ;
        ( 'POSY' MOPOSY ) ;
        ( 'XFMT' MOXFMT ) ;
        ( 'YFMT' MOYFMT ) ;
        ( 'AXES' ) ;
        ( 'NCLK' ) ;
        ( 'LEGE' (POSITION) ) ;
        ( TAB1 ) ;

   avec :
   TAB1 . i = CHAI ('NOLI'_) (| 'TIRR'_ |) ('REMP'_ ('BLAN'_) )  ...
        | 'TIRC'_ |
        | 'TIRL'_ |
        | 'TIRM'_ |

        ... ('LABEL'_ MOT3) ('MARQ'_ (MOT2) ('PLEIN'_) MOT1) ('REGU');

   ( ou l'on definit le caractere espace par : _ = MOT ' '; )

   TAB1 . 'TITRE' . i = 'CHAI' MOT4 ;

   TAB1 . 'INITIAL' . i = ENT1 ;
   TAB1 . 'FINAL' . i = ENT2 ;

   TAB1 . 'LIGNE_VARIABLE' . i = LENT1 ;

    Objet :

    Cette directive permet de tracer une EVOLUTION.
    Cette evolution est une eventuelle concatenation de plusieurs
    sous-evolutions EVOLi.

    Commentaire :

        OPTIONS GENERALES DE LA ZONE GRAPHIQUE

    PAR DEFAUT :

      - Courbe lineaire en X et en Y
      - Cadrage automatique
      - Fenetre rectangulaire
      - Courbes tracees simultanement dans le meme cadre
      - Courbes sans marqueurs
      - Points reunis par des droites
      - Axes gradues avec des multiples de .02 et .05
      - Titre general = celui de l'evolution
      - Nom axe X (resp. Y) = nom absc (resp. ordo) 1ere sous-evolution

    OPTIONS DISPONIBLES :

     'LOGX' : Echelle logarithmique pour l'axe des abscisses.
     'LOGY' : Echelle logarithmique pour l'axe des ordonnees.
     'GRIL' : Afficher une "grille". Suivi éventuellement de :
       - TYPELIGN : MOT definissant le type de ligne pour la grille
        = |  'LIGN'  (LIGNe continue = par défaut)
        |  'TIRR'  (TIRets normaux)
        |  'TIRC'  (TIRets Courts)
        |  'TIRL'  (TIRets Longs),
        |  'TIRM'  (TIRets Mixtes)
        |  'POIN'  (POINtillés)
       - 'GRIS': Colore en gris les lignes consituant la grille.
     'CARR' : Cadre carre et meme echelle pour les axes X et Y.
     'XBOR' : On impose les bornes XINF et XSUP sur l'axe des X.
     'YBOR' : On impose les bornes YINF et YSUP sur l'axe des Y.
     'XGRA' : On impose l'espace entre chaque graduation de l'axe des X
        a DELTAX (uniquement possible avec une echelle lineaire).
     'YGRA' : On impose l'espace entre chaque graduation de l'axe des Y
        a DELTAY (uniquement possible avec une echelle lineaire).
     'MIMA' : Affichage des minimum et maximum globaux aux courbes.
     'DATE' : Affichage de la date.
     'LOGO' : Affichage du logo.
     'SEPA' : Courbes tracees separement avec les memes axes.
     'LEGE' : Ajout des legendes pour les courbes (voir plus bas).
        Le nombre de legendes individuelles est limité a 30.
        Suivi éventuellement de :
       - POSITION : MOT definissant la position souhaitee de la legende
        = | 'NO' (Nord-Ouest)
        | 'NE' (Nord-Est)
        | 'SO' (Sud-Ouest)
        | 'SE' (Sud-Est)
        | 'EXT' (Exterieur = par défaut)
        | 'XY' suivi de 2 FLOTTANT X Y.
        Si la legende est a l'exterieur du cadre, le cadre sera
        necessairement carre.
     'CHOI' : Restreint l'affichage aux courbe(s) de rang(s) N1, N2 ...
     'TITR' : Modification du titre general.
     'TITX' : Modification du nom de l'axe des abscisses (20 caracteres
        maximum).
     'TITY' : Modification du nom de l'axe des ordonnees (20 caracteres
        maximum).
     'POSX' : Permet de positionner le titre de l'axe des abscisses.
        Doit être suivi du mot-clé MOPOSX
        à choisir parmi : 'EXCE' (position excentrée),
        'CENT' (position centrée).
     'POSY' : Permet de positionner le titre de l'axe des ordonnés.
        Doit être suivi du mot-clé MOPOSY
        à choisir parmi : 'EXCE' (position excentrée),
        'CENT' (position centrée).
     'XFMT' : Permet d'imposer le format d'ecriture des valeurs de
        l'axe X via le format defini par MOXFMT.
        Exemples de format pour MOXFMT :
        '(I4)' : entier sur 4 chiffres
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DESTRA [Post-traitement Affichage] (proc)
Procedure DESTRA
---------------- TRACHIT NTAB

  DESSTRA TAB1 (TAB2) (EVOL1 (TAB3))
        ('TABMIMA')
        ( 'LOGX' )
        ( 'LOGY' )
        ( 'GRIL' )
        ( 'XBOR' XINF XSUP )
        ( 'YBOR' YINF YSUP )
        ( 'MIMA' )
        ( 'DATE' )
        ( 'LOGO' )
        ( 'SEPA' )
        ( 'CHOI' | N1 (N2 (N3 ...)) | )
        (  | LENTI1  | )
        ( 'TITR' 'bla bla...' )
        ( 'TITX' 'blax' )
        ( 'TITY' 'blay' )
        ( 'AXES' )
        ( 'NCLK' )
        ( 'REGU' ) ;

 Objet

   Cette procedure permet de tracer a l'aide de l'operateur DESS
   les courbes des evolutions contenues dans les tables sorties
   par TRACHIS ou TRACHIT. Les textes contenus dans TAB1.'LEGEND1'
   et TAB1.'LEGEND2' sont concatenes et mis en legende.

   Elle permet egalement de tracer le tableau des maxima et minima
   pour ces memes evolutions. Dans ce cas, TAB1.'LEGEND1' est le
   sous-titre du tableau (ex: l'espece dont on observe la
   concentration), et TAB1.'LEGEND2' l'en-tete de chaque ligne (ex: le
   temps correspondant a chaque courbe).

 Commentaires

   TAB1 Table issue de TRACHIS ou TRACHIT.

   TAB2 Table optionnelle (Cf. DESS) contenant des specifications
        de trace qui viendront ecraser (specifs. de tracer) ou
        completer (titre) les chaines composees automatiquement.
        Elle est indicee comme la table, et non au fil des
        sous-evolutions eventuelles.

   EVOL2 evolution supplementaire eventuelle a superposer, avec

   TBDES2 sa table de specifications de tracer (optionnelle, Cf. DESS)
        indicee de façon standard (suivant les sous-evolutions)

   'TABMIMA' mot-clef indiquant que l'on veut tracer le tableau
        des valeurs minimale et maximale de chaque evolution.
        (Cf. NTAB).
        La premiere colonne du tableau contiendra les textes
        de TAB1.'LEGEND2'. Le sous-titre de la table est
        TAB1.'LEGEND1'.

   'CHOI' suivi des indice ou de la liste des indices de la table
        TAB1 a prendre en compte (defaut = tous). Cette
        fonctionnalite ressemble a celle de l'operateur DESS, mais
        en differe par le fait que DESS considere les
        sous-evolutions alors que DESTRA considere des evolutions
        eventuellement complexes.

   'REGU' mot-clef demandant que les marqueurs soient places a
        intervalles reguliers (Cf. operateur DESS)

   Tous les autres mot-clefs sont des options generales de DESS
        (Cf. DESS) les mots possibles sont : 'LOGX' 'LOGY' 'GRIL'
        'CARR' 'XBOR' 'YBOR' 'MIMA' 'DATE' 'LOGO' 'SEPA'
        'TITR' 'TITX' 'TITY' 'AXES' 'NCLK'.

## DETO [Multi-physique Multi-physique]
    Operateur DETO

    CHP2 CHP3 CHP4 = DETO CHP1 ;

    Objet :

    L'operateur DETO evalue pour un melange O2/N2/H2/H2O les
conditions CJ (Chapman-Jouguet), AICC (Adiabatic Isochore Complete
Combustion) et Zeldovitch-Neuman-Doringts (ZND), la vitesse de CJ
ainsi que le taux d'avancement de la detonation stable.

    Commentaire :

       CHP1 : Objet de type CHPOINT decrivant le melange.

       CHP2 : Objet resultat de type CHPOINT contenant les
        conditions CJ, la vitesse CJ et le taux
        d'avancement de la detonation stable.

       CHP3 : Objet resultat de type CHPOINT contenant les
        conditions ZND.

       CHP4 : Objet resultat de type CHPOINT contenant les
        conditions AICC.

    Remarques :

    1) Le nom des composantes de CHPO1 sont :
 'O2', 'N2', 'H2' et 'H2O' : nombre de moles des constituants
 'P' , 'T' : pression et temperature du melange

    2) Le nom des composantes des CHPO resultats sont :
 'RCJ' 'TCJ' et 'PCJ' : densite, pression et temperature CJ
 'TAUX' et 'VCJ' : taux d'avancement et vitesse de CJ.
 'RZND' 'TZND' et 'PZND' : densite, pression et temperature ZND
 'RAIC' 'TAIC' et 'PAIC' : densite, pression et temperature AICC

    3) Les unites sont les suivantes : pression en Pa, temperature
 en K, densite en kg/m3 et vitesse en m/s.

## DETR [Langage Base]
    Directive DETR
    -------------- PLAC

    DETR | OBJET1 ('GEOMETRIE') ('TOUT') ('ELEMENTAIRE') |;
        |  |
        | 'TRAC'  ISEG  |

        OBJET1=ATTACHE,CHPOINT,CONFIGUR
        EVOLUTIO,LISTENTI,LISTMOTS
        LISTREEL,MAILLAGE,MCHAML
        RIGIDITE,SOLUTION,LISTOBJE

    Objet :

    Cette directive detruit l'objet OBJET1. Elle ne doit pas etre
utilisee a priori; son utilisation est interne a CASTEM2000.
    En presence du mot TRAC et de la valeur ISEG l'operateur
previendra s'il doit supprimer le segment ISEG.

    Commentaire :

    Les types d'objets destructibles sont :

    ATTACHE CHPOINT CONFIGUR EVOLUTIO LISTENTI SOLUTION

    LISTMOTS LISTREEL MAILLAGE MCHAML RIGIDITE

    Remarque :

    Dans le seul cas oº OBJET1 est de type CHPOINT, il est autorise
d'indiquer l'option 'GEOMETRIE'. La geometrie sous-jacente a OBJET1 est
alors detruite, ce qui n'est pas le cas sinon.

    Dans le seul cas oº OBJET1 est de type MAILLAGE il est autorise
d'indiquer l'option 'TOUT'. L'objet et ses sous-objets sont alors
detruits.

    Dans le seul cas oº OBJET1 est de type RIGIDITE il est autorise
d'indiquer l'option 'ELEMENTAIRE'. L'objet est alors detruit
ainsi que les matrices elementaires le composant.

    Dans le cas oº, OBJET1 est de type EVOLUTION il est autorise
d'indiquer l'option 'TOUT'. L'objet est alors detruit ainsi
que les listes de reels le composant.

    Dans le cas oº OBJET1 est de type SOLUTION les objets CHPOINT
et MCHAML le composant sont egalement detruits (les geometries sous-
jacentes des champs ne le sont pas ).

## DEVE [Mecanique Limites]
    Operateur DEVERSOIR

    ATTA1 = DEVE STRU1 STRU2 'GRAV' FLOT1 'RHO' FLOT2 'RAYO' FLOT3

        'ZINI' FLOT4 'HAUT' FLOT5 'EPLA' FLOT6 'EPLB' FLOT7 ;

    Objet :

    L'operateur DEVERSOIR construit un objet de type ATTACHE qui
contient les donnees d'une liaison de type DEVERSOIR.

    La liaison DEVERSOIR est un modele de couplage hydro-elastique
entre deux collecteurs annulaires limites par une virole mince.
Le fluide se deverse du collecteur superieur dans le collecteur
inferieur (les collecteurs sont des lames d'epaisseur faible
par rapport au rayon).

    Commentaire :

   STRU1 : objet qui contient les points de liaison sur la lame du haut
        (type STRUCTURE).

    STRU2 : objet qui contient les points de liaison sur la lame du bas
        (type STRUCTURE).
        (les points superieurs et inferieurs doivent correspondre)

   'GRAV' : mot-cle suivi de :
    FLOT1 : acceleration de la pesanteur (type FLOTTANT)

   'RHO' : mot-cle suivi de :
    FLOT2 : masse volumique du fluide (type FLOTTANT)

   'RAYO' : mot-cle suivi de :
    FLOT3 : rayon du deversoir (type FLOTTANT)

   'ZINI' : mot-cle suivi de :
    FLOT4 : hauteur de fluide au dessus du rebord du deversoir
        a l'equilibre (type FLOTTANT)

   'HAUT' : mot-cle suivi de :
    FLOT5 : hauteur de chute (type FLOTTANT)

   'EPLA' : mot-cle suivi de :
    FLOT6 : epaisseur de la lame fluide superieure (type FLOTTANT)

   'EPLB' : mot-cle suivi de :
    FLOT7 : epaisseur de la lame fluide inferieure (type FLOTTANT)

    ATTA1 : objet resultat (type ATTACHE)

## DFDT [Mecanique Resolution]
     Operateur DFDT

     Syntaxe EQEX (cf EQEX) :

     ... 'EQEX' ... 'OPTI' MOT1 MOT2 MOT3 ('INCOD' MOT4)
        'ZONE' MOD2
        'OPER' 'DFDT' OBJ1 OBJ2 (OBJ6) OBJ3 (OBJ4) (OBJ5)
        'INCO' MOT5 (MOT6)

     Objet :

     L'operateur DFDT discretise le terme de derivee en temps d'une
equation scalaire ou vectorielle.

     Cet operateur est appele par la procedure transitoire EXEC.
La syntaxe indiquee permet a l'utilisateur de construire a l'aide
de l'operateur EQEX les donnees necessaires a l'operateur.

     Commentaires :

    'OPTI' : Mot cle introduisant les options numeriques de DFDT
     MOT1 : Type de discretisation spatiale ('EF','VF','EFM1')
     MOT2 : Type de discretisation temporelle ('IMPL')
     MOT3 : Type de decentrement ('CENTREE','SUPG','SUPGDC')

    'INCOD': Precise le support de l'inconnue (facultatif)
     MOT4 : 'CENTRE'

    'ZONE' : Mot cle introduisant les informations geometriques
     MOD2 : MODEL de sous-type 'NAVIER_STOKES' pour la zone ou
        s'applique DFDT

    'OPER' : Mot cle introduisant les donnees physiques associees
        a l'operateur dont le nom suit
    'DFDT' : Nom de l'operateur
     OBJ1 : Coefficient multiplicateur
        (CHPOINT SCAL [CENTRE ou SOMMET] ou FLOTTANT ou MOT)
     OBJ2 : Inconnue au pas de temps precedant (CHPOINT ou MOT)
     OBJ3 : Valeur du pas de temps (FLOTTANT ou MOT)
        Dans le cas particulier ou on indique 'DELTAT' pour
        OBJ3 DFDT va chercher le pas de temps dans la table
        PASDETPS calcule automatiquement en explicite par les
        operateurs NS NSKE ou TSCA.
     OBJ4 : Champ de vitesse pour decentrement SUPG ou SUPGDC
        (CHPOINT VECT SOMMET ou POINT ou MOT)
     OBJ5 : Coefficient de diffusion pour decentrement SUPG ou SUPGDC
        (CHPOINT SCAL [CENTRE ou SOMMET] ou MOT)
     OBJ6 : Inconnue 2 pas de temps en arrier, pour la directive BDF2
        dans EQEX, (CHPOINT ou MOT)
     OBJ4 et OBJ5 sont facultatifs si MOT3='CENTREE'.

    'INCO' : Mot cle introduisant le nom des inconnues primale et duale
     MOT5 : Nom de l'inconnue primale
     MOT6 : Nom de l'inconnue duale
     Pour l'instant, primale=duale : MOT6 est donc facultatif.

     Remarques :

     1) Lorsque OBJi est de type MOT, l'operateur utilise le champ
contenu dans la table INCO a l'indice MOT indique.

     2) Le support geometrique (spg) des inconnues contient une des
classes de points du modele 'NAVIER_STOKES'.Selon la formulation
choisie les compatibilites suivantes sont verifiees :
   - En formulation EF ou EFM1, le spg de la duale contient SOMMET
   - En formulation VF ou EFMC, le spg de la duale contient CENTRE
   - Avec MOT4, on peut autoriser le cas CENTRE en EFM1 et en EF, le
resultat obtenu etant identique a une formulation VF

     3) Le coefficient multiplicateur OBJ1 et la diffusion OBJ5
peuvent avoir comme spg SOMMET. Dans l'evaluation des termes
elementaires, ces champs sont moyennes par element.

     4) L'utilisateur-programmeur developpant ses propres procedures
transitoire appellera DFDT suivant la syntaxe :
  B A = DFDT TAB1 ;
avec TAB1 : Table de sous type EQEX contenant les informations
        physiques et numeriques de l'operateur DFDT. Cette
        table est construite par l'operateur EQEX.
     A : Matrice "masse" de type MATRIK
     B : Second membre de type CHPO. Le nom de l'inconnue duale
        MOT6 etant le nom de la composante du CHPO cree.

## DFER [Mathematiques Autres]
Operateur DFER

  CHP1 = DFER GEO1 GEO2 (FLOT1) ;

Objet :

L'operateur DFER fabrique un chpoint de densite de presence de fers dans un
maillage massif.

  Commentaire :

  GEO1 : objet maillage constitue d'elements massifs.

  GEO2 : objet maillage constitue des elements seg2 ou seg3

  FLOT1 : flottant donnant la distance d'influence d'un fer ( par defaut
        FLOT1 vaut 0.3)

  CHP1 : objet de type chpoint representant la densite de fers

## DFOU [Post-traitement Analyse]
    Operateur DFOURIER

      CH2 = DFOU CH1 FLOT1 ;

    Objet :

    Dans le cas d'une analyse en serie de Fourier, l'operateur DFOURIER
calcule les valeurs du champ CH1 pour un angle donne FLOT1.

    Commentaire :

      CH1 : champ de forces ou de deplacements (type CHPOINT) ou
        champ de contraintes ou de deformations (type MCHAML).

      FLOT1 : valeur de l'angle en degres (type FLOTTANT).

      CH2 : champ resultat, du meme type que CH1.

## DGSI [Mecanique Dynamique]
 Operateur DGSI

    RES = DGSI OBJ1 <'AXI' i> <'IMPR'> ;

 OBJET :

 Calcul de la matrice masse diagonale ---> Creation d'un CHAMPOIN
 D0=NI ( MASSE LUMPE )

OBJ1 : objet MAILLAGE

AXI : Calcule en coordonee cylindrique 2D
i=1 axe de symetrie ox
i=2 axe de symetrie oy

## DIAD [Mathematiques Autres]
Operateur DIAD
-------------- MULTIREC

LIST1 = DIAD (MOT1) LIST2 ;
        MOT1='DIRE','INVE','IVIN'

objet :

Si MOT1='DIRE'(cte), l'operateur DIAD construit LIST1 en supprimant
une valeur sur deux de LIST2 (type LISTREEL). Le premier point est
toujours conserve.

Si MOT1='INVE'(rse), l'operateur DIAD construit LIST1 en inserant
un zero entre chaque point de LIST2. L'insertion s'effectue toujours
apres le premier point et longueur(LIST1)=2*longueur(LIST2) si
longueur(LIST2) est pair ou 2*longueur(LIST2)-1 si longueur(LIST2)
est impair.

Si MOT1='IVIN', l'operateur DIAD construit LIST1 en inserant entre
chaque point la moyenne de ses deux voisin, avec les memes regles de
longueur que celles indiquees au point precedant.

options :

MOT1 vaut 'DIRE', 'INVE' ou 'IVIN'. Le defaut est 'DIRE'.

## DIAG [Mathematiques Autres]
    Operateur DIAGNEG

    N1 = DIAGNEG RIG1 ;

    Objet :

   L'operateur DIAGNEG donne le nombre de valeurs propres negative d'un
matrice de rigidite (correction faite des multiplicateurs de Lagrange).

    Commentaire :

    RIG1 : matrice de rigidite (type RIGIDITE)

    N1 : nombre de valeurs propres negatives (type ENTIER)

## DIFF [Maillage Manipulation]
OBJ1 = DIFF OBJ2 OBJ3 ;

Operateur DIFFERENCE SYMETRIQUE

Objet :

L'operateur DIFF construit la difference symetrique entre deux objets.

Commentaire :

OBJi : objets de type MAILLAGE, MMODEL ou RIGIDITE.

Remarque 1 : a DIFF b = ( a union b) - (a inter b)

Remarque 2 : pour les objets MMODEL, l'operation est faite
____________ sur les sous-zones. Si l'operation est menee
        dans le but d'obtenir un modele portant sur les
        zones geometriques non communes aux deux modeles,
        alors il convient d'operer sur les maillages.

## DIFFANIS [Fluides Resolution] (proc)
   Operateur DIFFANIS

   newdiff = DIFFANIS MateDiff (typdi) (ANISO) ;

  APPELE PAR TRANSGEN - PAS POUR UTILISATEUR

  ---------MISE A JOUR DE LA DISPERSIVITE----------------------

|-----------------------------------------------------------------|
| Generalites : DIFFANIS remet un teneur de diffusion isotrope avec
|  un format general anisotrope K11 K21 etc ....  |
|  en remplissant avec des 0 les composantes vides  |
|-----------------------------------------------------------------|
|  |
|-----------------------------------------------------------------|
|  ENTREES  |
|-----------------------------------------------------------------|
|  |
| ANISO  LOGIQUE VRAI SI ANISOTROPE, FAUX SINON  |
|  |
| MateDiff : Tenseur de diffusion  (type iso, ..) champoint  |
|  de composante 'K' en isotrope, 'K11', 'K21',  |
|  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
|  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
|  |
| typdi  si 'EFMH' calcul particulier
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
|  |
|  |
| newdiff  : matrice de diffusion identique a Matediff mais ecrite|
|  sous la forme d'un tenseur si elle etait isotrope a  |
|  une composante K (cette composante est alors reportee|
|  a l'identique sur K11, K22 et K33)  |
|  |
|  |

## DIME [Langage Base]
    Operateur DIMENSION

    ENTI1 = DIMENSION OBJET1 (MOT);
        OBJET1=LISTREEL,LISTENTI,LISTMOTS

    Objet :

    L'operateur DIMENSION fournit la dimension ENTI1 (type ENTIER)
    d'un objet OBJET1.

    Commentaire :

|  OBJET1  |  Sous-type  |  Signification  |
|----------|-------------|-----------------------------------|
| MOT  |  |  nombre de caractères  |
|__________|_____________|___________________________________|
| LISTREEL |  |  nombre de FLOTTANTs contenus  |
|__________|_____________|___________________________________|
| LISTENTI |  |  nombre de ENTIERs contenus  |
|__________|_____________|___________________________________|
| LISTMOTS |  |  nombre de MOTs contenus  |
|__________|_____________|___________________________________|
| LISTCHPO |  |  nombre de CHPOINTs contenus  |
|__________|_____________|___________________________________|
| LISTOBJE |  |  nombre d'OBJETS contenus  |
|__________|_____________|___________________________________|
| EVOLUTION|  |  nombre de courbes contenues  |
|__________|_____________|___________________________________|
|  |  |  nombre d'inconnues du  |
| RIGIDITE |  |  probleme physique associe  |
|__________|_____________|___________________________________|
|  |  MODE  |  nombre de modes  |
|  |_____________|___________________________________|
| SOLUTION |  SOLUSTAT  |  nombre de solutions statiques  |
|  |_____________|___________________________________|
|  |  DYNAMIQUE  |  nombre d'instants  |
|__________|_____________|___________________________________|
| TABLE  |  |  nombre d'objets contenus  |
|__________|_____________|___________________________________|
| CHARGEME |  |  nombre d'objets contenus  |
|__________|_____________|___________________________________|
|  |  'COMP'  |  nombre de variable (composante)  |
| NUAGE  |  'UPLE'  |  nombre de uplets (elements)  |
|__________|_____________|___________________________________|

## DIMN [Mathematiques Autres]
    Operateur DIMNOYAU

    ENTI1 = DIMNOYAU RIG1 ;

    Objet :

    L'operateur DIMNOYAU donne la dimension ENTI1 (type ENTIER)
du noyau de la matrice RIG1 (type RIGIDITE).

    Remarque :

    La matrice RIG1 doit avoir ete factorisee au prealable.

## DIRI [Mecanique Modele]
    Operateur DIRI

   EV1 TAB1 TAB2 = DIRI UNIT TMAX NB ....

        | 'EUROCODE'  RM  ROH  S  FCM  ;
        ....  |
        | 'BPEL'  RM  ROH  FC28 ;

    Objet :

    L'operateur DIRI identifie les parametres du modele de MAXWELL

    Commentaire :

   UNIT : unite de temps du calcul (type MOT) a choisir
        parmi SECONDE, JOUR (option par defaut), ou ANNEE

   TMAX : duree maximale du calcul (type FLOTTANT)

   NB : nombre de branches visqueuses du modele de Maxwell
        (type ENTIER). La branche elastique porte le numero 0

Si l'identification est faite a partir de la courbe de fluage
l'EUROCODE 2 (option par defaut), il faut donner en plus:

   RM : rayon moyen de la piece en metres (type FLOTTANT)

   ROH : pourcentage d'humidite (0.<roh<100.) (type FLOTTANT)

   S : coefficient caracteristique de la nature du ciment
        (type FLOTTANT)

   FCM : resistance moyenne du beton en compression, exprimee
        en MPa (type FLOTTANT)

Si l'identification est faite a partir de la courbe de fluage
du BPEL, il faut donner en plus:

   RM : rayon moyen de la piece en metres (type FLOTTANT)

   ROH : pourcentage d'humidite (0.<roh<100.) (type FLOTTANT)

   FC28 : resistance moyenne du beton en compression a 28 jours,
        exprimee en MPa (type FLOTTANT)

   EV1 : Module d'Young (exprime en Pa) du materiau fonction
        du temps (exprime en unite de temps donnee dans UNIT)
        (type EVOLUTIO)

   TAB1 : table indicee par des entiers et contenant pour chaque
        branche de la chaine, l'inverse du temps de relaxation
        dans l'unite inverse de l'unite de temps donnee dans UNIT

   TAB2 : table indicee par des entiers et contenant pour chaque
        branche de la chaine, le module (exprime en Pa) en
        fonction du temps (exprime dans l'unite de temps donnee
        dans UNIT)

## DIST [Mathematiques Autres]
   Operateur DIST

   FLOT1 = 'DIST' POIN1 POIN2 ;

   Objet :

   L'operateur DIST calcule la distance euclidienne FLOT1 (type
FLOTTANT) entre les deux points POIN1 et POIN2 (type POINT).

## DIVU [—]
    Opérateur DIVU

    CHP2 = DIVU MODE1 CHP1 CHEL1 ;

    Objet :

    L'opérateur DIVU calcul la divergence du champ de vitesse en
chaque élément. Ce champ est calculé à partir des débits aux faces
dans le cadre de la résolution des équations de DARCY par une méthode
d'éléments finis mixtes hybrides.

    Commentaire :

       MODE1 : Objet modèle (type MMODEL) décrivant la formulation
        utilisée. On attend une formulation DARCY (cf. MODE).

       CHP1 : Objet de type CHPOINT contenant le débit à travers
        chaque face. Le support géométrique de ce champ est
        le MAILLAGE des points FACE . Le nom de
        la composante du CHPOINT est FLUX (cf. HDEB).

       CHEL1 : Objet de type MCHAML contenant pour chaque élément le
        sens de la normale à chaque face (cf. KNRF).

       CHP2 : Objet résultat de type CHPOINT contenant la divergence
        du champ de vitesse pour chaque élément. Le support
        géométrique de ce champ est le MAILLAGE des points
        CENTRE. Le nom de la composante du CHPOINT est SCAL.

## DMMU [Mathematiques Autres]
 Operateur DMMU
 -------------- DMTD

CHP3 = 'DMMU' TAB1 RIG1 CHP1 (CHP2) ;

 Objet:
Cet operateur est utilise dans le cadre d'une formulation
elements finis mixtes hybrides.
Soit D la matrice divergence, pour un element.
D est une matrice ligne dont tous les termes sont 1.
Soit M une matrice elementaire de diffusion.
Soit U la matrice elementaire de convection.
Soit B la matrice de correspondance entre les numeros de face
 locaux et globaux.
Cet operateur va calculer pour chaque element le produit:
        -1 t -1 t
        D (M -U) B CHP1 ou D M B CHP1

Commentaires:

TAB1 : Objet de type TABLE et de sous type DOMAINE contenant
        les maillages et les connectivites.(cf DOMA)

RIG1 : Objet rigidite de sous type DARCY contenant les
        matrices elementaires inverses pour les elements
        hybrides . Cet objet rigidite est le resultat de MHYB .

CHP1 : Objet de type CHPOINT, dont le support geometrique est
        le maillage TAB1.FACE.

CHP2 : Objet de type CHPOINT contenant le flux a travers chaque
        face de la vitesse. Le support geometrique de ce champ est
        TAB1.FACE . Le nom de la composante de ce CHPOINT est FLUX.
        A defaut, on ne tient pas compte de la vitesse.

CHP3 : Objet de type CHPOINT dont le support geometrique est
        le maillage TAB1.CENTRE, les noms des composantes
        sont ceux de CHP2

## DMTD [Mathematiques Autres]
 Operateur DMTD
 --------------- DMMU

 CHP1 = 'DMTD' MODL1 RIG1 ;

 Objet :
 Cet operateur est utilise dans le cadre d'une formulation
 elements finis mixtes hybrides.
 Soit D la matrice divergence, pour un element.
 D est une matrice ligne dont tous les termes sont 1.
 Soit M une matrice elementaire de diffusion.
 Cet operateur va calculer pour chaque element le terme:
        -1 t
        D M D
 Ce qui se traduit par la somme des termes de chaque matrice de
 Darcy elementaire affectee au centre de chaque element

Commentaires :

 MODL1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

 RIG1 : Objet rigidite de sous type DARCY contenant les
        matrices elementaires inverses pour les elements
        hybrides . Cet objet rigidite est le resultat de MHYB .

 CHP1 : Objet de type CHPOINT ayant une composante dont le nom est
        SCAL. Son support geometrique est le maillage CENTRE.

## DOMA [Fluides Modele]
 Operateur DOMA

 RES = DOMA MOD1 MOT ;

 Objet : Cet operateur permet de restituer les informations
 _____ crees dans la table de preconditionnement du modele
        'NAVIER_STOKES' ou 'EULER'

 Commentaires :

 MOD1 : Objet de type MMODEL 'NAVIER_STOKES' ou 'EULER'
 MOT : Objet de type MOT a choisir dans la liste ci-dessous.

 RES : objet resultat

        Objet restitue
   Mot cle Type Commentaires
   MAILLAGE MAILLAGE Maillage de base pour la
        discretisation
   QUAF MAILLAGE Maillage de QUAF ayant servi
        a construire le modele
   MACRO MAILLAGE (Discretisation MACRO)
        Maillage MACRO

   SOMMET MAILLAGE Support geometrique (SPG)
        des points SOMMET
        (DDLs de base de l'element)

   CENTRE MAILLAGE SPG des points CENTRE

   FACE MAILLAGE SPG des points FACE

   CENTREP1 MAILLAGE SPG des points CENTREP1
        (pression non conforme P1)

   CENTREP0 MAILLAGE SPG des points CENTREP0
        (pression non conforme P0)

   MSOMMET MAILLAGE SPG des points sommets stricts
        i.e. sans les milieux des aretes
        ni les faces ni la bulle.
        (pression P1 ou Q1 conforme)

   FACEL MAILLAGE connectivites (SEG3)
        ELEMENT->FACE->ELEMENT

   FACEL2 MAILLAGE idem precedent partitionne
        les SEG2 correspondent aux
        faces frontieres
   FACEP MAILLAGE connectivites FACE->SOMMET
        (de la face)
   ELTFA MAILLAGE connectivites ELEMENT->FACE

   MMAIL MAILLAGE connectivites correspondantes
        aux MSOMMET

   ENVELOPP MAILLAGE connectivites QUAF orientees
        de l'enveloppe (resp contour)

   MAILFACE MAILLAGE Maillage contenant les faces
        du maillage de QUAF ayant
        servi a construire le modele

   ARETE MAILLAGE Maillage contenant les aretes
        du maillage de QUAF ayant
        servi a construire le modele

Les mots cles ci-dessous donnent des informations geometriques
 stockees sous forme de CHPOINT

   VOLUME CHPOINT SCAL CENTRE contenant le volume des elements
   DIAMAX CHPOINT SCAL CENTRE contenant le diametre max
   DIAMIN CHPOINT SCAL CENTRE contenant le diametre min
   NORMALEV CHPOINT VECT SOMMET contenant les composantes de la
        normale aux sommets pour l'ENVELOPPE
   NORMALE CHPOINT VECT FACE contenant les composantes de la
        normale associee aux faces des
        elements
   SURFACE CHPOINT SCAL FACE contenant la surface des faces
   ORIENTAT CHAMELEM contenant l'orientation des faces d'un
        element par rapport aux normales definis precedemment.

   XXDIAGSI CHPOINT SCAL SOMMET matrice masse diagonale pour les
        points SOMMET.

   XXVOLUM CHPOINT SCAL CENTRE matrice masse diagonale pour les
        points CENTRE.

   XXCTREP1 CHPOINT SCAL CENTRE matrice masse diagonale pour les
        points CENTREP1.

   XXCTREP0 CHPOINT SCAL CENTRE matrice masse diagonale pour les
        points CENTREP0.

   XXMSOMME CHPOINT SCAL CENTRE matrice masse diagonale pour les
        points MSOMMET.

  Les valeurs de la matrice masse diagonale donnent le Volume d'un
  element entourant un point. La somme de ce CHPOINT donne le volume
  du domaine. Ce CHPOINT eleve a la puissance 1/IDIM donne l'echelle
  de longueur moyenne des elements entourant un point.

l'instruction :
TAB = DOMA MOD1 'TABLE' ;
permet de recuperer le contenu de la table de
preconditionnement dans l'objet TAB de type TABLE.

CAS MODELE 'EULER'.

Dans le cas du modele 'EULER', il faux d'abord creer la table de
connectivites, i.e. :

TAB1 = 'DOMA' MMODE 'VF' ;

ou

TAB1 est la table des connectivites
MMODE est le modele EULER.

Attention: dans ce cas particulier l'operateur DOMA cree les points
centres des faces et les points centres des elements.

## DONCHI1 [Multi-physique Multi-physique] (proc)
Methode DONCHI1
--------------- OBJE LIESPECE

 OBJ1 = OBJET DONCHI1 ;

    Objet

 La methode DONCHI1 permet de creer un objet de type objet et de
 CLASSE DONCHI1. Un tel objet contient toutes les donnees de CHI1.
 Cette methode permet de tester la coherence des donnees lors de
 l'ecriture.

    Commentaires

    Les methodes associees a DONCHI1 sont

   GIDEN GCHXMX GBDD GCLIM GNVCOMP
   GNVESP GNVSOSO GECHANGE GTEMPERA ACCES

   GIDEN Charge le contenu de l'indice IDEN, un LISTENTI contenant
        les identifiants (dans la base de donnees), des
        composants chimiques a utiliser.
        appel: OBJ1%GIDEN LENT1 ;

   GCHXMX Charge le contenu de l'indice CHXMX, un LISTENTI contenant
        les identifiants des mineraux a retenir. A defaut on
        conserve tous les mineraux dont les composants sont
        utilises.
        appel: OBJ1%GCHXMX LENT1 ;

   GBDD Charge le contenu de l'indice BDD, un mot servant a
        preciser le format de la base de donnees. 'STRASBG' ou
        'MINEQL' . L'option par defaut est 'MINEQL'.
        'MINEQL' correspond a la base de donnees standard de Mineql.
        'STRASBG' correspond a la base de donnees issue de Kindis.
        Les formats sont decrits dans le rapport DMT/94/597.
        appel: OBJ1%GBDD MOT1 ;

   GCLIM Charge le contenu de l'indice CLIM, on doit donner un
        mot ( TYP3 , COMP3, TYP4, TYP5, TYP6 ) et un LISTENTI.

        appel: OBJ1%GCLIM MOT1 LENT1 ;
        -----------------------------------------------------------|
        Mot  |  LISTENTI  |
        -----------------------------------------------------------|
        TYP3 | identifiants des especes dont on veut imposer l'  |
        | activite  |
        -----------------------------------------------------------|
        COMP3| pour chacune des especes de TYP3 l'identifiant du  |
        | composant immobile ou 0. Si TYP3 ne contient que des|
        | especes simples cette donnee est inutile.  |
        -----------------------------------------------------------|
        TYP4 |  identifiants des especes precipitees.  |
        -----------------------------------------------------------|
        TYP5 | identifiants des especes en solution, pouvant etre  |
        | precipites.  |
        -----------------------------------------------------------|
        TYP6 | identifiants des especes non prises en compte.  |
        -----------------------------------------------------------|

   GNVCOMP Charge le contenu de l'indice NVCOMP, un nombre et le
        nom d'un objet de CLASSE LINVCOMP ( cf LINVCOMP)
        appel: OBJ1%GNVCOMP num1 OBJ2 ;

   GNVESP Charge le contenu de l'indice NVESP, un nombre et le
        nom d'un objet de CLASSE LIESPECE ( cf LIESPECE)
        appel: OBJ1%GNVESP num1 OBJ2 ;

   GNVSOSO Charge le contenu de l'indice NVSOSO, un nombre et le
        nom d'un objet de CLASSE LIRSOSO ( cf LIRSOSO)
        appel: OBJ1%GNVSOSO num1 OBJ2 ;

   GECHANGE Charge le contenu de l'indice ECHANGE, un LISTENTI.
        contenant les identifiants des sites de surface
        par echange ionique.
        appel: OBJ1%GECHANGE LENT1 ;

   GTEMPERA Charge le contenu de l'indice TEMPERATURE, un mot 'OUI'
        'NON' ou entier (1 ou 2).
        'NON' on ne tient pas compte de la temperature. C'est
        l'option par defaut.
        - Cas de la base STRASBG.
        Si 'OUI' on prendra en compte les effets thermiques sur
        le logk, par interpolation de donnees tabulees.
        - Cas de la base MINEQL.
        1 ou 'OUI' on utilise la premiere approximation d'Ulich
        K(T)=K0+f(H(T)-H(T0))

        2 on utilise la deuxieme approximation d'Ulich
        K(T)=K0+f((H(T)-H(T0)),(Cp(T)-Cp(T0)))

        appel: OBJ1%GTEMPERA MOT1 ;

   ACCES permet d'acceder au contenu des indices charges par les
        methodes precedentes.

        appel: pour GIDEN GCHXMX GBDD GECHANGE GTEMPERA
        LENT1= DONCHI1%ACCESS METH1 ;

        pour GNVCOMP GNVESP GNVSOSO on peut preciser
        l'indice.
        LENT1= DONCHI1%ACCESS METH1 num1 ;
        ou TAB1 =DONCHI1%ACCESS METH1 ;

        pour GCLIM on peut preciser les memes mots qu'en
        entree .
        LENT1= DONCHI1%ACCESS METH1 MOT1 ;
        ou LENT1= DONCHI1%ACCESS METH1 ;

## DONCHI2 [Multi-physique Multi-physique] (proc)
Methode DONCHI2
--------------- OBJE

 OBJ1 = OBJET DONCHI2 ;

    Objet

 La methode DONCHI2 permet de creer un objet de type objet et de
 CLASSE DONCHI2. Un tel objet contient les donnees chimiques
 de CHI2. Cette methode permet de tester la coherence des donnees
 lors de l'ecriture.

    Commentaires

    Les methodes associees a DONCHI2 sont

 GLOGC GTOT GFIONI GNTY4 GTEMPE GCLIM ACCES

  GLOGC charge le contenu de l'indice LOGC.
        C' est un objet de type CHPOIN qui possede une composante
        par composant chimique. Pour chaque composant chimique il
        contiendra le log de l'estimation de l'espece simple
        associee. Le nom de ces composantes est un mot de 4
        caracteres, forme par X suivi eventuellement de 0 ou 00 et
        du numero identifiant le composant chimique.
        Appel : OBJ1%GLOGC CHPO1 ;

  GTOT charge le contenu de l'indice TOT.
        C' est un objet de type CHPOIN qui possede une composante
        par composant chimique. Pour chaque composant chimique il
        contiendra la concentration totale (ou analytique) ( en
        solution + mineraux). Le nom de ces composantes est un mot
        de 4 caracteres, forme par X suivi eventuellement de 0 ou
        00 et du numero identifiant le composant chimique.
        Appel : OBJ1%GTOT CHPO1 ;

  GFIONI charge le contenu de l'indice FIONI.
        Objet de type CHPOIN ayant une composante scalaire, et
        contenant une estimation de la force ionique en chaque
        point du maillage.
        Appel : OBJ1%GFIONI CHPO1 ;

  GNTY4 charge le contenu de l'indice NTY4.
        Objet de type CHPOIN ayant une composante pour chaque
        espece de precipite potentiel. En chaque point du maillage
        on indiquera si le mineral est precipite ( =1) ou non( =0).
        Appel : OBJ1%GNTY4 CHPO1 ;

  GTEMPE charge le contenu de l'indice TEMPE.
        Objet de type CHPOIN contenant la temperature.
        Appel : OBJ1%GTEMPE CHPO1 ;

  GCLIM charge le contenu de l'indice CLIM.
        Valeur de l'activite imposee des especes de type 3.
        Objet de type CHPOIN ayant une composante pour chaque
        espece dont l'activite est imposee.Les noms des composantes
        sont ceux figurant dans la liste TAB1.IDEN.NOMTYP3.
        ( TAB1 etant la table issue de CHI1)
        Appel : OBJ1%GCLIM CHPO1 ;

  ACCES permet d'acceder au contenu des indices charges par les
        metodes precedentes.
        Appel : CHPO1 = OBJ1%ACCES METH1 ;

## DREXUS [Mecanique Resolution] (proc)
    Procedure DREXUS

  'DREXUS' ETAB ;

  en entree :

   ETAB . 'MODELE' : objet modele
   ETAB . 'GRANDES_DEFORMATIONS' : option : logique
   ETAB . 'CARACTERISTIQUES' : chamelem de caracteristiques
   ETAB . 'LIAISONS' : conditions aux limites en depl
   ETAB . 'CHARGEMENT' : objet chargement
   ETAB . 'VITESSE_INITIALE' : champ par point
   ETAB . 'TEMPS_SORTIE' : liste de reels des temps a stocker
   ETAB . 'FREQUENCE_SORTIE' : frequence de sortie (entier)
   ETAB . 'NPASMAX' : nombre maximal de pas de temps
   ETAB . 'IMPACT' . 'MAITRE' : ligne maitre
   ETAB . 'IMPACT' . 'ESCLAVE' : ligne esclave
   ETAB . 'IMPACT' . 'NEZ' : nez esclave poi1 (plat,cone,hemi)
   ETAB . 'IMPACT' . 'LARGEUR' : largeur ou rayon du nez
   ETAB . 'IMPACT' . 'ANGLE' : angle / vecteur (nez conique)
   ETAB . 'IMPACT' . 'VECTEUR' : vecteur definissant l'axe (avec nez)
   ETAB . 'IMPACT' . 'MASSE' : masse du poi1
   ETAB . 'TEMPS_INITIAL' : option : temps initial (0. par defaut)
   ETAB . 'COEFF_STABILITE' : option : coeff multi pdt (0.5 par def)
   ETAB . 'PAS_TEMPS' : option : pas de temps (reel)
   ETAB . 'FREQ_MENAGE' : option : frequence de menage (50 par def)
   ETAB . 'AMORTISSEMENT' : option : matrice d'amortissement

  en sortie :

   ETAB . 'NPAS' . N : No du pas (entier)
   ETAB . 'TEMPS' . N : Instant (reel)
   ETAB . 'DEPLACEMENTS' . N : champoint deplacements
   ETAB . 'VITESSES' . N : champoint vitesse
   ETAB . 'ACCELERATIONS' . N : champoint accelerations
   ETAB . 'FORCES_EXTERIEURES' . N : champoint forces externes
   ETAB . 'CONTRAINTES' . N : chamelem de contraintes
   ETAB . 'VARIABLES_INTERNES' . N : chamelem des variables
        internes
   ETAB . 'DEFORMATIONS_INELASTIQUE' . N : chamelem des deformations
        inelastiques

    Objet :

La procedure DREXUS permet de realiser un calcul mecanique dynamique,
en formulation Lagrangienne, avec un algorithme explicite dit des
"differences centrees".

  -Le comportement du materiau peut etre non lineaire.
  -Il est possible de prendre en compte les grands deplacements.
   On utilise dans ce cas un modele hypoelastique, associe a la
   derivee de Truesdell des contraintes de Cauchy.
  -Il est possible de modeliser des impact (en 2D). Il faut alors
   definir deux lignes de contact: une maitre et une esclave.
   (cf 'IMPO' 'IMPA' ).
  -Pour imposer des deplacement non nuls il faut fournir dans le
   chargement la derivee seconde du second membre de
   la condition sur le deplacement.

Le calcul est effectue avec un pas de temps constant jusqu'a atteindre
le nombre maximal de pas specifie ou bien le temps final des temps de
sortie. Les resultats sont stockes pour tous les temps specifies dans
la liste des temps de sortie.

L'algorithme d'integration en temps se resume comme suit

 0- Deplacement  Un  |
    Vitesse  Vn  |-  connus a l'instant n
    Acceleration An  |

 1- Calcul du deplacement au temps n+1/2

     Un+1 = Un + dt.Vn + (dt.dt/2).An

 2- Calcul des forces externes et internes au temps (n+1)

     Fn+1 = Fn+1(ext) - div(Sigma(n+1)) - Famortissement(Vn+1/2)

 3- Calcul des accelerations au temps avec prise en compte des
    conditions aux limites et des impacts.

    M.An+1 = Fn+1

 4- Calcul des vitesses au temps n+1

    Vn+1 = Vn + dt/2.(An + An+1)

   Commentaire :

La reprise d'un calcul est automatique a partir de la table sortie
du precedent appel a DREXUS.

en entree on utilise une table qui sert a definir les options et
les parametres du calcul. Les indices de l'objet TAB1 sont des mots
(a ecrire en toutes lettres, et en majuscules s'ils sont mis entre
cotes) dont voici la liste :

 'MODELE' : objet modele qui decrit la modelisation
        loi de comportement et element fini.

 'CARACTERISTIQUES' : chamelem de caracteristiques associe au
        modele

 'LIAISONS' : conditions aux limites en deplacement
        stockees dans une matrice

 'CHARGEMENT' : objet de type chargement qui donne une
        description temporelle du chargement

 'VITESSE_INITIALE' : champ par point de vitesse initiale. Le nom
        des composantes est identique aux
        deplacements.

 'GRANDES_DEFORMATIONS' : logique (vrai ou faux) indiquant si l'on
        les grandes deformations seront modelisees

 'TEMPS_SORTIE' : liste de reels des temps a stocker dans la
        table de sortie

 'FREQUENCE_SORTIE' : frequence des enregistrements dans la table
        de sortie (entier)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DROI [Maillage Lignes]
    Operateur DROIT (alias D)

    GEO1 = DROIT (N1) POIN1 POIN2 ('DINI' DENS1) ('DFIN' DENS2) ;

    Objet :

    L'operateur DROIT construit le segment de droite joignant les deux
points POIN1 et POIN2.

    Commentaire :

    POIN1, POIN2 : points delimitant le segment de droite (type POINT)

    DENS1, DENS2 :densites associees aux points commençant et finissant
        le segment de droite (type FLOTTANT)

    N1 : nombre d'elements generes (type ENTIER)

    GEO1 : segment de droite (type MAILLAGE)

    Remarque 1 :

    Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
    Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.
    Si N1 est negatif, N1 elements seront engendres et leurs tailles
seront calculees en tenant compte des densites des extremites.

    Remarque 2 :

    Si les densites associees aux points POIN1 et POIN2 ne sont pas
correctes, il est possible de les surcharger. Pour le premier point, il
faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour le
deuxieme point, derriere le mot-cle 'DFIN'.

    Remarque 3 :

    Si une ligne LIG1 est donnee a la place du point POIN1 (ou POIN2),
cette ligne est prolongee jusqu'au point POIN2 (elle commence au point
POIN1).
    Si le point POIN2 n'est pas donne, la premiere extremite de la ligne
LIG1 est prise en compte; ce qui permet de fermer celle-ci.

## DSPR [Mathematiques Traitement]
    Operateur DSPR

    EVOL1 = DSPR N1 EVOL2 ('FMIN' FLOT1) ('FMAX' FLOT2) (COUL1) ;

    Objet :

    L'operateur DSPR construit la courbe de densite spectrale de
puissance d'un signal.

    Commentaire :

  N1 : on utilise, pour la transformee de FOURIER rapide,
        un nombre de points egal a 2**N1 (type ENTIER).
        ( Si le signal traite est plus long, on le tronque; s'il est
        plus court, on le complete par des 0. )

  EVOL2 : objet contenant le signal a etudier (type EVOLUTION); les
        abscisses doivent etre a pas constant, les valeurs du signal
        etant les ordonnees. L'objet doit contenir une seule courbe.

 'FMIN' : mot-cle suivi de :
  FLOT1 : frequence minimale visualisee (type FLOTTANT)
        elle sera positive (0 par defaut).

 'FMAX' : mot-cle suivi de :
  FLOT2 : frequence maximale visualisee (type FLOTTANT)
        elle sera inferieure a 1/(2*DT), DT etant le pas de temps
        du signal d'entree.
        (Valeur par defaut = valeur maximale calculee)

  COUL1 : couleur choisie (blanc par defaut) (type MOT)

  EVOL1 : objet contenant le spectre (type EVOLUTION).

## DUDW [Fluides Resolution]
    Operateur DUDW
    -------------- KMBT KMAB

    SYNTAXE - EQEX Cf operateur EQEX

    'OPER' 'DUDW' eps 'INCO' UN :

    OBJET :

 Cet operateur discretise le terme de penalisation de l'equation de
continuite pour l'equation de quantite de mouvement:

   Commentaires :

   eps : est le coefficient de penalisation
        FLOTTANT ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice MOT.

   Remarque :

1/ L'incompressibilite n'est realisee que si eps est suffisemment petit
  mais pas trop, sinon les erreurs numeriques deviennent importantes et
  a la limite on peut meme obtenir une division par zero.

  (avec LAPN) on peut prendre 1.e-10 < (eps mu / L**2 ) < 1.e-6
        = =
2/ Cet operateur n'est pas a utiliser en 3D,il conduit a des tailles de
  systeme lineaire prohibitives.

   Options : (EQEX)

   Formulation Implicite OPTION IMPL
   Pression non conforme P0 OPTION CENTRE
   Pression non conforme P1 ou iso P1 OPTION CENTREP1

## DUPONT2 [Thermique Resolution] (proc)
        D U P O N T 2

RESOLUTION D'UN PROBLEME DE THERMIQUE TRANSITOIRE NON-LINEAIRE
METHODE A DEUX PAS DE TEMPS

PROCEDURE APPELE PAR PASAPAS : STAB = DUPONT2 ETAB

ETAB, TABLE CONTENANT EN ENTREE :

INDICE 'SOUSTYPE' THERMIQUE
INDICE 'INITIAL(0)' CHAMP DE TEMPERATURE INITIAL AU PAS 0
INDICE 'INITIAL(1)' CHAMP DE TEMPERATURE INITIAL AU PAS 1
        ( LA DONNEE DE CE CHAMP EST FACULTATIVE )
INDICE 'VIEUXPAS' PAS DE TEMPS ENTRE INITIAL(0) ET INITIAL(1)
        (DONNEE INDISPENSABLE SI EXISTE INITIAL(1))
INDICE 'RAYONNEMENT' LOGIQUE VALANT VRAI POUR UNE CONDITION
        DE RAYONNEMENT
INDICE 'EMISSIVITE' MCHAML DECRIVANT LES FACTEURS D'EMISSIVITE
        LES FACTEURS D'EMISSIVITE
INDICE 'CELSIUS' LOGIQUE VALANT VRAI SI L'UNITE EST LE
        DEGRE CELSIUS (CAPITAL SI RAYONNEMENT)
INDICE 'MOD_THE' OBJET MODELE THERMIQUE
INDICE 'MOD_CON' OBJET MODELE CONVECTION
INDICE 'BLOCAGES_THERMIQUES' MATRICE DE BLOCAGE
INDICE 'MAT_THE' OBJET MATERIAU THERMIQUE.
        CE CHAMP PEUT AVOIR DES COMPOSANTES DE
        TYPE FLOTTANT OU EVOLUTION
INDICE 'MAT_CON' OBJET MATERIAU CONVECTION
INDICE 'CHARGEMENT' CHARGEMENT DECRIVANT LES :
        VALEURS DES VARIABLES EXTERNES (EX: TE,
        FLUX,TEMPERATURES IMPOSEES ,...)
        VALEURS DES VARIABLES EXTERNES
INDICE 'PHASE' TABLE TAB1 POUR L'OPERATEUR CAPACITE
INDICE 'TEMPS0' TEMPS INITIAL (CORRESPOND A INITAL(0))
INDICE 'PAS' VALEUR DU PAS DE TEMPS
INDICE 'TEM_CALC' LISTREEL : TEMPS DES RESULTATS A CALCULER
INDICE 'RELAXATION_DUPONT' VALEUR DU COEFFICIENT DE RELAXATION
        (VALEUR PAR DEFAUT 0.25)
INDICE 'SOUS-RELAXATION' VALEUR DU COEFF. DE SOUS-RELAXATION
        (VALEUR PAR DEFAUT 0.5)
INDICE PROJECTION LOGIQUE VALANT VRAI SI COUPLAGE ET SI LE
        MAILLAGE DE LA MECANIQUE ET DE LA THERMIQUE
        EST DIFFERENT

STAB, TABLE CONTENANT EN SORTIE

INDICE INITIAL(2) DERNIER CHAMP DE TEMPERATURE CALCULE
INDICE ERREUR DRAPEAU D'ERREUR
INDICE RELAXATION_DUPONT VALEUR DU COEFFICIENT DE RELAXATION
        INITIALISE (0.25) SI BESOIN EST
RAYONNEMENT INFORMATIONS SUR LE RAYONNEMENT
        EVENTUELLEMENT REACTUALISEES

## DYNAMIC [Mecanique Dynamique] (proc)
   Procedure DYNAMIC

   TAB2 = DYNAMIC TAB1 ;

   Objet :

   Cette procedure permet d'effectuer un calcul dynamique pas a pas.

   Elle peut utiliser les algorithmes :
   - Newmark centre (schema de l'acceleration moyenne) (par defaut)
   - HHT
   - alpha-generalise

   Les arguments d'entree et de sortie de la procedure sont des tables
   definies ci-apres.

   Commentaire :

   | TAB1 : Objet de type TABLE contenant les donnes d'ENTREE |

     DONNEES DU PROBLEME
     ###################

     TAB1 . 'DEPL' : deplacement initial [CHPOINT]
     TAB1 . 'VITE' : vitesse initiale [CHPOINT]
     TAB1 . 'CHAR' : chargement [CHARGEME]
     TAB1 . 'RIGI' : raideur [RIGIDITE]
     TAB1 . 'MASS' : masse [RIGIDITE]
   ( TAB1 . 'AMOR' ) : amortissement [RIGIDITE]

     TEMPS DE CALCUL
     ###############

     TAB1 . 'TEMPS_CALCULES' : [LISTREEL] strictement croissant
        contenant tous les instants de
        calcul (dont l'instant initial)

     PARAMETRES DE SAUVEGARDE
     ########################

     SORTIE GIBIANE

   | TAB1 . 'PAS_SAUVES'  : [ENTIER] indiquant la cadence de la
   |  sauvegarde ou [MOT] valant 'TOUS' ou
OU |  'FINAL' (par defaut, on conserve 1
   |  pas de temps sur 4)
   | TAB1 . 'TEMPS_SAUVES'  : [LISTREEL] des instants a sauver

   ( TAB1 . 'MAILLAGE_SAUVE' ) : [MAILLAGE] pouvant etre fourni pour
        limiter le support geometrique des
        donnees sauvegardees

   ( TAB1 . 'SAUV' ) : VRAI si l'on souhaite SAUVER a chaque pas
        de maniere incrementale dans le fichier
        a definir prealablement par la commande :
        "OPTI 'SAUV' nomfic ;"

   ( TAB1 . 'ECON' ) : VRAI si l'on souhaite FANTomiser les resultats
        sauvegardes sur disque

     SORTIE VTK (PARAVIEW) => OPTIONNELLE

   | TAB1 . 'PAS_SAUVES_VTK'  : idem ci-dessus
OU | TAB1 . 'TEMPS_SAUVES_VTK'  (par defaut : aucune sortie VTK)

     TAB1 . 'MAILLAGE_VTK' : objet [MAILLAGE] ou [TABLE] passe a
        l'operateur SORT 'VTK' definissant la
        ou les geometries a sauvegarder
        (seulement si l'un des 2 indices
        ci-dessus est present)

   ( TAB1 . 'FICHIER_VTK' ) : [MOT] indiquant l'emplacement ou
        seront ecrits les fichiers VTK
        Beaucoup de fichiers peuvent etre
        crees => on recommande de les placer
        dans un sous-repertoire (par defaut,
        tout est dans le dossier courant)

     SORTIE CSV (TABLEUR) => OPTIONNELLE

   | TAB1 . 'PAS_SAUVES_CSV'  : idem ci-dessus
OU | TAB1 . 'TEMPS_SAUVES_CSV'  (par defaut : aucune sortie CSV)

     TAB1 . 'MAILLAGE_CSV' : objet [MAILLAGE] contenant les noeuds
        ou seront enregistrees les donnees
        (seulement si l'un des 2 indices
        ci-dessus est present)

   ( TAB1 . 'COMPOSANTES_CSV' ): [LISTMOTS] des composantes a conserver
        (par defaut, on conserve toutes les
        composantes disponibles)

   ( TAB1 . 'FICHIER_CSV' ) : [MOT] indiquant l'emplacement ou
        sera cree le fichier CSV (par defaut,
        on n'ecrit rien sur le disque)

     APPEL A DES PROCEDURES SPECIFIQUES
     ##################################

   ( TAB1 . 'CHARMECA' ) : VRAI si appelle la procedure CHARMECA
        definie par ailleurs par l'utilisateur et
        qui renvoie une table TCHAR avec un ou
        plusieurs indices parmi :

        'ADDI_MATRICE' => ajout a l'operateur
        'ADDI_SECOND' => ajout au second membre
        (composantes FLX)
        'ADDI_KNL' => ajout a la raideur
        'ADDI_CNL' => ajout a l'amortissement
        'ADDI_FNL' => ajout au second membre
        (composantes hors FLX)

   ( TAB1 . 'VITEUNIL' ) : correction des vitesses lors d'un impact
        (VRAI par defaut, seulement possible avec
        le schema de Newmark acceleration moyenne)

     SCHEMA D'INTEGRATION TEMPORELLE => OPTIONNEL
     ###############################

   | TAB1 . 'ALPHA_F'  : active le schema HHT et donne son parametre
   |  \alpha
OU |
   | TAB1 . 'RHO_INF'  : active le schema alpha-generalise et donne
   |  son parametre \rho^{\intfy} (rayon spectral
   |  a l'infini)

   | TAB2 : Objet de type TABLE (aussi stocke dans TAB1.'RESULTATS') |
   |  contenant les objets GIBIANE sauvegardes a chaque pas de |
   |  temps demande  |

     TAB2 . I . 'TEMP' : temps [FLOTTANT]
     TAB2 . I . 'DEPL' : deplacement [CHPOINT]
     TAB2 . I . 'VITE' : vitesse [CHPOINT]
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DYNAMOD2 [Mecanique Dynamique] (proc)
 Procedure DYNAMOD2
 ------------------ DYNAMODE

 Objet :

Cette procedure est utilisee par la procedure DYNAMODE.

## DYNAMOD3 [Mecanique Dynamique] (proc)
Procedure DYNAMOD3
------------------ DYNAMODE

Objet :

Cette procedure est utilisee par la procedure DYNAMODE.

## DYNAMODE [Mecanique Dynamique] (proc)
    Procedure DYNAMODE

    TAB1 = DYNAMODE MOT1 LREEL1 BAS1 (LREEL2) ('BLOC' N1) ...
        ... ('DEPL' CHPO1) ('VITE' CHPO2) ('SAUV') ...
        ... ('SUIT' SOL1) ...

        ... ( 'CHAR' TAB2 )
        ( 'SEIS' TAB3 )
        ( 'RECO' TAB4 )
        ( 'MAXI' TAB5 )
        ( 'EVOL' TAB6 ) ;

    Objet :

    Cette procedure calcule la reponse dynamique d'une structure selon
le schema suivant :

     - projection sur la base modale.
     - integration explicite en temps.
     - recombinaison modale de la reponse.

    Commentaire :

    MOT1 : nom de l'operateur de resolution : "DEVO" ou "PLEX"
        (type MOT)

    LREEL1 : liste des instants de calcul (type LISTREEL)

    BAS1 : base modale (type BASEMODA)

    en option :

    LREEL2 : liste des coefficients d'amortissement, en pourcentage,
        associes aux modes de la base (type LISTREEL)

    'BLOC' : mot-cle indiquant que l'on veut faire un calcul par bloc
        suivi de :
    N1 : nombre de blocs (type ENTIER)

    'DEPL' : mot-cle indiquant que l'on a des deplacements initiaux
        suivi de :
    CHPO1 : valeurs des deplacements initiaux (type CHPOINT)

    'VITE' : mot-cle indiquant que l'on a des vitesses initiales
        suivi de :
    CHPO2 : valeurs des vitesses initiales (type CHPOINT)

    'SAUV' : mot-cle indiquant que l'on veut une sauvegarde de la
        reponse modale a l'instant final.

    'SUIT' : mot-cle indiquant que l'on poursuit un calcul anterieur
        suivi de :
    SOL1 : condition initiale pour une reprise (type SOLUTION)

    'CHAR' : mot-cle indiquant que l'on veut creer un objet CHARGEME
        suivi de :
    TAB2 : objet (type TABLE) contenant autant de tables (N2) que de
        chargements.

        pour i variant de 1 a N2 on a :

        - TAB2 i 'CHARGEMENT' : chargement spatial et temporel de
        la structure (type CHARGEME)
        - TAB2 i 'STRUCTURE' : sous-structure oº doit s'appliquer
        le chargement (facultatif)
        (type STRUCTUR)
        - TAB2 i 'NUMERO' : numero de la sous-structure
        (facultatif) (type ENTIER)

    'SEIS' : mot-cle, indiquant que l'on veut creer un objet CHARGEME
        pour un calcul sismique, suivi de :
    TAB3 : objet (type TABLE) contenant autant de tables que de
        directions de seisme.

        pour i variant de 1 a 3 on a :

        - TAB3 i 'EVOLUTION' : la discretisation temporelle du
        seisme (type EVOLUTION)
        - TAB3 i 'COEFFICIENT' : coefficient multiplicatif applique
        au seisme (type FLOTTANT)
        - TAB3 i 'DIRECTION' : direction du seisme (UX, UY, UZ)
        (type MOT)

    'RECO' : mot-cle indiquant que l'on veut une recombinaison
        modale pour toute la structure a des instants donnes, suivi
        de :
    TAB4 : objet (type TABLE) contenant autant de tables (N2) que de
        demandes de recombinaisons

        pour i variant de 1 a N2 on a :

        - TAB4 i 'TYPE' : type demande (DEPL,ACCE,VITE,
        LIAI, CONT) (type MOT)
        - TAB4 i 'TEMPS' : temps oº l'on veut la recombinaison
        modale pour toute la structure
        (type FLOTTANT)
        - TAB4 i 'STRUCTURE' : sous-structure oº doit s'effectuer
        la recombinaison (facultatif)
        (type STRUCTUR)
        - TAB4 i 'NUMERO' : numero de la sous-structure
        (facultatif) (type ENTIER)

    'MAXI' : mot-cle indiquant que l'on demande le maximum en valeur
        absolue d'une composante au cours du temps apres une
        recombinaison modale, suivi de :
    TAB5 : objet (type TABLE) contenant autant de tables (N2) que de
        demandes de maxima

        pour i variant de 1 a N2 on a :

        - TAB5 i 'TYPE' : type du maximum demande (DEPL,
        ACCE, VITE, LIAI, CONT) (type MOT)
        - TAB5 i 'POINT' : points oº doit s'effectuer la
        recherche du maximum (type POINT
        - TAB5 i 'COMPOSANTE' : nom de la composante du point
        (type MOT)
        - TAB5 i 'STRUCTURE' : sous-structure oº doit s'effectuer
        la recombinaison (facultatif)
        (type STRUCTUR)
        - TAB5 i 'NUMERO' : numero de la sous-structure
        (facultatif) (type ENTIER)

    'EVOL' : mot-cle indiquant que l'on veut une recombinaison modale
        en quelques points en fonction du temps, suivi de :
    TAB6 : objet (type TABLE) contenant autant de tables (N2) que de
        demandes d'evolutions.

        pour i variant de 1 a N2 on a :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DYNC [Mecanique Dynamique]
   Operateur DYNC

CHAP{Objet}

     Calcul des branches de reponse d'un systeme mecanique en
     fonction de ses parametres.

     Plus precisement, une solution periodique du systeme d'equations
     differentielles :
        .. . .
       M q + C q + K q = f^ext(t) + f^nl(Q,Q,a)

     avec :

       M : matrice diagonale des masses generalisees
       C : matrice des amortissements modaux
       K : matrice diagonale des raideurs generalisees
       f^ext: vecteur des forces exterieures
       f^nl : vecteur des forces de non-lineaires (liaisons)
       q : vecteur des contributions modales
       a : parametre de continuation

     est calculee par la methode d'equilibrage harmonique (HBM).
     Ensuite, des branches de reponse sont construites pas a pas par
     l'algorithme de continuation par pseudo-longueur d'arc.
     A chaque pas, la stabilite des solutions calculees est evaluee et
     les bifurcations eventuelles sont detectees.
     Trois types de reponses sont prevues : reponse forcee, cycle limite
     d'un systeme autonome et calcul des modes non-lineaire de systemes
     non amorti.

CHAP{Syntaxe}

    TAB1 = DYNC TMOD TCHR TLIA TAMOR TINI TNUM NHBM NFFT;

    avec :

    TMOD : table representant une base modale ou un ensemble de
        bases modales (type TABLE).

    TCHR : table representant les forces libres appliquees dans le
        domaine frequentiel (type TABLE).
        Uniquement utile lors du calcul d'une reponse forcee.

    TLIA : table rassemblant les descriptions des liaisons (type
        TABLE).

    TAMOR : table representant la matrice des amortissements
        generalises (type TABLE). Par defaut, seule la partie
        diagonale de la matrice est consideree.
        Non prise en compte pour les modes non-lineaires.

    TINI : table donnant une approximation initiale (type TABLE).

    TNUM : table des parametres numeriques pour la continuation
        (type TABLE).

    NHBM : nombre d'harmoniques dans l'approximation (type ENTIER).

    NFFT : nombre de pas de temps d'evaluation pour l'AFT
        (type ENTIER).

    TAB1 : table contenant les resultats (type TABLE).

CHAP{Description des tables}

   Remarques :

   * Toutes les TABLES doivent etre sous-typees.
   * Dans toute la suite la base A represente la base modale dans
     laquelle les equations sont decouplees (composantes 'ALFA' ) ;
     et la base B represente la base des deplacements des noeuds
     (composantes 'UX' , 'UY' , ... ).

PART{TMOD : Base Modale}

   a/ Cas d'une base unique :
      TMOD : table issue de l'operateur VIBR telle que :
      TMOD.'SOUSTYPE' = MOT 'BASE_MODALE';
      TMOD.'MODES' : table contenant les modes 1 a n

   b/ Cas d'une base composee de plusieurs bases :
      TAB2.'SOUSTYPE' = MOT 'ENSEMBLE_DE_BASES';
      TAB2.I : table de base modale definie comme au a/
        avec I variant de 1 a n bases

PART{TCHR : Chargement}

      On considere un chargement harmonique et on specifie son contenu
      frequentiel.

      TCHR . 'SOUSTYPE' = MOT 'CHARGEMENT';
      TCHR . j = FextA (CHPOINT);

      * j : indice de la composante frequentielle ou s'applique le
        chargement avec : - j = 0 : terme constant
        - j > 0 : terme en cos(jwt)
        - j < 0 : terme en sin(jwt)
      * FextA : description spatiale (type CHPOINT) du chargement
        (projete sur base A)

      Exemple : chargement de 5. variant comme cos(+1*wt)
        applique selon FY en P2 :
        TMOD = VIBR 'IRAM' 1. NMODE Ks Ms ;
        Fext = MANU CHPO P2 'FY' 5. ;
        FextA = PJBA Fext TMOD;
        TCHR . +1 = FextA ;

PART{TLIA : Description des Liaisons}

      TLIA.'SOUSTYPE' = MOT 'LIAISON';
      TLIA.'LIAISON_A' : TABLE de sous-type LIAISON_A, definissant
        les liaisons sur base A
      TLIA.'LIAISON_B' : TABLE de sous-type LIAISON_B, definissant
        les liaisons sur base B

      Exemple :
        TLIA = TABLE 'LIAISON' ;
        TTLB = TABLE 'LIAISON_B' ;
        TLIA.'LIAISON_B' = TTLB ;
        TTLB.1 = TL1 ;
        TTLB.2 = TL2 ;

      TL1 et TL2 sont deux tables definissant des liaisons
      (voir paragraphe "DEFINITION DES LIAISONS" dans la notice de
      l'operateur DYNE).
      Dans la table qui regroupe les liaisons sur une base
      (TTLB dans l'exemple), les liaison doivent etre indicees par
      les entiers 1 a NL , ou NL est le nombre de ces liaisons.

PART{TAMOR : Amortissement}
[… notice tronquée ; texte complet dans l'archive PCW_24]

## DYNE [Mecanique Dynamique]
    Operateur DYNE
    ______________ PSMO RECO

CHAP{Objet}

    Calcul d'une reponse dynamique a l'aide d'algorithmes
    explicite : Fu-DeVogelaere, differences centrees,
    acceleration moyenne ou Fox-Goodwin.

    Il s'agit de calculer la solution du systeme d'equations :
        .. .
      M Q + C Q = F(Q,t) avec F(Q,t) = -K Q + Fl + Fe
        .
      Q(0) = Q0 et Q(0) = L0

    avec :

      M : matrice diagonale des masses generalisees
      C : matrice des amortissements modaux
      K : matrice diagonale des raideurs generalisees
      Fl : vecteur des forces de liaisons
      Fe : vecteur des forces exterieures
      Q : vecteur des contributions modales
      Q0 : vecteur des contributions modales initiales
      L0 : vecteur des vitesse modales initiales

CHAP{Syntaxes}
PART{Syntaxe 1}

    TAB1 = DYNE  |'DE_VOGELAERE'  | ...
        |'DIFFERENCES_CENTREES'|
        |'ACCELERATION_MOYENNE'|
        |'FOX_GOODWIN'  |

   ... | TAB2  | (TAB4) (TAB5) | TAB6  | N1 FLOT1 (N2) TAB8 ;
       | TAB3  |  | TAB7  |
        | TAB6 TAB7 |

    TAB2 : table representant une base modale ou un ensemble de
        bases modales (type TABLE).

    TAB3 : table reunissant les matrices de raideur et de masse
        generalisees (type TABLE). Seules les parties
        diagonales des matrices sont considerees.

    TAB4 : table representant la matrice des amortissements
        generalises (type TABLE). Par defaut, seule la partie
        diagonale de la matrice est consideree.

    TAB5 : table rassemblant les descriptions des liaisons (type
        TABLE).

    TAB6 : table representant l'evolution des forces libres
        appliquees (type TABLE).

    TAB7 : table donnant les conditions initiales (type TABLE).

    TAB8 : Table definissant les resultats que l'on veut dans la
        table de sortie TAB1 (type TABLE).

    N1 : Nombre de pas (type ENTIER).

    FLOT1 : Pas de temps (type FLOTTANT).

    N2 : Sortie tous les N2 pas de calcul (type ENTIER),
        par defaut N2 = 1 .

    TAB1 : Table contenant les resultats.

PART{Syntaxe 2}

    DYNE 'DE_VOGELAERE' TAB11 ;

    TAB11 : Table de soustype 'PASAPAS' (syntaxe 2 seulement)

CHAP{ DESCRIPTION DES TABLES }

  Remarques :

  * Toutes les TABLES doivent etre sous-typees.

  * Dans toute la suite la base A represente la base modale dans
    laquelle les equations sont decouplees (composantes 'ALFA' ) ;
    et la base B represente la base des deplacements des noeuds
    (composantes 'UX' , 'UY' , ... ) .

PART{TAB2 : Base Modale}

        a/ Cas d'une base unique :
        TAB2 : table issue de l'operateur VIBR telle que :
        TAB2.'SOUSTYPE' : 'BASE_MODALE'
        TAB2.'MODES' : table contenant les modes 1 a n

        Pour la prise en compte des pseudo-modes, on complete avec :
        TAB2.'PSEUDO_MODES' : table des pseudo-modes definis
        par l'operateur PSMO

        b/ Cas d'une base composee de plusieurs bases :
        TAB2.'SOUSTYPE' : 'ENSEMBLE_DE_BASES'
        TAB2.I : table de base modale definie comme au a/
        avec I variant de 1 a n bases

        c/ Pour la prise en compte des deplacements dus a la rotation
        des corps rigides il faut completer la table avec :
        TAB2.'MODES'.Irot.'CORPS_RIGIDE' = 'VRAI';
        TAB2.'MODES'.Irot.'CENTRE_DE_GRAVITE'= G;
        Irot numero du "mode" de rotation, G de type point.
        Les coordonnees de l'axe de rotation sont les composantes
        'RX','RY','RZ' du champoint de la "deformee modale" de
        rotation.
        La valeur de rotation est automatiquement normee a 1.
        Une base modale elementaire ne peut contenir qu'un seul
        "mode" de rotation de corps rigide. Par consequent il faut
        definir une base modale pour chaque corps rigide.

PART{TAB3 : Raideur et Masse}

        TAB3.'SOUSTYPE' : 'RAIDEUR_ET_MASSE'
        TAB3.'RAIDEUR' : matrice de raideur (type RIGIDITE)
        TAB3.'MASSE' : matrice de masse (type RIGIDITE)
        TAB3.'NATURE_RAIDEUR' : 'PLEINE' si l'on souhaite considerer les
        termes extra-diagonaux de la matrice.
        'DIAGONALE' sinon (par defaut).
        TAB3.'NATURE_MASSE' : 'PLEINE' si l'on souhaite considerer les
        termes extra-diagonaux de la matrice.
        'DIAGONALE' sinon (par defaut).
        TAB3.'BASE_MODALE' : TABLE de sous-type BASE_MODALE permettant
        le calcul des forces de liaisons en base B

PART{TAB4 : Description de l'amortissement}
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EC8ACSIS [Mecanique Dynamique] (proc)
   Procedure EC8ACSIS

   RS = EC8ACSIS TAB1;

   objet:

 a)

   Generation d'un spectre de reponse RS (objet de type EVOLUTION
   comportant une seule courbe) selon les directive de l'EUROCODE
   numero 8 et suivant les parametres TAB1 (objet de type TABLE).

   L'EUROCODE 8 propose l'evolution en periode suivante:

    0 < T < T1 Be = 1 + T/T1 * (B0-1)

    T1 < T < T2 Be = B0

    T2 < T Be = (T2/T)**K * B0

   Be(B0) etant le spectre de reponse d'acceleration normalise, pour un
   amortissement de 5%, RS est obtenu apres introduction de l'acceleration
   maximale Ag du sol et de l'amortissement Khi (<.7):

        RE = Ag * Be(nu*B0) nu=(.05/Khi) **.5

   Pour des periode elevees le code doit etre complete. Pour les terrains
   standards, on limite le deplacement :

        d < dmax = (Ag/g) * D0

   ou g est l'acceleration de la pesanteur.

   Dans ce cas le RE sera definie par le dmax multiplier par le facteur
   d'amplification pour les hautes periodes AMPF (AMPF =1.4).

   Des jeux de donnees (T1,T2,B0,K et D0) sont prevus pour les terrains
   de type A, B ou C.

   Le spectre RS est genere sur une grille de periode compris entre
   TINI (<T1) et TFIN (>T2).

b)

   Generation d'un spectre de reponse RS pour utiliser dans les analyses
   Lineaires. Dans ce cas B0 est divise par le facteur de comportement

        B0 = B0 / Q

   et par T > T2 la condition de deplacement constant n'est pas imposee.
   c.a.d.

        RE = Ag * Be(Eta*B0/Q)

   sujet a la condition

        RE >= 0.2 Ag

   parametres obligatoires:

   Les parametres sont contenues dans TAB1 (objet de type TABLE).

   indice type objet commentaires
        pointe

    TYPE MOT indiquant le type de spectre a savoir:

        a) 'GSIG' (spectre de reponse pour la
        generation des signaux artificiels

        b) 'ALIN' (spectre de reponse pour l'analyse
        lineaire (linear analysis design spectra)).
        dans ce cas on est oblige de fournir le
        parametre Q coefficient de comportement
        (behaviour factor) dans la table

    Q FLOTTANT indiquant la valeur du coefficient de
        comportement si TYPE vaut 'ALIN'.

    AG FLOTTANT indiquant Ag (cm/s/s).

    SOIL MOT indiquant le type de terrain
        'A' 'B' ou 'C'
      ou

    T1
    T2 FLOTTANT indiquant T1, T2 et B0.
    B0

    TINI
    TFIN FLOTTANT donnant TINI et TFIN.

   parametres optionnels:

   Les parametres sont contenues dans TAB1 (objet de type TABLE).

   indice type objet commentaires
        pointe

   K FLOTTANT representant K (defaut = 1
        conduisant a une vitesse constante)

   D0 FLOTTANT indiquant D0
        (defaut = pas de limitation).

   AMOR FLOTTANT indiquant Khi (defaut = 0.05)

   GRAN MOT representant la grandeur physique de
        reponse: 'ACCE'(leration), 'VITE'(sse) ou
        'DEPL'(acement relatif). Le defaut est 'ACCE'.

   ABSC MOT representant la grandeur physique des
        abscisses: 'PERI'(ode) ou 'FREQ'(uence).
        Le defaut est 'PERI'.

   N ENTIER indiquant le nombre de points sur
   NP' ENTIER les branches du spectre au-dela de T2
        (defaut = 25).

## ECFE [Mecanique Resolution]
Operateur ECFE

 RI1 SIGF VARF BEFI = 'ECFE' MODL BE0 VAR0 DEPST CARAC
        (PRECIS) (NITMAX) (UPDATELAG);

Description :

Retour exponentiel avec line search au niveau local

Modeles : VMT_FEFP, RHMC_FEFP, POWDER_FEFP, POWDERCAP_FEFP.

Il rend les contraintes (SIGF), variables internes (VARF) et
deformations elastiques (BEFI).

Il rend egalement le module tangent consistent (RI1)

Cet operateur est appele par INCREME

Voir la notice de PASAPAS pour l'utilisation de cette possibilite

## ECHI [Multi-physique Multi-physique]
$X ECHI (Operateur de discretisation)

     Operateur ECHI

     Syntaxe EQEX (cf EQEX) :

     ... 'EQEX' ... 'OPTI' MOT1 MOT2
        'ZONE' MOD2
        'OPER' 'ECHI' OBJ1 OBJ2
        'INCO' MOT3 (MOT4)

     Objet :

     L'operateur ECHI modelise un echange d'energie ou de masse (ou
toute autre grandeur scalaire) entre une surface ou un volume et le
milieu exterieur.

     Dans le cas d'une equation scalaire portant sur T, le terme
discretise sera de la forme h(T-To) avec h coefficient d'echange
par unite de temps et unite de surface ou de volume, T inconnue
sur laquelle porte l'echange et To champ exterieur.

     Dans le cas d'un systeme d'equations le terme discretise peut
prendre une forme plus generale pouvant coupler deux equations
scalaires. Soit V l'inconnue scalaire (ou inconnue duale) sur
laquelle porte l'equation consideree. Le terme discretise est de la
forme h(T-U) avec T inconnue sur laquelle porte l'echange (inconnue
primale), U champ exterieur.

     La convention de signe associee a ce terme est la suivante :
lorsque le flux est positif (h>0 et T>To (resp. T>U)) la quantite T
(resp. V) diminue.

     Cet operateur est appele par les procedures transitoires EXEC
et EXIC. La syntaxe indiquee permet a l'utilisateur de construire
a l'aide de l'operateur EQEX les donnees necessaires a l'operateur.

     Commentaires :

    'OPTI' : Mot cle introduisant les options numeriques de ECHI
     MOT1 : Type de discretisation spatiale ('EF', 'VF' ou 'EFM1')
     MOT2 : Type de discretisation temporelle ('EXPL' ou 'IMPL')
     La formulation numerique par defaut est EFM1 EXPLICITE.

    'ZONE' : Mot cle introduisant les informations geometriques
     MOD2 : MODEL de sous-type 'NAVIER_STOKES' pour la zone ou
        s'applique ECHI

    'OPER' : Mot cle introduisant les donnees physiques associees
        a l'operateur dont le nom suit
    'ECHI' : Nom de l'operateur
     OBJ1 : Coefficient d'echange h (CHPOINT SCAL CENTRE ou
        FLOTTANT ou MOT)
     OBJ2 : Champ exterieur To (resp. U) (CHPOINT SCAL CENTRE ou
        CHPOINT SCAL SOMMET ou FLOTTANT ou MOT)

    'INCO' : Mot cle introduisant le nom des inconnues primales et
        duales intervenant dans l'echange.
     MOT3 : Nom de l'inconnue sur laquelle porte l'echange T,
        inconnue primale
     MOT4 : Nom de l'inconnue sur laquelle porte l'equation, T
        (resp V), inconnue duale.

     Dans un algorithme explicite, on impose que les inconnues primale
     et duale soient identique. Il est donc inutile de donner MOT4.
     De plus l'operateur est quand meme traite implicitement (matrice
     masse diagonalisee) ce qui fait qu'il n'introduit pas de
     contrainte supplementaire sur la pas de temps!

     Dans un algorithme implicite, lorsque les inconnues primale et
     duale sont identiques, il est egalement inutile de donner MOT4.

     Remarques :

     1) Lorsque OBJ1 et OBJ2 sont de type MOT, l'operateur utilise
 le champ contenu dans la table INCO a l'indice MOT indique.

     2) Le support geometrique (spg) des CHPOINT est une des classes
 de points de la table DOMAINE. Suivant la formulation choisie les
 compatibilites suivantes sont verifiees :
   - En formulation EF ou EFM1, le spg de l'inconnue duale est SOMMET
   - En formulation VF le spg de l'inconnue duale est CENTRE
   - En implicite, lorsque l'inconnue primale et l'inconnue duale sont
     differentes, le spg de l'inconnue primale est CENTRE ou SOMMET.
   - Le spg du coefficient d'echange est CENTRE ou SOMMET en formulation
     EF ou EFM1 et uniquement CENTRE en formulation VF.

     3) Les formulations EF, EFM1 et VF sont disponibles en explicite
et en implicite. En explicite, EF est assimilee a EFM1 ; en implicite
EFM1 a EF.

     4) Le type d'elements du maillage contenu a l'indice MAILLAGE de
 la table DOMAINE indique si l'echange est volumique ou surfacique :
   - L'echange est surfacique (un flux est echange) si
        en 2D, les elements sont de type SEG2 ou SEG3,
        en 3D, les elements sont de type TRI3, QUA4, TRI6, TRI7
        ou QUA9.
   - L'echange est volumique (une source volumique est echangee) si
        en 2D, les elements sont de type TRI3, QUA4, TRI6, TRI7
        ou QUA9.
        en 3D, les elements sont de type CUB8, PRI6, TET4,
        CU27, PR21, TE15,
        PR18 ou TE10.
   - Des elements de type SEG2 ou SEG3 en 3D n'ont pas de sens.
   - En 3D, les elements de type PYR5 ne sont pas disponibles.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ECHIMP [Fluides Limites]
   Operateur ECHIMP

   DOMAINE D'APPLICATION : Thermo-hydraulique.

    OBJET : Imposer des echanges thermiques a travers un objet
   -------- maillage du domaine de calcul.

    SYNTAXE : 'ZONE' $DOM 'OPER' ECHIMP H TETA 'INCO' TN

    TABLEAUX AUTORISES :

H Coefficient d'echange thermique CHPOINT SCAL CENTRE

TETA Temperature a la paroi CHPOINT SCAL CENTRE

TN Temperature CHPOINT SCAL SOMMET

## ECOU [Mecanique Resolution]
    Operateur ECOULE

    SIG1 VAR1 DEPS1 = ECOU MODL1 SIG2 VAR2 EPS3 CAR1 ( TAB1 ) ...

        ... (FLOT1) ('NOID') (ISTEP) ;

    Objet :

    Etant donne un etat initial materiellement et statiquement admissible
caracterise par un champ de contraintes, un champ de variables internes,
des caracteristiques materielles et geometriques d'une part et un incre
ment de deformations d'autre part, l'operateur ECOULE calcule l'etat
final materiellement admissible, qui se caracterise par un nouveau champ
de contraintes, de nouvelles variables internes et par un increment de
deformations inelastiques.

    Commentaire :

    MODL1 : objet modele (type MMODEL)

    SIG2 : champ de contraintes initiales
        (type MCHAML, sous-type CONTRAINTES)

    VAR2 : champ de variables internes initiales
        (type MCHAML, sous-type VARIABLES INTERNES)

    EPS3 : increment de deformations
        (type MCHAML, sous-type DEFORMATIONS)

    CAR1 : description du materiau et de caracteristiques geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

    TAB1 : TABLE contenant des informations complementaires necessaires
        pour les materiaux viscoplastiques avec ou sans endommagement

        - en indice 'DEFI', le champ de deformations inelastiques
        au debut du pas (type MCHAML, sous-type DEFORMATIONS)

        - en indice 'TEMPS0', le temps au debut du pas
        (type FLOTTANT)

        - en indice 'DT', le pas de temps (type FLOTTANT)

        - en indice 'MAXISOUSPAS', le nombre maximal de sous-pas
        utilise pour l'integration des equations (type ENTIER)
        (par defaut 200)

    FLOT1 : precision numerique utilisee pour le calcul
        (type FLOTTANT)
        par defaut FLOT1 est egal a 1.E-3

    ISTEP : indicateur d'action pour calcul non-local (type ENTIER),
        valant 1 pour calcul des fonctions seuil uniquement, ou 2
        pour calcul des variables dissipatives (par defaut 0)

    SIG1 : nouveau champ de contraintes
        (type MCHAML, sous-type CONTRAINTES)

    VAR1 : nouvelles variables internes
        (type MCHAML, sous-type VARIABLES INTERNES)

    DEPS1 : increment de deformations inelastiques
        (type MCHAML, sous-type DEFORMATIONS)

    Remarques :

    Il convient de respecter l'ordre des donnees en entree et en
sortie.

    La lecture du mot 'NOID' permet de supprimer les messages
d'erreur en cas de non-convergence, tout en produisant un resultat.
Dans ce cas, si on a donne une table TAB1, elle contient en sortie,
en indice 'SUCCES', un logique qui vaut VRAI si on a bien converge
et FAUX sinon.

## EFFMARTI [Voile Beton arme] (proc)
    procedure EFF_MARTI

   SIG2 = EFF_MARTI SIG1 MOD1 MAT1 VECT1 VECT2
        H1 ENRE1 ENRI1 COT1

Objet :

Cette procedure transforme les effots generalisés sur un element
bidimensionel(coque, voile) sur la base du modele à  trois couche de
Marti.
Les efforts (N11, N22 et N12) et les moments appliqués (M11, M22, M12)
sont projetés sur deux couches externe et interne d epaisseur
egale à deux fois l enrobage. Les efforts hors-plan de cisaillment
(V1 et V2) sont appliqués à la couche intermediaire:

 / ---------------------------------------------------- /
 | 2c_ext  o  o  o  o  o  o  | cou ext
 /  .................................................... |
 |  n^ /t2  |
 |  |/  |
 | h-2c_int-2c_ext  |---> t1  |  h
 |  |
 |  |
 /  .................................................... |
 | 2c_int  o  o  o  o  o  o  | cou int
 / ---------------------------------------------------- /

Les couches externe et interne sont chargées par une triplet des
efforts de membrane.

N11_ext = N11/2 + M11/D + V1^2/(2V0*cotg(theta))
N22_ext = N22/2 + M22/D + V2^2/(2V0*cotg(theta))
N12_ext = N12/2 + M12/D + V1*V2/(2V0*cotg(theta))

N11_int = N11/2 - M11/D + V1^2/(2V0*cotg(theta))
N22_int = N22/2 - M22/D + V2^2/(2V0*cotg(theta))
N12_int = N12/2 - M12/D + V1*V2/(2V0*cotg(theta))

avec

h = epaisseur totale
c_ext = enrobage couche externe
c_int = enrobage couche interne
V0 = (V1^2 + V2^2)^(0.5)
D = h - c_int - c_ext

Commentaire :
Les couches externe et interne sont definies selon la direction du
vecteur normal n=t1xt2

L angle theta est compris entre 25 et 45 degrés.

En entree :

    SIG1: MCHAML des contraintes
    MOD1: MMODEL associé au SIG1
    MAT1: MCHAML associé au SIG1
    VEC1: direction 1 pour le calcul des contraintes
    VEC2: direction 2 pour le calcul des contraintes
    H1: epaisseur de l element plaque
    ENRE1: enrobage couche externe
    ENRi1: enrobage couche interne
    COT1: terme cotg(theta)

En sortie :

    SIG2: MCHAML avec les composents des efforts projeés
        sur les couches externe et interne et les efforts
        globaux qui agissent sur l element coque
        Component N11 external layer N11E
        Component N22 external layer N22E
        Component N12 external layer N12E
        Component N11 internal layer N11I
        Component N22 internal layer N11I
        Component N12 internal layer N11I
        Component M11 global M11T
        Component M22 global M22T
        Component M12 global M12T
        Component V1 global V1T
        Component V2 global V2T
        Resultant Vr VR

Remarques :

Seulement en 3D le caLcul est possible

## EGA [Mathematiques Logique]
Operateur EGA
------------- < >

LOG1 = OBJET1 EGA OBJET2 (OBJET3) ;

Objet :

L'operateur EGA compare les objets OBJET1 et OBJET2.

Dans le cas general, c'est leur identite qui est testee.
Deux objets deduits l'un de l'autre par affectation (=) sont egaux.
Deux objets deduits l'un de l'autre par copie (COPI) sont differents.

Pour certains types d'objet, le test porte sur leur contenu.

Commentaire :

OBJET1 / OBJET2 : objet a comparer.

OBJET3 : - Pour la comparaison d'objets de type FLOTTANT,
        OBJET3 est la tolerance (type FLOTTANT).
        - Pour la comparaison d'objets de type MOT, OBJET3 est
        un ENTIER precisant le nombre de caracteres sur lesquels
        porte la comparaison. EGA compte le nombre de caracteres
        de gauche a droite a partir du 1er caractere. Par defaut,
        on considere tous les caracteres de chaque objet.

LOG1 : resultat (type LOGIQUE) ayant pour valeur VRAI si les
        deux objets sont egaux et FAUX sinon.

Remarque :

Pour des objets de type MOT, il faut respecter l'ordre suivant :
LOG1 = EGA MOT1 MOT2 ;
Dans la comparaison on ne tiendra pas compte des blancs situes a
la fin des mots. (EGA 'AA' 'AA ') est VRAI.

Si on compare des scalaires (type ENTIER ou FLOTTANT),
OBJET2 sera converti au type de OBJET1.

## ELAS [Mecanique Resolution]
    Operateur ELASTICITE

      CHAM2 = ELAS MOD1 CHAM1 CAR1 (VAR1);

    Objet :

    Cet operateur calcule des contraintes a partir de deformations, ou
des deformations a partir de contraintes , dans l'hypothese d'un
materiau elastique .
    Actuellement , seul le materiau elastique lineaire est disponible.

    Commentaire :

      MOD1 : Objet modele (type MMODEL)

      CHAM1 : champ de contraintes ou deformations (type MCHAML,
        sous-type CONTRAINTES ou DEFORMATIONS)

      CAR1 : champ de proprietes materielles et/ou geometrique (type
        MCHAML, sous type CARACTERISTIQUES)

      VAR1 : champ de variables internes (type MCHAML, sous-type
        VARIABLES INTERNES) facultatif

      CHAM2 : champ de deformations ou contraintes (type MCHAML,
        sous-type DEFORMATIONS ou CONTRAINTES)

    REMARQUES :
        Dans le cas des materiaux endommageables et visco-
        endommageables (liste ci-dessous), et dans le cas ou le
        champ de variables internes est donne, la matrice de
        HOOKE utilisee pour les calculs tient compte de
        l'endommagement. Ceci est valable pour les modeles :
        'PLASTIQUE' 'ENDOMMAGEABLE'
        'VISCOPLASTIQUE' 'VISCODOMMAGE'
        'ENDOMMAGEMENT' 'MAZARS'
        'ENDOMMAGEMENT' 'MVM'
        'PLASTIQUE_ENDOM' 'ROUSSELIER'
        'PLASTIQUE_ENDOM' 'GURSON2'
        'FLUAGE' 'CERAMIQUE'

        Dans le cas de calcul des deformations a partir de
        contraintes avec l'element poutre, il convient de
        creer un materiau avec les sections reduites 'SECY'
        et 'SECZ'. Sinon on ne peut pas inverser la matrice
        de Hooke.

        Dans le cas de calcul des deformations a partir de
        contraintes avec l'element tuyau, il convient de
        creer un materiau avec le coefficent 'CISA'. Sinon
        on ne peut pas inverser la matrice de Hooke.

        Dans le cas de calcul des deformations a partir de
        contraintes pour un materiau orthotrope en contraintes
        planes, il convient de donner les composantes 'YG3',
        'NU13' et 'NU23'. Sinon on ne peut pas inverser la
        matrice de Hooke.

        Dans le cas des elements joints 3D, l'operateur ELAS
        ne marche qu'en isotrope.

## ELECNEUT [Multi-physique Multi-physique] (proc)
Procedure ELECNEUT
------------------ CHI2 DONCHI2

LOGI1 = ELECNEUT TAB1 OBJ1 OBJ2 LENT1 ;

   Objet
   Cette procedure permet de modifier les concentrations
   totales d'un objet de classe DONCHI2 de façon a realiser
   l'equilibre electrique de la solution chimique.

   Commentaires
   TAB1 : table de soustype CHIMI1. Resultat de l'operateur CHI1.
   OBJ1 : Objet de type DONCHI2 ( les valeurs de OBJ1%GTOT sont
        modifiees en sortie)
   OBJ2 : Objet de type PARMCHI2
   LENT1: LISTENTI liste des conposants dont on peut modifier
        la concentration totale
   LOGI1: logique FAUX si la neutralite est verifie
        VRAI si la neutralite ne peut etre verifiee
        (ceci permet de reprendre le calcul avec moins de test)

## ELEM [Maillage Manipulation]
    Operateur ELEM
    -------------- DROI MAXI

    Cet operateur a plusieurs fonctions selon les donnees .

   | 1ere Fonction  |

    Il permet d'extraire des elements de differents types d'un MAILLAGE
donne GEO2. Le resultat est un objet de type MAILLAGE ou POINT .

    GEO1 = GEO2 ELEM | (type d'element si plusieurs types) | | LENTI1 |;
        | COUL1  | | N1  |;
        |
        | 'COUL' I1 ;
        |
        | 'CONTENANT'  POIN1 ('TOUS') ('NOVERIF') ;
        |
        | 'APPUYE'  ( |'STRICTEMENT' | ) GEO3 ('NOVERIF') ;
        |  ( |'LARGEMENT'  | )
        |
        | 'COMPRIS'  POIN1 POIN2 ;

    Les differentes possibilites sont :

   - on extrait de GEO2 les elements du type requis (type MOT).

   - on extrait les elements du type indique et dont la liste des
     numeros se trouve dans l'objet LENTI1 (type LISTENTI).

   - on extrait le N1-ieme element du type indique.

   - on extrait de GEO2 les elements de la couleur COUL1 indiquee.

   - on extrait le N1-ieme element de la couleur COUL1 indiquee.

   - on extrait les elements de la couleur COUL1 indiquee dont la liste
     se trouve dans l'objet LENTI1 (type LISTENTI).

   - on extrait les elements de numero de couleur I1 (voir operateur COUL
     pour connaitre les numeros associes a chaque couleur)

   - on extrait l'element de GEO2 contenant le point POIN1. En presence
     du mot cle TOUS, tous les elements contenant ce point sont fournis.
     Si le mot NOVERIF est utilise, il est autorise de creer
     un resultat de type MAILLAGE vide.

   - on extrait les elements de GEO2 s'appuyant strictement (par defaut)
     ou largement sur les points de l'objet GEO3 (type POINT ou
     MAILLAGE). Si le mot NOVERIF est utilise il est autorise de creer
     un resultat de type MAILLAGE vide.

   - on extrait pour une ligne GEO2 un segment compris entre deux points
     avec l'option 'COMP'. La ligne resultat est decrite de POIN1
     vers POIN2 (type POINT).

    Exemples :

        GEO1 ELEM TRI3
        GEO1 ELEM QUA4 3
        GEO1 ELEM APPUYE LARGEMENT POIN8
        GEO1 ELEM SEG2 (LECT 1 PAS 2 9)
        GEO1 ELEM ROSE
        GEO1 ELEM BLEU 1
        GEO1 ELEM TURQ (LECT 2 PAS 1 3)
        GEO1 ELEM CONT PO1
        LIG1 ELEM COMP PO1 PO2

 Il y a possibilite de concatener la selection sur le type et la couleur

        GEO1 ELEM QUA4 ROSE
        GEO1 ELEM BLEU PRI6 4
        GEO1 ELEM SEG2 ROUG (LECT 1 PAS 2 9)

   | 2eme Fonction  |
    LMOT1 = GE02 ELEM 'TYPE' ;
    LMOT1 = GE02 ELEM 'COUL' ;

    Il permet de connaitre les types des elements contenus d'un MAILLAGE
donne GEO2 (option 'TYPE') ou bien la couleur des elements (option
'COUL'). Dans ce cas le resultat est un objet de type LISTMOTS.

   | 3eme Fonction  |
   GEO1 = CHE1 'ELEM'| MOT1  |('ABS') (MOT3) (MOT4 LMOTS1);
        | MOT2  X1  |
        |'COMPRIS' X1 X2|

   Il permet d'extraire d'un champ/element l'element ou les elements
supports du maximum ou du minimum de l'ensemble de valeurs d'une ou
de plusieurs composantes du champ ou contenant les valeurs verifiant
une relation de comparaison par rapport a une valeur de reference.

    Commentaire :

    CHE1 : Objet de type MCHAML

    MOT1 :'MAXI' ou 'MINI' pour rechercher les elements pour
        lesquels CHE1 est maximum / minimum

    X1 : Valeur de reference (type FLOTTANT)
    X2 : Valeur de reference (type FLOTTANT)

    MOT2 X1 : Recherche les elements de CHE1 dont la valeur vérifie
        une des conditions suivantes :
        'SUPERIEUR' |
        'EGSUPE'  |
        'EGALE'  | X1
        'EGINFE'  |
        'INFERIEUR' |
        'DIFFERENT' |

   'COMPRIS' X1 X2 : Recherche les elements de CHE1 dont la
        valeur est comprise entre X1 et X2

   'ABS' : Mot cle optionnel indiquant que la recherche des
        elements se fera sur la valeur absolue de CHE1

    MOT3 : Mot cle optionnel pouvant prendre l'une des valeurs
        suivantes :
        'LARG' (Par defaut) Un element est contenu dans GEO1 si
        au moins un de ses points support
        verifie la condition souhaitee

        'STRI' Un element est contenu dans GEO1 si
        tous ses points support verifient
        la condition souhaitee
        Dans le cas de 'MAXI' ou 'MINI', un
        seul element est retenu

    MOT4 : Mot cle optionnel pouvant prendre l'une des valeurs
        suivantes :
        'AVEC' : Considere seulement les composantes de CHE1 qui
        sont contenues dans LMOTS1 (Objet de type
        LISTMOTS)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ELFE [Mecanique Dynamique]
Operateur ELFE

 RESU1  = ELFE |'LAPLACE' ! 'PLAQUE' LT1
        |  |  E1 H1 NU1 RHO1 LCAM1
        |  |  PC1
        |  |  CHAM1
        |  |  OP1  |  OP2
        |  |  |  ST1
        |  |  S0 LOM1
        |  |
        |  | 'POUTRE' GEO1 (GE02) CHPO1 CHELEM LFR1
        |  |  S0 POIN1 COMP1 IMETH1 (IMP1)
        |  |
        |  | 'ACOU' GEO1 CHPO1 CHELEM  (TEXP) LFR1
        |  |  S0 POIN1 COMP1
        |  |
        |  |
        |  |
        |'TEMPS'  | 'POUTRE' STRU1 ATTA1 TEMP1
        |  |  DT1 CHAR1 (M1) GREE1
        |  |  ('NFOIS' NN1)
        |  |
        |  |

OPTION LAPLACE PLAQUE
   Cette option permet de calculer la fonction de transfert
   d'une plaque plane en flexion par une formulation integrale
 dans le domaine frequntiel ( Laplace)

  L1 : Maillage du contour ( elements SEG3)
  H1 : Epaisseur de la plaque (type FLOTTANT)
  E1 : Module d'Young (type FLOTTANT)
  NU1 : Coefficient de poisson (type FLOTTANT)
  RHO1 : Masse volumique
  LCAM1 : Liste des coefficients d'amortissement externe
        associes a chaque pulsation de la liste LOM1
  PC1 : Noeuds formant des coins
  CHAM1 : Champ des conditions aux limites imposees
        composantes possibles :
        WW : fleche
        WN : derivee normale de la fleche
        MN : moment flechissant
        KN : effort tranchant
  OP1 : Point d'application de l'effort
  OP2 : Point dont on calcule le deplacement
  ST1 : Maillage surfacique strictement interne
        a la plaque dont on veut la deformee
        ( forme d'elements de type POI1)
  S0 : partie reelle de la variable de Laplace
  LOM1 : liste des pulsations ( balayage en frequnce )

  RESU1 : TYPE TABLE
   si on a donne OP1 OP2 ( fonction de transfert)
  RESU1.1 : module du deplacement en OP2 ( LISTREEL)
  RESU1.2 : phase du deplacement en OP2 ( LISTREEL)
   si on a donne ST1 ( surface deformee )
  RESU1.i : champ definissant le deplacement pour
        la ieme pulsation de la liste LOM1
        ( CHPOINT de composantes MODU et PHAS )

OPTION LAPLACE POUTRE
   Cette option permet de calculer la fonction de transfert d'un
r{seau de poutres (treillis de poutres) @ l'aide de la formula-
tion int{grale dans le domaine fr{quentiel de LAPLACE.

  GEO1 : Objet d{crivant le r{seau de poutres (type MAILLAGE
        SEG2)
 (GEO2) : Objet d{crivant le mªme maillage que GEO1 avec pour
        chaque poutre du r{seau des points suppl{mentaires
        oº l'on calculera le d{placement associ{.

  CHPO1 : Objet d{crivant les conditions aux limites aux
        noeuds extr{mit{s (type CHPOINT).On fixe des
        valeurs particuli}res au vecteur d{placement ( UX,
        UY, UZ ), au vecteur rotation (RX,RY,RZ), au vecteur
        force (FX, FY, FZ), au vecteur moment (MX, MY, MZ)
        et @ une {ventuelle masse ponctuelle (MA).

  CHELEM : Objet d{crivant les caract{ristiques des poutres
        de type MCHAML :

        - on d{finit les caract{ristiques suivantes :

        - YOUN .. module d'YOUNG
        - NU .... coefficient de POISSON
        - RHO ... masse volumique
        - SECT .. section de la poutre
        - INRY .. moment d'inertie /Oy (rep}re local)
        - INRZ .. moment d'inertie /Oz (rep}re local)
        - TORS .. moment de torsion (rep}re local)
        - SECY .. section r{duite au cisaillement /Oy
        - SECZ .. section r{duite au cisaillement /oz
        - CAM ... coefficient d'amortissement visqueux
        - ETA ... amortissement interne (en pourcent)
        - VECT .. vecteur d{finissant l'axe Oy
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ELIM [Maillage Manipulation]
Directive ELIMINATION

ELIM GEO1 (GEO2) (FLOT1) ;

Objet :

La directive ELIM remplace dans GEO1 (type MAILLAGE) tous les noeuds
distants de moins de FLOT1 (type FLOTTANT) par un seul point. Si
FLOT1 n'est pas fourni, le programme prend le dixieme de la densite
courante.

Si GEO2 (type MAILLAGE) est egalement fourni, l'elimination ne se
se fait qu'entre noeuds appartenant respectivement a GEO1 et GEO2
et non a l'interieur d'un meme objet. Autrement dit, les eventuels
doublons a l'interieur de GEO1 ou de GEO2 ne sont pas fusionnes.

Remarques

- L'elimination agit aussi sur les objets qui font reference a des
  noeuds elimines (types MAILLAGE, CHPOINT, TABLE...) en changeant
  ces references.

- L'elimination peut poser des problemes lorsque les noeuds
  elimines sont references par des champs par points: il faut
  pouvoir definir une seule valeur des composantes aux noeuds
  elimines a partir de plusieurs valeurs initiales. L'attribut
  "NATURE" des champs par points est prise en compte dans ce cas
  (pour les champs "DISCRET" on somme, pour les champs "DIFFUS"
  les valeurs doivent etre egales, pour les champs "INDETERMINE"
  on declenche une erreur).

## ELNO [Fluides Resolution]
    Operateur ELNO
    -------------- KCHT PENT

    CHP2 = ELNO MODE1 CHP1 | ('CENTRE')  ;
        | ('CENTREP1')
        | ('MSOMMET')
        | ('VOLUMF' GRCHP1 LIMCHP1)

    Objet :

 L'operateur ELNO transforme un CHPOINT definit sur les points CENTRE
ou CENTREP1 en un CHPOINT definit sur les points SOMMET.
Cet operateur concerne uniquement les CHPOINTs s'appuyant sur une
formulation 'NAVIER_STOKES'.

    Commentaires :

    MODE1 : Objet modele (type MMODEL). On attend une formulation
        'NAVIER_STOKES'

    CHP1 : Objet de type CHPOINT (points CENTRE)
        L'objet ne doit pas etre partitionne et ne doit avoir
        qu'une composante

    CHP2 : Objet de type CHPOINT (points SOMMET)

    'CENTRE' (option par defaut).
      ou
    'CENTREP1' : Mot-cle du type de CHPOINT de CHP1.
      ou
    'MSOMMET'

    'VOLUMF' : Mot-cle pour une reconstruction de type Volumes finis
     Dans ce cas il faut donner les informations suivantes :

     GRCHP1 : Objet de type CHPOINT (points CENTRE) contenant les
        valeurs du gradient de CHP1.

     LIMCHP1 : Objet de type CHPOINT (points CENTRE) contenant les
        valeurs du limiteur du gradient : Methode MUSCL
        (voir operateur PENT).

    Complements d'information :

      On cherche CHP2 minimisant au sens des distributions l'ecart
    (CHP2 - CHP1) avec la contrainte supplementaire que l'integrale
    du champ sur le domaine soit conservee.
      On ne peut appliquer cette transformation qu'aux grandeurs
    physiques intensives (temperature vitesse pression etc).
    Cette derniere propriete n'est pas controlee par l'operateur.
      Les matrices masses sont condensees sur la diagonale.

    Exemple :
      KPRES = 'CENTREP1' ;
      pe=exco rv.inco.'PRESSION' 'PRES' ;
      pe= kcht $bell scal KPRES pe ;
      pn= elno $bell pe KPRES ;

    Cas CHP1 MSOMMET :

    Dans ce cas CHP1, connu aux sommets de l'element, est interpole
    sur les autres noeuds selon l'element lineaire correspondant.

     Remarques pour les volumes finis

       La valeur en un point sommet est calcule en effectuant la
     moyenne des valeurs reconstruites a partir des Centres des
     elements auquel il appartient.

       Si on utilise le MOTCLE 'VOLUMF', la donnee du gradient et
     du limiteur est obligatoire.

     Si le gradient est calcule avec l'operateur PENT et le limiteur
    impose a 1, la reconstruction au sommet d'un CHPOINT CENTRE
    lineaire est exact a l'interieur du domaine.

     Si la valeur du limiteur en tout point est 0, la reconstruction
    consiste simplement a effectuer la moyenne des valeurs
    de CHP1 au centre voisins d'un sommet.

## ELST [Mecanique Dynamique]
    Operateur ELST

    ELSTR1 = ELST STRU1 GEO1 ;

    Objet :

    L'operateur ELST cree un objet de type ELEMSTRU que l'on utilise
pour ecrire des liaisons entre sous-structures.

    Commentaire :

    STRU1 : objet de type STRUCTUR

    GEO1 : objet inclus dans la geometrie de la structure
        (objet geometrique constitue d'un seul type d'element)
        (type POINT ou MAILLAGE).

    ELSTR1 : objet de type ELEMSTRU
