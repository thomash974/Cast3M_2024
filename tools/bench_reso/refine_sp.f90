! Test numerique : une descente-remontee en simple precision (facteurs REAL*4)
! combinee au raffinement iteratif de MONDES atteint-elle le critere de MONDES
! (crite = crit*sqrt(xzprec*xszpre)) et en combien de passes ?
! Matrice : Laplacien 2D (nx*nx) + terme de masse, SPD, stockee en bande.
program refine_sp
  implicit none
  integer, parameter :: nx = 60, n = nx*nx, bw = nx
  real(8) :: a(0:bw, n), l(0:bw, n), x(n), b(n), r(n), u(n), d(n)
  real(4) :: ls(0:bw, n)
  real(8) :: lmin, xzprec, xszpre, crit, crite, crit2, shift
  integer :: i, j, k, it, ishift
  lmin = 8.d0*sin(acos(-1.d0)/(2.d0*(nx+1)))**2   ! plus petite valeur propre du Laplacien 2D
  xzprec = epsilon(1.d0); xszpre = real(epsilon(1.0))
  do ishift = 1, 4
    shift = 10.d0**(-(ishift-1)*2)       ! conditionnement croissant (valeur propre min ~ shift)
    a = 0.d0
    do i = 1, n
      a(0,i) = 4.d0 - lmin + shift
      if (mod(i,nx) /= 1) a(1,i) = -1.d0     ! lien (i,i-1)
      if (i > nx) a(bw,i) = -1.d0            ! lien (i,i-nx)
    end do
    ! LDLt en bande : l(0,i)=D(i), l(k,i)=L(i,i-k)
    l = a
    do i = 1, n
      do k = 1, min(bw, i-1)
        l(k,i) = l(k,i)
      end do
    end do
    call cholband(l, n, bw)
    ls = real(l, 4)
    call random_number(b); b = b - 0.5d0
    crit = maxval(abs(b)); crite = crit*sqrt(xzprec*xszpre)
    u = 0.d0; r = b
    do it = 1, 30
      call solve_sp(ls, n, bw, r, x)
      u = u + x
      call matvec(a, n, bw, u, r); r = b - r
      crit2 = maxval(abs(r))
      if (crit2 <= crite) exit
    end do
    print '(A,ES8.1,A,I3,A,ES9.2)', ' decalage=', shift, '  passes simple precision=', it, '  residu final=', crit2
    ! reference : double precision, 1 passe
    call solve_dp(l, n, bw, b, x)
    call matvec(a, n, bw, x, r); r = b - r
    print '(A,ES9.2)', '    double precision, 1 passe, residu=', maxval(abs(r))
  end do
contains
  subroutine cholband(l, n, bw)
    integer :: n, bw
    real(8) :: l(0:bw,n)
    integer :: i, j, k, m
    real(8) :: s
    ! Cholesky LLt en bande (diag dans l(0,:)), conserve la sortie sous forme L
    do i = 1, n
      do j = max(1,i-bw), i
        s = l_get(l, i, j)
        do m = max(1, i-bw, j-bw), j-1
          s = s - l_get(l,i,m)*l_get(l,j,m)
        end do
        if (i == j) then
          l(0,i) = sqrt(s)
        else
          call l_set(l, i, j, s/l(0,j))
        end if
      end do
    end do
  end subroutine
  real(8) function l_get(l, i, j)
    real(8) :: l(0:bw,n); integer :: i, j
    l_get = l(i-j, i)
  end function
  subroutine l_set(l, i, j, v)
    real(8) :: l(0:bw,n), v; integer :: i, j
    l(i-j, i) = v
  end subroutine
  subroutine solve_sp(ls, n, bw, rhs, x)
    integer :: n, bw; real(4) :: ls(0:bw,n); real(8) :: rhs(n), x(n)
    real(4) :: y(n), s; integer :: i, m
    do i = 1, n
      s = real(rhs(i),4)
      do m = max(1,i-bw), i-1
        s = s - ls(i-m,i)*y(m)
      end do
      y(i) = s/ls(0,i)
    end do
    do i = n, 1, -1
      s = y(i)
      do m = i+1, min(n,i+bw)
        s = s - ls(m-i,m)*y(m)
      end do
      y(i) = s/ls(0,i)
    end do
    x = real(y,8)
  end subroutine
  subroutine solve_dp(l, n, bw, rhs, x)
    integer :: n, bw; real(8) :: l(0:bw,n), rhs(n), x(n)
    real(8) :: y(n), s; integer :: i, m
    do i = 1, n
      s = rhs(i)
      do m = max(1,i-bw), i-1
        s = s - l(i-m,i)*y(m)
      end do
      y(i) = s/l(0,i)
    end do
    do i = n, 1, -1
      s = y(i)
      do m = i+1, min(n,i+bw)
        s = s - l(m-i,m)*y(m)
      end do
      y(i) = s/l(0,i)
    end do
    x = y
  end subroutine
  subroutine matvec(a, n, bw, v, w)
    integer :: n, bw; real(8) :: a(0:bw,n), v(n), w(n); integer :: i, k
    w = a(0,:)*v
    do i = 1, n
      do k = 1, min(bw, i-1)
        w(i) = w(i) + a(k,i)*v(i-k)
        w(i-k) = w(i-k) + a(k,i)*v(i)
      end do
    end do
  end subroutine
end program
