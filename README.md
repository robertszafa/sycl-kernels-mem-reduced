Evaluation of a memory reduction compiler pass for stencil codes from [here](https://github.com/wimvanderbauwhede/RefactorF4Acc/tree/devel/TyTraCLTransformations/MemoryReduction).

We are using Inel's SYCL implementation dpc++ to target FPGAs on inteldevcloud, but the kernel code also runs on CPU (GPU can also be easily added by adding the SYCL appropriate device selector).
