#include "LightMonitor.h"

#include "defines.h"
#include <float.h>
#include "LightDriver.h"

#define LIGHT_MONITOR_LEVEL_TRANSITION_DURATION_MS 2000

LightMonitor::LightMonitor(LightDriver *pLightDriver) :
		Task(MsToTaskTime(LIGHT_LEVEL_MONITORING_INTERVAL_MS)), pLightDriver(
				pLightDriver) {
	setInstanceName("lgtMon");
}

bool LightMonitor::OnStart() {
	traceIfNamed("OnStart");

	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	return true;
}

void LightMonitor::OnStop() {
	traceIfNamed("OnStop");

	pLightDriver->currentPotentiometer.setLevelMaxLimit(1.0f);
}

void LightMonitor::OnUpdate(uint32_t deltaTime) {
	traceIfNamed("OnUpdate");

	float temperatureCurrentLimit = calculateTemperatureCurrentLimit();

	pLightDriver->currentPotentiometer.setLevelMaxLimit(
			min(levelMaxLimit, temperatureCurrentLimit),
			LIGHT_MONITOR_LEVEL_TRANSITION_DURATION_MS);
}

float LightMonitor::calculateTemperatureCurrentLimit() {
	float temperatureCurrentLimit = 1.0f;

	float currentLevel = pLightDriver->currentPotentiometer.getLevel();

	if (currentLevel > CURRENT_ACTIVATION_THRESHOLD) {
		float temperaturePIControlVariable = getTemperaturePIDControlVariable();

		temperatureCurrentLimit = levelMaxLimit
				* (1.0f + temperaturePIControlVariable);

		traceIfNamed(
				"TempPIDControlVariable: %f, temperatureCurrentLimit: %f",
				temperaturePIControlVariable, temperatureCurrentLimit);
	}

	return _constrain(temperatureCurrentLimit, 0.0f, 1.0f);
}

float LightMonitor::getTemperaturePIDControlVariable() {
	float dt = LIGHT_LEVEL_MONITORING_INTERVAL_MS / 1000.0f;

	float temperature = pLightDriver->getEmitterTemperature();

	traceIfNamed("temp: %f", temperature);

	float temperatureError = TEMPERATURE_TARGET - temperature;

	temperatureErrorIntegral += temperatureError * dt;
	temperatureErrorIntegral =
			temperatureErrorIntegral < 0.0f ?
					max(temperatureErrorIntegral, -TEMPERATURE_MAX_ERROR) :
					min(temperatureErrorIntegral, TEMPERATURE_MAX_ERROR);

	float derivative = calculateDerivate(temperatureError, temperatureError_1,
			temperatureError_2, dt);

	temperatureError_2 = temperatureError_1;
	temperatureError_1 = temperatureError;

	traceIfNamed("Kp * error: %f, Ki * errorIntegral %f, Kd * der: %f", Kp * temperatureError, Ki * temperatureErrorIntegral, Kd * derivative);

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


