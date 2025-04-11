#ifndef LIB_PSS_SECURITY_H
#define LIB_PSS_SECURITY_H 1

#include <Sce/Pss/Core/Mono/PsmDlls.hpp>
#include <string>
#include <iostream>

namespace Sce::Pss::Core::Mono
{
	class Security {
	private:
		static PsmDlls::PssSystemFileEnum nameToEnum(std::string name);
		static std::string enumToName(PsmDlls::PssSystemFileEnum fileEnum);

	public:
		static int IsSecurityCriticalExempt(const char* exeFullPath);
		static bool VerifyDll(std::string dllFullPath, PsmDlls::PssSystemFileEnum whatDll);
	};
}

#endif