#include "GnulightBuilder.h"

GnulightBuilder::GnulightBuilder(Gnulight *instance) :
		instance(instance) {

}

GnulightBuilder GnulightBuilder::configureGnulight() {
	return GnulightBuilder { new Gnulight() };
}

GnulightBuilder GnulightBuilder::setTemperatureReadFunction(
		float (*temperatureReadFunction)()) {
	instance->tempMonitor = new TempMonitor(*instance,
			temperatureReadFunction);
	return *this;
}

GnulightBuilder GnulightBuilder::setBattery(Battery &battery) {
	instance->batteryMonitor = new BatteryMonitor(*instance, battery);
	return *this;
}

Gnulight* GnulightBuilder::build() {
	instance->setup();
	return instance;
}
