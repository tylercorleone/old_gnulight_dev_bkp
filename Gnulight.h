#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "defines.h"
#include "Button.h"
#include "LithiumBattery.h"
#include "Task.h"

#include "AdvancedLightDriver.h"
#include "UserInteractionMonitorTask.h"
#include "LightMonitorTask.h"
#include "PowerOffMode.h"
#include "ConstantLightMode.h"
#include "LithiumBatteryMonitor.h"
#include "StrobeMode.h"
#include "ParameterCheckMode.h"

typedef enum PowerState {
	POWER_STATE_ON, POWER_STATE_OFF
} PowerState;

class Gnulight : public TaskManager {
	typedef enum InternalLifecycleState {
		LIFECYCLE_STATE_UNKNOWN, LIFECYCLE_STATE_BOOTSTRAPPING, LIFECYCLE_STATE_ON, LIFECYCLE_STATE_SHUTTING_DOWN, LIFECYCLE_STATE_OFF
	} InternalLifecycleState;
	friend class Button;
	friend class UserInteractionMonitorTask;
	friend class GnulightMode;
	friend class PowerOffMode;
	friend class ConstantLightMode;
	friend class StrobeMode;
	friend class ParameterCheckMode;
public:
	Gnulight();
	void Setup();
	void switchPower(PowerState state);
	void enterMode(GnulightMode& mode, ButtonInteraction* interaction = nullptr);
	void enterMode(GnulightMode& mode, const char* msg);
	void interpretUserInteraction(ButtonInteraction& interaction);
	void EnterSleep();
protected:
	static void buttonStateChangeISR();
	void handleFallbackInteraction(ButtonInteraction& interaction);
	void handleFallbackInteraction(const char* msg);
	static void emptyBatteryCallback();
	InternalLifecycleState internalLifecycleState = LIFECYCLE_STATE_UNKNOWN;
	static Button *staticButton;
	Button button {this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	LithiumBattery battery {4.2, 2.8, 3.2, 0.053, BATTERY_SENSING_PIN, 1};
	AdvancedLightDriver lightDriver {TEMPERATURE_SENSING_PIN};
	UserInteractionMonitorTask uiMonitor {MsToTaskTime(10), this};
	LightMonitorTask lightMonitorTask {&lightDriver};
	Dimmable<float> *recipientsToDimForCauseBattery[1] = {&lightMonitorTask};
	LithiumBatteryMonitor batteryMonitor {&battery, BATTERY_LEVEL_MONITORING_INTERVAL_MS, emptyBatteryCallback, recipientsToDimForCauseBattery};

	GnulightMode* currentMode = nullptr;
	PowerOffMode powerOffMode {"PowerOffMode", this};
	ConstantLightMode constantLightMode {"ConstantLightMode", this};
	StrobeMode strobeMode {"StrobeMode", this};
	ParameterCheckMode parameterCheckMode {"ParameterCheckMode", this};
};

#endif
