module module_hotspot3d_superkernel

contains

   subroutine stencil_0(tIn, pIn, v0)

      integer, parameter :: nx = 500
      integer, parameter :: ny = 500
      integer, parameter :: nz = 100

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: tIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: pIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v0

      real :: dx
      real :: dy
      real :: dz
      real :: cap
      real :: rx
      real :: ry
      real :: rz
      real :: t_chip
      real :: chip_height
      real :: chip_width
      real :: amb_temp
      real :: max_slope
      real :: dt
      real :: ce
      real :: cw
      real :: cn
      real :: cs
      real :: ct
      real :: cb
      real :: cc
      real :: stepDivCap
      integer :: global_id

      t_chip = 0.0005
      chip_height = 0.016
      chip_width = 0.016
      amb_temp = 80.0

      dx = chip_height/numRows
      dy = chip_width/numCols
      dz = t_chip/layers

      cap = 0.5*1.75e6*t_chip*dx*dy
      rx = dy/(2.0*100*t_chip*dx)
      ry = dx/(2.0*100*t_chip*dy)
      rz = dz/(100*dx*dy)

      max_slope = 3.0e6/(0.5*t_chip*1.75e6)
      dt = 0.001/max_slope

      stepDivCap = dt/cap
      ce = stepDivCap/rx
      cw = ce
      cn = stepDivCap/ry
      cs = cn
      ct = stepDivCap/rz
      ct = cb

      cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct)

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

      v0(i, j, k) = tIn(i, j, k)*cc + tIn(i - 1, j, k)*cn + tIn(i + 1, j, k)*cs + &
                    tIn(i, j, k + 1)*ce + tIn(i, j, k - 1)*cw + tIn(i, j + 1, k)*ct + &
                    tIn(i, j - 1, k)*cb + (dt/cap)*pIn(i, j, k) + ct*amb_temp

   end subroutine stencil_0

   subroutine stencil_1(v0, pIn, v1)

      integer, parameter :: nx = 500
      integer, parameter :: ny = 500
      integer, parameter :: nz = 100

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v0
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: pIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v1

      real :: dx
      real :: dy
      real :: dz
      real :: cap
      real :: rx
      real :: ry
      real :: rz
      real :: t_chip
      real :: chip_height
      real :: chip_width
      real :: amb_temp
      real :: max_slope
      real :: dt
      real :: ce
      real :: cw
      real :: cn
      real :: cs
      real :: ct
      real :: cb
      real :: cc
      real :: stepDivCap
      integer :: global_id

      t_chip = 0.0005
      chip_height = 0.016
      chip_width = 0.016
      amb_temp = 80.0

      dx = chip_height/numRows
      dy = chip_width/numCols
      dz = t_chip/layers

      cap = 0.5*1.75e6*t_chip*dx*dy
      rx = dy/(2.0*100*t_chip*dx)
      ry = dx/(2.0*100*t_chip*dy)
      rz = dz/(100*dx*dy)

      max_slope = 3.0e6/(0.5*t_chip*1.75e6)
      dt = 0.001/max_slope

      stepDivCap = dt/cap
      ce = stepDivCap/rx
      cw = ce
      cn = stepDivCap/ry
      cs = cn
      ct = stepDivCap/rz
      ct = cb

      cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct)

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

      v1(i, j, k) = v0(i, j, k)*cc + v0(i - 1, j, k)*cn + v0(i + 1, j, k)*cs + &
                    v0(i, j, k + 1)*ce + v0(i, j, k - 1)*cw + v0(i, j + 1, k)*ct + &
                    v0(i, j - 1, k)*cb + (dt/cap)*pIn(i, j, k) + ct*amb_temp

   end subroutine stencil_1

   subroutine stencil_2(v1, pIn, v2)

      integer, parameter :: nx = 500
      integer, parameter :: ny = 500
      integer, parameter :: nz = 100

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v1
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: pIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: v2

      real :: dx
      real :: dy
      real :: dz
      real :: cap
      real :: rx
      real :: ry
      real :: rz
      real :: t_chip
      real :: chip_height
      real :: chip_width
      real :: amb_temp
      real :: max_slope
      real :: dt
      real :: ce
      real :: cw
      real :: cn
      real :: cs
      real :: ct
      real :: cb
      real :: cc
      real :: stepDivCap
      integer :: global_id

      t_chip = 0.0005
      chip_height = 0.016
      chip_width = 0.016
      amb_temp = 80.0

      dx = chip_height/numRows
      dy = chip_width/numCols
      dz = t_chip/layers

      cap = 0.5*1.75e6*t_chip*dx*dy
      rx = dy/(2.0*100*t_chip*dx)
      ry = dx/(2.0*100*t_chip*dy)
      rz = dz/(100*dx*dy)

      max_slope = 3.0e6/(0.5*t_chip*1.75e6)
      dt = 0.001/max_slope

      stepDivCap = dt/cap
      ce = stepDivCap/rx
      cw = ce
      cn = stepDivCap/ry
      cs = cn
      ct = stepDivCap/rz
      ct = cb

      cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct)

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

      v2(i, j, k) = v1(i, j, k)*cc + v1(i - 1, j, k)*cn + v1(i + 1, j, k)*cs + &
                    v1(i, j, k + 1)*ce + v1(i, j, k - 1)*cw + v1(i, j + 1, k)*ct + &
                    v1(i, j - 1, k)*cb + (dt/cap)*pIn(i, j, k) + ct*amb_temp

   end subroutine stencil_2

   subroutine stencil_3(v2, pIn, tOut)

      integer, parameter :: nx = 500
      integer, parameter :: ny = 500
      integer, parameter :: nz = 100

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: v2
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: pIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: tOut

      real :: dx
      real :: dy
      real :: dz
      real :: cap
      real :: rx
      real :: ry
      real :: rz
      real :: t_chip
      real :: chip_height
      real :: chip_width
      real :: amb_temp
      real :: max_slope
      real :: dt
      real :: ce
      real :: cw
      real :: cn
      real :: cs
      real :: ct
      real :: cb
      real :: cc
      real :: stepDivCap
      integer :: global_id

      t_chip = 0.0005
      chip_height = 0.016
      chip_width = 0.016
      amb_temp = 80.0

      dx = chip_height/numRows
      dy = chip_width/numCols
      dz = t_chip/layers

      cap = 0.5*1.75e6*t_chip*dx*dy
      rx = dy/(2.0*100*t_chip*dx)
      ry = dx/(2.0*100*t_chip*dy)
      rz = dz/(100*dx*dy)

      max_slope = 3.0e6/(0.5*t_chip*1.75e6)
      dt = 0.001/max_slope

      stepDivCap = dt/cap
      ce = stepDivCap/rx
      cw = ce
      cn = stepDivCap/ry
      cs = cn
      ct = stepDivCap/rz
      ct = cb

      cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct)

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

      tOut(i, j, k) = v2(i, j, k)*cc + v2(i - 1, j, k)*cn + v2(i + 1, j, k)*cs + &
                      v2(i, j, k + 1)*ce + v2(i, j, k - 1)*cw + v2(i, j + 1, k)*ct + &
                      v2(i, j - 1, k)*cb + (dt/cap)*pIn(i, j, k) + ct*amb_temp

   end subroutine stencil_3

   subroutine hotspot3d_superkernel(tIn, pIn, tOut, state_ptr)
      integer, parameter :: nx = 500
      integer, parameter :: ny = 500
      integer, parameter :: nz = 100

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: tIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(In) :: pIn
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)), intent(Out) :: tOut

      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v0
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v1
      real, dimension(0:(nx + 1), 0:(ny + 1), 0:(nz + 1)) :: v2

      integer :: state
      integer :: state_ptr
      integer, parameter :: ST_STENCIL_0 = 0
      integer, parameter :: ST_STENCIL_1 = 1
      integer, parameter :: ST_STENCIL_2 = 2
      integer, parameter :: ST_STENCIL_3 = 3

      state = state_ptr ! state
      select case (state)
      case (ST_STENCIL_0)
         call stencil_0(tIn, pIn, v0)
      case (ST_STENCIL_1)
         call stencil_1(v0, pIn, v1)
      case (ST_STENCIL_2)
         call stencil_2(v1, pIn, v2)
      case (ST_STENCIL_3)
         call stencil_3(v2, pIn, tOut)
      end select

   end subroutine hotspot3d_superkernel
end module module_hotspot3d_superkernel
