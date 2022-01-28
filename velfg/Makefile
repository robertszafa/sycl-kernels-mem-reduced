# Domain size is parameterized.
ifndef IP
IP := 10
endif
ifndef JP
JP := 10
endif
ifndef KERNEL
KERNEL := swi_reduced
endif

# NUM_CU is the unroll factor for the swi_reduced kernel top level loop. Compute units
# are not yet implemented in dpcpp, so unrolling the loop is the next best thing.
# NUM_CU only makes sense for FPGA hardware compiles.
ifdef NUM_CU
KERNEL_POSTFIX := _$(NUM_CU)cu
endif

CXX := dpcpp
CXXFLAGS += -std=c++17 -O2 -DIP=$(IP) -DJP=$(JP) -D$(KERNEL) -DNUM_CU=$(NUM_CU)
# CXXFLAGS += -g

SRC := src/velfg.cpp
HDR := src/kernel_velfg_$(KERNEL).hpp src/velfg_sizes.hpp
BIN := bin/velfg_$(KERNEL)$(KERNEL_POSTFIX)_$(IP)x$(JP)

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
