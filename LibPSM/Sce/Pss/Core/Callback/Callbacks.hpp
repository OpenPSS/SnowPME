#ifndef LIB_PSS_CALLBACKS_H
#define LIB_PSS_CALLBACKS_H 1

namespace Sce::Pss::Core::Callback {
	class Callbacks {
	protected:
		static bool isInitalized;
		static void errorOnNotInitalized();
	};

}
#endif