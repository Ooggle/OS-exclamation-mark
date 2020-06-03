/*! \file io.h
 *  \brief Contain the definition of io.s
 *  \date 2020/06/02
 */

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

/*! \brief Sends the given data to the given I/O port. Defined in io.s
 *
 *  \param port The I/O port to send the data to
 *  \param data The data to send to the I/O port
 */
void outb(unsigned short port, unsigned char data);

/*! \brief Return a byte from a I/O port
 *
 *  \param port The address of the I/O port
 *  \return The read byte
 */
unsigned char inb(unsigned short port);

#endif
