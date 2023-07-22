#ifndef CLOS_GDT_H
#define CLOS_GDT_H

struct gdt_entry {
	void *base;
	void *limit;
	unsigned char flags;
	unsigned char access;
};

extern unsigned short int SEGDESC_KERNEL_DATA;
extern unsigned short int SEGDESC_KERNEL_CODE;
extern unsigned short int SEGDESC_USER_DATA;
extern unsigned short int SEGDESC_USER_CODE;

int gdt_encode_entry(unsigned char *res, struct gdt_entry e);

int gdt_init();

#endif
