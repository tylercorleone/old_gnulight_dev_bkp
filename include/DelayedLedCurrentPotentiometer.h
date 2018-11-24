//#ifndef DELAYEDLEDCURRENTPOTENTIOMETER_H
//#define DELAYEDLEDCURRENTPOTENTIOMETER_H
//
//#include <DelayedCappablePotentiometerActuator.h>
//#include "LedCurrentPotentiometer.h"
//
//class DelayedLedCurrentPotentiometer: public LedCurrentPotentiometer {
//public:
//	DelayedLedCurrentPotentiometer(TaskManager *taskManager) {
//		delayedMaxCurrentLevelSetter = new DelayedCappablePotentiometerActuator(
//				ACTUATOR_INTERVAL_MS, taskManager, this);
//	}
//
//	void setLevelMaxLimit(float level, uint32_t transitionDurationMs = 0) {
//		traceNamedInstance("setLevelMaxLimit(%f, %u)", level, transitionDurationMs);
//		delayedMaxCurrentLevelSetter->setLevelMaxLimit(level, transitionDurationMs);
//	}
//
//protected:
//	DelayedCappablePotentiometerActuator *delayedMaxCurrentLevelSetter;
//};
//
//#endif
//
