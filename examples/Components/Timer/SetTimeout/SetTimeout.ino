#include <ArduinoComponents.h>
using namespace components;

/*
    This code has 2 phsical components: 
        1. A button connected to pin 8 and being pulled up by Arduino
        2. A led on pin 13
    There is also a 3rd imaginary component - a Timer. With Timer we can schedule code to run after
    some delay or in fixed intervals.
    In this example, every time the button is pressed we turn the led on and schedule to turn it off after 3 second.
    If the button is pressed again, we turn the led on (it might be already on) and schedule the turn off to 3 second 
    from the time it was pressed. if the timer was already running, it basically prospones the callback.
    Effectivly, the led will stay on forever if the button is pressed once every 3 seconds!
*/

TactileButton btn(8, TriggerOn::Low ,InputPull::Up);
Timer timer;
LED led(13);

void setup() {
  led.off();
  btn.onRelease([&](){
    led.on();
    timer.setTimeout([&]() {
      led.off();
    }, 3000);
  });
}

void loop() {
  btn.loop();
  timer.loop();
}