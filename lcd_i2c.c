#include "lcd_i2c.h"

static uint8_t b_lcd_addr;
static uint8_t b_lcd_cols;
static uint8_t b_lcd_rows;
static uint8_t b_lcd_charsize;
static uint8_t b_lcd_backlight;
static uint8_t b_lcd_display_control;
static uint8_t b_lcd_display_mode;

typedef struct
{
	uint8_t row;
	uint8_t col;
}cursor_pos_t;

static cursor_pos_t s_pos;


/**
 * @brief platform delay
 */
static void delay_ms(uint32_t dw_ms)
{
	// delay
}


void i2c_master_init_for_targetMCU(void)
{
	// platform i2c initialization
	// for esp32
	/*
	int i2c_master_port = I2C_MASTER_NUM;

	i2c_config_t conf =
	{ .mode = I2C_MODE_MASTER, .sda_io_num =
	I2C_MASTER_SDA_IO, .scl_io_num = I2C_MASTER_SCL_IO, .sda_pullup_en = GPIO_PULLUP_ENABLE, .scl_pullup_en =
			GPIO_PULLUP_ENABLE, .master.clk_speed = I2C_MASTER_FREQ_HZ, };

	i2c_param_config(i2c_master_port, &conf);

	return i2c_driver_install(i2c_master_port, conf.mode,
	I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
	*/
}

/**
 * @fn void i2c_master_transmit(const uint8_t*, uint8_t)
 * @brief platform transmit
 * @param pb_data
 * @param b_size
 */
static void i2c_master_transmit(const uint8_t *pb_data, uint8_t b_size)
{
	// platform i2c transmit function
	// for esp32
	/*i2c_master_write_to_device(I2C_MASTER_NUM, SLAVE_ADDRESS_LCD, pb_data, b_size,
	I2C_MASTER_TIMEOUT_MS / portTICK_RATE_MS);*/
}


/* HARDWARE SECTION END */





/************ low level data pushing commands **********/

void lcd_load_custom_character(uint8_t char_num, uint8_t *rows)
{
	lcd_create_char(char_num, rows);
}

/*********** mid level commands, for sending data/cmds */
static void lcd_send(uint8_t b_val, uint8_t mode)
{
	uint8_t data_u, data_l;
	uint8_t data_t[4];

	if (mode == RS) // data
	{
		data_u = (b_val & 0xf0);
		data_l = ((b_val << 4) & 0xf0);
		data_t[0] = data_u | 0x0D;  //en=1, rs=1
		data_t[1] = data_u | 0x09;  //en=0, rs=1
		data_t[2] = data_l | 0x0D;  //en=1, rs=1
		data_t[3] = data_l | 0x09;  //en=0, rs=1
	}
	else// command
	{
		data_u = (b_val & 0xf0);
		data_l = ((b_val << 4) & 0xf0);
		data_t[0] = data_u | 0x0C;  //en=1, rs=0
		data_t[1] = data_u | 0x08;  //en=0, rs=0
		data_t[2] = data_l | 0x0C;  //en=1, rs=0
		data_t[3] = data_l | 0x08;  //en=0, rs=0
	}
	i2c_master_transmit(data_t, 4);
}

static void lcd_command(uint8_t b_val)
{
	lcd_send(b_val, 0);
}

/**
 * @fn void lcd_write(const char*, uint8_t)
 * @brief Writes the data to the output stream
 *
 * @pre
 * @post
 * @param pc_str
 * @param b_size
 */
void lcd_write(const char *pc_str, uint8_t b_size)
{
	for(uint8_t i = 0; i < b_size; ++i)
	{
		lcd_send((uint8_t)pc_str[i], RS);
	}
}

/**
 * @fn void lcd_write_line(const char*, uint8_t)
 * @brief Writes the data followed by the current line to the output stream.
 *
 * @pre
 * @post
 * @param pc_str
 * @param b_size
 */
void lcd_write_line(const char *pc_str, uint8_t b_size)
{
	lcd_write(pc_str, b_size);
	lcd_set_cursor(0, s_pos.row + 1);
}


/********** high level commands, for the user! */

void lcd_set_attr(uint8_t b_addr, uint8_t b_cols, uint8_t b_rows, uint8_t b_charsize)
{
	b_lcd_addr = b_addr;
	b_lcd_cols = b_cols;
	b_lcd_rows = b_rows;
	b_lcd_charsize = b_charsize;
	b_lcd_backlight = LCD_BACKLIGHT;
}
void lcd_begin(void)
{
	uint8_t display_func;

	s_pos.row = 0;
	s_pos.col = 0;

	display_func = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;
	if (b_lcd_rows > 1)
	{
		display_func |= LCD_2LINE;
	}
	// for some 1 line displays you can select a 10 pixel high font
	if ((b_lcd_charsize != 0) && (b_lcd_rows == 1))
	{
		display_func |= LCD_5x10DOTS;
	}
	// SEE PAGE 45/46 FOR INITIALIZATION SPECIFICATION!
	// according to datasheet, we need at least 40ms after power rises above 2.7V
	// before sending commands. Arduino can turn on way befer 4.5V so we'll wait 50
	delay_ms(50);
	// Now we pull both RS and R/W low to begin commands
	lcd_command(b_lcd_backlight);
	delay_ms(1000);

	//put the LCD into 4 bit mode
	// this is according to the hitachi HD44780 datasheet
	// figure 24, pg 46

	// we start in 8bit mode, try to set 4 bit mode
	lcd_command(0x30);
	delay_ms(5);  // wait min 4.1ms

	// second try
	lcd_command(0x30);
	delay_ms(5);
	;  // wait min 4.1ms

	// third go!
	lcd_command(0x30);
	delay_ms(2);

	// finally, set to 4-bit interface
	lcd_command(0x20);

	// set # lines, font size, etc.
	lcd_command(LCD_FUNCTIONSET | display_func);

	// turn the display on with no cursor or blinking default
	b_lcd_display_control = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	lcd_display_on();

	// clear it off
	lcd_clear();

	// Initialize to default text direction (for roman languages)
	b_lcd_display_mode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	lcd_command(LCD_ENTRYMODESET | b_lcd_display_mode);

	lcd_home();
}

void lcd_clear(void)
{
	lcd_command(LCD_CLEARDISPLAY);  // clear display, set cursor position to zero
	delay_ms(10);  // this command takes a long time!
}

void lcd_home(void)
{
	s_pos.row = 0;
	s_pos.col = 0;
	lcd_command(LCD_RETURNHOME);  // set cursor position to zero
	delay_ms(10);  // this command takes a long time!
}

// Turn the display on/off (quickly)
void lcd_display_off(void)
{
	b_lcd_display_control &= ~LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}

void lcd_display_on(void)
{
	b_lcd_display_control |= LCD_DISPLAYON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}

void lcd_set_cursor(uint8_t col, uint8_t row)
{
	int row_offsets[] =
	{ 0x00, 0x40, 0x14, 0x54 };
	if (row > b_lcd_rows)
	{
		row = b_lcd_rows - 1;  // we count rows starting w/0
	}
	s_pos.row = row;
	s_pos.col = col;
	lcd_command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

// Turns the underline cursor on/off
void lcd_cursor_off(void)
{
	b_lcd_display_control &= ~LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}
void lcd_cursor_on(void)
{
	b_lcd_display_control |= LCD_CURSORON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}

// Turn on and off the blinking cursor
void lcd_blink_off(void)
{
	b_lcd_display_control &= ~LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}
void lcd_blink_on(void)
{
	b_lcd_display_control |= LCD_BLINKON;
	lcd_command(LCD_DISPLAYCONTROL | b_lcd_display_control);
}

// These commands scroll the display without changing the RAM
void lcd_scroll_display_left(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT);
}
void lcd_scroll_display_right(void)
{
	lcd_command(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT);
}

// This is for text that flows Left to Right
void lcd_left_to_right(void)
{
	b_lcd_display_mode |= LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | b_lcd_display_mode);
}

// This is for text that flows Right to Left
void lcd_right_to_left(void)
{
	b_lcd_display_mode &= ~LCD_ENTRYLEFT;
	lcd_command(LCD_ENTRYMODESET | b_lcd_display_mode);
}

// This will 'right justify' text from the cursor
void lcd_autoscroll_on(void)
{
	b_lcd_display_mode |= LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | b_lcd_display_mode);
}

// This will 'left justify' text from the cursor
void lcd_autoscroll_off(void)
{
	b_lcd_display_mode &= ~LCD_ENTRYSHIFTINCREMENT;
	lcd_command(LCD_ENTRYMODESET | b_lcd_display_mode);
}

// Allows us to fill the first 8 CGRAM locations
// with custom characters
void lcd_create_char(uint8_t location, uint8_t charmap[])
{
	location &= 0x7;  // we only have 8 locations 0-7
	lcd_command(LCD_SETCGRAMADDR | (location << 3));
	lcd_write((char*)charmap, 8);
}




