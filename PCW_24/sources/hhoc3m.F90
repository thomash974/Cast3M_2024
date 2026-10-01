subroutine hhoc3m(charfct, charhho, &
                           tabint,maxint, &
                           tabflo,maxflo, &
                           iret,charerr)

#ifdef HHO
  use castem_hho         !!  use castem_hho_elements

  implicit none

  integer(kind=8), intent(out) :: iret
  character(len=*),intent(out) :: charerr

  integer(kind=8), intent(in)  :: maxint, maxflo
  integer(kind=8), dimension(1:maxint), intent(inout) :: tabint
  real(kind=8),    dimension(1:maxflo), intent(inout) :: tabflo
  character(len=*),intent(in)  :: charfct, charhho

  integer(kind=8), save :: initlib = 0, longlib = 0
  character(len=512), save :: charlib = " "

  integer(kind=8) :: ncl, nll
  integer(kind=8) :: ib1, i_err
  character(len=256) :: charfcl

  type(ExitStatus)         :: es
  type(ElementDescription) :: ed
  type(ElementGeometry)    :: eg
  type(ElementFunctions)   :: ef
  type(GenericFunctions)   :: gf

  iret = 0
  charerr = "__NO_ERROR__ "
  i_err = 0

!! First initialisations (only at the first time)
!! These initialisations could also be done by C3M.
  IF (initlib == 0) THEN
!-dbg    write(6,*) 'HHOC3M LIBHHO INIT',longlib

!    CALL GET_ENVIRONMENT_VARIABLE( NAME="BIT", LENGTH=ncl )
!    IF (ncl < 1 .OR. ncl > 512) THEN
!      charerr = "Variable BIT not defined "
!      iret = 5
!      return
!    END IF
!    CALL GET_ENVIRONMENT_VARIABLE( NAME="BIT", VALUE=charfcl )
!    IF (charfcl(1:ncl) /= "64") THEN
!      charerr = "Only libHHO 64BIT version is available "
!      iret = 5
!      return
!    END IF

    CALL GET_ENVIRONMENT_VARIABLE( NAME="CASTEM_HHO_ROOT", LENGTH=nll)
    IF (nll < 1 .OR. nll > (512-37)) THEN
      charerr = "Variable CASTEM_HHO_ROOT not defined "
      iret = 5
      return
    END IF
    CALL GET_ENVIRONMENT_VARIABLE( NAME="CASTEM_HHO_ROOT", VALUE=charlib)

    CALL GET_ENVIRONMENT_VARIABLE( NAME="CASTEM_PLATEFORME", LENGTH=ncl )
    IF (ncl < 1 .OR. ncl > 256) THEN
      charerr = "Variable CASTEM_PLATEFORME not defined "
      iret = 5
      return
    END IF
    CALL GET_ENVIRONMENT_VARIABLE( NAME="CASTEM_PLATEFORME", VALUE=charfcl )
    IF ( INDEX(charfcl,"WINDOWS") /= 0 ) THEN
      charlib = charlib(1:nll)//"\lib\libmechhcanoCast3MElements.dll"
    ELSE IF( INDEX(charfcl,"Linux") /= 0 ) THEN
      charlib = charlib(1:nll)//"/lib/libmechhcanoCast3MElements.so"
    ELSE IF( INDEX(charfcl,"MAC") /= 0 ) THEN
      charlib = charlib(1:nll)//"/lib/libmechhcanoCast3MElements.dylib"
    ELSE
      charerr = "variable CASTEM_PLATEFORME ill-defined "
      iret = 5
      return
    ENDIF
    longlib = LEN_TRIM(charlib)
  ELSE
!-dbg    write(6,*) 'HHOC3M LIBHHO',initlib,longlib
  ENDIF
!! END of 1st initialisations

  initlib = initlib + 1
  nll = longlib
!-dbg  write(6,*) "CHARLIB=", charlib(1:nll), "="

  ncl = LEN_TRIM(charhho)
!-dbg  write(6,*) 'HHOC3M',maxint,maxflo
!-dbg  write(6,*) '      ',charhho(1:ncl)

!-------------------------------------------------------------------------------
  if (charfct(1:4) == 'INIT') then
!-------------------------------------------------------------------------------
!!    write(6,*) 'HHOC3M - INIT',tabint(1),tabint(2),tabint(4)
    charfcl = charhho(1:ncl)//"_get_element_description"
    ncl = LEN_TRIM(charfcl)
    es = get_element_description(ed,charlib(1:nll),charfcl(1:ncl))
    iret = es%exitstatus
    if (iret /= 0) then
!!      write(6,*) es%exitstatus
      charerr = get_error_message(es)
      return
    end if
!! Quelques verifications pour la mise au point :
    i_err = 0
    if (tabint( 1) /= ed % dim_eucli) i_err = i_err + 1
    if (tabint( 3) /= ed % dir_dof_face_unknown) i_err = i_err + 10
    if (tabint( 5) /= ed % dir_dof_cell_unknown) i_err = i_err + 100
    if (tabint( 6) /= ed % num_vertices) i_err = i_err + 1000
    IF (i_err > 0) THEN
      charerr = "ELEMENT DESCRIPTION inconsistent"
      iret = 5
      RETURN
    END IF
    tabint( 1) = ed % dim_eucli
    tabint( 3) = ed % dir_dof_face_unknown
    tabint( 5) = ed % dir_dof_cell_unknown
    tabint( 6) = ed % num_vertices
    tabint( 7) = ed % num_faces
    tabint( 8) = ed % num_quadrature_points
    tabint( 9) = ed % dim_field
    tabint(10) = ed % dir_dof_gradient
    tabint(11) = ed % dim_space_element
    tabint(12) = ed % dim_face_block
    tabint(13) = ed % dim_cell_block
    tabint(14) = ed % dim_MB
    tabint(15) = ed % dim_MB_matrices
    tabint(16) = ed % dim_MSTAB
    tabint(17) = ed % dim_MKCC
    tabint(18) = ed % dim_MKCF
    tabint(19) = ed % dim_MVC
    tabint(20+1:20+ed % num_faces) = ed % num_vertices_per_face(1:ed%num_faces)
!! Quelques verifications supplementaires :
    IF (ed % dim_eucli == 2) THEN
      DO ib1 = 1, ed % num_vertices
        if (tabint(20+ib1) /= 2) then
          write(6,*) 'INIT 2D - tabint(20+',ib1,') bizarre !'
          i_err = i_err + 1
        end if
      END DO
    ELSE IF (ed % dim_eucli == 1) THEN
      if (tabint(20+1) /= 1) then
        write(6,*) 'INIT 1D - tabint(20+1) bizarre !'
        i_err = i_err + 1
      end if
    END IF
    IF (i_err > 0) THEN
      charerr = "ELEMENT NumVertices par Face incorrect "
      iret = 21
      RETURN
    END IF

!-------------------------------------------------------------------------------
  else if (charfct(1:4) == 'INTG') then
!-------------------------------------------------------------------------------
    charfcl = charhho(1:ncl)//"_get_element_functions"
    ncl = LEN_TRIM(charfcl)
    es = get_element_functions(ef,charlib(1:nll),charfcl(1:ncl))
    iret = es%exitstatus
    if (iret /= 0) then
!!      write(6,*) es%exitstatus
      charerr = get_error_message(es)
      return
    end if
    eg % connectivity = tabint(tabint(1):tabint(2))
    eg % vertices_coordinates = tabflo(tabint(3):tabint(4))
    do ib1 = 1, tabint(5)
      ncl = tabint(6)+ib1
      es = get_gauss_weight(ef, eg, tabflo(ncl:ncl), ib1)
      iret = es%exitstatus
      if (iret /= 0) then
        charerr = get_error_message(es)
        return
      end if
!!      write(6,*) "gauss_weight_data: ", ib1, tabflo(ncl)
    end do

!-------------------------------------------------------------------------------
  else if (charfct(1:4) == 'BHHO') then
!-------------------------------------------------------------------------------
    charfcl = charhho(1:ncl)//"_get_element_functions"
    ncl = LEN_TRIM(charfcl)
    es = get_element_functions(ef,charlib(1:nll),charfcl(1:ncl))
    iret = es%exitstatus
    if (iret /= 0) then
      charerr = get_error_message(es)
      return
    end if
    eg % connectivity = tabint(tabint(1):tabint(2))
    eg % vertices_coordinates = tabflo(tabint(3):tabint(4))
    es = get_gradient_operator(ef, eg, tabflo(tabint(5):tabint(6)), tabint(7))
    iret = es%exitstatus
    if (iret /= 0) then
      charerr = get_error_message(es)
      return
    end if

!-------------------------------------------------------------------------------
  else if (charfct(1:4) == 'SHHO') then
!-------------------------------------------------------------------------------
    charfcl = charhho(1:ncl)//"_get_element_functions"
    ncl = LEN_TRIM(charfcl)
    es = get_element_functions(ef,charlib(1:nll),charfcl(1:ncl))
    iret = es%exitstatus
    if (iret /= 0) then
      charerr = get_error_message(es)
      return
    end if
    eg % connectivity = tabint(tabint(1):tabint(2))
    eg % vertices_coordinates = tabflo(tabint(3):tabint(4))
    es = get_stabilization_operator(ef, eg, tabflo(tabint(5):tabint(6)))
    iret = es%exitstatus
    if (iret /= 0) then
      charerr = get_error_message(es)
      return
    end if

!-------------------------------------------------------------------------------
  else
!-------------------------------------------------------------------------------
    iret = 5
    charerr(1:37) = "HHOC3M interface: Keyword incorrect "
  end if

#else

    integer(kind=8), intent(out) :: iret
    character(len=*),intent(out) :: charerr

    charerr = "Cast3M a ete construit sans le support pour HHO"
    iret = 5

#endif /* HHO */

end subroutine hhoc3m
