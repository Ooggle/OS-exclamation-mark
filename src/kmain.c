/*! \file kmain.c
 *  \brief Contain the main functions of the kernel
 *  \date 2020/06/03
 */

#include "io.h"
#include "fb.h"

int kmain()
{
    fb_clear_screen();
    char thetext[] = "My Poor OS Project";
    char tell[] = "Tell your world!";
    fb_write_text(thetext, 18, 10, 0x3C, 0);
    fb_move_cursor(0, 0);
    //fb_disable_cursor();
    //fb_enable_cursor(0, 15);
    write(thetext, 18);
    for(int y = 0; y < 40; y++)
    {
        for(int i = 0; i < 2999999; i++);
        fb_line_return();
        write(tell, 16);
    }
    return 0;
}

