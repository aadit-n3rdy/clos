
section .text

global io_inb
io_inb:
	xor eax, eax
	mov dx, [esp+4]
	in al, dx
	ret

global io_outb
io_outb:
	mov dx, [esp+4]
	mov al, [esp+8]
	out dx, al
	ret

