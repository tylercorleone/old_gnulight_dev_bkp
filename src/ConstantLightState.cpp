#include "ConstantLightState.h"
#include "Gnulight.h"

ConstantLightState::ConstantLightState(Gnulight *gnulight) :
		State("constLightState"), gnulight(gnulight) {
}

bool ConstantLightState::onEnterState(const ButtonEvent &event) {
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

	gnulight->lightDriver.setLevel(0.0);
	gnulight->lightDriver.setState(OnOffState::ON);
	gnulight->lightDriver.setMainLevel(wantedLevel, MAIN_LEVEL_TRANSITION_DURATION_MS);

	return true;
}

bool ConstantLightState::handleEvent(const ButtonEvent &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			gnulight->enterState(gnulight->powerOffState);
			return true;
		case 2:
			gnulight->lightDriver.setNextSubLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		gnulight->lightDriver.setNextMainLevel(MAIN_LEVEL_TRANSITION_DURATION_MS);
		return true;
	} else {
		return false;
	}
}
