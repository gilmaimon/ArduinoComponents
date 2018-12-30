#include "TimedDispatch.h"
#include "../IO/IO.h"
#include "Ref.h"

namespace components {
	TimedDispatch::TimedDispatch(Ref<Component> parent, VoidCallback callback) : 
		Component(parent), 
		timeoutCallback(callback), 
		timeLeft(0), 
		timerRunning(false), 
		lastMillis(0) {

	}

	void TimedDispatch::disptach_delayed(unsigned long delay) {
		cancel();
		timeLeft = delay;
		timerRunning = true;
		lastMillis = millisTime();
	}

	void TimedDispatch::cancel() {
		timerRunning = false;
	}

	void TimedDispatch::privateLoop() {
		unsigned long newMillis = millisTime();
		if(!timerRunning) return;
		if(newMillis - lastMillis > timeLeft) {
				cancel();
				timeoutCallback();
			} else {
			timeLeft -= (newMillis - lastMillis);
			lastMillis = newMillis;
		}
	}
};