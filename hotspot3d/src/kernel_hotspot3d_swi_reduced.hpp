#include <CL/sycl.hpp>
#include <array>
#include <cstdio>
#include <iostream>

#if FPGA || FPGA_EMULATOR
  #include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "hotspot3d_sizes.hpp"

using namespace sycl;

double hotspot3d_swi_reduced(queue &q, const std::vector<float> &tIn,
                             const std::vector<float> &pIn,
                             std::vector<float> &tOut) {

  buffer tin_buf(tIn);
  buffer pin_buf(pIn);
  buffer tout_buf(tOut);

  sycl::event event = q.submit([&](handler &hnd) {
    accessor tin_0(tin_buf, hnd, read_only);
    accessor pin_0(pin_buf, hnd, read_only);
    accessor tout_1(tout_buf, hnd, write_only, no_init);

    hnd.single_task<
        class hotspot3d_superkernel>([=]() [[intel::kernel_args_restrict]] {
      const int nx___stencil_0_scal = 500;
      const int ny___stencil_0_scal = 500;
      const int nz___stencil_0_scal = 100;
      const int nx___stencil_1_scal = 500;
      const int ny___stencil_1_scal = 500;
      const int nz___stencil_1_scal = 100;
      const int nx___stencil_2_scal = 500;
      const int ny___stencil_2_scal = 500;
      const int nz___stencil_2_scal = 100;
      const int nx___stencil_3_scal = 500;
      const int ny___stencil_3_scal = 500;
      const int nz___stencil_3_scal = 100;
      float dx___stencil_3_scal;
      float dy___stencil_3_scal;
      float dz___stencil_3_scal;
      float cap___stencil_3_scal;
      float rx___stencil_3_scal;
      float ry___stencil_3_scal;
      float rz___stencil_3_scal;
      float t_chip___stencil_3_scal;
      float chip_height___stencil_3_scal;
      float chip_width___stencil_3_scal;
      float amb_temp___stencil_3_scal;
      float max_slope___stencil_3_scal;
      float dt___stencil_3_scal;
      float ce___stencil_3_scal;
      float cw___stencil_3_scal;
      float cn___stencil_3_scal;
      float cs___stencil_3_scal;
      float ct___stencil_3_scal;
      float cb___stencil_3_scal;
      float cc___stencil_3_scal;
      float stepdivcap___stencil_3_scal;
      float dx___stencil_2_scal;
      float dy___stencil_2_scal;
      float dz___stencil_2_scal;
      float cap___stencil_2_scal;
      float rx___stencil_2_scal;
      float ry___stencil_2_scal;
      float rz___stencil_2_scal;
      float t_chip___stencil_2_scal;
      float chip_height___stencil_2_scal;
      float chip_width___stencil_2_scal;
      float amb_temp___stencil_2_scal;
      float max_slope___stencil_2_scal;
      float dt___stencil_2_scal;
      float ce___stencil_2_scal;
      float cw___stencil_2_scal;
      float cn___stencil_2_scal;
      float cs___stencil_2_scal;
      float ct___stencil_2_scal;
      float cb___stencil_2_scal;
      float cc___stencil_2_scal;
      float stepdivcap___stencil_2_scal;
      int i___f_maps_tout_1_0;
      float dx___stencil_1_scal;
      float dy___stencil_1_scal;
      float dz___stencil_1_scal;
      float cap___stencil_1_scal;
      float rx___stencil_1_scal;
      float ry___stencil_1_scal;
      float rz___stencil_1_scal;
      float t_chip___stencil_1_scal;
      float chip_height___stencil_1_scal;
      float chip_width___stencil_1_scal;
      float amb_temp___stencil_1_scal;
      float max_slope___stencil_1_scal;
      float dt___stencil_1_scal;
      float ce___stencil_1_scal;
      float cw___stencil_1_scal;
      float cn___stencil_1_scal;
      float cs___stencil_1_scal;
      float ct___stencil_1_scal;
      float cb___stencil_1_scal;
      float cc___stencil_1_scal;
      float stepdivcap___stencil_1_scal;
      int i___f_maps_tout_1_1;
      float dx___stencil_0_scal;
      float dy___stencil_0_scal;
      float dz___stencil_0_scal;
      float cap___stencil_0_scal;
      float rx___stencil_0_scal;
      float ry___stencil_0_scal;
      float rz___stencil_0_scal;
      float t_chip___stencil_0_scal;
      float chip_height___stencil_0_scal;
      float chip_width___stencil_0_scal;
      float amb_temp___stencil_0_scal;
      float max_slope___stencil_0_scal;
      float dt___stencil_0_scal;
      float ce___stencil_0_scal;
      float cw___stencil_0_scal;
      float cn___stencil_0_scal;
      float cs___stencil_0_scal;
      float ct___stencil_0_scal;
      float cb___stencil_0_scal;
      float cc___stencil_0_scal;
      float stepdivcap___stencil_0_scal;
      int i___f_maps_tout_1_2;
      int i___f_maps_tout_1_4;
      float sv_v0_s_0_in___f_comp_tout_1_5[49];
      float sv_pin_0_in___f_comp_tout_1_5[7];
      int i___f_maps_tout_1_7;
      float sv_v1_s_0_in___f_comp_tout_1_8[49];
      float sv_pin_0_in___f_comp_tout_1_8[7];
      float v2_s_0___f_comp_tout_1_10[7];
      float pin_0___f_comp_tout_1_10;
      const int s1[] = {503, 252005, 252506, 252507, 252508, 253009, 504511};
      float svec_tout_1_11[2501];
      int s_idx_1;
      int s_idx_2;
      int s_idx_3;
      int s_idx_4;
      float svec_tout_1_12[343];
      float svec_tout_1_13[49];
      float svec_tout_1_14[7];
      float numrows___stencil_2_scal;
      int k_range___stencil_1_scal;
      float layers___stencil_2_scal;
      int k_range___stencil_0_scal;
      int k_range___stencil_3_scal;
      float layers___stencil_0_scal;
      float numcols___stencil_1_scal;
      float numcols___stencil_3_scal;
      float numcols___stencil_0_scal;
      int k_range___stencil_2_scal;
      float layers___stencil_3_scal;
      float numrows___stencil_0_scal;
      float numrows___stencil_3_scal;
      float numrows___stencil_1_scal;
      float numcols___stencil_2_scal;
      float layers___stencil_1_scal;

      [[intel::ivdep]]
      for (int idx = 1; idx < (NX - 2) * (NY - 2) * (NZ - 2); ++idx) {
        // RF4A Begin Inline
        for (s_idx_1 = 1; s_idx_1 <= 7; s_idx_1 += 1) {
          for (s_idx_2 = 1; s_idx_2 <= 7; s_idx_2 += 1) {
            for (s_idx_3 = 1; s_idx_3 <= 7; s_idx_3 += 1) {
              for (s_idx_4 = 1; s_idx_4 <= 7; s_idx_4 += 1) {
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1, s_idx_1,
                                       s_idx_2, s_idx_3, s_idx_4)] =
                      tin_0[F1D2C(1, idx + s1[F1D2C(1, s_idx_1)] +
                                         s1[F1D2C(1, s_idx_2)] +
                                         s1[F1D2C(1, s_idx_3)] +
                                         s1[F1D2C(1, s_idx_4)])];
              }
            }
          }
        }
        for (s_idx_1 = 1; s_idx_1 <= 7; s_idx_1 += 1) {
          for (s_idx_2 = 1; s_idx_2 <= 7; s_idx_2 += 1) {
            for (s_idx_3 = 1; s_idx_3 <= 7; s_idx_3 += 1) {
                svec_tout_1_12[F3D2C(((7 - 1) + 1), ((7 - 1) + 1), 1, 1, 1,
                                     s_idx_1, s_idx_2, s_idx_3)] =
                    pin_0[F1D2C(1, idx + s1[F1D2C(1, s_idx_1)] +
                                       s1[F1D2C(1, s_idx_2)] +
                                       s1[F1D2C(1, s_idx_3)])];
              }
            }
          }
        for (s_idx_1 = 1; s_idx_1 <= 7; s_idx_1 += 1) {
          for (s_idx_2 = 1; s_idx_2 <= 7; s_idx_2 += 1) {
              svec_tout_1_13[F2D2C(((7 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
                  pin_0[F1D2C(1, idx + s1[F1D2C(1, s_idx_1)] +
                                     s1[F1D2C(1, s_idx_2)])];
          }
        }
        for (s_idx_1 = 1; s_idx_1 <= 7; s_idx_1 += 1) {
            svec_tout_1_14[F1D2C(1, s_idx_1)] =
                pin_0[F1D2C(1, idx + s1[F1D2C(1, s_idx_1)])];
        }
        for (i___f_maps_tout_1_7 = 1; i___f_maps_tout_1_7 <= 7;
             i___f_maps_tout_1_7 += 1) {
          for (i___f_maps_tout_1_4 = 1; i___f_maps_tout_1_4 <= 7;
               i___f_maps_tout_1_4 += 1) {
            for (i___f_maps_tout_1_2 = 1; i___f_maps_tout_1_2 <= 7;
                 i___f_maps_tout_1_2 += 1) {
              t_chip___stencil_0_scal = 0.0005;
              chip_height___stencil_0_scal = 0.016;
              chip_width___stencil_0_scal = 0.016;
              amb_temp___stencil_0_scal = 80.0;
              dx___stencil_0_scal =
                  chip_height___stencil_0_scal / numrows___stencil_0_scal;
              dy___stencil_0_scal =
                  chip_width___stencil_0_scal / numcols___stencil_0_scal;
              dz___stencil_0_scal =
                  t_chip___stencil_0_scal / layers___stencil_0_scal;
              cap___stencil_0_scal = 0.5 * 1.75e6 * t_chip___stencil_0_scal *
                                     dx___stencil_0_scal * dy___stencil_0_scal;
              rx___stencil_0_scal =
                  dy___stencil_0_scal /
                  (2.0 * 100 * t_chip___stencil_0_scal * dx___stencil_0_scal);
              ry___stencil_0_scal =
                  dx___stencil_0_scal /
                  (2.0 * 100 * t_chip___stencil_0_scal * dy___stencil_0_scal);
              rz___stencil_0_scal =
                  dz___stencil_0_scal /
                  (100 * dx___stencil_0_scal * dy___stencil_0_scal);
              max_slope___stencil_0_scal =
                  3.0e6 / (0.5 * t_chip___stencil_0_scal * 1.75e6);
              dt___stencil_0_scal = 0.001 / max_slope___stencil_0_scal;
              stepdivcap___stencil_0_scal =
                  dt___stencil_0_scal / cap___stencil_0_scal;
              ce___stencil_0_scal =
                  stepdivcap___stencil_0_scal / rx___stencil_0_scal;
              cw___stencil_0_scal = ce___stencil_0_scal;
              cn___stencil_0_scal =
                  stepdivcap___stencil_0_scal / ry___stencil_0_scal;
              cs___stencil_0_scal = cn___stencil_0_scal;
              ct___stencil_0_scal =
                  stepdivcap___stencil_0_scal / rz___stencil_0_scal;
              ct___stencil_0_scal = cb___stencil_0_scal;
              cc___stencil_0_scal =
                  1.0 - (2.0 * ce___stencil_0_scal + 2.0 * cn___stencil_0_scal +
                         3.0 * ct___stencil_0_scal);
              k_range___stencil_0_scal = ((100 - 1) + 1);
              sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_4,
                                                   i___f_maps_tout_1_2)] =
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 4)] *
                      cc___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 3)] *
                      cn___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 5)] *
                      cs___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 7)] *
                      ce___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 1)] *
                      cw___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 6)] *
                      ct___stencil_0_scal +
                  svec_tout_1_11[F4D2C(((7 - 1) + 1), ((7 - 1) + 1),
                                       ((7 - 1) + 1), 1, 1, 1, 1,
                                       i___f_maps_tout_1_7, i___f_maps_tout_1_4,
                                       i___f_maps_tout_1_2, 2)] *
                      cb___stencil_0_scal +
                  (dt___stencil_0_scal / cap___stencil_0_scal) *
                      svec_tout_1_12[F3D2C(((7 - 1) + 1), ((7 - 1) + 1), 1, 1,
                                           1, i___f_maps_tout_1_7,
                                           i___f_maps_tout_1_4,
                                           i___f_maps_tout_1_2)] +
                  ct___stencil_0_scal * amb_temp___stencil_0_scal;
            }
            sv_pin_0_in___f_comp_tout_1_5[F1D2C(1, i___f_maps_tout_1_4)] =
                svec_tout_1_13[F2D2C(((7 - 1) + 1), 1, 1, i___f_maps_tout_1_7,
                                     i___f_maps_tout_1_4)];
          }
          for (i___f_maps_tout_1_1 = 1; i___f_maps_tout_1_1 <= 7;
               i___f_maps_tout_1_1 += 1) {
            t_chip___stencil_1_scal = 0.0005;
            chip_height___stencil_1_scal = 0.016;
            chip_width___stencil_1_scal = 0.016;
            amb_temp___stencil_1_scal = 80.0;
            dx___stencil_1_scal =
                chip_height___stencil_1_scal / numrows___stencil_1_scal;
            dy___stencil_1_scal =
                chip_width___stencil_1_scal / numcols___stencil_1_scal;
            dz___stencil_1_scal =
                t_chip___stencil_1_scal / layers___stencil_1_scal;
            cap___stencil_1_scal = 0.5 * 1.75e6 * t_chip___stencil_1_scal *
                                   dx___stencil_1_scal * dy___stencil_1_scal;
            rx___stencil_1_scal =
                dy___stencil_1_scal /
                (2.0 * 100 * t_chip___stencil_1_scal * dx___stencil_1_scal);
            ry___stencil_1_scal =
                dx___stencil_1_scal /
                (2.0 * 100 * t_chip___stencil_1_scal * dy___stencil_1_scal);
            rz___stencil_1_scal =
                dz___stencil_1_scal /
                (100 * dx___stencil_1_scal * dy___stencil_1_scal);
            max_slope___stencil_1_scal =
                3.0e6 / (0.5 * t_chip___stencil_1_scal * 1.75e6);
            dt___stencil_1_scal = 0.001 / max_slope___stencil_1_scal;
            stepdivcap___stencil_1_scal =
                dt___stencil_1_scal / cap___stencil_1_scal;
            ce___stencil_1_scal =
                stepdivcap___stencil_1_scal / rx___stencil_1_scal;
            cw___stencil_1_scal = ce___stencil_1_scal;
            cn___stencil_1_scal =
                stepdivcap___stencil_1_scal / ry___stencil_1_scal;
            cs___stencil_1_scal = cn___stencil_1_scal;
            ct___stencil_1_scal =
                stepdivcap___stencil_1_scal / rz___stencil_1_scal;
            ct___stencil_1_scal = cb___stencil_1_scal;
            cc___stencil_1_scal =
                1.0 - (2.0 * ce___stencil_1_scal + 2.0 * cn___stencil_1_scal +
                       3.0 * ct___stencil_1_scal);
            k_range___stencil_1_scal = ((100 - 1) + 1);
            sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                 i___f_maps_tout_1_7,
                                                 i___f_maps_tout_1_1)] =
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 4)] *
                    cc___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 3)] *
                    cn___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 5)] *
                    cs___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 7)] *
                    ce___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 1)] *
                    cw___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 6)] *
                    ct___stencil_1_scal +
                sv_v0_s_0_in___f_comp_tout_1_5[F2D2C(((7 - 1) + 1), 1, 1,
                                                     i___f_maps_tout_1_1, 2)] *
                    cb___stencil_1_scal +
                (dt___stencil_1_scal / cap___stencil_1_scal) *
                    sv_pin_0_in___f_comp_tout_1_5[F1D2C(1,
                                                        i___f_maps_tout_1_1)] +
                ct___stencil_1_scal * amb_temp___stencil_1_scal;
          }
          sv_pin_0_in___f_comp_tout_1_8[F1D2C(1, i___f_maps_tout_1_7)] =
              svec_tout_1_14[F1D2C(1, i___f_maps_tout_1_7)];
        }
        for (i___f_maps_tout_1_0 = 1; i___f_maps_tout_1_0 <= 7;
             i___f_maps_tout_1_0 += 1) {
          t_chip___stencil_2_scal = 0.0005;
          chip_height___stencil_2_scal = 0.016;
          chip_width___stencil_2_scal = 0.016;
          amb_temp___stencil_2_scal = 80.0;
          dx___stencil_2_scal =
              chip_height___stencil_2_scal / numrows___stencil_2_scal;
          dy___stencil_2_scal =
              chip_width___stencil_2_scal / numcols___stencil_2_scal;
          dz___stencil_2_scal =
              t_chip___stencil_2_scal / layers___stencil_2_scal;
          cap___stencil_2_scal = 0.5 * 1.75e6 * t_chip___stencil_2_scal *
                                 dx___stencil_2_scal * dy___stencil_2_scal;
          rx___stencil_2_scal =
              dy___stencil_2_scal /
              (2.0 * 100 * t_chip___stencil_2_scal * dx___stencil_2_scal);
          ry___stencil_2_scal =
              dx___stencil_2_scal /
              (2.0 * 100 * t_chip___stencil_2_scal * dy___stencil_2_scal);
          rz___stencil_2_scal =
              dz___stencil_2_scal /
              (100 * dx___stencil_2_scal * dy___stencil_2_scal);
          max_slope___stencil_2_scal =
              3.0e6 / (0.5 * t_chip___stencil_2_scal * 1.75e6);
          dt___stencil_2_scal = 0.001 / max_slope___stencil_2_scal;
          stepdivcap___stencil_2_scal =
              dt___stencil_2_scal / cap___stencil_2_scal;
          ce___stencil_2_scal =
              stepdivcap___stencil_2_scal / rx___stencil_2_scal;
          cw___stencil_2_scal = ce___stencil_2_scal;
          cn___stencil_2_scal =
              stepdivcap___stencil_2_scal / ry___stencil_2_scal;
          cs___stencil_2_scal = cn___stencil_2_scal;
          ct___stencil_2_scal =
              stepdivcap___stencil_2_scal / rz___stencil_2_scal;
          ct___stencil_2_scal = cb___stencil_2_scal;
          cc___stencil_2_scal =
              1.0 - (2.0 * ce___stencil_2_scal + 2.0 * cn___stencil_2_scal +
                     3.0 * ct___stencil_2_scal);
          k_range___stencil_2_scal = ((100 - 1) + 1);
          v2_s_0___f_comp_tout_1_10[F1D2C(1, i___f_maps_tout_1_0)] =
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 4)] *
                  cc___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 3)] *
                  cn___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 5)] *
                  cs___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 7)] *
                  ce___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 1)] *
                  cw___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 6)] *
                  ct___stencil_2_scal +
              sv_v1_s_0_in___f_comp_tout_1_8[F2D2C(((7 - 1) + 1), 1, 1,
                                                   i___f_maps_tout_1_0, 2)] *
                  cb___stencil_2_scal +
              (dt___stencil_2_scal / cap___stencil_2_scal) *
                  sv_pin_0_in___f_comp_tout_1_8[F1D2C(1, i___f_maps_tout_1_0)] +
              ct___stencil_2_scal * amb_temp___stencil_2_scal;
        }
        pin_0___f_comp_tout_1_10 = pin_0[F1D2C(1, idx)];
        t_chip___stencil_3_scal = 0.0005;
        chip_height___stencil_3_scal = 0.016;
        chip_width___stencil_3_scal = 0.016;
        amb_temp___stencil_3_scal = 80.0;
        dx___stencil_3_scal =
            chip_height___stencil_3_scal / numrows___stencil_3_scal;
        dy___stencil_3_scal =
            chip_width___stencil_3_scal / numcols___stencil_3_scal;
        dz___stencil_3_scal = t_chip___stencil_3_scal / layers___stencil_3_scal;
        cap___stencil_3_scal = 0.5 * 1.75e6 * t_chip___stencil_3_scal *
                               dx___stencil_3_scal * dy___stencil_3_scal;
        rx___stencil_3_scal =
            dy___stencil_3_scal /
            (2.0 * 100 * t_chip___stencil_3_scal * dx___stencil_3_scal);
        ry___stencil_3_scal =
            dx___stencil_3_scal /
            (2.0 * 100 * t_chip___stencil_3_scal * dy___stencil_3_scal);
        rz___stencil_3_scal = dz___stencil_3_scal /
                              (100 * dx___stencil_3_scal * dy___stencil_3_scal);
        max_slope___stencil_3_scal =
            3.0e6 / (0.5 * t_chip___stencil_3_scal * 1.75e6);
        dt___stencil_3_scal = 0.001 / max_slope___stencil_3_scal;
        stepdivcap___stencil_3_scal =
            dt___stencil_3_scal / cap___stencil_3_scal;
        ce___stencil_3_scal = stepdivcap___stencil_3_scal / rx___stencil_3_scal;
        cw___stencil_3_scal = ce___stencil_3_scal;
        cn___stencil_3_scal = stepdivcap___stencil_3_scal / ry___stencil_3_scal;
        cs___stencil_3_scal = cn___stencil_3_scal;
        ct___stencil_3_scal = stepdivcap___stencil_3_scal / rz___stencil_3_scal;
        ct___stencil_3_scal = cb___stencil_3_scal;
        cc___stencil_3_scal =
            1.0 - (2.0 * ce___stencil_3_scal + 2.0 * cn___stencil_3_scal +
                   3.0 * ct___stencil_3_scal);
        k_range___stencil_3_scal = ((100 - 1) + 1);
        tout_1[F1D2C(1, idx)] =
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 4)] * cc___stencil_3_scal +
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 3)] * cn___stencil_3_scal +
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 5)] * cs___stencil_3_scal +
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 7)] * ce___stencil_3_scal +
            (*v2_s_0___f_comp_tout_1_10) * cw___stencil_3_scal +
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 6)] * ct___stencil_3_scal +
            v2_s_0___f_comp_tout_1_10[F1D2C(1, 2)] * cb___stencil_3_scal +
            (dt___stencil_3_scal / cap___stencil_3_scal) *
                pin_0___f_comp_tout_1_10 +
            ct___stencil_3_scal * amb_temp___stencil_3_scal;
        // RF4A End Inline
      }
    });
  });

  auto start = event.get_profiling_info<info::event_profiling::command_start>();
  auto end = event.get_profiling_info<info::event_profiling::command_end>();
  auto time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
