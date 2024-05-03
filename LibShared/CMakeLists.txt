cmake_minimum_required(VERSION 3.20)

project(LibShared VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(LibShared STATIC
    Threading/ThreadSafeCounter.hpp
    Threading/ThreadSafeCounter.cpp
    Debug/Logger.hpp
    Debug/Logger.cpp
    LibShared.hpp
    Config.cpp
    String/StringUtil.cpp
    String/Path.cpp
    String/StringUtil.hpp
    String/Path.hpp
    RuntimeImplementation.hpp
    Config.hpp
)

target_compile_options(LibShared PRIVATE -Wall -Wextra)

target_include_directories(LibShared PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)