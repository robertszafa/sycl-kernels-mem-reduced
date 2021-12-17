#include "CL/sycl/properties/accessor_properties.hpp"
#include <CL/sycl.hpp>
#include <iostream>
#include <vector>

#if FPGA || FPGA_EMULATOR
#include <sycl/ext/intel/fpga_extensions.hpp>
#endif

#include "sw2d_sizes.hpp"

using namespace sycl;

void sw2d_reduced(queue &q, const std::vector<int> &wet, const std::vector<float> &eta,
                const std::vector<float> &u, const std::vector<float> &v,
                const std::vector<float> &h, std::vector<float> &etann, std::vector<float> &un,
                std::vector<float> &vn) {

}
