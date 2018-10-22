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
	virtual ~LightDriver() {};
	virtual void setup();
	void setCurrentLevel(float level);
	float getCurrentLevel();
	virtual void switchLightStatus(LightStatus lightStatus);
	virtual void toggleLightStatus();
	LightStatus getLightStatus();
protected:
	uint8_t getPwmAmount();
private:
	void digPotWrite(unsigned int value);
	LightStatus lightStatus;
	float currentLevel = 0.0f;
	uint8_t pwmAmount;
};

#endif
