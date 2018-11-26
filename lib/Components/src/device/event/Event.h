#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

class Event {
	/*
	 * Does nothing, just type inference
	 */
public:
	virtual const char* getEventTypeUUID() const;
	static const char* eventTypeUUID();
	virtual ~ Event();
protected:
	Event() {
	}
};

inline const char* Event::getEventTypeUUID() const {
	return eventTypeUUID();
}

inline const char* Event::eventTypeUUID() {
	const static char eventUUID = 'E';
	return &eventUUID;
}

inline Event::~Event() {
}

#include "ButtonEvent.h"
#include "MessageEvent.h"

#endif
