module module_jacobi3d_superkernel

contains

   subroutine stencil_0(u, v0)

      integer, parameter :: nx = 300
      integer, parameter :: ny = 300
      integer, parameter :: nz = 300

      real, parameter :: c = 0.1

      integer :: i
      integer :: j
      integer :: k
      integer :: i_range
      integer :: j_range
      integer :: k_range
      integer :: i_rel
      integer :: j_rel
      integer :: k_rel

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: u
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v0

      integer :: global_id
      call get_global_id(global_id, 0)

      k_range = ((nz - 1) + 1)
      j_range = ((ny - 1) + 1)
      i_range = ((nx - 1) + 1)
      k_rel = (global_id/(j_range*i_range))
      k = (k_rel + 1)
      j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
      j = (j_rel + 1)
      i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
      i = (i_rel + 1)

      v0(i, j, k) = (u(i - 1, j, k) + u(i + 1, j, k) + u(i, j - 1, k) + u(i, j + 1, k) + u(i, j, k - 1) + u(i, j, k + 1))*c

   end subroutine stencil_0

   subroutine stencil_1(v0, v1)

      integer, parameter :: nx = 300
      integer, parameter :: ny = 300
      integer, parameter :: nz = 300

      real, parameter :: c = 0.1

      integer :: i
      integer :: j
      integer :: k
      integer :: i_range
      integer :: j_range
      integer :: k_range
      integer :: i_rel
      integer :: j_rel
      integer :: k_rel

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v0
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v1

      integer :: global_id
      call get_global_id(global_id, 0)

      k_range = ((nz - 1) + 1)
      j_range = ((ny - 1) + 1)
      i_range = ((nx - 1) + 1)
      k_rel = (global_id/(j_range*i_range))
      k = (k_rel + 1)
      j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
      j = (j_rel + 1)
      i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
      i = (i_rel + 1)

      v1(i, j, k) = (v0(i - 1, j, k) + v0(i + 1, j, k) + v0(i, j - 1, k) + v0(i, j + 1, k) + v0(i, j, k - 1) + v0(i, j, k + 1))*c

   end subroutine stencil_1

   subroutine stencil_2(v1, v2)

      integer, parameter :: nx = 300
      integer, parameter :: ny = 300
      integer, parameter :: nz = 300

      real, parameter :: c = 0.1

      integer :: i
      integer :: j
      integer :: k
      integer :: i_range
      integer :: j_range
      integer :: k_range
      integer :: i_rel
      integer :: j_rel
      integer :: k_rel

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v1
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v2

      integer :: global_id
      call get_global_id(global_id, 0)

      k_range = ((nz - 1) + 1)
      j_range = ((ny - 1) + 1)
      i_range = ((nx - 1) + 1)
      k_rel = (global_id/(j_range*i_range))
      k = (k_rel + 1)
      j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
      j = (j_rel + 1)
      i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
      i = (i_rel + 1)

      v2(i, j, k) = (v1(i - 1, j, k) + v1(i + 1, j, k) + v1(i, j - 1, k) + v1(i, j + 1, k) + v1(i, j, k - 1) + v1(i, j, k + 1))*c

   end subroutine stencil_2

   subroutine stencil_3(v2, un)

      integer, parameter :: nx = 300
      integer, parameter :: ny = 300
      integer, parameter :: nz = 300

      real, parameter :: c = 0.1

      integer :: i
      integer :: j
      integer :: k
      integer :: i_range
      integer :: j_range
      integer :: k_range
      integer :: i_rel
      integer :: j_rel
      integer :: k_rel

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v2
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: un

      integer :: global_id
      call get_global_id(global_id, 0)

      k_range = ((nz - 1) + 1)
      j_range = ((ny - 1) + 1)
      i_range = ((nx - 1) + 1)
      k_rel = (global_id/(j_range*i_range))
      k = (k_rel + 1)
      j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
      j = (j_rel + 1)
      i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
      i = (i_rel + 1)

      un(i, j, k) = (v2(i - 1, j, k) + v2(i + 1, j, k) + v2(i, j - 1, k) + v2(i, j + 1, k) + v2(i, j, k - 1) + v2(i, j, k + 1))*c

   end subroutine stencil_3

  !  subroutine stencil_4(v3, v4)

  !     integer, parameter :: nx = 300
  !     integer, parameter :: ny = 300
  !     integer, parameter :: nz = 300

  !     real, parameter :: c = 0.1

  !     integer :: i
  !     integer :: j
  !     integer :: k
  !     integer :: i_range
  !     integer :: j_range
  !     integer :: k_range
  !     integer :: i_rel
  !     integer :: j_rel
  !     integer :: k_rel

  !     real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v3
  !     real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v4

  !     integer :: global_id
  !     call get_global_id(global_id, 0)

  !     k_range = ((nz - 1) + 1)
  !     j_range = ((ny - 1) + 1)
  !     i_range = ((nx - 1) + 1)
  !     k_rel = (global_id/(j_range*i_range))
  !     k = (k_rel + 1)
  !     j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
  !     j = (j_rel + 1)
  !     i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
  !     i = (i_rel + 1)

  !     v4(i, j, k) = (v3(i - 1, j, k) + v3(i + 1, j, k) + v3(i, j - 1, k) + v3(i, j + 1, k) + v3(i, j, k - 1) + v3(i, j, k + 1))*c

  !  end subroutine stencil_4

  !  subroutine stencil_5(v4, un)

  !     integer, parameter :: nx = 300
  !     integer, parameter :: ny = 300
  !     integer, parameter :: nz = 300

  !     real, parameter :: c = 0.1

  !     integer :: i
  !     integer :: j
  !     integer :: k
  !     integer :: i_range
  !     integer :: j_range
  !     integer :: k_range
  !     integer :: i_rel
  !     integer :: j_rel
  !     integer :: k_rel

  !     real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v4
  !     real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: un

  !     integer :: global_id
  !     call get_global_id(global_id, 0)

  !     k_range = ((nz - 1) + 1)
  !     j_range = ((ny - 1) + 1)
  !     i_range = ((nx - 1) + 1)
  !     k_rel = (global_id/(j_range*i_range))
  !     k = (k_rel + 1)
  !     j_rel = ((global_id - (k_rel*(j_range*i_range)))/i_range)
  !     j = (j_rel + 1)
  !     i_rel = ((global_id - (k_rel*(j_range*i_range))) - (j_rel*i_range))
  !     i = (i_rel + 1)

  !     un(i, j, k) = (v4(i - 1, j, k) + v4(i + 1, j, k) + v4(i, j - 1, k) + v4(i, j + 1, k) + v4(i, j, k - 1) + v4(i, j, k + 1))*c

  !  end subroutine stencil_5

   subroutine jacobi3d_superkernel(u, un, state_ptr)
      integer, parameter :: nx = 300
      integer, parameter :: ny = 300
      integer, parameter :: nz = 300

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: u
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: un

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v0
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v1
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v2
      ! real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v3
      ! real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v4

      integer :: state
      integer :: state_ptr
      integer, parameter :: ST_STENCIL_0 = 0
      integer, parameter :: ST_STENCIL_1 = 1
      integer, parameter :: ST_STENCIL_2 = 2
      integer, parameter :: ST_STENCIL_3 = 3
      integer, parameter :: ST_STENCIL_4 = 4
      integer, parameter :: ST_STENCIL_5 = 5

      state = state_ptr ! state
      select case (state)
      case (ST_STENCIL_0)
         call stencil_0(u, v0)
      case (ST_STENCIL_1)
         call stencil_1(v0, v1)
      case (ST_STENCIL_2)
         call stencil_2(v1, v2)
      case (ST_STENCIL_3)
         call stencil_3(v2, un)
      ! case (ST_STENCIL_4)
      !    call stencil_4(v3, v4)
      ! case (ST_STENCIL_5)
      !    call stencil_5(v4, un)
      end select

   end subroutine jacobi3d_superkernel
end module module_jacobi3d_superkernel
