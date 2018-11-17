#ifndef LIGHTDRIVER_H
#define LIGHTDRIVER_H

#include <stdint.h>

#include <LightDimmer.h>
#include <PotentiometerActuator.h>
#include "system/HostSystemAware.h"
#include "defines.h"
#include "Dimmable.h"
#include "LedCurrentPotentiometer.h"

#define ACTUATORS_INTERVAL_MS MsToTaskTime(30)

class Gnulight;

enum MainLightLevel {
	MIN, MED, MAX
};

class LightDriver: public LightDimmer, public HostSystemAware<Gnulight> {
public:
	LightDriver(Gnulight* gnulight, uint8_t temperatureSensingPin);
	void setup();
	void setLevel(float level) override;
	void setLevel(float level, uint32_t transitionDurationMs);
	MainLightLevel getCurrentMainLevel();
	float setMainLevel(MainLightLevel, uint32_t transitionDurationMs = 0);
	float setNextMainLevel(uint32_t transitionDurationMs = 0);
	float setNextSubLevel(uint32_t transitionDurationMs = 0);
	float getEmitterTemperature();
private:
	friend class LightMonitor;
	float getCurrentLevel();
	void setCurrentLevel(float level);
	float getCurrentUpperLimit();
	void setCurrentUpperLimit(float limit, uint32_t transitionDurationMs = 0);

	const static uint8_t MAIN_LEVELS_NUM = 3;
	const static uint8_t SUBLEVELS_NUM = 2;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { {
	MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f }, { 0.25f, 0.5f }, { 0.75f, 1.0f } };
	MainLightLevel currentMainLevel = MainLightLevel::MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };

	LedCurrentPotentiometer currentPotentiometer;
	uint8_t temperatureSensingPin;
	PotentiometerActuator lightLevelActuator { ACTUATORS_INTERVAL_MS,
			(TaskManager*) pHostSystem, this };
	PotentiometerActuator currentActuator { ACTUATORS_INTERVAL_MS,
			(TaskManager*) pHostSystem, &currentPotentiometer };

	float currentUpperLimit = 1.0f;
	float wantedCurrentLevel = 0.0f;
};

#endif
