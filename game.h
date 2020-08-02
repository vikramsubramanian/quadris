#ifndef GAME_H_
#define GAME_H_
#include <fstream>
#include <random>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include "direction.h"

class Level;
class gameBoard;
struct Command;

struct gamePImpl{
    int lvl_;
    Level* strat_;
    std::ifstream file_;
    int seed_;
    std::mt19937 rng_;
    bool random_;
    gameBoard* board_;
    std::istream* in_;
};

class Game {
    public:
        Game(int, std::string, int);
        ~Game();
        void play();
    private:
        void _setLevel();
        void _closeFile();
        gamePImpl* gameData_;
};

#endif
