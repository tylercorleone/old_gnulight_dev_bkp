#ifndef GNULIGHT_H
#define GNULIGHT_H

#include <stdint.h>
#include <stddef.h>
#include <Task.h>

#include "Components.h"
#include "BatteryMonitor.h"
#include "LightMonitor.h"
#include "Button.h"
#include "ConstantLightMode.h"
#include "defines.h"
#include "Dimmable.h"
#include "LightDriver.h"
#include "LithiumBattery.h"
#include "ParameterCheckMode.h"
#include "PowerOffMode.h"
#include "StrobeMode.h"

class Gnulight : public TaskManager {
	friend class Button;
	friend class UserInteractionMonitor;
	friend class GnulightMode;
	friend class PowerOffMode;
	friend class ConstantLightMode;
	friend class StrobeMode;
	friend class ParameterCheckMode;
public:
	Gnulight();
	void Setup();
	void switchPower(OnOffState state);
	void enterMode(GnulightMode& mode);
	void enterMode(GnulightMode& mode, ButtonInteraction* interaction);
	void enterMode(GnulightMode& mode, const char* msg);
	void interpretUserInteraction(ButtonInteraction& interaction);
	void EnterSleep();
protected:
	static void buttonStateChangeISR();
	void handleFallbackInteraction();
	void handleFallbackInteraction(ButtonInteraction& interaction);
	void handleFallbackInteraction(const char* msg);
	static void emptyBatteryCallback();
	static Button *staticButton;
	Button button {this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	LithiumBattery battery {4.17, 2.8, 3.2, 0.053, BATTERY_SENSING_PIN, 1};
	LightDriver lightDriver {this, TEMPERATURE_SENSING_PIN};
	Dimmable<float> *batteryLevelObservers[1] = {&lightMonitor};
	BatteryMonitor batteryMonitor {&battery, BATTERY_LEVEL_MONITORING_INTERVAL_MS, emptyBatteryCallback, batteryLevelObservers};
	LightMonitor lightMonitor { &lightDriver };
	GnulightMode* currentMode = nullptr;
	PowerOffMode powerOffMode {this, "PowerOffMode"};
	ConstantLightMode constantLightMode {this, "ConstLightMode"};
	StrobeMode strobeMode {this, "StrobeMode"};
	ParameterCheckMode parameterCheckMode {this, "ParCheckMode"};
};

#endif
