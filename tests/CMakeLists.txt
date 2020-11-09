cmake_minimum_required(VERSION 2.6)
project(tests)

set(cmake_build_type debug)
set(cmake_cxx_flags "-Wall -Wextra -std=c++11")

add_executable(tests
    catch2/catch_amalgamated.hpp
    ../src/Cell.cpp
    ../src/Path.cpp
    ../src/vibes.cpp
    tests_lab.cpp
)
