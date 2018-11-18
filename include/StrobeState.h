#ifndef STROBESTATE_H
#define STROBESTATE_H

#include <HostSystemAware.h>
#include <State.h>
#include "FunctionsSequenceTask.h"

class Gnulight;

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

class StrobeState: public State, public HostSystemAware<Gnulight> {
public:
	StrobeState(Gnulight* gnulight) :
		HostSystemAware(gnulight) {
	}
protected:
	bool onEnterState(const Event &event) override;
	void onExitState() override;
	bool receiveEvent(const Event &event) override;
	static uint32_t switchLightStatus(StrobeState *_this);
	static float sinWave(uint32_t millis, uint32_t periodMs);
	static float triangularWave(uint32_t millis, uint32_t periodMs);
	FunctionsSequenceTask& toggleLightStatusTask = SequenceTaskBuilder::begin(
			StrobeState::switchLightStatus, this).thenRepeat();
	StrobeTypes currentStrobeType = SINUSOIDAL_STROBE;
	float varName = 0.0;
	uint32_t periodMultiplierX1000 = 1000UL;
};

#endif