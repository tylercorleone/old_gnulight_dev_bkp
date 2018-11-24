#ifndef CAPPABLEPOTENTIOMETER_H
#define CAPPABLEPOTENTIOMETER_H

#include "Potentiometer.h"

class CappablePotentiometer: public Potentiometer {
public:
	void setLevel(float level) override;
	float getLevelMaxLimit();
	void setLevelMaxLimit(float limit);
	virtual bool levelUpdateForceCondition();
	virtual ~CappablePotentiometer();
protected:
	float levelMaxLimit = 1.0f;
	float wantedLevel = -1.0f;
};

inline void CappablePotentiometer::setLevel(float level) {
	wantedLevel = _constrain(level, 0.0f, 1.0f);

	if (wantedLevel <= levelMaxLimit) {
		Potentiometer::setLevel(wantedLevel);
	} else {
		traceIfNamed("setLevel(%f) skip", wantedLevel);
	}
}

inline float CappablePotentiometer::getLevelMaxLimit() {
	return levelMaxLimit;
}

inline void CappablePotentiometer::setLevelMaxLimit(float limit) {
	traceIfNamed("setLevelMaxLimit(%f)", limit);

	levelMaxLimit = _constrain(limit, 0.0, 1.0);

	if (levelMaxLimit < level || (level < wantedLevel && levelMaxLimit > level) || levelUpdateForceCondition()) {

		/*
		 * we have to reduce the level || we can increase level
		 */
		Potentiometer::setLevel(min(wantedLevel, levelMaxLimit));
	}
}

inline bool CappablePotentiometer::levelUpdateForceCondition() {
	return false;
}

inline CappablePotentiometer::~CappablePotentiometer() {

}

#endif
