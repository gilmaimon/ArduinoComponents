#include <ArduinoComponents.h>

using namespace components;

#define BTN_PIN 8
#define LED_PIN 13

// Initialize an input object for the button that is pulled to high
DigitalInput button(BTN_PIN, InputPull::Up);
DigitalOutput led(LED_PIN);

void setup() {}

bool isButtonPressed() {
	// Button pin is normally high (because it is pulled up)
	// When the button is pressed, reading will be low (Ground)
	return button.isLow();
}

// The led will be on when the button is pressed
void loop() {
	if(isButtonPressed()) {
		led.high();
	} else {
		led.low();
	}
}