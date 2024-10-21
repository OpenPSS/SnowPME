#ifndef LIB_PSS_INITALIZECSHARP_H
#define LIB_PSS_INITALIZECSHARP_H 1
#include <string>
#include <mono/mono.h>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
namespace Sce::Pss::Core {

	typedef struct PsmMonoFunc {
		const char* functionSignature;
		void* functionPointer;
	} PsmMonoFunc;


	class InitalizeCsharp {
	private:
		static int installFunctions(PsmMonoFunc* functions);
		static int registerFunctions();
		static int registerError();
		static int registerServices();
		static int registerCamera();
		static int registerLocation();
		static int registerImaging();
		static int registerInput();
		static int registerAudio();
		static int registerGraphics();
		static int registerEnvironment();

	public:
		InitalizeCsharp();

	};
}

#endif