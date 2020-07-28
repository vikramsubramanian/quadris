#include "TBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

TBlock::TBlock()
{
    pieceList.push_back(Piece(0, 3, 'T'));
    pieceList.push_back(Piece(1, 3, 'T'));
    pieceList.push_back(Piece(1, 4, 'T'));
    pieceList.push_back(Piece(2, 3, 'T'));
}

TBlock::~TBlock(){}

TBlock * TBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new TBlock();
}
