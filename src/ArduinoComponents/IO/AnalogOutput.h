#ifndef __ANALOGOUTPUT_H__
#define __ANALOGOUTPUT_H__

#include "IO.h"
#include "DigitalOutput.h"
namespace components {
	class AnalogOutput : public DigitalOutput {
	public:
		AnalogOutput(PinNumber);
		void write(float);
		~AnalogOutput();
	private:
		#ifdef ARDUINO_ARCH_ESP32
			unsigned char pwmChannel;
		#endif
	};
};

#endif
