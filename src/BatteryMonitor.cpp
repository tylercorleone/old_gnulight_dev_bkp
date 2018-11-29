#include "BatteryMonitor.h"
#include "Gnulight.h"

BatteryMonitor::BatteryMonitor(Gnulight &gnulight, Battery &battery) :
		Task(BATTERY_LEVEL_MONITORING_INTERVAL_MS), DeviceAware(gnulight), Named(
				"battMonitor"), battery(battery) {
}

bool BatteryMonitor::OnStart() {
	traceIfNamed("OnStart");
	return true;
}

void BatteryMonitor::OnStop() {
	traceIfNamed("OnStop");
}

void BatteryMonitor::OnUpdate(uint32_t deltaTime) {
	traceIfNamed("OnUpdate");

	float remainingCharge = battery.getRemainingCharge();

	traceIfNamed("batt: %f%%", remainingCharge);

	if (remainingCharge > remainingCharge_1 && remainingCharge < remainingCharge_1 + FILTERED_RECHARGE_AMOUNT) {

		/*
		 * Recharged, but not sufficiently
		 */
		return;
	}

	remainingCharge_1 = remainingCharge;

	float currentLimit = calculateInstantaneousMaxCurrent(remainingCharge);

	traceIfNamed("currLimit: %f", currentLimit);

	Device().currentPotentiometer.setBatteryCausedLimit(currentLimit);

	if (currentLimit == 0.0) {
		onEmptyBattery();
	}
}

float BatteryMonitor::calculateInstantaneousMaxCurrent(float remainingCharge) {
	if (remainingCharge <= 0.0f) {
		return 0.0;
	} else if (remainingCharge < 0.05f) {
		return 0.05f;
	} else if (remainingCharge < 0.15f) {
		return 0.1f;
	} else if (remainingCharge < 0.25f) {
		return 0.25f;
	} else if (remainingCharge < 0.35f) {
		return 0.5f;
	}

	return 1.0f;
}

void BatteryMonitor::onEmptyBattery() {
	infoIfNamed("Empty battery!");
	Device().enterState(Device().parameterCheckMode,
			MessageEvent(ParameterCheckMode::BATTERY_CHECK_MSG));
}
