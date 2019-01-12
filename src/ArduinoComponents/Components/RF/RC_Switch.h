#ifdef EXPERIMENTAL_RF

#ifndef __RC_SWITCH_H__
#define __RC_SWITCH_H__

#include <RCSwitch.h>
#include "../Component.h"
#include "../../Helpers/Function.h"

namespace components {
	class RC_Switch : public Component {
	public:
		enum class MODE {
			MODE_Reciever, Mode_transmitter
		};
		RC_Switch(int pin, MODE mode) : Component(nullptr), codeCallback([](int code){}) {
			if(mode == MODE::MODE_Reciever) {
				mySwitch.enableReceive(pin);
			} else {
				mySwitch.enableTransmit(pin);
			}
		}

		void onCode(Function<void(int)> callback) {
			codeCallback = callback;
		}

		void send(int code) {
			mySwitch.send(code, 24);
		}

		~RC_Switch() {}

	private:
		RCSwitch mySwitch;
		Function<void(int)> codeCallback;
		
		void privateLoop() {
			if (mySwitch.available()) {
				int value = mySwitch.getReceivedValue();
				if (value == 0)	return;
				codeCallback(value);
				mySwitch.resetAvailable();
			}
		}
	};
};

#endif //__RC_SWITCH_H__
#endif //EXPERIMENTAL_RF