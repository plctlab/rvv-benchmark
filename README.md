# rvv-benchmark  
&ensp; &ensp;&ensp; This respository is to test the rvv-benchmark, the vector assembly code examples come from riscv/riscv-v-spec/example whose github linking is https://github.com/riscv/riscv-v-spec.
main.c here calls the function implemented in the assembly file, you can use Makefile with rvv-llvm to compile and link C files and assembly files，
and then run the executable file on the spike simulator.

## (1) Vector Assembly Code Example Supported

**Vector Assembly Code Example**  

| Assembly  | Descriptiion                             | Status                    |
| --------- | ---------------------------------------- | ----------------------- |
| memcpy.s  | memory copy example                      | :ballot_box_with_check: |
| strlen.   | return string length example             | :ballot_box_with_check: |
| strcpy.   | copy string example                      | :ballot_box_with_check: |
| strncpy.s | copy fixed string of size n              | :ballot_box_with_check: |
| saxpy.s   | y[i] = a * x[i] + y[i]                   | :ballot_box_with_check: |
| sgemm.S   | c[m][n] += a[m][k]*b[k][n]               | :ballot_box_with_check: |
| vvaddint32.s | vector-vector add example             | :ballot_box_with_check: |


## (2) Specification About sgemm.S Example

&ensp; &ensp;&ensp;sgemm.S example is incomplete in several ways. One of which is the logic for saving and restoring the callee-saved registers (s0, s1, etc.). In particular, as you've noticed, the example expects the programmer to determine the correct values of FRAMESIZE and OFFSET (actually, you'd need three different OFFSETs...). To learn about the correct choices, you should study the (System V) RISC-V psABI, where the lingking is https://github.com/riscv/riscv-elf-psabi-doc/blob/master/riscv-elf.md
    
    
## (3) Run Tests

To run the test, you should have the following tools available:

  * rvv clang/llvm (https://github.com/isrc-cas/rvv-llvm)
  * riscv gcc elf toolchain (https://github.com/riscv/riscv-gnu-toolchain)
  * spike (https://github.com/riscv/riscv-isa-sim)
  * pk (https://github.com/riscv/riscv-pk)

**Modify Makefile：**

Change the path for your environment. For an example,

```
GCC_TOOLCHAIN_DIR := $(HOME)/install/riscv-elf
SYSROOT_DIR := $(GCC_TOOLCHAIN_DIR)/riscv64-unknown-elf
```

&ensp;&ensp;&ensp; These are used to find the location of gnu linker, header files and libraries. The executing commands of clang and spike have added into Makefile, where you can input "make" to run our test, make sure your installing location of riscv-gnu-toolchain correct before inputing "make" command, or you can modify the right path of riscv-gnu-toolchain in your local computer.

**Build and run the test：**

```
$ make
$ make run
```  

**View riscv executable file in assembly form：**

```  
 $ riscv64-unknown-elf-objdump -d elf>& elf.dump
```


