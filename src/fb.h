/*! \file fb.h
 *  \brief Contain the definition of fb.c functions
 *  \date 2020/06/03
 */

#ifndef INCLUDE_FB_H
#define INCLUDE_FB_H

#include "io.h"

#define my_sizeof(type) ((char *)(&type+1)-(char*)(&type))

// \brief the I/O ports
#define FB_COMMAND_PORT 0x3D4
#define FB_DATA_PORT 0x3D5

// \brief the I/O ports commands
#define FB_HIGH_BYTE_COMMAND 14
#define FB_LOW_BYTE_COMMAND 15

/*! \brief Moves the cursor of the framebuffer to the given position
 *
 *  \param y The new y position of the cursor
 *  \param x The new x position of the cursor
 */
void fb_move_cursor(int y, int x);

/*! \brief Moves the cursor of the framebuffer to the given position
 *
 *  \param pos The new position of the cursor (0 to 1999)
 */
void fb_move_cursor_simple(int pos);

/*! \brief Write text using the framebuffer
 *
 *  \param text The text to write
 *  \param len The lenght of the text
 *  \param line The line of witch the text will be displayed (0 to 24)
 *  \param offset The off to space up the text from the left
 *  \param blink 0 or 1, blink switch
 */
void fb_write_text(char *text, int len, int line, int offset, int blink);

/*! \brief Clear the framebuffer
 */
void fb_clear_screen();

/*! \brief Enable the cursor
 */
void fb_enable_cursor(unsigned char cursor_start, unsigned char cursor_end);

/*! \brief Disable the cursor
 */
void fb_disable_cursor();

/*! \brief Return the current cursor position
 *
 *  \return the current cursor position
 */
unsigned short int fb_get_cursor_position();

/*! \brief Write the content of the buffer and align the cursor
 *  
 *  \param buf The buffer to write
 *  \param len The len of the buffer
 */
void fb_write(char *buf, unsigned int len);

/*! \brief Return to the beginning of the next line
 */
void fb_line_return();

#endif

