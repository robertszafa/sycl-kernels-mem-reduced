#include <CL/sycl.hpp>
#include <array>
#include <iostream>

#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "diffusion_sizes.hpp"

#if swi_reduced
#include "kernel_diffusion_swi_reduced.hpp"
#else
#error "At least default reduced should be defined."
#endif

using namespace sycl;

//************************************
// Initialize the array from 0 to array_size - 1
//************************************
void InitializeArrays(std::vector<float> &u_0, std::vector<float> &v_0, std::vector<float> &w_0) {
  for (unsigned int j = 0; j < U_V_W_ARRAY_SIZE; ++j) {
    u_0[j] = j*0.7;
    v_0[j] = j*0.8;
    w_0[j] = j*0.9;
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
#elif GPU
  gpu_selector d_selector;
#else
  // The default device selector will select the most performant device.
  default_selector d_selector;
#endif

  try {
    property_list properties{property::queue::enable_profiling()};
    queue q(d_selector, exception_handler, properties);

    // inputs
    std::vector<float> pp_in_0(U_V_W_ARRAY_SIZE);
    std::vector<float> u_in_0(U_V_W_ARRAY_SIZE);
    std::vector<float> v_in_0(U_V_W_ARRAY_SIZE);
    std::vector<float> w_in_0(U_V_W_ARRAY_SIZE);
    std::vector<float> hdmask_0(U_V_W_ARRAY_SIZE);
    std::vector<float> crlato_0(ARRAY_SIZE_1D);
    std::vector<float> crlatu_0(ARRAY_SIZE_1D);
    std::vector<float> crlavo_0(ARRAY_SIZE_1D);
    std::vector<float> crlavu_0(ARRAY_SIZE_1D);
    std::vector<float> acrlat0_0(ARRAY_SIZE_1D);
    // vector
    std::vector<float> pp_out_1(U_V_W_ARRAY_SIZE);
    std::vector<float> u_out_1(U_V_W_ARRAY_SIZE);
    std::vector<float> v_out_1(U_V_W_ARRAY_SIZE);
    std::vector<float> w_out_1(U_V_W_ARRAY_SIZE);

    InitializeArrays(u_in_0, v_in_0, w_in_0);

    // Print out the device information used for the kernel code.
    // std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Domain size: " << DOMAIN_SIZE << "\n";
    auto start = std::chrono::steady_clock::now();
    double kernel_time = 0;

#if swi_reduced
  kernel_time = diffusion_swi_reduced(q, crlato_0, crlatu_0, acrlat0_0, crlavo_0, crlavu_0,
                                      pp_in_0, w_in_0, hdmask_0, u_in_0, v_in_0, pp_out_1,
                                      w_out_1, u_out_1, v_out_1);
#else
    #error "At least default reduced should be defined."
#endif

    // Wait for all work to finish.
    q.wait();

    auto stop = std::chrono::steady_clock::now();
    double total_time = (std::chrono::duration<double>(stop - start)).count() * 1000.0;

    std::cout << "Kernel time (ms): " << kernel_time << "\n";
    std::cout << "Total time (ms): " << total_time << "\n";

    // Force data movement.
    // InitializeArrays(u_in_0, v_in_0, w_in_0);
  } catch (exception const &e) {
    std::cout << "An exception was caught.\n";
    std::terminate();
  }

  return 0;
}
