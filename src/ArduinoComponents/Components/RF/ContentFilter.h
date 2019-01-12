#ifdef EXPERIMENTAL_RF

#ifndef CONTENTFILTER_H_
#define CONTENTFILTER_H_

#include "RfInterface.h"

namespace components {
	namespace ContentFilter {
		static FilterFunction StartsWith(uint8_t* str) {
			return [str](const Message& msg){
				if(strlen(str) > msg.len) return false;
				for(int i = 0; i < strlen(str); i++) {
					if(str[i] != msg.data[i]) return false;
				}
				return true;
			};
		}
	}
};
#endif //CONTENTFILTER_H_
#endif //EXPERIMENTAL_RF