#include "LithiumBatteryMonitor.h"
#include "Arduino.h"
#include "defines.h"

LithiumBatteryMonitor::LithiumBatteryMonitor(LithiumBattery *lithiumBattery,
		uint32_t interval, void (*emptyBatteryCallback)(), Dimmable<float> **recipientsToDim) :
		lithiumBattery(lithiumBattery), Task(interval), emptyBatteryCallback(
				emptyBatteryCallback), recipientsToDim(recipientsToDim) {
	trace("Inst. LBM");
}

bool LithiumBatteryMonitor::OnStart() {
	maxRelativeCurrent = max(TERMINAL_GUARANTEED_RELATIVE_CURRENT,
			calculateInstantaneousMaxRelativeCurrent());
	notifyDimmableRecipients();
	return true;
}

void LithiumBatteryMonitor::OnUpdate(uint32_t deltaTime) {
	float actualMaxRelativeCurrent = calculateInstantaneousMaxRelativeCurrent();
	if (actualMaxRelativeCurrent < maxRelativeCurrent
			|| actualMaxRelativeCurrent
					> maxRelativeCurrent * rechargeThresholdMultiplier
			|| (actualMaxRelativeCurrent > 0.7f
					&& actualMaxRelativeCurrent > maxRelativeCurrent)) {
		trace("Upd. bareLevelTh. " + actualMaxRelativeCurrent);
		maxRelativeCurrent = actualMaxRelativeCurrent;
	}

	notifyDimmableRecipients();

	if (maxRelativeCurrent <= TERMINAL_GUARANTEED_RELATIVE_CURRENT) {
		maxRelativeCurrent = TERMINAL_GUARANTEED_RELATIVE_CURRENT;
		emptyBatteryCallback();
	}
}

void LithiumBatteryMonitor::notifyDimmableRecipients() {
	int recipientsCount = sizeof(recipientsToDim) / sizeof(Dimmable<float>*);
	for (int i = 0; i < recipientsCount; ++i) {
		recipientsToDim[i]->setDimmableMaxValue(maxRelativeCurrent);
	}
}

float LithiumBatteryMonitor::calculateInstantaneousMaxRelativeCurrent() {
	float currentCapacity = lithiumBattery->getRemainingCharge();
	if (currentCapacity == 0.0f) {
		return 0.0f;
	} else if (currentCapacity < 0.05f) {
		return 0.05f;
	} else if (currentCapacity < 0.1f) {
		return 0.1f;
	} else if (currentCapacity < 0.3f) {
		return 0.5f;
	}
	return 1.0f;
}
