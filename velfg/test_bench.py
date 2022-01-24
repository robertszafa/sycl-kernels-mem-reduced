import csv
import os
import re

REPEAT = 5

RESULTS_FILE = 'results_velfg.csv'

BIN_PATH = './bin/'
KERNEL_PREFIX = 'velfg'
KERNEL_TYPES = [
    'swi', 
    'swi_reduced', 
    'ndrange', 
    'ndrange_reduced', 
    'pipes'
    ]
SIZES = [
    '10x10', 
    '100x100', 
    '200x200', 
    '300x300',
    '900x900',
    '1900x1900',
    ]

# Found in report.htlm under area. The numbers seems to be stable, inrespective of kernel source.
BRAM_STATIC_PARTITION = 492

KP_DIM = 90


if __name__ == "__main__":
    header = ['kernel'] + SIZES
    time_data = []
    time_norm_data = []
    ram_usage_data = []
    freq_data = []

    for kernel_type in KERNEL_TYPES:
        kernel_times = [kernel_type]
        kernel_times_norm = [kernel_type]
        kernel_ram_usage = [kernel_type]
        kernel_freq = [kernel_type]

        for size in SIZES:
            binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga'
            report = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga.prj/acl_quartus_report.txt'
            domain_size = int(size.split('x')[0]) * int(size.split('x')[1]) * KP_DIM
            print(f'\n--- {binary} ---')
            
            if not os.path.isfile(binary):
                print(binary + " doesn't exist. Skipping time test..")
                kernel_times.append('N/A')
            else:
                time = float("inf")
                for _ in range(REPEAT):
                    out = os.popen(binary).read()
                    time_str = re.findall("\d+\.\d+", out)
                    try:
                        time = float(time_str[0]) if float(time_str[0]) < time else time
                    except:
                        print(f'{binary} output\n: {out}')

                kernel_times.append(time)
                kernel_times_norm.append(time / domain_size)
            

            if not os.path.isfile(report):
                print(report + " doesn't exist. Skipping resource usage..")
                kernel_ram_usage.append('N/A')
            else:
                with open(report, 'r') as report_f:
                    report_str = report_f.read()

                ram_usage_str = re.findall("RAM blocks: (.*?)/", report_str)
                freq_str = re.findall("Actual clock freq: (\d+)", report_str)

                rams = 0
                freq = 0
                try:
                    rams = int(re.sub("[^0-9]", "", ram_usage_str[0])) - BRAM_STATIC_PARTITION
                except:
                    print('Something went wrong with  getting ram usage from ' + report + ". Skipping..")
                try:
                    freq = freq_str[0]
                except:
                    print('Something went wrong with getting freq from ' + report + ". Skipping..")

                kernel_ram_usage.append(rams)
                kernel_freq.append(freq)
        
        time_data.append(kernel_times)
        time_norm_data.append(kernel_times_norm)
        ram_usage_data.append(kernel_ram_usage)
        freq_data.append(kernel_freq)


    with open(RESULTS_FILE, 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)

        writer.writerow(["Time (ms)"])
        writer.writerow(header)
        writer.writerows(time_data)

        writer.writerow([""])
        writer.writerow(["BRAMs (only kernel system)"])
        writer.writerow(header)
        writer.writerows(ram_usage_data)

        writer.writerow([""])
        writer.writerow(["Frequency (MHz)"])
        writer.writerow(header)
        writer.writerows(freq_data)

        writer.writerow([""])
        writer.writerow(["Time per domain item (ms)"])
        writer.writerow(header)
        writer.writerows(time_norm_data)
