#ifndef GNULIGHTBUILDER_H
#define GNULIGHTBUILDER_H

#include "gnulight_config.h"

#include "Gnulight.h"

class GnulightBuilder {
public:
	static GnulightBuilder configureGnulight();
	GnulightBuilder setBattery(Battery *battery);
	GnulightBuilder setBatteryMonitor(BatteryMonitor *batteryMonitor);
	Gnulight* build();
private:
	GnulightBuilder(Gnulight *instance);
	Gnulight *instance;
};

#endif
