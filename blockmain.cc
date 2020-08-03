#include "BlockFactory.h"
#include "block.h"
#include "gameBoard.h"

#include <iostream>
#include <vector>
using namespace std;


int main(){
    vector<Direction> tryr;
    tryr.push_back(Direction::counterclockwise);

    
    tryr.push_back(Direction::right);
    
    gameBoard boop = gameBoard();

    boop.newBlock('J');
    boop.newBlock('Z');
    boop.drop();

    boop.newBlock('S');
    boop.transformBlock(tryr);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    boop.drop();

    boop.newBlock('S');
    boop.transformBlock(tryr);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    boop.drop();
    boop.newBlock('L');
    boop.transformBlock(tryr);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    boop.drop();

    boop.newBlock('I');
    boop.transformBlock(tryr);
    tryr.push_back(Direction::right);
    tryr.push_back(Direction::right);
    boop.drop();

    boop.hint();
    boop.newBlock('I');
    boop.tempPrint();
    boop.updateScore();
    boop.tempPrint();
    // boop.newBlock('L');
    // boop.tempPrint();
    // boop.transformBlock(tryr);
    // boop.tempPrint();

}

