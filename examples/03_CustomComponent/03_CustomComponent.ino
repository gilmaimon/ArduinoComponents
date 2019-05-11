#include <ArduinoComponents.h>

using namespace components;

class ButtonToggledLED : public Component {
public:
	ButtonToggledLED(PinNumber buttonPin, PinNumber ledPin) : 
		Component(), 
		led(ledPin, State::Low), 
		button(buttonPin, TriggerOn::Low, InputPull::Up) {

		// When we register a components as a child, it's loop is called every time our loop is called
		// So instead of us needing to call it's loop, it is called automaticaly and the object 
		// is ready to use and read when execution arrives to this->privateLoop
		RegisterChild(button);
		
		// Register a callback for the onRelease event
		button.onRelease([&](){
			// Led stores its state internally, so it can be toggled
			led.toggle();
			// delay to ignore button debounces
			millisDelay(50);
		});
	}

private:
	LED led;
	TactileButton button;

	void privateLoop() {
		// By the time this function is called, `button`'s loop had already been executed
		// and onRelease was called (if the button was actually released), so there is no
		// work to be done in this function.
	}
};

#define BTN_PIN 8
#define LED_PIN 13

ButtonToggledLED app(BTN_PIN, LED_PIN);
void setup() {}

void loop() {
	app.loop();
}