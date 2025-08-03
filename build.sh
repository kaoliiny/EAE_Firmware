#!/bin/bash 

# enable verbose mode
set -x

BUILD_OPTIONS=""

if [ "$1" == "all" ]
then
    BUILD_OPTIONS=""
elif [ "$1" == "tests" ]
then
    BUILD_OPTIONS+="-DAPP_INCLUDE=OFF"
elif [ "$1" == "app" ]
then
    BUILD_OPTIONS+="-DGTESTS_INCLUDE=OFF"
fi

rm -rf build && cmake -B build $BUILD_OPTIONS; cmake --build build;
