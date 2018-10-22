#include "ConstantLightMode.h"
#include "Gnulight.h"

ConstantLightMode::ConstantLightMode(Gnulight* gnulight, const char* modeName) :
		GnulightMode(gnulight, modeName) {}

bool ConstantLightMode::onEnterMode(ButtonInteraction* interaction) {
	info(modeName + "::onEnterMode");
	if (interaction->getClicksCount() > 0) {
		switch (interaction->getClicksCount()) {
		case 1:
			pHostSystem->advancedLightDriver.setPotentiometerLevel(0.0);
			pHostSystem->advancedLightDriver.switchLightStatus(LightStatus::ON);
			pHostSystem->advancedLightDriver.setMainLevel(MainLightLevel::MAX, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		case 2:
			pHostSystem->advancedLightDriver.setPotentiometerLevel(0.0);
			pHostSystem->advancedLightDriver.switchLightStatus(LightStatus::ON);
			pHostSystem->advancedLightDriver.setMainLevel(MainLightLevel::MED, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction->getHoldStepsCount() > 0) {
			pHostSystem->advancedLightDriver.setPotentiometerLevel(0.0);
			pHostSystem->advancedLightDriver.switchLightStatus(LightStatus::ON);
			pHostSystem->advancedLightDriver.setMainLevel(MainLightLevel::MIN, CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
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
			pHostSystem->advancedLightDriver.setNextSubLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		default:
			return false;
		}
	} else {
		if (interaction.getHoldStepsCount() > 0) {
			pHostSystem->advancedLightDriver.setNextMainLevel(CONSTANT_LIGHT_LEVEL_TRANSITION_DURATION_MS);
			return true;
		} else {
			return false;
		}
	}
}
