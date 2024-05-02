#include <Sce/Pss/Core/Mono/Security.hpp>
#include <Sce/Pss/Core/Mono/PsmDlls.hpp>
#include <Sce/Pss/Core/Crypto/CryptoLibrary.hpp>
#include <LibShared.hpp>
#include <fstream>
#include <filesystem>
#include <string.h>
using namespace Shared::String;
using namespace Shared::Debug;

using namespace Sce::Pss::Core::Mono::PsmDlls;
namespace Sce::Pss::Core::Mono
{

	PssSystemFileEnum Security::nameToEnum(std::string name) {
		for (int i = 0; i < (sizeof(PsmDllFilenameList) / sizeof(std::string)); i++) {
			if (StringUtil::ToLower(PsmDllFilenameList[i]) == StringUtil::ToLower(name)) {
				return (PssSystemFileEnum)i;
			}
		}
		return PssSystemFileEnum::NONE;
	}

	std::string Security::enumToName(PssSystemFileEnum fileEnum) {
		return PsmDllFilenameList[(int)fileEnum];
	}

	bool Security::VerifyDll(std::string dllFullPath, PssSystemFileEnum whatDll) {
		bool res = false;
		// check the DLL file exists :
		if ( std::filesystem::exists(std::filesystem::path(dllFullPath)) ) {
			// get the filesize of the DLL
			uint8_t* buffer = new uint8_t[MscorlibSize]; // Allocate memory for the DLL
			std::ifstream* dllStream = new std::ifstream(dllFullPath, std::ios::in | std::ios::binary); // Open the DLL File 

			if (dllStream->is_open() && !dllStream->fail()) { // Check if open  was successful
				// Read DLL Contents
				dllStream->read((char*)buffer, MscorlibSize);
				uint64_t readSz = dllStream->gcount();
				dllStream->close();

				// Hash the DLLs
				uint8_t gotHash[0x14];
				Crypto::CryptoLibrary::Sha1Sum(buffer, (uint32_t)readSz, gotHash);

				// Check hash matches whats expected.
				switch (whatDll) {
					case PssSystemFileEnum::MSCORLIB:
						for (int i = 0; i < (sizeof(MscorlibSha1) / sizeof(gotHash)); i++) { if (memcmp(gotHash, MscorlibSha1[i], sizeof(gotHash)) == 0) { res = true; break; } };
						break;																											 
					case PssSystemFileEnum::SYSTEM:																			 
						for (int i = 0; i < (sizeof(SystemSha1) / sizeof(gotHash)); i++) { if (memcmp(gotHash, SystemSha1[i], sizeof(gotHash)) == 0) { res = true; break; } };
						break;																											 
					case PssSystemFileEnum::SCE_PLAYSTATON_CORE:																 
						for (int i = 0; i < (sizeof(ScePlayStationCoreSha1) / sizeof(gotHash)); i++) { if (memcmp(gotHash, ScePlayStationCoreSha1[i], sizeof(gotHash)) == 0) { res = true; break; } };
						break;
				}
			}

			delete dllStream;
			delete[] buffer;
		}
		return res;		
	}

	int Security::IsSecurityCriticalExempt(const char* exeFullPath) {

		std::string exePath = std::string(exeFullPath);
		std::string filename = Path::GetFilename(exePath);

		PssSystemFileEnum systemFile = nameToEnum(filename);
		
		if (systemFile != PssSystemFileEnum::NONE && VerifyDll(exeFullPath, systemFile)) {
			Logger::Debug("Determined Security Level for : " + filename + " as [SecurityCritical]");
			return true;
		}

		Logger::Debug("Determined Security Level for : " + filename + " as [SecurityTransparent]");
		return false;
	}


}
