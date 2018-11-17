#include "ConstantLightMode.h"
#include "Gnulight.h"

bool ConstantLightMode::onEnterMode(ButtonInteraction* interaction) {
	info(modeName + "::onEnterMode");

	if (interaction->getClicksCount() > 0) {
		switch (interaction->getClicksCount()) {
		case 1:
			pHostSystem->lightDriver.setLevel(0.0);
			pHostSystem->lightDriver.setState(OnOffState::ON);
			pHostSystem->lightDriver.setMainLevel(MainLightLevel::MAX, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		case 2:
			pHostSystem->lightDriver.setLevel(0.0);
			pHostSystem->lightDriver.setState(OnOffState::ON);
			pHostSystem->lightDriver.setMainLevel(MainLightLevel::MED, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction->getHoldStepsCount() > 0) {
			pHostSystem->lightDriver.setLevel(0.0);
			pHostSystem->lightDriver.setState(OnOffState::ON);
			pHostSystem->lightDriver.setMainLevel(MainLightLevel::MIN, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		} else {
			return false;
		}
	}
}

void ConstantLightMode::onExitMode() {
	info(modeName + "::onExitMode");
}

bool ConstantLightMode::interpretUserInteraction(ButtonInteraction& interaction) {
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
			pHostSystem->enterMode(pHostSystem->powerOffMode);
			return true;
		case 2:
			pHostSystem->lightDriver.setNextSubLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pHostSystem->lightDriver.setNextMainLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		} else {
			return false;
		}
	}
}
