#include "ConstantLightMode.h"
#include "Gnulight.h"

ConstantLightMode::ConstantLightMode(const char* className, Gnulight* gnulight) :
		GnulightMode(className, gnulight) {
	trace(className + "::" + className);
}

bool ConstantLightMode::onEnterMode(ButtonInteraction* interaction) {
	info(className + "::onEnterMode");
	if (interaction->getClicksCount() > 0) {
		switch (interaction->getClicksCount()) {
		case 1:
			pSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MAX);
			pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			return true;
		case 2:
			pSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MED);
			pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction->getHoldStepsCount() > 0) {
			pSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MIN);
			pSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			return true;
		} else {
			return false;
		}
	}
}

void ConstantLightMode::onExitMode() {
	info(className + "::onExitMode");
}

bool ConstantLightMode::interpretUserInteraction(ButtonInteraction& interaction) {
	if (interaction.getClicksCount() > 0) {
		switch (interaction.getClicksCount()) {
		case 1:
			pSystem->enterMode(pSystem->powerOffMode, &interaction);
			return true;
		case 2:
			pSystem->lightDriver.setNextSubLevel();
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pSystem->lightDriver.setNextMainLevel();
			return true;
		} else {
			return false;
		}
	}
}
