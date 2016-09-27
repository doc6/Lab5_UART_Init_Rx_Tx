/*
 *  Module: my_lcd
 *  Author: M. J. Cree,
 *  Modified by D. O. Corlett,
 *
 *  (C) 2009-2014 The University of Waikato
 *
 *  Routines to interface to the 16x2 text LCD display.
 *  Modified to use D. O. Corlett's functions for
 *  displaying text to 16x2 LCD display
 */

#ifndef _LIBRARY_LCD_H_
#define _LIBRARY_LCD_H_


/*
 * LCD PINS:
 *
 * Port D:
 * 	Port D is used for the data lines to and from the LCD.
 * 	This LCD library allows the LCD to run in both 8-bit mode,
 * 	and 4-bit mode. When using both the LCD and the serial port
 * 	4-bit mode should be used to avoid collision on D6 and D7 as
 * 	these pins are the serial TX and RX.
 *
 * 	8-bit mode:
 * 	LCD:		ATMEGA 328p
 * 	D0	---->	D0
 * 	D1	---->	D1
 * 	D2	---->	D2
 * 	D3	---->	D3
 * 	D4	---->	D4
 * 	D5	---->	D5
 * 	D6	---->	D6
 * 	D7	---->	D7
 *
 * 	4-bit mode:
 * 	LCD:		ATMEGA 328p
 * 	D4	---->	D4
 * 	D5	---->	D5
 * 	D6	---->	D6
 * 	D7	---->	D7
 *
 * 	The LCD uses three control lines, EN, RW, and RS.
 * 	These control lines can be configured on port B or port C.
 * 	To set control line to Port B set the global variable: ctrl_port_b
 * 	to true(1), to set control line to port C set ctrl_port_b to false(0).
 * 	The control lines are set to port C by default.
 *
 * 	Control lines:
 * 	Port B:
 * 	EN	---->	B3
 * 	RW	---->	B4
 * 	RS	---->	B5
 *
 * 	Port C:
 * 	EN	---->	C3
 * 	RW	---->	C4
 * 	RS	---->	C5
 *
 */

/*
 * 	Initialise the LCD for Control on portC or portB and Data on portD for 8 bit and 4 bit mode depending on the argument (8 or 4).
 *
 * 	Set argument  bit to 8-bit mode or 4 for 4-bit mode.
 * 	Set argument ctrl_port_mode_b to 0 for control lines on port c, or >= 1 for port b.
 */
extern void my_lcd_init(unsigned char bit, unsigned char ctrl_port_mode_b);

/*
 * 	Clears the LCD.
 */
extern void my_lcd_clear(void);

/*
 *	Displays the argument string of characters on the LCD.
 */
extern void my_lcd_display(char string[]);

/*
 * 	Displays a string of words on the LCD without
 * 	splitting words between a line on the display.
 * 	Arguments are the length of the string array
 * 	and the string array, use: sizeof(string).
 */
extern void my_lcd_display_AutoWrap(int stringSize, char string[]);

/* 	Set ctrl_port_b to true(1) if using pins 11, 12, and 13 for the LCD
 * 	control pins: EN, RW, and RS respectively. If ctrl_port_b is not
 * 	true then the default control port is set to port C, with pins
 *	3, 4, and 5 as EN, RW, and RS respectively.
 */

#endif
