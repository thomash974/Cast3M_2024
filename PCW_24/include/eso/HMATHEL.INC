c     ********** parametres pour le non local **************************

c     NBVIA3D nombre de non locales actives transmises par c'modele'
c     INLVIA3D(l): pointeur sur les variables actives transmis par 'cmodele'
c     NMAT3 : nombre de parametres du materiaux support 
c     (renforts et decalage castem compris)

c     ** initialisation des tableaux pour Helmholtz ********************
      do i=1,NB_HELM
c       capacite   
        CAPAH(i)=1.d0
c       source
        DEPIH(i)=0.d0
c       blocage a la valeur initial
        BLOQH(i)=.false.
c       valeur initiale
        INITH(i)=0.d0
c       non lineaire par defaut
        LINEH(i)=0.d0
        do j=1,3
c           diffusions principales orthotrope 
            DIFFH(i,j) =0.d0
            do k=1,3 
c               directions des diffusions principales
                if(j.eq.k) then
                    VECTH(i,j,k)=1.d0
                else
                    VECTH(i,j,k)=0.d0
                end if
            end do 
        end do
      end do
        
c     ****** reperage des variables actives si on est en non local *****             
      if(istep.ne.0) then        
c        recuperation des parametres materiaux pour VARI non locales actives
c        print*,'Etape 1-1 ds charge_materiaux_helmholtz.h istep',istep      
         do i=1,NBVIA3D 
c           capacite
            CAPAH(i)=xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+1)
c            print*,'CAPAH(',i,')=',CAPAH(i)
c           blocage 
            if(xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+2).eq.1.) then            
                BLOQH(i)=.true.
            else
                BLOQH(i)=.false.
            end if
c            print*,'BLOQH(',i,')=',xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+2)
c     #      ,'->',BLOQH(i)
c           valeur imposee sur le blocage
            DEPIH(i)=xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+3)
c            print*,'DEPIH(',i,')=',DEPIH(i)
c           valeur initiale
            INITH(i)=xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+4)
c            print*,'INITH(',i,')=',INITH(i)
c           boucle sur les diffusions principales
c           valeur initiale
            LINEH(i)=int(xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+5))
c            print*,'INITH(',i,')=',INITH(i)
c           boucle sur les diffusions principales
            do j=1,3
c               coefficient de diffusion
                DIFFH(i,j)=xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+5+
     #           (j-1)*4+1)
c                print*,'DIFFH(',i,j,')=',DIFFH(i,j)
c               longueur caracteristique
                LCARH(i,j)=2.d0*(DIFFH(i,j)/CAPAH(i))**(1./2.)
c                print*,'LCARH(',i,j,')=',LCARH(i,j)
c               boucle sur les composantes du vecteur direction de la diffusion
                vnorm=0.d0
                do k=1,3
                    VECTH(i,j,k)=xmat(NMAT3+(i-1)*NB_PARA_PAR_HELM+5+
     #               (j-1)*4+1+k)
c                    print*,'VECTH(',i,j,k,')=',VECTH(i,j,k)
                    vnorm=vnorm+VECTH(i,j,k)**2
                end do
                vnorm=sqrt(vnorm)
                if(vnorm.eq.0.) then
c                 si la norme est nulle on suppose que les LCARH
c                 sont portees par le repere fixe
                  write(*,'(a22,1x,i2,a16,i2)')
     #            'Il manque la direction',j,' pour Helmholtz ',i
                  ierr1=1
                  return
                end if
c               matrice des tailles associees aux diffusions
                if(j.eq.1) then 
                    do k=1,3
                        do l=1,3
                            TAILH(i,k,l)=LCARH(i,j)*
     #                      (VECTH(i,j,k)*VECTH(i,j,l))
                        end do
                    end do
                else
                    do k=1,3
                        do l=1,3
                            TAILH(i,k,l)=TAILH(i,k,l)+
     #                      LCARH(i,j)*(VECTH(i,j,k)*VECTH(i,j,l))                  
                        end do
                    end do
                end if
c               fin de la construction de la matrice des tailles
            end do
C             print*,'Dans charge_materiaux_helmholtz.h (MATHEL.INC)'
C             do j=1,3
C                 do k=1,3
C                     print*,'TailH(',i,j,k,')=',tailh(i,j,k)
C                 end do
C             end do
c           fin de la boucle sur les diffusions principales    
         end do
c        fin de la boucle sur les variables de Helmholtz
      end if
c     fin du chargement des parametres non locaux





      
    
