/*! \file serial.c
 *  \brief Contain the functions used to communicate with the serial
 *  \date 2020/06/05
 */

#include "io.h"
#include "serial.h"

void serial_configure_baud_rate(unsigned short com, unsigned short divisor)
{
    outb(SERIAL_LINE_COMMAND_PORT(com),
         SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com),
         (divisor >> 8) & 0x00FF);
    outb(SERIAL_DATA_PORT(com),
         divisor & 0x00FF);
}

void serial_configure_line(unsigned int com)
{
    /* Bit:     | 7 | 6 | 5 4 3 | 2 | 1 0 |
     * Content: | d | b | prty  | s | dl  |
     * Value:   | 0 | 0 | 0 0 0 | 0 | 1 1 | = 0x03
     */
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

int serial_is_transmit_fifo_empty(unsigned int com)
{
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(unsigned int com, char *buf, unsigned int len)
{
    //while(serial_is_transmit_fifo_empty(com) != 1);
    for(unsigned int i = 0; i < len; i++)
    {
        outb(com, (char) buf[i]);
        for(int y = 0; y < 3000000; y++);
    }
}


