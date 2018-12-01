#include "Gnulight.h"

Gnulight::Gnulight(BrightnessDriver &brightnessDriver, const char *deviceName) :
		GenericDevice(deviceName, &powerOffMode), brightnessDriver(
				brightnessDriver) {

}

void Gnulight::onSetup() {
	button.setName("btn");
	enterState(powerOffMode);
}

void Gnulight::switchPower(OnOffState state) {
	infoIfNamed("switchPower(%s)", state == OnOffState::ON ? "ON" : "OFF");

	if (state == OnOffState::ON) {
		infoIfNamed("HERE GNULIGHT");
		onPowerOn();
		if (batteryMonitor != nullptr) {
			StartTask(batteryMonitor);
		}
		if (tempMonitor != nullptr) {
			StartTask(tempMonitor);
		}
	} else {
		if (batteryMonitor != nullptr) {
			StopTask(batteryMonitor);
		}
		if (tempMonitor != nullptr) {
			StopTask(tempMonitor);
		}infoIfNamed("GOODBYE");
		onPowerOff();
	}
}

void Gnulight::onPowerOn() {

}

void Gnulight::onPowerOff() {

}
