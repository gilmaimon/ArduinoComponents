#ifndef __DIGITALINPUT_H__
#define __DIGITALINPUT_H__

#include "IO.h"

namespace components {
	class DigitalInput : public IO_Pin {
	public:
		DigitalInput(PinNumber, InputPull);
		DigitalInput(PinNumber);
		bool isHigh();
		bool isLow();
	};
};

#endif
