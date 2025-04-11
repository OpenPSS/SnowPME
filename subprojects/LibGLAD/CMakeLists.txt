cmake_minimum_required(VERSION 3.20)
project(Glad)

add_library(glad glad/glad.h glad.c)
target_include_directories(glad PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
