project('Shared', 'cpp',
  version: '0.1',
  default_options: ['warning_level=0', 'cpp_std=c++20'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()
include_libs = include_directories('.')

libShared = static_library('Shared',
	'Config.cpp',
	'Threading/ProgressTracker.cpp',
	'Debug/Logger.cpp',
	'Debug/Assert.cpp',
	'String/Path.cpp',
	'String/Format.cpp',
	'Windowing/CallbackBase.cpp',
	'Windowing/Event.cpp',
	'Windowing/EventQueue.cpp',
	'Windowing/WindowControl.cpp',
	include_directories: [ include_libs ],
	install: true)
	
LibShared_dep = declare_dependency(
	include_directories: include_libs,
	link_with: libShared
)
