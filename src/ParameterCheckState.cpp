#include "ParameterCheckState.h"
#include "Gnulight.h"

const char *ParameterCheckState::BATTERY_CHECK = "b";
const char *ParameterCheckState::LAMP_TEMPERATURE_CHECK = "t";

ParameterCheckState::ParameterCheckState(Gnulight *gnulight) :
		State("parCheckState"), gnulight(gnulight) {
}

bool ParameterCheckState::onEnterState(const MessageEvent &event) {
	float parameterValue;

	if (event.equals(BATTERY_CHECK) && gnulight->battery != nullptr) {

		parameterValue = round(gnulight->battery->getRemainingCharge() * 10.0f);

	} else if (event.equals(LAMP_TEMPERATURE_CHECK)) {

		parameterValue = gnulight->lightDriver.getEmitterTemperature() / 10.0f;

	} else {
		return false;
	}

	// lets round to the first decimal
	parameterValue = round(parameterValue * 10.0f) / 10.0f;

	// the integer part
	strobesForIntegerPartCount = (int8_t) parameterValue;

	// the decimal part
	strobesForDecimalPartCount = ((int8_t) (parameterValue * 10)) % 10;

	traceIfNamed("%s: %f", event.getMessage(), parameterValue);

	gnulight->lightDriver.setState(OnOffState::OFF); // light could be ON!
	gnulight->lightDriver.setMainLevel(LightLevelIndex::MED);
	gnulight->StartTask(&renderValueWithFlashes);

	return true;
}

void ParameterCheckState::onExitState() {
	gnulight->StopTask(&renderValueWithFlashes);
}

uint32_t ParameterCheckState::switchLightStatus(ParameterCheckState *_this) {
	if (_this->strobesForIntegerPartCount <= 0
			&& _this->strobesForDecimalPartCount == 0) {

		/*
		 * signal finished
		 */
		_this->gnulight->enterState(_this->gnulight->powerOffState);
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
				&& _this->gnulight->lightDriver.getState() == OnOffState::ON) {
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
