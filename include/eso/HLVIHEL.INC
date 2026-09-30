c   lecture de variables interne de la formulation d helmholt numero ivari    
        do ii=1,NB_VARI_PAR_HELM
          Helm0(NL,ii)=var0(NVAR3+(NL-1)*NB_VARI_PAR_HELM+ii)
c         copie dans valeur finale pour le cas ou rien n evolue
          Helm1(NL,ii)=Helm0(NL,ii)
C           write(*,'(2(A7,I2,I2,A2,e10.3))')
C      #                   ' Helm0(',nl,ii,')=',helm0(nl,ii),
C      #                   ' Helm1(',nl,ii,')=',helm1(nl,ii)
        end do