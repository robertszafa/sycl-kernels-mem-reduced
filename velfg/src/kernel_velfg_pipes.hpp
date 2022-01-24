#include "CL/sycl/aliases.hpp"
#include "CL/sycl/properties/accessor_properties.hpp"
#include <CL/sycl.hpp>
#include <iostream>
#include <vector>


#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "velfg_sizes.hpp"

using namespace sycl;

double velfg_pipes(queue &q, const std::vector<float> &u, const std::vector<float> &v,
                 const std::vector<float> &w, const std::vector<float> &dx1,
                 const std::vector<float> &dy1, const std::vector<float> &dzn,
                 const std::vector<float> &dzs, std::vector<float> &f, std::vector<float> &g,
                 std::vector<float> &h) {

  range<1> fgh_range{F_G_H_ARRAY_SIZE};
  range<1> uvw_range{U_V_W_ARRAY_SIZE};

  // You define a pipe by specialising the pipe<> class with an id, type, and
  // optional min_capacity. The below is just an alias for so that it is
  // consistent across uses.
  //
  // some_pipe::write(DATA), some_pipe::read() are blocking
  // some_pipe::write(DATA, success_bool_flag),
  // some_pipe::read(success_bol_flag) are blocking

  using u_memrd_2_map76_133_pre = pipe<class u_memrd_2_map76_133_pre_class, float>;
  using v_memrd_2_map76_133_pre = pipe<class v_memrd_2_map76_133_pre_class, float>;
  using w_memrd_2_map76_133_pre = pipe<class w_memrd_2_map76_133_pre_class, float>;
  // post-smache
  using u_i_j_k_memrd_2_map76_133_post = pipe<class u_i_j_k_memrd_2_map76_133_post_class, float>;
  using u_im1_j_k_memrd_2_map76_133_post =
      pipe<class u_im1_j_k_memrd_2_map76_133_post_class, float>;
  using u_i_jm1_k_memrd_2_map76_133_post =
      pipe<class u_i_jm1_k_memrd_2_map76_133_post_class, float>;
  using u_i_j_km1_memrd_2_map76_133_post =
      pipe<class u_i_j_km1_memrd_2_map76_133_post_class, float>;
  using u_im1_jp1_k_memrd_2_map76_133_post =
      pipe<class u_im1_jp1_k_memrd_2_map76_133_post_class, float>;
  using v_i_j_k_memrd_2_map76_133_post = pipe<class v_i_j_k_memrd_2_map76_133_post_class, float>;
  using v_im1_j_k_memrd_2_map76_133_post =
      pipe<class v_im1_j_k_memrd_2_map76_133_post_class, float>;
  using v_i_jm1_k_memrd_2_map76_133_post =
      pipe<class v_i_jm1_k_memrd_2_map76_133_post_class, float>;
  using v_ip1_jm1_k_memrd_2_map76_133_post =
      pipe<class v_ip1_jm1_k_memrd_2_map76_133_post_class, float>;
  using v_i_j_km1_memrd_2_map76_133_post =
      pipe<class v_i_j_km1_memrd_2_map76_133_post_class, float>;
  using v_i_jm1_kp1_memrd_2_map76_133_post =
      pipe<class v_i_jm1_kp1_memrd_2_map76_133_post_class, float>;
  using w_i_j_k_memrd_2_map76_133_post = pipe<class w_i_j_k_memrd_2_map76_133_post_class, float>;
  using w_i_j_km1_memrd_2_map76_133_post =
      pipe<class w_i_j_km1_memrd_2_map76_133_post_class, float>;
  using w_ip1_j_km1_memrd_2_map76_133_post =
      pipe<class w_ip1_j_km1_memrd_2_map76_133_post_class, float>;
  using w_i_jp1_km1_memrd_2_map76_133_post =
      pipe<class w_i_jp1_km1_memrd_2_map76_133_post_class, float>;
  using u_im1_j_kp1_memrd_2_map76_133_post =
      pipe<class u_im1_j_kp1_memrd_2_map76_133_post_class, float>;
  using w_im1_j_k_memrd_2_map76_133_post =
      pipe<class w_im1_j_k_memrd_2_map76_133_post_class, float>;
  using w_i_jm1_k_memrd_2_map76_133_post =
      pipe<class w_i_jm1_k_memrd_2_map76_133_post_class, float>;
  /// map76_133 -> map218
  // pre-smache
  using cov1_map76_133_2_map218_pre = pipe<class cov1_map76_133_2_map218_pre_class, float>;
  using cov2_map76_133_2_map218_pre = pipe<class cov2_map76_133_2_map218_pre_class, float>;
  using cov3_map76_133_2_map218_pre = pipe<class cov3_map76_133_2_map218_pre_class, float>;
  using cov4_map76_133_2_map218_pre = pipe<class cov4_map76_133_2_map218_pre_class, float>;
  using cov5_map76_133_2_map218_pre = pipe<class cov5_map76_133_2_map218_pre_class, float>;
  using cov6_map76_133_2_map218_pre = pipe<class cov6_map76_133_2_map218_pre_class, float>;
  using cov7_map76_133_2_map218_pre = pipe<class cov7_map76_133_2_map218_pre_class, float>;
  using cov8_map76_133_2_map218_pre = pipe<class cov8_map76_133_2_map218_pre_class, float>;
  using cov9_map76_133_2_map218_pre = pipe<class cov9_map76_133_2_map218_pre_class, float>;
  using diu1_map76_133_2_map218_pre = pipe<class diu1_map76_133_2_map218_pre_class, float>;
  using diu2_map76_133_2_map218_pre = pipe<class diu2_map76_133_2_map218_pre_class, float>;
  using diu3_map76_133_2_map218_pre = pipe<class diu3_map76_133_2_map218_pre_class, float>;
  using diu4_map76_133_2_map218_pre = pipe<class diu4_map76_133_2_map218_pre_class, float>;
  using diu5_map76_133_2_map218_pre = pipe<class diu5_map76_133_2_map218_pre_class, float>;
  using diu6_map76_133_2_map218_pre = pipe<class diu6_map76_133_2_map218_pre_class, float>;
  using diu7_map76_133_2_map218_pre = pipe<class diu7_map76_133_2_map218_pre_class, float>;
  using diu8_map76_133_2_map218_pre = pipe<class diu8_map76_133_2_map218_pre_class, float>;
  using diu9_map76_133_2_map218_pre = pipe<class diu9_map76_133_2_map218_pre_class, float>;
  // post-smache
  using cov1_i_j_k_map76_133_2_map218_post =
      pipe<class cov1_i_j_k_map76_133_2_map218_post_class, float>;
  using cov1_ip1_j_k_map76_133_2_map218_post =
      pipe<class cov1_ip1_j_k_map76_133_2_map218_post_class, float>;
  using cov2_i_j_k_map76_133_2_map218_post =
      pipe<class cov2_i_j_k_map76_133_2_map218_post_class, float>;
  using cov2_i_jp1_k_map76_133_2_map218_post =
      pipe<class cov2_i_jp1_k_map76_133_2_map218_post_class, float>;
  using cov3_i_j_k_map76_133_2_map218_post =
      pipe<class cov3_i_j_k_map76_133_2_map218_post_class, float>;
  using cov3_i_j_kp1_map76_133_2_map218_post =
      pipe<class cov3_i_j_kp1_map76_133_2_map218_post_class, float>;
  using cov4_i_j_k_map76_133_2_map218_post =
      pipe<class cov4_i_j_k_map76_133_2_map218_post_class, float>;
  using cov4_ip1_j_k_map76_133_2_map218_post =
      pipe<class cov4_ip1_j_k_map76_133_2_map218_post_class, float>;
  using cov5_i_j_k_map76_133_2_map218_post =
      pipe<class cov5_i_j_k_map76_133_2_map218_post_class, float>;
  using cov5_i_jp1_k_map76_133_2_map218_post =
      pipe<class cov5_i_jp1_k_map76_133_2_map218_post_class, float>;
  using cov6_i_j_k_map76_133_2_map218_post =
      pipe<class cov6_i_j_k_map76_133_2_map218_post_class, float>;
  using cov6_i_j_kp1_map76_133_2_map218_post =
      pipe<class cov6_i_j_kp1_map76_133_2_map218_post_class, float>;
  using cov7_i_j_k_map76_133_2_map218_post =
      pipe<class cov7_i_j_k_map76_133_2_map218_post_class, float>;
  using cov7_ip1_j_k_map76_133_2_map218_post =
      pipe<class cov7_ip1_j_k_map76_133_2_map218_post_class, float>;
  using cov8_i_j_k_map76_133_2_map218_post =
      pipe<class cov8_i_j_k_map76_133_2_map218_post_class, float>;
  using cov8_i_jp1_k_map76_133_2_map218_post =
      pipe<class cov8_i_jp1_k_map76_133_2_map218_post_class, float>;
  using cov9_i_j_k_map76_133_2_map218_post =
      pipe<class cov9_i_j_k_map76_133_2_map218_post_class, float>;
  using cov9_i_j_kp1_map76_133_2_map218_post =
      pipe<class cov9_i_j_kp1_map76_133_2_map218_post_class, float>;
  using diu1_i_j_k_map76_133_2_map218_post =
      pipe<class diu1_i_j_k_map76_133_2_map218_post_class, float>;
  using diu1_ip1_j_k_map76_133_2_map218_post =
      pipe<class diu1_ip1_j_k_map76_133_2_map218_post_class, float>;
  using diu2_i_j_k_map76_133_2_map218_post =
      pipe<class diu2_i_j_k_map76_133_2_map218_post_class, float>;
  using diu2_i_jp1_k_map76_133_2_map218_post =
      pipe<class diu2_i_jp1_k_map76_133_2_map218_post_class, float>;
  using diu3_i_j_k_map76_133_2_map218_post =
      pipe<class diu3_i_j_k_map76_133_2_map218_post_class, float>;
  using diu3_i_j_kp1_map76_133_2_map218_post =
      pipe<class diu3_i_j_kp1_map76_133_2_map218_post_class, float>;
  using diu4_i_j_k_map76_133_2_map218_post =
      pipe<class diu4_i_j_k_map76_133_2_map218_post_class, float>;
  using diu4_ip1_j_k_map76_133_2_map218_post =
      pipe<class diu4_ip1_j_k_map76_133_2_map218_post_class, float>;
  using diu5_i_j_k_map76_133_2_map218_post =
      pipe<class diu5_i_j_k_map76_133_2_map218_post_class, float>;
  using diu5_i_jp1_k_map76_133_2_map218_post =
      pipe<class diu5_i_jp1_k_map76_133_2_map218_post_class, float>;
  using diu6_i_j_k_map76_133_2_map218_post =
      pipe<class diu6_i_j_k_map76_133_2_map218_post_class, float>;
  using diu6_i_j_kp1_map76_133_2_map218_post =
      pipe<class diu6_i_j_kp1_map76_133_2_map218_post_class, float>;
  using diu7_i_j_k_map76_133_2_map218_post =
      pipe<class diu7_i_j_k_map76_133_2_map218_post_class, float>;
  using diu7_ip1_j_k_map76_133_2_map218_post =
      pipe<class diu7_ip1_j_k_map76_133_2_map218_post_class, float>;
  using diu8_i_j_k_map76_133_2_map218_post =
      pipe<class diu8_i_j_k_map76_133_2_map218_post_class, float>;
  using diu8_i_jp1_k_map76_133_2_map218_post =
      pipe<class diu8_i_jp1_k_map76_133_2_map218_post_class, float>;
  using diu9_i_j_k_map76_133_2_map218_post =
      pipe<class diu9_i_j_k_map76_133_2_map218_post_class, float>;
  using diu9_i_j_kp1_map76_133_2_map218_post =
      pipe<class diu9_i_j_kp1_map76_133_2_map218_post_class, float>;
  // map218 -> mem_wr
  using f_out = pipe<class f_out_class, float>;
  using g_out = pipe<class g_out_class, float>;
  using h_out = pipe<class h_out_class, float>;

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
  // Output buffers are initialised with non-const host pointer,
  // which ensures device->host data transfer after buffer goes out of scope.
  buffer f_buf(f);
  buffer g_buf(g);
  buffer h_buf(h);


  //////////////////////////////
  // memory read
  sycl::event event_first = q.submit([&](handler &hnd) {
    accessor u(u_buf, hnd, read_only);
    accessor v(u_buf, hnd, read_only);
    accessor w(u_buf, hnd, read_only);

    hnd.single_task<class memrd>([=]() [[intel::kernel_args_restrict]] {
      // Writes and reads from the same channel must follow the same sequence to
      // prevent deadlock. Use mem_fence() to ensure ordering.
      for (int count = 0; count < DOMAIN_SIZE; count++) {
        u_memrd_2_map76_133_pre::write(u[U_V_W_LOWEST_IDX + count]);
        v_memrd_2_map76_133_pre::write(v[U_V_W_LOWEST_IDX + count]);
        w_memrd_2_map76_133_pre::write(w[U_V_W_LOWEST_IDX + count]);
      }
    });
  });

  //////////////////////////////
  // memory read -> map76 SMACHE
  q.submit([&](handler &hnd) {
    hnd.single_task<class memrd_smache>([=]() [[intel::kernel_args_restrict]] {
      // Store the stencil reach + the current i_j_k element
      float u_buffer[STENCIL_REACH + 1];
      float v_buffer[STENCIL_REACH + 1];
      float w_buffer[STENCIL_REACH + 1];

      // loop for the entire array + offset buffer
      // (W_DOMAIN_SIZE + STENCIL_REACH) because that is the largest
      // for (int count = 0; count < (W_DOMAIN_SIZE + STENCIL_REACH); count++)
      for (int count = 0; count < (DOMAIN_SIZE + STENCIL_REACH); count++) {
// SHIFT-RIGHT register for the buffers
// TODO: Probably no need for this pragma.
#pragma unroll
        for (int i = 0; i < STENCIL_REACH; ++i) {
          u_buffer[i] = u_buffer[i + 1];
          v_buffer[i] = v_buffer[i + 1];
          w_buffer[i] = w_buffer[i + 1];
        }

        if (count < DOMAIN_SIZE) {
          u_buffer[STENCIL_REACH] = u_memrd_2_map76_133_pre::read();
          v_buffer[STENCIL_REACH] = v_memrd_2_map76_133_pre::read();
          w_buffer[STENCIL_REACH] = w_memrd_2_map76_133_pre::read();
        }

        // start emitting once all data covered by the stencil reach is read
        // into the buffer
        const int IDX_I_J_K = REACH_NEG;
        if (count >= STENCIL_REACH) {
          u_i_j_k_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K]);
          u_im1_j_k_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K - OFFSET_IM1_J_K]);
          u_i_jm1_k_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K - OFFSET_I_JM1_K]);
          u_i_j_km1_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K - OFFSET_I_J_KM1]);
          u_im1_jp1_k_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K + OFFSET_IM1_JP1_K]);
          u_im1_j_kp1_memrd_2_map76_133_post::write(u_buffer[IDX_I_J_K + OFFSET_IM1_J_KP1]);

          v_i_j_k_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K]);
          v_im1_j_k_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K - OFFSET_IM1_J_K]);
          v_i_jm1_k_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K - OFFSET_I_JM1_K]);
          v_ip1_jm1_k_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K - OFFSET_IP1_JM1_K]);
          v_i_j_km1_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K - OFFSET_I_J_KM1]);
          v_i_jm1_kp1_memrd_2_map76_133_post::write(v_buffer[IDX_I_J_K + OFFSET_I_JM1_KP1]);

          w_i_j_k_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K]);
          w_i_j_km1_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K - OFFSET_I_J_KM1]);
          w_ip1_j_km1_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K - OFFSET_IP1_J_KM1]);
          w_i_jp1_km1_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K - OFFSET_I_JP1_KM1]);
          w_im1_j_k_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K - OFFSET_IM1_J_K]);
          w_i_jm1_k_memrd_2_map76_133_post::write(w_buffer[IDX_I_J_K - OFFSET_I_JM1_K]);
        }
      }
    });
  });

  //////////////////////////////
  // map 76 and map 133
  q.submit([&](handler &hnd) {
    accessor dx1(dx1_buf, hnd, read_only);
    accessor dy1(dy1_buf, hnd, read_only);
    accessor dzn(dzn_buf, hnd, read_only);
    accessor dzs(dzs_buf, hnd, read_only);

    hnd.single_task<class map76_133>([=]() [[intel::kernel_args_restrict]] {
      const int u0 = 0;

      const int k_vel2_range = (((KP + 1) - 1) + 1);
      const int j_vel2_range = ((JP - 1) + 1);
      const int i_vel2_range = ((IP - 1) + 1);

      for (uint idx = 0; idx < DOMAIN_SIZE; ++idx) {
        float cov1 = 0, cov2 = 0, cov3 = 0, cov4 = 0, cov5 = 0, cov6 = 0, cov7 = 0, cov8 = 0, cov9;
        float diu1 = 0, diu2 = 0, diu3 = 0, diu4 = 0, diu5 = 0, diu6 = 0, diu7 = 0, diu8 = 0, diu9;

        int k_vel2_rel = (idx / (j_vel2_range * i_vel2_range));
        int k_vel2 = k_vel2_rel + 1;
        int j_vel2_rel = ((idx - (k_vel2_rel * (j_vel2_range * i_vel2_range))) / i_vel2_range);
        int j_vel2 = j_vel2_rel + 1;
        int i_vel2_rel =
            ((idx - (k_vel2_rel * (j_vel2_range * i_vel2_range))) - (j_vel2_rel * i_vel2_range));
        int i_vel2 = i_vel2_rel + 1;

        // u values
        float u_i_j_k = u_i_j_k_memrd_2_map76_133_post::read();
        float u_im1_j_k = u_im1_j_k_memrd_2_map76_133_post::read();
        float u_i_jm1_k = u_i_jm1_k_memrd_2_map76_133_post::read();
        float u_i_j_km1 = u_i_j_km1_memrd_2_map76_133_post::read();
        float u_im1_jp1_k = u_im1_jp1_k_memrd_2_map76_133_post::read();
        float u_im1_j_kp1 = u_im1_j_kp1_memrd_2_map76_133_post::read();

        // v values
        float v_i_j_k = v_i_j_k_memrd_2_map76_133_post::read();
        float v_im1_j_k = v_im1_j_k_memrd_2_map76_133_post::read();
        float v_i_jm1_k = v_i_jm1_k_memrd_2_map76_133_post::read();
        float v_ip1_jm1_k = v_ip1_jm1_k_memrd_2_map76_133_post::read();
        float v_i_j_km1 = v_i_j_km1_memrd_2_map76_133_post::read();
        float v_i_jm1_kp1 = v_i_jm1_kp1_memrd_2_map76_133_post::read();

        // w values
        float w_i_j_k = w_i_j_k_memrd_2_map76_133_post::read();
        float w_i_j_km1 = w_i_j_km1_memrd_2_map76_133_post::read();
        float w_ip1_j_km1 = w_ip1_j_km1_memrd_2_map76_133_post::read();
        float w_i_jp1_km1 = w_i_jp1_km1_memrd_2_map76_133_post::read();
        float w_im1_j_k = w_im1_j_k_memrd_2_map76_133_post::read();
        float w_i_jm1_k = w_i_jm1_k_memrd_2_map76_133_post::read();

        if (k_vel2 < KP) {
          float nou1 = (u_im1_j_k + u_i_j_k) / 2.;
          diu1 = (-u_im1_j_k + u_i_j_k) / dx1[F1D2C((-1), i_vel2)];
          float nou5 = (v_i_jm1_k + v_i_j_k) / 2.;
          diu5 = (-v_i_jm1_k + v_i_j_k) / dy1[F1D2C(0, j_vel2)];
          float nou9 = (w_i_j_km1 + w_i_j_k) / 2.;
          diu9 = (-w_i_j_km1 + w_i_j_k) / dzn[F1D2C((-1), k_vel2)];
          cov1 = nou1 * diu1;
          cov5 = nou5 * diu5;
          cov9 = nou9 * diu9;
        }

        if (k_vel2 < KP) {
          float nou2 = (dx1[i_vel2 + 1] * v_i_jm1_k + dx1[i_vel2] * v_ip1_jm1_k) /
                       (dx1[F1D2C((-1), i_vel2)] + dx1[F1D2C((-1), i_vel2 + 1)]);
          diu2 = 2. * (-u_i_jm1_k + u_i_j_k) / (dy1[F1D2C(0, j_vel2 - 1)] + dy1[F1D2C(0, j_vel2)]);
          cov2 = nou2 * diu2;
        }

        float nou3 =
            (dx1[F1D2C((-1), i_vel2 + 1)] * w_i_j_km1 + dx1[F1D2C((-1), i_vel2)] * w_ip1_j_km1) /
            (dx1[F1D2C((-1), i_vel2)] + dx1[F1D2C((-1), i_vel2 + 1)]);
        diu3 = (-u_i_j_km1 + u_i_j_k) / dzs[F1D2C((-1), k_vel2 - 1)];
        cov3 = nou3 * diu3;

        if (k_vel2 < KP) {
          float nou4 =
              (dy1[F1D2C(0, j_vel2 + 1)] * u_im1_j_k + dy1[F1D2C(0, j_vel2)] * u_im1_jp1_k) /
              (dy1[F1D2C(0, j_vel2)] + dy1[F1D2C(0, j_vel2 + 1)]);
          diu4 = 2. * (-v_im1_j_k + v_i_j_k + v_i_j_k) /
                 (dx1[F1D2C((-1), i_vel2 - 1)] + dx1[F1D2C((-1), i_vel2)]);
          cov4 = (nou4 - u0) * diu4;
        }

        float nou6 = (dy1[F1D2C(0, j_vel2 + 1)] * w_i_j_km1 + dy1[F1D2C(0, j_vel2)] * w_i_jp1_km1) /
                     (dy1[F1D2C(0, j_vel2)] + dy1[F1D2C(0, j_vel2 + 1)]);
        diu6 = (-v_i_j_km1 + v_i_j_k) / dzs[F1D2C((-1), k_vel2 - 1)];
        cov6 = nou6 * diu6;

        // map133 specific
        float nou7 =
            (dzn[F1D2C((-1), k_vel2 + 1)] * u_i_j_k + dzn[F1D2C((-1), k_vel2)] * u_im1_j_kp1) /
            (dzn[F1D2C((-1), k_vel2)] + dzn[F1D2C((-1), k_vel2 + 1)]);
        diu7 =
            2. * (-w_im1_j_k + w_i_j_k) / (dx1[F1D2C((-1), i_vel2 - 1)] + dx1[F1D2C((-1), i_vel2)]);
        cov7 = (nou7 - u0) * diu7;
        float nou8 =
            (dzn[F1D2C((-1), k_vel2 + 1)] * v_i_jm1_k + dzn[F1D2C((-1), k_vel2)] * v_i_jm1_kp1) /
            (dzn[F1D2C((-1), k_vel2)] + dzn[F1D2C((-1), k_vel2 + 1)]);
        diu8 = 2. * (-w_i_jm1_k + w_i_j_k) / (dy1[F1D2C(0, j_vel2 - 1)] + dy1[F1D2C(0, j_vel2)]);
        cov8 = nou8 * diu8;

        cov1_map76_133_2_map218_pre::write(cov1);
        cov2_map76_133_2_map218_pre::write(cov2);
        cov3_map76_133_2_map218_pre::write(cov3);
        cov4_map76_133_2_map218_pre::write(cov4);
        cov5_map76_133_2_map218_pre::write(cov5);
        cov6_map76_133_2_map218_pre::write(cov6);
        cov7_map76_133_2_map218_pre::write(cov7);
        cov8_map76_133_2_map218_pre::write(cov8);
        cov9_map76_133_2_map218_pre::write(cov9);

        diu1_map76_133_2_map218_pre::write(diu1);
        diu2_map76_133_2_map218_pre::write(diu2);
        diu3_map76_133_2_map218_pre::write(diu3);
        diu4_map76_133_2_map218_pre::write(diu4);
        diu5_map76_133_2_map218_pre::write(diu5);
        diu6_map76_133_2_map218_pre::write(diu6);
        diu7_map76_133_2_map218_pre::write(diu7);
        diu8_map76_133_2_map218_pre::write(diu8);
        diu9_map76_133_2_map218_pre::write(diu9);
      }
    });
  });

  //////////////////////////////
  // map 76_and_133 --> map 218 SMACHE
  q.submit([&](handler &hnd) {
    hnd.single_task<class map76_133_smache>([=]() [[intel::kernel_args_restrict]] {
      // Store the stencil reach + the current i_j_k element
      // All cov and diu reaches are purely positive, there are only 3 cases:
      /// (i+1, j, k) or (i, j+1, k) or (i, j, k+1)
      const int COV1_REACH = OFFSET_IP1_J_K;
      const int COV2_REACH = OFFSET_I_JP1_K;
      const int COV3_REACH = OFFSET_I_J_KP1;
      const int COV4_REACH = OFFSET_IP1_J_K;
      const int COV5_REACH = OFFSET_I_JP1_K;
      const int COV6_REACH = OFFSET_I_J_KP1;
      const int COV7_REACH = OFFSET_IP1_J_K;
      const int COV8_REACH = OFFSET_I_JP1_K;
      const int COV9_REACH = OFFSET_I_J_KP1;

      const int DIU1_REACH = OFFSET_IP1_J_K;
      const int DIU2_REACH = OFFSET_I_JP1_K;
      const int DIU3_REACH = OFFSET_I_J_KP1;
      const int DIU4_REACH = OFFSET_IP1_J_K;
      const int DIU5_REACH = OFFSET_I_JP1_K;
      const int DIU6_REACH = OFFSET_I_J_KP1;
      const int DIU7_REACH = OFFSET_IP1_J_K;
      const int DIU8_REACH = OFFSET_I_JP1_K;
      const int DIU9_REACH = OFFSET_I_J_KP1;

      // All streams produce the same amount of elements.
      // For each stream, we have a (JP*KP) sized buffer which corresponds to the maximum reach.
      // Eventhough some streams have a reach of KP or even 1, having smaller buffers for them
      // would result in a deadlock.
      const int STENCIL_REACH_COV_DIU = OFFSET_I_J_KP1;

      float cov1_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov2_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov3_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov4_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov5_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov6_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov7_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov8_buffer[STENCIL_REACH_COV_DIU + 1];
      float cov9_buffer[STENCIL_REACH_COV_DIU + 1];

      float diu1_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu2_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu3_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu4_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu5_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu6_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu7_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu8_buffer[STENCIL_REACH_COV_DIU + 1];
      float diu9_buffer[STENCIL_REACH_COV_DIU + 1];

      // loop for the entire array + offset buffer
      for (int count = 0; count < (DOMAIN_SIZE + STENCIL_REACH_COV_DIU); count++) {
// SHIFT-RIGHT register for the buffers
#pragma unroll
        for (int i = 0; i < STENCIL_REACH_COV_DIU; ++i) {
          cov1_buffer[i] = cov1_buffer[i + 1];
          cov2_buffer[i] = cov2_buffer[i + 1];
          cov3_buffer[i] = cov3_buffer[i + 1];
          cov4_buffer[i] = cov4_buffer[i + 1];
          cov5_buffer[i] = cov5_buffer[i + 1];
          cov6_buffer[i] = cov6_buffer[i + 1];
          cov7_buffer[i] = cov7_buffer[i + 1];
          cov8_buffer[i] = cov8_buffer[i + 1];
          cov9_buffer[i] = cov9_buffer[i + 1];

          diu1_buffer[i] = diu1_buffer[i + 1];
          diu2_buffer[i] = diu2_buffer[i + 1];
          diu3_buffer[i] = diu3_buffer[i + 1];
          diu4_buffer[i] = diu4_buffer[i + 1];
          diu5_buffer[i] = diu5_buffer[i + 1];
          diu6_buffer[i] = diu6_buffer[i + 1];
          diu7_buffer[i] = diu7_buffer[i + 1];
          diu8_buffer[i] = diu8_buffer[i + 1];
          diu9_buffer[i] = diu9_buffer[i + 1];
        }

        if (count < DOMAIN_SIZE) {
          cov1_buffer[STENCIL_REACH_COV_DIU] = cov1_map76_133_2_map218_pre::read();
          cov2_buffer[STENCIL_REACH_COV_DIU] = cov2_map76_133_2_map218_pre::read();
          cov3_buffer[STENCIL_REACH_COV_DIU] = cov3_map76_133_2_map218_pre::read();
          cov4_buffer[STENCIL_REACH_COV_DIU] = cov4_map76_133_2_map218_pre::read();
          cov5_buffer[STENCIL_REACH_COV_DIU] = cov5_map76_133_2_map218_pre::read();
          cov6_buffer[STENCIL_REACH_COV_DIU] = cov6_map76_133_2_map218_pre::read();
          cov7_buffer[STENCIL_REACH_COV_DIU] = cov7_map76_133_2_map218_pre::read();
          cov8_buffer[STENCIL_REACH_COV_DIU] = cov8_map76_133_2_map218_pre::read();
          cov9_buffer[STENCIL_REACH_COV_DIU] = cov9_map76_133_2_map218_pre::read();

          diu1_buffer[STENCIL_REACH_COV_DIU] = diu1_map76_133_2_map218_pre::read();
          diu2_buffer[STENCIL_REACH_COV_DIU] = diu2_map76_133_2_map218_pre::read();
          diu3_buffer[STENCIL_REACH_COV_DIU] = diu3_map76_133_2_map218_pre::read();
          diu4_buffer[STENCIL_REACH_COV_DIU] = diu4_map76_133_2_map218_pre::read();
          diu5_buffer[STENCIL_REACH_COV_DIU] = diu5_map76_133_2_map218_pre::read();
          diu6_buffer[STENCIL_REACH_COV_DIU] = diu6_map76_133_2_map218_pre::read();
          diu7_buffer[STENCIL_REACH_COV_DIU] = diu7_map76_133_2_map218_pre::read();
          diu8_buffer[STENCIL_REACH_COV_DIU] = diu8_map76_133_2_map218_pre::read();
          diu9_buffer[STENCIL_REACH_COV_DIU] = diu9_map76_133_2_map218_pre::read();
        }

        // start emitting once all data covered by the biggest stencil reach is read into the buffer
        if (count >= STENCIL_REACH_COV_DIU) {
          cov1_i_j_k_map76_133_2_map218_post::write(cov1_buffer[0]);
          cov1_ip1_j_k_map76_133_2_map218_post::write(cov1_buffer[COV1_REACH]);
          cov2_i_j_k_map76_133_2_map218_post::write(cov2_buffer[0]);
          cov2_i_jp1_k_map76_133_2_map218_post::write(cov2_buffer[COV2_REACH]);
          cov3_i_j_k_map76_133_2_map218_post::write(cov3_buffer[0]);
          cov3_i_j_kp1_map76_133_2_map218_post::write(cov3_buffer[COV3_REACH]);
          cov4_i_j_k_map76_133_2_map218_post::write(cov4_buffer[0]);
          cov4_ip1_j_k_map76_133_2_map218_post::write(cov4_buffer[COV4_REACH]);
          cov5_i_j_k_map76_133_2_map218_post::write(cov5_buffer[0]);
          cov5_i_jp1_k_map76_133_2_map218_post::write(cov5_buffer[COV5_REACH]);
          cov6_i_j_k_map76_133_2_map218_post::write(cov6_buffer[0]);
          cov6_i_j_kp1_map76_133_2_map218_post::write(cov6_buffer[COV6_REACH]);
          cov7_i_j_k_map76_133_2_map218_post::write(cov7_buffer[0]);
          cov7_ip1_j_k_map76_133_2_map218_post::write(cov7_buffer[COV7_REACH]);
          cov8_i_j_k_map76_133_2_map218_post::write(cov8_buffer[0]);
          cov8_i_jp1_k_map76_133_2_map218_post::write(cov8_buffer[COV8_REACH]);
          cov9_i_j_k_map76_133_2_map218_post::write(cov9_buffer[0]);
          cov9_i_j_kp1_map76_133_2_map218_post::write(cov9_buffer[COV9_REACH]);

          diu1_i_j_k_map76_133_2_map218_post::write(diu1_buffer[0]);
          diu1_ip1_j_k_map76_133_2_map218_post::write(diu1_buffer[DIU1_REACH]);
          diu2_i_j_k_map76_133_2_map218_post::write(diu2_buffer[0]);
          diu2_i_jp1_k_map76_133_2_map218_post::write(diu2_buffer[DIU2_REACH]);
          diu3_i_j_k_map76_133_2_map218_post::write(diu3_buffer[0]);
          diu3_i_j_kp1_map76_133_2_map218_post::write(diu3_buffer[DIU3_REACH]);
          diu4_i_j_k_map76_133_2_map218_post::write(diu4_buffer[0]);
          diu4_ip1_j_k_map76_133_2_map218_post::write(diu4_buffer[DIU4_REACH]);
          diu5_i_j_k_map76_133_2_map218_post::write(diu5_buffer[0]);
          diu5_i_jp1_k_map76_133_2_map218_post::write(diu5_buffer[DIU5_REACH]);
          diu6_i_j_k_map76_133_2_map218_post::write(diu6_buffer[0]);
          diu6_i_j_kp1_map76_133_2_map218_post::write(diu6_buffer[DIU6_REACH]);
          diu7_i_j_k_map76_133_2_map218_post::write(diu7_buffer[0]);
          diu7_ip1_j_k_map76_133_2_map218_post::write(diu7_buffer[DIU7_REACH]);
          diu8_i_j_k_map76_133_2_map218_post::write(diu8_buffer[0]);
          diu8_i_jp1_k_map76_133_2_map218_post::write(diu8_buffer[DIU8_REACH]);
          diu9_i_j_k_map76_133_2_map218_post::write(diu9_buffer[0]);
          diu9_i_j_kp1_map76_133_2_map218_post::write(diu9_buffer[DIU9_REACH]);
        }
      }
    });
  });

  //////////////////////////////
  // map 218 and write memory
  sycl::event event_last = q.submit([&](handler &hnd) {
    accessor dx1(dx1_buf, hnd, read_only);
    accessor dy1(dy1_buf, hnd, read_only);
    accessor dzn(dzn_buf, hnd, read_only);
    accessor dzs(dzs_buf, hnd, read_only);

    accessor f(f_buf, hnd, write_only, no_init);
    accessor g(g_buf, hnd, write_only, no_init);
    accessor h(h_buf, hnd, write_only, no_init);

    hnd.single_task<class map218>([=]() [[intel::kernel_args_restrict]] {
      const float vn = 15.83 * 0.000001;

      const int k_range = ((KP - 1) + 1);
      const int j_range = ((JP - 1) + 1);
      const int i_range = ((IP - 1) + 1);

      for (uint idx = 0; idx < DOMAIN_SIZE; ++idx) {
        float cov1_i_j_k = cov1_i_j_k_map76_133_2_map218_post::read();
        float cov1_ip1_j_k = cov1_ip1_j_k_map76_133_2_map218_post::read();
        float cov2_i_j_k = cov2_i_j_k_map76_133_2_map218_post::read();
        float cov2_i_jp1_k = cov2_i_jp1_k_map76_133_2_map218_post::read();
        float cov3_i_j_k = cov3_i_j_k_map76_133_2_map218_post::read();
        float cov3_i_j_kp1 = cov3_i_j_kp1_map76_133_2_map218_post::read();
        float cov4_i_j_k = cov4_i_j_k_map76_133_2_map218_post::read();
        float cov4_ip1_j_k = cov4_ip1_j_k_map76_133_2_map218_post::read();
        float cov5_i_j_k = cov5_i_j_k_map76_133_2_map218_post::read();
        float cov5_i_jp1_k = cov5_i_jp1_k_map76_133_2_map218_post::read();
        float cov6_i_j_k = cov6_i_j_k_map76_133_2_map218_post::read();
        float cov6_i_j_kp1 = cov6_i_j_kp1_map76_133_2_map218_post::read();
        float cov7_i_j_k = cov7_i_j_k_map76_133_2_map218_post::read();
        float cov7_ip1_j_k = cov7_ip1_j_k_map76_133_2_map218_post::read();
        float cov8_i_j_k = cov8_i_j_k_map76_133_2_map218_post::read();
        float cov8_i_jp1_k = cov8_i_jp1_k_map76_133_2_map218_post::read();
        float cov9_i_j_k = cov9_i_j_k_map76_133_2_map218_post::read();
        float cov9_i_j_kp1 = cov9_i_j_kp1_map76_133_2_map218_post::read();

        float diu1_i_j_k = diu1_i_j_k_map76_133_2_map218_post::read();
        float diu1_ip1_j_k = diu1_ip1_j_k_map76_133_2_map218_post::read();
        float diu2_i_j_k = diu2_i_j_k_map76_133_2_map218_post::read();
        float diu2_i_jp1_k = diu2_i_jp1_k_map76_133_2_map218_post::read();
        float diu3_i_j_k = diu3_i_j_k_map76_133_2_map218_post::read();
        float diu3_i_j_kp1 = diu3_i_j_kp1_map76_133_2_map218_post::read();
        float diu4_i_j_k = diu4_i_j_k_map76_133_2_map218_post::read();
        float diu4_ip1_j_k = diu4_ip1_j_k_map76_133_2_map218_post::read();
        float diu5_i_j_k = diu5_i_j_k_map76_133_2_map218_post::read();
        float diu5_i_jp1_k = diu5_i_jp1_k_map76_133_2_map218_post::read();
        float diu6_i_j_k = diu6_i_j_k_map76_133_2_map218_post::read();
        float diu6_i_j_kp1 = diu6_i_j_kp1_map76_133_2_map218_post::read();
        float diu7_i_j_k = diu7_i_j_k_map76_133_2_map218_post::read();
        float diu7_ip1_j_k = diu7_ip1_j_k_map76_133_2_map218_post::read();
        float diu8_i_j_k = diu8_i_j_k_map76_133_2_map218_post::read();
        float diu8_i_jp1_k = diu8_i_jp1_k_map76_133_2_map218_post::read();
        float diu9_i_j_k = diu9_i_j_k_map76_133_2_map218_post::read();
        float diu9_i_j_kp1 = diu9_i_j_kp1_map76_133_2_map218_post::read();

        const int k_rel = (idx / (j_range * i_range));
        const int k = k_rel + 1;
        const int j_rel = ((idx - (k_rel * (j_range * i_range))) / i_range);
        const int j = j_rel + 1;
        const int i_rel = ((idx - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        const int i = i_rel + 1;

        float covx1 = (dx1[F1D2C((-1), i + 1)] * cov1_i_j_k + dx1[F1D2C((-1), i)] * cov1_ip1_j_k) /
                      (dx1[F1D2C((-1), i)] + dx1[F1D2C((-1), i + 1)]);
        float covy1 = (cov2_i_j_k + cov2_i_jp1_k) / 2.;
        float covz1 = (cov3_i_j_k + cov3_i_j_kp1) / 2.;
        float covc = covx1 + covy1 + covz1;
        float dfu1 =
            2. * (-diu1_i_j_k + diu1_ip1_j_k) / (dx1[F1D2C((-1), i)] + dx1[F1D2C((-1), i + 1)]) +
            (-diu2_i_j_k + diu2_i_jp1_k) / dy1[F1D2C(0, j)] +
            (-diu3_i_j_k + diu3_i_j_kp1) / dzn[F1D2C((-1), k)];
        float df = vn * dfu1;
        f[F_G_H_IDX_1_1_1 + idx] = -covc + df;

        covx1 = (cov4_i_j_k + cov4_ip1_j_k) / 2.;
        covy1 = (dy1[F1D2C(0, j + 1)] * cov5_i_j_k + dy1[F1D2C(0, j)] * cov5_i_jp1_k) /
                (dy1[F1D2C(0, j)] + dy1[F1D2C(0, j + 1)]);
        covz1 = (cov6_i_j_k + cov6_i_j_kp1) / 2.;
        covc = covx1 + covy1 + covz1;
        float dfv1 = (-diu4_i_j_k + diu4_ip1_j_k) / dx1[F1D2C((-1), i)] +
                     2. * (-diu5_i_j_k + diu5_i_jp1_k) / (dy1[F1D2C(0, j)] + dy1[F1D2C(0, j + 1)]) +
                     (-diu6_i_j_k + diu6_i_j_kp1) / dzn[F1D2C((-1), k)];
        df = vn * dfv1;
        g[F_G_H_IDX_1_1_1 + idx] = -covc + df;

        if ((k < (KP - 1))) {
          covx1 = (cov7_i_j_k + cov7_ip1_j_k) / 2.;
          covy1 = (cov8_i_j_k + cov8_i_jp1_k) / 2.;
          covz1 = (dzn[F1D2C((-1), k + 1)] * cov9_i_j_k + dzn[F1D2C((-1), k)] * cov9_i_j_kp1) /
                  (dzn[F1D2C((-1), k)] + dzn[F1D2C((-1), k + 1)]);
          covc = covx1 + covy1 + covz1;
          float dfw1 = (-diu7_i_j_k + diu7_ip1_j_k) / dx1[F1D2C((-1), i)] +
                       (-diu8_i_j_k + diu8_i_jp1_k) / dy1[F1D2C(0, j)] +
                       (-diu9_i_j_k + diu9_i_j_kp1) / dzs[F1D2C((-1), k)];
          df = vn * dfw1;
          h[F_G_H_IDX_1_1_1 + idx] = -covc + df;
        }
      }
    });
  });

  auto start = event_first.get_profiling_info<info::event_profiling::command_start>();
  auto end = event_last.get_profiling_info<info::event_profiling::command_end>();
  double time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
