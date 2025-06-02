#ifndef LIB_PSS_INITALIZECSHARP_H
#define LIB_PSS_INITALIZECSHARP_H 1
#include <string>
#include <mono/mono.h>
#include <Sce/Pss/Core/Mono/PsmMonoFunc.hpp>

namespace Sce::Pss::Core {
	class InitalizeCsharp {
	private:
		static int installFunctions(Sce::Pss::Core::Mono::PsmMonoFunc* functions);
		static int registerErrors();
		static int registerServices();
		static int registerCamera();
		static int registerLocation();
		static int registerImaging();
		static int registerInput();
		static int registerAudio();
		static int registerGraphics();
		static int registerEnvironment();

		static int unregisterEnvironment();
	public:
		static int Initalize();
		static int Terminate();
	};
}

#endif