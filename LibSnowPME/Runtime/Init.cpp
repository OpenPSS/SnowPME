#include <Runtime/Init.hpp>
#include <Debug/Logger.hpp>

#include <LibShared.hpp>
#include <LibPSM.hpp>
#include <LibCXML.hpp>

#include <mono/mono.h>

#include <filesystem>
#include <string>
#include <Callback/WindowImpl.hpp>
#include <Callback/AudioImpl.hpp>

using namespace Shared::Debug;
using namespace Shared;

using namespace LibCXML;
using namespace Sce::Pss::Core;
using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Memory;

namespace SnowPME::Runtime {

	std::string       Init::appExe = "";
	MonoDomain*       Init::psmDomain = nullptr;
	MonoAssembly*     Init::psmCoreLib = nullptr;
	MonoAssembly*     Init::msCoreLib = nullptr;
	MonoAssembly*     Init::systemLib = nullptr;

	int Init::initCallbacks(Graphics::Window* oglWindow) {
		Callback::WindowImpl::Init(oglWindow);

		Sce::Pss::Core::Callback::WindowCallbacks::Init(
			Callback::WindowImpl::SwapBuffers,
			Callback::WindowImpl::GetTime,
			Callback::WindowImpl::PollEvents,
			Callback::WindowImpl::WasClosed,
			Callback::WindowImpl::WasMinimized,
			Callback::WindowImpl::YesNoMessageBox);

		Callback::AudioImpl::Init();
		Sce::Pss::Core::Callback::AudioCallbacks::Init(
			Callback::AudioImpl::OpenMP3,
			Callback::AudioImpl::CloseMP3,
			Callback::AudioImpl::PlayMP3,
			Callback::AudioImpl::PauseMP3,
			Callback::AudioImpl::ResumeMP3,
			Callback::AudioImpl::StopMP3,
			Callback::AudioImpl::IsMP3Paused,
			Callback::AudioImpl::IsMP3Playing,
			Callback::AudioImpl::IsMP3Stopped,
			Callback::AudioImpl::SetLoop);

		return PSM_ERROR_NO_ERROR;
	}

	void Init::LoadApplication(std::string gameFolder, Graphics::Window* window) {

		Sandbox* psmSandbox = new Sandbox(gameFolder);

		std::string appInfoPath = "/Application/app.info";
		CXMLElement* elem = !psmSandbox->PathExist(appInfoPath, false) 
							? nullptr
							: new CXMLElement(psmSandbox->LocateRealPath(appInfoPath, false),
							"PSMA");
		AppInfo* psmAppInfo = new AppInfo(elem);

		Thread::SetMainThread();

		// setup window callbacks
		Init::initCallbacks(window);

		// Initalize mono
		Init::initMono(psmSandbox->LocateRealPath("/Application/app.exe", false));
	}
	

	void Init::StartApplication() {
		Init::launchExe(appExe);
	}

	int Init::initMono(std::string executablePath) {
		appExe = executablePath;

		int heapSizeLimit = AppInfo::CurrentApplication->ManagedHeapSize * 0x400;
		int resourceSizeLimit = AppInfo::CurrentApplication->ResourceHeapSize * 0x400;

		HeapAllocator::CreateResourceHeapAllocator(resourceSizeLimit);

		if (heapSizeLimit + resourceSizeLimit > 0x6000000) {
			Logger::Error("resource_heap_size + managed_heap_size > 96MB.");
			return PSM_ERROR_OUT_OF_MEMORY;
		}
		Logger::Debug("cxml : managed_heap_size : " + std::to_string(heapSizeLimit));
		Logger::Debug("cxml : resource_heap_size : " + std::to_string(resourceSizeLimit));

		Logger::Debug("Starting: " + executablePath);


		// Lockdown mono if security is enabled
		if (!Shared::Config::SecurityCritical) {
			mono_security_enable_core_clr();
			mono_security_set_core_clr_platform_callback(Sce::Pss::Core::Mono::Security::IsSecurityCriticalExempt);
		}

				
		// Tell mono there is no config file
		mono_config_parse(NULL);

		// Set runtime install location
		mono_set_dirs(Config::RuntimeLibPath.c_str(), Config::RuntimeConfigPath.c_str());
		
		// Create a domain in which this application will run under.
		psmDomain = mono_jit_init_version(appExe.c_str(), "mobile");

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

		// Add all PSM Exclusive functions.
		Init::addFunctions();


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
		mono_runtime_resource_set_callback(Sce::Pss::Core::Mono::Resources::ResourceLimitReachedCallback);

		// Set up resource limits for PSM Games... 
		mono_runtime_resource_limit(MONO_RESOURCE_JIT_CODE, 0x1000000, 0x1000000);
		mono_runtime_resource_limit(MONO_RESOURCE_METADATA, 0x1000000, 0x1000000);

		mono_gc_set_heap_size_limit(heapSizeLimit, heapSizeLimit);
		mono_thread_set_max_threads(16);
		mono_threadpool_set_max_threads(8,8);
		mono_thread_set_threads_exhausted_callback(Sce::Pss::Core::Mono::Resources::ThreadsExhaustedCallback);

		return PSM_ERROR_NO_ERROR;
	}

	void Init::launchExe(std::string runExe) {
		// Load the executable
		MonoAssembly* runAssembly = mono_domain_assembly_open(psmDomain, runExe.c_str());

		// Create argv
		char* args[2] = { (char*)runExe.c_str(), NULL };

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

	void Init::addFunctions() {
		mono_add_internal_call("Sce.PlayStation.Core.Error::GetExceptionInfoNative(string&,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Error::GetExceptionInfoNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.Log::WriteNative(string)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::Log::WriteNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.Log::GetNeedsRedirection()", reinterpret_cast<void*>(Sce::Pss::Core::Environment::Log::GetNeedsRedirection));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.SystemEvents::CheckEventsNative(Sce.PlayStation.Core.Environment.SystemEvents/InternalData&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::SystemEvents::CheckEventsNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.SystemParameters::GetInt(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::SystemParameters::GetInt));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.SystemParameters::GetFloat(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::SystemParameters::GetFloat));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.SystemParameters::GetString(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::SystemParameters::GetString));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.SystemMemory::GetMemoryUsage(bool)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::SystemMemory::GetMemoryUsage));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.PersistentMemory::WriteNative(byte[])", reinterpret_cast<void*>(Sce::Pss::Core::Environment::PersistentMemory::WriteNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.PersistentMemory::ReadNative(byte[])", reinterpret_cast<void*>(Sce::Pss::Core::Environment::PersistentMemory::ReadNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.Shell::ExecuteNative(Sce.PlayStation.Core.Environment.Shell/Action&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::Shell::ExecuteNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::NewNative(Sce.PlayStation.Core.Environment.CommonDialogType,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::NewNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::ReleaseNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::OpenNative(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.TextInputDialog/Arguments&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::OpenNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::AbortNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::AbortNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::GetState(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::GetState));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.TextInputDialog::GetResult(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Environment.TextInputDialog/Results&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::TextInputDialog::GetResult));
		mono_add_internal_call("Sce.PlayStation.Core.Services.AccountInformation::GetUniqueID(byte[])", reinterpret_cast<void*>(Sce::Pss::Core::Services::AccountInformation::GetUniqueID));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::NewNative(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::NewNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::ReleaseNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::OpenNative(int,int,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandArguments&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::OpenNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::AbortNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::AbortNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::GetState));
		mono_add_internal_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandResults&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::InAppPurchaseDialog::GetResult));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.Clipboard::SetTextNative(string)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::Clipboard::SetTextNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.Clipboard::GetTextNative(string&)", reinterpret_cast<void*>(Sce::Pss::Core::Environment::Clipboard::GetTextNative));
		mono_add_internal_call("Sce.PlayStation.Core.Environment.NetworkInformation::GetNetworkInterfaceTypeNative()", reinterpret_cast<void*>(Sce::Pss::Core::Environment::NetworkInformation::GetNetworkInterfaceTypeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::NewNative(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::NewNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::ReleaseNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.CameraImportDialog/DialogArguments&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::OpenNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::AbortNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::AbortNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::GetState));
		mono_add_internal_call("Sce.PlayStation.Core.Device.CameraImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.CameraImportDialog/DialogResults&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::CameraImportDialog::GetResult));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::NewNative(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::NewNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::ReleaseNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogArguments&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::OpenNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::AbortNative(int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::AbortNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::GetState));
		mono_add_internal_call("Sce.PlayStation.Core.Device.PhotoImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogResults&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::PhotoImportDialog::GetResult));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Create(int,int,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.MultiSampleMode,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::Create));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Delete(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::Delete));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Update(int,Sce.PlayStation.Core.Graphics.GraphicsUpdate,Sce.PlayStation.Core.Graphics.GraphicsState&,int[])", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::Update));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SwapBuffers(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::SwapBuffers));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Clear(int,Sce.PlayStation.Core.Graphics.ClearMask)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::Clear));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays2(int,Sce.PlayStation.Core.Graphics.Primitive[],int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArraysInstanced(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArraysInstanced));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels(int,byte[],Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels2(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int,int,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetMaxScreenSize(int&,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::GetMaxScreenSize));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenSizes(Sce.PlayStation.Core.Imaging.ImageSize[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenSizes));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenInfo(int,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.MultiSampleMode&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenInfo));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetCaps(int,Sce.PlayStation.Core.Graphics.GraphicsCapsState&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::GetCaps));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetActiveScreen(int,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::SetActiveScreen));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetVirtualScreen(int,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmGraphicsContext::SetVirtualScreen));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromFile(string,string,string[],int[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::FromFile));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromImage(byte[],byte[],string[],int[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::FromImage));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::Delete(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::Delete));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::AddRef(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::AddRef));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformCount(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformCount));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeCount(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeCount));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindUniform(int,string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::FindUniform));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindAttribute(int,string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::FindAttribute));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformBinding(int,int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformBinding));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformBinding(int,int,string)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformBinding));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeBinding(int,int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeBinding));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeBinding(int,int,string)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeBinding));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformType(int,int,Sce.PlayStation.Core.Graphics.ShaderUniformType&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformType));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeType(int,int,Sce.PlayStation.Core.Graphics.ShaderAttributeType&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeType));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformName(int,int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformName));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeName(int,int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeName));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformSize(int,int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformSize));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeSize(int,int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeSize));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Matrix4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector3&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector2&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,single&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,int&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Matrix4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector3[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector2[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,single[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,int[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeValue2(int,int,single[])", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeValue2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformTexture(int,int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformTexture));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeStream(int,int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeStream));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeStream(int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeStream));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Create(int,int,int,int,Sce.PlayStation.Core.Graphics.VertexFormat[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::Create));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Delete(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::Delete));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::AddRef(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::AddRef));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices(int,System.Array,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices2(int,int,System.Array,Sce.PlayStation.Core.Graphics.VertexFormat,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Vector4&,int,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices2));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetIndices(int,uint16[],int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmVertexBuffer::SetIndices));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Create(Sce.PlayStation.Core.Graphics.PixelBufferType,int,int,bool,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelBufferOption,Sce.PlayStation.Core.Graphics.InternalOption,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmPixelBuffer::Create));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Delete(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmPixelBuffer::Delete));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::AddRef(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmPixelBuffer::AddRef));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::GetInfo(int,Sce.PlayStation.Core.Graphics.PixelBufferType&,int&,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelBufferOption&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmPixelBuffer::GetInfo));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::FromFile(Sce.PlayStation.Core.Graphics.PixelBufferType,string,bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::FromFile));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::FromImage(Sce.PlayStation.Core.Graphics.PixelBufferType,byte[],bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::FromImage));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetFilter(int,Sce.PlayStation.Core.Graphics.TextureFilter&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::SetFilter));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetWrap(int,Sce.PlayStation.Core.Graphics.TextureWrap&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::SetWrap));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetMaxAnisotropy(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::SetMaxAnisotropy));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetPixels(int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,System.Array,Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int,int,int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::SetPixels));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmTexture::GenerateMipmap(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmTexture::GenerateMipmap));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Create(int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmFrameBuffer::Create));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Delete(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmFrameBuffer::Delete));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::AddRef(int)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmFrameBuffer::AddRef));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetColorTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmFrameBuffer::SetColorTarget));
		mono_add_internal_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetDepthTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Graphics::PsmFrameBuffer::SetDepthTarget));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Sound::NewFromFilename(string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Sound::NewFromFilename));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Sound::NewFromFileImage(byte[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Sound::NewFromFileImage));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Sound::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Sound::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Sound::CreatePlayerNative(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Sound::CreatePlayerNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::PlayNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::PlayNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::StopNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::StopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.SoundStatus&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetStatusNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetVolumeNative(int,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetVolumeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetVolumeNative(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::SetVolumeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPanNative(int,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetPanNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPanNative(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::SetPanNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetLoopNative(int,bool&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetLoopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetLoopNative(int,bool)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::SetLoopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPlaybackRateNative(int,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetPlaybackRateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPlaybackRateNative(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::SetPlaybackRateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPosition(int,ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPosition(int,ulong)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::SetPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetLength(int,ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::SoundPlayer::GetLength));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Bgm::NewFromFilename(string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Bgm::NewFromFilename));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Bgm::NewFromFileImage(byte[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Bgm::NewFromFileImage));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Bgm::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Bgm::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.Bgm::CreatePlayerNative(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::Bgm::CreatePlayerNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::PlayNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::PlayNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::StopNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::StopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.BgmStatus&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetStatusNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::PauseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::PauseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::ResumeNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::ResumeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetVolumeNative(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::SetVolumeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetVolumeNative(int,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetVolumeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopNative(int,bool&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetLoopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopNative(int,bool)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::SetLoopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetPlaybackRateNative(int,single&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetPlaybackRateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetPlaybackRateNative(int,single)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::SetPlaybackRateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetPosition(int,ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetPosition(int,ulong)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::SetPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLength(int,ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetLength));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopPosition(int,ulong&,ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::GetLoopPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopPosition(int,ulong,ulong)", reinterpret_cast<void*>(Sce::Pss::Core::Audio::BgmPlayer::SetLoopPosition));
		mono_add_internal_call("Sce.PlayStation.Core.Input.Touch::GetDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Input::Touch::GetDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Input.Touch::GetRearTouchDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Input::Touch::GetRearTouchDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Input.GamePad::GetDataNative(int,Sce.PlayStation.Core.Input.GamePadData&)", reinterpret_cast<void*>(Sce::Pss::Core::Input::GamePad::GetDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Input.Motion::GetDataNative(int,Sce.PlayStation.Core.Input.MotionData&)", reinterpret_cast<void*>(Sce::Pss::Core::Input::Motion::GetDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::NewFromFilename(string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::NewFromFilename));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::NewFromFileImage(byte[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::NewFromFileImage));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeColor(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,Sce.PlayStation.Core.Imaging.ImageColor&,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::NewFromModeSizeColor));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeBuffer(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,byte[],int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::NewFromModeSizeBuffer));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::AddRefNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::AddRefNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::GetSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::GetSize));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::SetDecodeSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::SetDecodeSize));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::DecodeNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::DecodeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::GetPixelData(int,byte[],uint)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::GetPixelData));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::GetPixelDataSize(int,uint&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::GetPixelDataSize));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::ResizeNative(int,Sce.PlayStation.Core.Imaging.ImageSize&,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::ResizeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::CropNative(int,Sce.PlayStation.Core.Imaging.ImageRect&,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::CropNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::DrawImageNative(int,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::DrawImageNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::DrawRectangleNative(int,Sce.PlayStation.Core.Imaging.ImageColor&,Sce.PlayStation.Core.Imaging.ImageRect&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::DrawRectangleNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::DrawTextNative(int,string,int,int,Sce.PlayStation.Core.Imaging.ImageColor&,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::DrawTextNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::ExportNative(int,string,string)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::ExportNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Image::SaveAsNative(int,string)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Image::SaveAsNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::NewFromFilenameSizeStyle(string,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::NewFromFilenameSizeStyle));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::NewFromAliasSizeStyle(Sce.PlayStation.Core.Imaging.FontAlias,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::NewFromAliasSizeStyle));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::AddRefNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::AddRefNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetName(int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetName));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetSize(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetSize));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetStyle(int,Sce.PlayStation.Core.Imaging.FontStyle&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetStyle));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetMetrics(int,Sce.PlayStation.Core.Imaging.FontMetrics&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetMetrics));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetTextWidthNative(int,string,int,int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetTextWidthNative));
		mono_add_internal_call("Sce.PlayStation.Core.Imaging.Font::GetTextMetricsNative(int,string,int,int,Sce.PlayStation.Core.Imaging.CharMetrics[])", reinterpret_cast<void*>(Sce::Pss::Core::Imaging::Font::GetTextMetricsNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Location::StartNative()", reinterpret_cast<void*>(Sce::Pss::Core::Device::Location::StartNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Location::StopNative()", reinterpret_cast<void*>(Sce::Pss::Core::Device::Location::StopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Location::GetDataNative(Sce.PlayStation.Core.Device.LocationData&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Location::GetDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Location::GetEnableDevicesNative()", reinterpret_cast<void*>(Sce::Pss::Core::Device::Location::GetEnableDevicesNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetNumberOfCamerasNative()", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetNumberOfCamerasNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetCameraFacingNative(int,Sce.PlayStation.Core.Device.CameraFacing&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetCameraFacingNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeCountNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeCountNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeCountNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeCountNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::NewFromIndex(int,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::NewFromIndex));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::ReleaseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::ReleaseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetCameraStateNative(int,Sce.PlayStation.Core.Device.CameraState&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetCameraStateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::HasTakenPictureNative(int,Sce.PlayStation.Core.Device.PictureState&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::HasTakenPictureNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::OpenNative(int,Sce.PlayStation.Core.Device.CameraSize)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::OpenNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::CloseNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::CloseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetPreviewSizeNative(int,Sce.PlayStation.Core.Device.CameraSize&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetPreviewSizeNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetPreviewImageFormatNative(int,Sce.PlayStation.Core.Device.CameraImageFormat&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetPreviewImageFormatNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::StartNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::StartNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::StopNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::StopNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::ReadNative(int,byte[],int,long&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::ReadNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::TakePictureNative(int,Sce.PlayStation.Core.Device.CameraSize)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::TakePictureNative));
		mono_add_internal_call("Sce.PlayStation.Core.Device.Camera::GetPictureFilenameNative(int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Device::Camera::GetPictureFilenameNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::CreateRequestNative(int,string,string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::CreateRequestNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::QueueRequestNative(int,string,string,int&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::QueueRequestNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::DestroyRequestNative(int)", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::DestroyRequestNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::GetResponseNative(int,string&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::GetResponseNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::RegisterThreadNative()", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::RegisterThreadNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.NetworkRequest::UnregisterThreadNative()", reinterpret_cast<void*>(Sce::Pss::Core::Services::NetworkRequest::UnregisterThreadNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::CheckStateNative(uint&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::CheckStateNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::GetOnlineIdNative(string&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::GetOnlineIdNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::GetAccountIdNative(ulong&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::GetAccountIdNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::SetWebRequestDelegate(intptr)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::SetWebRequestDelegate));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::SetAuthServer(bool)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::SetAuthServer));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::GetAuthTicketDataNative(string&)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::GetAuthTicketDataNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::ResetAuthTicketNative()", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::ResetAuthTicketNative));
		mono_add_internal_call("Sce.PlayStation.Core.Services.Network::SetAppIdNative(string)", reinterpret_cast<void*>(Sce::Pss::Core::Services::Network::SetAppIdNative));
	}
		

}