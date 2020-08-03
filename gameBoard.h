#ifndef _GAMEBOARD_
#define _GAMEBOARD_
#include "subject.h"
#include "displayStruct.h"
#include "BlockFactory.h"
#include "block.h"

#include <vector>
#include <string>

class gameBoard : public Subject
{
    public:
        gameBoard();
        ~gameBoard();
        bool gameOver();
        void newBlock(char);
        void transformBlock(std::vector<Direction>);
        int getHiScore();
        void setHiScore(int);
        void updateScore();
        DisplayStruct *getState();
        std::string getNextBlock();
        void drop();
        void replace(char piece);
        void tempPrint();
        void setLevel(int);
        void decreaseLevel();
        void hint();


    private:

        std::vector<Block*> blocks;
        bool isGameOver;
        Block* curBlock;
        Block* nextBlock;
        DisplayStruct *displayStruct;
        //METHODS//
        
        void generateBoardFromBlocks();
};


#endif
