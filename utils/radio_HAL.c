#include "radio_HAL.h"
#include "nrf24L01Plus.h"
#include "debug.h"

#define ADDRESS_WIDTH	(5)		// (3 - 5)
#define CHANNEL_MHZ		(2460)	// 2400 - 2525 MHz
#define BITRATE_KBPS	(2000)	// 1000, 2000 Kbps
#define ADDRESS_FILLER	(0xC2)

uint8_t selfAddressArray[ADDRESS_WIDTH];
uint8_t broadcastAddressArray[ADDRESS_WIDTH] = {0, 0, ADDRESS_FILLER, ADDRESS_FILLER, ADDRESS_FILLER};

static void wordToBuffer(uint16_t inputData, uint8_t *buffer);
static uint16_t bufferToWord(uint8_t *buffer);

void Radio_HAL_Init(uint16_t selfAddress)
{
	wordToBuffer(selfAddress, selfAddressArray);

	nordic_init((selfAddressArray), broadcastAddressArray, 32, CHANNEL_MHZ, BITRATE_KBPS, ADDRESS_WIDTH);
	nordic_standby1_to_rx();
}

bool Radio_HAL_Send(uint16_t dstAddress, uint8_t *buffer, uint8_t sizeOfBuffer)
{
	nordic_rx_to_Stanby1();
	nordic_standby1_to_tx_mode1();

	uint8_t txAddress[ADDRESS_WIDTH];
	wordToBuffer(dstAddress, txAddress);

	nordic_set_tx_address(txAddress, ADDRESS_WIDTH);
	nordic_set_rx_pipe0_addr(txAddress, ADDRESS_WIDTH);

	bool result;
	result = nordic_mode1_send_single_packet(buffer, 32);

	nordic_set_rx_pipe0_addr(selfAddressArray, ADDRESS_WIDTH);

	nordic_standby1_to_rx();
	return result;
}

bool Radio_HAL_SendBroadcast(uint8_t *buffer, uint8_t sizeOfBuffer)
{
	nordic_rx_to_Stanby1();
	nordic_set_auto_ack_for_pipes(false, false, false, false, false, false);
	nordic_set_tx_address(broadcastAddressArray, ADDRESS_WIDTH);

	nordic_set_auto_transmit_options(250, 0);
	nordic_standby1_to_tx_mode1();

	bool result;
	result = nordic_mode1_send_single_packet(buffer, 32);
	nordic_set_auto_ack_for_pipes(true, false, false, false, false, false);
    nordic_set_auto_transmit_options(500, 3);
	nordic_standby1_to_rx();
	return result;
}

int Radio_HAL_Receive(uint8_t *buffer)
{
	if(nordic_is_packet_available())
	{
		nordic_read_rx_fifo(buffer, 32);

		// Only clear the interrupt if no more receivedPacket available
		// because nordic has 3 level Rx FIFO.
		if (!nordic_is_packet_available()) {
			nordic_clear_packet_available_flag();
		}
		return 32;
	}
	else	{
		return (-1);
	}
}

static void wordToBuffer(uint16_t inputData, uint8_t *buffer)
{
	buffer[0] = (uint8_t)(inputData & 0xFF);
	buffer[1] = (uint8_t)( (inputData >> 8) & 0xFF );
	/*
	 * Все неиспользуемые байты адреса заполняются значением 0xC2,
	 * чтобы повысить помехоустойчивость пакета.
	 */
	int i;
	for (i = 2; i < ADDRESS_WIDTH; ++i) {
		buffer[i] = ADDRESS_FILLER;
	}
}

static uint16_t bufferToWord(uint8_t *buffer)
{
	uint16_t result = 0;
	result = (uint16_t)(buffer[0]);
	result |= ( (uint16_t)(buffer[1]) << 8);
	return result;
}
