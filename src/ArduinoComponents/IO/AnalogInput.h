#ifndef __ANALOGINPUT_H__
#define __ANALOGINPUT_H__

#include "IO.h"
#include "DigitalInput.h"

namespace components {
	class AnalogInput : public DigitalInput {
	public:
		AnalogInput(PinNumber, InputPull);
		AnalogInput(PinNumber);
		float read();
	};
};
#endif
