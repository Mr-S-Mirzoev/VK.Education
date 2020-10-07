cmake_minimum_required(VERSION 3.0)
project(process VERSION 0.0.1 LANGUAGES CXX)

# Make main executable
add_executable(main main.cpp process.cpp)
target_compile_features(main PRIVATE cxx_std_17)

# Make test executable
add_executable(test test.cpp process.cpp)
target_compile_features(test PRIVATE cxx_std_17)