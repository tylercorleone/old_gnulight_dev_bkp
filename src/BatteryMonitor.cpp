#include "BatteryMonitor.h"
#include "Gnulight.h"

BatteryMonitor::BatteryMonitor(Battery *battery, uint32_t monitoringInterval,
		void (*onEmptyBatteryFunc)()) :
		Task(monitoringInterval), battery(battery), onEmptyBattery(
				onEmptyBatteryFunc) {
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

	float currentLimit = calculateInstantaneousMaxCurrent();

	traceIfNamed("currentLimit: %f", currentLimit);

	if (currentLimit == BATTERY_EMPTY_CURRENT) {
		onEmptyBattery();
	}
}

float BatteryMonitor::calculateInstantaneousMaxCurrent() {
	float remainingCharge = battery->getRemainingCharge();

	if (remainingCharge == 0.0f) {
		return BATTERY_EMPTY_CURRENT;
	} else if (remainingCharge < 0.05f) {
		return 0.05f;
	} else if (remainingCharge < 0.15f) {
		return 0.1f;
	} else if (remainingCharge < 0.25f) {
		return 0.5f;
	}

	return BATTERY_FULL_CURRENT;
}
