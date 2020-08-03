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

        bool gameOver_();

        // Accessors and Mutators
        int getScore_();
        int getHiScore_();
        void setHiScore_(int);
        void updateScore_();
        DisplayStruct *getState_();
        std::string getNextBlock_();

        // command functions
        void newBlock_(char);
        void transformBlock_(std::vector<Direction>);
        void drop_();
        void constructiveForce_(char);
        void replace_(char piece);
        void setLevel_(int);
        void hint_(bool);


    private:
        std::vector<Block*> blocks_;
        bool isGameOver_;
        Block* curBlock_;
        Block* nextBlock_;
        DisplayStruct *displayStruct_;
        void removeCurrentBlockFromDisplayBoard_();
        void generateBoardFromBlocks_();
};

#endif