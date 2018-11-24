#include "BatteryMonitor.h"
#include "Gnulight.h"

BatteryMonitor::BatteryMonitor(Gnulight *gnulight, uint32_t interval,
		CappablePotentiometer **recipientsToDim) :
		Task(interval), Named("battMon"), gnulight(gnulight), recipientsToDim(
				recipientsToDim) {
}

bool BatteryMonitor::OnStart() {
	traceIfNamed("OnStart");

	return true;
}

void BatteryMonitor::OnStop() {
	traceIfNamed("OnStop");

	maxRelativeCurrent = BATTERY_FULL_CURRENT;
	notifyDimmableRecipients();
}

void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	traceIfNamed("OnUpdate");

	float newMaxRelativeCurrent = calculateInstantaneousMaxRelativeCurrent();

	if (newMaxRelativeCurrent < maxRelativeCurrent
			|| newMaxRelativeCurrent
					> maxRelativeCurrent * RECHARGE_THRESHOLD_MULTIPLIER
			|| newMaxRelativeCurrent > ALMOST_FULL_THRESHOLD_CURRENT) {

		maxRelativeCurrent = newMaxRelativeCurrent;

		traceIfNamed("maxRelativeCurrent: %f", maxRelativeCurrent);
	}

	if (maxRelativeCurrent <= BATTERY_EMPTY_CURRENT) {
		maxRelativeCurrent = TERMINAL_GUARANTEED_RELATIVE_CURRENT;
		emptyBatteryCallback();
	}

	notifyDimmableRecipients();
}

void BatteryMonitor::notifyDimmableRecipients() {
	int recipientsCount = sizeof(recipientsToDim) / sizeof(CappablePotentiometer*);

	for (int i = 0; i < recipientsCount; ++i) {
		recipientsToDim[i]->setLevelMaxLimit(maxRelativeCurrent);
	}
}

float BatteryMonitor::calculateInstantaneousMaxRelativeCurrent() {
	float currentCapacity = gnulight->battery.getRemainingCharge();

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
	if (gnulight->currentState != &gnulight->parameterCheckState) {
		info("Batt. is empty");

		gnulight->enterState(gnulight->parameterCheckState, ParameterCheckState::BATTERY_CHECK);
	}
}
