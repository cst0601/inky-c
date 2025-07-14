cmake_minimum_required(VERSION 3.15)

# set the project name and version
project(InkyC VERSION 1.0)

# sub directories
add_subdirectory(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# # Google test requirements
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Fetch content
# include(FetchContent)
# FetchContent_Declare(
#     googletest  
#     GIT_REPOSITORY https://github.com/google/googletest
#     GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723
# )
# FetchContent_MakeAvailable(googletest)

# specify the C standard
add_library(inkyc_compiler_flags INTERFACE)
set_property(TARGET inkyc_compiler_flags PROPERTY C_STANDARD 11)

add_executable(InkyC src/main.c)

target_include_directories(InkyC PUBLIC includes)
target_link_libraries(InkyC PUBLIC i2c)

# build tests
enable_testing()
add_executable(
  inky_test
  test/main.cpp
)
target_link_libraries(
  inky_test 
  GTest::gtest_main
)
include(GoogleTest)
gtest_discover_tests(inky_test)
