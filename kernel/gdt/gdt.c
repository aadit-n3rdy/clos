
#include "gdt/gdt.h"
#include "vga/vga.h"
#include "util.h"

int gdt_encode_entry(unsigned char *res, struct gdt_entry e)  {
	res[7] = ((unsigned long int)e.base >> 24) & 0xff;
	res[6] = ((e.flags & 15) << 4) | (((unsigned long int)e.limit >> 16) & 15);
	res[5] = e.access;
	res[4] = ((unsigned long int)e.base >> 16) & 0xff;
	res[3] = ((unsigned long int)e.base >> 8) & 0xff;
	res[2] = (unsigned long int)e.base & 0xff;
	res[1] = ((unsigned long int)e.limit >> 8) & 0xff;
	res[0] = (unsigned long int)e.limit & 0xff;
	return 0;
}

int gdt_fill(void* gdt_begin, void *gdt_end) {
	vga_puts("Filling gdt\n");
	vga_puts("\n");
	struct gdt_entry gdt_entries[] = {
		{0, 0, 0, 0},
		// kernel data
		{0, (void*)0xfffff, 12, 0x92},

		// kernel code
		{0, (void*)0xfffff, 12, 0x9A},

		// user data
		{0, (void*)0xfffff, 12, 0xF2},

		// user code
		{0, (void*)0xfffff, 12, 0xFA},
		
		// task 
		// TODO: Set VALID TSS
		{0, 0, 0, 0}
	};
	int gdt_count = sizeof(gdt_entries)/sizeof(gdt_entries[0]);
	int gdt_total = (gdt_end - gdt_begin)>>3;

	vga_puts("GDT max. no. of entries: ");
	vga_put_uint(gdt_total, 10);
	vga_puts("\n");

	int i;
	for (i = 0; i < gdt_count; i++) {
		gdt_encode_entry(gdt_begin + (i << 3), gdt_entries[i]);
	}
	vga_puts("Encoded entries\n");
	for (; i < (gdt_total); i++) {
		// use NULL entry for all others
		gdt_encode_entry(gdt_begin + (i << 3), gdt_entries[0]);
	}

	vga_puts("Returning from gdt_fill\n");

	return 0;
}
