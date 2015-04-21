#!/bin/sh
cd -- `dirname "$0"`
rm -rf build.64 && mkdir build.64 && cd build.64
cmake -DCMAKE_C_FLAGS=-m64 cmake .. && make && make test
