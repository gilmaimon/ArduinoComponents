#ifndef REF_H_
#define REF_H_

namespace components {
	// Non owning reference
	template <class T> 
	class Ref {
	public:
		Ref() : _ref(nullptr) {}
		Ref(T* ref) : _ref(ref) {}
		Ref(T& ref) : _ref(&ref) {}
		Ref(const Ref<T>& other) : _ref(other._ref) {}
		Ref<T>& operator=(const Ref<T>& other) { 
			_ref = other._ref;
			return *this;
		}

		template <class BaseClass>
		Ref(Ref<BaseClass>& other) : _ref((T*) *other) {}

		T* operator->() { return _ref; }
		const T& operator->() const { return *_ref; }

		T* operator*() { return _ref; }
		
		operator bool() const { return _ref != nullptr; }
	private:
		T *_ref;
	};
};

#endif