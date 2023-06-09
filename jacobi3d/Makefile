# Domain size is parameterized.
ifndef IP
IP := 300
endif
ifndef KP
KP := 300
endif
ifndef JP
JP := 300
endif
ifndef KERNEL
KERNEL := swi_reduced
endif

CXX := dpcpp
CXXFLAGS += -std=c++17 -DIP=$(IP) -DKP=$(KP) -DJP=$(JP) -D$(KERNEL) -DNUM_CU=$(NUM_CU) -m64 
# CXXFLAGS += -g 
CXXFLAGS += -O2 -fsycl-dead-args-optimization


SRC := src/jacobi3d.cpp
HDR := src/kernel_jacobi3d_$(KERNEL).hpp src/jacobi3d_sizes.hpp
BIN := bin/jacobi3d_$(KERNEL)_$(IP)x$(KP)

.PHONY: host fpga_emu fpga 

all: host
host: $(BIN)
gpu: $(BIN).gpu
fpga_emu: $(BIN).fpga_emu
fpga: $(BIN).fpga
report: $(BIN).a 


$(BIN): $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

$(BIN).gpu: $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -DGPU=1 -o $@ $(SRC)

$(BIN).fpga_emu: $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga $< -o $@ -DFPGA_EMULATOR=1 

# To reuse fpga image add: -reuse-exe=$(BIN).fpga
# To add profiling info do:  -Xsprofile
$(BIN).fpga: $(BIN).dev.o | bin
	$(CXX) $(CXXFLAGS) -fintelfpga $< -o $@ -Xshardware 
# -Xsboard=intel_s10sx_pac:pac_s10

$(BIN).dev.o: $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -c $< -o $@ -DFPGA=1 
# -Xsboard=intel_s10sx_pac:pac_s10

# This is just for generating fpga resource report.
$(BIN).a:  $(BIN).dev.o $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -fsycl-link $< -o $@ -Xshardware

# Make bin/ dir if doesn't exist
bin:
	mkdir $@

clean:
	rm -rf *.o *.d *.out *.mon *.emu *.aocr *.aoco *.prj *.fpga_emu *.fpga *.a bin/*
