#include "GnulightBuilder.h"

GnulightBuilder::GnulightBuilder(Gnulight *instance) :
		instance(instance) {

}

GnulightBuilder GnulightBuilder::configureGnulight() {
	return GnulightBuilder { new Gnulight() };
}

GnulightBuilder GnulightBuilder::setBatteryMonitor(
		BatteryMonitor *batteryMonitor) {
	instance->batteryMonitor = batteryMonitor;
	return *this;
}

GnulightBuilder GnulightBuilder::setBattery(Battery *battery) {
	instance->battery = battery;
	return *this;
}

Gnulight* GnulightBuilder::build() {
	return instance;
}
