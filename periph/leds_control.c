#include "leds_control.h"

Led_t led1, led2, led3, led4, led5, led6, led7, led8;
Led_t *ledArray[] = {&led1, &led2, &led3, &led4, &led5, &led6, &led7, &led8};

void LedsControl_Init()
{
	Led_Init(&led1, LED1_GPIO, LED1_Pin);
	Led_Init(&led2, LED2_GPIO, LED2_Pin);
	Led_Init(&led3, LED3_GPIO, LED3_Pin);
	Led_Init(&led4, LED4_GPIO, LED4_Pin);
	Led_Init(&led5, LED5_GPIO, LED5_Pin);
	Led_Init(&led6, LED6_GPIO, LED6_Pin);
	Led_Init(&led7, LED7_GPIO, LED7_Pin);
	Led_Init(&led8, LED8_GPIO, LED8_Pin);
}
