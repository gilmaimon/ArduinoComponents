#ifndef __TIMEDDISPATCH_H__
#define __TIMEDDISPATCH_H__

#include "../Helpers/VoidCallback.h"
#include "Component.h"

namespace components {
	class TimedDispatch : public Component {
	public:
		TimedDispatch(VoidCallback callback) : TimedDispatch(nullptr, callback) {}
		TimedDispatch(Ref<Component> parent, VoidCallback callback);
		void dispatch_delayed(unsigned long delay);
		bool isRunning();
		void cancel();

	private:
		void privateLoop();

		VoidCallback timeoutCallback;
		unsigned long deadline;
		bool timerRunning;
	};
};

#endif
