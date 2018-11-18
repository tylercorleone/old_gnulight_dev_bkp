#ifndef TimedLinearPotentiometerActuator_h
#define TimedLinearPotentiometerActuator_h

#include <stdint.h>

#include "Potentiometer.h"
#include "TimedLinearLevelSetter.h"

class TaskManager;

class PotentiometerActuator: public TimedLinearLevelSetter {
public:
	PotentiometerActuator(uint32_t timeInterval,
			TaskManager* taskManager, Potentiometer* potentiometer);
private:
	float readLevel() override;
	void writeLevel(float level) override;
	Potentiometer* potentiometer;
};

inline PotentiometerActuator::PotentiometerActuator(
		uint32_t timeInterval, TaskManager* taskManager,
		Potentiometer* potentiometer) :
		TimedLinearLevelSetter(timeInterval, taskManager), potentiometer(
				potentiometer) {
}

inline float PotentiometerActuator::readLevel() {
	return potentiometer->getLevel();
}

inline void PotentiometerActuator::writeLevel(float level) {
	potentiometer->setLevel(level);
}

#endif
