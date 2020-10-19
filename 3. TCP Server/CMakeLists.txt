cmake_minimum_required(VERSION 3.8)

# Project settings
project(tcp_server VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Library settings
set(INC_DIR ${DIR}/inc)
set(LIB_DIR ${DIR}/lib)

# Test library settings
set(SRC_DIR ${DIR}/src)

# Library name
set(LIB_NAME tcp-server)
set(TARGET_NAME test)

# Initialize test binary
set(TEST ${SRC_DIR}/test.cpp)
add_subdirectory(${LIB_DIR})
add_executable(${TARGET_NAME} ${TEST})

# Link test binary with our library.
target_link_libraries(${TARGET_NAME} PUBLIC ${LIB_NAME})

# Build library
target_include_directories(${TARGET_NAME} PUBLIC ${LIB_DIR})