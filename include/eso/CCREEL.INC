C     -INC CCREEL
C
      REAL*8      XZERO,XPI,XGRAND,XPETIT,XZPREC
      REAL*4      XSGRAN,XSPETI,XSZPRE
      COMMON/REEL/XGRAND,XPETIT,XZPREC
      COMMON/REE4/XSGRAN,XSPETI,XSZPRE
      COMMON/INTX/IGRAND,IPETIT
      save /reel/,/ree4/,/intx/
      PARAMETER(XZERO=0.D0)
      PARAMETER(XPI  =3.141592653589793D0)
C
C             CE COMMON CONTIENT QUELQUES CONSTANTE
C
C                 XZERO=0.D0
C                 XPI  =3.14159..............
C                 XGRAND= NOMBRE GRAND EN VALEUR ABSOLUE real*8
C                 XPETIT= NOMBRE PETIT EN VALEUR ABSOLUE real*8
C                 xzprec precision machine real*8 relative a 1
C
C                 XSGRAN= NOMBRE GRAND EN VALEUR ABSOLUE real*4
C                 XSPETI= NOMBRE PETIT EN VALEUR ABSOLUE real*4
C                 xszpre precision machine real*4 relative a 1

C     La MACRO A_EGALE_B permet de tester l'egalite de deux REAL*8
C     A et B en tenant compte de la precision relative XZPREC et 
C     absolue XPETIT
      MACRO , A_EGALE_B(A,B)=(ABS((A)-(B)) .LE.
     2                MAX(ABS(A)*XZPREC,ABS(B)*XZPREC,XPETIT/XZPREC))
