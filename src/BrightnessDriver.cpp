#include "BrightnessDriver.h"

BrightnessDriver::BrightnessDriver(TaskManager &taskManager) {
	setName("brightDriver");

	gradualMaxCurrentLevelSetter = new GradualCappablePotentiometerActuator(
			DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, *this);
}

void BrightnessDriver::updateLevelMaxLimit() {
	float limit = min(tempCausedLimit, battCausedLimit);

	gradualMaxCurrentLevelSetter->setLevelMaxLimit(limit,
			MsToTaskTime(LEVEL_MAX_LIMIT_TRANSITION_MS));
}

void BrightnessDriver::setBatteryCausedLimit(float limit) {
	battCausedLimit = limit;
	updateLevelMaxLimit();
}

void BrightnessDriver::setTemperatureCausedLimit(float limit) {
	tempCausedLimit = limit;
	updateLevelMaxLimit();
}
