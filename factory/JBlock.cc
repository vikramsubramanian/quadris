#include "JBlock.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

JBlock::JBlock()
{
    pieceList.push_back(Piece(0, 3, 'J'));
    pieceList.push_back(Piece(0, 4, 'J'));
    pieceList.push_back(Piece(1, 4, 'J'));
    pieceList.push_back(Piece(2, 4, 'J'));
}

JBlock::~JBlock() {}

JBlock *JBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new JBlock();
}
