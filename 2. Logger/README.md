# Implementation of class Logger:

    .
    ├── CMakeLists.txt
    ├── base.cpp - BaseLogger
    ├── base.hpp
    ├── file.cpp - FileLogger
    ├── file.hpp
    ├── log_utils.cpp - Global functions to work with singleton
    ├── log_utils.hpp
    ├── logger.cpp - Logger class itself
    ├── logger.hpp
    ├── main.cpp - how Process class may be used
    ├── stdstream.cpp - StdOutLogger and StdErrLogger
    ├── stdstream.hpp
    ├── test.cpp - tests for class Logger and Helper classes
    ├── test.hpp
    ├── tools.cpp - Level and Message classes + pr_debug function.
    └── tools.hpp

# Installation

    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release
    make