MBALIGN equ 1<<0
MBMEMINFO equ 1<<1
MAGIC equ 0x1BADB002
FLAGS equ MBALIGN | MBMEMINFO
CHECKSUM equ -(MAGIC + FLAGS)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 16
stack_top:
resb 16384
stack_bottom:

extern kernel_main

section .text
global _start
_start:
	mov esp, stack_bottom
	mov ebp, stack_bottom

	call kernel_main

_boot_hlt:
	cli
	hlt
	jmp _boot_hlt

global kern_exit
kern_exit:
	jmp _boot_hlt
