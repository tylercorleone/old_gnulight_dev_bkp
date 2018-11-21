#include "Gnulight.h"
#include <LowPower.h>
#include <avr/power.h>

#define USE_WDT

Button *Gnulight::staticButton;

Gnulight::Gnulight() :
		System(&powerOffState) {
	trace("Inst. Glht");
}

void Gnulight::Setup() {
	trace("Glht::setup");

	button.setInstanceName("btn");
	TaskManager::Setup();
	pinMode(BATTERY_SENSING_PIN, INPUT);
	lightDriver.setup();
	StartTask(&batteryMonitor);
	enterState(powerOffState);

#ifndef INFO
	power_usart0_disable(); // 0.1 mA (28.7 mA)
#endif
}

void Gnulight::switchPower(OnOffState state) {
	info("Glht::switchPower %s", state == OnOffState::ON ? "ON" : "OFF");

	if (state == OnOffState::ON) {
		info("---\nHERE GNULIGHT\n---");
		digitalWrite(DEVICES_VCC_PIN, HIGH);
	} else {
		digitalWrite(DEVICES_VCC_PIN, LOW);
		info("---\nGOODBYE\n---");
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
	wdt_enable(WDTO_500MS);
#endif
}
