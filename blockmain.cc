#include "BlockFactory.h"
#include "block.h"
#include "gameBoard.h"

#include <iostream>
#include <vector>
using namespace std;


int main(){
    vector<Direction> tryr;
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::clockwise);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::down);
    tryr.push_back(Direction::down);
    tryr.push_back(Direction::down);
    
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

