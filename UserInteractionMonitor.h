#ifndef USER_INTERACTION_MONITOR_TASK_H
#define USER_INTERACTION_MONITOR_TASK_H

#include "defines.h"
#include "Task.h"

class Button;
class Gnulight;

class UserInteractionMonitor: public Task {
public:
	UserInteractionMonitor(uint32_t timeInterval, Button* button, Gnulight* gnulight);
protected:
	bool OnStart() override;
	void OnUpdate(uint32_t deltaTime) override;
	void OnStop() override;
private:
	uint8_t lastHoldStepsCountDelivered = 0;
	Button* button;
	Gnulight* gnulight;
};

#endif
