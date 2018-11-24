#ifndef LIGHTDRIVER_H
#define LIGHTDRIVER_H

#include "gnulight_config.h"

#include <stdint.h>
#include <DelayedPotentiometerActuator.h>
#include <LightDimmer.h>
#include <HostSystemAware.h>
#include "LedCurrentPotentiometer.h"

#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.00035f
#define MAIN_LEVELS_NUM 3
#define SUBLEVELS_NUM 2

enum MainLightLevel {
	MIN, MED, MAX
};

class LightDriver: public LightDimmer {
public:
	LightDriver(TaskManager *taskManager, uint8_t temperatureSensingPin);
	void setup();
	using LightDimmer::setLevel;
	void setLevel(float level, uint32_t transitionDurationMs);
	MainLightLevel getMainLevel();
	float setMainLevel(MainLightLevel, uint32_t transitionDurationMs = 0);
	float setNextMainLevel(uint32_t transitionDurationMs = 0);
	float setNextSubLevel(uint32_t transitionDurationMs = 0);
	float getEmitterTemperature();
private:
	friend class LightMonitor;
	float _setMainLevel(uint32_t transitionDurationMs = 0);
	TaskManager *taskManager;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { {
	MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f }, { 0.25f, 0.5f }, { 0.75f, 1.0f } };
	MainLightLevel currentMainLevel = MainLightLevel::MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	uint8_t temperatureSensingPin;
	DelayedPotentiometerActuator delayedLevelSetter {
	DELAYED_LEVEL_SETTER_INTERVAL_MS, taskManager, this };
	LedCurrentPotentiometer currentPotentiometer { taskManager };
};

#endif
