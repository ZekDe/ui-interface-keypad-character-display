
SemaphoreHandle_t xSemaphore_btn0 = NULL;


void IRAM_ATTR button_isr_handler_btn0(void *arg)
{
	xSemaphoreGiveFromISR(xSemaphore_btn0, NULL);
}

// task that will react to button clicks
void button_task(void *arg)
{

	// infinite loop
	for (;;)
	{
		if (xSemaphoreTake(xSemaphore_btn0,portMAX_DELAY) == pdTRUE)
		{
			if(gpio_get_level(GPIO_INPUT_IO_0) == 1)
			{
				vTaskDelay(100 / portTICK_RATE_MS);
				BTN_ENTER_PGX_handler();
			}
			if(gpio_get_level(GPIO_INPUT_IO_1) == 1)
			{
				vTaskDelay(100 / portTICK_RATE_MS);
				BTN_DOWN_PGX_handler();
			}
		}
	}
}

void app_main()
{
	xSemaphore_btn0 = xSemaphoreCreateBinary();

	lcd_blink_off();



	// configure button and led pins as GPIO pins
	gpio_pad_select_gpio(GPIO_INPUT_IO_0);
	gpio_set_direction(GPIO_INPUT_IO_0, GPIO_MODE_INPUT);
	gpio_set_intr_type(GPIO_INPUT_IO_0, GPIO_INTR_POSEDGE);

	gpio_pad_select_gpio(GPIO_INPUT_IO_1);
	gpio_set_direction(GPIO_INPUT_IO_1, GPIO_MODE_INPUT);
	gpio_set_intr_type(GPIO_INPUT_IO_1, GPIO_INTR_POSEDGE);

	// start the task that will handle the button
	xTaskCreate(button_task, "button_task", 2048, NULL, 10, NULL);

	// install ISR service with default configuration
	gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);

	// attach the interrupt service routine
	gpio_isr_handler_add(GPIO_INPUT_IO_0, button_isr_handler_btn0, NULL);
	gpio_isr_handler_add(GPIO_INPUT_IO_1, button_isr_handler_btn0, NULL);

	ESP_ERROR_CHECK(i2c_master_init_for_esp32());
	lcd_set_attr(SLAVE_ADDRESS_LCD, 20, 4, LCD_5x8DOTS);
	lcd_begin();
	lcd_clear();

	gpio_set_direction(4, GPIO_MODE_OUTPUT);
	gpio_set_level(4, true);

	lcd_blink_off();

	ui_page0_ctor();
	//ui_pagex_ctor();
	ui_page0_show();
	LCD_HARDWARE_BLINK_OFF();
}

