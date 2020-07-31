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
    
    
## (3) Running Tests

**make and run the test：**

```
$ cd rvv-llvm
$ mkdir build
$ cd build
$ cmake -DLLVM_TARGETS_TO_BUILD="RISCV" -DLLVM_ENABLE_PROJECTS=clang  -G "Unix Makefiles" ../llvm
$ make

$ clang --target=riscv64-unknown-elf -march=rv64gcv main.c memcpy.s strlen.s strncpy.s vvaddint32.s saxpy.s strcpy.s sgemm.S --sysroot=/home/u/tools/riscv64/install/riscv64-unknown-elf  --gcc-toolchain=/home/u/tools/riscv64/install -o elf  

$ spike --isa=rv64gcv pk elf
```  
&ensp; &ensp;&ensp;where the option of sysroot and gcc-toolchain will help you find the location of header files and libraries. The executing commands of clang and spike have added into Makefile, where you can input "make" to run our test, make sure your installing location of riscv-gnu-toolchain correct before inputing "make" command, or you can modify the right path of riscv-gnu-toolchain in your local computer.  

**view riscv executable file in assembly form：**

```  
 $ riscv64-unknown-elf-objdump -d elf>& elf.dump
```


