#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "defines.h"
#include "Button.h"
#include "LithiumBattery.h"
#include "Task.h"

#include "AdvancedLightDriver.h"
#include "BatteryMonitor.h"
#include "PowerOffMode.h"
#include "ConstantLightMode.h"
#include "StrobeMode.h"
#include "ParameterCheckMode.h"
#include "UserInteractionMonitor.h"

typedef enum PowerState {
	POWER_STATE_ON, POWER_STATE_OFF
} PowerState;

class Gnulight : public TaskManager {
	typedef enum InternalLifecycleState {
		LIFECYCLE_STATE_UNKNOWN, LIFECYCLE_STATE_BOOTSTRAPPING, LIFECYCLE_STATE_ON, LIFECYCLE_STATE_SHUTTING_DOWN, LIFECYCLE_STATE_OFF
	} InternalLifecycleState;
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
	void switchPower(PowerState state);
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
	InternalLifecycleState internalLifecycleState = LIFECYCLE_STATE_UNKNOWN;
	static Button *staticButton;
	Button button {this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	LithiumBattery battery {4.2, 2.8, 3.2, 0.053, BATTERY_SENSING_PIN, 1};
	AdvancedLightDriver advancedLightDriver {this, TEMPERATURE_SENSING_PIN};
	Dimmable<float> *batteryLevelObservers[1] = {&advancedLightDriver};
	BatteryMonitor batteryMonitor {&battery, BATTERY_LEVEL_MONITORING_INTERVAL_MS, emptyBatteryCallback, batteryLevelObservers};
	GnulightMode* currentMode = nullptr;
	PowerOffMode powerOffMode {this, "PowerOffMode"};
	ConstantLightMode constantLightMode {this, "ConstLightMode"};
	StrobeMode strobeMode {this, "StrobeMode"};
	ParameterCheckMode parameterCheckMode {this, "ParCheckMode"};
};

#endif
