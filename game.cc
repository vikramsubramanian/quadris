#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include "game.h"
#include "direction.h"
#include "levels.h"
#include "gameBoard.h"
#include "Command.h"

// -------------------------------------------------------------------------------
// Constructor
Game::Game(int lvl, std::string file, int seed) {
    gameData_ = new gamePImpl;
    gameData_->lvl_ = lvl;
    setLevel();
    gameData_->file_ = std::ifstream(file);
    if(!gameData_->file_.is_open()){
        std::cerr << "Error, cannot open specified text file." << std::endl;
    }
    gameData_->seed_ = seed;
    gameData_->random_ = false;
    gameData_->board_ = new gameBoard;
}

// -------------------------------------------------------------------------------
// Destructor
Game::~Game() {
    if (nullptr != gameData_) {
        if (nullptr != gameData_->strat_) {
            delete gameData_->strat_;
        }
        if (nullptr != gameData_->board_) {
            delete gameData_->board_;
        }
        delete gameData_;
    }
}

// -------------------------------------------------------------------------------
// Level Setter
// A integer level must be set
void Game::setLevel() {
    if (nullptr != gameData_->strat_) {
        delete gameData_->strat_;
    }
    switch (gameData_->lvl_) {
        case 0:
            gameData_->strat_ = new Level0();
            break;
        case 1:
            gameData_->strat_ = new Level1();
            break;
        case 2:
            gameData_->strat_ = new Level2();
            break;
        case 3:
            gameData_->strat_ = new Level3();
            break;
        case 4:
            gameData_->strat_ = new Level4();
            break;
        default:
            std::cout << "Invalid level for creating a strategy";
            std::cout << "Invalid level: '" << gameData_->lvl_ << "'" << std::endl;
    }
}
