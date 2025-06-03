project('External', ['cpp','c'],
	version: '0.1',
	default_options: ['warning_level=3', 'cpp_std=c++20'])

cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()
include_libs = include_directories('./Linux/include')
External_dep = declare_dependency(
	include_directories: include_libs
)
