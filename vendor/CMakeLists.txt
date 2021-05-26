cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Setting dependency settings
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Default to building shared libraries" FORCE)
set(BUILD_TESTING OFF CACHE BOOL "Disable Building of Tests" FORCE)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/json-c)
