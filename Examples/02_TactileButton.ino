// Note: Uncomment next line to set this file as main
//#define TACTILE_BUTTON_IS_MAIN
#ifdef TACTILE_BUTTON_IS_MAIN

#include "IO/IOComponents.h"
#include "Componenets/TactileButton.h"
#include "Componenets/LED.h"

#define BTN_PIN 3
#define LED_PIN LED_BUILTIN

// ** Can also be initialized with DigitalInput:
// TactileButton button(DigitalInput(BTN_PIN, InputPull::InputPull_Up))
TactileButton button(BTN_PIN, TriggerOn::Low, InputPull::Up);
LED led(LED_PIN);

void setup() {
	led.off();

	// Register a callback for the onRelease event
	button.onRelease([&led](){
		// Led stores its state internally, so it can be toggled
		led.toggle();
		// delay to ignore button debounces
		delay(50);
	});
}

void loop() {
	// we call loop() on button so it can proccess phsical input and call our callbacks
	button.loop();
}


#endif