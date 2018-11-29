#include "LightDriver.h"
#include <PWM.h>
#include <SPI.h>

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

LightDriver::LightDriver(Potentiometer &currentPotentiometer,
		TaskManager &taskManager) :
		LightDimmer(currentPotentiometer) {
	setInstanceName("lightDrv");

	delayedLevelSetter = new DelayedPotentiometerActuator(
	DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, *this);
}

void LightDriver::setup() {
	debugIfNamed("setup");

	pinMode(TEMPERATURE_SENSING_PIN, INPUT);
}

void LightDriver::setLevel(float level, uint32_t transitionDurationMs) {
	traceIfNamed("setLevel(%f, %u)", level, transitionDurationMs);

	delayedLevelSetter->setLevel(level, transitionDurationMs);
}

LightLevelIndex LightDriver::getCurrentMainLevel() {
	return currentMainLevelIndex;
}

float LightDriver::setMainLevel(LightLevelIndex levelIndex,
		uint32_t transitionDurationMs) {
	currentMainLevelIndex = levelIndex;
	setLevel(MAIN_LEVEL, transitionDurationMs);
	return MAIN_LEVEL;
}

float LightDriver::setNextMainLevel(uint32_t transitionDurationMs) {
	return setMainLevel((currentMainLevelIndex + 1) % MAIN_LEVELS_NUM,
			transitionDurationMs);

}

float LightDriver::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1) % SUBLEVELS_NUM;
	return setMainLevel(currentMainLevelIndex, transitionDurationMs);
}

#undef MAIN_LEVEL
