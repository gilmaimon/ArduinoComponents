#include <ArduinoComponents.h>
#include <ArduinoComponents/Components/TimedDispatch.h>
using namespace components;

#define LED_PIN 13

/*
    This example blinks a led without using delay.
    This sketch uses TimedDispatch to set a timer for 1 second,
    when the timer ends, the LED toggles it's state (from high to 
    low and from low to high). This results in a blinking led which 
    demonstrates the basic usage of TimedDispatch. 
*/

LED led(LED_PIN);

// onTimerEnd is the callback that will be called when the timer is over
TimedDispatch dispatch(onTimerEnd);

// the callback toggles the led and resets the timer
void onTimerEnd() {
    led.toggle();
    dispatch.dispatch_delayed(1000);
}

void setup() {
    // set a timer to 1 second
    dispatch.dispatch_delayed(1000);
}

void loop() {
    // the component's loop must be called in order for it to
    // check if the timer has ended and if so, to call the callback
    dispatch.loop();
}