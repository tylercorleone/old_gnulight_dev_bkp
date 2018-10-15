#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#define MINIMUM_LIGHT_OUTPUT 0.002f

#include <Arduino.h>
#include "defines.h"

enum LightStatus {
	LIGHT_STATUS_ON, LIGHT_STATUS_OFF
};

class LightDriver {
public:
	LightDriver();
	virtual ~LightDriver() {};
	void setup();
	virtual void setPotentiometerLevel(float level);
	virtual float getPotentiometerLevel();
	void switchLightStatus(LightStatus lightStatus);
	void toggleLightStatus();
	LightStatus getLightStatus();
protected:
	uint8_t getPwmAmount();
private:
	LightStatus lightStatus;
	float potentiometerLevel = 0.0f;
	uint8_t pwmAmount;
	void digPotWrite(unsigned int value);
};

#endif
