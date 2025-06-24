project('GlobalInclude', ['cpp','c'],
	version: '0.1',
	default_options: ['warning_level=0', 'cpp_std=c++20', 'default_library=static'])

cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()
include_libs = include_directories('.')
GlobalInclude_dep = declare_dependency(
	include_directories: include_libs
)
