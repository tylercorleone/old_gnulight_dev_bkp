#include "Gnulight.h"
#include <LowPower.h>
#include <avr/power.h>

Gnulight *staticGnulight;

#define USE_WDT

Button *Gnulight::staticButton;

Gnulight::Gnulight() :
		System(&powerOffState) {
	trace("Inst. Glht");
}

void Gnulight::Setup() {
	trace("Glht::setup");
	TaskManager::Setup();
	pinMode(CURRENT_SENSING_PIN, INPUT);
	pinMode(BATTERY_SENSING_PIN, INPUT);
	staticGnulight = this;
	lightDriver.setup();
	StartTask(&batteryMonitor);
	StartTask(&lightMonitor);
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

void Gnulight::emptyBatteryCallback() {
	if (staticGnulight->currentMode == &staticGnulight->parameterCheckState) {
		return;
	} info("Batt. is empty");
	staticGnulight->enterState(staticGnulight->parameterCheckState, ParameterCheckState::BATTERY_CHECK);
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
