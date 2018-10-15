#ifndef PARAMETER_CHECK_MODE_H
#define PARAMETER_CHECK_MODE_H

#include "defines.h"
#include "GnulightMode.h"
#include "FunctionsSequenceTask.h"

class AdvancedLightDriver;

#define SIGNAL_STROBE_INTERVAL_MS 500UL
#define DIGIT_SIGNAL_DUTY_CYCLE 0.08f
#define COMMA_SIGNAL_DUTY_CYCLE 0.8f

const char BATTERY_CHECK = 'b';
const char LAMP_TEMPERATURE_CHECK = 't';

class ParameterCheckMode: public GnulightMode {
public:
	ParameterCheckMode(const char*, Gnulight*);
protected:
	bool onEnterMode(const char* msg) override;
	void onExitMode() override;
	static uint32_t switchLightStatus(ParameterCheckMode* _this);
	FunctionsSequenceTask* pRenderValueWithFlashes;
	int8_t strobesForIntegerPartCount = -1;
	int8_t strobesForDecimalPartCount = -1;
};

#endif
