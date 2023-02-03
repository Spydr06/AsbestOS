#ifndef KERNEL_IO_H
#define KERNEL_IO_H

// framebuffer colors
#define FB_GREEN 2
#define FB_BLACK 0

void outb(unsigned short port, unsigned char data);
void fb_write_cell(unsigned int i, char c, unsigned char fg, unsigned char bg);
void fb_move_cursor(unsigned short pos);

#endif /* KERNEL_IO_H */
