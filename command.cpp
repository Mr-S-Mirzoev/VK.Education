#include "command.h"

std::string ToUpperCommand::apply(const std::string &in_s) {
    std::string s(in_s);
    for (unsigned i = 0; i < s.length(); ++i)
        if (islower(s[i]))
            s[i] = toupper(s[i]);
    return s;
}

std::string ToLowerCommand::apply(const std::string &in_s) {
    std::string s(in_s);
    for (unsigned i = 0; i < s.length(); ++i)
        if (isupper(s[i]))
            s[i] = tolower(s[i]);
    return s;
}

ReplaceCommand::ReplaceCommand (char a, char b): A(a), B(b) {}

std::string ReplaceCommand::apply(const std::string &in_s) {
    std::string s(in_s);
    for (unsigned i = 0; i < s.length(); ++i)
        if (s[i] = A)
            s[i] = B;
    return s;
}