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
#ifndef IP
    #define IP 10
#endif
#ifndef JP
    #define JP 10
#endif
#ifndef KP
    #define KP 90
#endif


constexpr unsigned int DOMAIN_SIZE = (unsigned int) IP * (unsigned int) JP * (unsigned int) KP;

constexpr unsigned int DX_ARRAY_SIZE = IP + 3;
constexpr unsigned int DY_ARRAY_SIZE = JP + 2;
constexpr unsigned int DZ_ARRAY_SIZE = KP + 4;

// The velfg fortran code uses a (0,:ip+1), (0:jp+1), (0:kp+1) range.
// The original definition from LES starts at -1 and ends at p+2, but we
// ignore this here for simplicity. Those two additional points are used as
// halo which is not used in velfg.
constexpr unsigned int IP_U_V_W = IP + 2;
constexpr unsigned int JP_U_V_W = JP + 2;
constexpr unsigned int KP_U_V_W = KP + 2;

constexpr unsigned int U_V_W_ARRAY_SIZE = IP_U_V_W * JP_U_V_W * KP_U_V_W;

constexpr unsigned int IP_F_G_H = IP + 1;
constexpr unsigned int JP_F_G_H = JP + 1;
constexpr unsigned int KP_F_G_H = KP + 1;

constexpr unsigned int F_G_H_ARRAY_SIZE = IP_F_G_H * JP_F_G_H * KP_F_G_H;

/// These are absolute values.
constexpr unsigned int OFFSET_I_J_KM1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 0);
constexpr unsigned int OFFSET_I_JM1_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 0, 1);
constexpr unsigned int OFFSET_IM1_J_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 0, 1, 1);
constexpr unsigned int OFFSET_IP1_JM1_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 2, 0, 1);
constexpr unsigned int OFFSET_IP1_J_KM1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 2, 1, 0);
constexpr unsigned int OFFSET_I_JP1_KM1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 2, 0);
constexpr unsigned int OFFSET_I_JM1_KP1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 0, 2) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_IM1_J_KP1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 0, 1, 2) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_IM1_JP1_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 0, 2, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_I_J_KP1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 2) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_I_JP1_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 2, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);
constexpr unsigned int OFFSET_IP1_J_K =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 2, 1, 1) -
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);

/// Steps in the k dimension result in highest C array offset.
/// The u array stencil reach could be slightly smaller keeping all array
/// reaches the same seems better than saving the 90 points of buffer space.
constexpr unsigned int REACH_NEG = OFFSET_I_J_KM1;
constexpr unsigned int REACH_POS = OFFSET_I_J_KM1;

/// negative + postitive reach
constexpr unsigned int STENCIL_REACH = REACH_NEG + REACH_POS;

/// We start at (1, 1, 1)
constexpr unsigned int U_V_W_IDX_1_1_1 =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 1, 1, 1);

/// Lowest accessed index is (0, 1, 1)
constexpr unsigned int U_V_W_LOWEST_IDX =
    F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, 0, 1, 1);

constexpr unsigned int F_G_H_IDX_1_1_1 =
    F3D2C(IP_F_G_H, JP_F_G_H, 0, 0, 0, 1, 1, 1);
