#include <CL/sycl.hpp>
#include <array>
#include <cstdio>
#include <iostream>

#if FPGA || FPGA_EMULATOR
  #include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "hotspot3d_sizes.hpp"

using namespace sycl;

double hotspot3d_swi(queue &q, const std::vector<float> &tIn,
                     const std::vector<float> &pIn, std::vector<float> &tOut) {

  buffer tin_buf(tIn);
  buffer pin_buf(pIn);
  buffer tout_buf(tOut);

  buffer v0_buf(tIn);
  buffer v1_buf(tIn);
  buffer v2_buf(tIn);

  auto event1 = q.submit([&](handler &hnd) {
    accessor tin(tin_buf, hnd, read_only);
    accessor pin(pin_buf, hnd, read_only);
    accessor v0(v0_buf, hnd, write_only, no_init);

    hnd.single_task<class hotspot3d_base_0>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id < (NX-2) * (NY-2) * (NZ-2);
               ++global_id) {
            const int k_range = ((nz - 1) + 1);
            const int j_range = ((ny - 1) + 1);
            const int i_range = ((nx - 1) + 1);
            const int k_rel = (global_id / (j_range * i_range));
            const int k = k_rel + 1;
            const int j_rel =
                ((global_id - (k_rel * (j_range * i_range))) / i_range);
            const int j = j_rel + 1;
            const int i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                               (j_rel * i_range));
            const int i = i_rel + 1;
            v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0, i,
                       j, k)] =
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] *
                    cc +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] *
                    cn +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] *
                    cs +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] *
                    ce +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)] *
                    cw +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j + 1, k)] *
                    ct +
                tin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j - 1, k)] *
                    cb +
                (dt / cap) *
                    pin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0,
                              0, i, j, k)] +
                ct * amb_temp;
          }
        });
  });

q.submit([&](handler &hnd) {
    accessor v0(v0_buf, hnd, read_only);
    accessor pin(pin_buf, hnd, read_only);
    accessor v1(v1_buf, hnd, write_only, no_init);

    hnd.single_task<class hotspot3d_base_1>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id < (NX-2) * (NY-2) * (NZ-2);
               ++global_id) {
            const int k_range = ((nz - 1) + 1);
            const int j_range = ((ny - 1) + 1);
            const int i_range = ((nx - 1) + 1);
            const int k_rel = (global_id / (j_range * i_range));
            const int k = k_rel + 1;
            const int j_rel =
                ((global_id - (k_rel * (j_range * i_range))) / i_range);
            const int j = j_rel + 1;
            const int i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                               (j_rel * i_range));
            const int i = i_rel + 1;
            v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0, i,
                       j, k)] =
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] *
                    cc +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] *
                    cn +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] *
                    cs +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] *
                    ce +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)] *
                    cw +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j + 1, k)] *
                    ct +
                v0[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j - 1, k)] *
                    cb +
                (dt / cap) *
                    pin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0,
                              0, i, j, k)] +
                ct * amb_temp;
          }
        });
  });

  
q.submit([&](handler &hnd) {
    accessor v1(v1_buf, hnd, read_only);
    accessor pin(pin_buf, hnd, read_only);
    accessor v2(v2_buf, hnd, write_only, no_init);

    hnd.single_task<class hotspot3d_base_2>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id < (NX-2) * (NY-2) * (NZ-2);
               ++global_id) {
            const int k_range = ((nz - 1) + 1);
            const int j_range = ((ny - 1) + 1);
            const int i_range = ((nx - 1) + 1);
            const int k_rel = (global_id / (j_range * i_range));
            const int k = k_rel + 1;
            const int j_rel =
                ((global_id - (k_rel * (j_range * i_range))) / i_range);
            const int j = j_rel + 1;
            const int i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                               (j_rel * i_range));
            const int i = i_rel + 1;
            v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0, i,
                       j, k)] =
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] *
                    cc +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] *
                    cn +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] *
                    cs +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] *
                    ce +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)] *
                    cw +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j + 1, k)] *
                    ct +
                v1[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j - 1, k)] *
                    cb +
                (dt / cap) *
                    pin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0,
                              0, i, j, k)] +
                ct * amb_temp;
          }
        });
  });

    auto event2 = q.submit([&](handler &hnd) {
    accessor v2(v2_buf, hnd, read_only);
    accessor pin(pin_buf, hnd, read_only);
    accessor tout(tout_buf, hnd, write_only, no_init);

    hnd.single_task<class hotspot3d_base_3>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id < (NX-2) * (NY-2) * (NZ-2);
               ++global_id) {
            const int k_range = ((nz - 1) + 1);
            const int j_range = ((ny - 1) + 1);
            const int i_range = ((nx - 1) + 1);
            const int k_rel = (global_id / (j_range * i_range));
            const int k = k_rel + 1;
            const int j_rel =
                ((global_id - (k_rel * (j_range * i_range))) / i_range);
            const int j = j_rel + 1;
            const int i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                               (j_rel * i_range));
            const int i = i_rel + 1;
            tout[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0, i,
                       j, k)] =
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] *
                    cc +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] *
                    cn +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] *
                    cs +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] *
                    ce +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)] *
                    cw +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j + 1, k)] *
                    ct +
                v2[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0, 0,
                          i, j - 1, k)] *
                    cb +
                (dt / cap) *
                    pin[F3D2C((((nx + 1) - 0) + 1), (((ny + 1) - 0) + 1), 0, 0,
                              0, i, j, k)] +
                ct * amb_temp;
          }
        });
  });

  auto start =
      event1.get_profiling_info<info::event_profiling::command_start>();
  auto end = event2.get_profiling_info<info::event_profiling::command_end>();
  auto time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
