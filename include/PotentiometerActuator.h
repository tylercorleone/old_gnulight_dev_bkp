#ifndef POTENTIOMETERACTUATOR_H
#define POTENTIOMETERACTUATOR_H

#include "defines.h"
#include <Task.h>

class AdvancedLightDriver;

class PotentiometerActuator: public Task {
public:
	PotentiometerActuator(AdvancedLightDriver* advancedLightDriver, uint32_t timeInterval, TaskManager* taskManager);
	void setPotentiometerLevel(float level, uint32_t transitionDurationMs, bool lightnessSimulationEnabled);
private:
	float readLevel();
	void writeLevel(float level);
	void OnUpdate(uint32_t timeInterval) override;
	TaskManager* taskManager;
	AdvancedLightDriver* advancedLightDriver;
	float targetLevel;
	uint32_t stepsToGo;
	bool operateAtRelativeCurrentLevel;
};

#endif
