#ifndef POWEROFFSTATE_H
#define POWEROFFSTATE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

class PowerOffState: public State<ButtonEvent> {
public:
	PowerOffState(Gnulight *gnulight);
protected:
	bool onEnterState() override;
	void onExitState() override;
	bool handleEvent(const ButtonEvent &event) override;
	Gnulight *gnulight;
};

#endif
