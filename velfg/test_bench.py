import csv
import os
import re

REPEAT = 1
NOT_RUN = True

RESULTS_FILE = 'results_velfg.csv'

BIN_PATH = './bin/'
KERNEL_PREFIX = 'velfg'
KERNEL_TYPES = [
    'pipes',
    'ndrange', 
    'ndrange_reduced', 
    'swi', 
    'swi_reduced_1cu', 
    # 'swi_reduced_2cu', 
    # 'swi_reduced_3cu', 
    # 'swi_reduced_4cu', 
    # 'swi_reduced_5cu', 
    # 'swi_reduced_6cu', 
    # 'fortran',
    # 'fortran_omp',
    # 'cpu_swi',
    # 'cpu_swi_reduced',
    # 'cpu_ndrange',
    # 'cpu_ndrange_reduced',
    # 'gpu_ndrange',
    # 'gpu_ndrange_reduced',
    ]
SIZES = [
    # '10x10', 
    '100x100', 
    '200x200', 
    '300x300',
    '600x600',
    '900x900',
    '1900x1900',
    ]

# Found in report.htlm under area. The numbers seems to be stable, inrespective of kernel source.
BRAM_STATIC_PARTITION = 492
ALMS_STATIC_PARTITION = 89975 # In report this is 'Logic utilization'
REGISTERS_STATIC_PARTITION = 98940
DSP_STATIC_PARTITION = 0

KP_DIM = 90

CPU_DEVICE = 'Intel(R) Xeon(R) Gold 6128 CPU 6 cores @ 3.40GHz'

FPGA_DEVICE = 'Intel PAC Platform (pac_ee00000) Arria 10 FPGA'

GPU_DEVICE = 'Intel(R) UHD Graphics P630'


if __name__ == "__main__":
    header = ['kernel'] + SIZES
    kernel_time_data = []
    total_time_data = []
    throughput_data = []
    ram_usage_data = []
    alm_usage_data = []
    reg_usage_data = []
    dsp_usage_data = []
    freq_data = []

    for kernel_type in KERNEL_TYPES:
        kernel_times = [kernel_type]
        total_times = [kernel_type]
        kernel_throughput = [kernel_type]
        kernel_ram_usage = [kernel_type]
        kernel_alm_usage = [kernel_type]
        kernel_reg_usage = [kernel_type]
        kernel_dsp_usage = [kernel_type]
        kernel_freq = [kernel_type]

        for size in SIZES:
            if 'fortran' in kernel_type:
                binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.exe'
            elif 'cpu' in kernel_type:
                kernel_type_bin_name = kernel_type.strip('cpu_')
                binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type_bin_name}_{size}'
            elif 'gpu' in kernel_type:
                kernel_type_bin_name = kernel_type.strip('gpu_')
                binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type_bin_name}_{size}.gpu'
            else:
                binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga'
            report = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga.prj/acl_quartus_report.txt'

            domain_size = int(size.split('x')[0]) * int(size.split('x')[1]) * KP_DIM

            print(f'Running {binary} {REPEAT} times...')
            
            if not os.path.isfile(binary) or NOT_RUN:
                print(binary + " doesn't exist. Skipping time test..")
                kernel_times.append('N/A')
                total_times.append('N/A')
                kernel_throughput.append('N/A')
            else:
                kernel_time = float("inf")
                total_time = float("inf")

                for _ in range(REPEAT):
                    out = os.popen(binary).read()
                    kernel_time_str = re.findall(r"Kernel time \(ms\):\s*(.+)", out)
                    total_time_str = re.findall(r"Total time \(ms\):\s*(.+)", out)
                    try:
                        kernel_time = float(kernel_time_str[0]) if float(kernel_time_str[0]) < kernel_time else kernel_time
                        total_time = float(total_time_str[0]) if float(total_time_str[0]) < total_time else total_time
                    except:
                        print(f'**ERROR** run {binary} & got output:\n {out}')

                kernel_times.append(kernel_time)
                total_times.append(total_time)
                kernel_throughput.append(domain_size / kernel_time)
            
            # For FPGAs, check BRAM usage and design frequency
            if not 'fortran' in kernel_type and not 'cpu' in kernel_type and not 'gpu' in kernel_type:
                if not os.path.isfile(report):
                    print(report + " doesn't exist. Skipping resource usage..")
                    kernel_ram_usage.append('N/A')
                    kernel_alm_usage.append('N/A')
                    kernel_reg_usage.append('N/A')
                    kernel_dsp_usage.append('N/A')
                    kernel_freq.append('N/A')
                else:
                    with open(report, 'r') as report_f:
                        report_str = report_f.read()

                    ram_usage_str = re.findall("RAM blocks: (.*?)/", report_str)
                    alm_usage_str = re.findall("Logic utilization: (.*?)/", report_str)
                    reg_usage_str = re.findall("Registers: ([,\d]+)", report_str)
                    dsp_usage_str = re.findall("DSP blocks: (.*?)/", report_str)
                    freq_str = re.findall("Actual clock freq: (\d+)", report_str)

                    rams = 0
                    alms = 0
                    regs = 0
                    dsps = 0
                    freq = 0
                    try:
                        rams = int(re.sub("[^0-9]", "", ram_usage_str[0])) - BRAM_STATIC_PARTITION
                        alms = int(re.sub("[^0-9]", "", alm_usage_str[0])) - ALMS_STATIC_PARTITION
                        regs = int(re.sub("[^0-9]", "", reg_usage_str[0])) - REGISTERS_STATIC_PARTITION
                        dsps = int(re.sub("[^0-9]", "", dsp_usage_str[0])) - DSP_STATIC_PARTITION
                        freq = freq_str[0]
                    except Exception as e:
                        print('Something went wrong with  getting ram usage from ' + report + ". Skipping.." + str(e))

                    kernel_ram_usage.append(rams)
                    kernel_alm_usage.append(alms)
                    kernel_reg_usage.append(regs)
                    kernel_dsp_usage.append(dsps)
                    kernel_freq.append(freq)

        
        kernel_time_data.append(kernel_times)
        total_time_data.append(total_times)
        throughput_data.append(kernel_throughput)
        ram_usage_data.append(kernel_ram_usage)
        alm_usage_data.append(kernel_alm_usage)
        reg_usage_data.append(kernel_reg_usage)
        dsp_usage_data.append(kernel_dsp_usage)
        freq_data.append(kernel_freq)


    with open(RESULTS_FILE, 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)

        writer.writerow(["Kernel exec time (ms)"])
        writer.writerow(header)
        writer.writerows(kernel_time_data)

        writer.writerow([""])
        writer.writerow(["Throughput (points/ms)"])
        writer.writerow(header)
        writer.writerows(throughput_data)

        writer.writerow([""])
        writer.writerow([f"BRAMs (only kernel system, SYCL takes {BRAM_STATIC_PARTITION})"])
        writer.writerow(header)
        writer.writerows(ram_usage_data)

        writer.writerow([""])
        writer.writerow([f"ALMs (only kernel system, SYCL takes {ALMS_STATIC_PARTITION})"])
        writer.writerow(header)
        writer.writerows(alm_usage_data)

        writer.writerow([""])
        writer.writerow([f"REGs (only kernel system, SYCL takes {REGISTERS_STATIC_PARTITION})"])
        writer.writerow(header)
        writer.writerows(reg_usage_data)

        writer.writerow([""])
        writer.writerow([f"DSPs (only kernel system, SYCL takes {DSP_STATIC_PARTITION})"])
        writer.writerow(header)
        writer.writerows(dsp_usage_data)

        writer.writerow([""])
        writer.writerow(["Frequency (MHz)"])
        writer.writerow(header)
        writer.writerows(freq_data)

        writer.writerow([""])
        writer.writerow(["Total time (JIT + mem transfer) (ms)"])
        writer.writerow(header)
        writer.writerows(total_time_data)

        writer.writerow([""])
        writer.writerow([f'CPU: {CPU_DEVICE}'])
        writer.writerow([f'FPGA: {FPGA_DEVICE}'])
        writer.writerow([f'GPU: {GPU_DEVICE}'])
