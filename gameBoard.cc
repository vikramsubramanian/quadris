#include "gameBoard.h"
#include "displayStruct.h"
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"
#include "TBlock.h"

#include <vector>
#include <iostream>
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
        for (int i = 0; i < 4; i++)
        {
            //Now we check if we have space to get the new block in
            xCor = genblock->pieceList.at(i).x;
            yCor = genblock->pieceList.at(i).y;
            if (displayStruct->board[yCor][xCor] != '_')
            {
                //This means we have no space to get the new block into the board
                //this means the game is over
                isGameOver = true;
                cerr << "Looks like there is no place. Game Over." << endl;
                return;
            }
        }
            curBlock = nextBlock;
            nextBlock = genblock;
            if (curBlock != nullptr){
            blocks.push_back(curBlock);
            }
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
        for (int j=0; j<4; j++){
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
    delete displayStruct;
}

void gameBoard::transformBlock(vector<Direction> dirs){

    for (int i=0; i<dirs.size(); i++){
        generateBoardFromBlocks();
        curBlock->translate(dirs.at(i), displayStruct->board);
    }
}

void gameBoard::drop() {
    generateBoardFromBlocks();
    bool status = curBlock->translate(Direction::down, displayStruct->board);
    while (status==true){
        generateBoardFromBlocks();
        status = curBlock->translate(Direction::down, displayStruct->board);
    }
    curBlock = nullptr; 
    return;
}

int gameBoard::getScore(){

    return displayStruct->score;
}

void gameBoard::updateScore(){
    bool isFullFlag = true;
    int numberOfLines = 0;
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            if(displayStruct->board[i][j] = '_'){
                isFullFlag = false;
            }
        }

        if (isFullFlag == true){
            numberOfLines += 1;
            for (int j = 0; j < 11; j++)
            {
                displayStruct->board[i][j] = '_';
                for(int l=0; l< blocks.size(); l++){
                    for(int ll = 0; ll < 4; ll++){
                        if ( blocks.at(l)->pieceList.at(ll).x ==  j &&
                             blocks.at(l)->pieceList.at(ll).y ==  i)
                             {
                                 blocks.at(l)->pieceList.erase(blocks.at(l)->pieceList.begin() + ll);
                             }
                        if (blocks.at(l)->pieceList.size() == 0)
                            {
                                displayStruct->score += (1 + blocks.at(l)->level) * (1 + blocks.at(l)->level);
                                Block* temp = blocks.at(l);
                                blocks.erase(blocks.begin() + l);
                                delete temp;
                            }
                    }
                }
            }
        }
        isFullFlag = true;
    }
    displayStruct->score += (numberOfLines + displayStruct->level) * (numberOfLines + displayStruct->level);
    if (displayStruct->score > displayStruct->hiScore)
        displayStruct->hiScore = displayStruct->score;
    return;
}

DisplayStruct *gameBoard::getState(){
    return displayStruct;
}

char* gameBoard::getNextBlock(){
    char nextBlockRepr[2][4];
    char type = nextBlock->pieceList.at(1).type;
    for(int i=0; i<2; i++){
        for(int j=0; j<4; j++){
            nextBlockRepr[i][j] = '_';
        }
    }
    for (int i = 0; i < 4; i++)
    {
        nextBlockRepr[nextBlock->pieceList.at(i).y - 3][nextBlock->pieceList.at(i).x] = type;
    }
    return *nextBlockRepr;
}

void gameBoard::increaseLevel()
{
    displayStruct->level += 1;
}
void gameBoard::decreaseLevel()
{
    displayStruct->level -= 1;
}
