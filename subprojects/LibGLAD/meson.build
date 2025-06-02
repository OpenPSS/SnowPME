project('GLAD', 'c',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20'])


c = meson.get_compiler('c')
dirbase = meson.current_source_dir()
include_libs = include_directories('.')

libGLAD = static_library('GLAD',
        'glad.c',
		include_directories: [ include_libs ],
        install: true)

libGLAD_dep = declare_dependency(include_directories: include_libs, link_with: libGLAD)