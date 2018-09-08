#ifndef LITHIUMBATTERYMONITOR_H
#define LITHIUMBATTERYMONITOR_H

#define TERMINAL_GUARANTEED_RELATIVE_CURRENT 0.01f

#include "inttypes.h"
#include "stddef.h"
#include "Task.h"
#include "LithiumBattery.h"
#include "Dimmable.h"

class LithiumBatteryMonitor: public Task {
public:
	LithiumBatteryMonitor(LithiumBattery *lithiumBattery, uint32_t interval,
			void (*emptyBatteryCallback)(), Dimmable<float> **recipientsToDim);
private:
	bool OnStart() override;
	void OnUpdate(uint32_t deltaTime) override;
	float calculateInstantaneousMaxRelativeCurrent();
	void notifyDimmableRecipients();
	LithiumBattery *lithiumBattery;
	void (*emptyBatteryCallback)();
	Dimmable<float> **recipientsToDim;
	float maxRelativeCurrent = 1.0f;
	static constexpr float rechargeThresholdMultiplier = 1.05;
};

#endif
