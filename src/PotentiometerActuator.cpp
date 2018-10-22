#include "PotentiometerActuator.h"
#include "AdvancedLightDriver.h"

PotentiometerActuator::PotentiometerActuator(AdvancedLightDriver* advancedLightDriver, TaskManager* taskManager)
		: Task(MsToTaskTime(TIMED_POTENTIOMETER_SETTER_INTERVAL_MS)), advancedLightDriver(advancedLightDriver), taskManager(taskManager) {
}

void PotentiometerActuator::setPotentiometerLevel(float level,
		uint32_t transitionDurationMs, bool operateOnCurrent) {
	debug(
			"PotAct::setPotentiometerLevel(" + level + ", " + transitionDurationMs + ", " + operateOnCurrent + ")");
	targetLevel = level;
	stepsToGo = transitionDurationMs / TaskTimeToMs(_timeInterval);
	this->operateOnCurrent = operateOnCurrent;
	if (stepsToGo == 0) {
		if (this->isActive()) {
			taskManager->StopTask(this);
		}
		writeLevel(targetLevel);
	} else {
		taskManager->StartTask(this);
	}
}

void PotentiometerActuator::OnUpdate(uint32_t timeInterval) {
	trace("PotAct::OnUpdate");
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

float PotentiometerActuator::readLevel() {
	return operateOnCurrent ?
					advancedLightDriver->getCurrentLevel() :
					advancedLightDriver->getPotentiometerLevel();
}

void PotentiometerActuator::writeLevel(float level) {
	if (operateOnCurrent) {
		advancedLightDriver->setCurrentLevel(level);
	} else {
		advancedLightDriver->_setPotentiometerLevel(level);
	}
}

