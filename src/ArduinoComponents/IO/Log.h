#ifndef LOG_H_
#define LOG_H_

#include "Arduino.h"

namespace components {
	template <typename T> void Log(T t) {
		Serial.println(t);
	}

	template<typename T, typename... Args> void Log(T t, Args... args) {
		Serial.print(t);

		Log(args...);
	}


	template <typename T> void LogS(T t) {
		Serial.println(t);
	}

	template<typename T, typename... Args> void LogS(T t, Args... args) {
		Serial.print(t);
		Serial.print(" ");

		LogS(args...);
	}
};

#endif