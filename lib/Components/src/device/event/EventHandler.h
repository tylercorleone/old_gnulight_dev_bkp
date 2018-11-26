#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

class Event;

template<typename T = Event> class EventHandler {
public:
	virtual bool handleEvent(const T &event) = 0;
	virtual ~EventHandler() {}
};

#endif
