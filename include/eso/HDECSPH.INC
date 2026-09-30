      integer npos        
      parameter (PI=3.141592653589793D0,ang1=pi)
      real*8 thet1(npos+1),gam1(npos+1),x(npos+1,npos+1)
      real*8 y(npos+1,npos+1),z(npos+1,npos+1),tri(npos,2*npos-2,3,3)
      real*8 s(npos,2*npos-2),xg(npos,2*npos-2),yg(npos,2*npos-2)
      real*8 zg(npos,2*npos-2)