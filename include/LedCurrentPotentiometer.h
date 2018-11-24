#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include "gnulight_config.h"

#include <stdint.h>
#include <CappablePotentiometer.h>
#include <DelayedCappablePotentiometerActuator.h>

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
};

#endif
