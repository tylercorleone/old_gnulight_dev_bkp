#include "LedCurrentPotentiometer.h"

#include "defines.h"
#include <SPI.h>
#include <PWM.h>

#define LED_PIN_PWM_MAX 65535

LedCurrentPotentiometer::LedCurrentPotentiometer(Gnulight *gnulight) :
		HostSystemAware(gnulight) {

}

void LedCurrentPotentiometer::setup() {
	setInstanceName("ledCurrPot");
	traceNamedInstance("setup");

	Timer1_Initialize();
	SetPinFrequency(LED_PIN, 122);
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void LedCurrentPotentiometer::levelActuationFunction(float level) {
	float _level = constrain(level, 0.0, currentUpperLimit);

	// Imin senza pwm = 0.191 * 3 = 0.573 A
	// Imax = 0.616 * 3 = 1.848 A

	// Ioff = 0.16 mA -> 0.694 -> 0.429
	// ILED_ON(light off) = 9.15

	/*
	 il rapporto tra la corrente massima e quella minima ottenibile senza usare pwm è del 3.1%
	 */
	float K = 0.031f;
	float x;
	if (_level <= K) {
		pwmAmount = LED_PIN_PWM_MAX * _level / K;
		x = 0;
	} else {
		pwmAmount = LED_PIN_PWM_MAX;
		x = (_level - K) / (1.0f - K);
	}

	pwmWriteHR(LED_PIN, LED_PIN_PWM_MAX - pwmAmount); // (LED_PIN_PWM_MAX - pwm) because of negative logic of shuttown pin of LM2596

	uint16_t digPotValue = (uint16_t) (256 * (1.0f - x));
	digPotWrite(digPotValue);

	traceNamedInstance("pwmAmount: %u, digPotValue: %u", pwmAmount, digPotValue);
}

float LedCurrentPotentiometer::getCurrentUpperLimit() {
	return currentUpperLimit;
}

void LedCurrentPotentiometer::setCurrentUpperLimit(float limit,
		uint32_t transitionDurationMs) {
	traceNamedInstance("setCurrentUpperLimit(%f, %u)", limit, transitionDurationMs);

	currentUpperLimit = constrain(limit, 0.0f, 1.0f);

	if (currentUpperLimit < level) {

		/*
		 * we have to reduce current
		 */
		currentActuator.setLevel(currentUpperLimit, transitionDurationMs);
	} else if (currentUpperLimit > level
			&& level < wantedCurrentLevel) {

		/*
		 * we can increase current
		 */
		currentActuator.setLevel(min(currentUpperLimit, wantedCurrentLevel),
				transitionDurationMs);
	}
}

void LedCurrentPotentiometer::digPotWrite(uint16_t value) {
	SPI.transfer16(0x01FF & value);
	digitalWrite(PIN_SPI_SS, HIGH);
	digitalWrite(PIN_SPI_SS, LOW);
}
