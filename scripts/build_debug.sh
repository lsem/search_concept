#!/usr/bin/env bash

mkdir -p bld/debug/
cd bld/debug/
cmake -DCMAKE_BUILD_TYPE=Debug ../..
make -j2
