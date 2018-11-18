#ifndef POWEROFFSTATE_H
#define POWEROFFSTATE_H

#include <Event.h>
#include <State.h>
#include <HostSystemAware.h>

class Gnulight;

class PowerOffState: public State, public HostSystemAware<Gnulight> {
public:
	PowerOffState(Gnulight *gnulight);
protected:
	bool onEnterState() override;
	void onExitState() override;
	bool receiveEvent(const Event &event) override;
};

#endif
