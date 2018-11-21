#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include "Components.h"
#include "Named.h"

class Potentiometer: public Named {
public:
	float getLevel();
	virtual void setLevel(float level);
	OnOffState getState();
	virtual void setState(OnOffState state);
	void toggleState();
	virtual ~Potentiometer();
protected:
	virtual void levelActuationFunction(float level) = 0;
	virtual void onEnterOffState();
	virtual void onEnterOnState();

	OnOffState state = OnOffState::OFF;
	float level = 1.0;
};

inline float Potentiometer::getLevel() {
	return level;
}

inline void Potentiometer::setLevel(float level) {
	traceNamedInstance("setLevel(%f)", level);
	this->level = _constrain(level, 0.0f, 1.0f);

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
