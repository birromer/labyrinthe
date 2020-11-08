cmake_minimum_required(VERSION 2.6)
project(main)

set(cmake_build_type debug)
set(cmake_cxx_flags "-Wall -Wextra -std=c++11")

file(
    GLOB_RECURSE
    source_files
    src/*.cpp
)

add_executable(
    td5
    ${source_files}
)
