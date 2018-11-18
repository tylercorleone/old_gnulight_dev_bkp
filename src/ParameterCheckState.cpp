#include <string.h>
#include "ParameterCheckState.h"
#include "Gnulight.h"

const char *ParameterCheckState::BATTERY_CHECK = "b";
const char *ParameterCheckState::LAMP_TEMPERATURE_CHECK = "t";

bool ParameterCheckState::onEnterState(const Event &event) {
	info("PCM::onEnterMode");

	float parameterValue;

	if (event.isMessage(BATTERY_CHECK)) {
		parameterValue =
				static_cast<int8_t>(getHostSystem()->battery.getRemainingCharge()
						* 10);
	} else if (event.isMessage(LAMP_TEMPERATURE_CHECK)) {
		parameterValue =
				getHostSystem()->lightDriver.getEmitterTemperature()
						/ 10.0f;
	} else {
		return false;
	}

	strobesForIntegerPartCount = static_cast<int8_t>(parameterValue);
	strobesForDecimalPartCount = static_cast<int8_t>(round(
			parameterValue * 10.0f)) % 10;
	debug("%s value: %f",event.getMessage(), parameterValue);
	getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MED);
	getHostSystem()->lightDriver.setState(OnOffState::OFF);
	getHostSystem()->StartTask(&renderValueWithFlashes);
	return true;
}

void ParameterCheckState::onExitState() {
	info("PCM::onExitMode");
	getHostSystem()->StopTask(&renderValueWithFlashes);
}

uint32_t ParameterCheckState::switchLightStatus(ParameterCheckState* _this) {
	if (_this->strobesForDecimalPartCount == 0
			&& (_this->strobesForIntegerPartCount == -1
					|| _this->strobesForIntegerPartCount == 0)) {
		_this->getHostSystem()->enterState(_this->getHostSystem()->powerOffState);
		return -1;
	}
	uint32_t interval;
	if (_this->strobesForIntegerPartCount > 0) {
		if (_this->getHostSystem()->lightDriver.getState()
				== OnOffState::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForIntegerPartCount;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else if (_this->strobesForIntegerPartCount == 0) {
		if (_this->getHostSystem()->lightDriver.getState()
				== OnOffState::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * COMMA_SIGNAL_DUTY_CYCLE);
		} else {
			_this->strobesForIntegerPartCount = -1;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else {
		if (_this->getHostSystem()->lightDriver.getState()
				== OnOffState::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForDecimalPartCount;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	}
	_this->getHostSystem()->lightDriver.toggleState();
	return interval;
}
