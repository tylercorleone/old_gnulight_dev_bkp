#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include "../lib/Components/src/Components.h"

/**********   PIN MAPPING   **********/
#define BUTTON_PIN 2
#define DEVICES_VCC_PIN 5
#define LED_PIN 9

#define BATTERY_SENSING_PIN A2
#define TEMPERATURE_SENSING_PIN A1
#define CURRENT_SENSING_PIN A3

/************************************/
#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.00035f

/**********   TIMING   **********/
#define BATTERY_LEVEL_MONITORING_INTERVAL_MS 5000
#define LIGHT_LEVEL_MONITORING_INTERVAL_MS 10000
#define LOG_DELAY 5000UL

#endif
