#include "LedCurrentPotentiometer.h"

#include "defines.h"
#include <SPI.h>
#include <PWM.h>

#define LED_PIN_PWM_MAX 65535

void LedCurrentPotentiometer::setup() {
	trace("LCP::setup");
	Timer1_Initialize();
	SetPinFrequency(LED_PIN, 122);
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void LedCurrentPotentiometer::levelActuationFunction(float level) {
	debug("LCP setting led current level " + level);
	// Imin senza pwm = 0.191 * 3 = 0.573 A
	// Imax = 0.616 * 3 = 1.848 A

	// Ioff = 0.16 mA -> 0.694 -> 0.429
	// ILED_ON(light off) = 9.15
	/*
	 il rapporto tra la corrente massima e quella minima ottenibile senza usare pwm è del 3.1%
	 */
	float K = 0.031f;
	float x;
	if (level <= K) {
		pwmAmount = LED_PIN_PWM_MAX * level / K;
		x = 0;
	} else {
		pwmAmount = LED_PIN_PWM_MAX;
		x = (level - K) / (1.0f - K);
	}

	trace("LCP pwmAmount: " + pwmAmount);
	pwmWriteHR(LED_PIN, LED_PIN_PWM_MAX - pwmAmount); // (LED_PIN_PWM_MAX - pwm) because of negative logic of shuttown pin of LM2596

	digPotWrite((int) (256 * (1.0f - x)));
}

void LedCurrentPotentiometer::digPotWrite(uint16_t value) {
	trace("LCP::digPotWrite " + value);
	SPI.transfer16(0x01FF & value);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, HIGH);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, LOW);
}