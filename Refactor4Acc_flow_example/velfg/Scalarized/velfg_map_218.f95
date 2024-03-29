module singleton_module_velfg_map_218

contains

subroutine velfg_map_218_scal(dx1,cov1_i_j_k,cov1_ip1_j_k,cov2_i_j_k,cov2_i_jp1_k,cov3_i_j_k, &
      cov3_i_j_kp1,diu1_i_j_k,diu1_ip1_j_k,diu2_i_j_k,diu2_i_jp1_k,dy1,diu3_i_j_k,diu3_i_j_kp1, &
      dzn,dfu1_i_j_k,cov4_i_j_k,cov4_ip1_j_k,cov5_i_j_k,cov5_i_jp1_k,cov6_i_j_k,cov6_i_j_kp1, &
      diu4_i_j_k,diu4_ip1_j_k,diu5_i_j_k,diu5_i_jp1_k,diu6_i_j_k,diu6_i_j_kp1,dfv1_i_j_k, &
      cov7_i_j_k,cov7_ip1_j_k,cov8_i_j_k,cov8_i_jp1_k,cov9_i_j_k,cov9_i_j_kp1,diu7_i_j_k, &
      diu7_ip1_j_k,diu8_i_j_k,diu8_i_jp1_k,diu9_i_j_k,diu9_i_j_kp1,dzs,dfw1_i_j_k,f_i_j_k,g_i_j_k, &
      h_i_j_k)
 integer, parameter :: ip=600
 integer, parameter :: jp=600
 integer, parameter :: kp=90
 real, parameter :: vn=15.83 * 0.000001
 integer, parameter :: u0=0
 real :: covx1
 integer :: i
 integer :: j
 integer :: k
 real :: covy1
 real :: covz1
 real :: covc
 real :: df
 integer :: k_range
 integer :: j_range
 integer :: i_range
 integer :: k_rel
 integer :: j_rel
 integer :: i_rel
 real, dimension((-1):(ip+1)), intent(in) :: dx1
 real, intent(In) :: cov1_i_j_k
 real, intent(In) :: cov1_ip1_j_k
 real, intent(In) :: cov2_i_j_k
 real, intent(In) :: cov2_i_jp1_k
 real, intent(In) :: cov3_i_j_k
 real, intent(In) :: cov3_i_j_kp1
 real, intent(In) :: diu1_i_j_k
 real, intent(In) :: diu1_ip1_j_k
 real, intent(In) :: diu2_i_j_k
 real, intent(In) :: diu2_i_jp1_k
 real, dimension(0:(jp+1)), intent(in) :: dy1
 real, intent(In) :: diu3_i_j_k
 real, intent(In) :: diu3_i_j_kp1
 real, dimension((-1):(kp+2)), intent(in) :: dzn
 real, intent(In) :: cov4_i_j_k
 real, intent(In) :: cov4_ip1_j_k
 real, intent(In) :: cov5_i_j_k
 real, intent(In) :: cov5_i_jp1_k
 real, intent(In) :: cov6_i_j_k
 real, intent(In) :: cov6_i_j_kp1
 real, intent(In) :: diu4_i_j_k
 real, intent(In) :: diu4_ip1_j_k
 real, intent(In) :: diu5_i_j_k
 real, intent(In) :: diu5_i_jp1_k
 real, intent(In) :: diu6_i_j_k
 real, intent(In) :: diu6_i_j_kp1
 real, intent(In) :: cov7_i_j_k
 real, intent(In) :: cov7_ip1_j_k
 real, intent(In) :: cov8_i_j_k
 real, intent(In) :: cov8_i_jp1_k
 real, intent(In) :: cov9_i_j_k
 real, intent(In) :: cov9_i_j_kp1
 real, intent(In) :: diu7_i_j_k
 real, intent(In) :: diu7_ip1_j_k
 real, intent(In) :: diu8_i_j_k
 real, intent(In) :: diu8_i_jp1_k
 real, intent(In) :: diu9_i_j_k
 real, intent(In) :: diu9_i_j_kp1
 real, dimension((-1):(kp+2)), intent(in) :: dzs
 real, intent(Out) :: f_i_j_k
 real, intent(Out) :: g_i_j_k
 real, intent(Out) :: h_i_j_k
 real, intent(InOut) :: dfu1_i_j_k
 real, intent(InOut) :: dfv1_i_j_k
 real, intent(InOut) :: dfw1_i_j_k
 integer :: global_id
 call get_global_id(global_id,0)
 k_range = ((90 - 1) + 1)
 j_range = ((600 - 1) + 1)
 i_range = ((600 - 1) + 1)
 k_rel = (global_id / (j_range * i_range))
 k = (k_rel + 1)
 j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
 j = (j_rel + 1)
 i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
 i = (i_rel + 1)
 covx1 = (dx1(i + 1) * cov1_i_j_k + dx1(i) * cov1_ip1_j_k) / (dx1(i) + dx1(i + 1))
 covy1 = (cov2_i_j_k + cov2_i_jp1_k) / 2.
 covz1 = (cov3_i_j_k + cov3_i_j_kp1) / 2.
 covc = covx1 + covy1 + covz1
 dfu1_i_j_k = 2. * (-diu1_i_j_k + diu1_ip1_j_k) / (dx1(i) + dx1(i + 1)) + (-diu2_i_j_k +  &
      diu2_i_jp1_k) / dy1(j) + (-diu3_i_j_k + diu3_i_j_kp1) / dzn(k)
 df = vn * dfu1_i_j_k
 f_i_j_k = (-covc + df)
 covx1 = (cov4_i_j_k + cov4_ip1_j_k) / 2.
 covy1 = (dy1(j + 1) * cov5_i_j_k + dy1(j) * cov5_i_jp1_k) / (dy1(j) + dy1(j + 1))
 covz1 = (cov6_i_j_k + cov6_i_j_kp1) / 2.
 covc = covx1 + covy1 + covz1
 dfv1_i_j_k = (-diu4_i_j_k + diu4_ip1_j_k) / dx1(i) + 2. * (-diu5_i_j_k + diu5_i_jp1_k) / (dy1(j) +  &
      dy1(j + 1)) + (-diu6_i_j_k + diu6_i_j_kp1) / dzn(k)
 df = vn * dfv1_i_j_k
 g_i_j_k = (-covc + df)
 if ((k < (kp - 1))) then
 covx1 = (cov7_i_j_k + cov7_ip1_j_k) / 2.
 covy1 = (cov8_i_j_k + cov8_i_jp1_k) / 2.
 covz1 = (dzn(k + 1) * cov9_i_j_k + dzn(k) * cov9_i_j_kp1) / (dzn(k) + dzn(k + 1))
 covc = covx1 + covy1 + covz1
 dfw1_i_j_k = (-diu7_i_j_k + diu7_ip1_j_k) / dx1(i) + (-diu8_i_j_k + diu8_i_jp1_k) / dy1(j) +  &
      (-diu9_i_j_k + diu9_i_j_kp1) / dzs(k)
 df = vn * dfw1_i_j_k
 h_i_j_k = (-covc + df)
end if
end subroutine velfg_map_218_scal

end module singleton_module_velfg_map_218

