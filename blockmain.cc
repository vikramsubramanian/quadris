#include "BlockFactory.h"
#include "block.h"
#include "gameBoard.h"

#include <iostream>
#include <vector>
using namespace std;


int main(){
    vector<Direction> tryr;
    tryr.push_back(Direction::clockwise);


    
    gameBoard boop = gameBoard();

    boop.newBlock('L');
    boop.newBlock('L');
    boop.tempPrint();
    boop.transformBlock(tryr);
    // boop.drop();
    boop.tempPrint();
    boop.newBlock('L');

    

    // boop.newBlock('L');
    // boop.tempPrint();
    // boop.transformBlock(tryr);
    // boop.tempPrint();

}

