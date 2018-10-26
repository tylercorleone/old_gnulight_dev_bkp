#include "ParameterCheckMode.h"
#include "Gnulight.h"

bool ParameterCheckMode::onEnterMode(const char* msg) {
	info(modeName + "::onEnterMode");
	float parameterValue;
	switch (*msg) {
	case BATTERY_CHECK:
		parameterValue =
				static_cast<int8_t>(pHostSystem->battery.getRemainingCharge()
						* 10);
		break;
	case LAMP_TEMPERATURE_CHECK:
		parameterValue =
				pHostSystem->advancedLightDriver.getEmitterTemperature()
						/ 10.0f;
		break;
	default:
		return false;
	}
	strobesForIntegerPartCount = static_cast<int8_t>(parameterValue);
	strobesForDecimalPartCount = static_cast<int8_t>(round(
			parameterValue * 10.0f)) % 10;
	debug(*msg + " value " + parameterValue);
	pHostSystem->advancedLightDriver.setMainLevel(MainLightLevel::MED);
	pHostSystem->advancedLightDriver.switchLightStatus(LightStatus::OFF);
	pHostSystem->StartTask(&renderValueWithFlashes);
	return true;
}

void ParameterCheckMode::onExitMode() {
	info(modeName + "::onExitMode");
	pHostSystem->StopTask(&renderValueWithFlashes);
}

uint32_t ParameterCheckMode::switchLightStatus(ParameterCheckMode* _this) {
	if (_this->strobesForDecimalPartCount == 0
			&& (_this->strobesForIntegerPartCount == -1
					|| _this->strobesForIntegerPartCount == 0)) {
		_this->pHostSystem->enterMode(_this->pHostSystem->powerOffMode);
		return -1;
	}
	uint32_t interval;
	if (_this->strobesForIntegerPartCount > 0) {
		if (_this->pHostSystem->advancedLightDriver.getLightStatus()
				== LightStatus::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForIntegerPartCount;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else if (_this->strobesForIntegerPartCount == 0) {
		if (_this->pHostSystem->advancedLightDriver.getLightStatus()
				== LightStatus::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * COMMA_SIGNAL_DUTY_CYCLE);
		} else {
			_this->strobesForIntegerPartCount = -1;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else {
		if (_this->pHostSystem->advancedLightDriver.getLightStatus()
				== LightStatus::OFF) {
			interval = MsToTaskTime(
					SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForDecimalPartCount;
			interval =
					MsToTaskTime(
							SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	}
	_this->pHostSystem->advancedLightDriver.toggleLightStatus();
	return interval;
}
