#ifndef LITHIUMBATTERY_H
#define LITHIUMBATTERY_H

#include "inttypes.h"
#include "defines.h"

class LithiumBattery {
public:
	LithiumBattery(float voltageFull, float voltageEmpty,
			float firstLinearStepEndVoltage, float firstLinearStepEndCapacity,
			uint8_t voltageSensingPin, uint8_t batteriesInSeries);
	float getVoltageFull() {
		return voltageFull;
	}
	;
	float getVoltageEmpty() {
		return voltageEmpty;
	}
	;
	float getCurrentVoltage();
	virtual float getRemainingCharge();
private:
	uint8_t voltageSensingPin;
	uint8_t batteriesInSeries;
	float voltageFull;
	float voltageEmpty;
	float firstLinearStepEndVoltage;
	float firstLinearStepEndCapacity;
};

#endif
