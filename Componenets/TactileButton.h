#ifndef __TACTILEBUTTON_H__
#define __TACTILEBUTTON_H__

#include "../IO/IO.h"
#include "../IO/DigitalInput.h"
#include "../Helpers/VoidCallback.h"
#include "BaseComponent.h"

class TactileButton : public BaseComponent {
public:
	TactileButton(DigitalInput input) : TactileButton(nullptr, input) {}
	TactileButton(Ref<BaseComponent> parent, DigitalInput input);
	TactileButton(PinNumber pin, InputPull pull) : TactileButton(nullptr, pin, pull) {}
	TactileButton(Ref<BaseComponent> parent, PinNumber pin, InputPull pull);

	void onPress(VoidCallback cbk);
	void onRelease(VoidCallback cbk);
	
private:
	DigitalInput _input;
	bool _pressed;
	VoidCallback _on_press;
	VoidCallback _on_release;

	void privateLoop();
};
#endif
