cmake_minimum_required(VERSION 2.6)
project(src)

set(cmake_build_type debug)
set(cmake_cxx_flags "-Wall -Wextra -std=c++11")

add_executable( td5
    td4.cpp
    Cell.cpp
    Path.cpp
    vibes.cpp
)
