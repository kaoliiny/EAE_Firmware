#!/bin/bash

# enable verbose mode
set -x

if [ "$1" == "tests" ]
then
    ctest --test-dir build -V --stop-on-failure;
elif [ "$1" == "app" ]
then
    ./build/srcs/EAE_Firmware $2
fi
