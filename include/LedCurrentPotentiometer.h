#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include <stdint.h>
#include <HostSystemAware.h>
#include <CappablePotentiometer.h>

class Gnulight;

class LedCurrentPotentiometer: public CappablePotentiometer, public HostSystemAware<Gnulight> {
public:
	LedCurrentPotentiometer(Gnulight *gnulight);
	void setup();
	void levelActuationFunction(float level) override;
private:
	friend class LightMonitor;
	void digPotWrite(uint16_t value);
	uint16_t pwmAmount = 0;
};

#endif
