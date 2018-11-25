#ifndef BATTERY_H
#define BATTERY_H

class Battery {
public:
	Battery(float (*readVoltageFunc)());

	/**
	 * Returns a value between 0.0 and 1.0
	 */
	virtual float getRemainingCharge() = 0;
	virtual ~Battery();
protected:
	float (*readVoltage)(void);
};

inline Battery::Battery(float (*readVoltageFunc)()) :
		readVoltage(readVoltageFunc) {

}

inline Battery::~Battery() {

}

#endif
