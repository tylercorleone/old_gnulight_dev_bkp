#ifndef POWEROFFSTATE_H
#define POWEROFFSTATE_H

#include "gnulight_config.h"

#include <Components.h>

class Gnulight;

class PowerOffState: public State<Event> {
public:
	PowerOffState(Gnulight *gnulight);
protected:
	bool onEnterState() override;
	bool onEnterState(const Event &event) override;
	void onExitState() override;
	bool handleEvent(const Event &event) override;
	Gnulight *gnulight;
};

#endif
