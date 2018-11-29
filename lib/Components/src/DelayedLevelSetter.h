#ifndef DELAYEDLEVELSETTER_H
#define DELAYEDLEVELSETTER_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

class DelayedLevelSetter: public Task {
public:
	DelayedLevelSetter(uint32_t timeInterval, TaskManager &taskManager);
	void setLevel(float level, uint32_t transitionDurationMs);
	virtual ~DelayedLevelSetter();
protected:
	virtual float readLevel() = 0;
	virtual void writeLevel(float level) = 0;
	TaskManager &taskManager;
private:
	void OnUpdate(uint32_t timeInterval) override;
	float targetLevel = 0.0;
	uint32_t stepsToGo = 0;
};

inline DelayedLevelSetter::DelayedLevelSetter(uint32_t timeInterval,
		TaskManager &taskManager) :
		Task(timeInterval), taskManager(taskManager) {
}

inline void DelayedLevelSetter::setLevel(float level,
		uint32_t transitionDurationMs) {
	if (getTaskState() == TaskState_Running) {
		taskManager.StopTask(this);
	}

	stepsToGo = transitionDurationMs / TaskTimeToMs(_timeInterval);

	if (stepsToGo == 0 || readLevel() == level) {
		writeLevel(level);
	} else {
		targetLevel = level;
		taskManager.StartTask(this);
	}
}

inline void DelayedLevelSetter::OnUpdate(uint32_t deltaTime) {

	if (stepsToGo == 1) {
		writeLevel(targetLevel);
	} else {
		float currentLevel = readLevel();
		writeLevel(currentLevel + (targetLevel - currentLevel) / stepsToGo);
	}

	--stepsToGo;

	if (stepsToGo == 0) {
		taskManager.StopTask(this);
	}
}

inline DelayedLevelSetter::~DelayedLevelSetter() {
}

#endif
