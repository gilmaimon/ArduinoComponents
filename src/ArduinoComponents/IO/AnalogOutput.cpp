#include "AnalogOutput.h"
#include <Arduino.h>

namespace components {

#ifdef ARDUINO_ARCH_ESP32
	AnalogOutput::AnalogOutput(PinNumber pin) : DigitalOutput(pin) {
		static unsigned char pwmChannelCounter = 0;

		this->pwmChannel = pwmChannelCounter++;
		ledcAttachPin(pin, this->pwmChannel);
		ledcSetup(this->pwmChannel, 12000, 8);
	}

	void AnalogOutput::write(float value) {
		ledcWrite(this->pwmChannel, 255 * value);
	}
#else
	AnalogOutput::AnalogOutput(PinNumber pin) : DigitalOutput(pin) {}

	void AnalogOutput::write(float value) {
		analogWrite(pinNumber(), 255 * value);
	}
#endif
	AnalogOutput::~AnalogOutput() {}
};