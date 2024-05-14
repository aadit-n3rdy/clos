#ifndef CLOS_UTIL_H
#define CLOS_UTIL_H

unsigned int get_msw();
// Get the machine status word

void utoa(unsigned int a, char *str, int base);

void ptrtooa(void *ptr, char *str);

void timedelay_exp(int level); 
// Wait for some amount of time, amount of time increases exponentially with exp. 
// Use maybe 6 or 7

void kern_exit();

void *memcpy(void *dest, void *src, unsigned int n);
// Pretty much just memcpy from the C standard library

#define ADDR_P2V(x) ((x) + 0xC0000000)
#define ADDR_V2P(x) ((x) - 0xC0000000)

#endif
