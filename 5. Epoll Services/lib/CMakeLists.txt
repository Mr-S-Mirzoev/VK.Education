cmake_minimum_required(VERSION 3.8)

project(tcp_server VERSION 0.0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)

set(LIBRARY epoll)
set(CURRENT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_DIR ${CURRENT_DIR}/../inc)
set(LIBRARY_DIR ${CURRENT_DIR})

set(TCP_LIB_NAME tcp-server)
set(TCP_DIR "${CURRENT_DIR}/../../3. TCP Server/lib")
set(TCP_INC ${TCP_DIR}/../inc)

# Build Server and Client
find_library(${TCP_LIB_NAME})

# Set the list of source files.
set(LIB ${LIBRARY_DIR}/buff_conn.cpp
        ${LIBRARY_DIR}/epoll.cpp
        ${LIBRARY_DIR}/listener.cpp
        ${LIBRARY_DIR}/service.cpp
        ${LIBRARY_DIR}/address.cpp)

add_library(${LIBRARY} SHARED ${LIB})
target_link_libraries(${LIBRARY} PUBLIC ${TCP_LIB_NAME})

target_include_directories(${LIBRARY} PUBLIC ${INCLUDE_DIR})
target_include_directories(${LIBRARY} PUBLIC ${TCP_INC})