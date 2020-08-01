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
    Direction dir;
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
            case 'b':
                std::cin >> lvl >> seed >> flag;
                std::cout << levels[lvl]->nextBlock(seed, myIn, flag) << std::endl;
                break;
            case 't':
                std::cin >> lvl >> trans;
                switch (trans) {
                    case 'l':
                        dir = Direction::left;
                        break;
                    case 'r':
                        dir = Direction::right;
                        break;
                    case 'd':
                        dir = Direction::down;
                        break;
                    case 'c':
                        dir = Direction::clockwise;
                        break;
                    case 'w':
                        dir = Direction::counterclockwise;
                        break;
                    default:
                        std::cout << "Invalid transformation case! ";
                        std::cout << "Invalid transformation: '" << trans << "'" << std::endl;
                }
                for (auto c: levels[lvl]->transform(dir)) {
                    std::cout << CommandString[c] << std::endl;
                }
                break;
            case 'd':
                std::cin >> lvl >> flag;
                for (auto c: levels[lvl]->drop(flag)) {
                    std::cout << CommandString[c] << std::endl;
                }
                break;
            default:
                std::cout << "Invalid test case! ";
                std::cout << "Invalid dir: '" << cmd << "'" << std::endl;
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