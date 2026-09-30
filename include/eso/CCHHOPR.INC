C  ------------------------
C   PReconditionnement HHO
C  ------------------------
C-INC CCHHOPR   <-- Ne pas oublier d'inclure CCHHOPA avant
C  ------------------------

C- MSQHHO : Maillage global des faces = squelette
C- MCEHHO : Maillage global des cellules hho
C- MPFHHO : Maillage global des Points supports des Faces
C- MPCHHO : Maillage global des Points supports des Cellules (barycentre)

C- NUFHHO : NomBre Utilise de type de Faces HHO (> 0 en cas de HHO)
C- NFAHHO : Nombre total de Faces HHO (> 0 en cas de HHO)
C- NBFHHO : NomBre de Faces HHO par type de face (indices 1 a NFHMAX)
C-          Les faces etant :
C-             en 1D des POI1 (1 noeud) 
C-             en 2D des SEG2 (2 noeuds) 
C-             en 3D des polygones a N (>=3) sommets
C-          On utilise le nombre de sommets de face comme indice du tableau
C- NBFHHO(0) : toujours = 0 (pour le cumul)
C- MAFHHO : MAillage des Faces de type (i)
C- LOFHHO : Ordre de chaque face du type (i)

      COMMON / CPRHHO / IDIHHO, IFOHHO,
     &                  MSQHHO, MCEHHO, MPFHHO, MPCHHO,
     &                  NUFHHO, NFAHHO,
     &                  NUCHHO, NCEHHO,
     &                  NBFHHO(0:NFAMAX), MAFHHO(NFAMAX),
     &                  LOFHHO(NFAMAX),
     &                  NBCHHO(0:NCEMAX), MACHHO(NCEMAX),
     &                  NISFHO, NISCHO

      COMMON / CPLHHO / LIFHHO(LFAMAX), LICHHO(LCEMAX)

C Statut SAVE aux COMMONs pour garantir leur permanence :
      SAVE  / CPRHHO / , / CPLHHO /

