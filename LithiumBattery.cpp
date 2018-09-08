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

float LithiumBattery::getRelativeCapacity() {
	float currentVoltage = constrain(getCurrentVoltage(), voltageEmpty,
			voltageFull);
	if (currentVoltage >= firstLinearStepEndCapacity) {
		return firstLinearStepEndCapacity
				+ (currentVoltage - firstLinearStepEndVoltage)
						* (1.0f - firstLinearStepEndCapacity)
						/ (voltageFull - firstLinearStepEndVoltage);
	} else {
		return (currentVoltage - voltageEmpty)
				* (firstLinearStepEndCapacity)
				/ (firstLinearStepEndVoltage - voltageEmpty);
	}
}

float LithiumBattery::getMaxRelativeCurrent() {
	float currentCapacity = getRelativeCapacity();
	if (currentCapacity == 0.0f) {
		return 0.0f;
	} else if (currentCapacity < 0.05f) {
		return 0.05f;
	} else if (currentCapacity < 0.1f) {
		return 0.1f;
	} else if (currentCapacity < 0.3f) {
		return 0.5f;
	}
	return 1.0f;
}

float LithiumBattery::getCurrentVoltage() {
	int analogValue = (analogRead(voltageSensingPin) + analogRead(voltageSensingPin)) / 2;
	return analogValue * (5.0f / 1023.0f / batteriesInSeries);
}
