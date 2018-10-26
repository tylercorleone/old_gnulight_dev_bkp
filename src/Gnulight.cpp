#include "Gnulight.h"
#include <LowPower.h>

#include <avr/power.h>
#include "UserInteractionMonitor.h"

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
	staticGnulight = this;
	advancedLightDriver.setup();
	StartTask(&batteryMonitor);
	enterMode(powerOffMode);

#ifndef INFO
	power_usart0_disable(); // 0.1 mA (28.7 mA)
#endif
}

void Gnulight::switchPower(PowerState state) {
	info(
			"Glht::switchPower " + (state == POWER_STATE_ON ? "ON" : "OFF"));
	if (state == POWER_STATE_ON) {
		digitalWrite(DEVICES_VCC_PIN, HIGH);
		internalLifecycleState = LIFECYCLE_STATE_ON;
		info("---\nHERE GNULIGHT\n---");
	} else {
		advancedLightDriver.switchLightStatus(LightStatus::OFF);
		// StopAllTasks();
		digitalWrite(DEVICES_VCC_PIN, LOW);
		internalLifecycleState = LIFECYCLE_STATE_OFF;
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
	if (staticGnulight->internalLifecycleState == LIFECYCLE_STATE_SHUTTING_DOWN) {
		trace("Already shutting down");
		return;
	}
	info("Batt. is empty");
	staticGnulight->internalLifecycleState = LIFECYCLE_STATE_SHUTTING_DOWN;
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
