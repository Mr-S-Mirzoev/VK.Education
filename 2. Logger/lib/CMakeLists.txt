cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

set(LIB_SRC ${LIB_DIR}/src)

# Set the list of source files.
set(LIB ${LIB_SRC}/base.cpp
        ${LIB_SRC}/file.cpp
        ${LIB_SRC}/log_utils.cpp
        ${LIB_SRC}/logger.cpp
        ${LIB_SRC}/stderr.cpp
        ${LIB_SRC}/stdout.cpp
        ${LIB_SRC}/tools.cpp)

add_library(${LIB_NAME} SHARED ${LIB})

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})