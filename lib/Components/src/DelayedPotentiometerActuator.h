#ifndef DELAYEDPOTENTIOMETERACTUATOR_H
#define DELAYEDPOTENTIOMETERACTUATOR_H

#include <stdint.h>

#include "DelayedLevelSetter.h"
#include "Potentiometer.h"

class TaskManager;

class DelayedPotentiometerActuator: public DelayedLevelSetter {
public:
	DelayedPotentiometerActuator(uint32_t timeInterval,
			TaskManager *taskManager, Potentiometer *potentiometer);
protected:
	float readLevel() override;
	void writeLevel(float level) override;
	Potentiometer *potentiometer;
};

inline DelayedPotentiometerActuator::DelayedPotentiometerActuator(
		uint32_t timeInterval, TaskManager *taskManager,
		Potentiometer *potentiometer) :
		DelayedLevelSetter(timeInterval, taskManager), potentiometer(
				potentiometer) {
}

inline float DelayedPotentiometerActuator::readLevel() {
	return potentiometer->getLevel();
}

inline void DelayedPotentiometerActuator::writeLevel(float level) {
	potentiometer->setLevel(level);
}

#endif
