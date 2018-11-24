#ifndef LITHIUMBATTERY_H
#define LITHIUMBATTERY_H

class LithiumBattery {
public:
	LithiumBattery(float voltageEmpty, float firstLinearStepEndVoltage,
			float voltageFull, float firstLinearStepEndCapacity,
			float (*readBatteryVoltageFunction)(void));

	float getVoltageFull() {
		return voltageFull;
	}

	float getVoltageEmpty() {
		return voltageEmpty;
	}

	float getRemainingCharge();
private:
	float (*readBatteryVoltage)(void);
	float voltageFull;
	float voltageEmpty;
	float firstLinearStepEndVoltage;
	float firstLinearStepEndCapacity;
};

inline LithiumBattery::LithiumBattery(float voltageEmpty,
		float firstLinearStepEndVoltage, float voltageFull,
		float firstLinearStepEndCapacity, float (*readBatteryVoltageFunction)(void)) {
	this->readBatteryVoltage = readBatteryVoltageFunction;
	this->voltageFull = voltageFull;
	this->voltageEmpty = voltageEmpty;
	this->firstLinearStepEndVoltage = firstLinearStepEndVoltage;
	this->firstLinearStepEndCapacity = firstLinearStepEndCapacity;
}

/**
 * Returns a value between 0.0 and 1.0
 */
inline float LithiumBattery::getRemainingCharge() {
	float currentVoltage = _constrain(readBatteryVoltage(), voltageEmpty,
			voltageFull);

	if (currentVoltage < firstLinearStepEndCapacity) {
		return (currentVoltage - voltageEmpty) * (firstLinearStepEndCapacity)
				/ (firstLinearStepEndVoltage - voltageEmpty);
	} else {
		return firstLinearStepEndCapacity
				+ (currentVoltage - firstLinearStepEndVoltage)
						* (1.0f - firstLinearStepEndCapacity)
						/ (voltageFull - firstLinearStepEndVoltage);
	}
}

#endif
