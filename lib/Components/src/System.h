#ifndef SYSTEM_H
#define SYSTEM_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#include "Event.h"
#include "State.h"

class System: public TaskManager {
public:
	System(State *failbackState);
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

inline void System::enterState(State &state) {
	if (currentState != nullptr) {
		currentState->onExitState();
	}
	currentState = &state;
	if (!state.onEnterState()) {
		reachFailbackState();
	}
}

inline void System::enterState(State &state, const Event &event) {
	if (currentState != nullptr) {
		currentState->onExitState();
	}
	currentState = &state;
	if (!state.onEnterState(event)) {
		reachFailbackState();
	}
}

inline void System::receiveEvent(const Event &event) {
	if (!currentState->receiveEvent(event)) {
		reachFailbackState();
	}
}

inline void System::reachFailbackState() {
	if (currentState != nullptr) {
		currentState->onExitState();
	}
	currentState = failbackState;
	failbackState->onEnterState();
}

#endif
