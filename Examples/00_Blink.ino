// Note: Uncomment next line to set this file as main
//#define BLINK_IS_MAIN
#ifdef BLINK_IS_MAIN

#include "IO/IO.h"
#include "IO/DigitalOutput.h"

DigitalOutput led(13);

void setup() {}

void loop() {
	led.high();
	millisDelay(1000);
	led.low();
	millisDelay(1000);
}

#endif