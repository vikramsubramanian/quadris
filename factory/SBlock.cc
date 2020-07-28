#include "SBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

SBlock::SBlock()
{
    pieceList.push_back(Piece(2, 3, 'S'));
    pieceList.push_back(Piece(1, 3, 'S'));
    pieceList.push_back(Piece(1, 4, 'S'));
    pieceList.push_back(Piece(0, 3, 'S'));
}

SBlock::~SBlock() {}

SBlock *SBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new SBlock();
}
