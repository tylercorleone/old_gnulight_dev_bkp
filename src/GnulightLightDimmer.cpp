#include "../include/GnulightLightDimmer.h"

GnulightLightDimmer::GnulightLightDimmer(Potentiometer &brightnessPotentiometer,
		TaskManager &taskManager) :
		LightDimmer(brightnessPotentiometer) {
	setName("lightDrv");

	gradualLevelSetter = new GradualPotentiometerActuator(
	DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, *this);
}

void GnulightLightDimmer::setLevel(float level, uint32_t transitionDurationMs) {
	traceIfNamed("setLevel(%f, %u)", level, transitionDurationMs);

	gradualLevelSetter->setLevel(level, transitionDurationMs);
}

LightLevelIndex GnulightLightDimmer::getCurrentMainLevel() {
	return currentMainLevelIndex;
}

#define MAIN_LEVEL mainLevels[currentMainLevelIndex][currentSubLevelsIndexes[currentMainLevelIndex]]

float GnulightLightDimmer::setMainLevel(LightLevelIndex levelIndex,
		uint32_t transitionDurationMs) {
	currentMainLevelIndex = levelIndex;
	setLevel(MAIN_LEVEL, transitionDurationMs);
	return MAIN_LEVEL;
}

#undef MAIN_LEVEL

float GnulightLightDimmer::setNextMainLevel(uint32_t transitionDurationMs) {
	return setMainLevel((currentMainLevelIndex + 1) % MAIN_LEVELS_NUM,
			transitionDurationMs);

}

float GnulightLightDimmer::setNextSubLevel(uint32_t transitionDurationMs) {
	currentSubLevelsIndexes[currentMainLevelIndex] =
			(currentSubLevelsIndexes[currentMainLevelIndex] + 1) % SUBLEVELS_NUM;
	return setMainLevel(currentMainLevelIndex, transitionDurationMs);
}
