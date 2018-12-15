#ifndef __ANALOGOUTPUT_H__
#define __ANALOGOUTPUT_H__

#include "IO.h"
#include "DigitalOutput.h"

class AnalogOutput : public DigitalOutput {
public:
	AnalogOutput(PinNumber);
	void write(float);
	~AnalogOutput();
};

#endif
