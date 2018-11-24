#ifndef CONSTANTLIGHTSTATE_H
#define CONSTANTLIGHTSTATE_H

#include "gnulight_config.h"

#include <State.h>

#define MAIN_LEVEL_TRANSITION_DURATION_MS 300UL

class Gnulight;

class ConstantLightState: public State {
public:
	ConstantLightState(Gnulight *gnulight);
protected:
	bool onEnterState(const Event &event) override;
	bool receiveEvent(const Event &event) override;
	Gnulight *gnulight;
};

#endif
