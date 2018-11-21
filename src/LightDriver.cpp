#include "LightDriver.h"

#include "Gnulight.h"
#include <PWM.h>
#include <SPI.h>

LightDriver::LightDriver(Gnulight *gnulight, uint8_t temperatureSensingPin) :
		LightDimmer(&currentPotentiometer), HostSystemAware(gnulight), temperatureSensingPin(
				temperatureSensingPin) {
	setInstanceName("lghtDrv");
	currentPotentiometer.setInstanceName("currPot");
}

void LightDriver::setup() {
	debugNamedInstance("setup");

	pinMode(temperatureSensingPin, INPUT);
	currentPotentiometer.setup();
}

void LightDriver::setLevel(float level, uint32_t transitionDurationMs) {
	traceNamedInstance("setLevel(%f, %u)", level, transitionDurationMs);

	lightLevelActuator.setLevel(_constrain(level, 0.0f, 1.0f),
			transitionDurationMs);
}

//float LightDriver::getCurrentLevel() {
//	return currentPotentiometer.getLevel();
//}

//void LightDriver::setCurrentLevel(float level) {
//	traceNamedInstance("setCurrentLevel(%f)", level);
//
//	wantedCurrentLevel = level;
//	currentPotentiometer.setLevel(min(currentUpperLimit, level));
//}

//float LightDriver::getCurrentUpperLimit() {
//	return currentUpperLimit;
//}
//
//void LightDriver::setCurrentUpperLimit(float limit,
//		uint32_t transitionDurationMs) {
//	traceNamedInstance("setCurrentUpperLimit(%f, %u)", currentUpperLimit, transitionDurationMs);
//
//	currentUpperLimit = constrain(limit, 0.0f, 1.0f);
//	float currentLevel = currentPotentiometer.getLevel();
//
//	if (currentUpperLimit < currentLevel) {
//
//		/*
//		 * we have to reduce current
//		 */
//		currentActuator.setLevel(currentUpperLimit, transitionDurationMs);
//	} else if (currentUpperLimit > currentLevel
//			&& currentLevel < wantedCurrentLevel) {
//
//		/*
//		 * we can increase current
//		 */
//		currentActuator.setLevel(min(currentUpperLimit, wantedCurrentLevel),
//				transitionDurationMs);
//	}
//}

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

	float resultingPotentiometerLevel =
			mainLevels[currentMainLevel][currentSubLevelsIndexes[currentMainLevel]];

	setLevel(resultingPotentiometerLevel, transitionDurationMs);

	return resultingPotentiometerLevel;
}

float LightDriver::getEmitterTemperature() {
	analogRead(temperatureSensingPin);
	return analogRead(temperatureSensingPin) * 5.0f * 100.0f / 1023 - 50;
}
