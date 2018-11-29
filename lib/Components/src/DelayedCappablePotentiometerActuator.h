#ifndef DELAYEDCAPPABLEPOTENTIOMETERACTUATOR_H
#define DELAYEDCAPPABLEPOTENTIOMETERACTUATOR_H

#include "CappablePotentiometer.h"
#include "DelayedPotentiometerActuator.h"

class DelayedLevelMaxLimitSetter: public DelayedLevelSetter {
public:
	DelayedLevelMaxLimitSetter(uint32_t timeInterval, TaskManager &taskManager,
			CappablePotentiometer &cappablePotentiometer);
private:
	CappablePotentiometer &cappablePotentiometer;
	float readLevel() override;
	void writeLevel(float level);
};

class DelayedCappablePotentiometerActuator: public DelayedPotentiometerActuator {
public:
	DelayedCappablePotentiometerActuator(uint32_t timeInterval,
			TaskManager &taskManager,
			CappablePotentiometer &cappablePotentiometer);
	void setLevelMaxLimit(float level, uint32_t transitionDurationMs);
private:
	DelayedLevelMaxLimitSetter delayedLevelMaxLimitSetter { _timeInterval,
			taskManager, (CappablePotentiometer&) potentiometer };
};

inline DelayedLevelMaxLimitSetter::DelayedLevelMaxLimitSetter(
		uint32_t timeInterval, TaskManager &taskManager,
		CappablePotentiometer &cappablePotentiometer) :
		DelayedLevelSetter(timeInterval, taskManager), cappablePotentiometer(
				cappablePotentiometer) {
}

inline float DelayedLevelMaxLimitSetter::readLevel() {
	return cappablePotentiometer.getLevelMaxLimit();
}

inline void DelayedLevelMaxLimitSetter::writeLevel(float level) {
	cappablePotentiometer.setLevelMaxLimit(level);
}

inline DelayedCappablePotentiometerActuator::DelayedCappablePotentiometerActuator(
		uint32_t timeInterval, TaskManager &taskManager,
		CappablePotentiometer &cappablePotentiometer) :
		DelayedPotentiometerActuator(timeInterval, taskManager,
				cappablePotentiometer) {
}

inline void DelayedCappablePotentiometerActuator::setLevelMaxLimit(float level,
		uint32_t transitionDurationMs) {
	delayedLevelMaxLimitSetter.setLevel(level, transitionDurationMs);
}

#endif
