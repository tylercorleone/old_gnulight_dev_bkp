#include "ParameterCheckMode.h"
#include "Gnulight.h"

ParameterCheckMode::ParameterCheckMode(const char* className,
		Gnulight* gnulight) :
		GnulightMode(className, gnulight) {
	trace(className + "::" + className);
	pRenderValueWithFlashes = new FunctionsSequenceTask(ParameterCheckMode::switchLightStatus, this);
	pRenderValueWithFlashes->thenRepeat();
}

bool ParameterCheckMode::onEnterMode(const char* msg) {
	info(className + "::onEnterMode");
	float parameterValue;
	switch (*msg) {
	case BATTERY_CHECK:
		parameterValue = static_cast<int8_t>(pSystem->battery.getRelativeCapacity() * 10);
		break;
	case LAMP_TEMPERATURE_CHECK:
		parameterValue = pSystem->lightDriver.getTemperature() / 10.0f;
		break;
	default:
		return false;
	}
	strobesForIntegerPartCount = static_cast<int8_t>(parameterValue);
	strobesForDecimalPartCount = static_cast<int8_t>(round(parameterValue * 10.0f)) % 10;
	debug(*msg + " value " + parameterValue);
	pSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MED);
	pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_OFF);
	pSystem->StartTask(pRenderValueWithFlashes);
	return true;
}

void ParameterCheckMode::onExitMode() {
	info(className + "::onExitMode");
	pSystem->StopTask(pRenderValueWithFlashes);
}

uint32_t ParameterCheckMode::switchLightStatus(ParameterCheckMode* _this) {
	if (_this->strobesForDecimalPartCount == 0
			&& (_this->strobesForIntegerPartCount == -1
					|| _this->strobesForIntegerPartCount == 0)) {
		_this->pSystem->enterMode(_this->pSystem->powerOffMode);
		return -1;
	}
	uint32_t interval;
	if (_this->strobesForIntegerPartCount > 0) {
		if (_this->pSystem->lightDriver.getLightStatus() == LIGHT_STATUS_OFF) {
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForIntegerPartCount;
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else if (_this->strobesForIntegerPartCount == 0) {
		if (_this->pSystem->lightDriver.getLightStatus() == LIGHT_STATUS_OFF) {
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * COMMA_SIGNAL_DUTY_CYCLE);
		} else {
			_this->strobesForIntegerPartCount = -1;
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	} else {
		if (_this->pSystem->lightDriver.getLightStatus() == LIGHT_STATUS_OFF) {
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * DIGIT_SIGNAL_DUTY_CYCLE);
		} else {
			--_this->strobesForDecimalPartCount;
			interval = MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * (1.0f - DIGIT_SIGNAL_DUTY_CYCLE));
		}
	}
	_this->pSystem->lightDriver.toggleLightStatus();
	return interval;
}
