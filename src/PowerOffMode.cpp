#include "../include/PowerOffMode.h"

#include "Gnulight.h"

PowerOffMode::PowerOffMode(Gnulight &gnulight) :
		State(gnulight, "powerOffState") {
}

bool PowerOffMode::onEnterState() {
	Device().lightDimmer.setState(OnOffState::OFF);
	Device().switchPower(OnOffState::OFF);
	return true;
}

void PowerOffMode::onExitState() {
	Device().switchPower(OnOffState::ON);
}

bool PowerOffMode::handleEvent(const ButtonEvent &event) {

	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
		case 2:
			Device().enterState(Device().constantLightMode, event);
			return true;
		case 3:
			Device().enterState(Device().strobeMode, event);
			return true;
		case 4:
			Device().enterState(Device().parameterCheckMode, MessageEvent(ParameterCheckMode::BATTERY_CHECK_MSG));
			return true;
		case 5:
			Device().enterState(Device().parameterCheckMode, MessageEvent(ParameterCheckMode::LAMP_TEMPERATURE_CHECK_MSG));
			return true;
		case 6:
			Device().lightDimmer.isLightnessSimulationEnabled(
					!Device().lightDimmer.isLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		Device().enterState(Device().constantLightMode, event);
		return true;
	} else {
		return false;
	}
}
