#ifndef LITHIUMBATTERYMONITOR_H
#define LITHIUMBATTERYMONITOR_H

#include "gnulight_config.h"

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include <Battery.h>
#include <CappablePotentiometer.h>
#include <Components.h>

#define EMERGENCY_CURRENT_LEVEL 0.01f
#define BATTERY_FULL_CURRENT 1.0f
#define BATTERY_EMPTY_CURRENT 0.0f
#define RECHARGE_THRESHOLD_MULTIPLIER 1.05f

class BatteryMonitor: public Task, public Named {
public:
	BatteryMonitor(Battery *battery, uint32_t monitoringInterval,
			void (*onEmptyBatteryFunc)());
	float calculateInstantaneousMaxCurrent();
private:
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	Battery *battery;
	float currentLimit_1 = BATTERY_FULL_CURRENT;
	void (*onEmptyBattery)();
};

#endif
