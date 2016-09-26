/*
 * my_uart_init_rx.c
 *
 *  Created on: 24/09/2016
 *  Author: D. O. Corlett
 *
 *	Initalises the serial port and also
 *	receives serial data from PC, displays
 *	it on an LCD, and retransmits it back
 *	to the PC.
 */

#include <avr/io.h>
//#include "libser.h"
#include <util/delay.h>
#include "my_lcd.h"

/* Initalise the serial port for the given board rate/100 and MC clock speed in MHz*/
void my_uart0_init(unsigned int BaudRate, unsigned int ClockSpeed)
{
	unsigned int UBRR0Val = (ClockSpeed*1000000/16/(BaudRate*100))-1;	// Calculate UBRRn value.

	/* Set the board rate */
	UBRR0H = (unsigned char) UBRR0Val >> 8; 	// Put 4 MSB of 12-bit baud rate in UBRR
	UBRR0L = (unsigned char) UBRR0Val; 			// Put 8 LSB of baud rate in UBRR

	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);

	/* Set frame format: even parity, 1 stop bit, 8-bit data */
	UCSR0C = (1 << UPM01) | (0 << USBS0) | (1 << UCSZ01)|(1 << UCSZ00);
}

/*
 * 	Continually checks the receive flag to see
 *  if data has been received, then returns
 *  the data when it has been received.
 */
char my_uart0_rx_byte(void)
{
	while( !(UCSR0A & (1 << RXC0)) )
	{
		// Do nothing until there is data to be read.
	}

	return UDR0;		// Return the received byte from UDR0 register.
}

/*
 *	Waits until transmit buffer is empty then
 *	transmits the argument byte via the serial
 *	port.
 */
void my_uart0_tx_byte(unsigned char byte)
{
	/* Wait until the transmit buffer is empty. */
	while( !(UCSR0A & (1 << UDRE0)) )
	{
		// Do nothing until the data is ready to be sent.
	}

	UDR0 = byte;		// Put the data byte into the buffer to send the byte.
}



int main()
{
	char RxByte;
	char con[32];

	my_lcd_init(4);						// Initalise LCD in 4 bit mode.
	my_uart0_init(96, 16);				// Initalise the serial communication at a board rate of 9600 Hz

	ctrl_port_b = 1;					// Set LCD control lines to port B.

	while(1)
	{
		RxByte = my_uart0_rx_byte();	// Wait until received message from PC.

		my_uart0_tx_byte(RxByte);		// Transmit the received message back to the PC.

		/* Display received message on LCD */
		snprintf(con, 32, "%s%c", "Received: ", RxByte);
		my_lcd_display(con);

	}
	return 0;
}
