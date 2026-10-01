c declaration des variables fibres romain
      integer NB_PARA_FIBRE_U,ifibre
      parameter (PI=3.141592653589793D0,nparfib=111)
      real*8 eof(3),vf1(3),vf2(3),m0f,Lf,L0f,muf,lech,mwf
      real*8 cokf1(10),cokf2(10),cowp1(10),cowp2(10),cofp(10),cow03(10)
      real*8 cowf(10),mink1,maxk1,mink2,maxk2,minwp1,maxwp1
      real*8 minwp2,maxwp2,minw03,maxw03,minwf,maxwf,minfp,maxfp
      real*8 sfib0(6),sfib(6),wmax(3),wmoy(3),etw(3),ncf(3)
      real*8 dir3(3),wmoy0(3),etw0(3),wpl30(3),nc0(3),longf(3)
      real*8 rigf0(3),wmax0(3),vw3(3),wferm(3),sigdec(3)
      integer rmax,rmax1,rmax2,rmax3,iloc(3)
      real*8 sigmaxt(3),wpsig(3),wmiloc(3),sigfp33(3,3),vecw33(3,3)
      real*8 sigfx33(3,3),sigfr(3),phimoy(3),wmaxd(3),wmaxd0(3)
      real*8 vecw(3),epse13(3),epse133(3,3),sigfe(3),gfap(3),cvar(3)
      real*8 wplmax(3)      
c fin declaration romain fibres