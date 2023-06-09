#include <CL/sycl.hpp>
#include <array>
#include <iostream>

#if FPGA || FPGA_EMULATOR
  #include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "diffusion_sizes.hpp"

using namespace sycl;

double diffusion_swi(
    queue &q, const std::vector<float> &crlato_0,
    const std::vector<float> &crlatu_0, const std::vector<float> &acrlat0_0,
    const std::vector<float> &crlavo_0, const std::vector<float> &crlavu_0,
    const std::vector<float> &pp_in_0, const std::vector<float> &w_in_0,
    const std::vector<float> &hdmask_0, const std::vector<float> &u_in_0,
    const std::vector<float> &v_in_0, std::vector<float> &pp_out_1,
    std::vector<float> &w_out_1, std::vector<float> &u_out_1,
    std::vector<float> &v_out_1) {

  range<1> num_items{pp_in_0.size()};

  buffer u_in_0_buf(u_in_0);
  buffer v_in_0_buf(v_in_0);
  buffer w_in_0_buf(w_in_0);
  buffer pp_in_0_buf(pp_in_0);
  buffer hdmask_0_buf(hdmask_0);
  buffer crlato_0_buf(crlato_0);
  buffer crlatu_0_buf(crlatu_0);
  buffer crlavo_0_buf(crlavo_0);
  buffer crlavu_0_buf(crlavu_0);
  buffer acrlat0_0_buf(acrlat0_0);

  buffer u_out_1_buf(u_out_1.data(), num_items);
  buffer v_out_1_buf(v_out_1.data(), num_items);
  buffer w_out_1_buf(w_out_1.data(), num_items);
  buffer pp_out_1_buf(pp_out_1.data(), num_items);

  // 16 temporary 3D arrays.
  buffer pp_tmp_buf(u_in_0);
  buffer w_tmp_buf(u_in_0);
  buffer v_tmp_buf(u_in_0);
  buffer u_tmp_buf(u_in_0);
  buffer tmp_lap_1104_buf(u_in_0);
  buffer ms_sdfg_1330___local_hdweight_1693_buf(u_in_0);
  buffer tmp_lap_857_buf(u_in_0);
  buffer tmp_lap_610_buf(u_in_0);
  buffer tmp_lap_363_buf(u_in_0);
  buffer ms_sdfg_1330___local_frac_1_dx_1660_buf(u_in_0);
  buffer tmp_T_sqr_s_1351_buf(u_in_0);
  buffer tmp_S_sqr_uv_1352_buf(u_in_0);
  buffer ms_sdfg_1330___local_smag_u_1696_buf(u_in_0);
  buffer ms_sdfg_1330___local_smag_v_1719_buf(u_in_0);
  buffer ms_sdfg_1330___local_smag_u_1696__1_buf(u_in_0);
  buffer ms_sdfg_1330___local_smag_v_1719__1_buf(u_in_0);

  // q.submit([&](handler &hnd) {

  //   accessor u_in(u_in_0_buf, hnd, read_only);
  //   accessor v_in(v_in_0_buf, hnd, read_only);
  //   accessor w_in(w_in_0_buf, hnd, read_only);
  //   accessor pp_in(pp_in_0_buf, hnd, read_only);
  //   accessor hdmask(hdmask_0_buf, hnd, read_only);

  //   accessor crlato(crlato_0_buf, hnd, read_only);
  //   accessor crlatu(crlatu_0_buf, hnd, read_only);

  //   accessor crlavo(crlavo_0_buf, hnd, read_only);
  //   accessor crlavu(crlavu_0_buf, hnd, read_only);

  //   accessor acrlat0(acrlat0_0_buf, hnd, read_only);

  //   accessor u_out(u_out_1_buf, hnd, write_only, no_init);
  //   accessor v_out(v_out_1_buf, hnd, write_only, no_init);
  //   accessor w_out(w_out_1_buf, hnd, write_only, no_init);
  //   accessor pp_out(pp_out_1_buf, hnd, write_only, no_init);

  //   // 16 temporary 3D arrays.
  //   accessor pp_tmp(pp_tmp_buf, hnd, read_write);
  //   accessor w_tmp(w_tmp_buf, hnd, read_write);
  //   accessor v_tmp(v_tmp_buf, hnd, read_write);
  //   accessor u_tmp(u_tmp_buf, hnd, read_write);
  //   accessor tmp_lap_1104(tmp_lap_1104_buf, hnd, read_write);
  //   accessor
  //   ms_sdfg_1330___local_hdweight_1693(ms_sdfg_1330___local_hdweight_1693_buf,
  //   hnd, read_write);

  //   accessor tmp_lap_857(tmp_lap_857_buf, hnd, read_write);
  //   accessor tmp_lap_610(tmp_lap_610_buf, hnd, read_write);
  //   accessor tmp_lap_363(tmp_lap_363_buf, hnd, read_write);

  //   accessor
  //   ms_sdfg_1330___local_frac_1_dx_1660(ms_sdfg_1330___local_frac_1_dx_1660_buf,
  //   hnd, read_write); accessor tmp_t_sqr_s_1351(tmp_T_sqr_s_1351_buf, hnd,
  //   read_write); accessor tmp_s_sqr_uv_1352(tmp_S_sqr_uv_1352_buf, hnd,
  //   read_write);

  //   accessor
  //   ms_sdfg_1330___local_smag_u_1696(ms_sdfg_1330___local_smag_u_1696_buf,
  //   hnd, read_write); accessor
  //   ms_sdfg_1330___local_smag_v_1719(ms_sdfg_1330___local_smag_v_1719_buf,
  //   hnd, read_write); accessor
  //   ms_sdfg_1330___local_smag_u_1696__1(ms_sdfg_1330___local_smag_u_1696__1_buf,
  //   hnd, read_write); accessor
  //   ms_sdfg_1330___local_smag_v_1719__1(ms_sdfg_1330___local_smag_v_1719__1_buf,
  //   hnd, read_write);

  //   hnd.single_task<class diffusion_superkernel>([=]()
  //   [[intel::kernel_args_restrict]] {
  //     for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

  //     }
  //     // RF4A End Inline
  //   });
  // });

  q.submit([&](handler &hnd) {
    accessor pp_in(pp_in_0_buf, hnd, read_only);
    accessor crlato(crlato_0_buf, hnd, read_only);
    accessor crlatu(crlatu_0_buf, hnd, read_only);

    accessor tmp_lap_1104(tmp_lap_1104_buf, hnd, write_only);

    hnd.single_task<class map_0>([=]() [[intel::kernel_args_restrict]] {
      for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {
        float local_delta_1767_in;
        float local_delta_1764_in;
        float local_laplacian_1761_in;
        int i;
        int j;
        int k;
        int k_range;
        int j_range;
        int i_range;
        int k_rel;
        int j_rel;
        int i_rel;
        k_range = (((KP + 1) - 1) + 1);
        j_range = ((JP - 1) + 1);
        i_range = ((IP - 1) + 1);
        k_rel = (global_id / (j_range * i_range));
        k = k_rel + 1;
        j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
        j = j_rel + 1;
        i_rel =
            ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        i = i_rel + 1;

        local_delta_1767_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                         i - 1, j, k)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)]);
        local_delta_1764_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                         i + 1, j, k)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)]);
        local_laplacian_1761_in =
            (((pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k + 1)] +
               pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k - 1)]) -
              (2.0 * pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)])) +
             (crlato[F1D2C(0, i)] * local_delta_1764_in)) +
            (crlatu[F1D2C(0, i)] * local_delta_1767_in);
        tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)] = local_laplacian_1761_in;
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor hdmask(hdmask_0_buf, hnd, read_only);
    accessor ms_sdfg_1330___local_hdweight_1693(
        ms_sdfg_1330___local_hdweight_1693_buf, hnd, write_only);
    hnd.single_task<class map_1>([=]() [[intel::kernel_args_restrict]] {
      for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

        int i;
        int j;
        int k;
        int k_range;
        int j_range;
        int i_range;
        int k_rel;
        int j_rel;
        int i_rel;
        k_range = (((KP + 1) - 1) + 1);
        j_range = ((JP - 1) + 1);
        i_range = ((IP - 1) + 1);
        k_rel = (global_id / (j_range * i_range));
        k = k_rel + 1;
        j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
        j = j_rel + 1;
        i_rel =
            ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        i = i_rel + 1;
        ms_sdfg_1330___local_hdweight_1693[F3D2C(
            (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j, k)] =
            (0.5 * hdmask[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)]);
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor pp_in(pp_in_0_buf, hnd, read_only);
    accessor hdmask(hdmask_0_buf, hnd, read_only);
    accessor crlato(crlato_0_buf, hnd, read_only);
    accessor crlatu(crlatu_0_buf, hnd, read_only);
    accessor tmp_lap_1104(tmp_lap_1104_buf, hnd, read_only);
    accessor pp_out(pp_out_1_buf, hnd, write_only, no_init);
    hnd.single_task<class map_2>([=]() [[intel::kernel_args_restrict]] {
      for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

        float local_delta_1803_in;
        float local_delta_1797_in;
        float local_fly_1336_in;
        float local_diffusive_flux_y_1800_in;
        float local_delta_1794_in;
        float local_delta_1788_in;
        float local_fly_1302_in;
        float local_diffusive_flux_y_1791_in;
        float local_delta_flux_y_1282_in;
        float local_delta_1785_in;
        float local_delta_1779_in;
        float local_flx_1267_in;
        float local_diffusive_flux_x_1782_in;
        float local_delta_1776_in;
        float local_delta_1770_in;
        float local_flx_1235_in;
        float local_diffusive_flux_x_1773_in;
        float local_delta_flux_x_1217_in;
        int i;
        int j;
        int k;
        int k_range;
        int j_range;
        int i_range;
        int k_rel;
        int j_rel;
        int i_rel;
        k_range = (((KP + 1) - 1) + 1);
        j_range = ((JP - 1) + 1);
        i_range = ((IP - 1) + 1);
        k_rel = (global_id / (j_range * i_range));
        k = k_rel + 1;
        j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
        j = j_rel + 1;
        i_rel =
            ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        i = i_rel + 1;
        local_delta_1803_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                         i - 1, j, k)]);
        local_delta_1797_in =
            (tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)] -
             tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i - 1, j, k)]);
        local_fly_1336_in = (crlato[F1D2C(0, i)] - 1 * local_delta_1797_in);

        if ((local_fly_1336_in * local_delta_1803_in) > 0.0) {
          local_diffusive_flux_y_1800_in = 0.0;
        } else {
          local_diffusive_flux_y_1800_in = local_fly_1336_in;
        }
        local_delta_1794_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                         i + 1, j, k)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)]);
        local_delta_1788_in =
            (tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i + 1, j, k)] -
             tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)]);
        local_fly_1302_in = (crlato[F1D2C(0, i)] * local_delta_1788_in);
        if ((local_fly_1302_in * local_delta_1794_in) > 0.0) {
          local_diffusive_flux_y_1791_in = 0.0;
        } else {
          local_diffusive_flux_y_1791_in = local_fly_1302_in;
        }
        local_delta_flux_y_1282_in =
            local_diffusive_flux_y_1791_in - local_diffusive_flux_y_1800_in;
        local_delta_1785_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k - 1)]);
        local_delta_1779_in =
            (tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)] -
             tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k - 1)]);
        local_flx_1267_in = local_delta_1779_in;

        if ((local_flx_1267_in * local_delta_1785_in) > 0.0) {
          local_diffusive_flux_x_1782_in = 0.0;
        } else {
          local_diffusive_flux_x_1782_in = local_flx_1267_in;
        }
        local_delta_1776_in =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k + 1)] -
             pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)]);
        local_delta_1770_in =
            (tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k + 1)] -
             tmp_lap_1104[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)]);
        local_flx_1235_in = local_delta_1770_in;
        if ((local_flx_1235_in * local_delta_1776_in) > 0.0) {
          local_diffusive_flux_x_1773_in = 0.0;
        } else {
          local_diffusive_flux_x_1773_in = local_flx_1235_in;
        }
        local_delta_flux_x_1217_in =
            local_diffusive_flux_x_1773_in - local_diffusive_flux_x_1782_in;
        pp_out[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                     k)] =
            (pp_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                         j, k)] -
             (hdmask[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)] *
              (local_delta_flux_x_1217_in + local_delta_flux_y_1282_in)));
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor w_in(w_in_0_buf, hnd, read_only);
    accessor crlato(crlato_0_buf, hnd, read_only);
    accessor crlatu(crlatu_0_buf, hnd, read_only);
    accessor tmp_lap_857(tmp_lap_857_buf, hnd, write_only);
    hnd.single_task<class map_3>([=]() [[intel::kernel_args_restrict]] {
      for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

        float local_delta_1812_in;
        float local_delta_1809_in;
        float local_laplacian_1806_in;
        int i;
        int j;
        int k;
        int k_range;
        int j_range;
        int i_range;
        int k_rel;
        int j_rel;
        int i_rel;
        k_range = (((KP + 1) - 1) + 1);
        j_range = ((JP - 1) + 1);
        i_range = ((IP - 1) + 1);
        k_rel = (global_id / (j_range * i_range));
        k = k_rel + 1;
        j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
        j = j_rel + 1;
        i_rel =
            ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        i = i_rel + 1;
        local_delta_1812_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                        i - 1, j, k)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)]);
        local_delta_1809_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                        i + 1, j, k)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)]);
        local_laplacian_1806_in =
            ((((w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k + 1)] +
                w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k - 1)]) -
               (2.0 * w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)])) +
              (crlato[F1D2C(0, i)] * local_delta_1809_in)) +
             (crlatu[F1D2C(0, i)] * local_delta_1812_in));
        tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] = local_laplacian_1806_in;
      }
    });
  });

  q.submit([&](handler &hnd) {
    accessor w_in(w_in_0_buf, hnd, read_only);
    accessor hdmask(hdmask_0_buf, hnd, read_only);
    accessor tmp_lap_857(tmp_lap_857_buf, hnd, read_only);
    accessor crlato(crlato_0_buf, hnd, read_only);
    accessor crlatu(crlatu_0_buf, hnd, read_only);
    accessor w_out(w_out_1_buf, hnd, write_only, no_init);
    hnd.single_task<class map_4>([=]() [[intel::kernel_args_restrict]] {
      for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

        float local_delta_1848_in;
        float local_delta_1842_in;
        float local_fly_1089_in;
        float local_diffusive_flux_y_1845_in;
        float local_delta_1839_in;
        float local_delta_1833_in;
        float local_fly_1055_in;
        float local_diffusive_flux_y_1836_in;
        float local_delta_flux_y_1035_in;
        float local_delta_1830_in;
        float local_delta_1824_in;
        float local_flx_1020_in;
        float local_diffusive_flux_x_1827_in;
        float local_delta_1821_in;
        float local_delta_1815_in;
        float local_flx_988_in;
        float local_diffusive_flux_x_1818_in;
        float local_delta_flux_x_970_in;
        int i;
        int j;
        int k;
        int k_range;
        int j_range;
        int i_range;
        int k_rel;
        int j_rel;
        int i_rel;
        k_range = (((KP + 1) - 1) + 1);
        j_range = ((JP - 1) + 1);
        i_range = ((IP - 1) + 1);
        k_rel = (global_id / (j_range * i_range));
        k = k_rel + 1;
        j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
        j = j_rel + 1;
        i_rel =
            ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
        i = i_rel + 1;
        local_delta_1848_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                        i - 1, j, k)]);
        local_delta_1842_in =
            (tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k)] -
             tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i - 1, j, k)]);
        local_fly_1089_in = (crlato[F1D2C(0, i)] - 1 * local_delta_1842_in);

        if ((local_fly_1089_in * local_delta_1848_in) > 0.0) {
          local_diffusive_flux_y_1845_in = 0.0;
        } else {
          local_diffusive_flux_y_1845_in = local_fly_1089_in;
        }
        local_delta_1839_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                        i + 1, j, k)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)]);
        local_delta_1833_in =
            (tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i + 1, j, k)] -
             tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k)]);
        local_fly_1055_in = (crlato[F1D2C(0, i)] * local_delta_1833_in);
        if ((local_fly_1055_in * local_delta_1839_in) > 0.0) {
          local_diffusive_flux_y_1836_in = 0.0;
        } else {
          local_diffusive_flux_y_1836_in = local_fly_1055_in;
        }
        local_delta_flux_y_1035_in =
            local_diffusive_flux_y_1836_in - local_diffusive_flux_y_1845_in;
        local_delta_1830_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k - 1)]);
        local_delta_1824_in =
            (tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k)] -
             tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k - 1)]);
        local_flx_1020_in = local_delta_1824_in;

        if ((local_flx_1020_in * local_delta_1830_in) > 0.0) {
          local_diffusive_flux_x_1827_in = 0.0;
        } else {
          local_diffusive_flux_x_1827_in = local_flx_1020_in;
        }
        local_delta_1821_in =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k + 1)] -
             w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)]);
        local_delta_1815_in =
            (tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k + 1)] -
             tmp_lap_857[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k)]);
        local_flx_988_in = local_delta_1815_in;

        if ((local_flx_988_in * local_delta_1821_in) > 0.0) {
          local_diffusive_flux_x_1818_in = 0.0;
        } else {
          local_diffusive_flux_x_1818_in = local_flx_988_in;
        }
        local_delta_flux_x_970_in =
            local_diffusive_flux_x_1818_in - local_diffusive_flux_x_1827_in;
        w_out[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                    k)] =
            (w_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i,
                        j, k)] -
             (hdmask[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)] *
              (local_delta_flux_x_970_in + local_delta_flux_y_1035_in)));
      }
    });
  });

    q.submit([&](handler &hnd) {
      accessor v_in(v_in_0_buf, hnd, read_only);
      accessor crlato(crlato_0_buf, hnd, read_only);
      accessor crlatu(crlatu_0_buf, hnd, read_only);
      accessor tmp_lap_610(tmp_lap_610_buf, hnd, write_only);
      hnd.single_task<class map_5>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_delta_1857_in;
          float local_delta_1854_in;
          float local_laplacian_1851_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_delta_1857_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1854_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_laplacian_1851_in =
              ((((v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k + 1)] +
                  v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k - 1)]) -
                 (2.0 * v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1),
                                   0, 0, 0, i, j, k)])) +
                (crlato[F1D2C(0, i)] * local_delta_1854_in)) +
               (crlatu[F1D2C(0, i)] * local_delta_1857_in));
          tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                            i, j, k)] = local_laplacian_1851_in;
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor v_in(v_in_0_buf, hnd, read_only);
      accessor hdmask(hdmask_0_buf, hnd, read_only);
      accessor crlato(crlato_0_buf, hnd, read_only);
      accessor tmp_lap_610(tmp_lap_610_buf, hnd, read_only);
      accessor v_tmp(v_tmp_buf, hnd, write_only);
      hnd.single_task<class map_6>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_delta_1893_in;
          float local_delta_1887_in;
          float local_fly_842_in;
          float local_diffusive_flux_y_1890_in;
          float local_delta_1884_in;
          float local_delta_1878_in;
          float local_fly_808_in;
          float local_diffusive_flux_y_1881_in;
          float local_delta_flux_y_788_in;
          float local_delta_1875_in;
          float local_delta_1869_in;
          float local_flx_773_in;
          float local_diffusive_flux_x_1872_in;
          float local_delta_1866_in;
          float local_delta_1860_in;
          float local_flx_741_in;
          float local_diffusive_flux_x_1863_in;
          float local_delta_flux_x_723_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_delta_1893_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)]);
          local_delta_1887_in =
              (tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)] -
               tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i - 1, j, k)]);
          local_fly_842_in = (crlato[F1D2C(0, i)] - 1 * local_delta_1887_in);

          if ((local_fly_842_in * local_delta_1893_in) > 0.0) {
            local_diffusive_flux_y_1890_in = 0.0;
          } else {
            local_diffusive_flux_y_1890_in = local_fly_842_in;
          }
          local_delta_1884_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1878_in =
              (tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i + 1, j, k)] -
               tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)]);
          local_fly_808_in = (crlato[F1D2C(0, i)] * local_delta_1878_in);

          if ((local_fly_808_in * local_delta_1884_in) > 0.0) {
            local_diffusive_flux_y_1881_in = 0.0;
          } else {
            local_diffusive_flux_y_1881_in = local_fly_808_in;
          }
          local_delta_flux_y_788_in =
              local_diffusive_flux_y_1881_in - local_diffusive_flux_y_1890_in;
          local_delta_1875_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)]);
          local_delta_1869_in =
              (tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)] -
               tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k - 1)]);
          local_flx_773_in = local_delta_1869_in;

          if ((local_flx_773_in * local_delta_1875_in) > 0.0) {
            local_diffusive_flux_x_1872_in = 0.0;
          } else {
            local_diffusive_flux_x_1872_in = local_flx_773_in;
          }
          local_delta_1866_in =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] -
               v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1860_in =
              (tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k + 1)] -
               tmp_lap_610[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)]);
          local_flx_741_in = local_delta_1860_in;

          if ((local_flx_741_in * local_delta_1866_in) > 0.0) {
            local_diffusive_flux_x_1863_in = 0.0;
          } else {
            local_diffusive_flux_x_1863_in = local_flx_741_in;
          }
          local_delta_flux_x_723_in =
              local_diffusive_flux_x_1863_in - local_diffusive_flux_x_1872_in;
          v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                      k)] =
              (v_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               (hdmask[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k)] *
                (local_delta_flux_x_723_in + local_delta_flux_y_788_in)));
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor u_in(u_in_0_buf, hnd, read_only);
      accessor crlato(crlato_0_buf, hnd, read_only);
      accessor crlatu(crlatu_0_buf, hnd, read_only);
      accessor tmp_lap_363(tmp_lap_363_buf, hnd, write_only);
      hnd.single_task<class map_7>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_delta_1902_in;
          float local_delta_1899_in;
          float local_laplacian_1896_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_delta_1902_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1899_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_laplacian_1896_in =
              ((((u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k + 1)] +
                  u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k - 1)]) -
                 (2.0 * u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1),
                                   0, 0, 0, i, j, k)])) +
                (crlato[F1D2C(0, i)] * local_delta_1899_in)) +
               (crlatu[F1D2C(0, i)] * local_delta_1902_in));
          tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                            i, j, k)] = local_laplacian_1896_in;
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor u_in(u_in_0_buf, hnd, read_only);
      accessor v_in(v_in_0_buf, hnd, read_only);
      accessor hdmask(hdmask_0_buf, hnd, read_only);
      accessor crlato(crlato_0_buf, hnd, read_only);
      accessor tmp_lap_363(tmp_lap_363_buf, hnd, read_only);
      accessor u_tmp(u_tmp_buf, hnd, write_only);
      hnd.single_task<class map_8>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_delta_1938_in;
          float local_delta_1932_in;
          float local_fly_595_in;
          float local_diffusive_flux_y_1935_in;
          float local_delta_1929_in;
          float local_delta_1923_in;
          float local_fly_561_in;
          float local_diffusive_flux_y_1926_in;
          float local_delta_flux_y_541_in;
          float local_delta_1920_in;
          float local_delta_1914_in;
          float local_flx_526_in;
          float local_delta_1911_in;
          float local_delta_1905_in;
          float local_flx_494_in;
          float local_diffusive_flux_x_1908_in;
          float local_delta_flux_x_476_in;

          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_delta_1938_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i - 1, j, k)]);
          local_delta_1932_in =
              (tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)] -
               tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i - 1, j, k)]);
          local_fly_595_in = (crlato[F1D2C(0, i)] - 1 * local_delta_1932_in);

          if ((local_fly_595_in * local_delta_1938_in) > 0.0) {
            local_diffusive_flux_y_1935_in = 0.0;
          } else {
            local_diffusive_flux_y_1935_in = local_fly_595_in;
          }
          local_delta_1929_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i + 1, j, k)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1923_in =
              (tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i + 1, j, k)] -
               tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)]);
          local_fly_561_in = (crlato[F1D2C(0, i)] * local_delta_1923_in);

          if ((local_fly_561_in * local_delta_1929_in) > 0.0) {
            local_diffusive_flux_y_1926_in = 0.0;
          } else {
            local_diffusive_flux_y_1926_in = local_fly_561_in;
          }
          local_delta_flux_y_541_in =
              local_diffusive_flux_y_1926_in - local_diffusive_flux_y_1935_in;
          local_delta_1920_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k - 1)]);
          local_delta_1914_in =
              (tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)] -
               tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k - 1)]);
          local_flx_526_in = local_delta_1914_in;

          if ((local_flx_526_in * local_delta_1920_in) > 0.0) {
            local_diffusive_flux_y_1926_in = 0.0;
          } else {
            local_diffusive_flux_y_1926_in = local_flx_526_in;
          }
          local_delta_1911_in =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k + 1)] -
               u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)]);
          local_delta_1905_in =
              (tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k + 1)] -
               tmp_lap_363[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)]);
          local_flx_494_in = local_delta_1905_in;

          if ((local_flx_494_in * local_delta_1911_in) > 0.0) {
            local_diffusive_flux_x_1908_in = 0.0;
          } else {
            local_diffusive_flux_x_1908_in = local_flx_494_in;
          }
          local_delta_flux_x_476_in =
              local_diffusive_flux_x_1908_in - local_diffusive_flux_y_1926_in;
          u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                      k)] =
              (u_in[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                          i, j, k)] -
               (hdmask[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k)] *
                (local_delta_flux_x_476_in + local_delta_flux_y_541_in)));
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor v_tmp(v_tmp_buf, hnd, read_only);
      accessor u_tmp(u_tmp_buf, hnd, read_only);
      accessor acrlat0(acrlat0_0_buf, hnd, read_only);
      accessor tmp_t_sqr_s_1351(tmp_T_sqr_s_1351_buf, hnd, write_only);
      hnd.single_task<class map_10>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float ms_sdfg_1330___local_frac_1_dx_1660;
          float local_delta_1944_in;
          float local_delta_1941_in;
          float local_t_s_1667_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          ms_sdfg_1330___local_frac_1_dx_1660 = acrlat0[F1D2C(0, i)] * 5729.58;
          local_delta_1944_in =
              (u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k - 1)] -
               u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)]);
          local_delta_1941_in =
              (v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i - 1, j, k)] -
               v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)]);
          local_t_s_1667_in =
              (local_delta_1941_in * 5729.58 / 6371229.0) -
              (local_delta_1944_in * ms_sdfg_1330___local_frac_1_dx_1660);
          tmp_t_sqr_s_1351[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                 0, 0, i, j, k)] =
              local_t_s_1667_in * local_t_s_1667_in;
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor v_tmp(v_tmp_buf, hnd, read_only);
      accessor u_tmp(u_tmp_buf, hnd, read_only);
      accessor acrlat0(acrlat0_0_buf, hnd, read_only);
      accessor tmp_s_sqr_uv_1352(tmp_S_sqr_uv_1352_buf, hnd, write_only);
      hnd.single_task<class map_11>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float ms_sdfg_1330___local_frac_1_dx_1660;
          float local_delta_1950_in;
          float local_delta_1947_in;
          float local_s_uv_1680_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          ms_sdfg_1330___local_frac_1_dx_1660 = acrlat0[F1D2C(0, i)] * 5729.58;
          local_delta_1950_in =
              (v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k + 1)] -
               v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)]);
          local_delta_1947_in =
              (u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i + 1, j, k)] -
               u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)]);
          local_s_uv_1680_in =
              ((local_delta_1947_in * (5729.58 / 6371229.0)) +
               (local_delta_1950_in * ms_sdfg_1330___local_frac_1_dx_1660));
          tmp_s_sqr_uv_1352[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                  0, 0, i, j, k)] =
              local_s_uv_1680_in * local_s_uv_1680_in;
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor tmp_t_sqr_s_1351(tmp_T_sqr_s_1351_buf, hnd, read_only);
      accessor tmp_s_sqr_uv_1352(tmp_S_sqr_uv_1352_buf, hnd, read_only);
      accessor ms_sdfg_1330___local_hdweight_1693(
          ms_sdfg_1330___local_hdweight_1693_buf, hnd, read_only);
      accessor ms_sdfg_1330___local_smag_u_1696(
          ms_sdfg_1330___local_smag_u_1696_buf, hnd, write_only);
      hnd.single_task<class map_12>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_avg_1953_in;
          float local_avg_1956_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_avg_1956_in =
              (0.5 * (tmp_s_sqr_uv_1352[F3D2C((((IP + 1) - 0) + 1),
                                              (((JP + 1) - 0) + 1), 0, 0, 0,
                                              i - 1, j, k)] +
                      tmp_s_sqr_uv_1352[F3D2C((((IP + 1) - 0) + 1),
                                              (((JP + 1) - 0) + 1), 0, 0, 0, i,
                                              j, k)]));
          local_avg_1953_in =
              (0.5 * (tmp_t_sqr_s_1351[F3D2C((((IP + 1) - 0) + 1),
                                             (((JP + 1) - 0) + 1), 0, 0, 0, i,
                                             j, k + 1)] +
                      tmp_t_sqr_s_1351[F3D2C((((IP + 1) - 0) + 1),
                                             (((JP + 1) - 0) + 1), 0, 0, 0, i,
                                             j, k)]));
          ms_sdfg_1330___local_smag_u_1696[F3D2C(
              (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j, k)] =
              ((0.3 * sqrt((local_avg_1953_in + local_avg_1956_in))) -
               ms_sdfg_1330___local_hdweight_1693[F3D2C((((IP + 1) - 0) + 1),
                                                        (((JP + 1) - 0) + 1), 0,
                                                        0, 0, i, j, k)]);
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor ms_sdfg_1330___local_smag_u_1696(
          ms_sdfg_1330___local_smag_u_1696_buf, hnd, read_only);
      accessor ms_sdfg_1330___local_smag_u_1696__1(
          ms_sdfg_1330___local_smag_u_1696__1_buf, hnd, write_only);
      hnd.single_task<class map_13>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float dace_min0___local_smag_u_1696_out;
          float dace_max0___dace_min1___local_smag_u_1696_out;
          float dace_max1___dace_min1___local_smag_u_1696_out;
          float dace_min1___local_smag_u_1696_out;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          dace_min0___local_smag_u_1696_out = 0.5;
          dace_max0___dace_min1___local_smag_u_1696_out = 0.0;
          dace_max1___dace_min1___local_smag_u_1696_out =
              ms_sdfg_1330___local_smag_u_1696[F3D2C((((IP + 1) - 0) + 1),
                                                     (((JP + 1) - 0) + 1), 0, 0,
                                                     0, i, j, k)];
          if (dace_max0___dace_min1___local_smag_u_1696_out <
              dace_max1___dace_min1___local_smag_u_1696_out) {
            dace_min1___local_smag_u_1696_out =
                dace_max1___dace_min1___local_smag_u_1696_out;
          } else {
            dace_min1___local_smag_u_1696_out =
                dace_max0___dace_min1___local_smag_u_1696_out;
          }
          if (dace_min0___local_smag_u_1696_out <
              dace_min1___local_smag_u_1696_out) {
            ms_sdfg_1330___local_smag_u_1696__1[F3D2C(
                (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j, k)] =
                dace_min0___local_smag_u_1696_out;
          } else {
            ms_sdfg_1330___local_smag_u_1696__1[F3D2C(
                (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j, k)] =
                dace_min1___local_smag_u_1696_out;
          }
        }
      });
    });

    q.submit([&](handler &hnd) {
      accessor ms_sdfg_1330___local_smag_u_1696__1(
          ms_sdfg_1330___local_smag_u_1696__1_buf, hnd, read_only);
      accessor u_tmp(u_tmp_buf, hnd, read_only);
      accessor crlato(crlato_0_buf, hnd, read_only);
      accessor crlatu(crlatu_0_buf, hnd, read_only);
      accessor u_out(u_out_1_buf, hnd, write_only, no_init);
      hnd.single_task<class map_14>([=]() [[intel::kernel_args_restrict]] {
        for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

          float local_lapu_1726_in;
          int i;
          int j;
          int k;
          int k_range;
          int j_range;
          int i_range;
          int k_rel;
          int j_rel;
          int i_rel;
          k_range = (((KP + 1) - 1) + 1);
          j_range = ((JP - 1) + 1);
          i_range = ((IP - 1) + 1);
          k_rel = (global_id / (j_range * i_range));
          k = k_rel + 1;
          j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
          j = j_rel + 1;
          i_rel =
              ((global_id - (k_rel * (j_range * i_range))) - (j_rel * i_range));
          i = i_rel + 1;
          local_lapu_1726_in =
              ((((u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                              0, i, j, k + 1)] +
                  u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                              0, i, j, k - 1)]) -
                 (2.0 * u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1),
                                    0, 0, 0, i, j, k)])) +
                (crlato[F1D2C(0, i)] *
                 (u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                              0, i + 1, j, k)] -
                  u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                              0, i, j, k)]))) +
               (crlatu[F1D2C(0, i)] *
                (u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i - 1, j, k)] -
                 u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                             0, i, j, k)])));
          u_out[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                      k)] =
              (u_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)] +
               (ms_sdfg_1330___local_smag_u_1696__1[F3D2C((((IP + 1) - 0) + 1),
                                                          (((JP + 1) - 0) + 1),
                                                          0, 0, 0, i, j, k)] *
                local_lapu_1726_in));
        }
      });
    });

      q.submit([&](handler &hnd) {
        accessor tmp_t_sqr_s_1351(tmp_T_sqr_s_1351_buf, hnd, read_only);
        accessor tmp_s_sqr_uv_1352(tmp_S_sqr_uv_1352_buf, hnd, read_only);
        accessor ms_sdfg_1330___local_hdweight_1693(
            ms_sdfg_1330___local_hdweight_1693_buf, hnd, read_only);
        accessor ms_sdfg_1330___local_smag_v_1719(
            ms_sdfg_1330___local_smag_v_1719_buf, hnd, write_only);
        hnd.single_task<class map_15>([=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

            int i;
            int j;
            int k;
            int k_range;
            int j_range;
            int i_range;
            int k_rel;
            int j_rel;
            int i_rel;
            k_range = (((KP + 1) - 1) + 1);
            j_range = ((JP - 1) + 1);
            i_range = ((IP - 1) + 1);
            k_rel = (global_id / (j_range * i_range));
            k = k_rel + 1;
            j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
            j = j_rel + 1;
            i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                     (j_rel * i_range));
            i = i_rel + 1;
            ms_sdfg_1330___local_smag_v_1719[F3D2C(
                (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j, k)] =
                ((0.3 *
                  sqrt(((0.5 * (tmp_t_sqr_s_1351[F3D2C((((IP + 1) - 0) + 1),
                                                       (((JP + 1) - 0) + 1), 0,
                                                       0, 0, i, j, k)] +
                                tmp_t_sqr_s_1351[F3D2C((((IP + 1) - 0) + 1),
                                                       (((JP + 1) - 0) + 1), 0,
                                                       0, 0, i + 1, j, k)])) +
                        (0.5 * (tmp_s_sqr_uv_1352[F3D2C((((IP + 1) - 0) + 1),
                                                        (((JP + 1) - 0) + 1), 0,
                                                        0, 0, i, j, k)] +
                                tmp_s_sqr_uv_1352[F3D2C(
                                    (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1),
                                    0, 0, 0, i, j, k - 1)]))))) -
                 ms_sdfg_1330___local_hdweight_1693[F3D2C((((IP + 1) - 0) + 1),
                                                          (((JP + 1) - 0) + 1),
                                                          0, 0, 0, i, j, k)]);
          }
        });
      });

      q.submit([&](handler &hnd) {
        accessor ms_sdfg_1330___local_smag_v_1719(
            ms_sdfg_1330___local_smag_v_1719_buf, hnd, read_only);
        accessor ms_sdfg_1330___local_smag_v_1719__1(
            ms_sdfg_1330___local_smag_v_1719__1_buf, hnd, write_only);
        hnd.single_task<class map_16>([=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

            float dace_min0___local_smag_v_1719_out;
            float dace_max0___dace_min1___local_smag_v_1719_out;
            float dace_max1___dace_min1___local_smag_v_1719_out;
            float dace_min1___local_smag_v_1719_out;
            int i;
            int j;
            int k;
            int k_range;
            int j_range;
            int i_range;
            int k_rel;
            int j_rel;
            int i_rel;
            k_range = (((KP + 1) - 1) + 1);
            j_range = ((JP - 1) + 1);
            i_range = ((IP - 1) + 1);
            k_rel = (global_id / (j_range * i_range));
            k = k_rel + 1;
            j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
            j = j_rel + 1;
            i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                     (j_rel * i_range));
            i = i_rel + 1;
            dace_min0___local_smag_v_1719_out = 0.5;
            dace_max0___dace_min1___local_smag_v_1719_out = 0.0;
            dace_max1___dace_min1___local_smag_v_1719_out =
                ms_sdfg_1330___local_smag_v_1719[F3D2C((((IP + 1) - 0) + 1),
                                                       (((JP + 1) - 0) + 1), 0,
                                                       0, 0, i, j, k)];
            if (dace_max0___dace_min1___local_smag_v_1719_out <
                dace_max1___dace_min1___local_smag_v_1719_out) {
              dace_min1___local_smag_v_1719_out =
                  dace_max1___dace_min1___local_smag_v_1719_out;
            } else {
              dace_min1___local_smag_v_1719_out =
                  dace_max0___dace_min1___local_smag_v_1719_out;
            }
            if (dace_min0___local_smag_v_1719_out <
                dace_min1___local_smag_v_1719_out) {
              ms_sdfg_1330___local_smag_v_1719__1[F3D2C(
                  (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                  k)] = dace_min0___local_smag_v_1719_out;
            } else {
              ms_sdfg_1330___local_smag_v_1719__1[F3D2C(
                  (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                  k)] = dace_min1___local_smag_v_1719_out;
            }
          }
        });
      });

      auto event = q.submit([&](handler &hnd) {
        accessor ms_sdfg_1330___local_smag_v_1719__1(
            ms_sdfg_1330___local_smag_v_1719__1_buf, hnd, read_only);
        accessor v_tmp(v_tmp_buf, hnd, read_only);
        accessor crlavo(crlavo_0_buf, hnd, read_only);
        accessor crlavu(crlavu_0_buf, hnd, read_only);
        accessor v_out(v_out_1_buf, hnd, write_only, no_init);
        hnd.single_task<class map_17>([=]() [[intel::kernel_args_restrict]] {
          for (int global_id = 1; global_id <= DOMAIN_SIZE; global_id += 1) {

            float local_lapv_1728_in;
            int i;
            int j;
            int k;
            int k_range;
            int j_range;
            int i_range;
            int k_rel;
            int j_rel;
            int i_rel;
            k_range = (((KP + 1) - 1) + 1);
            j_range = ((JP - 1) + 1);
            i_range = ((IP - 1) + 1);
            k_rel = (global_id / (j_range * i_range));
            k = k_rel + 1;
            j_rel = ((global_id - (k_rel * (j_range * i_range))) / i_range);
            j = j_rel + 1;
            i_rel = ((global_id - (k_rel * (j_range * i_range))) -
                     (j_rel * i_range));
            i = i_rel + 1;
            local_lapv_1728_in =
                ((((v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k + 1)] +
                    v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k - 1)]) -
                   (2.0 *
                    v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)])) +
                  (crlavo[F1D2C(0, i)] *
                   (v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i + 1, j, k)] -
                    v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                0, 0, i, j, k)]))) +
                 (crlavu[F1D2C(0, i)] *
                  (v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i - 1, j, k)] -
                   v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0,
                               0, i, j, k)])));
            v_out[F3D2C(
                  (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0, i, j,
                  k)] = (v_tmp[F3D2C((((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0,
                                  0, 0, i, j, k)] +
                      (ms_sdfg_1330___local_smag_v_1719__1[F3D2C(
                           (((IP + 1) - 0) + 1), (((JP + 1) - 0) + 1), 0, 0, 0,
                           i, j, k)] *
                       local_lapv_1728_in));
          }
        });
      });

      auto start =
          event.get_profiling_info<info::event_profiling::command_start>();
      auto end = event.get_profiling_info<info::event_profiling::command_end>();
      auto time_in_ms = static_cast<double>(end - start) / 1000000;

      return time_in_ms;
    }
