#ifndef PARAMETERCHECKSTATE_H
#define PARAMETERCHECKSTATE_H

#include <FunctionsSequenceTask.h>
#include <HostSystemAware.h>
#include <State.h>

class Gnulight;

#define SIGNAL_STROBE_INTERVAL_MS 800UL
#define DIGIT_SIGNAL_DUTY_CYCLE 0.15f
#define COMMA_SIGNAL_DUTY_CYCLE 1.0f

class ParameterCheckState: public State, public HostSystemAware<Gnulight> {
public:
	static const char *BATTERY_CHECK;
	static const char *LAMP_TEMPERATURE_CHECK;

	ParameterCheckState(Gnulight *gnulight);
protected:
	bool onEnterState(const Event &event) override;
	void onExitState() override;
	static uint32_t switchLightStatus(ParameterCheckState *_this);
	FunctionsSequenceTask& renderValueWithFlashes = SequenceTaskBuilder::begin(
			ParameterCheckState::switchLightStatus, this).thenRepeat();
	int8_t strobesForIntegerPartCount = 0;
	int8_t strobesForDecimalPartCount = 0;
};

#endif
