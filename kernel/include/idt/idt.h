#ifndef CLOS_IDT_H
#define CLOS_IDT_H

struct idt_desc {
	unsigned short int isr_low;
	unsigned short int segsel;
	unsigned char reserved;
	unsigned char flags;
	unsigned short int isr_high;
} __attribute__((__packed__));

void idt_init();

#endif
