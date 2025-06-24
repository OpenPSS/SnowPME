project('GLAD', 'c',
  version: '0.1',
  default_options: ['warning_level=3', 'c_std=c99', 'default_library=static'])

dirbase = meson.current_source_dir()
include_libs = include_directories('.')

add_project_arguments('-Wno-object-to-function-pointer-cast', language: 'c')

libGLAD = static_library(
  'GLAD',
  'glad.c',
  include_directories: [ include_libs ],
  install: true
)

LibGLAD_dep = declare_dependency(
  include_directories: include_libs,
  link_with: libGLAD
)
