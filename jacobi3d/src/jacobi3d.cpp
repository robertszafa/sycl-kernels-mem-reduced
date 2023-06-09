#include <CL/sycl.hpp>
#include <array>
#include <iostream>

#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "jacobi3d_sizes.hpp"

#if swi_reduced
#include "kernel_jacobi3d_swi_reduced.hpp"
#elif swi
#include "kernel_jacobi3d_swi.hpp"
#else
#error "At least default reduced should be defined."
#endif

using namespace sycl;

//************************************
// Initialize the array from 0 to array_size - 1
//************************************
void InitializeArrays(std::vector<float> &u, std::vector<float> &un) {
  for (unsigned int j = 0; j < U_ARRAY_SIZE; ++j) {
    u[j] = j*0.7;
    un[j] = 0;
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

    std::vector<float> u(U_ARRAY_SIZE + IP*JP);
    std::vector<float> un(U_ARRAY_SIZE + IP*JP);

    InitializeArrays(u, un);

    // Print out the device information used for the kernel code.
    // std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Domain size: " << DOMAIN_SIZE << "\n";
    auto start = std::chrono::steady_clock::now();
    double kernel_time = 0;

#if swi_reduced
  kernel_time = jacobi3d_swi_reduced(q, u, un);
#elif swi
  kernel_time = jacobi3d_swi(q, u, un);
#else
    #error "At least default reduced should be defined."
#endif

    // Wait for all work to finish.
    q.wait();

    auto stop = std::chrono::steady_clock::now();
    double total_time = (std::chrono::duration<double>(stop - start)).count() * 1000.0;

    std::cout << "Kernel time (ms): " << kernel_time << "\n";
    // std::cout << "Total time (ms): " << total_time << "\n";

    // Force data movement.
    // InitializeArrays(u_in_0, v_in_0, w_in_0);
  } catch (exception const &e) {
    std::cout << "An exception was caught.\n";
    std::terminate();
  }

  return 0;
}
