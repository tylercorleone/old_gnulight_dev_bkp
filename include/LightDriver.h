#ifndef LIGHTDRIVER_H
#define LIGHTDRIVER_H

#include <stdint.h>

#include <LightDimmer.h>
#include <PotentiometerActuator.h>
#include <HostSystemAware.h>
#include "defines.h"
#include "Dimmable.h"
#include "LedCurrentPotentiometer.h"

#define ACTUATOR_INTERVAL_MS MsToTaskTime(30)
#define MAIN_LEVELS_NUM 3
#define SUBLEVELS_NUM 2

class Gnulight;

enum MainLightLevel {
	MIN, MED, MAX
};

class LightDriver: public LightDimmer, public HostSystemAware<Gnulight> {
public:
	LightDriver(Gnulight *gnulight, uint8_t temperatureSensingPin);
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
//	float getCurrentLevel();
//	void setCurrentLevel(float level);
//	float getCurrentUpperLimit();
//	void setCurrentUpperLimit(float limit, uint32_t transitionDurationMs = 0);
	float _setMainLevel(uint32_t transitionDurationMs = 0);
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { {
	MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f }, { 0.25f, 0.5f }, { 0.75f, 1.0f } };
	MainLightLevel currentMainLevel = MainLightLevel::MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };

	LedCurrentPotentiometer currentPotentiometer {getHostSystem()};
	PotentiometerActuator lightLevelActuator { ACTUATOR_INTERVAL_MS,
			(TaskManager*) getHostSystem(), this };
//	PotentiometerActuator currentActuator { ACTUATOR_INTERVAL_MS,
//			(TaskManager*) getHostSystem(), &currentPotentiometer };
	uint8_t temperatureSensingPin;
//	float currentUpperLimit = 1.0f;
//	float wantedCurrentLevel = 0.0f;
};

#endif
