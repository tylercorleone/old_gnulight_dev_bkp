#include "../include/ConstantLightMode.h"

#include "Gnulight.h"

ConstantLightMode::ConstantLightMode(Gnulight &gnulight) :
		State(gnulight, "constLightState") {
}

bool ConstantLightMode::onEnterState(const ButtonEvent &event) {
	LightLevelIndex wantedLevel;

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			wantedLevel = LightLevelIndex::MAX;
			break;
		case 2:
			wantedLevel = LightLevelIndex::MED;
			break;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		wantedLevel = LightLevelIndex::MIN;
	} else {
		return false;
	}

	Device().lightDriver.setLevel(0.0);
	Device().lightDriver.setState(OnOffState::ON);
	Device().lightDriver.setMainLevel(wantedLevel, MAIN_LEVEL_TRANSITION_DURATION_MS);

	return true;
}

bool ConstantLightMode::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			Device().enterState(Device().powerOffMode);
			return true;
		case 2:
			Device().lightDriver.setNextSubLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		Device().lightDriver.setNextMainLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
		return true;
	} else {
		return false;
	}
}
