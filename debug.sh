#!/bin/bash

cmake -S . -B debug -DCMAKE_BUILD_TYPE=Debug
cmake --build debug

