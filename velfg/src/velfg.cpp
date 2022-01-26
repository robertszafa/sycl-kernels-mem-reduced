#include <CL/sycl.hpp>
#include <iostream>
#include <vector>
#include <ctime>


#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "velfg_sizes.hpp"

#if swi_reduced
  #include "kernel_velfg_swi_reduced.hpp"
#elif swi
  #include "kernel_velfg_swi.hpp"
#elif ndrange_reduced
  #include "kernel_velfg_ndrange_reduced.hpp"
#elif ndrange
  #include "kernel_velfg_ndrange.hpp"
#elif pipes
  #include "kernel_velfg_pipes.hpp"
#else
  #error "At least default reduced should be defined."
#endif

using namespace sycl;

//************************************
// Initialize the array from 0 to array_size - 1
//************************************
void InitializeArrays(std::vector<float> &u_0, std::vector<float> &v_0, std::vector<float> &w_0,
                      std::vector<float> &dx1, std::vector<float> &dy1, std::vector<float> &dzn,
                      std::vector<float> &dzs_0, std::vector<float> &f_1, std::vector<float> &g_1,
                      std::vector<float> &h_1) {
  // ! Initialisation
  for (unsigned int i = 0; i < DZ_ARRAY_SIZE; ++i) {
    dzn[i] = 1.0;
    dzs_0[i] = 1.0;
  }
  for (unsigned int i = 0; i < DX_ARRAY_SIZE; ++i)
    dx1[i] = 1.0;

  for (unsigned int i = 0; i < DY_ARRAY_SIZE; ++i)
    dy1[i] = 1.0;

  // !--dz vertical direction
  float z2[DZ_ARRAY_SIZE];
  z2[0] = 2.5;
  dzn[0] = 2.5;
  dzn[1] = 2.5;
  for (unsigned int i = 2; i <= 15; ++i)
    dzn[i] = dzn[i - 1] * 1.05;
  for (unsigned int i = 16; i <= 44; ++i)
    dzn[i] = 5.0;
  for (unsigned int i = 45; i < DZ_ARRAY_SIZE; ++i)
    dzn[i] = dzn[i - 1] * 1.0459;

  for (unsigned int i = 1; i < DZ_ARRAY_SIZE; ++i)
    z2[i] = dzn[i - 1] * 1.05;

  dzn[DZ_ARRAY_SIZE - 1] = dzn[DZ_ARRAY_SIZE - 2];
  dzn[0] = dzn[1];

  // First zero all in/out arrays
  for (unsigned int j = 0; j < U_V_W_ARRAY_SIZE; ++j) {
    u_0[j] = 0;
    v_0[j] = 0;
    w_0[j] = 0;
  }
  for (unsigned int j = 0; j < F_G_H_ARRAY_SIZE; ++j) {
    f_1[j] = 0;
    g_1[j] = 0;
    h_1[j] = 0;
  }

  // !-- initial wind profile
  int count = 0;
  for (int i = 0; i <= IP + 1; ++i) {
    for (int k = 1; k <= 78; ++k) {
      for (int j = 1; j <= JP; ++j) {
        u_0[F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, i, j, k)] =
            powf(5. * ((z2[k] + 0.5 * dzn[k]) / 600.), 0.2);
        // u_0[F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, i, j, k)] = j;
      }
    }
  }

  for (int i = 0; i <= 1; ++i) {
    for (int k = 79; k <= KP; ++k) {
      for (int j = 1; j <= JP; ++j) {
        u_0[F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, i, j, k)] =
            u_0[F3D2C(IP_U_V_W, JP_U_V_W, 0, 0, 0, i, j, 77)];
      }
    }
  }
}

// Create an exception handler for asynchronous SYCL exceptions
static auto exception_handler = [](sycl::exception_list e_list) {
  for (std::exception_ptr const &e : e_list) {
    try {
      std::rethrow_exception(e);
    } catch (std::exception const &e) {
#if _DEBUG
      std::cout << "Failure" << std::endl;
#endif
      std::terminate();
    }
  }
};

int main(int argc, char *argv[]) {
  // Create device selector for the device of your interest.
#if FPGA_EMULATOR
  // DPC++ extension: FPGA emulator selector on systems without FPGA card.
  ext::intel::fpga_emulator_selector d_selector;
#elif FPGA
  // DPC++ extension: FPGA selector on systems with FPGA card.
  ext::intel::fpga_selector d_selector;
#else
  // The default device selector will select the most performant device.
  default_selector d_selector;
#endif

  try {
    property_list properties{property::queue::enable_profiling()};
    queue q(d_selector, exception_handler, properties);

    // Print out the device information used for the kernel code.
    std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Domain size: " << DOMAIN_SIZE << "\n";

    // host data
    // inputs
    std::vector<float> u_0(U_V_W_ARRAY_SIZE);
    std::vector<float> v_0(U_V_W_ARRAY_SIZE);
    std::vector<float> w_0(U_V_W_ARRAY_SIZE);
    std::vector<float> dx1(DX_ARRAY_SIZE);
    std::vector<float> dy1(DY_ARRAY_SIZE);
    std::vector<float> dzn(DZ_ARRAY_SIZE);
    std::vector<float> dzs_0(DZ_ARRAY_SIZE);
    // outputs
    std::vector<float> f_1(F_G_H_ARRAY_SIZE);
    std::vector<float> g_1(F_G_H_ARRAY_SIZE);
    std::vector<float> h_1(F_G_H_ARRAY_SIZE);

    InitializeArrays(u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);

    auto start = std::clock();
    double kernel_time = 0;

#if swi_reduced
    kernel_time = velfg_swi_reduced(q, u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
#elif swi
    kernel_time = velfg_swi(q, u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
#elif ndrange_reduced
    kernel_time = velfg_ndrange_reduced(q, u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
#elif ndrange
    kernel_time = velfg_ndrange(q, u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
#elif pipes
    kernel_time = velfg_pipes(q, u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
#else
    #error "At least default reduced should be defined."
#endif

    // Wait for all work to finish.
    q.wait();
    
    auto stop = std::clock();

    std::cout << "\nFinished kernel execution in (ms): " << kernel_time << "\n";
    std::cout << "Finished kernel execution + memory transfer in (ms): " 
              << 1000.0 * (stop - start) / CLOCKS_PER_SEC << "\n";

    // std::cout << f_1[1] << "\n";
    // std::cout << f_1[F_G_H_IDX_1_1_1] << "\n";
    // std::cout << f_1[F_G_H_IDX_1_1_1 + 1] << "\n";

    // Force fpga->cpu data movement. 
    InitializeArrays(u_0, v_0, w_0, dx1, dy1, dzn, dzs_0, f_1, g_1, h_1);
  } catch (exception const &e) {
    std::cout << "An exception was caught.\n";
    std::terminate();
  }

  return 0;
}
