#include "AnalogInput.h"
#include <Arduino.h>

AnalogInput::AnalogInput(PinNumber pin, InputPull pull) : DigitalInput(pin, pull) {}
AnalogInput::AnalogInput(PinNumber pin) : AnalogInput(pin, InputPull::None) {}

float AnalogInput::read() {
	return analogRead(pinNumber()) / 1024.0;
}