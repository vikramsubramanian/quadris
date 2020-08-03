#ifndef GAME_H_
#define GAME_H_
#include <fstream>
#include <random>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include "direction.h"

class Level;
class gameBoard;
struct Command;
class TextDisplay;
class Observer;

struct gameInit{
    int lvl_; 
    std::string file_; 
    int seed_;
    bool textOnly_;
};

struct gamePImpl{
    // Store the input parameters for the restart command
    gameInit init_;
    gameBoard* board_;
    std::vector<Observer*> displays;
    bool gui; 
    int lvl_;
    Level* strat_;
    std::ifstream file_;
    std::mt19937 rng_;
    bool random_;
    std::istream* in_;
    bool bonusEnabled_;
    // For the constructive force
    int drops_;
    int prevScore_;
    bool flag_;
};

class Game {
    public:
        Game(int, std::string, int, bool);
        ~Game();
        void play();
    private:
        // Observer DP
        void _attachObservers();
        void _deleteObservers();

        void _clearGameData();
        void _setLevel();
        void _nextBlock();
        void _restart();
        void _constructiveForce();
        void _act(Command);
        gamePImpl* gameData_;
};

#endif