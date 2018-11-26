#include "LightMonitor.h"
#include <float.h>
#include "Gnulight.h"

#define LIGHT_MONITOR_LEVEL_TRANSITION_MS 2000

LightMonitor::LightMonitor(Gnulight *gnulight) :
		Task(MsToTaskTime(LIGHT_MONITOR_INTERVAL_MS)), Named("lgtMon"), gnulight(
				gnulight) {
}

bool LightMonitor::OnStart() {
	traceIfNamed("OnStart");

	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	return true;
}

void LightMonitor::OnStop() {
	traceIfNamed("OnStop");

	gnulight->lightDriver.currentPotentiometer.setLevelMaxLimit(1.0f);
}

void LightMonitor::OnUpdate(uint32_t deltaTime) {
	traceIfNamed("OnUpdate");

	float batteryCurrentLimit = 1.0f;

	if (gnulight->batteryMonitor != nullptr) {
		batteryCurrentLimit =
				gnulight->batteryMonitor->calculateInstantaneousMaxCurrent();
	}

	float temperatureCurrentLimit = calculateTemperatureCurrentLimit();

	gnulight->lightDriver.currentPotentiometer.setLevelMaxLimit(
			min(batteryCurrentLimit, temperatureCurrentLimit),
			LIGHT_MONITOR_LEVEL_TRANSITION_MS);
}

float LightMonitor::calculateTemperatureCurrentLimit() {
	float temperatureCurrentLimit = 1.0f;

	if (gnulight->lightDriver.currentPotentiometer.getLevel() > CURRENT_ACTIVATION_THRESHOLD) {
		float PIDvar = getTemperaturePIDControlVariable();

		temperatureCurrentLimit =
				gnulight->lightDriver.currentPotentiometer.getLevelMaxLimit()
						* (1.0f + PIDvar);

		traceIfNamed("PID: %f, tempCurrentLimit: %f", PIDvar, temperatureCurrentLimit);
	}

	return _constrain(temperatureCurrentLimit, 0.0f, 1.0f);
}

float LightMonitor::getTemperaturePIDControlVariable() {
	float dt = LIGHT_MONITOR_INTERVAL_MS / 1000.0f;

	float temperatureError = EMITTER_TARGET_TEMPERATURE
			- gnulight->lightDriver.getEmitterTemperature();

	traceIfNamed("temp: %f", EMITTER_TARGET_TEMPERATURE - temperatureError);

	temperatureErrorIntegral += temperatureError * dt;
	temperatureErrorIntegral = _constrain(temperatureErrorIntegral,
			-TEMPERATURE_MAX_ERROR, TEMPERATURE_MAX_ERROR);

	float derivative = calculateDerivate(temperatureError, temperatureError_1,
			temperatureError_2, dt);

	temperatureError_2 = temperatureError_1;
	temperatureError_1 = temperatureError;

	traceIfNamed("P: %f, I: %f, D: %f", Kp * temperatureError, Ki * temperatureErrorIntegral, Kd * derivative);

	return Kp * temperatureError + Ki * temperatureErrorIntegral
			+ Kd * derivative;
}

float LightMonitor::calculateDerivate(float f_t, float f_t_1, float f_t_2,
		float dt) {

	if (f_t_2 == FLT_MAX) {
		if (f_t_1 == FLT_MAX) {
			return 0.0f;
		} else {
			return (f_t - f_t_1) / dt;
		}
	}

	return (3.0f * f_t - 4.0f * f_t_1 + f_t_2) / (2.0f * dt);
}

