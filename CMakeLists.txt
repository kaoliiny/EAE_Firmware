cmake_minimum_required(VERSION 4.0)
project(EAE_Firmware)

set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_C_COMPILER gcc)

# Set global CFLAGS
set(CMAKE_C_FLAGS " -Wall -Wextra -Werror -std=c99")

# Can disabled via command-line argument -DGTESTS_INCLUDE=OFF
set(GTESTS_INCLUDE ON CACHE BOOL "Include Google tests. Enabled by default")

# Can disabled via command-line argument -DAPP_INCLUDE=OFF
set(APP_INCLUDE ON CACHE BOOL "Include build of main application Enabled by default")

if(APP_INCLUDE)
    add_subdirectory(srcs)
endif()

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
