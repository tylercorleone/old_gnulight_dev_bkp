#include "LightDriver.h"
#include <PWM.h>
#include <SPI.h>

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

MainLightLevel LightDriver::getMainLevel() {
	return currentMainLevel;
}

float LightDriver::setMainLevel(MainLightLevel level,
		uint32_t transitionDurationMs) {
	currentMainLevel = level;

	return _setMainLevel(transitionDurationMs);
}

float LightDriver::setNextMainLevel(uint32_t transitionDurationMs) {
	currentMainLevel = (currentMainLevel + 1) % MAIN_LEVELS_NUM;

	return _setMainLevel(transitionDurationMs);
}

float LightDriver::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevel] =
			(currentSubLevelsIndexes[currentMainLevel] + 1) % SUBLEVELS_NUM;

	return _setMainLevel(transitionDurationMs);
}

float LightDriver::_setMainLevel(uint32_t transitionDurationMs) {
	setLevel(
			mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]],
			transitionDurationMs);

	return mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]];
}

#define V_OUT (analogRead(temperatureSensingPin) * 5.0f / 1023.0f)
#define V_0 0.5
#define T_C 0.01

float LightDriver::getEmitterTemperature() {
	analogRead(temperatureSensingPin);
	// it is a MCP9700A-E/TO
	return (V_OUT - V_0) / T_C;
}
