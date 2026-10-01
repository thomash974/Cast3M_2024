c     declaration des parametres materiaux pour HELMHOLTZ
c     capacite   
      real*8  CAPAH(NB_HELM)
c     indicateur de blocage (1 si noeid bloque)
      logical BLOQH(NB_HELM)
c     valeur imposee au blocage
      real*8  DEPIH(NB_HELM)
c     valeur initiale
      real*8  INITH(NB_HELM)
c     indicateur de calcul lineaire 
      integer LINEH(NB_HELM)
c     coefficients de diffusion principaux orthotropes 
      real*8  DIFFH(NB_HELM,3)  
c     directions des diffusions principales 
      real*8  VECTH(NB_HELM,3,3)
c     Pi utile pour le calcul de LCARH 
      real*8 PIH
      parameter (PIH=3.1415926535d0)
c     longueur caracteristiques calculees lcar=(sqrt(2/Pi)*Diff/Capa))**(1/3)
      real*8  LCARH(NB_HELM,3)
c     matrice de taille associee aux diffusions non locales
      real*8  TAILH(NB_HELM,3,3)  
c     tableau des variables internes associees aux formulations de Helmholtz
      real*8  HELM0(NB_HELM,NB_VARI_PAR_HELM)
      real*8  HELM1(NB_HELM,NB_VARI_PAR_HELM)


