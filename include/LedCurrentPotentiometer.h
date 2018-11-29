#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include "gnulight_config.h"

#include <stdint.h>
#include <CappablePotentiometer.h>
#include <DelayedCappablePotentiometerActuator.h>

#define LEVEL_MAX_LIMIT_TRANSITION_MS 2000
#define MIN_LEVEL_WITHOUT_PWM 0.031f

class LedCurrentPotentiometer: public CappablePotentiometer {
public:
	LedCurrentPotentiometer(TaskManager &taskManager);
	void setup();
	void updateLevelMaxLimit();
	void setBatteryCausedLimit(float limit);
	void setTemperatureCausedLimit(float limit);
	void onSetLevel(float level) override;
private:
	void digPotWrite(uint16_t value);
	float battCausedLimit = 1.0f;
	float tempCausedLimit = 1.0f;
	DelayedCappablePotentiometerActuator *delayedMaxCurrentLevelSetter;
};

#endif
