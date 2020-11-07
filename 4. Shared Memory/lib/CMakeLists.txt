cmake_minimum_required(VERSION 3.8)

project(shmem-map VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY shmem-map)
set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CURRENT_DIR}/../inc)
set(LIBRARY_DIR ${CURRENT_DIR})

# Set the list of source files.
set(LIB ${LIBRARY_DIR}/allocator.cpp)

add_library(${LIBRARY} SHARED ${LIB})

target_include_directories(${LIBRARY} PUBLIC ${INCLUDE_DIR})