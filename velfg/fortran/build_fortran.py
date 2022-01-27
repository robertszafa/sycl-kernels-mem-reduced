import os


SIZES = [
    '10x10', 
    '100x100', 
    '200x200', 
    '300x300',
    '600x600',
    '900x900',
    '1900x1900',
    ]

FLFLAGS = ['-Ofast','-flto', '-Wall','-cpp','-m64','-ffree-form','-ffree-line-length-0',
           '-fconvert=little-endian','-frecord-marker=4', '-mcmodel=medium', '-fopenmp']

# For the serial version I'm still using omp timers but just omit the paralled do loop pragma.
# The below flag adds the parallel loop pragma.
OMPFLAGS = [ '-DWITH_OPENMP']

FC='gfortran'


if __name__ == "__main__":
    for size in SIZES:
        ip = int(size.split('x')[0]) 
        jp = int(size.split('x')[1])
        
        flflags_string = ' '.join(FLFLAGS)
        build_command = f'{FC} {flflags_string} -DIP={ip} -DJP={jp} *.f95 -o ../bin/velfg_fortran_{ip}x{jp}.exe'
        out = os.popen(build_command).read()
        if out:
            print(f'\n\t** Error **\n{out}')

        flflags_string_omp = ' '.join(FLFLAGS + OMPFLAGS)
        build_command_omp = f'{FC} {flflags_string_omp} -DIP={ip} -DJP={jp} *.f95 -o ../bin/velfg_fortran_omp_{ip}x{jp}.exe'
        out_omp = os.popen(build_command_omp).read()
        if out_omp:
            print(f'\n\t** Error omp **\n{out_omp}')

        