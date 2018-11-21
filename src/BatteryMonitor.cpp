#include "BatteryMonitor.h"

#include "defines.h"
#include "Gnulight.h"

BatteryMonitor::BatteryMonitor(Gnulight *pGnulight, uint32_t interval,
		Dimmable<float> **recipientsToDim) :
		Task(interval), pGnulight(pGnulight), recipientsToDim(recipientsToDim) {
	trace("Inst. BM");
}

bool BatteryMonitor::OnStart() {
	trace("BM::OnStart");
	return true;
}

void BatteryMonitor::OnStop() {
	trace("BM::OnStop");
	maxRelativeCurrent = BATTERY_FULL_CURRENT;
	notifyDimmableRecipients();
}

void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	trace("BM::OnUpdate");

	float actualMaxRelativeCurrent = calculateInstantaneousMaxRelativeCurrent();

	if (actualMaxRelativeCurrent < maxRelativeCurrent
			|| actualMaxRelativeCurrent
					> maxRelativeCurrent * RECHARGE_THRESHOLD_MULTIPLIER
			|| actualMaxRelativeCurrent > ALMOST_FULL_THRESHOLD_CURRENT) {
		debug("BM maxRelativeCurrent: %f", maxRelativeCurrent);

		maxRelativeCurrent = actualMaxRelativeCurrent;
	}

	if (maxRelativeCurrent <= BATTERY_EMPTY_CURRENT) {
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
	float currentCapacity = pGnulight->battery.getRemainingCharge();

	if (currentCapacity == 0.0f) {
		return 0.0f;
	} else if (currentCapacity < 0.05f) {
		return 0.05f;
	} else if (currentCapacity < 0.1f) {
		return 0.1f;
	} else if (currentCapacity < 0.3f) {
		return 0.5f;
	}

	return BATTERY_FULL_CURRENT;
}

void BatteryMonitor::emptyBatteryCallback() {
	if (pGnulight->currentState != &pGnulight->parameterCheckState) {
		info("Batt. is empty");
		pGnulight->enterState(pGnulight->parameterCheckState, ParameterCheckState::BATTERY_CHECK);
	}
}
