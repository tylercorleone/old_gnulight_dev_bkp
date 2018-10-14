#include "TemperatureMonitor.h"

#include "defines.h"
#include "AdvancedLightDriver.h"
#include <float.h>

#define LEVEL_TRANSITION_DURATION_MS 200

TemperatureMonitor::TemperatureMonitor(AdvancedLightDriver *pAdvLightDriver) :
		pAdvLightDriver(pAdvLightDriver), Task(MsToTaskTime(LIGHT_LEVEL_MONITORING_INTERVAL_MS)), Dimmable(1.0f) {
}

bool TemperatureMonitor::OnStart() {
	trace("TM::OnStart");
	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	return true;
}

void TemperatureMonitor::OnStop() {
	trace("TM::OnStop");
	pAdvLightDriver->setCurrentUpperLimit(1.0);
}

void TemperatureMonitor::OnUpdate(uint32_t deltaTime) {
	trace("TM::OnUpdate");
	float newCurrentUpperLimit = calculateMaxRelativeCurrent();
	if (newCurrentUpperLimit != pAdvLightDriver->getCurrentUpperLimit()) {
		pAdvLightDriver->setCurrentUpperLimit(calculateMaxRelativeCurrent(), LEVEL_TRANSITION_DURATION_MS);
	}
}

float TemperatureMonitor::calculateMaxRelativeCurrent() {
	float currentToTemperatureTarget = 1.0f;
	float actualCurrent =
			pAdvLightDriver->LightDriver::getPotentiometerLevel();
	if (actualCurrent > CURRENT_ACTIVATION_THRESHOLD) {
		float temperaturePIControlVariable = getTemperaturePIDControlVariable();
		trace("TempPIDControlVariable " + temperaturePIControlVariable);
		currentToTemperatureTarget = actualCurrent * (1.0f + 0.5f * temperaturePIControlVariable);
		trace("currentToTemperatureTarget " + currentToTemperatureTarget);
	}
	return min(currentToTemperatureTarget, getDimmableMaxValue());
}

float TemperatureMonitor::getTemperaturePIDControlVariable() {
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

float TemperatureMonitor::calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt) {
	if (f_t_2 == FLT_MAX) {
		if (f_t_1 == FLT_MAX) {
			return 0.0f;
		} else {
			return (f_t - f_t_1) / dt;
		}
	}
	return (3.0f * f_t - 4.0f * f_t_1 + f_t_2) / (2.0f * dt);
}
