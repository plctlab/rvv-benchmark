objects = main.c memcpy.s sgemm.S strlen.s vvaddint32.s saxpy.s strcpy.s strncpy.s

target = rvv1

$(target) : $(objects)
	clang  --target=riscv64-unknown-elf -march=rv64gv --sysroot=/home/u/tools/riscv64/install/riscv64-unknown-elf  --gcc-toolchain=/home/u/tools/riscv64/install -o rvv1 $(objects)	
	spike --isa=rv64gv pk $(target)

clean :
	rm -f $(objects) $(target)
