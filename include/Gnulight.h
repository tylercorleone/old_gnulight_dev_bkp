#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "gnulight_config.h"

#include <Components.h>

#include "BatteryMonitor.h"
#include "LightMonitor.h"
#include "ConstantLightState.h"
#include "LightDriver.h"
#include "ParameterCheckState.h"
#include "PowerOffState.h"
#include "StrobeState.h"


#include "GnulightBuilder.h"

class GnulightBuilder;

class Gnulight : public System {
	friend class PowerOffState;
	friend class ConstantLightState;
	friend class StrobeState;
	friend class ParameterCheckState;
	friend class LightMonitor;
public:
	Gnulight();
	void Setup();
	void switchPower(OnOffState state);
	void EnterSleep();
protected:
	friend class GnulightBuilder;
	static void buttonStateChangeISR();
	static Button *staticButton;
	Button button {this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	Battery *battery = nullptr;
	LightDriver lightDriver {this, TEMPERATURE_SENSING_PIN};
	BatteryMonitor *batteryMonitor = nullptr;
	LightMonitor lightMonitor { this };
	State *currentState = nullptr;
	PowerOffState powerOffState {this};
	ConstantLightState constantLightState {this};
	StrobeState strobeState {this};
	ParameterCheckState parameterCheckState {this};
};

#endif
