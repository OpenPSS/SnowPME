project('ImGui', 'cpp',
  version  '0.1',
  default_options  ['warning_level=3', 'cpp_std=c++14'])


cpp = meson.get_compiler('cpp')
dirbase = meson.current_source_dir()

libImGui = static_library('ImGui',
	'backends/imgui_impl_opengl2.cpp',
	'backends/imgui_impl_sdl2.cpp',
	'imgui_draw.cpp',
	'imgui_tables.cpp',
	'imgui_widgets.cpp',
	'imgui.cpp',
	install  true)
	
libImGui_dep = declare_dependency(link_with libImGui)