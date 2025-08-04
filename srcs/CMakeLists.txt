cmake_minimum_required(VERSION 4.0)
project(EAE_Firmware)

set(CMAKE_C_STANDARD 99)
# GoogleTest requires at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_C_COMPILER "gcc")

# TODO: compile only needed modules / files
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/srcs/*.c ${CMAKE_SOURCE_DIR}/srcs/*.h)

add_executable(${PROJECT_NAME} ${SOURCES})
