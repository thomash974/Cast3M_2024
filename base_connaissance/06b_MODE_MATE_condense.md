# MODE, MATE, OPTI : versions condensées (le texte complet est dans le lot B, fichier 06c)

## MODE — modèle (formulation + comportement + éléments)

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
        deplacement du ma

Sections détaillées de la notice MODE (comportements et éléments par formulation) : LINEAIRE ; NON_LINEAIRE (UMAT) ; PLASTIQUE ; ENDOMMAGEMENT ; FLUAGE ; PLASTIQUE_ENDOM ; VISCOPLASTIQUE ; VISCO_EXTERNE ; IMPEDANCE ; Remarques ; Lineaire (ELASTIQUE) ; Non lineaire (PLASTIQUE) ; Sans frottement ; Avec frottement ; MECANIQUE ; FLUIDE ; FLUIDE MECANIQUE ; POREUX ; THERMIQUE CONDUCTION, PHASE ou SOURCE ; THERMIQUE CONVECTION ; THERMIQUE RAYONNEMENT ; THERMIQUE ADVECTION ; DIFFUSION ; DIFFUSION ADVECTION ; DARCY ; FROTTEMENT ; MAGNETODYNAMIQUE ; NAVIER_STOKES ; EULER (Volumes Finis) ; FISSURE ; THERMOHYDRIQUE ; LIAISON.

## MATE — noms de paramètres du matériau par modèle

Syntaxe : `MAT1 = MATE MODL1 NOMC1 VAL1 NOMC2 VAL2 ... ;` (MODL1 = modèle créé par MODE). Le nom de composante `'XXXX'` est limité à 4 caractères. Ci-dessous, pour chaque type de matériau (section de la notice), les noms de paramètres et un libellé abrégé.

**MECANIQUE ELASTIQUE ISOTROPE** : YOUN=module d'Young ; NU=coefficient de poisson ; RHO=masse volumique ; ALPH=coefficient de dilatation thermique… ; TREF=temperature de reference de la… ; TALP=temperature de reference du… ; VISQ=coefficient de viscosite ; KS=raideur de cisaillement ( N/m3 ) ; KN=raideur normale ( N/m3 ) ; ALPN=coefficient de dilatation thermique…
**MECANIQUE ELASTIQUE ARMATURE** : YOUN=module d'Young ; SECT=section de l'armature ; FF=coefficient de frottement angulaire… ; PHIF=coefficient de frottement lineaire… ; GANC=glissement a l'ancrage (0.0) ; RMU0=coefficient de relaxation de… ; FPRG=contrainte de rupture garantie… ; RH10=relaxation a 1000 heures (2.5 %)
**MECANIQUE ELASTIQUE MODAL** : FREQ=frequence (type 'FLOTTANT') ; MASS=masse generalisee (type 'FLOTTANT') ; DEFO=deformee modale (type 'CHPOINT') ; AMOR=amortissement generalise (type… ; CGRA=centre de gravite pour la rotation…
**MECANIQUE ELASTIQUE STATIQUE** : RIDE=produit rigite * deformee (type… ; MADE=produit masse * deformee (type… ; DEFO=deformee (type 'CHPOINT') ; AMOR=amortissement generalise (type…
**MECANIQUE ELASTO NON_LINEAIRE** : ECRO=mot-cle suivi de :
**MECANIQUE ELASTO-PLASTIQUE** : SIGY=limite elastique ; ECRO=mot-cle suivi de : ; H=module d'ecrouissage ; R0=limite elastique ; RM=limite elastique finale ; B=constante liee a l'evolution de la… ; LTR=limite en traction simple ; LCS=limite en compression simple ; SIGF=contrainte limite d'ecoulement ; J1C=valeur de J a l'initiation ; T=module de dechirure ; JDA=mot-cle suivi de : ; TRAC=mot-cle suivi de : ; EPSD=Seuil d'endommagement : il s'agit… ; DC=Valeur critique de la variable D… ; EPSR=Deformation plastique a rupture du… ; NCRI=nombre de directions de faiblesse… ; ANG1=angle de la 1-ere direction avec Ox… ; TRA1=limite en traction selon la 1-ere… ; PHI1=angle de frottement (en degres) ; PSI1=angle de dilatance (en degres) ; STOR=contrainte limite elastique en torsion ; SCOM=contrainte limite elastique en… ; COMP=mot-cle suivi de : ; FLXY=mot-cle suivi de : ; FLXZ=mot-cle suivi de : ; CISY=mot-cle suivi de : ; CISZ=mot-cle suivi de : ; EAYI=module apres plasatification ; YMOM=moment de plastification ; SFDP=degradation de raideur pour des… ; SFDN=negative (SFDN est egale a SFDP… ; PINP="pinching" pour des courbures… ; PINN=(PINN est egale a PINP dans le cas… ; SRDP=adoussissement cyclique pour des… ; SRDN=negative (SRDP est egale a SRDN… ; UELA=deplacement elastique limite au… ; FPLA=effort plastique (100) ; HCIN=module d ecrouissage cinematique… ; PFIS=parametre de l evolution de… ; QFRA=parametre de l evolution de… ; APIH=parametre de l evolution du… ; BPIH=parametre de l evolution du… ; E0=indice des vides initial ; M=coefficient de frottement ; COHE=cohesion ; P0=pression de preconsolidation ; KAPA=pente elastique dans un diagramme… ; LAMD=pente plastique dans un diagramme… ; G1=module de cisaillement ; E1=module d'elasticite de reference ; P1=pression correspondant a la valeur… ; BETA=module de compressibilite plastique ; A=coefficient dans la loi d'ecrouissage ; N=exposant de la loi elastique non… ; SBAR=limite elastique heterogene ; PORO=porosite initiale ; PHI=angle de frottement (utilise dans… ; MU=angle de dilatance (utilise dans le… ; FTRC=resistance maximale en traction ; PNOR=Position de la pointe… ; SJTB=Relation contrainte normale -… ; SJCB=Relation contrainte normale -… ; SJSB=Relation contrainte de cisaillement… ; CPLG=Definition des couplages ; S1T=Glissement au debut du plateau ; S2T=Glissement a la fin du plateau ; S3T=Glissement a la fin de l'adoucissement ; T1T=Contrainte de cisaillement sur le… ; T3T=Contrainte de cisaillement… ; ALFA=Parametre definissant la premiere… ; PERI=Perimetre de la barre d'acier ; AD=fragilite (1.0e-5) ; Y0=seuil en energie pour… ; ALPA=coefficient de couplage des modes I… ; GAIN=module d'ecrouissage cinematique 1… ; AAIN=module d'ecrouissage cinematique 2… ; Q1CO=coefficient critere de Gurson 1 (3.5) ; Q2CO=coefficient critere de Gurson 2 (0.9) ; Q3CO=coefficient critere de Gurson 3 (0.1) ; SYCO=contrainte d'activation du critere… ; NCOE=coefficient d'ecrouissage 1 (2) ; KCOE=coefficient d'ecrouissage 1 (1.0e10) ; TC=degre de corrosion macroscopique… ; GONF=0 si pas de gonflement et 1 sinon.… ; EF=seconde raideur normale ; ECN=seuil de deformation en dessous… ; FRIC=angle du critere de frottement de… ; FNE=limite d'elasticite pour l'effort… ; QT=raideur tangente au dela du seuil… ; TYPE=parametre pour choisir le type de… ; FIMU=angle de frottement entre les… ; SGMT=valeur limite en compression pure ; I0=angle initial d'inclinaison des… ; S0=cohesion ; B0=rapport entre les cisaillements… ; UP=valeur du deplacement tangentiel… ; UR=valeur du deplacement tangentiel… ; KNI=raideur normale initiale du joint ; FI0=angle de frottement residuel entre… ; VM=deplacement normal correspondant a… ; STSY=contrainte de plasticite ; STSU=contrainte ultime ; EPSH=deformation de debut d'ecrouissage ; EPSU=deformation ultime ; ROFA=coefficient RO ; BFAC=rapport de la rigidite… ; A1FA=coefficient A1 ; A2FA=coefficient A2 ; FALD=rapport de la longueur entre deux… ; A6FA=coefficient A6 ; CFAC=coefficient C ; AFAC=coefficient A ; LANC=Longueur d'ancrage ; SECT=Section d'une barre d'acier ; G12=Module de cisaillement ; STFC=containte de compression au pic ; EZER=deformation de compression au pic ; STFT=contrainte de traction au pic ; ALF1=parametre de confinement ; OME1=parametre de confinement ; ZETA=pente de la partie descendante de… ; ST85=plateau de la courbe de compression ; TRAF=facteur definissant l'adoucissement… ; STPT=contrainte residuelle en traction ; FAMX=facteur F1 (definissant le point de… ; FACL=facteur F2 (definissant le point… ; FAM1=facteur F1'(definissant la pente… ; FAM2=facteur F2'(definissant la pente… ; FC=resistance en compression ; FC_R=contrainte residuelle en compression ; STRC=Deformation controlant… ; FT=resistance en traction ; FT_R=contrainte residuelle en traction ; STRT=Deformation controlant… ; SOCT=section d'acier (fonction de l'acier) ; SOGS=limite elasticite (400 MPa) ; DCS=endommagement critique (0.2) ; TCS=degre de corrosion en terme de… ; MS=exposant d'acrouissage (2.786) ; KS=facteur d'acrouissage (500 MPa) ; GCEO=module de Coulomb (15 GPA) ; GAMC=coefficient d'ecrouissage… ; ACOE=coefficient d'ecrouissage… ; LCCO=longueur d'ancrage (fonction de la… ; EPSC=deformation seuil de… ; TCI=degre de corrosion en terme de… ; CALA=indicateur de calcul ; HYST=indicateur pour choisir le type de… ; ALDI=fragilite en traction uniaxiale… ; GAM1=module d'ecrouissage cinematique 1… ; A1=module d'ecrouissage cinematique 2… ; AF=module surface plasticite (1.0) ; AG=module potentiel plasticite (1.0) ; AC=ecrouissage plastique 1 (4.0e10) ; BC=ecrouissage plastique 2 (600.0) ; SIGU=contrainte asymptotique compression… ; THET=inclinaison de la diagonale (en degre) ; YOUS=module d'elasticite ; ROST=Densite volumique de cadre ; EULT=Deformation ultime utilisee pour le… ; DELP=Deformation limite du domaine… ; DELN=Deformation limite du domaine… ; DMAP=Endom. maximum lors de la… ; DMAN=Endom. maximum lors de la… ; TETA=Fraction de la resistance… ; MONP=Evolution de l'effort tranchant (ou… ; MONN=Evolution de l'effort tranchant (ou… ; DELA=Deformation limite du domaine… ; DMAX=Endom. maximum lors de la… ; GAMM=Parametre reglant la position du… ; GAMP=Parametre reglant la position du… ; MONO=Evolution de la force axiale de… ; F0=Porosite initiale du beton (0.3) ; Q1=Parametre du critere de Gurson… ; Q2=Parametre du critere de Gurson… ; Q3=Parametre du critere de Gurson… ; SGM0=Resistance de la matrice cimentaire… ; XN=Exposant du seuil de… ; NVP=Parametre de la viscoplasticite de… ; MVP=Parametre de la viscoplasticite de… ; K=Influence l'evolution de la… ; MDT=Parametre de viscosite de… ; NDT=Parametre de viscosite de… ; MDC=Parametre de viscosite de… ; NDC=Parametre de viscosite de… ; ED0=Seuil en deformation pour la… ; AT=Parametre pour la traction (20000) ; BT=Parametre pour la traction (1.6) ; SIG1=limite elastique dans la premiere… ; SIG2=limite elastique dans la deuxieme… ; TRA2=mot-cle suivi de : ; HHH1=Module d'ecrouissage cinematique de… ; FTPE=Limite originelle de traction de la… ; FCPE=Limite originelle de compression de… ; FTGR=Limite originelle de traction de la… ; FCGR=Limite originelle de compression de… ; WOR0=Travail cyclique de reference ; TREV=Evolution de l'ecrouissage isotrope… ; COEV=Evolution de l'ecrouissage isotrope… ; LCAT=Longueur associee a la courbe de… ; LCAC=Longueur associee a la courbe de… ; EPSO=Parametre d'endommagement cyclique… ; EPSI=deformation plastique equivalente… ; GP=pente du module de cisaillement par… ; GT=terme corrigeant le module de… ; YMAX=limite d'ecoulement maximale a… ; TMO=temperature de fusion du materiau… ; DYG=terme DYG ; C1=coefficient C1' ; C2=coefficient C2' ; C3=terme C3'.T ( produit C3' par la… ; C4=terme C4'.T ( produit C4' par la… ; C5=coefficient C5' ; L=diametre moyen d'un grain ; RHO=densite initiale du materiau ; TAU=parametre sans dimension TAU utlise… ; P=parametre sans dimension P ; SINF=parametre sans dimension SINF ; G=parametre sans dimension g utilise… ; YINF=parametre sans dimension YINF ; Y1=parametre sans dimension Y1 utilise… ; Y2=parametre sans dimension Y2 utilise… ; YC=energie critique d'endommageme ; AL=gouverne la forme et le lieu de… ; NN=caracterise la plus ou moins grande… ; DCRI=permet de simuler une rupture… ; KN=rigidites d'interface normale ; SIG0=Limite elastique ; SIGI=Contrainte ultime ; KISO=module d'ecrouissage lineaire ; VELO=parametre de vitesse ; PC=Doit etre 0 (Seuls les materiaux… ; PA=Parametre d'echelle (habituellement 1) ; QA=Parametre d'echelle (habituellement 1) ; EXPM=Parametre de l'equation du caŽne… ; E=Forme sur le plan deviatorique ; K1=Parametre d'ecrouissage du caŽne… ; K2=Parametre d'ecrouissage du caŽne… ; ETAB=Valeur maximale de etacon(kcon),… ; EXPV=Parametre d'ecrouissage du caŽne… ; CCON=parametre d'evolution de la… ; EXPL=P)rametre d'evolution de la… ; PCAP=Valeur initiale de la contrainte… ; EXPR=parametre d'evolution de la… ; CCAP=parametre d'evolution de la… ; ALP=Shape of cap function. Intersection… ; MSHA=forme de la section deviatorique… ; NNN1=Parametre du critere (dependence de… ; NNN2=Parametre du critere (dependence de… ; ETA0=Densite relative initiale ; PHI0=Angle de friction initial ; NNNC=Parametre du critere (dependance de… ; DIAM=diametre de la fondation (si… ; LX=longueur de la fondation dans la… ; LY=longueur de la fondation dans la… ; QMAX=capacite portante de la fondation ; A6=vitesse d'agrandissement de la… ; ETA3=parametre de viscosite ; XTIM=pas de temps pour le calcul dynamique ; A8=type de calcul ; A9=type de fondation ; KA=raideur en cisaillement horizontal… ; YA0=limite elastique de le l'acier (en N) ; KB=raideur en cisaillement horizontal… ; YB0=seuil d'endommagement du beton (en… ; PULO=relation d'adherence entre le… ; m=Exposant ecrouissage ; Tc=Taux de Corrosion ; Dc=Endommagement critique ; TFUS=FLOTTANT, temperature de fusion du…
**MECANIQUE ENDOMMAGEABLE** : KTR0=seuil en deformation pour la… ; ACOM=parametre pour la compression (1.4) ; BCOM=parametre pour la compression (1900.) ; ATRA=parametre pour la traction (0.8) ; BTRA=parametre pour la traction (17000) ; BETA=correction pour le cisaillement (1.06) ; YS1=seuil en energie pour la traction… ; YS2=seuil en energie pour la… ; A1=parametre pour la traction (5000 MPa) ; B1=parametre pour la traction (1.5) ; A2=parametre pour la compression (10 MPa) ; B2=parametre pour la compression (1.5) ; BET1=gere les deformations inelastiques… ; BET2=gere les deformations inelastiques… ; SIGF=contrainte de refermeture de… ; EPCR=deformation au debut de… ; MUP=rapport du module tangent au module… ; Y0=seuil d'endommagement ; YC=energie critique d'endommageme ; GAM1=parametres de couplage entre… ; AL=gouverne la forme et le lieu de… ; NN=caracterise la plus ou moins grande… ; DCRI=permet de simuler une rupture… ; KS=rigidites d'interface en cisaillement ; KN=rigidites d'interface normale ; MM=parametre de l'effet de retard (… ; KK=temps caracteristique ; RATI=rapport des resistances en… ; LOI=1 si la loi d'endommagement est… ; HLEN=longueur caracteristique (cf.… ; GVAL=energie de fissuration (300) ; FTUL=Limite en traction (3.6e6) ; REDC=Coefficient d'abaissement (1.7e6) ; FC01=Limite elastique en compression… ; RT45=Rapport en comp. bi-axiale (1.18) ; FCU1=Contrainte au pic de compression… ; STRU=Deformation ultime en compression… ; EXTP=Deformation de reference en… ; STRP=Contrainte de reference en… ; EXT1=Deformation point 1 (-0.006) ; STR1=Contrainte point 1 (-35e6) ; EXT2=Deformation point 2 (-0.008) ; STR2=Contrainte point 2 (-22e6) ; NCRI=indicateur 1 : post pic en traction… ; K0=seuil en deformation pour la… ; A=Parametre d'endommagement A (5.D03) ; a=Parametre d'endommagement de… ; etaC=Parametre de sensibilite… ; etaT=Parametre de sensibilite… ; Dc=Valeur critique de l'endommagement… ; GF=enargie de fissuration ; LTR=resistance en traction ; LCS=resistance en compression uniaxiale ; LBI=resistance en compression biaxiale ; SIGY=limite d'elasticite en compression… ; EPM=deformation au pic en compression… ; EPU=deformation ultime en compression… ; LCAR=longueur caracteristique ; ALFA=parametre lie a la concavite de la… ; C=parametre associe a la duree de vie ; ALFA1=parametre associe a la duree de vie ; ALFA2=parametre pilotant le niveau… ; ALFA3=parametre lie a la concavite de la… ; FT=resistance equivalente en traction… ; ALDI=fragilite en traction uniaxiale… ; ALIN=fragilite en compression uniaxiale… ; YOUF=module d'Young equivalent en partie… ; NUF=coefficient de Poisson "quivalent… ; GAMT=parametre endommagement de traction… ; GAMC=parametre endommagement de… ; GAMF=parametre endommagement en partie… ; SEUI=seuil initial d'activation de… ; ALF=coefficient de couplage des… ; XNX=CHAMELEM initial des normales aux… ; XNY=CHAMELEM initial des normales aux… ; IND1=CHAMELEM (0 ou 1) ; 0 si non… ; SREF=contrainte de fermeture des… ; AF=parametre critere compression 1 - ; AG=parametre critere compression 1 - ; BF=parametre critere compression 2 - ; BG=parametre critere compression 2 - ; AC=evolution plasticite en compression… ; BC=evolution plasticite en compression… ; SIGU=contraintes asymptotique en… ; FC=contrainte d'activation de la… ; EPUT=deformation limite en traction… ; EPUC=deformation limite en compression… ; NEND=indicateur pour choisir la maniere… ; SIGT=resistance en traction (3.6 MPa) ; QP="vitesse" de refermeture de fissure… ; CF=coefficient de frottement des… ; TFUS=FLOTTANT, temperature de fusion du…
**MECANIQUE FLUAGE** : TTRA=Temperature de transition ; ENDG=Deformation totale au dela de… ; TFUS=FLOTTANT, temperature de fusion du…
**MECANIQUE PLASTIQUE-ENDOMMAGEABLE** : RHO=la densite initiale du materiau ; TRAC=mot cle suivi de : ; EVOL=mot cle suivi de : ; COMP=mot cle suivi de: ; ECRO=mot-cle suivi de : ; SIG1=parametre SIG1 intervenant dans le… ; D=parametre D intervenant dans le… ; F=parametre F0, fraction volumique… ; FC=fraction volumique de cavites… ; Q=Q ; FU=F_U valeur ultime de F_* ( en… ; FF=F_F valeur ultime de F, au dela le… ; FNS=FNS valeur maximale de la fraction… ; FNE=FNE valeur maximale de la fraction… ; SNS=SNS ecart autour de SIGN pour… ; SNE=SNE ecart autour de EPSN pour… ; SIGN=SIGN contrainte moyenne pour… ; EPSN=EPSN deformation plastique moyenne… ; F0=fraction de cavites initiale ; Q2=Q2 ( 1. si non fourni ) ; Q3=Q3 ( Q**2 si non fourni ) ; SRMA=valeur 1. pour tenir compte de la… ; AC=Parametre de la partie… ; AT=Parametre de la partie… ; BC=Parametre de la partie… ; BT=Parametre de la partie… ; EPD0=seuil d'endommagement en… ; RC=Maximum des contraintes effectives… ; RT=Maximum des contraintes effectives… ; P=Parametre de la partie plasticite… ; AH=Parametre de la partie plasticite… ; BH=Parametre de la partie plasticite… ; CH=Parametre de la partie plasticite… ; GAMA=Parametre de la partie plasticite… ; ALFA=Parametre de la partie plasticite… ; A=Parametre de la partie plasticite… ; K0=Parametre pour la partie plasticite… ; TFUS=FLOTTANT, temperature de fusion du…
**MECANIQUE VISCO-PLASTIQUE** : SIGY=valeur initiale de la limite… ; N=exposant de la loi de viscosite 24 ; K=coefficient de viscosite 151 MPa ; A=coefficient d'ecrouissage… ; C=terme de rappel d'ecrouissage… ; B=coefficient d'ecrouissage isotrope 8 ; Q=ecrouissage isotrope a saturation… ; CK=constante dans la loi d'evolution… ; R0=valeur initiale de la limite… ; CD=constante dans la loi d'evolution… ; M=exposant de la deformation… ; A1=coefficient de la deformation… ; C1=coefficient du terme de rappel 180 ; C0=reglage pour deformation… ; P1M0=seuil pour terme de reglage ; G=coefficient du terme de… ; R=exposant du terme de restauration 4 ; NN=exposant de la deformation… ; C2=coefficient de la deformation… ; G1=coefficient du terme de… ; R1=exposant de ALPHA2 4. ; BETA=coefficient de ALPHA4 0.4 ; KK=valeur initiale de la limite… ; K0=coefficient de viscosite 116 MPa ; ALFK=coefficient d'evolution isotrope de… ; ALFR=coefficient d'evolution isotrope du… ; ALF=coefficient de viscosite 2.E6 ; BET1=facteur de normalisation pour la… ; A2=coefficient de la deformation… ; BET2=facteur de normalisation pour la… ; R2=exposant du terme de restauration 4 ; PHI=coefficient multiplicatif du terme… ; GAMA=coefficient de l'effet de… ; QMAX=valeur maximale de Q 455 MPa ; QSTA=valeur stabilisee de Q 200 MPa ; MU=coefficient de la loi d'evolution… ; ETA=facteur liant q a la deformation… ; QT=courbe d'evolution de Q(0) en… ; EXP1=exposant du terme de rappel 2. ; EXP2=exposant du terme de rappel 2. ; CP1=Coefficient de ALPHAp1 34000 MPa ; CP2=Coefficient de ALPHAp2 60000 MPa ; CV1=Coefficient de ALPHAv1 24000 MPa ; CV2=Coefficient de ALPHAv2 9000 MPa ; CVP1=Coefficient de couplage… ; CVP2=Coefficient de couplage… ; DP1=Coefficient de ALPHAp1*dp 250 ; DP2=Coefficient de ALPHAp2*dp 3000 ; DV1=Coefficient de ALPHAv1*dv 300 ; DV2=Coefficient de ALPHAv2*dv 3000 ; BP=Coefficient de P 120 ; QP=Coef. de l'ecrouissage isotrope… ; RP0=Valeur initiale du seuil plastique… ; BV=Coefficient de V 10 ; QV=Coef. de l'ecrouissage isotrope… ; RV0=Valeur initiale du seuil… ; KS=Coefficient de normalisation du… ; H0=taux d'ecrouissage athermique initial ; AP=exposant de la loi d'ecrouissage ; SB=coefficient de la loi de saturation… ; S0=valeur initiale de S ; CL1=coefficient de la deformation… ; DNL1=coefficient du terme de rappel ; GDM1=facteur de normalisation pour la… ; PTM1=exposant du terme de restauration ; CL2=coefficient de la deformation… ; DNL2=coefficient du terme de rappel ; GDM2=facteur de normalisation pour la… ; PTM2=exposant du terme de restauration ; RMAX=valeur maximale de R ; BR=coefficient d'ecrouissage isotrope ; H=ecrouissage cinematique ; HVIS=module lie a la viscosite ; DILT=PDILT, liste de reels contenant les… ; NDIM=NDIME, liste de 4 entiers en format… ; COHI=PCOHI, liste de reels contenant les… ; ACOU=PECOU, liste de reels contenant les… ; ECRI=PECRI, liste de reels contenant les… ; ECRC=PECRC, liste de reels contenant les… ; DURI=PDURI, liste de reels contenant les… ; CROI=PCROI, liste de reels contenant les… ; INCR=PINCR, liste de reels contenant les… ; SIP1=SENSIP1, numero d'ordre de la 1ere… ; SIP2=SENSIP2, numero d'ordre de la 2eme… ; YOUN=module d'Young ; NU=coefficient de Poisson ; ALPH=coefficient de dilatation thermique… ; TREF=temperature de reference de la… ; TALP=temperature de reference du… ; RHO=masse volumique initiale ; DG=taille de grain ; KP=constante du modele ; K1=constante du modele ; M1=constante du modele ; Q1=energie d'activation du mecanisme 1 ; N1=constante du modele ; CR=concentration en Chrome ; CR1=constante du modele ; CR2=constante du modele ; CR3=constante du modele ; K2=constante du modele ; M2=constante du modele ; Q2=energie d'activation du mecanisme 2 ; N2=constante du modele ; DG0=constante du modele ; OMEG=constante du modele ; Q3=energie d'activation du systeme ; N3=constante du modele ; ADEN=donnee specifique du materiau ; KGON=coefficient de gonflement ; BUMI=valeur seuil du taux de combustion… ; EFIS=energie moyenne degagee par fission ; POR0=porosite initiale ; TYPE=0. (par defaut) si combustible UO2,… ; COMP=0. (par defaut) si combustible… ; DYN=0. (par defaut) si couplage statique, ; DYN1=constante de la fonction de… ; DYN2=constante de la fonction de… ; DYN3=constante de la fonction de… ; RI=valeur limite de l'ecrouissage ; SD=facteur endommagement ductile ; RD=exposant endommagement ductile ; PD=seuil d'endommagement ductile ; SC=facteur endommagement de fluage ; RC=exposant endommagement de fluage ; PC=seuil d'endommagement de fluage ; ECRO=mot-cle suivi de : ; DIM3=dimension 3 en cas de calcul 2D ; FIBR=entier à mettre à 1 en presence de… ; NREN=nombre de types de renforts longs… ; DALR=coefficient de dilatation… ; HREF=hydratation de reference pour la… ; HYDR=avancement chimique controlant la… ; HYDS=hydratation seuil ; YORF=Young matrice pour hydratation de… ; NURF=Nu matrice pour hydratation de… ; RT=resistance a la traction pour l… ; REF=contrainte de refermeture de… ; DELT=coeff de confinement pour le… ; EPT=deformation au pic de traction (si… ; GFT=energie de fissuration en raction ; EPC=deformation totale au pic de… ; EKDC=deformation caracteristique pour la… ; DT80=endommagement thermique… ; TSTH=temperature seuil endo thermique ; GFR=energie de refermeture des fissures… ; ALTC=Influence de l endo de traction sur… ; VRAG=volume de gel de RAG cree par unite… ; HRAG=ecrouissage relatif pour la… ; KRAG=module de compressibilite pour le… ; EKDG=deformation caracteristique pour la… ; VVRG=volume des vides accessibles a la RAG ; CRAG=coeff de concentration de… ; TRAG=temps caracteristique de l alcali… ; NRJR=energie d'activation de l alcali… ; SRSR=degre de saturation seuil pour la rag ; TTRG=temperature de reference pour la rag ; DCDG=coeff de couplag endo de rag endo… ; PORO=volume de pores CAPILLAIRES par… ; VW=volume d eau pour le retrait par… ; CSHR=coeff de concentration de… ; BSHR=coefficient de Biot pour le non sature ; MSHR=module de de la courbe de rention d… ; MVGN=exposant pour la loi de Van-Genuchten ; DCDW=couplage entre endommagement… ; SKDW=contrainte caracteristique… ; TTKW=temperature caracteristique pour… ; HSHR=module d ecrouissage pour la micro… ; TTRW=temperature de reference pour la… ; KWRT=coeff de couplage depression… ; KWRC=coeff de couplage sechage… ; EKFL=deformation caracteristique… ; YKSY=rapport module kelvin / module… ; XFLU=endommagement maximum par fluage ; TAUK=temps caracteristique kelvin ; TAUM=temps caracteristique maxwell ; NRJM=NRJ activation du potentiel de… ; TTRF=temperature de reference pour le… ; DFMX=endommagement maxi par fluage ; MDTT=module de Biot pour la deformation… ; TDTT=temps caracteristique pour la… ; WDTT=quantite d eau de reference dans… ; PDTT=pression d eau caracteristique dans… ; VREF=volume de ref pour la mesure de RTP ; VMAX=volume max pour methode wl2 ; CVRT=coeff de variation de la resistance… ; TPRD=temps cracteristique pour la… ; NRJP=energie d activation de… ; SRSD=saturation caracteristique pour les… ; VDEF=quantite maximale de def par unite… ; NALD=teneur en alcalin libre en solution… ; SSAD=rappot sulfate sur aluminium du… ; NAKD=seuil caracteristique en alcalins… ; NABD=seuil en alcalins pour le blocage… ; EXND=exposant de la loi de couplage… ; EXMD=exposant de la loi de couplage… ; TTKD=temperature caracteristique de… ; TDID=temps caracteristique de… ; TFID=temps caracteristique de fixation… ; NRJD=energie d activation de dissolution… ; TTRP=temperature de reference pour le… ; EKDS=deformation caracteristique pour l… ; TTKF=temperature seuil pour la fixation… ; NRJF=energie d activation pour la… ; NSUL=nombre de moles de sulfates ; HDEF=modules d ecrouissage pour la DEF ; KDEF=module de compressibilite de la DEF ; VVDF=Module de biot pour la DEF ; CDEF=coeff de concentration de… ; DCDS=coeff de couplage endo de def endo… ; SSJA=contrainte seuil minimale pour… ; TMJA=temps caracteristique ecoulement… ; YOJA=module d young jeune age lorsque… ; NUJA=coefficient de poisson jeune age… ; DLJA=coeff DELTA de Drucker Prager au… ; RCJA=RC jeune age lorsque HYDR<HYDS ; RTJA=RT jeune age ; ROA1=densite volumique des armatures de… ; VR11=projection sur le 1er axe (2eme… ; VR12=projection sur le 2eme axe (2eme… ; VR13=projection sur le 3eme axe (2eme… ; PRE1=precontrainte initiale ; YOR1=module d Young de armature de type 1 ; SYR1=limite elastique ; HPL1=module d ecrouissage cinematique ; SUR1=contrainte maximale de traction ; EPU1=deformation plastique de debut d… ; WPR1=energie surfacique de rupture… ; DEQ1=diametre equivalent de l armature… ; TYR1=contrainte de cisaillement de l… ; HIR1=rigidite de l interface armature /… ; TTR1=temperature de reference pour les… ; SKR1=contrainte de reference pour la… ; TMR1=temps caracteristique du module de… ; EKR1=potentiel de fluage pour la loi de… ; XFL1=coefficient de non linearite du… ; TKR1=temps caracteristique du fluage… ; YKY1=rapport entre la deformation… ; ATR1=energie d activation du fluage ; CTM1=coefficient de couplage… ; MUS1=tau de chargement a partir duquel l… ; XNR1=exposant de la loi d activation… ; RHOF=densite volumique de fibres ; DIFI=diametre des fibres ; LOFI=longueur des fibres ; EOF1=valeur de l'ellipsoide… ; EOF2=valeur de l'ellipsoide… ; EOF3=valeur de l'ellipsoide… ; VF11=composante 1 du premier vecteur… ; VF12=composante 2 du premier vecteur… ; VF13=composante 3 du premier vecteur… ; VF21=composante 1 du second vecteur… ; VF22=composante 2 du second vecteur… ; VF23=composante 3 du second vecteur… ; YOFI=module d'Young des fibres ; FYF=limite elastique des fibres ; FU=contrainte ultime admissible par… ; RTEC=resistance moyenne à la traction du… ; LECH=longueur de l'essai de reference… ; MW=coefficient de Weibull lie à la… ; HFI=rigidite de l'interface fibre-matrice ; TMAX=contrainte de debut de decollement… ; TD=contrainte de frottement… ; SK=glissement caracteristique… ; MECR=module d'ecrouissage (contrainte)… ; LCAN=longueur ancree caracteristique… ; FABO=force d'about lie à un defaut… ; ALEC=angle d'ouverture du pentaedre… ; MUF=coefficient de frottement… ; NINC=nombre de types d inclusions (la… ; FRA0=fraction volumique ; YOU0=module de Young ; NUP0=coefficient de Poisson ; ALP0=coefficient de dilatation thermique ; TFL0=temps caracteristique du fluage… ; EAF0=energie d activation thermique du… ; FLM0=coefficient de fluage non lineaire… ; FLK0=coefficient de fluage reversible de… ; RTP0=resistance effective en traction de… ; RFP0=contrainte de refermeture de… ; RTI0=resistance a la traction en… ; RFI0=contrainte de refermeture de… ; DLT0=coefficient de frottement interne… ; BTA0=coefficient de dilatance pour l… ; COH0=cohesion en cisaillement pour le… ; SWP0=saturation en eau de la porosite de… ; MVG0=module de Van Genuchten pour la… ; NVG0=exposant de Van Genucten pour la… ; CPH0=variation de volume de la phase par… ; VCH0=potentiel de gonflement chimique de… ; SRS0=saturation en eau minimale pour la… ; TCH0=temps caracteristique de la… ; EAC0=energie d'activation de la reaction… ; ACS0=avancement de la reaction au moment… ; KCH0=coefficient de compressibilite du… ; DCPK=endomagement au pic de compression ; MCC=Module d ecrouissage initial pour… ; PPCC=pression de preconsolidation à… ; PFCC=pression de fin de consolidation… ; TT0E=temperature de debut de reduction… ; TT1E=temperature mediane de reduction… ; MTTE=exposant de non linearite pour le… ; PTTE=fraction residuelle du module d… ; TT0C=temperature de debut de reduction… ; TT1C=temperature mediane pour la… ; MTTC=exposant de non linearite de la… ; PTTC=fraction residuelle de resistance a… ; TT0T=temperature de debut de reduction… ; TT1T=temperature mediane de reduction… ; MTTT=exposant de non linearite pour l… ; PTTT=fraction residuelle de resistance… ; TFUS=FLOTTANT, temperature de fusion du…
**MECANIQUE VISCO_EXTERNE**
**MECANIQUE NON_LOCAL** : CAP1=terme capacitif pour l equation d… ; BLO1=indicateur de conditions aux… ; DEP1=valeur du deplacement impose sur la… ; INI1=valeur initiale de la variable de… ; LIN1=indicateur de linearite du probleme… ; DH11=coefficient de diffusion non locale… ; V111=projection sur le 1er axe du repere… ; V112=projection sur le 2eme axe du… ; V113=projection sur le 3eme axe du… ; DH12=coefficient de diffusion non locale… ; V121=projection sur le 1er axe du repere… ; V122=projection sur le 2eme axe du… ; V123=projection sur le 3eme axe du… ; DH13=coefficient de diffusion non locale… ; V131=projection sur le 1er axe du repere… ; V132=projection sur le 2eme axe du… ; V133=projection sur le 3eme axe du…
**MECANIQUE IMPEDANCE** : CPLE=module de torsion (Nm) (type… ; INER=moment d'inertie (type 'FLOTTANT') ; AROT=amortissement reduit en rotation (%) ; RAID=raideur (N/m) (type 'FLOTTANT') ; MASS=masse (type 'FLOTTANT') ; AMOR=amortissement generalise (%) (type… ; ZNU=coefficient numerique utilise comme… ; ALPH=coefficient de dilatation thermique… ; VISC=viscosite de friction (Ns/m) (type… ; MOCO=module complexe (type 'EVOLUTION')
**MECANIQUE CAOUTCHOUC**
**MECANIQUE ELASTIQUE ORTHOTROPE** : NU12=coefficient de Poisson ; G12=module de cisaillement ; TREF=temperature de reference de la… ; TALP=temperature de reference du… ; RHO=masse volumique ; KN=raideur normale au plan du joint ; ALPN=coefficient de dilatation thermique… ; QN=raideur angulaire de torsion ( N.m ) ; ALP1=coefficient de dilatation thermique… ; ALP2=coefficient de dilatation thermique… ; ALQN=coefficient de dilatation thermique… ; ALQ1=coefficient de dilatation thermique… ; ALQ2=coefficient de dilatation thermique… ; MASS=masse totale du bloc represente par… ; JX=inertie de rotation autour de l'axe… ; JY=inertie de rotation autour de l'axe… ; JZ=inertie de rotation autour de l'axe… ; KS=raideur de cisaillement ( N/m ) ; QS=raideur angulaire de flexion ( N.m ) ; ALPS=coefficient de dilatation thermique… ; ALQS=coefficient de dilatation thermique…
**MECANIQUE ELASTIQUE ANISOTROPE** : TREF=temperature de reference de la… ; TALP=temperature de reference du… ; RHO=masse volumique ; MASS=masse totale du bloc represente par… ; JX=inertie de rotation autour de l'axe… ; JY=inertie de rotation autour de l'axe… ; JZ=inertie de rotation autour de l'axe…
**MECANIQUE ELASTIQUE UNIDIRECTIONNEL** : YOUN=module d'Young ; RHO=masse volumique ; ALPH=coefficient de dilatation thermique… ; TREF=temperature de reference de la… ; TALP=temperature de reference du…
**MECANIQUE ELASTIQUE SECTION** : MODS=modele decrivant la section (type… ; MATS=proprietes materielles decrivant la…
**LIQUIDE** : RHO=masse volumique ; RORF=masse volumique de reference ; CSON=celerite du son ; CREF=celerite de reference ; LCAR=longueur caracteristique ; G=acceleration de la pesanteur
**HOMOGENEISE FLUIDE-STRUCTURE** : B11=permeabilite acoustique selon l'axe X ; B22=permeabilite acoustique selon l'axe Y ; B12=permeabilite acoustique mixte ; ROF=masse volumique du fluide ; CSON=celerite du son dans le fluide ; YOUN=rigidite des tubes ; ROS=masse volumique des tubes ; RORF=masse volumique de reference du fluide ; CREF=celerite de reference dans le fluide ; LCAR=longueur caracteristique du domaine… ; E111=| ; E112=| ; E121=| coefficients cellulaires du… ; E122=| ; E221=| ; E222=|
**RACCORD FLUIDE-TUYAU** : RHO=masse volumique ; RORF=masse volumique de reference ; LCAR=longueur caracteristique
**THERMIQUE CONDUCTION** : RHO=masse specifique ; C=chaleur specifique ; TINI=temperature initiale du milieu ; K=conductivite isotrope ; KT=conductivite integree equivalente
**THERMIQUE Changement de PHASE** : TPHA=temperature de changement de phase ; QLAT=chaleur latente par unite de masse
**THERMIQUE CONVECTION** : H=coefficient d'echange ; TC=temperature "exterieure" d'echange… ; TCIN=temperature "exterieure" d'echange… ; TCSU=temperature "exterieure" d'echange…
**THERMIQUE RAYONNEMENT** : EMIS=coefficient d'emissivite pour les… ; EINF=emissivite relative a la face… ; ESUP=emissivite relative a la face… ; E_IN=emissivite de l'infini si besoin… ; T_IN=temperature "a l'infini" (milieu… ; CABS=coefficient d'absorbtion du milieu… ; TABS=temperature de la cavite
**THERMIQUE ADVECTION** : RHO=masse specifique ; C=chaleur specifique ; TINI=temperature initiale du milieu ; K=conductivite isotrope ; VITX=Vitesse suivant X (1D) ; VITE=vitesse de deplacement dans le tuyau
**THERMIQUE SOURCE** : QVOL=densite volumique de chaleur imposee. ; QINF=densite volumique de chaleur… ; QSUP=densite volumique de chaleur… ; QTOT=objet FLOTTANT, quantite de chaleur… ; ORIG=objet POINT, point P0 origine, ; RGAU=objet FLOTTANT, valeur du parametre… ; DIRE=objet POINT, point P1 definissant… ; ZGAU=objet FLOTTANT, valeur du parametre…
**THERMIQUE ORTHOTROPE** : RHO=masse volumique ; C=chaleur massique ; H=coefficient d'echange
**THERMIQUE ANISOTROPE** : RHO=masse volumique ; H=coefficient d'echange ; C=chaleur massique
**CHANGEMENT_PHASE PARFAIT** : PRIM=Valeur de l'inconnue ou du… ; DUAL=Quantite latente par unite de volume.
**CHANGEMENT_PHASE SOLUBILITE** : SOLU=Valeur limite maximale de la…
**DARCY ISOTROPE** : K=permeabilite isotrope
**DARCY ORTHOTROPE**
**DARCY ANISOTROPE**
**COULOMB** : MU=coefficient de frottement (egal a… ; JEU=Distance minimale a respecter entre…
**FROCABLE** : FF=voir code BPEL99 ; PHIF=voir code BPEL99
**ROTATION** : ANGL=angle de la rotation imposee
**DEPLACEMENT** : AMPL=amplification du deplacement impose
**POREUX ELASTIQUE ISOTROPE** : YOUN=module d'Young ; NU=coefficient de poisson ; RHO=masse volumique ; ALPH=coefficient de dilatation thermique… ; TREF=temperature de reference de la… ; TALP=temperature de reference du… ; MOB=module de Biot ; COB=coefficient de Biot ; PERM=permeabilite intrinseque ; VISC=viscosite dynamique du fluide ; ALPM=coefficient de couplage pression -… ; KS=raideur de cisaillement ; KN=raideur normale ; PERT=permeabilite intrinseque tangentielle ; PERH=permeabilite intrinseque normale de… ; PERB=permeabilite intrinseque normale de…
**POREUX ELASTIQUE ORTHOTROPE** : TREF=temperature de reference de la… ; TALP=temperature de reference du… ; RHO=masse volumique ; MOB=module de Biot ; VISC=viscosite dynamique du fluide ; ALPM=coefficient de couplage pression -
**POREUX ELASTIQUE ANISOTROPE** : TREF=temperature de reference de la… ; TALP=temperature de reference du… ; RHO=masse volumique ; VISC=viscosite du fluide ; ALPM=coefficient de couplage pression -
**POREUX ELASTIQUE UNIDIRECTIONNEL** : YOUN=module d'Young ; RHO=masse volumique ; ALPH=coefficient de dilatation thermique… ; TREF=temperature de reference de la… ; TALP=temperature de reference du… ; MOB=module de Biot ; COB=coefficient de Biot ; PERM=permeabilite intrinseque ; VISC=viscosite dynamique du fluide ; ALPM=coefficient de couplage pression -…
**CORFOU** : ETA=resistivite (en ohm.m) ; PERM=permeabilite relative
**MAGNETODYNAMIQUE ORTHOTROPE** : ETA1=resistivite suivant la premiere… ; ETA2=resistivite suivant la deuxieme… ; PERM=permeabilite relative
**Modele CEREM** : AC1=temperature debut transition ; AR1=temperature fin transition ; MS0=temperature transition… ; BETA ; AC ; AA ; ZS ; TPLM ; CARB ; ACAR=temperature transition au… ; DG0=taille de grain ; AGRA ; TIHT=temperature debut refroidissement ; TFHT=temperature fin refroidissement ; DTHT=decrement de temperature ; NHTR=donnees des proportions de phases… ; NLEB=donnees modele de Leblond au… ; ZA=proportion d'austenite ; ZF=proportion de ferrite ; ZB=proportion de bainite ; ZM=proportion de martensite
**Modele PARALLELE**
**Modele ZTMAX** : VIPH=valeur maxi de la variable ; VDEH=valeur mini de la variable ; VPAR=nom de la variable parametre (par…
**loi POISEU_BLASIUS** : RUGO=rugosite (m)
**loi POISEU_COLEBROOK** : RUGO=rugosite (m)
**loi FROTTEMENT1** : REC=nombre de Reynolds critique donne… ; FK=k ; FA=a ; FB=b ; FC=c ; FD=d
**loi FROTTEMENT2** : REC=nombre de Reynolds critique donne… ; FK=k ; FA=a ; FB=b ; FC=c ; FD=d
**loi FROTTEMENT3** : RUGO=rugosite (m) ; FK=k
**loi FROTTEMENT4** : RUGO=rugosite (m) ; FK=k ; SORT=composante optionnelle (type TABLE)
**loi POINT_PLAN FLUIDE** : NORM='NORMALE' (type POINT) ; INER='COEFFICIENT_INERTIE' ; CONV='COEFFICIENT_CONVECTION' ; VISC='COEFFICIENT_VISCOSITE' ; PELO='COEFFICIENT_P_D_C_ELOIGNEMENT' ; FRAP='COEFFICIENT_P_D_C_RAPPROCHEMENT' ; JFLU='JEU_FLUIDE'
**loi POINT_PLAN FROTTEMENT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; JEU ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; AMOR='AMORTISSEMENT' ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION)
**loi POINT_PLAN** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; JEU ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION) ; PERM='LIAISON_PERMANENTE' (type ENTIER 0… ; SPLA='SEUIL_PLASTIQUE' ; AMOR='AMORTISSEMENT'
**loi POINT_POINT FROTTEMENT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; JEU ; POIB='POINT_B' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; AMOR='AMORTISSEMENT' ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION) ; MODE
**loi POINT_POINT DEPLACEMENT_PLASTIQUE** : NORM='NORMALE' (type POINT) ; ECRO='ECROUISSAGE' ; JEU ; POIB='POINT_B' ; PERM='LIAISON_PERMANENTE' (type ENTIER 0… ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION) ; AMOR='AMORTISSEMENT'
**loi POINT_POINT ROTATION_PLASTIQUE** : NORM='NORMALE' (type POINT) ; ECRO='ECROUISSAGE' ; JEU ; POIB='POINT_B' ; PERM='LIAISON_PERMANENTE' (type ENTIER 0… ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION) ; AMOR='AMORTISSEMENT' ; ELAS=(type ENTIER 0 ou 1)
**loi POINT_POINT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; JEU ; POIB='POINT_B' ; PERM='LIAISON_PERMANENTE' (type ENTIER 0… ; AMOR='AMORTISSEMENT' ; LOIC='LOI_DE_COMPORTEMENT' (type EVOLUTION)
**loi POINT_CERCLE MOBILE** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; PCER='CERCLE' ; RAYO='RAYON' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; CINT='CONTACT_INTERIEUR' ; AMOR='AMORTISSEMENT'
**loi POINT_CERCLE FROTTEMENT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; EXCE='EXCENTRATION' ; RAYO='RAYON' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; CINT='CONTACT_INTERIEUR' ; AMOR='AMORTISSEMENT'
**loi POINT_CERCLE** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; EXCE='EXCENTRATION' ; RAYO='RAYON' ; AMOR='AMORTISSEMENT'
**loi CERCLE_PLAN FROTTEMENT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; JEU ; RAYS='RAYON_SUPPORT' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; AMOR='AMORTISSEMENT'
**loi CERCLE_CERCLE FROTTEMENT** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; EXCE='EXCENTRATION' ; RAYS='RAYON_SUPPORT' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; RAYB='RAYON_BUTEE' ; AMOR='AMORTISSEMENT' ; CINT='CONTACT_INTERIEUR'
**loi PROFIL_PROFIL INTERNE/EXTERNE** : NORM='NORMALE' (type POINT) ; RAID='RAIDEUR' ; PFIX='PROFIL_FIXE' (type MAILLAGE) ; PMOB='PROFIL_MOBILE' (type MAILLAGE) ; ERAI='EXPOSANT_RAIDEUR'
**loi LIGNE_LIGNE FROTTEMENT** : NORM='NORMALE' (type POINT) ; LIMA='LIGNE_MAITRE' (type MAILLAGE) ; LIES='LIGNE_ESCLAVE' (type MAILLAGE) ; RAID='RAIDEURS' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; JEU ; AMOR='AMORTISSEMENT' ; RECH='RECHERCHE' (type ENTIER 0 : local,… ; SYME='SYMETRIE' (type ENTIER 0 ou 1)
**loi LIGNE_CERCLE FROTTEMENT** : NORM='NORMALE' (type POINT) ; LIMA='LIGNE_MAITRE' (type MAILLAGE) ; LIES='LIGNE_ESCLAVE' (type MAILLAGE) ; RAID='RAIDEURS' ; GLIS='COEFFICIENT_GLISSEMENT' ; ADHE='COEFFICIENT_ADHERENCE' ; RTAN='RAIDEUR_TANGENTIELLE' ; ATAN='AMORTISSEMENT_TANGENTIEL' ; AMOR='AMORTISSEMENT' ; RECH='RECHERCHE' (type ENTIER 0 : local,… ; RAYO='RAYON' ; ACTN='ACTNOR' (type ENTIER 0 ou 1) ; INVE='INVERSION' (type ENTIER 0 ou 1)
**loi PALIER_FLUIDE RHODE_LI** : LONG='LONGUEUR_PALIER' ; RAYO='RAYON_ARBRE' ; VISC='VISCOSITE_FLUIDE' ; RHOF='RHO_FLUIDE' ; PADM='PRESSION_ADMISSION' ; VROT='VITESSE_ARBRE' ; EPSI='CRITERE_ARRET' ; PHII ; AFFI ; TLOB='GEOMETRIE_PALIER' ; AMOR='AMORTISSEMENT'
**loi COUPLAGE DEPLACEMENT** : ORIG='ORIGINE'
**loi COUPLAGE VITESSE** : ORIG='ORIGINE'
**loi POLYNOMIALE** : COEF='COEFFICIENT'
**loi NEWMARK MODAL** : JEU ; EXCE=soit u le deplacement normal, ; FROT=coefficient de frottement ; MOFR=modele (type MMODEL) sur lequel…
**loi de FICK** : KD=coefficient de diffusion ; CDIF=terme capacitif, analogue a…
**DIFFUSION ORTHOTROPE** : CDIF=terme capacitif,
**DIFFUSION ANISOTROPE** : CDIF=terme capacitif,
**Reperes d'orthotropie pour elements coques** : RADIAL=equivaut a "DIRECTION (PT - P1)",… ; INCLINE=La premiere direction d'orthotropie…
**Reperes d'orthotropie pour elements massifs** : RADIAL=en dimension 2, VEC1 joint le point… ; INCLINE=La premiere direction d'orthotropie…
**Direction des materiaux unidirectionnels**
**DIFFUSION ADVECTION** : VITX=Vitesse suivant X (1D) ; DX=Vitesse suivant X (1D) ; VITE=Vitesse axiale ; DL=Taille de maille dans la direction…
**Elements Massifs**
**Elements COQ2, COQ3, COQ4, DKT, DST** : EPAI=epaisseur de la coque
**Elements COQ6, COQ8** : EPAI=epaisseur de la coque
**Elements ROT3** : EPAI=epaisseur de la coque (avec 'MATE')
**Elements POJS, TRIS, QUAS** : SECT=aire de la section droite… ; ALPY=facteur de gauchissement dans la… ; ALPZ=facteur de gauchissement dans la…
**Elements JOINT generalise**
**Elements BARRE** : SECT=section droite
**Elements CERCE** : SECT=section droite
**Elements POUTRE, TIMO** : SECT=section droite ; INRY=moment d'inertie par rapport a… ; INRZ=moment d'inertie par rapport a… ; TORS=moment d'inertie de torsion (3D…
**Elements TUYAU** : EPAI=epaisseur ; RAYO=rayon exterieur du tuyau
**Elements LINESPRING** : EPAI=epaisseur de la coque ; FISS=profondeur de l'entaille
**Elements TUYAU FISSURE** : EPAI=epaisseur ; RAYO=rayon exterieur du tuyau ; ANGL=ouverture totale en degre de la…
**Elements RACCORD**
**Elements LSE2** : RAYO=rayon interieur du tuyau
**Elements LITU** : RAYO=rayon interieur du tuyau
**Elements HOMOGENEISE** : SCEL=mesure de la cellule elementaire… ; SFLU=mesure du domaine fluide dans la… ; EPS=pas tubulaire du milieu ; NOF1=rapport de la norme de la deformee… ; NOF2=rapport du produit scalaire de la…

## OPTI — options les plus courantes

'OPTION' MOT1 VAL1 (MOT2 VAL2 ...) ;
Mots-clés fréquents : DIME (1,2,3), ELEM (SEG2, TRI3, QUA4, CUB8, TET4, TRI6, QUA8, CU20…), MODE (PLAN CONT / PLAN DEFO / AXIS / TRID / FOUR / UNID), TRAC (X, OPEN, PSC, FICHIER), ECHO (0 ou 1), DENS. Détail complet dans le lot B, fichier 06c.
