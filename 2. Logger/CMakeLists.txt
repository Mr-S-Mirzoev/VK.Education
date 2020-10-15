cmake_minimum_required(VERSION 3.8)
project(process VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

# Make main and test executable
add_executable(main main.cpp log_utils.cpp logger.cpp file.cpp stdstream.cpp base.cpp tools.cpp)
add_executable(test test.cpp log_utils.cpp logger.cpp file.cpp stdstream.cpp base.cpp tools.cpp)