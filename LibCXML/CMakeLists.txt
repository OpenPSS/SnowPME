cmake_minimum_required(VERSION 3.20)

project(LibCXML VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(LibCXML STATIC
    CXMLAttributeBase.hpp
    CXMLAttribute.cpp
    CXMLFile.hpp
    CXMLReader.cpp
    CXMLAttributeBase.cpp
    CXMLElement.cpp
    LibCXML.hpp
    CXMLReader.hpp
    CXMLAttribute.hpp
    CXMLStream.cpp
    CXMLStream.hpp
    CXMLElement.hpp
)

target_compile_options(LibCXML PRIVATE -Wall -Wextra)

target_include_directories(LibCXML PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
