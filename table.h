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
        auto spl = split(s);
        if (!N)
            N = spl.size();

        if (spl.size() != N)
            throw std::logic_error("Line has diff No. of columns than previous");
        else
            v.push_back(spl);
    }

    std::size_t height () const {
        return v.size();
    }

    std::string get(int i, int N) {
        return v[i][N];
    }

    void set (const std::string &s, int i, int N) {
        v[i][N] = s;
    }

    friend std::ostream& operator<< (std::ostream &out, Table &t) {
        for (auto &ln : t.v) {
            for (auto &s : ln)
                out << s << "\t";
            out << std::endl;
        }
        return out;
    }
};

#endif