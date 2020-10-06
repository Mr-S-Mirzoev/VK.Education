#include "thread_pool.h"
#include "command.h"
#include "table.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main (int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: ./conveyor in.txt" << std::endl;
        exit(1);
    }

    std::ifstream infile(argv[1]);   
    std::string line;
    Table t;
    while (std::getline(infile, line))
        t.append(line);

    std::cout << "Initial state:" << std::endl;
    std::cout << t;
    
    while (std::cin >> line) {
        unsigned strlen = line.length();

        std::size_t semicol_pos = line.find(':');
        if (semicol_pos == std::string::npos)
            throw std::logic_error("Wrong format");

        int N = std::stoi(line.substr(0, semicol_pos));
        Command *com;

        if (line.substr(strlen - 2) == ":u")
            com = new ToLowerCommand;
        else if (line.substr(strlen - 2) == ":U")
            com = new ToUpperCommand;
        else if (semicol_pos == strlen - 3)
            com = new ReplaceCommand(line[strlen - 2], line[strlen - 1]);
        else
            throw std::logic_error ("Unknown command");
        
        ThreadPool pool(4);
        std::vector< std::future<std::string> > results;

        for(int i = 0; i < t.height(); ++i) {
            auto s = t.get(i, N);
            results.emplace_back(
                pool.enqueue([s, com] {
                    return com->apply(s);
                })
            );
        }

        int i = 0;
        for(auto && result: results) {
            t.set(result.get(), i, N);
            i++;
        }
    }

    std::cout << std::endl << "Final state" << std::endl;
    std::cout << t;
}