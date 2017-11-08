#!/bin/sh
cd -- `dirname "$0"`
rm -rf build.32 && mkdir build.32 && cd build.32
cmake -DCMAKE_C_FLAGS=-m32 .. && make && env CTEST_OUTPUT_ON_FAILURE=1 make test
