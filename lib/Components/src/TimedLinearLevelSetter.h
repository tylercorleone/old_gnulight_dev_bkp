#ifndef TIMEDLINEARLEVELSETTER_H
#define TIMEDLINEARLEVELSETTER_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#define TIMED_POTENTIOMETER_ACTUATOR_INTERVAL_MS 30UL

class TimedLinearLevelSetter: public Task {
public:
	TimedLinearLevelSetter(uint32_t timeInterval, TaskManager* taskManager);
	void setLevel(float level, uint32_t transitionDurationMs);
	virtual ~TimedLinearLevelSetter();
protected:
	virtual float readLevel() = 0;
	virtual void writeLevel(float level) = 0;
private:
	void OnUpdate(uint32_t timeInterval) override;
	TaskManager* taskManager;
	float targetLevel = 0.0;
	uint32_t stepsToGo = 0;
};

inline TimedLinearLevelSetter::TimedLinearLevelSetter(uint32_t timeInterval,
		TaskManager* taskManager) :
		Task(timeInterval), taskManager(taskManager) {
}

inline void TimedLinearLevelSetter::setLevel(float level,
		uint32_t transitionDurationMs) {
	targetLevel = level;
	stepsToGo = transitionDurationMs / TaskTimeToMs(_timeInterval);
	if (stepsToGo == 0) {
		if (getTaskState() == TaskState_Running) {
			taskManager->StopTask(this);
		}
		writeLevel(targetLevel);
	} else {
		taskManager->StartTask(this);
	}
}

inline void TimedLinearLevelSetter::OnUpdate(uint32_t timeInterval) {
	float currentLevel = readLevel();
	if (stepsToGo == 1 || currentLevel == targetLevel) {
		writeLevel(targetLevel);
		taskManager->StopTask(this);
	} else {
		float levelIncrement = (targetLevel - currentLevel) / stepsToGo;
		writeLevel(currentLevel + levelIncrement);
		--stepsToGo;
	}
}

inline TimedLinearLevelSetter::~TimedLinearLevelSetter() {
}

#endif
