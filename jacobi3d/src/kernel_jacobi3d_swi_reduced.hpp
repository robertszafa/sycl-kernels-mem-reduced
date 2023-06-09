#include <CL/sycl.hpp>
#include <array>
#include <cstdio>
#include <iostream>

#if FPGA || FPGA_EMULATOR
  #include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "jacobi3d_sizes.hpp"

using namespace sycl;

double jacobi3d_swi_reduced(queue &q, const std::vector<float> &u,
                            std::vector<float> &un) {

  range<1> num_items{u.size()};

  buffer u_0_buf(u);
  buffer un_1_buf(un);

  sycl::event event = q.submit([&](handler &hnd) {
    accessor u_0(u_0_buf, hnd, read_only);
    accessor un_1(un_1_buf, hnd, write_only, no_init);

    hnd.single_task<class jacobi3d_superkernel>(
        [=]() [[intel::kernel_args_restrict]] {
          const int nx___stencil_0_scal = 300;
          const int ny___stencil_0_scal = 300;
          const int nz___stencil_0_scal = 300;
          const float c___stencil_0_scal = 0.1;
          const int nx___stencil_1_scal = 300;
          const int ny___stencil_1_scal = 300;
          const int nz___stencil_1_scal = 300;
          const float c___stencil_1_scal = 0.1;
          const int nx___stencil_2_scal = 300;
          const int ny___stencil_2_scal = 300;
          const int nz___stencil_2_scal = 300;
          const float c___stencil_2_scal = 0.1;
          const int nx___stencil_3_scal = 300;
          const int ny___stencil_3_scal = 300;
          const int nz___stencil_3_scal = 300;
          const float c___stencil_3_scal = 0.1;
          int i___stencil_3_scal;
          int j___stencil_3_scal;
          int k___stencil_3_scal;
          int i_range___stencil_3_scal;
          int j_range___stencil_3_scal;
          int k_range___stencil_3_scal;
          int i_rel___stencil_3_scal;
          int j_rel___stencil_3_scal;
          int k_rel___stencil_3_scal;
          int i___stencil_2_scal;
          int j___stencil_2_scal;
          int k___stencil_2_scal;
          int i_range___stencil_2_scal;
          int j_range___stencil_2_scal;
          int k_range___stencil_2_scal;
          int i_rel___stencil_2_scal;
          int j_rel___stencil_2_scal;
          int k_rel___stencil_2_scal;
          int i___stencil_1_scal;
          int j___stencil_1_scal;
          int k___stencil_1_scal;
          int i_range___stencil_1_scal;
          int j_range___stencil_1_scal;
          int k_range___stencil_1_scal;
          int i_rel___stencil_1_scal;
          int j_rel___stencil_1_scal;
          int k_rel___stencil_1_scal;
          int i___stencil_0_scal;
          int j___stencil_0_scal;
          int k___stencil_0_scal;
          int i_range___stencil_0_scal;
          int j_range___stencil_0_scal;
          int k_range___stencil_0_scal;
          int i_rel___stencil_0_scal;
          int j_rel___stencil_0_scal;
          int k_rel___stencil_0_scal;
          int i___f_maps_un_1_0;
          float v0_s_0___f_comp_un_1_1[6];
          int i___f_maps_un_1_2;
          float v1_s_0___f_comp_un_1_3[6];
          int i___f_maps_un_1_4;
          float v2_s_0___f_comp_un_1_5[6];
          const int s1[] = {303, 91205, 91506, 91508, 91809, 182711};
          float svec_un_1_6[1496];
          int s_idx_1;
          int s_idx_2;
          int s_idx_3;
          int s_idx_4;
          int idx;

          [[intel::ivdep]] for (idx = 1;
                                idx < (300 - 4) * (300 - 4) * (300 - 4);
                                ++idx) {

            // [[intel::loop_coalesce]] 
            for (s_idx_1 = 1; s_idx_1 <= 6; s_idx_1 += 1) {
              for (s_idx_2 = 1; s_idx_2 <= 6; s_idx_2 += 1) {
                for (s_idx_3 = 1; s_idx_3 <= 6; s_idx_3 += 1) {
                  for (s_idx_4 = 1; s_idx_4 <= 6; s_idx_4 += 1) {
                    svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                      ((6 - 1) + 1), 1, 1, 1, 1, s_idx_1,
                                      s_idx_2, s_idx_3, s_idx_4)] =
                        u_0[F1D2C(1, idx + s1[F1D2C(1, s_idx_1)] +
                                         s1[F1D2C(1, s_idx_2)] +
                                         s1[F1D2C(1, s_idx_3)] +
                                         s1[F1D2C(1, s_idx_4)])];
                  }
                }
              }
            }


            // [[intel::loop_coalesce]] 
            for (i___f_maps_un_1_4 = 1; i___f_maps_un_1_4 <= 6;
                                          i___f_maps_un_1_4 += 1) {
                #pragma unroll
              for (i___f_maps_un_1_2 = 1; i___f_maps_un_1_2 <= 6;
                   i___f_maps_un_1_2 += 1) {
                #pragma unroll
                for (i___f_maps_un_1_0 = 1; i___f_maps_un_1_0 <= 6;
                     i___f_maps_un_1_0 += 1) {
                  k_range___stencil_0_scal = ((300 - 1) + 1);
                  v0_s_0___f_comp_un_1_1[F1D2C(1, i___f_maps_un_1_0)] =
                      (svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 3)] +
                       svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 4)] +
                       svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 2)] +
                       svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 5)] +
                       svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 1)] +
                       svec_un_1_6[F4D2C(((6 - 1) + 1), ((6 - 1) + 1),
                                         ((6 - 1) + 1), 1, 1, 1, 1,
                                         i___f_maps_un_1_4, i___f_maps_un_1_2,
                                         i___f_maps_un_1_0, 6)]) *
                      c___stencil_0_scal;
                }


                k_range___stencil_1_scal = ((300 - 1) + 1);
                v1_s_0___f_comp_un_1_3[F1D2C(1, i___f_maps_un_1_2)] =
                    (v0_s_0___f_comp_un_1_1[F1D2C(1, 3)] +
                     v0_s_0___f_comp_un_1_1[F1D2C(1, 4)] +
                     v0_s_0___f_comp_un_1_1[F1D2C(1, 2)] +
                     v0_s_0___f_comp_un_1_1[F1D2C(1, 5)] +
                     (*v0_s_0___f_comp_un_1_1) +
                     v0_s_0___f_comp_un_1_1[F1D2C(1, 6)]) *
                    c___stencil_1_scal;
              }
              k_range___stencil_2_scal = ((300 - 1) + 1);
              v2_s_0___f_comp_un_1_5[F1D2C(1, i___f_maps_un_1_4)] =
                  (v1_s_0___f_comp_un_1_3[F1D2C(1, 3)] +
                   v1_s_0___f_comp_un_1_3[F1D2C(1, 4)] +
                   v1_s_0___f_comp_un_1_3[F1D2C(1, 2)] +
                   v1_s_0___f_comp_un_1_3[F1D2C(1, 5)] +
                   (*v1_s_0___f_comp_un_1_3) +
                   v1_s_0___f_comp_un_1_3[F1D2C(1, 6)]) *
                  c___stencil_2_scal;
            }

            k_range___stencil_3_scal = ((300 - 1) + 1);
            un_1[F1D2C(1, idx)] = (v2_s_0___f_comp_un_1_5[F1D2C(1, 3)] +
                                   v2_s_0___f_comp_un_1_5[F1D2C(1, 4)] +
                                   v2_s_0___f_comp_un_1_5[F1D2C(1, 2)] +
                                   v2_s_0___f_comp_un_1_5[F1D2C(1, 5)] +
                                   (*v2_s_0___f_comp_un_1_5) +
                                   v2_s_0___f_comp_un_1_5[F1D2C(1, 6)]) *
                                  c___stencil_3_scal;
            // RF4A End Inline
          }
        });
  });

  auto start = event.get_profiling_info<info::event_profiling::command_start>();
  auto end = event.get_profiling_info<info::event_profiling::command_end>();
  auto time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
