program main
    use module_velfg_superkernel, only : velfg_superkernel
    integer :: global_id
    ! common /ocl/ global_id
    ! Declarations
    real, dimension(1:33341168) :: u_0
    real, dimension(1:33341168) :: v_0
    real, dimension(1:33341168) :: w_0
    real, dimension(1:32869291) :: f_1
    real, dimension(1:32869291) :: g_1
    real, dimension(1:32869291) :: h_1
    integer, parameter :: ST_STAGE_KERNEL_1 = 1 ! stage_kernel_1
    integer :: state_ptr
    integer, parameter :: niters = 5
    integer :: iter 
    ! Loops over stage calls
    state_ptr = ST_STAGE_KERNEL_1
    do iter = 1, niters
    print *, iter
    do global_id = 1, 33341168
      call velfg_superkernel(u_0, v_0, w_0, f_1, g_1, h_1,state_ptr)
    end do
    end do

end program main  
