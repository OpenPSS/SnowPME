#include <Sce/Pss/Core/Mono/Init.hpp>
#include <Sce/Pss/Core/Mono/Resources.hpp>
#include <Sce/Pss/Core/Threading/Thread.hpp>
#include <Sce/Pss/Core/Memory/HeapAllocator.hpp>
#include <Sce/Pss/Core/Mono/Security.hpp>
#include <Sce/Pss/Core/Io/ICall.hpp>
#include <Sce/Pss/Core/Edata/Callbacks.hpp>
#include <Sce/Pss/Core/Io/Sandbox.hpp>
#include <Sce/Pss/Core/Metadata/AppInfo.hpp>

#include <LibCXML.hpp>
#include <LibShared.hpp>
#include <LibMonoBridge.hpp>
#include <LibPSM.hpp>

using namespace LibCXML;

using namespace Shared::Debug;
using namespace Shared;

using namespace Sce::Pss::Core::Io;
using namespace Sce::Pss::Core::Metadata;
using namespace Sce::Pss::Core::Threading;
using namespace Sce::Pss::Core::Memory;

namespace Sce::Pss::Core::Mono {
	std::string Init::appExe = "";
	MonoDomain* Init::psmDomain = nullptr;
	MonoAssembly* Init::psmCoreLib = nullptr;
	MonoAssembly* Init::msCoreLib = nullptr;
	MonoAssembly* Init::systemLib = nullptr;

	int Init::initMono(std::string gameFolder) {
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
		return Init::initMonoAssembly(sandbox->LocateRealPath("/Application/app.exe", false));
	}

	int Init::initMonoAssembly(std::string exeFile) {
		Thread::SetMainThread();

		Init::appExe = exeFile;

		int heapSizeLimit = AppInfo::CurrentApplication->ManagedHeapSize * 0x400;
		int resourceSizeLimit = AppInfo::CurrentApplication->ResourceHeapSize * 0x400;

		HeapAllocator::CreateResourceHeapAllocator(resourceSizeLimit);

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
		Init::psmDomain = mono_jit_init_version(appExe.c_str(), "mobile");

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

	void Init::launchExe() {
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

	void Init::addFunctions() {
		#define add_call(sig, func) mono_add_internal_call(sig,  reinterpret_cast<void*>(func))
		add_call("Sce.PlayStation.Core.Error::GetExceptionInfoNative(string&,string&)", Sce::Pss::Core::Error::GetExceptionInfoNative);
		add_call("Sce.PlayStation.Core.Environment.Log::WriteNative(string)", Sce::Pss::Core::Environment::Log::WriteNative);
		add_call("Sce.PlayStation.Core.Environment.Log::GetNeedsRedirection()", Sce::Pss::Core::Environment::Log::GetNeedsRedirection);
		add_call("Sce.PlayStation.Core.Environment.SystemEvents::CheckEventsNative(Sce.PlayStation.Core.Environment.SystemEvents/InternalData&)", Sce::Pss::Core::Environment::SystemEvents::CheckEventsNative);
		add_call("Sce.PlayStation.Core.Environment.SystemParameters::GetInt(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,int&)", Sce::Pss::Core::Environment::SystemParameters::GetInt);
		add_call("Sce.PlayStation.Core.Environment.SystemParameters::GetFloat(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,single&)", Sce::Pss::Core::Environment::SystemParameters::GetFloat);
		add_call("Sce.PlayStation.Core.Environment.SystemParameters::GetString(Sce.PlayStation.Core.Environment.SystemParameters/ParameterKey,string&)", Sce::Pss::Core::Environment::SystemParameters::GetString);
		add_call("Sce.PlayStation.Core.Environment.SystemMemory::GetMemoryUsage(bool)", Sce::Pss::Core::Environment::SystemMemory::GetMemoryUsage);
		add_call("Sce.PlayStation.Core.Environment.PersistentMemory::WriteNative(byte[])", Sce::Pss::Core::Environment::PersistentMemory::WriteNative);
		add_call("Sce.PlayStation.Core.Environment.PersistentMemory::ReadNative(byte[])", Sce::Pss::Core::Environment::PersistentMemory::ReadNative);
		add_call("Sce.PlayStation.Core.Environment.Shell::ExecuteNative(Sce.PlayStation.Core.Environment.Shell/Action&)", Sce::Pss::Core::Environment::Shell::ExecuteNative);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::NewNative(Sce.PlayStation.Core.Environment.CommonDialogType,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::ReleaseNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::OpenNative(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.TextInputDialog/Arguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::AbortNative(Sce.PlayStation.Core.Environment.CommonDialogType,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::GetState(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState);
		add_call("Sce.PlayStation.Core.Environment.TextInputDialog::GetResult(Sce.PlayStation.Core.Environment.CommonDialogType,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Environment.TextInputDialog/Results&)", Sce::Pss::Core::Environment::CommonDialog::GetResult);
		add_call("Sce.PlayStation.Core.Services.AccountInformation::GetUniqueID(byte[])", Sce::Pss::Core::Services::AccountInformation::GetUniqueID);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::OpenNative(int,int,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState);
		add_call("Sce.PlayStation.Core.Services.InAppPurchaseDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Services.InAppPurchaseDialog/CommandResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult);
		add_call("Sce.PlayStation.Core.Environment.Clipboard::SetTextNative(string)", Sce::Pss::Core::Environment::Clipboard::SetTextNative);
		add_call("Sce.PlayStation.Core.Environment.Clipboard::GetTextNative(string&)", Sce::Pss::Core::Environment::Clipboard::GetTextNative);
		add_call("Sce.PlayStation.Core.Environment.NetworkInformation::GetNetworkInterfaceTypeNative()", Sce::Pss::Core::Environment::NetworkInformation::GetNetworkInterfaceTypeNative);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.CameraImportDialog/DialogArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState);
		add_call("Sce.PlayStation.Core.Device.CameraImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.CameraImportDialog/DialogResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::NewNative(int,int&)", Sce::Pss::Core::Environment::CommonDialog::NewNative);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::ReleaseNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::ReleaseNative);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::OpenNative(int,int,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogArguments&)", Sce::Pss::Core::Environment::CommonDialog::OpenNative);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::AbortNative(int,int)", Sce::Pss::Core::Environment::CommonDialog::AbortNative);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::GetState(int,int,Sce.PlayStation.Core.Environment.CommonDialogState&)", Sce::Pss::Core::Environment::CommonDialog::GetState);
		add_call("Sce.PlayStation.Core.Device.PhotoImportDialog::GetResult(int,int,Sce.PlayStation.Core.Environment.CommonDialogResult&,Sce.PlayStation.Core.Device.PhotoImportDialog/DialogResults&)", Sce::Pss::Core::Environment::CommonDialog::GetResult);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Create(int,int,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.MultiSampleMode,int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Create);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Delete(int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Delete);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Update(int,Sce.PlayStation.Core.Graphics.GraphicsUpdate,Sce.PlayStation.Core.Graphics.GraphicsState&,int[])", Sce::Pss::Core::Graphics::PsmGraphicsContext::Update);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SwapBuffers(int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SwapBuffers);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::Clear(int,Sce.PlayStation.Core.Graphics.ClearMask)", Sce::Pss::Core::Graphics::PsmGraphicsContext::Clear);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArrays2(int,Sce.PlayStation.Core.Graphics.Primitive[],int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArrays2);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::DrawArraysInstanced(int,Sce.PlayStation.Core.Graphics.DrawMode,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::DrawArraysInstanced);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels(int,byte[],Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::ReadPixels2(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::ReadPixels2);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetMaxScreenSize(int&,int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetMaxScreenSize);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenSizes(Sce.PlayStation.Core.Imaging.ImageSize[],int&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenSizes);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetScreenInfo(int,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.MultiSampleMode&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetScreenInfo);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::GetCaps(int,Sce.PlayStation.Core.Graphics.GraphicsCapsState&)", Sce::Pss::Core::Graphics::PsmGraphicsContext::GetCaps);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetActiveScreen(int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SetActiveScreen);
		add_call("Sce.PlayStation.Core.Graphics.PsmGraphicsContext::SetVirtualScreen(int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmGraphicsContext::SetVirtualScreen);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromFile(string,string,string[],int[],int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FromFile);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FromImage(byte[],byte[],string[],int[],int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FromImage);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::Delete(int)", Sce::Pss::Core::Graphics::PsmShaderProgram::Delete);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::AddRef(int)", Sce::Pss::Core::Graphics::PsmShaderProgram::AddRef);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformCount(int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformCount);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeCount(int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeCount);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindUniform(int,string,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FindUniform);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::FindAttribute(int,string,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::FindAttribute);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformBinding(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformBinding);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformBinding(int,int,string)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformBinding);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeBinding(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeBinding);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeBinding(int,int,string)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeBinding);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformType(int,int,Sce.PlayStation.Core.Graphics.ShaderUniformType&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformType);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeType(int,int,Sce.PlayStation.Core.Graphics.ShaderAttributeType&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeType);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformName(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformName);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeName(int,int,string&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeName);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformSize(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformSize);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeSize(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeSize);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Matrix4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector3&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,Sce.PlayStation.Core.Vector2&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,single&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue(int,int,int,int&,Sce.PlayStation.Core.Graphics.ShaderUniformType)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Matrix4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector4[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector3[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,Sce.PlayStation.Core.Vector2[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,single[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetUniformValue2(int,int,int[],Sce.PlayStation.Core.Graphics.ShaderUniformType,int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetUniformValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeValue2(int,int,single[])", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeValue2);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetUniformTexture(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetUniformTexture);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::GetAttributeStream(int,int,int&)", Sce::Pss::Core::Graphics::PsmShaderProgram::GetAttributeStream);
		add_call("Sce.PlayStation.Core.Graphics.PsmShaderProgram::SetAttributeStream(int,int,int)", Sce::Pss::Core::Graphics::PsmShaderProgram::SetAttributeStream);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Create(int,int,int,int,Sce.PlayStation.Core.Graphics.VertexFormat[],int&)", Sce::Pss::Core::Graphics::PsmVertexBuffer::Create);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::Delete);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::AddRef);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices(int,System.Array,int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetVertices2(int,int,System.Array,Sce.PlayStation.Core.Graphics.VertexFormat,Sce.PlayStation.Core.Vector4&,Sce.PlayStation.Core.Vector4&,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetVertices2);
		add_call("Sce.PlayStation.Core.Graphics.PsmVertexBuffer::SetIndices(int,uint16[],int,int,int)", Sce::Pss::Core::Graphics::PsmVertexBuffer::SetIndices);
		add_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Create(Sce.PlayStation.Core.Graphics.PixelBufferType,int,int,bool,Sce.PlayStation.Core.Graphics.PixelFormat,Sce.PlayStation.Core.Graphics.PixelBufferOption,Sce.PlayStation.Core.Graphics.InternalOption,int&)", Sce::Pss::Core::Graphics::PsmPixelBuffer::Create);
		add_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmPixelBuffer::Delete);
		add_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmPixelBuffer::AddRef);
		add_call("Sce.PlayStation.Core.Graphics.PsmPixelBuffer::GetInfo(int,Sce.PlayStation.Core.Graphics.PixelBufferType&,int&,int&,int&,Sce.PlayStation.Core.Graphics.PixelFormat&,Sce.PlayStation.Core.Graphics.PixelBufferOption&)", Sce::Pss::Core::Graphics::PsmPixelBuffer::GetInfo);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::FromFile(Sce.PlayStation.Core.Graphics.PixelBufferType,string,bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", Sce::Pss::Core::Graphics::PsmTexture::FromFile);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::FromImage(Sce.PlayStation.Core.Graphics.PixelBufferType,byte[],bool,Sce.PlayStation.Core.Graphics.PixelFormat,int&)", Sce::Pss::Core::Graphics::PsmTexture::FromImage);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetFilter(int,Sce.PlayStation.Core.Graphics.TextureFilter&)", Sce::Pss::Core::Graphics::PsmTexture::SetFilter);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetWrap(int,Sce.PlayStation.Core.Graphics.TextureWrap&)", Sce::Pss::Core::Graphics::PsmTexture::SetWrap);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetMaxAnisotropy(int,single)", Sce::Pss::Core::Graphics::PsmTexture::SetMaxAnisotropy);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::SetPixels(int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,System.Array,Sce.PlayStation.Core.Graphics.PixelFormat,int,int,int,int,int,int)", Sce::Pss::Core::Graphics::PsmTexture::SetPixels);
		add_call("Sce.PlayStation.Core.Graphics.PsmTexture::GenerateMipmap(int)", Sce::Pss::Core::Graphics::PsmTexture::GenerateMipmap);
		add_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Create(int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::Create);
		add_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::Delete(int)", Sce::Pss::Core::Graphics::PsmFrameBuffer::Delete);
		add_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::AddRef(int)", Sce::Pss::Core::Graphics::PsmFrameBuffer::AddRef);
		add_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetColorTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::SetColorTarget);
		add_call("Sce.PlayStation.Core.Graphics.PsmFrameBuffer::SetDepthTarget(int,int,int,Sce.PlayStation.Core.Graphics.TextureCubeFace,int&)", Sce::Pss::Core::Graphics::PsmFrameBuffer::SetDepthTarget);
		add_call("Sce.PlayStation.Core.Audio.Sound::NewFromFilename(string,int&)", Sce::Pss::Core::Audio::Sound::NewFromFilename);
		add_call("Sce.PlayStation.Core.Audio.Sound::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Audio::Sound::NewFromFileImage);
		add_call("Sce.PlayStation.Core.Audio.Sound::ReleaseNative(int)", Sce::Pss::Core::Audio::Sound::ReleaseNative);
		add_call("Sce.PlayStation.Core.Audio.Sound::CreatePlayerNative(int,int&)", Sce::Pss::Core::Audio::Sound::CreatePlayerNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::ReleaseNative(int)", Sce::Pss::Core::Audio::SoundPlayer::ReleaseNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::PlayNative(int)", Sce::Pss::Core::Audio::SoundPlayer::PlayNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::StopNative(int)", Sce::Pss::Core::Audio::SoundPlayer::StopNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.SoundStatus&)", Sce::Pss::Core::Audio::SoundPlayer::GetStatusNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetVolumeNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetVolumeNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetVolumeNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetVolumeNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPanNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetPanNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPanNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetPanNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetLoopNative(int,bool&)", Sce::Pss::Core::Audio::SoundPlayer::GetLoopNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetLoopNative(int,bool)", Sce::Pss::Core::Audio::SoundPlayer::SetLoopNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPlaybackRateNative(int,single&)", Sce::Pss::Core::Audio::SoundPlayer::GetPlaybackRateNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPlaybackRateNative(int,single)", Sce::Pss::Core::Audio::SoundPlayer::SetPlaybackRateNative);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetPosition(int,ulong&)", Sce::Pss::Core::Audio::SoundPlayer::GetPosition);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::SetPosition(int,ulong)", Sce::Pss::Core::Audio::SoundPlayer::SetPosition);
		add_call("Sce.PlayStation.Core.Audio.SoundPlayer::GetLength(int,ulong&)", Sce::Pss::Core::Audio::SoundPlayer::GetLength);
		add_call("Sce.PlayStation.Core.Audio.Bgm::NewFromFilename(string,int&)", Sce::Pss::Core::Audio::Bgm::NewFromFilename);
		add_call("Sce.PlayStation.Core.Audio.Bgm::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Audio::Bgm::NewFromFileImage);
		add_call("Sce.PlayStation.Core.Audio.Bgm::ReleaseNative(int)", Sce::Pss::Core::Audio::Bgm::ReleaseNative);
		add_call("Sce.PlayStation.Core.Audio.Bgm::CreatePlayerNative(int,int&)", Sce::Pss::Core::Audio::Bgm::CreatePlayerNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::ReleaseNative(int)", Sce::Pss::Core::Audio::BgmPlayer::ReleaseNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::PlayNative(int)", Sce::Pss::Core::Audio::BgmPlayer::PlayNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::StopNative(int)", Sce::Pss::Core::Audio::BgmPlayer::StopNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetStatusNative(int,Sce.PlayStation.Core.Audio.BgmStatus&)", Sce::Pss::Core::Audio::BgmPlayer::GetStatusNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::PauseNative(int)", Sce::Pss::Core::Audio::BgmPlayer::PauseNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::ResumeNative(int)", Sce::Pss::Core::Audio::BgmPlayer::ResumeNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetVolumeNative(int,single)", Sce::Pss::Core::Audio::BgmPlayer::SetVolumeNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetVolumeNative(int,single&)", Sce::Pss::Core::Audio::BgmPlayer::GetVolumeNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopNative(int,bool&)", Sce::Pss::Core::Audio::BgmPlayer::GetLoopNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopNative(int,bool)", Sce::Pss::Core::Audio::BgmPlayer::SetLoopNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetPlaybackRateNative(int,single&)", Sce::Pss::Core::Audio::BgmPlayer::GetPlaybackRateNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetPlaybackRateNative(int,single)", Sce::Pss::Core::Audio::BgmPlayer::SetPlaybackRateNative);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetPosition(int,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetPosition);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetPosition(int,ulong)", Sce::Pss::Core::Audio::BgmPlayer::SetPosition);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLength(int,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetLength);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::GetLoopPosition(int,ulong&,ulong&)", Sce::Pss::Core::Audio::BgmPlayer::GetLoopPosition);
		add_call("Sce.PlayStation.Core.Audio.BgmPlayer::SetLoopPosition(int,ulong,ulong)", Sce::Pss::Core::Audio::BgmPlayer::SetLoopPosition);
		add_call("Sce.PlayStation.Core.Input.Touch::GetDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", Sce::Pss::Core::Input::Touch::GetDataNative);
		add_call("Sce.PlayStation.Core.Input.Touch::GetRearTouchDataNative(int,Sce.PlayStation.Core.Input.TouchData[],int,int&)", Sce::Pss::Core::Input::Touch::GetRearTouchDataNative);
		add_call("Sce.PlayStation.Core.Input.GamePad::GetDataNative(int,Sce.PlayStation.Core.Input.GamePadData&)", Sce::Pss::Core::Input::GamePad::GetDataNative);
		add_call("Sce.PlayStation.Core.Input.Motion::GetDataNative(int,Sce.PlayStation.Core.Input.MotionData&)", Sce::Pss::Core::Input::Motion::GetDataNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::NewFromFilename(string,int&)", Sce::Pss::Core::Imaging::Image::NewFromFilename);
		add_call("Sce.PlayStation.Core.Imaging.Image::NewFromFileImage(byte[],int&)", Sce::Pss::Core::Imaging::Image::NewFromFileImage);
		add_call("Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeColor(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,Sce.PlayStation.Core.Imaging.ImageColor&,int&)", Sce::Pss::Core::Imaging::Image::NewFromModeSizeColor);
		add_call("Sce.PlayStation.Core.Imaging.Image::NewFromModeSizeBuffer(Sce.PlayStation.Core.Imaging.ImageMode,Sce.PlayStation.Core.Imaging.ImageSize&,byte[],int&)", Sce::Pss::Core::Imaging::Image::NewFromModeSizeBuffer);
		add_call("Sce.PlayStation.Core.Imaging.Image::AddRefNative(int)", Sce::Pss::Core::Imaging::Image::AddRefNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::ReleaseNative(int)", Sce::Pss::Core::Imaging::Image::ReleaseNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::GetSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", Sce::Pss::Core::Imaging::Image::GetSize);
		add_call("Sce.PlayStation.Core.Imaging.Image::SetDecodeSize(int,Sce.PlayStation.Core.Imaging.ImageSize&)", Sce::Pss::Core::Imaging::Image::SetDecodeSize);
		add_call("Sce.PlayStation.Core.Imaging.Image::DecodeNative(int)", Sce::Pss::Core::Imaging::Image::DecodeNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::GetPixelData(int,byte[],uint)", Sce::Pss::Core::Imaging::Image::GetPixelData);
		add_call("Sce.PlayStation.Core.Imaging.Image::GetPixelDataSize(int,uint&)", Sce::Pss::Core::Imaging::Image::GetPixelDataSize);
		add_call("Sce.PlayStation.Core.Imaging.Image::ResizeNative(int,Sce.PlayStation.Core.Imaging.ImageSize&,int&)", Sce::Pss::Core::Imaging::Image::ResizeNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::CropNative(int,Sce.PlayStation.Core.Imaging.ImageRect&,int&)", Sce::Pss::Core::Imaging::Image::CropNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::DrawImageNative(int,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", Sce::Pss::Core::Imaging::Image::DrawImageNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::DrawRectangleNative(int,Sce.PlayStation.Core.Imaging.ImageColor&,Sce.PlayStation.Core.Imaging.ImageRect&)", Sce::Pss::Core::Imaging::Image::DrawRectangleNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::DrawTextNative(int,string,int,int,Sce.PlayStation.Core.Imaging.ImageColor&,int,Sce.PlayStation.Core.Imaging.ImagePosition&)", Sce::Pss::Core::Imaging::Image::DrawTextNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::ExportNative(int,string,string)", Sce::Pss::Core::Imaging::Image::ExportNative);
		add_call("Sce.PlayStation.Core.Imaging.Image::SaveAsNative(int,string)", Sce::Pss::Core::Imaging::Image::SaveAsNative);
		add_call("Sce.PlayStation.Core.Imaging.Font::NewFromFilenameSizeStyle(string,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", Sce::Pss::Core::Imaging::Font::NewFromFilenameSizeStyle);
		add_call("Sce.PlayStation.Core.Imaging.Font::NewFromAliasSizeStyle(Sce.PlayStation.Core.Imaging.FontAlias,int,Sce.PlayStation.Core.Imaging.FontStyle,int&)", Sce::Pss::Core::Imaging::Font::NewFromAliasSizeStyle);
		add_call("Sce.PlayStation.Core.Imaging.Font::AddRefNative(int)", Sce::Pss::Core::Imaging::Font::AddRefNative);
		add_call("Sce.PlayStation.Core.Imaging.Font::ReleaseNative(int)", Sce::Pss::Core::Imaging::Font::ReleaseNative);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetName(int,string&)", Sce::Pss::Core::Imaging::Font::GetName);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetSize(int,int&)", Sce::Pss::Core::Imaging::Font::GetSize);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetStyle(int,Sce.PlayStation.Core.Imaging.FontStyle&)", Sce::Pss::Core::Imaging::Font::GetStyle);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetMetrics(int,Sce.PlayStation.Core.Imaging.FontMetrics&)", Sce::Pss::Core::Imaging::Font::GetMetrics);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetTextWidthNative(int,string,int,int,int&)", Sce::Pss::Core::Imaging::Font::GetTextWidthNative);
		add_call("Sce.PlayStation.Core.Imaging.Font::GetTextMetricsNative(int,string,int,int,Sce.PlayStation.Core.Imaging.CharMetrics[])", Sce::Pss::Core::Imaging::Font::GetTextMetricsNative);
		add_call("Sce.PlayStation.Core.Device.Location::StartNative()", Sce::Pss::Core::Device::Location::StartNative);
		add_call("Sce.PlayStation.Core.Device.Location::StopNative()", Sce::Pss::Core::Device::Location::StopNative);
		add_call("Sce.PlayStation.Core.Device.Location::GetDataNative(Sce.PlayStation.Core.Device.LocationData&)", Sce::Pss::Core::Device::Location::GetDataNative);
		add_call("Sce.PlayStation.Core.Device.Location::GetEnableDevicesNative()", Sce::Pss::Core::Device::Location::GetEnableDevicesNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetNumberOfCamerasNative()", Sce::Pss::Core::Device::Camera::GetNumberOfCamerasNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetCameraFacingNative(int,Sce.PlayStation.Core.Device.CameraFacing&)", Sce::Pss::Core::Device::Camera::GetCameraFacingNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeCountNative(int)", Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeCountNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPreviewSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetSupportedPreviewSizeNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeCountNative(int)", Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeCountNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetSupportedPictureSizeNative(int,int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetSupportedPictureSizeNative);
		add_call("Sce.PlayStation.Core.Device.Camera::NewFromIndex(int,int&)", Sce::Pss::Core::Device::Camera::NewFromIndex);
		add_call("Sce.PlayStation.Core.Device.Camera::ReleaseNative(int)", Sce::Pss::Core::Device::Camera::ReleaseNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetCameraStateNative(int,Sce.PlayStation.Core.Device.CameraState&)", Sce::Pss::Core::Device::Camera::GetCameraStateNative);
		add_call("Sce.PlayStation.Core.Device.Camera::HasTakenPictureNative(int,Sce.PlayStation.Core.Device.PictureState&)", Sce::Pss::Core::Device::Camera::HasTakenPictureNative);
		add_call("Sce.PlayStation.Core.Device.Camera::OpenNative(int,Sce.PlayStation.Core.Device.CameraSize)", Sce::Pss::Core::Device::Camera::OpenNative);
		add_call("Sce.PlayStation.Core.Device.Camera::CloseNative(int)", Sce::Pss::Core::Device::Camera::CloseNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetPreviewSizeNative(int,Sce.PlayStation.Core.Device.CameraSize&)", Sce::Pss::Core::Device::Camera::GetPreviewSizeNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetPreviewImageFormatNative(int,Sce.PlayStation.Core.Device.CameraImageFormat&)", Sce::Pss::Core::Device::Camera::GetPreviewImageFormatNative);
		add_call("Sce.PlayStation.Core.Device.Camera::StartNative(int)", Sce::Pss::Core::Device::Camera::StartNative);
		add_call("Sce.PlayStation.Core.Device.Camera::StopNative(int)", Sce::Pss::Core::Device::Camera::StopNative);
		add_call("Sce.PlayStation.Core.Device.Camera::ReadNative(int,byte[],int,long&)", Sce::Pss::Core::Device::Camera::ReadNative);
		add_call("Sce.PlayStation.Core.Device.Camera::TakePictureNative(int,Sce.PlayStation.Core.Device.CameraSize)", Sce::Pss::Core::Device::Camera::TakePictureNative);
		add_call("Sce.PlayStation.Core.Device.Camera::GetPictureFilenameNative(int,string&)", Sce::Pss::Core::Device::Camera::GetPictureFilenameNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::CreateRequestNative(int,string,string,int&)", Sce::Pss::Core::Services::NetworkRequest::CreateRequestNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::QueueRequestNative(int,string,string,int&)", Sce::Pss::Core::Services::NetworkRequest::QueueRequestNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::DestroyRequestNative(int)", Sce::Pss::Core::Services::NetworkRequest::DestroyRequestNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::GetResponseNative(int,string&)", Sce::Pss::Core::Services::NetworkRequest::GetResponseNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::RegisterThreadNative()", Sce::Pss::Core::Services::NetworkRequest::RegisterThreadNative);
		add_call("Sce.PlayStation.Core.Services.NetworkRequest::UnregisterThreadNative()", Sce::Pss::Core::Services::NetworkRequest::UnregisterThreadNative);
		add_call("Sce.PlayStation.Core.Services.Network::CheckStateNative(uint&)", Sce::Pss::Core::Services::Network::CheckStateNative);
		add_call("Sce.PlayStation.Core.Services.Network::GetOnlineIdNative(string&)", Sce::Pss::Core::Services::Network::GetOnlineIdNative);
		add_call("Sce.PlayStation.Core.Services.Network::GetAccountIdNative(ulong&)", Sce::Pss::Core::Services::Network::GetAccountIdNative);
		add_call("Sce.PlayStation.Core.Services.Network::SetWebRequestDelegate(intptr)", Sce::Pss::Core::Services::Network::SetWebRequestDelegate);
		add_call("Sce.PlayStation.Core.Services.Network::SetAuthServer(bool)", Sce::Pss::Core::Services::Network::SetAuthServer);
		add_call("Sce.PlayStation.Core.Services.Network::GetAuthTicketDataNative(string&)", Sce::Pss::Core::Services::Network::GetAuthTicketDataNative);
		add_call("Sce.PlayStation.Core.Services.Network::ResetAuthTicketNative()", Sce::Pss::Core::Services::Network::ResetAuthTicketNative);
		add_call("Sce.PlayStation.Core.Services.Network::SetAppIdNative(string)", Sce::Pss::Core::Services::Network::SetAppIdNative);
	}

	void Init::ScePsmMonoInit(const char* gameFolder) {
		if(initMono(std::string(gameFolder)) == PSM_ERROR_NO_ERROR)
			Init::launchExe();
	}
}
