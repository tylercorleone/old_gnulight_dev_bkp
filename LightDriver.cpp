#include "LightDriver.h"

#include <SPI.h>
#include "utils.h"

LightDriver::LightDriver() {
	trace("Inst. LD");
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	lightStatus = LIGHT_STATUS_OFF;
	Utils::setPwmFrequency(LED_PIN, 256);
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void LightDriver::setup() {
	setPotentiometerLevel(0.0f);
}

LightStatus LightDriver::getLightStatus() {
	return lightStatus;
}

float LightDriver::getPotentiometerLevel() {
	return potentiometerLevel;
}

uint8_t LightDriver::getPwmAmount() {
	return pwmAmount;
}

void LightDriver::setPotentiometerLevel(float level) {
	debug("LD::setPotentiometerLevel " + level);
	// Imin senza pwm = 0.191 * 3 = 0.573 A
	// Imax = 0.616 * 3 = 1.848 A

	// Ioff = 0.16 mA -> 0.694 -> 0.429
	// ILED_ON(light off) = 9.15
	/*
	 il rapporto tra la corrente massima e quella minima ottenibile senza usare pwm è del 3.1%
	 */
	potentiometerLevel = constrain(level, 0.0f, 1.0f);
	float K = 0.031f;
	float x;
	if (potentiometerLevel <= K) {
		pwmAmount = 255 * potentiometerLevel / K;
		x = 0;
	} else {
		pwmAmount = 255;
		x = (potentiometerLevel - K) / (1.0f - K);
	}
	trace("pwmAmount: " + pwmAmount);
	if (lightStatus == LIGHT_STATUS_ON) {
		analogWrite(LED_PIN, 255 - pwmAmount);
	}
	digPotWrite((int) (256 * (1.0f - x)));
}

void LightDriver::switchLightStatus(LightStatus lightStatus) {
	trace("LD::switchLightStatus " + (lightStatus == LIGHT_STATUS_ON ? "ON" : "OFF"));
	if (lightStatus == LIGHT_STATUS_ON) {
		analogWrite(LED_PIN, 255 - pwmAmount); // (255 - pwm) because of negative logic of shuttown pin of LM2596
	} else {
		digitalWrite(LED_PIN, HIGH);
	}
	this->lightStatus = lightStatus;
}

void LightDriver::toggleLightStatus() {
	switchLightStatus(lightStatus == LIGHT_STATUS_ON ? LIGHT_STATUS_OFF : LIGHT_STATUS_ON);
}

void LightDriver::digPotWrite(unsigned int value) {
	trace("LD::digPotWrite " + value);
	SPI.transfer16(0x01FF & value);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, HIGH);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, LOW);
}
