#include "TactileButton.h"

TactileButton::TactileButton(Ref<BaseComponent> parent, DigitalInput input) : BaseComponent(parent), _input(input), _pressed(false), _on_press([](){}), _on_release([](){}) {}
TactileButton::TactileButton(Ref<BaseComponent> parent, PinNumber pin, InputPull pull) : TactileButton(parent, DigitalInput(pin, pull)) {}

void TactileButton::onPress(VoidCallback cbk) {
	this->_on_press = cbk;
}

void TactileButton::onRelease(VoidCallback cbk) {
	this->_on_release = cbk;
}

void TactileButton::privateLoop() {	
	bool pressedState = _input.isLow();
	if(pressedState != _pressed) {
		if(pressedState == true/* && !_on_press.empty()*/) _on_press();
		else if(pressedState == false/* && !_on_release.empty()*/) _on_release();
		_pressed = pressedState;
	}
}