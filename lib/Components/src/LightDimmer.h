#ifndef LIGHTDIMMER_H
#define LIGHTDIMMER_H

#include "Components.h"
#include "Potentiometer.h"

class LightDimmer: public Potentiometer {
public:
	LightDimmer(Potentiometer *currentPotentiometer);
	bool isLightnessSimulationEnabled();
	void isLightnessSimulationEnabled(bool);
	virtual ~LightDimmer();
protected:
	void levelActuationFunction(float level) override;
	void onSwitchOn() override;
	void onSwitchOff() override;
	float convertLightnessIntoLuminance(float lightness);
	Potentiometer *currentPotentiometer;
	bool lightnessSimulationEnabled = true;
};

#define cube(x) ((x)*(x)*(x))

inline LightDimmer::LightDimmer(Potentiometer *currentPotentiometer) :
		currentPotentiometer(currentPotentiometer) {

}

inline void LightDimmer::levelActuationFunction(float level) {
	lightnessSimulationEnabled ?
			currentPotentiometer->setLevel(convertLightnessIntoLuminance(level)) :
			currentPotentiometer->setLevel(level);
}

inline bool LightDimmer::isLightnessSimulationEnabled() {
	return lightnessSimulationEnabled;
}

inline void LightDimmer::isLightnessSimulationEnabled(bool isEnabled) {
	lightnessSimulationEnabled = isEnabled;
}

inline float LightDimmer::convertLightnessIntoLuminance(float lightness) {
	// lightness = the normalized L value of L*a*b* color space.
	// luminance = the relative emitted luminance (Y)

	if (lightness < 0.08f) {
		return 0.12842f * ((lightness + 0.16f) / 1.16f - 0.04f / 0.29f);
	} else {
		return cube((lightness + 0.16f) / 1.16f);
	}
}

inline void LightDimmer::onSwitchOn() {
	levelActuationFunction(level);
	currentPotentiometer->setState(OnOffState::ON);
}

inline void LightDimmer::onSwitchOff() {
	currentPotentiometer->setState(OnOffState::OFF);
}

inline LightDimmer::~LightDimmer() {
}

#endif
