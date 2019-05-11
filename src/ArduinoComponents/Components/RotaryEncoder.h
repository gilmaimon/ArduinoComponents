#ifndef __ROTARYENCODER_H__
#define __ROTARYENCODER_H__

/*
	Credit for this code goes to @HaxorGate
	See the github issue: https://github.com/gilmaimon/ArduinoComponents/issues/10
*/
#include <Arduino.h>
#include "TactileButton.h"
#include "Component.h"
namespace components
{
	class RotaryEncoder : public Component
	{
		public:
			RotaryEncoder( uint8_t a, uint8_t b, uint8_t clicks = 0 );
		private:
			int32_t rotation;
			int32_t onRotate( int8_t dr );
			uint8_t detents;
			TactileButton A;
			TactileButton B;
			void privateLoop( void );
	};
}

#endif