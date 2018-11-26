#include "Gnulight.h"

float readBatterVoltage();
void onEmptyBattery();

Gnulight *gnulight;

void setup() {
#ifdef INFO
	Serial.begin(9600);
#endif

	LithiumBattery *battery = new LithiumBattery(2.8, 3.2, 4.17, 0.053, readBatterVoltage);
	BatteryMonitor *batteryMonitor = new BatteryMonitor(battery, BATTERY_LEVEL_MONITORING_INTERVAL_MS, onEmptyBattery);
	batteryMonitor->setInstanceName("batteryMonitor");

	gnulight = GnulightBuilder::configureGnulight()
		.setBattery(battery)
		.setBatteryMonitor(batteryMonitor)
		.build();
	
	gnulight->Setup();
}

void loop() {
	gnulight->Loop(WDTO_X);
}

inline float readBatterVoltage() {
	analogRead(BATTERY_SENSING_PIN);
	return 5.0f * analogRead(BATTERY_SENSING_PIN) / 1023;
}

void onEmptyBattery() {/*
	if (gnulight->currentState != &gnulight->parameterCheckState) {

		infoIfNamed("Empty battery!");
		gnulight->enterState(gnulight->parameterCheckState, ParameterCheckState::BATTERY_CHECK);
	}*/
}

void setUnusedPinStatus(int mode, int level) {
	// Current (mA) OFF, ON
	
	// INPUT LOW (0.429, 9.04)
	// INPUT HIGH (0.429, 5.12)
	// OUTPUT LOW (0.429, 5.55)
	// OUTPUT HIGH (0.429, 5.12)
	// INPUT_PULLUP LOW (0.429, 9.04)
	// INPUT_PULLUP HIGH (0.429, 5.15)
	
	pinMode(0, mode);
	pinMode(3, mode);
	pinMode(4, mode);
	pinMode(6, mode);
	pinMode(7, mode);
	pinMode(8, mode);
	pinMode(12, mode);

	digitalWrite(0, level);
	digitalWrite(3, level);
	digitalWrite(4, level);
	digitalWrite(6, level);
	digitalWrite(7, level);
	digitalWrite(8, level);
	digitalWrite(12, level);

	pinMode(A0, mode);
	pinMode(A1, mode);
	pinMode(A5, mode);
	pinMode(A6, mode);
	pinMode(A7, mode);

	digitalWrite(A0, level);
	digitalWrite(A1, level);
	digitalWrite(A5, level);
	digitalWrite(A6, level);
	digitalWrite(A7, level);
}
