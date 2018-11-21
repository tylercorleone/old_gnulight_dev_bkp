#ifndef CAPPABLEPOTENTIOMETER_H
#define CAPPABLEPOTENTIOMETER_H

#include "Potentiometer.h"

class CappablePotentiometer: public Potentiometer {
public:
	void setLevel(float level) override;
	float getLevelMaxLimit();
	void setLevelMaxLimit(float limit);
	virtual bool levelUpdateConditionOverride();
	virtual ~CappablePotentiometer();
protected:
	float wantedLevel = 0.0f;
	float levelMaxLimit = 1.0f;
};

inline float CappablePotentiometer::setLevel(float level) {
	wantedLevel = _constrain(level, 0.0f, 1.0f);

	if (wantedLevel <= levelMaxLimit) {
		Potentiometer::setLevel(level);
	}
}

inline float CappablePotentiometer::getLevelMaxLimit() {
	return levelMaxLimit;
}

inline void CappablePotentiometer::setLevelMaxLimit(float limit) {
	traceNamedInstance("setLevelMaxLimit(%f)", level);
	levelMaxLimit = _constrain(level, 0.0, 1.0);

	if (levelMaxLimit < level || (level < wantedLevel && levelMaxLimit > level) || levelUpdateConditionOverride()) {

		/*
		 * we have to reduce the level || we can increase level
		 */
		Potentiometer::setLevel(min(wantedLevel, levelMaxLimit));
	}
}

bool CappablePotentiometer::levelUpdateConditionOverride() {
	return false;
}

inline CappablePotentiometer::~CappablePotentiometer() {

}

#endif
