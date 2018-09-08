#include "defines.h"
#include "Button.h"
#include "Gnulight.h"
#include "UserInteractionMonitorTask.h"

Button::Button(Gnulight* gnulight, uint8_t pin, Button *&staticButton, void (*changeISR)(void)) :
		HostSystemAware(gnulight) {
	trace("Inst. Btn");
	pinMode(pin, INPUT_PULLUP);
	delay(1);
	status = digitalRead(BUTTON_PIN) == LOW ? PRESSED : RELEASED;
	staticButton = this;
	attachInterrupt(digitalPinToInterrupt(pin), changeISR, CHANGE);
}

void Button::onButtonFall() {
	trace("Btn::onButtonFall");
	if (status == PRESSED) {
		trace("Button is returning LOW from LOW");
		return;
	}
	status = PRESSED;
	lastFallTime = lastChangeTime = getNow();
	if (lastFallTime - lastRiseTime >= CONSECUTIVE_CLICK_MAX_DELAY) {
		// se non c'è più tempo per cumulare un altro click
		clicksCount = 0;
	}
}

void Button::onButtonRise() {
	trace("Btn::onButtonRise");
	if (status == RELEASED) {
		trace("Button is returning HIGH from HIGH");
		return;
	}
	status = RELEASED;
	lastRiseTime = lastChangeTime = getNow();
	if (lastRiseTime - lastFallTime < CONSECUTIVE_CLICK_MAX_DELAY) {
		++clicksCount;
		clicksCountAck = false;
	} else if (lastRiseTime - lastFallTime <= CYCLE_ZERO_INTERVAL_MS) {
		clicksCount = 1;
		clicksCountAck = false;
	}
}

void Button::statusChangeCallback() {
	digitalRead(BUTTON_PIN) == LOW ? onButtonFall() : onButtonRise();
	pSystem->StartTask(&pSystem->uiMonitor);
}

ButtonInteraction Button::ackInteraction() {
	uint8_t _clicksCount = 0;
	if (!clicksCountAck && getNow() - lastRiseTime >= CONSECUTIVE_CLICK_MAX_DELAY) {
		clicksCountAck = true;
		_clicksCount = clicksCount;
	}
	return ButtonInteraction(_clicksCount, convertHoldTimeToHoldStepsCount(getHoldTime()));
}

bool Button::isUserInteracting() {
	if (status == PRESSED) {
		return true;
	} else {
		if (getNow() - lastRiseTime < CONSECUTIVE_CLICK_MAX_DELAY) {
			return true;
		} else {
			return clicksCount > 0 && !clicksCountAck;
		}
	}
}

uint8_t Button::convertHoldTimeToHoldStepsCount(
		uint32_t milliseconds) {
	if (milliseconds <= CYCLE_ZERO_INTERVAL_MS) {
		return 0;
	}
	return (milliseconds - CYCLE_ZERO_INTERVAL_MS) / CYCLE_INTERVAL_MS + 1;
}

uint32_t Button::getHoldTime() const {
	if (status != PRESSED) {
		return 0;
	}
	return getNow() - lastFallTime;
}

uint32_t Button::getLastRiseTime() const {
	return lastRiseTime;
}

uint32_t Button::getLastFallTime() const {
	return lastFallTime;
}

uint32_t Button::getLastChangeTime() const {
	return lastChangeTime;
}

uint8_t Button::inspectClicksCount() const {
	return clicksCount;
}

bool Button::isPressed() const {
	return status == PRESSED;
}

bool Button::isHoldingFrom(uint32_t milliseconds) const {
	return status == PRESSED && getNow() - lastFallTime >= milliseconds;
}
