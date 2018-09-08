#ifndef PROTECTEDLITHIUMBATTERY_H
#define PROTECTEDLITHIUMBATTERY_H

#define TERMINAL_GUARANTEED_CURRENT 0.01f

#include "inttypes.h"
#include "stddef.h"
#include "Task.h"
#include "LithiumBattery.h"

class ProtectedLithiumBattery: public LithiumBattery, public Task {
public:
	ProtectedLithiumBattery(uint32_t interval, void (*emptyBatteryCallback)(), float voltageFull,
			float voltageEmpty, float firstLinearStepEndVoltage,
			float firstLinearStepEndCapacity, uint8_t voltageSensingPin,
			uint8_t batteriesInSeries);
	float getMaxRelativeCurrent() override;
private:
	bool OnStart() override;
	void OnUpdate(uint32_t deltaTime) override;
	void updateMaxRelativeCurrent();
	void (*emptyBatteryCallback)();
	float maxRelativeCurrent = 1.0f;
	static constexpr float rechargeThresholdFilter = 1.05;
};

#endif
