C***********************************************************************
C NOM         : TMATOP1.INC
C DESCRIPTION : Regroupement de tous les includes définissant des
C     segments, utilisés pour le mailleur topologique, d'après les
C     travaux de T. Coupez et al.
C
C     Voir aussi TMATOP2.INC pour l'include définissant les variables
C     globales (COMMON).      
C
C               Bibliographie :
C
C@article{doi:10.1080/12506559.2000.10511454,
C     author = {Coupez, Thierry},
C     title = {Génération de maillage et adaptation de maillage par
C     optimisation locale},
C     journal = {Revue Européenne des Éléments Finis},
C     volume = {9},
C     number = {4},
C     pages = {403-423},
C     year = {2000},
C     doi = {10.1080/12506559.2000.10511454},
C     URL = {http://www.tandfonline.com/doi/abs/10.1080/12506559.2000.10511454}}
C     
C
C@PhdThesis{,
C  author =       {Cyril Gruau},
C   title =        {Génération de métriques pour adaptation anisotrope
C     de maillage, application à la mise en forme des matériaux}, 
C  school =       {ENSMP},
C  year =         {2004},
C  month =     {10 dec}}
C      
C@article{Gruau20054951,
C     title = "3D tetrahedral, unstructured and anisotropic mesh
C     generation with adaptation to natural and multidomain metric", 
C     journal = "Computer Methods in Applied Mechanics and Engineering",
C     volume = "194",
C     number = "48 - 49",
C     pages = "4951 - 4976",
C      year = "2005",
C     issn = "0045-7825",
C     doi = "10.1016/j.cma.2004.11.020",
C     url = "http://www.sciencedirect.com/science/article/pii/S0045782505000745",
C     author = "Cyril Gruau and Thierry Coupez",
C     keywords = "Topology and shape optimization",
C     keywords = "Elliptic interpolation",
C     keywords = "Thickness detection and curvature treatment",
C     keywords = "Interface refinement"}
C
C @article{Coupez20112391,
C     title = "Metric construction by length distribution tensor and
C     edge based error for anisotropic adaptive meshing",
C     journal = "Journal of Computational Physics",
C     volume = "230",
C     number = "7",
C     pages = "2391 - 2405",
C     year = "2011",
C     issn = "0021-9991",
C     doi = "10.1016/j.jcp.2010.11.041",
C     url = "http://www.sciencedirect.com/science/article/pii/S002199911000656X",
C     author = "T. Coupez",
C     keywords = "Metric",
C     keywords = "Length distribution tensor",
C     keywords = "Anisotropic meshing",
C     keywords = "Interpolation error",
C     keywords = "Edge error estimate"}
C
C
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 31/03/2021, version initiale
C HISTORIQUE : v1, 31/03/2021, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************

C***********************************************************************
C NOM         : SMELEMX.INC
C DESCRIPTION :
C
C     Segment maillage de travail (simple un seul type d'éléments)
C     extensible. Inspiré de MELEME et de TRAVJ 
C     
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 30/10/2017, version initiale
C HISTORIQUE : v1, 30/10/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
C Segment MELEMX
C Description :
C
      SEGMENT MELEMX
      
      INTEGER NLINI,NNINI,NLCOU,NNCOU
*      ,NLMAX,NNMAX
      INTEGER ITYPEX
      INTEGER NUMX(NNMAX,NLMAX)
      ENDSEGMENT
C
C End of include MELEMX
C
C***********************************************************************
C NOM         : SMETRIQ.INC
C DESCRIPTION :
C
*     Segment stockant la métrique à chaque noeud
*     On pourrait s'en servir pour stocker aussi les coordonnées des
*     noeuds       
*      
C
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 23/11/2017, version initiale
C HISTORIQUE : v1, 23/11/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
      SEGMENT METRIQ
      REAL*8 XIN(NNIN,NNNOE)
      ENDSEGMENT
*      
C
C End of include SMETRIQ
C
C***********************************************************************
C NOM         : SMLENTX.INC
C DESCRIPTION :
C
C     Segment liste d'entiers extensible
C     extensible. Inspiré de MLENTI et de MELEMX
C     
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 20/12/2017, version initiale
C HISTORIQUE : v1, 20/12/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
C Segment MLENTX
C Description :
C
      SEGMENT MLENTX
      INTEGER JGINI,JGCOU
      INTEGER LECTX(JGMAX)
      ENDSEGMENT
C
C End of include MLENTX
C
C***********************************************************************
C NOM         : STOPINV.INC
C DESCRIPTION :
C
*
*     Segment Topologie inverse tel que décrit dans la thèse de Gruau
*     p.171
*     Le tableau TLC contient des listes chaînées dont le dernier
*     élément est un -1
*     Le tableau TIC(I) contient un pointeur vers le premier élément de la
*     list chaînée (dans le tableau TLC) pour le Ieme noeud ou -1 si la
*     liste est vide
*     Le tableau TDC(I) contient la longueur de la Ieme liste chaînée
*     pour une liste vide). Ce dernier tableau ne serait pas obligatoire
*     d'après Gruau.
*     LDGT est l'index courant-1 dans TLC (normalement LDGT est un
*     multiple de IDIMP)        
*      
C
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 03/10/2017, version initiale
C HISTORIQUE : v1, 03/10/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
      SEGMENT TOPINV
      INTEGER LDGT
      INTEGER TLC(IDIMP*NBELEM)
      INTEGER TIC(NBPTS)
      INTEGER TDC(NBPTS)
      ENDSEGMENT
*      
C
C End of include STOPINV
C
C***********************************************************************
C NOM         : STRAVJ.INC
C DESCRIPTION :
C
C     Segment de travail en numérotation locale avec des segments
C     extensibles. 
C     
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 11/10/2017, version initiale
C HISTORIQUE : v1, 11/10/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
C Description :
C
*     NVZER sert à compter le nombre d'elements nul que l'on introduit
*     en vue de déclencher un nettoyage (voir topdif)
      SEGMENT TRAVJ
      INTEGER NVINI,NPINI,NVCOU,NPCOU,NVMAX,NPMAX,NVZER
* PVIRT est le noeud virtuel dans la numérotation locale      
*     POINTEUR JCOORD.MCOORD
*     POINTEUR JNMETR.MOTS*4(NNIN).MLMOTS
*     POINTEUR JCMETR.XIN(NNIN,NPMAX).METRIQ
*     POINTEUR JTOPO.MELEME
*     POINTEUR JTOPI.TOPINV
*     POINTEUR JNBL(NVMAX).MLENTI      
*     POINTEUR JNNO(NPMAX-NPINI).MLENTI      
      INTEGER PVIRT
      INTEGER COORD
      INTEGER NMETR
      INTEGER CMETR
      INTEGER TOPO
      INTEGER TOPI
      INTEGER NBL
      INTEGER NNO

**     INTEGER NBL(NBELEM)
      ENDSEGMENT
C
C End of include STRAVJ
C
C***********************************************************************
C NOM         : STRAVL.INC
C DESCRIPTION :
C
C     Segment de travail en numérotation locale avec des segments
C     extensibles. 
C     
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 11/10/2017, version initiale
C HISTORIQUE : v1, 11/10/2017, création
C HISTORIQUE :
C HISTORIQUE :
C
C***********************************************************************
C
C Segment TRAVL
C Description :
C
*     NVZER sert à compter le nombre d'elements nul que l'on introduit
*     en vue de déclencher un nettoyage (voir topdif)
      SEGMENT TRAVL
      INTEGER NCINI,NCCOU,NCMAX,NVOCOU,NINDI,NINDJ
*     POINTEUR LMCANS.MELEMX
*     POINTEUR LIDXCA(NCMAX+1).MLENTI
*     POINTEUR LOKVOL(NCMAX).MLENTI,NVOCOU       
*     POINTEUR LQUALS(NLMAX).MLREEL,NLCOU       
*     POINTEUR LNQUAL(NCMAX).MLENTI
*     POINTEUR LINDI(NCMAX),NINDI
*     POINTEUR LINDJ(NCMAX),NINDJ
      INTEGER MCANS
      INTEGER IDXCA
      INTEGER OKVOL
      INTEGER QUALS
      INTEGER NQUAL
      INTEGER INDI
      INTEGER INDJ
*
*      POINTEUR IPBTL.MELEMX
      INTEGER PBTL
*      

      
**     INTEGER NBL(NBELEM)
      ENDSEGMENT
C
C End of include STRAVL
C
