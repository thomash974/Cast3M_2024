c        chargement variables internes i        
         epsr0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+1)
         eper0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+2)
         eplr0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+3)
         sigre0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+4)
         eprm0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+5)
         mu_r0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+6)
         eprk0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+7)
         spre0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+8)
         eplrc(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+9)
         damrt0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+10)
         damrt1(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+11)
         damrt2(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+12)
c        la taille n est pas recharge depuis var0 au 1er pas car
c        elle n a pas encore ete passee de varf a var0             
         if(.not.ppas) then
          longr(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+13)
         end if             
         sigr0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+14)
         epleq0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+15) 
         damrc0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+16)
         eplrt(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+17)
         diffr0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+18)
         taui0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+19) 
         dami0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+20)
         if(ppas.and.((istep.eq.0).or.(istep.eq.1))) then
c          modules tg pris = module initiaux au premier pas local
c          et  la 1ere sous iteration non locale (istep=1)             
           Et0(i)=yor(i)
           Hs0(i)=Hintr(i)
           refr0(i)=1.0d0
         else
c          recuperation  modules de l iteration precedente
c          ou du pas precedent converge si istep=1            
           Et0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+21)
           Hs0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+22)
c          fonction de refermeture de fissure du renfort                
           refr0(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+23)
         end if
c        hypothese sur deformations anelastiques             
         epart(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+24)
         eparv(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+25)
         sigr_nl(i)=var0(NVAR2+(i-1)*NB_VARI_PAR_RENF+26)