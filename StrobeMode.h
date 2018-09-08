#ifndef STROBE_MODE_H
#define STROBE_MODE_H

#include "defines.h"
#include "GnulightMode.h"
#include "FunctionsSequenceTask.h"

class AdvancedLightDriver;

#define STROBE_TYPES_COUNT 6

#define SLOW_STROBE_INTERVAL_MS 500UL
#define FAST_STROBE_INTERVAL_MS 250UL
#define BEACON_STROBE_INTERVAL_MS 4000UL
#define BEACON_STROBE_DUTY_CYCLE 0.01 // percent
#define DISCO_STROBE_INTERVAL_MS 80UL
#define DISCO_STROBE_DUTY_CYCLE 0.2 // percent
#define SINUSOIDAL_STROBE_INTERVAL_MS 30UL
#define LINEAR_STROBE_INTERVAL_MS 30UL

enum StrobeTypes {
	SLOW_STROBE = 0, FAST_STROBE = 1, BEACON_STROBE = 2, DISCO_STROBE = 3, SINUSOIDAL_STROBE = 4, LINEAR_STROBE = 5
};

class StrobeMode: public GnulightMode {
public:
	StrobeMode(const char*, Gnulight*);
	bool interpretUserInteraction(ButtonInteraction& interaction);
protected:
	bool onEnterMode(ButtonInteraction* interaction);
	void onExitMode();
	static uint32_t switchLightStatus(StrobeMode* _this);
	FunctionsSequenceTask* pToggleLightStatusTask;
	StrobeTypes currentStrobeType = SLOW_STROBE;
};

#endif
