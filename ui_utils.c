#include "ui_utils.h"
#include "ui.h"

void str_cpy(char *dest_str,char *src_str, uint8_t b_size)
{
	for(uint8_t i = 0; i < b_size; ++i)
	{
		dest_str[i] = src_str[i];
	}
}

void move_arrow(uint8_t b_pos)
{
	if(b_pos == 0)
	{
		s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_visible(true);
		s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_visible(false);
	}
	else if(b_pos == 1)
	{
		s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_visible(true);
		s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_visible(false);
	}
	else if(b_pos == 2)
	{
		s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_visible(true);
		s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_visible(false);
	}
	else if( b_pos == 3)
	{
		s_pg0_obj.lbl[LBL_ARROW_1_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_2_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_3_PG0].set_visible(false);
		s_pg0_obj.lbl[LBL_ARROW_4_PG0].set_visible(true);
	}
}

