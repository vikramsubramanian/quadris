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
    rotateAroundPivot[0] = 0;
    rotateAroundPivot[1] = 3;
}

IBlock::~IBlock() {}

IBlock *IBlock::Factory::create()
{
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
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

JBlock::~JBlock() {}

JBlock *JBlock::Factory::create()
{
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
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

LBlock::~LBlock() {}

LBlock *LBlock::Factory::create()
{
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
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

OBlock::~OBlock() {}

OBlock *OBlock::Factory::create()
{
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
    pieceList.push_back(Piece(0, 4, 'S'));
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

SBlock::~SBlock() {}

SBlock *SBlock::Factory::create()
{
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
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

TBlock::~TBlock() {}

TBlock *TBlock::Factory::create()
{
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
    rotateAroundPivot[0] = 2;
    rotateAroundPivot[1] = 3;
}

ZBlock::~ZBlock() {}

ZBlock *ZBlock::Factory::create()
{
    return new ZBlock();
}
//////////////////////////////////////////
/////////// B BLOCK FOR LEVEL 4 //////////
//////////////////////////////////////////
BBlock::BBlock()
{
    pieceList.push_back(Piece(5, 3, 'B'));
    rotateAroundPivot[0] = 5;
    rotateAroundPivot[1] = 3;
}

BBlock::~BBlock() {}

BBlock *BBlock::Factory::create()
{
    return new BBlock();
}
