#ifndef GAME_H_
#define GAME_H_
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
    bool random_;
    gameBoard* board_;
};

class Game {
    public:
        Game(int, std::string, int);
        ~Game();
        void play();
    private:
        void _setLevel();
        gamePImpl* gameData_;
};

#endif
