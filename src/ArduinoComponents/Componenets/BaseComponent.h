#ifndef BASECOMPONENT_H_
#define BASECOMPONENT_H_

#include "../Helpers/Ref.h"
#include "../Helpers/Vector.h"

class BaseComponent {
public:
	BaseComponent(Ref<BaseComponent> parent = nullptr) : _parent(parent), _children(5), _isLooping(false) {}
	void loop() {
		_isLooping = true;
		loopChildren();
		if(_isLooping) {
			privateLoop();
		}
	}

protected:
	void SkipLoop() {
		_isLooping = false;
		if(*_parent != nullptr) _parent->SkipLoop();
	}
	void RegisterChild(Ref<BaseComponent> child) {
		_children.push(child);
	}

private:
	Ref<BaseComponent> _parent;
	Vector<Ref<BaseComponent>> _children;
	bool _isLooping;

	void loopChildren() {
		for(unsigned i = 0; i < _children.size(); i++) {
			_children.get(i)->loop();
			if(!_isLooping) {
				SkipLoop();
				return;
			}
		}
	}

	virtual void privateLoop() = 0;
};

#endif 