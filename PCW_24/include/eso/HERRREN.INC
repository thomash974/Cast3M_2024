             if(ierr_renfort.eq.1) then
                 print*,'Erreur 1 endo_renfort ds fluendo3d'
                 print*,'Renfort numero:',i
                 do j=0,9
                    print*,'var0(',ivari+j,')=',var0(ivari+j)
                 end do
                 print*,'variable pour renfort3d'
                 print*,'direction'
                 do j=1,3
                   print*,'vecr(',i,j,')=',vecr(i,j)
                 end do
                 print*,'coeff_nlr(i) av renfort',var0(ivari+3)
                 print*,istep,NB_RENF,i,epstf33,epsr0(i),
     #           epsrf(i),eplr0(i),eplrf(i),yor(i),syr(i),sigre0(i),
     #           sigref(i),hplr(i),tor(i),ekr(i),skr(i),ATRR(i),khir(i),
     #           gamr(i),sprec(i),teta1,teta2,dt,ppas,theta,eprm0(i),
     #           eprmf(i),ttaref(i),rhor(i),mu_r0(i),fl3d,errr,xnr(i),
     #           xmuthr(i),eprk0(i),eprkf(i),tokr(i),yksyr(i),
     #           plast_seule,epspmf33,spre0(i),
     #           spref(i),epst033,depsa(i),epleq0(i),epleqf(i),
     #           epsmf(i),epsm0(i),sigr_nl(i),coeff_nlr(i),eper0(i),
     #           epart(i),eparv(i),hypo_nl(i),plr_iso,log_H_RENF(i),
     #           garder,Pb_nl(i),travail_fissure
                 print*,'variables pour endo_renfort'
                 print*,sigref(i),eplrf(i),syr(i),sur(i),
     #           epsrf(i),epu(i),hplr(i),yor(i),wpr(i),longr(i),
     #           damrt0(i),damrtf(i),damrt1(i),damrt2(i),damrc0(i),
     #           damrcf(i),refrf(i),eplrt(i),eplrc(i),plr_iso,
     #           diffr0(i),diffrf(i),yor(i),deqr(i),Hintr(i),
     #           grad_sigr(i),tauie(i),taur(i),dami0(i),damif(i),
     #           epsmf(i),eplr0(i),sigre0(i),log_H_RENF(i),epsm0(i),
     #           epsr0(i),depsa(i),Et0(i),Etf(i),Hs0(i),Hsf(i),sigrf(i),
     #           spref(i),epart(i),eparv(i),source_nl(i),coeff_nlr(i),
     #           taui0(i),tauif(i),coeff_nli(i),eprkf(i),
     #           eprmf(i),hypo_nl(i),istep,err1,garder,
     #           endo_interface_explicit
                 print*,'coeff_nlr(i)',coeff_nlr(i)
                 print*,'coeff_nli(i)',coeff_nli(i)               
                 ierr1=1
                 return
              end if 