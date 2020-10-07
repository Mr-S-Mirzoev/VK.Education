#ifndef TEST_H
#define TEST_H

#define TEST(name, count, code) \
    {\
        std::cout << "Test \"" << name << "\" #" << count << std::endl; \
        code \
        std::cout << std::endl; \
    }

#endif