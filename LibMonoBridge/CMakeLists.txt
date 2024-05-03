cmake_minimum_required(VERSION 3.20)

project(LibMonoBridge VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(LibMonoBridge
    LibMonoBridge.hpp
    PssCrypto.cpp
    PssCrypto.hpp
)

target_compile_options(LibMonoBridge PRIVATE -Wall -Wextra)

target_link_libraries(LibMonoBridge PRIVATE LibPSM)
