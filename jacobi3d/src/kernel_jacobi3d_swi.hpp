#include <CL/sycl.hpp>
#include <array>
#include <iostream>

#if FPGA || FPGA_EMULATOR
  #include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "jacobi3d_sizes.hpp"

using namespace sycl;

double jacobi3d_swi(queue &q, const std::vector<float> &u,
                    std::vector<float> &un) {

  range<1> num_items{u.size()};

  buffer u_0_buf(u);
  buffer un_1_buf(un);

  buffer v0_buf(u);
  buffer v1_buf(u);
  buffer v2_buf(u);

  constexpr float c = 0.1;

  q.submit([&](handler &hnd) {
    accessor u_0(u_0_buf, hnd, read_only);
    accessor v0(v0_buf, hnd, write_only, no_init);

    hnd.single_task<class jacobi3d_base_0>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int i = 1; i < IP - 1; ++i) {
            for (int j = 1; j < JP - 1; ++j) {
              for (int k = 1; k < KP - 1; ++k) {
                v0[F3D2C(IP, JP, IP, 0, 0, i, j, k)] =
                    (u_0[F3D2C(IP, JP, IP, 0, 0, i - 1, j, k)] +
                     u_0[F3D2C(IP, JP, IP, 0, 0, i + 1, j, k)] +
                     u_0[F3D2C(IP, JP, IP, 0, 0, i, j - 1, k)] +
                     u_0[F3D2C(IP, JP, IP, 0, 0, i, j + 1, k)] +
                     u_0[F3D2C(IP, JP, IP, 0, 0, i, j, k - 1)] +
                     u_0[F3D2C(IP, JP, IP, 0, 0, i, j, k + 1)]) *
                    c;
              }
            }
          }
        });
  });

  q.submit([&](handler &hnd) {
    accessor v0(v0_buf, hnd, read_only);
    accessor v1(v0_buf, hnd, write_only);

    hnd.single_task<class jacobi3d_base_1>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int i = 1; i < IP - 1; ++i) {
            for (int j = 1; j < JP - 1; ++j) {
              for (int k = 1; k < KP - 1; ++k) {
                v1[F3D2C(IP, JP, IP, 0, 0, i, j, k)] =
                    (v0[F3D2C(IP, JP, IP, 0, 0, i - 1, j, k)] +
                     v0[F3D2C(IP, JP, IP, 0, 0, i + 1, j, k)] +
                     v0[F3D2C(IP, JP, IP, 0, 0, i, j - 1, k)] +
                     v0[F3D2C(IP, JP, IP, 0, 0, i, j + 1, k)] +
                     v0[F3D2C(IP, JP, IP, 0, 0, i, j, k - 1)] +
                     v0[F3D2C(IP, JP, IP, 0, 0, i, j, k + 1)]) *
                    c;
              }
            }
          }
        });
  });

  q.submit([&](handler &hnd) {
    accessor v1(v0_buf, hnd, read_only);
    accessor v2(v0_buf, hnd, write_only);

    hnd.single_task<class jacobi3d_base_2>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int i = 1; i < IP - 1; ++i) {
            for (int j = 1; j < JP - 1; ++j) {
              for (int k = 1; k < KP - 1; ++k) {
                v2[F3D2C(IP, JP, IP, 0, 0, i, j, k)] =
                    (v1[F3D2C(IP, JP, IP, 0, 0, i - 1, j, k)] +
                     v1[F3D2C(IP, JP, IP, 0, 0, i + 1, j, k)] +
                     v1[F3D2C(IP, JP, IP, 0, 0, i, j - 1, k)] +
                     v1[F3D2C(IP, JP, IP, 0, 0, i, j + 1, k)] +
                     v1[F3D2C(IP, JP, IP, 0, 0, i, j, k - 1)] +
                     v1[F3D2C(IP, JP, IP, 0, 0, i, j, k + 1)]) *
                    c;
              }
            }
          }
        });
  });

  auto event = q.submit([&](handler &hnd) {
    accessor v2(v0_buf, hnd, read_only);
    accessor un_1(v0_buf, hnd, write_only);

    hnd.single_task<class jacobi3d_base_3>(
        [=]() [[intel::kernel_args_restrict]] {
          for (int i = 1; i < IP; ++i) {
            for (int j = 1; j < JP; ++j) {
              for (int k = 1; k < KP; ++k) {
                un_1[F3D2C(IP, JP, IP, 0, 0, i, j, k)] =
                    (v2[F3D2C(IP, JP, IP, 0, 0, i - 1, j, k)] +
                     v2[F3D2C(IP, JP, IP, 0, 0, i + 1, j, k)] +
                     v2[F3D2C(IP, JP, IP, 0, 0, i, j - 1, k)] +
                     v2[F3D2C(IP, JP, IP, 0, 0, i, j + 1, k)] +
                     v2[F3D2C(IP, JP, IP, 0, 0, i, j, k - 1)] +
                     v2[F3D2C(IP, JP, IP, 0, 0, i, j, k + 1)]) *
                    c;
              }
            }
          }
        });
  });

  auto start = event.get_profiling_info<info::event_profiling::command_start>();
  auto end = event.get_profiling_info<info::event_profiling::command_end>();
  auto time_in_ms = static_cast<double>(end - start) / 1000000;

  return time_in_ms;
}
