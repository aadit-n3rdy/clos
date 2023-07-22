
section .bss
_IDT_BEGIN:
resb 2048
_IDT_END:

section .data
_IDTR:
dw 0
dd 0
debug_msg db 'Max IDT entries: ', 0
exit_msg db 'Exiting idt_init', 10, 0
newline db 10, 0

extern SEGDESC_KERNEL_CODE
extern idt_fill
extern vga_puts
extern vga_put_uint
extern ISR_TABLE
extern pic_isr_kb

section .text

global idt_init
idt_init:
	push ebp
	mov ebp, esp

	push debug_msg
	call vga_puts
	add esp, 4

	mov eax, _IDT_END
	sub eax, _IDT_BEGIN

	xor edx, edx
	mov ecx, 8
	div ecx

	push dword 10
	push eax
	call vga_put_uint
	add esp, 8

	push newline
	call vga_puts
	add esp, 4

	push eax
	push edx
	push ecx

	mov dword [ISR_TABLE+33*4], pic_isr_kb

	push ISR_TABLE
	push _IDT_BEGIN
	call idt_fill
	add esp, 8

	pop ecx
	pop edx
	pop eax

	mov word [_IDTR], _IDT_END - _IDT_BEGIN - 1
	mov dword [_IDTR + 2], _IDT_BEGIN
	lidt [_IDTR]

	pop ebp
	ret
