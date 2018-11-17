#ifndef LEDDRIVER_H
#define LEDDRIVER_H

#include <Arduino.h>
#include "defines.h"

enum class LightStatus {
	OFF, ON
};

class LightDriver {
public:
	LightDriver();
	virtual ~LightDriver() {
	}
	virtual void setup();
	void setCurrentLevel(float level);
	float getCurrentLevel();
	virtual void switchLightStatus(LightStatus lightStatus);
	virtual void toggleLightStatus();
	LightStatus getLightStatus();
protected:
	uint16_t getPwmAmount();
private:
	void digPotWrite(unsigned int value);
	LightStatus lightStatus = LightStatus::OFF;
	float currentLevel = 0.0f;
	uint16_t pwmAmount = 0;
};

#endif
