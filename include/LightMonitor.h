
#ifndef LIGHTMONITOR_H
#define LIGHTMONITOR_H

#include <inttypes.h>
#include <stddef.h>
#include "Task.h"
#include "Dimmable.h"

#define TEMPERATURE_TARGET 50.0f
#define TEMPERATURE_MAX_ERROR 500.0f
#define CURRENT_ACTIVATION_THRESHOLD 0.2f

class AdvancedLightDriver;
class ProtectedLithiumBattery;

class LightMonitor: public Task, public Dimmable<float> {
public:
	LightMonitor(AdvancedLightDriver *pAdvLightDriver);
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
	void dim(float value);
private:
    float calculateCurrentUpperLimit();
    float getTemperaturePIDControlVariable();
    float calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt);
	AdvancedLightDriver *pAdvLightDriver;
	float maxAppliableCurrent = 1.0;
	float Kp = 0.001f;
	float Ki = 0.000015f;
	float Kd = 0.5f;
	float temperatureErrorIntegral;
	float temperatureError_1, temperatureError_2;
};

#endif
