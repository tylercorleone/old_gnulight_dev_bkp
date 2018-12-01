#ifndef GNULIGHTCUSTOMIZER_H
#define GNULIGHTCUSTOMIZER_H

#include "gnulight_config.h"

#include "Gnulight.h"

class GnulightCustomizer {
public:
	static GnulightCustomizer customize(Gnulight &gnulight);
	GnulightCustomizer setBattery(Battery &battery);
	GnulightCustomizer setTemperatureReadFunction(float (*temperatureReadFunction)());
	Gnulight* build();
private:
	GnulightCustomizer(Gnulight &instance);
	Gnulight &instance;
};

#endif
