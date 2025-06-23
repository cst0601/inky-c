cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(InkyC VERSION 1.0)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# specify the C standard
add_library(inkyc_compiler_flags INTERFACE)
set_property(TARGET inkyc_compiler_flags PROPERTY C_STANDARD 11)

add_executable(InkyC src/main.c)

target_include_directories(InkyC PUBLIC includes)

target_link_libraries(InkyC PUBLIC inkyc_compiler_flags i2c)