export

CC:=i686-elf-gcc
AS:=nasm -felf32
AR:=i686-elf-ar

CFLAGS:=-g -Wall -ffreestanding -Wextra -std=c99

ifeq ($(SRCDIR),)
SRCDIR:=$(PWD)
endif

OUT_ELF := out/clos.elf

.PHONY: qemu qemu_kernel multiboot clean init

init:
	@$(MAKE) -C kernel init

out/clos.iso: $(OUT_ELF) multiboot
	cp $(OUT_ELF) isodir/boot/
	grub-mkrescue -o out/clos.iso isodir

qemu: multiboot out/clos.iso $(OUT_ELF)
	qemu-system-i386 -enable-kvm -no-reboot -cdrom out/clos.iso

qemu_kernel: multiboot out/clos.elf $(OUT_ELF)
	qemu-system-i386 -enable-kvm -no-reboot -kernel out/clos.elf

bochs: out/clos.iso
	bochs -q -f bochsrc

multiboot: out/clos.elf
	@./check_multiboot

$(OUT_ELF): kernel
	$(CC) -g -T linker.ld -o $@ -ffreestanding -O2 -nostdlib kernel/libkernel.a -lgcc

clean:
	- rm -f out/*
	@$(MAKE) -C kernel clean

.PHONY: kernel
kernel:
	@$(MAKE) -C kernel kernel
