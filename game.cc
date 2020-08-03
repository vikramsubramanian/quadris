#include <fstream>
#include <random>
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include <vector>
#include "game.h"
#include "direction.h"
#include "levels.h"
#include "gameBoard.h"
#include "Command.h"
#include "observer.h"
#include "TextDisplay.h"

// -------------------------------------------------------------------------------
// Public Functions (- play)
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Constructor
Game::Game(int lvl, std::string file, int seed) {
    gameData_ = new gamePImpl;
    gameData_->board_ = new gameBoard;
    _attachObservers();
    gameData_->lvl_ = lvl;
    _setLevel();
    gameData_->file_ = std::ifstream(file);
    gameData_->seed_ = seed;
    gameData_->rng_ = std::mt19937(seed);
    gameData_->random_ = false;
    gameData_->in_ = &std::cin;
    gameData_->bonusEnabled_ = false;
}

// -------------------------------------------------------------------------------
// Destructor
Game::~Game() {
    if (nullptr != gameData_) {
        if (nullptr != gameData_->strat_) {
            delete gameData_->strat_;
        }
        if (nullptr != gameData_->board_) {
            _deleteObservers();
            delete gameData_->board_;
        }
        delete gameData_;
    }
}

// -------------------------------------------------------------------------------
// Private Functions
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Observer Attacher
void Game::_attachObservers() {
    gameData_->displays.push_back(new TextDisplay{std::cout, gameData_->board_});
    gameData_->board_->attach(gameData_->displays.at(0));
/*    
    if (GUI) {
            gameData_->displays.push_back(new GraphicDisplay{std::cout, gameData_->board_});
            gameData_->board_->attach(gameData_->displays.at(1));
    }
*/
}

// -------------------------------------------------------------------------------
// Observer Deleter
void Game::_deleteObservers() {
    for (auto a: gameData_->displays) {
        delete a;
    }
    gameData_->displays.clear();
}


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
    }
    gameData_->board_->setLevel(gameData_->lvl_);
}

// -------------------------------------------------------------------------------
// Next Block Setter
void Game::_nextBlock() {
    char block;
    block = gameData_->strat_->nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
    gameData_->board_->newBlock(block);
}

// -------------------------------------------------------------------------------
// Game Restarter
void Game::_restart() {
    int hiScore;
    
    //Reset the seed
    gameData_->rng_ = std::mt19937(gameData_->seed_);

    //Reset the block file
    gameData_->file_.clear();
    gameData_->file_.seekg(std::ios::beg);

    // Carry over the highest score, whether that's the current hiScore saved in game or something else entirely
    hiScore = gameData_->board_->getHiScore();
    _deleteObservers();
    delete gameData_->board_;
    gameData_->board_ = new gameBoard;
    _attachObservers();
    gameData_->board_->setLevel(gameData_->lvl_);
    gameData_->board_->setHiScore(hiScore);

    _nextBlock();
    _nextBlock();
}

// -------------------------------------------------------------------------------
// Game Action Taker
void Game::_act(Command cmd)
{
    std::vector<Direction> dirs;
    int mult;
    std::string file;
    std::ifstream ifn;

    mult = cmd.multiplier_;
    if (0 == mult) {
        std::cout << "A multiplier of zero does not issue a command. Please use a positive integer multiplier." << std::endl;
        return;
    }
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
            while (mult > 0) {
                gameData_->board_->drop();
                gameData_->board_->updateScore();
                _nextBlock();
                mult--;
                if (gameData_->board_->gameOver()) {
                    break;
                }
            }
            break;
        case Type::LEVELUP:
            gameData_->lvl_ = (4 > gameData_->lvl_ + mult) ? gameData_->lvl_ + mult : 4;
            _setLevel();
            break;
        case Type::LEVELDOWN:
            gameData_->lvl_ = (0 < gameData_->lvl_ - mult) ? gameData_->lvl_ - mult : 0;
            _setLevel();
            break;
        case Type::NORANDOM:
            gameData_->random_ = false;
            *(gameData_->in_) >> file;
            gameData_->file_ = std::ifstream(file);
            break;
        case Type::RANDOM:
            gameData_->random_ = true;
            break;
        case Type::SEQUENCE:
            *(gameData_->in_) >> file;
            ifn = std::ifstream(file);
            gameData_->in_ = &ifn;
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
            _restart();
            break;
        case Type::HINT: 
            break;
        case Type::RENAME:
            if(gameData_->bonusEnabled_ == false)
                std::cout << "Invalid player command! Please enter a proper player command." << std::endl;
            break;
        case Type::ENABLE_BONUS:
            gameData_->bonusEnabled_ = true;
            break;
        case Type::DISABLE_BONUS:
            gameData_->bonusEnabled_ = false;
            break;
        case Type::BAD_COMMAND:
            std::cout << "Invalid player command! Please enter a proper player command." << std::endl;
            break;
        default:
            std::cout << "Invalid command!" << std::endl;
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

    _nextBlock();
    _nextBlock();
    
    while (!gameData_->board_->gameOver() && *(gameData_->in_) >> cmd) {
        _act(cmd);
    }
    std::cout << "BZZT! Game Over!" << std::endl;
}