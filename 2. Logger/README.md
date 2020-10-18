# Implementation of class Logger:

    .
    ├── CMakeLists.txt - Global cmake which builds shared library and test executable
    ├── README.md
    ├── inc
    │   ├── base.hpp - BaseLogger
    │   ├── file.hpp - FileLogger
    │   ├── log_utils.hpp - Log utilities (global interface to work with logger)
    │   ├── logger.hpp - Logger singleton
    │   ├── stderr.hpp - StdErrLogger
    │   ├── stdout.hpp - StdOutLogger
    │   └── tools.hpp - Level class and debug prints tool
    ├── lib
    │   ├── CMakeLists.txt - Shared library linker
    │   ├── base.cpp
    │   ├── file.cpp
    │   ├── log_utils.cpp
    │   ├── logger.cpp
    │   ├── stderr.cpp
    │   ├── stdout.cpp
    │   └── tools.cpp
    └── src
        ├── test.cpp - Test source file
        └── test.hpp

# Installation

    mkdir build
    cd build
    cmake ..
    make