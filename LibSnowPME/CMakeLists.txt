cmake_minimum_required(VERSION 3.20)

project(LibSnowPME VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(LibSnowPME
    Callback/Impl.hpp
    Callback/WindowImpl.cpp
    Callback/AudioImpl.hpp
    Callback/Impl.cpp
    Callback/AudioObject.hpp
    Callback/AudioImpl.cpp
    Callback/WindowImpl.hpp
    Runtime/Init.cpp
    Runtime/Init.hpp
    Graphics/Window.cpp
    Graphics/Window.hpp
    Graphics/Gui/MsgBox.cpp
    Graphics/Gui/MsgBox.hpp
    Graphics/Gui/RuntimeLibsWindow.cpp
    Graphics/Gui/DemoWindow.hpp
    Graphics/Gui/RuntimeLibsWindow.hpp
    Graphics/Gui/ImGuiWindow.hpp
    Graphics/Gui/ImGuiWindow.cpp
    Graphics/Gui/SnowGui.hpp
    Graphics/Gui/InstallGamePackageWindow.cpp
    Graphics/Gui/SnowGui.cpp
    Graphics/Gui/MainWindow.hpp
    Graphics/Gui/InstallGamePackageWindow.hpp
    Graphics/Gui/MainWindow.cpp
    Graphics/Gui/DemoWindow.cpp
    LibSnowPME.hpp
)

target_compile_options(LibSnowPME PRIVATE -Wall -Wextra)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2_mixer REQUIRED CONFIG REQUIRED COMPONENTS SDL2_mixer)

target_link_libraries(LibSnowPME
PRIVATE
    LibPSM
    LibShared
    LibCXML
    LibImGui
    glad
    SDL2::SDL2
    SDL2_mixer
PUBLIC
    LibPSSMono
)

target_include_directories(LibSnowPME PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${SDL2_INCLUDE_DIRS}
)