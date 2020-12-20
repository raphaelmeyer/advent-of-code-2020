cmake_minimum_required(VERSION 3.19)

project(AdventOfCode)

include(CTest)

# Settings
add_library(settings INTERFACE)
target_compile_options(settings INTERFACE -O2 -Wall -Wextra -Werror -std=c++20)

add_subdirectory(vendor)
add_subdirectory(source)
