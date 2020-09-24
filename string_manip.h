#ifndef STRMANIP_H
#define STRMANIP_H

#include <string>
#include <vector>

std::vector <std::string> split (const std::string &s, const std::string &delim) {
    auto start = 0U;
    auto end = s.find(delim);
    std::vector <std::string> v;
    while (end != std::string::npos)
    {
        v.push_back(s.substr(start, end - start));
        start = end + delim.length();
        end = s.find(delim, start);
    }
    v.push_back(s.substr(start, end));
    return v;
}

#endif