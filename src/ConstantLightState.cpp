#include "ConstantLightState.h"
#include "Gnulight.h"

ConstantLightState::ConstantLightState(Gnulight *gnulight) :
		State("constLightState"), gnulight(gnulight) {
}

bool ConstantLightState::onEnterState(const Event &event) {
	MainLightLevel wantedLevel;

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
			wantedLevel = MainLightLevel::MAX;
			break;
		case 2:
			wantedLevel = MainLightLevel::MED;
			break;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		wantedLevel = MainLightLevel::MIN;
	} else {
		return false;
	}

	gnulight->lightDriver.setLevel(0.0);
	gnulight->lightDriver.setState(OnOffState::ON);
	gnulight->lightDriver.setMainLevel(wantedLevel, MAIN_LEVEL_TRANSITION_DURATION_MS);

	return true;
}

bool ConstantLightState::receiveEvent(const Event &event) {
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
