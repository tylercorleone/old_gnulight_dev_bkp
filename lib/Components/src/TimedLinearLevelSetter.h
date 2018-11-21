#ifndef TIMEDLINEARLEVELSETTER_H
#define TIMEDLINEARLEVELSETTER_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

class TimedLinearLevelSetter: public Task {
public:
	TimedLinearLevelSetter(uint32_t timeInterval, TaskManager *taskManager);
	void setLevel(float level, uint32_t transitionDurationMs);
	virtual ~TimedLinearLevelSetter();
protected:
	virtual float readLevel() = 0;
	virtual void writeLevel(float level) = 0;
private:
	void OnUpdate(uint32_t timeInterval) override;
	TaskManager *taskManager;
	float targetLevel = 0.0;
	uint32_t stepsToGo = 0;
};

inline TimedLinearLevelSetter::TimedLinearLevelSetter(uint32_t timeInterval,
		TaskManager *taskManager) :
		Task(timeInterval), taskManager(taskManager) {
}

inline void TimedLinearLevelSetter::setLevel(float level,
		uint32_t transitionDurationMs) {
	if (getTaskState() == TaskState_Running) {
		taskManager->StopTask(this);
	}

	targetLevel = level;

	stepsToGo = transitionDurationMs / TaskTimeToMs(_timeInterval);

	if (stepsToGo == 0) {
		writeLevel(targetLevel);
	} else {
		taskManager->StartTask(this);
	}
}

inline void TimedLinearLevelSetter::OnUpdate(uint32_t deltaTime) {

	if (stepsToGo == 1) {
		writeLevel(targetLevel);
	} else {
		float currentLevel = readLevel();
		writeLevel(currentLevel + (targetLevel - currentLevel) / stepsToGo);
	}

	--stepsToGo;

	if (stepsToGo == 0) {
		taskManager->StopTask(this);
	}
}

inline TimedLinearLevelSetter::~TimedLinearLevelSetter() {
}

#endif
