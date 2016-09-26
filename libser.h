/*
 *  libser.h
 * 
 *  by M. J. Cree.
 * 
 *  Code for demonstrating the UART on the Arduino Uno.
 *
 *  (C) The University of Waikato 2012-2013
 */

/* Size of transmit and receive buffer.  This enables the receiver to
 * receive up to UART0_RXBUF_SIZE characters before the characters have to
 * be read.
 */
#include <stdio.h>			// Included my D.O. Corlett because FILE error...
#define UART0_RXBUF_SIZE 16
#define UART0_TXBUF_SIZE 16


/* UART low level entry points. */

/*
 * uart0_init(baud)
 *
 * Initialise the UART controller on the Arduino Uno.
 * Pass the required baudrate divided by 100 as baud.
 *
 * For example: uart0_init(3) sets baudrate to 300 bytes per second.
 *
 * In this implementation UART interrupts are used to transmit and recieve
 * characters on the serial port.  This enables the receiver to continue to
 * receive up to UART0_RXBUF_SIZE number of characters without intervention
 * from the calling program.
 */
extern void uart0_init(unsigned int baud);

/*
 * uart0_tx_byte(chr)
 *
 * Transmit the byte chr up the serial port.  Has a UART0_TXBUF_SIZE byte
 * transmit buffer so if the UART is busy queues the chr in the transmit
 * buffer (provided it is not full).
 *
 * Returns
 *   true --- byte queued for transmission
 *   false --- transmit bufffer full, cannot transmit.
 */
extern int uart0_tx_byte(char chr);

/*
 * uart0_rx_byte()
 *
 * Returns a byte received from the UART.  Bytes are queued in a
 * UART0_RXBUF_SIZE byte receive buffer if the serial port is not read quick
 * enough.  If the receive buffer overflows chars are lost.
 *
 * Returns
 *   -1 -- if no byte received
 *   char (>=0) -- if byte received
 */
extern int uart0_rx_byte(void);


/* UART buffered I/O */
/*
 * In the vein of gets() but receives a string from the UART.  Blocks
 * until a string is received.
 */
extern void uart0_gets(char *s, int size);

/* Like uart0_gets() but also echoes all received chars back up
 * the transmit line.
 */
extern void uart0_gets_echo(char *s, int size);

/* In the vein of puts() but transmits the string up the UART. */
extern void uart0_puts(char *s);


/* Blocking character transmit and receive that can be used to implement
 * stdin and stdout so that can use stdio from libc in main program. See AVR
 * libc documentation for example of how to use.
 */
extern int uart0_fputc(char c, FILE *f);
extern int uart0_fgetc(FILE *f);
