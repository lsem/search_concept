add_library(llvm_expected INTERFACE)
# we cannot use set_target_properties(.. CXX_STANDARD 20) for interface libs, BUT even line below
# shich must work not woking with Clang 10, uncomment once we have c++20 compiler.
# So far we can make it working by making sure targets using this lib enable C++20.
# target_compile_features(llvm_expected INTERFACE cxx_std_20)
target_include_directories(llvm_expected INTERFACE include/)

