cmake_minimum_required(VERSION 3.8)

# Project settings
project(tcp_server_test VERSION 0.0.1 LANGUAGES CXX)
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
set(TARGET_CLIENT test-client)
set(TARGET_SERVER test-server)

# Initialize test binary
set(TEST_CLIENT ${SRC_DIR}/test-client.cpp)
set(TEST_SERVER ${SRC_DIR}/test-server.cpp)
add_subdirectory(${LIB_DIR})
add_executable(${TARGET_CLIENT} ${TEST_CLIENT})
add_executable(${TARGET_SERVER} ${TEST_SERVER})

# Link test binary with our library.
target_link_libraries(${TARGET_SERVER} PUBLIC ${LIB_NAME})
target_link_libraries(${TARGET_CLIENT} PUBLIC ${LIB_NAME})

# Build library
target_include_directories(${TARGET_CLIENT} PUBLIC ${LIB_DIR})
target_include_directories(${TARGET_SERVER} PUBLIC ${LIB_DIR})