
/*
 *
 * by Lewis Loflin www.bristolwatch.com lewis@bvu.net
 * http://www.bristolwatch.com/rpi/i2clcd.htm
 * Using wiringPi by Gordon Henderson
 *
 *
 * Port over lcd_i2c.py to C and added improvements.
 * Supports 16x2 and 20x4 screens.
 * This was to learn now the I2C lcd displays operate.
 * There is no warrenty of any kind use at your own risk.
 *
 */
#ifndef I2CLCD_H
#define I2CLCD_H

#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

// Define some device parameters
#define I2C_ADDR 0x27 // I2C device address

// Define some device constants
#define LCD_CHR 1 // Mode - Sending data
#define LCD_CMD 0 // Mode - Sending command

#define LINE1 0x80 // 1st line
#define LINE2 0xC0 // 2nd line

#define LCD_BACKLIGHT 0x08 // On
// LCD_BACKLIGHT = 0x00  # Off

#define ENABLE 0b00000100 // Enable bit

void lcd_init(void);
void lcd_byte(int bits, int mode);
void lcd_toggle_enable(int bits);

// added by Lewis
void typeInt(int i);
void typeFloat(float myFloat);
void lcdLoc(int line); // move cursor
void ClrLcd(void);     // clr LCD return home
void typeln(const char *s);
void typeChar(char val);
int fd; // seen by all subroutines

// float to string
void typeFloat(float myFloat);

// int to string
void typeInt(int i);

// clr lcd go home loc 0x80
void ClrLcd(void);

// go to location on LCD
void lcdLoc(int line);

// out char to LCD at current position
void typeChar(char val);

// this allows use of any size string
void typeln(const char *s);

void lcd_byte(int bits, int mode);

void lcd_toggle_enable(int bits);

void lcd_init();

#endif /* I2CLCD_H */