#ifndef LEDCURRENTPOTENTIOMETER_H
#define LEDCURRENTPOTENTIOMETER_H

#include <stdint.h>

#include "Potentiometer.h"

class LedCurrentPotentiometer : public Potentiometer {
public:
	void setup();
	void levelActuationFunction(float level) override;
private:
	void digPotWrite(uint16_t value);
	uint16_t pwmAmount = -1;
};

#endif
