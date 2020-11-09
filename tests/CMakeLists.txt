cmake_minimum_required(VERSION 3.5)
project(tests)

enable_testing()

#set(cmake_build_type debug)
set(cmake_cxx_flags "-Wall -Wextra -std=c++11")

add_executable(tests
    catch2/catch_amalgamated.hpp
    ../src/Cell.cpp
    ../src/Path.cpp
    ../src/vibes.cpp
    tests_lab.cpp
)

include(CTest)
include(./Catch.cmake)
include(./ParseAndAddCatchTests.cmake)
ParseAndAddCatchTests(tests)
#catch_discover_tests(tests)
