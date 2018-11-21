#ifndef GNULIGHT_H
#define GNULIGHT_H

#include <Button.h>
#include <System.h>

#include "defines.h"
#include "BatteryMonitor.h"
#include "LightMonitor.h"
#include "ConstantLightState.h"
#include "Dimmable.h"
#include "LightDriver.h"
#include "LithiumBattery.h"
#include "ParameterCheckState.h"
#include "PowerOffState.h"
#include "StrobeState.h"

class Gnulight : public System {
	friend class PowerOffState;
	friend class ConstantLightState;
	friend class StrobeState;
	friend class ParameterCheckState;
	friend class BatteryMonitor;
public:
	Gnulight();
	void Setup();
	void switchPower(OnOffState state);
	void EnterSleep();
protected:
	static void buttonStateChangeISR();
	static Button *staticButton;
	Button button {this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	LithiumBattery battery {2.8, 3.2, 4.17, 0.053, readBatterVoltage};
	LightDriver lightDriver {this, TEMPERATURE_SENSING_PIN};
	Dimmable<float> *batteryLevelObservers[1] = {&lightMonitor};
	BatteryMonitor batteryMonitor {this, BATTERY_LEVEL_MONITORING_INTERVAL_MS, batteryLevelObservers};
	LightMonitor lightMonitor { &lightDriver };
	State *currentState = nullptr;
	PowerOffState powerOffState {this};
	ConstantLightState constantLightState {this};
	StrobeState strobeState {this};
	ParameterCheckState parameterCheckState {this};
};

#endif
