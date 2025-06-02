project('SnowPME', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()
include_libs = include_directories('.')


# external include folder
External = subproject('External')
external_dep = External.get_variable('external_dep')

# required subprojects
LibPSM = subproject('LibPSM')
libPSM_dep = LibPSM.get_variable('libPSM_dep')
LibShared = subproject('LibShared')
libShared_dep = LibShared.get_variable('libShared_dep')
LibCXML = subproject('LibCXML')
libCXML_dep = LibCXML.get_variable('libCXML_dep')
LibImGui = subproject('LibImGui')
libImGui_dep = LibImGui.get_variable('libImGui_dep')
LibGLAD = subproject('LibGLAD')
libGLAD_dep = LibGLAD.get_variable('libGLAD_dep')

libSnowPME = static_library('SnowPME',
	'Callback/Impl.cpp',
	'Callback/WindowImpl.cpp',
	'Graphics/Gui/ConfigurationWindow.cpp',
	'Graphics/Gui/DemoWindow.cpp',
	'Graphics/Gui/ImGuiWindow.cpp',
	'Graphics/Gui/InstallGameFolderWindow.cpp',
	'Graphics/Gui/InstallGamePackageWindow.cpp',
	'Graphics/Gui/InstallGameWindow.cpp',
	'Graphics/Gui/MsgBox.cpp',
	'Graphics/Gui/ProgramList.cpp',
	'Graphics/Gui/ProgramSelectWindow.cpp',
	'Graphics/Gui/RuntimeLibsWindow.cpp',
	'Graphics/Gui/SnowGui.cpp',
	'Graphics/Window.cpp',
	'Runtime/Application.cpp',
	include_directories: [ include_libs ],
		dependencies: [
		libPSM_dep,
		libShared_dep,
		libCXML_dep,
		libImGui_dep,
		libGLAD_dep,
		external_dep
	],
	install: true)

libSnowPME_dep = declare_dependency(include_directories: include_libs, link_with: libSnowPME)