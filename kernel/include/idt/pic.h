
#ifndef CLOS_PIC_H
#define CLOS_PIC_H

#define PIC_MC 0x0020
#define PIC_MD 0x0021

#define PIC_SC 0x00A0
#define PIC_SD 0x00A1

int pic_init();
void pic_setmask(unsigned short mask);
unsigned short pic_getmask();

#endif
