#ifdef EXPERIMENTAL_RF

#ifndef __ASK_RF_H__
#define __ASK_RF_H__

#include <RH_ASK.h>
#include <SPI.h>
#include "RfInterface.h"

namespace components {
	class ASK_RF : public RfInterface {
	public:
		ASK_RF() = delete;
		ASK_RF(uint8_t rxPin, uint8_t txPin) : ASK_RF(nullptr, 2000, rxPin, txPin) {}
		ASK_RF(uint8_t rxPin, uint8_t txPin, Ref<Component> parent) : ASK_RF(parent, 2000, rxPin, txPin) {}
		ASK_RF(Ref<Component> parent = nullptr, uint16_t speed = 2000, uint8_t rxPin = 11, uint8_t txPin = 12, uint8_t pttPin = 10, bool pttInverted = false);
		virtual bool send(Message& msg);
		virtual ~ASK_RF();
	public:
		RH_ASK _driver;
		virtual void privateLoop();
	};
};

#endif //__ASK_RF_H__
#endif //EXPERIMENTAL_RF