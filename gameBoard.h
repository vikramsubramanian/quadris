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
        int getScore();
        void updateScore();
        DisplayStruct *getState();
        std::string getNextBlock();
        void drop();
        //I think Julia will work on the text display. She could take this and work off it.
        void tempPrint();
        void increaseLevel();
        void decreaseLevel();


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
