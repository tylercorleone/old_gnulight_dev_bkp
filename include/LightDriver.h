#ifndef LIGHTDRIVER_H
#define LIGHTDRIVER_H

#include "gnulight_config.h"

#include <Components.h>
#include <stdint.h>
#include "LedCurrentPotentiometer.h"

#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.00035f
#define MAIN_LEVELS_NUM 3
#define SUBLEVELS_NUM 2

enum LightLevelIndex {
	MIN, MED, MAX
};

class LightDriver: public LightDimmer {
public:
	LightDriver(TaskManager *taskManager, uint8_t temperatureSensingPin);
	void setup();
	using LightDimmer::setLevel;
	void setLevel(float level, uint32_t transitionDurationMs);
	LightLevelIndex getCurrentMainLevel();
	float setMainLevel(LightLevelIndex, uint32_t transitionDurationMs = 0);
	float setNextMainLevel(uint32_t transitionDurationMs = 0);
	float setNextSubLevel(uint32_t transitionDurationMs = 0);
	float getEmitterTemperature();
private:
	friend class LightMonitor;
	TaskManager *taskManager;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { {
			MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f }, { 0.25f, 0.5f }, { 0.75f, 1.0f } };
	LightLevelIndex currentMainLevelIndex = LightLevelIndex::MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	uint8_t temperatureSensingPin;
	LedCurrentPotentiometer currentPotentiometer { taskManager };
	DelayedPotentiometerActuator delayedLevelSetter {
		DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, this };
};

#endif
