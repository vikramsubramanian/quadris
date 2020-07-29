#include "ZBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

ZBlock::ZBlock()
{
    pieceList.push_back(Piece(0, 3, 'Z'));
    pieceList.push_back(Piece(1, 3, 'Z'));
    pieceList.push_back(Piece(1, 4, 'Z'));
    pieceList.push_back(Piece(2, 4, 'Z'));
}

ZBlock::~ZBlock() {}

ZBlock *ZBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new ZBlock();
}
