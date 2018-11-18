#include "ConstantLightState.h"

#include "Gnulight.h"

bool ConstantLightState::onEnterState(const Event &event) {
	info("CLS::onEnterState");

	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			getHostSystem()->lightDriver.setLevel(0.0);
			getHostSystem()->lightDriver.setState(OnOffState::ON);
			getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MAX, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		case 2:
			getHostSystem()->lightDriver.setLevel(0.0);
			getHostSystem()->lightDriver.setState(OnOffState::ON);
			getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MED, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (event.getHoldStepsCount() > 0) {
			getHostSystem()->lightDriver.setLevel(0.0);
			getHostSystem()->lightDriver.setState(OnOffState::ON);
			getHostSystem()->lightDriver.setMainLevel(MainLightLevel::MIN, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		} else {
			return false;
		}
	}
}

bool ConstantLightState::receiveEvent(const Event &event) {
	if (event.getClicksCount() > 0) {
		switch (event.getClicksCount()) {
		case 1:
			getHostSystem()->enterState(getHostSystem()->powerOffState);
			return true;
		case 2:
			getHostSystem()->lightDriver.setNextSubLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else if (event.getHoldStepsCount() > 0) {
		getHostSystem()->lightDriver.setNextMainLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
		return true;
	} else {
		return false;
	}
}
