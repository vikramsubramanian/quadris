#include "blockTypes.h"
#include "block.h"
#include "piece.h"
#include "BlockFactory.h"

#include <iostream>

//////////////////////////////////////////
///////////    I BLOCK    ////////////////
//////////////////////////////////////////
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


//////////////////////////////////////////
///////////    J BLOCK    ////////////////
//////////////////////////////////////////
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
//////////////////////////////////////////
///////////    L BLOCK    ////////////////
//////////////////////////////////////////
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
//////////////////////////////////////////
///////////    O BLOCK    ////////////////
//////////////////////////////////////////
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

//////////////////////////////////////////
///////////    S BLOCK    ////////////////
//////////////////////////////////////////
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
//////////////////////////////////////////
///////////    T BLOCK    ////////////////
//////////////////////////////////////////
TBlock::TBlock()
{
    pieceList.push_back(Piece(0, 3, 'T'));
    pieceList.push_back(Piece(1, 3, 'T'));
    pieceList.push_back(Piece(1, 4, 'T'));
    pieceList.push_back(Piece(2, 3, 'T'));
}

TBlock::~TBlock() {}

TBlock *TBlock::Factory::create()
{
    std::cerr << "New block factory created" << std::endl;
    return new TBlock();
}

//////////////////////////////////////////
///////////    Z BLOCK    ////////////////
//////////////////////////////////////////
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
