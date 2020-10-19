cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

# Set the list of source files.
set(LIB ${LIB_DIR}/connection.cpp
        ${LIB_DIR}/descriptor.cpp
        ${LIB_DIR}/server.cpp)

add_library(${LIB_NAME} SHARED ${LIB})

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})