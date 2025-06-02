project('SnowPME', 'cpp',
  version  '0.1',
  default_options  ['warning_level=3', 'cpp_std=c++14'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

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
	install  true)
	
libSnowPME_dep = declare_dependency(link_with libSnowPME)