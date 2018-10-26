#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "UserInteractionMonitor.h"

class Gnulight;

enum class ButtonStatus {
	UNKNOWN, PRESSED, RELEASED
};

class ButtonInteraction {
	friend class Button;
public:
	ButtonInteraction(uint8_t clicksCount, uint8_t holdStepsCount) :
			clicksCount(clicksCount), holdStepsCount(holdStepsCount) {
	}
	uint8_t getClicksCount() const {
		return clicksCount;
	}
	uint8_t getHoldStepsCount() const {
		return holdStepsCount;
	}
private:
	uint8_t clicksCount;
	uint8_t holdStepsCount;
};

class Button {
	friend class UserInteractionMonitor;
public:
	Button(Gnulight* gnulight, uint8_t pin, Button *&staticButton, void (*changeISR)(void));
	bool isUserInteracting();
	ButtonInteraction ackInteraction();
	void statusChangeCallback();
private:
	void onButtonFall();
	void onButtonRise();
	void refreshHoldStatus(uint32_t now, boolean isExitingFromHold = false);
	void reset();
	volatile ButtonStatus status = ButtonStatus::UNKNOWN;
	volatile uint32_t lastFallTimeMs = 0;
	volatile uint32_t lastRiseTimeMs = 0;
	volatile uint8_t clicksCount = 0;
	volatile uint8_t holdsCount = 0;
	volatile bool haveClicksToNotify = false;
	volatile bool haveHoldsToNotify = false;
	UserInteractionMonitor uiMonitor {MsToTaskTime(10), this, gnulight};
	Gnulight* gnulight;
};

#endif
