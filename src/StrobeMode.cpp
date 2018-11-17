#include "StrobeMode.h"
#include "Gnulight.h"

bool StrobeMode::onEnterMode(ButtonInteraction* interaction) {
	info(modeName + "::onEnterMode");debug("strobe type " + currentStrobeType);
	varName = pHostSystem->lightDriver.setMainLevel(
			MainLightLevel::MED);
	if (currentStrobeType == SINUSOIDAL_STROBE
			|| currentStrobeType == LINEAR_STROBE) {
		pHostSystem->lightDriver.setState(OnOffState::ON);
	}
	pHostSystem->StartTask(&toggleLightStatusTask);
	return true;
}

void StrobeMode::onExitMode() {
	info(modeName + "::onExitMode");
	pHostSystem->StopTask(&toggleLightStatusTask);
}

bool StrobeMode::interpretUserInteraction(ButtonInteraction& interaction) {
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
			pHostSystem->enterMode(pHostSystem->powerOffMode);
			return true;
		case 2:
			currentStrobeType = (currentStrobeType + 1) % STROBE_TYPES_COUNT;
			debug("strobe type " + currentStrobeType);

			if (currentStrobeType == SINUSOIDAL_STROBE
					|| currentStrobeType == LINEAR_STROBE) {
				MainLightLevel currentMainLevel =
						pHostSystem->lightDriver.getCurrentMainLevel();
				varName = pHostSystem->lightDriver.setMainLevel(
						currentMainLevel);
				pHostSystem->lightDriver.setState(
						OnOffState::ON);
			}

			toggleLightStatusTask.setTimeInterval(0);
			pHostSystem->ResetTask(&toggleLightStatusTask);			return true;
		case 3:
			periodMultiplierX1000 *= 2;
			return true;
		case 4:
			if (periodMultiplierX1000 > 125) {
				periodMultiplierX1000 /= 2;
			}
			return true;
		default:
			return false;
		}
	} else if (interaction.getHoldStepsCount() > 0) {
		varName = pHostSystem->lightDriver.setNextMainLevel();
		return true;
	} else {
		return false;
	}
}

uint32_t StrobeMode::switchLightStatus(StrobeMode* _this) {
	uint32_t nextIntervalMs = 0;
	float nextPotentiometerLevel;
	uint32_t periodMs;

	switch (_this->currentStrobeType) {
	case ON_OFF_STROBE:
		nextIntervalMs = ON_OFF_STROBE_PERIOD_MS / 2
				* _this->periodMultiplierX1000 / 1000;
		break;
	case BEACON_STROBE:
		if (_this->pHostSystem->lightDriver.getState()
				== OnOffState::OFF) {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS * BEACON_STROBE_DUTY_CYCLE;
		} else {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS
					* (1.0f - BEACON_STROBE_DUTY_CYCLE);
		}
		break;
	case DISCO_STROBE:
		if (_this->pHostSystem->lightDriver.getState()
				== OnOffState::OFF) {
			nextIntervalMs = DISCO_STROBE_PERIOD_MS * DISCO_STROBE_DUTY_CYCLE;
		} else {
			nextIntervalMs = DISCO_STROBE_PERIOD_MS
					* (1.0f - DISCO_STROBE_DUTY_CYCLE);
		}
		break;
	case SINUSOIDAL_STROBE:
		periodMs = PERIODICAL_SEQUENCE_STROBES_PERIOD_MS
				* _this->periodMultiplierX1000 / 1000;
		nextPotentiometerLevel = MIN_POTENTIOMETER_LEVEL
				+ (_this->varName - MIN_POTENTIOMETER_LEVEL)
						* (sinWave(millis(), periodMs)) / 2.0f;
		break;
	case LINEAR_STROBE:
		periodMs = PERIODICAL_SEQUENCE_STROBES_PERIOD_MS
				* _this->periodMultiplierX1000 / 1000;
		nextPotentiometerLevel = MIN_POTENTIOMETER_LEVEL
				+ (_this->varName - MIN_POTENTIOMETER_LEVEL)
						* triangularWave(millis(), periodMs);
		break;
	default:
		return -1;
	}

	if (_this->currentStrobeType != SINUSOIDAL_STROBE
			&& _this->currentStrobeType != LINEAR_STROBE) {
		_this->pHostSystem->lightDriver.toggleState();
	} else {
		_this->pHostSystem->lightDriver.setLevel(
				nextPotentiometerLevel);
		nextIntervalMs = LEVEL_REFRESH_INTERVAL_MS;
	}

	return MsToTaskTime(nextIntervalMs);
}

float StrobeMode::triangularWave(uint32_t millis, uint32_t periodMs) {
	millis = millis % periodMs;
	if (millis < periodMs / 2) {
		return static_cast<float>(millis) / (periodMs / 2);
	} else {
		return static_cast<float>(-(millis - periodMs)) / (periodMs / 2);
	}
}

float StrobeMode::sinWave(uint32_t millis, uint32_t periodMs) {
	return sin(millis * 2.0 * PI / periodMs) + 1.0f;
}
