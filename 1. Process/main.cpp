#include "process.hpp"

int main(int argc, char *argv[]) {
    std::string path;
    std::vector <std::string> args;
    if (argc >= 2) {
        path = argv[1];
        for (int i = 2; i < argc; ++i)
            args.push_back(argv[i]);
    } else {
        path = "ls";
        args.push_back("-haltr");
    }
    Process ps(path, args);
    std::string s(1000, '\0'); 
    ps.read(s.data(), 1000);
    std::cout << s;
    return 0;
}