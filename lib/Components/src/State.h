#ifndef STATE_H
#define STATE_H

#include "Event.h"

class State {
	friend class System;
protected:
	virtual bool onEnterState() {return false;}
	virtual bool onEnterState(const Event &event) {return false;}
	virtual void onExitState() {}
	virtual bool receiveEvent(const Event &event) {return false;}
	virtual ~State() {};
};

#endif
