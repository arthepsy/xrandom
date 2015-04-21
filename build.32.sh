#!/bin/sh
cd -- `dirname "$0"`
rm -rf build.32 && mkdir build.32 && cd build.32
cmake -DCMAKE_C_FLAGS=-m32 .. && make && make test
