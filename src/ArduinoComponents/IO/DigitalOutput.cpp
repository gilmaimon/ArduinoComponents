#include "DigitalOutput.h"
#include <Arduino.h>

namespace components {
	DigitalOutput::DigitalOutput(PinNumber pin) : IO_Pin(pin) {
		pinMode(pinNumber(), OUTPUT);
	}

	void DigitalOutput::high() {
		digitalWrite(pinNumber(), true);
	}

	void DigitalOutput::low() {
		digitalWrite(pinNumber(), false);
	}

	void DigitalOutput::write(State s) {
		if(s == State_Low) low();
		else if (s == State_High) high();
	}

	DigitalOutput::~DigitalOutput() {}
};