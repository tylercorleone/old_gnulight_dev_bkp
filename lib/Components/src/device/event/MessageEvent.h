#ifndef MESSAGEEVENT_H
#define MESSAGEEVENT_H

#include "Event.h"
#include <string.h>

class MessageEvent: public Event {
public:
	MessageEvent(const char *message);
	const char* getMessage() const;
	bool equals(const char *message) const;
	bool equals(const MessageEvent &event) const;
	const char* getEventTypeUUID() const override;
	static const char* eventTypeUUID();
	virtual ~MessageEvent();
private:
	const char *message = nullptr;
};

inline MessageEvent::MessageEvent(const char *message) :
		message(message) {
}

inline const char* MessageEvent::getMessage() const {
	return message;
}

inline bool MessageEvent::equals(const char *message) const {
	return strcmp(this->message, message) == 0;
}

inline bool MessageEvent::equals(const MessageEvent &event) const {
	return strcmp(this->message, event.message) == 0;
}

inline const char* MessageEvent::getEventTypeUUID() const {
	return eventTypeUUID();
}

inline const char* MessageEvent::eventTypeUUID() {
	const static char messageEventUUID = 'M';
	return &messageEventUUID;
}

inline MessageEvent::~MessageEvent() {
}

#endif
