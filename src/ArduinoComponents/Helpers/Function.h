/*
* All Credit goes to - https://shaharmike.com/cpp/naive-std-function/
*/

#ifndef FUNCTION_H_
#define FUNCTION_H_

namespace components {
	template <typename T>
	class Function;

	template <typename ReturnValue, typename... Args>
	class Function<ReturnValue(Args...)> {
	public:
		template <typename T>
		Function(T t) {
			callable_ = new CallableT<T>(t);
		}
		
		template <typename T>
		Function& operator=(T t) {
			if (callable_ == nullptr) delete callable_;
			callable_ = new CallableT<T>(t);
			return *this;
		}

		ReturnValue operator()(Args... args) const {
			return callable_->Invoke(args...);
		}

		~Function() {
			if (callable_ == nullptr) delete callable_;
		}

	private:
		class ICallable {
			public:
			virtual ~ICallable() = default;
			virtual ReturnValue Invoke(Args...) = 0;
		};

		template <typename T>
		class CallableT : public ICallable {
			public:
			CallableT(const T& t)
			: t_(t) {
			}

			~CallableT() override = default;

			ReturnValue Invoke(Args... args) override {
				return t_(args...);
			}

			private:
			T t_;
		};

		ICallable* callable_;
	};
};

#endif