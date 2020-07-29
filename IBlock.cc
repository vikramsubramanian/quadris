#include "IBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

IBlock::IBlock()
{
    pieceList.push_back(Piece(0, 3, 'I'));
    pieceList.push_back(Piece(1, 3, 'I'));
    pieceList.push_back(Piece(2, 3, 'I'));
    pieceList.push_back(Piece(3, 3, 'I'));
}

IBlock::~IBlock() {}

IBlock *IBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new IBlock();
}
