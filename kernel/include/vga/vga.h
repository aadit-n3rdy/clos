#ifndef CLOS_VGA_H
#define CLOS_VGA_H

#define VGA_DEFAULT_COL 0x0f

#define VGA_DEFAULT_FG WHITE
#define VGA_DEFAULT_BG BLACK

enum  VGA_COLORS {
	BLACK			= 0,
	BLUE			= 1,
	GREEN			= 2,
	CYAN			= 3,
	RED				= 4,
	MAGENTA			= 5,
	BROWN			= 6,
	LIGHT_GRAY		= 7,
	DARK_GRAY		= 8,
	LIGHT_BLUE		= 9,
	LIGHT_GREEN		= 10,
	LIGHT_CYAN		= 11,
	LIGHT_RED		= 12,
	LIGHT_MAGENTA	= 13,
	LIGHT_YELLOW	= 14,
	WHITE			= 15
};

struct vga_char {
	unsigned char val;
	unsigned char col;
} __attribute__((packed));


void vga_putchar(unsigned char fg, unsigned char bg, char c);

void vga_puts(char *str);

void vga_put_uint(unsigned int d, int base);

#endif
