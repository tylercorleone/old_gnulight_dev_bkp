#include "PowerOffMode.h"
#include "Gnulight.h"

PowerOffMode::PowerOffMode(const char* className, Gnulight* gnulight) :
		GnulightMode(className, gnulight) {
	trace(className + "::" + className);
}
bool PowerOffMode::onEnterMode(ButtonInteraction* interaction) {
	info(className + "::onEnterMode");
	pSystem->switchPower(POWER_STATE_OFF);
	pSystem->EnterSleep();
	return true;
}

void PowerOffMode::onExitMode() {
	info(className + "::onExitMode");
	pSystem->switchPower(POWER_STATE_ON);
}

bool PowerOffMode::interpretUserInteraction(ButtonInteraction& interaction) {
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
		case 2:
			pSystem->enterMode(pSystem->constantLightMode, &interaction);
			return true;
		case 3:
			pSystem->enterMode(pSystem->strobeMode, &interaction);
			return true;
		case 4:
			pSystem->enterMode(pSystem->parameterCheckMode, &BATTERY_CHECK);
			return true;
		case 5:
			pSystem->enterMode(pSystem->parameterCheckMode, &LAMP_TEMPERATURE_CHECK);
			return true;
		case 6:
			pSystem->lightDriver.setLightnessSimulationEnabled(
					!pSystem->lightDriver.getLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pSystem->enterMode(pSystem->constantLightMode, &interaction);
			return true;
		} else {
			return false;
		}
	}
}
