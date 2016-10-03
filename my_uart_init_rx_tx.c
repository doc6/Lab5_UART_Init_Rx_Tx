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

#include <stdio.h>
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

/*
 * 	Input format: ####X####
 *
 * 	Returns error message or result of operation in the given argument string.
 */
void parse_string_to_operation(char *str, int strLength)
{
	int num1 = 0;
	int num2 = 0;
	int strIndx = 0;
	int result;

	/* 0=no operation, error,
	 * 1=division,
	 * 2=multiplication,
	 * 3=subtraction,
	 * 4=addition.*/
	int operation = 0;

	/*
	 * 0=no error,
	 * 1=error 1: invalid input string format
	 * 2=error 2: invalid operator.
	 */
	int error_code = 0;

	int errorCode;

	/* Look for first number in operation: */
	while( str && str[strIndx] != '/' && str[strIndx] != '*' && str[strIndx] != '-' && str[strIndx] != '+' )
	{
			/* If the current character is a number
			 * Then convert it to an integer*/
			if( (str[strIndx] >= 48 && str[strIndx] <= 57) )
			{
				num1 += str[strIndx] - 48;		// Convert the number character to an int.
			}
			else
			{
				error_code = 1;					// error 1: invalid input string format.
			}

		strIndx++;
	}

	/* Determine the operator: */
	switch(str[strIndx])
	{
	case '/':
		operation = 1;
		break;
	case '*':
		operation = 21;
		break;
	case '-':
		operation = 3;
		break;
	case '+':
		operation = 4;
		break;
    default :	// error 2: invalid operator.
    	operation = 0;
	}

	// error 2: invalid operator.
	if(operation == 0)
	{
		error_code = 2;
	}

	/* Look for second number in operation: */
	while( str )
	{
			/* If the current character is a number
			 * Then convert it to an integer*/
			if( (str[strIndx] >= 48 && str[strIndx] <= 57) )
			{
				num2 += str[strIndx] - 48;		// Convert the number character to an int.
			}
			else
			{
				operation = 1;					// error 1: invalid input string format.
			}

		strIndx++;
	}

	/* check errors */
	if( error_code )
	{
		/* Do errors */
		switch(error_code)
		{
		case 1:		// error 1: invalid input string format.
			snprintf(str, strLength, "%s", "error 1: invalid input string format.");
			break;
		case 2:		// error 2: invalid operator.
			snprintf(str, strLength, "%s", "error 2: invalid operator.");
			break;
		default :	// Default error: Unknown error.
			snprintf(str, strLength, "%s", "Default error: Unknown error.");
		}
	}
	else
	{
		/* Do operation:*/
		switch(operation)
		{
		case 1:		// (/)
			snprintf(str, strLength, "%s = %i", str, num1/num2);
			break;
		case 2:		// (*)
			snprintf(str, strLength, "%s = %i", str, num1*num2);
			break;
		case 3:		// (-)
			snprintf(str, strLength, "%s = %i", str, num1-num2);
			break;
		case 4:		// (+)
			snprintf(str, strLength, "%s = %i", str, num1+num2);
			break;
		case 5:		// error 5: invalid input string format.
			snprintf(str, strLength, "%s", "error 5: invalid input string format.");
			break;
		}
	}
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
		parse_string_to_operation
	}
	return 0;
}
