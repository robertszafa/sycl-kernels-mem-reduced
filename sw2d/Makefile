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


CXX := dpcpp
CXXFLAGS += -std=c++17 -O2 -DNX=$(NX) -DNY=$(NY) -D$(KERNEL)
# CXXFLAGS += -g

SRC := src/sw2d.cpp
HDR := src/kernel_sw2d_$(KERNEL).hpp src/sw2d_sizes.hpp
BIN := bin/sw2d_$(KERNEL)_$(NX)x$(NY)

.PHONY: host fpga_emu fpga 

all: host
host: $(BIN)
fpga_emu: $(BIN).fpga_emu
fpga: $(BIN).fpga
report: $(BIN).a 


$(BIN): $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

$(BIN).fpga_emu: $(SRC) $(HDR) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga $< -o $@ -DFPGA_EMULATOR=1

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
