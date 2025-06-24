#include <Sce/Pss/Core/InitializeCsharp.hpp>
#include <Sce/Pss/Core/Mono/PsmMonoFunc.hpp>
#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>

#include <LibShared.hpp>

#include <mono/mono.h>

using namespace Sce::Pss::Core::Mono;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Environment;
using namespace Shared::Debug;

namespace Sce::Pss::Core {
	int InitalizeCsharp::installFunctions(PsmMonoFunc* functionsList) {
		for (int i = 0;; i++) {
			if ( functionsList[i].functionSignature == nullptr) return PSM_ERROR_NO_ERROR;
			if ( functionsList[i].functionPointer == nullptr ) return PSM_ERROR_COMMON_ARGUMENT;

			Logger::Debug(std::string(functionsList[i].functionSignature) + " -> " + std::to_string(reinterpret_cast<uintptr_t>(functionsList[i].functionPointer)));
			mono_add_internal_call(functionsList[i].functionSignature, reinterpret_cast<void*>(functionsList[i].functionPointer));
		}
	}

	int InitalizeCsharp::registerErrors() {
		return InitalizeCsharp::installFunctions(ErrorFunctions);
	}
	int InitalizeCsharp::registerServices() {
		return InitalizeCsharp::installFunctions(ServiceFunctions);
	}
	int InitalizeCsharp::registerCamera() {
		return InitalizeCsharp::installFunctions(CameraFunctions);
	}
	int InitalizeCsharp::registerLocation() {
		return InitalizeCsharp::installFunctions(LocationFunctions);
	}
	int InitalizeCsharp::registerImaging() {
		return InitalizeCsharp::installFunctions(ImagingFunctions);
	}
	int InitalizeCsharp::registerInput() {
		return InitalizeCsharp::installFunctions(InputFunctions);
	}
	int InitalizeCsharp::registerAudio() {
		return InitalizeCsharp::installFunctions(AudioFunctions);
	}
	int InitalizeCsharp::registerGraphics() {
		if (Thread::IsMainThread()) {
			return InitalizeCsharp::installFunctions(GraphicsFunctions);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads\n");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int InitalizeCsharp::registerEnvironment() {
		PersistentMemory::Initalize();
		return InitalizeCsharp::installFunctions(EnvironmentFunctions);
	}

	int InitalizeCsharp::unregisterEnvironment() {
		PersistentMemory::Terminate();

		return PSM_ERROR_NO_ERROR;
	}

	int InitalizeCsharp::Initalize() {
		InitalizeCsharp::registerErrors();
		// IntHandleTable::Initialize(); ?

		InitalizeCsharp::registerEnvironment();
		InitalizeCsharp::registerGraphics();
		InitalizeCsharp::registerAudio();
		InitalizeCsharp::registerInput();
		InitalizeCsharp::registerImaging();
		InitalizeCsharp::registerLocation();
		InitalizeCsharp::registerCamera();
		InitalizeCsharp::registerServices();

		return PSM_ERROR_NO_ERROR;
	}

	int InitalizeCsharp::Terminate() {
		InitalizeCsharp::unregisterEnvironment();

		return PSM_ERROR_NO_ERROR;
	}

}