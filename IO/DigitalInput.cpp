#include "DigitalInput.h"
#include <Arduino.h>

DigitalInput::DigitalInput(PinNumber pin, InputPull pull) : IO_Pin(pin) {
	if(pull == InputPull_None) pinMode(pin, INPUT);
	else if(pull == InputPull_Up) pinMode(pin, INPUT_PULLUP);
	else if(pull == InputPull_Down) "NotSupported!!";

}

DigitalInput::DigitalInput(PinNumber pin) : DigitalInput(pin, InputPull_None) {}

bool DigitalInput::isHigh() {
	return digitalRead(pinNumber());
}

bool DigitalInput::isLow() {
	return !isHigh();
}