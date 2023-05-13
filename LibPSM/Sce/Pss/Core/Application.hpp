#ifndef LIB_PSM_APPGLOBAL_H
#define LIB_PSM_APPGLOBAL_H 1

#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>

namespace Sce::Pss::Core {
	class Application {
	public:

		static Sce::Pss::Core::Metadata::AppInfo * PsmAppInfo();
		static void SetPsmAppInfo(Sce::Pss::Core::Metadata::AppInfo* Sandbox);

		static Sce::Pss::Core::Io::Sandbox* PsmSandbox();
		static void SetPsmSandbox(Sce::Pss::Core::Io::Sandbox* Sandbox);
	};
}
#endif