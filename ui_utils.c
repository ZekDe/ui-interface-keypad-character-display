/*
 * ui_utils.c
 *
 *  Created on:
 *      Author:
 */
#include "ui_utils.h"
#include "ui.h"

void BTN_ENTER_PGX_handler(void)
{
	if (s_pg0_obj.o_active)	{s_pg0_obj.s_btn[BTN_ENTER_PG0].emit_btn_pressed();}
	//else if (s_pgx_obj.o_active){s_pgx_obj.s_btn[BTN_ENTER_PGX].emit_btn_pressed();}
}

void BTN_DOWN_PGX_handler(void)
{
	if (s_pg0_obj.o_active){s_pg0_obj.s_btn[BTN_DOWN_PG0].emit_btn_pressed();}
	//else if (s_pgx_obj.o_active){s_pgx_obj.s_btn[BTN_DOWN_PGX].emit_btn_pressed();}
}
