#ifndef _BLOCK_TYPES_H_
#define _BLOCK_TYPES_H_
#include "BlockFactory.h"
#include "block.h"
#include "piece.h"

//////////////////////////////////////////
///////////    I BLOCK    ////////////////
//////////////////////////////////////////
class IBlock : public Block
{
    IBlock();
    ~IBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        IBlock *create();
        friend class BlockFactoryInitializer;
    };
};
//////////////////////////////////////////
///////////    J BLOCK    ////////////////
//////////////////////////////////////////
class JBlock : public Block
{
    JBlock();
    ~JBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        JBlock *create();
        friend class BlockFactoryInitializer;
    };
};

//////////////////////////////////////////
///////////    L BLOCK    ////////////////
//////////////////////////////////////////
class LBlock : public Block
{
    LBlock();
    ~LBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        LBlock *create();
        friend class BlockFactoryInitializer;
    };
};

//////////////////////////////////////////
///////////    O BLOCK    ////////////////
//////////////////////////////////////////

class OBlock : public Block
{
    OBlock();
    ~OBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        OBlock *create();
        friend class BlockFactoryInitializer;
    };
};

//////////////////////////////////////////
///////////    S BLOCK    ////////////////
//////////////////////////////////////////

class SBlock : public Block
{
    SBlock();
    ~SBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        SBlock *create();
        friend class BlockFactoryInitializer;
    };
};
//////////////////////////////////////////
///////////    T BLOCK    ////////////////
//////////////////////////////////////////
class TBlock : public Block
{
    TBlock();
    ~TBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        TBlock *create();
        friend class BlockFactoryInitializer;
    };

};

//////////////////////////////////////////
///////////    Z BLOCK    ////////////////
//////////////////////////////////////////

class ZBlock : public Block
{
    ZBlock();
    ~ZBlock();

    friend class BlockFactoryInitializer;
    friend class Factory;

    class Factory : public BlockFactory
    {
        ZBlock *create();
        friend class BlockFactoryInitializer;
    };
};
//////////////////////////////////////////
#endif
