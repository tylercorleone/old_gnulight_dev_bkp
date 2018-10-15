#include "AdvancedLightDriver.h"
#include "Gnulight.h"

AdvancedLightDriver::AdvancedLightDriver(uint8_t temperatureSensingPin,
		Gnulight* gnulight) :
		temperatureSensingPin(temperatureSensingPin), HostSystemAware(gnulight) {
	trace("Inst. ALD");
	pinMode(temperatureSensingPin, INPUT);
}

void AdvancedLightDriver::setPotentiometerLevel(float level) {
	setPotentiometerLevel(level, 0);
}

void AdvancedLightDriver::setPotentiometerLevel(float level,
		uint32_t transitionDurationMs) {
	debug("ALD::setPotentiometerLevel(" + level + ", " + transitionDurationMs + ")");
	potentiometerActuator.setPotentiometerLevel(level, transitionDurationMs, false);
}

void AdvancedLightDriver::_setPotentiometerLevel(float level) {
	potentiometerLevel = level;
	if (lightnessSimulationEnabled) {
		targetCurrentLevel = convertLightnessIntoLuminance(level);
	} else {
		targetCurrentLevel = level;
	}
	LightDriver::setPotentiometerLevel(
			min(targetCurrentLevel, currentUpperLimit));
}

/**
 * limit [0, 1]
 */
void AdvancedLightDriver::setCurrentUpperLimit(float limit,
		uint32_t transitionDurationMs) {
	debug("ALD::setCurrentUpperLimit(" + limit + ", " + transitionDurationMs + ")");
	currentUpperLimit = constrain(limit, 0.0f, 1.0f);
	float currentLevel = LightDriver::getPotentiometerLevel();
	if (currentLevel > currentUpperLimit) {
		potentiometerActuator.setPotentiometerLevel(currentUpperLimit,
				transitionDurationMs, true);
	} else if (currentLevel != currentUpperLimit
			&& currentLevel < targetCurrentLevel) {
		potentiometerActuator.setPotentiometerLevel(
				min(targetCurrentLevel, currentUpperLimit),
				transitionDurationMs, true);
	}
}

float AdvancedLightDriver::getCurrentUpperLimit() {
	return currentUpperLimit;
}

bool AdvancedLightDriver::getLightnessSimulationEnabled() {
	return lightnessSimulationEnabled;
}

void AdvancedLightDriver::setLightnessSimulationEnabled(bool isEnabled) {
	lightnessSimulationEnabled = isEnabled;
}

float AdvancedLightDriver::getPotentiometerLevel() {
	return potentiometerLevel;
}

void AdvancedLightDriver::setMainLevel(MainLightLevel level,
		uint32_t transitionDurationMs) {
	currentMainLevelIndex = level;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]],
			transitionDurationMs);
}

float AdvancedLightDriver::getCurrentMainLevel() {
	return mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]];
}

void AdvancedLightDriver::setNextMainLevel(uint32_t transitionDurationMs) {
	currentMainLevelIndex = (currentMainLevelIndex + 1) % MAIN_LEVELS_NUM;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]],
			transitionDurationMs);
}
void AdvancedLightDriver::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1)
					% SUBLEVELS_NUM;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]],
			transitionDurationMs);
}

float AdvancedLightDriver::convertLightnessIntoLuminance(float lightness) {
	/*
	 lightness = the normalized L value of L*a*b* color space.
	 luminance = the relative emitted luminance (Y)
	 */
	if (lightness < 0.08f) {
		return 0.12842f * ((lightness + 0.16f) / 1.16f - 0.04f / 0.29f);
	} else {
		return pow((lightness + 0.16f) / 1.16f, 3);
	}
}

float AdvancedLightDriver::getEmitterTemperature() {
	return ((analogRead(temperatureSensingPin)
			+ analogRead(temperatureSensingPin)) / 2.0f) / 1023.0 * 5.0 * 100.0
			- 50.0;
}
