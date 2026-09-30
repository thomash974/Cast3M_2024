c     ***** declaration parametres materiaux des renforts repartis *****
      logical plr_iso
c     vrai si les renforts ont un ecrouissage isotrope
c     faux si l ecrouissage des aciers est cinematique        
      parameter (plr_iso=.false.)

c     parametres des  renforts pour chaque direction
      real*8 rhor(NB_RENF),deqr(NB_RENF),yor(NB_RENF),syr(NB_RENF),rhov
      real*8 taur(NB_RENF),vecr(NB_RENF,3),Hintr(NB_RENF)
      real*8 lsr(NB_RENF),lfr(NB_RENF),longr(NB_RENF),lcr(NB_RENF)
      real*8 hplr(NB_RENF),tor(NB_RENF),ekr(NB_RENF),skr(NB_RENF)
      real*8 ATRR(NB_RENF),khir(NB_RENF),gamr(NB_RENF),sprec(NB_RENF)
      real*8 ttaref(NB_RENF),xnr(NB_RENF),xmuthr(NB_RENF)
      real*8 refr0(NB_RENF),refr1(NB_RENF),refrf(NB_RENF)
      real*8 eprp1(NB_RENF)
c     gradient de la contrainte dans le renfort
      real*8 grad_sigr(NB_RENF),coeff_nlr(NB_RENF),coeff_nli(NB_RENF)      
c     variable pour l endommagement des renforts      
      real*8 sur(NB_RENF),epu(NB_RENF),wpr(NB_RENF)
      real*8 damrt0(NB_RENF),damrt1(NB_RENF),damrt2(NB_RENF)
      real*8 damrtf(NB_RENF)
      real*8 damrc0(NB_RENF),damrcf(NB_RENF)
c     contrainte de cisaillement et endommagement interface renforts
      real*8 tauie(NB_RENF),dami0(NB_RENF),damif(NB_RENF)
      real*8 taui0(NB_RENF),tauif(NB_RENF)
      real*8 epsm0(NB_RENF),epsmf(NB_RENF)         
c     nombre de renfort effectivement consideres pour un calcul
c     on doit avoir NRENF00<=NB_RENF    
      integer NRENF00
c     predicteur pour les renforts non locaux
      real*8 Et0(NB_RENF),Etf(NB_RENF)
      real*8 Hs0(NB_RENF),Hsf(NB_RENF) 
      real*8 diffr0(NB_RENF),diffrf(NB_RENF)  

c     *** declaration variables internes pour les renforts *************
      real*8 epsr0(NB_RENF),epsrf(NB_RENF),eplr0(NB_RENF),eplrf(NB_RENF)
      real*8 sigr0(NB_RENF),sigrf(NB_RENF),spre0(NB_RENF),spref(NB_RENF)
      real*8 sigr_nl(NB_RENF),sigr_nl0(NB_RENF)
      real*8 eprm0(NB_RENF),eprmf(NB_RENF),depsa(NB_RENF)
      real*8 source_nl(NB_RENF),eper0(NB_RENF)
      real*8 epart(NB_RENF),eparv(NB_RENF)     
      real*8 sigrfissp(NB_RENF,3,3),mu_r0(NB_RENF),eperf(NB_RENF) 
      real*8 eprk0(NB_RENF),eprkf(NB_RENF),tokr(NB_RENF),yksyr(NB_RENF)
      real*8 epleq0(NB_RENF),epleqf(NB_RENF)
      real*8 eplrt(NB_RENF),eplrc(NB_RENF)
c     contraintes effective dans les renforts
      real*8 sigref(NB_RENF),sigre0(NB_RENF)
c     hypothese ecoulement
      real*8 Pb_nl(NB_RENF),hypo_nl(NB_RENF) 
c     resultante des effets de renforts traversant les fissures
      real*8 sigrd33(3,3),sigrd6(6),sigrd33p(3,3),sigrd6p(6) 
c     declaration supplementaires pour le traitement non local des renforts
      logical log_H_RENF(NB_RENF)
      integer Num_H_RENF(NB_RENF)
      
      
      
    
      
