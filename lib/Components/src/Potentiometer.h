#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Components.h"
#include "Named.h"

#define _constrain(value,low,high) ((value)<(low)?(low):((value)>(high)?(high):(value)))

class Potentiometer: public Named {
public:
	Potentiometer();
	float getLevel();
	OnOffState getState();
	void toggleState();
	virtual ~Potentiometer();

	virtual void levelActuationFunction(float level) = 0;
	virtual void setLevel(float level);
	virtual void setState(OnOffState state);

protected:
	virtual void onEnterOffState();
	virtual void onEnterOnState();

	OnOffState state = OnOffState::OFF;
	float level = 0.0;
};

inline Potentiometer::Potentiometer() {

}

inline float Potentiometer::getLevel() {
	return level;
}

inline void Potentiometer::setLevel(float level) {
	traceNamedInstance("setLevel(%f)", level);
	this->level = _constrain(level, 0.0, 1.0);

	if (state == OnOffState::ON) {
		levelActuationFunction(this->level);
	}
}

inline OnOffState Potentiometer::getState() {
	return state;
}

inline void Potentiometer::setState(OnOffState state) {
	debugNamedInstance("setState(%s)", state == OnOffState::ON ? "ON" : "OFF");
	this->state = state;
	state == OnOffState::OFF ? onEnterOffState() : onEnterOnState();
}

inline void Potentiometer::toggleState() {
	setState(state == OnOffState::ON ? OnOffState::OFF : OnOffState::ON);
}

inline void Potentiometer::onEnterOffState() {
	levelActuationFunction(0.0);
}

inline void Potentiometer::onEnterOnState() {
	setLevel(level);
}

inline Potentiometer::~Potentiometer() {
}

#endif
