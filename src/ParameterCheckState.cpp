#include <string.h>
#include "ParameterCheckState.h"
#include "Gnulight.h"

const char *ParameterCheckState::BATTERY_CHECK = "b";
const char *ParameterCheckState::LAMP_TEMPERATURE_CHECK = "t";

ParameterCheckState::ParameterCheckState(Gnulight *gnulight) :
		HostSystemAware(gnulight) {
}

bool ParameterCheckState::onEnterState(const Event &event) {
	info("PCM::onEnterMode");

	float parameterValue;

	if (event.isMessage(BATTERY_CHECK)) {
		parameterValue = round(
				getHostSystem()->battery.getRemainingCharge() * 10);
	} else if (event.isMessage(LAMP_TEMPERATURE_CHECK)) {
		parameterValue = getHostSystem()->lightDriver.getEmitterTemperature()
				/ 10.0f;
	} else {
		return false;
	}

	strobesForIntegerPartCount = (int8_t) parameterValue;
	strobesForDecimalPartCount = round(parameterValue * 10.0f) % 10;

	debug("%s value: %f", event.getMessage(), parameterValue);

	getHostSystem()->lightDriver.setState(OnOffState::OFF); // light could be ON!
	getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MED);
	getHostSystem()->StartTask(&renderValueWithFlashes);

	return true;
}

void ParameterCheckState::onExitState() {
	info("PCM::onExitMode");

	getHostSystem()->StopTask(&renderValueWithFlashes);
}

uint32_t ParameterCheckState::switchLightStatus(ParameterCheckState *_this) {

	if (_this->strobesForIntegerPartCount <= 0
			&& _this->strobesForDecimalPartCount == 0) {

		_this->getHostSystem()->enterState(
				_this->getHostSystem()->powerOffState);
		return 0;
	}

	_this->getHostSystem()->lightDriver.toggleState();

	int8_t *pCounter;
	float intervalMultiplier;

	if (_this->strobesForIntegerPartCount >= 0) {

		/*
		 * Is an integer or the comma
		 */
		pCounter = &_this->strobesForIntegerPartCount;

		if (_this->strobesForIntegerPartCount == 0
				&& _this->getHostSystem()->lightDriver.getState()
						== OnOffState::ON) {
			intervalMultiplier = COMMA_SIGNAL_DUTY_CYCLE;
		} else {
			intervalMultiplier = DIGIT_SIGNAL_DUTY_CYCLE;
		}

	} else {

		/*
		 * Is a decimal
		 */
		pCounter = &_this->strobesForDecimalPartCount;
		intervalMultiplier = DIGIT_SIGNAL_DUTY_CYCLE;
	}

	if (_this->getHostSystem()->lightDriver.getState() == OnOffState::OFF) {
		--*pCounter;
		intervalMultiplier = 1.0f - intervalMultiplier;
	}

	return MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * intervalMultiplier);
}
