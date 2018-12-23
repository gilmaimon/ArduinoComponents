#include "NonBlockingBlinkingLed.h"

NonBlockingBlinkingLed::NonBlockingBlinkingLed(components::LED led, unsigned interval) : blinking(true), led(led) {
	resumeBlinking(interval);
}

NonBlockingBlinkingLed::NonBlockingBlinkingLed(components::LED led) : blinking(false), led(led) {}
	
void NonBlockingBlinkingLed::resumeBlinking(long interval) {
	if(blinking && interval == blinkInterval) return;
	
	blinking = true;
	millisLeft = blinkInterval = interval;
	lastMillis = components::millisTime();
}

void NonBlockingBlinkingLed::stopBlinking() {
	blinking = false;
}

void NonBlockingBlinkingLed::privateLoop() {
	if(!blinking) return;
	
	auto deltaSinceLastUpdate = components::millisTime() - lastMillis;
	lastMillis = components::millisTime();
	millisLeft -= deltaSinceLastUpdate;
	
	if (millisLeft < 0) {
		millisLeft = blinkInterval;
		led.toggle();
	}
}

void NonBlockingBlinkingLed::on() {
	stopBlinking();
	led.on();
}

void NonBlockingBlinkingLed::off() {
	stopBlinking();
	led.off();
}