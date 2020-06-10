/*! \file serial.h
 *  \brief Contain the definition of serial.c
 *  \date 2020/06/05
 */

#ifndef INCLUDE_SERIAL_H
#define INCLUDE_SERIAL_H

/*! \brief The I/O ports
 *         
 *         All the I/O ports are calculated relative to the data port.
 *         This is because all serial ports (COM1, COM2, COM3, COM4)
 *         have their ports in the same order, but they start at different
 *         values.
 */
#define SERIAL_COM1_BASE 0x3F8

#define SERIAL_DATA_PORT(base) (base)
#define SERIAL_FIFO_COMMAND_PORT(base) (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base) (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base) (base + 5)

/*! \brief The I/O port Commands
 *         
 *         Tells the serial port to expect first the highest 8 bits on
 *         the data port, then the lowest 8 bits will follow.
 */
#define SERIAL_LINE_ENABLE_DLAB 0x80

/*! \brief Sets the speed of the data being sent. The default speed of a
 *         serial port is 115200 bits/s. The argument is a divisor of that
 *         number, hence the resulting speed becomes (115200 / divisor) bits/s.
 *
 *  \param com The COM port to configure
 *  \param divisor The divisor
 */
void serial_configure_baud_rate(unsigned short com, unsigned short divisor);

/*! \brief Configures the line of the given serial port. The port is set to
 *         have a data length of 8 bits, no parity, one stop bit and break
 *         control disabled.
 *
 *  \param com The serial port to configure
 */
void serial_configure_line(unsigned int com);

/*! \brief Checks whether the the transmit FIFO queue is empty or not for the given COM
 *  
 *  \param com the COM port
 *  \return 0 if the transmit FIFO queue is not empty
 *          1 if the transmit FIFO queue is empty
 */
int serial_is_transmit_fifo_empty(unsigned int com);

/*! \brief Write the content of the buffer to the chosen serial port
 *  
 *  \param com The I/O port of the serial
 *  \param buf The buffer to write
 *  \param len The length of the buffer
 */
void serial_write(unsigned int com, char *buf, unsigned int len);

#endif
