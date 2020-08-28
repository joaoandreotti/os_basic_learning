# list of files with matching pattern
C_SOURCES = $(wildcard kernel/*.c drivers/*.c)

# map a file.c to file.o
OBJ = $(C_SOURCES: .c=.o)


# $^ == all dependency files
# $< == first dependency file
# $@ == target file

all: os-image
	qemu-system-i386 -fda $< ; rm *.o *.bin os-image

os-image: boot/system_boot.bin kernel.bin
	cat $^ > $@

boot/system_boot.bin: boot/system_boot.asm
	nasm $< -f bin -o $@

kernel.bin: call_kernel.o kernel.o interrupt.o
	i686-elf-ld $^ -o $@ -Ttext 0x1000 --oformat binary

call_kernel.o: kernel/call_kernel.asm
	nasm $< -f elf -o $@

interrupt.o: cpu/interrupt.asm
	nasm $< -f elf -o $@

kernel.o: kernel/kernel.c
	i686-elf-gcc -ffreestanding -c $< -o $@  

clean:
	rm  *.o *.bin  os-image
