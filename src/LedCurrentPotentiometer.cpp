#include "LedCurrentPotentiometer.h"
#include <SPI.h>
#include <PWM.h>

#define LED_PIN_PWM_MAX 65535

LedCurrentPotentiometer::LedCurrentPotentiometer(TaskManager &taskManager) {
	setInstanceName("ledCurrPot");

	delayedMaxCurrentLevelSetter = new DelayedCappablePotentiometerActuator(
	DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, *this);
}

void LedCurrentPotentiometer::setup() {
	traceIfNamed("setup");

	Timer1_Initialize();
	SetPinFrequency(LED_PIN, 122);
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void LedCurrentPotentiometer::updateLevelMaxLimit() {
	traceIfNamed("updateLevelMaxLimit");

	float limit = min(tempCausedLimit, battCausedLimit);

	delayedMaxCurrentLevelSetter->setLevelMaxLimit(limit,
			MsToTaskTime(LEVEL_MAX_LIMIT_TRANSITION_MS));
}

void LedCurrentPotentiometer::setBatteryCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}

void LedCurrentPotentiometer::setTemperatureCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

#define DIG_POT_LEVEL (level - MIN_LEVEL_WITHOUT_PWM) / (1.0f - MIN_LEVEL_WITHOUT_PWM)

void LedCurrentPotentiometer::onSetLevel(float level) {
	// Imin senza pwm = 0.191 * 3 = 0.573 A
	// Imax = 0.616 * 3 = 1.848 A

	// Ioff = 0.16 mA -> 0.694 -> 0.429
	// ILED_ON(light off) = 9.15

	uint16_t digPotValue;
	uint16_t pwmAmount;
	if (level < MIN_LEVEL_WITHOUT_PWM) {

		/*
		 * PWM mode
		 */
		pwmAmount = (level / MIN_LEVEL_WITHOUT_PWM) * LED_PIN_PWM_MAX;
		digPotValue = 256;
	} else {

		/*
		 * PWM-less mode
		 */
		pwmAmount = LED_PIN_PWM_MAX;
		// (1.0f - digPotContrib) because of hardware configuration
		digPotValue = (uint16_t) (256 * (1.0f - DIG_POT_LEVEL));
	}

	digPotWrite(digPotValue);

	// LM2596 uses negative logic on shutdown button
	pwmWriteHR(LED_PIN, LED_PIN_PWM_MAX - pwmAmount);

	traceIfNamed("PWM: %u, digPotValue: %u", pwmAmount, digPotValue);
}

void LedCurrentPotentiometer::digPotWrite(uint16_t value) {
	SPI.transfer16(0x01FF & value);
	digitalWrite(PIN_SPI_SS, HIGH);
	digitalWrite(PIN_SPI_SS, LOW);
}
