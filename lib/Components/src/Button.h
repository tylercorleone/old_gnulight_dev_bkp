#ifndef BUTTON_H
#define BUTTON_H

#include "Components.h"

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#define CONSECUTIVE_CLICKS_MAX_DELAY 600L
#define BUTTON_HOLD_BEGIN_THRESHOLD_MS 800L
#define HOLD_CYCLE_DURATION_MS 1200UL

class Button;

enum class ButtonStatus {
	PRESSED, RELEASED
};

class ButtonInteractionMonitor: public Task {
public:
	ButtonInteractionMonitor(Button *button, uint32_t timeInterval);
protected:
	void OnUpdate(uint32_t deltaTime) override;
private:
	Button *button;
};

class Button: public DeviceAware<BasicDevice>, public Named {
	friend class ButtonInteractionMonitor;
public:
	Button(BasicDevice *system, uint8_t inputPin, Button *&staticButton,
			void (*changeISR)(void));
	bool isUserInteracting();
	ButtonEvent ackInteraction();
	void statusChangeCallback();
private:
	void onButtonFall();
	void onButtonRise();
	void refreshHoldStatus(uint32_t now, bool isExitingFromHold = false);
	void reset();
	volatile ButtonStatus status;
	uint8_t inputPin;
	volatile uint32_t lastFallTimeMs;
	volatile uint32_t lastRiseTimeMs;
	volatile uint8_t clicksCount;
	volatile uint8_t holdsCount;
	volatile bool haveClicksToNotify;
	volatile bool haveHoldsToNotify;
	ButtonInteractionMonitor uiMonitor { this , MsToTaskTime(10)};
};

inline ButtonInteractionMonitor::ButtonInteractionMonitor(Button *button,
		uint32_t timeInterval) :
		Task(timeInterval), button(button) {
}

inline void ButtonInteractionMonitor::OnUpdate(uint32_t deltaTime) {
	if (button->isUserInteracting()) {

		/*
		 * User is interacting. Stay awake to intercept holds!
		 */
		ButtonEvent event = button->ackInteraction();

		if (event.getClicksCount() > 0 || event.getHoldStepsCount() > 0) {
			debugIfOtherNamed(button, "%s: %d clicks, %d holds",
					button->getInstanceName(), event.getClicksCount(),
					event.getHoldStepsCount());

			/*
			 * We have a complete interaction
			 */
			button->Device()->receiveEvent(event);
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
			button->Device()->StopTask(this);
			button->reset();
		}
		interrupts();
	}
}

inline Button::Button(BasicDevice *system, uint8_t inputPin, Button *&staticButton,
		void (*changeISR)(void)) :
		DeviceAware(system), inputPin(inputPin) {
	pinMode(inputPin, INPUT_PULLUP);
	delay(1);
	status =
			digitalRead(inputPin) == LOW ?
					ButtonStatus::PRESSED : ButtonStatus::RELEASED;
	staticButton = this;
	reset();
	attachInterrupt(digitalPinToInterrupt(inputPin), changeISR, CHANGE);
}

inline void Button::onButtonFall() {
	traceIfNamed("onButtonFall");

	if (status == ButtonStatus::PRESSED) {
		traceIfNamed("LOW bounce filtered");
		return;
	}

	lastFallTimeMs = millis();
	status = ButtonStatus::PRESSED;
	holdsCount = 0;
	haveHoldsToNotify = false;
}

inline void Button::onButtonRise() {
	traceIfNamed("onButtonRise");

	if (status == ButtonStatus::RELEASED) {
		traceIfNamed("HIGH bounce filtered");
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
	Device()->StartTask(&uiMonitor);
}

inline ButtonEvent Button::ackInteraction() {
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

	return ButtonEvent(clicksToNotify, holdsToNotify);
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

inline void Button::refreshHoldStatus(uint32_t millis,
		boolean isExitingFromHold) {
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
	holdsCountTemp = (holdDurationMs - BUTTON_HOLD_BEGIN_THRESHOLD_MS)
			/ HOLD_CYCLE_DURATION_MS + 1;

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
