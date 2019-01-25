#include "Timer.h"
#include "../IO/IO.h"
#include "../Helpers/Ref.h"

namespace components {
	Timer::Timer(Ref<Component> parent) : 
		Component(parent),
		_timeout_callback([](){}),
		_timer_running(false), 
		_deadline(0) {
	}

	void Timer::setTimeout(VoidCallback callback, unsigned long delay) {
		cancel();
		_intervaling = false;
		_timer_running = true;
		_timeout_callback = callback;
		_deadline = millisTime() + delay;
	}

	void Timer::onInterval(VoidCallback callback, unsigned long interval) {
		cancel();
		
		_interval = interval;
		_intervaling = true;

		_timer_running = true;
		_timeout_callback = callback;
		_deadline = millisTime() + interval;
	}

	void Timer::cancel() {
		_timer_running = false;
	}

	bool Timer::isRunning() {
		return _timer_running;
	}
	
	unsigned long Timer::timeLeft() {
		return _deadline - millisTime();
	}

	void Timer::privateLoop() {
		if(!_timer_running) return;
		if(millisTime() >= _deadline) {
			if(_intervaling) {
				_deadline = millisTime() + _interval;
				_timeout_callback();
			} else {
				cancel();
				_timeout_callback();
			}
		}
	}
};