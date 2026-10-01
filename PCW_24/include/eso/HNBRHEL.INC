c     Declaration commune pour les varibales de Helmholtz
c     Nombre de variable détat principales
      integer NB_HELM
c     Nombre de parametres par variable d etat
      integer NB_PARA_PAR_HELM
c     Nombre de variable internes par avriables d etat
      integer NB_VARI_PAR_HELM
c     nombre de variables non locales ISO et UNI      
      parameter (NB_HELM=8) 
c     nombre de parametre par variable iso et par variable uni
      parameter (NB_PARA_PAR_HELM=17)     
c     nombre de vari par vari ISO (cf idvar4) (99 maxi)
      parameter (NB_VARI_PAR_HELM=10)
c     calcul du nombre maximum de variables de helmholtz
      integer NB_PARA_HELM,NB_VARI_HELM
c     nombre total de parametres non locaux (cf idmatr.eso)
      parameter (NB_PARA_HELM=NB_HELM*NB_PARA_PAR_HELM)
c     nombre de vari pour le non local
      parameter (NB_VARI_HELM=NB_HELM*NB_VARI_PAR_HELM)
c     tableau des numeros des variables internes non locales actives par Helmholtz
      integer INLVIA3D(NB_HELM) 
c     nombre de Helmholtz actives
      integer NBVIA3D
