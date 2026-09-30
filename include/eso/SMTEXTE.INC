C=======================================================================
C     OBJET DE TYPE 'TEXT','E   '
      SEGMENT, MTEXTE
        CHARACTER MTEXT*(LOCHAI)
        INTEGER   NCART
        INTEGER   MTRADC

C         MTEXT  : Chaine contenant le TEXTE a interpreter
C         NCART  : Longueur de la chaine contenue dans MTEXT
C         MTRADC : Pointeur vers SEGMENT MTRADU
      ENDSEGMENT
      POINTEUR MTEXT1.MTEXTE, MTEXT2.MTEXTE

      SEGMENT, MTRADU
        INTEGER  MTRAD(0)

C        MTRAD : Tableau d'entier extensible contenant la position dans la pile
C                de l'objet decode
      ENDSEGMENT
C=======================================================================
