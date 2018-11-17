#include "Gnulight.h"
#include <LowPower.h>
#include <avr/power.h>


Gnulight *staticGnulight;

#define USE_WDT

Button *Gnulight::staticButton;

Gnulight::Gnulight() {
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
	enterMode(powerOffMode);

#ifndef INFO
	power_usart0_disable(); // 0.1 mA (28.7 mA)
#endif
}

void Gnulight::switchPower(OnOffState state) {
	info(
			"Glht::switchPower " + (state == OnOffState::ON ? "ON" : "OFF"));
	if (state == OnOffState::ON) {
		digitalWrite(DEVICES_VCC_PIN, HIGH);
		info("---\nHERE GNULIGHT\n---");
	} else {
		lightDriver.setState(OnOffState::OFF);
		digitalWrite(DEVICES_VCC_PIN, LOW);
		info("---\nGOODBYE\n---");
		EnterSleep();
	}
}

void Gnulight::enterMode(GnulightMode& mode) {
	debug("Glht::enterMode " + mode.getModeName());
	if (currentMode != nullptr) {
		currentMode->onExitMode();
	}
	currentMode = &mode;
	if (!mode.onEnterMode()) {
		handleFallbackInteraction();
	}
}

void Gnulight::enterMode(GnulightMode& mode, ButtonInteraction* interaction) {
	debug("Glht::enterMode " + mode.getModeName());
	if (currentMode != nullptr) {
		currentMode->onExitMode();
	}
	currentMode = &mode;
	if (!mode.onEnterMode(interaction)) {
		handleFallbackInteraction(*interaction);
	}
}

void Gnulight::enterMode(GnulightMode& mode, const char* msg) {
	debug("Glht::enterMode " + mode.getModeName());
	currentMode->onExitMode();
	currentMode = &mode;
	if (!mode.onEnterMode(msg)) {
		handleFallbackInteraction(msg);
	}
}

void Gnulight::interpretUserInteraction(ButtonInteraction& interaction) {
	debug(
			"Btn interaction. " + interaction.getClicksCount() + " clicks, " + interaction.getHoldStepsCount() + " hold steps");
	if (!currentMode->interpretUserInteraction(interaction)) {
		handleFallbackInteraction(interaction);
	}
}

void Gnulight::handleFallbackInteraction() {
	debug(currentMode->getModeName() + " couldn't handle interaction");
	enterMode(powerOffMode);
}

void Gnulight::handleFallbackInteraction(ButtonInteraction& interaction) {
	debug(
			currentMode->getModeName() + " couldn't handle interaction. " + interaction.getClicksCount() + " clicks, " + interaction.getHoldStepsCount() + " hold steps");
	enterMode(powerOffMode);
}

void Gnulight::handleFallbackInteraction(const char* msg) {
	debug(
			currentMode->getModeName() + " couldn't handle msg " + String(msg));
	enterMode(powerOffMode);
}

void Gnulight::buttonStateChangeISR() {
	staticButton->statusChangeCallback();
}

void Gnulight::emptyBatteryCallback() {
	if (staticGnulight->currentMode == &staticGnulight->parameterCheckMode) {
		return;
	}
	info("Batt. is empty");
	staticGnulight->enterMode(staticGnulight->parameterCheckMode,
			&BATTERY_CHECK);
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
