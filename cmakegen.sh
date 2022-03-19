#!/bin/bash

mkdir -p build
cd build
cmake -DCMAKE_OSX_DEPLOYMENT_TARGET=10.15 ..
make -j4
