#include <Sce/Pss/Core/Mono/InitializeMono.hpp>
#include <Sce/Pss/Core/Mono/Resources.hpp>
#include <Sce/Pss/Core/Mono/MonoUtil.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Mono/Security.hpp>
#include <Sce/Pss/Core/Io/IoCall.hpp>
#include <Sce/Pss/Core/Io/Edata/EdataCallbacks.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>
#include <Sce/Pss/Core/Services/InAppPurchaseDialog.hpp>
#include <Sce/Pss/Core/InitializeCsharp.hpp>

#include <LibCXML.hpp>
#include <LibShared.hpp>
#include <LibMonoBridge.hpp>
#include <mono/mono.h>

#include <csetjmp>

using namespace LibCXML;

using namespace Shared::Debug;
using namespace Shared;

using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Memory;
using namespace Sce::Pss::Core::Environment;
using namespace Sce::Pss::Core::Services;

namespace Sce::Pss::Core::Mono {

	int InitializeMono::exitCode = 0;
	MonoDomain* InitializeMono::psmDomain = nullptr;

	int InitializeMono::ScePsmTerminate() {
		mono_exit(0);

		psmDomain = nullptr;
		InitalizeCsharp::Terminate();

		HeapAllocator::MakeLocalObject();
		AppInfo::MakeLocalObject();
		Sandbox::MakeLocalObject();
		InAppPurchaseDialog::MakeLocalObject();

		return PSM_ERROR_NO_ERROR;
	}

	int InitializeMono::ScePsmInitalize(const char* assemblyPath, int resourceHeapSize) {
		std::string appExePath = std::string(assemblyPath, strlen(assemblyPath));
		Logger::Info("C# Assembly Loading [ " + appExePath + " ]");

		// Lockdown mono if security is enabled
		if (!Config::SecurityCritical) {
			mono_security_enable_core_clr();
			mono_security_set_core_clr_platform_callback(Security::IsSecurityCriticalExempt);
		}


		// Tell mono there is no config file
		mono_config_parse(nullptr);

		// Set runtime install location
		mono_set_dirs(Config::RuntimeLibPath, Config::RuntimeConfigPath);

		// Create a domain in which this application will run under.
		// be sure to specify the "playstation mobile" version not regular mono.
		InitializeMono::psmDomain = mono_jit_init_version(appExePath.c_str() , "mobile");

		// run profiler and debug if needed
		if (strlen(Config::ProfilerSettings) > 0)
			mono_profiler_load(Config::ProfilerSettings);
		if (Config::MonoDebugger)
			mono_debug_init(MONO_DEBUG_FORMAT_MONO);

		// PSM Icalls
		pss_io_icall_install_functions(
			Sce::Pss::Core::Io::IoCall::PsmClose,
			Sce::Pss::Core::Io::IoCall::PsmDirectoryCreate,
			Sce::Pss::Core::Io::IoCall::PsmDirectoryRemove,
			Sce::Pss::Core::Io::IoCall::PsmDirectoryOpen,
			Sce::Pss::Core::Io::IoCall::PsmDirectoryRead,
			Sce::Pss::Core::Io::IoCall::PsmDirectoryGetWorking,
			Sce::Pss::Core::Io::IoCall::PsmDirectorySetWorking,
			Sce::Pss::Core::Io::IoCall::PsmFileOpen,
			Sce::Pss::Core::Io::IoCall::PsmFileDelete,
			Sce::Pss::Core::Io::IoCall::PsmFileGetInformation,
			Sce::Pss::Core::Io::IoCall::PsmFileRead,
			Sce::Pss::Core::Io::IoCall::PsmFileWrite,
			Sce::Pss::Core::Io::IoCall::PsmFileSeek,
			Sce::Pss::Core::Io::IoCall::PsmFileFlush,
			Sce::Pss::Core::Io::IoCall::PsmFileGetSize,
			Sce::Pss::Core::Io::IoCall::PsmFileTruncate,
			Sce::Pss::Core::Io::IoCall::PsmFileCopy,
			Sce::Pss::Core::Io::IoCall::PsmFileSetAttributes,
			Sce::Pss::Core::Io::IoCall::PsmFileSetTimes,
			Sce::Pss::Core::Io::IoCall::PsmFileGetPathInformation);


		// setup all C# side psm related functions ...
		HeapAllocator::MakeUniqueObject(std::make_shared<HeapAllocator>(resourceHeapSize, "ScePsmResourceHeap"));

		// Set this as the 'main thread'
		Thread::SetMainThread();

		// initalize C# functions
		InitalizeCsharp::Initalize();

		// Load essential dlls
		std::string msCorLibPath = Config::MscorlibPath();
		std::string systemLibPath = Config::SystemLibPath();
		std::string psmCoreLibPath = Config::PsmCoreLibPath();

		MonoAssembly* msCoreLib = MonoUtil::MonoAssemblyOpenFull(psmDomain, msCorLibPath.c_str());
		MonoAssembly* systemLib = MonoUtil::MonoAssemblyOpenFull(psmDomain, systemLibPath.c_str());
		MonoAssembly* psmCoreLib = MonoUtil::MonoAssemblyOpenFull(psmDomain, psmCoreLibPath.c_str());

		MonoImage* msCoreLibImage = mono_assembly_get_image(msCoreLib);
		MonoImage* systemImage = mono_assembly_get_image(systemLib);

		// Calls SetToConsole. 
		MonoImage* psmCoreLibImage = mono_assembly_get_image(psmCoreLib);
		MonoClass* psmLogClass = mono_class_from_name(psmCoreLibImage, "Sce.PlayStation.Core.Environment", "Log");
		MonoMethod* psmSetToConsoleMethod = mono_class_get_method_from_name(psmLogClass, "SetToConsole", 0);
		mono_runtime_invoke(psmSetToConsoleMethod, nullptr, nullptr, nullptr);

		return PSM_ERROR_NO_ERROR;
	}


	int InitializeMono::scePsmMonoJitExec2(MonoAssembly* assembly, char** argv, int argc) {
		MonoObject* exception = nullptr;

		// Get executable image
		MonoImage* runImage = mono_assembly_get_image(assembly);

		// Get address of entry point
		uint32_t entryPointAddr = mono_image_get_entry_point(runImage);

		// Get entry point method
		MonoMethod* entryPointMethod = mono_get_method(runImage, entryPointAddr, nullptr);

		// Run entry point function
		mono_runtime_run_main(entryPointMethod, argc, argv, &exception);

		if (exception != nullptr)
			mono_unhandled_exception(exception);

		return PSM_ERROR_NO_ERROR;
	}

	int InitializeMono::scePsmExecute(const char* appExe, int* resCode) {
		// Load the executable
		MonoAssembly* appExeBin = MonoUtil::MonoAssemblyOpenFull(InitializeMono::psmDomain, appExe);

		// Create argv
		char* argv[2] = { (char*)appExe, nullptr };

		if (appExeBin != nullptr) {

			// start assembly
			InitializeMono::scePsmMonoJitExec2(appExeBin, argv, 1);

			mono_runtime_set_shutting_down();
			mono_threads_set_shutting_down();

			mono_thread_suspend_all_other_threads();

			if (appExe != nullptr) {
				*resCode = mono_environment_exitcode_get();
			}
			return PSM_ERROR_NO_ERROR;
		}
		else {
			Logger::Error("Cannot open assembly: " + std::string(appExe));
			return PSM_ERROR_COMMON_FILE_NOT_FOUND;
		}
	}

	int InitializeMono::ScePssMain(const char* gameFolder) {
		int resCode = 0;
		// create Sandbox object
		std::shared_ptr<Sandbox> sandbox = Sandbox::MakeUniqueObject(std::make_shared<Sandbox>(gameFolder));

		std::string appInfoPath = "/Application/app.info";
		std::string realAppExePath = sandbox->LocateRealPath("/Application/app.exe", false);
		
		// create appinfo object
		std::shared_ptr<AppInfo> appInfo = (!sandbox->PathExist(appInfoPath, false) ? nullptr : AppInfo::MakeUniqueObject(std::make_shared<AppInfo>(sandbox->LocateRealPath(appInfoPath, false))));

		// setup Edata ... for ScePsmDrm / PSSE decrypt..
		PssCryptoCallbacks callbacks;
		callbacks.eOpen  = Sce::Pss::Core::Io::Edata::EdataCallbacks::EdataOpen;
		callbacks.eRead  = Sce::Pss::Core::Io::Edata::EdataCallbacks::EdataRead;
		callbacks.eSeek  = Sce::Pss::Core::Io::Edata::EdataCallbacks::EdataSeek;
		callbacks.eClose = Sce::Pss::Core::Io::Edata::EdataCallbacks::EdataClose;
		ScePsmEdataMonoInit(&callbacks);

		// setup limits 

		int heapSizeLimit = appInfo->ManagedHeapSize * 0x400;
		int resourceSizeLimit = appInfo->ResourceHeapSize * 0x400;
		

		if (heapSizeLimit + resourceSizeLimit > 0x6000000) {
			Logger::Error("resource_heap_size + managed_heap_size > 96MB.");
			return PSM_ERROR_OUT_OF_MEMORY;
		}
		Logger::Debug("cxml : managed_heap_size : "+ std::to_string(heapSizeLimit));
		Logger::Debug("cxml : resource_heap_size : "+ std::to_string(resourceSizeLimit));


		int res = InitializeMono::ScePsmInitalize(realAppExePath.c_str(), appInfo->ResourceHeapSize);
		if (res != PSM_ERROR_NO_ERROR) {
			Logger::Error("Failed to call ScePsmInitalize // " + std::to_string(res));
			return res;
		}

		// This is automatically called when a resource limit is reached
		mono_runtime_resource_set_callback(Resources::ResourceLimitReachedCallback);

		// Set up resource limits for PSM Games... 
		mono_runtime_resource_limit(MONO_RESOURCE_JIT_CODE, 0x1000000, 0x1000000);
		mono_runtime_resource_limit(MONO_RESOURCE_METADATA, 0x1000000, 0x1000000);

		mono_gc_set_heap_size_limit(heapSizeLimit, heapSizeLimit);
		mono_thread_set_max_threads(16);
		mono_threadpool_set_max_threads(8, 8);
		mono_thread_set_threads_exhausted_callback(Resources::ThreadsExhaustedCallback);

		InitializeMono::scePsmExecute(realAppExePath.c_str(), &resCode);
		InitializeMono::ScePsmTerminate();

		Logger::Info("app.exe exited with status code: " + std::to_string(resCode));

		return resCode;
	}


}
