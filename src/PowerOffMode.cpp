#include "PowerOffMode.h"
#include "Gnulight.h"

bool PowerOffMode::onEnterMode() {
	info(modeName + "::onEnterMode");
	pHostSystem->switchPower(OnOffState::OFF);
	return true;
}

void PowerOffMode::onExitMode() {
	info(modeName + "::onExitMode");
	pHostSystem->switchPower(OnOffState::ON);
}

bool PowerOffMode::interpretUserInteraction(ButtonInteraction& interaction) {
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
		case 2:
			pHostSystem->enterMode(pHostSystem->constantLightMode, &interaction);
			return true;
		case 3:
			pHostSystem->enterMode(pHostSystem->strobeMode, &interaction);
			return true;
		case 4:
			pHostSystem->enterMode(pHostSystem->parameterCheckMode, &BATTERY_CHECK);
			return true;
		case 5:
			pHostSystem->enterMode(pHostSystem->parameterCheckMode, &LAMP_TEMPERATURE_CHECK);
			return true;
		case 6:
			pHostSystem->lightDriver.setLightnessSimulationEnabled(
					!pHostSystem->lightDriver.getLightnessSimulationEnabled());
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pHostSystem->enterMode(pHostSystem->constantLightMode, &interaction);
			return true;
		} else {
			return false;
		}
	}
}
