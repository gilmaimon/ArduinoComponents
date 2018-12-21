#ifndef __DIGITALOUTPUT_H__
#define __DIGITALOUTPUT_H__

#include "IO.h"

namespace components {
	class DigitalOutput : public IO_Pin {
	public:
		DigitalOutput(PinNumber);
		virtual void high();
		virtual void low();
		void write(State);
		~DigitalOutput();
	};
};
#endif
