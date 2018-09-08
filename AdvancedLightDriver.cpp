#include "AdvancedLightDriver.h"

#include "Gnulight.h"

AdvancedLightDriver::AdvancedLightDriver(uint8_t temperatureSensingPin,
		LithiumBattery* battery) :
		temperatureSensingPin(temperatureSensingPin), battery(battery) {
	trace("Inst. ALD");
	pinMode(temperatureSensingPin, INPUT);
}

void AdvancedLightDriver::setPotentiometerLevel(float level) {
	debug("ALD::setPotentiometerLevel " + level);
	potentiometerLevel = constrain(level, 0.0f, 1.0f);
	if (lightnessSimulationEnabled) {
		targetCurrentLevel = convertLightnessIntoLuminance(potentiometerLevel);
	} else {
		targetCurrentLevel = potentiometerLevel;
	}
	LightDriver::setPotentiometerLevel(min(targetCurrentLevel, maxRelativeCurrent));
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

void AdvancedLightDriver::setMainLevel(MainLightLevel level) {
	currentMainLevelIndex = level;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]);
}

float AdvancedLightDriver::getCurrentMainLevel() {
	return mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]];
}

void AdvancedLightDriver::setNextMainLevel() {
	currentMainLevelIndex = (currentMainLevelIndex + 1) % MAIN_LEVELS_NUM;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]);
}
void AdvancedLightDriver::setNextSubLevel() {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1)
					% SUBLEVELS_NUM;
	setPotentiometerLevel(
			mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]);
}

float AdvancedLightDriver::convertLightnessIntoLuminance(float lightness) {
	/*
	 lightness (the L value of L*a*b* color space), in this case [0, 1]
	 luminance (Y, [0, 1]
	 */
	if (lightness < 0.08f) {
		return 0.12842f * ((lightness + 0.16f) / 1.16f - 0.04f / 0.29f);
	} else {
		return pow((lightness + 0.16f) / 1.16f, 3);
	}
}

float AdvancedLightDriver::getTemperature() {
	return ((analogRead(temperatureSensingPin) + analogRead(temperatureSensingPin)) / 2.0f) / 1023.0 * 5.0 * 100.0 - 50.0;
}
