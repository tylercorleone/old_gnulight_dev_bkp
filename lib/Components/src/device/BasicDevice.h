#ifndef BASICDEVICE_H
#define BASICDEVICE_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#include "../common/components_commons.h"
#include "device/State.h"

// let's save some data and program space...
enum class DeviceInteraction {
	ENTER_STATE, ENTER_STATE_WITH_EVENT, RECEIVE_EVENT, ENTER_FALLBACK, ENTER_FALLBACK_WITH_EVENT
};

class BasicDevice: public TaskManager , public Named {
public:
	BasicDevice(AbstractState *fallbackState = nullptr);
	BasicDevice(const char *systemName, AbstractState *fallbackState = nullptr);
	void enterState(AbstractState &state);
	void enterState(AbstractState &state, const Event &event);
	void receiveEvent(const Event &event);
private:
	void handleInteraction(DeviceInteraction interaction, AbstractState &state, const Event *pEvent = nullptr);
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
	handleInteraction(DeviceInteraction::ENTER_STATE, state);
}

inline void BasicDevice::enterState(AbstractState &state, const Event &event) {
	handleInteraction(DeviceInteraction::ENTER_STATE_WITH_EVENT, state, &event);
}

inline void BasicDevice::receiveEvent(const Event &event) {
	handleInteraction(DeviceInteraction::RECEIVE_EVENT, *currentState, &event);
}

// ENTER_STATE, ENTER_STATE_WITH_EVENT, RECEIVE_EVENT, ENTER_FALLBACK, ENTER_FALLBACK_WITH_EVENT

/**
 * SThis is not very elegant but saves data and program space
 */
inline void BasicDevice::handleInteraction(DeviceInteraction interaction, AbstractState &state, const Event *pEvent) {
	if (interaction != DeviceInteraction::RECEIVE_EVENT && currentState != nullptr) {
		debugIfStateHasName(currentState, "onExitState");
		currentState->onExitState();
	}

	if (interaction != DeviceInteraction::ENTER_STATE && interaction != DeviceInteraction::ENTER_FALLBACK) {

		/*
		 * we have an event
		 */

		bool eventCorrectlyHandled = false;

		if (state.canHandleEvent(*pEvent)) {
			if (interaction == DeviceInteraction::RECEIVE_EVENT) {
				debugIfStateHasName(&state, "handleEvent");
				eventCorrectlyHandled = state.handleGenericEvent(*pEvent);
			} else {
				debugIfStateHasName(&state, "onEnterState");
				eventCorrectlyHandled = state.onEnterStateWithGenericEvent(*pEvent);
			}
		} else {
			debugIfStateHasName(&state, "unhandled event");
		}

		if (!eventCorrectlyHandled) {
			if (interaction != DeviceInteraction::ENTER_FALLBACK_WITH_EVENT) {
				if (fallbackState != nullptr) {

					/*
					 * let's try to enter fallbackState
					 */
					handleInteraction(DeviceInteraction::ENTER_FALLBACK_WITH_EVENT, *fallbackState, pEvent);
				} else {
					currentState = nullptr;
					debugIfNamed("hanged up");
				}
			} else {

				/*
				 * fallbackState couldn't handle the event. We don't mind!
				 */
				currentState = fallbackState;
			}
		} else {
			currentState = &state;
		}
	} else {

		/*
		 * enter state without event
		 */
		debugIfStateHasName(&state, "onEnterState");
		if (!state.onEnterState()) {
			currentState = &state;
		} else {
			if (interaction == DeviceInteraction::ENTER_STATE) {
				if (fallbackState != nullptr) {

					/*
					 * let's try to enter fallbackState
					 */
					handleInteraction(DeviceInteraction::ENTER_FALLBACK, *fallbackState);
				} else {
					currentState = nullptr;
					debugIfNamed("hanged up");
				}
			} else {

				/*
				 * Couldn't enter fallbackState. We don't mind!
				 */
				currentState = fallbackState;
			}
		}
	}
}

#undef debugIfStateHasName

#endif
