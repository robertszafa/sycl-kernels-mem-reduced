program main
   use module_velfg_superkernel, only: velfg_superkernel
   integer :: global_id

   integer, parameter :: ip = IP
   integer, parameter :: jp = JP
   integer, parameter :: kp = 90

   real, dimension(0:(ip + 1), (-1):(jp + 1), 0:(kp + 1)) :: u
   real, dimension(0:(ip + 1), (-1):(jp + 1), 0:(kp + 1)) :: v
   real, dimension(0:(ip + 1), (-1):(jp + 1), (-1):(kp + 1)) :: w
   real, dimension(0:ip, 0:jp, 0:kp) :: f
   real, dimension(0:ip, 0:jp, 0:kp) :: g
   real, dimension(0:ip, 0:jp, 0:kp) :: h

   real, dimension((-1):(kp + 2)) :: dzn
   real, dimension((-1):(kp + 2)) :: dzs
   real, dimension((-1):(ip + 1)) :: dx1
   real, dimension(0:(jp + 1)) :: dy1
   integer :: i, j, k

   integer, parameter :: ST_LES_MAP_87 = 10 !  les_map_87
   integer, parameter :: ST_LES_MAP_107 = 11 !  les_map_107

   integer, parameter :: ST_velfg_MAP_76 = 18 !  velfg_map_76
   integer, parameter :: ST_velfg_MAP_133 = 19 !  velfg_map_133
   integer, parameter :: ST_velfg_MAP_155 = 20 !  velfg_map_155
   integer, parameter :: ST_velfg_MAP_218 = 28 !  velfg_map_218
   integer, dimension(3) :: states = (/ST_velfg_MAP_76, ST_velfg_MAP_133, ST_velfg_MAP_218/)
   integer :: state_ptr, state_idx
   integer :: clock_rate
   integer(kind=4), dimension(0:1) :: timestamp

   do k = -1, kp + 2
      dzn(k) = 1.
      dzs(k) = 1.
   end do
   do i = -1, ip + 1
      dx1(i) = 1.
   end do
   do j = 0, jp + 1
      dy1(j) = 1.
   end do

   call system_clock(timestamp(0), clock_rate)
   do state_idx = 1, 3
      state_ptr = states(state_idx)
      do global_id = 1, IP*JP*KP - 1
         call velfg_superkernel(f, g, h, dzn, u, v, w, dx1, dy1, dzs, state_ptr, global_id)
      end do
   end do

   call system_clock(timestamp(1), clock_rate)
   print '("Finished kernel execution in (ms): ",f6.3)', (timestamp(1) - timestamp(0))/real(clock_rate)
   print '("Finished kernel execution + memory transfer in (ms): ",f6.3)', (timestamp(1) - timestamp(0))/real(clock_rate)

end program main
