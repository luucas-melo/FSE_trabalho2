#ifndef LCD
#define LCD

// Define some device parameters
#define I2C_ADDR 0x27 // I2C device address

// Define some device constants
#define LCD_CHR 1 // Mode - Sending data
#define LCD_CMD 0 // Mode - Sending command

#define LINE1 0x80         // 1st line
#define LINE2 0xC0         // 2nd line
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

void show_temperatute_lcd(double, double, int);
void show_message_lcd(const char *);

#endif
