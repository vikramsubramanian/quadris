#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <fstream>
#include "Game.h"
#include "Command.h"
using namespace std;

int main(int argc, char *argv[])
{

    // identify if command line option given and if so
    // initiate appropriate variables for game instantiantion
    string cmd;
    bool textOnly = false;
    int seed = 0;
    string fileName;
//    ifstream sequenceFile;
    int startLevel = 0;

    if (argc > 1)   // seed given through command line
    {
        char* endp;
        cmd = argv[1];
        switch(cmd){
            case "-text":
                textOnly = true;
                break;
            case "-seed":
                seed = strtol(argv[2], &endp, 0);
                break;
            case "-scriptfile":
                fileName = argv[2];
                break;
            case "-startlevel":
                startLevel = strtol(argv[2], &endp, 0);
                break;
            default:
                cerr << "Invalid command line option." << endl;

        }
    }
    
    // initializing game object
    Game* g = new Game(startLevel, fileName, seed);
    g->play(); // returns once game is over or player quits
    delete g; // Deleting game instance
    return 1;
}


