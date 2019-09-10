#!/usr/bin/env bash

mkdir -p bld/debug_prof/
cd bld/debug_prof/
cmake -DCLANG_CODE_COVEREGE=ON -DCMAKE_BUILD_TYPE=Debug ../..
make -j2
