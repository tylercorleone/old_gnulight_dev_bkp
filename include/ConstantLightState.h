#ifndef CONSTANTLIGHTSTATE_H
#define CONSTANTLIGHTSTATE_H

#include <HostSystemAware.h>
#include <State.h>
#include "defines.h"

class Gnulight;

#define CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS 300UL

class ConstantLightState: public State, public HostSystemAware<Gnulight> {
public:
	ConstantLightState(Gnulight* gnulight) :
		HostSystemAware(gnulight) {
	}
protected:
	bool onEnterState(const Event &event) override;
	bool receiveEvent(const Event &event) override;
};

#endif
