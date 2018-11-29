#ifndef GNULIGHT_H
#define GNULIGHT_H

#include "gnulight_config.h"

#include <Components.h>

#include "BatteryMonitor.h"
#include "ConstantLightMode.h"
#include "LightDriver.h"
#include "ParameterCheckMode.h"
#include "PowerOffMode.h"
#include "StrobeMode.h"
#include "TempMonitor.h"

class GnulightBuilder;

class Gnulight : public GenericDevice {
	friend class GnulightBuilder;
	friend class TempMonitor;
	friend class BatteryMonitor;
	friend class PowerOffMode;
	friend class ConstantLightMode;
	friend class StrobeMode;
	friend class ParameterCheckMode;
public:
	Gnulight();
private:
	void setup();
	void switchPower(OnOffState state);
	void EnterSleep();
	static void buttonStateChangeISR();
	static Button *staticButton;

	/*
	 * Components
	 */
	Button button { *this, BUTTON_PIN, staticButton, buttonStateChangeISR};
	LedCurrentPotentiometer currentPotentiometer { *this };
	LightDriver lightDriver { currentPotentiometer, *this };

	// optional components
	BatteryMonitor *batteryMonitor = nullptr;
	TempMonitor *tempMonitor = nullptr;

	/*
	 * Modes
	 */
	PowerOffMode powerOffMode {*this};
	ConstantLightMode constantLightMode {*this};
	StrobeMode strobeMode {*this};
	ParameterCheckMode parameterCheckMode {*this};
};

#include "GnulightBuilder.h"

#endif
