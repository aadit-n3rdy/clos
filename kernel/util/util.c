#include <stdint.h>

void utoa(unsigned int a, char *str, int base) {
	int i;
	char tmp;
	if (!a) {
		str[0] = '0';
		str[1] = '\0';
		return;
	}
	for (i = 0; a; i++) {
		tmp = (a%base);
		str[i] = (tmp < 10) ? ('0' + tmp) : ('a' + tmp - 10);
		a /= base;
	}
	int len = i;
	str[len] = '\0';
	i = 0;
	for (i = 0; i < len/2; i++) {
		tmp = str[i];
		str[i] = str[len-i-1];
		str[len-i-1] = tmp;
	}
}

void timedelay_exp(int level) {
	if (level <= 0) {
		return;
	}
	for (int i = 0; i < 10; i++) {
		timedelay_exp(level-1);
	}
}
