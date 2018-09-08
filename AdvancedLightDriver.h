#ifndef ADVANCEDLIGHTDRIVER_H
#define ADVANCEDLIGHTDRIVER_H

#include "LightDriver.h"
#include "Dimmable.h"

enum MainLightLevel {
	MAIN_LIGHT_LEVEL_MIN = 0, MAIN_LIGHT_LEVEL_MED = 1, MAIN_LIGHT_LEVEL_MAX = 2
};

class AdvancedLightDriver : public LightDriver, public Dimmable<float> {
	friend class LightMonitorTask;
public:
	AdvancedLightDriver(uint8_t temperatureSensingPin);
	void setPotentiometerLevel(float level) override;
	float getPotentiometerLevel() override;
	void setMainLevel(MainLightLevel);
	float getCurrentMainLevel();
	void setNextMainLevel();
	void setNextSubLevel();
	bool getLightnessSimulationEnabled();
	void setLightnessSimulationEnabled(bool);
    float getEmitterTemperature();
private:
	float convertLightnessIntoLuminance(float lightness);
	const static uint8_t MAIN_LEVELS_NUM = 3;
	const static uint8_t SUBLEVELS_NUM = 2;
	bool lightnessSimulationEnabled = true;
	const float mainLevels[MAIN_LEVELS_NUM][SUBLEVELS_NUM] = { { MINIMUM_LIGHT_OUTPUT, 0.02f },
			{ 0.2f, 0.5f }, { 0.75f, 1.0f } };
	uint8_t currentMainLevelIndex = MAIN_LIGHT_LEVEL_MAX;
	uint8_t currentSubLevelsIndexes[MAIN_LEVELS_NUM] = { 0, 0, 0 };
	uint8_t temperatureSensingPin;
	float potentiometerLevel = 0.0f;
	float targetCurrentLevel = 0.0f;
};

#endif
