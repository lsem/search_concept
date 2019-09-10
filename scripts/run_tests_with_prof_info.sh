#!/usr/bin/env bash

LLVM_PROFDATA=${LLVM_ROOT}/llvm-profdata
LLVM_COV=${LLVM_ROOT}/llvm-cov

pushd bld/debug_prof/src/apps/tests_unit/
LLVM_PROFILE_FILE="tests_unit.profraw" ./tests_unit

echo "Coverege:"
${LLVM_PROFDATA} merge -sparse tests_unit.profraw -o tests_unit.profdata
${LLVM_COV} show ./tests_unit -instr-profile=tests_unit.profdata # -format=html
popd
