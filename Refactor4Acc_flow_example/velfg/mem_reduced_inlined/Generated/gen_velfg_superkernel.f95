program main
use module_velfg_superkernel, only : velfg_superkernel
      implicit none
    integer :: global_id
!    ! common /ocl/ global_id
!    ! Declarations
    real, dimension(1:13248) :: u_0
    real, dimension(1:13248) :: v_0
    real, dimension(1:13248) :: w_0
    real, dimension(1:11011) :: f_1
    real, dimension(1:11011) :: g_1
    real, dimension(1:11011) :: h_1
      integer, parameter :: st_stage_kernel_1=1
    integer :: state_ptr
      integer, parameter :: niters=5
    integer :: iter
!    ! Loops over stage calls
    state_ptr = st_stage_kernel_1
    do iter = 1, niters
    print *, iter
    do global_id = 1, 13248
      call velfg_superkernel(u_0, v_0, w_0, f_1, g_1, h_1,state_ptr)
    end do
    end do
end program main  
