#ifndef LIB_PSS_CALLBACKBASE_H
#define LIB_PSS_CALLBACKBASE_H 1

namespace Sce::Pss::Core::Callback {
	class CallbackBase {
	protected:
		static bool isInitalized;
		static void errorOnNotInitalized();
	};

}
#endif