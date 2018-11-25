#include "LightDriver.h"
#include <PWM.h>
#include <SPI.h>

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

LightDriver::LightDriver(TaskManager *taskManager,
		uint8_t temperatureSensingPin) :
		LightDimmer(&currentPotentiometer), taskManager(taskManager), temperatureSensingPin(
				temperatureSensingPin) {
	setInstanceName("lightDrv");
}

void LightDriver::setup() {
	debugIfNamed("setup");

	pinMode(temperatureSensingPin, INPUT);
	currentPotentiometer.setup();
}

void LightDriver::setLevel(float level, uint32_t transitionDurationMs) {
	traceIfNamed("setLevel(%f, %u)", level, transitionDurationMs);

	delayedLevelSetter.setLevel(level, transitionDurationMs);
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

#define V_OUT (analogRead(temperatureSensingPin) * 5.0f / 1023.0f)
#define V_0 0.5
#define T_C 0.01

float LightDriver::getEmitterTemperature() {
	analogRead(temperatureSensingPin);
	// it is a MCP9700A-E/TO
	return (V_OUT - V_0) / T_C;
}

#undef MAIN_LEVEL
