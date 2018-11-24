#ifndef CONSTANTLIGHTSTATE_H
#define CONSTANTLIGHTSTATE_H

#include <State.h>

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
