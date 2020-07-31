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
// Public Functions (- play)
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Constructor
Game::Game(int lvl, std::string file, int seed) {
    gameData_ = new gamePImpl;
    gameData_->lvl_ = lvl;
    _setLevel();
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
        if(gameData_->file_.is_open()){
            gameData_->file_.close();
        }
        if (nullptr != gameData_->board_) {
            delete gameData_->board_;
        }
        delete gameData_;
    }
}

// -------------------------------------------------------------------------------
// Private Functions
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Level Setter
// A integer level must be set
void Game::_setLevel() {
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

// -------------------------------------------------------------------------------
// Public Functions (Only play)
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Gameplayer
void Game::play()
{
    Command cmd;
    std::vector<Direction> trans;
    while (std::cin >> cmd) {
        switch (cmd.commandType_) {
            case Type::LEFT:
                trans = gameData_->strat_->transform(Direction::left);
                gameData_->board_->transformBlock(trans);
                break;
            case Type::RIGHT:
                trans = gameData_->strat_->transform(Direction::right);
                gameData_->board_->transformBlock(trans);
                break;
            case Type::DOWN:
                trans = gameData_->strat_->transform(Direction::down);
                gameData_->board_->transformBlock(trans);
                break;
            case Type::CLOCKWISE:
                trans = gameData_->strat_->transform(Direction::clockwise);
                gameData_->board_->transformBlock(trans);
                break;
            case Type::COUNTERCLOCKWISE:
                trans = gameData_->strat_->transform(Direction::counterclockwise);
                gameData_->board_->transformBlock(trans);
                break;
            case Type::DROP:
                break;
            case Type::LEVELUP:
                break;
            case Type::LEVELDOWN:
                break;
            case Type::NORANDOM:
                gameData_->random_ = false;
                break;
            case Type::RANDOM:
                gameData_->random_ = true;
                break;
            case Type::I:
                break;
            case Type::J: 
                break;
            case Type::L: 
                break;
            case Type::S: 
                break;
            case Type::Z: 
                break;
            case Type::O: 
                break;
            case Type::RESTART: 
                break;
            case Type::HINT: 
                break;
            default:
                std::cout << "Invalid player command!";
                //std::cout << "Invalid command: '" << cmd << "'" << std::endl;
        }
    }
}

int main() { 
    int lvl, seed;
    std::string file;
    std::cout << "Please specify your starting level." << std::endl;
    std::cin >> lvl;
    std::cout << "Please specify your sequence file." << std::endl;
    std::cin >> file;
    std::cout << "Please specify your seed level." << std::endl;
    std::cin >> seed;
    Game* game = new Game(lvl, file, seed);
    game->play();
    return 0;
}