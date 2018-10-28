#include "../include/LightDriver.h"

#include "Gnulight.h"
#include <PWM.h>
#include <SPI.h>

LightDriver::LightDriver(Gnulight* gnulight, uint8_t temperatureSensingPin) :
		LightDimmer(&currentPotentiometer), HostSystemAware(gnulight), temperatureSensingPin(
				temperatureSensingPin) {
	trace("Inst. LD");
}

void LightDriver::setup() {this->toggleState();
	trace("LD::setup");
	pinMode(temperatureSensingPin, INPUT);
	currentPotentiometer.setup();
}

void LightDriver::setLevel(float level) {
	LightDimmer::setLevel(level);
}

void LightDriver::setLevel(float level, uint32_t transitionDurationMs) {
	debug("LD::setPotentiometerLevel(" + level + ", " + transitionDurationMs + ")");
	lightLevelActuator.setLevel(constrain(level, 0.0f, 1.0f),
			transitionDurationMs);
}

float LightDriver::getCurrentLevel() {
	return currentPotentiometer.getLevel();
}

void LightDriver::setCurrentLevel(float level) {
	wantedCurrentLevel = level;
	currentPotentiometer.setLevel(min(currentUpperLimit, level));
}

float LightDriver::getCurrentUpperLimit() {
	return currentUpperLimit;
}

void LightDriver::setCurrentUpperLimit(float limit,
		uint32_t transitionDurationMs) {
	debug("LD::setCurrentUpperLimit(" + currentUpperLimit + ", " + transitionDurationMs + ")");

	currentUpperLimit = constrain(limit, 0.0f, 1.0f);

	float currentLevel = currentPotentiometer.getLevel();
	if (currentLevel > currentUpperLimit) {
		currentActuator.setLevel(currentUpperLimit, transitionDurationMs);
	} else if (currentLevel != currentUpperLimit
			&& currentLevel < wantedCurrentLevel) {
		currentActuator.setLevel(min(wantedCurrentLevel, currentUpperLimit),
				transitionDurationMs);
	}
}

float LightDriver::setMainLevel(MainLightLevel level,
		uint32_t transitionDurationMs) {
	currentMainLevel = level;
	float resultingPotentiometerLevel =
			mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]];
	setLevel(resultingPotentiometerLevel, transitionDurationMs);
	return resultingPotentiometerLevel;
}

MainLightLevel LightDriver::getCurrentMainLevel() {
	return currentMainLevel;
}

float LightDriver::setNextMainLevel(uint32_t transitionDurationMs) {
	currentMainLevel = (currentMainLevel + 1) % MAIN_LEVELS_NUM;
	float resultingPotentiometerLevel =
			mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]];
	setLevel(resultingPotentiometerLevel, transitionDurationMs);
	return resultingPotentiometerLevel;
}

float LightDriver::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevel] =
			(currentSubLevelsIndexes[currentMainLevel] + 1) % SUBLEVELS_NUM;
	float resultingPotentiometerLevel =
			mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]];
	setLevel(resultingPotentiometerLevel, transitionDurationMs);
	return resultingPotentiometerLevel;
}

float LightDriver::getEmitterTemperature() {
	return ((analogRead(temperatureSensingPin)
			+ analogRead(temperatureSensingPin)) / 2.0f) / 1023.0 * 5.0 * 100.0
			- 50.0;
}
