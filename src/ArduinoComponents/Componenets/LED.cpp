#include "LED.h"

namespace components {
	LED::LED(PinNumber pin, State startState) : LED(DigitalOutput(pin), startState) {}
	LED::LED(DigitalOutput out, State startState) : _output(out), _state(startState) {
		_output.write(_state);
	}

	void LED::on() {
		_output.high();
		_state = State_High;
	}

	void LED::off() { 
		_output.low();
		_state = State_Low; 
	}

	void LED::toggle() {
		if(_state == State_Low) on();
		else off();
	}

	void LED::set(State state) {
		if(state == State_Low) off();
		else on();
	}
};