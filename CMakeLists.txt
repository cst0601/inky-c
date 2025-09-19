cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(InkyC VERSION 1.0)

# specify the C standard
add_library(inkyc_compiler_flags INTERFACE)
set_property(TARGET inkyc_compiler_flags PROPERTY C_STANDARD 11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# example directory
add_subdirectory(examples)

# test directory
add_subdirectory(test)
