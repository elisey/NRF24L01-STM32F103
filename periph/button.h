#pragma once

#include "stm32f10x.h"
#include <stdbool.h>

#define buttonNUM_OF_BUTTONS	2

#define buttonBUTTON1_GPIO		GPIOC
#define buttonBUTTON1_Pin		GPIO_Pin_14
#define buttonBUTTON1_RCC		RCC_APB2Periph_GPIOC

#define buttonBUTTON2_GPIO		GPIOC
#define buttonBUTTON2_Pin		GPIO_Pin_15
#define buttonBUTTON2_RCC		RCC_APB2Periph_GPIOC

#define buttonDEBOUNCE_BETWEEN_SCAN			10u
#define buttonDEBOUNCE_AFTER_PRESS				200u
#define buttonsPRESSED_LEVEL	Bit_RESET

typedef uint8_t button_t;


void Button_Process(void *pvParameters);
