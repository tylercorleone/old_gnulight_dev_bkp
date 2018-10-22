#ifndef STROBE_MODE_H
#define STROBE_MODE_H

#include "defines.h"
#include "GnulightMode.h"
#include "FunctionsSequenceTask.h"

class AdvancedLightDriver;

#define STROBE_TYPES_COUNT 5

#define ON_OFF_STROBE_PERIOD_MS 500UL
#define BEACON_STROBE_PERIOD_MS 4000UL
#define BEACON_STROBE_DUTY_CYCLE 0.01 // percent
#define DISCO_STROBE_PERIOD_MS 80UL
#define DISCO_STROBE_DUTY_CYCLE 0.2 // percent
#define LEVEL_REFRESH_INTERVAL_MS 30UL

#define PERIODICAL_SEQUENCE_STROBES_PERIOD_MS 2000UL

enum StrobeTypes {
	SINUSOIDAL_STROBE = 0, LINEAR_STROBE = 1, ON_OFF_STROBE = 2, BEACON_STROBE = 3, DISCO_STROBE = 4
};

class StrobeMode: public GnulightMode {
public:
	StrobeMode(Gnulight*, const char* modeName);
	bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode(ButtonInteraction* interaction);
	void onExitMode();
	static uint32_t switchLightStatus(StrobeMode* _this);
	static float sinWave(uint32_t millis, uint32_t periodMs);
	static float triangularWave(uint32_t millis, uint32_t periodMs);
	FunctionsSequenceTask* pToggleLightStatusTask;
	StrobeTypes currentStrobeType = SINUSOIDAL_STROBE;
	float varName;
	uint32_t periodMultiplierX1000 = 1000UL;
};

#endif
