#ifndef IO_H_
#define IO_H_

namespace components {
	typedef int PinNumber;

	class IO_Pin {
	public:
		IO_Pin(PinNumber pin) : _pin(pin) {}
		PinNumber pinNumber() { return _pin; }
	protected:
		const PinNumber _pin;
	};

	enum class State : bool {
		High = true,
		Low = false
	};

	enum class TriggerOn {
		High,
		Low
	};

	enum class InputPull {
		None,
		Up,
		Down,
	};

	unsigned long millisTime();
	void millisDelay(unsigned millis);
};
#endif /* IO_H_ */