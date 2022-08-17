/*
 * ui.h
 *
 *  Created on: 
 *      Author: 
 */

#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include <stdint.h>
#include "lcd_i2c.h"


#define LCD_HARDWARE_BLINK_ON() lcd_blink_on();
#define LCD_HARDWARE_BLINK_OFF() lcd_blink_off();

// PAGE POSITIONS
#define SET_LBL_0_PG0_POS()	lcd_set_cursor(0, 0) // time position
#define SET_LBL_1_PG0_POS()	lcd_set_cursor(17, 0) // temperature position
// #define SET_LBL_X_PGX_POS()	lcd_set_cursor(x, x)

/* PAGE 0*/
#define NUM_OF_LBL_PG0		2    // number of labels in page 0(time and temp)
#define NUM_OF_BTN_PG0		2	 // number of buttons in page 0(enter and down)
#define LBL_0_PG0_SIZE		5    // time info character size
#define LBL_1_PG0_SIZE		3	 //temperature info

/* PAGE X*/
// define your size of labels as above
#define NUM_OF_LBL_PGX		x
#define NUM_OF_BTN_PG0		x
#define LBL_0_PGX_SIZE		x

//button id (define your buttons as below how many you need like BTN_ENTER_PGX)
typedef enum
{
	BTN_ENTER_PG0 = 0,
	BTN_DOWN_PG0,
	BTN_END_PG0,
}button_obj_name_pg0_t;

/* typedef enum
{
	BTN_X_PGX = 0,
	BTN_XX_PGX,
	BTN_END_PGX,
}button_obj_name_pgx_t; */

//label id (define your labels as below how many you need like LBL_TIME_PGX)
typedef enum
{
	LBL_TIME_PG0 = 0,
	LBL_TEMP_PG0,
	LBL_END_PG0,

}label_obj_name_pg0_t;

/* typedef enum
{
	LBL_X_PGX = 0,
	LBL_XX_PGX,
	LBL_END_PGX,

}label_obj_name_pgx_t; */

//button functions
typedef struct
{
	// add button features
	void (*emit_btn_pressed)(void);
} button_t;

//label functions
typedef struct
{
	// add label features
	void (*set_text)(char*, uint8_t);
	void (*set_visible)(bool);
} label_t;


typedef struct
{
	button_t s_btn[NUM_OF_BTN_PG0];
	label_t  lbl[NUM_OF_LBL_PG0];

	char lbl0[LBL_0_PG0_SIZE];
	char lbl1[LBL_1_PG0_SIZE];

	bool o_active; // is page active or not?
} page0_t;

extern page0_t s_pg0_obj;
// extern pagex_t s_pgx_obj;

/*  APP DATA */
typedef struct
{
	int i_hour;
	int i_minute;
}pg0_data_t;

extern pg0_data_t s_pg0_data;



void ui_hide_all_pages(void);

void ui_page0_ctor(void);
void ui_page0_show(void);




inline void str_cpy(char *dest_str,char *src_str, uint8_t b_size)
{
	for(uint8_t i = 0; i < b_size; ++i)
	{
		dest_str[i] = src_str[i];
	}
}

#endif /* MAIN_UI_H_ */
