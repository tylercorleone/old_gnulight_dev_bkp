#ifndef STROBE_MODE_H
#define STROBE_MODE_H

#include "GnulightMode.h"
#include "FunctionsSequenceTask.h"

class LightDriver;

#define STROBE_TYPES_COUNT 5

#define ON_OFF_STROBE_PERIOD_MS 500UL
#define BEACON_STROBE_PERIOD_MS 4000UL
#define BEACON_STROBE_DUTY_CYCLE 0.01
#define DISCO_STROBE_PERIOD_MS 80UL
#define DISCO_STROBE_DUTY_CYCLE 0.2
#define LEVEL_REFRESH_INTERVAL_MS 30UL

#define PERIODICAL_SEQUENCE_STROBES_PERIOD_MS 2000UL

#define MIN_POTENTIOMETER_LEVEL MIN_LIGHT_CURRENT_ABOVE_ZERO * 4.0

enum StrobeTypes {
	SINUSOIDAL_STROBE = 0,
	LINEAR_STROBE = 1,
	ON_OFF_STROBE = 2,
	BEACON_STROBE = 3,
	DISCO_STROBE = 4
};

class StrobeMode: public GnulightMode {
public:
	StrobeMode(Gnulight* gnulight, const char* modeName) :
			GnulightMode(gnulight, modeName) {
	}
	boolean interpretUserInteraction(ButtonInteraction& interaction);
protected:
	boolean onEnterMode(ButtonInteraction* interaction);
	void onExitMode();
	static uint32_t switchLightStatus(StrobeMode* _this);
	static float sinWave(uint32_t millis, uint32_t periodMs);
	static float triangularWave(uint32_t millis, uint32_t periodMs);
	FunctionsSequenceTask& toggleLightStatusTask = SequenceTaskBuilder::begin(
			StrobeMode::switchLightStatus, this).thenRepeat();
	StrobeTypes currentStrobeType = SINUSOIDAL_STROBE;
	float varName = 0.0;
	uint32_t periodMultiplierX1000 = 1000UL;
};

#endif
