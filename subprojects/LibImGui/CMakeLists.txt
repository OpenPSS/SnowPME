cmake_minimum_required(VERSION 3.20)
project(LibImGui)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

add_library(LibImGui
    backends/imgui_impl_opengl2.cpp
    backends/imgui_impl_opengl2.h
    backends/imgui_impl_sdl2.cpp
    backends/imgui_impl_sdl2.h
    imconfig.h
    imgui_draw.cpp
    imgui_internal.h
    imgui_tables.cpp
    imgui_widgets.cpp
    imgui.cpp
    imgui.h
    LibImGui.hpp
)

target_link_libraries(LibImGui PRIVATE
    ${SDL2_LIBRARIES}
    OpenGL::OpenGL
)

target_include_directories(LibImGui
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${SDL2_INCLUDE_DIRS}
)
