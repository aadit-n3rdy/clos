
#include "vga/vga.h"
#include "util.h"

#define COLS 80
#define ROWS 25

struct vga_char* const VGA_BUF = (void*)0xB8000;
int cursor = 0;

static void inc_cursor();
static void vga_newline();
static void scroll();

static void vga_newline() {
	if (!(cursor%COLS)) {
		VGA_BUF[cursor].val = ' ';
		inc_cursor();
	}
	while (cursor%COLS) {
		VGA_BUF[cursor].val = ' ';
		inc_cursor();
	}
}

static void scroll() {
	for (int i = 0; i < ROWS-1; i++) {
		for (int j = 0; j < COLS; j++) {
			VGA_BUF[COLS * i + j] = VGA_BUF[COLS * (i+1) + j];
		}
	}
	for (int j = 0; j < COLS; j++) {
		VGA_BUF[COLS * (ROWS - 1) + j].val = ' ';
	}
}

static void inc_cursor() {
	cursor++;
	if (cursor >= COLS * ROWS) {
		scroll();
		cursor = COLS * (ROWS-1);
	}
}

void vga_putchar(unsigned char fg, unsigned char bg, char c) {
	switch(c) {
		case '\n':
			vga_newline();
			break;
		default:
			VGA_BUF[cursor].col = (bg<<4) | fg;
			VGA_BUF[cursor].val = c;
			inc_cursor();
			break;
	}
}

void vga_puts(char *str) {
	char *start = str;
	while (*str != '\0') {
		vga_putchar(VGA_DEFAULT_FG, VGA_DEFAULT_BG, *str);
		str++;
	}
}

void vga_put_uint(unsigned int d, int base) {
	char buf[32];
	utoa(d, buf, base);
	vga_puts(buf);
}
