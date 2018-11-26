#ifndef CONSTANTLIGHTSTATE_H
#define CONSTANTLIGHTSTATE_H

#include "gnulight_config.h"

#include <Components.h>

#define MAIN_LEVEL_TRANSITION_DURATION_MS 300UL

class Gnulight;

class ConstantLightState: public State<ButtonEvent> {
public:
	ConstantLightState(Gnulight *gnulight);
protected:
	bool onEnterState(const ButtonEvent &event) override;
	bool handleEvent(const ButtonEvent &event) override;
	Gnulight *gnulight;
};

#endif
