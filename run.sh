#!/bin/bash

cd build && ctest -V --stop-on-failure; cd ..