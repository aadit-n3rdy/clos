#include "stdint.h"

void *memcpy(void *dest, void *src, size_t n) {
	if ((size_t)dest%4 == 0 && (size_t)src%4 == 0) {
		uint32_t *d, *s;
		d = (uint32_t*)dest;
		s = (uint32_t*)src;
		n = n>>2;
		for (size_t i = 0; i < n; i++) {
			d[i] = s[i];
		}
	}
	else {
		uint8_t *d, *s;
		d = (uint8_t*)dest;
		s = (uint8_t*)src;
		for (size_t i = 0; i < n; i++) {
			d[i] = s[i];
		}
	}
}

