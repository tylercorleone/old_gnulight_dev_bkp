#include "StrobeState.h"
#include "Gnulight.h"

StrobeState::StrobeState(Gnulight* gnulight) :
		State("strobeState"), gnulight(gnulight) {
}

bool StrobeState::onEnterState(const ButtonEvent &event) {
	debugIfNamed("strobe type %d", currentStrobeType);

	varName = gnulight->lightDriver.setMainLevel(LightLevelIndex::MED);

	if (currentStrobeType == SINUSOIDAL_STROBE
			|| currentStrobeType == LINEAR_STROBE) {
		gnulight->lightDriver.setState(OnOffState::ON);
	}

	gnulight->StartTask(&toggleLightStatusTask);
	return true;
}

void StrobeState::onExitState() {
	gnulight->StopTask(&toggleLightStatusTask);
}

bool StrobeState::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			gnulight->enterState(gnulight->powerOffState);
			return true;
		case 2:
			currentStrobeType = (currentStrobeType + 1) % STROBE_TYPES_COUNT;
			debugIfNamed("strobe type %d", currentStrobeType);

			if (currentStrobeType == SINUSOIDAL_STROBE
					|| currentStrobeType == LINEAR_STROBE) {

				LightLevelIndex currentMainLevel =
						gnulight->lightDriver.getCurrentMainLevel();
				varName = gnulight->lightDriver.setMainLevel(
						currentMainLevel);
				gnulight->lightDriver.setState(OnOffState::ON);
			}

			toggleLightStatusTask.setTimeInterval(0);
			gnulight->ResetTask(&toggleLightStatusTask);
			return true;
		case 3:
			if (periodMultiplierX1000 <= 32000) {
				periodMultiplierX1000 *= 2;
			}
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
		varName = gnulight->lightDriver.setNextMainLevel();
		return true;
	} else {
		return false;
	}
}

#define THE_PERIOD (PERIODICAL_SEQUENCE_STROBES_PERIOD_MS * _this->periodMultiplierX1000 / 1000)

uint32_t StrobeState::switchLightStatus(StrobeState* _this) {
	uint32_t nextIntervalMs;
	float nextPotentiometerLevel;

	switch (_this->currentStrobeType) {

	case ON_OFF_STROBE:
		nextIntervalMs = ON_OFF_STROBE_PERIOD_MS / 2
				* _this->periodMultiplierX1000 / 1000;
		break;
	case BEACON_STROBE:
		if (_this->gnulight->lightDriver.getState() == OnOffState::OFF) {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS * BEACON_STROBE_DUTY_CYCLE;
		} else {
			nextIntervalMs = BEACON_STROBE_PERIOD_MS
					* (1.0f - BEACON_STROBE_DUTY_CYCLE);
		}
		break;
	case DISCO_STROBE:
		if (_this->gnulight->lightDriver.getState() == OnOffState::OFF) {
			nextIntervalMs = DISCO_STROBE_PERIOD_MS * DISCO_STROBE_DUTY_CYCLE;
		} else {
			nextIntervalMs = DISCO_STROBE_PERIOD_MS
					* (1.0f - DISCO_STROBE_DUTY_CYCLE);
		}
		break;
	case SINUSOIDAL_STROBE:
		nextIntervalMs = LEVEL_REFRESH_INTERVAL_MS;
		nextPotentiometerLevel = MIN_POTENTIOMETER_LEVEL
				+ (_this->varName - MIN_POTENTIOMETER_LEVEL)
						* (sinWave(millis(), THE_PERIOD));
		break;
	case LINEAR_STROBE:
		nextIntervalMs = LEVEL_REFRESH_INTERVAL_MS;
		nextPotentiometerLevel = MIN_POTENTIOMETER_LEVEL
				+ (_this->varName - MIN_POTENTIOMETER_LEVEL)
						* triangularWave(millis(), THE_PERIOD);
		break;
	default:
		return -1;
	}

	if (_this->currentStrobeType != SINUSOIDAL_STROBE
			&& _this->currentStrobeType != LINEAR_STROBE) {
		_this->gnulight->lightDriver.toggleState();
	} else {
		_this->gnulight->lightDriver.setLevel(nextPotentiometerLevel);
	}

	return MsToTaskTime(nextIntervalMs);
}

#undef THE_PERIOD

float StrobeState::triangularWave(uint32_t millis, uint32_t periodMs) {
	millis = millis % periodMs;
	if (millis < periodMs / 2) {
		return static_cast<float>(millis) / (periodMs / 2);
	} else {
		return static_cast<float>(-(millis - periodMs)) / (periodMs / 2);
	}
}

float StrobeState::sinWave(uint32_t millis, uint32_t periodMs) {
	return (_sin(millis * TWO_PI / periodMs) + 1.0f) / 2.0f;
}
