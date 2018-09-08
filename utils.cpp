#include "utils.h"
#include "defines.h"
#include <SPI.h>

void Utils::setPwmFrequency(int pin, int divisor) {
	// Set pin 9's PWM frequency to 3906 Hz (31250/8 = 3906)
	uint8_t mode;
	if (pin == 5 || pin == 6 || pin == 9 || pin == 10) {
		// Note that the base frequency for pins 3, 9, 10, and 11 is 31250 Hz
		switch (divisor) {
		case 1:
			mode = 0x01;
			break;
		case 8:
			mode = 0x02;
			break;
		case 64:
			mode = 0x03;
			break;
		case 256:
			mode = 0x04;
			break;
		case 1024:
			mode = 0x05;
			break;
		default:
			return;
		}
		if (pin == 5 || pin == 6) {
			//Note that the base frequency for pins 5 and 6 is 62500 Hz
			TCCR0B = (TCCR0B & 0b11111000) | mode;
		} else {
			TCCR1B = (TCCR1B & 0b11111000) | mode;
		}
	} else if (pin == 3 || pin == 11) {
		switch (divisor) {
		case 1:
			mode = 0x01;
			break;
		case 8:
			mode = 0x02;
			break;
		case 32:
			mode = 0x03;
			break;
		case 64:
			mode = 0x04;
			break;
		case 128:
			mode = 0x05;
			break;
		case 256:
			mode = 0x06;
			break;
		case 1024:
			mode = 0x7;
			break;
		default:
			return;
		}
		TCCR2B = (TCCR2B & 0b11111000) | mode;
	}
}

void Utils::digPotEPROMWrite(unsigned int value) {
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW);
	delay(5);
	SPI.transfer16(0x21FF & value);
	delay(5);
	digitalWrite(PIN_SPI_SS, HIGH);
	SPI.endTransaction();
	SPI.end();
}
