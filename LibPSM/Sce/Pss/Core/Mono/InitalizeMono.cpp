#include <Sce/Pss/Core/Mono/InitalizeMono.hpp>
#include <Sce/Pss/Core/Mono/Resources.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Mono/Security.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Edata/Callbacks.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/InitializeCsharp.hpp>

#include <LibCXML.hpp>
#include <LibShared.hpp>
#include <LibMonoBridge.hpp>

using namespace LibCXML;

using namespace Shared::Debug;
using namespace Shared;

using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Memory;

namespace Sce::Pss::Core::Mono {
	std::string InitalizeMono::appExe = "";
	MonoDomain* InitalizeMono::psmDomain = nullptr;
	MonoAssembly* InitalizeMono::psmCoreLib = nullptr;
	MonoAssembly* InitalizeMono::msCoreLib = nullptr;
	MonoAssembly* InitalizeMono::systemLib = nullptr;

	int InitalizeMono::initMono(std::string gameFolder) {
		Sandbox* sandbox = new Sandbox(gameFolder);

		std::string appInfoPath = "/Application/app.info";
		CXMLElement* elem = (!sandbox->PathExist(appInfoPath, false) ? nullptr : new CXMLElement(sandbox->LocateRealPath(appInfoPath, false), "PSMA"));
		AppInfo* appInfo = new AppInfo(elem);

		// setup Edata ...
		PssCryptoCallbacks callbacks; 
		callbacks.eOpen = Pss::Core::Edata::Callbacks::EdataOpen;
		callbacks.eRead = Pss::Core::Edata::Callbacks::EdataRead;
		callbacks.eSeek = Pss::Core::Edata::Callbacks::EdataSeek;
		callbacks.eClose = Pss::Core::Edata::Callbacks::EdataClose;
		ScePsmEdataMonoInit(&callbacks);

		// Initalize mono assembly
		return InitalizeMono::initMonoAssembly(sandbox->LocateRealPath("/Application/app.exe", false));
	}

	int InitalizeMono::initMonoAssembly(std::string exeFile) {


		InitalizeMono::appExe = exeFile;

		int heapSizeLimit = AppInfo::CurrentApplication->ManagedHeapSize * 0x400;
		int resourceSizeLimit = AppInfo::CurrentApplication->ResourceHeapSize * 0x400;


		if (heapSizeLimit + resourceSizeLimit > 0x6000000) {
			Logger::Error("resource_heap_size + managed_heap_size > 96MB.");
			return PSM_ERROR_OUT_OF_MEMORY;
		}
		Logger::Debug("cxml : managed_heap_size : " + std::to_string(heapSizeLimit));
		Logger::Debug("cxml : resource_heap_size : " + std::to_string(resourceSizeLimit));

		Logger::Debug("Starting: " + exeFile);


		// Lockdown mono if security is enabled
		if (!Config::SecurityCritical) {
			mono_security_enable_core_clr();
			mono_security_set_core_clr_platform_callback(Security::IsSecurityCriticalExempt);
		}


		// Tell mono there is no config file
		mono_config_parse(NULL);

		// Set runtime install location
		mono_set_dirs(Config::RuntimeLibPath.c_str(), Config::RuntimeConfigPath.c_str());

		// Create a domain in which this application will run under.
		InitalizeMono::psmDomain = mono_jit_init_version(appExe.c_str(), "mobile");

		// PSM Icalls
		pss_io_icall_install_functions(
			Sce::Pss::Core::Io::ICall::PsmClose,
			Sce::Pss::Core::Io::ICall::PsmDirectoryCreate,
			Sce::Pss::Core::Io::ICall::PsmDirectoryRemove,
			Sce::Pss::Core::Io::ICall::PsmDirectoryOpen,
			Sce::Pss::Core::Io::ICall::PsmDirectoryRead,
			Sce::Pss::Core::Io::ICall::PsmDirectoryGetWorking,
			Sce::Pss::Core::Io::ICall::PsmDirectorySetWorking,
			Sce::Pss::Core::Io::ICall::PsmFileOpen,
			Sce::Pss::Core::Io::ICall::PsmFileDelete,
			Sce::Pss::Core::Io::ICall::PsmFileGetInformation,
			Sce::Pss::Core::Io::ICall::PsmFileRead,
			Sce::Pss::Core::Io::ICall::PsmFileWrite,
			Sce::Pss::Core::Io::ICall::PsmFileSeek,
			Sce::Pss::Core::Io::ICall::PsmFileFlush,
			Sce::Pss::Core::Io::ICall::PsmFileGetSize,
			Sce::Pss::Core::Io::ICall::PsmFileTruncate,
			Sce::Pss::Core::Io::ICall::PsmFileCopy,
			Sce::Pss::Core::Io::ICall::PsmFileSetAttributes,
			Sce::Pss::Core::Io::ICall::PsmFileSetTimes,
			Sce::Pss::Core::Io::ICall::PsmFileGetPathInformation);


		// setup all C# side psm related functions ...
		HeapAllocator::CreateResourceHeapAllocator(resourceSizeLimit);
		Thread::SetMainThread();
		InitalizeCsharp();

		// Load essential dlls
		std::string msCorLibPath = Config::MscorlibPath();
		std::string systemLibPath = Config::SystemLibPath();
		std::string psmCoreLibPath = Config::PsmCoreLibPath();

		msCoreLib = mono_domain_assembly_open(psmDomain, msCorLibPath.c_str());
		systemLib = mono_domain_assembly_open(psmDomain, systemLibPath.c_str());
		psmCoreLib = mono_domain_assembly_open(psmDomain, psmCoreLibPath.c_str());

		MonoImage* msCoreLibImage = mono_assembly_get_image(msCoreLib);
		MonoImage* systemImage = mono_assembly_get_image(systemLib);

		// Calls SetToConsole. 
		MonoImage* psmCoreLibImage = mono_assembly_get_image(psmCoreLib);
		MonoClass* psmLogClass = mono_class_from_name(psmCoreLibImage, "Sce.PlayStation.Core.Environment", "Log");
		MonoMethod* psmSetToConsoleMethod = mono_class_get_method_from_name(psmLogClass, "SetToConsole", 0);
		mono_runtime_invoke(psmSetToConsoleMethod, NULL, NULL, NULL);

		// This is automatically called when a resource limit is reached
		mono_runtime_resource_set_callback(Resources::ResourceLimitReachedCallback);

		// Set up resource limits for PSM Games... 
		mono_runtime_resource_limit(MONO_RESOURCE_JIT_CODE, 0x1000000, 0x1000000);
		mono_runtime_resource_limit(MONO_RESOURCE_METADATA, 0x1000000, 0x1000000);

		mono_gc_set_heap_size_limit(heapSizeLimit, heapSizeLimit);
		mono_thread_set_max_threads(16);
		mono_threadpool_set_max_threads(8, 8);
		mono_thread_set_threads_exhausted_callback(Sce::Pss::Core::Mono::Resources::ThreadsExhaustedCallback);

		return PSM_ERROR_NO_ERROR;
	}

	void InitalizeMono::launchExe() {
		// Load the executable
		MonoAssembly* runAssembly = mono_domain_assembly_open(psmDomain, appExe.c_str());

		// Create argv
		char* args[2] = { (char*)appExe.c_str(), NULL };

		MonoObject* exception = NULL;

		// Get executable image
		MonoImage* runImage = mono_assembly_get_image(runAssembly);

		// Get address of entry point
		uint32_t entryPointAddr = mono_image_get_entry_point(runImage);

		// Get entry point method
		MonoMethod* entryPointMethod = mono_get_method(runImage, entryPointAddr, NULL);

		// Run entry point function
		mono_runtime_run_main(entryPointMethod, 1, args, &exception);

		if (exception != NULL)
			mono_unhandled_exception(exception);

	}

	void InitalizeMono::ScePsmMonoInit(const char* gameFolder) {

		if (InitalizeMono::initMono(std::string(gameFolder)) == PSM_ERROR_NO_ERROR) {
			InitalizeMono::launchExe();
		}

	}
}
