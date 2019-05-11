#ifndef __LED_H__
#define __LED_H__

#include "../IO/IO.h"
#include "../IO/DigitalOutput.h"
#include "Component.h"

/*
Name: LED
Include: #include <ArduinoComponents/Components/LED.h>
Sentence: A class for representing a LED, turning it on, off or toggling it. 
BasicUsage:
	// For a LED connected on pin 13
	LED led(13);

	led.on(); // turns the led on
	led.off(); // turns off the led

	led.toggle(); // switches the led off or on (toggle)
Notes:
	- LED has no state "events" so you dont HAVE to call loop, but you should, for uniformity.
*/

namespace components {
	class LED : public Component {
	public:
		LED(PinNumber pin, State startState = State::Low);
		LED(DigitalOutput out, State startState = State::Low);

		void on();
		void off();
		void toggle();
		void set(State state);
		bool isOn() const {return _state == State::High; }

	private:
		DigitalOutput _output;
		State _state;

		void privateLoop() {}
	};
};

#endif