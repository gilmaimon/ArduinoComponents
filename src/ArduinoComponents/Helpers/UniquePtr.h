#ifndef UNIQUEPTR_H_
#define UNIQUEPTR_H_

namespace components {	
	template<typename T> class UniquePtr {
	public:
		UniquePtr(T* t) : _ptr(t) {}

		UniquePtr() : UniquePtr(nullptr) {}

		template <class OtherType>
		UniquePtr(UniquePtr<OtherType>& other) : _ptr(other._unsafe_get()) {
			other._unsafe_set(nullptr);
		}

		template <class OtherType>
		UniquePtr(UniquePtr<OtherType>&& other) : _ptr(other._unsafe_get()) {
			other._unsafe_set(nullptr);
		}

		UniquePtr<T>* operator=(T* t) {
			if(_ptr) delete _ptr;
			_ptr = t;
			return this;
		}

		template <class OtherType>
		UniquePtr<T>* operator=(UniquePtr<OtherType>& other) {
			if(_ptr) delete _ptr;
			_ptr = other._unsafe_get();
			other._unsafe_set(nullptr);
			return this;
		}


		T* operator->() {
			return _ptr;
		}

		operator bool() {
			return _ptr != nullptr;
		}

		void _unsafe_set(T* ptr) {
			_ptr = ptr;
		}

		T* _unsafe_get() {
			return _ptr;
		}

		~UniquePtr() {
			delete _ptr;
		}
	private:
		T* _ptr;
	};
	
	template <class T, typename... Args>
	UniquePtr<T> MakeUnique(Args... args) {
		return UniquePtr<T>(new T(args...));
	}
};

#endif