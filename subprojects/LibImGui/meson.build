project('ImGui', 'cpp',
  version  '0.1',
  default_options  ['warning_level=3', 'cpp_std=c++14'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

libSDL2_dep = cpp.find_library('libSDL2', required: true)
libOpenGL_dep = cpp.find_library('libOpenGL', required: true)

libImGui = static_library('ImGui',
	'backends/imgui_impl_opengl2.cpp',
	'backends/imgui_impl_sdl2.cpp',
	'imgui_draw.cpp',
	'imgui_tables.cpp',
	'imgui_widgets.cpp',
	'imgui.cpp',
    dependencies: [
        libOpenGL_dep,
        libSDL2_dep,
    ],
	install: true)