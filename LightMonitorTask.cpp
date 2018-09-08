#include "LightMonitorTask.h"
#include "defines.h"
#include "AdvancedLightDriver.h"
#include <float.h>

LightMonitorTask::LightMonitorTask(AdvancedLightDriver *pAdvLightDriver) :
		pAdvLightDriver(pAdvLightDriver), Task(MsToTaskTime(LIGHT_LEVEL_MONITORING_INTERVAL_MS)), Dimmable(1.0f) {
}

bool LightMonitorTask::OnStart() {
	temperatureErrorIntegral = 0.0f;
	temperatureError_1 = temperatureError_2 = FLT_MAX;
	pAdvLightDriver->setDimmableMaxValue(calculateMaxRelativeCurrent());
}

void LightMonitorTask::OnUpdate(uint32_t deltaTime) {
	pAdvLightDriver->setDimmableMaxValue(calculateMaxRelativeCurrent());
	float currentLevel = pAdvLightDriver->LightDriver::getPotentiometerLevel();
	if (currentLevel > pAdvLightDriver->getDimmableMaxValue()) {
		pAdvLightDriver->LightDriver::setPotentiometerLevel(pAdvLightDriver->getDimmableMaxValue());
	} else if (currentLevel < pAdvLightDriver->targetCurrentLevel && currentLevel != pAdvLightDriver->getDimmableMaxValue()) {
		pAdvLightDriver->LightDriver::setPotentiometerLevel(min(pAdvLightDriver->targetCurrentLevel, pAdvLightDriver->getDimmableMaxValue()));
	}
}

float LightMonitorTask::calculateMaxRelativeCurrent() {
	float currentToTemperatureTarget = 1.0f;
	float actualCurrent =
			pAdvLightDriver->LightDriver::getPotentiometerLevel();
	if (actualCurrent > 0.2f) {
		float temperaturePIControlVariable = getTemperaturePIDControlVariable();
		trace("TempPIDControlVariable " + temperaturePIControlVariable);
		currentToTemperatureTarget = actualCurrent * (1.0f + 0.5f * temperaturePIControlVariable);
		trace("currentToTemperatureTarget " + currentToTemperatureTarget);
	}
	return min(currentToTemperatureTarget, getDimmableMaxValue());
}

float LightMonitorTask::getTemperaturePIDControlVariable() {
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

float LightMonitorTask::calculateDerivate(float f_t, float f_t_1, float f_t_2, float dt) {
	if (f_t_2 == FLT_MAX) {
		if (f_t_1 == FLT_MAX) {
			return 0.0f;
		} else {
			return (f_t - f_t_1) / dt;
		}
	}
	return (3.0f * f_t - 4.0f * f_t_1 + f_t_2) / (2.0f * dt);
}
