# Notices complètes MODE, MATE et OPTI (texte compacté)

## OPTI
    Directive OPTION

    'OPTION' MOT1 VAL1 (MOT2 VAL2 ...) ;

    Objet :

    La directive OPTION sert à préciser des options générales de calcul.

    Options possibles :

|Mot-clé | Valeurs possibles (une)  | Défaut |  Commentaire  |
| MOTi  |  VALi  |  |  |
|--------|----------------------------|--------|-----------------------|
|'ACQU'  |  numéro unité logique  |  9  | fichier d'entrée  |
|  |  ou 'nom fichier'  |  |  |
|  |  |  |  |
|'ASSI'  |  nombre d'assistants  |  0  | parallélisme  |
|  |  |  |  |
|'ATTE'  | Duree d'attente pour un  |  0  | Surveillance GEMAT  |
|  | SEGMENT au dela de laquelle|  |  <0 : ooogll  |
|  | on affiche un message GEMAT|  |  >0 : ooowait  |
|  | (en Microsecondes)  |  |  |
|  |  |  |  |
|'CADR'  |  FLOTTANT positif  |  30.  | Coté du cadre (en cm) |
|  |  |  |  |
|'COSC'  |  NOIR,BLANC, JAUN  |  NOIR  | Couleur fond d'ecran  |
|  |  |  |  |
|'COUL'  | DEFA,BLEU,ROUG,ROSE,JAUN,  |  DEFA  | couleur prédéfinie  |
|  | VERT,TURQ,BLAN,NOIR,AZUR,  |  |  |
|  | ORAN,VIOL,OCEA,CYAN,OLIV,  |  |  |
|  | GRIS  |  |  |
|  |  |  |  |
|'DEBU'  |  0,1  |  0  | en cas d'erreur, on ne!
|  |  |  | peut pas lister les  |
|  |  |  | objets internes à la  |
|  |  |  | procedure  |
|  |  |  |  |
|'DENS'  |  FLOTTANT positif  |  0.  | taille de maille par  |
|  |  |  | defaut (voir aussi  |
|  |  |  | notice DENS)  |
|  |  |  |  |
|'DIME'  |  1,2,3  |  0  | dimension de l'espace |
|  |  |  |  |
|'DONN'  |  numéro unité logique  |  5  | cartes données  |
|  |  ou 'nom fichier'  |  |  |
|  |  |  |  |
|'ECHO'  |  -1,0,1,2  |  1  | écho données  |
|  |  |  |  |
|'ECRA'  |  |  |  |
|  |  |  |  |
|'ELEM'  | POI1,SEG2,SEG3,TRI3,TRI6,  |  | élément à fabriquer  |
|  | QUA4,QUA8,RAC2,RAC3,CUB8,  |  |  |
|  | CU20,PRI6,PR15,PYR5,PY13,  |  |  |
|  | TET4,TE10  |  |  |
|  |  |  |  |
|'EPTR'  |  1,2,...,10  |  1  | épaisseur du trait  |
|  |  |  | pour le tracé  |
|  |  |  |  |
|'ERRE'  | FATAL,NORMAL,  | NORMAL | Type de traitements  |
|  | CONTROLE,IGNORE  |  | des erreurs  |
|  |  |  |  |
|'ERMA'  |  |  | en sortie donne la  |
|  |  |  | valeur maxi de  |
|  |  |  | l'erreur atteinte.  |
|  |  |  |  |
|'FTRA'  |  chaîne de caractères  |  -  | Nom du fichier conte- |
|  |  |  | nant le tracé de type |
|  |  |  | PostScript ou MIF  |
|  |  |  | (FrameMaker)  |
|  |  |  |  |
|'IMPI'  |  0,1,2  |  0  | niveau de message  |
|  |  |  |  |
|'IMPR'  |  numéro unité logique  |  6  | imprimante  |
|  |  ou nom fichier  |  |  |
|  |  |  |  |
|'INCO'  |  LMOT1 LMOT2 ou MOT1 MOT2  |  | Noms d'inconnues  |
|  |  |  | primales (L)MOT1 et  |
|  |  |  | duales (L)MOT2 definis|
|  |  |  | par l'utilisateur  |
|  |  |  |  |
|'ISOV'  | LIGNE,SURFACE,SULI  | SURFACE| Type de tracé des  |
|  |  |  | isovaleurs  |
|  |  |  |  |
|'LANG'  | FRANCAIS,ANGLAIS,...  |FRANCAIS| Langue de la notice  |
|  |  |  |  |
|'LECT'  |  numéro unité logique  |  4  | fichier d'entrée  |
|  |  ou 'nom fichier'  |  |  |
|  |  |  |  |
|'LOCA'  | VRAI,FAUX  | FAUX  | creation d'une table  |
|  |  |  | &TOTO apres chaque  |
|  |  |  | appel de la procedure |
|  |  |  | TOTO contenant toutes |
|  |  |  | ses variables locales |
|  |  |  |  |
|'MODE'  | PLAN CONT ( cont planes )  |  PLAN  | - modèle de calcul  |
|  | PLAN DEFO ( défo planes )  |  DEFO  |  (en 2D et en 1D)  |
|  | PLAN GENE (défo planes  |  | - numero de l'harmo-  |
|  |  généralisées)  |  |  nique pour FOUR  |
|  | AXIS  (axisymétrique)  |  |  |
|  | FOUR  NN  (Fourier )  |  |  (voir remarques)  |
|  | TRID  (tridimensionnel)|  |  |
|  | UNID PLAN (DYDZ)  )  |  |  |
|  | UNID PLAN DYCZ  )  |  |  |
|  | UNID PLAN CYDZ  )  |  |  |
|  | UNID PLAN CYCZ  )  |  |  |
|  | UNID PLAN GYDZ  )  |  |  |
|  | UNID PLAN GYCZ  )  |  |  |
|  | UNID PLAN DYGZ  )  1D  |  |  |
|  | UNID PLAN CYGZ  )  |  |  |
|  | UNID PLAN GYGZ  )  |  |  |
|  | UNID AXIS (AXDZ)  )  |  |  |
|  | UNID AXIS AXCZ  )  |  |  |
|  | UNID AXIS AXGZ  )  |  |  |
|  | UNID SPHE  )  |  |  |
|  | FREQ  (frequentiel)  |  | (voir remarques)  |
|  |  |  |  |
|'NAVI'  | LICE,LIMS,LBMS,MCCE,MCP1,  |  | Définition du couple  |
|  | MCMS,QFCE,QFP1,QFMS  |  | vitesse/pression dans |
|  |  |  | le cadre NavierStokes |
|  |  |  |  |
|'NBP'  | ENTIER positif ou nul  |  | Impose le nombre de  |
|  |  |  | points  |
|  |  |  |  |
|'NGMA'  | ENTIER positif (VAR NGMAXY)| 100000 | Nb de mots ( matrice )|
|  |  |  |  |
|'NIVE'  |  24  |  24  | Niveau des sorties  |
|  |  |  |  |
|'NORM'  | LISMOT1 LISREE1  |  |Normalisation des  |
|  |  (LISMO2  LISREE2)  |  |variables en vue de la |
|  | 'AUTO'  |  |factorisation  |
|  | 'ANNU'  |  |  |
|  |  |  |  |
|'OEIL'  | POINT  |  |Oeil par défaut  |
|  |  |  |  |
|'OMBR'  | VRAI,FAUX  | VRAI  |Ombrage des tracés FACE|
|  |  |  |  |
|'PARA'  | VRAI,FAUX  | FAUX  | par défaut pas de  |
|  |  |  | Gibiane parallèle  |
|  |  |  |  |
|'PLAC'  | Entier positif  | Ptot  | Place mémoire libre  |
|  |  |  /10 | minimale à respecter  |
|  |  |  |  |
|'POLI'  |8_BY_13,9_BY_15,TIMES_10,  |8_BY_13 | choix de la police  |
|  |TIMES__24,HELV_10,HELV_12,  |  | pour dessins et traces|
|  |HELV_18  |  |  |
|  |  |  |  |
|'POTR'  | COURIER_N, COURIERB_N,  |COURIER_14| choix de la police  |
|  | HELVETICA_N ou TIMES_N  |  | pour dessins et traces|
|  | avec N=12,14,16 ou 18  |  | postscript (PS et PSC)|
|  |  |  |  |
|'RESO'  | 'DIRECTE' ou  'ITERATIVE'  | 'DIRE' | Méthode de résolution |
|  |  |  |  |
|'REST'  |  numéro unité logique  |  2  | fichier d'entrée  |
|  |  ou 'nom fichier'  |  |  |
|  |  mot-clé éventuel FORM  |  |  |
|  |  mot-clé éventuel BINAAT |  |  |
|  |  mot-clé éventuel XDR  |  |  |
|  |  |  |  |
|'SAUV'  |  numéro unité logique  |  8  | fichier de sortie  |
|  |  ou 'nom fichier'  |  |  |
|  |  mot-clé éventuel FORMAT |  |  |
|  |  mot-clé éventuel XDR  |  |  |
|  |  mot-clé éventuel BINA  |  |  |
|  |  mot-clé éventuel TAILLE | 4.5e8  |  |
|  |  suivi de la taille max  |  |  |
|  |  en nombre de mot simple  |  |  |
|  |  précision.  |  |  |
|  |  |  |  |
|'SORT'  |  numéro unité logique  |  7  | fichier de sortie  |
|  |  ou 'nom fichier'  |  |  |
|  |  |  |  |
|'SURV'  |  numero du segment Esope |  | Surveillance GEMAT  |
|  |  à surveiller  |  |  |
|  |  |  |  |
|'TRAC'  | BENS,IBM,GKS,PHIGS,X,PS  |  BENS  | unité de sortie  |
|  | MIF,PSC,OPEN  |  | graphique  |
|  |  |  |  |
|'VERI'  |  0,1  |  0  | Trace des opérateurs  |
|  |  |  |  |
|'ZERO'  | ENTIER positif  |  4  | Nombre de zéros  |
|  |  |  | consécutifs à prendre |
|  |  |  | en compte (RESOLUTION)|
|  |  |  |  |
|'PETI'  | FLOTTANT  |  | Defini la plus petite |
|  |  |  | valeur non nulle dans |
|  |  |  | Cast3M  |
|  |  |  |  |
|'GRAN'  | FLOTTANT  |  | Defini la plus grande |
|  |  |  | valeur dans Cast3M  |
|  |  |  |  |
|'PREC'  | FLOTTANT  |  | Precision des  |
|  |  |  | operations sur les  |
|  |  |  | FLOTTANTS  |
|  |  |  | (System Dependant)  |
|--------|----------------------------|--------|-----------------------|

    Exemple :

    OPTION DIME 2 ELEM QUA4 ;

    Remarques :

    --- VALE ---------------------------------------------------------

    Les valeurs courantes de certaines options peuvent être obtenues par
    l'opérateur VALE(UR).

    --- OPTI 'LANG' --------------------------------------------------

    Par défaut, la langue utilisée pour la notice et les messages
    d'erreur est le français. En fait, la notice de chaque opérateur
    contient une partie (la syntaxe) commune à toutes les langues et des
    parties spécifiques à chaque langue. Si on utilise par exemple
    "OPTION LANGUE JAVANAIS;", l'opérateur INFO n'imprimera que la
    syntaxe de l'opérateur et les messages d'erreurs seront en francais
    car ils n'existent pas en javanais.

    --- OPTI 'ECHO' --------------------------------------------------

    L'option ECHO permet de spécifier la verbosité de l'affichage dans
    Cast3M :
     - ECHO -1 : Affichage des messages d'erreur seulement
     - ECHO 0 : Ajout des Warnings (Messages d'erreur négatifs)
     - ECHO 1 : Ajout des instructions interprétées (Hors PROCEDURES)
     - ECHO 2 : Ajout du contenu des PROCEDURES externe

    --- OPTI 'MODE' --------------------------------------------------

    Le mode de calcul defini par MODE doit etre compatible avec la
    dimension courante (definie par DIME). Si tel n'est pas le cas, un
    message d'erreur sera affiche.

    En cas d'option MODE PLAN GENE, il faudra donner, par modèle, un
    point support aux inconnues supplémentaires (translation et
    rotations de la section) et de référence géométrique à la rotation
    de la section étudiée.

    En cas d'option MODE FOUR, on donne le numéro d'harmonique positif
    pour les modes symétriques et négatif pour les modes
    antisymétriques. En indiquant MODE FOUR NOHARM, on peut créer des
    objets utilisables en MODE FOUR quel que soit le numéro
    d'harmonique.

    Dans le cas d'une modelisation unidimensionnelle (DIME 1 MODE UNID),
    le mode de calcul par defaut est MODE UNID PLAN (DYDZ). Les options
    UNID PLAN et UNID AXIS correspondent, en mecanique, respectivement a
    UNID PLAN DYDZ et UNID AXIS AXDZ. Pour les options MODE UNID PLAN
    GYDZ, UNID PLAN GYCZ, UNID PLAN DYGZ, UNID PLAN CYGZ, UNID PLAN GYGZ
    et UNID AXIS AXGZ, il faudra ajouter a chacun des modeles un point
    support caracterisant la(les) direction(s) de deformation
    generalisee 'G-' (translation(s) de la ligne etudiee) et de ddl UY
    et UZ.

    En cas d'option MODE FREQ :
    - PASAPAS resout le problème dynamique dans la base des modes
      propres et extension en balayant l'échelle des fréquences ;
    - les objets MODELE déclarés ensuite sont associés à des champs
      munis de composantes imaginaires.

    --- OPTI 'SAUV' --------------------------------------------------

    Pour l'option SAUV avec FORMAT ou TAILLE, les mots clés doivent
    précéder le numéro de l'unité logique ou le nom du fichier.

    Le format de sortie XDR utilise la bibliothèque fxdr en provenance
    de l'université de California, San Diego et ses contributeurs

    --- OPTI 'NBP' --------------------------------------------------

    L'option NBP permet, en liaison avec RESTituer, de fusionner les
    résultats de plusieurs calculs faits avec le même maillage.

    --- OPTI 'TRAC' --------------------------------------------------

    Pour l'option TRAC, selon ce qui est supporté sur le système
    informatique utilisé, BENS crée des fichiers de type LGI, IBM
    appelle le système graphique GDDM, GKS appelle le système GKS, PHIGS
    appelle le système graphique PHIGS, X appelle l'interface X-WINDOW,
    PS crée un fichier de type PostScript monochrome, MIF crée un
    fichier au format Framemaker et PSC crée un fichier de type
    PostScript couleur.

    --- OPTI 'FTRA' --------------------------------------------------

    L'option 'FTRA' (Fichier de TRAcé) ne peut être utilisée que lorsque
    la sortie graphique se fait au format PS, PSC ou MIF. Elle permet
    non seulement de choisir le nom du fichier contenant les dessins
    mais aussi de modifier celui-ci au cours d'une session et ainsi
    créér plusieurs fichiers de dessins.
    Le mot-clé 'SUIT' permet au cours d'une meme execution de cast3m de
    realiser les traces a la suite des precedents dans le fichier
    specifie (sinon, le fichier est par defaut ecrase). Exemple :
      OPTI TRAC PSC FTRA 'toto-1.ps';
      DESS evol1;
      OPTI TRAC PSC FTRA 'toto-2.ps';
      DESS evol2;
      OPTI TRAC PSC FTRA 'toto-1.ps' 'SUIT';
      DESS evol3;
    --> toto-1.ps contiendra les traces des evolutions evol1 et evol3,
        et toto-2.ps contiendra le trace de evol2.

    --- OPTI 'NORM' --------------------------------------------------

    Pour l'option NORM il faut donner un LISTMOT contenant les inconnues
    primales à normaliser et le LISTREEL contenant les facteurs de
    normalisation. On peut aussi spécifier les variables duales avec
    leurs facteurs de normalisation. Il est aussi possible de demander
    la normalisation automatique 'AUTO' qui prend plus de temps.
    Ex. 1. Pour changer d'unité de mm vers des mètres il faut donner
        1000.
    Ex. 2. Pour les fluides, on peut donner les valeurs ROREF CREF et
        LCAR à 1 et normaliser P par ROREF * CREF * CREF / LCAR et PI
        par ROREF * LCAR.

    Le mot clé 'ANNU' (annuler) sert à annuler le recours à la
    normalisation des variables.

   Remarque 1) Lorsque la normalisation de variables est demandée, le
        programme duplique toutes les matrices élémentaires
        concernées et leur applique la normalisation. Le
        programme utilise donc beaucoup plus de mémoire en cas de
        résolution avec la normalisation que lorsque cette option
        est desactivée.

   Remarque 2) La normalisation des variables primales et duales
        entraîne la perte de la symétrie de la matrice inversée
        d'où le besoin encore accru en ressources dans ce cas là.

   Remarque 3) En cas de normalisation des matrices non-symétriques, il
        est demandé à l'utilisateur de spécifier les facteurs de
        normalisation pour les variables primales et
        duales. L'option automatique 'AUTO' est assimilée au cas
        où seules les variables primales à normaliser sont
        définies, elle ne marche donc pas dans le cas
        non-symétrique.

   Remarque 4) Il est déconseillé de modifier les options de
        normalisation entre deux inversions de la même matrice
        (au sens de l'objet de Cast3m).

    --- OPTI 'PARA' --------------------------------------------------

   Deux usages :

     1) Paralleliser automatiquement des operations avec les assistants
        (voir aussi ASSI).

     2) Vectoriser des operations sur des objets LISTOBJE.

   Concernant ce 2e usage, la syntaxe generale est :

        OPTI PARA VRAI ;
        LOBJ2 = OPER LOBJ1 ... ;
        OPTI PARA FAUX ;

   L'operateur OPER est alors applique a chaque element du LISTOBJE LOBJ1.
   Le resultat LOBJ2 est egalement un objet de type LISTOBJE. Les resultats
   de chaque operation elementaire doivent ainsi etre tous du meme type, et
   ce type doit pouvoir etre supporte par l'objet LISTOBJE (voir ENUM).

## MODE
    Operateur MODE (MODELISER)
    -------------------------- MATE CARA

    Objet :

    L'operateur MODE (MODELISER) permet d'associer a un maillage
une formulation, un modele de comportement du materiau, un type
d'element fini a utiliser et eventuellement un nom de constituant,
le nombre de points d'integration dans l'epaisseur des coques DKT
('INTEGRE' N1) et le point support de la deformation plane
generalisee ('DPGE' P1).
    Dans le cas d'un modele de comportement mecanique non lineaire
externe developpe par l'utilisateur, des informations supplementaires
doivent etre saisies : numero ou nom affecte a la loi de comportement,
liste des parametres externes, liste des composantes de materiau, liste
des variables internes de la loi.
   Le modele MELANGE PARALLELE permet de superposer des
comportements elementaires associes a des noms de phases, et d'en
realiser une combinaison lineaire a l'aide des coefficients de phases.
    Les differentes donnees et mots cles doivent apparaitre dans l'ordre
defini par la syntaxe ci-dessus.

CHAP{Specification generale}

    MODL1 = MODE GEO1 FOR1 MAT1 ( ...MATn ) (FUSION) ...

      | ... ( ELEM1 ... ELEMn ) ...
      |
      | ... ('INCO' MOT2 (MOT3) ) ...
      |
      | ... ('NON_LOCAL' MOT2 'V_MOYENNE' LMOTS6) ...
      |
      |  ( | 'NUME_LOI' ILOI1  | )  ( 'PARA_LOI' LMOTS1 )
        | 'NOM_LOI'  CLOI16 |
        ( 'C_MATERIAU' LMOTS2 ) ( 'C_VARINTER' LMOTS3 )

        ('INTEGRE' N1 ) ( 'CONS' MOT4 ) ( 'DPGE' P1)
        ('PHAS' MOT5 )  (| 'LIBRE' |)
        | 'LIE'  |
        (LMOTS4 LMOTS5) ;

      |  ... MODL2 ( ... MODLn)  ;

    Commentaire :

      GEO1 : geometrie (type MAILLAGE)

      FOR1 : formulation definie par un ou plusieurs mots
        choisis parmi :

        - formulations simples : |  'THERMIQUE'
        |  'MECANIQUE'
        |  'LIQUIDE'
        |  'POREUX'
        |  'DARCY'
        |  'CONTACT'
        |  'CONTRAINTE'
        |  'MAGNETODYNAMIQUE'
        |  'NAVIER_STOKES'
        |  'MELANGE'
        |  'EULER'
        |  'FISSURE'
        |  'LIAISON'
        |  'THERMOHYDRIQUE'
        |  'ELECTROSTATIQUE'
        |  'DIFFUSION'
        |  'CHARGEMENT'
        |  'METALLURGIE'
        |  'CHANGEMENT_PHASE'

        - formulation couplee : 'LIQUIDE' 'MECANIQUE'

     MAT1 (...MATn ) : type de materiau avec autant de mots que
        necessaire (type MOT). Les types possibles
        sont listes plus loin.

     (FUSION) : pour les modeles mecaniques non-lineaires,
        exceptes NON_LINEAIRE (Umat) et VISCO_EXTERNE,
        cette option permet de prendre en compte la fusion
        du materiau dans l'integration du comportement par
        la mise a zero des varirables internes pour T > Tfus.

     ( ELEM1...ELEMn ) : element(s)-fini(s) particulier(s) a utiliser
        (type MOT). Par defaut, on utilise l'element fini
        ayant le meme nom que le support geometrique.
        Cette liste est obligatoire pour les coques et
        les elements joints. Les types possibles sont
        listes plus loin. Pour le modele 'NAVIER_STOKES'
        on peut utiliser les noms generiques LINE
        (lineaire) MACRO (iso-P2 iso-P1) ou QUAF
        (quadratique pour les fluides).
        Pour la formulation 'MECANIQUE' le nom generique
        BBAR induit des termes spheriques diminues de la
        projection de la trace dans la base des derivees
        des fonctions de forme.

     ( NON_LOCAL MOT2 ) : uniquement pour la mise en oeuvre non locale.
        MOT2 definit cette mise en oeuvre: 'MOYE' si
        simple moyenne par methode integrale, suivi de 'SB'
        si methode integrale basee sur l'etat de contraintes,
        ou 'HELM' si basee sur la methode différentielle
        (équation de Helmholtz).
        Il faut ensuite donner le mot clef 'V_MOYENNE' pour
        preciser dans LMOTS6 la liste des variables internes
        a traiter en non local.

     ( INCO MOT2 (MOT3) ) : uniquement pour la formulation DIFFUSION :
        noms des inconnues primale MOT2 et duale MOT3.
        ATTENTION : le nom de l'inconnue primale est
        limite a 2 caracteres (CO par defaut) afin de
        pouvoir nommer les composantes du gradient
        (CO,X...). La donnee de MOT3 est optionnelle.
        Le nom de l'inconnue duale est, par defaut,
        'QXX', quand 'XX' est le nom de la primale.

     Ensemble de 4 donnees definissant un modele de comportement externe
     programme par l'utilisateur, en formulation 'MECANIQUE' :
     => loi 'NON_LINEAIRE' 'UTILISATEUR', pouvant etre associee a
        - 'ELASTIQUE' 'ISOTROPE',
        - 'ELASTIQUE' 'ORTHOTROPE',
        - 'ELASTIQUE' 'ANISOTROPE',
        - 'ELASTIQUE' 'UNIDIRECTIONNEL'.
     => loi de comportement du groupe 'VISCO_EXTERNE', pouvant etre
        associee uniquement a 'ELASTIQUE' 'ISOTROPE'.

     ( ILOI1 ) : Numero affecte a la loi de comportement externe.
        type ENTIER : 1 <EG ILOI1 <EG 999999
     ( CLOI16 ) : Nom affecte a la loi de comportement externe.
        type MOT de 16 caracteres au maximum
     ILOI1 OU CLOI16 = donnee obligatoire pour tout modele externe.

     ( LMOTS1 ) : Objet de type LISTMOTS donnant la liste des noms des
        parametres externes de la loi de comportement.
        Donnee facultative.
        Si la temperature 'T ' fait partie des parametres
        externes du modele, elle doit etre declaree en tete
        de liste.
        Les redondances dans la liste des parametres externes
        sont interdites.

     ( LMOTS2 ) : Objet de type LISTMOTS donnant la liste des noms des
        composantes de materiau de la loi de comportement.
        Donnee obligatoire pour une loi de comportement
        'NON_LINEAIRE' 'UTILISATEUR' : toutes les composantes
        du comportement (domaine lineaire et non lineaire)
        doivent etre declarees. Les redondances dans la liste
        des composantes de materiau sont interdites.
        Donnee ignoree dans les autres cas : toutes les lois
        du groupe 'VISCO_EXTERNE' ont les memes composantes de
        materiau que le comportement 'ELASTIQUE' 'ISOTROPE'.

     ( LMOTS3 ) : Objet de type LISTMOTS donnant la liste des noms des
        variables internes de la loi de comportement.
        Donnee facultative.
        Les redondances dans la liste des variables internes
        sont interdites.
        Par defaut, les lois du groupe 'VISCO_EXTERNE' ont 4
        variables internes : 'EC0 ', 'ESW0', 'P ' et 'QTLD'.
        L'objet LMOTS3 donne la liste des variables internes
        supplementaires par rapport aux 4 pre-definies.

     Remarques :
     => Une loi 'NON_LINEAIRE' 'UTILISATEUR' peut s'appliquer a tout
        type d'element fini, a l'exeption des coques sans points
        d'integration dans l'epaisseur.
        Pour les elements autres que les massifs, les caracteristiques
        geometriques utiles peuvent etre declarees parmi les parametres
        externes de la loi.
     => Les lois du groupe 'VISCO_EXTERNE' ne s'appliquent en l'etat
        actuel qu'aux elements massifs.
     => Pas de redondances entre noms de composantes de materiau et
        noms de variables internes.
     => Si le modele externe 'NON_LINEAIRE' 'UTILISATEUR' calcule des
        deformations inelastiques, celles-ci peuvent etre sorties si
        elles ont ete declarees parmi les variables internes.

     ( LMOTS4 ) : Objet de type LISTMOTS donnant la liste des noms des
        inconnues primales pour un materiau impedance pour
        un support POI1 ou le premier point d'un SEG2

     ( LMOTS5 ) : Objet de type LISTMOTS donnant la liste des noms des
        inconnues primales pour un materiau impedance pour
        le second point d'un SEG2

      (N1 ) : nombre de points integration(entre 1 et 15) dans
        l'epaisseur lorsqu'on utilise les elements de
        coque avec integration numerique dans l'epaisseur .
        Il est conseille d'utiliser un nombre impair.

     ( MOT4 ) : nom du constituant (type MOT, au maximum 16 caracteres)
        Cette possibilite est a utiliser lorsque l'on veut
        associer dans un meme calcul plusieurs modeles a un
        meme objet maillage, comme par exemple dans le cas des
        coques multicouches. Le nom MOT4 permet alors a
        l'utilisateur d'identifier chacun des constituants.
        Par defaut, chaque modele a un constituant unique.

     ( MOT5 ) : nom de phase (type MOT, au maximum 8 caracteres)
        Cette possibilite est a utiliser lorsque l'on veut
        associer dans un meme calcul plusieurs modeles a un
        meme objet maillage, et combiner ces modeles comme
        dans un melange multiphases. Le nom MOT5 permet alors a
        l'utilisateur d'identifier chacune des phases.
        Par defaut, la phase est ' '.

     ( 'LIBRE' ) : pour les elements JOI1, il est possible d'indiquer si le
     ( 'LIE' ) repere local est libre (par defaut) ou lie au maillage des
        joints. Un repere local lie peut etre mis a jour selon le
        deplacement du maillage grace a l'operateur FORM (utilise
        en grands deplacements). Dans ce cas, la longueur des
        joints doit etre non nulle.

      MODL2 ( .. MODn) : modele possedant un nom de phase (type
        MMODEL)

      MODL1 : objet modele resultat (type MMODEL)

 Remarque :

 Les noms de formulation et de comportement de materiau doivent
 etre donnes en toutes lettres.

CHAP{MECANIQUE}
    | Noms des materiaux en MECANIQUE |

 Le comportement lineaire doit d'abord etre defini, puis
 le comportement non lineaire, le cas echeant, selon les
 directives ci-dessous. Par exemple, les donnees suivantes :

        ELASTIQUE ISOTROPE PLASTIQUE ISOTROPE

 correspondent a un materiau dont le comportement lineaire est
 elastique isotrope et dont le comportement non lineaire est
 plastique selon un modele de Von Mises a ecrouissage isotrope.

PART{LINEAIRE}
- Comportements lineaires :

 * 'ELASTIQUE'  | ('ISOTROPE')  (option par defaut)
        | 'ORTHOTROPE'
        | 'ANISOTROPE'
        | 'UNIDIRECTIONNEL'
        | 'HOMOGENEISE'
        | 'SECTION'
        | 'ARMATURE'
        | 'MODAL'
        | 'STATIQUE'
        | 'IMPEDANCE'

    Le cas SECTION est utilisable pour les poutres de Timoschenko
    et permet de decrire le comportement lineaire et non lineaire
    d'une section droite. Si l'element de poutre est en 2D
    (Contraintes ou deformations planes), l'axe Oy du repere local
    de l'element de poutre correspond a l'axe Ox de la section.

    Le cas ARMATURE est utilise pour les armatures (actives ou
    passives) du beton arme ( element fini : BARRE, support
    geometrique : SEG2).

    Le materiau 'MODAL' permet une representation des deplacements
    sur une base de modes propres (voir VIBR). Le support geometrique
    est un maillage constitue d'un point. De maniere analogue le
    materiau 'STATIQUE' permet une representation au moyen d'une
    solution elastique. Ces deux materiaux sont compatibles avec
    un materiau 'IMPEDANCE' non-lineaire.

- Comportements non lineaires :

PART{NON_LINEAIRE (UMAT)}
 * 'NON_LINEAIRE' : comportement elastique non lineaire ou
        comportement non lineaire externe.
        Pas d'option par defaut.
        Doit etre suivi d'un mot choisi parmi :

       |----------------------------------------------------------------
       | 'EQUIPLAS' : Modele de comportement elastique
       |  non-lineaire dont le comportement en
       |  charge est strictement identique au
       |  comportement plastique isotrope
       |
       |----------------------------------------------------------------
       | 'UTILISATEUR' : Modele de comportement non lineaire externe
       |  developpe par l'utilisateur.
       |
       |  Un numero ILOI1 ou un nom CLOI16 doit etre affecte a la loi
       |  de comportement externe.
       |  La liste des parametres externes de la loi est donnee par
       |  l'objet LMOTS1 (le cas echeant).
       |  La liste des composantes de materiau est donnee par LMOTS2.
       |  Cette liste couvre les domaines lineaire et non lineaire du
       |  comportement.
       |  La liste des variables internes de la loi est donnee par
       |  l'objet LMOTS3 (le cas echeant).
       |
       |  Le modele 'NON_LINEAIRE' 'UTILISATEUR' est integre par un
       |  formalisme programme par l'utilisateur dans le module
       |  externe UMAT.
       |  Ce module est appele par l'operateur COMP pour la resolution
       |  a chaque point d'integration du modele. Etant donnes :
       |  - un etat initial a l'instant t0 : contraintes, deformations
       |  totales, variables internes ;
       |  - un pas de temps dt ;
       |  - un increment de deformations totales impose de t0 a t0+dt ;
       |  - les valeurs des parametres externes a t0 et t0+dt ;
       |  le module UMAT calcule l'etat final a t0+dt : nouvelles
       |  contraintes et variables internes (parmi lesquelles les
       |  deformations inelastiques le cas echeant).
       |
       |  Remarque :
       |
       |  Un certain nombre de lois sont pre-existantes dans la version
       |  fournie. On peut citer les lois definies par le numero :
       |  5  pour plastique isotrope
       |  7  pour VISCOPLASTIQUE' 'GATT_MONERIE'
       |  10  pour ELASTICITE ISOTROPE ISOTHERME
       |  11  pour ELASTICITE ISOTROPE NON ISOTHERME
       |  12  pour ELASTICITE ORTHOTROPE ISOTHERME
       |  21,22  pour 'FLUAGE' 'POLYNOMIAL' (massif)
       |  31  pour modele Mooney-rivlin(2D Plan CONT,3D massif)
       |  32  pour modele neo-hookien
       |  33  pour modele  GD (hyperelastique)
       |  34  pour modele Hart-Smith (hyperelastic)
       |  35  pour modele Biderman (hyperelastic)
       |  36  pour modele 8chaines (hyperelastic)
       |  Des exemples d'utilisations de ces lois existent dans les
       |  fichiers .dgibi fournis et les donnees des parametres sont
       |  MATE
       |
       |
       |  Mode operatoire :
       |  ---------------
       |  1 - Programmer le module externe UMAT et ses dependances :
       |  - Reprendre le module exemple integre au code.
       |  Il faut conserver imperativement la premiere carte du
       |  module exemple pour assurer le succes de la compilation.
       |  - Respecter l'interface d'appel de la routine.
       |  2 - Compiler le module externe et ses dependances, puis
       |  edition de liens avec le reste du code.
       |  3 - Mise en oeuvre en langage Gibiane en respectant la syntaxe
       |  decrite ci-dessus.
       |
       |  Interface du module externe UMAT :
       |  --------------------------------
       |  SUBROUTINE UMAT ( STRESS, STATEV, DDSDDE, SSE, SPD, SCD,
       | &  RPL, DDSDDT, DRPLDE, DRPLDT,
       | &  STRAN, DSTRAN, TIME, DTIME,
       | &  TEMP, DTEMP, PREDEF, DPRED,
       | &  CMNAME, NDI, NSHR, NTENS, NSTATV,
       | &  PROPS, NPROPS, COORDS,
       | &  DROT, PNEWDT, CELENT, DFGRD0, DFGRD1,
       | &  NOEL, NPT, LAYER, KSPT, KSTEP, KINC )
       |  IMPLICIT REAL*8(A-H,O-Z)
       |
       |  CHARACTER*16  CMNAME
       |
       |  INTEGER  NDI, NSHR, NTENS, NSTATV, NPROPS,
       | &  NOEL, NPT, LAYER, KSPT, KSTEP, KINC
       |
       |  REAL*8  STRESS(NTENS), STATEV(*),
       | &  DDSDDE(NTENS,NTENS),
       | &  SSE, SPD, SCD,
       | &  RPL, DDSDDT(NTENS), DRPLDE(NTENS), DRPLDT,
       | &  STRAN(NTENS), DSTRAN(NTENS),
       | &  TIME(2), DTIME,
       | &  TEMP, DTEMP, PREDEF(*), DPRED(*),
       | &  PROPS(NPROPS),
       | &  COORDS(3),
       | &  DROT(3,3),
       | &  PNEWDT,
       | &  CELENT,
       | &  DFGRD0(3,3), DFGRD1(3,3)
       |
       |
       |  IN/OUT : STRESS : REAL*8(NTENS), tenseur des contraintes
       |  En entree : tenseur des contraintes a t0
       |  En sortie : tenseur des contraintes a t0+dt
       |  IN/OUT : STATEV : REAL*8(*), variables internes
       |  En entree : variables internes a t0
       |  En sortie : variables internes a t0+dt
       |
       |
       |  OUT  : DDSDDE : REAL*8(NTENS,NTENS), matrice jacobienne du
       |  modele (matrice tangente) a t0+dt
       |  Sortie facultative, non exploitee par CAST3M
       |  pour l'instant
       |
       |  IN/OUT : SSE  : REAL*8, energie de deformation elastique
       |  SPD  : REAL*8, dissipation plastique
       |  SCD  : REAL*8, dissipation visqueuse
       |  Valeurs a t0 en entree, a t0+dt en sortie
       |  Entrees/sorties facultatives, non exploitees
       |  par CAST3M pour l'instant
       |
       |
       |  OUT  : RPL  : REAL*8, puissance calorifique volumique
       |  degagee par le travail mecanique, a t0+dt
       |  DDSDDT : REAL*8(NTENS), derivee du tenseur des
       |  contraintes par rapport a la temperature,
       |  a t0+dt
       |  DRPLDE : REAL*8(NTENS), derivees de RPL par rapport
       |  aux composantes du tenseur des deformations,
       |  a t0+dt
       |  DRPLDT : REAL*8, derivee de RPL par rapport a la
       |  temperature, a t0+dt
       |  Sorties facultatives, non exploitees par
       |  CAST3M pour l'instant
       |  Ces sorties sont prevues pour un couplage
       |  fort entre thermique et mecanique
       |
       |
       |  IN  : STRAN  : REAL*8(NTENS), tenseur des deformations
       |  totales a t0
       |  DSTRAN : REAL*8(NTENS), tenseur des increments de
       |  deformation totale par rapport a l'etat
       |  de reference a t0
       |
       |
       |  IN  : TIME  : REAL*8(2), TIME(1) = 0
       |  TIME(2) = t0
       |  DTIME  : REAL*8,  DTIME  = dt
       |  t0 : precedent instant d'equilibre atteint
       |  dt : nouveau pas de temps propose par
       |  PASAPAS pour atteindre l'equilibre
       |  avec l'increment de deformation totale
       |  impose (DSTRAN)
       |
       |
       |  IN  : TEMP  : REAL*8, temperature a t0
       |  DTEMP  : REAL*8, increment de temperature a t0+dt
       |  PREDEF : REAL*8(*), vecteur des parametres externes
       |  de la loi de comportement, valeurs a t0
       |  DPRED  : REAL*8(*), increments des parametres
       |  externes a t0+dt
       |
       |
       |  IN  : CMNAME : CHARACTER*16, identifiant de la loi de
       |  comportement
       |  1) La loi est identifiee par le numero qui lui
       |  a ete attribue : ILOI1, mot cle 'NUME_LOI'
       |  Par convention, ce numero est encode dans
       |  les 4 derniers caracteres de la chaine,
       |  et doit etre recupere dans UMAT par une
       |  instruction du type
       |  K4ILOI = CMNAME(13:16)
       |  (K4ILOI variable locale de type CHARACTER*4)
       |  2) La loi est identifiee par le nom qui lui a
       |  a ete attribue : CLOI16, mot cle 'NOM_LOI'
       |  et peut etre recupere dans UMAT directement
       |  car CMNAME = CLOI16 (variable CHARACTER*16)
       |
       |
       |  IN  : NDI  : INTEGER definissant le type de calcul CAST3M
       |
       |
       |  IN  : NSHR  : INTEGER
       |  Entree non active dans le cas d'une
       |  adherence a CAST3M
       |
       |
       |  IN  : NTENS  : INTEGER, nombre de composantes du tenseur
       |  des contraintes
       |  NSTATV : INTEGER, nombre de variables internes
       |
       |
       |  IN  : PROPS  : REAL*8(NPROPS), vecteur des constantes
       |  de materiau
       |  NPROPS : INTEGER, nombre de constantes de materiau
       |
       |
       |  IN  : COORDS : REAL*8(3), coordonnees cartesiennes du point
       |  d'integration courant
       |
       |
       |  IN  : DROT  : REAL*8(3,3), matrice de passage du repere
       |  local de l'element fini massif au repere
       |  general du maillage
       |  Entree non active pour les elements finis
       |  non massifs
       |
       |
       |  OUT  : PNEWDT : REAL*8, rapport entre le nouveau pas de
       |  temps suggere et le pas de temps en entree
       |  (NEWDT = PNEWDT * DTIME)
       |
       |
       |  IN  : CELENT : REAL*8, longueur caracteristique de
       |  l'element
       |  Determinee comme la distance maximale entre
       |  deux noeuds de l'element.
       |
       |
       |  IN  : DFGRD0 : REAL*8(3,3), tenseur gradient de deplacement
       |  a t0
       |  DFGRD1 : REAL*8(3,3), tenseur gradient de deplacement
       |  a t0+dt
       |
       |
       |  IN  : NOEL  : INTEGER, numero de l'element courant
       |  Attention : numerotation locale (numero de
       |  l'element dans la sous-zone courante)
       |  NPT  : INTEGER, numero du point d'integration
       |  courant
       |
       |
       |  IN  : LAYER  : INTEGER
       |  KSPT  : INTEGER,
       |  Entrees non actives dans le cas d'une
       |  adherence a CAST3M
       |
       |
       |  IN  : KSTEP  : INTEGER
       |  KINC  : INTEGER
       |  Entrees n'ayant pas de sens dans
       |  le cas d'une adherence a CAST3M
       |
       |  CONVENTION : on autorise la programmation de l'utilisateur a
       |  se servir de KINC comme code retour. Regles a respecter :
       |  1 - Pas d'initialisation superflue de KINC en entrant dans
       |  UMAT. KINC est initialise a 1 avant l'appel a UMAT.
       |  2 - En cas d'erreur, KINC est affecte d'une valeur
       |  differente de 1
       |
       |----------------------------------------------------------------

PART{PLASTIQUE}
 * 'PLASTIQUE' suivi d'un mot choisi parmi :

       | ('ISOTROPE') : Modele de Von Mises a ecrouissage isotrope
       |  (option par defaut)
       |
       | 'PARFAIT'  : Modele de Von Mises sans ecrouissage
       |
       | 'CINEMATIQUE'  : Modele de Von Mises a ecrouissage
       |  cinematique lineaire
       |
       | 'DRUCKER_PARFAIT' : Modele de Drucker-Prager a ecoulement
       |  associe et sans ecrouissage
       |
       | 'DRUCKER_PRAGER'  : Modele de Drucker-Prager a ecoulement
       |  non associe et ecrouissage
       |
       | 'BETON'  : Modele beton (uniquement en contraintes
       |  planes).
       |
       | 'CHABOCHE1'  : Modele Chaboche a un centre (et ecrouissage
       |  isotrope).
       |
       | 'CHABOCHE2'  : Modele Chaboche a deux centres (et ecrouis-
       |  sage isotrope).
       |
       | 'TUYAU_FISSURE'  : Modele de plasticite (parfaite)/
       |  (ecrouissage) pour l'element TUYAU
       |  FISSURE.
       |
       | 'ENDOMMAGEABLE'  : Modele de materiau elastoplastique
       |  endommageable (Lemaitre Chaboche).
       |
       | 'GAUVAIN'  : Modele de Gauvain.
       |
       | 'BILIN_MOMY'  : modele de flexion ou de cisaillement
       | 'BILIN_EFFZ'  bilineaire pour les element POUT et TIMO
       |
       | 'TAKEDA_MOMY' : modele de flexion ou de cisaillement
       | 'TAKEMO_EFFZ'  de takeda pour les element POUT et TIMO
       |
       | 'BA1D'  : modele global de poteau en bÃ©ton armÃ©
       |  en flexion pour les elements POUT
       |
       | 'LINESPRING'  : Modele de plasticite (parfaite)/(ecrouis-
       |  sage) pour l'element LINESPRING.
       |
       | 'UBIQUITOUS'  : Modele Ubiquitous.
       |
       | 'GLOBAL'  : Modele de plasticite pour les elements en
       |  beton arme qui permet la prise en compte
       |  des lois de comportement globales, diffe-
       |  rentes selon les types de sollicitation.
       |
       | 'CAM_CLAY' : Modele ayant un comportement elastique
       |  non-lineaire en volume et plastique en
       |  volume et en distorsion.
       |
       | 'HUJEUX'  : Modele de comportement de sols et de
       |  certains milieux granulaires, ayant
       |  un comportement plastique en volume et
       |  en distorsion.
       |
       | 'GURSON'  : Modele plastique basee sur la surface de
       |  de Gurson qui depend de la pression. La
       |  porosite est introduite comme variable
       |  interne. Ce modele est utilise pour la
       |  rupture ductile par croissance de cavites.
       |  Il n'est implante qu'en 3D et en axisym.
       |
       | 'JOINT_DILATANT' : Modele de joint avec critere de
       |  type Mohr-Coulomb et ecoulement non
       |  associe (en 2D cont. planes, defo. planes)
       |
       | 'JOINT_SOFT' : Modele de joint avec critere de
       |  type Mohr-Coulomb et adoucissement et sans dilatance
       |  (en 2D cont. planes, defo. planes)
       |
       | 'JOINT_COAT' : Modele de joint en cisaillement avec critere de
       |  plasticite isotrope, adoucissement et endommagement.
       |  (en 2D cont. planes, defo. planes)
       |
       | 'ANCRAGE_ELIGEHAUSEN' : Modele d'ancrage reprenant la loi
       |  d'Eligehausen (avec adoucissement) en cisaillement
       |  Le comportement du joint en traction-compression
       |  reste elastique lineaire.
       |  (en 2D cont. planes, defo. planes)
       |
       | 'COULOMB'  : Modele de joint dilatant avec critere de
       |  type Mohr-Coulomb et ecoulement associe
       |  (en 3D isotrope, 2D axi, cont. planes, defo. planes)
       |
       | 'INTJOI  ' : Modele d'interface acier/beton sans/avec prise
       |  en compte de la corrosion. Trois mecanismes sont
       |  couples : endommagement, glissement interne et
       |  anelasticite des produits de corrosion s'il y a
       |  lieu. Ce modele est implante pour des elements
       |  joints 2D/3D.
       |
       | 'AMADEI'  : Modele de joint non lineaire incremental
       |  a comportement adoucissant en cisaillement
       |  (en 3D isotrope, 2D axi, defo. planes)
       |
       | 'ACIER_UNI': Modele de comportement de l'acier de
       |  Menegotto-Pinto utilisable pour les elements
       |  modelisant une section de poutre  (modele a fibre)
       |  et les elements de barre
       |
       | 'ACIER_ANCRAGE': Modele de comportement d'ancrage ou de recouvrement
       |  base sur de le modele d'acier ACIER_UNI et le modele
       |  de glissement acier/beton ANCRAGE_ELIGEHAUSEN.
       |  Cette loi uniaxiale est valable pour des elements de
       |  barre ou des sections de poutre  (modele a fibre)
       |  et les elements de barre
       |
       | 'BETON_UNI': Modele de comportement du beton de
       |  Hognestad utilisable pour les elements
       |  modelisant une section de poutre (modele a fibre)
       |  et les elements de barre
       |
       | 'BETON_BAEL':Modele de beton du BAEL pour les elements
       |  modelisant une section de poutre (modele a fibre)
       |  et les element de barre
       |
       | 'MAZARS'  : Modele d'endommagement scalaire pour le beton
       |  (bien adapte aux chargements monotones) pour les
       |  elements modelisant une section de poutre (modele a fibre)
       |  Ce modele a ete implemente dans le modele a fibre
       |  dans sa formulation 3D complete et non pas uniaxiale
       |
       | 'INTIMP'  : Modele d'acier corrode couple avec un modele
       |  d'interface acier/beton RICINT. Le couplage est effectue
       |  en realisant l'equilibre d'un element barre. Ce modele
       |  permet une prise en compte de l'interface acier/beton dans
       |  un calcul de type multifibre en relaxant les contraintes
       |  dans l'acier selon le niveau d'endommagement de l'interfac
       |
       | 'UNILATERAL'  : Modele d'endommagement a 2 variables
       |  scalaires pour le beton ( bien adapte
       |  aux chargements cycliques ) pour les elements
       |  modelisant une section de poutre (modele a fibre)
       |  et les elements de barre (modele de laborderie)
       |
       | 'FRAGILE_UNI':Modele d'endommagement et unilateral fragile
       |  en traction et en compression pour les elements
       |  modelisant une section de poutre (modele a fibre)
       |
       | 'STRUT_UNI':  Modele non-lineaire pour l'effort tranchant
       |  (diagonale en beton pour la compression et cadre
       |  pour la traction) pour les elements
       |  modelisant une section de poutre (modele a fibre)
       |
       | 'CISAIL_NL' : Modele non-lineaire avec adoucissement
       |  reliant cisaillement et effort tranchant
       |  pour les elements de poutre de Timoshenko
       |  et les elements modelisant une section de
       |  poutre (modele a fibre) (la loi est non lineaire
       |  dans la direction Oz du repere local de la poutre)
       |
       | 'INFILL_UNI'  : modele non-lineaire d'endommagement-plasticite
       |  unilateral avec adoucissement en compression et
       |  sans resistance en traction  (element de barre
       |  uniquement).
       |  Cette loi peut etre utilisee sur deux
       |  elements de barre comme modele global
       |  pour modeliser les murs de remplissage en maconnerie
       |
       | 'PARFAIT_UNI': Modele d'acier elasto-plastique avec ecrouissage
       |  cinematique pour les elements modelisant une
       |  section de poutre
       |
       | 'PARFAIT_ANCRAGE': Modele de comportement d'ancrage ou de recouvrement
       |  base sur de le modele d'acier PARFAIT_UNI et le modele
       |  de glissement acier/beton ANCRAGE_ELIGEHAUSEN.
       |  Cette loi uniaxiale est valable pour des elements de
       |  barre ou des sections de poutre (modele a fibre)
       |
       | 'OTTOSEN'  : Modele de comportement des materiaux fragiles
       |  ecrit selon l'approche des modeles de fissuration
       |  fictive. Lorsque l'endommagement est localise, le
       |  modele tient compte d'un parametre de taille
       |  donnant une mesure de la zone degradee afin
       |  d'assurer un calcul objectif vis a vis du
       |  choix du maillage.
       |
       | 'OTTOVARI' : Nouvelle implementation du modele OTTOSEN pour traiter le
       |  cas ou les parametres materiau sont variables.
       |  Seulement pour les elements massifs volumiques.
       |
       | 'BETOCYCL'  : Modele plastique reproduisant la degradation
       |  de resistance en compression sous chargement
       |  cyclique. Le modele comporte deux surfaces
       |  (une "interieure" et une "exterieure")
       |  ayant chacune un mecanisme de traction
       |  et un de compression du type Rankyne.
       |  Ce modele a ete developpe pour la modelisation
       |  de structures planes en maconnerie soumises
       |  a des chargements cycliques
       |  (en 2D contraintes planes).
       |
       | 'STEINBERG': Modele de comportement de Steinberg-Cochran
       |  -Guinan utilisable pour des elements
       |  massifs. Ce modele a ete elabore pour
       |  reproduire le comportement sous choc
       |  des solides metalliques.
       |
       | 'ZERILLI'  : Modele de comportement de Zerilli-Armstrong
       |  utilisable pour des elements massifs.
       |  Il propose une formulation mathematique
       |  de la contrainte d'ecoulement au sens de
       |  Von Mises s'appuyant sur la theorie des
       |  dislocations.
       |
       | 'PRESTON'  : Modele de comportement de
       |  Preston-Tonks-Wallace
       |  utilisable pour des elements massifs.
       |  Il propose une formulation mathematique
       |  de la contrainte d'ecoulement s'appuyant,
       |  d'une part sur la theorie des dislocations
       |  et d'autres part sur la theorie
       |  de l'analyse dimensionnelle.
       |
       | 'HINTE'  : Modele de joint avec degradation jusqu'a la
       |  phase ultime de la rupture. Ce modele
       |  d'endommagement est independant du temps.
       |  Il a comme support geometrique les elements
       |  raccord ( en 2D pour l'instant)
       |
       | 'J2'  : Modele de Von Mises avec ecrouissage isotrope
       |  exponentiel/lineaire
       |  matrice tangente consistante disponible
       |  (option de calcul : plan defo,axis)
       |
       | 'RH_COULOMB'  : Modele de Mohr Coulomb approche hyperbolique
       |  plasticite parfaite et associee
       |  matrice tangente consistante disponible
       |  sous-decoupage disponible (voir SSTE)
       |  (option de calcul : plan defo,axis)
       |
       | 'MRS_LADE'  : Modele de MRS-Lade pour les materiaux granulaires
       |  sans cohesion
       |  Cap-modele,ecrouissage conique non associe
       |  matrice tangente consistante disponible
       |  sous-decoupage disponible (voir SSTE)
       |  (option de calcul : plan defo,axis)
       |
       | 'VMT_FEFP'  : Modele de Von Mises Tresca avec ecrouissage isotrope
       |  exponentiel/lineaire, hyperelasticite et
       |  deformations finies
       |  matrice tangente consistante disponible (voir ECFE)
       |  (option de calcul : plan defo,axis)
       |
       | 'RHMC_FEFP'  : Modele de Mohr Coulomb plastique approche
       |  hyperbolique avec hyperelasticite et
       |  deformations finies
       |  plasticite parfaite et associee
       |  matrice tangente consistante disponible (voir ECFE)
       |  (option de calcul : plan defo,axis)
       |
       | 'POWDER_FEFP'  : Modele de plasticite elliptique dependant de la
       |  densite avec hyperelasticite et deformations finies
       |  utilise pour la simulation de compaction de poudre
       |  a froid
       |  matrice tangente consistante disponible (voir ECFE)
       |  (option de calcul : plan defo,axis)
       |
       | 'POWDERCAP_FEFP': Modele de plasticite elliptique dependant de la
       |  densite avec hyperelasticite et deformations finies
       |  utilise pour la simulation de compaction de poudre
       |  a froid
       |  matrice tangente consistante disponible (voir ECFE)
       |  (option de calcul : plan defo,axis)
       |
       | 'DRUCKER_PRAGER_2' : Modele de plasticite adoucissant pour les betons
       |  a deux surfaces seuils : un critere de Rankine en
       |  traction et un critere de drucker-prager adoucissan
       |  en compression
       |
       | 'RICBET_UNI' :  Modele d'endommagement pour le beton (bien adapte aux
       |  chargements cycliques et sismique) pour les elements
       |  modelisant une section de poutre (modele a fibre).
       |  La particularite de ce modele est qu'il prend en comp
       |  les effets hysteretiques locaux.
       |
       | 'DP_SOL' :  Modele de plasticite Drucker-Prager avec loi
       |  d ecoullement non assosie et ecrouissage non lineaire
       |
       | 'LIAISON_ACBE' :  Modele d'adherence unidimensionnel (liaison
       |  acier-beton) prenant en compte la decharge,
       |  pour les elements coaxiaux (COA2 et COS2)
       |  dans le cas tridimensionel.
       |
       | 'OUGLOVA' :  Modele de elastoplastique endommageable de l'acier
       |  corrode. Implante pour des calculs en 3D, 2D, 1D et
       |  multifibres
       |
       | 'IWPR3D_SOL' :  Modele de plasticite base sur le travaux de
       |  Prevost sur un modele de nested yield surface
       |  La loi est composee de 10 surface de charge
       |  Ã  ecrouissage lineaire. La loi peut reppresenter
       |  l'anisotropie dans la phase plastique
       |
       | 'NORTON' :  Modele de fluage de Norton unidirectionnel pour les elements modelisant une
       |  section de poutre (modele a fibre, elements finis POJS, TRIS, QUAS).
       |
       | 'POLYNOMIAL' : Modele de fluage polynomial unidirectionnel pour les elements modelisant
       |  une section de poutre (modele a fibre, elements finis POJS, TRIS, QUAS).
       |
       | 'BLACKBURN' et 'BLACKBURN_2' : Modeles de fluage de Blackburn unidirectionnel pour les
       |  elements modelisant une section de poutre (modele a fibre,
       - elements finis POJS, TRIS, QUAS).
       |
       | 'LEMAITRE' : Modele de fluage de Lemaitre unidirectionnel pour les elements modelisant
       |  une section de poutre (modele a fibre, elements finis POJS, TRIS, QUAS).

PART{ENDOMMAGEMENT}
 * 'ENDOMMAGEMENT' suivi d'un mot choisi parmi :

       | 'MAZARS'  : Modele d'endommagement scalaire pour
       |  le beton (bien adapte aux chargements monotones)
       |
       | 'UNILATERAL'  : Modele d'endommagement a 2 variables
       |  scalaires pour le beton (bien adapte aux chargements cycliques)
       |
       | 'ROTATING_CRACK' : Modele d'endommagement pour le
       |  beton
       |
       | 'SIC_SIC' : Modele d'endommagement pour le composite
       |  ceramique SiC/SiC
       |
       | 'MVM'  : Modele d'endommagement de Von Mises modifie
       |  dommage scalaire nonlocal pour materiau quasifragile
       |
       | 'SICSCAL'  : Modele 'scalaire' d'endommagement pour le composite
       |  tisse  SiCf/SiC developpe a l'ONERA avec 3 variables
       |  d'endommagement correspondant aux plans perpendiculaires
       |  aux directions des fibres: d1 et d2 et dans le plan
       |  du pli: d3.
       |
       | 'SICTENS'  : Modele 'pseudo-tensoriel' d'endommagement pour le compos
       |  tisse  SiCf/SiC developpe a l'ONERA avec 5 variables
       |  d'endommagement correspondant aux plans perpendiculaires
       |  aux directions des fibres : d1 et d2, dans le plan du pl
       |  et dans les plans perpendiculaires aux directions a + et
       |  45Â° des fibres (rotation dans le plan du pli).
       |
       | 'DAMAGE_TC'  : Modele d'endommagement a deux variables : une en tractio
       |  et une en compression. Ce modele est utilisation en
       |  cyclique et est regularise par energie de fissuration.
       |
       | 'DESMORAT'  : Modele d'endommagement anisotrope pour le beton
       |  ( bien adapte aux chargements monotones ).
       |  Ce modele est utilisable en non local.
       |
       | 'FATSIN'  : Modele d'endommagement scalaire isotrope de materiaux te
       |  en FATigue SINusoidale (implante en local ou nonlocal)
       |
       | 'RICRAG'  : Modele d'endommagement scalaire pour
       |  le beton (adapte aux cas de chargements monotones et
       |  cycliques alternes Ã  niveau modere de charge) pour les
       |  elements volumiques 2D/3D.
       |
       | 'GLRC_DM'  : ModÃ¨le d'endommagement scalaire pour le bÃ©ton armÃ©
       |  sous chargement cyclique. Ce modÃ¨le est formulÃ©
       |  en termes de contraintes et dÃ©formation gÃ©nÃ©ralisÃ©es.
       |  Il est implantÃ© pour des Ã©lÃ©ments de type coque. Il
       |  peut Ãªtre notÃ© qu'il n'y a pas de branche adoucissante
       |  Ainsi, aucun phÃ©nomÃ¨ne de localisation des dÃ©formation
       |  ne peut apparaÃ®tre, ce qui assure une indÃ©pendance Ã  l
       |  discrÃ©tisation.
       | 'EFEM'  : ModÃ¨le mettant permettant la mise en oeuvre de la
       |  mÃ©thode EFEM (Embeded Finite Element Method).
       |
       | 'RICBET'  : Modele d'endommagement visant Ã  dÃ©crire le comportemen
       |  du bÃ©ton sous chargement cyclique/sismique. Parmi ses po
       |  forts, on peut citer : la disymmÃ©trie traction/compressi
       |  les dÃ©formations permanentes en traction et en compressi
       |  les effets hystÃ©rÃ©tiques en traction en enfin, un effet
       |  unilatÃ©ral complet linÃ©aire. Elements volumique 3D.
       |
       | 'RICCOQ'  : ModÃ¨le d'endommagement simplifiÃ© rÃ©gularisÃ© par
       |  l'energie de fissuration. Il est prÃ©vu pour les Ã©lÃ©me
       |  coques. Sa formulation est simple et robuste.
       |
       | 'CONCYC'  : ModÃ¨le d'endommagement scalaire regularise soit en non
       |  local soit par une approche energetique (Hillerborg) adap
       |  aux chargements cycliques. Des enrichissement multi-axiau
       |  du critere de fissuration et de l'evolution de la
       |  fissuration peuvent etre activees. Le cisaillement peut e
       |  controle efficacement. Il prend en compte l effet unilate
       |  les deformations permamentes et les effets hysteretiques
       |  induites par friction.

PART{FLUAGE}
 * 'FLUAGE' suivi d'un mot choisi parmi :

       | 'NORTON'  : Modele de fluage de NORTON
       |
       | 'BLACKBURN'  : Modele de fluage de Blackburn
       |
       | 'RCCMR_316'  : Modele de fluage RCC-MR pour l'acier 316-SS
       |
       | 'RCCMR_304'  : Modele de fluage RCC-MR pour l'acier 304-SS
       |
       | 'LEMAITRE'  : Modele de fluage de Lemaitre
       |
       | 'POLYNOMIAL' : Modele de fluage de polynomial
       |
       | 'CERAMIQUE' : Modele de comportement des ceramiques
       |  Au dessus d'une temperature de transition
       |  le materiau flue selon la loi de Norton.
       |  Au dessous de cette temperature, il se comporte
       |  selon le modele d'Ottosen.
       |  la perte de rigidite des elements ayant subi en
       |  fluage une deformation totale superieure a une
       |  limite fixee peut aussi etre prise en compte.
       |
       | 'MAXWELL'  : Modele de Maxwell generalise. L modele possede
       |  4 branches obligatoires ( en plus de la branche
       |  purement elastique) et 4 branches facultatives.
       |
       | 'MAXOTT'  : Modele de comportement couplant le modele OTTOSEN
       |  pour le comportement fragile et le modele de
       |  MAXWELL pour le comportement de fluage.
       |
       | 'KELVIN' :  Modele de comportement pour le fluage propre du
       |  beton. Ce modele est base sur une chaÃ®ne de
       |  Kelvin-Voigt compose de 3 systemes en serie et
       |  de 1 ressort isole pour la partie purement
       |  elastique.

PART{PLASTIQUE_ENDOM}
 * 'PLASTIQUE_ENDOM' suivi d'un mot choisi parmi :

       | 'PSURY'  : modele d'endommagement P/Y
       |
       | 'ROUSSELIER': modele d'endommagement ductile de Rousselier
       |
       | 'GURSON2'  : modele d'endommagement ductile de Gurson
       |  modifie par Needleman et Tvergaard
       |
       | 'DRAGON'  : modele endommageable quasi-fragile de Dragon
       |
       | 'BETON_URGC': modele de beton
       |
       | 'BETON_INSA': modele de beton
       |
       | 'BETON_DYNAR_LMT' : modele de beton pour dynamique rapide
       |
       | 'ENDO_PLAS' : modele de beton plastique endommageable

PART{VISCOPLASTIQUE}
 * 'VISCOPLASTIQUE' suivi d'un mot choisi parmi :

       | 'CHABOCHE'  : Modele viscoplastique de Chaboche
       |
       | 'GUIONNET'  : Modele viscoplastique de Guionnet
       |
       | 'ONERA'  : Modele viscoplastique "unifie" de Chaboche
       |  (effets "memoire" de la def. plastique)
       |
       | 'OHNO'  : Modele viscoplastique de Ohno
       |  (ONERA-Chaboche modifie Ohno )
       |
       | 'VISCODOMMAGE' : Modele viscoplastique endommageable de
       |  Lemaitre et Chaboche
       |
       | 'PARFAIT'  : Modele viscoplastique parfait.
       |
       | 'POUDRE_A'  : Modele viscoplastique d'ABOUAF pour
       |  les poudres
       |
       | 'DDI'  : Modele a deux deformations inelastiques.
       |
       | 'KOCKS'  : Modele viscoplatique de KOCKS
       |
       | 'NOUAILHAS_A : Modele viscoplastique de Nouailhas
       |
       | 'NOUAILHAS_B : Modele viscoplastique de Chaboche
       |
       | 'VISK2' : Modele viscoplastique a 2 variables internes
       |  base sur le modele plastique a ecrouissage cinematique
       |
       | 'VISCOHINTE' : Il s'agit d'un modele de JOIN avec
       |  degradation jusqu'a la phase ultime de la
       |  rupture. Ce modele d'endommagement est
       |  dependant du temps. Il a comme support
       |  geometrique les elements RACCORD.
       |
       | 'MISTRAL' : Modele general de deformation MISTRAL. Ce modele
       |  requiert un comportement elastique orthotrope.
       |
       | 'GATT_MONERIE' : Modele viscoplastique de GATT_MONERIE pour
       |  le comportement du combustible UO2
       |
       | 'UO2': Modele couplant la viscoplasticite du combustible UO2
       |  decrite par le modele GATT_MONERIE et son comportement
       |  fragile en traction (apparition de fissuration fictive)
       |  decrit par le modele propose par OTTOSEN.
       |
       | 'VISCODD': Modele viscoplastique a ecrouissage isotrope
       |  avec deux variables dendommagements: une premiere
       |  ductile isotrope et une seconde de fluage anisotrope.
       |
       |  'SYCO1' : loi de 'SYMONDS & COWPER' standard (cf. MATE)
       |  'SYCO2' : loi de 'SYMONDS & COWPER' modifiee (cf. MATE)
       |  disponible pour les formulations 3D et 2D contraintes planes
       |  et deformations planes avec les elements massifs et XFEM.
       |
       | 'FLUENDO3D' : modele de fluage, couple a la plasticite et a l'endommagement.
       |  - Differentes pressions intra-poreuses peuvent etre envisagees : capillaire,
       |  reaction alcalis granulats (RAG) et formation d'ettringite differee (DEF).
       |  - Renforts repartis, qui peuvent glisser si le modele est utilise
       |  avec la procedure Helmholtz 'NON-LOCALE'.
       |  - Une repartition anisotrope des fibres peut etre consideree.
       |
       |'ENDO3D' : cf. modele FLUENDO3D sans la viscosite, sans RAG ni
       |  DEF, sans renforts ni fibres, mais avec un critere plastique
       |  de CamClay en supplement. les parametres peuvent dependre de la
       |  Temperature.
       |
       |'INCLUSION3D' : modele analytique d'homogeneisation base sur
       |  une cinematique micro-mecanique permettant d'envisager simultanement,
       |  elasticite, fluage et plasticite, avec des pressions interstitielles
       |  dans chaque phase induites par la capillarite et une reaction chimique

PART{VISCO_EXTERNE}
 * 'VISCO_EXTERNE' : comportement viscoplastique externe.
        Pas d'option par defaut.
        Doit etre suivi d'un mot choisi parmi :

       | 'GENERAL' : modele evaluant une deformation inelastique
       |  combinaison d'un terme de gonflement et d'un terme
       |  de fluage, a l'aide d'un critere general sur les
       |  contraintes (critere de Von Mises)
       |
       | 'DRUCKER_PRAGER' : Option non disponible pour le calcul
       |
       | 'COHESION' : Option non disponible pour le calcul
       |
       | 'CONSOLIDATION' : Option non disponible pour le calcul
       |
       | 'UTILISATEUR' : Option non disponible pour le calcul
       |
       |
       |  Commentaires :
       |  ------------
       |  Un numero ILOI1 ou un nom CLOI16 doit etre affecte a toute
       |  loi de comportement du groupe 'VISCO_EXTERNE'.
       |  La liste des parametres externes de la loi est donnee par
       |  l'objet LMOTS1 (le cas echeant).
       |  Les composantes de materiau sont les memes que celles du
       |  comportement 'ELASTIQUE' 'ISOTROPE'.
       |  Quatre variables internes pre-definies pour toutes les lois :
       |  - 'EC0 ' : deformation equivalente cumulee de fluage,
       |  - 'ESW0' : deformation equivalente cumulee de gonflement,
       |  - 'P  ' : 1er invariant du tenseur des contraintes
       |  = 1/3 trace (SIGMA),
       |  - 'QTLD' : contrainte equivalente de Von Mises
       |  = SQRT(3/2 S:S), avec S deviateur des contraintes.
       |  La liste des variables internes supplementaires est donnee par
       |  l'objet LMOTS3 (le cas echeant).
       |
       |  Les lois 'VISCO_EXTERNE' sont integrees par un schema general
       |  de type Runge-Kutta d'ordre 2. Le processus d'integration fait
       |  appel au module utilisateur CREEP pour le calcul de vitesses
       |  equivalentes de deformation de fluage et de gonflement.
       |  Etant donnes :
       |  - les deformations equivalentes cumulees EC0 et ESW0 au debut
       |  du pas ;
       |  - les variables internes caracterisant l'etat de contraintes
       |  P et QTLD, au debut OU a la fin du pas ;
       |  - les eventuelles variables internes supplementaires au debut
       |  du pas ;
       |  - un pas de temps dt ;
       |  - un indicateur de debut OU de fin du pas ;
       |  le module CREEP calcule :
       |  - deux increments de deformation equivalente de fluage et de
       |  gonflement : produits des vitesses de deformation (evaluees
       |  au debut OU en fin de pas) par le pas de temps dt ;
       |  - les valeurs des variables internes supplementaires en fin
       |  de pas, si la routine est appelee avec l'indicateur de fin
       |  du pas.
       |
       |  Mode operatoire :
       |  ---------------
       |  1 - Programmer le module externe CREEP et ses dependances :
       |  - Reprendre le module exemple integre au code.
       |  Il faut conserver imperativement la premiere carte du
       |  module exemple pour assurer le succes de la compilation.
       |  - Respecter l'interface d'appel de la routine.
       |  2 - Compiler le module externe et ses dependances, puis
       |  edition de liens avec le reste du code.
       |  3 - Mise en oeuvre en langage Gibiane en respectant la syntaxe
       |  decrite ci-dessus.
       |
       |----------------------------------------------------------------
       |  Interface du module externe CREEP :
       |  ---------------------------------
       |
       |  SUBROUTINE CREEP (DECRA,DESWA,STATEV,serd,EC0,ESW0,P,QTILD,
       | &  TEMP,DTEMP,PREDEF,DPRED,TIME,DTIME,
       | &  CMNAME,leximp,LEND,COORDS,NSTATV,NOEL,NPT,
       | &  layer,kspt,KSTEPC,KINC)
       |  IMPLICIT REAL*8(A-H,O-Z)
       |
       |
       |  CHARACTER*16  CMNAME
       |
       |  INTEGER  leximp, LEND, NSTATV, NOEL, NPT, layer, kspt,
       |  &  KSTEPC, KINC
       |
       |  REAL*8  DECRA(5), DESWA(5), STATEV(*),
       |  &  serd, EC0, ESW0, P, QTILD,
       |  &  TEMP,DTEMP, PREDEF(*),DPRED(*), TIME(2),DTIME,
       |  &  COORDS(*)
       |
       |----------------------------------------------------------------
       |  OUT  : DECRA  : REAL*8(5)
       |  DECRA(1) : increment scalaire de deformation
       |  de fluage, au debut du pas si LEND=0,
       |  a la fin du pas si LEND=1.
       |  Les composantes 2 a 5 ne sont pas exploitees
       |  dans le cas d'une adherence a CAST3M.
       |
       |  OUT  : DESWA  : REAL*8(5)
       |  DESWA(1) : increment scalaire de deformation
       |  de gonflement, au debut du pas si LEND=0,
       |  a la fin du pas si LEND=1.
       |  Les composantes 2 a 5 ne sont pas exploitees
       |  dans le cas d'une adherence a CAST3M.
       |
       |  Remarque : la routine CREEP evalue des VITESSES de deformation
       |  (fluage et gonflement) au debut ou a la fin du pas, suivant la
       |  valeur de LEND.
       |  Les increments DECRA(1) et DESWA(1) sont ensuite determines
       |  par les produits de ces vitesses par le pas de temps DTIME.
       |
       |  IN/OUT : STATEV : REAL*8(*),variables internes supplementaires
       |  Il s'agit des eventuelles variables internes
       |  s'ajoutant aux 4 pre-definies 'EC0 ','ESW0',
       |  'P  ' et 'QTLD'.
       |  Valeurs au debut du pas si LEND=0.
       |  Peuvent etre mises a jour si LEND=1: valeurs
       |  a la fin du pas.
       |
       |  IN/OUT : serd  : REAL*8, puissance volumique de deformation
       |  inelastique (produit contracte du tenseur
       |  des contraintes et du tenseur des vitesses
       |  de deformation inelastique).
       |  Entree/sortie facultative, non exploitee par
       |  CAST3M pour l'instant.
       |
       |  IN  : EC0  : REAL*8, deformation de fluage cumulee.
       |  1ere des 4 variables internes pre-definies.
       |  Valeur au debut du pas.
       |
       |  IN  : ESW0  : REAL*8, deformation de gonflement cumulee.
       |  2eme des 4 variables internes pre-definies.
       |  Valeur au debut du pas.
       |
       |  IN  : P  : REAL*8, 1er invariant du tenseur des
       |  contraintes = 1/3 trace(SIGMA)
       |  3eme des 4 variables internes pre-definies.
       |  Valeur au debut du pas si LEND=0, a la fin
       |  du pas si LEND=1.
       |
       |  IN  : QTILD  : REAL*8, contrainte equivalente de Von Mises
       |  = SQRT(3/2 S:S), S deviateur des contraintes
       |  4eme des 4 variables internes pre-definies.
       |  Valeur au debut du pas si LEND=0, a la fin
       |  du pas si LEND=1.
       |
       |  IN  : TEMP  : REAL*8, temperature a la fin du pas.
       |  DTEMP  : REAL*8, increment de temperature au cours du
       |  pas de temps.
       |  PREDEF : REAL*8(*), vecteur des parametres externes
       |  de la loi de comportement, valeurs a la fin
       |  du pas.
       |  DPRED  : REAL*8(*),increments des parametres externes
       |  au cours du pas de temps.
       |
       |  IN  : TIME  : REAL*8(2)
       |  TIME(1) : duree cumulee des iterations
       |  internes a la fin du pas en cours.
       |  TIME(2) : instant intermediaire absolu
       |  a la fin du pas en cours.
       |  DTIME  : REAL*8, valeur du pas de temps en cours.
       |
       |  Remarque : l'instant absolu correspondant a la precedente
       |  iteration interne convergee est TIME(2)-DTIME.
       |
       |  IN  : CMNAME : CHARACTER*16, identifiant de la loi de
       |  comportement.
       |  1) La loi est identifiee par le numero qui lui
       |  a ete attribue : ILOI1, mot cle 'NUME_LOI'
       |  Par convention, ce numero est encode dans
       |  les 4 derniers caracteres de la chaine,
       |  et doit etre recupere dans CREEP par une
       |  instruction du type
       |  K4ILOI = CMNAME(13:16)
       |  (K4ILOI variable locale de type CHARACTER*4)
       |  2) La loi est identifiee par le nom qui lui a
       |  a ete attribue : CLOI16, mot cle 'NOM_LOI'
       |  et peut etre recupere dans CREEP directement
       |  car CMNAME = CLOI16 (variable CHARACTER*16)
       |
       |  IN  : leximp : INTEGER
       |  Entree non active dans le cas d'une
       |  adherence a CAST3M.
       |
       |  IN  : LEND  : INTEGER, indicateur de debut/fin de pas.
       |  LEND=0 : les entrees P, QTILD sont definies
       |  au debut du pas ; les sorties DECRA(1),
       |  DESWA(1) sont calculees au debut du pas.
       |  LEND=1 : les entrees P, QTILD sont definies
       |  a la fin du pas ; les sorties DECRA(1),
       |  DESWA(1) sont calculees a la fin du pas.
       |
       |  IN  : COORDS : REAL*8(*), coordonnees cartesiennes du point
       |  d'integration courant.
       |
       |  IN  NSTATV : INTEGER, nombre de variables internes
       |  supplementaires (en plus des 4 pre-definies)
       |
       |  IN  : NOEL  : INTEGER, numero de l'element courant.
       |  Attention : numerotation locale (numero de
       |  l'element dans la sous-zone courante).
       |  NPT  : INTEGER, numero du point d'integration
       |  courant.
       |
       |  IN  : layer  : INTEGER
       |  kspt  : INTEGER
       |  Entrees non actives dans le cas d'une
       |  adherence a CAST3M.
       |
       |  IN/OUT : KSTEPC : INTEGER
       |  Entree n'ayant pas de sens dans le cas d'une
       |  adherence a CAST3M.
       |
       |  CONVENTION : on autorise la programmation de l'utilisateur a
       |  se servir de KSTEPC comme code retour. Regles a respecter :
       |  1. Pas d'initialisation superflue de KSTEPC en entrant dans
       |  CREEP. KSTEPC est initialise a 1 avant l'appel a CREEP.
       |  2. En cas d'erreur, KSTEPC est affecte d'une valeur
       |  differente de 1
       |
       |  IN  : KINC  : INTEGER, compteur d'iterations internes.
       |  Incrementation geree par l'appelant.
       |
       |----------------------------------------------------------------

PART{IMPEDANCE}
 * 'IMPEDANCE' , s'utilise pour pour un maillage support constitue de
        POI1 ou SEG2, suivi d'un mot choisi parmi :

       |'ELASTIQUE' : Comportement purement lineaire elastique
       |
       |'VOIGT'  : Comportement superposant un frein visqueux
       |  a une reponse de ressort lineaire
       |
       |'REUSS  : Comportement resultant de l'association en serie
       |  d'un frein visqueux et d'un ressort lineaire
       |
       |'COMPLEXE'  : Comportement restreint au calcul frequentiel,
       |  associant une partie elastique et un frein visqueux

       Il peut etre possible d'utiliser un autre materiau non-lineaire
       de cette notice (ex : 'PLASTIQUE' 'PARFAIT')

PART{Remarques}
  Remarques : * Actuellement, il n'est pas possible de cumuler
  _________ les comportements non lineaires

        * Actuellement, seul le comportement lineaire
        elastique isotrope peut etre utilise avec un
        comportement non lineaire, a l'exception du modele
        MISTRAL qui requiert un comportement elastique
        orthotrope.

CHAP{LIQUIDE & LIQUIDE MECANIQUE}
    | Noms des materiaux pour la formulation LIQUIDE |

 La seule donnee de la formulation est necessaire.

    | Noms des materiaux pour la formulation LIQUIDE  MECANIQUE |

 La seule donnee de la formulation est necessaire.

CHAP{POREUX}
    | Noms des materiaux pour la formulation POREUX |

 Le comportement lineaire doit d'abord etre defini, puis
 le comportement non lineaire, le cas echeant, selon les
 directives ci-dessous :

PART{Lineaire (ELASTIQUE)}
- Comportements lineaires :

 * 'ELASTIQUE' ('ISOTROPE')

- Comportements non lineaires :

PART{Non lineaire (PLASTIQUE)}
 * 'PLASTIQUE' suivi d'un mot choisi parmi :

       | ('ISOTROPE') : Modele de Von Mises ecrouissage isotrope.
       |
       | 'PARFAIT'  : Modele de Von Mises sans ecrouissage
       |
       | 'CINEMATIQUE'  : Modele de Von Mises ecrouissage
       |  cinematique lineaire.
       |
       | 'DRUCKER_PRAGER'  : Modele de Drucker-Prager a ecoulement
       |  non associe.
       |
       | 'DRUCKER_PARFAIT'  : Modele simplifie de Drucker-Prager
       |  (parfait)

CHAP{CONTACT}
    | Noms des materiaux pour la formulation CONTACT |

    Il faut donner les deux maillages entre lesquels imposer la
    condition de contact et eventuelement un mot-cle parmi :

       | 'SYME' : traitement symetrique du contact
       | 'MESC' : traitement non symetrique du contact (maitre/esclave)
       | 'FAIB' : formulation faible du contact ou la condition de
        non penetration est imposee en moyenne sur chaque
        element
       | 'MORT' : formulation mortar du contact ou les conditions de
        contact sont imposees entre elements des deux surfaces
        potentiellement en contact. Les multiplicateurs de
        Lagrange sont discretises par des fonctions de forme
        lineaires (seulement disponible en 2D).

    Par defaut, le traitement du contact est maitre-esclave (mot-cle MESC)
    La condition Maitre Esclave impose qu'aucun noeud du second maillage
    ne traverse un element du premier maillage.

    En 2D, les deux maillages doivent etre constitues d'elements de type
    SEG2. Ces lignes doivent etre orientees et la condition de contact est
    imposee sur leur droite.

        MAIL1
        >----->------>------>  /|\
        | DEP1
        <-----<------<------<  \|/
        MAIL2

    En 3D, les deux maillages doivent etre constitues d'elements de type
    TRI3. Ces surfaces doivent etre orientees et la condition de contact
    est ecrite selon la direction d'orientation.

PART{Sans frottement}
- Comportement sans frottement :

 * ('UNILATERAL') (pour l'instant, le seul disponible)

PART{Avec frottement}
- Comportements avec frottements :

 * 'FROTTANT' suivi d'un mot choisi parmi :

       |  'COULOMB'  :  frottement de coulomb entre deux lignes (2D)
       |  ou deux surfaces (3D).
       |
       |  'FROCABLE'  :  frottement de cables de precontraintes selon
       |  lois du BPEL99. Il faut en plus donner le
       |  modele des cables et le maillage du volume
       |  dans lequel les cables sont noyes.

CHAP{CONTRAINTE}
    | Noms des materiaux pour la formulation CONTRAINTE

    Il faut donner le maillage sur lesquel imposer la contrainte
    et un mot-cle parmi :

       | 'ROTATION'  : contrainte sur la rotation
        If faut alors indiquer un (2D) ou deux (3D) POINT definissant(s) l'axe de rotation
       | 'DEPLACEMENT' : contrainte sur le deplacement
        If faut alors indiquer un POINT definissant le vecteur du deplacementn
       | 'RELATION'  : contrainte sur une relation cinematique

CHAP{THERMIQUE}
    | Noms des materiaux en THERMIQUE |
       |  ('ISOTROPE')
       |  'ORTHOTROPE'
       |  'ANISOTROPE'

* Comportements
       |  'CONDUCTION'  C'est le comportement par defaut
       |
       |  'CONVECTION'  Convection entre deux surfaces ou entre milieu
       |  externe et paroi. Pour les coques il faut un des
       |  mots:
       |  'SUPERIEURE'
       |  'INFERIEURE'  suivant que l'Ã©change se fait par la
       |  face superieure ou inferieure de la coque
       |
       |  'RAYONNEMENT'  Echange thermique par rayonnement. suivi d'un des
       |  mots :
       |
       |  - 'INFINI'  rayonnement Ã  l'infini
       |  - 'FAC_A_FAC' rayonnement face Ã  face de deux surface
       |  suivi de :
       |  GEO1  surface 1
       |  GEO2  surface 2
       |  GEO3  maillage de seg2 reliant les
       |  points homologues de GEO1 et GEO2
       |  MOD1  modele "thermique convection"
       |  sur les elements raccords liant
       |  les deux faces
       |  - 'CAVITE'  rayonnement de la surface sur elle-meme
       |  suivi ou non des mots :
       |
       |  'CONVEXE' si la cavite est convexe
       |  'FERME'  si la cavite est ferme
       |  'SYMETRIQUE' en cas d'etude d'une partie
       |  symetrique de la cavite totale
       |  'FAC_FORME' si on veut utiliser la
       |  methode qui s'appuie sur le
       |  calcul des facteurs de formes
       |  'ABSO'  si le milieu est absorbant
       |
       |  Remarque : un modele de thermique rayonnement peut etre defini
       |  en plusieurs fois a condition de preciser le meme constituant
       |
       |  'PHASE'  En cas de changement de phase avec chaleur latente. Ce
       |  comportement est une extension non lineaire de la
       |  conduction
       |
       |  'ADVECTION'  Transport de chaleur par un champ de vitesse
       |
       |  'SOURCE'  Definition d'une source de chaleur appliquee sur le
       |  maillage fourni au modele. La formulation generale
       |  permet de definir une densite volumique de chaleur
       |  (voir MATE).
       |
       |  Deux distributions spatiales specifiques sont egalement
       |  disponibles :
       |  - 'GAUSSIENNE' 'ISOTROPE'
       |  - 'GAUSSIENNE' 'ISOTROPE_TRANSVERSE'
       |
       |  Remarque : les modeles de source GAUSSIENNE ne sont disponibles
       |  que pour les elements massifs en dimension 2 et 3.

CHAP{CHANGEMENT_PHASE}
    | Noms des materiaux en CHANGEMENT_PHASE |
       |  'PARFAIT'
       | Remarque : Les variables primales et duales impactees sont a
       |  fournir obligatoirement a 'MODE'.
       |  ex : pour un changement de phase thermique :
       |  MOD1 = ... 'INCO' 'T' 'Q' ... ;

       |  'SOLUBILITE'
       | Remarque : Les 2 inconnues primales et 2 duales impactees sont a
       |  fournir obligatoirement a 'MODE'.
       |  ex : pour une solubilite liquide gaz en diffusion :
       |  MOD1 = ... 'INCO' 'CL' 'CGA' 'QL' 'QGA' ... ;

CHAP{METALLURGIE}
    | Noms des materiaux en METALLURGIE |
   Deux types de transformations sont disponibles pour les transformations
   metallurgiques :
   1- Type KOISTINEN-MARBURGER (Acta Metallurgica, Vol.7, Issue 1,
      January 1959, pp.59-60)
   2- Type LEBLOND-DEVAUX (Acta Metallurgica, Vol.32, Issue 1,
      January 1984, pp.137-146)

   Pour definir les transformations, quatre objets sont a fournir en plus
   a l'operateur MODE :
   'PHASES' : (LISTMOTS) liste des phases en presence
   'REACTIFS': (LISTMOTS) liste des reactifs pour chaque transformation
   'PRODUITS': (LISTMOTS) liste des produits pour chaque transformation
   'TYPE'  : (LISTMOTS) type de chacune des reactions | 'KOIS'
        | 'LEBL'

CHAP{DARCY}
    | Noms des materiaux en DARCY |
       | ('ISOTROPE')
       | 'ORTHOTROPE'
       | 'ANISOTROPE'

CHAP{MAGNETODYNAMIQUE}
    | Noms des materiaux en MAGNETODYNAMIQUE |

 La seule formulation actuellement disponible est
 la formulation en coques minces 'POTENTIEL_VECTEUR' (option
 par defaut).

  syntaxe :

  * 'POTENTIEL_VECTEUR'  | ('ISOTROPE')  (option par defaut)
        | 'ORTHOTROPE'

CHAP{NAVIER_STOKES, EULER}
    | Noms des materiaux pour la formulation NAVIER_STOKES |

 La seule donnee de la formulation est necessaire.

    | Noms des materiaux pour la formulation EULER  |

 La seule donnee de la formulation est necessaire.

CHAP{MELANGE}
    | Noms des materiaux pour la formulation MELANGE  |

   'CEREM' : modele de transition de phase du 16MND5

   'PARALLELE' : modele de combinaison lineaire de modeles
    elemntaires munis de noms de phases.

   'ZTMAX' : modele de changement d'etat avec transition. Par
    defaut la variable d'etat est la temperature.

CHAP{FISSURE}
    | Noms des materiaux pour la formulation FISSURE  |

     | ('PARF')  | ('MASS')  | ('POISEU_BLASIUS')
     | ('REEL')  | ('FILM')  | ('POISEU_COLEBROOK')
        | ('FROTTEMENT1')
        | ('FROTTEMENT2')
        | ('FROTTEMENT3')
        | ('FROTTEMENT4')

    * choix de la loi de comportement pour la vapeur d'eau
     | 'PARF' : gaz parfait
     | 'REEL' : gaz reel
    * choix du modele de condensation
     | 'MASS' : condensation en masse (la vapeur condensee est
     transportee par le fluide)
     | 'FILM' : condensation en film (la vapeur condensee est
     transportee par le fluide.
     condensation en masse (mot-cle MASS): la vapeur condensee forme
     un film qui adhere a la paroi, dont l'epaisseur ne modifie pas
     l'ouverture de la fissure.
    * choix de la loi de frottement
     | ('POISEU_BLASIUS')  : ecoulement dans un canal rectangulaire lisse
     | ('POISEU_COLEBROOK') : ecoulement dans un canal rectangulaire rugueux
     | ('FROTTEMENTi') : loi a coefficients choisis par l'utilisateur
    *les valeurs par defaut sont : PARF MASS POISEU_BLASIUS

CHAP{THERMOHYDRIQUE}
    | Noms des materiaux pour la formulation THERMOHYDRIQUE |

   'SCHREFLER' : modele de couplage thermohydrique pour milieux poreux
        insatures constitues de 4 phases : solide poreux, eau
        liquide, eau vapeur et air sec.

CHAP{LIAISON}
    | Noms des materiaux pour la formulation LIAISON  |

   La base A est formee a partir d'un ensemble de deformees
   (par exemple modes propres ou modes statiques) ; la base B est
   celle des elements finis.

   - Liaisons compatibles avec PASAPAS et DYNE (voir notice DYNE)

  'POINT_PLAN' 'FLUIDE' : s'exprime en base A et base B

  'POINT_PLAN' 'FROTTEMENT' : base B

  'POINT_PLAN' : base A et base B

  'POINT_POINT' 'FROTTEMENT' : base B

  'POINT_POINT' 'DEPLACEMENT_PLASTIQUE' : base B

  'POINT_POINT' 'ROTATION_PLASTIQUE' : base B

  'POINT_POINT' : base B

  'POINT_CERCLE' 'MOBILE' : base B

  'POINT_CERCLE' 'FROTTEMENT' : base B

  'POINT_CERCLE' : base B

  'CERCLE_PLAN' 'FROTTEMENT' : base B

  'CERCLE_CERCLE' 'FROTTEMENT' : base B

  'PROFIL_PROFIL' 'INTERIEUR' : base B

  'PROFIL_PROFIL' 'EXTERIEUR' : base B

  'LIGNE_LIGNE' 'FROTTEMENT' : base B

  'LIGNE_CERCLE' 'FROTTEMENT' : base B

  'PALIER_FLUIDE' 'RHODE_LI' : base B

  'COUPLAGE' 'DEPLACEMENT' : base A

  'COUPLAGE' 'VITESSE' : base A

  'POLYNOMIALE' : base A

  - Liaison compatible uniquement avec PASAPAS

  'NEWMARK' 'MODAL' : base A

CHAP{DIFFUSION}
    | Noms des materiaux pour la formulation DIFFUSION |
       |  ('ISOTROPE')
       |  'ORTHOTROPE'
       |  'ANISOTROPE'

* Comportements
       |  'FICK'  Loi de Fick (J = -D.grad(C)), modele par defaut.

* Comportements additionnel :
       |  'ADVECTION'  Transport de matiere par un champ de vitesse
       |  (J = C.V)

CHAP{CHARGEMENT}
    | Noms des materiaux pour la formulation CHARGEMENT |

   'PRESSION' : dÃ©finit un modele de chargement de pression.
        GEO1 est un maillage de surface.

    Remarques :
      La surface GEO1 doit etre orientee (voir INVE et ORIE).

CHAP{Tableau des elements disponibles par formulation}

    Les tableaux qui suivent indiquent, pour chaque formulation,quels
 sont les elements finis disponibles, associes a un support geometrique
 donne, le(s) degre(s) de leurs fonctions d'interpolation, les options
 de calcul dans lesquelles ils sont utilisables (voir OPTI) ainsi que
 les inconnues nodales correspondantes.

PART{MECANIQUE}
 |  Elements finis en formulation MECANIQUE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  POI1  |  POI1  |  point  |  | PLAN GENE | UX UY  |
 |  |  |  |  |cf Remarque| UZ RX RY  |
 |  |-----------------------------------------------------|
 |  |  CERC  |  cerce  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  POJS  | element de  |  | PLAN  |  |
 |  |  |  section  |  | TRID  |  |
 |  |  | de poutre  |  |  |  |
 |  SEG2  |  BARR  |  barre  |  1  | PLAN CONT | UX UY  |
 |  |  |  |  | PLAN DEFO | UX UY  |
 |  |  |  armature  |  | TRID  | UX UY UZ  |
 |  |------------------------------------------------------
 |  |  BAEX  |  barre  |  1  | PLAN CONT | UX UY  |
 |  |  | excentree  |  | PLAN DEFO | UX UY  |
 |  |  |  |  | TRID  | UX UY UZ  |
 |  |------------------------------------------------------
 |  | (M1D2)  | massif (1D) |  1  | UNID PLAN | UX  |
 |  |  |  2 noeuds  |  | UNID AXIS | UR  |
 |  |  |  |  | UNID SPHE | UR  |
 |  |------------------------------------------------------
 |  |  COQ2  | coque mince |  1  | PLAN CONT | UX UY RZ  |
 |  |  |  |  | PLAN DEFO | UX UY RZ  |
 |  |  |  |  et | PLAN GENE | UX UY RZ  |
 |  |  |  |  |cf Remarque| UZ RX RY  |
 |  |  |  |  3  | AXIS  | UR UZ RT  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |  |  |  |  | RT  |
 |  |------------------------------------------------------
 |  |  POUT  |  poutre  |  1  | TRID  | UX UY UZ  |
 |  |  |  |  et |  | RX RY RZ  |
 |  |  |  |  3  | PLAN CONT | UX UY RZ  |
 |  |  |  |  | PLAN DEFO | UX UY RZ  |
 |  |------------------------------------------------------
 |  |  TIMO  |  poutre  |  1  | TRID  | UX UY UZ  |
 |  |  |  de  |  |  | RX RY RZ  |
 |  |  | Timoschenko |  | PLAN CONT | UX UY RZ  |
 |  |  |  |  | PLAN DEFO | UX UY RZ  |
 |  |------------------------------------------------------
 |  |  TUYA  | tuyau droit |  1  | TRID  | UX UY UZ  |
 |  |  |  et  |  et |  | RX RY RZ  |
 |  |  |  coude  |  3  |  |  |
 |  |------------------------------------------------------
 |  |  TUFI  |  tuyau  |  | TRID  | UX UY UZ  |
 |  |  |  fissure  |  |  | RX RY RZ  |
 |  |------------------------------------------------------
 |  |  JOI1  | joint  |  0  | TRID  | UX UY UZ  |
 |  |  | unidimen-  |  |  | RX RY RZ  |
 |  |  | sionnel a  |  | PLAN CONT | UX UY RZ  |
 |  |  | deux noeuds |  | PLAN DEFO | UX UY RZ  |
 |  SEG3  |  BAR3  |  barre  |  2  |  TRID  | UX UY UZ  |
 |  |------------------------------------------------------
 |  | (M1D3)  | massif (1D) |  2  | UNID PLAN | UX  |
 |  |  |  3 noeuds  |  | UNID AXIS | UR  |
 |  |  |  |  | UNID SPHE | UR  |
 |  TRI3  | (TRI3)  |  triangle  |  1  | PLAN CONT | UX UY  |
 |  |  |  a 3 noeuds |  | PLAN DEFO | UX UY  |
 |  |  |  |  | PLAN GENE | UX UY  |
 |  |  |  massif  |  |cf Remarque| UZ RX RY  |
 |  |  |  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  ICT3  |  triangle  |  1  | PLAN CONT | UX UY  |
 |  |  |  a 3 noeuds |  | PLAN DEFO | UX UY  |
 |  |  |incompressib.|  | AXIS  | UR UZ  |
 |  |------------------------------------------------------
 |  |  COQ3  | coque mince |  1  | TRID  | UX UY UZ  |
 |  |  |  polynome  |  et |  | RX RY RZ  |
 |  |  | incomplet  |  3  |  |  |
 |  |  | en flexion  |  |  |  |
 |  |------------------------------------------------------
 |  |  DKT  | coque mince |  1  | TRID  | UX UY UZ  |
 |  |  | hypothese de|  et |  | RX RY RZ  |
 |  |  |  Kirchhoff  |  3  |  |  |
 |  |  |  discrete  |  |  |  |
 |  |------------------------------------------------------
 |  |  DST  | coque avec  |  1  | TRID  | UX UY UZ  |
 |  |  | cisaillement|  et |  | RX RY RZ  |
 |  |  | transverse  |  3  |  |  |
 |  |------------------------------------------------------
 |  |  TRIH  | element  |  | PLAN CONT | P PI UX UY|
 |  |  | homogeneise |  | PLAN DEFO | P PI UX UY|
 |  |  |  |  | AXIS  | P PI UR RT|
 |  |  |  |  | FOUR  | P PI UR UT|
 |  |  |  |  |  | RR RT  |
 |  |------------------------------------------------------
 |  |  TRIS  | element de  |  1  | PLAN  |  |
 |  |  |  section  |  | TRID  |  |
 |  |  | de poutre  |  |  |  |
 |  QUA4  | (QUA4)  | quadrangle  |  1  | PLAN CONT | UX UY  |
 |  |  | a 4 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  |  |  | PLAN GENE | UX UY  |
 |  |  |  massif  |  |cf Remarque| UZ RX RY  |
 |  |  |  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  Q4RI  | quadrangle  |  1 | PLAN CONT | UX UY  |
 |  |  | a 4 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  | et 1x1  |  | PLAN GENE | UX UY  |
 |  |  | point de  |  |cf Remarque| UZ RX RY  |
 |  |  | Gauss  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  ICQ4  | quadrangle  |  1  | PLAN CONT | UX UY  |
 |  |  | a 4 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  |incompressib.|  | AXIS  | UR UZ  |
 |  |------------------------------------------------------
 |  |  COQ4  | coque mince |  1  | TRID  | UX UY UZ  |
 |  |  |  avec  |  |  | RX RY RZ  |
 |  |  | cisaillement|  |  |  |
 |  |  | transverse  |  |  |  |
 |  |------------------------------------------------------
 |  |  QUAS  | element de  |  1  | PLAN  |  |
 |  |  |  section  |  | TRID  |  |
 |  |  | de poutre  |  |  |  |
 |  |------------------------------------------------------
 |  |  QUAH  | element  |  | AXIS  | P PI UR RT|
 |  |  | homogeneise |  | FOUR  | P PI UR UT|
 |  |  |  |  |  | RR RT  |
 |  TRI6  | (TRI6)  |  triangle  |  2  | PLAN CONT | UX UY  |
 |  |  |  a 6 noeuds |  | PLAN DEFO | UX UY  |
 |  |  |  |  | PLAN GENE | UX UY  |
 |  |  |  massif  |  |cf Remarque| UZ RX RY  |
 |  |  |  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  ICT6  |  triangle  |  2  | PLAN CONT | UX UY  |
 |  |  |  a 6 noeuds |  | PLAN DEFO | UX UY  |
 |  |  |incompressib.|  | AXIS  | UR UZ  |
 |  |------------------------------------------------------
 |  |  COQ6  |  coque  |  2  | TRID  | UX UY UZ  |
 |  |  |  epaisse  |  |  | RX RY RZ  |
 |  |------------------------------------------------------
 |  |  TRH6  | element  |  2  | PLAN CONT | P PI UX UY|
 |  |  | homogeneise |  | PLAN DEFO | P PI UX UY|
 |  QUA8  | (QUA8)  | quadrangle  |  2  | PLAN CONT | UX UY  |
 |  |  | a 8 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  |  |  | PLAN GENE | UX UY  |
 |  |  |  massif  |  |cf Remarque| UZ RX RY  |
 |  |  |  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  Q8RI  | quadrangle  |  2 | PLAN CONT | UX UY  |
 |  |  | a 8 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  | et 2x2  |  | PLAN GENE | UX UY  |
 |  |  | points de  |  |cf Remarque| UZ RX RY  |
 |  |  | Gauss  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  |------------------------------------------------------
 |  |  ICQ8  | quadrangle  |  2  | PLAN CONT | UX UY  |
 |  |  | a 8 noeuds  |  | PLAN DEFO | UX UY  |
 |  |  |incompressib.|  | AXIS  | UR UZ  |
 |  |------------------------------------------------------
 |  |  COQ8  |  coque  |  2  | TRID  | UX UY UZ  |
 |  |  |  epaisse  |  |  | RX RY RZ  |
 |  POLY  |  POLY  | Polygone  |  1  | PLAN CONT | UX UY  |
 |  |  |meme nombre  |  | PLAN DEFO | UX UY  |
 |  |  |de noeuds  |  | PLAN GENE | UX UY  |
 |  |  |que de cotes |  |cf Remarque| UZ RX RY  |
 |  |  |  massif  |  | AXIS  | UR UZ  |
 |  |  |  |  | FOUR  | UR UZ UT  |
 |  CUB8  | (CUB8)  |  cube  |  1  | TRID  | UX UY UZ  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  CUBH  | element  |  | TRID  | P PI UX RY|
 |  |  | homogeneise |  |  |  UY RX|
 |  |------------------------------------------------------
 |  |  SHB8  | element de  | 1  | TRID  | UX UY UZ  |
 |  |  | coque  |  |  |  |
 |  |  |  |  |  |  |
 |  |------------------------------------------------------
 |  |  ICC8  |incompressib.|  1  | TRID  | UX UY UZ  |
 |  TET4  | (TET4)  |  tetraedre |  1  | TRID  | UX UY UZ  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  ICT4  |incompressib.|  1  | TRID  | UX UY UZ  |
 |  PRI6  | (PRI6)  |  prisme  |  1  | TRID  | UX UY UZ  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  ICP6  |incompressib.|  1  | TRID  | UX UY UZ  |
 |  PYR5  | (PYR5)  |  pyramide  |  1  | TRID  | UX UY UZ  |
 |  |  |  a 5 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  ICY5  |incompressib.|  1  | TRID  | UX UY UZ  |
 |  CU20  | (CU20)  |  cube  |  2  | TRID  | UX UY UZ  |
 |  |  | a 20 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  C20R  |  cube  |  2  | TRID  | UX UY UZ  |
 |  |  | a 20 noeuds |  |  |  |
 |  |  |  massif et  |  |  |  |
 |  |  |  2x2x2  |  |  |  |
 |  |  |  points de  |  |  |  |
 |  |  |  Gauss  |  |  |  |
 |  |------------------------------------------------------
 |  |  IC20  |incompressib.|  2  | TRID  | UX UY UZ  |
 |  TE10  | (TE10)  |  tetraedre |  2  | TRID  | UX UY UZ  |
 |  |  | a 10 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  IC10  |incompressib.|  2  | TRID  | UX UY UZ  |
 |  PR15  | (PR15)  |  prisme  |  2  | TRID  | UX UY UZ  |
 |  |  | a 15 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  P15R  |  prisme  |  2  | TRID  | UX UY UZ  |
 |  |  | a 15 noeuds |  |  |  |
 |  |  |  massif et  |  |  |  |
 |  |  | 3x2 points  |  |  |  |
 |  |  |  de Gauss  |  |  |  |
 |  |------------------------------------------------------
 |  |  IC15  |incompressib.|  2  | TRID  | UX UY UZ  |
 |  PY13  | (PY13)  |  pyramide  |  2  | TRID  | UX UY UZ  |
 |  |  | a 13 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  IC13  |incompressib.|  2  | TRID  | UX UY UZ  |
 |  RAC2  |  LISP  |  element  |  | TRID  | UX UY UZ  |
 |  |  | linespring  |  |  | RX RY RZ  |
 |  |------------------------------------------------------
 |  |  LISM  |  element  |  | TRID  | UX UY UZ  |
 |  |  | linespring  |  |  | RX RY RZ  |
 |  |  |  modifie  |  |  |  |
 |  |------------------------------------------------------
 |  |  JOI2  |  element  |  1  | PLAN DEFO | UX UY  |
 |  |  |  joint a  |  | PLAN CONT | UX UY  |
 |  |  |  4 noeuds  |  | AXIS  | UR UZ  |
 |  |------------------------------------------------------
 |  |  COA2  |  element  |  1  | PLAN DEFO | UX UY  |
 |  |  |  coaxial a  |  | PLAN CONT | UX UY  |
 |  |  COS2  |  4 noeuds  |  | TRID  | UX UY UZ  |
 |  RAC3  |  JOI3  |  element  |  2  | PLAN DEFO | UX UY  |
 |  |  |  joint a  |  | PLAN CONT | UX UY  |
 |  |  |  6 noeuds  |  | AXIS  | UR UZ  |
 |  LIA3  |  JOT3  |  element  |  1  | TRID  | UX UY UZ  |
 |  |  |  joint a  |  |  |  |
 |  |  |  6 noeuds  |  |  |  |
 |  LIA4  |  JOI4  |  element  |  1  | TRID  | UX UY UZ  |
 |  |  |  joint a  |  |  |  |
 |  |  |  8 noeuds  |  |  |  |

PART{FLUIDE}
 |  Elements finis en formulation FLUIDE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |------------------------------------------------------------------|
 |  SEG2  |  LSE2  |  element  |  1  | TRID  | P PI  |
 |  |  |  tuyau  |  |  |  |
 |  |  | acoustique  |  |  |  |
 |  |  |  pure  |  |  |  |
 |  |------------------------------------------------------
 |  |  LSU2  | element de  |  1  | PLAN CONT | P  PI UZ  |
 |  |  |  surface  |  | PLAN DEFO | P  PI UZ  |
 |  |  |  libre  |  | AXIS  | P  PI UZ  |
 |  |  |  |  | FOUR  | P  PI UZ  |
 |  TRI3  |  LTR3  |  triangle  |  1  | PLAN CONT | P  PI  |
 |  |  | a 3 noeuds  |  | PLAN DEFO | P  PI  |
 |  |  |  massif  |  | AXIS  | P  PI  |
 |  |  |  |  | FOUR  | P  PI  |
 |  |------------------------------------------------------
 |  |  LSU3  | element de  |  1  | TRID  | P  PI UZ  |
 |  |  |  surface  |  |  |  |
 |  |  |  libre  |  |  |  |
 |  QUA4  |  LQU4  | quadrangle  |  1  | PLAN CONT | P  PI  |
 |  |  | a 4 noeuds  |  | PLAN DEFO | P  PI  |
 |  |  |  massif  |  | AXIS  | P  PI  |
 |  |  |  |  | FOUR  | P  PI  |
 |  |------------------------------------------------------
 |  |  LSU4  | element de  |  1  | TRID  | P  PI UZ  |
 |  |  |  surface  |  |  |  |
 |  |  |  libre  |  |  |  |
 |  CUB8  |  LCU8  |  cube  |  1  | TRID  | P  PI  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TET4  |  LTE4  |  tetraedre |  1  | TRID  | P  PI  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PRI6  |  LPR6  |  prisme  |  1  | TRID  | P  PI  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PYR5  |  LPY5  |  pyramide  |  1  | TRID  | P  PI  |
 |  |  |  a 5 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |

PART{FLUIDE MECANIQUE}
 |  Elements finis en formulation FLUIDE  MECANIQUE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  |  LITU  |  raccord  |  1  | TRID  | P PI UX UY|
 |  |  |  liquide  |  |  | UZ  |
 |  |  |  tuyau  |  |  |  |
 |  RAC2  | (RAC2)  |  raccord  |  1  | PLAN CONT | P PI UX UY|
 |  |  |  liquide  |  | PLAN DEFO | P PI UX UY|
 |  |  |  massif  |  | AXIS  | P PI UR UZ|
 |  |  |  |  | FOUR  | P PI UR UZ|
 |  |------------------------------------------------------
 |  |  RACO  |  raccord  |  3  | PLAN CONT | P PI UX UY|
 |  |  |  liquide  |  |  | RZ  |
 |  |  |  coque  |  | PLAN DEFO | P PI UX UY|
 |  |  |  |  |  | RZ  |
 |  |  |  |  | AXIS  | P PI UR UZ|
 |  |  |  |  |  | RT  |
 |  |  |  |  | FOUR  | P PI UR UZ|
 |  |  |  |  |  | RT  |
 |  LIA3  | (LIA3)  |  raccord  |  1  | TRID  | P  PI  |
 |  |  |  liquide  |  |  | UX UY UZ  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  LICO  |  raccord  |  3  | TRID  | P  PI  |
 |  |  |  liquide  |  |  | UX UY UZ  |
 |  |  |  coque  |  |  | RX RY RZ  |
 |  LIA4  | (LIA4)  |  raccord  |  1  | TRID  | P  PI  |
 |  |  |  liquide  |  |  | UX UY UZ  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  LIC4  |  raccord  |  3  | TRID  | P  PI  |
 |  |  |  liquide  |  |  | UX UY UZ  |
 |  |  |  coque  |  |  | RX RY RZ  |

PART{POREUX}
 |  Elements finis en formulation POREUX  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  TRI6  | (TRIP)  |  triangle  |  2  | PLAN CONT | UX UY P  |
 |  |  |  a 6 noeuds |  et | PLAN DEFO | UX UY P  |
 |  |  |  massif  |  1  | AXIS  | UR UZ P  |
 |  QUA8  | (QUAP)  | quadrangle  |  2  | PLAN CONT | UX UY P  |
 |  |  | a 8 noeuds  |  et | PLAN DEFO | UX UY P  |
 |  |  |  massif  |  1  | AXIS  | UR UZ P  |
 |  CU20  | (CUBP)  |  cube  |  2  | TRID  | UX UY UZ  |
 |  |  | a 20 noeuds |  et |  | P  |
 |  |  |  massif  |  1  |  |  |
 |  TE10  | (TETP)  |  tetraedre |  2  | TRID  | UX UY UZ  |
 |  |  | a 10 noeuds |  et |  | P  |
 |  |  |  massif  |  1  |  |  |
 |  PR15  | (PRIP)  |  prisme  |  2  | TRID  | UX UY UZ  |
 |  |  | a 15 noeuds |  et |  | P  |
 |  |  |  massif  |  1  |  |  |
 |  RAP3  | (JOP3)  |  element  |  2  | PLAN CONT | UX UY P  |
 |  |  |  joint a  |  et | PLAN DEFO | UX UY P  |
 |  |  |  8 noeuds  |  1  | AXIS  | UR UZ P  |
 |  LIP6  | (JOP6)  |  element  |  2  | TRID  | UX UY UZ  |
 |  |  |  joint a  |  et |  | P  |
 |  |  |  15 noeuds  |  1  |  |  |
 |  LIP8  | (JOP8)  |  element  |  2  | TRID  | UX UY UZ  |
 |  |  |  joint a  |  et |  | P  |
 |  |  |  20 noeuds  |  1  |  |  |

PART{THERMIQUE CONDUCTION, PHASE ou SOURCE}
 |  Elements finis en THERMIQUE, pour les formulations :  |
 |  CONDUCTION, PHASE ou SOURCE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  |  JOI1  |  joint  |  1  | PLAN  | T  |
 |  |  |  |  | TRID  | T  |
 |  |------------------------------------------------------
 |  |  BARR  |  barre  |  1  | PLAN  | T  |
 |  |  |  |  | TRID  | T  |
 |  |------------------------------------------------------
 |  | (T1D2)  | massif (1D) |  1  | UNID PLAN | T  |
 |  |  |  2 noeuds  |  | UNID AXIS | T  |
 |  |  |  |  | UNID SPHE | T  |
 |  |------------------------------------------------------
 |  |  COQ2  | coque mince |  1  | PLAN  | T TSUP  |
 |  |  |  variation  |  |  |  TINF  |
 |  |  | parabolique |  | AXIS  | T TSUP  |
 |  |  |  dans  |  |  |  TINF  |
 |  |  | l'epaisseur |  |  |  |
 |  SEG3  | (T1D3)  | massif (1D) |  1  | UNID PLAN | T  |
 |  |  |  3 noeuds  |  | UNID AXIS | T  |
 |  |  |  |  | UNID SPHE | T  |
 |  TRI3  | (TRI3)  |  triangle  |  1  | PLAN  | T  |
 |  |  |  a 3 noeuds |  | AXIS  | T  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ3  | coque mince |  1  | TRID  | T TSUP  |
 |  |  |  variation  |  |  |  TINF  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  QUA4  | (QUA4)  | quadrangle  |  1  | PLAN  | T  |
 |  |  | a 4 noeuds  |  | AXIS  | T  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ4  | coque mince |  1  | TRID  | T TSUP  |
 |  |  |  variation  |  |  |  TINF  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  TRI6  | (TRI6)  |  triangle  |  2  | PLAN  | T  |
 |  |  |  a 6 noeuds |  | AXIS  | T  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ6  |  coque  |  2  | TRID  | T TSUP  |
 |  |  |  epaisse  |  |  |  TINF  |
 |  |  |  variation  |  |  |  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  QUA8  | (QUA8)  | quadrangle  |  2  | PLAN  | T  |
 |  |  | a 8 noeuds  |  | AXIS  | T  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ8  |  coque  |  2  | TRID  | T TSUP  |
 |  |  |  epaisse  |  |  |  TINF  |
 |  |  |  variation  |  |  |  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  CUB8  | (CUB8)  |  cube  |  1  | TRID  | T  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TET4  | (TET4)  |  tetraedre |  1  | TRID  | T  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PRI6  | (PRI6)  |  prisme  |  1  | TRID  | T  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PYR5  | (PYR5)  |  pyramide  |  1  | TRID  | T  |
 |  |  |  a 5 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  CU20  | (CU20)  |  cube  |  2  | TRID  | T  |
 |  |  | a 20 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TE10  | (TE10)  |  tetraedre |  2  | TRID  | T  |
 |  |  | a 10 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PR15  | (PR15)  |  prisme  |  2  | TRID  | T  |
 |  |  | a 15 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PY13  | (PY13)  |  pyramide  |  2  | TRID  | T  |
 |  |  | a 13 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |

PART{THERMIQUE CONVECTION}
 |  Elements finis en formulation THERMIQUE CONVECTION  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  POI1  | (POI1)  | element 0D  |  1  | UNID PLAN | T  |
 |  |  | capacite  |  | UNID AXIS | T  |
 |  |  | pour massif |  | UNID SPHE | T  |
 |  SEG2  | (SEG2)  |  element  |  1  | PLAN  | T  |
 |  |  | d'echange  |  | AXIS  | T  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ2  |  element  |  1  | AXIS  |  TSUP  |
 |  |  | d'echange  |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  |------------------------------------------------------
 |  | (SEG2)  | element 1D  |  1  | UNID PLAN | T  |
 |  |  | d'echange  |  | UNID AXIS | T  |
 |  |  | face a face |  | UNID SPHE | T  |
 |  |  | a 1x1 noeuds|  |  |  |
 |  SEG3  | (SEG3)  |  element  |  2  | PLAN  | T  |
 |  |  | d'echange  |  | AXIS  | T  |
 |  |  | pour massif |  |  |  |
 |  TRI3  | (TRI3)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ3  |  element  |  1  | TRID  |  TSUP  |
 |  |  | d'echange  |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  QUA4  | (QUA4)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ4  |  element  |  1  | TRID  |  TSUP  |
 |  |  | d'echange  |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  TRI6  | (TRI6)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ6  |  element  |  2  | TRID  |  TSUP  |
 |  |  | d'echange  |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  QUA8  | (QUA8)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ8  |  element  |  2  | TRID  |  TSUP  |
 |  |  | d'echange  |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  RAC2  | (RAC2)  |  element  |  1  | PLAN  | T  |
 |  |  | d'echange  |  | AXIS  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x2 noeuds|  |  |  |
 |  RAC3  | (RAC3)  |  element  |  2  | PLAN  | T  |
 |  |  | d'echange  |  | AXIS  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x3 noeuds|  |  |  |
 |  LIA3  | (LIA3)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x3 noeuds|  |  |  |
 |  LIA4  | (LIA4)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x4 noeuds|  |  |  |
 |  LIA6  | (LIA6)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x6 noeuds|  |  |  |
 |  LIA8  | (LIA8)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x8 noeuds|  |  |  |

PART{THERMIQUE RAYONNEMENT}
 |  Elements finis en formulation THERMIQUE  RAYONNEMENT  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  | (SEG2)  |  element de |  1  | PLAN  | T  |
 |  |  | rayonnement |  | AXIS  | T  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ2  |  element de |  1  | AXIS  |  TSUP  |
 |  |  | rayonnement |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  SEG3  | (SEG3)  |  element de |  2  | PLAN  | T  |
 |  |  | rayonnement |  | AXIS  | T  |
 |  |  | pour massif |  |  |  |
 |  TRI3  | (TRI3)  |  element de |  1  | TRID  | T  |
 |  |  | rayonnement |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ3  |  element de |  1  | TRID  |  TSUP  |
 |  |  | rayonnement |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  QUA4  | (QUA4)  |  element de |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | rayonnement |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ4  |  element de |  1  | TRID  |  TSUP  |
 |  |  | rayonnement |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  TRI6  | (TRI6)  |  element de |  2  | TRID  | T  |
 |  |  | rayonnement |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ6  |  element de |  2  | TRID  |  TSUP  |
 |  |  | rayonnement |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  QUA8  | (QUA8)  |  element de |  2  | TRID  | T  |
 |  |  | rayonnement |  |  |  |
 |  |  | pour massif |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ8  |  element de |  2  | TRID  |  TSUP  |
 |  |  | rayonnement |  |  |ou TINF  |
 |  |  | pour coque  |  |  |  |
 |  RAC2  | (RAC2)  |  element de |  1  | PLAN  | T  |
 |  |  | rayonnement |  | AXIS  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x2 noeuds|  |  |  |
 |  RAC3  | (RAC3)  |  element de |  2  | PLAN  | T  |
 |  |  | rayonnement |  | AXIS  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x3 noeuds|  |  |  |
 |  LIA3  | (LIA3)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x3 noeuds|  |  |  |
 |  LIA4  | (LIA4)  |  element  |  1  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x4 noeuds|  |  |  |
 |  LIA6  | (LIA6)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x6 noeuds|  |  |  |
 |  LIA8  | (LIA8)  |  element  |  2  | TRID  | T  |
 |  |  | d'echange  |  |  |  |
 |  |  | face a face |  |  |  |
 |  |  | a 2x8 noeuds|  |  |  |

PART{THERMIQUE ADVECTION}
 |  Elements finis en formulation THERMIQUE  ADVECTION  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  |  TUY2  | element de  |  1  | PLAN  | T  |
 |  |  | tuyauterie  |  | TRID  |  |
 |------------|------------------------------------------------------
 |  SEG3  |  TUY3  | element de  |  2  | PLAN  | T  |
 |  |  | tuyauterie  |  | TRID  |  |
 |------------|------------------------------------------------------
 |  |  | triangle  |  |  |  |
 |  TRI3  | (TRI3)  | a 3 noeuds  |  1  | PLAN  | T  |
 |  |  | massif  |  |  |  |
 |  |  | quadrangle  |  |  |  |
 |  QUA4  | (QUA4)  | a 4 noeuds  |  1  | PLAN  | T  |
 |  |  | massif  |  |  |  |
 |  |  | triangle  |  |  |  |
 |  TRI6  | (TRI6)  | a 6 noeuds  |  2  | PLAN  | T  |
 |  |  | massif  |  |  |  |
 |  |  | quadrangle  |  |  |  |
 |  QUA8  | (QUA8)  | a 8 noeuds  |  2  | PLAN  | T  |
 |  |  | massif  |  |  |  |

PART{DIFFUSION}
 |  Elements finis en formulation DIFFUSION  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  POI1  | (POI1)  | element 0D  |  1  | UNID PLAN | (CO)  |
 |  |  | capacite  |  | UNID AXIS | (CO)  |
 |  |  | pour massif |  | UNID SPHE | (CO)  |
 |  SEG2  |  JOI1  |  joint  |  1  | PLAN  | (CO)  |
 |  |  |  |  | TRID  | (CO)  |
 |  |------------------------------------------------------
 |  |  BARR  |  barre  |  1  | PLAN  | (CO)  |
 |  |  |  |  | TRID  | (CO)  |
 |  |------------------------------------------------------
 |  | (M1D2)  | massif (1D) |  1  | UNID PLAN | (CO)  |
 |  |  |  2 noeuds  |  | UNID AXIS | (CO)  |
 |  |  |  |  | UNID SPHE | (CO)  |
 |  |------------------------------------------------------
 |  |  COQ2  | coque mince |  1  | PLAN  | (CO)(COIN)|
 |  |  |  variation  |  |  |  (COSU)|
 |  |  | parabolique |  | AXIS  | (CO)(COIN)|
 |  |  |  dans  |  |  |  (COSU)|
 |  |  | l'epaisseur |  |  |  |
 |  SEG3  | (M1D3)  | massif (1D) |  1  | UNID PLAN | (CO)  |
 |  |  |  3 noeuds  |  | UNID AXIS | (CO)  |
 |  |  |  |  | UNID SPHE | (CO)  |
 |  TRI3  | (TRI3)  |  triangle  |  1  | PLAN  | (CO)  |
 |  |  |  a 3 noeuds |  | AXIS  | (CO)  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ3  | coque mince |  1  | TRID  | (CO)(COSU)|
 |  |  |  variation  |  |  |  (COIN)  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  QUA4  | (QUA4)  | quadrangle  |  1  | PLAN  | (CO)  |
 |  |  | a 4 noeuds  |  | AXIS  | (CO)  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ4  | coque mince |  1  | TRID  | (CO)(COSU)|
 |  |  |  variation  |  |  |  (COIN)  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  TRI6  | (TRI6)  |  triangle  |  2  | PLAN  | (CO)  |
 |  |  |  a 6 noeuds |  | AXIS  | (CO)  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ6  |  coque  |  2  | TRID  | (CO)(COSU)|
 |  |  |  epaisse  |  |  |  (COIN)  |
 |  |  |  variation  |  |  |  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  QUA8  | (QUA8)  | quadrangle  |  2  | PLAN  | (CO)  |
 |  |  | a 8 noeuds  |  | AXIS  | (CO)  |
 |  |  |  massif  |  |  |  |
 |  |------------------------------------------------------
 |  |  COQ8  |  coque  |  2  | TRID  | (CO)(COSU)|
 |  |  |  epaisse  |  |  |  (COIN)  |
 |  |  |  variation  |  |  |  |
 |  |  | parabolique |  |  |  |
 |  |  |  dans  |  |  |  |
 |  |  | l'epaisseur |  |  |  |
 |  CUB8  | (CUB8)  |  cube  |  1  | TRID  | (CO)  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TET4  | (TET4)  |  tetraedre |  1  | TRID  | (CO)  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PRI6  | (PRI6)  |  prisme  |  1  | TRID  | (CO)  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PYR5  | (PYR5)  |  pyramide  |  1  | TRID  | (CO)  |
 |  |  |  a 5 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  CU20  | (CU20)  |  cube  |  2  | TRID  | (CO)  |
 |  |  | a 20 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TE10  | (TE10)  |  tetraedre |  2  | TRID  | (CO)  |
 |  |  | a 10 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PR15  | (PR15)  |  prisme  |  2  | TRID  | (CO)  |
 |  |  | a 15 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PY13  | (PY13)  |  pyramide  |  2  | TRID  | (CO)  |
 |  |  | a 13 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |

PART{DIFFUSION ADVECTION}
 |  Elements finis en formulation THERMIQUE  ADVECTION  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  |  TUY2  | element de  |  1  | PLAN  | (CO)  |
 |  |  | tuyauterie  |  | TRID  |  |
 |------------|------------------------------------------------------
 |  SEG3  |  TUY3  | element de  |  2  | PLAN  | (CO)  |
 |  |  | tuyauterie  |  | TRID  |  |
 |------------|------------------------------------------------------
 |  |  | triangle  |  |  |  |
 |  TRI3  | (TRI3)  | a 3 noeuds  |  1  | PLAN  | (CO)  |
 |  |  | massif  |  |  |  |
 |  |  | quadrangle  |  |  |  |
 |  QUA4  | (QUA4)  | a 4 noeuds  |  1  | PLAN  | (CO)  |
 |  |  | massif  |  |  |  |
 |  |  | triangle  |  |  |  |
 |  TRI6  | (TRI6)  | a 6 noeuds  |  2  | PLAN  | (CO)  |
 |  |  | massif  |  |  |  |
 |  |  | quadrangle  |  |  |  |
 |  QUA8  | (QUA8)  | a 8 noeuds  |  2  | PLAN  | (CO)  |
 |  |  | massif  |  |  |  |

PART{DARCY}
 |  Elements finis en formulation DARCY  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  TRI7  | (HYT3)  |  triangle  |  | PLAN  | TH  |
 |  |  |  a 3 noeuds |  |  |  |
 |  |  |  hybride  |  |  |  |
 |  QUA9  | (HYQ4)  | quadrangle  |  | PLAN  | TH  |
 |  |  | a 4 noeuds  |  |  |  |
 |  |  | hybride  |  |  |  |
 |  CU27  | (HYC8)  |  cube  |  | TRID  | TH  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  hybride  |  |  |  |
 |  TE15  | (HYT4)  |  tetraedre |  | TRID  | TH  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  hybride  |  |  |  |
 |  PR21  | (HYP6)  |  prisme  |  | TRID  | TH  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  hybride  |  |  |  |

PART{FROTTEMENT}
 |  Elements finis en formulation FROTTEMENT  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  MULT  | (FRO3)  |  element a  |  1  | PLAN  | UX UY LX  |
 |  |  |  3 + 2  |  | AXIS  | UR UZ LX  |
 |  |  |  noeuds  |  |  |  |
 |  MULT  | (FRO4)  |  2+ n noeuds|  1  | 3D  | UX UY UZ  |
 |  |  |  |  |  | LX  |
 |  |  |  |  |  |  |
 |  MULT  |  |  2 noeuds  |  1  | 2D-3D  | Ui LX  |
 |  |  |  |  |  |  |

PART{MAGNETODYNAMIQUE}
 |  Elements finis formulation en MAGNETODYNAMIQUE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  TRI3  |  (ROT3) |  element de |  1  | TRID  | FC  |
 |  |  | magneto-  |  |  |  |
 |  |  | dynamique  |  |  |  |
 |  |  | pour coque  |  |  |  |

PART{NAVIER_STOKES}
 |  Elements finis formulation NAVIER_STOKES  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 | QUAF LINE et MACR sont les noms  |  |  |  |
 | generiques pour les familles  |  |  |  |
 | d'elements listes dans les colonnes|  |  |  |
 | corespondantes  |  |  |  |
 |  QUAF  | LINE  |  | 1 U |  |  |
 |  |  |  | 0 P |  |  |
 | TRI7 QUA9  |TRF3 QUF4| TRI3 QUA4  |  | PLAN AXI  | UX UY  |
 | CU27 PR21  |CUF8 PRF6| CUB8 PRI6  |  | TRID  | UX UY UZ  |
 | TE15 PR19  |TEF4 PYF5| TET4 PYR5  |  | TRID  | UX UY UZ  |
 |  |  | Pression nc |  |  |  |
 |  |  | P0  |  |  |  |
 |  QUAF  | MACR  |  | 1 U |  |  |
 |  |  |  | 0 P |  |  |
 | TRI7 QUA9  |MTR6 MQU9|4xTRI3 4xQUA4|  | PLAN AXI  | UX UY  |
 | CU27 PR21  |MC27 MP18|8xCUB8 8xPRI6|  | TRID  | UX UY UZ  |
 | TE15 PR19  |MT10 MP14|8xTET4  |  | TRID  | UX UY UZ  |
 |  |  | Pression nc |  |  |  |
 |  |  | iso P1  |  |  |  |
 |  QUAF  | QUAF  |  | 2 U |  |  |
 |  |  |  | 1 P |  |  |
 | TRI7 QUA9  |TRF7 QUF9| TRI7 QUA9  |  | PLAN AXI  | UX UY  |
 | CU27 PR21  |CF27 PF21| CU27 PR21  |  | TRID  | UX UY UZ  |
 | TE15 PR19  |TF15 PF19| TE15 PR19  |  | TRID  | UX UY UZ  |
 |  |  | Pression nc |  |  |  |
 |  |  | P1  |  |  |  |

PART{EULER (Volumes Finis)}
 |  Volumes finis formulation EULER  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 | TRI3 QUA4  |  |  |  | PLAN  |  |
 | CUB8 PRI6  |  |  |  | TRID  |  |
 | TET4 PYR5  |  |  |  | TRID  |  |

PART{FISSURE}
 |  Elements finis en formulation FISSURE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  SEG2  |  |  |  | MONOD  |  |
 |  |  |  |  | PLAN  |  |
 |  |  |  |  | TRID  |  |

PART{THERMOHYDRIQUE}
 |  Elements finis en formulation THERMOHYDRIQUE  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  TRI3  | (TRI3)  |  triangle  |  1  | PLAN  | PG,PC,T  |
 |  |  |  a 3 noeuds |  | AXIS  | PG,PC,T  |
 |  |  |  massif  |  |  |  |
 |  QUA4  | (QUA4)  | quadrangle  |  1  | PLAN  | PG,PC,T  |
 |  |  | a 4 noeuds  |  | AXIS  | PG,PC,T  |
 |  |  |  massif  |  |  |  |
 |  TRI6  | (TRI6)  |  triangle  |  2  | PLAN  | PG,PC,T  |
 |  |  |  a 6 noeuds |  | AXIS  | PG,PC,T  |
 |  |  |  massif  |  |  |  |
 |  QUA8  | (QUA8)  | quadrangle  |  2  | PLAN  | PG,PC,T  |
 |  |  | a 8 noeuds  |  | AXIS  | PG,PC,T  |
 |  |  |  massif  |  |  |  |
 |  CUB8  | (CUB8)  |  cube  |  1  | TRID  | PG,PC,T  |
 |  |  |  a 8 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TET4  | (TET4)  |  tetraedre |  1  | TRID  | PG,PC,T  |
 |  |  |  a 4 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PRI6  | (PRI6)  |  prisme  |  1  | TRID  | PG,PC,T  |
 |  |  |  a 6 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PYR5  | (PYR5)  |  pyramide  |  1  | TRID  | PG,PC,T  |
 |  |  |  a 5 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  CU20  | (CU20)  |  cube  |  2  | TRID  | PG,PC,T  |
 |  |  | a 20 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  TE10  | (TE10)  |  tetraedre |  2  | TRID  | PG,PC,T  |
 |  |  | a 10 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PR15  | (PR15)  |  prisme  |  2  | TRID  | PG,PC,T  |
 |  |  | a 15 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |
 |  PY13  | (PY13)  |  pyramide  |  2  | TRID  | PG,PC,T  |
 |  |  | a 13 noeuds |  |  |  |
 |  |  |  massif  |  |  |  |

PART{LIAISON}
 |  Elements finis en formulation LIAISON  |
 | Support  | Element | Description |Degre|  Option  | Inconnues |
 | geometrique|  fini  |  |  | de calcul |  nodales  |
 |  POI1  | (POI1)  |  point  |  1  | PLAN  | ALFA  BETA|
 |  |  |  |  | TRID  | en base A |

 Remarque : Correspondance entre les noms des inconnues primales (P)
 --------- et duales (D) :

  P : UX UY UZ UT RX RY RZ RT RR P PI T TSUP TINF LX TH FC PG PC
  D : FX FY FZ FT MX MY MZ MT MR FP FPI Q QSUP QINF FLX FLUX ED QG QC

  P : ALFA BETA CO
  D : FALF FBET QCO

    Les inconnues nodales liees aux deformations planes
 generalisees (UZ,RX,RY) et leurs duales (FZ,MX,MY) sont supportees
 par le point defini lors de l'option MODE PLAN GENE.
    Dans les modes de calcul 1D, les inconnues nodales liees au(x)
 deformation(s) plane(s) generalisee(s) (UZ,UY) et leurs duales (FZ,FY)
 sont supportees par le point defini lors de l'option MODE UNID PLAN
 CYGZ/DYGZ/GYCZ/GYDZ/GYGZ ou MODE UNID AXIS AXGZ.

 Note : Le comportement ELASTIQUE UNIDIRECTIONNEL ne fonctionne
 ----- pas en massif tridimensionnel.

## MATE
    Operateur MATE
    -------------- ACIER

    Syntaxe :

    MAT1 = MATE MODL1 NOMCi VALi ... ;

    Objet :

    L'operateur MATE (MATERIAU) cree un champ de proprietes materielles
    et/ou geometriques. Pour les elements qui necessitent des proprietes
    materielles et geometriques, on peut soit les introduire toutes a la
    fois par MATE, soit introduire les proprietes materielles par MATE
    et les proprietes geometriques par CARA, puis fusionner les deux
    champs ainsi obtenus par ET.

    Dans la partie "Detail des proprietes" ci-apres, on decrit :
    - les proprietes materielles attendues pour chaque formulation
      (sections 1 a 12),
    - la definition des reperes d'orthotropie des formulations non
      isotropes (section 13),
    - et les proprietes geometriques dans une derniere section.

    Commentaire :

    MAT1 : objet contenant les caracteristiques du materiau (type
        MCHAML, sous-type CARACTERISTIQUES)

    MODL1 : Objet modele (type MMODEL)

    NOMCi : nom du ieme parametre (type MOT) (voir ci-dessous)

    VALi : valeur(s) du ieme parametre (types ENTIER, FLOTTANT,
        MCHAML, EVOLUTION, LISTMOTS, POINT ...)

        Remarque 1 : le type LISTMOTS concerne des composantes
        evaluees a l'externe par l'operateur VARI, a l'aide
        du module utilisateur COMPUT. Dans ce cas, l'objet
        LISTMOTS donne la liste des parametres dont depend
        la composante.
        Remarque 2 : Si VALi est de type MCHAML celui-ci doit
        etre en correspondance avec le modele, c'est a dire
        avoir le meme objet maillage que le modele. Pour ce faire
        soit on part d'un CHPOINT transforme en MCHAML (operateur
        CHAN), soit on procede comme dans l'exemple
        cham_vari.dgibi (voir exemple : cham_vari.dgibi)

   Detail des proprietes :

CHAP{formulation MECANIQUE}

PART{MECANIQUE ELASTIQUE ISOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ISOTROPE |

   'YOUN' : module d'Young
   'NU ' : coefficient de poisson
   'RHO ' : masse volumique
   'ALPH' : coefficient de dilatation thermique secant
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'VISQ' : coefficient de viscosite

   Cas des elements joints elastiques isotropes :

       - dans le cas des elements joints 2D elastiques, seul le cas
   isotrope est autorise. Les noms des parametres NOMCi a rentrer
   pour un element joint 2D sont :

   'KS ' : raideur de cisaillement ( N/m3 )
   'KN ' : raideur normale ( N/m3 )
   'RHO ' : masse volumique ( kg/m2 )
   'ALPN' : coefficient de dilatation thermique secant dans la
        direction normale au joint ( m/K )
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation

    Remarque : meme si les valeurs de KS et KN sont identiques, il
        faut les rentrer deux fois.

       - dans le cas des elements joints 3D elastiques isotropes,
    les deux raideurs de cisaillement sont identiques. Les noms des
    parametres NOMCi a rentrer sont les memes que ceux du cas du 2D
    isotrope.

PART{MECANIQUE ELASTIQUE ARMATURE}
   | Noms des parametres pour un materiau ELASTIQUE ARMATURE |

   Ce modele concerne les armatures du beton arme (BARR sur SEG2).

   Dans le cas d'armatures passives, les parametres sont :

   'YOUN' : module d'Young
   'SECT' : section de l'armature

   Dans le cas des armatures actives (beton precontraint), il convient
   de preciser egalement :

   Pour la perte de precontrainte par frottement :
   'FF ' : coefficient de frottement angulaire (0.18 rd-1)
   'PHIF' : coefficient de frottement lineaire (0.002 m-1)

   Pour la perte de precontrainte par recul a l'ancrage :
   'GANC' : glissement a l'ancrage (0.0)

   Pour la perte de precontrainte par relaxation de l'acier :
   'RMU0' : coefficient de relaxation de l'armature (0.43)
   'FPRG' : contrainte de rupture garantie (1700.e6 Pa)
   'RH10' : relaxation a 1000 heures (2.5 %)

PART{MECANIQUE ELASTIQUE MODAL}
   | Noms des parametres pour un materiau ELASTIQUE MODAL  |

   'FREQ' : frequence (type 'FLOTTANT')
   'MASS' : masse generalisee (type 'FLOTTANT')
   'DEFO' : deformee modale (type 'CHPOINT')

   Parametres facultatifs
   'AMOR' : amortissement generalise (type 'FLOTTANT')
   'CGRA' : centre de gravite pour la rotation (type 'POINT')

PART{MECANIQUE ELASTIQUE STATIQUE}
   | Noms des parametres pour un materiau ELASTIQUE STATIQUE |

   'RIDE' : produit rigite * deformee (type 'CHPOINT')
   'MADE' : produit masse * deformee (type 'CHPOINT')
   'DEFO' : deformee (type 'CHPOINT')

   Parametres facultatifs
   'AMOR' : amortissement generalise (type 'FLOTTANT')

PART{MECANIQUE ELASTO NON_LINEAIRE}
   | Noms des parametres pour un materiau ELASTO NON_LINEAIRE |

   Modele elastique NON_LINEAIRE EQUIPLAS :

   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.

   Modele NON_LINEAIRE UTILISATEUR :

   La liste de composantes de materiau est celle definie par l'objet
   LISTMOTS donne sous le mot cle 'C_MATERIAU' dans la syntaxe de
   l'operateur MODE.

PART{MECANIQUE ELASTO-PLASTIQUE}
   | Noms des parametres pour un materiau ELASTO-PLASTIQUE |

   Les parametres qui suivent sont a definir EN PLUS des parametres
   relatifs au comportement elastique. Les modeles de plasticite
   disponibles sont les suivants :

   Modele plastique PARFAIT :

   'SIGY' : limite elastique

   Modele plastique a ecrouissage ISOTROPE :

   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.

   Modele plastique a ecrouissage CINEMATIQUE LINEAIRE :

   'SIGY' : limite elastique
   'H ' : module d'ecrouissage

   Modele plastique a ecrouissage de type CHABOCHE :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Xi variables d'ecrouissage cinematique (i=1 ou 2)
        EP tenseur des deformations plastiques
        p deformation plastique equivalente cumulee
        J2 deuxieme invariant des contraintes
        deviatoriques

   --> Critere : J2 (S-X) = R(p)

   --> Ecrouissages: dXi = Ci * (2/3 * Ai * PHI(p) * dEP - Xi*dp )
        dR = B * (RM - R ) dp
        avec : X = X1 dans le cas d'un seul centre
        X1+X2 dans le cas de deux centres
        R(0)=R0
        PHI(p)= 1 + (PSI-1)* e**(-OMEG*p)

   Les donnees a introduire sont les suivantes :

        Cas a 1 centre sans ecrouissage isotrope :

   'A ','C ' : parametres liees a l'evolution du centre
   'PSI ','OMEG' : parametres liees au terme de rappel
   'R0 ' : limite elastique

        Cas a 1 centre avec ecrouissage isotrope :

   'A ','C ' : parametres liees a l'evolution du centre
   'PSI ','OMEG' : parametres liees au terme de rappel
   'R0 ' : limite elastique initiale
   'RM ' : limite elastique finale
   'B ' : constante liee a l'evolution de la limite elastique

        Cas a 2 centres sans ecrouissage isotrope :

   'A1 ','C1 ' : parametres liees a l'evolution du 1-er centre
   'A2 ','C2 ' : parametres liees a l'evolution du 2-eme centre
   'PSI ','OMEG' : parametres liees au terme de rappel
   'R0 ' : limite elastique

        Cas a 2 centres avec ecrouissage isotrope :

   'A1 ','C1 ' : parametres liees a l'evolution du 1-er centre
   'A2 ','C2 ' : parametres liees a l'evolution du 2-eme centre
   'PSI ','OMEG' : parametres liees au terme de rappel
   'R0 ' : limite elastique initiale
   'RM ' : limite elastique finale
   'B ' : constante liee a l'evolution de la limite elastique

   Modele plastique de type DRUCKER-PRAGER PARFAIT :

   'LTR ' : limite en traction simple
   'LCS ' : limite en compression simple

   Dans ce cas, le critere utilise a pour equation :

        ALFA * Tr(S) + Seq = K

   avec : S tenseur des contraintes
        Seq contrainte equivalente au sens de Von Mises

        ALFA = (  |LCS| - LTR ) / ( |LCS| + LTR )
        K = 2. * |LCS| * LTR / ( |LCS| + LTR )

   L'ecoulement est associe.

   Modele plastique de type DRUCKER-PRAGER :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Seq contrainte equivalente au sens de Von Mises
        p deformation plastique equivalente cumulee

   --> Critere initial : ALFA * Tr(S) + BETA * Seq = K

   --> Critere ultime : ETA * Tr(S) + MU * Seq = KL

   --> Ecrouissage : dK = H * dp ( H en valeur algebrique)

   --> Potentiel d'ecoulement : GAMM * Tr(S) + DELT * Seq

   Les parametres a definir sont:
        ALFA, BETA, K, ETA, MU, KL, H, GAMM, DELT

   Modele BETON en contraintes planes (2D ou coques minces)

  ('LTR1') : limite en traction dans la 1-ere direction (par defaut
        YOUN*1.2E-4)
  ('ETR1') : deformation a rupture en traction dans la 1-ere direction
        (par defaut 3*LTR1/YOUN)
  ('LTR2') : limite en traction dans la 2-eme direction (par defaut
        LTR1)
  ('ETR2') : deformation a rupture en traction dans la 2-eme direction
        (par defaut 3*LTR2/YOUN)
  ('BETR') : coefficient de reduction du module de cisaillement en
        cas de fissuration (compris entre 0. et 1., par defaut
        0.1)
  ('VF1X') : deux composantes du vecteur VF1 definissant la direction
  ('VF1Y') assocee a LTR1 (par defaut 1. et 0. respectivement)

  ('LCS ') : limite en compression simple (par defaut YOUN*1.2E-3)
  ('ECS ') : deformation a rupture en compression simple (par defaut
        10*LCS/YOUN)
  ('LBIC') : limite en bi-compression

   Modele BETON en deformations planes, axisymetrique et 3D

   Dans ce modele, le comportement du beton est non-lineaire dans le
   domaine des tractions, et lineaire par ailleurs.

  ('LTR1') : limite en traction dans la 1-ere direction (par defaut
        YOUN*1.2E-4)
  ('ETR1') : deformation a rupture en traction dans la 1-ere direction
        (par defaut 3*LTR1/YOUN)
  ('LTT1') : limite de transition en traction dans la 1-ere direction
        (par defaut 0.)
  ('ETT1') : deformation correspondant a LTT1 (par defaut ETR1)
  ('ERS1') : deformation residuelle en traction dans la 1-ere
        direction (par defaut 0.)
  ('VF1X') : trois composantes du vecteur VF1 definissant la direction
  ('VF1Y') assocee a LTR1
  ('VF1Z')

  ('LTR2') : limite en traction dans la 2-eme direction (par defaut
        LTR1)
  ('ETR2') : deformation a rupture en traction dans la 2-eme direction
        (par defaut 3*LTR2/YOUN)
  ('LTT2') : limite de transition en traction dans la 2-eme direction
        (par defaut 0.)
  ('ETT2') : deformation correspondant a LTT2 (par defaut ETR2)
  ('ERS2') : deformation residuelle en traction dans la 2-eme
        direction (par defaut 0.)
  ('VF2X') : trois composantes du vecteur VF2 definissant la direction
  ('VF2Y') assocee a LTR2
  ('VF2Z')

  ('LTR3') : limite en traction dans la 3-eme direction (par defaut
        LTR1)
  ('ETR3') : deformation a rupture en traction dans la 3-eme direction
        (par defaut 3*LTR3/YOUN)
  ('LTT3') : limite de transition en traction dans la 3-eme direction
        (par defaut 0.)
  ('ETT3') : deformation correspondant a LTT3 (par defaut ETR3)
  ('ERS3') : deformation residuelle en traction dans la 3-eme
        direction (par defaut ERS1)
  ('VF3X') : trois composantes du vecteur VF3 definissant la direction
  ('VF3Y') assocee a LTR3, necessaires uniquement en 3D si besoin.
  ('VF3Z')

  ('BETR') : coefficient residuel de reduction du module de
        cisaillement en cas de fissuration (compris entre 0. et
        1., par defaut 0.1)

   Attention : Les vecteurs VF1, VF2 et VF3 doivent etre orthogonaux.
        Dans le cas d'un calcul avec une limite en traction
        differente des deux autres, il est obligatoire de definir
        le vecteur correspondant a cette limite VF1, VF2 ou VF3

        Dans le cas oa¹ LTR1, LTR2 et LTR3 sont donnees, les
        deux vecteurs VF1 et VF2 sont obligatoires pour definir
        les directions 1, 2 et 3.

        On peut introduire des valeurs non nulles traduisant des
        ouvertures initiales des fissures dans les directions
        1, 2 et 3 a l'aide de la table TAB1 utilisee dans la
        procedure NONLIN au moyen de : TAB1.'VARI'.'OUV1',
        TAB1.'VARI'.'OUV2', TAB1.'VARI'.'OUV3'.

   Modele plastique parfait pour les elements TUYAU FISSURE :

   'SIGF' : contrainte limite d'ecoulement
   'J1C ' : valeur de J a l'initiation
   'T ' : module de dechirure

   Modele plastique ecrouissable pour les elements TUYAU FISSURE :

   'JDA ' : mot-cle suivi de :
   NOMJDA : courbe J-Da constituee par un objet de type
        EVOLUTIO, avec en abscisse la propagation et en
        ordonnee J.

   'TRAC' : mot-cle suivi de :
   NOMTRAC : courbe de traction constituee par un objet de type
        EVOLUTIO, avec en abscisse les rotations (en radians)
        et en ordonnee les moments. La procedure TRACTUFI
        permet de fabriquer une telle courbe en cas de non
        propagation. La procedure PROPAG permet de
        fabriquer une telle courbe en cas de propagation.

   Modele de materiau elastoplastique endommageable (Lemaitre-Chaboche)

     L'ecrouissage et l'endommagement sont isotropes. Le critere de
   Von Mises est couple a l'endommagement.

   'TRAC' : mot-cle suivi de :
   NOMTRAC : courbe de traction constituee par un objet de type
        EVOLUTIO, avec en abscisse les deformations et en
        les contraintes. Elle doit contenir comme premier
        point, le point (0,0) et comme second point, le
        point correspondant a la limite elastique.
        On peut la dessiner par la directive DESSINE .
   'EPSD' : Seuil d'endommagement : il s'agit de la deformation
        plastique a partir de laquelle le materiau s'endommage.
   'DC ' : Valeur critique de la variable D decrivant l'endom-
        magement. DC caracterise la rupture du materiau .
   'EPSR' : Deformation plastique a rupture du materiau .

   Modele UBIQUITOUS

     Il s'agit d'un modele de plasticite pour des materiaux presentant
   une ou deux directions de faiblesse. Selon chaque direction, le
   critere est de type Mohr-Coulomb avec ecoulement eventuellement
   non associe. Ce modele ne fonctionne qu'en bidimensionnel.

   'NCRI' : nombre de directions de faiblesse (1 ou 2)
   'ANG1' : angle de la 1-ere direction avec Ox (en degres)
   'TRA1' : limite en traction selon la 1-ere direction
   'PHI1' : angle de frottement (en degres)
   'PSI1' : angle de dilatance (en degres)
  ('ANG2')  |
  ('TRA2')  |:  idem pour la deuxieme direction
  ('PHI2')  |
  ('PSI2')  |

   Modele GAUVAIN

     Il s'agit d'un modele de plasticite globale pour les poutres en
   beton arme soumises a des chargements de flexion dominante.

   'TRAC' : mot-cle suivi de :
   NOMTRAC : courbe(s) de traction constituee(s) par un objet de
        type EVOLUTIO, avec en abscisse des deformations et en
        ordonnee des contraintes. Chaque courbe doit decrire
        une loi moment-courbure, depuis les valeurs negatives
        (4 points) jusqu'aux valeurs positives (4 points),
        en passant par l'origine, soit 9 points au total.
        On transforme les moments en contraintes et les
        courbures en deformations par les formules classiques
        en prenant comme distance a la fibre moyenne, la demi
        hauteur de la poutre.
        Si une seule courbe est fournie, on l'utilise pour les
        deux directions de flexion.
        On peut dessiner ces courbes par la directive DESSINE.
   'STOR' : contrainte limite elastique en torsion
   'SCOM' : contrainte limite elastique en compression

   Modele GLOBAL

     Il s'agit d'un modele de plasticite globale pour les poutres en
   beton arme qui permet la prise en compte des lois de comportement
   non-lineaire selon les types de sollicitation (axiale, flexion et
   cisaillement).

   'COMP' : mot-cle suivi de :
   NOMCOMP : courbe de comportement pour des sollicitations axiales,
        constituee par un objet de type EVOLUTIO, avec en
        abscisse des deplacements et en ordonnee des forces
        axiales.
   'FLXY' : mot-cle suivi de :
   NOMFLXY : courbe de comportement pour des sollicitations en flexion
        dans le plan xOz, constituee par un objet de type
        EVOLUTION, avec en abscisse des produits (rotation *
        longueur de l'element) et en ordonnee des moments de
        flexion.
   'FLXZ' : mot-cle suivi de :
   NOMFLXZ : courbe de comportement pour des sollicitations en flexion
        dans le plan xOy, constituee par un objet de type
        EVOLUTION, avec en abscisse des produits (rotation *
        longueur de l'element) et en ordonnee des moments de
        flexion.
   'CISY' : mot-cle suivi de :
   NOMCISY : courbe de comportement pour des sollicitations en
        cisaillement dans le plan xOy, constituee par un objet de
        type EVOLUTIO, avec en abscisse des deplacements et en
        ordonnee des efforts tranchants.
   'CISZ' : mot-cle suivi de :
   NOMCISZ : courbe de comportement pour des sollicitations en
        cisaillement dans le plan xOz, constituee par un objet de
        type EVOLUTIO, avec en abscisse des deplacements et en
        ordonnee des efforts tranchants.

   Remarques : - il faut definir au moins une loi pour un materiau;
        - pour un materiau on ne peut definir qu'une loi en
        flexion (FLXY ou FLXZ) et qu'une loi en cisaillement
        (CISY ou CISZ);
        - pour des lois de comportement en compression-traction
        et en flexion l'element fini peut etre POUT ou TIMO,
        pour les lois en cissailement on ne peut utiliser que
        l'element TIMO;
        - les objets de type EVOLUTIO doivent decrire les lois
        depuis les valeurs negatives (2 ou 3 points) jusqu'aux
        valeurs positives (2 ou 3 points), en passant par
        l'origine, soit 5 ou 7 points au total.

   Modele BILIN_MOMY

     Il s'agit d'un modele de plasticite de flexion pour les poutres
   (elements POUT ou TIMO) agissant sur la composante (locale) MOMY.

   'EAYI' : module apres plasatification
   'YMOM' : moment de plastification

   Modele BILIN_EFFZ

     Idem que le precedent mais agissant sur l'effort tranchant selon la
   composante (locale)EFFZ.

   Modele TAKEMO_MOMY

     Il s'agit d'un modele de plasticite-endommagement de flexion pour
   les poutres (elements POUT ou TIMO) agissant sur la composante
   (locale) MOMY.

   'TRAC' : mot-clef suivi de :
   NOMTRAC : courbe de base decrivant la loi moment-courbure. Si le
        comportement est symmetrique, cette courbe trilineaire
        comprend 4 points: origine, crackage, plastification et
        un point definissant le comportement apres
        plastification. Si le comportement est non symmetrique,
        la courbe comprend 7 points, depuis les valeurs negatives
        (3 points) jusqu'aux valeurs positives (3 points), en
        passant par l'origine.
        On peut dessiner cette courbe par la directive DESSIN.

   'SFDP' : degradation de raideur pour des courbures positives ou
   'SFDN' : negative (SFDN est egale a SFDP dans le cas symmetrique)

   'PINP' : "pinching" pour des courbures positives ou negative
   'PINN' : (PINN est egale a PINP dans le cas symmetrique)

   'SRDP' : adoussissement cyclique pour des courbures positives ou
   'SRDN' : negative (SRDP est egale a SRDN dans le cas symmetrique)

   Modele TAKEMO_EFFZ

     Meme que le precedent, mais agissant sur l'effort tranchant
   EFFZ.

   Modele BA1D

     Il s'agit d'un modele formule en contraintes generalisees pour decrire
   le comportement cyclique de poteaux en beton arme sujets a de la flexion

   'UELA' : deplacement elastique limite au dela duquel l'endommagement
        est active (1.0E-3)
   'FPLA' : effort plastique (100)
   'HCIN' : module d ecrouissage cinematique pour la plasticite (10.0)
   'PFIS' : parametre de l evolution de l'endommagement (0.3)
   'QFRA' : parametre de l evolution de l'endommagement (0.5)
   'APIH' : parametre de l evolution du glissement (1.0)
   'BPIH' : parametre de l evolution du glissement (5.0)

   Modele CAM_CLAY

   'E0 ' : indice des vides initial
   'M ' : coefficient de frottement
   'COHE' : cohesion
   'P0 ' : pression de preconsolidation
   'KAPA' : pente elastique dans un diagramme e-log(p)
   'LAMD' : pente plastique dans un diagramme e-log(p)
   'G1 ' : module de cisaillement

   Modele HUJEUX

     Il s'agit d'un modele de comportement pour les sables et
   certaines argiles. Les equations du modele sont de la forme :

   --> Notations : EE tenseur des deformations elastiques
        EP tenseur des deformations inelastiques
        S tenseur des contraintes
        ep trace(EP)
        eq deuxieme invariant du deviateur de EP
        p trace(S)/3
        q deuxieme invariant des contraintes
        deviatoriques
        K1 module d'incompressibilite
        G1 module de cisaillement

   --> elasticite : dp = K1*P1*((-p/P1)**N)*trace(dEE)
        dq = 3*g1*P1*((-p/P1)**N)*dev(dEE)

   --> Critere : F = q/M*(COHE-p)
        + R * (B*ln((COHE-p)/(COHE+PC)*exp(-1./B)) - 1.)

   --> Ecrouissages: R=R0+eq/(eq+A)
        PC= (P0+COHE)*exp(-BETA*ep) - COHE
   --> Potentiel
       d'ecoulement: G = q/M*(COHE-p) + ln(COHE-p)

   'M ' : coefficient de frottement
   'COHE' : cohesion
   'P0 ' : pression de preconsolidation (> 0.)
   'E1 ' : module d'elasticite de reference
   'P1 ' : pression correspondant a la valeur E1 fournie
   'BETA' : module de compressibilite plastique
   'A ' : coefficient dans la loi d'ecrouissage
   'B ' : coefficient different de 0.
   'R0 ' : valeur initiale de R
   'N ' : exposant de la loi elastique non lineaire
        (compris entre 0. et 1., mais different de 1.)

   Modele de GURSON

     La surface de plasticite est definie par
   SIGeq - (SIGY+H.epse)*( 1+PORO**2-2*PORO*cosh(-1.5*P/SBAR) ) =0

   'SIGY' : limite elastique initiale
   'H ' : coefficient d'ecrouissage (Prandtl-Reuss)
   'SBAR' : limite elastique heterogene
   'PORO' : porosite initiale

   Modele JOINT_DILATANT

     Il s'agit d'un modele de joint avec un critere de Mohr-Coulomb
   et ecoulement non associe.

   'PHI ' : angle de frottement (utilise dans le critere)
   'MU ' : angle de dilatance (utilise dans le potentiel
        d'ecoulement)
   'FTRC' : resistance maximale en traction

   Modele JOINT_SOFT

     Il s'agit d'un modele de joint avec un critere de Mohr-Coulomb
     et avec adoucissement en traction et cisaillement. L'ecoulement se
     fait sans dilatance.

   'PNOR' : Position de la pointe (hypothetique) du cone
   'SJTB' : Relation contrainte normale - ouverture du joint en traction
        (type EVOLUTION - Valeur positive pour la traction)
   'SJCB' : Relation contrainte normale - fermeture du joint en traction
        (type EVOLUTION - Valeur positive pour la traction)
   'SJSB' : Relation contrainte de cisaillement - glissement en cisaillement
        pour une contrainte normale nulle (Type EVOLUTION)
   'BETA' : Parametre controlant la decharge en cisaillement
   'CPLG' : Definition des couplages

   Modele JOINT_COAT

     Il s'agit d'un modele de joint cisaillement avec critere de plasticite
   isotrope, adoucissement et endommagement.

   'SJSB' : Relation contrainte de cisaillement - glissement en cisaillement
        (type EVOLUTION)
   'BETA' : Parametre controlant la decharge

   Modele ANCRAGE_ELIGEHAUSEN

     Il s'agit d'un modele de glissement acier/beton reprenant la loi
   d'Eligehausen (sous chargement monotone): la relation contrainte de
   cisaillement - glissement possede un plateau puis est adoucissante
   de facon lineaire. Le comportement du joint en traction/compression
   est lineaire elastique.

   'S1T' : Glissement au debut du plateau
   'S2T' : Glissement a la fin du plateau
   'S3T' : Glissement a la fin de l'adoucissement
   'T1T' : Contrainte de cisaillement sur le plateau
   'T3T' : Contrainte de cisaillement residuelle apres la fin de
        l'adoucissement
   'ALFA' : Parametre definissant la premiere partie de la courbe situee
        avant le plateau
        (Valeur conseillee: 0.4)
   'PERI' : Perimetre de la barre d'acier

   Modele INTJOI

     Il s'agit d'un modele [1,2] d'interface acier/beton sans/avec prise en
   compte de la corrosion. Son support est un elements joint 2D/3D. Il est
   bien adapte aux cas des chargements comlpexes (monotones, cycliques
   alternes). Les parametres, en plus de celles elastiques, sont les suivan

  * Parametres mecaniques (sans corrosion)
   'AD' : fragilite (1.0e-5)
   'Y0' : seuil en energie pour l'endommagement (50)
   'ALPA' : coefficient de couplage des modes I et II (6)
   'GAIN' : module d'ecrouissage cinematique 1 (2.0e9)
   'AAIN' : module d'ecrouissage cinematique 2 (5.0e-7)

  * Parametres lies au phenomene de corrosion
   'Q1CO' : coefficient critere de Gurson 1 (3.5)
   'Q2CO' : coefficient critere de Gurson 2 (0.9)
   'Q3CO' : coefficient critere de Gurson 3 (0.1)
   'SYCO' : contrainte d'activation du critere de Gurson (-1.0e6 Pa)
   'NCOE' : coefficient d'ecrouissage 1 (2)
   'KCOE' : coefficient d'ecrouissage 1 (1.0e10)
   'TC ' : degre de corrosion macroscopique (perte de section)
   'GONF' : 0 si pas de gonflement et 1 sinon. Dans ce dernier cas,
        considerer un champs thermique equivalent pour faire
        pas informations liees a la deformations imposees

     [1] B. Richard, F. Ragueneau, C. Cremona, L. Adelaie, JL Tailhan. (2010). A
        three-dimensional steel/concrete model including corrosion effects. Eng
        Fracture Mechanics. 77:951-973.

     [2] L. Adelaide, B. Richard, F. Ragueneau, C. Cremona. (2010). Thermodynami
        admissibility of a set of constitutive equations coupling elasticity,
        isotropic damage and internal sliding. Comptes Rendus Mecanique. 338:1

   Modele COULOMB

     Il s'agit d'un modele de joint dilatant avec un critere de
   Mohr-Coulomb et ecoulement associe.

     Si utilise avec un element autre que JOI1, il faut donner :
   'EF ' : seconde raideur normale
   'ECN ' : seuil de deformation en dessous duquel la raideur
        normale passe de KN a EF (a rentrer en valeur absolue)
   'COHE' : cohesion (0. pour le frottement classique)
   'FRIC' : angle du critere de frottement de Coulomb (en degres)
  ('FTRC') : resistance maximale en traction (0. par defaut)

     Si utilise avec un element JOI1, il faut donner :
   'FNE ' : limite d'elasticite pour l'effort normal de compression
   'QT ' : raideur tangente au dela du seuil d'elasticite FNE,
        il faut verifier QT < KN
   'COHE' : cohesion (0. pour le frottement classique)
   'FRIC' : angle du critere de frottement de Coulomb (en degres)
   'TYPE' : parametre pour choisir le type de glissement:
        - = 1 : deplacement
        - = 2 : rotation
  Remarque: - pour l'element JOI1, possibilite de plasticite dans la
        direction normale au plan de glissement (ecrouissage
        isotrope lineaire en compression).

   Modele AMADEI

     Il s'agit d'un modele de joint a comportement incremental non
   lineaire et comportement post-pic adoucissant en cisaillement

   'FIMU' : angle de frottement entre les asperites
   'SGMT' : valeur limite en compression pure
   'I0 ' : angle initial d'inclinaison des asperites
   'S0 ' : cohesion
   'B0 ' : rapport entre les cisaillements residuel et pic pour
        les faibles compressions
   'UP ' : valeur du deplacement tangentiel associe au pic
   'UR ' : valeur du deplacement tangentiel associe au debut
        du comportement en cisaillement residuel
   'KNI ' : raideur normale initiale du joint
   'FI0 ' : angle de frottement residuel entre les asperites
   'VM ' : deplacement normal correspondant a la fermeture
        maximale du joint et compte positivement en compression

   Modele ACIER_UNI

     Il s'agit du modele uni-axial de Menegotto-Pinto modifie pour
   prendre en compte le flambage du ferraillage.

   'STSY' : contrainte de plasticite
   'STSU' : contrainte ultime
   'EPSH' : deformation de debut d'ecrouissage
   'EPSU' : deformation ultime
   'ROFA' : coefficient RO
   'BFAC' : rapport de la rigidite d'ecrouissage cyclique avec la
        rigidite elastique
   'A1FA' : coefficient A1
   'A2FA' : coefficient A2
   'FALD' : rapport de la longueur entre deux renfort de
        cisaillement avec le diametre de la barre
   'A6FA' : coefficient A6
   'CFAC' : coefficient C
   'AFAC' : coefficient A

   Modele ACIER_ANCRAGE

     Il s'agit du modele de comportement d'ancrage ou de recouvrement
   base sur de le modele d'acier ACIER_UNI et le modele de glissement
   acier/beton ANCRAGE_ELIGEHAUSEN. Ce modele est base sur l'equilibre
   entre la traction dans les aciers et les contraintes de cisaillement
   a l'interface acier-beton (supposees uniforme sur toute la longueur
   d'ancrage). Cet equilibre est realise de facon iterative.

   'LANC' : Longueur d'ancrage
   'SECT' : Section d'une barre d'acier

  - Donnees relatives au modele de glissement:

   'G12' : Module de cisaillement
   'S1T' : Glissement au debut du plateau
   'S2T' : Glissement a la fin du plateau
   'S3T' : Glissement a la fin de l'adoucissement
   'T1T' : Contrainte de cisaillement sur le plateau
   'T3T' : Contrainte de cisaillement residuelle apres la fin de
        l'adoucissement
   'ALFA' : Parametre definissant la premiere partie de la courbe situee
        avant le plateau
        (Valeur conseillee: 0.4)

  - Donnees relatives au modele d'acier:

   'STSY' : contrainte de plasticite
   'STSU' : contrainte ultime
   'EPSH' : deformation de debut d'ecrouissage
   'EPSU' : deformation ultime
   'ROFA' : coefficient RO
   'BFAC' : rapport de la rigidite d'ecrouissage cyclique avec la
        rigidite elastique
   'A1FA' : coefficient A1
   'A2FA' : coefficient A2
   'FALD' : rapport de la longueur entre deux renfort de
        cisaillement avec le diametre de la barre
   'A6FA' : coefficient A6
   'CFAC' : coefficient C
   'AFAC' : coefficient A

   Modele BETON_UNI

     Il s'agit d'un modele de Hognestad, avec ou sans confinement

   'STFC' : containte de compression au pic
   'EZER' : deformation de compression au pic
   'STFT' : contrainte de traction au pic
   'ALF1' : parametre de confinement
   'OME1' : parametre de confinement
   'ZETA' : pente de la partie descendante de la courbe de
        compression
   'ST85' : plateau de la courbe de compression
   'TRAF' : facteur definissant l'adoucissement de traction

   'STPT' : contrainte residuelle en traction

  Parametres definissant la courbe de fermeture et d'ouverture de la
  fissure
   'FAMX' : facteur F1 (definissant le point de refermeture)
        FAMX doit etre positif pour avoir un sens physique.
        Si sa valeur est negative, la loi de fermeture de fissure
        raide est prise et les parametres STPT, FAMX, FACL, FAM1
        et FAM2 ne sont pas pris en compte par le modele
   'FACL' : facteur F2 (definissant le point d'ouverture complete)
   'FAM1' : facteur F1'(definissant la pente associee a F1)
   'FAM2' : facteur F2'(definissant la pente associee a F2)

   Modele FRAGILE_UNI

     Il s'agit d'un modele d'endommagement uni-axial fragile
   en traction et compression. L'adoucissement est hyperbolique
   avec possibilite de contrainte residuelle.

   'FC ' : resistance en compression
   'FC_R' : contrainte residuelle en compression
   'STRC' : Deformation controlant l'adoucissement en compression
   'FT ' : resistance en traction
   'FT_R' : contrainte residuelle en traction
   'STRT' : Deformation controlant l'adoucissement en traction

   Modele BETON_BAEL

     Cette loi uniaxiale reprend la loi donnee pour le beton par le
   BAEL pour la compression. Le modele est plastique en compression
   et unilateral en traction (avec resistance nulle)

   'FC ' : resistance en compression

   Modele MAZARS

     Memes caracteristiques que le materiau ENDOMMAGEABLE

   Modele INTIMP
     Modele d'acier corrode avec prise en compte de la degradation de
   l'interface acier/beton sans/avec corrosion [1]. Le modele d'acier
   corrodee est celui developpe par [2,3], celui d'interface est celui
   developpe par [4]. Le couplage est realise par l'approche proposee
   par [5]. Les parametres a entrer, en plus des caracteristiques elastiq
   sont les suivants :

   * Modele d'acier :
      'SOCT' : section d'acier (fonction de l'acier)
      'SOGS' : limite elasticite (400 MPa)
      'DCS ' : endommagement critique (0.2)
      'TCS ' : degre de corrosion en terme de perte de section lie a l'acier
      'MS ' : exposant d'acrouissage (2.786)
      'KS ' : facteur d'acrouissage (500 MPa)

   * Modele d'interface :
      'GCEO' : module de Coulomb (15 GPA)
      'AD ' : fragilite (7.5e-5)
      'GAMC' : coefficient d'ecrouissage cinematique 1 (7.0e9)
      'ACOE' : coefficient d'ecrouissage cinematique 2 (5.0e-7)
      'LCCO' : longueur d'ancrage (fonction de la longueur des elements, 1 si
      'EPSC' : deformation seuil de l'endommagement (1.0e-4)
      'TCI ' : degre de corrosion en terme de perte de section lie a l'acier
      'CALA' : indicateur de calcul
        = 0 si modele couple
        = 1 si modele d'interface seul
        = 2 si modele d'acier seul

   * References:
     [1] B. Richard, F. Ragueneau, C. Cremona. (2010). A multifber approach
        to describe the ultimate behaviour of corroded reinforced concrete
        structures. Euro-C conference, Rohmoos/Schladming, Austria.

     [2] A. Ouglova. (2010). Etude du comportement mecanique des structures en
        arme ateintes par corrosion. These de L'ENS Cachan.

     [3] B. Richard, F. RAgueneau, C. Cremona, L. Adelaie, JL Tailhan. (2010). A
        three-dimensional steel/concrete model including corrosion effects. Eng
        Fracture Mechanics. 77:951-973.

     [4] L. Adelaide, B. Richard, F. Ragueneau, C. Cremona. (2010). Thermodynami
        admissibility of a set of constitutive equations coupling elasticity,
        isotropic damage and internal sliding. Comptes Rendus Mecanique. 338:1

     [5] D. Combescure, F. Wang. (2007). Assessments of existing RC structures u
        dynamic loading using non linear modeling. CONSEC 2007, Tours, France.

   Modele RICBET_UNI
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

    'HYST' : indicateur pour choisir le type de critere de refermeture
        voulu : à contrainte nulles (1) ou à deformations nulles (2)

    'FT ' : resistance equivalente en traction (2.1e6 MPa)
    'ALDI' : fragilite en traction uniaxiale (4.0e-3)
    'GAM1' : module d'ecrouissage cinematique 1 (5.0e9)
    'A1 ' : module d'ecrouissage cinematique 2 (2.0e-6)
    'SIGF' : contraite de refermeture des fissures (-3.0e6)
    'FC ' : resistance en compession (10.0e6)
    'AF ' : module surface plasticite (1.0)
    'AG ' : module potentiel plasticite (1.0)
    'AC ' : ecrouissage plastique 1 (4.0e10)
    'BC ' : ecrouissage plastique 2 (600.0)
    'SIGU' : contrainte asymptotique compression (-6.0e6)

   * References:
     [1] B. Richard, F. Ragueneau (2012). 3D modelling of concrete for
        earthquake analysis: damage mechanics and plasticity coupling.
        WCCM 2012, Sao Paulo, Bresil.

     [2] B. Richard, F. Ragueneau (2012). Continuum damage mechanics based
        model for quasibrittle materials subjected to cyclic loadings:
        formulation, numerical implementation and applications.
        Engineering Fracture Mechanics. In press.

   Modele UNILATERAL

      Memes caracteristiques que le materiau ENDOMMAGEABLE

   Modele PARFAIT_UNI

       Il s'agit d'un modele plastique avec ecrouissage cinematique
       utilisable pour l'acier.

    'SIGY' : limite elastique
    'H ' : Module d'ecrouissage (H=0 pour un modele plastique parfait)

   Modele PARFAIT_ANCRAGE

    Il s'agit du modele de comportement d'ancrage ou de recouvrement
    base sur de le modele d'acier PARFAIT_UNI et le modele de glissement
    acier/beton ANCRAGE_ELIGEHAUSEN. Ce modele est base sur l'equilibre
    entre la traction dans les aciers et les contraintes de cisaillement
    a l'interface acier-beton (supposees uniforme sur toute la longueur
    d'ancrage). Cet equilibre est realise de facon iterative.

   'LANC' : Longueur d'ancrage
   'SECT' : Section d'une barre d'acier

  - Donnees relatives au modele de glissement:

   'G12' : Module de cisaillement
   'S1T' : Glissement au debut du plateau
   'S2T' : Glissement a la fin du plateau
   'S3T' : Glissement a la fin de l'adoucissement
   'T1T' : Contrainte de cisaillement sur le plateau
   'T3T' : Contrainte de cisaillement residuelle apres la fin de
l'adoucissement
   'ALFA' : Parametre definissant la premiere partie de la courbe situee
avant le plateau
        (Valeur conseillee: 0.4)

  - Donnees relatives au modele d'acier:

   'SIGY' : limite elastique
   'H ' : Module d'ecrouissage (H=0 pour un modele plastique parfait)

   Modele STRUT_UNI

   Il s'agit d'un modele de diagonale et tirant pour un comportement
   en cisaillement non-lineaire du modele a fibre
   Il faut donner les caracteristiques du beton, de l'acier
   ainsi que la quantite d'acier et l'inclinaison de la diagonale.

     Pour le beton:

   'STFC' : containte de compression au pic
   'EZER' : deformation de compression au pic
   'STFT' : contrainte de traction au pic
   'ALF1' : parametre de confinement
   'OME1' : parametre de confinement
   'ZETA' : pente de la partie descendante de la courbe de
        compression
   'ST85' : plateau de la courbe de compression
   'TRAF' : facteur definissant l'adoucissement de traction
   'STPT' : contrainte residuelle en traction
   'FAMX' : facteur F1 (definissant le point de refermeture)
   'FACL' : facteur F2 (definissant le point d'ouverture complete)

   'THET' : inclinaison de la diagonale (en degre)

      Pour l'acier:

   'YOUS' : module d'elasticite
   'STSY' : contrainte de plasticite
   'STSU' : contrainte ultime
   'EPSH' : deformation de debut d'ecrouissage
   'EPSU' : deformation ultime
   'ROFA' : coefficient RO
   'BFAC' : rapport de la rigidite d'ecrouissage cyclique avec la
        rigidite elastique
   'A1FA' : coefficient A1
   'A2FA' : coefficient A2

   'ROST' : Densite volumique de cadre

   'EULT' : Deformation ultime utilisee pour le calcul
        de l'indice d'endommagement
     Si abs(EULT)>1, les indices d'endommagement des 2 bielles valent 0.
     Si EULT<0, les indices sont fonctions de la deformation
        maximale en compression dans le beton
     Si EULT>0, les indices sont fonctions de la position de l'axe
     neutre.

   Modele CISAIL_NL

       Il s'agit d'un modele non-lineaire d'endommagement-plasticite
       avec adoucissement pour l'effort tranchant.
       Cette loi peut etre utilisee sur un element de poutre TIMO
       comme modele global ou comme materiau d'une section de poutre
       (modele a fibre).

   'DELP' : Deformation limite du domaine elastique (sens positif)
   'DELN' : Deformation limite du domaine elastique (sens negatif)
   'DMAP' : Endom. maximum lors de la plastification (sens positif)
   'DMAN' : Endom. maximum lors de la plastification (sens negatif)
   'BETA' : Parametre de pincement
   'ALFA' : Parametre reglant la vitesse de la degradation de
        resistance sous chargement cyclique
   'TETA' : Fraction de la resistance residuelle apres complete
        degradation sous chargement cyclique
   'MONP' : Evolution de l'effort tranchant (ou de la contrainte de
        cisaillement) en fonction de la deformation plastique (sens positif)
   'MONN' : Evolution de l'effort tranchant (ou de la contrainte de
        cisaillement) en fonction de la deformation plastique (sens negatif)

   Modele INFILL_UNI

       Il s'agit d'un modele non-lineaire d'endommagement-plasticite
       unilateral avec adoucissement en compression et sans resistance en
       traction (element de barre uniquement).
       Cette loi peut etre utilisee sur deux elements de barre
       comme modele global pour modeliser les murs de
       remplissage en maconnerie

   'DELA' : Deformation limite du domaine elastique
   'DMAX' : Endom. maximum lors de la plastification
   'BETA' : Parametre de pincement
   'GAMM' : Parametre reglant la position du point de rechargement
   'GAMP' : Parametre reglant la position du point de rechargement
   'ALFA' : Parametre reglant la vitesse de la degradation de
        resistance sous chargement cyclique
   'TETA' : Fraction de la resistance residuelle apres complete
        degradation sous chargement cyclique
   'MONO' : Evolution de la force axiale de compression en fonction
        de la deformation plastique (attention, la compression
        est prise positive ...)

   Modele OTTOSEN

  ('LTR') : limite en traction
        (par defaut YOUN*1.2E-4)
  ('GFTR') : taux de restitution d'energie
        (nomme aussi energie de fissuration)
        (par defaut LTR*3.9E-5, mais cette valeur correspond
        a des unites SI)
  ('GS') : module traduisant la perte de resistance au cisaillement
        d'une fissure avec son ouverture (usuellement compris
        entre 2 et 6 Mpa et par defaut YOUN*1.8E-4)
  ('BTR') : fraction non recouvrable de l'ouverture d'une fissure.
        (par defaut 0.2)
  ('LCS') : limite en compression simple
        (par defaut le materiau est elastique en compression)
  ('LCBI') : limite en bi-compression
        (par defaut 1.15*LCS)
  ('EPCM') : deformation plastique au pic, en compression simple
        (par defaut 4.*LCS/(3.*YOUN))
  ('EPCU') : deformation plastique ultime, en compression simple
        (par defaut 5.*EPCM)

  Dans un deuxieme temps, il faut obligatoirement adjoindre au CHAML de
  de sous-type CARACTERISTIQUES construit par l'operateur MATE, le CHAML
  resultat de l'operateur TAILLE applique au modele de calcul.

  Par ailleurs en deformations planes et en axisymetrique on peut
  definir en plus :

  ('EPSR') : deformation a rupture dans la direction normale au plan
        de representation.

  En cas de grands deplacements, il faut definir l'option LAGRANGIEN de PASAPAS
  a TOTAL pour prendre correctement en compte l'evolution du repere local.

   Modele OTTOVARI

  ('LTR') : limite en traction
        (par defaut YOUN*1.2E-4)
  ('GFTR') : taux de restitution d'energie
        (nomme aussi energie de fissuration)
        (par defaut LTR*3.9E-5, mais cette valeur correspond
        a des unites SI)
  ('BTR') : fraction non recouvrable de l'ouverture d'une fissure.
        (par defaut 0.2)
  ('LCS') : limite en compression simple
        (par defaut le materiau est elastique en compression)

  Dans un deuxieme temps, il faut obligatoirement adjoindre au CHAML de
  de sous-type CARACTERISTIQUES construit par l'operateur MATE, le CHAML
  resultat de l'operateur TAILLE applique au modele de calcul.

   Modele viscoplastique viscoendommageable pour le beton en dynamque
   rapide BETON_DYNAR_LMT
   - ATTENTION la porosite initiale influence le module d'young reel
        Km=YOUNG/(3*(1-2*NU))
        Gm=YOUNG/(2*(1+NU))

  - Coefficients de compressibilite et cisaillement de la matrice
    avec les pores (Mori-Tanaka)
        Kporo=4*XKm*XGm*(1-f)/(4*XGm+3*XKm*f)
        Gporo=XGm*(1-f)/(1+f*(6*XKm+12*XGm)/(9*XKm+8*XGm))

  - Critere de plasticite FNT :

      FNT = 3*J2(SIG) / SGM**2 + 2Q1f cosh(Q2 I1 / 2SGM) - (1+(Q3 f)**2)

   - Evolution de la deformation plastique

     EPSP = 1/(1-D)*(FNT/MVP)**NVP * dFNT/dSIG

   - Evolution de la porosite

      Df = K * f/(1-f) * (FNT/MVP)**NVP

   - Fonction seuil d'endommagement en traction en compression :

      FDi = (EPSE - ED0 - 1/Ai*(Di/(1-Di))**(1/Bi))

 - Evolution de l'endommagement en traction en compression :

      Di= (FDi/MDi)**NDi

Les donnees a introduire en plus des parametres d'elasticite sont les
suivantes:

   'F0' : Porosite initiale du beton (0.3)
   'Q1' : Parametre du critere de Gurson modifie par Needleman
        et Tvergaard (0.5 a 2.)
   'Q2' : Parametre du critere de Gurson modifie par Needleman
        et Tvergaard (0.5 a 2.)
   'Q3' : Parametre du critere de Gurson modifie par Needleman et
        Tvergaard (0.5 a 2.)
   'SGM0': Resistance de la matrice cimentaire sans les pores (70 Mpa)
   'XN' : Exposant du seuil de viscoplasticite (15.)
   'NVP' : Parametre de la viscoplasticite de type Perzyna (1.5)
   'MVP' : Parametre de la viscoplasticite de type Perzyna (1.D-2)
   'K' : Influence l'evolution de la porosite (15 a 60)
   'MDT' : Parametre de viscosite de l'endommagement de traction (0.5D-4)
   'NDT' : Parametre de viscosite de l'endommagement de traction (5.)
   'MDC' : Parametre de viscosite de l'endommagement de compression
        (0.5D-3)
   'NDC' : Parametre de viscosite de l'endommagement de compression (20.)
   'ED0' : Seuil en deformation pour la traction (1.D-04)
   'AC' : Parametre pour la compression (3000)
   'BC' : Parametre pour la compression (4.)
   'AT' : Parametre pour la traction (20000)
   'BT' : Parametre pour la traction (1.6)

   Modele PARFAIT_INSA

   Modele plastique parfait pour le comportement orthotrope
   dedouple de coques minces

    'SIG1' : limite elastique dans la premiere direction d'orthotropie

    'SIG2' : limite elastique dans la deuxieme direction d'orthotropie

   Modele ECROUIS_INSA

   Modele plastique ecrouissable pour le comportement orthotrope
   dedouple de coques minces

    'TRA1' : mot-cle suivi de :
    NOMTRA1 : courbe de traction dans la premiere direction
        d'orthotropie constituee par un objet de type
        EVOLUTION avec en abscisse les deformations et en
        ordonee les contraintes. Elle doit contenir comme
        premier point, le point (0,0) et comme second point,
        le point correspondant a la limite elastique.

    'TRA2' : mot-cle suivi de :
    NOMTRA2 : courbe de traction dans la deuxieme direction
        d'orthotropie constituee par un objet de type
        EVOLUTION avec en abscisse les deformations et en
        ordonee les contraintes. Elle doit contenir comme
        premier point, le point (0,0) et comme second point,
        le point correspondant a la limite elastique.

   Modele BETOCYCL
     Modele comportant deux surfaces avec deux mecanismes chacunes.
     Une partie de l'ecrouissage isotrope du mecanisme de compression
     de la grande surface est due a l'ecrouissage cinematique de la
     petite surface. Les surfaces sont definies par des criteres de
     Rankyne avec ecrouissage cinematique (petite surface) ou isotrope
     (grande surface).

    'HHH1' : Module d'ecrouissage cinematique de la petite surface.
        (type FLOTTANT)
    'FTPE' : Limite originelle de traction de la petite surface
        (type FLOTTANT)
    'FCPE' : Limite originelle de compression de la petite surface
        (type FLOTTANT)
    'FTGR' : Limite originelle de traction de la grande surface
        (type FLOTTANT)
    'FCGR' : Limite originelle de compression de la grande surface
        (type FLOTTANT)
    'WOR0' : Travail cyclique de reference
        (type FLOTTANT)
    'TREV' : Evolution de l'ecrouissage isotrope de traction
        (type EVOLUTIO)
    'COEV' : Evolution de l'ecrouissage isotrope de compression
        (type EVOLUTIO)
    'LCAT' : Longueur associee a la courbe de traction
        (type FLOTTANT)
    'LCAC' : Longueur associee a la courbe de compression
        (type FLOTTANT)
    'EPSO' : Parametre d'endommagement cyclique (deformation)
        (type FLOTTANT)

    Remarques:
    1- Les huit premiers parametres sont calcules par la procedure
       IDENTI a partir des courbes de traction, de compression simples,
       du maillage et des autres parametres.
    2- L'utilisation de longueurs associees aux courbes de traction et
       compression permet de limiter la dependance vis-a-vis du maillage.

   Modele STEINBERG

   Lois constitutives :

     limite d'ecoulement Y :

     Y = SIGY.(1+BETA.(P'+EPSI))**N.G/G0

     et :

     SIGY.(1+BETA.(P'+EPSI))**N < YMAX

     avec:
        P': deformation plastique equivalente
        P'=sqrt(2/3.EP:EP)
        EP: tenseur des deformations plastiques deviatoires
        G: le module de cisaillement

     module de cisaillement G :

     G = G0+GP'.P/(ETA**(1/3))+GT'.(T-300)
     G0 = YOUNG0/(2*(1+NU0))

     avec : YOUNG0 module d'elasticite initial
        NU0 coefficient de Poisson (constant)
        G0 module de cisaillement initial

     TM=TM0*EXP(2.MU0.(1.-1./ETA))/( ETA ** (2./3.) )
     TM: temperature de fusion

     et: si T > TM :

     G = Y = 0

     des lors la trace de la deformation plastique ets nulle
     et le deviateur des deformations elastques est nul.

     avec:
        P: la pression hydrostatique:
        P=-trace(SIGMA)/3
        SIGMA: le tenseur des contraintes
        ETA:la compression
        ETA=RHO/RHO0
        RHO,RHO0:densite et densite initiale du materiau
        T: temperature exprimee ici en degre Kelvin

     Le module de cisaillement G est donne secant i.e.:

        SIG=HOOK.DEF et D_SIG=HOOK.D_DEF+D_HOOK.DEF

   'SIGY' : limite d'ecoulement initial
   'BETA' : coefficient BETA de l'ecrouissage
   'N' : coefficient N de l'ecrouissage
   'EPSI' : deformation plastique equivalente initiale
   'GP' : pente du module de cisaillement par rapport a la
        pression ( sans unite ): GP'
   'GT' : terme corrigeant le module de cisaillement en fonction
        de la temperature (terme homogene au module
        de cisaillement).
        On rentre ici directement le terme GT'.(T-300) de
        la loi constitutive sous forme d'un objet EVOLUTION
        (en fonction de la temperature).
   'YMAX' : limite d'ecoulement maximale a module de cisaillement
        constant
   'TMO' : temperature de fusion du materiau pour ETA=1
   'MU' : coefficient MU0 intervenant dans le calcul de la
        temperature de fusion

   Modele ZERILLI

   Lois constitutives :

     -Limite d'elasticite Y pour les materiaux Cubiques
     a Faces Centrees (C.F.C.) :

      Y = DYG+C2'.sqrt(P').exp(-c3'.T+C4'.T.ln(EPT))+K.L**(-1/2)

     -Limite d'elasticite Y pour les materiaux Cubiques
     Centres (C.C.) :

      Y = DYG+C1'.exp(-C3'.T+C4'.T.ln(EPT))+C5'.(P')**N+K.L**(-.5)

      avec:
        T :la temperature
        P':la deformation plastique equivalente
        P'=sqrt(2/3.EP:EP)
        EP:le tenseur des deformations plastiques
        EPT:vitesse de deformation totale equivalente
        EPT=sqrt(2/3.ET:ET)
        ET: tenseur des vitesses de deformation

   'DYG' : terme DYG
   'C1' : coefficient C1'
   'C2' : coefficient C2'
   'C3' : terme C3'.T ( produit C3' par la temperature
        T) entre sous forme d'un objet EVOLUTION
        ( en fonction de la temperature)
   'C4' : terme C4'.T ( produit C4' par la temperature
        T) entre sous forme d'un objet EVOLUTION
        ( en fonction de la temperature)
   'C5' : coefficient C5'
   'N' : coefficient N
   'K' : coefficient K
   'L' : diametre moyen d'un grain
   'TYPE' : type de structure du materiau
        Si la structure est CFC: TYPE=0.
        Si la structure est CC : TYPE=1.

   Modele PRESTON

   Equations constitutives :

     -module de cisaillement G :

     G = G0+GP'.P/(ETA**(1/3))+GT'.(T-300)
     G0 = YOUNG0/(2*(1+NU0))

     avec : YOUNG0 module d'elasticite initial
        NU0 coefficient de Poisson (constant)
        G0 module de cisaillement initial
        ETA:la compression
        ETA=RHO/RHO0

     TM=TM0*EXP(2.MU0.(1.-1./ETA))/( ETA ** (2./3.) )
     TM: temperature de fusion

     et: si T > TM :

     G = Y = 0 ( Y: limite d'elasticite)

     des lors la trace de la deformation plastique ets nulle
     et le deviateur des deformations elastques est nul.

     -Termes adimensionnels:

      Y' = Y/G
      T' = T/TM
      EPT'= EPT/X

     avec:
        Y la contrainte d'ecoulement
        G le module de cisaillement
        T la temperature
        TM la temperature de fusion
        X = 1/6.(4/PI)**(.5).OMEGA
        OMEGA: pulsation de Debye
        OMEGA = (G/RHO)**(.5)
        RHO:densite du materiau
        EPT: vitesse de deformation totale equivalente
        EPT=sqrt(2/3.ET:ET)
        ET: vitesse de deformation totale

     -Terme adimensionnel de contrainte de saturation YS:

      S1 = S0-(S0-SINF).erf(K'.T'.ln(g/EPT')
      S2 = S0.(EPT'/g)**BETA
      YS = max(S1,S2)

     -Terme adimensionnel de limite d'elasticite YL:

      L1 = Y0-(Y0-YINF).erf(K'.T'.ln(g/EPT')
      L2 = Y1.(EPT'/g)**Y2
      YL = max(L1,min(L2,S2))

     -Terme adimensionnel de contrainte d'ecoulement
     Y' dans le cas de materiaux
     Cubiques Centres (C.C.): P=0

     Y' = YS-(YS-YL).exp(-TAU.EP/(YS-YL))

     -Terme adimensionnel de contrainte d'ecoulement
     Y' dans le cas des autres
     materiaux : P different de 0

     Coeff1 = (S0-YL).(exp(P.(YS-YL)/(S0-YL))-1)
     Coeff2 = 1-exp(-P.(YS-YL)/(S0-YL))
     Y' = YS+(S0-YL)/P.ln(1-Coeff2.exp(-P.TAU.EP/Coeff1))

     avec:
        EP: deformation plastique equivalente
        EP=sqrt(2/3.EPS:EPS)
        EPS: deformations plastiques

     Le module de cisaillement G est donne secant i.e.:

        SIG=HOOK.DEF et D_SIG=HOOK.D_DEF+D_HOOK.DEF

   'RHO' : densite initiale du materiau
   'TAU' : parametre sans dimension TAU utlise dans
        la loi d'ecrouissage du modele
   'P' : parametre sans dimension P
        -si P=0, on est dans le cas des materiaux a structure
        cubique centre (C.C.)
        -sinon, on est dans le cas des materiaux a structure
        cristallographique differente.
   'S0' : parametre sans dimension S0
        il donne la contrainte de saturation pour T=0Â°K
   'SINF' : parametre sans dimension SINF
        il donne la contrainte de saturation pour T(Â°K) infini
   'K' : parametre sans dimension K'.T utlise dans
        le calcul de la contrainte de saturation et la
        limite elastique. On le rentre sous forme
        d'un objet EVOLUTION (en fonction de la temperature
        T)
   'G' : parametre sans dimension g utilise dans
        le calcul de la contrainte de saturation et la
        limite elastique
   'Y0' : parametre sans dimension Y0
        il donne la limite d'elasticite pour T=0Â°K
   'YINF' : parametre sans dimension YINF
        il donne la limite d'elasticite pur T(Â°K) infini
   'Y1' : parametre sans dimension Y1 utilise dans le
        calcul de la limite d'elasticite
   'Y2' : parametre sans dimension Y2 utilise dans le
        calcul de la limite d'elasticite
   'BETA' : parametre sans dimension BETA utilise dans le
        calcul de la limite d'elasticite et de la contrainte
        de saturation
   'GP' : pente du module de cisaillement par rapport a la
        pression ( sans unite ): GP'
   'GT' : terme corrigeant le module de cisaillement en fonction
        de la temperature (terme homogene au module
        de cisaillement).
        On rentre ici directement le terme GT'.(T-300) de
        la loi constitutive sous forme d'un objet EVOLUTION
        (en fonction de la temperature).
   'TMO' : temperature de fusion du materiau pour ETA=1
   'MU' : coefficient MU0 intervenant dans le calcul de la
        temperature de fusion

   Modele HINTE
      Il s'agit d'un modele de joint dedie au delaminage de
      structures composites stratifies (fonctionne en 2D).
      On suppose les deux modes d'endommagement Y1 en cisaillement
      et Y2 en ouverture de fissure entre plis.

       L'energie dissipee est :

        E = Y1*(d1/dt) + Y2*(d2/dt) d1 et d2 sont deux
       variables internes d'endommagement

       Si : d2 < 1 et Y < YR alors d1 = d2 = W(Y)
        sinon d1 = d2 = 1

       Un endommagement isotrope est introduit sous la forme :

        Y = sup(((Y2)**AL) + ( (GAM1*Y1)**AL))**(1/AL)

       La fonction de delaminage est :

        w(Y)=((N/(N+1))**N)*( <Y-Y0>**N)/ ((YC-Y0)**N)

       La force thermodynamique a rupture associee a l'endommagement
       ultime DR est :

        YR = Y0 + ( ((N+1)/N) * (DCRI** (1/N))*(YC-Y0)

       Les parametres du modele sont donc :

    'Y0' : seuil d'endommagement
    'YC' : energie critique d'endommageme
    'GAM1' : parametres de couplage entre energies de cisaillement
        et d'ouverture
    'AL' : gouverne la forme et le lieu de rupture en mode mixte
    'NN' : caracterise la plus ou moins grande fragilite de
        l'interface (plus N est grand, plus l'interface
        est fragile)
    'DCRI' : permet de simuler une rupture fragile(par defaut DCRI=1)
    'KS' : rigidites d'interface en cisaillement
    'KN' : rigidites d'interface normale

   Modele J2

   * Les equations du modele sont (voir [1]):

     --> Notation: J2 deuxieme invariant du tenseur deviatorique des
        contraintes
        sigy limite d'elasticite
        epse deformation plastique equivalente (variable interne)
        F critere de plasticite
        G potentiel d'ecoulement
     --> critere de plasticite
        F = sqrt(3*J2)-sigy(epse)
     --> loi d'ecrouissage:
        sigy(epse) = SIG0+KISO*epse +(SIGI-SIG0)*(1-exp(-VELO*epse))
     --> Potentiel d'ecoulement :
        G = F (plasticite associee)

   * Les parametres specifiques du modele sont :

     'SIG0' : Limite elastique
     'SIGI' : Contrainte ultime
     'KISO' : module d'ecrouissage lineaire
     'VELO' : parametre de vitesse

   * References:

     [1] Simo, J.C. and Hughes, T.J.R. ``Computational Inelasticity'',
        Springer-Verlag, New York, 1997

   Modele RH_COULOMB

   Modele de Mohr-Coulomb approxime hyperbolique (plasticite associee et
   parfaite)

   * Les equations du modele sont (voir [1]):

     --> Notation: I1 Premier invariant du tenseur des contraintes
        J2 deuxieme invariant du tenseur deviatorique des
        t angle de Lode (de -30Â° a +30Â°
        F critere de plasticite
        G potentiel d'ecoulement

     --> critere de plasticite
        F = I1/3.D0*sin(PHI)-COHE*cos(PHI)+sqrt(J2*ktet(t)**2+(ar*COHE)**2)
        ar = 0.05*cos(PHI)
        ktet(t)= aa - bb*sin(3*t) si abs(t) > 25Âº
        cos(t)-sin(PHI)*sin(t)/sqrt(3) si abs(t) =< 25Âº
        aa = aa(PHI,25Âº) see [1]
        bb = bb(PHI,25Âº) see [1]
     --> Potentiel d'ecoulement :
        G = F (plasticite associee)

   * Les parametres specifiques du modele sont :

     'COHE' : cohesion
     'PHI ' : angle de friction

   * References:

     [1] Abbo, A.J. and Sloan, S.W., ``A smooth hyperbolic approximation
        to the Mohr-Coulomb yield criterion'', Computers and Structures,
        54, 3, 427-441, 1995.

   Modele MRS_LADE

   * Les equations du modele sont (voir [1,2]):

     --> Notations : I1 Prelmier invariant du tenseur des contraintes
        J2 deuxieme invariant du tenseur deviatorique des
        contraintes
        p = -I1/3
        q = sqrt(3*J2)
        t angle de (de 0Âº a 60Âº)
        kcon variable interne du caŽne
        kcap variable interne de la fermeture
        dkcon increment de kcon
        dkcap increment de kcap
        dwp increment du travail plastique
        Fcon equation du caŽne
        Fcap equation de la fermeture
        Gcon potentiel d'ecoulement du caŽne
        Gcap potentiel d'ecoulement de la fermeture
     --> Equation du caŽne :
        Fcon = wwf(t,E)*q*(1+q/QA)**EXPM - etacon(kcon)*p
        wwf(t,E) = W-W function
     --> Equation de la fermeture :
        Fcap = ((p-cpm*pcapf(kcap))/(cpr*pcapf(kcap)))**2 +
        (wwf(t,E)*q*(1+q/QA)**EXPM/
        (etacon(kcon)*cfr*pcapf(kcap)) )**2 - 1
        cpm = cpm(PHI,ALP)
        cpr = cpr(PHI,ALP)
        cfr = cfr(PHI,ALP)
     --> loi d'ecrouissage du caŽne:
        etacon(kcon) = aaa*exp(-bbb*kcon)*(K1+kcon)**(1/EXPV) +
        K2*ETAB*kcon/(EPSI+kcon)
        aaa = aaa(EXPV,K1,K2,EPSI)
        bbb = bbb(EXPV,K1,K2,EPSI)
     --> loi d'ecrouissage de la fermeture:
        pcapf(kcap) = PCAP*(1+kcap**(1/EXPR))
     --> evolution des variables internes:
        dkcon = (p/PA))**(-EXPL)/(CCON*PA)* dwp
        dkcap = (PCAP/PA)**(-EXPR))/(CCAP*PA)* dwp
     --> Potentiel d'ecoulement du caŽne:
        Gcon = wwf(t,E)*q*(1+q/QA)**EXPM - N etacon(kcon)
        *( p-2*ALP*pcapf(kcap)*ln(p+ALP*pcapf(kcap)) )
     --> Potentiel d'ecoulement de la fermeture:
        Gcap = Fcap (plasticite associee)

   * Les parametres specifiques du modele sont :

     'PC ' : Doit etre 0 (Seuls les materiaux sans cohesion sont
        implementes)
     'PA ' : Parametre d'echelle (habituellement 1)
     'QA ' : Parametre d'echelle (habituellement 1)
     'EXPM' : Parametre de l'equation du caŽne (doit etre >= 0)
        = 0 entraine une relation lineaire p-q dans la region du caŽn
        alors etacon(kcon) est identique a l'angle de friction
     'E ' : Forme sur le plan deviatorique
        De = 1 (circulaire) a = 0.5 (triangulaire), habituellement =
0.7
     'K1 ' : Parametre d'ecrouissage du caŽne (doit etre > 0)
     'K2 ' : Parametre d'ecrouissage du caŽne (doit etre > 0)
        K2*ETAB est la valeur residuelle (atteinte pour kcon=infinity)
        of etacon(kcon), function related with the friction angle.
     'ETAB' : Valeur maximale de etacon(kcon), fonction correlee avec
l'angle
        de friction. (doit etre > 0). Elle est atteinte pour kcon=1
     'EXPV' : Parametre d'ecrouissage du caŽne (doit etre > 0)
     'EPSI' : Parametre d'ecrouissage du caŽne (doit etre > 0)
     'N ' : Degre de non-associativite a l'apex (p = 0).
        De 0 (incompressibilite dans toute la region du caŽne)
        a -1 (ecoulement associe pour p = 0)
     'CCON' : parametre d'evolution de la variable interne du caŽne (positif
     'EXPL' : P)rametre d'evolution de la variable interne du caŽne (positif
     'PCAP' : Valeur initiale de la contrainte limite isotrope pcapf(kcap),
        (intersection del la fermeture avec l'axe p)
     'EXPR' : parametre d'evolution de la variable interne de la fermeture
        (positif)
     'CCAP' : parametre d'evolution de la variable interne de la fermeture
        (positif)
     'PHI ' : doit etre = 0, l'incompressibilite est imposee a l'intersect
        caŽne fermeture.
        (parameter related with cap slope at cone-cap intersection)
     'ALP ' : Shape of cap function. Intersection of cone-cap is located
        at p = ALP * pcapf(kcap) (must be > 0)

     Parameters for numerical differentiation (integration of const.
     law and computation of consistent tangent moduli, see [3,4]) are fixed
     in time-integration operator.

   * References:

     [1] Sture, S., Runesson, K. and Macari-Pasqualino, E.J.
        ``Analysis and calibration of a three-invariant plasticity
        model for granular materials'', Ing. Archiv, 59, 253-266, 1989.
     [2] Perez-Foguet, A. and Huerta, A. ``Plastic flow potential for the
        cone region of the MRS-Lade model'', J. Engr. Mech, Vol. 125,
        pp. 364-367, 1999.
     [3] Perez-Foguet, A., Rodriguez-Ferran, A. and Huerta, A. ``Numerical
        differentiation for local and global tangent operators in
        computational plasticity'', Comp. Meth. App. Mech. Engrg. Vol. 189,
        pp. 277-296, 2000.
     [4] Perez-Foguet, A., Rodriguez-Ferran, A. and Huerta, A.
        ``Numerical differentiation for non-trivial consistent tangent
        matrices: an application to the MRS-Lade model'', Int. J. Num. Met.
        Engrg., Vol. 48, pp. 159-184, 2000.

   Modele VMT_FEFP

   * Modele hyperelastoplastique, FeFp plasticite en deformation finie, voir
     [1].

   * Les equations de plasticite sont decrites en [2]. Le modele de plastici
     est appele Von Mises - Tresca.

   * Le modele hyperelastique de Hencky est utilise.

   * Les parametres specifiques au modele sont :

     'SIG0' : Limite elastique
     'SIGI' : Contrainte ultime
     'KISO' : Module d'ecrouissage lineaire
     'VELO' : Parametre de vitesse
     'MSHA' : forme de la section deviatorique (1, Von Mises a 20, Tresca)

     Les parametres du line search local (integration de l'equation
     constitutive, voir [2]) sont definis dans l'operateur d'integration
     temporel.

     References:

     [1] Simo, J.C., ``Numerical analysis of classical plasticity'', in P.G.
        Ciarlet and J.J. Lions, editors, Handbook of Numerical Analysis, vol.
        IV, Elsevier, Amsterdam, 1998.
     [2] Perez-Foguet, A., Armero, F., On the formulation of closest-point
        projection algorithms. Part II: Globally convergent schemes, Int. J.
        Num. Meth. Engrg., 53:331-374, 2002.

   Modele RHMC_FEFP

   * Modele hyperelastoplastique, FeFp plasticite en deformation finie (Voir
     le modele VMT_FEF)

   * Les equations de plasticite sont les memes que le modele de RH_COULOMB
     en petite deformation.

   * Le modele hyperelastique de Hencky est utilise.

   * Les parametres specifiques au modele sont :

   'COHE' : Cohesion
   'PHI ' : Angle de friction

   Modele POWDER_FEFP

   * Modele hyperelastoplastique, FeFp plasticite en deformation finie (Voir
     le modele VMT_FEF)

   * Les equations de plasticite sont decrites en [1]. Le modele de plastici
     est elliptique dans l'espace de l'invariant des contraintes et sa taille
     et sa forme dependent de la densite relative.

   * Le modele hyperelastique de Hencky est utilise.

   * Les parametres specifiques au modele sont :

     'SIGY' : Limite elastique du materiau entierement compacte
     'NNN1' : Parametre du critere (dependence de l'ellipse avec la densite
     'NNN2' : Parametre du critere (dependence de l'ellipse avec la densite
     'ETA0' : Densite relative initiale

   * References:

   [1] Perez-Foguet, A., Rodriguez-Ferran, A. and Huerta, A. ``Consistent
       tangent matrices for density-dependent plasticity models'', Int. J.
       Ana. Num. Met. Geomech., Vol. 25, pp. 1045-1075, 2001.

   Modele POWDERCAP_FEFP

  * Modele hyperelastoplastique (Voir le modele POWDER_FEFP)

  * Les parametres specifiques au modele sont :

    'SIGY' : Limite elastique du materiau entierement compacte
    'NNN1' : Parametre du critere (dependence de l'ellipse avec la densite)
    'NNN2' : Parametre du critere (dependence de l'ellipse avec la densite)
    'ETA0' : Densite relative initiale
    'COHE' : Cohesion du materiau entierement compacte
    'PHI0' : Angle de friction initial
    'PHI ' : Angle de friction du materiau entierement compacte
    'NNNC' : Parametre du critere (dependance de la cohesion avec la densit

   Modele BETON_INSA

   Ce modele fonctionne en contraintes planes (2D ou coques minces) ,
   et deformations planes ou axisymetrique

   ('ALFA') : rapport des contraintes ultimes en traction simple et
        en compression simple (par defaut 0.1)
   ('LCS ') : contrainte ultime en compression simple
        (par defaut YOUN*1.E-3)
   ('EMAX') : deformation de rupture en compression simple (par defaut
        10*LCS/YOUN)
   ('EPUT') : deformation de rupture en traction simple (par defaut
        3*ALFA*LCS/YOUN)
   ('ICOM') : choix du type de comportement a l'interieur du domaine
        ultime
        ICOM = 0 : comportement elasto-plastique ecrouissable
        ICOM = 1 : comportement elastique
        (par defaut 0)
   ('FTC ') : coefficient residuel de reduction du module de
        cisaillement en cas de fissuration (compris entre 0. et
        1., par defaut 0.1)

   ('GFTR') : energie de fissuration (si 'EPUT' n'est pas donnee
        la valeur par defaut de 'GFTR' est 0.15 )
        si GFTR est donnee il n'est pas necessaire de donner
        'EPUT'

   Modele ISS_GRANGE

   Il s'agit d'un modele d'interaction sol-structure developpe par
   S.GRANGE (2008). Le modele d'origine est developpe dans
   these[1]. Une modification sur le calcul des phenomenes de
   plasticite et de decollement a ete apportee de maniere a en
   faciliter la programation.

   Le modele implante est utilisable exclusivement avec les elements
   joint JOI1 en comportement orthotrope 3D. Pour comprendre
   l'influence de chacun, il est recommande de se referer a la these
   de S.GRANGE[1] (resume du modele page 77) et aux articles [2][3].

   'DIAM' : diametre de la fondation (si circulaire)
   'LX ' : longueur de la fondation dans la direction x
        (si fondation filante ou rectangulaire)
   'LY ' : longueur de la fondation dans la direction y
        (si fondation filante ou rectangulaire)

   'XA','XB','XC','XD','XE','XF': parametres decrivant la forme
        du critere de rupture
   'QMAX' : capacite portante de la fondation
   'A6 ' : vitesse d'agrandissement de la surface de charge

   'ETA3' : parametre de viscosite
   'XTIM' : pas de temps pour le calcul dynamique

   'A8 ' : type de calcul
        si = 1 : decollement desactive
        sinon : decollement active

   'A9 ' : type de fondation
        si = 1 : filante
        si = 2 : rectangulaire
        sinon : circulaire

   Les raideurs elastiques de la fondation (Kelz,Kelh,etc...) sont a
   entrer comme les raideurs elastiques de l'element joi1 orthotrope
   (KN,KS1,etc...). Il faut faire attention au changement d'axes
   (local <-> ISS)!

   * References:
     [1] S. Grange(2008). Modelisation simplifiee 3D de l'interaction
        sol-structure: application au genie parasismique.
        Ph. D. thesis, INP Grenoble.
        http://tel.archives-ouvertes.fr/tel-00306842/fr.

     [2] S. Grange, P. Kotronis, J. Mazars (2009). A macro-element to
        simulate 3D soil-structure interaction considering plasticity
        and uplift. International Journal of Solids and Structures 46
        3651-3663.

     [3] S. Grange, P. Kotronis, J. Mazars (2009). A macro-element to
        simulate dynamic Soil-Structure Interaction. Engineering
        Structures 31 (2009) 3034-3046.

   Modele RUP_THER
   Le modele RUP_THER est un modele de comportement en cisaillement
   horizontal pour les rupteurs thermiques developpe par T.T.Huyen
   Nguyen, en cours de these au LMT Cachan. Il est utilisable avec
   les elements joints JOI1 orthotropes en 3D. Ce modele est concu
   pour des sollicitations sismiques. Il tient compte de la
   plastification des armatures d'acier contenues dans les rupteurs,
   ainsi que de l'endommagement du beton dans lequel les rupteurs
   sont ancres. Un phenomene d'hysteresis global est aussi considere.

   Parametres concernant le comportement de l'acier :
   'KA ' : raideur en cisaillement horizontal de la section
        totale de l'acier dans un rupteur (en N/m)
   'YA0 ' : limite elastique de le l'acier (en N)
   'ALPA', 'BETA' : parametres de l'ecrouissage cinematique de
        l'acier (sans unite)

   Parametres concernant le comportement du be©ton :
   'KB ' : raideur en cisaillement horizontal de la section
        de beton (en N/m)
   'YB0 ' : seuil d'endommagement du beton (en N.m)
   'C1 ', 'D1 ' : parametres de l'endommagement du beton
        (sans unite)
        l'endommagement s'ecrit:
        d = 1 - 1/(1 + C1*Y**D1)
   'ALPB', 'BETB' : parametres de l'ecrouissage cinematique
        du beton (sans unite)

   Modele DP_SOL
   Modele de plasticite Drucker-Prager avec loi d'ecoullement
   non associe et ecrouissage non lienaire.

     f(sig,q) = |sig_dev| - ((2/3)**0.5)*(SIGY - q(xi)) + ALPA*(tr(sig))
     g(sig)  = DELT*|sig_dev| + GAMA*(tr(sig))

     q(xi) = -(SIGI - SIGY)*(1 - exp(BETA*xi))

     'SIGY' Contrainte limite elastique
     'SIGI' Contrainte limite ultime a la saturation
     'ALPA' Pente du cone du critere DP
     'GAMA' 1ere parametre de la loi d'ecoullement
     'DELT' 2eme parametre de la loi d'ecoullement
     'BETA' vitesse de saturation

   Modele IWPR3D_SOL
   Modele de plasticite base sur le travaux de Prevost sur un modele
   de nested yield surface la loi est composee de 10 surface de charge
   à ecrouissage lineaire. La loi peut reppresenter l'anisotropie
   dans la phase plastique

     s = dev(sig) (partie deviatoire tenseur contrainte)
     p = tr(sig)/3 (contrainte moyenne)

     SURFACES DE CHARGE
       f_i(sig,q) = |s - (p - c)*alp_i| + ((2/3)**0.5)*m_i*(p - c)R_i(theta_i)

       i=1...10
       m_i angle du critere i dans le plan p-q (parametre materiaux)
       c cohesion
       alp_i back-stress du critere i
       R_i facteru R pour le critere i (anisotropie)
       theta_i angle de Lode critere i

       où:
       R_i = [2k]/[(1+k)-(1-k)*cos(3*theta_i)]
       cos(theta_i) = -(sqrt(6))*(n_i)³
       n_i = (s - (p - c)*alp_i)/|s - (p - c)*alp_i|

       k entre 1 et 0.75 pour k=1 no anuisotropie

     ELASTICITE NON LINEAIRE

       Ds = 2*G*De_el (De_el increment du tensuer de deformation deviatoire el
       Dp = K*De_vol_el (De_vol_el increment deformation volumique elastique)

       G = G0*a*[(p-c)/(pref-c)]^N
       K = K0*a*[(p-c)/(pref-c)]^N

       et

       K0 = E0/(3(1-2*nu))
       G0 = E0/(2(1+nu))
       E0 parametre materiau
       N parametre materiau (N=0 elasticite lineaire)
        N<1

     LOI ECOULEMENT
       Dep_pla = P_i*gam

       avec

       P_i = P_i' + P_i''*Id
       P_i' = Df_i/Ds
       P_i'' = A_i*[((eta/eta_car_i)² - 1)/((eta/eta_car_i)² + 1)]
       eta = (sqrt(3/2*s:s))/p
       eta_car_i = eta_i_c cos(3*theta_i) >=0
        eta_i_e cos(3*theta_i) < 0

       A_i parametre materiau (compris entre 0 et 1)
       eta_i_c pente surface caracteristique en compression du critere i
       eta_i_e pente surface caracteristique en extension du critere i

     LOI D' EVOLUTION DU BACK-STRESS
       Dalp_i = 2/3H_i(theta_i)*mu*gam
       mu tensor determine a partir de la regle d'ecrouissage de Mroz

       H_i = [((H_i_c - H_i_e)/2)cos(3*theta_i) + ((H_i_c + H_i_e)/2)]*[(p-c)/(p

       H_i_c Module plastique du critere i en compression
       H_i_e Module plastique du critere i en extension

     Le parametres materiaux du modele sont:

     'E0' Parametre E0
     'ALP0' Parametre a
     'C' Cohesion c
     'N1' Parametre N
     'PREF' Pression de reference pref (il peut etre egal -1.)
     'K1' parametre k

     'M1' pente critere 1
     'M2' pente critere 2
     'M3' pente critere 3
     'M4' pente critere 4
     'M5' pente critere 5
     'M6' pente critere 6
     'M7' pente critere 7
     'M8' pente critere 8
     'M9' pente critere 9
     'M10' pente critere 10

     'HC1' Module plastique en compression critere 1
     'HC2' Module plastique en compression critere 2
     'HC3' Module plastique en compression critere 3
     'HC4' Module plastique en compression critere 4
     'HC5' Module plastique en compression critere 5
     'HC6' Module plastique en compression critere 6
     'HC7' Module plastique en compression critere 7
     'HC8' Module plastique en compression critere 8
     'HC9' Module plastique en compression critere 9

     'HE1' Module plastique en extension critere 1
     'HE2' Module plastique en extension critere 2
     'HE3' Module plastique en extension critere 3
     'HE4' Module plastique en extension critere 4
     'HE5' Module plastique en extension critere 5
     'HE6' Module plastique en extension critere 6
     'HE7' Module plastique en extension critere 7
     'HE8' Module plastique en extension critere 8
     'HE9' Module plastique en extension critere 9

     'DA1' Parametre A_i critere 1
     'DA2' Parametre A_i critere 2
     'DA3' Parametre A_i critere 3
     'DA4' Parametre A_i critere 4
     'DA5' Parametre A_i critere 5
     'DA6' Parametre A_i critere 6
     'DA7' Parametre A_i critere 7
     'DA8' Parametre A_i critere 8
     'DA9' Parametre A_i critere 9

     'E_C1' pente surface caracteristique en compression critere 1
     'E_C2' pente surface caracteristique en compression critere 2
     'E_C3' pente surface caracteristique en compression critere 3
     'E_C4' pente surface caracteristique en compression critere 4
     'E_C5' pente surface caracteristique en compression critere 5
     'E_C6' pente surface caracteristique en compression critere 6
     'E_C7' pente surface caracteristique en compression critere 7
     'E_C8' pente surface caracteristique en compression critere 8
     'E_C9' pente surface caracteristique en compression critere 9

     'E_E1' pente surface caracteristique en extension critere 1
     'E_E2' pente surface caracteristique en extension critere 2
     'E_E3' pente surface caracteristique en extension critere 3
     'E_E4' pente surface caracteristique en extension critere 4
     'E_E5' pente surface caracteristique en extension critere 5
     'E_E6' pente surface caracteristique en extension critere 6
     'E_E7' pente surface caracteristique en extension critere 7
     'E_E8' pente surface caracteristique en extension critere 8
     'E_E9' pente surface caracteristique en extension critere 9

     OBS: Le dernier critere (10) reppresente la surface ultime

   Modele LIAISON_ACBE

   'PULO' : relation d'adherence entre le glissement tangentiel
        (abscisse) et la contrainte tangentielle d'adherence
        (ordonnee) (type EVOLUTION)
   'KN' : raideur normale de l'element d'interface (valeur
        recommandee 1.e15 Pa.m-1)
   'KS' : raideur tangentielle de l'element d'interface (valeur
        recommandee egale a la pente initiale de la relation
        d'adherence PULO)
   'SECT' : section de l'element d'acier sur lequel s'appuie
        l'element d'interface

   Modele OUGLOVA
   Modele elasto-plastique endommageable de Lemaitre modifie afin de
   tenir compte de la corrosion des armatures.

   'SIGY' : Contrainte limite elastique
   'K' : Pente ecrouissage
   'm' : Exposant ecrouissage
   'Tc' : Taux de Corrosion
   'Dc' : Endommagement critique

   Modele NORTON
   Modele de fluage de Norton uniaxial (pour les elements finis de poutres a fibre).
   Les parametres a renseigner sont identiques a ceux de la version pour les elements massifs
   (voir dans la categorie FLUAGE) :
   'AF1' 'AF2' 'AF3' 'SMAX'

   Modele POLYNOMIAL
   Modele de fluage polynomial uniaxial (pour les elements finis de poutres a fibre).
   Les parametres a renseigner sont identiques a ceux de la version pour les elements massifs
   (voir dans la categorie FLUAGE) :
   'AF0' 'AF1' 'AF2' 'AF3' 'AF4' 'AF5' 'AF6' 'SMAX'

   Modeles BLACKBURN et BLACKBURN_2
   Modeles de fluage de Blackburn uniaxiaux (pour les elements finis de poutres a fibre).
   Les parametres a renseigner sont identiques a ceux de la version pour les elements massifs
   (voir dans la categorie FLUAGE) :
   'AF1' 'AF2' 'AF3' 'AF4' 'RF1' 'RF2' 'RF3' 'RF4' 'BF1' 'BF2' 'BF3' 'BF4' 'BF5' 'SMAX'

   Modele LEMAITRE
   Modele de fluage de Lemaitre uniaxial (pour les elements finis de poutres a fibre).
   Les parametres a renseigner sont identiques a ceux de la version pour les elements massifs
   (voir dans la categorie FLUAGE) :
   'AF1' 'AF2' 'AF3' 'AF4' 'KXF' 'KYF' 'SMAX'

   FUSION :

   Pour tous les modeles de plasticite, l'option FUSION met a zero les
   variables internes du modele si la temperature au point d'integration
   est superieure a la temperature de fusion, donnee par :

   'TFUS' : FLOTTANT, temperature de fusion du materiau.

PART{MECANIQUE ENDOMMAGEABLE}
   | Noms des parametres pour un materiau ENDOMMAGEABLE |

  Modele MAZARS

      Il s'agit d'un modele d'endommagement scalaire isotrope pour le
    beton. (Ce modele est utilisable en non local). Voir la preocedure
    IDENTI pour l'aide a l'identification des parametres.

   'KTR0' : seuil en deformation pour la traction (1.D-04)
   'ACOM' : parametre pour la compression (1.4)
   'BCOM' : parametre pour la compression (1900.)
   'ATRA' : parametre pour la traction (0.8)
   'BTRA' : parametre pour la traction (17000)
   'BETA' : correction pour le cisaillement (1.06)

  Deux lois d'evolution complementaires sont proposees pour le
  comportement en traction de facon a pouvoir utiliser une
  regularisation de type "HILLERBORG" :

  Pour -10 < ATRA <0 evolution exponentielle :
        DT=UN - KTR0/EPSTILD*EXP(BTRA*(KTR0-EPSTILD))
  Dans ce cas on peut calculer BTRA en fonction de GF :
        BTRA=H*YOUN*KTR0/(GF-H(KTR0**2/(2*YOUN))) avec
        H: Taille de l'element fini
 (Voir egalement le cas test mazars2
        et http://web.univ-pau.fr/~clb/HDR/hdrnew.pdf)

  Pour ATRA < -10 : evolution lineaire
        DT=UN - KTR0*(BTRA - EPSTILD)/EPSTILD/(BTRA - KTR0)
        BTRA represente alors la deformation equivalente pour
        laquelle l'endommagement atteint 1.

   Modele UNILATERAL

      Il s'agit d'un modele d'endommagement scalaire isotrope a deux
      variables d'endommagement avec gestion des refermetures de
      fissures.

   'YS1 ' : seuil en energie pour la traction (2.5 E-4 MPa)
   'YS2 ' : seuil en energie pour la compression (1.5 E-3 MPa)
   'A1 ' : parametre pour la traction (5000 MPa)
   'B1 ' : parametre pour la traction (1.5)
   'A2 ' : parametre pour la compression (10 MPa)
   'B2 ' : parametre pour la compression (1.5)
   'BET1' : gere les deformations inelastiques en traction (1MPa)
   'BET2' : gere les deformations inelastiques en compression (-40MPa)
   'SIGF' : contrainte de refermeture de fissures (-3.5MPa)

   Modele ROTATING_CRACK

      Il s'agit d'un modele de type "smeared crack" dans lequel la
    direction de fissuration change a chaque pas. Seul l'endommagement
    du materiau par traction est decrit.

   'EPCR' : deformation au debut de l'endommagement dans un essai
        de traction uniaxiale
   'MUP ' : rapport du module tangent au module d'Young, la courbe
        de traction uniaxiale etant modelisee de facon bilineaire
   Modele SIC_SIC

     Il s'agit d'un modele d'endommagement scalaire anisotrope specifique
     pour le composite ceramique SiC/SiC. Ce modele est utilisable
     seulement en 3D massif. L'endommagement est decrit par trois
     variables scalaires correspondant aux trois directions d'orthtropie
     du materiau. Les donnees materiau sont fournies a l'aide de la
     directive ORTHOTROPE. Les parametres qui suivent servent a decrire
     les lois d'endommagement.

     G1DC,G1Y0,G1YC,G1P: pour la premiere direction
     G2DC,G2Y0,G2YC,G2P: pour la deuxieme direction
     G3DC,G3Y0,G3YC,G3P: pour la troisieme direction

     AXEP: paramatre optionel qui specifie laquelle des trois directions
     d'orthotropie coa¯ncide avec l'epaisseur (doit etre compris
     entre 1 et 3, par defaut = 3)

    - Equations du modele:

     Notations:

        S : tenseur des contraintes
        E : tenseur des deformations
        C : tenseur de compliance
        Ki : tenseurs caracterisitiques du materiau
        (obtenus a partir du tenseur de Hook)
        h(-Ei): fonction de Heavyside,
        h=0 si -Ei<0
        h=1 si -Ei>0
        Pi : tenseurs lies aux directions d'endommagement
        di : variables d'endommagement

     Relation contraintes-deformations:

      S= C x E - Ceff x E

      Ceff= di*Ki-di*h(-Ei)(Pi x Ki x Pi) (Somme sur i=1,3)

     Force thermodynamique liee a l'endommagement:

      Yi= 1/2*E x Ki x E

      Yeq= <y1> + <y2> + <y3>
        (<x> = partie positive de x)

     Lois d'evolution de l'endommagement:

      di=DiDC*(1-EXP-(<(Yeq**1/2-GiY0)/GiYC>**GiP)) (i=1,3)

     Ce modele a ete developpe a l'ONERA. Pour plus de detail sur le
     modele et son idetification, voir les rapports du Project Brite Euram
     BE-5462.

     L'identification du modele a ete conduite sur un composite 2D
     produit par la SEP. Les parametres des lois d'endommagement pour ce
     composite sont:

     GiDC : 0.6 (i=1,3)
     GiY0 : 1.3
     GiYC : 4
     GiP : 1

   Modele VISCOHINTE

    Les lois du modele sont les meme que pour le modele HINTE. Seules
    la variation de l'endommagement est modifiee.

    Si d2 <1 et Y<YR alors :
        d2/dt = k <w(Y) -d2>**M , w(Y)<1
        d1/dt = d2/dt
        sinon : d2 = 1

    pour des taux d'endommagement faibles le modele se comporte comme
    le modele HINTE

    Les parametres sont :

    'Y0' : seuil d'endommagement
    'YC' : energie critique d'endommageme
    'GAM1' : parametres de couplage entre energies de cisaillement
        et d'ouverture
    'AL' : gouverne la forme et le lieu de rupture en mode mixte
    'NN' : caracterise la plus ou moins grande fragilite de
        l'interface (plus N est grand, plus l'interface
        est fragile)
    'DCRI' : permet de simuler une rupture fragile(par defaut DCRI=1)
    'KS' : rigidites d'interface en cisaillement
    'KN' : rigidites d'interface normale
    'MM' : parametre de l'effet de retard ( par defaut=1)
    'KK' : temps caracteristique

   Modele MVM

   * C'est un modele d'endommagement nonlocal isotrope pour les materiaux
       quasifragiles. Les equations du modele sont
       (voir les references [1] et [2]) :

     --> Notation: I1 premier invariant du tenseur des contraintes
        J2 deuxieme invariant du tenseur des contraintes
        D endommagement
        Y variable d'etat local
        Ytil variable d'etat nonlocal
        B1 parametre du materiau
        B2 parametre du materiau
        Y0 taux d'endommagement
        k rapport des resistances en compression et en traction
        nu coefficient de Poisson

     --> Loi des variables d'etat

        (k-1)*I1) 1 (k-1)*I1 12*k*J2
        Y = ------------ + ---*sqrt( ( -------- )^2 + (--------) )
        (2*k*(1-2*)) 2*k 1-2*nu (1+nu)^2

     --> Loi d'endommagement. Deux choix :

        Y0*(1-A)
        1. Loi exponentielle : D = 1 - -------- - B2*exp(-B1*(Ytil-Y0))
        Ytil
        1
        2. loi polynomiale : D = 1 - -----------------------------
        1+B1*(Ytil-Y0)+B2*(Ytil-Y0)^2

   Les parametres sont :

   'Y0' : seuil d'endommagement
   'B1' : parametre associe a la pente au sommet de la courbe contraintes
        deformation
   'B2' : parametre associe a la contrainte residuelle de la courbe
        contrainte deformation
   'RATI' : rapport des resistances en compression et en traction
   'LOI ' : 1 si la loi d'endommagement est exponentielle
        0 si la loi d'endommagement est polynomial

   * References:

   [1] Peerlings, R.H.J., de Borst, R., Brekelmans, W.A.M. and Geers,
       M.D. (1998), Gradient-enhanced damage modelling of concrete
       fracture, Mechanics of Cohesive-Frictional Materials, 3,
       323-342.

   [2] Rodriguez-Ferran A., Huerta A. (2000), Error estimation and
       adaptivity for nonlocal damage models. International Journal of
       Solids and Structures, 37, 7501-7528.

  Modele SICSCAL :
     Modele scalaire d'endommagement pour le composite tisse SiCf/SiC
     developpe a l'ONERA avec 3 variables d'endommagement correspondant
     a des fissures dans les plans perpendiculaires aux directions des
     fibres, d1 et d2, et dans le plan du pli, d3.
     La loi de comportement ainsi que sa validation sont detailles dans
     la reference SEMT/LM2S/05-034. Les directions d'anisotropie sont
     definies telles que les fibres sont selon les directions 1 et 2.
     La loi de comportement s'exprime d'apres:
     E = Seff S + Eth + Er + Es
     Oa¹ E est la deformation, S, la contrainte, Seff, le tenseur des
     souplesses effectives. Eth, Er et Es sont respectivement la
     contrainte thermique, residuelle et stockees.
     Seff = S0 + (nui di Hi0) (somme sur i=1,3)
     S0 : Tenseur des souplesses non endommage.
     Hi0 : Tenseur d' ordre 4 representant l'effet du domage di sur la
     souplesse
     Hi0 est calcule d'apres S0 et les coefficients HiN, HiHP and HiP
     Les noms des parametres a definir sont: H1N, H1HP, H1P, H2N, H2HP,
     H2P, H3N, H3P.
     Les valeurs par defaut sont:
     h1n=1, h1hp =0.7, h1p=0.45
     h2n=1, h2hp =0.7, h2p=0.45
     h3n=1, h3p=0.7
     Les indices d'activation nui sont calcules avec les parametres
     DTAL, TER0, SIF1, SIF2, SIF3, AIF1, AIF2, AIF3.
     Les valeurs par defaut sont SIF1=SIF2=SIF3 =3.10-4 et
     AIF1=AIF2=AIF3=0.
     Le calcul des deformations residuelles necessite les parametres:
     ETA1, ETA2 et ETA3. Les valeurs par defaut sont ETA1=ETA2= 0.1,
     ETA3=0.
     Les lois d'evolution de l'endommagement sont exprimees avec les
     parametres :DCT1, DCT2, DCT3, DCN1, DCN2, DCN3, YCT1, YCT2, YCT3,
     YCN1,YCN2, YCN3, Y01T, Y02T, Y03T, Y01N, Y02N, Y03N, PT1, PT2,
     PT3, PN1, PN2, PN3.
     Les valeurs par defaut sont DCT1=DCT2=DCT3=DCN1=DCN2=DCN3=4,
     YCT1=YCT2=YCT3=YCN1=YCN2=YCN3=1870,83(Pa**0.5),
     Y01T=Y02T=31.6(Pa**0.5), Y03T=Y01N=Y02N=Y03N=173.2(Pa**0.5),
     PT1=PT2=1.2, PT3=PN1=PN2=PN3=1.
     Un parametre de couplage B doit aussi etre defini.
     Sa valeur par defaut est B=1.

   Modele SICTENS:
     Modele pseudo-tensoriel d'endommagement pour le composite tisse
     SiCf/SiC developpe a l'ONERA avec 5 variables d'endommagement
     correspondant a des fissures dans les plans perpendiculaires aux
     deux directions des fibres, d1 et d2, dans le plan du pli, d3 et
     dans les plans perpendiculaires aux directions a + et - 45Â° des
     fibres, d4 et d5. La loi de comportement ainsi que sa validation
     sont detailles dans la reference SEMT/LM2S/05-034.
     Les directions d'anisotropie sont definies telles que les fibres
     sont selon les directions 1 et 2.
     La loi de comportement s'exprime d'apres:
     E = Seff S + Eth + Er + Es
     Oa¹ E est la deformation, S, la contrainte, Seff, le tenseur des
     souplesses effectives. Eth, Er et Es sont respectivement la
     contrainte thermique, residuelle et stockee.
     Seff = S0 + (nui di Hi0) (somme sur i=1,5)
     S0 : Tenseur des souplesses non endommage.
     Hi0 : Tenseur d'ordre 4 representant l'effet du dommage di sur la
     souplesse
     Hi0 est calcule d'apres S0 et les coefficients HiN, HiHP et HiP.
     Les noms des parametres a definir sont : H1N, H1HP, H1P, H2N,
     H2HP, H2P, H3N, H3P, H4N, H4HP, H4P, H5N, H5HP, H5P.
     Les valeurs par defaut sont:
     h1n=1, h1hp =0.7, h1p=0.45
     h2n=1, h2hp =0.7, h2p=0.45
     h3n=1, h3p=0.7
     h4n=1, h4hp =0.7, h4p=1.2
     h5n=1, h5hp =0.7, h5p=1.2
     Les indices d'activation nui sont calcules avec les parametres
     DTAL, TER0, SIF1, SIF2, SIF3, SIF4, SIF5, AIF1, AIF2, AIF3,
     AIF4, AIF5.
     Les valeurs par defaut sont SIF1=SIF2=SIF3=SIF4=SIF5=3.10-4,
     AIF1=AIF2=AIF3=0.5 et AIF4=AIF5=1.
     Le calcul des deformations residuelles necessite la connaissance
     des parametres ETA1, ETA2, ETA3, ETA4 et ETA5. Les valeurs par
     defaut sont: ETA1=ETA2=0.1, ETA3=0, ETA4=ETA5=0.1
     Les lois d'evolution de l'endommagement sont exprimees avec les
     parametres :
     DC1, DC2, DC3, DC4, DC5, YC1, YC2, YC3, YC4, YC5, Y01, Y02, Y03,
     Y04, Y05, PY1, PY2, PY3, PY4, PY5.
     Les valeurs par defaut sont :
     DC1=DC2=DC3=DC4=DC5=4, YC1= YC2=YC3=1870,83 (Pa**0.5),
     YC4= YC5=3464.1 (Pa**0.5), Y01=Y02=Y03=173.2 (Pa**0.5),
     Y04=Y05=173.2 (Pa**0.5), PY1= PY2=PY3=1., PY4, PY5=1.2.
     Les parametres de couplage B1, B2 and B3 doivent aussi etre
     definis.
     Leur valeur par defaut est fixee a 1.

   Modele DAMAGE_TC
     Les donnees a introduire en plus des parametres d'elasticite
     sont les suivantes:

     'HLEN' : longueur caracteristique (cf. maillage)
     'GVAL' : energie de fissuration (300)
     'FTUL' : Limite en traction (3.6e6)
     'REDC' : Coefficient d'abaissement (1.7e6)
     'FC01' : Limite elastique en compression (-25e6)
     'RT45' : Rapport en comp. bi-axiale (1.18)
     'FCU1' : Contrainte au pic de compression (-42e6)
     'STRU' : Deformation ultime en compression (-0.015)
     'EXTP' : Deformation de reference en compression (-0.001)
     'STRP' : Contrainte de reference en compression (-22e6)
     'EXT1' : Deformation point 1 (-0.006)
     'STR1' : Contrainte point 1 (-35e6)
     'EXT2' : Deformation point 2 (-0.008)
     'STR2' : Contrainte point 2 (-22e6)
     'NCRI' : indicateur 1 : post pic en traction exponentiel
        2 : post pic en traction lineaire

   Modele DESMORAT
     Les donnees a introduire en plus des parametres d'elasticite
     sont les suivantes:

     'K0' : seuil en deformation pour la traction (5.D-05)
     'A' : Parametre d'endommagement A (5.D03)
     'a' : Parametre d'endommagement de l'ordre de grandeur des
        deformations atteintes en compression (2.93D-4)
     'etaC' : Parametre de sensibilite hydrostatique en compression (0.)
     'etaT' : Parametre de sensibilite hydrostatique en traction (3.)
     'Dc' : Valeur critique de l'endommagement pour la gestion
        de la rupture (0.9 a 0.999)

     ne pas oublier de declarer dans la table de PASAPAS :
        tab1.'MOVA' = 'D11';

    Modele DRUCKER_PRAGER_2
      Les donnes a introduire en plus des parametres d'elasticite sont
      les suivantes :

      'GF' : enargie de fissuration
      'LTR' : resistance en traction
      'LCS' : resistance en compression uniaxiale
      'LBI' : resistance en compression biaxiale
      'SIGY' : limite d'elasticite en compression uniaxiale
      'EPM' : deformation au pic en compression uniaxiale
      'EPU' : deformation ultime en compression uniaxiale
      'LCAR' : longueur caracteristique

   Modele FATSIN

   * Ce modele d'endommagement nonlocal isotrope [1,2] est dedie aux mater
       testes sous des chargements sinusoidaux de fatigue. En tout
       point, les champs mecaniques de deplacement, de deformation et de cont
       sont pseudo-sinusoa¯daux et peuvent s'ecrire sous la forme generique :
        x= x_a * sin (2*pi/T * N/T)
       oa¹ x_a est l'amplitude de la grandeur x, T la periode et N le nombre d
       Le modele permet de calculer l'endommagement atteint apres l'applicatio
       de N cycles de chargements. Base sur l'elasticite isotrope (module d'Y
       et Coeff. de Poisson Nu), l'integration temporelle de l'endommagement es
       realisee a l'echelle macroscopique des cycles. Le chargement de la str
       est statique de valeur l'amplitude de la sollicitation appliquee (positi
       sans decrire le cycle de sinus.

       Les equations du modele sont (voir les references [1] et [2]) :

     --> Notation: Eps_eq : Amplitude de deformation equivalente
        Eps_moy : Moyenne non-locale integrale de Eps_eq
        depend de la longueur caracteristique lc
        (cf. 'NLOC')
        Sig_i : Amplitude de contrainte principale
        <x> : Partie positive de x ( <x>=0.5*[x+abs(x)])
        E_0 : Module d'Young du materiau vierge (D=0)
        N : Nombre de cycles
        D : Endommagement atteint au cycle N

     --> Deformation equivalente Eps_eq
        (\ ( < Sig_i> ) )
        Eps_eq = sqrt ( \ ( ----------- )^2 )
        ( / ( E_0 * (1-D) ) )
        (/___ )

     --> Loi d'endommagement : Expression du taux d'endommagement par cycle dD/d
        d'expression generale

        Eps_moy ^ (BETA+1) - KTR0 ^ (BETA+1)
        dD/dN = f(D) --------------------------------------------------------
        (BETA+1)

     Deux choix possibles de la fonction f(D) :

        1. Loi classique L2R ( Reference [3])

        f(D) = C D^ALFA

        2. loi phenomenologique L3R (Reference [1,2]) plus specifiquement
        les betons bitumineux

        ALFA2 ( D ) ( ( D )
        f(D) = -------------- * ( ----- ) ^ (1-ALFA3) * exp ( (-------)^(ALFA3
        ALFA1 * ALFA3 ( ALFA2 ) ( ( ALFA2 )

   Les parametres sont :

   'KTR0' : seuil d'endommagement lie a la limite d'endurance
   'BETA' : parametre associe a la pente p de la droite de fatigue
        (log(Nf) vs log(Eps_a)) suivant la relation (beta=-(p+1)
   'LOI ' : 2 si la loi d'endommagement est L2R
        3 si la loi d'endommagement est L3R
   Dans le cas de la loi L2R
   'ALFA' : parametre lie a la concavite de la courbe d'endommagement
   'C ' : parametre associe a la duree de vie

   Dans le cas de la loi L3R
   'ALFA1' : parametre associe a la duree de vie
   'ALFA2' : parametre pilotant le niveau d'endommagement pour lequel le taux
        d'endommagement diminue puis re-augmente
   'ALFA3' : parametre lie a la concavite de la courbe d'endommagement

   Remarque : Il est conseille d'attribuer la valeur 0. aux parametres non uti

   * References:

        References:
     [1] D. Bodin, (2002), Modele d'endommagement cyclique - Application aux En
        These de Doctorat. Ecole Centrale de Nantes. p. 187.
        (http://www.lcpc.fr/fr/recherches/th_soutenues/index1.dml)

     [2] D. Bodin, G. Pijaudier-Cabot, C. de La Roche, J.-M Piau and A. Chabot,
        A Continuum Damage Approach to Asphalt Concrete Fatigue Modelling, Jour
        Engineering Mechanics, ASCE, vol. 130 (6), pp. 700-708.

     [2] Paas, R. H. J. W., Scheurs, P. J. G., and Brekelmans, W. A. M. (1993).
        continuum approach to brittle and fatigue damage: Theory and numerical
        procedures. Int. J. Solids Struct., 30~4!, 579-599.

    Modele RICRAG
      Ce modele [1,2] est à utiliser pour des chargements monotones et
      cyclique niveau de charge du fait de la prise en compte partielle
      de l'effet unilateral. Il peut etre utilise avec l'approche
      non-local telle qu'elle implantee Cast3M. Les parametres à rentrer,
      en plus des caracteristiques elastiques sont les suivants :

      'FT' : resistance equivalente en traction (3.6e6 )
      'ALDI' : fragilite en traction uniaxiale (1.0e-2)
      'ALIN' : fragilite en compression uniaxiale (5.0e-4)
      'GAM1' : module d'ecrouissage cinematique 1 (7.0e7 - 7.0e9)
      'A1' : module d'ecrouissage cinematique 2 (7.0e-7)

   * References:
     [1] B. Richard, F. Ragueneau, C. Cremona, L. Adelaide. (2010). Isotropic
        continuum damage mechanics for concrete under cyclic loading: stiffness
        recovery, inelastic strains and frictional sliding. Engineering Fractur
        Mechanics. 77:1203-1223.

     [2] L. Adelaide, B. Richard, F. Ragueneau, C. Cremona. (2010). Thermodynami
        admissibility of a set of constitutive equations coupling elasticity,
        isotropic damage and internal sliding. Comptes Rendus Mecanique. 338:1

    Modele GLRC_DM
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

      'YOUF' : module d'Young equivalent en partie flexion
      'NUF ' : coefficient de Poisson "quivalent en partie flexion
      'GAMT' : parametre endommagement de traction en membrane
      'GAMC' : parametre endommagement de compression en membrane
      'GAMF' : parametre endommagement en partie flexion
      'SEUI' : seuil initial d'activation de l'endommagement
      'ALF ' : coefficient de couplage des endommagement membrane/flexion

      Il peuvent etre identifies à l'aide de la procedure IDENTI de Cast3M
      [1] à partir de donnees ayant une signification physique.

   * References :
     [1] B. Richard, N. Ile. (2012). Influence de la fissuration du beton
        sur les mouvements transferes - phase 2 : implantation dans Cast3M
        d'un modele simplifie de beton arme et validation sur les element
        de structures. Rapport technique CEA RT12-011/A.

    Modele EFEM
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

      'FT ' : Limite en traction
      'XNX ' : CHAMELEM initial des normales aux fissures (selon la premiere coo
      'XNY ' : CHAMELEM initial des normales aux fissures (selon la seconde coor
      'IND1' : CHAMELEM (0 ou 1) ; 0 si non fissure, 1 sinon

    Modele RICBET
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

      'FT ' : resistance en traction (3.6E6)
      'GAM1' : module d'ecrouissage cinematique 1 (5E9)
      'A1 ' : module d'ecrouissage cinematique 2 (8E-6)
      'ALDI' : fragilite en traction (6.0E-3)
      'SREF' : contrainte de fermeture des fissures (-3.2E6)
      'AF ' : parametre critere compression 1 -
        reponse compression biaxiale (0.7)
      'AG ' : parametre critere compression 1 -
        dilatance (0.6)
      'BF ' : parametre critere compression 2 -
        reponse compression biaxiale (0.3)
      'BG ' : parametre critere compression 2 -
        dilatance (0.45)
      'AC ' : evolution plasticite en compression 1 (3.2E10)
      'BC ' : evolution plasticite en compression 2 (700)
      'SIGU' : contraintes asymptotique en compression (-4E6)
      'FC ' : contrainte d'activation de la plasticite
        en compression (6E6)

   * References:
     [1] B. Richard, F. Ragueneau (2012). 3D modelling of concrete for
        earthquake analysis: damage mechanics and plasticity coupling.
        WCCM 2012, Sao Paulo, Brazil.

     [2] B. Richard, F. Ragueneau (2012). Continuum damage mechanics based
        model for quasibrittle materials subjected to cyclic loadings:
        formulation, numerical implementation and applications.
        Engineering Fracture Mechanics. In press.

    Modele RICCOQ
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

      'FT ' : Resistance en traction (3.6E6)
      'FC ' : Seuil initial en compression (10E6)
      'EPUT' : deformation limite en traction (according to the mesh)
      'EPUC' : deformation limite en compression (according to the mesh)

   * References:
     [1] B. Richard (2012). SERIES/ENISTAT Project. Preliminary
        numerical time history analysis. CEA Technical report
        RT-12-013/A.

    Modele CONCYC
      Les parametres à rentrer, en plus des caracteristiques elastiques,
      sont les suivants :

      'NEND ' : indicateur pour choisir la maniere de gerer l
        endommagement
        = 1 : type RICRAG [1]
        = 2 : consolidation modifiee [2]
        = 3 : critere modifie [2]
      'SIGT ' : resistance en traction (3.6 MPa)
      'ATRA ' : parametre lie a l energie de fissuration (0.004)
      'BTRA ' : parametre lie la formulation de la loi d endommagement [2]
        = si NEND = 1 : 0.0
        = si NEND = 2 : 4.5
        = si NEND = 3 : 0.31
      'QP ' : "vitesse" de refermeture de fissure (6.5)
      'CF ' : coefficient de frottement des fissures (2.89)

   * References:
     [1] B. Richard, F. Ragueneau, C. Cremona, L. Adelaide. (2010). Isotropic
        continuum damage mechanics for concrete under cyclic loading: stiffness
        recovery, inelastic strains and frictional sliding. Engineering Fractur
        Mechanics. 77:1203-1223.

     [2] M. Vassaux. (2014) Comportement mecanique des materiaux
        quasi-fragiles sous sollicitations cycliques: de l’experimentation
        numerique au calcul de structures. These de Doctorat.
        Ecole Normale Superieure de Cachan.

   FUSION :

   Pour tous les modeles d'endommagement, l'option FUSION met a zero
   les variables internes du modele si la temperature au point
   d'integration est superieure a la temperature de fusion, donnee par :

   'TFUS' : FLOTTANT, temperature de fusion du materiau.

PART{MECANIQUE FLUAGE}
   | Noms des parametres pour un materiau en FLUAGE |

   Les parametres qui suivent sont a definir EN PLUS des parametres
   relatifs au comportement elastique. Les modeles de fluage disponibles
   sont decrits ci-dessous, par l'equation modelisant le resultat d'un
   essai de fluage a contrainte constante, avec les notations suivantes

        ef deformation de fluage equivalente
        s contrainte equivalente
        t temps

   Seul les modeles polynomial, CCPL, X11 et SODERBERG sont decrits par le
   developpement de la vitesse de fluage vf en fonction de la contrainte
   equivalente.

   Dans les calculs, l'hypothese d'un ecrouissage par la deformation
   est faite.

   Modele de fluage de NORTON :
        ef = AF1 * ( s**AF2 ) * ( t**AF3 )

   Les parametres a introduire sont 'AF1 ','AF2 ','AF3 ', ainsi qu'une
   contrainte de reference 'SMAX' (egale par defaut au module d'Young
   fois 1.E-3).

   Modele de fluage de BLACKBURN :
        ef = A * ( 1 - exp(-R*t) ) + B * t

   avec A = AF1 * exp(AF2*s) + AF3 * s**AF4
        R = RF1 * exp(RF2*s) + RF3 * s**RF4
        B = BF1 * (sinh(BF2*s))**BF3 + BF4 * exp(BF5*s)

   Les parametres a introduire sont 'AF1 ' a 'AF4 ', RF1 ' a 'RF4 ',
   et 'BF1 ' a 'BF5 ', ainsi qu'une contrainte de reference 'SMAX'
   (egale par defaut au module d'Young fois 1.E-3).

   Modele de fluage de BLACKBURN_2:
        ef = A * ( 1 - exp(-R*t) ) + B * t

   avec A = AF1 * exp(AF2*s) + AF3 * s**AF4
        R = RF1 * exp(RF2*s) + RF3 * s**RF4
        B = BF1 * (sinh(BF2*s))**BF3 + BF4 * s**BF5

   Les parametres a introduire sont 'AF1 ' a 'AF4 ', RF1 ' a 'RF4 ',
   et 'BF1 ' a 'BF5 ', ainsi qu'une contrainte de reference 'SMAX'
   (egale par defaut au module d'Young fois 1.E-3).

   Modele de fluage RCC-MR pour acier 316-SS :
        ef = AF1 * ( s**AF2 ) * ( t**AF3 ) si t < TF
     et ef = BF1 * ( s**BF2 ) si t > TF

   avec TF = TF1 * ( s**TF2 )

   Les parametres a introduire sont 'AF1 ' a 'AF3 ','BF1 ', 'BF2 ',
   'TF1 ', 'TF2 ', ainsi qu'une contrainte de reference 'SMAX' (egale
   par defaut au module d'Young fois 1.E-3).

   Modele de fluage RCC-MR pour acier 304-SS :
        ef = A1 * ( 1 - e**(-R*t) ) + A2 * ( 1 - e**(-S*t) ) + B * t

   avec: B = BF1 * (sinh(BF2*s/BF3))**BF3
        R = RF1 * (sinh(RF2*s/RF3))**RF3
        A1 = AF1 * B / R
        S = ( SF1 / RF1 ) * R
        A2 = AF2 + AF3*s si s > SF2 , 0. sinon

   Les parametres a introduire sont 'AF1 ' a 'AF3 ','BF1 ' a 'BF3 ',
   'RF1 ' a 'RF3 ', 'SF1 ','SF2 ', ainsi qu'une contrainte de reference
   'SMAX' (egale par defaut au module d'Young fois 1.E-3).

   Modele de fluage de LEMAITRE :
        ef = AF1 * ( X**AF2 + Y )

   avec: dX/dt = ( s / KXF )**( AF3 / AF2 ) * ( AF4**(1/AF2 ) )
        dY/dt = ( s / KYF )**AF3 * AF4

   Les parametres a introduire sont 'KXF ','KYF ','AF1 ','AF2 ','AF3 ',
   'AF4 ', ainsi qu'une contrainte de reference 'SMAX' (egale par defaut
   au module d'Young fois 1.E-3).

   Modele de fluage POLYNOMIAL :
        vf = AF0 + AF1*s**AF2 + AF3*s**AF4 +AF5*s**AF6

   Les parametres a introduire sont 'AF0 ','AF1 ','AF2 ','AF3 ','AF4 ',
   'AF5 ','AF6 ', ainsi qu'une contrainte de reference 'SMAX' (egale par
    defaut au module d'Young fois 1.E-3).

   Modele de fluage CERAMIQUE :
    Au dessus de la temperature de transition , le materiau flue
    selon la loi de Norton:
        ef = AF1* ( s**AF2 ) * ( t**AF3 )

    Les trois premiers parametres a introduire sont 'AF1 ','AF2 ','AF3 '
    , ainsi qu'une contrainte de reference 'SMAX'
    (egale par defaut au module d'Young fois 1.E-3).

   En dessous de la temperature de transition , le materiau se comporte
   selon le modele d'Ottosen :

   ('LTR') : limite en traction
        (par defaut YOUN*1.2E-4)
   ('GFTR') : taux de restitution d'energie
        (nomme aussi energie de fissuration)
        (par defaut LTR*3.9E-5, mais cette valeur correspond
        a des unites SI)
   ('GS') : module traduisant la perte de resistance au cisaillement
        d'une fissure avec son ouverture (usuellement compris
        entre 2 et 6 Mpa et par defaut YOUN*1.8E-4)
   ('BTR') : fraction non recouvrable de l'ouverture d'une fissure.
        (par defaut 0.2)

   Dans un deuxieme temps, il faut obligatoirement adjoindre au MCHAML
   de sous-type CARACTERISTIQUES construit par l'operateur MATE, le
   MCHAML resultat de l'operateur TAILLE applique au modele de calcul.

   Par ailleurs en deformations planes et en axisymetrique on peut
   definir en plus :

   ('EPSR') : deformation a rupture dans la direction normale au plan
        de representation.

  Les parametres specifiques au modele sont :

    'TTRA' : Temperature de transition
    'ENDG' : Deformation totale au dela de laquelle on a perte de
        la rigidite des elements en fluage

    Modele de fluage de COMETE :

        ef = AF1 * s ** AF2 * t ** AF3
        + BF1 * s ** BF2 * (BF3 ** BF5) * t ** BF4

    Les parametres a introduire sont 'AF1 ' a 'AF3 ', BF1 ' a 'BF5 ',
    ainsi qu'une contrainte de reference 'SMAX' (egale par defaut au
    module d'Young fois 1.E-3).

    Modele de fluage de CCPL :

        vf = (1 + AL1 * FII) * min (max(vf1,vf2) , vf3)
        + DF1 * s ** DF2 * FII * DF3

    avec :
    vf1 = AF1 * s ** AF2 * AF3
    vf2 = BF1 * s ** BF2 * BF3
    Vf3 = CF1 * s ** CF2 * CF3

    Les parametres a introduire sont 'AF1 ' a 'AF3 ', 'BF1 ' a 'BF3 ',
    'CF1 ' a 'CF3 ', 'DF1 ' a 'DF3 ', 'AL1 ', 'FII 'ainsi qu'une
    contrainte de reference 'SMAX' (egale par defaut au module d'Young
    fois 1.E-3).

     Modele de fluage de SODERBERG :

        ef = vs * t + EF * (1-exp(-R t))
        et
        vs = (1 + AL1 * FII) * min (max(vf1,vf2) , vf3) +
        DF1 * s ** DF2 * FII * DF3

     avec :
     vf1 = AF1 * s ** AF2 * AF3
     vf2 = BF1 * s ** BF2 * BF3
     Vf3 = CF1 * s ** CF2 * CF3

     EF = (EF1 * exp (EF2 * s)) + EF3
     R = (RF1 + RF2 * s) ** RF3

     Les parametres a introduire sont 'AF1 ' 'AF3 ', 'BF1 ' 'BF3 ',
     'CF1 ' 'CF3 ', 'DF1 ' 'DF3 ', 'AL1 ', 'FII ', 'EF1 ', 'EF2 ', 'EF3 ',
     'RF1 ', 'RF2 ', 'RF3 ', ainsi qu'une contrainte de reference 'SMAX'
     (egale par defaut au module d'Young fois 1.E-3).

    Modele de fluage de X11 :

        vf = vs + (vp - vs) * exp(-ef/E0)

    avec :
    vp = vp0 * vpf
    vs = vs0 * vsf

    E0 = EP01 * TANH (EP02 * s)
    vp0 = VP01 * SINH (VP02 * s)
    vs0 = VS01 * SINH (VS02 * s)
    vpf = VPF0 * exp (-VPF1 * FII) + (1 - VPF0)*exp(-VPF2 * FII)
    vsf = (1 - VSF0)*exp(-VSF1 * FII) + VSF0

    Les parametres a introduire sont 'EP01' a 'EP02', 'VP01' a 'VP02',
    'VS01' a 'VS02', 'VPF0' a 'VPF2', 'VSF1' a 'VSF2', 'FII '
    ainsi qu'une contrainte de reference 'SMAX' (egale par defaut au
    module d'Young fois 1.E-3).

  Modele de fluage de MAXWELL :

 Le modele de fluage de MAXWELL generalise possede 4 branches
 obligatoires en plus de la branche purement elastique. Il peut
 avoir au maximum huit branches.
 Les donnees des quatre premieres branches sont donc obligatoires.

 Pour chaque branche les parametres a fournir sont le module
 d'elasticite 'EMi' et le temps de relaxation 'TRi'
(i variant de 1 a 4,5,6,7 ou 8).
 Pour la branche au comportement elastique, seul le module 'EM0' est
 a fournir.

 La procedure IDENTI permet d'identifier les parametres du modele
 pour le comportement du beton selon les reglements EUROCODE 2 ou BPEL
 ou suivant le modele de fluage du LCPC.

  Modele de fluage de MAXOTT :

 Les parametres de ce modele de comportement sont les parametres du
 modele de MAXWELL et les parametres du modele OTTOSEN.

 Modele de fluage de KELVIN :

 Le modele de fluage de Kelvin possede 3 systemes de kelvin-voigt
 plus un ressort isole. Il faut donc les parametres suivants :
 YFi : module d'elasticite du ieme systeme
 TFi : temps caracteristique du ieme systeme
 Pour le ressort isole, son module d'elasticite est donne dans 'YOUN'

   FUSION :

   Pour tous les modeles de fluage, l'option FUSION met a zero
   les variables internes du modele si la temperature au point
   d'integration est superieure a la temperature de fusion, donnee par :

   'TFUS' : FLOTTANT, temperature de fusion du materiau.

PART{MECANIQUE PLASTIQUE-ENDOMMAGEABLE}
   | Noms des parametres pour un materiau PLASTIQUE-ENDOMMAGEABLE |

   Les parametres qui suivent sont a definir EN PLUS des parametres
   relatifs au comportement elastique. Les modeles de plasticite
   endommageable disponibles sont les suivants:

   Modele d'endommagement triaxial P/Y :

    -Loi elastoplastique:

        ecrouissage isotrope (cf modele 'PLASTIQUE' 'ISOTROPE' )

    -loi d'endommagement:

        Pseudo porosite A:
        A=(RHOf-RHO)/RHOf
        avec :
        RHO: densite du materiau
        RHOf: densite du materiau lorsqu'on a
        commence a endommager ( lorsqu'on a atteint
        la courbe de debut d'endommagement pour la
        premiere fois)

        Variable d'endommagement D:
        D=f(A) f est une fonction entree par l'utilisateur

        Fonction d'endommagement g(A):
        Si A<0:
        g(A)=1
        Si A>0:
        g(A)=1-D

        Formulation du modele:
        Phases de charge (A augmente):
        SIGMA=SIGMA_PL.g(A)
        Phases de decharge (A diminue):
        Si A>0 :
        SIGMA=SIGMA_PL.g(Amax)
        Si A<0:
        SIGMA=SIGMA_PL

        avec:
        SIGMA: tenseur des contraintes finales
        SIGMA_PL: tenseur des contraintes issues du
        calcul elastoplastique
        Amax: valeur maximale de A

   'RHO' : la densite initiale du materiau
   'TRAC' : mot cle suivi de :
   NOMTRAC : objet de type EVOLUTION donnant la courbe
        de traction elasto-plastique du materiau
   'EVOL' : mot cle suivi de :
   NOMEVOL : objet de type evolution donnant la courbe de debut
        d'endommagement du materiau , c'est a dire
        le rapport P/Y ( P est la trace des contraintes
        divisee par 3 et Y est la contrainte equivalente au
        sens de Von Mises ) en fonction de la deformation
        plastique equivalente.
        Au dessus de cette courbe, il y a endommagement
        du materiau, en dessous on n'endommage pas.
    'COMP' : mot cle suivi de:
    NOMCOMP : objet de type evolution donnant la courbe
        d'evolution de l'endommagement en fonction de la
        pseudo porosite

   Modele d'endommagement ductile de ROUSSELIER

   - Critere de plasticite F :
      F = J2(SIG/RHO)-R(P)+B(BETA).D.EXP(SM/(RHO*SIG1))

   - Fonction d'endommagement B(BETA) :
      B(BETA)=SIG1.F0.EXP(BETA)/(1-F0+F0*EXP(BETA))

   - Rapport de densite RHO :
      RHO=(densite actuelle)/(densite initiale)
      RHO=1/(1-F0+F0*EXP(BETA))

   - Ecoulement plastique isotrope

   - Variable d'endommagement BETA :
     d BETA = d P .D.EXP(SM/(RHO*SIG1))

   - Si f ( fraction volumique de cavites) > FC: SIG=0.D0

   avec: SIG = les contraintes
        SM = tracer(SIG)/3 la contrainte moyenne
        P = deformation plastique cumulee
        R(P) = la courbe de traction du materiau sain

   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.
   'SIG1' : parametre SIG1 intervenant dans le calcul de
        l'endommagement
   'D' : parametre D intervenant dans le calcul de
        l'endommagement
   'F' : parametre F0, fraction volumique initiale de cavites
        dans le materiau
   'FC' : fraction volumique de cavites limite, au dela de
        laquelle les contraintes et la rigidite du materiau
        sont nulles

   Modele d'endommagement ductile de GURSON modifie NEEDLEMAN TVERGAARD
    (GURSON2)
    1er cas :

   - Critere de plasticite F :
      F = J2(SIG)**2-R(Pmat)**2.G_end=0
      G_end=1+Q3.(F_*)**2-2.Q.F_*.COSH(3.Q2.SMT/(2.R(Pmat))

   - Fonction d'endommagement F_*
      Si F<F_C : F_*=F
      Sinon : F_*=F_C+(F_U-F_C)/(F_F-F_C).(F-F_C)

   - Deformation plastique cumulee dans la matrice Pmat
     (1-F).R(Pmat).dPmat=SIG:dEP

   - Fraction de cavite F
      dF=dFg+dFn
      dFg=(1-F)*trace(dEP)
      dFn=BB.(dR(Pmat)+dSMT)+DD.dPmat
   avec:
     .Si (R(Pmat)+SMT)) depasse sa valeur maximale atteinte:
       BB=FNS/(SNS*(2.*PI)**.5)*EXP(-.5*((R(Pmat)+SMT-SIGN)/SNS)**2)
      sinon
       BB=0
     .Si Pmat depasse sa valeur maximale atteinte:
       DD=FNE/(SNE*(2.*PI)**.5)*EXP(-.5*((Pmat-EPSN)/SNE)**2)
      sinon
       DD=0
   ou:
      EP : deformation plastique
      Pmat: deformation plastique cumulee dans la matrice
      SMT=trace(SIG)/3
      SIG : contraintes
      R(Pmat) : courbe de traction du materiau sain

   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.
   'Q' : Q
   'FU' : F_U valeur ultime de F_* ( en general vaut 1/Q )
   'FF' : F_F valeur ultime de F, au dela le materiau est
        rompu ( les contraintes sont nulles)
   'FC' : F_C valeur de F au dessus de laquelle les cavites
        coalescent
   'FNS' : FNS valeur maximale de la fraction des cavites nuclees
        controlee par les contraintes
   'FNE' : FNE valeur maximale de la fraction des cavites nuclees
        controlee par les deformations
   'SNS' : SNS ecart autour de SIGN pour lequel on a nucleation
        controle par les contraintes
   'SNE' : SNE ecart autour de EPSN pour lequel on a nucleation
        controle par les deformations
   'SIGN' : SIGN contrainte moyenne pour laquelle apparait
        la nucleation
   'EPSN' : EPSN deformation plastique moyenne pour laquelle
        apparait la nucleation
   'F0' : fraction de cavites initiale

   Parametres facultatifs
   'Q2' : Q2 ( 1. si non fourni )
   'Q3' : Q3 ( Q**2 si non fourni )

       (voir DMT 96-566)

      2eme cas : modification SRMA (1999) :

     - Deformation plastique cumulee dans la matrice Pmat
     (1-Fg).R(Pmat).dPmat=SIG:dEP

     - Fraction de cavite F
      dF=dFg+dFn
      dFg=(1-Fg)*trace(dEP)
      dFn=BB.(dR(Pmat)+dSMT)+DD.dPmat

     -contrainte dans le materiau
     SMT=(1-F).K.(((1-Fg)/(1-F0)/RHO)-1)

   'SRMA' : valeur 1. pour tenir compte de la modification

   Modele d'endommagement quasi-fragile de DRAGON

   - Notations
       S: tenseur des contraintes
       E: tenseur des deformations
       I: tenseur identite
       D: tenseur d'endommagement (variable interne)
       L,M: coefficients de Lame
       A,Bt,G,C0,C1,B: coefficients du materiau
       E+: tenseur des deformations positives
       dl: pseudo-multiplicateur plastique

   - Equations du modele

     Relation contrainte - deformation :
       S = L*(trE)*I + 2*M*E + A*[tr(E.D)*I + (trD)*I]
        + 2*Bt*(E.D + D.E) + G*D

     Force thermodynamique liee a l'endommagement :
       F = -G*E - 2*Bt*(E.E) - A*(trE)*E

     Critere d'endommagement :
       f(F,D) = SQRT[1/2 (G*E+):(G*E+)] - B*(G*E+):D - (C0 + C1*trD) = 0

     Loi d'evolution : dD = dl*df/dF

   - Les donnees a introduire sont :

   'ALFA', 'BETA','g','C0','C1','B' : coefficients du materiau.

   Modele elastique plastique endommageable ENDO_PLAS

    Les donnees a introduire en plus des parametres d'elasticite sont les
    suivantes:

   'AC' : Parametre de la partie endommagement pour la compression (asymptote
        finale)
   'AT' : Parametre de la partie endommagement pour la traction (asymptote
        finale)
   'BC' : Parametre de la partie endommagement pour la compression (courbe
        post-pic)
   'BT' : Parametre de la partie endommagement pour la traction (courbe post
        pic)
   'EPD0': seuil d'endommagement en deformation pour la traction
   'RC' : Maximum des contraintes effectives en compression pour la plasticite
   'RT' : Maximum des contraintes effectives en traction pour la plasticite
   'P' : Parametre de la partie plasticite pour la compression
   'AH' : Parametre de la partie plasticite (valeur recommandee 7.D-05)
   'BH' : Parametre de la partie plasticite pour la compression
   'CH' : Parametre de la partie plasticite pour le confinement
   'GAMA': Parametre de la partie plasticite (valeur recommandee 0.99)
   'ALFA': Parametre de la partie plasticite (valeur recommandee 0.5)
   'A' : Parametre de la partie plasticite pour le confinement (seuil
        d'apparition de la plasticite)
   'K0' : Parametre pour la partie plasticite (valeur recommandee 0.1)

   FUSION :

   Pour tous les modeles plastiques-endommageables, l'option FUSION met
   a zero les variables internes du modele si la temperature au point
   d'integration est superieure a la temperature de fusion, donnee par :

   'TFUS' : FLOTTANT, temperature de fusion du materiau.

PART{MECANIQUE VISCO-PLASTIQUE}
   | Noms des parametres pour un materiau VISCO-PLASTIQUE |

   Les parametres qui suivent sont a definir EN PLUS des parametres
   relatifs au comportement elastique. Les modeles de viscoplasticite
   disponibles sont les suivants:

   Modele viscoplastique de CHABOCHE :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Sy limite d'elasticite
        Ai variable d'etat d'ecrouissage cinematique
        Xi ecrouissage cinematique
        q variable d'etat d'ecrouissage isotrope
        R ecrouissage isotrope
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        J2 deuxieme invariant du tenseur deviatorique
        <a> partie positive de a

   --> Critere : F = J2 (S-X) - (Sy + R)

   --> Lois d'etat : Xi = 2/3*A*C*Ai
        R = b*Q*q

   --> Ecoulement : dp = <F/K>**N
        : dEP = 3/2 * dp * < S-X > / J2(S-X)

   --> Ecrouissages : dAi = dEP - C*Ai*dp
        dq = (1 - b*q)*dp

   On donne a titre indicatif les valeurs des parametres du modele
   pour un acier 316L a 20°C (voir aussi exemples).

   Parametre : Valeurs Acier 316
   ----------- -----------------
   Loi d'evolution du seuil :
   'SIGY' : valeur initiale de la limite elastique 82 MPa
   'N ' : exposant de la loi de viscosite 24
   'K ' : coefficient de viscosite 151 MPa

   Lois d'ecrouissages :
   'A ' : coefficient d'ecrouissage cinematique 58 MPa
   'C ' : terme de rappel d'ecrouissage cinematique 2800
   'B ' : coefficient d'ecrouissage isotrope 8
   'Q ' : ecrouissage isotrope a saturation 60 MPa

   Elements d'identification des noms de composantes des variables internes
   en mode tridimensionnel :

   Variable Nom de composante Description
   -------- ----------------- -----------
   Ai AXX, AYY... AYZ Variable d'ecrouissage cinematique
   EP EIXX, EIYY... EIYZ Deformation viscoplastique
   p EPSE Deformation plastique cumulee
   q QQ Variable d'ecrouissage isotrope

   Reference : J. Lemaitre, J.-L. Chaboche, "Mecanique des materiaux solides",
   ----------- Dunod, 2e edition, 1996.

   Modele viscoplastique de GUIONNET :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        X variables d'ecrouissage cinematique
        ai variables internes ( i=2,4 )
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        p1 dp1 = dp mais p1=0 a chaque inversion de
        charge
        pI valeur de p1 a l'inversion de charge
        J2 deuxieme invariant du tenseur deviatorique
        n normale au critere F
        t temps
        <a> partie positive de a
        x.y produit scalaire de x par y

   --> Critere : F = J2 (S-X) = R - KK

   --> Ecrouissages: dX =M* p1**(M-1) * [ 2/3 *(A*a2 + a1* EP.n)
        et - ( C1 -C*a2)* X.n ] *dEP
        - ( C0*< pI-P1M0 > + C*a4 )*X*dp
       ecoulement - G * J2(X)**R * X*dt
        R = R0*(1-CD) + R0*CD*a2
        KK = K *(1+CK*a2)
        dEP = 3/2 * < F/KK >**N * n
       si p1 > pI : da2 = da4 = NN * p1**(NN-1) * dp
       si p1 < pI : da2 = C2*(Q * pI**NN -a2) * dp - G1 * a2**R1 *dt
       si p1 < pI : da4 = - BETA*a4*dp/p

   Il convient de se rapporter a la note CEA -N-2612 pour de plus
   amples renseignements. On donne a titre indicatif les valeurs des
   parametres pour un acier 316L a 600Â°C.

   Les donnees a introduire sont les suivantes :
        Valeurs Acier 316
   Loi d'evolution du seuil : -----------------
   'N ' : exposant du seuil de viscoplasticite 20
   'K ' : facteur initial de normalisation du seuil 10 MPa
   'CK ' : constante dans la loi d'evolution de K 3.87
   'R0 ' : valeur initiale de la limite elastique 80 MPa
   'CD ' : constante dans la loi d'evolution de R 0.

   Loi d'evolution du centre X :
   'A ' : coefficient de ALPHA2 15000 MPa
   'M ' : exposant de la deformation plastique ( <1 ) 0.8
   'A1 ' : coefficient de la deformation plastique 200000 MPa
   'C ' : coefficient de ALPHA4 40
   'C1 ' : coefficient du terme de rappel 180
   'C0 ' : reglage pour deformation progressive 0.
   'P1M0' : seuil pour terme de reglage
   'G ' : coefficient du terme de restauration 1.5E-10 /s
   'R ' : exposant du terme de restauration 4

   Loi d'evolution des variables internes ALPHA2 et ALPHA4 :
   'NN ' : exposant de la deformation plastique 0.075
   'C2 ' : coefficient de la deformation plastique 4
   'Q ' : coefficient de la deformation plastique 3.43
   'G1 ' : coefficient du terme de restauration 1.5E-6
   'R1 ' : exposant de ALPHA2 4.
   'BETA' : coefficient de ALPHA4 0.4

   Modele viscoplastique ONERA (Chaboche unifie) :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Xi variables d'ecrouissage cinematique (i=1 ou 2)
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        q variable isotrope de la surface memoire en
        deformation
        Y variable cinematique de la surface memoire en
        deformation
        I2 deuxieme invariant du tenseur
        J2 deuxieme invariant du tenseur deviatorique
        n normale au critere F
        nn normale au seuil G
        t temps
        T temperature
        <a> partie positive de a
        x.y produit scalaire de x par y
        X = X1 dans le cas d'un seul centre
        X1+X2 dans le cas de deux centres

   --> Critere : F = J2(S-X) - R' - KK
        avec : R' = ALFR * R

   --> Ecrouissages: dXi =2/3 * Ai*Ci*dEP - Ci*Xi*p'*dp
        - ( J2(Xi)/BETi )**(Ri-1) * Xi * dt (i=1-2)
        si BETi non nul, sinon :
        dXi =2/3 * Ai*Ci*dEP - Ci*Xi*p'*dp (i=1-2)
        avec : p' = PHI+(1-PHI)* e** (-B*p)

        dp = < F/K' >**N * e**(ALF* < F/K' >**(N+1))
        avec : K' = K0 + ALFK * R

        dR  = B*(Q - R)*dp + GAMA*Sign(QR-R)*|QR-R|**M *dt

   --> Ecoulement : dEP = 3/2 * dp * < S-X > / J2(S-X)

   --> Memoire en G = I2 (EP-Y) - q < 0
       deformation dQ = 2*MU*(QMAX-Q)* dq + dQ/dT.dT
       inelastique : dq = ETA * < n.nn > * dp
        dY = (3/2 ** 0.5) * (1-ETA) * < n.nn > * nn*dp
        QR = Q - QSTA * ( 1 - ((QMAX-Q)/QMAX)**2)

   La valeur initiale de Q doit etre fournie en entree de PASAPAS.
   Par defaut, sa valeur est 0.

   On donne a titre indicatif les valeurs des parametres du modele
   pour un acier 316L a 600°C :

   Parametre : Valeurs Acier 316
   ----------- -----------------
   Loi d'evolution du seuil :
   'KK ' : valeur initiale de la limite elastique 10 MPa
   'N ' : exposant de la loi de viscosite 24
   'K0 ' : coefficient de viscosite 116 MPa
   'ALFK' : coefficient d'evolution isotrope de K 1.5
   'ALFR' : coefficient d'evolution isotrope du seuil 0.35
   'ALF ' : coefficient de viscosite 2.E6

   Loi d'evolution des centres X1 et X2 :
   'A1 ' : coefficient de la deformation plastique 67.5 MPa
   'C1 ' : coefficient du terme de rappel 1300
   'BET1' : facteur de normalisation pour la restauration 4807 MPa
   'R1 ' : exposant du terme de restauration 4
   'A2 ' : coefficient de la deformation plastique 80 MPa
   'C2 ' : coefficient du terme de rappel 45
   'BET2' : facteur de normalisation pour la restauration 58480 MPa
   'R2 ' : exposant du terme de restauration 4
   'PHI ' : coefficient multiplicatif du terme de rappel 1.

   Loi d'evolution de l'ecrouissage isotrope :
   'B ' : coefficient d'ecrouissage isotrope 12
   'GAMA' : coefficient de l'effet de restauration 2.E-7
   'M ' : exposant du terme de restauration 2

   Loi d'evolution de la memoire de la deformation plastique :
   'QMAX' : valeur maximale de Q 455 MPa
   'QSTA' : valeur stabilisee de Q 200 MPa
   'MU ' : coefficient de la loi d'evolution de Q 19
   'ETA ' : facteur liant q a la deformation plastique 0.06

   Parametre optionnel :
   'QT' : courbe d'evolution de Q(0) en fonction de la
        temperature (objet de type EVOLUTION).

   Initialisation de la variable interne Q :
   Q(0) : 30 MPa (acier 316)

   Elements d'identification des noms de composantes des variables internes
   en mode tridimensionnel :

   Variable Nom de composante Description
   -------- ----------------- -----------
   Xi XiXX, XiYY... XiYZ Ecrouissage cinematique i
   Y GPXX, GPYY... GPYZ Variable cinematique de la surface memoire
   EP VIXX, VIYY... VIYZ Deformation viscoplastique
   p EPSE Deformation plastique cumulee
   R' RR Ecrouissage isotrope
   Q QQQ Parametre stabilisation ecrouissage isotrope
   q QQ Variable isotrope de la surface memoire

   Remarque 1 : Pour initialiser la variable Q, il convient de creer
   ------------ un champ par element de variables internes du modele,
        dont la composante 'QQQ' a la valeur Q(0).
        Ce champ doit etre passe en argument de la procedure
        PASAPAS (voir notice PASAPAS).

   Remarque 2 : La donnee du paramatre optionnel 'QT' ne permet pas
   ------------ de s'affranchir de l'initialisation de la variable Q.

   Reference : D. Nouailhas, "Modelisation de l'ecrouissage et de la
   ----------- restauration en viscoplasticite cyclique",
        Revue de Physique Appliquee, 23 (1988) 339-349.

   Modele viscoplastique de OHNO :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Xi variables d'ecrouissage cinematique (i=1 ou 2)
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        q variable isotrope de la surface memoire en
        deformation
        Y variable cinematique de la surface memoire en
        deformation
        I2 deuxieme invariant du tenseur
        J2 deuxieme invariant du tenseur deviatorique
        n normale au critere F
        nn normale au seuil G
        t temps
        <a> partie positive de a
        x.y produit scalaire de x par y
        X = X1 dans le cas d'un seul centre
        X1+X2 dans le cas de deux centres
        RR = ALFR * R
        K = K0 + ALFK * R
        Q(0)=Q0

   --> Critere : F = J2(S-X) - RR - KK
   --> Ecrouissages:
      dXi =2/3 * Ai*Ci*dEP - Ci*p'*< dEP:Ki >*(J2(Xi)/LIMi)**EXPi
        - ( J2(Xi)/BETi )**(Ri-1) * Xi * dt (i=1-2)
        si BETi non nul, sinon :
        dXi =2/3 * Ai*Ci*dEP - Ci*Xi*dp' (i=1-2)
        avec : p' = PHI+(1-PHI)* e** (-B*p)

        LIMi = Ai/p' (i=1 ou 2)

        Ki = Xi / J2(Xi) (i=1 ou 2)

        dp = < F/K >**N * e**(ALF* < F/K >**(N+1))

        dR  = B*(Q - R)*dp + GAMA*Sign(QR-R)*|QR-R|**M *dt

   --> Ecoulement : dEP = 3/2 * dp * < S-X > / J2(S-X)

   --> Memoire en G = I2 (EP-Y) - q < 0
       deformation dQ = 2*MU*(QMAX-Q)* dq
       inelastique : dq = ETA * < n.nn > * dp
        dY = (3/2 ** 0.5) * (1-ETA) * < n.nn > * nn*dp
        QR = Q - QSTA * ( 1 - ((QMAX-Q)/QMAX)**2)

   La valeur initiale de Q est Q0 et doit etre initialisee (voir ci-dessous).

   Ce modele s'inspire du modele viscoplastique ONERA de Chaboche
   On donne a titre indicatif les
   valeurs des parametres pour un acier 316L a 600Â°C.

   Les donnees a introduire sont les suivantes :
        Valeurs Acier 316
   Loi d'evolution du seuil : -----------------
   'N ' : exposant du seuil de viscoplasticite 24
   'KK ' : valeur initiale de la limite elastique 10 MPa
   'K0 ' : facteur initial de normalisation du seuil 116 MPa
   'ALFK' : coefficient d'evolution isotrope de K 1.5
   'ALFR' : coefficient d'evolution isotrope du seuil 0.35
   'ALF ' : coefficient de viscosite 2.E6

   Loi d'evolution des centres X1 et X2 :
   'A1 ' : coefficient de la deformation plastique 67.5 MPa
   'C1 ' : coefficient du terme de rappel 1300
   'BET1' : facteur de normalisation pour la restauration 4807 MPa
   'R1 ' : exposant du terme de restauration 4
   'A2 ' : coefficient de la deformation plastique 80 MPa
   'C2 ' : coefficient du terme de rappel 45
   'BET2' : facteur de normalisation pour la restauration 58480 MPa
   'R2 ' : exposant du terme de restauration 4
   'PHI ' : coefficient multiplicatif du terme de rappel 1.
   'EXP1' : exposant du terme de rappel 2.
   'EXP2' : exposant du terme de rappel 2.

   Loi d'evolution de l'ecrouissage isotrope :
   'B ' : coefficient d'ecrouissage isotrope 12
   'GAMA' : coefficient de l'effet de restauration 2.E-7
   'M ' : exposant du terme de restauration 2

   Loi d'evolution de la memoire de la deformation plastique :
   'QMAX' : valeur maximale de Q 455 MPa
   'QSTA' : valeur stabilisee de Q 200 MPa
   'MU ' : coefficient de la loi d'evolution de Q 19
   'ETA ' : facteur liant q a la deformation plastique 0.06

 + Initialisation de la variable interne Q : Q = Q0 = 30 MPa (acier 316)
   Pour cela, il convient de creer un champ par element de variables
   internes a une composante de nom 'QQ' et de valeur Q0. Ce champ
   sera passe dans la table argument de PASAPAS.

   Modele viscoplastique endommageable de LEMAITRE :
   Notation :
        S : tenseur des contraintes
        dev(S) : deviateur du tenseur des contraintes
        tr(S) : trace du tenseur des contraintes
        J0(S) : contrainte principale maximale
        Seq : contrainte equivalente de VON MISES
        p : deformation inelastique cumulee
        D : variable d'endommagement
        X(S) : contrainte equivalente de fluage

   Les equations du modele sont :
   dEP = (3/2) * dp * (dev(S) / Seq)
   dq = dp * (1 - D)
   dq = ( Seq/((1 - D) * KK * (q**(1/M))) ) ** N
   dD = (< X(S)/A > ** R) * ((1 - D)**-k) avec k fonction de <X(S)>
   X(S)= ALP1 * J0(S) + BLP1 * (tr(S)/3) + (1 - ALP1 - BLP1) * Seq
   <y> = 0 si y < 0 ; <y> = y si y > 0

   Les donnees a introduire sont les suivantes :
   N,M,KK : parametres definissant la loi de fluage
   A,R : parametres definissant la loi d'evolution du dommage D
   ALP1,BLP1 : parametres definissant la contrainte equivalente de
        fluage X(S)
   EVOL : mot-cle suivi de :
   NOMEVOL : courbe definissant l'evolution du parametre k avec la
        contrainte equivalente de fluage X(S) .
        Cette courbe est constituee par un objet de type
        EVOLUTIO, avec en abscisse X(S) et en ordonnees k.
        Si k est constant, definir une evolution constante
   SMAX : contrainte de reference(egale par defaut au module d'Young
        fois 1.E-3)
   REMARQUE QUAND LE MATERIAU DEPEND DE LA TEMPERATURE T
   si les listes de temperatures definissant l'evolution de certains
        des parametres N,M,KK,A,R,ALP1,BLP1,EVOL sont identiques
   alors
        pour T = (1 - teta)*T1 + teta*T2
        la vitesse des variables internes V vaut :
        V(T) = (1 - teta)*V(T1) + teta*V(T2)
        V(Ti) etant la vitesse calculee avec la valeur
        des parametres obtenue pour Ti (i=1,2)
   sinon
        V(T) se calcule avec la valeur des parametres
        obtenue pour T
   finsi

   Modele viscoplastique parfait:
     La variation de la deformation viscoplastique est donnee par
       devp/dt = ( (s-sigy) / k)**N * (s'/s)
     Les donnees materiau sont donc

      SIGY : limite elastique
      K : constante de viscosite
      N : exposant de la loi
     Le modele marche meme lorsque SIGY = 0

   Modeles viscoplastiques pour poudre :

Modele d'ABOUAF pour la densification des poudres.

Les equations du modele sont de la forme :

 --> Notations :
        S tenseur des contraintes
        s tenseur deviateur de contraintes
        Seq contrainte equivalente
        d tenseur unite
        I1 premier invariant du tenseur contrainte
        J2 deuxieme invariant du tenseur deviatorique
        rho densite relative du materiau poreux
        f fonction de la densite relative
        c fonction de la densite relative
        evp deformation viscoplastique
        t temps
        T temperature

 --> Equations du modele d'Abouaf :
        Seq = (f*I1**2+3/2*c*J2**2)**0.5
        devp/dt = rho*A*exp(-Q/RT)*Seq**(n-1)*(f*I1*d+3/2*c*s)
        tr(devp/dt) = -(drho/dt)/rho

 --> Donnees a introduire :
        A coefficient de la loi de fluage en puissance
        N exposant de la loi de fluage en puissance
        QSRT energie d'activation
        F0->F5 parametres definissant la fonction f
        C0->C5 parametres definissant la fonction c
        RHOR densite relative initiale du materiau

 --> Pour tout renseignements, contacter :
        DTA/CEREM/DEM/SGM F. MORET (33) 76.88.53.40
        CENG - 17, rue des Martyrs C. DELLIS (33) 76.88.57.26
        38054 GRENOBLE Cedex 9 P. LeGALLO (33) 76.88.54.64
        FRANCE Fax : (33) 76.88.51.17

   Modele viscoplastique a deux deformations inelastiques (DDI) :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        EP tenseur des deformations plastiques
        p deformation plastique equivalente cumulee
        EV tenseur des deformations viscoplastiques
        v deformation viscoplastique equivalente cumulee
        Xpi, Xvi variables d'ecrouissage cinematique (i=1 ou 2)
        Rp, Rv variables d'ecrouissage isotrope
        J2 deuxieme invariant du tenseur deviatorique
        np normale au critere Fp
        nv normale au critere Fv
        t temps
        <a> partie positive de a
        Xp = Xp1
        Xv = Xv1 dans le cas d'un seul centre
        Xp = Xp1+Xp2
        Xv = Xv1+Xv2 dans le cas de deux centres

   --> Criteres : Fp = J2(S-Xp) - Rp
        Fv = J2(S-Xv) - Rv

   --> Ecrouissage : Xp1 = 2/3CP1*ALPHAp1 + 2/3CVP1*ALPHAv1
        Xp2 = 2/3CP2*ALPHAp2 + 2/3CVP2*ALPHAv2
        Xv1 = 2/3CV1*ALPHAv1 + 2/3CVP1*ALPHAp1
        Xv2 = 2/3CV2*ALPHAv2 + 2/3CVP2*ALPHAp2
        dALPHApi = dEp - 3/2*(DPi/CPi)*Xpi*dp (i=1,2)
        dALPHAvi = dEv - 3/2*(DVi/CVi)*Xvi*dv (i=1,2)
        Rp = RP0 + QP*(1-exp(-BP*p))
        Rv = RV0 + Qv*(1-exp(-BV*v))

   --> Ecoulement : dp verifie dFp=0
        dEp = 3/2 * dp * < S-Xp > / J2(S-Xp)
        dV = (< Fv > / KS) ** n
        dEv = 3/2 * dv * < S-Xv > / J2(S-Xv)

   Donnees materiau a introduire (on donne a titre indicatif les
   valeurs des parametres pour le Zirconium alpha a 200Â°C):

        Valeurs Zirconium
   Loi d'evolution des centres Xpi et Xvi : -----------------
   'CP1' : Coefficient de ALPHAp1 34000 MPa
   'CP2' : Coefficient de ALPHAp2 60000 MPa
   'CV1' : Coefficient de ALPHAv1 24000 MPa
   'CV2' : Coefficient de ALPHAv2 9000 MPa
   'CVP1' : Coefficient de couplage visco-plastique 0
   'CVP2' : Coefficient de couplage visco-plastique 0

   Loi d'evolution des variables internes ALPHApi et ALPHAvi:
   'DP1' : Coefficient de ALPHAp1*dp 250
   'DP2' : Coefficient de ALPHAp2*dp 3000
   'DV1' : Coefficient de ALPHAv1*dv 300
   'DV2' : Coefficient de ALPHAv2*dv 3000

   Loi d'evolution de l'ecrouissage isotrope:
   'BP' : Coefficient de P 120
   'QP' : Coef. de l'ecrouissage isotrope plastique -60 MPa
   'RP0' : Valeur initiale du seuil plastique 135 MPa
   'BV' : Coefficient de V 10
   'QV' : Coef. de l'ecrouissage isotrope viscoplastique -20 MPa
   'RV0' : Valeur initiale du seuil viscoplastique 70 MPa

   Loi d'evolution de V:
   'KS' : Coefficient de normalisation du seuil 960 MPa
   'N' : Exposant du seuil de viscoplasticite 3.4

    Modele Visco elasto visco plastique anisotherme de KOCKS :

   Les equations du modele sont de la forme :

   --> Notations : S resistance isotrope a la deformation (variable
        interne)
        SP variation de la variable interne
        J2 deuxieme invariant des contraintes deviatoriques
        EPP taux de variation de deformation plastique
        equivalente

   --> Loi d'ecoulement : EPP = A [SINH(B*J2/S) ** 1./M * EXP(-Q/RT)

   --> Variation de la variable interne:

        SP = H0 (ABS (Ssat - S)/(Ssat - S0))**AP *SIGN(Ssat - S0)*EPP

        Saturation de S :

        Ssat = SB*(Z/A)**N

        Parametre de Zener Holomon : Z = EPP*EXP(Q/RT)

   Les donnees a introduire sont les suivantes :

   'A ' :facteur pre-exponentiel
   'B ' :facteur de normalisation de la variable S
   'M ' :exposant de la loi d'ecoulement
   'Q ' :energie d'activation
   'R ' :constante des gaz parfaits
   'H0 ' :taux d'ecrouissage athermique initial
   'AP ' :exposant de la loi d'ecrouissage
   'SB ' :coefficient de la loi de saturation de S
   'N ' :exposant de la loi de saturation de S
   'S0 ' :valeur initiale de S

   Modele viscoplastique NOUAILHAS_A :

   La difference avec le modele viscoplastique ONERA se situe
   dans la maniere de calculer Xi.

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Ai variables pour l'ecrouissage cinematique
        (i=1 ou 2)
        Xi ecrouissage cinematique (i=1 ou 2)
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        q variable isotrope de la surface memoire en
        deformation
        Y variable cinematique de la surface memoire en
        deformation
        I2 deuxieme invariant du tenseur
        J2 deuxieme invariant du tenseur deviatorique
        n normale au critere F
        nn normale au seuil G
        t temps
        <a> partie positive de a
        x.y produit scalaire de x par y
        X = X1 dans le cas d'un seul centre
        X1+X2 dans le cas de deux centres
        RR = ALFR * R
        K = K0 + ALFK * R
        Q(0)=Q0

   --> Critere : F = J2(S-X) - RR - KK
   --> Ecrouissages: Xi = 2/3 * CLi * Ai
        dAi = dEP - DNLi * Ai * p' * dp
        - 3/2 * ( J2(Xi)/GDMi )**(PTMi) * (Xi/J2(Xi)) * dt
        (i=1 ou 2)
        si GDMi non nul, sinon :
        dAi = dEP - DNLi * Ai * p' * dp (i=1 ou 2)

        avec : p' = PHI+(1-PHI)* e** (-B*p)

        dp = < F/K >**N * e**(ALF* < F/K >**(N+1))

        dR  = B*(Q - R)*dp + GAMA*Sign(QR-R)*|QR-R|**M *dt

   --> Ecoulement : dEP = 3/2 * dp * < S-X > / J2(S-X)

   --> Memoire en G = I2 (EP-Y) - q < 0
       deformation dQ = 2*MU*(QMAX-Q)* dq
       inelastique : dq = ETA * < n.nn > * dp
        dY = (3/2 ** 0.5) * (1-ETA) * < n.nn > * nn*dp
        QR = Q - QSTA * ( 1 - ((QMAX-Q)/QMAX)**2)

   La valeur initiale de Q est Q0 et doit etre definie (voir ci apres)

   Il convient de se rapporter au rapport de D. NOUAILHAS :
   " A viscoplastic modelling applied to stainless steel behaviour",
   Second Inter. Conf. on Constitutive Laws for Engineering Materials,
        University of Arizona, Tucson,1987

   Loi d'evolution du seuil :
   'N ' : exposant du seuil de viscoplasticite
   'KK ' : valeur initiale de la limite elastique
   'K0 ' : facteur initial de normalisation du seuil
   'ALFK' : coefficient d'evolution isotrope de K
   'ALFR' : coefficient d'evolution isotrope du seuil
   'ALF ' : coefficient de viscosite

   Loi d'evolution des centres X1 et X2 :
   'CL1 ' : coefficient de la deformation plastique
   'DNL1' : coefficient du terme de rappel
   'GDM1' : facteur de normalisation pour la restauration
   'PTM1' : exposant du terme de restauration
   'CL2 ' : coefficient de la deformation plastique
   'DNL2' : coefficient du terme de rappel
   'GDM2' : facteur de normalisation pour la restauration
   'PTM2' : exposant du terme de restauration
   'PHI ' : coefficient multiplicatif du terme de rappel

   Loi d'evolution de l'ecrouissage isotrope :
   'B ' : coefficient d'ecrouissage isotrope
   'GAMA' : coefficient de l'effet de restauration
   'M ' : exposant du terme de restauration

   Loi d'evolution de la memoire de la deformation plastique :
   'QMAX' : valeur maximale de Q
   'QSTA' : valeur stabilisee de Q
   'MU ' : coefficient de la loi d'evolution de Q
   'ETA ' : facteur liant q a la deformation plastique

 + Initialisation de la variable interne Q : Q = Q0 = 30 MPa (acier 316)
   Pour cela, il convient de creer un champ par element de variables
   internes a une composante de nom 'QQ' et de valeur Q0. Ce champ
   sera passe dans la table argument de PASAPAS.

   Modele viscoplastique de NOUAILHAS_B :

   La difference avec le modele de NOUAILHAS_A se situe sur l'evolution
   de l'ecrouissage isotrope. Par ailleurs la restauration par le temps
   n'est possible que sur le calcul de X1

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        Ai variables pour l'ecrouissage cinematique
        (i=1 ou 2)
        Xi ecrouissage cinematique (i=1 ou 2)
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        I2 deuxieme invariant du tenseur
        J2 deuxieme invariant du tenseur deviatorique
        t temps
        <a> partie positive de a
        X = X1 dans le cas d'un seul centre
        X1+X2 dans le cas de deux centres

   --> Critere : F = J2(S-X) - RR
   --> Ecrouissages: X1 = 2/3 * CL1 * A1
        dA1 = dEP - DNL1 * A1 * p' * dp
        - 3/2 * ( J2(X1)/GDM1 )**(PTM1) * (X1/J2(X1)) * dt
        si GDM1 non nul, sinon :
        dA1 = dEP - DNL1 * A1 * p' * dp

   --> Ecrouissages: X2 = 2/3 * CL2 * A2
        dA2 = dEP - DNL2 * A2 * p' * dp

        avec : p' = PHI+(1-PHI)* e** (-B*p)

        dp = < F/K0 >**N * e**(ALF* < F/K0 >**(N+1))

        RR = KK + (RMAX - KK) * (1 - e**(-BR * p))

   --> Ecoulement : dEP = 3/2 * dp * < S-X > / J2(S-X)

   Il convient de se rapporter au rapport de D. NOUAILHAS :
   " A viscoplastic modelling applied to stainless steel behaviour",
   Second Inter. Conf. on Constitutive Laws for Engineering Materials,
        University of Arizona, Tucson,1987

   Loi d'evolution du seuil :
   'N ' : exposant du seuil de viscoplasticite
   'KK ' : valeur initiale de l'ecrouissage isotrope
   'K0 ' : facteur initial de normalisation du seuil
   'ALF ' : coefficient de viscosite

   Loi d'evolution des centres X1 et X2 :
   'CL1 ' : coefficient de la deformation plastique
   'DNL1' : coefficient du terme de rappel
   'GDM1' : facteur de normalisation pour la restauration
   'PTM1' : exposant du terme de restauration
   'CL2 ' : coefficient de la deformation plastique
   'DNL2' : coefficient du terme de rappel
   'PHI ' : coefficient multiplicatif du terme de rappel
   'B ' : coefficient d'ecrouissage cinematique

   Loi d'evolution de l'ecrouissage isotrope :
   'RMAX' : valeur maximale de R
   'BR ' : coefficient d'ecrouissage isotrope

   Modele viscoplastique VISK2 :
     En deca su seuil, le comportement est elastique. Au-dela, on cumule
     un effet d'ecrouissage cinematique, et un effet de viscosite de type
     Maxwell, etendu par la possibilite d'utiliser une loi polynomiale.
     (DMT 98/013)

     Les donnees a introduire sont les suivantes :
      'SIGY' : limite elastique
      'H ' : ecrouissage cinematique
      'ETA ' : coefficient de viscosite
      'HVIS' : module lie a la viscosite
      'N ' : exposant de la loi

      Modele general de deformation MISTRAL,
      traite comme un modele viscoplastique

      Ce modele, applicable a un materiau orthotrope, traite l'ensemble
      des deformations suivantes :

        - dilatation thermique,
        - deformation elastique,
        - 0 ou 1 deformation plastique instantanee a seuil,
        - 0 a 3 (dans version actuelle) deformations viscoplastiques,
        - croissance sous irradiation.

      De ce fait, pour tout materiau traite par MISTRAL :

        - la dilatation thermique existant par ailleurs dans CASTEM
      doit etre mise a zero : 'ALP1' 0. 'ALP2' 0. 'ALP3' 0. ,

        - les coefficients d'elasticite doivent etre definis de la
      facon generale existant dans CASTEM pour un materiau orthotrope :

        'YG1 ' E1 'YG2 ' E2 'YG3 ' E3
        'NU12' NU12 'NU23' NU23 'NU13' NU13
        'G12 ' MU12 ['G13 ' MU13 'G23 ' MU23]

      mais les objets E1, E2, E3, NU12, NU23, NU13, MU12, [MU23, MU13]
      sont necessairement des evolutions donnant les coefficients
      d'elasticite en fonction de la temperature absolue (en K).

      Le modele MISTRAL fonctionne pour des elements massifs et pour
      les types de calcul suivants : tridimensionnel, axisymetrie,
      deformations planes, contraintes planes et deformations planes
      generalisees.

      Les donnees a introduire sont les suivantes :
      (cf rapport DMN/SEMI/LEMO/RT/01-010/A)

      'DILT' : PDILT, liste de reels contenant les parametres des
        fonctions traduisant l'evolution des coefficients de
        dilatation thermique en fonction de la temperature.

      'NDIM' : NDIME, liste de 4 entiers en format reel contenant :
        - le nombre de deformations plastiques instantanees a
        seuil (0 ou 1),
        - le nombre de deformations viscoplastiques (0 a 3),
        - le numero maximal de niveau de contraintes internes
        pour toute deformation plastique precedente (0 a 2 dans
        version actuelle), le niveau 0 correspondant aux
        contraintes internes (directement) mesurables,
        - 1 ou 0 selon qu'il existe ou non des couplages par
        les contraintes internes entre deformations plastiques
        de natures differentes.

      'COHI' : PCOHI, liste de reels contenant les parametres des
        fonctions traduisant l'evolution des coefficients
        d'anisotropie plastique (de Hill) en fonction de la
        temperature et de la fluence de neutrons rapides *.

      'ACOU' : PECOU, liste de reels contenant les parametres relatifs
        a la loi d'ecoulement **.

      'ECRI' : PECRI, liste de reels contenant les parametres relatifs
        a la loi d'ecrouissage isotrope *.

      'ECRC' : PECRC, liste de reels contenant les parametres relatifs
        a la loi d'ecrouissage cinematique *.

      'DURI' : PDURI, liste de reels contenant les parametres relatifs
        a la variable de durcissement d'irradiation *.

       * : pour toutes les deformations plastiques
       ** : pour toutes les deformations viscoplastiques

      'CROI' : PCROI, liste de reels contenant les parametres de la loi
        de croissance sous irradiation.

      'INCR' : PINCR, liste de reels contenant les increments maximaux
        autorisees pour la determination automatique du pas de
        temps lors de l'integration des equations d'evolution
        des variables materiau par MISTRAL.

      Avec certains types de calcul de CASTEM, toutes les bases de
      l'espace a 3 dimensions ne sont pas accessibles pour la base
      principale d'orthotropie, par exemple : la base (radiale,
      circonferentielle, axiale) n'est pas accessible en mode
      axisymetrique (la direction circonferentielle est toujours en
      3eme position). Or les lois des gaines des combustibles sont
      habituellement exprimees dans cette base.

      C'est pourquoi on doit fournir les deux nombres suivants pour
      definir la base principale d'orthotropie pour MISTRAL (toujours dans
      l'espace a 3 dimensions) par rapport a la base principale
      d'orthotropie pour CASTEM (il s'agit d'une simple permutation des
      axes avec eventuel changement de sens pour conserver l'orientation
      de l'espace) :

      'SIP1' : SENSIP1, numero d'ordre de la 1ere direction de la base
        MISTRAL dans la base CASTEM, affecte du signe - s'il y a
        changement de sens.

      'SIP2' : SENSIP2, numero d'ordre de la 2eme direction de la base
        MISTRAL dans la base CASTEM, affecte du signe - s'il y a
        changement de sens.

      Avant l'appel a l'operateur 'MATE', les donnees peuvent etre lues
      sur un fichier, et en plus mises en forme adaptee a CASTEM pour les
      coefficients d'elasticite, par la procedure @mistpar de la facon
      suivante :

        fichier = 'nom du fichier de donnees' ;
        PDILT E1 E2 E3 NU12 NU23 NU13 MU12 MU23 MU13
        NDIME PCOHI PECOU PECRI PECRC PDURI PCROI PINCR
        = @mistpar fichier SENSIP1 SENSIP2 ;

     Les nombres SENSIP1 et SENSIP2, affecte a 'SIP1' et 'SIP2' dans
     l'operateur 'MATE', sont arguments de cette procedure pour transformer
     les coefficients d'elasticite de la base d'orthotropie MISTRAL
     a celle de CASTEM.

   Modele GATT_MONERIE :

   Le modele GATT_MONERIE decrit la viscoplasticite du combustible UO2
   standard ou dope au Chrome.
   Il fonctionne pour des elements massifs et pour les types de calcul
   suivants : tridimensionnel, axisymetrie, deformations planes,
   contraintes planes et deformations planes generalisees.

   Dans ce modele :

   le module d'Young E s'ecrit sous la forme :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     E = Em(T) * Ef(f)

   oa¹ Em(T) est une fonction de la temperature (eventuellement
        constante) T exprimee en Kelvin
      Ef(f) est une fonction de la porosite f du materiau
        (eventuellement constante)
      f est une variable interne du modele representant la porosite

   le module de cisaillement G s'ecrit sous la forme :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     G = Gm(T) * Gf(f)

   oa¹ Gm(T) est une fonction de la temperature (eventuellement
        constante) T exprimee en Kelvin
      Gf(f) est une fonction de la porosite f du materiau
        (eventuellement constante)
      f est une variable interne du modele representant la porosite

   le coefficient de Poisson NU est obtenu a partir de l'expression :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
      NU = (E/2G) - 1

   le coefficient de dilatation thermique ALPHA s'ecrit sous la forme :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     ALPHA = ALPHAm(T) * ALPHAf(f)

   oa¹ ALPHAm(T) est une fonction de la temperature (eventuellement
        constante) T exprimee en Kelvin
      ALPHAf(f) est une fonction de la porosite f du materiau
        (eventuellement constante)
      f est une variable interne du modele representant la porosite

   Dans le cadre de ce modele, les donnees a introduire et relatives au
   comportement elastique du modele sont donc les suivantes :

   'YOUN' : module d'Young
   'NU ' : coefficient de Poisson
   'ALPH' : coefficient de dilatation thermique secant
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'RHO ' : masse volumique initiale

   ALPH est OBLIGATOIRE
   RHO est OBLIGATOIRE (cf. plus loin)

   La deformation visco-plastique Evp comprend un fluage d'origine
   thermique primaire et secondaire et un fluage induit par
   l'irradiation.

   Fluage d'origine thermique :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    La vitesse de fluage primaire d'origine thermique s'exprime par :

   vEvp0 = 1.5 * KPRIM * ( Sigeq**(AP-1)) / Evpq**BP ) * Sigprim

   Le fluage secondaire d'origine thermique fait intervenir
   deux mecanismes (de diffusion et de dislocation).

   Pour chacun de ces deux mecanismes de fluage, le potentiel
   thermodynamique PSIi s'ecrit sous la forme
   (i=1 : premier mecanisme / i=2 : second mecanisme) :

   PSIi = (AKi /(Ni+1)) *
        ( Ai(f)*((1.5*Sigm)**2) + Bi(f)*(Sigeq**2) ) ** ((Ni+1)/2) )

     avec Sigma : tenseur de contraintes
        Sigm = (trace Sigma)/3
        II : tenseur identite
        Sigprim = Sigma - Sigm*II
        Sigeq : contrainte equivalente au sens de Von Mises :
        Sigeq = (1.5 * Sigprim : Sigprim)**0.5
        Evpq = ( (2/3) * (Evp :: Evp) ) ** 0.5
        Evp :: Evp designant le produit contracte du tenseur de
        deformation visco-plastique Evp

     KPRIM = KP * exp(- QP/R*T)

     Ai(f) et Bi(f) sont des fonctions de la porosite f :

      Ai(f) = (Ni*(f**(-1/Ni) - 1))**(-2*Ni/(Ni+1))
      Bi(f) = (1 +(2f/3)) / ( (1-f)**(2*Ni/(Ni+1)) )
       (Ni constante du modele)

      AK1 = WC1 * K1 * (DG**M1) * exp(- Q1/R*T)
      WC1 = 1 + 0.5*CR1*[1+th((CR-CR2)/CR3)]
      AK2 = WC2 * K2 * (DG**M2) * exp(- Q2/R*T)
      WC2 = 2 * [1-cos(DG/DG0)]
       (KP, AP, BP, Ki, Ni et Mi constantes du modele,
        QP energie d'activation du fluage primaire,
        Qi energie d'activation du mecanisme i,
        CR1, CR2, CR3 constantes pour le mecanisme de diffusion,
        CR concentration en Chrome,
        DG taille de grain,
        DG0 constante pour le mecanisme de dislocation,
        R constante des gaz parfaits,
        T temperature exprimee en Kelvin)

   Pour chaque mecanisme, la vitesse de fluage thermique vEvpi se
   calcule par :

   vEvpi =
     (1/3 * dPSIi/dSigm * II) + (1.5 * dPSIi/dSigeq * Sigprim/Sigeq)

   soit :

   vEvpi = 0.5 * AKi *
    ( ( Ai(f)*((1.5*Sigm)**2) + Bi(f)*(Sigeq**2) ) ** ((Ni-1)/2) ) *
        ( Ai(f)*1.5*Sigm*II + 3*Bi(f)*Sigprim)

   Le potentiel thermodynamique PSI est le resultat du couplage entre
   ces deux mecanismes via la fonction de couplage statique Theta0
   ou dynamique Theta:
     PSI = (1-Theta0)*PSI1 + Theta0*PSI2 ou
     PSI = (1-Theta )*PSI1 + Theta *PSI2

 La fonction de couplage statique Theta0 est definie par :
     Theta0(T,GSigeq) = 0.5*BETA * (1 + th((T-(OMEG*(GSigeq**(-Q))))/H))

       (th : tangente hyperbolique,
        OMEG, Q et H constantes du modele,
        BETA : parametre permettant d'introduire le couplage)

     et dTheta0/dSigma = 0.5*BETA*Q*(OMEG/H)*(GSigeq**(-Q-2)) *
        [1-(th((T-(OMEG*(GSigeq**(-Q))))/H)**2] *
        [(9A1/(4B1+A1))*Sigm*II + 1.5*(B1/(B1+A1/4))*Sigprim]

     oa¹ GSigeq =
     ( (B1/(B1+A1/4)) * (Sigeq**2) + (9A1/(4B1+A1)) * (Sigm**2) ) ** 0.5

 La vitesse de la fonction de couplage dynamique Theta est definie par :
     vTheta(T,Sigeq) = signe(Theta0-Theta)*((Theta0-Theta)**2)/Theta0/to

       (Theta0 : fonction de couplage statique definie ci-dessus,
        to temps caracteristique constant dependant de la taille
        de grain pour le combustible UO2 et valant
        to = DYN1 * (1 + th((DYN2-T)/DYN3)) + 1 pour le combustible
        AFA3GLAA,
        DYN1, DYN2 et DYN3 constantes du modele)

   La vitesse de fluage thermique secondaire vEvp12 issue des deux
   mecanismes et du couplage statique entre eux est :

   vEvp12 = (1-Theta0)*vEvp1 + Theta0*vEvp2 + dTheta0/dSigma*(PSI2-PSI1)

   La vitesse de fluage thermique secondaire vEvp12 issue des deux
   mecanismes et du couplage dynamique entre eux est :

   vEvp12 = (1-Theta)*vEvp1 + Theta*vEvp2

   La vitesse de fluage thermique (primaire et secondaire) est :

   vEvp = vEvp0 + vEvp12

   Cette vitesse de fluage thermique vEvp est par ailleurs multipliee
   par un facteur d'acceleration dont l'expression est : 1 + K*PHI
     avec PHI flux de fissions
        K constante du modele

   Fluage induit par l'irradiation :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
   La vitesse vEvpir de fluage induit par l'irradiation est de la
   forme :

    vEvpir = A * PHI * (Sigma**(N3-1))*exp(-Q3/R*T)*(1.5*Sigprim)

      avec : Sigma : tenseur de contraintes
        Sigm = (trace Sigma)/3
        II : tenseur identite
        Sigprim = Sigma - Sigm*II
        A et N3 constantes du modele
        PHI flux de fissions
        Q3 energie d'activation du systeme
        R constante des gaz parfaits
        T temperature exprimee en Kelvin

   Dans le cadre de ce modele, les donnees a introduire et relatives au
   comportement visco-plastique du modele sont donc les suivantes :

   'R ' : constante des gaz parfaits

   Pour les deux mecanismes associes au fluage d'origine thermique :

   'DG ' : taille de grain

    pour le fluage primaire :

   'KP ' : constante du modele
   'AP ' : constante du modele
   'BP ' : constante du modele
   'QP ' : energie d'activation du fluage primaire

    pour le mecanisme 1 (fluage secondaire) :

   'K1 ' : constante du modele
   'M1 ' : constante du modele
   'Q1 ' : energie d'activation du mecanisme 1
   'N1 ' : constante du modele
   'CR ' : concentration en Chrome
   'CR1 ' : constante du modele
   'CR2 ' : constante du modele
   'CR3 ' : constante du modele

    pour le mecanisme 2 (fluage secondaire) :

   'K2 ' : constante du modele
   'M2 ' : constante du modele
   'Q2 ' : energie d'activation du mecanisme 2
   'N2 ' : constante du modele
   'DG0 ' : constante du modele

   Pour le couplage entre les deux mecanismes :

   'OMEG' : constante du modele
   'Q ' : constante du modele
   'H ' : constante du modele
   'BETA' : 1. ou 0. selon la presence ou non de couplage

   Pour l'acceleration du fluage thermique :

   'K ' : constante du modele

   Pour le fluage induit par l'irradiation :

   'A ' : constante du modele
   'Q3 ' : energie d'activation du systeme
   'N3 ' : constante du modele

   La vitesse de deformation liee au gonflement solide s'ecrit :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     vEgs = (1/3) * KGON * (d Bu / dt) * II

   La vitesse de deformation liee a la densification se calcule par :
   ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
     vEd = (1/3) *
      d/dt [-1*(1+KGON*Bu)*A*Ln(Bu/BUMI)/(1 - POR0 + A*Ln(Bu/BUMI))]
       * II

    avec II : tenseur identite

      Le coefficient A est obtenu par un processus iteratif qui
      necessite les donnees suivantes :

   'ADEN' : donnee specifique du materiau
   'KGON' : coefficient de gonflement
   'BUMI' : valeur seuil du taux de combustion en dessous de laquelle
        la masse volumique est constante

      Bu est le taux de combustion (variable interne du modele) :
      Son calcul a partir de l'evolution temporelle du flux de fissions
      PHI necessite les donnees suivantes :

   'RHO ' : masse volumique initiale
   'EFIS' : energie moyenne degagee par fission
   'POR0' : porosite initiale

   Donnees optionnelles :

   'TYPE' : 0. (par defaut) si combustible UO2, 1. si comb AFA3GLAA
   'COMP' : 0. (par defaut) si combustible compressible, 1. sinon
   'DYN ' : 0. (par defaut) si couplage statique,
        1. si couplage dynamique
   pour combustible UO2 :
   'DYN1' : constante de la fonction de couplage dynamique (to)
   pour combustible AFA3GLAA :
   'DYN1' : constante de la fonction de couplage dynamique
   'DYN2' : constante de la fonction de couplage dynamique
   'DYN3' : constante de la fonction de couplage dynamique

   Avant l'appel a l'operateur 'MATE', les donnees peuvent etre lues
   sur un fichier, et de plus mises en forme adaptee a CAST3M, par la
   procedure @GATTPAR de la facon suivante :

   fichier = 'nom du fichier de donnees' ;
   tata = '@GATTPAR' fichier ;
   (se reporter a la notice de la procedure @GATTPAR)

   Modele UO2 :

   Le modele UO2 decrit la viscoplasticite du combustible UO2
   standard ou dope au Chrome avec possibilite de fissuration en
   traction. Il s'agit d'un couplage entre le modele de fissuration
   propose par OTTOSEN et le modele viscoplastique GATT_MONERIE.
   Il fonctionne :
   - pour des elements massifs et pour les types de calcul
     tridimensionnel, axisymetrique, en deformations planes, en
     contraintes planes et en deformations planes generalisees.
   - pour des elements de type coques minces avec ou sans cisaillement
     transverse en tridimensionnel.

   Pour la description des donnees a introduire dans le cadre de ce
   modele, on se reportera au chapitre relatif au modele GATT_MONERIE
   en ce qui concerne les caracteristiques de viscoplasticite.

   Les caracteristiques de fissuration a fournir sont donnees ci-apres :

  ('LTR') : limite en traction (par defaut YOUN*1.2E-4)
  ('LTR1') : limite en traction pour la premiere direction de
        fissuration (par defaut LTR)
  ('LTR2') : limite en traction pour la deuxieme direction de
        fissuration (par defaut LTR)
  ('LTR3') : limite en traction pour la troisieme direction de
        fissuration (par defaut LTR) - sans objet en contraintes
        planes et pour les coques minces
  ('GFTR') : taux de restitution d'energie ou energie de fissuration
        (par defaut LTR*3.9E-5)
  ('GFT1') : energie de fissuration pour la premiere direction de
        fissuration (par defaut GFTR)
  ('GFT2') : energie de fissuration pour la deuxieme direction de
        fissuration (par defaut GFTR)
  ('GFT3') : energie de fissuration pour la troisieme direction de
        fissuration (par defaut GFTR) - sans objet en contraintes
        planes et pour les coques minces
  ('GS') : module traduisant la perte de resistance au cisaillement
        d'une fissure avec son ouverture (par defaut YOUN*1.8E-4)
  ('GS1') : pour la premiere direction de fissuration,
        module traduisant la perte de resistance au cisaillement
        de la fissure avec son ouverture (par defaut GS)
  ('GS2') : pour la deuxieme direction de fissuration,
        module traduisant la perte de resistance au cisaillement
        de la fissure avec son ouverture (par defaut GS)
  ('GS3') : pour la troisieme direction de fissuration,
        module traduisant la perte de resistance au cisaillement
        de la fissure avec son ouverture (par defaut GS) - sans
        objet en contraintes planes et pour les coques minces
  ('EPSR') : deformation a rupture dans la direction normale au plan
        de representation pour les calculs axisymetriques, en
        deformations planes et en deformations planes
        generalisees (par defaut 3.*LTR/YOUN)
  ('EPSB') : deformation caracterisant le changement de pente dans
        le cas d'une relation contrainte/deformation d'ouverture
        bilineaire dans la direction normale au plan de
        representation, pour les calculs axisymetriques, en
        deformations planes et en deformations planes
        generalisees (par defaut 0.)
  ('WRUP') : ouverture determinant la rupture d'une fissure
        (par defaut 0.)
  ('WRU1') : ouverture determinant la rupture d'une fissure pour la
        premiere direction de fissuration
        (par defaut WRUP ou 2*GFT1/LTR1 si WRUP=0.)
  ('WRU2') : ouverture determinant la rupture d'une fissure pour la
        deuxieme direction de fissuration
        (par defaut WRUP ou 2*GFT2/LTR2 si WRUP=0.)
  ('WRU3') : ouverture determinant la rupture d'une fissure pour la
        troisieme direction de fissuration
        (par defaut WRUP ou 2*GFT3/LTR3 si WRUP=0.) - sans objet
        pour les calculs axisymetriques, en deformations planes,
        en deformations planes generalisees, en contraintes
        planes et pour les coques minces
  ('BILI') : ouverture caracterisant le changement de pente dans le
        cas d'une relation contrainte/ouverture bilineaire
        (par defaut 0.)
  ('BIL1') : pour la premiere direction de fissuration, ouverture
        caracterisant le changement de pente dans le cas d'une
        relation contrainte/ouverture bilineaire
        (par defaut BILI)
  ('BIL2') : pour la deuxieme direction de fissuration, ouverture
        caracterisant le changement de pente dans le cas d'une
        relation contrainte/ouverture bilineaire
        (par defaut BILI)
  ('BIL3') : pour la troisieme direction de fissuration, ouverture
        caracterisant le changement de pente dans le cas d'une
        relation contrainte/ouverture bilineaire
        (par defaut BILI) - sans objet pour les calculs
        axisymetriques, en deformations planes, en deformations
        planes generalisees, en contraintes planes et pour les
        coques minces
  ('BTR') : fraction non recouvrable de l'ouverture d'une fissure
        (par defaut 0.2)
  ('SIMP') : conditionne le type de resolution souhaitee
        0. resolution exacte
        1. resolution simplifiee a energie de fissuration nulle
        (par defaut 0.)

  Remarque : les valeurs par defaut sont fournies dans le systeme
  ---------- d'unites international

  Dans un deuxieme temps, il faut obligatoirement adjoindre au CHAML de
  de sous-type CARACTERISTIQUES construit par l'operateur MATE, le CHAML
  resultat de l'operateur TAILLE applique au modele de calcul.

  En cas de grands deplacements, il faut definir l'option LAGRANGIEN de PASAPAS
  a TOTAL pour prendre correctement en compte l'evolution du repere local.

   Modele viscoplastique VISCODD :

   Les equations du modele sont de la forme :

   --> Notations : S tenseur des contraintes
        SEQ contrainte equivalente endommagee
        EP tenseur des deformations inelastiques
        p deformation inelastique equivalente cumulee
        M tenseur prenant en compte l'anisotropie de l'endommagem
        t temps
        <a> partie positive de a
        r variable d'ecrouissage isotrope
        R ecrouissage isotrope
        DD endommagement isotrope ductile
        YD taux de restitution d'energie d'endommagement ductile
        DC endommagement anisotrope de fluage
        YC taux de restitution d'energie d'endommagment de fluage
        H(.) fonction d'Heaviside

   --> Calcul de SEQ : SEQ = SQRT((S:M:S)/((1-DD)*(1-DC))
   --> Critere : F = SEQ - R - SIGY
   --> Ecrouissage: dR = b*(Ri - R)*dr
   --> Loi de Viscosite : dr = <F/k>**n dt
   --> Ecoulement : dEP = dr * M:S / (SEQ*(1-DD)*(1-DC))
   --> Loi d endommagment ductile : dDD = (YD/sd)**rd*dr * H(p-pd)
   --> Loi d endommagment de fluage : dDC = (YC/sc)**rc * dt * H(p-pc)

   Les parametres de la loi a introduire sont les suivants :

   'N ' : exposant de loi de viscoplasticite
   'K ' : module de viscosite
   'B ' : facteur d'ecrouissage
   'RI ' : valeur limite de l'ecrouissage
   'SIGY' : limite d elasticite
   'SD ' : facteur endommagement ductile
   'RD ' : exposant endommagement ductile
   'PD ' : seuil d'endommagement ductile
   'SC ' : facteur endommagement de fluage
   'RC ' : exposant endommagement de fluage
   'PC ' : seuil d'endommagement de fluage

   L'exemple visco2d.dgibi traite du fluage d'une eprouvette en 16MND5
   avec cette loi mais pour de plus amples renseignements il convient
   de se rapporter a la these de B. Vereecke :
   "Analyse probabiliste du comportement d'une famille d'aciers pour
    cuve de REP en cas d'accident grave ", These de doctorat,
    Universite Paris 6, LMT-Cachan

   Modele SYCO1

   Ce modele fonctionne en 2D contraintes planes, 2D deformations planes
   ou 3D pour des elements massifs ou elements XFEM

   Le comportement viscoplastique du materiau est modelise
   par la loi de Symonds & Cowper "standard" qui s'ecrit:

   sig_dyn(T,epse,rate_epse) = sig_stat(T,epse)*(1+(rate_epse/D)**(1/p))

   où sig_dyn est la contrainte equivalente de Von Mises en dynamique,
   sig_stat est la contrainte equivalente de Von Mises en statique,
   epse est la deformation plastique equivalente cumulee,
   rate_epse est la vitesse de deformation plastique equivalente,
   D et p sont les constantes caracteristiques de la viscosite du materiau.

   Parametres concernant l'ecrouissage statique du materiau:
   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.

   Parametres concernant la viscosite du materiau:
   'PSYC' p
   'DSYC' D

   Modele SYCO2

   Ce modele fonctionne en 2D contraintes planes, 2D deformations planes
   ou 3D pour des elements massifs ou elements XFEM

   Le comportement viscoplastique du materiau est modelise par une loi
   de Symonds & Cowper modifiee (cf. these de B. Prabel) qui s'ecrit:

   sig_dyn(T,epse,rate_epse) = sig_stat(T, epse)*(1+ H(T,epse)*(rate_epse**(1/p)

   où sig_dyn est la contrainte equivalente de Von Mises en dynamique,
   sig_stat est la contrainte equivalente de Von Mises en statique,
   epse est la deformation plastique equivalente cumulee,
   rate_epse est la vitesse de deformation plastique equivalente,
   et H(T, epse) = A + B * EXP(-epse/C).
   A, B, C et p sont les parametres caracteristiques de la viscosite du mate

   Parametres concernant l'ecrouissage statique du materiau:
   'ECRO' : mot-cle suivi de :
   EVOL1 : objet de type EVOLUTION, courbe d'ecrouissage du
        materiau donnant l'evolution de la contrainte
        equivalente en fonction de la deformation plastique
        cumulee. Le premier point de la courbe definit
        la limite elastique.

   Parametres concernant la viscosite du materiau:
   'PSYC' P
   'ASYC' A
   'BSYC' B
   'CSYC' C

   Modele FLUENDO3D

   Ce modele fonctionne en 3D pour des elements massifs, en 2D pour les
   deformations planes, ou 2D pour le mode axisymetrique.

   Le comportement est elastique, visqueux non lineraire, plastique
   et endommageable. Des pressions capillaires et chemo-mecaniques (RAG
   et DEF) agissement sur la matrice poreuse via la theorie de Biot.
   Des renforts reparties peuvent etre consideres (armatures longues
   et fibres courtes). Les lois de comportement utilisees sont detaillees
   dans la notice en ligne :

   https://hal.insa-toulouse.fr/hal-01710289v2/document

   Lors de la declaration du materiau, il convient de retenir que les
   parametres du 'noyau lineaire' du modele (YOUN, NU, ALPH, RHO, TREF,
   TALP) sont ceux du materiau homogeneise ( matrice, armatures et
   fibres comprises)

   les parametres du modele sont regroupes ci-dessous en fonction de la
   physique sous jacente qu'ils controlent. Omettre un de ces sous-ensembles
   revient a ne pas considerer ses effets.

   RAPPEL DU NOYAU LINEAIRE UTILISE POUR LA MATRICE DE RIGIDITE DES ELEMENTS

   'YOUN' : module d young homogeneise pour l hydratation maximale
   'NU ' : coefficient de Poisson homogeneise pour l hydratation maximale
   'ALPH' : coefficient de dilatation thermique lineique homogeneise
   'TREF' : temperature de reference pour le chargement thermique
   'TALP' : temperature de reference pour la dilatation thermique moyenne

   PAREMETRES GENERAUX LIES AUX OPTIONS DE CALCUL

   'DIM3' : dimension 3 en cas de calcul 2D
   'FIBR' : entier à mettre à 1 en presence de fibres courtes, 0 en l'absence de fibres
   'NREN' : nombre de types de renforts longs (armatures de beton arme par exemple), 0 si pas d armature
   'DALR' : coefficient de dilatation differentielle des renforts long par rapport a la matrice

   ETAT PHYSICO-CHIMIQUE DE LA MATRICE

   'HREF' : hydratation de reference pour la definition des parametres mecaniques
   'HYDR' : avancement chimique controlant la mecanique via la loi de De Schuter (hydratation pour le beton)
   'HYDS' : hydratation seuil

   ENDOMMAGEMENT

   'YORF' : Young matrice pour hydratation de reference
   'NURF' : Nu matrice pour hydratation de reference
   'RT ' : resistance a la traction pour l hydratation de reference HREF
   'REF ' : contrainte de refermeture de fissure pour HREF
   'RC ' : resistance a la compression pour HREF
   'DELT' : coeff de confinement pour le critere de Druker Prager
   'BETA' : dilatance pour l ecoulement non associe de Druker Prager
   'EPT ' : deformation au pic de traction (si endo pre pic de traction)
   'GFT ' : energie de fissuration en raction
   'EPC ' : deformation totale au pic de compression
   'EKDC' : deformation caracteristique pour la variation de module
   'DT80' : endommagement thermique caracteristique a 80°C
   'TSTH' : temperature seuil endo thermique
   'GFR ' : energie de refermeture des fissures de traction
   'ALTC' : Influence de l endo de traction sur celui de compresssion

   PRESSION INTRA POREUSE DUE A L ALCALI-REACTION (RAG)

   'VRAG' : volume de gel de RAG cree par unite de volume de materiau
   'HRAG' : ecrouissage relatif pour la plasticite de RAG
   'KRAG' : module de compressibilite pour le gel de rag
   'EKDG' : deformation caracteristique pour la loi d ecrouissage de rag
   'VVRG' : volume des vides accessibles a la RAG
   'CRAG' : coeff de concentration de contrainte pour l influence de la pression de rag sur la fissuration par traction diffuse
   'TRAG' : temps caracteristique de l alcali reaction a tref
   'NRJR' : energie d'activation de l alcali reaction
   'SRSR' : degre de saturation seuil pour la rag
   'TTRG' : temperature de reference pour la rag
   'DCDG' : coeff de couplag endo de rag endo de compression
   'ALRG' avancement chimique latent pour la rag
   'EPSG' deformation seuil pour amorcer l'endo de rag

   PRESSION D EAU INTRA POREUSE (EFFETS CAPILLAIRES)

   'PORO' : volume de pores CAPILLAIRES par unite de volume de materiau
   'VW ' : volume d eau pour le retrait par unite de volume de materiau
   'CSHR' : coeff de concentration de contrainte par les contraintes hydriques
   'BSHR' : coefficient de Biot pour le non sature
   'MSHR' : module de de la courbe de rention d eau de Van-Gnuchten
   'MVGN' : exposant pour la loi de Van-Genuchten
   'DCDW' : couplage entre endommagement hydrique et endommagement de compression
   'SKDW' : contrainte caracteristique caracterisant l endo hydrique
   'TTKW' : temperature caracteristique pour effets temperature sur isotherme
   'HSHR' : module d ecrouissage pour la micro fissure d origine capillaire
   'TTRW' : temperature de reference pour la definition de l'isotherme hydrique
   'KWRT' : coeff de couplage depression capillaire resitance a la traction
   'KWRC' : coeff de couplage sechage resistance a la compression

   FLUAGE DE LA MATRICE

   'EKFL' : deformation caracteristique potentiel de fluage
   'YKSY' : rapport module kelvin / module elastique
   'XFLU' : endommagement maximum par fluage
   'TAUK' : temps caracteristique kelvin
   'TAUM' : temps caracteristique maxwell
   'NRJM' : NRJ activation du potentiel de fluage de Maxwell
   'TTRF' : temperature de reference pour le fluage propre
   'DFMX' : endommagement maxi par fluage
   'MDTT' : module de Biot pour la deformation visqeuse (ou thermique) transitoire (DTT)
   'TDTT' : temps caracteristique pour la deformation thermique transitoire a la temperature TTRF
   'WDTT' : quantite d eau de reference dans les C-S-H pour le calcul des surpressions en DTT
   'PDTT' : pression d eau caracteristique dans les CSH pour la DTT

   EFFET D ECHELLE PROBABILISTE DE WEIBULL POUR LA MATRICE

   'VREF' : volume de ref pour la mesure de RTP
   'VMAX' : volume max pour methode wl2
   'CVRT' : coeff de variation de la resistance en traction

   PRESSION INTRAPOREUSE DUE A LA FORMATION D ETTRINGITE DIFFEREE (DEF)

   'TPRD' : temps cracteristique pour la precipitation de la def
   'NRJP' : energie d activation de precipitation de la def
   'SRSD' : saturation caracteristique pour les reactions de def
   'VDEF' : quantite maximale de def par unite de volume de materiau
   'NALD' : teneur en alcalin libre en solution pour la def
   'SSAD' : rappot sulfate sur aluminium du ciment pour la def
   'NAKD' : seuil caracteristique en alcalins pour la DEF
   'NABD' : seuil en alcalins pour le blocage de la DEF
   'EXND' : exposant de la loi de couplage temperature seuil - alcalinspour la def
   'EXMD' : exposant de la loi de couplage vitesse de precipitation -alcalins pour la def
   'TTKD' : temperature caracteristique de dissolution de l ettringite pour la def
   'TDID' : temps caracteristique de dissolution des aluminates pour la def
   'TFID' : temps caracteristique de fixation de l aluminium dans les hydrogrenats
   'NRJD' : energie d activation de dissolution de la def
   'TTRP' : temperature de reference pour le temps caracteristique de precipitation de la def
   'EKDS' : deformation caracteristique pour l endo par la def
   'TTKF' : temperature seuil pour la fixation des al dans les hydrogrenats en cas de def
   'NRJF' : energie d activation pour la fixation des alu dans les hydrogrenats
   'NSUL' : nombre de moles de sulfates
   'HDEF' : modules d ecrouissage pour la DEF
   'KDEF' : module de compressibilite de la DEF
   'VVDF' : Module de biot pour la DEF
   'CDEF' : coeff de concentration de contrainte pour les effets de la pression de DEF sur la matrice
   'DCDS' : coeff de couplage endo de def endo de compression

   COMPORTEMENT FLUIDE DU MATERIAU AVANT LE SEUIL D HYDRATATION

   'SSJA' : contrainte seuil minimale pour initier le fluage lorsque HYDR<HYDS
   'TMJA' : temps caracteristique ecoulement etat liquide lorsque HYDR<HYDS
   'YOJA' : module d young jeune age lorsque HYDR<HYDS
   'NUJA' : coefficient de poisson jeune age lorsque HYDR<HYDS
   'DLJA' : coeff DELTA de Drucker Prager au jeune age lorsque HYDR<HYDS
   'RCJA' : RC jeune age lorsque HYDR<HYDS
   'RTJA' : RT jeune age

   COMPORTEMENT DES RENFORTS LONGS (REPETABLE DE 1 A 5 RENFORTS, EN MODIFIANT L INDICE 1)

   Geometrie des armatures de type 1
   'ROA1' : densite volumique des armatures de type 1
   'VR11' : projection sur le 1er axe (2eme indice) de la base globale du vecteur unitaire d orientation de l armature de type 1 (1er indice)
   'VR12' : projection sur le 2eme axe (2eme indice) de la base globale du vecteur unitaire d orientation de l armature de type 1 (1er indice)
   'VR13' : projection sur le 3eme axe (2eme indice) de la base globale du vecteur unitaire d orientation de l armature de type 1 (1er indice)

   Comportement instantane des armatures de type 1
   'PRE1' : precontrainte initiale
   'YOR1' : module d Young de armature de type 1
   'SYR1' : limite elastique
   'HPL1' : module d ecrouissage cinematique
   'SUR1' : contrainte maximale de traction
   'EPU1' : deformation plastique de debut d ecrouissage negatif de l armature
   'WPR1' : energie surfacique de rupture localisee de l armature

   Comportement instantane a l interface armature de type 1 / matrice
   'DEQ1' : diametre equivalent de l armature de type 1
   'TYR1' : contrainte de cisaillement de l interface armature matrice
   'HIR1' : rigidite de l interface armature / matrice

   Comportement differe de l armature de type 1
   'TTR1' : temperature de reference pour les donnees de fluage de l armature
   'SKR1' : contrainte de reference pour la mesure des parametres visqueux
   'TMR1' : temps caracteristique du module de visqueux de Maxwell consolidant
   'EKR1' : potentiel de fluage pour la loi de consolidation
   'XFL1' : coefficient de non linearite du fluage de Maxwell
   'TKR1' : temps caracteristique du fluage reversible
   'YKY1' : rapport entre la deformation elastique et la deformation de fluage reversible (Kelvin)

   Influence de la temperature sur le comportement differe de l armature de type 1
   'ATR1' : energie d activation du fluage
   'CTM1' : coefficient de couplage thermo-mecanique pour le fluage en temperature
   'MUS1' : tau de chargement a partir duquel l activation thermique depend du chargement
   'XNR1' : exposant de la loi d activation thermique du fluage de l armature

   COMPORTEMENT DES FIBRES

   Geometrie pour les fibres
   'RHOF' : densite volumique de fibres
   'DIFI' : diametre des fibres
   'LOFI' : longueur des fibres
   'EOF1' : valeur de l'ellipsoide d'orientation des fibres dans la direction VF1
   'EOF2' : valeur de l'ellipsoide d'orientation des fibres dans la direction VF2
   'EOF3' : valeur de l'ellipsoide d'orientation des fibres dans la direction VF3
   'VF11' : composante 1 du premier vecteur principal d'inclinaison des fibres
   'VF12' : composante 2 du premier vecteur principal d'inclinaison des fibres
   'VF13' : composante 3 du premier vecteur principal d'inclinaison des fibres
   'VF21' : composante 1 du second vecteur principal d'inclinaison des fibres
   'VF22' : composante 2 du second vecteur principal d'inclinaison des fibres
   'VF23' : composante 3 du second vecteur principal d'inclinaison des fibres

   Comportement mecanique pour les fibres
   'YOFI' : module d'Young des fibres
   'FYF ' : limite elastique des fibres
   'FU ' : contrainte ultime admissible par une fibre

   Caracterisation Statistique de la matrice autour des fibres
   'RTEC' : resistance moyenne à la traction du beton issue d'un essai de reference de longueur LECH dans la direction de traction
   'LECH' : longueur de l'essai de reference dans la direction de traction
   'MW ' : coefficient de Weibull lie à la dispersion des resistances à la traction du beton

   Comportement mecanique de l interface fibre/matrice
   'HFI ' : rigidite de l'interface fibre-matrice
   'TMAX' : contrainte de debut de decollement de l'interface fibre-matrice
   'TD ' : contrainte de frottement fibre-matrice en zone decollee
   'SK ' : glissement caracteristique d'abrasion de l'interface en phase d'arrachement des fibres
   'MECR' : module d'ecrouissage (contrainte) liee à l'accumulation de particules à l'interface fibre-matrice en phase d'arrachement des fibres
   'LCAN' : longueur ancree caracteristique liee à l'impact de l'ancrage sur l'abrasion fibre-matrice phase d'arrachement des fibres
   'FABO' : force d'about lie à un defaut d'extremite des fibres
   'ALEC' : angle d'ouverture du pentaedre d'ecaillage (degres)
   'MUF ' : coefficient de frottement fibre-matrice pour les fibres inclinees par rapport à la direction d'extraction

   Modele INCLUSION3D

   Ce modele fonctionne en 3D pour des elements massifs, en 2D pour les
   deformations planes, ou 2D pour le mode axisymetrique.

   Le comportement est elastique, visqueux, plastique et endommageable.
   Des pressions capillaires ou physico-chimiques agissement sur less
   phases supposee poreuses via la theorie de Biot. La version actuelle
   ne fonctionne que pour une matrice contenant un seul type d inclusion.
   la somme des fractions volumique des phases doit etre egale a 1.

   https://hal.insa-toulouse.fr/hal-01710289v2/document

   les parametres du modele sont regroupes ci-dessous en fonction de la
   physique sous jacente qu'ils controlent.

   RAPPEL DU NOYAU LINEAIRE UTILISE POUR LA MATRICE DE RIGIDITE DES ELEMENTS

   'YOUN' : module d young homogeneise
   'NU ' : coefficient de Poisson homogeneise
   'ALPH' : coefficient de dilatation thermique lineique homogeneise
   'TREF' : temperature de reference pour le chargement thermique
   'TALP' : temperature de reference pour la dilatation thermique moyenne
   'DIM3' : dimension hors plan si 2D

   PARAMETRES GENERAUX

   'NINC' : nombre de types d inclusions (la version actuelle ne fonctionne que pour 1)
   'TTRF' : temperature de reference pour l ensemble des parametres des phases
   'RT ' : resistance du maillon faible pour la localisation
   'RR 'resistance a la refermeture pour la localisation

   PARAMETRES PROPRES AUX PHASES ( INDICE 0 POUR LA MATRICE, A REPETER AVEC INDICE 1 POUR L INCLUSION)

   Mecanique lineaire
   'FRA0' : fraction volumique
   'YOU0' : module de Young
   'NUP0' : coefficient de Poisson
   'ALP0' : coefficient de dilatation thermique

   Fluage
   'TFL0' : temps caracteristique du fluage pour kelvin et pour Maxwell
   'EAF0' : energie d activation thermique du fluage
   'FLM0' : coefficient de fluage non lineaire pour le potentiel de fluage de Maxwell
   'FLK0' : coefficient de fluage reversible de Kelvin (deformation de fluage reversible / deformation elastique)

   Plasticite parfaite associess au criteres de Rankine
   'RTP0' : resistance effective en traction de la phase
   'RFP0' : contrainte de refermeture de fissure pour la phase
   'RTI0' : resistance a la traction en contrainte totale pour l interface externe a la pahse
   'RFI0' : contrainte de refermeture de fissure pour l interface externe a la phase

   Plasticite parfaite associee au critere de Drucker Prager
   'DLT0' : coefficient de frottement interne pour le critere de Drucker Prager
   'BTA0' : coefficient de dilatance pour l ecoulement de Drucker Prager
   'COH0' : cohesion en cisaillement pour le critere de Drucker Prager

   Effets de l eau intra-poreuse
   'POR0' : porosite (en fraction volumique de la phase)
   'SWP0' : saturation en eau de la porosite de la phase
   'MVG0' : module de Van Genuchten pour la courbe de rentention d eau
   'NVG0' : exposant de Van Genucten pour la courbe de rentention d eau
   'CPH0' : variation de volume de la phase par effets osmotiques

   Effets de la pression intra-poreuse due aux phases neoformees
   'VCH0' : potentiel de gonflement chimique de la phase (en fraction volumique de la phase)
   'SRS0' : saturation en eau minimale pour la reaction chimique
   'TCH0' : temps caracteristique de la reaction chimique
   'EAC0' : energie d'activation de la reaction chimique
   'ACS0' : avancement de la reaction au moment de l initiation du gonflement
   'KCH0' : coefficient de compressibilite du produit chimique neoforme

   Modele ENDO3D

   Ce modele fonctionne en 3D pour des elements massifs, en 2D pour les
   deformations planes, ou 2D pour le mode axisymetrique.

   Le comportement est elastique, plastique et endommageable. Des
   pressions capillaires agissement sur la matrice poreuse via la
   theorie de Biot.

   https://hal.insa-toulouse.fr/hal-01710289v2/document

   les parametres du modele sont regroupes ci-dessous en fonction de la
   physique sous jacente qu'ils controlent. Omettre un de ces sous-ensembles
   revient a ne pas considerer ses effets.

   RAPPEL DU NOYAU LINEAIRE UTILISE POUR LA MATRICE DE RIGIDITE DES ELEMENTS

   'YOUN' : module d young
   'NU ' : coefficient de Poisson
   'ALPH' : coefficient de dilatation thermique lineique
   'TREF' : temperature de reference pour le chargement thermique
   'TALP' : temperature de reference pour la dilatation thermique
   'DIM3' : dimension hors plan si 2D

   COMPORTEMENT MECCANIQUE A LA TEMPERATURE DE REFERENCE

   criteres de Rankine en traction et refermeture de fissures
   'RT ' : resistance a la traction
   'EPT ' : deformation au pic de traction
   'GFT ' : energie de fissuration de traction
   'REF ' : contrainte de refermeture de fissure
   'GFR ' : energie de refermeture des fissures de traction

   critere de cisaillement
   'RC ' : resistance a la compression
   'EPC ' : deformation au pic de compression
   'DCPK' : endomagement au pic de compression
   'DELT' : coefficient de confinement pour le critere de Druker Prager
   'BETA' : dilatance pour l ecoulement de Druker Prager
   'EKDC' : deformation caracteristique pour l endo de compression
   'ALTC' : coefficient de couplage endo de traction / endo de compression

   critere de CamClay
   'PORO' : porosite initiale de la matrice
   'MCC' : Module d ecrouissage initial pour Cam Clay
   'PPCC' : pression de preconsolidation à porosite initiale
   'PFCC' : pression de fin de consolidation pour CamClay

   INFLUENCE DE LA TEMPERATUE SUR LE COMPORTEMENT MECANIQUE

   Influence de la temperature sur le module d Young
   'TT0E' : temperature de debut de reduction thermique pour le module d Young
   'TT1E' : temperature mediane de reduction thermique pour le module d Young
   'MTTE' : exposant de non linearite pour le module d Young
   'PTTE' : fraction residuelle du module d Young a haute temperature

   Influence de la temperature sur la resistance a la compression
   'TT0C' : temperature de debut de reduction thermique pour Rc
   'TT1C' : temperature mediane pour la reduction thermique pour Rc
   'MTTC' : exposant de non linearite de la reduction thermique pour Rc
   'PTTC' : fraction residuelle de resistance a la compression a haute temperature

   Influence de la temperature sur la resistance a la traction
   'TT0T' : temperature de debut de reduction thermique pour Rt
   'TT1T' : temperature mediane de reduction thermique pour Rt
   'MTTT' : exposant de non linearite pour l evolution thermique de Rt
   'PTTT' : fraction residuelle de resistance en traction a haute temperature

   FUSION :

   Pour tous les modeles visco-plastiques, l'option FUSION met a zero
   les variables internes du modele si la temperature au point
   d'integration est superieure a la temperature de fusion, donnee par :

   'TFUS' : FLOTTANT, temperature de fusion du materiau.

PART{MECANIQUE VISCO_EXTERNE}
   | Noms des parametres pour un materiau VISCO_EXTERNE |

   Les parametres des lois du groupe 'VISCO_EXTERNE' sont les memes que
   ceux du comportement 'ELASTIQUE' 'ISOTROPE'.

PART{MECANIQUE NON_LOCAL}
   | Noms des parametres pour une mise en oeuvre en NON_LOCAL |

   FORMULATIONS NON LOCALES INTEGRALES

    Pour une mise en oeuvre non locale de type 'MOYE' il faut
    introduire la longueur caracteristique 'LCAR'.

    Pour une mise en oeuvre non locale de type 'SB' il faut
    introduire la longueur caracteristique 'LCAR' et la contrainte
    limite de traction 'SBFT' pour la normalisation.

   FORMULATIONS NON LOCALES DIFFERENTIELLES

    Pour une mise en oeuvre non locale de type Helmholtz, les parametres
    suivants doivent etre introduits en faisant varier le 1er indice (1)
    jusqu’au nombre de formulations non locales de Helmholtz declarees avec le
    modele (voir la notice de MODE avec les options 'NON_LOCAL' 'MOYE' 'HELM')

    Pour une variable scalaire non locale X1 induite par une source locale S1,
    l’equation de Helmholtz est consideree comme anisotrope avec 3 directions
    de diffusion (i=1..3), chaque direction de diffusion est specifiee
    en utilisant un vecteur d’orientation V1i de composantes V1ij dans
    la base globale (xj=1..3) :

    CAP1. X1 - somme (i=1..3) DH1i. somme (j=1..3) d( somme (k=1..3) (V1ij.V1ik). dX1/dxk)/dxj = S1

    'CAP1' : terme capacitif pour l equation d Helmhotz (defaut 1.)
    'BLO1' : indicateur de conditions aux limites de Dirichlet (defaut 0 = non)
    'DEP1' : valeur du deplacement impose sur la condition aux limites de Dirichlet (defaut 0.)
    'INI1' : valeur initiale de la variable de Helmholtz
    'LIN1' : indicateur de linearite du probleme (par defaut 0, le probleme est alors suppose non lineaire et une boucle de convergence permet d acceder aux sousiterations d Helmholtz avec istep=3 dans le modele, les parametres de controle de la boucle de sous iteration sont reglables, cf. notice de pasapas)
    'DH11' : coefficient de diffusion non locale dans la direction 1 (i.e. lc1**2/2 avec lc1 longueur caracteristique direction 1)
    'V111' : projection sur le 1er axe du repere global du vecteur de direction de diffusion 1
    'V112' : projection sur le 2eme axe du repere global du vecteur de direction de diffusion 1
    'V113' : projection sur le 3eme axe du repere global du vecteur de direction de diffusion 1
    'DH12' : coefficient de diffusion non locale dans la direction 2 (i.e. lc2**2/2 avec lc1 longueur caracteristique direction 1)
    'V121' : projection sur le 1er axe du repere global du vecteur de direction de diffusion 2
    'V122' : projection sur le 2eme axe du repere global du vecteur de direction de diffusion 2
    'V123' : projection sur le 3eme axe du repere global du vecteur de direction de diffusion 2
    'DH13' : coefficient de diffusion non locale dans la direction 3 (i.e. lc3**2/2 avec lc1 longueur caracteristique direction 1)
    'V131' : projection sur le 1er axe du repere global du vecteur de direction de diffusion 3
    'V132' : projection sur le 2eme axe du repere global du vecteur de direction de diffusion 3
    'V133' : projection sur le 3eme axe du repere global du vecteur de direction de diffusion 3 ;

PART{MECANIQUE IMPEDANCE}
   | Noms des parametres pour un materiau IMPEDANCE  |
   remarques :
   - Pour un support POI1, 3 parametres facultatifs supplementaires :
   'CPLE' : module de torsion (Nm) (type 'FLOTTANT')
   'INER' : moment d'inertie (type 'FLOTTANT')
   'AROT' : amortissement reduit en rotation (%)

   - pour combiner le modele IMPEDANCE ELASTIQUE avec un materiau
   non-lineaire (par exemple 'PLASTIQUE' 'PARFAIT') on complete avec
   les parametres du materiau vise.

   Modele IMPEDANCE ELASTIQUE :
   'RAID' : raideur (N/m) (type 'FLOTTANT')

   Parametres facultatifs
   'MASS' : masse (type 'FLOTTANT')
   'AMOR' : amortissement generalise (%) (type 'FLOTTANT')
   'ZNU' : coefficient numerique utilise comme coefficient de Poisson
   'ALPH' : coefficient de dilatation thermique secant

   Modele IMPEDANCE REUSS ou IMPEDANCE VOIGT :
   'RAID' : raideur (N/m) (type 'FLOTTANT')
   'VISC' : viscosite de friction (Ns/m) (type 'FLOTTANT')

   Parametres facultatifs
   'MASS' : masse (type 'FLOTTANT')
   'AMOR' : amortissement generalise (%) (type 'FLOTTANT')

   Modele IMPEDANCE COMPLEXE :
   'MOCO' : module complexe (type 'EVOLUTION')
   - composante 'RAID' (type 'EVOLUTION'),
        abscisse frequence 'FREQ' ou 'TEMP' (type 'LISTREEL')
        ordonnee raideur 'MOCO' (N/m) (type 'LISTREEL')
   - composante 'VISC' (type 'EVOLUTION'),
        abscisse frequence 'FREQ' ou 'TEMP' (type 'LISTREEL')
        ordonnee viscosite 'VISC' (Ns/m) (type 'LISTREEL')

   Parametres facultatifs
   'MASS' : masse (type 'FLOTTANT')
   'AMOR' : amortissement generalise (%) (type 'FLOTTANT')

PART{MECANIQUE CAOUTCHOUC}
   | Noms des parametres pour un materiau CAOUTCHOUC  |

 MATE : HYPERELASTIQUE
L Gornet, Ecole Centrale Nantes, GeM

Les densites d'energie de type Mooney-Rivlin, Biderman, Hart-Smith,
Arruda-Boyce et GD sont disponibles en formulation
incompressible dans le cas des contraintes planes.
Les modeles quasi-incompressibles sont implantes sous les hypotheses
tridimensionnelle et deformations planes.
Les parametres par defaut correspondent a un caoutchouc a 8% de
sulfure vulcanise pendant 3 heures.
Le materiau est du type de celui presente dans Treloard (1944).
On suppose de plus qu'il est equivalent a celui de Kawabata el al. 1981.
Ce caoutchouc presente l'avantage d'etre fortement elastique
reversible sans presenter de cristallisation sous contrainte jusqu'a
400% d'extension. Il est donc bien decrit par des modeles hyperelastiques.

Dans le cas des materiaux quasi-incompressible, on partitionne
l'energie elastique W en une partie isochore Wiso(Ib1, Ib2) et
une partie hydrostatique W(J). Les invariants Ib1 et Ib2 sont
construits a partir du gradient de la transformation Fb= J**(-1/3) F
avec I3=J**2

W(J). = 5/ D (J-1)**2, ou D represente le coefficient
de penalite (1.E-4 par defaut).

TRELOAR L. R. G., "Stress-strain data for vulcanised rubber
under various types of deformation", Trans. Faraday Soc., Vol. 40,
pp. 59-70, 1944.
KAWABATA S., MATSUDA M., TEI K., ET KAWAI H., "Experimental survey of
the strain energy density function of isoprene rubber vulcanizate",
Macromolecules,14 , pp. 154-162, 1981.
J. LEMAITRE, J.L. CHABOCHE, A BENALLAL, R. DESMORAT, Mecanique des
materiaux solides, 3eme edition, Dunod 2009

   Modele MOONEY-RIVLIN :
hyperelastique Mooney Rivlin
Incompressible : W(I1,I2,I3=1)=C10 (I1-3)+C20*(I2-3)
Quasi-incompressible : W(Ib1,Ib2,I3=J**2)= Wiso(Ib1, Ib2)+.5/ D (J-1)**2
Caoutchouc Treloard / Kawabata, 2 parametres : C1 = 0.183 MPa ;
C2 = 0.0034 MPa
Le modele Neo-Hookeen correspond a C20=0 et C10 = nkT=0.4 MPa

   Modele BIDERMAN :
Modele : hyperelastique Biderman
Incompressible :
W(I1,I2,I3=1)=C10 (I1-3)+C20*(I1-3)**2+C30*(I1-3)**3+ C01 (I2-3)
Quasi-incompressible : W(Ib1, Ib2, I3=J**2)=Wiso(Ib1,Ib2)+.5/ D (J-1)**2
Caoutchouc Treloard / Kawabata : 4 parametres
C01 = 0.0233 MPa; C10 = 0.208 MPa ;C20 = -0.0024 MPa C30 = 0.0005MPa

   Modele HART-SMITH :
Modele hyper elastique : Hart-Smith
Incompressible :
W(I1, I3=1)= G* Intg (exp(K1 ( I1 -3)**2) dI1)+3 K2 ln(I2/3)
Quasi-incompressible :
W(Ib1, Ib2, I3=J**2)= Wiso(Ib1, Ib2)+.5/ D (J-1)**2
Caoutchouc Treloard / Kawabata : 3 parametres
G = 0.175 MPa ;K1 = 2.86E-4 MPa ; K2 = 0.311 MPa

   Modele 8-CHAINES :
Modele : Densite d'energie hyperelastique 8-Chaines
Le modele est implante a partir du developpement de Taylor de
l'inverse de la fonction de Langevin a l'ordre 5.
Incompressible :
W(I1, I3=1)= NKT (Sommes sur n de (Cn / N**(n-1) (I1**n-3**n))
Cn sont les coefficients du developpement de Taylor
Quasi-incompressible : W(Ib1, I3=J**2)= Wiso(Ib1)+.5/ D (J-1)**2
Caoutchouc Treloard / Kawabata, 2 parametres : NKT = 0.28 MPa VN= 25.4

   Modele 8-CHAINES :
Modele hyper elastique : GD
Ce modele exprime a partir des invariants a des performances identiques
au modele Ogden 5 parametres (Gornet, Club Cast3M 2009).
Le modele 8 Chaines (equivalent a la partie en I1 du modele Hart-Smith)
est confine par le reseau avoisinant (energie de l'enveloppe)
Incompressible :
W(I1, I3=1)= H1* Intg (exp(H3 ( I1 -3)**2) dI1)+3H2 Intg (dI2/I2**2)
Quasi-incompressible : W(Ib1, Ib2, I3=J**2)= Wiso(Ib1, Ib2)+.5/ D (J-1)**2
Caoutchouc Treloard / Kawabata : 3 parametres
H1 = 0.142236 MPa; H2 = 1.5854659E-2 MPa ; H3 = 3.4946541E-4 MPa

PART{MECANIQUE ELASTIQUE ORTHOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ORTHOTROPE |

   Coques minces (COQ2, COQ3, DKT)

    'YG1 ', 'YG2 ' : modules d'Young
    'NU12' : coefficient de Poisson
    'G12 ' : module de cisaillement
    'ALP1', 'ALP2' : coefficients de dilatation thermique secants
    'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
    'TALP' : temperature de reference du coefficient de dilatation
    'RHO ' : masse volumique

   Coques avec cisaillement transverse (DST, COQ4, COQ6, COQ8)

    'YG1 ', 'YG2 ' : modules d'Young
    'NU12' : coefficient de Poisson
    'G12 ' 'G23 ', 'G13 ' : modules de cisaillement
    'ALP1', 'ALP2' : coefficients de dilatation thermique secants
    'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
    'TALP' : temperature de reference du coefficient de dilatation
    'RHO ' : masse volumique

   Elements joints 3D (JOI4)

    'KS1 ', 'KS2 ' : raideurs de cisaillement selon les
        directions 1 et 2 du plan du joint
        ( N/m3 )
    'KN ' : raideur normale au plan du joint
        ( N/m3 )
    'RHO ' : masse volumique du joint ( kg/m2 )
    'ALPN' : coefficient de dilatation thermique secant
        suivant la normale au joint ( m/K )
    'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
    'TALP' : temperature de reference du coefficient de dilatation

   Elements joints unidimensionnels en 3D (JOI1)

   Les unites sont donnees a titre indicatif en systeme SI.

   'KS1 ', 'KS2 ' : raideurs de cisaillement selon les
        directions 1 et 2 du plan normal
        a l'axe du joint ( N/m )
   'KN ' : raideur normale ( N/m )
   'QS1 ', 'QS2 ' : raideur angulaire de flexion selon
        les directions 1 et 2 du plan
        normal a l'axe du joint ( N.m )
   'QN ' : raideur angulaire de torsion ( N.m )
   'ALPN' : coefficient de dilatation thermique secant dans la
        direction normale au joint ( m/K )
   'ALP1' : coefficient de dilatation thermique secant dans la
        direction transverse #1 au joint ( m/K )
   'ALP2' : coefficient de dilatation thermique secant dans la
        direction transverse #2 au joint ( m/K )
   'ALQN' : coefficient de dilatation thermique secant en rotation
        selon la direction normale au joint ( 1/K )
   'ALQ1' : coefficient de dilatation thermique secant en rotation
        selon la direction transverse #1 au joint ( 1/K )
   'ALQ2' : coefficient de dilatation thermique secant en rotation
        selon la direction transverse #2 au joint ( 1/K )
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'MASS' : masse totale du bloc represente par l'element
        joint ( kg )
   'JX ' : inertie de rotation autour de l'axe X ( kg/m**2 )
   'JY ' : inertie de rotation autour de l'axe Y ( kg/m**2 )
   'JZ ' : inertie de rotation autour de l'axe Z ( kg/m**2 )

   Elements joints unidimensionnels en 2D (JOI1)

   Les unites sont donnees a titre indicatif en systeme SI.

   'KS ' : raideur de cisaillement ( N/m )
   'KN ' : raideur normale ( N/m )
   'QS ' : raideur angulaire de flexion ( N.m )
   'ALPN' : coefficient de dilatation thermique secant dans la
        direction normale au joint ( m/K )
   'ALPS' : coefficient de dilatation thermique secant dans la
        direction transverse ( m/K )
   'ALQS' : coefficient de dilatation thermique secant en rotation
        ( 1/K )
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'MASS' : masse totale du bloc represente par l'element
        joint ( kg )
   'JZ ' : inertie de rotation autour de l'axe Z ( kg/m**2 )

   Massifs tridimensionnels

    'YG1 ', 'YG2 ', 'YG3 ' : modules d'Young
    'NU12', 'NU23', 'NU13' : coefficients de Poisson
    'G12 ', 'G23 ', 'G13 ' : modules de cisaillement
    'ALP1', 'ALP2', 'ALP3' : coefficients de dilatation thermique secants
    'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
    'TALP' : temperature de reference du coefficient de dilatation
    'RHO ' : masse volumique

   Massifs bidimensionnels

   | contrainte plane  | deformation plane  | serie de Fourier  |
   |  | axisymetrique  |  |
   |--------------------|--------------------|----------------------|
   |'YG1','YG2'  |'YG1', 'YG2', 'YG3' | 'YG1', 'YG2', 'YG3'  |
   |'NU12''G12 '  |'NU12','NU23','NU13'| 'NU12','NU23','NU13' |
   |'YG3' 'NU23','NU13' |'G12 '  | 'G12 ','G23 ','G13 ' |
   |'ALP1','ALP2'  |'ALP1','ALP2','ALP3'| 'ALP1','ALP2','ALP3' |
   |'TREF','TALP'  |'TREF','TALP'  | 'TREF','TALP'  |
   |'RHO'  |'RHO '  | 'RHO'  |

   Remarques
   - Dans le cas du modele NON_LINEAIRE UTILISATEUR affecte aux massifs
     bidimensionnels et tridimensionnels, les parametres specifiques a
     l'elasticite orthotrope doivent etre donnes dans l'ordre defini
     ci-dessus, la definition du repere d'orthotropie (mot-cles
     'DIRECTION'...ou 'RADIAL'...) survenant apres la donnee du ou des
     modules de cisaillement, donc avant la donnee des coefficients de
     dilatation thermique.
   - Dans le cas du modele NON_LINEAIRE UTILISATEUR affecte aux elements
     finis 1D, les modules d'Young et les coefficients de Poisson
     doivent etre donnes dans le meme ordre que celui defini pour les
     massifs tridimensionnels.

PART{MECANIQUE ELASTIQUE ANISOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ANISOTROPE |

   Massifs tridimensionnels

    Les noms des parametres dans un cas tridimensionnel correspondent
    aux 21 termes independants de la matrice de Hooke pour un materiau
    anisotrope :

    | sig1 |  |D11  sym.  |  | eps1  |
    | sig2 |  |D21 D22  |  | eps2  |
    | sig3 | =  |D31 D32 D33  |  x  | eps3  |
    | tau12|  |D41 D42 D43 D44  |  | gama12|
    | tau13|  |D51 D52 D53 D54 D55  |  | gama13|
    | tau23|  |D61 D62 D63 D64 D65 D66 |  | gama23|

    A ces parametres il faut ajouter (si necessaire) :

     'ALP1','ALP2','ALP3' : coefficients de dilatation thermique secants
     'AL12','AL23','AL13'
     'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
     'TALP' : temperature de reference du coefficient de dilatation
     'RHO' : masse volumique

   Massifs bidimensionnels

   |  contrainte plane  | deformation plane  | serie de Fourier  |
   |  | axisymetrique  |  |
   |'D11','D21','D22'  |'D11','D21','D22'  | 'D11','D21','D22'  |
   |'D31','D32','D33'  |'D31','D32','D33'  | 'D31','D32','D33'  |
   |'D41','D42','D43'  |'D41','D42','D43'  | 'D41','D42','D43'  |
   |'D44'  |'D44'  | 'D44','D55','D65'  |
   |  |  | 'D66'  |
   |'ALP1','ALP2','AL12'|'ALP1','ALP2','ALP3'| 'ALP1','ALP2','ALP3' |
   |'TREF','TALP'  |'AL12','TREF','TALP'| 'AL12','TREF','TALP' |
   |'RHO '  |'RHO '  | 'RHO '  |

   Remarque : Dans le cas des contraintes planes, les coefficients D11,
        D21, ... doivent etre les memes que dans le cas des
        deformations planes. Les modifications dues a l'hypothese
        des contraintes planes sont effectuees par l'operateur.

        L'option anisotrope n'est pas definie pour les elements
        joints.

   Elements joints unidimensionnels en 3D (JOI1)

    Les unites sont donnees a titre indicatif en systeme SI.

    Les noms des parametres dans un cas tridimensionnel correspondent
    aux 21 termes independants de la matrice de Hooke pour un materiau
    anisotrope :

    | EFFX |  |D11  sym.  |  | EXX  |
    | EFFY |  |D21 D22  |  | GXY  |
    | EFFZ | =  |D31 D32 D33  |  x  | GXZ  |
    | MOMX |  |D41 D42 D43 D44  |  | CXX  |
    | MOMY |  |D51 D52 D53 D54 D55  |  | CXY  |
    | MOMZ |  |D61 D62 D63 D64 D65 D66 |  | CXZ  |

    A ces parametres il faut ajouter (si necessaire) :

     'ALP1','ALP2','ALP3' : coefficients de dilatation thermique secants
     'ALQ1','ALQ2','ALQ3' en translation et en rotation
     'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
     'TALP' : temperature de reference du coefficient de dilatation
     'MASS ' : masse totale du bloc represente par l'element
        joint ( kg )
     'JX ' : inertie de rotation autour de l'axe X ( kg/m**2 )
     'JY ' : inertie de rotation autour de l'axe Y ( kg/m**2 )
     'JZ ' : inertie de rotation autour de l'axe Z ( kg/m**2 )

   Elements joints unidimensionnels en 2D (JOI1)

    Les unites sont donnees a titre indicatif en systeme SI.

    Les noms des parametres dans un cas bidimensionnel correspondent
    aux 6 termes independants de la matrice de Hooke pour un materiau
    anisotrope :

    | EFFX |  | D11  sym.|  | EXX  |
    | EFFY | =  | D21 D22  |  x  | GXY  |
    | MOMZ |  | D31 D32 D33 |  | CXZ  |

    A ces parametres il faut ajouter (si necessaire) :

     'ALP1','ALP2','ALQ3' : coefficients de dilatation thermique secants
     'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
     'TALP' : temperature de reference du coefficient de dilatation
     'MASS ' : masse totale du bloc represente par l'element
        joint ( kg )
     'JZ ' : inertie de rotation autour de l'axe Z ( kg/m**2 )

PART{MECANIQUE ELASTIQUE UNIDIRECTIONNEL}
   | Noms des parametres pour un materiau ELASTIQUE UNIDIRECTIONNEL |

   'YOUN' : module d'Young
   'RHO ' : masse volumique
   'ALPH' : coefficient de dilatation thermique secant
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation

PART{MECANIQUE ELASTIQUE SECTION}
   | Noms des parametres pour un materiau ELASTIQUE SECTION  |

   'MODS' : modele decrivant la section (type MMODEL)
   'MATS' : proprietes materielles decrivant la section
        (type MCHAML), associees au modele ci-dessus
  ('MAHO') : matrice de hooke de la poutre equivalente
        (type LISTREEL)

CHAP{formulations LIQUIDE & LIQUIDE MECANIQUE}

PART{LIQUIDE}
   | Noms des parametres pour un LIQUIDE |

   'RHO ' : masse volumique
   'RORF' : masse volumique de reference
   'CSON' : celerite du son
   'CREF' : celerite de reference
   'LCAR' : longueur caracteristique
   'G ' : acceleration de la pesanteur

PART{HOMOGENEISE FLUIDE-STRUCTURE}
   | Noms des parametres pour un milieu homogeneise fluide-structure |

   'B11 ' : permeabilite acoustique selon l'axe X
   'B22 ' : permeabilite acoustique selon l'axe Y
   'B12 ' : permeabilite acoustique mixte
   'ROF ' : masse volumique du fluide
   'CSON' : celerite du son dans le fluide
   'YOUN' : rigidite des tubes
   'ROS ' : masse volumique des tubes
   'RORF' : masse volumique de reference du fluide
   'CREF' : celerite de reference dans le fluide
   'LCAR' : longueur caracteristique du domaine fluide
   'E111'  :  |
   'E112'  :  |
   'E121'  :  | coefficients cellulaires du deuxieme ordre
   'E122'  :  |
   'E221'  :  |
   'E222'  :  |

PART{RACCORD FLUIDE-TUYAU}
   | Noms des parametres pour un element de raccord fluide-tuyau |

   'RHO ' : masse volumique
   'RORF' : masse volumique de reference
   'LCAR' : longueur caracteristique

CHAP{Formulation THERMIQUE}
   | Noms des parametres en formulation THERMIQUE |

PART{THERMIQUE CONDUCTION}
   'RHO' : masse specifique
   'C' : chaleur specifique
   'TINI' : temperature initiale du milieu

   Elements Massifs
   'K' : conductivite isotrope

   Elements JOI1
   'KT' : conductivite integree equivalente

PART{THERMIQUE Changement de PHASE}
   'TPHA' : temperature de changement de phase
        (Elle est attendue constante par SOUS-ZONES)
   'QLAT' : chaleur latente par unite de masse

PART{THERMIQUE CONVECTION}
   'H' : coefficient d'echange

   Elements Massifs
   'TC' : temperature "exterieure" d'echange convectif

   Elements Coques
   'TCIN' : temperature "exterieure" d'echange convectif de la face inferieure
   'TCSU' : temperature "exterieure" d'echange convectif de la face superieure

PART{THERMIQUE RAYONNEMENT}
   'EMIS' : coefficient d'emissivite pour les massifs
   'EINF' : emissivite relative a la face inferieure (COQUES)
   'ESUP' : emissivite relative a la face superieure (COQUES)
   'E_IN' : emissivite de l'infini si besoin (1.D0 par defaut)
   'T_IN' : temperature "a l'infini" (milieu ambiant)
   'CABS' : coefficient d'absorbtion du milieu interne d'une cavite
   'TABS' : temperature de la cavite

        La designation des peaux des COQUES se fait par rapport a la
        normale exterieure de l'element : la peau superieure est
        placee dans le sens de la normale exterieure vis-a-vis du
        plan median. Dans le cas ou les elements ne sont pas orientes
        d'une facon coherente, il faut les reorienter en utilisant
        l'operateur ORIENT.

PART{THERMIQUE ADVECTION}
   'RHO' : masse specifique
   'C' : chaleur specifique
   'TINI' : temperature initiale du milieu
   'K' : conductivite isotrope

   Elements Massifs (repere global)
   'VITX' : Vitesse suivant X (1D)
   'VITX','VITY' : Vitesse suivant X,Y (2D)
   'VITX','VITY','VITZ' : Vitesse suivant X,Y,Z (3D)

   Elements TUYAU (repere local)
   'VITE' : vitesse de deplacement dans le tuyau

PART{THERMIQUE SOURCE}
   | Noms des parametres pour un materiau THERMIQUE SOURCE |

     'QVOL' : densite volumique de chaleur imposee.

    Remarque : le parametre QVOL peut etre un flottant ou un champ,
        champ par point (CHPOINT) ou par element (MCHAML).

   Dans le cas d'elements coques, on dispose des deux parametres
   supplementaires :

     'QINF' : densite volumique de chaleur imposee sur la face
        inferieure de l'element coque ;
     'QSUP' : densite volumique de chaleur imposee sur la face
        superieure de l'element coque.

    Remarque : voir ORIE pour la definition des faces inferieure
        et superieure des elements coques.

   | Noms des parametres pour un materiau THERMIQUE SOURCE GAUSSIENNE |

   Les modeles de source gaussienne disponibles sont :

   Modele THERMIQUE SOURCE GAUSSIENNE ISOTROPE :

     La distribution de chaleur est definie par l'equation suivante :

        Q(r) = Q0.EXP{-2.[(r/R0)^2]}

     r etant la distance a un point P0 origine, Q0 et R0 des parametres.

     Les parametres du modele sont :

     'QTOT' : objet FLOTTANT, quantite de chaleur imposee dans tout
        demi-espace passant par le centre de la Gaussienne.
        Si le centre de la Gaussienne est a la surface du milieu,
        QTOT est alors la quantite totale de chaleur fournie au milieu.
     'ORIG' : objet POINT, point P0 origine,
     'RGAU' : objet FLOTTANT, valeur du parametre R0.

     Remarque : Le parametre Q0 est egal a :

        - DIME 2 MODE PLAN : Q0 = 0.25/pi/R0/R0
        - DIME 2 MODE AXIS : Q0 = (pi**1.5)/(2**0.5)*R0*(XK1+XK2+XK3)
        avec :
        o XK1 = 0.25*R0*R0*exp(-2.*r(P0)*r(P0)/R0/R0)
        o XK2 = 0.5*R0*r(P0)*(pi/2)**0.5
        o XK3 = (pi**0.5)/(2**1.5)*R0*r(P0)*erf(r(P0)*(2**0.5)/R0)
        ou r(P0) est la 1ere coordonnee du point P0.
        - DIME 3 MODE TRID : Q0 = sqrt(2**5/pi**3)/R0/R0/R0*QTOT

   Modele THERMIQUE SOURCE GAUSSIENNE ISOTROPE_TRANSVERSE :

     La distribution de chaleur est definie par l'equation suivante :

        Q(r',z') = Q0.EXP{-2.[(r'/R0)^2 + (z'/Z0)^2]}

     avec :
        - r' : la distance a l'axe d'isotropie transverse, dont
        l'origine est definie par un point P0 et la direction
        d'isotropie transverse par un point P1,
        - z' : la coordonne sur l'axe d'isotropie transverse,
     et Q0, R0 et Z0 des parametres.

     Les parametres du modele sont :

     'QTOT' : objet FLOTTANT, quantite de chaleur imposee dans les
        demi-espaces definis par la direction d'anisotropie de
        la distribution Gaussienne et passant par son centre.
        Si le centre de la Gaussienne est a la surface du milieu
        et que sa direction d'anisotropie est orthogonale a cette
        surface, alors QTOT est la quantite totale de chaleur
        fournie au milieu.
     'ORIG' : objet POINT, point P0 origine,
     'RGAU' : objet FLOTTANT, valeur du parametre R0,
     'DIRE' : objet POINT, point P1 definissant l'axe d'isotropie
        transverse,
     'ZGAU' : objet FLOTTANT, valeur du parametre Z0.

     Remarque : Le parametre Q0 est egal a :

        - DIME 2 MODE PLAN : Q0 = 0.25/pi/R0/Z0
        - DIME 2 MODE AXIS : Q0 = (pi**1.5)/(2**0.5)*Z0*(XK1+XK2+XK3)
        avec :
        o XK1 = 0.25*R0*R0*exp(-2.*r(P0)*r(P0)/R0/R0)
        o XK2 = 0.5*R0*r(P0)*(pi/2)**0.5
        o XK3 = (pi**0.5)/(2**1.5)*R0*r(P0)*erf(r(P0)*(2**0.5)/R0)
        ou r(P0) est la 1ere coordonnee du point P0.
        - DIME 3 MODE TRID : Q0 = sqrt(2**5/pi**3)/R0/R0/Z0*QTOT

PART{THERMIQUE ORTHOTROPE}
   | Noms des parametres pour une formulation THERMIQUE ORTHOTROPE |

   Coques (COQ2, COQ3, COQ4, COQ6, COQ8)

     'K1','K2','K3' : conductivites thermiques
     'RHO' : masse volumique
     'C ' : chaleur massique
     'H ' : coefficient d'echange

   Massifs tridimensionnels

     'K1','K2','K3' : conductivites thermiques
     'RHO' : masse volumique
     'C ' : chaleur massique
     'H ' : coefficient d'echange

   Massifs bidimensionnels

        | bidimensionnel et  | serie de Fourier  |
        | axisymetrique  |  |
        | 'K1','K2'  | 'K1','K2','K3'  |
        | 'RHO','H','C'  | 'RHO','H','C'  |

PART{THERMIQUE ANISOTROPE}
   | Noms des parametres pour une formulation THERMIQUE ANISOTROPE |

   Massifs tridimensionnels

      'K11','K21','K22' : les termes independants de la matrice
      'K31','K32','K33' de conductivites anisotrope
      'RHO' : masse volumique
      'H' : coefficient d'echange
      'C' : chaleur massique

   Massifs bidimensionnels

        | bidimensionnel et  | serie de Fourier  |
        | axisymetrique  |  |
        |'K11','K21','K22'  | 'K11','K21','K22'  |
        |  | 'K33'  |
        | 'RHO','H','C'  | 'RHO','H','C'  |

   Remarque :

   Dans le cas des coques en thermique ainsi que des coques epaisses
   orthotropes en mecanique, il faut entrer les proprietes geometriques
   en meme temps que les proprietes materielles.

CHAP{Formulation CHANGEMENT_PHASE}
   | Noms des parametres en formulation CHANGEMENT_PHASE |
PART{CHANGEMENT_PHASE PARFAIT}
   'PRIM' : Valeur de l'inconnue ou du chargement a laquelle le
        changement de phase a lieu.
   'DUAL' : Quantite latente par unite de volume.

PART{CHANGEMENT_PHASE SOLUBILITE}
   'SOLU' : Valeur limite maximale de la solubilite de la
        premiere inconnue primale.

CHAP{Formulation METALLURGIE}
   | Noms des parametres en formulation METALLURGIE |
   Les caracteristiques des transformations de phase metallurgiques
   different selon que la transformation soit de type KOISTINEN-MARBURGER
   ou LEBLOND-DEVAUX. Elles sont indexees par le numero "i" de la reaction.
   1- Type KOISTINEN-MARBURGER : 'KMi' (constant dans leur theorie)
        'MSi' (constant dans leur theorie)
   2- Type LEBLOND-DEVAUX : 'PEQi'
        'TAUi'
        'Fi '
      exemples : metallurgie_07.dgibi --> metallurgie_14.dgibi

CHAP{Formulation DARCY}
PART{DARCY ISOTROPE}
   | Noms des parametres en formulation DARCY |

   'K' : permeabilite isotrope

PART{DARCY ORTHOTROPE}
   | Noms des parametres pour une formulation DARCY ORTHOTROPE |

   Hybrides tridimensionnels

     'K1','K2','K3' : permeabilites hydrauliques

   Hybrides bidimensionnels

     'K1','K2' : permeabilites hydrauliques

PART{DARCY ANISOTROPE}
   | Noms des parametres pour une formulation DARCY ANISOTROPE |

   Hybrides tridimensionnels

      'K11','K21','K22' : les termes independants de la matrice
      'K31','K32','K33' de permeabilites anisotropes

   Hybrides bidimensionnels

      'K11','K21','K22' : les termes independants de la matrice
        de permeabilites anisotropes

CHAP{CONTACT}

PART{COULOMB}
   Modele de frottement de COULOMB :

   'MU' : coefficient de frottement (egal a tgPHI)
   'JEU' : Distance minimale a respecter entre les objets en
        contact (type MCHAML, sur le MAILLAGE de contact
        issu d'IMPO)
   ('COHE'): coefficient de cohesion
   ('ADHE'): coefficient d'adherence

PART{FROCABLE}
   Modele de frottement des cables 'FROCABLE' :

   'FF' : voir code BPEL99
   'PHIF' : voir code BPEL99

CHAP{CONTRAINTE}

PART{ROTATION}
   Modele de contrainte de ROTATION:

   'ANGL' : angle de la rotation imposee

PART{DEPLACEMENT}
   Modele de contrainte de DEPLACEMENT:

   'AMPL' : amplification du deplacement impose

CHAP{POREUX}

PART{POREUX ELASTIQUE ISOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ISOTROPE |

   'YOUN' : module d'Young
   'NU ' : coefficient de poisson
   'RHO ' : masse volumique
   'ALPH' : coefficient de dilatation thermique secant
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'MOB ' : module de Biot
   'COB ' : coefficient de Biot
   'PERM' : permeabilite intrinseque
   'VISC' : viscosite dynamique du fluide
   'ALPM' : coefficient de couplage pression - temperature

      Cas des joints poreux

   'KS ' : raideur de cisaillement
   'KN ' : raideur normale
   'COB ' : coefficient de Biot
   'MOB ' : module de Biot
   'PERT' : permeabilite intrinseque tangentielle
   'PERH' : permeabilite intrinseque normale de la face en haut
   'PERB' : permeabilite intrinseque normale de la face en bas
   'VISC' : viscosite dynamique du fluide

PART{POREUX ELASTIQUE ORTHOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ORTHOTROPE |

   Massifs tridimensionnels

    'YG1 ', 'YG2 ', 'YG3 ' : modules d'Young
    'NU12', 'NU23', 'NU13' : coefficients de Poisson
    'G12 ', 'G23 ', 'G13 ' : modules de cisaillement
    'ALP1', 'ALP2','ALP3' : coefficients de dilatation thermique secants
    'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
    'TALP' : temperature de reference du coefficient de dilatation
    'RHO ' : masse volumique
    'COB1', 'COB2', 'COB3' : coefficients de Biot
    'MOB ' : module de Biot
    'PER1', 'PER2', 'PER3' : permeabilites intrinseques
    'VISC' : viscosite dynamique du fluide
    'ALPM' : coefficient de couplage pression -
        temperature

   Massifs bidimensionnels

    Les noms de parametres pour les differents cas bidimensionnels sont
    resumes dans le tableau suivant :

   | contrainte plane  | deformation plane  | serie de Fourier  |
   |  | axisymetrique  |  |
   |--------------------|--------------------|----------------------|
   |'YG1', 'YG2','YG3'  |'YG1', 'YG2', 'YG3' | 'YG1', 'YG2', 'YG3'  |
   |'NU12','NU23','NU13'|'NU12','NU23','NU13'| 'NU12','NU23','NU13' |
   |'G12 '  |'G12 '  | 'G12 ','G23 ','G13 ' |
   |'ALP1','ALP2'  |'ALP1','ALP2','ALP3'| 'ALP1','ALP2','ALP3' |
   |'TREF','TALP'  |'TREF','TALP'  | 'TREF','TALP'  |
   |'RHO'  |'RHO '  | 'RHO'  |
   |'COB1','COB2','COB3'|'COB1','COB2','COB3'| 'COB1','COB2','COB3' |
   |'MOB '  |'MOB '  | 'MOB '  |
   |'PER1','PER2'  |'PER1','PER2'  | 'PER1','PER2','PER3' |
   |'VISC'  |'VISC'  | 'VISC'  |
   |'ALPM'  |'ALPM'  | 'ALPM'  |

PART{POREUX ELASTIQUE ANISOTROPE}
   | Noms des parametres pour un materiau ELASTIQUE ANISOTROPE |

   Massifs tridimensionnels

    Les noms des parametres dans un cas tridimensionnel correspondent
    aux 21 termes independants de la matrice de Hooke pour un materiau
    anisotrope et aux 6 termes independants de la matrice de Biot :

    | sig1 |  |D11  sym.  |  | eps1  |  |COB1 |
    | sig2 |  |D21 D22  |  | eps2  |  |COB2 |
    | sig3 | =  |D31 D32 D33  |  x  | eps3  |  - |COB3 | x p
    | tau12|  |D41 D42 D43 D44  |  | gama12|  |CO12 |
    | tau13|  |D51 D52 D53 D54 D55  |  | gama13|  |CO13 |
    | tau23|  |D61 D62 D63 D64 D65 D66 |  | gama23|  |CO23 |

    et au module de Biot : 'MOB '

    A ces parametres il faut ajouter (si necessaire) :

     'ALP1','ALP2','ALP3' : coefficients de dilatation thermique secants
     'AL12','AL23','AL13'
     'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
     'TALP' : temperature de reference du coefficient de dilatation
     'RHO' : masse volumique
     'PER1','PER2','PER3'  | : matrice de permeabilites intrinseques
     'PE12','PE13','PE23'  |
     'VISC' : viscosite du fluide
     'ALPM' : coefficient de couplage pression -
        temperature

   Massifs bidimensionnels

    Les noms des parametres pour les differents cas bidimensionnels
    sont resumes dans le tableau suivant :

   |  contrainte plane  | deformation plane  | serie de Fourier  |
   |  | axisymetrique  |  |
   |'D11','D21','D22'  |'D11','D21','D22'  | 'D11','D21','D22'  |
   |'D31','D32','D33'  |'D31','D32','D33'  | 'D31','D32','D33'  |
   |'D41','D42','D43'  |'D41','D42','D43'  | 'D41','D42','D43'  |
   |'D44'  |'D44'  | 'D44','D55','D65'  |
   |  |  | 'D66'  |
   |'ALP1','ALP2'  |'ALP1','ALP2','ALP3'| 'ALP1','ALP2','ALP3' |
   |'AL12'  |'AL12'  | 'AL12'  |
   |'TREF','TALP'  |'TREF','TALP'  | 'TREF','TALP'  |
   |'RHO '  |'RHO '  | 'RHO '  |
   |'COB1','COB2','COB3'|'COB1','COB2','COB3'| 'COB1','COB2','COB3' |
   |'CO12','MOB '  |'CO12','MOB '  | 'CO12','MOB '  |
   |'PER1','PER2','PE12'|'PER1','PER2','PE12'| 'PER1','PER2','PER3' |
   |'VISC'  |'VISC'  | 'PE12','VISC'  |
   |'ALPM'  |'ALPM'  | 'ALPM'  |

PART{POREUX ELASTIQUE UNIDIRECTIONNEL}
   | Noms des parametres pour un materiau ELASTIQUE UNIDIRECTIONNEL |

   'YOUN' : module d'Young
   'RHO ' : masse volumique
   'ALPH' : coefficient de dilatation thermique secant
   'TREF' : temperature de reference de la structure
        (aucune deformation d'origine thermique)
   'TALP' : temperature de reference du coefficient de dilatation
   'MOB ' : module de Biot
   'COB ' : coefficient de Biot
   'PERM' : permeabilite intrinseque
   'VISC' : viscosite dynamique du fluide
   'ALPM' : coefficient de couplage pression - temperature

CHAP{MAGNETODYNAMIQUE}

PART{CORFOU}
   Coques (modelisation CORFOU)

   'ETA' : resistivite (en ohm.m)
   'PERM' : permeabilite relative
        mu = mur.mu0 avec mu0 = 4.pi.e-7 henry/m

PART{MAGNETODYNAMIQUE ORTHOTROPE}
   Coques (modelisation CORFOU)

   'ETA1' : resistivite suivant la premiere direction d'orthotropie
        (en ohm.m)
   'ETA2' : resistivite suivant la deuxieme direction d'orthotropie
        (en ohm.m)
   'PERM' : permeabilite relative
        mu = mur.mu0 avec mu0 = 4.pi.e-7 henry/m

CHAP{MELANGE}

PART{Modele CEREM}
   Modele CEREM (transition de phase du 16MND5)

    'AC1' : temperature debut transition
    'AR1' : temperature fin transition
    'MS0' : temperature transition martensitique initiale
    'BETA':
    'AC' :
    'AA' :
    'ZS' :
    'TPLM':
    'CARB':
    'ACAR': temperature transition au refroidissement
    'DG0' : taille de grain
    'AGRA':
    'TIHT': temperature debut refroidissement
    'TFHT': temperature fin refroidissement
    'DTHT': decrement de temperature
    'NHTR': donnees des proportions de phases finales pour
        differents trajets de refroidissement (objet NUAGE)
    'NLEB': donnees modele de Leblond au chauffage (objet NUAGE)
    'ZA' : proportion d'austenite
    'ZF' : proportion de ferrite
    'ZB' : proportion de bainite
    'ZM' : proportion de martensite
    'MS' ; temperature de transition martensitique

PART{Modele PARALLELE}
   Modele PARALLELE (combinaison lineaire)

   Les coefficients de phases sont les 4 premieres lettres des noms
   de phases participant au modele.

PART{Modele ZTMAX}
   Modele ZTMAX (transition entre 2 phases)

   'PHA1', 'PHA2' : proportions phase1 / phase 2
   'VIPH' : valeur maxi de la variable
   'VDEH' : valeur mini de la variable
   'AC1', 'AC2': debut et fin de transition 1->2 quand la variable croit
   'AC3', 'AC4': debut et fin de transition 2->1 quand la variable
        decroa®t
   'VPAR' : nom de la variable parametre (par defaut 'T')

CHAP{FISSURE}

     Notations : f : coefficient de frottement
        e : ouverture en entree de fissure
        RE : nombre de Reynolds
        REC : nombre de Reynolds critique

PART{loi POISEU_BLASIUS}
   | Parametres pour la loi de frottement POISEU_BLASIUS |
     C'est la loi par defaut pour la formulation FISSURE.
     En regime laminaire : f=96/RE
     En regime turbulent lisse : f=0.316*RE^(-0.25) (Blasius)
     Le nombre de Reynolds critique REC vaut 2042 (intersection entre
     ces 2 fonctions)

     'RUGO': rugosite (m)
        RUGO/2e doit etre inferieur a 1e-4

PART{loi POISEU_COLEBROOK}
   | Parametres pour la loi de frottement POISEU_COLEBROOK |
     f = max(96/RE;Colebrook)
     Formule implicite de Colebrook :
     1/sqrt(f) = -2 log(RUGO/2e/3.7+2.51/RE/sqrt(f)) (log base 10)
     Le nombre de Reynolds critique varie avec la rugosite

     'RUGO': rugosite (m)
        RUGO/2e doit etre superieur ou egal a 1e-4

PART{loi FROTTEMENT1}
   | Parametres pour la loi de frottement FROTTEMENT1  |
     En regime laminaire : f=k/RE
     En regime turbulent : f=(a+bRE^c)^d

     'REC': nombre de Reynolds critique donne par l utilisateur
     'FK': k
     'FA': a
     'FB': b
     'FC': c
     'FD': d

PART{loi FROTTEMENT2}
   | Parametres pour la loi de frottement FROTTEMENT2  |
     En regime laminaire : f=k/RE
     En regime turbulent : f=a(b+clogRE)^d

     'REC': nombre de Reynolds critique donne par l utilisateur
     'FK': k
     'FA': a
     'FB': b
     'FC': c
     'FD': d

PART{loi FROTTEMENT3}
   | Parametres pour la loi de frottement FROTTEMENT3  |
     FROT3 : k*Colebrook sur toute la gamme de Reynolds

     'RUGO': rugosite (m)
        RUGO/2e doit etre superieur ou egal a 1e-4
     'FK': k

PART{loi FROTTEMENT4}
   | Parametres pour la loi de frottement FROTTEMENT4  |
     FROT4 : k*(max(96/RE;Colebrook))

     'RUGO': rugosite (m)
        RUGO/2e doit etre superieur ou egal a 1e-4
     'FK': k

CHAP{LIAISON}

   Voir egalement notice DYNE
   'SORT' : composante optionnelle (type TABLE)
     la table est indicee par l'objet (type MMODEL) de liaison

PART{loi POINT_PLAN FLUIDE}
   | Parametres pour la loi POINT_PLAN FLUIDE  |
   'NORM' : 'NORMALE' (type POINT)
   'INER' : 'COEFFICIENT_INERTIE'
   'CONV' : 'COEFFICIENT_CONVECTION'
   'VISC' : 'COEFFICIENT_VISCOSITE'
   'PELO' : 'COEFFICIENT_P_D_C_ELOIGNEMENT'
   'FRAP' : 'COEFFICIENT_P_D_C_RAPPROCHEMENT'
   'JFLU' : 'JEU_FLUIDE'

PART{loi POINT_PLAN FROTTEMENT}
   | Parametres pour la loi POINT_PLAN FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'JEU' :
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)

PART{loi POINT_PLAN}
   | Parametres pour la loi POINT_PLAN  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'JEU' :

    composantes optionnelles
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)
   'PERM' : 'LIAISON_PERMANENTE' (type ENTIER 0 ou 1)
   'SPLA' : 'SEUIL_PLASTIQUE'
   'AMOR' : 'AMORTISSEMENT'

PART{loi POINT_POINT FROTTEMENT}
   | Parametres pour la loi POINT_POINT FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'JEU' :
   'POIB' : 'POINT_B'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)
   'MODE' :

PART{loi POINT_POINT DEPLACEMENT_PLASTIQUE}
   | Pour la loi POINT_POINT DEPLACEMENT_PLASTIQUE  |
   'NORM' : 'NORMALE' (type POINT)
   'ECRO' : 'ECROUISSAGE'
   'JEU' :
   'POIB' : 'POINT_B'
   'PERM' : 'LIAISON_PERMANENTE' (type ENTIER 0 ou 1)
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'

PART{loi POINT_POINT ROTATION_PLASTIQUE}
   | Pour la loi  POINT_POINT ROTATION_PLASTIQUE  |
   'NORM' : 'NORMALE' (type POINT)
   'ECRO' : 'ECROUISSAGE'
   'JEU' :
   'POIB' : 'POINT_B'
   'PERM' : 'LIAISON_PERMANENTE' (type ENTIER 0 ou 1)
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'ELAS' : (type ENTIER 0 ou 1)

PART{loi POINT_POINT}
   | Parametres pour la loi  POINT_POINT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'JEU' :
   'POIB' : 'POINT_B'
   'PERM' : 'LIAISON_PERMANENTE' (type ENTIER 0 ou 1)

   composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'LOIC' : 'LOI_DE_COMPORTEMENT' (type EVOLUTION)

PART{loi POINT_CERCLE MOBILE}
   | Parametres pour la loi POINT_CERCLE MOBILE  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'PCER' : 'CERCLE'
   'RAYO' : 'RAYON'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composantes optionnelles
   'CINT' : 'CONTACT_INTERIEUR'
   'AMOR' : 'AMORTISSEMENT'

PART{loi POINT_CERCLE FROTTEMENT}
   | Parametres pour la loi POINT_CERCLE FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'EXCE' : 'EXCENTRATION'
   'RAYO' : 'RAYON'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composantes optionnelles
   'CINT' : 'CONTACT_INTERIEUR'
   'AMOR' : 'AMORTISSEMENT'

PART{loi POINT_CERCLE}
   | Parametres pour la loi POINT_CERCLE  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'EXCE' : 'EXCENTRATION'
   'RAYO' : 'RAYON'

    composante optionnelle
   'AMOR' : 'AMORTISSEMENT'

PART{loi CERCLE_PLAN FROTTEMENT}
   | Parametres pour la loi CERCLE_PLAN FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'JEU' :
   'RAYS' : 'RAYON_SUPPORT'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composante optionnelle
   'AMOR' : 'AMORTISSEMENT'

PART{loi CERCLE_CERCLE FROTTEMENT}
   | Parametres pour la loi CERCLE_CERCLE FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'EXCE' : 'EXCENTRATION'
   'RAYS' : 'RAYON_SUPPORT'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'
   'RAYB' : 'RAYON_BUTEE'

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'CINT' : 'CONTACT_INTERIEUR'

PART{loi PROFIL_PROFIL INTERNE/EXTERNE}
   | Parametres pour les lois PROFIL_PROFIL INTERNE  |
   |  PROFIL_PROFIL EXTERNE  |
   'NORM' : 'NORMALE' (type POINT)
   'RAID' : 'RAIDEUR'
   'PFIX' : 'PROFIL_FIXE' (type MAILLAGE)
   'PMOB' : 'PROFIL_MOBILE' (type MAILLAGE)
   'ERAI' : 'EXPOSANT_RAIDEUR'

PART{loi LIGNE_LIGNE FROTTEMENT}
   | Parametres pour la loi LIGNE_LIGNE FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'LIMA' : 'LIGNE_MAITRE' (type MAILLAGE)
   'LIES' : 'LIGNE_ESCLAVE' (type MAILLAGE)
   'RAID' : 'RAIDEURS'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'
   'JEU' :

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'RECH' : 'RECHERCHE' (type ENTIER 0 : local, 1 global)
   'SYME' : 'SYMETRIE' (type ENTIER 0 ou 1)

PART{loi LIGNE_CERCLE FROTTEMENT}
   | Parametres pour la loi LIGNE_CERCLE FROTTEMENT  |
   'NORM' : 'NORMALE' (type POINT)
   'LIMA' : 'LIGNE_MAITRE' (type MAILLAGE)
   'LIES' : 'LIGNE_ESCLAVE' (type MAILLAGE)
   'RAID' : 'RAIDEURS'
   'GLIS' : 'COEFFICIENT_GLISSEMENT'
   'ADHE' : 'COEFFICIENT_ADHERENCE'
   'RTAN' : 'RAIDEUR_TANGENTIELLE'
   'ATAN' : 'AMORTISSEMENT_TANGENTIEL'

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'
   'RECH' : 'RECHERCHE' (type ENTIER 0 : local, 1 global)
   'RAYO' : 'RAYON'
   'ACTN' : 'ACTNOR' (type ENTIER 0 ou 1)
   'INVE' : 'INVERSION' (type ENTIER 0 ou 1)

PART{loi PALIER_FLUIDE RHODE_LI}
   | Parametres pour la loi PALIER_FLUIDE RHODE_LI  |
   'LONG' : 'LONGUEUR_PALIER'
   'RAYO' : 'RAYON_ARBRE'
   'VISC' : 'VISCOSITE_FLUIDE'
   'RHOF' : 'RHO_FLUIDE'
   'PADM' : 'PRESSION_ADMISSION'
   'VROT' : 'VITESSE_ARBRE'
   'EPSI' : 'CRITERE_ARRET'
   'PHII' :
   'AFFI' :
   'TLOB' : 'GEOMETRIE_PALIER'

    composantes optionnelles
   'AMOR' : 'AMORTISSEMENT'

PART{loi COUPLAGE DEPLACEMENT}
   | Parametres pour la loi COUPLAGE DEPLACEMENT  |
   'ORIG' : 'ORIGINE'
   'COEF : 'COEFFICIENT'

PART{loi COUPLAGE VITESSE}
   | Parametres pour la loi COUPLAGE VITESSE  |
   'ORIG' : 'ORIGINE'
   'COEF : 'COEFFICIENT'

PART{loi POLYNOMIALE}
   | Parametres pour la loi POLYNOMIALE  |
   'COEF' : 'COEFFICIENT'
   'PCO1' ... 'PCO9' : points origines (maximum 9)
   'TCO1' ... 'TCO9' : tables contributions (maximum 9)

PART{loi NEWMARK MODAL}
        Loi non compatible avec DYNE
   | Parametres pour la loi NEWMARK MODAL  |
   'JEU' :
   'EXCE' : soit u le deplacement normal,
        si jeu < 0 u - exce > jeu
        si jeu > 0 u - exce < jeu
   'FROT' : coefficient de frottement
   'MOFR' : modele (type MMODEL) sur lequel s'applique le frottement

CHAP{DIFFUSION}

PART{loi de FICK}
   | Parametres pour la loi FICK  |
   'KD' : coefficient de diffusion
   'CDIF' : terme capacitif, analogue a (rho*Cp) en THERMIQUE

PART{DIFFUSION ORTHOTROPE}
   | Noms des parametres pour une formulation DIFFUSION ORTHOTROPE |

   Massifs tridimensionnels

     'KD1','KD2','KD3' : diffusivites
     'CDIF' : terme capacitif,
        analogue a (rho*Cp) en THERMIQUE

   Massifs bidimensionnels

    Les noms des parametres pour les differents cas bidimensionnels
    sont resumes dans le tableau suivant :

        | bidimensionnel et  | serie de Fourier  |
        | axisymetrique  |  |
        | 'KD1','KD2'  | 'KD1','KD2','KD3'  |
        | 'CDIF'  | 'CDIF'  |

PART{DIFFUSION ANISOTROPE}
   | Noms des parametres pour une formulation DIFFUSION ANISOTROPE |

   Massifs tridimensionnels

      'KD11','KD21','KD22' : les termes independants de la matrice
      'KD31','KD32','KD33' : de diffusivite anisotrope
      'CDIF' : terme capacitif,
        analogue a (rho*Cp) en THERMIQUE

   Massifs bidimensionnels

     Les noms des parametres pour les differents cas bidimensionnels
     sont resumes dans le tableau suivant :

        | bidimensionnel et  | serie de Fourier |
        | axisymetrique  |  |
        | 'KD11','KD21','DK22' | 'KD11','KD21',  |
        |  | 'KD22','KD33'  |
        | 'CDIF'  | 'CDIF'  |

CHAP{Definition des reperes d'orthotropie et unidirectionnels}

        | 'DIRECTION' P1 (P2) | | ('PARALLELE')  |
   MAT1 = MATE MODL1 |  | | 'PERPENDICULAIRE'  | ...
        |  'RADIAL' P1  (P2) | | 'INCLINE' FLOT1 (P3) |

        ... NOMCi VALi ... ;

    Les proprietes d'orthotropie et d'anisotropie sont donnees dans
    des reperes qui dependent des elements coques ou massifs et qui
    sont definis comme suit :

PART{Reperes d'orthotropie pour elements coques}
        | Reperes d'orthotropie pour elements coques |

    Les reperes d'orthotropie sont definis par la donnee de la premiere
    direction d'orthotropie. On commence par definir un premier vecteur
    VEC1 par :

    'DIRECTION' : on projette la direction P1 (type POINT) sur le plan
        tangent a la coque, ce qui donne un vecteur VEC1.

    'RADIAL' : equivaut a "DIRECTION (PT - P1)", PT etant un point
        courant de la coque (direction variable en fonction
        du point de l'element).

    puis on specifie la premiere direction d'orthotropie par :

    'PARALLELE' : VEC1 est alors la premiere direction
        d'orthotropie

    'PERPENDICULAIRE': La premiere direction d'orthotropie est alors
        perpendiculaire a VEC1

    'INCLINE' : La premiere direction d'orthotropie fait un
        angle +/-FLOT1 (type FLOTTANT) avec la direction
        VEC. P3 (type POINT) donne la direction de la
        normale exterieure a la coque et donc le signe de
        l'angle. Si ce vecteur n'est pas fourni,
        l'orientation est celle de la normale a la coque.

    Par exemple, dans le cas d'une coque cylindrique modelisee en 3D ou
    en 2D Fourier, on ecrira 'DIRECTION' P1, P1 etant dirige selon l'axe
    du cylindre, puis 'PARALLELE' si la premiere direction d'orthotropie
    est selon l'axe, 'PERPENDICULAIRE' si elle est perpendiculaire a l'axe,
    ou 'INCLINE' FLOT1 si elle est en helice le long du cylindre.

   Remarque 1 :
   La direction P2 n'est pas utilisee dans le cas des elements coques.
   La 3eme direction est toujours perpendiculaire a la surface de la
   coque.

   Remarque 2 :
   Pour les elements joints 3D elastiques orthotropes, les reperes
   d'orthotropie sont identiques a ceux des elements coques. Seule
   l'option 'RADIAL' est interdite.

   Remarque 3 :
   L'option 'RADIAL' est interdite pour les coques minces 2D.

PART{Reperes d'orthotropie pour elements massifs}
        | Reperes d'anisotropie pour elements massifs |

    On construit d'abord un triedre a partir des deux vecteurs VEC1 et
    VEC2 fournis par l'utilisateur. Le premier axe correspond a VEC1.
    Le troisieme axe est perpendiculaire aux vecteurs VEC1 et VEC2.
    Le deuxieme axe complete le triedre. Les vecteurs VEC1 et VEC2 sont
    donnes par :

    'DIRECTION' : la direction P1 (type point) correspond a VEC1 et
        la direction P2 (type point) correspond a VEC2 .

    'RADIAL' : en dimension 2, VEC1 joint le point courant a P1;
        en dimension 3, VEC1 est selon l'axe P1 P2 et VEC2
        est selon la perpendiculaire a VEC1 menee depuis
        le point courant.

    Le repere d'anisotropie correspond au triedre defini ci-dessus
    eventuellement tourne autour de l'axe 3 :

    'PARALLELE' : VEC1 est alors la premiere direction
        d'orthotropie (aucune rotation autour de l'axe 3)

    'PERPENDICULAIRE': La premiere direction d'orthotropie est alors
        perpendiculaire a VEC1 (rotation de +90 autour
        de l'axe 3)

    'INCLINE' : La premiere direction d'orthotropie fait un
        angle FLOT1 (type FLOTTANT) avec la direction
        VEC1 (rotation d'un angle quelconque autour
        de l'axe 3)

    Remarque 1 :
    Dans un cas bidimensionnel, la definition d'un seul vecteur (VEC1)
    est suffisante. Le deuxieme axe correspond a un vecteur qui fait
    un angle de + 90 avec le vecteur VEC1 dans le plan.
    Le troisieme vecteur est donc toujours hors-plan sauf dans le cas
    ci-dessous.
    En 2D Fourier, pour les modeles MECANIQUE ORTHOTROPE, il est
    possible d'incliner le repere d'orthotropie avec l'option INCLINE
    suivie de 2 reels FLOT1 et FLOT2. FLOT1 est l'angle de rotation de
    VEC1 autour du vecteur hors-plan (axe 3) et FLOT2 est l'angle de
    rotation des vecteurs 2 et 3 autour du 1er vecteur.

    Remarque 2 :
    La direction P3 n'est pas utilisee dans le cas des elements massifs.

PART{Direction des materiaux unidirectionnels}
        | Direction des materiaux unidirectionnels  |

    La syntaxe ci-dessus pour les reperes d'orthotropie (ou
    d'anisotropie )dans les cas des elements coques et massifs,
    s'applique egalement aux materiaux unidirectionnels. Dans ce
    cas le premier axe d'orthotropie correspond a la direction des
    materiaux unidirectionnels.

PART{DIFFUSION ADVECTION}
   | Parametres supplementaires en cas d'ADVECTION  |
   Obligatoires
     Elements Massifs (repere global)
     'VITX' : Vitesse suivant X (1D)
     'VITX','VITY' : Vitesse suivant X, Y (2D)
     'VITR','VITZ' : Vitesse suivant R, Z (2D AXI)
     'VITX','VITY','VITZ' : Vitesse suivant X, Y, Z (3D)
        (2D PLAN DPGE)

     'DX' : Vitesse suivant X (1D)
     'DX','DY' : Vitesse suivant X, Y (2D)
     'DX','DY','DZ' : Vitesse suivant X, Y, Z (3D)
        (2D PLAN DPGE)
     Elements TUYAU (repere local)
     'VITE' : Vitesse axiale

   Optionnels : Stabilisation de l'ADVECTION par la
   ---------- methode SUPG (Streamline Upwind Petrov Galerkin)
     Elements Massifs (repere global)
     'DX' : Taille de maille suivant X (1D)
     'DX','DY' : Taille de maille suivant X, Y (2D)
     'DR','DZ' : Taille de maille suivant R, Z (2D AXI)
     'DX','DY','DZ' : Taille de maille suivant X, Y, Z (3D)
        (2D PLAN DPGE)
     Elements TUYAU (repere local)
     'DL' : Taille de maille dans la direction axiale

CHAP{PROPRIETES GEOMETRIQUES}

PART{Elements Massifs}
  | Noms des caracteristiques pour les elements massifs |

   ('DIM3') : epaisseur dans le cas des contraintes planes

PART{Elements COQ2, COQ3, COQ4, DKT, DST}
  | Noms des caracteristiques pour les elements COQ2, COQ3, COQ4, DKT,
  |  DST

   'EPAI' : epaisseur de la coque
   ('ALFA') : coefficient utilise dans le critere de plasticite
        (par defaut 2/3)
   ('EXCE') : excentrement du plan moyen de la coque par rapport au
        plan de reference, compte positif dans le sens de la
        normale (non disponible pour COQ3)
   ('DIM3') : epaisseur dans l'autre direction (cas des COQ2 en
        contraintes planes)

PART{Elements COQ6, COQ8}
   | Noms des caracteristiques pour les elements COQ6, COQ8 |

   'EPAI' : epaisseur de la coque
   ('EXCE') : excentrement par rapport au plan moyen, compte positif
        dans le sens de la normale

PART{Elements ROT3}
   | Noms des caracteristiques pour les elements ROT3 |

   'EPAI' : epaisseur de la coque (avec 'MATE')

PART{Elements POJS, TRIS, QUAS}
   | Noms des caracteristiques pour un element POJS, TRIS, QUAS |

   La section est decrite dans le plan xOy. L'axe Ox du repere de
   description de la section est l'axe local Oy de l'element TIMO.

   'SECT' : aire de la section droite (seulement pour les elements POJS)

   'ALPY' : facteur de gauchissement dans la direction locale Oy
        coefficient qui multiplie la contrainte de cisaillement
        sxy (Ox et Oy sont des axes locaux de l'element TIMO).

   'ALPZ' : facteur de gauchissement dans la direction locale Oz
        coefficient qui multiplie la contrainte de cisaillement
        sxz (Ox et Oz sont des axes locaux de l'element TIMO).

   Ces coefficients dans le cas d'une section homogene peuvent etre
   definis d'apres la theorie de Timoshenko.

PART{Elements JOINT generalise}
   | Noms des caracteristiques pour les elements de joint generalise |

   ('EPAI') : epaisseur du joint

PART{Elements BARRE}
   | Noms des caracteristiques pour un element BARRE |

   'SECT' : section droite

PART{Elements CERCE}
   | Noms des caracteristiques pour un element CERCE |

   'SECT' : section droite

PART{Elements POUTRE, TIMO}
   | Noms des caracteristiques pour un element POUTRE, TIMO |

    Les caracteristiques de la poutre sont definies dans le repere local
    de l'element (Ox axe de la poutre oriente du premier point vers
    le second, Oy defini si necessaire par l'utilisateur, Oz completant
    le repere).Il faut que les axes Oy Oz soient des axes pricipaux de
    la section car on ne definit pas les moments d'inertie croisees
    (sauf poul l'element TIMO avec un modele SECTION).

    'SECT' : section droite
    'INRY' : moment d'inertie par rapport a l'axe local Oy
        (3D seulement)
    'INRZ' : moment d'inertie par rapport a l'axe local Oz
    'TORS' : moment d'inertie de torsion (3D seulement)
    ('SECY') : section reduite a l'effort tranchant selon l'axe local
    ('SECZ') : section reduite a l'effort tranchant selon l'axe local
        (3D seulement)
    ('VECT') : mot-cle permettant de definir l'axe local Oy. Il doit
        etre suivi par un vecteur appartenant au plan xOy
        (objet de type POINT) (TRID seulement).
    DX, DY, DZ : distances permettant de calculer des contraintes a
        partir des moments (cf VMIS) :
    ('DX  ') | : distance associee a la torsion (TORS)
    ('DY  ') | : distance a la fibre neutre suivant l'axe Oy
    ('DZ  ') | : distance a la fibre neutre suivant l'axe Oz

    Par defaut, les sections SECY et SECZ sont prises egales a SECT pour
    l'element TIMO et pour les elements POUTRE on neglige l'energie
    de deformation de cisaillement (cela revient a imposer des valeurs
    infinies pour les sections reduites)

PART{Elements TUYAU}
   | Noms des caracteristiques pour un element TUYAU |

    Cet element sert a representer des portions de tuyau droit ou de
    coude, la differenciation se faisant par le rayon de courbure.
    Les caracteristiques du tuyau sont definies dans le repere local de
    l'element, de la Meme facon que pour l'element POUTRE.

   'EPAI' : epaisseur
   'RAYO' : rayon exterieur du tuyau
   ('RACO') : rayon de courbure s'il s'agit d'un coude
   ('VECT') : mot-cle permettant de definir l'axe local Oy. Il doit
        etre suivi par un POINT representant un vecteur de xOy.
        Cette donnee est imperative s'il s'agit d'un coude.

        Attention : pour les coudes, le vecteur local Oz, deduit
        de Ox et Oy, est situe dans le plan du coude et oriente
        par convention vers l'extrados du coude.
   ('PRES') : pression interne
   ('CFFX') : facteur multiplicatif permettant de calculer la
        contrainte de membrane a partir de l'effort EFFX, pour
        le critere de plasticite (1. par defaut), (cf VMIS).
   ('CFMX') : facteur multiplicatif permettant de calculer la
        contrainte de torsion a partir du moment MOMX, pour
        le critere de plasticite (3.**0.5 par defaut), (cf VMIS).
   ('CFMY') : facteur multiplicatif permettant de calculer la
        contrainte de flexion a partir du moment MOMY, pour
        le critere de plasticite ((pi/4)*gamma par defaut),
        (cf VMIS).
   ('CFMZ') : facteur multiplicatif permettant de calculer la
        contrainte de flexion a partir du moment MOMZ, pour
        le critere de plasticite ((pi/4)*gamma par defaut),
        (cf VMIS).
   ('CFPR') : facteur multiplicatif permettant de calculer la
        contrainte circonferentielle due a la pression. Facteur
        non utilise pour le critere de plasticite mais
        seulement dans le calcul de la contrainte equivalente
        (0. par defaut), (cf VMIS).

        Remarque : pour CFMY et CFMZ, gamma est egal a 1. pour
        les parties droites et a maxi ( 1., (8/9)/lambda**2/3 )
        pour les coudes, avec lambda = epai*raco/rmoy**2 oa¹
        rmoy est le rayon moyen du tuyau.

PART{Elements LINESPRING}
   | Noms des caracteristiques pour un element LINESPRING |

   'EPAI' : epaisseur de la coque
   'FISS' : profondeur de l'entaille
   'VX  ' |
   'VY  ' |  : composantes du vecteur normal au plan de la coque (son
   'VZ  ' |  sens indique le cote de la coque oÂº s'ouvre l'entaille)

    Remarque :

    Il ne doit pas y avoir d'angle inferieur a 175 degres ou superieur
    a 185 degres entre les elements dans leur plan (defini a l'aide
    du vecteur normal).

PART{Elements TUYAU FISSURE}
   | Noms des caracteristiques pour un element TUYAU FISSURE |

     Cet element permet de representer des portions de tuyau droit ou
     de coude fissure, la difference etant faite d'apres le rayon de
     courbure.

     Les caracteristiques du tuyau sont definies dans le repere local de
     l'element, de la meme facon que pour l'element POUTRE.

    'EPAI' : epaisseur
    'RAYO' : rayon exterieur du tuyau
    'ANGL' : ouverture totale en degre de la fissure
    'VX  ' |
    'VY  ' | : composantes du vecteur definissant l'axe du tuyau fissure
    'VZ  ' |
    'VXF '  |
    'VYF '  | : composantes du vecteur definissant l'orientation de la
    'VZF '  |  fissure

    Remarque :

    Le domaine de validite de cet element correspond a un rapport
    RAYO/EPAI compris entre 5.5 et 20.5.

PART{Elements RACCORD}
   | Noms des caracteristiques pour un element RACCORD |

    Pour les elements de raccord fluide-structure autres que LITU,
    il est necessaire de connaa®tre la position du fluide par rapport
    a l'element de raccord. Pour cela on donne derriere le mot-cle
    'LIQU' l'objet geometrique representant le fluide.

PART{Elements LSE2}
   | Noms des caracteristiques pour un element LSE2 |

    'RAYO' : rayon interieur du tuyau
   ('RACO') : rayon de courbure s'il s'agit d'un coude

PART{Elements LITU}
   | Noms des caracteristiques pour un element LITU |

    'RAYO' : rayon interieur du tuyau
   ('RACO') : rayon de courbure s'il s'agit d'un coude
   ('VECT') : mot-cle permettant de definir l'axe local Oy. Il doit
        etre suivi par un POINT representant un vecteur de xOy.
        Cette donnee est imperative s'il s'agit d'un coude.

        Attention : pour les coudes, le vecteur local Oz, deduit
        de Ox et Oy, est situe dans le plan du coude et oriente
        par convention vers l'extrados du coude.

PART{Elements HOMOGENEISE}
   | noms des caracteristiques pour un element HOMOGENEISE |

   'SCEL' : mesure de la cellule elementaire agrandie
   'SFLU' : mesure du domaine fluide dans la cellule agrandie
   'EPS ' : pas tubulaire du milieu
   'NOF1' : rapport de la norme de la deformee modale du tube
        par la norme de la pression selon l'axe du faisceau
   'NOF2' : rapport du produit scalaire de la deformee modale du tube
        et de la deformee modale de la pression par le carre
        de la norme de la pression selon l'axe du faisceau

    Remarque :

    Dans le cas de l'etude d'une tranche , les coefficients 'NOF1' et
    'NOF2' valent 1 tous les deux.
