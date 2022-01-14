import csv
import os
import re

REPEAT = 5

RESULTS_FILE = 'results_velfg.csv'

BIN_PATH = './bin/'
KERNEL_PREFIX = 'velfg'
KERNEL_TYPES = ['swi', 'swi_reduced', 'ndrange', 'ndrange_reduced', 'pipes']
SIZES = ['10x10', '100x100', '200x200', '300x300']




if __name__ == "__main__":
    header = ['kernel'] + SIZES
    time_data = []
    ram_usage_data = []

    for kernel_type in KERNEL_TYPES:
        kernel_times = [kernel_type]
        kernel_ram_usage = [kernel_type]

        for size in SIZES:
            binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga_emu'
            report = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{size}.fpga.prj/acl_quartus_report.txt'
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
                        print('Something went wrong with getting time from ' + binary + ". Skipping..")
                        break

                kernel_times.append(time)
            

            if not os.path.isfile(report):
                print(report + " doesn't exist. Skipping resource usage..")
                kernel_ram_usage.append('N/A')
            else:
                with open(report, 'r') as report_f:
                    report_str = report_f.read()

                ram_usage_str = re.findall("RAM blocks: (.*?)/", report_str)

                rams = 0
                try:
                    rams = re.sub("[^0-9]", "", ram_usage_str[0])
                except:
                    print('Something went wrong with ram usage from ' + report + ". Skipping..")

                kernel_ram_usage.append(rams)
                print(rams)
        
        time_data.append(kernel_times)
        ram_usage_data.append(kernel_ram_usage)


    with open(RESULTS_FILE, 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)

        writer.writerow(["Time"])
        writer.writerow(header)
        writer.writerows(time_data)

        writer.writerow([""])
        writer.writerow(["RAM (out of 2700)"])
        writer.writerow(header)
        writer.writerows(ram_usage_data)
