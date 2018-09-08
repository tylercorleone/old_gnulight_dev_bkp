#include "ProtectedLithiumBattery.h"
#include "Arduino.h"
#include "defines.h"

ProtectedLithiumBattery::ProtectedLithiumBattery(uint32_t interval,
		void (*emptyBatteryCallback)(), float voltageFull, float voltageEmpty,
		float firstLinearStepEndVoltage, float firstLinearStepEndCapacity,
		uint8_t voltageSensingPin, uint8_t batteriesInSeries) :
		Task(interval), emptyBatteryCallback(emptyBatteryCallback), LithiumBattery(
				voltageFull, voltageEmpty, firstLinearStepEndVoltage,
				firstLinearStepEndCapacity, voltageSensingPin,
				batteriesInSeries) {
	trace("Inst. PLB");
	pinMode(BATTERY_SENSING_PIN, INPUT);
}

float ProtectedLithiumBattery::getMaxRelativeCurrent() {
	return maxRelativeCurrent;
}

bool ProtectedLithiumBattery::OnStart() {
	maxRelativeCurrent = max(TERMINAL_GUARANTEED_CURRENT,
			LithiumBattery::getMaxRelativeCurrent());
	return true;
}

void ProtectedLithiumBattery::OnUpdate(uint32_t deltaTime) {
	float actualMaxRelativeCurrent = max(TERMINAL_GUARANTEED_CURRENT,
			LithiumBattery::getMaxRelativeCurrent());
	if (actualMaxRelativeCurrent < maxRelativeCurrent
			|| actualMaxRelativeCurrent
					> maxRelativeCurrent * rechargeThresholdFilter
			|| (actualMaxRelativeCurrent > 0.7f
					&& maxRelativeCurrent < actualMaxRelativeCurrent)) {
		trace("Upd. bareLevelTh. " + actualMaxRelativeCurrent);
		maxRelativeCurrent = actualMaxRelativeCurrent;
	}

	if (maxRelativeCurrent == TERMINAL_GUARANTEED_CURRENT) {
		emptyBatteryCallback();
	}
}
