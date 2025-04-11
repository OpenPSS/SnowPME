#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <LibShared.hpp>
#include <mono/mono.h>


using namespace Shared::Debug;
using namespace Shared::String;

using namespace Sce::Pss::Core::Io;

namespace Sce::Pss::Core::Environment {
	uint8_t PersistentMemory::memoryBuffer[0x10000] = { 0 };
	std::string PersistentMemory::pmDatFile = "/System/pm.dat";

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

	int PersistentMemory::Initalize() { // runs when the program exits.
		Logger::Debug("Writing " + pmDatFile + " from disk.");
		uint64_t fileHandle = 0;
		uint32_t bytesWritten = 0;
		if (ICall::PsmFileOpenSystem((char*)pmDatFile.c_str(), SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_WRITE, &fileHandle, true) == PSM_ERROR_NO_ERROR) {
			ICall::PsmFileWrite(fileHandle, PersistentMemory::memoryBuffer, sizeof(PersistentMemory::memoryBuffer), &bytesWritten);
			ICall::PsmClose(fileHandle);
		}
		else {
			memset(PersistentMemory::memoryBuffer, 0, sizeof(PersistentMemory::memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::Terminate() {
		return PersistentMemory::Flush();
	}

	int PersistentMemory::Flush() { 
		Logger::Debug("Reading " + pmDatFile + " from disk.");
		uint64_t fileHandle = 0;
		uint32_t bytesRead = 0;
		if (ICall::PsmFileOpenSystem((char*)pmDatFile.c_str(), SCE_PSS_FILE_OPEN_FLAG_BINARY | SCE_PSS_FILE_OPEN_FLAG_READ , &fileHandle, true) == PSM_ERROR_NO_ERROR) {
			ICall::PsmFileRead(fileHandle, PersistentMemory::memoryBuffer, sizeof(PersistentMemory::memoryBuffer), &bytesRead);
			ICall::PsmClose(fileHandle);
		}
		else {
			memset(PersistentMemory::memoryBuffer, 0, sizeof(PersistentMemory::memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::WriteNative(MonoArray* fileImage) {
		Logger::Debug(__FUNCTION__);

		if (fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = (uint8_t*)mono_array_addr_with_size(fileImage, 0, 1);
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Write(pm, pmLen);
	}
	int PersistentMemory::ReadNative(MonoArray* fileImage) {
		Logger::Debug(__FUNCTION__);

		if(fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = (uint8_t*)mono_array_addr_with_size(fileImage, 0, 1);
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Read(pm, pmLen);
	}
}
