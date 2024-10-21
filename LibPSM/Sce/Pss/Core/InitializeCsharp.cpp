#include <Sce/Pss/Core/InitializeCsharp.hpp>
#include <Sce/Pss/Core/PsmMonoFunc.hpp>
#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>

#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/ExceptionInfo.hpp>

#include <LibShared.hpp>
#include <mono/mono.h>

using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Environment;
using namespace Shared::Debug;

namespace Sce::Pss::Core {
	int InitalizeCsharp::installFunctions(PsmMonoFunc* functionsList) {
		for (int i = 0;; i++) {
			if ( functionsList[i].functionSignature == nullptr) return PSM_ERROR_NO_ERROR;
			if ( functionsList[i].functionPointer == nullptr ) PSM_ERROR_COMMON_ARGUMENT;

			Logger::Debug(std::string(functionsList[i].functionSignature)+" -> "+std::to_string((uint64_t)functionsList[i].functionPointer));
			mono_add_internal_call(functionsList[i].functionSignature, reinterpret_cast<void*>(functionsList[i].functionPointer));
		}
	}

	int InitalizeCsharp::registerError() {
		return installFunctions(ErrorFunctions);
	}
	int InitalizeCsharp::registerServices() {
		return installFunctions(ServiceFunctions);
	}
	int InitalizeCsharp::registerCamera() {
		return installFunctions(CameraFunctions);
	}
	int InitalizeCsharp::registerLocation() {
		return installFunctions(LocationFunctions);
	}
	int InitalizeCsharp::registerImaging() {
		return installFunctions(ImagingFunctions);
	}
	int InitalizeCsharp::registerInput() {
		return installFunctions(InputFunctions);
	}
	int InitalizeCsharp::registerAudio() {
		return installFunctions(AudioFunctions);
	}
	int InitalizeCsharp::registerGraphics() {
		if (Thread::IsMainThread()) {
			return installFunctions(GraphicsFunctions);
		}
		else {
			ExceptionInfo::AddMessage("Sce.PlayStation.Core.Graphics cannot be accessed by multiple theads");
			return PSM_ERROR_COMMON_INVALID_OPERATION;
		}
	}
	int InitalizeCsharp::registerEnvironment() {
		PersistentMemory::ReadPersistantMemoryFromDisk();
		return installFunctions(EnvironmentFunctions);
	}

	int InitalizeCsharp::registerFunctions() {
		InitalizeCsharp::registerError();
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

	InitalizeCsharp::InitalizeCsharp() {
		InitalizeCsharp::registerFunctions();
	}

}