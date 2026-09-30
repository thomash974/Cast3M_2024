c*************************************************************************
c        Appel au modele de fibre3d ROMAIN (fibre = parametre de fluendo a suivre...idvis cfluendo )

        if(ifibre.eq.1) then    
         
         do i=1,3
            do j=1,3
            dir3(j)=vwpl33(j,i)
            end do
C             call tail1d(longf(i),t33,n33,xe3d,NBNMAX3D,NBNB3D,
C      #      idimb3d,dir3,Mjacob,Mnoeuds,NBRENF,NBNLISO,NBNLUNI,
C      #      METHODNL,DHI,DHU,VU,err1)  
              call tail1d(longf(i),dir3,Method_N,XE3D,NBNMAX3D,
     #        NBNB3D,IDIMB3D,Method_H,LcH,err1)
         end do
         
         rmax1=int(log(4*longf(1)/Lf)/log(2.d0)+1)
         rmax2=int(log(4*longf(2)/Lf)/log(2.d0)+1)  
         rmax3=int(log(4*longf(3)/Lf)/log(2.d0)+1)    
c        rmax=int(max(rmax1,rmax2,rmax3))    
         
c        print*,rmax,"rmax",longr(1),longr(2),longr(3)      

         sfib0(1)=var0(NVAR1+1)
         sfib0(2)=var0(NVAR1+2)
         sfib0(3)=var0(NVAR1+3)
         sfib0(4)=var0(NVAR1+4)
         sfib0(5)=var0(NVAR1+5)
         sfib0(6)=var0(NVAR1+6)
         wmax0(1)=var0(NVAR1+7)
         wmax0(2)=var0(NVAR1+8)
         wmax0(3)=var0(NVAR1+9)
         wmoy0(1)=var0(NVAR1+10)
         wmoy0(2)=var0(NVAR1+11)
         wmoy0(3)=var0(NVAR1+12)
         etw0(1)=var0(NVAR1+13)
         etw0(2)=var0(NVAR1+14)
         etw0(3)=var0(NVAR1+15)         
         nc0(1)=var0(NVAR1+16)
         nc0(2)=var0(NVAR1+17)
         nc0(3)=var0(NVAR1+18)
         wpl30(1)=var0(NVAR1+19)
         wpl30(2)=var0(NVAR1+20)
         wpl30(3)=var0(NVAR1+21)
         rigf0(1)=var0(NVAR1+22)
         rigf0(2)=var0(NVAR1+23)
         rigf0(3)=var0(NVAR1+24)
         wferm(1)=var0(NVAR1+25)
         wferm(2)=var0(NVAR1+26)
         wferm(3)=var0(NVAR1+27)
         iloc(1)=int(var0(NVAR1+28))
         iloc(2)=int(var0(NVAR1+29))
         iloc(3)=int(var0(NVAR1+30))
         sigdec(1)=var0(NVAR1+31)
         sigdec(2)=var0(NVAR1+32)
         sigdec(3)=var0(NVAR1+33)
         wpsig(1)=var0(NVAR1+34)
         wpsig(2)=var0(NVAR1+35)
         wpsig(3)=var0(NVAR1+36)
         wmiloc(1)=var0(NVAR1+37)
         wmiloc(2)=var0(NVAR1+38)
         wmiloc(3)=var0(NVAR1+39)
         sigmaxt(1)=var0(NVAR1+40)
         sigmaxt(2)=var0(NVAR1+41)
         sigmaxt(3)=var0(NVAR1+42)
         wmaxd0(1)=var0(NVAR1+43)
         wmaxd0(2)=var0(NVAR1+44)
         wmaxd0(3)=var0(NVAR1+45)
         phimoy(1)=var0(NVAR1+46)
         phimoy(2)=var0(NVAR1+47)
         phimoy(3)=var0(NVAR1+48)
         cvar(1)=var0(NVAR1+49)
         cvar(2)=var0(NVAR1+50)
         cvar(3)=var0(NVAR1+51)
         wplmax(1)=var0(NVAR1+52)
         wplmax(2)=var0(NVAR1+53)
         wplmax(3)=var0(NVAR1+54)
       
         call fibs3d(Df,Lf,lech,mwf,rtec,rhof,eof,vf1,vf2,gft00,
     #cokf1,cokf2,cowp1,cowp2,cofp,cow03,cowf,mink1,maxk1,mink2,
     #maxk2,minwp1,maxwp1,minwp2,maxwp2,minfp,maxfp,minw03,maxw03,
     #minwf,maxwf,sfib0,wplt6,wmax,wmoy,etw,ncf,sigfr,wpltx6,longf,
     #nc0,wmoy0,etw0,wpl30,rigf0,wmax0,vw3,rmax1,rmax2,rmax3,phimoy,
     #wferm,sigdec,iloc,wpsig,wmiloc,sigmaxt,vecw33,sfib,wmaxd,
     #wmaxd0,epstf6,Ef,fuf,young,xmt,dtiso,ept00,rt00,cvar,wplmax)
        
c      print*,"sortie"
c      on sauve les vari ds les varf
c      on stocke les sfib avant de leur appliquer l endommagement
c      sfib affiche est donc une contrainte effective
         varf(NVAR1+1)=sfib(1)
         varf(NVAR1+2)=sfib(2)
         varf(NVAR1+3)=sfib(3)
         varf(NVAR1+4)=sfib(4)
         varf(NVAR1+5)=sfib(5)
         varf(NVAR1+6)=sfib(6)
         varf(NVAR1+7)=wmax(1)
         varf(NVAR1+8)=wmax(2)
         varf(NVAR1+9)=wmax(3)
         varf(NVAR1+10)=wmoy(1)
         varf(NVAR1+11)=wmoy(2)
         varf(NVAR1+12)=wmoy(3)
         varf(NVAR1+13)=etw(1)
         varf(NVAR1+14)=etw(2)
         varf(NVAR1+15)=etw(3)
         varf(NVAR1+16)=ncf(1)
         varf(NVAR1+17)=ncf(2)
         varf(NVAR1+18)=ncf(3)
         varf(NVAR1+19)=vw3(1)
         varf(NVAR1+20)=vw3(2)
         varf(NVAR1+21)=vw3(3)
         varf(NVAR1+22)=rigf0(1)
         varf(NVAR1+23)=rigf0(2)
         varf(NVAR1+24)=rigf0(3)
         varf(NVAR1+25)=wferm(1)
         varf(NVAR1+26)=wferm(2)
         varf(NVAR1+27)=wferm(3)
         varf(NVAR1+28)=iloc(1)
         varf(NVAR1+29)=iloc(2)
         varf(NVAR1+30)=iloc(3)
         varf(NVAR1+31)=sigdec(1)
         varf(NVAR1+32)=sigdec(2)
         varf(NVAR1+33)=sigdec(3)
         varf(NVAR1+34)=wpsig(1)
         varf(NVAR1+35)=wpsig(2)
         varf(NVAR1+36)=wpsig(3)
         varf(NVAR1+37)=wmiloc(1)
         varf(NVAR1+38)=wmiloc(2)
         varf(NVAR1+39)=wmiloc(3)
         varf(NVAR1+40)=sigmaxt(1)
         varf(NVAR1+41)=sigmaxt(2)
         varf(NVAR1+42)=sigmaxt(3)
         varf(NVAR1+43)=wmaxd(1)
         varf(NVAR1+44)=wmaxd(2)
         varf(NVAR1+45)=wmaxd(3)
         varf(NVAR1+46)=phimoy(1)
         varf(NVAR1+47)=phimoy(2)
         varf(NVAR1+48)=phimoy(3)
         varf(NVAR1+49)=cvar(1)
         varf(NVAR1+50)=cvar(2)
         varf(NVAR1+51)=cvar(3)
         varf(NVAR1+52)=wplmax(1)
         varf(NVAR1+53)=wplmax(2)
         varf(NVAR1+54)=wplmax(3)
         
         
         do i=1,3
C          if(wmax(i).lt.wmax0(i)) then
C          wplx3(i)=wmax0(i)
C          else
c          substitution de l ouverture de fissure maxi pour le calcul des endommagement
c          par la valeur issue de la presence des fibres
           wplx3(i)=wmaxd(i)
c         end if
         end do

        end if 
c    fin appel au programme fibres romain
c***********************************************************************
