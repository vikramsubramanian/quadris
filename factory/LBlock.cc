#include "LBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

LBlock::LBlock()
{
    pieceList.push_back(Piece(0, 4, 'L'));
    pieceList.push_back(Piece(1, 4, 'L'));
    pieceList.push_back(Piece(2, 4, 'L'));
    pieceList.push_back(Piece(2, 3, 'L'));
}

LBlock::~LBlock() {}

LBlock *LBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new LBlock();
}
