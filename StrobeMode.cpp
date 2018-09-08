#include "StrobeMode.h"
#include "Gnulight.h"

StrobeMode::StrobeMode(const char* className, Gnulight* gnulight) :
		GnulightMode(className, gnulight) {
	trace(className + "::" + className);
	pToggleLightStatusTask = new FunctionsSequenceTask(StrobeMode::switchLightStatus, this);
	pToggleLightStatusTask->thenRepeat();
}

bool StrobeMode::onEnterMode(ButtonInteraction* interaction) {
	info(className + "::onEnterMode");
	debug("strobe type " + currentStrobeType);
	pSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MED);
	if (currentStrobeType == SINUSOIDAL_STROBE || currentStrobeType == LINEAR_STROBE) {
		pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
	}
	pSystem->StartTask(pToggleLightStatusTask);
	return true;
}

void StrobeMode::onExitMode() {
	info(className + "::onExitMode");
	pSystem->StopTask(pToggleLightStatusTask);
}

bool StrobeMode::interpretUserInteraction(ButtonInteraction& interaction) {
	pSystem->ResetTask(pToggleLightStatusTask);
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
			pSystem->enterMode(pSystem->powerOffMode, &interaction);
			return true;
		case 2:
			currentStrobeType = (currentStrobeType + 1) % STROBE_TYPES_COUNT;
			debug("strobe type " + currentStrobeType);
			if (currentStrobeType == SINUSOIDAL_STROBE) {
				pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			}
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pSystem->lightDriver.setNextMainLevel();
			return true;
		} else {
			return false;
		}
	}
}

uint32_t periodo = 2000;
float ondaTriangolare(uint32_t t) {
	t = t % periodo;
	if (t < periodo / 2) {
		return static_cast<float>(t) / (periodo / 2);
	} else {
		return static_cast<float>(-(t - periodo)) / (periodo / 2);
	}
}

uint32_t StrobeMode::switchLightStatus(StrobeMode* _this) {
	uint32_t interval = 0;
	switch (_this->currentStrobeType) {
	case SLOW_STROBE:
		interval = MsToTaskTime(SLOW_STROBE_INTERVAL_MS);
		break;
	case FAST_STROBE:
		interval = MsToTaskTime(FAST_STROBE_INTERVAL_MS);
		break;
	case BEACON_STROBE:
		if (_this->pSystem->lightDriver.getLightStatus() == LIGHT_STATUS_OFF) {
			interval = MsToTaskTime(BEACON_STROBE_INTERVAL_MS * BEACON_STROBE_DUTY_CYCLE);
		} else {
			interval = MsToTaskTime(BEACON_STROBE_INTERVAL_MS * (1.0f - BEACON_STROBE_DUTY_CYCLE));
		}
		break;
	case DISCO_STROBE:
		if (_this->pSystem->lightDriver.getLightStatus() == LIGHT_STATUS_OFF) {
			interval = MsToTaskTime(DISCO_STROBE_INTERVAL_MS * DISCO_STROBE_DUTY_CYCLE);
		} else {
			interval = MsToTaskTime(DISCO_STROBE_INTERVAL_MS * (1.0f - DISCO_STROBE_DUTY_CYCLE));
		}
		break;
	case SINUSOIDAL_STROBE: {
		float newLevel = _this->pSystem->lightDriver.getCurrentMainLevel()
				* (sin(0.001f * millis() * PI) + 1.0f) / 2.0f;
		newLevel = max(newLevel, MINIMUM_LIGHT_OUTPUT);
		_this->pSystem->lightDriver.setPotentiometerLevel(newLevel);
	}
		interval = MsToTaskTime(SINUSOIDAL_STROBE_INTERVAL_MS);
		break;
	case LINEAR_STROBE:
		_this->pSystem->lightDriver.setPotentiometerLevel(max(MINIMUM_LIGHT_OUTPUT, ondaTriangolare(millis())));
		interval = MsToTaskTime(SINUSOIDAL_STROBE_INTERVAL_MS);
		break;
	default:
		return -1;
	}
	if (_this->currentStrobeType != SINUSOIDAL_STROBE && _this->currentStrobeType != LINEAR_STROBE) {
		_this->pSystem->lightDriver.toggleLightStatus();
	}
	return interval;
}
