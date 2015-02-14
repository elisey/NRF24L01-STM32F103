#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>

void Radio_HAL_Init(uint16_t selfAddress);
bool Radio_HAL_Send(uint16_t dstAddress, uint8_t *buffer, uint8_t sizeOfBuffer);
bool Radio_HAL_SendBroadcast(uint8_t *buffer, uint8_t sizeOfBuffer);
int Radio_HAL_Receive(uint8_t *buffer);

#ifdef __cplusplus
}
#endif
