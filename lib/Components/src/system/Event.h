#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>
#include <string.h>

class Event {
public:
	Event(uint8_t clicksCount, uint8_t holdStepsCount) :
			clicksCount(clicksCount), holdStepsCount(holdStepsCount) {
	}

	Event(const char *message) :
			message(message) {
	}

	uint8_t getClicksCount() const {
		return clicksCount;
	}

	uint8_t getHoldStepsCount() const {
		return holdStepsCount;
	}

	const char* getMessage() const {
		return message;
	}

	bool isMessage(const char *message) const {
		return strcmp(this->message, message) == 0;
	}
private:
	uint8_t clicksCount = 0;
	uint8_t holdStepsCount = 0;
	const char *message = nullptr;
};

#endif
