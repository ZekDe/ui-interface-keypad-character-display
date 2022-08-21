#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "i2c.h"
#include <stdbool.h>
#include <stdint.h>

// platform defines
#define I2C_MASTER_NUM  0
#define I2C_MASTER_TX_BUF_DISABLE  0
#define I2C_MASTER_RX_BUF_DISABLE  0
#define I2C_MASTER_SCL_IO  21
#define I2C_MASTER_SDA_IO  22
#define I2C_MASTER_FREQ_HZ  400000
#define I2C_MASTER_TIMEOUT_MS       1000
// platform defines end

#define SLAVE_ADDRESS_LCD			0x27//  0x4E
#define BACKLIGHT	0x08
#define LCD_NOBACKLIGHT 0x00
#define EN 4  // Enable bit
#define RW 2  // Read/Write bit
#define RS 1  // Register select bit

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00
void err_t i2c_master_init_for_targetMCU(void);


void lcd_set_attr(uint8_t b_addr, uint8_t b_cols, uint8_t b_rows, uint8_t b_charsize);
void lcd_begin(void);
void lcd_clear(void);
void lcd_home(void);
void lcd_display_off(void);
void lcd_display_on(void);
void lcd_set_cursor(uint8_t col, uint8_t row);
void lcd_cursor_off(void);
void lcd_cursor_on(void);
void lcd_blink_off(void);
void lcd_blink_on(void);
void lcd_scroll_display_left(void);
void lcd_scroll_display_right(void);
void lcd_left_to_right(void);
void lcd_right_to_left(void);
void lcd_autoscroll_on(void);
void lcd_autoscroll_off(void);
void lcd_write(const char *pc_str, uint8_t b_size);
void lcd_write_line(const char *pc_str, uint8_t b_size);

void lcd_create_char(uint8_t location, uint8_t charmap[]);

void lcd_load_custom_character(uint8_t char_num, uint8_t *rows);


/*
 * example
 * lcd_set_attr(SLAVE_ADDRESS_LCD, 20, 4, LCD_5x8DOTS);
 * lcd_begin();
 * lcd_cursor_on();
 * lcd_write_line("text", 4);
 * lcd_write("another text", 12);
 * lcd_write("text", 4);
 */

#endif /* LCD_I2C_H */
