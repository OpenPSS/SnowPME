project('SnowPME', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()
include_libs = include_directories('.')

GlobalInclude = subproject('GlobalInclude')
LibPSM = subproject('LibPSM')
LibShared = subproject('LibShared')
LibCXML = subproject('LibCXML')
LibImGui = subproject('LibImGui')
LibGLAD = subproject('LibGLAD')
LibPssMono = subproject('LibPssMono')

GlobalInclude_dep = GlobalInclude.get_variable('GlobalInclude_dep')
LibPSM_dep = LibPSM.get_variable('LibPSM_dep')
LibShared_dep = LibShared.get_variable('LibShared_dep')
LibCXML_dep = LibCXML.get_variable('libCXML_dep')
LibImGui_dep = LibImGui.get_variable('LibImGui_dep')
LibGLAD_dep = LibGLAD.get_variable('LibGLAD_dep')
LibPssMono_dep = LibPssMono.get_variable('LibPssMono_dep')


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
		LibPSM_dep,
		LibShared_dep,
		LibCXML_dep,
		LibImGui_dep,
		LibGLAD_dep,
		LibPssMono_dep,
		GlobalInclude_dep
	],
	install: true,
)

LibSnowPME_dep = declare_dependency(
	include_directories: include_libs,
	link_with: libSnowPME
)
