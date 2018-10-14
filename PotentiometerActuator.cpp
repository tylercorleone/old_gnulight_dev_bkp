#include "PotentiometerActuator.h"
#include "AdvancedLightDriver.h"

PotentiometerActuator::PotentiometerActuator(
		AdvancedLightDriver* advancedLightDriver, uint32_t timeInterval,
		TaskManager* taskManager) :
		advancedLightDriver(advancedLightDriver), Task(timeInterval), taskManager(
				taskManager) {
}

void PotentiometerActuator::setPotentiometerLevel(float level,
		uint32_t transitionDurationMs, bool operateAtRelativeCurrentLevel) {
	debug(
			"PotAct::setPotentiometerLevel(" + level + ", " + transitionDurationMs + ", " + operateAtRelativeCurrentLevel + ")");
	targetLevel = level;
	stepsToGo = transitionDurationMs / _timeInterval;
	this->operateAtRelativeCurrentLevel = operateAtRelativeCurrentLevel;
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
	return operateAtRelativeCurrentLevel ?
					advancedLightDriver->LightDriver::getPotentiometerLevel() :
					advancedLightDriver->getPotentiometerLevel();
}

void PotentiometerActuator::writeLevel(float level) {
	if (operateAtRelativeCurrentLevel) {
		advancedLightDriver->LightDriver::setPotentiometerLevel(level);
	} else {
		advancedLightDriver->_setPotentiometerLevel(level);
	}
}

