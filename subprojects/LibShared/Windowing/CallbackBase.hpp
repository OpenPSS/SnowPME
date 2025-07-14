#ifndef SHARED_CALLBACKBASE_H
#define SHARED_CALLBACKBASE_H 1

namespace Shared::Windowing {
	class CallbackBase {
	protected:
		static bool isInitalized;
		static void errorOnNotInitalized();
	public:
		static bool IsInitalized();
	};

}
#endif