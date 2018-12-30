#ifndef __TACTILEBUTTON_H__
#define __TACTILEBUTTON_H__

#include "../IO/IO.h"
#include "../IO/DigitalInput.h"
#include "../Helpers/VoidCallback.h"
#include "Component.h"

namespace components {
	class TactileButton : public Component {
	public:
		TactileButton(DigitalInput input, TriggerOn trigger) : TactileButton(nullptr, input, trigger) {}
		TactileButton(Ref<Component> parent, DigitalInput input, TriggerOn trigger);
		TactileButton(PinNumber pin, TriggerOn trigger, InputPull pull = InputPull::None) : TactileButton(nullptr, pin, trigger, pull) {}
		TactileButton(Ref<Component> parent, PinNumber pin, TriggerOn trigger, InputPull pull = InputPull::None);

		void onPress(VoidCallback cbk);
		void onRelease(VoidCallback cbk);
		
	private:
		DigitalInput _input;
		bool _pressed;
		VoidCallback _on_press;
		VoidCallback _on_release;
		TriggerOn trigger;

		void privateLoop();
	};
};
#endif
