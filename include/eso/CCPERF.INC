*     -INC CCPERF
*
*     Mesure des durees dans les blocs (PROCEDURES et BOUCLES)
*
      COMMON/CPERFO/ITPSPR,ITPSBO,IPTEMP
      save /cperfo/
C     Initialisation dans bdata.eso
C     ITPSPR : Pointeur sur ITPSBL pour les durees dans les PROCEDURES
C     ITPSBO : Pointeur sur ITPSBL pour les durees dans les BOUCLES
C     IPTEMP : Pointeur sur ITEMPS pour les temps par thread

      SEGMENT ITPSBL
        INTEGER      NIVCOU
        INTEGER      IPRONI(NIVMAX)
        INTEGER      NBAPRO(NBBLOC)
        INTEGER      TPSPRO(2,NBBLOC)
        INTEGER      DURPRO(2,NBBLOC)
C       LMNOM=24
        CHARACTER*24 CDPROC(NBBLOC)
C       NIVCOU      : Niveau courant (profondeur en terme de procedure)
C       NIVMAX      : Niveau maximum rencontre
C       IPRONI      : Place de la procedure dans les tableaux (NBAPRO, TPSPRO et DURPRO)
C       NBBLOC      : Nombre de blocs differents (PROCEDURES, BOUCLES, ...)
C       NBAPRO      : Nombre d'appel des procedure
C       TPSPRO(1,.) : Valeur du "temps elapsed" au debut du chronometrage des procedure
C             (2,.) : Valeur du "temps CPU"     au debut du chronometrage des procedure
C       DURPRO(1,.) : Duree Elapsed cumulee de la procedure ('Self')
C             (2,.) : Duree CPU     cumulee de la procedure ('Self')
C       CDPROC      : Nom des procedures
      ENDSEGMENT
