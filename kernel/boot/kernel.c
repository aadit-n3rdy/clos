#include "vga/vga.h"
#include "util.h"
#include "gdt/gdt.h"
#include "idt/idt.h"
#include "io.h"
#include "idt/pic.h"

#include <stdint.h>

#include "config.h"

#define TEST_SIZE(TYPE, VAL) vga_puts(#TYPE); \
	if (sizeof(TYPE) == VAL) { \
		vga_puts(": Valid\n"); \
	} else { \
		vga_puts(": Invalid\n"); \
	}

extern int _kernel_end;
extern int _kernel_start;

void *kernel_end = &_kernel_end;
void *kernel_start = &_kernel_start;

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
	
	TEST_SIZE(uint32_t, 4);
	TEST_SIZE(int32_t, 4);
	TEST_SIZE(uint16_t, 2);
	TEST_SIZE(int16_t, 2);
	TEST_SIZE(uint8_t, 1);
	TEST_SIZE(int8_t, 1);
	TEST_SIZE(size_t, sizeof(void*));

	vga_puts("Some shit\n");
	timedelay_exp(3);
	vga_puts("Hopefully VGA is without bugs?\n");

	vga_puts("Space occupied by kernel: 0x");
	vga_put_uint(kernel_end - kernel_start - 0xC0000000, 16);

	while(1) {
	}

	vga_puts("Exiting kernel\n");
}
