module singleton_module_velfg_map_76

contains

subroutine velfg_map_76(dx1_0,dy1_0,dzn_0,dzs_0,u_s_0,v_s_0,w_s_0,cov1_1,cov2_1,cov3_1,cov4_1, &
      cov5_1,cov6_1,cov9_1,diu1_1,diu2_1,diu3_1,diu4_1,diu5_1,diu6_1,diu9_1,nou1_1,nou2_1,nou3_1, &
      nou4_1,nou5_1,nou6_1,nou9_1)
use singleton_module_velfg_map_76, only : velfg_map_76_scal
 implicit none
!      BEGIN ex-sub decls velfg_map_76_scal
 integer, parameter :: ip___velfg_map_76_scal=10
 integer, parameter :: jp___velfg_map_76_scal=10
 integer, parameter :: kp___velfg_map_76_scal=90
 integer, parameter :: u0___velfg_map_76_scal=0
 integer :: i_vel2___velfg_map_76_scal
 integer :: j_vel2___velfg_map_76_scal
 integer :: k_vel2___velfg_map_76_scal
 integer :: k_vel2_range___velfg_m___9606c486
 integer :: j_vel2_range___velfg_m___4b6e60e4
 integer :: i_vel2_range___velfg_m___ea66ec4a
 integer :: k_vel2_rel___velfg_map_76_scal
 integer :: j_vel2_rel___velfg_map_76_scal
 integer :: i_vel2_rel___velfg_map_76_scal
 integer :: global_id___velfg_map_76_scal
!      END ex-sub decls velfg_map_76_scal
 real, dimension(-1:11), intent(in) :: dx1_0
 real, dimension(0:11), intent(in) :: dy1_0
 real, dimension(-1:92), intent(in) :: dzn_0
 real, dimension(-1:92), intent(in) :: dzs_0
 real, dimension(1:5), intent(in) :: u_s_0
 real, dimension(1:5), intent(in) :: v_s_0
 real, dimension(1:4), intent(in) :: w_s_0
 real, intent(out) :: cov1_1
 real, intent(out) :: cov2_1
 real, intent(out) :: cov3_1
 real, intent(out) :: cov4_1
 real, intent(out) :: cov5_1
 real, intent(out) :: cov6_1
 real, intent(out) :: cov9_1
 real, intent(out) :: diu1_1
 real, intent(out) :: diu2_1
 real, intent(out) :: diu3_1
 real, intent(out) :: diu4_1
 real, intent(out) :: diu5_1
 real, intent(out) :: diu6_1
 real, intent(out) :: diu9_1
 real, intent(out) :: nou1_1
 real, intent(out) :: nou2_1
 real, intent(out) :: nou3_1
 real, intent(out) :: nou4_1
 real, intent(out) :: nou5_1
 real, intent(out) :: nou6_1
 real, intent(out) :: nou9_1
!    ! Temp vars
 real :: nou1___velfg_map_76
 real :: diu1___velfg_map_76
 real :: nou5___velfg_map_76
 real :: diu5___velfg_map_76
 real :: nou9___velfg_map_76
 real :: diu9___velfg_map_76
 real :: nou2___velfg_map_76
 real :: diu2___velfg_map_76
 real :: nou3___velfg_map_76
 real :: diu3___velfg_map_76
 real :: nou4___velfg_map_76
 real :: diu4___velfg_map_76
 real :: nou6___velfg_map_76
 real :: diu6___velfg_map_76
!    ! Call to the original scalarised subroutine
!      BEGIN inlined call to velfg_map_76_scal
 call get_global_id(global_id___velfg_map_76_scal,0)
 k_vel2_range___velfg_m___9606c486 = (((90 + 1) - 1) + 1)
 j_vel2_range___velfg_m___4b6e60e4 = ((10 - 1) + 1)
 i_vel2_range___velfg_m___ea66ec4a = ((10 - 1) + 1)
 k_vel2_rel___velfg_map_76_scal = (global_id___velfg_map_76_scal /  &
      (j_vel2_range___velfg_m___4b6e60e4 * i_vel2_range___velfg_m___ea66ec4a))
 k_vel2___velfg_map_76_scal = (k_vel2_rel___velfg_map_76_scal + 1)
 j_vel2_rel___velfg_map_76_scal = ((global_id___velfg_map_76_scal - (k_vel2_rel___velfg_map_76_scal  &
      * (j_vel2_range___velfg_m___4b6e60e4 * i_vel2_range___velfg_m___ea66ec4a))) /  &
      i_vel2_range___velfg_m___ea66ec4a)
 j_vel2___velfg_map_76_scal = (j_vel2_rel___velfg_map_76_scal + 1)
 i_vel2_rel___velfg_map_76_scal = ((global_id___velfg_map_76_scal - (k_vel2_rel___velfg_map_76_scal  &
      * (j_vel2_range___velfg_m___4b6e60e4 * i_vel2_range___velfg_m___ea66ec4a))) -  &
      (j_vel2_rel___velfg_map_76_scal * i_vel2_range___velfg_m___ea66ec4a))
 i_vel2___velfg_map_76_scal = (i_vel2_rel___velfg_map_76_scal + 1)
 if ((k_vel2___velfg_map_76_scal < kp___velfg_map_76_scal)) then
 nou1___velfg_map_76 = (u_s_0(3) + u_s_0(4)) / 2.
 diu1___velfg_map_76 = (-u_s_0(3) + u_s_0(4)) / dx1_0(i_vel2___velfg_map_76_scal)
 nou5___velfg_map_76 = (v_s_0(2) + v_s_0(5)) / 2.
 diu5___velfg_map_76 = (-v_s_0(2) + v_s_0(5)) / dy1_0(j_vel2___velfg_map_76_scal)
 nou9___velfg_map_76 = (w_s_0(1) + w_s_0(4)) / 2.
 diu9___velfg_map_76 = (-w_s_0(1) + w_s_0(4)) / dzn_0(k_vel2___velfg_map_76_scal)
 cov1_1 = nou1___velfg_map_76 * diu1___velfg_map_76
 cov5_1 = nou5___velfg_map_76 * diu5___velfg_map_76
 cov9_1 = nou9___velfg_map_76 * diu9___velfg_map_76
 end if
 if ((k_vel2___velfg_map_76_scal < kp___velfg_map_76_scal)) then
 nou2___velfg_map_76 = (dx1_0(i_vel2___velfg_map_76_scal + 1) * v_s_0(2) +  &
      dx1_0(i_vel2___velfg_map_76_scal) * v_s_0(3)) / (dx1_0(i_vel2___velfg_map_76_scal) +  &
      dx1_0(i_vel2___velfg_map_76_scal + 1))
 diu2___velfg_map_76 = 2. * (-u_s_0(2) + u_s_0(4)) / (dy1_0(j_vel2___velfg_map_76_scal - 1) +  &
      dy1_0(j_vel2___velfg_map_76_scal))
 cov2_1 = nou2___velfg_map_76 * diu2___velfg_map_76
 end if
 nou3___velfg_map_76 = (dx1_0(i_vel2___velfg_map_76_scal + 1) * w_s_0(1) +  &
      dx1_0(i_vel2___velfg_map_76_scal) * w_s_0(2)) / (dx1_0(i_vel2___velfg_map_76_scal) +  &
      dx1_0(i_vel2___velfg_map_76_scal + 1))
 diu3___velfg_map_76 = (-u_s_0(1) + u_s_0(4)) / dzs_0(k_vel2___velfg_map_76_scal - 1)
 cov3_1 = nou3___velfg_map_76 * diu3___velfg_map_76
 if ((k_vel2___velfg_map_76_scal < kp___velfg_map_76_scal)) then
 nou4___velfg_map_76 = (dy1_0(j_vel2___velfg_map_76_scal + 1) * u_s_0(3) +  &
      dy1_0(j_vel2___velfg_map_76_scal) * u_s_0(5)) / (dy1_0(j_vel2___velfg_map_76_scal) +  &
      dy1_0(j_vel2___velfg_map_76_scal + 1))
 diu4___velfg_map_76 = 2. * (-v_s_0(4) + v_s_0(5)) / (dx1_0(i_vel2___velfg_map_76_scal - 1) +  &
      dx1_0(i_vel2___velfg_map_76_scal))
 cov4_1 = (nou4___velfg_map_76 - u0___velfg_map_76_scal) * diu4___velfg_map_76
 end if
 nou6___velfg_map_76 = (dy1_0(j_vel2___velfg_map_76_scal + 1) * w_s_0(1) +  &
      dy1_0(j_vel2___velfg_map_76_scal) * w_s_0(3)) / (dy1_0(j_vel2___velfg_map_76_scal) +  &
      dy1_0(j_vel2___velfg_map_76_scal + 1))
 diu6___velfg_map_76 = (-v_s_0(1) + v_s_0(5)) / dzs_0(k_vel2___velfg_map_76_scal - 1)
 cov6_1 = nou6___velfg_map_76 * diu6___velfg_map_76
!      END inlined call to velfg_map_76_scal
 nou1_1 = nou1___velfg_map_76
 diu1_1 = diu1___velfg_map_76
 nou5_1 = nou5___velfg_map_76
 diu5_1 = diu5___velfg_map_76
 nou9_1 = nou9___velfg_map_76
 diu9_1 = diu9___velfg_map_76
 nou2_1 = nou2___velfg_map_76
 diu2_1 = diu2___velfg_map_76
 nou3_1 = nou3___velfg_map_76
 diu3_1 = diu3___velfg_map_76
 nou4_1 = nou4___velfg_map_76
 diu4_1 = diu4___velfg_map_76
 nou6_1 = nou6___velfg_map_76
 diu6_1 = diu6___velfg_map_76
end subroutine velfg_map_76

end module singleton_module_velfg_map_76

