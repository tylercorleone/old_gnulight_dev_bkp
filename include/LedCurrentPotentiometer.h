#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include <stdint.h>
#include <CappablePotentiometer.h>
#include <DelayedCappablePotentiometerActuator.h>
#include "defines.h"

class LedCurrentPotentiometer: public CappablePotentiometer {
public:
	LedCurrentPotentiometer(TaskManager *taskManager);
	void setup();
	using CappablePotentiometer::setLevelMaxLimit;
	void setLevelMaxLimit(float level, uint32_t transitionDurationMs);
	void levelActuationFunction(float level) override;
private:
	void digPotWrite(uint16_t value);
	DelayedCappablePotentiometerActuator *delayedMaxCurrentLevelSetter;
	uint16_t pwmAmount = 0;
};

#endif
