cmake_minimum_required(VERSION 3.20)

project(LibDefault)

add_library(default SHARED ${CMAKE_CURRENT_SOURCE_DIR}/libdefault.cpp)

target_link_libraries(default PRIVATE
    -Wl,-whole-archive
    LibPSM
    -Wl,-no-whole-archive
)