#ifndef BUTTON_H
#define BUTTON_H

#include "Components.h"
#include "Event.h"
#include "HostSystemAware.h"
#include "Named.h"
#include "System.h"

#define CONSECUTIVE_CLICKS_MAX_DELAY 600L
#define BUTTON_HOLD_BEGIN_THRESHOLD_MS 800L
#define HOLD_CYCLE_DURATION_MS 1200UL

class Button;

enum class ButtonStatus {
	UNKNOWN, PRESSED, RELEASED
};

class ButtonInteractionMonitor: public Task, public HostSystemAware<System> {
public:
	ButtonInteractionMonitor(uint32_t timeInterval, Button *button, System *system);
protected:
	void OnUpdate(uint32_t deltaTime) override;
private:
	Button *button;
};


class Button: public HostSystemAware<System>, public Named {
	friend class ButtonInteractionMonitor;
public:
	Button(System *system, uint8_t inputPin, Button *&staticButton, void (*changeISR)(void));
	bool isUserInteracting();
	Event ackInteraction();
	void statusChangeCallback();
private:
	void onButtonFall();
	void onButtonRise();
	void refreshHoldStatus(uint32_t now, bool isExitingFromHold = false);
	void reset();
	volatile ButtonStatus status = ButtonStatus::UNKNOWN;
	uint8_t inputPin;
	volatile uint32_t lastFallTimeMs = 0;
	volatile uint32_t lastRiseTimeMs = 0;
	volatile uint8_t clicksCount = 0;
	volatile uint8_t holdsCount = 0;
	volatile bool haveClicksToNotify = false;
	volatile bool haveHoldsToNotify = false;
	ButtonInteractionMonitor uiMonitor {MsToTaskTime(10), this, getHostSystem()};
};

inline ButtonInteractionMonitor::ButtonInteractionMonitor(uint32_t timeInterval,
		Button *button, System *system) :
		Task(timeInterval), HostSystemAware(system), button(button) {
}

inline void ButtonInteractionMonitor::OnUpdate(uint32_t deltaTime) {
	if (button->isUserInteracting()) {

		/*
		 * User is interacting. Stay awake to intercept holds!
		 */
		Event event = button->ackInteraction();

		if (event.getClicksCount() > 0 || event.getHoldStepsCount() > 0) {
			if (button->getInstanceName() != nullptr) {
				trace("%s: %d clicks, %d holds", button->getInstanceName(), event.getClicksCount(), event.getHoldStepsCount());
			}

			/*
			 * We have a complete interaction
			 */
			getHostSystem()->receiveEvent(event);
		}
	} else {

		/*
		 * No interaction. No hold to intercept.
		 */
		noInterrupts();
		if (!button->isUserInteracting()) {

			/*
			 * Double check
			 */
			getHostSystem()->StopTask(this);
			button->reset();
		}
		interrupts();
	}
}

inline Button::Button(System *system, uint8_t inputPin, Button *&staticButton, void (*changeISR)(void)) :
		HostSystemAware(system), inputPin(inputPin) {
	pinMode(inputPin, INPUT_PULLUP);
	delay(1);
	status =
			digitalRead(inputPin) == LOW ?
					ButtonStatus::PRESSED : ButtonStatus::RELEASED;
	staticButton = this;
	attachInterrupt(digitalPinToInterrupt(inputPin), changeISR, CHANGE);
}

inline void Button::onButtonFall() {
	traceNamedInstance("onButtonFall");

	if (status == ButtonStatus::PRESSED) {
		trace("LOW bounce filtered");
		return;
	}

	lastFallTimeMs = millis();
	status = ButtonStatus::PRESSED;
	holdsCount = 0;
	haveHoldsToNotify = false;
}

inline void Button::onButtonRise() {
	traceNamedInstance("onButtonRise");

	if (status == ButtonStatus::RELEASED) {
		trace("HIGH bounce filtered");
		return;
	}

	lastRiseTimeMs = millis();
	status = ButtonStatus::RELEASED;

	if (lastRiseTimeMs - lastFallTimeMs >= BUTTON_HOLD_BEGIN_THRESHOLD_MS) {

		/*
		 * Exting from a hold
		 */
		refreshHoldStatus(lastRiseTimeMs, true);
	} else {

		/*
		 * This is a click
		 */
		++clicksCount;
		haveClicksToNotify = true;
	}
}

inline void Button::statusChangeCallback() {
	digitalRead(inputPin) == LOW ? onButtonFall() : onButtonRise();
	getHostSystem()->StartTask(&uiMonitor);
}

inline Event Button::ackInteraction() {
	uint32_t currentMs = millis();
	uint8_t clicksToNotify = 0;

	if (haveClicksToNotify) {
		if (currentMs - lastRiseTimeMs < CONSECUTIVE_CLICKS_MAX_DELAY) {

			/*
			* There is still time to cumulate clicks, so we cannot (already) notify them
			*/
			clicksToNotify = 0;
		} else {
			clicksToNotify = clicksCount;
			clicksCount = 0;
			haveClicksToNotify = false;
		}
	}

	refreshHoldStatus(currentMs);
	uint8_t holdsToNotify = 0;

	if (haveHoldsToNotify) {
		holdsToNotify = holdsCount;
		if (status != ButtonStatus::PRESSED) {
			holdsCount = 0;
		}
		haveHoldsToNotify = false;
	}

	return Event(clicksToNotify, holdsToNotify);
}

/*
 * Used to keep alive the user interaction monitor
 */
inline bool Button::isUserInteracting() {
	if (status == ButtonStatus::PRESSED) {
		return true;
	} else {
		return haveClicksToNotify || haveHoldsToNotify;
	}
}

inline void Button::refreshHoldStatus(uint32_t millis, boolean isExitingFromHold) {
	if (status == ButtonStatus::RELEASED && !isExitingFromHold) {
		return;
	}

	uint32_t holdDurationMs = millis - lastFallTimeMs;

	if (holdDurationMs < BUTTON_HOLD_BEGIN_THRESHOLD_MS) {

		/*
		 * Too soon
		 */
		return;
	}

	uint8_t holdsCountTemp;
	holdsCountTemp = (holdDurationMs - BUTTON_HOLD_BEGIN_THRESHOLD_MS) / HOLD_CYCLE_DURATION_MS + 1;

	if (holdsCountTemp == holdsCount) {

		/*
		 * Already notified
		 */
		return;
	}

	holdsCount = holdsCountTemp;
	haveHoldsToNotify = true;
}

inline void Button::reset() {
	lastFallTimeMs = 0;
	lastRiseTimeMs = 0;
	clicksCount = 0;
	holdsCount = 0;
	haveClicksToNotify = false;
	haveHoldsToNotify = false;
}

#endif
