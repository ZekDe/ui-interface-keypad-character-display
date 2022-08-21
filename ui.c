/*
 * ui.c
 *
 *  Created on:
 *      Author:
 */
#include "ui.h"

page0_t s_pg0_obj;
pg0_data_t s_pg0_data;

//pagex_t s_pgx_obj;
//pgx_data_t s_pgx_data;

/* PAGE 0*/
static void callback_pg0_btn0_pressed(void);
static void callback_pg0_btn1_pressed(void);

static void callback_pg0_lbl0_set_text(const char *pc_str, uint8_t b_size);
static void callback_pg0_lbl1_set_text(const char *pc_str, uint8_t b_size);

static void callback_pg0_lbl0_set_visible(bool);
static void callback_pg0_lbl1_set_visible(bool);

/* PAGE X*/


void ui_hide_all_pages(void)
{
	s_pg0_obj.o_active = false;
	//s_pgx_obj.o_active = false;
	
	lcd_clear();
}

/*	PAGE 0 BEGIN */
void ui_page0_ctor(void)
{
	lcd_blink_off();

	s_pg0_obj.s_btn[BTN_ENTER_PG0].emit_btn_pressed = callback_pg0_btn0_pressed;
	s_pg0_obj.s_btn[BTN_DOWN_PG0].emit_btn_pressed = callback_pg0_btn1_pressed;

	s_pg0_obj.lbl[LBL_TIME_PG0].set_text = callback_pg0_lbl0_set_text;
	s_pg0_obj.lbl[LBL_TEMP_PG0].set_text = callback_pg0_lbl1_set_text;


	s_pg0_obj.lbl[LBL_TIME_PG0].set_visible = callback_pg0_lbl0_set_visible;
	s_pg0_obj.lbl[LBL_TEMP_PG0].set_visible = callback_pg0_lbl1_set_visible;
}

void ui_page0_show(void)
{
	s_pg0_obj.o_active = true;

	lcd_clear();

	s_pg0_obj.lbl[LBL_TIME_PG0].set_text("     ", LBL_0_PG0_SIZE);
	s_pg0_obj.lbl[LBL_TEMP_PG0].set_text("   ", LBL_1_PG0_SIZE);

	s_pg0_obj.lbl[LBL_TIME_PG0].set_visible(true);
	s_pg0_obj.lbl[LBL_TEMP_PG0].set_visible(true);
}

static void callback_pg0_btn0_pressed(void)
{
	// app dependent
}

static void callback_pg0_btn1_pressed(void)
{
	// app dependent
}

static void callback_pg0_lbl0_set_visible(bool o_en)
{
	if (o_en)
	{
		SET_LBL_0_PG0_POS();
		lcd_write(s_pg0_obj.lbl0, LBL_0_PG0_SIZE);
	}
	else
	{
		SET_LBL_0_PG0_POS();
		lcd_write("     ", LBL_0_PG0_SIZE);
	}
}

static void callback_pg0_lbl1_set_visible(bool o_en)
{
	if (o_en)
	{
		SET_LBL_1_PG0_POS();
		lcd_write(s_pg0_obj.lbl1, LBL_1_PG0_SIZE);
	}
	else
	{
		SET_LBL_1_PG0_POS();
		lcd_write("   ", LBL_1_PG0_SIZE);
	}
}

static void callback_pg0_lbl0_set_text(const char *pc_str, uint8_t b_size)
{
	SET_LBL_0_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl0, pc_str, b_size);
}

static void callback_pg0_lbl1_set_text(cont char *pc_str, uint8_t b_size)
{
	SET_LBL_1_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl1, pc_str, b_size);
}

}
/*	PAGE 0 END */
