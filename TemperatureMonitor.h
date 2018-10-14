#ifndef LIGHTTEMPERATUREMONITORTASK_H
#define LIGHTTEMPERATUREMONITORTASK_H

#include <inttypes.h>
#include <stddef.h>
#include "Task.h"
#include "Dimmable.h"

#define TEMPERATURE_TARGET 50.0f
#define TEMPERATURE_MAX_ERROR 500.0f
#define CURRENT_ACTIVATION_THRESHOLD 0.2f

class AdvancedLightDriver;
class ProtectedLithiumBattery;

class TemperatureMonitor: public Task, public Dimmable<float> {
public:
	TemperatureMonitor(AdvancedLightDriver *pAdvLightDriver);
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
private:
    float calculateMaxRelativeCurrent();
    float getTemperaturePIDControlVariable();
    float calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt);
	AdvancedLightDriver *pAdvLightDriver;
	float Kp = 0.002f;
	float Ki = 0.000025f;
	float Kd = 1.5f;
	float temperatureErrorIntegral;
	float temperatureError_1, temperatureError_2;
};

#endif
