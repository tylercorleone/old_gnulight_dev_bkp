#include "PowerOffState.h"
#include "Gnulight.h"

PowerOffState::PowerOffState(Gnulight *gnulight) :
		HostSystemAware(gnulight) {
	info("Inst. PowerOffState");
}

bool PowerOffState::onEnterState() {
	info("PowerOffState::onEnterState");

	getHostSystem()->lightDriver.setState(OnOffState::OFF);
	getHostSystem()->switchPower(OnOffState::OFF);
	return true;
}

void PowerOffState::onExitState() {
	info("PowerOffState::onExitState");

	getHostSystem()->switchPower(OnOffState::ON);
}

bool PowerOffState::receiveEvent(const Event &event) {
	if (event.getClicksCount() > 0) {

		switch (event.getClicksCount()) {
		case 1:
		case 2:
			getHostSystem()->enterState(getHostSystem()->constantLightState, event);
			return true;
		case 3:
			getHostSystem()->enterState(getHostSystem()->strobeState, event);
			return true;
		case 4:
			getHostSystem()->enterState(getHostSystem()->parameterCheckState, Event(ParameterCheckState::BATTERY_CHECK));
			return true;
		case 5:
			getHostSystem()->enterState(getHostSystem()->parameterCheckState, Event(ParameterCheckState::LAMP_TEMPERATURE_CHECK));
			return true;
		case 6:
			getHostSystem()->lightDriver.isLightnessSimulationEnabled(
					!getHostSystem()->lightDriver.isLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}

	} else if (event.getHoldStepsCount() > 0) {
		getHostSystem()->enterState(getHostSystem()->constantLightState, event);
		return true;
	} else {
		return false;
	}
}
