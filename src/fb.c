/*! \file fb.c
 *  \brief Contain the functions to communicate with the framebuffer
 *  \date 2020/06/03
 */

#include "io.h"
#include "fb.h"

void fb_move_cursor(int y, int x)
{
    unsigned short pos = y * 80 + x;
 
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, (unsigned char) (pos & 0xFF));
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (unsigned char) ((pos >> 8) & 0xFF));
}

void fb_move_cursor_simple(int pos)
{
	outb(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, (unsigned char) (pos & 0xFF));
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    outb(FB_DATA_PORT, (unsigned char) ((pos >> 8) & 0xFF));
}

void fb_write_text(char *text, int len, int line, int offset, unsigned char fg_color, unsigned char bg_color, int blink)
{
    for(int i = 0; i < len; i++)
    {   
        char *fb = (char *) 0x000B8000 + (i * 0x2) + offset + (line * 0xA0);
        fb[0] = (char) text[i];
        fb[1] = ((bg_color & 0x0F) << 4) + (fg_color & 0x0F) + (blink * 128);
    }
}

void fb_clear_screen()
{
    for(int i = 0; i < 1999; i++)
    {
        char *fb = (char *) 0x000B8000 + (i * 0x2);
        fb[0] = 0x00;
        fb[1] = 0x07;
    }
}

void fb_disable_blink()
{
   inb(0x03DA);
   outb(0x03C0, 0x30);
   outb(0x03C0, inb(0x03C1) & 0xF7);
}

void fb_enable_blink()
{
   inb(0x03DA);
   outb(0x03C0, 0x30);
   outb(0x03C0, inb(0x03C1) | 0x08);
}

void fb_enable_cursor(unsigned char cursor_start, unsigned char cursor_end)
{
    outb(0x3D4, 0x0B);
    outb(0x3D5, cursor_start);

    outb(0x3D4, 0x0A);
    outb(0x3D5, cursor_end);
}

void fb_disable_cursor()
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

unsigned short int fb_get_cursor_position()
{
    unsigned short int pos = 0;

    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((unsigned short int)inb(0x3D5)) << 8;

    return pos;
}

void fb_write(char *buf, unsigned int len)
{
    unsigned short pos = fb_get_cursor_position();

    if((pos + len) > 1999)
    {
        fb_clear_screen();
        fb_move_cursor_simple(0);
        pos = 0;
    }

    for(unsigned int i = 0; i < len; i++)
    {   
        char *fb = (char *) 0x000B8000 + (pos * 2) + (i * 0x2);
        fb[0] = (char) buf[i];
        fb[1] = 0x07;
    }

    // move the cursor right after the text
    fb_move_cursor_simple(pos + len);
}

void fb_line_return()
{
    unsigned short int pos = fb_get_cursor_position();
    if((pos + 80) > 1999)
    {
        fb_clear_screen();
        fb_move_cursor_simple(0);
        pos = 0;
    }
    else
    {
        fb_move_cursor_simple(pos + (80 - (pos % 80)));
    }
}

