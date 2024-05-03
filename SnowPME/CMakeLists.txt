cmake_minimum_required(VERSION 3.20)

project(SnowPME VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(SnowPME
    SnowPME.cpp
    Program.cpp
    Program.hpp
)

target_compile_options(SnowPME PRIVATE -Wall -Wextra)

target_link_libraries(SnowPME PRIVATE
    LibPSM
    LibSnowPME
    LibShared
)
