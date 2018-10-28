#include "LithiumBattery.h"
#include "Arduino.h"

LithiumBattery::LithiumBattery(float voltageFull, float voltageEmpty,
		float firstLinearStepEndVoltage, float firstLinearStepEndCapacity, uint8_t voltageSensingPin, uint8_t batteriesInSeries) {
	this->voltageFull = voltageFull;
	this->voltageEmpty = voltageEmpty;
	this->firstLinearStepEndVoltage = firstLinearStepEndVoltage;
	this->firstLinearStepEndCapacity = firstLinearStepEndCapacity;
	this->voltageSensingPin = voltageSensingPin;
	this->batteriesInSeries = batteriesInSeries;
}

/**
 * Returns a value between 0.0 and 1.0
 */
float LithiumBattery::getRemainingCharge() {
	float currentVoltage = constrain(getCurrentVoltage(), voltageEmpty,
			voltageFull);
	if (currentVoltage < firstLinearStepEndCapacity) {
		return (currentVoltage - voltageEmpty)
				* (firstLinearStepEndCapacity)
				/ (firstLinearStepEndVoltage - voltageEmpty);
	} else {
			return firstLinearStepEndCapacity
					+ (currentVoltage - firstLinearStepEndVoltage)
							* (1.0f - firstLinearStepEndCapacity)
							/ (voltageFull - firstLinearStepEndVoltage);
	}
}

float LithiumBattery::getCurrentVoltage() {
	float analogValue = (analogRead(voltageSensingPin) + analogRead(voltageSensingPin)) / 2.0;
	return analogValue * (5.0f / 1023.0f / batteriesInSeries);
}
