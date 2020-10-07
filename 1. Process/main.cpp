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
/*    std::string input;  // FOR CAT
    std::cin >> input;
    ps.write(input.data(), input.length());
    std::string s(1000, '\0'); */
    ps.read(s.data(), 1000);
    std::cout << s << std::endl;
    std::cout << ps.exec_failed() << std::endl;
    return 0;
}