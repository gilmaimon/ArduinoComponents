#ifndef __TACTILEBUTTON_H__
#define __TACTILEBUTTON_H__

#include "../IO/IO.h"
#include "../IO/DigitalInput.h"
#include "../Helpers/VoidCallback.h"
#include "Component.h"

/*
Name: TactileButton
Include: #include <ArduinoComponents/Components/TactileButton.h>
Sentence: A class for representing phsical button and acting upon actins (press and release).
BasicUsage:
	// For a button connected on pin 8 and GND (shorted to GND when pressed)
	void doSomethingWhenPressed() {
		// ... Code
	}

	void doSomethingWhenReleased() {
		// ... Code
	}
	
	TactileButton btn(8, TriggerOn::Low ,InputPull::Up);
	btn.onPress(doSomethingWhenPressed);
	btn.onRelease(doSomethingWhenReleased);

	// Must Call loop!
	void loop() {
		// ... Code
		btn.loop();
		// ... Code
	}
Notes:
	- TactileButton has a state so its `loop` function must be called for it to work!
	- You can also use lambda functions (it must have no parameters - a proper void callback).
*/

namespace components {
	class TactileButton : public Component {
	public:
		TactileButton(DigitalInput input, TriggerOn trigger) : TactileButton(nullptr, input, trigger) {}
		TactileButton(Ref<Component> parent, DigitalInput input, TriggerOn trigger);
		TactileButton(PinNumber pin, TriggerOn trigger, InputPull pull = InputPull::None) : TactileButton(nullptr, pin, trigger, pull) {}
		TactileButton(Ref<Component> parent, PinNumber pin, TriggerOn trigger, InputPull pull = InputPull::None);

		void onPress(VoidCallback cbk);
		void onRelease(VoidCallback cbk);

		bool isPressed();
		
	private:
		DigitalInput _input;
		bool _pressed;
		VoidCallback _on_press;
		VoidCallback _on_release;
		TriggerOn _trigger;

		void privateLoop();
	};
};
#endif
