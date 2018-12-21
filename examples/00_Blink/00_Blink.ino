#include <ArduinoComponents.h>

using namespace components;

DigitalOutput led(13);

void setup() {}

void loop() {
	led.high();
	millisDelay(1000);
	led.low();
	millisDelay(1000);
}