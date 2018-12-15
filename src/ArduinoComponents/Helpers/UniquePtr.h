#ifndef UNIQUEPTR_H_
#define UNIQUEPTR_H_

template<typename T> class UniquePtr {
public:
	UniquePtr(T* t = nullptr) {
		_ptr = t;
	}
	UniquePtr<T>* operator=(T* t) {
		if(_ptr) delete _ptr;
		_ptr = t;
		return this;
	}

	UniquePtr<T>* operator=(UniquePtr<T>& other) {
		if(_ptr) delete _ptr;
		_ptr = other._ptr;
		other._ptr = nullptr;
		return this;
	}

	T* operator->() {
		return _ptr;
	}

	~UniquePtr() {
		delete _ptr;
	}
private:
	T* _ptr;
};

#endif