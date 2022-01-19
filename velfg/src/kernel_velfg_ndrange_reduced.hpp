#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "velfg_sizes.hpp"

using namespace sycl;

void velfg_ndrange_reduced(queue &q, const std::vector<float> &u, const std::vector<float> &v,
                           const std::vector<float> &w, const std::vector<float> &dx1,
                           const std::vector<float> &dy1, const std::vector<float> &dzn,
                           const std::vector<float> &dzs, std::vector<float> &f,
                           std::vector<float> &g, std::vector<float> &h) {

  range<1> num_items{f.size()};

  // Create buffers that hold the data shared between the host and the devices.
  // The buffer destructor is responsible to copy the data back to host when it
  // goes out of scope.
  buffer u_buf(u);
  buffer v_buf(v);
  buffer w_buf(w);
  buffer dx1_buf(dx1);
  buffer dy1_buf(dy1);
  buffer dzn_buf(dzn);
  buffer dzs_buf(dzs);
  buffer f_buf(f.data(), num_items);
  buffer g_buf(g.data(), num_items);
  buffer h_buf(h.data(), num_items);

  // DPC++ supports unnamed lambda kernel by default.
  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);

    // Global memory accessor. For local mem, use local_accessor<>
    const accessor u_0(u_buf, hnd, read_only);
    const accessor v_0(v_buf, hnd, read_only);
    const accessor w_0(w_buf, hnd, read_only);
    const accessor dx1_0(dx1_buf, hnd, read_only);
    const accessor dy1_0(dy1_buf, hnd, read_only);
    const accessor dzn_0(dzn_buf, hnd, read_only);
    const accessor dzs_0(dzs_buf, hnd, read_only);
    // no_init lets the runtime know that the host f, g, h values don't need to be transfered to the
    // device by default they are, e.g. the kernel could end up not overriding all values.
    accessor f_1(f_buf, hnd, write_only, no_init);
    accessor g_1(g_buf, hnd, write_only, no_init);
    accessor h_1(h_buf, hnd, write_only, no_init);

    hnd.parallel_for<class velfg_superkernel>(DOMAIN_SIZE, [=](id<1> item_id) [[intel::kernel_args_restrict]] {
      const int global_id = item_id + 1;

      const int kp___velfg_map_76_scal = KP;
      const int u0___velfg_map_76_scal = 0;
      const int kp___velfg_map_133_scal = KP;
      const int u0___velfg_map_133_scal = 0;
      const int kp___velfg_map_218_scal = KP;
      const float vn___velfg_map_218_scal = 15.83 * 0.000001;

      float covx1___velfg_map_218_scal = 0;
      int i___velfg_map_218_scal = 0;
      int j___velfg_map_218_scal = 0;
      int k___velfg_map_218_scal = 0;
      float covy1___velfg_map_218_scal = 0;
      float covz1___velfg_map_218_scal = 0;
      float covc___velfg_map_218_scal = 0;
      float df___velfg_map_218_scal = 0;
      int j_range___velfg_map_218_scal = 0;
      int i_range___velfg_map_218_scal = 0;
      int k_rel___velfg_map_218_scal = 0;
      int j_rel___velfg_map_218_scal = 0;
      int i_rel___velfg_map_218_scal = 0;
      float dfu1___velfg_map_218 = 0;
      float dfv1___velfg_map_218 = 0;
      float dfw1___velfg_map_218 = 0;
      float nou7___velfg_map_133 = 0;
      float diu7___velfg_map_133 = 0;
      float nou8___velfg_map_133 = 0;
      float diu8___velfg_map_133 = 0;
      int i___f_maps_f_1_g_1_h_1_1 = 0;
      float nou1___velfg_map_76 = 0;
      float diu1___velfg_map_76 = 0;
      float nou5___velfg_map_76 = 0;
      float diu5___velfg_map_76 = 0;
      float nou9___velfg_map_76 = 0;
      float diu9___velfg_map_76 = 0;
      float nou2___velfg_map_76 = 0;
      float diu2___velfg_map_76 = 0;
      float nou3___velfg_map_76 = 0;
      float diu3___velfg_map_76 = 0;
      float nou4___velfg_map_76 = 0;
      float diu4___velfg_map_76 = 0;
      float nou6___velfg_map_76 = 0;
      float diu6___velfg_map_76 = 0;

      float cov1_s_0___f_comp_f_1____a1652fff[2];
      float cov2_s_0___f_comp_f_1____71cf34a3[2];
      float cov3_s_0___f_comp_f_1____571b4b3a[2];
      float diu1_s_0___f_comp_f_1____f81d980d[2];
      float diu2_s_0___f_comp_f_1____e05a5b92[2];
      float diu3_s_0___f_comp_f_1____d0299603[2];
      float cov4_s_0___f_comp_f_1____4c58ee66[2];
      float cov5_s_0___f_comp_f_1____91f7197a[2];
      float cov6_s_0___f_comp_f_1____dcd2e1f3[2];
      float diu4_s_0___f_comp_f_1____4f05f130[2];
      float diu5_s_0___f_comp_f_1____8ac031a2[2];
      float diu6_s_0___f_comp_f_1____b1f35dc5[2];
      float cov7_s_0___f_comp_f_1____f85a90f2[2];
      float cov8_s_0___f_comp_f_1____187de70[2];
      float cov9_s_0___f_comp_f_1____44f8210b[2];
      float diu7_s_0___f_comp_f_1____9bfc5fb8[2];
      float diu8_s_0___f_comp_f_1____6399bded[2];
      float diu9_s_0___f_comp_f_1____cb19f377[2];

#if IP == 10 && JP == 10
      const int s1[] = {13, 14, 25, 157};
      const int s2[] = {13, 145, 146, 156, 157};
      const int s3[] = {13, 145, 156, 157, 168};
      const int s4[] = {156, 300};
      const int s5[] = {145, 289};
      const int s6[] = {145, 156, 157};
      const int s8[] = {198, 199};
      const int s11[] = {183, 184};
#elif IP == 100 && JP == 100
      const int s1[] = {103,104,205,10507};
      const int s2[] = {103,10405,10406,10506,10507};
      const int s3[] = {103,10405,10506,10507,10608};
      const int s4[] = {10506,20910};
      const int s5[] = {10405,20809};
      const int s6[] = {10405,10506,10507};
      const int s8[] = {10818,10819};
      const int s11[] = {10713,10714};
#elif IP == 200 && JP == 200
      const int s1[] = {203,204,405,41007};
      const int s2[] = {203,40805,40806,41006,41007};
      const int s3[] = {203,40805,41006,41007,41208};
      const int s4[] = {41006,81810};
      const int s5[] = {40805,81609};
      const int s6[] = {40805,41006,41007};
      const int s8[] = {41618,41619};
      const int s11[] = {41413,41414};
#elif IP == 300 && JP == 300
      const int s1[] = {303,304,605,91507};
      const int s2[] = {303,91205,91206,91506,91507};
      const int s3[] = {303,91205,91506,91507,91808};
      const int s4[] = {91506,182710};
      const int s5[] = {91205,182409};
      const int s6[] = {91205,91506,91507};
      const int s8[] = {92418,92419};
      const int s11[] = {92113,92114};
#else
#error "Domain size not generated (the stencil offsets come hardcoded from our toolchain)."
#endif

      int s_idx_1 = 0;
      int s_idx_2 = 0;
      float svec_f_1_g_1_h_1_17[10];
      float svec_f_1_g_1_h_1_18[10];
      float svec_f_1_g_1_h_1_19[8];
      float svec_f_1_g_1_h_1_32[4];
      float svec_f_1_g_1_h_1_33[6];
      float svec_f_1_g_1_h_1_34[4];

      //    !RF4A Begin Inline
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 5; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              u_0[F1D2C(1, global_id + s8[F1D2C(1, s_idx_1)] + s3[F1D2C(1, s_idx_2)])];
        }
      }
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 5; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              v_0[F1D2C(1, global_id + s8[F1D2C(1, s_idx_1)] + s2[F1D2C(1, s_idx_2)])];
        }
      }
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 4; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              w_0[F1D2C(1, global_id + s8[F1D2C(1, s_idx_1)] + s1[F1D2C(1, s_idx_2)])];
        }
      }
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_32[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              u_0[F1D2C(1, global_id + s11[F1D2C(1, s_idx_1)] + s4[F1D2C(1, s_idx_2)])];
        }
      }
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 3; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_33[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              w_0[F1D2C(1, global_id + s11[F1D2C(1, s_idx_1)] + s6[F1D2C(1, s_idx_2)])];
        }
      }
    #pragma unroll
      for (s_idx_1 = 1; s_idx_1 <= 2; s_idx_1 += 1) {
        for (s_idx_2 = 1; s_idx_2 <= 2; s_idx_2 += 1) {
          svec_f_1_g_1_h_1_34[F2D2C(((2 - 1) + 1), 1, 1, s_idx_1, s_idx_2)] =
              v_0[F1D2C(1, global_id + s11[F1D2C(1, s_idx_1)] + s5[F1D2C(1, s_idx_2)])];
        }
      }

      #pragma unroll
      for (i___f_maps_f_1_g_1_h_1_1 = 1; i___f_maps_f_1_g_1_h_1_1 <= 2;
           i___f_maps_f_1_g_1_h_1_1 += 1) {
        const int j_vel2_range___velfg_m___4b6e60e4 = ((10 - 1) + 1);
        const int i_vel2_range___velfg_m___ea66ec4a = ((10 - 1) + 1);
        const int k_vel2_rel___velfg_map_76_scal =
            (global_id / (j_vel2_range___velfg_m___4b6e60e4 * i_vel2_range___velfg_m___ea66ec4a));
        const int k_vel2___velfg_map_76_scal = k_vel2_rel___velfg_map_76_scal + 1;
        const int j_vel2_rel___velfg_map_76_scal =
            ((global_id - (k_vel2_rel___velfg_map_76_scal * (j_vel2_range___velfg_m___4b6e60e4 *
                                                             i_vel2_range___velfg_m___ea66ec4a))) /
             i_vel2_range___velfg_m___ea66ec4a);
        const int j_vel2___velfg_map_76_scal = j_vel2_rel___velfg_map_76_scal + 1;
        const int i_vel2_rel___velfg_map_76_scal =
            ((global_id - (k_vel2_rel___velfg_map_76_scal * (j_vel2_range___velfg_m___4b6e60e4 *
                                                             i_vel2_range___velfg_m___ea66ec4a))) -
             (j_vel2_rel___velfg_map_76_scal * i_vel2_range___velfg_m___ea66ec4a));
        const int i_vel2___velfg_map_76_scal = i_vel2_rel___velfg_map_76_scal + 1;

        /**
            ***************************
                map76
            ***************************
        */
        if ((k_vel2___velfg_map_76_scal < kp___velfg_map_76_scal)) {
          nou1___velfg_map_76 =
              (svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)] +
               svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
              2.;

          diu1___velfg_map_76 =
              (-svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)] +
               svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
              dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)];
          diu1_s_0___f_comp_f_1____f81d980d[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              diu1___velfg_map_76;

          nou5___velfg_map_76 =
              (svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)] +
               svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 5)]) /
              2.;

          diu5___velfg_map_76 =
              (-svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)] +
               svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 5)]) /
              dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)];

          diu5_s_0___f_comp_f_1____8ac031a2[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              diu5___velfg_map_76;

          nou9___velfg_map_76 =
              (svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
               svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
              2.;
          diu9___velfg_map_76 =
              (-svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
               svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
              dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal)];
          diu9_s_0___f_comp_f_1____cb19f377[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              diu9___velfg_map_76;

          cov1_s_0___f_comp_f_1____a1652fff[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              nou1___velfg_map_76 * diu1___velfg_map_76;

          cov5_s_0___f_comp_f_1____91f7197a[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              nou5___velfg_map_76 * diu5___velfg_map_76;

          cov9_s_0___f_comp_f_1____44f8210b[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              nou9___velfg_map_76 * diu9___velfg_map_76;

          nou2___velfg_map_76 =
              (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal + 1)] *
                   svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)] +
               dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)] *
                   svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)]) /
              (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)] +
               dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal + 1)]);

          diu2_s_0___f_comp_f_1____e05a5b92[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              2. *
              (-svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)] +
               svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
              (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal - 1)] +
               dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)]);

          cov2_s_0___f_comp_f_1____71cf34a3[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              nou2___velfg_map_76 * diu2___velfg_map_76;
        }

        nou3___velfg_map_76 =
            (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal + 1)] *
                 svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)] *
                 svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)]) /
            (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)] +
             dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal + 1)]);
        diu3___velfg_map_76 =
            (-svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)]) /
            dzs_0[F1D2C(-1, k_vel2___velfg_map_76_scal - 1)];
        diu3_s_0___f_comp_f_1____d0299603[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] = diu3___velfg_map_76;

        cov3_s_0___f_comp_f_1____571b4b3a[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
            nou3___velfg_map_76 * diu3___velfg_map_76;

        if ((k_vel2___velfg_map_76_scal < kp___velfg_map_76_scal)) {
          nou4___velfg_map_76 =
              (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal + 1)] *
                   svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)] +
               dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)] *
                   svec_f_1_g_1_h_1_17[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 5)]) /
              (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)] +
               dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal + 1)]);
          diu4___velfg_map_76 =
              2. *
              (-svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 4)] +
               svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 5)]) /
              (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal - 1)] +
               dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)]);
          diu4_s_0___f_comp_f_1____4f05f130[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              diu4___velfg_map_76;
          cov4_s_0___f_comp_f_1____4c58ee66[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
              (nou4___velfg_map_76 - u0___velfg_map_76_scal) * diu4___velfg_map_76;
        }

        nou6___velfg_map_76 =
            (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal + 1)] *
                 svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)] *
                 svec_f_1_g_1_h_1_19[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)]) /
            (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)] +
             dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal + 1)]);

        diu6___velfg_map_76 =
            (-svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             svec_f_1_g_1_h_1_18[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 5)]) /
            dzs_0[F1D2C(-1, k_vel2___velfg_map_76_scal - 1)];
        diu6_s_0___f_comp_f_1____b1f35dc5[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] = diu6___velfg_map_76;

        cov6_s_0___f_comp_f_1____dcd2e1f3[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
            nou6___velfg_map_76 * diu6___velfg_map_76;

        /**
        ***************************
            map133
        ***************************
        */
        nou7___velfg_map_133 =
            (dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal + 1)] *
                 svec_f_1_g_1_h_1_32[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal)] *
                 svec_f_1_g_1_h_1_32[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)]) /
            (dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal)] +
             dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal + 1)]);
        diu7___velfg_map_133 =
            2. *
            (-svec_f_1_g_1_h_1_33[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)] +
             svec_f_1_g_1_h_1_33[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)]) /
            (dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal - 1)] +
             dx1_0[F1D2C(-1, i_vel2___velfg_map_76_scal)]);
        diu7_s_0___f_comp_f_1____9bfc5fb8[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
            diu7___velfg_map_133;
        cov7_s_0___f_comp_f_1____f85a90f2[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
            (nou7___velfg_map_133 - u0___velfg_map_133_scal) * diu7___velfg_map_133;

        nou8___velfg_map_133 =
            (dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal + 1)] *
                 svec_f_1_g_1_h_1_34[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal)] *
                 svec_f_1_g_1_h_1_34[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 2)]) /
            (dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal)] +
             dzn_0[F1D2C(-1, k_vel2___velfg_map_76_scal + 1)]);
        diu8___velfg_map_133 =
            2. *
            (-svec_f_1_g_1_h_1_33[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 1)] +
             svec_f_1_g_1_h_1_33[F2D2C(((2 - 1) + 1), 1, 1, i___f_maps_f_1_g_1_h_1_1, 3)]) /
            (dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal - 1)] +
             dy1_0[F1D2C(0, j_vel2___velfg_map_76_scal)]);
        diu8_s_0___f_comp_f_1____6399bded[F1D2C(1, i___f_maps_f_1_g_1_h_1_1)] =
            diu8___velfg_map_133;
      }

      j_range___velfg_map_218_scal = ((10 - 1) + 1);
      i_range___velfg_map_218_scal = ((10 - 1) + 1);
      k_rel___velfg_map_218_scal =
          (global_id / (j_range___velfg_map_218_scal * i_range___velfg_map_218_scal));
      k___velfg_map_218_scal = k_rel___velfg_map_218_scal + 1;
      j_rel___velfg_map_218_scal =
          ((global_id - (k_rel___velfg_map_218_scal *
                         (j_range___velfg_map_218_scal * i_range___velfg_map_218_scal))) /
           i_range___velfg_map_218_scal);
      j___velfg_map_218_scal = j_rel___velfg_map_218_scal + 1;
      i_rel___velfg_map_218_scal =
          ((global_id - (k_rel___velfg_map_218_scal *
                         (j_range___velfg_map_218_scal * i_range___velfg_map_218_scal))) -
           (j_rel___velfg_map_218_scal * i_range___velfg_map_218_scal));
      i___velfg_map_218_scal = i_rel___velfg_map_218_scal + 1;
      covx1___velfg_map_218_scal =
          (dx1_0[F1D2C(-1, i___velfg_map_218_scal + 1)] * (*cov1_s_0___f_comp_f_1____a1652fff) +
           dx1_0[F1D2C(-1, i___velfg_map_218_scal)] *
               cov1_s_0___f_comp_f_1____a1652fff[F1D2C(1, 2)]) /
          (dx1_0[F1D2C(-1, i___velfg_map_218_scal)] + dx1_0[F1D2C(-1, i___velfg_map_218_scal + 1)]);
      covy1___velfg_map_218_scal =
          ((*cov2_s_0___f_comp_f_1____71cf34a3) + cov2_s_0___f_comp_f_1____71cf34a3[F1D2C(1, 2)]) /
          2.;
      covz1___velfg_map_218_scal =
          ((*cov3_s_0___f_comp_f_1____571b4b3a) + cov3_s_0___f_comp_f_1____571b4b3a[F1D2C(1, 2)]) /
          2.;
      covc___velfg_map_218_scal =
          covx1___velfg_map_218_scal + covy1___velfg_map_218_scal + covz1___velfg_map_218_scal;
      dfu1___velfg_map_218 =
          2. *
              (-(*diu1_s_0___f_comp_f_1____f81d980d) +
               diu1_s_0___f_comp_f_1____f81d980d[F1D2C(1, 2)]) /
              (dx1_0[F1D2C(-1, i___velfg_map_218_scal)] +
               dx1_0[F1D2C(-1, i___velfg_map_218_scal + 1)]) +
          (-(*diu2_s_0___f_comp_f_1____e05a5b92) + diu2_s_0___f_comp_f_1____e05a5b92[F1D2C(1, 2)]) /
              dy1_0[F1D2C(0, j___velfg_map_218_scal)] +
          (-(*diu3_s_0___f_comp_f_1____d0299603) + diu3_s_0___f_comp_f_1____d0299603[F1D2C(1, 2)]) /
              dzn_0[F1D2C(-1, k___velfg_map_218_scal)];
      df___velfg_map_218_scal = vn___velfg_map_218_scal * dfu1___velfg_map_218;
      f_1[F1D2C(1, global_id)] = -covc___velfg_map_218_scal + df___velfg_map_218_scal;
      covx1___velfg_map_218_scal =
          ((*cov4_s_0___f_comp_f_1____4c58ee66) + cov4_s_0___f_comp_f_1____4c58ee66[F1D2C(1, 2)]) /
          2.;
      covy1___velfg_map_218_scal =
          (dy1_0[F1D2C(0, j___velfg_map_218_scal + 1)] * (*cov5_s_0___f_comp_f_1____91f7197a) +
           dy1_0[F1D2C(0, j___velfg_map_218_scal)] *
               cov5_s_0___f_comp_f_1____91f7197a[F1D2C(1, 2)]) /
          (dy1_0[F1D2C(0, j___velfg_map_218_scal)] + dy1_0[F1D2C(0, j___velfg_map_218_scal + 1)]);
      covz1___velfg_map_218_scal =
          ((*cov6_s_0___f_comp_f_1____dcd2e1f3) + cov6_s_0___f_comp_f_1____dcd2e1f3[F1D2C(1, 2)]) /
          2.;
      covc___velfg_map_218_scal =
          covx1___velfg_map_218_scal + covy1___velfg_map_218_scal + covz1___velfg_map_218_scal;
      dfv1___velfg_map_218 =
          (-(*diu4_s_0___f_comp_f_1____4f05f130) + diu4_s_0___f_comp_f_1____4f05f130[F1D2C(1, 2)]) /
              dx1_0[F1D2C(-1, i___velfg_map_218_scal)] +
          2. *
              (-(*diu5_s_0___f_comp_f_1____8ac031a2) +
               diu5_s_0___f_comp_f_1____8ac031a2[F1D2C(1, 2)]) /
              (dy1_0[F1D2C(0, j___velfg_map_218_scal)] +
               dy1_0[F1D2C(0, j___velfg_map_218_scal + 1)]) +
          (-(*diu6_s_0___f_comp_f_1____b1f35dc5) + diu6_s_0___f_comp_f_1____b1f35dc5[F1D2C(1, 2)]) /
              dzn_0[F1D2C(-1, k___velfg_map_218_scal)];
      df___velfg_map_218_scal = vn___velfg_map_218_scal * dfv1___velfg_map_218;
      g_1[F1D2C(1, global_id)] = -covc___velfg_map_218_scal + df___velfg_map_218_scal;
      if ((k___velfg_map_218_scal < (kp___velfg_map_218_scal - 1))) {
        covx1___velfg_map_218_scal = ((*cov7_s_0___f_comp_f_1____f85a90f2) +
                                      cov7_s_0___f_comp_f_1____f85a90f2[F1D2C(1, 2)]) /
                                     2.;
        covy1___velfg_map_218_scal =
            ((*cov8_s_0___f_comp_f_1____187de70) + cov8_s_0___f_comp_f_1____187de70[F1D2C(1, 2)]) /
            2.;
        covz1___velfg_map_218_scal =
            (dzn_0[F1D2C(-1, k___velfg_map_218_scal + 1)] * (*cov9_s_0___f_comp_f_1____44f8210b) +
             dzn_0[F1D2C(-1, k___velfg_map_218_scal)] *
                 cov9_s_0___f_comp_f_1____44f8210b[F1D2C(1, 2)]) /
            (dzn_0[F1D2C(-1, k___velfg_map_218_scal)] +
             dzn_0[F1D2C(-1, k___velfg_map_218_scal + 1)]);
        covc___velfg_map_218_scal =
            covx1___velfg_map_218_scal + covy1___velfg_map_218_scal + covz1___velfg_map_218_scal;
        dfw1___velfg_map_218 = (-(*diu7_s_0___f_comp_f_1____9bfc5fb8) +
                                diu7_s_0___f_comp_f_1____9bfc5fb8[F1D2C(1, 2)]) /
                                   dx1_0[F1D2C(-1, i___velfg_map_218_scal)] +
                               (-(*diu8_s_0___f_comp_f_1____6399bded) +
                                diu8_s_0___f_comp_f_1____6399bded[F1D2C(1, 2)]) /
                                   dy1_0[F1D2C(0, j___velfg_map_218_scal)] +
                               (-(*diu9_s_0___f_comp_f_1____cb19f377) +
                                diu9_s_0___f_comp_f_1____cb19f377[F1D2C(1, 2)]) /
                                   dzs_0[F1D2C(-1, k___velfg_map_218_scal)];
        df___velfg_map_218_scal = vn___velfg_map_218_scal * dfw1___velfg_map_218;
        h_1[F1D2C(1, global_id)] = -covc___velfg_map_218_scal + df___velfg_map_218_scal;
      }

      //    !RF4A End Inline
    });
  });
}
