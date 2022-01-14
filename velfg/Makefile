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


CXX := dpcpp
CXXFLAGS += -std=c++17 -O2 -DIP=$(IP) -DJP=$(JP) -D$(KERNEL)
# CXXFLAGS += -g

SRC := src/velfg.cpp
HDR := src/kernel_velfg_$(KERNEL).hpp src/velfg_sizes.hpp
BIN := bin/velfg_$(KERNEL)_$(IP)x$(JP)

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
