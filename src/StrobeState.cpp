#include "../include/StrobeState.h"

#include "Gnulight.h"

bool StrobeState::onEnterState(const Event &event) {
	info("SM::onEnterMode");
	debug("SM: strobe type %d", currentStrobeType);
	varName = getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MED);
	if (currentStrobeType == SINUSOIDAL_STROBE
			|| currentStrobeType == LINEAR_STROBE) {
		getHostSystem()->lightDriver.setState(OnOffState::ON);
	}
	getHostSystem()->StartTask(&toggleLightStatusTask);
	return true;
}

void StrobeState::onExitState() {
	info("SM::onExitMode");
	getHostSystem()->StopTask(&toggleLightStatusTask);
}

bool StrobeState::receiveEvent(const Event &event) {
	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			getHostSystem()->enterState(getHostSystem()->powerOffState);
			return true;
		case 2:
			currentStrobeType = (currentStrobeType + 1) % STROBE_TYPES_COUNT;
			debug("SM: strobe type %d", currentStrobeType);

			if (currentStrobeType == SINUSOIDAL_STROBE
					|| currentStrobeType == LINEAR_STROBE) {
				MainLightLevel currentMainLevel =
						getHostSystem()->lightDriver.getCurrentMainLevel();
				varName = getHostSystem()->lightDriver.setMainLevel(
						currentMainLevel);
				getHostSystem()->lightDriver.setState(OnOffState::ON);
			}

			toggleLightStatusTask.setTimeInterval(0);
			getHostSystem()->ResetTask(&toggleLightStatusTask);
			return true;
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
	} else if (event.getHoldStepsCount() > 0) {
		varName = getHostSystem()->lightDriver.setNextMainLevel();
		return true;
	} else {
		return false;
	}
}

uint32_t StrobeState::switchLightStatus(StrobeState* _this) {
	uint32_t nextIntervalMs = 0;
	float nextPotentiometerLevel;
	uint32_t periodMs;

	switch (_this->currentStrobeType) {
	case ON_OFF_STROBE:
		nextIntervalMs = ON_OFF_STROBE_PERIOD_MS / 2
				* _this->periodMultiplierX1000 / 1000;
		break;
	case BEACON_STROBE:
		if (_this->getHostSystem()->lightDriver.getState() == OnOffState::OFF) {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS * BEACON_STROBE_DUTY_CYCLE;
		} else {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS
					* (1.0f - BEACON_STROBE_DUTY_CYCLE);
		}
		break;
	case DISCO_STROBE:
		if (_this->getHostSystem()->lightDriver.getState() == OnOffState::OFF) {
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
		_this->getHostSystem()->lightDriver.toggleState();
	} else {
		_this->getHostSystem()->lightDriver.setLevel(nextPotentiometerLevel);
		nextIntervalMs = LEVEL_REFRESH_INTERVAL_MS;
	}

	return MsToTaskTime(nextIntervalMs);
}

float StrobeState::triangularWave(uint32_t millis, uint32_t periodMs) {
	millis = millis % periodMs;
	if (millis < periodMs / 2) {
		return static_cast<float>(millis) / (periodMs / 2);
	} else {
		return static_cast<float>(-(millis - periodMs)) / (periodMs / 2);
	}
}

float StrobeState::sinWave(uint32_t millis, uint32_t periodMs) {
	return sin(millis * 2.0 * PI / periodMs) + 1.0f;
}