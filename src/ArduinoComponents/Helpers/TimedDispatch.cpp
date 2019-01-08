#include "TimedDispatch.h"
#include "../IO/IO.h"
#include "Ref.h"

namespace components {
	TimedDispatch::TimedDispatch(Ref<Component> parent, VoidCallback callback) : 
		Component(parent), 
		timeoutCallback(callback), 
		timerRunning(false), 
		deadline(0) {

	}

	void TimedDispatch::disptach_delayed(unsigned long delay) {
		cancel();
		timerRunning = true;
		deadline = millisTime() + delay;
	}

	void TimedDispatch::cancel() {
		timerRunning = false;
	}

	bool TimedDispatch::isRunning() {
		return timerRunning;
	}

	void TimedDispatch::privateLoop() {
		if(!timerRunning) return;
		if(millisTime() >= deadline) {
				cancel();
				timeoutCallback();
		}
	}
};