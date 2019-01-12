#ifdef EXPERIMENTAL_RF

#include <RH_ASK.h>
#include <SPI.h>
#include "ASK_RF.h"

namespace components {
	ASK_RF::ASK_RF(Ref<Component> parent, uint16_t speed, uint8_t rxPin, uint8_t txPin, uint8_t pttPin, bool pttInverted) : 
		RfInterface(parent),
		_driver(speed, rxPin, txPin, pttPin, pttInverted) {
		if (!_driver.init())
			Serial.println("init failed");
	}

	bool ASK_RF::send(Message& msg) {
		_driver.send(msg.data, msg.len);
		_driver.waitPacketSent();
		return true;
	}

	void ASK_RF::privateLoop() {
		uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
		uint8_t buflen = sizeof(buf);
		if (_driver.recv(buf, &buflen)) {
			//Serial.println("Got MSG!");
			Message msg;
			msg.len = buflen;
			memcpy(msg.data, buf, buflen);
			msg.data[buflen] = NULL;
			disptachMessageToHandlers(msg);
		}
	}

	ASK_RF::~ASK_RF() {}
};

#endif //EXPERIMENTAL_RF