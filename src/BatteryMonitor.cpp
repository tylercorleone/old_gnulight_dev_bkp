#include "BatteryMonitor.h"

#include "defines.h"

BatteryMonitor::BatteryMonitor(LithiumBattery *lithiumBattery,
		uint32_t interval, void (*emptyBatteryCallback)(), Dimmable<float> **recipientsToDim) :
		Task(interval), lithiumBattery(lithiumBattery), emptyBatteryCallback(
				emptyBatteryCallback), recipientsToDim(recipientsToDim) {
	trace("Inst. BM");
}

bool BatteryMonitor::OnStart() {
	trace("BM::OnStart");
	maxRelativeCurrent = max(TERMINAL_GUARANTEED_RELATIVE_CURRENT,
			calculateInstantaneousMaxRelativeCurrent());
	notifyDimmableRecipients();
	return true;
}

void BatteryMonitor::OnStop() {
	trace("BM::OnStop");
	maxRelativeCurrent = 1.0;
	notifyDimmableRecipients();
}

void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	trace("BM::OnUpdate");
	float actualMaxRelativeCurrent = calculateInstantaneousMaxRelativeCurrent();
	if (actualMaxRelativeCurrent < maxRelativeCurrent
			|| actualMaxRelativeCurrent
					> maxRelativeCurrent * rechargeThresholdMultiplier
			|| (actualMaxRelativeCurrent > 0.7f
					&& actualMaxRelativeCurrent > maxRelativeCurrent)) {
		trace("Upd. bareLevelTh. " + actualMaxRelativeCurrent);
		maxRelativeCurrent = actualMaxRelativeCurrent;
	}

	if (maxRelativeCurrent <= TERMINAL_GUARANTEED_RELATIVE_CURRENT) {
		maxRelativeCurrent = TERMINAL_GUARANTEED_RELATIVE_CURRENT;
		emptyBatteryCallback();
	}

	notifyDimmableRecipients();
}

void BatteryMonitor::notifyDimmableRecipients() {
	int recipientsCount = sizeof(recipientsToDim) / sizeof(Dimmable<float>*);
	for (int i = 0; i < recipientsCount; ++i) {
		recipientsToDim[i]->dim(maxRelativeCurrent);
	}
}

float BatteryMonitor::calculateInstantaneousMaxRelativeCurrent() {
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
