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
    while (std::getline(infile, line)) {
        t.append(line);
    }
    while (std::cin >> line) {
        unsigned strlen = line.length();
        int N = std::stoi(line.substr(0, line.find(':')));
        if (line.find(':') == std::string::npos)
        Command *com;
        if (line.substr(strlen - 2) == ":u") {
            com = new ToLowerCommand;
        } else if (line.substr(strlen - 2) == ":U") {
            com = new ToUpperCommand;
        } else {
            throw std::logic_error("Unknown command");
        }
        

    }
}