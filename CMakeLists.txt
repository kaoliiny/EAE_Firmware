cmake_minimum_required(VERSION 4.0)
project(EAE_Firmware)

set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_C_COMPILER gcc)

add_subdirectory(srcs)

# Can disabled via command-line argument -DTEST_INCLUDE=OFF
set(GTESTS_INCLUDE ON CACHE BOOL "Include Google tests. Enabled by default")

if(GTESTS_INCLUDE)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        52eb810 # release-1.17.0
    )

    FetchContent_MakeAvailable(googletest)

    # Enable testing for current directory and below.
    enable_testing()

    add_subdirectory(tests)
endif()
