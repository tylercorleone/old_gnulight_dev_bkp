#ifndef DELAYEDCAPPABLEPOTENTIOMETERACTUATOR_H
#define DELAYEDCAPPABLEPOTENTIOMETERACTUATOR_H

#include "CappablePotentiometer.h"
#include "DelayedPotentiometerActuator.h"

class DelayedLevelMaxLimitSetter: public DelayedLevelSetter {
public:
	DelayedLevelMaxLimitSetter(uint32_t timeInterval, TaskManager *taskManager,
			CappablePotentiometer *cappablePotentiometer) :
			DelayedLevelSetter(timeInterval, taskManager), cappablePotentiometer(
					cappablePotentiometer) {
	}
private:
	CappablePotentiometer *cappablePotentiometer;

	float readLevel() override {
		return cappablePotentiometer->getLevelMaxLimit();
	}

	void writeLevel(float level) override {
		cappablePotentiometer->setLevelMaxLimit(level);
	}
};



class DelayedCappablePotentiometerActuator: public DelayedPotentiometerActuator {
public:
	DelayedCappablePotentiometerActuator(uint32_t timeInterval,
			TaskManager *taskManager, CappablePotentiometer *cappablePotentiometer);
	void setLevelMaxLimit(float level,
				uint32_t transitionDurationMs);
private:
	DelayedLevelMaxLimitSetter delayedLevelMaxLimitSetter { _timeInterval, taskManager,
		(CappablePotentiometer*) potentiometer };
};

inline DelayedCappablePotentiometerActuator::DelayedCappablePotentiometerActuator(
		uint32_t timeInterval, TaskManager *taskManager,
		CappablePotentiometer *cappablePotentiometer) :
		DelayedPotentiometerActuator(timeInterval, taskManager, cappablePotentiometer) {
}

inline void DelayedCappablePotentiometerActuator::setLevelMaxLimit(float level,
		uint32_t transitionDurationMs) {
	delayedLevelMaxLimitSetter.setLevel(level, transitionDurationMs);
}

#endif
