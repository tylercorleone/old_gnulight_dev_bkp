#include "defines.h"
#include "Button.h"
#include "Gnulight.h"

Button::Button(Gnulight* gnulight, uint8_t pin, Button *&staticButton,
		void (*changeISR)(void)) :
		gnulight(gnulight) {
	debug("Inst. Btn");
	pinMode(pin, INPUT_PULLUP);
	delay(1);
	status = digitalRead(BUTTON_PIN) == LOW ? ButtonStatus::PRESSED : ButtonStatus::RELEASED;
	staticButton = this;
	attachInterrupt(digitalPinToInterrupt(pin), changeISR, CHANGE);
}

void Button::onButtonFall() {
	trace("Btn::onButtonFall");
	if (status == ButtonStatus::PRESSED) {
		trace("LOW bounce filtered");
		return;
	}
	lastFallTimeMs = millis();
	status = ButtonStatus::PRESSED;
	holdsCount = 0;
	haveHoldsToNotify = false;
}

void Button::onButtonRise() {
	trace("Btn::onButtonRise");
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

void Button::statusChangeCallback() {
	digitalRead(BUTTON_PIN) == LOW ? onButtonFall() : onButtonRise();
	gnulight->StartTask(&uiMonitor);
}

ButtonInteraction Button::ackInteraction() {
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

	return ButtonInteraction(clicksToNotify, holdsToNotify);
}

/*
 * Used to keep alive the user interaction monitor
 */
bool Button::isUserInteracting() {
	if (status == ButtonStatus::PRESSED) {
		return true;
	} else {
		return haveClicksToNotify || haveHoldsToNotify;
	}
}

void Button::refreshHoldStatus(uint32_t millis, boolean isExitingFromHold) {
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

void Button::reset() {
	lastFallTimeMs = 0;
	lastRiseTimeMs = 0;
	clicksCount = 0;
	holdsCount = 0;
	haveClicksToNotify = false;
	haveHoldsToNotify = false;
}
