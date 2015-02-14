#include "button.h"
#include "debug.h"
#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"

typedef struct	{
	GPIO_TypeDef* GPIOx;
	uint16_t pin;
	void (*callback)();
} buttonData_t;

buttonData_t buttonsData[buttonNUM_OF_BUTTONS];

static void prv_init();
static void prv_scanButton(button_t buttonsIndex);
static bool prv_isButtonPressed(button_t buttonsIndex);
static void prv_wasPress(button_t buttonsIndex);
static void prv_onButton1Pressed();
static void prv_onButton2Pressed();


void Button_Process(void *pvParameters)
{
	prv_init();
	while(1)
	{
		int i;
		for (i = 0; i < buttonNUM_OF_BUTTONS; ++i) {
			prv_scanButton(i);
		}
		vTaskDelay(10 / portTICK_RATE_MS);
	}
}

static void prv_init()
{
	buttonsData[0].GPIOx = buttonBUTTON1_GPIO;
	buttonsData[0].pin = buttonBUTTON1_Pin;
	buttonsData[0].callback = prv_onButton1Pressed;

	buttonsData[1].GPIOx = buttonBUTTON2_GPIO;
	buttonsData[1].pin = buttonBUTTON2_Pin;
	buttonsData[1].callback = prv_onButton2Pressed;

	RCC_APB2PeriphClockCmd (
			buttonBUTTON1_RCC |
			buttonBUTTON2_RCC,
			ENABLE );

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_IPU;

	int i;
	for (i = 0; i < buttonNUM_OF_BUTTONS; ++i) {
		gpio.GPIO_Pin = buttonsData[i].pin;
		GPIO_Init(buttonsData[i].GPIOx, &gpio);
	}
}

static void prv_scanButton(button_t buttonsIndex)
{
	int i;
	for (i = 0; i < 5; ++i) {
		if (prv_isButtonPressed(buttonsIndex) == false)	{
			return;
		}
		vTaskDelay(buttonDEBOUNCE_BETWEEN_SCAN / portTICK_RATE_MS);
	}

	//Было нажатие
	prv_wasPress(buttonsIndex);

	//ожидание отпускания кнопки
	while (prv_isButtonPressed(buttonsIndex) == true)	{
		vTaskDelay(buttonDEBOUNCE_BETWEEN_SCAN / portTICK_RATE_MS);
	}

	vTaskDelay(buttonDEBOUNCE_AFTER_PRESS / portTICK_RATE_MS);
}

static bool prv_isButtonPressed(button_t buttonsIndex)
{
	GPIO_TypeDef* GPIOx = buttonsData[buttonsIndex].GPIOx;
	uint16_t pin = buttonsData[buttonsIndex].pin;

	if (GPIO_ReadInputDataBit(GPIOx, pin) == buttonsPRESSED_LEVEL)	{
		return true;
	}
	return false;
}

static void prv_wasPress(button_t buttonsIndex)
{
	if (buttonsData[buttonsIndex].callback != NULL)	{
		buttonsData[buttonsIndex].callback();
	}
}

#include "radio.h"

static void prv_onButton1Pressed()
{
	debug_printf("Button 1 pressed\r");
	mesh_send(1, mesh_pkt_ack, "Button 1 pressed", 17, 3);

}

static void prv_onButton2Pressed()
{
	debug_printf("Button 2 pressed\r");
	mesh_send(1, mesh_pkt_ack, "Button 2 pressed", 17, 3);
}
