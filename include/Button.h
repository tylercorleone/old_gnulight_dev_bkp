#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>
#include "UserInteractionMonitor.h"

class Gnulight;

enum ButtonStatus {
	PRESSED, RELEASED
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

public:
	Button(Gnulight* gnulight, uint8_t pin, Button *&staticButton, void (*changeISR)(void));
	void statusChangeCallback();
//	void setup(uint8_t pin, void (*changeISR)(void));
	bool isUserInteracting();
	ButtonInteraction ackInteraction();
	uint32_t getHoldTime() const;
	uint32_t getLastRiseTime() const;
	uint32_t getLastFallTime() const;
	uint32_t getLastChangeTime() const;
	uint8_t inspectClicksCount() const;
	bool isPressed() const;
	bool isHoldingFrom(uint32_t milliseconds) const;

private:
	void onButtonFall();
	void onButtonRise();
	uint8_t convertHoldTimeToHoldStepsCount(uint32_t milliseconds);
	volatile ButtonStatus status;
	volatile uint32_t lastFallTime = 0;
	volatile uint32_t lastRiseTime = 0;
	volatile uint32_t lastChangeTime = 0;
	volatile uint8_t clicksCount = 0;
	volatile bool clicksCountAck = false;
	UserInteractionMonitor uiMonitor {MsToTaskTime(10), this, gnulight};
	Gnulight* gnulight;
};

#endif
