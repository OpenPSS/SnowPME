project('LibImGui', 'cpp',
  version: '0.1',
  default_options: ['warning_level=3', 'cpp_std=c++20', 'default_library=static'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

libSDL2_dep = cpp.find_library('SDL2', required: true)
libOpenGL_dep = cpp.find_library('GL', required: true)

include_libs = include_directories('.')

libImGui = static_library('ImGui',
	'backends/imgui_impl_opengl2.cpp',
	'backends/imgui_impl_sdl2.cpp',
	'imgui_draw.cpp',
	'imgui_tables.cpp',
	'imgui_widgets.cpp',
	'imgui.cpp',
    dependencies: [
        libSDL2_dep,
		libOpenGL_dep
    ],
	include_directories: [ include_libs ],
	install: true)

LibImGui_dep = declare_dependency(
	include_directories: include_libs,
	link_with: libImGui
)
