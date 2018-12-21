#include "IO.h"
#include "Arduino.h"

namespace components {
	unsigned long millisTime() {
		return millis();
	}

	void millisDelay(unsigned millis) {
		delay(millis);
	}
};