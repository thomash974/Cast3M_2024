C  ---------------------
C   PARAMETRES pour HHO
C  ---------------------
C-INC CCHHOPA
C  ------------------------

C- Numero des Elements HHO dans la liste des elements du tableau NOMTP :
C- [Voir fichier BDATA/INIDATA lors du remplissage de NOMTP]
C- Ce numero est utilise dans les sousprogrammes NUMGEO et NUMMFR.
      INTEGER HHO_NUM_ELEMENT
      PARAMETER( HHO_NUM_ELEMENT = 281)

C- Numero de la Formulation HHO fourni suite a l'appel a NUMMFR :
C- [Voir fichier NUMMFR pour ce numero]
      INTEGER HHO_MFR_ELEMENT
      PARAMETER( HHO_MFR_ELEMENT = 89)

C- Nombre de donnees IVAMOD/TYMODE pour un modele HHO
      PARAMETER ( MTYHHO = 5 )

C- Nombre maximal de sommets/cotes pour un element HHO polygonal (2D)
      INTEGER HHO_MAX_EDGE
      PARAMETER ( HHO_MAX_EDGE = 20 )
C- Nombre maximal de sommets/cotes pour une face poygonale du polyedre (3D)
C- idem que HHO_MAX_EDGE

C- Nombre maximal de types de cellules differents :
C-   En 1D => 1
C             --> SEG2(2)
C-   En 2D => 2 + (HHO_MAX_EDGE-3+1)
C             --> TRI3(4) QUA4(8) POLY(32 & 3 a HHO_MAX_EDGE sommets)
C-   en 3D => 2 / Par la suite : + 2 + x
C             --> TET4(23) CUB8(14) / Par la suite : PRI6(16) PYR5(25) POLY3D(x)
      PARAMETER ( NC1MAX = 1 , NC2MAX = HHO_MAX_EDGE , NC3MAX = 2 )

C- NCEMAX = MAX(NC1MAX, NC2MAX, NC3MAX)
      PARAMETER ( NCEMAX = HHO_MAX_EDGE )

      PARAMETER ( IC1MAX = 0 ,
     &            IC2MAX = IC1MAX + NC1MAX ,
     &            IC3MAX = IC2MAX + NC2MAX )

      PARAMETER ( LCEMAX = NC1MAX + NC2MAX + NC3MAX )

C- Nombre maximal de types de faces differents :
C-   En 1D => 1 --> POI1(1)
C-   En 2D => 1 --> SEG2(2)
C-   En 3D => 2 --> TRI3(4) QUA4(8)  (pas de changement si on ajoute PRI6 et PYR5)
C- Par la suite POLY3D -> POLY(32 & 5 a HHO_MAX_EDGE sommets)
      PARAMETER ( NF1MAX = 1 , NF2MAX = 1 , NF3MAX = 2 )

C- NFAMAX = MAX(NF1MAX, NF2MAX, NF3MAX) -> on fige NFAMAX = HHO_MAX_EDGE
      PARAMETER ( NFAMAX = HHO_MAX_EDGE )

      PARAMETER ( IF1MAX = 0 ,
     &            IF2MAX = IF1MAX + NF1MAX ,
     &            IF3MAX = IF2MAX + NF2MAX )

      PARAMETER ( LFAMAX = NF1MAX + NF2MAX + NF3MAX )

