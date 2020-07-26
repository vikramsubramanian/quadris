#include "levels.h"
#include <iostream>
#include <utility>
using namespace std;

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
    // A board cannot be used for operations until it is constructed.
    // NOTE: If a board (a, b, c, d) is moved from then it is not longer
    // a valid object to be used for any operations (until you create 
    // a new board in that location). Moved from levels are nulled out
    // after being moved from to help you realize this.
    while (cin >> cmd && cmd != 'q') {
        switch (cmd) {
            // Command to play one turn on the target board. Expects
            // to receive which board to play on after reading 't'.
            case 'i':
                cin >> lvl >> seed;
                cout << levels[lvl]->nextBlock(seed) << endl;
                break;
            default:
                cout << "Invalid test case! ";
                cout << "Invalid command: '" << cmd << "'" << endl;
        }   
    }
    for (size_t i = 0; i < 5; ++i) delete levels[i];
    if (!cin && !cin.eof()) {
        cout << "Invalid test case! ";
        cout << "A read failed, likely because the program was trying";
        cout << " to read a number and didn't receive it. ";
        cout << "Make sure your test case is valid!" << endl;
        return -1;
    }
    return 0;
}