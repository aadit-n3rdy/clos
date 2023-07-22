
#include "io.h"
#include "idt/pic.h"

int pic_init() {
	unsigned char mask1, mask2;

	mask1 = io_inb(PIC_MD);
	mask2 = io_inb(PIC_SD);

	io_outb(PIC_MC, 0x11);
	io_outb(PIC_SC, 0x11);

	io_outb(PIC_MD, 0x20);
	io_outb(PIC_SD, 0x28);

	io_outb(PIC_MD, 1<<2); // Tell master that slave is at IRQ 2
	io_outb(PIC_SD, 2);    // Tell slave it is connected to IRQ 2 of master
	
	io_outb(PIC_MD, 0x01); // Enable 8086 mode
	io_outb(PIC_SD, 0x01);

	io_outb(PIC_MD, mask1);
	io_outb(PIC_SD, mask2);

	return 0;
}

unsigned short pic_getmask() {
	unsigned char master, slave;
	master = io_inb(PIC_MD);
	slave = io_inb(PIC_SD);
	return ((unsigned short)slave << 8) | ((unsigned short)master);
}

void pic_setmask(unsigned short mask) {
	io_outb(PIC_MD, mask & 0xff);
	io_outb(PIC_SD, (mask & 0xff00) >> 8);
}
