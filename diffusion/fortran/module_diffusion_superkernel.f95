module module_diffusion_superkernel
    implicit none

    contains


subroutine map_0(pp_in, crlato, crlatu, tmp_lap_1104)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128
  
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: pp_in
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_lap_1104

  real :: local_delta_1767_in
  real :: local_delta_1764_in
  real :: local_laplacian_1761_in

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel

  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1767_in = (pp_in(i - 1, j, k) - pp_in(i, j, k))
  local_delta_1764_in = (pp_in(i + 1, j, k) - pp_in(i, j, k))
  local_laplacian_1761_in = (( (pp_in(i, j, k + 1) + pp_in(i, j, k - 1)) - (2.0 * pp_in(i, j, k))) + (crlato(i) * local_delta_1764_in) ) + (crlatu(i) * local_delta_1767_in) 
  tmp_lap_1104(i, j, k) = local_laplacian_1761_in

end subroutine map_0


subroutine map_1(hdmask, ms_sdfg_1330___local_hdweight_1693)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_hdweight_1693

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel

  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  ms_sdfg_1330___local_hdweight_1693(i, j, k) = (0.5 * hdmask(i, j, k))

end subroutine map_1

subroutine map_2(pp_in, hdmask, tmp_lap_1104, crlato, crlatu, pp_out)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128
  
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: pp_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_lap_1104
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: pp_out

  real :: local_delta_1803_in 
  real :: local_delta_1797_in 
  real :: local_fly_1336_in 
  real :: local_diffusive_flux_y_1800_in 
  real :: local_delta_1794_in 
  real :: local_delta_1788_in 
  real :: local_fly_1302_in 
  real :: local_diffusive_flux_y_1791_in 
  real :: local_delta_flux_y_1282_in 
  real :: local_delta_1785_in 
  real :: local_delta_1779_in 
  real :: local_flx_1267_in 
  real :: local_diffusive_flux_x_1782_in 
  real :: local_delta_1776_in 
  real :: local_delta_1770_in 
  real :: local_flx_1235_in 
  real :: local_diffusive_flux_x_1773_in 
  real :: local_delta_flux_x_1217_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel

  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1803_in = (pp_in(i, j, k) - pp_in(i - 1, j, k))
  local_delta_1797_in = (tmp_lap_1104(i, j, k) - tmp_lap_1104(i - 1, j, k))
  local_fly_1336_in = (crlato(i) - 1 * local_delta_1797_in)
  
  if ((local_fly_1336_in * local_delta_1803_in) > 0.0) then
    local_diffusive_flux_y_1800_in = 0.0  
  else
    local_diffusive_flux_y_1800_in = local_fly_1336_in
  end if

  local_delta_1794_in = (pp_in(i + 1, j, k) - pp_in(i, j, k))
  local_delta_1788_in = (tmp_lap_1104(i + 1, j, k) - tmp_lap_1104(i, j, k))
  local_fly_1302_in = (crlato(i) * local_delta_1788_in)

  if ((local_fly_1302_in * local_delta_1794_in) > 0.0) then 
    local_diffusive_flux_y_1791_in = 0.0 
  else 
    local_diffusive_flux_y_1791_in = local_fly_1302_in
  end if

  local_delta_flux_y_1282_in = (local_diffusive_flux_y_1791_in - local_diffusive_flux_y_1800_in)
  local_delta_1785_in = (pp_in(i, j, k) - pp_in(i, j, k - 1))
  local_delta_1779_in = (tmp_lap_1104(i, j, k) - tmp_lap_1104(i, j, k - 1))
  local_flx_1267_in = local_delta_1779_in
  
  if ((local_flx_1267_in * local_delta_1785_in) > 0.0) then
    local_diffusive_flux_x_1782_in = 0.0 
  else 
    local_diffusive_flux_x_1782_in = local_flx_1267_in
  end if

  local_delta_1776_in = (pp_in(i, j, k + 1) - pp_in(i, j, k))
  local_delta_1770_in = (tmp_lap_1104(i, j, k + 1) - tmp_lap_1104(i, j, k))
  local_flx_1235_in = local_delta_1770_in

  if ((local_flx_1235_in * local_delta_1776_in) > 0.0) then
    local_diffusive_flux_x_1773_in = 0.0 
  else
    local_diffusive_flux_x_1773_in =  local_flx_1235_in
  end if

  local_delta_flux_x_1217_in = (local_diffusive_flux_x_1773_in - local_diffusive_flux_x_1782_in)

  pp_out(i, j, k) = (pp_in(i, j, k) - (hdmask(i, j, k) * (local_delta_flux_x_1217_in + local_delta_flux_y_1282_in)))

end subroutine map_2

subroutine map_3(w_in, crlato, crlatu, tmp_lap_857)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: w_in
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_lap_857

  real :: local_delta_1812_in 
  real :: local_delta_1809_in 
  real :: local_laplacian_1806_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel

  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1812_in = (w_in(i - 1, j, k) - w_in(i, j, k))
  local_delta_1809_in = (w_in(i + 1, j, k) - w_in(i, j, k))
  local_laplacian_1806_in = ((((w_in(i, j, k + 1) + w_in(i, j, k - 1)) - (2.0 * w_in(i, j, k))) + (crlato(i) * local_delta_1809_in)) + (crlatu(i) * local_delta_1812_in))
  tmp_lap_857(i, j, k) = local_laplacian_1806_in

end subroutine map_3

subroutine map_4 (w_in, hdmask, tmp_lap_857, crlato, crlatu, w_out)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: w_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_lap_857
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: w_out

  real :: local_delta_1848_in 
  real :: local_delta_1842_in 
  real :: local_fly_1089_in 
  real :: local_diffusive_flux_y_1845_in 
  real :: local_delta_1839_in 
  real :: local_delta_1833_in 
  real :: local_fly_1055_in 
  real :: local_diffusive_flux_y_1836_in 
  real :: local_delta_flux_y_1035_in 
  real :: local_delta_1830_in 
  real :: local_delta_1824_in 
  real :: local_flx_1020_in 
  real :: local_diffusive_flux_x_1827_in 
  real :: local_delta_1821_in 
  real :: local_delta_1815_in 
  real :: local_flx_988_in 
  real :: local_diffusive_flux_x_1818_in 
  real :: local_delta_flux_x_970_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel

  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1848_in = (w_in(i, j, k) - w_in(i - 1, j, k))
  local_delta_1842_in = (tmp_lap_857(i, j, k) - tmp_lap_857(i - 1, j, k))
  local_fly_1089_in = (crlato(i) - 1 * local_delta_1842_in)
  
  if ((local_fly_1089_in * local_delta_1848_in) > 0.0) then
    local_diffusive_flux_y_1845_in = 0.0 
  else 
   local_diffusive_flux_y_1845_in = local_fly_1089_in
  end if

  local_delta_1839_in = (w_in(i + 1, j, k) - w_in(i, j, k))
  local_delta_1833_in = (tmp_lap_857(i + 1, j, k) - tmp_lap_857(i, j, k))
  local_fly_1055_in = (crlato(i) * local_delta_1833_in)

  if ((local_fly_1055_in * local_delta_1839_in) > 0.0) then 
    local_diffusive_flux_y_1836_in = 0.0 
  else 
    local_diffusive_flux_y_1836_in = local_fly_1055_in
  end if

  local_delta_flux_y_1035_in = (local_diffusive_flux_y_1836_in - local_diffusive_flux_y_1845_in)
  local_delta_1830_in = (w_in(i, j, k) - w_in(i, j, k - 1))
  local_delta_1824_in = (tmp_lap_857(i, j, k) - tmp_lap_857(i, j, k - 1))
  local_flx_1020_in = local_delta_1824_in
   
  if ((local_flx_1020_in * local_delta_1830_in) > 0.0) then 
    local_diffusive_flux_x_1827_in = 0.0
  else 
    local_diffusive_flux_x_1827_in = local_flx_1020_in
  end if

  local_delta_1821_in = (w_in(i, j, k + 1) - w_in(i, j, k))
  local_delta_1815_in = (tmp_lap_857(i, j, k + 1) - tmp_lap_857(i, j, k))
  local_flx_988_in = local_delta_1815_in
   
  if ((local_flx_988_in * local_delta_1821_in) > 0.0) then 
    local_diffusive_flux_x_1818_in = 0.0
  else 
    local_diffusive_flux_x_1818_in = local_flx_988_in
  end if

  local_delta_flux_x_970_in = (local_diffusive_flux_x_1818_in - local_diffusive_flux_x_1827_in)
  w_out(i, j, k) = (w_in(i, j, k) - (hdmask(i, j, k) * (local_delta_flux_x_970_in + local_delta_flux_y_1035_in)))

end subroutine map_4

subroutine map_5(v_in, crlato, crlatu, tmp_lap_610)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_in
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_lap_610

  real :: local_delta_1857_in 
  real :: local_delta_1854_in 
  real :: local_laplacian_1851_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1857_in = (v_in(i - 1, j, k) - v_in(i, j, k))
  local_delta_1854_in = (v_in(i + 1, j, k) - v_in(i, j, k))
  local_laplacian_1851_in = ((((v_in(i, j, k + 1) + v_in(i, j, k - 1)) - (2.0 * v_in(i, j, k))) + (crlato(i) * local_delta_1854_in)) + (crlatu(i) * local_delta_1857_in))
  tmp_lap_610(i, j, k) = local_laplacian_1851_in

end subroutine map_5

subroutine map_6(v_in, hdmask, crlato, tmp_lap_610, v_tmp)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_lap_610
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: v_tmp

  real :: local_delta_1893_in 
  real :: local_delta_1887_in 
  real :: local_fly_842_in 
  real :: local_diffusive_flux_y_1890_in 
  real :: local_delta_1884_in 
  real :: local_delta_1878_in 
  real :: local_fly_808_in 
  real :: local_diffusive_flux_y_1881_in 
  real :: local_delta_flux_y_788_in 
  real :: local_delta_1875_in 
  real :: local_delta_1869_in 
  real :: local_flx_773_in 
  real :: local_diffusive_flux_x_1872_in 
  real :: local_delta_1866_in 
  real :: local_delta_1860_in 
  real :: local_flx_741_in 
  real :: local_diffusive_flux_x_1863_in 
  real :: local_delta_flux_x_723_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1893_in = (v_in(i, j, k) - v_in(i - 1, j, k))
  local_delta_1887_in = (tmp_lap_610(i, j, k) - tmp_lap_610(i - 1, j, k))
  local_fly_842_in = (crlato(i) - 1 * local_delta_1887_in)
  
  if ((local_fly_842_in * local_delta_1893_in) > 0.0) then 
    local_diffusive_flux_y_1890_in = 0.0
  else 
    local_diffusive_flux_y_1890_in = local_fly_842_in
  end if
  local_delta_1884_in = (v_in(i + 1, j, k) - v_in(i, j, k))
  local_delta_1878_in = (tmp_lap_610(i + 1, j, k) - tmp_lap_610(i, j, k))
  local_fly_808_in = (crlato(i) * local_delta_1878_in)
  
  if ((local_fly_808_in * local_delta_1884_in) > 0.0) then 
    local_diffusive_flux_y_1881_in = 0.0
  else 
    local_diffusive_flux_y_1881_in = local_fly_808_in
  end if
  local_delta_flux_y_788_in = (local_diffusive_flux_y_1881_in - local_diffusive_flux_y_1890_in)
  local_delta_1875_in = (v_in(i, j, k) - v_in(i, j, k - 1))
  local_delta_1869_in = (tmp_lap_610(i, j, k) - tmp_lap_610(i, j, k - 1))
  local_flx_773_in = local_delta_1869_in
  
  if ((local_flx_773_in * local_delta_1875_in) > 0.0) then 
    local_diffusive_flux_x_1872_in = 0.0
  else 
    local_diffusive_flux_x_1872_in = local_flx_773_in
  end if 
  local_delta_1866_in = (v_in(i, j, k + 1) - v_in(i, j, k))
  local_delta_1860_in = (tmp_lap_610(i, j, k + 1) - tmp_lap_610(i, j, k))
  local_flx_741_in = local_delta_1860_in
  
  if ((local_flx_741_in * local_delta_1866_in) > 0.0) then 
    local_diffusive_flux_x_1863_in = 0.0
  else 
    local_diffusive_flux_x_1863_in = local_flx_741_in
  end if

  local_delta_flux_x_723_in = (local_diffusive_flux_x_1863_in - local_diffusive_flux_x_1872_in)
  v_tmp(i, j, k) = (v_in(i, j, k) - (hdmask(i, j, k) * (local_delta_flux_x_723_in + local_delta_flux_y_788_in)))

end subroutine map_6

subroutine map_7(u_in, crlato, crlatu, tmp_lap_363)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_in
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_lap_363

  real :: local_delta_1902_in 
  real :: local_delta_1899_in 
  real :: local_laplacian_1896_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1902_in = (u_in(i - 1, j, k) - u_in(i, j, k))
  local_delta_1899_in = (u_in(i + 1, j, k) - u_in(i, j, k))
  local_laplacian_1896_in = ((((u_in(i, j, k + 1) + u_in(i, j, k - 1)) - (2.0 * u_in(i, j, k))) + (crlato(i) * local_delta_1899_in)) + (crlatu(i) * local_delta_1902_in))
  tmp_lap_363(i, j, k) = local_laplacian_1896_in

end subroutine map_7

subroutine map_8(u_in, hdmask, crlato, tmp_lap_363, u_tmp)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_lap_363
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: u_tmp

  real :: local_delta_1938_in 
  real :: local_delta_1932_in 
  real :: local_fly_595_in 
  real :: local_diffusive_flux_y_1935_in 
  real :: local_delta_1929_in 
  real :: local_delta_1923_in 
  real :: local_fly_561_in 
  real :: local_diffusive_flux_y_1926_in 
  real :: local_delta_flux_y_541_in 
  real :: local_delta_1920_in 
  real :: local_delta_1914_in 
  real :: local_flx_526_in 
  real :: local_delta_1911_in 
  real :: local_delta_1905_in 
  real :: local_flx_494_in 
  real :: local_diffusive_flux_x_1908_in 
  real :: local_delta_flux_x_476_in 
  
  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_delta_1938_in = (u_in(i, j, k) - u_in(i - 1, j, k))
  local_delta_1932_in = (tmp_lap_363(i, j, k) - tmp_lap_363(i - 1, j, k))
  local_fly_595_in = (crlato(i) - 1 * local_delta_1932_in)
   
  if ((local_fly_595_in * local_delta_1938_in) > 0.0) then
    local_diffusive_flux_y_1935_in = 0.0
  else 
    local_diffusive_flux_y_1935_in = local_fly_595_in
  end if

  local_delta_1929_in = (u_in(i + 1, j, k) - u_in(i, j, k))
  local_delta_1923_in = (tmp_lap_363(i + 1, j, k) - tmp_lap_363(i, j, k))
  local_fly_561_in = (crlato(i) * local_delta_1923_in)
   
  if ((local_fly_561_in * local_delta_1929_in) > 0.0) then
    local_diffusive_flux_y_1926_in = 0.0
  else 
    local_diffusive_flux_y_1926_in = local_fly_561_in
  end if

  local_delta_flux_y_541_in = (local_diffusive_flux_y_1926_in - local_diffusive_flux_y_1935_in)
  local_delta_1920_in = (u_in(i, j, k) - u_in(i, j, k - 1))
  local_delta_1914_in = (tmp_lap_363(i, j, k) - tmp_lap_363(i, j, k - 1))
  local_flx_526_in = local_delta_1914_in
  
  if ((local_flx_526_in * local_delta_1920_in) > 0.0) then
    local_diffusive_flux_y_1926_in = 0.0
  else 
    local_diffusive_flux_y_1926_in = local_flx_526_in
  end if

  local_delta_1911_in = (u_in(i, j, k + 1) - u_in(i, j, k))
  local_delta_1905_in = (tmp_lap_363(i, j, k + 1) - tmp_lap_363(i, j, k))
  local_flx_494_in = local_delta_1905_in
   
  if ((local_flx_494_in * local_delta_1911_in) > 0.0) then
    local_diffusive_flux_x_1908_in = 0.0
  else 
    local_diffusive_flux_x_1908_in = local_flx_494_in
  end if

  local_delta_flux_x_476_in = (local_diffusive_flux_x_1908_in - local_diffusive_flux_y_1926_in)
  u_tmp(i, j, k) = (u_in(i, j, k) - (hdmask(i, j, k) * (local_delta_flux_x_476_in + local_delta_flux_y_541_in)))

end subroutine map_8

! subroutine map_9(acrlat0, ms_sdfg_1330___local_frac_1_dx_1660)
!   integer, parameter :: ip=128
!   integer, parameter :: jp=80
!   integer, parameter :: kp=128

!   real, dimension(0:(ip+1)), intent(In) :: acrlat0
!   real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_frac_1_dx_1660

!   integer :: global_id
!   integer :: i
!   integer :: j
!   integer :: k
!   integer :: k_range
!   integer :: j_range
!   integer :: i_range
!   integer :: k_rel
!   integer :: j_rel
!   integer :: i_rel

!   call get_global_id(global_id,0)
!   k_range = (((kp + 1) - 1) + 1)
!   j_range = ((jp - 1) + 1)
!   i_range = ((ip - 1) + 1)
!   k_rel = (global_id / (j_range * i_range))
!   k = (k_rel + 1)
!   j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
!   j = (j_rel + 1)
!   i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
!   i = (i_rel + 1)

!   ms_sdfg_1330___local_frac_1_dx_1660(i, j, k) = (acrlat0(i) * 5729.58)

! end subroutine map_9

subroutine map_10(u_tmp, v_tmp, acrlat0, tmp_T_sqr_s_1351)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_tmp
  real, dimension(0:(ip+1)), intent(In) :: acrlat0
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_T_sqr_s_1351

  real :: ms_sdfg_1330___local_frac_1_dx_1660
  real :: local_delta_1944_in
  real :: local_delta_1941_in
  real :: local_T_s_1667_in

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  ms_sdfg_1330___local_frac_1_dx_1660 = acrlat0(i) * 5729.58

  local_delta_1944_in = (u_tmp(i, j, k - 1) - u_tmp(i, j, k))
  local_delta_1941_in = (v_tmp(i - 1, j, k) - v_tmp(i, j, k))
  local_T_s_1667_in = (local_delta_1941_in * 5729.58 / 6371229.0) - (local_delta_1944_in * ms_sdfg_1330___local_frac_1_dx_1660)
  tmp_T_sqr_s_1351(i, j, k) = (local_T_s_1667_in * local_T_s_1667_in)

end subroutine map_10

subroutine map_11(u_tmp, v_tmp, acrlat0, tmp_S_sqr_uv_1352)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128
  
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_tmp
  real, dimension(0:(ip+1)), intent(In) :: acrlat0
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: tmp_S_sqr_uv_1352

  real :: ms_sdfg_1330___local_frac_1_dx_1660 
  real :: local_delta_1950_in 
  real :: local_delta_1947_in 
  real :: local_S_uv_1680_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  ms_sdfg_1330___local_frac_1_dx_1660 = acrlat0(i) * 5729.58

  local_delta_1950_in = (v_tmp(i, j, k + 1) - v_tmp(i, j, k))
  local_delta_1947_in = (u_tmp(i + 1, j, k) - u_tmp(i, j, k))
  local_S_uv_1680_in = ((local_delta_1947_in * (5729.58 / 6371229.0)) + (local_delta_1950_in * ms_sdfg_1330___local_frac_1_dx_1660))
  tmp_S_sqr_uv_1352(i, j, k) = (local_S_uv_1680_in * local_S_uv_1680_in)

end subroutine map_11

subroutine map_12(tmp_T_sqr_s_1351, tmp_S_sqr_uv_1352, ms_sdfg_1330___local_hdweight_1693, ms_sdfg_1330___local_smag_u_1696)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_T_sqr_s_1351
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_S_sqr_uv_1352
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_hdweight_1693
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_smag_u_1696

  real :: local_avg_1953_in
  real :: local_avg_1956_in

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_avg_1956_in = (0.5 * (tmp_S_sqr_uv_1352(i - 1, j, k) + tmp_S_sqr_uv_1352(i, j, k)))
  local_avg_1953_in = (0.5 * (tmp_T_sqr_s_1351(i, j, k + 1) + tmp_T_sqr_s_1351(i, j, k)))
  ms_sdfg_1330___local_smag_u_1696(i, j, k) = ((0.3 * sqrt((local_avg_1953_in + local_avg_1956_in))) - ms_sdfg_1330___local_hdweight_1693(i, j, k))

end subroutine map_12

subroutine map_13(ms_sdfg_1330___local_smag_u_1696, ms_sdfg_1330___local_smag_u_1696__1)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_smag_u_1696
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_smag_u_1696__1

  real :: dace_min0___local_smag_u_1696_out 
  real :: dace_max0___dace_min1___local_smag_u_1696_out 
  real :: dace_max1___dace_min1___local_smag_u_1696_out 
  real :: dace_min1___local_smag_u_1696_out 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  dace_min0___local_smag_u_1696_out = 0.5
  dace_max0___dace_min1___local_smag_u_1696_out = 0.0
  dace_max1___dace_min1___local_smag_u_1696_out = ms_sdfg_1330___local_smag_u_1696(i, j, k)
  if (dace_max0___dace_min1___local_smag_u_1696_out < dace_max1___dace_min1___local_smag_u_1696_out) then
    dace_min1___local_smag_u_1696_out = dace_max1___dace_min1___local_smag_u_1696_out 
  else 
    dace_min1___local_smag_u_1696_out = dace_max0___dace_min1___local_smag_u_1696_out
  end if
  if (dace_min0___local_smag_u_1696_out < dace_min1___local_smag_u_1696_out) then
    ms_sdfg_1330___local_smag_u_1696__1(i, j, k) = dace_min0___local_smag_u_1696_out 
  else 
    ms_sdfg_1330___local_smag_u_1696__1(i, j, k) = dace_min1___local_smag_u_1696_out
  end if

end subroutine map_13

subroutine map_14(ms_sdfg_1330___local_smag_u_1696__1, u_tmp, crlato, crlatu, u_out)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_smag_u_1696__1
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_tmp
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: u_out

  real :: local_lapu_1726_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_lapu_1726_in = ((((u_tmp(i, j, k + 1) + u_tmp(i, j, k - 1)) - (2.0 * u_tmp(i, j, k))) + (crlato(i) * (u_tmp(i + 1, j, k) - u_tmp(i, j, k)))) + (crlatu(i) * (u_tmp(i - 1, j, k) - u_tmp(i, j, k))))
  u_out(i, j, k) = (u_tmp(i, j, k) + (ms_sdfg_1330___local_smag_u_1696__1(i, j, k) * local_lapu_1726_in))

end subroutine map_14

subroutine map_15(tmp_T_sqr_s_1351, tmp_S_sqr_uv_1352, ms_sdfg_1330___local_hdweight_1693, ms_sdfg_1330___local_smag_v_1719)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_T_sqr_s_1351
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: tmp_S_sqr_uv_1352
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_hdweight_1693
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_smag_v_1719

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  ms_sdfg_1330___local_smag_v_1719(i, j, k) = ((0.3 * sqrt(((0.5 * (tmp_T_sqr_s_1351(i, j, k) + tmp_T_sqr_s_1351(i + 1, j, k))) + (0.5 * (tmp_S_sqr_uv_1352(i, j, k) + tmp_S_sqr_uv_1352(i, j, k - 1)))))) - ms_sdfg_1330___local_hdweight_1693(i, j, k))

end subroutine map_15

subroutine map_16(ms_sdfg_1330___local_smag_v_1719, ms_sdfg_1330___local_smag_v_1719__1)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_smag_v_1719
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: ms_sdfg_1330___local_smag_v_1719__1

  real :: dace_min0___local_smag_v_1719_out 
  real :: dace_max0___dace_min1___local_smag_v_1719_out 
  real :: dace_max1___dace_min1___local_smag_v_1719_out 
  real :: dace_min1___local_smag_v_1719_out 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)


dace_min0___local_smag_v_1719_out = 0.5
dace_max0___dace_min1___local_smag_v_1719_out = 0.0
dace_max1___dace_min1___local_smag_v_1719_out = ms_sdfg_1330___local_smag_v_1719(i, j, k)
if (dace_max0___dace_min1___local_smag_v_1719_out < dace_max1___dace_min1___local_smag_v_1719_out) then 
  dace_min1___local_smag_v_1719_out = dace_max1___dace_min1___local_smag_v_1719_out 
else 
  dace_min1___local_smag_v_1719_out = dace_max0___dace_min1___local_smag_v_1719_out
end if
if (dace_min0___local_smag_v_1719_out < dace_min1___local_smag_v_1719_out) then 
  ms_sdfg_1330___local_smag_v_1719__1(i, j, k) = dace_min0___local_smag_v_1719_out 
else 
  ms_sdfg_1330___local_smag_v_1719__1(i, j, k) = dace_min1___local_smag_v_1719_out
end if

end subroutine map_16

subroutine map_17(ms_sdfg_1330___local_smag_v_1719__1, v_tmp, crlavo, crlavu, v_out)
  integer, parameter :: ip=128
  integer, parameter :: jp=80
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: ms_sdfg_1330___local_smag_v_1719__1
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_tmp
  real, dimension(0:(ip+1)), intent(In) :: crlavo
  real, dimension(0:(ip+1)), intent(In) :: crlavu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: v_out

  real :: local_lapv_1728_in 

  integer :: global_id
  integer :: i
  integer :: j
  integer :: k
  integer :: k_range
  integer :: j_range
  integer :: i_range
  integer :: k_rel
  integer :: j_rel
  integer :: i_rel
  call get_global_id(global_id,0)
  k_range = (((kp + 1) - 1) + 1)
  j_range = ((jp - 1) + 1)
  i_range = ((ip - 1) + 1)
  k_rel = (global_id / (j_range * i_range))
  k = (k_rel + 1)
  j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range)
  j = (j_rel + 1)
  i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range))
  i = (i_rel + 1)

  local_lapv_1728_in = ((((v_tmp(i, j, k + 1) + v_tmp(i, j, k - 1)) - (2.0 * v_tmp(i, j, k))) + (crlavo(i) * (v_tmp(i + 1, j, k) - v_tmp(i, j, k)))) + (crlavu(i) * (v_tmp(i - 1, j, k) - v_tmp(i, j, k))))
  v_out = (v_tmp(i, j, k) + (ms_sdfg_1330___local_smag_v_1719__1(i, j, k) * local_lapv_1728_in))

end subroutine map_17


subroutine diffusion_superkernel(pp_in, w_in, v_in, u_in, hdmask, acrlat0, crlato, crlatu, crlavo, crlavu, pp_out, w_out, v_out, u_out, state)
  integer, parameter :: ip=128
  integer, parameter :: jp=90
  integer, parameter :: kp=128

  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: pp_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: w_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: v_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: u_in
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(In) :: hdmask
  real, dimension(0:(ip+1)), intent(In) :: acrlat0
  real, dimension(0:(ip+1)), intent(In) :: crlato
  real, dimension(0:(ip+1)), intent(In) :: crlatu
  real, dimension(0:(ip+1)), intent(In) :: crlavo
  real, dimension(0:(ip+1)), intent(In) :: crlavu
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: pp_out
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: w_out
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: v_out
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)), intent(Out) :: u_out
  integer, intent(In) :: state

  ! Intermediate buffers
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: pp_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: w_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: v_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: u_tmp
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_lap_1104
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_hdweight_1693
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_lap_857
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_lap_610
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_lap_363
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_frac_1_dx_1660
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_T_sqr_s_1351
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: tmp_S_sqr_uv_1352
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_smag_u_1696
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_smag_v_1719
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_smag_u_1696__1
  real, dimension(0:(ip+1), 0:(jp+1), 0:(kp+1)) :: ms_sdfg_1330___local_smag_v_1719__1

  integer, parameter :: ST_MAP_0 = 0
  integer, parameter :: ST_MAP_1 = 1
  integer, parameter :: ST_MAP_2 = 2
  integer, parameter :: ST_MAP_3 = 3
  integer, parameter :: ST_MAP_4 = 4
  integer, parameter :: ST_MAP_5 = 5
  integer, parameter :: ST_MAP_6 = 6
  integer, parameter :: ST_MAP_7 = 7
  integer, parameter :: ST_MAP_8 = 8
  integer, parameter :: ST_MAP_9 = 9
  integer, parameter :: ST_MAP_10 = 10
  integer, parameter :: ST_MAP_11 = 11
  integer, parameter :: ST_MAP_12 = 12
  integer, parameter :: ST_MAP_13 = 13
  integer, parameter :: ST_MAP_14 = 14
  integer, parameter :: ST_MAP_15 = 15
  integer, parameter :: ST_MAP_16 = 16
  integer, parameter :: ST_MAP_17 = 17

  select case(state)
    case (ST_MAP_0)
      call map_0(pp_in, crlato, crlatu, tmp_lap_1104)
    case (ST_MAP_1)
      call map_1(hdmask, ms_sdfg_1330___local_hdweight_1693)
    case (ST_MAP_2)
      call map_2(pp_in, hdmask, tmp_lap_1104, crlato, crlatu, pp_out)
    case (ST_MAP_3)
      call map_3(w_in, crlato, crlatu, tmp_lap_857)
    case (ST_MAP_4)
      call map_4 (w_in, hdmask, tmp_lap_857, crlato, crlatu, w_out)
    case (ST_MAP_5)
      call map_5(v_in, crlato, crlatu, tmp_lap_610)
    case (ST_MAP_6)
      call map_6(v_in, hdmask, crlato, tmp_lap_610, v_tmp)
    case (ST_MAP_7)
      call map_7(u_in, crlato, crlatu, tmp_lap_363)
    case (ST_MAP_8)
      call map_8(u_in, hdmask, crlato, tmp_lap_363, u_tmp)
    ! case (ST_MAP_9)
      ! call map_9(acrlat0, ms_sdfg_1330___local_frac_1_dx_1660)
    case (ST_MAP_10)
      call map_10(u_tmp, v_tmp, acrlat0, tmp_T_sqr_s_1351)
    case (ST_MAP_11)
      call map_11(u_tmp, v_tmp, acrlat0, tmp_S_sqr_uv_1352)
    case (ST_MAP_12)
      call map_12(tmp_T_sqr_s_1351, tmp_S_sqr_uv_1352, ms_sdfg_1330___local_hdweight_1693, ms_sdfg_1330___local_smag_u_1696)
    case (ST_MAP_13)
      call map_13(ms_sdfg_1330___local_smag_u_1696, ms_sdfg_1330___local_smag_u_1696__1)
    case (ST_MAP_14)
      call map_14(ms_sdfg_1330___local_smag_u_1696__1, u_tmp, crlato, crlatu, u_out)
    case (ST_MAP_15)
      call map_15(tmp_T_sqr_s_1351, tmp_S_sqr_uv_1352, ms_sdfg_1330___local_hdweight_1693, ms_sdfg_1330___local_smag_v_1719)
    case (ST_MAP_16)
      call map_16(ms_sdfg_1330___local_smag_v_1719, ms_sdfg_1330___local_smag_v_1719__1)
    case (ST_MAP_17)
      call map_17(ms_sdfg_1330___local_smag_v_1719__1, v_tmp, crlavo, crlavu, v_out)
  end select

end subroutine diffusion_superkernel

end module module_diffusion_superkernel
