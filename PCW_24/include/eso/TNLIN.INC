C***********************************************************************
C  TNLIN.INC       INCLUDES DE TRAVAIL POUR NLIN
C***********************************************************************
C***********************************************************************
C NOM         : SELREF.INC
C DESCRIPTION : Segments de description des éléments de référence.
C
C REFERENCES  : 
C * @Book{dhattettouzot,
C    author =    {Gouri Dhatt and Gilbert Touzot},
C    title =        {Une présentation de la méthode des éléments finis},
C    publisher =    {MALOINE S.A.},
C    year =         {1984},
C    series =    {Collection universitaire de Compiègne},
C    address =   {27, rue de l'Ecole-de-Médecine, 75006 PARIS},
C    edition =   {2}
C   }
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 20/07/99, version initiale
C HISTORIQUE : v1, 20/07/99, création
C HISTORIQUE : v1.1 08/99, modifs pour mettre les infos sur quel noeud 
C                          correspond à quel ddl.
C HISTORIQUE : v2, 19/10/99, dans ELREFS, on ne duplique plus le nom
C              d'élément et on utilise un segment extensible, plus
C              souple 
C HISTORIQUE : 05/05/00
C              v1.2 : on ne considère plus que des éléments avec 
C                     approximation nodale (moins générale) pour 
C                     nettoyer le code (peut-être n'est-ce pas très
C                     astucieux)
C HISTORIQUE : 
C***********************************************************************
C
C Segment décrivant les caractéristiques d'un élément de référence
C type Lagrange ou Hermite. On se place dans le cadre d'approximations 
C nodales par sous-domaines.
C L'ensemble des éléments de référence est initialisé dans la subroutine
C inlrfs.eso 
C
C * LNNOM, LNFORM, LNTYPL, LNESP (type ENTIER) : 
C   longueur de chaînes de caractère.
C * NOMLRF : nom unique caractérisant un élément de référence.
C   Notre choix de nom est la concaténation des informations
C   suivantes : - espace de fonctions (L2, H1)
C               - degré de l'approximation (D0, D1, D2)
C               - forme de l'élément (SEgment, TRiangle, QUadrangle,
C                 TEtraèdre, PRisme, CUbe)
C               - nombre de degrés de liberté
C   ex: le triangle linéaire + bulle a pour nom 'H1D1TR4'
C * FORME : forme géométrique de l'élément (SEGMENT, TRIANGLE, 
C           QUADRANGLE, TETRAEDRE, PRISME, CUBE)
C * TYPEL : type d'élément (LAGRANGE, HERMITE). Seul des éléments 
C           de Lagrange sont implémentés pour l'instant.
C * ESPACE : espace de discrétisation de l'inconnue sur l'élément.
C            (L2, H1)
C * DEGRE  : degré de l'approximation
C * NDIMEL : dimension de l'espace de référence
C * NBNOD  : nombre de noeuds d'approximation de l'élément
C * XCONOD : coordonnées des noeuds d'approximation
C * NBDDL  : nombre de degrés de liberté (ddl) de l'élément 
C   (=NBNOD pour les éléments de Lagrange)
C * NPQUAF : pour chaque ddl, le numéro du point du QUAF sur lequel
C            on le localise (=> sa continuité entre éléments)
C * NUMCMP : pour chaque ddl, le numéro de composante qu'on lui 
C            attribue (un point du QUAF peut supporter plusieurs ddl)
C * QUENOD : pour chaque ddl, le numéro du noeud d'approximation de
C            l'élément de référence qui le supporte.
C * ORDDER : pour chaque ddl, on indique l'ordre de dérivation par
C            rapport à chaque coordonnée de l'espace de référence.
C         exemple : si le 5eme ddl correspond à la valeur de 
C                   d^3u/dksi ddzeta^2 au 4eme noeud d'approximation,
C                   on aura : QUENOD(5)=4    noeud
C                             ORDDER(1,5)=1  ord. der. en ksi
C                             ORDDER(2,5)=0  ord. der. en eta
C                             ORDDER(3,5)=2  ord. der. en dzeta
C     Pour les éléments de Lagrange, on choisit en général :
C     QUENOD(i)=i, ORDDER(j,i)=0 tt (i,j)
C * MBPOLY (type POLYNS, voir l'include SPOLYNO) : contient
C   les fonctions de base sur l'élément, il y en a autant que de 
C   degrés de liberté. Les fonctions de forme sont calculés à partir
C   des fonctions de base (cf. kfnref.eso). Les fonctions de base
C   peuvent être les fonctions de forme.
C
C AMELIORATIONS POSSIBLES :
C -----------------------
C * XCONOD pourrait être un pointeur sur un segment de type MCOORD
C   vu sa signification...
C * MBPOLY est actuellement un pointeur sur une base de polynômes.
C   On pourrait généraliser à d'autres types de fonctions (par exemple,
C   les fractions rationnelles qui servent pour les éléments pyramidaux,
C   hexagonaux). Il faudrait alors modifier l'objet qui est pointé par
C   MBPOLY et les subroutines chargés d'évaluer les fonctions de base.
C
      SEGMENT ELREF
      CHARACTER*(LNNOM)  NOMLRF
      CHARACTER*(LNFORM) FORME 
      CHARACTER*(LNTYPL) TYPEL 
      CHARACTER*(LNESP)  ESPACE
      INTEGER DEGRE
      REAL*8 XCONOD(NDIMEL,NBNOD)
      INTEGER NPQUAF(NBDDL)
      INTEGER NUMCMP(NBDDL)
      INTEGER QUENOD(NBDDL)
      INTEGER ORDDER(NDIMEL,NBDDL)
      POINTEUR MBPOLY.POLYNS
      ENDSEGMENT
C
C Segment (extensible) contenant une liste d'éléments de référence.
C 
C  LISEL est la liste des pointeurs sur les éléments de référence.
      SEGMENT ELREFS
      POINTEUR LISEL(0).ELREF
      ENDSEGMENT


C***********************************************************************
C NOM         : SFACTIV.INC
C DESCRIPTION : Segments des faces actives. Sert pour les intégrations
C               sur les faces d'un maillage (Syntaxe de NLIN avec deux
C               maillages)
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 19/12/2002, version initiale
C HISTORIQUE : v1, 19/12/2002, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
*
      SEGMENT FACTIV
      POINTEUR IFACTI(NBSOUV).SFACTI
      ENDSEGMENT
      SEGMENT SFACTI
      POINTEUR ISFACT(NBSOFV).SSFACT
      ENDSEGMENT
      SEGMENT SSFACT
      LOGICAL LFACTI(NBELFV,NBELEV)
      ENDSEGMENT
C
C End of include SFACTIV
C


C***********************************************************************
C NOM         : SFALRF.INC
C DESCRIPTION : Segments de description de familles d'éléments 
C               de référence.
C               Par famille, on entend : ensemble d'éléments de formes
C               géométriques différentes, mais compatibles (au niveau
C               des espaces d'approximation) 
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 17/08/99, version initiale
C HISTORIQUE : v1, 17/08/99, création
C HISTORIQUE : v2, 23/03/99, mise au standard des points de Gauss
C HISTORIQUE :
C***********************************************************************
C
C Segment décrivant les caractéristiques d'une famille d'élément de 
C référence.
C L'ensemble des familles d'éléments de référence est initialisé dans la
C subroutine infals.eso
C * LNNFA (type ENTIER) : longueur de chaîne de caractère.
C * NOMFA  : nom unique caractérisant une famille d'éléments de
C            référence. 
C * NBLRF  : nombre d'éléments de la famille.
C * NUQUAF : numéro d'éléments de type QUAF (cf. tableau NOMS de
C            CCGEOME.INC)
C * ELEMF  : pointeur sur les éléments de référence correspondant à
C            chaque QUAF
C
      SEGMENT FALRF
      CHARACTER*(LNNFA) NOMFA
      INTEGER NUQUAF(NBLRF)
      POINTEUR ELEMF(NBLRF).ELREF
      ENDSEGMENT
C
C Segment (extensible) contenant une liste de familles d'éléments de
C référence.
C
C LISFA est la liste des pointeurs sur des familles d'éléments de
C référence. 
      SEGMENT FALRFS
      POINTEUR LISFA(0).FALRF
      ENDSEGMENT


C***********************************************************************
C NOM         : SFAPG.INC
C DESCRIPTION : Segments de description de familles de méthodes 
C               d'intégration type Gauss.
C               Par famille, on entend : ensemble de méthodes 
C               d'intégration sur des éléments de référence de formes 
C               géométriques différentes, mais d'ordre d'intégration
C               similaires.
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 16/07/02, version initiale
C HISTORIQUE : v1, 16/07/02, création
C HISTORIQUE :
C***********************************************************************
C
C Segment décrivant les caractéristiques d'une famille d'élément de 
C référence.
C L'ensemble des familles d'éléments de référence est initialisé dans la
C subroutine infals.eso
C * LNNFAP (type ENTIER) : longueur de chaîne de caractère.
C * NOMFAP  : nom unique caractérisant une famille de méthodes 
C             d'intégration
C * NBMPG  : nombre de méthodes d'intégration de la famille.
C * NBQUAF : numéros d'élément de type QUAF (cf. tableau NOMS de
C            CCOPTIO.INC)
C * MPOGAU  : pointeur sur les éléments de référence correspondant à
C            chaque QUAF
C
      SEGMENT FAPG
      CHARACTER*(LNNFAP) NOMFAP
      INTEGER NBQUAF(NBMPG)
      POINTEUR MPOGAU(NBMPG).POGAU
      ENDSEGMENT
C
C Segment (extensible) contenant une liste de familles d'éléments de
C référence.
C
C LISFPG est la liste des pointeurs sur des familles de méthodes
C d'intégration

      SEGMENT FAPGS
      POINTEUR LISFPG(0).FAPG
      ENDSEGMENT


C***********************************************************************
C NOM         : SIQUAF.INC
C PROJET      : Noyau linéaire NLIN
C DESCRIPTION : Segments contenant des informations de nature 
C               géométrique sur les élements quadratiques fluides 
C               (QUAFs)
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C APPELES          : 
C APPELES (E/S)    : 
C APPELES (BLAS)   :
C APPELES (CALCUL) :
C APPELE PAR       :
C***********************************************************************
C VERSION    : v1, 17/10/02, version initiale
C HISTORIQUE : v1, 17/10/02, création
C HISTORIQUE :
C HISTORIQUE :
C HISTORIQUE :
C***********************************************************************
C
C Segment décrivant un élément QUAF de référence.
C L'ensemble des des éléments QUAF de référence est initialisé dans la
C subroutine inqfrs.eso
C * NUMQUF : numéro d'éléments de type QUAF (cf. tableau NOMS de
C            CCGEOME.INC)
C * NDIMQR : dimension de l'espace de référence
C * NBNOQR : nombre de noeuds du QUAF de référence
C * XCONQR : Coordonnées dans l'espace de référence des noeuds
C            du QUAF de référence.
C * NUCENT : numéro du noeud (relativement à XCONQR) du centre de
C            l'élément QUAF de référence
C * LFACE  : objet de de type MELEME partitionné donnant les faces 
C            de l'élément QUAF de référence relativement à la
C            numérotation de référence donnée par XCONQR
C
      SEGMENT IQUAF
      INTEGER NUMQUF
      REAL*8 XCONQR(NDIMQR,NBNOQR)
      INTEGER NUCENT
      POINTEUR LFACE.MELEME
      ENDSEGMENT
C
C Segment contenant une liste d'éléments QUAF de référence
C 
      SEGMENT IQUAFS
      POINTEUR LISQRF(NBQRF).IQUAF
      ENDSEGMENT


C***********************************************************************
C NOM         : SLCOMP.INC
C PROJET      : Noyau linéaire NLIN
C DESCRIPTION : Segments contenant des informations sur les lois
C               de comportement
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C APPELES          : 
C APPELES (E/S)    : 
C APPELES (BLAS)   :
C APPELES (CALCUL) :
C APPELE PAR       :
C***********************************************************************
C VERSION    : v1, 10/05/04, version initiale
C HISTORIQUE : v1, 10/05/04, création
C HISTORIQUE :
C HISTORIQUE :
C HISTORIQUE :
C***********************************************************************
C
C Segment décrivant une loi de comportement
C L'ensemble de ces segments est initialisé dans incoms.eso
C * NOMCOM : nom de la loi de comportement de longueur LNNCOM
C * NCOCOF : nombre de coeff dont dépend la loi
C * DERCOF(ICOCOF) = 0 : la loi dépend uniquement du coeff ICOCOF
C                  = 1 : la loi dépend uniquement d'au moins une 
C                        dérivée spatiale du coeff ICOCOF
C                  = 2 : la loi dépend du coeff ICOCOF et d'une de ses
C                        dérivées
C * LTREF          = .FALSE. : la loi de comportement ne dépend pas 
C                              des éléments associés à la transformation
C                              élément de référence -> élément réel 
C                  = .TRUE.  : le contraire
C
      SEGMENT COMP
      CHARACTER*8 NOMCOM
      INTEGER DERCOF(NCOCOF)
      LOGICAL LTREF
      ENDSEGMENT
C
C Segment contenant une liste d'infos sur les comportements
C 
      SEGMENT COMPS
      POINTEUR LISCOM(NBCOMP).COMP
      ENDSEGMENT


C***********************************************************************
C NOM         : SMCHAEL.INC
C DESCRIPTION : Mes champs par éléments ! Objets temporaires pour nlin.
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 19/08/99, version initiale
C HISTORIQUE : v1, 19/08/99, création
C HISTORIQUE :
C HISTORIQUE :
C***********************************************************************
C
C Segment chapeau du champ par éléments.
C * N1 (type ENTIER) : partitionnement du champ par élément
C                      chaque partition contient un seul type d'élément
C * IMACHE : pointeur sur des maillages élémentaires
C * ICHEVA : pointeur sur des champs associés aux maillages élémentaires
C
      SEGMENT MCHAEL
      POINTEUR JMACHE(N1).MELEME
      POINTEUR ICHEVA(N1).MCHEVA
      ENDSEGMENT
C
C Segment contenant les valeurs (scalaires, vectorielles ou
C matricielles) des composantes (scalaires, vectorielles ou
C matricielles) du champ par éléments en un certain nombre 
C de points de l'élément.
C * NBLIG, NBCOL (type ENTIER) : Nb. de lignes et de colonnes 
C   de la valeur matricielle (on choisit généralement NBLIG=1 
C   si la valeur est vectorielle, NBLIG=NBCOL=1 si scalaire)
C * N2LIG, N2COL (type ENTIER) : idem pour pour les composantes
C   (on choisit également N2LIG=composante duale, N2COL=composante
C   primale dans le cas d'une composante matricielle)
C * NBPOI (type ENTIER) : nombre de points où l'on exprime la valeur du
C   champ sur un élément.
C * NBELM (type ENTIER) : nombre d'éléments où l'on exprime la valeur du
C   champ.
C * NMCHLI, NMCHCO : noms de composantes (non utilisés, ils sont juste
C   là pour la lisibilité).
C * WELCHE : les valeurs du champ.
C
C REMARQUES IMPORTANTES :
C -----------------------
C * L'objet défini ainsi ne contient pas tous les éléments nécessaires à
C   son interprétation (par exemple, il ne dit rien sur les points de
C   l'éléments où les valeurs sont exprimées). 
C   Ce n'est pas très grave car c'est un objet temporaire. Par contre
C   son interprétation dépend de l'entité qu'il représente et tous les
C   indices du tableau VELCHE ne servent pas forcément.
C   Un exemple : pour stocker les valeurs de dérivées de fonctions de
C                forme aux points de Gauss sur un élément de référence,
C                on peut imposer : 
C      NBLIG=1 (non utilisé)
C      NBCOL=NDDL (nb. de degrés de liberté de l'élément de référence)
C      N2LIG=1 (non utilisé)
C      N2COL=ISREF (dimension de l'espace de référence)
C            indique par rapport à quelle variable d'espace est
C            effectuée la dérivation.
C      NBPOI=NPOGO (nb. de points de Gauss). On sous-entend que l'on a
C      déjà choisi une méthode d'intégration type Gauss, connue par
C      ailleurs. 
C      NBELM=1 (non utilisé)
C * On utilise les mêmes astuces que pour le vrai CHAMELEM à savoir :  
C   - si un champ est défini sur un nombre NEL d'éléments (obtenu par
C     exemple à l'aide des IMACHE), NBELM peut valoir :
C       -> soit NEL (cas courant)
C       -> soit 1   (auquel cas le champ vaut la même chose sur les NEL
C          éléments)
C   - de même pour les autres indices, ex. si le champ est constant par
C     élément, on peut avoir NBPOI=1, etc...
C   On rejoint la remarque précédente : il faut généralement avoir des
C   informations supplémentaires, extérieures au champ ("vraies" valeurs
C   des indices...) pour pouvoir l'utiliser
C
      SEGMENT MCHEVA
C      CHARACTER*8 NMCHLI(N2LIG),NMCHCO(N2COL)
      REAL*8 WELCHE(NBLIG,NBCOL,N2LIG,N2COL,NBPOI,NBELM)
      ENDSEGMENT
*
      SEGMENT LCHEVA
      POINTEUR LISCHE(NBCHE).MCHEVA
      ENDSEGMENT
C=======================================================================        
C     OBJET DE TYPE 'LIST''LOGI'. DEFINIT UNE LISTE DE LOGIQUE.                  
C=======================================================================        
      SEGMENT MLLOGI
      LOGICAL LOGI(JG)
      ENDSEGMENT
C***********************************************************************
C NOM         : SMTNLIN.INC
C DESCRIPTION : Les segments de données d'entrée et de données de
C      travail pour NLIN 
C
C
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 05/08/2002, version initiale
C HISTORIQUE : v1, 05/08/2002, création
C HISTORIQUE : v1, 27/08/2002, ajout des variables duales
C HISTORIQUE : v2, 26/09/2002, modification, simplification (?)
C HISTORIQUE : v3, 22/08/2003, modifs nls9
C HISTORIQUE : v4, 22/09/2003, refonte complète
C                              on pourrait encore aller une etape plus
C                              loin en ne distinguant plus coeff et
C                              variables 
C***********************************************************************
C
C Segment TUTU
C Description :
C
* Pour la géométrie
      SEGMENT TABGEO
      CHARACTER*4 DISGEO
* 
      POINTEUR JGEO.MCHAEL
*
      ENDSEGMENT
* Pour les variables et les coefficients
      SEGMENT TABVDC
*   Contient un numéro entre 1 et JGVD
      INTEGER VVARPR(NUMVPR)
      INTEGER VVARDU(NUMVDU)
      INTEGER VDATPR(NUMDPR)
      INTEGER VDATDU(NUMDDU)
*   Contient un numéro entre 1 et JGCOF
      INTEGER VCOFPR(NUMCPR)
      INTEGER VCOFDU(NUMCDU)
**  Facteur multiplicatif pour le coefficient (remplace vfmul)
*      REAL*8  XCOFPR(NUMCPR)
*      REAL*8  XCOFDU(NUMCDU)
*
* Contient un pointeur sur une liste de numéros de coefficients
* (entre 1 et JLCOF) ou 0 si le terme n'intervient pas dans
* l'opérateur
*
      INTEGER ILCPR(NUMDER+1,NUMOP,NUMVPR)
      INTEGER ILCDU(NUMDER+1,NUMOP,NUMVDU)
*
* Les listes de coefficients (sans doublons)
*
*      Les MLENTI pointés sont de dimension JGCOF
*    et MLENTI.LECT(IGCOF)=i indique que le coefficient de numéro 
*    IGCOF (entre 1 et JGCOF) sera à la puissance i (éventuellement 0
*    ou négatif)
      POINTEUR VLCOF(JLCOF).MLENTI
*
*  Les coefficients (sans doublons)
*
*    LDAT contient un numéro entre 1 et JGVD
      POINTEUR VCOMP(JGCOF).COMP
      POINTEUR VLDAT(JGCOF).MLENTI
*
*  Les valeurs des variables et des datas (sans doublons) 
*  DJSVD contient un numéro d'espace de discrétisation (entre 1 et KGVD)
*
*   Si MVD.EQ.0 : la valeur de la variable ou de la donnée JGVD est
*                 inconnue 
*   Si MVD.GT.0 : la valeur de la variable ou de la donnée JGVD est
*                 connue et donnée par le chpoint ou le mchaml pointé
*                 Le type de champ est donné par TYPVD      
*   Si MVD.LT.0 : la valeur de la variable ou de la donnée JGVD est
*                 connue et constante donnée par XVD(JGVD)

      INTEGER  DJSVD(JGVD)
      POINTEUR NOMVD(JGVD).MLMOTS
      CHARACTER*8 TYPVD(JGVD)
      INTEGER MVD(JGVD)
*      POINTEUR MVD(JGVD).MCHPOI
*      POINTEUR NVD(JGVD).MCHAML
      REAL*8 XVD(JGVD)
*
*  Les différents espaces de discrétisations 
*  pour les variables et les datas (sans doublons)
*
      CHARACTER*4 DISVD(KGVD)
      ENDSEGMENT
*
* Segment contenant les objets de travail
*
      SEGMENT TATRAV
* Valeurs des listes de coefficients (local)
      POINTEUR VVCOF(JLCOF).MCHEVA
* Valeurs des coefficients (local)
      POINTEUR VCOF(JGCOF).MCHEVA
* Valeurs des variables et data (global)
      POINTEUR IVD(JGVD).MCHAEL
* Valeurs des variables et data et de leurs dérivées (local)
      POINTEUR VD(JGVD).MCHEVA
      POINTEUR DVD(JGVD).MCHEVA
* Fonctions de forme
      POINTEUR FFVD(KGVD).MCHEVA
      POINTEUR DFFVD(KGVD).MCHEVA
*
* On définit des tableaux de logique valant .TRUE. si on a besoin 
* de calculer les MCHEVA correspondant, sauf pour VVCOF : on doit 
* tous les calculer
* 
      LOGICAL LVCOF(JGCOF)
* Valeurs des variables et data et de leurs dérivées (local)
      LOGICAL LVD(JGVD)
      LOGICAL LDVD(JGVD)
* Fonctions de forme
      LOGICAL LFFVD(KGVD)
      LOGICAL LDFFVD(KGVD)
*
      ENDSEGMENT
*
* Segment contenant les matrices élémentaires 
*
      SEGMENT TABMAT
      POINTEUR VMAT(NUMVDU,NUMVPR).MCHAEL
      ENDSEGMENT
C
C End of include SMTNLIN
C


C***********************************************************************
C NOM         : SPOGAU.INC
C DESCRIPTION : Segments décrivant des méthodes d'intégration numérique
C               (type Gauss) : en particulier poids et points 
C               d'intégration.
C
C REFERENCES  : 
C * @Book{stroud,
C    author =    {A.H. Stroud},
C    title =        {Approximate calculation of Multiple Integrals},
C    publisher =    {Prentice-Hall, Inc.},
C    year =         {1971},
C    series =    {Prentice-Hall Series in Automatic Computation},
C    annote =    {M2309A, la bible pour les méthodes de cubature
C                 type Gauss}
C   }
C * Continuation des travaux de Stroud par Ronald Cools :
C   http://www.cs.kuleuven.ac.be/~ronald/index.html
C   mailto://Ronald.Cools@cs.kuleuven.ac.be
C   et ses articles
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v2, 19/10/99
C HISTORIQUE : v1, 21/07/99, création
C HISTORIQUE : v2, 19/10/99, dans POGAUS, on ne duplique plus le nom de
C              méthode, et on utilise un segment extensible, plus souple
C HISTORIQUE : 
C***********************************************************************
C
C Segment décrivant une méthode d'intégration numérique de type Gauss
C L'ensemble des méthodes de type Gauss est initialisé dans la subroutine  
C inpgs.eso
C
C * LNNPG, LNTPG, LNFPG (type ENTIER) :
C   longueur de chaînes de caractère.
C * NOMPG : nom unique caractérisant la méthode d'intégration.
C   Notre choix de nom est la concaténation des informations
C   suivantes : - type de méthode (GAuss, Gauss-Produit (conique), 
C                 Gauss-Jacobi + valeurs de \alpha,\beta)
C               - forme du domaine d'intégration (cf. Stroud) :
C                 * Cubique en dimension 1, 2, 3 (C1, C2, C3)
C                 * Simplex en dimension 2, 3    (T2, T3)
C                 * Prisme à base triangle (PR)
C                 (sauf pour les méthodes Gauss-Jacobi qui sont
C                 forcément sur un C1)
C               - ordre de la méthode d'intégration
C               - nombre de points de la méthode d'intégration
C  Exemple de noms : * GJ10-7-4 (méthode de Gauss-Jacobi \alpha=1 \beta=0
C                      d'ordre 7 à 4 points
C                    * GPT2-7-16 (méthode Gauss-produit sur un triangle,
C                      ordre 7 à 16 points
C * TYPMPG : type de la méthode (GAUSS, GAUSS-JACOBI, GAUSS-PRODUIT)
C * FORLPG : forme géométrique du domaine d'intégration (SEGMENT,
C            TRIANGLE, QUADRANGLE, TETRAEDRE, PRISME, CUBE)
C * NORDPG : ordre de la méthode (tel qu'on intègre exactement tous les
C            monômes d'ordre inférieur ou égal à NORDPG)
C * NBPG   : nombre de points d'intégration.
C * NDLPG  : dimension de l'espace du domaine d'intégration.
C * XCOPG  : coordonnées des points d'intégration
C * XPOPG  : poids associé à chaque point d'intégration
C
C AMELIORATIONS POSSIBLES :
C -----------------------
C * XCOPG et XPOPG pourraient être des pointeurs sur des champs par
C  éléments MCHAEL par souci de régularité avec le reste de nlin.
C
      SEGMENT POGAU
      CHARACTER*(LNNPG)  NOMPG
      CHARACTER*(LNTPG)  TYPMPG
      CHARACTER*(LNFPG)  FORLPG
      INTEGER NORDPG
      REAL*8 XCOPG(NDLPG,NBPG)
      REAL*8 XPOPG(NBPG)
      ENDSEGMENT
C
C     Segment contenant une liste de méthodes d'intégration numérique
C
C  LISPG est la liste des pointeurs sur les méthodes d'intégrations
      SEGMENT POGAUS
      POINTEUR LISPG(0).POGAU
      ENDSEGMENT


C***********************************************************************
C NOM         : SPOLYNO.INC
C DESCRIPTION : Segment servant à stocker un polynôme. 
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DRN/DMT/SEMT/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 05/05/00, version initiale
C HISTORIQUE : v1, 05/05/00, création
C HISTORIQUE :
C HISTORIQUE :
C***********************************************************************
C * NBMON  : nb. de monômes du polynôme
C * NDIML  : les monômes sont dans R^{NDIML}
C * COEMON : coefficient multiplicateur de chaque monôme
C * EXPMON : exposant des monômes de la base polynômiale
C         exemple : si le 4ème monôme du polynôme est x^2 z^3
C                   alors : EXPMON(1,4)=2
C                           EXPMON(2,4)=0
C                           EXPMON(3,4)=3
      SEGMENT POLYNO
      REAL*8  COEMON(NBMON)
      INTEGER EXPMON(NDIML,NBMON)
      ENDSEGMENT 
C
C Segment contenant une liste de NBPOLY polynômes
C 
      SEGMENT POLYNS
      POINTEUR LIPOLY(NBPOLY).POLYNO
      ENDSEGMENT
C***********************************************************************
C NOM         : TMPREC.INC
C DESCRIPTION : Segment contenenant des informations de 
C               préconditionnement
C
C
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SFME/LTMF)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 12/10/2005, version initiale
C HISTORIQUE : v1, 12/10/2005, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
C Segment MPREC
C Description :
C
      SEGMENT MPREC
      POINTEUR DAT(NDAT).MCHEVA
      POINTEUR PREC(NPREC).MCHEVA
      ENDSEGMENT
C
C End of include TMPREC
C


