cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(APPLICATION_NAME simple-example)

set(OUTPUT_DIR_DEBUG "${CMAKE_BINARY_DIR}/bin/examples/${APPLICATION_NAME}/Debug")
set(OUTPUT_DIR_RELEASE "${CMAKE_BINARY_DIR}/bin/examples/${APPLICATION_NAME}/Release")

file(GLOB_RECURSE "APPLICATION_SOURCE" "${CMAKE_CURRENT_SOURCE_DIR}/*.c")
file(GLOB_RECURSE "APPLICATION_HEADERS" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")

add_executable(${APPLICATION_NAME} ${APPLICATION_SOURCE} ${APPLICATION_HEADERS})
target_link_libraries(${APPLICATION_NAME} PRIVATE unleash-client-c)
target_include_directories(${APPLICATION_NAME} PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/"
        "${CMAKE_SOURCE_DIR}/include/"
        "${CMAKE_SOURCE_DIR}/vendor/"
        )
