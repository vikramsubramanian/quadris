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

struct gamePImpl{
    gameBoard* board_;
    std::vector<Observer*> displays;
    bool gui; 
    int lvl_;
    Level* strat_;
    std::ifstream file_;
    int seed_;
    std::mt19937 rng_;
    bool random_;
    std::istream* in_;
//    int hiScore_;
    bool bonusEnabled_;
};

class Game {
    public:
        Game(int, std::string, int);
        ~Game();
        void play();
    private:
        void _attachObservers();
        void _deleteObservers();
        void _setLevel();
        void _nextBlock();
        void _restart();
        void _act(Command);
        gamePImpl* gameData_;
};

#endif
