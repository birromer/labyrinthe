cmake_minimum_required(VERSION 3.5)
project(tests)

enable_testing()

#set(cmake_build_type debug)
set(cmake_cxx_flags "-Wall -Wextra -std=c++11")

add_subdirectory(Catch2)


add_executable(tests
    #    catch2/catch_amalgamated.hpp
    ../src/Cell.cpp
    ../src/Path.cpp
    ../src/vibes.cpp
    tests_lab.cpp
)

target_link_libraries(tests Catch2::Catch2)

include(CTest)
#include(./catch2/Catch.cmake)
#catch_discover_tests(tests)
include(./catch2/ParseAndAddCatchTests.cmake)
ParseAndAddCatchTests(tests)

