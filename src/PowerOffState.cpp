#include "PowerOffState.h"
#include "Gnulight.h"

PowerOffState::PowerOffState(Gnulight *gnulight) :
		State("powerOffState"), gnulight(gnulight) {
}

bool PowerOffState::onEnterState() {
	gnulight->lightDriver.setState(OnOffState::OFF);
	gnulight->switchPower(OnOffState::OFF);
	return true;
}

void PowerOffState::onExitState() {
	gnulight->switchPower(OnOffState::ON);
}

bool PowerOffState::handleEvent(const Event &event) {

	if (event.getEventTypeUUID() != ButtonEvent::eventTypeUUID()) {
		return false;
	}

	ButtonEvent *buttonEvent = (ButtonEvent*) &event;
	if (buttonEvent->getClicksCount() > 0) {

		switch (buttonEvent->getClicksCount()) {
		case 1:
		case 2:
			gnulight->enterState(gnulight->constantLightState, event);
			return true;
		case 3:
			gnulight->enterState(gnulight->strobeState, event);
			return true;
		case 4:
			gnulight->enterState(gnulight->parameterCheckState, MessageEvent(ParameterCheckState::BATTERY_CHECK));
			return true;
		case 5:
			gnulight->enterState(gnulight->parameterCheckState, MessageEvent(ParameterCheckState::LAMP_TEMPERATURE_CHECK));
			return true;
		case 6:
			gnulight->lightDriver.isLightnessSimulationEnabled(
					!gnulight->lightDriver.isLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}

	} else if (buttonEvent->getHoldStepsCount() > 0) {
		gnulight->enterState(gnulight->constantLightState, event);
		return true;
	} else {
		return false;
	}
}
