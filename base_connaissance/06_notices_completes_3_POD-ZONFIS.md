# Notices Gibiane complètes (français), partie 3/3 : POD à ZONFIS

Texte des notices `INFO`, sans décorations, sans colonne « voir aussi » ni section anglaise. Chaque notice commence par `## NOM [section]`.

## POD [Mathematiques Autres]
Operateur POD

   |TPOD1  | = POD |LDATA1  | (LENTI1) (LCOMP1)  ----+
   |LPOD1 LVAL1|  |TAB1 (MOT1)|  |
     |
     |
     +------>  |'SNAPSHOTS'| (MASS1) NBMOD ('TBAS' (MAIL1)) ;
        |'CLASSIQUE'|

Objet :

L'operateur POD applique la methode de Decomposition Orthogonale
aux valeurs Propres (POD) a un signal d'entree donne. En retour,
on obtient la base formee des premiers vecteurs propres ainsi que
les valeurs propres associees.

Commentaires :

DEFINITION DU SIGNAL D'ENTREE

LDATA1 [LISTCHPO] : Signal d'entree generique constitue d'un
        ensemble de champs de meme structure (meme
        geometrie et memes composantes)

TAB1 [TABLE] : Table de resultats issue d'un calcul CAST3M
        (sous-type PASAPAS, DYNAMIC ou EXEC) dans
        laquelle recuperer automatiquement le signal

MOT1 [MOT] : Nom de la grandeur consideree, par exemple :
        - pour PASAPAS : DEPLACEMENTS (par defaut),
        TEMPERATURES...
        - pour DYNAMIC : DEPL (par defaut), VITE...
        - pour EXEC : UN (par defaut), PN, TN...

LENTI1 [LISTENTI] : Liste optionnelle des indices des pas de
        temps a considerer pour calculer la base POD
        (permet de sous-echantillonner le signal)

LCOMP1 [LISTMOTS] : Liste optionnelle des composantes retenues

DEFINITION DE LA METHODE DE CALCUL

'SNAPSHOTS' : methode preconisee quand le nombre de d.d.l. (noeuds
        + composantes) est largement superieur au nombre de
        pas de temps

'CLASSIQUE' : methode preconisee quand le nombre de d.d.l. (noeuds
        + composantes) est largement inferieur au nombre de
        pas de temps

 MASS1 [RIGIDITE] : matrice de masse (ou de raideur) fournie
        optionnellement pour calculer proprement les
        produits scalaires (notion d'energie)

DEFINITION DU FORMAT DE SORTIE

NBMOD [ENTIER] : Nombre de modes POD a calculer (ne devrait pas
        exceder le nombre de pas de temps si SNAPSHOTS ou
        le nombre de d.d.l. si CLASSIQUE)

'TBAS' : mot-cle indiquant que l'on souhaite recuperer les resultats
        sous la forme d'une table de sous-type BASE_MODALE

MAIL1 [MAILLAGE] : Si le mot-cle 'TBAS' est present, on peut fournir
        en option le maillage MAIL1 qui sera place a
        l'indice 'MAILLAGE' de la table de sortie TPOD1
        (utilise notamment par la procedure EXPLORER)

OBJETS EN SORTIE

TPOD1 [TABLE] : Table de sous-type BASE_MODALE (renvoyee si le
        mot-cle 'TBAS' est specifie)

LPOD1 [LISTCHPO] : Liste des modes POD ranges par valeurs propres
        decroissantes (renvoyee si le mot-cle 'TBAS' est
        absent)

LVAL1 [LISTREEL] : Liste des valeurs propres rangees par ordre
        decroissant (renvoyee si le mot-cle 'TBAS' est
        absent)

Remarques :

a) Les multiplicateurs de Lagrange sont toujours ignores lors du
    calcul des modes POD (meme si 'LX' est specifiee dans COMP1).

b) Les modes POD renvoyes sont unitaires au sens de la norme infinie
   (leur maximum vaut 1, toutes composantes confondues). Il est
   possible de les renormaliser avec la norme Euclidienne grace a
   l'operateur NNOR.

c) Un indice 'VALEUR_PROPRE' est ajoute pour chaque mode present
   dans la table TPOD1 (souvent plus pertinent que 'FREQUENCE').

## POIN [Maillage Points]
    Operateur POIN
    -------------- MOTS MINI

    Cet operateur a trois fonctions selon les donnees.

   | 1ere fonction |

    L'operateur POIN permet de creer
     - un POINT defini par ses coordonnees (FLOTTANT).
     - un MAILLAGE de POI1 defini par ses coordonnees (LISTREEL).

    RESU1 = POIN OBJET1 (OBJET2) (OBJET3) ('DENS' OBJET4);

    Commentaire :

    |  OBJET1  |  OBJET2  |  OBJET3  |  OBJET4  ||  RESU1  |
    |  FLOTTANT  |  FLOTTANT  |  FLOTTANT  |  FLOTTANT  ||  POINT  |
    |  LISTREEL  |  LISTREEL  |  LISTREEL  |  LISTREEL  ||  MAILLAGE |

    OBJET1 : 1ere coordonnee DIME 1, 2 ou 3
    OBJET2 : 2eme coordonnee DIME 2 ou 3
    OBJET3 : 3eme coordonnee DIME 3

   'DENS' : Mots cle optionnel permettant de definir la densite
    OBJET4 : densite

    Remarque :

    En DIMEnsion 1, la creation d'un point n'est possible que via cette
        fonction de l'operateur POIN.
    En DIMENsions 2 et 3, l'operateur POIN est equivalent a la syntaxe
        couramment utilisee : POIN1 = FLOT1 FLOT2 (FLOT3) ;

   | 2eme fonction |

    L'operateur POIN extrait d'une geometrie un ou plusieurs points.

    POINi = GEO1  POIN | N1
        | I1 I2
        | 'INITIAL'
        | 'FINAL'
        | 'JONC'
        | 'PROC'  POIN1
        | 'DROIT'  POIN1  POIN2  (FLOT1)
        | 'PLAN'  POIN1  POIN2 POIN3  (FLOT1)
        | 'CYLI'  AXEI1  AXEJ2 POIN1  (FLOT1)
        | 'CONE'  SOMM1  AXEI1 POIN1  (FLOT1)
        | 'SPHE'  CENTR1 POIN1  (FLOT1)
        | 'TORE'  CENTR1 AXEI1 CENTR2 POIN1 (FLOT1)

    Commentaire :

    GEO1 : geometrie (type MAILLAGE)

    Suivant le mot-cle, l'operateur POIN extrait de GEO1 :

    -  <aucun>  : le N1-ieme point  | Dans ce cas, GEO1 ne doit etre
        | compose que d'elements de type
        | POI1 ou SEG2 (voir remarque)
    - <aucun> : le I1-ieme noeud du I2-eme element

    - 'INITIAL' : le premier point  | GEO1 est compose uniquement
    - 'FINAL'  : le dernier point  | d'elements POI1, SEG2 ou SEG3

    - 'JONC' : les points connectes a plus de 2 elements
        (destine essentiellement aux maillages de lignes)

    - 'PROC' : le point le plus proche de POIN1 (type POINT)

    - 'DROIT' : l'ensemble des points situes sur la droite POIN1 POIN2
        (type POINT)
    - 'PLAN' : l'ensemble des points situes sur le plan POIN1 POIN2
        POIN3 (type POINT)
    - 'CYLI' : l'ensemble des points situes sur le cylindre d'axe
        AXEI1 AXEJ1 (type POINT) passant par le point POIN1
        (type POINT)
    - 'CONE' : l'ensemble des points situes sur le cone de sommet
        SOMM1 (type POINT), dont l'axe est AXEI1 SOMM1 (type
        POINT) et passe par le point POIN1 (type POINT)
    - 'SPHE' : l'ensemble des points situes sur la sphere de centre
        CENTR1 passant par le point POINT1
    - 'TORE' : l'ensemble des points situes sur le tore de centre
        CENTR1 (type POINT), dont un point de l'axe est AXEI1
        (type POINT) dont le centre de petit cercle est CENTR2
        (type POINT) et passant par le point POIN1 (type POINT

    Avec les mots-cles 'DROIT','PLAN','CYLI','CONE','SPHE','TORE' on
    peut introduire un critere de proximite :

    - FLOT1 : critere de distance (type FLOTTANT)

    Remarques :

    Il faut donner GEO1 avant POIN ou sinon directement apres.

    Pour extraire des points d'un objet GEO1 qui n'est pas compose
    d'elements de type POI1 ou SEG2, il faut d'abord changer GEO1 en un
    objet compose d'elements de type POI1 (voir operateur CHANGER),
    puis utiliser l'operateur POIN. Si GEO1 est compose d'elements SEG2,
    POINT GEO1 NN ramene le premier point du NN-ieme element.

    Les mots-cles 'DROIT','PLAN','CYLI','CONE','SPHE','TORE' ne sont pas
    disponibles en DIMEnsion 1.

    Le critere CRIT est par defaut le dixieme de la densite courante.

   | 3eme Fonction |

    L'operateur POIN extrait d'un champ (ou cree quand il s'agit d'un
point de Gauss) le ou les points supports du maximum ou du minimum de
l'ensemble de valeurs d'une ou de plusieurs composantes du champ, ou
les points supports des valeurs verifiant une relation de comparaison
par rapport a une (ou deux) valeur(s) de reference.

        |  'MAXI'  |  'AVEC'
   GEO1 = CHE1 POIN  |  'MINI'  | ('ABS') (  LMOTS1 );
        |  |  'SANS'
        |'SUPERIEUR' |  |
        |'EGSUPE'  |  |
        |'EGALE'  | FLOT1  |
        |'EGINFE'  |  |
        |'INFERIEUR' |  |
        |'DIFFERENT' |  |
        |'COMPRIS' FLOT1 FLOT2|

    Commentaire :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## POINTCYL [Maillage Points] (proc)
    Procedure POINTCYL

    POIN1 = POINTCYL RAY1 FLOT1 (FLOT2) ;

    Objet :

    La procedure POINTCYL permet de definir un point (ou un maillage de points)
par des coordonnees cylindriques.

    Commentaire :

    RAY1 : rayon (type FLOTTANT ou LISTREEL)

    FLOT1 : angle en degres (type FLOTTANT ou LISTREEL)

    FLOT2 : cote (en 3D) (type FLOTTANT ou LISTREEL)

    POIN1 : point, ou MAILLAGE de points si l'on utilise des LISTREEL

## POINTSPH [Maillage Points] (proc)
    Procedure POINTSPH

    POIN1 = POINTSPH FLOT1 FLOT2 FLOT3 ;

    Objet :

    La procedure POINTSPH permet de definir un point (ou un maillage de points)
par des coordonnees spheriques.

    Commentaire :

    FLOT1 : distance a l'origine (type FLOTTANT ou LISTREEL)

    FLOT2 : angle autour de l'axe Z (compris entre 0 et 360 degres)
        (type FLOTTANT ou LISTREEL)

    FLOT3 : 2ieme angle (compris entre -90 et +90 degres)
        (type FLOTTANT ou LISTREEL)

    POIN1 : point, ou MAILLAGE de points si l'on utilise des LISTREEL

## POLA [Mathematiques Autres]
   Operateur POLA

     R1 U1 = POLA MODL1 GRAD1  | ('GEOM') | ;
        |  'DEPL'  |

   Objet :

L'operateur POLA effectue la decomposition polaire d'un champ de
gradient F associe a une transformation geometrique: X --> x = X+u
        F = R1 * U1
Le gradient F est soit donne directement (option 'GEOM' prise par
defaut), auquel cas F = GRAD1 = dx/dX, soit determine a partir
du gradient du champ de deplacement u qui fait passer d'une
geometrie a l'autre (option 'DEPL'), auquel cas GRAD1 = du/dX et
F = Id + GRAD1.

     Commentaire :

     MODL1 : Objet de type MMODEL

     GRAD1 : champ de gradients (type MCHAML)

     R1 : champ de rotation pure (type MCHAML, sous type gradient)

     U1 : champ de deformation pure (type MCHAML, sous type
        gradient)

## POLYNO [Mathematiques Fonctions] (proc)
   procedure POLYNO

   FLOT1 = POLYNO FLOT2 COEF0 COEF1 (COEF2 COEF3 COEF4 COEF5) ;

   Objet :

   Cette procedure sert a calculer un polynome de degre superieur ou egal
@ 1 et inferieur ou egal a 5.

   Commentaire :

   La procedure POLYNO calcule la quantite :

        FLOT1 = COEF0 + COEF1*FLOT2 + COEF2*FLOT2*FLOT2
        + COEF3*FLOT2*FLOT2*FLOT2
        + ....

   FLOT2 : variable du polynÔme (type FLOTTANT)

   COEFi : coefficients du polynÔme (type FLOTTANT)

   FLOT1 : resultat (type FLOTTANT)

## POSI [Langage Objets]
 Operateur POSI

 Objet :

 L'opérateur POSI recherche la ou les positions d'un ou plusieurs
 items au sein d'une liste.

 Syntaxe :

   OBJET1 = POSI OBJET2 'DANS' OBJET3 (OBJET4) ('TOUS')

   Types possibles detailles ci-apres :

 => Cherche la premiere occurrence d'un item dans une liste

       ENTIER = POSI ENTIER 'DANS' LISTENTI ;
       ENTIER = POSI FLOTTANT 'DANS' LISTREEL (FLOT1) ;
       ENTIER = POSI MOT 'DANS' LISTMOTS ('NOCA') ;
       ENTIER = POSI MOT 'DANS' MOT ('NOCA') ;
       ENTIER = POSI POINT 'DANS' MAILLAGE ;

 => Cherche toutes les occurrences d'un item dans une liste

       LISTENTI = POSI ENTIER 'DANS' LISTENTI 'TOUS' ;
       LISTENTI = POSI FLOTTANT 'DANS' LISTREEL (FLOT1) 'TOUS' ;
       LISTENTI = POSI MOT 'DANS' LISTMOTS ('NOCA') 'TOUS' ;
       LISTENTI = POSI MOT 'DANS' MOT ('NOCA') 'TOUS' ;
       LISTENTI = POSI POINT 'DANS' MAILLAGE 'TOUS' ;

 => Cherche la premiere occurrence de plusieurs items dans une liste

       LISTENTI = POSI LISTENTI 'DANS' LISTENTI ;
       LISTENTI = POSI LISTREEL 'DANS' LISTREEL (FLOT1) ;
       LISTENTI = POSI LISTMOTS 'DANS' LISTMOTS ('NOCA') ;
       LISTENTI = POSI MAILLAGE 'DANS' MAILLAGE ;

Commentaires :

1) Si OBJET2 (ou un de ses items) n'est pas trouve dans la liste
   OBJET3, sa position vaut 0.

2) Le premier item de la liste OBJET3 occupe la position 1.

3) Pour detecter que deux nombres reels sont egaux, on compare leur
   difference (en valeur absolue) avec un nombre juge suffisamment
   petit. Par defaut, on utilise un critere RELATIF base sur la
   precision machine. L'utilisateur peut imposer une valeur ABSOLUE
   pour ce critere via la donnee de FLOT1 (type FLOTTANT).

4) Par defaut, la comparaison de chaines est sensible a la casse,
   ce qui signifie que l'on distingue les majuscules des minuscules.
   On peut indiquer a la directive que l'on souhaite plutot faire une
   recherche insensible a la casse grace au mot-cle "NOCA".

5) Les maillages doivent etre elementaires et de POI1.

## POSS [Presentation Presentation]
  COMPATIBILITE DES ELEMENTS ET DES OPERATEURS

OPERATEURS A R M S B K
        F I A I S S
        F G S G I I
        E I S M G G
elements support valeurs de IFOUR

 TRI3 TRI3 * * * * * -2 -1
 TRI6 TRI6 * * * * * -2 -1
 QUA4 QUA4 * * * * * -2 -1
 QUA8 QUA8 * * * * * -2 -1
 CUB8 CUB8 * * * * * 2
 CU20 CU20 * * * * 2
 TET4 TET4 * * * * * 2
 TE10 TE10 * * * * 2
 PRI6 PRI6 * * * * * 2
 PR15 PR15 * * * * 2
 PYR5 PYR5 * * * * 2
 PY13 PY13 * 2
 COQ3 TRI3 * * * * * 2
 DKT TRI3 * * * * * 2
 POUT SEG2 * * * * * * 2
 LISP RAC2 * * * * 2
 TUYA SEG2 * * * * * * 2
 TUFI SEG2 * * 2
 LTR3 TRI3 * * 2
 LQU4 QUA4 * * 2
 LCU8 CUB8 * * 2
 LPR6 PRI6 * * 2
 LPY5 PYR5 * * 2
 LTE4 TET4 * * 2

## POSTDDI [Mecanique Resolution] (proc)
    Procedure POSTDDI

   TAB1 TAB2 TAB3 TAB4 = POSTDDI TAB5 TAB6 MAI1 PER1 NPE1 IDE1;

    Objet :

    Calcul du mombre de cycles a rupture sur un ou plusieurs
cycles stabilises (a la suite d'un calcul utilisant le modele
visco-plastique a deux deformations inelastiques (DDI)).

   Commentaire :

 En entree

    TAB5 TABLE C'est la table issue d'un calcul fait
        a l'aide de PASAPAS

    TAB6 TABLE Table qui contient les parametres des
        lois d'endommagement. Les indices de
        cette table sont des mots. La liste en
        est : PETITA, B, C, SIGU, SIGL, M,
        ALPHA, BETA, GRANDA, K, R.

    MAI1 MAILLAGE Objet maillage definissant la zone sur
        laquelle on effectue le calcul.

    PER1 FLOTTANT Periode du chargement.

    NPE1 ENTIER Nombre de periodes sur lesquelles on
        calcule le nombre de cycles a rupture.

    IDE1 ENTIER Numero de la premiere periode de calcul.

 En sortie

    TAB1 TABLE table indicee par les numeros de periodes
        contenant les nombres de cycles a rupture
        en fatigue seule (champs par element).

    TAB2 TABLE table indicee par les numeros de periodes
        contenant les nombres de cycles a rupture
        en fluage seul (champs par element).

    TAB3 TABLE table (par periode) des nombres de cycles
        a rupture (entiers)

    TAB4 TABLE table indicee par les numeros de periodes
        contenant les dommages finaux (champs par
        element)

## POSTDDI1 [Post-traitement Analyse] (proc)
Procedure POSTDDI1

   CHAM1 = POSTDDI1 CHAM2 FLO1 MOD1;

Cette procedure est appelee par POSTDDI.

## POSTOU [Mecanique Rupture] (proc)
    Procedure POSTOU

    Objet :

MECANIQUE :

  Une procedure permet d'effectuer un calcul de l'ouverture de fissure
  dans le cas complexe suivant le trajet de fissure. La fissure s'ouvre
  perpendiculairement au trajet de fissure. L'ouverture de fissure
  prend en compte les microfissures autour d'une fissure principale.

  Cette procédure est composée de trois procedures qui réalise
  les calculs dans l'ordre suivant :

  - initou: permet de positionner les points de fissure
  - zonfis: permet de detecter visuellement une zone de fissure
  - postou: permet de caculer l'ouverture de fissure

  La procedure postou permet de caculer l'ouverture de fissure.

   Description :

L'entree pour postou:

TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :
    TAB1 TABLE : continuation du calcul avec initou et zonfis
    OBJET1 FLOTTANT : demi-longueur de la ligne de post-traitement.

La sortie pour postou:

    TAB1.CHE TABLE : coordonnee des points de fissure dans une
        zone de fissure

    TAB1.NORMM TABLE : points d'extremite de la ligne de
        post-traitement
    TAB1.DIRNN TABLE : direction de la ligne de post-traitement

    TAB1.OUVNO LISTREEL : ouverture normale sur les lignes de
        post-traitement
    TAB1.OUVTO LISTREEL : ouverture tangentielle sur les lignes de
        post-traitement
    TAB1.OUVNX LISTREEL : abscisse sur les lignes de post-traitement

    TAB1.FISNO LISTREEL : ouverture normale au trajet de fissure
    TAB1.FISTO LISTREEL : ouverture tangentielle au trajet de fissure
    TAB1.FISNX LISTREEL : coordonnee X de l'ouverture normale
    TAB1.FISNZ LISTREEL : coordonnee Z de l'ouverture normale

## POSTVIBR [Post-traitement Affichage] (proc)
Procedure POSTVIBR

Objet :

La procedure POSTVIBR est appelee par EXPLORER. Elle permet de
depouiller graphiquement les resultats d'une table BASE_MODALE
ou LIAISONS_STATIQUES.

## POT_SCAL [Magnetostatique Magnetostatique] (proc)
      Procedure POT_SCAL

       POT_SCAL TABB SOLIN

      Objet :
      En magnetostatique 3D calcul par la methode a deux potentiels
      le potentiel total et le potentiel reduit.
      Materiaux isotropes ou isotropes transverse .

      Commentaires :

      TABB table contenant les indices suivants en toute lettre

      'DPHI' = GEO1 maillage de la zone de potentiel reduit

eventuellement:
      'RIGCON' = RIG1 rigidite construite comme suit:

        | MOD1 = GEO1 'MODE' 'THERMIQUE' 'ISOTROPE'
        | RIG1 = 'CONDUC' MOD1  'K'  MUAIR
        RIG1 peut l'assemblage de rigidites elementaires
        et de rigiditees de super elements
        ( si absente de la table cette conductivite sera construite
        - sans super elements)

      'SEPPHI'= GEO2 surface de separation (appartenant a DPHI)
      'ORIG' = POINT de la surface de separartion ou on impose
        l'egalite des potentiels

      'POTSYM'= TAB1
        avec TAB1 table contenant des tables de description
        sur SEPPHI et son entourage eventuel pour calcul
        et application du saut de potentiel

      TAB1.I = TABLE STN (I = 1,2.........N)
        une table STN permet de decrire differentes formes
       de conditions limites pouvant se presenter ou de passer
       directement des objets de type rigidite a prendre en compte
       dans la resolution ( conditions de periodicite par exemple)
       3 formes disponibles :

        1)  |STN.'LGEO' = GEO3 maillage type ligne( trace de SEPPHI
        |  dans un plan de symetrie des potentiels
        |  si elle existe .En general le saut de
        |  potentiel est nul si on a choisi
        |  ORIG sur cette ligne )
        |STN.'MTYP' = MOT1  'TBLOQ' OU 'RENSE'  condition
        s'appliquant aussi a la surface GEO4
        si TBLOQ blocage a zero des noeuds de GEO3
        si RENSE application relation d ensemble sur GEO3
      eventuellement ( si SEPPHI a plusieurs traces dans un plan de
      symetrie des potentiels) :

        |STN.'SGEO'  = GEO4 maillage de type surface (surface
        |  equipotentielle liee au saut de potentiel)
        |  GEO3  appartient a son son contour

        2)  |STN.'IMPOSE' = CHPO chpoint du saut impose localement

      'MUAIR' = FLOT1 permeablite du vide

      'DPSI' = GEO4 maillage de la zone de potentiel total
        (totalite du domaine air et ferro-magnetique)

      |'AIRPSI' = GEO5  maillage de la zone d' air de DPSI
      |  (appartient a DPSI)
OU  |'RIGCSPSI' =  RIG2 rigidite construite  comme suit:

        | MOD2 = GEO5 'MODE' 'THERMIQUE' 'ISOTROPE'
        | RIG2 = 'CONDUC' MOD2  'K'  MUAIR
        RIG2 peut l'assemblage de rigidites elementaires
        et de rigiditees de super elements

      'TABNUSEC' = TABMAT table stockage de l'ensemble
        des materiaux ferro-magnetiques

        | MODI = MODE GEOI THERMIQUE ISOTROPE (ORTHOTROPE)
        |  TABMAT.MODI = STN ;
        |  STN.'EV1'  = evolution MU1(H)  sortie  voir H_B
Imat fois  |  si materiau  isotrope transverse (isotrope plan 23)
        |  STN.'EV2'  = evolution MU2(H)  sortie  voir H_B
        |  STN.'DIR1' = P1  direction 1 (type point)
        |  STN.'DIR2' = P2  direction 2 (type point)

      'BLOQUE' = conditions limites du probleme global
      'BIOT' = CHP1 champ D INDUCTION defini au minimum sur
        la surface de separation SEPPHI ( contruit avec l operateur
        BIOT par exemple attention c'est H et non B )

      'ISTEP' entier 1 le calcul sera fait en une seule fois
        ou 2 le calcul est fait en deux temps :

        A) cacul du champ d induction la TABB doit etre
        sauvegardee ( voir SAUVER)
        B) le complement du calcul est lance apres restitution
        de la sauvegarde en etrant dans POT_SCAL puis MAG_NLIN

 SOLIN si present on calcule la solution en lineaire
        Pour un calcul non lineaire apres passage dans POT_SCAL
        il faut enchainer par la procedure MAGNLIN

        si absent le premier pas sera fait dans MAG_NLIN
        voir ci apres

      Cette procedure construit et archive dans TABB les ingredients
      necessaire a un passage en non lineaire dans MAG_NLIN.

      SORTIES :

      le potentiel est dans TABB.'POTENTIEL'
        POTENTIEL REDUIT ET POTENTIEL TOTAL SUR LES ZONES
        CORRESPONDANTES.

        SI ON S INTERESSE A L INDUCTION VOIR PROCEDURE MKGDT

## POT_VECT [Magnetostatique Magnetostatique] (proc)
        Procedure POT_VECT

        POT_VECT TAB1 (MOT1)

        Objet :

        En magnetostatique 2D calcul du potentiel vecteur

        TAB1 table dont les arguments sont :

        'MUAIR' permeabilite de l'air ( defaut 4 * PI * 1.E-7 )
        'AIR' Partie air non reduite a un super element

        |'AIRSUP'  Partie air traitee en super element(pas obligatoire)
option  |'MAITRES' Points maitres si super element
        |'ENCS '  Condition limite sur super element(eventuellement)

        'TABNUSEC' = TABMAT table contenant des tables de description
        de la ( des) zones Ferro_magnetique(s) comme suit:

        |MODI = MODE GEO1 THERMIQUE ISOTROPE (ORTHOTROPE)
        |TABMAT.MODI = STN ;
        |STN = TABLE ;
        |STN.'EV1 = MU1(H)  courbe 1./MU0*MUREL(B) type evolution
   Imat fois |  obtenues par H_B a partir de B(H) par exemple
        si materiau orthotrope
        |STN.'DIR1' =  P1  direction associee ( type point)
        |STN.'EV2' = MU2(H) courbe 1./MU0*MUREL(B) type evolution
        |la direction associee est perpendiculaire a DIR1

   conditions limites generales et courants

        'BLOQUE' Conditions limites generales regroupees
        'IMPOSE' CHPOINT (cree par DEPIMP, la partie rigidite doit
        etre dans MATAB.'BLOQUE')
        'COUR' table de tables contenant la description des blocs
        de courants constituee par un ou des appel(s) a la
        procedure DESCOUR

        'AXI' = VRAI si probleme axisymetrique.

        MOT1 mot optionnel 'SOLIN' pour le calcul du premier pas
        lineaire

        En sortie :

        'POTENTIEL' si on a demande le calcul du premier pas
        par SOLIN
        TABB contient en plus les ingredients necessaires a la
        procedure MAG_NLIN pour faire les calculs non
        lineaires ( voir MAG_NLIN).

## POUT2MAS [Maillage Volumes] (proc)
Procedure POUT2MAS:

      MAIL3D = POUT2MAS MOD1 MAT1 (MOTCLE) (TAB1);
        |('GAUSS')
        |('MASSIF')

Objet:
     POUT2MAS genere un maillage massif MAIL3D a partir d'un modele
     de poutre pour permettre la verification des dimensions et des
     orientations des modeles de poutre.
     Des champs de deplacements, les deformees associees, ainsi que
     certains champs par elements par elements du modele a fibre (MATS,
     VONS, VAIS) s'appuyant sur le maillage 3D peuvent aussi etre
     calculees a partir des champs s'appuyant sur le maillage de poutre.

Entree:
   MOD1 : Modele de poutre de type section, poutre ou tuyau

   MAT1: Materiau contenant les donnees materiaux et le vecteur VECT
        (vecteur local Oy de la poutre)
        Pour les tuyaux: rayon et epaisseur du tuyau
        Pour les poutres: inerties INRZ INRY,
        Pour les poutres de type section MODS MATS

   MOTCLE:

     Option 'GAUSS': Les sections sont tracees a chaque point de Gauss
        des elements de poutre (option par defaut)

     Option 'MASSIF': Un volume base sur la geometrie de la section et
        ayant la discretisation des elements de poutre
        dans le sens longitudinal est genere.

   TAB1: Table contenant les indices:

   TAB1.'TUYAU': Table precisant certains parametres pour la generation
   I du maillage pour les tuyaux
   (TAB1.'TUYAU'). 'NCIRC' : nombre de segments le long de la circon-
        -ference du tuyau (NCIRC=4 par defaut)
   (TAB1.'TUYAU'). 'NEPAI' : nombre de segments sur l'epaisseur du tuyau
        (NEPAI=1 par defaut)

   TAB1.'POUTRE': Table precisant certains parametres pour la generation
        du maillage pour les poutres

   Sous option poutre de section circulaire:
   (TAB1.'POUTRE').'CIRCULAIRE' = VRAI;
   (TAB1.'POUTRE'). 'NCIRC' : nombre de segments le long de la circon-
        -ference du tuyau (4 par defaut)

   Sous option poutre de section rectangulaire:
   (TAB1.'POUTRE').'RECTANGULAIRE' = VRAI;
   (TAB1.'POUTRE'). 'NY' : nombre de segments sur le cote Oy
        (repere local de la poutre) (NY= 1 par defaut)
   (TAB1.'POUTRE'). 'NZ' : nombre de segments sur le cote Oz
        (repere local de la poutre) (NZ=1 par defaut)

   TAB1.'DEPLACEMENTS': Table contenant les champs de deplacements
        definis sur le maillage de poutre
   (TAB1.'DEPLACEMENTS').i: Objet de type CHPOINT (champs de deplacement)

   TAB1.'DEPLACEMENTS_3D': Table contenant les nouvelles deformees
        sur le maillage 3D
   (TAB1.'DEPLACEMENTS_3D').i: Objet de type CHPOINT
        (champs de deplacement)

   TAB1.'DEFORMEE': Table contenant les deformees s'appuyant sur le
        maillage 3D
   (TAB1.'DEFORMEE').i: Objet de type DEFORMEE

   TAB1.'AMPLITUDE_DEFORMEES': FLOTTANT donnant l'amplitude des deformees

Pour l'option GAUSS uniquement:

   TAB1.'MATS': Table contenant les champs de caracteristiques du
        modele a fibre (YOUN, NU, RHO, SECT...) s'appuyant
        sur la section 2D.
   (TAB1.'MATS').i: Objet de type MCHAML (champs decaracteristiques)

   TAB1.'VONS': Table contenant les champs de contraintes du
        modele a fibre (SMXX, SMXY, SMXZ...) s'appuyant
        sur la section 2D.
   (TAB1.'VONS').i: Objet de type MCHAML (champs de contraintes)

    TAB1.'VAIS': Table contenant les champs de variables internes du
        modele a fibre (EPSE, EPSO...) s'appuyant
        sur la section 2D.
   (TAB1.'VAIS').i: Objet de type MCHAML

   TAB1.'RELATION_3D': Si cet indice le table contient le booleen VRAI,
        les relations cinematiques liant le modele
        de coque et le maillage volumique sont crees.

Sortie:
    MAIL3D: Maillage 3D volumique ou surfacique

    TAB1.'MATS_3D': Table contenant les champs s'appuyant
        sur le modele 3D (option GAUSS seulement).
   (TAB1.'MATS_3D').i: Objet de type MCHAML (champs de caracteristiques)

    TAB1.'VONS_3D': Table contenant les champs s'appuyant
        sur le modele 3D (option GAUSS seulement).
   (TAB1.'VONS_3D').i: Objet de type MCHAML

    TAB1.'VAIS_3D': Table contenant les champs s'appuyant
        sur le modele 3D (option GAUSS seulement).
   (TAB1.'VAIS_3D').i: Objet de type MCHAML

    TAB1.'RELATION_3D': Table contenant les relations cinematiques
        (RIGIDITE) entre le modele de coque
        et le maillage volumique

  Remarque: Les champs VONS et VAIS sont situes dans les variables
        internes du modele de poutre a fibre

## PPRE [Fluides Resolution] (proc)
    Operateur PPRE

    SYNTAXE (EQEX) : Cf operateur EQEX

    'OPER' PPRE 'VN' Rrho

    OBJET :

L'operateur PPRE, propre au modele bifluide, calcule et introduit la
force due au gradient de pression dans l'equation de quantite de
mouvement des particules.
Les equations de qdm etant divisees par la masse volumique, il multiplie
le gradient de pression du gaz par le rapport des masses volumiques
RHOf/RHOp.

    COMMENTAIRES :

Rrho rapport masse vol. gaz / masse vol. particules FLOTTANT

VN indice de la table INCO pour la MOT
       vitesse des particules (CHPOINT VECT SOMMET)

## PRCH [Fantome]
Operateur PRCH

Cet opérateur a été débranché.

## PREC [Mecanique Resolution]
   Operateur PREC

     PRE1 =  PREC MODARM MATARM F1 (TAB1) |(MAIL1) | (PRE0) ;

   Objet :

   L'operateur PREC construit calcule les pertes de precontraintes
   et construit le cham des containtes effectives sur des armatures
   a partir des tensions initiales appliquees a une extremite
   de chaque cable appartenant au modele
     ( modeles MARR ou ARMATURE BARR )

     Commentaire :

     MODARM : objet modele associe aux cables (type MMODEL)

     MATARM : champ de caracteristiques associe au modele
        (type MCHAML, sous-type CARACTERISTIQUES)

     F1 : valeur de la force de tension a
        l'extremite du cable (type FLOTTANT)

     MAIL1 : Maillage des extermites sur lesquelles on applique
        les tensions (type POI1 ) (pour les element BARR)
        par defaut la tension sera appliquee aux points
        finaux de chaque cable sous-tendant le modele

     POIN1 point si il n y a qu un seul cable (type POINT) a la
        place du maillage

     PRE0 : champ de contraintes initiales (facultatif)
        (type MCHAML, sous-type CONTRAINTES)

     PRE1 : champ de contraintes resultat
        (type MCHAML, sous-type CONTRAINTES)

Dans le cas de calculs de perte de precontrainte :

     TAB1 : TABLE contenant les arguments suivants :

   Pour la perte de precontrainte par frottement
 TAB1.'FF' : coefficient de frottement angulaire (defaut 0.18 rd-1)
 TAB1. 'PHIF' : coefficient de frottement lineaire (defaut 0.002 m-1)

  Pour la perte de precontrainte par recul a l'ancrage :

 TAB1.'GANC' : glissement a l'ancrage (defaut 0.0)

  Pour la perte de precontrainte par relaxation de l'acier :

  TAB1.'RMU0': coefficient de relaxation de l'armature ((defaut 0.43)
  TAB1.'FPRG': contrainte de rupture garantie ((defaut 1700.e6 Pa)
  TAB1.'RH10': relaxation a 1000 heures expimee en % (defaut 2.5 )

    NOTA :
      -le maillage support d un SOUS-MODELE (type SEG2 ) doit
     etre constitues de lignes SANS BRANCHEMENT
      -si il y a une precontrainte initiale le MODARM et MATARM
     sont imperativement les memes que pour le calcul initial

   DANS LE CAS DE L'UTISATION DES VALEURS PAR DEFAUT LES UNITES
    DOIVENT ETRE CELLE MENTIONNES CI DESSUS.

## PREPAENC [Fluides Modele] (proc)
   Procedure PREPAENC

     PREPAENC RXT TBT ;

   OBJET :

La procedure PREPAENC est une procedure interne appelee par ENCEINTE

   Commentaires

   RXT TABLE :
   TBT TABLE :

## PRES [Mecanique Limites]
  Operateur PRES
  -------------- CNEQ BSIG

1ere syntaxe

  Objet :
    L'operateur PRES calcule les forces nodales equivalentes a une
pression appliquee a la surface d'un modele element finis.

  Syntaxe générale :
CHPO1 = PRES | 'MASS' MODL1  | FLOT1 GEO1 | ;
        |  | CHPO2  |
        |  | CHEL1  |
        |
        | 'COQU' MODL1  | FLOT1  | |  'NORM'  | (CAR1);
        |  | CHPO2  | |  VEC1  |
        |  | CHEL1  | |  'POIN'  POIN1 |
        |
        | 'FISS' MODL1  | FLOT1  |  VEC1 POIN1 CAR1 ;
        |  | CHPO2  |
        |
        | 'TUYA' MODL1  CAR1 ;
        |
        | 'SHB8' MODL1  | FLOT1  |  'INTERNE'  | |  ;
        |  |  |  'EXTERNE'  | |
        |  |  |
        |  | CHPO2  |

Entrees :
    MASS |
    COQU | : mot-cle designant le type d'element sur lequel la pression
    FISS |  est appliquee (elements massifs, coques, linesprings,
    TUYA |  tuyaux ou SHB8)
    SHB8 |

    MODL1 : objet sur lequel la pression est appliquee (type MMODEL)

    FLOT1 : valeur algebrique de la pression (type FLOTTANT)

    GEO1 : pour les elements massifs, maillage sur lequel la pression
        est appliquee (type MAILLAGE)

    CHPO2 : champ contenant les valeurs de pression aux noeuds
        (type CHPOINT)

    CHEL1 : champ contenant les valeurs de pression (type MCHAML)

    NORM : mot-cle indiquant que la pression est positive si elle es
        portee par la normale positive a l'element

    VEC1 : vecteur donnant la direction suivant laquelle la pression
        est appliquee (type POINT).(Ne fonctionne qu'en 3D)

    POIN : mot-cle suivi de :

    POIN1 : point vers lequel la pression est appliquee (type POINT)
        ne s'utilise que pour des coques ou des linesprings.(Ne
        fonctionne qu'en 3D)

    CAR1 : caracteristiques des coques, des linesprings ou des
        tuyaux (type MCHAML, sous-type CARACTERISTIQUES) :
        - pour les coques epaisses, contient les valeurs des
        epaisseurs aux points d'integration
        - pour les linesprings, contient les valeurs des caracte-
        ristiques aux points d'integration
        - pour les tuyaux, contient la valeur de la pression
        interne

   'INTERNE' : il faut mettre en pression la surface interne (externe)
   'EXTERNE' (si le maillage contenu dans MODL1 ne contient
        pas les references au deux surfaces il faut
        utiliser l'operateur ORIE)

Sortie
    CHPO1 : forces nodales equivalentes (type CHPOINT)

- Remarque 1 :
    ATTENTION : Si vous utilisez un MODELE plus grand que la zone ou
    la pression est definie par le CHPOINT CHPO2, alors les elements
    situes a la frontieres, ayant un point avec une pression non nulle,
    se verront eux aussi charges. Il est donc fortement conseille de
    fournir une reduction du MODELE sur les elements concernes.

    Pour les coques, on reoriente les elements de la surface sur
    laquelle s'applique la pression.

    L'angle que fait le vecteur avec la face d'un element doit etre
    superieur a 1 degre.

    Pour les elements massifs; la pression est supposee dirigee vers
    l'interieur du massif. Dans le cas d'une depression il faut donner
    une pression ou un champ par points de pression negatifs.

    Avec l'option NORM, la normale N a l'element est definie telle
    que l'element de coque ayant pour numerotation (i,j) on ait
    (ij,N)=+90.

    Pour les elements SHB8 une pression positive est dirige vers
    l'element si celui-ci est correctement oriente (voir ORIE)

- Remarque 2 :
    ATTENTION : il faut utiliser un modele MODL1 dont la formulation
    est coherente avec le calcul d'une force de pression
    (ex : MECANIQUE, POREUX,...).

2nd Syntaxe

CHEL2 = PRES MODL1 | MOT1 VAL1 (MAIL1) ;
        | CHEL1  ;

  Objet :
    L'operateur PRES definit un champ par element de pression.
Dans ce cas, le champ de forces nodales equivalentes peut etre
obtenu a l'aide de l'opérateur BSIGMA.

  En sortie :
    CHEL2 : champ par element de pression (type MCHAML).

  En entree :

    MODL1 : objet de type MMODEL, modele de définition du chargement
        de pression.

    MOT1 : objet de type MOT, nom de la composante de pression.

    VAL1 : objet de type FLOTTANT, valeur algébrique de la pression.

    MAIL1 : objet de type MAILLAGE, surface sur laquelle on souhaite
        appliquer une pression. Par défaut, elle s'applique sur
        toute la surface de définition du modele.

    CHEL1 : objet de type MCHAML, champ par element de pressions.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PRET [Fluides Resolution]
  Operateur PRET
  -------------- KONV

I) ECOULEMENT COMPRESSIBLE

     Dans le cadre de la modelisation d'un ecoulement compressible
  en discretisation volumes finis des Équations d'Euler, cet
  operateur permet de calculer les variables primitives aux
  interfaces (i.e. etats 'gauche' et 'droite' de chaque face), a
  partir des variables primitives aux centres.

  |  1ere modele  |

  Gaz parfait (mono-espece); les chaleurs specifiques cp et cv
  sont independantes de la temperature.

  Cas a: premier ordre en espace, premier ordre en temps

        MCHAM1 MCHAM2 MCHAM3 MCHAM4 = 'PRET' MCLE1 ENTI1 ENTI2
        MOD1 CHPO1 CHPO2 CHPO3 CHPO4 ;

  Commentaire :

        MCLE1 : MOT; 'PERFMONO'.

        ENTI1 : ENTIER; ordre en espace (=1).

        ENTI2 : ENTIER; ordre en temps (=1).

        MOD1 : Objet MODELE.

        CHPO1 : CHPOINT "CENTRE" contenant la masse volumique (en
        kg/m^3; une composante, 'SCAL').

        CHPO2 : CHPOINT "CENTRE" contenant la vitesse (en m/s;
        deux composantes en 2D, 'UX ','UY ').

        CHPO3 : CHPOINT "CENTRE" contenant la pression du gaz
        (en Pa; une composante, 'SCAL').

        CHPO4 : CHPOINT "CENTRE" contenant le "gamma" du gaz (une
        composante, 'SCAL').

        MCHAM1 : MCHAML contenant la masse volumique, qui a comme
        SPG (support geometrique) 'DOMA' MOD1 'FACEL'
        (une composante, 'SCAL'; en kg/m^3)

        MCHAM2 : MCHAML contenant la vitesse (m/s) et les cosinus
        directeurs du repere locale (n,t) dans le repere
        global (x,y) (dans le cas 2D 6 composantes:
        * 'UN' = vitesse normale (SPG = 'FACEL')
        * 'UT' = vitesse tangentielle (SPG = 'FACEL')
        * 'NX' = n.x (SPG = 'FACE')
        * 'NY' = n.y (SPG = 'FACE')
        * 'TX' = t.x (SPG = 'FACE')
        * 'TY' = t.y (SPG = 'FACE')).

        MCHAM3 : MCHAML (SPG = "FACEL") contenant la pression du
        gaz (en Pa, une seule composante, 'SCAL').

        MCHAM4 : MCHAML (SPG = "FACEL") contenant le "gamma" du
        gaz (une seule composante, 'SCAL').

  Cas b: deuxieme ordre en espace, premier ou deuxieme ordre en temps

        MCHAM1 MCHAM2 MCHAM3 MCHAM4 = 'PRET' MCLE1 ENTI1 ENTI2
        MOD1 CHPO1 CHPO2 CHPO3 CHPO4 CHPO5 CHPO6
        CHPO7 CHPO8 CHPO9 CHPO10 (FLOT1) ;

  Commentaire :

        MCLE1 : MOT; 'PERFMONO'

        ENTI1 : ENTIER; ordre en espace (=2)

        ENTI2 : ENTIER; ordre en temps (=1 ou 2)

        MOD1 : Objet MODELE.

        CHPO1 : CHPOINT "CENTRE" contenant la masse volumique (en
        kg/m^3; une composante, 'SCAL').

        CHPO2 : CHPOINT "CENTRE" contenant le gradient de la
        masse volumique (en kg/m^4; 2 composantes en 2D,
        'P1DX', 'P1DY').

        CHPO3 : CHPOINT "CENTRE" contenant le limiteur du
        gradient de la masse volumique (une seule
        composante 'P1 ')

        CHPO4 : CHPOINT "CENTRE" contenant la vitesse (en m/s;
        deux composantes en 2D, 'UX ','UY ').

        CHPO5 : CHPOINT "CENTRE" contenant le gradient de la
        vitesse (en s^-1; 4 composantes en 2D, 'P1DX',
        'P1DY', 'P2DX', 'P2DY').

        CHPO6 : CHPOINT "CENTRE" contenant le limiteur du
        gradient de la vitesse (2 composantes en 2D,
        'P1', 'P2').

        CHPO7 : CHPOINT "CENTRE" contenant la pression du gaz
        (en Pa; une composante, 'SCAL').

        CHPO8 : CHPOINT "CENTRE" contenant le gradient de la
        pression (en Pa/m; 2 composantes en 2D, 'P1DX',
        'P1DY').

        CHPO9 : CHPOINT "CENTRE" contenant le limiteur du
        gradient de la pression (une composante, 'P1' ).

        CHPO10 : CHPOINT "CENTRE" contenant le "gamma" du gaz
        (une composante, 'SCAL').

        FLOT1 : FLOTTANT (a specifier dans le cas ENTI2 = 2) qui
        contient l'increment en temps (en s) pour l'etape
        de prediction (valeur conseillee = Dt / 2);

        MCHAM1 : MCHAML contenant la masse volumique, qui a comme
        SPG (support geometrique) 'DOMA' MOD1 'FACEL'
        (une composante, 'SCAL'; en kg/m^3)

        MCHAM2 : MCHAML contenant la vitesse (m/s) et les cosinus
        directeurs du repere locale (n,t) dans le repere
        global (x,y) (dans le cas 2D 6 composantes:
        * 'UN' = vitesse normale (SPG = 'FACEL')
        * 'UT' = vitesse tangentielle (SPG = 'FACEL')
        * 'NX' = n.x (SPG = 'FACE')
        * 'NY' = n.y (SPG = 'FACE')
        * 'TX' = t.x (SPG = 'FACE')
        * 'TY' = t.y (SPG = 'FACE')).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PRIM [Mathematiques Fonctions]
    Operateur PRIM

    a) EVOL2 = PRIM EVOL1 ;

    b1) RCHPO1 RCHPO2 = 'PRIM' 'PERFMONO' CHPO1 CHPO2 CHPO3 CHPO4 ;

    b2) RCHPO1 RCHPO2 RCHPO3 RCHPO4 RCHPO5 = 'PRIM' 'PERFMULT' TAB1
        CHPO1 CHPO2 CHPO3 CHPO4 ;

    b3) RCHPO1 RCHPO2 RCHPO3 RCHPO4 (RCHPO5) RCHPO6 =
        'PRIM' 'PERFTEMP' TAB1 CHPO1 CHPO2 CHPO3 CHPO4
        (CHPO5) (CHPO6) ;
       ou

        RCHPO1 RCHPO2 RCHPO3 (RCHPO5) RCHPO6 = 'PRIM' 'PERFTEMP'
        TAB1 CHPO1 CHPO2 CHPO3 (CHPO5) (CHPO6) ;

    c) RMAT1 = 'PRIM' 'CONSPRIM' MAIL1 LMOT1 LMOT2
        CHPO1 CHPO2 CHPO3 CHPO4 ;

    d) RCHPO8 RCHPO7 RCHPO6 RCHPO5 RCHPO4 RCHPO3 RCHPO2 RCHPO1 =
        'PRIM' 'TWOFLUID'
        CHPO1 CHPO2 CHPO3 CHPO4 CHPO5
        CHPO6 CHPO7 CHPO8 CHPO9 CHPO10 CHPO11;

    e) RCHD1 RCHD2 RCHV1 RCHV2 RCHP1 RCHP2 RCHT1 RCHT2 =
        'PRIM' 'DEM' TABPGAS
        CHPAL1 CHPAL2 CHPARN1 CHPARN2 CHPAGN1 CHPAGN2
        CHPARET1 CHPARET2 CHPTGUE1 CHPTGUE2 EPS ;

    f) RCHPO0 RCHPO1 (RCHPO2) = 'PRIM' 'GFMP' TAB1
        CHPO0 CHPO1 CHPO2 CHPO3 (CHPO4 CHPO5) ;

 a) L'operateur PRIMITIVE calcule la primitive d'un objet EVOLUTION
    pouvant representer des fonctions dont on connait la valeur pour
    des abscisses croissantes.
    La valeur de la primitive pour la premiere abscisse de chaque
    fonction est 0.

     ATTENTION : les valeurs sont rendues aux abscisses de l'evolution
    initiale ( l'evolution resultat ne represente pas la primitive
    en tous points de l'intervale)

 b) Dans le cadre de la modelisation d'un ecoulement compressible en
    discretisation volumes finis (equations d'Euler ou Navier-Stokes),
    cet operateur permet de calculer les variables primitives (i.e.
    pression, vitesse, temperature, ...) a partir des variables
    conservatives (i.e. masse volumique, quantite de mouvement, energie
    volumique totale, masse volumique de chaque espece).

 b1 -----------------
    |  1ere modele  |

    Gaz parfait (mono-espece); les chaleurs specifiques cp et cv
    sont independantes de la temperature.

    RCHPO1 RCHPO2 = 'PRIM' MCLE1 CHPO1 CHPO2 CHPO3 CHPO4 ;

    Commentaire :

    MCLE1 : MOT, 'PERFMONO'.

    CHPO1 : CHPOINT contenant la masse volumique (en kg/m^3; une
        composante, 'SCAL').

    CHPO2 : CHPOINT contenant les debits (en kg/s/m^2; deux
        composantes en 2D, 'UX ','UY ', trois composantes
        en 3D, 'UX ','UY ', 'UZ ').

    CHPO3 : CHPOINT contenant l'energie totale par unite de volume
        (en J/m^3; une composante, 'SCAL').

    CHPO4 : CHPOINT contenant le "gamma" du gaz (une composante,
        'SCAL').

    RCHPO1 : CHPOINT contenant la vitesse (m/s; deux composantes
        en 2D, 'UX ','UY ', trois composantes
        en 3D, 'UX ','UY ', 'UZ ').

    RCHPO2 : CHPOINT contenant la pression du gaz (Pa; une composante,
        'SCAL').

    Remarques :

    1) On controle que
       * la pression est positive,
       * 1 < gamma < 3
       * les CHPOINTs sont definis sur le meme support geometrique

    2) CHPO1, CHPO2, CHPO3 sont les variables conservatives des
       Équations d'Euler.

 b2 -----------------
    |  2eme modele  |

    Melange de gaz parfaits (cp et cv independants de la temperature)

    RCHPO1 RCHPO2 RCHPO3 RCHPO4 RCHPO5 = 'PRIM' MCLE1 TAB1 CHPO1
        CHPO2 CHPO3 CHPO4 ;

    Commentaire :

    MCLE1 : MOT, 'PERFMULT'.

    TAB1 : TABLE qui contient :
        * les noms des especes qui apparaissent explicitement
        dans les equations d'Euler en TAB1 . 'ESPEULE'
        (LISTMOTS);
        * le nom de l'espece qui n'y est pas dans
        TAB1 . 'ESPNEULE' (MOT);
        * les CP et les CV des gaz qui apparaissent en
        TAB1 . 'ESPEULE' et en TAB1 . 'ESPNEULE'
        TAB1 . 'CP' (TABLE)
        TAB1 . 'CV' (TABLE).

    CHPO1 : CHPOINT contenant la masse volumique (en kg/m^3; une
        composante, 'SCAL').

    CHPO2 : CHPOINT contenant les debits (en kg/s/m^2; deux
        composantes en 2D, 'UX ','UY ', trois composantes
        en 3D, 'UX ','UY ', 'UZ ').

    CHPO3 : CHPOINT contenant l'energie totale par unite de volume
        (en J/m^3; une composante, 'SCAL').

    CHPO4 : CHPOINT contenant la masse volumique des especes qui sont
        explicitement "splitted" dans les equations d'Euler
        (en kg/m^3; leurs noms sont dans TAB1 . 'ESPEULE').

    RCHPO1 : CHPOINT contenant la vitesse (en m/s; deux composantes
        en 2D, 'UX ','UY ', trois composantes
        en 3D, 'UX ','UY ', 'UZ ').
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PRIN [Mecanique Resolution]
    Operateur PRIN
    -------------- CALP VMIS

       CHAM2 = PRIN CHAM1 MODL1 (CAR1) (MOT1) ;

    Objet :

    L'operateur PRIN calcule le champ de contraintes ou de deformations
principales associe a un champ de contraintes ou de deformations.
Il fournit egalement les cosinus directeurs
des directions principales par rapport au repere general.

    Dans le cas des coques minces, on calcule a partir des contraintes
 ou des deformations generalisees les contraintes ou les deformations
 principales vraies.

    Commentaire :

    CHAM1 : champ de contraintes ou de deformations
        (type MCHAML, sous-type CONTRAINTES ou DEFORMATIONS)

    MODL1 : objet modele (type MMODEL)

    CAR1 : champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

    MOT1 : mot-cle (type MOT) qui indique pour les coques l'endroit
        ou les contraintes ou les deformations sont calculees :

        'SUPE' : en peau superieure
        'MOYE' : sur la surface moyenne ( par defaut )
        'INFE' : en peau inferieure

        On peut aussi indiquer, en dimension 2, que l'on veut ordonner
        les trois contraintes ou deformations principales.
        Dans ce cas mettre : 'TRID'

    CHAM2 : champ de contraintes ou de deformations principales
        (type MCHAML, sous-type PRINCIPALE)

    Remarque : En dimension 3, les contraintes ou les deformations
    __________ princiales sont ordonnees par valeur algebrique
        decroissante, la premiere etant la plus grande.

        En dimension 2, la troisieme valeur principale correspond
        systematiquement a la direction perpendiculaire au plan.
        Par consequent, seules les 2 premieres sont ordonnees, sauf si
        on a donne le mot-clef 'TRID'.

        On peut obtenir les noms de composantes associes aux
        contraintes ou deformations principales en utilisant
        l'operateur EXTR : EXTR CHAM2 COMP ...

## PRNS [Mathematiques Traitement]
Operateur PRNS

EVOL1 = PRNS EVOL2 EVOL3 LREEL1 (LREEL2 FLOT1 MOT1 MOT2 COUL1)
        ( MOT3 (ENTI1) (FLOT2) (TPL) )
        ( MOT4 DTIME ) ;

objet :

Calcul du spectre de reponse EVOL1 (comportant une unique courbe)
associe:

- au spectre de puissance EVOL2 (comportant une unique courbe) d'un
  signal stationnaire "virtuel" de dure TE.

- et a N courbes de modulation EVOL3 fonction du temps (comportant N
  courbes) correspondantes aux bandes de frequence indiquees dans
  LREEL1 [ la bande de frequence de la i-eme fonction EVOL3 est
  donnee par le i-eme (frequence inferieure) et le i+1-eme
  (frequence superieure) element de LREEL1 ].

Les fonctions de modulation doivent toute demarrer au meme instant
TI et s'achever au meme instant TF. La duree du signal TE est
evidemment donnee par TF-TI. La distribution des maxima suit la loi
de Newmark/Gumble 1.

options :

- Le calcul du spectre de reponse s'effectue sur une grille
  de periode de 75 points, compris entre 0.04s (25 Hz) et TE et
  uniformement distribue dans un espace logarithmique. Une grille
  alternative peut etre donnee en option dans LREEL2.

- Le spectre de reponse est calcule pour un amortissement standard
  de 0,05. L'option FLOT1 permet de specifier un amortissement
  different.

- MOT1 represente la grandeur physique de reponse: 'ACCE'(leration),
  'VITE'(sse) ou 'DEPL'(acement relatif). Le defaut est 'ACCE'.

- MOT2 represente la grandeur en abscisse de EVOL1:
  'PERI'(ode) ou 'FREQ'(uence). Le defaut est 'PERI'.

- COUL1 represente la couleur de l'objet cree.
  Par defaut c'est la couleur de EVOL2.

- La partie non-stationnaire du calcul (fonction de transfert des
  oscillateurs) se refere a K processus stationnaires. L'intervalle
  de temps defini par EVOL3 est donc divise en K parties egales et
  integration numerique temporelle sur chaque intervalle est
  realisee sur M instants equidistants. La modulation instationnaire
  peut etre non nulle au dela de TE: l'integration peut etre
  completee sur une duree supplementaire TPL. De plus, des processus
  iteratifs (e.g. recherche de zero a une precision PREC) sont
  eventuellement mis en oeuvre pour determiner la distribution. MOT3
  permet de specifier K et M d'une part et TPLU et PREC d'autre part.
  Si MOT3 vaut 'NBPR'(ocessus), ENTI1 specifie K. Si MOT3 vaut
  'NBIN'(tegration) alors ENTI1 specifie M. Si MOT3 vaut 'TPLU'(s),
  alors FLOT2 specifie TPL. Si MOT3 vaut 'PREC'(ision), alors FLOT2
  specifie PREC. Si MOT3 vaut 'NBDE'(faut), K correspond a des
  processus d'environ 2 secondes, M vaut 10, TPL vaut 20 secondes
  et PREC vaut 1.E-3. Le defaut pour MOT3 est 'NBDE'.

- La partie non-stationnaire du calcul peut se referrer a une
  modelisation en ondelette si MOT4 vaut 'ONDE'. Dans ce cas EVOL2
  contient autant de point que de bande de frequence et EVOL3 la
  modelisation des coefficient en ondelette: la premiere courbe est
  le residu, et les suivantes sont relatives a chaque niveau de
  decomposition (des basses vers les hautes frequences). DTIME
  indique la periode echantillonnage associe au residu. Dans ce cas
  M et K ne peuvent plus etre specifies.

## PROB [Mathematiques Statistiques]
Operateur PROB

FLOT6 = PROB FLOT1 FLOT2 FLOT3 FLOT4 FLOT5;

Objet :

L'operateur PROB calcule la probabilite que la variable
aleatoire definie par sa moyenne, son ecart-type, ses
coefficients de symetrie et d'aplatissement, soit inferieure
a une certaine valeur.

Commentaire :

FLOT1 = moyenne de la variable aleatoire (type FLOTTANT)

FLOT2 = ecart-type de la variable aleatoire (type FLOTTANT)

FLOT3 = coefficient de symetrie de la v.a. (type FLOTTANT)

FLOT4 = coefficient d'aplatissement de la v.a. (type FLOTTANT)

FLOT5 = borne superieur de l'integrale (type FLOTTANT)

FLOT6 = probabilite (type FLOTTANT)

## PROBABRS [Mathematiques Statistiques] (proc)
Procedure PROBABRS

FLOT9 = PROBABRS FLOT1 FLOT2 FLOT3 FLOT4
        FLOT5 FLOT6 FLOT7 FLOT8

Objet :

Cette procedure permet le calcul de la probabilite de defaillance
idealisee :
        Prob(R<S)
Probabilite que la resistance (R) soit inferieure a
        la sollicitation (S)

(la resistance et la sollicitation sont definies par leur
 quatre premiers moments statistiques)

Commentaire :

FLOT1 : Moyenne de la resistance R (type REEL)

FLOT2 : Ecart-type de la resistance R (type REEL)

FLOT3 : Coefficient de symetrie de la resistance R (type REEL)

FLOT4 : Coefficient d'aplatissement de la resistance R (type REEL)

FLOT5 : Moyenne de la sollicitation S (type REEL)

FLOT6 : Ecart-type de la sollicitation S (type REEL)

FLOT7 : Coefficient de symetrie de la sollicitation S (type REEL)

FLOT8 : Coefficient d'aplatissement de la sollicitation S (type REEL)

FLOT9 : Probabilite que R < S (type REEL)

## PROBDENS [Mathematiques Statistiques] (proc)
Procedure PROBDENS

EVOL1 EVOL2 = PROBDENS FLOT1 FLOT2 FLOT3 FLOT4

Objet :

Cette procedure calcule les evolutions de la densite de
probabilite et de la fonction de repartition entre
    mu-6*sigma et mu+6*sigma.

Commentaire :

FLOT1 = moyenne (type FLOTTANT)

FLOT2 = ecart-type (type FLOTTANT)

FLOT3 = coefficient de symetrie (type FLOTTANT)

FLOT4 = coefficient d'aplatissement (type FLOTTANT)

EVOL1 = densite de probabilite (type EVOLUTION)

EVOL2 = fonction de repartition (type EVOLUTION)

## PROCHEXT [Multi-physique Multi-physique] (proc)
  Procedure PROCHEXT Voir EXECRXT

  PROCHEXT TPS RXT 'KAS1' HZ HAIR TAIR HMER TMER ;

  ou

  PROCHEXT TPS RXT 'KAS2' HZ TAIR LAIR TMER LMER ;

  OBJET :

Cette procedure est destinée à être appelée par la procédure personnelle
de EXECRXT. PROCHEXT permet de modéliser l'échange thermique de la paroi
externe de l'enceinte avec un milieu extérieur. L'enceinte est supposée
semi-immergée. On peut donc définir deux modes d'échange l'un avec l'eau
(partie inférieure) et l'autre avec l'atmosphère (partie supérieure).

Dans le cas 'KAS1' On se donne la hauteur d'eau et deux couples,
(coefficient d'échange et température extérieure). Toutes ces grandeurs
dépendent du temps (ce sont des objets EVOLUTION).

Dans le cas 'KAS2' On se donne toujours la hauteur d'eau et deux
températures extérieures, mais les coefficients d'échange sont calculés
à l'aide d'une corrélation de couche limite de convection naturelle
pour une paroi plane verticale, respectivement pour l'eau et l'air
(Nusselt = 0.113 Grashof**0.33). Dans ce cas seul la hauteur d'eau et
les températures extérieures dépendent du temps.

On renvoie aux jeux de données: pressuhx1.dgibi et pressuhx2.dgibi

  Commentaires

 TPS 'FLOTTANT': est le temps (en secondes). Cette information est
        transmise par la procédure personnelle si l'appel
        se fait dans dans la procédure personnelle.
 RXT 'TABLE' : est la table envoyé à EXECRXT. Cette information
        est transmise par la procédure personnelle.
'KAS1' 'MOT' : Indique que l'on donne les coefficients d'échange
'KAS2' 'MOT' : Indique que l'on calcule les coefficients d'échange
        à l'aide d'une corrélation de convection naturelle
 HZ 'EVOLUTION': Hauteur de la partie immergée à partir du point le
        plus bas de l'enceinte. Elle peut dépendre du temps
 HAIR 'EVOLUTION': Coefficient d'échange en W/m**2/°K pour la partie
        émergée. Il peut dépendre du temps
 HMER 'EVOLUTION': Coefficient d'échange en W/m**2/°K pour la partie
        immergée. Il peut dépendre du temps
 TAIR 'EVOLUTION': Température de l'air extérieur en °C.
        Elle peut dépendre du temps
 TMER 'EVOLUTION': Température de l'eau extérieure en °C.
        Elle peut dépendre du temps
 LAIR 'FLOTTANT' : Echelle de longueur (en mètre) pour la corrélation
        de convection naturelle en air.
 LMER 'FLOTTANT' : Echelle de longueur (en mètre) pour la corrélation
        de convection naturelle en eau.

## PRODT [Fluides Resolution] (proc)
Procedure PRODT

   Syntaxe :

        P = PRODT $MD (| 'TODEF' |) UN (GB TN) ;
        | 'TOROT' |
        | 'COMPL' |
        | 'MIXTE' |

       P Mesure locale du gradient de vitesse
        CHPOINT (SCAL SOMMET)

       $MD Modele NAVIER_STOKES
        MMODEL

       UN Champ de vitesse
        CHPOINT (VECT SOMMET)

       GB Vecteur de flottabilite g*beta (vecteur accleration de
        la pesanteur * coefficient de dilatation thermique)
        POINT

       TN Champ de temperature
        CHPOINT (SCAL SOMMET)

   Objet :

   Cette procedure renvoie une mesure du tenseur gradient des vitesses,
   grandeur qui intervient notamment dans le calcul de la viscosite
   turbulente de modeles RANS ou LES (k-Epsilon, Spalart-Allmaras,
   Smagorinsky...).

   Commentaires :

   Pour modeliser la production d'energie turbulente, de nombreux
   auteurs ont recours a une formulation de type C * Nut * P, ou :

      - C est un facteur adimensionnel, souvent constant voire unitaire
      - Nut est la viscosite turbulente
      - P est une mesure locale du tenseur gradient de vitesse

   LA PROCÉDURE PRODT CALCULE UNIQUEMENT LE TERME P, brut, laissant
   aux routines dediees aux differents modeles le soin de calculer la
   production reelle.

   /!\ P est homogene a l'inverse d'un temps au carre
       => IL PEUT ÊTRE NÉCÉSSAIRE D'EN PRENDRE LA RACINE!

   Differentes mesures du tenseur gradient des vitesses sont proposees:

      - 'TODEF': tenseur taux de deformation (PAR DÉFAUT)

        P = |S|² = 2*Sij*Sij avec Sij = 0.5*(Uij+Uji)
        Uij = dUi/dxj

      - 'TOROT': tenseur taux de rotation

        P = |R|² = 2*Rij*Rij avec Rij = 0.5*(Uij-Uji)
        Uij = dUi/dxj

      - 'COMPL': tenseur des vitesses complet

        P = |U|² = Uij*Uij  avec Uij = dUi/dxj

      - 'MIXTE': combinaison de la deformation et de la vorticite
        (Dacles-Mariani et al., AIAA Journal 33(9), 1995)

        P = { |R| + Cprod*Min(0,|S|-|R|) }²

        avec Cprod=2

   Si les donnees GB et TN sont fournies, la production ou destruction
   d'energie turbulente d'origine thermique est prise en compte:

        G = (GB/sgt) * Grad(TN)

        avec sgt = 0.7 (Prandtl turbulent)

   La modelisation adoptee ici est inspiree par les travaux de W.Rodi.
   Seule les contributions stabilisatrices des forces de flottabilite
   sont considerees:

    - si Grad(T)*GB est negatif (stratification stable), la production
      totale est amoidrie comme suit:

        (P + G)(1 + c3.Rf)

        avec Rf = -G/(P+G) (Nombre de Richardson)
        c3 = 0.8

    - sinon, G=Rf=0 de sorte qu'une stratification instable ne modifie
      pas la production.

## PROG [Langage Base]
 Operateur PROG
 -------------- EVOL ENUM

 LREEL1 = PROG 1. 2. 3. 4. 5. ;

 Objet :

 L'operateur PROG fabrique un objet LREEL1 de type LISTREEL a partir
 d'un nombre arbitraire d'objets de type ENTIER ou FLOTTANT.

 La sous-directive PAS permet d'engendrer des nombres regulierement
 espaces, et la sous directive * permet d'engendrer plusieurs fois le
 meme nombre. Par ailleurs des options correspondant a certaines
 fonctions sont disponibles.

 Commentaire :

 |  Sous-directive PAS  |

 LREEL1 = PROG 1. PAS 2. 5. ; equivaut a : LREEL1 = PROG 1. 3. 5. ;

 Si le PAS ne divise pas exactement l'intervalle, est retenue la
 valeur la plus proche le permettant.
 Si le PAS est incoherent, le resultat contiendra la valeur
 initiale et la valeur finale.

 Autre possibilite :

 LREEL1 = PROG 1. PAS 1. GEOM 2. 8. ;

 equivaut a :

 LREEL1 = PROG 1. 2. 4. 8. ;

 Dans ce cas, le pas est pondere par la suite geometrique de raison 2.
 Si le PAS ne divise pas exactement l'intervalle, est retenue la
 valeur par exces la plus proche le permettant.
 Si le PAS est incoherent, le resultat contiendra la valeur
 initiale et la valeur finale.

 Autre possibilite :

 LREEL1 = PROG 1. PAS 2. NPAS 2 ; equivaut a : LREEL1 = PROG 1. 3. 5. ;

 NPAS doit etre positif ou nul.

 Autre possibilite :

 LREEL1 = PROG 1. PAS 1. GEOM 2. NPAS 3 ;

 equivaut a :

 LREEL1 = PROG 1. 2. 4. 8. ;

 Dans ce cas, le pas est pondere par la suite geometrique de raison 2.

 |  Sous-directive  *  |

 LREEL1 = PROG 4 * 3. ; equivaut a : LREEL1 = PROG 3. 3. 3. 3. ;

 On peut utiliser des pas negatifs et utiliser ensemble les sous-
 directives.

 LREEL1 = PROG 1. 2. PAS -2. -6. 2. 3 * 9. PAS 2. 3. * 13. ;
 or
 LREEL1 = PROG 1. 2. PAS -2. NPAS 4 2. 3 * 9. PAS 2. 3. * 13. ;
 equivaut a
 LREEL1 = PROG 1. 2. 0. -2. -4. -6. 2. 9. 9. 9. 11. 13. 13. 13.;

 |  Option  SINU  |

 LREEL1 = PROG 'SINU' FLOT1 ('PHAS' FLOT2) ('AMPL' FLOT3) ...

        ...  | PROG 1. 2. ..X.. 4. 5.  |  ;
        | LREEL2  |

 L'option SINU de l'operateur PROG permet d'engendrer une liste de
 sinus de reels a partir :

    - d'un nombre arbitraire d'objets de type ENTIER ou FLOTTANT
    - d'un objet de type LISTREEL

 A X on associe ( FLOT3 * SIN ( 360*FLOT1*X + FLOT2 ) )

 LREEL2 : objet de type LISTREEL

 FLOT1 : frequence en Hz (type FLOTTANT positif)

'PHAS' : mot-cle suivi de :
 FLOT2 : valeur de la phase en degres (type FLOTTANT),
        egale a 0. par defaut.

'AMPL' : mot-cle suivi de :
 FLOT3 : valeur de l'amplitude du sinus (type FLOTTANT
        positif), egale a 1. par defaut.

 Remarque :

 Il est naturellement possible d'utiliser les directives PAS et *
 pour cette option .

 |  Options  LINE , EXPO , LOGA  |

        |'LINE'|
 LREEL1 = PROG |'EXPO'| ('A' A1) ('B' B1) | PROG 1. 2. ..X.. 4. 5. |
        |'LOGA'|  | LREEL2  |

 Les options 'LINE', 'EXPO' et 'LOGA' calculent les valeurs des
 fonctions :

    A1*X+B1 pour l'option 'LINE'
    EXP(A1*X+B1) pour l'option 'EXPO'
    LOG(A1*X+B1) pour l'option 'LOGA'

 pour les valeurs de la variable X contenues dans l'objet LREEL2 de
 type LISTREEL ou definies apres le mot cle 'PROG'.

 LREEL2 : objet de type LISTREEL

'A' : mot-cle suivi de :
 A1 : valeur de type FLOTTANT, egale a 1. par defaut.

'B' : mot-cle suivi de :
 B1 : valeur de type FLOTTANT, egale a 0. par defaut.

 |  option TABLE |

 LREEL1 = PROG 'TABL' TAB1 ;

 L'option 'TABL' crée la liste de reels indicés par des
 entiers dans la table TAB1. On donne la liste dans l'ordre
 croissant des indices de la table.

 TAB1 : objet de type TABLE

 LREEL1 : objet de type LISTREEL

 Remarque : si TAB1 contient d'autres types d'indices que des
 ---------- entiers, ceux-ci sont ignorés.

## PROI [Mathematiques Autres]
 Operateur PROI

OBJ1 = PROI | GEO2  CHEL1  | (FLOT1)  | ; (1)
        | MOD2  (CARA) CHEL1  (MOT2)|  |  (2)
        | MOD2  (CARA) CHEL1  'MINI' (ENT1)  |  (3)
        | 'POLY' GEO1 GEO2 CHPO1 ENT2 MOT1 ('POID' X1 X2) |  (4)

 Objet:

 L'operateur PROI effectue la projection des composants d'un MCHAML
 defini aux noeuds d'une geometrie donnee soit sur une nouvelle
 geometrie GEO2, soit sur les noeuds (par defaut) ou les points
 d'intégration d'un modele MOD2 (si MOT2 est present et different de
 'NOEUDS').

 Pour les syntaxes 1 et 2, les nouvelles valeurs sont obtenues par
 interpolation avec les fonctions de forme a partir des valeurs
 initiales et definissent un champ par points sur la nouvelle
 geometrie. Ce champ est de nature diffuse si le champ resultat est
 un champ par point.

 Commentaire :

 OBJ1 : Champ apres projection
        type CHPOINT pour les syntaxes (1) et (4)
        type MCHAML pour les syntaxes (2) et (3)

 GEO2 : Nouvelle geometrie (type MAILLAGE) sur laquelle on veut
        projeter le champ CHEL1

 MOD2 : Modele (type MMODEL) contenant les nouveaux points supports
        (noeuds ou points d'intégration) sur lesquels on veut
        projeter les valeurs du champ CHEL1

 CARA : Caracteristiques associees au modele MOD2 (type MCHAML,
        sous-type CARACTERISTIQUES) pour les elements coque
        (attention : on rappelle que ce champ doit etre donne avant
        CHEL1 si CHEL1 est également de sous-type CARACTERISTIQUES)

 CHEL1 : Champ par elements (type MCHAML) que l'on veut projeter. Il
        doit être defini aux NOEUDS du massif

 MOT2 : Mot precisant la localisation des point ou sera defini le
        champ. Par defaut aux 'NOEUDS' ou aux points d'integration
        au choix 'GRAVITE', 'RIGIDITE', 'MASSE' ou 'STRESSES'

 FLOT1 : Critère de rattrapage pour les points de GEO2 ou MOD2
        situés légèrement en-dehors du domaine de CHEL1
        Valeur par défaut : 1.e-5

 'MINI' : Si ce mot 'MINI' est present, l'evaluation est faite
        pour chaque composante par minimisation de l integrale
        (Ue-Us)**2 sur chaque element du support de sortie
        Ue : valeur de la composante au point courant dans
        le champ origine
        Us : valeur de la composante au point courant dans
        le champ resultat

 ENT1 : Si le mot-clef 'MINI' est present, on peut donner le nombre
        de points d'integration utilises par direction pour evaluer
        l'integrale (3 par defaut, i.e. 9 points pour une surface
        et 27 pour un volume) en précisant l'entier ENT1

 'POLY' : Si le mot-clef 'POLY' est present, l'operateur PROI
        effectue la projection sur GEO2 des composantes
        d'un CHPOINT CHPO1 defini sur GEO1. Il calcule aussi les
        derivees premieres et secondes du champ par rapport aux
        variables X et Y. Cette option marche en axisymmetrique et
        en dimension 2. (Voir remarque b pour plus de details)

 ENT2 : Si le mot-clef 'POLY' est present, l'entier ENT2 precise le
        type de symetrie :
        1 : pas de symetrie
        2 : symetrie par rapport a l'axe X
        etc.....

 CHPO1 : Champ par point (type CHPOINT) a projeter

 GEO1 : Geometrie associee a CHPO1

 MOT1 : Mot 'PLAN' ou 'AXIS'

 'POID' : Mot-clef facultatif introduisant la donnee de deux poids
        pour l'interpolation des fonctions. Ils valent 1 par defaut
     X1 : Poids des premiers voisins
     X2 : Poids des secondes voisins

 Remarques :

 a) Le champ par element CHEL1 doit obligatoirement etre supporte par
    des element massifs

 b) Avec l'option POLY :
    L'operateur effectue la projection sur GEO2 des composantes d'un
    CHPOINT CHPO1 defini sur GEO1. Il calcule aussi les derivees
    premieres et secondes du champ par rapport aux variables X et Y.
    Cette option marche en axisymmetrique et en dimension 2.

    La methode POLY consiste pour chaque point de GEO2 a selectionner
    les premiers voisins et les seconds puis d'ajuster au mieux des
    fonctions polynomiales connaissant les valeurs aux points voisins
    et leur poids.

    Les fonctions polynomiales sont obtenues a partir du
    developpement en serie entiere des fonctions complexes.
    L'ajustement est fait par la methode des moindres carres (on
    attribue des poids aux premiers et aux seconds voisins).

    Les derivees sont obtenues en derivant les fonctions polynomiales.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PROJ [Maillage Manipulation]
    Operateur PROJETER
  | 1ER CAS|

   GEO1 = GEO2 PROJ |('CYLI') VEC1  | |'PLAN' POIN1  POIN2  POIN3;
        | 'CONI'  SOMM1 | |'SPHE' CENTR1 POIN1;
        |'CYLI' CENTR1 CENTR2 POIN1;
        |'CONI' SOMM2  AXEI1  POIN1;
        |'TORI' CENTR1 AXEI1  CENTR2 POIN1
        |'DROI' POIN1  POIN2;
        |'CERC' CENTR1 POIN1;

    Objet :

    L'operateur PROJ construit un objet GEO1 resultant de la projection
d'un objet GEO2 suivant un vecteur (projection CYLIndrique) ou de la
projection radiale de sommet donne (projection CONIque).

    Commentaire :

    GEO2 : geometrie a projeter (type MAILLAGE)

    'CYLI' : mot-cle indiquant une projection cylindrique suivi de :
    VEC1 : vecteur (type POINT) utilise dans la projection cylindrique

    'CONI' : mot-cle indiquant une projection conique suivi de :
   SOMM1 : centre de la projection conique (type POINT)

    La projection se fait sur differents supports geometriques suivant l
mot-cle :

   'PLAN' : sur un plan definit par trois points POIN1, POIN2 et POIN3
        (type POINT)

   'SPHE' : sur une sphere de centre CENTR1 (type POINT) passant par le
        point POIN1 (type POINT)

   'CYLI' : sur un cylindre d'axe passant par CENTR1 et CENTR2 (type
        POINT) et contenant le point POINT1 (type POINT)

   'CONI' : sur le cone de sommet SOMM2 (type POINT), dont l'axe passe
        par le point AXEI1 (type POINT) et contenant le point POIN1
        (type POINT)

   'TORI' : sur le tore de centre CENTR1 (type POINT), dont l'axe passe
        par le point AXEI1(type POINT), dont un centre de petit
        cercle est CENTR2 (type POINT) et passant par le point POIN1
        (type POINT)

   'DROI' : sur une droite (en 2D) passant par les points POIN1 et POIN2
        (type POINT)

   'CERC' : sur un cercle (en 2D) de centre CENTR1 (type POINT) passant
        par le point POIN1 (type POINT)

   | 2EME CAS |

      GEO1 = GEO2 PROJ 'CYLI' DIR GEO3
        'CONI' P1 GEO3

    Objet :

    L'operateur PROJ effectue la projection cylindrique d'un objet
    GEO2 sur un objet GEO3 suivant la direction DIR, ou la
    projection conique de sommet P1 d'un objet GEO2 sur un objet GEO3.
    L'objet resultant de l'une ou l'autre des projections est GEO3.

    Commentaires :

     GEO1 : objet (type maillage) resultant de la projection.

     GEO2 : objet (type maillage) que l'on projette.

     CYLI : mot cle designant la projection cylindrique.

     CONI : mot cle designant la projection conique.

     DIR : direction de la projection cylindrique (type point).

     P1 : sommet de la projection conique (type point).

     GEO3 : objet (type maillage) sur lequel on projette.

## PROJGRIL [—] (proc)
 Procedure PROJGRIL

 MAIL1 CHP1 = PROJGRIL NUAG1 (LISMO1 si n > 2) (LISRE1 si n > 2) ;

 Objet :

 Cette procedure construit la projection d'un NUAGE, representant une
 fonction de n variables definie sur une grille de points, dans un
 plan de 2 composantes de la grille.
 Le plan de la projection se definit en fixant n-2 composantes de la
 grille (voir exemples ci dessous). La projection se fait alors dans
 les deux dimensions non fixees.
 Cette procedure peut etre utilie afin de visualiser les valeurs d'un
 tel nuage (pour verification par exemple).

 Commentaire :

 NUAG1 : NUAGE representant la fonction de n variables definie sur
        une grille de points (voir notice de IPOL option 'GRILL').

 LISMO1 : LISTMOTS contennant les noms des composantes fixees de
        NUAG1 (seulement si n > 2, le nombre de composantes fixees
        doit etre egal a n-2).

 LISRE1 : LISTREEL contennant les valeurs des composantes fixees
        (seulement si n > 2, de meme taille que LISMO1).

 MAIL1 : MAILLAGE d'elements QUA4 ou chaque noeud est un point de la
        grille "coupee" par la projection. Les noeuds de MAIL1 sont
        positionnes selon les deux composantes non fixees :
        - la 1ere coordonnee des noeuds correspond a la 1ere
        composante du NUAGE non fixee ;
        - la 2eme coordonnee des noeuds correspond a la 2eme
        composante du NUAGE non fixee.

 CHP1 : CHPOINT des valeurs de la fonction aux noeuds de MAIL1.

 Remarques :

 La construction d'un NUAGE representant une grille est decrite dans
 la notice de IPOL option 'GRILL'.
 Dans le cas d'un plan ne passant par les points de la grille, une
 interpolation multi-lineaire est effectuee.

 Exemples :

 1) Grille de dimension 2. Dans ce cas, il n'y a pas de projection a
    effectuer, on ne fixe pas de composantes, le nuage est represente
    dans son integralite.

       NUA1 = NUAG 'COMP' 'X' (PROG 0. 1. 2.)
        'COMP' 'Y' (PROG -1. 1.)
        'COMP' 'F' (PROG 4. 8. 15. 16. 23. 42.) ;
       MAIL1 CHP1 = PROJGRIL NUA1 ;
       TRAC CHP1 MAIL1 ;

     Ce qui donnera le champ suivant :

    Y
    ^
    |
    |  16.  23.  42.
 1 - O---------O---------O
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |4.  |8.  |15.
-1 - O---------O---------O
    |
    |
 0  --------|---------|---------|---------> X
        0 1 2

 2) Grille de dimension 3. Dans ce cas, il faut fixer une composante
    pour faire la projection (ici on projette dans le plan Y=0.)

       NUA1 = NUAG 'COMP' 'X' (PROG 0. 1. 2.)
        'COMP' 'Y' (PROG -1. 1.)
        'COMP' 'Z' (PROG 1. 3.)
        'COMP' 'F' (PROG 4. 8. 15. 16. 23. 42.
        8. 42. 23. 15. 4. 16.) ;
       MAIL1 CHP1 = PROJGRIL NUA1 (MOTS 'Y') (PROG 0.) ;
       TRAC CHP1 MAIL1 ;

     Ce qui donnera le champ suivant :

    Z
    ^
    |
    |  11.5  23.  19.5
 3 - O---------O---------O
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |  |  |
    |  |10.  |15.5  |28.5
 1 - O---------O---------O
    |
    |
 0  --------|---------|---------|---------> X
        0 1 2

## PROL [Mathematiques Autres]
Operateur PROL

EVOL2  =  PROL | (BORN) |  EVOL1  FLOT1  (FLOT2)  ;
        |  LINE  |

Objet :

    L'operateur PROL prolonge une fonction definie par un objet
evolution (EVOL1) en un (ou deux) point(s) des abscisses situe(s)
hors de son intervalle de definition (liste des abscisses).

    Le prolongement est effectue en prenant la valeur a la borne
de l'intervalle de definition la plus proche (option BORN) ou en
extrapolant lineairement la fonction (option LINE).

Commentaire :

EVOL1 : objet EVOLUTION, fonction que l'on souhaite prolonger
        hors de son domaine de definition.

FLOT1 : objet FLOTTANT, valeur des abscisses a laquelle on
        souhaite prolonger la fonction.

FLOT2 : objet FLOTTANT, valeur des abscisses a laquelle on
        souhaite prolonger la fonction.

EVOL2 : objet EVOLUTION, prolongement de EVOL1 en FLOT1
        (et FLOT2).

Remarques :
    Si FLOT1 (ou FLOT2) est dans l'intervalle de definition de
EVOL1, alors il est ignore.

## PROP [Changement_De_Phase Changement_De_Phase]
    Operateur PROP
    -------------- SOUR RESO

      PROP1 = 'PROP' MOD1 PROP0 QLINT CHP1 ;

    Objet :

    L'operateur 'PROP' calcule le champ par element de proportion de
phase pour une formulation de type 'CHANGEMENT_PHASE'.
Cet operateur est automatiquement appele dans la procedure TRANSNON.

      Commentaire :

      MOD1 : objet de type MMODEL contenant une formulation de type
        'CHANGEMENT_PHASE'.

      PROP0 : objet de type MCHAML contenant les proportions de phases
        initiales.

      QLINT : objet de type MCHAML contenant la quantite latente
        integree sur l'element (aux NOEUDS) avec l'operateur 'SOUR'.

      CHP1 : objet de type CHPOINT contenant les reactions associees
        aux matrices de blocages du changement de phases. De maniere
        classique, ce champ sort directement de 'RESO'

      PROP1 : nouveau MCHAML de proportions de phases.

## PROPAG [Mecanique Rupture] (proc)
    Procedure PROPAG

    EVOL1 = PROPAG TAB1 ;
        TAB1.'METHODE' TAB1.'COUTRA'
        TAB1.'JDA' TAB1.'YOUN'
        TAB1.'SIG1' TAB1.'SIGF'
        TAB1.'REXT' TAB1.'EPAI'
        TAB1.'ANGLE' TAB1.'COUL'
        TAB1.'ALFA' TAB1.'N'

    Objet :

   Cette procedure est specifique a l'element de tuyauterie fissuree
TUFI . Elle permet de determiner la loi de comportement globale
moment-rotation de l'element incluant la propagation de fissure
a partir de la courbe de traction et de la courbe de resistance
a la dechirure du materiau ,en appliquant:
   - soit une methode simplifiee (quatre methodes sont disponibles
     correspondant respectivement aux mots-cles TADA,LBBNRC,LBB1,LBB2)
   - soit une base de donnees experimentales (mot-cle DEFR)
pour la prise en compte de la plasticite.

   La procedure cree un objet evolution pouvant etre directement
   introduit en donnees de l'operateur MATE (composante TRAC) pour
   l'element TUFI.

   Commentaire :

   EVOL1 : objet (type EVOLUTION) decrivant la courbe moment-rotation

   TAB1 : objet (type TABLE) contenant :

      TAB1 METHODE : mot-cle (type MOT) valant DEFR, TADA, LBBNRC,
        LBB1 ou LBB2 et indiquant la methode simplifiee
        utilisee
      TAB1 COUTRA : objet (type EVOLUTION) decrivant la courbe de
        traction du materiau
      TAB1 JDA : objet (type EVOLUTION) decrivant la courbe de
        resistance a la dechirure du materiau
      TAB1 YOUN : module d'Young (type FLOTTANT)
      TAB1 SIG1 : contrainte conventionnelle a 0.2% (type FLOTTANT)
      TAB1 SIGF : eventuellement contrainte d'ecoulement
        (type FLOTTANT)
      TAB1 REXT : rayon exterieur (type FLOTTANT)
      TAB1 EPAI : epaisseur
      TAB1 ANGLE : angle total de la fissure en degres
      TAB1 COUL : indique eventuellement la couleur (type MOT)
        affectee a la courbe creee
      TAB1 ALFA : eventuellement coefficients de la loi de type
      TAB1 N : Ramberg-Osgood qui permet de representer la
        courbe de traction du materiau (methode LBBNRC)
        (type FLOTTANT)

## PRRA [Mathematiques Fonctions]
Operateur PRRA

  TAB1 = PRRA MOD1 ;

Objet :

L'operateur PRRA met sous forme de table, exploitable par la procedure
charther, les données du rayonnement.

  Commentaire :

  MOD1 : objet modele de "thermique rayonnement"

  TAB1 : objet TABLE indicée de 1 a N pour les N conditions
  independantes de rayonnement

## PSATT [Thermique Resolution] (proc)
   Procedure PSATT

     P = PSATT T ;

   OBJET :

 La procedure PSATT calcule la pression partielle de vapeur pour la
temperature de saturation T.

   Commentaires

  T : Temperature de la vapeur (en K)
 La donnee d'entree est un CHPOINT, un FLOTTANT ou un LISTREEL.

  P : PSAT(T) (en Pa)

## PSCA [Mathematiques Autres]
    Operateur PSCAL
    --------------- PMIX

CHAP{Syntaxe avec des POINTS}

    FLOT1 = VEC1 PSCA VEC2 ;

PART{Objet}
    L'operateur PSCA effectue le produit scalaire de deux vecteurs.

PART{Commentaire}
    VEC1, VEC2 : vecteurs (type POINT ou type TABLE, sous-type VECTEUR)
    FLOT1 : resultat du produit scalaire (type FLOTTANT)

CHAP{Syntaxe avec des CHPOINT ou des MCHAML}

    OBJ3 = PSCA OBJ1 OBJ2 LMOTS1 LMOTS2 ;

PART{Objet}
    L'operateur PSCA effectue le produit scalaire de deux champs par
    points ou de deux champs par elements. Le resultat est obtenu en
    faisant en chaque point la somme des produits des composantes
    definies pour chaque champ.

PART{Commentaire}
    OBJ1 : champ par points (type CHPOINT ou MCHAML )
    OBJ2 : champ par points (type CHPOINT ou MCHAML )
    LMOTS1 : liste des composantes (type LISTMOTS) du premier champ
    LMOTS2 : liste des composantes (type LISTMOTS) du second champ
    OBJ3 : objet resultat (type CHPOINT ou MCHAML )

PART{Exemple}
    Si les composantes du premier champ sont UX,UY,UZ et celles du
    second sont FX,FY,FZ, on calculera en chaque point support
        (UX*FX)+(UY*FY)+(UZ*FZ).

    NOTA: pour les champs par elements, sous zones, points supports,
    harmoniques doivent imperativement etre identiques pour les champs
    d'entree (operer prealablement les conversions necessaires
    ( CHANGER , REDUIRE ... )

## PSIP [Mathematiques Autres]
 Operateur PSIP

 CHP1  | = PSIP MAIL1 MAIL2 (CRIT1) |  | ;
 CHP1 CHP2  |  | 'DEUX' | P1 (P2) |
        |  |  | MAIL3  |
 CHP1 CHP2 CHP3 |  | 'TROI' | P1 (P2) |

 Objet :

Pour les points de MAIL1, l'operateur calcule le champ de distance
euclidienne au maillage MAIL2 (compose de seg2 en 2D et de tri3/qua4
en 3D).
Cette distance est signee suivant l'orientation de MAIL2.
L'utilisation de CRIT1 permet d'exclure du champs resultat CHP1 les
points situes a une distance (en norme infinie) superieure a CRIT1.

Si l'option 'DEUX' est utilisee, un second champ CHP2, orthogonal au
premier, donne en 2D la distance signee par rapport a la droite
perpendiculaire a MAIL2 en son extremite P1, et en 3D au plan
perpendiculaire a MAIL2 passant par MAIL3 (maillage de seg2).
En 2D, dans le cas ou deux pointes sont donnees, la distance signee
CHP2 est calculee par rapport a la pointe la plus proche.

Avec l'option 'TROI' (uniquement possible en 3D), un troisieme champ
CHP3 orthogonal aux deux premiers vient completer la base.

 Commentaire :

CHP1 : objet CHPOINT de distance signee dont le nom de composante
        est PHI

CHP2 : objet CHPOINT de distance signee dont le nom de composante
        est PSI

CHP3 : objet CHPOINT de distance signee dont le nom de composante
        est TAU

MAIL1 : maillage donnant les points pour lesquels on veut les champs

MAIL2 : maillage en 2D de seg2 et en 3D de tri3

'DEUX': Mot option demandant le calcul du deuxieme champ.

P1 : point extremite de la ligne MAIL2

P2 : 2eme point extremite de la ligne MAIL2

MAIL3 : maillage de seg2

CRIT1 : distance minimale pour laquelle CHP1 et CHP2 doivent etre
        evalues

 Remarque :

Lors d'une modelisation avec des elements finis etendus en
mecanique de la rupture (XFEM),
-CHP1 et CHP2 sont les level set decrivant le repere local de fissure.
-MAIL2 represente la fissure ou le plan de la fissure.
-En 2D, P1 (et P2) represente(nt) la (les) pointe(s) de fissure.
-En 3D, MAIL3 represente le front de fissure.

## PSMO [Mecanique Dynamique]
    Operateur PSMO

    SOLUT  =  PSMO |  STRU1  MOD1  ( LIAI1 )  | ('FREQ' XFREQ )
        | RIGT  ( MAST )  TBA1 ( TLIAI ) |

        ...  ('SEISME'('UX') ('UY') ('UZ') )  (| CHPO1 |)  ;

    Objet :

    L'operateur PSMO permet de calculer, lors d'un calcul par
recombinaison modale, la contribution des modes negliges non pris
en compte dans la base modale. Ces modes sont supposes avoir une
reponse quasi-statique.

    Commentaire :

     STRU1 : objet de type STRUCTURE

     MOD1 : objet de type SOLUTION, contenant les modes de la
        structure

     LIAI1 : objet decrivant les liaisons non permanentes (chocs)
        existant sur la structure (type ATTACHE).

     RIGT : objet de type RIGIDITE, matrice de raideur de la
        structure

     MAST : objet de type RIGIDITE, matrice de masse de la
        structure

     TBA1 : objet de type TABLE de sous-type BASE_DE_MODES,
        issu de la procedure TRADUIRE

     TLIAI : objet de type TABLE de sous-type 'POINT_DE_LIAISON',
        indice de 1 a N points de choc, contenant :
        - TLIAI.I.'POINT' = le point de choc (type POINT)
        .'NORMALE' = la normale de choc (type POINT)

     CHPO1 : objet contenant la description spatiale des chargements
        (cas des forces concentrees) ou des supports (cas
        d'une structure multisupportee) (type CHPOINT)

     LCHP1 : objet contenant plusieurs CHPOINTs (type LISTCHPO)

    'SEISME' : mot-cle indiquant que la structure est soumise a une
        excitation sismique.

    'UX' : mot-cle, direction de l'excitation suivant X.

    'UY' : mot-cle, direction de l'excitation suivant Y.

    'UZ' : mot-cle, direction de l'excitation suivant Z.

    'FREQ' : mot-cle indiquant, dans le cas oº la structure a des
        modes de corps solide, que l'utilisateur veut imposer
        la frequence a laquelle on etudiera la reponse de la
        structure.

     XFREQ : valeur de la frequence (type FLOTTANT).

     SOLUT : objet resultat
        - de type SOLUTION de sous-type PSEUMODE, si on a donne
        les modes de la structure dans un objet SOLUTION.
        - de type TABLE de sous-type PSEUDO_MODE, si on a donne
        les modes de la structure dans un objet TABLE.
        Description de SOLUT :
        TABLE indicee par des ENTIERs I variant de 1 a N
        SOLUT . I . 'DEPLACEMENT' = pseudo-mode calcule
        (type CHPOINT)
        cas d'une structure monosupportee (option SEISME)
        . 'DIRECTION' = 1, 2, ou 3
        direction du seisme
        cas d'une force concentree
        ou structure multisupportee
        . 'CHAMP_BASE_B' = pointeur du CHPOINT
        pour lequel on a calcu-
        le le pseudo-mode
        . 'CHAMP_BASE_A' = pointeur du CHPOINT
        BASE_B projete sur la
        base modale.
        cas d'une force de choc
        . 'POINT' = point de choc
        . 'NORMALE' = normale de choc

    Remarques :

    * Cas d'une structure monosupportee

      La structure est soumise a une acceleration sismique d'ensemble
unitaire dans la direction donnee.
        Lors de la demande de recombinaison l'utilisateur donnera le
chargement reel.

        Exemple pour un seisme de direction UX :

        SOLUT = 'PSMO' STRU1 MOD1 'SEISME' 'UX' ;
        ou
        SOLUT = 'PSMO' RIGT MAST TBA1 'SEISME' 'UX' ;

    * Cas d'une structure multisupportee

      On associe a chaque pseudo-mode un CHPOINT.
Le pseudo-mode est calcule a partir du champ contenant les
deplacements des points supports.
      Lors de la demande de recombinaison l'utilisateur donnera le
chargement reel.

       Exemple :

        SOLUT = 'PSMO' STRU1 MOD1 'SEISME' CHPO1 ;
        ou
        SOLUT = 'PSMO' RIGT MAST TBA1 'SEISME' CHPO1 ;

    * Cas d'une force concentree

      On associe a chaque pseudo-mode un CHPOINT.
      Lors de la demande de recombinaison l'utilisateur donnera le
chargement reel.

       Exemple pour une force concentree :

        SOLUT = 'PSMO' STRU1 MOD1 CHPO1 ;
        ou
        SOLUT = 'PSMO' RIGT TBA1 CHPO1 ;

    * Cas d'une force de choc

      On associe a chaque pseudo-mode un CHPOINT.

       Exemple pour une force de choc :

        SOLUT = 'PSMO' STRU1 MOD1 LIAI1 ;
        ou
        SOLUT = 'PSMO' RIGT TBA1 TLIAI ;

## PSRS [Mathematiques Traitement]
Operateur PSRS

EVOL1 = PSRS EVOL2 FLOT1 LREEL1 (LREEL2 MOT1 MOT2 MOT3 COUL1);

objet :

Calcul des N spectres de reponse EVOL1 associes au spectre de
puissance EVOL2 (comportant une unique courbe) d'un signal de
dure FLOT1 (REEL) et aux N amortissements contenu dans LREEL1.

options :

- Le calcul des spectres de reponse s'effectue sur une grille
  de periode de 75 points, compris entre 0.04s (25 Hz) et FLOT1 et
  uniformement distribue dans un espace logarithmique. Une grille
  alternative peut etre donnee en option dans LREEL2.

- MOT1 represente la grandeur physique de reponse:
  'ACCE'(leration), 'VITE'(sse) ou 'DEPL'(acement relatif). Le
  defaut est 'ACCE'.

- MOT2 represente le type de distribution choisi pour evaluer le
  lieu des maxima du spectre de reponse: 'CRAM'(er) ou 'NEWG'(umg).
  Le defaut est 'CRAM'.

- MOT3 represente la grandeur en abscisse de EVOL1:
  'PERI'(ode) ou 'FREQ'(uence). Le defaut est 'PERI'.

- COUL1 represente la couleur de l'objet cree.
  Par defaut c'est la couleur de EVOL2.

## PVEC [Mathematiques Autres]
    Operateur PVEC
    -------------- PMIX

CHAP{Syntaxe avec des POINTS}

    VEC3 = VEC1 PVEC (VEC2 si 3D) ;

PART{Objet}
    L'operateur PVEC effectue le produit vectoriel (note x)
    de n-1 vecteurs, n etant la dimension de l'espace (n=2 ou 3).
    Le resultat est le vecteur :
        VEC3 = | e_Z  x VEC1  en 2D
        | VEC1 x VEC2  en 3D

PART{Commentaire}
   VEC1, VEC2 : vecteurs (type POINT)
   VEC3 : objet resultat (type POINT)

CHAP{Syntaxe avec des CHPOINT ou des MCHAML}

    OBJ3 = PVEC OBJ1 LMOTS1 (OBJ2 LMOTS2 si 3D) LMOTS3 ;

PART{Objet}
    L'operateur PVEC effectue le produit vectoriel de n-1 champs par
    point/element, n étant la dimension de l'espace (n=2 ou 3).
    En dimension 2, le resultat est le champ par point/element de
    composantes (-y, x), où x et y sont les composantes de OBJ1.

PART{Commentaire}
    OBJ1, OBJ2, OBJ3 : champ (type CHPOINT ou MCHAML)
    LMOTS1, LMOTS2, LMOTS3 : liste des composantes (type LISTMOTS),
    de dimension n, associee a chaque champ, dans l'ordre du systeme de
    coordonnees retenu.

PART{Exemple}
    Avec :
      LMOTS1 = MOTS 'U,X' 'U,Y' 'U,Z' ;
      LMOTS2 = MOTS 'V,X' 'V,Y' 'V,Z' ;
      LMOTS3 = MOTS 'W,X' 'W,Y' 'W,Z' ;
    OBJ3 aura la structure :
      W,X = (U,Y * V,Z) - (U,Z * V,Y)
      W,Y = (U,Z * V,X) - (U,X * V,Z)
      W,Z = (U,X * V,Y) - (U,Y * V,X)

## QOND [Multi-physique Multi-physique]
   Operateur QOND

Objet : Calcule le flux de masse de vapeur d'eau condensee dans un
        melange air-vapeur au contact d'une zone froide (paroi ou
        condenseur volumique).

Syntaxe : M = QOND CP ALFAB ALFAT H TP PTOT YVAP YH2O <BETA> ;

M = BETA * H/CP *(ALFAB/ALFAT)**.666 *Ln[(PTOT-PSAT(TP))/(PTOT-PVAP)]
M = 0 si PVAP < PSAT(TP)

M : CHPOINT SCAL (densite de flux de masse de vapeur condensee
        [kg/m2/s])
CP : FLOTTANT (chaleur specifique vapeur [J/kg/K])
ALFAB : FLOTTANT (diffusivite brownienne [m2/s])
ALFAT : FLOTTANT (diffusivite thermique [m2/s])
H : CHPOINT SCAL (coeff d'echange thermique a la paroi [W/m2/K])
TP : CHPOINT SCAL (temperature paroi [K])
PTOT : CHPOINT SCAL (pression totale du melange [Pa])
YVAP : CHPOINT SCAL (fraction massique vapeur [vap/eau tot])
YH2O : CHPOINT SCAL (fraction massique eau [eau tot/gaz])
BETA : FLOTTANT (coefficient [option, par defaut beta=1])

Important: - Tous les CHPOINTs doivent avoir le meme support geom.
_________ et LE MEME POINTEUR SUR LE SUPPORT GEOMETRIQUE.
        - Il faut utiliser les UNITES S.I.
        - M aura le meme support geometrique que H,TP....
        - Bien respecter l'ordre des donnees.
        - ne fonctionne pas en vapeur pure (ie sans air)

## QUADRATU [Mathematiques Statistiques] (proc)
Procedure QUADRATU

TAB1 = QUADRATU MOT1 FLOT1 FLOT2 ENTI1;

Objet :

Cette procedure calcule les points et poids d'integration
associes a une densite de probabilite.

Commentaire :

MOT1 : type de loi ('NORM', 'LOGN', 'EXPO', 'UNIF')

FLOT1 : valeur moyenne (type REEL)

FLOT2 : ecart-type (type REEL)

ENTI1 : nombre de points d'integration (type ENTIER)

TAB1 : (type TABLE)

TAB1.i.POINT = i-eme point d'integration (type FLOTTANT)

TAB1.i.POIDS = i-eme poids d'integration (type FLOTTANT)

## QUEL [Maillage Lignes]
Operateur QUELCONQUE

LIG1 = QUELCONQUE  | 'SEG2' |  | POIN1 POIN2 ......  POINn | ;
        | 'SEG3' |  | LISTX (LISTY (LISTZ))  |
        | MAIL1  |

Objet :

L'operateur QUELCONQUE permet de construire une ligne brisee
constituee d'elements du type demande, passant :
- soit par les points donnes
- soit par les points dont les coordonnees sont fournies dans des
  listes de reels.
- soit a partir d'un maillage de points

Commentaire :

'SEG2' | mot-cle indiquant le type d'element souhaite.
'SEG3' |

 POINi : points definissant la ligne brisee (type POINT)

 LISTX : abscisses des points definissant la ligne brisee
        (type LISTREEL)

 LISTY : ordonnees des points definissant la ligne brisee
        (type LISTREEL)
        Cet operande n'est a donner qu'en 2D ou 3D.

 LISTZ : cotes des points definissant la ligne brisee
        (type LISTREEL)
        Cet operande n'est a donner qu'en 3D.

 MAIL1 : maillage constitue de points (type MAILLAGE)

 LIG1 : ligne brisee (type MAILLAGE)

 Remarque :

 Si le type est 'SEG3' :

 1) Il faut, suivant la syntaxe choisie, soit donner dans la
    liste les points intermediaires, soit prendre en compte les
    coordonnees des points intermediaires.

 2) Soit N le nombre de points a considerer. N-3 doit etre pair,
    afin que le dernier segment de la ligne ne soit pas incomplet.

## QUIT [Langage Methodes]
    Directive QUITTER
    ----------------- DEBM

    QUITTER OBJ1 ;

    Objet :

    La directive QUITTER sert a interrompre l'execution du bloc OBJ1,
ou de la procedure OBJ1. Le contrÔle est alors rendu a l'instruction
suivant la fin du bloc ou a l'instruction FINPRO de la procedure.

    Remarque :

    Si plusieurs blocs sont imbriques, il est possible de quitter celui
que l'on desire en indiquant son nom.

    Exemple :

    * calcul de la constante d'EULER

    * INITIALISATIONS
    I=0 ; CRIT= 1E-5; CRITM= CRIT*-1; C=0. ;
    EPS1= 0 ; OK = FAUX ;

    REPETER 50 BLOC1 ;

     I = I + 1; C = C + (1./ I) ;
     EPS = C - (LOG I) ;
     D = EPS - EPS1 ;

       SI ( (D < CRIT) ET (D > CRITM) ) ;

       OK = VRAI ;
       QUITTER BLOC1 ;

       FINSI ;

     EPS1 = EPS ;

     FIN BLOC1 ;

     SI OK ;
      LIST EPS ;
     SINON ;
      LIST 'RATE' ;
     FINSI ;
     FIN;

    Exemple d'utilisation de blocs imbriques :

    REPETER BLOC1 ;

    REPETER BLOC2 ;

      SI CONDITION ;
        QUITTER BLOC2 ;
      SINON ;
        QUITTER BLOC1 ;
      FIN BLOC2 ;
    FIN BLOC1 ;

## QULX [Mecanique Resolution]
    Operateur QULX

    CHPO1 = QULX RIG1 CHPO2 ;

    Objet :

    L'operateur QULX sert uniquement pour la procedure des appuis unila-
teraux. Il extrait d'un champ par points les multiplicateurs de Lagrange
existant dans une matrice de rigidite. Le champ par point obtenu est
de nature discrete.

    Commentaire :

    RIG1 : matrice de rigidite (type RIGIDITE)

    CHPO2 : champ par point (type CHPOINT) contenant les multiplicateurs
        de Lagrange

    CHPO1 : multiplicateurs de Lagrange (type CHPOINT)

## RACC [Maillage Autres]
    Operateur RACCORD

    | 1ere possibilite : creation d'un element de raccord ordinaire |

    GEO3 = RACC (FLOT1) GEO1 GEO2 ;

    Objet :

    L'operateur RACCORD engendre une ligne GEO3 de points doubles en
raccordant les objets GEO1 et GEO2 (lignes en 2D).

    Commentaire :

    GEO1, GEO2 : objets a raccorder (type MAILLAGE)

    GEO3 : ligne de raccordement (type MAILLAGE)

    FLOT1 : critere de distance (type FLOTTANT)
        (voir remarque ci-dessous)

    Remarque :

    Les objets GEO1 et GEO2 sont des SEGMENTS a 2 ou 3 points.
    Utiliser l'operateur LIAISON pour des maillages surfaciques en 3D.

    Un element est cree entre un element de l'objet GEO1 et un element
de l'objet GEO2 distants point a point de moins d'un critere FLOT1
(type FLOTTANT), egal, par defaut, au dixieme de la densite courante.

    Si l'objet GEO3 doit etre utilise comme raccord fluide-structure,
il est imperatif que le premier objet GEO1 soit l'objet fluide et que
le second objet GEO2 soit l'objet solide.

    Pour la creation d'un element joint JOI2, JOI3 (2D) :

        -GEO1 et GEO2 definissent respectivement les lignes 1 et 2
de cet element. Ces lignes doivent etre parcourues dans le meme sens.
Ce sens est defini par celui de la ligne 1, et tel que si un
observateur la parcourt selon ce sens, il doit voir le joint
a sa droite.

        -Pour la prise en compte d'un jeu initial x dans un element
joint, GEO1 et GEO2 doivent etre distants de x. De plus, x doit etre
rentre comme deformation inelastique normale initiale lors de l'appel
a PASAPAS (cf rapport DMT/93.655).

    | 2eme possibilite : creation d'un element de raccord poreux |

    GEO4 = RACC (FLOT1) GEO1 GEO2 GEO3 ;

    Objet :

    L'operateur RACCORD engendre une ligne GEO4 de points doubles ou
    triples en raccordant les objets GEO1, GEO2 et GEO3.

    Commentaire :

    GEO1, GEO2, GEO3 : objets a raccorder (type MAILLAGE)

    GEO4 : ligne de raccordement (type MAILLAGE)

    FLOT1 : critere de distance (type FLOTTANT)
        (voir remarque)

    Remarque :

    Les objets GEO1 et GEO2 sont des SEGMENTS a 3 points. L'objet GEO3
    est un SEGMENT a 2 points.
    Un element est cree entre un element de l'objet GEO1, un element
    de l'objet GEO2 et un element de l'objet GEO3 distants point a point
    de moins d'un critere FLOT1 (type FLOTTANT), egal, par defaut,
    au dixieme de la densite courante.
    La convention est la meme que ci-dessus pour les JOI2 et JOI3, et
    GEO3 definit la ligne intermediaire.

## RACP [Mathematiques Fonctions]
    Operateur RACPOL

      XR1 ( XI2)  = RACPOL |(MOT1)  | LISTREE1 ( MOT1 )  ||;
        |  | A0  A1  A2  (A3) (A4)||
        | 'INTE' X1 X2 LISTREE1  |

    Objet :

    L'operateur RACP calcule les racines d'un polynome du Neme
degre .

      Commentaire :

      Le polynome est de la forme :

        A0 + A1*X + (A2*X**2) + (A3*X**3) + (A4*X**4) + ...
      avec A0 la premiere valeur du listreel LISTREE1, A1 la
      seconde valeur etc...

      Les racines reelles sont rangees par ordre croissant dans le
      listreel XR1. Si MOT1 prend la valeur IMAGINAIRE toutes les
      racines du polynome sont sorties. XR1, ordonne par ordre
      croissant, contient la partie reelle et XI2 contient la partie
      imaginaire.

      Le mot MOT1 peut aussi prendre comme valeur BAIRSTOW dans ce
      cas la methode de Bairstow est utilisee.

      Dans la seconde syntaxe seules les racines reelles sont sorties.

      L'option 'INTE' demande de chercher la premiere racine relle dans
      l'intervalle X1 X2. S'il n'y en a pas XR1 prend la valeur 'VIDE'.

## RAFF [Maillage Manipulation]
    Operateur RAFF

    1ere fonction : raffinement d'un maillage

      GEO2 = RAFF GEO1 CHPO1 ;

    Objet :

       L'operateur RAFF part d'un maillage existant (GEO1) pour le raffiner
    en respectant un champ de densite (CHPO1). Tant que la densite n'est
    pas atteinte un element est divise en sous elements etc...
    Le maillage genere contient le resultat de la division des elements
    plus des elements de types relations (itypel=22) qui permettent de
    realiser au mieux la conformite en deplacement des elements.

    Commentaire :

    Entrees :

      - GEO1 : Maillage initial

      - CHPO1 : Objet CHPOINT de densite

    Sortie :

      - GEO2 : Maillage final, contenant les relations a imposer.

    Remarque :

    Apres avoir raffiné un maillage il est nécéssaire de faire appel à
    l'opérateur RELA pour contruire les relations de conformité
    entre les différentes zones de raffinement.

    2e fonction : raffinement d'une liste de reels

      LRE2  =  RAFF  LRE1  | ENT1  ;
        [ FLOT1

    Objet

       L'operateur RAFF permet egalement de raffiner un LISTREEL.

    Commentaire

    Entrees :
      - LRE1 : objet LISTREEL, liste initiale.

      - ENT1 : objet ENTIER, nombre de sous-decoupages de chaque
        intervalle de la liste. ENT1 peut etre negatif
        (voir remarque).

      - FLOT1 : objet FLOTTANT, valeur cible de la taille
        des intervalles de la liste.

    Sortie :
      - LRE2 : objet LISTREEL, liste raffinee.

    Remarque 1

    Si ENT1 est negatif, la taille du decoupage de deux intervalles
    successifs de tailles differentes suit une progression geometrique.
    Le nombre d'intervalles peut alors etre different de celui attendu
    (abs(ENT1)).

    Remarque 2

    Si le LISREEL contient une succession de valeurs identiques,
    les intervalles entre ces veleurs sont egalement decoupes.
    Par exemple, la liste {1 1} raffinee d'un facteur 3 est
    la liste {1 1 1 1}.
    Ce comportement est souhaitable pour obtenir des LISTREEL
    de meme dimension en sortie de RAFF, quelles que soient
    les valeurs du LISTREEL en entree.

    Exemple d'utilisation de la 1ere fonction

    opti elem qua4 mode plan defo dime 2;
    dens 2.;
* mesh 10x6
    pa= 0 0; pb= 10 0;pc= 20 0;
    liab= pa droi pb;libc= pb droi pc;
    su = (liab et libc) trans ( 0 12);
    trac su;
* definition of density
    x y = coor su;
    distance = ((x - 10 ) * ( x- 10) + ( y * y)) ** 0.5;
    den = 0.3 + (0.18*distance);
    trac su den;
* new mesh
    su2= raff su den;
    hh = elem su2 SURE ;
    sureal = su2 diff hh ;
* use of this mesh
* definition of model and caracteristic
    mo= mode su2 mecanique elastique isotrope ;
    ma = mate mo YOUN 2.e5 NU 0.3 ;
* conformity relations
    rel = rela mo;
* loads
    psupe = su2 poin droite ( 0 12) ( 10 12) 0.1;
    lisupe = elem ( contour su2) appu stric psupe;
    ff = pres ( redu mo sureal) massif lisupe -1.;
* displacements conditions
    py0= point su2 droit pa pc 0.01;
    liy0= elem ( contou su2) appu strict py0;
    li2bc = liy0 elem compris pb pc;
    cl1= bloqu li2bc UY;
    cl2= bloq UX pb;
    cltot= cl1 et cl2;
* compute elastic solution
    ri = rigi mo ma;
    displa = reso ( ri et cltot et rel) ff;
    stre = sigma displa mo ma;
    vm = vmis stre mo ma;
    trac su2 vm mo ma;
* compute stress intensity factor
    gt = table;
    gt.'OBJECTIF' = MOT 'J';
    lifis = liy0 elem compris pa pb;
    gt.'LEVRE_SUPERIEURE' = lifis;
    gt.'FRONT_FISSURE' = Pb;
    gt.'CARACTERISTIQUES' = ma;
    gt.'MODELE' = mo;
    gt.'SOLUTION_RESO' = displa;
    rea = reaction (ri et rel) displa;
    gt.'CHARGEMENTS_MECANIQUES'=rea;
    naa = 5;opti veri 1;
    repe no naa;
      gt.'COUCHE' = &no;
      G_THETA gt;
      si ( &no ega 1) ; g2=prog gt.resultats;sinon;
      g2 = g2 et ( prog gt.resultats); finsi;
    fin no;
    xx = prog 1 pas 1 naa;
    ev= evol manu 'nb of rows' xx 'G ' g2;
    ttt=table;
    ttt.1 = mot 'MARQ CROI';
    tt2=table;
    tt2.1= ' G ';
    ttt.'TITRE'=tt2;
    dess ev lege ttt;
$$$$

## RAFT [Maillage Manipulation]
    Operateur RAFT

    SURF2 = RAFT (CHPO1) SURF1 (N1);

    Objet :

    L'operateur RAFT raffine un maillage triangulaire (objet
SURF1) pour respecter une carte de taille donnee par des valeurs
aux noeuds de SURF1 (objet CHPO1 ou directement les valeurs aux
noeuds). Aucun noeud n'est ajoute sur la frontiere, en revanche
des noeuds sont ajoutes a l'interieur du domaine pour que les
triangles aient la taille souhaitee. Le nombre de noeuds du
maillage resultant peut etre limite par l'utilisateur a une
valeur N1.

    Commentaire :

    SURF1: objet de type MAILLAGE. Il doit etre constitue exclu-
sivement de triangles.

    CHPO1: objet de type CHPOINT. Ce champ de point donne la
carte des tailles souhaitees. Chaque point correspond a un noeud
du maillage de SURF1.La valeur associee au noeud correspond a la
longueur souhaitee pour les elements incidents au noeud.
Si CHPO1 n'est pas donne on prend la densite locale affectee a
chaque noeud du maillage SURF1 lors de sa creation (voir TRIA).
Si elle est nulle (non fixee),on raffine pour ameliorer la forme
des triangles.

    N1 : objet de type ENTIER. C'est le nombre maximum de noeuds
que l'on souhaite dans le maillage resultant. Il ne peut etre
inferieur au nombre de noeuds deja presents dans SURF1.

    Remarques :

    Comme son nom l'indique le RAFFINEUR n'enleve aucun noeud
du maillage initial (SURF1) meme si ce dernier est trop dense
pour la taille souhaitee imposee (CHPO1).

    RAFT ne fonctionne que pour des triangles lineaires (TRI3).

## RAIN [Mathematiques Traitement]
Operateur RAIN

L'operateur RAIN effectue la decomposition d'un signal de contrainte
en une succession de cycles de contrainte elementaires en suivant
la methode de comptage rainflow. Le signal de contrainte en entree
doit etre une suite alternee de maxima et de minima.

L'operateur RAIN retourne les amplitudes des cycles de contrainte ainsi
que le residu, defini comme les extrema du signal d'entree n'appartenant a aucun
cycle de contrainte identifie.

|  Syntaxe :  |

LREE1 LREE2 = RAIN LREE3 ;

Commentaire :

LREE1 : Amplitudes des cycles de contrainte identifies (type LISTREEL)

LREE2 : Residu du signal d'entree, defini comme les extrema du signal
        n'appartenant a aucun cycle de contrainte identifie (type LISTREEL)

LREE3 : Signal de contrainte a traiter, doit etre une suite alternee
        de maxima et de minima (type LISTREEL)

## RAMBERG [Mecanique Modele] (proc)
 Procedure RAMBERG

     RAMBERG TAB1;

        TAB1.'COURBE_TRACTION'.'SIG0'.'EPS0'
        .'ALPHA'.'N'.'COUBE_RAMBERG'
        .'AJUSTEMENT'

 Objet :

       Etant donnee la courbe de traction d'un materiau,
  cette procedure permet d'ajuster sur cette courbe une
  loi de type Ramberg-Osgood :
        eps/eps0 = (sig/sig0) + (alpha * ((sig/sig0)**n))
  L'ajustement est effectue par regression lineaire des
  points de la courbe de traction en coordonnees log-log.

Commentaire :

    ENTREES :

       Une table TAB1 indicee par des mots .

    TAB1.'COURBE_TRACTION' : courbe de traction du materiau
        constitue par un objet de type
        EVOLUTION, avec en abscisse les
        deformations et en ordonnee les
        contraintes (les premiers points
        doivent deja contenir une partie
        plastique).

    TAB1.'SIG0' : valeur de la contrainte intervenant dans la
        loi de Ramberg-Osgood.

    TAB1.'EPS0' : deformation associee a la contrainte SIG0 dans
        la loi de Ramberg-Osgood.

     SORTIES :

       Une table indicee par des mots.

    TAB1.'ALPHA' : coefficient alpha de la loi Ramberg-Osgood

    TAB1.'N' : paramatre d'ecrouissage de la loi Ramberg-Osgood

    TAB1.'COURBE_RAMBERG' : objet de type EVOLUTION donnant la
        loi Ramberg-Osgood ajustee

    TAB1.'AJUSTEMENT' : coefficient d'ajustement de la loi par
        regression lineaire (AJUSTEMENT = 1
        ajustement parfait)

## RAVC [Mecanique Resolution]
 Operateur RAVC

 Objet :

Cet operateur est specifique a la procedure VITEUNIL

## RAY [Fluides Limites] (proc)
    Procedure RAY

    SYNTAXE (EQEX et EXEC) : Cf operateur EQEX et EXEC

  'ZONE' paroi 'OPER' RAY TABRA 'INCO' 'TN'

    OBJET :

Procedure permettant de prendre en compte du rayonnement (en cavite) dans
les operateurs 'EQEX' & 'EXEC' (couplage convection-rayonnement);
Se couple aux equations habituelles de Navier_Stokes (cf. conv_ray.dgibi)

        EN 2D
        elements lignes (SEG2 ou SEG3)
        EN 3D
        elements coques (QUA4 ou TRI3)

     Commentaires :

     paroi Objet MMODEL de type 'NAVIER_STOKES' associe a la
        surface

     TABRA table propre au rayonnement

     TN Champ de temperature (en K) CHPOINT SCAL SOMMET

 tabra . ma_rai = maillage rayonnement
 tabra . mm_rai = modele rayonnement (de type rayonnement)
 tabra . mr_rai = chamelem (issu de l'operateur rayonnement)

ENGL====================================================================

    DESCRIPTION :

Procedur allowing to take in consideration the radiation in the operators
'EQEX' & 'EXEC' (coupling convection_radiation);
Couple in usuel Navier_Stockes equations (cf. conv_ray.dgibi).

        IN 2D
        2D shell elements (SEG2 ou SEG3)
        IN 3D
        3D shell elements (TRI3 QUA4 )

     Comment:

     paroi MMODEL object 'NAVIER_STOKES' type associated to the surface

     TABRA Radiation table

     TN Temperature field CHPOINT SCAL SOMMET

 tabra . ma_rai = radiation mesch
 tabra . mm_rai = radiation model (type RAYONNEMENT)
 tabra . mr_rai = chamelem (from raye operator)

## RAYE [Thermique Modele]
    Operateur RAYE
    -------------- HRCAV CAV HRC

     CH2 = RAYE MODL1 CHAM1 CHAM2 ;
 ou
     CH2 = RAYE MODL1 CHAM1 CHAM2 CHAM3 (PREC) ('TABS' VAL);

    Objet :

    Cet operateur intervient dans la modelisation du rayonnement
 thermique dans une cavite contenant un milieu transparent
 ou un milieu absorbant a temperature uniforme.
    Il calcule:
- soit la matrice de rayonnement R telle que:
        Phi = R.T**4
- soit la temperature de rayonnement Trad associee a la valeur
  du champ de temperature T pour une iteration donnee telle que
        Phi = emis * stefan * (T**4 - Trad**4)

        (Phi: flux rayonne, emis: emissivite)

    Commentaire :

    MODL1 : structure modelisee (type MMODEL)

    CHAM1 : matrice des facteurs de forme (type MCHAML)

    CHAM2 : champ d'emissivite (type MCHAML)

    CHAM3 : champ de temperature (type MCHAML)

    PREC : precision relative du calcul de la radiosite
        par une methode iterative (type flottant)
        (valeur par defaut 1e-10)

    'TABS': mot-cle necessaire si la cavite contient
        un milieu absorbant a temperature uniforme

    VAL : temperature du milieu absorbant (type flottant)
        en degre K

    CH2 : matrice de rayonnement (type MCHAML)
        ou bien champ de temperature (type MCHAML)

## RAYN [Thermique Modele]
    Operateur RAYN
    -------------- RAYE

     CH2 = RAYN MODL1 CHAM1 CHAM2 (STEF) ;

    Objet :

    Cet operateur calcule la matrice de "conductivite" correspondant
a la linearisation du rayonnement en milieu transparent dans une
cavite.

    Commentaire :

    MODL1 : structure modelisee (type MMODEL)

    CHAM1 : matrice de rayonnement (type MCHAML)

    CHAM2 : champ de temperature (type MCHAML)

    CH2 : matrice de conductivite (type RIGIDITE)

    STEF : constante de Stefan-Boltzmann (par defaut 5.67e-8 Wm-2K-4)
        (type FLOTTANT)

    Remarque importante:
    L'unite de la temperature est obligatoirement le degre Kelvin.

## RDIV [Multi-physique Multi-physique] (proc)
   Procedure RDIV

   SYNTAXE ( EQEX ) : Cf operateur EQEX

    'OPER' 'RDIV' 'U0' 'INCO' 'UN'

   OBJET :

  Calcule le champ de vitesse U a divergence nulle et minimisant l'ecart
||U - U0||.

   Commentaires

   U0 Champ de vitesse ne verifiant pas DIV (U0) = 0
        CHPOINT VECT CENTRE ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice MOT.

## REAC [Mecanique Resolution]
    Operateur REAC
    -------------- RELA RESO

    | CHPO2 |  =  REAC  RIG1 | CHPO1 | ;
    | TAB2  |  | TAB1  |
     ( TAB4 = )  | TAB3  |

    Objet :

    L'operateur REACTION construit a partir de la solution CHPO1 d'un
systeme lineaire, sur le premier membre duquel ont ete imposees des
conditions, la variation du second membre permettant de verifier
ces conditions.

    Commentaire :

    RIG1 : objet contenant entre autres des conditions imposees (type
        RIGIDITE)

    CHPO1 : champ solution (obtenu par exemple par RESOU)
        (type CHPOINT).

    TAB1 : objet TABLE definissant les modes, les pseudo-modes, ...
        - de sous-type BASE_MODALE, ou
        - de sous-type ENSEMBLE_DE_BASES.

    CHPO2 : champ d'actions resultat (type CHPOINT) de nature discrete
        necessaire a la verification des conditions imposees.

    TAB2 : meme structure que TAB1, mais completee a l'indice
        'REACTION_MODALE' pour les modes
        'REACTION' pour les pseudo-modes,
        par le champ d'actions resultat (type CHPOINT)

    TAB3 : objet TABLE de sous-type 'LIAISONS_STATIQUES'
        (TAB4 optionnel). Doit comporter des indices de type
        ENTIER pointant sur des tables (type TABLE). Celles-ci
        doivent comporter un indice 'DEFORMEE', type CHPOINT
        et sont completees par un indice 'REACTION', type CHPOINT

    Exemple :

    Soit RIG1 la matrice de rigidite d'une structure, BLO1 l'objet
contenant les blocages et relations, FORC1 un champ de forces externes,
le champ de deplacements de la structure est obtenu par :

        DEP1 = RESOU ( RIG1 ET BLO1 ) FORC1 ;

    On obtient les reactions aux appuis par :

        CHPO1 = REAC BLO1 DEP1 ;

    Remarque :

    Si RIG1 ne contient pas de matrices elementaires associees a
des conditions imposees, on cree un champ CHPO2 vide.

## RECENTRE [Fluides Resolution] (proc)
Procedure RECENTRE

 CHP2 = RECENTRE CHP1 MODELE NIV

 Objet :

 Procedure interne appelee par DARCYSAT

 prend un champ point centre CHP1, et
   - si le mot niv = 'CENTRE', ne fait rien,
   - si le mot niv = 'MSOMMET' , fait la moyenne au centre
   - si le mot niv = 'FACE' (en EFMH) , fait la moyenne au centre a l'aide d

 Retourne le champ-point (re)centre CHP2.
 S'appuie sur le modele.

## RECO [Mecanique Dynamique]
  Operateur RECO
  -------------- EVOL 'RECO'

  CHPO2  =  RECO  CHPO1 | TBAS1 (TLIA1) ;
        | MOD1 CAR1 ;
        | BASE1 (CHAR1 XLIAI TEMPS) TYPE ;

  CHPO2  =  RECO  TPASA | TBAS1 (TLIA1)  | TEMPS TYPE ;
        | MOD1 CAR1  |
        | BASE1 (CHAR1 XLIAI ) |

  CHPO2 = RECO TDYNE TBAS2 (CHAR1 TLIAI) TEMPS TYPE ;

  LCHPO2 = RECO LCHPO1 TBAS1 NMOD1 ;

  Objet :

  L'operateur RECO recombine un (ou plusieurs) CHPOINT(s) sur base
  "physique" a partir des contributions modales q contenues dans un
  (ou plusieurs) CHPOINT(s) ou dans une TABLE de resultats (PASAPAS
  ou DYNE) et des modes X et solutions statiques Y constituant une
  base.
  Autrement dit, il calcule :
       u(t) = [ X Y ] * q(t)

  Les deformees modales doivent avoir le meme maillage support (les
  memes points avec le meme ordre) et les memes noms de composantes
  dans le meme ordre.

  Commentaire :

- q(t) fourni sous la forme :

  CHPO1 : Contributions modales (type CHPOINT)
  LCHPO1 : Evolution temporelle des contributions modales (type
        LISTCHPO)
  TDYNE : Objet TABLE de sous-type RESULTAT_DYNE
  TPASA : Objet TABLE de sous-type PASAPAS

- X et Y fournis sous la forme :

  TBAS1 : Objet TABLE de sous-type BASE_MODALE
  NMOD1 : ENTIER indiquant le nombre de modes retenus pour effectuer
        la recombinaison modale (par defaut : tous les modes)
  TLIA1 : Objet TABLE de sous-type LIAISONS_STATIQUES
  TBAS2 : Objet TABLE definissant les modes, les pseudo-modes...
        de sous-type BASE_MODALE ou ENSEMBLE_DE_BASES
  BASE1 : Objet BASE MODALE elementaire (la procedure de declaration
        d'une base elementaire figure au chapitre BASE)
  MOD1 : Objet MMODEL decrivant la base modale
  CAR1 : Objet MCHAML decrivant les proprietes de la base

- options de sortie :

  TEMPS : Temps ou on demande la recombinaison (type FLOTTANT)
  TYPE : Type de la variable (type MOT) choisi parmi:
        'DEPL', 'VITE', 'ACCE', 'CONT', 'REAC'
        - pour recombiner les contraintes: le TYPE est 'CONT'
        et le resultat est un objet de type MCHAML
        - pour les autres TYPEs, le resultat est un CHPOINT
        - l'option REAC ne fonctionne que si l'on a donne la
        base modale sous forme d'une TABLE

- u(t) obtenus sous la forme :

  CHPO2 : Grandeur reconstruite sur base physique a l'instant
        demande (type CHPOINT)
  LCHPO2 : Evolution temporelle de la grandeur reconstruite sur base
        physique, aux memes instants que LCHPO1 (type LISTCHPO)

- si l'on veut tenir compte des pseudo-modes :

  CHAR1 : Objet definissant le chargement de la structure (type
        CHARGEME). Les pseudo-modes ont ete calcules et doivent
        etre dans la base.
  XLIAI : Contributions modales definissant les forces de liaison
        (type CHPOINT)
  TLIAI : Table de liaison DYNE (type TABLE)

## RECOMPOM [Mathematiques Traitement] (proc)
Procedure RECOMPOM
------------------ NORMALIM

N2 EVOL1_SIGN =RECOMPOM EVOL2_MRESI EVOL3_MDECO
        FLOT1_DTIME (FLOT2_RESI LREEL1_DECO TAB1);

Objet :

La procedure RECOMPOM permet d'effectuer la recomposition
EVOL1_SIGN (comportant une courbe) d'un signal dont on connait
la decomposition en ondelette orthogonal sous forme de fonctions
de modulation EVOL3_MDECO (contenant N1 courbes) et d'une fonction
residu EVOL2_MRESI (contenant une courbes). FLOT1_DTIME indique
la periode echantillonnage associee a EVOL2_MRESI. Le signe des
coefficients en ondelette est genere de façon aleatoire. N2 indique
le nombre de niveaux de recomposition effectivement atteint.

Les fonctions EVOL3_MDECO et EVOL2_MRESI peuvent etre identifiees
en utilisant la procedure DECOMPOS, l'operateur LSQF.

les valeurs FLOT2_RESI et LREEL1_DECO peuvent etre determinees
avec la procedure NORMALIM ou calculees avec RESPOWNS.

La procedure RECOMPOM utilise la procedure RECOMPOS et l'operateur
PERT.

Options :

FLOT2_RESI : FLOT2_RESI permet de ponderer EVOL2_MRESI. Defaut 1.

LREEL1_DECO : LREEL1_DECO, comportant N1 FLOTTANT permet de
        ponderer EVOL3_MDECO. Defaut 1. ... 1.

TAB1 : le contenu significatif de TAB1 est le suivant:

indice type objet commentaires
        pointe

 LREC ENTIER permet de specifier le nombre de niveaux
        de recomposition souhaite. Par defaut c'est
        le maximum, c'est-a-dire N1.

 FORC LOGIQUE permet de forcer la recomposition suivant
        LREC au dela de N1 en ajoutant des niveaux
        nuls. Le defaut est FAUX (pas d'autorisation).

 BORD MOT specifie les conditions de bord pour les
        calcul de correlation: 'SYME'(trique) ou
        'PADD'(ing) de zero. Le defaut est 'SYME'.

 TYPE MOT permet de specifier le type d'ondelette
        orthogonale: 'MALL'(at) ou 'DAUB'echie.
        Le defaut est 'MALL'.

 AMPL FLOTTANT introduit une perturbation aleatoire de
        type sinus/cosinus dans la determination
        des signaux en ondelette (operateur PERT).
        Par defaut AMPL est nul.

 INIT ENTIER permet d'initialiser le generateur de
        nombre aleatoire. Par defaut on ne fait rien.

 TINI FLOTTANT permet de preciser une borne inferieure
        de reconstruction du signal.

 TFIN FLOTTANT permet de preciser une borne superieure
        de reconstruction du signal.

## RECOMPOS [Mathematiques Traitement] (proc)
Procedure RECOMPOS

N2 EVOL1_SIGN =RECOMPOS EVOL2_RESI EVOL3_DECO (TAB1);

Objet :

La procedure RECOMPOS permet d'effectuer la recomposition
EVOL1_SIGN (comportant une courbe) d'un signal dont on
connait la decomposition en ondelette orthogonale EVOL3_DECO
(contenant N1 courbes) et le residu EVOL2_RESI (contenant une
courbes). L'entier N2 indique le nombre de niveaux de
recomposition effectivement atteint.

La procedure RECOMPOS utilise la procedure MULTIREC.

Options :

Le contenu significatif de TAB1 est le suivant:

indice type objet commentaires
        pointe

 LREC ENTIER permet de specifier le nombre de niveaux
        de recomposition souhaite. Par defaut c'est
        le maximum, c'est-a-dire N1.

 FORC LOGIQUE permet de forcer la recomposition suivant
        LREC au dela de N1 en ajoutant des niveaux
        nuls. Le defaut est FAUX (pas d'autorisation).

 BORD MOT specifie les conditions de bord pour les
        calcul de correlation: 'SYME'(trique) ou
        'PADD'(ing) de zero. Le defaut est 'SYME'.

 TYPE MOT permet de specifier le type d'ondelette
        orthogonale: 'MALL'(at) ou 'DAUB'echie.
        Le defaut est 'MALL'.

 TINI FLOTTANT permet de preciser une borne inferieure
        de reconstruction du signal.

 TFIN FLOTTANT permet de preciser une borne superieure
        de reconstruction du signal.

## RECOVIBC [Dynamique Post-traitement] (proc)
Procedure RECOVIBC

RECOVIBC TbasC2 TbasR1;

Objet :

Recombine une base modale complexe TbasC2 notée [q] obtenue avec VIBC
sur un problème projeté sur la base de modes réelles TbasR1 notée [X],
qui n'aurait pas déjà été recombinée directement par VIBC.
Les déformées modales complexes recombinée z_j sont ainsi
supportées par les degrés de liberté du modèle éléments finis :

   z_j^R = [X] * q_j^R
   z_j^I = [X] * q_j^I

Commentaire :

TbasR1 (E) : Objet TABLE de sous-type BASE_MODALE issue de VIBR

TbasC2 (E/S) : Objet TABLE de sous-type BASE_MODALE issue de VIBC
        avec les indices suivants :

- en entrée (E) de RECOVIBC :

  TbasC2
  . 'MODES'
    . 'MAILLAGE' = maillage des point_repere des modes
    . j = table du j ème mode complexe
      . 'DEFORMEE_MODALE_REELLE' = q_j^R
      . 'DEFORMEE_MODALE_IMAGINAIRE' = q_j^I

- en sortie (S) de RECOVIBC ::

  TbasC2
  . 'MODES'
    . 'MAILLAGE' = maillage de TbasR1
    . 'MAILLAGE_P' = maillage des point_repere des modes
    . j = table du j ème mode complexe
      . 'DEFORMEE_MODALE_REELLE' = z_j^R
      . 'DEFORMEE_MODALE_IMAGINAIRE' = z_j^I
      . 'DEFORMEE_MODALE_REELLE_P' = q_j^R
      . 'DEFORMEE_MODALE_IMAGINAIRE_P' = q_j^I

## REDU [Langage Objets]
    Operateur REDU

      OBJET3 = REDU ('STRI') OBJET1 OBJET2 ;

    Objet :

    L'operateur REDU reduit :

        - un champ par points aux points d'un maillage donne.
        - un champ par points aux valeurs non nulles d'un CHPOINT.
        - un champ par elements aux elements d'un maillage donne.
        - un champ par elements a l'objet MMODEL donne.
        - un objet MMODEL a un maillage donne.
        - un objet NUAGE a des composantes donnees.
        - un objet RIGIDITE aux elements d'un maillage donne
        - objet ESCLAVE de champ par elements a l'objet MMODEL donne
        - un MMODEL de contact aux elements qui risquent d'etre actifs

      Commentaire :

      Types possibles :

      |  OBJET1  |  OBJET2  |  OBJET3  |
a ----------------------------------------------------
      |  CHPOINT  |  MAILLAGE  |  CHPOINT  |
      |  CHPOINT  |  POINT  |  CHPOINT  |
      |  CHPOINT  |  CHPOINT  |  CHPOINT  |
      |  MCHAML  |  MAILLAGE  |  MCHAML  |
      |  MCHAML  |  MMODEL  |  MCHAML  |
      |  MMODEL  |  MAILLAGE  |  MMODEL  |
      |  NUAGE  |  MOT1,MOT2...  |  NUAGE  |
      |  RIGIDITE  |  MAILLAGE  |  RIGIDITE  |
      | TABLE (esclave)|  MMODEL  |  MCHAML  |
      |  MMODEL  |  'CONTACT'  |  MMODEL  |

    Remarque 1 : modele de MELANGE

    En cas de reduction d'un MCHAML sur un MMODEL de MELANGE, le
    mot-cle STRICT indique de ne garder que les composantes portant
    sur le melange.

    En cas de reduction d'un MCHAML ou d'un MMODEL
    sur un maillage :

     - ce maillage doit etre constitue d'elements du meme type que le
       maillage support du MCHAML ou du MMODEL.

     - tous les elements du maillage doivent etre inclus dans le
       maillage support du MCHAML, ou du MMODEL.

    Remarque 2 : TYPE des MCHAML

    REDU verifie le type des MCHAML et le corrige au besoin.
    Les types considérés par REDU sont les suivants :

      - DEPLACEMENTS
      - FORCES
      - TEMPERATURE
      - GRADIENT
      - DEFORMATIONS
      - CONTRAINTES
      - CONTRAINTES PRINCIPALES
      - DEFORMATIONS INELASTIQUES
      - VARIABLES INTERNES
      - CARACTERISTIQUES
      - GRADIENT DE FLEXION
      - SCALAIRE
      - MATRICE DE HOOKE
      - MATRICE DE RAYONNEMENT

    Le type d'un MCHAML est défini par ses composantes. S'il
    possede au moins une composante d'un type connu et aucune
    composante d'un autre type, alors son type est celui de la
    composante identifiee. Par exemple, s'il possede un nom de
    composante de CONTRAINTES, alors il est type CONTRAINTES.

    Le type des MCHAML sert de precondionnement a certains
    operateurs.

    Toutefois LE TYPE DES MCHAML N'EST PAS UNE DONNEE OBLIGATOIRE.

## REFE [Maillage Generaux]
Operateur REFE

OBJET : Lister les objets maillages inclus au sens des noeuds dans
----- un autre ou indiquer si un objet maillage est inclus dans
        un autre.

SYNTAXE 1 : LOBI = REFE OBJ2 ;
        LOBI : objet LISTMOTS contenant la liste

SYNTAXE 2 : LOGI = OBJ1 REFE OBJ2 ;
        LOGI : objet de type LOGIQUE prenant les valeurs VRAI
        ou FAUX suivant que OBJ1 est inclus ou non dans
        OBJ2

## REGE [Maillage Manipulation]
    Operateur REGENERER

    GEO1 = REGE GEO2 ('VERI');

    Objet :

    Certaines situations conduisent a creer des elements ayant des
noeuds spatialement confondus. Il peut etre interessant de les remplacer
par des elements ou les noeuds doubles n'apparaissent qu'une fois, par
exemple triangle pour quadrangle, prisme pour cube.

    L'operation se fait en deux temps:

Il faut d'abord fusionner les noeuds confondus par l'utilisation de
l'operateur ELIMINATION, puis transformer les elements les contenant
par l'utilisation de l'operateur REGENERER.

    Commentaire :

    GEO2 : geometrie a regenerer (type MAILLAGE)

    GEO1 : geometrie resultat (type MAILLAGE)

    VERI : mot clé indiquant que l'on souhaite verifier que le maillage
        finale ne comporte pas de noeud double (avertissement sinon)

    Exemple :

    OPTI ELEM QUA4 DIME 2;
    POIN1 = 0 0 ; POIN2 = 5 0;
    LIG1 = POIN1 DROI 5 POIN2;
    SURF1 = LIG1 ROTA 5 90. ( 0.001 0.) ;
    ELIM SURF1 0.05 ;
    TRIQUA1 = REGENERER SURF1 ;

     Remarque :

     Sont actuellement prevus les passages suivants :

        SEG2 ---> POI1
        SEG3 ---> SEG2
        TRI3 ---> SEG2
        TRI4 ---> SEG2
        QUA4 ---> TRI3
        QUA5 ---> TRI3
        TRI6 ---> SEG3
        TRI7 ---> SEG3
        QUA8 ---> TRI6
        QUA9 ---> TRI6
        CUB8 ---> PRI6
        CU20 ---> PR15

## REGL [Maillage Surfaces]
    Operateur REGLER
    ---------------- ROTA SURF GENE

    SURF1 = LIG1 REGLER (N1) ('DINI' DENS1) ('DFIN' DENS2) LIG2 ;

    Objet :

    L'operateur REGLER construit la surface reglee s'appuyant sur les
lignes LIG1 et LIG2. Ces deux lignes doivent etre de meme type,
avoir le meme nombre d'elements et etre decrites dans le meme sens.

    Commentaire :

    LIG1 |  : lignes sur lesquelles s'appuie la surface a generer
    LIG2 |  (type MAILLAGE)

    N1 : nombre de couches d'elements generees (type ENTIER)

    DENS1 | : densites associees aux lignes LIG1 et LIG2 (type FLOTTANT)
    DENS2 |

    Remarque :

    Si N1 est specifie, N1 est le nombre de couches d'elements engendree
dans l'operation.

    Si N1 n'est pas specifie, ce nombre est calcule en fonction des
densites utilisees.

    Si N1 est negatif, N1 couches seront engendrees et leurs epaisseurs
seront calculees en tenant compte des densites des extremites.

    Si les densites associees aux lignes LIG1 et LIG2 ne sont pas
correctes, il est possible de les surcharger. Pour la densite initiale,
il faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour la
finale, derriere le mot-cle 'DFIN'.

    Si LIG1 est une surface, l'operation s'applique au cote 3 de cette
surface, s'il existe, et le resultat est la surface initiale augmentee
de celle que l'on cree.

    Si LIG2 est une surface, l'operation s'applique au cote 1 de cette
surface s'il existe, et le resultat est la surface initiale precedee
de celle que l'on cree.

## RELA [Mecanique Limites]
    Operateur RELA
    -------------- SYMT RESO
        ANTI COLLER

CHAP{Definir une relation lineaire entre des inconnues}
PART{Relation definie entre deux maillages}

   RIG1 = RELA  |  | (VAL1) | MOT1  | GEO1 ...
        |'MINI'|  | 'DEPL' |'DIRECTION' VEC1 |
        |'MAXI'|  | 'ROTA' |  |

        |  +  | (VAL2) | MOT2  | GEO2  ...
        |  -  |  | 'DEPL' |'DIRECTION' VEC2 |
        | 'ROTA' |  |

    Objet :

    L'operateur RELATION permet de construire la raideur associee a une
relation lineaire entre les inconnues de noms MOTi ponderees par des
coefficients (eventuels) VAL1, VAL2 ..., des noeuds respectifs des
maillages GEO1, GEO2, (voir l'exemple ci-dessous) ...

    Commentaire :

    MOTi : noms des inconnues (type MOT)

    VALi : coefficients de ponderation (type ENTIER ou FLOTTANT)

    VECi : permet de mettre en relation le deplacement (mot-cle 'DEPL')
        ou la rotation (mot-cle 'ROTA') dans la direction VEC1 (type
        POINT)

    GEOi : geometries (type MAILLAGE) constituees toutes du meme nombre
        de noeuds ou d'un seul noeud.

    RIG1 : objet resultat (type RIGIDITE)
        a adjoindre a la rigidite de la structure pour la resolution

    Remarque :

    L'operateur DEPIMP permet eventuellement d'imposer une valeur non
nulle a la relation.

    Si une geometrie ne contient qu'un seul noeud, il apparaitra dans toutes
les relations balayant les noeuds respectifs des autres geometries.

    La relation peut etre d'egalite ou d'inegalite (cas des relations
unilaterales) en presence des mots-cles 'MINI' ou 'MAXI'.

    Exemple :

    REL1 = RELA MINI 2.5 UX L1 - UY L2 + 3 UX L3 ;
    JEU1 = DEPIMP REL1 0.3 ;

  Ceci traduit les inegalites :

   2.5*UX(noeud i de L1)-UY(noeud i de L2)+3*UX(noeud i de L3) >EG 0.3

  pour i allant de 1 au nombre de noeuds de L1 (L2, L3, ... aussi)

PART{Relation definie par un champ par point (CHPOINT)}

    RIG1 = RELA  | 'MAXI' |  CHPO1  ('DUAL' CHPO2);
        | 'MINI' |

    Objet :

    L'operateur RELATION permet de construire la raideur associee a
une relation lineaire entre les inconnues dont les noms sont ceux des
composantes du champ par points CHPO1 (type CHPOINT) aux points qui
sont ceux du champ et ponderees par les valeurs du champ en ces
points.

    La relation peut etre d'egalite ou d'inegalite (cas des relations
unilaterales) en presence des mots-cles 'MINI' ou 'MAXI'.

    Si le mot cle DUAL est indique, il faut fournir un champ (type CHAMPOINT)
decrivant les reactions sur la relation. Sinon, c'est la transposee de la
relation qui est utilisee Pour pouvoir traiter l'aspect unilateral,
il faut prendre soin de la direction du champ de reactions.

PART{Relation definie par un modele (MMODEL)}

    RIG1 = RELA MOD1 ;

    Objet :

    L'operateur RELATION permet de construire la raideur associee a une
relation lineaire entre inconnues, contenue dans un objet MMODEL.

Commentaire :

    MOD1 : Objet MMODEL a partir duquel on va construire la raideur.

        Si MOD1 contient des sous-zones X-FEM on va construire les
        blocages mettant a zero les ddl non actifs.

        SI MOD1 contient des sous-zones de SURE on va construire les
        relation linéaires associées.

        Sinon on sort une raideur vide.

PART{Option CORI : relation de mouvement de corps rigide}

    RIG1 = RELA  'CORI' 'DEPL' | ('NOVERIF') GEO1 ;
        |
        | 'ROTA' GEO1 (GEO2) ;

    Objet :

    L'option 'CORI' de l'operateur RELA permet de construire la raideur
RIG1 (type RIGIDITE) associee a un mouvement de corps rigide,au premier
ordre pour une geometrie :

   En l'absence du mot cle 'ROTA' le mouvement de corps rigide pour
l'objet GEO1 (type MAILLAGE) est assure en imposant que la distance
entre les noeuds reste constante. Pour cela il faut au moins 4 points
non-coplanaires en 3D et 3 points non-alignes en 2D (si ce n'est pas
le cas utiliser le mot 'NOVERIF' avec le risque de ne pas avoir le
resultat souhaite). Cette option est a utiliser quand les rotations ne
sont pas considerees commes des DDL.
  En presence du mot cle 'ROTA' le mouvement de corps rigide est assure
en imposant que les DDL des noeuds de GEO1 (type MAILLAGE ou POINT avec
des DDL de rotation) et de GEO2 (type MAILLAGE sans DDL de rotation /
facultatif) soient les elements de reduction du meme distributeur defini
a partir des deplacements et rotations d'un point maitre de GEO1.

PART{Option ENSE : relation de mouvement d'ensemble}

    RIG1 = RELA 'ENSE' MOT1 GEO1 ;

    Objet :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## REMA [Maillage Autres]
Operateur REMA (REMAiller)
-------------------------- RAFT

MAIL1 (METR1) = 'REMA' MAIL2 (MAIL3) (METR2) ...

        ... | ('AJNO') | ('IPOL') (TAB1) ;
        |  'NOAJ'  |

Objet :

Cet operateur remaille un maillage de simplex (triangles ou
tetraedres) de maniere anisotrope par un algorithme de maillage
topologique du a T. Coupez et al.

Commentaire :

  MAIL1 : maillage genere (type MAILLAGE)

  METR1 : si le mot-cle 'IPOL' est donne, METR1 (type CHPOINT) est
        la metrique interpolee sur le nouveau maillage MAIL1

  MAIL2 : maillage a optimiser (type MAILLAGE)

  MAIL3 : partie du bord de MAIL2 que le mailleur ne doit pas
        modifier (par defaut le mailleur peut retirer ou ajouter
        des noeuds sur les parties planes du bord de MAIL2)

  METR2 : objet de type FLOTTANT ou CHPOINT
        Si METR2 est de type FLOTTANT, il s'agit de la taille
        d'arete voulue (densite)
        Si METR2 est de type CHPOINT, il s'agit de l'inverse
        de la metrique voulue (unite : longueur^-2)

  TAB1 : objet optionnel de type TABLE dont les indices sont des
        parametres d'entree ou de sortie du mailleur
        (voir notice MAILTOPO pour plus de details)

Remarques :

 1) Si la metrique voulue est isotrope, le nom de composante est G.
    Si la metrique voulue est anisotrope, les noms des composantes
    sont : G11, G21, G22, (G31, G32, G33 en 3D)

 2) Si le mot-clef 'AJNO' (par defaut) est donne, le mailleur peut
    generer de nouveaux noeuds.
    Si le mot-clef 'NOAJ' est donne, le mailleur ne genere pas de
    nouveaux noeuds.

## REMP [Langage Objets]
Directive/operateur REMPLACER
----------------------------- ENLE

REMPLACER OBJET1 INDIC1 OBJET2 ;

MOT2 = REMPLACER MOT1 INDIC1 OBJET2 ;

Objet :

La directive REMPLACER remplace l'element de position INDIC1 dans
l'objet OBJET1 par l'objet OBJET2.

Si INDIC1 est un objet LISTENTI, on remplace successivement les
indices voulus de OBJET1 par :

 - la meme valeur à chaque fois, si OBJET2 n'est pas une liste.

 - des valeurs definies individuellement, si OBJET2 est une liste
   de meme longueur que INDIC1.

Dans le cas ou OBJET1 est de type MOT, REMPLACER devient un
operateur (le resultat est renvoye dans un nouvel objet MOT2).

Operations possibles :

|  OBJET1  |  INDIC1  |  OBJET2  |
|  MOT  |  MOT  |  MOT  |
|  MOT  |  LISTMOTS  |  LISTMOTS  |
|  LISTREEL  |  ENTIER  |  FLOTTANT  |
|  LISTENTI  |  ENTIER  |  ENTIER  |
|  LISTMOTS  |  ENTIER  |  MOT  |
|  LISTCHPO  |  ENTIER  |  CHPOINT  |
|  LISTREEL  |  LISTENTI  |  FLOTTANT  |
|  LISTENTI  |  LISTENTI  |  ENTIER  |
|  LISTMOTS  |  LISTENTI  |  MOT  |
|  LISTCHPO  |  LISTENTI  |  CHPOINT  |
|  LISTREEL  |  LISTENTI  |  LISTREEL  |
|  LISTENTI  |  LISTENTI  |  LISTENTI  |
|  LISTMOTS  |  LISTENTI  |  LISTMOTS  |
|  LISTCHPO  |  LISTENTI  |  LISTCHPO  |

## RENDSOUR [thermique, mathematiques] (proc)
Procedure RENDSOUR

RESU1 = RENDSOUR CGMOD1 CGMAT1 (LREE1) ('MOYE') ;

Objet :

   La procedure RENDSOUR calcule le rendement d'une source
de chaleur mobile definie par les CHARGEMENTs de modeles
(CGMOD1) et de materiaux (CGMAT1). Plus precisement, RENDSOUR
determine la quantite de chaleur reellement integree dans
le calcul par rapport a celle specifiee dans le modele, le
support geometrique de la source (maillage) ne couvrant pas
necessairement tout le domaine spatial du modele analytique.

   On peut fournir une discretisation temporelle (LREE1) avec
laquelle calculer le rendement. Par defaut, RENDSOUR utilise
la liste des temps contenue dans le chargement CGMOD1. Les
piquets de temps ou l'intensite de la source est nulle ne sont
pas comptes. En sortie, RESU1 est un objet EVOLUTION contenant
l'evolution du rendement de la source en fonction des piquets
de temps ou il est compte.

   Le mot-cle 'MOYE' permet de calculer le rendement moyen de
la source de chaleur sur l'ensemble des piquets de temps ou son
intensite est non nulle. Dans ce cas, RESU1 est un FLOTTANT.

Commentaire :

   CGMOD1 : objet CHARGEMENT de nom MODE, decrivant l'evolution
        temporelle du modele de source de chaleur,

   CGMAT1 : objet CHARGEMENT de nom MATE, decrivant l'evolution
        temporelle des caracteristiques du modele,

   LREE1 : objet LISTREEL, instants de mesure du rendement,

   RESU1 : objet FLOTTANT ou EVOLUTION, rendement de la source
        de chaleur.

## REPART [Mathematiques Statistiques] (proc)
   Procedure REPART
   ----------------- FINVREPA

   FLO2 = REPART TAB1 FLO1;

        TAB1 . typva
        . A
        . B
        . LAMBDA
        . MU
        . MOYENNE
        . ECART_TYPE
        . TAU
        . K
        . W
        . MIN
        . MAX
        . U

      FLO1 flottant.

   Objet :
La procedure REPART calcule au point FLO1 la valeur de la fonction de
 repartition de la variable aleatoire dont les caracteristique se trouvent
 dans TAB1.
   Donnees :

 TAB1 . 'TYPVA' : chaine de caractere contenant le type de
     la variable aleatoire.
    Les types disponibles sont :
        'LOI_UNIFORME'
        'LOI_DE_LAPLACE'
        'LOI_NORMALE_STANDARD' (i.e. centree,reduite)
        'LOI_EXPONENTIELLE'
        'LOI_LOGNORMALE'
        'LOI_NORMALE'
        'LOI_WEIBULL_MIN'
        'LOI_NORMALE_TRONQUEE'
        'LOI_EXPONENTIELLE_TRONQUEE'
        'LOI_GUMBEL_MAX'
        'LOI_NORMALE_TRONQUEE_INF'
        'LOI_DE_FRECHET'

  Dans le cas de la loi uniforme :
 TAB1 . 'A'
 TAB1 . 'B' : sont les bornes de l'intervalle sur lequel
       la variable est definie (A<B)

  Dans le cas de la loi de Laplace :
pas de parametre. La densite vaut : 0.5*exp( - |x|).

  Dans le cas de la loi normale centree reduite (LOI_NORMALE_STANDARD) :
pas de parametre. La densite vaut : exp(-0.5*x^2)/((2*pi)**0.5)

  Dans le cas de la loi exponentielle :
    TAB1 . 'LAMBDA'
    TAB1 . 'MU'
 la densite vaut : lambda*exp(lambda*(mu - x)) si x >= mu
        0 sinon

  Dans le cas de la loi lognormale :
 TAB1 . 'MOYENNE'
 TAB1 . 'ECART_TYPE'
sont la moyenne et l'ecart-type de la variable aleatoire.

  Dans le cas de la loi normale :
 TAB1 . 'MOYENNE'
 TAB1 . 'ECART_TYPE'
sont la moyenne et l'ecart-type de la variable aleatoire.

  Dans le cas de la loi Weibull min :
 TAB1 . 'TAU'
 TAB1 . 'K'
 TAB1 . 'W'
 la densite vaut :
  ((X-TAU)/(W-TAU))**(K-1) * K / (W - TAU) * (exp (- ((X-TAU)/(W-TAU))**K))

  Dans le cas de la loi normale tronquee :
 TAB1 . 'MOYENNE'
 TAB1 . 'ECART_TYPE'
 TAB1 . 'MIN'
 TAB1 . 'MAX'
Les deux premiers parametres
sont la moyenne et l'ecart-type de la variable aleatoire.
MIN et MAX sont deux reels qui determinent l'intervalle de variation.

  Dans le cas de la loi exponentielle tronquee :
    TAB1 . 'LAMBDA'
    TAB1 . 'MU'
    TAB1 . 'MIN'
    TAB1 . 'MAX'
MIN et MAX sont deux reels qui determinent l'intervalle de variation.

  Dans le cas de la loi Gumbel max :
    TAB1 . 'LAMBDA'
    TAB1 . 'MU'
 la densite vaut :
lambda*exp(-lambda*(x-mu)-exp(-lambda*(x-mu)))

  Dans le cas de la loi Normale tronquee inf :
 TAB1 . 'MOYENNE'
 TAB1 . 'ECART_TYPE'
sont la moyenne et l'ecart-type de la variable aleatoire.
 TAB1 . 'MIN'
 est la borne inferieure des valeurs que peut prendre la variable
  aleatoire.

  Dans le cas de la loi de Frechet :
 TAB1 . 'U'
 TAB1 . 'K'
 TAB1 . 'B'
 la densite vaut :
  ((u - b)/(x - b))**k * exp(- ((u - b)/(x - b))**k) * k / (x - b)

## REPE [Langage Base]
Directive REPETER
----------------- FIN

REPETER BLOC1 (N1) ;

Objet :

L'objet BLOC1 (de type BLOC) est constitue de l'ensemble des
instructions comprises entre la directive REPETER BLOC1 et
la directive FIN BLOC1.

La directive REPETER permet de repeter N1 (type ENTIER) fois
l'execution de cet ensemble d'instructions.

Un objet ENTIER s'appelant &BLOC1 est incremente a chaque iteration
(compteur de la boucle valant 1 lors du premier passage).

ATTENTION : seules les 7 premieres lettres du nom BLOC1 sont mises
        derriere le caractere &.

Remarque :

Si N1 est specifie, il faut le mettre apres le nom de la boucle.

Si N1 est nul, le code de la boucle n'est jamais execute.

Si N1 est negatif ou s'il n'est pas specifie, la repetition se fait
indefiniment.

Il est possible dans tous les cas d'interrompre la repetition a
l'aide de la directive QUITTER. L'instruction ITERER permet quant
a elle de passer directement a l'iteration suivante, sans executer
le reste du code present jusqu'a la fin du bloc.

Exemple :

* Calcul de la constante d'Euler
* ==============================

I=0 ; CRIT= 1E-5; CRITM= CRIT*-1; C=0. ;
EPS1= 0 ; OK = FAUX ;

REPETER BLOTO 100 ;

I = I + 1; C = C + (1./ I) ;
EPS = C - (LOG I) ;
D = EPS - EPS1 ;

SI ( (D < CRIT) ET (D > CRITM) ) ;

OK = VRAI ;
MESS ' constante d'euler atteinte au bout de ' &BLOTO 'iterations';
QUITTER BLOTO ;

FINSI ;
EPS1 = EPS ;

FIN BLOTO ;

SI OK ;
LIST EPS ;
SINON ;
MESSAGE 'RATE' ;
FINSI ;
FIN;

## REPIX [Fluides Resolution] (proc)
Procedure REPIX

REPIX TAB1 ;

Objet :

Cette procedure "nettoie" les objets encombrants en memoire
(matrices) de la table TAB1 de sous type EQEX utilisee
en mecanique des fluides.

Commentaires :

TAB1 : Table de sous type EQEX creee par l'operateur EQEX.

## RESEAU [Mecanique Rupture] (proc)
Procedure RESEAU

Objet :

Cette procedure est appelee par la procedure TRACTUFI.

## RESI [Magnetostatique Magnetostatique]
Operateur RESI

RIG1 = RESI MOD1 MAT1;

Objet :

L'operateur RESI construit la matrice de resistance d'un modele
'MAGNETODYNAMIQUE' avec une formulation 'POTENTIEL_VECTEUR'.

Commentaire :

 MOD1 : nom du modele 'MAGNETODYNAMIQUE' (type MODELE)
 MAT1 : champ de caracteristiques du materiau (type MCHAML)
 RIG1 : matrice de resistance (type RIGIDITE)

## RESO [Mecanique Resolution]
    Operateur RESO

 CHPO1 (CHPO2 ..) = RESO RIG1 (PREC) CHPO3 (CHPO4..)
 ('NOID')('NOUNIL')('STAB')('ELIM' NBPASSE)('NOSTAB')('SOUC')
 (CHPOF) ('INIB' BLO1 LENTI1);

 (NB_MOD_RIG MAIL_CONTR) ... = ... ('ENSE') ;

    LICHP2 = RESO RIG1 LICHP1 ;

    (TAB2 = ) RESO RIG1 TAB1 ;

    Objet :

    L'operateur RESO construit une solution, si elle existe, du systeme
lineaire : RIG1 CHPO1 = CHPO3 .
    L'operateur RESO construit les solutions, si elles existent,
  de chacun des systemes lineaire : RIG1 CHPO1 = CHPO3 ,
     CHPO1 pris dans LICHP1, ou dans TAB1,
     CHPO3 range dans LICHP2, resp. TAB1

    Commentaire :

    RIG1 : objet de type RIGIDITE.

    CHPO3 : objet de type CHPOINT.

    CHPO1 : objet de type CHPOINT dont les composantes sont les duales
        de celles de CHPO3 par rapport a RIG1.

    LICHP1, LICHP2 : objet de type LISTCHPO

    TAB1 : objet de type TABLE, de sous-type 'LIAISONS_STATIQUES'
        Les indices sont de type ENTIER, pointent sur des objets
        TABLE, comportant les entrees
        - 'BLOCAGE', type RIGIDITE
        - 'FORCE', type CHPOINT, 2nd membre du systeme
        et completes par
        - 'DEFORMEE' type CHPOINT, solution du systeme
        - 'POINT_REPERE', type POINT, associe au deplacement calcule

    TAB2 : type TABLE, optionnel

    Remarque :

 1- En presence d'une famille de seconds membres CHPO3, CHPO4 ...,
l'operateur RESO construit la famille de solutions CHPO1, CHPO2 ..
respectivement associee.

 2- Si RIG1 contient des matrices issues de conditions unilaterales,
RESO appelle la procedure UNILATER pour fournir une solution du systeme.
Si il y a des matrices de frottement, il faut fournir le champ CHPOF
de forces limite de frottement.

 3- Les mots-cle 'NOID' et 'NOUNIL' sont utiles quand on emploie RESO a
    l'interieur d'une procedure :

      - 'NOID' desactive la vÃ©rificatin du residu ce qui autorise la
      resolution du systeme avec comme second membre la restriction de
      CHPO3, (CHPO4 ..) a l'espace cible de RIG1.

      - 'NOUNIL' permet de resoudre le systeme en ignorant le caractere
        eventuellement unilateral de RIG1.

      - 'INIB' BLO1 LENTI1 permet dans le cas de contact d'indiquer un
        etat de contact initial. Voir la procedure UNILATER.

 4- Le mot cle 'STAB' fait utiliser pour la resolution un operateur
    rendu positif par augmentation diagonale. CHPOx peut donc ne pas
    etre solution du probleme initial.
    Le mot-clÃ© 'NOSTAB' fait gconserver l'opÃ©rateur fourni.

 5- Le mot cle 'SOUC' provoque l'emission d'un soucis au lieu d'une
    erreur en cas d'impossibilite de resoudre le systeme.

 6- Le mot cle 'ELIM' permet de regler le nombre NBPASSE de passes
    d'elimination des inconnues soumises a des conditions ou relations
    imposees.

 7- Par "OPTION RESO DIRECTE" ou "OPTION RESO ITERATIVE"
    on peut choisir soit une resolution par methode de CROUT
    ( methode par defaut) soit une resolution par methode de gradients
    conjugues avec preconditionnement ILU0 stabilise.

 8- Les champs par points CHPO1(2..) obtenus sont de nature diffuse.

 9- Le mot-cle 'ENSE' indique que au cas ou le systeme est singulier
    et la singularite est excite, RESO fournira un vecteur du noyau.
    Il y a alors deux resultats supplementaires : NB_MOD_RIG qui est le
    nombre de vecteurs du noyau retournes et MAIL_CONTR qui est le
    maillage des noeuds sur lesquels on a applique une contrainte
    pour pouvoir resoudre le systeme.

10- PREC est la precision de l'operation. Le defaut est 1D-18.

    Exemple :

    RIG1 etant la raideur d'une structure , FORC1 un champ de force
s'exerçant sur cette structure, on obtiendra le champ de deplacements
DEP1 en resultant, par l'instruction :

        DEP1 = RESO RIG1 FORC1 ;

## RESO_ASY [Fluides Resolution] (proc)
Procedure RESO_ASY

Objet :

Cette procedure ne peut pas etre appelee par l'utilisateur.

Elle est appelee par l'operateur RESO

## RESP [Langage Methodes]
    Operateur RESPRO

    RESPRO OBJET1 OBJET2 ..... ;

    Objet :

    L'operateur RESPRO permet a l'interieur d'une procedure de rendre
des resultats OBJET1 OBJET2 .....

    Remarque :

    Il peut y avoir plusieurs ordres RESPRO dans une procedure.

    Ces resultats ne seront disponibles a la lecture qu'au moment de
l'appel a FINPRO.

    Le premier resultat rendu par RESP sera affecte au premier nom
devant le signe = , etc....

    Exemple :

    Procedure creant les N premieres puissances entieres d'un nombre.

        DEBP PUISSANC ;
        ARGU X*FLOTTANT N*ENTIER ;
        SI ( N <EG 0) ; QUITTER PUISSANC; FINSI;
        B = 1.;
        RESPRO B;
        NN = N - 1 ;
        SI ( NN EGA 0) ; QUITTER PUISSANC; FINSI;
        REPETER PU NN;
        B = B * X ;
        RESPRO B;
        FIN PU;
        FINPROC;

        A B C = PUISSANC 4 3;
        AA = PUISSANC 2 20 PROG;

   Dans notre exemple A B C valent respectivement 1 4 16 et AA est un
objet LISTREEL contenant les 20 premieres puissances de 2 (1 2 4 8...).

## RESPOWNS [Mathematiques Traitement] (proc)
Procedure RESPOWNS

EVOL1_PS = RESPOWNS EVOL2_RS EVOL3_M LREEL1_F (TAB1);

objet :

Calcul du spectre de puissance EVOL1_PS (comportant une unique
courbe) d'un signal stationnaire "virtuel" de duree TE associe a
un spectres de reponse EVOL2_RS (comportant une courbe)
correspondant a un amortissement AMOR, et a N courbes de
modulation EVOL3_M (comportant N courbes) aux bandes de
frequence indiquees dans LREEL1_F. La bande de frequence de la
i-eme fonction EVOL3_M est donnee par le i-eme (frequence
inferieure) et le i+1-eme (frequence superieure) element de OM.

Les fonctions de modulation doivent toutes demarrer au meme instant TI
et s'achever au meme instant TF. La duree du signal TE est evidemment
donnee par TF-TI. La frequence de coupure de EVOL1_PS est donnee par la
valeur maximale de LREEL1_F.

Pour stabiliser le processus de convergence, les iteration
s'effectuent en utilisant le filtre de Hanning (operateur HANN).

Une option speciale permet une identification compatible avec un
calcul en ondelette.

options :

Les options sont contenues dans TAB1.

indice type objet commentaires
        pointe

 GPRP MOT representant la grandeur physique de
        reponse : 'ACCE'(leration), 'VITE'(sse) ou
        'DEPL'(acement relatif). Le defaut est 'ACCE'.

 GPAB MOT representant la grandeur physique en abscisse
        de la reponse: 'PERI'(ode) ou 'FREQ'(uence).
        Le defaut est 'PERI'.

 AMOR FLOTTANT specifiant l'amortissement AMOR. Le defaut
        est 0.05.

 FFPS LISTREEL donnant le reticule de calcul en frequence
        du spectre de puissance. Le defaut est une
        progression geometrique entre 1/TE et la
        frequence de coupure dont la raison est
        (1+2*KSI), ou KSI=MIN AMOR.

 TTRS LISTREEL donnant le reticule de calcul en periode du
        spectre de reponse. Le defaut est celui de
        operateur PSRS.

 JMAX ENTIER representant le nombre maximum iteration
        autorise. Le defaut est 15.

 JHAN ENTIER representant le nombre iteration comportant
        le filtrage de Hanning. le defaut est JMAX.

 EMAX REEL representant la limite de convergence de
        l'erreur. Le defaut est 1.E-2.

 NBPR ENTIER indiquant le nombre de processus stationnaires
        associes au calcul de spectre de reponse.
        Le defaut est celui de operateur PRNS.

 NBIN ENTIER indiquant le nombre de points integration
        temporelle associe a chaque processus
        stationnaire. Le defaut est celui de
        operateur PRNS.

 LIST LOGIQUE indiquant la possibilite d'affichage du
        processus de convergence. Le defaut est FAUX.

 ONDE FLOTTANT indiquant t la periode echantillonnage
        associee a la premiere fonction de modulation.
        La presence de ce parametre indique un calcul
        par ondelette: dans ce cas EVOL1_PS contient
        autant de point que de bande de frequence et
        EVOL3_M la modelisation des coefficients en
        ondelette: la premiere courbe est le residu,
        et les suivantes sont relatives a chaque niveau
        de decomposition (des basses vers les hautes
        frequences).

## RESPOWSP [Mathematiques Traitement] (proc)
Procedure RESPOWSP

EVOL1_PS = RESPOWSP EVOL2_RS FLOT1_TE LREEL1_AMOR (TAB1);

objet :

Calcul du spectre de puissance EVOL1_PS (comportant une unique
courbe) d'un signal de duree FLOT1_TE associe a N spectres de
reponse EVOL2_RS (pouvant comporter N courbes) correspondant
aux N amortissements LREEL1_AMOR. Cette transformation inverse
n'a de sens mathematique que si EVOL2_RS ne contient qu'une
seule courbe. Si N>1, EVOL1_PS doit etre considere comme
un spectre moyen.

Pour stabiliser le processus de convergence, les iteration
s'effectuent en utilisant le filtre de Hanning (operateur HANN).

options :

Les options sont contenues dans TAB1 (objet de type TABLE).

indice type objet commentaires
        pointe

 GPRP MOT representant la grandeur physique de reponse:
        'ACCE'(leration), 'VITE'(sse) ou
        'DEPL'(acement relatif). Le defaut est 'ACCE'.

 GPAB MOT representant la grandeur physique en abscisse
        de la reponse: 'PERI'(ode) ou 'FREQ'(uence).
        Le defaut est 'PERI'.

 FRCO FLOTTANT indiquant la frequence de coupure du signal.
        le defaut est 25 Hz.

 FFPS LISTREEL donnant le reticule de calcul en frequence du
        spectre de puissance. Le defaut est une
        progression geometrique entre 1/FLOT1_TE et
        la frequence de coupure dont la raison
        est (1+2*KSI), ou KSI=MIN LREEL1_AMOR.

 TTRS LISTREEL donnant le reticule de calcul en periode du
        spectre de reponse. Le defaut est celui de
        operateur PSRS.

 DIST MOT representant le type de distribution choisie
        pour evaluer le lieu des maxima du spectre de
        reponse: 'CRAM'(er) ou 'NEWG'(umg). Le
        defaut est 'CRAM'.

 JMAX ENTIER representant le nombre maximum iteration
        autorisee. Le defaut est 15.

 JHAN ENTIER representant le nombre iteration comportant
        le filtrage de Hanning. le defaut est JMAX.

 EMAX FLOTTANT representant la limite de convergence de
        l'erreur. Le defaut est 1.E-2.

 LIST LOGIQUE indiquant la possibilite d'affichage du
        processus de convergence. Le defaut est FAUX.

## REST [Entree-Sortie Entree-Sortie]
    Directive RESTITUER

    RESTITUER ( 'FORMAT' ) ;
        ( 'LABEL' CHA1 )

    Objet :

    La directive RESTITUER permet de remettre en memoire les objets
decrits dans le fichier de numero logique IORES1 defini par :

        OPTION REST IORES1 ;

    Si le "label" est precise la lecture s'arretera un fois lu la
partie de la sauvegarde portant ce label.

    Remarque :

    Utiliser l'option FORMAT si et seulement si le fichier a ete
ecrit en formate.

    Un LABEL vide ou pas de label du tout entraine la restitution de
tout le fichier.

    Il est possible, dans le cas oº on a fait plusieurs calculs avec
le meme maillage, de les fusionner en utilisant conjointement la
directive OPTION NBP NPT.

    ATTENTION :

    Il est conseille de mettre cette directive en tete du fichier
de donnees et en particulier avant la creation de nouveaux points.
Par contre, elle doit etre precedee de la redefinition des OPTIONs.

## RESU [Mathematiques Autres]
    Operateur RESULT

    CHPO1 = RESULT CHPO2 ;

    Objet :

    L'operateur RESULT calcule la resultante d'un champ par points. Le
champ resultant contient un point auquel sont affectees les valeurs
correspondant aux sommations sur les differentes composantes.

    Commentaire :

    CHPO2 : champ dont on calcule la resultante (type CHPOINT)

    CHPO1 : champ resultat (type CHPOINT) de nature discrete

    Remarque : fonctionnalité obsolete

    Le calcul de la somme des valeurs des objets LISTREEL et LISTENTI
    est desormais realise par l'operateur SOMM.

## RETO [—]
L'operateur RETOUR permet de quitter l'interpreteur GIBIANE et de revenir au pro

$$$$

## RETRAIT [Mecanique Resolution] (proc)
Procedure RETRAIT
----------------- PHASAGE

  CHAM2 = RETRAIT ........;

Objet :

  Cette procedure permet de calculer le tenseur de deformations
  differees du au retrait du beton. Elle est appellee
  automatiquement par la procedure PHASAGE.

## RETSAT [Fluides Resolution] (proc)
   Procedure RETSAT

     RETSAT RXT TBT ;

   OBJET :

La procedure RETSAT est une procedure interne appelee par EXECRXT

   Commentaires

   RXT TABLE :
   TBT TABLE :

## RFCO [—]
Operateur RFCO

   R1 F1 = RFCO MOD1 LOG1 CHEL1 ;

Objet :

L'operateur RFCO calcule les raideurs des modeles de CONTACT ou CONTRAINTE MOD1
ainsi que les valeurs des seconds membres.

  Commentaire :

  MOD1 : objet MODELE contenant les formulations 'CONTACT' ou 'CONTRAINTE'

  LOG1 : LOGIQUE a FAUX en cas de non convergence

  CHEL1 : CHAMELEM de proprietes des modeles

  R1 : RIGIDITES de conditions ou ENTIERS 0

  F1 : CHPOINT portant sur les multiplicateurs de Lagrange des modeles et contenant les seconds membres

 Remarque : Cet operateur est appele par PASAPAS pour actualiser les conditions en cours de calcul

## RIGI [Mecanique Modele]
    Operateur RIGIDITE
    ------------------ CARA MEC3

      RIG1 = RIGI MODL1 CHAM1 ( CHAM2 ) ('NOER');

    Objet :

    L'operateur RIGI calcule la RIGIDITE de differents objets :

    |  Elements finis  |

      Commentaire :

      MODL1 : objet modele ( type MMODEL ).

      CHAM1 : Champ de caracteristiques materielles et eventuellement
        geometriques si necessaire pour certains elements (cf
        remarque ci-dessous) (type MCHAML, sous-type
        CARACTERISTIQUES) ou de matrices de Hooke (type MCHAML,
        sous-type MATRICE DE HOOKE).

      CHAM2 : Champ de caracteristiques (type MCHAML, sous-type
        CARACTERISTIQUES) necessaires pour certains elements
        (cf remarque ci-dessous) si CHAM1 est un champ de
        matrices de Hooke.

      RIG1 : Resultat de type RIGIDITE de sous-type RIGIDITE.

      'NOER' : En presence de ce mot cle rend un entier contenant le numero
        de l'erreur comme resultat.

      Remarque :

      Il faut specifier des caracteristiques si la description
      geometrique de l'element ne peut se faire par le maillage;
      par exemple l'epaisseur d'elements de plaques ou les inerties
      de flexion pour les elements de poutres etc...

    |  Raideurs additionnelles  |

    RIG1 = RIGI  |  ('DEPL') ('ROTA')  |  VAL  GEO1  ;
        |  NOMINC ...  |

    Commentaire :

    'DEPL' : mot-cle pour designer toutes les translations

    'ROTA' : mot-cle pour designer toutes les rotations

     NOMINC : un ou plusieurs noms (type MOT) designant les degres de
        liberte concernes (dans ce cas ne pas se servir
        des 2 mots-cles precedents )

     Les noms d'inconnues possibles sont :

     pour un calcul en MODE PLAN CONT : UX UY
     pour un calcul en MODE PLAN DEFO : UX UY
     pour un calcul en MODE AXIS : UR UZ RT
     pour un calcul en MODE FOUR : UR UZ UT RT
     pour un calcul en MODE TRID : UX UY UZ RX RY RZ

     VAL : rigidite additionnelle (type FLOTTANT).

     GEO1 : objet contenant les noeuds oº seront ajoutees les
        rigidites (type POINT ou MAILLAGE).

     RIG1 : objet de type RIGIDITE de sous-type RIGIDITE.

    |  Analyse modale  |

    RIG2 = RIGI BAS1 ;
    RIG3 = RIGI SOL1 ;
    RIG4 = RIGI SOL2 STRU1 ;

    RIG5 = RIGI TAB1 ;

    RIG6 = RIGI TAB2 (TAB3) ;
    Commentaire :

    RIG2 est l'ensemble des matrices de rigidites s'appuyant sur la
base modale BAS1. La base modale BAS1 est donnee sous la forme d'un
objet BASEMODA.

    RIG3 est la rigidite due aux modes (rigidites generalisees) contenus
dans l'objet SOL1 (type SOLUTION, sous-type MODE).

    RIG4 est la rigidite due au couplage sur la structure STRU1 (type
STRUCTUR) des solutions statiques contenues dans l'objet SOL2 (type
SOLUTION, sous-type SOLUSTAT).

    RIG5 est la rigidite due aux modes (rigidites generalisees) contenus
dans l'objet TAB1 (type TABLE de sous-type 'BASE_DE_MODES').

    RIG6 est la rigidite dans la base des deformees dans TAB2 (type
TABLE) de sous-type 'BASE_MODALE' ou bien 'LIAISONS_STATIQUES'.
Lorsque TAB3 est specifie, de sorte que ces deux sous-types
apparaissent en argument, les termes de couplage sont egalement calcules.

    Remarque :

    Les supports geometriques de RIG2, RIG3 et RIG4 contiennent les
points associes aux modes ou aux liaisons definies entre les structures.
On associe la composante 'ALFA' au mode, 'BETA' a une liaison sur des
libres, 'FBET' a une liaison sur des noeuds bloques.

    Le support geometrique de RIG6 contient les points associes
aux deformees statiques ou modales. Les composantes 'BETA', duale 'FBET'
sont relatives aux premieres, 'ALFA', duale 'FALF' aux secondes.

## RIMP [Mathematiques Autres]
   Operateur RIMP

   EVOL2 = RIMP EVOL1 ;

   Objet :

   L'operateur RIMP change le sous-type d'un objet de type EVOLUTION complexe.

   Si EVOL1 est de sous-type 'PREE' 'PIMA' (partie reelle, partie imaginaire),
EVOL2 sera de sous-type 'MODU' 'PHAS' (module, phase) et vice-versa.

## ROSENT [Thermique Resolution] (proc)
Procedure ROSENT

CHPO1 = ROSENT TAB1 ;

        TAB1.'PUISSANCE' .'RENDEMENT'
        .'DIFFUSVITE' .'CONDUCTIVITE'
        .'VITESSE'
        .'T0'
        .'NTERMES'
        .'MAILLAGE'
        .'EPAISSEUR'
        .'LOCAL' .'INSTANT'
        .'GAUSS' .'XPOS' .'YPOS'

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

        'XPOS' : REEL : Si 'GAUSS' est VRAI, abscisse de la
        source

        'YPOS' : REEL : Si 'GAUSS' est VRAI, ordonnee de la
        source

En sortie :

        CHPO1 : CHPOINT : Champ de temperature (en °C ou en K)

## ROTA [Maillage Surfaces]
    Operateur ROTATION
    ------------------ SURF GENE

    SURF1 = LIG1 ROTA (N1) FLOT1 ('DINI' DENS1) ('DFIN' DENS2) ...
        ... POIN1 (POIN2 si 3D) ;

    Objet :

    L'operateur ROTATION construit une surface engendree par la rotation
d'une ligne, d'un angle donne autour d'un point en 2D ou d'un axe en 3D.

    Commentaire :

    FLOT1 : angle de rotation (type FLOTTANT)

    POIN1 : centre de rotation (type POINT)

    POIN1 POIN2 : points definissant l'axe de rotation (type POINT)

    LIG1 : ligne generant la surface (type MAILLAGE)

    DENS1 DENS2 : densites associees a la ligne LIG1 et au(x) point(s)
        POIN1 (et POIN2) (type FLOTTANT)

    N1 : nombre de couches d'elements generees (type ENTIER)

    SURF1 : surface resultat (type MAILLAGE)

    Remarque :

    Si N1 est specifie, N1 est le nombre de couches d'elements engendrees
dans la rotation.

    Si N1 est positif, N1 couches d'egale epaisseur seront engendrees.

    Si N1 est negatif, N1 couches seront engendrees et leur epaisseur
sera calculee en tenant compte des densites utilisees.

    Si N1 n'est pas specifie, ce nombre est calcule en fonction des
densites utilisees.

    Si les densites associees a la ligne LIG1 et au point POIN1 (et
POIN2) ne sont pas correctes, il est possible de les surcharger. Pour la
densite initiale, il faut donner la bonne valeur derriere le mot-cle
'DINI', et pour la finale, derriere le mot-cle 'DFIN'.

    Si LIG1 est une surface, la rotation s'applique au cote 3 de cette
surface s'il existe, et le resultat est la surface initiale augmentee
de celle que l'on cree.

    La ligne LIG1 ne doit pas avoir de points sur l'axe de rotation.

## ROTA_IMP [Mecanique Limites] (proc)
   Procedure ROTA_IMP

 RIG1 CH1 = ROTA_IMP ANGLE POIN1 POIN2 MAIL1

  Objet :

La procedure ROTA_IMP construit la raideur RIG1 et le champ de deplacement
impose CH1 permettant d'imposer au maillage MAIL1 une condition de rotation
d'angle ANGLE autour de l'axe defini par les points POINT1 et POINT2.

Remarques:

La matrice et le champ dependent de l'angle. Il faut donc les reevaluer
pour chaque nouvel angle

L'angle doit etre strictement compris entre -90 et +90.

## RSET [Fluides Modele]
Directive RSET

 OBJET : Surcharger tout ou partie d'un CHAMPOINT TRIO existant
        avec un flottant et/ou un autre CHAMPOINT
        Dans ce dernier cas seul les points communs entre le
        premier et le deuxieme CHAMPOINT sont concernes.

 SYNTAXE : RSET CHP1 VAL <SPG> ;
        RSET CHP1 CHP2 <SPG> ;

        SPG support geometrique

## RTEN [Mathematiques Autres]
    Operateur RTENS
    --------------- CALP GRAD

CHAM3  =  RTENS  CHAM1 MODL1 |  CHAM2  ;
        |
        |  ( CHAM2 )  ...

        |  VEC1 ( VEC2 )  ;
        |
        ...  |  'POLA'  CENTR1 ;
        |  'SPHE'  CENTR1  AXEI1 ;
        | 'CYLI'  CENTR1  AXEI1 ;
        | 'TORI' ('CART')  CENTR1 AXEI1 ;
        | 'TORI'  'CIRC'  CENTR1 AXEI1 CENTR2 ;

CHPO2 = RTENS CHPO1 VEC1 (VEC2) ;

CHAM4  =  RTENS  CHAM1 MODL1  GRAD1  | ('RTAR') |  ;
        |  RART  |

    Cet operateur a plusieurs fonctions selon les donnees.

    | 1 Fonction |

    A partir d'un champ de contraintes ou de deformations definis
pour des elements massifs dans le repere general, pour les coques minces
dans le repere local a l'element (dont le premier vecteur est colineaire
au premier cote de l'element), et pour les coques epaisses dans les reperes
locaux (repere a chacun des points d'integration), l'operateur RTENS calcule
le champ de contraintes ou de deformations dans un nouveau repere orthonorme
direct.

    CHAM3 = RTENS CHAM1 MODL1 (CHAM2) VEC1 ( VEC2 ) ;

    Commentaire :

    CHAM1 : champ de contraintes ou de deformations initial (type
        MCHAML, sous-type CONTRAINTES ou DEFORMATIONS)

    MODL1 : objet modele (type MMODEL)

    CHAM2 : champ de caracteristiques contenant les epaisseurs dans
        le cas des coques epaisses (type MCHAML, sous-type
        CARACTERISTIQUES)

    VEC1 | : vecteurs servant a definir le repere orthonorme (type
    VEC2 |  POINT )

    CHAM3 : champ de contraintes ou de deformations dans le nouveau
        repere (type MCHAML, sous-type CONTRAINTES ou
        DEFORMATIONS)

    Remarque :

    Le repere orthonorme direct est defini comme suit :

  - pour les elements massifs bidimensionnels par le vecteur VEC1 et
     le vecteur normal a VEC1 (obtenu a partir de VEC1 par une rotation
     de pi/2 dans le sens trigonometrique)

  - pour les elements massifs tridimensionnels par le vecteur VEC1, le
     vecteur contenu dans le plan (VEC1,VEC2) et normal a VEC1, et le
     vecteur produit vectoriel de VEC1 et VEC2

  - pour les elements coque tridimensionnels, par le vecteur
     projection de VEC1 dans le plan de la coque et le vecteur contenu
     dans le plan de la coque, normal a VEC1 et tel que leur produit
     vectoriel soit dirige suivant la normale positive a l'element si
     seul VEC1 est fourni, ou bien tel que leur produit vectoriel soit
     de meme sens que le produit vectoriel de VEC1 et VEC2, si VEC2
     est fourni egalement.

    | 2 Fonction |

    A partir d'un champ de contraintes ou de deformations definies
pour des elements massifs orthotropes dans le repere general, pour les
coques minces orthotropes dans le repere local a l'element (dont le premier
vecteur est colineaire au premier cote de l'element), et pour les coques
epaisses orthotropes dans les reperes locaux (repere a chacun des points
d'integration), l'operateur RTENS calcule le champ de contraintes ou de
deformations dans le repere d'orthotropie .

    CHAM3 = RTENS CHAM1 MODL1 CHAM2 ;

    Commentaire :

    CHAM1 : champ de contraintes ou de deformations initial (type
        MCHAML, sous-type CONTRAINTES ou DEFORMATIONS)

    MODL1 : objet modele (type MMODEL)

    CHAM2 : champ de cosinus-directeurs des axes d'orthotropie par
        rapport aux reperes locaux des elements(type MCHAML,
        sous-type CARACTERISTIQUES)

    CHAM3 : champ de contraintes ou de deformations dans le repere
        d'orthotropie (type MCHAML, sous-type CONTRAINTES ou
        DEFORMATIONS)

    Remarque 1 :

    CHAM2 (ou CHEL2) peut etre le mchaml de caracteristiques
    materielles cree par l'operateur MATR (ou MATE) etant donne que
    le mchaml de caracteristiques materielles contient les cosinus-
    directeurs des axes d'orthotropie. Les noms de composantes qui
    representent les cosinus-directeurs des axes d'orthotropie sont :
    V1X,V1Y pour les elements coques et les element massifs en 2D, et
    V1X,V1Y,V1Z,V2X,V2Y,V2Z pour les elements massifs en 3D.

    | 3 Fonction |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## RVSAT [Fluides Resolution] (proc)
   Procedure RVSAT
   --------------- ASPARAM

   OBJ2 OBJ3 = RVSAT OBJ1 ;

   OBJET :

La procedure RVSAT calcule la densite de vapeur d'eau a saturation et
sa derivee par rapport a la temperature (la temperature etant comprise
entre 20 et 200 degre C. )
Cette procedure est appelee par la procedure ASPARAM.

   Commentaires

    OBJ1 CHPOINT Champ de temperature [C]
    OBJ2 CHPOINT Densite de vapeur [kg/m3]
    OBJ3 CHPOINT Derive de la densite par rapport a la temp.
        [kg/C/m3]

## RVST2 [Fluides Resolution] (proc)
   Procedure RVST2
   --------------- ASPARAM

   OBJ2 OBJ3 = RVSAT OBJ1 ;

   OBJET :

La procedure RVS2T calcule la densite de vapeur d'eau a saturation et
sa derivee par rapport a la temperature (la temperature etant comprise
entre 0 et 20 degre C. )
Cette procedure est appelee par la procedure ASPARAM en complement de la
procedur rvsat.procedur

   Commentaires

    OBJ1 CHPOINT Champ de temperature [C]
    OBJ2 CHPOINT Densite de vapeur [kg/m3]
    OBJ3 CHPOINT Derive de la densite par rapport a la temp.
        [kg/C/m3]

## SAIS [Entree-Sortie Entree-Sortie]
 Operateur SAIS

 OBJ1 = SAIS CHAINE TYPE;

 Objet :

 L'operateur SAIS permet de saisir interactivement un nom
 d'objet ou une valeur sur la fenetre de trace.

CHAINE : Chaine de caracteres affichee a l'ecran

TYPE : Type de l'objet a saisir

OBJ1 : Objet saisi

## SATUTILS [Fluides Modele] (proc)
 Procedure SATUTILS
 ------------------

Objet :

Ensemble de procedures appelees par DARCYSAT reunies dans
SATUTILS appelees comme suit :
SATUTILS nom_proc arguments de la procedure

## SAUF [Langage Objets]
Operateur SAUF

        LIST3 = LIST1 SAUF LIST2 (| FLOT1  |) ;
        | 'NOCA' |

Objet :

L'operateur SAUF cree une liste LIST3 a partir des elements
d'une liste LIST1 differents des elements d'une liste LIST2.

Les listes peuvent etre des objets de type LISTENTI, LISTREEL ou
LISTMOTS.

Dans le cas des LISTREEL, on peut fournir un critere FLOT1 (type
FLOTTANT) pour differencier deux reels en valeur absolue.

Dans le cas des LISTMOTS, on peut ajouter le mot-cle 'NOCA' pour
considerer egaux deux mots de casse differente.

## SAUT [Entree-Sortie Entree-Sortie]
    Directive SAUTER

        | 'LIGNE' |
    SAUTER  (N1)  |  |  ;
        | 'PAGE'  |

    Objet :

    La directive SAUTER permet de sauter des pages ou des lignes lors
des impressions.

    Remarque :

    Le nombre entier N1 de lignes ou pages a sauter vaut 1 par defaut.

    En utilisation interactive, SAUTER PAGE provoque l'effacement
de l'ecran.

## SAUV [Entree-Sortie Entree-Sortie]
   Directive SAUVER

   SAUVER ('FORMAT' ) OBJET1 ... OBJETi ;
        ('LABEL' CHA1 )
        ('MUET' )

   Objet :

   La directive SAUVER permet d'ecrire les objets OBJET1, ... OBJETi
sur le fichier logique IOSAU1 au format XDR (le defaut),BINAIRE ou FORMATE
defini par :

        OPTION SAUV (|'XDR' |) IOSAU1 ;
        |'FORM'|
        |'BINA'|

de maniere a interrompre un calcul, pour le reprendre ulterieurement.
Il ne s'agit pas d'un stockage de resultats en vue d'une recombinaison
ulterieure.

   L'ecriture se fait en incremental, c'est a dire que seuls les
objets n'ayant pas deja etes sauves et ceux ayant etes modifies seront
ecrits a la suite de ceux etant deja sur le fichier. Il est possible
de donner un "label" a cette partie de la sauvegarde dans la
perspective de relire le fichier jusqu'a ce label inclus.

   Commentaire :

   Tous les objets nommes, inclus ou references par les operandes
sont egalement sauves.

   Remarque :

   L'option facultative FORMAT permet l'ecriture en formate.
Elle DOIT etre prealablement precisee par la directive OPTI 'SAUV'.
Les fichiers formates sont encombrants. Cette option n'est a utiliser
que pour la mise au point. L'optio XDR permet de transferer des fichiers
entre ordinateurs d'architectures differentes.

   L'option facultative MUET demande au logiciel de ne signaler que
la fin de la sauvegarde

## SEIS [Mecanique Dynamique]
    Operateur SEISME

    CHAR1 = SEISME  EVOL1 | BAS1 | FLOT1 MOT1 ;
        | TAB1 |

    Objet :

    L'operateur SEISME cree un objet CHARGEMENT a partir d'une
description temporelle et d'une description spatiale sur la base modale
d'un seisme.

    Commentaire :

    EVOL1 : objet contenant la discretisation temporelle du
        seisme (type EVOLUTION).

    BAS1 : objet contenant la base modale de la structure
        (description spatiale) (type BASEMODA)

    TAB1 : objet contenant la base modale de la structure
        (description spatiale) (type TABLE)

    FLOT1 : coefficient multiplicateur applique au seisme
        (type FLOTTANT)

    MOT1 : nom (type MOT) definissant la direction du seisme,
        a choisir parmi : 'UX', 'UY', 'UZ'.

    CHARG1 : objet resultat (type CHARGEME)

    Remarque :

    Au 26/06/86, cet operateur ne fonctionne que pour les bases
modales.

    Il engendre un CHPOINT qui represente la repartition spatiale
(sur les ALFA) du chargement sismique.

    Ce champ multiplie par la fonction de temps donne les forces
generalisees :

        FN = - Q * GAM(t) * FLOT1
        NI

      oº Q est le deplacement generalise du NI-ieme mode dans la
        NI
direction I et GAM(t) l'acceleration.

## SENS [Mathematiques Autres]
  Operateur SENS

 a)

  TAB1 = SENS CHAM1 CHAM2 ;

 b)

  TAB2 = SENS TAB1 ;

  Objet :

a) SENSIBILITE

  L'operateur SENS calcule la difference des champs CHAM1 et
CHAM2 (CHAM1 - CHAM2) de type MCHAML.Lorsq'il a calcule cette
difference,l'operateur SENS fait la moyenne arithmetique de la
valeur du champ aux points de gauss pour avoir la valeur moyenne
du champ sur chaque sous-zone.
Ces valeurs sont alors rangees dans la table TAB1 indicee par des
entiers de 1 au nombre d'elements.

b) SENS

   L'operateur SENS determine le sens de parcours d'un ou
plusieurs contours orientes fermes en dimension 2.
La table TAB1 doit avoir le format de la table issue de
l'operateur CCON:

     TAB1 . entier ---> maillage du contour (SEG2 ou SEG3)

 La table TAB2 a pour format

     TAB2 . entier ---> +/- 1

 A chaque maillage est associe un entier
      +1 si le maillage est parcouru dans le sens trigonometrique
      -1 sinon

  Remarque :

a)
  Pour que l'operateur SENS calcule bien la difference des deux
  MCHAML, ils doivent presenter des sous zones elementaires
  similaires et des noms de composantes identiques.
  Cet operateur est utile en optimisation pour preparer le calcule
  de sensibilites.

b)
  Sous l'option MODE AXIS le contour n'est pas necessairement ferme.
  Les points situes sur l'axe OZ sont consideres comme lie entre eux
  par application de la symetrie.

## SGE [Fluides Resolution] (proc)
   Procedure SGE

   SYNTAXE ( EQEX ) : Cf operateur EQEX:

   ZONE $M 'OPER' 'SGE' 'RO' 'UN' 'MU' 'INCO' 'UN'

   OBJET :

Cette procedure calcule le terme de viscosite de sous-maille selon le
        t
modele de Smagorinsky : MUs= Ro Cs H**2. |Grad U + Grad U | ou
Cs est la constante de Smagorinsky (Cs=0.01), H la taille des mailles.
MUs est homogene a une viscosite dynamique (Kg/m/s).
Les effets lies a la temperature ne sont pas pris en compte pour le
moment.
Le resultat est place dans la table 'INCO' a l'indice 'MUT' et est
CHPOINT (SCAL SOMMET).

   Commentaires

   $M Modele NAVIER_STOKES
        MMODEL

   RO Densite
        FLOTTANT ou CHPOINT SCAL SOMMET ou MOT

   U Champ de vitesse moyen
        CHPOINT (VECT SOMMET)

   MU Viscosite dynamique moleculaire
        FLOTTANT ou CHPOINT SCAL SOMMET ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice MOT.

## SHFDT [Mecanique Dynamique] (proc)
    Procedure SHFDT

La procedure SHFDT est appelee par la procedure DECONV3D dans l'option
BIELAK pour onde incidente SH inclinee. Elle calcule la fonction de
transfert du mouvement d'un point dans le sol par rapport a un point de
reference a la surface.

## SI [Langage Base]
    Directive SI
    ------------ FINS

    SI LOG1 ;

    Objet :

    Les directives SI, SINON et FINSI permettent l'execution
conditionnelle de donnees suivant la valeur de la variable LOG1 (type
LOGIQUE)

    Exemple :

    BOOL = I > 10 ;
    SI BOOL ;

    J= 2 * I ; COMM execute si I est plus grand que 10
    LIST J ;

    SINON ;

    J= I ; COMM execute si I est plus petit que 10

    FINSI ;

    Note : SINON est optionnel.

## SIAR [Mathematiques Traitement]
Operateur SIAR (SIgnaux ARtificiel)

EVOL1 and/or EVOL2 and/or EVOL3 = SIAR ...

        ..... | EVOL4 EVOL5 LREEL1 (FLOT1  'TINI' FLOT2)  |
        | EVOL4  FLOT1 ('TINI' FLOT2)  | .....

        ..... ('ACCE' 'VITE' 'DEPL' )
        ('NCOU' ENTI1 )
        ('NPOI' ENTI2 )
        ('NSIN' ENTI3 )
        ('INIT' ENTI4 )

Objet :

L'operateur SIAR genere un ensemble de ENTI1 signaux non
stationnaires (en acceleration et/ou vitesse et/ou deplacement
selon la syntaxe indiquee) correspondant au spectre de puissance
stationnaire EVOL4 (comportant une courbe) et aux N fonctions de
modulation EVOL5 (comportant N courbes) associees aux bandes de
frequences extraites de LREEL1 [ la bande de frequence de la i-eme
fonction EVOL5 est donnee par le i-eme (frequence inferieure) et le
i+1-eme (frequence superieure) element de LREEL1 ]. Dans le cas ou
EVOL5 et LREEL1 ne sont pas donnes, la modulation est de 1 en temps
sur toute la plage de frequence de EVOL4.

Options :

- Par defaut on genere 3 series de signaux, en acceleration (EVOL1
  comportant ENTI1 courbes), en vitesse (EVOL2 idem EVOL1) et en
  deplacement (EVOL3: idem EVOL1). On ne peut generer qu'une seule
  serie de signaux en utilisant les mots cle 'ACCE'(leration),
  'VITE'(sse) et 'DEPL'(acement).

- Par defaut on ne genere qu'un seul signal par serie EVOL1 et/ou
  EVOL2 et/ou EVOL3. L'option 'NCOU' permet d'introduire un nombre
  ENTI1 plus eleve.

- Dans le cas ou EVOL5 et LREEL1 sont donnes, les signaux sont
  generes sur l'intervalle de temps defini par les abscisses dans
  EVOL5. Un intervalle plus restreint peut etre defini en
  introduisant les valeurs FLOT1 et/ou FLOT2, ce dernier apres
  le mot-cle 'TINI'.

- Dans le cas ou EVOL5 et LREEL1 ne sont pas donnes, les signaux
  sont generes de 0. a FLOT1. L'instant initial peut etre change
  en utilisant l'option 'TINI'.

- Le signal est genere sur une grille d'instant equidistant. Le
  nombre de point par defaut correspond a un intervalle elementaire
  de 0.02s. On peut aussi indiquer ce nombre a l'aide de l'option
  'NPOI' suivi de ENTI2.

- Le signal est genere a partir d'une recomposition en frequence.
  On peut specifier le nombre de frequence a l'aide du ENTI3 en
  utilisant l'option 'NSIN'. Par defaut ENTI3 correspond a des
  bandes de frequence de 0.1 Hz.

- La recomposition necessite un tirage de phase aleatoire. L'option
  'INIT' permet l'initialisation de generateur par l'utilisateur en
  introduisant ENTI4 (objet de type entier).

## SIF [Mecanique Rupture] (proc)
Procedure SIF

SIF MAT1 DEP1 TAB1 ;

        TAB1.'FRTFISS'
        .'LEVRE_1'
        .'LEVRE_2'
        .'MODMIXTE'
        .'MAILLAGE'
        .'DEBOUCH'
        .'PDEBOUCH'
        .'EPAI'
        .'FLEXION'
        .'MEMBRANE'

Objet :

Cette procedure calcule le facteur d'intensite de contraintes
en mode I (eventuellement en mode II ), a partir des deplacements
des levres de la fissure.
La valeur calculee est une moyenne sur les trois points les
plus proches de la pointe de fissure.
La procedure est applicable aux cas bidimensionnels, tridimen-
sionnels massifs et coques minces.
- En 2D, le probleme d'un chargement en mode mixte peut etre traite.
- En 3D massif , pour chaque noeud du front de fissure, le facteur
  d'intensite de contraintes est calcule a partir des deplacements
  des points situes dans le plan normal au front de fissure au noeud
  considere (le maillage doit etre elabore de maniere a prevoir
  l'existence de ces plans normaux au front de fissure). Si la
  fissure est debouchante, la formule de contraintes planes est
  appliquee pour les points situes en surface.
- En 3D coques minces, les facteurs d'intensite de contraintes de
  membrane et de flexion peuvent etre calculees. Le calcul du facteur
  d'intensite de contrainte en flexion est realise grace aux
  rotations aux noeuds induisant une deformation de peau. Le calcul
  en mode mixte est supporte.

Commentaire :

En entree :

MAT1 : Champ de caracteristiques materielles

DEP1 : Champ de deplacements

TAB1 : Objet de type TABLE ,indice par des mots, servant a
        definir les options et les parametres du calcul :

  Arguments pour un probleme bidimensionnel

   indice type objet commentaires
        pointe

  FRTFISS POINT pointe de la fissure

  LEVRE_1 MAILLAGE ligne decrivant les levres de la fissure
        si chargement en mode mixte, 1ere levre

  MODMIXTE LOGIQUE VRAI si chargement en mode mixte

  LEVRE_2 MAILLAGE si chargement en mode mixte, ligne
        decrivant la 2ieme levre de la fissure

  Arguments pour un probleme tridimensionnel massif

   indice type objet commentaires
        pointe

  FRTFISS MAILLAGE ligne decrivant le front de fissure

  LEVRE_1 MAILLAGE surface decrivant les levres de la fissure
        si chargement en mode mixte, 1ere levre

  MODMIXTE LOGIQUE VRAI si chargement en mode mixte

  LEVRE_2 MAILLAGE si chargement en mode mixte, surface
        decrivant la 2ieme levre de la fissure

  DEBOUCH LOGIQUE VRAI si la fissure est debouchante

  PDEBOUCH POINT/MAILLAGE points du front situes en surface

  Arguments pour un probleme tridimensionnel coques minces

   indice type objet commentaires
        pointe

  FRTFISS POINT pointe de la fissure

  LEVRE_1 MAILLAGE ligne decrivant les levres de la fissure
        si chargement en mode mixte, 1ere levre

  MODMIXTE LOGIQUE VRAI si chargement en mode mixte

  LEVRE_2 MAILLAGE si chargement en mode mixte, ligne
        decrivant la 2ieme levre de la fissure

  EPAI FLOTTANT epaisseur des coques

  MEMBRANE LOGIQUE VRAI pour le calcul du terme de
        membrane

  FLEXION LOGIQUE VRAI pour le calcul du terme de
        flexion

  En sortie :

  En sortie, TAB1 permet de retrouver les valeurs du facteur
  d'intensite de contraintes.

  indice type objet commentaires
        pointe

  K1 FLOTTANT/TABLE en 2D, flottant: valeur de K1,
        en 3D massif, table contenant
        les valeurs de K1 a chaque noeud
        du front,
        en 3D coques minces, table
        contenant 3 flottants :
        MEMBRANE : terme de membrane
        FLEXION : terme de flexion
        TOTAL : somme des deux

  K2 FLOTTANT/TABLE si chargement en mode mixte :
        en 2D, flottant : valeur de K2
        en 3D coques minces, table
        contenant 3 flottants :
        MEMBRANE : terme de membrane
        FLEXION : terme de flexion
        TOTAL : somme des deux

  Exemple : pour lister le facteur K calcule au noeud P15 du
        front de fissure ,il faudra coder : LIST (TAB1.K1.P15 )

  Remarque :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SIGM [Mecanique Resolution]
    Operateur SIGMA
    --------------- CALP CARA

    SIG1 = SIGMA ('NOER')  | ('LINE') |  MODL1 CHAM1 ( CHAM2 ) DEP1 ;
        |  'QUAD'  |

    Objet :

L'operateur SIGMA calcule un champ de contraintes SIG1 a partir d'un
champ de deplacements DEP1.

ATTENTION : cet operateur suppose un comportement elastique lineaire
du materiau et l'absence de deformation initiale.
(par ex. en cas de deformation due a un champ de temperature, il faudra
soustraire a ce champ de contraintes les contraintes d'origine
thermiques calculees par l'operateur THETA).

Par defaut, seuls les termes LINEAIRES des deformations sont pris en
compte. Si une autre hypothese de deformation (quadratique ...) est
souhaitee, le mot-cle associe ('QUAD'...) doit etre specifie.

Pour certains elements, il s'agit d'efforts (barres, poutres, tuyaux),
pour d'autres il s'agit de contraintes generalisees (coques minces)
Les contraintes sont calculees dans le repere general pour les
elements massifs et dans le repere local pour les elements coques,
plaques, poutres.

    Commentaire :

    'NOER' : Mot-cle indiquant de ne pas faire d'erreur en cas de
        changement de signe du jacobien.

    'LINE' : Mot-cle indiquant que seuls les termes du premier ordre
        en deplacement doivent etre utilises.
    'QUAD' : Mot-cle indiquant que les termes lineaire et quadratiques
        sont utilises.

    MODL1 : objet modele (type MMODEL)

    CHAM1 : Champ de caracteristiques materielles et eventuellement
        geometriques si necessaire pour certains elements (cf
        remarque ci-dessous) (type MCHAML, sous-type
        CARACTERISTIQUES) ou de matrices de Hooke (type MCHAML,
        sous-type MATRICE DE HOOKE).

    CHAM2 : Champ de caracteristiques (type MCHAML, sous-type
        CARACTERISTIQUES) necessaires pour certains elements
        (cf remarque ci-dessous) si CHAM1 est un champ de
        matrices de Hooke.

    DEP1 : champ de deplacements (type CHPOINT)

    SIG1 : champ de contraintes resultat (type MCHAML, sous-type
        CONTRAINTES)

    Remarques :

1. Il faut specifier des caracteristiques si la description
    geometrique de l'element ne peut se faire par le maillage;
    par exemple l'epaisseur d'elements de plaques ou les inerties
    de flexion pour les elements de poutres etc...

2. Dans le cas de coques excentrees, les contraintes sont calculees
    au niveau de la surface moyenne excentree.

3. Le calcul des contraintes du second ordre est implemente pour les
   elements suivants :
      - massifs : tous
      - lineiques : BARR POUT TUYA TIMO
      - plaques et coques : COQ2
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SIGN [Mathematiques Fonctions]
  RESU1 = 'SIGN' OBJET1 (MOT1) ;

Operateur SIGN

Objet :

L'operateur SIGN calcule le signe d'OBJET1.

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

## SIGNCORR [Mathematiques Traitement] (proc)
Procedure SIGNCORR

Cette procedure est appelee par la procedure SIGNSYNT

## SIGNDERI [Mecanique Dynamique] (proc)
    Procedure SIGNDERI

    EV02 = SIGNDERI EVO1

    Objet :

    La directive SIGNDERI ajoute une droite a l'accelerogramme pour
avoir les vitesse et deplacement nuls aux temps initial et final.

    Commentaire :

    EVO1 : signal a corriger (type EVOLUTION)
    EVO2 : signal corrige (type EVOLUTION)

## SIGNENVE [Mathematiques Traitement] (proc)
Procedure SIGNENVE

Cette procedure est appelee par la procedure SIGNSYNT

## SIGNSYNT [Mathematiques Traitement] (proc)
    Procedure SIGNSYNT

    EV01 = SIGNSYNT MOT1 TAB1

    Objet :

    La procedure SIGNSYNT cree des signaux synthetiques par recombinaison
de sinusoïdes a phases aleatoires. Deux options sont prevues :
        FABR ET BLAN

    Commentaire :

    MOT1 : mot-cle (type MOT ) caracterisant la sortie desiree
    TAB1 : objet de type TABLE
    EVO1 : signal(signaux) cree(s)

  1-OPTION creation de signaux synthetiques a partir d'un spectre de
        reference

   MOT1 = FABR

   TAB1 'MOTIT' ( type MOT) texte sur 16 caracteres max.

   TAB1 'SEISME' 'SPECTRE' (type EVOL) spectre de reference
   TAB1 'SEISME' 'AMORT' (type FLOTTANT) amortissement
   TAB1 'SEISME' 'TYPSP' (type MOT)) type du spectre
        'ACCE' 'VITE' ou 'DEPL'

   TAB1 'SIGNAL' 'ENVE' (TYPE MOT) facultatif : type de
        l'enveloppe = 'PLATLIN'
        par defaut enveloppe constant
   TAB1 'SIGNAL' 'NP' (TYPE ENTIER) tel que le nombre de points
        du signal : 2 ** NP
   TAB1 'SIGNAL' 'DUREE' (TYPE FLOTTANT) duree du signal
   TAB1 'SIGNAL' 'TDEBUT' (TYPE FLOTTANT) debut du plateau
   TAB1 'SIGNAL' 'TFIN' (TYPE FLOTTANT) fin du plateau

Signal
   ^
   |  --------
   |  /  \
   |  /  \
   | /  \
   |----|--------|---|-----> temps
        tdebut tfin T

   TAB1 'NBITER' (type ENTIER) Nombre d'iterations demandees
   TAB1 'NBSIGN' (type ENTIER) Nombre de signaux
   TAB1 'NALEAT' (type ENTIER) Parametre d'initialisation
        des phases
   TAB1 'FRCOUP' (type FLOTTANT) frequence de coupure
   TAB1 'OPTSORT' (type MOT) option facultative de sorties
        intermediaires :
        SPECTRE : a chaque iteration
        on sortira les spectres
        obtenus
        SIGNAUX : a chaque iteration
        on sortira les spectres e
        les signaux

       ++ RESULTAT EN SORTIE

   EV01 (type TABLE) contient le(s) signal(ux)
        genere(s) (ecart-type unite)

 2-OPTION signal bruit blanc par combinaison de sinusoïdes a phases
        aleatoires

   MOT1 = BLANC

   TAB1 'MOTIT' (type MOT) texte sur 16 caracteres max.
   TAB1 'NP' (type ENTIER) nombre de points = 2 ** NP
   TAB1 'DELTAF' (type FLOTTANT) pas en frequence
   TAB1 'NALEAT' (type ENTIER) parametre d'initialisation
        des phases

       ++ RESULTAT EN SORTIE

   EV01 (type EVOLUTION) contient le signal
        genere (ecart-type unite)

       REMARQUES
    La methode de generation utilise la TFR. On doit donc utiliser
        2 ** NP points

  Le spectre de reference doit couvrir l'intervalle :
     fmin < 1 / T avec T duree du signal
     fmax > 1 / (2 * DT) avec DT = T / (2 ** NP)

## SIGS [Mecanique Dynamique]
    Operateur SIGSOL

      SOL2  =  SIGSOL  MODL1  MAT1  ( CAR1 )  |  SOL1  |  ;

    Objet :

    L'operateur SIGSOL calcule les contraintes a partir d'un objet de
    type SOLUTION ou d'un objet de type TABLE.

      Commentaire:

      MODL1: objet modele ( type MMODEL ).

      MAT1 : champ de caracteristiques materielles et geometriques
        ou de matrices de Hooke (type MCHAML, sous-type
        CARACTERISTIQUES ou MATRICE DE HOOKE)

      CAR1 : champ de caracteristiques geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

  a/ cas de l'objet SOLUTION :

    SOL1 : objet de type SOLUTION de sous-type MODE, SOLUSTAT ou
        PSEUMODE

    SOL2 : objet de type SOLUTION de sous-type identique a celui de SOL1
        SOL2 est en fait identique a SOL1, mais complete par les
        contraintes.

  b/ cas de l'objet TABLE :

    TAB1 : objet TABLE definissant les modes, les pseudo-modes, ...
        - de sous-type BASE_MODALE, ou
        - de sous-type ENSEMBLE_DE_BASES.

    SOL2 : objet de type TABLE, identique a TAB1 mais complete
        - a l'indice 'CONTRAINTE_MODALE' pour les modes,
        - a l'indice 'CONTRAINTE' pour les pseudo-modes,
        par le champ de contraintes.

    Remarque :

    Les caracteristiques CAR1 sont facultatives. Leur support
geometriques doit etre inclus dans celui de MAT1. Si on met CAR1, il
faut le mettre apres MAT1.

    Il faut specifier les caracteristiques, si la description
geometrique de l'element ne peut se faire par le maillage; par exemple,
l'epaisseur d'elements de plaques ou les inerties d'elements de poutres.

## SILAM [Post-traitement Affichage] (proc)
Procedure SILAM
--------------- @LACALC

SILAM TAB_LAM DEPL1 NZON VET1 P0 ;

Objet :

Cette procedure permet de visualiser la variation des contraintes
suivant l'epaisseur par rapport a un point demande.

En entree:

TAB_LAM Table caracteristique du multicouche
DEPL1 Champ des deplacements
NZON Numero de la zone demandee
VET1 Direction d'orientation du champ des contraintes
P0 Point pur lequel on veut visualiser les contraintes

## SIMP [Mathematiques Fonctions]
Operateur SIMPLEX

ENT1 TAB4_X TAB5_D= SIMPLEX TAB1_F TAB2_I TAB3_E (FLOT1);

Objet :

L'operateur SIMPLEX cherche le maximum d'une fonction lineaire
ou linearisee F(Xi) de la forme :

F(Xi) = F0 + Fi * Xi ;

soumises aux contraintes suivantes:

- Xi >EG 0. contraintes primaires

- Iji * Xi <EG Ij contraintes additionnelles de type inegalite

- Eji * Xi = Ej contraintes additionnelles de type egalite

Dans le cas ou il y a une solution non infinie on indique :

- les valeurs de Xi et celle correspondante de F

- les distances Dj aux inegalites

Commentaire :

TAB1_F : table (type TABLE) contenant :
        - dans TAB1_F.0 : la valeur F0 (FLOTTANT)
        - dans TAB1_F.i : les valeurs Fi (FLOTTANT)

TAB2_I : table (type TABLE) decrivant les inegalites
        - dans TAB2_I.j.0 : la valeur Ij (FLOTTANT)
        - dans TAB2_I.j.i : les valeurs Iji (FLOTTANT)

TAB2_E : table (type TABLE) decrivant les egalites
        - dans TAB2_E.j.0 : la valeur Ej (FLOTTANT)
        - dans TAB2_E.j.i : les valeurs Eji (FLOTTANT)

FLOT1 : FLOTTANT facultatif qualifiant la convergence de la
        solution (par defaut 1.D-10)

ENT1 : information sur la solution
        - ENT1 = 0 une solution non infinie existe
        - ENT1 = 1 solution infinie
        - ENT1 =-1 pas de solution possible

TAB4_X : table (type TABLE) contenant les resultats primaires :
        - dans TAB1_X.0 : la valeur de F (FLOTTANT)
        - dans TAB1_X.i : les valeurs Xi (FLOTTANT)

TAB5_D : table (type TABLE) contenant les distances aux inegalites:
        - dans TAB5_D.i : les valeurs Di (FLOTTANT)

Remarques :

Le nombre d'egalites independantes doit etre strictement inferieur
au nombre d'inconnues.

En entree comme en sortie les indices des tables correspondant a des
valeurs nulles peuvent etre omis.

S'il n'y a pas de contraintes additionnelles de type inegalite ou
(exclusif) de type egalite, on doit cependant entrer une table vide.

Si ENT1 n'est pas nul les tables TAB4_X TAB5_D sont vides.

## SIN [Mathematiques Fonctions]
  RESU1 = 'SIN' OBJET1 (MOT1) ;

Operateur SIN
------------- ACOS ASIN ATG

Objet :

L'operateur SIN calcule le sinus de l'objet OBJET1.
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

## SINH [Mathematiques Fonctions]
  RESU1 = 'SINH' OBJET1 (MOT1) ;

Operateur SINH
-------------- ACOS ASIN ATG

Objet :

L'operateur SINH calcule le sinus hyperbolique de l'objet OBJET1.

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

## SINO [Langage Base]
    Directive SINON
    --------------- FINS

    SINON ;

    Objet :

    Les directives SI, SINON et FINSI permettent l'execution condition-
nelles de donnees.

    Exemple :

    BOOL = I > 10 ;
    SI BOOL ;
    J= 2 * I ; COMM EXECUTE SI I EST PLUS GRAND QUE 10 ;
    LIST J ;
    SINON ;
    J= I ; COMM EXECUTE SI I EST PLUS PETIT QUE 10 ;
    FINSI ;

    Note : SINON est optionnel.

## SISSIB [Mecanique Dynamique] (proc)
    Procedure SISSIB

    TAB2 = SISSIB TAB1 ;

    Objet :

    La procedure SISSIB calcule la reponse sismique d'une structure a
l'aide d'une methode spectrale

    Commentaire :

    TAB1 : objet de type TABLE de sous-type DONNEE contenant les
        donnees suivantes :

    TAB1.'STRUCTURE' : TAB2 (type TABLE) de sous-type BASE_MODALE
        contenant a l'indice MODES les modes propres
        de la structure et a l'indice 'PSEUDO_MODES'
        (facultatif) les pseudomodes associes a une
        excitation sismique.

    TAB1.'AMORTISSEMENT': LREE1 (type LISTREEL) contenant les
        amortissements modaux des modes de la
        structure.

    TAB1.'EXCITATION' : TAB3 (type TABLE) de sous-type 'EXCITATION'
        indicee par un entier I1 variant de 1 au
        nombre de directions d'excitation a prendre
        en compte dans le calcul (<EG 3).
    TAB3.I1 : objet de type TABLE telle que :
      TAB3.I1.'DIRECTION' : MO1 (type MOT) valeur 'X' ou 'Y'
        ou 'Z' decrivant la direction de
        l'excitation
      TAB3.I1.'SPECTRE' : EVO1 (type EVOLUTION)
        contenant le(s) spectre(s)
        en pseudo acceleration du
        mouvement sismique
      TAB3.I1.'AMORTISSEMENT' : LREE2 (type LISTREEL)
        contenant les amortissements
        des spectres
      TAB3.I1.'ACCELERATION_MAXIMALE' : FLOT1 (type FLOTTANT)
        (facultatif) acceleration
        maximale du seisme.

    TAB1.'RECOMBINAISON_MODES' : MO2 (type MOT) type de recombinaison
        a choisir parmi :
        SRSS : combinaison quadratique simple
        ROSENBLUETH : combinaison quadratique complete
        formule de ROSENBLUETH
        CQC : combinaison quadratique complete
        formule de DER KIUREGHIAN
        DIX_POUR_CENT : combinaison par la regle des 10%.

    TAB1.'DUREE' : FLOT2 (type FLOTTANT), duree de
        la partie forte du seisme.
        Necessaire uniquement dans le
        cas de la formule de ROSENBLUETH

    TAB1.'RECOMBINAISON_DIRECTIONS' : MO3 (type MOT) regle de
        recombinaison des directions
        de seisme (actuellement une seule
        possibilite : 'QUADRATIQUE').

    TAB1.'SORTIES' : TAB4 (type TABLE) de sous-type 'SORTIES'
        contenant :
        TAB4.'DOMAINE' : objet de type MAILLAGE ou MMODEL
        designant le domaine geometrique sur
        lequel on veut des sorties (il faut
        fournir un objet de type MMODEL quand
        on demande des sorties relatives aux
        contraintes)
        TAB4.'DEPLACEMENTS' : objet de type LOGIQUE (VRAI OU FAUX)
        indiquant que l'on veut sortir les
        deplacements.
        TAB4.'ACCELERATIONS' : objet de type LOGIQUE (VRAI OU FAUX)
        indiquant que l'on veut sortir les
        accelerations.
        TAB4.'CONTRAINTES' : objet de type LOGIQUE (VRAI OU FAUX)
        indiquant que l'on veut sortir les
        contraintes.
        TAB4.'REACTIONS' : objet de type LOGIQUE (VRAI OU FAUX)
        indiquant que l'on veut sortir les
        reactions.

    TAB1.'IMPRESSION' : objet de type LOGIQUE indiquant que l'on veut
        l'impression automatique des resultats
        (facultatif, par defaut : FAUX).

    TAB1.'TRONCATURE' : objet de type LOGIQUE indiquant que l'on veut
        tenir compte de l'effet de troncature de la
        base modale a l'aide des pseudo-modes.
        (facultatif, par defaut : FAUX).

    TAB1.'REPRISE' : Objet de type TABLE (facultatif) genere lors
        d'un precedent appel a SISSIB pour la meme
        structure, contenant les valeurs des spectres
        pour chacun des modes ainsi que les
        coefficients de correlation entre modes qui
        dans ce cas ne sont pas recalculer.

    TAB2 : objet de type TABLE contenant les resultats
        du calcul :

    TAB2.'REPRISE' : objet de type TABLE pouvant etre fournie
        comme donnee a SISSIB lors d'un calcul
        ulterieur sur la meme structure (voir
        TAB1.'REPRISE').

    TAB2.MO4.MO5 : objet de type CHPOINT ou MCHAML
        contenant les sorties MO5
        (objet de type MOT, de valeur
        DEPLACEMENTS, ACCELERATIONS,
        CONTRAINTES ou REACTIONS) pour
        la direction d'excitation MO4
        (objet de type MOT, de valeur
        X, Y ou Z).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SMTP [Multi-physique Multi-physique]
    Operateur SMTP

    (RIG2) (CHP3) = SMTP MODE1 RIG1 (TAB2) (CHP1) (CHP2) ;

    Objet :

    L'operateur SMTP cree la contribution au systeme matriciel
en trace de charge des termes sources et des termes de convection
dans le cadre de la resolution de l'equation de diffusion-convection
par une methode d'elements finis mixtes hybrides (modele DARCY).

    Commentaire :

       MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

       RIG1 : Objet rigidite de sous type MASSEHYB contenant les
        matrices masses elementaires inverses pour les elements
        hybrides (cf. MHYB).

       TAB2 : Objet table de sous type DARCY_TRANSITOIRE contenant
        les conditions initiales et les coefficients pour le
        schema d'integration en temps dans le cas transitoire
        (cf procedure darcytra).

       CHP1 : Objet de type CHPOINT contenant l'integrale du terme
        source en chaque element. Le support geometrique de
        ce champ est le MAILLAGE des points CENTRE.
        Le nom de la composante du CHPOINT est SOUR.

       CHP2 : Objet de type CHPOINT contenant le flux a travers
        chaque face de la vitesse. Le support geometrique de
        ce champ est le MAILLAGE des points FACE .
        Le nom de la composante du CHPOINT est FLUX.

       CHP3 : Objet resultat de type CHPOINT contenant differentes
        contributions au second membre. Le support geometrique
        de ce champ est le MAILLAGE des points FACE.
        Le nom de la composante du CHPOINT est FLUX.
        En permanent, CHP3 n'est cree que si CHP1 est donne.

       RIG2 : Objet rigidite de sous type CONVEFMH contenant les
        matrices elementaires provenant des termes convectifs.
        RIG2 n'est cree que si CHP2 est donne. En transitoire
        RIG2 n'est pas cree si la convection est explicite.

## SOLS [Mecanique Dynamique]
    Operateur SOLS

    SOL1 = SOLS ATTA1 STRU1 ;

    Objet :

    L'operateur SOLS fabrique des solutions statiques U pour l'ensemble
des liaisons permanentes de ATTA1 qui s'appliquent sur la structure STRU
    Il peut s'agir :

        - soit de liaisons portant sur des noeuds libres,
U est alors solution de : KU + Pt = 0

        - soit de liaisons portant sur des noeuds bloques,
U est alors obtenu en imposant un deplacement unite aux noeuds de
liaison.

    Commentaire :

    SOL1 : objet resultat (type SOLUTION, sous-type SOLUSTAT)

    STRU1 : structure elementaire (type STRUCTURE)

    ATTA1 : ensemble des liaisons permanentes (type ATTACHE)

## SOLVEFMH [Fluides Resolution] (proc)
      Operateur SOLVEFMH

APPELE PAR TRANGEOL- PAS POUR UTILISATEUR

|-----------------------------------------------------------------|
| Phrase d'appel (en GIBIANE)  |
|-----------------------------------------------------------------|
|  |
| mattr TABRES tfin tcfin = SOLVEFMH MoDARCY ChPSour  |
|  MassEFMH (MatTR ou mattM) SMTR Tcini cini  |
|  nomespec nbespece nbsource TABRES tbdartra |
|  CHCLIM ;  |
|  |
|  |
|-----------------------------------------------------------------|
| Generalites : MATTEFMH construit la matrice de discretisation  |
|  du probleme de transport convection-diffusion pour|
|  le premier pas de tps d'un algorithme transitoire.|
|  Le second membre et les Conditions limites de flux|
|  sont pris en compte.  |
|  RESTE TCINI, DECENTR et TERME LIN  |
|-----------------------------------------------------------------|
|  |
|-----------------------------------------------------------------|
|  ENTREES  |
|-----------------------------------------------------------------|
| MoDARCY  : modele Darcy.  |
|  |
| Deltat  : pas de temps utilise pour calculer la concentration  |
|  |
| ChPSour  : Champ par points des sources volumiques par unite de |
|  temps (support maillage centre). Composante associees|
|  aux especes  |
|  |
| MassEFMH : matrice elementaire EFMH  |
|  |
| MatTr  : matrice globale sur les traces - rigidite  |
|  argument optionnel on donne alors martTM  |
|  |
| MatTM  : matrice globale sur les traces - Matrik  |
|  argument optionnel on donne alors matrTR  |
|  |
| SMTr  : second membre sur les traces  |
|  |
| Tcini  : Trace de concentration aux faces (eventuellement a  |
|  plusieurs composantes (especes) - sert a initialiser |
|  le XINIT de KRES et a calculer la valeur de la  |
|  concentration au centre  |
|  |
| nomespec : liste des noms de composante des especes dans Cini  |
|  |
| nbespece : nombre de composante de Cini, soit nombre d'especes  |
|  |
| nbsource : nombre de composantes du terme source qd X especes  |
|  |
| TABRES  : Table complete definissant les options de resolution |
|  pour 'KRES'.  |
|  |
| TbDarTra : table Darcy transitoire utilisee par MHYB, SMTP ...  |
|  |
| CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
|  Chpoint a n composantes contenant les conditions aux |
|  limites de Neumann et Dirichlet par espece.  |
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
|  |
| Tcfin  : Trace de concentration aux faces (eventuellement a  |
|  plusieurs composantes (especes) - etat final apres  |
|  resolution  |
|  |
| cfin  : concentration apres calcul pour toutes les especes  |
|  |
| TABSORT  : Table complete definissant les options de resolution |
|  pour 'KRES'.  |
|  |
| Matk  : matrice globale sur les traces pour la convection  |
|  en format matrik. Elle differe de la matrice entree |
|  si cette derniere est une rigidite car traduite en  |
|  Matrik. Elle contient egalement les preconditionnemen|
|  cree par l'operateur de resolution KRES  |
|  |
|-----------------------------------------------------------------|

## SOLVVF [Fluides Resolution] (proc)
Operateur SOLVVF

 APPELE par TRANGEOL

|-----------------------------------------------------------------|
| Phrase d'appel (en GIBIANE)  |
|-----------------------------------------------------------------|

      matsor TABRES cfin cflu cfluco = SOLVVF MoDARCY
        ChPSour Mattt Smtr Cini Mctot Mdiff Difftot
        Qface nomespec nbespece
        nbsource OPTRES CHCLIM Nouvmat ;

|-----------------------------------------------------------------|
| Generalites : MATTVF construit la matrice de discretisation  |
|  du probleme de transport convection-diffusion pour|
|  le premier pas de tps d'un algorithme transitoire.|
|  Le second membre et les Conditions limites de flux|
|  sont pris en compte.  |
|  RESTE TCINI, DECENTR et TERME LIN  |
|-----------------------------------------------------------------|
|  |
|-----------------------------------------------------------------|
|  ENTREES  |
|-----------------------------------------------------------------|
| MoDARCY  : modele Darcy.  |
|  |
| ChPSour  : Champ par points des sources volumiques par unite de |
|  temps (support maillage centre). Composante associees|
|  aux especes  |
|  |
| Mattt : matrice discretisation  VF  |
|  |
| SMTr  : second membre sur les traces  |
|  |
| nomespec : liste des noms de composante des especes dans Cini  |
|  |
| nbespece : nombre de composante de Cini, soit nombre d'especes  |
|  |
| nbsource : nombre de composantes du terme source qd X especes  |
|  |
| TABRES  : Table complete definissant les options de resolution |
|  pour 'KRES'.  |
|  |
|  |
| CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
|  Chpoint a n composantes contenant les conditions aux |
|  limites de Neumann et Dirichlet par espece.  |

| NOUVMAT  : Logique affecte a VRAI lorsque que Matot vient
|  d'etre calculee
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
| Matk  : matrice globale VF
|  |
| cfin  : concentration apres calcul pour toutes les especes  |
|  |
| TABSORT  : Table complete definissant les options de resolution |
|  pour 'KRES'.  |
|  |
|-----------------------------------------------------------------|

## SOMM [Mathematiques Autres]
    Operateur SOMME

CHAP{Calcul de la somme des valeurs d'une liste}

    | REEL2 | = SOMME | LREEL1 | ;
    | ENTI2 |  | LENTI1 |

    Commentaire :

     LREEL1/LENTI1 : liste de valeurs a sommer (type LISTREEL/LISTENTI)
        (= {x1 x2 x3 ...})

     REEL2/ENTI2 : objet resultat (type FLOTTANT/ENTIER)
        (= x1 + x2 + x3 + ...)

CHAP{Calcul de la somme cumulee des valeurs d'une liste}

    | LREEL2 | = SOMME 'CUMU' | LREEL1 | ;
    | LENTI2 |  | LENTI1 |

    Commentaire :

     LREEL1/LENTI1 : liste de valeurs a sommer (type LISTREEL/LISTENTI)
        (= {x1 x2 x3 ...})

     LREEL2/LENTI2 : liste resultat (type LISTREEL/LISTENTI)
        (= {x1 (x1+x2) (x1+x2+x3) ...})

## SOMT [Mathematiques Autres]
 Operateur SOMT

 RESU1 = SOMT CHP1 ;

 Objet :

Cet operateur permet de sommer les valeurs d'un champoint.

- CHP1 doit etre un champoint a une seule composante de
  type SCAL.
- RESU1 correspond a la somme des valeurs du champoint. C'est
  un objet de type FLOTTANT.

Cet operateur est appele a disparaitre.
Il est preferable d'utiliser :

        RESU1 = MAXI (RESULT CHP1) ;

## SORE [Thermique Modele]
 Operateur SORET

    RIG1 = SORET MMODE1 MAT1 CHAM1 CHPO1 ;

  Objet :

  L'operateur SORET cree une matrice de type conductivite pour des
  problemes de diffusion particuliers

  Commentaire :

  MMODE1 : Modele de 'THERMIQUE' 'CONDUCTION' ou 'DIFFUSION' 'FICK'
        (Type MMODEL)

  MAT1 : Champ de caracteristiques materiau
        (Type MCHAML)

  CHAM1 : Multiplicateur K dans l'equation ci-apres
        (Type MCHAML)

  CHPO1 : Champ potentiel dont on veut calculer le gradient
        H dans l'equation ci-apres
        (Type CHPOINT)

  RIG1 : matrice de rigidite sous type conductivite
        (Type RIGIDITE)

Remarque importante :
     Construit la matrice correspondant au flux suivant :

        Ji = -Di.K.(GRAD H).Ci

      Ji Densite de flux de l'espece i
      Di Coefficient de diffusion de l'espece i
      Ci Concentration de l'espece i
      H Potentiel induisant un courant proportionnel a Ci
      K Coefficient multiplicateur du flux

## SORT [Entree-Sortie Entree-Sortie]
    Directive SORTIR
    ---------------- REST SAUV

    SORT (|'AVS' |) [objet(s)] [options] ;
        |'EXCE'|
        |'ABAQ'|
        |'MED' |
        |'VTK' |
        |'MAT' |
        |'CHAI'|
        |'FER '|
        |'NAS '|
        |'STL '|

    Objet :

    Sortie d'objets GIBI vers un fichier défini au préalable par
    l'instruction :

    OPTI 'SORT' NOMFIC ;

    Il est inutile de spécifier l'extension dans NOMFIC.

    Remarque : On peut aussi utiliser la syntaxe : 'OPTI' 'SORT' N1 ;
        où N1 est le numéro d'unité logique (N1 = 7 par défaut).
        Le fichier de sortie sera alors nommé "fort.N1". Ceci
        n'est toutefois PAS recommandé.

CHAP{Sortie standard}
    | Sortie standard  |

    SORT MAIL1 ('NOOP') ;

    En l'absence de mot-clé, la directive SORTir écrit la géométrie
    définie par l'objet MAIL1 (type MAILLAGE). Tous les sous-objets
    nommés contenus dans MAIL1 figurent dans le fichier de sortie.

    Il est possible de relire ce maillage grâce à la directive LIRE.

    La numérotation des noeuds du maillage sorti est optimisée pour
    une résolution par la méthode de CROUT. Si l'optimisation n'est
    pas désirée, mettre le mot-clé 'NOOP'.

    Remarque : Cette directive existe pour compatibilité avec les
        versions antérieures de CASTEM et n'est pas appelée à
        être améliorée (le niveau de sortie utilisé est bloqué
        à 2)

        Dans le contexte d'une utilisation exclusive avec CASTEM,
        utilisez de préférence SAUVer (et RESTituer).

CHAP{Sortie 'AVS '}
    | Sortie AVS  |

    SORT 'AVS' (MAIL1) (CHPO1) (CHML1) ('SUIT') ('TEMP' FLOT1) ;

    Lorsque le mot-clé 'AVS' est specifié, la directive SORTir écrit
    MAIL1 (type MAILLAGE), CHPO1 (type CHPOINT) et CHML1 (type MCHAML)
    au format AVS UCD ASCII (extension .inp).

    La présence de chacun des trois arguments est facultative, mais au
    moins l'un des trois doit être présent.

    La partie de la géometrie sortie est déterminée par (dans l'ordre
    de priorité décroissante) :
       - le maillage MAIL1
       - le support du champ par éléments CHML1
       - le support du champ par points CHPO1

    Seuls les points qui appartiennent à la partie de la geométrie
    specifiée ci-dessus sont sortis. Le critère d'appartenance est
    le numéro du noeud et non sa position.

    Lorsqu'un MAILLAGE et un MCHAML sont fournis, on vérifie que le
    support du MCHAML contient entièrement le MAILLAGE ; dans le cas
    contraire un message d'erreur est géneré.

    Lorsqu'un CHPOINT est présent dans la liste des arguments et que la
    geométrie est spécifiée (soit par un MAILLAGE soit par un MCHAML),
    on verifie que l'intersection du support du CHPOINT avec cette
    geométrie est non vide. Si ce n'est pas le cas, la sortie du
    CHPOINT est annulée. Lorsque le support du CHPOINT ne couvre pas
    entièrement la géometrie, le CHPOINT est étendu sur le reste de
    la géometrie avec des valeurs nulles.

    Le MCHAML ne doit contenir qu'une seule valeur (de chaque
    composante) par élement. Cette contrainte est imposée par AVS.
    Dans un cas général, il convient donc de changer les noeuds support
    du MCHAML à sortir en centres de gravité des elements (opérateur
    CHANger).

    La présence du mot-clé 'SUIT' permet de ne pas écraser les données
    écrites précédemment et de rajouter le nouvel enregistrement à la
    suite du fichier. Dans ce cas précis, il ne faut pas utiliser
    OPTI 'SORT' avant d'appeler SORT 'AVS'. Le fichier pourrait alors
    ne pas être disponible pour des applications externes tant qu'il
    n'est pas refermé (en utilisant OPTI "SORT" à nouveau ou en
    quittant CASTEM).

    Le mot-clé 'TEMP' (suivi par un FLOTTANT) donne la possibilité
    de rajouter au fichier AVS une variable globale 'time' qui
    permettra d'associer les données écrites à un instant précis de la
    simulation.

CHAP{Sortie 'EXCE' (EXCEL TM)}
    | Sortie EXCEL (TM)  |

    SORT 'EXCE' OBJ1 (... OBJn) ('NCOL' ENTI1) ('SEPA' |'PVIR'|) ...
        |'VIRG'|
        |'ESPA'|
        |'TABU'|
        |'OBLI'|
        ... ('DIGI' ENTI2) ;

    avec OBJi = [ LENTIi | LREELi | LMOTSi | EVOLi | TABi ]

    Lorsque le mot-clé 'EXCE' est specifié, la directive SORTir écrit
    des données tabulaires sous forme de .csv (Comma-Separated Values),
    interprétable par des logiciels comme Microsoft EXCEL ou MATLAB par
    exemple.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SOUC [Langage Base]
Operateur SOUCIS

L1 = SOUCI (N1);

Objet:

L' operateur SOUCI gere la signalisation des soucis.

Il rend un logique vrai si le souci est non nul et faux sinon.
Suivi par un entier N1, il positionne l'indicateur de souci courant.

Remarques:

Le souci est croissant mais peut être remis a zero.

Chaque assistant a son souci propre.

## SOUDAGE [—] (proc)
    Procedure SOUDAGE

CHAP{1ere Fonction : specification d'une sequence de soudage}
PART{Specification generale}

    Objet :

        La procedure SOUDAGE permet de definir une sequence de soudage,
    dont la description est stockee dans une table qui contient aussi
    des donnees d'entree, principalement des parametres relatifs au
    procede de soudage (vitesse de soudage, puissance, debit de fil...).

        La procedure possede 3 options :
        - POINT : pour definir un point de soudure ;
        - PASSE : pour definir une passe de soudage ;
        - DEPLA : pour definir un deplacement de l'outil.
        La specification de la sequence de soudage se fait par des appels
    successifs a la procedure en combinant ces differentes options.

       En sortie, la table contient des donnees servant a la definition
    d'un calcul de soudage (evolution de la puissance thermique au cours
    du temps, trajectoire de l'outil, etc.)

    Sa syntaxe generale est :

    SOUDAGE TAB1 | POINT  ... ;
        | PASSE
        | DEPLA

    Remarque : la procedure SOUDAGE ne fonctionne qu'en dimension 3.

PART{Donnees d'entree}

    TAB1 . VITESSE_DE_SOUDAGE : objet FLOTTANT, vitesse de soudage

    TAB1 . PUISSANCE_DE_SOUDAGE : objet FLOTTANT, puissance thermique
        de soudage

    TAB1 . DIAMETRE_DE_FIL : objet FLOTTANT, diametre du fil de
        metal d'apport

    TAB1 . VITESSE_DE_FIL : objet FLOTTANT, vitesse de devidement
        du fil de metal d'apport

    TAB1 . DEBIT_DE_FIL : objet FLOTTANT, debit volumique de
        fil de metal d'apport (ignore si
        les indices VITESSE_DE_FIL et
        DIAMETRE_DE_FIL sont renseignes)

    TAB1 . VITESSE_DE_DEPLACEMENT : objet FLOTTANT, vitesse de deplacement
        de la torche sans soudage (par defaut,
        egal a VITESSE_DE_SOUDAGE)

    TAB1 . POINT_DE_DEPART : objet POINT, origine de la sequence
        de soudage ((0 0 0) par defaut)

    TAB1 . TEMPS_DE_COUPURE : objet FLOTTANT, temps de mise a zero
        ou a valeur nominale de la puissance
        de soudage (0,1 par defaut)

    TAB1 . LARGEUR_DE_PASSE : objet FLOTTANT, largeur d'une passe
        (requis pour appel option DEPLA COUCHE)

PART{Option POINT}

    Syntaxe :

    SOUDAGE TAB1 'POINT' FLOT1 ('PUIS' FLOT2) ('DEBI' FLOT3) ('EVEN' MOT1 (FLOT4))' ;

    Commentaire :

    FLOT1 : objet FLOTTANT, duree de realisation du point de soudure

    FLOT2 : objet FLOTTANT, puissance thermique utilisee pour la
        realisation de ce point de soudure. Ne modifie pas la
        valeur fournie dans TAB1.'PUISSANCE_DE_SOUDAGE'

    FLOT3 : objet FLOTTANT, debit de fil utilise pour la realisation
        de ce point de soudure. Ne modifie pas la valeur fournie
        dans TAB1.'DEBIT_DE_FIL'

    MOT1 : objet MOT, evenement relatif a la realisation de ce point
        de soudure.

    FLOT4 : objet FLOTTANT, duree du transitoire genere par cet evenement
        (pas de transitoire par defaut).

PART{Option PASSE}

    Syntaxe :

    SOUDAGE TAB1 'PASSE' | 'DROI' P1  | ('RELA') ('VITE' FLOT1) ...
        | 'CERC' P1 P2 (N1) |  'ABSO'
        | 'MAIL' LIGN1

    ... ('PUIS' FLOT2) ('DEBI' FLOT3) ('EVEN' MOT1 (FLOT4))' ;

    Objet :

       L'option PASSE permet de specifier la realisation d'une passe
    partant du point courant et suivant :
       - DROI : une ligne droite jusqu'au point P1 ;
       - CERC : un arc de cercle de centre P2 jusqu'au point P1 ;
       - MAIL : la ligne de maillage LIGN1.

    Commentaire :

    P1 : objet POINT, extremite finale de la passe

    P2 : objet POINT, centre du cercle

    N1 : objet ENTIER, nombre de segments discretisant l'arc de cercle
        (par defaut, valeur calculee pour avoir 5 degres d'angle
        entre deux segments).

    LIGN1 : objet MAILLAGE, ligne de maillage orientee representant
        la trajectoire de la passe

    'RELA' : objet MOT, indique que les coordonnees des points sont fournies
        relativement au point courant

    'ABSO' : objet MOT, indique que les coordonnees des points sont fournies
        dans le repere general de coordonnees

    FLOT1 : objet FLOTTANT, vitesse de soudage utilisee pour la
        realisation de cette passe. Ne modifie pas la
        valeur fournie dans TAB1.'VITESSE_DE_SOUDAGE'

    FLOT2 : objet FLOTTANT, puissance thermique utilisee pour la
        realisation de cette passe. Ne modifie pas la
        valeur fournie dans TAB1.'PUISSANCE_DE_SOUDAGE'
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SOUR [Thermique Modele]
    Operateur SOURCE

    CHPO1 =  SOURCE  MODE1 | VAL1 GEO1 | (CAR1) ('ELEM') ;
        |  |
        | CHPO2  |
        | CHAM1  |

    Objet :

    L'operateur SOURCE permet d'imposer une source volumique de
chaleur dans une ou plusieurs parties d'une structure.

    Commentaire :

    MODE1 : structure modelisee (type MODELE)

    VAL1 : valeur de la source volumique (type FLOTTANT)

    GEO1 : partie de la structure ou est imposee la
        source (type MAILLAGE)

    CHPO2 : champ a une seule composante pour les massifs
        et a 3 composantes QINF, QVOL et QSUP pour les coques
        contenant les valeurs des sources respectivement en
        peau interne, surface moyenne , peau externe.
        (type CHPOINT)

   CHAM1 : champ par element a une seule composante pour les
        massifs et a trois composantes QINF, QVOL et QSUP
        pour les coques contenant les valeurs des sources
        respectivement en peau interne, surface moyenne,
        peau externe.

    CAR1 : caracteristiques geometriques de la structure
        (type MCHAML, sous-type CARACTERISTIQUES).Cette
        donnee est utilisee uniquement dans le cas des
        elements coques, barre, tuy2 et tuy3
        (tuy. = advection thermique dans un tuyau).

    'ELEM' : (facultatif) si fourni, le champ resultat CHPO1 est
        alors un MCHAML aux NOEUDS.

    CHPO1 : flux nodaux equivalents (type CHPOINT) de composantes
        Q pour les massifs, QINF Q QSUP pour les coques.

      ATTENTION : Si vous utilisez un MODELE plus grand que la zone ou
la source est definie par le CHPOINT CHPO2 ou le maillage GEO2 , alors
les elements exterieurs touchantla frontieres, voient une source non
nulle,et seront eux aussi charges. Il est donc fortement conseille de
fournir une reduction du MODELE sur les elements strictement concernes.

## SPAL [Fluides Modele] (proc)
Procedure SPAL

  SYNTAXE (cf. operateur EQEX)

        'ZONE' $MD 'OPER' 'SPAL' 'RHO' 'UN' 'MU' 'DT'
        ('PERIODIC' GEOM1 GEOM2)
        'INCO' 'NU0'

   Objet :

   Calcule le champ de viscosite dynamique turbulente grace au modele
   de Spalart-Allmaras.

   Commentaires :

   1) LES PARAMÈTRES REQUIS sont:

      RHO*[MOT|FLOTTANT|CHPOINT] : Masse volumique  (kg/m3)
      UN *[MOT|CHPOINT]  : Vitesse d'advection  (m/s)
      MU *[MOT|FLOTTANT|CHPOINT] : Viscosite moleculaire dyn. (Pa.s)
      DT *[MOT|FLOTTANT]  : Duree du pas de temps  (s)
      NU0*[MOT] : Nom attribue a la viscosite modifiee

      Un objet de type MOT indique que l'on va chercher la valeur
      dans la table 'INCO'.

   /!\ ATTENTION: Ce modele necessite aussi la donnee de la distance
        a la paroi dans (RV.'PAROIS'.'DIST') !!

   2) Le champ de viscosite effective (moleculaire + turbulente) est
      renvoye dans la table 'INCO' a l'indice 'MUFN' par defaut, mais
      l'utilisateur peut definir ce nom lui-meme (cf. definition des
      parametres avances, remarque 4)

   /!\ ATTENTION: Les conditions aux limites de Dirichlet ainsi que
        les conditions initiales devront porter sur 'NU0'
        et non pas sur 'MUFN' !!

   3) LE PARAMÈTRE OPTIONNEL 'PERIODIC' permet d'imposer des
      conditions de periodicite sur 'MUFN' entre les maillages GEOM1
      et GEOM2.

   4) LES PARAMÈTRES AVANCÉS du modele peuvent etre personnalises en
      ajoutant une table nommee 'SPALART_ALLMARAS' dans RV:

   | TABLE PRINCIPALE 'SPALART_ALLMARAS'  |
   | Indice  | Valeur  | Description  |
   | 'KVERS'  | [MOT-cle] | Variante du modele a utiliser:  |
   |  | 'ORIG'  | - Modele original de base (par defaut) |
   |  | 'TRIP'  | - Modele original avec ft1 et ft2  |  <= À FAI
   |  | 'SALSA'  | - Modele modifie par Rung et al.  |  <= À FAI
   |  |  |  |
   | 'NOMMUF'  | MOT  | Nom de l'inconnue de viscosite totale  |
   |  |  |  ('MUFN' par defaut)  |
   |  |  |  |
   | 'KCONST'  | TABLE  | Constantes du modele  |
   |  |  |  |
   | 'KTGRAD'  | [MOT-cle] | Mesure scalaire du tenseur gradient:  |
   |  | 'TOROT'  | - Taux de rotation (Par defaut)  |
   |  | 'TODEF'  | - Taux de deformation  |
   |  | 'COMPL'  | - Norme euclidienne du tenseur complet |
   |  | 'MIXTE'  | - Expression de Dacles-Mariani et al.  |
   |  |  |  |
   | 'KMUFN'  | [MOT-cle] | Instant auquel est renvoye 'MUFN'  |
   |  | 'APRES'  | - Fin du pas de temps (Par defaut)  |
   |  | 'AVANT'  | - Debut du pas de temps  |
   |  | 'DEMI'  | - Apres le demi pas de temps ('ALGO1') |
   |  |  |  |
   | 'KSRC'  | [MOT-cle] | Algo. utilise pour les termes sources  |
   |  | 'ALGO1'  | - Methode de Newton (Par defaut)  |
   |  | 'ALGO2'  | - Separation S+/S-  |
   |  |  |  |
   | 'NEWTON'  | TABLE  | Parametres de l'algorithme de Newton  |
   |  |  | si le parametre 'KSRC' vaut 'ALGO1'  |
   |  |  |  |
   | 'METHINV' | TABLE  | Options de la methode d'inversion.  |
   |  |  | Par defaut, ce sont celles definies  |
   |  |  | pour le probleme global dans RV  |
   |  |  |  |
   | 'KOPT2'  | TABLE  | Options de discretisation temporelle.  |
   |  |  | Par defaut, les parametres passes par  |
   |  |  | EQEX 'OPTI' sont appliques a la fois a |
   |  |  | l'operateur de convection/diffusion  |
   |  |  | TSCA et a la derivee temporelle DFDT  |
   |  |  | (sauf que DFDT est 'CENTREE')  |
   |  |  |  |
   | 'VERROU'  | TABLE  | Etat des verrous numeriques  |
   |  |  |  |
   | 'DUMP'  | LOGIQUE  | Sauver les variables internes au modele|
   |  |  | SA dans la table 'INCO' sous l'indice  |
   |  |  | 'SPAL'? (Par defaut: FAUX)  |

   | SOUS-TABLE 'KCONST'  |
   | Indice  | Valeur  | Description  | Defaut |
   | 'SIGMA'  | FLOTTANT  | Nombre de Prandtl turbulent  | 2/3  |
   | 'CB1'  | FLOTTANT  | Taux de production turbulente | 0.1355 |
   | 'CB2'  | FLOTTANT  | Diffusion non conservative  | 0.622  |
   | 'KAPPA'  | FLOTTANT  | Constante de Von Karman  | 0.41  |
   | 'CV1'  | FLOTTANT  | Épai. ss-couche visq. (Bas-Re)| 7.1  |
   | 'CW1'  | FLOTTANT  | Equilibre Prod/Dest zone log. | 3.2391 |
   | 'CW2'  | FLOTTANT  | Controle du coef. frottement  | 0.3  |
   | 'CW3'  | FLOTTANT  | Borne sup. de fw (environ)  | 2.  |

   | SOUS-TABLE 'NEWTON'  |
   | Indice  | Valeur  | Description  | Defaut |
   | 'CRIT'  | FLOTTANT  | Critere d'arret en norme inf. | 1.E-10 |
   | 'IMAX'  | ENTIER  | Nombre max. d'iterations  | 10  |
   | 'OMEGA'  | FLOTTANT  | Facteur de relaxation  | 1.  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## SPO [Mecanique Dynamique]
    Operateur SPO

    EVOL2 = SPO EVOL1 'AMOR' LREEL1 ('FREQ' LREEL2) ('TEMP' LREEL3) ...

        ... ('COUL' COUL1) MOT1 ;

    Objet :

    Cet operateur permet de calculer un ou plusieurs spectres
d'oscillateurs selon qu'on donne un ou plusieurs amortissements.

    Commentaire :

    EVOL1 : objet contenant le signal d'excitation (type EVOLUTION)

   'AMOR' : mot-cle suivi de :
    LREEL1 : valeur(s) d'amortissement correspondant a (aux)
        oscillateur(s) (type LISTREEL)

   'FREQ' : mot-cle suivi de :
    LREEL2 : objet contenant la liste de frequences oº l'on desire
        que les deplacements maximaux soit calcules.

        Par defaut, on prend la liste definie comme suit :

        Soit T la duree du signal.
        DT le pas de temps moyen du signal.
        XSI une valeur de la liste des amortissements.

        On prend une liste de frequences comprises entre 1/T et
        1/2*DT :

        De 1/T a 1/XSI*T les frequences sont prises avec un pas
        constant qui vaut 1/T.

        De 1/T a 1/2*DT, le pas DF varie de façon que l'on ait
        DF/F=XSI.
        DF=F(i+1)-F(i) (difference entre 2 frequences successives
        F(i) etant la valeur de la ieme frequence).

   'TEMP' : mot-cle suivi de :
    LREEL3 : objet contenant la liste des temps oº l'on desire
        que les deplacements soient calcules (reponse de
        l'oscillateur) (type LISTREEL)
        Par defaut, on utilise la liste des temps de l'objet
        EVOLUTION, contenant l'excitation completee sur une
        demi periode par des zeros.

   'COUL' : mot-cle suivi de :
    COUL1 : couleur desiree des courbes (type MOT)

    MOT1 : MOT permettant de specifier le type de sortie :
        'DEPL' : spectre en deplacement
        'VITE' : spectre en pseudo-vitesse
        'ACCE' : spectre en pseudo-acceleration
        'ACCA' : spectre en acceleration absolue

    EVOL2 : objet resultat (type EVOLUTION).

## SPON [Mecanique Dynamique]
 Operateur SPON

 EVOL3 = SPON ('DEMA') 'SIGN' EVOL1 'SPEL' EVOL2 MOT1

        'AMOR' LREEL1 'MOT2' LREEL2 ('COUL' COUL1) MOT3;

 Objet :

 Cet operateur permet de calculer un ou plusieurs spectres
 d'oscillateurs non lineaires EVOL3 selon qu'on donne un ou
 plusieurs amortissements et spectres lineaires.

 Commentaire :

'DEMA' : mot-cle. En presence du mot cle 'DEMA' le spectre
        calcule est le spectre de reponse non-lineaire
        ayant comme ductilite appellee la valeur de la
        ductilite donnee (a 5% pres). Dans ce cas l'
        evolution resultat a en ordonnees le deplacement
        relatif, pseudo-vitesse ou pseudo-acceleration
        correpondant a la limite elastique.
        En l'absence du mot cle 'DEMA' le spectre calcule
        est le spectre de reponse non-lineaire ayant
        comme deplacement limite elastique le quotient
        entre le deplacement maximum lineaire (donne par
        EVOL2) est la ductilite donnee (1ere valeur de
        LREEL2). Dans ce cas l'evolution resultat a en
        ordonnees le deplacement relatif, pseudo-vitesse
        ou pseudo-acceleration definis de la façon usuelle.

'SIGN' : mot-cle suivi de :
 EVOL1 : objet contenant le signal d'excitation avec pas
        de temps constant ( DT = CONSTANT !! )

'SPEL' : mot-cle suivi de :
 EVOL2 : objet contenant le spectre lineaire avec ordonnees en
        frequence. Elle peut etre calculee par l'operateur SPO.
        Ceci n'est pas obligatoire car cette evolution ne sert
        que pour definir la limite elastique en absence du mot
        cle 'DEMA' ou la valeur de la limite elastique de la
        premiere iteration dans le cas ou le mot cle 'DEMA'
        est donne.

 MOT1 : MOT permettant de specifier le type du spectre lineaire
        (EVOL2) :
        'DEPL' : spectre en deplacement
        'VITE' : spectre en pseudo-vitesse
        'ACCE' : spectre en pseudo-acceleration

'AMOR' : mot-cle suivi de :
 LREEL1 : valeur(s) d'amortissement correspondant a (aux)
        oscillateur(s) et a (aux) spectre(s) donne(s) en EVOL2

'MOT2' : MOT specifiant le comportement non-lineaire
        (de type bilineaire)
        'TAKE' : Takeda bilineaire
        'CINE' : elastoplastique avec ecrouissage cinematique
        'ISOT' : elastoplastique avec ecrouissage isotrope
        'ELAS' : elastique non-lineaire

 LREEL2 : objet contenant les proprietes du modele non lineaire

        Pour le modele Takeda :
        5 flottants. En ordre :

        Force |
        |  ___2_____
        |  /  * /
        | 1/*  /
        7*  | /  /3
        _______*_______ /________/_________
        / / * Depl.
        6/  /|  *
        /  / |* 4
        -----5----/* |
        |
        |
        Figure: Forme General des Relations Force/Deplacement
        du Modele

        - Ductilite : quotient entre le deplacement
        maximum et le deplacement limite elastique

        - Teta : quotient entre la raideur tangente de
        la courbe monotone apres la limite
        elastique (Rig2) et la raideur lineaire
        ( Rig1 = W**2 ). La raideur apres le limite elastique
        est calculee par : Rig2 = W ** 2 * Teta

        - sfdp :parametre de degradation de rigidite cyclique.
        Une decharge est orientee vers un effort egal a
        -sfdp*effort limite elastique (voir notice de MATE).

        - Beta :parametre de pincement
        La valeur de l'effort pinp (voir notice de MATE) est
        pinp = beta*effort limite elastique.

        - srdp : parametre d'adoucissement cyclique
        Il represente l'augmentation de la deformation maximale
        atteinte par unite d'energie absorbee.
        (voir notice de MATE)

        Pour les autres modeles :
        Il suffit de donner les deux premiers parametres du
        modele precedent.

'COUL' : mot-cle suivi de :
 COUL1 : couleur desiree des courbes

 MOT3 : MOT permettant de specifier le type de sortie :
        'DEPL' : spectre en deplacement
        'VITE' : spectre en pseudo-vitesse
        'ACCE' : spectre en pseudo-acceleration
        'EPSE' : spectre en deformation non-lineaire
        cumulee

 EVOL3 : resultat de type EVOLUTION. Chaque courbe de cet
        objet contient autant de points que EVOL2

## SPPLANC [Mecanique Dynamique] (proc)
 Procedure SPPLANC

 TAB2 = SPPLANC TAB1

 Objet :
 Cette procedure permet le calcul des spectres de plancher par une
  approche analytique.

Commentaire
TAB1 : objet de type table contenant

    Indice Type Commentaires
    ------ ---- ------------
    STRUC TABLE Caracteristiques modales
        de la structure support

        Indice Type

        NMODE ENTIER Nombre de modes
        FREQU TABLE Les frequences modales
        AMORT TABLE Les amortissements modaux

    PLANCH TABLE Caracteristiques du
        Plancher etudie (P)

        Indice Type

        LISFREQ LISTREEL Axe frequentiel du
        spectre de plancher
        PAR DEFAUT :
        discretisation par la
        procedure "DISCRFR"

        COEFFPL TABLE Les coefficients de
        participation modale
        en P : ( Qn * PHIn ) / Mn

        AMORTPL FLOTTANT Amortissement du spectre
        de plancher a calculer

        TYPSPPL MOT Type du spectre de
        plancher
        'DEPL' : deplacement
        'VITE' : pseudo-vitesse
        'ACCE' : pseudo-accel.

    EXCIT TABLE Donnees de l'excitation
        ( processus separable )

        Indice Type

        ENVE MOT Type de l'enveloppe
        'PLATLIN' :
        montee-plat-descente
        ( par defaut : plateau )

        DUREE FLOTTANT Duree du signal

        TDEB FLOTTANT Temps ou commence
        le plateau ( montee )

        TFIN FLOTTANT Temps ou se termine
        le plateau ( debut desc.)

        DSP EVOLUTION D.S.P. de la fonction
        aleatoire stationnaire

TAB2 : objet de type table contenant

    Indice Type Commentaires
    ------ ---- ------------
    SIGM EVOLUTION Spectre ecart-type

    FPIC EVOLUTION Spectre de facteur de pic

    SPPL EVOLUTION Spectre de plancher
        (SPPL = SIGM*FPIC)

## SQTP [Multi-physique Multi-physique]
    Operateur SQTP

    CHP2 = SQTP MODE1 RIG1 RIG2 CHP1 ;

    Objet :

    L'operateur SQTP cree la contribution au systeme matriciel
en trace de charge de force vomuliques dans le cadre de la resolution
de la loi de DARCY par une methode d'elements finis mixtes hybrides
(modele DARCY). Cet operateur est notamment utile pour prendre en compte
les forces de gravite lorsque l'on pose le probleme de DARCY en terme
de pression et non plus de charge.

   !! Cette fonctionnalite n'est pas compatible actuellement avec la
   resolution d'un probleme de DARCY en transitoire !!

    Commentaire :

     MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

     RIG1 : Objet rigidite de sous type MASSE contenant les
        matrices masses elementaires pour les elements
        hybrides (cf. MHYB).

     RIG2 : Objet rigidite de sous type HYBTP (cf. MATP)

     CHP1 : Objet de type CHPOINT de composantes FX FY (FZ) contenant
        le vecteur de la force volumique moyenne par element.
        Le support geometrique de ce champ est le MAILLAGE CENTRE

     CHP2 : Objet resultat de type CHPOINT contenant la contribution
        au second membre des forces volumiques. Le support
        geometrique de ce champ est le MAILLAGE de points FACE.
        Le nom de la composante du CHPOINT est FLUX.

## SSCH [Multi-physique Multi-physique]
Operateur SSCH
-------------- CHI2

   CHPO1 = SSCH TAB1 CHPO2 CHPO3 CHPO4 ;

  Objet
  Calcul du terme de production chimique lors d'un calcul couple
  avec une equation de transport par espece.

  Commentaires
  TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

  CHPO2 nom d'un objet de type CHPOIN ayant une composante pour
        chaque composante du systeme chimique
        contient la variation de la partie fixee des composantes
        chimiques au cours du pas de temps.

  CHPO3 nom d'un objet de type CHPOIN ayant une composante pour
        chaque espece en solution, et contenant la concentration
        de chaque espece en solution.

  CHPO4 nom d'un objet de type CHPOIN ayant une composante pour
        chaque espece en solution, et contenant la variation
        des especes en solution au cours du pas de temps

  CHPO1 nom d'un objet de type CHPOIN ayant une composante pour
        chaque espece en solution, et contenant le terme de
        production chimique.

## SSTE [Mecanique Resolution]
Operateur SSTE

 SIGF VARF DEPIN RI1 = 'SSTE' MODL SIG0 VAR0 DEPST CARAC
        (PRECIS) (NMAXSSTEPS) (NITMAX) ;

Description :

Integration avec sous-decoupage de l'equation constitutive
elastoplastique au niveau du point d'integration.

Modeles : J2, RH_COULOMB, MRS_LADE.

Il rend les contraintes (SIGF), les variables internes (VARF) et
la deformation plastique (DEPIN).

Il rend aussi le module tangent consistant (RI1).

Il est appele par UNPAS.

Voir la notice de PASAPAS pour utiliser cette possibilite.

## STRU [Mecanique Modele]
    Operateur STRU

    STRU1 = STRU RIG1 MASS1 (N1) ;

    Objet :

    L'operateur STRU permet de creer un objet STRUCTURE, par les
donnees des objets RIGIDITE et MASSE s'y rapportant.

    Commentaire :

    RIG1 : matrice de rigidite (type RIGIDITE)

    MASS1 : matrice de masse de la structure (type RIGIDITE)

    N1 : nombre de sous-structures identiques a creer (type ENTIER)

    STRU1 : structure (type STRUCTURE)

    Remarque :

    Si N1 n'est pas specifie, STRU1 est une sous-structure dite element-
taire (elle ne contient qu'une seule structure).

    Si N1 est specifie, N1 sous-structures identiques sont creees. Chaque
sous-structure est reperable par son numero. Par exemple STRU1 4 est la
4ieme sous-structure de STRU1.

## SUIT [Mathematiques Autres]
Operateur SUITE

LCHPO1 = SUITE (CHPO1 (CHPO2 ...)) ;

Objet :

L'operateur SUITE permet de creer une liste de champs par points.

Commentaire :

CHPOi : champs par points (type CHPOINT)

LCHPO1 : objet resultat (type LISTCHPO) contenant les champs par
        points CHPOi

## SUPE [Mecanique Modele]
    Operateur SUPER

    RESU1 = SUPER  | 'RIGIDITE'  ('NOMU') RIG1  |  GEO1  |
        |  |  RIG2  |
        |  |  CHPO1 |
        |
        | 'CHARGE'  SUPER1  FORC1
        | 'DEPLA'  SUPER1  DEP1  (FORC1) ('NOER')

    (LCHP1) RESU1 = SUPER 'MASSE' SUPER1 MAS1 ('LCHP')

    Objet :

    L'operateur SUPER est le point de passage oblige pour toutes les
operations concernant un super-element.

    Commentaire :

    Suivant le mot-cle, plusieurs options sont possibles :

    | 1ere Option |

     'RIGIDITE' : mot-cle indiquant qu'on definit et qu'on calcule la
        matrice equivalente d'un super-element. Pour permettre
        de charger les relations, les multiplicateurs de
        Lagrange associes sont ajoutes aux points maitres.

     NOMU : mot cle optionnel indiquant qu'on ne veut pas
        transferer les multiplicateurs de Lagrange dans les
        noeuds maitres

     RIG1 : matrice de rigidite que l'on veut reduire
        (type RIGIDITE)

     GEO1  |  : servent a definir l'ensemble des points maitres et les
     RIG2  |  inconnues associees definissant le super-element.
     CHPO1  |  (type MAILLAGE, RIGIDITE ou CHPOINT)

        Avec GEO1 (type MAILLAGE), on prend pour chaque noeud
        les inconnues existant dans RIG1.

     RESU1 : objet resultat (type SUPERELE)

    | 2eme Option |

     'CHARGE' : mot-cle indiquant qu'on reduit le chargement sur les
        points maitres du super-element.

     SUPER1 : super-element sur lequel on reduit les charges
        (type SUPERELE)

     FORC1 : charges a reduire (type CHPOINT)

     RESU1 : objet resultat (type CHPOINT)

    | 3eme Option |

     'DEPLA' : mot-cle indiquant qu'on veut calculer le champ de
        deplacements a l'interieur du super-element.

     SUPER1 : super-element dans lequel on calcule le champ de
        deplacements (type SUPERELE)

     DEP1 : champ de deplacements des noeuds maitres (type CHPOINT

     FORC1 : charges s'appliquant sur la structure ( CHPOINT)

     RESU1 : objet resultat (type CHPOINT) representant les depla-
        cements .

     'NOER' : Les Nan sont transformes en zero dans la solution.

    | 4eme Option |

    'MASSE' : mot-cle indiquant qu'on calcule la matrice de masse
        equivalente.

    SUPER1 : super-element qui permet de reduire la masse
        (type SUPERELE)

    MASS1 : matrice de masse qu'on veut reduire (type RIGIDITE)

    RESU1 : matrice de masse reduite (type RIGIDITE)

    'LCHP' : en presence du mot clef 'LCHP' (type MOT), LCHP1
    LCHP1 (type LISTCHPO) contient les ligne de la matrice
        de transformation

    Exemple :

    STRU1 est compose de RIG1 et RIG2 dont les supports geometriques
GEO1 et GEO2 ont une ligne LIG1 commune.
    Soit FORC1 et FORC2 les charges sur les deux parties.
On peut enchainer le calcul suivant :

        * calcul de la rigidite equivalente de RIG2
        SUPER1 = SUPER 'RIGIDITE' RIG2 LIG1 ;
        * recuperation de la rigidite et assemblage avec le reste de
        * la structure
        RIG3 = EXTRAI SUPER1 'RIGI';
        RIG4 = RIG1 ET RIG3;
        * reduction des charges
        FORC3 = SUPER 'CHARGE' SUPER1 FORC2;
        * resolution de la structure totale
        DET1 = RESOU RIG4 ( FORC1 ET FORC3);
        * calcul des deplacements dans le super-element
        DEP1 = SUPER 'DEPLA' SUPER1 DET1 FORC2;
        * calcul de la masse equivalente a MASS2
        MASS3 = SUPER 'MASSE' SUPER1 MASS2;
        * calcul d'un mode propre
        MOD1 = VIBR 'PROCHE' (PROG 0.) RIG4 (MASS1 ET MASS3);

## SURF [Maillage Surfaces]
    Operateur SURFACE
    ----------------- ROTA GENE

    SURF1 = SURFACE (CHPO1) | LIG1  | 'PLANE' (CRIT) ;
        |  | 'SPHERIQUE'  CENTR1 ;
        |  | 'CYLINDRIQUE' AXEI1  AXEJ1 ;
        |  | 'CONIQUE'  SOMM1  AXEJ1 ;
        |  | 'TORIQUE'  CENTR1 AXEJ1 CENTR2 ;
        |
        |
        | 'POLYNOME' N1 N2 P1  P2  (P3  (P4  ... ) )
        |  P11  P12 (P13 (P14 ... ) )
        |  (P21 (P22 (P23 (P24 ... ) )
        |  (  ...  )
        |  ('PARAMETRE' U1 U2  V1 V2) ('REGULIER') ;

    Objet :

    L'operateur SURFACE construit le maillage de l'interieur du contour defini
par l'objet LIG1 (qui doit etre un ensemble de lignes fermees). Par ailleurs
l'option POLYNOME permet de construire une surface parametree.

    Commentaire :

    Il est possible de donner un CHPOINT (CHPO1) de taille de maille
(une composante par noeud) a respecter.

    LIG1 peut etre constitue de contours exterieurs et interieurs
(delimitant des trous) qui doivent tourner dans des sens opposes.

    Le maillage peut etre realise a l'aide d'elements triangulaires ou
quadrangulaires et triangulaires selon ce qui a ete demande dans la
directive OPTION.

    La surface peut etre PLANE, SPHERIQUE, CYLINDRIQUE, CONIQUE ou
TORIQUE (suivant le mot-cle).

    'PLAN' : en option :
    'CRIT' : critere de planeite. cosinus de l'angle entre
        les points de la ligne et la normale au plan

    'SPHERIQUE' : mot-cle suivi de :
    CENTR1 : centre de la sphere (type POINT)

    'CYLINDRIQUE' : mot-cle suivi de :
    AXEI1, AXEJ1 : deux points de l'axe du cylindre (type POINT)

    'CONIQUE' : mot-cle suivi de :
    SOMM1, AXEI1 : sommet du cone et un point de l'axe (type POINT)

    'TORIQUE' : mot-cle suivi de :
    CENTR1 : centre du tore (type POINT)
    AXEI1 : un point de l'axe de symetrie (type POINT)
    CENTR1 : centre d'un petit cercle (type POINT)

    Remarque :

    Dans le cas d'une surface conique, le contour ne doit pas passer par
le sommet du cone.

   |  Option POLYNOME  |

    Le resultat est le MAILLAGE de la surface parametree d'equation :

        |  P1  P2  P3  P4 .. |  |  1  |
        2  (N2-1)  | P11 P12 P13 P14 .. |  |  U  |
P(U,V) = (1 V V  ...V  ) x | P21 P22 P23 P24 .. | x |  ..  |
        |  ...  |  |U**(N1-1)|

    N1 , N2, : respectivement le nombre de colonnes et
        de lignes de la matrice de points (type ENTIER).

    P1, P11, ... , : objets de type POINT. Les abscisses de
        ces points donnent la representation parametrique
        des abscisses des points de la surface, etc...

    U1, U2 : bornes de variation du parametre U (type
        FLOTTANT) (egales a (0,1) par defaut).

    V1, V2 : bornes de variation du parametre V (type
        FLOTTANT) (egales a (0,1) par defaut).

   'REGULIER' : mot-cle (type MOT) indiquant que les points
        de la surface doivent etre regulierement
        repartis dans l'espace geometrique (eu egard
        aux densites existantes) plutot que dans
        l'espace parametrique.

## SYME [Mathematiques Autres]
    Operateur SYMETRIE
    ------------------ HOMO

    Cet operateur a plusieurs fonctions selon les donnees.

   | 1re fonction |

    L'operateur SYME construit l'objet resultant de la symetrie de
l'objet GEO2 par rapport a un point, une droite ou un plan.

    GEO1 = GEO2  SYME | 'POINT' POIN1 ;
        | 'DROIT' POIN1 POIN2 ;
        | 'PLAN'  POIN1 POIN2 POIN3 ;

    Commentaire :

    GEO2 : objet a symetriser (type POINT ou MAILLAGE)

   'POINT' : mot-cle indiquant une symetrie par rapport a un point,
        suivi de :
    POIN1 : point de symetrie (type POINT)

   'DROIT' : mot-cle indiquant une symetrie par rapport a une droite,
        suivi de :
    POIN1 |  : deux points definissant une droite (type POINT)
    POIN2 |

   'PLAN' : mot-cle indiquant une symetrie par rapport a un plan,
        suivi de :
    POIN1 |  : trois points definissant un plan (type POINT)
    POIN2 |
    POIN3 |

    GEO1 : objet symetrise (type POINT ou MAILLAGE)

    Remarques :

    OBJET1 OBJET2 ... OBJETn  SYME | 'POINT' POIN1 ;
        | 'DROIT' POIN1 POIN2 ;
        | 'PLAN'  POIN1 POIN2 POIN3 ;

    L'operation est effectuee sur les n objets simultanement et a n
resultats :

        NC1 NC2 NC3 NC4 = C1 C2 C3 C4 SYME 'POINT' (10. 0.) ;

    Cette regle n'est pas applicable aux objets de type POINT dont
la symetrie doit etre ecrite separement pour chaque point.

    Seul le mot-cle 'POINT' est utilisable en DIMEnsion 1.

   | 2e fonction |

    L'operateur SYME construit l'objet resultant de la symetrie de
l'objet champ par points scalaire CHP2 par rapport a un point, une
droite ou un plan. L'operation est effectuee simultanement sur
l'objet maillage support du champ GEO2.

    GEO1 CHP1 = GEO2 CHP2 SYME | 'POINT' POIN1 ;
        | 'DROIT' POIN1 POIN2 ;
        | 'PLAN'  POIN1 POIN2 POIN3 ;

    Commentaire :

    GEO2 : objet maillage support du champ a symetriser
        (type MAILLAGE)
    CHP2 : objet champ par points a symetriser (type CHPOINT)

   'POINT' : mot-cle indiquant une symetrie par rapport a un point,
        suivi de :
    POIN1 : point de symetrie (type POINT)

   'DROIT' : mot-cle indiquant une symetrie par rapport a une droite,
        suivi de :
    POIN1 |  : deux points definissant une droite (type POINT)
    POIN2 |

   'PLAN' : mot-cle indiquant une symetrie par rapport a un plan,
        suivi de :
    POIN1 |  : trois points definissant un plan (type POINT)
    POIN2 |
    POIN3 |

    GEO1 : objet maillage support symetrise (type MAILLAGE)

    CHP1 : objet champ par points symetrise (type CHPOINT)

    Seul le mot-cle 'POINT' est utilisable en DIMEnsion 1.

## SYMT [Multi-physique Multi-physique]
    Operateur SYMT :
    -------------- RESO RELA

    RIG1 = SYMT ('DEPL') ('ROTA') POIN1 POIN2 (POIN3 si 3D) GEO1 (FLOT1)

    Objet :

    L'operateur SYMT permet d'imposer des conditions aux limites de type
SYMETRIE sur les degres de liberte en deplacement et/ou en rotation.

    Commentaire :

   'DEPL' : conditions aux limites de type SYMETRIE sur les d.d.l.
        en DEPLACEMENT.

   'ROTA' : conditions aux limites de type SYMETRIE sur les d.d.l.
        en ROTATION.

   IMPORTANT : l'UNE au moins de ces deux specifications est OBLIGATOIRE

    POIN1 |  : points definissant l'axe de symetrie en 2D (type POINT).
    POIN2 |

    POIN1 |  : points definissant le plan de symetrie en 3D (type POINT)
    POIN2 |
    POIN3 |

    GEO1 : objet sur lequel on impose les conditions aux limites
        (type MAILLAGE).

    FLOT1 : critere de selection des points appartenant a
        l'axe ou au plan de symetrie (type FLOTTANT).
        Par defaut on utilise le 1/10 de la densite courante.
        FLOT1 est donc NECESSAIRE lorsqu'aucune densite n'a
        ete definie precedemment.

    RIG1 : conditions aux limites symetriques (type RIGIDITE)

    ATTENTION Le choix du critere conditionne l'ensemble des points
    _________ sur lesquels porteront les conditions de symetrie.
        Il est donc conseille d'une part de le choisir avec
        soin et d'autre part de visualiser les blocages ainsi
        obtenus au moyen de l'operateur TRAC.

    Remarques :

    NE PAS CONFONDRE cet operateur avec l'operateur de maillage SYME ||

    Cet operateur n'est pas disponible en dimension 1.
    L'utilisation de l'operateur BLOQUE est suffisante.

## SYNT [Mecanique Dynamique]
    Operateur SYNTHESE

    SOL2 = SYNTHESE SOL1 BAS1 ;

    Objet :

    L'operateur SYNTHESE est utilise en sous-structuration.
Il cree un objet SOLUTION contenant les modes de la structure, a partir
des modes des sous-structures et des champs de contributions modales
sur ces modes.

    Commentaire :

      BAS1 : base modale contenant les modes des sous-structures,
        les objets ATTACHE decrivant les liaisons entre les sous-
        structures et les solutions statiques correspondantes
        (type BASEMODA)

      SOL1 : objet contenant les modes de la structure exprimes sur la
        base modale BAS1 (obtenu en utilisant l'operateur VIBR)
        (type SOLUTION)

      SOL2 : objet contenant les modes de la structure exprimes sur la
        base elements finis (type SOLUTION, sous-type MODE)

## TABL [Langage Objets]
    Operateur TABLE

    TAB1 = TABLE  | ( MOT1 ) | ;
        | ( TAB2 ) |

    Objet :

    L'operateur TABLE sert a initialiser une structure de table.

    Commentaire :

    L'operateur TABLE suivi par :

    MOT1 : indique le sous-type de la table (type MOT)
        ce mot est range dans la table avec pour indice le mot
        'SOUSTYPE'

    TAB2 : permet de renommer la table TAB2 (type TABLE)

    Remarque importante :

    Pour l'utilisation, le nom de la table doit etre separe de l'indice
considere par un . ; si l'indice est un nombre flottant contenant un .,
il faut en plus mettre des blancs entre le nom de la table et l'indice.
D'un maniere generale, l'usage des blancs entre la table et les indices
est fortement recommande.

Par exemple : MATAB1 . 3.68

 Pour les indices de type MOT on ne tient pas compte des blancs situes
 a la fin des mots. C'est a dire que TAB1.'AA' et TAB1.'AA '
 representent le meme indice

    Exemple d'emploi d'une table :

*
* on cree une table de sous-type VECTEUR
*
    MATAB = TABLE 'VECTEUR' ;
*
* on definit l'element d'indice 1 comme etant egal a 5
*
    MATAB . 1 = 5 ;
*
* on definit l'element d'indice 'ESS' comme etant egal a 2.732
*
   J = MOT 'ESS' ;
   MATAB . J = 2.732 ;
   LIST MATAB . J ;
*
   J = 1 ;
   B = MATAB . J ;
*
* B a pour valeur l'element de la table indice (qui vaut 1), soit 5
*
   T2 = TABLE MATAB;
*
* la table est accessible par le nouveau nom T2
*

## TABLO2D [Post-traitement Affichage] (proc)
Procedure TABLO2D
----------------- @HISTOGR

        TABLO2D | ('LINE') | NLIG NCOL LVAL (TIT) ;
        |  'LOGA'  |

Objet :

La procedure TABLO2D permet d'afficher sous forme graphique 2D
(matrice de cases colorees) un tableau de valeurs numeriques.

L'option 'LINE' (par defaut) fait une correspondance lineaire entre
les donnees et l'echelle de couleurs tandis que l'option 'LOGA'
permet de mieux visualiser des donnees s'etalant sur plusieurs
ordres de grandeur en en prenant la valeur absolue puis le
logarithme decimal.

Commentaire :

NLIG [ENTIER] : Nombre de lignes du tableau

NCOL [ENTIER] : Nombre de colonnes du tableau

LVAL [LISTREEL] : Liste des NLIG*NCOL valeurs du tableau, rangees
        ligne apres ligne

TIT [MOT] : Titre general du graphique

## TABLO3D [Post-traitement Affichage] (proc)
Procedure TABLO3D
----------------- @HISTOGR

  TABLO3D | ('LINE') | (ZERO) (MARQ) NLIG NCOL LVAL (TIT) ;
        |  'LOGA'  |
        |  'CLOG'  |
        |  'ZLOG'  |

Objet :

La procedure TABLO3D permet d'afficher sous forme graphique 3D
(matrice de barres colorees) un tableau de valeurs numeriques.

L'option 'LINE' (par defaut) fait une correspondance lineaire entre
les donnees et l'echelle de hauteurs et de couleurs. Pour mieux
visualiser des donnees s'etalant sur plusieurs ordres de grandeur,
il est possible d'utiliser les options 'CLOG', 'ZLOG' ou 'LOGA' qui
en considerent le logarithme decimal respectivement pour la couleur,
la hauteur ou les deux.

Contrairement a la procedure TABLO2D, il est ainsi possible de
distinguer les valeurs positives et negatives tout en utilisant
une echelle logarithmique.

Commentaire :

ZERO [FLOTTANT] : Valeur en-deca de laquelle un nombre de LVAL
        est considere nul ; en termes images, il s'agit
        de l'altitude du "plancher" du graphe de barres.
        Par defaut, on prend le plus petit reel de LVAL.

MARQ [LOGIQUE] : Indique que l'on souhaite identifier la barre
        en (1,1) par un petit marqueur triangulaire
        (comportement par defaut)

NLIG [ENTIER] : Nombre de lignes du tableau

NCOL [ENTIER] : Nombre de colonnes du tableau

LVAL [LISTREEL] : Liste des NLIG*NCOL valeurs du tableau, rangees
        ligne apres ligne

TIT [MOT] : Titre general du graphique

## TAGR [Mathematiques Autres]
Operateur TAGR

GRAD1 = TAGR GRAD2 ;

Objet :

L'operateur TAGR calcule la transposee d'une matrice de gradients.

Commentaire :

GRAD1 | : matrice de gradients (type CHAMELEM, sous-type GRADIENT).
GRAD2 |

## TAIL [Mathematiques Autres]
    Operateur TAIL
    -------------- MATE CFL

       CHAM2  =  'TAIL' | 'DIRECTION'  MODL1 ('UNIF')
        |
        | 'DIAMETRE_MIN' MODL1 (CARA1)  ;

    Objet :

    L'operateur TAIL permet de caracteriser la geometrie des elements
d'un modele.

    Suivi du mot cle 'DIRECTION' il calcule les composantes dans le repere
global de deux tenseurs. Ces tenseurs permettent de calculer un parametre
de taille en chaque point de calcul de la rigidite d'un element. Les
composantes sont sous la forme d'un CHAML. Avec l'option 'UNIF',
toutes les composantes du CHAML sont nulles.

     Suivi du mot cle 'DIAMETRE_MIN' il calcule le parametre de taille
qui sert a formuler la condition C.F.L. . Ce parametre est la plus
petite longueur separant deux noeuds ou un noeud et un cote non adjacent
dans l'element. Autrement dit il minimise la longueur de propagation
de l'information d'un noeud vers les cotes non adjacents via les
fonctions d'interpolation d'un element. Dans le cas d'elements de
coques ou de poutres un second parametre est calcule qui correspond
a une longueur caracterisant la propagation des ondes de flexion.

      Commentaire :

      MODL1 : objet modele ( type MMODEL ).

      CARA1 : objet de type MCHAML de sous-type CARACTERISTIQUES,
        caracterisant les eventuels elements de poutres ou
        de plaque ( voir l'operateur 'CARA' )

      CHAM2 : objet resultat, champ de CARACTERISTIQUES
        geometriques (type MCHAML, sous-type CARACTERISTIQUES).

    Remarque :

   -- Option 'DIRECTION' :

    Elle ne s'applique qu'aux elements massifs.
    Les composantes de ce champ de CARACTERISTIQUES sont des
proprietes geometriques obligatoires pour l'utilisation du modele
OTTOSEN (voir aussi : MATE - Modele OTTOSEN).

    Un parametre de taille d'un element fini est une information
directionnelle. Notons VF un vecteur directeur et T,N les tenseurs
calcules par l'operateur TAIL. Une information sur la taille de
l'element au point de calcul considere nous est fournie par le
calcul :

        l = ('VF.T.VF)/('VF.N.VF)
        ou 'VF designe le vecteur transpose de VF

  -- Option 'DIAMETRE_MIN' :

Le champ par element cree est defini au centre de gravite de l'element.
Il y a une composante pour les elements massifs de nom 'L' et une
seconde composante de nom 'L2H' pour les elements de coques ou de
poutre.

## TAKM_EFZ [Mecanique Resolution] (proc)
    Procedure TAKM_EFZ

    EVOL1=TAKM_EFZ LREE1 LENT1 TABL1;

    Objet :

    Cette procedure permet de tester le modele de plasticite de
poutre 'TAKEMO_EFFZ', plasticite sur l'effort tranchant.

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
     SECZ  |  FLOTTANT  |  Surface reduite d'effort tranchant
     TRAC  |  EVOLUTION  |  Courbe trilineaire
        |  |  cisaillement/effort
SFDP,SFDN  |  FLOTTANT  |  Degradation de raideur
PINP,PINN  |  FLOTTANT  |  "Pinching"
SRDP,SRDN  |  FLOTTANT  |  adoucissement cyclique

## TAKM_MOY [Mecanique Resolution] (proc)
    Procedure TAKM_MOY

    EVOL1=TAKM_MOY LREE1 LENT1 TABL1;

    Objet :

    Cette procedure permet de tester le modele de plasticite de
poutre 'TAKEMO_MOMY', plasticite de flexion.

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
     INRY  |  FLOTTANT  |  Moment d'inertie
     TRAC  |  EVOLUTION  |  Courbe trilineaire moment/courbure
SFDP,SFDN  |  FLOTTANT  |  Degradation de raideur
PINP,PINN  |  FLOTTANT  |  "Pinching"
SRDP,SRDN  |  FLOTTANT  |  adoucissement cyclique

## TAN [Mathematiques Fonctions]
  RESU1 = 'TAN' OBJET1 (MOT1) ;

Operateur TAN
-------------- ACOS ASIN ATG

Objet :

L'operateur TAN calcule la tangente de l'objet OBJET1.
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

## TANH [Mathematiques Fonctions]
  RESU1 = 'TANH' OBJET1 (MOT1) ;

Operateur TANH
-------------- ACOS ASIN ATG

Objet :

L'operateur TANH calcule la tangente hyperbolique de l'objet OBJET1.

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

## TASS [Maillage Autres]
    Directive TASSER

    GEO2 = TASS (GEO1) ('NOOP') ;

    Objet :

    La directive TASS retasse le contenu de la memoire en eliminant les
points qui ne sont plus accessibles.

    ATTENTION :

    Le plus souvent, l'utilisation de TASSER est inutile, car une
renumerotation automatique est faite lors de la resolution (operateur
RESOU). Il convient d'utiliser la directive TASSER que si l'on comprend
bien ce qu'elle fait. Remarquons que TASS est appele automatiquement
par l'operateur MENAGE.

    Commentaire :

    GEO1 : geometrie (type MAILLAGE)

        Si l'objet GEO1 (type MAILLAGE) est specifie, la nouvelle
        numerotation est optimisee pour cet objet, du point de vue
        de la resolution du systeme lineaire associe, par la
        methode de CROUT.

        Cette numerotation (qui est continue et commence a 1 pour
        l'objet GEO1) est reproductible. Elle est identique a celle
        obtenue dans la directive SORTIR.

        Si GEO1 est un maillage de POI1, la nouvelle numerotation
        numerotera les noeuds a leur rang d'apparition dans GEO1.

    GEO2 : geometrie (type MAILLAGE de POI1)

        Ce maillage de POI1 contient l'ancienne numerotation, c'est
        a dire que le ieme element contient l'ancien noeud numero i
        (sauf disparition de noeuds).
        Il permet de reconstruire l'ancienne numerotation (si cela
        est possible) en le soumettant a l'operateur TASS.

    'NOOP' : mot-cle signifiant que l'optimisation de la numerotation
        n'est pas necessaire.

## TCNM [Fluides Resolution]
 Operateur TCNM

 Cet operateur est appele en interne par la procedure EXEQ

 OBJET :

Commentaires :

## TCRR [Fluides Resolution]
 Operateur TCRR

 Cet operateur est appele par la procedure EXEQ

 OBJET :

Commentaires :

## TEMP [Entree-Sortie Entree-Sortie]
   Directive TEMPS

 TEMPS |  -  | ;
       | 'PLAC'  |
       | 'IMPR' |  -  |  -  |
       |  | 'MAXI' | 'HORL'  |
       |  | 'SOMM' | 'CPU'  |
       |  'APPE'  |
       |  'EFFI'  |
       |  | 'PROC' |  -  |
       |  | 'BOUC' | 'HORL'  |
       |  | 'CPU'  |
       |  | 'APPE'  |
       | 'ZERO'  |
       | 'SGAC' 'IMPR'  |

   Operateur TEMPS

 TAB1 = TEMPS 'NOEC' ;
 ENTI1 ENTI2 = TEMPS 'SGAC' ;
 ENTI1  = TEMPS | 'CPU'  | ;
        | 'HORL' |

   Objet :

Syntaxe 1 : Utilisation comme une directive
 -'TEMP';
     - Affiche le temps horloge et CPU ecoule depuis le dernier appel

 -'TEMP' 'SGAC' 'IMPR' ;
     - Affiche le nombre d'appel par operateur, le cumul de segments
       restes actifs apres l'appel ainsi que la taille (en K-MOTS)
       correspondante.
       Remarque : Esope fait une pile de SEGMENTS a desactiver, un SEGMENT
        dans cette pile n'est pas compte comme desactive.

 -'TEMP' 'PLAC' ;
     - Affiche l'etat de la memoire dans ESOPE (en MOTS)

 -'TEMP' 'IMPR' (MOT1 (MOT2)) (MOT3) ;
     - MOT1 : 'PROC' : Informations sur les PROCEDURES
        'BOUC' : Informations sur les BOUCLES
        Sans MOT1: Informations sur les OPERATEURS (MOT2 possible)
        MOT2 :'MAXI' : Maximum de tous les ASSISTANTS
        'SOMM' : Somme sur tous les ASSISTANTS
        Sans MOT2: Toutes les valeurs des ASSISTANTS
        Attention, c'est le maximum du temps horloge qui est indique,
        meme avec SOMM.

     - MOT3 : 'HORL' : Temps horloge seulement (Avec trie croissant)
        'CPU ' : Temps CPU seulement (Avec trie croissant)
        'APPE' : Nombre d'appels seulement (Avec trie croissant)
        Sans MOT3: Toutes les informations.

 -'TEMP' 'ZERO' ;
     - Initialise les tableaux des temps ainsi que les informations
       liees aux SEGMENTS.

   Remarque : 1 MOT = 8 octets en 64-bits
   ---------- 4 octets en 32-bits

Syntaxe 2 : Utilisation comme un operateur
 - TAB1 ='TEMP' 'NOEC' ;
     - Renvoie dans la TABLE TAB1 le detail par operateur et
       par assistant des temps horloge et CPU ainsi que le
       nombre d'appels. On retrouvera egalement les temps
       horloge et CPU depuis le depart du calcul et depuis le
       dernier appel a l'operateur TEMP.

 - ENTI1 ENTI2 ='TEMP' 'SGAC' ;
     - Renvoie dans 2 entiers l'etat general des segments
        ENTI1 : Nombre total de SEGMENTS Actifs
        ENTI2 : Taille totale correspondante (en MOTS).

   Remarque : 1 MOT = 8 octets en 64-bits
   ---------- 4 octets en 32-bits

 - ENTI1 ='TEMP' | 'CPU'  | ;
        | 'HORL' |
     - Renvoie dans l'entier ENTI1 le temps CPU ou le temps HORLoge
       (en millisecondes) ecoule depuis le dernier appel a TEMP ZERO.

## TENSION [Mecanique Resolution] (proc)
 Procedure TENSION
 ----------------- PHASAGE

   TAB2 = TENSION TAB1;

 Objet :

 Cette procedure permet de creer une table contenant toutes les
 donnees, concernant les cables, necessaires a un calcul de
 precontrainte dans une structure en beton arme. Elle utilise
 l'operateur PREC pour determiner la distribution des efforts
 le long des cables en tenant compte des pertes de tension quasi
 instantanees. Les formules utilisees sont celles du BPEL91.

 TAB1 est indicee par des entiers 1,2,3,... et pointe vers des
 tables qui contiennent les donnees pour un groupe de cables.

 les indices de ces tables sont:

     'TPS' : flottant contenant la date de mise en tension
        de n sous-groupes de cables considere en jours.
        Cette date est a compter a partir de la premiere
        levee de beton.

     IET : indice entier du sous-groupe (1,..n) qui pointe
        vers une table

les indices, tous de type mot, de cette table sont :

     'GEOMETRIE1' : maillage contenant la description des extremites
        tendues

     'GEOMETRIE2' : maillage contenant la description des deuxiemes
        extremites tendues (uniquement si necessaire).

     'MODELE' : objet MODELE associe au groupe de cables.

     'MATERIAU' : materiau associe au groupe de cables.

     'FORCE' : flottant donnant la force exprimee en Newton.

     'TYPE_CAB' : mot '1EXT' ou '2EXT' indiquant si le groupe de
        cables est tendu par une ou par les deux
        extremites.

     'COEF_PREC' : table contenant les valeurs pour prise en compte
        des pertes quasi instantanees. Ces donnees sont
        celles de l'operateur PREC.

les indices, tous de type mot, de cette derniere table sont :

     'FF' : coefficient de frottement angulaire defaut 0.18 rd-1)
     'PHIF' : coefficient de frottement lineaire (defaut 0.002 m-1)

      Pour la perte de precontrainte par recul a l'ancrage :

     'GANC' : glissement a l'ancrage (defaut 0.0m)

      Pour la perte de precontrainte par relaxation de l'acier :

     'RMU0': coefficient de relaxation de l'armature ((defaut 0.43)
     'FPRG': contrainte de rupture garantie ((defaut 1700.e6 Pa)
     'RH10': relaxation a 1000 heures expimee en % (defaut 2.5 )

## TEXT [Langage Caracteres]
    Operateur TEXTE

    TEXT1 = TEXTE OBJET1 (OBJET2 ....... ) ;

    Objet :

    L'operateur TEXTE permet de donner un nom a un texte.
Ce texte est fabrique a partir des objets OBJET1, OBJET2, ...

    Commentaire :

    Les types possibles pour les objets sont MOT, ENTIER, FLOTTANT.

    A l'utilisation, un texte est remplace par son contenu, qui est
associe a une instruction elementaire. Par suite, si il comprend des
parentheses, elles ne sont par remplacees par leur contenu.

    Exemples :

    Si OEIL est un point de vue et MAIL un maillage,
l'instruction : " T = TEXTE ' TRAC OEIL MAIL '; " suivie de
l'instruction : " T ; " aura le meme effet que " TRAC OEIL MAIL ; "
c'est-a-dire effectuera un trace.

    La suite d'instructions : I = 2; J = 3; K = 6;
        TT = TEXTE I 'FOIS' J 'EGALE' K ;
        LIST TT;

provoquera l'impression de: 2 FOIS 3 EGALE 6

## TFR [Mathematiques Traitement]
 Operateur TFR

 | EVOL1  | = TFR N1 | EVOL2  | MOT1 ...
 | LCHPR LCHPI LISTF |  | LCHPO LISTT |

        ... ('FMIN' FLOT1) ('FMAX' FLOT2) (COUL1) (COUL2) ;

 Objet :

 L'operateur TFR construit la transformee de Fourier rapide (FFT)
 d'un signal.

 Commentaire :

 N1 : on utilise, pour la transformee de Fourier rapide,
        un nombre de points egal a 2**N1 (type ENTIER)
        (Si le signal traite est plus long, on le tronque;
        s'il est plus court, on le complete par des 0.)

 EVOL2 : objet contenant le signal a etudier (type EVOLUTION);
        les abscisses doivent etre a pas constant, les valeurs
        du signal etant les ordonnees. L'objet ne doit contenir
        qu'une seule courbe.
 ou
 LCHPO : objet contenant le signal a etudier (type LISTCHPO) sous
        la forme d'une liste de champs par points en fonction du
        temps. les chpoints contenus doivent tous avoir exactement
        la meme structure. LCHPO doit etre suivi de :
 LISTT : liste des temps du signal a etudier;
        le pas de temps est suppose constant.

 MOT1 : mot indiquant la syntaxe des valeurs complexes de la TFR

        'REIM' pour partie reelle et partie imaginaire / Frequence
        'MOPH' pour module et phase / Frequence

'FMIN' : mot-cle suivi de :
 FLOT1 : frequence minimale visualisee; elle sera superieure a 0.
        (type FLOTTANT, valeur par defaut = 0.)

'FMAX' : mot-cle suivi de :
 FLOT2 : frequence maximale visualisee; elle sera inferieure
        a 1/(2*DT), DT etant le pas de temps du signal d'entree.
        (type FLOTTANT, valeur par defaut = valeur maximale
        calculee)

 COUL1 : couleur choisie de la premiere courbe (type MOT)
        (blanc par defaut)

 COUL2 : couleur choisie de la deuxieme courbe (type MOT)
        (blanc par defaut)

 EVOL1 : objet contenant la TFR, sous forme de deux courbes.
        (type EVOLUTION)
 ou
 LCHPR : partie reelle de la TFR (type LISTCHPO) sous la forme
        d'une liste de champs par points en fonction de la
        frequence.
 LCHPI : partie imaginaire de la TFR (type LISTCHPO) sous la forme
        d'une liste de champs par points en fonction de la
        frequence.
 LISTF : liste des frequences (type LISTREEL).

## TFRI [Mathematiques Traitement]
    Operateur TFRI

    EVOL2 = TFRI EVOL1 ;

    Objet :

    L'operateur TFRI construit la transformee de Fourier inverse d'un
signal (inverse de la transformee de Fourier rapide).

    Commentaire :

    EVOL1 : objet complexe sur lequel on fera la transformee de
        Fourier inverse (type EVOLUTION).
        Les abscisses doivent etre a pas constant.
        L'objet EVOLUTION doit etre complexe :

        PREE,PIMA : partie reelle, partie imaginaire
        ou MODU,PHAS : module, phase

    EVOL2 : objet reel contenant la transformee de FOURIER
        inverse (type EVOLUTION).

## THERMIC [Thermique Resolution] (proc)
Procedure THERMIC

THERMIC (MOT1) TAB1 ;

        MOT1=NONLINEAIRE:
        TAB1.'SOUSTYPE' .'MAILLAGE' .'COQUE' .'EPAI'
        .'CONDUCTIVITE' .'BLOCAGE' .'CRITERE' .'EVOCOND'
        .'ITERMAX' .'IMPOSE' .'NITER' .'FLUX' .'NIVEAU'

Objet :

La procedure THERMIC permet de traiter le probleme suivant :

- regime permanent nonlineaire (materiaux isotropes seulement) ;

Commentaire :

TAB1 : objet (type TABLE, sous-type 'THERMIQUE') contenant :

        - les operandes en entree;
        - les champs thermiques resultats en sortie;

MOT1 : mots-cle (type MOT) caracterisant le type de
       calcul entrepris.

| 1 - Regime permanent non-lineaire |

MOT1 = NONLINEAIRE

TAB1 contient en entree les operandes suivants :

TAB1 'SOUSTYPE' 'THERMIQUE' (type MOT)
TAB1 'COQUE' type d'element coque(type MOT)
TAB1 'EPAI' epaisseur de la coque
TAB1 'PEAU' Peau sur laquelle s'effectue l'echange
TAB1 'BLOCAGE' matrice de blocage (type RIGIDITE)
TAB1 'IMPOSE' valeurs imposees (type CHPOINT)
TAB1 'FLUX' flux equivalents (type CHPOINT)
TAB1 'INSTANT(0)' Champ de temperature initial(type CHPOINT)
        ou sinon fournir les trois donnees
        suivantes
TAB1 'CONDUC(0)' Table des valeurs initiales de la conduc-
        tivite indicee par les modeles des sous zones
TAB1 'CONVEC(0)' Table des valeurs initiales de la convection
        indicee par les objets modeles
TAB1 'TEMPEX(0)' Table des temperatures initiales exterieures
        indicee par les objets modeles
TAB1 'CONDUCTIVITE' Matrice de conductivite ou sinon fournir les
        deux donnees suivantes
TAB1 'TABCOND' table des conductivites indicee par les objets
        modeles des differentes sous-zones,la conduc-
        tivite de chaque zone peut etre representee
        par un nombre (type FLOTTANT) ou par un objet
        d'evolution decrivant la variation de la
        dconductivite fonction de la temperature : K(T)
TAB1 'CONVECTION' table des tables pour une condition de convection
        indicee par les mots-cles suivants :

     'TABCONV1' table des coefficients d'echange indicee par
        les objets modeles des differentes surfaces de
        convection ,le coefficient d'echange de chaque
        surface peut etre represente par un nombre (type
        FLOTTANT) ou par un objet d'evolution decrivant
        la variation du coefficient d'echange fonction
        de la temperature : H(T)
     'TABTE1' table des temperatures exterieures indicee par
        les objets modeles des differentes surfaces de
        convection,la temperature exterieure de chaque
        surface peut etre representee par un nombre
        (type FLOTTANT) ,par un champ par point (type
        CHPOINT) ou par un objet d'evolution decrivant
        la variation de la temperature exterieure
        fonction de la temperature de la surface
        de convection : TE(T)
TAB1 'CRITERE' critere de convergence ( 10E-5 par defaut )
        (type FLOTTANT)
TAB1 'NITER' reactualisation de la conductivite toutes
        les NITER iterations ( NITER = 1 par defaut )
        (type ENTIER)
TAB1 'NIVEAU' niveaux de messages ( NIVEAU = 0 par defaut )
        (type ENTIER)
TAB1 'ITERMAX' nombre d'iterations maximum (type ENTIER)
        ( ITERMAX = 10 par defaut )

TAB1 contient en sortie:

TAB1 'TEMPERATURE' champ de temperature resultat (type CHPOINT)

## THET [Mecanique Resolution]
    Operateur THETA

      SIG1 = THET MODL1 MAT1 CH1 ;

    Objet :

    L'operateur THETA calcule les contraintes associees aux
    deformations d'origine thermique, a savoir :

        SIGMA = HOOK * EPSTHER
        EPSTHER = ALPHA * (T - TALP)

    ou HOOK est la matrice de Hooke et EPSTHER les deformations
    d'origine thermique.

      Commentaire :

      MODL1 : Objet modele (type MMODEL)

      MAT1 : Champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES )

      CH1 : champ de temperature (type MCHAML, sous-type TEMPERATURES
        ou type CHPOINT). Pour les elements joints, seuls sont
        autorises les champs de temperature de type MCHAML. Le
        type CHPOINT est interdit pour les joints.

      SIG1 : champ de contraintes (type MCHAML, sous-type CONTRAINTES)

    Remarque :

    SGIMA est le champ de contraintes entre les temperatures TALP et T.
Pour obtenir le champ de contraintes total entre TREF et T, il faut donc
retrancher le champ de contraintes entre TALP et TREF, obtenu en appelant
THET avec le champ de temperature TREF et le champ de caracteristiques
materielles a TREF.

    Remarque :

    Pour les elements coques ,le champ de temperature doit avoir
trois composantes de noms : TINF ,T, et TSUP, designant respectivement
la temperature en peau inferieure ,en surface moyenne et en peau
superieure.

    Pour les autres elements, le champ de temperature doit avoir une
composante de nom : T.

    Il est possible a partir des contraintes thermiques de retrouver
les deformations thermiques en utilisant l'operateur ELAS.

## TIRE [Mathematiques Autres]
    Operateur TIRE

    Cet operateur a deux fonctions selon les arguments :

    |  1ere fonction |

    OBJ1 = TIRE SOL1 MOT1 (VAL1) ;

    Objet :

    L'operateur TIRE permet de tirer d'un objet SOLUTION, un objet
dont la nature est precisee dans la syntaxe.

    Commentaire :

    On cherche a l'interieur de l'objet SOL1, un objet repere par :

       - un mot-cle : la liste des mots-cles pour chaque sous-type
        d'objet de type SOLUTION est definie dans SOLU.
       - un 'instant' : un temps, un cas de charge, un mode, ...

    SOL1 : objet de type SOLUTION

    MOT1 : mot-cle definissant le type de la variable : ('DEPL',
        'VITE', 'ACCE', 'LIAI', 'FREQ', 'MGEN', 'QX', 'QY',
        'QZ' , 'POIN' , ...)

        'POIN' est le mot-cle permettant d'obtenir le point-repere
        associe a un mode.

    VAL1 : definition de l'instant, a choisir parmi les couples :

        'TEMP' T : temps a prendre (type FLOTTANT)
        'CAS' ICAS : cas a prendre (type ENTIER)
        'RANG' IRG : rang de l'objet a prendre (type ENTIER)
        'NUME' INUME : numero du mode a prendre(@ programmer) (type
        ENTIER)
        Par defaut l'operateur choisit le dernier instant.

    OBJ1 : objet resultat (type MOT, FLOTTANT, ENTIER suivant la syntaxe
        adoptee)

    |  2eme fonction  |

    OBJ1 = TIRE  CHAR1 FLOT1 | ('TABL') ;
        |  (MOT1)  ;

    Objet :

    L'operateur TIRE permet de tirer d'un objet de type CHARGEMENT,
  un objet correspondant au chargement a un instant donne.

    Commentaire :

    CHAR1 : objet de type CHARGEMENT, sous-type FORCE

    FLOT1 : temps auquel on veut le chargement (type FLOTTANT)

    OBJ1 : objet resultat : type CHPOINT, MCHAML, TABLE, MMODEL,
        MAILLAGE, RIGIDITE ou POINT. Ce dernier cas correspond
        a un chargement de nom TRAJ (voir CHAR).

    MOT1 : Nom du chargement pour lequel on desire le champ
        instancie.

    'TABL': Mot-clef indiquant que l'on veut que les resultats
        soient ranges dans une table indicee par les noms
        des chargements elementaires et pointant vers les
        champs instancies correspondants (type CHPOINT ou
        MCHAML).

  Remarque : si ni MOT1 ni 'TABL' ne sont precises, le chargement
        sera la somme des chargements elementaires instancies.
        Dans ce cas, tous les chargements elementaires instan-
        -cies doivent etre du meme type.

## TITR [Langage Base]
    Directive TITRE

    Objet :

    La directive TITRE permet de donner un titre a la tache en cours.
Il contient au plus 72 caracteres. La syntaxe est celle de
l'operateur CHAIN (appele en interne).

    Commentaire :

    Ce titre s'affichera, en particulier, lors de tout trace demande
apres l'execution de cette directive.

    Exemple :

    PRESS = 25.86 ;
    ICAS = 2 ;
    TITRE ' CAS DE CHARGE NUMERO' ICAS ' VALEUR DE LA PRESSION' PRESS;

cette suite d'instructions fabrique le titre suivant :

   CAS DE CHARGE NUMERO 2 VALEUR DE LA PRESSION 25.860

## TOIM [Mecanique Resolution]
Operateur TOIM

Syntaxe (EQEX) : Cf Operateur EQEX

'OPER' 'TOIM' tos 'INCO' 'UN'

Objet :

Discretise une condition de contrainte (visqueuse) sur une
surface et calcule l'increment.

Commentaires :

tos tension de surface dans le repere local CHPOINT VECT CENTRE
        ou VECTEUR
      en 2D (Tt=mu dUt/dn Tn=mu dUn/dn - P)
(par convention une tension oposee a la quantite de mouvement est
 comptee negativement, la pression est positive)

UN Champ de vitesse CHPOINT VECT SOMMET

OPTION

L'operateur est discretise par une methode d'element finis EF
(meme discretisation pour EFM1)

## TOPOACTI [—] (proc)
    Procedure TOPOACTI

Cette procedure est appelee par TOPOPTIM.

## TOPOBOOT [—] (proc)
    Procedure TOPOBOOT

Cette procedure est appelee par TOPOPTIM.

## TOPOCHAN [—] (proc)
    Procedure TOPOCHAN
    __________________ TOPOSURF

Cette procedure est appelee par TOPOPTIM et TOPOSURF.

## TOPOCRIT [—]
    Procedure TOPOCRIT

Cette procedure est appelee par TOPOPTIM pour mettre a jour le critere
d optimalite.

Les utilisateurs avances peuvent definir leur propre version de
TOPOCRIT, juste avant de faire appel a TOPOPTIM.

## TOPODENS [—] (proc)
    Procedure TOPODENS

Cette procedure est appelee par TOPOPTIM.

## TOPOFCTR [—] (proc)
    Procedure TOPOFCTR

Cette procedure est appelee par TOPOPTIM.

## TOPOFILT [—] (proc)
    Procedure TOPOFILT

Cette procedure est appelee par TOPOPTIM pour filtrer le champ de
sensibilite.

Les utilisateurs avances peuvent definir leur propre version de
TOPOFILT, juste avant de faire appel a TOPOPTIM.

## TOPOINFO [—] (proc)
    Procedure TOPOINFO

Cette procedure est appelee par TOPOPTIM.

## TOPOLOGY [—] (proc)
    Procedure TOPOLOGY

Cette procedure est appelee par TOPOPTIM pour mettre a jour la
topologie.

Les utilisateurs avances peuvent definir leur propre version de
TOPOLOGY, juste avant de faire appel a TOPOPTIM.

## TOPOMATE [—] (proc)
    Procedure TOPOMATE

Cette procedure est appelee par TOPOPTIM pour modifier les proprietes
du materiau afin de tenir compte d'un champ de densite donne.

La version actuelle de cette procedure ne modifie que le module
d'Young pour les materiaux mecanique et la conductivite pour les
materiaux thermique.

Les utilisateurs avances peuvent definir leur propre version de
TOPOMATE, juste avant de faire appel a TOPOPTIM, en particulier
si un materiau de comportement non lineaire est utilise pour
modifier convenablement toutes les proprietes supposees affectees
par la densite.

## TOPOPTIM [Mathematiques Autres] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CAST3M
        PAR Guenhael Le Quilliec
        Laboratoire de Mecanique Gabriel Lame
 Universite de Tours, Universite d Orleans, INSA Centre Val de Loire
    Polytech Tours, 7 avenue Marcel Dassault, 37200 Tours, France

    Procedure TOPOPTIM
    __________________ TOPOCHAN TOPODENS
        TOPOFCTR TOPOFILT
        TOPOINFO TOPOLOGY
        TOPOMATE TOPORESO
        TOPORSTR TOPOSAUV
        TOPOSENS TOPOSURF

    TOPOPTIM TAB1 ;

    TAB1. CONVERGENCE OC_L2
        CRITERE OC_L2_MIN
        CYCLE OC_MAX_IT
        CYCLES_SAUVEGARDES POIDS_ENERGIE_DEFO
        FACTEUR_D POIDS_MECANISME
        FACTEUR_P POIDS_TEMPERATURE
        FACTEUR_Q PRECISION
        FRACTION_VOLUME PROCEDURE_TOPOPERS
        FILTRE RAPPORT_RAIDEURS_MECANIQUES
        FILTRE_CRITERE RAPPORT_RAIDEURS_THERMIQUES
        FILTRE_EXPOSANT RESOLUTION
        FILTRE_RAYON RESOLUTION_LINEAIRE
        FILTRE_TAUX RESOLUTION_PASAPAS
        MAILLAGE RESTRICTIONS
        MAX_CYCLES SEUIL
        MECANISME TOPOLOGIE
        MECANISME_ZERO_SPRING TOPOLOGIE_MAX_INC
        MES_SAUVEGARDES TOPOLOGIE_MIN
        OC_B_MIN TRAC
        OC_CRITERE ZERO_DIVISION
        OC_L1 ZONE_FIGEE

    Objet :

Cette procedure permet d effectuer une optimisation topologique d une
structure soumise a un chargement mecanique et/ou thermique, en
considerant un comportement lineaire ou non-lineaire, avec ou sans
restrictions geometriques sur la topologie de sortie. Elle permet aussi
d effectuer une synthese d un mecanisme souple.

    Commentaires :

La premiere version de cette procedure s inspirait directement des
travaux de O. Sigmund ainsi que ceux de W. Hunter.

La version actuelle (3.0) a ete adaptee pour traiter les non-linearites
(contact, plasticite, grandes deformations, grands deplacements et
grandes rotations), sous chargements multiphysiques. Il est possible
d ajouter des restrictions geometriques sur la topologie de sortie
(e.g. une periodicite). Elle est entierement ecrite en Gibiane afin de
faciliter les developpements pour les utilisateurs avances.

Deux filtres differents sont proposes :
    - Le filtre GIBIANE qui, comme son nom l indique, est ecrit en
      language Gibiane et qui correspond a des interpolations
      successives entre les noeuds et les points d integration
      afin d assurer des performances correctes meme sur des maillages
      denses.
    - Le filtre MATRICE qui fait appel a l operateur MFIL et qui est
      particulierement adapte au cas des maillages de mailles de
      tailles heterogenes. Quand l exposant vaut 1.0, ce filtre
      est identique a celui propose dans les travaux de O. Sigmund.
L operation de filtrage est assuree par la procedure TOPOFILT que les
utilisateurs avances peuvent redefinir avant de faire appel a TOPOPTIM.

L etape de resolution, les restrictions geometriques, les mises a jour
du materiau (pour tenir compte de la densite), de la sensibilite et de
la topologie sont elles aussi assurees par des procedures externes :
TOPORESO, TOPORSTR, TOPOMATE, TOPOSENS et TOPOLOGY respectivement. La
encore, les utilisateurs avances peuvent redefinir ces procedures avant
de faire appel a TOPOPTIM.

Enfin, une procedure personnelle TOPOPERS peut etre appelee a chaque
cycle d optimisation, juste apres la resolution, donnant a
l utilisateur la possibilite d intergir avec TOPOPTIM au cours du
processus d optimisation. Il peut par exemple appliquer sa propre
fonction objectif et calculer son propre champs de sensibilite, ou
bien encore creer ses propres restrictions geometriques...

    Remarques :

Le facteur d amortissement (FACTEUR_D) permet d attenuer les phenomenes
oscillatoires lors des cycles d optimisation mais ralentit en
contrepartie la convergence.

Le facteur de penalite (FACTEUR_P) a en quelque sorte pour role de
favoriser la creation de branches dans la topologie en amplifiant les
valeurs proches de 0 ou 1 et d atenuer les zones de valeurs
intermediaires.

Le facteur d echelle de gris (FACTEUR_Q) a pour role d eliminer les
valeurs intermidaires pour obtenir au final une topologie binaire
constituee essentiellement de 0 et de 1.

L etape de filtrage a pour role de flouter la sensibilite afin d attenuer
l influence du maillage sur le resultat de l optimisation topologique.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## TOPORESO [—] (proc)
    Procedure TOPORESO

Cette procedure est appelee par TOPOPTIM.

## TOPORSTR [—] (proc)
    Procedure TOPORSTR

Cette procedure est appelee par TOPOPTIM pour appliquer une restriction
geometrique sur la topologie de sortie.

Les utilisateurs avances peuvent definir leur propre version de
TOPORSTR, juste avant de faire appel a TOPOPTIM.

## TOPOSAUV [—] (proc)
    Procedure TOPOSAUV

Cette procedure est appelee par TOPOPTIM pour sauvegarder des
resultats au cours de l'optimisation.

Les utilisateurs avances peuvent definir leur propre version de
TOPOSAUV, juste avant de faire appel a TOPOPTIM.

## TOPOSENS [—] (proc)
    Procedure TOPOSENS

Cette procedure est appelee par TOPOPTIM.

## TOPOSURF [Mathematiques Autres] (proc)
        CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CAST3M
        PAR Guenhael Le Quilliec
        Laboratoire de Mecanique Gabriel Lame
 Universite de Tours, Universite d Orleans, INSA Centre Val de Loire
    Polytech Tours, 7 avenue Marcel Dassault, 37200 Tours, France

    Procedure TOPOSURF
    __________________ TOPOPTIM

    MAIL1 = TOPOSURF TAB1 ;

    TAB1. ELIMINATION ORIENTATION
        EPAISSEUR SUREPAISSEUR
        ISOVALEUR TAUX_FILTRAGE
        MODELE TOPOLOGIE

    Objet :

Cette procedure permet de generer une surface lissee a partir d une
topologie 2D ou 3D. La topologie a lisser peut etre directement issue
de la porcedure TOPOPTIM.

    En entree :

En entree, TAB1 sert a definir les options et les parametres de lissage.
Les indices de l objet TAB1 sont des mots (a ecrire en toutes lettres,
et en majuscules s ils sont mis entre cotes) dont voici la liste :

 ELIMINATION : FLOTTANT correspondant au critere de la directive
        ELIMINATION applique pour la fusion des elements de la
        surface de sortie. Cette donnee est facultative et est
        egale a 1.0e-6 par defaut.

 EPAISSEUR : FLOTTANT donnant l epaisseur d extrusion dans le cas d une
        topologie 2D et qu un maillage 3D est souhaite en sortie
        (mettre a 0.0 sinon). Cette donnee est facultative et est
        egale a 1.0 par defaut.

 ISOVALEUR : FLOTTANT donnant l isovaleur de la surface a generer. Cette
        donnee est facultative et est egale a 0.5 par defaut.

 MODELE : modele de comportement sur lequel repose le champ tolologique
        a lisser. Cette donnee est obligatoire.

 ORIENTATION : LOGIQUE precisant s il faut ou non orienter les elements
        de la surface de sortie et fusionner les elements
        superposes. Cette donnee est facultative et est egale a
        VRAI par defaut.

 SUREPAISSEUR : FLOTTANT correspondant a la valeur de surepaisseur creee
        autour du domaine occupe par le modele du champ
        topologique. De preference, cette valeur doit etre tres
        faible comparee a la taille des elements lorsque le
        domaine n est pas convexe. Cette donnee est facultative
        et est egale a 1.0e-3 par defaut.

 TAUX_FILTRAGE : taux de filtrage a appliquer a la topologie donnee en
        entree. Cette donnee est facultative et est egale a 1
        par defaut.

 TOPOLOGIE : champ scalaire de type MCHAML exprime aux centres de
        gravite et correspondant a la topologie a lisser. Cette
        donnee est obligatoire.

    En sortie :

Une surface MAIL1 est obtenue en sortie sous la forme d un maillage
compose d elements triangulaires a 3 noeuds en 3D ou d elements de type
segments a 2 noeuds en 2D.

Cette surface peut ensuite etre extraite au format STL via la procedure
SORTIR.

    Exemples :

toposurf_01.dgibi toposurf_02.dgibi toposurf_03.dgibi

## TOTE [Mathematiques Traitement]
Operateur TOTEMP

L'operateur TOTEMP calcule la somme des intervalles de l'abscisses
d'une fonction pour lesquelles son ordonnee est superieure a un
seuil predefini. Exemple : calcul de la duree totale de choc d'un
enregistrement d'impacts au cours du temps.

LREEL1 = TOTEMP EVOL1 VAL1 ;

Commentaire :

EVOL1 : objet contenant une ou des fonctions (type EVOLUTIO)

FLOT1 : seuil (type FLOTTANT)
        FLOT1 est donne sous la forme d'un % de la valeur maximale
        de l'enregistrement (1.D-6% par defaut)

LREEL1 : objet resultat (type LISTREEL)

Remarque :

Si EVOL1 contient plusieurs fonctions, l'operation est faite pour
chacune d'elles.

Les abscisses doivent etre classees dans un ordre strictement
croissant.

## TOUR [Mathematiques Autres]
Operateur TOUR
-------------- DEDU

     OBJ2 = OBJ1 TOUR FLOT1 POIN1 (POIN2 si 3D) ;

     NOBJ1 ... NOBJN = OBJ1 ... OBJN TOUR

Objet :

L'operateur TOUR cree un objet resultant de la rotation autour
d'un point ou d'un axe du support geometrique d'un objet, et
eventuellement de ses composantes.

Lorsque l'operation est realisee simultanement pour plusieurs
operandes, les geometries elementaires ne sont transformees
qu'une seule fois.

Dans le cas ou l'objet est un CHPOINT et possede des composantes
   'UX' 'UY' 'UZ' ou 'FX' 'FY' 'FZ' ou
   'RX' 'RY' 'RZ' ou 'MX' 'MY' 'MZ' ,
ou s'il s'agit d'un MCHAML de composantes
   'SMXX' 'SMYY' 'SMZZ' 'SMXY' 'SMXZ' 'SMYZ' ou
   'EPXX' 'EPYY' 'EPZZ' 'EPXY' 'EPXZ' 'EPYZ',
celles-ci subissent egalement la rotation, les autres composantes
restant inchangees.

Cet operateur n'est pas disponible en DIMEnsion 1 (sans interet).

Commentaire :

  OBJ1 : types POINT, MAILLAGE, CHPOINT, MCHAML, MMODEL.
        OBJ1 peut aussi etre une table. Dans ce cas tous les
        objets contenus dans la table, qui doivent etre d'un des
        types ci-dessus, subiront la translation ou la
        transformation. Si une table est donnee, il ne doit pas y
        avoir d'autres objets.

  FLOT1 : type FLOTTANT, amplitude de rotation en degres

  POIN1, POIN2 : type POINT, centre de rotation en 2D, axe en 3D

  OBJ2 : resultat de meme type que OBJ1

  OBJ1 ... OBJN : voir OBJ1

  NOBJ1 ... NOBN : resultats respectivement de memes types
        que OBJ1 ... OBJN

## TRAC [Post-traitement Affichage]
    Directive TRACER
    ---------------- @PLOTPRI

    La directive TRAC permet de dessiner plusieurs types d'objets :
    1 : MAILLAGE
    2 : DEFORMEE
    3 : VECTEUR
    4 : isovaleurs d'un CHPOINT ou d'un MCHAML
    5 : ARETE d'un MAILLAGE

    La directive TRAC ne modifie pas les objets fournis en entree,
    mais realise le trace sur l'unite graphique specifiee par
    l'instruction : " OPTION TRAC ... ".

PART{trace d'un MAILLAGE}

    TRAC  OBJET1 | ((OEIL1) si 3D)  |  ;
        | ('QUAL')  |
        | ('NOEUD')  |
        | ('COUL'  ( COUL1 ) )  |
        | ('ELEM')  |
        | ('CACH')  |
        | ('FACE')  |
        | ('ECLA'  ( RAPP1 ) )  |
        | ('COUPE' POIN1 POIN2 POIN3 ) |
        | ('SECT'  POIN1 POIN2 POIN3 ) |
        | ('TITR' 'bla bla...')  |
        | ('NCLK')  |
        | ('DATE')  |
        | ('CHAM')  |
        | ('BOIT' MAIL3)  |
        | (ANNO1)  |

    Commentaire :

    OBJET1 : objet a tracer (type MAILLAGE ou RIGIDITE).
        Dans le cas ou il s'agit d'une RIGIDITE, c'est le maillage
        sous-jacent a la rigidite qui est trace. Ceci permet
        d'obtenir un trace d'une structure munie de ses conditions
        aux limites.

    OEIL1 : point de vue (en 3D) (type POINT) (facultatif)
        le trace est fait alors en perspective cavaliere.

    'QUAL' : mot-cle indiquant que les noms des entites presentes sur
        le dessin y seront portes.

    'NOEUD' : mot-cle indiquant que les numeros reels des noeuds seront
        mentionnes sur le dessin.
        ATTENTION : la numerotation change lors de certaines
        instructionsa (comme TASS ou SORT).

    'COUL' : mot-cle indiquant que seuls les elements qui ont la
        couleur specifiee par COUL1 (type MOT) ou, si COUL1 n'est
        pas precisee, la couleur par defaut, seront affiches.

    'ELEM' : mot-cle indiquant que les numeros locaux dans chaque
        objet elementaire seront mentionnes sur le dessin.
        Un objet elementaire est constitue d'un seul type
        d'element.

    'CACH' : mot-cle indiquant que seules les parties apparentes de
        l'objet seront affichees.

    'FACE' : mot-cle indiquant que la representation sera effectuee en
        remplissant les faces de l'element. L'intensite sera
        fonction de l'angle de la facette avec l'observateur.

    'ECLA' : mot-cle indiquant que le trace sera effectue en eclatant
        les elements. Chaque element sera represente avec un
        rapport d'homothetie RAPP1 (type FLOTTANT), egal par
        defaut a 0.5.

    'COUPE' : mot-cle indiquant que seule la partie se trouvant au dela
        du plan de coupe, defini par trois points POIN1, POIN2 et
        POIN3 (type POINT), par rapport a l'oeil est tracee.

    'SECT ' : mot-cle indiquant que seule l'intersection avec le plan de
        coupe, defini par trois points POIN1, POIN2 et POIN3 (type
        POINT), par rapport a l'oeil est tracee.

    'TITR' : Modification du titre du trace.

    'NCLK' : supprime les possibilites de trace interactif (X & OGL).

    'DATE' : mot-cle indiquant que l'affichage sera horodate.

    'CHAMP' : mot-cle indiquant que la valeur des champs sera indique au
        du point support.

    'BOITE' : mot-cle indiquant que la fenetre de trace sera centree sur
        le maillage MAIL3 (type MAILLAGE). MAIL3 n'est pas trace.

    ANNO1 : objet ANNOTATI permettant d'enrichir l'affichage graphique
        (categories, etiquettes...)

PART{trace d'une DEFORMEE} |

    TRAC  DEFO1  | ((OEIL1) si 3D)  |  ;
        | ('CACH')  |
        | (('DIRE') 'COUPE' POIN1 POIN2 POIN3) |
        | ('SECT' POIN1 POIN2 POIN3);  |
        | ('ANIME')  |
        | ('OSCIL')  |
        | ('TITR' 'bla bla...')  |
        | ('NCLK')  |
        | ('FACE') ('FACB') ('FSDB')  |
        | ('BOIT' MAIL3)  |
        | (ANNO1)  |

    Commentaire :

    DEFO1 : objet deforme a tracer (type DEFORME).

    OEIL1 : point de vue (en 3D seulement) (type POINT) (facultatif).

    'COUPE' : mot-cle indiquant que seule la partie se trouvant au dela
        du plan de coupe, defini par trois points POIN1, POIN2 et
        POIN3 (type POINT), par rapport a l'oeil est tracee.

    'SECT ' : mot-cle indiquant que seule l'intersection avec le plan de
        coupe, defini par trois points POIN1, POIN2 et POIN3 (type
        POINT), par rapport a l'oeil est tracee.

    'CACH' : mot-cle indiquant que seules les parties apparentes de
        l'objet sont tracees.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## TRAC3D [Post-traitement Affichage] (proc)
    Procedure TRAC3D

    TRAC3D GEO1 CHPO1 FLOT1 FLOT2 N1 N2 FLOT3 FLOT4 FLOT5 LOG1 ;

    Objet :

    Cette procedure permet de construire un maillage 3D deforme a par-
tir d'un maillage 2D (forme d'elements SEG2 uniquement) et d'un champ
de deplacements axisymetrique ou de Fourier.

    Elle permet ensuite de tracer ce maillage 3D suivant un oeil dont le
coordonnees sont passees en argument. Il est possible aussi de tracer
ce maillage a partir d'un autre oeil, il faut pour cela affecter au
parametre LOG1 la valeur vraie.

    Commentaire :

   GEO1 : maillage 2D (type MAILLAGE)

   CHPO1 : champ de deplacements issu d'un calcul axisymetrique ou de
        (type CHPOINT)

   FLOT1 : amplification des deplacements (type FLOTTANT)

   FLOT2 : angle de rotation en degres pour la construction du
        maillage 3D (type FLOTTANT)

   N1 : nombre de decoupages de cet angle (type ENTIER)

   N2 : numero de l'harmonique (type ENTIER) (0 si calcul axi)

   FLOT3 : abscisse de l'oeil (type FLOTTANT)

   FLOT4 : ordonnee de l'oeil (type FLOTTANT)

   FLOT5 : cote de l'oeil (type FLOTTANT)

   LOG1 : objet (type LOGIQUE) qui est egal a VRAI si on utilise la
        procedure en interactif ou egal a FAUX sinon

    Remarque IMPORTANTE :

    Cette procedure ne cree aucun objet.

    Si on utilise cette procedure en batch il faut affecter a l'argument
LOG1 la valeur FAUX.

## TRAC3D_2 [Post-traitement Affichage] (proc)
    Procedure TRAC3D_2

    TAB1 = TRAC3D_2 GEO1 OBJ1 MODL1 FLOT1 N1 N2 ;

    Objet :

    Cette procedure permet de construire un maillage et un champs
soit de deplacements, soit de contraintes, soit de deformations
ou soit de pression 3D a partir d'un maillage 2D (forme d'elements
SEG2, TRI3 ou QUA4 uniquement) et d'un champ respectivement de
deplacements, de contraintes, de deformations ou de pression
axisymetrique ou de Fourier. Il ne peut pas etre fournit de
maillage de fluide et de structure en meme temps.

Note : le MCHAML de sortie est appuye aux noeuds du maillage.
       le CHPOINT de sortie est de nature 'DIFFUS'

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

## TRACHIS [Post-traitement Analyse] (proc)
 Procedure TRACHIS
 ------------------ EVOL DARCYTRA

 TAB1 = TRACHIS TAB2 MOT1 GEO1  (| LENTI1 |) (LMOTS1) (| LMOTS2 |)
        | LREEL1 |  | TAB3  |

        ('PREF' MOT2) ('UNIT' MOT3 (FLOT1)) ;

Objet

    Cette procedure sert au post-traitement des resultats d'un
    calcul transitoire type DARCYTRA, DARCYSAT, PASAPAS, CHIMIE ...
    On genere des evolutions le long d'une ligne et leurs legendes.
    Les resultats sont groupes dans une table qui permettra
    d'effectuer des traces a l'aide de la procedure DESTRA.

Commentaires

  TAB2 : Table de donnees issue du calcul transitoire
        contenant les indices 'TEMPS' et MOT2,
        auxquels on trouve, aux indices entiers les temps et
        le champ point que l'on souhaite explorer a ces
        temps-la.

  MOT1 : Nom de l'indice de TAB2 indiquant les CHPOs a suivre
        (type MOT). TAB2.MOT1.i doit etre un CHPOINT.

  GEO1 : MAILLAGE de la ligne (SEG2) selon laquelle visualiser
        l'evolution de la grandeur MOT1.

  MOT2 : mot par lequel on voudra remplacer MOT1 dans les
        legendes des graphiques.
        c'est aussi le prefixe des legendes.
        (type MOT, Defaut = MOT2)

  LENTI1 : Liste des indices des temps a utiliser
        (type LISTENTI, Defaut = tous)

  LREEL1 : Liste des temps a utiliser (Defaut = tous), doivent
        correspondre a ceux de TAB2.

  LMOTS1 : Liste des composantes des chpos a utiliser
        (Defaut = toutes)

  TAB3 : Table contenant, pour chaque indice entier de
        composante, la chaine de caracteres correspondante.
        Ils sont aussi le suffixe de la legende qui varie avec la
        composante.
        (type MOT, defaut = nom de la composante).

  LMOTS2 : idem sous forme de liste, si on peut se contenter de 4
        caracteres (type MOT, defaut = nom de la composante).

  MOT3 : Unite de temps a faire figurer en suffixe de legende
        (facultatif, type MOT, dans {us,ms,s,h,j,a}),
        voir CONVT.

  FLOT1 : valeur en secondes de l'unite de temps dans laquelle
        sont donnees les valeurs de TAB2.'TEMPS' (defaut=1)

  TAB1 : table indicee par des entiers. Elle contient pour
        chaque cas i une table a trois indices :
    . 'VALEUR' : L'evolution en fonction de l'abscisse pour une
        composante a un temps donne.
    . 'LEGEND1': Prefixe de la legende pour toutes les courbes
        contient MOT2 (defaut : MOT1)
    . 'LEGEND2': Suffixe de cette legende (variable)
        contient TAB3.i (defaut LMOTS1(i)) et le mot 't='
        suivi de la valeur du temps dans l'unite MOT4, puis
        l'unite de temps MOT4.

Remarques

Les mots-clefs et leurs arguments doivent etre places en dernier

## TRACHIT [Post-traitement Analyse] (proc)
 Procedure TRACHIT
 ------------------ EVOL DARCYTRA

 TAB1 = TRACHIT TAB2 MOT1 GEO1 (| LENTI1 |) (LMOTS1) (TAB3) (TAB4)
        | LREEL1 |

        ('PREF' MOT2) ;

Objet

    Cette procedure sert au post-traitement des resultats d'un
    calcul transitoire type DARCYSAT, DARCYTRA, PASAPAS, CHIMIE ...
    On genere des evolutions en fonction du temps et leurs legendes.
    Les resultats sont groupes dans une table qui permettra
    d'effectuer des traces a l'aide de la procedure DESTRA.

Commentaires

  TAB2 : Table de donnees issue du calcul transitoire
        contenant les indices 'TEMPS' et MOT2,
        auxquels on trouve, aux indices entiers les temps et
        le champ point que l'on souhaite explorer a ces
        temps-la.

  MOT1 : Nom de l'indice de TAB2 indiquant les CHPOs a suivre
        (type MOT). TAB2.MOT1.i doit etre un CHPOINT.

  GEO1 : MAILLAGE contenant les points auxquels
        visualiser l'evolution de la grandeur MOT1
        (type MAILLAGE).

  MOT2 : mot par lequel on voudra remplacer MOT1 dans les
        legendes des graphiques.
        c'est aussi le prefixe des legendes.
        (type MOT, Defaut = MOT2)

  LENTI1 : Liste des indices des temps a utiliser
        (type LISTENTI, Defaut = tous)

  LREEL1 : Liste des temps a utiliser, doivent correspondre a ceux
        de TAB2 (type LISTREEL, Defaut = tous).

  LMOTS1 : Liste des composantes des chpos a utiliser
        (type LISTMOTS, Defaut = toutes)

  TAB3 : Table contenant, pour chaque indice entier de
        composante, la chaine de caracteres correspondante.
        Ils sont aussi la premiere partie du suffixe de la
        legende qui varie avec la composante
        (type MOT, defaut = nom de la composante, sous-type
        (obligatoire si on donne TAB4) indice
        'SOUSTYPE'='NOM_COMPOSANTE').

  TAB4 : TABLE contenant, pour chaque indice entier de
        point, la chaine de caracteres correspondante.
        Ils sont aussi la deuxieme partie du suffixe de la
        legende qui varie avec le point.
        (type MOT, defaut = numero du point, sous-type
        (obligatoire) indice 'SOUSTYPE'='NOM_POINT').

  TAB1 : TABLE indicee par des entiers. Elle contient pour
        chaque indice i une table a trois indices :
    . 'VALEUR' : L'evolution en fonction du temps pour une
        composante en un point.
    . 'LEGEND1': Prefixe de la legende pour toutes les courbes.
        Contient MOT2 (defaut = MOT1)
    . 'LEGEND2': Suffixe de cette legende (variable).
        Contient le nom de composante TAB3.i (defaut =
        LMOTS1(i)) et le nom du point TAB4.i (defaut =
        mot 'PT ' puis le numero du point dans le maillage
        GEO1).

Remarques

Les mots-clefs doivent etre places en dernier

## TRACMECA [Post-traitement Affichage] (proc)
   Procedure TRACMECA
   ------------------ LIMEMECA

   TAB3=TRACMECA MODL1 TAB1 TAB2 (FLOT1);

    Objet :

    La procedure TRACMECA permet de visualiser les modes de rupture
elementaires de la structure MODL1, determines dans les table TAB1 et
TAB2 par l'operateur MESM. Le resultat est une table TAB3 d'index entier
associer au numero du mecanisme d'objet de type DEFORMEE. FLOT1 et un
coefficient reel qui permet de moduler l'amplitude de la deformee
(defaut 1.).

    La presence de rotation plastique est indiquee par de cercles
(de couleur rouge si la rotation est positive, rose si elle est
negative). La plastification d'un element est representee par des
etoiles (de couleur bleue en compression, turquoise en traction).

## TRACPART [Post-traitement Affichage] (proc)
Procedure TRACPART

TRACPART TAB1 ( | 'TOUT' | ) 'NCLK' ;
        | 'ANIM' |
        |  ENTI1 |

Objet :

La procedure TRACPART permet de visualiser graphiquement les
partitions d'un maillage telles que creees avec l'operateur PART

Commentaire :

TAB1 : partition du maillage renvoyee par PART (type TABLE)

'TOUT' : mot-cle indiquant que l'on souhaite tracer toutes les
        partitions simultanement

'ANIM' : mot-cle indiquant de mettre en evidence les differentes
        partitions les unes apres les autres

ENTI1 : numero de la partition que l'on souhaite mettre en
        evidence (type ENTIER)

'NCLK' : mot-cle permettant de desactiver l'interactivite du trace
        (pas de rotation, zoom, etc...)

Remarques :

1) En l'absence des mots-cles 'TOUT' et 'ANIM' et sans nombre
   ENTI1, la fenetre de trace fera apparaitre un menu interactif
   permettant a l'utilisateur de balayer les differentes partitions
   a sa guise.

2) La vitesse de defilement des partitions avec l'option 'ANIM'
   est pilotee par la valeur de la variable __ANIM__ (type ENTIER)
   valant 1000000 par defaut. Plus sa valeur est petite, plus
   le defilement est rapide. Elle peut etre modifiee directement
   dans le jeu de donnees avant l'appel a TRACPART.

## TRACTUFI [Mecanique Rupture] (proc)
    Procedure TRACTUFI

    EVOL1 CM KF = TRACTUFI TAB1 ;
        TAB1.'METHODE' .'COUTRA' .'YOUN'
        .'SIG1' .'SIGF4 .'REXT' .'EPAI'
        .'ANGLE' .'COUL' .'ALFA' .'N'

    Objet :

   Cette procedure est specifique a l'element de tuyauterie fissuree
TUFI . Elle permet de determiner la loi de comportement globale
moment-rotation de l'element a partir de la courbe de traction du
materiau, en appliquant :

   - soit une methode simplifiee (quatre methodes sont disponibles
     correspondant respectivement aux mots-cles TADA,LBBNRC,LBB1,LBB2)
   - soit une base de donnees experimentales (mot-cle DEFR)

   La procedure cree un objet evolution pouvant etre directement
   introduit en donnees de l'operateur MATE (composante TRAC) pour
   l'element TUFI. Elle fournit aussi CM coefficient de la matrice de
   complaisance ainsi que KF qui permet de calculer le facteur de
   forme

   Commentaire :

   EVOL1 : objet (type EVOLUTION) decrivant la courbe moment-rotation

   CM : objet (type FLOTTANT) complaisance

   KF : objet (type FLOTTANT) pour le calcul du facteur de forme

   TAB1 : objet (type TABLE) contenant :

      TAB1 METHODE : mot-cle (type MOT) valant DEFR, TADA, LBBNRC,
        LBB1 ou LBB2 et indiquant la methode simplifiee
        utilisee
      TAB1 COUTRA : objet (type EVOLUTION) decrivant la courbe de
        traction du materiau
      TAB1 YOUN : module d'Young (type FLOTTANT)
      TAB1 SIG1 : contrainte conventionnelle a 0.2% (type FLOTTANT)
      TAB1 SIGF : eventuellement contrainte d'ecoulement
        (type FLOTTANT)
      TAB1 REXT : rayon exterieur (type FLOTTANT)
      TAB1 EPAI : epaisseur
      TAB1 ANGLE : angle total de la fissure en degres
      TAB1 COUL : indique eventuellement la couleur (type MOT)
        affectee a la courbe creee
      TAB1 ALFA : eventuellement valeurs permettant d'adapter
      TAB1 N : la courbe de traction (methode LBBNRC)
        (type FLOTTANT)

## TRADUIRE [Mecanique Dynamique] (proc)
    Procedure TRADUIRE

    TAB1 = TRADUIRE (SOL1) ;

    Objet :

    Cette procedure cree, a partir d'un objet SOLUTION de sous-type MODE
une table de sous-type BASE_DE_MODES.

    Commentaire :

    SOL1 : objet (type SOLUTION, sous-type MODE) a convertir

    TAB1 : objet (type TABLE) utilise en entree de l'operateur DYNE

## TRAJ [Mecanique Resolution]
   Operateur TRAJ

    Cas d'une formulation elements finis :
    MODL4 MCH4 = TRAJ MOT1  |CHPO1|  |TAB1 |  ('PORO' MCH1) TAB2 ;
        |TAB4 |  |MODL1|

    Cas d'une formulation mixte hybride(modele DARCY)
    MODL4 MCH4 = TRAJ MOT1 MODL1 |CHPO2|  ('PORO' MCH1)  TAB2  ;
        |TAB5 |  ('DISP' MCH2)
        ('DIFF' MCH3)

      Objet
     L'operateur TRAJ permet de calculer les trajectoires de particules
     lachees dans un domaine maille pour lequel on connait :
     soit un champs de vitesses ou de flux, constant au cours du temps,
     soit des champs de vitesses ou de flux, donnes pour differentes
     valeurs du temps.

     Commentaire

     TAB1 est un objet de type TABLE et de sous type DOMAINE.
        C'est le resultat de l'operateur DOMA applique au maillage
        sur lequel on fait le calcul.

     MOT1 indique le type de calcul que l'on veut faire :
        'CONVECTION_EXPLICITE' la position des particules est
        calculee de proche en proche en fonction de la
        vitesse locale (c'est l'option par defaut).
        'CONVECTION_ANALYTIQUE' Calcul des lignes de courant par
        integration analytique (uniquement en formulation EFMH)
        'CONVECTION_DIFFUSION' Calcul des trajectoires par
        iterations successives en prenant en compte les
        phenomenes de convection-dipersion-diffusion. (Cette
        option n'est pour l'instant developpee que pour le
        modele DARCY)

     MODL1 Objet modele (type MMODEL) decrivant la formulation
        utilisee (cf. MODE). Les formulations actuellement
        prevues sont DARCY et NAVIER_STOKES.

     CHPO1 champ de vitesse defini aux noeuds du maillage TAB1.MAILLAGE
        Les composantes ont pour noms VX VY (VZ).

     TAB4 est le nom d'un objet de type TABLE et de sous type
        TRANSITOIRE. Cette table contient a l'indice 'TEMPS'
        une table de flottants, et a l'indice 'VITESSE',une
        table de CHPOINT. Ces deux tables sont indicees par des
        entiers 0 1 2 ...N :
        TAB4.VITESSE.N est un CHPOINT ayant les memes
        caracteristiques que CHPO1.
        TAB4.TEMPS.N est le temps correspondant.

     CHP02 Objet de type CHPOINT contenant le debit a travers
        chaque face. Le support geometrique de ce champ est
        le maillage contitue les centres des FACES. Le nom de
        la composante du CHPOINT est FLUX (cf. HDEB).

     TAB5 est un objet de type TABLE et de sous-type
        DARCY_TRANSITOIRE. Elle contient a l'indice 'TEMPS'
        une table de flottants, et a l'indice 'FLUX', une table de
        CHPOINT. Ces deux tables sont indicees par des
        entiers 0 1 2 ...N (cf DARCYTRA) :
        TAB5.FLUX.N est un CHPOINT ayant les memes
        caracteristiques que CHPO2.
        TAB5.TEMPS.N est le temps correspondant.

     MCH1 objet MCHAML contenant la porosite au centre de gravite
        de chaque element. Au moment du calcul la vitesse sera
        divisee par la porosite. Si cette valeur est absente la
        porosite est supposee egale a 1.

     MCH2 objet MCHAML a deux composantes contenant respectivement
        la dispersivite longitudinale et la dispersivite
        transversale au centre de gravite de chaque element. Les
        dispersivites sont imposees constantes par element.
        Par defaut, la dispersivite est nulle.
        (utilise uniquement dans le calcul 'CONVECTION_DIFFUSION')

     MCH3 objet MCHAML a une composante contenant la diffusion
        isotrope effective au centre de gravite de chaque
        element. Par defaut, la diffusion est nulle.
        (utilise uniquement dans le calcul 'CONVECTION_DIFFUSION')

     TAB2 table a plusieurs indices contenant la description
        du lacher de particules :

     TAB2.'TEMPS_LIMITE' contient un reel : le temps maximal de calcul

     TAB2.'CFL' contient un reel : le nombre de Courant a respecter.
        Le pas de temps de calcul en depend. En moyenne, il y aura
        1/CFL sauts de particule par maille.
        Ce nombre doit etre compris entre 1.E-8 et 1.(Defaut 0.05)
        (utilise uniquement dans le calcul 'CONVECTION_EXPLICITE').

     TAB2.'DELTAT_SAUVE' contient un reel : le pas de temps avec lequel
        on conserve les resultats pour un post-traitement. Si
        cette valeur est nulle, tous les temps de calcul seront
        sauvegardes.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## TRAN [Maillage Surfaces]
    Operateur TRANSLATION
    --------------------- ROTA SURF GENE

    SURF1 = LIG1 TRANSLATION (N1) ('DINI' DENS1) ('DFIN' DENS2) VEC1 ;

    Objet :

    L'operateur TRANSLATION construit la surface engendree par la trans-
lation d'une ligne suivant un vecteur donne.

    Commentaire :

    LIG1 : ligne a translater (type MAILLAGE)
        l'objet LIG1 doit etre une ligne

    N1 : nombre de couches d'elements engendrees dans la translation
        (type ENTIER)

    VEC1 : vecteur de translation (type POINT)

    DENS1 | : densites associees (type FLOTTANT) a la ligne LIG1 et au
    DENS2 |  vecteur VEC1

    SURF1 : surface engendree (type MAILLAGE)

    Remarque :

    Si N1 n'est pas specifie, le nombre de couches d'elements est calcul
en fonction des densites utilisees.

    Si N1 est specifie et positif, N1 couches d'egale epaisseur seront
engendrees.

    Si N1 est negatif, N1 couches seront engendrees et leur epaisseur
sera calculee en tenant compte des densites utilisees.

    Si les densites associees a la ligne LIG1 et au vecteur VEC1 ne
sont pas correctes, il est possible de les surcharger. Pour la densite
initiale, il faut donner la bonne valeur derriere le mot-cle 'DINI'
et pour la finale, derriere le mot-cle 'DFIN'.

    Si LIG1 est une surface, la translation s'applique au cote 3 de
cette surface, si il existe, et le resultat est la surface initiale
augmentee de celle que l'on cree.

## TRANGEOL [Fluides Resolution] (proc)
    Procedure TRANGEOL

    RES1 RES2 = TRANGEOL modarcy TRANS1 (TRANS2);

 APPELE par TRANSGEN - DECONSEILLE AUX UTILISATEURS NON DEVELOPPEURS

 resout : POROSITE * DC/DT = DIV (DIFFUSIVITE GRAD C - CONVECTION C)
        + SOURCE

        ou C est la CONCENTRATION, eventuellement a plusieurs
        composantes (multiespeces non couplees).
        La diffusivite, la convection ... doivent etre
        toutefois les memes pour toutes les especes
        pour avoir des matrices de discretisation communes.
        seul le terme source est donne par espece.

        Condition aux limites Neumann DIrichlet Mixtes flux total

        DIFFUSIVITE = DIFFUSIVITE entree + Dispersivite calculee

        Decentrement automatique (peut etre desactive en EFMH).

        Resolution sur 1 avancee en TEMPS.

        Discretisation VF ou EFMH

        Solveur KRES

|modarcy  Objet modele (MMODEL cree par MODE) DARCY  |

| TRANS1  Table contenant les indices suivants :  |
|---------------------------------------------------------------- |
|'DIFFUSIVITE' Donnees physiques et materielles :  |
|  diffusivite effective - CHAMPOINT de COMPOSANTES  |
|  K11 K21 K22 K31 K32 K33 au centre des elements  |
|  |
|'POROSITE'  Valeur du coef devant D/DT (Type Champoint, Comp  |
|  'SCAL', ou FLOTTANT) - Defaut 1.  |
|  |
| DELTAT  pas de temps  |
|  |
|'CONVECTION'  vitesse au face. C'est le debit integre aux faces  |
|  multiplie par la normale sortante de l'element  |
|  et divise par la longueur de la face.  |
|  Il s'agit de la projection du vecteur vitesse sur  |
|  direction normale a la face. (Type CHPO Face, comp.|
|  VX VY VZ). L'interet est que cette vitesse est  |
|  desormais intependante de l'orientation des normale|
|  ce qui est utile dans certains cas.  |
|  OPTIONNEL  |
|  |
|'VITELEM'  Vitesse au centre des elements (Type CHPO centre,  |
|  comp. VX VY VZ). Utilise uniquement si DECENTREMENT |
|  ou si dispersion. OPTIONNEL donc  |
|  |
|'ALPHAL'  coefficient de dispersivite longitudinale (CHPO de |
|  composante SCAL) - 0 si absent  |
|  |
|'ALPHAT'  coefficient de dispersivite transverse (CHPO de  |
|  composante SCAL) - 0 si absent  |
|  Rque : si ALPHAL ou ALPHAT est present les deux  |
|  doivent etre renseignes.  |
|  |
|----------------------  |
|Conditions initiales :  |
|----------------------  |
|  |
|'CONCENTRATION' concentration en debut de pas de temps  |
|  (quantite d'element par unite de volume d'eau)  |
|  (Type CHPO Centre, Comp libre 4 lettres au plus)  |
|  la concentration peut avoir plusieurs composante  |
|  la resolution etant alors faite pour chaque  |
|  composante  |
|  |
|--------------------------------------  |
|Conditions aux limites / chargements :  |
|--------------------------------------  |
|  |
| 'CLIMITES'  table contenant les indices suivants :  |
|  |
|'TRACE_IMPOSE' Valeurs des traces imposees (charge ou concentra- |
|  -tion) - nom de la concentration  |
|  |
|'FLUX_IMPOSE' Valeurs des flux imposes integres par face  |
|  (Type CHARGEMENT de CHPO Face) - nom concentration |
|  |
|'FLUXTOT_IMP' Valeurs des flux totaux imposes integres par face  |
|  (Type CHARGEMENT de CHPO Face, comp. nom de la  |
|  concentration )  |
|  |
|'MIXTES'  Table : - indice C contient les valeurs des flux  |
|  mixtes imposes integres par face  |
|  (Type CHARGEMENT de CHPO Face,  |
|  comp. idem concentration defaut 0.)|
|  - indices A et B sont des reels  |
|  |
|  la condition mixte s'ecrit  |
|  C =  A * flux diffusif +  B * Concentration  |
|  |
|  |
|'SOURCE'  Valeurs du terme source par maille et par unite de |
|  temps (ex : puits, filiation)  |
|  Les valeurs a l'indice i sont les valeurs entre  |
|  les temps i-1 et i.  |
|  (CHARGEMENT de CHPO Centre, comp de conc. ini)  |
|  |
|  |
|--------------------  |
|Donnees numeriques :  |
|--------------------  |
|  |
|  |
| 'LUMP'  FAUX SI pas de mass lumping, VRAI sinon.  |
|  VRAI seulement sur des maillages de rectangles et  |
|  parallelepipedes rectangles et tenseur de dissusion|
|  orthotrope. Permet de rendre les schemas monotone  |
|  pour la diffusion-instationnaire - OBLIGATOIRE  |
|  |
| 'DECENTREMENT' VRAI si diffusion numerique pour Peclet = 2,  |
|  permet  |
|  de stabiliser (en explicite) voire rendre monotone |
|  le schema de convection.  |
|  FAUX si schema sans convection, ou en implicite et |
|  absence d'oscillations - plus precis  |
|  OBLIGATOIRE  |
|  |
| 'TYPDISCRETISATION'  'VF' si VF et 'EFMH' si EFMH  |
|  |
|  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## TRANSFER [Mecanique Dynamique] (proc)
Procedure TRANSFER

        |  Mot1  P1  |
 Ftrans = TRANSFER Modes Amor |  |
        | 'SEISME' Dir1 |

        Mot2 P2 Mosort Lfreq Mochoi (Mocoul) ;

Cette procedure calcule la fonction de transfert d'une structure
en deplacement, vitesse ou acceleration. C'est la reponse (amplitude
complexe) a une force localisee ou a une acceleration d'ensemble.
Le calcul est effectue par recombinaison modale.

    Modes : Objet SOLUTION contenant les modes de la structure
        ou
        Objet TABLE contenant les modes de la structure

    Amor : Objet LISTREEL contenant les amortissements reduits
        pour chaque mode (ex : pour 2% on mettra 0.02)

    Mot1 : Objet MOT definissant la direction de la sollicitation
        (UX, UY, UZ ... ) dans le cas d'une force ponctuelle

    P1 : Objet POINT definissant le point d'application de la
        sollicitation dans le cas d'une force ponctuelle

    Dir1 : Objet MOT definissant la direction de la sollicitation
        (UX, UY, UZ ... ) dans le cas d'une acceleration
        d'ensemble

    Mot2 : Objet MOT definissant la direction pour laquelle on
        calcule la reponse

    P2 : Objet POINT definissant le point oº l'on calcule la
        reponse

    Lfreq : Objet LISTREEL definissant les frequences pour
        lesquelles le calcul est effectue

    Mosort : Objet MOT definissant le type de reponse demande
        Les mots admis sont : DEPL pour deplacement
        VITE pour vitesse
        ACCE pour acceleration
        Dans le cas d'une acceleration d'ensemble (SEISME), le
        deplacement et la vitesse sont donnes dans le repere
        relatif et l'acceleration dans le repere absolu.

    Mochoi : Objet MOT definissant le type de sortie desire
        Les mots admis sont : MOPH pour module et phase
        REIM pour partie reelle et partie
        imaginaire

    Mocoul : Objet MOT facultatif definissant la couleur des courbes
        Si Mocoul est absent, la couleur choisie est la couleur
        par defaut

   Le resultat Ftrans est un objet EVOLUTION, de sous-type complexe
   contenant soit la partie reelle et la partie imaginaire, soit le
   module et la phase suivant la valeur de Mochoi

## TRANSGEN [Fluides Resolution] (proc)
     Operateur TRANSGEN

     TRANSGEN TABLE ;

   ISSUE de la procedure DARCYTRA !
   La syntaxe est conservee a l'exception de quelques points :

   1 - quelques nouvelles fonctionnalites supplementaires
        - numeriques : choix VF EFMH, decentrement, mass lumping,
        solveur KRES accessible
        - physique : dispersivite calculee, nouvelles conditions
        aux limites (mixtes, flux total)

   2 - syntaxe modifiee pour porosite et caracteristiques, et FLUXDIFF
       FLUXCONV au lieu de 'FLUX', CONVECTION est maintenant une vitesse
       et non un flux convectif, VITELEM la vitesse au centre est rajoutee
       pour les calculs de dispersivite.

   3 - plus d'histoire de composantes 'H' 'TH' pour la concentration
     et sa trace car pas lieu d'etre en VF et relativement incompatible
     avec une gestion multiespece. La composante de concentration est
     libre (ex I129) et les conditions aux limites doivent avoir
     le meme nom de composante, ainsi que pour toutes les variables de meme
     dimension que la concentration (Concentration de saturation etc ...).
     Voire notice detaillee en dessous pour les noms de composantes.
     En gros, les jeux de donnees Darcytra tournent si les 'TH' sont
     transformes en 'H' plus modifs -1- et -2- (au plus quelques lignes
     dans les jeux de donnees), voir les jeux transport*.dgibi etc ..

   Fonction

   Resolution de l'equation de transport de Radio nucleides en milieu
   poreux par une methode d'elements finis mixtes hybrides ou VF.
   Les inconnues du probleme sont
   - en EFMH, la concentration, la trace de
    concentration et le debit diffusif.
   - en VF, la concentration
   Gere pas de temps, retard, diffusion, dispersion, convection,
   source, preicipitation dissolution, decroissance, conditions aux
   limites (Dirichlet, Neumann, Mixtes, flux total)
   numerique : solveurs directs et iteratifs, decentrement, VF et
        EFMH, implicte explicite krank-Nicholson, mass lump

   Remarque

   TRANSGEN remplace DARCYTRA pour le transport, DARCYTRA reste pour la resolut
   de l'equation de DARCY. Les personnes qui tiennent a utiliser des VF
   pour resoudre DARCY peuvent utiliser TRANSGEN en mettant une porosite
   nulle (annule le terme en temps) et une convection nulle.

Operandes (a mettre dans TABLE) :

 |  |
 | Indice  Contenu  |
 |  |
 |  |
 |------------------------------------------------  |
 |Donnees physiques, geometriques et materielles :  |
 |------------------------------------------------  |
 |  |
 |'MODELE'  Objet modele (MMODEL cree par MODE) DARCY  |
 |  |
 |'CARACTERISTIQUES' Donnees physiques et materielles :  |
 |  diffusivite effective - CHAMPOINT de COMPOSANTES  |
 |  K11 K21 K22 K31 K32 K33 au centre des elements  |
 |  |
 |'POROSITE'  Valeur de la porosite (Type Champoint, Comp  |
 |  'SCAL', ou FLOTTANT) - Defaut 1.  |
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
 |'LANGMUIR'  Quantite maximale 'Fsat' adsorbee sur le solide  |
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
 |  l'indice 'COEF_RETARD' contient le coefficient  |
 |  K ramene a une unite de volume de fluide.  |
 |  - Non disponible pour l'instant -  |
 |  |
 |'LIMITE_SOLUBILITE' Limite de solubilite (Type chpoin), composante
 |  identique a la concentration  |
 |  si absente pas de precipitation dissolution  |
 |  |
 |'COEF_DISSOLUTION' Coef. de dissolution (Type CHPO Centre, Comp  |
 |  'SCAL'). Tel que dC/dt = Coef * (Csat - C)  |
 |  Si absent pas de dissolution precipitation  |
 |  |
 |'CONVECTION'  vitesse au face. C'est le debit integre aux faces  |
 |  multiplie par la normale sortante de l'element  |
 |  et divise par la longueur de la face.  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## TRANSIT0 [Thermique Resolution] (proc)
Procedure TRANSIT0

Objet :

Cette procedure est appelee par la procedure THERMIC.

## TRANSIT1 [Thermique Resolution] (proc)
Procedure TRANSIT1

Objet :

Cette procedure est appelee par la procedure THERMIC.

## TRANSIT2 [Thermique Resolution] (proc)
Procedure TRANSIT2

Objet :

Cette procedure est appelee par la procedure THERMIC.

## TRANSIT3 [Thermique Resolution] (proc)
Procedure TRANSIT3

Objet :

Cette procedure est appelee par la procedure THERMIC.

## TRANSLIN [Thermique Resolution] (proc)
T R A N S L I N

RESOLUTION D'UN PROBLEME DE THERMIQUE TRANSITOIRE LINEAIRE
METHODE A UN PAS DE TEMPS ( THETA SCHEMA )

PROCEDURE APPELEE PAR PASAPAS : STAB = TRANSLIN ETAB

ETAB, TABLE CONTENANT EN ENTREE :

INDICE 'INITIAL(1)' CHAMP DE TEMPERATURE INITIAL AU PAS 0
INDICE 'MOD_THE' OBJET MODELE THERMIQUE
INDICE 'MOD_CON' OBJET MODELE CONVECTION
INDICE 'BLOCAGES_THERMIQUES' MATRICE DE BLOCAGE
INDICE 'MAT_THE' OBJET MATERIAU THERMIQUE.
INDICE 'MAT_CON' OBJET MATERIAU CONVECTION
INDICE 'CHARGEMENT' CHARGEMENT DECRIVANT LES
        VALEURS DES VARIABLES EXTERNES (EX: TE,
        FLUX,TEMPERATURES IMPOSEES ,...)
INDICE 'TEMPS0' TEMPS INITIAL (CORRESPOND A INITAL(1))
INDICE 'TEM_CALC' LISTREEL : TEMPS DES RESULTATS A CALCULER
INDICE 'RELAXATION_THETA' VALEUR DU COEFFICIENT DE RELAXATION
        (VALEUR PAR DEFAUT 0.5)
INDICE 'SOUS-RELAXATION' VALEUR DU COEFF. DE SOUS-RELAXATION
        (VALEUR PAR DEFAUT 0.5)

ETAB, TABLE CONTENANT EN SORTIE

INDICE INITIAL(2) DERNIER CHAMP DE TEMPERATURE CALCULE

## TRANSNON [Thermique Resolution] (proc)
    T R A N S N O N

RESOLUTION D'UN PROBLEME DE THERMIQUE TRANSITOIRE NON-LINEAIRE
METHODE A UN PAS DE TEMPS ( THETA SCHEMA )

PROCEDURE APPELEE PAR PASAPAS : STAB = TRANSNON ETAB

ETAB, TABLE CONTENANT EN ENTREE :

INDICE 'INITIAL(1)' CHAMP DE TEMPERATURE INITIAL AU PAS 0
INDICE 'RAYONNEMENT' LOGIQUE VALANT VRAI POUR UNE CONDITION
        DE RAYONNEMENT
INDICE 'EMISSIVITE' MCHAML DECRIVANT LES FACTEURS D'EMISSIVITE
        NOM DE LA COMPOSANTE : EMIS
INDICE 'CELSIUS' LOGIQUE VALANT VRAI SI L'UNITE EST LE
        DEGRE CELSIUS (CAPITAL SI RAYONNEMENT)
INDICE 'MOD_THE' OBJET MODELE THERMIQUE
INDICE 'MOD_CON' OBJET MODELE CONVECTION
INDICE 'BLOCAGES_THERMIQUES' MATRICE DE BLOCAGE
INDICE 'MAT_THE' OBJET MATERIAU THERMIQUE.
        CE CHAMP PEUT AVOIR DES COMPOSANTES DE
        TYPE FLOTTANT OU EVOLUTION (ABS-ORD).
        ORD : VALEUR DE LA COMPOSANTE CONCERNE POUR
        LA VALEUR ABS.
INDICE 'MAT_CON' OBJET MATERIAU CONVECTION
INDICE 'CHARGEMENT' CHARGEMENT DECRIVANT LES
        VALEURS DES VARIABLES EXTERNES (EX: TE,
        FLUX,TEMPERATURES IMPOSEES ,...)
INDICE 'PHASE' TABLE TAB1 POUR L'OPERATEUR CAPACITE
INDICE 'TEMPS0' TEMPS INITIAL (CORRESPOND A INITAL(1)
INDICE 'TEM_CALC' LISTREEL : TEMPS DES RESULTATS A CALCULER
INDICE 'RELAXATION_THETA' VALEUR DU COEFFICIENT DE RELAXATION
        (VALEUR PAR DEFAUT 0.5)
INDICE 'SOUS_RELAXATION' VALEUR DU COEFF. DE SOUS-RELAXATION
        (VALEUR PAR DEFAUT 0.5)
INDICE 'CRITERE' VALEUR DU CRITERE DE FIN D'ITERATION
        (VALEUR PAR DEFAUT 10E-5)
INDICE 'MAXITERATION' NOMBRE MAXIMUM D'ITERATIONS AUTORISEES
INDICE PROJECTION LOGIQUE VALANT VRAI SI COUPLAGE ET SI LE
        MAILLAGE DE LA MECANIQUE ET DE LA THERMIQUE
        EST DIFFERENT

ETAB, TABLE CONTENANT EN SORTIE

INDICE INITIAL(2) DERNIER CHAMP DE TEMPERATURE CALCULE
INDICE ERREUR DRAPEAU D'ERREUR
INDICE TEM_SAUV DERNIER TEMPS CALCULE
INDICE RAYONNEMENT INFORMATIONS SUR LE RAYONNEMENT
        EVENTUELLEMENT REACTUALISEES

## TRC [—] (proc)
    Procedure TRC

    TRC MOD1 MAT1 TINI TFIN LRE1 MOT1 (FLOT1) ;

    Objet :

  Cette procedure permet de calculer un diagramme TRC a partir d'un
  modele metallurgique.

| Entrees | Description  | Type  |
| MOD1  |Modele de formulation METALLURGIQUE  | MMODEL  |
| MAT1  |Caracteristiques du Modele METALLURGIQUE | MCHAML  |
| TINI  |Temperature initiale  | FLOTTANT |
| TFIN  |Temperature finale  | FLOTTANT |
| LRE1  |Liste des vitesses de refroidissement  | LIRTREEL |
| MOT1  |Phase consommee au refroidissement  | MOT  |
| FLOT1  |Seuil de detection d'une transformation  | FLOTTANT |
|  |de phase (0.005 par defaut)  |  |

## TRES [Mecanique Resolution]
    Operateur TRESCA
    ---------------- PRIN CALP

      CHAM2 = TRES MODL1 SIG1 (CAR1) (MOT1) ;

    Objet :

    L'operateur TRESCA calcule la contrainte equivalente de Tresca
d'un champ de contraintes.

      Commentaire :

      SIG1 : champ de contraintes (type MCHAML, sous-type
        CONTRAINTES)

      CAR1 : champ de caracteristiques geometriques necessaire pour
        les coques minces (type MCHAML, sous-type
        CARACTERISTIQUES)

      MOT1 : mot-cle qui indique pour les coques oº on veut calculer
        les contraintes :

        'SUPE' : en peau superieure
        'MOYE' : sur la surface moyenne ( par defaut )
        'INFE' : en peau inferieure

      CHAM2 : contrainte equivalente de Tresca (type MCHAML, sous-type
        SCALAIRE)

      Remarque :

    Dans le cas des coques minces, on calcule a partir des contraintes
generalisees une contrainte de Tresca vraie.

## TRIA [Maillage Autres]
    Operateur TRIANGULATION
    ----------------------- RAFT

   L'operateur TRIANGULATION s'utilise dans les cas suivants :

   |  1ere possibilite  |

    SURF1 = TRIA LIG1 (N1) ;

    Objet :

    L'operateur TRIANGULATION construit un maillage d'un domaine
plan defini par sa frontiere (objet LIG1). Aucun noeud n'est
ajoute sur la frontiere, en revanche des noeuds sont ajoutes a
l'interieur du domaine pour ameliorer la forme des triangles.
Le nombre de noeuds generes est minimum, il peut etre encore
limite en fixant la valeur de N1.

    Commentaire :

    LIG1 : objet de type MAILLAGE. Il est constitue d'une ou
plusieurs lignes fermees. Leur orientation et leur ordre peuvent
etre quelconque. LIG1 peut contenir des aretes pendantes et des
lignes ouvertes .Ce sont des aretes imposees que l'on retrouvera
dans le maillage resultant (SURF1). Ces aretes doivent etre a
l'interieur du domaine.

    N1 : objet de type ENTIER. C'est le nombre maximum de
noeuds que doit contenir SURF1. Il est superieur ou egal au
nombre de noeuds de LIG1.

    Remarque :

    L'operateur TRIANGULATION genere peu de triangles ; il est
deconseille d'utiliser directement le resultat pour un calcul
elements finis. En revanche on peut raisonnablement evaluer la
fonction "taille souhaitee" et raffiner le maillage avec l'opera-
teur RAFT.

   La densite affectee a chaque noeud du maillage est la densite
courante(voir DENS).Elle peut etre positive ou nulle(non fixee).

   TRIANGULATION ne fonctionne que pour des elements lineaires :
LIG1 doit etre compose de SEG2 et SURF ne contient que des TRI3.

   |  2eme possibilite  |

    MAIL2 = TRIA MAIL1 ('CONV') (FLOT1) ;

    Objet :

    L'operateur TRIANGULATION construit la triangulation de
    Delaunay d'un ensemble de points.

    Commentaire :

    MAIL1 : objet MAILLAGE, forme d'elements de type POI1.

    'CONV' : mot clef permettant de verifier la convexite de la
        triangulation. La taille de la boite de triangulation
        utilisee est augmentee si besoin.

    FLOT1 : objet FLOTTANT permettant de definir une taille de maille
        cible a respecter pour la triangulation. De nouveaux
        noeuds sont ajoute a l'ensemble de points initial.

    MAIL2 : objet MAILLAGE, triangulation de Delaunay des points
        de MAIL1, constitue d'elements TRI3 (TET4) en 2D (3D).

   |  3eme possibilite  |

    MAIL1 = 'TRIA' 'TOPO' MAIL2  | ('AJNO') | (TAB1) ;
        |  'NOAJ'  |

    Objet :

    L'operateur TRIANGULATION genere un maillage de simplex (triangles
    ou tetraedres) par un algorithme de maillage topologique du a T.
    Coupez et al.

    Commentaire :

     MAIL1 : maillage genere (type MAILLAGE)

     MAIL2 : bord du maillage a generer (type MAILLAGE)

     TAB1 : objet optionnel de type TABLE dont les indices sont des
        parametres d'entree ou de sortie du mailleur
        (voir notice MAILTOPO pour plus de details)

    Remarque :

    Si le mot-clef 'AJNO' (par defaut) est donne, le mailleur peut
    generer de nouveaux noeuds.
    Si le mot-clef 'NOAJ' est donne, le mailleur ne genere pas de
    nouveaux noeuds.

    Limitation :

    MAIL2 doit etre connexe

## TRIE [Post-traitement Analyse]
Operateur TRIE

Syntaxe 1 : trie des elements en fonction des level set

   MCHAM1 |  | =  TRIE  MO1 CHP1 CHP2 |  | ;
        |  |  | 'SAUT' |
        | REL1 |  | 'DESE' |

Objet :

L'operateur TRIE trie les elements d'un modele xfem et sort un
MCHAML d'enrichissement en fonction de la valeur des level set.
En presence du mot 'SAUT', l'approximation du deplacement est
seulement H-enrichie, la pointe de fissure doit toujours etre
sur un bord de l'element.
En présence du mot 'DESE', l'enrichissement "pointe de fissure"
est progressivement abandonné : celui qui correspond à la fissure
à l'instant n-1 est retiré du modèle, celui de l'instant n est
mis à 0 (via REL1), et celui de l'instant n+1 (actuel) est ajouté.

Commentaire :

MO1 (E/S) : objet MMODEL dont les elements sont a trier /
        objet MMODEL avec les elements tries

CHP1,CHP2 (E) : les deux CHPOINT level set servant a
        trier les elements

MCHAM1 (S) : objet MCHAML d'enrichissement.

'SAUT' : mot cle relatif à l'option sans enrichissement de type
        "pointe de fissure".

'DESE' : mot cle relatif à l'option de désenrichissement progressif
        des fonctions de type "pointe de fissure".

Syntaxe 2 : trie des elements en fonction d'un enrichissement donne

   TRIE MO1 MCHAM1;

Objet :

L'operateur TRIE trie les elements d'un modele xfem en fonction
d'un MCHAML d'enrichissement fourni (ayant ete prealablement
construit avec la syntaxe 1).
Cela permet de re-construire le modele a la configuration associee
a MCHAM1.

Commentaire :

MO1 (E/S) : objet MMODEL dont les elements sont a trier /
        objet MMODEL avec les elements tries

MCHAM1 (E) : objet MCHAML d'enrichissement.

## TRTRAJEC [Post-traitement Affichage] (proc)
Procedure TRTRAJEC

    GEO1 = TRTRAJEC TAB1 ;

    Objet
    Cette procedure genere un maillage de SEG2 a partir de la table
    resultat de l'operateur TRAJ.
    Ceci de facon a pouvoir tracer les trajectoires.

    Commentaires

    GEO1 est un maillage de SEG2
    TAB1 est la table issue de l'operateur TRAJ

## TSCA [Multi-physique Multi-physique]
    Operateur TSCA

    SYNTAXE - EQEX Cf operateur EQEX

     1/ Formulation non conservative
a/
    'OPER' 'TSCA' rocp un lambda s 'INCO' 'TN' :

b/
    'OPER' 'TSCA' alpha un s 'INCO' 'TN' :
    'OPER' 'TSCA' alpha un s nut st 'INCO' 'TN' :

     2/ Formulation conservative

    'OPER' 'TSCA' lambda 'UN' S tn 'INCO' 'HN' :
    'OPER' 'TSCA' lambda 'UN' S tn mut st 'INCO' 'HN' :

    Objet :

  Cet operateur discretise une equation de transport diffusion
  + source et calcule l'increment pour un algorithme explicite.
   Suivant l'option les equations sont traites sous forme
  conservative ou non conservative.

     1/ Formulation non conservative
a/
  rocp dT/dt + u Grad T = lambda Lapl T + s (s=S)

b/
  dT/dt + u Grad T = alpha Lapl T + s (s=S/(ro cp))

     2/ Formulation conservative

  dh/dt + Div ( u h ) = (lambda + mut/st) Lapl(T) + S

    Commentaires :

     rocp, alpha capacite calorifique, diffusivite thermique
     lambda conductivite thermique
        FLOTTANT ou CHPOINT SCAL CENTRE ou CHPOINT SCAL SOMMET ou MOT
     s,S densite de source volumique (s=S/ro cp)
        POINT ou CHPOINT SCAL CENTRE ou MOT
     nut,(mut) viscosite cinematique,(dynamique) turbulente
        CHPOINT SCAL CENTRE ou MOT
     st Prandtl turbulent
        FLOTTANT ou MOT
     un Champ de vitesse transportant
        CHPOINT VECT SOMMET ou MOT
     tn,hn Champ de temperature ou d'enthalpie
        CHPOINT SCAL SOMMET ou MOT

 Un coefficient de type MOT indique que l'operateur va chercher le
 coefficient dans la table INCO a l'indice MOT.

    Options : (EQEX)

 La discretisation des termes de convection peut etre :

 centree OPTION CENTREE
 decentree OPTION SUPG
 decentree avec capture de choc OPTION SUPGCC Option par defaut
 tenseur visqueux (ordre 2 en temps) OPTION TVISQ

 Formulation non conservative OPTION NOCONS Option par defaut
 Formulation conservative OPTION CONS

 Formulation EFM1 OPTION EFM1 Option par defaut

## TYPE [Langage Base]
    Operateur TYPE

    MOT1 = TYPE OBJET1 ;

    Objet :

    L'operateur TYPE permet de connaitre le type d'un objet OBJET1.
Le resultat MOT1 est un objet de type MOT, il contient 8 caracteres .

## T_IPOL [Fluides Resolution] (proc)
  Procedure T_IPOL

  OBJET :

Procedure appelee uniquement par le procedure ENCEINTE.

## T_PITETA [Mecanique Rupture] (proc)
    Procedure T_PITETA

    Objet :

   Cette procedure est utilisee par la procedure G_THETA. Elle
permet de fabriquer un "champ theta".

## UNILATER [Mecanique Resolution] (proc)
Procedure UNILATER

Objet :

Cette procedure ne peut pas etre appelee par l'utilisateur.

Elle sert aux appuis unilateraux.

## UNIQ [Langage Objets]
   Operateur UNIQUE

   RES1 ... RESi ... RESn = UNIQUE OBJ1 ... OBJi ... OBJn
        (FLOT1) ('NOCA')('ORDO') ;

   Objet :

   Supprime les doublons dans un objet.
   RESi est du meme type que OBJi.

>> CAS DES OBJETS DE TYPE 'LISTENTI'

   Supprime les doublons dans OBJi de type LISTENTI.

>> CAS DES OBJETS DE TYPE 'LISTREEL'

   Supprime les doublons dans OBJi de type LISTREEL.

   Pour detecter que deux nombres reels sont egaux, on compare leur
   difference (en valeur absolue) a un nombre juge suffisamment petit.
   Par defaut, on utilise un critere RELATIF base sur la precision
   machine. L'utilisateur peut imposer une valeur ABSOLUE pour ce
   critere via la donnee de FLOT1 (type FLOTTANT).

>> CAS DES OBJETS DE TYPE 'LISTMOTS'

   Supprime les doublons dans OBJi de type LISTMOTS.

   Par defaut, l'identification de doublons est sensible a la casse,
   ce qui signifie que l'on distingue les majuscules des minuscules.
   On peut indiquer a la directive que l'on souhaite plutot faire une
   elimination insensible a la casse grace au mot-cle 'NOCA'.

>> CAS DES OBJETS DE TYPE 'MAILLAGE'

   Supprime les doublons dans OBJi de type MAILLAGE.

   Deux elements sont egaux si ils contiennent les memes noeuds même
   si ils sont de couleurs différentes.

   En presence du mot cle ORDO, il faut de plus que les noeuds soient
   a la meme position dans l'element.

>> REMARQUE

   Quand des doublons sont detectes, seule la premiere occurrence
   est conservee, toutes les autres sont supprimees.

## UNPAS [Mecanique Resolution] (proc)
procedure UNPAS

Cette procedure est appelee par PASAPAS, elle calcule un pas
mecanique.

## UPDAEFMH [Fluides Resolution] (proc)
       Operateur UPDAEFMH

 ATTENTION La vitesse est optionnelle, L'ordre est important
 et les types d'arguments qui se suivent aussi pour tester leur
presence

 APPELE PAR TRANGEOL - PAS POUT UTILISATEUR

  |-----------------------------------------------------------------|
  | Phrase d'appel (en GIBIANE)  |
  |-----------------------------------------------------------------|
  |  |
  |SMTr MatrTr TbDarTra MassEFMH Difftot = UPDAEFMH MoDARCY Porosite|
  |  MateDiff difftot ChPSour cini tcini deltat  |
  |  (Qface) nomespec nbespece nbsource LMLump  |
  |  DECENTR massEFMH | mattr tbdartra TABMODI;  |
  |  | mattm  |
  |-----------------------------------------------------------------|
  | Generalites : UPDAEFMH construit la matrice de discretisation  |
  |  du probleme de transport convection-diffusion pour|
  |  le premier pas de tps d'un algorithme transitoire.|
  |  Le second membre et les Conditions limites de flux|
  |  sont pris en compte.  |
  |  RESTE TCINI, DECENTR et TERME LIN  |
  |-----------------------------------------------------------------|
  |  |
  |-----------------------------------------------------------------|
  |  ENTREES  |
  |-----------------------------------------------------------------|
  | MoDARCY  : modele Darcy.  |
  |  |
  | Porosite : champ par elements de composante 'CK'  |
  |  |
  | MateDiff : Tenseur de diffusion  (type iso, ..) champ par  |
  |  points de composante 'K' en isotrope, 'K11', 'K21',  |
  |  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
  |  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
  |  |
  | Diffdisp : Tenseur de dispersion  (type iso, ..) champ par  |
  |  points de composante 'K' en isotrope, 'K11', 'K21',  |
  |  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
  |  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
  |  |
  | ChPSour  : Champ par points des sources volumiques par unite de |
  |  temps (support maillage centre). Composante ??????  |
  |  |
  | Cini  : Concentration initiale, CHPOINT centre.  |
  |  Composante 'H'.  |
  |  |
  | Tcini  : Trace de concentration aux faces (eventuellement a  |
  |  plusieurs composantes (especes)  |
  |  |
  | Deltat  : Pas de temps  |
  |  |
  | Qface  : vitesse aux faces, CHPO face de composantes Vx, Vy  |
  |  en 2d et Vx, Vy, Vz en 3d. Il s'agit plus exatement  |
  |  de (V.n)n, c'est a dire de la composante normale de  |
  |  la vitesse aux faces. ???????? (je pressens que  |
  |  castem va sortir des flux, cad integres sur surfaces)|
  |  |
  | nomespec : liste des noms de composante des especes dans Cini  |
  |  |
  | nbespece : nombre de composante de Cini, soit nombre d'especes  |
  |  |
  | nbsource : nombre de composantes du terme source qd X especes  |
  |  |
  | LMLump  : Logique. Si vrai on effectue une condensation de  |
  |  masse de la matrice EFMH  |
  |  |
  | DECENTR  : Logique. Vrai veut dire schemas decentres et faux  |
  |  veut dire schema convectif centre.  |
  |  |
  | MatTm  : matrice globale sur les traces. MATRIK en entree  |
  |  sort MATRIK si non modifiee, RIGIDITE sinon  |
  |  Soit on rentre cet argument soit le suivant Mattr  |
  |  |
  | MatTr  : idem mais rigidite en entree on ressort cette matrice|
  |  inchangee si les options MATMODI indiquent aucune  |
  |  modif. Optionnel. On rentre Mattm si absent.  |
  |  |
  | TbDarTra : table Darcy transitoire utilisee par MHYB, SMTP ...  |
  |  |
  | TABMODI  : table contenant des logiques indiquant la necessite  |
  |  ou non de reclalculer certains termes.  |
  |  'POROSITE' : VRAI si le coefficient devant D/DT  |
  |  (porosite) est modifie depuis le dernier|
  |  appel  |
  |  'DELTAT'  : VRAI si le pas de tps a change  |
  |  'CONVECTI' : VRAI si la vitesse a change  |
  |  'COEF_LIN' : VRAI si le coef en facteur de C a change|
  |  'DIFFUSI'  : VRAI si les diffusivites ont change  |
  |  |
  | CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
  |  Chpoint a n composantes contenant les conditions aux |
  |  limites de Neumann et Dirichlet par espece.  |
  |  |
  |  |
  |-----------------------------------------------------------------|
  |  ENTREES-SORTIES  |
  |-----------------------------------------------------------------|
  |  |
  | MassEFMH : matrice elementaire EFMH  |
  |  |
  | Remarque  |
  | --------  |
  | On a toujours interet a rentrer Mattm si on l'a et qu'il n'y a  |
  | pas de modification, afin de conserver les factorisations LU  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## UPDAVF [Fluides Resolution] (proc)
       Operateur UPDAVF

ATTENTION La vitesse est optionnelle, L'ordre est important
et les types d'arguments qui se suivent aussi pour tester leur
presence

APPELE PAR TRANGEOL. PAR POUR UTILISATEUR

 |-----------------------------------------------------------------|
 | Phrase d'appel (en GIBIANE)  |
 |-----------------------------------------------------------------|

        SMTr Mattt Difftot Mctot Mdiff Nouvmat = UPDAVF
        MoDARCY Porosite Matediff Diffdisp ChPSour
        DeltaT Cini TetaDiff TetaConv
        Qface nomespec nbespece nbsource
        Matot Jaco Mctot Mdiff Mpor TABMODI CHCLIM ;

 |-----------------------------------------------------------------|
 | Generalites : MATTVF construit la matrice de discretisation  |
 |  du probleme de transport convection-diffusion pour|
 |  le premier pas de tps d'un algorithme transitoire.|
 |  Le second membre et les Conditions limites de flux|
 |  sont pris en compte.  |
 |-----------------------------------------------------------------|
 |  |
 |-----------------------------------------------------------------|
 |  ENTREES  |
 |-----------------------------------------------------------------|
 | MoDARCY  : modele Darcy.  |
 |  |
 | Porosite : champ par elements de composante 'CK'  |
 |  |
 | MateDiff : Tenseur de diffusion  (type iso, ..) champ par  |
 |  points de composante 'K' en isotrope, 'K11', 'K21',|
 |  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
 |  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
 |  |
 | Diffdisp : Tenseur de dispersion  (type iso, ..) champ par  |
 |  points de composante 'K' en isotrope, 'K11', 'K21',|
 |  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
 |  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
 |  |
 | ChPSour  : Champ par points des sources volumiques par unite de |
 |  temps (support maillage centre). Composante ??????  |
 |  |
 | Cini  : Concentration initiale, CHPOINT centre.  |
 |  Composante 'H'.  |
 |  |
 | Deltat  : Pas de temps  |
 |  |
 | Qface  : vitesse aux faces, CHPO face de composantes Vx, Vy  |
 |  en 2d et Vx, Vy, Vz en 3d. Il s'agit plus exatement  |
 |  de (V.n)n, c'est a dire de la composante normale de  |
 |  la vitesse aux faces. ???????? (je pressens que  |
 |  castem va sortir des flux, cad integres sur surfaces)|
 |  |
 | nomespec : liste des noms de composante des especes dans Cini  |
 |  |
 | nbespece : nombre de composante de Cini, soit nombre d'especes  |
 |  |
 | nbsource : nombre de composantes du terme source qd X especes  |
 |  |
 | Matot  : matrice globale de discretisation en VF  |
 |  |
 | Jaco  : matrice globale de discretisation en VF pour le probleme
 |  stationnaire

 | Mpor  : matrice globale de discretisation en VF pour le probleme
 |  stationnaire
 |  |
 | Mchamt  : Coef permettant de calculer le flux total
 |  |
 | Mchamt1  : Coef permettant de calculer le flux diffusif
 |  |
 |  |
 | TABMODI  : table contenant des logiques indiquant la necessite  |
 |  ou non de reclalculer certains termes.  |
 |  'POROSITE' : VRAI si le coefficient devant D/DT  |
 |  (porosite) est modifie depuis le dernier|
 |  appel  |
 |  'DELTAT'  : VRAI si le pas de tps a change  |
 |  'CONVECTI' : VRAI si la vitesse a change  |
 |  'COEF_LIN' : VRAI si le coef en facteur de C a change|
 |  'DIFFUSI'  : VRAI si les diffusivites ont change  |
 |  |
 | CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
 |  Chpoint a n composantes contenant les conditions aux |
 |  limites de Neumann et Dirichlet par espece.  |
 |  |
 |  |
 |-----------------------------------------------------------------|
 |  ENTREES-SORTIES  |
 |-----------------------------------------------------------------|
 |  |
 | Difftot  : Coefficient de diffusion totale, integre decentrement|
 |  |
 |  |
 |-----------------------------------------------------------------|
 |  SORTIES  |
 |-----------------------------------------------------------------|
 |  |
 |  |
 | RESI  : second membre  |
 |  |
 | Matot  : matrice globale de discretisation en VF  |
 |  |
 | Difftot  : Coefficient de diffusion totale, integre decentrement|

 | Mpor  : matrice globale de discretisation en VF pour le probleme
 |  stationnaire
 |  |
 | Mchamt  : Coef permettant de calculer le flux total
 |  |
 | Mchamt1  : Coef permettant de calculer le flux diffusif
 |  |
 |  |
 |-----------------------------------------------------------------|

## USACCE [Mecanique Usure] (proc)
Procedure USACCE
---------------- USDEPL USEXPL USIMPL USINIB
        USPOST USTMPS USURE

        REE1 = USACCE TAB1 ;

 [Q. Caradec thesis]

 Objet :

   Procedure qui determine le facteur de saut de cycle a appliquer au
   taux d'usure calcule pour un cycle. Ce facteur peut etre constant
   tout au long du calcul ou variable. Dans ce dernier cas, sa valeur
   depend de la vitesse d'elargissement de la zone usee.

 Commentaires :

   REE1 : Objet de type REEL donnant le facteur de saut de cycle.

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USEXPL et USIMPL.
 Elle ne doit pas etre appelee directement.

## USADAC [Mecanique Usure] (proc)
Procedure USADAC
---------------- USDEPL USEXPL USIMPL USINIB
        USPOST USTMPS USURE

        PROG1 REE1 = USADAC PROG2 PROG3 ;

 [Q. Caradec thesis]

 Objet :

   Procedure qui determine, a un cycle donne, le facteur de saut de
   cycle. La largeur de la zone usee, notee L, en fonction du nombre de
   cycle, note N, est supposee s'exprimer sous la forme :

        L(N) = L0 + [L1 '*' N '**' L2]

   L1 et L2 sont reevalues a chaque nouveau cycle via l'operateur LEVM.
   Cette procedure calcule les valeurs de L(N) et de ses derivees
   partielles pour chaque cycle. Il s'agit de la procedure transmise
   a LEVM.

 Commentaires :

   PROG1 : Objet de type LISTREEL donnant les valeurs des parametres
        L1 et L2 proposes par l'operateur LEVM.

   REE1 : Objet de type REEL donnant la valeur final du critere de
        l'operateur LEVM.

   PROG2 : Objet de type LISTREEL donnant les cycles d'usure calcules
        (abscisses de la suite de points a approximer).

   PROG3 : Objet de type LISTREEL donnant les largeurs de zone usee a
        chaque cycle (ordonnees de la suite de points a approximer)

 Cette procedure est appelee par USACCE.
 Elle ne doit pas etre appelee directement.

## USCALC [Mecanique Usure] (proc)
Procedure USCALC
---------------- USDEPL USEXPL USIMPL USINIB
        USPOST USTMPS USURE

        USCALC TAB1 ;

 Objet :

   Procedure qui determine, pour chaque noeud du maillage se trouvant
   a l'indice 'SURFACE_APPLICATION', la pression de contact, le
   cisaillement, le glissement et l'energie dissipee.
   Lorsque tous les instants du cycle sont calcules, elle construit le
   cycle d'usure (force tangentielle en fonction du deplacement). Ce
   dernier est utilise pour determiner si les pas de temps doivent etre
   reevalues ou non.

   (Voir ci-dessous pour les indices de la table concernes)

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USURE.
 Elle ne doit pas etre appelee directement.

Resultat conserve en fin de calcul
  'CYCLE_DE_FRETTING' : EVOLUTION tracant la reaction tangentielle en
        fonction du deplacement impose.

## USDEPL [Mecanique Usure] (proc)
Procedure USDEPL
---------------- USCALC USEXPL USIMPL USINIB
        USPOST USTMPS USURE

        USDEPL TAB1 ENT1 ;

 Objet :

   Procedure qui actualise les coordonnees du maillage a partir du champ
   contenu a l'indice 'USURE_CYCLE'.

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

   ENT1 : Objet de type ENTIER donnant le numero de la boite a
        considerer.

 Cette procedure est appelee par USEXPL et USIMPL.
 Elle ne doit pas etre appelee directement.

## USEXPL [Mecanique Usure] (proc)
Procedure USEXPL
---------------- USDEPL USDEPL USIMPL USINIB
        USPOST USTMPS USURE

        USEXPL TAB1 ;

 Objet :

   Procedure qui applique l'usure selon un schema explicite :

        h[k+1] = h[k] + deltaN * DH[k]

   Avec
    - h[k+1] : l'usure au cycle [k+1]
    - h[k] : l'usure au cycle [k]
    - deltaN : facteur de saut de cycle (voir USACCE)
    - DH[k] : taux d'usure au cycle [k] (voir USCALC)

   Une fois tous les instants du cycle [k] calcule, le maillage est
   deplace de h[k+1] et le cycle suivant demarre.

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USURE.
 Elle ne doit pas etre appelee directement.

## USIMPL [Mecanique Usure] (proc)
Procedure USIMPL
---------------- USDEPL USDEPL USEXPL USINIB
        USPOST USTMPS USURE

        USIMPL TAB1 ;

 [Q. Caradec thesis]

 Objet :

   Procedure qui applique l'usure selon un schema implicite :

        h[k+1] = h[k] + deltaN * DH[k+1]

   Avec
    - h[k+1] : l'usure au cycle [k+1]
    - h[k] : l'usure au cycle [k]
    - deltaN : facteur de saut de cycle (voir USACCE)
    - DH[k+1] : taux d'usure au cycle [k+1] (voir USCALC)

   Un schema iteratif est implemente et a chacune des iterations,
   notee i, la convergence est testee selon :

        h[k] + deltaN * DH[k+1]{i} - h[k+1]{i} < crit

   Avec
    - crit : critere de convergence

   Une fois ce critere satisfait, le cycle suivant demarre.

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USURE.
 Elle ne doit pas etre appelee directement.

## USINIB [Mecanique Usure] (proc)
Procedure USINIB
---------------- USDEPL USDEPL USEXPL USEXPL
        USPOST USTMPS USURE

        USINIB TAB1 ;

 Objet :

   Procedure d'initialisation des tables de stockage des resultats.

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USURE.
 Elle ne doit pas etre appelee directement.

## USPOST [Mecanique Usure] (proc)
Procedure USPOST
---------------- USDEPL USDEPL USEXPL USEXPL
        USINIB USTMPS USURE

        USPOST TAB1 ENT1 ;

 Objet :

   Procedure de post-traitement appelee a la fin de chaque cycle
   d'usure. Elle calcule l'energie dissipee durant le cycle numerique
   (integration du cycle de fretting), le volume use durant beta cycles
   numeriques (integration du profil d'usure) et le nombre de cycles
   reels equivalent.

   (Voir ci-dessous pour les indices de la table concernes)

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

   ENT1 : Objet de type ENTIER donnant le numero de la boite a
        considerer.

 Cette procedure est appelee par USEXPL et USIMPL.
 Elle ne doit pas etre appelee directement.

Resultats conserves en fin de calcul

  Indices contenant un objet de type LISTREEL donnant pour chaque
  cycle calcule :
   'PRESSION_MAX_CYCLE' : la valeur de pression max.
   'CISAILLEMENT_MAX_CYCLE' : la valeur de cisaillement max.
   'ENERGIE_DISSIPEE_CYCLE' : l'energie dissipee
   'VOLUME_USE_CYCLE' : le volume use
   'PROF_USEE_MAX_CYCLE' : la profondeur usee max.
   'LARGEUR_CONTACT_CYCLE' : la largeur de la zone de contact

  Indices contenant un objet de type TABLE ou pour chaque cycle
  calcule, un objet de type CHPOINT fournit :
   'PRESSION_MOYENNE_CYCLE' : la pression moyenne
   'CISAILLEMENT_MOYEN_CYCLE' : le cisaillement moyen
   'GLISSEMENT_CYCLE' : le glissement

  Indices contenant un objet de type EVOLUTION :
   'PRESMAX_VS_CYCLES' : pression max en fonction du cycle
   'CISAMAX_VS_CYCLES' : cisaillement max en fonction du cycle
   'ED_CYCLE_VS_CYCLES' : energie dissipee a chaque cycle en fonction
        du cycle
   'ED_TOT_VS_CYCLES' : energie dissipee totale en fonction du cycle
   'V_USE_TOT_VS_CYCLES' : volume use total en fonction du cycle
   'V_USE_TOT_VS_ED_TOT' : volume use total en fonction de l'energie
        dissipee

## USPROF [Mecanique Usure] (proc)
Procedure USPROF
---------------- USINIB USPOST USTMPS USURE

        TAB2 = USPROF TAB1 ENT1 ;

 Objet :

   Procedure qui calcule le profil d usure a appliquer selon

        DeltaH = alpha * beta * phi

   Avec
    - alpha : valeur se trouvant a l'indice 'COEFFICIENT_USURE'
    - beta : valeur se trouvant a l'indice 'FACTEUR_ACCELERATION'
    - phi : densite surfacique d'energie dissipee (voir USCALC)

   (Voir ci-dessous pour les indices de la table concernes)

 Commentaires :

   TAB2 : Objet de type TABLE correspondant a la boite d'usure, avec
        les indices correctement initialises

   TAB1 : Objet de type TABLE correspondant a la boite d'usure

   ENT1 : Objet de type ENTIER donnant le numero de la boite a
        considerer

 Cette procedure est appelee par USURE

Resultats conserves en fin de calcul
   'USURE_TOTALE' : CHPOINT contenant les profondeurs usees en chaque
        point du maillage 'SURFACE_APPLICATION'
   En 2D :
     'EVO_USURE_CYCLE' : EVOLUTION donnant pour chaque cycle calcule
        la profondeur usee le long du maillage
        'SURFACE_APPLICATION'

## USTMPS [Mecanique Usure] (proc)
Procedure USTMPS
---------------- USDEPL USDEPL USEXPL USEXPL
        USINIB USPOST USURE

        USTMPS TAB1 ;

 Objet :

   Procedure qui determine la liste d'instants de calcul pour le
   prochain cycle.

 Commentaires :

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

 Cette procedure est appelee par USURE.
 Elle ne doit pas etre appelee directement.

## USURE [Mecanique Usure] (proc)
Procedure USURE
---------------- USDEPL USDEPL USEXPL USEXPL
        USINIB USPOST USTMPS

        TAB2 = USURE TAB1 ;

 Objet :

   Procedure principale pour les calculs d'usure dont le principe est
   le suivant :
   - a chaque instant d'un cycle d'usure, la densite d'energie dissipee
     par frottement est calculee
   - lorsque le dernier instant d'un cycle est atteint, la geometrie
     de la zone usee est actualisee selon un schema explicite ou
     implicite
   Le calcul se poursuit jusqu'a ce que le nombre total de cycles
   souhaite soit calcule.

   Pour faire un calcul d'usure, il faut utiliser la procedure PASAPAS.
   La procedure USURE est la seule procedure a appeler, depuis la
   procedure PERSO1 (voir usure.dgibi).

   Les informations propres a l'usure doivent etre contenues dans une
   table, notee ici BUSURE, stockee a l'indice 'BOITES_USURE' de la
   table de PASAPAS, notee ici TAB1, soit :

        TAB1.'BOITES_USURE' = BUSURE ;

   Les informations a transmettre sont les suivantes :
   - pour les i surfaces a user (i > 0) :

       BUSURE. i .'SURFACE_APPLICATION'
       -> Surface usee (ou sera appliquee l'usure).

       BUSURE. i .'COEFFICIENT_USURE'
       -> Valeur du coefficient d'usure.

       BUSURE. i .'VOLUME_REPARTITION'
       -> Volume sous la surface usee pour "repartir" l'usure.

   - de facon commune aux surfaces a user :
     1/ Informations obligatoires :

       BUSURE.'DONNEES'.'NB_CYCLES'
       -> Nombre de cycles d'usure.

       BUSURE.'DONNEES'.'PERIODE'
       -> Periode d'un cycle d'usure.

       BUSURE.'DONNEES'.'INCREMENTS_CYCLE'
       -> Nombre de pas de temps calcule par cycle d'usure.

       BUSURE.'DONNEES'.'T_DEBUT_USURE'
       -> Temps ou demarre l'usure.
        Si l'indice 'TEMPS_CALCULES' de la table de PASAPAS ne
        contient pas le dernier instant, alors les pas de temps
        seront reevalues a chaque fin de cycle. Ce temps doit
        alors etre un multiple de la periode.

     2/ Informations facultatives :

       BUSURE.'DONNEES'.'ACCELERATION'
       -> Valeur du facteur de saut de cycle.
        Par defaut, vaut 1.

       BUSURE.'DONNEES'.'SAUV_AUTO'
       -> Booleen valant VRAI si on souhaite sauvegarder les resultats
        a chaque fin de cycle. Lorsque cette option est a VRAI,
        l'option ECONOMIQUE de PASAPAS est activee.
        Par defaut, vaut FAUX.

       BUSURE.'DONNEES'.'SCHEMA'
       -> Schema de resolution pour l'usure. Choix entre EXPLICITE et
        IMPLICITE.
        Par defaut, vaut EXPLICITE.

       BUSURE.'DONNEES'.'DELTA_L0'
       -> Valeur d'elargissement de la zone usee souhaitee entre deux
        cycles consecutifs. Utile en cas de facteur de saut de cycle
        variable.
        Par defaut, vaut la taille de maille minimale des i maillages
        'SURFACE_APPLICATION'.

       BUSURE.'DONNEES'.'DN_CYCLES_INIT'
       -> Nombre de cycles a calculer avant de calculer le coefficient
        de saut de cycles variable.
        Par defaut, vaut 10.

 Commentaires :

   TAB2 : Objet de type TABLE correspondant a la table de PASAPAS.

   TAB1 : Objet de type TABLE correspondant a la table de PASAPAS.

## UTIL [Langage Base]
   Directive UTILISATEUR

     UTIL MOT1 MONFICHIER ;

  La directive UTILISATEUR n'est plus utilisee

Les procedures et notices sont maintenant directement lues dans des fichiers
eponymes appartenant aux repertoires specifies par les variables
d'environnement CASTEM_PROCEDUR24 et CASTEM_NOTICE24.

Par defaut et dans l'ordre, ce sont:
Le repertoire courant
Le repertoire ./procedur
Le repertoire d'installation

Exemple de fichier de procedure:

   $$$$ MAPRO1
   DEBPROC MAPRO1 i*.....
   FINPRO J...;

## VALE [Langage Base]
    Operateur VALEUR

    VAL1 = VALEUR MOT1 ;

    Objet :
   | 1ere fonction |

    L'operateur VALE sert a recuperer les valeurs affectees aux options
    generales de calcul (ces valeurs ont ete soit affectees par
    l'intermediaire de la directive OPTION, soit initialisees au debut
    de l'execution).

    Options possibles :

|mot-cle  | resultat(s) possible(s)  |  commentaire  |
| MOT1  | VAL1  |  |
|-------------|----------------------------|-----------------------|
|'ACQU'  | numero unite logique  | fichier d'entree  |
|  |  |  |
|'ASSI'  | nombre d'assistants  | parallélisme  |
|  |  |  |
|'CADR'  | FLOTTANT positif  | Cote du cadre (en cm) |
|  |  |  |
|'COSC'  |  NOIR,BLANC, JAUN  | Couleur fond d'ecran  |
|  |  |  |
|'COUL'  | DEFA,BLEU,ROUG,ROSE,JAUN,  | couleur prédéfinie  |
|  | VERT,TURQ,BLAN,NOIR,AZUR,  |  |
|  | ORAN,VIOL,OCEA,CYAN,OLIV,  |  |
|  | GRIS  |  |
|  |  |  |
|'DEBU'  |  0,1  | en cas d'erreur, on ne!
|  |  | peut pas lister les  |
|  |  | objets internes à la  |
|  |  | procedure  |
|  |  |  |
|'DENS'  |  FLOTTANT positif  | taille de maille par  |
|  |  | defaut (voir aussi  |
|  |  | notice DENS)  |
|  |  |  |
|'DIME'  | 0,1,2,3  | dimension de l'espace |
|  |  |  |
|'DONN'  | numero unite logique  | cartes donnees  |
|  |  |  |
|'ECHO'  | 0,1,2  | echo donnees  |
|  |  |  |
|'ELEM'  | POI1,SEG2,SEG3,TRI3,TRI6,  | element a fabriquer  |
|  | QUA4,QUA8,RAC2,RAC3,CUB8,  |  |
|  | CU20,PRI6,PR15,PYR5,PY13,  |  |
|  | TET4,TE10  |  |
|  |  |  |
|'EPTR'  |  1,2,...,10  | épaisseur du trait  |
|  |  | pour le tracé  |
|  |  |  |
|'ERRE'  | 0,1,2,3  | niveau max d'erreur  |
|  |  | permis  |
|  |  |  |
|'FTRA'  | chaîne de caractères  | Nom du fichier conte- |
|  |  | nant le tracé de type |
|  |  | PostScript ou MIF  |
|  |  | (FrameMaker)  |
|  |  |  |
|'GRAN'  | FLOTTANT  | Plus grande valeur  |
|  |  | dans Cast3M  |
|  |  | (System Dependant)  |
|  |  |  |
|'IMPI'  | 0,1,2  | niveau de message  |
|  |  |  |
|'IMPR'  | numero unite logique  | imprimante  |
|  |  |  |
|'INCO'  |  LMOT1 LMOT2  | Noms des inconnues  |
|  |  | primales (LMOT1) et  |
|  |  | duales (LMOT2)  |
|  |  |  |
|'ISOV'  | LIGNE,SURFACE,SULI  | Type de trace des  |
|  |  | isovaleurs  |
|  |  |  |
|'LANG'  | FRAN,ANGL,...  | Langue pour la notice |
|  |  |  |
|'LECT'  | numero unite logique  | fichier d'entree  |
|  |  |  |
|'LOCA'  | VRAI,FAUX  | creation d'une table  |
|  |  | &TOTO apres chaque  |
|  |  | appel de la procedure |
|  |  | TOTO contenant toutes |
|  |  | ses variables locales |
|  |  |  |
|'MODE'  | PLANCONT  | modele de calcul  |
|  | PLANDEFO  |  |
|  | PLANGENE  |  |
|  | AXIS  |  |
|  | FOUR  |  |
|  | TRID  |  |
|  | UNIDPLANDYDZ  |  |
|  | UNIDPLANDYCZ  |  |
|  | UNIDPLANCYDZ  |  |
|  | UNIDPLANCYCZ  |  |
|  | UNIDPLANGYDZ  |  |
|  | UNIDPLANGYCZ  |  |
|  | UNIDPLANDYGZ  |  |
|  | UNIDPLANCYGZ  |  |
|  | UNIDPLANGYGZ  |  |
|  | UNIDAXISAXDZ  |  |
|  | UNIDAXISAXCZ  |  |
|  | UNIDAXISAXGZ  |  |
|  | UNIDSPHE  |  |
|  | FREQ  |  |
|  |  |  |
|'MODE' 'FOUR'| nn  | Harmonique de Fourier |
|  |  |  |
|'NAVI'  | LICE,LIMS,LBMS,MCCE,MCP1,  | Définition du couple  |
|  | MCMS,QFCE,QFP1,QFMS  | vitesse/pression dans |
|  |  | le cadre NavierStokes |
|  |  |  |
|'NBP'  | ENTIER positif ou nul  | Impose le nombre de  |
|  |  | points  |
|  |  |  |
|'NGMA'  | ENTIER positif (VAR NGMAXY)| Nb de mots ( matrice )|
|  |  |  |
|'NIVE'  |  0...19  | Niveau des sorties  |
|  |  |  |
|'OEIL'  | POINT  |Point de vu courant  |
|  |  |  |
|'OMBR'  | VRAI,FAUX  |Ombrage des traces FACE|
|  |  |  |
|'PARA'  | VRAI,FAUX  | Gibiane parallèle  |
|  |  |  |
|'PETI'  | FLOTTANT  | Plus petite valeur non|
|  |  | nulle dans Cast3M  |
|  |  | (System Dependant)  |
|  |  |  |
|'PLAC'  | Entier positif  | Place memoire libre  |
|  |  | minimale a respecter  |
|  |  |  |
|'POLI'  |8_BY_13,9_BY_15,TIMES_10,  | choix de la police  |
|  |TIMES__24,HELV_10,HELV_12,  | pour dessins et traces|
|  |HELV_18  |  |
|  |  |  |
|'POTR'  | COURIER_N, HELVETICA_N  |  choix de la police  |
|  | ou TIMES_N  | pour dessins et traces|
|  | avec N=12,14,16 ou 18  | postscript (PS et PSC)|
|  |  |  |
|'PREC'  | FLOTTANT  | Precision des  |
|  |  | operations sur les  |
|  |  | FLOTTANTS  |
|  |  | (System Dependant)  |
|  |  |  |
|'RESO'  | 'DIRECTE' ou  'ITERATIVE'  | Méthode de résolution |
|  |  |  |
|'REST'  | numero unite logique  | fichier d'entree  |
|  |  |  |
|'SAUV'  | numero unite logique  | fichier de sortie  |
|  |  |  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## VALNOM [Mathematiques Traitement] (proc)
Procedure VALNOM voir aussi : RESPOWNS VALSPE
---------------- RECOMPOM

FLOT1_R LREEL1_O = VALNOM LREEL2_S FLOT1_DT;

objet :

A partir de la donnee d'un spectre stationnaire LREEL2_S associe
a un calcul en ondelette (voir e.g. RESPOWNS et VALSPE) et du pas
de temps FLOT1_DT du residu, on calcul la ponderation LREEL1_O des
coefficients en ondelettes et FLOT1_R du residu. Cette procedure
permet une generation du signal a l'aide de RECOMPOM.

## VALP [Mathematiques Autres]
    Operateur VALPROPRE

    LREEL1 = VALPROPRE LREEL2 LREEL3 ('ITERATION' N1) ...

        ... ( |  | FLOT1 ) ;

    Objet :

    L'operateur VALPROPRE calcule les valeurs propres d'une matrice
tridiagonale de la forme:

    | A1  1  0  0  0  0 |
    | B1  A2  1  0  0  0 |
    |  0  B2  A3  1  0  0 |
    |  0  0  B3  A4  1  0 |
    |  0  0  0  B4  A5  1 |
    |  0  0  0  0  B5  A6 |

    Commentaire :

    LREEL2 : termes de la diagonale de la matrice (type LISTREEL)

    LREEL3 : termes de la sous-diagonale de la matrice (type LISTREEL)

    N1 : nombre maximum d'iterations permis dans les calculs
        (type ENTIER)

    FLOT1 : precision absolue ou relative de convergence
        (type FLOTTANT)

    LREEL1 : liste des valeurs propres, dans l'ordre de calcul
        (type LISTREEL)

## VALSPE [Mathematiques Traitement] (proc)
Procedure VALSPE voir aussi : NORMALIM
---------------- COURSPEC

LREEL1_S= VALSPE FLOT1_R LREEL2_O FLOT1_DT;

objet :

A partir de la donnee de la ponderation LREEL1_O des coefficients
en ondelettes et FLOT1_R du residu (e.g. via NORMALIM) ainsi que
le pas de temps FLOT1_DT du residu, on calcule le spectre
stationnaire LREEL1_S. Cette procedure permet e.g. un trace
a l'aide de COURSPEC.

## VAPDIF [Fluides Modele] (proc)
  Procedure VAPDIF

  DV = VAPDIF PM TM YV YH2 YHE YO2 YN2 YCO2 YCO ;

  OBJET :

Procedure donnant le coefficient de diffusion de la vapeur dans le
melange

  Commentaires

    PM : Pression totale (Pa)
    TM : Temperature du melange (K)
    YV : Fraction massique de vapeur
    YH2 : Fraction massique de hydrogene
    YHE : Fraction massique de helium
    YO2 : Fraction massique de oxygene
    YN2 : Fraction massique de azote
    YCO2 : Fraction massique de CO2
    YCO : Fraction massique de CO

    DV : coefficient de diffusion en m2/s

## VARI [Mecanique Resolution]
    Operateur VARI

    | 1ere possibilite |

    Objet :

    L'operateur VARI calcule un champ variable a partir d'un champ
donne et d'une loi de variation donnee sous la forme d'une fonction.

      CHEL2 = VARI  | MODL1 CHEL1 EVOL1 |  (MOT1) ;
        | MODL1 CHPO1 EVOL1 |
      ou

      CHPO2 = VARI CHPO1 EVOL1 (MOT2) ;

      Commentaire :

      MODL1 : Objet modele (type MMODEL)

      CHEL1 : Champ donne (type MCHAML)
        S'il a plusieurs composantes, on prend celle dont le nom
        est en abscisse de la loi de variation.

      CHPO1 : Champ donne (type CHPOINT)
        S'il a plusieurs composantes, on prend celle dont le nom
        est en abscisse de la loi de variation.

      EVOL1 : Objet definissant la loi de variation (type EVOLUTION)

      MOT1 : Objet de type MOT, sur 8 caracteres, servant a preciser
        le support du champ scalaire. Les noms possibles sont :

        'NOEUD ' : Scalaire aux noeuds

        'GRAVITE ' : Scalaire au centre de gravite

        'RIGIDITE' : Scalaire aux points d'integration de la
        raideur

        'MASSE ' : Scalaire aux points d'integration de la
        masse

        'STRESSES' : Scalaire aux points de calcul des
        contrainte

        Le nom pris par defaut est 'RIGIDITE'.

      MOT2 : nom a attribuer a la composante du champ par point
        resultat. Par defaut, on prend le nom en ordonnee de la loi
        de variation.

      CHPO2 : champ par points (type CHPOINT) a une seule composante
        de meme nature que CHPO1.

      CHEL2 : objet resultat (type MCHAML, de sous-type SCALAIRE).

    | 2eme possibilite |

    Objet :

    La valeur de certaines composantes d'un champ/element (ex :
    les proprietes materielles) depend en un point d'un parametre
    (ex : la temperature). Les lois de variation de ces composantes
    en fonction de leur parametre respectif sont donnees par des
    objets de type EVOLUTION ou NUAGE (FLOTTANT - EVOLUTION ou
    FLOTTANT-FLOTTANT-EVOLUTION).
    (note : operateur MATE accepte les objets de ces types).
    Etant donne un champ/point ou un champ/element, l'operateur VARI
    determine la valeur des composantes du champ/element selon leurs
    lois de variation en chaque point.
    Remarque 1 : Le parametre sus-cite peut varier d'un point a
        l'autre du champ/element .
    Remarque 2 : Dans le cas d'un nuage sous la forme
        FLOTTANT-FLOTTANT-EVOLUTION, il est necessaire que le
        nuage soit defini sous la forme d'une grille (memes
        valeurs donnees au deuxieme FLOTTANT pour chaque
        valeur du premier FLOTTANT)

    Extension : evaluation externe de composantes
    La valeur de certaines composantes d'un champ/element (ex : les
    proprietes materielles) depend en un point d'un ou de plusieurs
    parametres.
    Ces composantes sont decrites par des objets LISTMOTS donnant les
    listes de leurs parametres respectifs.
    (note : operateur MATE accepte les objets de type LISTMOTS)
    Les lois de variation de ces composantes en fonction de leurs
    parametres sont programmees par l'utilisateur dans le module
    externe COMPUT et ses dependances, qui ont ete compiles et lies
    au reste du code.
    Etant donne un champ/point ou un champ/element donnant les valeurs
    des parametres, l'operateur VARI appelle le module externe COMPUT
    pour evaluer les composantes en chaque noeud ou point d'integration
    du support demande.

    Remarque 1 : la description d'une composante par un objet LISTMOTS
    doit etre uniforme sur toutes les sous-zones du modele, car la
    fonction externe evaluant la composante est unique.

    Remarque 2 : le module externe COMPUT est appele pour TOUTES les
    composantes devant etre evaluees par des fonctions externes.
    La programmation de l'utilisateur doit faire la distinction des
    composantes par leur nom.

    Remarque 3 : avant l'evaluation de chaque composante, un premier
    appel au module externe COMPUT est effectue, afin de verifier la
    coherence entre la description de la composante et la programmation
    du module externe : meme nombre de parametres et memes noms de
    parametres. Apres cette verification, le module COMPUT est appele
    pour evaluer la composante en chaque point du support demande.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## VARIHC [Mecanique Resolution] (proc)
Procedure VARIHC

Cette procedure est appelee par PASAPAS, elle cree un champ
par element permettant d assurer la continuite du trajet de
fissuration dans le cas d un probleme resolu par la methode
E-FEM. La continuite est assuree en resolvant un probleme
de convection-diffusion a la fin de chaque pas de temps.
La diffusion est consideree comme isotrope.

## VARIHCSU [Mecanique Resolution] (proc)
Procedure VARIHCSU

Cette procedure est appelee par PASAPAS, elle cree un champ
par element permettant d assurer la continuite du trajet de
fissuration dans le cas d un probleme resolu par la methode
E-FEM. La continuite est assuree en resolvant un probleme
de convection-diffusion a la fin de chaque pas de temps.
La diffusion est consideree comme anisotrope.

## VECT [Post-traitement Affichage]
Operateur VECTEUR

VEC1 = VECT | CHPO1 (FLOT1) (|  'DEPL'  |  'FORC'  |)  (COUL1);
        |  (|  LMOT1  |)
        |  (| MOT1 MOT2 (MOT3 si 3D) |)
        |
        | CHAM1 (CHAM2) MOD1 (FLOT1) (MOCOMP1)  (LISMO1);
        |
        | CHAM1 (CHAM2) MOD1 (FLOT1)  LCOMP1  (LISMO1);

Objet :

L'operateur VECT construit un objet de type VECTEUR a partir :
   - des composantes d'un champ par point de vecteurs (syntaxe 1),
   - d'un champ par elements de contraintes principales (syntaxe 2),
   - d'un champ par elements de variables internes (syntaxe 2),
   - d'un champ par elements autre (syntaxe 3).

Commentaire :

VEC1 : vecteur resultat (type VECTEUR)

Syntaxe n°1 :

  CHPO1 : champ de vecteurs (type CHPOINT)

  FLOT1 : coefficient d'amplification (type FLOTTANT)
        Si il est positif le trace se fera sous formes de fleches
        originaire des points.
        Si il est negatif, le trace se fera sous forme de fleches
        pointant vers les points
        Si il est omis, il sera automatiquement calcule.

  'DEPL' | : mot-cle designant les composantes de deplacement
  'FORC' |  ou de force

  MOT1 | : noms des composantes du champ associees aux directions Ox
  MOT2 |  Oy (et eventuellement Oz en 3D) (type MOT)
  MOT3 |

  LMOT1 : idem MOT1, MOT2...

  COUL1 : couleur attribuee au vecteur VEC1 (type MOT)

Syntaxe n°2 :

  CHAM1 : champ par elements (type MCHAML, sous-type
        CONTRAINTES PRINCIPALES ou VARIABLES INTERNES)

  CHAM2 : champ par elements optionnel (type MCHAML, sous-type
        CARACTERISTIQUES)

  MOD1 : objet modele (type MMODEL)

  FLOT1 : coefficient d'amplification (type FLOTTANT)

  MOCOMP1 : si on ne souhaite conserver qu'une seule composante,
        nom de cette composante (type MOT)

  LISMO1 : liste des couleurs affectees aux composantes
        (type LISTMOTS)

Syntaxe n°3 :

  CHAM1 : champ par elements (type MCHAML, de sous-type différent
        de CONTRAINTES PRINCIPALES et VARIABLES INTERNES)

  CHAM2 : champ par elements (type MCHAML, de sous-type
        CARACTERISTIQUES) des caracteristiques geometriques
        (necessaire uniquement pour les coques epaisses)

  MOD1 : objet modele (type MMODEL)

  FLOT1 : coefficient d'amplification (type FLOTTANT)

  LCOMP1 : noms des composantes obligatoires constituant le vecteur
        (type LISTMOT)

  LISMO1 : liste des couleurs affectees aux composantes
        (type LISTMOTS)

Remarques :

Le vecteur VEC1 peut etre visualise par la directive TRACER.

Il apparaitra avec l'amplification FLOT1 et la couleur COUL1 dans le
premier cas ; avec l'amplification FLOT1 et les couleurs donnees
dans LISMO1 dans le second cas.

Il est possible, dans le but d'obtenir plusieurs traces de vecteurs
sur le meme graphique, d'appliquer l'operateur ET entre des objets
de type VECTEUR.

Le MCHAML de VARIABLES INTERNES est normalement issu de la
procedure PASAPAS et est destine a la visualisation des fissures
avec la directive TRACER. En 2D ( ou element de coque ) le trait
dessine represente la fissure, tandis qu'en 3D il est
perpendiculaire au plan de la fissure.

Exemple d'application :

Visualisation du champ de reactions a des blocages :

       RITOT = RIGID ET BLOQ ;
       DEP = RESOU RITOT FORCES;
       REA = REACT DEP RITOT;
       VEC = VECTEUR REA 15. FX FY FZ ROUG;
       TRAC OEIL S VEC ;

## VENV [Entree-Sortie Entree-Sortie]
Operateur VENV

MOT2 = 'VENV' MOT1 ;

Objet :

L'operateur VENV recupere, dans MOT2, la valeur de la variable
d'environnement de nom MOT1.

Commentaire :

MOT1 : Chaine de caracteres (de type MOT) correspondant au nom de la
        variable d'environnement (variable systeme) a lire.
        Cette chaine ne doit pas compter plus de 256 caracteres.

MOT2 : Chaine de caracteres (de type MOT) contenant la valeur de la
        variable de nom MOT1 lue. Dans le cas ou la variable n'est pas
        definie, MOT2 contient le MOT ' ' (un seul espace).

Remarques :

Tous les espaces sont ignores lors de la lecture du nom de la variable MOT1.

"'VENV' 'USER' ;" et "'VENV' ' U S ER ' ;" conduisent au meme resultat
(par exemple, root).

Les noms de variables acceptes sont composes de lettres majuscules et/ou
minuscules, de chiffres et du caractere souligne "_", les chiffres etant
interdits en premier caractere.

## VERI [Mathematiques Autres]
Operateur VERI

LOG1 = 'VERI' | FLOT1 | ;
        | CHPO1 |

Objet :

L'operateur VERI verifie qu'un nombre FLOTTANT FLOT1 est un reel.
Il peut aussi verifier que les valeurs d'un CHPOINT CHPO1 sont
reelles.

Il rend le LOGIQUE LOG1 egal a VRAI si oui et FAUX si non.

Remarque :

  INF et NAN ne sont pas des reels.

## VERM [Maillage Generaux]
Directive VERM

    VERM GEO1 ;

Objet :

La directive VERM verifie le maillage GEO1 constitue d'elements
massifs. Les verifications sont de deux types.

- verifie qu'une meme maille n'apparait pas plusieurs fois dans
  une meme sous-zone.

- verifie qu'il n'y a pas d'elements de degre un accole a un
  element de degre 2,

- verifie que la continuite des elements massifs 3D est bien
  assuree par des faces de meme types.

Pour aider l'utilisateur des points et des mailles nommees sont
crees, de noms NODEXX et MESHXX ou XX vaut 1,2,3,...

Des messages d'avertissements sont emis.

## VERS [Maillage Generaux]
    Operateur VERSENS

    GEO2 = VERSENS GEO1 ;

    Objet :

    L'operateur VERSENS est l'operateur identite sur le objet GEO1 (type
MAILLAGE). Toutefois, il produit une erreur si dans GEO1 deux elements
jointifs sont orientes en sens opposes.

## VERTYTAB [Entree-Sortie Entree-Sortie] (proc)
   Procedure VERTYTAB

   VERTYTAB OBJ1 ENTREE TYPE ;

   OBJET :

La procedure VERTYTAB verifie l'existence et le type d'une entree
dans une table. Si OBJ1.ENTREE n'existe pas ou n'est pas du type TYPE
un message d'erreur est edite.

   Commentaires

   OBJ1 : Objet de type TABLE
   ENTREE : Objet de type MOT indice de la table dont on teste
        l'existence
   TYPE : Objet de type MOT type attendu pour OBJ1.ENTREE

## VIBC [Mathematiques Autres]
    Operateur VIBC

CHAP{Objet}

    L'operateur VIBC recherche les valeurs propres et les
    vecteurs propres (reels ou complexes) de problemes "petits"
    (typiquement des matrices projetees sur base modale obtenue
    avec l'operateur VIBR) par des algorithmes directs (QR ou QZ).

    En particulier, 3 syntaxes associees aux 3 problemes aux
    valeurs propres suivants sont prevues :

    (1) [K + (i*2*pi*w)*C - (2*pi*w)**2 M] X = 0
    (2) [ A - \lambda I ] . X = 0 avec A symetrique
    (3) [ A - \lambda I ] . X = 0 avec A = [K1 K2 ; K3 K4]

CHAP{Syntaxe 1 : Probleme aux valeurs propres quadratique}

PART{Syntaxe gibiane}

    BAS2 = VIBC MASS1 RIG1 (AMOR1) (BAS1) (ENT1);

PART{Arguments}

    BAS2 : objet resultat contenant les valeurs et les vecteurs
        propres complexes (type TABLE, sous-type BASEMODA).
        Details : cf. §Structure de la table de sortie.

    MASS1 : matrice de masse
        (type RIGIDITE, sous-type MASSE)

    RIG1 : matrice de rigidite
        (type RIGIDITE, sous-type RIGIDITE)

    AMOR1 : matrice d'amortissement
        (type RIGIDITE, sous-type AMORTISSEMENT)

    BAS1 : base de modes reels, sur laquelle les matrices ont
        ete eventuellement projetees (type TABLE, sous-type
        BASEMODA). Sa specification implique la recombinaison
        sur les degres de liberte elements finis (physique).

    ENT1 : entier specifiant le nombre de couple de modes
        complexes de plus bas module a sortir. Par defaut,
        tous sont fournis en sortie.

    Rem : Si le type des matrices correspond a MASSE, RIGIDITE et
        AMORTISSEMENT, elles sont triees et leur ordre d'entree
        n'a pas d'importance. Sinon elles sont traitees selon
        leur ordre d'entree.

PART{Commentaires}

    Avec cette syntaxe, l'operateur VIBC recherche les valeurs
    propres complexes w (en Hz) et les vecteurs propres complexes X
    solutions de l'equation fondamentale de la dynamique :
        M q'' + C q' + K q = 0
        avec q(t) = X exp(i*2*pi*w*t)

    Il resoud donc :
        [K + (i*2*pi*w)*C - (2*pi*w)**2 M] X = 0
    et fournit :
        X = X + i X et w = w + i w
        R I R I

    L'algorithme utilise est le QZ.

CHAP{Syntaxe 2 : Probleme aux valeurs propres reel symetrique}

PART{Syntaxe gibiane}

    BAS2 = VIBC RIG1 ;

PART{Arguments}

    BAS2 : objet resultat contenant les valeurs et les vecteurs
        propres reels (type TABLE, sous-type BASEMODA).
        Details : cf. structure de la table de sortie.

    RIG1 : matrice symetrique (type RIGIDITE)

PART{Commentaires}

    Avec cette syntaxe, l'operateur VIBC recherche les valeurs
    propres reelles lambda et les vecteurs propres reels X
    solutions de :
        [ A - \lambda I ] . X = 0 avec A symetrique
    et fournit : X et \lambda

    L'algorithme utilise est le QR (Lapack).

CHAP{Syntaxe 3 : Probleme aux valeurs propres reel non-symetrique de taille double}

PART{Syntaxe gibiane}

    BAS2 = VIBC RIG1 RIG2 RIG3 RIG4;

PART{Arguments}

    BAS2 : objet resultat contenant les valeurs et les vecteurs
        propres reels (type TABLE, sous-type BASEMODA).
        Details : cf. structure de la table de sortie.

    RIG1,2,3 et 4 : matrice de rigidite quelconque (type RIGIDITE)

PART{Commentaires}

    Avec cette syntaxe, l'operateur VIBC recherche les valeurs
    propres complexes w=-(i/2pi)*\lambda et les vecteurs propres X
    solutions de :
        [ A - \lambda I ] . X = 0
        avec A = [ RIG1 RIG2 ]
        [ RIG3 RIG4 ]
    ce qui correspond par exemple a une matrice de monodromie.
    Il fournit :
        X = X + i X et w = w + i w
        R I R I

    L'algorithme utilise est le QZ.

CHAP{Structure de la table de sortie}

      BAS2.'SOUSTYPE' = mot 'BASE_MODALE'
      BAS2.'CONVERGENCE' = LOGIQ1 (syntaxes 1 et 3)
      BAS2.'MODES' = TAB2
      + TAB2.'SOUSTYPE' = mot 'BASE_DE_MODES'
      + TAB2.'MAILLAGE' = MAIL1
      + TAB2.IMOD = TAB3
        + TAB3.'SOUSTYPE' = 'MODE_COMPLEXE'
        + TAB3.'POINT_REPERE' = PT1
        + TAB3.'NUMERO_MODE' = NUMOD
        + TAB3.'FREQUENCE_REELLE' = wR (syntaxes 1 et 3)
        + TAB3.'FREQUENCE_IMAGINAIRE' = wI (syntaxes 1 et 3)
        + TAB3.'DEFORMEE_MODALE_REELLE' = XR (syntaxes 1 et 3)
        + TAB3.'DEFORMEE_MODALE_IMAGINAIRE' = XI (syntaxes 1 et 3)
        + TAB3.'VALEUR_PROPRE' = lambda (syntaxe 2)
        + TAB3.'DEFORMEE_MODALE' = X (syntaxe 2)

      BAS2 : type TABLE, sous-type BASE_MODALE
      LOGIQ1 : logique indiquant si VIBC a converge
[… notice tronquée ; texte complet dans l'archive PCW_24]

## VIBR [Mathematiques Autres]
    Operateur VIBRATION

        |'PROCHE'  ... |
    SOL1 = VIBRATION  |'INTERVALLE' ... |  RIG1 MASS1  (AMO1) ...
        |'SIMULTANE'  ... |
        |'IRAM'  ... |

        ... ('IMPR') (LOG1) ;

    Objet :

    L'operateur VIBRATION recherche certaines valeurs propres w (en Hz)
    et modes propres X d'un systeme physique represente par :
    - sa rigidite K
    - sa masse M
    - son amortissement C (uniquement possible avec l'option IRAM)

    Autrement dit, il resoud :
      [K - (2*pi*w)**2 M] X = 0
        ou
      [K + (2*i*pi*w)*C - (2*pi*w)**2 M] X = 0

    Commentaire :

    SOL1 : objet resultat contenant les valeurs et les modes
        propres (de TYPE TABLE).

    RIG1 : matrice de rigidite K du systeme physique
        (type RIGIDITE, sous-type RIGIDITE)

    MASS1 : matrice de masse du M systeme physique
        (type RIGIDITE, sous-type MASSE)

    AMO1 : matrice d'amortissement C du systeme physique
        (type RIGIDITE, sous-type AMORTISS)

    'IMPR' : mot-cle indiquant que l'on veut des impressions
        intermediaire

    LOG1 : indique quel traitement adopter pour les valeurs
        propres negatives (type LOGIQUE, par defaut VRAI).
        - si VRAI, pour lambda = (2*pi*w)**2 negatif,
        la frequence propre retournee sera :
        sign(lambda)*|w|
        - si FAUX, la frequence retournee sera : |w|

    Suivant le mot-cle ('PROCHE', 'INTERVALLE', 'SIMULTANE', ou 'IRAM'),
    la recherche des modes propres est effectuee de plusieurs manieres :

    |  1ere possibilite  :  'PROCHE'  |

    SOL1 = VIBRATION 'PROCHE' LREEL1 ( LENTI1 ) RIG1 MASS1 ;

    L'option 'PROCHE' correspond a la methode des iterations inverses
sur sous-espace. Cet algorithme robuste peut s'averer couteux
lorsqu'un tres grand nombre de modes est recherche.
    Pour chaque reel FREQ de LREEL1 (type LISTREEL) et pour chaque
entier N de LENTI1 ( type LISTENTI ) on recherche les N modes propres
dont les frequences sont les plus proches de FREQ. Les listes doivent
donc etre de meme taille !

    |  2eme possibilite  :  'INTERVALLE'  |

        |'BASSE'|
    SOL1 = VIBRATION 'INTERVALLE' FLOT1 FLOT2 (|  | N1)
        |'HAUTE'|

        RIG1 MASS1 ( 'MULT' )

    L'option 'INTERVALLE' correspond a la methode de la bissection. Cet
algorithme se revele generalement tres couteux par rapport aux autres.
    On recherche les modes propres dont les frequences sont contenues
dans l'intervalle [FLOT1,FLOT2]. FLOT1 et FLOT2 sont de type FLOTTANT.
    On peut limiter la recherche aux N1 (type ENTIER) plus basses
(option 'BASSE') ou hautes (option 'HAUTE') frequences dans
l'intervalle donne. Les modes multiples peuvent etre obtenus avec
l'option 'MULT'.

    |  2eme possibilite  :  'SIMULTANE'  |

    SOL1 = VIBRATION 'SIMULTANE' FLOT1 N1 RIG1 MASS1 ;

    L'option 'SIMULTANE' correspond a la methode de Lanczos avec re-
orthogonalisation. Cet algorithme est particulierement efficace
lorsqu'un tres grand nombre de modes est recherche.
    On recherche une serie de N1 (type ENTIER) modes propres dont les
frequences sont voisines d'une valeur FLOT1 (type FLOTTANT).

    |  4eme possibilite  :  'IRAM'  |

    SOL1 = VIBRATION 'IRAM' FLOT1 N1 RIG1 MASS1 (AMO1) (MOTRI);

    L'option 'IRAM' correspond à la méthode d'Arnoldi avec redémarrage
implicite.

La librairie libre ARPACK (Copyright (c) 1996-2008 Rice University.
Developed by D.C. Sorensen, R.B. Lehoucq, C. Yang, and K. Maschhoff.
All rights reserved.) est utilisee.
Cette dernière utilise également les libraires LAPACK ET BLAS.

Elle permet de traiter différents types de problèmes :
  - Hermitiens et non-Hermitiens
  - Linéaires ou quadratiques

On recherche une serie de N1 (type ENTIER) modes propres dont les
frequences sont voisines d'une valeur FLOT1 (type FLOTTANT).

    MOTRI : MOT correspondant à l'option de tri utilisée pour les
        valeurs propres. A choisir parmi :

        'LM' - Extraction des modes avec les valeurs propres les plus
        proches - en module - de du décalage spectral (option par
        défaut)

        'SM' - Extraction des modes avec les valeurs propres les plus
        éloignées du décalage spectral

        'LR' - Extraction des modes avec les valeurs propres à la plus
        grande partie réélle

        'SR' - Extraction des modes avec les valeurs propres à la plus
        petite partie réélle

        'LI' - Extraction des modes avec les valeurs propres à la plus
        grande partie imaginaire
[… notice tronquée ; texte complet dans l'archive PCW_24]

## VIDE [Langage Objets]
    Operateur VIDE
    -------------- SUIT,MOTS,MANU

    Objet :

    L'opérateur VIDE permet de créer un ou plusieurs objets vides
    de types/sous-types donnés.

    L'opérateur VIDE permet egalement de tester si un objet est vide.

CHAP{Creation d'un objet vide}

    Syntaxe :

    Deux possibilités pour récupérer les objets vides créés :

      1) Objets séparés :

        OBJ1,...,OBJn = VIDE [GROUPE1,...,GROUPEn]

      2) Objets indicés dans une table :

        TAB1 = VIDE ('TABULER' ( |LENTI1| ) ) [GROUPE1,...,GROUPEn]
        |LREEL1|
        |LMOTS1|

    Dans les deux cas, GROUPEi est de la forme :

        MOTAi(/MOTBi)(*ENTIi)

   Commentaires :

   1) La création d'objets vides peut être intéressante lorsqu'il s'agit
      de construire des objets par itérations successives.
      L'opérateur VIDE permet d'initialiser l'objet global et d'éviter
      ainsi tout test d'existence avant d'utiliser l'opérateur ET.
      Ceci est particulièrement précieux quand le premier ET peut
      survenir alternativement en différents points du jeu de données.

   2) Si l'option 'TABULER' est utilisee, il est possible d'indiquer à
      quels indices sont placés les objets qui sont créés en spécifiant
      une liste LENTI1 (type LISTENTI) ou LREEL1 (type LISTREEL) ou
      LMOTS1 (type LISTMOTS).

      Si la liste est trop courte, les indices manquants seront des
      entiers incrémentés suivant l'ordre de création des objets.

      /!\ ATTENTION : On laisse à l'utilisateur le soin de s'assurer
        qu'aucun indice de la table ne sera écrasé. Cela
        surviendra automatiquement si la liste fournie
        comporte des doublons, mais peut aussi arriver
        s'il s'agit d'un LISTENTI trop court.

   3) Les GROUPEi définissent le type MOTAi, ainsi qu'éventuellement le
      sous-type MOTBi et/ou le nombre d'objets à créer. Le tableau
      ci-dessous précise quelles sont les valeurs autorisées :

        MOTAi  |  MOTBi
       'MAILLAGE'  |  N'importe quel type d'élément valide
        |  (Par défaut : valeur retournée par VALE 'ELEM')
       'CHPOINT '  |  Nature du champ : 'DISCRET' ou 'DIFFUS'
        |  (Par défaut : 'INDETERMINE')
       'MCHAML  '  |  AUCUN
       'MMODEL  '  |  AUCUN
       'RIGIDITE'  |  Le sous-type attribué à la matrice
        |  (Par défaut : chaîne vide '  ')
       'EVOLUTIO'  |  Le sous-type REEL ou COMPLEXE (courbes par paire)
        |  (Par défaut : chaîne vide '  ')
       'LISTENTI'  |  AUCUN
       'LISTREEL'  |  AUCUN
       'LISTMOTS'  |  AUCUN
       'LISTCHPO'  |  AUCUN
       'TABLE  '  |  Le sous-type attribué à la table
        |  (Par défaut : la table n'a pas de sous-type)
       'DEFORME '  |  AUCUN
       'VECTEUR '  |  AUCUN
       'CHARGEME'  |  AUCUN
       'NUAGE'  |  AUCUN
       'ANNOTATI'  |  AUCUN
       'LISTOBJE'  |  AUCUN

   Exemples :

   a) MAIL1 = VIDE 'MAILLAGE' ;
      MAIL2 = VIDE 'MAILLAGE'/'SEG2' ;
      MAIL3 = VIDE 'MAILLAGE'/'TRI3' ;

      MAIL1 est un maillage vide constitué de l'élément par défaut
      MAIL2 est un maillage vide de SEG2
      MAIL3 est un maillage vide de TRI3

   b) RIG1 RIG2 = VIDE 'RIGIDITE'/'RIGIDITE' 'RIGIDITE'/'MASSE' ;

      RIG1 est une matrice vide de sous-type 'RIGIDITE'
      RIG2 est une matrice vide de sous-type 'MASSE'

   c) LENTI1 LENTI2 LENTI3 = VIDE 'LISTENTI'*3 ;
      TAB1 = VIDE 'TABU' 'LISTENTI'*3 ;
      TAB2 = VIDE 'TABU' (MOTS 'UX' 'UY' 'UZ') 'LISTENTI'*3 ;

      LENTI1, LENTI2 et LENTI3 sont trois listes d'entiers vides.
      TAB1 contient trois indices 1, 2 et 3 renvoyant chacun à une
      liste d'entiers vide.
      Idem dans TAB3, mais les indices sont 'UX','UY' et 'UZ'.

   d) MAIL1 MAIL2 = VIDE 'MAILLAGE'/'CUB8'*2 ;
      MAIL1 MAIL2 = VIDE 'MAILLAGE'*2/'CUB8' ;

      L'ordre est indifférent : MAIL1 et MAIL2 sont deux maillages vides
      de CUB8.

CHAP{Test d'un objet}

    LOG1 = VIDE OBJ1 ;

    LOG1 : LOGIQUE, resultat du test,

    et OBJ1 de type :

    MAILLAGE, CHPOINT, MCHAML, MMODEL, RIGIDITE, EVOLUTIO,
    LISTENTI, LISTREEL, LISTMOTS, LISTCHPO, TABLE, DEFORME,
    VECTEUR, CHARGEME, NUAGE, ANNOTATI.

    Remarque : l'objet MOT ne peut pas etre teste.

## VISA [Maillage Autres]
    Operateur VISAVIS

    MAI1 MAI2 = VISAVIS (FLOT1) GEO1 (GEO2) ;

    Objet :

    Operateur VISAVIS cree la liste des noeuds de GEO1 ayant un
noeud de GEO2 localise au meme endroit, il cree aussi
la liste des noeuds de GEO2 concernes.

    Les listes des noeuds en vis-a-vis sont presentees sous la forme
d'objets de type MAILLAGE compose elements POI1 a un noeud.

    Les noeuds selectionnes sont a une distance inferieure au dixieme
de la densite courante ou inferieur a FLOT1 s'il est fourni.

    Si GEO2 n'est pas fourni on dresse les listes des noeuds doubles
de GEO1.

   Remarque :
   Cet operateur peut etre utile quand il faut fournir des objets
maillages dont seul la liste des noeuds ordonnee est importante,
par exemple pour operateur RELATION.

## VITETFOR [Mecanique Dynamique] (proc)
    procedure VITETFOR

    cette procedure est appelee par la procedure de dynamique
PASAPAS afin de calculer des corrections aux vitessses et
aux forces en cas de contact avec liaison persistante

## VITEUNIL [Mecanique Resolution] (proc)
    procedure VITEUNIL

    cette procedure est appelee par les procedures de dynamique
( NEWMARK, NONLIN) afin de corriger les vitesses en cas d'appuis
unilateraux.

## VLOC [Post-traitement Affichage]
Operateur VLOC
-------------- VECT VSUR

CHAM123 = VLOC MOD1 MAT1 ;

Objet :

L'operateur VLOC construit un champ (type CHAMELEM) representant
le repere local d'orthotropie a partir du modele et du materiau.

Commentaire :

MOD1 : modele de calcul , type MMODEL (cree par MODE)

MAT1 : materiau associe au modele, type CHAMELEM (cree par MATE)

CHAM123 : CHAMELEM defini aux POINTS DE GAUSS de RIGIDITE
        de sous type VECTEUR LOCAUX de composantes :

| Mode de | type  |  Noms des composantes  |
| calcul  | d'element | vecteur V1  | vecteur V2  | vecteur V3  |
|  3D  |  tous  | V1X V1Y V1Z | V2X V2Y V2Z | V3X V3Y V3Z |
|  2D  |  massif  | V1X V1Y  | V2X V2Y  |  -  |
|  2D  |  coque  | V1X V1Y V1Z | V2X V2Y V2Z | V3X V3Y V3Z |
|  Axi et |  massif  | V1R V1Z  | V2R V2Z  |  -  |
| Fourier |  |  |  |  |
|  Axi et |  coque  | V1R V1Z V1T | V2R V2Z V2T | V3R V3Z V3T |
| Fourier |  |  |  |  |

Dans le cas des coques, V3 est toujours perpendiculaire a la coque.

Il est ensuite possible de visualiser la base (V1,V2,V3) avec
l'operateur VECT.

## VMIS [Mecanique Resolution]
    Operateur VMIS
    -------------- PRIN CARA

       VMIS1 = VMIS MODL1 SIG1 ( CAR1 ) ;

    Objet :

    L'operateur VMIS calcule une contrainte equivalente a un champ de
contraintes. Dans les cas massifs ( 2D et 3D ), elle coïncide avec
la contrainte de Von Mises.

      Commentaire :

      MODL1 : objet modele ( type MMODEL ).

      SIG1 : champ de CONTRAINTES ( type MCHAML,
        sous-type CONTRAINTES)

      CAR1 : champ de CARACTERISTIQUES geometriques necessaires
        pour les elements coques, poutres et tuyaux (type
        MCHAML, sous-type CARACTERISTIQUES)

      VMIS1 : objet resultat (type MCHAML ).

    Remarque :

    Dans le cas des coques minces, la contrainte equivalente est
calculee a partir des efforts membranaires Nij et flexionnels Mij
et des caracteristiques (cf operateur CARA) selon la formule :

    Seq = ( (N / EPAIS)**2 + (6 * ALFA * M / EPAIS**2)**2 ) ** 0.5

    ou N = ( N11**2 + N22**2 - N11*N22 + 3*N12**2 ) ** 0.5
        M = ( M11**2 + M22**2 - M11*M22 + 3*M12**2 ) ** 0.5

    Dans le cas des poutres, la contrainte equivalente est calculee
a partir des efforts, des moments, et des caracteristiques (cf operateur
CARA) selon la formule :

    Seq = ( ( EFFX / SECT )**2
        + ( MOMX * DX / TORS )**2
        + ( MOMY * DZ / INRY )**2
        + ( MOMZ * DY / INRZ )**2 )**0.5

    Dans le cas des tuyaux, la contrainte equivalente est calculee
a partir des efforts, des moments, et des caracteristiques (cf operateur
CARA) selon la formule :

    Seq = ( ( EFFX * CFFX / SECT )**2 +
        + ( MOMX * CFMX * RMOY / TORS )**2
        + ( MOMY * CFMY * RMOY / INRY )**2
        + ( MOMZ * CFMZ * RMOY / INRZ )**2 )
        + ( PRES * RMOY * CFPR / EPAI )**2 )**0.5

    Les inerties etant eventuellement modifiees en fonction
des flexibilites pour les coudes.

## VNIMP [Fluides Resolution] (proc)
   Operateur VNIMP
   --------------- EQEX

   SYNTAXE ( EQEX ) : Cf operateur EQEX

     'OPER' 'VNIMP' coef 'INCO' 'UN'

   OBJET :

L'operateur VNIMP discretise en 2D la condition limite V.n = vnormale
par une methode d'elements finis. (n normale dependant du sens de
description de la frontiere)

   Commentaires

    coef vitesse normale
        FLOTTANT
        ou CHPOINT SCAL SOMMET
        ou MOT

    UN Champ de vitesse
        CHPOINT VECT SOMMET

Un coefficient de type MOT indique que l'operateur va chercher le
champ dans la table INCO a l'indice MOT.

## VOLU [Maillage Volumes]
    Operateur VOLUME

    L'operateur VOLU s'emploie dans differents cas :

    |  1ere possibilite  |

    GEO1 = SURF1 VOLU ('VERB') ;

    Objet :

   L'operateur VOLU construit le maillage GEO1 (type MAILLAGE) du volume
situe a l'interieur de l'enveloppe SURF1 (type MAILLAGE).

   Le mot-cle 'VERB' indique que l'on souhaite afficher des informations
supplementaires pendant la construction des elements du maillage.

    |  2eme possibilite  |

    GEO1 = SURF1 VOLU | (N1) ('DINI' DENS1) ('DFIN' DENS2) |  ...
        | 'PROG' LR1  |

        |'TRAN'  VEC1  |
        ...  |'ROTA'  FLOT1  AXEI1 AXEJ1  | ;
        |'GENE'  LIG1  |
        | SURF2  |

    Objet :

    L'operateur VOLU construit le volume engendre par translation ou
rotation d'une surface.

    Commentaire :
    SURF1 : surface (type MAILLAGE)

    N1 : nombre de couches engendrees (type ENTIER)

    'TRAN' : mot-cle, indiquant que le volume est engendre par une
        translation de la surface SURF1, suivi de :
    VEC1 : vecteur de translation (type POINT)

    'ROTA' : mot-cle, indiquant que le volume est engendre par une rota
        tion de la surface SURF1, suivi de:
    FLOT1 : angle de rotation (type FLOTTANT)
    AXEI1 | : points (type POINT) definissant l'axe (oriente) de
    AXEJ1 |  rotation

    'GENE' : mot-cle, indiquant que le volume est engendre par une
        translation parallelement a une generatrice, suivi de :
    LIG1 : ligne generatrice (type MAILLAGE)

    SURF2 : si aucun mot-cle n'est precise, le volume construit relie
        SURF1 et SURF2 (type MAILLAGE)
        les deux objets SURF1 et SURF2 doivent etre homeomorphes

    DENS1 | : densites associees a la surface SURF1 et au vecteur VEC1
    DENS2 |  (option 'TRAN') ou a l'axe AXEI1 AXEJ1 (option 'ROTA') ou
        a la ligne LIG1 (option 'GENE') ou a la surface SURF2.

    LR1 : LISTREEL definissant les positions des noeuds
        intermediaires crees (voir la remarque).

    Remarques :

    Si SURF1 est deja un volume, l'operation s'applique a la face 2 de
SURF1 et a pour resultat SURF1 augmente des elements engendrees. Il en
est de meme pour SURF2 et son eventuelle face 1.

    Si N1 n'est pas specifie, le nombre de couches engendrees et leurs
epaisseurs seront calcules en fonction des densites utilisees.

    Si N1 est specifie et positif, N1 couches d'egale epaisseur seront
engendrees.

    Si N1 est negatif, N1 couches seront engendrees et leur epaisseur
sera calculee en tenant compte des densites utilisees.

    Si les densites associees a la surface SURF1 et au vecteur VEC1 ou
 aux points AXEI1 et AXEJ1 ou a la surface SURF2 ne sont pas correctes,
il est possible de les surcharger. Pour la densite initiale, il faut
donner la bonne valeur derriere le mot-cle 'DINI' et, pour la finale,
derriere le mot-cle 'DFIN'.

    Lorsque l'option 'PROG' suivie d'un LISTREEL est utilisee, les
noeuds intermediaires seront crees selon la regle suivante. Les deux
extremites du volume (SURF1 et SURF2 ou l'image de SURF1 par TRANslation
ou ROTAtion) sont homeomorphes, chaque point de la premiere possede donc
l'equivalent appartenant a la seconde surface.
Si LR1 = {r1,...,rn} alors on pour toute paire de points equivalents
nous definisson una application lineaire L: [r1,rn] --->
intervalle(P1,P2) (ou arc liant P1 et P2 dans le cas 'ROTA') telle que
L(r1)=P1 et L(rn)=P2. Les points intermediaires seront places aux
endroits L(r2), L(r3), ... Si LR1 contient n valeurs, alors (n-1)
couches d'elements seront generees.
ATTENTION !!! Aucune verification n'est faite sur le contenu de LR1. En
particulier, si la progression a l'interieur de LR1 n'est pas monotone,
des couches d'elements vont se chevaucher.

    |  3eme possibilite  |

     GEO1 = SURF1 VOLU SURF2 PO1 PO2 (N1) ('DINI' DENS1) ('DFIN' DENS2)

     Objet :

     L'operateur VOLU raccorde des maillages surfaciques qui
 ont des structures de grille mais pas forcement le meme nombre
 de lignes et de colonnes. Par contre le nombre total de noeuds
 sur les lignes de SURF1 et SURF2 doit etre pair. De meme pour
 les noeuds des colonnes.

     Commentaire :

     SURF1: objet de type MAILLAGE. Il doit etre constitue exclu-
        sivement de quadrangle QUA4 ou QUA8 et avoir une
        structure de grille.

     SURF2: objet de type MAILLAGE. Il doit etre constitue du me-
        me type d'elements que SURF1 et avoir une structure
        de grille.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## VORO [Maillage Autres]
 Operateur VORONOI

 TAB1 = VORO MAIL1 MAIL2 (CHR1);

 Objet :

L'operateur VORONOI construit la partition de Voronoi d'un ensemble
de points MAIL1 limitee au domaine defini par le maillage MAIL2.
La partition de Voronoi est definie par la table TAB1 decrite
ci-dessous.

 Commentaire :

 MAIL1 : objet MAILLAGE, forme d'elements de type POI1.

 MAIL2 : objet MAILLAGE, contour (enveloppe) ferme, oriente, connexe
        et constitue d'elements SEG2 (TRI3) en 2D (3D), servant a
        limiter la partition de Voronoi.

 CHR1 : objet CHPOINT, permet de decrire le poid associe a chaque
        centre de cellule.

 TAB1 : objet TABLE contenant la partition de Voronoi.
        La table est organisee ainsi :

   - TAB1 . 'VISU' = Maillage de toutes les aretes de la partition
        de Voronoi (elements SEG2)
   - TAB1 . 'POND' = Objet de type CHPOINT indiquant le poid associe
        a chaque centre de cellule

   - TAB1 . 'CELL' = Table des cellules de Voronoi
   - TAB1 . 'CELL' . P1 = Table de la cellule de
        germe P1 (type POINT)
   - TAB1 . 'CELL' . P1 . 'VISU' = Maillage de la cellule de
        germe P1
   - TAB1 . 'CELL' . P1 . 'FACS' = Liste-entier des numeros des
        faces formant la cellule
        de germe P1 (en 3D)
   - TAB1 . 'CELL' . P1 . 'ARTS' = Liste-entier des numeros des
        aretes formant la cellule
        de germe P1 (en 2D)
   - TAB1 . 'CELL' . P1 . 'VOIS' = Maillage des points
        voisins du point P1

   - TAB1 . 'FACS' = Table des faces des cellules
   - TAB1 . 'FACS' . n1 = Table de la face numero n1
        (type ENTIER)
   - TAB1 . 'FACS' . n1 . 'VISU' = Maillage de la face numero n1
   - TAB1 . 'FACS' . n1 . 'ARTS' = Liste des numeros des aretes
        formant la face numero n1

   - TAB1 . 'ARTS' = Table des aretes des cellules
   - TAB1 . 'ARTS' . m1 = Maillage de l'arete numero m1

 Remarque :

 * L'utilisation d'un champ par point comme argument de VORO permet
 de generer une partition de Voronoi Ponderee.
 Les valeurs du champ par point doivent verifier : pour tout couple
 de points (P1,P2) de poids (x1,x2), on a :
        |(x1)**2 - (x2)**2| =< (d(P1,P2))**2
 ou d(P1,P2) est la longueur du segment P1P2.

## VSUR [Mathematiques Autres]
   Operateur VSUR

   CHAM1 = VSUR MODL1 ('NORM')

   Objet :

   L'operateur VSUR permet de calculer :
- les 'vecteurs surface' aux points d'integration des elements coques,
- les 'vecteurs tangent' aux points d'integration des elements poutres,
- pour les autres types d'element le champ par element est vide.
Si le mot-cle 'NORM' n'est pas specifie, la norme des vecteurs est
egale au jacobien au point considere, sinon le champ par element est
en fait le champ de normales aux coques.

   Commentaire :

   MODL1 : objet modele (type MMODEL)

   CHAM1 : objet resultat (type MCHAML) de composantes VX, VY, (VZ)
        ou VR, VZ

   'NORM' : mot-cle : s'il est specifie les vecteurs sont normes,
        CHAM a alors pour sous-type 'NORMALES', sinon CHAM a pour
        sous-type 'VECTEURS SURFACE'

## VTIMP [Fluides Resolution] (proc)
   Operateur VTIMP
   --------------- EQEX

   SYNTAXE ( EQEX ) : Cf operateur EQEX

     'OPER' 'VTIMP' coef 'INCO' 'UN'

   OBJET :

L'operateur VTIMP discretise en 2D la condition limite V.t = vtangente
par une methode d'elements finis. (t tangente dependant du sens de
description de la frontiere)

   Commentaires

    coef vitesse tangente
        FLOTTANT
        ou CHPOINT SCAL SOMMET
        ou MOT

    UN Champ de vitesse
        CHPOINT VECT SOMMET

Un coefficient de type MOT indique que l'operateur va chercher le
champ dans la table INCO a l'indice MOT.

## WAAM [—] (proc)
    Procedure WAAM

CHAP{Specification generale}

    Objet :

        La procedure WAAM permet de mailler une sequence de soudage
    (voir SOUDAGE). Outre le maillage, elle fournit en sortie un
    sequencage du maillage en fonction du temps representant une
    discretisation spatio-temporelle de l'apport de matiere selon
    un pas de discretisation choisi. Elle propose egalement une
    discretisation temporelle du chargement (sous-option TEMP).
    Enfin, l'option VISU permet de visualiser le sequencage realise
    de l'apport de matiere.

    Remarque : la procedure WAAM est uniquement disponible en dimension 3.

CHAP{Option MAIL}

    Syntaxe :

    TAB2 = WAAM TAB1 'MAIL' 'PAS' | FLOT1 | ('LARG' FLOT2) | ('DENS FLOT3) | ...
        | LREE1 |  |  (N1)  |

        ... ('TEMP' (FLOT4)) ;

    Entrees :

    TAB1 : objet TABLE, sequence de soudage definie avec SOUDAGE.

    FLOT1 : objet FLOTTANT, pas de discretisation en espace de l'apport
        de matiere (le long de la trajectoire de soudage).

    LREE1 : objet LISTREEL, liste des pas de discretisation en espace de
        l'apport de matiere (le long de la trajectoire de soudage).
        Chaque pas est utilise successivement. Le dernier pas est
        conserve pour discretiser le reste de la passe a mailler si
        l'ensemble des pas de la liste ne couvre pas toute la longueur.

    FLOT2 : objet FLOTTANT, largeur des passes de soudage (facultatif
        si defini dans TAB1).

    FLOT3 : objet FLOTTANT, densite du maillage.

    N1 : objet ENTIER, nombre d'element sur un pas de discretisation
        en espace (1 par defaut). Si un LISTREEL est fourni,
        on considere le 1er pas de la liste.

    FLOT4 : objet FLOTTANT, pas de temps de calcul lors des passes de soudage.
        Par defaut, (1/3pi) du temps de parcours du 1er pas de
        discretization en espace.

    Sorties :

    TAB2 . MAILLAGE : objet MAILLAGE, maillage final de la sequence

    TAB2 . EVOLUTION_MAILLAGE : objet TABLE definissant le sequencage
        temporel de l'apport de matiere

        . EVOLUTION_MAILLAGE . TEMPS : objet TABLE contenant en indice
        les instants du sequencage de
        l'apport de matiere (0 a N)

        . EVOLUTION_MAILLAGE . MAILLAGE : objet TABLE contenant en indice
        les maillages actives aux instants
        definis a l'indice TEMPS

        . EVOLUTION_MAILLAGE . TEMPS . i : objet FLOTTANT, (i+1)eme instant
        de la sequence

        . EVOLUTION_MAILLAGE . MAILLAGE . i : objet MAILLAGE, maillage
        a l'instant correspant
        de la table des TEMPS

    TAB2 . TEMPS_CALCULES : objet LISTREEL, liste des temps de calculs
        fournie par l'option TEMP.

    TAB2 . TEMPS_EVENEMENTS : objet LISTREEL, liste des instants relatifs
        aux evenements, s'il y en a de defini.

    TAB2 . INDEX_EVENEMENTS : objet LISTENTI, liste des numeros des evenements
        associes aux instants de la liste ci-dessus.

    Remarque : dans la liste des TEMPS_CALCULES, le pas de temps est deraffine
    ---------- progressivement selon une suite geometrique de raison 2 lorsque
        la puissance thermique est a 0 (deplacement ou pause).

CHAP{Option VISU}

    Syntaxe :

    WAAM TAB2 'VISU' | (CACH) | (GEO2) ;
        | (FACE) | ;

    Commentaire :

     CACH : visualisation avec option CACH de TRAC

     FACE : visualisation avec option FACE de TRAC

     GEO2 : objet MAILLAGE ajoute aux maillages visualises

## WEIBULL [Mecanique Rupture] (proc)
Procedure WEIBULL

PR1 CHEL1 = WEIBULL SIG1 MO1 KV SIGU SIG0 M ;

Objet:

Calcul de la probabilite de rupture selon la statistique
de Weibull et le principe des actions indipendantes (PIA).

En entree:

  SIG1 : MCHAML de type CONTRAIN de contraintes.

  MO1 : Objet MMODL associe a SIG1

  KV : Coefficient corretif de volume en cas de
        calculs planes et/ou possibles symmetries.

  SIGU : Containte limite (nulle pour les materiaux
        ceramiques).

  SIG0 : Containte de normalisation.

  M : Puissance ou Module de Weibull.

En sortie:

  PR1 : Probabilite de rupture.

  CHEL1: MCHAML qu'on integre.

## WEIP [Mathematiques Statistiques]
Operateur WEIP

M SIG0 = WEIP LREEL1 D1 D2 A1 ;

Objet:

Cet operateur calcule les parametres M (module de Weibull)
et SIG0 (sigma-zero) relatifs a une distribution statistique
de Weibull.

En entree:

LREEL1 : Liste des valeurs de la contrainte de ruptur
        obtenu experimentalement avec des essais a
        flexion a 4 points sur un'eprouvette.

D1 : distance entre les appuis de l'eprouvette.

D2 : distance entre les charges appliquees.

A1 : Surface de la section de l'eprouvette.

        D2
        |<---------->|
        P/2 |  | P/2
        --------|------------|--------------
        /  v  v  /|
       /  / |
      ------------------------------------  |
      |  |A1|
      |  | /
      |  |/
        /\ /\
        |  D1  |
        |<---------------------->|

## WORK [Mecanique Resolution]
   Operateur WORK

   WORK1 = WORK MODL1 SIG1 GRAD1 (GRAF1) ;

   Objet :

   L'operateur WORK calcule la trace de produit tensoriel
   contracte d'un champ de contraintes SIG1 avec un champ
   de gradients GRAD1 (et facultativement un champ de gradients
   de flexion GRAF1 pour les elements coques), i.e.

        WORK1 = Tr (SIG1 * GRAD1)

   Commentaire :

    MODL1 : objet modele ( type MMODEL)

    SIG1 : champ de contraintes (type MCHAML,
        sous-type CONTRAINTES)

    GRAD1 : champ de gradients (type MCHAML )

    GRAF1 : champ de gradients de flexion (type MCHAML)

    WORK1 : objet de type MCHAML

  Remarque:

 Le champ de gradients de flexion( necessaire uniquement pour les
elements coques mince )est donne en derniere position .

## XBIF [Fluides Resolution] (proc)
   Procedure XBIF

  OBJET :

  Cette procedure resoud les equations d'un modele bifluide. Deux
  phases sont en presence: un gaz qui est le fluide porteur et des
  particules qui sont considerees comme un gaz (particulaire).

  Les principales hypotheses sont les suivantes:

       - les particules sont monodisperses, homogenes et spheriques

       - le fluide particulaire est tres dilue: sa fraction
        volumique est tres inferieure a un et on approxime
        la fraction volumique du fluide porteur par un

       - le fluide porteur est incompressible

       - le gradient de pression exerce sur chacune des phases
        est le meme a un facteur de proportionnalite pres: le
        rapport des masses volumiques du gaz porteur et du solide

       - le couplage des deux phases apparait dans leurs
        equations de quantite de mouvement par un terme de
        transfert interfacial qui n'est autre que la trainee
        de Stokes ou une formule contenant un coefficient de
        trainee; le terme de couplage est de la forme
        +/-K*(U-V) ou U et V sont les vitesses respectivement
        du gaz porteur et des particules

  Le systeme a traiter comprend deux equations de conservation: masse
  et quantite de mouvement pour chacune des phases. Il y a donc quatre
  equations a quatre inconnues: les vitesses du gaz porteur et du
  gaz particulaire, la pression totale et la fraction volumique en
  particules.

  Les equations a resoudre sont les suivantes:

   | alphf = 1 ; div(U) = 0
   |
   | dU/dt + (U.div)U = -grad(P)/rof + nuf*lapl(U) - Kf*(U-V)
   |
   | dV/dt + (V.div)V = -grad(P)/rop + nup*lapl(U) + Kp*(U-V)
   |  + (1-rof/rop)*g
   |
   | d(alphp)/dt + div(alphp*V) = 0

  avec: rof masse volumique du gaz porteur
        rop masse volumique du solide
        nuf viscosite cinematique du gaz porteur
        nup viscosite cinematique des particules
  (ces quatre proprietes pysiques sont supposees constantes)

        Kf coefficient de couplage du gaz porteur
        Kp coefficient de couplage des particules

        alphf fraction volumique du gaz porteur
        alphp fraction volumique du gaz particulaire
        U vitesse du gaz porteur
        V vitesse du gaz particulaire
        P pression totale

1/ On resoud le systeme couple des equations de quantite de
  mouvement (qui sont des equations de Navier-Stokes) a partir
  des algorithmes semi-implicites de deux operateurs NS associes
  a chacune des equations.
  Le fluide porteur est incompressible ce qui est le moyen
  d'obtenir la pression qui est commune aux deux phases.
  Le couplage entre l'equation de quantite de mouvement du gaz porteur
  et celle des particules est traite de facon explicite. C'est une
  limite numerique du modele: le couplage ne peut pas etre
  extremement fort (tres petites particules). Si tel doit etre
  le cas, autant conclure au non-glissement interphasique et alors
  les vitesses des deux gaz sont egales.

  Les informations sont donnees dans une table de type EQEX (creee
  par EQEX). Cette table doit posseder une entree 'PRESSION'
  contenant une table de type EQPR (creee par EQPR) ou figurent les
  informations liees a l'equation de pression et a sa resolution.
  Enfin la table doit contenir une entree 'KIZT', table cree
  par l'utilisateur et contenant les CHAMPOINT-TRIO.

2/ On resoud l'equation de conservation de la masse de particules
  a l'aide de l'operateur KONV suivant les informations donnees
  dans une table de type EQEX (creee par EQEX).

  Voir les operateurs EQEX, EQPR, NS et KONV.

  SYNTAXE :

     XBIF Tab1 Tab2 Tab3 Flo1 Flo2 ;

   Tab1 est une table de type EQEX (2 equations de
        quantite de mouvement)
   Tab2 est une table de type EQPR (pression)

   Tab3 est une table de type EQEX (continuite particules)

   Flo1 est un flottant (coefficient de couplage du
        gaz porteur)
   Flo2 est un flottant (coefficient de couplage du
        gaz de particules)

  REMARQUES :

    1/ L'utilisateur peut trouver en guise d'exemple un jeu de
    donnees avec un appel a XBIF. C'est xbif.dtc.

    2/ Noter que dans l'etat actuel de la modelisation ne figurent
    pas encore de termes liees a la turbulence.

## XFEM [Post-traitement Analyse]
   Operateur XFEM

   Objet :

   L'operateur XFEM permet de post-traiter les resultats obtenus
avec un modele utilisant la formuation XFEM.

   | 1ere possibilite :  |
   |  reconstitution de champ de deplacement physique |

   CHPO2 = XFEM 'RECO' CHPO1 MOD1 ;
   CHPO2 CHPO3 = XFEM 'RECO' CHPO1 MOD1 MAIL2;

   Objet :

  L'operateur XFEM avec le mot-cle 'RECO' reconstruit le deplacement
 physique a partir des inconnues de deplacement classique et de
 celles associees aux enrichissements.

   Commentaire :

   CHPO1 : champ de deplacement avec inconnues XFEM (UX, AX, B1X..)
        (type CHPOINT)

   MOD1 : Modele contenant au moinsune sous-zone XFEM (type MODELE)

   CHPO2 : Champ de deplacement physique (UX, UY, UZ) (type CHPOINT)
   CHPO3 : "

   MAIL2 : Support de CHPO2 et CHPO3 si different des noeuds de CHPO1

   | 2eme possibilite : Calcul du deplacement sur la fissure |

   CHPO2 CHPO3 = XFEM 'FISS' GEO1 CHPO1 MOD1

   Objet :

 L'operateur XFEM avec le mot-cle 'FISS' construit les champs de
deplacements physiques sur le maillage de la fissure. Ces champs
sont utiles pour tracer l'ouverture de la fissure.

   Commentaire :

   GEO11 : Support geometrique de la fissure (type MAILLAGE)

   CHPO1 : champ de deplacement avec inconnues XFEM (UX, AX, B1X..)
        (type CHPOINT)

   MOD1 : Modele contenant au moins une sous-zone XFEM (type MODELE)

   CHPO2 : Champ de deplacement levre superieure (type CHPOINT)

   CHPO3 : Champ de deplacement levre inferieure (type CHPOINT)

## XTMX [Mathematiques Autres]
    Operateur XTMX

    FLOT1 = XTMX CHPO1 RIG1 ;

    Objet :

    L'operateur XTMX calcule l'application de la forme quadratique
associee a une rigidite et a un champ par points.

    Commentaire :

    CHPO1 : champ par points (type CHPOINT)

    RIG1 : matrice de rigidite (type RIGIDITE)

    FLOT1 : objet resultat (type FLOTTANT)

    Remarque :
    La regle de transposition associant les inconnues primales de X
    et duales de MX utilise les noms definis dans bdata (CCHAMP)
    (on calcule donc implicitement : UX*FX + UY*FY + ...).
    L'utilisation d'une autre regle passe par une syntaxe du type :
    flot1 = XTY chpo1 (Rig1 * chpo1) lmot1 lmot2;
    ou lmot1 et lmot2 sont des LISTMOTS definis par l'utilisateur.

## XTX [Mathematiques Autres]
    Operateur XTX

    FLOT3 = XTX  | CH1  |  ;
        |  |
        | FLOT1 CH1  FLOT2 CH2 |

    Objet :

    L'operateur XTX calcule la norme d'un champ ou celle d'une combinai-
son lineaire de deux champs de meme type.

    Commentaire :

    CH1 |  : champs a normer (type  MCHAML ou CHPOINT)
    CH2 |

    FLOT1 | : coefficients multiplicatifs (type FLOTTANT)
    FLOT2 |

    FLOT3 : norme du champ CH1 (type FLOTTANT)

    Remarque :

    Cette norme est la somme des carres de toutes les composantes
en tous points. Le resultat FLOT3 est de type FLOTTANT.

## XTY [Mathematiques Autres]
    Operateur XTY

    FLOT1 = XTY CHPO1 CHPO2 LMOTS1 LMOTS2 ;

    LREE11 = XTY LICHP1 LICHP2 LMOTS1 LMOTS2 ;

    Objet :

    L'operateur XTY calcule le produit scalaire de deux champs en
  faisant la somme des produits terme a terme de certaines composantes.
   L'operateur calcule les produits scalaires pour 2 champs de
  meme indice pris dans des listes et forme ainsi une suite de reels

    Commentaire :

    CHPO1 : objet de type CHPOINT

    CHPO2 : objet de type CHPOINT

   LICHP1, LICHP2 : objet de type LISTCHPO

    LMOTS1 : liste des noms de composantes de CHPO1 a prendre en
        compte (type LISTMOTS).

    LMOTS2 : liste des noms des composantes de CHPO2 correspondantes
        (type LISTMOTS)

    FLOT1 : produit scalaire (type FLOTTANT)

    LREE1 : type LISTREEL

    Exemple :

    Pour faire le produit F * U en dimension 3, on utilisera les
noms de composantes : UX UY UZ et FX FY FZ .

    ATTENTION :

    Les deux LISTMOTS doivent etre de meme longueur.

## XXT [Mathematiques Autres]
   Operateur XXT

   RIG1 = XXT CH1 (FLOT2);

   Objet :

   L'operateur XXT calcule la matrice de rigidite RIG3 (objet de type
RIGIDITE) a partir du produit tensoriel du champ par point CH1 (objet
de type CHPOINT) par lui meme, pondere eventuellement par FLOT2 (objet
de type flottant).

   Remarque :

- Le maillage support de RIG1 est un unique superelement construit
   a partir des noeuds du maillage sous-tendant CH1.

- Pour ne pas perturber le fonctionnement de l'operateur RESO
   (resolution de systeme lineaire), CH1 ne doit comporter qu'une
   seule zone, et des composantes homogenes a des forces (voir le
   manuel de l'operateur FORC).

- RIG1 est de sous-type 'RIGIDITE'.

## YTMX [Mathematiques Autres]
    Operateur YTMX

    FLOT1 = YTMX CHPO1 CHPO2 RIG1 ;

    Objet :

    L'operateur YTMX calcule l'application de la forme bilineaire
associee a une rigidite et a deux champs par points.

    Commentaire :

    CHPO1 : champ par points (type CHPOINT)

    CHPO2 : champ par points (type CHPOINT)

    RIG1 : matrice de rigidite (type RIGIDITE)

    FLOT1 : objet resultat (type FLOTTANT)

    Dans le cas de matrices non-symetrique l'ordre des champs par
 points est important. L'operateur effectue l'operation :

    CHPO2(transpose)*RIG1*CHPO1

    Remarque :
    La regle de transposition associant les inconnues primales de Y
    et duales de MX utilise les noms definis dans bdata (CCHAMP)
    (on calcule donc implicitement : UX*FX + UY*FY + ...).
    L'utilisation d'une autre regle passe par une syntaxe du type :
    flot1 = XTY chpo2 (Rig1 * chpo1) lmot1 lmot2;
    ou lmot1 et lmot2 sont des LISTMOTS definis par l'utilisateur.

## ZERO [Mathematiques Autres]
    Operateur ZERO

      CHAM1 = ZERO MODL1 MOT1 ;

    Objet :

    L'operateur ZERO permet de creer un champ par element dont les
composantes sont toutes nulles.

      Commentaire:

      MODL1 : objet modele ( type MMODEL ).

      MOT1 : objet de type MOT, de 8 caracteres, definissant le nom d
        sous-type du champ par element a creer, choisi parmi :

        'NOEUD ' : scalaire aux noeuds

        'GRAVITE ' : scalaire au centre de gravite

        'RIGIDITE' : scalaire aux points d'integration de la
        raideur

        'MASSE ' : scalaire aux points d'integration de la
        masse

        'STRESSES' : scalaire aux points de contraintes

        'DEPLACEM' : deplacements

        'FORCES ' : forces

        'GRADIENT' : gradient

        'CONTRAIN' : contraintes

        'DEFORMAT' : deformations

        'MATERIAU' : materiaux

        'CARACTER' : caracteristiques

        'TEMPERAT' : temperatures

        'PRINCIPA' : contraintes principales

        'MAHOOKE ' : matrice de Hooke

        'HOTANGEN' : matrice de Hooke tangente

        'VARINTER' : variables internes

        'DEFINELA' : deformations inelastiques

      CHAM1 : champ par elements cree (type MCHAML)

## ZIGZAG [Maillage Lignes] (proc)
    Procedure ZIGZAG

    GEO1 = ZIGZAG POIN0 V1 V2 N1 'D' LONG1 'S' LONG2 'R' RAY1 ... ;
ou
    GEO1 = ZIGZAG POIN0 V1 V2 N1 'D' LONG1 'A' ANGL1 'R' RAY1 ... ;
ou
    GEO1 = ZIGZAG POIN0 V1 V2 'DINI' DENS1 'DFIN' DENS2 'D' LONG1 ... ;

    Objet :

    La procedure ZIGZAG permet de construire une ligne definie par une
succession de parties droites (D) et arrondies (S,R) ou (A,R).

    Commentaires :

    POIN0 : point initial de la ligne (type POINT).

    V1 : vecteur tangent a la ligne en POIN0 (type POINT).

    V2 : deuxieme vecteur (type POINT), necessaire pour definir
        le plan contenant la ligne. Ce plan est oriente par le
        produit vectoriel N = V1 ^ V2.

    N1 : nombre d'elements souhaite (type ENTIER).

    DENS1 | : densites associes au point initial et au point final
    DENS2 |  de la ligne (type FLOTTANT).

    LONG1 : longueur de la partie rectiligne a creer (type FLOTTANT).

    LONG2 : longueur de la partie courbe a creer (type FLOTTANT)
        (comptee positivement dans le sens de la normale N).

    ANGL1 : angle en degre de la partie courbe (type FLOTTANT)
        (compte positivement dans le sens de la normale N).

    RAY1 : rayon de la partie courbe (type FLOTTANT).

    GEO1 : ligne creee (type MAILLAGE).

    Remarques :

     1/. POIN0 doit etre le premier argument suivi de V1, puis de V2.
     2/. Il y a un noeud aux extremites de chaque ligne elementaire.
     3/. Si N1 est specifie, N1 elements environ de longueur voisines
        seront engendres.
     4/. Si les densites DENS1 et DENS2 sont specifiees, la taille des
        elements sera calculee en tenant de ces valeurs.

## ZLEG [Mathematiques Fonctions]
Operateur ZLEG

LREE1 LREE2 = ZLEG ENT1;

objet :

Operateur ZLEG calcule les zeros et les poids de la derivee
du polynome de Legendre dans l'interval normalise (-1, +1).

ENT1 est le degre du polynome. Il y a ENT1 + 1 points

LREE1 listreel contenent les ENT1 + 1 coordonnees des
      points (normalise dans l'interval (-1, +1)).

LREE2 listreel contenent les ENT1 + 1 poids de Gauss-Lobatto

## ZONFIS [—] (proc)
Section Rupture Rupture

    Procedure ZONFIS

    Objet :

MECANIQUE :

  Une procedure permet d'effectuer un calcul de l'ouverture de fissure
  dans le cas complexe suivant le trajet de fissure. La fissure s'ouvre
  perpendiculairement au trajet de fissure. L'ouverture de fissure
  prend en compte les microfissures autour d'une fissure principale.

  Cette procédure est composée de trois procedures qui réalise
  les calculs dans l'ordre suivant :

  - initou: permet de positionner les points de fissure
  - zonfis: permet de detecter visuellement une zone de fissure
  - postou: permet de caculer l'ouverture de fissure

  La procedure zonfis permet de detecter visuellement une zone de fissure.

   Description :

L'entree pour zonfis:
Voici la liste :

    TAB1.DROI LOGIQUE : pour ajuster la zone de fissure
    OBJET1 ENTIER : numero de colonne de partie haute
    OBJET2 ENTIER : numero de colonne de partie basse
    OBJET3 ENTIER : numero de ligne de partie haute
    OBJET4 ENTIER : numero de ligne de partie basse
    OBJET5 FLOTTANT : limite haute de la grille
    OBJET6 FLOTTANT : limite basse de la grille
    OBJET7 FLOTTANT : ajustement de translation gauche
    OBJET8 FLOTTANT : ajustement de translation droite
    OBJET9 FLOTTANT : ajustement en bas gauche ou droite

La sortie pour zonfis:

    TAB1.ZONE liste des points d'ajustement
