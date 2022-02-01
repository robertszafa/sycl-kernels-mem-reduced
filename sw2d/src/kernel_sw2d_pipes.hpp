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

double sw2d_pipes(queue &q, const std::vector<int> &wet, const std::vector<float> &eta,
                const std::vector<float> &u, const std::vector<float> &v,
                const std::vector<float> &h, std::vector<float> &etann, std::vector<float> &un,
                std::vector<float> &vn) {
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

  /// Pipe declarations.
  // memrd_smache -> map49_55
  using h_pipe_memrd_j_k = pipe<class h_pipe_memrd_j_k_class, float>;
  using u_pipe_memrd_j_k = pipe<class u_pipe_memrd_j_k_class, float>;
  using v_pipe_memrd_j_k = pipe<class v_pipe_memrd_j_k_class, float>;

  using eta_pipe_memrd_j_k = pipe<class eta_pipe_memrd_j_k_class, float>;
  using eta_pipe_memrd_jp1_k = pipe<class eta_pipe_memrd_jp1_k_class, float>;
  using eta_pipe_memrd_j_kp1 = pipe<class eta_pipe_memrd_j_kp1_class, float>;

  using wet_pipe_memrd_j_k = pipe<class wet_pipe_memrd_j_k_class, int>;
  using wet_pipe_memrd_j_kp1 = pipe<class wet_pipe_memrd_j_kp1_class, int>;
  using wet_pipe_memrd_jp1_k = pipe<class wet_pipe_memrd_jp1_k_class, int>;

  // map49_55 -> map55_smache
  using un_pipe_map55_j_k = pipe<class un_pipe_map55_j_k_class, float>;
  using vn_pipe_map55_j_k = pipe<class vn_pipe_map55_j_k_class, float>;
  using h_pipe_map55_j_k = pipe<class h_pipe_map55_j_k_class, float>;
  using eta_pipe_map55_j_k = pipe<class eta_pipe_map55_j_k_class, float>;
  using wet_pipe_map55_j_k = pipe<class wet_pipe_map55_j_k_class, float>;

  // map55_smache -> map75
  using h_pipe_map55_smache_j_k = pipe<class h_pipe_map55_smache_j_k_class, float>;
  using h_pipe_map55_smache_j_kp1 = pipe<class h_pipe_map55_smache_j_kp1_class, float>;
  using h_pipe_map55_smache_jp1_k = pipe<class h_pipe_map55_smache_jp1_k_class, float>;
  using h_pipe_map55_smache_j_km1 = pipe<class h_pipe_map55_smache_j_km1_class, float>;
  using h_pipe_map55_smache_jm1_k = pipe<class h_pipe_map55_smache_jm1_k_class, float>;
  using vn_pipe_map55_smache_j_k = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using vn_pipe_map55_smache_j_km1 = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using vn_pipe_map55_smache_jm1_k = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using un_pipe_map55_smache_j_k = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using un_pipe_map55_smache_j_km1 = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using un_pipe_map55_smache_jm1_k = pipe<class vn_pipe_map55_smache_j_k_class, float>;
  using eta_pipe_map55_smache_j_k = pipe<class eta_pipe_map55_smache_j_k_class, float>;
  using wet_pipe_map55_smache_j_k = pipe<class wet_pipe_map55_smache_j_k_class, float>;

  // map75 -> map75_smache
  using etan_pipe_map75_j_k = pipe<class etan_pipe_map75_j_k_class, float>;
  using wet_pipe_map75_j_k = pipe<class wet_pipe_map75_j_k_class, float>;

  // map75_smache -> map92
  using wet_pipe_map75_smache_j_k = pipe<class wet_pipe_map75_smache_j_k_class, int>;
  using wet_pipe_map75_smache_j_kp1 = pipe<class wet_pipe_map75_smache_j_kp1_class, int>;
  using wet_pipe_map75_smache_jp1_k = pipe<class wet_pipe_map75_smache_jp1_k_class, int>;
  using wet_pipe_map75_smache_j_km1 = pipe<class wet_pipe_map75_smache_j_km1_class, int>;
  using wet_pipe_map75_smache_jm1_k = pipe<class wet_pipe_map75_smache_jm1_k_class, int>;
  using etan_pipe_map75_smache_j_k = pipe<class etan_pipe_map75_smache_j_k_class, float>;
  using etan_pipe_map75_smache_j_kp1 = pipe<class etan_pipe_map75_smache_j_kp1_class, float>;
  using etan_pipe_map75_smache_jp1_k = pipe<class etan_pipe_map75_smache_jp1_k_class, float>;
  using etan_pipe_map75_smache_j_km1 = pipe<class etan_pipe_map75_smache_j_km1_class, float>;
  using etan_pipe_map75_smache_jm1_k = pipe<class etan_pipe_map75_smache_jm1_k_class, float>;

  q.submit([&](handler &hnd) {
    accessor h(h_buf, hnd, read_only);
    accessor u(u_buf, hnd, read_only);
    accessor v(v_buf, hnd, read_only);
    accessor eta(eta_buf, hnd, read_only);
    accessor wet(wet_buf, hnd, read_only);

    hnd.single_task<class memrd_smache>([=]() {
      constexpr uint REACH_POS = std::max(OFFSET_J_KP1, OFFSET_JP1_K);
      constexpr uint REACH_NEG = 0;
      constexpr uint STENCIL_REACH = REACH_NEG + REACH_POS;

      // Store the stencil reach + the current i_j_k element
      float h_buffer[STENCIL_REACH + 1];
      float u_buffer[STENCIL_REACH + 1];
      float v_buffer[STENCIL_REACH + 1];
      float eta_buffer[STENCIL_REACH + 1];
      float wet_buffer[STENCIL_REACH + 1];

      for (int idx = 0; idx < (ARRAY_SIZE + STENCIL_REACH); idx++) {
// SHIFT-RIGHT register for the buffers
// TODO: Probably no need for this pragma.
#pragma unroll
        for (int i = 0; i < STENCIL_REACH; ++i) {
          h_buffer[i] = h_buffer[i + 1];
          u_buffer[i] = u_buffer[i + 1];
          v_buffer[i] = v_buffer[i + 1];
          eta_buffer[i] = eta_buffer[i + 1];
          wet_buffer[i] = wet_buffer[i + 1];
        }

        if (idx < ARRAY_SIZE) {
          h_buffer[STENCIL_REACH] = h[idx];
          u_buffer[STENCIL_REACH] = u[idx];
          v_buffer[STENCIL_REACH] = v[idx];
          eta_buffer[STENCIL_REACH] = eta[idx];
          wet_buffer[STENCIL_REACH] = wet[idx];
        }

        // start emitting once all data covered by the stencil reach is read into the buffer
        constexpr uint IDX_J_K = REACH_NEG;
        if (idx >= STENCIL_REACH) {
          h_pipe_memrd_j_k::write(h_buffer[IDX_J_K]);
          u_pipe_memrd_j_k::write(u_buffer[IDX_J_K]);
          v_pipe_memrd_j_k::write(v_buffer[IDX_J_K]);

          eta_pipe_memrd_j_k::write(eta_buffer[IDX_J_K]);
          eta_pipe_memrd_j_kp1::write(eta_buffer[IDX_J_K + OFFSET_J_KP1]);
          eta_pipe_memrd_jp1_k::write(eta_buffer[IDX_J_K + OFFSET_JP1_K]);

          wet_pipe_memrd_j_k::write(wet_buffer[IDX_J_K]);
          wet_pipe_memrd_j_kp1::write(wet_buffer[IDX_J_K + OFFSET_J_KP1]);
          wet_pipe_memrd_jp1_k::write(wet_buffer[IDX_J_K + OFFSET_JP1_K]);
        }
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor un(un_buf, hnd, write_only, no_init);
    accessor vn(vn_buf, hnd, write_only, no_init);

    hnd.single_task<class map49_55>([=]() {
      for (int global_id = 0; global_id < ARRAY_SIZE; ++global_id) {
        const auto h_j_k = h_pipe_memrd_j_k::read();
        const auto u_j_k = u_pipe_memrd_j_k::read();
        const auto v_j_k = v_pipe_memrd_j_k::read();
        const auto eta_j_k = eta_pipe_memrd_j_k::read();
        const auto eta_j_kp1 = eta_pipe_memrd_j_kp1::read();
        const auto eta_jp1_k = eta_pipe_memrd_jp1_k::read();
        const auto wet_j_k = wet_pipe_memrd_j_k::read();
        const auto wet_jp1_k = wet_pipe_memrd_jp1_k::read();
        const auto wet_j_kp1 = wet_pipe_memrd_j_kp1::read();

        auto du___dyn_j_k = -dt * g * (eta_j_kp1 - eta_j_k) / dx;
        auto dv___dyn_j_k = -dt * g * (eta_jp1_k - eta_j_k) / dy;

        float un_j_k = 0.0;
        float vn_j_k = 0.0;

        if (wet_j_k == 1) {
          if ((wet_j_kp1 == 1) || (du___dyn_j_k > 0.0))
            un_j_k = u_j_k + du___dyn_j_k;
        } else {
          if ((wet_j_kp1 == 1) && (du___dyn_j_k < 0.0))
            un_j_k = u_j_k + du___dyn_j_k;
        }
        if (wet_j_k == 1) {
          if ((wet_jp1_k == 1) || (dv___dyn_j_k > 0.0))
            vn_j_k = v_j_k + dv___dyn_j_k;
        } else {
          if ((wet_jp1_k == 1) && (dv___dyn_j_k < 0.0))
            vn_j_k = v_j_k + dv___dyn_j_k;
        }

        un[global_id] = un_j_k;
        vn[global_id] = vn_j_k;

        un_pipe_map55_j_k::write(un_j_k);
        vn_pipe_map55_j_k::write(vn_j_k);
        h_pipe_map55_j_k::write(h_j_k);
        eta_pipe_map55_j_k::write(eta_j_k);
        wet_pipe_map55_j_k::write(wet_j_k);
      }
    });
  });

  q.submit([&](handler &hnd) {
    hnd.single_task<class map55_smache>([=]() {
      constexpr uint REACH_POS = std::max(OFFSET_J_KP1, OFFSET_JP1_K);
      constexpr uint REACH_NEG = std::max(OFFSET_J_KM1, OFFSET_JM1_K);
      constexpr uint STENCIL_REACH = REACH_NEG + REACH_POS;

      // Store the stencil reach + the current i_j_k element
      float vn_buffer[STENCIL_REACH + 1];
      float un_buffer[STENCIL_REACH + 1];
      float h_buffer[STENCIL_REACH + 1];
      float eta_buffer[STENCIL_REACH + 1];
      float wet_buffer[STENCIL_REACH + 1];

      for (int idx = 0; idx < (ARRAY_SIZE + STENCIL_REACH); idx++) {
// SHIFT-RIGHT register for the buffers
// TODO: Probably no need for this pragma.
#pragma unroll
        for (int i = 0; i < STENCIL_REACH; ++i) {
          vn_buffer[i] = vn_buffer[i + 1];
          un_buffer[i] = un_buffer[i + 1];
          h_buffer[i] = h_buffer[i + 1];
          eta_buffer[i] = eta_buffer[i + 1];
          wet_buffer[i] = wet_buffer[i + 1];
        }

        if (idx < ARRAY_SIZE) {
          vn_buffer[STENCIL_REACH] = vn_pipe_map55_j_k::read();
          un_buffer[STENCIL_REACH] = un_pipe_map55_j_k::read();
          h_buffer[STENCIL_REACH] = h_pipe_map55_j_k::read();
          eta_buffer[STENCIL_REACH] = eta_pipe_map55_j_k::read();
          wet_buffer[STENCIL_REACH] = wet_pipe_map55_j_k::read();
        }

        // start emitting once all data covered by the stencil reach is read into the buffer
        constexpr uint IDX_J_K = REACH_NEG;
        if (idx >= STENCIL_REACH) {
          vn_pipe_map55_smache_j_k::write(vn_buffer[IDX_J_K]);
          vn_pipe_map55_smache_j_km1::write(vn_buffer[IDX_J_K - OFFSET_J_KM1]);
          vn_pipe_map55_smache_jm1_k::write(vn_buffer[IDX_J_K - OFFSET_JM1_K]);

          un_pipe_map55_smache_j_k::write(un_buffer[IDX_J_K]);
          un_pipe_map55_smache_j_km1::write(un_buffer[IDX_J_K - OFFSET_J_KM1]);
          un_pipe_map55_smache_jm1_k::write(un_buffer[IDX_J_K - OFFSET_JM1_K]);

          h_pipe_map55_smache_j_k::write(h_buffer[IDX_J_K]);
          h_pipe_map55_smache_j_kp1::write(h_buffer[IDX_J_K + OFFSET_J_KP1]);
          h_pipe_map55_smache_jp1_k::write(h_buffer[IDX_J_K + OFFSET_JP1_K]);
          h_pipe_map55_smache_j_km1::write(h_buffer[IDX_J_K - OFFSET_J_KM1]);
          h_pipe_map55_smache_jm1_k::write(h_buffer[IDX_J_K - OFFSET_JM1_K]);

          eta_pipe_map55_smache_j_k::write(eta_buffer[IDX_J_K]);

          wet_pipe_map55_smache_j_k::write(wet_buffer[IDX_J_K]);
        }
      }
    });
  });

  q.submit([&](handler &hnd) {
    hnd.single_task<class map75>([=]() {
      for (int global_id = 0; global_id < ARRAY_SIZE; ++global_id) {
        const auto vn_j_k = vn_pipe_map55_smache_j_k::read();
        const auto vn_j_km1 = vn_pipe_map55_smache_j_km1::read();
        const auto vn_jm1_k = vn_pipe_map55_smache_jm1_k::read();
        const auto un_j_k = un_pipe_map55_smache_j_k::read();
        const auto un_j_km1 = un_pipe_map55_smache_j_km1::read();
        const auto un_jm1_k = un_pipe_map55_smache_jm1_k::read();
        const auto h_j_k = h_pipe_map55_smache_j_k::read();
        const auto h_j_kp1 = h_pipe_map55_smache_j_kp1::read();
        const auto h_jp1_k = h_pipe_map55_smache_jp1_k::read();
        const auto h_j_km1 = h_pipe_map55_smache_j_km1::read();
        const auto h_jm1_k = h_pipe_map55_smache_jm1_k::read();
        const auto eta_j_k = eta_pipe_map55_smache_j_k::read();
        const auto wet_j_k = wet_pipe_map55_smache_j_k::read();

        float hep___dyn = 0.5 * (un_j_k + (float)fabs(un_j_k)) * h_j_k;
        float hen___dyn = 0.5 * (un_j_k - (float)fabs(un_j_k)) * h_j_kp1;
        float hue___dyn = hep___dyn + hen___dyn;
        float hwp___dyn = 0.5 * (un_j_km1 + (float)fabs(un_j_km1)) * h_j_km1;
        float hwn___dyn = 0.5 * (un_j_km1 - (float)fabs(un_j_km1)) * h_j_k;
        float huw___dyn = hwp___dyn + hwn___dyn;
        float hnp___dyn = 0.5 * (vn_j_k + (float)fabs(vn_j_k)) * h_j_k;
        float hnn___dyn = 0.5 * (vn_j_k - (float)fabs(vn_j_k)) * h_jp1_k;
        float hvn___dyn = hnp___dyn + hnn___dyn;
        float hsp___dyn = 0.5 * (vn_jm1_k + (float)fabs(vn_jm1_k)) * h_jm1_k;
        float hsn___dyn = 0.5 * (vn_jm1_k - (float)fabs(vn_jm1_k)) * h_j_k;
        float hvs___dyn = hsp___dyn + hsn___dyn;
        float etan_j_k =
            eta_j_k - dt * (hue___dyn - huw___dyn) / dx - dt * (hvn___dyn - hvs___dyn) / dy;

        etan_pipe_map75_j_k::write(etan_j_k);
        wet_pipe_map75_j_k::write(wet_j_k);
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor wet(wet_buf, hnd, read_only);
    accessor eta(eta_buf, hnd, read_only);

    hnd.single_task<class map75_smache>([=]() {
      constexpr uint REACH_POS = std::max(OFFSET_J_KP1, OFFSET_JP1_K);
      constexpr uint REACH_NEG = std::max(OFFSET_J_KM1, OFFSET_JM1_K);
      constexpr uint STENCIL_REACH = REACH_NEG + REACH_POS;

      // Store the stencil reach + the current i_j_k element
      float etan_buffer[STENCIL_REACH + 1];
      float wet_buffer[STENCIL_REACH + 1];

      for (int idx = 0; idx < (ARRAY_SIZE + STENCIL_REACH); idx++) {
// SHIFT-RIGHT register for the buffers
// TODO: Probably no need for this pragma.
#pragma unroll
        for (int i = 0; i < STENCIL_REACH; ++i) {
          etan_buffer[i] = etan_buffer[i + 1];
          wet_buffer[i] = wet_buffer[i + 1];
        }

        if (idx < ARRAY_SIZE) {
          etan_buffer[STENCIL_REACH] = etan_pipe_map75_j_k::read();
          wet_buffer[STENCIL_REACH] = wet_pipe_map75_j_k::read();
        }

        // start emitting once all data covered by the stencil reach is read into the buffer
        constexpr uint IDX_J_K = REACH_NEG;
        if (idx >= STENCIL_REACH) {
          etan_pipe_map75_smache_j_k::write(etan_buffer[IDX_J_K]);
          etan_pipe_map75_smache_j_kp1::write(etan_buffer[IDX_J_K + OFFSET_J_KP1]);
          etan_pipe_map75_smache_jp1_k::write(etan_buffer[IDX_J_K + OFFSET_JP1_K]);
          etan_pipe_map75_smache_j_km1::write(etan_buffer[IDX_J_K - OFFSET_J_KM1]);
          etan_pipe_map75_smache_jm1_k::write(etan_buffer[IDX_J_K - OFFSET_JM1_K]);

          wet_pipe_map75_smache_j_k::write(wet_buffer[IDX_J_K]);
          wet_pipe_map75_smache_j_kp1::write(wet_buffer[IDX_J_K + OFFSET_J_KP1]);
          wet_pipe_map75_smache_jp1_k::write(wet_buffer[IDX_J_K + OFFSET_JP1_K]);
          wet_pipe_map75_smache_j_km1::write(wet_buffer[IDX_J_K - OFFSET_J_KM1]);
          wet_pipe_map75_smache_jm1_k::write(wet_buffer[IDX_J_K - OFFSET_JM1_K]);
        }
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor etann(etann_buf, hnd, write_only, no_init);

    hnd.single_task<class map92>([=]() {
      for (int global_id = 0; global_id < ARRAY_SIZE; ++global_id) {

        auto etan_j_k = etan_pipe_map75_smache_j_k::read();
        auto etan_j_kp1 = etan_pipe_map75_smache_j_kp1::read();
        auto etan_jp1_k = etan_pipe_map75_smache_jp1_k::read();
        auto etan_j_km1 = etan_pipe_map75_smache_j_km1::read();
        auto etan_jm1_k = etan_pipe_map75_smache_jm1_k::read();
        auto wet_j_k = wet_pipe_map75_smache_j_k::read();
        auto wet_j_kp1 = wet_pipe_map75_smache_j_kp1::read();
        auto wet_jp1_k = wet_pipe_map75_smache_jp1_k::read();
        auto wet_j_km1 = wet_pipe_map75_smache_j_km1::read();
        auto wet_jm1_k = wet_pipe_map75_smache_jm1_k::read();

        float etann_j_k = 0.0;
        if (wet_j_k == 1) {
          float term1___map75 =
              float(1.0 - 0.25 * eps * (wet_j_kp1 + wet_j_km1 + wet_jp1_k + wet_jm1_k)) * etan_j_k;
          float term2___map75 = 0.25 * eps * (wet_j_kp1 * etan_j_kp1 + wet_j_km1 * etan_j_km1);
          float term3___map75 = 0.25 * eps * (wet_jp1_k * etan_jp1_k + wet_jm1_k * etan_jm1_k);
          etann_j_k = term1___map75 + term2___map75 + term3___map75;
        } else {
          etann_j_k = etan_j_k;
        }

        etann[global_id] = etann_j_k;
      }
    });
  });

  auto start = event_first.get_profiling_info<info::event_profiling::command_start>();
  auto end = event_last.get_profiling_info<info::event_profiling::command_end>();
  double time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
