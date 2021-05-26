cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

# Definitions
add_definitions(-D_CRT_SECURE_NO_WARNINGS)

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    add_definitions(-DUL_RELEASE)
else()
    add_definitions(-DUL_DEBUG)
endif()

# Dependencies
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor)

project(unleash-client-c LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE "SOURCES" "${CMAKE_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE "HEADERS" "${CMAKE_SOURCE_DIR}/include/*.h")

add_library(unleash-client-c STATIC ${SOURCES} ${HEADERS})
target_include_directories(unleash-client-c PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
        "${CMAKE_SOURCE_DIR}/vendor/"
        )

message(STATUS "Searching for LibCurl...")
find_package(CURL REQUIRED)

target_link_libraries(unleash-client-c CURL::libcurl json-c)

# Example Projects
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples/simple)

# Tests
find_package(GTest)

if(GTEST_FOUND)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()
