#ifndef GRADUALPOTENTIOMETERACTUATOR_H
#define GRADUALPOTENTIOMETERACTUATOR_H

#include <GradualLevelSetter.h>
#include <stdint.h>

#include "Potentiometer.h"

class TaskManager;

class GradualPotentiometerActuator: public GradualLevelSetter {
public:
	GradualPotentiometerActuator(uint32_t timeInterval,
			TaskManager &taskManager, Potentiometer &potentiometer);
protected:
	float readLevel() override;
	void writeLevel(float level) override;
	Potentiometer &potentiometer;
};

inline GradualPotentiometerActuator::GradualPotentiometerActuator(
		uint32_t timeInterval, TaskManager &taskManager,
		Potentiometer &potentiometer) :
		GradualLevelSetter(timeInterval, taskManager), potentiometer(
				potentiometer) {
}

inline float GradualPotentiometerActuator::readLevel() {
	return potentiometer.getLevel();
}

inline void GradualPotentiometerActuator::writeLevel(float level) {
	potentiometer.setLevel(level);
}

#endif
