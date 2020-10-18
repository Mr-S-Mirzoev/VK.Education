cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)

# Set the list of source files.
set(LIB ${LIB_DIR}/base.cpp
        ${LIB_DIR}/file.cpp
        ${LIB_DIR}/log_utils.cpp
        ${LIB_DIR}/logger.cpp
        ${LIB_DIR}/stderr.cpp
        ${LIB_DIR}/stdout.cpp
        ${LIB_DIR}/tools.cpp)

add_library(${LIB_NAME} SHARED ${LIB})

target_include_directories(${LIB_NAME} PUBLIC ${INC_DIR})