[![arduino-library-badge](http://www.ardu-badge.com/badge/ArduinoComponents.svg?)](http://www.ardu-badge.com/ArduinoComponents) [![Build Status](https://travis-ci.org/gilmaimon/ArduinoComponents.svg?branch=master)](https://travis-ci.org/gilmaimon/ArduinoComponents)

Quick Jump:
* [Getting Started](#Getting-Started)
* [Basics](#Basics)
* [Component](#Component)
* [Examples](#Examples)
* [Contributing](#Contributing)
* [License](#License)

# Arduino Components
Components is a project that aims to help electronics hobbyists to write code for Arduino that is:
- **Modern** - Take advantage of the included Helper Classes (Vector, Function, TimedDispatch...) and write event driven code
- **Reusable** - Reuse existing components or your own from past projects
- **Extendable** - Make your own (hardware independent) components and use base components from the library
- **Testable** - Centralize Platform dependent code. Mock and test components individually

&nbsp;
![Structure](https://github.com/gilmaimon/ArduinoComponents/blob/master/Components.png)

## Getting Started

### Prerequisites
You can get the latest library version via the built in [Arduino IDE Library Manager](https://www.arduino.cc/en/guide/libraries) or get the ZIP file with the source code from the [GitHub release](https://github.com/gilmaimon/ArduinoComponents/releases) page.

### Dependencies
**There are none!** This library (in it's current form) is fully self contained.

*UPDATE 12.01.2019: If you wish to use the experimental RF componenets you will need to `#define EXPERIMENTAL_RF`and to have the following libraries installed:*
- *[RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/) - Packet Radio library for embedded microprocessors.*
- *[rc-switch](https://github.com/sui77/rc-switch) - Arduino lib to operate 433/315Mhz devices.*
### Project Structure
- **IO** - includes the basic IO classes such as `DigitalInput`, `DigitalOutput`, `AnalaogInput`, `millisTime` (and more)
- **Components** - includes a few useful components such as `LED`, `TactileButton` and some more experimental RF classes. *Open for contributions and extensions!*
- **Helpers** - includes useful helper classes such as `Vector`, `Function` and `Ref`

## Basics
### Basic IO
For basic digital and analog input and output this library provides the following utilities:
#### Digital IO
```C++
// initiates digital output on pin 13
DigitalOutput led(13); 
// pin can be controlled with:
led.high();
led.low();

// initiates digital input on pin 8
DigitalInput in(8);
if(in.isHigh()) {
  // Do something when HIGH
}
if(in.isLow()) {
  // Do something when LOW
}
```

#### Analog IO
```C++
// initiates PWM output on pin 9 (pwm on UNO)
AnalogOutput led(9);
// pwm values should be between 0.0 and 1.0
led.write(0.25); // led is 25% on 

// pwm pins can also be controlled with:
led.high();
led.low();

// initiates analog input on pin 8
AnalogInput in(8);
float reading = in.read(); // returns a value from 0.0 to 1.0
if(reading > 0.75) {
  // Do something when higher than 75%
}
```

## Component

`Component` represents the base class for all components. this is the class to extend if you want to create custom components.
Custom components should:
- Override `privateLoop`
- Call `RegisterChild` on children (not mendatory)

### Interface
``` c++
class Component {
public:
    Component(Ref<Component> parent = nullptr);
    
    // loop is the public interface for proccessing input and inner class state. Notice it is not virtual.
    // loop will call `loop` on all children and than call `privateLoop`
    void loop();

protected:
    // `RegisterChild` stores a reference to the child in a vector so later (on `loop`) 
    //  the child's `loop` could be called
    void RegisterChild(Ref<Component> child);
    
    // `SkipLoop` will stop the current looping and will restart looping from the root parent. This is
    // useful when  we dont want to run any code after a certain event or input
    void SkipLoop();

private:
    // `loopChildren` will call the `loop` function on all the children that were registered (via `RegisterChild`)
    void loopChildren();
    
    // `privateLoop` is the function that derived classes can override and populate with 
    // whatever the object need to do 
    virtual void privateLoop() = 0;
};
```

For built-in components [Click Here](https://github.com/gilmaimon/ArduinoComponents/tree/master/src/ArduinoComponents/Components)  
View the `Examples` section below for more examples of components creation and usage.

## Examples
* [Examples](#Examples)
	* [Blink](#Blink)
	* [Basic IO](#Basic-IO)
	* [Higher Level Components](#Higher-Level-Components)
	* [Custom Components](#Custom-Components)
	
### Blink
This is a good example for using the built in `DigitalOutput` class. **Notice** how you don't need to rewrite the pin number every time and there is no risk of forgetting to write `pinMode(...)` etc.
```c++
DigitalOutput led(LED_BUILTIN);

void setup() {}

void loop() {
    led.high();
    delay(1000);
    led.low();
    delay(1000);
}
```

### Basic IO
This example uses `DigitalInput` and `DigitalOutput` to light up an LED when a button is pressed down.

```c++
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
```

### Higher Level Components
This example shows how to use "Higher Level" components such as `LED` and `TactileButton` to create a sketch that toggles LED state on button presses.
**Notice** how button calls a callback when it is released (input goes from high to low). Also notice how all the code is in setup - responding to the event instead of manually checking in the `loop` function. 
```c++
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
```

### Custom Components
This example is a bit more advanced. It shows a way to create a custom component (an object that extends `Component`) that has a button and an led. This sketch is another way to write the previous example.
```c++
class ButtonToggledLED : public Component {
public:
	ButtonToggledLED(PinNumber buttonPin, PinNumber ledPin) : 
		Component(), 
		led(ledPin, State::Low), 
		button(buttonPin, TriggerOn::Low, InputPull::Up) {

		// When we register a components as a child, it's loop is called every time our loop is called
		// So instead of us needing to call it's loop, it is called automaticaly and the object 
		// is ready to use and read when execution arrives to this->privateLoop
		RegisterChild(button);
		
		// Register a callback for the onRelease event
		button.onRelease([&](){
			// Led stores its state internally, so it can be toggled
			led.toggle();
			// delay to ignore button debounces
			delay(50);
		});
	}

private:
	TactileButton button;
	LED led;

	void privateLoop() {
		// By the time this function is called, `button`'s loop had already been executed
		// and onRelease was called (if the button was actually released), so there is no
		// work to be done in this function.
	}
};

#define BTN_PIN 8
#define LED_PIN 13

ButtonToggledLED app(BTN_PIN, LED_PIN);
void setup() {}

void loop() {
	app.loop();
}
```

## Contributing
Contributions are welcomed! You can help by:
- Try the library out! Open issues and help others
- Write custom components or share components you wrote for your own projects
- Add examples
- Fix bugs and documentation
- Suggest refactoring and challenge design decisions

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
