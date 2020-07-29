#include "OBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

OBlock::OBlock()
{
    pieceList.push_back(Piece(0, 4, 'O'));
    pieceList.push_back(Piece(0, 3, 'O'));
    pieceList.push_back(Piece(1, 4, 'O'));
    pieceList.push_back(Piece(1, 3, 'O'));
}

OBlock::~OBlock() {}

OBlock *OBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new OBlock();
}
