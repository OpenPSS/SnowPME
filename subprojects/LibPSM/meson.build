project('LibPSM', 
  ['cpp', 'c'],
  version: '0.1',
  default_options:  {
    'warning_level': '0',
    'cpp_std': 'c++20',
    'c_std': 'c11',
    'default_library': 'static'
  }
)
cpp = meson.get_compiler('cpp')
c = meson.get_compiler('c')

dirbase = meson.current_source_dir()

include_libs = include_directories('.')

# required subprojects
LibShared = subproject('LibShared')
LibGLAD = subproject('LibGLAD')
LibCXML = subproject('LibCXML')
LibMonoBridge = subproject('LibMonoBridge')
LibPssMono = subproject('LibPssMono')
GlobalInclude = subproject('GlobalInclude')

LibShared_dep = LibShared.get_variable('LibShared_dep')
LibGLAD_dep = LibGLAD.get_variable('LibGLAD_dep')
LibCXML_dep = LibCXML.get_variable('libCXML_dep')
LibMonoBridge_dep = LibMonoBridge.get_variable('libMonoBridge_dep')
LibPssMono_dep = LibPssMono.get_variable('LibPssMono_dep')
GlobalInclude_dep = GlobalInclude.get_variable('GlobalInclude_dep')

LibPSM = static_library('PSM',
	'Sce/Pss/Core/Audio/Bgm.cpp',
	'Sce/Pss/Core/Audio/BgmPlayer.cpp',
	'Sce/Pss/Core/Audio/Impl/AudioImpl.cpp',
	'Sce/Pss/Core/Audio/Sound.cpp',
	'Sce/Pss/Core/Audio/SoundPlayer.cpp',
	'Sce/Pss/Core/Crypto/AesCbc.cpp',
	'Sce/Pss/Core/Crypto/AesEcb.cpp',
	'Sce/Pss/Core/Crypto/Algorithms/aes.c',
	'Sce/Pss/Core/Crypto/Algorithms/aes_x86.c',
	'Sce/Pss/Core/Crypto/Algorithms/hmac_sha256.c',
	'Sce/Pss/Core/Crypto/Algorithms/md5.c',
	'Sce/Pss/Core/Crypto/Algorithms/sha1.c',
	'Sce/Pss/Core/Crypto/Algorithms/sha256.c',
	'Sce/Pss/Core/Crypto/CryptoLibrary.cpp',
	'Sce/Pss/Core/Crypto/Md5Hash.cpp',
	'Sce/Pss/Core/Device/Camera.cpp',
	'Sce/Pss/Core/Device/CameraImportDialog.cpp',
	'Sce/Pss/Core/Device/Location.cpp',
	'Sce/Pss/Core/Device/PhotoImportDialog.cpp',
	'Sce/Pss/Core/Environment/Clipboard.cpp',
	'Sce/Pss/Core/Environment/CommonDialog.cpp',
	'Sce/Pss/Core/Environment/Log.cpp',
	'Sce/Pss/Core/Environment/NetworkInformation.cpp',
	'Sce/Pss/Core/Environment/PersistentMemory.cpp',
	'Sce/Pss/Core/Environment/Shell.cpp',
	'Sce/Pss/Core/Environment/SystemEvents.cpp',
	'Sce/Pss/Core/Environment/SystemMemory.cpp',
	'Sce/Pss/Core/Environment/SystemParameters.cpp',
	'Sce/Pss/Core/Environment/TextInputDialog.cpp',
	'Sce/Pss/Core/Error.cpp',
	'Sce/Pss/Core/Errorable.cpp',
	'Sce/Pss/Core/ExceptionInfo.cpp',
	'Sce/Pss/Core/Graphics/CGX.cpp',
	'Sce/Pss/Core/Graphics/FrameBuffer.cpp',
	'Sce/Pss/Core/Graphics/GraphicsContext.cpp',
	'Sce/Pss/Core/Graphics/OpenGL.cpp',
	'Sce/Pss/Core/Graphics/PixelBuffer.cpp',
	'Sce/Pss/Core/Graphics/PsmFrameBuffer.cpp',
	'Sce/Pss/Core/Graphics/PsmGraphicsContext.cpp',
	'Sce/Pss/Core/Graphics/PsmPixelBuffer.cpp',
	'Sce/Pss/Core/Graphics/PsmShaderProgram.cpp',
	'Sce/Pss/Core/Graphics/PsmTexture.cpp',
	'Sce/Pss/Core/Graphics/PsmVertexBuffer.cpp',
	'Sce/Pss/Core/Graphics/ShaderProgram.cpp',
	'Sce/Pss/Core/Graphics/ShaderProgramOption.cpp',
	'Sce/Pss/Core/Graphics/Texture.cpp',
	'Sce/Pss/Core/Graphics/Texture2D.cpp',
	'Sce/Pss/Core/Graphics/TextureCube.cpp',
	'Sce/Pss/Core/Graphics/VertexBuffer.cpp',
	'Sce/Pss/Core/Imaging/Font.cpp',
	'Sce/Pss/Core/Imaging/Image.cpp',
	'Sce/Pss/Core/Imaging/Impl/ImageImpl.cpp',
	'Sce/Pss/Core/InitializeCsharp.cpp',
	'Sce/Pss/Core/Input/GamePad.cpp',
	'Sce/Pss/Core/Input/Motion.cpp',
	'Sce/Pss/Core/Input/Touch.cpp',
	'Sce/Pss/Core/Io/DirectoryIterator.cpp',
	'Sce/Pss/Core/Io/Edata/EdataCallbacks.cpp',
	'Sce/Pss/Core/Io/Edata/EdataList.cpp',
	'Sce/Pss/Core/Io/Edata/EdataStream.cpp',
	'Sce/Pss/Core/Io/Edata/PsmDrm.cpp',
	'Sce/Pss/Core/Io/EmulatedDirectory.cpp',
	'Sce/Pss/Core/Io/FileSystem.cpp',
	'Sce/Pss/Core/Io/IoCall.cpp',
	'Sce/Pss/Core/Io/PsmFileHandle.cpp',
	'Sce/Pss/Core/Io/Sandbox.cpp',
	'Sce/Pss/Core/Memory/HeapAllocator.cpp',
	'Sce/Pss/Core/Metadata/AppInfo.cpp',
	'Sce/Pss/Core/Mono/InitializeMono.cpp',
	'Sce/Pss/Core/Mono/MonoUtil.cpp',
	'Sce/Pss/Core/Mono/Resources.cpp',
	'Sce/Pss/Core/Mono/Security.cpp',
	'Sce/Pss/Core/PsmObject.cpp',
	'Sce/Pss/Core/PsmUniqueObject.cpp',
	'Sce/Pss/Core/Services/AccountInformation.cpp',
	'Sce/Pss/Core/Services/InAppPurchaseDialog.cpp',
	'Sce/Pss/Core/Services/InAppPurchaseInventory.cpp',
	'Sce/Pss/Core/Services/InAppPurchaseProduct.cpp',
	'Sce/Pss/Core/Services/Network.cpp',
	'Sce/Pss/Core/Services/NetworkRequest.cpp',
	'Sce/Pss/Core/Services/UniqueId.cpp',
	'Sce/Pss/Core/System/PlatformSpecific.cpp',
	'Sce/Pss/Core/Threading/Thread.cpp',
	'Sce/Pss/Core/Timing/DeltaTime.cpp',
	'Sce/Pss/Core/Timing/Time.cpp',
	include_directories: [ include_libs ],
	dependencies: [
		LibShared_dep,
		LibGLAD_dep,
		LibCXML_dep,
		LibMonoBridge_dep,
		LibPssMono_dep,
		GlobalInclude_dep
	],
	c_args: ['-maes', '-mssse3']
)
	
LibPSM_dep = declare_dependency(
	include_directories: include_libs,
	link_with: LibPSM
)
