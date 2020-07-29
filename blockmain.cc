#include "BlockFactory.h"
#include "block.h"
#include "TBlock.h"
#include "gameBoard.h"

#include <iostream>
#include <vector>
using namespace std;


int main(){
    vector<direction> tryr;
    tryr.push_back(direction::right);
    tryr.push_back(direction::clockwise);
    tryr.push_back(direction::right);
    tryr.push_back(direction::down);
    tryr.push_back(direction::down);
    tryr.push_back(direction::down);
    
    gameBoard boop = gameBoard();
    boop.newBlock('T');
    boop.newBlock('O');
    boop.tempPrint();
    boop.transformBlock(tryr);
    boop.tempPrint();
    boop.newBlock('L');
    boop.tempPrint();
    boop.transformBlock(tryr);
    boop.tempPrint();
}

