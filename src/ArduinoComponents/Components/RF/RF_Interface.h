#ifdef EXPERIMENTAL_RF

#ifndef RFINTERFACE_H_
#define RFINTERFACE_H_

#include <stdint.h>
#include <string.h>
#include "../../Helpers/Function.h"
#include "../../Helpers/Vector.h"

#include "../Component.h"

namespace components {
	struct Message {
		Message() : Message("") {}
		Message(const char* str) {
			len = strlen(str);
			memcpy(data, (uint8_t*) str, len);
		}
		static const uint16_t MAX_LENGTH = 128;
		uint8_t data[MAX_LENGTH];
		uint16_t len;
	};

	/*
	rf.onMessage([](const Message& msg){
		
		return true; // msg was handled and should not be dispatched any more
	});

	rf.onMessage(ContentFilter("ABCDEFGHIJKLMNOP"), [](const Message& msg){
		
		return false; // keep sending this msg to handlers
	});
	*/

	enum Status : bool {
		Status_Success = false,
		Status_Failure = true
	};

	typedef Function<bool(const Message&)> FilterFunction;
	typedef Function<bool(const Message&)> HandlerFunction;

	class RfInterface : public Component {
	public:
		RfInterface(Ref<Component> parent) : Component(parent) {}

		virtual bool send(Message& msg) = 0;
		
		void onMessage(FilterFunction filter, HandlerFunction handler) {
			_handlers.push(FilterHandlerPair{
				filter, 
				handler
			});
		}
		void onMessage(HandlerFunction handler) {
			_handlers.push(FilterHandlerPair{
				[](const Message&){
					return true;
				}, 
				handler
			});
		}

		virtual ~RfInterface() {}

	protected:
		void disptachMessageToHandlers(const Message& msg) {
			for(unsigned i = 0; i < _handlers.size(); i++) {
				if(_handlers.get(i).filter(msg)) {
					bool handled = _handlers.get(i).handler(msg);
					if(handled) return;
				}
			}
		}

	private:
		struct FilterHandlerPair {
			FilterHandlerPair(
				FilterFunction filterFunction = [](const Message&){ return false; }, 
				HandlerFunction handlerFunction = [](const Message&){ return false; }
			) : filter(filterFunction), handler(handlerFunction) {}
			FilterFunction filter;
			HandlerFunction handler;
		};
		Vector<FilterHandlerPair> _handlers;
	};
};
#endif //RFINTERFACE_H_
#endif //EXPERIMENTAL_RF