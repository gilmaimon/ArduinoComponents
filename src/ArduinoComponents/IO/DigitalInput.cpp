#include "DigitalInput.h"
#include <Arduino.h>

namespace components {
	DigitalInput::DigitalInput(PinNumber pin, InputPull pull) : IO_Pin(pin) {
		if(pull == InputPull::None) pinMode(pin, INPUT);
		else if(pull == InputPull::Up) pinMode(pin, INPUT_PULLUP);
		else if(pull == InputPull::Down) {
			//NOT SUPPORTED
		}
	}

	DigitalInput::DigitalInput(PinNumber pin) : DigitalInput(pin, InputPull::None) {}

	bool DigitalInput::isHigh() {
		return digitalRead(pinNumber());
	}

	bool DigitalInput::isLow() {
		return !isHigh();
	}
};