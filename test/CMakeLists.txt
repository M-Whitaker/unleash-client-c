cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

include(GoogleTest)

option(INTERNET  "Run tests that require the internet" ON)

add_definitions(-DTEST_FOLDER_PATH="$ENV{TEST_FOLDER}")

if (INTERNET)
    add_definitions(-DULTEST_INTERNET)
endif()

add_executable(tests test.cc
        conformance/01-simple-examples.cc
        unit/networkingTest.cc
        )
target_include_directories(tests PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/include/"
        "${CMAKE_SOURCE_DIR}/vendor/"
        )
target_link_libraries(tests PRIVATE unleash-client-c GTest::GTest)
gtest_discover_tests(tests)
