#include "GnulightCustomizer.h"

GnulightCustomizer::GnulightCustomizer(Gnulight &instance) :
		instance(instance) {

}

GnulightCustomizer GnulightCustomizer::customize(Gnulight &gnulight) {
	return GnulightCustomizer { gnulight };
}

GnulightCustomizer GnulightCustomizer::setTemperatureReadFunction(
		float (*temperatureReadFunction)()) {
	instance.tempMonitor = new TempMonitor(instance,
			temperatureReadFunction);
	return *this;
}

GnulightCustomizer GnulightCustomizer::setBattery(Battery &battery) {
	instance.batteryMonitor = new BatteryMonitor(instance, battery);
	return *this;
}
