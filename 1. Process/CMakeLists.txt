cmake_minimum_required(VERSION 3.8)
project(process VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Make main executable
add_executable(main main.cpp process.cpp)

# Make test executable
add_executable(test test.cpp process.cpp)