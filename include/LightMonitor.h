#ifndef LIGHTMONITOR_H
#define LIGHTMONITOR_H

#include "gnulight_config.h"

#include <stdint.h>
#include <stddef.h>
#include <Task.h>
#include <CappablePotentiometer.h>

class Gnulight;

#define LIGHT_MONITOR_INTERVAL_MS 10000
#define EMITTER_TARGET_TEMPERATURE 50.0f
#define TEMPERATURE_MAX_ERROR 500.0f
#define CURRENT_ACTIVATION_THRESHOLD 0.2f

class LightMonitor: public Task, public CappablePotentiometer {
public:
	LightMonitor(Gnulight *gnulight);
	bool OnStart() override;
	void OnStop() override;
	void OnUpdate(uint32_t deltaTime) override;
private:
	void levelActuationFunction(float level) override {
		// does nothing
	}
	float calculateTemperatureCurrentLimit();
	float getTemperaturePIDControlVariable();
	float calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt);
	Gnulight *gnulight;
	float Kp = 0.001f;
	float Ki = 0.000015f;
	float Kd = 0.5f;
	float temperatureErrorIntegral;
	float temperatureError_1, temperatureError_2;
};

#endif
