#ifndef __NONBLOCKINGBLINKINGLED_H__
#define __NONBLOCKINGBLINKINGLED_H__

#include "LED.h"
#include "Component.h"
#include "../IO/IO.h"

class NonBlockingBlinkingLed : public components::Component {
public:
	NonBlockingBlinkingLed(components::LED led, unsigned interval);
	NonBlockingBlinkingLed(components::LED led);
		
	void resumeBlinking(long interval);
	void stopBlinking();
	void on();
	void off();

private:
	components::LED led;
	long millisLeft;
	long lastMillis;
	int blinkInterval;
	bool blinking;
	
	void privateLoop();
};

#endif //__NONBLOCKINGBLINKINGLED_H__
