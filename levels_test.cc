#include "levels.h"
#include <iostream>
#include <utility>
#include <string>
#include <fstream>

int main() {
    // Our levels, we refer to them as a, b, c, and d respectively.
    Level *levels[5] = {nullptr, nullptr, nullptr, nullptr, nullptr};
    levels[0] = new Level0();
    levels[1] = new Level1();
    levels[2] = new Level2();
    levels[3] = new Level3();
    levels[4] = new Level4();
    char cmd, trans;    
    int lvl, seed;
    bool flag;
    std::string file;
    Command command;
    std::string CommandString[6] = {"left", "right", "down", "clockwise", "counterclockwise", "drop"};
    std::cout << "Please specify your sequence file." << std::endl;
    std::cin >> file;
    std::ifstream myIn (file);
    if(!myIn.is_open()){
        std::cerr << "Error, cannot open specified text file." << std::endl;
        return 0;
    }
    while (std::cin >> cmd && cmd != 'q') {
        switch (cmd) {
            case 'i':
                std::cin >> lvl >> seed;
                std::cout << levels[lvl]->nextBlock(seed) << std::endl;
                break;
            case 'f':
                std::cin >> lvl;
                std::cout << levels[lvl]->nextBlock(myIn) << std::endl;
                break;
            case 't':
                std::cin >> lvl >> trans;
                switch (trans) {
                    case 'l':
                        command = Command::left;
                        break;
                    case 'r':
                        command = Command::right;
                        break;
                    case 'd':
                        command = Command::down;
                        break;
                    case 'c':
                        command = Command::clockwise;
                        break;
                    case 'w':
                        command = Command::counterclockwise;
                        break;
                    default:
                        std::cout << "Invalid transformation case! ";
                        std::cout << "Invalid transformation: '" << trans << "'" << std::endl;
                }
                for (auto c: levels[lvl]->transform(command)) {
                    std::cout << CommandString[c] << std::endl;
                }
                break;
            case 'd':
                std::cin >> lvl;
                for (auto c: levels[lvl]->drop()) {
                    std::cout << CommandString[c] << std::endl;
                }
                break;
            case 'b':
                std::cin >> lvl >> flag;
                for (auto c: levels[lvl]->drop(flag)) {
                    std::cout << CommandString[c] << std::endl;
                }
                break;
            default:
                std::cout << "Invalid test case! ";
                std::cout << "Invalid command: '" << cmd << "'" << std::endl;
        }   
    }
    for (size_t i = 0; i < 5; ++i) delete levels[i];
    if (!std::cin && !std::cin.eof()) {
        std::cout << "Invalid test case! ";
        std::cout << "A read failed, likely because the program was trying";
        std::cout << " to read a number and didn't receive it. ";
        std::cout << "Make sure your test case is valid!" << std::endl;
        return -1;
    }
    myIn.close();
    return 0;
}