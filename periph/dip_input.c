#include "dip_input.h"
#include <stdbool.h>

#define bit(n)							(1u << (n))
#define setBit(x,n)           			((x) |= bit(n))
#define clrBit(x,n)  		  			((x) &= ~bit(n))
#define getBit(x,n)   		  			(((x) & bit(n)) ? 1u : 0u)

static void prv_gpioInit();

void DipInput_Init()
{
	prv_gpioInit();
}

uint8_t DipInput_GetData()
{
	uint8_t data = 0;

	if ((DIP_INPUT1_GPIO->IDR & DIP_INPUT1_Pin) != 0) {
		setBit(data, 0);
	}
	if ((DIP_INPUT2_GPIO->IDR & DIP_INPUT2_Pin) != 0) {
		setBit(data, 1);
	}
	if ((DIP_INPUT3_GPIO->IDR & DIP_INPUT3_Pin) != 0) {
		setBit(data, 2);
	}
	if ((DIP_INPUT4_GPIO->IDR & DIP_INPUT4_Pin) != 0) {
		setBit(data, 3);
	}
	if ((DIP_INPUT5_GPIO->IDR & DIP_INPUT5_Pin) != 0) {
		setBit(data, 4);
	}
	if ((DIP_INPUT6_GPIO->IDR & DIP_INPUT6_Pin) != 0) {
		setBit(data, 5);
	}
	return data;
}

static void prv_gpioInit()
{
	RCC_APB2PeriphClockCmd (
			DIP_INPUT1_RCC |
			DIP_INPUT2_RCC |
			DIP_INPUT3_RCC |
			DIP_INPUT4_RCC |
			DIP_INPUT5_RCC |
			DIP_INPUT6_RCC,
			ENABLE );

	GPIO_InitTypeDef gpio;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	gpio.GPIO_Mode = GPIO_Mode_IPU;

	gpio.GPIO_Pin = DIP_INPUT1_Pin;
	GPIO_Init(DIP_INPUT1_GPIO, &gpio);

	gpio.GPIO_Pin = DIP_INPUT2_Pin;
	GPIO_Init(DIP_INPUT2_GPIO, &gpio);

	gpio.GPIO_Pin = DIP_INPUT3_Pin;
	GPIO_Init(DIP_INPUT3_GPIO, &gpio);

	gpio.GPIO_Pin = DIP_INPUT4_Pin;
	GPIO_Init(DIP_INPUT4_GPIO, &gpio);

	gpio.GPIO_Pin = DIP_INPUT5_Pin;
	GPIO_Init(DIP_INPUT5_GPIO, &gpio);

	gpio.GPIO_Pin = DIP_INPUT6_Pin;
	GPIO_Init(DIP_INPUT6_GPIO, &gpio);
}
