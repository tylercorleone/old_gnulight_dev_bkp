#ifndef POTENTIOMETERACTUATOR_H
#define POTENTIOMETERACTUATOR_H

#include "defines.h"
#include <Task.h>

#define TIMED_POTENTIOMETER_SETTER_INTERVAL_MS 30UL

class AdvancedLightDriver;

class PotentiometerActuator: public Task {
public:
	PotentiometerActuator(AdvancedLightDriver* advancedLightDriver, TaskManager* taskManager);
	void setPotentiometerLevel(float level, uint32_t transitionDurationMs, bool operateOnCurrent);
private:
	float readLevel();
	void writeLevel(float level);
	void OnUpdate(uint32_t timeInterval) override;
	AdvancedLightDriver* advancedLightDriver;
	TaskManager* taskManager;
	float targetLevel;
	uint32_t stepsToGo;
	bool operateOnCurrent;
};

#endif
