#include <CL/sycl.hpp>
#include <iostream>
#include <vector>


#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "sw2d_sizes.hpp"

#if swi_reduced
  #include "kernel_sw2d_swi_reduced.hpp"
#elif swi
  #include "kernel_sw2d_swi.hpp"
#elif ndrange_reduced
  #include "kernel_sw2d_ndrange_reduced.hpp"
#elif ndrange
  #include "kernel_sw2d_ndrange.hpp"
#elif pipes
  #include "kernel_sw2d_pipes.hpp"
#else
  #error "At least default reduced should be defined."
#endif

using namespace sycl;

void InitializeArrays(std::vector<float> &eta, std::vector<float> &h, std::vector<float> &u,
                      std::vector<float> &v, std::vector<int> &wet) {
  const float hmin = 0.05;
  std::vector<float> hzero(ARRAY_SIZE, 10.0);

  // ! land boundaries with 10 m elevation
  for (int k = 0; k < ARRAY_NX; ++k) {
    hzero[F2D2C(ARRAY_NX, 0, 0, 0, k)] = -10.0;
    hzero[F2D2C(ARRAY_NX, 0, 0, NY + 1, k)] = -10.0;
  }
  for (int j = 0; j < ARRAY_NY; ++j) {
    hzero[F2D2C(ARRAY_NX, 0, 0, j, 0)] = -10.0;
    hzero[F2D2C(ARRAY_NX, 0, 0, j, NX + 1)] = -10.0;
  }

  for (int j = 0; j < ARRAY_NY; ++j) {
    for (int k = 0; k < ARRAY_NX; ++k) {
      eta[F2D2C(ARRAY_NX, 0, 0, j, k)] = -std::min(0.0f, hzero[F2D2C(ARRAY_NX, 0, 0, j, k)]);
    }
  }

  for (int j = 0; j < ARRAY_NY; ++j) {
    for (int k = 0; k < ARRAY_NX; ++k) {
      h[F2D2C(ARRAY_NX, 0, 0, j, k)] =
          hzero[F2D2C(ARRAY_NX, 0, 0, j, k)] + eta[F2D2C(ARRAY_NX, 0, 0, j, k)];
      wet[F2D2C(ARRAY_NX, 0, 0, j, k)] = 1;

      if (h[F2D2C(ARRAY_NX, 0, 0, j, k)] < hmin) {
        wet[F2D2C(ARRAY_NX, 0, 0, j, k)] = 0;
      }

      u[F2D2C(ARRAY_NX, 0, 0, j, k)] = 0.;
      v[F2D2C(ARRAY_NX, 0, 0, j, k)] = 0.;
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
#elif GPU
  gpu_selector d_selector;
#else
  // The default device selector will select the most performant device.
  default_selector d_selector;
#endif

  try {
    // Enable profiling.
    property_list properties{property::queue::enable_profiling()};
    queue q(d_selector, exception_handler, properties);

    // Print out the device information used for the kernel code.
    std::cout << "Running on device: " << q.get_device().get_info<info::device::name>() << "\n";
    std::cout << "Domain size: " << DOMAIN_SIZE << "\n";

    // host data
    // inputs
    std::vector<int> wet(ARRAY_SIZE);
    std::vector<float> eta(ARRAY_SIZE);
    std::vector<float> u(ARRAY_SIZE);
    std::vector<float> v(ARRAY_SIZE);
    std::vector<float> h(ARRAY_SIZE);
    // outputs
    std::vector<float> etann(ARRAY_SIZE);
    std::vector<float> un(ARRAY_SIZE);
    std::vector<float> vn(ARRAY_SIZE);

    InitializeArrays(eta, h, u, v, wet);

    auto start = std::chrono::steady_clock::now();
    double kernel_time = 0;

#if swi_reduced
    kernel_time = sw2d_swi_reduced(q, wet, eta, u, v, h, etann, un, vn);
#elif swi
    kernel_time = sw2d_swi(q, wet, eta, u, v, h, etann, un, vn);
#elif ndrange_reduced
    kernel_time = sw2d_ndrange_reduced(q, wet, eta, u, v, h, etann, un, vn);
#elif ndrange
    kernel_time = sw2d_ndrange(q, wet, eta, u, v, h, etann, un, vn);
#elif pipes
    kernel_time = sw2d_pipes(q, wet, eta, u, v, h, etann, un, vn);
#else
    #error "At least default reduced should be defined."
#endif

    // Wait for all work to finish.
    q.wait();
    
    auto stop = std::chrono::steady_clock::now();
    double total_time = (std::chrono::duration<double> (stop - start)).count() * 1000.0;

    std::cout << "Kernel time (ms): " << kernel_time << "\n";
    std::cout << "Total time (ms): " << total_time << "\n";

    // Force data movement. 
    InitializeArrays(eta, h, u, v, wet);
  } catch (exception const &e) {
    std::cout << "An exception was caught.\n";
    std::terminate();
  }

  return 0;
}
