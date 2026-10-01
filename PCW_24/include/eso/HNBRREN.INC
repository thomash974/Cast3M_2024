c     nombre de renforts et de parametres pour les renforts
      integer NB_RENF,NB_PARA_PAR_RENF,NB_VARI_PAR_RENF
c     nombre renforts
      parameter(NB_RENF=5)
c     nombre parametres par renfort
      parameter(NB_PARA_PAR_RENF=25)
c     nombre de variables internes par renfort repartis (cf idvar4)
      parameter (NB_VARI_PAR_RENF=26) 
c     nombre total de parametres pour les renforts
      integer NB_PARA_RENF
      parameter(NB_PARA_RENF=NB_RENF*NB_PARA_PAR_RENF)
c     nombre totale de variables internes pour les renforts
      integer NB_VARI_RENF
      parameter(NB_VARI_RENF=NB_RENF*NB_VARI_PAR_RENF)
