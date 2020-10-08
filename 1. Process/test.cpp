#include "process.hpp"
#include "test.h"

int main() {
    TEST("Unknown short name", 0, {
        std::string path;
        std::vector <std::string> args;

        path = "lsa";
        args.push_back("-haltr");

        Process ps(path, args);
        std::cout << "Exec return status: " << ps.return_status() << std::endl;
        ps.close();
    })

    TEST("Okay short name", 1, {
        std::string path;
        std::vector <std::string> args;

        path = "ls";
        args.push_back("-haltr");

        Process ps(path, args);
        std::cout << "Exec return status: " << ps.return_status() << std::endl;
        ps.close();
    })

    TEST("Reading the output", 2, {
        std::string path;
        std::vector <std::string> args;

        path = "ls";
        args.push_back("-haltr");

        Process ps(path, args);
        std::string s(1000, '\0'); 
        ps.read(s.data(), 1000);
        std::cout << s;
        ps.close();
    })

    TEST("Reading the output of failed process", 3, {
        std::string path;
        std::vector <std::string> args;

        path = "lsa";
        args.push_back("-haltr");

        Process ps(path, args);
        std::string s(1000, '\0'); 
        ps.read(s.data(), 1000);
        std::cout << s;
        ps.close();
    })

    TEST("Performing cat of input", 4, {
        std::string path;
        std::vector <std::string> args;

        path = "cat";

        Process ps(path, args);

        std::string input;
        std::string s(1000, '\0'); 
        
        while (std::cin >> input) {
            ps.write(input.data(), input.length());
            ps.read(s.data(), 1000);
            std::cout << s << std::endl;
            s.assign(1000, '\0'); 
        }
        ps.close();
    }) 
}