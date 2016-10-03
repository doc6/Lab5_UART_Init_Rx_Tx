/*
 *  Module: my_lcd
 *  Author: D. O. Corlett
 *
 *	Functions for interfacing and displaying text to 16x2 LCD display.
 *
 */

#ifndef _LIBRARY_LCD_H_			// Checks if this library has already been included.
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
 * 	To set control line to Port B set the ctrl_port_mode_b
 * 	argument in the my_lcd_init() function to true(1), to set
 * 	control line to port C set ctrl_port_b to false(0). The
 * 	control lines are set to port C by default.
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
 *
 * 	Set argument ctrl_port_b to > 0 (true) if using pins 11, 12, and 13 for the LCD
 * 	control pins: EN, RW, and RS respectively.
 * 	Set argument ctrl_port_b to 0 (false) to set control lines to port C, with pins
 *	3, 4, and 5 as EN, RW, and RS respectively.
 */
extern void my_lcd_init(unsigned char bit, unsigned char ctrl_port_mode_b);

/*
 *	Sets the delay time for the LCD to process instructions to enable comparability between various LCD modules.
 *		general_delay sets the delay time for processing general instructions in us.
 *		clear_delay delay time for processing the clear instruction in us.
 *
 *		As per the dot matrix LCD data sheet supplied in ENEL317-16B lab manual:
 *		Default delay for general instuction is 50 us.
 *		Default delay for clear instruction is 2000 us.
 */
extern void my_lcd_process_delayTime(unsigned int general_delay, unsigned int clear_delay);

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

#endif
