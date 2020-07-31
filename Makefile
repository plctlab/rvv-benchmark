SYSROOT_DIR := /home/u/tools/riscv64/install/riscv64-unknown-elf
TOOLCHAIN_DIR := /home/u/tools/riscv64/install
CC_PREFIX := /home/u/rvv/llvm/rvv-llvm/build/bin/
SPIKE_DIR := /home/u/rvv/riscv-isa-sim/build/
PK_DIR := /home/u/rvv/riscv-pk/build/
objects = main.c memcpy.s sgemm.S strlen.s vvaddint32.s saxpy.s strcpy.s strncpy.s

target = rvv1

$(target) : $(objects)
	$(CC_PREFIX)clang  --target=riscv64-unknown-elf -march=rv64gcv --sysroot=$(SYSROO_DIR)  --gcc-toolchain=$(TOOLCHAIN_DIR) -o $(target) $(objects)

run :
	$(SPIKE_DIR)spike --isa=rv64gcv $(PK_DIR)pk $(target)

clean :
	rm -f $(target)
