#ifndef STATE_H
#define STATE_H

#include "event/Event.h"
#include "event/EventHandler.h"
#include "common/Named.h"

class AbstractState : public Named {
	friend class BasicDevice;
	template<typename T> friend class State;
protected:
	virtual bool onEnterState() {return false;}
	virtual void onExitState() {}
	virtual ~AbstractState() {};
protected:
	AbstractState(const char *stateName = nullptr) : Named(stateName) {}
	virtual bool canHandleEvent(const Event &event) {return false;}
	virtual bool handleGenericEvent(const Event &event) {return false;}
	virtual bool onEnterStateWithGenericEvent(const Event &event) {return false;}
};

template<typename T> class State : public AbstractState, public EventHandler<T> {
	friend class BasicDevice;
protected:
	State(const char *stateName = nullptr) : AbstractState(stateName) {}
	virtual bool onEnterState(const T &event) {return false;}
	virtual bool handleEvent(const T &event) override {return false;}
	virtual ~State() {};
protected:

	bool canHandleEvent(const Event &event) {
		return event.getEventTypeUUID() == T::eventTypeUUID();
	}

	bool handleGenericEvent(const Event &event) override {
		return handleEvent(static_cast<const T&>(event));
	}

	bool onEnterStateWithGenericEvent(const Event &event) override {
		return onEnterState(static_cast<const T&>(event));
	}
};

#endif
