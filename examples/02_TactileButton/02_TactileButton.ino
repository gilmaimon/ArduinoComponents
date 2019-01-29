#include <ArduinoComponents.h>
#include "ArduinoComponents/Components/LED.h"
#include "ArduinoComponents/Components/TactileButton.h"

using namespace components;

#define BTN_PIN 8
#define LED_PIN 13

// ** Can also be initialized with DigitalInput:
// TactileButton button(DigitalInput(BTN_PIN, InputPull::InputPull_Up))
TactileButton button(BTN_PIN, TriggerOn::Low, InputPull::Up);
LED led(LED_PIN);

void setup() {
	led.off();

	// Register a callback for the onRelease event
	button.onRelease([](){
		// Led stores its state internally, so it can be toggled
		led.toggle();
		// delay to ignore button debounces
		millisDelay(50);
	});
}

void loop() {
	// we call loop() on button so it can proccess phsical input and call our callbacks
	button.loop();
}