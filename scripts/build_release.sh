#!/usr/bin/env bash

mkdir -p bld/release/
cd bld/release/
cmake -DCMAKE_BUILD_TYPE=Release ../..
make -j2
