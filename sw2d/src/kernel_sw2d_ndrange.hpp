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

void sw2d_ndrange(queue &q, const std::vector<int> &wet, const std::vector<float> &eta,
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

  // Intermediate arrays.
  buffer<float> du___dyn_buf(array_range);
  buffer<float> dv___dyn_buf(array_range);
  buffer<float> etan_buf(array_range);

  // Submit kernels in-order to the same blocking queue.
  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor eta(eta_buf, hnd, read_only);
    accessor du___dyn(du___dyn_buf, hnd, write_only, no_init);
    accessor dv___dyn(dv___dyn_buf, hnd, write_only, no_init);

    hnd.parallel_for<class map49>(DOMAIN_SIZE, [=](id<1> item_id) {
      const uint global_id = item_id + 1;
      const uint j_range = ((NX - 1) + 1);
      const uint k_range = ((NY - 1) + 1);
      const uint j_rel = global_id / k_range;
      const uint j = j_rel + 1;
      const uint k_rel = (global_id - (j_rel * k_range));
      const uint k = k_rel + 1;

      du___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
          -dt * g *
          (eta[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] -
           eta[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)]) /
          dx;
      dv___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
          -dt * g *
          (eta[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] -
           eta[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)]) /
          dy;
    });
  });

  q.submit([&](handler &hnd) {
    accessor u(u_buf, hnd, read_only);
    accessor wet(wet_buf, hnd, read_only);
    accessor v(v_buf, hnd, read_only);

    accessor du___dyn(du___dyn_buf, hnd, read_only);
    accessor dv___dyn(dv___dyn_buf, hnd, read_only);

    accessor un(un_buf, hnd, write_only, no_init);
    accessor vn(vn_buf, hnd, write_only, no_init);

    hnd.parallel_for<class map55>(DOMAIN_SIZE, [=](id<1> item_id) {
      const uint global_id = item_id + 1;
      const uint j_range = ((NX - 1) + 1);
      const uint k_range = ((NY - 1) + 1);
      const uint j_rel = global_id / k_range;
      const uint j = j_rel + 1;
      const uint k_rel = (global_id - (j_rel * k_range));
      const uint k = k_rel + 1;

      un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] = 0.0;
      if (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] == 1) {
        if ((wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] == 1) ||
            (du___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] > 0.0))
          un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
              u[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
              du___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      } else {
        if ((wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] == 1) &&
            (du___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] < 0.0))
          un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
              u[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
              du___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      }
      vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] = 0.0;
      if (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] == 1) {
        if ((wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] == 1) ||
            (dv___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] > 0.0))
          vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
              v[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
              dv___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      } else {
        if ((wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] == 1) &&
            (dv___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] < 0.0))
          vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
              v[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
              dv___dyn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      }
    });
  });

  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor un(un_buf, hnd, read_only);
    accessor vn(vn_buf, hnd, read_only);
    accessor h(h_buf, hnd, read_only);
    accessor eta(eta_buf, hnd, read_only);

    accessor etan(etan_buf, hnd, write_only, no_init);

    hnd.parallel_for<class map75>(DOMAIN_SIZE, [=](id<1> item_id) {
      const uint global_id = item_id + 1;
      const uint j_range = ((NX - 1) + 1);
      const uint k_range = ((NY - 1) + 1);
      const uint j_rel = global_id / k_range;
      const uint j = j_rel + 1;
      const uint k_rel = (global_id - (j_rel * k_range));
      const uint k = k_rel + 1;

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

      hep___dyn = 0.5 *
                  (un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
                   (float)fabs(un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      hen___dyn = 0.5 *
                  (un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] -
                   (float)fabs(un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)];
      hue___dyn = hep___dyn + hen___dyn;
      hwp___dyn = 0.5 *
                  (un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)] +
                   (float)fabs(un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)];
      hwn___dyn = 0.5 *
                  (un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)] -
                   (float)fabs(un[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      huw___dyn = hwp___dyn + hwn___dyn;
      hnp___dyn = 0.5 *
                  (vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] +
                   (float)fabs(vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      hnn___dyn = 0.5 *
                  (vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] -
                   (float)fabs(vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)];
      hvn___dyn = hnp___dyn + hnn___dyn;
      hsp___dyn = 0.5 *
                  (vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)] +
                   (float)fabs(vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)];
      hsn___dyn = 0.5 *
                  (vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)] -
                   (float)fabs(vn[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)])) *
                  h[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      hvs___dyn = hsp___dyn + hsn___dyn;
      etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] = eta[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] -
                                                      dt * (hue___dyn - huw___dyn) / dx -
                                                      dt * (hvn___dyn - hvs___dyn) / dy;
    });
  });

  q.submit([&](handler &hnd) {
    // stream debug(1024, 256, hnd);
    accessor wet(wet_buf, hnd, read_only);
    accessor etan(etan_buf, hnd, read_only);
    accessor etann(etann_buf, hnd, write_only, no_init);

    hnd.parallel_for<class map92>(DOMAIN_SIZE, [=](id<1> item_id) {
      const uint global_id = item_id + 1;
      const uint j_range = ((NX - 1) + 1);
      const uint k_range = ((NY - 1) + 1);
      const uint j_rel = global_id / k_range;
      const uint j = j_rel + 1;
      const uint k_rel = (global_id - (j_rel * k_range));
      const uint k = k_rel + 1;

      float term1___shapiro;
      float term2___shapiro;
      float term3___shapiro;

      if (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] == 1) {
        term1___shapiro = (1.0 - 0.25 * eps *
                                     (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] +
                                      wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)] +
                                      wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] +
                                      wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)])) *
                          etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
        term2___shapiro = 0.25 * eps *
                          (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] *
                               etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k + 1)] +
                           wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)] *
                               etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k - 1)]);
        term3___shapiro = 0.25 * eps *
                          (wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] *
                               etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j + 1, k)] +
                           wet[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)] *
                               etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j - 1, k)]);
        etann[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
            term1___shapiro + term2___shapiro + term3___shapiro;
      } else {
        etann[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)] =
            etan[F2D2C((((NY + 1) - 0) + 1), 0, 0, j, k)];
      }
    });
  });
}
