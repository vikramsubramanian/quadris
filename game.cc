#include <random>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include "game.h"
#include "direction.h"
#include "levels.h"
#include "gameBoard.h"
#include "Command.h"
#include "TextDisplay.h"

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
    gameData_->seed_ = seed;
    gameData_->rng_ = std::mt19937(seed);
    gameData_->random_ = false;
    gameData_->board_ = new gameBoard;
    gameData_->board_->attach(new TextDisplay{std::cout, gameData_->board_});
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
    std::vector<Direction> dirs;
    char block;
    int mult;

    block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
    gameData_->board_->newBlock(block);
    block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
    gameData_->board_->newBlock(block);

    while (!gameData_->board_->gameOver() && std::cin >> cmd) {
        mult = cmd.multiplier_;
        switch (cmd.commandType_) {
            case Type::LEFT:
                dirs = gameData_->strat_->transform(mult, Direction::left);
                gameData_->board_->transformBlock(dirs);
                break;
            case Type::RIGHT:
                dirs = gameData_->strat_->transform(mult, Direction::right);
                gameData_->board_->transformBlock(dirs);
                break;
            case Type::DOWN:
                dirs = gameData_->strat_->transform(mult, Direction::down);
                gameData_->board_->transformBlock(dirs);
                break;
            case Type::CLOCKWISE:
                dirs = gameData_->strat_->transform(mult, Direction::clockwise);
                gameData_->board_->transformBlock(dirs);
                break;
            case Type::COUNTERCLOCKWISE:
                dirs = gameData_->strat_->transform(mult, Direction::counterclockwise);
                gameData_->board_->transformBlock(dirs);
                break;
            case Type::DROP:
                gameData_->board_->drop();
                gameData_->board_->updateScore();
                block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
                gameData_->board_->newBlock(block);
                break;
            case Type::LEVELUP:
                if (4 > gameData_->lvl_) {
                    gameData_->lvl_ += 1;
                }
                _setLevel();
                break;
            case Type::LEVELDOWN:
                if (0 < gameData_->lvl_) {
                    gameData_->lvl_ -= 1;
                }
                _setLevel();
                break;
            case Type::NORANDOM:
                gameData_->random_ = false;
                break;
            case Type::RANDOM:
                gameData_->random_ = true;
                break;
            case Type::I:
                gameData_->board_->replace('I');
                break;
            case Type::J: 
                gameData_->board_->replace('J');
                break;
            case Type::L: 
                gameData_->board_->replace('L');
                break;
            case Type::S: 
                gameData_->board_->replace('S');
                break;
            case Type::Z: 
                gameData_->board_->replace('Z');
                break;
            case Type::O: 
                gameData_->board_->replace('O');
                break;
            case Type::T:
                gameData_->board_->replace('T');
                break;
            case Type::RESTART: 
                gameData_->rng_ = std::mt19937(gameData_->seed_);
                gameData_->file_.clear();
                gameData_->file_.seekg(std::ios::beg);
                delete gameData_->board_;
                gameData_->board_ = new gameBoard;
                gameData_->board_->attach(new TextDisplay{std::cout, gameData_->board_});
                block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
                gameData_->board_->newBlock(block);
                block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
                gameData_->board_->newBlock(block);
                break;
            case Type::HINT: 
                break;
            case Type::RENAME: 
                break;
            case Type::BAD_COMMAND:
                std::cout << "Invalid player command! Please enter a proper player command." << std::endl;
                break;
            default:
                std::cout << "Invalid command!" << std::endl;
        }
    }
    std::cout << "BZZT! Game Over!" << std::endl;
}