#include "Gnulight.h"

float readBatteryVoltage();
float readTemperature();

Gnulight *gnulight;
LithiumBattery battery {2.8, 3.2, 4.17, 0.053, readBatteryVoltage};


void setup() {
#ifdef INFO
	Serial.begin(9600);
#endif

	gnulight = GnulightBuilder::configureGnulight()
		.setBattery(battery)
		.setTemperatureReadFunction(readTemperature)
		.build();
	
	gnulight->Setup();
}

void loop() {
	gnulight->Loop(WDTO_X);
}

inline float readBatteryVoltage() {
	analogRead(BATTERY_SENSING_PIN);
	return 5.0f * analogRead(BATTERY_SENSING_PIN) / 1023;
}

#define V_OUT (analogRead(TEMPERATURE_SENSING_PIN) * 5.0f / 1023.0f)
#define V_0 0.5
#define T_C 0.01

float readTemperature() {
	analogRead(TEMPERATURE_SENSING_PIN);
	// it is a MCP9700A-E/TO
	return (V_OUT - V_0) / T_C;
}