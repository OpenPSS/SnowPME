project('Shared', 'cpp',
  version  '0.1',
  default_options  ['warning_level=3', 'cpp_std=c++14'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

libShared = static_library('Shared',
	'Config.cpp',
	'ProgressTracker.cpp',
	'Debug/Logger.cpp',
	'String/Path.cpp',
	'String/StringUtil.cpp',
	install: true)