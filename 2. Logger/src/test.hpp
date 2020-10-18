#ifndef TEST_H
#define TEST_H

#include <iostream>

#define TEST(name, count, code) \
    std::cerr << "Test START" << std::endl; \
    {\
        std::cout << "Test \"" << name << "\" #" << count << std::endl; \
        try { \
            code \
        } catch (std::runtime_error &re) { \
            std::cout << "Exec failed: " << re.what() << std::endl; \
        } \
    } \
    std::cerr << "Test END" << std::endl; \
    std::cout << std::endl; 

#endif