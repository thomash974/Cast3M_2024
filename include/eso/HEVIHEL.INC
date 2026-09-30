c   ecriture de variables interne de la formulation d helmholt numero ivari 
c   ivari numero de la variable interne objet d helmholtz
c   helm (ivari,1) sous classe de varible interne associe par helmholtz à ivari   
        do ii=1,NB_VARI_PAR_HELM
          varf(NVAR3+(NL-1)*NB_VARI_PAR_HELM+ii)=Helm1(NL,ii)
C           write(*,'(I4,2(1x,e10.3))') NVAR3+(NL-1)*NB_VARI_PAR_HELM+ii,
C      #    var0(NVAR3+(NL-1)*NB_VARI_PAR_HELM+ii),
C      #    varf(NVAR3+(NL-1)*NB_VARI_PAR_HELM+ii)
        end do