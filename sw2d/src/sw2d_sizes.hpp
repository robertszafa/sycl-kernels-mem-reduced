#pragma once

constexpr unsigned int F1D2C(unsigned int i_lb, unsigned int ix) { return (ix - i_lb); }
constexpr unsigned int F2D2C(unsigned int i_rng, unsigned int i_lb, unsigned int j_lb,
                             unsigned int ix, unsigned int jx) {
  return (i_rng * (jx - j_lb) + ix - i_lb);
}
constexpr unsigned int F3D2C(unsigned int i_rng, unsigned int j_rng, unsigned int i_lb,
                             unsigned int j_lb, unsigned int k_lb, unsigned int ix, unsigned int jx,
                             unsigned int kx) {
  return (i_rng * j_rng * (kx - k_lb) + i_rng * (jx - j_lb) + ix - i_lb);
}
constexpr unsigned int F4D2C(unsigned int i_rng, unsigned int j_rng, unsigned int k_rng,
                             unsigned int i_lb, unsigned int j_lb, unsigned int k_lb,
                             unsigned int l_lb, unsigned int ix, unsigned int jx, unsigned int kx,
                             unsigned int lx) {
  return (i_rng * j_rng * k_rng * (lx - l_lb) + i_rng * j_rng * (kx - k_lb) + i_rng * (jx - j_lb) +
          ix - i_lb);
}

// Domain size is supplied by build system.
#ifndef NX
#define NX 500
#endif
#ifndef NY
#define NY 500
#endif

constexpr unsigned int DOMAIN_SIZE = (unsigned int) NX * (unsigned int) NY;

/// Covers domain plus halo points.
constexpr unsigned int ARRAY_NX = (NX + 2);
constexpr unsigned int ARRAY_NY = (NY + 2);
constexpr unsigned int ARRAY_SIZE = ARRAY_NX * ARRAY_NY;

constexpr float g = 9.81;
constexpr float dt = 0.1;
constexpr float dx = 10.0;
constexpr float dy = 10.0;
constexpr float eps = 0.05;

constexpr unsigned int IDX_1_1 = F2D2C(ARRAY_NY, 0, 0, 1, 1);

/// These are absolute values
constexpr unsigned int OFFSET_J_KP1 = F2D2C(ARRAY_NY, 0, 0, 1, 2) - IDX_1_1;
constexpr unsigned int OFFSET_JP1_K = F2D2C(ARRAY_NY, 0, 0, 2, 1) - IDX_1_1;
constexpr unsigned int OFFSET_J_KM1 = F2D2C(ARRAY_NY, 0, 0, 1, 1) - IDX_1_1;
constexpr unsigned int OFFSET_JM1_K = F2D2C(ARRAY_NY, 0, 0, 1, 1) - IDX_1_1;

