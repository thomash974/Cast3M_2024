C  ----------------------------
C   Restitution/Sauvegarde HHO
C  ----------------------------
C-INC CCHHORS
C  ------------------------

      COMMON / CRSHHO / ISAUHO, IRESHO,
**     &                  MSQHHO, MCEHHO, MPFHHO, MPCHHO,
     &                  ISSQHO, ISCEHO, ISPFHO, ISPCHO

C Statut SAVE aux COMMONs pour garantir leur permanence :
      SAVE  / CRSHHO /

