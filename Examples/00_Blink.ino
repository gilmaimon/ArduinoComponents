// Note: Uncomment next line to set this file as main
//#define BLINK_IS_MAIN
#ifdef BLINK_IS_MAIN

#include "IO/DigitalOutput.h"

DigitalOutput led(LED_BUILTIN);

void setup() {}

void loop() {
	led.high();
	delay(1000);
	led.low();
	delay(1000);
}

#endif