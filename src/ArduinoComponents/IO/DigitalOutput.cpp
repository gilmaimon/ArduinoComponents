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
		if(s == State::Low) low();
		else if (s == State::High) high();
	}

	DigitalOutput::~DigitalOutput() {}
};