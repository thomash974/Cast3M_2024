# Notices Gibiane complètes (français), partie 2/3 : ENCEINTE à PMPB

Texte des notices `INFO`, sans décorations, sans colonne « voir aussi » ni section anglaise. Chaque notice commence par `## NOM [section]`.

## ENCEINTE [Fluides Resolution] (proc)
    Procedure ENCEINTE

      ENCEINTE NDT RXT ;

    Commentaires

    NDT ENTI1 : nombre de pas de temps
    RXT TAB1 : table contenant les informations permettant de calculer
        l'evolution de la composition d'un melange gazeux dans
        une enceinte fermee

    OBJET :

  La procedure ENCEINTE calcule, a partir d'un etat initial, l'evolution
 au cours du temps d'un melange gazeux dans une enceinte fermee.

CHAP{Generalites}

  L'etat initial est uniforme en espace lorsqu'il est donne par
 l'utilisateur, issu d'un calcul precedent sinon.

  L'air est toujours present dans le melange gazeux. Il peut aussi contenir un
 ou plusieurs des constituants suivants: vapeur d'eau, H2, N2, He, O2, CO et
 CO2. Les gaz incondensables sont modelises par la loi des gaz parfaits. C'est
 aussi le choix par defaut de la vapeur (version V0), un modele gaz reel etant
 en test (version V1).

  En presence de vapeur la condensation en paroi peut apparaitre si les
 conditions locales sont reunies (Pvap > Psat). Le modele de condensation est
 de type Chilton-Colburn et associe a une correlation d'echange de type
 convection naturelle le long d'une plaque plane verticale.

  On distingue 4 types de conditions aux limites suivant la nature de la
 frontiere du domaine fluide : zones d'injection (breches), ventilation forcee
 et clapet de decharge (sorties), parois thermiques et parois inertes :

  - sur les zones d'injection ou breches, on impose des conditions aux limites
 de type valeur imposee pour la vitesse, la temperature du melange, la densite
 du melange et de ses constituants. Il faut donc y preciser le debit massique
 de chaque constituant du melange (kg/s) et la temperature d'entree (oC) (voir
 entree 'scenario' des Breches) ;

  - sur les sorties, on impose un debit (ventilation) et on precise les
 parametres de la perte de charge (clapet de decharge) (voir entree 'scenario'
 des Sorties) ;

  - sur les parois thermiques, la vitesse est nulle (suf si fonction de paroi
 (entree FPAROI)) et la temperature evolue au cours du temps (entree TIMP), est
 a priori constante (entree ECHANP), le resultat d'un calcul de thermique paroi
 (entree THERMP). Pour ce dernier cas, il est possible de coupler la resolution
 des equations de l'enrergie paroi et fluide de façon implicite (entree
 THERCO). En presence de vapeur les parois thermiques sont susceptibles de
 condenser. Elles sont par contre impermeables pour tous les incondensables.

  - sur les parois inertes, la vitesse est nulle, et elles sont impermeables
 pour toutes les autres inconnues (temperature, vapeur et gaz incondensables).
 Les parois inertes correspondent au maillage obtenu par difference entre
 l'enveloppe du volume fluide et les parois, breches et sorties.

 Par suite, les conditions aux limites sont correctement definies.

  La turbulence des mouvements de gaz est modelisee soit par une viscosite
 tourbillonnaire constante, soit par un modele de longueur de melange soit par
 un modele K-epsilon (entree MODTURB). En absence de l'entree MODTURB,
 l'ecoulement est laminaire.

  Un modele d'aspersion est disponible.

  Un modele de condensation en masse est en test.

  Au moyen du fichier d'extension dgibi, l'utilisateur transmet a CAST3M les
 donnees du scenario etudie. Regroupees dans la table notee RXT a differents
 indices qui sont precises dans cette notice, le transitoire est alors calcule
 par la procedure ENCEINTE avec la table RXT et le nombre de pas de temps ndt
 en donnees d'entree :

   ENCEINTE ndt rxt ;

  La table RXT est completee au moment de l'execution par trois tables :
  - la sous table rxt.'GEO' contient les modeles et objets geometriques crees a
 partir des donnees fournies.
  - la sous table rxt.'TBT' est la table de travail proprement dite et contient
 les autres objets crees necessaires au calcul hormis les inconnues.
  - la sous table rxt.'TIC' contient les inconnues au dernier temps connu
 (temps calcule ou condition initiale) ainsi que les champs variables en temps.

 Les entrees de RXT fournis par l'utilisateur ne sont donc pas modifiees.

 Les indices de RXT sont les presentes ci-dessous.

CHAP{Objets geometriques}

 rxt . 'vtf' = GEO1 ; maillage fluide (OBLIGATOIRE)
 rxt . 'pi' = POI1 ; point interieur du domaine fluide ou sera imposee
        la pression (OBLIGATOIRE).
 rxt . 'axe' = GEO2 ; axe de revolution si 2D AXI
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ENER [Mecanique Resolution]
    Operateur ENER

      CHAM3 = ENER MOD1 CHAM1 CHAM2 ;

    Objet :

    L'operateur ENER calcule le produit tensoriel contracte d'un champ
de contraintes avec un champ de deformations .
    Le resultat est un champ scalaire qui represente une densite
d'energie.

      Commentaire :

       MOD1 : objet modele (type MMODEL)

       CHAM1 : objet de type MCHAML de sous-type CONTRAINTES ou
        DEFORMATIONS

       CHAM2 : objet de type MCHAML de sous-type DEFORMATIONS ou
        CONTRAINTES

       CHAM3 : objet de type MCHAML de sous-type SCALAIRE

## ENERMODE [Post-traitement Affichage] (proc)
    Procedure ENERMODE

    ENERMODE TBAS TRESD (TINIT) (LOG1);

    Objet :

    Cette procedure permet de tracer les evolutions temporelles du travail
des forces exterieures, des forces interieures et des forces d'inertie,
ainsi que l'evolution temporelle du bilan energetique pour un calcul
explicite effectue sur base modale avec l'operateur DYNE. Il est
necessaire d'avoir demande la sortie du 'TRAVAIL_EXTERIEUR' et du
'TRAVAIL_INTERIEUR' dans DYNE.

    Commentaire :

    TBAS : table de soustype 'BASE_MODALE' ou 'ENSEMBLE_DE_BASES'
    TRESD : table resultat de l'operateur DYNE ou table indicee de 1 a N
        contenant N tables resultats de l'operateur DYNE
    TINIT : table de conditions initiales de l'operateur DYNE (facultatif)
    LOG1 : logique (facultatif). Si il est vrai les evolutions sont
        tracees pour chaque mode. Dans le cas contraire seulement
        les evolutions correspondantes a la somme de la contribution
        de tous les modes sont tracees.

## ENLE [Langage Objets]
    Operateur ENLEVER
    ----------------- OTER OUBL

        OBJET2 = ENLEVER OBJET1 (MOT_CLE) INDIC1 ;

    Objet :

    L'operateur ENLEVER cree OBJET2 en enlevant le ou les elements
    d'indice(s) INDIC1 dans l'objet OBJET1.

    Operations possibles :

   |  OBJET1  |  MOT_CLE  |  INDIC1  |  OBJET2  |
   |________________|________________|________________|________________|
   |  LISTREEL  |  AUCUN  |  ENTIER  |  LISTREEL  |
   |  LISTREEL  |  AUCUN  |  LISTENTI  |  LISTREEL  |
   |  LISTENTI  |  AUCUN  |  ENTIER  |  LISTENTI  |
   |  LISTENTI  |  AUCUN  |  LISTENTI  |  LISTENTI  |
   |  LISTMOTS  |  AUCUN  |  ENTIER  |  LISTMOTS  |
   |  LISTMOTS  |  AUCUN  |  LISTENTI  |  LISTMOTS  |
   |  LISTCHPO  |  AUCUN  |  ENTIER  |  LISTCHPO  |
   |  LISTCHPO  |  AUCUN  |  LISTENTI  |  LISTCHPO  |
   |  CHPOINT  |  AUCUN  |  MOT  |  CHPOINT  |
   |  CHPOINT  |  AUCUN  |  LISTMOTS  |  CHPOINT  |
   |  TABLE  |  AUCUN  |  (quelconque)  |  TABLE  |
   |  CHARGEME  |  AUCUN  |  MOT  |  CHARGEMENT  |
   |  MMODEL  |  'FORM'  |  MOT  |  MMODEL  |
   |  MMODEL  |  'COMP'  |  MOT  |  MMODEL  |

    Remarques :

    Dans le cas ou OBJET1 est une liste (LISTENTI, LISTREEL, LISTMOTS,
    LISTCHPO), les indices contenus dans INDIC1 correspondent aux
    positions des elements de OBJET2 avant toute suppression. Si un
    nombre est present plusieurs fois dans la liste INDIC1, l'element
    correspondant de OBJET1 ne sera donc elimine qu'une seule fois.
    Attention a bien respecter l'ordre des operandes si deux LISTENTI
    sont fournis.

    Dans le cas ou OBJET1 est un objet de type CHPOINT, INDIC1 (types
    MOT ou LISTMOTS) contient des noms de composantes.

    Dans le cas d'une TABLE, il faut veiller a respecter l'ordre des
    operandes (OBJET1 puis INDIC1).

    Dans le cas d'un CHARGEMENT, INDIC1 (type MOT) correspond au type
    du chargement a enlever.

    Dans le cas ou OBJET1 est un MMODEL, un mot cle est attendu.
    MOT_CLE doit etre
      FORM : on enleve du MMODEL les regions pour lesquelles la
        formulation est celle indiquee par INDIC1.
    OR
      COMP -> on enleve du MMODEL les regions pour lesquelles le
        comportement est celui indique par INDIC1.
    Si INDIC1 ne correspond a aucune formulation ou comportement ou
    dans le cas d'un MMODEL vide, OBJET2 = OBJET1.

$$$$

## ENRICHIS [Mathematiques Traitement] (proc)
Procedure ENRICHIS

EVOL1 = ENRICHIS EVOL2 ENTI1;

objet :

Permet la generation d'un signal EVOL1 (comportant N courbes) a
partir d'un signal EVOL2 (comportant N courbes) sur une grille
2**ENTI1 fois plus riche, sans modifier son contenu en frequence
(au sens d'une transformee en ondelette). On utilise la procedure
RECOMPOS.

## ENSE [Mecanique Resolution]
   Operateur ENSEMBLE

   SOL1 = ENSEMBLE RIG1 ;

   Objet :

   L'operateur ENSEMBLE cree un objet SOL1 de type SOLUTION, contenant
les modes d'ensembles associes a la matrice de rigidite RIG1 (type
RIGIDITE)

   Exemple :

   Soit RRR la RIGIDITE d'une structure avec ses blocages, et MAILLA
le maillage; supposons que la structure ait deux modes rigides,
il est possible de les visualiser par la sequence suivante :

        MMM = ENSE RRR;
        DE1 = TIRER MMM DEPL RANG 1;
        DE2 = TIRER MMM DEPL RANG 2;
        DEFO1 = DEFORME DE1 MAILLA 2.5 ROUGE;
        DEFO2 = DEFORME DE2 MAILLA 4.5 VERT ;
        TRAC ( DEFO1 ET DEFO2 ) ;

## ENTI [Mathematiques Fonctions]
Operateur ENTIER

        OBJ2 = ENTI (|'TRONCATURE'|) OBJ1 ;
        |'INFERIEUR' |
        |'SUPERIEUR' |
        |'PROCHE'  |

Objet :

L'operateur ENTIER convertit un objet OBJ1 a valeurs reelles vers
un objet OBJ2 a valeurs entieres.

Les conversions possibles sont : FLOTTANT => ENTIER
        LISTREEL => LISTENTI
        CHPOINT => CHPOINT
        MOT => ENTIER
        LISTMOTS => LISTENTI

Un mot-cle peut preciser la maniere dont on desire effectuer la
conversion :

a) TRONCATURE (par defaut) : fonction troncature ("fix")
   => ENTI1 correspond a la troncature de FLOT1, c'est-a-dire les
      chiffres places avant le separateur decimal

b) INFERIEUR : fonction plancher ("floor")
   => ENTI1 est le plus grand entier inferieur ou egal a FLOT1

c) SUPERIEUR : fonction plafond ("ceiling")
   => ENTI1 est le plus petit entier superieur ou egal a FLOT1

d) PROCHE : fonction arrondi ("round")
   => ENTI1 est l'entier le plus proche de FLOT1

Remarques :

1) La fonction "partie entiere", d'un point de vue mathematique,
   correspond a l'option 'INFERIEUR'. La "partie fractionnaire"
   d'un nombre FLOT1, toujours d'un point de vue mathematique, est
   par consequent egale a FLOT1 - (ENTI 'INFERIEUR' FLOT1)

2) Les operations de troncature ci-dessous sont equivalentes :
     ENTI1 = ENTI 'TRONCATURE' FLOT1 ;
     ENTI1 = (SIGN FLOT1)*(ENTI 'INFERIEUR' (ABS FLOT1)) ;

3) Les operations d'arrondi ci-dessous sont equivalentes :
     ENTI2 = ENTI 'PROCHE' FLOT1 ;
     ENTI2 = (SIGN FLOT1)*(ENTI 'INFERIEUR' ((ABS FLOT1) + 0.5)) ;

4) Pour l'option 'PROCHE', le cas ou la partie fractionnaire de
   ENTI1 vaut 0.5 est indetermine. Le resultat est alors l'entier
   de meme signe et de valeur absolue directement superieure a
   FLOT1, autrement dit :
   - le plus petit entier superieur a FLOT1 si FLOT1 > 0
   - le plus grand entier inferieur a FLOT1 si FLOT1 < 0

5) Lors de la conversion d'un objet CHPOINT, toutes les composantes
   sont prises en compte. Apres l'operation, ses valeurs sont des
   reels (REAL, au sens informatique) dont la partie fractionnaire
   est nulle.

6) Pour que la conversion depuis un objet de type MOT ou LISTMOTS
   soit possible, les mots doivent contenir des nombres (entiers
   ou reels) sous un format standard. La conversion suit alors les
   regles enoncees ci-dessus.

Exemples :

        | TRONCATURE  INFERIEUR  SUPERIEUR  PROCHE  |
        8  |  8  8  8  8  |
      0.5  |  0  0  1  1  |
     -3.5  |  -3  -4  -3  -4  |
     5.21  |  5  5  6  5  |
     -4.9  |  -4  -5  -4  -5  |
    -2.05  |  -2  -3  -2  -2  |

=> voir le cas-test 'conversion_enti.dgibi'
   (il contient notamment une representation graphique des quatre
    fonctions disponibles)

## ENUM [Langage Base]
    Operateur ENUMERER
    ------------------ MOTS

CHAP{Definir une liste d'objets}
      LOBJ1 = ENUM OBJ1 OBJ2 ... ;

    Objet :

    L'operateur ENUMERER permet de creer une liste d'objets de
    meme type. Les types d'objets supportes sont :

     MAILLAGE, LISTENTI, POINT , LISTREEL, CHPOINT , RIGIDITE,
     STRUCTUR, ATTACHE , SOLUTION, BASEMODA, LISTOBJE, VECTDOUB,
     LISTMOTS, DEFORME , LISTCHPO, CHARGEME, EVOLUTIO, VECTEUR ,
     TABLE , ELEMSTRU, BLOQSTRU, MCHAML , MMODEL , NUAGE ,
     MATRIK , OBJET , ESCLAVE , ANNOTATI, ENTIER.

    La liste cree respecte l'ordre d'enumeration.

    Commentaire :

    OBJ1, OBJ2 : objets de meme type.

    LOBJ1 : objet LISTOBJE, liste des objets enumeres.

CHAP{Créer une liste composée de N1 fois le meme objet}

      LOBJ1 = ENUM N1*OBJ1 ;

    Objet :

    Cette option crée une liste composée de N1 fois l'objet OBJ1.

    Commentaire :

    N1 : objet ENTIER ;

    OBJ1 : objet de la liste.

CHAP{Créer une liste d'objets donnés dans une table}

      LOBJ1 = ENUM 'TABL' TAB1 ;

    Objet :

    L'option TABLe permet de créer une liste d'objets a partir
    d'objets indicés dans une table par des entiers. Tous les
    objets doivent etre du même type.

    Commentaire :

    TAB1 : objet TABLE contenant des objets de même type
        indicés par des entiers.

    LOBJ1 : objet LISTOBJE contenant les objets en question.

    Remarque : si TAB1 contient d'autres types d'indice, MOT
    ---------- ou autre, ceux-ci sont ignores.

## ENVE [Maillage Surfaces]
Operateur ENVELOPPE

Objet :

L'operateur ENVELOPPE a deux fonctions differentes :

| 1ere fonction |

SURF1 = ENVELOPPE VOLU1 ('ORIE') ('NOID') ;

Objet :

L'operateur ENVELOPPE fabrique l'enveloppe SURF1 (type MAILLAGE)
du volume VOLU1 (type MAILLAGE), c'est-a-dire conventionnellement
l'ensemble des faces de ce volume qui n'appartiennent qu'a un
seul element.

En présence du mot-clé 'ORIE', les faces des elements sont orientées
vers l'intérieur du volume. Toutefois, pour obtenir le meme effet,
on conseille d'orienter prealablement le volume avec l'operateur
ORIE puis d'utiliser ENVE sans le mot-cle ORIE.

Remarque :

En presence du mot cle NOID, si l'enveloppe est vide,
un maillage vide est créé. Sinon, il y a une erreur.

| 2eme fonction |

TAB1 = ENVELOPPE TAB2 ;

Objet :

L'operateur ENVELOPPE fabrique le spectre enveloppe d'une serie
de spectres d'oscillateurs.

Commentaire :

TAB2 : objet de type TABLE contenant autant de tables que
        de spectres d'oscillateurs. Ces tables sont indicees
        par un numero de 1 a N.

La k-ieme table contient :

en indice 'SPECTRE' : k-ieme spectre (type EVOLUTION).

en indice 'AMORTISSEMENT' : les amortissements pour chaque
        courbe du k-ieme spectre (type
        LISTREEL).

TAB1 : objet de type table contenant le spectre ENVELOPPE,
        indicee comme suit :

TAB1.'SPECTRE' : le spectre enveloppe (type EVOLUTION).

TAB1.'AMORTISSEMENT' : les amortissements pour chaque courbe
        du spectre (type LISTREEL).

## EPAIFUT [Mecanique Modele] (proc)
Procedure EPAIFUT
----------------- PHASAGE

  CHAM2 = EPAIFUT MAIL1 MAIL2 MAIL3;

Objet :

  Cette procedure permet de calculer le rayon de sechage du beton
  a prendre en compte dans le BPEL ou l'Eurocode 2 pour les
  calculs de retrait ou de fluage differes. La structure en beton
  doit etre maillee en element volumiques et on doit fournir les
  surfaces internes et externes.

     MAIL1 : maillage volumique du beton.

     MAIL2 : maillage de la surface interne

     MAIL3 : maillage de la surface externe

## EPSI [Mecanique Resolution]
    Operateur EPSI
    -------------- ELAS HOOK

    1)  EPS1 = EPSI  | ('LINE') |  MODL1 DEP1 ( CAR1 ) (HOO1) ('NOER');
        |  'QUAD'  |
        |  'TRUE'  |
        |  'JAUM'  |
        |  'UTIL'  |

    2)  EPS1 = EPSI  MODL1  GRAD1  | ('GEOM') | ;
        |  'DEPL'  |

    Objet :

    Pour la syntaxe 1), le calcul des deformations se fait,
suivant la methode precisee par le mot cle.
    Par defaut, seuls les termes lineaires sont pris en compte.

    La syntaxe 2) permet de calculer un champ de deformations
en prenant le logarithme naturel d'un champ de gradient symetrique
( EPS = 1/2.ln(Ftrans.F) ).
    La seconde syntaxe ne fonctionne actuellement que pour la
formulation massive. Le champ de gradient F est :
- soit donne directement : F = GRAD1 (option 'GEOM', prise par defaut),
- soit determine a partir du gradient du champ de deplacement :
F = I + GRAD1 (option 'DEPL').

    Pour certains elements (poutres, tuyaux, coques minces avec
ou sans cisaillement transverse) il s'agit de deformations
generalisees, c'est-a-dire de deformations membranaires et de
variations de courbure. Pour les elements joints, il s'agit de
deplacements relatifs. Les deformations sont calculees dans le
repere general pour les elements massifs et dans le repere local
pour les elements coques, plaques et poutres.

    Commentaire :

      'LINE', 'QUAD', 'TRUE', 'JAUM' ou 'UTIL' :
        mot-cle specifiant l'hypothese de calcul des deformations
        (lineaire par defaut).

      MODL1 : objet modele (type MMODEL).

      DEP1 : champ de deplacements (type CHPOINT).

      CAR1 : champ de caracteristiques geometriques (type MCHAML,
        sous-type CARACTERISTIQUES) necessaire pour certains
        elements (poutres ,coques ...).
        Il contient egalement les caracteristiques materielles
        pour l'element coque DST dans l'absence du champ de
        matrices de Hooke.

      HOO1 : champ de matrices de Hooke (type MCHAML, sous-type
        MATRICE DE HOOKE) necessaire pour l'element coque DST
        si CAR1 ne contient pas les caracteristiques
        materielles

      'NOER' : mot-cle indiquant de ne pas faire d'erreur en cas de
        changement de signe du jacobien. Dans ce cas, en
        sortie EPS1 contient un entier non nul.

      GRAD1 : champ de gradient, symetrique (type MCHAML, sous-type
        GRADIENT).

      'GEOM' : mot-cle indiquant que le champ de gradient GRAD1 est
        associe a une transformation geometrique.
      'DEPL' : mot-cle indiquant que le champ de gradient GRAD1 est
        associe a un champ de deplacement.

      EPS1 : champ de deformations resultat (type MCHAML, sous-type
        DEFORMATIONS).

    Remarques :

1. Dans le cas des coques excentrees, les deformations sont calculees
    au niveau de la surface moyenne excentree

2. Dans le cas 2D contraintes planes, la deformation selon la direction
    perpendiculaire au plan n'est pas calculable. On la met egale a 0.

3. Le calcul des deformations du second ordre est implemente pour les
   elements suivants :
      - massifs : tous
      - lineiques : BARR POUT TUYA TIMO
      - plaques et coques : COQ2 DKT
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EPTH [Mecanique Resolution]
    Operateur EPTH

      EPS1 = EPTH MODL1 MAT1 CH1 ;

    Objet :

    L'operateur EPTH calcule les deformations d'origine thermique,
    a savoir :

        EPSTHER = ALPHA * (T - TALP)

    ou ALPHA est le coefficient de dilatation thermique secant entre
        la temperature de reference TALP et la temperature actuelle T

      Commentaire :

      MODL1 : Objet modele (type MMODEL)

      MAT1 : Champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES )

      CH1 : champ de temperature (type MCHAML, sous-type TEMPERATURES
        ou type CHPOINT). Pour les elements joints, seuls sont
        autorises les champs de temperature de type MCHAML. Le
        type CHPOINT est interdit pour les joints.

      EPS1 : champ de deformations (type MCHAML, sous-type CONTRAINTES)

    Remarque :

    EPS1 est le champ de deformations entre les temperatures TALP et T.
Pour obtenir le champ de deformations total entre TREF et T, il faut donc
retrancher le champ de deformations entre TALP et TREF, obtenu en appelant
EPTH avec le champ de temperature TREF et le champ de caracteristiques
materielles a TREF.

    Remarque :

    Pour les elements coques ,le champ de temperature doit avoir
trois composantes de noms : TINF ,T, et TSUP, designant respectivement
la temperature en peau inferieure ,en surface moyenne et en peau
superieure.

    Pour les autres elements, le champ de temperature doit avoir une
composante de nom : T.

    Remarque :

  Dans le cas des coques excentrees, les deformations thermiques sont
 calculees au niveau de la surface moyenne excentree

    Remarque :

  Dans le cas d'elements finis BBAR a interpolation lineaire, le
calcul des deformations thermique est affaiblie a l'ordre inferieur.

## EQEX [Multi-physique Multi-physique]
Operateur EQEX

Objet :

Cree une TABLE contenant les informations necessaires a la solution
solution explicite ou implicite d'une ou plusieurs E.D.P. effectuee
par la procedure EXEC.

Cette table est a completer par une table 'INCO' contenant les
inconnues.

On peut aussi ajouter des tables 'HIST' et 'INCO'.'HIST' pour
sauvegarder des historiques.

Syntaxe :

RV = EQEX (RV) -->--+
        |
+------<------<------+------<------<------<------<------+
|  |
v  (OPTIONS APPLIQUEES AUX OPERATEURS PLACES APRES)  |
|  ^
+---> ('OPTI' opt1 opt2 opt3 ...)  -->--+  |
        |  |
     +------<------<------<------<------+  |
     |  ^
     v  (OPERATEUR QUI SERA APPELE A CHAQUE P.D.T)  |
     |  |
     +---> 'ZONE' nomz 'OPER' nomo (arg1 arg2 ...) -->--+
     |  ('INCO' nom1 nom2 ...)  |
     ^ v
     |  |
     +-------<------<------<------<------<------<-------+
        |
        |
+------<------<------<------<------<------<------<------+
|
v (DEFINITION DES CONDITIONS AUX LIMITES)
|
+---> 'CLIM' inc1 comp1 mail1 val1 ...
        ... inc2 comp2 mail2 val2 ... -->--+
        |
        |
+------<------<------<------<------<------<------<------+
|
+---> ('ITMA' itma) ('NITER' nite) --->---+
        |  (PARAMETRES
+------<------<------<------<------<------+ TEMPORELS DE
|  LA SIMULATION)
+---> ('ALFA' alfa) ('OMEGA' omeg) --->---+
        |
        |
        v

        (autres directives parmi :
        DUMP FIDT NISTO
        NOMVI TPSI TFINAL )

Directive DUMP
Cette directive est utile pour la mise au point du jeu de donnees
=> on imprime le deroulement du decodage de EQEX

Directive ITMA
itma (ENTIER) : nombre maximum de pas de temps (defaut 1)

Directive ALFA
alfa (FLOTTANT) : tolerance (0. < alfa < 1.) sur le pas de temps
        (defaut 1.)

Directive FIDT
fidt (ENTIER) : frequence d'impression des pas de temps (defaut 20)

Directive NISTO
nisto (ENTIER) : frequence de sauvegarde de l'historique d'une
grandeur en un point dans la table RV.'HIST' (defaut 20)

Directive NOMVI
nomvi (MOT) : nom du champ de vitesse servant au calcul de la
pression pour l'algorithme semi-explicite (par defaut 'UN')

Directive TPSI
tpsi (flottant) : temps initial

Directive TFINAL
tfinal (flottant) : temps final (defaut 1.e30)

Directive NITER
niter (entier) : nombre d'iterations internes a un pas de temps
pour resoudre une non linearite (defaut 1)

Directive OMEGA
omega (flottant) : facteur de relaxation (0 < omega < 1) pour
resoudre une non linearite (defaut 1.)

Directive IMPR
impr (entier) : niveau global d'impression ecran (0 par defaut)

Directive OPTI
Elle sert a preciser les options de tous les operateurs places
dans les directives OPER situees apres
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EQPR [Multi-physique Multi-physique]
    Operateur EQPR

   Objet : Cree une table contenant les informations necessaires a la
        solution implicite de la pression dans l'algorithme
        semi implicite.
   La table cree par EQPR est a rajouter dans la table cree par EQEX
   a l'indice 'PRESSION'.

   Syntaxe :

   RVP = EQPR NOMD

        <'KTYPI' i> ---|
        |
     |---------<-------|
     |
     |-> 'ZONE' nomz 'OPER' nomo <arg1 > ---|
     |  |
     |----------------<---------------------|
     |
     |
     V
     ;

NOMD Table DOMAINE domaine total sur lequel sont defini les
      inconnues

Directive ZONE

nomz : Table DOMAINE sur lequel va porter l'operateur. Cet objet
       doit etre inclus dans nomd (Ceci n'est pas encore verifie).

mot cle OPER
nomo : objet de type mot, nom de l'operateur de discretisation a
       executer. A choisir dans la liste ci-dessous.

      PRESSION (Div(U)=0.)
      VNIMP Vitesse normale imposee
      VTIMP Vitesse tangentielle imposee
arg1 arg2 ...etc : arguments de l'operateur (Cf operateur concerne)
       l'operateur (Cf operateur concerne)
       Les arguments lus sont places dans la table associee a l'operateur
       dans l'ordre de la lecture aux indices ARG1 ARG2 ... etc

Directive KTYPI

ktypi (entier) type de la methode d'inversion
      1 Choleski (valeur par defaut)
      2 GC (voir Chapitre Gradient-Conjugue)
      3 DCG "
      4 ICG "

## EQUI [Mecanique Modele]
Operateur EQUI
-------------- PROI

  RIG1 = EQUI 'RIGI' MODBET MODCAB MAT1 ;

  CHPO1 = EQUI 'FORCES' MODBET MODCAB SIG1 ;

Objet :

L'operateur EQUI calcule la rigidite des cables ou les forces
equivalentes a des precontraintes exprimees aux noeuds du beton.

  Commentaire :

  'RIGI' : mot pour indiquer que l'on veut calculer la contribution
        a la rigidite

  'FORCES' : mot pour indiquer que l'on veut calculer des forces
        equivalentes.

  MODBET : objet modele associe au beton (type MMODEL)

  MODCAB : objet modele associe aux cables (type MMODEL)

  MAT1 : champ de proprietes materielles du beton et des cables
        (type MCHAML, sous-type CARACTERISTIQUES)

  RIG1 : matrices de rigidite
        (type RIGIDITE, sous-type RIGIDITE)

  SIG1 : champ de contraintes (type MCHAML,
        sous-type CONTRAINTES)

  CHPO1 : champ de forces (type CHPOINT)

## ERF [Mathematiques Fonctions]
  RESU1 = 'ERF' OBJET1 (MOT1) ;

Operateur ERF

Objet :

L'operateur ERF calcule la fonction d'erreur de Gauss de l'objet
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

## ERFC [Mathematiques Fonctions]
  RESU1 = 'ERFC' OBJET1 (MOT1) ;

Operateur ERFC

Objet :

L'operateur ERFC calcule la fonction d'erreur complementaire
de Gauss de l'objet OBJET1.

  ERFC(X) = 1 - ERF(X)

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

## ERRE [Langage Methodes]
    Foncteur ERREUR

    Le foncteur ERREUR a deux fonctions differentes :

    | 1ere fonction |

    ERREUR | MOT1 ;
        |
        | N1 ( 'AVEC' OBJ1 OBJ2 ...)

    Objet :

    Utilise en directive, ERREUR signale dans les procedures une erreur
    detectee lors de l'execution.

    Elle provoque l'appel du sous-programme ERREUR.

    On peut l'utiliser de deux manieres :

    - Soit avec un objet MOT1 (type MOT), auquel cas le message
      personnalise est affiche et l'erreur generique 308 est declenchee

    - Soit avec un numero N1 (type ENTIER) qui correspond a un numero de
      message pre-redige dans le fichier GIBI.ERREUR. Certains messages
      comportent des motifs commencant par le caractere "%". Ces motifs
      peuvent etre remplaces par des valeurs transmises apres le mot-cle
      "AVEC". Ainsi, chaque OBJi remplacera le i-eme motif de type
      correspondant.

      | MOTIF | OBJi  | Remarques  |
      | %m,%M | MOT  | jusqu'a 120 caracteres au total  |
      |  | LISTMOTS  | %M tronque les espaces de fin, %m pas |
      | %i  | ENTIER  | 9 items maximum  |
      |  | LISTENTI  |  |
      | %r  | FLOTTANT  | 9 items maximum  |
      |  | LISTREEL  |  |
      | %b  | LOGIQUE  | 9 items maximum  |
      |  |  |  |

    | 2eme fonction |
       FLOT1 CHAM2 = ERREUR MODL1 SIG1 MAT1 ;

      Objet :

    Utilise en operateur ERREUR permet de calculer une erreur globale
FLOT1 (type FLOTTANT) et un champ d'erreur CHAM2 (type MCHAML) lies
@ un calcul de contraintes SIG1 (type MCHAML). MAT1 correspond au
champ de proprietes materielles (type MCHAML), MODL1 correspond a
l'objet modele (type MMODEL)

    Remarque :

L'utilisation de l'operateur ERRE est liee aux elements massifs.

## ET [Langage Objets]
 Operateur ET
 ------------ +

 |  1ere possibilite  |

 OBJETR = 'ET' ('TELQUEL') OBJET1 OBJET2 (OBJET3 ...) ('NOER');

Objet :

 L'operateur ET construit l'objet OBJETR representant le resultat
 de la fusion des objets OBJET1 et OBJET2.

 Cette operation n'a actuellement de sens qu'entre objets de meme
 type. Le resultat a le meme type que les objets OBJET1 et OBJET2.

 Dans le seul cas ou OBJET1 et OBJET2 sont de type logique, il peut
 y avoir d'autres opérandes également de type logique.

 Font exceptions a cette regle les concatenations respectives de
 POINT et MAILLAGE -> MAILLAGE
 POINT et POINT -> MAILLAGE (elements de type POI1)
 MOT et LISTMOTS -> LISTMOTS
 ENTIER et LISTENTI -> LISTENTI
 FLOTTANT/ENTIER et LISTREEL -> LISTREEL
 ENTIER et ENTIER -> LISTENTI
 FLOTTANT et FLOTTANT -> LISTREEL
 ENTIER et FLOTTANT -> LISTREEL
 FLOTTANT et ENTIER -> LISTREEL
 OBJET et LISTOBJE -> LISTOBJE (voir remarque)

 Commentaire :

 Les types d'objet acceptes par l'operateur ET sont :
 POINT MAILLAGE LOGIQUE CHPOINT RIGIDITE MMODEL MCHAML
 ATTACHE BLOQSTRU ELEMSTRU SOLUTION DEFORME BASMOD VECTEUR
 LISTREEL LISTENTI EVOLUTIO CHARGEME STRUCTUR MCHAML TABLE
 LISTMOTS MOT NUAGE LISTCHPO MATRIK FLOTTANT ENTIER
 LISTOBJE

 Remarques :

* Si les objets OBJET1 et OBJET2 sont de type LOGIQUE,
  le resultat est la conjonction logique des 2 objets.
  D'autres LOGIQUEs peuvent aussi être fournis et le résultat
  est alors la conjonction logique de tous les objets.

* Si les objets OBJET1 et OBJET2 sont de type CHPOINT, l'operation
  n'est possible que si ils ont la meme nature (DISCRET ou DIFFUS).
  Le resultat est la concatenation des deux objets pour leurs parties
  disjointes et pour leurs parties communes constituees par les memes
  composantes aux memes noeuds le resultat depend de leur nature :
  - s'ils sont de nature diffuse la valeur doit etre la meme pour
      les deux champs, sauf si le motcle NOER est indique.
  - s'ils sont de nature discrete on somme les deux valeurs.

* Si les objets OBJET1 et OBJET2 sont de type MOT, ils doivent
  etre places derriere ET. Le resultat est la concatenation des deux
  mots. Si le mot 'TELQUEL' est utilise les blancs aux extremites de
  OBJET1 et OBJET2 sont conserves. Voir aussi operateur 'CHAINE'.

* Si les objets OBJET1 et OBJET2 sont de type TABLE, ils
  doivent etre tous les deux de sous-type "LIAISONS_STATIQUES",
  ou bien "BASE_MODALE".

* Si les objets OBJET1 et OBJET2 sont de type MAILLAGE, les
  partitions de type SEG2 sont concatenees en veillant a preserver une
  continuite de parcours de la partition resultat, sauf en presence du
  mot-clef 'TELQUEL' qui force un respect de l'ordre des maillages
  fournis en entree.

* Si OBJET1 et OBJET2 sont un LISTOBJE et un OBJET de meme type
  que ceux contenus dans la liste, l'objet est ajoute en fin de
  liste.

 |  2eme possibilite  |

 OBJET2 = 'ET' ( TAB1 ) ;
        ( LOBJ1 )

 Objet :

 L'operateur ET construit la fusion de l'ensemble des objets
 contenus :
 - soit dans la table de sous-type ESCLAVE TAB1 ;
 - soit dans la liste d'objets LOBJ1.

 Ces objets doivent etre de type POINT, MAILLAGE, CHPOINT, MCHAML,
 RIGIDITE, MATRIK, MMODEL, EVOLUTION, LISTREEL, LISTENTI, FLOTTANT
 ou ENTIER.

 Le resultat est du meme type que les objets places en chaque indice
 entier de TAB1 a l'exception des objets repertories dans le
 tableau qui suit :

 | Type de de l'indice  |  Type du résultat |
 | POINT  |  MAILLAGE  |
 | FLOTTANT  |  LISTREEL  |
 | ENTIER  |  LISTENTI  |

## ETG [Langage Objets]
    Operateur ETG
    ------------- ENUM

    OBJET2 = 'ETG' ( TAB1 ) ;
        ( LOBJ1 )

    Objet :

    L'operateur ETG construit l'objet OBJET2 representant le resultat
    de la fusion (operateur 'ET') de la collection d'objets contenus :
    - soit dans la table TAB1 de 'SOUSTYPE' 'ESCLAVE' ;
    - soit dans la liste d'objets LOBJ1.

    La table TAB1 ou la liste d'objets LOBJ1 ne doivent contenir que
    des objets de type :
    'CHPOINT', 'RIGIDITE', 'LOGIQUE' , 'MCHAML', 'MMODEL', 'MAILLAGE',
    'MATRIK' , 'FLOTTANT', 'EVOLUTIO', 'ENTIER', 'MOT' , 'CHARGEME'.

$$$$

## EVOL [Post-traitement Affichage]
     Operateur EVOL

 L'operateur EVOL definit l'evolution d'une (ou plusieurs) grandeur(s)
 en fonction d'un parametre. Le resultat est un objet de type EVOLUTION.

 Plusieurs options sont disponibles :

CHAP{Sur une LIGNE a partir d'un objet CHPOINT}
     |  Option CHPO  |

     EVOL1 = EVOL (COUL) 'CHPO' CHP1 COMP GEO1 ;

     Objet :

     Cette option permet de definir l'evolution d'une composante d'un
     CHPOINT le long d'une ligne de noeuds.

     Commentaire :

     COUL : couleur de la (ou des) courbe(s). Si elle est omise
        on utilise la couleur par defaut definie dans OPTION.

     CHP1 : le champ de type CHPOINT.

     COMP : nom de la composante (type MOT). Elle peut etre omise
        si le champ CHP1 n'a qu'une seule composante.

     GEO1 : la ligne de noeuds (type MAILLAGE).

     En abscisse figurera l'abscisse curviligne le long de la ligne
     et en ordonnee la valeur de la composante correspondante. La ligne
     devra etre continue et ne pas etre branchee.

CHAP{En un (ou plusieurs) POINT(s) et plusieurs instants}
     |  Option TEMP  |

     EVOL1 = EVOL (|COUL |) 'TEMP' |LCHP1 LREE1| (LIPDT1)  ...
        |LCOUL|  |TAB1 (MOT1)|

        ...  |COMP  | |POIN1  | ;
        |LCOMP | |MAIL1  |
        |N1 N2 N3|

     Objet :

     Cette option permet de tracer l'evolution temporelle de resultats
     de calcul (PASAPAS, DYNAMIC, EXEC...) en certains points.

     Commentaire :

     Les resultats sont contenus soit :

       1) dans un objet TAB1 de type TABLE (et de sous-type PASAPAS,
        DYNAMIC ou EXEC), auquel cas on peut fournir dans MOT1
        l'indice de la grandeur a tracer :
        - pour PASAPAS : DEPLACEMENTS (par defaut), TEMPERATURES...
        - pour DYNAMIC : DEPL (par defaut), VITE...
        - pour EXEC : UN (par defaut), PN, TN...

       2) dans un objet LCHP1 de type LISTCHPO (ordonnees) et un objet
        LREE1 de type LISTREEL (abscisses)

     On peut restreindre la liste des pas de temps traces en donnant
     l'objet LIPDT1 de type LISTENTI.

     Si la grandeur est vectorielle, les noms des composantes doivent
     etre precises par la donnee de COMP (type MOT) ou LCOMP (type
     LISTMOTS).

     Le (ou les) point(s) ou tracer les courbes sont specifies dans
     POIN1 (type POINT) ou MAIL1 (type MAILLAGE).

     COUL (type MOT) ou LCOUL (type LISTMOTS) definissent les couleurs
     attribuees a chaque courbe.

     Cas particulier, pour une grandeur PASAPAS de type MCHAML :
       + tous les instants disponibles sont traces (pas de LIPDT1)
       + on ne peut choisir qu'une seule composante (pas de LCOMP)
       + on ne donne pas POIN1 ou MAIL1 mais 3 objets N1, N2 et N3 de
        type ENTIER (indiquant le N3-eme point de Gauss du N2-eme
        element de la N1-ieme zone du modele)

CHAP{FONCTION complexe a partir de trois objets LISTREEL}
     |  Option COMP  |

     EVOL1 = EVOL (COUL) 'COMP'  | ('REIM') |  ...
        | ('MOPH') |

        ... ('LEGE' TITOR1 TITOR2) ...

        ... NOMABS LISTABS (NOMOR1) LISTOR1 (NOMOR2) LISTOR2 ;

     Objet :

     Cette option permet de definir une fonction complexe a partir de
     trois listes de reels (cf PROG).

     Commentaire :

     COUL : couleur de la (ou des) courbe(s). Si elle est omise
        on utilise la couleur par defaut definie dans OPTION.

    'REIM' : mot-cle indiquant que la fonction complexe est definie
        sous la forme partie reelle - partie imaginaire (option
        prise par defaut).

    'MOPH' : mot-cle indiquant que la fonction complexe est
        definie sous la forme module - phase.

    'LEGE' : mot-cle permettant de donner des titres aux courbes

     TITOR1 : titre de la partie reelle ou amplitude (Re ou Amp par
        defaut).

     TITOR2 : titre de la partie imaginaire ou phase (Im ou \j par
        defaut).

     NOMABS : nom des abscisses (MOT de 12 caracteres au maximum)

     LISTABS : liste de reels en abscisse (type LISTREEL)

     NOMOR1 : nom des parties reelles ou modules en ordonnee
        (MOT de 12 caracteres au maximum)

     LISTOR1 : parties reelles ou modules en ordonnee (type LISTREEL)

     NOMOR2 : nom de la partie imaginaire ou phase en ordonnee
        (MOT de 12 caracteres au maximum)

     LISTOR2 : parties imaginaires ou phases en ordonnee (type LISTREEL)

CHAP{FONCTION a partir de deux objets LISTREEL}
     |  Option MANU  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXAC [Fluides Resolution] (proc)
  Procedure EXAC

  EXAC TAB1 ;

  Objet :

  Cette procedure permet de resoudre des problemes de mecanique des
 fluides .

1/ Si l'entree 'PRESSION' n'existe pas :
  RESOUD des EDP en explicite suivant les informations donnees
  dans une table de type EQEX (creee par EQEX).

2/ Si l'entree 'PRESSION' existe :
  RESOUD les equations de NAVIER-STOKES suivant un algorithme
  semi-implicite suivant les informations donnees dans une table
  de type EQEX (creee par EQEX).

  Cette table doit avoir une entree 'PRESSION' contenant la table
  de type EQPR ou sont rassemblees les informations liees a
  l'equation de pression et a sa resolution. Table creee par EQPR.

  Enfin la table doit contenir une entree 'INCO' , table creee
  par l'utilisateur et de sous type 'INCO' contenant les CHAMPOINTs
  d'initialisation.
  Si la table possede une entree HIST contenant une table (cree par
  KHIS ) la table des historiques est completee

## EXCC [Mecanique Limites]
Operateur EXCC
-------------- IMPO EXCF

 CHPOI1 = EXCC RIG1 DEPL1 MODE1 CHAM1 (CHPOI2);

Objet :

EXCC permet de calculer un champ de force limite de frottement
(type CHPOINT) a partir de la raideur de frottement RIG1, du champ
de deplacement DEPL1 (type CHPOINT), du modele de contact-frottant
MODE1 et du champ de proprietes de frottement CHAM1 (type MCHAML).

On peut fournir un champ minimum de forces de frottement : CHPOI2.

Remarque :

EXCC est employe dans UNPAS. Il y a peu de raisons de l'employer
directement.
EXCC est employe uniquement dans le cas des cables.

## EXCE [Mathematiques Fonctions]
    Operateur EXCELLENCE

    TAB1 = EXCE TAB1 ;
        TAB1.'VX0' .'VF' .'VXMIN'
        .'VXMAX' .'MC' .'VCMAX'
        .'METHODE' .'DELTA0'
        .'MAXITERATION' .'XSMAX'
        .'VDIS' .'T0' .'S0'

    Objet :
 L'operateur EXCELL cherche le minimum d'une fonction F(Xi), la methode
utilisee est connue sous le nom de MMA (Method of Moving Asymptotes)
proposee par K.Svanberg. Il s'agit donc de trouver le minimum d'une
fonction F(Xi) avec i=1,N et sachant que :

   - il existe des relations Cj(Xi) < Cjmax j > 0 j=1,M

   - Il existe des relations sur chaque inconnue Ximin < Xi < Ximax

 La donnee des fonctions F et Cj se fait a l'aide des valeurs des
fonctions et de leurs derivees au point de depart X0.

    Donnees :
 TAB1.'VX0' : table (sous-type VECTEUR) contenant les valeurs
        initiales des variables X0i.
        La table est indicee par les ENTIERs i. (i=1,N)

 TAB1.'VF' : table (sous-type VECTEUR) contenant :
        - dans TAB1.'VF'.0 : la valeur de F(X0i)
        - dans TAB1.'VF'.I : la valeur de la derivee de F
        par rapport a Xi en X0 (i=1,N).

 TAB1.'MC' : table indicee par des ENTIERs j (j=1,M) et
        contenant autant de tables que de relations Cj.

      TAB1.'MC'.J est une table representant la fonction Cj
        - dans TAB1.'MC'.J.0 : la valeur initiale de
        Cj(X0) (j=1,M)
        - dans TAB1.'MC'.J.I : la valeur de la derivee de
        Cj par rapport a Xi en X0 (i=1,N).

 TAB1.'VXMIN' : table indicee par des ENTIERs (i=1,N) et
        contenant :
        - dans TAB1.'VXMIN'.I : la valeur de Ximin

 TAB1.'VXMAX' : table indicee par des ENTIERs (i=1,N) et
        contenant :
        - dans TAB1.'VXMAX'.I : la valeur de Ximax

 TAB1.'VCMAX' : table indicee par des ENTIERs (i=1,M) et
        contenant :
        - dans TAB1.'VCMAX'.I : la valeur de Cjmax

 TAB1.'METHODE' : (facultatif) est un MOT precisant la methode de
        linearisation a utiliser.

        - 'STA' pour l'emploi de la methode standard.
        - 'MOV' si les fonctions sont tres fortement
        non-lineaires.
        - 'LIN' si les fonctions sont peu non-lineaires
        et qu'il y a des variables a variations non
        continues.

 TAB1.'T0' : (facultatif) change la valeur du reel compris
        entre 0. et 1. qui gouverne la convexite des
        fonctions. Plus t0 est grand plus les fonctions
        sont convexes. Par defaut, pour la methode
        standard, t0 est pris egal a 0.3333.

 TAB1.'S0' : (facultatif) change la valeur du reel compris
        entre 0. et 1. qui gouverne la convexite des
        fonctions. Plus s0 est grand plus les fonctions
        sont convexes. Par defaut, pour la methode
        MOV, s0 est pris egal a 0.7.

 TAB1.'MAXITERATION' : (facultatif) change la valeur maximum
        autorisee pour le nombre d'iterations.
        (Par defaut 100)

 TAB1.'VDIS' : table indicee par des ENTIERs k (k=1,KK) et
        contenant autant de tables que de variables
        n'ayant que des valeurs discretes autorisees.
        Cette option n'est pas encore disponible.

    Remarque :
    ---------- - Au depart les variables X0i doivent satisfaire
        aux conditions Ximin < X0i < Ximax

        - Le point de depart ne satisfait pas forcement les
        relations Cj < Cjmax
        Dans ce cas une variables supplementaire de
        relaxation est introduite et la solution trouvee
        par EXCELL ne satisfera peut-etre pas non plus
        les relations. L'influence de cette variable
        de relaxation peut etre modifiee par deux reels
        TAB1.'DELTA0' et TAB1.'XSMAX'. Par defaut
        DELTA0=50. et XSMAX=500. ( il faut DELTA0 >1. et
        XSMAX > DELTA0)
    Exemple :

    La fonction que l'on desire minimiser n'est pas celle
qui est minimisee par l'operateur EXCE. La demarche a suivre est de
resoudre une succession de probleme. Partant d'un etat connu des
variables on demande a EXCE de calculer le minimum d'un probleme
approche, la fonction F a minimiser est remplacee par la fonction
linearisee decrite ci-dessus ainsi que les fonctions C. Puis on repart
de la solution trouvee par EXCE. L'algorithme se presente ainsi :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXCF [Mecanique Limites]
Operateur EXCF
-------------- IMPO EXCC

 RIG3 RIG4 CHPOI1 = EXCF RIG1 DEPL1 MODE1 CHAM1 ENT1;

Objet :

EXCF permet de calculer un champ de force limite de frottement
(type CHPOINT) ainsi que la partie non symetrique de la raideur de
frottement RIG4 a partir de la raideur de frottement RIG1, du champ
de deplacement DEPL1 (type CHPOINT), du modele de contact-frottant
MODE1 et du champ de proprietes de frottement CHAM1 (type MCHAML).

RIG4 est la partie non symetrique de la raideur de frottement.
RIG3 est la matrice de transfert du multiplicateur de Lagrange .
de contact vers celui de frottement.

ENT1 est un entier indiquant l'iteration courante. Il permet de
regulariser la direction de frottement.

Remarque :

EXCF est employe dans UNPAS. Il y a peu de raisons de l'employer
directement.

## EXCI [Mecanique Resolution]
    Operateur EXCITER

 RIG2 LOG LENT1 = EXCITER  (| RAPIDE |) RIG1 MAIL_CONTR DEP1 DEP2 (FO1);
        | MOYEN  |
        | LENT  |

    Objet :

    L'operateur EXCITER est utilise dans le cadre de la resolution des
conditions unilaterales.

    A partir des blocages MINI et MAXI, d'un champ de deplacements impo-
ses et d'un champ de deplacements, et en cas de frottement d'un champ de
forces limite de frottement indiquant la direction du frottement, cet
operateur donne les blocages actifs. Les noeuds contenus dans le
maillage MAIL_CONTR sont elimines dans les blocages actifs.

    Commentaire :

    RIG1 : matrice de rigidite contenant les blocages MINI et MAXI
        (type RIGIDITE)

    RAPIDE : methode utilisee. RAPIDE par defaut.
    MOYEN
    LENT

    MAIL_CONTR : maillage des noeuds a ne pas mettre dans RIG2

    DEP1 : champ de deplacements imposes (type CHPOINT)

    DEP2 : champ de deplacements (type CHPOINT)

    FO1 : champ de forces (type CHPOINT)

    RIG2 : matrice de rigidite contenant les blocages actifs
        (type RIGIDITE)

    LOG : logique disant si il blocages actifs sont restes les memes

    LENTI1 : liste d'entiers (type LISTENTI) valant 1 ou 0 suivant que
        les blocages successifs sont actifs ou non-actifs.

## EXCO [Langage Objets]
    Operateur EXCO

     CH2 =  EXCO  | MOT1  (n1) ('NOID') CH1 (MOT2)  (n2) |  ...
        | LISM1 (n1) ('NOID') CH1 (LISM2) (n2) |

        ... ('NATURE'|'INDETER')
        |'DIFFUS' )
        |'DISCRET') ;

    Objet :

    Cet operateur cree a partir d'un champ, un champ de meme type en
extrayant une ou plusieurs composantes donnees.

    Commentaire :

    CH2 : objet resultat de meme type que CH1 (type CHPOINT ou MCHAML)

    CH1 : champ a traiter (type CHPOINT ou MCHAML)

    MOT1 : nom de la composante a extraire du champ CH1 (type MOT)

    MOT2 : nouveau nom donne a la composante extraite (type MOT)

    LISM1 : liste des composantes a extraire du champ CH1
        (type LISTMOTS)

    LISM2 : liste des nouveaux noms donnes aux composantes extraites
        (type LISTMOTS)

    Dans le cas 2D Fourier,
    n1 : harmonique de Fourier a extraire (type ENTIER)
    n2 : nouvelle harmonique de Fourier a donner (type ENTIER)

    'NOID' : mot cle indiquant de ne pas faire d'erreur si une
        composante est absente du champ CH1. Il doit absolument
        etre positionne avant MOT2.

    Remarques :

 1. Dans le cas de l'extraction d'une seule composante d'un champ, le
    nom de la composante extraite est MOT2 (type MOT) si ce MOT est
    fourni, sinon le nom de la composante extraite est MOT1 dans le cas
    des champs de type MCHAML et 'SCAL' dans le cas des champs de type
    CHPOINT.

    Si la composante de nom MOT1 n'existe pas dans le champ CH1,
    l'operateur signale une erreur sauf si on emploie le mot 'NOID'.
    Dans ce cas, l'operateur cree un champ CH2 vide.

 2. Dans le cas de l'extraction de plusieurs composantes d'un champ,
    les composantes extraites gardent leur nom, sauf si LISM2 est donne.
    Dans ce cas, LISM1 et LISM2 doivent avoir le meme nombre de
    composantes.

    Si une composante definie dans LISM1 n'existe pas dans le champ CH1,
    l'operateur signale une erreur sauf si on emploie le mot 'NOID'.

 3. Dans le cas 2D Fourier, si n1 ou n2 n'est pas fourni, l'harmonique
    de Fourier par defaut (cf. OPTI) est utilisee.

 4. Preciser la nature n'est possible que si l'on travaille avec des
    champs de points (CHPOINT). Si elle n'est pas specifiee, on garde
    celle du champ par point argument.

## EXCP [Changement_De_Phase Changement_De_Phase]
Operateur EXCP
-------------- PROP RESO

  CHP3 = 'EXCP' MOD1 MAT1 QLINT PROP0 CHP1 CHP2 ;

Objet :

L'operateur 'EXCP' calcule la chaleur latente qu'il faudrait
consommer pour finir de changer de phase. Ce resultat est mis
sous forme directement exploitable par l'operateur 'RESO'.

Cet operateur est automatiquement appele dans la procedure TRANSNON.

  Commentaire :

  MOD1 : objet de type MMODEL contenant une formulation de type
        'CHANGEMENT_PHASE'.

  MAT1 : objet MCHAML des caracteristiques. La composante 'PRIM'
        est attendue constante par SOUS-ZONE.

  PROP0 : objet de type MCHAML contenant les proportions de phases
        initiales.

  QLINT : objet de type MCHAML contenant la quantite latente
        integree sur l'element (aux NOEUDS) avec l'operateur 'SOUR'.

  CHP1 : objet CHPOINT contenant les inconnues initiales.

  CHP2 : objet CHPOINT contenant l'increment des inconnues et les
        reactions 'LX' sur les blocages (si sortie de 'RESO').

  CHP3 : objet CHPOINT des chaleurs latentes exprimees sur les
        multiplicateurs de lagrange ('LX') a injecter comme argument
        de l'operateur 'RESO'.

## EXEC [Fluides Resolution] (proc)
    Procedure EXEC
    -------------- DOMA KCHT

    EXEC TAB1 ;

    Objet :

   I/ TRANSPORT/DIFFUSION D'UN SCALAIRE

    Cette procedure permet d'effectuer un calcul du transport
   (convection/diffusion), d'un scalaire passif, en transitoire ou en
   regime permanent, en presence de conditions aux limites variees, valeur
   imposee, flux, echange avec le milieu exterieur, source etc. Le
   calcul peut etre lineaire ou non. Les non linearites sont resolues
   par une methode de point fixe. La description de l'equation a
   resoudre se fait a l'aide de l'operateur EQEX qui cree la table TAB1.
   Le scalaire peut aussi bien etre la temperature qu'une concentration
   ou toute grandeur physique intensive.
   Les parametres de l'algorithme sont definis dans la table TAB1 a l'aide
   de EQEX.

   I.1/ Calcul transitoire explicite.

   Le pas de temps est soumis a une contrainte de stabilite. Il peut etre
   impose ou calcule automatiquement.
   Les non linearites, notamment sur les proprietes physiques,peuvent
   etre resolues en les actualisant dans une procedure de calcul appelee
   a chaque pas de temps. Le regime permanent peut etre obtenu comme
   limite asymptotique du transitoire.

*.Exemple I.1 :.........................................................
* Procedure calculant une propriete physique dependant de la temperature

      'DEBP' CALCUL ;
      'ARGU' RX*TABLE ;
      iarg = rx . 'IARG' ;
      rv = rx . 'EQEX' ;
*Lecture des arguments de l'operateur calcul
      'SI' ( 'NON' ( 'EGA' iarg 1)) ;
        'MESS' 'Procedure CALCUL : nombre d arguments incorrect ' iarg ;
        'QUIT' CALCUL ;
      'FINSI' ;

      'SI' ( 'EGA' ('TYPE' rx . 'ARG1') 'MOT ') ;
        TN = rv . 'INCO' . (rx . 'ARG1') ;
      'SINON' ;
        'MESS' 'Procedure CALCUL : type argument invalide ' ;
        'QUIT' CALCUL ;
      'FINSI' ;

* La temperature est exprimee en Kelvin
      T = TN + 273. ;
*Viscosite dynamique : loi de Sutherland : Kg/m/s
      MU = 1.648*(T**1.5) * ('INVE' (T + 0.648))
*conductivite : loi de Sutherland : W/m/oC
      LB = 1.368*(T**1.5) * ('INVE' (T + 0.368))
*J/kg/oC
      CP = 1015 ;
* Nombre de Prandtl
      Pr = MU * CP * ('INVE' LB)
* le Reynolds est donne
      Re = 400. ;
      Pe = Re * Pr ;
      rv . 'INCO' . 'IPE' = 'INVE' Pe ;
* La derniere instruction cree des objet vides
* pour satisfaire la procedure EXEC
      as2 ama1 = 'KOPS' 'MATRIK' ;
      'FINPROC' as2 ama1 ;

* On cree la table RV decrivant le probleme physique
* On choisit un algorithme explicite (OPTI 'EFM1')
* Le pas de temps est calcule automatiquement
* (mot cle 'DELTAT' sur DFDT)
* On fera 200 pas de temps
* Le Peclet est calcule dans la procedure CALCUL

      RV = 'EQEX' 'OMEGA' 1. 'NITER' 1 'ITMA' 200
      'ZONE' $mt 'OPER' CALCUL 'TN'
      'OPTI' 'EFM1' 'SUPG'
      'ZONE' $mt 'OPER' 'TSCA' 'IPE' 'UN' 0. 'INCO' 'TN'
      'OPTI' 'EFM1' 'CENTREE'
      'ZONE' $mt 'OPER' 'DFDT' 1. 'TN' 'DELTAT' 'INCO' 'TN'
      'CLIM' 'TN' 'TIMP' entree 0. 'TN' 'TIMP' paroi 1.
      ;
      rv . 'INCO' = 'TABLE' 'INCO' ;
      rv . 'INCO' .'UN'= 'KCHT' $mt 'VECT' 'SOMMET' (1. 0.) ;
      rv . 'INCO' .'TN'= 'KCHT' $mt 'SCAL' 'SOMMET' 0. ;

      EXEC RV ;

* Les resultats se trouvent dans la table rv . 'INCO'

*.Fin exemple I.1 ......................................................

   I.2/ Calcul direct d'un regime permanent.

   - On peut faire une recherche directe d'un regime permanent avec
   des iterations internes pour resoudre les non-linearites.

*.Exemple I.2 :.........................................................

* On cree la table RV decrivant le probleme physique
* On choisit un algorithme IMPLICITE (OPTI 'EF' 'IMPL')
* On fera 10 iterations avec un facteur de relaxation de OMEGA=0.5
* Le Peclet est calcule dans la procedure CALCUL decrite dans
* l'exemple 1.

      RV = 'EQEX' 'OMEGA' 0.5 'NITER' 10 'ITMA' 0
      'ZONE' $mt 'OPER' CALCUL 'TN'
      'OPTI' 'EF' 'SUPG' 'IMPL'
      'ZONE' $mt 'OPER' 'TSCA' 'IPE' 'UN' 0. 'INCO' 'TN'
      'CLIM' 'TN' 'TIMP' entree 0. 'TN' 'TIMP' paroi 1.
      ;
      rv . 'INCO' = 'TABLE' 'INCO' ;
      rv . 'INCO' . 'UN' = 'KCHT' $mt 'VECT' 'SOMMET' (1. 0.) ;
      rv . 'INCO' . 'TN' = 'KCHT' $mt 'SCAL' 'SOMMET' 0. ;

      EXEC RV ;

* Les resultats se trouvent dans la table rv . 'INCO'

*.Fin exemple I.2 ......................................................

   I.3/ Calcul transitoire implicite.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXECRXT [Fluides Resolution] (proc)
    Procedure EXECRXT

      EXECRXT ENTI1 TAB1 ;

    Commentaire :

      ENTI1 : nombre de pas de temps

      TAB1 : table RXT contenant la description du probleme fluide

    Objet :

  La procedure EXECRXT calcule, a partir d'un etat initial, l'evolution
 au cours du temps d'un melange gazeux dans une enceinte fermee.

CHAP{Generalites}

  L'etat initial est uniforme en espace lorsqu'il est donne par
 l'utilisateur, issu d'un calcul precedent sinon.

  L'air est toujours present dans le melange gazeux. Il peut aussi contenir un
 ou plusieurs des constituants suivants: vapeur d'eau, H2, N2, He, O2, CO et
 CO2. Les gaz incondensables sont modelises par la loi des gaz parfaits. C'est
 aussi le choix par defaut de la vapeur (version V0), un modele gaz reel etant
 en test (version V1).

  En presence de vapeur la condensation en paroi peut apparaitre si les
 conditions locales sont reunies (Pvap > Psat). Le modele de condensation est
 de type Chilton-Colburn et associe a une correlation d'echange de type
 convection naturelle le long d'une plaque plane verticale.

  On distingue 4 types de conditions aux limites suivant la nature de la
 frontiere du domaine fluide : zones d'injection (breches), ventilation forcee
 et clapet de decharge (sorties), parois thermiques et parois inertes :

  - sur les zones d'injection ou breches, on impose des conditions aux limites
 de type valeur imposee pour la vitesse, la temperature du melange, la densite
 du melange et de ses constituants. Il faut donc y preciser le debit massique
 de chaque constituant du melange (kg/s) et la temperature d'entree (oC) (voir
 entree 'scenario' des Breches) ;

  - sur les sorties, on impose un debit (ventilation) et on precise les
 parametres de la perte de charge (clapet de decharge) (voir entree 'scenario'
 des Sorties) ;

  - sur les parois thermiques, la vitesse est nulle (suf si fonction de paroi
 (entree FPAROI)) et la temperature evolue au cours du temps (entree TIMP), est
 a priori constante (entree ECHANP), le resultat d'un calcul de thermique paroi
 (entree THERMP). Pour ce dernier cas, il est possible de coupler la resolution
 des equations de l'enrergie paroi et fluide de façon implicite (entree
 THERCO). En presence de vapeur les parois thermiques sont susceptibles de
 condenser. Elles sont par contre impermeables pour tous les incondensables.

  - sur les parois inertes, la vitesse est nulle, et elles sont impermeables
 pour toutes les autres inconnues (temperature, vapeur et gaz incondensables).
 Les parois inertes correspondent au maillage obtenu par difference entre
 l'enveloppe du volume fluide et les parois, breches et sorties.

 Par suite, les conditions aux limites sont correctement definies.

  La turbulence des mouvements de gaz est modelisee soit par une viscosite
 tourbillonnaire constante, soit par un modele de longueur de melange soit par
 un modele K-epsilon (entree MODTURB). En absence de l'entree MODTURB,
 l'ecoulement est laminaire.

  Un modele d'aspersion est disponible.

  Un modele de condensation en masse est en test.

  Au moyen du fichier d'extension dgibi, l'utilisateur transmet a CAST3M les
 donnees du scenario etudie. Regroupees dans la table notee RXT a differents
 indices qui sont precises dans cette notice, le transitoire est alors calcule
 par la procedure EXECRXT avec la table RXT et le nombre de pas de temps ndt en
 donnees d'entree :

   EXECRXT ndt rxt ;

  La table RXT est completee au moment de l'execution par trois tables :
  - la sous table rxt.'GEO' contient les modeles et objets geometriques crees a
 partir des donnees fournies.
  - la sous table rxt.'TBT' est la table de travail proprement dite et contient
 les autres objets crees necessaires au calcul hormis les inconnues.
  - la sous table rxt.'TIC' contient les inconnues au dernier temps connu
 (temps calcule ou condition initiale) ainsi que les champs variables en temps.

 Les entrees de RXT fournis par l'utilisateur ne sont donc pas modifiees.

 Les indices de RXT sont les presentes ci-dessous.

CHAP{Objets geometriques}

 rxt . 'vtf' = GEO1 ; maillage fluide (OBLIGATOIRE)
 rxt . 'pi' = POI1 ; point interieur du domaine fluide ou sera imposee
        la pression (OBLIGATOIRE).
 rxt . 'axe' = GEO2 ; axe de revolution si 2D AXI

  On peut definir un nombre quelconque de Breches en indiquant le nom de la
 breche, son maillage et la direction du champ de vitesse a la breche autant
 de fois que necessaire :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXIC [Fluides Resolution] (proc)
 Procedure EXIC

 EXIC TAB1 ;

 Objet :

 Cette procedure permet de resoudre des problemes de mecanique des
fluides par un algorithme implicite suivant les informations donnees
dans une table TAB1 de type EQEX (creee par EQEX).
 TAB1 doit contenir une entree 'INCO' , table creee
 par l'utilisateur et de sous type 'INCO' contenant les CHAMPOINTs
 d'initialisation.

## EXIS [Langage Base]
Operateur EXISTE

LOG1(,LOG2,...) =  EXISTE  |  NOM1 (*TYP1)  | ;
        |  NOM1 (*'FICHIER')  |
        |  TAB1  OBJ1  |
        |  OBJ1  OBJ2  |
        |  %  OBJ2  |
        |  CH1  MOT1  |
        |  CH1  OBJ1  |
        |  LMOTS1 | MOT1  |  |
        |  | LMOTS2  ('ET'/'OU') |  |
        |  LENTI1  ENTI1  |
        |  LREEL1  FLOT1  (FLOT2)  |
        |  SOL1  'CONT'  |
        |  NUAG1  MOT1  |
        |  CHAR1  | MOT1 (MOT2)  |  |
        |  | 'LIBR'/'LIE ' |  |
        |  MODL1  MOT1  MOT2  |

Objet :

L'operateur EXISTE permet de verifier l'existence d'objets.

Commentaires :

Dans tous les cas qui suivent, LOG1(,LOG2,...) sont des objets de
type LOGIQUE valant VRAI si l'existence est averee, FAUX sinon.

1) Lorsqu'un unique argument NOM1 est present, l'operateur permet
    de savoir si un objet portant un tel nom existe.
    a) L'ensemble *TYP1 est facultatif.
        - S'il est present, le test est VRAI si un objet NOM1 de
        type TYP1 existe.
        - S'il est omis, le test est FAUX seulement pour les objets
        de type ANNULE
        En effet, tout nom NOM1 non attribue est vu comme un objet
        existant de type MOT.

    b) L'ensemble *'FICHIER' permet de tester l'existence du fichier NOM1.
       NOM1 doit etre de type 'MOT' et definir le chemin absolu ou
       relatif vers le fichier a tester.

2) Dans le cas d'une table TAB1 (type TABLE), il permet de savoir
    si l'indice OBJ1 de la table existe (type ENTIER, FLOTTANT, MOT,
    LOGIQUE, PROCEDUR...).

3) Dans le cas d'un OBJET OBJ1, il permet se savoir si l'indice
    OBJ2 existe. A l'interieur d'une methode s'appliquant sur
    l'objet, % remplace le nom de l'objet.

4) Dans le cas d'un champ CH1 (type CHPOINT ou MCHAML), il permet
    de savoir si la composante de nom MOT1 (type MOT) existe.
    Dans le cas d'un champ CH1 (type MCHAML), il permet de savoir
    si une zone s'appuie sur l'objet OBJ1 (type MAILLAGE ou
    MMODEL). La verification porte aussi sur le constituant et
    la phase pour le type MMODEL.

5) Dans le cas d'une liste de mots LMOTS1 (type LISTMOTS), il
    permet de savoir si le mot MOT1 (type MOT) existe. On peut
    aussi fournir une seconde liste de mots a rechercher LMOTS2
    (type LISTMOTS). Dans ce cas, LOG1 est VRAI si TOUS les mots de
    LMOTS2 sont dans LMOTS1 (mot-cle 'ET') ou bien si AU MOINS UN
    des mots de LMOTS2 est trouve dans LMOTS1 (mot-cle 'OU'). En
    l'absence de mot-cle, on sort autant d'objets LOG1, LOG2, ...
    qu'il y a de mots a tester dans LMOTS2.

6) Dans le cas d'une liste d'entiers LENTI1 (type LISTENTI), il
    permet de savoir si l entier ENTI1 (type ENTIER) existe.

7) Dans le cas d'une liste de reels LREEL1 (type LISTREEL), il
    permet de savoir si le reel FLOT1 (type FLOTTANT) existe. Il
    est possible de fournir la tolerance FLOT2 (type FLOTTANT)
    utilisee pour tester les egalites entre nombres reels.

8) Dans le cas d'un objet SOL1 (type SOLUTION), il permet de savoir
    si les contraintes (mot-cle 'CONT') sont incluses.

9) Dans le cas d'un objet NUAG1 (type NUAGE), il permet de savoir
    si le mot MOT1 (type MOT) est un nom de composante du NUAGE.

10) Dans le cas de CHAR1 (type CHARGEMENT), il permet de savoir si
    le mot MOT1 (type MOT) est le nom d'un chargement elementaire,
    ou bien s'il existe des sous-objets CHARGEMENT de nature libre
    (mot-cle 'LIBRE') ou liee (mot-cle 'LIE') dans CHAR1, ou bien
    si le chargement elementaire de nom MOT1 est defini a partir
    d'un objet de type MOT2 (CHPOINT, MCHAML, TABLE ou LISTOBJE).

11) Dans le cas d'un objet MODL1 (type MMODEL), les deux arguments
    MOT1 et MOT2 (type MOT) permettent de savoir :

    a) S'il existe des zones du MMODEL correspondant a une
       formulation donnee. Dans ce cas MOT1 est alors 'FORM' et
       MOT2 est un ou plusieurs mots definissant la formulation.

    b) S'il existe des zones du MMODEL correspondant a un ou
       plusieurs constituants donnes. Dans ce cas MOT1 est alors
       'CONS' et MOT2 est un ou plusieurs mots definissant les
       constituants.

    c) S'il existe des zones du MMODEL correspondant a un ou
       plusieurs elements finis donnes. Dans ce cas MOT1 est alors
       'ELEM' et MOT2 est un ou plusieurs mots definissant les
       elements finis.

    d) S'il existe des zones elementaires du MMODEL dont la liste
       de mots qui definit le comportement du materiau contient
       le(s) mot(s) MOT2. Pour cela, on specifiera 'MATE' pour MOT1.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXP [Mathematiques Fonctions]
  RESU1 = 'EXP' OBJET1 (MOT1) ;

Operateur EXP

Objet :

L'operateur EXP calcule l'exponentielle de l'objet OBJET1.

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

## EXPLORER [Post-traitement Affichage] (proc)
  Procedure EXPLORER

  EXPLORER  TAB1 | (LMOC1) (TOPT1) ;
        | 'CHAR'  (TOPT2) ;

  Objet :

  La procedure EXPLORER permet de depouiller graphiquement les
  resultats d'une table PASAPAS, BASE_MODALE ou LIAISONS_STATIQUES.

  Cas d'une table PASAPAS :

> TAB1 : TABLE issue de PASAPAS

> LMOC1 : LISTMOTS des mots-cles definissant les resultats a produire:
        - 'DEPL' : Deformee
        - 'CONT' : Isovaleur des Contraintes
        (eventuellement suivi du nom de la composante)
        - 'VAR' : Isovaleur des Variables Internes
        - 'TEMP' : Isovaleur du champ de Temperature
        - 'REAC' : Vecteur des Reactions
        - 'EVOL' : Trace d'Evolutions definies dans TOPT1 . 'EVOL'
        Rem : un seul trace d'isovaleur est possible par appel

  Rem : en l'absence de LMOC1,
        - si la sortie graphique est 'X', un menu permettant de
        choisir les resultats et le pas de temps est propos�;
        - si la sortie graphique est differente, l'isovaleur du champ
        de contraintes sur le maillage deforme est trace par defaut
        pour tous les pas de temps.

> TOPT1 : TABLE facultative d'options contenant :

- dans le cas d'une evolution :
  TOPT1 . 'EVOL' : TABLE obligatoire dans le cas d'une Evolution
  TOPT1 . 'EVOL' . 'TYPE' = MOT |'ESPA'  pour une evolution spatiale
        |'TEMP'  pour une evolution temporelle

  TOPT1 . 'EVOL' . 'COMP' = MOT : nom de la composante a tracer
  TOPT1 . 'EVOL' . 'TITR' = MOT : titre du trace

- dans le cas d'une evolution temporelle (TEMP) d'un chpoint :
  TOPT1 . 'EVOL' . 'POIN' = POINT dont on souhaite l'evolution

- dans le cas d'une evolution temporelle (TEMP) d'un mchaml :
  TOPT1 . 'EVOL' . 'ZONE' = ENTIER numero de la zone,
  TOPT1 . 'EVOL' . 'ELEM' = ENTIER numero de l element,
  TOPT1 . 'EVOL' . 'PTG' = ENTIER numero du point de Gauss
        dont on souhaite l'evolution

- dans le cas d'une evolution spatiale (ESPA) :
  TOPT1 . 'EVOL' . 'LIGN' = MAILLAGE de SEG2 sur lequel on souhaite
        l'evolution

- dans le cas d'une deformee :
  TOPT1 . 'AMPL' = FLOTTANT indiquant le facteur d'amplification de la
        deformee le cas echeant

>'CHAR' : MOT-cle indiquant que l'on souhaite visualiser le chargement

> TOPT2 : TABLE facultative d'options contenant :
  TOPT2 . 'TYPE' = MOT | 'MECA'  : type de chargement a tracer
        | 'T'
        | 'DEFI'
        |  ...
  TOPT2 . 'COMP' = MOT : composante eventuelle (FX ou FY par ex.)

  Exemples : plas1.dgibi, explochar.dgibi

  Cas d'une table BASE_MODALE ou LIAISONS_STATIQUES :

> TAB1 : TABLE issue de VIBR ou d'un calcul par sous-structuration
        dynamique (IDLI, BLOQ, RESO, REAC)

> LMOC1 : LISTMOTS des mots-cles definissant les actions a produire
        parmi :
        - 'TABL' : pour imprimer sur le terminal les resultats
        (mode, frequence, masse generalisee, ...)
        sous le forme d'un tableau de synthese.
        - 'DEFO' : pour tracer sur le sortie graphique les deformees
        modales.
        - 'DEF0' : (le dernier caractere etant le chiffre zero)
        pour tracer en superposition des deformees
        le maillage non deformee en gris
        - 'VTK' : pour sortir au format VTK (cf. Paraview) les
        deformees modales.
        - 'LIST' : pour generer aux indices LISTE_DEFORMEES,
        LISTE_FREQUENCES et LISTE_MASSES de la table
        d'entree les LISTCHPO, LISTREEL et LISTREEL
        correspondants.
        - 'MAIL' : pour generer a l'indice MAILLAGE_REPERE le
        maillage de POI1 contenant l'ensemble des points
        reperes des modes.

        Rem : si LMOC1 n'est pas fourni, on realise par defaut les
        actions : 'TABL' 'DEFO' 'DEF0' et 'MAIL'.

> TOPT1 : TABLE facultative d'options contenant :
  TOPT1 . 'LISTE_MODES' : liste des modes a traiter
  TOPT1 . 'MAILLAGE' : maillage sur lequel tracer les deformees
        (si different de celui de la base modale)
  TOPT1 . 'TITRE' : debut de titre lors du trace des deformees
  TOPT1 . 'LEGENDES' : legendes a ajouter a la fin du titre
        lors du trace des deformees
  TOPT1 . 'FICHIER_VTK' : nom du fichier pour les sorties VTK
  TOPT1 . 'MAILLAGE_2' : maillage supplementaire a tracer
  TOPT1 . 'MAILLAGE_VECTEUR' : points support pour lesquels on
        souhaite tracer le vecteur deplacement
  TOPT1 . 'AMPLIFICATION_RELATIVE': valeur de l'amplification relative
        de la deformee (5% par defaut)
  TOPT1 . 'OPTIONS_TRAC': liste des options a passer a TRAC (CHAINE)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## EXTC [Maillage Points]
Operateur EXTC

  OBJ2 = EXTC OBJET1 I ;

Objet : extraire les points centre ou face d'un objet maillage

        type FACEL

 OBJET1 objet maillage type FACEL de type SEG3 obligatoirement
        (ptc1 ptface ptc2)

 I : indice valant 1,2 ou 3 indiquant la rangee que l'on extrait

 OBJET2 : objet maillage resultat de type POI1

## EXTE [Entree-Sortie Entree-Sortie]
    Operateur EXTE

    TABS = EXTE COMMANDE (! ENTIn ) ..... ;
        ! FLOTn
        ! MOTn
        ! LISTREELn
        ! LISTENTIn
        ! TABLEn
        ! 'RC'

    Objet :

    L'operateur EXTE appele une commande exterieur a Castem, lui
transmet des valeurs et range dans une table ses resultats.

    La commande lit les valeurs sur son entree standard et ecrit les
resultats sur sa sortie standard.

    Les valeurs peuvent etre des entiers, des flottants, des mots, des
listentiers, des listreels.

    Si une table est fournie, c'est son contenu (indice par des
entiers positifs) qui est transmis.

    Le mot cle RC indique que l'on veut inserer un retour chariot.

    Les resultats sont ranges dans la table TABS, indices par des
entiers.

    Exemple :

 TABS = EXTE 'bc' 1 + 2 'RC' 3 * 6 'RC';

    EXTE appele la commande unix bc (basic calculator) et lui passe en
entree 1 + 2 puis sur une autre ligne 3 * 6.

    En sortie, sur un systeme UNIX possedant bc, TABS contient avec
comme indice 1 l'entier 3 et comme indice 2 l'entier 18. Sinon TABS
est vide.

## EXTR [Langage Objets]
    Operateur EXTRAIRE

        OBJET1 = EXTRAIRE OBJET2 OBJET3 ;

    Objet :

    L'operateur EXTRAIRE permet d'extraire de l'objet OBJET2
le composant d'indice OBJET3.

    Operations possibles :

|  OBJET2  |  OBJET3  |  OBJET1  |
|  MOT  |  |  TABLE  |
|  MOT  |  ENTI1 (ENTI2)  OU  LISTENTI  |  MOT  |
|  LISTREEL  |  ENTIER  |  FLOTTANT  |
|  LISTREEL  |  LISTENTI  |  LISTREEL  |
|  LISTENTI  |  ENTIER  |  ENTIER  |
|  LISTENTI  |  LISTENTI  |  LISTENTI  |
|  LISTMOTS  |  ENTIER  |  MOT  |
|  LISTMOTS  |  LISTENTI  |  LISTMOTS  |
|  LISTCHPO  |  ENTIER  |  CHPOINT  |
|  LISTCHPO  |  LISTENTI  |  LISTCHPO  |
|  LISTCHPO  |  'VALE' (MOT1|LMOT1) (POIN1)  |  LISTREEL  |
|  MCHAML  |  MOT ENTIER ENTIER ENTIER  |  FLOTTANT  |
|  MCHAML  |  MOT ENTIER ENTIER ENTIER  |  OBJET  |
|  MCHAML  |  'TITR' OU 'TYPE'  |  LISTMOTS  |
|  MCHAML  |  'MAIL'  |  MAILLAGE  |
|  MCHAML  |  'COMP' ( MODL1 )  |  LISTMOTS  |
|  MCHAML  |  'CONS' ( MODL1 )  |  LISTMOTS  |
|  MCHAML  |  'DEVA'  |  LISTMOTS  |
|  MCHAML  |  'COVA'  |  LISTMOTS  |
|  MCHAML  |  'NBZO'  |  ENTIER  |
|  MMODEL  |  'MAIL'  |  MAILLAGE  |
|  MMODEL  |  'MAIL' 'FROT'  |  MAILLAGE  |
|  MMODEL  |  'ZONE'  |  TABLE  |
|  MMODEL  |  MOT1  MOT2  |  MMODEL  |
|  MMODEL  |  MOT1  |  LISTMOTS  |
|  MMODEL  |  'PARA'  |  LISTMOTS  |
|  MMODEL  |  'NLOC'  |  LISTMOTS  |
|  MMODEL  |  'PHAS'  |  LISTMOTS  |
|  EVOLUTION  |  MOT ou 'ORDO' 'ABSC' N  |  LISTREEL  |
|  EVOLUTION  |  'COUR' | N  |  |  EVOLUTION  |
|  |  | MOT1  |  |  EVOLUTION  |
|  |  | LISTENT1 |  |  EVOLUTION  |
|  EVOLUTION  |  'PAS'  ENTI1  |  EVOLUTION  |
|  EVOLUTION  |  MOT1  'INDI' ENTI1 ('ZERO')  |  EVOLUTION  |
|  EVOLUTION  |  MOT1  FLOT2 ('ZERO')  |  EVOLUTION  |
|  EVOLUTION  |  'COUL' |  |  LISTMOTS  |
|  |  | N  |  MOT  |
|  SUPERELE  |  MOT  |  RIGIDITE  |
|  RIGIDITE  |  MOT1  ( MOT2 )  (MOT3)  |  MAILLAGE  |
|  RIGIDITE  |  MOT1  ( MOT2 )  |  RIGIDITE  |
|  RIGIDITE  |  'CONT'  |  TABLE  |
|  RIGIDITE  |  'COMP' ('DUAL')  |  LISTMOTS  |
|  RIGIDITE  |  'DIAG'  |  CHPOINT  |
|  RIGIDITE  |  | LISTMOT1 LISTMOT2 |  |  RIGIDITE  |
|  |  |  MOT1  MOT2  |  |  RIGIDITE  |
|  MATRIK  |  'COMP' ('DUAL')  |  LISTMOTS  |
|  MATRIK  |  'DIAG'  |  CHPOINT  |
|  MATRIK  |  | LISTMOT1 LISTMOT2 |  |  MATRIK  |
|  |  |  MOT1  MOT2  |  |  MATRIK  |
|  CHPOINT  | 'MAIL' ('NOMU')  |  MAILLAGE  |
|  CHPOINT  |  MOT1  POIN1 (NHARM)  |  FLOTTANT  |
|  CHPOINT  | 'VALE' (COMP1) (GEO1) ('NOID')|  LISTREEL  |
|  CHPOINT  | 'TITR'  |  MOT  |
|  CHPOINT  | 'COMP'  |  LISTMOTS  |
|  CHPOINT  | 'TYPE'  |  MOT  |
|  CHPOINT  | 'NATU'  |  MOT  |
|  BASEMODA  |  MOT  |  SOLUTION  |
|  BASEMODA  |  MOT  |  RIGIDITE  |
|  DEFORME  |  MOT  |  FLOTTANT  |
|  CHARGEME  |  'CHAR' (ENTIER)  |  CHARGEME  |
|  CHARGEME  |  'CHAM' (ENTIER)  | CHPOINT,MCHAML |
|  CHARGEME  |  'TRAJ' (ENTIER)  |  CHPOINT  |
|  CHARGEME  |  'EVOL' (ENTIER)  |  EVOLUTIO  |
|  CHARGEME  |  'VITE' (ENTIER)  |  EVOLUTIO  |
|  CHARGEME  |  'LOBJ' (ENTIER)  |  LISTOBJE  |
|  CHARGEME  |  'LREE' (ENTIER)  |  LISTREEL  |
|  CHARGEME  |  'COMP'  |  LISTMOTS  |
|  CHARGEME  |  'LIE '  |  CHARGEME  |
|  CHARGEME  |  'LIBR'  |  CHARGEME  |
|  CHARGEME  |  MOT  |  CHARGEME  |
|  CHARGEME  |  LISTMOTS  |  CHARGEME  |
|  CHARGEME  |  MOT  'TABL'  |  TABLES  |
|  NUAGE  |  'COMP'  |  LISTMOTS  |
|  NUAGE  |  'MAXI' MOT  |  NUAGE1  |
|  NUAGE  |  'MINI' MOT  |  NUAGE1  |
|  NUAGE  |  'INFE' MOT FLOTTANT  |  NUAGE1  |
|  NUAGE  |  'SUPE' MOT FLOTTANT  |  NUAGE1  |
|  NUAGE  |  'ENTR' MOT FLOT1 FLOT2  |  NUAGE  |
|  NUAGE  |  MOT  |  OBJET  |
|  NUAGE1 = NUAGE ne comportant qu'un seul n-uplet  |
|  LISTOBJE  |  'TYPE'  |  MOT  |
|  LISTOBJE  |  ENTIER  |  OBJET1  |

    Remarque préliminaire :

    Si l'opérateur est appliqué à un véritable objet (ex. : LISTREEL)
    il crée un nouvel objet (dans cet ex. : un FLOTTANT).
    Par contre, s'il est appliqué à une suite d'objets (ex. : LISTCHPO
    ou TABLE), alors il ne fait qu'affecter un nom à un objet déjà
    existant (ex. : un CHPOINT dans le cas d'un LISTCHPO).

 >> CAS D'UN OBJET DE TYPE 'MOT'

    1) Il s'agit de fabriquer une TABLE contenant tous les objets nommés
       qui ont pour type le mot lu. La TABLE est indicée par des entiers
       1, 2, 3, etc...

    2) Extraction d'une sous-chaîne de caractères :

        - soit de la position ENTI1 incluse jusqu'à la fin de la chaîne
        - soit de la position ENTI1 jusqu'à la position ENTI2 (incluses)
        - soit les caractères indiqués dans un LISTENTI
[… notice tronquée ; texte complet dans l'archive PCW_24]

## FACE [Maillage Surfaces]
    Operateur FACE

    GEO1 = FACE (N1) GEO2 ;

    Objet :

    L'operateur FACE sert a retrouver la N1-ieme face d'un objet
massif GEO2 (type MAILLAGE) maille avec des cubes.

    Commentaire :

    N1 : numero de la face (type ENTIER)

    GEO2 : element massif (type MAILLAGE)

    GEO1 : face de l'element (type MAILLAGE)

    Remarque :

    La premiere face est conventionnellement la face du bas (face
initiale d'un objet engendre par translation) et la deuxieme, la face
du haut (opposee a la premiere).

    Si N1 n'est pas indique, FACE rend toutes les faces de l'objet.

    Exemple: F1 F2 F3 = FACE MONVOLUM ;

## FACTORIE [Mathematiques Fonctions] (proc)
Procedure FACTORIE

ENTI1 = FACTORIE ENTI2 ;

Objet :

Cette procedure calcule la factorielle d'un entier.

Commentaire :

ENTI2 : nombre dont on veut la factorielle (type ENTIER)

ENTI1 : factorielle du nombre ENTI2 (type ENTIER)

## FANT [Langage Objets]
    Directive FANTOME

        FANTOME TAB1 INDICE1 ;

    Objet :

    La directive FANTOME permet d'attribuer a un objet contenu dans une table
le type FANTOME. Pour cela il faut que l'objet ait ete pealablement sauvegarde
par la directive SAUVER.

    L'interet de cette operation est de pouvoir recuperer la place memoire des
objets prenant le type FANTOME.

     Commentaires :
       TAB1 est l'objetc de type TABLE

       INDICE1 est l'indice permettant d'atteindre l'objet a faire disparaitre

## FATI [Mecanique Rupture]
Operateur FATI

TAB1 = 'TABLE' 'PASAPAS' ;
TAB1.'MODELE' = MO1 ;
'PASAPAS' TAB1 ;
CHAR1 = 'CHAR' TAB1.'TEMPS' TAB1.'CONTRAINTES' ;

CHE2 = 'MANU' 'CHML' MO1 'APAP' -0.33 'BPAP' 8.e7
      'ADVK' -0.34 'BDVK' 8.1e7 'ASIN' -0.35 'BSIN' 8.2e7
      'ACRO' -0.36 'BCRO' 8.3e7 'A_DC' -0.37 'B_DC' 8.4e7
      'TYPE' 'CARACTERISTIQUES' 'STRESSES' ;

CHE3 = 'FATI' MO1 CHAR1 CHE2 (REEL1 REEL2 MOT4 'SEUIL' |MOT5 );
        |REEL3

(MOT4 : 'TOUS','DVKP','PAPA','SINE','CROS','DC','VMIS')
(MOT5 : 'TOUS')

'TRAC' MO1 CHE3 ;

EV5 = 'EXTR' CHE3 'PTAU' IZO IEL IGA ;
'DESS' EV5 ;
'OPTI' 'SORT' 'test.csv' ;
'SORT' 'EXCE' EV5 ;

Objet :

En utilisant le mot cle 'TOUS', l'operateur FATI produit
CHE3 dont les composantes correspondent à
l'évaluation de différents critères de fatigue :
DANG VAN, PAPADOPOULOS, SINES, CROSSLAND, DC et VON MISES
a partir des resultats d'un calcul de cycle de chargement
avec PASAPAS.
On peut preciser les bornes du cycle avec REEL1 < REEL2.

Si on précise 'DVKP' ou 'PAPA' ou 'SINE' ou 'CROS' ou 'DC'
la 1ere composante de CHE3 est l'évaluation du critere,
la 2nde de nom 'PTAU' est, lorsque le critere évalué
est supérieur à une valeur donnée qui est -0.2 par defaut
modifiable à l'aide du mot-clé 'SEUIL' suivi de 'TOUS'
ou d'un réel, une paire de courbes
dont la 1ere est le trajet du deviateur ('DVKP' ou 'PAPA')
ou se réduit au point critique ('SINE', 'CROS' ou 'DC')
et la 2nde la droite de DANG VAN dans le plan (P, TAU),
dont les coefficients sont 'A***' et 'B***'
spécifiés par CHE2.
Ces courbes peuvent être exportees vers EXCEL.

Commentaire :

MOD1 : type MODELE
CHAR1 : type CHARGEMENT
CHE2 : type MCHAML, titre/type CARACTERISTIQUES
MOT4, MOT5 : type MOT
CHE3 : type MCHAML, titre/type FATIGUE
EV5 : type EVOLUTION
REEL1, REEL2, REEL3 : type FLOTTANT

## FCOURANT [Fluides Resolution] (proc)
Procedure FCOURANT

CHPO1 = FCOURANT MAIL1 CHPO2 (RIG1 (CHPO3)) (TAB1) ;

Objet :

Cette procedure calcule la fonction de courant scalaire, en 2D et 2D
axisymetrique, correspondant au champ de vitesse a divergence nul
donne.

Commentaire :

  MAIL1 : Domaine de definition de la vitesse (type MAILLAGE)

  CHPO2 : Champ de vitesse (type CHPOINT)

  RIG1 : Conditions sur la fonction de courant
  CHPO3 (Par defaut, on bloque le premier noeud de MAIL1)

  TAB1 : table optionnelle precisant les options pour le solveur
        de systeme lineaire KRES (cf. notice KRES)

  CHPO1 : Fonction de courant (type CHPOINT, nom de composante
        'PSI')

Remarques :

  1) Faute de modele, les conditions sur la fonction de courant
     (RIG1) doivent porter sur une inconnue de nom 'T'.

  2) Si TAB1 n'est pas presente, on utilise RESO pour resoudre le
     systeme lineaire.

Notes :

On utilise les definitions suivantes pour la fonction de courant psi
en fonction du champ de vitesse u :

  1) En 2D plan : dpsi/dx = u_y
        dpsi/dy = - u_x

  2) En 2D axisymetrique : dpsi/dr = ( 2pi r) u_z
        dpsi/dz = (-2pi r) u_r

Ces definitions sont compatibles avec l'interpretation suivante :
psi(B) - psi(A) = debit volumique (m^2.s-1 en 2D plan, m^3.s-1 en 2D
axi) traversant le segment [AB]. Le sens positif est celui du
vecteur faisant un angle de +90 degres avec le vecteur AB.

En 2D axi, psi est appelee fonction de courant de Stokes.
Elle est egale a la composante hors plan du potentiel vecteur
associe a u dans la decomposition de Helmholtz, divisee par la
coordonnee radiale r.

Si le champ de vitesse u n'est pas approximativement a divergence
nulle, les isovaleurs de la fonction de courant psi ne seront pas
necessairement tangentes aux vecteurs vitesse.

## FDENS [Mathematiques Statistiques] (proc)
   Procedure FDENS
   ---------------- REPART

 FLO2 = FDENS TAB1 FLO1;

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
La procedure FDENS calcule la densite au point FLO1 d'une variable aleatoire
dont les caracteristiques sont donnees dans TAB1.

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

## FDT [Mathematiques Fonctions]
    Operateur FDT

    EVOL1 =  FDT  MOT1 |'CONS'  FLOT1  LREEL1  | ;
        |  |
        |'NOCO'  | 'COUP'  LREEL2 | | ;
        |  |  | |
        |  | LREEL3  | | ;
        |  |
        | LREEL4  LREEL5  | ;

    Objet :

    L'operateur FDT permet de creer une fonction (type EVOLUTION)
@ partir d'une liste d'ordonnees et d'un pas de temps.

    Commentaire :

    MOT1 : type de la fonction (type MOT) : 'ACCE', 'DEPL', etc...

    'CONS' : mot-cle indiquant que le signal est a pas constant

     FLOT1 : pas de temps (type FLOTTANT)

     LREEL1 : valeurs du signal (type LISTREEL)

    'NOCO' : mot-cle indiquant que le signal est a pas variable

    'COUP' : mot-cle indiquant que le signal est donne sous la
        forme de couples

     LREEL2 : objet contenant les couples Ti,F(Ti) (type LISTREEL)

     LREEL3 : objet contenant Ti,i=1,N puis F(Ti),i=1,N
        (type LISTREEL)

     LREEL4 : objet de type LISTREEL contenant un seul reel
        (0. ou la valeur du pas de temps).

     LREEL5 : objet de type LISTREEL contenant le signal
        (bande CASTEM2000 engendree par TIROIR)

## FFOR [Mecanique Modele]
    Operateur FFOR
    -------------- RAYN

     CH2 = FFOR MODL1 CHE1 ;

    Objet :

    Cet operateur calcule la matrice des facteurs de forme associee a
une geometrie qui discretise une cavite.

    Commentaire :

    MODL1 : structure modelisee (type MMODEL)

    CHE1 : champ par element de caracteristiques qui contient ou non
        la valeur du coefficient d'absorption

    CH2 : champ contenant la matrice des facteurs de forme
        (type MCHAML)

    Remarques :

 1. L'orientation trigonometrique des elements (associee a
    l'ordre de description des noeuds dans chaque element)
    definit une direction normale qui doit correspondre au
    cote qui rayonne.
    Cette condition est indispensable.

 2. L'axe de revolution en axisymetrique ne doit pas etre maille.
    Un axe (ou un plan) de symetrie ne doit pas etre maille.

 3. L'option 'SYME' n'est pas disponible en axisymetrique (pour
    definir un axe autre que l'axe de revolution).

 4. L'option IMPI de l'operateur OPTI fournit les erreurs commises
    sur les bilans et les conditions de reciprocite.

 5. Dans le cas d'un milieu absorbant le coefficient d'absorption
    doit etre negatif. Le milieu contenu dans la cavite est a
    temperature uniforme et ne diffuse pas.
    Cette option n'est pas compatible avec les options 'SYME'
    ou 'CVXE'.

 6. L'unite de la temperature est le degre Kelvin
    (cf. operateur RAYN).

## FIABILI [Mecanique Resolution] (proc)
    Procedure FIABILI
    ----------------- FDENS REPART

    FIAB TAB1 ;

        TAB1 . param_optimisation . methode
        . param_optimisation . t0
        . param_optimisation . s0
        . param_optimisation . vxmin
        . param_optimisation . vxmax
        . param_optimisation . vcmax
        . param_optimisation . maxiteration
        . noms_des_variables
        . max_iteration
        . fct_limite
        . grad_fct_limite
        . param_va . k . typva
        . param_va . k . A
        . param_va . k . B
        . param_va . k . LAMBDA
        . param_va . k . MU
        . param_va . k . MOYENNE
        . param_va . k . ECART_TYPE
        . param_va . k . TAU
        . param_va . k . K
        . param_va . k . W
        . param_va . k . MIN
        . param_va . k . MAX
        . param_va . k . U
        . matcov
        . points_initiaux
        . critere
        . resu . i . indfiab
        . resu . i . <<nom_d_une_va>>
        . resu . i . proba_defaillance
        . resu . i . facteurs_de_sensibilite
        . resu . i . vecteurs_des_sensibilites

    Objet :
 La procedure FIABILI cherche la probabilite de defaillance d'une
structure. Cette probabilite est evaluee par la methode FORM.
La procedure sort l'indice de fiabilite de Hasofer-Lind.
La procedure sort les sensibilites de chacune des variables aleatoires.

    Donnees :
  TAB1 . 'PARAM_OPTIMISATION' : est une table qui contient les parametres
pour la methode d'optimisation. On utilise l'operateur EXCE de castem 2000 et
on se reportera a la notice de cet operateur pour plus de detail. Attention,
les valeurs sont passees ici dans des listreels.

  TAB1 . 'PARAM_OPTIMISATION' . 'METHODE' : (facultatif) est un mot. Le choix
        est entre 'STA', 'MOV', 'LIN'.

  TAB1 . 'PARAM_OPTIMISATION' . 'T0' : (facultatif) Reel compris entre 0 et 1.
  TAB1 . 'PARAM_OPTIMISATION' . 'S0' : (facultatif) Reel compris entre 0 et 1.
  TAB1 . 'PARAM_OPTIMISATION' . 'VXMIN' : listreel contenant les valeurs
        minimales que peuvent prendre les
        variables aleatoires.
  TAB1 . 'PARAM_OPTIMISATION' . 'VXMAX' : listreel contenant les valeurs
        maximales que peuvent prendre les
        variables aleatoires.
  TAB1 . 'PARAM_OPTIMISATION' . 'VCMAX' : listreel contenant les constantes
        Cjmax.
  TAB1 . 'PARAM_OPTIMISATION' . 'MAXITERATION' :(facultatif) change la valeur
        maximale autorisee pour le nombre
        d'iterations dans EXCE.
        (Par defaut 100)
  TAB1 . 'NOMS_DES_VARIABLES' : listmots contenant le nom de chaque variable.
  TAB1 . 'MAX_ITERATION' : (facultatif) change la valeur maximale autorisee
        pour le nombre de fois ou on lance EXCE.
  TAB1 . 'FCT_LIMITE' : table indicee de 1 au nombre de fonctions limites
        qui contient les chaines de caractere qui sont les
        noms des procedures calculant les fonctions limites.
        Ces procedures reçoivent en entree un listreel de valeurs prises
        par les variables aleatoires. elles sortent un reel qui est la valeur
        de la fonction limite en ce point.
  TAB1 . 'GRAD_FCT_LIMITE' :(facultatif) table indicee de 1 au nombre de
        fonctions limites
        qui contient les chaines de caractere qui sont les
        noms des procedures calculant les gradients des
        fonctions limites.
        Ces procedures reçoivent en entree un listreel de valeurs prises
        par les variables aleatoires. elles sortent un listreel qui contient
        le gradient de la fonction limite en ce point.
        Cet indice de la table est optionnels. il faut eviter de le donner
        pour limiter le nombre d'appels a la fonction limite.

  TAB1 . 'PARAM_VA' : est une table indicee de 1 au nombre de variables
        aleatoires.

  TAB1 . 'PARAM_VA' . k : est une table qui contient les differents parametres
        necessaire a la connaissance de la kieme variable
        aleatoire.
  TAB1 . 'PARAM_VA' . k . 'TYPVA' : chaine de caractere contenant le type de
      la kieme variable aleatoire.
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
[… notice tronquée ; texte complet dans l'archive PCW_24]

## FILC [Mathematiques Autres] (proc)
Procedure FILC

EV2 = FILC EV1 FO DF1

Objet :

La procédure FILC permet de calculer pour un signal donné
une evolution filtree par un passe-bas

Commentaire :

EV1 : objet de type EVOLUTION
FO : frequence de coupure de type FLOTTANT
DF1 : intervalle pour ajuster la coupure du contenu
        frequenciel de type FLOTTANT
EV2 : objet de type EVOLUTION

 | Modu  Fonction de filtrage
 |
 |  DF1
 |  |------------|
 |
 |____________________1
 |  *  *
 |  *
 |  *
 |  *
 |  *  * __________0
 |---------------------------|  Freq
        F0

Contacts :
Alberto FRAU (CEA/DEN/DANS/DM2S/SEMT/EMSI)
Benjamin RICHARD (CEA/DEN/DANS/DM2S/SEMT/EMSI)

## FILT [Mathematiques Autres]
    Operateur FILT

   EVOL1 = FILT N1 'TYPE' | 'PHAU' FLOT1 |('SORT'|'REIM'|) 'DFRQ' FLOT2
        | 'PBAS' FLOT1 |(  |'MOPH'|)
        | 'OMEG' ENTI1

    Objet :

    L'operateur FILT permet de calculer les filtres PASSE-HAUT,
PASSE-BAS ...

    Commentaire :

    N1 : on utilise un nombre de points egal a 2**N1 (type ENTIER)

   'TYPE' : mot-cle suivi de :

   'PHAU' : pour un filtre PASSE-HAUT de frequence de coupure FLOT1
        (type FLOTTANT).

   'PBAS' : pour un filtre PASSE-BAS de frequence de coupure FLOT1
        (type FLOTTANT).

   'OMEG' : pour un filtre en OMEGA de puissance ENTI1 (type ENTIER).

   'SORT' : mot-cle suivi de :
   'REIM' : filtre defini sous forme parties reelles et imaginaires
   'MOPH' : filtre defini sous forme module et phase (par defaut)

   'DFRQ' : mot-cle suivi de :
    FLOT2 : valeur du pas en frequence en Hz (type FLOTTANT).

    EVOL1 : resultat de type EVOLUTION.

## FILTREKE [Fluides Resolution] (proc)
   Procedure FILTREKE

   SYNTAXE ( EQEX ) : Cf operateur EQEX

   'OPER' 'FILTREKE' U0 L0 NU UN 'INCO' 'KN' 'EN'

   OBJET :

Cette procedure filtre les valeurs de k et de epsilon du modele de
turbulence K - epsilon . Les contraintes suivantes sont imposees :
0 < k < Max(UN,U0)**2
epsilon > Cnu * k**1.5 / L0 > 0
ou Cnu = 0.09 est une constante du modele K-epsilon
ou U0 est une vitesse de reference limitant l'intensite turbulente.
ou L0 est une echelle de longueur limite.
=> Nut < U0*L0

   Commentaires

   U0 Vitesse de reference
        FLOTTANT ou MOT

   L0 Echelle de longueur
        FLOTTANT ou MOT

   NU Viscosite cinematique
        FLOTTANT ou MOT

   UN Champ de vitesse
        CHPOINT VECT SOMMET ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice donne.

## FIMP [Thermique Limites]
   Operateur FIMP

   I)

   SYNTAXE (EQEX) : Cf operateur EQEX

 'ZONE' $paroi 'OPER' FIMP COEF 'INCO' 'TN'

   OBJET :

   Discretise une densite de flux ou une source et calcule l'increment

       EN 2D
       elements lignes (SEG2 ou SEG3) -> Flux (en K/ms)
       elements massifs (TRI3 TRI7 etc) -> Source volumique (en K/m2s)
       EN 3D
       elements lignes (SEG2 ou SEG3) -> Pas de sens !!
       elements coques (TRI3 TRI7 etc) -> Flux (en K/m2s)
       elements massifs (CUB8 CU27 etc) -> Source volumique (en K/m3s)

    Commentaires :

    $paroi Objet MMODEL de type 'NAVIER_STOKES' associe a la
        surface sur laquelle porte le flux

    COEF densite de flux CHPOINT SCAL CENTRE
        ou CHPOINT SCAL SOMMET
        ou FLOTTANT ou MOT
        (par convention un flux entrant est compte positivement)

    TN Champ de temperature (en K) CHPOINT SCAL SOMMET

L'operateur permet de calculer un terme source soit surfacique soit
volumique suivant la nature du support geometrique, pour l'inconnue
TN. Cette inconnue doit etre un CHPOINT SCAL SOMMET. Cependant une
extension est possible si on veut rajouter une source volumique
a l'equation Div U = 0
 pour cela on fait porter l'inconnue sur la pression (INCO PRES)
et on precise le support de la pression avec l'option INCOD.
Dans ce cas seul les supports geometriques volumiques sont autorises.
ex :
'OPTI' 'INCOD' KPRES
'ZONE' $MT 'OPER' 'FIMP' COEF 'INCO' 'PRES'
ou
 KPRES = 'CENTRE'
 ou 'CENTREP1'
 ou 'MSOMMET'

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice MOT.

   OPTION : (EQEX)

   Formulation element finis EF et EFM1 (par defaut)
   Inconnue duale INCOD SOMMET (option par defaut)

II Discretisation des Equations d'Euler

IIa : gaz parfait mono-constituent polytropique

Discretisation en VF "cell-centered" des equations d'Euler pour un gaz
parfait mono-constituent polytropique

Inconnues:

densite, quantite de mouvement (qdm), energie totale par unite de volume
(variables conservatives)

On peut calculer:

IIa.1 Calcul de la contribution de la force de gravite au residu

IIa.2 Calcul de la contribution de la force de gravite a la matrice
      jacobienne

IIa.1 Le residu

RCHRES = 'FIMP' 'VF' 'GRAVMONO' 'RESI' LISTINCO CHPRN CHPGN CHPGRAV ;

LISTINCO : objet de type LISTMOTS
        Noms de composantes du resultat (RCHRES)
        Il contient dans l'ordre suivant: le noms de la densite,
        de la qdm, de l'energie totale par unite de volume

CHPRN : CHPOINT contenant la masse volumique (une
        composante, 'SCAL').

CHPGN : CHPOINT contenant le qdm (deux composantes en 2D, 'UX ',
        'UY ', meme SPG que CHPRN).

CHPGRAV : CHPOINT contenant la gravite (deux composantes en 2D,
        'UX ', 'UY ', meme SPG que CHPRN).

RCHRES : objet de type CHPOINT (composantes = LISTINCO, meme SPG
        que CHPRN)

IIa.2 La matrice jacobienne

RJAC = 'FIMP' 'VF' 'GRAVMONO' 'JACOCONS' LISTINCO CHPRN CHPGN CHPGRAV ;

LISTINCO : objet de type LISTMOTS
        Il contient dans l'ordre suivant: le noms de la densite,
        de la qdm, de l'energie totale par unite de volume

CHPRN : CHPOINT contenant la masse volumique (une
        composante, 'SCAL').

CHPGN : CHPOINT contenant le qdm (deux composantes en 2D, 'UX ',
        'UY ', meme SPG que CHPRN).

CHPGRAV : CHPOINT contenant la gravite (deux composantes en 2D,
        'UX ', 'UY ', meme SPG que CHPRN).

RJAC : objet de type MATRIK
        (meme SPG que CHPRN)
        (inconnues primales = inconnues duales = LMOT1)
        Il contient le jacobien du residu par rapport aux variables
        conservatives.

III Discretisation des Equations de Navier-Stokes avec le
     modele turbulent k-epsilon

IIIa : gaz thermiquement parfait multi-constituent

Discretisation des Equations de Navier-Stokes multi-constituent
 avec le modele turbulent k-epsilon

Inconnues:

densite, quantite de mouvement (qdm), energie totale par unite de volume,
densites des especes qui sont dans (TABGAS.'ESPEULE'),
energie cinetique de la turbulence par unite de volume,
taux de dissipation de l'energie turbulente par unite de volume
(variables conservatives)

On peut calculer:

IIIa.1 la contribution de la force de la gravite,
       de les termes sources des equations de conservation
       des especes et des termes sources des equations
       d'energie cinetique de la turbulence et de taux de
       dissipation de l'energie turbulente au residu

Le Residu
[… notice tronquée ; texte complet dans l'archive PCW_24]

## FIN [Langage Base]
    Directive FIN

    Objet :

    La directive FIN s'utilise dans deux cas :

    | 1er cas |
    FIN ;

    Objet :

    La directive FIN provoque l'arret de l'execution de CASTEM2000,
si elle est executee.

    | 2eme cas |
    FIN BLOC1 ;

    Objet :

    La directive FIN sert a terminer la definition d'un bloc BLOC1,
commencee par la directive REPETER.

## FINM [Langage Methodes]
    Operateur FINMETH
    ----------------- RESP

    FINMETH ( OBJ1 OBJ2 ..... ) ;

    Objet :

    L'operateur FINMETH termine la definition d'une procedure-methode
qui a ete commencee par DEBMETH.

    Commentaire :

    Le mot FINMETH est suivi des noms locaux OBJ1 OBJ2 ... des objets
 resultats s'il y en a .

    Voir l'operateur FINPROC.

## FINP [Langage Methodes]
   Operateur FINPROC
   ----------------- RESP

   FINPROC ( OBJ1 OBJ2 ..... ) ;

   Objet :

   L'operateur FINPROC termine la definition d'une procedure.

   Commentaire :

   Le mot FINPROC est suivi des noms locaux OBJ1 OBJ2 ... des objets
resultats s'il y en a .

   Voir l'exemple de l'operateur DEBPROC.

## FINS [Langage Base]
    Directive FINSI
    --------------- SINO

    FINSI ;

    Objet :

    Les directives SI, SINON et FINSI permettent l'execution
conditionnelle de donnees suivant la valeur de la variable logique BOOL1

    Exemple :

     BOOL1 = I > 10 ;

     SI BOOL1 ;

       J= 2 * I ; COMM execute si I est plus grand que 10 ;
       LIST J ;

     SINON ;

       J= I ; COMM execute si I est plus petit que 10 ;

     FINSI ;

    Remarque : SINON est optionnel.

## FINVREPA [Mathematiques Statistiques] (proc)
   Procedure FINVREPA
   ------------------- REPART

   FLO2 = FINVREPA TAB1 FLO1;

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
La procedure FINVREPA calcule au point FLO1 la valeur de l'inverse de
 la fonction de repartition de la variable aleatoire dont les
caracteristique se trouvent dans TAB1.
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

## FION [Multi-physique Multi-physique]
Operateur FION

    CHPO2 = FION TAB1 CHPO1 ;

     Objet
    Calcul de la force ionique d'une solution chimique en tout point
    d'un domaine.

    Commentaires
    TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

    CHPO1 nom d'un objet de type CHPOIN ayant une composante pour
        chaque espece en solution, et contenant la concentration
        de chaque espece en solution.

    CHPO2 objet de type CHPOIN ayant une composante scalaire et
        contenant la force ionique en chaque point.

## FISS [Fluides Resolution]
  Operateur FISS

   RES = FISS MODL1 MAT1 TAB_CL

  Objet :

  Cet operateur calcule le debit de fuite d'un melange air-vapeur
circulant dans une macrofissure traversante (ouverture superieure
a 25 microns), en regime permanent pour une temperature de paroi
donnee et des pressions amont et aval imposees.

L'operateur utilise une discretisation fluide monodimensionnelle :
l'ouverture (petite dimension de la fissure) et l'etendue (grande
dimension) ne sont pas maillees.

Le modele diphasique est homogene (les 2 phases ont les
memes vitesse et temperature).

  Commentaires:

  MODL1 : objet modele (type MMODEL)
        (le maillage contenu dans MODL1 est constitue d'elements
        SEG2 definissant le parcours de la fissure dans le sens
        amont aval)
  MAT1 : champ des caracteristiques materielles (type MCHAML,
        sous-type CARACTERISTIQUES)
  TAB_CL : table des conditions aux limites (type TABLE) :

     TAB_CL.'PRESSION_TOTALE_AMONT' : pression totale en amont de la
        fissure (Pa) (type flottant)
     TAB_CL.'PRESSION_VAPEUR_AMONT' : pression partielle de vapeur en
        amont de la fissure (Pa)
        (type flottant)
     TAB_CL.'TEMPERATURE_AMONT' : temperature du gaz en amont de
        la fissure (°C) (type flottant)
     TAB_CL.'PRESSION_TOTALE_AVAL' : pression totale en aval de la
        fissure (Pa) (type flottant)
     TAB_CL.'TEMPERATURE_PAROI' : temperature de paroi (°C)
        (type CHPOINT)
     TAB_CL.'OUVERTURE' : ouverture de la fissure (m)
        (type CHPOINT)
     (TAB_CL.'ETENDUE') : etendue de la fissure (m)
        (type CHPOINT)
     (TAB_CL.'DEBIT_INITIAL') : debit d'initialisation
        (kg/m2/s) (type flottant)

  RES : champoint multicomposante de meme support que les deux
        champoints precedents, representant les grandeurs
        caracteristiques de l'ecoulement le long de la fissure.

     nom de  |
   composante | signification

       'P' : pression (Pa)
       'PV' : pression vapeur (Pa)
       'TF' : temperature (°C)
       'X : titre
       'U' : vitesse (m/s)
       'H' : coefficient d'echange (W/m2/K)
       'Q' : debit total (kg/s)
       'QA' : debit air (kg/s)
       'QE' : debit eau (liquide+vapeur) (kg/s)
       'RE' : nombre de Reynolds
       'F' : densite de puissance echangee entre le fluide et
        la paroi (W/m2)

  Remarque:

  Il faut remplir TAB_CL avant chaque appel a FISS.

## FIXHC [Mecanique Resolution] (proc)
Procedure FIXHC

Cette procedure est appelee par PASAPAS, elle cree un champ
par element permettant d assurer la continuite du trajet de
fissuration dans le cas d un probleme resolu par la methode
E-FEM. La continuite est assuree en resolvant un probleme
de conduction a la fin de chaque pas de temps.

## FLAM [Multi-physique Multi-physique]
    Operateur FLAM

 1a) ZH2 ZO2 ZN2 ZH2O Q = FLAM | 'EBU'  | RHO CV MOT1 R YH2 YO2 YN2
        | 'LAMINAIR' |

        YH2O T Dt | K E YH2u C_EBU (C0)  | ;
        |  |

 1b) RCHPO1 RCHPO2 RCHPO3 RCHPO4 = 'FLAM' 'HEAVYSID' CHPO1 FLOT1 FLOT2
        FLOT3 CHPO2 CHPO3 CHPO4 CHPO5 ;

 1c) RCHPO1 RCHPO2 RCHPO3 RCHPO4 = 'FLAM' 'ARRHENIU' CHPO1 FLOT1 FLOT2
        FLOT3 FLOT4 FLOT5 FLOT6 FLOT7 FLOT8
        CHPO2 CHPO3 CHPO4 CHPO5 ;

 2a) RCHPO1 = 'FLAM' 'CREBCOM' MOD1 FLOT1 FLOT2 CHPO1 ;

 2b) RCHPO1 RCHPO2 = 'FLAM' 'CREBCOM2' MOD1 TAB2 LMOT1 LREE1 CHPO1
     CHPO2 CHPO3 CHPO4 CHPO5 FLOT1 FLOT2 FLOT3 ;

    OBJET :

 1) Cet operateur integre du temps tn au temps tn+1=tn+Dt des equations
 differentielles ordinaires qui modelisent l'evolution temporelle des
 fractions massiques d'hydrogene, d'oxygene, d'azote et de vapeur d'eau
 selon la reaction globale,

        2 H_2 + O_2 ---> 2 H_2O

 Ainsi, on resoud entre tn et tn+1,

        dYH2/dt = C_H2 omega(...)
        dYO2/dt = C_O2 omega(...)
        dYH2O/dt = C_H2O omega(...)

 ou Yi est la fraction massique associee a l'espece i et les C_i
 sont des constantes dependantes de la stoechiometrie, et des masses
 molaires des differents constituants, et omega la vitesse de reaction.
 L'azote intervient uniquement comme espece neutre.
 Suivant l'option, la vitesse de reaction est donnee par une cinetique
 adaptee a la combustion en regime laminaire, a la combustion en regime
 turbulent de type Eddy Break-Up (EBU), ou une loi d'Arrhenius adaptee
 a la detonation (ARRHENIU), ou un modele de combustion infiniment
 rapide si la temperature est plus grande qu'une temperature seuil
 (HEAVYSID).

 2) Suivi du front de flamme selon le critere "CREBCOM"

   Commentaires :

1a) Cas 'LAMINAR', 'EBU'

   ZH2 : fraction massique de H2 au temps tn+1 (CHPOINT)
   ZO2 : fraction massique de O2 au temps tn+1 (CHPOINT)
   ZN2 : fraction massique de N2 au temps tn+1 (CHPOINT)
   ZH2O : fraction massique de H2O au temps tn+1 (CHPOINT)
   Q : energie liberee par la reaction (CHPOINT)
   RHO : densite du melange (CHPOINT)
   CV : capacite calorifique a volume constant (CHPOINT)
   MOT1 : dependance en T des CV ('LINEAIRE' ou 'QUADRATI')
   R : constante des gaz du melange (CHPOINT)
   YH2 : fraction massique de H2 au temps tn (CHPOINT)
   YO2 : fraction massique de O2 au temps tn (CHPOINT)
   YN2 : fraction massique de N2 au temps tn (CHPOINT)
   YH2O : fraction massique de H2O au temps tn (CHPOINT)
   T : temperature du melange (CHPOINT)
   Dt : pas de temps (REEL)
   K : energie cinetique turbulente (CHPOINT)
   E : taux de dissipation de K (CHPOINT)
   YH2u : fraction massique de H2 initiale (CHPOINT)
   C_EBU : constante du modele Eddy Break-Up (REEL)
   C0 : valeur seuil (defaut 1.d-4) (REEL) :
        Yh2/Yh2u > 1-C0 -> Q=0 ; Yh2/Yh2u < C0 -> Yh2=0

   N.B.: Tous les CHPOINTs ont une seule composante et le meme support
        geometrique : CENTRE ou SOMMET.

1b) Cas 'HEAVYSID'

   CHPO1 : CHPOINT contenant la temperature de seuil (en K;
        une composante, 'SCAL').

   FLOT1 : FLOTTANT contenant l'enthalpie de H2 a 0K (en J/kg)

   FLOT2 : FLOTTANT contenant l'enthalpie de O2 a 0K (en J/kg)

   FLOT3 : FLOTTANT contenant l'enthalpie de H2O a 0K (en J/kg)

   CHPO2 : CHPOINT contenant la masse volumique de
        l'hydrogene (en Kg/m^3; une composante, 'H2 ').

   CHPO3 : CHPOINT contenant la masse volumique de
        l'oxygene (en Kg/m^3; une composante, 'O2 ').

   CHPO4 : CHPOINT contenant la masse volumique de
        l'eau (en Kg/m^3; une composante, 'H2O ').

   CHPO5 : CHPOINT contenant la temperature (en K; une
        composante, 'SCAL').

   RCHPO1 : CHPOINT contenant la masse volumique de
        l'hydrogene apres la reaction (en Kg/m^3;
        une composante, 'H2 ').

   RCHPO2 : CHPOINT contenant la masse volumique de
        l'oxygene apres la reaction (en Kg/m^3;
        une composante, 'O2 ').

   RCHPO3 : CHPOINT contenant la masse volumique de
        l'eau apres la reaction (en Kg/m^3;
        une composante, 'H2O ').

   RCHPO4 : CHPOINT contenant la chaleur libere' (en J/m^3;
        une composante, 'SCAL').

   N.B.: Tous les CHPOINTs ont une seule composante et le meme support
        geometrique.

1c) CAS 'ARRHENIU'

   CHPO1 : CHPOINT contenant la temperature de seuil (en K;
        une composante, 'SCAL').

   FLOT1 : FLOTTANT contenant la constant A (en unites S.I.)

   FLOT2 : FLOTTANT contenant la constant b

   FLOT3 : FLOTTANT contenant la constant c
[… notice tronquée ; texte complet dans l'archive PCW_24]

## FLAMBAGE [Mecanique Resolution] (proc)
    Procedure FLAMBAGE

    TAB1 = FLAMBAGE TAB2 ;
        TAB2.'OBJM' .'LAM1' .'LAM2' .'CLIM'
        .'NMOD' .'SIG0' .'SIG1' .'MATE'
        .'CARA' .'RIGI' .'KSIG' .'MODE'
        .'PLAS' .'MOTA'

    Objet :

    Cette procedure permet de faire des calculs de flambage elastique
et plastique.

    Commentaire :

    TAB2 : Objet (type TABLE) dont le contenu doit etre :

   1)Dans le cas de l'utilisation des nouveaux objets MMODEL et MCHAML

      Indice Type objet Commentaire
        pointe

      'OBJM' MMODEL objet modele
      'LAM1' FLOTTANT coefficient multiplicateur minimal
      'LAM2' FLOTTANT coefficient multiplicateur maximal
      'NMOD' ENTIER nombre de modes propres desires
      'CLIM' RIGIDITE matrices associees aux blocages

    Puis au choix :

      'SIG1' MCHAML Champ de contraintes variant avec le
        multiplicateur du chargement
     ('SIG0') MCHAML Champ de contraintes ne variant pas
        avec le multiplicateur du chargement
      'MATE' MCHAML Proprietes materielles

     ('CARA') MCHAML Caracteristiques geometriques

    ou bien :

      'RIGI' RIGIDITE Matrice de rigidite
      'KSIG' RIGIDITE Matrice de rigidite geometrique

    TAB1 : Objet (type TABLE) contenant autant de tables que de modes
        calcules, et indicee par le numero du mode.
        Chacune des tables associee a un mode contient :

      Indice Type objet Commentaire
        pointe

      'LAMB' FLOTTANT Coefficient multiplicateur du chargement
      'DEPL' CHPOINT Mode propre norme
      'MODN' ENTIER Numero de l'harmonique de Fourier
      'MODM' ENTIER Numero du mode azimutal

    Remarque :

    Dans le cas d'une analyse en serie de Fourier, on peut chercher
 le flambage sur une famille d'harmoniques en donnant dans TAB2 :

      'MODE' LISTENTI Liste des harmoniques de Fourier

    Il faudra alors, pour definir les conditions aux limites, les
 construire avec l'option :

        OPTION FOURIER NOHARM ;

    On peut faire une analyse de flambage plastique en donnant :

      'PLAS' MOT Mot demandant le flambage plastique
      'MATP' MCHAML Materiau plastique tangent (cf MOTA)

    La methode utilisee est la methode du module tangent. On peut aussi
 donner comme matrice de rigidite (indice 'RIGI') la matrice tangente
 que l'on veut si l'on ne souhaite pas utiliser cette methode.

## FLOQUET [Mecanique Dynamique] (proc)
 Procedure FLOQUET

 lrprog liprog = FLOQUET TAB1;

 Objet :

Cette procedure est utilisee par la procedure CONTINU.
Elle calcule les coefficients de Floquet en determinant les valeurs
propres du determinant de Hill.

## FLOT [Mathematiques Fonctions]
Operateur FLOTTANT

FLOT1 = FLOTTANT ENTI1 ;
LREEL1 = FLOTTANT LENTI1 ;

FLOT1 = FLOTTANT MOT1 ;
LREEL1 = FLOTTANT LMOT1 ;

Objet :

L'operateur FLOTTANT convertit un entier ENTI1 (resp. une liste
d'entiers LENTI1) en un reel FLOT1 (resp. une liste de reels
LREEL1).

On peut fournir à l'operateur FLOTTANT un mot MOT1 (resp. une liste
de mots LMOT1) pour convertir une ou des chaines de caracteres en
un nombre reel FLOT1 (resp. une liste de reels LREEL1). Le symbole
separateur decimal depend du systeme utilise.

Exemples :

FLOT 25 => 25.00
FLOT '-1.5' => -1.50
ENTI '.2e3' => 200.00

## FLUX [Thermique Limites]
 Operateur FLUX

 CHPO1 = FLUX MMODE1 | FLOT1 GEO1  | ( 'DIRECTION' VEC1 ) (MOT1) ;
        |  |
        | CH2  |
        | CH3  LMOTS1  |

 Objet :

 L'operateur FLUX permet d'imposer un flux sur une partie du contour
 (resp. de l'enveloppe) d'une structure 2D (resp. 3D).

 Commentaire :

 CHPO1 : flux nodaux equivalents (type CHPOINT a 1 composante)

 MMODE1 : structure modelisee (type MMODEL).

 FLOT1 : valeur algebrique du flux (type FLOTTANT).

 GEO1 : cote de la structure soumis au flux (type MAILLAGE)

'DIRECTION' : mot-cle indiquant qu'on va donner la direction du flux
        (par defaut, le flux est dirige selon la normale a
        l'element).

 VEC1 : vecteur indiquant la direction du flux (type POINT) .

 CH2 : champ a 1 composante donnant la valeur algebrique des
        flux. CH2 peut etre de type CHAMELEM (flux exprime aux
        points de Gauss) ou de type CHPOINT (flux aux noeuds).

 CH3 : champ a 2 composantes pour les modeles massifs 2D
        et a 3 composantes pour les modeles 3D massifs.
        CH3 peut etre de type CHAMELEM ou CHPOINT.

 LMOTS1 : liste des composantes (type LISTMOTS) du champ CH3
        a prendre en compte (voir remarque 2).

 MOT1 : mot-cle qui indique pour les coques sur quelle peau se
        fait la convection :
        'SUPE' : en peau superieure
        'INFE' : en peau inferieure

 Remarque 1 :

 Un flux est compte positivement s'il est dirige vers l'interieur
 d'un element massif.

 Remarque 2 (pour la syntaxe avec LMOTS1) :

 Les composantes sont associees dans leur ordre de declaration dans
 LMOTS1 avec les directions 1 2 (3). Le produit scalaire est fait
 localement avec les normales. Le flux resultant est positif si le
 vecteur est dirige vers l'interieur d'un element massif.

 Remarque 3 (pour les coques) :

 La designation des peaux de la coque se fait par rapport a la
 normale exterieure de l'element : la peau superieure est placee
 dans le sens de la normale exterieure vis-a-vis du plan median.
 Dans le cas ou les elements ne sont pas orientes d'une façon
 coherente, il faut les reorienter en utilisant l'operateur ORIENT.

 Remarque 4 (pour l'option DIRE) :

 L'option DIRE exige que les produits scalaires DIRE*(normales
 elementaires) soient tous du meme signe (pas de replis de la surface)

 Remarque 5 :

 Si vous utilisez un MODELE plus grand que la zone ou le flux est
 defini par le CHPOINT CH2 ou les noeuds du maillage GEO1,
 alors les elements exterieurs touchant la frontiere voient un flux
 non nul, et seront eux aussi charges. Il est donc fortement
 conseille de fournir une reduction du MODELE sur les elements
 strictement concernes.

## FOFI [Mecanique Resolution]
 Operateur FOFI
 --------------

FORC1 = FOFISS MODL1 SIG1 GRDEP1 ( CAR1 ) ;

Objet :

L'operateur FOFI calcule le champ de forces nodales resultant de
l'integration du produit d'un champ de contraintes par un champ de
gradients de deplacements.

Commentaire :

MODL1 : Objet modele (type MMODEL)

SIG1 : Champ de contraintes (type MCHAML)

GRDEP1 : Champ de gradients de deplacement DEP1 (type MCHAML)

CAR1 : champ de caracteristiques necessaire pour certains
        elements (voir remarque ci-dessous) (type MCHAML,
        sous-type CARACTERISTIQUES)

FORC1 : champ de forces nodales (type CHPOINT)

Remarques :

1 ) Etant donne un champ de contraintes S et un champ de deplacements
    U, l'operateur FOFI calcule le champ de forces nodales dont le
    travail dans un champ de deplacements V soit egal a :

        / k k
        |  ij  dU  dV
        |  S  * --i * --j  dM
        /M dx dx

    Il est l'analogue de l'operateur BSIGMA pour les termes
    quadratiques du tenseur de deformations.

2 ) En analyse de Fourier, le numero de l'harmonique utilise est
    celui defini par la directive OPTION.

3 ) Il faut specifier des caracteristiques, si la description
    geometrique de l'element ne peut se faire par le maillage,
    par exemple l'epaisseur d'elements de plaques ou les inerties
    d'elements de poutres.

## FONC [Mathematiques Fonctions]
 Operateur FONC

   LREEL1 = FONC | 'FRESNEL' | 'CX' | LREEL2 ;
        |  | 'SX' |

 Objet :

 L'operateur FONC permet le calcul des integrales de Fresnel
 par la methode de Lanczos :
 separation de l'espace d'integration en deux domaines (x<4 et x>4)

 Commentaire :

'CX' : integrale en cosinus
        / x
        F = 1/sqrt(2.PI) / cos(t)/sqrt(t) dt
        / 0

'SX' : integrale en sinus
        / x
        F = 1/sqrt(2.PI) / sin(t)/sqrt(t) dt
        / 0

 LREEL2 : les valeurs de la variable (type LISTREEL).

 LREEL1 : les valeurs de la fonction (type LISTREEL).

## FORBLOC [Magnetostatique Magnetostatique] (proc)
Procedure FORBLOC

CHP2 CHP3 = FORBLOC GEO1 CHP1 FLOT1 ( LOG1 )

Objet :
En magnetostatique 2d potentiel vecteur permet de calculer des
forces sur un inducteur par une integrale de surface J * B

Commentaire :

GEO1 maillage
CHP1 potentiel defini au moins sur GEO1
FLOT1 densite de courant sur GEO1
LOG1 optionnel Logique valant VRAI si pb axisymetrique
        (pb plan par defaut )

En sortie :

CHP2 = champoint de forces aux noeuds ( FX FY ) ( en
       axisymetrique on les appelle quand meme FX et FY )
resultats par unite de longueur pour pb plans et par radian
pour pb axisymetrique
CHP3 champoint de la resultante au barycentre de GEO1

## FORC [Mecanique Limites]
    Operateur FORCE
    --------------- OPTI

    FORC1 = FORCE  |  VEC1  |  GEO1 ;
        |  MOTi VALi ... |

    Objet :

    L'operateur FORCE construit un champ de forces resultant de l'appli-
cation d'une force ponctuelle.

    Commentaire :

    La force peut etre definie :

    - soit par un vecteur
    - soit par les valeurs de composantes

     VEC1 : vecteur (type POINT) dont les composantes sont les valeurs
        de la force selon les axes de coordonnees.

     MOTi : nom des composantes (type MOT)

     VALi : valeurs des composantes (type FLOTTANT) de nom MOTi

     GEO1 : lieu geometrique sur lequel la force est appliquee
        (type POINT ou MAILLAGE)

    Remarque :

    On doit specifier VEC1 avant GEO1.

    Les noms de forces possibles sont :

      pour un calcul en mode PLAN CONT : FX FY
      pour un calcul en mode PLAN DEFO : FX FY
      pour un calcul en mode PLAN GENE : FX FY FZ(*)
      pour un calcul en mode AXIS : FR FZ
      pour un calcul en mode FOUR : FR FZ FT
      pour un calcul en mode TRID : FX FY FZ

    (*) uniquement au point support des inconnues supplementaires

    La force VEC1 est repartie sur les differents points de GEO1.

    Exemple :

    Si GEO1 contient 50 points, la force appliquee sur chaque
point est 1/50 de VEC1 (ou 1/50 de VALi).

## FORM [Mecanique Resolution]
    Foncteur FORME

    (CONF2) (CAR2) = FORME (CONF1) (CHPO1) (MOD1 CAR1) ;

    Objet :

    Le foncteur FORME manipule les objets de type CONFIGURATION (champs
de discretisation). Il a un double role de directive et d'operateur.

    Commentaire :

    En tant que directive, FORME actualise le champs de coordonnees
d'apres la CONFIGURATION CONF1 (ou par defaut les coordonnees courantes)
eventuellement mise a jour a l'aide du champ de deplacements CHPO1
(type CHPOINT).

    En tant qu'operateur, FORME cree la CONFIGURATION CONF2 contenant
le champ de coordonnees actualise par le foncteur et actualise le champ de
coordonnees d'apres la nouvelle CONFIGURATION CONF2.

    On peut de plus reactualiser certaines caracteristiques, a savoir les
vecteurs definissant les reperes locaux pour les elements POUTRE, TUYAU,
JOI1 avec repere LIE (option de MODE), TUYAU FISSURE, LINESPRING.
Pour ces deux derniers, on se limite a l'hypothese des petites rotations.

    Dans ce cas, il faut donner le champ de caracteristiques CAR1
(type MCHAML, sous-type CARACTERISTIQUES) ainsi que la modele de calcul
MOD1 (type MMODEL)qui sera reactualise en CAR2.
La donnee du CHPOINT CHPO1 est alors obligatoire.

    Exemple :

    DEP = RESOU RITOT FORCE ; --> calcul du champ de deplacements
    FORME DEP ; --> actualisation du champ de coordonnees
    TRAC GEO1 ; --> trace de la structure deformee

    Si GEO1 est la structure non deformee du probleme en cours,
l'operateur TRAC donnera le trace de la structure deformee sans
amplification.

    Une alternatice est:

    CONF1 = FORM ; --> stocke dans CONF1 la configuration initiale
    CONF2 = FORM DEP1 ; --> cree CONF2 qui est desormais active
    TRAC GEO1 ; --> trace de la structure deformee
    FORM CONF1 ; --> retour a la configuration initiale

## FORNOD [Mecanique Dynamique] (proc)
    procedure FORNOD

La procedure FORNOD est appelee par la procedure DECONV.

## FOR_CONT [Magnetostatique Magnetostatique] (proc)
   Procedure FOR_CONT

     CHPO2 CHPO3 = FOR_CONT GEO1 CHPO1 FLOT1 ;

   Objet :

   En magnetostatique 2d potentiel vecteur calcul de forces
   sur un inducteur par une integrale de contour

   Commentaire :

   GEO1 maillage
   CHPO1 potentiel vecteur sur au moins GEO1
   FLOT1 densite de courant sur GEO1

   en sortie :

   CHPO2 resultante des forces sur le bloc
        par unite de longueur en plan
        par radian en axisymetrique (attention a la
signification pour les forces radiales)
   CHPO3 moment par rapport a l'origine

## FOUR2TRI [Maillage Volumes] (proc)
Procedure FOUR2TRI:
      FOUR2TRI TAB1 (NUMFOUR);

Objet :

     FOUR2TRI genere un maillage 3D a partir d'un modele ou d'un
     maillage 2D Fourier.
     Si des champs (deplacements, forces ou scalaire) 2D Fourier sont
     fournis, alors les champs 3D correspondant sont crees sur le
     maillage 3D.
     La table TAB1 peut etre reutilisees pour des appels successifs
     a FOUR2TRI. Les infos utiles (maillages, etc.) sont conservees.
     Ceci permet par exemple de recombiner les champs definis sur
     plusieurs harmoniques de Fourier.

Entree :

     NUMFOUR : (ENTIER) Numero d'harmonique de Fourier sur lequel
        sont definis les champs 2D a recombiner en 3D.

     TAB1 : (TABLE) avec les indices suivants :

       . 'MODELE' : (MMODEL) modele 2D Fourier
     ou
       . 'MAILLAGE' : (MAILLAGE) maillage 2D

       . 'ANGLES' : (LISTREEL facultatif) discretisation angulaire du
        maillage 3D (= prog 0. 15. 360. par defaut)

       . 'REDRESSE' : (LOGIQUE facultatif) changement de repere pour
        aligner z et Z (FAUX par defaut) tel que :
        = | FAUX --> (r,\theta,z)_{2D} = (X,-Z,Y)_{3D}
        | VRAI --> (r,\theta,z)_{2D} = (X,Y,Z)_{3D}

       . 'ELIM' : (FLOTTANT facultatif) tolerance pour l'appel aux
        operateurs ELIM, MASQ et IPOL (=1.E-12 par defaut)

       . |'DEPLACEMENTS' | : (TABLE facultative) indicee par i=1..n
        |'EFFORTS'  |
        |'CHPO_SYME'  |
        |'CHPO_ANTI'  |
        . i : (CHPOINT) champ 2D Fourier a reconstruire

Sortie:
     Les indices ajoutes a TAB1 sont :

       . 'MAILLAGE_3D' : (MAILLAGE) maillage 3D obtenu par rotation
        (via ROTA ou VOLU 'ROTA')

       . 'ANGLE_3D' : (CHPOINT) angle \theta sur le maillage 3D

       . 'COORDONNEES_2D' : (CHPOINT) coordonnees (r,z) du maillage 2D

       . 'COORDONNEES_3D' : (CHPOINT) coordonnees (r,z) du maillage 3D

       . |'DEPLACEMENTS_3D' | : (TABLE) indicee par i=1..n
        |'EFFORTS_3D'  |
        |'CHPO_SYME_3D'  |
        |'CHPO_ANTI_3D'  |
        . i : (CHPOINT) champ 3D reconstruit

## FPA [Multi-physique Multi-physique]
    Operateur FPA

   SYNTAXE (EQEX) : (voir l'operateur EQEX)

 'ZONE' $PAROI 'OPER' 'FPA' NU YP UET NORM AK ROG RAP 'INCO' 'CN'

   OBJET :

Calcule le depot d'aerosols en regime turbulent, transitoire simultane
sur l'ecoulement et les particules.

   COMMENTAIRES :

$PAROI ligne (2D) ou surface (3D) de depot TABLE sous type DOMAINE

NU viscosite du gaz (m2/s) FLOTTANT

YP epaisseur de la couche limite gaz (m) FLOTTANT

UET vitesse de frottement du gaz (m/s) CHPOINT SCAL CENTRE PAROI

NORM normale sortante a la paroi (m) CHPOINT VECT CENTRE PAROI

AK vitesse de depot des particules (m/s) CHPOINT SCAL CENTRE PAROI

ROG masse volum. part. x gravite (kg/m2s2) POINT

RAP rayon des particules (m) FLOTTANT

CN concentration des particules (-) CHPOINT SCAL SOMMET DOMTO

Remarques :

- Ne pas oublier d'initialiser le champoint AK, qui est ici une sortie
- UET est calcule par FPU (fonctions de paroi pour la vitesse)
- NORM est calcule par DOMA sur tout le domaine, puis reduit sur la
  paroi par KCHT
- YP est a priori le meme que pour FPU, meme si on peut le choisir
  different.
- l'operateur FPA realise la condition aux limites pour une equation de
  concentration (oper. TSCA).

## FPAL [Fluides Resolution] (proc)
     Operateur FPAL
     -------------- ECHI

     AK = FPAL NU ROF UET NOR ROG RAP $PAROI ;

     OBJET :

    Fonctions de Paroi Aerosols : Calcule la vitesse de depot d'aerosols
    en regime laminaire

     COMMENTAIRES :

AK vitesse de depot des particules (m/s) CHPOINT SCAL CENTRE PAROI

NU viscosite du gaz (m2/s) FLOTTANT

ROF masse volumique du gaz (kg/m3) FLOTTANT

UET vitesse de frottement du gaz (m/s) CHPOINT SCAL CENTRE PAROI

NOR champ des normales aux faces (m) CHPOINT VECT FACE DOMTOT

ROG masse volum. part. x gravite (kg/m2s2) POINT

RAP rayon des particules (m) FLOTTANT

$PAROI objet modele associe a la ligne de MMODEL TYPE 'NAVIER_STOKES'
        depot (en 2D)

     Remarques :

- UET est calcule par KUET (en regime laminaire)
- NOR est calcule par DOMA sur tout le domaine (option 'NORMALE')
- AK est un coefficient d'echange pour la masse, il est ensuite
  donne a l'operateur ECHI qui realisera la condition limite de depot
  pour l'equation de concentration (oper. TSCA).
- operateur non teste en 3D.

## FPT [Thermique Resolution]
    Operateur FPT

    Syntaxe (EQEX) : Cf Operateur EQEX

       'ZONE' $DOM 'OPER' FPT RO MU CP LB UET YP H TETA 'INCO' TN

      ( FPT utilise les operateurs : )
      ( KFPT : calcul de H )
      ( ECHIMP : calcul des fonctions de paroi )
      ( sur la temperature )

    DOMAINE D'APPLICATION : Thermo-hydraulique turbulente.

     OBJET :

    Fonction de paroi standard associee au modele K-epsilon pour
    la temperature (TN)

     UTILISATION :

    La vitesse de frottement UET , le coefficient d'echange H , ainsi que
    la temperature de paroi TETA doivent etre initialisees avant execution .
    Ces trois chpoint reposent sur le meme support geometrique .
    Choisir de preference une valeur d'epaisseur de couche limite YP
    telle que sa valeur adimentionnee Y+ soit comprise entre 30 et 300 lors
    des calculs.

     TABLEAUX AUTORISES :

 $DOM Modele NAVIER_STOKES

 RO Densite FLOTTANT ou CHPOINT SCAL SPG

 MU Viscosite dynamique moleculaire FLOTTANT ou CHPOINT SCAL SPG

 CP Chaleur specifique FLOTTANT ou CHPOINT SCAL SPG

 LB Conductivite thermique FLOTTANT ou CHPOINT SCAL SPG

 UET Vitesse de frottement CHPOINT SCAL SPG

 YP Distance la paroi FLOTTANT

 H Coefficient d'echange thermique CHPOINT SCAL SPG

 TETA Temperature a la paroi FLOTTANT ou CHPOINT SCAL SPG

 TN Champ de Temperature CHPOINT SCAL SOMMET

IMPORTANT:

Suivant la formulation EF ou EFM1 SPG doit etre SOMMET ou CENTRE

## FPU [Mecanique Resolution]
    Operateur FPU

    Syntaxe (EQEX) : Cf Operateur EQEX

1ere syntaxe

    Formulation EFM1 :

       'OPER' 'FPU' NU UET YP 'INCO' 'UN' 'KN' 'EN'

2eme syntaxe

    Formulation EF :

       'OPER' 'FPU' RO UN MU UET YP 'INCO' 'UN' <'KN' 'EN'>

3eme syntaxe

    Formulation EF :

       'OPER' 'FPU' RO UN MU UET $mt NUEFF 'INCO' 'UN'

    Objet :

I/ 1ere syntaxe - Formulation EFM1

    Discretise une condition de tension a la paroi suivant un modele de
    fonction de paroi (modele de longueur de melange de Van Driest [1])
    La solution U+ de l'equation est tabulee pour Y+ = 1 a 100. Loi Log
    standard au dela.
    Pour l'equation de QDM la condition est une condition de Neumann
    sur la frontiere maillee du domaine. La fonction de paroi modelise
    une partie de l'ecoulement du fluide (zone d'epaisseur Yp) qui se
    fait en dehors du domaine maille. Il convient d'en tenir compte
    lorsqu'on fait des bilans.

    Les conditions limites correspondantes sur K et Epsilon sont
    calculees si presence des inconnues 'KN' et 'EN'.

    les valeurs de K et Epsilon sont imposees comme des conditions de
    Dirichlet.
    Dans le cas EFM1 les inconnues K et Epsilon sont obligatoires.

II/ 2eme syntaxe - Formulation EF

    Les fonctionnalites de cette option different sur deux points de la
    precedente. La fonction de paroi est implicitee (methode iterative)
    et la loi U+ = F(Y+) est donnee par la loi Reichardt valable jusqu'a
    Y+ = 0. Pour le reste cette option est identique a la precedente.
    Les conditions limites correspondantes sur K et Epsilon sont
    calculees si presence des inconnues 'KN' et 'EN'. La loi de paroi est
    exterieure au domaine maille.

III/ 3eme syntaxe - Formulation EF

    Les fonctionnalites de cette option different sur deux points de la
    precedente. La fonction de paroi est integree a la premiere rangee
    d'element du maillage. La valeur de Yp (distance a la frontiere) est
    calculee automatiquement. La condition limite sur la QDM est une
    condition d'adherence (u=v=w=0). C'est FPU qui l'impose. La viscosite
    effective est modifiee sur la premiere rangee d'elements pour assurer
    la continuite de la contrainte avec le reste de l'ecoulement.
    Pour l'instant les valeurs de K et Epsilon ne sont pas calculees.
    Pour le reste cette option est identique a la precedente.

[1] On Turbulent Flow Near a Wall. R.H. Van Driest.
    Journal of the Aeronautical Sciences (Nov 1956)

    Commentaires :

I/ 1ere syntaxe - Formulation EFM1 -

 NU Viscosite cinematique moleculaire (m**2/s) FLOTTANT
 YP distance a la paroi (m) FLOTTANT
        Cette distance doit etre telle que le premier point du maillage
        se situe dans la couche limite. Un Y+ compris entre 30 et 300
        est l'ideal. (Verification a posteriori par l'utilisateur)
 UET Vitesse de frottement (m/s):
        en formulation EFM1 CHPOINT SCAL CENTRE
        MOT
 UN Champ de vitesse (m/s) CHPOINT VECT SOMMET
<KN> Energie turbulente CHPOINT SCAL SOMMET
<EN> Taux de dissipation de K CHPOINT SCAL SOMMET

    La vitesse de frottement UET, doit etre initialisee en formulation
    EFM1 a une valeur physiquement admissible sous peine de divergence
    de la solution. On peut s'aider de la formule ci-dessous.
    Choisir de preference une valeur d'epaisseur de couche limite YP
    telle que sa valeur adimentionnee Y+ soit comprise entre 30 et 300
    lors des calculs. (Y+=YP*UET/NU)

II/ 2eme syntaxe - Formulation EF

 RO Densite (Kg/m**3) FLOTTANT
        CHPOINT SCAL SOMMET
        MOT
 UN Champ de vitesse (m/s) CHPOINT VECT SOMMET
        MOT
 MU Viscosite dynamique moleculaire (Kg/m/s) FLOTTANT
        CHPOINT SCAL SOMMET
        MOT
 UET Vitesse de frottement (m/s):
        en formulation EF CHPOINT SCAL SOMMET
        MOT
 YP distance a la paroi (m) FLOTTANT

<KN> Energie turbulente CHPOINT SCAL SOMMET
<EN> Taux de dissipation de K CHPOINT SCAL SOMMET

III/ 3eme syntaxe - Formulation EF (Fonction de paroi integree au maillage)

 RO Densite (Kg/m**3) FLOTTANT
        CHPOINT SCAL SOMMET
        MOT
 UN Champ de vitesse (m/s) CHPOINT VECT SOMMET
        MOT
 MU Viscosite dynamique moleculaire (Kg/m/s) FLOTTANT
        CHPOINT SCAL SOMMET
        MOT
 UET Vitesse de frottement (m/s):
        en formulation EF CHPOINT SCAL SOMMET
        MOT
 $MD Modele Navier-Stokes de la frontiere MMODEL
 NUEFF Viscosite effective qui sera modifiee CHPOINT SCAL SOMMET
        par l'operateur. MOT
[… notice tronquée ; texte complet dans l'archive PCW_24]

## FRCTRACE [Poteau et poutre en Beton arme] (proc)
    procedure FRCTRACE

   VAL1 = FRCTRACE TAB1;

Objet :

    Procedure pour tracer les surfaces limites et les enveloppes des
    elements de type portique (frame) en beton armé (POUT et TIMO)

Commentaire :
    Cette procedure est appellée par la procedure de calcul des marges
    pour les elements frame (TIMO et POUT) - voir MRCFRAME

En entree :

En sortie :

Remarques :

## FREN [Mathematiques Autres]
Operateur FRENET

CHPO1 = FREN LIG1 ;

Objet :

L'operateur FRENET construit le repere de Frenet d'un maillage LIG1 de SEG2
ou de SEG3.

Commentaire :

LIG1 : courbe dont on veut le repere de Frenet (type MAILLAGE)

CHPO1 : repere de Frenet (type CHPOINT), la tangente etant definie par les
composantes TX, TY (et TZ en 3D), la normale par les composantes NX, NY
(et NZ en 3D) et la binormale par les composantes BX, BY (et BZ en 3D)

Remarque : la courbe LIG1 peut ne pas etre connexe, cependant chacune de ses
composantes connexe doit etre convenablement orientee.

Remarque : dans le cas d'une courbe ouverte, la tangente est determinee a
chaque extremite par la direction du segment correspondant. En 3D, on
determine alors la binormale a partir de celle calculee au point adjacent
par orthonormalisation, et la normale s'en deduit. Le repere est par
consequent moins bon aux extremites.

## FREPART [Mecanique Limites] (proc)
Procedure FREPART

CH1 = FREPART FO1 LI1 ;

  Objet:

Cette procedure permet d'imposer une force repartie sur
une ligne ouverte

En entree:

FO1 Force a repartir (POINT)
LI1 Ligne sur laquelle se reparti la force (MAILLAGE)

En sortie:

CH1 Champ des forces calculees (CHPOINT)

## FREQPERI [Mathematiques Traitement] (proc)
Procedure FREQPERI

EVOL1_P=FREQPERI EVOL2_F;

objet:

effectue la transformation d'un signal en frequence EVOL2_F
(comportant N courbes) en un signal en periode EVOL1_P
(comportant N courbes), et vice-versa.

## FRIG [Mecanique Modele]
  Operateur FRIG

RIG1 = FRIG RIG2 MODEL1 CHD1 ;

  Objet :

  Cet operateur n'est plus utilise.

## FRON [Thermique Resolution]
    Operateur FRON

   CHT2 = FRON CHT1 CHCARA T1 DT ;

    Objet :

  L'operateur FRON permet de suivre l'avancee d'un front sur une
structure lorsque ce dernier se propage dans toutes les direction a
une vitesse connue (composante 'VIT' de CHCARA). La combustion est
caracterisee par un temps de combustion (composante 'TCMB' de CHPCARA).
  Il faut specifier un champ par point donnant les instants de passage
du front en chaque point (composante 'TPS' ) estime au temps T1.
L'operateur calcule alors le temps de passage du front au temps T1+DT
lorsque le point n'a pas enocre brule au temps T1, il garde la valeur
de CHT1 dans le cas contraire.

  CHT2: champ par point de composante 'TPS'
  CHT1: champ par point de composante 'TPS' au temps t1
  CHCARA: champ par point de composantes
        'VIT'pour la vitesse de combustion
        'TCMB' pour le temps de combustion.
  T1 : instant ou ont ete estimees les valeurs de CHT1
  DT : taille du pas de temps. CHT2 est estime au temps T2=T1+DT.

## FRONABS [Mecanique Dynamique] (proc)
   Procedure FRONABS

   RIG1 = FRONABS TAB1 ( TYP_FRON ) NHARM

Objet :

La procedure FRONABS permet de fabriquer des frontieres absorbantes
de type LYSMER ou de type WHITE utilisees dans les calculs de
l'interaction sol-structure. Ces frontieres composees d'amortisseurs
visqueux ont pour but d'eviter au maximum la reflexion des ondes
sur la bordure du maillage de sol :

    - La frontiere de type LYSMER absorbe totalement l'energie des
      ondes planes a incidence normale. Elle est utilisee dans la
      deconvolution du mouvement sismique du sol ;

    - La frontiere de type WHITE donne une efficacite optimale
      d'absorption d'energie lorsqu'au meme instant plusieurs ondes
      arrivent avec des angles d'incidence differents.

Commentaire :

En entree :

 TAB1 : TABLE contenant les indices suivants en toute lettre

'FRONTIERE' : support geometrique de la frontiere, compose d'elements
        de type SEG3 horizontal ou vertical en 2D :
        PLANDEFO, AXIS, FOUR 0,1

'MASSE_VOLUMIQUE' : masse volumique du sol.
'POISSON' : coefficient de Poisson du sol.
'YOUNG' : module d'Young du sol.

 TYP_FRON : MOT indiquant le type de frontiere utilisee :
        'LYSMER' (par defaut) ou 'WHITE'.

 NHARM : ENTIER numero du mode FOURIER

En sortie :

RIG1 : Objet de type 'RIGIDITE' et de sous-type 'AMORTISSEMNT'
       contenant la matrice d'amortissement de la frontiere absorbante

Remarque :

        La procedure ne traite pas les frontieres obliques ni les
        modeles tridimensionels.

## FROT [Fluides Resolution]
   Operateur FROT

   SYNTAXE ( EQEX ) : Cf operateur EQEX

    'OPER' 'FROT' CK CB <V0> 'INCO' 'UN'

   OBJET :

  Discretise l'operateur de perte de charge sur l'equation de quantite
de mouvement en 2D et 3D

   Commentaires

   Le tenseur de perte de charge doit etre diagonal et donne dans le
repere global.
        bx
        | Kx  0  0  || (u - u0)  |
        |  ||  by |
        | 0  Ky  0  || (v - v0)  |
        |  ||  bz |
        | 0  0  Kz || (w - w0)  |

   CK coefficients de perte de charge
        VECTEUR ou CHPOINT VECT CENTRE ou MOT

   CB exposant
        VECTEUR ou CHPOINT VECT CENTRE ou MOT

   V0 vitesse relative (par defaut V0=0. 0. 0.)
        VECTEUR ou CHPOINT VECT CENTRE ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice MOT.

   Options : (EQEX)

Formulation EFM1 OPTION EFM1 Option par defaut
Option explicite OPTION EXPL Option par defaut
Option implicite OPTION IMPL
Dans ce dernier cas il peut etre necessaire de remettre le champ de
vitesse a divergence nulle.

## FSUR [Mecanique Limites]
    Operateur FSUR

  CHPO1 = FSUR | 'MASS' MODL1  |  VEC1  GEO1  |  (CAR1) ;
        |  |  CHPO2  |
        |
        | 'COQU' MODL1  |  VEC1  |  (CAR1) ;
        |  |  CHPO2  |
        |
        | 'POUT' MODL1  |  VEC1  |  ('PROJ' VEC2) ;
        |  CHPO2  |

    Objet :

    L'operateur FSUR calcule les forces nodales equivalentes a une
densite de force surfacique appliquee sur un objet.

      Commentaire :

      MASS | : mot-cle obligatoire designant le type d'element sur
      COQU |  lequel la force est appliquee (elements massifs,
      POUT |  coques, poutres)

      MODL1 : objet sur lequel la force est appliquee (type MMODEL)

      VEC1 : vecteur representant la densite surfacique de forces
        dans le cas ou elle est constante (type POINT)

      GEO1 : pour les elements massifs, maillage sur lequel la force
        est appliquee (type MAILLAGE)

      CHPO2 : champ contenant la densite surfacique de forces aux
        noeuds. Dans le cas des poutres il peut contenir
        egalement une densite de moments (type CHPOINT).

      CAR1 : caracteristiques des coques et des massifs :
        (type MCHAML, sous-type CARACTERISTIQUES)
        - pour les coques epaisses, contient les valeurs des
        epaisseurs aux points d'integration
        - pour les massifs en contraintes planes, contient les
        valeurs des epaisseurs aux points d'integration

      PROJ : mot-cle facultatif suivi de :

      VEC2 : qui indique que la densite de forces est definie
        par unite de longueur de la projection de l'element sur
        le plan normal au vecteur VEC2 (type POINT).

      CHPO1 : forces nodales equivalentes resultantes (type CHPOINT)

    Remarque : 1. Dans le cas des coques excentrees, l'excentrement
    __________ n'est pas pris en compte

## FTRAN [Mathematiques Autres] (proc)
 Operateur FTRAN

EV3 = FTRAN EV1 EV2 F0 VAL1;

 Objet :

 La procedure FTRAN calcule la fonction de transfert entre les
 evolutions EV1 et EV2

 Commentaire :

 EV1 : premiere evolution (type EVOLUTION)
 EV2 : deuxieme evolution (type EVOLUTION)
 F0 : frequence de coupure (type FLOTTANT)
 VAL1 : nombre de points à effacer aux extremités du
        domaine frequenciel (type ENTIER)
 EV3 : fonction de transfert (module et phase)
        (type EVOLUTION)
        EV3 = TFR(EV1)/TFR(EV2)

## FUIT [Maillage Manipulation]
    Operateur FUIT

     MAIL4 MAIL5 MAIL6 = 'FUIT' MAIL1 MAIL2 MAIL3 ;

    Objet :

    L'operateur FUIT permet de scinder un contour oriente ferme en deux autres
contours orientes fermes et de creer le segment de fuite (type SEG2) qui les
relie. L'element de fuite est le plus petit segment parmi les segments ayant
une extremite dans MAIL2 et l'autre extremite dans MAIL3.

        entrees:

    MAIL1: (objet de type MAILLAGE) contour oriente ferme forme d'elements
        de type SEG2 uniquement.

    MAIL2: (objet de type MAILLAGE) dont un des points sera le support d'une
        des extremite de l'element de fuite.

    MAIL3: (objet de type MAILLAGE) dont un des points sera le support de
        l'autre extremite de l'element de fuite.

       sorties:

    MAIL4: (objet de type MAILLAGE) contenant un element de type SEG2 et qui
        est l'element de fuite. (MAIL4 est aussi contenu dans MAIL5 et son
        inverse dans MAIL6).

    MAIL5: (objet de type MAILLAGE) contenant un des deux contours fermes
        orientes issu de MAIL1.

    MAIL6: (objet de type MAILLAGE) contenant le second contour ferme
        oriente issu de MAIL1.

    Remarque :

     Seuls les points de MAIL2 et MAIL3 qui appartiennent a MAIL1 sont pris
en compte. Sous l'option de calcul AXIS les contours ne sont pas
necessairement fermes. Ils peuvent implicitement etre fermes par symetrie
suivant l'axe (Oz).

## FZERO [Mathematiques Fonctions] (proc)
Procedure FZERO

XSOL = FZERO FONCTION XA XB (XTOL);

Objet :

Cette procedure calcule le zero d'une fonction x->f(x) elle-meme
definie par une procedure.
La methode de Brent est utilisee.

Commentaire :

FONCTION : PROCEDURE definisant la fonction x -> y=f(x) telle que :
        y = FONCTION x;

[XA XB] : intervalle de recherche (FLOTTANTs)

XTOL (facultatif) : precision sur la solution (FLOTTANT)

Exemple :
debp f6 x;
  y = (exp x) - 2. - (1. / ((10.*x)**2)) + (2./((100.*x)**3));
finp y;

x6 = FZERO f6 -4. 2.;
y6 = f6 x6;
* the result is : x6=0.70320 et f6=-2.7E-16 which is correct !

* graphical verification :
x6_p = prog -4. PAS 0.01 2.;
f6_p = f6 x6_p;
ev6 = evol bleu manu 'x' x6_p 'f(x)' f6_p;
dess ev6 'YBOR' -5 5 'YGRA' 1 'AXES';

## F_S2PI [Magnetostatique Magnetostatique] (proc)
 Procedure F_S2PI

  appelee par la procedure DDFOUR

 Objet :
En magnetostatique potentiel vecteur 2d reconstitue par les
symetries appropriees la solution sur 2PI

## GAM1 [Mathematiques Statistiques] (proc)
Procedure GAM1

  CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
 A DISPOSITION DE LA COMMUNAUTE CAST3M
   PAR F. DUPRAT (LMDC - INSA Toulouse)

  Cette procedure est appelee par la procedure NATAF

## GAMM [Mathematiques Fonctions]
  RESU1 = 'GAMM' OBJET1 (MOT1) ;

Operateur GAMM

Objet :

L'operateur GAMM applique la fonction Gamma d'Euler a l'objet OBJET1.

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

## GANE [Mecanique Modele]
Operateur GA(us-)NE(wton)
------------------------- AJUSTE, EXCE

TAB2=GANE TAB1 ('AMOR' FLOT1);

CHPO1 RIGI1=GANE TAB1 'MATR' ('AMOR' FLOT1);

Objet :

L'operateur GANE construit la matrice et le second membre de la
methode de Gauss-Newton ou de Levenberg-Marquardt.

- En donnant le mot clef 'MATR', ces objets sont retournes dans
  CHPO1 (type 'CHPOINT') and RIGI1 (type 'RIGIDITE').

- Sans ce mot clef, le syteme lineaire est resolu et le resultat
  (direction de descente) stocke dans TAB2 (type 'TABLE').

- Le mot clef 'AMOR' permet d'introduire le parametre de viscosite
  nu=FLOT1 (type 'FLOTTANT') de la methode L-M . Par defaut
  nu=0 (methode G-N).

La fonction a minimiser est: 2F(X)={f(X)}.{f(X)}, and [J(X)]=df/dX

La direction de descente est H solution de:
  [[transpose([J])[J]]+[nu*I]]{H} = -{transpose([J]){f}}

Un exemple d'utilisation est donne dans gane.dgibi.

Commentaire :

TAB1 : Table de type 'VECTEUR' contenant
        TAB1 . 0 = f(X)
        TAB1 . 1 = df/dX1
        .
        TAB1 . n = df/dXn

FLOT1 : 'FLOTTANT'=nu

CHPO1 : -{transpose([J]){f}}
RIGI1 : [transpose([J])[J]]

TAB2 : TABLE of type 'VECTEUR' contenant
        TAB2 . 1 = H1
        .
        TAB2 . n = Hn

## GDFLIM1 [Mathematiques Statistiques] (proc)
Procedure GDFLIM1

  CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
 A DISPOSITION DE LA COMMUNAUTE CAST3M
   PAR F. DUPRAT (LMDC - INSA Toulouse)

  Cette procedure est appelee par la procedure HASOFER

## GENE [Maillage Surfaces]
    Operateur GENERATRICE
    --------------------- ROTA SURF

    SURF1 = LIG1 GENERATRICE LIG2 ;

    Objet :

    L'operateur GENERATRICE construit la surface SURF1 (type MAILLAGE)
engendree par la translation de la ligne LIG1 (type MAILLAGE) parallele-
ment a la ligne LIG2 (type MAILLAGE)

## GENJ [Maillage Autres]
    Operateur GENJ

    GEO2 = GENJ GEO1 FLOT1;

    Objet :

    L'operateur GENJ genere le maillage GEO2 (type MAILLAGE) d'elements
de joint succeptible de lier les contours interieurs du maillage GEO1
(type MAILLAGE). FLOT1 (type FLOTTANT) indique la tolerance utilisee pour
determiner la proximite de deux points.

    Remarque :

    En 2D, GENJ genere des elements de type JOI2 a partir de maillage de
TRI3 et/ou QUA4. En 3D, les elements de joints sont des JOI3 et/ou JOI4
generes a partir d'elements de type CUB8, PRI6, PYR5 et/ou TET4

## GIBI [Presentation Presentation]
        Systeme CASTEM2000 - Programme GIBI

 Le programme GIBI est fonde sur le concept d'OBJET. Un objet represente
une structure abstraite de donnees utilisee par les methodes de calcul
scientifique, notamment par element fini.

 La creation d'un objet est effectuee par l'appel a un OPERATEUR tel que
 "DROIT" ou "TRAN".

 Il existe egalement des DIRECTIVES permettant de preciser les options
generales de calcul ou d'effectuer des actions variees. Par exemple la
directive "OPTION" sert a preciser la dimension de l'espace et le type
d'element que l'utilisateur desire fabriquer et la directive "DENSITE"
sert a definir la taille de la maille qui aura pour extremite un point
cree avec cette densite.

 Les objets sont connus par leur nom (comme d'ailleurs les operateurs),
et par leur type.

 Les types d'objet utiles a la creation de maillage sont, outre les mots
et les nombres :
        le POINT ou noeud d'un maillage.
        le MAILLAGE qui represente un maillage ou un sous-maillage
        et qui, sous sa forme la plus generale peut etre defini comme
        un element de P(P(E)).

 Un objet se nomme a l'aide du signe d'affectation : " = ".

 Pour creer l'objet entier de nom "UN" et de valeur 1, on ecrira :

        UN = 1 ;

 L'instruction de base de GIBI est de la forme suivante :

        resultat = operation (liste d'objets)

exemple: ARC = POIN1 CERCLE CENTRE POIN2 ;

        nom de nom du operateur nom du nom de la finit
       l'objet point qui de fabri- point deuxieme toute
       resultat sera la cation d' centre extremite inst-
        premiere un arc de de l'arc ruction
        extremite cercle GIBI

 Une exception a cette regle, l'operation de creation d'un point se
passe d'operateur :
        POINT=10. 0. 0. ;

 Les donnees de GIBI se font en format libre. Chaque instruction, qui
peut tenir au plus sur sept cartes se termine par un point-virgule.

 Les cartes contenant * en premiere colonne sont ignorees et peuvent
donc permettre d'introduire des commentaires dans les donnees.

 Les noms des operateurs et des directives sont caracterises par
leurs quatre premiers caracteres. Les noms des objets et des mots-cles
sont caracterises par leurs huit premiers caracteres.

 Trois types de facilites permettent d'alleger les donnees de GIBI :

 - Le chainage des operations : le resultat d'une operation est pris
        comme premier operande de l'operation suivante.
     exemple:
        RESU = A ET B ET C ET D ;

 - Les parentheses : l'ensemble des parentheses et de leur contenu
        est considere comme l'objet en resultant.
     exemple:
        SURFACE = LIGNE TRANSLATION ( P1 MOINS P2 );

  - La place des objets de types differents intervenant dans une
        instruction est en principe indifferente.
     exemple:
        TRAC OEIL GEOM; GEOM TRAC OEIL; OEIL TRAC GEOM;
     sont la meme operation.

## GMV [Fluides Limites]
 Operateur GMV (Groupe Moto Ventilateur) Voir aussi :

 Objet : Discretise un terme source de quantite de mouvement.
        On impose soit la valeur de ce terme source
        ou alors on calcule ce terme source en fonction des
        caracteristiques du GMV (Courbe debit-pression)
        fourni par l'utilisateur.

 Syntaxe (EQEX) :

        GMV TABGMV INCO 'UN'

 TABGMV : Table contenant les entrees suivantes

'DIR' POINT direction de l'impulsion
'PENTREE' LISTENTI numero des elements (zone GMV)
        pour le calcul de la pression d'entree
'PSORTIE' LISTENTI numero des elements (zone GMV)
        pour le calcul de la pression de sortie
'LDEBIT' MAILLAGE ligne (2D) pour le calcul du debit

<'KIMP'> FLOTTANT impulsion imposee (sa valeur)
<'IMPR'> ENTIER frequence d'impression des informations
        sur le point de fonctionnement du GMV

Si entree 'KIMP' absente

 'GMV' EVOLUTION Courbe pression-debit du GMV
<'OMEGA'> FLOTTANT facteur de relaxation (defaut 0.5)
<'K0'> FLOTTANT Valeur d'initialisation de K
        (cette valeur est reactualisee a chaque
        pas )

Exemple : Voir le jeux de donnees HY2.dtc

## GNFL [Fantome]
Opérateur GNFL

    Cet opérateur est appelé par PASAPAS .

## GRAD [Mathematiques Autres]
Operateur GRAD

  GRAD1 = GRAD MODL1 CHPO1 (CAR1) ;

Objet :

L'operateur GRAD calcule les gradients d'un champ de type CHPOINT.

  Commentaire :

  MODL1 : Objet de type MMODEL contenant une des formulations
        compatibles suivantes :
        - MECANIQUE
        - THERMIQUE
        - DIFFUSION
        - THERMOHYDRIQUE

  CHPO1  : Champ de | deplacement  | (type CHPOINT).
        | temperature  |
        | concentration |

  CAR1 : Champ de caracteristiques geometriques (type MCHAML).

  GRAD1 : champ de gradients (type MCHAML).

## GRAF [Mathematiques Autres]
Operateur GRAF

  GRAF1 = GRAF MODL1 DEP1 ;

Objet :

L'operateur GRAF calcule les gradients de flexion dans les elements
de coque mince .

  Commentaire :

  MODL1 : Objet de type MMODEL.

  DEP1 : Champ de deplacements (type CHPOINT).

  GRAF1 : champ de gradients (type MCHAML).

  Remarque : Les coques ne peuvent pas etre excentrees.

## GREE [Mathematiques Autres]
    Operateur GREEN

    EVOL1 = GREEN STRU1 FLOT1 FLOT2....

       |'BERNOUILLI_EULER'| 'NON_FILTRE' ;
   ... |  | 'FILTRE' FLOT3 FLOT4 ('AMORTISSEMENT' FLOT5)
       |
       | 'TIMOSHENKO' FLOT6 'FILTRE' FLOT3 FLOT4 ('AMORTISSEMENT' FLOT5)

    Objet :

    L'operateur GREEN calcule des fonctions de GREEN associees a des
poutres pour des resolutions de problemes dynamiques par equation
integrale.

    Commentaire :

    STRU1 : objet decrivant la poutre (type STRUCTUR)

    FLOT1 : valeur du temps de calcul demande (type FLOTTANT)

    FLOT2 : pas de temps de calcul (type FLOTTANT)

    FLOT3 : frequence basse de filtrage (type FLOTTANT)

    FLOT4 : frequence haute de filtrage (type FLOTTANT)

    FLOT5 : valeur de l'amortissement (type FLOTTANT)

    FLOT6 : coefficient de forme adimensionnel (type FLOTTANT)

    EVOL1 : objet de type EVOLUTIO, contenant les fonctions de
        Green de traction-compression, torsion, flexion aux
        extremites de la poutre.

## GRESP [Fluides Resolution] (proc)
Procedure GRESP

CHP1 = GRESP MTK1 CHP2 CHP3 TAB1 ;

Objet :

La procedure GRESP resout de maniere approchee un systeme de type
point-selle par une methode de projection algebrique incrementale.

Elle est appelee par la procedure EXEC dans le cadre de la resolution
des equations de Navier-Stokes incompressible en transitoire a la
place de KRES lorsque la methode de projection algebrique incrementale
est demandee (cf. notice EXEC indice 'GPROJ' de la table rv).

Commentaire :

MTK1 : matrice du systeme a resoudre (type MATRIK)

CHP2 : champ des conditions aux limites de Dirichlet (type CHPOINT)

CHP3 : second membre du systeme a resoudre (type CHPOINT)

TAB1 : table argument de EXEC ("rv")

CHP1 : solution approchee du systeme (type CHPOINT)

## GYRO [Mecanique Dynamique]
Operateur GYROSCOPIQUE

Objet :

L'operateur GYROSCOPIQUE calcule la matrice de couplage gyroscopique
utilisee pour l'etude des machines tournantes a l'aide d'elements
finis de poutre

RIG1 = GYRO MODL1 MAT1 ;

Commentaire :

RIG1 : matrice de couplage construite (TYPE rigidite)

MODL1: Modele (objet MMODEL)

MAT1 : Caracteristiques materiau (objet MCHAML)

Les matrices de couplage gyroscopique sont calculees pour les elements
POUTRE, TUYAU et TIMO (modele SECTION inclu) en rotation autour de leur
axe local Ox (repere fixe).
Ce calcul necessite de connaitre la vitesse de rotation de l'arbre
(caracteristique OMEG en rad/s de l'element de poutre).

## G_AUX [Mecanique Rupture] (proc)
  Procedure G_AUX

  CH_AUX = G_AUX SUPTAB BOOL OBJUTI ;

  Objet :

Cette procedure calcule les champs auxiliaires nécessaires à G_THETA
afin de déterminer les facteurs d'intensités des contraintes via l'option
'DECOUPLAGE' (voir procédure G_THETA).

  En entree

  SUPTAB = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres).
        Pour voir quels sont les indices obligatoires, voir
        la notice de la procédure G_THETA.

      BOOL = Objet de type TABLE contenant les booléens utiles aux divers
        tests effectués au cours du déroulement de G_THETA.

      OBJUTI = Objet de type TABLE contenant divers objets utiles au cours
        du calcul. Cette table permet de conserver en mémoire des
        objets créés dans les divers procédures appelées par G_THETA.

  En sortie :

  CH_AUX = Objet de type TABLE contenant les champs auxiliaires nécessaires
        pour calculer les facteurs d'intensité des contraintes.

## G_CALCUL [Mathematiques Fonctions] (proc)
    Procedure G_CALCUL

    Objet :

   Cette procedure est utilisee par la procedure G_THETA. Elle
permet de determiner les differents termes d'une integrale de
contours.

## G_CAS [Mecanique Rupture] (proc)
  Procedure G_CAS

  OBJUTI = G_CAS SUPTAB BOOL ;

  Objet :

Cette procedure analyse la table fournie a la procedure G_THETA, puis
determine et resume le cas que l'utilisateur souhaite traite. Si les
donnees sont incompatibles, ou si le cas n'est pas encore traitable par
la procedure G_THETA, une erreur est renvoyee.
L'information sur le cas de figure est enregistree dans la table BOOL
qui est constituee exclusivement de booleens. Cela facilite les tests
ulterieurs dans G_THETA.

  En entree

  SUPTAB = Objet de type TABLE dont les indices sont des
        objets de type MOT (a ecrire en toutes lettres).
        Pour voir quels sont les indices obligatoires, voir
        la notice de la procedure G_THETA.

      BOOL = Objet de type TABLE contenant les booleens utiles aux divers
        tests effectues au cours du deroulement de G_THETA.

  En sortie :

  OBJUTI = Objet de type TABLE contenant des objets utiles a la procedure
        G_THETA crees pendant l'analyse de SUPTAB.

## G_THETA [Mecanique Rupture] (proc)
    Procedure G_THETA
    ----------------- CH_THETA

    G_THETA SUPTAB ;

        SUPTAB.'BLOCAGES_MECANIQUES' 'LEVRE_INFERIEURE'
        'CALCUL_CRITERE' 'METH_AUX'
        'CARACTERISTIQUES' 'MODELE'
        'CHAMP_THETA' 'MODELES_COMPOSITES'
        'CHARGEMENTS_MECANIQUES' 'NOEUDS_AVANCES'
        'CHPOINT_TRANSFORMATION' 'OBJECTIF'
        'CHPO_RESULTATS' 'OPERATEUR'
        'COUCHE' 'PHI'
        'CRIT_DECHA_GLOBAL1' 'POINT_CENTRE'
        'CRIT_DECHA_GLOBAL2' 'POINT_1'
        'CRIT_DECHA_LOCAL1' 'POINT_2'
        'CRIT_DECHA_LOCAL2' 'POINT_3'
        'DEFORMATIONS_IMPOSEES' 'PRESSION'
        'ELEMENT_MULTICOUCHE' 'PSI'
        'EPAISSEUR_RESULTATS' 'RESULTATS'
        'EVOLUTION_RESULTATS' 'ROTATION_RIGIDIFIANTE'
        'FISSURE_2' 'SOLUTION_PASAPAS'
        'FRONT_FISSURE' 'SOLUTION_RESO'
        'FRONT_FISSURE_2' 'TEMPERATURES'
        'LEVRE_SUPERIEURE'

    Objet :

    Cette procedure a deux objectifs principaux :

    1 ) calculer les integrales suivantes de la mecanique de la rupture :
        1.1) l'integrale J (ou G) d'un materiau isotrope, caracteristique
        en elasto-plastique. Les discontinuites de proprietes ne sont
        pas encore acceptables dans le cas des elements 3D massifs.
        1.2) l'integrale J dynamique d'un materiau isotrope,
        caracteristique en elasto-dynamique. Les discontinuites de
        proprietes ne sont pas encore acceptables dans le cas des
        elements 3D massifs.
        1.3) l'integrale C* d'un materiau isotrope, caracteristique
        dans le cas de fluage secondaire stationnaire. Le chargement
        doit etre mecanique et les dicsontinuites de proprietes ne sont
        pas encore acceptables, ni en 2D ni en 3D.
        1.4) l'integrale C*(h) d'un materiau isotrope, caracteristique
        dans le cas de fluage primaire ou tertiaire sous un chargement
        radial. Le chargement doit etre mecanique et les dicsontinuites
        de proprietes ne sont pas encore acceptables, ni en 2D ni en 3D.
        1.5) l'integrale de derivation dJ/da (a : longueur de la fissure)
        d'un materiau homogene et isotrope, utile pour etudier la
        stabilite de propagation d'une fissure ou des fissures
        interagissantes. Ne sont pas encore acceptables les discontinuites
        de proprietes en 2D ou en 3D et les elements de coque (mince
        ou epaisse).

    2 ) decoupler les modes mixtes d'un solide homogene constitue d'un materiau
        elastique lineaire isotrope, c'est a dire la separation des facteurs
        d'intensite des contraintes K1, K2 (et K3 en 3D).
        Les discontinuites de proprietes en 3D et les elements de coque ne sont
        pas encore acceptables.
        Les proprietes materielles doivent etre des constantes.

CHAP{ENTREES}

    En entree, SUPTAB (objet de type TABLE) sert a definir les options
    et les parametres du calcul. Ses indices sont des objets de type
    MOT (a ecrire en toutes lettres) dont voici la liste :

PART{Arguments obligatoires dans tous les cas}

    SUPTAB.'OBJECTIF'
    = MOT pour preciser le but du calcul, valant :
      1) 'J' pour calculer l'integrale J (ou G), caracteristique
        en elasto-plastique.
      2) 'J_DYNA' pour calculer l'integrale J (ou G), caracteristique
        en elasto-dynamique.
      3) 'C*' pour calculer l'integrale C*, caracteristique
        en fluage secondaire stationnaire.
      4) 'C*H' pour calculer l'integrale C*(h), caracteristique
        en fluage primaire ou tertiaire.
      5) 'DJ/DA' pour calculer l'integrale de la derivation dJ/da,
        caracteristique pour analyser la stabilite de
        propagation d'une fissure ou des fissures
        interagissantes.
      6) 'DECOUPLAGE' pour decouper les modes mixtes, c'est a dire la
        separation des facteurs K1, K2 (et K3 et 3D).

    SUPTAB.'COUCHE'
    = ENTIER representant le nombre de couches d'elements autour du
        front de la fissure qui se deplacent pour simuler la
        propagation de la fissure. Il vaut 0 si seul la pointe de
        la fissure se deplace, 1 si c'est la premiere couche
        d'elements entourant la fissure qui se deplace, 2 si c'est
        l'ensemble des premiere et deuxieme couches d'elements qui
        se deplace, etc.
        Il convient veiller a ce que l'ensemble des elements a deplacer
        n'atteint pas le bord de la structure fissuree.
        Si COUCHE et CHAMP_THETA sont tous deux donnés, CHAMP_THETA
        est écrasé (cf.8.).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## G_ULTI2D [Voile Beton arme] (proc)
    procedure G_ULTI2D

   VAL1 = G_ULTI2D TAB1;

Objet :

    Fonction pour la determination de la position de l'etat de contrainte S
    actuel par rapport à la surface limite pour les trois couches
    (externe, interne et intermediaire) selon le modele de MARTI
    (voir EFFMERTI). La procedure donne en sortie la
    valeur de controle VAL1. Si VAL1<0. S est en dehors du domaine ultime
        VAL1>0. S est à l'intérieur du domaine ultime

Commentaire :
Cette procedure est appellÃ©e par la procedure de calcul des marges pour
les elements 2D (voiles et plaques) - voir MRCSHELL

En entree :

En sortie :

Remarques :

## G_ULTIFR [Voile Beton arme] (proc)
    procedure G_ULTIFR

   VAL1 = G_ULTIFR TAB1;

Objet :

    Fonction pour la determination de la position de l'etat de contrainte S
    actuel par rapport à la surface limite pour les elements frame (TIMO et POUT)

    Valeur de controle VAL1. Si VAL1<0. S est en dehors du domaine ultime
        VAL1>0. S est à l'intérieur du domaine ultime

Commentaire :
Cette procedure est appellÃ©e par la procedure de calcul des marges pour
les elements 2D (voiles et plaques) - voir MRCSHELL

En entree :

En sortie :

Remarques :

## HANN [Mathematiques Traitement]
Operateur HANN

EVOL1 = HANN EVOL2 N1 (COUL1);

objet :

Operateur HANN effectue la moyenne de Hanning du spectre EVOL2
suivant le nombre N1 d'iteration de Hanning (application des
coefficients de Tuckey 1/4,1/2,1/4). Le spectre EVOL1 resultant
a le meme titre que EVOL2 prefixe par 'HANNING(valeur de N1)', et
la meme couleur sauf si celle-ci est indiquee optionellement par
COUL1.

attention:

EVOL1 et (implicitement) EVOL2 ne comportent qu'une seule courbe.

EVOL2 peut etre detruit sans modifier EVOL1.

## HASOFER [Multi-physique Multi-physique] (proc)
Procedure HASOFER

  CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
 A DISPOSITION DE LA COMMUNAUTE CAST3M
   PAR F. DUPRAT (LMDC - INSA Toulouse)

ERR1 = HASOFER TAB1 ;

Objet :

Cette procedure calcule l'indice de fiabilite d'Hasofer-Lind.

Commentaire :

TAB1 : objet de type TABLE

ERR1 : indice d'erreur (type FLOTTANT)

Entree :
    - nombre de variables : tab1.nbre_variables
    - parametres des variables NATAF : tab1.param_va
    - matrice de covariance : tab1.matcov;
    - coefficient de majoration 1 : tab1.major1
    - coefficient de majoration 2 : tab1.major2
    - precision relative du BETA : tab1.prec
    - nombre max d'iterations : tab1.itmax
    - point de depart P0 : tab1.depart
    - parametres du modele mecanique : tab1.parametres

Sortie :
    - point d'arrivee P* : tab1.arrivee
    - indices de fiabilite : tab1.beta
    - nombres d'appels a la FEL : tab1.appels
    - points P*(iter) : tab1.beta_point
    - valeurs de G(iter) : tab1.glim
    - ecarts |UP*i(iter+1)-UP*i(iter)|  : tab1.ecu
    - increments DELTA_X(iter) : tab1.delx
    - indice d'erreur : err1

## HAUBAN [Maillage Lignes] (proc)
    Procedure HAUBAN

    GEO1 MODL1 CHEL1 = HAUBAN P1 P2 ES PL L0 N1 ;

    Objet :

   Cette procedure fournit le maillage d'un cable accroche a ses
extremites et soumis a son poids propre. Il fournit egalement le
modele associe et le champ de tensions dans le cable.

   Commentaire :

   P1, P2 : les points extremites du cable (type POINT)

   ES : rigidite membranaire du cable ( type FLOTTANT)

   PL : poids lineique du cable (type FLOTTANT)

   L0 : longueur a vide du cable (type FLOTTANT)

   N1 : nombre d'elements desire (type ENTIER)

   GEO1 : maillage (type MAILLAGE)

   MODL1 : objet modele (type MMODEL)

   CHEL1 : champ de tensions (type MCHAML)

    Remarque : Le poids du cable est pris selon la direction z
    ________ dans le sens negatif.

## HBM [Mecanique Dynamique] (proc)
Procedure HBM
______________ HBM_POST

  HBM TAB1;

Objet :

HBM (Harmonic Balance Method ou equilibrage harmonique) transforme
le probleme dynamique non-lineaire etabli dans le domaine temporel
sous la forme du systeme d'equations differentielles (1) de taille N
en un systeme d'equations algebriques (2) de taille N*(2H+1)
via la decomposition en serie de Fourier (3) des inconnues du
probleme en vue d'une resolution par la methode de CONTINUation.

    .. . .
  M u(t) + C u(t) + K u(t) = fnl(u,u) + fext(wt) (1)

avec :

  M : matrice de masse
  C : matrice d'amortissement
  K : matrice de raideur
  fnl : forces non-lineaires dans le domaine temporel
  fext : vecteur des forces exterieures dans le domaine temporel
        de frequence w
  u : vecteur inconnue dans le domaine temporel

  Z(w) U - Fnl(U) - Fext = 0 (2)

avec :

  Z(w) = diag(K, Z_1, Z_2, ... Z_H )

  Z_k = [ K - k²w² M w C ]
        [ -wC K - k²w² M ]

  U = ( U_0 U_1 V_1 ... U_H _VH )

tel que :

  u(t) = U_0 + \sum_{k=1..H} cos kwt U_k + sin kwt V_k (3)

Entree :

TABHBM = TABLE

   . 'RIGIDITE_CONSTANTE' = K
   . 'AMORTISSEMENT_CONSTANT' = C
   . 'MASSE_CONSTANTE' = M
   . 'BLOCAGES_MECANIQUES' = Kblocages
   . 'RIGIDITE_CENTRIFUGE'
   . 'CORIOLIS_CONSTANT'
   . 'N_HARMONIQUE' = nombre d'harmoniques H
   . 'RESULTATS' = table des resultats attendus
        . i . 'POINT_MESURE' exprimes sur ddl temporel
        . 'COMPOSANTES'
        . 'COULEUR'
        . 'TITRE'

Sortie :

TABHBM
   . 'RIGIDITE_HBM' = partie de Z relative a K
   . 'AMORTISSEMENT_HBM' = partie de Z relative a C (pour w=1)
   . 'MASSE_HBM' = partie de Z relative a M (pour w=1)
   . 'BLOCAGES_HBM' = partie de Z relative a Kblocages
   . 'CENTRIFUGE_HBM' ...
   . 'CORIOLIS_HBM'

   . 'RESULTATS_HBM' = table des resultats attendus
        . j . 'POINT_MESURE' exprimes sur ddl frequentiels
        . 'COMPOSANTES'
        . 'COULEUR'
        . 'TITRE'
   . 'RESULTATS'
        . i . 'INDICES_HBM' = liste des indices j associe
        au i^eme resultat

   . 'COMPOSANTES'
      . 'DEPLACEMENT' = composantes temporelles de u (max.6)
      . 'FORCE' = composantes temporelles de f (max.6)
      . 'DEPLACEMENT_HBM' = composantes frequentielles de U
      . 'FORCE_HBM' = composantes frequentielles de F
      . 'HARM_DEPLACEMENT' = table des composantes de U
        (par harmonique)
      . 'HARM_FORCE' = table des composantes de F
        (par harmonique)

Correspondance entre inconnues temporelles et frequentielles :
  | domaine  |  domaine frequentiel  |
  | temporel  |  k=0  k=1(cos) k=1(sin)  ...  |
  |  UX  |  U1  U4  V4  ...  |
  |  UY  |  U2  U5  V5  ...  |
  |  UZ  |  U3  U6  V6  ...  |

## HBM_POST [Mecanique Dynamique] (proc)
Procedure HBM
______________ HBM

  HBM_POST TAB1 (LMOT1);

Objet :

Etant donne une table TAB1 decrivant un probleme de vibrations
non-lineaires dans le domaine frequentiel par la methode HBM
("Harmonic Balance Method" ou equilibrage harmonique) ayant ete
resolu par CONTINUation, cette procedure permet le post-traitement
(notamment dans le domaine temporel) des resultats contenus dans
cette table.

LMOT1 (type LISTMOTS) est une liste de mots-cles decrivant la liste
des actions de post-traitement a realiser parmi :

- MAXI : pour le calcul des EVOLUTIONS max|u(t)| en fonction du
        parametre de continuation (pseudo-temps)

- TEMP : pour le calcul de u(t). Stockage a raison de 1 courbe tous
        les N pas (ou N = TAB1 . 'PAS_SAUVES')
        .
- VITE : pour le calcul de u(t). (Analogue a l'option 'TEMP')

Entree :

TABHBM = TABLE

>>> indices presents en sortie de HBM suivi de CONTINU :

   . 'N_HARMONIQUE' = nombre d'harmoniques H
   . 'TEMPS_PROG' = liste des pseudo-temps calcules
   . 'RESULTATS' = table des resultats attendus
        . i . 'COULEUR'
        . 'TITRE'
        . 'INDICES_HBM' = liste des indices j associe
        au i^eme resultat

   . 'RESULTATS_HBM' = table des resultats attendus
        . j . 'RESULTATS' exprimes sur ddl frequentiels

>>> indices a ajouter eventuellement (propre a HBM_POST) :

   . 'N_PT_POST' = nombre de points a utiliser pour la
        discretisation temporelle
        (= 2**7 * H par defaut)

Sortie :

TABHBM
   . 'RESULTATS_EVOL'  =  EVOLUTIONs max|u(t)| en fonction du
        parametre de continuation

   . 'RESULTATS' . i = TABLE du i^eme resultat contenant :

      . 'RESULTATS_TEMPORELS' . l = EVOLUTION u(t/T) obtenue pour
        le l^ieme pseudo-temps de la
        liste TEMPS_PROG
        .
      . 'RESULTATS_TEMPORELS' . -l = EVOLUTION u(t/T) obtenue pour
        le l^ieme pseudo-temps de la
        liste TEMPS_PROG

## HDEB [Multi-physique Multi-physique]
 Operateur HDEB

CHP5 = HDEB MODE1 RIG1 CHP1 CHP2 (RIG2 CHP3) (CHP4);

 Objet :

 L'operateur HDEB cree le champ de debit (flux) a travers chaque
 face, dans le cas d'une formulation elements finis mixte hybride.

 A partir des charges et des traces de charge, dans le cadre de
 la resolution des equations de DARCY.

 A partir de concentrations au centre des elements et des traces
 de concentrations, dans le cadre d'un calcul couple
 transport/geochimie.

 Commentaire :

    MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

    RIG1 : Objet rigidite de sous type DARCY contenant les
        matrices elementaires de darcy inverses pour les
        elements hybrides (cf. MHYB).

    CHP1 : Objet de type CHPOINT contenant les concentrations
        (ou les charges) au centre des elements. Le support
        geometrique de ce champ est le MAILLAGE CENTRE de la
        table domaine. Ce champ peut avoir plusieur composantes.
        (A la suite d'un calcul Transport Geochimie on
        considerera les concentrations des aqueux)
        Dans le cas ou CHP2 a une composante TH, CHP1 doit avoir
        une composante de nom H. Dans les autres cas le nombre
        et les noms des composantes doivent etre identiques a
        ceux de CHP2.

    CHP2 : Objet de type CHPOINT contenant les traces de
        concentrations ou les traces de charges. Le support
        geometrique de ce champ est le MAILLAGE FACE de la
        table domaine. Ce champ doit avoir des composantes dont
        le nombre et les noms sont identiques a celles de CHP1
        ou au moins une composante de nom TH.
        (A la suite d'un calcul Transport Geochimie on
        considerera les concentrations des aqueux au centre
        des faces.)

    RIG2 : Objet rigidite de sous type MASSE contenant les
        matrices masses elementaires pour les elements
        hybrides (cf MHYB).

    CHP3 : Objet de type CHPOINT de composantes FX FY (FZ) contenant
        le vecteur de la force volumique moyenne par element.
        Le support geometrique de ce champ est le MAILLAGE CENTRE
        de la table domaine TAB1. Cet argument est optionnel.
        Il est generalement utile lorsque l'on pose le probleme
        de DARCY en terme de pression et non plus de charge.
        Son utilisation necessite la donnee de l'objet RIG2.

    CHP4 : Objet de type CHPOINT de support geometrique
        le MAILLAGE FACE de la table domaine. Flux de
        la vitesse convective. En presence de cette donnee
        on prendra en compte le flux convectif.

    CHP5 : Objet resultat de type CHPOINT contenant le debit a
        travers chaque face. Le support geometrique de ce
        champ est le MAILLAGE FACE de la table domaine TAB1.
        Dans le cas ou CHP2 a une composante TH, Le nom de la
        composante du CHPOIN est FLUX, dans les autres cas
        les noms des composantes sont ceux de CHP1.
        Si CHP4 est donne, CHP5 est la somme du flux diffusif
        et du flux convectif.

  Remarque : Il n'est pas possible d'intervertir l'ordre de lecture
        des differents CHPOIN.

## HERI [Langage Methodes]
    Operateur HERITE

      OBJET1%HERITE OBJET2;

    Objet :

    La procedure HERITE agit sur OBJET1, objet de type OBJET. Elle
lui fait heriter des methodes de l'objet OBJET2 en s'attribuant les
methodes de cet objet.

## HIST [Post-traitement Analyse]
    Operateur HIST voir aussi : @PASHIST

    |  Syntaxe 1  |

     LENT1 LENT2 = HIST LVAL1 LCLAS1 (LVAL2 LCLAS2 ( ... )) ...
        ... ('CLAS' 'OCCU') ;

    Objet :

     Etant donne :
     - les N evenements definis par les m-uplets {X1 X2 ... Xm}
       fournis sous la forme de m LISTREELS : LVAL1, ... LVALm
     - les classes correspondantes LCLAS1 (de dime N1+1), ...
       LCLASm (de dime Nm+1) de type LISTREEL egalement,
     L'operateur 'HIST' renvoie le LISTENTI correspondant :
     - a la classe de chaque evenement (option 'CLAS') --> LENT1
     - au nombre d'occurences des evenements dans chacune des
       classes (option 'OCCU') --> LENT2
     Par defaut (aucune option), on renvoie les 2 LISTENTI.

    Commentaires :

     On numerote de maniere globale les classes de telle sorte que
     la k^eme classe (numero global) renvoie aux classes k1, k2 ...
     avec : k = k1 + N1*(k2-1) + N1*N2*(k3-1) + ...
     La classe 0 est retournee si l'evenement est hors des limites des
     classes.
     Les valeurs des classes doivent etre fournies dans un ordre
     strictement croissant.

    Exemple :

     Soit la suite de 4 evenements :
       {0.2 4} {0.1 14} {0.5 10} {0.4 1}
     definie par :
       x1 = prog 0.2 0.1 1.1 0.5 0.4 ;
       x2 = prog 4.0 14.0 9.0 10.0 1.0 ;
     et les classes associees :
       y1 = prog 0. 0.5 1. ;
       y2 = prog 0. 5. 10. 15. 20.;

     la numerotation globale des classes est :
        0 0.5 1.0
        0 +-------+-------+----->y1
        |  1  |  2  |
        5 +-------+-------+
        |  3  |  4  |
        10 +-------+-------+
        |  5  |  6  |
        15 +-------+-------+
        |  7  |  8  |
        20 +-------+-------+
        |
        y2 v

     lclass loccu = HIST x1 y1 x2 y2 'CLAS' 'OCCU';
     --> lclass contient la suite de 5 entiers :
        1 5 6 1
     --> loccu contient la suite de 8 entiers :
        2 0 0 0 1 1 0 0

    |  Syntaxe 2  |

    EV1  = 'HIST' (COUL) MOD1 CHAM1 ('ABS') LRE1 | (MOT1)  | ;
        | (LMOT1) |

    Objet :

    L'operateur HIST determine la densite de distribution des valeurs
d'un champ par elements sur son maillage. Le resultat est un objet de
type EVOLUTION, dont les courbes sont de type HISTogramme, ce qui
permet leur trace sous forme d'histogrammes.

    Commentaire :

    COUL : couleur de(s) la courbe(s) en sortie (de type MOT) ;

    MOD1 : modele (de type MMODEL) ;

    CHAM1 : champ par elements (de type MCHAML) ;

    'ABS' : mot-cle indiquant que l'on prend la valeur absolue des
        valeurs de CHAM1 ;

    LRE1 : intervalles d'echantillonnage des valeurs de CHAM1 (de
        type LISTREEL) ;

    MOT1 : nom de la composante de CHAM1 a traiter (de type MOT) ;

    LMOT1 : nom de(s) la composante(s) de CHAM1 a traiter (de type
        LISTMOTS).

## HOMO [Maillage Manipulation]
Operateur HOMOTHETIE

GEO1 = GEO2 HOMO RAPP1 POIN1 ;

Objet :

L'operateur HOMOTHETIE construit un objet par homothetie

Commentaire :

GEO2 : objet initial (type MAILLAGE ou POINT)

RAPP1 : rapport de l'homothetie (type FLOTTANT)

POIN1 : centre de l'homothetie (type POINT)

GEO1 : objet resultat (type MAILLAGE ou POINT)

Remarque :

GEO1 GEO2 ... GEOn HOMO RAPP1 POIN1;

L'operation est effectuee sur les n objets simultanement et a n
resultats. Les n objets doivent être, soit tous de type MAILLAGE,
soit tous de type POINT.

Exemple :
    NC1 NC2 NC3 NC4 NS = C1 C2 C3 C4 S HOMO 0.3 (10 0) ;

## HOOK [Mecanique Modele]
  Operateur HOOKE

    HOO1 = HOOKE MODL1 CAR1 (VAR1) ('REFE') ;

  Objet :

  L'operateur HOOKE construit, a partir du champ de proprietes
  materielles ( et eventuellement, de caracteristiques geome-
  triques ), le champ de matrice de HOOKE.

    Commentaire:

    MODL1 : Objet modele (type MMODEL)

    CAR1 : Champ par element de caracteristiques geometriques et
        materielles (type MCHAML, sous-type CARACTERISTIQUES)

    VAR1 : champ de variables internes (type MCHAML, sous-type
        VARIABLES INTERNES) facultatif

    HOO1 : Champ par element de matrices de Hooke (type MCHAML,
        sous-type MATRICE DE HOOKE)

Remarques :

Dans le cas des materiaux endommageables et visco-endommageables,
et dans le cas ou le champ de variables internes est donne, la
matrice de HOOKE calculee tient compte de l'endommagement. Ceci est
valable pour les modeles suivants :
'PLASTIQUE' 'ENDOMMAGEABLE'
'VISCOPLASTIQUE' 'VISCODOMMAGE'
'ENDOMMAGEMENT' 'MAZARS'
'ENDOMMAGEMENT' 'MVM'
'PLASTIQUE_ENDOM' 'ROUSSELIER'
'PLASTIQUE_ENDOM' 'GURSON2'
'FLUAGE' 'CERAMIQUE'

CAR1 n'est necessaire que pour des types d'element dont la geometrie
complete ne peut pas etre deduite du maillage, comme par exemple, les
elements poutres, tuyaux, coques.

Pour les elements de type coque mince excentres, on peut indiquer
le mot 'REFE' pour obtenir les matrices de Hooke associees a des
grandeurs (efforts et deformations) definies au niveau de la surface
de reference. Sinon, les matrices correspondent a des grandeurs
definies au niveau de la surface excentree.

Dans le cas de l'element DST orthotrope HOO1 contient egalement les
cosinus-directeurs des axes d'orthotropie par rapport au repere
local de l'element.

## HOTA [Mecanique Modele]
    Operateur HOTANGE

      CHEL1 = HOTANGE MODL1 SIG1 VAR1 MAT1 ( 'PREC' FLOT1 )

    Objet :

    L'operateur HOTANGE calcule la matrice de Hooke tangente, pour
des etats de contraintes et de variables internes donnes.

      Commentaire :

      MODL1 : objet modele (type MMODEL)

      SIG1 : champ de contraintes (type MCHAML, sous-type CONTRAINTES)

      VAR1 : champ de variables internes (type MCHAML, sous-type
        VARIABLES INTERNES)

      MAT1 : champ de proprietes materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

      'PREC': mot cle indiquant que l'on donne la precision

      FLOT1 : precision avec laquelle on cherche si un etat de
        contraintes est plastique ou non (1.E-3 par defaut).

      'DT ': mot cle indiquant que l'on donne le pas de temps

      FLOT2 : pas de temps servant a calculer la matrice tangente.
        Cette donnee n'est necessaire que pour les modeles
        visqueux

      CHEL1 : champ de matrices de HOOKE (type MCHAML, sous-type
        MATRICE DE HOOKE)

      Il est necessaire de respecter l'ordre ci dessus pour les
      CHAML arguments.

## HP_PRO [Post-traitement Analyse]
  Procedure HP_PRO

  CHPO1 = HP_PRO CHPO2 ;

  Objet :

  Cette procedure effectue le calcul de la pression (chpo1)
a partir de la charge e (chpo2)

## HRAYO [Thermique Modele] (proc)
    Procedure HRAYO

 CHAM1 = HRAYO MCV MODL1 MATE1 T1 (MODL2)(MATE2) T2 (GEO1) (FLOT1);

    Objet :

    Calcule un coefficient d'echange linearise pour le traitement
des echanges par rayonnement avec un milieu infini ou face a face
entre deux frontieres.

    Commentaire :

    MCV : modele de convection (type MMODEL)

    MODL1 : modele de rayonnement defini sur la frontiere 1.
        (type MMODEL)

    MATE1 : champ d'emissivite defini sur la frontiere 1
        (type MCHAML)

    T1 : temperature definie sur la frontiere 1
        (type CHPOINT)

    MODL2 : modele de rayonnement defini sur la frontiere 2.

    MATE2 : champ d'emissivite defini sur la frontiere 2
        (type MCHAML)

    T2 : temperature definie sur la frontiere 2
        (type CHPOINT)

    GEO1 : geometrie definissant les relations entre les supports
        des champs T1 et T2
        (type MAILLAGE)

    FLOT1 : constante de Stefan-Boltzmann (par defaut 5.67e-8 Wm-2K-4)
        (type FLOTTANT)

    CHAM1 : coefficient d'echange linearise
        (type MCHAML)

    Remarques :

 Dans le cas du rayonnement face a face, le modele MCV est defini
 sur un objet maillage cree a partir des deux frontieres supposees
 homologues au moyen des operateurs RACC ou LIAI. La frontiere 1
 correspond au premier argument de ces operateurs et la frontiere
 2 au second.

 Dans le cas du rayonnement avec un milieu infini, les objets
 MODL2 MATE2 ne sont pas utilises. L'objet T2 est defini sur la
 frontiere 1 et correspond aux caractéristiques du milieu infini.

## HRCAV [Multi-physique Multi-physique] (proc)
    Procedure HRCAV

 CHAM1 = HRCAV MRT EMIS TE TRAD (FLOT1) ;

    Objet :

    Calcule un coefficient d'echange linearise pour le traitement
du rayonnement en milieu transparent dans une cavite.

    Commentaire :

    MRT : modele de rayonnement (type MMODEL)

    EMIS : champ d'emissivite defini le modele de rayonnement
        (type MCHAML)

    TE : temperature definie sur la cavite
        (type MCHAML)

    TRAD : temperature resultat de l'operateur RAYE, fonction
        des facteurs de forme, du champ d'emissivite, et
        du champ de temperature TE correspondant a une
        iteration donnee (champ precedent)
        (type MCHAML)

    FLOT1 : constante de Stefan-Boltzmann (par defaut 5.67e-8 Wm-2K-4)
        (type FLOTTANT)

    CHAM1 : coefficient d'echange (type MCHAML)

## HTCTRAN [Thermique Resolution] (proc)
    Procedure HTCTRAN

    HTCTRAN NPAS NSAUV NITER DT MOD1 TAB1 ;

    Objet :

  Cette procedure permet d'effectuer un calcul de transferts
  thermiques et hydriques dans un bloc de beton bidimensionnel ou
  axisymetrique ou tridimensionnel, soumis a des gradients de
  temperature.

   Commentaire :

 NPAS : nombre de pas a calculer (type ENTIER)

 NSAUV : nombre definissant la frequence de sauvegarde des resultats
        dans la table TAB1 (type ENTIER)

 NITER : nombre d'iterations a chaque pas (type ENTIER)

 DT : valeur du pas de temps en secondes (type FLOTTANT)

 MOD1 : modele thermique (type MMODEL)

 TAB1 : table utilisee en entree et en sortie (type TABLE)

En entree, TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :

 TEMPERATURE_INITIALE : temperature initiale en degres Celsius
        (type FLOTTANT)

 PRESSION_INITIALE : pression initiale en MPa. Elle est aussi
        utilisee pour determiner la teneur en eau
        initiale (type FLOTTANT)

 (LAMBDA) : constante utilisee dans la methode
        d'integration temporelle (0.55 par defaut)

 (GAMMA) : constante utilisee pour l'estimation de la
        temperature et de la pression au debut
        du pas (1. par defaut)

 (EPSILON) : constante pour le calcul de derivees
        (1.E-8 par defaut)

 (ERPM) : valeur de la precision pour la pression
        (1.E-4 par defaut)

 (ERTM) : valeur de la precision pour la temperature
        (1.E-4 par defaut)

 (C) : teneur en ciment initiale en Kg/m3
        (300. par defaut) (type FLOTTANT)

 (F_STE) : coefficient stochiometrique
        (0.24 par defaut) (type FLOTTANT)

 (F_INV) : coefficient d'avancement de l'hydratation
        (0.95 par defaut) (type FLOTTANT)

 (W1) : teneur en eau a saturation du beton a 25°C
        en Kg/m3 (100. par defaut) (type FLOTTANT)

 (A0) : coefficient de permeabilite initiale en m/s
        (1.E-13 par defaut ) (type FLOTTANT)

 (DEN_SEC) : densite du beton sec en Kg/m3
        (2400. par defaut) (type FLOTTANT)

 (CCP_SEC) : chaleur massique du beton sec en J/kg/C
        (880. par defaut) (type FLOTTANT)

 (K0_SEC) : premier coefficient intervenant dans le calcul de
        la conductivite thermique du beton sec en W/(m°C)
        (1.92 par defaut ) (type FLOTTANT)

 (K1_SEC) : second coefficient intervenant dans le calcul de
        la conductivite thermique du beton sec en W/(m°CxC)
        (-0.00125 par defaut ) (type FLOTTANT)

 (EWD) : evolution de l'eau chimiquement liee
        relachee avec la temperature en Kg/m3
        (McGill par defaut) (type EVOLUTION)

 (CAD) : chaleur de dessication du beton en J/Kg
        (0.2328E6 par defaut) (type FLOTTANT)

 (ALFA) : coefficient de dilatation thermique lineique
        du beton en /°C (9.E-6 par defaut)

 (E0) : module de Young du beton a 25°C en MPa
        (35000. par defaut) (type FLOTTANT)

 (EE0T) : evolution de E(T)/E0 avec la temperature
        (module de Young normalise du beton)
        (DTU P 92 701 par defaut) (type EVOLUTION)

 (NU) : coefficient de Poisson du beton (0.18 par defaut)
        (type FLOTTANT)

 (FLG) : indice de niveau d'impressions de controle, de 0 a 5
        (0 par defaut) (type ENTIER)

 FRONTIERES_PRESSION : table contenant les informations relatives
        aux frontieres echangeant de la vapeur
        (type TABLE)
        Elle contient des tables (indicees par les
        nombres entiers consecutifs : 1, 2, ...)
        correspondant chacune a une frontiere
        echangeant de la vapeur.
        Chacune de ces tables contient les objets
        suivants :

        'MAILLAGE' : maillage de la frontiere
        (type MAILLAGE)

        'CODIRXR' : cosinus directeur de la normale
        exterieure a la frontiere, par rapport a
        l'axe x ou r (type FLOTTANT ou CHPOINT)

        'CODIRYZ' : cosinus directeur de la normale
        exterieure a la frontiere, par rapport a
        l'axe y ou z (type FLOTTANT ou CHPOINT)

        'CODIRZZ' : dans le cas tridimensionnel,
        cosinus directeur de la normale
        exterieure a la frontiere, par rapport a
        l'axe z (type FLOTTANT ou CHPOINT)

 CONDUCTIVITE_THERMIQUE : matrice de conductivite liee a la convection
        thermique et aux blocages thermiques (type RIGIDITE).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## HTC_CHBW [Fluides Resolution] (proc)
procedure HTC_CHBW

  Cette procedure est appelee par les procedures HTCTRAN
  pour le calcul de l'eau liee.

## HTC_PER [Fluides Resolution] (proc)
procedure HTC_PER

  Cette procedure est appelee par la procedure HTCTRAN
  pour le calcul de le cefficient de permeabilite.

## HTC_WTR [Fluides Resolution] (proc)
procedure HTC_WTR

  Cette procedure est appelee par les procedures HTCTRAN
  et HTC_WWW pour le calcul de les proprietees de l'eau.

## HTC_WWW [Multi-physique Multi-physique] (proc)
procedure HTC_WWW

  Cette procedure est appelee par la procedure HTCTRAN
  pour le calcul de la teneur en eau du beton.

## HT_PRO [Multi-physique Multi-physique] (proc)
Procedure HT_PRO

CHPO2 CHPO3 CHPO4 = HT_PRO TAB1 (CHPO1) ;

Objet :

Cette procedure calcule la saturation, la teneur en eau et la
capacite en fonction de la pression d'eau P.
Cette procedure est utilisee a partir de la procedure DARCYSAT
Elle correspond a une loi definie par le soustype de TAB1 :
- VAN_GENUCHTEN
   Saturation reduite dans [0,1] : S = [1 + (-beta.Pw)**n]**(-m)
- EXPONENTIELLE
   S = C / ([exp(-beta.Pw)]**N + C - 1)
- LOGARITHMIQUE
   (-beta.Pw) tronque a 1 quand inferieur a 1.
   S = C / ([ln(-beta.Pw)]**N + C)

avec S = (TH2O - teta_r) / (poros - teta_r)

Commentaires :

TAB1 : table contenant les caracteristiques physiques, ayant
        pour indices
        BHETA, NEXP, MEXP : coefficients de la loi VAN_GENUCHTEN
        (attention a l'unite de beta)
        BHETA, COEF_N, COEF_C : coef pour la loi log ou exp.
        PORO : porosite (s. d.), poros
        (FLOTTANT ou CHAMP-POINT centre,
        comp 'SCAL')
        TERESIDU : teneur en eau residuelle (s. d.), teta_r
        (FLOTTANT ou CHAMP-POINT centre,
        comp 'SCAL')

CHPO1 : Pression d'eau (negative en non sature)
        seulement pour les lois exponentielle et logarithme.

CHPO2 : saturation reduite, S
        (CHAMP-POINT support de Pw)

CHPO3 : teneur en eau, TH2O
        (CHAMP-POINT support de Pw)

CHPO4 : capacite calculee analytiquement
        (CHAMP-POINT support de Pw)

Remarque :
 Si le champ CHPO1 est absent, on teste les arguments de la procedure
 et on ne fait pas de calculs.

## HVIT [Multi-physique Multi-physique]
    Operateur HVIT

    CHP2 = HVIT MODE1 CHP1 ;

    Objet :

    L'operateur HVIT cree le champ de vitesse au centre de chaque
elements. Ce champ est calcule a partir des debits aux faces dans
le cadre de la resolution des equations de DARCY par une methode
d'elements finis mixtes hybrides.

    Commentaire :

       MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

       CHP1 : Objet de type CHPOINT contenant le debit a travers
        chaque face. Le support geometrique de ce champ est
        le maillage centre des FACEs . Le nom de
        la composante du CHPOINT est FLUX (cf. HDEB).

       CHP2 : Objet resultat de type CHPOINT contenant la vitesse au
        centre de chaque element. Le support geometrique de ce
        champ est le MAILLAGE CENTRE des elements.
        Les noms des composantes du CHPOINT sont VX et VY.

## HYBP [Multi-physique Multi-physique]
    Operateur HYBP

    CHP4 = HYBP MODE1 RIG1 CHP1 (TAB2) (CHP2) (RIG2 CHP3) ;

    Objet :

    L'operateur HYBP cree le champ de charge a partir des traces
de charge dans le cadre de la resolution des equations de DARCY
par une methode d'elements finis mixtes hybrides.

    Commentaire :

       MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf MODE).

       RIG1 : Objet rigidite de sous type DARCY contenant les
        matrices de darcy elementaires inverses pour les elements
        hybrides (cf MHYB).

       CHP1 : Objet CHPOINT solution du systeme matriciel en trace
        de charge. Le support geometrique de ce champ est
        le MAILLAGE FACE de la table domaine TAB1. Le CHPOINT
        doit avoir au moins une composante de nom TH.

       TAB2 : Objet table de sous type DARCY_TRANSITOIRE contenant
        les conditions initiales et les coefficients pour le
        schema d'integration en temps dans le cas transitoire
        (cf procedure DARCYTRA).
        !! En cas de resolution transitoire les forces volumiques
        (arguments RIG2 et CHP3) ne sont pas encore disponibles !!

       CHP2 : Objet de type CHPOINT contenant l'integrale du terme
        source en chaque element. Le support geometrique de
        ce champ est le MAILLAGE CENTRE de la table domaine
        TAB1. Le nom de la composante du CHPOINT est SOUR.
        Cet argument est optionnel. Il n'a pas de raison
        d'etre si la source est nulle.

       RIG2 : Objet rigidite de sous type MASSE contenant les
        matrices masses elementaires pour les elements
        hybrides (cf MHYB).

       CHP3 : Objet de type CHPOINT de composantes FX FY (FZ) contenant
        le vecteur de la force volumique moyenne par element.
        Le support geometrique de ce champ est le MAILLAGE CENTRE
        de la table domaine TAB1. Cet argument est optionnel.
        Il est generalement utile lorsque l'on pose le probleme
        de DARCY en terme de pression et non plus de charge.
        Son utilisation necessite la donnee de l'objet RIG2.

       CHP4 : Objet resultat de type CHPOINT contenant la charge
        moyenne par element. Le support geometrique de ce
        champ est le MAILLAGE CENTRE la table domaine TAB1.
        Le nom de la composante du CHPOINT est H.

## H_B [Magnetostatique Magnetostatique] (proc)
 Procedure H_B

     EV1 = H_B FLOT1 (EVO1) (FLOT2) ;

 Objet :

En magnetostatique 2D potentiel vecteur ou 3D potentiel scalaire
rend la courbe mu(h) ou 1/(mu(b) suivant que l'on est en
potentiel scalaire (3D) ou en potentiel vecteur (2D)

Commentaire :

FLOT1 permeabilite du vide dans unite coherente
EVO1 evolution courbe b(h) du materiau H en abscisse et
        B en ordonee
        si absent une courbe standard est fournie.
FLOT2 facteur de compacite 1. par defaut.

En sortie :

EV1 evolution ,dependance de mu par rapport a H ou B

## IDBHT [Multi-physique Multi-physique] (proc)
 Procedure IDBHT

 Objet :

Cette procedure est utilisee par la procedure NONLIN
pour le beton a haute temperature.

## IDENTI [Mecanique Modele] (proc)
   Procedure IDENTI

        Y1 Y2 ... Yn = IDENTI NOMMOD X1 X2 ... Xm ;

   Objet :

   La procedure IDENTI permet une aide a l'identification de certains modeles
   de comportement.

   Commentaire :

   NOMMOD : Nom du modele ( type MOT )  |  MAZARS
        |  ...
        |

   X1 .. Xm : valeurs permettant l'identification des parametres

   Y1 .. Yn : parametres identifies

    a) Cas du modele MAZARS :

m= 7
   X1 : MODULE D"ELASTICITE INITIAL
   X2 : COEFFICIANT DE POISSON
   X3 : CONTRAINTE LIMITE EN TRACTION
   X4 : CONTRAINTE RESIDUELLE EN TRACTION
   X5 : INDICE DE FRAGILITE COMPRIS ENTRE 0 ET 1
   X6 : CONTRAINTE LIMITE EN COMPRESSION
   X7 : LA DEFORMATION CORRESPONDANT A CETTE LIMITE

n=5
   Y1 : PARAMETRE KTR0
   Y2 : ATRA
   Y3 : BTRA
   Y4 : ACOM
   Y5 : BCOM

   b) Cas du modele de MAXWELL

si identification de la courbe de fluage de l'EUROCODE 2 ( courbe par defaut)
m = 8
 X1 UNITE = unite de calcul (seconde, jour, annee)
 X2 TMAX = duree maximale du calcul
 X3 NB = nombre de branches visqueuses du modele de Maxwell
        (la branche elastique porte le numero 0)
 X4 EUROCODE
 X5 RM = rayon moyen de la piece en metres
 X6 ROH = pourcentage d'humidite (0. < roh < 100.)
 X7 S = coefficient relatif a la nature du ciment
 X8 FCM = resistance moyenne en compression [MPa]

si identification de la courbe de fluage du BPEL
m = 7
 X1 UNITE = unite de calcul (seconde, jour, annee)
 X2 TMAX = duree maximale du calcul
 X3 NB = nombre de branches visqueuses du modele de Maxwell
        (la branche elastique porte le numero 0)
 X4 BPEL
 X5 RM = rayon moyen de la piece en metres
 X6 ROH = pourcentage d'humidite (0. < roh < 100.)
 X7 FC28 = resistance moyenne en compression a 28 jours [MPa]

n=3
   Y1 : evolution contenant le module d'Young du materiau en Pa
        en fonction du temps en jours
   Y2 : table contenant les modules de chaque branche du modele
        en Pa en fonction du temps en jours
   Y3 : table contenant les temps de relaxation de chaque
        branche du modele, en jours
remarques : verifier en sortie que les courbes d'evolutions
donnees dans Y2 ne varient pas trop. Sinon risque de problemes
numeriques

si identification de la courbe de fluage LCPC
m = 7
 X1 UNITE = unite de calcul (seconde, jour, annee)
 X2 TMAX = duree maximale du calcul
 X3 NB = nombre de branches visqueuses du modele de Maxwell
        (la branche elastique porte le numero 0)
 X4 LCPC
 X5 RM = rayon moyen de la piece en metres
 X6 RHOS= taux d'armatures passives dans une section de beton arme
        (0. < RHOS < 1.)
 X7 E1AN = Module d'Young mesure en laboratoire a 1 an d'age [MPa]

n=3
   Y1 : evolution contenant le module d'Young du materiau en Pa
        en fonction du temps en jours
   Y2 : table contenant les modules de chaque branche du modele
        en Pa en fonction du temps en jours
   Y3 : table contenant les temps de relaxation de chaque
        branche du modele, en jours

   c) Cas du modele de GLRC_DM

m = 12
   X1 : module d'élasticité du béton
   X2 : coefficient de Poisson du béton
   X3 : module d'élasticité de l'acier
   X4 : coefficient de Poisson de l'acier
   X5 : l'épaisseur de la coque
   X6 : la section totale d'acier par mètre linéaire
   X7 : la position relative d'une nappe dans l'épaisseur
   X8 : la résistance en traction du béton
   X9 : l'effort limite de compression du béton par mètre linéaire
   X10 : le paramètre GAMMA_T tel que 0 < GAMMA_T < 1
   X11 : le paramètre GAMMA_F tel que 0 < GAMMA_F < 1
   X12 : favorise t-on le cisaillement ? 1 si oui, 0 sinon

n = 7
   Y1 : module d'Young équivalent en partie membrane
   Y2 : coefficient de Poisson équivalent en partie membrane
   Y3 : module d'Young équivalent en partie flexion
   Y4 : coefficient de Poisson équivalent en partie flexion
   Y5 : seuil initial dans la surface seuil d'endommagement
   Y6 : paramètre d'évolution de l'endommagement GAMMA_C
   Y7 : paramètre de couplage membrane/flexion ALPHA

      * References :
     [1] B. Richard, N. Ile. (2012). Influence de la fissuration du béton
        sur les mouvements transférés - phase 2 : implantation dans Cast3M
        d'un modèle simplifié de béton armé et validation sur les éléme
        de structures. Rapport technique CEA RT12-011/A.

## IDLI [Mathematiques Autres]
Operateur IDLI

  TAB1 = IDLI RIG1 GEO1 ;

Objet :

L'operateur IDLI etablit la table TAB1 (type TABLE) de
sous-type LIAISONS_STATIQUES.
Les entrees de cette table sont des tables (type TABLE)
donnant chacune
- un POINT_LIAISON (type POINT) appartenant
a l'intersection du maillage support de RIG1
(type RIGIDITE) et de GEO1 (type MAILLAGE)
- un DDL_LIAISON (type MOT) indiquant le degre de liberte
associe dans RIG1

  Commentaire :

  A partir de relations donnees, IDLI facilite la mise en
  place d'une analyse par sous-structuration
  (voir BLOQ, RESOU, DEPI, dyna14.dgibi)

## IFRE [Mathematiques Traitement]
Operateur IFRE

FLOT1 FLOT2 = IFRE FLOT3 ;

Objet :

L'operateur IFRE calcule les integrales de FRESNEL :

        / FLOT3
        FLOT1 = 1/sqrt(2.PI) / cos(T)/sqrt(T) dT
        / 0

        / FLOT3
        FLOT2 = 1/sqrt(2.PI) / sin(T)/sqrt(T) dT
        / 0

Commentaire :

FLOTi : objets de type FLOTTANT.
        FLOT3 est exprime en RADIAN.

## IJET [—]
Operateur IJET

   CHDIST MINTER CHFN CHDEP = IJET CHOLD CHNEW TOL TAB1 ;

Objet :

L'operateur IJET calcule, par une methode analytique exacte,
l'intersection entre des segments et les facettes triangulaires d'un
maillage.

Il fournit les distances de connection ainsi que le maillage forme
des points d'intersection.
Il calcule egalement le flux normalise et les champs de deplacement.
Cet operateur remplace la procedure @INTSEC.

Commentaire :

 en entree :

 CHOLD : coordonnees des points extremites initiales des segments
        (type CHPOINT a 3 composantes)

 CHNEW : coordonnees des points extremites finales des segments
        (type CHPOINT a 3 composantes appuye sur le meme support
        que CHOLD)

 TOL : tolerance (type FLOTTANT)

 TAB1 : table qui doit contenir les parametres suivants en entree

        tab1.<chamx1 |
        tab1.<chamy1 |
        tab1.<chamz1 |
        |
        tab1.<chamx2 |
        tab1.<chamy2 |---> Cf @rmcoor
        tab1.<chamz2 |
        |
        tab1.<chamx3 |
        tab1.<chamy3 |
        tab1.<chamz3 |
        |
        tab1.<chamf1 |
        tab1.<chamf2 |---> Cf @rmflun
        tab1.<chamf3 |
        |
        tab1.<cosx  |
        tab1.<cosy  |---> Cf @rmnorm
        tab1.<cosz  |

 en sortie :

 CHDIST : distance de connexion (distance entre point initial du
        segment et le point d'intersection a la facette) ou valeur du
        pas si au cas ou il n'y a pas d'intersection (type CHPOINT).
        Il s'appuie sur le maillage support de CHOLD.

 MINTER : maillage forme des noeuds du maillage support de
        CHOLD intersectes (type MAILLAGE).

 CHFN : flux normalise si intersection, sinon 0 (type CHPOINT).
        Il s'appuie sur le maillage support de CHOLD.

 CHDEP : champ de deplacement des points interceptes (type CHPOINT).

 Remarques :

 CHOLD, CHNEW, CHDIST et CHFN sont des chpoints definis sur un
 maillage reduit qui est forme des noeuds de OMBRE qui n'ont pas encore
 ete interceptes.

 Le maillage cree MINTER est compose d'elements de type POI1.

 Cet operateur remplace la procedure @INTSEC.

## IMAGES [Post-traitement Affichage] (proc)
    Procedure IMAGES

    IMAGES TAB1;

        TAB1.'TABLECAST'.'MAILLAGE'.'TYPE'.'LISTEMP'
        .'SIGCOMP'.'DEFO_SUPP'.'TITRE'
        .'OEIL'.'COULEUR'.'AMPLD'

    Objet :

     D'apres une idee originale de l'ISPRA, cette procedure permet
d'obtenir lors d'un calcul pas a pas :
      - les deformees a differents instants de calculs
        supperposees ou non avec la structure non deformee
      - le champ de contraintes sur la deformee a differents
        instants de calculs
      - le champ de temperatures sur la structure non deformee
        dans le cas d'un calcul thermique pur et a differents
        instants de calculs.
      - le champ de temperatures sur la structure deformee dans
        le cas d'un calcul couple thermique/mecanique a differents
        instants de calculs .

   Commentaire :

  En entree, TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :

  TABLECAST : table sortie de PASAPAS

  MAILLAGE : une partie du maillage total (maillage total par defaut)

  TYPE : type de trace que l'on desire obtenir
        = DDEFORMEE pour obtenir le trace des deformees
        = DCONTRAINTES pour obtenir le trace du champ de contraintes
        sur la deformee
        = DTEMPERATURES pour obtenir le trace du champ de temperatures
        sur la deformee dans le cas d'un calcul couple thermique/
        mecanique, sur la structure non deformee dans le cas d'un
        calcul thermique pur

  LISTEMP : numeros des temps de calculs que l'on desire visualiser
        (type LISTREEL) (cree par l'operateur PROG)

  SIGCOMP : pour le trace du champ de contraintes, type de contraintes
        que l'on desire visualiser sur la deformee
        = SIGVMIS pour visualiser les contraintes de VON MISES
        = nom de la composante du champ de contraintes

  DEFO_SUPP : pour le trace des deformees
        = VRAI si l'on desire supperposer la deformee avec la structure
        non deformee
        = FAUX si l'on desire uniquement la deformee

  TITRE : titre du dessin

  OEIL : oeil pour un trace 3D

  COULEUR : couleur de la deformee (rouge par defaut)

  AMPLD : amplitude de la deformee (donnee facultative)

En sortie on obtient un postscript.

    Remarques :

  Pour une presentation plus claire il est preferable de se limiter
a 6 dessins par page.

## IMPCHI1 [Entree-Sortie Entree-Sortie] (proc)
Procedure IMPCHI1

    IMPCHI1 TAB1 NOM1 ;

     Objet
    Cette procedure permet d'imprimer le contenu d'une table de
    sous type CHIMI1. ( issue de l'operateur CHI1)

    Commentaires
    TAB1 est une TABLE de type CHIMI1

    NOM1 est un mot, le nom de TAB1

## IMPCHI2 [Entree-Sortie Entree-Sortie] (proc)
Procedure IMPCHI2

    IMPCHI2 TAB1 NOM1 ;

     Objet
    Cette procedure permet d'imprimer le contenu d'une table de
    sous type CHIMI2. ( issue de l'operateur CHI2)

    Commentaires
    TAB1 est une TABLE de type CHIMI2

    NOM1 est un mot, le nom de TAB1.

## IMPE [Mecanique Modele]
     Operateur IMPE :

      RIG1 = IMPE RIG2 (RIG3) (REEL1) (| 'MASSE'  | )  (FLAM);
        | 'RAIDEUR'  |
        | 'AMORTISSEMENT'  |
        | 'QUELCONQUE'  LISREEL1  |

Objet:

  L'operateur IMPEDANCE calcule les matrices d impedance
  de sous-type MASSE, RAIDEUR, ou AMORTISSEMENT

  INPUT :

  RIG2: Matrice de rigidite initiale dont les inconnues primales et
        duales sont dans le domaine temporel (UX, UY, ..., FX, FY, ...)

  REEL1: REEL donnant la pulsation (en rad/s) pour laquelle est calculee
        l impedance (valeur par defaut: 1)

  FLAM: LOGIQUE (FAUX par defaut) specifiant si la matrice doit etre de
        sous type MASSE (necessaire si la matrice est utilise pour
        un calcul de flambage)

  'MASSE', 'RAIDEUR', 'AMORTISSEMENT', 'QUELCONQUE': Mot cle specifiant
  le type de matrice d impedance a creer

  L'option 'QUELCONQUE' necessite une LISREEL1 comprenant 4 reels:
  LISREEL1 = PROG REELA REELB REELC REELD;

  Il est également possible de fournir 2 matrices en entree afin de
  coupler les ddls de meme nom entre ces 2 matrices.
  C'est par exemple le cas lorsqu'on cherche à coupler les déplacements
  symetriques et antisymétriques lors d'un calcul en mode de Fourier
  (cas des machines tournantes par ex.) avec :
  - RIG2 qui est la matrice calculee avec les ddls symetriques
    (c'est a dire apres l'instruction OPTION MODE FOUR nhar)
  - RIG3 qui est la matrice calculee avec les ddls antisymetriques
    (c'est a dire apres l'instruction OPTION MODE FOUR (-1*nhar))

  Seule l'option RAIDEUR est permise lorsqu'une matrice comprenant
  des relations (i.e. faisant intervenir des multiplicateurs de Lagrange
  LX ) est fournie en entree.

  OUTPUT :

  RIG1: Objet RIGIDITE représentant la matrice d impedance
        (de meme sous type que la RIG2 ou de sous-type MASSE si le
        mot-clé 'FLAM' est précisé)

  La matrice RIG1 est creee par duplication de la matrice RIG1 sur
  les degres de liberte imaginaires (IUX, IUY, ..., IFX, IFY, ...)
  selon les règles suivantes :

  Cas 'RAIDEUR': [ RIG2 0 ]
        [ 0 RIG2 ]

  Cas 'MASSE': [ -REEL1^2*RIG2 0 ]
        [ 0 -REEL1^2*RIG2 ]

  Cas 'AMORTISSEMENT': [ 0 -REEL1*RIG2 ]
        [ REEL1*RIG2 0 ]

  Cas 'QUELCONQUE': [ REELA*RIG2 REELB*RIG2 ]
        [ REELC*RIG2 REELD*RIG2 ]

  Dans le cas ou deux matrices sont fournies en entrée, RIG1 vaut :

  Cas 'RAIDEUR': [ RIG2 0 ]
        [ 0 RIG3 ]

  Cas 'MASSE': [ -REEL1^2*RIG2 0 ]
        [ 0 -REEL1^2*RIG3 ]

  Cas 'AMORTISSEMENT': [ 0 -REEL1*RIG2bar ]
        [ REEL1*RIG3bar 0 ]

  avec RIG2bar_{ij} = | - RIG2_{ij}  si j refere au ddl UT
        |  RIG2_{ij}  pour tous les autres ddls.

## IMPF [Maillage Autres]
Operateur IMPF

  GEO1 = IMPF GEO2 ;

Objet :

Cet operateur n'est plus utilise.

## IMPO [Maillage Autres]
    Operateur IMPOSE
    ---------------- EXTR MODE

Syntaxe 1 :
    MAIL1  = 'IMPO' 'IMPA' 'MAIT'  LI1  'ESCL' | LI2 | ;

    Objet :

      LI1 , LI2 : maillages des frontieres en vis a vis qui definissent
        en 2D les lignes de contact.

      P1 : point (POI1) representatif du projectile indeformable.

      MAIL1 : objet maillage resultant contenant des elements de type 22.

    L'option 'IMPA' 'MAIT' 'ESCL' donne l'ensemble des liens possibles
    entre les points au cours d'un impact entre deux lignes ou
    entre une ligne et un projectile rigide supporte par un point.
    Ces liens ne seront pas forcement realises mais ils sont representes
    au sein d'un objet de type 'MAILLAGE' contenant les points physiques
    lies (3 dans le cas d'un contact ligne-ligne, 2 dans le cas d'un contact
    ligne-point) et les deux points supports des deux multiplicateurs de
    Lagrange. On suppose que LI1 est maitre et que LI2 ou P1 sont esclaves.

Syntaxe 2 :
    RIG1 = 'IMPO' 'IMPA' MAIL1 ...
        ... (|  'VECT' VECT1  |
        | 'HEMI' FLOT1  'VECT' VECT1  |
        | 'PLAT' FLOT2  'VECT' VECT1  |
        | 'CONE' FLOT3 'ANGL' FLOT4 'VECT' VECT1 |) ;

    Objet :

      MAIL1 : objet maillage resultant contenant des elements de type 22

      FLOT1 : rayon du projectile hemispherique (P1 est sur la sphere
        sur l'axe du cone)

      FLOT2 : largeur du projectile plat (P1 est sur la surface
        au centre du carre)

      FLOT3 : largeur du projectile conique (P1 est sur la pointe
        du cone)

      FLOT4 : angle du projectile conique (par raaport a l'axe de rotation)

      VECT1 : objet de type vecteur definissant l'axe du projectile.

      RIG1 : objet rigidite contenant les matrices des relations d'egalite.

    L'option 'IMPA' seule permet de construire l'objet de type 'RIGIDITE'
    contenant la matrice des relations de non penetration entre les noeuds
    pour lesquels on detecte un contact sur la configuration actuelle.
    Dans le cas d'un projectile rigide de type POI1 on peut definir trois
    formes : 'HEMI' (hemispherique), 'PLAT' ou 'CONE' (conique). La
    definition d'un vecteur indiquant la direction du point materiel est
    indispensable.

    Les coefficients de la matrices sont relatifs a la configuration actuelle.
    Ils correspondent a une linearisation des equations de non penetration.

## INCL [Maillage Manipulation]
    Operateur INCLUSION

    GEO1 = 'INCLUS' GEO2 GEO3 ('VOLU') | ('STRI') | ('NOID') (FLOT1) ;
        | ('LARG') |
        | ('BARY') |

    Objet :

    Deux cas sont a considerer.

    1) 2D ou 3D surfaces planes :

    L'operateur INCLUS extrait de l'objet GEO2 (type MAILLAGE)
l'ensemble des elements se trouvant entierement a l'interieur du contour
de l'objet GEO3 en 2D ou 3D surfaces planes (type MAILLAGE). Si le mot
option 'BARY' est utilise, un element est considere a l'interieur du
contour si son barycentre est a l'interieur de ce contour. SI le mot
'STRI'ctement est utilise les points se trouvant sur la frontiere sont
consideres comme etant a l'exterieur. Si le mot 'LARG'ement est fourni
(option par defaut), ils sont consideres comme etant a l'interieur.

    2) 3D volumique (mot-clef 'VOLU' a placer en premier):

    L'operateur INCLUS extrait de l'objet GEO2 (type MAILLAGE)
l'ensemble des elements se trouvant a l'interieur du volume forme par
les elements volumiques de GEO3. Dans le cas du mot option 'BARY', un
element est considere a l'interieur du volume si son barycentre est
lui-meme a l'interieur de ce volume. Si le mot 'STRI' est utilise il
faut que tous les noeuds de l'element soient a l'interieur du volume et,
si le mot 'LARG' est utilise, il suffit qu'un des noeuds de l'element
soit a l'interieur du volume forme par GEO3. Par defaut c'est l'option
'STRI' qui est active.

    L'objet resultat GEO1 est de type MAILLAGE.

    L'operateur genere une erreur si l'inclusion est vide, sauf en
presence du mot-clef 'NOID', auquel cas GEO1 est un maillage vide.

    FLOT1 (type FLOTTANT) n'est utilise qu'en 3D. Il permet de verifier
l'inclusion a un critere de precision pres. Suivant le signe de FLOT1,
on peut rattraper des points legerement a l'exterieur de GEO3 (FLOT1>0)
ou ne conserver que les points strictement a l'interieur (FLOT1<0).
Par defaut, FLOT1 est egal 1.E-2.

## INDE [Langage Base]
Operateur INDEX

TAB1 = INDEX TAB2 ;
TAB1 = INDEX MOT1 ;

Objet :

La première syntaxe de l'operateur INDEX permet d'obtenir l'ensemble
des indices d'une table. La table resultat TAB1 sera indicée de 1 à
n (n étant le nombre d'indices de la table TAB2).

La deuxième syntaxe de l'operateur INDEX permet d'obtenir l'ensemble
des objets nommés d'un type particulier. La table résultat TAB1 sera
indicée par les noms des objets nommés du type demandé.

Commentaire :

TAB2 : table dont on veut connaitre les indices (type TABLE)
MOT1 : objet de type MOT à choisir dans la liste suivante :
        *LOGIQUE ; *ENTIER ; *FLOTTANT ; *MOT ; *MAILLAGE
        *POINT ; *LISTENTI ; *LISTREEL ; *LISTMOTS ; *LISTCHPO
        *EVOLUTIO ; *RIGIDITE ; *TEXTE ; *DEFORME ; *CHARGEME
        *VECTEUR ; *TABLE ; *PROCEDUR ; *CHPOINT ; *MCHAML
        *MMODEL ; *NUAGE ; *MATRIK
TAB1 : objet resultat (type TABLE)

## INDI [Maillage Manipulation]
 Operateur INDI

 |  1ere possibilite  |

 CHAM1 = INDI GEO1 NOMi ... ;

 Objet :

 L'operateur INDI fournit des indicateurs permettant d'apprecier
 la qualite d'un maillage.
 Les criteres testes sont specifies par des mots-cles.
 L'operateur cree un champ par elements (type MCHAML) dont les
 composantes sont ces criteres.

 Commentaires :

 GEO1 : objet maillage (type MELEME)

 NOMi : mot-cle (type mot). Les valeurs possibles sont :

'PLAN' : Critere de planearite pour les elements a 4 noeuds.
        La valeur calculee est directement proportionnelle a
        l'angle entre les normales N1 et N2 definies par :

        - N1 = produit vectoriel (S1 S2,S1 S4)
        - N2 = produit vectoriel (S3 S4,S3 S2)
        (S1,S2,S3,S4 sont les sommets de l'element)

        Les valeurs sont comprises entre 0 et 100.
        Un mchaml resultat de valeur constante egale a 100
        indiquera que tous les elements sont plans.

'ASPE' : Pour les elements TRI3 et TET4 seulement
        Rapport d'aspect (aspect ratio), il s'agit du rapport de la
        plus grande arete sur la plus petite hauteur, normalise

        - pour les TRI3 = SQRT(3)/2 * grande arete / petite hauteur
        - pour les TET4 = SQRT(2/3) * grande arete / petite hauteur

        Les valeurs sont comprises entre 1 (element equilateral)
        et + infini

'SKEW' : Pour les elements TRI3 et TET4 seulement
        Pointicite (skewness), il s'agit de l'ecart relatif entre la
        mesure de l'element et celle de l'element "optimal"

        SKEW = (mes_optimal - mes) / mes_optimal

        La mesure est l'aire (pour les TRI3) ou le volume (pour les TET4)

        L'element "optimal" est l'element equilateral place dans la
        meme sphere circonscrite que l'element etudie

        Les valeurs sont comprises entre 0 (element equilateral)
        et 1 (element degenere)

 |  2eme possibilite  |

  CHAM1 = INDI 'TOPO' MAIL1 (METR1) ('LISTREEL') ;

  Objet :

  L'operateur INDI fournit un indicateur de qualite d'un maillage
  de TRI3 ou de TET4, eventuellement dans une metrique donnee.

  Commentaire :

  MAIL1 : maillage (type MAILLAGE) constitué d'un seul type
        d'elements TRI3 ou TET4
  METR1 : objet de type FLOTTANT ou CHPOINT
        Si METR1 est de type FLOTTANT, il s'agit de la taille
        d'arete voulue (densite)
        Si METR1 est de type CHPOINT, il s'agit de l'inverse
        de la metrique voulue (unite : longueur^-2)

  CHAM1 : champ (type MCHAML ou LISTREEL) de qualite

  Remarques :

  1) Si la metrique voulue est isotrope, le nom de composante est G.
     Si la metrique voulue est anisotrope, les noms des composantes
     sont : G11, G21, G22, (G31, G32, G33 en 3D)

  2) En presence du mot-cle LISTREEL, l'operateur renvoie un objet
     de ce type plutot que du type MCHAML.

  3) L'indicateur varie entre 0 (element degenere) et 1
     (element equilateral, de cote 1 dans la métrique voulue si
     METR1 est donnee)

## INDIBETA [Mathematiques Statistiques] (proc)
Procedure INDIBETA

FLOT4 = INDIBETA FLOT1 FLOT2 FLOT3;

Objet :

Cette procedure calcule l'indice de fiabilite associe a une
probabilite.

Commentaire :

FLOT1 = borne inferieure (type FLOTTANT)

FLOT2 = borne superieure (type FLOTTANT)

FLOT3 = probabilite (type FLOTTANT)

FLOT4 = indice de fiabilite (type FLOTTANT)

## INDIOBJE [Multi-physique Multi-physique] (proc)
Methode INDIOBJE
--------------- CHANUOBJ

  OBJ1 = OBJET INDIOBJE ;

    Objet

 La methode INDIOBJE definit un objet de CLASSE INDIOBJE.
 Les elements sont des entiers definis par l'utilisateur.
 Methode associee: GINDIOBJ.
        appel: OBJ1%GINDIOB num OBJ2 ;

## INDUCTIO [Magnetostatique Magnetostatique] (proc)
      Procedure INDUCTIO

      OBJET1 = INDUCTIO GEO1 CHP1 LOG1 (MOT1)

      Objet :
      En magnetostatique 2d potentiel vecteur calcul de l'induction
      a partir du potentiel vecteur

      Commentaire :

      GEO1 maillage sur lequel on veut l'induction
      CHP1 solution en potentiel definie au moins sur GEO1
      LOG1 variable logique valant VRAI si le probleme est
        axisymetrique.
      MOT1 'MCHAML' si l on veut le champ par element aux
        points d'integration

      en sortie :
      OBJET1 champ par point ( defaut ) ou par element
de composantes BX BY sur GEO1

NOTA : en axisymetrique BX et BY correspondent a BR et BZ

## INFO [Entree-Sortie Entree-Sortie]
    Directive INFO

    INFO MOT1 ;

    Objet :

    La directive INFO affiche la notice de la fonctionnalite de nom MOT1.
Par exemple :
    INFO OPTION ;
affiche la notice de la directive OPTION. L'ensemble des notices definit
le referentiel fonctionnel de Cast3M.

    A chaque page, il faut faire un retour chariot pour passer a la page
suivante. q, puis retour chariot permet de quitter.

    Dans le cas de notices structurees en chapitres et parties,
la directive INFO affiche un sommaire et permet de se positionner
dans la notice aux endroits references dans le sommaire.

## INICHI1 [Multi-physique Multi-physique] (proc)
 Procedure INICHI1
 ------------------ CHI2 DONCHI2

INICHI1 OBJ1 MOT1 MOT2 ;

    Objet
    Cette procedure permet de modifier de façon interactive,
    un objet de type DONCHI1 utilisable par l'operateur CHI1
    Pour toutes les questions posees :
    La touche <Entree> fait passer a la sequence suivante dans
    la procedure.
    La reponse 'OUI' permet d'effectuer l'operation proposee.

    Commentaires
    OBJ1 : Objet de type DONCHI1
    MOT1 : adresse du fichier de composants de la base de donnees.
    MOT2 : adresse du fichier de LOGK de la base de donnees.

## INICHI2 [Multi-physique Multi-physique] (proc)
  Procedure INICHI2
  ----------------- CHI2 DONCHI2

INICHI2 TAB1 OBJ1 (MAIL1);

     Objet
     Cette procedure permet de modifier, de façon interactive,
     un objet de classe DONCHI2 utilisable par l'operateur CHI2.
     Toutes les valeurs sont supposees constantes dans l'espace
     pour le maillage considere.
     Pour toutes les questions posees :
     La touche <Entree> fait passer a la sequence suivante dans
     la procedure.
     La reponse 'OUI' permet d'effectuer l'operation proposee.

     Commentaires
     TAB1 : table de soustype CHIMI1. Resultat de CHI1.
     OBJ1 : Objet de classe DONCHI2 (utilise en entree et en sortie)
     MAIL1: Maillage support pour les CHPOIN. A defaut si OBJ1%GTOT
        est donne on prendra son maillage support.
        Si on ne donne ni MAIL1 ni OBJ1%GTOT le support
        geometrique par defaut sera un point de coordonnees
        ( 0. 0.).

## INICHIMI [Multi-physique Multi-physique] (proc)
  Procedure INICHIMI
  ------------------ CHI2 DONCHI2

OBJ4 TAB1 OBJ5 = INICHIMI (OBJ1) (MOT1) (MOT2) (OBJ2) (OBJ3) (MAIL1);

      Objet
      Cette procedure permet d'initialiser, de façon interactive,
      les donnees pour un calcul de geochimie faisant intervenir
      les operateurs CHI1 et CHI2.
      Elle permet de calculer les concentrations totales des
      composants a partir des activites ou des quantites de mineraux
      desirees.
      Cette procedure permet egalement de determiner les
      concentrations totales des composants pour obtenir l'equilibre
      electrique.
      Toutes les valeurs sont supposees constantes dans l'espace
      pour le maillage considere.(cf CCDONCHI pour des valeurs
      non constantes)
      Tous les arguments d'entree sont facultatifs car en leur
      absence la procedure demande a l'utilisateur d'entrer les
      differentes valeurs au clavier.
      Pour toutes les questions posees :
      La touche <Entree> fait passer a la sequence suivante dans
      la procedure.
      La reponse 'OUI' permet d'effectuer l'operation proposee.
      La reponse 'QUIT' permet de sortir de la procedure.

      Commentaires
      OBJ1 : Objet de type DONCHI1
      MOT1 : adresse du fichier de composants de la base de donnees.
      MOT2 : adresse du fichier de LOGK de la base de donnees.
      OBJ2 : Objet de type DONCHI2
      OBJ3 : Objet de type PARMCHI2
      MAIL1: Maillage support pour les CHPOIN. A defaut si OBJ2%GTOT
        est donne on prendra son maillage support.
        Si on ne donne ni MAIL1 ni OBJ2%GTOT le support
        geometrique par defaut sera un point de coordonnees
        ( 0. 0.).
      OBJ4 : Objet de type DONCHI1. Il contient les corrections
        apportees interactivement a OBJ1.
      TAB1 : table de soustype CHIMI1. Resultat CHI1 applique a OBJ4.
      OBJ5 : Objet de type DONCHI2.

## INIMUR [Fluides Resolution] (proc)
  Procedure INIMUR

  OBJET :

Procedure appelee uniquement par le procedure ENCEINTE.

## ININLIN [Multi-physique Multi-physique] (proc)
$X ININLIN

      Procedure ININLIN

      TAB1 = ININLIN ENT1 ENT2 ENT3 ENT4 ENT5 ;

      Objet :

      Procedure permettant d'initialiser une table argument
      pour l'operateur NLIN.

      ENT1 : objet de type ENTIER, nombre d'operateurs

      ENT2 : objet de type ENTIER, nombre de variables

      ENT3 : objet de type ENTIER, nombre de donnees

      ENT4 : objet de type ENTIER, nombre de coefficients

      ENT5 : objet de type ENTIER, nombre de dimensions de
        l'espace d'integration

## INITEFMH [Fluides Resolution] (proc)
      Operateur INITEFMH

  ATTENTION La vitesse est optionnelle, L'ordre est important
  et les types d'arguments qui se suivent aussi pour tester leur
  presence

  Cette procedure est appelee par TRANGEOL.
  Pas de notice car pas pour utilisateur lambda.

|-----------------------------------------------------------------|
| Phrase d'appel (en GIBIANE)  |
|-----------------------------------------------------------------|
|  |
| SMTr MatrTr CoefDt TbDarTra MassEFMH nomespec  |
| nbespece Difftot Tcini TABRES TABMODI= INITEFMH MoDARCY Porosite|
|  MateDiff ChPSour DeltaT Cini TetaDiff  |
|  TetaConv TetaLin fluimp dircli (QFACE)  |
|  LMLump DECENTR CHCLIM optresol ;  |
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
| Porosite : champoint de composante 'CK'  |
|  |
| MateDiff : Tenseur de diffusion  (type iso, ..) champoint  |
|  de composante 'K' en isotrope, 'K11', 'K21',  |
|  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
|  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQUE'|
|  |
| DeltaT  : Pas de temps.  |
|  |
| ChPSour  : Champ par points des sources volumiques par unite de |
|  temps (support maillage centre). Composante ??????  |
|  |
| Cini  : Concentration initiale, CHPOINT centre.  |
|  Composante 'H'.  |
|  |
| Qface  : vitesse aux faces, CHPO face de composantes Vx, Vy  |
|  en 2d et Vx, Vy, Vz en 3d. Il s'agit plus exatement  |
|  de (V.n)n, c'est a dire de la composante normale de  |
|  la vitesse aux faces. ???????? (je pressens que  |
|  castem va sortir des flux, cad integres sur surfaces)|
|  |
| TetaDiff : Valeur de theta pour theta-schema en temps, operateur|
|  de diffusion. Entre 0 et 1. 0 = explicite, 1 = euler |
|  implicite.  |
|  |
| TetaConv : Valeur de theta pour theta-schema en temps, operateur|
|  de convection. Entre 0 et 1. 0 = explicite, 1 = Euler|
|  implicite.  |
|  |
| TetaLin  : valeur de theta pour theta-schema en temps, operateur|
|  lineaire du type coef * C, ou C est l'inconnue.  |
|  Entre 0 et 1. 0 = explicite, 1 = euler implicite.  |
|  ??????????? A voir car peut etre identique a Tetadiff|
|  |
| LMLump  : Logique. Si vrai on effectue une condensation de  |
|  masse de la matrice EFMH  |
|  |
| DECENTR  : Logique. Vrai veut dire schemas decentres et faux  |
|  veut dire schema convectif centre.  |
|  |
| CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
|  Chpoint a n composantes contenant les conditions aux |
|  limites de Neumann et Dirichlet par espece.  |
|  L'indice 'FLUXTOT' contient les conditions limites  |
|  de flux total et 'FLUMIXTE' concerne une condition  |
|  de flux mixte : 'FLUMIXTE' . 'VAL' contient le champ |
|  a n composantes indiquant le flux, 'FLUMIXTE' . 'A'  |
|  et 'FLUMIXTE' . 'B' les coef (champoints SCAL) tels  |
|  que A D grad (C) + B (C) = VAL  |
|  |
| OPTRESOL : Table dont l'entree est optionnelle definissant  |
|  les options de resolution pour 'KRES'.  |
|  |
|-----------------------------------------------------------------|
|  SORTIES  |
|-----------------------------------------------------------------|
|  |
|  |
| MassEFMH : matrice elementaire EFMH  |
|  |
| MatrTr  : matrice globale sur les traces  |
|  |
| SMTr  : second membre sur les traces  |
|  |
| TbDarTra : table Darcy transitoire utilisee par MHYB, SMTP ...  |
|  |
| nomespec : liste des noms de composante des especes dans Cini  |
|  |
| nbespece : nombre de composante de Cini, soit nombre d'especes  |
|  |
| nbsource : nombre de composantes du terme source qd X especes  |
|  |
| Diffdisp : Dipersivite, tenseur chpoint K11 K22 K33 K21 K31 K32 |
|  |
| TABRES  : Table complete definissant les options de resolution |
|  pour 'KRES'.  |
|  |
| Tcini  : Trace de concentration aux faces (eventuellement a  |
|  plusieurs composantes (especes)  |
|  |
| TABMODI  : table contenant des logiques indiquant la necessite  |
|  ou non de reclalculer certains termes.  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## INITOU [Mecanique Rupture] (proc)
    Procedure INITOU

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

  La procedure initou permet de positionner les points de fissure.

   Description :

L'entree pour initou:
TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :

    TAB1.GEO MAILLAGE : structuré a post-traiter (CUB8)
    TAB1.POI POI1 : sur un bord du maillage
    TAB1.LH MAILLAGE : ligne de limite haute
    TAB1.LB MAILLAGE : ligne de limite basse
    TAB1.LG MAILLAGE : ligne de limite gauche
    TAB1.LD MAILLAGE : ligne de limite droite
    TAB1.PLA MOTS : 'XY', 'YZ', 'ZX' defini le plan de
        post-traitement

    TAB1.HOR LOGIQUE : vrai si le cacule du saut horizontal
    TAB1.PAS ENTIER : numero de pas

    TAB1.CRITO FLOTTANT : critere du seuil pour la norme de saut de
        deplacement
    TAB1.CRITP FLOTTANT : critere du seuil pour la position de fissure

La sortie pour initou:

    TAB1.LIGV TABLE : ligne verticale de repere
    TAB1.LIGH TABLE : ligne horizontal de repere
    TAB1.TELZ TABLE : taille de grille verticale
    TAB1.TELX TABLE : taille de grille horizontale

    TAB1.SDH TABLE : saut de deplacement dans les trois directions
    TAB1.CDH TABLE : coordonnee du saut de deplacement

    TAB1.OUFT TABLE : norme de saut sur chaque ligne
    TAB1.COTX TABLE : coordonnee X sur chaque ligne
    TAB1.COTZ TABLE : coordonnee Z sur chaque ligne
    TAB1.OUFTT LISTREEL : norme de saut sur la structure
    TAB1.COTXX LISTREEL : coordonnee X sur la structure
    TAB1.COTZZ LISTREEL : coordonnee Z sur la structure

    TAB1.PFO TABLE : maxima locaux de la norme de saut
        sur chaque ligne
    TAB1.PFX TABLE : coordonnee X sur chaque ligne
    TAB1.PFZ TABLE : coordonnee Z sur chaque ligne
    TAB1.LPFO LISTREEL : maxima locaux de la norme de
        saut sur la structure
    TAB1.LPFX LISTREEL : coordonnee X sur la structure
    TAB1.LPFZ LISTREEL : coordonnee Z sur la structure

## INITVF [Fluides Resolution] (proc)
    Operateur INITVF

ATTENTION La vitesse est optionnelle, L'ordre est important
et les types d'arguments qui se suivent aussi pour tester leur
presence

Appele par TRANGEOL. Pas pour utilisateurs.

 |-----------------------------------------------------------------|
 | Phrase d'appel (en GIBIANE)  |
 |-----------------------------------------------------------------|
 |  |
 | RESI Matot jaco Mpor2 Mchamt mchamt1  difftot nomespec nbespece  |
 | nbsource  TABRES TABMODI NOUVMAT = INITVF MoDARCY Porosite  |
 |  MateDiff ChPSour DeltaT Cini TetaDiff  |
 |  TetaConv TetaLin  (QFACE)  QELEM  |
 |  DISPL  DISPT CHCLIM optresol ;  |
 |  |
 |-----------------------------------------------------------------|
 | Generalites : INITVF construit la matrice de discretisation  |
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
 |  elements de composante 'K' en isotrope, 'K11', 'K21',|
 |  'K22' en anisotrope 2d et  'K11', 'K21', 'K22', 'K31'|
 |  'K32', 'K33' en anisotrope 3d. Type 'CARACTERISTIQ
 |  |
 | ChPSour  : Champ par points des sources volumiques par unite de |
 |  temps (support maillage centre). Composante ??????  |
 |  |
 | DeltaT  : Pas de temps.  |
 |  |
 | Cini  : Concentration initiale, CHPOINT centre.  |
 |  |
 | TetaDiff : Valeur de theta pour theta-schema en temps, operateur|
 |  de diffusion. Entre 0 et 1. 0 = explicite, 1 = euler |
 |  implicite.  |
 |  |
 | TetaConv : Valeur de theta pour theta-schema en temps, operateur|
 |  de convection. Entre 0 et 1. 0 = explicite, 1 = Euler|
 |  implicite.  |
 |  |
 | TetaLin  : valeur de theta pour theta-schema en temps, operateur|
 |  lineaire du type coef * C, ou C est l'inconnue.  |
 |  Entre 0 et 1. 0 = explicite, 1 = euler implicite.  |
 |  ??????????? A voir car peut etre identique a Tetadiff|
 |  |
 |  |
 | Qface  : vitesse aux faces, CHPO face de composantes Vx, Vy  |
 |  en 2d et Vx, Vy, Vz en 3d. Il s'agit plus exatement  |
 |  de (V.n)n, c'est a dire de la composante normale de  |
 |  la vitesse aux faces. ???????? (je pressens que  |
 |  castem va sortir des flux, cad integres sur surfaces)|
 |  |
 | CHCLIM  : table d'indice 'NEUMANN' et 'DIRICHLET' contenant les|
 |  Chpoint a n composantes contenant les conditions aux |
 |  limites de Neumann et Dirichlet par espece.  |
 |  |
 | OPTRESOL : Table dont l'entree est optionnelle definissant  |
 |  les options de resolution pour 'KRES'.  |
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
 | Jaco  : matrice globale de discretisation en VF pour le probleme
 |  stationnaire  |
 |  |
 | Mpor  : matrice globale de discretisation en VF pour le probleme
 |  stationnaire  |
 |  |
 | Mchamt  : Coef permettant de calculer le flux total  |
 |  |
 | Mchamt1  : Coef permettant de calculer le flux diffusif  |
 |  |
 | Difftot  : Coefficient de diffusion totale, integre decentrement|
 |  |
 | Diffdisp : Coefficient de dispersivite  |
 |  |
 | nomespc  : liste des noms de composante des especes dans Cini  |
 |  |
 | nbespece : nombre de composante de Cini, soit nombre d'especes  |
 |  |
 | nbsource : nombre de composantes du terme source qd X especes  |
 |  |
 | TABRES  : Table complete definissant les options de resolution |
 |  pour 'KRES'.  |
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
[… notice tronquée ; texte complet dans l'archive PCW_24]

## INSE [Langage Objets]
    Operateur INSERER

      OBJET3 = INSERER OBJET1 N1 OBJET2 ;

    Objet :

    L'operateur INSERER insere dans OBJET1 l'objet OBJET2 a la position
N1 (et non pas apres). L'objet OBJET3 cree est de meme type que OBJET1.

    Operations possibles :

    |  OBJET1  |  N1  |  OBJET2  |
    |  LISTREEL  |  ENTIER  |  FLOTTANT  |
    |  LISTENTI  |  ENTIER  |  ENTIER  |
    |  LISTMOTS  |  ENTIER  |  MOT  |
    |  LISTCHPO  |  ENTIER  |  CHPOINT  |

## INSI [Mecanique Dynamique]
Operateur INSI

EVOL1 EVOL2 = INSI EVOL3 (MOT1);

        MOT1='SIMP','LINE'

objet :

Operateur INSI effectue l'integration numerique des signaux en
accelerations EVOL3 (comportant N courbes) et genere ainsi les
signaux en vitesse EVOL2 et en deplacement EVOL1 (comportant N
courbes).

Si EVOL3 est un ensemble d'accelerogrammes corriges a l'aide de
l'operateur COSI (utilisant la meme option), la vitesse finale,
le deplacement final et le deplacement moyen des signaux generes
sont nuls.

option:

Diverses methodes d'integration numerique peuvent etre choisies en
utilisant le mot-cle MOT1 :

- MOT1='SIMP'(lifie) se refere a l'utilisation d'une methode des
  trapezes pour deduire chaque variables de la discretisation de sa
  derivee.

- MOT1='LINE'(aire) se refere a l'utilisation d'un approximation
  lineaire de l'acceleration et a son integration consistante.
  Le defaut pour MOT1 est 'SIMP'.

## INTE [Maillage Manipulation]
    Operateur INTERSECTION

    Objet :

CHAP{Elements communs a deux maillages}

    MELE3 = MELE1 'INTER' MELE2 ;

    L'operateur INTERSECTION construit l'intersection de deux maillages,
    c'est a dire l'ensemble des elements appartenant aux deux maillages.

    Commentaire :

    MELE1 | : maillages en entree
    MELE2 |

    MELE3 : maillage constitue des elements appartenant aux deux
        maillages initiaux

CHAP{Intersection de deux surfaces analytiques}

    LIG1 = POIN1 INTER (N1) ('DINI' DENS1 ) ('DFIN' DENS2 )

        ('LONG' DLONG)...

    ...  |'PLAN' P1  | |'PLAN' P2  | POIN2
        |'SPHE' CENTR1  | |'SPHE' CENTR2  |
        |'CYLI' AXEI1  AXEJ1  | |'CYLI' AXEI2  AXEJ2  |
        |'CONI' SOMM1  P1  | |'CONI' SOMM2  P2  |
        |'TORI' CENTR1 P1  PC1 | |'TORI' CENTR2  P2  PC2 |

    L'operateur INTERSECTION construit l'arc de courbe, intersection de
    deux surfaces, compris entre deux points POIN1 et POIN2.

    Commentaire :

    POIN1 | : points extremite de l'arc de courbe genere (type POINT)
    POIN2 |

    N1 : nombre de segments generes (type ENTIER)

    DENSi : densites associees aux points extremite de l'arc (type
        FLOTTANT).
        le mot-cle 'DINI' permet de definir la densite du premier
        point et 'DFIN' celle du dernier point.

    DLONG : longueur de l'arc.
        le mot-cle 'LONG' permet d'imposer la longueur de l'arc.
        dans ce cas un nouveau point extremite final est calcule
        a partir de POIN2 et de LONG.

    Les surfaces peuvent etre planes, spheriques, cylindriques,
    coniques ou toriques suivant le mot-cle :

    'PLAN' : surface plane passant par Pi (type POINT)
    'SPHE' : surface spherique de centre CENTRi (type POINT)
    'CYLI' : surface cylindrique d'axe AXEIi AXEJi (type POINT)
    'CONI' : surface conique de sommet SOMMi (type POINT) passant par
        Pi(type POINT)
    'TORI' : surface torique de centre CENTRi (type POINT), d'axe CENTR
        Pi (type POINT); PCi est le centre d'un petit cercle.

    Remarque :

    Si N1 n'est pas specifie, l'arc de courbe est divise en accord avec
    les densites definies aux points POIN1 et POIN2.

    Si les densites associees aux points POIN1 et POIN2 ne sont pas
    correctes, il est possible de les surcharger. Pour le premier
    point donner la bonne valeur derriere la mot-cle 'DINI' et pour le
    deuxieme point, derriere le mot-cle 'DFIN'.

    Si une ligne LIGi est donnee a la place du point POIN1 (ou POIN2),
    cette ligne est prolongee jusqu'au point POIN2 (elle commence au
    point POIN1).

    Si le point POIN2 n'est pas donne, la premiere extremite de la ligne
    LIGi est prise en compte, ce qui permet de fermer celle-ci.

CHAP{Intersection geometrique de deux maillages}

    MELE1b MELE2b MELE3 MELE4 = 'INTER' 'GEOM' MELE1 MELE2

    L'operateur INTERSECTION construit l'intersection geometrique de
    deux maillages. Par exemple, l'intersection d'une sphere et d'un
    plan est un cercle.
    Cette option est aujourd'hui limitee au cas non-coplanaire de deux
    surfaces 3D constituée de triangle a 3 noeuds.

    Commentaire :

    MELE1 | : maillages en entree
    MELE2 |

    MELE1b : maillage issu de MELE1 dont certains elements ont ete
        coupes par l'intersection avec MELE2
    MELE3 : maillage decrivant l'intersection geometrique dont les
        noeuds appartiennent a MELE1b
    MELE2b et MELE4 : semblables a MELE1b et MELE3 avec des noeuds
        differents

    'NOVERIF' : Mot cle indiquant de ne pas produire d'erreur si
        l'intersction est 'VIDE'. Un maillage vide est généré.

CHAP{Intersection de deux modeles}

    MOD3 = MOD1 INTE MOD2 ;

    Objet :

    L'operateur INTERSECTION construit l'intersection de deux modeles,
    c'est a dire l'ensemble des sous-zones appartenant aux deux modeles.

    Commentaire :

    MOD1  | : objets de type MMODEL
    MOD2  |

    MOD3 : objet MMODEL resultat, constitue des sous-zones communes
        aux deux modeles.

    Remarque : pour les objets MMODEL, l'operation est faite
    __________ sur les sous-zones. Si l'operation est menee
        dans le but d'obtenir un modele portant sur

CHAP{Intersection de deux rigidites}

    RIG3 = RIG1 INTE RIG2 ;

    Objet :

    L'operateur INTERSECTION construit l'intersection de deux rigidites,
    c'est a dire l'ensemble des rigidites elementaires communes.

    Commentaire :

    RIG1  | : objets de type RIGIDITE,
    RIG2  |

    RIG3 : objet RIGIDITE resultat.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## INTG [Mathematiques Autres]
    Operateur INTG

    L'operateur INTG realise l'integration :
    - d'une composante d'un champ (objet de type CHAMELEM) (syntaxe 1)
       . soit sur le domaine ou elle est definie, auquel cas le resultat
        est un nombre,
       . soit sur chacun des elements (option 'ELEM') auquel cas le
        resultat est un champ par elements.
    - de fonction(s) (objet de type EVOLUTION) (syntaxe 2) par la
      methode des trapezes.

CHAP{Integration d'un champ par element}

      OBJET1 = INTG ('ELEM') MODL1 CHAM1 (MOT1) (CAR1) ;

      Commentaire :

      MODL1 : objet modele (type MMODEL).

      MOT1 : nom de la composante (type MOT),
        inutile si le champ n'a qu'une composante

      CHAM1 : champ contenant la composante qu'on integre (type MCHAML)

      CAR1 : champ de caracteristiques geometriques (type MCHAML,
        sous-type CARACTERISTIQUES)

      OBJET1 : objet resultat :

        - nombre (type FLOTTANT) si l'integration est realisee
        sur le domaine de definition de la composante

        - champ par elements (type MCHAML, sous-type SCALAIRE)
        dont les valeurs sont definies aux centres de gravite
        si l'integration est realisee sur chacun des elements
        (option avec le mot-cle 'ELEM')

      Attention : Pour les coques, le domaine d'integration est la
      ----------- surface de la coque et pour les poutres, le domaine
        d'integration est la ligne moyenne de la poutre.
        Si l'on veut integrer sur le volume de ces elements,
        il faut donner le champs de caracteristiques
        geometriques CAR1 (type MCHAML, sous-type
        CARACTERISTIQUES)

      Exemples d'applications possibles :

      calcul de la masse, du volume, de l'energie dissipee, etc ...

CHAP{Integration d'une evolution}

        | LREE1 LREE2 |
    RESU1  =  INTG  EVOL1 ('ABS') | ('BORN' | FLOT1 FLOT2 |) ;
        |
        | ('INDI' |  ENT1  ENT2 |) ;
        | LENT1 LENT2 |

   Commentaire :

     EVOL1 : fonction a integrer (type EVOLUTION).

     'ABS' : mot-cle pour integrer la valeur absolue de la fonction.

     'BORN' : mot-cle pour preciser les bornes de l'intervalle
        d'integration.

     FLOT1, FLOT2 : bornes de l'intervalle d'integration (type FLOTTANT).
        Si besoin, la valeur de l'evolution est interpolee
        (voir IPOL).
        Si FLOT1 > FLOT2, alors les bornes sont inversees et
        l'integrale est multipliee par -1.

     LREE1, LREE2 : definition de plusieurs intervalles d'integration
        en donnant deux listes de bornes (type LISTREEL).
        Si besoin, la valeur de l'evolution est interpolee
        (voir IPOL).
        Si certaines bornes sont donnees dans un ordre decroissant
        (FLOT1 > FLOT2), alors les bornes sont inversees et
        les integrales correspondantes sont multipliees par -1.

     'INDI' : mot-cle pour preciser les bornes de l'intervalle
        d'integration a l'aide des indices de la liste des
        abscisses.

     ENT1, ENT2 : indices de la liste des abscisses definissant les
        bornes de l'intervalle d'integration (type ENTIER).
        Si ENT1 > ENT2, alors les bornes sont inversees et
        l'integrale est multipliee par -1.

     LENT1, LENT2 : listes d'indices de la liste des abscisses definissant
        les intervalles d'integration (type LISTENTI).
        Si certains indices sont donnes dans un ordre decroissant
        (ENT1 > ENT2), alors les bornes sont inversees et les
        integrales correspondantes sont multipliees par -1.

     RESU1 : objet resultat, dont le type est :

        - FLOTTANT, si l'on integre une evolution sur 1 intervalle
        d'integration.

        - LISTREEL, si l'on integre une evolution sur plusieurs
        intevralles d'integration ou plusieurs evolutions (EVOL1
        contient plusieurs courbes) sur 1 interval d'integration.

        - NUAGE, si on integre plusieurs evolutions sur plusieurs
        intervalles d'integration. Dans ce cas, le NUAGE resultat
        comporte autant de composantes que d'evolutions, les noms
        de composante etant le numero de chaque courbe prefixee
        par 'IE' : 'IE1' pour la 1ere, 'IE2' pour la 2e...
        Chaque composante contient alors 1 LISTREEL, resultat de
        l'integration de l'evolution correspondante sur les
        differents intervalles d'integration.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## INTK [Presentation Presentation]
 INTRODUCTION : PRINCIPES ET NOTIONS DE BASE

 Castem 2000 est un programme de nouvelle generation.
L'utilisateur dispose de plusieurs notions lui permettant de
construire lui meme l'application qu'il desire dans un langage
qui lui est familier.

  LE CONCEPT D OBJET NOMME
 L'utilisateur resout son probleme en creant des OBJETS qu'il nomme.
Ces objets sont types et ranges dans une base de donnees.
A tout instant ces objets peuvent etre utilises et retrouves par
leur nom. Leur type permet de les classer et de savoir comment ils
peuvent etre manipules par les operateurs.

  LE CONCEPT D'OPERATEUR

 Les outils utilises pour creer ces objets sont appeles OPERATEURS.
Les OPERATEURS creent un ou plusieurs objets types a partir d'objets
existants fournis par l'utilisateur a l'aide du langage GIBIANE.

  LE LANGAGE GIBIANE

 Le langage GIBIANE permet d'enchainer les operateurs en leur faisant
lire et ecrire dans la base de donnees.

 Le langage permet aussi d'effectuer des boucles et des tests
logiques. L'utilisateur peut ainsi batir une application parametree
et meme programmer des algorithmes.

  LE CONCEPT DE PROCEDURE

 Une fois un algorithme ecrit et teste l'utilisateur peut souhaiter
archiver cet algorithme pour l'utiliser ulterieurement lui meme ou
bien pour permettre a d'autres d'utiliser son travail. La PROCEDURE
lui permet de le faire.

 La PROCEDURE s'utilise comme un operateur, qui a partir d'objets
types cree de nouveaux objets.

 Cependant la PROCEDURE est ecrite en GIBIANE et peut donc etre
realisee par l'utilisateur.

  QUEL TYPE D'ANALYSE PEUT ON FAIRE AVEC CASTEM 2000

 Castem 2000 est un outil de calcul de structure complet qui va du
mailleur GIBI a l'exploitation des resultats en passant par tous les
types de calculs envisageables.

 Il s'applique aux problemes mono bi et tri-dimensionnels.

 Les operateurs peuvent etre regroupes en plusieurs grandes classes:

| TYPE D OPERATEUR  |  NOM  | DISPONIBLE |
|-------------------------------------------------------------------|
| Les operateurs generaux  |  GENE  |  OUI  |
|-------------------------------------------------------------------|
| Les operateurs de maillage  |  GIBI  |  OUI  |
|-------------------------------------------------------------------|
| Les operateurs de calcul statique  |  STAT  |  OUI  |
|-------------------------------------------------------------------|
| Les operateurs de calcul dynamique  |  DYNA  |  ?  |
|-------------------------------------------------------------------|
| Les operateurs de calcul dynamique modal |  OSCAR  |  OUI  |
|-------------------------------------------------------------------|
| Les operateurs de calcul non lineaire  |  NONLIN |  OUI  |
|-------------------------------------------------------------------|
| Les operateurs de flambement  |  FLAM  |  ?  |
|-------------------------------------------------------------------|
| Les operateurs de visualisation  |  CINEMA |  OUI  |

## INT_COMP [Mathematiques Autres] (proc)
  Procedure IN_COMP

CHPO1 = INT_COMP GEO1 CHPO2 GEO2

  Objet :

  Interpolation d'une composante d'un champ par point sur
  un maillage

  Commentaire :

  GEO1 maillage supportant le champ par point initial
  CHPO2 champ par point a une composante defini sur GEO1
  GEO2 maillage support du champ par point de sortie chp1

  Cette procedure utilise l'operateur PROI qui exige en entree
  un chamelem , chpo2 est ici converti en utilisant un mmodel
  de thermique isotrope.

  En sortie :

   CHPO1 Champ par point resultat de l'interpolation

## INVA [Mecanique Resolution]
Operateur INVA
-------------- EPSI

  CHAM1 CHAM2 CHAM3 = INVA MOD1 CHAM4 (CAR1) (MOT1) ;

Objet :

L'operateur INVA calcule les 3 invariants d'un champ de tenseurs
de contraintes ou de deformations.

Le resultat est constitue de 3 champs scalaires. Le support de ces
champs est le meme que celui du champ tensoriel CHAM4.

  Commentaire :

  MOD1 : Objet modele (type MMODEL)

  CHAM4 : champ de tenseurs de contraintes ou de deformations
        (type MCHAML, sous-type CONTRAINTES ou DEFORMATIONS)

  CAR1 : champ de caracteristiques geometriques necessaire pour
        les elements de coques minces
        (type MCHAML, sous-type CARACTERISTIQUES)

  CHAM1 : premier invariant ( la trace )
        (type MCHAML, sous-type SCALAIRE)

  CHAM2 : deuxieme invariant ( la somme des produits 2 a 2 )
        (type MCHAML, sous-type SCALAIRE)

  CHAM3 : troisieme invariant ( le determinant )
        (type MCHAML, sous-type SCALAIRE)

  MOT1 : mot-cle (type MOT) qui indique pour les coques ou
        on veut calculer les contraintes ou les deformations:

        'SUPE' : en peau superieure
        'MOYE' : sur la surface moyenne ( par defaut )
        'INFE' : en peau inferieure

## INVE [Maillage Manipulation]
Operateur INVERSE

1ere fonction :

GEO2 = INVERSE GEO1 ;

Objet :

L'operateur INVE permet d'inverser l'orientation des elements
orientables de GEO1 (type MAILLAGE).

Remarques :

Les elements orientables sont les suivants :
SEG2, SEG3, TRI3, TRI4, TRI6, TRI7, QUA4, QUA5, QUA8, QUA9, TET4,
TE10, TE15, PRI6, PR15, PR21, PYR5, PY13, PY19, CUB8, CU20, CU27

Dans le cas des lignes (SEG2/SEG3), l'ordre de description des
elements est egalement inverse.

Le maillage d'entree GEO1 peut etre complexe ; les elements ne
pouvant etre inverses restant inchanges.

2eme fonction :

CHP2 = INVERSE CHP1 ;

Objet :

L'operateur INVE calcule l'inverse d'un champ par point CHP1 au sens
de la multiplication '*'. On cree un champ par point CHP2 semblable
a CHP1 et dont les valeurs sont les inverses des valeurs de CHP1.
La nature de CHP2 est identique a celle de CHP1.

## IN_MINI [Magnetostatique Magnetostatique] (proc)
Procedure IN_MINI

    appelee par la procedure POT_SCAL

  Objet :
  En magnetostatique calcul du saut de potentiel dans la methode
  a deux potentiel scalaires couples sur l'interface, elle est
  appelee par la procedure POT_SCAL.

## IPOL [Mathematiques Autres]
    Operateur IPOL

CHAP{Interpolation d'une fonction (EVOLUTION ou 2 LISTREEL)}
PART{Syntaxe}
    OBJET2 = 'IPOL'  OBJET1 | LREEL1 LREEL2 | ...
        | EVOL1  |

        ... | ('SPLI' ('DGAU' FLOT1) ('DDRO' FLOT2)) ;
        | 'TOUS';
PART{Objet}
L'OBJET2 obtenu par interpolation d'une fonction f definie par :
        LREEL1 : LISTREEL des abscisses {t_i}
        LREEL2 : LISTREEL des ordonnees correspondantes {f_i}
        ou par
        EVOL1 : EVOLUTION scalaire elementaire
        en l'abscisse OBJET1 de valeur t : OBJET2=f(t)

        OBJET2 a le meme type et les memes caracteristiques que OBJET1.
        Les types possibles pour OBJET1 sont : - FLOTTANT
        - LISTREEL
        - CHPOINT
        - MCHAML

        Par defaut, l'interpolation lineaire est utilisee et les
        abscisses doivent imperativement etre rangees par ordre
        croissant ou decroissant.

      - 'SPLI' : mot-cle permettant de specifier une interpolation par spline
        cubique. Dans ce cas, on peut preciser la valeur de la derivee
        premiere de la spline sur les bords gauche et droit de son
        intervalle de definition avec les mots-cles 'DGAU' et 'DDRO'.
        Si la derivee première n'est pas specifiee, on utilise la
        condition naturelle : derivee seconde nulle.
      Remarque : l'interpolation par spline cubique n'est pas locale,
        elle depend de l'ensemble des valeurs de la fonction donnee.

      - 'TOUS' : mot-cle permettant de specifier que la fonction f peut etre
        multi-valuee. La suite des abscisses n'est donc pas monotone.
        Dans ce cas, OBJET1 est necessairement un FLOTTANT et OBJET2
        est un LISTREEL contenant l'ensemble des y tel que y=f(t).

CHAP{Interpolation d'une TABLE de soustype 'RESULTAT'}
PART{Syntaxe}
    OBJET2 = 'IPOL' TABLE T ;
PART{Objet}
        OBJET2 est un CHPOINT ou un MCHAML obtenu par interpolation
        a partir d'une table de soustype 'RESULTAT' et d'un temps T.
        Le type de l'objet cree depend du contenu de la table.
PART{Exemple}
* La table de sous-type RESULTAT doit etre initialisee par :
    matab = 'TABLE' RESULTAT ;

* Puis on doit avoir une suite ordonnee d'indices de type FLOTTANT et
* les valeurs pointees doivent etre de meme type (CHPOINT ou MCHAML)
* Par exmple :
    matab. 1.5 = chpo1 ;
    matab. 3. = chpo2 ;

* Et ainsi vous pouvez faire :
    chpo3 = 'IPOL' matab 2. ;

* chpo3 est donc ici egal a l'operation :
    chpo3 = (CHPO1 * (2./3.)) + (CHPO2 * (1./3.))

CHAP{Interpolation d'un NUAGE}
PART{Syntaxe}
    OBJET2 = 'IPOL'  NUA1 OBJET3 | ('GAUSS') ;
        |  'RATIO'  ;
        |  'PID'  (P1) ('ELIM' xtol1);
        |  'GRILL'  ;
PART{Objet}
        OBJET2 est le resultat de l'interpolation d'une fonction
        de plusieurs variables definie par un NUAGE.

      + Pour les mots cles 'GAUSS', 'RATIO' et 'PID', il s'agit d'une
        fonction de n variables a p valeurs scalaires a partir d'un
        nuage de n+p uplets de scalaires (x,f(x)).
        x est de dimension n, f(x) est de dimension p.
        L'OBJET3 est soit un CHPOINT soit un MCHAML dont les noms
        des composantes correspondent aux noms de n composantes du
        nuage. Les composantes du champ et du nuage sont
        necessairement scalaires. OBJET2 est du type de OBJET3.
        ex: nuage de composantes 'X' 'Y' 'Z' 'T' 'F'
        champ argument de composantes 'X' 'Z'
        champ resultat de composantes 'Y' 'T' 'F'

        Deux methodes d'interpolations sont utilisees selon l'option :

        -- Avec les mots cles 'GAUSS' et 'RATIO',
        la methode utilisee pour l'interpolation est celle des
        elements finis diffus au premier ordre. Au point dont on
        veut connnaitre l'image par la fonction, on calcule un
        hyperplan qui minimise la somme ponderee des carres des
        differences des valeurs sur tous les points du nuage.
        La ponderation est obtenue par l'image de la distance entre
        le point et le noeud par la fonction de ponderation
        gaussienne (exp(-x**2)) ou rationelle (1/(1+x)).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ISOV [Post-traitement Analyse]
Operateur ISOVALEUR
------------------- @ISOSURF

MAIL1 = 'ISOV' CHAM1 | ('EGAL')  | VAL1 ;
        |  'EGINFE'  |
        |  'EGSUPE'  |

Objet :

L'operateur ISOVALEUR permet d'obtenir un maillage MAIL1
correspondant aux lieux geometriques ou un champ par element CHAM1
prend une valeur donnee VAL1, ou est inferieur (resp. superieur)
ou egal a VAL1 (mots-clés 'EGINFE' (resp. 'EGSUPE')).

Commentaire :

  MAIL1 : Maillage (type MAILLAGE) representant l'isovaleur.

  CHAM1 : Champ par element (type MCHAML) dont on veut calculer
        une isovaleur.

  VAL1 : Valeur (type FLOTTANT) de l'isovaleur voulue.

Note :

  Pour l'instant, l'operateur ne fonctionne que si le maillage
  sous-jacent a CHAM1 est constitue des elements lineaires :
  POI1, SEG2, TRI3, TET4, CUB8.

  Les options EGINFE et EGSUPE ne fonctionnent pas pour les CUB8.

## ISSLEQ [ISS dynamique] (proc)
    procedure ISSLEQ

   ISSLEQ TDON1

Objet :

Procedure pour appliquer la methode lineaire equivalent aux problemes ISS et
aux problemes de propagation des ondes. Le calcul est fait dans le domaine
temporelle.
On peut definir deux types des domaines pour le sol:
- CONSTANTE: sous-domaine non affecté par les iterations;
      l'option à utiliser est 'ISS_COMP_SIMP'.
- ITERATION: sous-domaine affecté par les iterations;
      l'option à utiliser est 'ISS_COMPLET'.

De plus, on peut integrer dans le calcul la presence de la structure
par la sous-table STRUCTURE. Ici on pourrait aussi ajouter les eventuelles
blocages mecaniques à integrer dans le modele sol.

Commentaire :

En entree :

  TDON1 :Table des donnees (type TABLE)
       .'SOL' :sous-table pour definir les
        donnees du profil
        du sol (type TABLE)
        .'ITERATION' :sous table pour la partie du
        sol à iterer (type TABLE)
        .I : couche I (type TABLE)
        .'MAILLAGE' :maillage de la couche I
        (type MAILLAGE)
        .'FRONTIERE' :frontiere de la couche I
        (type MAILLAGE)
        .'MASSE_VOLUMIQUE' :masse volumique de la couche I
        (type FLONNTANT)
        .'POISSON' :coefficient de poisson de la
        couche I (type FLOTTANT)
        .'G_GAMMA' :evolution de la courbe
        caracteristique G/G0-gamma
        (type EVOLUTION)
        .'H_GAMMA' :evolution de la courbe
        caracteristique Eps-gamma
        (type EVOLUTION)
        .'BASE' :frontiere inferieure de la
        derniere couche qui compose
        la stratigraphie (type MAILLAGE)
        a introduire une seule fois pour
        la dernier couche
        .'CONSTANTE' :sous table pour la partie du
        sol à iterer (type TABLE)
        .I : couche I (type TABLE)
        .'MAILLAGE' :maillage de la couche I
        (type MAILLAGE)
        .'FRONTIERE' :frontiere de la couche I
        (type MAILLAGE)
        .'MASSE_VOLUMIQUE' :masse volumique de la couche I
        (type FLONNTANT)
        .'POISSON' :coefficient de poisson de la
        couche I (type FLOTTANT)
        .'AMORTISSEMENT' :amortissement
        couche I (type FLOTTANT)
       .'STRUCTURE' :sous-table pour definir les donnees
        de la structure (type TABLE) (facultatif)
        .'MAILLAGE' :maillage de la structure
        (type MAILLAGE)
        .'RIGIDITE' :rigidité de la structure
        (type RIGIDITE)
        .'MASSE' :masse de la structure
        (type RIGIDITE)
        .'AMORTISSEMENT' :amortissement de la structure
        (type RIGIDITE)
        .'BLOCAGES_MECANIQUES' :tout type des blocages mecaniques
        supplementaires (type RIGIDITE)
       .'PARAMETRES' :sous TABLE pour definir les parametres
        du calcul (type TABLE)
        .'GAMMAO_X' :evolution de l’acceleration selon
        la direction x (type EVOLUTION)
        .'GAMMAO_Y' :evolution de l’acceleration selon
        la direction y (type EVOLUTION)
        .'GAMMAO_Z' :evolution de l’acceleration selon
        la direction z (type EVOLUTION)
        [seulement une des trois evolution
        est necessaire]
        .'POINT' :point de reference (type POINT)
        .'CRITERE' :critere de convergence pour le
        calcul lineaire equivalent (type FLOTTANT)
        (default 0.05)
        .'CHI' :coefficient pour la deformation moyenne
        gamma_m (type FLOTTANT)
        .'F1' :premiere frequence pour modele
        d amortissement de Rayleigh
        (type FLOTTANT)
        .'F2' :premiere frequence pour modele
        d amortissement de Rayleigh
        (type FLOTTANT)
        .'FC' :premiere de coupure du signal
        (type FLOTTANT)
        .'TYPE' :type de frontiere absorbante (LYSMER
        ou WHITE) (type MOT) (defaut LYSMER)
        .'PAR_DEC' :sous-table à donner pour la procedure
        DECONV3D - voir la notice correspondante
        (P_GAM sous-table) (facultatif)
        .'TYPE_CALCUL' : type de calcul ‘ISS_COMPLET’ (type MOT)
        tout le sol est à considere comme
        domaine à iterer. La sous-table
        ITERATION dans la table SOL est
        obligatoire
        type de calcul ‘ISS_COMP_SIMP’ (type MOT)
        une partie du sol est considere
        comme domaine à iterer et une
        partie constante. La sous table
        ITERATION dans la table SOL et la
        sous table CONSTANTE dans la table
        SOL sont obligatoires
[… notice tronquée ; texte complet dans l'archive PCW_24]

## ITER [Langage Base]
    Operateur ITERER

    ITERER BLOC1;

    Objet :

    L'operateur ITERER sert a interrompre l'execution du bloc
REPETER BLOC1.

    Le controle est rendu a l'instruction FIN BLOC1 qui, suivant la
valeur du compteur associe au bloc, reiterera ou non celui-ci.

    Exemple :

    Impression des premiers nombres impairs.

        I=0;
        J= 0;
        AA = MOT ' ER';
        BB= MOT ' NOMBRE IMPAIR EST' ;
        REPETER B1 20;
        I=I+1;
        SI ( (I / 2 * 2 ) EGA I);
        ITERER B1;
        FINSI;
        J=J+1;
        MESSAGE ' LE ' J AA BB I ;
        AA = MOT 'EME';
        FIN B1;

## ITRC [—]
Operateur ITRC

    CHDIST MINTER = ITRC CHOLD CHNEW TOL TAB1 ;

Objet :

L'operateur ITRC calcule, par une methode analytique exacte,
l'intersection entre des segments et les facettes triangulaires d'un
maillage.

Il fournit les distances de connection ainsi que le maillage forme
des points d'intersection.
Cet operateur remplace la procedure @INTERC.

Commentaire :

 en entree :

 CHOLD : coordonnees des points extremites initiales des segments
        (type CHPOINT a 3 composantes)

 CHNEW : coordonnees des points extremites finales des segments
        (type CHPOINT a 3 composantes appuye sur le meme support
        que CHOLD)

 TOL : tolerance (type FLOTTANT)

 TAB1 : table qui doit contenir les parametres suivants en entree

        tab1.<chamx1 |
        tab1.<chamy1 |
        tab1.<chamz1 |
        |
        tab1.<chamx2 |
        tab1.<chamy2 |---> Cf @rmcooro
        tab1.<chamz2 |
        |
        tab1.<chamx3 |
        tab1.<chamy3 |
        tab1.<chamz3 |
        |
        tab1.<cosx  |
        tab1.<cosy  |---> Cf @rmnorm
        tab1.<cosz  |

 en sortie :

 CHDIST : distance de connexion (distance entre point initial du
        segment et le point d'intersection a la facette) ou valeur du
        pas si au cas ou il n'y a pas d'intersection (type CHPOINT).
        Il s'appuie sur le maillage support de CHOLD.

 MINTER : maillage forme des noeuds du maillage support de
        CHOLD intersectes (type MAILLAGE).

 Remarques :

 CHOLD, CHNEW, CHDIST sont des chpoints definis sur un
 maillage reduit qui est forme des noeuds de OMBRE qui n'ont pas encore
 ete interceptes.

 Le maillage cree MINTER est compose d'elements de type POI1.

 Cet operateur remplace la procedure @INTERC.

## JACO [Mathematiques Autres]
 Operateur JACOBIEN

 CHAM = JACOBIEN MODL1

 Objet :

 L'operateur JACOBIEN permet de calculer la valeur absolue des
jacobiens aux points d'integration des elements de l'objet affecte
 ou du modele .

 Commentaire :

 MODL1: objet modele (type MMODEL)

 CHAM : objet resultat (type MCHAML, sous-type SCALAIRE)

## JEU [Mecanique Limites] (proc)
Procedure JEU
------------- DEPI

CHPO1 = JEU RIG1 ;

Objet :

La procedure JEU permet de calculer le second membre correspondant
a un jeu entre deux solides et associe aux relations liant les
degres de liberte de ces solides et traduisant le contact possible.

Commentaires :

RIG1 : objet de type RIGIDITE, de sous-type BLOCAGE, definissant
        les relations imposees aux degres de liberte des solides.

CHPO1 : resultat (type CHPOINT), qu'il convient d'additionner
        au second membre (forces en mecanique) avant d'effectuer
        la resolution.

## JONC [Mecanique Limites]
    Operateur JONCT

    ATTA1 = JONC STRU1 MOT1 LREEL1 ... ( STRU2 MOT2 LREEL2 ... )
        ( STRU3 MOT3 LREEL3 ... ) ( STRU4 MOT4 LREEL4 ... ) ...

    Objet :

    L'operateur JONCT fabrique un objet de type ATTACHE decrivant
la liaison entre plusieurs elements de structure.

    Cette liaison est definie par un nombre quelconque de liaisons
elementaires.

    Commentaire :

    STRUi : element de structure fabrique par l'operateur ELST.
        (type ELEMSTRU)

    MOTi : nom de l'inconnue en un point de STRUi (type MOT),
        a choisir parmi les deplacements UX, UY, ou UZ,
        les rotations RX, RY ou RZ, les forces FX, FY ou FZ,
        les moments MX, MY ou MZ.

    LREELi : liste des coefficients appliques aux points de
        STRUi (autant de coefficients que de points)(type
        LISTREEL).
        Si STRUi comporte un seul point, on peut remplacer
        le LREELi par un FLOTTANT.

## JPMA [—]
Operateur JPMA
        CHE1 = JPMA CHE2 MOD1 LREE1;

      Objet :

      Calcul du potentiel magnetique vecteur en 3D par integration sur les elements d'une geometrie 2D dans le plan XY
      avec une epaisseur donnee selon Z.
      L'integration est faite en multipliant les composantes JX et JY de la densite de courant par la matrice
      contenue dans la liste de reels LREE1. Il faut d'abord creer cette matrice par l'operateur MPMA.

      Commentaire :

        CHE2 densite de courant = un champ par element ayant les composantes JX et JY
        MOD1 modele ou la densite de courant est appliquee
        LREE1 matrice d'interactions entre les elements obtenue par MPMA

      en sortie :

        CHE1 potentiel magnetique vecteur qui est un champ par elements ayant les composantes AX et AY

## JPMM [—]
Operateur JPMM
        LREE2 = JPMM CHE1 MOD1 LREE1;

      Objet :

      Multiplication de chaque ligne d'une matrice (LREE1) par la valeur correspondante d'un champ par element (CHE1).

      Cet operateur est utilise en electromagnetisme afin d'obtenir la matrice sigma*M (sigma = conductivite,
      M = matrice pour calculer le potentiel vecteur magnetique, obtenue par MPMA).

      Commentaire :

        CHE1 un champ par element a une seule composante (typiquement la conductivite)
        MOD1 le modele ou CHE1 est defini
        LREE1 une matrice representee par une LISTREEL (typiquement la matrice pour la calcul du potentiel magnetique vecteur)

      en sortie :

        LREE2 LISTREEL qui represente la matrice en sortie (ligne par ligne)

      Remarques :

      - si CHE1 a plusieurs composantes, une seule est prise en compte (la premiere)

## KBBT [Fluides Resolution]
    Operateur KBBT
    -------------- KMBT DUDW

    SYNTAXE ( EQEX ) : Cf operateur EQEX

      'OPER' 'KBBT' coef <beta> 'INCO' 'UN' 'PRES'

    OBJET :

 L'operateur KBBT discretise les termes Div U et Grad P par une methode
d'elements finis, de sorte que le systeme obtenu reste symetique.

    Commentaires

     coef coefficent multiplicateur
        FLOTTANT
        ou CHPOINT SCAL SOMMET (porosite volumique)
        ou CHPOINT VECT SOMMET (porosite directionnelle)
        ou MOT

     beta parametre de stabilisation pour les elements lineaires
        FLOTTANT ou MOT

     UN Champ de vitesse
        CHPOINT VECT SOMMET ou MOT

     PRES Champ de pression
        CHPOINT SCAL CENTRE ou MOT
        CHPOINT SCAL CENTREP1 ou MOT
        CHPOINT SCAL CENTREP0 ou MOT
        le type doit etre precise dans les options mot cle INCOD

 Un coefficient de type MOT indique que l'operateur va chercher le
 champ dans la table INCO a l'indice MOT.

    Complements d'information :

 Soit le systeme d'equations de type Stokes ou Navier-Stokes regissant
l'ecoulement d'un fluide incompressible et visqueux.

 A U + Grad P = F : equation de quantite de mouvement

 -Div U = 0 : equation de conservation de la masse

 ou U et P sont respectivement la vitesse et la pression
 A est un operateur inversible (en general l'operateur de diffusion/
 convection)

 Dans la formulation variationelle retenue le terme Grad P
est integre par partie ce qui conduit si A est symetrique a un systeme
discretise symetrique (cas Stokes) en ecrivant l'equation de continuite:

   - Div U = 0 .

        t
 | A  -B |(U)  (F)
 |  |( ) =( )
 |-B  0 |(P)  (0)

     t /
 ou B est la matrice  de  | P Div W dv
        |v
        (W fonction test pour la vitesse)

        /
    B est la matrice  de  | q Div V dv
        |v
        (q fonction test pour la pression)

L'operateur KBBT construit donc les matrices elementaires correspondant
aux operateurs B et Bt (seule B est stokee)

 ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
 REMARQUE : Compte tenu du changement de signe de la deuxieme equation
        un eventuel terme source devra etre affecte d'un signe negatif.
 ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  1/ Conditions limites induites :

 En integrant par partie et en utilisant le theoreme de la divergence
 on a :

   / / /
   | W*Grad P dv =  | W P n ds - | P Div W dv
   |v  |s  |v

 L'integrale de surface est omise ce qui conduit a la condition limite
 par defaut :

   /
   | W P n ds = 0  (n normale exterieure)
   |s

 Ceci est a completer des conditions limites induites par d'autres
 operateurs integres par partie.
 Voir l'operateur TOIM pour imposer une valeur non nulle.

  :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
  2/ Si toutes les vitesses normales sont imposees (nulles ou non) sur
     les frontieres, il faut IMPERATIVEMENT imposer la pression en un
     point. C'est le cas pour tout ecoulement d'un fluide incompressible
     en cavite fermee.
 :::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

  3/ Si le coefficient est de type CHPOINT SCAL SOMMET
    (Porosite volumique H) On calcule :

   / / / /
   | W*H*Grad P dv =  | WHP n ds - | P H Div W dv  - | P W Grad H  dv
   |v  |s  |v  |v

  4/ Si le coefficient est de type CHPOINT VECT SOMMET
    (Porosite surfacique ou directionnelle Hi ) On calcule :

   / / / /
   | W*Hi*Grad P dv =  | WHi P n ds - | P Hi Div W dv  - | P W Grad Hi dv
   |v  |s  |v  |v

    Options : (EQEX)

    OPTI INCOD CENTRE
        CENTREP1
        CENTREP0

## KCHA [—]
Opérateur KCHA

       1) CHPO1 = 'KCHA' MODL1 CHAM1 'CHPO' ('QUAF')

       2) CHAM1 = 'KCHA' MODL1 CHPO1 'CHAM' ('QUAF')

 Objet :

 Cet opérateur permet de faire la correspondance entre un CHAMELEM
 constant par élément et un CHAMP-POINT appuyé aux centres des
 éléments.

 | 1ère possibilité : création d'un CHPO centre avec un CHAMELEM |

 Commentaire :

 CHAM1 : Champ par élément (type 'CHAMELEM')

 CHPO1 : Champ par points (type 'CHPOINT')

 MODL1 : Objet modèle décrivant la formulation utilisée (cf MODE)

 'CHPO' : Mot-clef précisant l'opération

 'QUAF' : Mot-clef précisant que le maillage support est un QUAF

 | 2ème possibilité : création d'un CHAMELEM avec un CHPO centre |

 Commentaire :

 CHAM1 : Champ par élément (type 'CHAMELEM')

 CHPO1 : Champ par points (type 'CHPOINT')

 MODL1 : Objet modèle décrivant la formulation utilisée (cf MODE)

 'CHAM' : Mot-clef précisant l'opération

 'QUAF' : Mot-clef précisant le choix du maillage support

 Remarques :

 1. CHAM1 doit être constant par élément et toutes ses composantes
    doivent être de type scalaire.

 2. CHPO1 est de nature 'DIFFUSE'.

 3. En présence du mot-clef 'CHAM', le maillage support du CHAMELEM
    généré sera le maillage QUAF. En son absence, c'est le maillage
    de base (par ex. QUA4) qui sera pointé par le CHAMELEM.
    L'usage de cette option dépend de l'opérateur auquel on destine
    le CHAMELEM à créer.

## KCHT [Mathematiques Autres]
    Operateur KCHT
    -------------- DOMA

    CHPO1 = KCHT | MOD1 | MOT1 MOT2 ('VERIF') ('COMP' MOTi) ...
        | TAB1 |
        ... | FLOT1 | (CHPO2 ... CHPOn);
        | VEC1  |

    Objet :

    Cree un CHPOINT s'appuyant sur un des supports geometriques (SPG)
    du modele ou d'une table DOMAINE.

    Commentaires :

     MOD1 : objet MMODEL type 'NAVIER_STOKES' ou 'DARCY'

     TAB1 : TABLE DOMAINE

     MOT1 : | 'SCAL' |  MOT2 : | 'SOMMET'  |
        | 'VECT' |  | 'FACE'  |
        | 'CENTRE'  |
        | 'CENTREP1' |
        | 'MSOMMET'  |

     'VERIF' : Mot cle indiquant que l'on veut un echo des composantes
        initialisees

     'COMP' : Mot cle indiquant que l'on va nommer les composantes
        MOTi : noms que l'on affecte aux composantes

     FLOT1 : valeur initiale donnee au CHPOINT si MOT1 = 'SCAL'

     VEC1 : valeur initiale (de type POINT) donnee au CHPOINT
        si MOT1 = 'VECT'

     CHPO2 : CHPOINT d'initialisation
      ... Les valeurs des points de CHPOn contenus dans le support
     CHPOn geometrique (DOMAINE) seront prises comme valeurs
        initiales et surchageront le cas echeant FLOT1 ou VEC1
        et CHPOn-1

     CHPO1 : CHPOINT resultat

    Complements d'information :

1/ Le CHPOINT est une collection de valeurs associees a des points.
    On peut associer a chaque point une ou plusieurs valeurs (SCALAIRE,
    VECTEUR etc..). Les champs representes par un CHPOINT peuvent etre
    continus ou discontinus ou bien encore pour les champs vectoriels
    defini par leur flux. On a choisi dans le cadre du domaine
    d'application lie a la mecanique des fluides de pouvoir representer
    ces trois types de champ a l'aide de la meme structure de CHPOINT.
    La difference n'intervient que par les points sur lesquels s'appuie
    le CHPOINT. Il y a donc quatre classes de points distinguees
    uniquement par leur localisation. Ce sont les points SOMMET,FACE,
    CENTRE ou CENTREP1 (3 points definissant une pression lineaire en
    2D pour chaque element, 4 points en 3D),

    Les SPG (support geometrique des espaces discrets) des CHPOINTs
    crees par KCHT sont pris dans cette liste
    Une verification de la coherence consiste a comparer les SPG
    des CHPOINTs et ceux du modele.

2/ On peut se servir de KCHT pour affecter le bon SPG a un CHPOINT.

## KCOT [Fluides Resolution]
   Operateur KCOT

        CHPC = KCOT OBJDOM ;

    OBJET : Cree un CHAMPOINT CENTRE contenant les informations
        decrites ci dessous, sur les elements du domaine.

    OBJDOM : TABLE de SOUSTYPE DOMAINE

    AVIS IMPORTANT ;

    Ces informations sont destinees aux operateurs de discretisation
    et sont rangees dans un ordre particulier.

Les dimensions du tableau sont : (DIME NBEL) DIME=8 en 2D
        DIME=13 en 3D
et il contient :

 pour un SEG2 la longueur de l'element (XML) et la matrice P(2,2) en 2D
        P(3,3) en 3D
 pour un TRI3 XML,XMH,AJ1/XML,AJ2/XML, et la matrice P(2,2) en 2D
        P(3,3) en 3D
 pour un QUA4 IDEM
 pour un CUB8 XML XMH XME et la matrice P
 pour un PRI6 IDEM

  MATRICE P
      LA MATRICE DE ROTATION DU REPERE GLOBALE VERS LE REPERE LOCAL
  DEFINI PAR DEUX OU TROIS POINTS PRIS DANS XYZ SUIVANT QU'ON EST
  EN 2D OU EN 3D
  ON PREND P1 P2 ET PNP

    U TEL QUE T SOIT DIRIGE SUIVANT P1P2 V TOURNE VERS
    . .V P1PNP ET U = T VECTORIEL V
    . .
    . . __ __
(P1). . . . .T (P2)  | tx ty tz  |
        |  |
 ON A ALORS WL= P WG  P  = | vx vy vz  |
        |  |
        | ux uy uz  |
        |__  __|

## KCTR [Fluides Resolution]
  Operateur KCTR

Remplace par l'option 'CENTRE' de l'operateur DOMA.

## KDIA [Fluides Resolution]
Directive KDIA

        KDIA RV ;

OBJET :

  Cet operateur construit une table de sous type KIZD contenant les
  diagonales et la place dans la table RV a l'indice KIZD.

  RV table de sous-type EQEX

## KDME [Fluides Resolution]
Operateur KDME

 OBJET : Cree un CHAMPOINT CENTRE contenant le diametre max des
        elements du domaine

 SYNTAXE : CHPC = KDME OBJDOM ;

        OBJDOM : TABLE de SOUSTYPE DOMAINE

## KDMI [Fluides Resolution]
Operateur KDMI

      CHPC = KDMI OBJDOM ;

 OBJET : Cree un CHAMPOINT CENTRE contenant le diametre min des
        elements du domaine

   OBJDOM : TABLE de SOUSTYPE DOMAINE

## KDOM [Fluides Resolution]
 Operateur KDOM

Remplace par l'operateur DOMA.

## KENT [Mecanique Modele]
Operateur KENT

Objet :

L'operateur KENT calcule les matrices de raideur necessaire a
l'etude des vibrations d'une structure situee dans un repere
non galileen caracterise par un champs de rotation
(elements BARR, POUT, TUYAU, COQUE, MASSIF en 3D,
        CERC et MASSIF en 2D Fourier).
Cet operateur permet de realiser des calculs dans un repere tournant.

 RIG1 = KENT | 'CENTRIFUGE' | MODL1 MAT1 VEC1
        | 'EULER'  |

  Commentaire :

 RIG1 : Matrice de raideur (type RIGIDITE)

 MODL1: Modele (objet MMODEL)

 MAT1 : Caracteristiques materiau (objet MCHAML)

 VEC1 : Vecteur vitesse de rotation (option CENTRIFUGE)
ou vecteur variation de vitesse de rotation (option EULER) (objet POINT)
 Ce vecteur est optionnel en mode de Fourier.
 Dans ce cas, si un vecteur est donne, seule la composante suivant Oz
 est prise en compte. Si aucun vecteur n'est donne, le vecteur (0. 1.) est
 pris par defaut.

 Option 'CENTRIFUGE': La matrice RIG1 represente la raideur centrifuge
        (les forces centrifuges etant suiveuses)

 Option 'EULER': La matrice RIG1 represente la raideur d'Euler
        (les forces d'Euler qui apparaissent quand le vecteur rotation
        n'est plus constant en module et/ou direction etant des forces
        suiveuses ).

## KEPSILON [Fluides Resolution] (proc)
   Procedure KEPSILON

   SYNTAXE ( EQEX ) : Cf operateur EQEX

   'OPER' 'KEPSILON' RO UN MU DT (RGB TN) 'INCO' 'KN' 'EN'

   OBJET :

Cette procedure calcule la viscosite effective (tourbillonnaire +
moleculaire) obtenue par la resolution en transitoire (un pas de temps)
d'un modele K-Epsilon. Le resultat est place dans la table 'INCO' a
l'indice 'MUF' pour la viscosite dynamique effective (kg/m/s).
Pour la version standard le desequilibre (Production/Dissipation) est
limite a 10 (Limitation proposee par Menter).
Precautions: L'algorithme ne converge pas (sans qu'il diverge) lorsque
l'allongement des mailles du maillage est superieur a 20!!

   Commentaires

   RO Densite
        FLOTTANT ou MOT

   UN Champ de vitesse
        CHPOINT VECT SOMMET ou MOT

   MU Viscosite dynamique (Kg/m/s)
        FLOTTANT ou MOT

   DT Pas de temps
        FLOTTANT ou MOT

   RGB Coefficient du terme de flottabilite
        VECTEUR ou MOT

   TN Champ de temperature
        CHPOINT SCAL SOMMET ou MOT

Un coefficient de type MOT indique que l'operateur va chercher le
coefficient dans la table INCO a l'indice donne.

Les options (parametres) de cette procedure doivent se trouver dans un
LISTMOTS a l'entree 'ALGO_KEPSILON' de la procedure RV.
ex : RV.'ALGO_KEPSILON'= MOTS 'Bw' 'Cnu';
En l'absence de cette entree les valeurs par defaut sont prises.

La liste des Options/Parametres est : IMPR,RNG,Filtre,Bw,Cnu,Nut,Fi,
M2M,CSTE,Ret,KL,KLbr,Chien,Sharma,Jones,Lam
Les options par defaut sont : Nut et le modele k - epsilon standard.

IMPR: permet d'afficher les options utilisees.

RNG : modele RNG k - epsilon.

Filtre : Modele K-epsilon filtre. L'echelle de longueur est
        filtree a une valeur precisee dans RV.'INCO'.'Echl'. Ce modele
        permet de mieux capter des instationarites ou des instabilites
        a grande echelle (de taille superieure a celle du filtre). On
        peut prendre comme echelle de longueur la taille des elements
        du maillage.

Bw : declenche une condition de realisabilite sur les contraintes de
      cisaillement maximum. On verifie que (u'v')/k < 0.3 (Bradshaw)
      DEFAUT = FAUX.

Cnu : La 'constante' Cnu est reliee au rapport Ksi=(Nut P)/epsilon :
      Cnu = F(1/Ksi) (Voir Rodi)
      Pour Ksi = 1 Cnu=0.09.
      DEFAUT = FAUX.

Nut : Les variables de resolution intermediaires sont Teta et Nut
      DEFAUT = VRAI.

Fi : Les variables de resolution intermediaires sont Teta et Fi
      DEFAUT = FAUX.

M2M : Constantes de Mohammadi et Medic.
      DEFAUT = FAUX.

CSTE: Les constantes du model sont lues dans la table INCO aux entrees
      'cnu' 'c2' 'sgk' 'sge' La constante c1 en est deduite
      DEFAUT = FAUX.

KL : Modele K-L. L'echelle de longueur doit etre specifiee dans la
      table 'INCO' (entree 'INCO'.'Echl'). Numeriquement ce modele est
      obtenu en remplaçant l'equation (EDP) sur epsilon par
      epsilon = k**1.5 / L. Il est necessaire de renseigner le modele
      comme si on resolvait le modele K-epsilon. La condition limite
      sur epsilon doit verifier l'equation ci-dessus

KLbr: Modele K-L bas Reynolds. C'est le modele de Wolfshtein (1967) et
      Yap (1987). A la place de l'echelle de longueur il faut donner la
      distance a la paroi: indice 'dparoi' (CHPOINT SCAL SOMMET) dans
      la table INCO. Les conditions limites sont U=0,K=0 et Epsilon=0 a
      la paroi. La premiere maille doit se trouver a un y+ < 1.
      Voir le jeux de donnee canalKLbr.dgibi

Chien: Modele k-epsilon Bas-Reynolds de Chien. Ce modele
      necessite la donnee de la distance a la paroi:
      entree 'INCO'.'dparoi' (meme support que k ou epsilon) et le
      calcul de y+ (entree 'INCO' 'yplus'). Cette derniere entree
      doit etre recalculee a chaque pas de temps via une procedure.
      Les conditions limites et les contraintes de maillage pres de la
      paroi sont les memes que precedemment.
      Voir le jeux de donnee canal-Chien.dgibi

Sharma: Modele k-epsilon Bas-Reynolds de Launder Sharma. Ce modele ne
      necessite aucune donnee supplementaire ce qui presente un
      avantage certain.
      Les conditions limites et les contraintes de maillage pres de la
      paroi sont les memes que precedemment.
      Voir le jeux de donnee canal-Sharma.dgibi

Jones: Modele k-epsilon Bas-Reynolds de Jones-Launder Sharma. Ce modele
      est quasiment identique au precedent aux valeurs des constantes
      pres.

 Lam: Modele k-epsilon Lam et Bremhorst (en test)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## KFCE [Fluides Resolution]
  Operateur KFCE

Remplace par l'option 'FACE' de l'operateur DOMA.

## KFPA [Multi-physique Multi-physique]
   Operateur KFPA
   -------------- FPAL

        AK = KFPA NU YP UET NORM ROG RAP ;

OBJET :

Calcule la vitesse de depot d'aerosols en regime turbulent

COMMENTAIRES :

AK vitesse de depot des particules (m/s) CHPOINT SCAL CENTRE PAROI

NU viscosite du gaz (m2/s) FLOTTANT

YP epaisseur de la couche limite gaz (m) FLOTTANT

UET vitesse de frottement du gaz (m/s) CHPOINT SCAL CENTRE PAROI

NORM normale sortante a la paroi (m) CHPOINT VECT CENTRE PAROI

ROG masse volum. part. x gravite (kg/m2s2) POINT

RAP rayon des particules (m) FLOTTANT

Remarques :

- UET est calcule par FPU (fonctions de paroi pour la vitesse)
- NORM est calcule par DOMA sur tout le domaine, puis reduit sur la
  paroi par KCHT.
- YP est a priori le meme que pour FPU, meme si on peut le choisir
  different.
- AK est un coefficient d'echange pour la masse, il est ensuite
  donne a l'operateur ECHI qui realisera la condition limite de depot
  pour l'equation de concentration (oper. TSCA).

## KFPT [Thermique Modele]
    Operateur KFPT

    Syntaxe :

      H = KFPT $mod RO MU CP LB UET YP

   DOMAINE D'APPLICATION : Thermo-hydraulique turbulente.

    OBJET :

   Calcul de H : Coefficient d'echange thermique d'origine convective
        issu des fonctions de paroi en thermique.
   H coefficient d'echange CHPOINT SCAL SOMMET

    UTILISATION :

   La vitesse de frottement UET est en general issu de l'operateur FPU.
   Choisir de preference une valeur de YP (distance a la paroi)
   telle que sa valeur adimentionnee Y+ soit comprise entre 30 et
   300 lors des calculs.

    COEFFICIENTS AUTORISES :

$DOM Modele NAVIER_STOKES

RO Densite FLOTTANT ou CHPOINT SCAL SOMMET

MU Viscosite dynamique moleculaire FLOTTANT ou CHPOINT SCAL SOMMET

CP Chaleur specifique FLOTTANT ou CHPOINT SCAL SOMMET

LB Conductivite thermique FLOTTANT ou CHPOINT SCAL SOMMET

UET Vitesse de frottement CHPOINT SCAL SOMMET

YP Distance la paroi FLOTTANT

## KHIS [Fluides Modele]
    Operateur KHIS

     TAB1 = KHIS nom1 comp1 geom1
        nom2 comp2 geom2

     Objet :

     Cree une table (de sous-type KHIS) pour les historiques temporels
     de EQEX (sauvegarde de la valeur de grandeurs en certains points)

     Commentaires :

     nom1 nom2 ... : nom (type MOT) de l'inconnue se trouvant dans la
        table 'INCO'

     comp1 comp2 ... : numero (type ENTIER) de la composante si
        l'inconnue est vectorielle (1 par defaut)

     geom1 geom2 ... : objets MAILLAGE (de type POI1) contenant la liste
        des noeuds

     Dans TAB1, une table contenant les symboles pour l'operateur
     DESSIN est creee et placee a l'indice 'TABD'. L'ordre des symboles
     est le suivant :
        *.1='MARQ PLUS'
        *.2='MARQ CROI'
        *.3='MARQ LOSA'
        *.4='MARQ CARR'
        *.5='MARQ TRIA'
        *.6='MARQ TRIB'
        *.7='MARQ ETOI'

     La frequence de sauvegarde est geree par la directive NISTO de
     l'operateur EQEX.

     Exemple :

     lh = elem TABDOM.SOMMET POI1 (lect 1 pas 10 101) ;
     lh1 = (poin proc (1 1) ) et (poin proc (0 1) ) ;

     his= khis 'UN' 1 lh
        'UN' 2 lh
        'KN' lh1
        'EN' lh1;
     rv.'HIST'=his ;

     ... exec rv ; ...

     dessin his.'TABD' his.'1UN' ;
     dessin his.'TABD' his.'2UN' ;
     dessin his.'TABD' his.'KN' ;
     dessin his.'TABD' his.'EN' ;

$$$$

## KLNO [Fluides Resolution]
 Operateur KLNO

        CHPS = KLNO TABDOM CHPC ;

 Objet : transforme un CHAMPOINT CENTRE en un CHAMPOINT SOMMET

  TABDOM : Table DOMAINE contenant le support geometrique de CHPC
  CHPC : CHAMPOINT CENTRE
  CHPS : CHAMPOINT SOMMET

COMPLEMENTS D'INFORMATION :

 On calcule A * TE (La matrice est diagonale)
        - A aire de l {l{ment
        - TE valeur de l'inconnue sur l'{l{ment

Pour avoir une approximation plus pr{cise, on peut utiliser un
module de r{solution de type A1 A2 ou A3 suivant le cas.
On peut {ventuellement imposer des valeurs.

## KLOP [Mathematiques Autres]
Operateur KLOP

        KLOP ind RV ;

Objet : execute un operateur de la liste des operateurs d'une table
        de type EQEX et se trouvant au rang ind.

RV Table de type EQEX
ind rang de l'operateur dans la liste (LISTOPER)

## KMAB [Fluides Resolution]
    Operateur KMAB
    -------------- DUDW EQEX

    SYNTAXE ( EQEX ) : Cf operateur EQEX

      'OPER' 'KMAB' coef <beta> 'INCO' 'UN' 'PRES'

    OBJET :

 L'operateur KMAB discretise le terme Div U du systeme d'equations de
Stokes (ou Navier-Stokes) par une methode d'elements finis.

    Commentaires

     coef coefficent multiplicateur
        FLOTTANT
        ou CHPOINT SCAL SOMMET (porosite volumique)
        ou CHPOINT VECT SOMMET (porosite directionnelle)
        ou MOT

     beta parametre de stabilisation pour les elements lineaires
        FLOTTANT ou MOT

     UN Champ de vitesse
        CHPOINT VECT SOMMET ou MOT

     PRES Champ de pression
        CHPOINT SCAL CENTRE ou MOT
        CHPOINT SCAL CENTREP1 ou MOT
        CHPOINT SCAL CENTREP0 ou MOT
        le type doit etre precise dans les options mot cle INCOD

 Un coefficient de type MOT indique que l'operateur va chercher le
 champ dans la table INCO a l'indice MOT.

    Complement d'information :

  1/ La formulation variationnelle est :

   /
   | q*Div U dv =
   |v

  2/ Si toutes les vitesses normales sont imposees (nulles ou non) sur
     les frontieres, il faut IMPERATIVEMENT imposer la pression en un
     point. C'est le cas pour tout ecoulement d'un fluide incompressible
     en cavite fermee.

  3/ Si le coefficient est de type CHPOINT SCAL SOMMET
    (Porosite volumique H) On calcule :

   / / /
   | q*Div(H U) dv = | q H Div U dv  + | q U Grad H  dv
   |v  |v  |v

  4/ Si le coefficient est de type CHPOINT VECT SOMMET
    (Porosite surfacique ou directionnelle Hi ) On calcule :

   /
   | q*Div((HU)i) dv
   |v

    Options : (EQEX)

    OPTI INCOD CENTRE
        CENTREP1
        CENTREP0

## KMAC [Fluides Resolution]
Operateur KMAC

 OBJET : Cet operateur est remplace par KMAB

## KMBT [Fluides Resolution]
   Operateur KMBT
   -------------- KBBT DUDW

   SYNTAXE ( EQEX ) : Cf operateur EQEX

     'OPER' 'KMBT' coef <beta> 'INCO' 'UN' 'PRES'

   OBJET :

L'operateur KMBT discretise le terme Grad P de l'equation de
Navier-Stokes par une methode d'elements finis.

   Commentaires

    coef coefficent multiplicateur
        FLOTTANT
        ou CHPOINT SCAL SOMMET (porosite volumique)
        ou CHPOINT VECT SOMMET (porosite directionnelle)
        ou MOT

    beta parametre de stabilisation pour les elements lineaires
        FLOTTANT ou MOT

    UN Champ de vitesse
        CHPOINT VECT SOMMET ou MOT

    PRES Champ de pression
        CHPOINT SCAL CENTRE ou MOT
        CHPOINT SCAL CENTREP1 ou MOT
        le type doit etre precise dans les options mot cle INCOD

Un coefficient de type MOT indique que l'operateur va chercher le
champ dans la table INCO a l'indice MOT.

   Complement d'information :

 1/ Conditions limites induites :

Dans la formulation variationelle retenue le terme Grad P est integre
par partie. En utilisant le theoreme de la divergence on a :

  / / /
  | W*Grad P dv =  | W P n ds - | P Div W dv
  |v  |s  |v

L'integrale de surface est omise ce qui conduit a la condition limite
par defaut :

  /
  | W P n ds = 0  (n normale exterieure)
  |s

Ceci est a completer des conditions limites induites par d'autre
operateurs integres par partie.
Voir l'operateur TOIM pour imposer une valeur non nulle.

 2/ Si le coefficient est de type CHPOINT SCAL SOMMET
   (Porosite volumique H) On calcule :

  / / / /
  | W*H*Grad P dv =  | WHP n ds - | P H Div W dv  - | P W Grad H  dv
  |v  |s  |v  |v

 3/ Si le coefficient est de type CHPOINT VECT SOMMET
   (Porosite surfacique ou directionnelle Hi ) On calcule :

  / / / /
  | W*Hi*Grad P dv =  | WHi P n ds - | P Hi Div W dv  - | P W Grad Hi dv
  |v  |s  |v  |v

   Options : (EQEX)

   OPTI INCOD CENTRE
        CENTREP1

## KMCT [Fluides Resolution]
Operateur KMCT

Objet : Cet operateur est remplace par KMBT

## KMF [Mathematiques Autres]
Operateur KMF

    OBJ3 = KMF OBJ1 OBJ2 <'TRANS'> ;

Objet : Cet operateur calcule le produit d'un objet MATRIK
        et d'un CHPOINT

 OBJ1 : objet MATRIK
 OBJ2 : objet CHPOINT
 OBJ3 : objet CHPOINT resultat

 La presence du mot cle 'TRANS' indique que le produit se fait
 avec la matrice transposee.

## KMTP [Multi-physique Multi-physique]
 Operateur KMTP

      MCHPOI = KMTP MATRIK B ;

        T
Objet : CALCUL DE C P

  MATRIK MATRICES ELEMENTAIRES DE LA DIVERGENCE (ALIAS "C")
        (objet de type MATRIK cree par KMAC)
  B CHAMP DE PRESSION (SCAL CENTRE) SUR LA ZONE PRESSION

  EN SORTIE :
        T
  MCHPOI CONTIENT LE GRADIENT DE PRESSION C P (VECT SOMMET)

## KNRF [Fluides Resolution]
     Operateur KNRF

Cet operateur a ete remplace par l'operateur DOMA.
(options NORMALE, SURFACE, ORIENTAT)

## KONV [Fluides Resolution]
     Operateur KONV

     OBJET :

 I Formulation Volume Finis (OPTI VF) :

      Discretise l'operateur de convection par des schemas volumes finis
    Il calcule un champ point FACE qui represente
    le flux de chaque arete du maillage selon 3 schemas.
    On ecrit le flux dans l'increment KIZG.

     SYNTAXE 1 : KONV VNF VNC option;
        VNF = U calcule aux sommets (par ksof)
        VNC = U calcule aux centres (par knol)
        Option = 'upwind' | 'quick' | 'muscl'

     SYNTAXE 2 : en utilisant EQEX
        RV = EQEX TABDOM ALFA .. ITMA ..
        'ZONE' MOD1 'OPER' 'KONV' VNF VNC 'INCO' 'TN'
        CLIM 'TN' TIMP ENTREE ... ;

        on met l'option dans klop : klop ind rv 'option' ;

   Erreur possible dans le calcul de DT si VN est petit changer EPSILON

      COMMENTAIRES :

Le flux est evalue sur chaque maille par : FI = VNF TK LGR
ou TK est la temperature sur la face K calculee de facons differentes selon
les schemas a partir des temperatures sur les mailles connexes: TIM ,TI ET TIP.
(Voir le rapport pour le choix de ces trois temperatures)

-Schema UPWIND :

        TK = TI

-Schema QUICK :

        TK = (TI+TIP)/2 + (TIM+TIP-2*TI)/8

-Schema MUSCL :

        TK = TI + DELTA_I/2

ou DELTA_I est la pente entre deux mailles :

        GAMMA_I = SIGNE (TIP-TI)
        DELTA_I = GAMMA_I * MAX (0,MIN(GAMMA_I*(TIP-TI),GAMMA_I*(TI-TIM)))

Le bilan des flux precedents est fait dans l'operateur AVCT

 II Formulation Element Finis (OPTI EF ou EFM1) :

      Discretise l'operateur de convection en Element Finis.
   Suivant l'option l'operateur est traites sous forme
  conservative ou non conservative.

    SYNTAXE - EQEX Cf operateur EQEX

    'OPER' 'KONV' ROC UN LAM 'INCO' 'TN' :

     1/ Formulation non conservative

        roc ( u Grad T )

     2/ Formulation conservative

        Div ( roc u T )

    Commentaires :

     roc capacite calorique (J/M**3/°C)
        FLOTTANT ou CHPOINT SCAL CENTRE ou CHPOINT SCAL SOMMET ou MOT
     lam conductivite thermique (W/M/°C)
        cette donnee est necessaire pour l'evaluation
        du Peclet de maille. En general c'est le coefficent
        de l'operateur LAPN. Si c'est operateur est absent
        mettre lam=0.
        FLOTTANT ou CHPOINT SCAL CENTRE ou CHPOINT SCAL SOMMET ou MOT
     un Champ de vitesse transportant
        CHPOINT VECT SOMMET ou MOT
     tn Champ de temperature
        CHPOINT SCAL SOMMET ou MOT

 Un coefficient de type MOT indique que l'operateur va chercher le
 coefficient dans la table INCO a l'indice MOT.

    Options : (EQEX)

 La discretisation des termes de convection peut etre :

 centree OPTION CENTREE
 decentree OPTION SUPG
 decentree avec capture de choc OPTION SUPGCC Option par defaut
 Crank Nicholson generalise OPTION CNG
 (ordre 4 en temps)

 Formulation non conservative OPTION NOCONS Option par defaut
 Formulation conservative OPTION CONS

 Formulation EF OPTION EF

 III Discretisation des Equations d'Euler

 IIIa : gaz parfait mono-constituent polytropique

 Discretisation en VF "cell-centered" des equations d'Euler pour un gaz
 parfait mono-constituent polytropique

 Inconnues:

 densite, quantite de mouvement (qdm), energie totale par unite de volume
 (variables conservatives)

 ou

 densite, vitesse, pression (variables primitives)

 On peut calculer:

 IIIa.1. Le flux numerique
 IIIa.2 Le residu
 IIIa.3 La matrice jacobienne du residu par rapport aux variables
        conservatives
 IIIa.4 La matrice jacobienne du residu par rapport aux variables
        primitives
 IIIa.5 La matrice de preconditionnent bas Mach par rapport aux
        variables conservatives
 IIIa.6 La matrice de preconditionnent bas Mach par rapport aux
        variables primitives
 IIIa.7 La contribution de quelque condition limite au residu et
        a la matrice jacobienne

 IIIa.1 et IIIa.2 Le flux numerique et le residu

 RCHPO1 RFLOT1 = 'KONV' 'VF' 'PERFMONO' MOT1 MOT2 MOD1 LMOT1 MCHAM1
        MCHAM2 MCHAM3 MCHAM4 (CHPO5 CHPO6) (MAIL1) ;

 ENTRÉES

 MOT1 : objet de type MOT
        Il vaut 'RESI' si on veut calculer le residu
        Il vaut 'FLUX' si on veut calculer le flux
[… notice tronquée ; texte complet dans l'archive PCW_24]

## KOPS [Mathematiques Autres]
 Operateur KOPS

 RES = KOPS CHP1 'MOTCLE' CHP2 ;

 ou

 RES = KOPS CHP1 'MOTCLE' TABD ;

 Objet :

 Effectue des operations arithmetiques entre deux CHPOINTs
 ou un CHPOINT et un flottant.
 Calcule le gradient ou le rotationnel d'un CHPOINT
 Calcule le produit matrice vecteur entre un objet MATRIK et un
 CHPOINT
 Calcule le produit entre un objet MATRIK et un FLOTTANT

 RES , CHP1 CHP2 CHPOINT et/ou FLOTTANT
 TABD objet MODEL 'NAVIER_STOKES'
 'MOTCLE' a choisir dans la liste suivante :

        '*' multiplication de deux CHPOINT
        de type SCALAIRE ou VECTEUR composante par
        composante
        le resultat est un CHPOINT SCALAIRE ou
        VECTEUR

        '/' idem precedent pour la division

        '+' idem precedent pour l'addition

        '-' idem precedent pour la soustraction

        '|<' Borne inferieurement un CHPOINT par un flottant.
        OBJ1 = KOPS OBJ2 '|<' OBJ3;
        OBJ1,OBJ2 CHPOINT OBJ3 FLOTTANT

        '>|' Borne superieurement un CHPOINT par un flottant.
        OBJ1 = KOPS OBJ2 '>|' OBJ3;
        OBJ1,OBJ2 CHPOINT OBJ3 FLOTTANT

        'GRAD' calcule le Gradient d'un CHPOINT scal sommet.
        Le resultat est un CHPOINT vect centre.
        Ne marche que pour les discretisations LINE,MACRO

        'GRADS' calcule le Gradient d'un CHPOINT scal sommet.
        Le resultat est un CHPOINT vect sommet.
        Marche pour toutes les discretisations LINE,MACRO
        et QUAF.

        'ROT ' calcule le Rotationel d'un CHPOINT vect sommet
        le deuxieme argument doit etre une table domaine
        ex : rt2d= kops un 'ROT' $mt ;
        Cf exemple 1 ci-dessous

        'CLIM' N (N is an INTEGER)
        surcharge dans CHP1 les valeurs de CHP2
        N=0 les noeuds correspondants sont mis a 0.
        N=1 " " " " a 1.e30
        N=2 " " " " a (CHP2*1.e30)
        N=3 " " " " a CHP2
        Si l'entier N est precede du signe -, les composantes
        de CHP2 doivent etre identiques a celles de CHP1
        sinon CHP1 n'est pas surcharge.
        Si l'entier N est positif, on teste sur les composantes
        UX UY UZ

        'MULT' realise le produit matrice vecteur entre un objet
        MATRIK et un CHPOINT ou un FLOTTANT
        ex : p1=kops ma1 'MULT' un ;
        Cf exemple 2 ci-dessous : calcul de la pression
        par une methode de penalisation.

        'RIMA' permet le passage d'un objet matrik a un objet
        rigidite et vice-versa

        Example
        rig1 = KOPS RIMA matrik1 ;
        matrik2 = KOPS RIMA rig2 ;
        rig1, rig2 objet de type rigidite
        matrik2, matrik1 objet de type matrik

        Si on veut forcer la création d'un objet RIGIDITE non
        symétrique, on indique le mot-clé 'NSYM'
        Example
        rig1 = KOPS RIMA matrik1 'NSYM' ;

        'MATIDE' permet de creer un objet RIGIDITE ou MATRIK identite
        mat1 = kops lmot1 geo1 ('MATRIK') ;
        ou
        lmot1 = liste de noms des inconnues (LISTMOTS)
        geo1 = support geometrique des inconnues
        (MAILLAGE)
        mat1 = RIGIDITE ou MATRIK identite

        'MATDIAGO' permet de creer un objet RIGIDITE (ou MATRIK)
        diagonal
        mat1 = kops 'MATDIAGO' chpo1 ('MATRIK') ;
        ou
        chpo1 = valeurs des termes diagonaux (CHPOINT)
        mat1 = RIGIDITE (ou MATRIK) diagonal
        Pour les objets RIGIDITE, utilisez plutot
        l'operateur 'MANU' 'RIGI'.

        'CHANINCO' mot clef obsolete. Voir l'operateur CHAN
        mot clef 'INCO'.

        'NINCDUPR' change les noms d'inconnues duales d'une
        matrice (ou d'un chpoint dual) afin qu'ils
        soient identiques aux noms d'inconnues
        primales
        |mat2 | = 'KOPS' 'NINCDUPR' |mat1 | ;
        |chpo2|  |chpo1|
        mati sont de type RIGIDITE ou MATRIK

        'NINCPRDU' change les noms d'inconnues duales d'une
        matrice (ou d'un chpoint dual) afin qu'ils
        correspondent aux noms d'inconnues primales
        suivant la correspondance conventionnelle
        de Castem
        (ex: 'UX' <-> 'FX', 'T' <-> 'Q', etc...)
        |mat2 | = 'KOPS' 'NINCPRDU' |mat1 | ;
        |chpo2|  |chpo1|
        mati sont de type RIGIDITE ou MATRIK

        'TRANSPOS' transpose une matrice (type MATRIK ou RIGIDITE)
        mat2 = 'KOPS' 'TRANSPOS' mat1 ;

        'EXTRNINC' mot clef obsolete. Voir l'operateur EXTR
        mot clef 'COMP' et 'COMP' 'DUAL'

        'EXTRINCO' mot clef obsolete. Voir l'operateur EXTR
[… notice tronquée ; texte complet dans l'archive PCW_24]

## KP [Mecanique Modele]
Operateur KP

 Cas 1 :

  RIG1 = KP  MODL1 | CHPO1 | ( 'FLAM' ) ( 'ASYM' ) ;
        | CHAM1 |

 Cas 2 :

  RIG1 = KP MODL1 RG (VEC1) ( 'FLAM' ) ( 'ASYM' ) ;

Objet :

L'operateur KP calcule la matrice de correction des forces associee a la
linearisation des actions de pression autour d'une position d'equilibre.
Une valeur de pression positive designe une force de pression ayant le
meme sens que la normale locale.

Cas 1 : On calcule la rigidite associee au changement de la direction de
------- la normale ainsi que de l'aire de surface soumise a un champ de
        pression donne.

Cas 2 : On calcule la rigidite associee a la variation de la valeur de
------- pression "vue" par la structure quand elle bouge dans un champ de
        pression a gradient lineaire "impose", qui ne depend pas
        de mouvement de la structure (par exemple pression hydrostatique).
        Actuellemnt cette option est disponible seulement pour les
        elements COQ3, DKT, DST et COQ4.

  Commentaire :

  MODL1 : Objet modele (type MMODEL ).

  CHPO1 : champ de pression (type CHPOINT).

  CHAM1 : champ de pression (type MCHAML).

 'FLAM' : mot-cle necessaire si l'on veut utiliser la matrice
        pour faire une analyse de flambage (facultatif).

 'ASYM' : mot-cle necessaire si l'on veut calculer la matrice
        asymetrique (facultatif).

  RG : module du gradient lineaire de la pression (type FLOTTANT).
        Par exemple en cas de pression hydrostatique |RG| = |p*g|
        ou p est la masse volumique du fluide et g l'acceleration
        de la pesanteur.

  VEC1 : direction du gradient de la pression (type POINT,
        facultatif). Par defaut il est defini comme la normale
        locale a chaque element de surface du maillage sous-jacent
        au modele MODL1. Ceci permet d'utiliser l'operateur pour
        calculer la rigidite associee a un sol elastique de type
        Winkler (contrainte de sol proportionelle au deplacement
        normal). Dans ce cas RG est la constante de raideur du sol.

  RIG1 : objet resultat (type RIGIDITE).

Remarques :

Le numero d'harmonique en cas d'analyse en serie de Fourier est
defini par la directive OPTION.
L'option de calcul 'ASYM' n'est pas disponible avec les elements
coq2 (mode de Fourier).

## KPRO [Mathematiques Autres]
    Operateur KPRO

    CHP2 = KPRO CHP1 GEO ;

    L'operateur KPRO construit la projection du champoint CHP1 selon
les connectivites definies par GEO:
la valeur de CHP1 au point 1 de chaque element de GEO est projetee sur
le point 2 du meme element de GEO.

    Commentaire :

    CHP1 : champoint a projeter

    CHP2 : champoint resulat de la projection

    GEO : objet maillage definissant les connectivites

## KRED [Fluides Resolution]
    Operateur KRED

Cet operateur a ete remplace par l'operateur KCHT.

## KRES [Fluides Resolution]
Operateur KRES

 1) KRES RVP CHPO1 'BETA' VAL1 VAL2 'PIMP' VAL3 VAL4 ;

 2) CHPO3 = KRES MA1 'TYPI' TAB1 ;

 2bis) CHPO3 = KRES MA1 (CHPO2) (MOTi VALi) ;

|  1ere possibilite  |

Objet :

Le foncteur KRES resout une equation de pression dans le
cadre de la resolution semi-implicite des equations
de Navier-Stokes dans CASTEM 2000.

Commentaire :

RVP : objet de type TABLE de sous-type EQPR

CHPO1 : objet de type CHPOINT contenant la variable
        PRESSION

VALi : objets de type REEL non documentes

|  2eme possibilite  |

Objet :

L'operateur KRES resout un systeme d'equations lineaires
de type Ax=b par une methode directe ou iterative.

Commentaire :

MA1 : objet de type RIGIDITE (ou MATRIK)
        c'est la matrice A.

TAB1 : TABLE de sous-type METHINV contenant les
        informations optionnelles.

CHPO2 : objet de type CHPOINT contenant le second membre
        du systeme a resoudre.
        C'est le "vecteur" b.

CHPO3 : objet de type CHPOINT contenant en retour
        (si la resolution a abouti) le "vecteur"
        solution du systeme : x.

Les informations sont :
- soit stockees dans TAB1 : TAB1 . MOTi = VALi (syntaxe 2) ;
- soit donnees sur ligne de commande (syntaxe 2bis).

MOTi et VALi peuvent prendre les valeurs suivantes :

- CLIM (type CHPOINT) :
   Conditions aux limites de Dirichlet

- SMBR (type CHPOINT) :
   Second membre CHPO2

- TYPINV (type ENTIER) :
   Methode d'inversion du systeme
   defaut -> 1 : resolution directe (Crout)
        2 : Gradient Conjugue
        3 : Bi-Gradient Conjugue Stabilise (BiCGSTAB)
        4 : BiCGSTAB(l)
        5 : GMRES(m) : restarted Generalized Minimal
        Residual
        6 : CGS (Conjugate Gradient Squared)
        7 : Algebraic Multigrid Notay FCG
        (matrice symetrique)
        8 : Algebraic Multigrid Notay GCR(m)
        (matrice non symetrique)
        9 : BiCG

- MATASS (type MATRIK) :
   Matrice de meme structure que MA1 (eventuellement egale)
   servant a preconditionner l'assemblage.
   Par defaut : MA1

- TYRENU (type MOT) :
   Methode de renumerotation des ddl :
   - 'RIEN'
   - 'SLOA' : algorithme de S.W. Sloan
   - 'GIPR' : algorithme de Gibbs-King
   - 'GIBA' : algorithme de Gibbs-Poole-Stockmeyer
   Par defaut : 'SLOA'

- PCMLAG (type MOT) :
   Methode de prise en compte des multiplicateurs de Lagrange :
   - 'RIEN'
   - 'APR2', 'APR3', 'APR4', 'APR5'.
   Par defaut : 'APR2'

- SCALING (type ENTIER) :
   Scaling de la matrice :
   - 0 : pas de scaling
   - 1 : scaling par les normes euclidiennes des lignes
        et des colonnes
   - 2 : scaling par la norme L1 des lignes et des colonnes
   Par defaut : 0

- SCALAG (type ENTIER) :
   Mise a l'echelle des multiplicateurs de Lagrange :
   - 0 : pas de mise a l'echelle
   - 1 : mise a l'echelle
   Par defaut : 1

 - OUBMAT (type ENTIER) :
    Oubli des matrices elementaires :
    - x0 : non
    - x1 : oui
    - x2 : suppression
    Destruction de la matrice assemblee (et du preconditionneur
    eventuel) apres resolution :
    - 0x : non
    - 1x : oui, sauf le profil Morse
    - 2x : oui
    Par defaut : 00

- IMPR (type ENTIER) :
   Niveau d'impression

- LTIME (type LOGIQUE) :
   Si cet indice vaut VRAI, l'operateur sort un deuxieme resultat
   de type TABLE qui contient les temps CPU passes dans les grandes
   etapes de l'algorithme de resolution.

- LDEPE (type LOGIQUE) :
   Si cet indice vaut VRAI (valeur par defaut) et que la matrice
   du systeme a resoudre est de type RIGIDITE, on effectue une
   elimination (si possible) des contraintes avant de resoudre.

- CVGOK (type ENTIER) (syntaxe 2 uniquement) :
     Une fois la resolution achevee, contient un entier strictement
     positif si la méthode de résolution n'a pas convergé et un
     entier strictement négatif si une erreur empêchant toute
     résolution s'est produite.

- indices specifiques aux methodes iteratives (2..9) :

  * XINIT (type CHPOINT) :
     Estimation de depart de l'inconnue.
     Par defaut : un chpoint nul.

  * MAPREC (type MATRIK) :
     Matrice de meme structure que MA1 (eventuellement egale)
     dont on utilise le preconditionneur.
     Par defaut : MA1

  * NITMAX (type ENTIER) :
     Nombre maximum de produits matrice-vecteur a effectuer.
     Par defaut : 2000.
  * CALRES (type ENTIER) :
     Façon de calculer le critere d'arret
     Par defaut : 0
     0 : ||b-Ax||_2 / ||b||_2
     1 : ||b-Ax||_2 / ||b-Ax0||_2
     (|| ||_2 : norme euclidienne)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## KRESP [—] (proc)
Procedure KRESP

CHPO2 = KRESP MA1 'TYPI' TAB1 MOTi VALi ;

  Objet :

  La procedure KRESP est appelee par la procedure EXEC.
  Elle prepare le calcul du preconditionneur puis fait appel
  a l'operateur KRES.

  Commentaire :

  MA1 : objet de type MATRIK (ou RIGIDITE)
        c'est la matrice A.

  TAB1 : TABLE de sous-type METHINV contenant les
        informations optionnelles (idem KRES).

  CHPO1 : objet de type CHPOINT contenant le second membre
        du systeme a resoudre par KRES.
        C'est le "vecteur" b.

  CHPO2 : objet de type CHPOINT contenant en retour
        (si la resolution a abouti) le "vecteur"
        solution du systeme : x.

  MOTi et VALi prennent les valeurs suivantes :

  - CLIM (type CHPOINT) :
     Conditions aux limites de Dirichlet

  - SMBR (type CHPOINT) :
     Second membre CHPO2

  - IMPR (type ENTIER) :
     Niveau d'impression

## KR_PRO [Fluides Resolution] (proc)
Procedure KR_PRO

CHPO2 = KR_PRO TAB1 CHPO1 ;

Objet :

Cette procedure calcule la permeabilite a l'eau
en fonction de la saturation reduite S.
Cette procedure est utilisee a partir de la procedure DARCYSAT.
La loi est donnee par le sous type de TAB1 :
- PUISSANCE
   k = ks S^B
- MUALEM
   k = ks * s^0.5 * (1 - (1 - (s^(1/M)))^M)^2
- BURDINE
   k = ks * s^2 * (1 - (1 - (s^(1/M)))^M)
- MUALEM_BURDINE
   k = ks * s^A * (1 - (1 - (s^(1/M)))^M)^B
- BROOKS_COREY
   k = ks * s^A * S^(2/lambda + B)
- EXPONENTIELLE
   k = ks * C / (C - 1 + exp (- alpha Pw N))
- LOGARITHMIQUE
   k = ks * C / (C + (log (- alpha Pw))^N)
   ou -alpha Pw tronque a 1 quand devient inferieur a 1.

Commentaires

TAB1 : table contenant les caracteristiques physiques, ayant
        pour indices

        SI loi 'PUISSANCE'
        'ALPHA' : coef. B (s.d.)

        SI loi 'MUALEM' 'BURDINE' et 'MUALEM_BURDINE'
        'COEF_M' : coef M

        SI loi 'MUALEM_BURDINE' et 'BROOKS_COREY'
        'COEF_A' : coef A
        'COEF_B' : coef B

        SI 'BROOKS_COREY'
        'LAMBDA' : coef lambda

        SI 'EXPONENTIELLE' ou 'LOGARITHMIQUE'
        'ALPHA' : alpha
        'COEF_C' : C
        'COEF_N' : N

        'PERMSAT' : coef. Ks, permeabilite a saturation (m/s)
        ('FLOTTANT', ou 'CHPOINT'
        dont les composantes sont celles demandees par la
        formulation, voir 'MODE' 'DARCY')
        sous-formulations autorisees : ISOTROPE,
        ORTHOTROPE, ANISOTROPE 2D ou 3D.
        'MODELE' : objet modele correspondant au domaine concerne

CHPO1 : saturation reduite ('CHPO' centre ou 'FACE') pour les
        lois PUISSANCE, MUALEM, BURDINE, MUALEM_BURDINE, BROOKS_COREY
        pression en eau pour les lois EXPONENTIELLE et LOGARITHMIQUE

CHPO2 : permeabilite totale en eau (m/s)

Remarques :

1. Le champ en sortie ont les meme points d'appui que le champ en
   entree.

2. Il a autant de composantes que l'indice PERMSAT.

3. Les directions d'anisotropie sont (0 0 1), (0 1 0) et (0 0 1)
   dans l'ordre. Charge a l'utilisateur de definir le tenseur
   PERMSAT dans ce repere-la.

## KSIG [Mecanique Modele]
    Operateur KSIGMA

      RIG1 = KSIGMA MODL1 SIG1 ( CAR1 ) ( 'FLAM' ) ;

    Objet :

    L'operateur KSIGMA calcule la matrice de raideur geometrique
    associee a un champ de contraintes.

      Commentaire :

      MODL1 : Objet modele ( type MMODEL ).

      SIG1 : champ de contraintes (type MCHAML, sous-type
        CONTRAINTES)

      CAR1 : champ de caracteristiques geometriques (pour certains
        elements: coques epaisses, DST, poutres, tuyaux)
        (type MCHAML, sous-type CARACTERISTIQUES)

     'FLAM' : mot-cle necessaire si l'on veut utiliser la matrice
        pour faire une analyse de flambage.

      RIG1 : objet resultat (type RIGIDITE, sous-type RIGIDITE).

    Remarque 1 :

     CAR1 doit contenir obligatoirement les cosinus-directeurs des
axes d'orthotropie par rapport au repere local , dans le cas de
l'element DST orthotrope ;ceci implique l'utilisation de l'operateur
MATR pour la creation de CAR1 .

    Remarque 2 :

    Le numero d'harmonique en cas d'analyse en serie de Fourier est
defini par la directive OPTION.

## KSOF [Mathematiques Autres]
 Operateur KSOF

    A = 'KSOF' TABDOM UN ;

 Objet : Transforme un CHPOINT VECT SOMMET en un CHPOINT SCAL FACE

A : resultat Champoint SCAL FACE

TABDOM : Table Domaine contenant le support geometrique de UN

UN : Champoint VECT SOMMET

## KTAN [Mecanique Modele]
    Operateur KTAN
    -------------- COMP

        |  matrice de raideur tangente  |

      RIG1 = 'KTAN' MODL1 SIG1 VAR1 MAT1
        ( 'PREC' FLOT1 ) ( 'DT ' FLOT2 )
        ( 'SYME' ) ;

    Objet :

    L'operateur KTAN calcule la matrice de raideur tangente en
elasto-plasticite. Si cela n'est pas possible, cet operateur
calcule la matrice de rigidite elastique.

      Commentaire :

      MODL1 : objet modele (type MMODEL)

      SIG1 : champ de contraintes (type MCHAML, sous-type CONTRAINTES)

      VAR1 : champ de variables internes (type MCHAML, sous-type
        VARIABLES INTERNES)

      MAT1 : champ de proprietes materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

      'PREC': mot-cle indiquant que l'on donne la precision

      FLOT1 : precision avec laquelle on cherche si un etat de
        contraintes est plastique ou non (1.E-3 par defaut)

      'DT ': mot-cle indiquant que l'on donne le pas de temps

      FLOT2 : pas de temps servant a calculer la matrice tangente
        Cette donnee n'est necessaire que pour les modeles
        visqueux.

      'SYME': mot-cle indiquant que l'on ne veut garder que la partie
        symetrique de la matrice tangente

      RIG1 : objet resultat (type RIGIDITE, sous-type RIGIDITE)

        |  matrice de raideur tangente  |
        |  par perturbation  |

      RIG1 = 'KTAN' 'PERT' MOD1 CHE1 CHE2
        ('C1' FLO1) ('C2' FLO2)
        ('SYME') ;

    Objet :

    L'operateur KTAN calcule la matrice de raideur tangente par
la methode de perturbation. A partir d'un etat initial et d'un etat
final, cet operateur perturbe l'increment de deformation en le
multipliant par un coefficient donne, calcule les contraintes
correspondant a cet etat perturbe et en deduit la matrice de
rigidite tangente.

      Commentaire :

        MOD1 MMODEL modele de calcul

        CHE1 MCHAML toutes les informations necessaires a
        l'operateur 'COMP' sur l'etat initial

        CHE2 MCHAML toutes les informations necessaires a
        l'operateur 'COMP' sur l'etat final
        ainsi que les contraintes de l'etat final
        ATTENTION ! Si plusieurs zones elementaires de ce champ
        correspondent au meme sous-modele, il faut
        que les deformations soient dans la premiere.

        'C1' mot-cle suivi du reel correspondant au
        coefficient C1 de la methode de calcul
        de la matrice tangente par perturbation

        FLO1 FLOTTANT strictement positif (par defaut 1.D-3)
        coefficient multiplicatif pour la perturbation
        de l increment de deformation

        'C2' mot-cle suivi du reel correspondant au
        coefficient C2 de la methode de calcul
        de la matrice tangente par perturbation

        FLO2 FLOTTANT strictement positif (par defaut FLO1/100.)
        deformation minimale de la perturbation

        'SYME' mot-cle indiquant que l'on ne veut garder que
        la partie symetrique de la matrice tangente

        RIG1 RIGIDITE objet resultat : matrice de rigidite

## KUET [Fluides Resolution] (proc)
   Operateur KUET
   -------------- FPAL

     UET = KUET NU UN NOR $DOMT $PAROI ;

OBJET :

Calcule la vitesse de frottement a la paroi pour un ecoulement laminaire

      UET = SQRT (TAU/RO) = SQRT (NU*dV/dY)

avec ; TAU cisaillement
       RO masse volumique
       NU viscosite cinematique
       V vitesse parallele a la paroi
       Y distance a la paroi

COMMENTAIRES :

UET vitesse de frottement (m/s) CHPOINT SCAL CENTRE PAROI

NU viscosite cinematique (m2/s) FLOTTANT

UN champ de vitesse (m/s) CHPOINT VECT SOMMET DOMT

NOR champ des normales aux faces (m) CHPOINT VECT FACE DOMT

$DOMT domaine total MMODEL SOUS TYPE 'NAVIER_STOKES'

$PAROI ligne representant la paroi (2D) MMODEL SOUS TYPE 'NAVIER_STOKES'

Remarques :

- NOR est calcule par DOMA sur tout le domaine (option 'NORMALE')
- L' operateur KUET ne fonctionne qu'en 2D (plan ou axisymetrique)

## KVOL [Fluides Resolution]
Operateur KVOL

     CHPC = KVOL OBJDOM ;

 OBJET : Cree un CHAMPOINT CENTRE contenant le volume des elements
        du domaine

        OBJDOM : TABLE de SOUSTYPE DOMAINE

## KWEIB1 [Mathematiques Statistiques] (proc)
Procedure KWEIB1

  CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
 A DISPOSITION DE LA COMMUNAUTE CAST3M
   PAR F. DUPRAT (LMDC - INSA Toulouse)

  Cette procedure est appelee par la procedure NATAF

## K_PRO [Fluides Resolution]
     Procedure K_PRO
     --------------- HT_PRO

        K1 = K_PRO TAB1 TAB2 ;

     Objet :

     Cette procedure permet de calculer la permeabilite a l'eau d'un
     milieu poreux non sature

        K1 : CHPOINT contenant la permeabilite

        TAB1 : table contenant les variables du problemes

        TAB2 : table contenant les parametres de la loi de permeabilite

    Commentaires :

   Les indices de la table TAB1 sont les suivants

        .'PNS_PROV' : CHPOINT des pressions negatives
        .'TH2O_PROV' : CHPOINT des teneurs en eau
        .'SATURATION_PROV' : CHPOINT des taux de saturation

   Dans le cadre d'un appel par DARCYSAT, ces CHPOINTs sont fournies.
   L'utilisateur peut ainsi creer une procedure personnelle decrivant
   une loi K(pression), K(teneur en eau) ou K(taux de saturation).

   Dans le cadre d'une utilisation hors contexte DARCYSAT, l'utilisateur
   doit seulement fournir la saturation pour la version standard.

   La loi de permeabilite standard est de la forme :
        K = K_sat * (S ** alpha)
   avec K_sat, permeabilite a saturation et S, taux de saturation

   Les indices de la table TAB2 sont les suivants :

        .'ALPHA' (type FLOTTANT OR CHPOINT) exposant de la loi
        .'PERMSAT' (type FLOTTANT OR CHPOINT) permeabilite a saturation

    Remarques :

  Dans le cas de l'utilisation d'une procedure K_PRO personnelle,
  TAB2 doit etre de soustype PERSONNELLE. L'utilisateur a alors toute
  liberte de choix sur les indices de la table TAB2.

  Les parametres sont de type FLOTTANT ou CHPOINT issu d'une operations
  KCHT ou KOPS. Pour un CHPOINT et dans le cadre d'une utilisation
  via la procedure DARCYSAT, le support geometrique des CHPOINT doit
  etre choisi en fonction de l'option d'homogeneisation (indice
  'HOMOGENEISATION' de la table transmise a DARCYSAT) : maillage
  'FACE' pour l'option decentree et maillage 'CENTRE' pour l'option
   centree.

     Exemple :

   Procedure personnelle K_PRO rassemblant 2 lois de forme analytique
   differentes s'appliquant sur deux zones distinctes :

'DEBPROC' KR_PRO TAB1*'TABLE' PRECED*'TABLE' ;
  si (EGA PRECED.'NOMZONE' 'SITE') ;
    K1 = 'KOPS' TAB1.'SATURATION_PROV' '**' PRECED.'ALPHA' ;
    K1 = 'KOPS' K1 '*' PRECED.'PERMSAT' ;
  finsi ;
  si (EGA PRECED.'NOMZONE' 'BO') ;
    K1 = (kops TAB1.'PNS_PROV' '*' PRECED.'ALPHA') EXP ;
    K1 = kops K1 '*' PRECED.'PERMSAT' ;
  finsi ;
'FINPROC' K1 ;

  Cette procedure est exploitable par DARCYSAT si les parametres
  des deux lois sont donnes a la table SATUR argument de la procedure
  DARCYSAT de la maniere suivante (cf. notice DARCYSAT) :

*---- definition de la loi de permeabilite
SATUR.'LOI_PERMEABILITE' = TABLE 'MULTIZONE' ;
*- pour la zone site
SATUR.'LOI_PERMEABILITE'. 'SITE' = TABLE 'STANDARD' ;
SATUR.'LOI_PERMEABILITE'. 'SITE'. 'ALPHA' = ... ;
SATUR.'LOI_PERMEABILITE'. 'SITE'. 'PERMSAT'= ... ;
SATUR.'LOI_PERMEABILITE'. 'SITE'. 'MODELE' = ... ;
*- pour la zone BO
SATUR.'LOI_PERMEABILITE'. 'BO' = TABLE 'PERSONNELLE' ;
SATUR.'LOI_PERMEABILITE'. 'BO'. 'ALPHA' = ... ;
SATUR.'LOI_PERMEABILITE'. 'BO'. 'PERMSAT'= ... ;
SATUR.'LOI_PERMEABILITE'. 'BO'. 'MODELE' = ... ;
*----calcul
DARCYSAT SATUR

## LAPL [Mathematiques Autres]
Operateur LAPLACE

EVOL2 = LAPL  | 'INVERSE'  LREEL1 LREEL2 LREEL3 FLOT1 ENTI1 ;

Objet :

L'operateur LAPL construit la transformee de Laplace inverse
d'une fonction de sk= a + i*wk, par la methode de DURBIN.

Commentaire :

LREEL1 : Objet contenant la liste des frequences wk (partie
        imaginaire de l'abscisse sk) .
        il faut que LREEL1 commence par 0. et que le pas soit cons-
        tant. LREEL1 doit contenir 2**N1 points.

LREEL2 : Objet contenant la partie reelle de la fonction F(sk)
        (type LISTREEL).

LREEL3 : Objet contenant la partie imaginaire de la fonction F(sk)
        (type LISTREEL).

FLOT1 : Partie reelle a de sk (positive ).

ENTI1 : ENTIER de regroupement de la methode de DURBIN
        tel que N1= ENTI1 * N2, oº N1 est le nombre de points de F
        et N2 le nombre de points de son inverse f.
        il faut que ENTI1 = 2**q

EVOL1 : fonction obtenue f(t) (type EVOLUTION)

## LAPN [Fluides Resolution]
     Operateur LAPN

 I Formulation Elements Finis :

     Syntaxe EQEX (cf EQEX) :

     ... 'EQEX' ... 'OPTI' MOT1 MOT2
        'ZONE' MOD1
        'OPER' 'LAPN' OBJ1
        'INCO' MOT3 (MOT4)

     OBJET :

     L'operateur LAPN discretise le terme de diffusion d'une equation
scalaire ou de l'equation de quantite de mouvement en supposant le
fluide incompressible.

     Dans le cas d'une equation scalaire de type equation de la chaleur
        dT/dt = div(alpha grad T)
cette operateur discretise le terme div(alpha grad T) ou alpha designe
la diffusivite ou la conductivite thermique (alpha en m2/s [SI]).

     Dans le cas de l'equation de quantite de mouvement, cet operateur
discretise la divergence du tenseur des contraintes visqueuses en
incompressible ; -> -> t ->
        dU/dt + ... = div(nu (grad U + grad U))
soit le terme div(nu (grad U + tgrad U)) ou nu designe la viscosite
cinematique (nu en m2/s [SI]).

     Dans le cas d'un systeme d'equations cet operateur permet de
discretiser le terme div(d grad T) dans une equation portant sur
une inconnue V : dV/dt + .... = div(d grad T)
V est appele inconnue duale et T inconnue primale.

     La convention de signe associee a ce terme est la suivante :
lorsque le coefficient de diffusion est positif, le maximum du champ
scalaire ou vectoriel decroit.

     Cet operateur est appele par la procedure EXEC.
La syntaxe indiquee permet a l'utilisateur de construire a l'aide
de l'operateur EQEX les donnees necessaires a l'operateur.

     Commentaires :

    'OPTI' : Mot cle introduisant les options numeriques de LAPN
     MOT1 : Type de discretisation spatiale ('EF', 'VF' ou 'EFM1')
     MOT2 : Type de discretisation temporelle ('EXPL' ou 'IMPL')
     Pour l'instant, VF et EF sont uniquement IMPL ; EFM1 EXPL.

    'ZONE' : Mot cle introduisant les informations geometriques
     MOD1 : Objet MODELE definissant la zone ou s'applique LAPN

    'OPER' : Mot cle introduisant les donnees physiques associees
        a l'operateur dont le nom suit
    'LAPN' : Nom de l'operateur
     OBJ1 : Coeff de diffusion (CHPO SCAL CENTRE, FLOTTANT ou MOT)

    'INCO' : Mot cle introduisant le nom des inconnues primale et duale
     MOT3 : Nom de l'inconnue primale T
     MOT4 : Nom de l'inconnue duale V
     Lorsque primale et duale sont identiques, MOT4 est optionnel. En
explicite, on a obligatoirement MOT3=MOT4.

     Resultats :

     En explicite :
     - Le second membre est stocke dans un CHPO et range dans la
table KIZG a l'indice de type MOT MOT3 (nom de l'inconnue).

     En implicite :
     - La matrice creee est stockee dans un MATRIK et rangee dans la
table TAB1 a l'indice de type MOT MATELM.
     - Le second membre est stocke dans un CHPO et assemble dans la
table EQEX a l'indice de type MOT SMBR. Le nom de l'inconnue duale
MOT4 etant le nom de la composante du CHPO cree.

     Remarques :

     1) Lorsque OBJ1 est de type MOT, l'operateur utilise le champ
contenu dans la table INCO a l'indice MOT indique.

     2) Le support geometrique (spg) des inconnues contient une des
classes de points de la table DOMAINE. Selon la formulation choisie
les compatibilites suivantes sont verifiees :
   - En formulation EF ou EFM1, le spg de la duale contient SOMMET
   - En formulation VF le spg de la duale contient CENTRE
   - lorsque les inconnues primale et duale sont differentes, elles
doivent avoir le meme spg.
   - le spg du coefficient de diffusion est CENTRE

     3) L'utilisateur-programmeur developpant ses propres procedures
transitoire appellera LAPN suivant la syntaxe :
     LAPN TAB1 ;
avec TAB1 : Table de sous type EQEX contenant les informations
        physiques et numeriques de l'operateur LAPN. Cette
        table est construite par l'operateur EQEX.

 II Formulation Volumes Finis :

 IIa : gaz parfait mono-constituant chaleur specifique constante

 Discretisations des termes diffusives des equations de Navier-Stokes
 compressible pour un gas parfait avec chaleur specifique constante

 SYNTAXE:

 RMAT1 RCHP1 DELTAT = 'LAPN' 'VF' 'PROPCOST' MOT1 MOT2 MOD1
        FLOT1 FLOT2 FLOT3 CHPO1 CHPO2 CHPO3 CHPO4 CHPO5
        (CHAM1 CHAM2 si MOT2 = 'IMPL')
        ('VIMP' CHPO6) ('TAUI' CHPO7)
        ('QIMP' CHPO8) ('MIXT' CHP10)
        ('TIMP' CHPO9) LMOT ('CLAUDEIS');

  MOT1 : objet de type MOT
        Il vaut 'RESI' si on veut calculer le residu
        Il vaut 'FLUX' si on veut calculer le flux
[… notice tronquée ; texte complet dans l'archive PCW_24]

## LCH2CLIM [Multi-physique Multi-physique] (proc)
Methode LCH2CLIM
---------------- OBJE

    LCH2CLIM CHPO1

    Objet

 La methode LCH2CLIM charge un CHPOINT dans l'element
 %CLIM d'un objet (DONCHI2)

## LCH2DELP [Multi-physique Multi-physique] (proc)
Methode LCH2DELP
---------------- OBJE

    LCH2DELP FLOT1

    Objet

 La methode LCH2DELP charge un FLOTTANT dans l'element
 %DELPE d'un objet (PARMCHI2)

## LCH2EPS [Multi-physique Multi-physique] (proc)
Methode LCH2EPS
--------------- OBJE

    LCH2EPS FLOT1

    Objet

 La methode LCH2EPS charge un FLOTTANT dans l'element
 %EPS d'un objet (PARMCHI2)

## LCH2FION [Multi-physique Multi-physique] (proc)
Methode LCH2FION
---------------- OBJE

    LCH2FION CHPO1

    Objet

 La methode LCH2FION charge un CHPOINT dans l'element
 %FIONI d'un objet (DONCHI2)

## LCH2IAFF [Multi-physique Multi-physique] (proc)
Methode LCH2IAFF
--------------- OBJE

    LCH2IAFF ENTI1

    Objet

 La methode LCH2IAFF charge un ENTIER dans l'element
 %IAFFICHE d'un objet (PARMCHI2)

## LCH2IMPR [Multi-physique Multi-physique] (proc)
Methode LCH2IMPR
--------------- OBJE

    LCH2IMPR LENT1

    Objet

 La methode LCH2IMPR charge un LISTENTI dans l'element
 %IMPRIM d'un objet (PARMCHI2)

## LCH2ITMA [Multi-physique Multi-physique] (proc)
Methode LCH2ITMA
--------------- OBJE

    LCH2ITMA ENTI1

    Objet

 La methode LCH2ITMA charge un ENTIER dans l'element
 %ITMAX d'un objet (PARMCHI2)

## LCH2ITSO [Multi-physique Multi-physique] (proc)
Methode LCH2ITSO
---------------- OBJE

    LCH2ITSO ENTI1

    Objet

 La methode LCH2ITSO charge un ENTIER dans l'element
 %ITERSOLI d'un objet (PARMCHI2)

## LCH2LOGC [Multi-physique Multi-physique] (proc)
Methode LCH2LOGC
---------------- OBJE

    LCH2LOGC CHPO1

    Objet

 La methode LCH2LOGC charge un CHPOINT dans l'element
 %LOGC d'un objet (DONCHI2)

## LCH2MDEL [Multi-physique Multi-physique] (proc)
Methode LCH2MDEL
--------------- OBJE

    LCH2MDEL ENTI1

    Objet

 La methode LCH2MDEL charge un ENTIER dans l'element
 %MDELPE d'un objet (PARMCHI2)

## LCH2NFI [Multi-physique Multi-physique] (proc)
Methode LCH2NFI
--------------- OBJE

    LCH2NFI ENTI1

    Objet

 La methode LCH2NFI charge un ENTIER dans l'element
 %NFI d'un objet (PARMCHI2)

## LCH2NITE [Multi-physique Multi-physique] (proc)
Methode LCH2NIT
--------------- OBJE

    LCH2NITE ENTI1

    Objet

 La methode LCH2NITE charge un ENTIER dans l'element
 %NITERPE d'un objet (PARMCHI2)

## LCH2NTY4 [Multi-physique Multi-physique] (proc)
Methode LCH2NTY4
---------------- OBJE

    LCH2NTY4 CHPO1

    Objet

 La methode LCH2NTY4 charge un CHPOINT dans l'element
 %NTY4 d'un objet (DONCHI2)

## LCH2PREP [Multi-physique Multi-physique] (proc)
Methode LCH2PREP
---------------- OBJE

    LCH2PREP FLOT1

    Objet

 La methode LCH2PREP charge un FLOTTANT dans l'element
 %PRECPE d'un objet (PARMCHI2)

## LCH2SORT [Multi-physique Multi-physique] (proc)
Methode LCH2SORT
--------------- OBJE

    LCH2SORT LMOTS

    Objet

 La methode LCH2SORT charge un LISTMOTS dans l'element
 %SORTIE d'un objet (PARMCHI2)

## LCH2TEMP [Multi-physique Multi-physique] (proc)
Methode LCH2TEMP
---------------- OBJE

    LCH2TEMP CHPO1

    Objet

 La methode LCH2TEMP charge un CHPOINT dans l'element
 %TEMPE d'un objet (DONCHI2)

## LCH2TOT [Multi-physique Multi-physique] (proc)
Methode LCH2TOT
--------------- OBJE

    LCH2TOT CHPO1

    Objet

 La methode LCH2TOT charge un CHPOINT dans l'element
 %TOT d'un objet (DONCHI2)

## LECT [Langage Base]
Operateur LECT
-------------- EVOL ENUM

LENTI1 = LECT 1 2 3 4 5 ;

Objet :

L'operateur LECT fabrique un objet LENTI1 de type LISTENTI a partir
d'un nombre arbitraire d'objets de type ENTIER.

La sous-directive PAS permet d'engendrer des nombres regulierement
espaces, et la sous directive * permet d'engendrer plusieurs fois le
meme nombre.

Commentaire :

|  Sous-directive PAS  |

LENTI1 = LECT 1 PAS 2 5 ; equivaut a : LENTI1 = LECT 1 3 5 ;

Le PAS doit obligatoirement diviser exactement l'intervalle.

Autre possibilite :

LENTI1 = LECT 1 PAS 2 NPAS 2 ; equivaut a : LENTI1 = LECT 1 3 5 ;

NPAS doit etre positif ou nul.

|  Sous-directive  *  |

LENTI1 = LECT 4 * 3 ; equivaut a : LENTI1 = LECT 3 3 3 3 ;

On peut utiliser des pas negatifs et melanger les
sous-directives.

LENTI1 = LECT 1 2 PAS -2 -6 2 3 * 9 PAS 2 3 * 13 ;
ou
LENTI1 = LECT 1 2 PAS -2 NPAS 4 2 3 * 9 PAS 2 3 * 13 ;
equivaut a
LENTI1 = LECT 1 2 0 -2 -4 -6 2 9 9 9 11 13 13 13 ;

## LEGENDE [Post-traitement Affichage] (proc)
  TAB1  =  LEGENDE  |  NUAG1  MOT1  ('FORMAT'  MOT2)  ;
        |  EVOL1 ;

Procedure LEGENDE

Objet :

La procedure LEGENDE renvoie une table de legende pour l'operateur DESS
permettant d'afficher les titres des EVOLUTIONs contenues dans l'objet
NUAG1 correspondant aux differentes valeurs de la composante MOT1 ou
une table contenant en titre les etiquettes des ordonnees de EVOL1.

Commentaire :

NUAG1 : Objet NUAGE possedant une composante de type EVOLUTION et
        d'autres de type FLOTTANT ou ENTIER.

MOT1 : Objet MOT, nom de la composante selon laquelle definir les
        titres des differentes EVOLUTIONS.

MOT2 : Objet MOT, format FORTRAN pour les valeurs des titres.

EVOL1 : Objet EVOLUTION dont on veut une table de legendes.

TAB1 : Objet TABLE, table de legende a fournir a l'operateur DESS.

## LESPCOMP [Multi-physique Multi-physique] (proc)
Methode LESPCOMP
---------------- OBJE

    Objet

 La methode LESPCOMP charge un LISTENTI dans l'element
 %COMP d'un objet (LIESPECE)

## LESPITYP [Multi-physique Multi-physique] (proc)
Methode LESPITYP
---------------- OBJE

LESPITYP ENTI1 ;

    Objet

 La methode LESPITYP charge un ENTIER dans l'element
 %ITYP d'un objet (LIESPECE)

## LESPLOGK [Multi-physique Multi-physique] (proc)
Methode LESPLOGK
--------------- OBJE

LESPLOGK FLOT1 ;

    Objet

 La methode LESPLOGK charge un FLOTTANT dans l'element
 %LOGK d'un objet (LIESPECE)

## LESPSTOE [Multi-physique Multi-physique] (proc)
Methode LESPSTOE
---------------- OBJE

    Objet

 La methode LESPSTOE charge un LISTREEL dans l'element
 %STOECH d'un objet (LIESPECE)

## LEVM [Mathematiques Fonctions]
Operateur LEVM
-------------- AJUSTE

LREE5 CHI2 = LEVM 'ABSC' LREE1 'ORDO' LREE2 'SIGM' LREE3
        'PARA' LREE4 'PROC' PRO1 ;

Objet :

L'operateur LEVM etablit la meilleure proposition d'un jeu de
parametres d'une fonction visant a approcher une suite de points
(abscisse, ordonnee) specifiee. Le critere est une moyenne
quadratique ponderee des ecarts des ordonnees. L'algorithme
reprend la methode dite de Levenberg-Marquardt. L'operateur n'est
pas reinitialisee en cas d'interruption par l'utilisateur.

Commentaire :

LREE5 : type LISTREEL, liste des parametres proposes

CHI2 : type FLOTTANT, valeur finale du critere

LREE1 : type LISTREEL, liste des abscisses

LREE2 : type LISTREEL, liste des ordonnees

LREE3 : type LISTREEL, liste des poids de chacun des points

LREE4 : type LISTREEL, liste des parametres d'initialisation
        (il convient de donner des reels non nuls dans l'ordre
        de grandeur des valeurs attendues)

PRO1 : procedure gibiane de calcul des ordonnees et des derivees
       partielles en chacun des points de LREE1. Il convient
       de s'assurer d'une precision coherente pour le calcul
       des derivees partielles. Exemple de donnees :

       DEBPROC PRO2 LREEX*LISTREEL LREEA*LISTREEL ;

       * calcul de la fonction parametree
       * compute the parameters dependant function
       * LREEX : liste des abscisses / abscissas
       * LREEA : liste des parametres / parameters
       * LREEY : liste des ordonnees / ordinates

       FINPROC LREEY ;

       DEBPROC PRO1 LREEX*LISTREEL LREEA*LISTREEL ;

       * fonction argument
       * input procedure for LEVM
       * LREEX : liste des abscisses / abscissas
       * LREEA : liste des parametres / parameters
       * LREEY : liste des ordonnees / ordinates
       * calcul de LREEY
       LREEY = PRO2 LREEX LREEA ;

       * derivees partielles / partial derivatives
       TLRE = TABLE ;
       REPETER BPAR (DIME LREEA) ;
        ai = EXTR LREEA &BPAR ;
        LREEB = COPIE LREEA ;
        REMP LREEB &BPAR (ai * (1. + 1.e-2)) ;
        TLRE . &BPAR = PRO2 LREEX LREEB ;
       FIN BPAR ;

       * LREDY : derivees partielles / partial derivatives
       LREDY = PROG ;
       REPETER BX (DIME LREEX) ;
        REPETER BPAR (DIME LREEA) ;
        dyi = ((EXTR TLRE . &BPAR &BX) - (EXTR LREEY &BX) )
        / 1.e-2 / (EXTR LREEA &BPAR) ;
        FIN BPAR ;
       FIN BX ;

       FINPROC LREEY LREDY ;

## LIAI [Maillage Autres]
   Operateur LIAISON

    | 1ere possibilite : creation d'elements de liaison ordinaires |

    GEO1 = LIAISON (FLOT1) GEO2 GEO3 ;

    Objet :

    L'operateur LIAISON engendre l'ensemble des elements de liaison
entre deux objets surfaciques.

    Commentaire :

    GEO2 | : objets surfaciques (type MAILLAGE)
    GEO3 |

    GEO1 : objet resultat (type MAILLAGE)

    FLOT1 : critere de proximite entre les deux objets surfaciques
        par defaut FLOT1 est egal au dixieme de la densite courante

    Remarque :

    Un element est cree entre un element de GEO2 et un element
de GEO3 distants de moins de CRIT point a point.

    Utiliser l'operateur RACCORD pour des maillages lineiques (2D).

    Pour la creation d'un element joint JOI4 (3D) :

        -GEO2 et GEO3 definissent respectivement les surfaces 1 et 2
de cet element. Ces surfaces doivent etre definies dans le meme sens.
Ce sens est celui du contour de la surface 1. La numerotation des
noeuds de la surface 1 doit etre telle que les axes (1,2,N) forment
un triedre direct, avec N dirigee positivement dans le sens de
l'ouverture de l'element joint.
   On definit les grandeurs suivantes :
 . axe 1 = vecteur reliant le noeud 1 au noeud 2 de la surface 1
 . axe 2 = vecteur reliant le noeud 1 au noeud 4 de la surface 1
 . axe N = vecteur normal au plan defini par les vecteurs 1 et 2
 . ouverture du joint = mouvement d'eloignement de la surface 1 par
   rapport a la surface 2 quand la surface 2 est fixe.

        -Pour la prise en compte d'un jeu initial x dans un element
joint, GEO2 et GEO3 doivent etre distants de x. De plus, x doit etre
rentre comme deformation inelastique normale initiale lors de l'appel
a PASAPAS (cf rapport DMT/93.655).

    | 2eme possibilite : creation d'un element de liaison poreux |

    GEO1 = LIAISON (FLOT1) GEO2 GEO3 GEO4 ;

    Objet :

    L'operateur LIAISON engendre l'ensemble des elements de liaison
    entre trois objets surfaciques.

    Commentaire :

    GEO2 | : objets surfaciques (type MAILLAGE)
    GEO3 |
    GEO4 |

    GEO1 : objet resultat (type MAILLAGE)

    FLOT1 : critere de proximite entre les objets surfaciques deux a deux
        par defaut FLOT1 est egal au dixieme de la densite courante

    Remarque :

    Un element est cree entre un element de GEO2, un element de GEO3 et un
    element de GEO4 distants de moins de CRIT point a point. Les objets
    GEO2 et GEO3 peuvent etre composes par des triangles a 6 points ou des
    rectangles a 8 points. L'objet GEO3 est composes par des triangles a 3
    points ou des rectangles a 4 points.

## LIBDD [Multi-physique Multi-physique] (proc)
Methode LIBDD
------------- OBJE

    Objet

 La methode LIBDD charge un MOT dans l'element
 %BDD d'un objet (DONCHI1)

## LICHXMX [Multi-physique Multi-physique] (proc)
Methode LICHXMX
--------------- OBJE

    Objet

 La methode LICHXMX charge un LISTENTI dans l'element
 %CHXMX d'un objet (DONCHI1)

    Commentaires

    voir DONCHI1

## LICOCHAR [Multi-physique Multi-physique] (proc)
Methode LICOCHAR
---------------- OBJE

    Objet

 La methode LICOCHAR charge un ENTIER dans l'element
 %CHARGE d'un objet (LINVCOMP)

## LICOMNOM [Multi-physique Multi-physique] (proc)
Methode LICOMNOM
---------------- OBJE

    Objet

 La methode LICOMNOM charge un mot dans l'element
 %NOM d'un objet (LINVCOMP)

## LIESPECE [Multi-physique Multi-physique] (proc)
Methode LIESPECE
---------------- DONCHI1

 OBJ1 = OBJET LIESPECE ;

    Objet

 La methode LIESPECE permet de creer un objet de type objet et de
 CLASSE LIESPECE. Un tel objet contient toutes les donnees d'une
 nouvelle espece pour l'operateur CHI1. Cet objet pourra etre
 utilise par DONCHI1%GNVESP.

    Commentaires

    Les methodes associees a LIESPECE sont

   ESP_IDEN ESP_LOGK ESP_ITYP ESP_COMP ESP_STOE

ESP_IDEN Charge le contenu de l'indice IDEN,entier identifiant de
        l'espece
        appel : OBJ1%ESP_IDEN ENTI1 ;

ESP_LOGK Charge le contenu de l'indice LOGK, reel logk de l'espece
        appel : OBJ1%ESP_LOGK FLOT1;

ESP_ITYP Charge le contenu de l'indice ITYP,entier type de l'espece
        2 complexe en solution
        3 activite fixee
        4 mineraux precipites
        5 mineraux dissous
        6 non pris en compte dans le calcul
        appel : OBJ1%ESP_ITYP ENTI1 ;

ESP_COMP Charge le contenu de l'indice COMP, LISTENTI contenant
        les identifiants des composants de l'espece.Le nombre de
        ces identifiants doit etre inferieur a 4 pour une base
        de donnee de type MINEQL et inferieur a 8 pour une base
        de donnee de type STRASBG.
        appel : OBJ1%ESP_COMP LENTI1 ;

ESP_STOE Charge le contenu de l'indice STOECH LISTREEL coefficient
        stoechiometrique correspondant a chacun de ces composants.
        appel : OBJ1%ESP_STOE LREEL1 ;

## LIGN [Maillage Lignes]
    Operateur LIGN
    -------------- DROI ROTA

    GEO1 = LIGN 'ROTA' .... voir cas 1
        'TRAN' .... voir cas 2

    (C est aussi admis)

 | Cas 1 : Trace d'un arc de cercle |

    GEO1 = LIGN (N1) CENTRE POINT1 (NORMAL si 3D) ANGLE
        ('DINI' DENS1) ('DFIN' DENS2) 'ROTA'

    Objet :

    L'operateur LIGN permet de construire l'arc de cercle de centre
    CENTRE, d'extremite POINT1 et d'angle d'ouverture ANGLE.
    En dimension 2, le sens trigonometrique impose l'orientation angulaire.
    En dimension 3, le cercle appartient au plan de normale NORMAL et le
    sens trigonometrique est impose par la direction de cette normale.

    Commentaire :

    CENTRE : centre du cercle (type POINT)

    POINT1 : point extremite de l'arc de cercle (type POINT)

    N1 : nombre d'elements generes (type ENTIER)

    DENS1 | : densites associees au point POINT et au 2eme point extremite
    DENS2 |  de l'arc de cercle (deduit de l'angle d'ouverture)
        (type FLOTTANT)

    NORMAL : en 3D, ce vecteur definit la normale au cercle . En appelant
        CP le vecteur (CENTRE->POINT1), le triedre direct correspondant
        est (CP,NORMAL vectoriel CP,NORMAL) (type POINT)

    ANGLE : angle d'ouverture de l'arc de cercle

    GEO1 : arc de cercle (type MAILLAGE)

    Remarque 1 :

     Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
     Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.

     Remarque 2 :

     Si une ligne LIG1 est donnee a la place du point POINT1 cette ligne
est prolongee jusqu'au point deduit de la rotation de l'extremite de LIG1.

 | Cas 2 : Trace d'une ligne par translation d'un point |

    GEO1 = LIGN (N1) POINT1 VECTEUR ('DINI' DENS1) ('DFIN' DENS2) 'TRAN'

    Objet :

    L'operateur LIGN permet de construire le segment d'extremites POINT1
    et POINT2 ou POINT2 = POINT1 + VECTEUR

    Commentaire :

    POINT1 : point extremite du segment (type POINT)

    VECTEUR : vecteur de translation de POINT1 (type POINT)

    N1 : nombre d'elements generes (type ENTIER)

    DENS1 | : densites associees au point POINT et au 2eme point extremite
    DENS2 |  de l'arc de cercle (deduit de l'angle d'ouverture)
        (type FLOTTANT)

    GEO1 : droite (type MAILLAGE)

    Remarque 1 :

     Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.
     Si N1 est specifie et positif, N1 elements d'egale longueur
seront engendres.

     Remarque 2 :

     Si une ligne LIG1 est donnee a la place du point POINT1 cette ligne
est prolongee jusqu'au point deduit de la translation de l'extremite de LIG1.

## LILIDEN [Multi-physique Multi-physique] (proc)
Methode LILIDEN
--------------- OBJE

    Objet

 La methode LILIDEN charge un LISTENTI dans l'element
 %IDEN d'un objet (DONCHI1)

## LILIECH [—] (proc)
Methode LILIECH
--------------- OBJE

    Objet

 La methode LILIECH charge un LISTENTI dans l'element
 %ECHANGE d'un objet (DONCHI1)

## LIMEMECA [Mecanique Resolution] (proc)
   Procedure LIMEMECA
   ------------------ TRACMECA

   LOG1 FLOT2 CHPO3 MCHML2=
        LIMEMECA MODL1 TAB1 TAB2 MCHML1 CHPO1 (CHPO2 FLOT1);

    Objet :

    La procedure LIMEMECA permet de determiner l'etat limite d'une
structure:

- definie par le modele MODL1 et les mecanismes de rupture
    elementaires TAB1 et TAB2 obtenus a l'aide de l'operateur MESM,

- dont les caracteristiques plastiques sont contenues dans le champ
    par element MCHML1,

- soumise au chargement variable contenu dans le champ par point
    CHPO1,

- soumise eventuellement au chargement constant CHPO2.

    FLOT1 et un coefficient (defaut 1.) qu'il faut eventuellement
augmenter si l'optimisation est incomplete (LOG1 est alors FAUX). L'etat
limite est defini par le coefficient multiplicateur FLOT2 de la charge
CHPO1, le mode d'ecoulement CHPO3 et l'etat d'ecoulement MCHML2.

    Remarque :

    le champ par element MCHML1 est constant par element, donne aux
noeuds et contient les composantes suivantes: 'MZ1+' et 'MZ1-' (moments
de plastification positif et negatif a l'extremite 1 de l'element),
'MZ2+' et 'MZ2-' (moments de plastification positif et negatif a
l'extremite 2 de l'element), et, eventuellement, 'F2+ ' et 'F2- '
(forces de plastification en traction et en compression le long de
l'element.

## LINBIDEN [Multi-physique Multi-physique] (proc)
Methode LINBIDEN
---------------- OBJE

    Objet

 La methode LINBIDEN charge un ENTIER dans l'element
 %IDEN d'un objet (LIESPECE)

## LINVCOMP [Multi-physique Multi-physique] (proc)
Methode LINVCOMP
---------------- DONCHI1

 OBJ1 = OBJET LINVCOMP ;

    Objet

 La methode LINVCOMP permet de creer un objet de type objet et de
 CLASSE LINVCOMP. Un tel objet contient toutes les donnees d'un
 nouveau composant pour l'operateur CHI1. Cet objet pourra etre
 utilise par DONCHI1%GNVCOMP.

    Commentaires

    Les methodes associees a LINVCOMP sont

   COM_IDEN COM_NOM COM_CHAR

 COM_IDEN Charge le contenu de l'indice IDEN,entier identifiant de
        l'espece
        appel : OBJ1%COM_IDEN ENTI1 ;

 COM_NOM Charge le contenu de l'indice NOM, nom de l'espece
        appel : OBJ1%COM_NOM MOT1;

 COM_CHAR Charge le contenu de l'indice CHARGE,entier charge de
        l'espece simple associee.
        appel : OBJ1%COM_CHAR ENTI1 ;

## LIRE [Entree-Sortie Entree-Sortie]
1. Directive LIRE

     LIRE | (GEO1)  | ;
        | 'PROC' FIC1 (MOT1) | ;

2. Operateur LIRE

     TAB1 = LIRE  | 'AVS'  | ;
        | 'MED' FIC1 |
        | 'UNV' FIC1 |
        | 'FEM' FIC1 |
        | 'NAS' FIC1 |
        | 'CSV' FIC1  ('DEBU' ENTI1) ('FIN' ENTI2) ('SEPA' MOT1) | ('COLO') | ;
        |  'LIGN'  |

     MAIL1= LIRE 'STL' FIC1 ;

    Objet :

| 1. Directive 'LIRE'  |
CHAP{'LIRE' utilise comme une directive}
PART{LIRE un MAILLAGE}
1.1. La directive LIRE lit un MAILLAGE sur le fichier d'unite logique N1
     definie par la directive OPTION :

        OPTION LECT N1; (N1 = 4 par defaut)

    Tous les sous-objets presents dans le fichier sont egalement lus.
    Si le nom GEO1 du maillage est fourni, on verifie qu'il existe bien
    sur le fichier.

PART{LIRE une PROCEDUR}
1.2. La directive LIRE cree une ou plusieurs procedures en important
     le contenu du fichier FIC1.

     Deux alternatives sont offertes :

     a) La syntaxe du fichier FIC1 est telle que celle adoptee pour
        charger des procedures via le fichier UTILPROC (voir la notice
        de l'operateur UTIL) :

        - Chaque procedure est encapsulee dans un bloc delimite par
        les instructions DEBP et FINP

        - Chacun de ces blocs est precede d'une ligne commençant par
        "$$$$ xxxxxxxx" où le mot xxxxxxxx est un nom GIBIANE valide.
        Ce nom doit etre identique a celui que l'on trouve derriere
        l'instruction DEBP correspondante (la casse est indifferente)

        Si MOT1 est fourni, alors seule la procedure de FIC1 portant ce
        nom sera importee (si elle existe).

     b) Le fichier est un jeu de donnees (suite d'instructions GIBIANE).
        Dans ce cas, un objet PROCEDUR de nom MOT1 est cree et le
        contenu de FIC1 y est charge. Cela signifie en particulier que
        la directive DEBP ne doit apparaitre nulle part dans FIC1.

| 2. Operateur 'LIRE'  |
CHAP{'LIRE' utilise comme un operateur}

PART{LIRE au format 'AVS'}
2.1 En presence du mot-cle 'AVS' LIRE devient un operateur, qui lit le
    fichier d'unite logique N1 definie par la directive OPTION :

        OPTION LECT N1; (N1 = 4 par defaut)

    On suppose que le fichier est de format AVS UCD (Unstructured
    Cell Data) ASCII.
    Les objets trouves dans ce fichier sont loges dans la table TAB1.
    La structure de cette table est la suivante (tous les indices sont
    de type MOT) :

    Indice  |  Contenu
    MAILSUPP | Objet de type MAILLAGE compose de points (POI1) et
        | contenant tous les noeuds. Cet objet consitue le support
        | du champ nodal (objet de type CHPOINT) si celui-ci
        | existe. Il est toujours cree. Il peut etre utilise pour
        | visualiser differentes parties du maillage par rapport au
        | maillage entier.
    LEMAILLA | Objet de type MAILLAGE contenant tous les elements
        | trouves dans le fichier AVS. C'est un objet compose de
        | sous-maillages elementaires, dont chacun est homogene du
        | point de vue du type d'element et du numero du materiau.
        | Il est toujours cree.
    SOUMAILA | Objet de type TABLE. Cette table contient les sous-
        | maillages elementaires qui sont indices par des nombres
        | entiers, allant de 1 jusqu'au nombre de ces sous-
        | maillages. Cette table est toujours creee.
    LECHPOIN | Objet de type CHPOINT. Il n'est cree que lorsque le
        | fichier AVS contient le champ nodal. Il s'appuie sur le
        | maillage MAILSUPP.
    LEMCHAML | Objet de type MCHAML. Il n'est cree que lorsque le
        | fichier AVS contient le champ par element. Il est compose
        | de sous-champs elementaires dont chacun s'appuie sur un
        | sous-maillage elementaire.
     tout  | Objet de type FLOTTANT (un nombre reel). Chaque
     autre  | composante du champ global (s'il existe) apparait dans la
     nom  | table sous son propre nom (tronque a 4 caracteres).

    Plusieurs structures UCD peuvent etre lues (par exemple dans un
    fichier cree avec la directive SORT 'AVS' ... 'SUIT') si on repete
    l'ordre de lecture plusieurs fois (voir soravs.dgibi).

PART{LIRE au format 'MED' (Salome)}
2.2 En presence du mot-cle 'MED', LIRE devient un operateur qui place
    les OBJETS MAILLAGE ou les champs de résultats, lus dans le fichier
    MED 3.2, dans une TABLE avec son nom comme indice.

    Dans le cas où les champs contiennent des valeurs nodales, ils
    sont lus dans Cast3M sous forme d'un objet de type CHPOINT.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## LIREFLOT [Entree-Sortie Entree-Sortie] (proc)
    Procedure LIREFLOT

        FLOT1 = LIREFLOT FLOT2 FLOT3 ;

    Objet :

    Cette procedure permet, dans une utilisation interactive, d'acquerir
de la part de l'utilisateur un nombre reel compris entre deux bornes.
    En cas d'erreur, un message apparait a l'ecran.

    Commentaire :

    FLOT2 : borne inferieure (type FLOTTANT)

    FLOT3 : borne superieure (type FLOTTANT)

    FLOT1 : nombre reel obtenu (type FLOTTANT)

    Remarque :

    Les operandes doivent etre entres dans l'ordre indique dans la
syntaxe.

## LIRSOSO [Multi-physique Multi-physique] (proc)
Methode LIRSOSO
--------------- DONCHI1

 OBJ1 = OBJET LIRSOSO ;

    Objet

 La methode LIRSOSO permet de creer un objet de type objet et de
 CLASSE LIRSOSO. Un tel objet contient toutes les donnees d'une
 nouvelle espece pour l'operateur CHI1. Cet objet pourra etre
 utilise par DONCHI1%GNVSOSO.

    Commentaires

    Les methodes associees a LIRSOSO sont

   SOS_IDEN SOS_ITYP SOS_SOLI SOS_FRAC

 SOS_IDEN Charge le contenu de l'indice IDEN,entier identifiant de
        la solution solide.
        appel: OBJ1%SOS_IDEN ENTI1 ;

 SOS_ITYP Charge le contenu de l'indice ITYP,entier type de la
        solution solide
        3 activite fixee
        4 solution solide precipite
        5 solutions solides dissoutes
        6 non pris en compte dans le calcul
        Pour les types 3 et 4, il faut obligatoirement
        donner les fractions molaires des poles des
        solutions solides; pour les types 5 et 6, ce
        n'est pas obligatoire.
        appel: OBJ1%SOS_ITYP ENTI1 ;

 SOS_SOLI Charge le contenu de l'indice SOLID. LISTENTI contenant
        les identifiants des poles mineraux purs de la
        solution solide. Le nombre de ces poles doit etre
        inferieur a 36. Ces poles sont mis automatiquement en
        type 6 (ils servent au calcul,mais n'ont pas
        d'existance physique).
        appel: OBJ1%SOS_SOLI LENTI1 ;

 SOS_FRAC Charge le contenu de l'indice FRACTIO. LISTREEL contenant
        les fractions molaires correspondant a chacun des poles.
        (Si la solution solide est mise en type 3 ou 4,
        l'operateur chi1 a besoin des fractions molaires pour
        calculer les coefficients stoechiometriques ainsi que
        le logK de la solution solide.Si la solution solide
        est mise en type 5 ou 6, l'operateur chi2 calculera
        lui meme les fractions molaires et le reste).
        appel: OBJ1%SOS_FRAC LREEL1 ;

## LIST [Entree-Sortie Entree-Sortie]
    Directive LISTE

    Objet :

    La directive LISTE s'utilise dans plusieurs cas :

    | 1er cas |

    LISTE ;

    Objet :

    La directive LISTE, sans operande, donne la liste des points et des
objets nommes.

    | 2eme cas |

    LISTE ( 'RESUME' ) OBJET1 ( N1 ( N2 )) ;

    Objet :

    La directive LISTE donne des informations sur l'objet OBJET1.

    Si le mot 'RESUME' est employe, certaines listes d'informations
seront reduites.

    Dans le cas de la liste d'une PROCEDURE, on peut preciser soit le
numero N1 (type ENTIER) de la ligne desiree, soit les bornes N1 N2
(type ENTIER) de l'intervalle des lignes desirees.
Exemple : LIST ACIER; ou LIST ACIER 5; ou LIST ACIER 5 8;

    Dans le cas d'un objet LISTENTI, LISTREEL ou RIGIDITE, on peut
préciser le nombre N1 de valeurs avant d'effectuer un retour a la lignes
(respectivement 20, 10 et 39 par defaut).

    Dans le cas d'un objet TABLE, on peut préciser le nombre N1 (limite
a 10) d'eventuelle sous-tables a explorer et afficher de maniere
recursive.

    | 3eme cas |

    LISTE *MONTYP1 (MOT1) ;

    Objet :

    Dans ce cas, la directive LISTE donne la liste des objets du
type MONTYP1.

    Si l'argument optionnel MOT1 est precise, LISTE ne liste que
les objets du type MONTYP1 correspondant a cette option.

    Actuellement, cette option n'est disponible que pour les objets
de type MAILLAGE, avec MOT1 egal a : LIGNE, SURFACE ou VOLUME.

## LITEMPER [Multi-physique Multi-physique] (proc)
Methode LITEMPER
---------------- DONCHI1

  LITEMPER <MOT1> <ENT1> ;

    Objet

 La methode LITEMPER charge un ENTIER ou un mot dans
 l'element %TEMPERATURE d'un objet (DONCHI1)

## LOG [Mathematiques Fonctions]
  RESU1 = 'LOG' OBJET1 (MOT1) ;

Operateur LOG

Objet :

L'operateur LOG calcule le logarithme naturel de l'objet OBJET1.

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

## LOGK [Multi-physique Multi-physique]
Operateur LOGK

    CHPO3 = LOGK TAB1 LENTI1 <'FORCEION' CHPO1 >

     Objet
    Calcul de la constante (apparente) de la loi d'action de masse,
    en tout point d'un domaine pour un systeme chimique donne.

    Commentaires
    TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

    LENTI1 est objet de type LISTENTI contenant la liste des
        identifiants pour lesquels on veut calculer le LOGK

    'FORCEION' mot cle ( doit preceder CHPO1)

    CHPO1 nom d'un objet de type CHPOIN ayant une composante scalaire
        , et contenant la valeur de la force ionique en chaque
        point du maillage.

    'TEMPERAT' mot cle ( doit preceder CHPO2)

    CHPO2 nom d'un objet de type CHPOIN contenant la temperature en
        chaque point du maillage. Cette temperature est exprimee
        en degres Celsius.

    CHPO3 objet de type CHPOIN ayant une composante par espece
        chimique. Les noms ont 4 caracteres dont le premier est W
        suivi eventuellement de 0 ou 00 et du numero d'ordre dans
        la liste TAB1.DESCHI.IDY de l'identifiant concerne.
        CHPO3 contient pour chaque espece chimique la constante
        apparente de la loi d'action de masse en chaque
        point du maillage.

## LSOSFRAC [Multi-physique Multi-physique] (proc)
Methode LSOSFRAC
--------------- LIRSOSO

    Objet

 La methode LSOSFRAC charge un LISTREEL dans l'element
 %FRACTIO d'un objet (LIRSOSO)

## LSOSSOLI [Multi-physique Multi-physique] (proc)
Methode LSOSSOLI
---------------- OBJE

    Objet

 La methode LSOSSOLI charge un LISTENTI dans l'element
 %SOLID d'un objet (LIRSOSO)

## LSQF [Mathematiques Traitement]
Operateur LSQF

EVOL1 = LSQF EVOL2 N1 (MOT1 N2) ;

objet :

Operateur LSQF permet d'effectuer une modelisation de type Least-
Squares des signaux EVOL2 (comportant N courbes) que l'on stocke dans
EVOL1 (comportant N courbes).

N1 specifie le nombre minimal de points vise dans EVOL1.

Chaque signal de EVOL2 doit avoir un pas de temps constant.

options :

MOT1 (type MOT) vaut 'UNIF','OPTI' ou 'REDU':

'UNIF': chaque modelisation est effectuee sur un nombre de points
        proche de N1 en une seule passe.

'OPTI': chaque modelisation est effectuee sur un nombre de points
        proche de N1 de façon optimisee. N2 (type ENTIER) indique
        alors de combien d'intervalle de fonction originale peuvent
        bouger les points de modelisation.
        (ATENTION: cette option est non disponible)

'REDU': indique que chaque modelisation est effectuee sur une
        fraction de la grille originale. N2 (type ENTIER) indique
        alors le facteur de reduction. Le nombre de point minimal
        continue etre regle par N1.

## LTL [Mathematiques Autres]
Operateur LTL

FLOT1 = LTL LREEL1 (LREEL2 FLOT2 FLOT3) ;

objet :

Operateur LTL effectue le produit scalaire de LREEL1 par LREEL2
(de meme longueur que LREEL1) eventuellement pondere par FLOT2 et
 FLOT3.

Si LREEL2 n'est pas donne, alors implicitement LREEL2=LREEL1.

FLOT2 et FLOT3 valent 1 par defaut.

## LUMP [Mecanique Modele]
Operateur LUMP
--------------- CARA

|  1ere possibilite  |

  MASS1 = 'LUMP' MODL1 MAT1 ;

Objet :

l'operateur LUMP calcule les matrices masse diagonalisee (ou "lumpee")
des elements references par le modele argument. La methode de
diagonalisation depend de l'element considere.

  Commentaire :

  MODL1 : objet modele ( type MMODEL ).

  MAT1 : Champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES).

  MASS1 : Resultat de type RIGIDITE de sous-type MASSE.

  Remarque :

  Le support geometrique de MASS1 sera celui de MAT1.

  Le numero de l'harmonique utilise dans le cas d'une analyse en
  serie de Fourier est precise par la directive OPTION :

        OPTION MODE FOUR NN ;

  Les caracteristiques gemoetrique ne sont obligatoires que si la
  description geometrique de l'element ne peut se faire par le
  maillage, par exemple l'epaisseur d'elements de plaques ou les
  sections des barres, etc ..

|  2eme possibilite  |

  RIG2 = 'LUMP' RIG1 (LMOTS) ;

 Objet :

Fabrication de la matrice lumpee a partir d'une matrice complete

Commentaire :

 RIG2 : matrice diagonale resultat

 RIG1 : matrice originale a lumper

 Le terme diagonal de RIG2 est egal a :

  - au terme diagonal de RIG1 si il se rapporte a une inconnue
  dont le nom est contenu dans LMOTS ( type listmots)

  - a la somme des termes de la ligne sinon

## MAGN [Presentation Presentation]
        liste de operateurs ou procedures dediees aux calculs
        en ELECTRO_MAGNETISME
|  |
|  2D  PLAN OU AXISYMETRIQUE  Formulation en potentiel vecteur  |
|  3D  VOLUMIQUE  Formulation a deux potentiels SCALAIREs |
|  Potentiel total /  Potentiel reduit  |
|  materiaux  non lineaires isotropes ou orthotropes  |
|---------------------------------------------------------------------|
|  Calculs 2D plans ou axisymetriques  |
|  POT_VECT , DESCOUR , INDUCTIO ,PROI ( option poly ) ,FOR_CONT  |
|  FORBLOC , DDFOUR  ,  A_HOMO  |
|---------------------------------------------------------------------|
|  Calculs 3D  |
|  BIOT  , POTSCAL , COUR3D  |
|---------------------------------------------------------------------|
|  Commun  au 2D et 3D  |
|  H_B  ,  MAG_NLIN  |

## MAG_NLIN [Magnetostatique Magnetostatique] (proc)
   Procedure MAG_NLIN

       MAG_NLIN TABB

    Objet :

    Calcul du potentiel vecteur ou du potentiel scalaire
    en non lineaire pour les problemes de magnetostatique
    en 2D potentiel vecteur ou 3D potentiel scalaire

    Commentaires :

    Une partie des arguments de la table TABB sont construits par
    un passage prealable dans les procedure POT_VECT ou POT_CSAL.

    Arguments additionnels specifiques de la procedure MAG_NLIN

    TABB objet de type table avec les indices suivants
        ecrits en toutes lettres

Obligatoires :

     'SOUSTYPE' THERMIQUE
     'EVOCOND' Evolution de Mu cree par la procedure H_B
        qui rend la courbe ad hoc pour POT_VECT ou
        POT_SCAL

Optionnel :

     'CRITERE' Ccritere de convergenve (10E-5 par defaut)
     'OME' Coef amortissement oscillations 0< OME < 1.
        pour le 2D principalement
     'NITER' Reactualisation de la conductivite toutes les
        NITER iterations (NITER=1 par defaut)
     'NIVEAU' Niveau des messages (NIVEAU=0 par defaut)
     'ITERMAX' Nonmbre d'iterations maximum
        (ITERMAX=10 par defaut)
Arguments fabriques dans les appels soit de POT_VECT soit de
POT_SCAL

     'FLUX' Flux equivallent
     'CLIM' Matrice de blocage (cree par BLOQUE T )
     'IMPOSE' Valeurs imposees (Cree par DEPI )
     'RIGCON ' Raideur constante
     'RIGFER ' Raideur variable

  ETAB contient en sortie : :

     'POTENTIEL' Potentiel resultat

## MAILSTRU [Maillage Surfaces] (proc)
    Procedure MAILSTRU

    GEO2 = MAILSTRU GEO1 FLOT1 ;

    Objet :

    La procedur MAILSTRU permet a partir d'un contour GEO1 de fabriquer
un maillage structure. La densite de maillage est definie par FLOT1 et
le type d'elements fabriques est le type courant defini dans OPTION.

Cette procedure ne marche que pour des elements de surface et le
resultat est de type MAILLAGE.

## MAILTOPO [Maillage Autres] (proc)
Procedure MAILTOPO
------------------ INDI

MAIL1 (METR1) = MAILTOPO | 'TRIA' MAIL2  | (METR2) ...
        | 'REMA' MAIL3 (MAIL4) |

        ... | ('AJNO') | ('IPOL') (TAB1) ;
        |  'NOAJ'  |
Objet :

Cette procédure n'est pas destinee a etre appelee par l'utilisateur
(voir operateurs TRIA et REMA).
Elle implemente un algorithme topologique de génération ('TRIA') ou
d'optimisation ('REMA') d'un maillage de simplex anisotrope du a T.
Coupez et al. (voir bibliographie ci-apres)

Commentaire :

  MAIL1 : maillage genere (type MAILLAGE)

  METR1 : si le mot-cle 'IPOL' est donne, METR1 (type CHPOINT) est
        la metrique interpolee sur le nouveau maillage MAIL1

  MAIL2 : bord du maillage a generer (type MAILLAGE)

  MAIL3 : maillage a optimiser (type MAILLAGE)

  MAIL4 : partie du bord de MAIL3 que le mailleur ne doit pas
        modifier (par defaut le mailleur peut retirer ou ajouter
        des noeuds sur les parties planes du bord de MAIL3)

  METR2 : objet de type FLOTTANT ou CHPOINT
        Si METR2 est de type FLOTTANT, il s'agit de la taille
        d'arete voulue (densite)
        Si METR2 est de type CHPOINT, il s'agit de l'inverse
        de la metrique voulue (unite : longueur^-2)

  TAB1 : objet optionnel de type TABLE dont les indices sont des
        parametres d'entree ou de sortie du mailleur
        Entree :
        TAB1 . 'debug' = 0..2 ; (0 par defaut)
        Niveau d'information
        TAB1 . 'graph' = faux..vrai ; (faux par defaut)
        Sortie de graphiques
        TAB1 . 'id_cas' = MOT1 ;
        Chaine de caracteres decrivant le cas
        TAB1 . 'max_iter' = ENTI1 ; (100 par defaut)
        Nombre d'iterations maximum de l'algorithme
        TAB1 . 'precrel_volume' = FLOT1 ; (1.D-11 par defaut)
        Precision relative en-dessous de laquelle un element
        est considere comme ayant un volume nul
        TAB1 . 'precrel_qualite' = FLOT1 ; (1.D-2 par defaut)
        Precision relative en-dessous de laquelle deux
        elements sont consideres comme ayant une qualite
        identique
        TAB1 . 'verif' = 0..2 ; (0 par defaut)
        Niveau de verification (debug) dans l'operateur
        appele (OPTO)
        TAB1 . 'impr_segadj' = 0..1 ; (0 par defaut)
        Impressions (debug) lors des ajustements de segments
        dans l'operateur appele (OPTO)
        Sortie :
        TAB1 . 'curtopo' = MAIL1 ;
        Maillage courant obtenu par l'algorithme
        TAB1 . 'dvol' = FLOT1 ;
        Difference entre le volume du maillage courant et le
        volume souhaite
        TAB1 . 'nnul' = ENTI1 ;
        Nombre d'elements du maillage courant ayant un volume
        nul
        TAB1 . 'miq' = FLOT1 ;
        Qualite minimum (cf. operateur INDI) des elements du
        maillage courant
        TAB1 . 'moq' = FLOT1 ;
        Qualite moyenne des elements du maillage courant
        TAB1 . 'maq' = FLOT1 ;
        Qualite maximal des elements du maillage courant

Remarques :

 1) Si la metrique voulue est isotrope, le nom de composante est G.
    Si la metrique voulue est anisotrope, les noms des composantes
    sont : G11, G21, G22, (G31, G32, G33 en 3D)

 2) Si le mot-clef 'AJNO' (par defaut) est donne, le mailleur peut
    generer de nouveaux noeuds.
    Si le mot-clef 'NOAJ' est donne, le mailleur ne genere pas de
    nouveaux noeuds.

Bibliographie :

@article{author = {Coupez, Thierry},
     title = {Generation de maillage et adaptation de maillage par
        optimisation locale},
     journal = {Revue Européenne des Éléments Finis},
     volume = {9}, number = {4}, pages = {403-423}, year = {2000},
     doi = {10.1080/12506559.2000.10511454}}

@PhdThesis{author = {Cyril Gruau},
       title = {Generation de métriques pour adaptation anisotrope
        de maillage, application à la mise en forme des matériaux},
        school = {ENSMP}, year = {2004}}

@article{author = "Cyril Gruau and Thierry Coupez",
     title = "3D tetrahedral, unstructured and anisotropic mesh
       generation with adaptation to natural and multidomain metric",
     journal = "Computer Methods in Applied Mechanics and Engineering",
     volume = "194", number = "48 - 49", pages = "4951 - 4976",
     year = "2005",
     doi = "10.1016/j.cma.2004.11.020"}

## MAILVORO [—] (proc)
Procedure MAILVORO

TAB2 = MAILVORO TAB1 ENV1 (NBDIV) (COEF1) ('COUL') ;

Objet :

La procedure MAILVORO realise le maillage volumique en 3D
(surfacique en 2D) d'une partition de Voronoi.

Commentaires :

Entree :

TAB1 = objet TABLE, issue de l'appel de l'operateur VORO, qui
        decrit une partition de Voronoi (voir notice VORO) ;

ENV1 = objet MAILLAGE, enveloppe ferme, oriente, connexe
        et constitue d'elements TRI3, servant a delimiter
        la partition de Voronoi ;

NBDIV = objet ENTIER, valeur cible du nombre d'elements par diametre
        de cellule, fixee par defaut a 6 ;

COEF1 = objet FLOTTANT, coefficient, fixe par defaut a 1/3,
        intervenant dans le calcul du critere d'elimination des
        petites aretes de la partition ;

'COUL' = permet de colorier le maillage de chaque cellule.
        La couleur de chaque cellule est choisie aleatoirement et
        est differente de celles de ces voisines.

Sortie :

TAB2 = objet de type TABLE decrivant le maillage de la partition
       de Vornoi.
*) Descriptif de la table TAB2 :

   TAB2 . 'MAIL' = MAILLAGE global, elements de type TET4 en 3D
        (TRI3 en 2D) ;
   TAB2 . 'CELL' = TABLE decrivant le maillage des cellules ;
   TAB2 . 'FACS' = TABLE decrivant le maillage des faces ;
   TAB2 . 'ARTS' = TABLE decrivant le maillage des aretes ;

*) Descriptif de l'indice TAB2 . 'CELL' :

   TAB2 . 'CELL' = TABLE contenant N indices de type POINT decrivant
        les centres des N cellules de la partition.

   TAB2 . 'CELL' . Pk . 'MAIL' = MAILLAGE de la cellule de centre Pk
        (elements de type TET4 en 3D)
        (elements de type TRI3 en 2D).
   TAB2 . 'CELL' . Pk . 'FACS' = LISTENTI, liste des numeros des
        faces de la cellule de centre Pk.
   TAB2 . 'CELL' . Pk . 'VOIS' = MAILLAGE des centres voisins de
        la cellule de centre Pk (elements POI1).
   TAB2 . 'CELL' . Pk . 'COUL' = MOT decrivant la couleur associee
        a la cellule de centre Pk.

*) Descriptif de l'indice TAB2 . 'FACS' (en 3D seulement) :

   TAB2 . 'FACS' = TABLE contenant M indices de type ENTIER
        decrivant les numeros des M faces de la partition.

   TAB2 . 'FACS' . i . 'MAIL' = MAILLAGE de la face numero i
        (elements de type TRI3).
   TAB2 . 'FACS' . i . 'ARTS' = LISTENTI, liste des numeros des
        aretes du contour de la face numero i.

*) Descriptif de l'indice TAB2 . 'ARTS' :

   TAB2 . 'ARTS' = TABLE contenant P indices de type ENTIER
        decrivant les numeros des P aretes de la partition.

   TAB2 . 'ARTS' . j = MAILLAGE de l'arete numero j
        (elements de type SEG2).

## MANU [Langage Objets]
    Operateur MANUEL

    Objet :

    L'operateur MANU permet de creer simplement des objets de type :
    MAILLAGE, CHPOINT, SOLUTION, RIGIDITE, MCHAML.

CHAP{MAILLAGE}

    GEO1 = MANU MOT1 | (POIN1 POIN2 . . .) | (COUL1) ;
        | GEO2  |

    Objet :

    L'operateur MANU construit, a partir d'une liste de points ou des
    points d'un autre maillage, un maillage forme par ces points,
    constitue d'elements dont le type est precise et de la couleur
    requise.

    Commentaire :

    MOT1 : type des elements (type MOT)

    POINTi : liste des points (type POINT)

    GEO2 : maillage (type MAILLAGE)

    COUL1 : couleur requise (type MOT)
        si la couleur n'est pas precisee, la couleur par defaut est
        utilisee

    GEO1 : objet resultat (type MAILLAGE)

    Exemple : NEWTR = MANU TRI3 ROSE ORIGIN (BASE POIN FINAL) (NOEU 12);

    Remarque : l'element MULT utilise dans le support des matrices
    de rigidite comportant des multiplicateurs de Lagrange est limite
    a 99 noeuds

CHAP{CHPOINT}

    CHPO1 = MANU  'CHPO' GEO1 | LMOT1  LREE1  |
        |  |
        |(ENTI1) MOT1 VAL1  MOT2 VAL2 |
        |  ---------  --------- |
        |  |___________|  |
        |  ENTI1 fois  |
        ('TITRE' MOT3)
        ('NATURE' MOT4) ;

    Objet :

    L'operateur MANU avec le mot-cle 'CHPO' construit un champ par point

    Commentaires :

    CHPO1 : objet resultat (type CHPOINT)

    GEO1 : support geometrique (type POINT ou MAILLAGE)

    'TITRE' : mot-cle (type MOT) suivi de
    MOT3 : titre donne au champ (type MOT)

    'NATURE': mot-cle (type MOT) suivi de
    MOT4 : mot-cle attribuant le nature du champ ('INDETERMINE'
        ou 'DIFFUS' ou 'DISCRET') ; par defaut la nature est
        indeteterminee

    SYNTAXE 1

    LMOT1 : liste des noms de composantes (type LISTMOTS)

    LREE1 : valeur associee a chaque composante, affectee a tous les
        noeuds de GEO1 (type LISTREEL)

    SYNTAXE 2

    ENTI1 : nombre de composantes (type entier). S'il n'est pas
        specifie, lit tous les couples MOTi VALi qui suivent

    MOTi : nom des composantes (type MOT) limite a 4 caracteres

    VALi : liste des valeurs affectee a chaque noeud de GEO1 pour la
        composante MOTi (type LISTREEL ou FLOTTANT)

    Remarques :

    La syntaxe 1 permet de creer des champs uniformes uniquement,
    tandis que la syntaxe 2 permet de creer des champs uniformes
    (VALi de type ENTIER ou FLOTTANT) ou variables (VALi de type LISTREEL).

    Pour la syntaxe 1, si LREE1 est plus court que LMOT1, les
    composantes en surplus sont creees mais initialisees a zero.

    Pour la syntaxe 2, si VALi est de type LISTREEL, alors GEO1 doit
    necessairement etre de type POI1 et VALi doit comporter autant de
    valeurs qu'il y a d'elements dans GEO1 (qu'il y ait des noeuds
    multiples ou non).

    Si le maillage GEO1 n'est pas de type POI1, ils sera automatiquement
    converti, avec chaque noeud n'apparaissant qu'une seule fois.

    Si le maillage GEO1 est deja de type POI1, les eventuels noeuds
    multiples vont etre fusionnes pour pouvoir servir de support au
    CHPOINT. C'est l'attribut NATUre qui regit le choix de la valeur
    retenue pour ces noeuds-ci :
    - DIFFUS : les doublons d'un meme noeud doivent avoir la meme valeur
    - DISCRET : les valeurs definies pour un meme noeud sont sommees

    On peut fournir la nature et le titre indifferemment apres le
    mot-clef 'CHPO' ou en fin de ligne, mais dans ce dernier cas, il
    est necessaire d'avoir specifie le nombre de composantes ENTI1.

    Exemples :

    Creation d'un champ discret avec 2 composantes uniformes :

       a) CHPO1 = MANU 'CHPO' GEO1 2 'UX' 1 'UY' 2.5 'NATURE' 'DISC' ;

        = MANU 'CHPO' GEO1 ('MOTS' 'UX' 'UY')
        ('PROG' 1 2.5 ) 'NATURE' 'DISC' ;

    Specification du titre d'un champ avec 1 composante uniforme :

       b) CHPO1 = MANU 'CHPO' 'TITRE' 'Densite' GEO1 'RHO' 1.5 ;

        = MANU 'CHPO' GEO1 1 'RHO' 1.5 'TITRE' 'Densite' ;

    Creation d'un champ avec 1 composante variable :

       c) CHPO1 = MANU 'CHPO' GEO1 'FX' (PROG 1.1 PAS 0.1 2.9) ;

    Creation de champs sur un maillage de 6 noeuds dont seulement 3
    sont distincts :

       d) CHPO1 = MANU 'CHPO' GEO1 'UX' 10. 'NATURE' 'DIFF' ;
        CHPO2 = MANU 'CHPO' GEO1 'UX' 10. 'NATURE' 'DISC' ;

        GEO1 => NOEUDS 4 7 7 1 7 4
        CHPO1 => NOEUDS 1 4 7
        VALEURS 10. 10. 10.
        CHPO2 => NOEUDS 1 4 7
        VALEURS 10. 20. 30.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## MAPP [Mathematiques Autres]
    Operateur MAPP

    EVOL1 = MAPP (COUL1) EVOL2 EVOL3 EVOL4 ;

    Objet :

    L'operateur MAPP construit une carte de Poincare.

    Commentaire :

    Cette carte est constituee d'un ensemble de points tires d'un espace
des phases d'un noeud du maillage etudie; les instants correspondants
@ ces points sont ceux oº un noeud de choc entre en contact avec la
structure voisine.

    COUL1 : couleur choisie (blanc par defaut)(type MOT)

    EVOL2 : forces de liaison sur le noeud de choc (type EVOLUTION)

    EVOL3 : liste des deplacements du noeud etudie (type EVOLUTION)

    EVOL4 : liste des vitesses du noeud etudie (type EVOLUTION)

    EVOL1 : points de la carte de Poincare (type EVOLUTION)

## MASQ [Mathematiques Autres]
Operateur MASQUE
---------------- SIGN

RESU1 = OBJET1  MASQ  |'SUPERIEUR' | ('SOMME')  | ENTI1  | ;
        |'EGSUPE'  |  | FLOT1  |
        |'EGALE'  |  | OBJET2 |
        |'EGINFE'  |
        |'INFERIEUR' |
        |'DIFFERENT' |
        |
        |'COMPRIS'  ('SOMME') | ENTI1  ENTI2  | ;
        |  | FLOT1  FLOT2  |
        |  | OBJET2 OBJET3 |
        |
        |'EXISTE'  (MOT1) ;

Objet :

L'operateur MASQUE fabrique un objet de meme type que OBJET1 dont
les valeurs sont des 1. ou des 0.

Si la relation algebrique (mots-clés 'SUPERIEUR', 'EGSUPE', ... )
ou la condition d'existence (mot-clé 'EXISTE') est verifiee,
alors la valeur retournee est 1., sinon elle vaut 0.

Pour les tests algebriques, chaque valeur de OBJET1 est comparee a
une valeur (ENTI1 ou FLOT1) ou a la valeur correspondante dans un
objet (OBJET2) de meme type que OBJET1.

Si le mot 'SOMME' est employe, RESU1 est la somme des 0. et des 1.,
sinon RESU1 est l'objet de meme type qu'OBJET1, contenant les 0. et
les 1.

Le test d'existence ne s'applique qu'aux objets de type MCHAML.

Commentaire :

OBJET1 : objet de type CHPOINT, LISTREEL, LISTENTI, MCHAML

OBJET2 : objet de meme type que OBJET1

OBJET3 : borne superieure (option 'COMPRIS') de OBJET1 lorsque
        celui-ci est de type CHPOINT ou MCHAML (meme type que
        OBJET1)

ENTI1 : nombre avec lequel sont comparees les valeurs de OBJET1
        lorsque celui-ci est de type LISTENTI (type ENTIER)

ENTI2 : borne superieure (option 'COMPRIS') de OBJET1 lorsque
        celui-ci est de type LISTENTI (type ENTIER)

FLOT1 : nombre avec lequel sont comparees les valeurs de OBJET1
        lorsque celui-ci est de type CHPOINT, LISTREEL ou MCHAML
        (type FLOTTANT)

FLOT1 : borne superieure (option 'COMPRIS') de OBJET1 lorsque
        celui-ci est de type LISTREEL (type FLOTTANT)

MOT1 : nom de la composante dont on veut tester l'existence
        (type MOT). En son absence toutes les composantes presentes
        dans le MCHAML sont testees.

RESU1 : objet resultat de meme type que OBJET1 sauf si le mot-cle
        'SOMME' est utilise auquel cas RESU1 est de type ENTIER

Remarque :

Si OBJET1 est un CHPOINT, alors le resultat de type CHPOINT aura le
meme support maillage de POI1.

Si OBJET1 et OBJET2 sont deux CHPOINTs, on rappelle que si OBJET2
n'est pas explicitement defini pour certains noeuds de OBJET1, sa
valeur en ces noeuds est implicitement 0. par convention.

## MASS [Mecanique Modele]
Operateur MASSE
--------------- LUMP MDIA

Objet :

l'operateur MASSE calcule les matrices de masse dans differents cas.

| Élements finis  |

  MASS1 = MASSE MODL1 MAT1 ;

  Commentaire :

  MODL1 : objet modele ( type MMODEL ).

  MAT1 : Champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES).

  MASS1 : Resultat de type RIGIDITE de sous-type MASSE.

  Remarque :

  Le support geometrique de MASS1 sera celui de MAT1.

  Le numero de l'harmonique utilise dans le cas d'une analyse en
  serie de Fourier est precise par la directive OPTION :

        OPTION MODE FOUR NN ;

  Les caracteristiques CAR1 ne sont obligatoires que si la
  description geometrique de l'element ne peut se faire par le
  maillage, par exemple l'epaisseur d'elements de plaques ou les
  sections des barres, etc ..
  Leur support geometrique doit etre inclus dans celui de MAT1.
  Si on met CAR1, il faut le mettre apres MAT1.

| MASSES ADDITIONNELLES  |

  MASS1 = MASSE  |( 'DEPL' ) ( 'ROTA' )|  FLOT1  GEO1 ;
        |  MOTi ...  |

  Commentaire :

 'DEPL' : mot-cle pour designer toutes les translations

 'ROTA' : mot-cle pour designer toutes les rotations

  MOTi : un ou plusieurs noms (type MOT) designant les degres
        de liberte concernes (dans ce cas ne pas se servir
        des 2 mots-cles precedents )

  Les noms des degres de liberte possibles sont :

  pour un calcul en MODE PLAN CONT : UX UY
  pour un calcul en MODE PLAN DEFO : UX UY
  pour un calcul en MODE AXIS : UR UZ RT
  pour un calcul en MODE FOUR : UR UZ UT RT
  pour un calcul en MODE TRID : UX UY UZ RX RY RZ

  FLOT1 : masse additionnelle (type FLOTTANT)

  GEO1 : objet geometrique oº seront ajoutees les masses
        (type POINT ou MAILLAGE).

  MASS1 : matrice masse (type RIGIDITE, sous-type MASSE).

| ANALYSE MODALE  |

  MASS2 = MASSE BAS1 ;
  MASS3 = MASSE SOL1 ;
  MASS4 = MASSE SOL2 STRU1 ;
  MASS5 = MASSE SOL1 SOL2 STRU1 ;
  MASS6 = MASSE TAB1 ;

  MASS7 = MASSE TAB2 (TAB3) RIG1 ;
  Commentaire :

  MASS2 : ensemble des matrices masse (type RIGIDITE, sous-type
        MASSE) s'appuyant sur la base modale BAS1

  BAS1 : base modale support (type BASEMODA)

  MASS3 : masse due aux modes (masses generalisees)(type RIGIDITE,
        sous-type MASSE)

  MASS4 : masse due au couplage des solutions statiques sur une
        structure (type RIGIDITE, sous-type MASSE)

  MASS5 : masse due au couplage des solutions statiques et des modes
        dans la structure (type RIGIDITE, sous-type MASSE)

  SOL1 : modes de la structure (type SOLUTION, sous-type MODE)

  SOL2 : solutions statiques (type SOLUTION, sous-type SOLUSTAT)

  STRU1 : structure elementaire (type STRUCTUR).

  MASS6 : masse due aux modes (masses generalisees)(type RIGIDITE,
        sous-type MASSE) contenus dans l'objet TAB1 (type TABLE
        de sous-type 'BASE_DE_MODES').

  MASS7 : type RIGIDITE, sous type MASSE, inertie dans la base des
        deformees listees dans TAB2, TABLE de sous-type
        'BASE_MODALE' ou bien 'LIAISONS_STATIQUES'. Lorsque TAB3
        est specifie, de sorte que ces deux sous-types
        apparaissent en argument, les termes de couplage sont
        egalement calcules.

  RIG1 : type RIGIDITE, sous-type MASSE, inertie exprimee dans la
        base initiale

Remarque :

Les supports geometriques de MASS2, MASS3, MASS4, MASS5 contiennent
les points associes aux modes ou aux liaisons definies entre les
structures. On associe la composante 'ALFA' au mode, 'BETA' a une
liaison sur des points libres, 'FBET' a une liaison sur des noeuds
bloques, de sous-type MODE.

Le support geometrique de MASS7 contient les points associes aux
deformees statiques ou modales. Les composantes 'BETA', duale 'FBET'
sont relatives aux premieres, 'ALFA', duale 'FALF' aux secondes.

## MATOUTIL [—] (proc)
Procedure MATOUTIL

Objet :

"MAilTOpo UTILitaires"

Des utililitaires utilises par la procedure MAILTOPO.

## MATP [Multi-physique Multi-physique]
    Operateur MATP

    RIG2 = MATP MODE1 RIG1 (TAB2) ;

    Objet :

    L'operateur MATP (MAtrice en Trace de charge TH) permet la
construction des matrices elementaires du systeme matriciel en
trace de charge dans le cadre de la resolution des equations
de DARCY par une methode d'elements finis mixtes hybrides.

    Commentaire :

       MODE1 : Objet modele (type MMODEL) decrivant la formulation
        utilisee. On attend une formulation DARCY (cf. MODE).

       RIG1 : Objet rigidite de sous type MASSEHYB contenant les
        matrices masses elementaires pour les elements
        hybrides (cf. MHYB).

       TAB2 : Objet table de sous type DARCY_TRANSITOIRE contenant
        les conditions initiales et les coefficients pour le
        schema d'integration en temps dans le cas transitoire
        (cf procedure darcytra).

       RIG2 : Objet rigidite resultat de sous type MATP contenant
        les matrices elementaires du systeme final en TH.

## MATR [Fantome]
Opérateur MATR

Cet opérateur a été débranché.
Se reporter à l'opérateur MATE(RIAU).

## MAX1 [Mathematiques Autres]
    Operateur MAX1

        |('AVEC')|
    CHP1 = MAX1 CHP2 ( |  | LMOTS1 ) ;
        | 'SANS' |

    Objet :

    L'operateur MAX1 norme un objet en le divisant par son maximum (de
telle sorte que son plus grand terme soit exactement egal a 1.).

    On peut limiter la recherche du maximum a un sous-ensemble en donnant
la liste des noms de composantes a considerer (mot-cle 'AVEC') ou a
exclure (mot-cle 'SANS').

    Commentaire :

    CHP2 : objet a normer (type CHPOINT)

    LMOTS1 : liste des noms de composantes a considerer ou a exclure
        (type LISTMOTS)

    CHP1 : objet resultat de meme type que CHP2 (type CHPOINT)

## MAXI [Mathematiques Fonctions]
    Operateur MAXIMUM
    ----------------- POIN ELEM

CHAP{Maximum d'un objet}
PART{Syntaxe}
    OBJET1 =  MAXI  OBJET2  ('ABS')  ( |('AVEC')| LMOTS1 ) ;
        | 'SANS' |

PART{Objet}
    L'operateur MAXIMUM determine la plus grande valeur algebrique
OBJET1 d'un objet OBJET2, ou de la valeur absolue d'OBJET2 si le
mot-cle 'ABS' a ete donne.

    On peut limiter la recherche du maximum a un sous-ensemble d'OBJET2
en donnant la liste LMOTS1 (type LISTMOTS) des noms de composantes a
considerer (mot-cle 'AVEC') ou a exclure (mot-cle 'SANS') dans la
recherche du maximum.

    Types d'objets possibles :
    |  OBJET2  |  OBJET1  |
    |  CHPOINT  |  FLOTTANT  |
    |  LISTENTI  |  ENTIER  |
    |  LISTREEL  |  FLOTTANT  |
    |  MCHAML  |  FLOTTANT  |

PART{Remarques}
 1. La limitation a certaines composantes n'a pas de sens pour les
objets de type LISTENTI et LISTREEL.

 2. On peut aussi utiliser les operateurs POIN ou ELEM pour chercher
le lieu geometrique du maximum d'un champ.

CHAP{Maximum d'une EVOLUTION}
PART{Syntaxe}
    OBJET2 OBJET3 OBJET4 = MAXI OBJET1 ('ABS')

PART{Objet}
    L'operateur MAXIMUM determine le couple abscisse - ordonnee
    de plus grande valeur algebrique, ainsi que l'indice de ce
    couple pour un OBJET1 de type EVOLUTIO ne comportant qu'une
    seule courbe. Si le mot-cle 'ABS' a ete donne, il s'agit de
    l'ordonnee de plus grande valeur absolue.
    Le type d'OBJET2 est ENTIER, OBJET3 et OBJET4 sont de type
    FLOTTANT. En cas de multiplicite de l'ordonnee maximale,
    le couple de plus faible indice est renvoye.

    Si OBJET1 de type EVOLUTIO comprend plusieurs courbes,
    l'operateur construit par extension des objets
    OBJET2, type LISTENTI, OBJET3 et OBJET4, type LISTREEL.

PART{Remarques}
    Seules les EVOLUTIONs d'un LISTREEL en fonction d'un autre
    LISTREEL sont permises.

CHAP{Maximum de n ENTIERs ou FLOTTANTs}
PART{Syntaxe}
      XMAX = MAXI ('ABS') X1 X2 (... Xn)

PART{Objet}
    L'operateur MAXIMUM retourne dans XMAX le reel/entier
    maximum des termes X1, X2, ..., Xn
    (ou des termes |X1|, |X2|, ... |Xn|  si 'ABS est precise).

CHAP{Maximum de n objets}
PART{Syntaxe}
      OBJET3 = MAXI ('ABS') OBJET1 OBJET2 (OBJETi ...)

PART{Objet}
    L'operateur MAXIMUM crée un objet de meme type que OBJET1, OBJET2,
    OBJETi... en prenant la valeur maximum (eventuellement en valeur
    absolue), terme à terme, de OBJET1, OBJET2, OBJETi...

    Les types autorises sont LISTENTI, LISTREEL et CHPOINT. Pour les
    objets CHPOINTS, les composantes et maillages supports doivent
    etre identiques.

## MAYOTO [—] (proc)
        Procedure MAYOTO

        RES = MAYOTO  | SENB | TAB;
        |  |
        | CT  |
        |  |
        | CCP  |

        Objet:

        Cette procedure permet un maillage automatique
        d'eprouvettes SENB, CT, CCP .

        Commentaire:

En entree :

        SENB, CT, CCP mot cle indiquant le type d'eprouvette a mailler

        TAB : table indicee par des mots,contenant les parametres
        necessaires au maillage automatique de l'eprouvette
        (type TABLE):

        TAB.app: type de maillage proche de la fissure
        (=1 maillage rayonnant )
        (=0 maillage quadrille )

    - Pour une SENB:

        TAB.s : longueur de l'eprouvette (type FLOTTANT)
        TAB.b : largeur de l'eprouvette (type FLOTTANT)
        TAB.a : taille de la fissure (type FLOTTANT)
        TAB.k : coefficient de finesse du maillage (type ENTIER)

    - Pour une CT:

        TAB.b : cote de l'eprouvette (type FLOTTANT)
        TAB.a : longueur fissuree (type FLOTTANT)
        TAB.k : coefficient de finesse du maillage (type ENTIER)

    - Pour une CCP:

        TAB.h : demi largeur de l'eprouvette (type FLOTTANT)
        TAB.l : demi longueur de l'eprouvette (type FLOTTANT)
        TAB.lf:longueur fissuree (type FLOTTANT)

En sortie :

        RES : table contenant les resultats (type TABLE).

        Pour tous les types d'eprouvettes, la table contient les
        resultats suivants:

        RES.e : eprouvette maillee
        RES.p : point extremite de la fissure
        RES.f : levre(s) de la fissure

        Elle contient egalement des resultats particuliers a
        chaque type d'eprouvette :

    - Pour une SENB:

        RES.n : ligament de la fissure
        RES.i : point de chargement superieur en flexion 3 pts
        RES.u : point de chargement en bas a droite

    - Pour une CT:

        RES.i : point de chergement situe dans le trou de la partie
        superieure
        RES.m : point de chargement dans la partie inferieure
        RES.g : maillage des goupille permettant une meilleure
        repartition des contraintes et evitant la
        plastification
        RES.n : ligament de la fissure

    - Pour une CCP:

        RES.s : ligne en haut de l'eprouvette
        RES.o : cote de l'eprouvette
        RES.m : ligaments de la fissure
        RES.v : ligne de symetrie verticale

        Remarque
        Des donnees incompatibles entraineront un echec complet de
        la procedure.

## MDIA [Mecanique Resolution]
     Operateur MDIA

     Syntaxe EQEX (cf EQEX) :

     ... 'EQEX' ... 'OPTI' MOT1 MOT2
        'ZONE' MOD2
        'OPER' 'MDIA' OBJ1
        'INCO' MOT3 (MOT4)

     Objet :

     L'operateur MDIA discretise un terme lineaire dans une equation
scalaire ou vectorielle. Cet operateur permet le couplage lineaire
entre inconnues.

     Dans le cas d'une equation scalaire portant sur T, le terme
discretise est de la forme aT avec a coefficient scalaire par unite
de temps.

     Dans le cas d'un systeme d'equations le terme discretise peut
prendre une forme plus generale permettant de coupler deux inconnues.
Soit V l'inconnue sur laquelle porte l'equation consideree (inconnue
duale). Le terme discretise est de la forme aT avec T inconnue sur
laquelle porte le couplage (inconnue primale) et a coefficient scalaire
ou vectoriel suivant les dimensions de T et V.

     La convention de signe associee a ce terme est la suivante :
lorsque a et T sont positifs, T (resp. V) diminue.

     Cet operateur est appele par la procedure transitoire EXEC.
La syntaxe indiquee permet a l'utilisateur de construire a l'aide
de l'operateur EQEX les donnees necessaires a l'operateur.

     Commentaires :

    'OPTI' : Mot cle introduisant les options numeriques de MDIA
     MOT1 : Type de discretisation spatiale ('EF', 'VF' ou 'EFM1')
     MOT2 : Type de discretisation temporelle ('IMPL')

    'ZONE' : Mot cle introduisant les informations geometriques
     MOD2 : MODEL de sous-type 'NAVIER_STOKES' pour la zone ou
        s'applique MDIA

    'OPER' : Mot cle introduisant les donnees physiques associees
        a l'operateur dont le nom suit
    'MDIA' : Nom de l'operateur
     OBJ1 : Coefficient a (CHPOINT ou FLOTTANT ou POINT ou MOT)

    'INCO' : Mot cle introduisant le nom des inconnues primale et duale
     MOT3 : Nom de l'inconnue primale T
     MOT4 : Nom de l'inconnue duale V
     Lorsque primale et duale sont identiques, MOT4 est optionnel

     Resultats :

    - La matrice "masse" est stockee dans un MATRIK et rangee dans la
table TAB1 a l'indice de type MOT MATELM.
    - Aucun second-membre n'est cree.

     Remarques :

     1) Lorsque OBJ1 est de type MOT, l'operateur utilise le champ
contenu dans la table INCO a l'indice MOT indique.

     2) Le support geometrique (spg) des inconnues contient une des
classes de points de la table DOMAINE. Selon la formulation choisie
les compatibilites suivantes sont verifiees :
   - En formulation EF ou EFM1, le spg de la duale contient SOMMET
   - En formulation VF le spg de la duale contient CENTRE
   - lorsque les inconnues primale et duale sont differentes,
le spg de l'inconnue primale est CENTRE ou SOMMET.

     3) Dimensions et supports des donnees :

        |  D i m e n s i o n  |
        | duale V | primale T | coeff. a |
    a T dans V 1 1 1
    ->->
    a T dans V 1 IDIM IDIM
    -> ->
    a T dans V IDIM 1 IDIM
      -> ->
    a T dans V IDIM IDIM 1

    primale T S C S S C S = SOMMET
    duale V S C C C S C = CENTRE
    coeff a S C S C C

     4) L'utilisateur-programmeur developpant ses propres procedures
transitoire appellera MDIA suivant la syntaxe :
     MDIA TAB1 ;
avec TAB1 : Table de sous type EQEX contenant les informations
        physiques et numeriques de l'operateur MDIA. Cette
        table est construite par l'operateur EQEX.

## MDNRIS [Mathematiques Statistiques] (proc)
Procedure MDNRIS

  MDNRIS P*FLOTTANT;

Objet :
procedure auxiliaire appelee par FINVREPA

## MDRECOMB [Fluides Resolution] (proc)
   Procedure MDRECOMB

     MDRECOMB RXT ;

   OBJET :

La procedure MDRECOMB est une procedure interne appelee par EXECRXT.
Cette procedure n'est executee qu'en presence de recombineurs. Celle-ci
permet d'effectuer les bilans 0D (masse et energie) entre les especes
qui entrent dans le recombineur et les especes qui sortent.

   Commentaires

   RXT : objet de type TABLE

## MEC1 [Presentation Presentation]
        CALCUL ELASTIQUE EN MECANIQUE

 La liste des objets manipules dans le cadre d'un calcul elastique en
mecanique est :

|  MMODEL  : formulation et modele de comportement  |
|  MCHAML  : Champ defini a l'interieur des elements  |
|  CHPOINT  : Champ defini aux noeuds du maillage  |
|  DEFORME  : Deformee d'un maillage sous un champ de deplacement  |
|  ENTIER  : Nombre entier  |
|  FLOTTANT : Nombre flottant  |
|  LISTENTI : Liste d'entiers (operateur LECT)  |
|  LISTREEL : Liste de reels  (operateur PROG)  |
|  LOGIQUE  : variable logique (vrai-faux)  |
|  MAILLAGE : Geometrie de la structure etudiee  |
|  MOT  : Mot  |
|  RIGIDITE : Matrice de raideurs et de blocages  |
|  SOLUTION : Famille de mode propre  |
|  VECTEUR  : Fleches (destine a etre trace)  |

## MEC2 [Presentation Presentation]
* *
* Exemple simple de calcul mecanique elastique *
* fonctionnant avec les anciennes structures AFFECT,MODELE,CHAMELEM *
* *
* Definition des options
*
        OPTI DIME 3 ELEM CU20 MODEL TRIDIM ; DENS 10 ;
*
* Maillage d'une barre de 5 elements CU20
*
  P1 = 0 0 0 ; P2 = 10 0 0 ; LI= P1 D 1 P2 ; SUB=LI TRAN (0 10 0) ;
   TOTAL = SUB VOLU TRAN (0 0 50) COUL JAUN ; SUH = TOTAL FACE 2 ;
     LIH = SUH COTE 2 ; TRAC TOTAL CACH (1000 -2000 1000) QUAL ;
*
* Formulation, materiau defini a l'aide de
* la procedure ACIER (voir operateur MATE)
*
        OBJMOD = MODELE TOTAL MECANIQUE ELASTIQUE CU20 ;
        CARM = ACIER A316L OBJMOD ;
*
* Conditions de blocages
*
        ENC1 = BLOQ UZ SUB ;
        ENC2 = BLOQ UY LI ; ENC3 = BLOQ UX P1 ;
*
* Blocage pour deplacements imposes
*
        ENC4 = BLOQ UZ SUH ;
        ENC = ENC1 ET ENC2 ET ENC3 ;
*
* Raideur totale
*
        RIG = (RIGI CARM OBJMOD) ET ENC ET ENC4 ;
*
* Valeur des deplacements imposes
*
        FEXT = DEPI ENC4 1E-9 ;
*
* Force ponctuelle et force totale
*
        FNOD = FORCE LIH (0 1000 0) ; FTOT = FEXT ET FNOD ;
*
* Resolution pour obtenir les deplacements
*
        DEP = RESOU RIG FTOT ;
*
* Vecteur force et reaction
*
        VEF = VECTEUR FTOT 0.03 FX FY FZ ROUG ;
        REA = REAC (ENC4 ET ENC) DEP ;
        VER = VECTEUR REA 0.01 FX FY FZ BLEU ;
*
* Contraintes et vonmises
*
        SSI = SIGMA DEP CARM OBJMOD; VM = VMIS SSI ;
*
* Deformee et trace
*
        DEF = DEFO TOTAL DEP 50 (VEF ET VER) VERT ;
        TRAC DEF VM (1000 -2000 1000) ;
        FIN ;

## MEC3 [Presentation Presentation]
* *
* Exemple simple de calcul mecanique elastique *
* fonctionnant avec les nouvelles structures MMODEL et MCHAML *
* *
* Definition des options
*
        OPTI DIME 3 ELEM CU20 MODEL TRIDIM ; DENS 10 ;
*
* Maillage d'une barre de 5 elements CU20
*
  P1 = 0 0 0 ; P2 = 10 0 0 ; LI= P1 D 1 P2 ; SUB=LI TRAN (0 10 0) ;
   TOTAL = SUB VOLU TRAN (0 0 50) COUL JAUN ; SUH = TOTAL FACE 2 ;
     LIH = SUH COTE 2 ; TRAC TOTAL CACH (1000 -2000 1000) QUAL ;
*
* Formulation, materiau defini a l'aide de
*
   MODL1 = MODL TOTAL MECANIQUE ELASTIQUE CU20 ;
    CARM = MATR MODL1 'YOUN' 2.E11 'NU' 0.3 'RHO' 7800. 'ALPH' 12.E-6 ;
*
* Conditions de blocages
*
        ENC1 = BLOQ UZ SUB ;
        ENC2 = BLOQ UY LI ; ENC3 = BLOQ UX P1 ;
*
* Blocage pour deplacements imposes
*
        ENC4 = BLOQ UZ SUH ;
        ENC = ENC1 ET ENC2 ET ENC3 ;
*
* Raideur totale
*
        RIG = (RIGI MODL1 CARM) ET ENC ET ENC4 ;
*
* Valeur des deplacements imposes
*
        FEXT = DEPI ENC4 1E-9 ;
*
* Force ponctuelle et force totale
*
        FNOD = FORCE LIH (0 1000 0) ; FTOT = FEXT ET FNOD ;
*
* Resolution pour obtenir les deplacements
*
        DEP = RESOU RIG FTOT ;
*
* Vecteur force et reaction
*
        VEF = VECTEUR FTOT 0.03 FX FY FZ ROUG ;
        REA = REAC (ENC4 ET ENC) DEP ;
        VER = VECTEUR REA 0.01 FX FY FZ BLEU ;
*
* Contraintes et vonmises
*
        SSI = SIGMA MODL1 DEP CARM ; VM = VMIS MODL1 SSI ;
*
* Deformee et trace
*
        DEF = DEFO TOTAL DEP 50 (VEF ET VER) VERT ;
        TRAC DEF MODL1 VM (1000 -2000 1000) ;
        FIN ;

## MECA [Presentation Presentation]
        CALCUL ELASTIQUE EN MECANIQUE

 La liste des operateurs utiles pour faire un calcul elastique en
mecanique est :

|  OPTION  : Declaration des options generales de calcul  |
|  ET  : Permet d'assembler des proprietes decrites par zones:  |
|  maillages, champs, raideurs ...  |
|  MODELE  : Definition du modele de comportement pour le materiau  |
|  MATER  : Description des proprietes du materiau  |
|  CARAC  : Description des caracteristiques supplementaires  |
|  epaisseur inerties ....  |
|  RIGIDITE : Construction des matrices de raideur des elements  |
|  MASSE  : Construction des matrices de masse des elements  |
|  BLOQUE  : Description des blocages encastrements et deplacements  |
|  imposes  |
|  SYMTRIE  : Description des proprietes de symetrie de la structure  |
|  ANTISYMT : Description des proprietes d'antisymetrie  |
|  RELATION : Description des relations imposees entre inconnues du  |
|  probleme  |
|  DEPIMP  : Affection de valeurs aux deplacements imposees  |
|  FORCE  : Introduction de forces exterieures  |
|  MOMENT  : Introduction de moment  |
|  PRESSION : Calcule les forces generalisees dues a une pression  |
|  BSIGMA  : Fourni le champ de forces resultant de l'integration  |
|  d'un champ de contraintes  |
|  RESU  : Permet de connaitre la resultante d'un champ de forces  |
|  THETA  : Calcule les contraintes equivalentes dues a un champ de |
|  temperature  |
|  RESOU  : Calcul des deplacements a partir des forces et de la  |
|  raideur  |
|  VIBRATI  : Calcul de modes et frequences propres  |
|  TIRER  : Extraction de modes propres de l'objet solution  |
|  construit par VIBRATI  |
|  SIGMA  : Calcul des contraintes  |
|  VMIS  : Calcul de la contrainte equivalente  |
|  VECTEUR  : Construction d'un ensemble de vecteur pouvant etre  |
|  traces a partir d'un champ  |
|  DEFORME  : Construction de la deformee d'une structure pouvant  |
|  etre tracee  |
|  TRACE  : Trace de grandeurs sur des maillages  |
|  LIST  : Impressions de resultats  |
|  SAUVER  : Interruption du calcul  |
|  RESTITUER: Reprise du calcul  |

 Il existe une procedure CALCULER qui enchaine ces operations dans le
cadre d'un calcul simple. Apres avoir construit un maillage faire :
" CALCULER ;" puis repondre aux questions.

## MENA [Langage Base]
    Directive MENAGE
    ---------------- DETR

    MENAGE ('OBLI') (La_place_desiree) ;

    Objet :

    La directive MENAGE a pour effet de supprimer de la memoire les
informations perimees et inaccessibles.

    On peut indiquer apres MENAGE la place memoire (exprimee en nombre d
mots) (type ENTIER) dont on veut obtenir la disponibilite.

    En presence du mot OBLI le menage est effectivement execute, sinon cela
depend, de la place utilisee, de ...

    Remarque 1 :

    Elle trouve son interet dans l'ecriture de processus iteratifs qui
creent de nouveaux objets a chaque iteration. MENAGE appelee a la
fin du processus eliminera de la memoire les objets devenus obsoletes.

    Remarque 2 :

    Si apres l'emploi de MENAGE il apparait une erreur dans
GEMAT du type :

    Le pointeur designe un segment supprime

cela provient d'une erreur interne dans MENAGE qui ne prend pas
correctement en compte les objets manipules.

    Remarque 3 :

    La directive MENAGE verifie la validite de tous les objets
accessibles. L'emploi de l'operateur DETRUIRE peut creer des structures
incorrectes, oº un objet pointe sur d'autres objets detruits.
Ceci n'est pas genant, si on ne se sert plus de ces objets.
L'operateur MENAGE arretera l'execution en detectant de telles
structures incorrectes.

    Remarque 4 :

    La directive MENAGE peut demander beaucoup de temps pour verifier
si les objets sont perimes ou inaccessibles.

## MENU [Entree-Sortie Entree-Sortie]
    Operateur MENU

    OBJR = MENU MESSAGE | OBJ1 OBJ2 ... OBJN ;
        | LMOT1  ;

    Objet :

    L'operateur MENU propose un choix d'objets a l'utilisateur puis
retourne celui choisi. Ces noms peuvent etre mis sous forme d'une
 liste de mots

   OBJR : objet choisi par l'utilisateur.
   OBJ1 :
   OBJN : objets entre les quels effectuer un choix.

   LMOT1: LISTMOTS contenant les noms entre lesquels effectuer un choix.

   MESSAGE : Chaine de caracteres affichee sous le choix a effectuer.

    Remarque :

    N'a ete presentement teste qu'avec un affichage XWindow.

## MESM [Mecanique Resolution]
   Operateur MESM
   -------------- LIMEMECA

   TAB1 TAB2=MESM MODL1 RIGI1 |('TOUT')|;
        'ROTA' ;

    Objet :

    L'operateur MESM determine l'ensemble des mecanismes elementaires
de ruine associes a la structure definie par le modele MODL1 et les
bloquages RIGI1. Le calcul est bidimensionel et s'applique uniquement
a des maillages de poutre (element 'TIMO' ou 'POUT').

    Si l'option 'TOUT' est utilisee, on considere 3 modes de rupture
par element (2 en rotation aux extremites de l'element et 1
longitudinal) alors que l'option 'ROTA' se limite a 2 modes (2 en
rotation).

    Le resultat est contenu dans 2 tables TAB1 et TAB2, indexees
par un nombre entier indiquant le numero du mecanisme elementaire. TAB1
contient les CHPOINT de deplacement des modes de rupture et TAB2 les
MCHAML de deformations plastiques associes.

    Remarque :

    Cet operateur permet d'effectuer un calcul de charge limite par
l'approche cinematique (voir procedure LIMEMECA). On peut visualiser
les modes elementaires de rupture (voir procedure TRACMECA).

    Les MCHAML de deformations plastiques sont constants par elements.
Les nom des composantes sont: 'RZP1' (rotation plastique autour de
l'axe local Oz a l'extremite 1 de l'element, 'RZP2' (rotation plastique
a l'extremite 2 de l'element et, eventuellement, 'UP2' (ouverture
plastique dans l'axe de l'element).

    Attention :

    RIGI1 est une rigidite qui ne contient que des bloquages qui ne
peuvent s'appliquer qu'aux degres de libertes de MODL1. Cette rigidite
peut inclure des relations

## MESS [Entree-Sortie Entree-Sortie]
    Directive MESSAGE

    Objet :

    La directive MESSAGE permet d'editer sous forme de message une suite
d'objets. La syntaxe est celle de l'operateur CHAINE (appele en interne).

    Exemple :

        OBJET1 = MOT ' LA VALEUR DE PI EST :' ;
        P = 3.14159 ;
        MESSAGE OBJET1 P ;

## MESU [Mathematiques Autres]
     Operateur MESURE

    FLOT1 = MESURE GEO1 | ('LONG') ;
        | ('SURF') ;
        | ('VOLU') ;

    CHPO1 = MESURE GEO1 'DENS' ;

    Objet :

    L'operateur MESU calcule la mesure du maillage GEO1.
Par defaut, si GEO1 est une ligne MESU en calculera la longueur, si GEO1 est
une surface, MESU en calculera la surface, et si GEO1 est un volume MESU en
calculera le volume.

    Si GEO1 est une ligne fermee, le mot cle SURF permettra de calculer
l'aire de la surface limitee par GEO1. En 3D on obtiendra l'aire de la
surface projetee sur son plan moyen.

    Si GEO1 est une surface close, le mot cle VOLU permettra de calculer
le volume enclos dans GEO1.

    L'option DENS permet de mesurer la carte de densite du maillage
(taille moyenne des aretes des elements en chaque noeud).

## METH [Langage Methodes]
    Operateur METHODE

      OBJET1%METHODE NOMMETH1 METH1;

    Objet :

    L'operateur METHODE affecte a l'objet de type OBJET OBJET1 une
methode qui portera le nom NOMMETH1. Lors de l'appel de cette methode
sur l'objet la methode (procedure) METH1 sera executee.

      Commentaire :

      NOMMETH1 : on extrait de cet objet son nom.

      METH1 : est une methode qui existe deja, elle est creee
        par l'operateur DEBMETH.

## MFIL [Mathematiques Autres]
        CETTE OPERATEUR A ETE MIS GRACIEUSEMENT
        A DISPOSITION DE LA COMMUNAUTE CAST3M
        PAR Guenhael Le Quilliec(1) ET Thomas Fournier(2)
        (1) Laboratoire de Mecanique Gabriel Lame
 Universite de Tours, Universite d Orleans, INSA Centre Val de Loire
    Polytech Tours, 7 avenue Marcel Dassault, 37200 Tours, France
      (2) Stage au Laboratoire de Mecanique Gabriel Lame en 2020

    Operateur MFIL
    ______________ TOPOSURF
        TOPOFILT

    RIG1 = MFIL CHPO1 (FLOT1 (FLOT2 (FLOT3))) (MOT1 (MOT2)) ;

    Objet :

L'operateur MFIL cree une matrice de rigidite contenant pour chaque
noeud du maillage les poids de ses noeuds voisins a appliquer dans le
but de pouvoir filtrer (i.e. lisser / floutter) un champ par points en
le multipliant par cette matrice.

Si un noeud voisin se trouve a une distance D < FLOT1, son poids
(sa raideur) est alors calcule comme suit :
       (1.0 - (Rv / FLOT1))**FLOT2
       * valeur de CHPO1 du noeud voisin
       / somme des poids de tous les noeuds voisins
Enfin seuls les poids > FLOT3 sont conserves.

    En entree :

 CHPO1 : (CHPOINT) Champ par points de ponderation (e.g. champ des volumes)
        qui est utilise dans le calcul des poids (raideurs) de la matrice
        de sortie.
        Ce champ permet egalement de recuperer les noeuds sur lesquelles
        s'appliquera la matrice de rigidite de sortie.

 FLOT1 : (FLOTTANT) Rayon d'action du filtre au voisinage de chaque noeud.
        Cette donnee est facultative et est egale a 0.0 par defaut. Le
        filtre n'aura alors aucun effet.

 FLOT2 : (FLOTTANT) Exposant applique lors du calcul des poids.
        Cette donnee est facultative et est egale a 1.0 par defaut.

 FLOT3 : (FLOTTANT) Valeur comprise entre 0.0 et 1.0 au dela de laquelle les
        poids sont conserves.
        Cette donnee est facultative et est egale a 0.0 par defaut.

 MOT1 : (MOT) Nom des inconnues primales.
        Cette donnee est facultative et est egale a 'SCAL' par defaut.

 MOT2 : (MOT) Nom des inconnues duales.
        Cette donnee est facultative et est egale a la valeur de MOT1 par defaut.

    En sortie :

 RIG1 : (RIGIDITE) Matrice de rigidite.

    Exemples:

mfil.dgibi

## MHYB [—]
   Opérateur MHYB

    | 1-ère Fonction |

   RIG1 = MHYB MODE1 CAR1 ('DARCY') ;

   Objet :

   L'opérateur MHYB permet le calcul de l'inverse des 'matrices de
darcy' élémentaires pour les modèles utilisant des éléments finis
mixtes hybrides.

   Commentaire :

      MODE1 : Objet modèle (type MMODEL) décrivant la formulation
        utilisée (cf. MODE).

      CAR1 : Objet de type MCHAML de sous-type CARACTERISTIQUES;
        Caractéristiques physiques de la structure (cf. MATE).

      RIG1 : Objet rigidité résultat contenant l'inverse des
        'matrices de darcy' élémentaires.

   'DARCY' : mot clé correspondant au sous-type de l'objet RIG1.

    | 2-ème Fonction |

   RIG1 = MHYB MODE1 MOT1 ;

   Objet :

   L'opérateur MHYB permet le calcul des 'matrices masses élémentaires
pour les modèles utilisant des éléments finis mixtes hybrides.

      RIG1 : Objet rigidité résultat contenant les matrices masses
        élémentaires.

   'MASSE' : mot clé correspondant au sous-type de l'objet RIG1

## MINI [Mathematiques Fonctions]
    Operateur MINIMUM
    ----------------- POIN ELEM

CHAP{Minimum d'un objet}
PART{Syntaxe}
    OBJET1 =  MINI  OBJET2  ('ABS')  ( |('AVEC')| LMOTS1 ) ;
        | 'SANS' |

PART{Objet}
    L'operateur MINIMUM determine la plus petite valeur algebrique
OBJET1 d'un objet OBJET2, ou de la valeur absolue d'OBJET2 si le
mot-cle 'ABS' a ete donne.

    On peut limiter la recherche du minimum a un sous-ensemble d'OBJET2
en donnant la liste LMOTS1 (type LISTMOTS) des noms de composantes a
considerer (mot-cle 'AVEC') ou a exclure (mot-cle 'SANS') dans la
recherche du minimum.

    Types d'objets possibles :
    |  OBJET2  |  OBJET1  |
    |  CHPOINT  |  FLOTTANT  |
    |  LISTENTI  |  ENTIER  |
    |  LISTREEL  |  FLOTTANT  |
    |  MCHAML  |  FLOTTANT  |

PART{Remarques}
 1. La limitation a certaines composantes n'a pas de sens pour les
objets de type LISTENTI et LISTREEL.

 2. On peut aussi utiliser les operateurs POIN ou ELEM pour chercher
le lieu geometrique du minimum d'un champ.

CHAP{Minimum d'une EVOLUTION}
PART{Syntaxe}
    OBJET2 OBJET3 OBJET4 = MINI OBJET1 ('ABS')

PART{Objet}
    L'operateur MINIMUM determine le couple abscisse - ordonnee
    de plus petite valeur algebrique, ainsi que l'indice de ce
    couple pour un OBJET1 de type EVOLUTIO ne comportant qu'une
    seule courbe. Si le mot-cle 'ABS' a ete donne, il s'agit de
    l'ordonnee de plus petite valeur absolue.
    Le type d'OBJET2 est ENTIER, OBJET3 et OBJET4 sont de type
    FLOTTANT. En cas de multiplicite de l'ordonnee minimale,
    le couple de plus faible indice est renvoye.

    Si OBJET1 de type EVOLUTIO comprend plusieurs courbes,
    l'operateur construit par extension des objets
    OBJET2, type LISTENTI, OBJET3 et OBJET4, type LISTREEL.

PART{Remarques}
    Seules les EVOLUTIONs d'un LISTREEL en fonction d'un autre
    LISTREEL sont permises.

CHAP{Minimum de n ENTIERs ou FLOTTANTs}
PART{Syntaxe}
      XMIN = MINI ('ABS') X1 X2 (... Xn)

PART{Objet}
    L'operateur MINIMUM retourne dans XMIN le reel/entier
    minimum des termes X1, X2, ..., Xn
    (ou des termes |X1|, |X2|, ... |Xn|  si 'ABS est precise).

CHAP{Minimum de n objets}
PART{Syntaxe}
      OBJET3 = MINI ('ABS') OBJET1 OBJET2 (OBJETi ...)

PART{Objet}
    L'operateur MINIMUM crée un objet de meme type que OBJET1, OBJET2,
    OBJETi... en prenant la valeur minimum (eventuellement en valeur
    absolue), terme à terme, de OBJET1, OBJET2, OBJETi...

    Les types autorises sont LISTENTI, LISTREEL et CHPOINT. Pour les
    objets CHPOINTS, les composantes et maillages supports doivent
    etre identiques.

## MISE [—]
 Directive MISE

MISE TAB1 ;

 Objet :

 Operateur qui permet l'ecritures des fichiers des donnees pour le logiciel M

 Commentaire :

 Cette operateur est appellé par la procedure PREPMISS. Voir la notice PREPMI

## MISL [—]
 Directive MISL

MISL TAB1 ;

 Objet :

 Operateur qui permet la lecture de la sortie du logiciel MISS3D

 Commentaire :

 Cette operateur est appellé par la procedure POSTMISS et IMPDMISS. Voir les
 POSTMISS et IMPDMISS

## MIXE [—]
    Operateur MIXE

        CHE3 = MIXE MOD1 CHE1 CHE2 ;

    Objet :

    L'operateur MIXE construit un objet CHE3 de type MCHAML,
    qui selon les lois contenues par l'objet MOD1,
    combine avec les pondérations du champs
    de caractéristiques CHE1, de type MCHAML, associé à MOD1,
    les grandeurs physiques de memes noms pour différentes
    phases collectées dans CHE2, de type MCHAML ;
    un coefficient de CHE1 de nom MOT1 est relatif aux
    grandeurs de CHE2 associées à la phase de nom identique.

    MOD1 : type MMODEL, formulation 'MELANGE'

$$$$

## MOCA [Mathematiques Fonctions]
    Operateur MOCA
    -------------- LEVM

    RESU1 = MOCA LISTPARA LISTMESU LISTFONC LISTDERi (('POIDS' LISTPOI);

    Objet :

    Soit une fonction G connue en n points. On cherche a determiner les
parametres (a,b,c...,p) d'une fonction F de maniere a approcher au mieux
la fonction G.
    L'operateur MOCA permet de determiner ce jeu de parametres. LISTMESU
(listreel) qui contient les n valeurs de G.

Il faut donner les valeurs LISTFONC (listreel de n valeurs)
obtenues pour F pour un jeu de parametres LISTPARA (listreel) et qui
seront a comparer a LISTMESU. Enfin il faut fournir LISTDERi
(listreels de n valeurs)(i=1,p) qui contiennent les derivees partielles
de F par rapport aux parametres.
    Cet operateur fournit le meilleur jeu de parametres si F varie
lineairement en fonction des parametres.Il choisit de minimiser un
critere egal a :
Somme sur j=1,n(poidj*poidj*(listmesu(j)-listF(j))*(listmesu(j)-listF(j))

      Commentaire :

      LISTPARA : LISTREEL de P valeurs donnant les parametres initiaux

      LISTMESU : LISTREEL de n valeurs donnant l'objectif pour la
        fonction G.

      LISTFONC : LISTREEL de n valeurs donnant les valeurs de F pour
        le jeu de parametres LISTPARA aux n points.

      LISTDERi : p LISTREEL donnant chacun la derivee partielle de F
        (pour chacun des n points) par rapport au ieme
        parametre.

      POIDS : mot introduisant LISTPOI qui contient les n poids a
        prendre en compte pour le cacul du critere a minimiser.
        En l'absence de cette donnee tous les poids valent 1.

      RESU1 : LISTREEL contenant les valeurs pour les P parametres.

     Remarque : On trouvera un exemple d'utilisation de cet operateur
        dans un des jeux de donnees de Cast3m (identifi.dgibi).
        Cet exemple utilise moca,dans un systeme iteratif, pour
        approcher une fonction nonlineaire.

## MOCU [Mecanique Resolution]
Operateur MOCU

(LREE1) LREE2 LREE3 = MOCU (LREE4) LREE5 LREE6 MODE1 CHAM1 FLOT1;
ou
 (LREE1) LREE2 LREE3 TAB1 =
        MOCU (LREE4) LREE5 LREE6 MODE1 CHAM1 FLOT1 VERIF;

Objet :

L'operateur MOCU (MOment/CoUrbure) calcule la reponse d'un modele
de SECTION soumis a une biflexion circulaire sous effort normal.

Commentaire :

(LREE4) : Programme de chargement en courbure par rapport a l'axe
        local Oy (en 3D uniquement)
(LREE1) : Reponse en moment par rapport a l'axe local Oy
        (en 3D uniquement)
LREE5 : Programme de chargement en courbure par rapport a l'axe
        local Oz
LREE2 : Reponse en moment par rapport a l'axe local Oz

LREE6 : Programme de chargement en effort normal
LREE3 : Reponse en deformation normale

MODE1 : Modele de la section

CHAM1 : Caracteristique de la section

FLOT1 : Tolerance pour les calculs non-lineaires

VERIF : avec l'option VERIF, MOCU sort une table de tables contenant
        les variables internes (indice 'VARIABLES_INTERNES)', les
        contraintes (indice 'CONTRAINTES') et la reponse
        en deformation normale dans la section
        a tous les instants de calculs.

Remarque :

L'origine du chargement est l'etat nul

## MODI [Post-traitement Affichage]
    Directive MODIFIER

    MODIFIER ( OEIL1 si 3D) GEO1 ;

    Objet :

    La directive MODIFIER permet, si on dispose d'un terminal graphique
interactif muni d'un curseur graphique, de deplacer ou de nommer des
points, de supprimer, d'ajouter ou de nommer des elements d'un maillage.

    Commentaire :

    OEIL1 : point origine de l'angle de vue (type POINT)

    GEO1 : geometrie affectee (type MAILLAGE)

    Remarque :

    Les points deplaces le sont pour tous les maillages les contenant,
mais seul le maillage GEO1 est concerne par le travail sur les
elements.

## MODL [Fantome]
Opérateur MODL (MODELISER)

Cet opérateur a été débranché.
Se reporter à l'opérateur MODE(LISER).

## MOIN [Maillage Generaux]
Operateur MOINS
--------------- DEPL

Objet :

L'operateur MOINS s'utilise dans les cas suivants :

|  1ere possibilite  |

        OBJ2 = OBJ1 MOINS | VEC1  ;
        | CHPO1

    NOBJ1  ... NOBJN  = OBJ1 ...  OBJN  MOINS |  VEC1  ;
        |  CHPO1

Objet :

L'operateur MOINS se comporte comme l'operateur PLUS
en multipliant par -1 les operandes VEC1 ou CHPO1.

Commentaire :

     OBJ1 : types POINT, MAILLAGE, CHPOINT, MCHAML, MMODEL,
        le type RIGIDITE est admis pour la translation par -VEC1
        mais pas pour la transformation par -CHPO1. Il est aussi
        possible de donner une TABLE.

  OBJ1 ... OBJN : voir OBJ1

     VEC1 : type POINT

    CHPO1 : type CHPOINT

     OBJ2 : resultat de meme type que OBJ1

NOBJ1 ... NOBN : resultats respectivement de memes types
        que OBJ1 ... OBJN

|  2eme possibilite  |

        CHPO1 = GEO2 MOINS GEO1 ;

Objet :

L'operateur MOINS cree un CHPOINT correspondant, si elle existe,
a la transformation qui permet d'obtenir GEO2 a partir de GEO1.
Le support de CHPO1 est l'ensemble des points de GEO1.

Commentaire :

    GEO1 : type MAILLAGE

    GEO2 : type MAILLAGE, topologiquement equivalent a GEO1

    CHPO1 : type CHPOINT

## MOME [Mecanique Limites]
    Operateur MOMENT
    ---------------- OPTI

    CHPO1 = MOMENT  |  VEC1  |  GEO1  ;
        |  MOTi FLOTi ... |

    Objet :

    L'operateur MOMENT definit un champ de moment resultant de l'appliqua-
tion du moment represente, soit par les composantes d'un vecteur, soit
par des valeurs de composantes.

    Commentaire :

    VEC1 : vecteur (type POINT)

    MOTi : nom des composantes (type MOT)

    FLOTi : valeurs des composantes (type FLOTTANT)

    GEO1 : support geometrique (type MAILLAGE)

    CHPO1 : champ de moments (type CHPOINT)

    Remarque :

    Les noms de moments possibles sont :

        pour un calcul en mode | PLAN CONT |
        | PLAN DEFO | :  MZ

        pour un calcul en mode AXIS : MT

        pour un calcul en mode FOUR : MT MZ

        pour un calcul en mode PLAN GENE : MX(*) MY(*)

        pour un calcul en mode TRID : MX MY MZ

        (*) uniquement au point support des inconnues supplementaires

    Exemple :

    Si GEO1 contient 50 points, le moment applique sur chaque
point est 1/50 de VEC1 (ou 1/50 de VALi).

    Attention : On doit specifier VEC1 avant GEO1.

## MONTAGNE [Post-traitement Affichage] (proc)
Procedure MONTAGNE

MONTAGNE  CHPO1 (CHPO2) GEO1 (FLOT1) (| POIN1 )

        ('CACHE') ('TITRE' CHA1) | ('VOLUME') ;

Objet :

Cette procedure sert a visualiser en relief un champ par point a une
composante, et eventuellement de superposer a ce relief les
isovaleurs d'un autre champ.

Commentaire :

CHPO1 : champ par points a visualiser (type CHPOINT)
        pour creer le relief

CHPO2 : champ par points a visualiser (type CHPOINT - facultatif)
        dont les isovaleurs s'appuieront sur le relief

GEO1 : support geometrique du champ (type MAILLAGE)

FLOT1 : coefficient d'amplification (type FLOTTANT - facultatif)

'TITRE' mot-clef suivi de
CHA1 : chaine de caracteres a utiliser comme titre du
        dessin. (facultatif)

POIN1 : point de vue (type POINT - facultatif)
PROG1 : idem (type LISTREEL - facultatif), sous la forme d'une
        liste de trois reels.

'FLECHE'/'VOLUME'/'SUPER' : (type MOT - facultatif) :
      FLECHE pour relief par des petites fleches
      VOLUME pour relief par volume (par defaut si CHPO1 seul)
      SUPER " " " " plus isovaleurs
        (selectionne obligatoirement si CHPO2 donne)

'CACHE' : mot-clef facultatif indiquant (avec 'VOLUME') qu'on veut
        les faces cachees. C'est l'option par defaut dans les
        autres cas.

Remarque :

Les deux champs doivent avoir le meme support geometrique GEO1,
et n'avoir qu'une seule composante.

Les axes horizontaux du trace correspondent aux deux premieres
coordonnees des points sous-tendant CHPO1.

Si on donne un seul champ et le mot-clef 'SUPER', trace ce champ
en relief et superpose ses propres isovaleurs dessus.

Si CHPO2 est fourni, l'option de trace devient 'SUPER' quel que
soit le mot-clef fourni.

Si OEIL n'est pas fourni, il est place au-dessus, regardant par le
sud-sud-ouest.
Pour fournir OEIL, il faut etre obligatoirement en dimension 3.

Si le coefficient d'amplification FLOT1, n'est pas fourni, il est
determine automatiquement en donnant une meme amplitude verticale
que les amplitudes horizontales.

## MOT [Langage Caracteres]
Operateur MOT

MOT1 = MOT MOT2 ;

Objet :

L'operateur MOT sert a donner un alias a un mot-cle ou a
mettre un nom d'operateur ou de procedure dans une table.

Commentaire :

MOT1 : alias donne au mot-cle (type MOT)

MOT2 : mot-cle (type MOT)

Exemple :

T = MOT 'TRAC' ;
TA= TABLE;
TA . 1 = MOT 'DROI';
TA . 2 = MOT CERC ;
ta . 2 = MOT PASAPAS;

On pourra alors ecrire : T OBJET ; au lieu de : TRAC OBJET ;

Remarque : Il est preferable de donner le nom d'un operateur
entre quotes mais le nom d'une procedure ne doit pas l'etre.

## MOTA [Mecanique Resolution]
    Operateur MOTA

      CHEL1 = MOTA MODL1 SIG1 VAR1 MAT1 (FLOT1) ;

    Objet :

    L'operateur MOTA calcule le champ de modules tangents, liant la
vitesse de contrainte equivalente DSIG a la vitesse de deformation
plastique equivalente DEPS :

        DSIG = CHEL1 * DEPS

      L'etat initial doit etre plastiquement et statiquement admissible.

      Commentaire :

      MODL1 : objet modele (type MMODEL)

      SIG1 : champ de contraintes (type MCHAML, sous-type CONTRAINTES)

      VAR1 : champ de variables internes (type MCHAML, sous-type
        VARIABLES INTERNES)

      MAT1 : champ de caracteristiques materielles et geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

      FLOT1 : precision permettant de determiner le critere (type
        FLOTTANT) la precision vaut 1.E-3 par defaut

      CHEL1 : champ de modules tangents (type MCHAML)

    Remarque :

    La logique de calcul du module tangent est la suivante pour chaque
point de chaque element :

    - ou bien SIG1 est a l'interieur de la surface de charge; dans ce ca
      le module est le module d'Young.

    - ou bien SIG1 est sur la surface de charge; dans ce cas le module
      est le module tangent.

    L'etat initial doit etre plastiquement et statiquement admissible.

    Un point se trouve sur la surface de charge si:

    - le materiau est plastique.
    - sa deformation plastique est strictement positive.
    - le critere du tenseur de contrainte SIG1 est superieur a
       FLOT1 * SELAS ( SELAS est le diametre actuel de la surface de
       charge ).

    Il convient de respecter l'ordre des donnees en entree .

## MOTS [Langage Base]
Operateur MOTS
-------------- EVOL ENUM

LMOTS1 = MOTS MOT1 MOT2 ... ;

Objet :

L'operateur MOTS cree une liste de mots de 8 caracteres.

Commentaire :

MOTi : mots contenus dans la liste de mots (type MOT)

LMOTS1 : liste de mots (type LISTMOTS)

|  Sous-directive  *  |

LMOTS1 = MOTS 3*'ROUG' ;

est equivalent a : LMOTS1 = MOTS 'ROUG' 'ROUG' 'ROUG' ;

On peut aussi ecrire :

LMOTS1 = MOTS 2*'BLEU' 2*'VERT' 'ROUG' ;

qui equivaut a : LMOTS1 = MOTS 'BLEU' 'BLEU' 'VERT' 'VERT' 'ROUG' ;

Remarque :

Pour eviter que l'un des mots soit pris pour un operateur, il faut
ecrire l'operateur MOTS en tete.

## MOYESPEC [Mathematiques Fonctions] (proc)
Procedure MOYESPEC

FLOT1 = MOYESPEC EVOL1 FLOT2 FLOT3;

objet :

La procedure MOYESPEC calcule la valeur moyenne FLOT1
d'une courbe EVOL1 dans l'intervalle donne par
FLOT2-FLOT3.

## MPMA [—]
Operateur MPMA
        LRRE1 = MPMA MOD1 FLOT1;

      Objet :

      MPMA donne la matrice qui sert a calculer le potentiel vecteur A
      sur les elements d'une geometrie dans le plan XY avec une epaisseur donnee selon Z.
      Pour une geometrie donnee, il faut appeler MPMA une fois et ensuite utiliser JPMA
      avec la densite de courant pour calculer le potentiel vecteur.

      Commentaire :

        MOD1 modele ou la densite de courant est appliquee
        FLOT1 epaisseur du modele (REEL)

      en sortie :

        LREE1 matrice d'interactions entre les elements utilisee par JPMA

     Remarques

    - le maillage du modele doit etre constitue d'un seul type d'elements

## MPRO [Maillage Autres]
Operateur MPRO
-------------- TRAC

MELEME = MPRO RAIDEUR ;

Objet :

L'operateur MPRO construit un maillage de la matrice triangulaire inferieure
apparaissant dans la factorisatin d'une matrice.

Commentaire :

MELEME : geometrie (type MAILLAGE)

RAIDEUR : raideur deja factorisee (type RIGIDITE)

## MRCFRAM1 [Poteau et poutre en Beton arme] (proc)
    procedure MRCFRAM1

   LAM1 = MRCFRAM1 MOT1 TAB1 TOL1;

Objet :

    Procedure appelee par MRCFRAME pour le calcul de la marge sismique
    des elements de type portiques (frame) (TIMO ou POUT) type POUTEAU COURT

Commentaire :
    Cette procedure est appellée par la procedure de calcul des marges
    pour les elements frame (TIMO et POUT) - voir MRCFRAME

En entree :

En sortie :

Remarques :

## MRCFRAM2 [Poteau et poutre en Beton arme] (proc)
    procedure MRCFRAM2

   LAM1 = MRCFRAM2 MOT1 TAB1 TOL1;

Objet :

    Procedure appele par MRCFRAME pour le calcul de la marge sismique
    des elements de type portique (frame) (TIMO ou POUT) type POUTEAU LONG

Commentaire :
    Cette procedure est appellée par la procedure de calcul des marges
    pour les elements frame (TIMO et POUT) - voir MRCFRAME

En entree :

En sortie :

Remarques :

## MRCFRAM3 [Poteau et poutre en Beton arme] (proc)
    procedure MRCFRAM3

   LAM1 = MRCFRAM3 MOT1 TAB1 TOL1;

Objet :

    Procedure appelee par MRCFRAME pour le calcul de la marge sismique
    des elements de type portique (frame) (TIMO ou POUT) type POUTRE COURTE

Commentaire :
    Cette procedure est appellée par la procedure de calcul des marges
    pour les elements frame (TIMO et POUT) - voir MRCFRAME

En entree :

En sortie :

Remarques :

## MRCFRAM4 [Poteau et poutre en Beton arme] (proc)
    procedure MRCFRAM4

   LAM1 = MRCFRAM4 MOT1 TAB1 TOL1;

Objet :

    Procedure appelee par MRCFRAME pour le calcul de la marge sismique
    des elements de type portique (frame) (TIMO ou POUT) type POUTRE LONG

Commentaire :
    Cette procedure est appellée par la procedure de calcul des marges
    pour les elements frame (TIMO et POUT) - voir MRCFRAME

En entree :

En sortie :

Remarques :

## MRCFRAME [Poteau et poutre en Beton arme] (proc)
    procedure MRCFRAME

   TAB2 = MRCFRAME MOT1 TAB1 TOL1 LELE1

Objet :

    Procedure pour la determination des marges de securite pour
    les elements de portique (frames) (TIMO et POUT) en beton arme avec ou sans la
    prise en compte des covariances des efforts.

Commentaire :
    Cette procedure est appellee (utilisable) seulement pour les claculs
    en 3D.

En entree :
     MOT1: Type de calcul [MOT]
        'RECTANGLE' sans prise en compte des
        covariances
        'ELLIPSOIDE' avec prise en compte des
        covariances
     TAB1.'MAILLAGE': Maillage de l element [MAILLAGE]
        .'EFFORT_SEISME': MCHAML de la matrice
        representant l enveloppe des
        efforts sismiques (voir SISSIB)
        .'EFFORT_STATIQUE': MCHAML des efforts statiques qui
        agissent sur l element frame
        .'CARACTERISTIQUES' :MCHAML contenant les
        caracteristiques de l element
        frame :
        'B_Y' longeur Y de la section
        en m [FLOTTANT]
        'B_Z' longeur Z de la section
        en m [FLOTTANT]
        'LIBY' Longeur ly
        en m [FLOTTANT]
        'LIBZ' Longeur lz
        en m [FLOTTANT]
        'SCAD' Espacement cadres
        en m [FLOTTANT]
        'ENRB' Enrobage en m [FLOTTANT]
        'PFER' Diametres ferrailage
        en mm [LISTREEL]
        'YFER' position y ferraillage
        en m [LISTREEL]
        'ZFER' position z ferraillage
        en m [LISTREEL]
        'ASWY' aire ferraillage transv y
        en m2 [FLOTTANT]
        'ASWZ' aire ferraillage transv z
        en m2 [FLOTTANT]
        'YACI' module d young
        de l acier
        en Pa [FLOTTANT]
        'EPSB' deformation ultime du
        beton [FLOTTANT]
        'EPSA' deformation ultime de
        l acier [FLOTTANT]
        .'FC_BET': Resistance caracteristique beton
        [FLOTTANT]
        .'GAM_C': Coef gammac 1.5/1.2 EC2/EC8
        [FLOTTANT]
        .'ALP_C': Coef alpa 1.0 EC2
        [FLOTTANT]
        .'FS_ACI': resistance caracteristique de l acier
        [FLOTTANT]
        .'GAM_S': Coef gammas 1.15 EC2
        [FLOTTANT]
        TOL1: Tollerance [FLOTTANT]
        LELE1: Liste des elements sur lesquels on veut sortir
        les graphiques des surfaces limites et des
        enveloppes (sans ou avec covariance - RECTANGLE
        ou ELLISPOIDE) (pas necessaire)
        [LISTREEL]

En sortie :

     TAB1.: Table Contenant:
        .'CH_LAMBDA': MCHAML les valeurs des marges (composent LAMB)
        .'CARTE': Maillage avec deux colorations pour indiquer les
        elements avec une marge superieure à 1 ou
        inferieure:
        ROUGE elements -> Lambda < 1.0
        VERT elements -> Lambda > 1.0
        .'GRAPHIQUES': Sous table pour les outils de graphique:
        .I. Ieme element
        .'LIMITE': Surface limite de l element [MAILLAGE]
        .'RECTANGLE': enveloppe sismique sans prise
        en compte des covariances
        (methode RECTANGLE) [MAILLAGE]
        .'ELLIPSOIDE': enveloppe sismique avec prise
        en compte des covariances
        (methode ELLIPSOIDE) [MAILLAGE]
        .'RECTANGLE_AUG': enveloppe sismique augmenté
        sans prise en compte des covariances
        (methode RECTANGLE) [MAILLAGE]
        .'ELLIPSOIDE_AUG': enveloppe sismique augmenté
        avec prise en compte des covariances
        (methode ELLIPSOIDE) [MAILLAGE]

Remarques :

## MRCSHELL [Voile Beton arme] (proc)
    procedure MRCSHELL

   TAB_OUT = TAB_IN TOL_1 L_ELE1 ;

Objet :

    Procedure pour la determination des marges de securite pour les voiles
    en beton arme avec ou sans la prise en compte des covarinces des
    efforts. La verification est faite sur les efforts projes selon
    le modele de MARTI a trois couches

Commentaire :
    Cette procedure est appellee (utilisable) seulement pour les clacul
    en 3D.

En entree :
    TYP_CAL1: Type de calcul [FLOTTANT]
        'RECTANGLE' sans prise en compte des
        covariances
        'ELLIPSOIDE' avec prise en compte des
        covariances
    TAB_IN.'MAILLAGE': Maillage du voile [MAILLAGE]
    TAB_IN.'EFFORT_SEISME': MCHAML des matrices
        rapresentant l'enveloppe des
        efforts sismiques (voir SISSIB)
    TAB_IN.'EFFORT_STATIQUE': MCHAML des efforts statiques qui
        agissent sur la voile
        (issu EFFMARTI)
    TAB_IN.'CARACTERISTIQUES_EXTERNE':MCHAML contenant les
        caracteristiques de la couche
        externe selon le modele de MARTI
        (voir EFFMARTI):
        'RHO1' taux d'acier direction 1
        'RHO2' taux d'acier direction 2
        'ENRO' Enrobage
    TAB_IN.'CARACTERISTIQUES_INTERNE':MCHAML contenant les
        caracteristiques de la couche
        interne selon le modele de MARTI
        (voir EFFMARTI):
        'RHO1' taux d'acier direction 1
        'RHO2' taux d'acier direction 2
        'ENRO' Enrobage
    TAB_IN.'CARACTERISTIQUES_CORE': MCHAML contenant les
        caracteristiques et les coeficients
        pour la couche intermediaire
        selon le modele de MARTI
        'H' Epaisseur Totale
        'RHOT' taux d'acier transversale
        'COTH' Facteur cisaillement
    TAB_IN.'FC_BET': Resistance caracteristique beton
        [FLOTTANT]
    TAB_IN.'GAM_C': Coef gammac 1.5/1.2 EC2/EC8
        [FLOTTANT]
    TAB_IN.'ALP_C': Coef alpa 1.0 EC2
        [FLOTTANT]
    TAB_IN.'NU_C': Coef nu 0.6*(1-250/fck) EC2
        [FLOTTANT]
    TAB_IN.'FS_ACI': resistance caracteristique acier
        [FLOTTANT]
    TAB_IN.'GAM_S': Coef gammas 1.15 EC2
        [FLOTTANT]
    TOL_1: Tollerance [FLOTTANT]
    L_ELE1: Liste des elements sur lesquels on veut sortir les
        graphiques des surfaces limites et des enveloppes
        (sans ou avec covariance - RECTANGLE ou ELLISPOIDE)
        pour les couches externes, internes et
        intermediaire (pas necessaire) [LISTREEL]

En sortie :

   TAB_OUT: Table output:
    .'CH_LAMBDA_E': MCHAML des valeurs des marges pour la couche
        externe (composent LAME)
    .'CH_LAMBDA_I': MCHAML des valeurs des marges pour la couche
        interne (composent LAMI)
    .'CH_LAMBDA_C': MCHAML des valeurs des marges pour la couche
        intermediaire (composent LAMC)
    .'CARTE_E': Maillage avec deux coloration pour indiquer les
        element avec une marge superieure à 1 ou
        inferieure (couche externe):
        ROUGE elements -> Lambda < 1.0
        VERT elements -> Lambda > 1.0
    .'CARTE_I': Maillage avec deux coloration pour indiquer les
        element avec une marge superieure à 1 ou
        inferieure (couche interne):
        ROUGE elements -> Lambda < 1.0
        VERT elements -> Lambda > 1.0
    .'CARTE_C': Maillage avec deux coloration pour indiquer les
        element avec une marge superieure à 1 ou
        inferieure (couche intermediaire):
        ROUGE elements -> Lambda < 1.0
        VERT elements -> Lambda > 1.0
    .'GRAPHIQUES': Sous table for the graphiques tools:
      .I. Ieme element
        .'LIMITE_E': Surface limite de la couche externe
        [MAILLAGE]
        .'LIMITE_E': Surface limite de la couche interne
        [MAILLAGE]
        .'LIMITE_C': Surface limite de la couche
        intermediaire [MAILLAGE]
        .'RECTANGLE_E': enveloppe couche externe sans prise
        en compte des covariances
        (methode RECTANGLE) [MAILLAGE]
        .'RECTANGLE_I': enveloppe couche interne sans prise
        en compte des covariances
        (methode RECTANGLE) [MAILLAGE]
        .'RECTANGLE_I': enveloppe couche intermediaire
        sans prise en compte des covariances
        (methode RECTANGLE) [MAILLAGE]
        .'ELLIPSOIDE_E': enveloppe couche externe avec prise
        en compte des covariances
        (methode ELLIPSOIDE) [MAILLAGE]
        .'ELLIPSOIDE_I': enveloppe couche interne avec prise
        en compte des covariances
        (methode ELLIPSOIDE) [MAILLAGE]
        .'ELLIPSOIDE_I': enveloppe couche intermediaire
[… notice tronquée ; texte complet dans l'archive PCW_24]

## MRCTRACE [Voile Beton arme] (proc)
    procedure MRCTRACE

   VAL1 = MRCTRACE TAB1;

Objet :

    Procedure pour tracer les surfaces limites et les enveloppes des
    trois couches selon le modele de MARTI (voir EFFMARTI)

Commentaire :
Cette procedure est appellée par la procedure de calcul des marges pour
les elements 2D (coques ou voiles) - voir MRCSHELL

En entree :

En sortie :

Remarques :

## MREM [Mecanique Resolution]
   Operateur MREM
   -------------- CHAN DEPE

     Syntaxe :

        CHPO3 = 'MREM' CHPO1 RIG1 RIG2 CHPO1 CHPO2 ;

      Objet :

L'operateur MREM est appele dans la procedure UNILATER pour
reintroduire les inconnues eliminees dans la solution.

Son emploi en dehors de ce contexte est deconseille.

## MULC [Mathematiques Autres] (proc)
Procedure MULC

CH1 = MULC CH2 CH3 ;

Objet :

La procedure MULC realise la multiplication terme a terme de 2
champs par points.

Commentaire :

CH2, CH3 : champs (type CHPOINT) pointant sur la meme geometrie et
        ayant les memes noms de composantes.

CH1 : champ (type CHPOINT) pointant sur la meme geometrie et
        ayant les memes noms de composantes que CH2 et CH3; la
        valeur de la composante Cj au point Pi du champ CH1 etant
        egale au produit des valeurs des champs CH2 et CH3 pour
        la meme composante et au meme point.

Remarques :

La procedure MULC est appelee par la procedure SISSIB.

On suggere d'utiliser l'operateur '*' qui est plus general.

## MULT [Mathematiques Autres]
Operateur MULT

LOG1 = MULT N1 N2 ;

Objet :

L'operateur MULT compare deux nombres entiers N1 et N2.

Commentaire :

N1, N2 : nombres entiers (type ENTIER)

LOG1 : resultat logique (type LOGIQUE)
        a pour valeur VRAI si N1 est un multiple entier de N2 et
        FAUX sinon.

## MULTIDEC [Mathematiques Traitement] (proc)
Procedure MULTIDEC
------------------ ANALYSER

N1 EVOL1_DECO EVOL2_RESI=MULTIDEC EVOL3_SIGN LREEL1_HT ENTI1_HT
        LREEL2_GT ENTI2_GT (ENTI3 MOT1);

Objet :

La procedure MULTIDEC permet d'effectuer la multidecomposition
d'un signal donne sur une grille uniforme de longueur quelconque
EVOL3_SIGN (dont on traite que la premiere courbe) par rapport
aux filtres miroirs conjugues LREEL1_HT et LREEL2_GT. LREEL1_HT
et LREEL2_GT pouvant etre non symetriques, ENTI1_HT et ENTI2_GT
indiquent le nombre de points "negatif" a prendre en compte dans
la convolution (ENTI1_HT et/ou ENTI2_GT sont negatifs si la
convolution est symetrique).

L'ENTIER N1 indique le nombre de niveaux d'analyse effectif,
EVOL1_DECO (contenant N1 courbes) contient la decomposition (des
basses vers les hautes "frequences") et EVOL2_RESI (contenant
une courbes) le residu de EVOL3_SIGN.

La procedure MULTIDEC utilise les operateurs CVOL et DIAD.

Options :

ENTI3 : L'ENTIER ENTI3 permet de specifier le nombre de niveaux
        de decomposition souhaite. Par defaut c'est le maximum
        autorise par le convolueur CVOL.

MOT1 : Le MOT MOT1 specifie les conditions de bord pour les
        calculs de correlation: 'SYME'(trique) ou 'PADD'(ing) de
        zero. Le defaut est 'SYME'.

## MULTIREC [Mathematiques Traitement] (proc)
Procedure MULTIREC
------------------ RECOMPOS

N2 EVOL1_SIGN=MULTIREC EVOL2_RESI EVOL3_DECO
        LREEL1_H ENTI1_H
        LREEL2_G ENTI2_G (ENTI3 MOT1);

Objet :

La procedure MULTIREC permet d'effectuer la multi-recomposition
EVOL1_SIGN (comportant une courbe) d'un signal a partir de sa
decomposition EVOL3_DECO (contenant N1 courbes des basses
vers les hautes frequences) et son residu EVOL2_RESI (contenant
une courbe) par rapport aux filtres conjugues LREEL1_H et LREEL2_G,
LREEL1_H et LREEL2_G pouvant etre non symetriques, ENTI1_H et ENTI2_G
indiquent le nombre de points "negatifs" a prendre en compte dans la
convolution (ENTI1_H et/ou ENTI2_G sont negatifs si la convolution
est symetrique)

L'ENTIER N2 indique le nombre de niveaux d'analyse effectif.

La procedure MULTIREC utilise les operateurs CVOL et DIAD.

Options :

ENTI3 : permet de specifier le nombre de niveaux de recomposition
        souhaite. Par defaut c'est N1.

MOT1 : specifie les conditions de bord pour les calculs de
        correlation: 'SYME'(trique) ou 'PADD'(ing) de zero. Le
        defaut est 'SYME'.

## MUTU [Magnetostatique Magnetostatique]
Operateur MUTU

RIG1 = MUTU MOD1 MAT1 (GEO1);

Objet :

L'operateur MUTU construit la matrice de mutuelle inductance
d'un modele 'MAGNETODYNAMIQUE' de calcul de Courants de
Foucault (formulation 'POTENTIEL_VECTEUR') avec le support
de ces courants.
Le maillage support des courants est a priori celui du
domaine de calcul, sinon GEO1 specifie un domaine deduit
par symetrie ou rotation. Dans ce dernier cas le logiciel essaye
de faire correspondre la topologie du maillage support du modele
MOD1 avec celle de GEO1. Si les topologies sont trop complexes,
il peut etre necessaire d'appeler plusieurs fois l'operateur
en simplifiant les donnees.

Commentaire :

 MOD1 : nom du modele 'MAGNETODYNAMIQUE' (type MODELE)
 MAT1 : champ de caracteristiques du materiau (type MCHAML)
 GEO1 : support des Courants de Foucault (type MAILLAGE)
 RIG1 : matrice de resistance (type RIGIDITE)

## M_DAMPIN [Mecanique Dynamique] (proc)
   Procedure M_DAMPIN

   RIG2 = M_DAMPIN TAB1 LREEL1 RIG1;

   Objet :

   La procedure M_DAMPIN construit une matrice d'amortissement
modal dans l'espace physique. Elle affecte a chaque mode de base
un amortissement reduit. Cette procedure correspond a l'operateur
AMOR qui travaille dans l'espace modal.

   Commentaire :

 TAB1 : table definissant les modes (type 'TABLE', sous-type
        'BASE_DE_MODES')

 LREEL1 : coefficients des amortissements modaux reduits (en %)
        (type 'LISTREEL')

 RIG1 : matrice de rigidite (type 'RIGIDITE', sous-type
        'RIGIDITE')

 RIG2 : matrice d'amortissement (type 'RIGIDITE', sous-type
        'RIGIDITE')

## M_DAMP_K [Mecanique Dynamique] (proc)
   Procedure M_DAMP_K

   RIG2 = M_DAMPIN TAB1 LREEL1 RIG1;

   Objet :

   La procedure M_DAMP_K construit une matrice d'amortissement
modal dans l'espace physique, completee par un amortissement
proportionel a la rigidite. Elle affecte a chaque mode de base
un amortissement reduit.

   Commentaire :

 TAB1 : table definissant les modes (type 'TABLE', sous-type
        'BASE_DE_MODES')

 LREEL1 : coefficients des amortissements modaux reduits (en %)
        (type 'LISTREEL')

 RIG1 : matrice de rigidite (type 'RIGIDITE', sous-type
        'RIGIDITE')

 RIG2 : matrice d'amortissement (type 'RIGIDITE', sous-type
        'RIGIDITE')

## NATAF [Mathematiques Autres] (proc)
   Procedure NATAF
   ----------------- FINVREPA REPART

    NATAF TAB1 ;

        TAB1 . transformation_directe
        . points_espace_physique
        . points_espace_reference
        . noms_des_variables
        . matcov
        . matrice_de_decorrelation
        . param_va . k . typva
        . param_va . k . A
        . param_va . k . B
        . param_va . k . LAMBDA
        . param_va . k . MU
        . param_va . k . MOYENNE
        . param_va . k . ECART_TYPE

   Objet :
La procedure NATAF calcule l'image d'un point de l'espace physique
dans l'espace de reference (si les variables sont dependantes par la
 transformation de NATAF) ou la reciproque c'est a dire l'image
 d'un point de l'espace de reference dans l'espace physique.

  Donnees :
 TAB1 . 'TRANSFORMATION_DIRECTE' : logique
  si VRAI on va de l'espace physique vers l'espace de reference
  si FAUX on va de l'espace de reference vers l'espace physique.

 TAB1 . 'POINTS_ESPACE_PHYSIQUE' : listreel des coordonnees du point
  dans l'espace physique.
   entree si TAB1 . 'TRANSFORMATION_DIRECTE' = VRAI
   sortie si TAB1 . 'TRANSFORMATION_DIRECTE' = FAUX

 TAB1 . 'POINTS_ESPACE_REFERENCE' : listreel des coordonnees du point
  dans l'espace de reference.
   entree si TAB1 . 'TRANSFORMATION_DIRECTE' = FAUX
   sortie si TAB1 . 'TRANSFORMATION_DIRECTE' = VRAI

 TAB1 . 'NOMS_DES_VARIABLES' : listmots contenant le nom de chaque variable.

 TAB1 . 'MATCOV' : listreel qui contient la matrice de correlation
   dans le cas ou les variables ne sont pas independantes. C'est la
   transformation de nataf qui est utilisee.
   pour une matrice | a b c |
        | b d e |
        | c e f |
   il faut rentrer (prog a b d c e f).
   Les lois autorisees sont :
  Uniforme, Normale centree reduite, Normale, Lognormale, Exponentielle.

 TAB1 . MATRICE_DE_DECORRELATION : listreel contenant la matrice
 triangulaire inferieure obtenue par la decomposition de Cholesky de
 la matrice de correlation fictive obtenue a l'aide des formules approchees.
   pour une matrice | a b c |
        | d e f |
        | g h i |
   c'est (prog a b c d e f g h i).
  si elle fournie par l'utilisateur, on ne la recalcule pas sinon on la
  calcule et on la fournit en sortie.

 TAB1 . 'PARAM_VA' . k : est une table qui contient les differents parametres
        necessaire a la connaissance de la kieme variable
        aleatoire.
 TAB1 . 'PARAM_VA' . k . 'TYPVA' : chaine de caractere contenant le type de
     la kieme variable aleatoire.
    Les types disponibles sont :
        'LOI_UNIFORME'
        'LOI_NORMALE_STANDARD' (i.e. centree,reduite)
        'LOI_EXPONENTIELLE'
        'LOI_LOGNORMALE'
        'LOI_NORMALE'

  Dans le cas de la loi uniforme :
 TAB1 . 'PARAM_VA' . k . 'A'
 TAB1 . 'PARAM_VA' . k . 'B' : sont les bornes de l'intervalle sur lequel
       la variable est definie (A<B)

  Dans le cas de la loi normale centree reduite (LOI_NORMALE_STANDARD) :
pas de parametre. La densite vaut : exp(-0.5*x^2)/((2*pi)**0.5)

  Dans le cas de la loi exponentielle :
    TAB1 . 'PARAM_VA' . k . 'LAMBDA'
    TAB1 . 'PARAM_VA' . k . 'MU'
 la densite vaut : lambda*exp(lambda*(mu - x)) si x >= mu
        0 sinon

  Dans le cas de la loi lognormale :
 TAB1 . 'PARAM_VA' . k . 'MOYENNE'
 TAB1 . 'PARAM_VA' . k . 'ECART_TYPE'
sont la moyenne et l'ecart-type de la variable aleatoire.

  Dans le cas de la loi normale :
 TAB1 . 'PARAM_VA' . k . 'MOYENNE'
 TAB1 . 'PARAM_VA' . k . 'ECART_TYPE'
sont la moyenne et l'ecart-type de la variable aleatoire.

## NAVI [Fluides Modele]
FRAN====================================================================|
        Navier_Stokes : Ecoulements fluides incompressibles visqueux  |
        ------------------------------------------------------------  |
  I Modeles physiques  |
  ____________________  |
  Le modele Navier_Stokes permet de traiter dans un formalisme Eulerien |
 les ecoulements multidimensionnels de fluides incompressibles ( ou  |
 faiblement compressibles) visqueux et newtonien. Cela concerne les  |
 ecoulements dans les structures internes industrielles, les ecoulements|
 atmospheriques a petite echelle, les ecoulements dans une enceinte de  |
 reacteur en situation accidentelle, le genie chimique (ecoulement dans |
 un reacteur chimique, centrifugation) les interactions fluide/structure|
 ... etc.  |
 Les regimes d'ecoulements peuvent etre stationnaires ou instationnaires|
 laminaires ou turbulents, en convection forcee, naturelle ou mixte.  |
        |
  Ecoulements faiblement compressibles :  |
        |
    approximation de Boussinesq  |
    approximation faible Mach  |
        |
  Modelisation de la turbulence :  |
        |
    modele K - Epsilon  |
    modele RNG K - Epsilon  |
        |
  Conditions limites :  |
        |
    vitesse, temperature .. imposees  |
    contraintes totale (visqueuses et pression) imposees  |
    flux thermique ou de masse impose  |
    condition d'echange thermique  |
    fonction de paroi QDM thermique et masse  |
        |
  Force de volume / termes,source ou puits  |
        |
  Ecoulements aux travers d'obstacles  |
        |
    faisceaux, plaques, diaphragmes  |
        |
  Modeles bi-fluide  |
        |
    transport de particules  |
    emulsion  |
        |
        |
  II Methodes numeriques  |
  ______________________  |
        |
        |
    II.1 Discretisation spatiale  |
    ----------------------------  |
        |
  Elle est obtenue par une methode d'elements finis multidimensionnelle |
 2D (plan ou axi) ou 3D.  |
        |
 On fera reference par la suite aux familles d'elements suivantes :  |
        |
 LINE  : SEG2 TRI3 QUA4 CUB8 PRI6 TET4 PYR5  |
 QUAD  : SEG3 TRI6 QUA8 CU20 PR15 TE10 PY13  (MECANIQUE)  |
 QUAF  : SEG3 TRI7 QUA9 CU27 PR21 TE15 PY19  (MECA FLU)  |
 MACRO : SEG3 TRI6 QUA9 CU27 PR18 TE10  (MECA FLU)  |
        |
        |
  La formulation mixte vitesse pression ne permet pas n'importe quel  |
 type d'element. On peut distinguer deux classes d'elements : les  |
 elements a pression continue et ceux a pression discontinue. On ne  |
 dispose dans CASTEM 2000 que de ces derniers.  |
        |
        |
        |
        A - Les elements quadratiques QUAF  |
        ==================================  |
        |
 P2+bulle - P1 nc (nc : non conforme) et Q2 - P1 nc  |
 (Crouzeix-Raviart) [1]  (Bercovier-Pironneau) [2]  |
 et leurs homologues 3D  |
 La pression est P1 non conforme  |
        |
        u  |
       /\  u-----u-----u  |
      /p \  |  |  |  |
    u/____\u  | p  |  |  |
    /\ u  /\  u-----u--p--u  |
   /p \  /p \  |  |  |  |
  /____\/____\  |  p  |  |
 u  u  u  u-----u-----u  |
        |
 Ref :  |
 [1] M. Crouzeix and P.A. Raviart : Conforming and non conforming  |
     finite element methods for solving the stationary Stokes equations.|
     R.A.I.R.O. (7eme annee,decembre 1973,R-3,p.33a76)  |
        |
 [2] M. Bercovier and O. Pironneau : Error estimates for finite element |
     solution of the Stokes problem in the primitive variables.  |
     Numer. Math. 33,p.211-224, 1979.  |
        |
 Les ordres de convergence spatiales sont :  |
 ------------------------------------------  |
  pour la vitesse  O(h**3)  |
  pour la pression O(h**2)  |
  h etant une mesure de l'element.  |
        |
  mise en oeuvre :  |
  ----------------  |
        |
 1/ Faire un maillage compose d'elements LINE ou QUAD.  |
        |
 2/ Transformer les elements du maillage en QUAF.  voir operateur CHAN  |
        |
 3/ Faire les eliminations necessaires de points eventuellement crees  |
    en double.  voir operateur ELIM  |
        |
 4/ Creer les objets MMODEL 'NAVIER_STOKES' associes aux maillages en  |
    precisant QUAF pour le type des elements finis.  |
        voir operateur MODE  |
        $MT = MODE MT 'NAVIER_STOKES' QUAF ;  |
        |
 5/ Creer les champs de vitesse et de pression.  |
    La vitesse  sera un CHPOINT VECT SOMMET  |
    La pression sera un CHPOINT SCAL CENTREP1  |
        voir operateur KCHT  |
    UN = KCHT $MT VECT SOMMET (0. 0. 0.) ;  |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## NAVIER [Fluides Modele]
FRAN====================================================================|
        Navier_Stokes : Ecoulements fluides incompressibles visqueux  |
        ------------------------------------------------------------  |
  I Modeles physiques  |
  ____________________  |
  Le modele Navier_Stokes permet de traiter dans un formalisme Eulerien |
 les ecoulements multidimensionnels de fluides incompressibles ( ou  |
 faiblement compressibles) visqueux et newtonien. Cela concerne les  |
 ecoulements dans les structures internes industrielles, les ecoulements|
 atmospheriques a petite echelle, les ecoulements dans une enceinte de  |
 reacteur en situation accidentelle le genie chimique (ecoulement dans  |
 un reacteur chimique, centrifugation) les interactions fluide/structure|
 .. etc.  |
 Les regimes d'ecoulements peuvent etre stationnaires ou instationnaires|
 laminaires ou turbulents, en convection forcee, naturelle ou mixte.  |
        |
  Ecoulements faiblement compressibles :  |
        |
    approximation de Boussinesq  |
    approximation faible Mach  |
        |
  Modelisation de la turbulence :  |
        |
    modele K - Epsilon  |
    modele RNG K - Epsilon  |
        |
  Conditions limites :  |
        |
    vitesse, temperature .. imposees  |
    contraintes totale (visqueuses et pression) imposees  |
    flux thermique ou de masse impose  |
    condition d'echange thermique  |
    fonction de paroi QDM thermique et masse  |
        |
  Force de volume / termes,source ou puits  |
        |
  Ecoulements aux travers d'obstacles  |
        |
    faisceaux, plaques, diaphragmes  |
        |
  Modeles bi-fluide  |
        |
    transport de particules  |
    emulsion  |
        |
        |
  II Methodes numeriques  |
  ______________________  |
        |
        |
    II.1 Discretisation spatiale  |
    ----------------------------  |
        |
  Elle est obtenue par une methode d'elements finis multidimensionnelle |
 2D (plan ou axi) ou 3D.  |
        |
 On fera reference par la suite aux familles d'elements suivantes :  |
        |
 LINE  : SEG2 TRI3 QUA4 CUB8 PRI6 TET4 PYR5  |
 QUAD  : SEG3 TRI6 QUA8 CU20 PR15 TE10 PY13  (MECANIQUE)  |
 QUAF  : SEG3 TRI7 QUA9 CU27 PR21 TE15 PY19  (MECA FLU)  |
 MACRO : SEG3 TRI6 QUA9 CU27 PR18 TE10  (MECA FLU)  |
        |
        |
  La formulation mixte vitesse pression ne permet pas n'importe quel  |
 type d'element. On peut distinguer deux classes d'elements : les  |
 elements a pression continue et ceux a pression discontinue. On ne  |
 dispose dans CASTEM 2000 que des derniers.  |
        |
        |
        |
        A - Les elements quadratiques QUAF  |
        ==================================  |
        |
 P2+bulle - P1 nc (nc : non conforme) et Q2 - P1 nc  |
 (Crouzeix-Raviart) [1]  (Bercovier-Pironneau) [2]  |
 et leurs homologues 3D  |
        |
 Ref :  |
 [1] M. Crouzeix and P.A. Raviart : Conforming and non conforming  |
     finite element methods for solving the stationary Stokes equations.|
     R.A.I.R.O. (7eme annee,decembre 1973,R-3,p.33a76)  |
        |
 [2] M. Bercovier and O. Pironneau : Error estimates for finite element |
     solution of the Stkes problem in the primitive variables.  |
     Numer. Math. 33,p.211-224, 1979.  |
        |
 Les ordres de convergence spatiales sont :  |
 ------------------------------------------  |
  pour la vitesse  O(h**3)  |
  pour la pression O(h**2)  |
  h etant une mesure de l'element.  |
        |
  mise en oeuvre :  |
  ----------------  |
        |
 1/ Faire un maillage compose d'elements LINE ou QUAD.  |
        |
 2/ Transformer les elements du maillage en QUAF.  voir operateur CHAN  |
        |
 3/ Faire les eliminations necessaires de points eventuellement crees  |
    en double.  voir operateur ELIM  |
        |
 4/ Creer les objets MMODEL 'NAVIER_STOKES' associes aux maillages en  |
    precisant QUAF pour le type des elements finis.  |
        voir operateur MODE  |
        $MT = MODE MT 'NAVIER_STOKES' QUAF ;  |
        |
 5/ Creer les champs de vitesse et de pression.  |
    La vitesse  sera un CHPOINT VECT SOMMET  |
    La pression sera un CHPOINT SCAL CENTREP1  |
        voir operateur KCHT  |
    UN = KCHT $MT VECT SOMMET (0 0 0) ;  |
    PN = KCHT $MT SCAL CENTREP1 0 ;  |
        |
        |
        |
        B - Les elements lineaires iso P2 - iso P1 nc MACRO  |
        iso Q2 - iso P1 nc  [1],[2]  |
        =======================================================  |
        |
[… notice tronquée ; texte complet dans l'archive PCW_24]

## NBEL [Maillage Generaux]
    Operateur NBEL
    -------------- NBNO

    RESU1 = NBEL GEO1 (LMOTS1) ;

    Objet :

    L'operateur NBEL donne le nombre d'elements contenus dans une
geometrie. La recherche peut etre restreinte a certain(s) type(s)
d'element(s) et le resultat est alors le nombre d'elements de chaque
type demande.

    Commentaire :

    GEO1 : geometrie (type MAILLAGE)

    LMOTS1 : liste des types d'elements (type LISTMOTS)

    RESU1 : nombre d'elements contenus dans la geometrie (type ENTIER)
        liste des nombres d'elements correspondant aux types
        demandes (type LISTENTI)

    Exemple :

    LIST (NBEL MONOBJ1); pour connaitre le nombre d'elements
        de l'objet MONOBJ1.

## NBNO [Maillage Generaux]
    Operateur NBNO

    ENTI1 = NBNO GEO1 ;

    Objet :

    L'operateur NBNO fournit le nombre de noeuds contenus dans une geo-
metrie.

    Commentaire :

    GEO1 : geometrie (type MAILLAGE)

    ENTI1 : nombre de noeuds (type ENTIER)

    Exemple :

    LIST (NBNO MONOBJ1); pour connaitre le nombre de noeuds
        de l'objet MONOBJ1.

## NEG [Mathematiques Logique]
Operateur NEG
------------- < >

LOG1 = OBJET1 NEG OBJET2 (FLOT1) ;

        OBJET1=ENTIER,FLOTTANT,LISTENTI

Objet :

L'operateur NEG compare les objets OBJET1 et OBJET2.

Dans le cas general, c'est leur identite qui est testee.
Deux objets deduits l'un de l'autre par affectation (=) sont egaux.
Deux objets deduits l'un de l'autre par copie (COPI) sont differents.

Pour certains types d'objet, le test porte sur leur contenu.

Commentaire :

OBJETi : objets a comparer.

FLOT1 : critere de comparaison (type FLOTTANT) entre deux
        flottants. Le critere est egal a 0. par defaut.

LOG1 : resultat logique (type LOGIQUE) ayant pour valeur FAUX
        si les deux objets sont egaux, VRAI sinon.

Remarque :

Si les objets sont des MOTs, il faut respecter l'ordre suivant :
LOG1 = NEG MOT1 MOT2 ;
Dans la comparaison on ne tiendra pas compte des blancs situes a
la fin des mots. (EGA 'AA' 'AA ') est VRAI.

Si on compare des scalaires (ENTIERS ou FLOTTANTS),
OBJET2 sera converti au type de OBJET1.

## NEUT [Multi-physique Multi-physique]
Operateur NEUT

    CHPO2 = NEUT TAB1 CHPO1 ;

     Objet
    Calcul du bilan electrique d'une solution chimique en tout point
    d'un domaine.

    Commentaires
    TAB1 est un objet de type TABLE et de sous type chimi1
        (cf operateur CHI1)

    CHPO1 nom d'un objet de type CHPOIN ayant une composante pour
        chaque espece en solution, et contenant la concentration
        de chaque espece en solution.

    CHPO2 objet de type CHPOIN ayant deux composantes ANIO et CATI.
        ANIO contient la concentration en anions.
        CATI contient la concentration en cations.

## NEWMARK [Mecanique Dynamique] (proc)
    Procedure NEWMARK

    CHPO1 CHPO2 = NEWMARK CHPO3 CHPO4 RIG1 RIG2 RIG3 CHPO5 CHPO6 FLOT1

    Objet :

    Cette procedure calcule un increment de solution en dynamique
pas a pas par l'algorithme de Newmark centre.

    Commentaire :

    CHPO3 : champ de deplacements au debut du pas (type CHPOINT)

    CHPO4 : champ de vitesses au debut du pas (type CHPOINT)

    RIG1 : operateur dynamique (type RIGIDITE)

    RIG2 : matrice de rigidite (type RIGIDITE)

    RIG3 : matrice de masse (type RIGIDITE)

    CHPO5 : champ de forces au debut du pas (type CHPOINT)

    CHPO6 : champ de forces a la fin du pas (type CHPOINT)

    FLOT1 : pas de temps (type FLOTTANT)

    CHPO1 : champ de deplacements a la fin du pas (type CHPOINT)

    CHPO2 : champ de vitesses a la fin du pas (type CHPOINT)

    Remarque :

    Les arguments de la procedure NEWMARK doivent etre entres dans
l'ordre indique dans la syntaxe.

    L'expression de l'operateur RIG1 est la suivante :

        RIG1 = RIG2 + AMOR1*(2/FLOT1) + RIG3*(4/FLOT1/FLOT1)

oº AMOR1 est la matrice d'amortissement .

    Les vitesses doivent etre des champs dont les noms de composantes
sont identiques a ceux de champs de deplacements .

## NLIN [Multi-physique Multi-physique]
$X NLIN (Construction de matrices elementaires)

      Operateur NLIN

      RIG1 = 'NLIN' MOT1 MAIL1 (MAIL2) TAB1 TAB2 ...
        ...  |('EREF')| ('ERRJ') ('MATK') ('MREG') ...
        |('ERF1')|
        ...  |('CHPO')| MOT2 ;
        |('CHAM')|

      Objet :

      L'operateur NLIN (Noyau LINeaire) cree une matrice correspondant
      a la discretisation d'une forme bilineaire par une methode
      d'elements finis scalaires.

      On aura :

        --- /
        \  |  dN_s  dM_r
      RIG1 = /  |  ------ d_qsl c_qrk ----- dOmega
        ---  |  dx_l  dx_k
        q,s,r,k,l  |
        / Omega

      ou : - Omega est le domaine d'integration de dimension n<=m,
        inclus dans R^m, et {x_1,...,x_m} une base orthogonale
        de R^m ;
        - k, l sont des indices muets variant de 0 a m (ou n si
        un des mots-cles 'EREF' ou 'ERF1' est specifie) avec
        la convention que d/dx_0 est l'identite ;
        - q varie de 1 a n_op, nombre d'operateurs a discretiser ;
        - r varie de 1 a n_vp, nombre de variables primales ;
        - s varie de 1 a n_vd, nombre de variables duales ;
        - \M^r (resp. \N^r) sont les fonctions d'interpolation de
        l'espace d'elements finis de la variable r (resp. s) ;
        - c_qkr (resp. d_qsl) sont des multiplicateurs. Ils sont
        obtenus par la multiplication de coefficients.
        Un coefficient est obtenu par une loi de comportement
        dependant de donnees connues.

      MOT1 : objet de type MOT, nom d'une famille d'elements finis
        utilisee pour l'interpolation geometrique.

      MAIL1 : objet de type MAILLAGE constitue d'elements de type
        QUAF, support de l'ensemble des espaces d'elements
        finis utilises. Si MAIL2 n'est pas donne, MAIL1 sert
        egalement de domaine d'integration Omega.

      MAIL2 : objet optionnel de type MAILLAGE constitue d'elements
        surfaciques de type QUAF. Ce maillage surfacique doit
        s'appuyer sur MAIL1 et sert de domaine d'integration
        Omega.

      TAB1 : objet de type TABLE contenant les informations liees
        aux variables primales.

      TAB2 : objet de type TABLE contenant les informations liees
        aux variables duales.

      EREF : mot-cles indiquant que les integrations sont
      ERF1 effectuees sur les elements de reference ou sur les
        elements de reference dont le volume a ete normalise
        a 1.

      ERRJ : mot-cle indiquant que, si le signe du jacobien change
        sur un element, l'operateur n'emet pas une erreur
        mais renvoie un entier (code d'erreur).

      MREG : mot-cle indiquant que MAIL1 est constitue d'elements
        identiques (orientation comprise).

      CHAM : mot-cle indiquant que NLIN renvoie des objets de type
        MCHAML (forces non assemblees) au lieu de CHPOINT le
        cas echeant (cf. note 1).

      MOT2 : Famille de methode d'integration a utiliser.

      RIG1 : objet de type RIGIDITE (ou MATRIK si le mot-cle MATK
        est utilise) contenant la matrice de l'operateur
        discretise.
        (ou objet de type ENTIER si mot-cle ERRJ)

      Commentaires :

        Un espace de discretisation est un regroupement
        coherent d'elements finis (une "famille"). Les
        familles disponibles, qui ne comprennent pas forcement
        toutes les formes geometriques d'elements, sont :
        * 'CSTE' : constant par element (L2 degre 0) ;
        * 'LINM' : lineaire par morceaux (L2 degre 1) ;
        * 'LINE' : lineaire (H1 degre 1) ;
        * 'LINC' : lineaire non conforme (degre 1) ;
        * 'LINB' : lineaire + bulle (H1 degre 1) ;
        * 'QUAI' : quadratique incomplet (H1 degre 2) ;
        * 'QUAD' : quadratique (H1 degre 2) ;
        * 'QUAF' : quadratique + bulle (H1 degre 2) ;
        * 'CUBI' : cubique (H1 degre 3) ;
        * 'BULL' : bulle (H10 degre 0).
[… notice tronquée ; texte complet dans l'archive PCW_24]

## NLOC [Mecanique Resolution]
Operateur NLOC (NON LOCAL)
-------------------------- PASAPAS

CHAM1 = NLOC  ( | 'MOYE' | )  CHAM2 CHAM3 ;
        | 'SB  ' |

Objet :

L'operateur NLOC (Non LOCal) construit a partir d'un MCHAML CHAM2,
d'un MCHAML CHAM3 de sous-type 'CONNECTIVITE NON LOCAL', cree a
l'aide de l'operateur CONNEC, LE MCHAML CHAM1 construit de la
meme maniere que CHAM2.
La methode de regularisation a utiliser est donnee par le mot-cle
'MOYE' (methode par defaut, si aucun mot-cle n'est donne) ou
'SB ' (methode stress-based).

Methode 'MOYE' :
Les composantes de CHAM2 dont le nom se trouve dans LISMO1 sont
moyennees, les autres sont reproduites a l'identique.

Methode 'SB ' :
La composante de CHAM2 dont le nom se trouve en premier dans LISMO1
est moyennee. Le champ CHAM2 doit contenir le champ à moyenner,
l'etat de contrainte du milieu regularise ainsi que des caracteristiques
(contrainte limite de traction, taille moyenne de l'élément).

Commentaire :

C'est un limiteur de localisation (de la meme maniere que
l'utilisation du second gradient ou de milieux de COSSERAT).

La methode 'MOYE' permet d'obtenir des resultats plus objectifs pour
les calculs non lineaires et en particulier en cas d'ecrouissage negatif
(adoucissement) en fournissant un moyen de s'affranchir des problemes
de dependance du maillage.

La methode de régularisation 'SB ' se base sur la méthode nonlocale
(NLOC) en introduisant l'influence de l'etat de contrainte dans le
milieu regularise sur les interactions nonlocales. Cette methode
permet d'ameliorer la description du champ d'endommagement a la rupture
ainsi que proche de bords libres comparee a la methode originale.
Plus de details peuvent etre trouves dans la publication suivante
qui sert egalement de reference pour citer ce travail :
  Giry C., Dufour F., Mazars M. Stress-based nonlocal damage model.
  International Journal of Solids and Structures 48 (2011) 3431-3443

CHAM2 : ('MOYE') MCHAML contenant minima les composantes a moyenner
        ('SB ') MCHAML contenant le champ a regulariser,le champ de
        contraintes principales, le champ de contrainte
        limite de traction et le champ de taille moyenne
        des elements

CHAM3 : MCHAML de type 'CONNECTIVITE NON LOCAL' construit par CONNEC

CHAM1 : MCHAML resultat

Attention :

  Lorsqu'une composante de CHAM2 est a moyenner, son support
  geometrique doit etre contenu dans celui de CHAM3 sinon on sort
  avec un message d'erreur.

## NNOR [Mecanique Resolution]
Operateur NNOR

Syntaxe 1 : Norme Infinie
   OBJET2 = NNOR  ('INFI')  OBJET1  ( | ('AVEC') | LMOTS1 )  ...

        ... ('RORF' VAL1 'CREF' VAL2 'LCAR' VAL3) ;

Syntaxe 2 : Norme Euclidienne
   OBJET2 = NNOR 'EUCL' OBJET1 (RIGID1) ;

Objet :

L'operateur NNOR rend un objet unitaire au sens de la norme infinie
(par defaut) ou de la norme Euclidienne.

La norme infinie (ou norme sup) d'un champ (mot-cle 'INFI')
correspond a sa plus grande valeur, tous noeuds et toutes
composantes confondues :

  + on peut limiter la recherche de la plus grande valeur a un
    sous-ensemble de l'objet en donnant une liste de composantes a
    considerer (mot-cle 'AVEC') ou a exclure (mot-cle 'SANS')

  + on peut redimensionner les composantes 'P' et 'PI' avant la
    recherche du maximum en fournissant les coefficients 'RORF',
    'CREF' et 'LCAR' du modele LIQUIDE correspondant

La norme Euclidienne (ou norme 2) d'un champ (mot-cle 'EUCL')
correspond a la racine carre de la somme des carres des valeurs
en chaque noeud et en chaque composante. Contrairement a la
norme sup, la norme 2 est associee a une forme quadratique dont
on peut eventuellement fournir la matrice (symetrique definie
positive).

Commentaire :

OBJET1 : objet a normer (type CHPOINT, TABLE de sous-type
        'BASE_MODALE' ou 'BASE_DE_MODES')

OBJET2 : objet norme de meme type que OBJET1

LMOTS1 : liste des composantes a considerer ou a exclure (type
        LISTMOTS)

'AVEC' : mot-cle indiquant que l'on regarde uniquement, dans
        la recherche de maximum, les valeurs associees aux
        composantes citees dans LMOTS1 (option par defaut)

'SANS' : mot-cle indiquant que l'on exclut, dans la recherche du
        maximum, les valeurs associees aux composantes citees
        dans LMOTS1

VAL1 | : valeurs des coefficients 'RORF', 'CREF', 'LCAR' donnees
VAL2 |  dans l'operateur MATE (materiau liquide ou materiau
VAL3 |  homogeneise fluide-structure)

RIGID1 : matrice symetrique definie positive associee a la forme
        quadratique (donc a la norme)

## NOCOMCHI [Multi-physique Multi-physique] (proc)
 Procedure NOCOMCHI
 ------------------ NOESPCHI

MO4 MO3 ENT2 = NOCOMCHI TAB1 MO1 <MO2> <ENT1> ;

     Objet
     Tous les composants chimiques utilises par CHI1 et CHI2 ayant:
     - un nom chimique (dont le nombre de lettres est variable)
     - un numero d'identification dans la base de donnees.
     - un nom de 4 lettres attribue par le code.
     Cette procedure permet de retrouver ces 3 elements lorsqu'un
     seul est connu.

     Commentaires

     TAB1 est une table issue de CHI1.

     MO1 mot cle

        'NUMCOMP' ENT1 sera le numero d'identification du composant.

        'NOMINT' MO2 sera le nom attribue par le code a ce composant

        'NOMCOMP' MO2 sera le nom chimique ( tel qu'il est dans la
        base de donnees)

     en sortie nous aurons:

        MO4 nom chimique
        MO3 nom attribue par le code
        ENT2 numero d'identification

## NOEL [Mathematiques Autres]
  Operateur NOEL

 CHP2 = NOEL MOD1 CHP1 <MOT> ;

 Objet :

 L'operateur NOEL transforme un CHPOINT definit sur les points
 SOMMET en un CHPOINT definit sur les points interieurs a l'element,
 CENTRE ou CENTREP1.
 Cet operateur necessite la donnee d'un objet modele 'NAVIER_STOKES'.

 Commentaires :

 MOD1 : Objet de type MMODEL 'NAVIER_STOKES'
 CHP1 : Objet de type CHPOINT (points SOMMET)
 CHP2 : Objet de type CHPOINT, CHPOINT resultat
 MOT : Objet de type MOT valant : CENTRE ou CENTREP1 ou MSOMMET
        par defaut on cree un CHPOINT CENTRE

 Complements d'information :

 NOEL est la transformation inverse de ELNO.

 Le cas MSOMMET consiste seulement a faire une reduction du CHAMP
(operateur REDU) sur les points MSOMMET de l'element. Il y a
toujours continuite entre elements.

## NOESPCHI [Multi-physique Multi-physique] (proc)
Procedure NOESPCHI
------------------ NOCOMCHI

MO3 ENT2 = NOESPCHI TAB1 <MO2> <ENT1> ;

    Objet
    Toutes les especes chimiques utilises par CHI1 et CHI2 ayant:
    - un numero d'identification dans la base de donnees.
    - un nom de 4 lettres attribue par le code.
    Cette procedure permet de retrouver le nom attribue par le code
    connaissant le numero d'identification et reciproquement.

    Commentaires

    TAB1 est une table issue de CHI1.

    ENT1 sera le numero d'identification de l'espece.

    MO2 sera le nom attribue par le code a cette espece.

    en sortie nous aurons:

        MO3 nom attribue par le code
        ENT2 numero d'identification

## NOEU [Maillage Points]
    Operateur NOEUD

    Objet :

    L'operateur NOEUD permet d'identifier un noeud dans un maillage ou
permet de connaitre le numero actuel d'un noeud d'apres son nom.

    Deux syntaxes sont possibles :

    |  1ere possibilite  |

    POIN1 = NOEUD N1 ;

    Objet :

    L'operateur NOEUD permet d'identifier le N1-ieme noeud du maillage.
Les numeros de noeuds apparaissent dans les commandes LIST et TRAC NOEUD

    Exemple : P = NOEU 321 ;

    |  2eme possibilite  |

    ENTI1 = NOEUD MOT1 ;

    Objet :

    L'operateur NOEUD permet de connaitre le numero ENTI1 (type ENTIER)
d'un noeud d'apres son nom MOT1 (type POINT)

    ATTENTION :

    Il s'agit du numero actuel, qui peut etre modifie par la suite.

## NOMC [Langage Objets]
    Operateur NOMC

    CHPO2 = NOMC  | MOT1  | CHPO1 ( 'NATU' |'INDETER'
        | LISTMOT1 LISTMOT2 |  |'DIFFUS'

    CHE2 = NOMC  | MOT1  | CHE1  ;
        | LISTMOT1 LISTMOT2 |

    Objet :

    L'operateur NOMC cree un nouveau champ par points, ou champ par
    elements, en changeant eventuellement le nom de certaines composantes.
    Le champ par elements ne doit comporter qu'un constituant.
    On utilise la syntaxe specifiant un mot dans les cas ou le champ par
    points, ou le champ par elements, possede une composante. Dans les autres
    cas, on precise la liste des composantes a renommer selon une
    seconde liste.

    Commentaire :

    CHPO1 : champ par points (type CHPOINT)

    CHE1 : champ par elements (type MCHAML)

    MOT1 : nouveau nom attribue a la composante (type MOT)

    LISMOT1 : liste des composantes a renommer (type LISTMOTS)

    LISMOT2 : liste des nouvelles composantes (type LISTMOTS)

    CHPO2 : objet resultat (type CHPOINT)

    CHE2 : objet resultat (type MCHAML)

    Remarques :

    1. Les noms de composantes font 4 caracteres.

    2. La liste LISMOT1 des composantes a remplacer dans
CHPO1 peut n'etre qu'une sous-liste de la liste de toutes les composantes
de CHPO1. La i-eme composante de LISMOT1 sera remplacee par la i-eme
composante de LISMOT2 (ces deux listes doivent avoir la meme longueur,
      celle-ci etant inferieure ou egale au nombre de composantes).

## NOMM [Langage Base]
    Directive NOMM

    NOMM LE_NOM OBJET ;

    Objet :

    La directive NOMMer permet de donner un nom a l'objet OBJET.

Si LE_NOM designe un MOT, c'est la valeur de ce MOT qui sera le nom
de l'objet. Sinon, ce sera la chaine LE_NOM.

Le nom de l'objet est automatiquement converti en MAJUSCULES.

## NON [Mathematiques Logique]
    Operateur NON

    LOG1 = NON LOG2 ;

    Objet :

    L'operateur NON est la negation de la proposition logique LOG2 (type
LOGIQUE). Le resultat LOG1 est de type LOGIQUE.

## NORM [Mathematiques Autres]
    Operateur NORM

    FLOT1 = NORM VEC1 ;

    Objet :

    L'operateur NORM calcule la norme FLOT1 (type FLOTTANT) du
vecteur VEC1 (type POINT).

## NORMALIM [Mathematiques Fonctions] (proc)
Procedure NORMALIM

LREEL1 EVOL1 = NORMALIM EVOL2 (FLOT1)

objet :

La procedure NORMALIM permet de generer les fonctions normees
EVOL1 (contenant N courbes) associees a EVOL2 (contenant N
courbes). LREEL1 (contenant N FLOTTANT) contient la norme de
chaque courbes de EVOL1.

options :

La norme introduite est par defaut la norme L2 evaluee a l'aide
de l'operateur SOMM. Si le FLOTTANT FLOT1 est introduit, on se
trouve dans le cas d'une analyse en ondelette et la norme est
determinee sur base d'une echantillonnage de periode FLOT1.

## NORV1 [Mathematiques Statistiques] (proc)
Procedure NORV1

  CETTE PROCEDURE A ETE MISE GRACIEUSEMENT
 A DISPOSITION DE LA COMMUNAUTE CAST3M
   PAR F. DUPRAT (LMDC - INSA Toulouse)

  Cette procedure est appelee par la procedure HASOFER

## NOTI [Presentation Presentation]
    Directive NOTICE

    NOTICE  | GIBI ;
        | CASTEM2000 ;

    Objet :

    La directive NOTICE permet d'obtenir respectivement la notice
d'emploi de GIBI ou CASTEM2000.

    Remarque :

    Cette notice s'imprime sur l'unite logique (6 par defaut)
definie par la directive OPTION :

        OPTION IMPR INUM ;

## NOUV [Presentation]
Documentation Generale sur Cast3M :
  http://www-cast3m.cea.fr/index.php?xml=maj2011

Modification de la gestion des procedures et des notices.

Elles sont maintenant directement lues dans des fichiers eponymes appartenant
aux repertoires specifies par les variables d'environnement CASTEM_PROCEDUR24
et CASTEM_NOTICE24.

Par defaut et dans l'ordre, ce sont:
Le repertoire courant
Le repertoire ./procedur
Le repertoire d'installation

## NS [Fluides Resolution]
    Operateur NS

    SYNTAXE ( EQEX ) : Cf operateur EQEX

  1/ Formulation non conservative

a/
      'OPER' 'NS' ro un mu 'INCO' 'UN'

b/
      'OPER' 'NS' nu 'INCO' 'UN'
      'OPER' 'NS' nu s 'INCO' 'UN'

     approximation de Boussinesq :
a/
      'OPER' 'NS' ro un mu gb tn tref 'INCO' 'UN'

b/
      'OPER' 'NS' nu gb tn tref 'INCO' 'UN'

  2/ Formulation conservative (dilatable)

      'OPER' 'NS' mu un 'INCO' 'GN'
      'OPER' 'NS' mu un S 'INCO' 'GN'

    OBJET :

 Cet operateur discretise les termes de diffusion, de convection et
eventuellement le terme source de l'equation de Navier - Stokes.
 Pour une dicretisation element finis EFM1 (algorithme explicite),
il calcule l'increment.
 Pour une dicretisation element finis EF (algorithme implicite ou semi
implicite), il calcule les matrices elementaires et les second membres.

 Suivant l'option les equations sont traitees sous forme conservative
ou non conservative.

1/ Formulation non conservative

a/
ro(du/dt + u Grad u) = mu Lapl u - Grad p < + s (=S) >
   ----- ------ < + ro*g*beta(T-Tref) >

b/
du/dt + u Grad u = nu Lapl u - 1/ro Grad p < + s (=S/ro) >
----- ----------- < + g*beta(T-Tref) >

2/ Formulation conservative (avec la vitesse massique comme inconnue).

dG/dt + Div ( u X G ) = mu (Lapl u + 1/3 (Grad Div u))
        - Grad p < + S >
(Les termes soulignes ne sont pas discretises dans NS voir procedure EXEC)

    Commentaires

 ro,nu,mu densite, viscosite cinematique (resp. dynamique) moleculaire
        FLOTTANT ou CHPOINT SCAL CENTRE ou CHPOINT SCAL SOMMET ou MOT
 s,S Source volumique de quantite de mouvement. (s=S/ro)
        POINT ou CHPOINT VECT CENTRE ou MOT

 approximation de Boussinesq :
 gb Coefficient de flottabilite (g*beta ou g est l'accelleration
        de la pesanteur et beta le coefficient de dilatabilite)
        POINT ou CHPOINT VECT CENTRE ou MOT
 tn Champ de temperature
        CHPOINT SCAL SOMMET ou MOT
 tref temperature de reference
        FLOTTANT ou CHPOINT SCAL SOMMET ou MOT

 un Champ de vitesse transportant
        CHPOINT VECT SOMMET ou MOT
 gn Champ de vitesse massique
        CHPOINT VECT SOMMET ou MOT

 Un coefficient de type MOT indique que l'operateur va chercher le
 coefficient dans la table INCO a l'indice MOT.

    Options : (EQEX)

 1/ Discretisation EFM1 : OPTI EFM1

 Algorithme Explicite

 La discretisation des termes de convection peut etre :

 centree CENTREE
 decentree SUPG
 decentree avec capture de choc SUPGCC Option par defaut

 Formulation non conservative NOCONS Option par defaut
 Formulation conservative CONS

 2/ Discretisation EF : OPTI EF

 Algorithme IMPLICITE OPTI IMPL ou SEMI omega

 La discretisation des termes de convection peut etre :

 centree CENTREE
 decentree SUPG
 decentree avec capture de choc SUPGCC Option par defaut
 tenseur visqueux (ordre 2 en temps) TVISQ

 Formulation non conservative NOCONS Option par defaut

## NSCLIM [Fluides Limites] (proc)
   Procedure NSCLIM

OBJ1 = NSCLIM tit TIMPR NOMQ val1 <'SWIRL' val2> NCO Tps
        MODG MODC <OBJ2> NOMG
        < NOMT sgm portee> ;

   OBJET :

 Procedure creant un CHPOIN pour les conditions limites NAVIER_STOKES

   Commentaires

  tit CHAI titre
  TIMPR LOGIQUE impressions et trace de controle si VRAI
  NOMQ MOT Type de condition limite a choisir parmi
        DEBIT Debit impose (Debit entrant >0)
        <'SWIRL' val2> swirl impose
        val2: FLOTTANT pourcentage par rapport a la vitesse debitante
        VITESSE Vitesse imposee (Vitesse entrante >0)
        TEMPERATURE Temperature imposee (ou scalaire)
        ADHERENCE u=v=w=0 imposees
        FPAROI u.n=0 et Fparoi
        SYMETRIE u.n=0 et rien si vitesse rien si Temperature
        SORTIE -> p=0
        PRESSION -> p=p0

  VAL1 FLOTTANT si constant en temps
      ou EVOLUTION sinon

  NCO MOT nom de la composante sur laquelle porte la
        condition limite
  TPS FLOTTANT Temps
  MODG MODELE geometrie globale (NAVIER_STOKES)
  MODC MODELE geometrie sur laquelle porte la condition limite
  <OBJ2> CHPOIN CHPOIN facultatif contenant les conditions limites
        a modifier

  NOMG MOT = STRICTEMENT
        LARGEMENT

  NOMT MOT = SGE
        XXXXXXXXX

   Exemple

rtf.'CLIM' = NSCLIM tit TIMPR 'TEMPERATURE' Tinj 'TF' Tps
        $vtf $esort (rtf.'CLIM') 'STRICTEMENT' ;

## NSKE [Fluides Resolution]
    Operateur NSKE

    SYNTAXE ( EQEX ) : Cf operateur EQEX

  1/ Cas incompressible

      'OPER' 'NSKE' nu nut 'INCO' 'UN' 'KN' 'EN'
      'OPER' 'NSKE' nu nut s 'INCO' 'UN' 'KN' 'EN'

     approximation de Boussinesq :
      'OPER' 'NSKE' nu nut gb tn tref 'INCO' 'UN' 'KN' 'EN'

  2/ Cas compressible (dilatable)

      'OPER' 'NSKE' ro mu mut un 'INCO' 'GN' 'KN' 'EN'
      'OPER' 'NSKE' ro mu mut un S 'INCO' 'GN' 'KN' 'EN'

    OBJET :

 Cet operateur discretise les termes de diffusion, de convection et
eventuellement le terme source des equations de Navier - Stokes
couplees au modele de turbulence K-epsilon, et calcule l'increment pour
un algorithme explicite.

 Suivant l'option les equations sont traitees sous forme conservative
ou non conservative.

1/ Formulation non conservative

du/dt + u Grad u = (nu+nut) Lapl u - 1/ro Grad p < + s (=S/ro) >
----- ----------- < + g*beta(T-Tref) >

2/ Formulation conservative (avec la vitesse massique comme inconnue).

dG/dt + Div ( u X G ) = (mu+mut)(Lapl u + 1/3 (Grad Div u))
        - Grad p < + S >
(Les termes soulignes ne sont pas discretises dans NSKE voir procedure EXEC)

    Commentaires

 ro densite
        FLOTTANT ou CHPOINT SCAL CENTRE ou MOT
 nu,mu viscosite cinematique (resp. dynamique) moleculaire
        FLOTTANT ou CHPOINT SCAL CENTRE ou MOT
 nut,mut viscosite cinematique (resp. dynamique) turbulente
        CHPOINT SCAL CENTRE ou MOT
 le champ de viscosite turbulente calcule dans NSKE est restitue dans
 nut ou mut
 s,S Source volumique de quantite de mouvement. (s=S/ro)
        POINT ou CHPOINT VECT CENTRE ou MOT

 approximation de Boussinesq :
 gb Coefficient de flottabilite (g*beta ou g est l'acceleration
        de la pesanteur et beta le coefficient de dilatabilite)
        POINT ou CHPOINT VECT CENTRE ou MOT
 tn Champ de temperature
        CHPOINT SCAL SOMMET ou MOT
 tref temperature de reference
        FLOTTANT ou CHPOINT SCAL SOMMET ou MOT

 un Champ de vitesse transportant
        CHPOINT VECT SOMMET ou MOT
 gn Champ de vitesse massique
        CHPOINT VECT SOMMET ou MOT

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

## NTAB [Post-traitement Affichage]
    Directive NTABLEAU
    ------------------ DESS

   NTAB (EVOL1 ET EVOL2 ET ... EVOLN) ( 'TITR' MOT1 ) ;
        (CHPE ) ( 'STITR' MOT2 )
        (CHPP ) ( 'TCOL' (ENTI1 MOT3)
        ( 'TLIG' (ENTI2 MOT4)
        ( 'TRILIG' ENTI3 )
        ( 'TRICOL' ENTI4 )
        ( 'TEXCOU' ENTI5 )
        ( 'LIGCOU' ENTI6 )
        ( 'COLCOU' ENTI7 )
        ( 'LOGCOU' ENTI8 )
        ( 'TITCOU' ENTI9 )
        ( 'NODATE' )
        ( 'NOCENTER' )
        ( 'NOLIG' )
        ( 'PAGE' )
        ( 'NOPAGE' )
        ( 'LOGO' )

    Objet :

    Cette directive permet de tracer un tableau a partir d'objets de
    type EVOLUTIO, CHAMELEM ou CHAMPOIN.

    * EVOLi evolutions :
      Toutes les valeurs des abcsisses sont regroupees dans la
      premiere colonne.
      Une evolution n'est prise en compte que si son abscisse est un
      nombre (ENTIER ou FLOTTANT).
      Les ordonnees sont imprimees en face des valeurs
      correspondantes, a raison d'une colonne par evolution entree.

    * CHPP champ par point :
      Seul le premier sous-champ est affiche. Pour voir les autres,
      faire une procedure pour les extraire et les afficher.

    * CHPE champ par element :
      idem.

    Commentaire :

    Par defaut:
       On centre les tableaux.
       On utilise le titre de l'objet
       Pas de sous-titre.
       On affiche la date.
       Les numeros de page sont mis si necessaire.

    * Les options generales possibles sont :

    'TITR' : mot-cle (type MOT) suivi de
    MOT1 : titre du tableau (defaut = titre de l'objet)

    'STITR' : mot-cle (type MOT) suivi de
    MOT2 : sous-titre du tableau (defaut = aucun)

    'TCOL' : mot-cle (type MOT) suivi de
    ENTI1 MOT3 : MOT3 devient l'en-tete de la colonne ENTI1
ou LMOT1 : LMOT1 sont les noms des colonnes de 1 a la dimension de
        LMOT1.

    'TLIG' : mot-cle (type MOT) suivi de
    ENTI2 MOT4 : MOT4 devient le nom de la ligne ENTI2
ou LMOT2 : LMOT2 sont les noms des lignes de 1 a la dimension de
        LMOT2.

    'TRILIG' : mot-cle (type MOT) demandant le tri des lignes suivi
        de
    ENTI3 : numero de la colonne de reference.

    'TRICOL' : mot-cle (type MOT) demandant le tri des colonnes
        suivi de
    ENTI4 : numero de la ligne de reference.

    * Changement des couleurs

    Attention a ne pas utiliser des couleurs qui n'existent pas sur la
    sortie utilisee.

    'TEXCOU' : mot-cle (type MOT) permettant de modifier la couleur
        du texte, suivi de
    ENTI5 : numero de la couleur du texte.

    'LIGCOU' : mot-cle (type MOT) suivi de
    ENTI6 : numero de la couleur des encadrements.

    'TITCOU' : mot-cle (type MOT) suivi de
    ENTI7 : numero de la couleur du titre.

    'LOGCOU' : mot-cle (type MOT) suivi de
    ENTI8 : numero de la couleur du logo.

    'COLCOU' : mot-cle (type MOT) suivi de
    ENTI9 : numero de la couleur des intitules de colonne.

    * options d'affichage

    'NODATE' : mot-clef supprimant l'affichage de la date.

    'NOLIG' : mot-clef supprimant l'encadrement automatique.

    'NOCENTER' : mot-clef demandant des tableaux non centres.

    'PAGE' : mot-clef forçant l'affichage des numeros de page.

    'NOPAGE' : mot-clef empechant l'affichage des numeros de page.

    'LOGO' : mot-clef indiquant qu'il faut afficher le logo.

    Exemple:

NTAB (EVOL1 ET EVOL2 ET EVOL3) 'TITR' 'Resonances circuits 1, 2 et 3';

## NUAG [Mathematiques Autres]
    Operateur NUAGE

   Cet operateur cree un objet NUAGE de differentes manieres.

    |  1ere possibilite  |
   NUA1 = NUAGE |  'COMP'  NOMCOMP1 OBJE1_1 OBJE1_2 .. OBJE1_M
        | ..  'COMP'  NOMCOMP2 OBJE2_1 OBJE2_2 .. OBJE2_M
        | .........
        | ..  'COMP'  NOMCOMPN OBJEN_1 OBJEN_2 .. OBJEN_M

   NUA1 = NUAGE | NOCOMP1*TYP1 NOCOMP2*TYP2 ... NOCOMPN*TYPN
        |  OBTYP1_1 OBTYP2_1 .... OBTYPN_1
        |  OBTYP1_2 OBTYP2_2 .... OBTYPN_2
        |  ..........
        |  OBTYP1_M OBTYP2_M .... OBTYPN_M

    Objet:

    Cet operateur permet de definir un objet de type NUAGE.
Un NUAGE est un ensemble de M N-uplets. Chaque composante
d'un N-uplet porte un nom (NOCOMPI).

Deux syntaxes sont autorisees :

   La premiere lit le nom puis tous les objets d'une composante etc..

   La seconde lit tous les noms de composantes avec le type des
objets, puis lit tous les N-uplets les uns apres les autres.

 Exemple : On veut definir un nuage qui decrit la variation
d'une courbe de traction en fonction de la temperature. Supposons
que EV1 EV2 EV3 sont les trois objets EVOLUTIO representant
les courbes de traction pour les temperatures T1 T2 T3.

    La definition du NUAGE peut alors se faire des deux facons
suivantes :

NU1 = NUAGE 'TEMPERATURE'*'FLOTTANT' 'TRAC'*'EVOLUTIO'
        T1 EV1 T2 EV2 T3 EV3;

NU2 = NUAGE 'COMP' 'TEMPERATURE' T1 T2 T3
        'COMP' 'TRAC' EV1 EV2 EV3 ;

    |  2eme possibilite  |

NU1 = NUAGE CHPO1 ;

    Objet :

    L'operateur NUAGE change un champ par point en nuage.
    A chaque point du champ par point il fait correspondre
un n-uplet du nuage compose des composantes du champ par point.

    Commentaire :

    NUA1 : objet resultat (type 'NUAGE')

    CHPO1 : objet de type 'CHPOINT'

    Remarque :

    Les composantes non definies dans une sous-zone du champ par
point sont prises egales a zero dans le n-uplet.

    Exemple :

    CHP1 = MANU 'CHPO' POIN1 2 'UX' 10 'UY' 20 ;
    NUA1 = NUAGE CHP1 ;
    LIST NUA1 ;
    Le nuage contient 1 n-uplet a 2 composantes
    Composante 1 de nom UX et de type FLOTTANT
    Liste des valeurs associees
    10.
    Composante 2 de nom UY et de type FLOTTANT
    Liste des valeurs associees
    20.

    |  3eme possibilite |

  NUA1 = NUAGE CHAM1;

    Objet :

    L'operateur NUAGE change un champ par elements en nuage.
A chaque point support du champ par elements, il fait correspondre
un n-uplet du nuage composes des valeurs des composantes aux points
consideres.

    Commentaire :

    NUA1 : objet resultat de type 'NUAGE'
    CHAM1 : objet de type 'MCHAML'

    Remarque :

    Toutes les composantes du champ par elements doivent etre de
type 'FLOTTANT'.
     Les composantes non definies dans une sous-zone du champ par
elements sont prises egales a zero dans le n-uplet.

    Exemple :

    LIG1 = P1 DROI 5 P2;
    CHAM1 = MANU CHML LIG1 G 9.81;
    CHAM2 = COOR 1 CHAM1;
    NUA1 = NUAGE CHAM2;
    LIST NUA1;
    Le nuage contient 10 n-uplets a une composante
    Composante 1 de nom SCAL et de type FLOTTANT
    Liste des valeurs associees : 10

## OBJE [Langage Methodes]
    Operateur OBJE
    -------------- METHODE

      OBJET1 = OBJET METH1 ;

    Objet :

    L'operateur OBJET cree un objet de type OBJET de classe
METHODE1 sur lequel on applique le constructeur METH1.

      Commentaire :

  La difference essentielle entre un OBJET et une TABLE est qu'il
n'est pas possible de se servir d'un OBJET sans passer par ses
methodes. Celles-ci se definissent par les methodes METHODE ou
HERITE qui sont mises de facon systematique dans les objets.

  Pour appliquer une methode sur un objet la syntaxe est:

 RESU1 RESU2... = OBJET1%METH1 ARG1 ARG2 ....;

  METH1 est une methode qui se definit comme une procedure. Il faut
seulement commencer par DEBMETHODE au lieu de DEBPROCEDUR et terminer
par FINMETHODE au lieu de FINPROCEDUR.
  A l'interieur de la methode METH1 on peut acceder aux elements
contenus dans l'objet par la syntaxe suivante :
Pour l'element ELE1 on pourra ecrire
       %ELE1 = ... ou
       RES = %ELE1 + ENT1 +....

Tout comme pour les tables ELE1 est un objet quelconque

## OBTE [Entree-Sortie Entree-Sortie]
  Operateur OBTENIR
  ----------------- MESS

  OBTENIR OBJET1*TYP1 ( OBJET2*TYP2 ....) ;

  Objet :

  L'operateur OBTENIR permet d'acquerir interactivement au clavier
un ou plusieurs objets de type TYPi.

  Remarque :

  Il est possible d'omettre le type ; dans ce cas, il ne faut pas
mettre le *.

  Si un ou plusieurs objets demandes ne sont pas fournis, un objet
de type ANNULE est crée. S'il s'agit d'un LISTENTI ou LISTREEL,
l'objet garde, s'il y a lieu, la liste d'éléments déjà fournis.

  La donnee entree au clavier peut etre : un ENTIER, un FLOTTANT,
un MOT, un LOGIQUE (VRAI-FAUX),un LISTENTI, un LISTREEL ou un nom
deja connu par CAST3M.

  Dans le cas de LISTENTI ou LISTREEL, il ne peut y avoir qu'un seul
objet en lecture. La liste des valeurs constituant l'objet peut etre
de longueur quelconque et peut etre donnée en une ou plusieurs fois.

  Exemple :

  La procedure LIREFLOT est un exemple d'emploi de OBTENIR.

       DEBPROC LIREFLOT UMIN*FLOTTANT UMAX*FLOTTANT ;
       REPETER BLOC1 ;
       OBTENIR FL*FLOTTANT ;
       SI (( >EG FL UMIN) ET ( <EG FL UMAX)) ;
       QUITTER BLOC1;
       FINSI ;
       MESSAGE ' DONNEZ UN NOMBRE COMPRIS ENTRE' UMIN 'ET' UMAX;
       FIN BLOC1;
       FINPROC FL;

## ONDE [Mathematiques Fonctions]
    Operateur ONDE

| 1ere possibilite : transformation par ondelettes continue |

    Objet :

    L'operateur ONDE construit la transformee par ondelettes
 continue d'un signal.

    Commentaire :

    N1 : on utilise, pour la transformee de Fourier rapide,
        un nombre de points egal a 2**N1 (type ENTIER)
        (Si le signal traite est plus long, on le tronque;
        s'il est plus court, on le complete par des 0.)

    EVOL2 : objet contenant le signal a etudier (type EVOLUTION);
        les abscisses doivent etre a pas constant, les valeurs
        du signal etant les ordonnees. L'objet ne doit contenir
        qu'une seule courbe.

    MOT1 : mot indiquant le type de sorties voulues

        'REIM' pour partie reelle et partie imaginaire / Frequence
        'MOPH' pour module et phase / Frequence

   'FMIN' : mot-cle suivi de :
    FLOT1 : frequence minimale visualisee; elle sera superieure a 0.

   'FMAX' : mot-cle suivi de :
    FLOT2 : frequence maximale visualisee; elle sera inferieure
        a 1/(2*DT), DT etant le pas de temps du signal d'entree.
        (type FLOTTANT)

   'NFRQ' : mot-cle suivi de :
    FLOT3 : nombre de pas en frequence
        (type FLOTTANT, valeur par defaut = 50 )

   'PULS' : mot-cle suivi de :
    FLOT4 : pulsation de l'ondelette mere de Morlet
        (type FLOTTANT, valeur par defaut = 5. )

    CHP1 : objet contenant la transformee, sous forme d'un chpo a deux
        composantes : MODU et PHAS pour l'option MOPH, PREE et
        PIMA pour l'option REIM.
        (type CHPOINT)

    MAIL1 : maillage sur lequel s'appui CHP1 ( carre unitaire ) :
     l'abscisse correspond au temps, et l'ordonnee a la frequence.

  CHP1 MAIL1 = ONDE N1 EVOL2 MOT1 'FMIN' FLOT1 'FMAX' FLOT2
        ('DFRQ' ENTI1) ('PULS' FLOT4) ;

| 2eme possibilite : extraction de l'arete de la transformee |

    Objet :

    L'operateur extrait l'arete de la transformee en ondelettes
 continue ( frequences et modules instantanes )

    Commentaire :

    MOT1 : mot indiquant le critere utilise pour l'extraction :

        'CRMO' : critere sur le module
        'CRPH' : critere sur la phase

   'EPSI' : mot-cle suivi de :
    FLOT5 : utilise seulement avec 'CRPH' : critere de nullite
        (type FLOTTANT, valeur par defaut = 1.E-4 )

   COUL1 : couleur choisie des courbes (type MOT)
        (blanc par defaut)

   EVOL1 : objet contenant 2 evolutions : la frequence et le
 module ( dans cet ordre ) de l'arete au cours du temps.
        (type EVOLUTION)

  EVOL1 = ONDE N1 EVOL2 MOT1 'FMIN' FLOT1 'FMAX' FLOT2
        ('DFRQ' ENTI1) ('EPSI' FLOT5) ('PULS' FLOT4) (COUL1) ;

## OPTO [Maillage Manipulation]
Operateur OPTO
-------------- TRIA REMA

MAIL1 CHPO1 ENTI1 ENTI2 ENTI3 ENTI4 = 'OPTO'
      MAIL2 MAIL3 CHPO2 ('VTOL' FLOT1) ('QTOL' FLOT2) ('ALGO' ENTI5)
        ('AJNO' ENTI6) ('VIRT' POIN1) ('NCMA' ENTI7) ('STMA' ENTI8)
        ('VERI' ENTI9) ('SGAJ' ENT10) ('IMPR' ENT11) ;

Objet :

Cet operateur n'est pas destine a etre appele par l'utilisateur.
Il OPtimise une TOpologie de maillage par amelioration locale.
Il est appele par la procedure MAILTOPO.

Commentaire :

  MAIL1 : Topologie optimisee (type MAILLAGE)
  CHPO1 : Metrique inverse sur la topologie optimisee (type CHPOINT)
  ENTI1 : Nombre de topologies examinees (type ENTIER)
  ENTI2 : Nombre de topologies changees (type ENTIER)
  ENTI3 : Nombre de topologies parcourues (type ENTIER)
  ENTI4 : Nombre de limitation du nombre de candidats (type ENTIER)

  MAIL2 : Topologie a optimiser (type MAILLAGE)
  MAIL3 : Entitees de la topologie autour desquelles optimiser
        (type MAILLAGE)
  CHPO2 : Inverse de la Metrique voulue definie sur MAIL2 (type
        CHPOINT)
  FLOT1 : Tolerance sur les volumes (1.d-11 par defaut)
  FLOT2 : Tolerance sur les qualites (1.d-2 par defaut)
  ENTI5 : Creation d'un maillage si egal a 0 (par defaut)
        Amelioration d'un maillage si egal a 1
  ENTI6 : L'algorithme n'ajoute pas de nouveaux noeuds si egal a 0
        (par defaut)
        L'algorithme ajoute des nouveaux noeuds si egal a 1
  POIN1 : Noeud virtuel
  ENTI7 : Nombre de Candidats MAximum (1000 par defaut)
  ENTI8 : STrategie quand on atteint le MAximum (0 par defaut)
  ENTI9 : Si egal a 1 : verification dans l'algorithme (lent, pour
        debugger, 0 par defaut)
  ENT10 : Si egal a 1 affichage des nombres de fois ou des segments
        sont ajustes (debug, 0 par defaut)
  ENT11 : Niveau d'impression (0 par defaut)

## ORBITE [Post-traitement Affichage] (proc)
Procedure ORBITE

ORBITE EVOL1 (TABOPT);

Objet :

Etant donne un ensemble de courbes contenues dans EVOL1 et
chacune definies par les listes {x_i} - {y_i} avec i={1..N},
la procedure ORBITE permet de DESSiner successivement une portion
de ces courbes en vue de realiser une animation de type orbite
ou trajectoire.

La "tete" de la trajectoire est materialise par un cercle plein.

Les options par defaut peuvent etre modifiee via la table
facultative TABOPT dont les indices pouvant etre donnes sont :

TABOPT . 'PAS' = nombre de pas entre 2 traces
ou
TABOPT . 'N_DESSIN' = nombre approximatif de traces souhaites

TABOPT . 'QUEUE' = nombre de pas pendant lesquels la remanence
        de la trajectoire est assure (ENTIER)
        ou mot 'INFINIE'

TABOPT . 'IDEB' = indice du pas definissant le debut de la
        courbe (0 par defaut)

TABOPT . 'TEMPS_CALCULES' = LISTENTI ou LISTREEL des temps
        a afficher dans le titre

TABOPT . 'EVOL_FIXE' = EVOLUTION immobile a ajouter aux traces

TABOPT . 'TITRE' = prefixe du titre (MOT)
        (mot ORBITE par defaut)
TABOPT . 'TITX' = titre des abscisses (MOT)
TABOPT . 'TITY' = titre des ordonnees (MOT)
TABOPT . 'XBOR' = bornes des abscisses (MOT) (ex: '-2. 1.5')
TABOPT . 'YBOR' = bornes des ordonnees (MOT)
TABOPT . 'CARR' = FAUX pour desactiver l'option CARR de DESS
        (VRAI par defaut)

Exemple : trace anime d'une courbe de Lissajous

xpi = 180.;
t = prog 0. pas (xpi / 360.) (4.*xpi);
y = 3. * (sin (2. * t));
x = -1. * (cos (1. * t));
ev = evol VERT manu 'x' x 'y' y;
dess ev;
toto = tabl; toto . 'CARR' = faux;
ORBITE ev toto;

|  |
|  _ _ _  _ _ _  |
|  _/  \__  o  \_  |
|  /  \_  .  \  |
| /  \_ .  \  |
| .  . \_  /  |
|  .  .  \__  _/  |
|  . . . .  \_ _ _/  |
|  |
|__________________________________|

## ORDO [Mathematiques Autres]
Operateur ORDONNER

Objet :

L'operateur ORDONNER range le contenu d'un objet ordonnable.

Syntaxes :

Tri d'un seul objet LISTENTI, LISTREEL ou LISTMOTS

LIS2 = ORDO LIS1 |('CROI')| ('ABSO') ('NOCA') ('UNIQ' (FLOT1)) ;
        |('DECR')|

Tri d'un ou plusieurs objets LISTENTI, LISTREEL et/ou LISTMOTS

a) Tri CROIssant ou DECRoissant

RES1 (.. RESN) = ORDO LIS1 (.. LISN) |('CROI')| ('ABSO') ('NOCA') ;
        |('DECR')|

TAB2 = ORDO TAB1 OBJ1 |('CROI')| ('ABSO') ('NOCA') ;
        |('DECR')|

b) Tri minimisant un COUT

RES0 RES1 (.. RESN) = ORDO LIS1 (.. LISN) 'COUT' LISCOU |('HONG')| ;
        | 'COMP' |

Tri d'un objet EVOLUTION

EVOL2 = ORDO EVOL1 |('CROI')| ('ABSO') ;
        |('DECR')|

Tri d'un objet MAILLAGE

MAIL2 = ORDO MAIL1 ;

Commentaires :

1) Les actions sont differentes selon le type de l'objet a traiter :

 - LISTENTI ou LISTREEL : on ordonne les nombres
 - LISTMOTS : on range les mots par ordre alphabetique
 - EVOLUTION : on ordonne les abscisses de chaque courbe
 - MAILLAGE :
      o POI1 : on ordonne les points par distance croissante au
        premier d'entre eux
      o SEG2, SEG3 : on ordonne les elements de maniere a decrire
        une ligne continue d'une extremite a l'autre
        (dans le cas d'une ligne fermee, celle-ci
        est ordonnee a partir du premier point du
        premier element, et le sens de parcours
        est celui du premier element)
      o autres : on ordonne par voisinnage des elements

2) Dans le cas d'un objet LIS1 (type LISTENTI, LISTREEL ou LISTMOTS)
   il est possible de fournir d'autres listes LIS2, LIS3, ...LISN
   (de types quelconques parmi LISTENTI, LISTREEL et LISTMOTS) qui
   subiront les memes permutations que LIS1. Toutes les listes
   doivent avoir la meme longueur.

3) Il est possible de regrouper les listes (type LISTENTI, LISTREEL
   ou LISTMOTS) dans un objet TAB1 de type TABLE. Le tri s'effectue
   alors sur celle d'indice OBJ1, et les autres listes subissent
   ensuite les memes permutations.

4) Description des mots-cles disponibles :

   >>> 'CROI' & 'DECR'
        s'applique a : LISTENTI, LISTREEL, LISTMOTS et EVOLUTION
        \__________________________/
        ou TABLE

        Il est possible de trier le contenu par ordre croissant
        (mot-cle 'CROI') ou decroissant (mot-cle 'DECR').

   >>> 'ABSO'
        s'applique a : LISTENTI, LISTREEL et EVOLUTION
        \________________/
        ou TABLE

        Le mot-cle 'ABSO' signifie que l'on ne tient compte que de
        la valeur absolue des nombres pour faire la mise en ordre.

   >>> 'NOCA'
        s'applique a : LISTMOTS (ou TABLE)

        Le mot-cle 'NOCA' indique que le tri est insensible a
        la casse des caracteres. En son absence, les majuscules
        precedent les minuscules dans l'ordre de tri.

   >>> 'UNIQ'
        s'applique a : LISTENTI, LISTREEL, LISTMOTS
        \__________________________/
        ou TABLE d'une seule liste

        (INVALIDE quand plusieurs listes sont triees simultenement)

        Le mot-cle 'UNIQ' permet de supprimer les eventuels doublons
        une fois le tri effectue. Si le mot 'NOCA' est present, deux
        mots seront consideres identiques meme si leur casse est
        differente, et seul l'un des deux sera conserve. Si un
        nombre FLOT1 (type FLOTTANT) est donne, deux reels seront
        consideres egaux si que leur difference (en valeur absolue)
        est inferieure a ce nombre.

   >>> 'COUT'
        s'applique a : LISTENTI, LISTREEL, LISTMOTS
        \__________________________/
        ou TABLE

        Le mot-cle 'COUT' doit obligatoirement etre suivi d'un objet
        LISCOU de valeurs C_i_j traduisant le cout de l'association
        (i;j). Cet objet de type LISTENTI ou LISTREEL est donc de
        dimension n**2 avec n la dimension des autres listes de
        valeurs LIS1 (.. LISN).

        ORDO calculera alors la permutation j=perm(i) minimisant
        le cout total, soit la somme pour i=1..n des C_i_perm(i)
        (retournee dans RES0). Les listes RES1 (.. RESN) sont les
        images des LIS1 (.. LISN) soumises a cette permutation-ci.

        L'option 'COMP' (pour COMPLET) calcule les (n!) permutations
        possibles, ce qui peut etre tres long. L'option 'HONG'
        utilise la methode "Hongroise", beaucoup plus rapide.

## ORDOVIBC [Mecanique Dynamique] (proc)
Operateur ORDOVIBC

ORDOVIBC TbasC2 (TbasC1);

Objet :

La procedure ORDOVIBC crée des listreels {wR} et {wI} des frequences
réelles et imaginaires d'une base modale complexe TbasC2 obtenue
avec VIBC et ordonne les modes complexes :
- selon {wR} croissant si TbasC1 n'est pas fourni,
- selon l'ordre des modes de TbasC1 de manière à minimiser
  le produit scalaire complexe <\psi1,\psi2> + <w1,w2>
  si TbasC1 est fourni.

Commentaire :

TbasC2 : base modales complexe a traiter
        (type TABLE, sous-type BASEMODA)
        avec les indices :
  . 'MODES' = table des modes |non ordonnée (Entree)
        |ordonnée  (Sortie)
  . 'LISTE_FREQUENCES_REELLES' = listreel des {wR} ordonnées (Sortie)
  . 'LISTE_FREQUENCES_IMAGINAIRES' = listreel des {wI} ordonnées (Sortie)

TbasC1 : base modales complexe de reference pour
        l'ordonnancement de TbasC2
        (type TABLE, sous-type BASEMODA)

## ORIE [Maillage Manipulation]
Operateur ORIENTER
------------------ ORDO

Objet :

L'operateur ORIENTER construit un maillage identique au maillage
initial, mais dont tous les elements orientables sont orientes.

| 1ere possibilite : orientation des elements massifs |

GEO1 = ORIENTER GEO2 ;

Objet :

Les elements sont orientes de la meme maniere que l'element de
reference correspondant (jacobien de la transformation geometrique
positif).

Commentaire :

GEO2 : maillage initial (type MAILLAGE)

GEO1 : maillage oriente (type MAILLAGE)

Remarque :

Les elements orientables pour chaque dimension d'espace sont les
suivants :
- 1D : SEG2, SEG3
- 2D : TRI3, TRI4, TRI6, TRI7, QUA4, QUA5, QUA8 et QUA9
- 3D : TET4, TE10, TE15, PRI6, PR15, PR21, PYR5, PY13, PY19, CUB8,
       CU20, CU27

| 2eme possibilite : orientation des elements surfaciques + coques |

 GEO1 = ORIENTER GEO2  | ('DIRECTION') VEC1  | ;
        |  'POINT'  POIN1 |

Objet :

En 3D, on oriente les elements en fonction de leur direction par
rapport a un vecteur ou a un point.

Commentaire :

GEO2 : maillage initial (type MAILLAGE)

VEC1 : vecteur definissant l'orientation (type POINT): le produit
        scalaire avec VEC1 de la normale sortante a chaque element
        est positif.

POIN1 : point definissant l'orientation (type POINT) : la normale
        sortante a chaque element pointe vers le demi-espace
        contenant POIN1.

GEO1 : maillage oriente (type MAILLAGE)

Les elements "orientables" sont de type TRI3/QUA4/TRI6/QUA8/
TRI7/QUA9.

Les elements de coques SHB8 (cub8) sont aussi orientables.

Remarque pour le SHB8 :

On suppose qu'il n'y a qu'une couche d'element dans l'epaisseur et
que les 4 premiers noeuds du cub8 representnte une peau de la coque.
On reoriente ces elements de telle facon que le vecteur indiquant la
direction traverse le cube de la peau interne vers la peau externe.
Le maillage resultat aura les deux peaux en references qui pourront
etre isolees par l'operateur FACE (surface interne est numero 1 et
externe numero 2).

## ORTH [Mathematiques Autres]
    Operateur ORTHOGONALISER

    CHPO1 = ORTH ('SEMBLABLE') CHPO2 LCHPO1 LREEL1 (LCHPO2) RIG1 ...
        ... ( FLOT1 (N1) ) ;

    Objet :

    L'operateur ORTHOGONALISER orthogonalise un objet CHPO2 par rapport
@ une suite d'objets Ui, orthogonaux entre eux et de meme type que CHPO2
Il est fondamental que les objets Ui soient orthogonaux entre eux.

    Commentaire :

    L'orthogonalite choisie est definie au moyen d'un objet RIG1 tel que
l'expression:
        CHPO2 * RIG1 * U(i)
ait un sens et puisse etre comparee a 0.

    'SEMBLABLE': mot-cle valable, si CHPO2 est de type CHPOINT. Il
        signifie que l'on est certain que tous les CHPOINTs
        s'appuient sur les memes points, avec les memes compo-
        santes. C'est une option qui accelere le calcul, mais
        qui demande a l'utilisateur une bonne maitrise des
        operandes fournis.

     LCHPO1 : suite des U(i) cites plus haut (type LISTCHPO)

     LREEL1 : la suite des produits U(i)*RIG1*U(i) (type LISTREEL)

     LCHPO2 : la suite des produits RIG1*U(i) (type LISTCHPO)
        Si elle est fournie, cette suite evite de refaire
        les produits RIG1*U(i).

     FLOT1 : precision d'orthogonalite demandee (type FLOTTANT).
        Elle est automatiquement modulee en fonction de la
        taille du probleme: Les erreurs de troncature sont
        plus importantes pour un gros probleme.

     N1 : nombre maximal d'orthogonalisations (type ENTIER),
        necessaires pour compenser les erreurs d'arrondi.
        (Cela n'a de sens que si l'on a donne une precision
        FLOT1).
        Interet de prendre N1 superieur a 1 n'est pas du
        tout etabli.

     CHPO2 : objet a orthogonaliser (type CHPOINT)

     CHPO1 : objet resultat (type CHPOINT)

## OSCI [Mathematiques Traitement]
    Operateur OSCI

    EVOL2 = OSCI EVOL1 'AMOR' FLOT1 'FREQ' FLOT2 ( 'TEMPS' LREEL1 )

        ( 'DEPL' FLOT3 ) ( 'VITE' FLOT4 ) 'COUL' COUL1 ;

    Objet :

    L'operateur OSCI permet de calculer la reponse X(t) d'un oscillateur
@ un signal donne, solution de l'equation :

        X''+ 2*FLOT1*W*X' + W*W*X =GAMMA(t)

    Commentaire :

    EVOL1 : Objet contenant le signal d'excitation
        (type EVOLUTION).

   'AMOR' : mot-cle suivi de :
    FLOT1 : amortissement de l'oscillateur (type FLOTTANT).

   'FREQ' : mot-cle suivi de :
    FLOT2 : frequence de l'oscillateur (type FLOTTANT).

   'TEMPS' : mot-cle suivi de :
    LREEL1 : liste de temps correspondant aux instants oº l'on
        souhaite effectuer les calculs (type LISTREEL).
        Par defaut, les temps sont ceux de l'objet EVOLUTION
        contenant le signal d'excitation.

   'DEPL' : mot-cle suivi de :
    FLOT3 : deplacement initial (type FLOTTANT).

   'VITE' : mot-cle suivi de :
    FLOT4 : vitesse initiale (type FLOTTANT).

   'COUL' : mot-cle suivi de :
    COUL1 : couleur de la courbe desiree (type MOT).

    EVOL2 : objet resultat (type EVOLUTION).

## OTER [Langage Objets]
Operateur OTER

    OTER TAB1 OBJET1 ;

Objet :

Le foncteur OTER permet de supprimer l'indice OBJET1
de la table TAB1

## OU [Mathematiques Logique]
    Operateur OU

    LOGR = OU LOG1 LOG2 (LOG3 ...);

    Objet :

    L'operateur OU travaille sur deux propositions logiques LOG1 et LOG2
(type LOGIQUE). Le resultat est la disjonction de ces propositions.

    Plus de deux logiques peuvent fournis. En ce cas le résultat est le
disjonction sur leur ensemble.

    Le resultat LOGR est de type LOGIQUE.

## OUBL [Langage Base]
Operateur OUBLIER
----------------- PLAC ENLE

OUBLIER OBJET1 ;
OUBLIER TAB1 OBJET1

Objet :

L'operateur OUBLIER efface de la memoire le nom d'objet OBJET1.
L'operateur OUBLIER efface de la memoire l'indice OBJET1 de la
   table TAB1 (OBJET1 ne doit pas etre un FLOTTANT). L'ordre
   des operandes doit etre respecte.

## OUVCOR [Mecanique Rupture]
    Procedure OUVCOR

    Objet :

MECANIQUE :

  Cette procedure permet d'effectuer un calcul de l'ouverture de fissure
  dans le cas complexe suivant le trajet de fissure. La fissure s'ouvre
  perpendiculairement au trajet de fissure. L'ouverture de fissure
  prend en compte les microfissures autour d'une fissure principale.

  Cette procedure est constituée de deux parties:

  Premiere partie:

  La premiere partie est composée de trois sous-procedures qui réalise
  les calculs dans l'ordre suivant :

  - initou: permet de positionner les points de fissure
  - zonfis: permet de detecter visuellement une zone de fissure
  - postou: permet de caculer l'ouverture de fissure

   Description des sous-procédures :

L'entree pour initou:
TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :

    TAB1.GEO MAILLAGE : structuré a post-traiter (CUB8)
    TAB1.POI POI1 : sur un bord du maillage
    TAB1.LH MAILLAGE : ligne de limite haute
    TAB1.LB MAILLAGE : ligne de limite basse
    TAB1.LG MAILLAGE : ligne de limite gauche
    TAB1.LD MAILLAGE : ligne de limite droite
    TAB1.PLA MOTS : 'XY', 'YZ', 'ZX' defini le plan de
        post-traitement

    TAB1.HOR LOGIQUE : vrai si le cacule du saut horizontal
    TAB1.PAS ENTIER : numero de pas

    TAB1.CRITO FLOTTANT : critere du seuil pour la norme de saut de
        deplacement
    TAB1.CRITP FLOTTANT : critere du seuil pour la position de fissure

Exemple d'utilisation : initou tab1;

L'entree pour zonfis:
Voici la liste :

    TAB1.DROI LOGIQUE : pour ajuster la zone de fissure
    OBJET1 ENTIER : numero de colonne de partie haute
    OBJET2 ENTIER : numero de colonne de partie basse
    OBJET3 ENTIER : numero de ligne de partie haute
    OBJET4 ENTIER : numero de ligne de partie basse
    OBJET5 FLOTTANT : limite haute de la grille
    OBJET6 ENTIER : limite basse de la grille
    OBJET7 ENTIER : ajustement de translation gauche
    OBJET8 ENTIER : ajustement de translation droite
    OBJET9 ENTIER : ajustement en bas gauche ou droite

Exemple d'utilisation :
    ZONFIS TAB1 OBJ1 OBJ2 OBJ3 OBJ4 OBJ5 OBJ6 OBJ7 OBJ8 OBJ9;

L'entree pour postou:

TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres)
dont voici la liste :
    TAB1 TABLE : continuation du calcul avec initou et zonfis
    OBJET1 FLOTTANT : demi-longueur de la ligne de post-traitement.

Exemple d'utilisation : postou tab1 obj1;

La sortie pour initou:

    TAB1.LIGV TABLE : ligne verticale de repere
    TAB1.LIGH TABLE : ligne horizontal de repere
    TAB1.TELZ TABLE : taille de grille verticale
    TAB1.TELX TABLE : taille de grille horizontale

    TAB1.SDH TABLE : saut de deplacement dans les trois directions
    TAB1.CDH TABLE : coordonnee du saut de deplacement

    TAB1.OUFT TABLE : norme de saut sur chaque ligne
    TAB1.COTX TABLE : coordonnee X sur chaque ligne
    TAB1.COTZ TABLE : coordonnee Z sur chaque ligne
    TAB1.OUFTT LISTREEL : norme de saut sur la structure
    TAB1.COTXX LISTREEL : coordonnee X sur la structure
    TAB1.COTZZ LISTREEL : coordonnee Z sur la structure

    TAB1.PFO TABLE : maxima locaux de la norme de saut
        sur chaque ligne
    TAB1.PFX TABLE : coordonnee X sur chaque ligne
    TAB1.PFZ TABLE : coordonnee Z sur chaque ligne
    TAB1.LPFO LISTREEL : maxima locaux de la norme de
        saut sur la structure
    TAB1.LPFX LISTREEL : coordonnee X sur la structure
    TAB1.LPFZ LISTREEL : coordonnee Z sur la structure

La sortie pour zonfis:

    TAB1.ZONE liste des points d'ajustement

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

  Deuxième partie:
[… notice tronquée ; texte complet dans l'archive PCW_24]

## OUVFISS [Mecanique Rupture] (proc)
    Procedure OUVFISS

    OUVFISS ETAB (I) (|TR);
        (|PRIN);

    Objet :

La procedure OUVFISS calcule l'ouverture de fissure à partir de l'etat
de contraintes et des caracteristiques elastiques pour chaque pas de
temps stockes dans la table ETAB.
On fait l'hypothese qu'une fissure unique peut traverser un element
fini et que la deformation est elastique autre part que dans la
fissure.
Le resultat est un tenseur d'ouverture de fissure (exprime
dans l'unite de longueur utilisee pour le calcul).
Par défaut, les calculs sont effectués sur l'ensemble des pas de temps
disponibles dans la table fournie. On peut préciser le numéro du pas à
traiter si on ne souhaite effectuer les calculs que sur un pas de
temps.
Si l'option 'TR' est indiquée, le résultat sera la trace du tenseur
d'ouverture de fissure.
Si l'option 'PRIN' est indiquée, le résultat ser le tenseur
d'ouverture de fissure écrit dans sa base principale.
La methode est construite pour un modele utilise pour decrire le
comportement non lineaire du materiau s'appuie sur une regularisation
energetique (Hillerborg ou crack band), mais les resultats obtenus avec d'autres
types de modeles (non local par exemple) devraient egalement être
corrects.

Plus de details peuvent être trouves dans la publication suivante que
vous êtes pries de referencer si vous utilisez cette procedure.

M. Matallah , C. La Borderie and O. Maurel, "A practical method to
estimate crack openings in concrete structures",
Int. J. Numer. Anal. Meth. Geomech. (2009) doi: 10.1002/nag.876

    Commentaires :

    ETAB : Table issue d'un calcul PASPAS.

    ETAB.OUV.I : Ouverture de fissure au pas "i" de type Champ par elements

     Exemple d'utilisation :

     PASAPAS ETAB;
     OUVFISS ETAB;
     I=DIME (ETAB . TEMPS);
     TRAC ETAB . OUV . (I-1) ETAB.MODELE;

$$$$

## PARA [Maillage Lignes]
    Operateur PARABOLE
    ------------------ CERC

    LIG1 = PARA (N1) ('DINI' DENS1) ('DFIN' DENS2) POIN1 POIN3 POIN2 ;

    Objet :

    L'operateur PARA construit un arc de parabole joignant deux points
tel que l'intersection des tangentes en ces points soit un point speci-
fie.

    Commentaire :

    N1 : nombre d'elements generes (type ENTIER)

    POIN1 | : extremites de l'arc de parabole (type POINT)
    POIN2 |

    POIN3 : point intersection des tangentes (type POINT)

    DENS1 | : densites associees aux extremites de l'arc de parabole
    DENS2 |  (type FLOTTANT)

    LIG1 : arc de parabole (type MAILLAGE)

    Remarque :

    Si N1 n'est pas specifie, le nombre d'elements engendres et leurs
tailles seront calcules en fonction des densites des extremites.

    Si N1 est specifie et positif, N1 elements d'egale longueur seront
engendres.

    Si N1 est negatif, N1 elements seront engendres et leurs tailles
seront calculees en tenant compte des densites des extremites.

    Si les densites associees aux points POIN1 et POIN2 ne sont pas
correctes, il est possible de les surcharger. Pour le premier point, il
faut donner la bonne valeur derriere le mot-cle 'DINI' et, pour le
deuxieme point, derriere le mot-cle 'DFIN'.

    Si une ligne LIG2 est donnee a la place du point POIN1 (ou POIN2)
cette ligne est prolongee jusqu'au point POIN2 (elle commence au
point POIN1).

    Si le point POIN2 n'est pas donne, la premiere extremite de la
ligne LIG1 est prise en compte, ce qui permet de fermer celle-ci.

## PARASTAT [Mathematiques Statistiques] (proc)
Procedure PARASTAT

FLOT1 FLOT2 FLOT3 FLOT4 = PARASTAT TAB1;

Objet :

Cette procedure calcule les parametres statistiques associes
a un ensemble de valeurs.

Commentaire :

TAB1 = (type TABLE)

TAB1.i.POINT = i-eme point d'integration (type FLOTTANT)

TAB1.i.POIDS = i-eme poids d'integration (type FLOTTANT)

FLOT1 = moyenne (type FLOTTANT)

FLOT2 = ecart-type (type FLOTTANT)

FLOT3 = coefficient de symetrie (type FLOTTANT)

FLOT4 = coefficient d'aplatissement (type FLOTTANT)

## PARC [Maillage Lignes]
    Operateur PARC

    GEO1 = PARC (N1) POIN1 CENTR1 POIN2 ('DINI' DENS1) ('DFIN' DENS2)

    Objet :

    L'operateur PARC permet de construire une ligne constituee d'une
succession d'arcs de paraboles, qui approchent un arc de cercle de
centre CENTR1, construit entre les points POIN1 et POIN2.
Les elements sont des segments a 3 noeuds, dont les extremites sont
sur l'arc de cercle et tangentes a l'arc de cercle.

    Commentaire :

    POIN1 | : points extremite de l'arc de cercle (type POINT)
    POIN2 |

    CENTR1 : centre du cercle (type POINT)

    N1 : nombre d'elements generes (type ENTIER)

    DENS1 | : densites associees aux points POIN1 et POIN2
    DENS2 |  (type FLOTTANT)

    GEO1 : ligne creee (type MAILLAGE)

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

     Si une ligne LIG1 est donnee a la place du point POIN1 (ou POIN2)
cette ligne est prolongee jusqu'au point POIN2 (la ligne commence au
point POIN1).
     Si le point POIN2 n'est pas donne, la premiere extremite de la
ligne LIG1 est consideree; ce qui permet de fermer celle-ci.

## PARMCHI2 [Multi-physique Multi-physique] (proc)
 Methode PARMCHI2
 ---------------- OBJE

  OBJ1 = OBJET PARMCHI2 ;

     Objet

  La methode PARMCHI2 permet de creer un objet de type objet et de
  CLASSE PARMCHI2. Un tel objet contient les donnees des parametres
  de CHI2. Cette methode permet de tester la coherence des donnees
  lors de l'ecriture.

     Commentaires

     Les methodes associees a PARMCHI2 sont

GEPS GITMAX GITERSOL GIAFFICH GPRECPE GNITERPE
GDELPE GMDELPE GNFI GSORTIE GIMPRIM

GEPS Charge le contenu de l'indice EPS.
       Un REEL, la precision du calcul.Valeur par defaut 1.E-4

GITMAX Charge le contenu de l'indice ITMAX.ENTIER nombre maximal
        d'iterations dans la resolution du systeme chimique.
        Valeur par defaut 20.

GITERSOL Charge le contenu de l'indice ITERSOLI ( ENTIER). Nombre
        maximal d'iterations, pour trouver les mineraux precipites.
        Valeur par defaut 10.

GIAFFICH Charge le contenu de l'indice IAFFICHE, un ENTIER permettant
     le choix d'affichage des resultats pour les solutions solides.
        1 coefficients stoechiometriques des solutions solides
        2 fractions molaires des solutions solides
        Valeur par defaut 2.

GPRECPE Charge le contenu de l'indice PRECPE( REEL).La precision
        sur le calcul redox. Valeur par defaut 1.E-10

GNITERPE Charge le contenu de l'indice NITERPE ( ENTIER).
        Le nombre maximal d'iterations de dichotomie.
        Valeur par defaut 50.

GDELPE Charge le contenu de l'indice DELPE ( REEL)
        L'intervalle initial des iterations de dichotomie.
        La valeur par defaut est 1.

GMDELPE Charge le contenu de l'indice MDELPE (ENTIER). Le nombre
        maximal de pas dans la recherche de l'intervalle
        de dichotomie. Valeur par defaut 20.
        ( evite de cycler lorsque l'on est tres loin de la solution)

GNFI Charge le contenu de l'indice NFI (ENTIER). Nombre de cycles
    de chimie.Valeur par defaut 4. Un cycle correspond a la
    sequence:
        * calcul de la force ionique
        * modification des logk
        |---
        * boucle mineraux a  |* resolution ( iterative )
        precipiter  |
        |* verification des mineraux
        |  precipites
        |---

GSORTIE Charge le contenu de l'indice SORTIE ( LISTMOTS).
        Ces mots doivent etre pris dans la liste:
        'PREC' 'FION' 'TYP6' 'TYP3' 'NTY4' 'TYP5' 'SURF' 'SOLU'
        'POLE' 'LOGK'
        Ils servent a preciser les elements que l'on veut voir
        figurer dans les resultats.

GIMPRIM Charge le contenu de l'indice IMPRIM (LISTENTI). Dans le cas
        ou l'on demande un niveau de message superieur a 0
        ( OPTION IMPI 1 ), ceci permet de limiter les impressions
        aux seuls noeuds du maillage dont le numero figure dans
        la liste.

## PART [Maillage Manipulation]
Operateur PARTITION

TABL1 = PART ('NESC') | 'OPTI' MAIL1 (ENTI1) ;
        |
        | 'ARLE' | MAIL1 | ENTI1 ;
        |  | MODL1 |
        |
        | 'CONN' MAIL1 ;
        |
        | 'SEPA' MAIL1 SEPA1 (SEPA2 ...) ;

        avec SEPAi = | 'FACE'
        | 'LIGN'
        | 'MAIL' MAIL2
        | 'ANGL' (FLOT2) ('TELQ')

Objet :

L'operateur PART construit une partition d'un objet, soit sa
decomposition en sous-ensembles non vides, disjoints deux a deux
et dont l'union correspond a l'objet initial.

Note : en l'absence du mot-cle 'NESC', la TABLE renvoyee en sortie
       sera de SOUSTYPE 'ESCLAVE'.

| Partition OPTIMISEE |

Tente d'equilibrer la taille des sous-parties d'un maillage et
de minimiser le nombre de points sur les frontieres.

Commentaire :

MAIL1 : Geometrie a partitionner (type MAILLAGE)

ENTI1 : Nombre de zones dans la partition (type ENTIER)

        Doit etre une puissance entiere positive de 2. Par defaut,
        on prend la plus petite puissance entiere positive de 2
        superieure au nombre d'assistants

TABL1 : Partition du maillage/modele (type TABLE)
        C'est une table dont les indices sont les entiers compris
        entre 1 et ENTI1 et dont les valeurs sont les maillages
        composant la partition

| Partition selon un motif ARLEQUIN |

Disperse des rangees d'elements adjacents dans les differentes
zones de la partition.

Commentaire :

MAIL1 : Geometrie a partitionner (type MAILLAGE)

MODL1 : Modele a partitionner (type MMODEL)

ENTI1 : Nombre de zones dans la partition (type ENTIER)

TABL1 : Partition du maillage/modele (type TABLE)
        C'est une table dont les indices sont les entiers compris
        entre 1 et ENTI1 et dont les valeurs sont les maillages
        ou modeles composant la partition

| Partition en composantes CONNEXES |

Decompose un maillage en ses composantes connexes.

Une composante connexe regroupe l'ensemble des elements joignables,
c'est-a-dire entre lesquels il est possible de trouver une chaine
d'elements ou deux maillons consecutifs partagent au moins 1 noeud.

Commentaire :

MAIL1 : Geometrie a partitionner (type MAILLAGE)

TABL1 : Partition du maillage (type TABLE)
        C'est une table dont les indices sont les entiers compris
        entre 1 et le nombre de composantes connexes et dont les
        valeurs sont les maillages formant les composantes connexes

| Partition suivant un SEPARATEUR |

Separe les composantes connexes d'un maillage (voir definition
ci-dessus) puis les subdivise suivant des regles donnees :

1) Mot-cle 'LIGN' (destine aux maillages de lignes) :

        Les noeuds appartenant a plus de 2 elements jouent le
        role de separateur (ces noeuds peuvent par ailleurs
        etre determines grace a l'operateur POIN 'JONC').

        => Plusieurs lignes se rejoignant en un meme noeud
        formeront autant de zones distinctes

2) Mot-cle 'FACE' (destine aux maillages surfaciques) :

        Les aretes appartenant a plus de 2 elements jouent le
        role de separateur (ces lignes peuvent par ailleurs
        etre determinees par l'operateur CONT 'INTE').

        => Deux surfaces ayant seulement 1 noeud en commun seront
        dans des zones distinctes

        => L'intersection de plusieurs surfaces (suivant une ou
        plusieurs lignes) aboutira a autant de zones distinctes

3) Mot-cle 'MAIL' :

       Le separateur est fourni sous la forme d'un maillage
       quelconque, typiquement surfacique pour partitionner des
       volumes, lineique pour partitionner des surfaces ou de POI1
       pour partitionner des lignes.

       C'est une generalisation des options 'LIGN' et 'FACE'.

       => Deux elements voisins du maillage a partitionner dont
        l'interface est incluse dans un element appartenant au
        maillage separateur seront affectes a des zones distinctes

4) Mot-cle 'ANGL' (destine aux maillages de lignes/surfaces) :

       Les aretes vives ou les angles vifs jouent le role de
       separateurs.

       => Deux elements voisins appartiennent a la meme zone
        si et seulement si l'angle entre leurs vecteurs normaux
        (surfaces) ou tangents (lignes) forment un angle plus
        petit qu'une valeur FLOT2 specifiee par l'utilisateur
        (angle non oriente compris entre 0 et 180 degres, par
        defaut 20 degres)
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PASAPAS [Mecanique Resolution] (proc)
    Procedure PASAPAS
    _________________ EXPLORER
    PASAPAS TAB1 ;

    TAB1. ACCELERATIONS MODELE
        AMORTISSEMENT MOVA
        AUGMENTATION_AUTOMATIQUE MTOL
        AUTOCRIT NB_BOTH
        AUTORESU NITERINTER_MAX
        AUTOMATIQUE NITER_KTANGENT
        AUTOPAS NMAXSUBSTEPS
        BCSTH NPAS_TRACKING
        BLOCAGES_DIFFUSIONS NRMAX
        BLOCAGES_MECANIQUES ORDRE
        BLOCAGES_THERMIQUES PARAMETRE_DE_PILOTAGE
        CAPACITE_CONSTANTE PAS_AJUSTE
        CARACTERISTIQUES PAS_MAX
        CELSIUS PILOTAGE_INDIRECT
        CHARGEMENT PRECDECHARGE
        CONCENTRATIONS PRECISINTER
        CONDUCTIVITE_CONSTANTE PRECISION
        PRECSOUSITERATION
        CONN PREDICTEUR
        CONSOLIDATION PROCEDURE_CHARMECA
        CONTRAINTES PROCEDURE_CHARTHER
        CONVERGENCE_FORCEE PROCEDURE_PARATHER
        CONVERGENCE_MEC_THE PROCEDURE_PERSO1
        CONVERGENCE_MONOTONE PROCEDURE_PERSO2
        CRITERE_COHERENCE PROCEDURE_REEV_MEC
        CTE_STEFAN_BOLTZMANN PROCEDURE_REEV_THE
        CTOL PROCEDURE_THERMIQUE
        DEFORMATIONS_INELASTIQUES PROCESSEURS
        DELTAITER PROJECTION
        DEPLACEMENTS PROPORTIONS_PHASE
        DEPLACEMENTS_PILOTES REACTIONS
        DYNAMIQUE REACTIONS_DIFFUSIONS
        ECONOMIQUE REACTIONS_THERMIQUES
        FEFP_FORMULATION REAC_GRANDS
        FORCES_PILOTEES REEQUILIBRAGE
        FREA1 RELAXATION_DUPONT
        FTOL RELAXATION_NONCONV
        GRANDS_DEPLACEMENTS RELAXATION_THETA
        HYPOTHESE_DEFORMATIONS REPRISE
        INITIALISATION RENORMALISATION
        K_SIGMA RIGIDITE_AUGMENTEE
        K_TANGENT RIGIDITE_CONSTANTE
        K_TANGENT_ITER0 SOUS_INCREMENT
        K_TANGENT_PERT SOUS_RELAXATION
        K_TANGENT_SYME STABILITE
        K_TANG_PERT_C1 SUBSTEPPING
        LAGRANGIEN TEMPERATURES
        LBC TEMPS
        LINESEARCH TEMPS_ADAPTATION_MODELE
        MAN TEMPS_CALCULES
        MASSE_CONSTANTE TEMPS_SAUVEGARDES
        MAXDEFOR TEMPS_SAUVES
        MAXSOUSPAS TRACKING
        MAXISOUSPAS TYP_TRAC
        MAXITERATION TTOL
        MAXSOUSITERATION
        MES_SAUVEGARDES UPDATE_LAGRANGIAN
        VARIABLES_INTERNES
        VITESSES
        ZONE_DE_PILOTAGE

    Objet :

MECANIQUE :

  Cette procedure permet d'effectuer un calcul non lineaire incremental
  La non linearite peut provenir, soit du materiau (plasticite), soit
  des grands deplacements soit des deux a la fois.
  Les resultats sont calcules a des valeurs du parametre d'evolution
  (pseudo temps ou temps reel) definies par l'utilisateur.
  Sous l'option MODE FREQ, la procedure resout l'équation dynamique
  sur la base modale étendue selon l'approche dite spectrale ou
  fréquentielle. Implicitement un instant est interprété comme une
  fréquence pour l'objet CHARGEMENT sans changement de terminologie.
  La procédure propose un balayage de fréquences par défaut lorsque la
  liste des TEMPS_CALCULES n'est pas précisée.

THERMIQUE :

  Cette procedure permet d'effectuer un calcul lineaire et
  non-lineaire en tenant compte de la conduction, de la convection
  et du rayonnement.

DIFFUSION :

  Cette procedure permet de resoudre un proble lineaire ou non-lineaire
  de diffusion.

  Il est possible d'effectuer un calcul couplant MECANIQUE, THERMIQUE
  et DIFFUSION. THERMIQUE et DIFFUSION sont resolues simulatnement.

   Commentaire :

En entree, TAB1 sert a definir les options et les parametres du calcul.
Les indices de l'objet TAB1 sont des mots (a ecrire en toutes lettres,
et en majuscules s'ils sont mis entre cotes) dont voici la liste :

 BLOCAGES_DIFFUSIONS : blocages de diffusion (type RIGIDITE ou
        CHARGEMENT de nom BLOD).

 BLOCAGES_MECANIQUES : blocages mecaniques (type RIGIDITE ou
        CHARGEMENT de nom BLOM).

 BLOCAGES_THERMIQUES : blocages thermiques (type RIGIDITE ou
        CHARGEMENT de nom BLOT).

 CARACTERISTIQUES : Champ de caracteristiques materielles et
        eventuellement geometriques si necessaire
        (type MCHAML, sous-type CARACTERISTIQUES,
        ou CHARGEMENT de nom MATE)
        Ses composantes peuvent etre de type :
        1) FLOTTANT si la composante est
        est constante sur toute la
        structure;
        2) MCHAML si la composante depend
        uniquement des points de la
        structure;
        3) EVOLUTION si la composante
        varie en fonction d'un seul
        parametre.
        4) NUAGE si la composante est
        decrite par une courbe de type
        EVOLUTION dependant d'un seul
        parametre.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PAS_DEFA [Mecanique Resolution] (proc)
procedure PAS_DEFA

Cette procedure est appelee au debut de PASAPAS, elle initialise
les valeurs par defaut et cree la table WTAB de pasapas.

Syntaxe :

PAS_DEFA TAB1 ;

Avec TAB1, table de donnees de PASAPAS.

En sortie, PAS_DEFA renvoie TAB1 avec un nouvel indice WTABLE.
Quelques sous-indices de WTABLE :

'CHAR_MODE' : LOGIQUE, vrai si chargement de nom MODE

'CHAR_MATE' : LOGIQUE, vrai si chargement de nom MATE

'CHAR_BLOD' : LOGIQUE, vrai si chargement de nom BLOD

'CHAR_BLOM' : LOGIQUE, vrai si chargement de nom BLOM

'CHAR_BLOT' : LOGIQUE, vrai si chargement de nom BLOT

## PAS_EPTH [Mecanique Resolution] (proc)
procedure PAS_EPTH

ETHER2 = PAS_EPTH PRECED MODEVAL MATEVAL | TEVAL*CHPOINT;

Cette procedure est appelee par PASAPAS et UNPAS. Elle permet de
calculer la deformation thermique:

1- ETREF, la deformation thermique de reference selon la relation:
   TREF = TEMPERATURE_REFERENCE
   ETREF = ALPHA(TREF)*(TREF-TALPA_REFERENCE)
   ETREF est stoque dans l'indice WTABLE.'ETREF'

2- ETHER2, la deformation thermique selon la relation:
   ETHER2 = ALPHA(T)*(T-TALPA_REFERENCE) - ETREF

ARGUMENTS
   ETHER2 (MCHAML) : Deformation thermique
   PRECED (TABLE ) : Table donnee en argument de PASAPAS
   MODELVAL(MMODEL) : MODELE mecanique sur lequel faire le calcul
   MATEVAL (MCHAML) : MCHAML materiau

   TEVAL (CHPOINT)
        ou : Temperature a laquelle on evalue ETHER2
        (MCHAML )

## PAS_ETAT [Mecanique Resolution] (proc)
procedure PAS_ETAT

Cette procedure est appelee par PASAPAS, elle cree un champ par
element representant l'etat de la structure a un instant donne.

## PAS_HELM [Mecanique Resolution] (proc)
Procedure PAS_HELM

Cette procedure est appelee au debut de UNPAS dans le cas
de l'utilisation d'un modele nonlocal de type HELM.

## PAS_INIT [Mecanique Resolution] (proc)
procedure PAS_INIT

Cette procedure est appelee par PASAPAS, elle initialise
les champs initiaux qui ne le sont pas, les mets dans la table
reperee par l'indice CONTINUATIOn de la table entree dans PASAPAS
et cree les tables de resultats.

## PAS_MATE [Mechanics Resolution] (proc)
procedure PAS_MATE

Cette procedure est appelee par PASAPAS, elle cree un champ par
element representant l'etat des materiaux a un instant donne.
Ce champ de materiaux est celui passe a l'operateur COMP.

## PAS_MODL [Mecanique Resolution] (proc)
Procedure PAS_MODL

PAS_MODL TAB1 ;

Objet :

Cette procedure est une procedure interne de PASAPAS.
Elle initialise et met a jour les sous-indices relatifs aux
modeles de l'indice WTABLE de la table PASAPAS, ainsi que
les sous-indices relatifs a leurs caracteristiques.

Commentaire :

TAB1 est la table PASAPAS.

Entrees :

En entree, PAS_MODL utilise les indices suivants :

TAB1.WTABLE.'MODELE' : objet MMODEL, par defaut,
        modele de PASAPAS (TAB1.MODELE)

TAB1.WTABLE.'CARACTERISTIQUES' : objet MCHAML, caracteristiques
        du modele (TAB1.'CARACTERISTIQUES'
        par defaut)

Sorties :

En sortie, PAS_MODL initialise ou met a jour les indices suivants :

TAB1.WTABLE.'MODELE_COURANT' : objet MMODEL, modele avec lequel
        PAS_MODL a instancie la table au
        precedent appel.

Indices utiles a TRANSNON :

TAB1.WTABLE.'THE1' : objet LOGIQUE, presence d'une formulation
        THERMIQUE

TAB1.WTABLE.'MOD_THE' : objet MMODEL, modeles THERMIQUE

TAB1.WTABLE.'MAT_THE' : objet MCHAML, champ de caracteristiques
        de 'MOD_THE'

TAB1.WTABLE.'THM1' : objet LOGIQUE, presence d'une formulation
        THERMOHYDRIQUE

TAB1.WTABLE.'MOD_THM' : objet MMODEL, modeles THERMOHYDRIQUE

TAB1.WTABLE.'MAT_THM' : objet MCHAML, champ de caracteristiques
        de 'MOD_THM'

TAB1.WTABLE.'FOR_THER' : objet LOGIQUE, presence d'une formulation
        THERMIQUE ou THERMOHYDRIQUE

TAB1.WTABLE.'MOD_T' : objet MMODEL, modeles THERMIQUE et
        THERMOHYDRIQUE

TAB1.WTABLE.'MAT_T' : objet MCHAML, champ de caracteristiques
        du modele 'MOD_T'

TAB1.WTABLE.'CONVECTION' : objet LOGIQUE, presence de CONVECTION

TAB1.WTABLE.'MOD_CON' : objet MMODEL, modeles THERMIQUE CONVECTION

TAB1.WTABLE.'MAT_CON' : objet MCHAML, champ de caracteristiques
        de 'MOD_CON'

TAB1.WTABLE.'RAYO' : objet LOGIQUE, presence de RAYONNEMENT

TAB1.WTABLE.'MOD_RAY' : objet MMODEL, modeles de RAYONNEMENT

TAB1.WTABLE.'MAT_RAY' : objet MCHAML, champ de caracteristiques
        de 'MAT_RAY'

TAB1.WTABLE.'ADVECTION' : objet LOGIQUE, presence d'advection

TAB1.WTABLE.'MOD_ADV' : objet MMODEL, modeles d'advection

TAB1.WTABLE.'MAT_ADV' : objet MCHAML, champ de caracteristiques
        de 'MOD_ADV'

TAB1.WTABLE.'CONDUCTION' : objet LOGIQUE, presence de CONDUCTION

TAB1.WTABLE.'MOD_COND' : objet MMODEL, modeles THERMIQUE CONDUCTION

TAB1.WTABLE.'MAT_COND' : objet MCHAML, champ de caracteristiques
        de 'MOD_COND'

TAB1.WTABLE.'SOURCE_Q' : objet LOGIQUE, presence de SOURCE THERMIQUE

TAB1.WTABLE.'MOD_SOQ' : objet MMODEL, modeles THERMIQUE SOURCE

TAB1.WTABLE.'MAT_SOQ' : objet MCHAML, champ de caracteristiques
        de 'MOD_SOQ'

TAB1.WTABLE.'FOR_DIFF' : objet LOGIQUE, presence d'une formulation
        DIFFUSION

TAB1.WTABLE.'MOD_DIF' : objet MMODEL, modeles de DIFFUSION

TAB1.WTABLE.'MAT_DIF' : objet MCHAML, champ de caracteristiques
        de 'MOD_DIF'

TAB1.WTABLE.'FOR_METALLU' : objet LOGIQUE, presence d'une formulation
        METALLURGIE

TAB1.WTABLE.'MOD_MET' : objet MMODEL, modeles METALLURGIE

TAB1.WTABLE.'MAT_MET' : objet MCHAML, champ de caracteristiques
        de 'MOD_MET'

TAB1.WTABLE.'PHASE' : objet LOGIQUE, presence d'une formulation
        CHANGEMENT_PHASE

TAB1.WTABLE.'MOD_PHA' : objet MMODEL, modeles CHANGEMENT_PHASE

TAB1.WTABLE.'MAT_PHA' : objet MCHAML, champ de caracteristiques
        de 'MOD_PHA'

TAB1.WTABLE.'MOD_TOT' : objet MMODEL, ensemble des modeles THERMIQUE,
        THERMOHYDRIQUE, DIFFUSION, METALLURGIE et
        CHANGEMENT_PHASE

TAB1.WTABLE.'MAT_TOT' : objet MCHAML, champ de caracteristiques
        de 'MOD_TOT'

Indices utiles a UNPAS :

TAB1.WTABLE.'MEC1' : objet LOGIQUE, presence d'une formulation
        MECANIQUE

TAB1.WTABLE.'MOD_MEC' : objet MMODEL, modeles MECANIQUE

TAB1.WTABLE.'MAT_MEC' : objet MCHAML, champ de caracteristiques
        de 'MOD_MEC'

TAB1.WTABLE.'CONTACT' : objet LOGIQUE, presence d'une formulation
        CONTACT

TAB1.WTABLE.'MODCONTA' : objet MMODEL, modeles de CONTACT

TAB1.WTABLE.'MATCONTA' : objet MCHAML, champ de caracteristiques
        de 'MODCONTA'

TAB1.WTABLE.'CAFROTTE' : objet LOGIQUE, presence de CONTACT FROTTEMENT

TAB1.WTABLE.'ADHERENCE' : objet LOGIQUE, presence de CONTACT ADHERENT

TAB1.WTABLE.'POR1' : objet LOGIQUE, presence d'une formulation
        POREUX

TAB1.WTABLE.'MOD_POR' : objet MMODEL, modeles POREUX

TAB1.WTABLE.'MAT_POR' : objet MCHAML, champ de caracteristiques
        de 'MOD_POR'

TAB1.WTABLE.'MOD_CHA' : objet MMODEL, modeles CHARGEMENT
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PAS_RAYO [Thermique Limites] (proc)
   Procedure PAS_RAYO

        TAB1 = PAS_RAYO TAB2 FLOT1 IENT1 ;

   Objet :

  Cette procedure PAS_RAYO traite en standard uniquement le cas du
rayonnement thermique et est appelee a chaque iteration du schema de
calcul d'un pas de thermique de PASAPAS.

   Commentaire :

      TAB2 : c'est la table entree dans PASAPAS

      FLOT1 : Instant pour lequel on veut calculer les differents termes
        necessaires dus au rayonnement (flux et/ou relations/matrices)

      IENT1 : valeur entiere valant :
        1 si l'appel vient de DUPONT2
        2 si premier appel de TRANSNON
        3 si deuxieme appel de TRANSNON

      TAB1 : est une table dont les indices sont

        - 'ADDI_SECOND' pointe un Chpoint second membre

        - 'ADDI_MATRICE' pointe une matrice a mettre au
        premier membre

## PAS_REPR [Mecanique Resolution] (proc)
procedure PAS_REPR

Cette procedure est appelee par PAS_DEFA, elle est
appelee en cas de reprise de calcul a un autre temps que
le dernier.

## PAS_RESU [Mecanique Resolution] (proc)
procedure PAS_RESU

Cette procedure est appelee par PASAPAS, elle mets les
resultats de ce qui vient d'etre calcules dans la table, passee
a pasapas, sous l'indice ESTIMATION. En cas de convergence mecanique-
thermique les resultats sont SAUVEGARDES sous certaines conditions.

## PAS_VERM [Mecanique Resolution] (proc)
procedure PAS_VERM

Cette procedure est appelee au debut de PASAPAS, elle verifie
la presence des champs necessaires a l'instanciation des materiaux.

## PAVE [Maillage Volumes]
    Operateur PAVE

    VOL1 = PAVE SURF1 SURF2 SURF3 SURF4 SURF5 SURF6 ;

    Objet :

    L'operateur PAVE permet de mailler avec des cubes l'interieur d'un
volume parallelipepedique dont les six faces sont precisees.

    Commentaire :

    SURFi : faces delimitant le volume (type MAILLAGE)

    VOL1 : volume resultat (type MAILLAGE)

    Remarque :

    Les faces doivent etre rectangulaires, maillees avec des quadrila-
teres par l'operateur DALLER.

    Les faces opposees qui doivent se suivre dans la liste, doivent avoir
des descriptions homologues.

## PECHE [Post-traitement Analyse] (proc)
Procedure PECHE
--------------- PASAPAS

CH2 = PECHE TAB1 MOT1 ( FLOT1 ) ( MOT2 ) ;

Objet :

Cette procedure permet de recuperer des resultats d'un calcul
effectue en utilisant la procedure NONLIN ou PASAPAS ,
pour un temps donne.

Commentaire :

TAB1 : table utilisee dans NONLIN ou PASAPAS (type TABLE)

MOT1 : mot-cle (type MOT) correspondant a l'indice du resultat
        souhaite (par exemple : 'RESUDEPL', 'DEPLACEMENTS', ...)

FLOT1 : temps (type FLOTTANT) pour lequel on souhaite les resul-
        tats. Par defaut, on recupere les resultats pour le
        dernier temps calcule

MOT2 : mot-cle (type MOT) 'IPOL' pour interpoler les resultats
        a un un instant qui n'est pas dans la liste des temps
        calcules.

CH2 : champ resultat (type CHPOINT ou MCHAML)

## PENCECHI [—] (proc)
Procedure PENCECHI

CHPO1 MAT1 = PENCECHI TAB1 ;

Objet :

Cette procedure est utilisee par la procedure PREPAENC pour
discretiser un terme d'echange.

## PENT [Multi-physique Multi-physique]
 Operateur PENT

 Objet :

 Évaluation du gradient d'un champ dans le cadre d'une
 discretisation de type volumes finis (variables aux
 centres)

 | 1ere possibilite : creation d'un gradient aux CENTRES  |

RCHPO1 RCHPO2 RCHELEM1 = 'PENT' MOD1
        'CENTRE' MCLE1 MCLE2 LMOT1 CHPO1 ('CLIM' CHPO2) ;

ou

RCHPO1 RCHPO2 = 'PENT' MOD1
        'CENTRE' MCLE1 MCLE2 LMOT1 CHPO1 ('CLIM' CHPO2)
        'GRADGEO' RCHELEM1 ;

 Commentaire :

 MOD1 : Objet MODELE.

 MCLE1 : MOT; indique la façon de considerer la frontiere;
        4 choix possibles:
        * 'BORDNULL': reconstruction lineaire exacte;
        le gradient du CHPOINT est nul sur les elements
        de frontiere;
        * 'LINEXACT': reconstruction lineaire exacte; le
        gradient est calcule sur les elements de frontiere
        par interpolation lineaire exacte.
        * 'EULESCAL': reconstruction lineaire exacte; le
        gradient est calcule en utilisant des conditions
        aux limites de type mur pour un champ scalaire
        (etat miroir a l'element de bord). Ceci dans le
        cadre des equations d'Euler.
        * 'EULEVECT': reconstruction lineaire exacte; le
        gradient est calcule en utilisant des conditions
        aux limites de type mur pour un champ vectoriel
        (etat miroir a l'element de bord). Ceci dans le
        cadre des equations d'Euler.

 MCLE2 : MOT; indique le type de limiteur de gradient a
        calculer.
        * 'LIMITEUR', on calcule le limiteur de Barth-Jespersen;
        * 'NOLIMITE', les coefficients de limiteur sont egal a
        1.0

 LMOT1 : LISTMOTS, composantes de CHPO1 et CHPO2

 CHPO1 : CHPOINT 'CENTRE' (i composantes, 1 <= i <= 9) dont on
        souhaite calculer le gradient.

 CHPO2 : CHPOINT (meme composantes que CHPO1): champoint
        qui specifie les conditions limites de type Dirichlet
        sur certains points de type 'FACE'

 RCHELEM1 : Champ par element des coefficients geometriques pour le
        calcul du gradient

 RCHPO1 : CHPOINT 'CENTRE' (NDIM * i composantes); contient le
        gradient du CHPO1; le gradient associe a la i-eme
        composante a pour noms de composantes 'PiDX', 'PiDY'
        ('PiDZ').

 RCHPO2 : CHPOINT 'CENTRE' (i composantes); contient les
        coefficients multiplicateurs compris entre 0 et 1 par
        lesquels il faut multiplier le gradient si on souhaite
        que ce dernier soit limite. Le nom des composantes est
        'Pi', avec la meme convention que pour RCHPO1.

Remarques :

1) Le gradient calcule est exact a l'interieur du domaine si la
   fonction est lineaire. Cette propriete est vraie egalement sur
   le bord avec l'option 'LINEXACT'.

2) Les options 'EULESCAL' et 'EULEVECT' traite la frontiere du
   domaine comme un mur.

3) Si on utilise l'option 'EULEVECT', CHPO1 (et CHPO2) doit avoir
   deux composantes en 2D ('UX','UY') et trois composantes en 3D
   ('UX','UY','UZ')

 | 2eme possibilite : creation d'un gradient aux FACEs  |

RCHPO1 RCHELEM1 = 'PENT' MOD1 'FACE' 'DIAMAN2' LMOT1 LMOT2
        CHPO1 CHPO2 CHPO3 ;

ou

RCHPO1 = 'PENT' MOD1 'FACE' 'DIAMAN2' LMOT1 LMOT2
        CHPO1 CHPO2 CHPO3 'GRADGEO' RCHELEM1 ;

Commentaire :

MOD1 : Objet MODELE.

LMOT1 : LISTMOTS, composantes de CHPO1 et CHPO2

LMOT2 : LISTMOTS, composantes de CHPO3 et RCHPO1

CHPO1 : CHPOINT 'CENTRE' dont on
        souhaite calculer le gradient.

CHPO2 : CHPOINT qui specifie les conditions limites de type
        Dirichlet sur certains points de type 'FACE'

CHPO3 : CHPOINT qui specifie les conditions limites de type
        von Neumann sur certains points de type 'FACE'

RCHELEM1 : Champ par element des coefficients geometriques pour le
        calcul du gradient.

RCHPO1 : CHPOINT 'FACE' (NDIM * i composantes); contient le
        gradient du CHPO1

Remarques :

1) La condition limite de type von Neumann prise en compte est donne
   par le produit scalaire de CHPO3 et des normales aux faces

 | 3eme possibilite : creation d'un gradient aux FACEs
 | en 2 dimensions avec tenseur symetrique

RCHPO1 RCHELEM1 = 'PENT' 'FACE' MCLE1 MOD1 CHPO1
        ('DISPDIF CHPO3) ('CLIM' CHPO2)
        ('NEUM' CHPO4) ('MIXT' CHPO5) ;

ou

RCHPO1 = 'PENT' 'FACE' MCLE1 MOD1 CHPO1 ('DISPDIF CHPO3)
        ('CLIM' CHPO2) ('NEUM' CHPO4) ('MIXT' CHPO5)
        'GRADGEO' RCHELEM1 ;

Commentaire :

MOD1 : Objet MODELE.

MCLE1 : Methode pour le calcul du gradient. Options possibles :
        'MPFA'

CHPO1 : CHPOINT 'CENTRE' dont on souhaite calculer le gradient.
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PERM [Mecanique Modele]
    Operateur PERMEABILITE

      RIG1 = PERM MODL1 MAT1 ;

    Objet :

    L'operateur PERM calcule les matrices de permeabilite des elements
de milieux poreux .

      Commentaire :

      MODL1 : objet modele (type MMODEL)

      MAT1 : champ de proprietes materielles (type MCHAML, sous-type
        CARACTERISTIQUES)

      RIG1 : matrices de permeabilite
        (type RIGIDITE, sous-type PERMEABILITE)

    Remarques :

    Le support geometrique de RIG1 sera celui de MAT1 .

    Le numero de l'harmonique utilise dans le cas d'une analyse en
serie de Fourier est precise par la directive:

        OPTION MODE FOUR NN ;

## PERT [Mathematiques Traitement]
Operateur PERT

LREEL1 = PERT LREEL2 ( 'SIGN' )
        ( 'AMPL' FLOT1 )
        ( 'INIT' ENTI1 ) ;

objet :

Operateur PERT perturbe LREEL2 pour produire LREEL1.

option :

- A l'aide du mot clef 'SIGN'(e), qui est le defaut, on change
  aleatoirement le signe des elements de LREEL2.

- A l'aide du mot clef 'AMPL'(itude), on perturbe aleatoirement
  l'amplitude (module) des elements de LREEL2. Chaque valeur est
  partiellement reporte sur ses voisines selon les fonctions
  cosinus et sinus pour preserver la puissance du signal original.
  L'amplitude moyenne (en degre) est donnee par FLOT1.

- La "perturbation" necessite un tirage de phase aleatoire. L'option
  'INIT' permet l'initialisation de generateur par l'utilisateur en
  introduisant ENTI1 (objet de type entier).

remarque :

les deux options 'SIGN' et 'AMPL' peuvent etre utilisee simultanement.

## PFLUAGE [Mecanique Resolution] (proc)
Procedure PFLUAGE
----------------- PHASAGE

  CHAM2 = PFLUAGE ........;

Objet :

  Cette procedure permet de calculer le tenseur de deformations
  differees du au fluage du beton. Elle est appellee
  automatiquement par la procedure PHASAGE.

## PHAJ [Changement_De_Phase Changement_De_Phase]
    Operateur PHAJ
    -------------- EXCP EXCS

      CHP2 = PHAJ MOD1 MAT1 CHP1 ;

    Objet :

    L'operateur 'PHAJ' calcule la valeur des "jeux" associes aux
conditions unilaterales de changement de phase en thermique.
Cet operateur est automatiquement appele dans la procedure TRANSNON.

      Commentaire :

      MOD1 : objet de type MMODEL contenant une formulation de type
        'CHANGEMENT_PHASE'.

      MAT1 : objet MCHAML des caracteristiques. La composante 'PRIM'
        est attendue constante par SOUS-ZONE.

      CHP1 : objet CHPOINT contenant les inconnues initiales.

      CHP2 : objet CHPOINT contenant les "jeux" des inconnues ('FLX')
        avant d'effectuer le changement de phase.

## PHASAGE [Mecanique Resolution] (proc)
 Procedure PHASAGE
 ----------------- EPAIFUT
  TAB2 = PHASAGE TAB1;

 Objet :

   Calculer les etats de contraintes a l'issu des sequences de
   constructions et de mise en tension des cables de precontrainte.
   (NB : Cette procedure a ete developpee pour une application
   particuliere et il peut manquer des options d'interet tout a
   fait general, merci de nous les signaler)

  Les indices de la table TAB1 sont tous des mots, ce sont :

  'FLUAGE' : mot parmi les quatre mots 'BPEL99', 'BPEL91'
        'LG','EC2' indiquant le reglement a appliquer pour la
        prise en compte du fluage reglementaire.
        Si la donnee n'est pas fournie le fluage n'est pas
        pris en compte.

  'RETRAIT' : mot parmi les quatre mots 'BPEL99', 'BPEL91'
        'LG','EC2' indiquant le reglement a appliquer pour la
        prise en compte du retrait reglementaire.
        Si la donnee n'est pas fournie le retrait n'est pas
        pris en compte.

  'LEVEES' : pointe vers une table contenant les informations
        concernant les levees du beton . Les indices de cette
        table sont des entiers 1,.N qui reperent les N levees.
        Chaque indice pointe vers une table qui a pour indice
        les mots :

        'MODELE' : objet modele associe a la levee .
        'MATERIAU' : materiau associe au modele precedent.
        'INSTANT' : temps en jours separant la premiere levee de
        celle-ci.(TAB1.LEVEES.1 doit etre egal a 0).
        ('COEF1') : flottant correspondant au taux d'humidite
        de la loi de retrait (facultatif :a ne
        fournir que si le calcul du retrait est
        demande ).
        ('COEF2') : objet chamelem donnant le taux d'armature
        (en poids) passive pour cette levee (a ne
        fournir que si le calcul du retrait est
        demande).
        ('SECHAGE') : objet chamelem contenant les differents
        rayons de sechage du modele exprime en
        centimetres (voir EPAIFUT) (a ne fournir
        que si le calcul du retrait est demande ).

  'PRECONTRAINTE' : pointe vers une table contenant la description
        des sequences de mise en tension des groupes de cables.
        C'est la table creee par la procedure TENSION.

  'MOD_RESTE': modele associe a la structure hors beton et hors
        cables de precontraintes (ferraillages, peau
        metallique ...).

  'MAT_RESTE': materiau associe au modele precedent.

  'BLOCAGES': objet rigidite contenant l'ensemble des
        blocages.

  'RIGIDITE_ADDITIONNELLE' : objet rigidite contenant
        eventuellement une rigidite constante.

  'TEMPS_FINAL': flottant donnant le temps final du calcul. Ce temps
        doit etre plus grand que le temps definissant
        la derniere levee et celui de la derniere
        mise en precontrainte.

  'SOUS_LEVEES' : entier donnant le nombre de sous pas pour calculer
        le fluage entre deux levees ( 1 par defaut).

  'SOUS_PRECONTRAINTES' : entier donnant le nombre de sous pas pour
        calculer le fluage a la suite d'une mise en tension
        d'un groupe de cables.

En sortie la table TAB2 contient en plus des elements de TAB1 les
indices :

  'TEMPS' : table indicee par les numeros des phases et
        contenant les differents temps ( en jours).

  'DRETRAIT' : table indicee par les numeros des levees et des
        phases et contenant les deformations de retrait.

  'DFLUAGE' : table indicee par les numeros des levees et des
        phases et contenant les deformations de fluage.

  'TABLE_SUITE' : table d'entree de la procedure pasapas dont il
        faudra, au moins, modifier le chargement et la liste
        des temps a calculer pour continuer le calcul.

Remarque :

 + tous les temps (en jours) ont comme origine la premiere
   levee de beton.

 + Pendant les levees c'est le poids qui cree des contraintes, il
   faut donc specifier les RHO des materiaux. Un objet CHARGEMENT
   correspondant est cree, sous l'indice 'CHARGEMENT' de la table
   tab2.'TABLE_SUITE'.

 + Pour continuer le calcul il faut :

    - recuperer la table fournit par TAB2.'TABLE_SUITE'
      (XXX= tab2.'TABLE_SUITE' ;)

    - redefinir les temps a calculer au dela du dernier temps calcule
      par la procedure PHASAGE. (XXX.'TEMPS_CALCULES'= ...)

    - ajouter au chargement deja dans la table le nouveau chargement.
      (XXX.'CHARGEMENT' = XXX.'CHARGEMENT' ET NOUV_CHA; )

    - appeler PASAPAS ( PASAPAS XXX; )

## PICA [Mecanique Resolution]
   Operateur PICA

   CH2 =  PICA |  -  | MODL1 CH1 DEP1 (DEP2);
        | 'JAUM' |
        | 'UTIL' |

   Objet :

1. Par defaut (pas de mot-cle), l'operateur PICA transforme :
   - un champ de contraintes de Piola-Kirchhoff de seconde espece
     en un champ de contraintes de Cauchy
   - ou un champ de deformations de Green-Lagrange
     en un champ de deformations d'Almansi-Euler.

2. En presence du mot-cle 'JAUM' (Jaummann), l'operateur PICA effectue
   un changement de repere sur le champ pour passer du repere
   corotationnel au repere general.

3. En presence du mot-cle 'UTIL' (utilisateur), on suppose que les
   contraintes issues du comportement sont des contraintes de Cauchy
   et par consequent PICA ne fait rien.

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

## PILE [Mecanique Resolution]
   Operateur PILEPS

     FLOT1 = PILEPS MCHAM1 MCHAM2 CRIT ;

   Objet :

   L'operateur PILEPS sert au pilotage automatique s'appuyant sur
une limitation de la plus grande deformation.
   Le resultat est le plus grand flottant XX tel que pour chaque
composante des champs par element de deformations MCHAM1 et
MCHAM2 la relation suivante soit verifiee :

        eps1 + XX*eps2 < CRIT si eps2>0 ou
        eps1 + XX*eps2 > -CRIT si eps2<0

## PILOINDI [Mecanique Resolution] (proc)
    Procedure PILOINDI

    Syntaxe :

      FLOT2 = PILOINDI TAB1 CHP1 CHP2 CHP3 CHP4 FLOT1;

    Objet :
    Cette procedure est applicable aux cas de pilotage indirect de chargement
    mecanique, pour lesquels la correction sur les inconnues nodales peut etre
    decomposee de maniere additive:

        d^(t) = d^(t-1) + dd^(i) (1)
        dd^(i) = dd^(i-1) + dI^(i) + [deta^(i)*dII^(i)] (2)
        dI^(i) = [K^(i-1)]^-1 *res^(i-1) (3)
        dII^(i) = [K^(i-1)]^-1 *dch (4)
        P(dd^(i)) = tau^(t) (5)

    avec:

    d^(t-1) : deplacement au pas de temps (t-1);
    dd^(i) : increment de deplacements sur le pas a l'iteration (i);
    dch : direction du chargement impose (donnee d'entree de l'analyse);
    res^(i-1) : desequilibre entre forces internes et externes ;
    K^(i-1) : matrice de rigidite du systeme ;
    deta^(i) : parametre de pilotage sur le pas ;
    P(dd^(i)) : equation de pilotage indirect ;
    tau^(t) : seuil que l'equation de pilotage doit respecter sur le pas.

    L'objectif de la procedure PILOINDI est de calculer la valeur deta^(i) (de
    type FLOTTANT). Ensuite, cette valeur est transmise a UNPAS afin de
    calculer la correction dd^(i). Par defaut, l'equation de pilotage porte
    sur le maximum de la deformation totale equivalente (methode CMSI). Poutant,
    la procedure PILOINDI peut etre surchargee par l'utilisateur qui souhaite
    definir sa propre equation de pilotage.

    Commentaire :

    TAB1 : Table courante de pasapas (type TABLE).
    CHP1 : Deplacement accumule jusqu'au debut du pas de temps (type CHPOINT),
        ce qui correspond a d^(t-1) dans l'equation (1).
    CHP2 : Deplacement accumule dans le pas de temps courant (type CHPOINT),
        ce qui correspond a dd^(i-1) dans l'equation (2).
    CHP3 : Partie de la correction correspondant a dI^(i) (type CHPOINT)
        dans l'equation (3).
    CHP4 : Partie de la correction correspondant a dII^(i) (type CHPOINT)
        dans l'equation (4).
    FLOT1 : Valeur limite que le critere de pilotage doit respecter dans le
        pas de temps courant (type FLOTTANT), ce qui correspond a tau^(t)
        dans l'equation (5).
    FLOT2 : Valeur (type FLOTTANT) calcule par PILOINDI, qui correspond a
        deta^(i) dans l'equation (2).

    Remarque :

    Les aspects theoriques et les formulations sous-jacentes sont disponibles
    dans les references [1], [2] et [3].

    Exemples d'application en pilotage indirect de chargement:

    pilotage_indirect_1.dgibi
    pilotage_indirect_1_cndi.dgibi
    pilotage_indirect_1_cmep.dgibi
    pilotage_indirect_2.dgibi

    References :

    [1] H. Oliveira, G. Rastiello, A. Millard, I. Bitar, B. Richard.
    Implementation of path-following solvers in the finite element toolbox
    Cast3M: formulations, algorithms and applications. Volume 161, 2021,
        103055, ISSN 0965-9978,
        https://doi.org/10.1016/j.advengsoft.2021.103055.

    [2] G. Rastiello, F. Riccard,, B. Richard. Discontinuity-scale
    path-following methods for the embedded discontinuity modeling of
    failure in solids. Computer Methods in Applied Mechanics and Engineering.
    Volume 349, 2019, Pages 431-457, ISSN 0045-7825,
    https://doi.org/10.1016/j.cma.2019.02.030.

        [3] G. Rastiello, H.L. Oliveira, A. Millard. Path-following
        methods for unstable structural responses induced by strain softening:
        a critical review. Comptes Rendus. Mécanique, Tome 350 (2022),
        pp. 205-236.
        doi : 10.5802/crmeca.112.

$$$$

## PJBA [Mecanique Dynamique]
    Operateur PJBA
    -------------- EVOL 'PJBA'

    |  1ere possibilite  |

    OBJET2  =  PJBA OBJET1 | TAB1 (TAB2)  |  ('LIBR') ;
        | BAS1 (STRU1 (N1)) |
        | MOD1 CAR1  |

    Objet :

    L'operateur PJBA projette des forces sur une base modale
    elementaire ou complexe.
    Autrement dit, il calcule :
        F^* = [ X Y ]^T * F
      ou X designe la base de modes propres (TAB1)
      et Y l'ensemble des solutions statiques (TAB2 optionnelle)

    Commentaire :

    OBJET2 : objet de meme type que OBJET1 (sauf cas particuliers),
        de composantes modales :
        FALF relatives aux modes propres X,
        FBET relatives aux solutions statiques Y.

    OBJET1 : champ de force (type CHPOINT ou CHARGEMENT). Les points et
        les composantes d'OBJET1 doivent etre inclus dans la base

    TAB1 : base modale X (type TABLE de sous-type BASE_MODALE
        obtenue avec VIBR par exemple)
    TAB2 : base de solutions statiques (ou modes contraints) Y
        (type TABLE, sous-type LIAISONS_STATIQUES obtenue par IDLI,
        BLOQ, RESO, DEPI, etc.)

    BAS1 : la base modale X (type BASEMODA)
    STRU1 : structure sur laquelle s'applique OBJET1, en cas de base
        modale complexe (type STRUCTUR)
    N1 : numero de la sous-structure si celle-ci est formee
        de sous-structures identiques

    MOD1 : objet MMODEL decrivant la base modale
    CAR1 : objet MCHAML decrivant les proprietes de la base

   'LIBR' : mot-cle a utiliser pour projeter des forces definies
        dans des axes fixes, dans une base "tournante"
        (par exemple pour un calcul en grands deplacements sur
        base tournante). Dans ce cas, OBJET2 est de type LISTCHPO.

    Remarque :

    Tous les CHPOINTs crees sont de nature discrete.
    L'option LIBR ne fonctionne qu'avec l'objet BASEMODA.

    Pour definir des forces sur les sous-structures S1, S2, ... ,
    il faut specifier pour chaque sous-structure Si sur quelle base
    elementaire s'applique le champ de forces exterieures Fi (type
    CHPOINT), pour calculer la force generalisee FNi correspondante.

    Par exemple pour chaque sous-structure Si associee a la base
    modale Bi :

        Fi = FORCE ...... ;
        FNi = PJBA Bi Fi ;

    puis :
        FN = FN1 ET FN2 ET ... ;

    |  2eme possibilite  |

    LCHPO2 = PJBA | LCHPO1  | (LIPDT1) TBAS1 (NMOD1) (RIGI1) ;
        | TAB1 (MOT1) |

    Objet :

    L'operateur PJBA projette un signal instationnaire (par exemple
    un resultat PASAPAS, DYNAMIC ou EXEC) sur les vecteurs d'une
    base modale donnee.

    Commentaire :

     Le signal instationnaire est contenu soit :

       1) dans un objet TAB1 de type TABLE (et de sous-type PASAPAS,
        DYNAMIC ou EXEC), auquel cas on peut fournir dans MOT1
        l'indice de la grandeur a tracer :
        - pour PASAPAS : DEPLACEMENTS (par defaut), TEMPERATURES...
        - pour DYNAMIC : DEPL (par defaut), VITE...
        - pour EXEC : UN (par defaut), PN, TN...

       2) dans un objet LCHPO1 de type LISTCHPO

     On peut restreindre la liste des pas de temps retenus en donnant
     l'objet LIPDT1 de type LISTENTI.

     La base de modes est donnee dans TBAS1 (objet TABLE de sous-type
     BASE_MODALE).

     Il est possible de specifier combien de modes doivent etre pris en
     compte en fournissant l'objet NMOD1 (type ENTIER). Si absent, la
     projection est effectuee sur tous les modes de TBAS1.

     RIGI1 (type RIGIDITE) est une matrice symetrique definie positive
     utilisee pour realiser le produit scalaire (si RIGI1 est absente,
     on fait classiquement la somme des produits des composantes).

     En sortie, LCHPO2 (type LISTCHPO) contient autant d'objets CHPOINT
     que LCHPO1 (un par pas de temps), et chaque CHPOINT contient un
     noeud par mode (correspondant a l'indice 'POINT_REPERE' de TBAS1).

    |  3eme possibilite  |

    RIG2 (RIG3) = PJBA RIG1 TAB1 |  (TAB2)  ;
        | ('REEL') ;

    Objet :

    L'operateur PJBA calcule la projection de la matrice de raideur
    RIG1 sur une base de modes reels ou complexes TAB1 (et de modes
    contraints TAB2 si ils sont presents).

    Autrement dit, il calcule :
        K^* = [ X Y ]^H * K * [ X Y ]
      ou X designe la base de modes propres (TAB1)
      et Y l'ensemble des solutions statiques (TAB2 optionnelle)

    ou, avec l'option 'REEL' :
        K^* = [X]^T * K * [X]

    Commentaire :
[… notice tronquée ; texte complet dans l'archive PCW_24]

## PLAC [Langage Base]
Operateur PLAC
-------------- OUBL

ENTI1 = PLACE ;

Objet :

L'operateur PLACE renseigne sur la taille (type ENTIER) de la memoire
disponible (en memoire principale et de debordement).

Remarque :

Le taux d'efficacite de la place disque y est estimee a 50%.

## PLAS [Mecanique Modele]
    Operateur PLAS

    SIG1 VAR1 DEPS1 = PLAS MODL1 SIG2 VAR2 EPS3 CAR1 (FLOT1) ;

    Objet :

    Etant donne un etat initial plastiquement et statiquement admissible
caracterise par un champ de contraintes, un champ de contraintes interne
materiau et eventuellement d'autres caracteristiques d'une part, un incre-
ment de deformations d'autre part, l'operateur PLAS realise l'ecoulement
selon la surface de charge.
    L'ecoulement selon la surface de charge est caracterise par un
nouveau champ de contraintes, de nouvelles variables internes
(plastiquement admissibles) et par un increment de deformations
inelastiques.

    Commentaire :

    MODL1 : objet modele (type MMODEL)

    SIG2 : champ de contraintes
        (type MCHAML, sous-type CONTRAINTES)

    VAR2 : champ de variables internes
        (type MCHAML, sous-type VARIABLES INTERNES)

    EPS3 : increment de deformations
        (type MCHAML, sous-type DEFORMATIONS)

    CAR1 : description du materiau et de caracteristiques geometriques
        (type MCHAML, sous-type CARACTERISTIQUES)

    FLOT1 : precision numerique utilisee pour le calcul
        (type FLOTTANT)
        par defaut FLOT1 est egal a 1.E-3

    SIG1 : nouveau champ de contraintes
        (type MCHAML, sous-type CONTRAINTES)

    VAR1 : nouvelles variables internes
        (type MCHAML, sous-type VARIABLES INTERNES)

    DEPS1 : increment de deformations inelastiques
        (type MCHAML, sous-type DEFORMATIONS)

    Remarque:

    Il convient de respecter l'ordre des donnees en entree et en
sortie.

## PLUS [Maillage Autres]
Operateur PLUS
--------------- TOUR DEDU

Objet :

L'operateur PLUS cree un nouvel objet et realise la translation
du support geometrique d'un objet par un vecteur, ou
la transformation definie par un champ de deplacements de
type CHPOINT, selon le type du dernier operande.
Lorsqu'il s'agit d'un CHPOINT, l'image
des points appartenant au support de celui-ci est etablie a partir
de la valeur des composantes 'UX' 'UY' ('UZ') ou 'UR' 'UZ' en ces points.
Lorsque l'operation est realisee simultanement pour
plusieurs operandes, les geometries elementaires ne sont transformees
qu'une seule fois.

        OBJ2 = OBJ1 PLUS | VEC1  ;
        | CHPO1

    NOBJ1  ... NOBJN  = OBJ1 ...  OBJN  PLUS |  VEC1  ;
        |  CHPO1

Commentaire :

     OBJ1 : types POINT, MAILLAGE, CHPOINT, MCHAML, MMODEL,
        le type RIGIDITE est admis pour la translation par VEC1
        mais pas pour la transformation par CHPO1.
        OBJ1 peut aussi etre une table. Dans ce cas tous les
        objets contenus dans la table, qui doivent etre d'un des
        types ci-dessus, subiront la translation ou la
        transformation. Si une table est donnee, il ne doit pas y
        avoir d'autres objets.

  OBJ1 ... OBJN : voir OBJ1

     VEC1 : type POINT

    CHPO1 : type CHPOINT

     OBJ2 : resultat de meme type que OBJ1

NOBJ1 ... NOBN : resultats respectivement de memes types
        que OBJ1 ... OBJN

## PMAT [Changement_De_Phase Changement_De_Phase]
Operateur PMAT
-------------- EXCP EXCS

  RIG1 = 'PMAT' MOD1 ;

Objet :

L'operateur 'PMAT' calcule les matrices de blocages associees a la
formulation 'CHANGEMENT_PHASE'.
Cet operateur est automatiquement appele dans la procedure TRANSNON.

  Commentaire :

  MOD1 : objet de type MMODEL contenant une formulation de type
        'CHANGEMENT_PHASE'.

  RIG1 : objet de type RIGIDITE

## PMIX [Mathematiques Autres]
    Operateur PMIXTE
    ---------------- PSCA

    FLOT1 = PMIXT VEC1 VEC2 ( VEC3 si 3D ) ;

    Objet :

    L'operateur PMIXTE effectue le produit mixte de 2 (en 2D) ou 3
(en 3D) vecteurs.

    Commentaire :

    VECi : vecteurs (type POINT)

    FLOT1 : resultat du produit mixte (type FLOTTANT)

## PMPB [Post-traitement Analyse] (proc)
 Procedure PMPB

  Objet :

   Decomposition de chaque composante d'un champ de contraintes
   definies sur un segment d'appui en

        MEMBRANE PM
        FLEXION LINEARISEE PB

        suivant la specification du RCCM

  Syntaxe :

     TABV = PMPB CHPO1 MAIL1 GRAPH ENTI1 ENTI2 ;

 ENTREES :

     CHPO1 champ par point de contraintes sur le segment MAIL1
        obtenu par projection du champ par element sur MAIL1
        ( operateur PROI )

     MAIL1 segmant d appui obligatoirement en elements SEG2

     GRAPH LOGIQUE valant VRAI si l'on desire le trace des
        decompositions

     ENTI1 entier identifiant le segment d'appui

     ENTI2 entier identifiant le champ de contraintes analyse

  SORTIES :

     TABV table contenant les objets suivants

TABV.1 listreel des flexions linearisees en peau interieure
TABV.2 listreel des membranes en peau interieure
TABV.3 listreel des contraintes totales en peau interieure

TABV.4 listreel des flexions linearisees en peau interieure
TABV.5 listreel des membranes en peau interieure
TABV.6 listreel des contraintes totales en peau interieure
