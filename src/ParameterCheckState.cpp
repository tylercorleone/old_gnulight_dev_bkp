#include "ParameterCheckState.h"
#include "Gnulight.h"

const char *ParameterCheckState::BATTERY_CHECK = "b";
const char *ParameterCheckState::LAMP_TEMPERATURE_CHECK = "t";

ParameterCheckState::ParameterCheckState(Gnulight *gnulight) :
		State("parCheckState"), gnulight(gnulight) {
}

bool ParameterCheckState::onEnterState(const Event &event) {
	float parameterValue;

	if (event.isMessage(BATTERY_CHECK)) {
		parameterValue = round(
				gnulight->battery.getRemainingCharge() * 10);
	} else if (event.isMessage(LAMP_TEMPERATURE_CHECK)) {
		parameterValue = gnulight->lightDriver.getEmitterTemperature()
				/ 10.0f;
	} else {
		return false;
	}

	strobesForIntegerPartCount = (int8_t) parameterValue;
	strobesForDecimalPartCount = round(parameterValue * 10.0f) % 10;

	traceIfNamed("%s value: %f", event.getMessage(), parameterValue);

	gnulight->lightDriver.setState(OnOffState::OFF); // light could be ON!
	gnulight->lightDriver.setMainLevel(MainLightLevel::MED);
	gnulight->StartTask(&renderValueWithFlashes);

	return true;
}

void ParameterCheckState::onExitState() {
	gnulight->StopTask(&renderValueWithFlashes);
}

uint32_t ParameterCheckState::switchLightStatus(ParameterCheckState *_this) {
	if (_this->strobesForIntegerPartCount <= 0
			&& _this->strobesForDecimalPartCount == 0) {

		_this->gnulight->enterState(
				_this->gnulight->powerOffState);
		return 0;
	}

	_this->gnulight->lightDriver.toggleState();

	int8_t *pCounter;
	float intervalMultiplier;

	if (_this->strobesForIntegerPartCount >= 0) {

		/*
		 * Is an integer or the comma
		 */
		pCounter = &_this->strobesForIntegerPartCount;

		if (_this->strobesForIntegerPartCount == 0
				&& _this->gnulight->lightDriver.getState()
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

	if (_this->gnulight->lightDriver.getState() == OnOffState::OFF) {
		--*pCounter;
		intervalMultiplier = 1.0f - intervalMultiplier;
	}

	return MsToTaskTime(SIGNAL_STROBE_INTERVAL_MS * intervalMultiplier);
}
