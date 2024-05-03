cmake_minimum_required(VERSION 3.24)

project(SnowPME_Project VERSION 1.0)

set(CMAKE_COLOR_DIAGNOSTICS ON)
add_definitions(-D_DEBUG)

include(External/pss-mono.cmake)
add_subdirectory(LibGLAD)
add_subdirectory(LibImGui)

add_subdirectory(LibShared)
add_subdirectory(LibCXML)
add_subdirectory(LibPSM)
add_subdirectory(LibMonoBridge)
add_subdirectory(LibSnowPME)
add_subdirectory(SnowPME)
#add_subdirectory(LibDefault)
