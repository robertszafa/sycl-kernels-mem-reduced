# Domain size is parameterized.
ifndef NX
NX := 500
endif
ifndef NY
NY := 500
endif
ifndef KERNEL
KERNEL := reduced
endif

# NUM_CU is the unroll factor for the swi_reduced kernel top level loop. Compute units
# are not yet implemented in dpcpp, so unrolling the loop is the next best thing.
# NUM_CU only makes sense for FPGA hardware compiles.
ifdef NUM_CU
KERNEL_POSTFIX := _$(NUM_CU)cu
endif

CXX := dpcpp
CXXFLAGS += -std=c++17 -O2 -DNX=$(NX) -DNY=$(NY) -D$(KERNEL) -DNUM_CU=$(NUM_CU)
# CXXFLAGS += -g

SRC := src/sw2d.cpp
HDR := src/kernel_sw2d_$(KERNEL).hpp src/sw2d_sizes.hpp
BIN := bin/sw2d_$(KERNEL)$(KERNEL_POSTFIX)_$(NX)x$(NY)

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

$(BIN).dev.o: $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -c $< -o $@ -DFPGA=1

# This is just for generating fpga resource report.
$(BIN).a:  $(BIN).dev.o $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -fsycl-link $< -o $@ -Xshardware

# Make bin/ dir if doesn't exist
bin:
	mkdir $@

clean:
	rm -rf *.o *.d *.out *.mon *.emu *.aocr *.aoco *.prj *.fpga_emu *.fpga *.a bin/*
