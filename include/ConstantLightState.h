#ifndef CONSTANTLIGHTSTATE_H
#define CONSTANTLIGHTSTATE_H

#include <HostSystemAware.h>
#include <State.h>

class Gnulight;

class ConstantLightState: public State, public HostSystemAware<Gnulight> {
public:
	ConstantLightState(Gnulight *gnulight);
protected:
	bool onEnterState(const Event &event) override;
	bool receiveEvent(const Event &event) override;
};

#endif
