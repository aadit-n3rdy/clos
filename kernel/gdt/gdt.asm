
section .bss
_GDT_BEGIN:
resb 96
_GDT_END:

section .data
gdtr dw 0
dd 0 

global SEGDESC_KERNEL_DATA
global SEGDESC_KERNEL_CODE
global SEGDESC_USER_DATA
global SEGDESC_USER_CODE
SEGDESC_KERNEL_DATA dw 08h
SEGDESC_KERNEL_CODE dw 10h
SEGDESC_USER_DATA   dw 18h
SEGDESC_USER_CODE   dw 20h

section .text

extern gdt_fill
global gdt_init
gdt_init:
	push ebp
	mov ebp, esp

	push _GDT_END
	push _GDT_BEGIN
	call gdt_fill
	add esp, 8
	cmp eax, 0

	je _gdt_fill_success
	ret

	_gdt_fill_success:
	cli
	mov ax, _GDT_END - _GDT_BEGIN - 1
	mov [gdtr], ax
	mov dword [gdtr+2], _GDT_BEGIN

	xor eax, eax
	
	lgdt [gdtr]

	jmp 10h:flush_gdt
	flush_ret:

	pop ebp
	mov eax, 0
	ret

flush_gdt:
	mov ax, [SEGDESC_KERNEL_DATA]
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp flush_ret

