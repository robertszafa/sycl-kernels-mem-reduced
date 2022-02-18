import csv
import os
import re
from subprocess import Popen, PIPE, STDOUT
from time import sleep, time

POWER_MEASUREMENT_RESOLUTION_SECS = 0.1

RESULTS_FILE = 'power_results_velfg.csv'

BIN_PATH = './bin/'
KERNEL_PREFIX = 'velfg_power'
KERNEL_TYPES = [
    'ndrange',
    'ndrange_reduced',
    'swi',
    'swi_reduced_1cu',
    ]
SIZE = '900x900'

FPGA_POWER_CMD = 'fpgainfo power'


def get_fpga_watts_now():
    out = os.popen(FPGA_POWER_CMD).read()
    watts_reg = re.findall(r"Total Input Power\s*:\s*([\d\.]+) Watts", out)
    return float(watts_reg[0])


if __name__ == "__main__":
    header = ['kernel', 'Runtime s', 'Average W', 'Total J']
    power_data = []

    for kernel_type in KERNEL_TYPES:
        binary = f'{BIN_PATH}{KERNEL_PREFIX}_{kernel_type}_{SIZE}.fpga'
        this_kernel_power = [kernel_type]

        if not os.path.isfile(binary):
            print(binary + " doesn't exist. Skipping..")
            this_kernel_power.append('N/A')
            continue

        print(f'Running {binary} ...')
        p_bin = Popen([binary], shell=True, stdin=PIPE, stdout=PIPE, stderr=STDOUT, close_fds=True) #, capture_output=True, text=True)

        times_measured = 0
        watts_total = 0
        start = time()
        while p_bin.poll() is None:
            watts_total += get_fpga_watts_now()
            times_measured += 1
            sleep(POWER_MEASUREMENT_RESOLUTION_SECS)
        end = time()

        kernel_time_sec = end - start
        avg_watts = watts_total / times_measured
        kernel_joules = int(avg_watts * kernel_time_sec)
        
        this_kernel_power.append(kernel_time_sec)
        this_kernel_power.append(avg_watts)
        this_kernel_power.append(kernel_joules)
        power_data.append(this_kernel_power)

        print(f'Ran for {int(kernel_time_sec)} s')
        print(f'Average Watts: {avg_watts} W')
        print(f'Total energy: {kernel_joules} J\n')


    with open(RESULTS_FILE, 'w', encoding='UTF8', newline='') as f:
        writer = csv.writer(f)

        writer.writerow(header)
        writer.writerows(power_data)
