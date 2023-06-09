#pragma once

constexpr unsigned int F1D2C(unsigned int i_lb, unsigned int ix) {
  return (ix - i_lb);
}
constexpr unsigned int F2D2C(unsigned int i_rng, unsigned int i_lb,
                             unsigned int j_lb, unsigned int ix,
                             unsigned int jx) {
  return (i_rng * (jx - j_lb) + ix - i_lb);
}
constexpr unsigned int F3D2C(unsigned int i_rng, unsigned int j_rng,
                             unsigned int i_lb, unsigned int j_lb,
                             unsigned int k_lb, unsigned int ix,
                             unsigned int jx, unsigned int kx) {
  return (i_rng * j_rng * (kx - k_lb) + i_rng * (jx - j_lb) + ix - i_lb);
}
constexpr unsigned int F4D2C(unsigned int i_rng, unsigned int j_rng,
                             unsigned int k_rng, unsigned int i_lb,
                             unsigned int j_lb, unsigned int k_lb,
                             unsigned int l_lb, unsigned int ix,
                             unsigned int jx, unsigned int kx,
                             unsigned int lx) {
  return (i_rng * j_rng * k_rng * (lx - l_lb) + i_rng * j_rng * (kx - k_lb) +
          i_rng * (jx - j_lb) + ix - i_lb);
}

// Domain size is supplied by build system.
#ifndef NX
  #define NX 500
#endif
#ifndef NY
  #define NY 500
#endif
#ifndef NZ
  #define NZ 100
#endif

constexpr unsigned int DOMAIN_SIZE =
    (unsigned int)NX * (unsigned int)NY * (unsigned int)NZ;

constexpr unsigned int ARRAY_SIZE_1D = NX + 2;

constexpr unsigned int NX_U_V_W = NX + 2;
constexpr unsigned int NY_U_V_W = NY + 2;
constexpr unsigned int NZ_U_V_W = NZ + 2;

constexpr unsigned int U_ARRAY_SIZE = NX_U_V_W * NY_U_V_W * NZ_U_V_W;

// /// These are absolute values.
constexpr unsigned int OFFSET_I_J_KM1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 0);
constexpr unsigned int OFFSET_I_JM1_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 0, 1);
constexpr unsigned int OFFSET_IM1_J_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 0, 1, 1);
constexpr unsigned int OFFSET_NX1_JM1_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 2, 0, 1);
constexpr unsigned int OFFSET_NX1_J_KM1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 2, 1, 0);
constexpr unsigned int OFFSET_I_NY1_KM1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 2, 0);
constexpr unsigned int OFFSET_I_JM1_NZ1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 0, 2) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_IM1_J_NZ1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 0, 1, 2) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_IM1_NY1_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 0, 2, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_I_J_NZ1 =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 2) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_I_NY1_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 2, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_NX1_J_K =
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 2, 1, 1) -
    F3D2C(NX_U_V_W, NY_U_V_W, 0, 0, 0, 1, 1, 1);

constexpr int nx = NX;
constexpr int ny = NY;
constexpr int nz = NZ;
constexpr float t_chip = 0.0005;
constexpr float chip_height = 0.016;
constexpr float chip_width = 0.016;
constexpr float amb_temp = 80.0;
constexpr float dx = chip_height / NX;
constexpr float dy = chip_width / NY;
constexpr float dz = t_chip / NZ;
constexpr float cap = 0.5 * 1.75e6 * t_chip * dx * dy;
constexpr float rx = dy / (2.0 * 100 * t_chip * dx);
constexpr float ry = dx / (2.0 * 100 * t_chip * dy);
constexpr float rz = dz / (100 * dx * dy);
constexpr float max_slope = 3.0e6 / (0.5 * t_chip * 1.75e6);
constexpr float dt = 0.001 / max_slope;
constexpr float stepdivcap = dt / cap;
constexpr float ce = stepdivcap / rx;
constexpr float cw = ce;
constexpr float cn = stepdivcap / ry;
constexpr float cs = cn;
constexpr float ct = stepdivcap / rz;
constexpr float cb = ct;
constexpr float cc = 1.0 - (2.0 * ce + 2.0 * cn + 3.0 * ct);
