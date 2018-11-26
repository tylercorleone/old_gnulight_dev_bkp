#ifndef BUTTONEVENT_H
#define BUTTONEVENT_H

#include "Event.h"
#include <stdint.h>

class ButtonEvent: public Event {
public:
	ButtonEvent(uint8_t clicksCount, uint8_t holdStepsCount);
	uint8_t getClicksCount() const;
	uint8_t getHoldStepsCount() const;
	const char* getEventTypeUUID() const override;
	static const char* eventTypeUUID();
	virtual ~ ButtonEvent();
private:
	uint8_t clicksCount = 0;
	uint8_t holdStepsCount = 0;
};

inline ButtonEvent::ButtonEvent(uint8_t clicksCount, uint8_t holdStepsCount) :
		clicksCount(clicksCount), holdStepsCount(holdStepsCount) {
}

inline uint8_t ButtonEvent::getClicksCount() const {
	return clicksCount;
}

inline uint8_t ButtonEvent::getHoldStepsCount() const {
	return holdStepsCount;
}

inline const char* ButtonEvent::getEventTypeUUID() const {
	return eventTypeUUID();
}

inline const char* ButtonEvent::eventTypeUUID() {
	const static char buttonEventUUID = 'B';
	return &buttonEventUUID;
}

inline ButtonEvent::~ButtonEvent() {
}

#endif
