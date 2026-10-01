C***********************************************************************
C NOM         : CCMATOP.INC
C DESCRIPTION : Variables globales (COMMON) pour le mailleur topologique
C
C      
C     Voir aussi l'include TMATOP1.INC pour l'include définissant les
C     segments et pour la bibliographie du mailleur topologique.
C     
C     CPZ1 : paramètres du mailleur
C
C     IMOMET : façon de faire la moyenne de la métrique
C              0 = arithmétique ;
C              1 = géométrique (pour les tenseurs, plusieurs définitions
C                  possibles) pour l'instant seule l'isotrope est dispo 
C                  pas l'anisotrope
C     
C     CPZ2 : statistiques
C     JPARCO : nombre d'entités du maillage parcourues (noeuds, arêtes,
C              faces, éléments)
C     JEXPLO : nombre de topologies explorées
C     JCHANG : nombre de topologies changées
C     JNASCM : nombre de fois où les topologies candidates étaient trop
C              nombreuses 
C
C LANGAGE     : ESOPE
C AUTEUR      : Stéphane GOUNAND (CEA/DEN/DM2S/SEMT/LTA)
C               mél : gounand@semt2.smts.cea.fr
C***********************************************************************
C VERSION    : v1, 04/10/2017, version initiale
C HISTORIQUE : v1, 04/10/2017, création
C HISTORIQUE :     08/04/2020, ajout de IMOMET, changement de l'include
C HISTORIQUE :
C
C***********************************************************************
C
C
      COMMON /CPZ1/ XDENS,XVTOL,QTOL,IMPR,IVERI,ISGADJ,IALGO,IAJNO,
     >      INCMA,ISTMA,IMET,IMOMET
      COMMON /CPZ2/ JPARCO,JEXPLO,JCHANG,JNASCM
      save /cpz1/,/cpz2/
C
C End of include 
C


