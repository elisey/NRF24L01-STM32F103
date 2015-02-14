#pragma once
#include "led.h"

#define LED1_GPIO	GPIOC
#define LED1_Pin	GPIO_Pin_6

#define LED2_GPIO	GPIOC
#define LED2_Pin	GPIO_Pin_7

#define LED3_GPIO	GPIOC
#define LED3_Pin	GPIO_Pin_8

#define LED4_GPIO	GPIOC
#define LED4_Pin	GPIO_Pin_9

#define LED5_GPIO	GPIOB
#define LED5_Pin	GPIO_Pin_6

#define LED6_GPIO	GPIOB
#define LED6_Pin	GPIO_Pin_7

#define LED7_GPIO	GPIOB
#define LED7_Pin	GPIO_Pin_8

#define LED8_GPIO	GPIOB
#define LED8_Pin	GPIO_Pin_9

extern Led_t led1, led2, led3, led4, led5, led6, led7, led8;
extern Led_t *ledArray[];
void LedsControl_Init();
