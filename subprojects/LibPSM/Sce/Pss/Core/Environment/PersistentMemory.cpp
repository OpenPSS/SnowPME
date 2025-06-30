#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <LibShared.hpp>

#include <mono/mono.h>
#include <cstdlib>
#include <cstring>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Io;

namespace Sce::Pss::Core::Environment {
	uint8_t PersistentMemory::memoryBuffer[0x10000] = { 0 };

	int PersistentMemory::Read(uint8_t* persistantMemory, size_t persistantMemSize) {
		if (persistantMemory == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (persistantMemSize == sizeof(PersistentMemory::memoryBuffer)) {
			if (persistantMemSize > sizeof(PersistentMemory::memoryBuffer) || PersistentMemory::memoryBuffer == nullptr || persistantMemory == nullptr) return PSM_ERROR_COMMON_IO; // this check seems pointless? (trying to replicate memcpy_s)

			memcpy(persistantMemory, PersistentMemory::memoryBuffer, sizeof(PersistentMemory::memoryBuffer));
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT;
	}
	int PersistentMemory::Write(uint8_t* persistantMemory, size_t persistantMemSize) {
		if (persistantMemory == nullptr)
			return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (persistantMemSize == sizeof(PersistentMemory::memoryBuffer)) {
			if (persistantMemSize > sizeof(PersistentMemory::memoryBuffer) || PersistentMemory::memoryBuffer == nullptr || persistantMemory == nullptr) return PSM_ERROR_COMMON_IO; // this check seems pointless? (trying to replicate memcpy_s)
			
			memcpy(PersistentMemory::memoryBuffer, persistantMemory, sizeof(PersistentMemory::memoryBuffer));
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT;
	}

	int PersistentMemory::Flush() { // runs when the program exits.
		Logger::Debug("Writing " + std::string(PM_DAT_FILE) + " from disk.");
		uint64_t fileHandle = 0;
		uint32_t _ = 0;
		if (IoCall::PsmFileOpen(PM_DAT_FILE, SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_WRITE | SCE_PSS_FILE_OPEN_FLAG_ALWAYS_CREATE, &fileHandle, true) == PSM_ERROR_NO_ERROR) {
			IoCall::PsmFileWrite(fileHandle, PersistentMemory::memoryBuffer, sizeof(PersistentMemory::memoryBuffer), &_);
			IoCall::PsmClose(fileHandle);
		}
		else {
			memset(PersistentMemory::memoryBuffer, 0, sizeof(PersistentMemory::memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::Terminate() {
		return PersistentMemory::Flush();
	}

	int PersistentMemory::Initalize() { 
		Logger::Debug("Reading " + std::string(PM_DAT_FILE) + " from disk.");
		uint64_t fileHandle = 0;
		uint32_t _ = 0;
		if (IoCall::PsmFileOpen(PM_DAT_FILE, SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ , &fileHandle, true) == PSM_ERROR_NO_ERROR) {
			IoCall::PsmFileRead(fileHandle, PersistentMemory::memoryBuffer, sizeof(PersistentMemory::memoryBuffer), &_);
			IoCall::PsmClose(fileHandle);
		}
		else {
			memset(PersistentMemory::memoryBuffer, 0, sizeof(PersistentMemory::memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::WriteNative(MonoArray* fileImage) {
		LOG_FUNCTION();

		if (fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = (uint8_t*)mono_array_addr_with_size(fileImage, 0, 1);
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Write(pm, pmLen);
	}
	int PersistentMemory::ReadNative(MonoArray* fileImage) {
		LOG_FUNCTION();

		if(fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = (uint8_t*)mono_array_addr_with_size(fileImage, 0, 1);
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Read(pm, pmLen);
	}
}
