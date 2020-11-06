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

# Test library settings
set(TESTS_DIR ${DIR}/tests)

# Library name
set(LIB_NAME tcp-server)
set(TARGET_CLIENT test-client)
set(TARGET_SERVER test-server)

# Initialize test binary
set(TEST_CLIENT ${TESTS_DIR}/test-client.cpp)
set(TEST_SERVER ${TESTS_DIR}/test-server.cpp)
add_subdirectory(${LIB_DIR})

# Build and link client.
add_executable(${TARGET_CLIENT} ${TEST_CLIENT})
target_link_libraries(${TARGET_CLIENT} PUBLIC ${LIB_NAME})
target_include_directories(${TARGET_CLIENT} PUBLIC ${INC_DIR})

# Build and link server.
add_executable(${TARGET_SERVER} ${TEST_SERVER})
target_link_libraries(${TARGET_SERVER} PUBLIC ${LIB_NAME})
target_include_directories(${TARGET_SERVER} PUBLIC ${INC_DIR})