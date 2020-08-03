#include "BlockFactory.h"
#include "block.h"
#include "gameBoard.h"

#include <iostream>
#include <vector>
using namespace std;


int main(){
    vector<Direction> tryr;
    tryr.push_back(Direction::right);
    vector<Direction> tryr2;
    tryr2.push_back(Direction::clockwise);
    // tryr2.push_back(Direction::counterclockwise);
    // tryr2.push_back(Direction::counterclockwise);

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


    boop.hint();
    boop.newBlock('I');
    boop.tempPrint();
    boop.transformBlock(tryr2);
    boop.tempPrint();
    // boop.transformBlock(tryr2);
    // boop.tempPrint();
    // boop.transformBlock(tryr2);
    // boop.tempPrint();
    // boop.transformBlock(tryr2);
    // boop.tempPrint();
    // boop.transformBlock(tryr2);
    // boop.tempPrint();
    // boop.newBlock('I');

    

    // boop.newBlock('L');
    // boop.tempPrint();
    // boop.transformBlock(tryr);
    // boop.tempPrint();

}

