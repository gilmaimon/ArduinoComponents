#ifndef __TIMER_H__
#define __TIMER_H__

#include "../Helpers/VoidCallback.h"
#include "Component.h"

/*
Name: Timer
Include: #include <ArduinoComponents/Components/Timer.h>
Sentence: A class for calling a callback function after specified delay.
BasicUsage:
	// For running code after some delay:
	Timer t;
	t.setTimeout([](){
		// Do Something after the delay
	}, 1000); // 1000 -> is the delay in milliseconds

	// For runnig code in fixed intervals
	Timer t;
	t.onInterval([](){
		// Do Something on intervals
	}, 1500); // 1500 -> is the interval in milliseconds


	// Always needed:
	void loop() {
		// ... Code
		t.loop();
		// ... Code
	}
Notes:
	- Timer has a state so its `loop` function must be called for it to work!
	- You don't have to use lambda function, you could pass a normal function (it must have no parameters).
	- calling setTimeout(..) while timer is already running (when isRunning() returns `true`) will cancel the 
	  already running timer and will restart it for the specified callback and delay.
*/

namespace components {
	class Timer : public Component {
	public:
		Timer(Ref<Component> parent);
		Timer() : Timer(nullptr) {}
		void setTimeout(VoidCallback callback, unsigned long delay);
		void onInterval(VoidCallback callback, unsigned long interval);
		bool isRunning();
		unsigned long timeLeft();
		void cancel();

	private:
		void privateLoop();

		VoidCallback _timeout_callback;
		bool _timer_running;
		unsigned long _deadline;
		
		unsigned _interval;
		bool _intervaling;
	};
};

#endif
