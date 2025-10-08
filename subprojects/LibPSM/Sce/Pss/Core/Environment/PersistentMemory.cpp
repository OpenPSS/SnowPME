#include <Sce/Pss/Core/Environment/PersistentMemory.hpp>
#include <Sce/Pss/Core/Error.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataStream.hpp>
#include <LibShared.hpp>

#include <mono/mono.h>
#include <cstdlib>
#include <cstring>

using namespace Shared::Debug;
using namespace Shared::String;
using namespace Sce::Pss::Core::Io::Edata;
using namespace Sce::Pss::Core::Io;

namespace Sce::Pss::Core::Environment {
	uint8_t PersistentMemory::memoryBuffer[0x10000] = { 0 };

	int PersistentMemory::Read(uint8_t* persistantMemory, size_t persistantMemSize) {
		if (persistantMemory == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (persistantMemSize == sizeof(memoryBuffer)) {
			if (persistantMemSize > sizeof(memoryBuffer) || memoryBuffer == nullptr || persistantMemory == nullptr) return PSM_ERROR_COMMON_IO; // this check seems pointless? (trying to replicate memcpy_s)

			memcpy(persistantMemory, memoryBuffer, sizeof(memoryBuffer));
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT;
	}
	int PersistentMemory::Write(uint8_t* persistantMemory, size_t persistantMemSize) {
		if (persistantMemory == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;
		if (persistantMemSize == sizeof(memoryBuffer)) {
			if (persistantMemSize > sizeof(memoryBuffer) || memoryBuffer == nullptr || persistantMemory == nullptr) return PSM_ERROR_COMMON_IO; // this check seems pointless? (trying to replicate memcpy_s)
			
			memcpy(memoryBuffer, persistantMemory, sizeof(memoryBuffer));
			return PSM_ERROR_NO_ERROR;
		}
		return PSM_ERROR_COMMON_ARGUMENT;
	}

	int PersistentMemory::Flush() { // runs when the program exits.
		Logger::Debug("Writing " + std::string(PersistentMemory::PM_DAT_FILE) + " from disk.");
		EdataStream edata = EdataStream(Sandbox::UniqueObject()->LocateRealPath(PersistentMemory::PM_DAT_FILE, true), std::ios::binary | std::ios::out, nullptr, false);
		if (edata.GetError() == PSM_ERROR_NO_ERROR) {
			edata.Write(memoryBuffer, sizeof(memoryBuffer));
			edata.Close();
		}
		else {
			memset(memoryBuffer, 0, sizeof(memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::Terminate() {
		return PersistentMemory::Flush();
	}

	int PersistentMemory::Initalize() { 
		Logger::Debug("Reading " + std::string(PersistentMemory::PM_DAT_FILE) + " from disk.");

		EdataStream edata = EdataStream(Sandbox::UniqueObject()->LocateRealPath(PersistentMemory::PM_DAT_FILE, true), std::ios::binary | std::ios::in, nullptr, false);
		if (edata.GetError() == PSM_ERROR_NO_ERROR) {
			edata.Read(memoryBuffer, sizeof(PersistentMemory));
			edata.Close();
		}
		else {
			memset(memoryBuffer, 0, sizeof(memoryBuffer));
		}
		return PSM_ERROR_NO_ERROR;
	}

	int PersistentMemory::WriteNative(MonoArray* fileImage) {
		LOG_FUNCTION();

		if (fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = reinterpret_cast<uint8_t*>(mono_array_addr_with_size(fileImage, 0, 1));
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Write(pm, pmLen);
	}
	int PersistentMemory::ReadNative(MonoArray* fileImage) {
		LOG_FUNCTION();

		if(fileImage == nullptr) return PSM_ERROR_COMMON_ARGUMENT_NULL;

		uint8_t* pm = reinterpret_cast<uint8_t*>(mono_array_addr_with_size(fileImage, 0, 1));
		size_t pmLen = mono_array_length(fileImage);

		return PersistentMemory::Read(pm, pmLen);
	}
}
