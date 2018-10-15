#include "ConstantLightMode.h"
#include "Gnulight.h"

#define LEVEL_TRANSITION_DURATION_MS 200

ConstantLightMode::ConstantLightMode(const char* className, Gnulight* gnulight) :
		GnulightMode(className, gnulight) {
	trace(className + "::" + className);
}

bool ConstantLightMode::onEnterMode(ButtonInteraction* interaction) {
	info(className + "::onEnterMode");
	if (interaction->getClicksCount() > 0) {
		switch (interaction->getClicksCount()) {
		case 1:
			pHostSystem->lightDriver.setPotentiometerLevel(0.0);
			pHostSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			pHostSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MAX, LEVEL_TRANSITION_DURATION_MS);
			return true;
		case 2:
			pHostSystem->lightDriver.setPotentiometerLevel(0.0);
			pHostSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			pHostSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MED, LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction->getHoldStepsCount() > 0) {
			pHostSystem->lightDriver.setPotentiometerLevel(0.0);
			pHostSystem->lightDriver.switchLightStatus(LIGHT_STATUS_ON);
			pHostSystem->lightDriver.setMainLevel(MAIN_LIGHT_LEVEL_MIN, LEVEL_TRANSITION_DURATION_MS);
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
			pHostSystem->enterMode(pHostSystem->powerOffMode, &interaction);
			return true;
		case 2:
			pHostSystem->lightDriver.setNextSubLevel(LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pHostSystem->lightDriver.setNextMainLevel(LEVEL_TRANSITION_DURATION_MS);
			return true;
		} else {
			return false;
		}
	}
}
