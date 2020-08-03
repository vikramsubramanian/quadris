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
Game::Game(int lvl, std::string file, int seed, bool textOnly)
{
    gameData_ = new gamePImpl;

    // initiation
    gameData_->init_.lvl_ = lvl;
    gameData_->init_.file_ = file;
    gameData_->init_.seed_ = seed;
    gameData_->init_.textOnly_ = textOnly;

    // set up Observer DP
    gameData_->board_ = new gameBoard;
    _attachObservers();

    // setup game data values
    gameData_->lvl_ = lvl;
    _setLevel();
    gameData_->file_ = std::ifstream(file);
    gameData_->rng_ = std::mt19937(seed);
    gameData_->random_ = false;
    gameData_->in_ = &std::cin;
    gameData_->bonusEnabled_ = false;
}

// -------------------------------------------------------------------------------
// Destructor
Game::~Game()
{
    _clearGameData();
    delete gameData_;
}

// -------------------------------------------------------------------------------
// Private Functions
// -------------------------------------------------------------------------------

// -------------------------------------------------------------------------------
// Observer Attacher
void Game::_attachObservers()
{
    gameData_->displays.push_back
        (new TextDisplay{std::cout, gameData_->board_});
    gameData_->board_->attach(gameData_->displays.at(0));
}

// -------------------------------------------------------------------------------
// Observer Deleter
void Game::_deleteObservers()
{
    for (auto a: gameData_->displays)
    {
        delete a;
    }
    gameData_->displays.clear();
}

// -------------------------------------------------------------------------------
// Game Data Clearer
void Game::_clearGameData()
{
    if (nullptr != gameData_)
    {
        if (nullptr != gameData_->strat_)
        {
            delete gameData_->strat_;
            gameData_->strat_ = nullptr;
        }   // delete level (strategy DP)
        if (nullptr != gameData_->board_)
        {
            _deleteObservers();
            delete gameData_->board_;
            gameData_->board_ = nullptr;
        }   // delete board and observers
    }
}

// -------------------------------------------------------------------------------
// Level Setter
// A integer level must be set
void Game::_setLevel()
{
    // delete old instance of level
    if (nullptr != gameData_->strat_)
    {
        delete gameData_->strat_;
        gameData_->strat_ = nullptr;
    }

    // determine new level and create instance
    switch (gameData_->lvl_)
    {
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

    // update game data and board
    gameData_->board_->setLevel_(gameData_->lvl_);
    gameData_->drops_ = 0;
    gameData_->prevScore_ = gameData_->board_->getScore_();
    gameData_->flag_ = true;
}

// -------------------------------------------------------------------------------
// Next Block Setter
void Game::_nextBlock()
{
    char block;
    block = gameData_->strat_->
            nextBlock(gameData_->rng_, gameData_->file_, gameData_->random_);
    gameData_->board_->newBlock_(block);
}

// -------------------------------------------------------------------------------
// Game Restarter
void Game::_restart()
{
    int hiScore;
    
    // Carry over the highest score, whether that's the
    // current hiScore saved in game or something else entirely
    hiScore = gameData_->board_->getHiScore_();
    _clearGameData();

    //Reset the block file
    gameData_->board_ = new gameBoard;
    _attachObservers();
    gameData_->board_->setHiScore_(hiScore);
    gameData_->lvl_ = gameData_->init_.lvl_;
    _setLevel();
    gameData_->file_ = std::ifstream( gameData_->init_.file_);
    gameData_->rng_ = std::mt19937(gameData_->init_.seed_);
    gameData_->random_ = false;
    gameData_->in_ = &std::cin;
    gameData_->bonusEnabled_ = false;

    _nextBlock();
    _nextBlock();
}

// -------------------------------------------------------------------------------
// External Force Handler
void Game::_constructiveForce()
{
    gameData_->drops_++;
    if (gameData_->prevScore_ != gameData_->board_->getScore_())
    {
        gameData_->flag_ = false;
    }

    // count blocks dropped and use constructive force
    // when too many blocks have dropped
    if (0 == gameData_->drops_ % 5)
    {
        if (gameData_->flag_ && gameData_->lvl_ == 4)
        {
            gameData_->board_->constructiveForce_('B');
        } 
        gameData_->flag_ = true;
    }

    gameData_->prevScore_ = gameData_->board_->getScore_();
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
    // handle zero multiplier
    if (0 == mult)
    {
        std::cout << "A multiplier of zero does not issue a command. " <<
            "Please use a positive integer multiplier." << std::endl;
        return;
    }

    // identify command and perform necessary actions
    switch (cmd.commandType_)
    {
        case Type::LEFT:
            dirs = gameData_->strat_->transform(mult, Direction::left);
            gameData_->board_->transformBlock_(dirs);
            break;
        case Type::RIGHT:
            dirs = gameData_->strat_->transform(mult, Direction::right);
            gameData_->board_->transformBlock_(dirs);
            break;
        case Type::DOWN:
            dirs = gameData_->strat_->transform(mult, Direction::down);
            gameData_->board_->transformBlock_(dirs);
            break;
        case Type::CLOCKWISE:
            dirs = gameData_->strat_->transform(mult, Direction::clockwise);
            gameData_->board_->transformBlock_(dirs);
            break;
        case Type::COUNTERCLOCKWISE:
            dirs = gameData_->strat_->
                    transform(mult, Direction::counterclockwise);
            gameData_->board_->transformBlock_(dirs);
            break;
        case Type::DROP:
            while (mult > 0) {
                gameData_->board_->drop_();
                gameData_->board_->updateScore_();
                _nextBlock();
                mult--;
                if (gameData_->board_->gameOver_()) {
                    break;
                }                    
                _constructiveForce();
                if (gameData_->board_->gameOver_()) {
                    break;
                }
            }
            break;
        case Type::LEVELUP:
            gameData_->lvl_ =
                    (4 > gameData_->lvl_ + mult) ? gameData_->lvl_ + mult : 4;
            _setLevel();
            break;
        case Type::LEVELDOWN:
            gameData_->lvl_ =
                    (0 < gameData_->lvl_ - mult) ? gameData_->lvl_ - mult : 0;
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
            gameData_->board_->replace_('I');
            break;
        case Type::J: 
            gameData_->board_->replace_('J');
            break;
        case Type::L: 
            gameData_->board_->replace_('L');
            break;
        case Type::S: 
            gameData_->board_->replace_('S');
            break;
        case Type::Z: 
            gameData_->board_->replace_('Z');
            break;
        case Type::O: 
            gameData_->board_->replace_('O');
            break;
        case Type::T:
            gameData_->board_->replace_('T');
            break;
        case Type::RESTART: 
            _restart();
            break;
        case Type::HINT:
            gameData_->board_->hint_(false);
            break;
        case Type::PLAY_HINT:
            gameData_->board_->hint_(true);
            gameData_->board_->updateScore_();
            _nextBlock();
            
            break;
        case Type::RENAME:
            break;
        case Type::ENABLE_BONUS:
            gameData_->bonusEnabled_ = true;
            break;
        case Type::DISABLE_BONUS:
            gameData_->bonusEnabled_ = false;
            break;
        case Type::BAD_COMMAND:
            std::cout << "Invalid player command! " <<
                "Please enter a proper player command." << std::endl;
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
    std::string newGame = "Y";

    while(newGame == "Y") {
        while (!gameData_->board_->gameOver_() && *(gameData_->in_) >> cmd) {
            _act(cmd);
        }
        std::cout << "BZZT! Game Over!" << std::endl;
        std::cout << "Would you like to play another game? (Y/N)" << std::endl;
        std::cin >> newGame;

        // if player would like to continue, restart game
        // and clear any renamed commands
        if(newGame == "Y")
        {
            _restart();
            cmd.resetMap_();
        }
    }
}