c romain      
c      ************recup parametres pour fibre3d ******* 
c     indicateur presence de fibres ( romain  )     
      ifibre=int(xmat(NMAT1-2))
      
      
      if(ifibre.eq.1) then

c      print*,"debut recuperation fibres romain",NBRFLU3D,
c     #xmat(nbelas3d+92),xmat(nbelas3d+93),xmat(nbelas3d+94)
       Df=xmat(NMAT1+1)
       Lf=xmat(NMAT1+2)
       Hf=xmat(NMAT1+3)
       Tmax=xmat(NMAT1+4)
       Td=xmat(NMAT1+5)
       sk=xmat(NMAT1+6)
       fabo=xmat(NMAT1+7)
       alphaec=xmat(NMAT1+8)
       m0f=xmat(NMAT1+9)
       L0f=xmat(NMAT1+10)
       muf=xmat(NMAT1+11)
       Ef=xmat(NMAT1+12)
       lech=xmat(NMAT1+13)
       mwf=xmat(NMAT1+14)
       fuf=xmat(NMAT1+15)
       rtec=xmat(NMAT1+16)
       rhof=xmat(NMAT1+17)
       eof(1)=xmat(NMAT1+18)
       eof(2)=xmat(NMAT1+19)
       eof(3)=xmat(NMAT1+20)
       vf1(1)=xmat(NMAT1+21)
       vf1(2)=xmat(NMAT1+22)
       vf1(3)=xmat(NMAT1+23)
       vf2(1)=xmat(NMAT1+24)
       vf2(2)=xmat(NMAT1+25)
       vf2(3)=xmat(NMAT1+26)
       fyf=xmat(NMAT1+27)

c      modif de la resistance a la traction      
c      Rt00=Rtec*(lech/longr(i))**(1/mw)    
c      print*,NMAT1+26,nbelas3d,NBRFLU3D,nbparr
 
       do i=1,10   
        cokf1(i)=xmat(NMAT1+NB_PARA_FIBRE_U+i) 
        cokf2(i)=xmat(NMAT1+NB_PARA_FIBRE_U+10+i) 
        cowp1(i)=xmat(NMAT1+NB_PARA_FIBRE_U+20+i) 
        cowp2(i)=xmat(NMAT1+NB_PARA_FIBRE_U+30+i) 
        cofp(i)=xmat(NMAT1+NB_PARA_FIBRE_U+40+i)  
        cow03(i)=xmat(NMAT1+NB_PARA_FIBRE_U+50+i) 
        cowf(i)=xmat(NMAT1+NB_PARA_FIBRE_U+60+i) 
       end do
       
       mink1=xmat(NMAT1+NB_PARA_FIBRE_U+71)
       maxk1=xmat(NMAT1+NB_PARA_FIBRE_U+72)
       mink2=xmat(NMAT1+NB_PARA_FIBRE_U+73)
       maxk2=xmat(NMAT1+NB_PARA_FIBRE_U+74)
       minwp1=xmat(NMAT1+NB_PARA_FIBRE_U+75)
       maxwp1=xmat(NMAT1+NB_PARA_FIBRE_U+76)
       minwp2=xmat(NMAT1+NB_PARA_FIBRE_U+77)
       maxwp2=xmat(NMAT1+NB_PARA_FIBRE_U+78)
       minfp=xmat(NMAT1+NB_PARA_FIBRE_U+79)
       maxfp=xmat(NMAT1+NB_PARA_FIBRE_U+80)
       minw03=xmat(NMAT1+NB_PARA_FIBRE_U+81)
       maxw03=xmat(NMAT1+NB_PARA_FIBRE_U+82)
       minwf=xmat(NMAT1+NB_PARA_FIBRE_U+83)
       maxwf=xmat(NMAT1+NB_PARA_FIBRE_U+84)
      end if

c       print*,"fin recuperation fibres romain"          
c fin recuperation fibres romain 