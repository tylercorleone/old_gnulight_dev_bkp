#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include "Components.h"
#include "Named.h"
#include "State.h"

class System: public TaskManager , public Named {
public:
	System(State *failbackState = 0);
	System(const char *systemName, State *failbackState = 0);
	void enterState(State &state);
	void enterState(State &state, const Event &event);
	void receiveEvent(const Event &event);
private:
	void reachFailbackState();
	State *currentState = nullptr;
	State *failbackState = nullptr;
};

inline System::System(State *failbackState) :
		failbackState(failbackState) {
}

inline System::System(const char *systemName, State *failbackState) :
		Named(systemName), failbackState(failbackState) {
}

inline void System::enterState(State &state) {
	if (currentState != nullptr) {
		debugIfOtherNamed(currentState, "onExitState");
		currentState->onExitState();
	}

	debugIfOtherNamed(&state, "onEnterState");

	currentState = &state;
	if (!state.onEnterState()) {
		reachFailbackState();
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
		reachFailbackState();
	}
}

inline void System::receiveEvent(const Event &event) {
	if (currentState == nullptr) {
		debugIfNamed("not in a valid state");
		return;
	}

	traceIfOtherNamed(currentState, "receiveEvent");
	if (!currentState->receiveEvent(event)) {
		reachFailbackState();
	}
}

inline void System::reachFailbackState() {
	if (currentState != nullptr) {
		debugIfOtherNamed(currentState, "onExitState");
		currentState->onExitState();
	}

	if (failbackState != nullptr) {
		debugIfOtherNamed(failbackState, "onEnterState");
		currentState = failbackState;
		failbackState->onEnterState();
	} else {
		currentState = nullptr;
		debugIfNamed("hanged up");
	}
}

#endif
