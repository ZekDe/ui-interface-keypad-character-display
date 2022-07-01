#ifndef UI_H
#define UI_H

#include <stdbool.h>
#include <stdint.h>

/* PAGE 0*/
#define NUM_OF_LBL_PG0		5
#define NUM_OF_BTN_PG0		1
#define LBL_0_PG0_SIZE		8
#define LBL_1_PG0_SIZE		2
#define LBL_2_PG0_SIZE		2
#define LBL_3_PG0_SIZE		2
#define LBL_4_PG0_SIZE		2

/* PAGE 1*/
#define NUM_OF_LBL_PG1		2
#define NUM_OF_BTN_PG1		1
#define LBL_0_PG1_SIZE		3
#define LBL_1_PG1_SIZE		4

/* PAGE 0*/
typedef enum
{
	BTN_ENTER_PG0 = 0,
	BTN_END_PG0,
}button_obj_name_pg0_t;

typedef enum
{
	LBL_SETTINGS_PG0 = 0,
	LBL_ARROW_1_PG0,
	LBL_ARROW_2_PG0,
	LBL_ARROW_3_PG0,
	LBL_ARROW_4_PG0,
	LBL_END_PG0,

}label_obj_name_pg0_t;

/* PAGE 1*/
typedef enum
{
	BTN_ENTER_PG1 = 0,
	BTN_END_PG1,
}button_obj_name_pg1_t;

typedef enum
{
	LBL_NEW_PG1 = 0,
	LBL_PAGE_PG1,
	LBL_END_PG1,

}label_obj_name_pg1_t;

typedef struct
{
	void (*emit_btn_pressed)(void);
} button_t;

typedef struct
{
	void (*set_text)(char*, uint8_t);
	void (*set_visible)(bool);
} label_t;

typedef struct
{
	button_t s_btn[NUM_OF_BTN_PG0];
	label_t lbl[NUM_OF_LBL_PG0];

	char lbl0[LBL_0_PG0_SIZE];
	char lbl1[LBL_1_PG0_SIZE];
	char lbl2[LBL_2_PG0_SIZE];
	char lbl3[LBL_3_PG0_SIZE];
	char lbl4[LBL_4_PG0_SIZE];

	bool o_active;
} page0_t;

typedef struct
{
	button_t s_btn[NUM_OF_BTN_PG1];
	label_t lbl[NUM_OF_LBL_PG1];

	char lbl0[LBL_0_PG1_SIZE];
	char lbl1[LBL_1_PG1_SIZE];

	bool o_active;
} page1_t;

extern page0_t s_pg0_obj;
extern page1_t s_pg1_obj;

void ui_page0_ctor(void);
void ui_page0_show(void);
void ui_page0_hide(void);

void ui_page1_ctor(void);
void ui_page1_show(void);
void ui_page1_hide(void);



/*  PAGE0 USER DATA */
typedef struct
{
	uint8_t b_cursor_pos;
}pg0_data_t;

/*  PAGE1 USER DATA */
typedef struct
{

}pg1_data_t;

extern pg0_data_t s_pg0_data;
extern pg1_data_t s_pg1_data;


#endif /* MAIN_UI_H_ */
