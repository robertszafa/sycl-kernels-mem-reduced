#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

#if FPGA || FPGA_EMULATOR
#include <CL/sycl/INTEL/fpga_extensions.hpp>
#endif

#include "velfg_sizes.hpp"

using namespace sycl;

void velfg_ndrange(queue &q, const std::vector<float> &u, const std::vector<float> &v,
                   const std::vector<float> &w, const std::vector<float> &dx1,
                   const std::vector<float> &dy1, const std::vector<float> &dzn,
                   const std::vector<float> &dzs, std::vector<float> &f, std::vector<float> &g,
                   std::vector<float> &h) {

  range<1> fgh_range{F_G_H_ARRAY_SIZE};
  range<1> uvw_range{U_V_W_ARRAY_SIZE};

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

  // Create buffers holding intermediate arrays in global memory.
  buffer<float> cov1_buf(uvw_range), cov2_buf(uvw_range), cov3_buf(uvw_range), cov4_buf(uvw_range),
      cov5_buf(uvw_range), cov6_buf(uvw_range), cov7_buf(uvw_range), cov8_buf(uvw_range),
      cov9_buf(uvw_range);
  buffer<float> diu1_buf(uvw_range), diu2_buf(uvw_range), diu3_buf(uvw_range), diu4_buf(uvw_range),
      diu5_buf(uvw_range), diu6_buf(uvw_range), diu7_buf(uvw_range), diu8_buf(uvw_range),
      diu9_buf(uvw_range);

  // Submit kernels in-order to the same blocking queue.
  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor u(u_buf, hnd, read_only);
    accessor v(v_buf, hnd, read_only);
    accessor w(w_buf, hnd, read_only);
    accessor dx1(dx1_buf, hnd, read_only);
    accessor dy1(dy1_buf, hnd, read_only);
    accessor dzn(dzn_buf, hnd, read_only);
    accessor dzs(dzs_buf, hnd, read_only);

    accessor diu1(diu1_buf, hnd, write_only, no_init);
    accessor diu2(diu2_buf, hnd, write_only, no_init);
    accessor diu3(diu3_buf, hnd, write_only, no_init);
    accessor diu4(diu4_buf, hnd, write_only, no_init);
    accessor diu5(diu5_buf, hnd, write_only, no_init);
    accessor diu6(diu6_buf, hnd, write_only, no_init);
    accessor diu9(diu9_buf, hnd, write_only, no_init);
    accessor cov1(cov1_buf, hnd, write_only, no_init);
    accessor cov2(cov2_buf, hnd, write_only, no_init);
    accessor cov3(cov3_buf, hnd, write_only, no_init);
    accessor cov4(cov4_buf, hnd, write_only, no_init);
    accessor cov5(cov5_buf, hnd, write_only, no_init);
    accessor cov6(cov6_buf, hnd, write_only, no_init);
    accessor cov9(cov9_buf, hnd, write_only, no_init);

    // map 76
    hnd.parallel_for(DOMAIN_SIZE, [=](id<1> item_id) {
      const int global_id = item_id + 1;

      float nou1[U_V_W_ARRAY_SIZE];
      float nou2[U_V_W_ARRAY_SIZE];
      float nou3[U_V_W_ARRAY_SIZE];
      float nou4[U_V_W_ARRAY_SIZE];
      float nou5[U_V_W_ARRAY_SIZE];
      float nou6[U_V_W_ARRAY_SIZE];
      float nou9[U_V_W_ARRAY_SIZE];

      const int u0 = 0;
      int i_vel2;
      int j_vel2;
      int k_vel2;
      int k_vel2_range;
      int j_vel2_range;
      int i_vel2_range;
      int k_vel2_rel;
      int j_vel2_rel;
      int i_vel2_rel;
      k_vel2_range = (((KP + 1) - 1) + 1);
      j_vel2_range = ((JP - 1) + 1);
      i_vel2_range = ((IP - 1) + 1);
      k_vel2_rel = (global_id / (j_vel2_range * i_vel2_range));
      k_vel2 = k_vel2_rel + 1;
      j_vel2_rel = ((global_id - (k_vel2_rel * (j_vel2_range * i_vel2_range))) / i_vel2_range);
      j_vel2 = j_vel2_rel + 1;
      i_vel2_rel = ((global_id - (k_vel2_rel * (j_vel2_range * i_vel2_range))) -
                    (j_vel2_rel * i_vel2_range));
      i_vel2 = i_vel2_rel + 1;

      if ((k_vel2 < KP)) {
        nou1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = (u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                       i_vel2 - 1, j_vel2, k_vel2)] +
                               u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                       j_vel2, k_vel2)]) /
                              2.;
        diu1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = (-u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                        i_vel2 - 1, j_vel2, k_vel2)] +
                               u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                       j_vel2, k_vel2)]) /
                              dx1[F1D2C((-1), i_vel2)];
        nou5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = (v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                       j_vel2 - 1, k_vel2)] +
                               v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                       j_vel2, k_vel2)]) /
                              2.;
        diu5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = (-v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                        j_vel2 - 1, k_vel2)] +
                               v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2,
                                       j_vel2, k_vel2)]) /
                              dy1[F1D2C(0, j_vel2)];
        nou9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            (w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                     k_vel2 - 1)] +
             w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                     k_vel2)]) /
            2.;
        diu9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            (-w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                      k_vel2 - 1)] +
             w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                     k_vel2)]) /
            dzn[F1D2C((-1), k_vel2)];
        cov1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = nou1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0,
                                         i_vel2, j_vel2, k_vel2)] *
                              diu1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0,
                                         i_vel2, j_vel2, k_vel2)];
        cov5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i_vel2, j_vel2,
                   k_vel2)] = nou5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0,
                                         i_vel2, j_vel2, k_vel2)] *
                              diu5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0,
                                         i_vel2, j_vel2, k_vel2)];
        cov9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            nou9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                       k_vel2)] *
            diu9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                       k_vel2)];
      }
      if ((k_vel2 < KP)) {
        nou2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            (dx1[F1D2C((-1), i_vel2 + 1)] * v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                                    0, 0, i_vel2, j_vel2 - 1, k_vel2)] +
             dx1[F1D2C((-1), i_vel2)] * v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                                i_vel2 + 1, j_vel2 - 1, k_vel2)]) /
            (dx1[F1D2C((-1), i_vel2)] + dx1[F1D2C((-1), i_vel2 + 1)]);
        diu2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            2. *
            (-u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2 - 1,
                      k_vel2)] +
             u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                     k_vel2)]) /
            (dy1[F1D2C(0, j_vel2 - 1)] + dy1[F1D2C(0, j_vel2)]);
        cov2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            nou2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                       k_vel2)] *
            diu2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                       k_vel2)];
      }
      nou3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (dx1[F1D2C((-1), i_vel2 + 1)] * w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                                                  0, i_vel2, j_vel2, k_vel2 - 1)] +
           dx1[F1D2C((-1), i_vel2)] * w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                              i_vel2 + 1, j_vel2, k_vel2 - 1)]) /
          (dx1[F1D2C((-1), i_vel2)] + dx1[F1D2C((-1), i_vel2 + 1)]);
      diu3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (-u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                    k_vel2 - 1)] +
           u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)]) /
          dzs[F1D2C((-1), k_vel2 - 1)];
      cov3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          nou3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] *
          diu3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)];
      if ((k_vel2 < KP)) {
        nou4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            (dy1[F1D2C(0, j_vel2 + 1)] * u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                                                 0, i_vel2 - 1, j_vel2, k_vel2)] +
             dy1[F1D2C(0, j_vel2)] * u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                             i_vel2 - 1, j_vel2 + 1, k_vel2)]) /
            (dy1[F1D2C(0, j_vel2)] + dy1[F1D2C(0, j_vel2 + 1)]);
        diu4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            2. *
            (-v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2 - 1, j_vel2,
                      k_vel2)] +
             v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                     k_vel2)]) /
            (dx1[F1D2C((-1), i_vel2 - 1)] + dx1[F1D2C((-1), i_vel2)]);
        cov4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
            (nou4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                        k_vel2)] -
             u0) *
            diu4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                       k_vel2)];
      }
      nou6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (dy1[F1D2C(0, j_vel2 + 1)] * w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                               i_vel2, j_vel2, k_vel2 - 1)] +
           dy1[F1D2C(0, j_vel2)] * w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                           i_vel2, j_vel2 + 1, k_vel2 - 1)]) /
          (dy1[F1D2C(0, j_vel2)] + dy1[F1D2C(0, j_vel2 + 1)]);
      diu6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (-v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                    k_vel2 - 1)] +
           v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)]) /
          dzs[F1D2C((-1), k_vel2 - 1)];
      cov6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          nou6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] *
          diu6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)];
    });
  });

  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor u(u_buf, hnd, read_only);
    accessor v(v_buf, hnd, read_only);
    accessor w(w_buf, hnd, read_only);
    accessor dx1(dx1_buf, hnd, read_only);
    accessor dy1(dy1_buf, hnd, read_only);
    accessor dzn(dzn_buf, hnd, read_only);

    accessor cov7(cov7_buf, hnd, write_only, no_init);
    accessor cov8(cov8_buf, hnd, write_only, no_init);
    accessor diu7(diu7_buf, hnd, write_only, no_init);
    accessor diu8(diu8_buf, hnd, write_only, no_init);

    // map 133
    hnd.parallel_for(DOMAIN_SIZE, [=](id<1> item_id) {
      const int global_id = item_id + 1;

      float nou7[U_V_W_ARRAY_SIZE];
      float nou8[U_V_W_ARRAY_SIZE];

      const int u0 = 0;
      int i_vel2;
      int j_vel2;
      int k_vel2;
      int k_vel2_range;
      int j_vel2_range;
      int i_vel2_range;
      int k_vel2_rel;
      int j_vel2_rel;
      int i_vel2_rel;
      k_vel2_range = (((KP - 1) - 1) + 1);
      j_vel2_range = ((JP - 1) + 1);
      i_vel2_range = ((IP - 1) + 1);
      k_vel2_rel = (global_id / (j_vel2_range * i_vel2_range));
      k_vel2 = k_vel2_rel + 1;
      j_vel2_rel = ((global_id - (k_vel2_rel * (j_vel2_range * i_vel2_range))) / i_vel2_range);
      j_vel2 = j_vel2_rel + 1;
      i_vel2_rel = ((global_id - (k_vel2_rel * (j_vel2_range * i_vel2_range))) -
                    (j_vel2_rel * i_vel2_range));
      i_vel2 = i_vel2_rel + 1;
      nou7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (dzn[F1D2C((-1), k_vel2 + 1)] * u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                                                  0, i_vel2 - 1, j_vel2, k_vel2)] +
           dzn[F1D2C((-1), k_vel2)] * u[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                              i_vel2 - 1, j_vel2, k_vel2 + 1)]) /
          (dzn[F1D2C((-1), k_vel2)] + dzn[F1D2C((-1), k_vel2 + 1)]);
      diu7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          2. *
          (-w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2 - 1, j_vel2,
                    k_vel2)] +
           w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)]) /
          (dx1[F1D2C((-1), i_vel2 - 1)] + dx1[F1D2C((-1), i_vel2)]);
      cov7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (nou7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2,
                      k_vel2)] -
           u0) *
          diu7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)];
      nou8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          (dzn[F1D2C((-1), k_vel2 + 1)] * v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                                                  0, i_vel2, j_vel2 - 1, k_vel2)] +
           dzn[F1D2C((-1), k_vel2)] * v[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                                              i_vel2, j_vel2 - 1, k_vel2 + 1)]) /
          (dzn[F1D2C((-1), k_vel2)] + dzn[F1D2C((-1), k_vel2 + 1)]);
      diu8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          2. *
          (-w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2 - 1,
                    k_vel2)] +
           w[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)]) /
          (dy1[F1D2C(0, j_vel2 - 1)] + dy1[F1D2C(0, j_vel2)]);
      cov8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] =
          nou8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)] *
          diu8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i_vel2, j_vel2, k_vel2)];
    });
  });

  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor u(u_buf, hnd, read_only);
    accessor v(v_buf, hnd, read_only);
    accessor w(w_buf, hnd, read_only);
    accessor dx1(dx1_buf, hnd, read_only);
    accessor dy1(dy1_buf, hnd, read_only);
    accessor dzn(dzn_buf, hnd, read_only);
    accessor dzs(dzs_buf, hnd, read_only);

    accessor diu1(diu1_buf, hnd, read_only);
    accessor diu2(diu2_buf, hnd, read_only);
    accessor diu3(diu3_buf, hnd, read_only);
    accessor diu4(diu4_buf, hnd, read_only);
    accessor diu5(diu5_buf, hnd, read_only);
    accessor diu6(diu6_buf, hnd, read_only);
    accessor diu7(diu7_buf, hnd, read_only);
    accessor diu8(diu8_buf, hnd, read_only);
    accessor diu9(diu9_buf, hnd, read_only);
    accessor cov1(cov1_buf, hnd, read_only);
    accessor cov2(cov2_buf, hnd, read_only);
    accessor cov3(cov3_buf, hnd, read_only);
    accessor cov4(cov4_buf, hnd, read_only);
    accessor cov5(cov5_buf, hnd, read_only);
    accessor cov6(cov6_buf, hnd, read_only);
    accessor cov7(cov7_buf, hnd, read_only);
    accessor cov8(cov8_buf, hnd, read_only);
    accessor cov9(cov9_buf, hnd, read_only);

    accessor f_1(f_buf, hnd, write_only, no_init);
    accessor g_1(g_buf, hnd, write_only, no_init);
    accessor h_1(h_buf, hnd, write_only, no_init);

    // map 218
    hnd.parallel_for(DOMAIN_SIZE, [=](id<1> item_id) {
      const int global_id = item_id + 1;

      float dfu1[U_V_W_ARRAY_SIZE];
      float dfv1[U_V_W_ARRAY_SIZE];
      float dfw1[U_V_W_ARRAY_SIZE];

      const float vn = 15.83 * 0.000001;
      const int u0 = 0;
      float covx1;
      int i;
      int j;
      int k;
      float covy1;
      float covz1;
      float covc;
      float df;
      int k_range;
      int j_range;
      int i_range;
      int k_rel;
      int j_rel;
      int i_rel;
      k_range = ((KP - 1) + 1);
      j_range = ((JP - 1) + 1);
      i_range = ((IP - 1) + 1);
      k_rel = (global_id / (j_range * i_range));
      k = k_rel + 1;
      j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
      j = j_rel + 1;
      i_rel = ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
      i = i_rel + 1;

      covx1 = (dx1[F1D2C((-1), i + 1)] *
                   cov1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i, j, k)] +
               dx1[F1D2C((-1), i)] * cov1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1),
                                                0, 0, i + 1, j, k)]) /
              (dx1[F1D2C((-1), i)] + dx1[F1D2C((-1), i + 1)]);
      covy1 = (cov2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
               cov2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j + 1, k)]) /
              2.;
      covz1 = (cov3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
               cov3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
              2.;
      covc = covx1 + covy1 + covz1;
      dfu1[F3D2C(((IP - 0) + 1), ((JP - 1) + 1), 0, 1, 1, i, j, k)] =
          2. *
              (-diu1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i, j, k)] +
               diu1[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i + 1, j,
                          k)]) /
              (dx1[F1D2C((-1), i)] + dx1[F1D2C((-1), i + 1)]) +
          (-diu2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
           diu2[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j + 1, k)]) /
              dy1[F1D2C(0, j)] +
          (-diu3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
           diu3[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
              dzn[F1D2C((-1), k)];
      df = vn * dfu1[F3D2C(((IP - 0) + 1), ((JP - 1) + 1), 0, 1, 1, i, j, k)];
      f_1[F3D2C(((IP - 0) + 1), ((JP - 0) + 1), 0, 0, 0, i, j, k)] = -covc + df;
      covx1 = (cov4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
               cov4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i + 1, j, k)]) /
              2.;
      covy1 = (dy1[F1D2C(0, j + 1)] *
                   cov5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i, j, k)] +
               dy1[F1D2C(0, j)] * cov5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0,
                                             0, i, j + 1, k)]) /
              (dy1[F1D2C(0, j)] + dy1[F1D2C(0, j + 1)]);
      covz1 = (cov6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
               cov6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
              2.;
      covc = covx1 + covy1 + covz1;
      dfv1[F3D2C(((IP - 1) + 1), ((JP - 0) + 1), 1, 0, 1, i, j, k)] =
          (-diu4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
           diu4[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i + 1, j, k)]) /
              dx1[F1D2C((-1), i)] +
          2. *
              (-diu5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i, j, k)] +
               diu5[F3D2C((((IP + 2) - (-1)) + 1), (((JP + 2) - 0) + 1), (-1), 0, 0, i, j + 1,
                          k)]) /
              (dy1[F1D2C(0, j)] + dy1[F1D2C(0, j + 1)]) +
          (-diu6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
           diu6[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
              dzn[F1D2C((-1), k)];
      df = vn * dfv1[F3D2C(((IP - 1) + 1), ((JP - 0) + 1), 1, 0, 1, i, j, k)];
      g_1[F3D2C(((IP - 0) + 1), ((JP - 0) + 1), 0, 0, 0, i, j, k)] = -covc + df;
      if ((k < (KP - 1))) {
        covx1 = (cov7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
                 cov7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i + 1, j, k)]) /
                2.;
        covy1 = (cov8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
                 cov8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j + 1, k)]) /
                2.;
        covz1 =
            (dzn[F1D2C((-1), k + 1)] *
                 cov9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
             dzn[F1D2C((-1), k)] *
                 cov9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
            (dzn[F1D2C((-1), k)] + dzn[F1D2C((-1), k + 1)]);
        covc = covx1 + covy1 + covz1;
        dfw1[F3D2C(((IP - 1) + 1), ((JP - 1) + 1), 1, 1, 1, i, j, k)] =
            (-diu7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
             diu7[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i + 1, j, k)]) /
                dx1[F1D2C((-1), i)] +
            (-diu8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
             diu8[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j + 1, k)]) /
                dy1[F1D2C(0, j)] +
            (-diu9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k)] +
             diu9[F3D2C((((IP + 2) - 0) + 1), (((JP + 2) - 0) + 1), 0, 0, 0, i, j, k + 1)]) /
                dzs[F1D2C((-1), k)];
        df = vn * dfw1[F3D2C(((IP - 1) + 1), ((JP - 1) + 1), 1, 1, 1, i, j, k)];
        h_1[F3D2C(((IP - 0) + 1), ((JP - 0) + 1), 0, 0, 0, i, j, k)] = -covc + df;
      }
    });
  });
}
