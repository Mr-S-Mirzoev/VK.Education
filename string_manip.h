#ifndef STRMANIP_H
#define STRMANIP_H

#include <string>
#include <vector>
#include <string_view>
#include <algorithm>

/*
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
} */

std::vector <std::string> split (const std::string &s)
{
    std::vector <std::string> v;
    static auto const isSpace = [](char letter){ return letter == ' '; };
    
    auto beginWord = std::find_if_not(begin(s), end(s), isSpace);
    while (beginWord != end(s))
    {
        auto const endWord = std::find_if(beginWord, end(s), isSpace);
        v.push_back(std::string(beginWord, endWord));
        beginWord = std::find_if_not(endWord, end(s), isSpace);
    }  
    return v;
}

#endif