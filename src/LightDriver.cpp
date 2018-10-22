#include "LightDriver.h"

#include <SPI.h>
#include "utils.h"

LightDriver::LightDriver() {
	trace("Inst. LD");
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, HIGH);
	lightStatus = LightStatus::OFF;
	Utils::setPwmFrequency(LED_PIN, 256);
	SPI.begin();
	digitalWrite(PIN_SPI_SS, LOW); // 0.429 -> 0.168 mA
}

void LightDriver::setup() {
	trace("LD::setup");
	setCurrentLevel(0.0f);
}

LightStatus LightDriver::getLightStatus() {
	return lightStatus;
}

float LightDriver::getCurrentLevel() {
	return currentLevel;
}

uint8_t LightDriver::getPwmAmount() {
	return pwmAmount;
}

void LightDriver::setCurrentLevel(float level) {
	debug("LD::setCurrentLevel " + level);
	// Imin senza pwm = 0.191 * 3 = 0.573 A
	// Imax = 0.616 * 3 = 1.848 A

	// Ioff = 0.16 mA -> 0.694 -> 0.429
	// ILED_ON(light off) = 9.15
	/*
	 il rapporto tra la corrente massima e quella minima ottenibile senza usare pwm è del 3.1%
	 */
	currentLevel = constrain(level, 0.0f, 1.0f);
	float K = 0.031f;
	float x;
	if (currentLevel <= K) {
		pwmAmount = 255 * currentLevel / K;
		x = 0;
	} else {
		pwmAmount = 255;
		x = (currentLevel - K) / (1.0f - K);
	}
	
	if (lightStatus == LightStatus::ON) {
		trace("LD pwmAmount: " + pwmAmount);
		analogWrite(LED_PIN, 255 - pwmAmount);
	}

	digPotWrite((int) (256 * (1.0f - x)));
}

void LightDriver::switchLightStatus(LightStatus lightStatus) {
	trace("LD::switchLightStatus " + (lightStatus == LightStatus::ON ? "ON" : "OFF"));
	if (lightStatus == LightStatus::ON) {
		analogWrite(LED_PIN, 255 - pwmAmount); // (255 - pwm) because of negative logic of shuttown pin of LM2596
	} else {
		digitalWrite(LED_PIN, HIGH);
	}
	this->lightStatus = lightStatus;
}

void LightDriver::toggleLightStatus() {
	switchLightStatus(lightStatus == LightStatus::ON ? LightStatus::OFF : LightStatus::ON);
}

void LightDriver::digPotWrite(unsigned int value) {
	trace("LD::digPotWrite " + value);
	SPI.transfer16(0x01FF & value);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, HIGH);
	delayMicroseconds(250);
	digitalWrite(PIN_SPI_SS, LOW);
}
