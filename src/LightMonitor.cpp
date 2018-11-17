#include "LightMonitor.h"

#include "defines.h"
#include "AdvancedLightDriver.h"
#include <float.h>

#define LIGHT_MONITOR_LEVEL_TRANSITION_DURATION_MS 2000

LightMonitor::LightMonitor(AdvancedLightDriver *pAdvLightDriver) :
		Task(MsToTaskTime(LIGHT_LEVEL_MONITORING_INTERVAL_MS)), pAdvLightDriver(pAdvLightDriver) {
}

bool LightMonitor::OnStart() {
	trace("TM::OnStart");
	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	return true;
}

void LightMonitor::OnStop() {
	trace("TM::OnStop");
	pAdvLightDriver->setCurrentUpperLimit(1.0);
}

void LightMonitor::OnUpdate(uint32_t deltaTime) {
	trace("TM::OnUpdate");
	float newCurrentUpperLimit = calculateCurrentUpperLimit();
	if (newCurrentUpperLimit != pAdvLightDriver->getCurrentUpperLimit()) {
		pAdvLightDriver->setCurrentUpperLimit(newCurrentUpperLimit, LIGHT_MONITOR_LEVEL_TRANSITION_DURATION_MS);
	}
}

float LightMonitor::calculateCurrentUpperLimit() {
	float currentUpperLimit = 1.0f;
	if (pAdvLightDriver->getCurrentLevel() > CURRENT_ACTIVATION_THRESHOLD) {
		float actualCurrentLimit = pAdvLightDriver->getCurrentUpperLimit();
		float temperaturePIControlVariable = getTemperaturePIDControlVariable();
		trace("TempPIDControlVariable: " + temperaturePIControlVariable);
		currentUpperLimit = actualCurrentLimit * (1.0f + temperaturePIControlVariable);
		trace("currentUpperLimit: " + currentUpperLimit);
	}
	return min(currentUpperLimit, maxAppliableCurrent);
}

float LightMonitor::getTemperaturePIDControlVariable() {
	float dt = static_cast<float>(LIGHT_LEVEL_MONITORING_INTERVAL_MS) / 1000.0f;
	float temperature = pAdvLightDriver->getEmitterTemperature();
	trace("Temp. " + temperature);
	float temperatureError = TEMPERATURE_TARGET - temperature;
	temperatureErrorIntegral += temperatureError * dt;
	temperatureErrorIntegral =
			temperatureErrorIntegral < 0.0f ?
					max(temperatureErrorIntegral, -TEMPERATURE_MAX_ERROR) :
					min(temperatureErrorIntegral, TEMPERATURE_MAX_ERROR);
	float derivative = calculateDerivate(temperatureError, temperatureError_1, temperatureError_2, dt);
	temperatureError_2 = temperatureError_1;
	temperatureError_1 = temperatureError;
	trace("Kp * error " + (Kp * temperatureError));
	trace("Ki * errorIntegral " + Ki * temperatureErrorIntegral);
	trace("Kd * der " + Kd * derivative);
	return Kp * temperatureError + Ki * temperatureErrorIntegral
			+ Kd * derivative;
}

float LightMonitor::calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt) {
	if (f_t_2 == FLT_MAX) {
		if (f_t_1 == FLT_MAX) {
			return 0.0f;
		} else {
			return (f_t - f_t_1) / dt;
		}
	}
	return (3.0f * f_t - 4.0f * f_t_1 + f_t_2) / (2.0f * dt);
}

void LightMonitor::dim(float value) {
	maxAppliableCurrent = value;
}
