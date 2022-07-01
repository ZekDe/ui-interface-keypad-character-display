#include "lcd_i2c.h"
#include "ui.h"

void button_irq_handler(void *arg)
{
	if(s_pg0_obj.o_active)
	{
		s_pg0_obj.s_btn[BTN_ENTER_PG0].emit_btn_pressed();
	}
	else if(s_pg1_obj.o_active)
	{
		s_pg1_obj.s_btn[BTN_ENTER_PG1].emit_btn_pressed();
	}
}

void main(void)
{
	i2c_master_init_for_targetMCU();
	lcd_set_attr(SLAVE_ADDRESS_LCD, 20, 4, LCD_5x8DOTS);
	lcd_begin();
	lcd_clear();

	ui_page0_ctor();
	ui_page1_ctor();
	ui_page0_show();

}



