#ifndef __ASK_RF_H__
#define __ASK_RF_H__

#include <RH_ASK.h>
#include <SPI.h>
#include "RfInterface.h"
#include "../BaseComponent.h"

namespace components {
	class ASK_Rf : public RfInterface {
	public:
		ASK_Rf() = delete;
		ASK_Rf(uint8_t rxPin, uint8_t txPin) : ASK_Rf(nullptr, 2000, rxPin, txPin) {}
		ASK_Rf(uint8_t rxPin, uint8_t txPin, Ref<BaseComponent> parent) : ASK_Rf(parent, 2000, rxPin, txPin) {}
		ASK_Rf(Ref<BaseComponent> parent = nullptr, uint16_t speed = 2000, uint8_t rxPin = 11, uint8_t txPin = 12, uint8_t pttPin = 10, bool pttInverted = false);
		virtual bool send(Message& msg);
		virtual ~ASK_Rf();
	public:
		RH_ASK _driver;
		virtual void privateLoop();
	};
};

#endif 
