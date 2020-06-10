/*! \file kmain.c
 *  \brief Contain the main function of the kernel
 *  \date 2020/06/03
 */

#include "io.h"
#include "fb.h"
#include "serial.h"

int kmain()
{
    fb_clear_screen();
    char thetext[] = "OS! Project";
    char tell[] = "Tell your world!";
    char writted[] = "serial writted!";
    fb_write_text(thetext, 11, 10, 0x42, 0);
    fb_move_cursor(0, 0);
    fb_write(thetext, 11);

    // serial
    serial_configure_baud_rate(SERIAL_COM1_BASE, 1);
    serial_configure_line(SERIAL_COM1_BASE);
    serial_write(SERIAL_COM1_BASE, tell, 16);

    fb_line_return();
    fb_write(writted, 15);
    
    /* for(int y = 0; y < 40; y++)
    {
        for(int i = 0; i < 3000000; i++);
        fb_line_return();
        fb_write(tell, 16);
    } */
    return 0;
}

