#include "nrf24L01Plus.h"
#include "dip_input.h"
#include "leds_control.h"
#include "radio_HAL.h"
#include "debug.h"
uint16_t selfAddress;

void delay(int time)
{
	volatile int i;
	for (i = 0; i < time; ++i) {
	}
}

void sender()
{
	uint8_t size = 32;
	uint8_t data[32];
	int i;
	for (i = 0; i < size; ++i) {
		data[i] = i+5;
	}

	while(1)
	{
		size++;
		if (size > 32)	{
			size = 1;
		}
		data[0] = size ;
		Radio_HAL_SendBroadcast(data, size);

		if (Radio_HAL_Send(1, data, size) == true)	{
			Led_SetState(&led2, led_on);
		}
		else	{
			Led_SetState(&led2, led_off);
		}

		if (Radio_HAL_Send(2, data, size) == true)	{
			Led_SetState(&led3, led_on);
		}
		else	{
			Led_SetState(&led3, led_off);
		}

		Led_Tougle(&led1);

		//delay(2000000);
	}

}

void receiver()
{
	while(1)	{
		uint8_t data[32];

		int result = Radio_HAL_Receive(data);
		if (result != -1)	{

			Led_Tougle(&led3);
			if (result == data[0])	{
				Led_Tougle(&led4);
			}
			else	{
				Led_SetState(&led2, led_on);
				while(1);
			}
		}

	}
}

int main(void)
{
	Debug_Init();

	pin1_off;
	pin2_off;
	pin3_off;
	pin4_off;
	pin5_off;

	pin1_on;
	pin2_on;
	pin3_on;
	pin4_on;
	pin5_on;




	DipInput_Init();
	selfAddress = DipInput_GetData() & 0b11;

	LedsControl_Init();
	Radio_HAL_Init(selfAddress);

	while(1)
    {
    	if (selfAddress == (3))	{
    		sender();
    	}
    	else	{
    		receiver();
    	}


    }
}
