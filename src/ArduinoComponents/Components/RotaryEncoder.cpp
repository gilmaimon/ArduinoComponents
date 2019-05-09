/*
	Credit for this code goes to @HaxorGate
	See the github issue: https://github.com/gilmaimon/ArduinoComponents/issues/10
*/

#include "RotaryEncoder.h"
namespace components
{
	RotaryEncoder::RotaryEncoder( uint8_t a, uint8_t b, uint8_t clicks )
	:	Component(),
		A( a, TriggerOn::Low, InputPull::Up ),
		B( b, TriggerOn::Low, InputPull::Up ),
		detents( clicks )
	{
		RegisterChild(A);
		A.onPress( [&] {
			if ( B.isPressed() == LOW )
			{
				rotation--;
				onRotate(-1);
			}
			else
			{
				rotation++;
				onRotate(+1);
			}
			delay(5);
		} );
		RegisterChild(B);
		B.onPress( [&] {
			delay(5);
		} );
	}

	int32_t RotaryEncoder::onRotate( int8_t dr )
	{
		if ( dr > 0 )
		{
			Serial.print( 'R' );
		}
		else
		{
			Serial.print( 'L' );
		}
		Serial.print( ' ' );
		if ( detents )
			rotation %= detents;
		Serial.println( rotation );
		return rotation;
	}

	void RotaryEncoder::privateLoop( void )
	{
		
	}
}