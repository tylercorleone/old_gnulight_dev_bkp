#ifndef STATE_H
#define STATE_H

#include "Event.h"
#include "Named.h"

class State : public Named {
	friend class System;
protected:
	using Named::Named;
	virtual bool onEnterState() {return false;}
	virtual bool onEnterState(const Event &event) {return false;}
	virtual void onExitState() {}
	virtual bool receiveEvent(const Event &event) {return false;}
	virtual ~State() {};
};

#endif
