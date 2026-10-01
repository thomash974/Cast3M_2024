c     nombre de renforts anisotropes reparties (min 0, max 6)
      NRENF00=INT(MAX(XMAT(NMAT1),0.D0) )

c     ********** recuperation des paramtres des renforts repartis ******
    
c      print*,'fluendo3d : nbre de renforts repartis:',NRENF00     
      if(NRENF00.gt.0) then
         if(NRENF00.gt.NB_RENF) then
c           nre maxi de renforts : NB_RENF
c           nbre de parametres par renforts : NB_PARA_PAR_RENF         
            print*,'Nbre de renforts repartie insuffisant dans '
            print*,'./nombre_renforts.h(NBRREN.INC)'          
            print*,'Nombre min de renforts necessaire:',NRENF00
            ierr1=1
            return
         end if            
         do i=1,NRENF00  
c            taux de renforts elestoplastiques dans 3 direction  
             rhor(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+1)
c            diametre equivalent des renforts
             deqr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+2)              
c            module d Young des renforts passifs
             yor(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+3) 
c            limite elastique des renforts
             syr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+4)
c            cisaillement maxi renfort matrice
             taur(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+5)
c            direction projete axe base fixe 1             
             vecr(i,1)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+6)
c            direction projete axe base fixe 1             
             vecr(i,2)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+7)
c            direction projete axe base fixe 1             
             vecr(i,3)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+8)
c            verif / normalisation vecteur direction             
             vnorm=vecr(i,1)**2+vecr(i,2)**2+vecr(i,3)**2
             vnorm=sqrt(vnorm)             
             if(vnorm.eq.0.) then
c                il manque la direction du renfort             
                 print*,'Donner la direction du renfort:', i
                 ierr1=1
                 return
             else if (vnorm.ne.1.) then
c                normalisation du vecteur direction             
                 do j=1,3
                      vecr(i,j)=vecr(i,j)/vnorm
                 end do
             end if 
c             do j=1,3
c             print*,'fluendo3d verc(',i,j,')=',vecr(i,j) 
c             end do 
c            module d ecrouissage cinematique des armatures
             hplr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+9)
c            temps caracteristique de fluage/relaxation             
             tor(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+10)
c            deformation caracteristique de fluage relaxation             
             ekr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+11)
c            contrainte caracteristique de la loi de relaxation/ fluage             
             skr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+12)
c            energie d'activation de reference pour la relaxation             
             ATRR(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+13)
c            coeff de couplage thermo-mecanique pour la relaxation             
             gamr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+14)
c            coeff de non lineraite mecanique de la relaxation             
             khir(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+15)
c            precontrainte imposee             
             sprec(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+16)
c            precontrainte fin de pas             
             spref(i)=sprec(i)             
c            temperature de reference armature
             ttaref(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+17) 
c            exposant de loi d'activation thermique
             xnr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+18)
c            taux de chargement a partir duquel l activation therm depend du chargement
             xmuthr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+19)
c            temps caracteristique de kelvin pour les renforts             
             tokr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+20)
c            rapport Ekelvin/Eelastique pour les renforts             
             yksyr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+21)   
c            limite ultime en traction du renfort
             sur(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+22)
             if(sur(i).eq.0.) then
               sur(i)=1.1*syr(i)
             end if
c            deformation ultime du renfort (debut de localisation)
             epu(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+23)
             if(epu(i).eq.0.) then
                epu(i)=0.07
             end if
c            energy de rupture du renfort
             wpr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+24) 
             if(wpr(i).eq.0.) then
              wpr(i)=1.d0
             end if
c            module de cisaillement de l interface du renfort
             Hintr(i)=xmat(NMAT2+NB_PARA_PAR_RENF*(i-1)+25)             
c            le renfort est il traite en non local ?
c            pour les renforts le non local est sur SHR(i) de numero: 
             ivarnl=NVAR2+(i-1)*NB_VARI_PAR_RENF+26
             call exhmtz(istep,NBVIA3D,INLVIA3D,NB_HELM,
     #       ivarnl,log_H_RENF(i),Num_H_RENF(i)) 
         end do 
      else
c        on teste tout de même l existence de non local renfort
         do i=NRENF00+1,NB_RENF
             ivarnl=NVAR2+(i-1)*NB_VARI_PAR_RENF+26
             call exhmtz(istep,NBVIA3D,INLVIA3D,NB_HELM,
     #       ivarnl,log_H_RENF(i),Num_H_RENF(i)) 
             if(log_H_RENF(i)) then
                print*,'Dans charge_materiaux_renforts.h (MATREN.INC)'
                print*,'Helmholtz pour un renfort et pas de renfort'
                ierr1=1
                return
             end if
         end do
      end if   
