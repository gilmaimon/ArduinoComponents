#include "Timer.h"
#include "../IO/IO.h"
#include "../Helpers/Ref.h"

namespace components {
	Timer::Timer(Ref<Component> parent) : 
		Component(parent),
		timeoutCallback([](){}),
		timerRunning(false), 
		deadline(0) {
	}

	void Timer::setTimeout(VoidCallback callback, unsigned long delay) {
		cancel();
		timerRunning = true;
		timeoutCallback = callback;
		deadline = millisTime() + delay;
	}

	void Timer::cancel() {
		timerRunning = false;
	}

	bool Timer::isRunning() {
		return timerRunning;
	}
	
	unsigned long Timer::timeLeft() {
		return deadline - millisTime();
	}

	void Timer::privateLoop() {
		if(!timerRunning) return;
		if(millisTime() >= deadline) {
				cancel();
				timeoutCallback();
		}
	}
};