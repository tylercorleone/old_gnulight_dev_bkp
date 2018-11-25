#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include "Components.h"
#include "State.h"
#include "HostSystemAware.h"

class System: public TaskManager , public Named {
public:
	System(State *fallbackState = nullptr);
	System(const char *systemName, State *fallbackState = nullptr);
	void enterState(State &state);
	void enterState(State &state, const Event &event);
	void receiveEvent(const Event &event);
private:
	void reachFallbackState();
	State *currentState = nullptr;
	State *fallbackState;
};

inline System::System(State *fallbackState) :
		fallbackState(fallbackState) {
}

inline System::System(const char *systemName, State *fallbackState) :
		Named(systemName), fallbackState(fallbackState) {
}

inline void System::enterState(State &state) {
	if (currentState != nullptr) {
		debugIfOtherNamed(currentState, "onExitState");
		currentState->onExitState();
	}

	debugIfOtherNamed(&state, "onEnterState");

	currentState = &state;
	if (!state.onEnterState()) {
		reachFallbackState();
	}
}

inline void System::enterState(State &state, const Event &event) {
	if (currentState != nullptr) {
		debugIfOtherNamed(currentState, "onExitState");
		currentState->onExitState();
	}

	debugIfOtherNamed(&state, "onEnterState");

	currentState = &state;
	if (!state.onEnterState(event)) {
		reachFallbackState();
	}
}

inline void System::receiveEvent(const Event &event) {
	if (currentState == nullptr) {
		debugIfNamed("not in a valid state");
		return;
	}

	traceIfOtherNamed(currentState, "receiveEvent");
	if (!currentState->receiveEvent(event)) {
		reachFallbackState();
	}
}

inline void System::reachFallbackState() {
	if (currentState != nullptr) {
		debugIfOtherNamed(currentState, "onExitState");
		currentState->onExitState();
	}

	if (fallbackState != nullptr) {
		debugIfOtherNamed(fallbackState, "onEnterState");
		currentState = fallbackState;
		fallbackState->onEnterState();
	} else {
		currentState = nullptr;
		debugIfNamed("hanged up");
	}
}

#endif
