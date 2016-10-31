cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project("cpp-lib")

enable_testing()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

SET( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++11" )
include_directories(${CMAKE_CURRENT_SOURCE_DIR} include/)

add_subdirectory(src)
add_subdirectory(tests)
