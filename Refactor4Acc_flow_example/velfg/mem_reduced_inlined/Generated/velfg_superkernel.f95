module singleton_module_velfg_superkernel

contains

subroutine velfg_superkernel(dx1_0,dy1_0,dzn_0,dzs_0,u_0,v_0,w_0,f_1,g_1,h_1,state_ptr)
 implicit none
 real, dimension(1:13248), intent(in) :: u_0
 real, dimension(1:13248), intent(in) :: v_0
 real, dimension(1:13248), intent(in) :: w_0
 real, dimension(1:11011), intent(out) :: f_1
 real, dimension(1:11011), intent(out) :: g_1
 real, dimension(1:11011), intent(out) :: h_1
 real, dimension(-1:11), intent(in) :: dx1_0
 real, dimension(0:11), intent(in) :: dy1_0
 real, dimension(-1:92), intent(in) :: dzn_0
 real, dimension(-1:92), intent(in) :: dzs_0
 integer, parameter :: st_stage_kernel_1=1
 integer :: state
 integer, intent(In) :: state_ptr
 state = state_ptr 
!  SUPERKERNEL BODY
 select case(state)
 case (st_stage_kernel_1)
 call stage_kernel_1(dx1_0, dy1_0, dzn_0, dzs_0, u_0, v_0, w_0, f_1, g_1, h_1)
 end select
end subroutine velfg_superkernel

end module singleton_module_velfg_superkernel

