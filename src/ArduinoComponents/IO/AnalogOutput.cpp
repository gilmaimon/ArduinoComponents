#include "AnalogOutput.h"
#include <Arduino.h>

AnalogOutput::AnalogOutput(PinNumber pin) : DigitalOutput(pin) {}

void AnalogOutput::write(float value) {
	analogWrite(pinNumber(), 255 * value);
}

AnalogOutput::~AnalogOutput() {}
