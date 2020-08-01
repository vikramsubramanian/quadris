#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include "game.h"
using namespace std;

int main(int argc, char *argv[])
{

    // identify if command line option given and if so
    // initiate appropriate variables for game instantiantion
    string cmd;
    bool textOnly = false;
    int seed = 0;
    string fileName = "sequence.txt";
    int startLevel = 0;

    for (int i = 1; i < argc; i++)   // seed given through command line
    {
        char* endp;
        cmd = argv[i];

        if(cmd == "-text")
            textOnly = true;
        else if (cmd == "-seed")
            seed = strtol(argv[i++ + 1], &endp, 0);
        else if(cmd == "-scriptfile")
            fileName = argv[i++ + 1];
        else if(cmd == "-startlevel")
            startLevel = strtol(argv[i++ + 1], &endp, 0);
        else
            cerr << "Invalid command line option." << endl;

    }

// initializing game object
    Game* g = new Game(startLevel, fileName, seed);
    g->play(); // returns once game is over or player quits
    delete g; // Deleting game instance
    return 1;
}


