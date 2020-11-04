cmake_minimum_required(VERSION 3.8)

project(tcp_server VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY tcp-server)
set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CURRENT_DIR}/../inc)
set(LIBRARY_DIR ${CURRENT_DIR})

# Set the list of source files.
set(LIB ${LIBRARY_DIR}/connection.cpp
        ${LIBRARY_DIR}/descriptor.cpp
        ${LIBRARY_DIR}/server.cpp)

add_library(${LIBRARY} SHARED ${LIB})

target_include_directories(${LIBRARY} PUBLIC ${INCLUDE_DIR})