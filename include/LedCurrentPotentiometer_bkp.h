#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include <stdint.h>
#include <HostSystemAware.h>
#include <Potentiometer.h>
#include <PotentiometerActuator.h>

class Gnulight;

#define ACTUATOR_INTERVAL_MS MsToTaskTime(30)

class LedCurrentPotentiometer: public Potentiometer, public HostSystemAware<Gnulight> {
public:
	LedCurrentPotentiometer(Gnulight *gnulight);
	void setup();
	void levelActuationFunction(float level) override;
private:
	friend class LightMonitor;
	void digPotWrite(uint16_t value);
	float getCurrentUpperLimit();
	void setCurrentUpperLimit(float limit, uint32_t transitionDurationMs = 0);
	PotentiometerActuator currentActuator { ACTUATOR_INTERVAL_MS,
			(TaskManager*) getHostSystem(), this };
	uint16_t pwmAmount = 0;
	float currentUpperLimit = 1.0f;
	float wantedCurrentLevel = 0.0f;
};

#endif
