#!/bin/bash

cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build Debug

