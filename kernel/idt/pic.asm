

section .data
kb_msg: db "Keyboard interrupt, scancode: 0x", 0
newline: db 10, 0
KEY_TABLE: times 256 db 0

extern vga_puts
extern vga_put_uint

section .text

global pic_isr_kb
pic_isr_kb:
	cli
	push ebp
	mov ebp, esp
	push ebx

	push kb_msg
	call vga_puts
	add esp, 4

	xor eax, eax
	in al, 0x60

	push 16
	push eax
	call vga_put_uint
	add esp, 8

	push newline
	call vga_puts
	add esp, 4

	mov al, 0x20
	out 0x20, al ; Send EOI

	pop ebx
	pop ebp
	sti
	iret
