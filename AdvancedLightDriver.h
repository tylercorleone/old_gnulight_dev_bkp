#ifndef ADVANCEDLIGHTDRIVER_H
#define ADVANCEDLIGHTDRIVER_H

#include "LightDriver.h"
#include "system/HostSystemAware.h"
#include "PotentiometerActuator.h"

#define TIMED_POTENTIOMETER_SETTER_INTERVAL_MS 30UL

class Gnulight;

enum MainLightLevel {
	MAIN_LIGHT_LEVEL_MIN = 0, MAIN_LIGHT_LEVEL_MED = 1, MAIN_LIGHT_LEVEL_MAX = 2
};

class AdvancedLightDriver : public LightDriver, public HostSystemAware<Gnulight> {
	friend class TemperatureMonitor;
public:
	AdvancedLightDriver(uint8_t temperatureSensingPin, Gnulight* gnulight);
	void setPotentiometerLevel(float level) override;
	void setPotentiometerLevel(float level, uint32_t transitionDurationMs);
	float getPotentiometerLevel() override;
	void setCurrentUpperLimit(float limit, uint32_t transitionDurationMs = 0);
	float getCurrentUpperLimit();
	void setMainLevel(MainLightLevel, uint32_t transitionDurationMs = 0);
	float getCurrentMainLevel();
	void setNextMainLevel(uint32_t transitionDurationMs = 0);
	void setNextSubLevel(uint32_t transitionDurationMs = 0);
	bool getLightnessSimulationEnabled();
	void setLightnessSimulationEnabled(bool);
    float getEmitterTemperature();
private:
    friend class PotentiometerActuator;
	void _setPotentiometerLevel(float level);
	float convertLightnessIntoLuminance(float lightness);
	const static uint8_t MAIN_LEVELS_NUM = 3;
	const static uint8_t SUBLEVELS_NUM = 2;
	bool lightnessSimulationEnabled = true;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { { MINIMUM_LIGHT_OUTPUT, 0.02f },
			{ 0.2f, 0.5f }, { 0.75f, 1.0f } };
	uint8_t currentMainLevelIndex = MAIN_LIGHT_LEVEL_MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	uint8_t temperatureSensingPin;
	PotentiometerActuator potentiometerActuator {this, TIMED_POTENTIOMETER_SETTER_INTERVAL_MS, (TaskManager*)pHostSystem};
	float potentiometerLevel = 0.0f;
	float currentUpperLimit = 1.0f;
	float targetCurrentLevel = 0.0f;
};

#endif
