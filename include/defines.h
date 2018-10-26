#ifndef DEFINITIONS_H
#define DEFINITIONS_H

// #define INFO
// #define DEBUG
// #define TRACE

#include <Arduino.h>

/**********   PIN MAPPING   **********/
#define BUTTON_PIN 2
#define DEVICES_VCC_PIN 5
#define LED_PIN 9

#define BATTERY_SENSING_PIN A2
#define TEMPERATURE_SENSING_PIN A1
#define CURRENT_SENSING_PIN A3

/************************************/
#define MIN_LIGHT_CURRENT_ABOVE_ZERO 0.002f

/**********   TIMING   **********/
#define BATTERY_LEVEL_MONITORING_INTERVAL_MS 5000
#define LIGHT_LEVEL_MONITORING_INTERVAL_MS 10000
#define CONSECUTIVE_CLICKS_MAX_DELAY 600L
#define BUTTON_HOLD_BEGIN_THRESHOLD_MS 800L
#define HOLD_CYCLE_DURATION_MS 1200UL
#define LOG_DELAY 5000UL

#ifdef INFO
#define info(string) Serial.println(String("") + string); Serial.flush()
#define WDTO_X 6 // -> WDTO_1S
#ifdef DEBUG
#define debug(string) Serial.println(String("") + string); Serial.flush()
#ifdef TRACE
#define trace(string) Serial.println(String("") + string); Serial.flush()
#else
#define trace(string)
#endif
#else
#define debug(string)
#define trace(string)
#endif
#else
#define WDTO_X
#define info(string)
#define trace(string)
#define debug(string)
#endif

#endif
