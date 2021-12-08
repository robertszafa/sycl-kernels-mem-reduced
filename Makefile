# Domain size is parameterized.
ifndef IP
IP := 10
endif
ifndef JP
JP := 10
endif
ifndef KERNEL
KERNEL := reduced
endif

CXX := dpcpp
CXXFLAGS += -g -std=c++17 -O2 -DIP=$(IP) -DJP=$(JP) -D$(KERNEL)

SRC := src/velfg.cpp
BIN := bin/velfg_$(KERNEL)_$(IP)x$(JP)

.PHONY: host fpga_emu fpga 

all: host
host: $(BIN)
fpga_emu: $(BIN).fpga_emu
fpga: $(BIN).fpga
report: $(BIN).a


$(BIN): $(SRC) | bin
	$(CXX) $(CXXFLAGS) -o $@ $(SRC)

$(BIN).fpga_emu: $(SRC) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -DFPGA_EMULATOR=1

$(BIN).fpga: $(BIN).dev.o | bin
	$(CXX) $(CXXFLAGS) -fintelfpga $^ -o $@ -Xshardware

$(BIN).dev.o: $(SRC) | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -c $^ -o $@ -DFPGA=1

# This is just for generating fpga resource report.
$(BIN).a:  $(BIN).dev.o | bin
	$(CXX) $(CXXFLAGS) -fintelfpga -fsycl-link $^ -o $@ -Xshardware

# Make bin/ dir if doesn't exist
bin:
	mkdir $@

clean:
	rm -rf *.o *.d *.out *.mon *.emu *.aocr *.aoco *.prj *.fpga_emu *.fpga *.a bin/*
