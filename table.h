#ifndef TABLE_H
#define TABLE_H

#include "string_manip.h"
#include <iostream>
#include <string>
#include <vector>

class Table {
    int N = 0;
    std::vector <std::vector<std::string>> v;
public:
    void append(std::string &s) {
        int i = 0;
        auto spl = split(s, "\t");
        if (!N)
            N = v.size();
        else
            if (spl.size() != N)
                throw std::logic_error("Line has diff No. of columns than previous");
            else
                v.push_back(spl);
    }

};

#endif