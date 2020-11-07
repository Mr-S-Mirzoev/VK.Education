cmake_minimum_required(VERSION 3.8)
project(shmem-map-test VERSION 0.1 DESCRIPTION "Shared memory map" LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# Set a local variable for current directory
set(DIR ${CMAKE_CURRENT_SOURCE_DIR})

# Library settings
set(INC_DIR ${DIR}/inc)
set(LIB_DIR ${DIR}/lib)
set(LIBRARY_NAME shmem-map)

# Test library settings
set(TESTS_DIR ${DIR}/example)

# Initialize test binary
set(TEST_ALLOC_USE ${TESTS_DIR}/allocator-usage.cpp)
set(TARGET_ALLOC_USE alloc-use)

# Build library
add_subdirectory(${LIB_DIR})

# Enable headers for executable
include_directories(${CUR_DIR}/inc)

# Executable
add_executable(${TARGET_ALLOC_USE} ${TEST_ALLOC_USE})
target_link_libraries(${TARGET_ALLOC_USE} PUBLIC ${LIBRARY_NAME})
target_include_directories(${TARGET_ALLOC_USE} PUBLIC ${INC_DIR})