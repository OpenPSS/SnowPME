#ifndef LIB_PSS_INITALIZECSHARP_H
#define LIB_PSS_INITALIZECSHARP_H 1
#include <string>
#include <mono/mono.h>
namespace Sce::Pss::Core {

	typedef struct PsmMonoFunc {
		const char* functionSignature;
		void* functionPointer;
	} PsmMonoFunc;


	static class InitalizeCsharp {
	private:
		static int installFunctions(PsmMonoFunc* functions);
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