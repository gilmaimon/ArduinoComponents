#ifndef __LED_H__
#define __LED_H__

#include "../IO/IO.h"
#include "../IO/DigitalOutput.h"

namespace components {
	class LED {
	public:
		LED(PinNumber pin, State startState = State_Low);
		LED(DigitalOutput out, State startState = State_Low);

		void on();
		void off();
		void toggle();
		void set(State state);
		bool isOn() const {return _state == State_High; }

	private:
		State _state;
		DigitalOutput _output;
	};
};

#endif