#ifndef LITHIUMBATTERYMONITOR_H
#define LITHIUMBATTERYMONITOR_H

#define TERMINAL_GUARANTEED_RELATIVE_CURRENT 0.01f

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include <HostSystemAware.h>

#include "Dimmable.h"

#define ALMOST_FULL_THRESHOLD_CURRENT 0.9f
#define BATTERY_FULL_CURRENT 1.0f
#define BATTERY_EMPTY_CURRENT 0.01
#define RECHARGE_THRESHOLD_MULTIPLIER 1.05f

class Gnulight;

class BatteryMonitor: public Task {
public:
	BatteryMonitor(Gnulight *pGnulight, uint32_t interval,
			Dimmable<float> **recipientsToDim);
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	float calculateInstantaneousMaxRelativeCurrent();
	void notifyDimmableRecipients();
	void emptyBatteryCallback();
	Gnulight *pGnulight;
	Dimmable<float> **recipientsToDim;
	float maxRelativeCurrent = BATTERY_FULL_CURRENT;
};

#endif
