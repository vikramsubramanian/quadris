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
    char cmd;    
    int lvl, seed;
    std::string file;
    // A board cannot be used for operations until it is constructed.
    // NOTE: If a board (a, b, c, d) is moved from then it is not longer
    // a valid object to be used for any operations (until you create 
    // a new board in that location). Moved from levels are nulled out
    // after being moved from to help you realize this.
    std::cout << "Please specify your sequence file." << std::endl;
    std::cin >> file;
    std::ifstream myIn (file);
    if(!myIn.is_open()){
        std::cerr << "Error, cannot open specified text file." << std::endl;
        return 0;
    }
    while (std::cin >> cmd && cmd != 'q') {
        switch (cmd) {
            // Command to play one turn on the target board. Expects
            // to receive which board to play on after reading 't'.
            case 'i':
                std::cin >> lvl >> seed;
                std::cout << levels[lvl]->nextBlock(seed) << std::endl;
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