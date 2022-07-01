#include "ui.h"
#include "lcd_i2c.h"
#include "ui_utils.h"

// label definitions for pages
#define SET_LBL_0_PG0_POS()	lcd_set_cursor(2, 0)
#define SET_LBL_1_PG0_POS()	lcd_set_cursor(0, 0)
#define SET_LBL_2_PG0_POS()	lcd_set_cursor(0, 1)
#define SET_LBL_3_PG0_POS()	lcd_set_cursor(0, 2)
#define SET_LBL_4_PG0_POS()	lcd_set_cursor(0, 3)

#define SET_LBL_0_PG1_POS()	lcd_set_cursor(0, 0)
#define SET_LBL_1_PG1_POS()	lcd_set_cursor(5, 0)

// page objects
page0_t s_pg0_obj;
page1_t s_pg1_obj;

// data of pages for application
pg0_data_t s_pg0_data;
pg1_data_t s_pg1_data;


static void callback_pg0_btn0_pressed(void);

static void callback_pg0_lbl0_set_text(char * pc_str, uint8_t b_size);
static void callback_pg0_lbl1_set_text(char * pc_str, uint8_t b_size);
static void callback_pg0_lbl2_set_text(char * pc_str, uint8_t b_size);
static void callback_pg0_lbl3_set_text(char * pc_str, uint8_t b_size);
static void callback_pg0_lbl4_set_text(char * pc_str, uint8_t b_size);

static void callback_pg0_lbl0_set_visible(bool);
static void callback_pg0_lbl1_set_visible(bool);
static void callback_pg0_lbl2_set_visible(bool);
static void callback_pg0_lbl3_set_visible(bool);
static void callback_pg0_lbl4_set_visible(bool);



static void callback_pg1_btn0_pressed(void);

static void callback_pg1_lbl0_set_text(char * pc_str, uint8_t b_size);
static void callback_pg1_lbl1_set_text(char * pc_str, uint8_t b_size);

static void callback_pg1_lbl0_set_visible(bool);
static void callback_pg1_lbl1_set_visible(bool);


/*	PAGE 0 BEGIN */
void ui_page0_ctor(void)
{
	s_pg0_obj.s_btn[BTN_ENTER_PG0].emit_btn_pressed = callback_pg0_btn0_pressed;

	s_pg0_obj.lbl[LBL_SETTINGS_PG0].set_text = callback_pg0_lbl0_set_text;
	s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_text = callback_pg0_lbl1_set_text;
	s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_text = callback_pg0_lbl2_set_text;
	s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_text = callback_pg0_lbl3_set_text;
	s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_text = callback_pg0_lbl4_set_text;

	s_pg0_obj.lbl[LBL_SETTINGS_PG0].set_visible = callback_pg0_lbl0_set_visible;
	s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_visible = callback_pg0_lbl1_set_visible;
	s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_visible = callback_pg0_lbl2_set_visible;
	s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_visible = callback_pg0_lbl3_set_visible;
	s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_visible = callback_pg0_lbl4_set_visible;
}

void ui_page0_show(void)
{
	s_pg0_obj.o_active = true;
	lcd_clear();

	s_pg0_obj.lbl[LBL_SETTINGS_PG0].set_text("settings", LBL_0_PG0_SIZE);
	s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_text("->", LBL_1_PG0_SIZE);
	s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_text("->", LBL_2_PG0_SIZE);
	s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_text("->", LBL_3_PG0_SIZE);
	s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_text("->", LBL_4_PG0_SIZE);

	move_arrow(s_pg0_data.b_cursor_pos);
}

void ui_page0_hide(void)
{
	s_pg0_obj.o_active = false;
	lcd_clear();
}

static void callback_pg0_btn0_pressed(void)
{
	// test code
	move_arrow(s_pg0_data.b_cursor_pos);
	++s_pg0_data.b_cursor_pos;
	if(s_pg0_data.b_cursor_pos == 3)
	{
		ui_page0_hide();
		ui_page1_show();
		s_pg0_data.b_cursor_pos = 0;
	}

}

static void callback_pg0_lbl0_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_0_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl0, pc_str, b_size);
}

static void callback_pg0_lbl1_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_1_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl1, pc_str, b_size);
}

static void callback_pg0_lbl2_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_2_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl2, pc_str, b_size);
}

static void callback_pg0_lbl3_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_3_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl3, pc_str, b_size);
}

static void callback_pg0_lbl4_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_4_PG0_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg0_obj.lbl4, pc_str, b_size);
}

static void callback_pg0_lbl0_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_0_PG0_POS();
		lcd_write(s_pg0_obj.lbl0, LBL_0_PG0_SIZE);
	}
	else
	{
		SET_LBL_0_PG0_POS();
		lcd_write("        ", LBL_0_PG0_SIZE);
	}
}

static void callback_pg0_lbl1_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_1_PG0_POS();
		lcd_write(s_pg0_obj.lbl1, LBL_1_PG0_SIZE);
	}
	else
	{
		SET_LBL_1_PG0_POS();
		lcd_write("  ", LBL_1_PG0_SIZE);
	}
}

static void callback_pg0_lbl2_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_2_PG0_POS();
		lcd_write(s_pg0_obj.lbl2, LBL_2_PG0_SIZE);
	}
	else
	{
		SET_LBL_2_PG0_POS();
		lcd_write("  ", LBL_2_PG0_SIZE);
	}
}

static void callback_pg0_lbl3_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_3_PG0_POS();
		lcd_write(s_pg0_obj.lbl3, LBL_3_PG0_SIZE);
	}
	else
	{
		SET_LBL_3_PG0_POS();
		lcd_write("  ", LBL_3_PG0_SIZE);
	}
}

static void callback_pg0_lbl4_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_4_PG0_POS();
		lcd_write(s_pg0_obj.lbl4, LBL_4_PG0_SIZE);
	}
	else
	{
		SET_LBL_4_PG0_POS();
		lcd_write("  ", LBL_4_PG0_SIZE);
	}
}

/*	PAGE 1 BEGIN */
void ui_page1_ctor(void)
{
	s_pg1_obj.s_btn[BTN_ENTER_PG1].emit_btn_pressed = callback_pg1_btn0_pressed;

	s_pg1_obj.lbl[LBL_NEW_PG1].set_text = callback_pg1_lbl0_set_text;
	s_pg1_obj.lbl[LBL_PAGE_PG1].set_text = callback_pg1_lbl1_set_text;

	s_pg1_obj.lbl[LBL_NEW_PG1].set_visible = callback_pg1_lbl0_set_visible;
	s_pg1_obj.lbl[LBL_PAGE_PG1].set_visible = callback_pg1_lbl1_set_visible;

}

void ui_page1_show(void)
{
	s_pg1_obj.o_active = true;

	s_pg1_obj.lbl[LBL_NEW_PG1].set_text("NEW", LBL_0_PG1_SIZE);
	s_pg1_obj.lbl[LBL_PAGE_PG1].set_text("PAGE", LBL_1_PG1_SIZE);

	s_pg1_obj.lbl[LBL_NEW_PG1].set_visible(true);
	s_pg1_obj.lbl[LBL_PAGE_PG1].set_visible(true);

}

void ui_page1_hide(void)
{
	s_pg1_obj.o_active = false;
	lcd_clear();
}

static void callback_pg1_btn0_pressed(void)
{
	ui_page1_hide();
	ui_page0_show();
}

static void callback_pg1_lbl0_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_0_PG1_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg1_obj.lbl0, pc_str, b_size);
}

static void callback_pg1_lbl1_set_text(char * pc_str, uint8_t b_size)
{
	SET_LBL_1_PG1_POS();
	lcd_write(pc_str, b_size);
	str_cpy(s_pg1_obj.lbl1, pc_str, b_size);
}

static void callback_pg1_lbl0_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_0_PG1_POS();
		lcd_write(s_pg1_obj.lbl0, LBL_0_PG1_SIZE);
	}
	else
	{
		SET_LBL_0_PG1_POS();
		lcd_write("        ", LBL_0_PG1_SIZE);
	}
}

static void callback_pg1_lbl1_set_visible(bool o_en)
{
	if(o_en)
	{
		SET_LBL_1_PG1_POS();
		lcd_write(s_pg1_obj.lbl1, LBL_1_PG1_SIZE);
	}
	else
	{
		SET_LBL_1_PG1_POS();
		lcd_write("  ", LBL_1_PG1_SIZE);
	}
}


