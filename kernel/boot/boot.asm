MBALIGN equ 1<<0
MBMEMINFO equ 1<<1
MAGIC equ 0x1BADB002
FLAGS equ MBALIGN | MBMEMINFO
CHECKSUM equ -(MAGIC + FLAGS)

KERNEL_BASE_OFFSET equ 0xC0000000

%define ADDR_V2P(x) (x - 0xC0000000)
%define ADDR_P2V(x) (x + 0xC0000000)

section .multiboot
align 4
	dd MAGIC
	dd FLAGS
	dd CHECKSUM

section .bss
align 4096
stack_top:
resb 4*4096
stack_bottom:

;section .prekernel_data

section .bss
align 4096
_boot_pagedir:
resb 4096
_boot_pagedir_end:
_boot_pagetab1:
resb 4096
_boot_pagetab1_end:

extern kernel_main
extern _kernel_start
extern _kernel_end

section .prekernel.text
global _start
_start:
	xchg bx, bx

	; edx: addr of current pagetab entry
	; ebx: value of current pagetab entry
	; eax: offset of current pagetab entry, is edx - _boot_pagetab1 
	mov edx, ADDR_V2P(_boot_pagetab1)
	mov ebx, 0

l1:
	cmp ebx, _kernel_start
	jg _boot_hlt
	je l1_exit
	; Map pre kernel area as well, lets see what happens
	mov dword [edx], ebx
	or dword [edx], 3
	add edx, 4
	add ebx, 4096
	jmp l1
l1_exit:
	xchg bx, bx

l2:
	cmp ebx, ADDR_V2P(_kernel_end)
	jge l2_exit
	mov [edx], ebx
	or dword [edx], 3
	add edx, 4
	add ebx, 4096
	jmp l2
l2_exit:
	mov [edx], ebx
	or dword [edx], 3

	mov dword  [ADDR_V2P(_boot_pagedir)], ADDR_V2P(_boot_pagetab1) + 3
	mov dword [ADDR_V2P(_boot_pagedir) + 0xC00], ADDR_V2P(_boot_pagetab1) + 3 

	xchg bx, bx

	mov eax, ADDR_V2P(_boot_pagedir)
	mov cr3, eax

	; Ensure PAE is disabled
	mov eax, cr4
	and eax, ~(1<<5)
	mov cr4, eax

	; Set paging bit in CR0
	mov eax, cr0
	or eax, 1<<31
	mov cr0, eax

	mov esp, stack_top
	mov ebp, stack_top

	call kernel_main

_boot_hlt:
	cli
	hlt
	jmp _boot_hlt

global kern_exit
kern_exit:
	jmp _boot_hlt
