cmake_minimum_required(VERSION 3.8)

# Project settings
project(tcp VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Set a local variable for current directory
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Library settings
set(INC_DIR ${DIR}/inc)
set(LIB_DIR ${DIR}/lib)

# Library initialazion
set(LIB_NAME epoll-net)

add_subdirectory(${LIB_DIR})