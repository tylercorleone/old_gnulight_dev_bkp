#ifndef USER_INTERACTION_MONITOR_TASK_H
#define USER_INTERACTION_MONITOR_TASK_H

#include "defines.h"
#include "Task.h"
#include "system/HostSystemAware.h"

class Gnulight;

class UserInteractionMonitorTask: public Task, public HostSystemAware<Gnulight> {
public:
	UserInteractionMonitorTask(uint32_t timeInterval, Gnulight* gnulight);
protected:
	bool OnStart() override;
	void OnUpdate(uint32_t deltaTime) override;
	void OnStop() override;
private:
	uint8_t lastHoldStepsCountDelivered = 0;
};

#endif
