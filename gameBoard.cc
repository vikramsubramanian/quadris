#include "gameBoard.h"
#include "displayStruct.h"
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

gameBoard::gameBoard(){
    isGameOver = false;
    curBlock = nullptr;
    nextBlock = nullptr;
    displayStruct = new DisplayStruct;
    displayStruct->score = 0;
    displayStruct->hiScore = 0;
    displayStruct->level = 0;
    for(int i=0;i<18;i++){
        for(int j = 0; j<11; j++){
            //We use underscores for testing purposes. TODO: Final code should have " "
            displayStruct->board[i][j] = '_';
        }
    }
}

void gameBoard::newBlock(char piece){
    int xCor = -1;
    int yCor = -1;
    if (!isGameOver)
    {
        //We can have a new block only if the game is still playable

        Block *genblock = BlockFactory::createBlock(piece);
        genblock->level = displayStruct->level;
        for (int i = 0; i < genblock->pieceList.size(); i++)
        {
            //Now we check if we have space to get the new block in
            xCor = genblock->pieceList.at(i).x;
            yCor = genblock->pieceList.at(i).y;
            if (displayStruct->board[yCor][xCor] != '_')
            {
                //This means we have no space to get the new block into the board
                //this means the game is over
                isGameOver = true;
                return;
            }
        }
            curBlock = nextBlock;
            nextBlock = genblock;
            if (curBlock != nullptr){
            blocks.push_back(curBlock);
            }
    }
    if(blocks.size() >= 1)
    {
        generateBoardFromBlocks();
        notifyObservers();
    }
}

void gameBoard::generateBoardFromBlocks()
{

    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            displayStruct->board[i][j] = '_';
        }
    }

    int xCor = -1;
    int yCor = -1;
    for(int i=0; i<blocks.size(); i++){
        for (int j = 0; j < blocks.at(i)->pieceList.size(); j++)
        {
            xCor = blocks.at(i)->pieceList.at(j).x;
            yCor = blocks.at(i)->pieceList.at(j).y;
            displayStruct->board[yCor][xCor] = blocks.at(i)->pieceList.at(j).type;
        }
    }
}

bool gameBoard::gameOver()
{
    return isGameOver;
}

void gameBoard::tempPrint()
   {
       generateBoardFromBlocks();
       cout << "    ||1|2|3|4|5|6|7|8|9|A|B|" << endl;
       cout << "    ||_____________________|" << endl;
       cout << "0"
            << "   ||";
       for (int i = 0; i < 18; i++)
       {

           for (int j = 0; j < 11; j++)
           {
               //We use underscores for testing purposes. TODO: Final code should have " "
               cout << displayStruct->board[i][j] << "|";
           }
           if (i+1 < 10)
           {
               cout << endl
                    << i+1 << "   ||";
           }
           else
           {
               cout << endl
                    << i+1<< "  ||";
           }
       }
       cout << endl;
       cout << endl;
       if(nextBlock != nullptr){
           cout << "    |______________________|" << endl;
           cout << "    | NEXT BLOCK:          |" << endl
                << "    | ";
               for (int i = 0; i < 4; i++)
           {
               cout << "("<< nextBlock->pieceList.at(i).x << "," << nextBlock->pieceList.at(i).y << ")";
           }
       }
       cout << " |" << endl;
       cout << "    |______________________|" << endl << endl;
   }


gameBoard::~gameBoard()
{
    delete nextBlock;
    for (auto p : blocks)
    {
        delete p;
    }
    blocks.clear();
    delete displayStruct;
}

void gameBoard::transformBlock(vector<Direction> dirs){

    for (int i=0; i<dirs.size(); i++){
        generateBoardFromBlocks();
        curBlock->translate(dirs.at(i), displayStruct->board);
    }
    generateBoardFromBlocks();
    notifyObservers();
}

void gameBoard::drop() {
    generateBoardFromBlocks();
    bool status = curBlock->translate(Direction::down, displayStruct->board);
    while (status==true){
        generateBoardFromBlocks();
        status = curBlock->translate(Direction::down, displayStruct->board);
    }
    curBlock = nullptr;
    generateBoardFromBlocks();
    notifyObservers();
    return;
}

int gameBoard::getScore(){

    return displayStruct->score;
}

void gameBoard::updateScore()
{

    bool isFullFlag = true;
    int numberOfLines = 0;
    for(int counter = 0; counter < 18; counter++)
    {
        generateBoardFromBlocks();
        for (int j = 0; j < 11; j++)
        {
            if (displayStruct->board[counter][j] == '_')
            {
                isFullFlag = false;
            }
        }

        if (isFullFlag == true)
        {
            numberOfLines += 1;
            for (int j = 0; j < 11; j++)
            {
                displayStruct->board[counter][j] = '_';
                for (int l = 0; l < blocks.size(); l++)
                {
                    for (int ll = 0; ll < blocks.at(l)->pieceList.size(); ll++)
                    {
                        if (blocks.at(l)->pieceList.at(ll).x == j &&
                            blocks.at(l)->pieceList.at(ll).y == counter &&
                            blocks.at(l) != curBlock)
                        {
                            blocks.at(l)->pieceList.erase(blocks.at(l)->pieceList.begin() + ll);
                        }
                        if (blocks.at(l)->pieceList.size() == 0)
                        {
                            displayStruct->score += (1 + blocks.at(l)->level) * (1 + blocks.at(l)->level);
                            Block *temp = blocks.at(l);
                            blocks.erase(blocks.begin() + l);
                            delete temp;
                        }
                    }
                }
            }
            
            for (int l = 0; l < blocks.size(); l++)
            {
                if (blocks.at(l) != curBlock)
                {
                    
                    generateBoardFromBlocks();
                    tempPrint();
                    blocks.at(l)->shiftDown(displayStruct->board);

                    
                }
            }
             
        }
        isFullFlag = true;
    }
    // We update score only if rows have been deleted
    if (numberOfLines > 0)
    {
        displayStruct->score += (numberOfLines + displayStruct->level) * (numberOfLines + displayStruct->level);
    }
    if (displayStruct->score > displayStruct->hiScore)
    {
        displayStruct->hiScore = displayStruct->score;
    }


    return;
}

DisplayStruct *gameBoard::getState(){
    return displayStruct;
}

void gameBoard::replace(char piece)
{
    blocks.erase(std::remove(blocks.begin(), blocks.end(), curBlock), blocks.end());
    generateBoardFromBlocks();
    
    //Now we generate a new block
    int xCor = -1;
    int yCor = -1;
    if (!isGameOver)
    {
        //We can have a new block only if the game is still playable
        Block *genblock = BlockFactory::createBlock(piece);
        genblock->level = displayStruct->level;
        for (int i = 0; i < genblock->pieceList.size(); i++)
        {
            //Now we check if we have space to get the new block in
            xCor = genblock->pieceList.at(i).x;
            yCor = genblock->pieceList.at(i).y;
            if (displayStruct->board[yCor][xCor] != '_')
            {
                //This means we have no space to get the new block into the board
                //this means the game is over
                isGameOver = true;
                return;
            }
        }
        curBlock = genblock;
        blocks.push_back(curBlock);


        generateBoardFromBlocks();
        notifyObservers();
    }
}

string gameBoard::getNextBlock(){
    string nextBlockRepr;
    char type = nextBlock->pieceList.at(1).type;
    for(int i=0; i<2; i++){
        for(int j=0; j<4; j++){
            nextBlockRepr[i*4+j] = '_';
        }
    }
    for (int i = 0; i < nextBlock->pieceList.size(); i++)
    {
        nextBlockRepr[(nextBlock->pieceList.at(i).y - 3)*4+nextBlock->pieceList.at(i).x] = type;
    }
    return string(nextBlockRepr);
}

void gameBoard::setLevel(int lvl)
{
    displayStruct->level = lvl;
}