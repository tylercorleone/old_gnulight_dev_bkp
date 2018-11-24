#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>

#define INFO
#define DEBUG
#define TRACE

/**********   PIN MAPPING   **********/
#define BUTTON_PIN 2
#define DEVICES_VCC_PIN 5
#define LED_PIN 9

#define BATTERY_SENSING_PIN A2
#define TEMPERATURE_SENSING_PIN A1

/************************************/
#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.00035f

/**********   TIMING   **********/
#define BATTERY_LEVEL_MONITORING_INTERVAL_MS 5000
#define LIGHT_LEVEL_MONITORING_INTERVAL_MS 10000
#define ACTUATOR_INTERVAL_MS MsToTaskTime(30)

#ifdef INFO
#define WDTO_X WDTO_2S
#else
#define WDTO_X WDTO_500MS
#endif

inline float readBatterVoltage() {
	analogRead(BATTERY_SENSING_PIN);
	return 5.0f * analogRead(BATTERY_SENSING_PIN) / 1023;
}

#include <Components.h>

#endif
