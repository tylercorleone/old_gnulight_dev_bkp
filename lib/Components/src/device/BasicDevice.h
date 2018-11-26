#ifndef BASICDEVICE_H
#define BASICDEVICE_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#include "../common/components_commons.h"
#include "device/State.h"

class BasicDevice: public TaskManager , public Named {
public:
	BasicDevice(AbstractState *fallbackState = nullptr);
	BasicDevice(const char *systemName, AbstractState *fallbackState = nullptr);
	void enterState(AbstractState &state);
	void enterState(AbstractState &state, const Event &event);
	void receiveEvent(const Event &event);
private:
	void enterFallbackState();
	void enterFallbackState(const Event &event);
	AbstractState *currentState;
	AbstractState *fallbackState;
};

inline BasicDevice::BasicDevice(AbstractState *fallbackState) :
		currentState(nullptr), fallbackState(fallbackState) {
}

inline BasicDevice::BasicDevice(const char *systemName,
		AbstractState *fallbackState) :
		Named(systemName), currentState(nullptr), fallbackState(fallbackState) {
}

#define debugIfStateHasName debugIfOtherNamed

inline void BasicDevice::enterState(AbstractState &state) {
	if (currentState != nullptr) {
		debugIfStateHasName(currentState, "onExitState");
		currentState->onExitState();
	}

	debugIfStateHasName(&state, "onEnterState");

	if (state.onEnterState()) {
		currentState = &state;
	} else {
		enterFallbackState();
	}
}

inline void BasicDevice::enterState(AbstractState &state, const Event &event) {
	if (currentState != nullptr) {
		debugIfStateHasName(currentState, "onExitState");
		currentState->onExitState();
	}

	if (state.canHandleEvent(event)) {
		debugIfStateHasName(&state, "onEnterState");
		if (state.onEnterStateWithGenericEvent(event)) {
			currentState = &state;
		} else {
			enterFallbackState(event);
		}
	} else {
		debugIfStateHasName(&state, "can't handle evt");
		enterFallbackState(event);
	}
}

inline void BasicDevice::receiveEvent(const Event &event) {
	if (currentState == nullptr) {
		debugIfNamed("not in a valid state");
		return;
	}

	if (currentState->canHandleEvent(event)) {
		debugIfStateHasName(currentState, "handleEvent");
		if (!currentState->handleGenericEvent(event)) {
			debugIfStateHasName(currentState, "onExitState");
			currentState->onExitState();
			enterFallbackState();
		}
	} else {
		debugIfStateHasName(currentState, "can't handle evt");
		debugIfStateHasName(currentState, "onExitState");
		currentState->onExitState();
		enterFallbackState(event);
	}
}

inline void BasicDevice::enterFallbackState() {
	if (fallbackState != nullptr) {
		debugIfStateHasName(fallbackState, "onEnterState");
		fallbackState->onEnterState();
		currentState = fallbackState;
	} else {
		currentState = nullptr;
		debugIfNamed("hanged up");
	}
}

inline void BasicDevice::enterFallbackState(const Event &event) {
	if (fallbackState != nullptr) {
		debugIfStateHasName(fallbackState, "onEnterState");
		if (!(fallbackState->canHandleEvent(event)
				&& fallbackState->onEnterStateWithGenericEvent(event))) {
			fallbackState->onEnterState();
			currentState = fallbackState;
		}
	} else {
		currentState = nullptr;
		debugIfNamed("hanged up");
	}
}

#undef debugIfStateHasName

#endif
