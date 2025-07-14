
# Google test requirements
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Fetch content
include(FetchContent)
FetchContent_Declare(
    googletest  
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG 52eb8108c5bdec04579160ae17225d66034bd723
)
FetchContent_MakeAvailable(googletest)

# enable_testing()
# add_executable(
#     inky_test
#     main.cpp
# )
# target_link_libraries(
#     inky_test
#     GTest::gtest_main
# )
# include(GoogleTest)
# gtest_discover_tests(inky_test)