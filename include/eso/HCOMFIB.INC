c     debut romain calcul des contraintes endommages dans les fibres  
c     reconstruction du tenseur des contraintesde fibres avec endo dans la base fixe
      if(ifibre.eq.1) then    
c       deformation elastique
        call x6x33(epstf6,epse133)
c       base des fissures      
        do i=1,3
            vecw(1)=vecw33(1,i)
            vecw(2)=vecw33(2,i)
            vecw(3)=vecw33(3,i)
c           deformation normale direction des fissures
            epse13(i)=sum(matmul(vecw,epse133)*vecw)
c           contribution des fibres zone non endommagee
            sigfe(i)=(1.d0-dt3(i))*rhof*
     #      max(min(Ef*epse13(i)*cos(phimoy(i)*pi/180.d0)**2,
     #      fuf*cos(phimoy(i)*pi/180.d0)**2),-fuf)
        end do
c       combinaison avec les fibres dans les fissures      
        do i=1,3
            do j=1,3
                if(i.eq.j) then 
                    sigfp33(i,j)=sigfr(i)*dt3(i)+sigfe(i)
                else
                    sigfp33(i,j)=0.d0
                end if
            end do
        end do    
        sigfx33=matmul(matmul(vecw33,sigfp33),transpose(vecw33))
        call x33x6(sigfx33,sfib)     
c       print*,wplx3(3),"dt3(3) fluendo",dt3(3)     
      end if
c     fin romain fibres  