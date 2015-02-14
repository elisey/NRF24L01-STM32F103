#pragma once

#include <stdint.h>
#include "stm32f10x.h"

#define DIP_INPUT1_GPIO		GPIOB
#define DIP_INPUT1_Pin		GPIO_Pin_0
#define DIP_INPUT1_RCC		RCC_APB2Periph_GPIOB

#define DIP_INPUT2_GPIO		GPIOB
#define DIP_INPUT2_Pin		GPIO_Pin_1
#define DIP_INPUT2_RCC		RCC_APB2Periph_GPIOB

#define DIP_INPUT3_GPIO		GPIOB
#define DIP_INPUT3_Pin		GPIO_Pin_2
#define DIP_INPUT3_RCC		RCC_APB2Periph_GPIOB

#define DIP_INPUT4_GPIO		GPIOA
#define DIP_INPUT4_Pin		GPIO_Pin_12
#define DIP_INPUT4_RCC		RCC_APB2Periph_GPIOA

#define DIP_INPUT5_GPIO		GPIOA
#define DIP_INPUT5_Pin		GPIO_Pin_11
#define DIP_INPUT5_RCC		RCC_APB2Periph_GPIOA

#define DIP_INPUT6_GPIO		GPIOA
#define DIP_INPUT6_Pin		GPIO_Pin_8
#define DIP_INPUT6_RCC		RCC_APB2Periph_GPIOA

void DipInput_Init();
uint8_t DipInput_GetData();
