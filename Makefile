##################################################################
# To run the make, you should have the following tools available:
#
#   * rvv clang/llvm (https://github.com/isrc-cas/rvv-llvm)
#   * riscv gcc elf toolchain (https://github.com/riscv/riscv-gnu-toolchain)
#   * spike (https://github.com/riscv/riscv-isa-sim)
#   * pk (https://github.com/riscv/riscv-pk)
#
##################################################################

# Change the path for your environment.

GCC_TOOLCHAIN_DIR := /path/to/gcc/elf/toolchain/install
SYSROOT_DIR := $(GCC_TOOLCHAIN_DIR)/riscv64-unknown-elf

CLANG := clang
SPIKE := spike
PK := pk

objects = main.c memcpy.s sgemm.S strlen.s vvaddint32.s saxpy.s strcpy.s strncpy.s

target = rvv-test

$(target) : $(objects)
	$(CLANG)  --target=riscv64-unknown-elf -menable-experimental-extensions -march=rv64gcv1p0 --sysroot=$(SYSROOT_DIR) --gcc-toolchain=$(GCC_TOOLCHAIN_DIR) -o $(target) $(objects)

run :
	$(SPIKE) --isa=rv64gcv $(PK) $(target)

clean :
	rm -f $(target)
