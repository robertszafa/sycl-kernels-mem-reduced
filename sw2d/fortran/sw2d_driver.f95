program main
   use omp_lib
   use module_dyn_shapiro_superkernel, only: dyn_shapiro_superkernel
   integer :: global_id

   integer, parameter :: nx = NX
   integer, parameter :: ny = NY

   real, parameter :: g = 9.81
   real, parameter :: dt = 0.1
   real, parameter :: dx = 10.0
   real, parameter :: dy = 10.0
   real, parameter :: eps = 0.05
   real, parameter :: hmin = 0.05

   integer, dimension(0:(ny + 1), 0:(nx + 1)) :: wet
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: eta
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: u
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: v
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: h

   real, dimension(0:(ny + 1), 0:(nx + 1)) :: etann
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: un
   real, dimension(0:(ny + 1), 0:(nx + 1)) :: vn

   real, dimension(0:(ny + 1), 0:(nx + 1)) :: hzero
   real :: tmp

   integer :: state_idx, j, k
   integer, parameter :: ST_DYN_SHAPIRO_MAP_49 = 0 !  dyn_shapiro_map_49
   integer, parameter :: ST_DYN_SHAPIRO_MAP_55 = 1 !  dyn_shapiro_map_55
   integer, parameter :: ST_DYN_SHAPIRO_MAP_75 = 2 !  dyn_shapiro_map_75
   integer, parameter :: ST_DYN_SHAPIRO_MAP_92 = 3 !  dyn_shapiro_map_92
   real(kind=8), dimension(0:1) :: timestamp

! INITIALISATION -------------------------------------------------
! initial conditions
   DO j = 0, ny + 1
   DO k = 0, nx + 1
      hzero(j, k) = 10.0
   END DO
   END DO

! land boundaries with 10 m elevation
   DO k = 0, nx + 1
      hzero(0, k) = -10.0
      hzero(ny + 1, k) = -10.0
   END DO

   DO j = 0, ny + 1
      hzero(j, 0) = -10.0
      hzero(j, nx + 1) = -10.0
   END DO

   DO j = 0, ny + 1
   DO k = 0, nx + 1
      tmp = min(0.0, hzero(j, k))
      eta(j, k) = -tmp
      etann(j, k) = -tmp
   END DO
   END DO
!XXXXXXXXXXXXXXXXXXX
! INITIALISATION END -------------------------------------------------

   !  call cpu_time(timestamp(0))
   timestamp(0) = omp_get_wtime()
   do state_idx = 0, 3
#ifdef WITH_OPENMP
!$OMP PARALLEL DO PRIVATE(global_id)
#endif
      do global_id = 1, NX*NY - 1
         call dyn_shapiro_superkernel(wet, eta, u, v, h, etann, un, vn, state_idx, global_id)
      end do
#ifdef WITH_OPENMP
!$OMP BARRIER
#endif
   end do

   !  call cpu_time(timestamp(1))
   timestamp(1) = omp_get_wtime()
   print '("Kernel time (ms): ",f10.3)', (timestamp(1) - timestamp(0))*1000.0
   print '("Total time (ms): ",f10.3)', (timestamp(1) - timestamp(0))*1000.0

end program main
