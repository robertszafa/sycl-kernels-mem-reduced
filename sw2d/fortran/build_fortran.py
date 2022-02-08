import os


SIZES = [
    '1000x1000', 
    '5000x5000', 
    '10000x10000', 
    '12500x12500', 
    '15000x15000', 
    ]

FLFLAGS = ['-Ofast','-flto', '-Wall','-cpp','-m64','-ffree-form','-ffree-line-length-0',
           '-fconvert=little-endian','-frecord-marker=4', '-mcmodel=medium', '-fopenmp -g']

# For the serial version I'm still using omp timers but just omit the paralled do loop pragma.
# The below flag adds the parallel loop pragma.
OMPFLAGS = [ '-DWITH_OPENMP']

FC='gfortran'


if __name__ == "__main__":
    for size in SIZES:
        nx = int(size.split('x')[0]) 
        ny = int(size.split('x')[1])
        
        flflags_string = ' '.join(FLFLAGS)
        build_command = f'{FC} {flflags_string} -DNX={nx} -DNY={ny} *.f95 -o ../bin/sw2d_fortran_{nx}x{ny}.exe'
        out = os.popen(build_command).read()
        if out:
            print(f'\n\t** Error **\n{out}')

        flflags_string_omp = ' '.join(FLFLAGS + OMPFLAGS)
        build_command_omp = f'{FC} {flflags_string_omp} -DNX={nx} -DNY={ny} *.f95 -o ../bin/sw2d_fortran_omp_{nx}x{ny}.exe'
        out_omp = os.popen(build_command_omp).read()
        if out_omp:
            print(f'\n\t** Error omp **\n{out_omp}')

        