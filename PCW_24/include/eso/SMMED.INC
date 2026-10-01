C-INC SMMED
C     INCLUDE CONTENANT DES SEGMENTS UTILES AU FORMAT MED 4

C       MED_NAME_SIZE : voir CCMED.INC

C---- SEGMENT pour repertorier les objets nommes et leur nom
      SEGMENT SREPER
        INTEGER                   IREPER(NBENT)
        CHARACTER*(MED_NAME_SIZE) CREPER(NBENT)
C       NBENT   : Nombre d'objets
C       IREPER  : Pointeur des OBJETS ou ENTIER pour les 'POINT'
C       CREPER  : Noms des OBJETS
      ENDSEGMENT

      POINTEUR SREPE1.SREPER, SREPE2.SREPER, SREPE3.SREPER

C---- Donnees pour CHPOINT et MCHAML
      SEGMENT IFOCHA
        INTEGER                   NBENTI
        CHARACTER*(MED_NAME_SIZE) NOCHAP(nbmspo)
        INTEGER                   PNUMDT(nbmspo)
        INTEGER                   LICHAP(nbmspo)
        INTEGER                   LIMAIL(nbmspo)
        INTEGER                   ISUPOR(nbmspo,2)
        REAL*8                    XTEMPS(nbmspo)

C       NBENTI : nombre de champs a sortir reellement
C       nbmspo : dimensionnement du SEGMENT (superieur ou egal a NBENTI)
C       NOCHAP : nom du champ a produire
C       PNUMDT : numero de pas de temps (numdt)
C       LICHAP : liste de pointeurs MSOUPO ou MCHAML
C       LIMAIL : liste de pointeurs MELEME
C       ISUPOR : type de support  (0,1) : Non-Defini (CHPOINT)
C                                 (1,1) : NOEUDS
C                                 (2,1) : GRAVITE
C                                 (N,1) : Non-prevu encore
C                                 (.,2) : Pointeur sur un MINTE (SEGMENT d'INTEGRATION)
C       XTEMPS : Valeur du temps pour ce pas de temps
      ENDSEGMENT

      POINTEUR LISCHP.IFOCHA, LISCHA.IFOCHA

