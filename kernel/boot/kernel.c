
#include "vga/vga.h"
#include "util.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "io.h"
#include "idt/pic.h"

#include "config.h"

void kernel_main() {
	vga_puts("Hello World!!\n01234\n");

	if (get_msw() & 1) {
		vga_puts("PROTECTED MODE\n");
	} else {
		vga_puts("STILL IN REAL MODE, exiting...\n");
		return;
	}

	gdt_init();

	vga_puts("huh, inited gdt?\n");

	vga_puts("Kernel code desc: 0x");
	vga_put_uint(SEGDESC_KERNEL_CODE, 16);
	vga_puts("\n");

	vga_puts("Kernel data desc: 0x");
	vga_put_uint(SEGDESC_KERNEL_DATA, 16);
	vga_puts("\n\n");

	idt_init();

	vga_puts("\nhuh, inited idt?\n");

#ifdef TEST_INT
	vga_puts("Testing interrupts, will exit after this. Should trigger int 0x08 \
with err code 0x10\n");
	__asm__ ("pushl $0x10; int $0x08");
	vga_puts("Ok lets hope that worked\n\n");
#endif

#ifdef TEST_HIGHINT
	vga_puts("Testing interrupt beyond 32, should continue after this\n");
	__asm__ volatile ("int $0x30");
	vga_puts("Ok lets hope that worked\n\n");
#endif

	pic_init();

	vga_puts("Done initing PIC\n");
	vga_puts("Enabling interrupts\n");
	__asm__ volatile("sti");

	pic_setmask(0xffff ^ (1<<1));

	while(1) {
	}

	vga_puts("Exiting kernel\n");
}
