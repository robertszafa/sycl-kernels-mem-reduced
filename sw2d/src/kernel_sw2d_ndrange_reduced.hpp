#include "CL/sycl/access/access.hpp"
#include "CL/sycl/properties/accessor_properties.hpp"
#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "sw2d_sizes.hpp"

using namespace sycl;

double sw2d_ndrange_reduced(queue &q, const std::vector<int> &wet, const std::vector<float> &eta,
                            const std::vector<float> &u, const std::vector<float> &v,
                            const std::vector<float> &h, std::vector<float> &etann,
                            std::vector<float> &un, std::vector<float> &vn) {
  range<1> array_range{ARRAY_SIZE};

  buffer wet_buf(wet);
  buffer eta_buf(eta);
  buffer u_buf(u);
  buffer v_buf(v);
  buffer h_buf(h);
  // Output
  buffer etann_buf(etann);
  buffer un_buf(un);
  buffer vn_buf(vn);

  auto event = q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor wet_0(wet_buf, hnd, read_only);
    accessor eta_0(eta_buf, hnd, read_only);
    accessor u_0(u_buf, hnd, read_only);
    accessor v_0(v_buf, hnd, read_only);
    accessor h_0(h_buf, hnd, read_only);

    accessor etann_1(etann_buf, hnd, write_only, no_init);
    accessor un_1(un_buf, hnd, write_only, no_init);
    accessor vn_1(vn_buf, hnd, write_only, no_init);

    hnd.parallel_for<class sw2d_superkernel>(DOMAIN_SIZE, [=](id<1> item_id) [[intel::kernel_args_restrict]] {
          const int global_id = item_id + 1;

          const float g___dyn_shapiro_map_49_scal = 9.81;
          const float dt___dyn_shapiro_map_49_scal = 0.1;
          const float dx___dyn_shapiro_map_49_scal = 10.0;
          const float dy___dyn_shapiro_map_49_scal = 10.0;
          const float dt___dyn_shapiro_map_75_scal = 0.1;
          const float dx___dyn_shapiro_map_75_scal = 10.0;
          const float dy___dyn_shapiro_map_75_scal = 10.0;
          const float eps___dyn_shapiro_map_92_scal = 0.05;
          float u_0___f_comp_un_1_vn_1_2;
          float du___dyn_1;
          float v_0___f_comp_un_1_vn_1_2;
          float dv___dyn_1;
          float term1___shapiro;
          float term2___shapiro;
          float term3___shapiro;
          float hep___dyn;
          float hen___dyn;
          float hue___dyn;
          float hwp___dyn;
          float hwn___dyn;
          float huw___dyn;
          float hnp___dyn;
          float hnn___dyn;
          float hvn___dyn;
          float hsp___dyn;
          float hsn___dyn;
          float hvs___dyn;
          int i___f_maps_etann_1_0;
          int i___f_maps_etann_1_8;
          int i___f_maps_etann_1_10;
          int svec_etann_1_19[6];
          float sv_v_0_in___f_comp_etann_1_11[2];
          int i___f_maps_etann_1_2;
          int i___f_maps_etann_1_5;
          float sv_u_0_in___f_comp_etann_1_6[2];
          float sv_du___dyn_1_in[2];
          float sv_dv___dyn_1_in[2];
          int i___f_maps_etann_1_13;
          float sv_un_s_0_in___f_comp____2871b75d[10];
          float svec_etann_1_21[25];
          float sv_vn_s_0_in___f_comp____22c6c54b[10];
          float sv_eta_0_in___f_comp_etann_1_14[5];
          int wet_s_1[5];
          float etan_s_0___f_comp_etann_1_16[5];

          // THESE OFFSETS ARE HARDCODED FOR SQUARE DOMAINS ONLY
          const int s1[] = {NX + 3, NX + 4, NX * 2 + 5};
          const int s3[] = {1, NX + 3};
          const int s5[] = {1, NX + 2, NX + 3, NX + 4, NX * 2 + 4};

          float svec_etann_1_17[10];
          float svec_etann_1_18[30];
          float svec_etann_1_20[10];
          float svec_etann_1_26[5];
          float eta_s_0[3];
          int wet_s_0[3];
      //  RF4A Begin Inline
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
            wet_s_1[F1D2C(1, s_idx_1)] = wet_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)])];
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
#pragma unroll
            for (int s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
              svec_etann_1_17[F2D2C(((5 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
                  u_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)] + s3[F1D2C(1, s_idx_2)])];
            }
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
#pragma unroll
            for (int s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
#pragma unroll
              for (int s_idx_3 = 1; s_idx_3 <= 3; s_idx_3 += 1) {
                svec_etann_1_18[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1, s_idx_1, s_idx_2,
                                      s_idx_3)] =
                    eta_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)] + s3[F1D2C(1, s_idx_2)] +
                                       s1[F1D2C(1, s_idx_3)])];
              }
            }
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
#pragma unroll
            for (int s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
#pragma unroll
              for (int s_idx_3 = 1; s_idx_3 <= 3; s_idx_3 += 1) {
                svec_etann_1_19[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1, s_idx_1, s_idx_2,
                                      s_idx_3)] =
                    wet_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)] + s3[F1D2C(1, s_idx_2)] +
                                       s1[F1D2C(1, s_idx_3)])];
              }
            }
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
#pragma unroll
            for (int s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
              svec_etann_1_20[F2D2C(((5 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
                  v_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)] + s3[F1D2C(1, s_idx_2)])];
            }
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
#pragma unroll
            for (int s_idx_2 = 1; s_idx_2 <= 5; s_idx_2 += 1) {
              svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
                  h_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)] + s5[F1D2C(1, s_idx_2)])];
            }
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 5; s_idx_1 += 1) {
            svec_etann_1_26[F1D2C(1, s_idx_1)] = eta_0[F1D2C(1, global_id + s5[F1D2C(1, s_idx_1)])];
          }
#pragma unroll
          for (int i___f_maps_etann_1_13 = 1; i___f_maps_etann_1_13 <= 5;
               i___f_maps_etann_1_13 += 1) {
#pragma unroll
            for (int i___f_maps_etann_1_5 = 1; i___f_maps_etann_1_5 <= 2;
                 i___f_maps_etann_1_5 += 1) {
              sv_u_0_in___f_comp_etann_1_6[F1D2C(1, i___f_maps_etann_1_5)] = svec_etann_1_17[F2D2C(
                  ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13, i___f_maps_etann_1_5)];
              sv_du___dyn_1_in[F1D2C(1, i___f_maps_etann_1_5)] =
                  -dt___dyn_shapiro_map_49_scal * g___dyn_shapiro_map_49_scal *
                  (&svec_etann_1_18[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1,
                                          i___f_maps_etann_1_13, i___f_maps_etann_1_5, 3)] -
                   &svec_etann_1_18[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1,
                                          i___f_maps_etann_1_13, i___f_maps_etann_1_5, 1)]) /
                  dx___dyn_shapiro_map_49_scal;
            }
#pragma unroll
            for (int i___f_maps_etann_1_2 = 1; i___f_maps_etann_1_2 <= 2;
                 i___f_maps_etann_1_2 += 1) {
              if (svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_2, 1)] == 1) {
                if ((svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_2, 3)] == 1) ||
                    (sv_du___dyn_1_in[F1D2C(1, i___f_maps_etann_1_2)] > 0.0))
                  sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                      ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13, i___f_maps_etann_1_2)] =
                      sv_u_0_in___f_comp_etann_1_6[F1D2C(1, i___f_maps_etann_1_2)] +
                      sv_du___dyn_1_in[F1D2C(1, i___f_maps_etann_1_2)];
              } else {
                if ((svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_2, 3)] == 1) &&
                    (sv_du___dyn_1_in[F1D2C(1, i___f_maps_etann_1_2)] < 0.0))
                  sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                      ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13, i___f_maps_etann_1_2)] =
                      sv_u_0_in___f_comp_etann_1_6[F1D2C(1, i___f_maps_etann_1_2)] +
                      sv_du___dyn_1_in[F1D2C(1, i___f_maps_etann_1_2)];
              }
            }
#pragma unroll
            for (int i___f_maps_etann_1_10 = 1; i___f_maps_etann_1_10 <= 2;
                 i___f_maps_etann_1_10 += 1) {
              sv_dv___dyn_1_in[F1D2C(1, i___f_maps_etann_1_10)] =
                  -dt___dyn_shapiro_map_49_scal * g___dyn_shapiro_map_49_scal *
                  (&svec_etann_1_18[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1,
                                          i___f_maps_etann_1_13, i___f_maps_etann_1_10, 2)] -
                   &svec_etann_1_18[F3D2C(((5 - 1) + 1), ((2 - 1) + 1), 1, 1, 1,
                                          i___f_maps_etann_1_13, i___f_maps_etann_1_10, 1)]) /
                  dy___dyn_shapiro_map_49_scal;
              sv_v_0_in___f_comp_etann_1_11[F1D2C(1, i___f_maps_etann_1_10)] =
                  svec_etann_1_20[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13,
                                        i___f_maps_etann_1_10)];
            }
#pragma unroll
            for (int i___f_maps_etann_1_8 = 1; i___f_maps_etann_1_8 <= 2;
                 i___f_maps_etann_1_8 += 1) {
              if (svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_8, 1)] == 1) {
                if ((svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_8, 2)] == 1) ||
                    (sv_dv___dyn_1_in[F1D2C(1, i___f_maps_etann_1_8)] > 0.0))
                  sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                      ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13, i___f_maps_etann_1_8)] =
                      sv_v_0_in___f_comp_etann_1_11[F1D2C(1, i___f_maps_etann_1_8)] +
                      sv_dv___dyn_1_in[F1D2C(1, i___f_maps_etann_1_8)];
              } else {
                if ((svec_etann_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_etann_1_8, 2)] == 1) &&
                    (sv_dv___dyn_1_in[F1D2C(1, i___f_maps_etann_1_8)] < 0.0))
                  sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                      ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_13, i___f_maps_etann_1_8)] =
                      sv_v_0_in___f_comp_etann_1_11[F1D2C(1, i___f_maps_etann_1_8)] +
                      sv_dv___dyn_1_in[F1D2C(1, i___f_maps_etann_1_8)];
              }
            }
            sv_eta_0_in___f_comp_etann_1_14[F1D2C(1, i___f_maps_etann_1_13)] =
                svec_etann_1_26[F1D2C(1, i___f_maps_etann_1_13)];
          }
#pragma unroll
          for (int i___f_maps_etann_1_0 = 1; i___f_maps_etann_1_0 <= 5; i___f_maps_etann_1_0 += 1) {
            hep___dyn = 0.5 *
                        (sv_un_s_0_in___f_comp____2871b75d[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 2)] +
                         (float)fabs(sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 2)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 3)];
            hen___dyn = 0.5 *
                        (sv_un_s_0_in___f_comp____2871b75d[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 2)] -
                         (float)fabs(sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 2)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 5)];
            hue___dyn = hep___dyn + hen___dyn;
            hwp___dyn = 0.5 *
                        (sv_un_s_0_in___f_comp____2871b75d[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 1)] +
                         (float)fabs(sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 1)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 1)];
            hwn___dyn = 0.5 *
                        (sv_un_s_0_in___f_comp____2871b75d[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 1)] -
                         (float)fabs(sv_un_s_0_in___f_comp____2871b75d[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 1)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 3)];
            huw___dyn = hwp___dyn + hwn___dyn;
            hnp___dyn = 0.5 *
                        (sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 2)] +
                         (float)fabs(sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 2)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 3)];
            hnn___dyn = 0.5 *
                        (sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 2)] -
                         (float)fabs(sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 2)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 4)];
            hvn___dyn = hnp___dyn + hnn___dyn;
            hsp___dyn = 0.5 *
                        (sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 1)] +
                         (float)fabs(sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 1)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 2)];
            hsn___dyn = 0.5 *
                        (sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(((5 - 1) + 1), 1, 1,
                                                                 i___f_maps_etann_1_0, 1)] -
                         (float)fabs(sv_vn_s_0_in___f_comp____22c6c54b[F2D2C(
                             ((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 1)])) *
                        svec_etann_1_21[F2D2C(((5 - 1) + 1), 1, 1, i___f_maps_etann_1_0, 3)];
            hvs___dyn = hsp___dyn + hsn___dyn;
            etan_s_0___f_comp_etann_1_16[F1D2C(1, i___f_maps_etann_1_0)] =
                sv_eta_0_in___f_comp_etann_1_14[F1D2C(1, i___f_maps_etann_1_0)] -
                dt___dyn_shapiro_map_75_scal * (hue___dyn - huw___dyn) /
                    dx___dyn_shapiro_map_75_scal -
                dt___dyn_shapiro_map_75_scal * (hvn___dyn - hvs___dyn) /
                    dy___dyn_shapiro_map_75_scal;
          }
          if (wet_s_1[F1D2C(1, 3)] == 1) {
            term1___shapiro = (1.0 - 0.25 * eps___dyn_shapiro_map_92_scal *
                                         (wet_s_1[F1D2C(1, 5)] + (*wet_s_1) + wet_s_1[F1D2C(1, 4)] +
                                          wet_s_1[F1D2C(1, 2)])) *
                              etan_s_0___f_comp_etann_1_16[F1D2C(1, 3)];
            term2___shapiro = 0.25 * eps___dyn_shapiro_map_92_scal *
                              (wet_s_1[F1D2C(1, 5)] * etan_s_0___f_comp_etann_1_16[F1D2C(1, 5)] +
                               (*wet_s_1) * (*etan_s_0___f_comp_etann_1_16));
            term3___shapiro = 0.25 * eps___dyn_shapiro_map_92_scal *
                              (wet_s_1[F1D2C(1, 4)] * etan_s_0___f_comp_etann_1_16[F1D2C(1, 4)] +
                               wet_s_1[F1D2C(1, 2)] * etan_s_0___f_comp_etann_1_16[F1D2C(1, 2)]);
            etann_1[F1D2C(1, global_id)] = term1___shapiro + term2___shapiro + term3___shapiro;
          } else {
            etann_1[F1D2C(1, global_id)] = etan_s_0___f_comp_etann_1_16[F1D2C(1, 3)];
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 3; s_idx_1 += 1) {
            eta_s_0[F1D2C(1, s_idx_1)] = eta_0[F1D2C(1, global_id + s1[F1D2C(1, s_idx_1)])];
          }
#pragma unroll
          for (int s_idx_1 = 1; s_idx_1 <= 3; s_idx_1 += 1) {
            wet_s_0[F1D2C(1, s_idx_1)] = wet_0[F1D2C(1, global_id + s1[F1D2C(1, s_idx_1)])];
          }
          u_0___f_comp_un_1_vn_1_2 = u_0[F1D2C(1, global_id)];
          du___dyn_1 = -dt___dyn_shapiro_map_49_scal * g___dyn_shapiro_map_49_scal *
                       (eta_s_0[F1D2C(1, 3)] - (*eta_s_0)) / dx___dyn_shapiro_map_49_scal;
          dv___dyn_1 = -dt___dyn_shapiro_map_49_scal * g___dyn_shapiro_map_49_scal *
                       (eta_s_0[F1D2C(1, 2)] - (*eta_s_0)) / dy___dyn_shapiro_map_49_scal;
          v_0___f_comp_un_1_vn_1_2 = v_0[F1D2C(1, global_id)];
          if ((*wet_s_0) == 1) {
            if ((wet_s_0[F1D2C(1, 3)] == 1) || (du___dyn_1 > 0.0))
              un_1[F1D2C(1, global_id)] = u_0___f_comp_un_1_vn_1_2 + du___dyn_1;
          } else {
            if ((wet_s_0[F1D2C(1, 3)] == 1) && (du___dyn_1 < 0.0))
              un_1[F1D2C(1, global_id)] = u_0___f_comp_un_1_vn_1_2 + du___dyn_1;
          }
          if ((*wet_s_0) == 1) {
            if ((wet_s_0[F1D2C(1, 2)] == 1) || (dv___dyn_1 > 0.0))
              vn_1[F1D2C(1, global_id)] = v_0___f_comp_un_1_vn_1_2 + dv___dyn_1;
          } else {
            if ((wet_s_0[F1D2C(1, 2)] == 1) && (dv___dyn_1 < 0.0))
              vn_1[F1D2C(1, global_id)] = v_0___f_comp_un_1_vn_1_2 + dv___dyn_1;
          }
        });
  });

  auto start = event.get_profiling_info<info::event_profiling::command_start>();
  auto end = event.get_profiling_info<info::event_profiling::command_end>();
  double time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
