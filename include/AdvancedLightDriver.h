#ifndef ADVANCEDLIGHTDRIVER_H
#define ADVANCEDLIGHTDRIVER_H

#include "LightDriver.h"
#include "system/HostSystemAware.h"
#include "LightMonitor.h"
#include "PotentiometerActuator.h"

class Gnulight;

enum MainLightLevel {
	MIN, MED, MAX
};

class AdvancedLightDriver : public LightDriver, public HostSystemAware<Gnulight>, public Dimmable<float> {
	friend class LightMonitor;
public:
	AdvancedLightDriver(Gnulight* gnulight, uint8_t temperatureSensingPin);
	void setup() override;
	void setPotentiometerLevel(float level, uint32_t transitionDurationMs = 0);
	float getPotentiometerLevel();
	void setCurrentUpperLimit(float limit, uint32_t transitionDurationMs = 0);
	float getCurrentUpperLimit();
	float setMainLevel(MainLightLevel, uint32_t transitionDurationMs = 0);
	MainLightLevel getCurrentMainLevel();
	float setNextMainLevel(uint32_t transitionDurationMs = 0);
	float setNextSubLevel(uint32_t transitionDurationMs = 0);
	bool getLightnessSimulationEnabled();
	void setLightnessSimulationEnabled(bool);
    float getEmitterTemperature();
	void dim(float value) override;
private:
    friend class PotentiometerActuator;
	void _setPotentiometerLevel(float level);
	float convertLightnessIntoLuminance(float lightness);
	const static uint8_t MAIN_LEVELS_NUM = 3;
	const static uint8_t SUBLEVELS_NUM = 2;
	bool lightnessSimulationEnabled = true;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { { MIN_LIGHT_CURRENT_ABOVE_ZERO, 0.02f },
			{ 0.2f, 0.5f }, { 0.75f, 1.0f } };
	MainLightLevel currentMainLevel = MainLightLevel::MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	uint8_t temperatureSensingPin;
	PotentiometerActuator potentiometerActuator {this, (TaskManager*)pHostSystem};
	LightMonitor lightMonitor {this};
	float potentiometerLevel = 0.0f;
	float currentUpperLimit = 1.0f;
	float targetCurrentLevel = 0.0f;
};

#endif
