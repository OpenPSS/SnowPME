project('GLAD', 'cpp',
  version  '0.1',
  default_options  ['warning_level=3', 'cpp_std=c++14'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

libGLAD = static_library('GLAD',
        'glad.c',
        install: true)