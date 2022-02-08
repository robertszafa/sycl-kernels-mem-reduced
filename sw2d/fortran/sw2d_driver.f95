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

   integer, allocatable :: wet(:, :)
   real, allocatable :: eta(:, :)
   real, allocatable :: u(:, :)
   real, allocatable :: v(:, :)
   real, allocatable :: h(:, :)
   real, allocatable :: etann(:, :)
   real, allocatable :: un(:, :)
   real, allocatable :: vn(:, :)
   real, allocatable :: hzero(:, :)
   real, allocatable :: du___dyn(:, :)
   real, allocatable  :: dv___dyn(:, :)
   real, allocatable  :: etan(:, :)

   integer :: state_idx, j, k
   integer, parameter :: ST_DYN_SHAPIRO_MAP_49 = 0 !  dyn_shapiro_map_49
   integer, parameter :: ST_DYN_SHAPIRO_MAP_55 = 1 !  dyn_shapiro_map_55
   integer, parameter :: ST_DYN_SHAPIRO_MAP_75 = 2 !  dyn_shapiro_map_75
   integer, parameter :: ST_DYN_SHAPIRO_MAP_92 = 3 !  dyn_shapiro_map_92
   real(kind=8), dimension(0:1) :: timestamp

   allocate (wet(0:(ny + 1), 0:(nx + 1)))
   allocate (eta(0:(ny + 1), 0:(nx + 1)))
   allocate (u(0:(ny + 1), 0:(nx + 1)))
   allocate (v(0:(ny + 1), 0:(nx + 1)))
   allocate (h(0:(ny + 1), 0:(nx + 1)))
   allocate (etann(0:(ny + 1), 0:(nx + 1)))
   allocate (un(0:(ny + 1), 0:(nx + 1)))
   allocate (vn(0:(ny + 1), 0:(nx + 1)))
   allocate (hzero(0:(ny + 1), 0:(nx + 1)))
   allocate (du___dyn(0:(ny + 1), 0:(nx + 1)))
   allocate (dv___dyn(0:(ny + 1), 0:(nx + 1)))
   allocate (etan(0:(ny + 1), 0:(nx + 1)))

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
      eta(j, k) = -min(0.0, hzero(j, k))
      etann(j, k) = -min(0.0, hzero(j, k))
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
         call dyn_shapiro_superkernel(wet, eta, u, v, h, etann, un, vn, du___dyn, dv___dyn, etan, state_idx, global_id)
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
