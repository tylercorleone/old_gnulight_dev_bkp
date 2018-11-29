#include "Gnulight.h"
#include <LowPower.h>
#include <avr/power.h>

#define USE_WDT

Button *Gnulight::staticButton;

Gnulight::Gnulight() :
		GenericDevice("Gnulight", &powerOffMode) {

}

void Gnulight::setup() {
	traceIfNamed("setup");

	button.setInstanceName("btn");
	TaskManager::Setup();
	pinMode(BATTERY_SENSING_PIN, INPUT);
	currentPotentiometer.setup();
	lightDriver.setup();
	if (batteryMonitor != nullptr) {
		StartTask(batteryMonitor);
	}
	if (tempMonitor != nullptr) {
		StartTask(tempMonitor);
	}
	enterState(powerOffMode);

#ifndef INFO
	power_usart0_disable(); // 0.1 mA (28.7 mA)
#endif
}

void Gnulight::switchPower(OnOffState state) {
	infoIfNamed("switchPower(%s)", state == OnOffState::ON ? "ON" : "OFF");

	if (state == OnOffState::ON) {
		infoIfNamed("HERE GNULIGHT");
		digitalWrite(DEVICES_VCC_PIN, HIGH);
	} else {
		digitalWrite(DEVICES_VCC_PIN, LOW);
		infoIfNamed("GOODBYE");
		EnterSleep();
	}
}

void Gnulight::buttonStateChangeISR() {
	staticButton->statusChangeCallback();
}

void Gnulight::EnterSleep() {
#if defined(USE_WDT)
	// disable watchdog so it doesn't wake us up
	wdt_reset();
	wdt_disable();
#endif

	LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

#if defined(USE_WDT)
	// enable watch dog after wake up
	wdt_reset();
	wdt_enable(WDTO_X);
#endif
}
