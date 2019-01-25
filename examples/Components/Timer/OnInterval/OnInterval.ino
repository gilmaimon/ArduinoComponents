#include <ArduinoComponents.h>
using namespace components;

/*
    This sketch only uses a LED connected to pin 13.
    We set a timer to execute our code on fixed intervals. so every 1s our callback runs.
    The callback will toggle the led's state so effectivly, the result is a blinking led.
*/

Timer timer;
LED led(13);

void setup() {
  timer.onInterval([&](){
    led.toggle();
  }, 1000);
}

void loop() {
  timer.loop();
}