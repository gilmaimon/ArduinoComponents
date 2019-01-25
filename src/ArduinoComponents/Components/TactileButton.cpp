#include "TactileButton.h"

namespace components {
	TactileButton::TactileButton(Ref<Component> parent, DigitalInput input, TriggerOn trigger) : Component(parent), _input(input), _pressed(false), _on_press([](){}), _on_release([](){}), _trigger(trigger) {}
	TactileButton::TactileButton(Ref<Component> parent, PinNumber pin, TriggerOn trigger, InputPull pull) : TactileButton(parent, DigitalInput(pin, pull), trigger) {}

	void TactileButton::onPress(VoidCallback cbk) {
		this->_on_press = cbk;
	}

	void TactileButton::onRelease(VoidCallback cbk) {
		this->_on_release = cbk;
	}

	void TactileButton::privateLoop() {	
		bool pressedState = (_trigger == TriggerOn::Low)? _input.isLow(): _input.isHigh();
		if(pressedState != _pressed) {
			if(pressedState == true) _on_press();
			else if(pressedState == false) _on_release();
			_pressed = pressedState;
		}
	}
};