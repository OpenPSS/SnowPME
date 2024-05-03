COMMON=-Wall -Wextra -I External/include -I LibImGui -I LibGLAD -I LibSnowPME -I LibShared -I LibPSM -I LibCXML -I LibMonoBridge -fpermissive

CFLAGS=$(COMMON) -std=c17
CXXFLAGS=$(COMMON) -std=c++20
LDFLAGS=-lGL -lSDL2 -lSDL2_mixer -Lpss-mono-libs -lmonosgen-static

EXECUTABLE=a.out
OBJ_FILES= \
 LibCXML/CXMLElement.cpp.o \
 LibCXML/CXMLAttributeBase.cpp.o \
 LibCXML/CXMLAttribute.cpp.o \
 LibCXML/CXMLReader.cpp.o \
 LibCXML/CXMLStream.cpp.o \
 LibGLAD/glad.c.o \
 LibImGui/imgui_draw.cpp.o \
 LibImGui/imgui_demo.cpp.o \
 LibImGui/backends/imgui_impl_opengl2.cpp.o \
 LibImGui/backends/imgui_impl_sdl2.cpp.o \
 LibImGui/imgui_tables.cpp.o \
 LibImGui/imgui.cpp.o \
 LibImGui/imgui_widgets.cpp.o \
 SnowPME/Program.cpp.o \
 SnowPME/SnowPME.cpp.o \
 LibSnowPME/Runtime/Init.cpp.o \
 LibSnowPME/Graphics/Window.cpp.o \
 LibSnowPME/Graphics/Gui/ImGuiWindow.cpp.o \
 LibSnowPME/Graphics/Gui/SnowGui.cpp.o \
 LibSnowPME/Graphics/Gui/RuntimeLibsWindow.cpp.o \
 LibSnowPME/Graphics/Gui/MainWindow.cpp.o \
 LibSnowPME/Graphics/Gui/MsgBox.cpp.o \
 LibSnowPME/Graphics/Gui/DemoWindow.cpp.o \
 LibSnowPME/Graphics/Gui/InstallGamePackageWindow.cpp.o \
 LibSnowPME/Callback/Impl.cpp.o \
 LibSnowPME/Callback/WindowImpl.cpp.o \
 LibSnowPME/Callback/AudioImpl.cpp.o \
 LibMonoBridge/PssCrypto.cpp.o \
 LibShared/Threading/ThreadSafeCounter.cpp.o \
 LibShared/String/Path.cpp.o \
 LibShared/String/StringUtil.cpp.o \
 LibShared/Config.cpp.o \
 LibShared/Debug/Logger.cpp.o \
 LibPSM/Sce/Pss/Core/Threading/Thread.cpp.o \
 LibPSM/Sce/Pss/Core/Io/Sandbox.cpp.o \
 LibPSM/Sce/Pss/Core/Io/DirectoryIterator.cpp.o \
 LibPSM/Sce/Pss/Core/Io/FileSystem.cpp.o \
 LibPSM/Sce/Pss/Core/Io/ICall.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/SystemEvents.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/Shell.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/SystemMemory.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/TextInputDialog.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/Clipboard.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/NetworkInformation.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/Log.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/PersistentMemory.cpp.o \
 LibPSM/Sce/Pss/Core/Environment/SystemParameters.cpp.o \
 LibPSM/Sce/Pss/Core/Services/Network.cpp.o \
 LibPSM/Sce/Pss/Core/Services/NetworkRequest.cpp.o \
 LibPSM/Sce/Pss/Core/Services/UniqueId.cpp.o \
 LibPSM/Sce/Pss/Core/Services/AccountInformation.cpp.o \
 LibPSM/Sce/Pss/Core/Services/InAppPurchaseDialog.cpp.o \
 LibPSM/Sce/Pss/Core/Error.cpp.o \
 LibPSM/Sce/Pss/Core/Device/CameraImportDialog.cpp.o \
 LibPSM/Sce/Pss/Core/Device/Camera.cpp.o \
 LibPSM/Sce/Pss/Core/Device/PhotoImportDialog.cpp.o \
 LibPSM/Sce/Pss/Core/Device/Location.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/FrameBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmFrameBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/OpenGL.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/TextureCube.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmTexture.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmShaderProgram.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/Texture2D.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PixelBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/GraphicsObject.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/ShaderProgram.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/VertexBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmVertexBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/CGX.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/ShaderProgramOption.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmPixelBuffer.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/PsmGraphicsContext.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/GraphicsContext.cpp.o \
 LibPSM/Sce/Pss/Core/Graphics/Texture.cpp.o \
 LibPSM/Sce/Pss/Core/Timing/DeltaTime.cpp.o \
 LibPSM/Sce/Pss/Core/Errorable.cpp.o \
 LibPSM/Sce/Pss/Core/System/Handles.cpp.o \
 LibPSM/Sce/Pss/Core/System/PlatformSpecific.cpp.o \
 LibPSM/Sce/Pss/Core/ExceptionInfo.cpp.o \
 LibPSM/Sce/Pss/Core/PsmObject.cpp.o \
 LibPSM/Sce/Pss/Core/Imaging/Font.cpp.o \
 LibPSM/Sce/Pss/Core/Imaging/Image.cpp.o \
 LibPSM/Sce/Pss/Core/Callback/Callbacks.cpp.o \
 LibPSM/Sce/Pss/Core/Callback/AudioCallbacks.cpp.o \
 LibPSM/Sce/Pss/Core/Callback/WindowCallbacks.cpp.o \
 LibPSM/Sce/Pss/Core/Mono/Util.cpp.o \
 LibPSM/Sce/Pss/Core/Mono/Resources.cpp.o \
 LibPSM/Sce/Pss/Core/Mono/Security.cpp.o \
 LibPSM/Sce/Pss/Core/Edata/EdataStream.cpp.o \
 LibPSM/Sce/Pss/Core/Edata/EdataList.cpp.o \
 LibPSM/Sce/Pss/Core/Edata/PsmDrm.cpp.o \
 LibPSM/Sce/Pss/Core/Memory/HeapAllocator.cpp.o \
 LibPSM/Sce/Pss/Core/Audio/BgmPlayer.cpp.o \
 LibPSM/Sce/Pss/Core/Audio/Sound.cpp.o \
 LibPSM/Sce/Pss/Core/Audio/Bgm.cpp.o \
 LibPSM/Sce/Pss/Core/Audio/SoundPlayer.cpp.o \
 LibPSM/Sce/Pss/Core/Metadata/AppInfo.cpp.o \
 LibPSM/Sce/Pss/Core/Crypto/AesEcb.cpp.o \
 LibPSM/Sce/Pss/Core/Crypto/CryptoLibrary.cpp.o \
 LibPSM/Sce/Pss/Core/Crypto/Algorithms/sha256.c.o \
 LibPSM/Sce/Pss/Core/Crypto/Algorithms/md5.c.o \
 LibPSM/Sce/Pss/Core/Crypto/Algorithms/sha1.c.o \
 LibPSM/Sce/Pss/Core/Crypto/Algorithms/aes.c.o \
 LibPSM/Sce/Pss/Core/Crypto/Algorithms/hmac_sha256.c.o \
 LibPSM/Sce/Pss/Core/Crypto/Md5Hash.cpp.o \
 LibPSM/Sce/Pss/Core/Crypto/AesCbc.cpp.o \
 LibPSM/Sce/Pss/Core/Input/GamePad.cpp.o \
 LibPSM/Sce/Pss/Core/Input/Touch.cpp.o \
 LibPSM/Sce/Pss/Core/Input/Motion.cpp.o

$(EXECUTABLE): $(OBJ_FILES)
	g++ -o '$@' $(CXXFLAGS) $^ $(LDFLAGS)

%.c.o: %.c
	gcc -o '$@' -c $(CFLAGS) $<

%.cpp.o: %.cpp
	g++ -o '$@' -c $(CXXFLAGS) $<

.PHONY: clean

clean:
	rm -f $(EXECUTABLE) $(OBJ_FILES)

include Makefile-autogen.mk
